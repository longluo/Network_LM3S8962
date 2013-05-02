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
# The base directory for the project.
#
ROOT=.

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH=./App
VPATH+=./HAL
VPATH+=./HAL/Oled
VPATH+=./lwipConfig
#VPATH+=./lwip-1.3.2/apps/httpserver_raw
#VPATH+=./lwip-1.3.2/ports/stellaris
#VPATH+=./lwip-1.3.2/ports/stellaris/netif
#VPATH+=./lwip-1.3.2/arch
#VPATH+=./lwip-1.3.2/src/api
#VPATH+=./lwip-1.3.2/src/core
#VPATH+=./lwip-1.3.2/src/core/ipv4
#VPATH+=./lwip-1.3.2/src/core/snmp
#VPATH+=./lwip-1.3.2/src/netif
#VPATH+=./lwip-1.3.2/src/netif/ppp
VPATH+=./Utils
VPATH+=./WebClient

#
# Where to find header files that do not live in the source directory.
#
IPATH=.
IPATH+=./App
IPATH+=./HAL/Oled
IPATH+=./HAL
IPATH+=./LM3S_Lib/inc
IPATH+=./lwipConfig
IPATH+=./lwip-1.3.2/apps
#IPATH+=./lwip-1.3.2/apps/httpserver_raw
IPATH+=./lwip-1.3.2/ports/stellaris/include
IPATH+=./lwip-1.3.2/src/include
IPATH+=./lwip-1.3.2/src/include/ipv4
IPATH+=./Utils
IPATH+=./WebClient

#
# The default rule, which causes the Ethernet I/O Control Application using lwIP 1.3.2 to be built.
#
all: ${COMPILER}
all: ${COMPILER}/webclient_lwip.axf

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
# Rules for building the webclient_lwip Application using lwIP 1.3.2.
#
${COMPILER}/webclient_lwip.axf: ${COMPILER}/main.o

${COMPILER}/webclient_lwip.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/webclient_lwip.axf: ${COMPILER}/rit128x96x4.o

#${COMPILER}/webclient_lwip.axf: ${COMPILER}/locator.o
${COMPILER}/webclient_lwip.axf: ${COMPILER}/lwiplib.o

${COMPILER}/webclient_lwip.axf: ${COMPILER}/webclient.o
#${COMPILER}/webclient_lwip.axf: ${COMPILER}/httpd.o
#${COMPILER}/webclient_lwip.axf: ${COMPILER}/cgifuncs.o

${COMPILER}/webclient_lwip.axf: ${COMPILER}/ustdlib.o
${COMPILER}/webclient_lwip.axf: ${COMPILER}/uartstdio.o

${COMPILER}/webclient_lwip.axf: ${ROOT}/LM3S_Lib/DriverLib/libdriver.a
${COMPILER}/webclient_lwip.axf: lwip_client.ld
SCATTERgcc_webclient_lwip=lwip_client.ld
ENTRY_webclient_lwip=ResetISR

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif

