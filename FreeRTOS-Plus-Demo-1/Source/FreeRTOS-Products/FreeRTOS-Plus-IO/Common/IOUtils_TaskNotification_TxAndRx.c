/*
 * IOUtils_tasknotification_TxAndRx.c
 *
 *  Created on: 30-May-2016
 *      Author: jaguar
 */

/* Standard includes. */
#include "string.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Device specific library includes. */
#include "FreeRTOS_DriverInterface.h"
#include "IOUtils_Common.h"

/*-----------------------------------------------------------*/
//
//
//lecture - i2c-eeprom - invoked from generic ioctl method from FreeRTOS_DriverInterface.c
//
//lecture - UART - invoked from generic ioctl method from FreeRTOS_DriverInterface.c
//

portBASE_TYPE xIOUtilsConfigureTasknotificationCircularBuffer( Peripheral_Control_t * const pxPeripheralControl,const uint32_t ulRequest, const portBASE_TYPE xBufferSize )
//portBASE_TYPE xIOUtilsConfigureCircularBufferRx( Peripheral_Control_t * const pxPeripheralControl, const portBASE_TYPE xBufferSize )
{
portBASE_TYPE xReturn = pdFAIL;
//Circular_Buffer_Rx_State_t *pxCircularBufferState;
TaskNotification_Circular_Buffer_State_t *pxCircularBufferState;

Transfer_Control_t **ppxTransferControl;

	if( ulRequest == ioctlUSE_TASKNOTIFICATION_TX )
	{
		ppxTransferControl = &( pxPeripheralControl->pxTxControl );
	}
	else
	{
		ppxTransferControl = &( pxPeripheralControl->pxRxControl );
	}



	/* A peripheral is going to use a Circular_Buffer structure to
	control Txn/Rxn. */
	vIOUtilsCreateTransferControlStructure( ppxTransferControl );
	configASSERT( *ppxTransferControl );
	//vIOUtilsCreateTransferControlStructure( &( pxPeripheralControl->pxRxControl ) );
	//configASSERT( pxPeripheralControl->pxRxControl );

	//if( pxPeripheralControl->pxRxControl != NULL )
	if( *ppxTransferControl != NULL )
	{
		/* Create the necessary structure. */
		//pxCircularBufferState = pvPortMalloc( sizeof( Circular_Buffer_Rx_State_t ) );
		pxCircularBufferState = pvPortMalloc( sizeof( TaskNotification_Circular_Buffer_State_t ) );

		if( pxCircularBufferState != NULL )
		{
				pxCircularBufferState->pucBufferStart = pvPortMalloc( xBufferSize );

				if( pxCircularBufferState->pucBufferStart != NULL )
				{
					pxCircularBufferState->usBufferLength = ( uint16_t ) xBufferSize;
					pxCircularBufferState->usErrorState = 0U;
					pxCircularBufferState->usNextReadIndex = 0U;
					pxCircularBufferState->usCharCount = 0U;
					pxCircularBufferState->usNextWriteIndex = 0U;
					//pxPeripheralControl->pxRxControl->pvTransferState = ( void * ) pxCircularBufferState;
					//pxPeripheralControl->pxRxControl->ucType = ioctlUSE_CIRCULAR_BUFFER_RX;
					//pxPeripheralControl->pxRxControl->ucType = ( uint8_t ) ulRequest;
					pxCircularBufferState->xBlockTime = portMAX_DELAY;

					( *ppxTransferControl )->pvTransferState = ( void * ) pxCircularBufferState;
					( *ppxTransferControl )->ucType = ( uint8_t ) ulRequest;


					xReturn = pdPASS;
				}
				else
				{
					/* The circular buffer was not created successfully, free the
					  pxCircularBufferState structure and just return an error. */
									vPortFree( pxCircularBufferState );
									pxCircularBufferState = NULL;

				}

		}

		if( pxCircularBufferState == NULL )
		{
			/* The Rx structure, or a member it contains,  could not be created,
			so the Rx control structure (which should point to it) should also
			be deleted. */
			//vPortFree( pxPeripheralControl->pxRxControl );
			vPortFree( *ppxTransferControl );
			*ppxTransferControl = NULL;
			//pxPeripheralControl->pxRxControl = NULL;
		}
	}

	return xReturn;
}
/*-----------------------------------------------------------*/


