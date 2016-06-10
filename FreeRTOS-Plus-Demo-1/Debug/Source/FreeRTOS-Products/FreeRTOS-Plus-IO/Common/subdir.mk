################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/FreeRTOS_DriverInterface.c \
../Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/FreeRTOS_IOUtils.c \
../Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_CharQueueTxAndRx.c \
../Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_CircularBufferRx.c \
../Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_TaskNotification_TxAndRx.c \
../Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_ZeroCopyTx.c 

OBJS += \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/FreeRTOS_DriverInterface.o \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/FreeRTOS_IOUtils.o \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_CharQueueTxAndRx.o \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_CircularBufferRx.o \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_TaskNotification_TxAndRx.o \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_ZeroCopyTx.o 

C_DEPS += \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/FreeRTOS_DriverInterface.d \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/FreeRTOS_IOUtils.d \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_CharQueueTxAndRx.d \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_CircularBufferRx.d \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_TaskNotification_TxAndRx.d \
./Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/IOUtils_ZeroCopyTx.d 


# Each subdirectory must supply rules for building sources it contributes
Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/%.o: ../Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_LPCOPEN -DCORE_M3 -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/Examples/Include" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-CLI" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-CLI" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/lpc_chip_175x_6x/inc" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Device/LPC17xx/SupportedBoards" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Include" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS/portable/GCC/ARM_CM3_MPU" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS/include" -I../CMSISv2p00_LPC17xx/inc -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -Wextra -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


