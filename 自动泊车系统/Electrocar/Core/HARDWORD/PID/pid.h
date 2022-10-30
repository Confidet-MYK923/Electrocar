#ifndef __PID_H
#define	__PID_H

#include "control.h"

typedef struct 
{
	float Kp;
	float Kd;
	float error;
	float lasterror;
	float target_value;
	float actual_value;
	
}PIDTypeDef;
extern PIDTypeDef PID;
void PID_Param_Init(void);
float PID_Realize(float position,float target_value);

#endif  /*__SERVO_H*/

