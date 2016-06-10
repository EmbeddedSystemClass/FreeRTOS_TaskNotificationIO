/*
 * IOUtils_tasknotification_TxAndRx.h
 *
 *  Created on: 30-May-2016
 *      Author: jaguar
 */

//#ifndef CIRCULAR_BUFFER_RX_H
//#define CIRCULAR_BUFFER_RX_H

#include "FreeRTOS_IO.h" //aaa-zzz : for  LPC_USART_T in IO-Utils Fns , If MACROS used no need of this header here
#ifndef TASK_NOTIFICATION_TX_RX_H
#define TASK_NOTIFICATION_TX_RX_H

/* The transfer structure used when a circular buffer is used for
reception. */
//typedef struct xCIRCULAR_BUFFER_RX_STATE
typedef struct xTASK_NOTIFICATION_CIRCULARBUFFER_STATE
{
	uint8_t *pucBufferStart;			/* The start address of the buffer storage area. */
	uint16_t usBufferLength;			/* The total length of the circular buffer. */
	uint16_t usNextWriteIndex;			/* Index into pucBufferStart to which the next received byte will be written. */
	uint16_t usNextReadIndex;			/* Index into pucBufferStart from which the next byte will be read. */
	uint16_t usErrorState;				/* Currently just set to pdFALSE or pdTRUE if a buffer overrun has not/has occurred respectively. */
	portTickType xBlockTime;			/* The amount of time a task should be held in the Blocked state (not using CPU time) to wait for data to become available when it attempts a read. */
	uint16_t usCharCount;				/* The number of characters currently in the circular buffer.  The difference between the number of characters written to the buffer, and the number read from the buffer. */
	TaskHandle_t task_to_be_Notified;
} TaskNotification_Circular_Buffer_State_t;
//} TaskNotification_IO_State_t;

#endif /* TASK_NOTIFICATION_TX_RX_H */

#define prvTaskNotificationTxCIRCULAR_BUFFER_STATE( pxPeripheralControl ) ( (  TaskNotification_Circular_Buffer_State_t * ) ( pxPeripheralControl )->pxTxControl->pvTransferState )
#define prvTaskNotificationRxCIRCULAR_BUFFER_STATE( pxPeripheralControl ) ( (  TaskNotification_Circular_Buffer_State_t * ) ( pxPeripheralControl )->pxRxControl->pvTransferState )
#define prvTaskNotificationIO_STATE( pxPeripheralControl ) ( (  TaskNotification_IO_State_t * ) ( pxPeripheralControl )->pxRxControl->pvTransferState )

portBASE_TYPE xIOUtilsReadCharsFromTaskNotificationCircularBuffer( TaskNotification_Circular_Buffer_State_t * const pxCircularBuffer, uint8_t * const pucBuffer, const size_t xBytesToRead );
portBASE_TYPE xIOUtilsWriteCharsintoTaskNotificationCircularBuffer( TaskNotification_Circular_Buffer_State_t * const pxCircularBuffer, uint8_t * const pucBuffer, const size_t xBytesToWrite );

#define ioutilsRECEIVE_FROM_TASKNOTIFICATION_CIRCULAR_BUFFER( pxPeripheralControl, xPeripheralDisable, xPeripheralEnable, pucBuffer, xBytes, xBytesReceived )	\
{																														\
portTickType xTicksToWait;																								\
xTimeOutType xTimeOut;																									\
TaskNotification_Circular_Buffer_State_t *pxCircularBufferState = prvTaskNotificationRxCIRCULAR_BUFFER_STATE( pxPeripheralControl );					\
																														\
	( xBytesReceived ) = 0U;																							\
	xTicksToWait = pxCircularBufferState->xBlockTime;																	\
	vTaskSetTimeOutState( &xTimeOut );																					\
	pxCircularBufferState->task_to_be_Notified = xTaskGetCurrentTaskHandle();								            \
	/* Are there any more bytes to be received? */																		\
	while( ( xBytesReceived ) < xBytes )																				\
	{                                                                                                                   \
        if(ulTaskNotifyTake( pdTRUE, portMAX_DELAY ) == pdPASS ) 											            \
		{														 														\
			( xPeripheralDisable ); 																					\
			( xBytesReceived ) += xIOUtilsReadCharsFromTaskNotificationCircularBuffer( pxCircularBufferState, &( ( pucBuffer ) [ ( xBytesReceived ) ] ), xBytes - ( xBytesReceived ) ); \
			( xPeripheralEnable );																						\
		}																												\
																														\
		if( xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait ) != pdFALSE )												\
		{																												\
			/* Time out has expired. */																					\
			break;																										\
		}																												\
	}																													\
}

//aaa-zzz
#if 1
#define ioutilsRX_CHARS_INTO_TASKNOTIFICATION_CIRCULAR_BUFFER_FROM_ISR( pxTransferControl, xCondition, xReceiveFunction, ulReceived, xHigherPriorityTaskWoken )	\
{																														\
TaskNotification_Circular_Buffer_State_t* const pxCircularBufferRxState = ( TaskNotification_Circular_Buffer_State_t * ) ( ( pxTransferControl )->pvTransferState );	\
uint16_t *pusNextWrite;																									\
																														\
	pusNextWrite = &( pxCircularBufferRxState->usNextWriteIndex );														\
																														\
	while( ( xCondition ) )																								\
	{																													\
		/* If there is space in the circular buffer. */																	\
		if( pxCircularBufferRxState->usCharCount < pxCircularBufferRxState->usBufferLength )							\
		{																												\
			pxCircularBufferRxState->pucBufferStart[ *pusNextWrite ] = ( xReceiveFunction );							\
			ulReceived++;																								\
			( pxCircularBufferRxState->usCharCount )++;																	\
																														\
			/* Move on to the next index, wrapping if necessary. */														\
			( *pusNextWrite )++;																						\
			if( *pusNextWrite == pxCircularBufferRxState->usBufferLength )												\
			{																											\
				*pusNextWrite = 0U;																						\
			}																											\
		}																												\
		else																											\
		{																												\
			/* An overrun has occurred. */																				\
			pxCircularBufferRxState->usErrorState = pdTRUE;																\
		}																												\
	}																													\
																														\
	if( ulReceived > 0UL )																								\
	{																													\
		/* Unblock any tasks that might have been waiting for new data to 												\
		arrive. */	                                                                                                    \
		vTaskNotifyGiveFromISR(pxCircularBufferRxState->task_to_be_Notified ,&( xHigherPriorityTaskWoken ) );           \
	}																													\
}
#endif

#if 0
//aaa-zzz
#define ioutilsTRANSMIT_TO_TASKNOTIFICATION_CIRCULAR_BUFFER( pxPeripheralControl, xPeripheralDisable, xPeripheralEnable, pucBuffer, \
 xBytes, xBytesSent )	\
{																														\
portTickType xTicksToWait;																								\
xTimeOutType xTimeOut;                                                                                                  \
unsigned int xbytesWritten=0;																								    \
TaskNotification_Circular_Buffer_State_t *pxCircularBufferState = prvTaskNotificationTxCIRCULAR_BUFFER_STATE( pxPeripheralControl );	\
																														\
	( xBytesSent ) = 0U;									         													\
	xTicksToWait = pxCircularBufferState->xBlockTime;																	\
	vTaskSetTimeOutState( &xTimeOut );																					\
	pxCircularBufferState->task_to_be_Notified = xTaskGetCurrentTaskHandle();								            \
	/* Are there any more bytes to be sent? */									     									\
	while( ( xBytesSent ) < xBytes )												     								\
	{                                                                                                                   \
		xbytesWritten = 0;                                                                                          \
		( xPeripheralDisable ); 																					\
        xbytesWritten = xIOUtilsWriteCharsintoTaskNotificationCircularBuffer( pxCircularBufferState, &( ( pucBuffer ) [ ( xBytesSent ) ] ), xBytes - ( xBytesSent ) ); \
		( xPeripheralEnable );                                                                                      \
        if( xbytesWritten >0 )                                                                                      \
        {                                                                                                           \
           if(ulTaskNotifyTake( pdTRUE, portMAX_DELAY !=0) )                                                       \
           ( xBytesSent ) += xbytesWritten;   																		\
        }                                                                                                        \
		if( xTaskCheckForTimeOut( &xTimeOut, &xTicksToWait ) != pdFALSE )												\
		{																												\
			/* Time out has expired. */																					\
			break;																										\
		}																												\
	}																													\
}
#endif




#define ioutilsTX_CHARS_OF_TASKNOTIFICATION_CIRCULAR_BUFFER_FROM_ISR( pxTransferControl, xCondition, xTransmitFunction, \
ultransmitted,xHigherPriorityTaskWoken )	                                                                            \
{																														\
TaskNotification_Circular_Buffer_State_t* const pxCircularBufferTxState = ( TaskNotification_Circular_Buffer_State_t * ) ( ( pxTransferControl )->pvTransferState );	\
uint16_t *pusNextRead;																								    \
uint8_t ucChar;		                                                                                                    \
																														\
	pusNextRead = &( pxCircularBufferTxState->usNextReadIndex );														\
	while( ( xCondition ) )	/* Fill FIFO until it is above- TX-FIFO-Trigger level: Minimum No.of spaces allowed */      \
	{																													\
		/* If there is data in the circular buffer. */																	\
		if( pxCircularBufferTxState->usCharCount > 0 )							                                        \
		{																												\
			ucChar = pxCircularBufferTxState->pucBufferStart[ *pusNextRead];                                            \
           /* (pxCircularBufferTxState->pucBufferStart)++;  */                                                              \
            ( xTransmitFunction );	            																		\
			ultransmitted++;																							\
			( pxCircularBufferTxState->usCharCount )--;																	\
																														\
			/* Move on to the next index, wrapping if necessary. */														\
			( *pusNextRead )++;					              															\
			if( *pusNextRead == pxCircularBufferTxState->usBufferLength )												\
			{																											\
				*pusNextRead = 0U;																						\
			}																											\
		}																												\
		else  /* no data in task notif Circular-buff */																											\
		{                                                                                                               \
           	if( ultransmitted > 0UL )																			        \
           	{																									     	\
          		/* Unblock any tasks that might have been waiting for new data to arrive.*/                             \
                vTaskNotifyGiveFromISR(pxCircularBufferTxState->task_to_be_Notified ,&( xHigherPriorityTaskWoken ) );   \
                break;                                                                                                  \
            }                                                                                                           \
    	}																												\
	}																													\
																								                        \
}



void vIOUtilsClearTaskNotificationCircularBuffer( Peripheral_Control_t * const pxPeripheralControl );


