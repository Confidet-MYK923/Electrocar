#ifndef __SERVO_H
#define	__SERVO_H

#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
/*TIM3*/
#define TIM3_ARR							(2000-1)//����
#define TIM3_PSC							(720-1)//Ԥ��Ƶֵ

/*Servo*/

#define SERVO_X_INIT_ANGLE		(0)//��������Ƕ�

extern float Angle_Flag_X;
void Servo_Angle_Init(void);

void Servo_X_Angle_Init(float Angle);


#endif  /*__SERVO_H*/
