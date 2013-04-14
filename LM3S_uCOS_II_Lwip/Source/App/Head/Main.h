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
#ifndef __MAIN_H 
#define __MAIN_H 

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************************************************
  TASK PRIORITIES 
*********************************************************************************************************/      
#define  TASK_START_PRIO              0
#define  TASK_UART_PRIO               1
#define  TASK_LED_PRIO                2
#define  TASK_KEY_PRIO                3
#define  TASK_DISP_PRIO               4
#define  TASK_TEMP_PRIO               5
#define	 TASK_BUZ_PRIO				  6
#define  TASK_RTC_PRIO                7

              
/*********************************************************************************************************
  TASK STACK SIZES  
*********************************************************************************************************/
#define  TASK_START_STK_SIZE          50
#define  TASK_UART_STK_SIZE           50
#define  TASK_LED_STK_SIZE            50
#define  TASK_DISP_STK_SIZE           50
#define  TASK_KEY_STK_SIZE            50
#define  TASK_TEMP_STK_SIZE           50
#define  TASK_BUZ_STK_SIZE			  50
#define  TASK_RTC_STK_SIZE            50


#ifdef __cplusplus
    }
#endif


#endif

/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/