void vIOUtilsClearTasknotificationRxCircularBuffer( Peripheral_Control_t * const pxPeripheralControl )
{
	TaskNotification_Circular_Buffer_State_t *pxCircularBufferState = prvTaskNotificationRxCIRCULAR_BUFFER_STATE( pxPeripheralControl );
	pxCircularBufferState->usErrorState = 0U;
	pxCircularBufferState->usNextReadIndex = 0U;
	pxCircularBufferState->usCharCount = 0U;
	pxCircularBufferState->usNextWriteIndex = 0U;
	//xSemaphoreTake( pxCircularBufferState->xNewDataSemaphore, 0U );
}

/*-----------------------------------------------------------*/
portBASE_TYPE xIOUtilsReadCharsFromTaskNotificationCircularBuffer( TaskNotification_Circular_Buffer_State_t * const pxCircularBuffer, uint8_t * const pucBuffer, const size_t xBytesToRead )
{
size_t xBytesAvailable, xBytesReadSoFar = 0U;
portBASE_TYPE xAttempts;
const portBASE_TYPE xMaxAttempts = 2;

	/* Two attempts at reading the required number of bytes are made in	case
	the first read just reads up to the end of the circular buffer before
	wrapping back round to the start - in which case the second	attempt will
	try and read the remaining bytes from the start. */
	for( xAttempts = 0; xAttempts < xMaxAttempts; xAttempts++ )
	{
		if( pxCircularBuffer->usCharCount == 0U )
		{
			/* There are no more characters in the buffer, so there is no point
			continuing. */
			break;
		}

		if( pxCircularBuffer->usNextReadIndex <= pxCircularBuffer->usNextWriteIndex )
		{
			/* How many bytes are available between the read and write
			indexes? */
			xBytesAvailable = ( pxCircularBuffer->usNextWriteIndex - pxCircularBuffer->usNextReadIndex );
		}
		else
		{
			/* How many bytes are available up to the end of the buffer? */
			xBytesAvailable = ( pxCircularBuffer->usBufferLength - pxCircularBuffer->usNextReadIndex );
		}

		/* Cap the bytes to read to a maximum of those asked for. */
		if( xBytesAvailable > ( xBytesToRead - xBytesReadSoFar ) )
		{
			xBytesAvailable = ( xBytesToRead - xBytesReadSoFar );
		}

		configASSERT( xBytesAvailable );

		/* Copy the bytes. */
		memcpy( &( pucBuffer[ xBytesReadSoFar ] ), &( pxCircularBuffer->pucBufferStart[ pxCircularBuffer->usNextReadIndex ] ), xBytesAvailable );

		/* Remember how many bytes have been read for the next iteration of
		this loop. */
		xBytesReadSoFar += xBytesAvailable;

		/* Characters have been removed from the buffer. */
		pxCircularBuffer->usCharCount -= xBytesAvailable;
		pxCircularBuffer->usNextReadIndex += xBytesAvailable;

		configASSERT( pxCircularBuffer->usNextReadIndex <= pxCircularBuffer->usBufferLength );

		if( pxCircularBuffer->usNextReadIndex == pxCircularBuffer->usBufferLength )
		{
			pxCircularBuffer->usNextReadIndex = 0U;
		}

		if( xBytesToRead == xBytesReadSoFar )
		{
			/* No more bytes are needed. */
			break;
		}
	}

	return xBytesReadSoFar;
}

