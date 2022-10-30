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
#ifndef __CONTROL_H__
#define __CONTROL_H__
/* Includes -------------------------------------------------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "motor.h"
#include "encoder.h"
#include "servo.h"
#include "oled.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "IIC.h"
#include "key.h"
#include "pid.h"
#include "math.h"
/* define ---------------------------------------------------------------------------------------------------------------*/
typedef struct 
{
	int16_t Isstop;
	int8_t key0anxia;
	int8_t carqidong;
	int8_t carqidong2;
	int8_t totime;
	int16_t time5s;
	int16_t time_daoche;
	int16_t time_turn;
	int16_t time_back;//
	int16_t time2_back;//二条
//	int16_t time_backduan;
	
	int16_t time_one;
	int16_t time_Leftdasi;
	int16_t time_qianjin;
	int16_t time_qianjinzuo;
	int16_t houtui;
	int16_t chuku;
}FLAGTypeDef;

typedef struct 
{
	int16_t Rcnt;
	int16_t Lcnt;
	int16_t hedata;
	int16_t carstep;
	int16_t car2step;
	int16_t time;
	int16_t time5s;
	
	float yaw;//矫正航向角
	float pwm;
	int16_t Righ_Target;
	int16_t left_Target;
	int16_t to_turn;//用于倒库转弯后时间
	int16_t to_daoche;//用于倒库时间
	int16_t to_back;
	int16_t to2_back;
	int16_t to_dasi;
//	int16_t to_backduan;
	
	int16_t to_one;
	int16_t to_qianjin;
	int16_t to_qianjinzuo;
	int16_t houtui;
	int16_t chuku;
	
}INDEXTypeDef;

typedef struct 
{
	int16_t aacx;//加速度
	int16_t aacy;
	int16_t aacz;
	
	int16_t gyrox;//角速度
	int16_t gyroy;
	int16_t gyroz;
	
	float pitch;//俯仰角
	float roll;//横滚角 
	float yaw;//航向角 
	float temp;
	
}MPU6050TypeDef;


extern INDEXTypeDef Index;
extern FLAGTypeDef flag;
extern  MPU6050TypeDef OutMpu;
/* funciton ---------------------------------------------------------------------------------------------------------------*/

void ALL_Init(void);
void zhuhanshu(void);

void zhuhanshu2(void);
void param_Init(void);
void angle_Judge(int16_t speed,int16_t jiaodu);

#endif /* __XXX_H */
/*****************************************************END OF FILE*********************************************************/	


