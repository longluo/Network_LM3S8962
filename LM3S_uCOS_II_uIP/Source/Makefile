#******************************************************************************
#
# Makefile - Rules for building the Sample Ethernet Application using uIP.
#
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=LM3S8962

#
# The base directory for project.
#
ROOT=.

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH=./App/Src
VPATH+=./Hal

VPATH+=./Hal/Oled
VPATH+=./uCOS-II/Ports
VPATH+=./uCOS-II/Ports/Src
VPATH+=./uCOS-II/Source/Src

VPATH+=./uip-1.0/apps/dhcpc

VPATH+=./uip-1.0/uip
VPATH+=./Utils


#
# Where to find header files that do not live in the source directory.
#
IPATH=.
IPATH+=./App
IPATH+=./Hal/Oled
IPATH+=./LM3_Lib/inc
IPATH+=./uip-1.0/apps/dhcpc
IPATH+=./uip-1.0/uip
IPATH+=./uip-1.0
IPATH+=./uCOS-II/Ports/Head
IPATH+=./uCOS-II/Source/Head
IPATH+=./Utils

#
# The default rule, which causes the Sample Ethernet Application using uIP to be built.
#
all: ${COMPILER}
all: ${COMPILER}/ucos_uip.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir ${COMPILER}

#
# Rules for building the Sample Ethernet Application using uIP.
#
${COMPILER}/ucos_uip.axf: ${COMPILER}/main.o

${COMPILER}/ucos_uip.axf: ${COMPILER}/rit128x96x4.o
${COMPILER}/ucos_uip.axf: ${COMPILER}/startup_${COMPILER}.o

${COMPILER}/ucos_uip.axf: ${COMPILER}/uip.o
${COMPILER}/ucos_uip.axf: ${COMPILER}/uip_arp.o
${COMPILER}/ucos_uip.axf: ${COMPILER}/uip_timer.o


${COMPILER}/ucos_uip.axf: ${COMPILER}/dhcpc.o
${COMPILER}/ucos_uip.axf: ${COMPILER}/httpd.o

${COMPILER}/ucos_uip.axf: ${COMPILER}/ustdlib.o

${COMPILER}/ucos_lwip.axf: ${COMPILER}/OS_CORE.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/OS_FLAG.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/OS_MBOX.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/OS_MEM.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/OS_MUTEX.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/OS_Q.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/OS_SEM.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/OS_TASK.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/OS_TIME.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/OS_DBG.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/os_cpu_a.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/os_cpu_c.o

${COMPILER}/ucos_uip.axf: ${ROOT}/LM3_Lib/DriverLib/libdriver.a
${COMPILER}/ucos_uip.axf: ucos_ii_uip.ld.ld
SCATTERgcc_ucos_uip=ucos_ii_uip.ld.ld
ENTRY_ucos_uip=ResetISR

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif

