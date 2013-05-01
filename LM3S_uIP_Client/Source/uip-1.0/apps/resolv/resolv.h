/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Network_LM3S8962\LM3S_uIP_Client\Source\uip-1.0\apps\resolv\resolv.h
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      DNS resolver code header file.
** 
** Version: 1.1
** Date created: 22:38:58,01/05/2013
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/
 
#ifndef __RESOLV_H__
#define __RESOLV_H__

#define	DNS_SERVER_PORT		53
typedef int uip_udp_appstate_t;
void resolv_appcall(void);
#define UIP_UDP_APPCALL resolv_appcall

#include "uipopt.h"

/**
 * Callback function which is called when a hostname is found.
 *
 * This function must be implemented by the module that uses the DNS
 * resolver. It is called when a hostname is found, or when a hostname
 * was not found.
 *
 * \param name A pointer to the name that was looked up.  \param
 * ipaddr A pointer to a 4-byte array containing the IP address of the
 * hostname, or NULL if the hostname could not be found.
 */
void resolv_found(char *name, u16_t *ipaddr);

/* Functions. */
void resolv_conf(const u16_t* dnsserver);
u16_t *resolv_getserver(void);
void resolv_init(void);
u16_t *resolv_lookup(char *name);
void resolv_query(char *name);
//u8_t resolv_hostname(char *name, uip_ipaddr_t *ip, uint32_t timeout_ms);

#endif /* __RESOLV_H__ */

/** @} */

