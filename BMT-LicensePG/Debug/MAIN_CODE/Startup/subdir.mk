################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../MAIN_CODE/Startup/startup_stm32f401retx.s 

OBJS += \
./MAIN_CODE/Startup/startup_stm32f401retx.o 

S_DEPS += \
./MAIN_CODE/Startup/startup_stm32f401retx.d 


# Each subdirectory must supply rules for building sources it contributes
MAIN_CODE/Startup/%.o: ../MAIN_CODE/Startup/%.s MAIN_CODE/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-MAIN_CODE-2f-Startup

clean-MAIN_CODE-2f-Startup:
	-$(RM) ./MAIN_CODE/Startup/startup_stm32f401retx.d ./MAIN_CODE/Startup/startup_stm32f401retx.o

.PHONY: clean-MAIN_CODE-2f-Startup