portBASE_TYPE xIOUtilsWriteCharsintoTaskNotificationCircularBuffer( TaskNotification_Circular_Buffer_State_t * const pxCircularBuffer, uint8_t * const pucBuffer, const size_t xBytesToWrite )
{
size_t xSpaceAvailable, xBytesWroteSoFar = 0U;
portBASE_TYPE xAttempts;
const portBASE_TYPE xMaxAttempts = 2;


	for( xAttempts = 0; xAttempts < xMaxAttempts; xAttempts++ )
	{
		if( pxCircularBuffer->usCharCount == pxCircularBuffer->usBufferLength )
		{
			/*  buffer is FULL, so there is no point in continuing. */
			break;
		}

		if( pxCircularBuffer->usNextWriteIndex == pxCircularBuffer->usNextReadIndex )
		{
			xSpaceAvailable = pxCircularBuffer->usBufferLength;
			pxCircularBuffer->usNextWriteIndex = 0;
						pxCircularBuffer->usNextReadIndex = 0;
		}
		else if( pxCircularBuffer->usNextWriteIndex <= pxCircularBuffer->usNextReadIndex )
		{
			/* How many bytes are available between the read and write
			indexes? */
			xSpaceAvailable = ( pxCircularBuffer->usNextReadIndex - pxCircularBuffer->usNextWriteIndex );

		}
		else
		{
			/* How many bytes are available up to the end of the buffer? */
			xSpaceAvailable = ( pxCircularBuffer->usBufferLength - pxCircularBuffer->usNextWriteIndex );
		}

		/* If more space available : Cap the space available to bytes to write. */
		if( xSpaceAvailable > ( xBytesToWrite - xBytesWroteSoFar ) )
		{
			xSpaceAvailable = ( xBytesToWrite - xBytesWroteSoFar);
		}

		configASSERT( xSpaceAvailable );

		/* Copy the bytes into circular buffer */

		memcpy( &( pxCircularBuffer->pucBufferStart[ pxCircularBuffer->usNextWriteIndex ] ),&( pucBuffer[ xBytesWroteSoFar ] ),  xSpaceAvailable );

		/* Remember how many bytes have been wrote --for the next iteration of	this loop. */
		xBytesWroteSoFar += xSpaceAvailable;

		/* Characters have been removed from the buffer. */
		pxCircularBuffer->usCharCount += xSpaceAvailable;
		pxCircularBuffer->usNextWriteIndex += xSpaceAvailable;

    	configASSERT( pxCircularBuffer->usNextWriteIndex <= pxCircularBuffer->usBufferLength );

		if( pxCircularBuffer->usNextWriteIndex == pxCircularBuffer->usBufferLength )
		{
			pxCircularBuffer->usNextWriteIndex = 0U;
		}

		if( xBytesToWrite == xBytesWroteSoFar )
		{
			/* No more bytes are needed. */
			break;
		}
	}

	return xBytesWroteSoFar;
}



/*-----------------------------------------------------------*/
#if 0
void vIOUtilsSetCircularBufferTimeout( Peripheral_Control_t *pxPeripheralControl, portTickType xMaxWaitTime )
{
Transfer_Control_t *pxTransferControlState = pxPeripheralControl->pxRxControl;
Circular_Buffer_Rx_State_t *pxCircularBufferState;

	pxCircularBufferState = ( Circular_Buffer_Rx_State_t * ) ( pxTransferControlState->pvTransferState );
	pxCircularBufferState->xBlockTime = xMaxWaitTime;
}
#endif

#if 0
	//aaa-zzz
uint32_t ioutilsRX_CHARS_INTO_TASKNOTIFICATION_CIRCULAR_BUFFER_FROM_ISR( Transfer_Control_t *pxTransferControl,portBASE_TYPE *xHigherPriorityTaskWoken)
//#define ioutilsRX_CHARS_INTO_TASKNOTIFICATION_CIRCULAR_BUFFER_FROM_ISR( pxTransferControl, xCondition, xReceiveFunction, ulReceived, xHigherPriorityTaskWoken )
{
TaskNotification_Circular_Buffer_State_t* const pxCircularBufferRxState = ( TaskNotification_Circular_Buffer_State_t * ) ( ( pxTransferControl )->pvTransferState );
uint16_t *pusNextWrite;
uint32_t ulReceived = 0;
	pusNextWrite = &( pxCircularBufferRxState->usNextWriteIndex );

	while( ( LPC_UART3->LSR & UART_LSR_RDR ) != 0 ) //RDR=1 ==> rx_fifo not empty
	{
		/* If there is space in the circular buffer. */
		if( pxCircularBufferRxState->usCharCount < pxCircularBufferRxState->usBufferLength )
		{

			pxCircularBufferRxState->pucBufferStart[ *pusNextWrite ] = ( LPC_UART3->RBR );
			ulReceived++;
			( pxCircularBufferRxState->usCharCount )++;

			/* Move on to the next index, wrapping if necessary. */
			( *pusNextWrite )++;
			if( *pusNextWrite == pxCircularBufferRxState->usBufferLength )
			{
				*pusNextWrite = 0U;
			}
		}
		else
		{
			/* An overrun has occurred. */
			pxCircularBufferRxState->usErrorState = pdTRUE;
		}
	}

	if( ulReceived > 0UL )
	{
		/* Unblock any tasks that might have been waiting for new data to
		arrive. */
		vTaskNotifyGiveFromISR(pxCircularBufferRxState->task_to_be_Notified ,&( xHigherPriorityTaskWoken ) );

		{
			int a;
			a++;
			a = a+1;

		}
	}
}
#endif

