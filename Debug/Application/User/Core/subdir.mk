################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/run/flatpak/doc/1386df1/STM32Firmware/Core/Src/main.c \
/run/flatpak/doc/1386df1/STM32Firmware/Core/Src/stm32f0xx_hal_msp.c \
/run/flatpak/doc/1386df1/STM32Firmware/Core/Src/stm32f0xx_it.c \
../Application/User/Core/syscalls.c \
../Application/User/Core/sysmem.c 

OBJS += \
./Application/User/Core/main.o \
./Application/User/Core/stm32f0xx_hal_msp.o \
./Application/User/Core/stm32f0xx_it.o \
./Application/User/Core/syscalls.o \
./Application/User/Core/sysmem.o 

C_DEPS += \
./Application/User/Core/main.d \
./Application/User/Core/stm32f0xx_hal_msp.d \
./Application/User/Core/stm32f0xx_it.d \
./Application/User/Core/syscalls.d \
./Application/User/Core/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/main.o: /run/flatpak/doc/1386df1/STM32Firmware/Core/Src/main.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F042x6 -c -I../../Core/Inc -I/run/user/1000/doc/70655d00/Core -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/stm32f0xx_hal_msp.o: /run/flatpak/doc/1386df1/STM32Firmware/Core/Src/stm32f0xx_hal_msp.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F042x6 -c -I../../Core/Inc -I/run/user/1000/doc/70655d00/Core -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/stm32f0xx_it.o: /run/flatpak/doc/1386df1/STM32Firmware/Core/Src/stm32f0xx_it.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F042x6 -c -I../../Core/Inc -I/run/user/1000/doc/70655d00/Core -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/User/Core/%.o Application/User/Core/%.su Application/User/Core/%.cyclo: ../Application/User/Core/%.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F042x6 -c -I../../Core/Inc -I/run/user/1000/doc/70655d00/Core -I../../Drivers/STM32F0xx_HAL_Driver/Inc -I../../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Core

clean-Application-2f-User-2f-Core:
	-$(RM) ./Application/User/Core/main.cyclo ./Application/User/Core/main.d ./Application/User/Core/main.o ./Application/User/Core/main.su ./Application/User/Core/stm32f0xx_hal_msp.cyclo ./Application/User/Core/stm32f0xx_hal_msp.d ./Application/User/Core/stm32f0xx_hal_msp.o ./Application/User/Core/stm32f0xx_hal_msp.su ./Application/User/Core/stm32f0xx_it.cyclo ./Application/User/Core/stm32f0xx_it.d ./Application/User/Core/stm32f0xx_it.o ./Application/User/Core/stm32f0xx_it.su ./Application/User/Core/syscalls.cyclo ./Application/User/Core/syscalls.d ./Application/User/Core/syscalls.o ./Application/User/Core/syscalls.su ./Application/User/Core/sysmem.cyclo ./Application/User/Core/sysmem.d ./Application/User/Core/sysmem.o ./Application/User/Core/sysmem.su

.PHONY: clean-Application-2f-User-2f-Core

