################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Examples/I2C/Copy\ of\ I2C-to-and-from-EEPROM.c \
../Source/Examples/I2C/I2C-coordinator.c \
../Source/Examples/I2C/font5x7.c 

OBJS += \
./Source/Examples/I2C/Copy\ of\ I2C-to-and-from-EEPROM.o \
./Source/Examples/I2C/I2C-coordinator.o \
./Source/Examples/I2C/font5x7.o 

C_DEPS += \
./Source/Examples/I2C/Copy\ of\ I2C-to-and-from-EEPROM.d \
./Source/Examples/I2C/I2C-coordinator.d \
./Source/Examples/I2C/font5x7.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Examples/I2C/Copy\ of\ I2C-to-and-from-EEPROM.o: ../Source/Examples/I2C/Copy\ of\ I2C-to-and-from-EEPROM.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_LPCOPEN -DCORE_M3 -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/Examples/Include" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-CLI" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-CLI" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/lpc_chip_175x_6x/inc" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Device/LPC17xx/SupportedBoards" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Include" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS/portable/GCC/ARM_CM3_MPU" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS/include" -I../CMSISv2p00_LPC17xx/inc -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -Wextra -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"Source/Examples/I2C/Copy of I2C-to-and-from-EEPROM.d" -MT"Source/Examples/I2C/Copy\ of\ I2C-to-and-from-EEPROM.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/Examples/I2C/%.o: ../Source/Examples/I2C/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__USE_LPCOPEN -DCORE_M3 -DDEBUG -D__CODE_RED -D__REDLIB__ -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/Examples/Include" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-CLI" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-CLI" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/lpc_chip_175x_6x/inc" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Device/LPC17xx/SupportedBoards" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS-Plus-IO/Include" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS/portable/GCC/ARM_CM3_MPU" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source" -I"/home/jaguar/Downloads/FreeRTOS_demos/Openthis-proj-with-lpcxpresso7.8/MPU_cmdLine/FreeRTOS-Plus-Demo-1/Source/FreeRTOS-Products/FreeRTOS/include" -I../CMSISv2p00_LPC17xx/inc -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -Wextra -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


