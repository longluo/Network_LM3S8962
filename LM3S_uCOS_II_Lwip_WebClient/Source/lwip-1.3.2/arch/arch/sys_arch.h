/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/****************************************Copyright (c)****************************************************
**                               Guangzhou ZHIYUAN electronics Co.,LTD.
**                                     
**                                 http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File Name:               sys_arch.h
** Last modified Date:      2008.9.1
** Last Version:            v1.0
** Description:             LWIP在uCOS下移植的操作系统抽象层的头文件声明
** 
**--------------------------------------------------------------------------------------------------------
** Created By:              Renhaibo任海波
** Created date:            2008.9.1
** Version:                 v1.0
** Descriptions:            The original version 初始版本
**
**--------------------------------------------------------------------------------------------------------
** Modified by:            
** Modified date:           
** Version:                 
** Description:           
**
*********************************************************************************************************/
#ifndef __ARCH_SYS_ARCH_H__
#define __ARCH_SYS_ARCH_H__

#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h>
#include "arch\cc.h"

#ifndef NULL
#define NULL  (void *)0
#endif

#define  LWIP_STK_SIZE      1024
#define  LWIP_TASK_MAX      1
#define  LWIP_START_PRIO    2 

#define SYS_MBOX_NULL    (void *)0
#define SYS_SEM_NULL     (void *)0

#define MAX_QUEUES         10

/*  LwIP邮箱数据结构  */
typedef struct {
    OS_EVENT*   pQ_Mbox;
    void*       pvQ_msgQueue[MAX_QUEUES];
} LwIP_Q_Mbox, *PLwIP_Q_Mbox;
    

typedef OS_EVENT *       sys_sem_t;    
typedef PLwIP_Q_Mbox     sys_mbox_t;
typedef unsigned char    sys_prot_t;
typedef u8_t             sys_thread_t;

#endif /* __ARCH_SYS_ARCH_H__ */

