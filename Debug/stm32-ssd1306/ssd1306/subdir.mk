################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32-ssd1306/ssd1306/ssd1306.c \
../stm32-ssd1306/ssd1306/ssd1306_fonts.c \
../stm32-ssd1306/ssd1306/ssd1306_tests.c 

OBJS += \
./stm32-ssd1306/ssd1306/ssd1306.o \
./stm32-ssd1306/ssd1306/ssd1306_fonts.o \
./stm32-ssd1306/ssd1306/ssd1306_tests.o 

C_DEPS += \
./stm32-ssd1306/ssd1306/ssd1306.d \
./stm32-ssd1306/ssd1306/ssd1306_fonts.d \
./stm32-ssd1306/ssd1306/ssd1306_tests.d 


# Each subdirectory must supply rules for building sources it contributes
stm32-ssd1306/ssd1306/%.o stm32-ssd1306/ssd1306/%.su: ../stm32-ssd1306/ssd1306/%.c stm32-ssd1306/ssd1306/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"G:/Dokumenty/SW_Mini_Fridge/SW_Mini_Fridge/stm32-ssd1306/ssd1306" -I"G:/Dokumenty/SW_Mini_Fridge/SW_Mini_Fridge/lwow/lwow/src/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-stm32-2d-ssd1306-2f-ssd1306

clean-stm32-2d-ssd1306-2f-ssd1306:
	-$(RM) ./stm32-ssd1306/ssd1306/ssd1306.d ./stm32-ssd1306/ssd1306/ssd1306.o ./stm32-ssd1306/ssd1306/ssd1306.su ./stm32-ssd1306/ssd1306/ssd1306_fonts.d ./stm32-ssd1306/ssd1306/ssd1306_fonts.o ./stm32-ssd1306/ssd1306/ssd1306_fonts.su ./stm32-ssd1306/ssd1306/ssd1306_tests.d ./stm32-ssd1306/ssd1306/ssd1306_tests.o ./stm32-ssd1306/ssd1306/ssd1306_tests.su

.PHONY: clean-stm32-2d-ssd1306-2f-ssd1306

