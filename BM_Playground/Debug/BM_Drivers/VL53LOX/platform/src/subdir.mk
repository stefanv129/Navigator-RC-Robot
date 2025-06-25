################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_platform.c \
../BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_win_serial_comms.c \
../BM_Drivers/VL53LOX/platform/src/vl53l0x_platform.c \
../BM_Drivers/VL53LOX/platform/src/vl53l0x_platform_log.c 

OBJS += \
./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_platform.o \
./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_win_serial_comms.o \
./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform.o \
./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform_log.o 

C_DEPS += \
./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_platform.d \
./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_win_serial_comms.d \
./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform.d \
./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform_log.d 


# Each subdirectory must supply rules for building sources it contributes
BM_Drivers/VL53LOX/platform/src/%.o BM_Drivers/VL53LOX/platform/src/%.su BM_Drivers/VL53LOX/platform/src/%.cyclo: ../BM_Drivers/VL53LOX/platform/src/%.c BM_Drivers/VL53LOX/platform/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/Inc" -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/VL53LOX/core/inc" -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/VL53LOX/platform/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BM_Drivers-2f-VL53LOX-2f-platform-2f-src

clean-BM_Drivers-2f-VL53LOX-2f-platform-2f-src:
	-$(RM) ./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_platform.cyclo ./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_platform.d ./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_platform.o ./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_platform.su ./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_win_serial_comms.cyclo ./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_win_serial_comms.d ./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_win_serial_comms.o ./BM_Drivers/VL53LOX/platform/src/vl53l0x_i2c_win_serial_comms.su ./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform.cyclo ./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform.d ./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform.o ./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform.su ./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform_log.cyclo ./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform_log.d ./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform_log.o ./BM_Drivers/VL53LOX/platform/src/vl53l0x_platform_log.su

.PHONY: clean-BM_Drivers-2f-VL53LOX-2f-platform-2f-src

