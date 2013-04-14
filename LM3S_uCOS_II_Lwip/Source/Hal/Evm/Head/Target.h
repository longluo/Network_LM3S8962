/****************************************Copyright (c)****************************************************
**                   Texas Instruments Semiconductor Technologies Co.,LTD.                              **
**                                                                                                      **                                     
**                                 http://www.ti.com                                                    **
**                                                                                                      **
**--------------File Info---------------------------------------------------------------------------------
** File Name:               Target.h                                                                    ** 
** Last modified Date:      12-20-2010                                                                  **
** Last Version:            1.0                                                                         **
** Description:             Header file of the target board                                             **
**                                                                                                      **
**--------------------------------------------------------------------------------------------------------
** Created By:              long.luo                                                                    **
** Created date:            10-04-2013                                                                  **
** Version:                 1.1                                                                         **
** Descriptions:            The original version                                                        **
**                                                                                                      **
*********************************************************************************************************/

#ifndef __TARGET_H
#define __TARGET_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************************************
  System Clock(CCLK) Setting   
  CCLK must be less than or equal to  20MHz/50MHz(depend on the max. cclk of the CPU)
  If PLL_EN = 0, CCLK = EXT_CLK/CCLK_DIV, CCLK must <=20MHZ/50MHz 
  If PLL_EN > 0, CCLK = 200MHz/CCLK_DIV, CCLK must <=20MHZ/50MHz
*********************************************************************************************************/
#define  PLL_EN             1                                           /*  1：Enable PLL      */
#define  CCLK_DIV           SYSCTL_SYSDIV_1                             /*  CCLK divider CCLK  */
#define  EXT_CLK            SYSCTL_XTAL_8MHZ                            /*  external clock     */     

/*********************************************************************************************************
  Setting of the target board's API function 
*********************************************************************************************************/
#define  TARGET_LED_EN		1											/*  1:Enable the LED            */

#define  TARGET_LED1_EN     0                                           /*  1:Enable LED1               */     
#define  TARGET_LED2_EN     0                                           /*  1:Enable LED2               */
#define  TARGET_LED3_EN     0                                           /*  1:Enable LED3               */
#define  TARGET_LED4_EN     0                                           /*  1:Enable LED4               */

#define  TARGET_BUZ_EN      1                                           /*  1:Enable the buzzer         */

#define  TARGET_KEY1_EN  	0  				                            /*  1:Enable Key1  使能Key1     */
#define  TARGET_KEY2_EN   	0  					                        /*  1:Enable Key2  使能Key2     */
#define  TARGET_KEY3_EN   	0  					                        /*  1:Enable Key3  使能Key3     */
#define  TARGET_KEY4_EN   	0  					                        /*  1:Enable Key4  使能Key4     */

#define  TARGET_TMR0A_EN    0                                           /*  1：Eanble the Timer0A API 
                                                                            functions                   */
                                                                           
#define  TARGET_KEY_SELECT_EN	0

#define  TARGET_KEY_UP_EN		0
#define  TARGET_KEY_DOWN_EN		0
#define  TARGET_KEY_LEFT_EN		0	
#define  TARGET_KEY_RIGHT_EN	0

#define  TARGET_PWM_EN			1
//#define  TARGET_PWM1_EN			1
//#define  TARGET_PWM2_EN			1

#define	 TARGET_UART_EN			1

#define	 TARGET_DISP_EN			1

#define  TARGET_ADC_EN			1


#if TARGET_LED_EN > 0
#define LED_SYSCTL		SYSCTL_PERIPH_GPIOF								/*  System control of LED      */
#define LED_GPIO_PORT  	GPIO_PORTF_BASE									/*  IO port of LED             */
#define LED_PIN       	GPIO_PIN_0										/*  Pin number of LED          */
#endif
                                                                         
#if TARGET_LED1_EN > 0
#define LED1_SYSCTL  	SYSCTL_PERIPH_GPIOA	                            /*  System control of LED1      */
#define LED1_GPIO_PORT  GPIO_PORTA_BASE     	                        /*  IO port of LED1             */  
#define LED1_PIN        GPIO_PIN_0				                        /*  Pin number of LED1          */
#endif

#if TARGET_LED2_EN > 0
#define LED2_SYSCTL     SYSCTL_PERIPH_GPIOA                             /*  System control of LED2      */
#define LED2_GPIO_PORT  GPIO_PORTA_BASE                                 /*  IO port of LED2             */
#define LED2_PIN        GPIO_PIN_0                                      /*  Pin number of LED2          */
#endif

#if TARGET_LED3_EN > 0
#define LED3_SYSCTL     SYSCTL_PERIPH_GPIOA                             /*  System control of LED3      */
#define LED3_GPIO_PORT  GPIO_PORTA_BASE                                 /*  IO port of LED3             */
#define LED3_PIN        GPIO_PIN_0                                      /*  Pin number of LED3          */
#endif

#if TARGET_LED4_EN > 0
#define LED4_SYSCTL     SYSCTL_PERIPH_GPIOA                             /*  System control of LED4      */
#define LED4_GPIO_PORT  GPIO_PORTA_BASE                                 /*  IO port of LED4             */
#define LED4_PIN        GPIO_PIN_0                                      /*  Pin number of LED4          */
#endif

#if TARGET_BUZ_EN > 0
#define BUZ_SYSCTL      SYSCTL_PERIPH_GPIOG                             /*  System control of the buzzer*/
#define BUZ_GPIO_PORT   GPIO_PORTG_BASE                                 /*  IO port of the buzzer       */  
#define BUZ_PIN         GPIO_PIN_1                                      /*  Pin number of the buzzer    */
#endif

#if TARGET_KEY1_EN > 0 
#define KEY1_SYSCTL    	SYSCTL_PERIPH_GPIOA	                            /*  System control of Key1      */ 
#define KEY1_GPIO_PORT  GPIO_PORTA_BASE     	                        /*  IO port of Key1             */
#define KEY1_PIN        GPIO_PIN_0                                      /*  Pin number of Key1          */
#endif

#if TARGET_KEY2_EN > 0  
#define KEY2_SYSCTL  	SYSCTL_PERIPH_GPIOA 	                        /*  System control of Key2      */
#define KEY2_GPIO_PORT  GPIO_PORTA_BASE     	                        /*  IO port of Key2             */
#define KEY2_PIN        GPIO_PIN_0          	                        /*  Pin number of Key2          */
#endif

#if TARGET_KEY3_EN > 0
#define KEY3_SYSCTL  	SYSCTL_PERIPH_GPIOA 	                        /*  System control of Key3      */
#define KEY3_GPIO_PORT  GPIO_PORTA_BASE     	                        /*  IO port of Key3             */
#define KEY3_PIN       	GPIO_PIN_0          	                        /*  Pin number of Key3          */
#endif

#if TARGET_KEY4_EN > 0
#define KEY4_SYSCTL 	SYSCTL_PERIPH_GPIOA		                        /*  System control of Key4      */
#define KEY4_GPIO_PORT  GPIO_PORTA_BASE     	                        /*  IO port of Key4             */
#define KEY4_PIN        GPIO_PIN_0          	                        /*  Pin number of Key4          */
#endif

#ifdef TARGET_KEY_SELECT_EN > 0
#define KEY_SELECT_SYSCTL		SYSCTL_PERIPH_GPIOF						/*  System control of Select Key */
#define KEY_SELECT_GPIO_PORT	GPIO_PORTF_BASE							/*  IO port of Select Key        */
#define KEY_SELECT_PIN			GPIO_PIN_1								/*  Pin number of Select Key     */
#endif

#ifdef TARGET_KEY_UP_EN > 0
#define KEY_UP_SYSCTL 			SYSCTL_PERIPH_GPIOE			/*  System control of Key      */
#define KEY_UP_GPIO_PORT  		GPIO_PORTE_BASE     	    /*  IO port of Key             */
#define KEY_UP_PIN        		GPIO_PIN_0          	    /*  Pin number of Key         */
#endif

#ifdef TARGET_KEY_DOWN_EN > 0
#define KEY_DOWN_SYSCTL 		SYSCTL_PERIPH_GPIOE			/*  System control of Key      */
#define KEY_DOWN_GPIO_PORT  	GPIO_PORTE_BASE     	    /*  IO port of Key             */
#define KEY_DOWN_PIN        	GPIO_PIN_1          	    /*  Pin number of Key         */
#endif

#ifdef TARGET_KEY_LEFT_EN > 0
#define KEY_LEFT_SYSCTL 		SYSCTL_PERIPH_GPIOE			/*  System control of Key      */
#define KEY_LEFT_GPIO_PORT  	GPIO_PORTE_BASE     	    /*  IO port of Key             */
#define KEY_LEFT_PIN        	GPIO_PIN_2         	    	/*  Pin number of Key         */
#endif

#ifdef TARGET_KEY_RIGHT_EN > 0
#define KEY_RIGHT_SYSCTL 		SYSCTL_PERIPH_GPIOE			/*  System control of Key      */
#define KEY_RIGHT_GPIO_PORT  	GPIO_PORTE_BASE     	    /*  IO port of Key             */
#define KEY_RIGHT_PIN        	GPIO_PIN_3          	    /*  Pin number of Key         */
#endif

#if TARGET_PWM_EN > 0
#define PWM_SYSCTL				SYSCTL_PERIPH_PWM
#define PWM_GPIO_PORT		
#define PWM_PIN
#endif

