#******************************************************************************
#
# Makefile - Rules for building the driver library.
#
#
#******************************************************************************

#
# The base directory for StellarisWare.
#
ROOT=../..

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find header files that do not live in the source directory.
#
IPATH=..

#
# The default rule, which causes the driver library to be built.
#
all: ${COMPILER}
all: ${COMPILER}/libdriver.a

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the driver library.
#
${COMPILER}/libdriver.a: ${COMPILER}/adc.o
${COMPILER}/libdriver.a: ${COMPILER}/can.o
${COMPILER}/libdriver.a: ${COMPILER}/comp.o
${COMPILER}/libdriver.a: ${COMPILER}/cpu.o
${COMPILER}/libdriver.a: ${COMPILER}/epi.o
${COMPILER}/libdriver.a: ${COMPILER}/ethernet.o
${COMPILER}/libdriver.a: ${COMPILER}/flash.o
${COMPILER}/libdriver.a: ${COMPILER}/gpio.o
${COMPILER}/libdriver.a: ${COMPILER}/hibernate.o
${COMPILER}/libdriver.a: ${COMPILER}/i2c.o
${COMPILER}/libdriver.a: ${COMPILER}/i2s.o
${COMPILER}/libdriver.a: ${COMPILER}/interrupt.o
${COMPILER}/libdriver.a: ${COMPILER}/mpu.o
${COMPILER}/libdriver.a: ${COMPILER}/pwm.o
${COMPILER}/libdriver.a: ${COMPILER}/qei.o
${COMPILER}/libdriver.a: ${COMPILER}/ssi.o
${COMPILER}/libdriver.a: ${COMPILER}/sysctl.o
${COMPILER}/libdriver.a: ${COMPILER}/systick.o
${COMPILER}/libdriver.a: ${COMPILER}/timer.o
${COMPILER}/libdriver.a: ${COMPILER}/uart.o
${COMPILER}/libdriver.a: ${COMPILER}/udma.o
${COMPILER}/libdriver.a: ${COMPILER}/usb.o
${COMPILER}/libdriver.a: ${COMPILER}/watchdog.o

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
