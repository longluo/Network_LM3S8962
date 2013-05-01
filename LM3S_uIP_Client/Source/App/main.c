/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Network_LM3S8962\LM3S_enet_uIP\Source\App\main.c
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      Sample WebServer Application for Ethernet.
** 
** Version: 1.0
** Date created: 23:27:01,30/04/2013
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_ethernet.h"
#include "debug.h"
#include "ethernet.h"
#include "flash.h"
#include "gpio.h"
#include "uart.h"
#include "interrupt.h"
#include "sysctl.h"
#include "systick.h"
#include "rit128x96x4.h"
#include "uip/uip.h"
#include "uip/uip_arp.h"
#include "Utils/ustdlib.h"
#include "Utils/uartstdio.h"
#include "clock-arch.h"



//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Ethernet with uIP (enet_uip)</h1>
//!
//! This example application demonstrates the operation of the Stellaris
//! Ethernet controller using the uIP TCP/IP Stack.  DHCP is used to obtain
//! an Ethernet address.  A basic web site is served over the Ethernet port.
//! The web site displays a few lines of text, and a counter that increments
//! each time the page is sent.
//!
//! For additional details on uIP, refer to the uIP web page at:
//! http://www.sics.se/~adam/uip/
//
//*****************************************************************************


#ifndef NULL
#define NULL (void *)0
#endif /* NULL */



//*****************************************************************************
//
// Defines for setting up the system clock.
//
//*****************************************************************************
#define SYSTICKHZ               CLOCK_CONF_SECOND
#define SYSTICKMS               (1000 / SYSTICKHZ)
#define SYSTICKUS               (1000000 / SYSTICKHZ)
#define SYSTICKNS               (1000000000 / SYSTICKHZ)

//*****************************************************************************
//
// Macro for accessing the Ethernet header information in the buffer.
//
//*****************************************************************************
#define BUF                     ((struct uip_eth_hdr *)&uip_buf[0])

//*****************************************************************************
//
// A set of flags.  The flag bits are defined as follows:
//
//     0 -> An indicator that a SysTick interrupt has occurred.
//     1 -> An RX Packet has been received.
//
//*****************************************************************************
#define FLAG_SYSTICK            0
#define FLAG_RXPKT              1
static volatile unsigned long g_ulFlags;

//*****************************************************************************
//
// A system tick counter, incremented every SYSTICKMS.
//
//*****************************************************************************
volatile unsigned long g_ulTickCounter = 0;

//*****************************************************************************
//
// Default TCP/IP Settings for this application.
//
// Default to Link Local address ... (169.254.1.0 to 169.254.254.255).  Note:
// This application does not implement the Zeroconf protocol.  No ARP query is
// issued to determine if this static IP address is already in use.
//
// TODO:  Uncomment the following #define statement to enable STATIC IP
// instead of DHCP.
//
//*****************************************************************************
/* use static IP */
#define USE_STATIC_IP																	 

#ifndef DEFAULT_IPADDR0
#define DEFAULT_IPADDR0         10 //169
#endif

#ifndef DEFAULT_IPADDR1
#define DEFAULT_IPADDR1         0 //254
#endif

#ifndef DEFAULT_IPADDR2
#define DEFAULT_IPADDR2         0 //19
#endif

#ifndef DEFAULT_IPADDR3
#define DEFAULT_IPADDR3         105
#endif

#ifndef DEFAULT_NETMASK0
#define DEFAULT_NETMASK0        255
#endif

#ifndef DEFAULT_NETMASK1
#define DEFAULT_NETMASK1        255
#endif

#ifndef DEFAULT_NETMASK2
#define DEFAULT_NETMASK2        255
#endif

#ifndef DEFAULT_NETMASK3
#define DEFAULT_NETMASK3        0
#endif


//*****************************************************************************
//
// UIP Timers (in MS)
//
//*****************************************************************************
#define UIP_PERIODIC_TIMER_MS   500
#define UIP_ARP_TIMER_MS        10000

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif

//*****************************************************************************
//
// The interrupt handler for the SysTick interrupt.
//
//*****************************************************************************
void
SysTickIntHandler(void)
{
    //
    // Increment the system tick count.
    // 
    g_ulTickCounter++;

    //
    // Indicate that a SysTick interrupt has occurred.
    //
    HWREGBITW(&g_ulFlags, FLAG_SYSTICK) = 1;
}

//*****************************************************************************
//
//! When using the timer module in UIP, this function is required to return
//! the number of ticks.  Note that the file "clock-arch.h" must be provided
//! by the application, and define CLOCK_CONF_SECONDS as the number of ticks
//! per second, and must also define the typedef "clock_time_t".
//
//*****************************************************************************
clock_time_t
clock_time(void)
{
    return((clock_time_t)g_ulTickCounter);
}

