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
#ifndef __MOTOR_H__
#define __MOTOR_H__
/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "control.h"

#define OUT4_Pin GPIO_PIN_12
#define OUT4_GPIO_Port GPIOB
#define OUT3_Pin GPIO_PIN_15
#define OUT3_GPIO_Port GPIOA
#define OUT2_Pin GPIO_PIN_3
#define OUT2_GPIO_Port GPIOB
#define LED0_Pin GPIO_PIN_5
#define LED0_GPIO_Port GPIOB
#define OUT1_Pin GPIO_PIN_8
#define OUT1_GPIO_Port GPIOB
/* define ---------------------------------------------------------------------------------------------------------------*/
//左电机
#define IN1_SET HAL_GPIO_WritePin(OUT1_GPIO_Port, OUT1_Pin, GPIO_PIN_SET)
#define IN1_RESET HAL_GPIO_WritePin(OUT1_GPIO_Port, OUT1_Pin, GPIO_PIN_RESET)

#define IN2_SET HAL_GPIO_WritePin(OUT2_GPIO_Port, OUT2_Pin, GPIO_PIN_SET)
#define IN2_RESET HAL_GPIO_WritePin(OUT2_GPIO_Port, OUT2_Pin, GPIO_PIN_RESET)

//右电机
#define IN3_SET HAL_GPIO_WritePin(OUT3_GPIO_Port, OUT3_Pin, GPIO_PIN_SET)
#define IN3_RESET HAL_GPIO_WritePin(OUT3_GPIO_Port, OUT3_Pin, GPIO_PIN_RESET)

#define IN4_SET HAL_GPIO_WritePin(OUT4_GPIO_Port, OUT4_Pin, GPIO_PIN_SET)
#define IN4_RESET HAL_GPIO_WritePin(OUT4_GPIO_Port, OUT4_Pin, GPIO_PIN_RESET)

//电机方向
#define FORWARD 1
#define BACK 2
#define STOP 0

/* function -------------------------------------------------------------------------------------------------------------*/
void Motor_TIM_Init(void);
void MOTOR_LEFT_DIR(uint8_t dir_choose);
void MOTOR_RIGH_DIR(uint8_t dir_choose);
void MOTOR_LOAD_PWM(int PWM1,int PWM2);
void Motor_Set_Enable(void);
void Motor_Set_Disable(void);
int abs(int p);



#endif /* __XXX_H */
/*****************************************************END OF FILE*********************************************************/	



