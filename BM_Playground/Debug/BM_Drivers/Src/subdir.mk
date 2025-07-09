################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BM_Drivers/Src/GPIO.c \
../BM_Drivers/Src/I2C.c \
../BM_Drivers/Src/MOVEMENT.c \
../BM_Drivers/Src/RCC.c \
../BM_Drivers/Src/TIMER.c 

OBJS += \
./BM_Drivers/Src/GPIO.o \
./BM_Drivers/Src/I2C.o \
./BM_Drivers/Src/MOVEMENT.o \
./BM_Drivers/Src/RCC.o \
./BM_Drivers/Src/TIMER.o 

C_DEPS += \
./BM_Drivers/Src/GPIO.d \
./BM_Drivers/Src/I2C.d \
./BM_Drivers/Src/MOVEMENT.d \
./BM_Drivers/Src/RCC.d \
./BM_Drivers/Src/TIMER.d 


# Each subdirectory must supply rules for building sources it contributes
BM_Drivers/Src/%.o BM_Drivers/Src/%.su BM_Drivers/Src/%.cyclo: ../BM_Drivers/Src/%.c BM_Drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BM_Drivers-2f-Src

clean-BM_Drivers-2f-Src:
	-$(RM) ./BM_Drivers/Src/GPIO.cyclo ./BM_Drivers/Src/GPIO.d ./BM_Drivers/Src/GPIO.o ./BM_Drivers/Src/GPIO.su ./BM_Drivers/Src/I2C.cyclo ./BM_Drivers/Src/I2C.d ./BM_Drivers/Src/I2C.o ./BM_Drivers/Src/I2C.su ./BM_Drivers/Src/MOVEMENT.cyclo ./BM_Drivers/Src/MOVEMENT.d ./BM_Drivers/Src/MOVEMENT.o ./BM_Drivers/Src/MOVEMENT.su ./BM_Drivers/Src/RCC.cyclo ./BM_Drivers/Src/RCC.d ./BM_Drivers/Src/RCC.o ./BM_Drivers/Src/RCC.su ./BM_Drivers/Src/TIMER.cyclo ./BM_Drivers/Src/TIMER.d ./BM_Drivers/Src/TIMER.o ./BM_Drivers/Src/TIMER.su

.PHONY: clean-BM_Drivers-2f-Src

