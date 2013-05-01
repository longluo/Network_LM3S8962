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
VPATH+=./uip-1.0/apps/dhcpc
VPATH+=./uip-1.0/apps/httpd
VPATH+=./uip-1.0/uip
VPATH+=./Utils

#
# Where to find header files that do not live in the source directory.
#
IPATH=.
IPATH+=./App
IPATH+=./Hal/Oled
IPATH+=./LM3_Lib/inc
IPATH+=./uip-1.0/apps
IPATH+=./uip-1.0/apps/dhcpc
IPATH+=./uip-1.0/apps/httpd
IPATH+=./uip-1.0/uip
IPATH+=./uip-1.0
IPATH+=./Utils

#
# The default rule, which causes the Sample Ethernet Application using uIP to be built.
#
all: ${COMPILER}
all: ${COMPILER}/enet_uip.axf

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
${COMPILER}/enet_uip.axf: ${COMPILER}/main.o

${COMPILER}/enet_uip.axf: ${COMPILER}/rit128x96x4.o
${COMPILER}/enet_uip.axf: ${COMPILER}/startup_${COMPILER}.o

${COMPILER}/enet_uip.axf: ${COMPILER}/uip.o
${COMPILER}/enet_uip.axf: ${COMPILER}/uip_arp.o
${COMPILER}/enet_uip.axf: ${COMPILER}/uip_timer.o

${COMPILER}/enet_uip.axf: ${COMPILER}/dhcpc.o
${COMPILER}/enet_uip.axf: ${COMPILER}/httpd.o

${COMPILER}/enet_uip.axf: ${COMPILER}/ustdlib.o
${COMPILER}/enet_uip.axf: ${ROOT}/LM3_Lib/DriverLib/libdriver.a
${COMPILER}/enet_uip.axf: enet_uip.ld
SCATTERgcc_enet_uip=enet_uip.ld
ENTRY_enet_uip=ResetISR

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif

