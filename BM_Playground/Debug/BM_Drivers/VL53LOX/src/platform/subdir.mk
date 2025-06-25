################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BM_Drivers/VL53LOX/src/platform/vl53l1_platform.c \
../BM_Drivers/VL53LOX/src/platform/vl53l1_platform_init.c \
../BM_Drivers/VL53LOX/src/platform/vl53l1_platform_log.c 

OBJS += \
./BM_Drivers/VL53LOX/src/platform/vl53l1_platform.o \
./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_init.o \
./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_log.o 

C_DEPS += \
./BM_Drivers/VL53LOX/src/platform/vl53l1_platform.d \
./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_init.d \
./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_log.d 


# Each subdirectory must supply rules for building sources it contributes
BM_Drivers/VL53LOX/src/platform/%.o BM_Drivers/VL53LOX/src/platform/%.su BM_Drivers/VL53LOX/src/platform/%.cyclo: ../BM_Drivers/VL53LOX/src/platform/%.c BM_Drivers/VL53LOX/src/platform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/Inc" -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/VL53L0X/Inc/core" -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/VL53L0X/Inc/platform" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BM_Drivers-2f-VL53LOX-2f-src-2f-platform

clean-BM_Drivers-2f-VL53LOX-2f-src-2f-platform:
	-$(RM) ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform.cyclo ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform.d ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform.o ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform.su ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_init.cyclo ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_init.d ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_init.o ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_init.su ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_log.cyclo ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_log.d ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_log.o ./BM_Drivers/VL53LOX/src/platform/vl53l1_platform_log.su

.PHONY: clean-BM_Drivers-2f-VL53LOX-2f-src-2f-platform

