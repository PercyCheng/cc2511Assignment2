################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/drawShapes.c \
../Sources/main.c \
../Sources/utilities.c 

OBJS += \
./Sources/Events.o \
./Sources/drawShapes.o \
./Sources/main.o \
./Sources/utilities.o 

C_DEPS += \
./Sources/Events.d \
./Sources/drawShapes.d \
./Sources/main.d \
./Sources/utilities.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Labs/Assignment2-Percy/Static_Code/System" -I"C:/Labs/Assignment2-Percy/Static_Code/PDD" -I"C:/Labs/Assignment2-Percy/Static_Code/IO_Map" -I"C:\Freescale\KDS_v3\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Labs/Assignment2-Percy/Sources" -I"C:/Labs/Assignment2-Percy/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


