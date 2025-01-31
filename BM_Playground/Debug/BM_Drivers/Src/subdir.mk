################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BM_Drivers/Src/F401RE_GPIO.c \
../BM_Drivers/Src/F401RE_RCC.c \
../BM_Drivers/Src/F401RE_TIMER.c 

OBJS += \
./BM_Drivers/Src/F401RE_GPIO.o \
./BM_Drivers/Src/F401RE_RCC.o \
./BM_Drivers/Src/F401RE_TIMER.o 

C_DEPS += \
./BM_Drivers/Src/F401RE_GPIO.d \
./BM_Drivers/Src/F401RE_RCC.d \
./BM_Drivers/Src/F401RE_TIMER.d 


# Each subdirectory must supply rules for building sources it contributes
BM_Drivers/Src/%.o BM_Drivers/Src/%.su BM_Drivers/Src/%.cyclo: ../BM_Drivers/Src/%.c BM_Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BM_Drivers-2f-Src

clean-BM_Drivers-2f-Src:
	-$(RM) ./BM_Drivers/Src/F401RE_GPIO.cyclo ./BM_Drivers/Src/F401RE_GPIO.d ./BM_Drivers/Src/F401RE_GPIO.o ./BM_Drivers/Src/F401RE_GPIO.su ./BM_Drivers/Src/F401RE_RCC.cyclo ./BM_Drivers/Src/F401RE_RCC.d ./BM_Drivers/Src/F401RE_RCC.o ./BM_Drivers/Src/F401RE_RCC.su ./BM_Drivers/Src/F401RE_TIMER.cyclo ./BM_Drivers/Src/F401RE_TIMER.d ./BM_Drivers/Src/F401RE_TIMER.o ./BM_Drivers/Src/F401RE_TIMER.su

.PHONY: clean-BM_Drivers-2f-Src

