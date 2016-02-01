################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tinyXML/tinystr.cpp \
../tinyXML/tinyxml.cpp \
../tinyXML/tinyxmlerror.cpp \
../tinyXML/tinyxmlparser.cpp 

OBJS += \
./tinyXML/tinystr.o \
./tinyXML/tinyxml.o \
./tinyXML/tinyxmlerror.o \
./tinyXML/tinyxmlparser.o 

CPP_DEPS += \
./tinyXML/tinystr.d \
./tinyXML/tinyxml.d \
./tinyXML/tinyxmlerror.d \
./tinyXML/tinyxmlparser.d 


# Each subdirectory must supply rules for building sources it contributes
tinyXML/%.o: ../tinyXML/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


