################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BM_Drivers/VL53LOX/bare_metal/src/vl53l0x_i2c_baremetal.c 

OBJS += \
./BM_Drivers/VL53LOX/bare_metal/src/vl53l0x_i2c_baremetal.o 

C_DEPS += \
./BM_Drivers/VL53LOX/bare_metal/src/vl53l0x_i2c_baremetal.d 


# Each subdirectory must supply rules for building sources it contributes
BM_Drivers/VL53LOX/bare_metal/src/%.o BM_Drivers/VL53LOX/bare_metal/src/%.su BM_Drivers/VL53LOX/bare_metal/src/%.cyclo: ../BM_Drivers/VL53LOX/bare_metal/src/%.c BM_Drivers/VL53LOX/bare_metal/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/Inc" -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/VL53LOX/core/inc" -I"C:/Users/voine/STM32CubeIDE/DegreeWS/BM_Playground/BM_Drivers/VL53LOX/bare_metal/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BM_Drivers-2f-VL53LOX-2f-bare_metal-2f-src

clean-BM_Drivers-2f-VL53LOX-2f-bare_metal-2f-src:
	-$(RM) ./BM_Drivers/VL53LOX/bare_metal/src/vl53l0x_i2c_baremetal.cyclo ./BM_Drivers/VL53LOX/bare_metal/src/vl53l0x_i2c_baremetal.d ./BM_Drivers/VL53LOX/bare_metal/src/vl53l0x_i2c_baremetal.o ./BM_Drivers/VL53LOX/bare_metal/src/vl53l0x_i2c_baremetal.su

.PHONY: clean-BM_Drivers-2f-VL53LOX-2f-bare_metal-2f-src

