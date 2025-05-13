################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/extra/libs/rlottie/lv_rlottie.c 

OBJS += \
./Drivers/lvgl/src/extra/libs/rlottie/lv_rlottie.o 

C_DEPS += \
./Drivers/lvgl/src/extra/libs/rlottie/lv_rlottie.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/extra/libs/rlottie/%.o Drivers/lvgl/src/extra/libs/rlottie/%.su Drivers/lvgl/src/extra/libs/rlottie/%.cyclo: ../Drivers/lvgl/src/extra/libs/rlottie/%.c Drivers/lvgl/src/extra/libs/rlottie/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"/home/kiet/STM32CubeIDE/workspace_1.18.1/STM32_TFT_Display_F407/Drivers/UI" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I/home/kiet/STM32CubeIDE/workspace_1.18.1/STM32_TFT_Display_F407/Drivers/lvgl -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-libs-2f-rlottie

clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-libs-2f-rlottie:
	-$(RM) ./Drivers/lvgl/src/extra/libs/rlottie/lv_rlottie.cyclo ./Drivers/lvgl/src/extra/libs/rlottie/lv_rlottie.d ./Drivers/lvgl/src/extra/libs/rlottie/lv_rlottie.o ./Drivers/lvgl/src/extra/libs/rlottie/lv_rlottie.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-extra-2f-libs-2f-rlottie

