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
 #include "motor.h"
/* define ---------------------------------------------------------------------------------------------------------------*/

#define FORWARD 1
#define BACK 2
#define STOP 0

void Motor_TIM_Init(void)//电机定时器使能
{
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);//PWM 1kZ 7199
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);	
}
void MOTOR_LEFT_DIR(uint8_t dir_choose)//左电机
{
	if(dir_choose==FORWARD)
	{
		
		IN1_SET;IN2_RESET;
		
	}
	else if(dir_choose==BACK)
	{
		IN1_RESET;IN2_SET;
		
	}
	else if(dir_choose==STOP)
	{
		IN1_SET;IN2_SET;
	}
}	

void MOTOR_RIGH_DIR(uint8_t dir_choose)//右电机
{
	if(dir_choose==FORWARD)
	{
		IN3_RESET;IN4_SET;
		
	}
	else if(dir_choose==BACK)
	{
		IN3_SET;IN4_RESET;
		
	}
	else if(dir_choose==STOP)
	{
		IN3_SET;IN4_SET;
	}
}	
#define PWM_MAX 7000

void MOTOR_LOAD_PWM(int PWM1,int PWM2)//装载PWM
{
	PWM1 = abs(PWM1);//左
	PWM2 = abs(PWM2);//右
	PWM1=(PWM1>PWM_MAX)?PWM_MAX:PWM1;
	PWM2=(PWM2>PWM_MAX)?PWM_MAX:PWM2;	
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, PWM1);//左
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, PWM2);//左
}
void Motor_Set_Enable(void)//使能电机
{
	//存在标志位
	flag.Isstop=0;//不停车
	MOTOR_LEFT_DIR(FORWARD);
	MOTOR_RIGH_DIR(FORWARD);
}
void Motor_Set_Disable(void)//失能电机
{
	//存在标志位
	flag.Isstop=1;//停车
	MOTOR_LEFT_DIR(STOP);
	MOTOR_RIGH_DIR(STOP);
}
int abs(int p)
{
	int q;
	q=p>0?p:(-p);
	return q;
}

