################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Static_Code/System/CPU_Init.c \
../Static_Code/System/Peripherals_Init.c \
../Static_Code/System/Vectors.c 

OBJS += \
./Static_Code/System/CPU_Init.o \
./Static_Code/System/Peripherals_Init.o \
./Static_Code/System/Vectors.o 

C_DEPS += \
./Static_Code/System/CPU_Init.d \
./Static_Code/System/Peripherals_Init.d \
./Static_Code/System/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Static_Code/System/%.o: ../Static_Code/System/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/kimbe/OneDrive/Documents/Git_Hub/labs-kimbender/Assignment2-Percy/Static_Code/System" -I"C:/Users/kimbe/OneDrive/Documents/Git_Hub/labs-kimbender/Assignment2-Percy/Static_Code/PDD" -I"C:/Users/kimbe/OneDrive/Documents/Git_Hub/labs-kimbender/Assignment2-Percy/Static_Code/IO_Map" -I"C:\Program Files\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/kimbe/OneDrive/Documents/Git_Hub/labs-kimbender/Assignment2-Percy/Sources" -I"C:/Users/kimbe/OneDrive/Documents/Git_Hub/labs-kimbender/Assignment2-Percy/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


