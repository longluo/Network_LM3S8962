/****************************************Copyright (c)****************************************************
**                          Texas Instruments Incorporated.                                             **  
**                 All rights reserved.Software License Agreement                                       **                                     
**                                 http://www.ti.com                                                    **
**                                                                                                      **
**--------------File Info---------------------------------------------------------------------------------
** File Name:               rit128x96x4.h                                                               ** 
** Last modified Date:      12-20-2010                                                                  **
** Last Version:            1.0                                                                         **
** Description:             Texas Instruments (TI) is supplying this software for use solely and        **
**                          exclusively on TI's microcontroller products. The software is owned by TI   **
**                          and/or its suppliers, and is protected under applicable copyright           **
**                          laws. You may not combine this software with "viral" open-source            **
**                          software in order to form a larger program.                                 **
**                          THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.                      **
**                          NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT        **
**                          NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR       **
**                          A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY        **
**                          CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL          **
**                          DAMAGES, FOR ANY REASON WHATSOEVER.                                         **
**                          This is part of revision 6075 of the EK-LM3S8962 Firmware Package.          **                                                                          **
**--------------------------------------------------------------------------------------------------------
** Created By:              long.luo                                                                **
** Created date:            10-04-2013                                                                  **
** Version:                 1.0                                                                         **
** Descriptions:            The original version                                                        **
**                                                                                                      **
*********************************************************************************************************/

#ifndef __RIT128X96X4_H__
#define __RIT128X96X4_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
 Prototypes for the driver APIs.
*********************************************************************************************************/
extern void RIT128x96x4Clear(void);
extern void RIT128x96x4StringDraw(const char *pcStr,
                                    unsigned long ulX,
                                    unsigned long ulY,
                                    unsigned char ucLevel);
extern void RIT128x96x4ImageDraw(const unsigned char *pucImage,
                                   unsigned long ulX,
                                   unsigned long ulY,
                                   unsigned long ulWidth,
                                   unsigned long ulHeight);
extern void RIT128x96x4Init(unsigned long ulFrequency);
extern void RIT128x96x4Enable(unsigned long ulFrequency);
extern void RIT128x96x4Disable(void);
extern void RIT128x96x4DisplayOn(void);
extern void RIT128x96x4DisplayOff(void);



#ifdef __cplusplus
    }
#endif

#endif // __RIT128X96X4_H__



