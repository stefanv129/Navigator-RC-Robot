################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BM_Drivers/VL53LOX/src/core/vl53l1_api.c \
../BM_Drivers/VL53LOX/src/core/vl53l1_api_calibration.c \
../BM_Drivers/VL53LOX/src/core/vl53l1_api_core.c \
../BM_Drivers/VL53LOX/src/core/vl53l1_api_debug.c \
../BM_Drivers/VL53LOX/src/core/vl53l1_api_preset_modes.c \
../BM_Drivers/VL53LOX/src/core/vl53l1_api_strings.c \
../BM_Drivers/VL53LOX/src/core/vl53l1_core.c \
../BM_Drivers/VL53LOX/src/core/vl53l1_core_support.c \
../BM_Drivers/VL53LOX/src/core/vl53l1_error_strings.c \
../BM_Drivers/VL53LOX/src/core/vl53l1_register_funcs.c \
../BM_Drivers/VL53LOX/src/core/vl53l1_silicon_core.c \
../BM_Drivers/VL53LOX/src/core/vl53l1_wait.c 

OBJS += \
./BM_Drivers/VL53LOX/src/core/vl53l1_api.o \
./BM_Drivers/VL53LOX/src/core/vl53l1_api_calibration.o \
./BM_Drivers/VL53LOX/src/core/vl53l1_api_core.o \
./BM_Drivers/VL53LOX/src/core/vl53l1_api_debug.o \
./BM_Drivers/VL53LOX/src/core/vl53l1_api_preset_modes.o \
./BM_Drivers/VL53LOX/src/core/vl53l1_api_strings.o \
./BM_Drivers/VL53LOX/src/core/vl53l1_core.o \
./BM_Drivers/VL53LOX/src/core/vl53l1_core_support.o \
./BM_Drivers/VL53LOX/src/core/vl53l1_error_strings.o \
./BM_Drivers/VL53LOX/src/core/vl53l1_register_funcs.o \
./BM_Drivers/VL53LOX/src/core/vl53l1_silicon_core.o \
./BM_Drivers/VL53LOX/src/core/vl53l1_wait.o 

C_DEPS += \
./BM_Drivers/VL53LOX/src/core/vl53l1_api.d \
./BM_Drivers/VL53LOX/src/core/vl53l1_api_calibration.d \
./BM_Drivers/VL53LOX/src/core/vl53l1_api_core.d \
./BM_Drivers/VL53LOX/src/core/vl53l1_api_debug.d \
./BM_Drivers/VL53LOX/src/core/vl53l1_api_preset_modes.d \
./BM_Drivers/VL53LOX/src/core/vl53l1_api_strings.d \
./BM_Drivers/VL53LOX/src/core/vl53l1_core.d \
./BM_Drivers/VL53LOX/src/core/vl53l1_core_support.d \
./BM_Drivers/VL53LOX/src/core/vl53l1_error_strings.d \
./BM_Drivers/VL53LOX/src/core/vl53l1_register_funcs.d \
./BM_Drivers/VL53LOX/src/core/vl53l1_silicon_core.d \
./BM_Drivers/VL53LOX/src/core/vl53l1_wait.d 


# Each subdirectory must supply rules for building sources it contributes
BM_Drivers/VL53LOX/src/core/%.o BM_Drivers/VL53LOX/src/core/%.su BM_Drivers/VL53LOX/src/core/%.cyclo: ../BM_Drivers/VL53LOX/src/core/%.c BM_Drivers/VL53LOX/src/core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/Inc" -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/VL53L0X/Inc/core" -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/VL53L0X/Inc/platform" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BM_Drivers-2f-VL53LOX-2f-src-2f-core

clean-BM_Drivers-2f-VL53LOX-2f-src-2f-core:
	-$(RM) ./BM_Drivers/VL53LOX/src/core/vl53l1_api.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_api.d ./BM_Drivers/VL53LOX/src/core/vl53l1_api.o ./BM_Drivers/VL53LOX/src/core/vl53l1_api.su ./BM_Drivers/VL53LOX/src/core/vl53l1_api_calibration.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_api_calibration.d ./BM_Drivers/VL53LOX/src/core/vl53l1_api_calibration.o ./BM_Drivers/VL53LOX/src/core/vl53l1_api_calibration.su ./BM_Drivers/VL53LOX/src/core/vl53l1_api_core.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_api_core.d ./BM_Drivers/VL53LOX/src/core/vl53l1_api_core.o ./BM_Drivers/VL53LOX/src/core/vl53l1_api_core.su ./BM_Drivers/VL53LOX/src/core/vl53l1_api_debug.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_api_debug.d ./BM_Drivers/VL53LOX/src/core/vl53l1_api_debug.o ./BM_Drivers/VL53LOX/src/core/vl53l1_api_debug.su ./BM_Drivers/VL53LOX/src/core/vl53l1_api_preset_modes.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_api_preset_modes.d ./BM_Drivers/VL53LOX/src/core/vl53l1_api_preset_modes.o ./BM_Drivers/VL53LOX/src/core/vl53l1_api_preset_modes.su ./BM_Drivers/VL53LOX/src/core/vl53l1_api_strings.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_api_strings.d ./BM_Drivers/VL53LOX/src/core/vl53l1_api_strings.o ./BM_Drivers/VL53LOX/src/core/vl53l1_api_strings.su ./BM_Drivers/VL53LOX/src/core/vl53l1_core.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_core.d ./BM_Drivers/VL53LOX/src/core/vl53l1_core.o ./BM_Drivers/VL53LOX/src/core/vl53l1_core.su ./BM_Drivers/VL53LOX/src/core/vl53l1_core_support.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_core_support.d ./BM_Drivers/VL53LOX/src/core/vl53l1_core_support.o ./BM_Drivers/VL53LOX/src/core/vl53l1_core_support.su ./BM_Drivers/VL53LOX/src/core/vl53l1_error_strings.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_error_strings.d ./BM_Drivers/VL53LOX/src/core/vl53l1_error_strings.o ./BM_Drivers/VL53LOX/src/core/vl53l1_error_strings.su ./BM_Drivers/VL53LOX/src/core/vl53l1_register_funcs.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_register_funcs.d ./BM_Drivers/VL53LOX/src/core/vl53l1_register_funcs.o ./BM_Drivers/VL53LOX/src/core/vl53l1_register_funcs.su ./BM_Drivers/VL53LOX/src/core/vl53l1_silicon_core.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_silicon_core.d ./BM_Drivers/VL53LOX/src/core/vl53l1_silicon_core.o ./BM_Drivers/VL53LOX/src/core/vl53l1_silicon_core.su ./BM_Drivers/VL53LOX/src/core/vl53l1_wait.cyclo ./BM_Drivers/VL53LOX/src/core/vl53l1_wait.d ./BM_Drivers/VL53LOX/src/core/vl53l1_wait.o ./BM_Drivers/VL53LOX/src/core/vl53l1_wait.su

.PHONY: clean-BM_Drivers-2f-VL53LOX-2f-src-2f-core

