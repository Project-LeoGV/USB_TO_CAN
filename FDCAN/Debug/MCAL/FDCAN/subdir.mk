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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G431RBTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-FDCAN

clean-MCAL-2f-FDCAN:
	-$(RM) ./MCAL/FDCAN/CAN_Program.d ./MCAL/FDCAN/CAN_Program.o ./MCAL/FDCAN/CAN_Program.su

.PHONY: clean-MCAL-2f-FDCAN

