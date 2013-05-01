/****************************************Copyright (c)****************************************************
**                   Texas Instruments Semiconductor Technologies Co.,LTD.                              **
**                                                                                                      **                                     
**                                 http://www.ti.com                                                    **
**                                                                                                      **
**--------------File Info---------------------------------------------------------------------------------
** File Name:               sys_arch.c                                                                  ** 
** Last modified Date:      12-20-2010                                                                  **
** Last Version:            1.0                                                                         **
** Description:             The abstruct level of Lwip base on ucos-II                                  **
**                                                                                                      **
**--------------------------------------------------------------------------------------------------------
** Created By:              long.luo                                                                    **
** Created date:            10-04-2013                                                                  **
** Version:                 1.0                                                                         **
** Descriptions:            The original version                                                        **
**                                                                                                      **
*********************************************************************************************************/

#include "lwip/opt.h"
#include "lwip/sys.h"
#include "arch/sys_arch.h"

#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_ints.h"
#include "interrupt.h"


/********************************************************************************************************
********************************************************************************************************/
static OS_MEM *pQueueMem;

//static char pcQueueMemoryPool[MAX_QUEUES * sizeof(LwIP_Q_Mbox)];
static LwIP_Q_Mbox  pcQueueMemoryPool[MAX_QUEUES];

static struct sys_timeouts lwip_timeouts[LWIP_TASK_MAX];
static struct sys_timeouts null_timeouts;


OS_STK LWIP_THREAD_STK[LWIP_TASK_MAX][LWIP_STK_SIZE]; /* stack used by lwip task */



/*********************************************************************************************************
** Function name:           sys_sem_new                                                                 **
** Descriptions:            Creat and return a semaphore                                                **     
** input parameters:        count : semaphore initialization status                                     **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            10-04-2013                                                                  **
*********************************************************************************************************/ 
sys_sem_t sys_sem_new(u8_t count)
{
    return OSSemCreate(count);
}

/*********************************************************************************************************
** Function name:           sys_sem_free                                                                **
** Descriptions:            Delete an indicated semaphore                                               **     
** input parameters:        sem : The semaphore which will be deleted                                   **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            10-04-2013                                                                  **
*********************************************************************************************************/ 
void sys_sem_free(sys_sem_t sem)
{
    INT8U   __u8Err;
   
    while (((OS_EVENT *)0) != (OSSemDel(sem,OS_DEL_ALWAYS,&__u8Err)))
    {
        OSTimeDlyHMSM(0,0,0,100);
    }
}

/*********************************************************************************************************
** Function name:           sys_sem_signal                                                              **
** Descriptions:            Send a semaphore                                                            **     
** input parameters:        sem : The semaphore which will be sent                                      **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            10-04-2013                                                                  **
*********************************************************************************************************/  
void sys_sem_signal(sys_sem_t sem)
{
    OSSemPost(sem);
}

/*********************************************************************************************************
** Function name:           __MSToOSTicks                                                               **
** Descriptions:            Invert ms into clock ticker                                                 **     
** input parameters:        u16MS : Clock ticker                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            10-04-2013                                                                  **
*********************************************************************************************************/ 
static INT16U __MSToTicks(INT32U u32MS)
{
    INT32U __u32DelayTicks;
  
    if (0 != u32MS)
    {
        __u32DelayTicks = (u32MS * OS_TICKS_PER_SEC)/100;
        if (1 > __u32DelayTicks)
        {
            __u32DelayTicks=1;
        }
        else if (65535 < __u32DelayTicks)
        {
            __u32DelayTicks = 65535;
        }
        else ;
    }
    else
    { 
        __u32DelayTicks = 0;
    }  
    return (INT16U)__u32DelayTicks;
}

/*********************************************************************************************************
** Function name:           sys_arch_sem_wait                                                           **
** Descriptions:            Waiting semaphore                                                           **     
** input parameters:        Sem :                                                                       **
**                          timeout :                                                                   **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            10-04-2013                                                                  **
*********************************************************************************************************/ 
u32_t sys_arch_sem_wait(sys_sem_t sem,u32_t timeout)
{
    INT8U __u8RtnVal; 
   
    OSSemPend(sem,__MSToTicks(timeout),&__u8RtnVal);
   
    if (__u8RtnVal == OS_NO_ERR)
    {
        return 0;
    }
    else 
    {
        return SYS_ARCH_TIMEOUT;
    }
}

/*********************************************************************************************************
** Function name:           sys_init                                                                    **
** Descriptions:            Initialize lwip                                                             **     
** input parameters:        Sem :                                                                       **
**                          timeout :                                                                   **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            10-04-2013                                                                  **
*********************************************************************************************************/ 
void sys_init(void)
{
    u8_t   i;
    u8_t   ucErr;
   
    do
    {
        pQueueMem = OSMemCreate( (void*)pcQueueMemoryPool, MAX_QUEUES,
                                sizeof(LwIP_Q_Mbox), &ucErr );  /*  Creat a ram section */
    }while(ucErr != OS_NO_ERR);
  
    for (i = 0; i < LWIP_TASK_MAX; i++)
    {
        lwip_timeouts[i].next = NULL;
    }
}

/*********************************************************************************************************
** Function name:           sys_mbox_new                                                                **
** Descriptions:            Creat a empty mbox                                                          **     
** input parameters:        Null                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            10-04-2013                                                                  **
*********************************************************************************************************/ 
sys_mbox_t sys_mbox_new(int size)
{  
    u8_t       ucErr;
    sys_mbox_t pQDesc;
    
    pQDesc = OSMemGet( pQueueMem, &ucErr );
    if ( ucErr == OS_NO_ERR ) 
    {   
        pQDesc->pQ_Mbox = OSQCreate( &(pQDesc->pvQ_msgQueue[0]), size );       
        if ( pQDesc->pQ_Mbox != ((OS_EVENT *)0 ) ) 
        {
            return pQDesc;
        }
    } 
    return SYS_MBOX_NULL;
}

/*********************************************************************************************************
** Function name:           sys_mbox_free                                                               **
** Descriptions:            Free a mbox                                                                 **     
** input parameters:        Null                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            10-04-2013                                                                  **
*********************************************************************************************************/ 
void sys_mbox_free(sys_mbox_t mbox)
{
    u8_t     ucErr;
    
    OSQFlush( mbox->pQ_Mbox);
    
    while (((OS_EVENT *)0 )!= (OSQDel( mbox->pQ_Mbox, OS_DEL_NO_PEND, &ucErr)))
    {
        OSTimeDlyHMSM(0,0,0,100);
    }
    
    ucErr = OSMemPut( pQueueMem, mbox );
}


/*********************************************************************************************************
** Function name:           sys_mbox_post                                                               **
** Descriptions:            Send a mbox                                                                 **     
** input parameters:        Null                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            10-04-2013                                                                  **
*********************************************************************************************************/ 
void sys_mbox_post(sys_mbox_t mbox,void *msg)
{
    while(OSQPost(mbox ->pQ_Mbox,msg) != OS_NO_ERR)
    {
        OSTimeDlyHMSM(0,0,0,100);
    }
}
          
/*********************************************************************************************************
** Function name:           sys_mbox_trypost
** Descriptions:            发送邮箱，将消息投递到指定的邮箱。该函数不会阻塞进程。
** input parameters:        mbox:指定要投递的邮箱
**                          msg: 指定要投递的消息
** output parameters:       无  
** Returned value:          如果邮箱是满的，返回ERR_MEM;反之，邮箱正确投递，返回ERR_OK。	
** Created by:		    任海波
** Created Date:	    2008.8.5
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:         
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
err_t sys_mbox_trypost(sys_mbox_t mbox,void *msg)
{
  if(OSQPost(mbox ->pQ_Mbox, msg) != OS_NO_ERR)
    return ERR_MEM;
  else
    return ERR_OK;
}

/*********************************************************************************************************
** Function name:           sys_arch_mbox_fetch
** Descriptions:            在指定的邮箱接收消息，该函数会阻塞线程
** input parameters:        mbox:指定接收消息的邮箱
**                          ttimeout: 指定等待的最长时间，单位为ms
** output parameters:       msg:保存接收到的消息指针    
** Returned value:           0： 在指定的时间内收到消息
**                          SYS_ARCH_TIMEOUT:在指定的时间内没有收到消息
** Created by:		    任海波
** Created Date:	    2008.8.6
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:         
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
u32_t sys_arch_mbox_fetch(sys_mbox_t mbox,void **msg,u32_t timeout)
{
   u8_t     ucErr;
   
   *msg = OSQPend( mbox->pQ_Mbox, __MSToTicks(timeout), &ucErr ); 
   
   if(ucErr == OS_NO_ERR)
     return 0;
   else
     return SYS_ARCH_TIMEOUT;
}

/*********************************************************************************************************
** Function name:           sys_arch_mbox_tryfetch
** Descriptions:            在指定的邮箱接收消息，该函数不会阻塞线程
** input parameters:        mbox:指定接收消息的邮箱
** output parameters:       msg:保存接收到的消息指针    
** Returned value:           0： 邮箱中存在消息
**                          SYS_MBOX_EMPTY:邮箱中没有消息
** Created by:		    任海波
** Created Date:	    2008.8.6
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:         
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
u32_t sys_arch_mbox_tryfetch(sys_mbox_t mbox,void **msg)
{
   u8_t     ucErr;
   
  *msg = OSQAccept(mbox ->pQ_Mbox,&ucErr);
  
  if(*msg == ((void *)0))
    return SYS_MBOX_EMPTY;
  else
    return 0;
}

/*********************************************************************************************************
** Function name:           sys_arch_timeouts
** Descriptions:            获取当前线程使用的sys_timeouts结构的指针
** input parameters:        无
** output parameters:       无
** Returned value:          返回一个指向当前线程使用的sys_timeouts结构的指针	
** Created by:		    任海波
** Created Date:	    2008.8.6
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:         
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
struct  sys_timeouts *sys_arch_timeouts(void)
{
   OS_TCB curr_task_pcb;
   u8_t curr_prio;
   s16_t err,offset;
    
	err = err;
  null_timeouts.next = NULL;

  err = OSTaskQuery(OS_PRIO_SELF,&curr_task_pcb); /* 获取当前线程的优先级 */
  curr_prio = curr_task_pcb.OSTCBPrio;
  
  offset = curr_prio - LWIP_START_PRIO;

  if(offset < 0 || offset >= LWIP_TASK_MAX)      /*如果不是LwIP的线程，那么返回timeouts->NULL*/
  {
    return &null_timeouts;
  }

  return &lwip_timeouts[offset];
}

/*********************************************************************************************************
** Function name:           sys_thread_new
** Descriptions:            建立一个新的任务
** input parameters:        thread: 新任务的入口地址
**                          arg:    传递给新线程的参数
**                          prio:   由LWIP指定的新任务的优先级
** output parameters:      无
** Returned value:          任务的优先级，注意这与Prio是不同的，这个值实际等于T_LWIP_THREAD_START_PRIO + prio，
**                          如果任务建立不成功，则返回0
** Created by:		    任海波
** Created Date:	    2008.8.6
**--------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:         
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
sys_thread_t  sys_thread_new(char *name,void(*thread)(void *arg),void *arg,int stacksize,int prio)
{
   INT8U   __u8Prio = 0;
   if(prio > 0 && prio <= LWIP_TASK_MAX) /* 如果优先级定义没有超过系统允许的范围 */
   {
      __u8Prio = LWIP_START_PRIO + (prio - 1);
      
      if(OS_NO_ERR == OSTaskCreate(thread, arg, 
                                   &LWIP_THREAD_STK[prio - 1][LWIP_STK_SIZE - 1],
                                   __u8Prio))
        return __u8Prio;
      else
        return 0;
   }
   else 
     return 0;
}

#if SYS_LIGHTWEIGHT_PROT
/*
 * This function is used to lock access to critical sections when lwipopt.h
 * defines SYS_LIGHTWEIGHT_PROT. It disables interrupts and returns a value
 * indicating the interrupt enable state when the function entered. This
 * value must be passed back on the matching call to sys_arch_unprotect().
 *
 * @return the interrupt level when the function was entered.
 * 
 */
sys_prot_t
sys_arch_protect(void)
{
  tBoolean bRet = 1;

  bRet = IntMasterDisable();

  return((sys_prot_t)bRet);
}

/*
 * This function is used to unlock access to critical sections when lwipopt.h
 * defines SYS_LIGHTWEIGHT_PROT. It enables interrupts if the value of the lev
 * parameter indicates that they were enabled when the matching call to
 * sys_arch_protect() was made.
 *
 * @param lev is the interrupt level when the matching protect function was
 * called
 *
 */
void
sys_arch_unprotect(sys_prot_t lev)
{
  /*
   * Only turn interrupts back on if they were originally on when the
   * matching sys_arch_protect() call was made.
   *
   */
  if(!(lev & 1)) {
    IntMasterEnable();
  }
}

#endif /* SYS_LIGHTWEIGHT_PROT */
