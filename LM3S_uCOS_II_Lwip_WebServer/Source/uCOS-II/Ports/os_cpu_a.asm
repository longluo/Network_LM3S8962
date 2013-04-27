;/****************************************Copyright (c)****************************************************
;**                   Texas Instruments Semiconductor Technologies Co.,LTD.		                         **
;**                                                                                                      **                                     
;**                                 http://www.ti.com                                                    **
;**																										 **
;**--------------File Info---------------------------------------------------------------------------------
;** File Name:               os_cpu_a.asm                                                                ** 
;** Last modified Date:      12-20-2010                                                                  **
;** Last Version:            1.0																		 **
;** Description:             The assembly functions that a uC/OS-II port requires                        **
;** 																									 **
;**--------------------------------------------------------------------------------------------------------
;** Created By:              long.luo                                                                    **
;** Created date:            10-04-2013																	 **
;** Version:                 1.0																		 **
;** Descriptions:            The original version  														 **
;**																										 **
;*********************************************************************************************************/

;*********************************************************************************************************
;  Declarations for the interrupt handlers that are used by the application.              
;*********************************************************************************************************
	EXTERN  OSRunning                
	EXTERN  OSPrioCur
	EXTERN  OSPrioHighRdy
	EXTERN  OSTCBCur
	EXTERN  OSTCBHighRdy
	EXTERN  OSIntNesting
	EXTERN  OSIntExit
	EXTERN  OSTaskSwHook
	EXTERN  OsEnterSum


;*********************************************************************************************************
;  Declarations for the exported functions             
;*********************************************************************************************************
	EXPORT  OSStartHighRdy
	EXPORT  OSCtxSw
	EXPORT  OSIntCtxSw
	EXPORT  OSPendSV
	EXPORT  OS_ENTER_CRITICAL
	EXPORT  OS_EXIT_CRITICAL                  
	EXPORT  IntDisAll


;*********************************************************************************************************
;  Registers or macros used by this file                                
;*********************************************************************************************************							    
NVIC_INT_CTRL           EQU     0xE000ED04                          ;  Interrupt control state register.

NVIC_SYSPRI2            EQU     0xE000ED20                          ;  System priority register (2)

NVIC_PENDSV_PRI         EQU     0xFFFF0000                          ; PendSV and system tick priority
                                                                    ;  (Both are lowest,0xff)  
NVIC_PENDSVSET          EQU     0x10000000                          ;  Value to trigger PendSV  
                                                                    ;  exception.

OS_CRITICAL_INT_PRIO    EQU     (0 << 5)		                    ;  Critical setions manage prio. 
                                                                    ; (equal or bigger number managed) 
                                                                        
	PRESERVE8                                                      

		AREA    UCOSII_ASM, CODE, READONLY
	THUMB

;/*********************************************************************************************************
;** Function name:           OS_ENTER_CRITICAL   														 **
;** Descriptions:            Enter the critical section                                                  **     
;** input parameters:        none																		 **
;** output parameters:       none     																	 **
;** Returned value:          noe  																		 **
;==========================================================================================================
;** Created by:              long.luo                                                                    **
;** Created Date:            11-04-2013                                                                  **
;*********************************************************************************************************/ 
OS_ENTER_CRITICAL
	IF OS_CRITICAL_INT_PRIO > 0
		PUSH 	{R1,R2} 	                
		LDR 	R1, =OS_CRITICAL_INT_PRIO       ;  Disable priorities between 
		;  OS_CRITICAL_INT_PRIO & 0xFF 
		MSR 	BASEPRI,  R1                                           
	 				 
	ELSE
		CPSID   I                              	;  Disable all the interrupts
		PUSH 	{R1,R2}      
	ENDIF

	LDR 	R1, =OsEnterSum			;  OsEnterSum++
	LDRB 	R2, [R1]
	ADD   	R2, R2, #1
	STRB 	R2, [R1]
	POP     {R1,R2}
	BX LR

;/*********************************************************************************************************
;** Function name:           OS_EXIT_CRITICAL   														 **
;** Descriptions:            Exit the critical section                                                   **     
;** input parameters:        none																		 **
;** output parameters:       none     																	 **
;** Returned value:          noe  																		 **
;==========================================================================================================
;** Created by:              long.luo                                                                    **
;** Created Date:            11-04-2013                                                                  **
;*********************************************************************************************************/
OS_EXIT_CRITICAL
	PUSH    {R1, R2}
	LDR     R1, =OsEnterSum                                         ;  OsEnterSum--
	LDRB    R2, [R1]
	SUB     R2, R2, #1
	STRB    R2, [R1]
	MOV     R1,  #0	      
	CMP     R2,  #0			                                        ;  if OsEnterSum=0,enable interrupt
	                                                
	IF OS_CRITICAL_INT_PRIO > 0                                         
		MSREQ	BASEPRI, R1 
	ELSE
		MSREQ  PRIMASK, R1   
	ENDIF
	
	POP   	{R1, R2}
	BX LR

;/*********************************************************************************************************
;** Function name:           OSStartHighRdy      														 **
;** Descriptions:            Uses the context switcher  to cause the first task to start.                **     
;** input parameters:        none																		 **
;** output parameters:       none     																	 **
;** Returned value:          noe  																		 **
;==========================================================================================================
;** Created by:              long.luo                                                                    **
;** Created Date:            11-04-2013                                                                  **
;*********************************************************************************************************/
OSStartHighRdy

        LDR     R4, =NVIC_SYSPRI2                                       ;  set the PendSV exception priority

        LDR     R5, =NVIC_PENDSV_PRI	
        STR     R5, [R4]
	    
        MOV     R4, #0                                                  ;  set the PSP to 0 for initial  
                                                                        ;  context switch call 
        MSR     PSP, R4

        LDR     R4, =OSRunning                                          ;  OSRunning = TRUE
        MOV     R5, #1
        STRB    R5, [R4]

        LDR     R4, =NVIC_INT_CTRL                                      ;  trigger the PendSV exception

        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]

        CPSIE   I                                                       ;  enable interrupts at processor 
                                                                        ;  level
