
#include "servo.h"

float Init_CompareX;//���ռ�ձȳ�ʼֵ

float Angle_Flag_X=0.0;

/*
 *�����ʼ�� ��ʼ�Ƕ�
 *
 */
void Servo_Angle_Init(void)
{
 Servo_X_Angle_Init(SERVO_X_INIT_ANGLE);//X������ʼ��
}

/*X������ʼ��΢��
 *Angle:�����Ƕ�
 *Direction:��������*/
void Servo_X_Angle_Init(float Angle)
{
 
  Init_CompareX =50+(((Angle+90)*(1/90.0))/20*TIM3_ARR);//90�Ȳ�����50ms����
	Angle_Flag_X=Angle;//��ǰ�Ƕ�
 __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, Init_CompareX);

}

/*********************************************END OF FILE*****************************************/