#if 1
//aaa-zzz
size_t  ioutilsTRANSMIT_TO_TASKNOTIFICATION_CIRCULAR_BUFFER( Peripheral_Control_t *  pxPeripheralControl, void *pucBuffer,size_t xBytes)
{
portTickType xTicksToWait;
xTimeOutType xTimeOut;
unsigned int xbytesWritten=0;
size_t xBytesSent=0;
TaskNotification_Circular_Buffer_State_t *pxCircularBufferState ;
int ret=0;
LPC_USART_T * const pxUART = (LPC_USART_T * const) diGET_PERIPHERAL_BASE_ADDRESS( pxPeripheralControl ); //aaa-zzz
pxCircularBufferState = prvTaskNotificationTxCIRCULAR_BUFFER_STATE( pxPeripheralControl );
( xBytesSent ) = 0U;
	xTicksToWait = pxCircularBufferState->xBlockTime;
	vTaskSetTimeOutState( &xTimeOut );
	pxCircularBufferState->task_to_be_Notified = xTaskGetCurrentTaskHandle();
	/* Are there any more bytes to be sent? */
	while( ( xBytesSent ) < xBytes )
	{
		xbytesWritten = 0;
		Chip_UART_IntDisable(pxUART, UART_IER_THREINT);	/* Disable peripheral. */

        xbytesWritten = xIOUtilsWriteCharsintoTaskNotificationCircularBuffer( pxCircularBufferState, &( ( pucBuffer ) [ ( xBytesSent ) ] ), xBytes - ( xBytesSent ) );

    	Chip_UART_IntEnable( pxUART, UART_IER_THREINT);	/* Enable peripheral. */

    	//Chip_UART_SendByte(pxUART,'c');

#if 1
        #define uartTX_BUSY_MASK			( 1UL << 6UL )
    	//In case - this is not High priority task: because of that it may get
    	//only intermittent time slices. If this is the case , by now it could
    	//be the case that UART-Tx buffer is Empty.
    	// so Fill the buffer again.
    	// (OR)
    	//mimic - task notific based TX-ISR code for Txing First char.
// do this only for condition THR is Empty.
	//if ( pxUART->LSR & UART_LSR_TEMT == 0)
	if( ( ( pxUART->LSR & uartTX_BUSY_MASK ) == uartTX_BUSY_MASK ) )
	{
		uint16_t  *usNextReadIndexp;
		uint8_t ucChar;
		uint8_t ultransmitted=0;
		usNextReadIndexp = &( pxCircularBufferState->usNextReadIndex );

		if( pxCircularBufferState->usCharCount > 0 )
		{
			ucChar = pxCircularBufferState->pucBufferStart[ *usNextReadIndexp];
            //(pxCircularBufferState->pucBufferStart)++;
            LPC_UART3->THR = ucChar;
            ultransmitted++;
        	( pxCircularBufferState->usCharCount )--;
			/* Move on to the next index, wrapping if necessary. */
			( *usNextReadIndexp )++;
			if( *usNextReadIndexp == pxCircularBufferState->usBufferLength )
			{
				*usNextReadIndexp = 0U;
			}
		}
	}



#endif
	    ( xBytesSent ) += xbytesWritten;
		if(xbytesWritten > 1)
		//if(xbytesWritten > 0)
        {
			ret= ulTaskNotifyTake( pdTRUE, portMAX_DELAY);
           //if( (ulTaskNotifyTake( pdTRUE, portMAX_DELAY) ) != pdTRUE) )
			{
			int a=3;
			a++;
			}

        }
		if( xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait ) != pdFALSE )
		{
			/* Time out has expired. */
			break;
		}
	} //while
}
#endif



