################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/FDCAN/CAN_Program.c 

OBJS += \
./MCAL/FDCAN/CAN_Program.o 

C_DEPS += \
./MCAL/FDCAN/CAN_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/FDCAN/%.o MCAL/FDCAN/%.su: ../MCAL/FDCAN/%.c MCAL/FDCAN/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../USB_Device/App -I../USB_Device/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-FDCAN

clean-MCAL-2f-FDCAN:
	-$(RM) ./MCAL/FDCAN/CAN_Program.d ./MCAL/FDCAN/CAN_Program.o ./MCAL/FDCAN/CAN_Program.su

.PHONY: clean-MCAL-2f-FDCAN

