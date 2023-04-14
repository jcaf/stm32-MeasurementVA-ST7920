################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/Core/INA229/ina229.c 

OBJS += \
./Application/User/Core/INA229/ina229.o 

C_DEPS += \
./Application/User/Core/INA229/ina229.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/INA229/%.o Application/User/Core/INA229/%.su Application/User/Core/INA229/%.cyclo: ../Application/User/Core/INA229/%.c Application/User/Core/INA229/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F042x6 -c -I../../Core/Inc -I/run/user/1000/doc/70655d00/Core -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Core-2f-INA229

clean-Application-2f-User-2f-Core-2f-INA229:
	-$(RM) ./Application/User/Core/INA229/ina229.cyclo ./Application/User/Core/INA229/ina229.d ./Application/User/Core/INA229/ina229.o ./Application/User/Core/INA229/ina229.su

.PHONY: clean-Application-2f-User-2f-Core-2f-INA229

