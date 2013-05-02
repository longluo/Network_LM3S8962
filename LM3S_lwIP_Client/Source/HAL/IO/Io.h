/************************************************************************************
** File: - E:\ARM\lm3s8962projects\WebIO\Source\HAL\IO\Io.h
**  
** Copyright (C), Long.Luo, All Rights Reserved!
** 
** Description: 
**      io.h - Prototypes for I/O routines for the enet_io example.
** 
** Version: 1.1
** Date created: 23:40:15,14/04/2013
** Author: Long.Luo
** 
** --------------------------- Revision History: --------------------------------
** 	<author>	<data>			<desc>
** 
************************************************************************************/

#ifndef __IO_H__
#define __IO_H__

#ifdef __cplusplus
extern "C"
{
#endif

void io_init(void);
void io_set_led(tBoolean bOn);
void io_set_pwm(tBoolean bOn);
void io_pwm_freq(unsigned long ulFreq);
void io_pwm_dutycycle(unsigned long ulDutyCycle);
unsigned long io_get_pwmfreq(void);
unsigned long io_get_pwmdutycycle(void);
void io_get_ledstate(char * pcBuf, int iBufLen);
int io_is_led_on(void);
void io_get_pwmstate(char * pcBuf, int iBufLen);
int io_is_pwm_on(void);
void sendtext2serial(unsigned char * c);

#ifdef __cplusplus
}
#endif

#endif /* __IO_H__ */

