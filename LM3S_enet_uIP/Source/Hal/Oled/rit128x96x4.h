//*****************************************************************************
//
// rit128x96x4.h - Prototypes for the driver for the RITEK 128x96x4 graphical
//                   OLED display.
//
// Copyright (c) 2007-2010 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 6459 of the EK-LM3S8962 Firmware Package.
//
//*****************************************************************************

#ifndef __RIT128X96X4_H__
#define __RIT128X96X4_H__

/*+++ added by luolong start */
//#include "grlib/grlib.h"
/*--- added by luolong end */

//*****************************************************************************
//
// Prototypes for the driver APIs.
//
//*****************************************************************************
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

/*+++ added by luolong start */
/*
extern void RIT128x96x4GUIInit(void);
extern void RIT128x96x4WriteOneByte(long lX,long lY,unsigned long ulValue);
extern unsigned char RIT128x96x4ReadValue(long lX,long lY);
extern void RIT128x96x4DotDraw(void * pvDisplayData,long lX,long lY,unsigned long ulValue);
extern void RIT128x96x4PixelDraw(void *pvDisplayData, long lX, long lY, unsigned long ulValue);
extern void RIT128x96x4PixelDrawMultiple(void *pvDisplayData, long lX,
										long lY, long lX0, long lCount,
										long lBPP,
										const unsigned char *pucData,
										const unsigned char *pucPalette);
extern void RIT128x96x4LineDrawH(void *pvDisplayData, long lX1, long lX2, long lY, unsigned long ulValue);
extern void RIT128x96x4LineDrawV(void *pvDisplayData, long lX, long lY1, long lY2, unsigned long ulValue);
extern void RIT128x96x4RectFill(void *pvDisplayData, const tRectangle *pRect, unsigned long ulValue);
extern unsigned long RIT128x96x4ColorTranslate(void *pvDisplayData, unsigned long ulValue);
extern void RIT128x96x4Flush(void *pvDisplayData);
extern void RIT128x96x4FillScreen(unsigned long ulValue);
*/
/*--- added by luolong end */

#endif // __RIT128X96X4_H__