//*****************************************************************************
//
// The interrupt handler for the Ethernet interrupt.
//
//*****************************************************************************
void
EthernetIntHandler(void)
{
    unsigned long ulTemp;

    //
    // Read and Clear the interrupt.
    //
    ulTemp = EthernetIntStatus(ETH_BASE, false);
    EthernetIntClear(ETH_BASE, ulTemp);

    //
    // Check to see if an RX Interrupt has occured.
    //
    if(ulTemp & ETH_INT_RX)
    {
        //
        // Indicate that a packet has been received.
        //
        HWREGBITW(&g_ulFlags, FLAG_RXPKT) = 1;

        //
        // Disable Ethernet RX Interrupt.
        //
        EthernetIntDisable(ETH_BASE, ETH_INT_RX);
    }
}

//*****************************************************************************
//
// Display a uIP type IP Address.
//
//*****************************************************************************
static void
DisplayIPAddress(void *ipaddr, unsigned long ulCol, unsigned long ulRow)
{
    char pucBuf[16];
    unsigned char *pucTemp = (unsigned char *)ipaddr;

    //
    // Convert the IP Address into a string.
    //
    usprintf(pucBuf, "%d.%d.%d.%d", pucTemp[0], pucTemp[1], pucTemp[2],
             pucTemp[3]);

	//
	UARTprintf("IP Addr: %d.%d.%d.%d\n", pucTemp[0], pucTemp[1], pucTemp[2],
             pucTemp[3]);

    //
    // Display the string.
    //
    RIT128x96x4StringDraw(pucBuf, ulCol, ulRow, 15);
}


//*****************************************************************************
//
// Callback for when DHCP client has been configured.
//
//*****************************************************************************
/*
void
dhcpc_configured(const struct dhcpc_state *s)
{
    uip_sethostaddr(&s->ipaddr);
    uip_setnetmask(&s->netmask);
    uip_setdraddr(&s->default_router);
    DisplayIPAddress((void *)&s->ipaddr, 18, 24);
}
*/

/*******************************WebClient Set***************************************/
//DNS 找到对应服务器IP
void resolv_found(char *name, u16_t *ipaddr)			
{
	if (ipaddr == NULL) 
	{
		UARTprintf("Host '%s' not found.\n", name);
	} 
	else 
	{
		UARTprintf("Found name '%s' = %d.%d.%d.%d\n", name,
									htons(ipaddr[0]) >> 8,
									htons(ipaddr[0]) & 0xff,
									htons(ipaddr[1]) >> 8,
									htons(ipaddr[1]) & 0xff);
		if (webclient_get("10.0.0.100", 80, "/sendnotify?cgi"))       
		{
			UARTprintf("the connection was initiated");
		}
		else
		{
			UARTprintf("the host name could not be found in the cache  or TCP connection could not be created.");
		}
	}	   
}


void webclient_closed(void)
{
	UARTprintf("Webclient: connection closed\n");
}

void webclient_aborted(void)
{
	UARTprintf("Webclient: connection aborted\n");
}

void webclient_timedout(void)
{
	UARTprintf("Webclient: connection timed out\n");
}

void webclient_connected(void)
{
	UARTprintf("Webclient: connected, waiting for data...\n");
}

void webclient_datahandler(char *data, u16_t len)
{
	UARTprintf("Webclient: got %d bytes of data.\n", len);
}


