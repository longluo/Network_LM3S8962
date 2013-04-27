/****************************************Copyright (c)****************************************************
**                   Texas Instruments Semiconductor Technologies Co.,LTD.                              **
**                                                                                                      **                                     
**                                 http://www.ti.com                                                    **
**                                                                                                      **
**--------------File Info---------------------------------------------------------------------------------
** File Name:               includes.h                                                                  ** 
** Last modified Date:      12-20-2010                                                                  **
** Last Version:            1.0                                                                         **
** Description:             uCOS-II's include file                                                      **
**                                                                                                      **
**--------------------------------------------------------------------------------------------------------
** Created By:              long.luo                                                                    **
** Created date:            10-04-2013                                                                  **
** Version:                 1.0                                                                         **
** Descriptions:            The original version                                                        **
**                                                                                                      **
*********************************************************************************************************/
#ifndef  __INCLUDES_H
#define  __INCLUDES_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************************************************
  Date types(Compiler specific)          
*********************************************************************************************************/
typedef unsigned char   uint8;                                          /* Unsigned  8 bit quantity     */
typedef signed   char   int8;                                           /* Signed    8 bit quantity     */
typedef unsigned short  uint16;                                         /* Unsigned  16 bit quantity    */
typedef signed   short  int16;                                          /* Signed    16 bit quantity    */
typedef unsigned int    uint32;                                         /* Unsigned  32 bit quantity    */
typedef signed   int    int32;                                          /* Signed    32 bit quantity    */
typedef float           fp32;                                           /* Single    precision          */
                                                                        /* floating  point              */
typedef double          fp64;                                           /* Double    precision          */
                                                                        /* floating  point              */

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL  0
#endif


/*********************************************************************************************************
  Standard header files 
*********************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/*********************************************************************************************************
  Driver's header files  
*********************************************************************************************************/

#include <lm3s8962.h>
#include <hw_memmap.h>
#include <hw_types.h>
#include <hw_ints.h>


#include <adc.h>
#include <can.h>
#include <comp.h>
#include <cpu.h>
#include <debug.h>
#include <ethernet.h>
#include <flash.h>
#include <gpio.h>
#include <hibernate.h>
#include <i2c.h>
#include <interrupt.h>
#include <mpu.h>
#include <pin_map.h>
#include <pwm.h>
#include <qei.h>
#include <ssi.h>
#include <sysctl.h>
#include <systick.h>
#include <timer.h>
#include <uart.h>
#include <watchdog.h>

/*********************************************************************************************************
  Port's header files 
*********************************************************************************************************/
//#include <os_cfg.h>
#include <os_cpu.h>
#include <ucos_ii.h>
#include <Target.h>             
#include <rit128x96x4.h>
#include <TargetInfo.h>

/*********************************************************************************************************
  User's header files 
*********************************************************************************************************/
#include <Main.h>

#ifdef __cplusplus
    }
#endif

#endif
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/
