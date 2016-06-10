/*
    FreeRTOS V7.3.0 - Copyright (C) 2012 Real Time Engineers Ltd.


    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

//
//
//lecture - refer to the mentioned web documentation - these are the best documentation for
//          this specific purpose ???
//
//
/******************************************************************************
 * The FreeRTOS+IO and FreeRTOS+CLI features mentioned in these comments are
 * documented on the following two URLs:
 * http://www.FreeRTOS.org/FreeRTOS-Plus/FreeRTOS_Plus_IO/
 * http://www.FreeRTOS.org/FreeRTOS-Plus/FreeRTOS_Plus_CLI/
 *
 * It is essential that jumpers are set correctly.  The required jumper
 * settings are pictured on the documentation page for this demo, which
 * can be located from the following URL:
 * http://www.FreeRTOS.org/FreeRTOS-Plus/FreeRTOS_Plus_IO/Featured-FreeRTOS_Plus_IO_Demos.shtml
 ******************************************************************************
 *
 * This demo provides the following functionality:
 *
 * --- Command Console ---
 * FreeRTOS+IO and FreeRTOS+CLI are used to create a command console. UART3 is
 * used for input and output.
 *
 * The FreeRTOS+IO zero copy transfer mode is used to transmit characters, and
 * the interrupt driven character queue transfer mode is used to receive
 * characters.
 *
 * The application registers the following commands:
 *
 *	+ "echo-parameters".  This command accepts a variable number of parameters.
 *    Each parameter entered is echoed back individually.
 *
 *	+ "echo-three-parameters".  This command is similar to "echo-parameters",
 *    but will only accept exactly three parameters.
 *
 *  + "task-stats".  This command displays a table that includes a line for each
 *    executing task.  The table displays information including the task state,
 *    and the task's stack high water mark.  (the closer the stack high water
 *    mark value is to zero the closer the task has come to overflowing its
 *    stack).
 *
 *	+ "run-time-stats".  This command also displays a table that also includes
 *    a line for each executing task.  This time the table displays the amount
 *    of time each task has spent in the "Running" state (actually executing).
 *    Both absolute and percentage times are shown.  See
 *    http://www.freertos.org/rtos-run-time-stats.html
 *
 *	+ "create-task".  This command takes a single numerical parameter.  It
 *     creates a new task and passes the command line parameter into the task as
 *     the task parameter.  The task that is created displays the parameter value
 *     on the command console.  The "task-stats" command can be used both before
 *     and after executing the "create-task" command to see the newly created
 *	   task appear in the table of running tasks.
 *
 *	+ "delete-task".  This command deletes the task that was created by the
 *    "create-task" command.
 *
 //lecture - is it a micro-usb or mini-usb connector ??? refer to board | schematics | user-manual
 //
 *
 *
 * By default, UART3 is set to 115200 baud, no start bits, 8 data bits and 1
 * stop bit. UART3 is routed, via a UART to USB converter, to the micro USB
 * connector marked X3 on the LPCXpresso base board.
 *
 //lecture - I2C2 bus (second I2C bus) is used for the OLED display - we need to get the
 //          I2C bus address
 //          of the OLED peripheral - refer to board | schematics | user-manual
 //
 //lecture - I2C2 bus (second I2C bus) is also used for EEPROM interface
 //
 //
 //lecture - we must check the configuration used for Write and Read - if required, we must
 //          modify the configuration settings and test the code ???
 //
 * --- Display Driver ---
 * FreeRTOS+IO is used to implement a display driver for the OLED display.
 * The OLED is configured for I2C operation, and uses the I2C2 peripheral.
 *
 * The example demonstrates the I2C port being used in the polled and
 * interrupt driven zero copy transfer modes.
 *
 * --- Serial EEPROM Interface ---
 * FreeRTOS+IO is used to write to, then read back from, an EEPROM that is
 * connected to the I2C2 peripheral.
 *
 * The example demonstrates the I2C port being used in the polled and interrupt
 * driven zero copy transfer modes to write to the EEPROM, and the polled and
 * interrupt driven circular buffer transfer modes to read back from the
 * EEPROM.
 *
 //
 //lecture - we must check the configuration and how it is done, in this case ??
 //
 //
 * --- 7-Segment Display ---
 * FreeRTOS+IO is used with an SPI peripheral in the polled transfer mode to
 * periodically write an incrementing number to a 7-segment	display.
 *
 //
 //lecture - we must see the how the LEDs are set-up and managed, in the hw and
 //          sw ???
 //
 * --- GPIO ---
 * FreeRTOS software timers are used to periodically toggle the multi-coloured
 * LEDs.
 */
//
//
//lecture - initially, just get a basic grip  -  once done, explore and comment every aspect
//          of the code ???
//
//
//
//
/* Standard includes. */

#include <string.h>

//
//
//FREERTOS headers
//
//

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include <basic_io.h> //aaa-zzz
//
//application specific headers ???
//
//
/* Example includes. */
#include "GPIO-output-and-software-timers.h"
#include "UART-interrupt-driven-command-console.h"
#include "UART-operation-modes-test.h"
#include "SPI-writes-to-7-seg-display.h"
#include "I2C-coordinator.h"
#include "FreeRTOS_CLI.h"

//#include "I2C-coordinator.h"  //aaa-zzz

extern  void prvI2CTask( void *pvParameters ); //aaa-zzz

/* Library includes. */
// #include "LPC17xx.h"  //aaa-zzz
#include "board.h"  //aaa-zzz  - for core_cm3.h (NVIC_SetPriorityGrouping)

//aaa-zzz

/* Misc constants. */
#define mainDONT_BLOCK					( 0 )

/* Definitions for the messages that can be sent to the check task. */
#define mainREG_TEST_1_STILL_EXECUTING	( 0 )
#define mainREG_TEST_2_STILL_EXECUTING	( 1 )
#define mainPRINT_SYSTEM_STATUS			( 2 )

/* GCC specifics. */
#define mainALIGN_TO( x )				__attribute__((aligned(x)))
//aaa-zzz

/* Hardware specifics.  The start and end address are chosen to ensure the
required GPIO are covered while also ensuring the necessary alignment is
achieved. */
#define mainGPIO_START_ADDRESS			( ( unsigned long * ) 0x2009c000 )
#define mainGPIO_END_ADDRESS			( mainGPIO_START_ADDRESS + ( 64 * 1024 ) )


/* The CLI commands are defined in CLI-commands.c. */
void vRegisterCLICommands( void );

/*-----------------------------------------------------------*/
//
//
//lecture - may need to modify this for our work ??? better resolution may be needed ???
//
//
/* Used in the run time stats calculations. */
static uint32_t ulClocksPer10thOfAMilliSecond = 0UL;

//aaa-zzz
/*-----------------------------------------------------------------------------------------------------------------------------------------------
 * -------------changes for UART+MPU code--------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------------------------------*/
/*FreeRTOS+IO includes */
#include "FreeRTOS_IO.h"  //aaa-zzz


/*handler for UART open */


static Peripheral_Descriptor_t xTestUART;



/*messages needed to be passed to check states */
static const unsigned char * msg = "system failed due to memory violation \r\n";
static const int8_t * const pcTestMessage1 = ( int8_t * ) "Check task is executing \r\n";
static const int8_t * const pcTestMessage2 = ( int8_t * ) "Regular Task 1 is executing \r\n\n";
static const int8_t * const pcTestMessage3 = ( int8_t * ) "Regular Task 2 is executing \r\n\n";
static const int8_t * const pcTestMessage4 = ( int8_t * ) "this is unprivileged task 1 is started . . .\r\n";
static const int8_t * const pcTestMessage5 = ( int8_t * ) "this is unprivileged task 1 is running . . .\r\n";

/*
 * Performs a similar function to prvCheckTestResult().  configASSERT() itself
 * has to be undefined in order to run through some of these scenarios.
 */
static void prvCheckTestResult( portBASE_TYPE xTestCondition, portBASE_TYPE xLine );




/*-----------------------------------------------------------*/
/* Prototypes for functions that implement tasks. -----------*/
/*-----------------------------------------------------------*/
/*
 * Prototype for the reg test tasks.  Amongst other things, these fill the CPU
 * registers with known values before checking that the registers still contain
 * the expected values.  Each of the two tasks use different values so an error
 * in the context switch mechanism can be caught.  Both reg test tasks execute
 * at the idle priority so will get preempted regularly.  Each task repeatedly
 * sends a message on a queue so long as it remains functioning correctly.  If
 * an error is detected within the task the task is simply deleted.
 */
static void prvRegTest1Task( void *pvParameters );
//static void prvRegTest2Task( void *pvParameters );

/*
 * Prototype for the check task.  The check task demonstrates various features
 * of the MPU before entering a loop where it waits for messages to arrive on a
 * queue.
 *
 * Two types of messages can be processes:
 *
 * 1) "I'm Alive" messages sent from the reg test tasks, indicating that the
 *    task is still operational.
 *
 * 2) "Print Status commands" sent periodically by the tick hook function (and
 *    therefore from within an interrupt) which command the check task to write
 *    either pass or fail to the terminal, depending on the status of the reg
 *    test tasks.
 */

static void prvCheckTask( void *pvParameters );

/*
 * Prototype for a task created in User mode using the original vTaskCreate()
 * API function.  The task demonstrates the characteristics of such a task,
 * before simply deleting itself.
 */
//static void prvOldStyleUserModeTask( void *pvParameters );

/*
 * Prototype for a task created in Privileged mode using the original
 * vTaskCreate() API function.  The task demonstrates the characteristics of
 * such a task, before simply deleting itself.
 */
//static void prvOldStylePrivilegedModeTask( void *pvParameters );


/*-----------------------------------------------------------*/
/* Prototypes for other misc functions.  --------------------*/
/*-----------------------------------------------------------*/

/*
 * Just configures any clocks and IO necessary.
 */
//static void prvSetupHardware( void );

/*
 * Simply deletes the calling task.  The function is provided only because it
 * is simpler to call from asm code than the normal vTaskDelete() API function.
 * It has the noinline attribute because it is called from asm code.
 */
static void prvDeleteMe( void ) __attribute__((noinline));

/*
 * Used by both reg test tasks to send messages to the check task.  The message
 * just lets the check task know that the task is still functioning correctly.
 * If a reg test task detects an error it will delete itself, and in so doing
 * prevent itself from sending any more 'I'm Alive' messages to the check task.
 */
static void prvSendImAlive( xQueueHandle xHandle, unsigned long ulTaskNumber );

/*
 * The check task is created with access to three memory regions (plus its
 * stack).  Each memory region is configured with different parameters and
 * prvTestMemoryRegions() demonstrates what can and cannot be accessed for each
 * region.  prvTestMemoryRegions() also demonstrates a task that was created
 * as a privileged task settings its own privilege level down to that of a user
 * task.
 */
//static void prvTestMemoryRegions( void );

/*-----------------------------------------------------------*/

/* The handle of the queue used to communicate between tasks and between tasks
and interrupts.  Note that this is a file scope variable that falls outside of
any MPU region.  As such other techniques have to be used to allow the tasks
to gain access to the queue.  See the comments in the tasks themselves for
further information. */
static xQueueHandle xFileScopeCheckQueue = NULL;



/*-----------------------------------------------------------*/
/* Data used by the 'check' task. ---------------------------*/
/*-----------------------------------------------------------*/

/* Define the constants used to allocate the check task stack.  Note that the
stack size is defined in words, not bytes. */
#define mainCHECK_TASK_STACK_SIZE_WORDS	128
#define mainCHECK_TASK_STACK_ALIGNMENT ( mainCHECK_TASK_STACK_SIZE_WORDS * sizeof( portSTACK_TYPE ) )

/* Declare the stack that will be used by the check task.  The kernel will
 automatically create an MPU region for the stack.  The stack alignment must
 match its size, so if 128 words are reserved for the stack then it must be
 aligned to ( 128 * 4 ) bytes. */
static portSTACK_TYPE xCheckTaskStack[ mainCHECK_TASK_STACK_SIZE_WORDS ] mainALIGN_TO( mainCHECK_TASK_STACK_ALIGNMENT );

/* Declare three arrays - an MPU region will be created for each array
using the xTaskParameters structure below.  THIS IS JUST TO DEMONSTRATE THE
MPU FUNCTIONALITY, the data is not used by the check tasks primary function
of monitoring the reg test tasks and printing out status information.

Note that the arrays allocate slightly more RAM than is actually assigned to
the MPU region.  This is to permit writes off the end of the array to be
detected even when the arrays are placed in adjacent memory locations (with no
gaps between them).  The align size must be a power of two. */
#define mainREAD_WRITE_ARRAY_SIZE 130
#define mainREAD_WRITE_ALIGN_SIZE 128
char cReadWriteArray[ mainREAD_WRITE_ARRAY_SIZE ] mainALIGN_TO( mainREAD_WRITE_ALIGN_SIZE );

#define mainREAD_ONLY_ARRAY_SIZE 260
#define mainREAD_ONLY_ALIGN_SIZE 256
char cReadOnlyArray[ mainREAD_ONLY_ARRAY_SIZE ] mainALIGN_TO( mainREAD_ONLY_ALIGN_SIZE );

#define mainPRIVILEGED_ONLY_ACCESS_ARRAY_SIZE 130
#define mainPRIVILEGED_ONLY_ACCESS_ALIGN_SIZE 128
char cPrivilegedOnlyAccessArray[ mainPRIVILEGED_ONLY_ACCESS_ALIGN_SIZE ] mainALIGN_TO( mainPRIVILEGED_ONLY_ACCESS_ALIGN_SIZE );



//aaa-zzz

static const uint8_t pcStringOfDigits[] = { 0x24, /* 0 */	0xAF, /* 1 */ 0xE0, /* 2 */	0xA2, /* 3 */ 0x2B, /* 4 */	0x32, /* 5 */ 0x30, /* 6 */	0xA7, /* 7 */ 0x20, /* 8 */	0x22 };


#define mainREG_TEST_STACK_SIZE_WORDS	128