//*****************************************************************************
//
// This example demonstrates the use of the Ethernet Controller with the uIP
// TCP/IP stack.
//
//*****************************************************************************
int
main(void)
{
    uip_ipaddr_t ipaddr;
    static struct uip_eth_addr sTempAddr;
    long lPeriodicTimer, lARPTimer, lPacketLength;
    unsigned long ulUser0, ulUser1;
    unsigned long ulTemp;

    //
    // Set the clocking to run directly from the crystal.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_8MHZ);

    //
    // Enable the peripherals used by the application.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure the GPIOs used to read the state of the on-board push buttons.
    //
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,
                         GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPadConfigSet(GPIO_PORTE_BASE,
                     GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA,
                     GPIO_PIN_TYPE_STD_WPU);

    //
    // Configure the LED, speaker, and UART GPIOs as required.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypePWM(GPIO_PORTG_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);

    //
    // Configure the first UART for 115,200, 8-N-1 operation.
    //
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         UART_CONFIG_PAR_NONE));
    UARTEnable(UART0_BASE);

    //
    // Initialize the OLED display.
    //
    RIT128x96x4Init(1000000);
    RIT128x96x4StringDraw("uIP WebClient", 12, 0, 15);

    //
    // Enable and Reset the Ethernet Controller.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ETH);
    SysCtlPeripheralReset(SYSCTL_PERIPH_ETH);

    //
    // Enable Port F for Ethernet LEDs.
    //  LED0        Bit 3   Output
    //  LED1        Bit 2   Output
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeEthernetLED(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3);

    //
    // Configure SysTick for a periodic interrupt.
    //
    SysTickPeriodSet(SysCtlClockGet() / SYSTICKHZ);
    SysTickEnable();
    SysTickIntEnable();

    //
    // Intialize the Ethernet Controller and disable all Ethernet Controller
    // interrupt sources.
    //
    EthernetIntDisable(ETH_BASE, (ETH_INT_PHY | ETH_INT_MDIO | ETH_INT_RXER |
                       ETH_INT_RXOF | ETH_INT_TX | ETH_INT_TXER | ETH_INT_RX));
    ulTemp = EthernetIntStatus(ETH_BASE, false);
    EthernetIntClear(ETH_BASE, ulTemp);

    //
    // Initialize the Ethernet Controller for operation.
    //
    EthernetInitExpClk(ETH_BASE, SysCtlClockGet());

    //
    // Configure the Ethernet Controller for normal operation.
    // - Full Duplex
    // - TX CRC Auto Generation
    // - TX Padding Enabled
    //
    EthernetConfigSet(ETH_BASE, (ETH_CFG_TX_DPLXEN | ETH_CFG_TX_CRCEN |
                                 ETH_CFG_TX_PADEN));

    //
    // Wait for the link to become active.
    // 
    RIT128x96x4StringDraw("Waiting for Link", 12, 8, 15);
    ulTemp = EthernetPHYRead(ETH_BASE, PHY_MR1);
    while ((ulTemp & 0x0004) == 0)
    {
        ulTemp = EthernetPHYRead(ETH_BASE, PHY_MR1);
    }
    RIT128x96x4StringDraw("Link Established", 12, 16, 15);

    //
    // Enable the Ethernet Controller.
    //
    EthernetEnable(ETH_BASE);

    //
    // Enable the Ethernet interrupt.
    //
    IntEnable(INT_ETH);

    //
    // Enable the Ethernet RX Packet interrupt source.
    //
    EthernetIntEnable(ETH_BASE, ETH_INT_RX);

    //
    // Enable all processor interrupts.
    //
    IntMasterEnable();

    //
    // Initialize the UART as a console for text I/O.
    //
    UARTStdioInit(0);
    UARTprintf("Start...\n");
    
	UARTprintf("uip_init\n");

    //
    // Initialize the uIP TCP/IP stack.
    //
    uip_init();
#ifdef USE_STATIC_IP
    uip_ipaddr(ipaddr, DEFAULT_IPADDR0, DEFAULT_IPADDR1, DEFAULT_IPADDR2,
               DEFAULT_IPADDR3);
    uip_sethostaddr(ipaddr);
    DisplayIPAddress(ipaddr, 18, 24);
    uip_ipaddr(ipaddr, DEFAULT_NETMASK0, DEFAULT_NETMASK1, DEFAULT_NETMASK2,
               DEFAULT_NETMASK3);
    uip_setnetmask(ipaddr);
#else
    uip_ipaddr(ipaddr, 0, 0, 0, 0);
    uip_sethostaddr(ipaddr);
    DisplayIPAddress(ipaddr, 18, 24);
    uip_ipaddr(ipaddr, 0, 0, 0, 0);
    uip_setnetmask(ipaddr);
#endif

    //
    // Configure the hardware MAC address for Ethernet Controller filtering of
    // incoming packets.
    //
    // For the Ethernet Eval Kits, the MAC address will be stored in the
    // non-volatile USER0 and USER1 registers.  These registers can be read
    // using the FlashUserGet function, as illustrated below.
    //
    FlashUserGet(&ulUser0, &ulUser1);
    if ((ulUser0 == 0xffffffff) || (ulUser1 == 0xffffffff))
    {
        //
        // We should never get here.  This is an error if the MAC address has
        // not been programmed into the device.  Exit the program.
        //
        RIT128x96x4StringDraw("MAC Address", 0, 16, 15);
        RIT128x96x4StringDraw("Not Programmed!", 0, 24, 15);
        while (1)
        {
        }
    }

    //
    // Convert the 24/24 split MAC address from NV ram into a 32/16 split MAC
    // address needed to program the hardware registers, then program the MAC
    // address into the Ethernet Controller registers.
    //
    sTempAddr.addr[0] = ((ulUser0 >>  0) & 0xff);
    sTempAddr.addr[1] = ((ulUser0 >>  8) & 0xff);
    sTempAddr.addr[2] = ((ulUser0 >> 16) & 0xff);
    sTempAddr.addr[3] = ((ulUser1 >>  0) & 0xff);
    sTempAddr.addr[4] = ((ulUser1 >>  8) & 0xff);
    sTempAddr.addr[5] = ((ulUser1 >> 16) & 0xff);

    //
    // Program the hardware with it's MAC address (for filtering).
    //
    EthernetMACAddrSet(ETH_BASE, (unsigned char *)&sTempAddr);
    uip_setethaddr(sTempAddr);

