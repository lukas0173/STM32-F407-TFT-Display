################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/UI/images/ui_img_231284188.c \
../Drivers/UI/images/ui_img_231295465.c \
../Drivers/UI/images/ui_img_244846933.c \
../Drivers/UI/images/ui_img_465554078.c \
../Drivers/UI/images/ui_img_546624313.c \
../Drivers/UI/images/ui_img_airbag_png.c \
../Drivers/UI/images/ui_img_engine_png.c \
../Drivers/UI/images/ui_img_left_png.c 

OBJS += \
./Drivers/UI/images/ui_img_231284188.o \
./Drivers/UI/images/ui_img_231295465.o \
./Drivers/UI/images/ui_img_244846933.o \
./Drivers/UI/images/ui_img_465554078.o \
./Drivers/UI/images/ui_img_546624313.o \
./Drivers/UI/images/ui_img_airbag_png.o \
./Drivers/UI/images/ui_img_engine_png.o \
./Drivers/UI/images/ui_img_left_png.o 

C_DEPS += \
./Drivers/UI/images/ui_img_231284188.d \
./Drivers/UI/images/ui_img_231295465.d \
./Drivers/UI/images/ui_img_244846933.d \
./Drivers/UI/images/ui_img_465554078.d \
./Drivers/UI/images/ui_img_546624313.d \
./Drivers/UI/images/ui_img_airbag_png.d \
./Drivers/UI/images/ui_img_engine_png.d \
./Drivers/UI/images/ui_img_left_png.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/UI/images/%.o Drivers/UI/images/%.su Drivers/UI/images/%.cyclo: ../Drivers/UI/images/%.c Drivers/UI/images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"/home/kiet/STM32CubeIDE/workspace_1.18.1/STM32_TFT_Display_F407/Drivers/UI" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I/home/kiet/STM32CubeIDE/workspace_1.18.1/STM32_TFT_Display_F407/Drivers/lvgl -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-UI-2f-images

clean-Drivers-2f-UI-2f-images:
	-$(RM) ./Drivers/UI/images/ui_img_231284188.cyclo ./Drivers/UI/images/ui_img_231284188.d ./Drivers/UI/images/ui_img_231284188.o ./Drivers/UI/images/ui_img_231284188.su ./Drivers/UI/images/ui_img_231295465.cyclo ./Drivers/UI/images/ui_img_231295465.d ./Drivers/UI/images/ui_img_231295465.o ./Drivers/UI/images/ui_img_231295465.su ./Drivers/UI/images/ui_img_244846933.cyclo ./Drivers/UI/images/ui_img_244846933.d ./Drivers/UI/images/ui_img_244846933.o ./Drivers/UI/images/ui_img_244846933.su ./Drivers/UI/images/ui_img_465554078.cyclo ./Drivers/UI/images/ui_img_465554078.d ./Drivers/UI/images/ui_img_465554078.o ./Drivers/UI/images/ui_img_465554078.su ./Drivers/UI/images/ui_img_546624313.cyclo ./Drivers/UI/images/ui_img_546624313.d ./Drivers/UI/images/ui_img_546624313.o ./Drivers/UI/images/ui_img_546624313.su ./Drivers/UI/images/ui_img_airbag_png.cyclo ./Drivers/UI/images/ui_img_airbag_png.d ./Drivers/UI/images/ui_img_airbag_png.o ./Drivers/UI/images/ui_img_airbag_png.su ./Drivers/UI/images/ui_img_engine_png.cyclo ./Drivers/UI/images/ui_img_engine_png.d ./Drivers/UI/images/ui_img_engine_png.o ./Drivers/UI/images/ui_img_engine_png.su ./Drivers/UI/images/ui_img_left_png.cyclo ./Drivers/UI/images/ui_img_left_png.d ./Drivers/UI/images/ui_img_left_png.o ./Drivers/UI/images/ui_img_left_png.su

.PHONY: clean-Drivers-2f-UI-2f-images

