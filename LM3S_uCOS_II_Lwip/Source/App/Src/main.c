/****************************************Copyright (c)****************************************************
**                   Texas Instruments Semiconductor Technologies Co.,LTD.                              **
**                                                                                                      **                                     
**                                 http://www.ti.com                                                    **
**                                                                                                      **
**--------------File Info---------------------------------------------------------------------------------
** File Name:               main.c                                                                      ** 
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

#include <includes.h>


/*********************************************************************************************************
**  CONSTANTS                                                                                           **
*********************************************************************************************************/

/*********************************************************************************************************
  VARIABLES 
*********************************************************************************************************/
static OS_STK  GstkStart[TASK_START_STK_SIZE];                          /*  The stack of start task     */
                                                                        
static OS_STK Task_LedStk[TASK_LED_STK_SIZE];                           /*  Led task stack              */
static OS_STK Task_UartStk[TASK_UART_STK_SIZE];
static OS_STK Task_KeyStk[TASK_KEY_STK_SIZE];
static OS_STK Task_DispStk[TASK_DISP_STK_SIZE];
static OS_STK Task_TempStk[TASK_TEMP_STK_SIZE];
static OS_STK Task_RTCStk[TASK_RTC_STK_SIZE];
static OS_STK Task_BuzStk[TASK_BUZ_STK_SIZE];


/*********************************************************************************************************
**   FUNCTION PROTOTYPES                                                                                **
*********************************************************************************************************/
static void taskStart (void  *parg);                                    /*  The start task              */
static void taskLed (void  *parg);
static void taskUart(void *parg);
static void taskDisp (void *parg);
static void taskKey (void *parg);
static void taskTemp (void *parg);                                     
static void taskRTC (void *parg);
static void taskBuz(void *parg);

extern stCurPhysics TargetInfo;


/*********************************************************************************************************
** Function name:           main                                                                        **
** Descriptions:                                                                                        **
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
int main (void)
{
    //IntDisAll();                                                        /* Disable all the interrupts   */
    
    OSInit();                                                           /*  Initialize the kernel of uC */

    OSTaskCreate ( taskStart,                                          
                   (void *)0, 
                   &GstkStart[TASK_START_STK_SIZE-1], 
                   TASK_START_PRIO );                                   /*  Initialize the start task   */
    OSStart();                                                          /*  Start uC/OS-II              */
    return(0) ;
}


/*********************************************************************************************************
** Function name:           taskStart                                                                   **
** Descriptions:            Start task                                                                  **
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          none                                                                        **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
static void taskStart (void  *parg)
{
    (void)parg;

    InitTarget();                                                       /*  Initialize the target's MCU */

    #if OS_TASK_STAT_EN > 0
    OSStatInit();                                                       /*  Enable statistics           */
    #endif

    /*  Create the other tasks here.     */
    OSTaskCreate (taskLed, (void *)0,           
                  &Task_LedStk[TASK_LED_STK_SIZE - 1], 
                  TASK_LED_PRIO);                                       /*  Initialize taskLed           */ 

/*
    OSTaskCreate(taskUart, (void *)0, 
    			&Task_UartStk[TASK_UART_STK_SIZE - 1],
    			TASK_UART_PRIO);
    
    OSTaskCreate (taskKey, (void *)0,
                  &Task_KeyStk[TASK_KEY_STK_SIZE - 1],
                  TASK_KEY_PRIO);
*/               

    OSTaskCreate (taskDisp, (void *)0,          
                  &Task_DispStk[TASK_DISP_STK_SIZE - 1], 
                  TASK_DISP_PRIO);         
                  
    OSTaskCreate (taskTemp, (void*)0,
                  &Task_TempStk[TASK_TEMP_STK_SIZE - 1],
                  TASK_TEMP_PRIO);   

    OSTaskCreate(taskRTC, (void*)0,
                 &Task_RTCStk[TASK_RTC_STK_SIZE - 1],
                 TASK_RTC_PRIO); 
/*
	OSTaskCreate(taskBuz, (void*)0,
				&Task_BuzStk[TASK_BUZ_STK_SIZE - 1],
				TASK_BUZ_PRIO);
				*/
                 
    while (1) 
    {                             
        OSTaskSuspend(OS_PRIO_SELF);                               /*  The start task can be pended here */
    }
}


/*********************************************************************************************************
**  The other tasks                                                                                     **
*********************************************************************************************************/
/*  Add the other tasks here . */

/*********************************************************************************************************
** Function name:           taskLed                                                                     **
** Descriptions:            LED Task                                                                    **
** input parameters:        *parg                                                                       **
** output parameters:       none                                                                        **
** Returned value:          none                                                                        **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
static  void  taskLed (void  *parg)
{
    (void)parg;

    LedOn(0);
    while (1) 
    {
        LedToggle(0);                                                   /*  Lighting LED                */              
        OSTimeDly(OS_TICKS_PER_SEC/2);                                  /*  Delay 0.5s                  */                  
    }
}


/*********************************************************************************************************
** Function name:           taskUart                                                                     **
** Descriptions:            UART Task                                                                    **
** input parameters:        *parg                                                                       **
** output parameters:       none                                                                        **
** Returned value:          none                                                                        **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            12-04-2013                                                                  **
*********************************************************************************************************/
static  void  taskUart (void  *parg)
{
    (void)parg;

    while (1) 
    {
		//UARTCharPut(unsigned long ulBase, unsigned char ucData);
        //OSTimeDly(OS_TICKS_PER_SEC);                                  /*  Delay 0.5s                  */                  
    }
}


/*********************************************************************************************************
** Function name:           taskKey                                                                     **
** Descriptions:            DISP Task                                                                   **
** input parameters:        *parg                                                                       **
** output parameters:       none                                                                        **
** Returned value:          none                                                                        **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
static void taskKey (void *parg)
{
    //uint8 KeySta = 0xFF;
    //static uint8 oldKeySta  = 0xFF;
    
    // oldKeySta = KeySta();
    while (1)
    {
        
    }
}


/*********************************************************************************************************
** Function name:           taskDisp                                                                    **
** Descriptions:            DISP Task                                                                   **
** input parameters:        *parg                                                                       **
** output parameters:       none                                                                        **
** Returned value:          none                                                                        **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
static void taskDisp (void  *parg)
{
    INT16U OSVersion = 0;
    int8 buf[20];

    OSVersion = OS_VERSION;
    
    RIT128x96x4Init(1000000);
                             
    (void) parg;
    while (1)
    {               
        sprintf(buf,"uC/OS-II v%ld.%ld ", OS_VERSION / 100, (OS_VERSION % 100));
        RIT128x96x4StringDraw(buf, 25, 10, 15);

        sprintf(buf,"===================");
        RIT128x96x4StringDraw(buf, 6, 20, 15);  
        
       
        sprintf(buf,"Temp: %ld.%ld C",TargetInfo.uTemp/1024,(TargetInfo.uTemp%1024)/102);
        RIT128x96x4StringDraw(buf, 10, 35, 15);
       
        sprintf(buf,"Time: %02d:%02d:%02d", TargetInfo.stTime.uHour,TargetInfo.stTime.uMin,TargetInfo.stTime.uSec);
        RIT128x96x4StringDraw(buf, 10, 45, 15);
        
        OSTimeDly(OS_TICKS_PER_SEC);
    }
}


/*********************************************************************************************************
** Function name:           taskRTC                                                                     **
** Descriptions:            DISP Task                                                                   **
** input parameters:        *parg                                                                       **
** output parameters:       none                                                                        **
** Returned value:          none                                                                        **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
static void taskRTC(void *parg)
{
    (void) parg;

    TargetInfo.stTime.uHour = 0;
    TargetInfo.stTime.uMin = 0;
    TargetInfo.stTime.uSec = 0;
    
    while (1)
    {
        TargetInfo.stTime.uSec++;
        if (60 <= TargetInfo.stTime.uSec)
        {
            TargetInfo.stTime.uSec = 0;
            TargetInfo.stTime.uMin ++;
            if (60 <= TargetInfo.stTime.uMin)
            {
                TargetInfo.stTime.uMin = 0;
                TargetInfo.stTime.uHour++;
                if (24 <= TargetInfo.stTime.uHour)
                {
                    TargetInfo.stTime.uHour = 0;
                }
            }
        }
        
        OSTimeDly(OS_TICKS_PER_SEC);
    }
}


/*********************************************************************************************************
** Function name:           taskTemp                                                                    **
** Descriptions:            DISP Task                                                                   **
** input parameters:        *parg                                                                       **
** output parameters:       none                                                                        **
** Returned value:          none                                                                        **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
static void taskTemp(void *parg)
{
    unsigned long ulValue = 0;

    InitADC();

    TargetInfo.uVcc = 0;
    TargetInfo.uTemp = 0;

    while (1)
    {
        ulValue = ADCSample();
        TargetInfo.uTemp = InvertTemperature(ulValue);
        OSTimeDly(OS_TICKS_PER_SEC * 3);
    }
}


/*********************************************************************************************************
** Function name:           taskBuz                                                                     **
** Descriptions:            Buzzer Task                                                                 **
** input parameters:        *parg                                                                       **
** output parameters:       none                                                                        **
** Returned value:          none                                                                        **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            12-04-2013                                                                  **
*********************************************************************************************************/
static void taskBuz(void *parg)
{
	TargetInfo.stPWM.ulFrequency = 440;
	TargetInfo.stPWM.ulDutyCycle = 50;
	
	SetPWMDutyCycle(TargetInfo.stPWM.ulDutyCycle);
	BuzFrequency(TargetInfo.stPWM.ulFrequency);
	
    while (1)
    {
    	BuzToggle();
        //OSTimeDly(OS_TICKS_PER_SEC / 2);
        OSTimeDly(OS_TICKS_PER_SEC);
    }
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/