#if TARGET_UART_EN > 0
#define UART_SYSCTL				SYSCTL_PERIPH_UART0
#define UART_GPIO_PORT
#define UART_PIN
#endif


/*********************************************************************************************************
  End of user's settings 
*********************************************************************************************************/
  

/*********************************************************************************************************
  Function Prototypes                                     
*********************************************************************************************************/
/*********************************************************************************************************
** Function name:           IntDisAll                                                                   **
** Descriptions:            Disable all interrupts from the interrupt controller                        **     
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
extern void IntDisAll (void);


/*********************************************************************************************************
** Function name:           LedInit                                                                     **
** Descriptions:            Initialize the target board's leds,support up to 4 leds                     **     
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if (TARGET_LED_EN > 0) || (TARGET_LED1_EN > 0) || (TARGET_LED2_EN >0 ) || (TARGET_LED3_EN > 0) || (TARGET_LED4_EN > 0)  
    extern void LedInit (void);
#endif


/*********************************************************************************************************
** Function name:           LedOn                                                                       **
** Descriptions:            Switch on one or all of the LEDs                                            **     
** input parameters:        led: The num.of led to be switched on, 1-4 for LED1-LED4,                   **
**                          0xFF for all leds, others no actio                                          **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if (TARGET_LED_EN > 0) || (TARGET_LED1_EN > 0) || (TARGET_LED2_EN > 0) || (TARGET_LED3_EN > 0) || (TARGET_LED4_EN > 0) 
    extern void LedOn (INT8U  ucLed);
#endif


/*********************************************************************************************************
** Function name:          LedOff                                                                       **
** Descriptions:            Switch off one or all of the LEDs                                           **     
** input parameters:        led: The num.of led to be switched off, 1-4 for LED1-LED4,                  **
**                          0xFF for all leds, others no actio                                          **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if (TARGET_LED_EN > 0) || (TARGET_LED1_EN > 0) || (TARGET_LED2_EN > 0) || (TARGET_LED3_EN > 0) || (TARGET_LED4_EN > 0)
    extern void LedOff (INT8U  ucLed);
#endif


/*********************************************************************************************************
** Function name:           LedToggle                                                                   **
** Descriptions:            Toggle one or all of the LEDs                                               **     
** input parameters:        led: The num.of led to be toggled, 1-4 for LED1-LED4,                       **
**                          0xFF for all leds, others no actio                                          **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if (TARGET_LED_EN > 0) || (TARGET_LED1_EN > 0) || (TARGET_LED2_EN > 0) || (TARGET_LED3_EN > 0) || (TARGET_LED4_EN > 0)
    extern void LedToggle (INT8U  ucLed);
#endif


/*********************************************************************************************************
** Function name:           BuzInit                                                                     **
** Descriptions:            Initialize the target board's buzzer                                        **     
** input parameters:        None                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if TARGET_BUZ_EN > 0
    extern void BuzInit (void);
#endif


/*********************************************************************************************************
** Function name:           BuzOn                                                                       **
** Descriptions:            Switch on the buzzer                                                        **     
** input parameters:        None                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if TARGET_BUZ_EN > 0
    extern void BuzOn (void);
#endif


/*********************************************************************************************************
** Function name:           BuzOff                                                                      **
** Descriptions:            Switch off the buzzer                                                       **     
** input parameters:        None                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if TARGET_BUZ_EN > 0
    extern void BuzOff (void);
#endif


/*********************************************************************************************************
** Function name:           BuzToggle                                                                   **
** Descriptions:            Toggle the buzzer                                                           **     
** input parameters:        None                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if TARGET_BUZ_EN > 0
    extern void BuzToggle (void);    
#endif


/*********************************************************************************************************
** Function name:           BuzFrequency                                                                **
** Descriptions:            Set the buzzer's frequency                                                  **     
** input parameters:        ulFrequency                                                                 **
** output parameters:       none                                                                        **
** Returned value:          none                                                                        **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            12-04-2013                                                                  **
*********************************************************************************************************/
#if TARGET_BUZ_EN > 0
    extern void BuzFrequency (INT32U ulFrequency);    
#endif


/*********************************************************************************************************
** Function name:           PWMInit                                                                     **
** Descriptions:            Initialize the target PWM                                                   **     
** input parameters:        None                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if TARGET_PWM_EN > 0
    extern void PWMInit (void);
#endif


/************************************************************************************
** Function: setPWMState()
** Routine Description: - 
**     Turn PWM on/off  
** Input parameters: - 
**    NONE 
** Output parameters: NONE
** Returned Value: NONE
** Remarks:
** 
** Date created: 23:09:42,27/05/2012
** Author: Long.Luo
************************************************************************************/
#if TARGET_PWM_EN > 0
	extern void SetPWMState(tBoolean bOn);
