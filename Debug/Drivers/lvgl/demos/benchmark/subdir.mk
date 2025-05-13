################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/demos/benchmark/lv_demo_benchmark.c 

OBJS += \
./Drivers/lvgl/demos/benchmark/lv_demo_benchmark.o 

C_DEPS += \
./Drivers/lvgl/demos/benchmark/lv_demo_benchmark.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/demos/benchmark/%.o Drivers/lvgl/demos/benchmark/%.su Drivers/lvgl/demos/benchmark/%.cyclo: ../Drivers/lvgl/demos/benchmark/%.c Drivers/lvgl/demos/benchmark/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"/home/kiet/STM32CubeIDE/workspace_1.18.1/STM32_TFT_Display_F407/Drivers/UI" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I/home/kiet/STM32CubeIDE/workspace_1.18.1/STM32_TFT_Display_F407/Drivers/lvgl -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-demos-2f-benchmark

clean-Drivers-2f-lvgl-2f-demos-2f-benchmark:
	-$(RM) ./Drivers/lvgl/demos/benchmark/lv_demo_benchmark.cyclo ./Drivers/lvgl/demos/benchmark/lv_demo_benchmark.d ./Drivers/lvgl/demos/benchmark/lv_demo_benchmark.o ./Drivers/lvgl/demos/benchmark/lv_demo_benchmark.su

.PHONY: clean-Drivers-2f-lvgl-2f-demos-2f-benchmark

