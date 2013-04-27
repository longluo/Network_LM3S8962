/****************************************Copyright (c)****************************************************
**                   Texas Instruments Semiconductor Technologies Co.,LTD.                              **
**                                                                                                      **                                     
**                                 http://www.ti.com                                                    **
**                                                                                                      **
**--------------File Info---------------------------------------------------------------------------------
** File Name:               isr.c                                                                       ** 
** Last modified Date:      12-20-2010                                                                  **
** Last Version:            1.0                                                                         **
** Description:             The interrupt service function                                              **
**                                                                                                      **
**--------------------------------------------------------------------------------------------------------
** Created By:              long.luo                                                                    **
** Created date:            10-04-2013                                                                  **
** Version:                 1.0                                                                         **
** Descriptions:            The original version                                                        **
**                                                                                                      **
*********************************************************************************************************/
#include <includes.h>

extern volatile tBoolean INTflag;

/*********************************************************************************************************
** Function name:           keyISR                                                                      **
** Descriptions:                                                                                        **
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
void keyISR (void)
{
    uint32 IntStatus;

    #if OS_CRITICAL_METHOD == 3
    OS_CPU_SR  cpu_sr;
    #endif 
    
    OS_ENTER_CRITICAL();      // 关中断                      
    OSIntNesting++;           // 操作系统中断嵌套层数加1     
    OS_EXIT_CRITICAL();
    
    IntStatus = GPIOPinIntStatus(GPIO_PORTE_BASE,true);
    GPIOPinIntClear(GPIO_PORTE_BASE,IntStatus);
    
    if (IntStatus & GPIO_PIN_2)
    {
        INTflag = true;
    }
    else if (IntStatus & GPIO_PIN_3)
    {
        INTflag = true;
    }

    OSIntExit();
}