#define mainREG_TEST_STACK_ALIGNMENT	( mainREG_TEST_STACK_SIZE_WORDS * sizeof( portSTACK_TYPE ) )


static portSTACK_TYPE xRegTest1Stack[ mainREG_TEST_STACK_SIZE_WORDS ] mainALIGN_TO( mainREG_TEST_STACK_ALIGNMENT );
static portSTACK_TYPE xRegTest2Stack[ mainREG_TEST_STACK_SIZE_WORDS ] mainALIGN_TO( mainREG_TEST_STACK_ALIGNMENT );


static void prvRegTest1Task( void *pvParameters );
static void prvRegTest2Task( void *pvParameters );


/* Fill in a xTaskParameters structure per reg test task to define the tasks. */
static volatile xTaskParameters xRegTest1Parameters =
{
	prvRegTest1Task,						/* pvTaskCode - the function that implements the task. */
	( signed char * ) "RegTest1",			/* pcName			*/
	mainREG_TEST_STACK_SIZE_WORDS,			/* usStackDepth		*/
	( void * ) 0x12345678,					/* pvParameters - this value is just to test that the parameter is being passed into the task correctly. */
	tskIDLE_PRIORITY | portPRIVILEGE_BIT,	/* uxPriority - note that this task is created with privileges to demonstrate one method of passing a queue handle into the task. */
	xRegTest1Stack,							/* puxStackBuffer - the array to use as the task stack, as declared above. */
	{										/* xRegions - this task does not use any non-stack data hence all members are zero. */
		/* Base address		Length		Parameters */
		{ 0x00,				0x00,			0x00 },
		{ 0x00,				0x00,			0x00 },
		{ 0x00,				0x00,			0x00 }
	}
};
/*-----------------------------------------------------------*/

#if 1

static xTaskParameters xRegTest2Parameters =
{
	prvRegTest2Task,				/* pvTaskCode - the function that implements the task. */
	( signed char * ) "RegTest2",	/* pcName			*/
	mainREG_TEST_STACK_SIZE_WORDS,	/* usStackDepth		*/
	( void * ) NULL,				/* pvParameters	- this task uses the parameter to pass in a queue handle, but the queue is not created yet. */
	tskIDLE_PRIORITY | portPRIVILEGE_BIT,				/* uxPriority		*/
	xRegTest2Stack,					/* puxStackBuffer - the array to use as the task stack, as declared above. */
	{								/* xRegions - this task does not use any non-stack data hence all members are zero. */
		/* Base address		Length		Parameters */
		{mainGPIO_START_ADDRESS,	( 64 * 1024 ),	portMPU_REGION_READ_WRITE},/* this to check its privileged data access in unprivileged function */
		{ 0x00,				0x00,			0x00 },
        { 0x00,				0x00,			0x00 },
	}
};



/* Fill in a xTaskParameters structure to define the check task - this is the
structure passed to the xTaskCreateRestricted() function. */
static const xTaskParameters xCheckTaskParameters =
{
	prvCheckTask,								/* pvTaskCode - the function that implements the task. */
	( signed char * ) "Check",					/* pcName			*/
	mainCHECK_TASK_STACK_SIZE_WORDS,			/* usStackDepth	- defined in words, not bytes. */
	( void * ) 0x12121212,						/* pvParameters - this value is just to test that the parameter is being passed into the task correctly. */
	( tskIDLE_PRIORITY + 1 ) | portPRIVILEGE_BIT,/* uxPriority - this is the highest priority task in the system.  The task is created in privileged mode to demonstrate accessing the privileged only data. */
	xCheckTaskStack,							/* puxStackBuffer - the array to use as the task stack, as declared above. */

	/* xRegions - In this case the xRegions array is used to create MPU regions
	for all three of the arrays declared directly above.  Each MPU region is
	created with different parameters.  Again, THIS IS JUST TO DEMONSTRATE THE
	MPU FUNCTIONALITY, the data is not used by the check tasks primary function
	of monitoring the reg test tasks and printing out status information.*/
	{
		/* Base address					Length									Parameters */
        { cReadWriteArray,				mainREAD_WRITE_ALIGN_SIZE,				portMPU_REGION_READ_WRITE },
  //      { cReadOnlyArray,				mainREAD_ONLY_ALIGN_SIZE,				portMPU_REGION_READ_ONLY },
  //      { cPrivilegedOnlyAccessArray,	mainPRIVILEGED_ONLY_ACCESS_ALIGN_SIZE,	portMPU_REGION_PRIVILEGED_READ_WRITE }
        {0,0,0},
        {0,0,0}
	}
};


#endif


