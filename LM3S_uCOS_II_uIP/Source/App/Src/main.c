/************************************************************************************
** File: - E:\ARM\lm3s8962projects\uCOS_II\uCOS2.52_Keil_Template\User\Main.c
** VENDOR_EDIT
** Copyright (C), Long.Luo 
** 
** Description: 
**      the main function template
** 
** Version: 1.0
** Date created: 23:13:08,17/05/2012
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 	long.luo	2012/10/01		Add a music play task
**
************************************************************************************/

#include <includes.h>
#include "score.h"


/*********************************************************************************************************
  CONSTANTS ��
*********************************************************************************************************/


/*********************************************************************************************************
  VARIABLES ��
*********************************************************************************************************/
static OS_STK Task_StartStk[TASK_START_STK_SIZE];                          /*  The stack of start task     */
                                                                        /*  ������Ķ�ջ              */
static OS_STK Task_LedStk[TASK_LED_STK_SIZE]; 
static OS_STK Task_BuzStk[TASK_BUZ_STK_SIZE];	

static OS_STK Task_MusicStk[TASK_MUSIC_STK_SIZE];

/*********************************************************************************************************
   FUNCTION PROTOTYPES ��������
*********************************************************************************************************/
static void taskStart (void  *parg);                                    /*  The start task  ������    */

/* Long.Luo, 2012/05/22, Add for: , */
static void taskLed (void  *parg);    
static void taskBuz(void *parg);

/* Long.Luo, 2012/10/01, Add for: , */
static void taskMusic(void * parg);
/* Add end. */


/************************************************************************************
** Function: main()
** Routine Description: - 
**      uC/OS��ֲģ��	
** Arguments: 
**  
** Return Value: None
** Remarks:
** 
** Date created: 21:37:52,20/05/2012
** Author: Long.Luo
************************************************************************************/
int main (void)
{
    intDisAll();                                                        /* Disable all the interrupts   */
                                                                        /* �ر������ж�                 */
    OSInit();                                                           /*  Initialize the kernel of uC */
                                                                        /*  OS-II ��ʼ��uC/OS-II���ں�  */
    OSTaskCreate(taskStart,                                          
		          (void *)0, 
				  &Task_StartStk[TASK_START_STK_SIZE-1], 
				  TASK_START_PRIO );                                   /*  Initialize the start task   */
                                                                        /*  ��ʼ��������              */  
    OSStart();                                                          /*  Start uC/OS-II ��uC/OS-II */
    return(0) ;
}


/*********************************************************************************************************
** Function name:           Task_Start	   
** Descriptions:            Start task	
** input parameters:        *p_arg
** output parameters:       ��      
** Returned value:          �� 
*********************************************************************************************************/
static void taskStart (void  *parg)
{
    (void)parg;

    targetInit();                                                       /*  Initialize the target's MCU */
                                                                        /*  ��ʼ��Ŀ�굥Ƭ��            */

    #if OS_TASK_STAT_EN > 0
    OSStatInit();                                                       /*  Enable statistics           */
                                                                        /*  ʹ��ͳ�ƹ���                */
    #endif

  	/*
     *  Create the other tasks here. �����ﴴ����������
     */
	OSTaskCreate(taskLed, 
				(void *)0,   		
				&Task_LedStk[TASK_LED_STK_SIZE-1], 
				TASK_LED_PRIO);   

	OSTaskCreate(taskBuz,
				(void *)0, 
				&Task_BuzStk[TASK_BUZ_STK_SIZE-1],  
				TASK_BUZ_PRIO);

/* Long.Luo, 2012/10/01, Add for: , */
    OSTaskCreate(taskMusic, 
    			(void *)0, 
    			&Task_MusicStk[TASK_MUSIC_STK_SIZE-1],
    			TASK_MUSIC_PRIO);
/* Add end. */
				

	while (1)
	{                             
        OSTaskSuspend(OS_PRIO_SELF);                                    /*  The start task can be pended*/
                                                                        /*  here. ����������������  */
    }
}


/*********************************************************************************************************
  The other tasks ��������
*********************************************************************************************************/

/*********************************************************************************************************
** Function name:           taskLed	   
** Descriptions:            LED ����	
** input parameters:        *parg
** output parameters:       ��      
** Returned value:          ��	 
*********************************************************************************************************/
static void taskLed(void *parg)
{
    (void)parg;
    
    while (1) 
    {
    	RIT128x96x4Clear();
    	RIT128x96x4StringDraw("Task Led", 30, 10, 15);
		ledOn(5);          					                            /*  ����LED                    */          	
		OSTimeDly(OS_TICKS_PER_SEC / 2); 			                    /*  ��ʱ0.5��                   */               	
		ledOff(5);                                                      /*  �ر�LED                    */           	
		OSTimeDly(OS_TICKS_PER_SEC / 2);  		                        /*  ��ʱ0.5��                   */			
	}
}


/************************************************************************************
** Function: taskBuz()
** Routine Description: - 
**     buzzer task
** Input parameters: - 
** 
** Output parameters: NONE
** Returned Value: NONE
** Remarks:
** 
** Date created: 23:47:46,22/05/2012
** Author: Long.Luo
************************************************************************************/
static void taskBuz(void *parg)
{
    (void)parg;
    
    while (1) 
    {
		RIT128x96x4Clear();
    	RIT128x96x4StringDraw("Task Buz", 30, 20, 15);       
    	setPWMState(TRUE);
    	OSTimeDly(2 * OS_TICKS_PER_SEC);  
    	setPWMState(FALSE);
    	OSTimeDly(10 * OS_TICKS_PER_SEC);  
	}
}


/************************************************************************************
** Function: taskMusic()
** Routine Description: - 
**     the Music Task  
** Input parameters: - 
**    NONE 
** Output parameters: NONE
** Returned Value: NONE
** Remarks:
** 
** Date created: 11:58:59,01/10/2012
** Author: Long.Luo
************************************************************************************/
static void taskMusic(void *parg)
{
    (void)parg;
    
    while (1) 
    {
		RIT128x96x4Clear();
    	RIT128x96x4StringDraw("Task Music", 30, 20, 15);       
		playNote(ButterflyLove);
    	OSTimeDly(2 * OS_TICKS_PER_SEC);  
	}
}


/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
