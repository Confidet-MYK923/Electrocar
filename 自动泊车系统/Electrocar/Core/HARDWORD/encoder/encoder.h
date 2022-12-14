/**
  *************************************************************************************************************************
  * @file    : xxx.h
  * @author  :Confident
  * @version : V1.0
  * @date    : 2022-XX-XX
  * @brief   : STM32Fxxx核心板核心板驱动程序--xxx模块H文件
  *************************************************************************************************************************
  * @attention
  * 
  * 
  * 
  *************************************************************************************************************************
  */


/* Define to prevent recursive inclusion --------------------------------------------------------------------------------*/
#ifndef __ENCODER_H__
#define __ENCODER_H__
/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"


/* define ---------------------------------------------------------------------------------------------------------------*/



/* function -------------------------------------------------------------------------------------------------------------*/

int Read_Speed(int TIMx);
void Encoder_TIM_Init(void);


#endif /* __XXX_H */
/*****************************************************END OF FILE*********************************************************/	



