################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UI/screens/ui_Screen1.c 

OBJS += \
./Drivers/UI/screens/ui_Screen1.o 

C_DEPS += \
./Drivers/UI/screens/ui_Screen1.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UI/screens/%.o Drivers/UI/screens/%.su Drivers/UI/screens/%.cyclo: ../Drivers/UI/screens/%.c Drivers/UI/screens/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"/home/kiet/STM32CubeIDE/workspace_1.18.1/STM32_TFT_Display_F407/Drivers/UI" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I/home/kiet/STM32CubeIDE/workspace_1.18.1/STM32_TFT_Display_F407/Drivers/lvgl -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-UI-2f-screens

clean-Drivers-2f-UI-2f-screens:
	-$(RM) ./Drivers/UI/screens/ui_Screen1.cyclo ./Drivers/UI/screens/ui_Screen1.d ./Drivers/UI/screens/ui_Screen1.o ./Drivers/UI/screens/ui_Screen1.su

.PHONY: clean-Drivers-2f-UI-2f-screens

