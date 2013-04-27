#******************************************************************************
#
# Makefile - Rules for building the uCOS-II lwIP Application.
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
VPATH+=./Hal/Evm/Src
VPATH+=./Hal/Oled/Src
VPATH+=./uCOS-II/Ports
VPATH+=./uCOS-II/Ports/Src
VPATH+=./uCOS-II/Source/Src
VPATH+=./lwip-1.3.2/ports/stellaris
VPATH+=./lwip-1.3.2/arch
VPATH+=./lwip-1.3.2/src/api
VPATH+=./lwip-1.3.2/src/core
VPATH+=./lwip-1.3.2/src/core/ipv4
VPATH+=./lwip-1.3.2/src/netif


#
# Where to find header files that do not live in the source directory.
#
IPATH=.
IPATH+=./App/Head
IPATH+=./Hal/Evm/Head
IPATH+=./Hal/Oled/Head
IPATH+=./LM3_Lib
IPATH+=./LM3_Lib/inc
IPATH+=./lwip-1.3.2/arch
IPATH+=./lwip-1.3.2/src/include
IPATH+=./uCOS-II/Ports/Head
IPATH+=./uCOS-II/Source/Head

#
# The default rule, which causes the zlgGUI Application using ZLG_GUI to be built.
#
all: ${COMPILER}
all: ${COMPILER}/ucos_lwip.axf

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
# Rules for building the zlgGUI Application.
#
${COMPILER}/ucos_lwip.axf: ${COMPILER}/main.o

${COMPILER}/ucos_lwip.axf: ${COMPILER}/perf.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/sys_arch.o

${COMPILER}/ucos_lwip.axf: ${COMPILER}/api_lib.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/api_msg.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/err.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/netbuf.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/netdb.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/netifapi.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/sockets.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/tcpip.o

${COMPILER}/ucos_lwip.axf: ${COMPILER}/sockets.o

${COMPILER}/ucos_lwip.axf: ${COMPILER}/tcp_in.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/tcp_out.o

${COMPILER}/ucos_lwip.axf: ${COMPILER}/autoip.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/icmp.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/igmp.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/inet.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/inet_chksum.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/ip.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/ip_addr.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/ip_frag.o

${COMPILER}/ucos_lwip.axf: ${COMPILER}/etharp.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/loopif.o

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

${COMPILER}/ucos_lwip.axf: ${COMPILER}/Target.o
${COMPILER}/ucos_lwip.axf: ${COMPILER}/rit128x96x4.o

${COMPILER}/ucos_lwip.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/ucos_lwip.axf: ${ROOT}/LM3_Lib/DriverLib/libdriver.a
${COMPILER}/ucos_lwip.axf: ucos_lwip.ld
SCATTERgcc_ucos_lwip=ucos_lwip.ld
ENTRY_ucos_lwip=ResetISR

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif

