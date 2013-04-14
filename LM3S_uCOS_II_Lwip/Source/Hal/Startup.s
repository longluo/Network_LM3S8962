;/****************************************Copyright (c)****************************************************
;**                   Texas Instruments Semiconductor Technologies Co.,LTD.		                         **
;**                                                                                                      **                                     
;**                                 http://www.ti.com                                                    **
;**																										 **
;**--------------File Info---------------------------------------------------------------------------------
;** File Name:                Startup.s                                                                  ** 
;** Last modified Date:      12-20-2010                                                                  **
;** Last Version:            1.0																		 **
;** Description:             Startup code of LM3S MCU                                                    **
;** 																									 **
;**--------------------------------------------------------------------------------------------------------
;** Created By:              long.luo                                                                    **
;** Created date:            10-04-2013																	 **
;** Version:                 1.0																		 **
;** Descriptions:            The original version  														 **
;**																										 **
;*********************************************************************************************************/

;*********************************************************************************************************
;*  Byte number of Main Stack     
;*********************************************************************************************************
Stack   EQU     512


;*********************************************************************************************************
;*  Byte number of the Heap          
;*********************************************************************************************************
Heap    EQU     256


;*********************************************************************************************************
;*  Allocate space for Main Stack   
;*********************************************************************************************************
        AREA    STACK, NOINIT, READWRITE, ALIGN=3
StackMem
        SPACE   Stack


;*********************************************************************************************************
;*  Allocate space for the heap                                
;*********************************************************************************************************
        AREA    HEAP, NOINIT, READWRITE, ALIGN=3
HeapMem
        SPACE   Heap


;*********************************************************************************************************
;*  Declarations for the interrupt handlers that are used by the application.                            
;*********************************************************************************************************
        EXTERN	OSPendSV  
		EXTERN  tickISRHandler
	   	;EXTERN  keyISR
        EXTERN  ADC3IntHandler
        ;EXTERN  UARTIntHandler
	
;*********************************************************************************************************
;*  Indicate that the code in this file preserves 8-byte alignment of the stack.              
;*********************************************************************************************************
        PRESERVE8


;*********************************************************************************************************
;*  Reset code section.                                           
;*********************************************************************************************************
        AREA    RESET, CODE, READONLY
        THUMB

;*********************************************************************************************************
;*  The vector table.
;*********************************************************************************************************
        EXPORT __Vectors
__Vectors
        DCD     StackMem + Stack        ; Top of Stack                                    
        DCD     Reset_Handler           ; Reset Handler                                    
        DCD     NmiSR                   ; NMI Handler                                
        DCD     IntDefaultHandler       ; Hard Fault Handler                                 
        DCD     IntDefaultHandler       ; The MPU fault handler                                
        DCD     IntDefaultHandler       ; The bus fault handler                                
        DCD     IntDefaultHandler       ; The usage fault handler                                 
        DCD     0                       ; Reserved                                
        DCD     0                       ; Reserved                                
        DCD     0                       ; Reserved                                
        DCD     0                       ; Reserved                                
        DCD     IntDefaultHandler       ; SVCall handler                          
        DCD     IntDefaultHandler       ; Debug monitor handler                   
        DCD     0                       ; Reserved                               
	    DCD     OSPendSV                ; The PendSV handler                     
	    DCD     tickISRHandler          ; The SysTick handler                    
        DCD     IntDefaultHandler       ; GPIO Port A                            
        DCD     IntDefaultHandler       ; GPIO Port B                            
        DCD     IntDefaultHandler       ; GPIO Port C                            
        DCD     IntDefaultHandler       ; GPIO Port D                            
        DCD     IntDefaultHandler       ; GPIO Port E                            
        DCD     IntDefaultHandler       ; UART0 Rx and Tx                        
        DCD     IntDefaultHandler       ; UART1 Rx and Tx                        
        DCD     IntDefaultHandler       ; SSI0 Rx and Tx                         
        DCD     IntDefaultHandler       ; I2C0 Master and Slave                  
        DCD     IntDefaultHandler       ; PWM Fault                              
        DCD     IntDefaultHandler       ; PWM Generator 0                        
        DCD     IntDefaultHandler       ; PWM Generator 1                        
        DCD     IntDefaultHandler       ; PWM Generator 2                        
        DCD     IntDefaultHandler       ; Quadrature Encoder 0                   
        DCD     IntDefaultHandler       ; ADC Sequence 0                         
        DCD     IntDefaultHandler       ; ADC Sequence 1                         
        DCD     IntDefaultHandler       ; ADC Sequence 2                         
        DCD     ADC3IntHandler          ; ADC Sequence 3                        
        DCD     IntDefaultHandler       ; Watchdog timer                        
        DCD     IntDefaultHandler       ; Timer 0 subtimer A                           
        DCD     IntDefaultHandler       ; Timer 0 subtimer B                           
        DCD     IntDefaultHandler       ; Timer 1 subtimer A                           
        DCD     IntDefaultHandler       ; Timer 1 subtimer B                           
        DCD     IntDefaultHandler       ; Timer 2 subtimer A                           
        DCD     IntDefaultHandler       ; Timer 2 subtimer B                          
        DCD     IntDefaultHandler       ; Analog Comparator 0                         
        DCD     IntDefaultHandler       ; Analog Comparator 1                         
        DCD     IntDefaultHandler       ; Analog Comparator 2                         
        DCD     IntDefaultHandler       ; System Control (PLL, OSC, BO)               
        DCD     IntDefaultHandler       ; Flash Control
        DCD     IntDefaultHandler       ; GPIO Port F
        DCD     IntDefaultHandler       ; GPIO Port G
        DCD     IntDefaultHandler       ; GPIO Port H
        DCD     IntDefaultHandler       ; UART2 Rx and Tx
        DCD     IntDefaultHandler       ; SSI1 Rx and Tx
        DCD     IntDefaultHandler       ; Timer 3 subtimer A
        DCD     IntDefaultHandler       ; Timer 3 subtimer B
        DCD     IntDefaultHandler       ; I2C1 Master and Slave
        DCD     IntDefaultHandler       ; Quadrature Encoder 1
        DCD     IntDefaultHandler       ; CAN0
        DCD     IntDefaultHandler       ; CAN1
        DCD     0                       ; Reserved
        DCD     IntDefaultHandler       ; Ethernet
        DCD     IntDefaultHandler       ; Hibernate


;*********************************************************************************************************
;*  Reset entry
;*********************************************************************************************************
        EXPORT  Reset_Handler
Reset_Handler
        IMPORT  __main
        LDR     R0, =__main
        BX      R0


;*********************************************************************************************************
;*  NMI exception handler. 
;*  It simply enters an infinite loop.
;*********************************************************************************************************
NmiSR
        B       NmiSR


;*********************************************************************************************************
;*  Fault interrupt handler. 
;*  It simply enters an infinite loop.
;*********************************************************************************************************
FaultISR
        B       FaultISR


;*********************************************************************************************************
;*  Unexpected interrupt handler. 
;*  It simply enters an infinite loop.
;*********************************************************************************************************
IntDefaultHandler
        B       IntDefaultHandler


;*********************************************************************************************************
;*  Make sure the end of this section is aligned.
;*********************************************************************************************************
        ALIGN



;*********************************************************************************************************
;*  Code section for initializing the heap and stack                                                      
;*********************************************************************************************************
        AREA    |.text|, CODE, READONLY

;*********************************************************************************************************
;*  The function expected of the C library startup 
;*  code for defining the stack and heap memory locations.
;*********************************************************************************************************
        IMPORT  __use_two_region_memory
        EXPORT  __user_initial_stackheap
__user_initial_stackheap
        LDR     R0, =HeapMem
        LDR     R1, =(StackMem + Stack)
        LDR     R2, =(HeapMem + Heap)
        LDR     R3, =StackMem
        BX      LR


;*********************************************************************************************************
;*  Make sure the end of this section is aligned.
;*********************************************************************************************************
        ALIGN


;*********************************************************************************************************
;*  End Of File                                                     
;*********************************************************************************************************
        END
        
