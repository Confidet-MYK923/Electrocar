
#include "servo.h"

float Init_CompareX;//舵机占空比初始值

float Angle_Flag_X=0.0;

/*
 *舵机初始化 初始角度
 *
 */
void Servo_Angle_Init(void)
{
 Servo_X_Angle_Init(SERVO_X_INIT_ANGLE);//X轴舵机初始化
}

/*X轴舵机初始化微调
 *Angle:调整角度
 *Direction:调整方向*/
void Servo_X_Angle_Init(float Angle)
{
 
  Init_CompareX =50+(((Angle+90)*(1/90.0))/20*TIM3_ARR);//90度补偿，50ms补偿
	Angle_Flag_X=Angle;//当前角度
 __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, Init_CompareX);

}

/*********************************************END OF FILE*****************************************/


