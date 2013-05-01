/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Network_LM3S8962\LM3S_uIP_Client\Source\uip-1.0\uip\uiplib.h
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      Various uIP library functions.
** 
** Version: 1.1
** Date created: 23:13:38,01/05/2013
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#ifndef __UIPLIB_H__
#define __UIPLIB_H__

/**
 * \addtogroup uipconvfunc
 * @{
 */

/**
 * Convert a textual representation of an IP address to a numerical representation.
 *
 * This function takes a textual representation of an IP address in
 * the form a.b.c.d and converts it into a 4-byte array that can be
 * used by other uIP functions.
 *
 * \param addrstr A pointer to a string containing the IP address in
 * textual form.
 *
 * \param addr A pointer to a 4-byte array that will be filled in with
 * the numerical representation of the address.
 *
 * \retval 0 If the IP address could not be parsed.
 * \retval Non-zero If the IP address was parsed.
 */
unsigned char uiplib_ipaddrconv(char *addrstr, unsigned char *addr);

/** @} */

#endif /* __UIPLIB_H__ */

