################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BM_Drivers/VL53LOX/core/src/vl53l0x_api.c \
../BM_Drivers/VL53LOX/core/src/vl53l0x_api_calibration.c \
../BM_Drivers/VL53LOX/core/src/vl53l0x_api_core.c \
../BM_Drivers/VL53LOX/core/src/vl53l0x_api_ranging.c \
../BM_Drivers/VL53LOX/core/src/vl53l0x_api_strings.c 

OBJS += \
./BM_Drivers/VL53LOX/core/src/vl53l0x_api.o \
./BM_Drivers/VL53LOX/core/src/vl53l0x_api_calibration.o \
./BM_Drivers/VL53LOX/core/src/vl53l0x_api_core.o \
./BM_Drivers/VL53LOX/core/src/vl53l0x_api_ranging.o \
./BM_Drivers/VL53LOX/core/src/vl53l0x_api_strings.o 

C_DEPS += \
./BM_Drivers/VL53LOX/core/src/vl53l0x_api.d \
./BM_Drivers/VL53LOX/core/src/vl53l0x_api_calibration.d \
./BM_Drivers/VL53LOX/core/src/vl53l0x_api_core.d \
./BM_Drivers/VL53LOX/core/src/vl53l0x_api_ranging.d \
./BM_Drivers/VL53LOX/core/src/vl53l0x_api_strings.d 


# Each subdirectory must supply rules for building sources it contributes
BM_Drivers/VL53LOX/core/src/%.o BM_Drivers/VL53LOX/core/src/%.su BM_Drivers/VL53LOX/core/src/%.cyclo: ../BM_Drivers/VL53LOX/core/src/%.c BM_Drivers/VL53LOX/core/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/Inc" -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/VL53LOX/core/inc" -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/VL53LOX/bare_metal/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BM_Drivers-2f-VL53LOX-2f-core-2f-src

clean-BM_Drivers-2f-VL53LOX-2f-core-2f-src:
	-$(RM) ./BM_Drivers/VL53LOX/core/src/vl53l0x_api.cyclo ./BM_Drivers/VL53LOX/core/src/vl53l0x_api.d ./BM_Drivers/VL53LOX/core/src/vl53l0x_api.o ./BM_Drivers/VL53LOX/core/src/vl53l0x_api.su ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_calibration.cyclo ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_calibration.d ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_calibration.o ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_calibration.su ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_core.cyclo ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_core.d ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_core.o ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_core.su ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_ranging.cyclo ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_ranging.d ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_ranging.o ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_ranging.su ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_strings.cyclo ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_strings.d ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_strings.o ./BM_Drivers/VL53LOX/core/src/vl53l0x_api_strings.su

.PHONY: clean-BM_Drivers-2f-VL53LOX-2f-core-2f-src

