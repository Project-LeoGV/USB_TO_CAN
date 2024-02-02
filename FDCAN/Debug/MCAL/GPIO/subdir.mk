################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/GPIO/GPIO_Program.c 

OBJS += \
./MCAL/GPIO/GPIO_Program.o 

C_DEPS += \
./MCAL/GPIO/GPIO_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/GPIO/%.o MCAL/GPIO/%.su: ../MCAL/GPIO/%.c MCAL/GPIO/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DSTM32G431RBTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCAL-2f-GPIO

clean-MCAL-2f-GPIO:
	-$(RM) ./MCAL/GPIO/GPIO_Program.d ./MCAL/GPIO/GPIO_Program.o ./MCAL/GPIO/GPIO_Program.su

.PHONY: clean-MCAL-2f-GPIO

