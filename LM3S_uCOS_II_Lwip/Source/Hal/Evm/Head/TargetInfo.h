/****************************************Copyright (c)****************************************************
**                   Texas Instruments Semiconductor Technologies Co.,LTD.                              **
**                                                                                                      **                                     
**                                 http://www.ti.com                                                    **
**                                                                                                      **
**--------------File Info---------------------------------------------------------------------------------
** File Name:               main.h                                                                      ** 
** Last modified Date:      12-20-2010                                                                  **
** Last Version:            1.0                                                                         **
** Description:             The main function example template                                          **
**                                                                                                      **
**--------------------------------------------------------------------------------------------------------
** Created By:              long.luo                                                                    **
** Created date:            10-04-2013                                                                  **
** Version:                 1.0                                                                         **
** Descriptions:            The original version                                                        **
**                                                                                                      **
*********************************************************************************************************/
#ifndef __DATA_H 
#define __DATA_H 

#ifdef __cplusplus
extern "C" {
#endif

#define  MAX_ADC_CHN    8

typedef struct 
{
    uint8  uHour;
    uint8  uMin;
    uint8  uSec;    
}stCurTime;

typedef struct 
{
    uint32 ADC_EN;              // ADC channel enable flag
    uint16 ADC_CH[MAX_ADC_CHN];    
}stCurADC;

typedef struct 
{
    uint32      uVcc;       // Target Vcc, lsd is 0.01V
    uint32      uTemp;      // Target temperature, lsd is 0.1C
    stCurADC    stADC;      // 
    stCurTime   stTime;     //
}stCurPhysics;

#ifdef __cplusplus
    }
#endif


#endif
/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/

