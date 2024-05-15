################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ExtLib/CAN_SPI.c \
../ExtLib/MCP2515.c 

OBJS += \
./ExtLib/CAN_SPI.o \
./ExtLib/MCP2515.o 

C_DEPS += \
./ExtLib/CAN_SPI.d \
./ExtLib/MCP2515.d 


# Each subdirectory must supply rules for building sources it contributes
ExtLib/%.o ExtLib/%.su ExtLib/%.cyclo: ../ExtLib/%.c ExtLib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Admin/STM32CubeIDE/workspace_1.14.0/STM32L152_CAN/ExtLib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ExtLib

clean-ExtLib:
	-$(RM) ./ExtLib/CAN_SPI.cyclo ./ExtLib/CAN_SPI.d ./ExtLib/CAN_SPI.o ./ExtLib/CAN_SPI.su ./ExtLib/MCP2515.cyclo ./ExtLib/MCP2515.d ./ExtLib/MCP2515.o ./ExtLib/MCP2515.su

.PHONY: clean-ExtLib