OSStartHang
        B       OSStartHang             

;/*********************************************************************************************************
;** Function name:           OSCtxSw            														 **
;** Descriptions:            Perform a contex switch from task level                                     **     
;** input parameters:        none																		 **
;** output parameters:       none     																	 **
;** Returned value:          noe  																		 **
;==========================================================================================================
;** Created by:              long.luo                                                                    **
;** Created Date:            11-04-2013                                                                  **
;*********************************************************************************************************/
OSCtxSw
	PUSH    {R4, R5}
	LDR     R4, =NVIC_INT_CTRL                                      ;  trigger the PendSV exception

	LDR     R5, =NVIC_PENDSVSET
	STR     R5, [R4]
	POP     {R4, R5}
	BX      LR


;/*********************************************************************************************************
;** Function name:           OSIntCtxSw            														 **
;** Descriptions:            called by OSIntExit() when it determines a context switch is needed as the  **
;**                          result of an interrupt.                                                     **     
;** input parameters:        none																		 **
;** output parameters:       none     																	 **
;** Returned value:          noe  																		 **
;==========================================================================================================
;** Created by:              long.luo                                                                    **
;** Created Date:            11-04-2013                                                                  **
;*********************************************************************************************************/
OSIntCtxSw
	PUSH    {R4, R5}
	LDR     R4, =NVIC_INT_CTRL                                      ;  trigger the PendSV exception
	                                                       
	LDR     R5, =NVIC_PENDSVSET
	STR     R5, [R4]
	POP     {R4, R5}
	BX      LR
	NOP

;/*********************************************************************************************************
;** Function name:           OSPendSV            														 **
;** Descriptions:            Used to cause a context switch                                              **
;** input parameters:        none																		 **
;** output parameters:       none     																	 **
;** Returned value:          noe  																		 **
;==========================================================================================================
;** Created by:              long.luo                                                                    **
;** Created Date:            11-04-2013                                                                  **
;*********************************************************************************************************/
OSPendSV
	IF OS_CRITICAL_INT_PRIO > 0	                                    ;  disable interupt 
		MRS R3, BASEPRI
		LDR R1, =OS_CRITICAL_INT_PRIO
		MSR BASEPRI, R1
	ELSE
		MRS     R3, PRIMASK                
		CPSID   I
	ENDIF


	MRS     R0, PSP                                                 ;  PSP is process stack pointer  

        CBZ     R0, OSPendSV_nosave                                     ;  skip register save the first 
                                                                        ;  time

        SUB     R0, R0, #0x20                                           ;  save remaining regs r4-11 on 
                                                                        ;  process stack 
        STM     R0, {R4-R11}

        LDR     R4, =OSTCBCur                                           ;  OSTCBCur->OSTCBStkPtr = SP;
        LDR     R4, [R4]
        STR     R0, [R4]                                                ;  R0 is SP of process being 
                                                                        ;  switched out
OSPendSV_nosave
        PUSH    {R14}                                                   ;  need to save LR exc_return 
                                                                        ;  value

        LDR     R0, =OSTaskSwHook                                       ;  OSTaskSwHook();
        BLX     R0
        POP     {R14}
 	  
        LDR     R4, =OSPrioCur                                          ;  OSPrioCur = OSPrioHighRdy
        LDR     R5, =OSPrioHighRdy     
        LDRB    R6, [R5]
        STRB    R6, [R4]

        LDR     R4, =OSTCBCur                                           ;  OSTCBCur  = OSTCBHighRdy;
        LDR     R6, =OSTCBHighRdy      
        LDR     R6, [R6]
        STR     R6, [R4]

        LDR     R0, [R6]                                                ;  SP = OSTCBHighRdy->OSTCBStkPtr;
        LDM     R0, {R4-R11}                                            ;  restore r4-11 from new process
                                                                        ;  stack 
        ADD     R0, R0, #0x20
        MSR     PSP, R0                                                 ;  load PSP with new process SP
                                                                        
 	   	
        ORR     LR, LR, #0x04                                           ;  ensure exception return uses 
                                                                        ;  PSP
        
	IF OS_CRITICAL_INT_PRIO > 0                                     ;  restore interrupts   
		MSR 	BASEPRI,  R3
	ELSE
		MSR     PRIMASK, R3
	ENDIF
		   
	BX      LR                                                      ; exception return will restore 
                                                                        ;  remaining context 
                                                                       
        NOP

;/*********************************************************************************************************
;** Function name:           IntDisAll            														 **
;** Descriptions:            Disable all interrupts from the interrupt controller                        **
;** input parameters:        none																		 **
;** output parameters:       none     																	 **
;** Returned value:          noe  																		 **
;==========================================================================================================
;** Created by:              long.luo                                                                    **
;** Created Date:            11-04-2013                                                                  **
;*********************************************************************************************************/
IntDisAll
    ;MRS     R0, PRIMASK;
    CPSID   I
    BX      LR
    
IntEnableAll
    MSR     PRIMASK,R0
    BX	    LR

    ALIGN


    END
    
;*********************************************************************************************************
;  END FILE                                               
;*********************************************************************************************************

