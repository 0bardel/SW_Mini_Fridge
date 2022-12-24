################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lwow/lwow/src/devices/lwow_device_ds18x20.c 

OBJS += \
./lwow/lwow/src/devices/lwow_device_ds18x20.o 

C_DEPS += \
./lwow/lwow/src/devices/lwow_device_ds18x20.d 


# Each subdirectory must supply rules for building sources it contributes
lwow/lwow/src/devices/%.o lwow/lwow/src/devices/%.su: ../lwow/lwow/src/devices/%.c lwow/lwow/src/devices/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"G:/Dokumenty/SW_Mini_Fridge/SW_Mini_Fridge/stm32-ssd1306/ssd1306" -I"G:/Dokumenty/SW_Mini_Fridge/SW_Mini_Fridge/lwow/lwow/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lwow-2f-lwow-2f-src-2f-devices

clean-lwow-2f-lwow-2f-src-2f-devices:
	-$(RM) ./lwow/lwow/src/devices/lwow_device_ds18x20.d ./lwow/lwow/src/devices/lwow_device_ds18x20.o ./lwow/lwow/src/devices/lwow_device_ds18x20.su

.PHONY: clean-lwow-2f-lwow-2f-src-2f-devices