#endif


/************************************************************************************
** Function: SetPWMFrequency()
** Routine Description: - 
**     set the PWM frequency 
** Input parameters: - 
** 		ulFrequency
** Output parameters: NONE
** Returned Value: NONE
** Remarks:
** 
** Date created: 23:01:20,22/05/2012
** Author: Long.Luo
************************************************************************************/
#if TARGET_PWM_EN > 0
	extern void SetPWMFrequency(INT32U ulFrequency);
#endif


/************************************************************************************
** Function: setPWMDutyCycle()
** Routine Description: - 
**     the buzzer voice 
** Input parameters: - 
** 
** Output parameters: NONE
** Returned Value: NONE
** Remarks:
** 
** Date created: 23:01:58,22/05/2012
** Author: Long.Luo
************************************************************************************/
#if TARGET_PWM_EN > 0
	extern void SetPWMDutyCycle(INT32U ulDutyCycle);
#endif


/*********************************************************************************************************
** Function name:           keyInit                                                                     **
** Descriptions:            Initialize the target board's keys,support up to 4 keys                     **     
** input parameters:        None                                                                        **
** output parameters:       none                                                                        **
** Returned value:          8-bit unsigned char data. Bit0-bit3 stand for the status of Key1-Key4,      **
**                          bit4-Bit7 no meaning                                                        **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if (TARGET_KEY1_EN > 0) ||  (TARGET_KEY2_EN > 0) || (TARGET_KEY3_EN > 0) || (TARGET_KEY4_EN > 0)
	|| (TARGET_KEY_SELECT_EN > 0) || (TARGET_KEY_UP_EN > 0) || (TARGET_KEY_DOWN_EN > 0) || (TARGET_KEY_LEFT_EN > 0) ||  (TARGET_KEY_RIGHT_EN > 0)
    extern void keyInit (void);    
#endif


/*********************************************************************************************************
** Function name:           keyRead                                                                     **
** Descriptions:            Read the status of the keys.                                                **     
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if (TARGET_KEY1_EN > 0) ||  (TARGET_KEY2_EN > 0) || (TARGET_KEY3_EN > 0) || (TARGET_KEY4_EN > 0)
	|| (TARGET_KEY_SELECT_EN > 0) || (TARGET_KEY_UP_EN > 0) || (TARGET_KEY_DOWN_EN > 0) || (TARGET_KEY_LEFT_EN > 0) ||  (TARGET_KEY_RIGHT_EN > 0)
    extern INT8U keyRead (void);    
#endif


/*********************************************************************************************************
** Function name:           timer0AInit                                                                 **
** Descriptions:            Initialize Timer0A to 32bit timeout                                         **     
** input parameters:        Tick: Number of timeout tick                                                **
**                          Prio: Interrupt priority                                                    **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if TARGET_TMR0A_EN > 0
    extern void timer0AInit (INT32U  ulTick, INT8U  ucPrio);
#endif


/*********************************************************************************************************
** Function name:           timer0AISR                                                                  **
** Descriptions:            Timeout interrupt handler of Timer0A                                        **     
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if TARGET_TMR0A_EN > 0
    extern void timer0AISR (void);
#endif


/*********************************************************************************************************
** Function name:           tickISRHandler                                                              **
** Descriptions:            Timeout interrupt handler of system timer                                   **     
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
extern void tickISRHandler (void);



/*********************************************************************************************************
** Function name:           InvertTemperature                                                           **
** Descriptions:            Invert the temperature                                                      **     
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            12-04-2013                                                                  **
*********************************************************************************************************/ 
#if TARGET_ADC_EN > 0
	extern INT32U InvertTemperature(INT32U ulValue);
#endif


/*********************************************************************************************************
** Function name:           InitADC                                                                     **
** Descriptions:            Initialize the ADC board                                                    **     
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
#if TARGET_ADC_EN > 0
	extern void InitADC(void);
#endif


/*********************************************************************************************************
** Function name:           ADCSample                                                                   **
** Descriptions:            Initialize the target board                                                 **     
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            10-04-2013                                                                  **
*********************************************************************************************************/ 
#if TARGET_ADC_EN > 0
	extern INT32U ADCSample(void);
#endif


/*********************************************************************************************************
** Function name:           InitTarget                                                                  **
** Descriptions:            Initialize the target board                                                 **     
** input parameters:        none                                                                        **
** output parameters:       none                                                                        **
** Returned value:          noe                                                                         **
==========================================================================================================
** Created by:              long.luo                                                                    **
** Created Date:            11-04-2013                                                                  **
*********************************************************************************************************/
extern void InitTarget (void);


#ifdef __cplusplus
    }
#endif

#endif

/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/

