################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/ASerialLdd1.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd10.c \
../Generated_Code/BitIoLdd11.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/BitIoLdd3.c \
../Generated_Code/BitIoLdd4.c \
../Generated_Code/BitIoLdd5.c \
../Generated_Code/BitIoLdd6.c \
../Generated_Code/BitIoLdd7.c \
../Generated_Code/BitIoLdd8.c \
../Generated_Code/BitIoLdd9.c \
../Generated_Code/Cpu.c \
../Generated_Code/Dir_x.c \
../Generated_Code/Dir_y.c \
../Generated_Code/Dir_z.c \
../Generated_Code/FC321.c \
../Generated_Code/Inhr1.c \
../Generated_Code/Mode_1.c \
../Generated_Code/Mode_2.c \
../Generated_Code/Mode_3.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PWM1.c \
../Generated_Code/Pins1.c \
../Generated_Code/PwmLdd1.c \
../Generated_Code/RealTimeLdd1.c \
../Generated_Code/Reset.c \
../Generated_Code/Sleep.c \
../Generated_Code/TU1.c \
../Generated_Code/TU3.c \
../Generated_Code/Term1.c \
../Generated_Code/x.c \
../Generated_Code/y.c \
../Generated_Code/z.c 

OBJS += \
./Generated_Code/ASerialLdd1.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd10.o \
./Generated_Code/BitIoLdd11.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/BitIoLdd3.o \
./Generated_Code/BitIoLdd4.o \
./Generated_Code/BitIoLdd5.o \
./Generated_Code/BitIoLdd6.o \
./Generated_Code/BitIoLdd7.o \
./Generated_Code/BitIoLdd8.o \
./Generated_Code/BitIoLdd9.o \
./Generated_Code/Cpu.o \
./Generated_Code/Dir_x.o \
./Generated_Code/Dir_y.o \
./Generated_Code/Dir_z.o \
./Generated_Code/FC321.o \
./Generated_Code/Inhr1.o \
./Generated_Code/Mode_1.o \
./Generated_Code/Mode_2.o \
./Generated_Code/Mode_3.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PWM1.o \
./Generated_Code/Pins1.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/RealTimeLdd1.o \
./Generated_Code/Reset.o \
./Generated_Code/Sleep.o \
./Generated_Code/TU1.o \
./Generated_Code/TU3.o \
./Generated_Code/Term1.o \
./Generated_Code/x.o \
./Generated_Code/y.o \
./Generated_Code/z.o 

C_DEPS += \
./Generated_Code/ASerialLdd1.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd10.d \
./Generated_Code/BitIoLdd11.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/BitIoLdd3.d \
./Generated_Code/BitIoLdd4.d \
./Generated_Code/BitIoLdd5.d \
./Generated_Code/BitIoLdd6.d \
./Generated_Code/BitIoLdd7.d \
./Generated_Code/BitIoLdd8.d \
./Generated_Code/BitIoLdd9.d \
./Generated_Code/Cpu.d \
./Generated_Code/Dir_x.d \
./Generated_Code/Dir_y.d \
./Generated_Code/Dir_z.d \
./Generated_Code/FC321.d \
./Generated_Code/Inhr1.d \
./Generated_Code/Mode_1.d \
./Generated_Code/Mode_2.d \
./Generated_Code/Mode_3.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PWM1.d \
./Generated_Code/Pins1.d \
./Generated_Code/PwmLdd1.d \
./Generated_Code/RealTimeLdd1.d \
./Generated_Code/Reset.d \
./Generated_Code/Sleep.d \
./Generated_Code/TU1.d \
./Generated_Code/TU3.d \
./Generated_Code/Term1.d \
./Generated_Code/x.d \
./Generated_Code/y.d \
./Generated_Code/z.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"C:/Users/kimbe/OneDrive/Documents/Git_Hub/labs-kimbender/Assignment2-Percy/Static_Code/System" -I"C:/Users/kimbe/OneDrive/Documents/Git_Hub/labs-kimbender/Assignment2-Percy/Static_Code/PDD" -I"C:/Users/kimbe/OneDrive/Documents/Git_Hub/labs-kimbender/Assignment2-Percy/Static_Code/IO_Map" -I"C:\Program Files\eclipse\ProcessorExpert/lib/Kinetis/pdd/inc" -I"C:/Users/kimbe/OneDrive/Documents/Git_Hub/labs-kimbender/Assignment2-Percy/Sources" -I"C:/Users/kimbe/OneDrive/Documents/Git_Hub/labs-kimbender/Assignment2-Percy/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