#ifndef USE_STATIC_IP
    //
    // Initialize the DHCP Client Application.
    //
    dhcpc_init(&sTempAddr.addr[0], 6);
    dhcpc_request();
#endif

	UARTprintf("webclient_init\n");

    //
    // Initialize the TCP/IP Application.
    //
    webclient_init();
    
    resolv_init();
    uip_ipaddr(ipaddr, 8, 8, 8, 8);
    resolv_conf(ipaddr);
	DisplayIPAddress(ipaddr, 18, 32);
    resolv_query("winginsky.oicp.net");

    //
    // Main Application Loop.
    //
    lPeriodicTimer = 0;
    lARPTimer = 0;
    while (true)
    {
        //
        // Wait for an event to occur.  This can be either a System Tick event,
        // or an RX Packet event.
        //
        while(!g_ulFlags)
        {
        }

        //
        // If SysTick, Clear the SysTick interrupt flag and increment the
        // timers.
        //
        if(HWREGBITW(&g_ulFlags, FLAG_SYSTICK) == 1)
        {
            HWREGBITW(&g_ulFlags, FLAG_SYSTICK) = 0;
            lPeriodicTimer += SYSTICKMS;
            lARPTimer += SYSTICKMS;
        }

        //
        // Check for an RX Packet and read it.
        //
        lPacketLength = EthernetPacketGetNonBlocking(ETH_BASE, uip_buf,
                                                     sizeof(uip_buf));
        if (lPacketLength > 0)
        {
            //
            // Set uip_len for uIP stack usage.
            //
            uip_len = (unsigned short)lPacketLength;

            //
            // Clear the RX Packet event and renable RX Packet interrupts.
            //
            if(HWREGBITW(&g_ulFlags, FLAG_RXPKT) == 1)
            {
                HWREGBITW(&g_ulFlags, FLAG_RXPKT) = 0;
                EthernetIntEnable(ETH_BASE, ETH_INT_RX);
            }

            //
            // Process incoming IP packets here.
            //
            if (BUF->type == htons(UIP_ETHTYPE_IP))
            {
                uip_arp_ipin();
                uip_input();

                //
                // If the above function invocation resulted in data that
                // should be sent out on the network, the global variable
                // uip_len is set to a value > 0.
                //
                if (uip_len > 0)
                {
                    uip_arp_out();
                    EthernetPacketPut(ETH_BASE, uip_buf, uip_len);
                    uip_len = 0;
                }
            }

            //
            // Process incoming ARP packets here.
            //
            else if (BUF->type == htons(UIP_ETHTYPE_ARP))
            {
                uip_arp_arpin();

                //
                // If the above function invocation resulted in data that
                // should be sent out on the network, the global variable
                // uip_len is set to a value > 0.
                //
                if (uip_len > 0)
                {
                    EthernetPacketPut(ETH_BASE, uip_buf, uip_len);
                    uip_len = 0;
                }
            }
        }

        //
        // Process TCP/IP Periodic Timer here.
        //
        if (lPeriodicTimer > UIP_PERIODIC_TIMER_MS)
        {
            lPeriodicTimer = 0;
            for (ulTemp = 0; ulTemp < UIP_CONNS; ulTemp++)
            {
                uip_periodic(ulTemp);

                //
                // If the above function invocation resulted in data that
                // should be sent out on the network, the global variable
                // uip_len is set to a value > 0.
                //
                if(uip_len > 0)
                {
                    uip_arp_out();
                    EthernetPacketPut(ETH_BASE, uip_buf, uip_len);
                    uip_len = 0;
                }
            }

#if UIP_UDP
            for(ulTemp = 0; ulTemp < UIP_UDP_CONNS; ulTemp++)
            {
                uip_udp_periodic(ulTemp);

                //
                // If the above function invocation resulted in data that
                // should be sent out on the network, the global variable
                // uip_len is set to a value > 0.
                //
                if(uip_len > 0)
                {
                    uip_arp_out();
                    EthernetPacketPut(ETH_BASE, uip_buf, uip_len);
                    uip_len = 0;
                }
            }
#endif // UIP_UDP
        }

        //
        // Process ARP Timer here.
        //
        if(lARPTimer > UIP_ARP_TIMER_MS)
        {
            lARPTimer = 0;
            uip_arp_timer();
        }
    }
}