static volatile xTaskParameters I2C_EEPROM_taskParameters =
{
	prvI2CTask,						/* pvTaskCode - the function that implements the task. */
	//( signed char * ) "RegTest1",			 pcName
	( const int8_t * const ) "I2CO",
	configI2C_TASK_STACK_SIZE,			/* usStackDepth		*/
	( void * ) 0x12345678,					/* pvParameters - this value is just to test that the parameter is being passed into the task correctly. */
	configI2C_TASK_PRIORITY | portPRIVILEGE_BIT,	/* uxPriority - note that this task is created with privileges to demonstrate one method of passing a queue handle into the task. */
	NULL,							/* puxStackBuffer - the array to use as the task stack, as declared above. */
	{										/* xRegions - this task does not use any non-stack data hence all members are zero. */
		/* Base address		Length		Parameters */
		{ 0x00,				0x00,			0x00 },
		{ 0x00,				0x00,			0x00 },
		{ 0x00,				0x00,			0x00 }
	}
};



static portTickType xLastExecutionTime;

/*-----------------------------------------------------------*/

int main( void )
{

	const char *pcTaskName = "i2c Task will run\n";

	printf("\n");
	printf("hello\n");
	//
	//lecture - need to refer to CMSIS code, lpc17xx reference manual and def. guide to
	//          CM3/CM4 - explore more on this ???
	//
	/* The examples assume that all priority bits are assigned as preemption
	priority bits. */
	NVIC_SetPriorityGrouping( 0UL );  //aaa-zzz
    //
	//
	//lecture - sw timers are being started for GPIO functionality - explore and add comments ??
	//
	//
	/* Start the timers that demonstrate FreeRTOS software timers and basic
	GPIO functionality. */
//	vGPIOSoftwareTimersStart();  //aaa-zzz
    //
    //
	//
	//
	//lecture - uart - this method is invoked to create a task that will manage command console
	//                 on UART3(??) - move into UART/UART-interrupt-driven-command-console.c -
	//                 more comments are added there
	//
	//
	/* Start the tasks that implements the command console on the UART, as
	described above. */
	vUARTCommandConsoleStart();

	//vUARTOperationModeTestsStart(); //aaa-zzz


	//
	//
	//lecture - registration is based on the understanding of the CLI implementation ???
	//          not really part of freertos+IO - used here for demontration purposes only ???
	//
	//
	/* Register two command line commands to show task stats and run time stats
	respectively. */
	//vRegisterCLICommands();



    //
	//
	//
	//lecture - another task that manages SPI port for 7 segment display - move into
	//          SPI-writes-to-7-seg-display.c for code and comments
	//
	//
	/* Start the task that demonstrates the SSP port being used in SPI mode to
	write to the 7 segment display. */
//vSPIWriteTaskStart();   //aaa-zzz

	vPrintString(pcTaskName); //aaa-zzz  ---semi hosting

//	DEBUGSTR("asdf");//aaa-zzz  ----> BOARD_UART
//	vPrintStringAndNumber("i2cTask\n");
	vPrintString("i2cTask\n");
    //
	//
	//lecture - the task that enables to manage OLED and EEPROM -
	//          refer to code under Examples/I2C - start with I2C-coordinator.c
	//
	//
	//lecture - i2c-eeprom - this is where the i2c related set-up starts
	//          i2c-eeprom - refer to i2c-coordinator.c for more details and code
	//
	//
	/* Start the task that uses an I2C peripheral to communicate with the
	OLED and the EEPROM. */

//	vI2CTaskStart();


	//xTaskCreateRestricted( &I2C_EEPROM_taskParameters, NULL );


	//aaa-zzz
#if 0

	xTestUART = FreeRTOS_open( boardCOMMAND_CONSOLE_UART, ( uint32_t ) ( (void *) 0 ) );
	prvCheckTestResult( ( xTestUART != NULL ), __LINE__ );



//	xRegTest1Parameters.pvParameters = (unsigned long * ) xTestUART;

	/* Create the queue used to pass "I'm alive" messages to the check task. */
		xFileScopeCheckQueue = xQueueCreate( 1, sizeof( unsigned long ) );

//    xTaskCreateRestricted( &xRegTest1Parameters, NULL );
//	xTaskCreateRestricted( &xRegTest2Parameters, NULL );
//	xTaskCreateRestricted( &xCheckTaskParameters, NULL );
#endif

    //
	//
	//
	//lecture - eventually, invoke the scheduler - control is passed to FreeRTOS and
	//          tasks are managed as per the FreeRTOS scheduler
	//
	//
	/* Start the FreeRTOS scheduler. */
	vTaskStartScheduler();

	/* The following line should never execute.  If it does, it means there was
	insufficient FreeRTOS heap memory available to create the Idle and/or timer
	tasks.  See the memory management section on the http://www.FreeRTOS.org web
	site for more information. */
	for( ;; );
}
/*-----------------------------------------------------------*/
//
//
//lecture - some timer issues are handled here ?? we must explore more on this ??
//
//
//
//
void vMainConfigureTimerForRunTimeStats( void )
{
	/* How many clocks are there per tenth of a millisecond? */
	ulClocksPer10thOfAMilliSecond = configCPU_CLOCK_HZ / 10000UL;
}
/*-----------------------------------------------------------*/
//
//
//
//lecture - in this example, systick is being used - first understand, how it is used -
//          replace it with additional hw timer ??? refer to my lpc17xx book code !!!
//
//
//
//
uint32_t ulMainGetRunTimeCounterValue( void )
{
uint32_t ulSysTickCounts, ulTickCount, ulReturn;
const uint32_t ulSysTickReloadValue = ( configCPU_CLOCK_HZ / configTICK_RATE_HZ ) - 1UL;
volatile uint32_t * const pulCurrentSysTickCount = ( ( volatile uint32_t *) 0xe000e018 );
volatile uint32_t * const pulInterruptCTRLState = ( ( volatile uint32_t *) 0xe000ed04 );
const uint32_t ulSysTickPendingBit = 0x04000000UL;

	/* NOTE: There are potentially race conditions here.  However, it is used
	anyway to keep the examples simple, and to avoid reliance on a separate
	timer peripheral. */


	/* The SysTick is a down counter.  How many clocks have passed since it was
	last reloaded? */
	ulSysTickCounts = ulSysTickReloadValue - *pulCurrentSysTickCount;

	/* How many times has it overflowed? */
	ulTickCount = xTaskGetTickCountFromISR();

	/* Is there a SysTick interrupt pending? */
	if( ( *pulInterruptCTRLState & ulSysTickPendingBit ) != 0UL )
	{
		/* There is a SysTick interrupt pending, so the SysTick has overflowed
		but the tick count not yet incremented. */
		ulTickCount++;

		/* Read the SysTick again, as the overflow might have occurred since
		it was read last. */
		ulSysTickCounts = ulSysTickReloadValue - *pulCurrentSysTickCount;
	}

	/* Convert the tick count into tenths of a millisecond.  THIS ASSUMES
	configTICK_RATE_HZ is 1000! */
	ulReturn = ( ulTickCount * 10UL ) ;

	/* Add on the number of tenths of a millisecond that have passed since the
	tick count last got updated. */
	ulReturn += ( ulSysTickCounts / ulClocksPer10thOfAMilliSecond );

	return ulReturn;
}



static void prvRegTest1Task( void *pvParameters )
{
/* This task is created in privileged mode so can access the file scope
queue variable.  Take a stack copy of this before the task is set into user
mode.  Once this task is in user mode the file scope queue variable will no
longer be accessible but the stack copy will. */


xQueueHandle xQueue = xFileScopeCheckQueue;
portBASE_TYPE xReturned;
//const portTickType xTaskPeriod_ms = 1000UL / portTICK_RATE_MS;
//const portTickType xTaskPeriod_ms = 100UL / portTICK_RATE_MS; //aaa-zzz
const portTickType xTaskPeriod_ms = 10UL / portTICK_RATE_MS;
portTickType xLastExeTime = xLastExecutionTime;

unsigned long *uart_handler mainALIGN_TO( 64 )= pvParameters ;


/*
 * here to check how the regions for this task are been stored in the MPU registers.
 * we check each MPU regions one by one.
 */


#define portMPU_REGION_BASE_ADDRESS				( ( volatile uint32_t * ) 0xe000ed9C )
#define portMPU_REGION_ATTRIBUTE				( ( volatile uint32_t * ) 0xe000edA0 )
#define portMPU_CTRL							( ( volatile uint32_t * ) 0xe000ed94 )
#define portMPU_REGION_NUMBER_REGESTER			( ( volatile uint32_t * ) 0xe000ed98 )

*portMPU_REGION_NUMBER_REGESTER = 0x0;
unsigned int reg0 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr0 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x1;
unsigned int reg1 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr1 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x2;
unsigned int reg2 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr2 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x3;
unsigned int reg3 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr3 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x4;
unsigned int reg4 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr4 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x5;
unsigned int reg5 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr5 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x6;
unsigned int reg6 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr6 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x7;
unsigned int reg7 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr7 = *portMPU_REGION_ATTRIBUTE;

/*to check if this unprivilaged function is allowed to accesss all the data which it wants to except its range . . . . . . . . . . . . . . */
//char a = cPrivilegedOnlyAccessArray[1];

	/* Now the queue handle has been obtained the task can switch to user
	mode.  This is just one method of passing a handle into a protected
	task, the other	reg test task uses the task parameter instead. */


portSWITCH_TO_USER_MODE();
//vTaskAllocateMPURegions( NULL, xAltRegions3);


xReturned = FreeRTOS_write( uart_handler, pcTestMessage4, strlen( ( char * ) pcTestMessage4 ) );
prvCheckTestResult( ( xReturned == ( portBASE_TYPE ) strlen( ( char * ) pcTestMessage4 ) ), __LINE__ );


/*to check if this unprivilaged function is allowed to accesss all the data which it wants to except its range . . . . . . . . . . . . . . */
//a = cReadOnlyArray[1];

for(;;)
{
    //printf("task1-usermode-send Alive Msg\n");


	xReturned = FreeRTOS_write( uart_handler, pcTestMessage5, strlen( ( char * ) pcTestMessage5 ) );
	prvCheckTestResult( ( xReturned == ( portBASE_TYPE ) strlen( ( char * ) pcTestMessage5 ) ), __LINE__ );

	prvSendImAlive( xQueue, mainREG_TEST_1_STILL_EXECUTING );

	//vTaskDelayUntil( &xLastExeTime, xTaskPeriod_ms );
	vTaskDelayUntil( &xLastExeTime, xTaskPeriod_ms ); //aaa-zzz
}

}
/*-----------------------------------------------------------*/

#if 1
static void prvRegTest2Task( void *pvParameters )
{
int8_t cRxedChar;
portBASE_TYPE xReturned;
/* The queue handle is passed in as the task parameter.  This is one method of
passing data into a protected task, the other reg test task uses a different
method. */

unsigned long *spi_handler= pvParameters;

xQueueHandle xQueue = xFileScopeCheckQueue;
uint8_t ucChar ;
const uint8_t ucMaxChar = 10U;
const portTickType xTaskPeriod_ms = 100UL / portTICK_RATE_MS;
portTickType xLastExeTime = xLastExecutionTime;


//portSWITCH_TO_USER_MODE();
unsigned int i=0;

for(;;)
{
		/* Send down a character at a time, using polling mode Tx. */
		//for( ucChar = 0; ucChar < ucMaxChar; ucChar++ )
		{
			/* Delay until it is time to update the display with a new digit. */

		//	board7SEG_ASSERT_CS();
			//FreeRTOS_write( pvParameters, &( pcStringOfDigits[ ucChar ] ), sizeof( uint8_t ) );
//			board7SEG_DEASSERT_CS();
		//	printf("sending Alive-Msg\r\n");
			prvSendImAlive( xQueue, mainREG_TEST_2_STILL_EXECUTING );
			vTaskDelayUntil( &xLastExeTime, xTaskPeriod_ms );

		}

}

}

#endif


static void prvCheckTask( void *pvParameters )
{
/* This task is created in privileged mode so can access the file scope
queue variable.  Take a stack copy of this before the task is set into user
mode.  Once that task is in user mode the file scope queue variable will no
longer be accessible but the stack copy will. */

unsigned long *Check_UART = xTestUART;
portBASE_TYPE xReturned;

xQueueHandle xQueue = xFileScopeCheckQueue;
long lMessage;
unsigned long ulStillAliveCounts[ 2 ] = { 0 };
char *pcStatusMessage = "PASS\r\n";
//unsigned char x = 5, y = 10;


	/* Just to remove compiler warning. */
	( void ) pvParameters;

/*
 * here to check how the regions for this task are been stored in the MPU registers.
 * we check each MPU regions one by one.
 */

#define portMPU_REGION_BASE_ADDRESS				( ( volatile uint32_t * ) 0xe000ed9C )
#define portMPU_REGION_ATTRIBUTE				( ( volatile uint32_t * ) 0xe000edA0 )
#define portMPU_CTRL							( ( volatile uint32_t * ) 0xe000ed94 )
#define portMPU_REGION_NUMBER_REGESTER			( ( volatile uint32_t * ) 0xe000ed98 )

*portMPU_REGION_NUMBER_REGESTER = 0x0;
unsigned int reg0 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr0 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x1;
unsigned int reg1 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr1 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x2;
unsigned int reg2 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr2 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x3;
unsigned int reg3 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr3 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x4;
unsigned int reg4 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr4 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x5;
unsigned int reg5 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr5 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x6;
unsigned int reg6 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr6 = *portMPU_REGION_ATTRIBUTE;

*portMPU_REGION_NUMBER_REGESTER = 0x7;
unsigned int reg7 = *portMPU_REGION_BASE_ADDRESS;
unsigned int atr7 = *portMPU_REGION_ATTRIBUTE;

	/* Demonstrate how the various memory regions can and can't be accessed.
	The task privilege is set down to user mode within this function. */
//	prvTestMemoryRegions();


//	portSWITCH_TO_USER_MODE();


	xReturned =FreeRTOS_write( Check_UART, pcTestMessage1, strlen( ( char * ) pcTestMessage1 ) );
	prvCheckTestResult( ( xReturned == ( portBASE_TYPE ) strlen( ( char * ) pcTestMessage1 ) ), __LINE__ );


	/* Change the memory regions allocated to this task to those initially
	set up for demonstration purposes to those actually required by the task. */
//	vTaskAllocateMPURegions( NULL, xAltRegions );



	/* This loop performs the main function of the task, which is blocking
	on a message queue then processing each message as it arrives. */
	for( ;; )
	{

		/* Wait for the next message to arrive. */
		xQueueReceive( xQueue, &lMessage, portMAX_DELAY );

		switch( lMessage )
		{
			case mainREG_TEST_1_STILL_EXECUTING	:
					/* Message from task 1, so task 1 must still be executing. */

//				xReturned =FreeRTOS_write( xTestUART, pcTestMessage2, strlen( ( char * ) pcTestMessage2 ) );
//				prvCheckTestResult( ( xReturned == ( portBASE_TYPE ) strlen( ( char * ) pcTestMessage2 ) ), __LINE__ );


					( ulStillAliveCounts[ 0 ] )++;

					xReturned = FreeRTOS_write( Check_UART, pcTestMessage2, strlen( ( char * ) pcTestMessage2 ) );
					prvCheckTestResult( ( xReturned == ( portBASE_TYPE ) strlen( ( char * ) pcTestMessage2 ) ), __LINE__ );

//					LCD_ClearScreen();
//					LCD_PrintString( x>>1, y>>1, pcStatusMessage, 6, COLOR_RED );
//					x += 7;
//					y += 9;

					break;

			case mainREG_TEST_2_STILL_EXECUTING	:
					/* Message from task 2, so task 2 must still be executing. */

//				xReturned =FreeRTOS_write( xTestUART, pcTestMessage3, strlen( ( char * ) pcTestMessage3 ) );
//				prvCheckTestResult( ( xReturned == ( portBASE_TYPE ) strlen( ( char * ) pcTestMessage3 ) ), __LINE__ );

					( ulStillAliveCounts[ 1 ] )++;

					xReturned = FreeRTOS_write( Check_UART, pcTestMessage3, strlen( ( char * ) pcTestMessage3 ) );
					prvCheckTestResult( ( xReturned == ( portBASE_TYPE ) strlen( ( char * ) pcTestMessage3 ) ), __LINE__ );


//					LCD_ClearScreen();
//					LCD_PrintString( x>>1, y>>1, pcStatusMessage, 6, COLOR_RED );
//					x += 7;
//					y += 9;

					break;

			case mainPRINT_SYSTEM_STATUS		:
					/* Message from tick hook, time to print out the system
					status.  If messages has stopped arriving from either reg
					test task then the status must be set to fail. */
					if( ( ulStillAliveCounts[ 0 ] == 0 ) || ( ulStillAliveCounts[ 1 ] == 0 )  )
					{
						/* One or both of the test tasks are no longer sending
						'still alive' messages. */
						pcStatusMessage = "FAIL\r\n";
					}

					/* Print a pass/fail message to the LCD - moving the
					message each time to provide feedback that the output
					is still being produced.  LCD_PrintString() accesses const
					data stored in flash, which all tasks are at liberty to do,
					and GPIO for which an MPU region has been set up for it. */
					xReturned =FreeRTOS_write( Check_UART, msg, strlen( ( char * ) msg ) );
					prvCheckTestResult( ( xReturned == ( portBASE_TYPE ) strlen( ( char * ) msg ) ), __LINE__ );

//					LCD_ClearScreen();
//					LCD_PrintString( x>>1, y>>1, pcStatusMessage, 6, COLOR_RED );
//					x += 7;
//					y += 9;

					/* Reset the count of 'still alive' messages. */
					memset( ulStillAliveCounts, 0x00, sizeof( ulStillAliveCounts ) );
					break;

		default :
					/* Something unexpected happened.  Delete this task so the
					error is apparent (no output will be displayed). */
					prvDeleteMe();
					break;
		}
	}
}


static void prvCheckTestResult( portBASE_TYPE xTestCondition, portBASE_TYPE xLine )
{
	/* If the test conditions indicates a failure, then just stop here so the
	line number can be inspected.  prvCheckTestResult() is not used in this
	case as some tests require configASSERT() to be undefined. */
	if( xTestCondition == 0 )
	{
		taskDISABLE_INTERRUPTS();
		for( ;; );
	}

	( void ) xLine;
}

static void prvDeleteMe( void )
{
	vTaskDelete( NULL );
}


static void prvSendImAlive( xQueueHandle xHandle, unsigned long ulTaskNumber )
{
	if( xHandle != NULL )
	{
		xQueueSend( xHandle, &ulTaskNumber, mainDONT_BLOCK );
	}
}




/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
;
	//printf("Idle\n");
}
