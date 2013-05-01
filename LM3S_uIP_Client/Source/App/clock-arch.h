/************************************************************************************
** File: - E:\ARM\lm3s8962projects\Network_LM3S8962\LM3S_uIP_Client\Source\App\clock-arch.h
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      clock-arch.h - uIP Project Specific Clock-Architecture header file.
** 
** Version: 1.1
** Date created: 22:48:29,01/05/2013
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#ifndef __CLOCK_ARCH_H__
#define __CLOCK_ARCH_H__

//
// Define how many clock ticks in one second.
// Note:  This should match the value of SYSTICKHZ in the main program.
//
#define CLOCK_CONF_SECOND       100

//
// Define the clock type used for returning system ticks.
//
typedef unsigned long clock_time_t;

#endif // __CLOCK_ARCH_H__

