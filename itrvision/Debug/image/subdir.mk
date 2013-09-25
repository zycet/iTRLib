################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../image/iformat.cc \
../image/image.cc 

OBJS += \
./image/iformat.o \
./image/image.o 

CC_DEPS += \
./image/iformat.d \
./image/image.d 


# Each subdirectory must supply rules for building sources it contributes
image/%.o: ../image/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/buaa/itrvision/itrbase" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


