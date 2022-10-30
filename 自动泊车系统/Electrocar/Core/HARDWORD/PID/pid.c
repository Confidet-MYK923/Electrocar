#include <pid.h>


PIDTypeDef PID;
void PID_Param_Init(void)
{
	PID.Kp=-8;
	PID.Kd=6;
	PID.error=0.0;
	PID.lasterror=0.0;
	PID.target_value=0.0;
	PID.actual_value=0.0;
}
float PID_Realize(float position,float target_value)
{
	//1,赋值，目标值传入PID参数 
	PID.target_value=target_value;
	PID.actual_value=position;
	//2.计算偏差
	PID.error=PID.target_value-PID.actual_value;
	//3.计算输出 
	PID.actual_value=PID.Kp*PID.error+PID.Kd*(PID.error-PID.lasterror);
	//4.累计偏差 
	PID.lasterror=PID.error;
	return PID.actual_value;
}

