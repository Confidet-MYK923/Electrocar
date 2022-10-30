/**
  *************************************************************************************************************************
  * @file    : xxx.c
  * @author  : Confident
  * @version : V1.0
  * @date    : 2022-XX-XX
  * @brief   : STM32Fxxx���İ���İ���������--xxxģ��C�ļ�
  *************************************************************************************************************************
  * @attention
  *ִ���ļ�
  * 
  *
  *************************************************************************************************************************
  */

/* Includes -------------------------------------------------------------------------------------------------------------*/
 #include "encoder.h"
/* define ---------------------------------------------------------------------------------------------------------------*/

void Encoder_TIM_Init(void)//��������ʱ����ʼ��
{

	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_1);//������ 
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_2);
	
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_2);	
	
}

int Read_Speed(int TIMx)
{
	int value;
	switch(TIMx)
	{
		case 2:value=(short)__HAL_TIM_GET_COUNTER(&htim2);__HAL_TIM_SET_COUNTER(&htim2,0);break;//IF�Ƕ�ʱ��2��1.�ɼ��������ļ���ֵ�����档2.����ʱ���ļ���ֵ���㡣
		case 4:value=(short)__HAL_TIM_GET_COUNTER(&htim4);__HAL_TIM_SET_COUNTER(&htim4,0);break;
		default:value=0;
	}
	return value;
}

