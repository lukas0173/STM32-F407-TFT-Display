################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.c \
../Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.c \
../Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.c \
../Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.c 

OBJS += \
./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.o \
./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.o \
./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.o \
./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.o 

C_DEPS += \
./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.d \
./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.d \
./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.d \
./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/lvgl/src/draw/nxp/pxp/%.o Drivers/lvgl/src/draw/nxp/pxp/%.su Drivers/lvgl/src/draw/nxp/pxp/%.cyclo: ../Drivers/lvgl/src/draw/nxp/pxp/%.c Drivers/lvgl/src/draw/nxp/pxp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I/home/kiet/STM32CubeIDE/workspace_1.18.1/STM32_TFT_Display_F407/Drivers/lvgl -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp

clean-Drivers-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp:
	-$(RM) ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.cyclo ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.d ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.o ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp.su ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.cyclo ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.d ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.o ./Drivers/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.su ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.cyclo ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.d ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.o ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.su ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.cyclo ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.d ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.o ./Drivers/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.su

.PHONY: clean-Drivers-2f-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp

