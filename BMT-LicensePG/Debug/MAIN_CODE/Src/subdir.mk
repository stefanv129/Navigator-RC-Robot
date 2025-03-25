################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MAIN_CODE/Src/main.c \
../MAIN_CODE/Src/syscalls.c \
../MAIN_CODE/Src/sysmem.c 

OBJS += \
./MAIN_CODE/Src/main.o \
./MAIN_CODE/Src/syscalls.o \
./MAIN_CODE/Src/sysmem.o 

C_DEPS += \
./MAIN_CODE/Src/main.d \
./MAIN_CODE/Src/syscalls.d \
./MAIN_CODE/Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
MAIN_CODE/Src/%.o MAIN_CODE/Src/%.su MAIN_CODE/Src/%.cyclo: ../MAIN_CODE/Src/%.c MAIN_CODE/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_F401RE -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MAIN_CODE-2f-Src

clean-MAIN_CODE-2f-Src:
	-$(RM) ./MAIN_CODE/Src/main.cyclo ./MAIN_CODE/Src/main.d ./MAIN_CODE/Src/main.o ./MAIN_CODE/Src/main.su ./MAIN_CODE/Src/syscalls.cyclo ./MAIN_CODE/Src/syscalls.d ./MAIN_CODE/Src/syscalls.o ./MAIN_CODE/Src/syscalls.su ./MAIN_CODE/Src/sysmem.cyclo ./MAIN_CODE/Src/sysmem.d ./MAIN_CODE/Src/sysmem.o ./MAIN_CODE/Src/sysmem.su

.PHONY: clean-MAIN_CODE-2f-Src

