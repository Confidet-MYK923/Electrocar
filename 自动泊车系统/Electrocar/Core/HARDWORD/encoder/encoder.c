/**
  *************************************************************************************************************************
  * @file    : xxx.c
  * @author  : Confident
  * @version : V1.0
  * @date    : 2022-XX-XX
  * @brief   : STM32Fxxx核心板核心板驱动程序--xxx模块C文件
  *************************************************************************************************************************
  * @attention
  *执行文件
  * 
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
 #include "encoder.h"
/* define ---------------------------------------------------------------------------------------------------------------*/

void Encoder_TIM_Init(void)//编码器定时器初始化
{

	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_1);//编码器 
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_2);
	
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_2);	
	
}

int Read_Speed(int TIMx)
{
	int value;
	switch(TIMx)
	{
		case 2:value=(short)__HAL_TIM_GET_COUNTER(&htim2);__HAL_TIM_SET_COUNTER(&htim2,0);break;//IF是定时器2，1.采集编码器的计数值并保存。2.将定时器的计数值清零。
		case 4:value=(short)__HAL_TIM_GET_COUNTER(&htim4);__HAL_TIM_SET_COUNTER(&htim4,0);break;
		default:value=0;
	}
	return value;
}

