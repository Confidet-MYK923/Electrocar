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
 #include "control.h"
/* define ---------------------------------------------------------------------------------------------------------------*/
FLAGTypeDef flag;
MPU6050TypeDef OutMpu;
INDEXTypeDef Index;
uint8_t UART_Receive_buffer[1]={0};



void param_Init(void)
{
	Index.carstep=0;
	Index.car2step=0;
	flag.totime=1;
	flag.time5s=1;
	flag.time_daoche=1;
	flag.time_turn=1;
	flag.time_back=1;
	flag.time_one=1;
	flag.time_Leftdasi=1;
	flag.time_qianjinzuo=1;
	flag.houtui=1;
	flag.chuku=1;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART3)
	{
		HAL_UART_Receive_IT(&huart3,UART_Receive_buffer, 1);//3收到数据
		switch(UART_Receive_buffer[0])
		{
			case '1':Index.hedata=1;break;
			case '2':Index.hedata=2;break;
			case '3':Index.hedata=3;break;
			case '4':Index.hedata=4;break;
			case '5':Index.hedata=5;break;
		}
//		if(UART_Receive_buffer[0]=='1')
//		{
//			Index.hedata=1;
//			printf("hedata=%d\n",Index.hedata);
//		}
	}
}

//#define TIMEMUBIAO 60//目标时间(后期需要更改时间)
//#define DUOCHE 170//倒库时间
//#define TURN 20//转弯时间
//#define WUMIAO 500//5s停车
//#define BACKTIME 95//倒车时间
//#define TIMEONE 100//1s停车时间
#define TIMEMUBIAO 55//目标时间(后期需要更改时间)
#define DUOCHE 130//倒库时间
#define TURN 20//转弯时间
#define WUMIAO 500//5s停车
#define BACKTIME 100//倒车时间
#define TIMEONE 100//1s停车时间

#define HOUTUI 1
#define CHUKU 400

////////////////
#define INIT 1
////////////////////侧方
#define BACK2TIME 280//侧方右倒库
#define LEFTDASI 250//左打死计时
#define QIANJIN 50//前进时间
#define QIANJINZUO 50//出库前进时间
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance ==TIM5)//10ms
	{
		mpu_dmp_get_data(&OutMpu.pitch, &OutMpu.roll, &OutMpu.yaw);
		OutMpu.yaw=OutMpu.yaw+0.9;
//		Index.Lcnt = -Read_Speed(2);//左右轮速度
//		Index.Rcnt = Read_Speed(4);
		if(flag.totime==0)//,用于延时发送，停车
		{
			Index.time++;
			if(Index.time==TIMEMUBIAO)
			{
				flag.totime=1;
				Index.time=0;
			}
		}
		if(flag.time5s==0)
		{
			Index.time5s++;
			if(Index.time5s==WUMIAO)//5s
			{
				flag.time5s=1;
				Index.time5s=0;
			}
		}
		if(flag.time_daoche==0)
		{
			Index.to_daoche++;
			if(Index.to_daoche==DUOCHE)//1s
			{
				flag.time_daoche=1;
				Index.to_daoche=0;
			}
		}
		if(flag.time_turn==0)
		{
			Index.to_turn++;
			if(Index.to_turn==TURN)//1s
			{
				flag.time_turn=1;
				Index.to_turn=0;
			}
		}
		if(flag.time_back==0)
		{
			Index.to_back++;
			if(Index.to_back==BACKTIME)
			{
				flag.time_back=1;
				Index.to_back=0;
				
			}
		}
		
		
		if(flag.time_one==0)
		{
			Index.to_one++;
			if(Index.to_one==TIMEONE)
			{
				flag.time_one=1;
				Index.to_one=0;
				
			}
		}
		
		if(flag.houtui==0)
		{
			Index.houtui++;
			if(Index.houtui==HOUTUI)
			{
				flag.houtui=1;
				Index.houtui=0;
			}
		}
		
		if(flag.chuku==0)
		{
			Index.chuku++;
			if(Index.chuku==CHUKU)
			{
				flag.chuku=1;
				Index.chuku=0;
			}
		}
		
		/////////////////////////////////////////////
		if(flag.time2_back==0)//右打死
		{
			Index.to2_back++;
			if(Index.to2_back==BACK2TIME)
			{
				flag.time2_back=1;
				Index.to2_back=0;
			}
		}
		if(flag.time_Leftdasi==0)//左打死
		{
			Index.to_dasi++;
			if(Index.to_dasi==LEFTDASI)
			{
				flag.time_Leftdasi=1;
				Index.to_dasi=0;
			}
		}
	
		if(flag.time_qianjin==0)//左打死
		{
			Index.to_qianjin++;
			if(Index.to_qianjin==QIANJIN)
			{
				flag.time_qianjin=1;
				Index.to_qianjin=0;
			}
		}
//		if(flag.time_qianjinzuo==0)//左打死
//		{
//			Index.to_qianjinzuo++;
//			if(Index.to_qianjin==QIANJIN)
//			{
//				flag.time_qianjinzuo=1;
//				Index.to_qianjinzuo=0;
//			}
//		}
		
		if(flag.time_qianjinzuo==0)//左打死
		{
			Index.to_qianjinzuo++;
			if(Index.to_qianjinzuo==QIANJINZUO)
			{
				flag.time_qianjinzuo=1;
				Index.to_qianjinzuo=0;
			}
		}
		
	}
}
#define HEINIT 0//何润韬偏移通信地址

void zhuhanshu2(void)
{
	if(flag.carqidong2==1)
	{
		switch(Index.car2step)
		{
			case 0://直线行驶
						Index.pwm=PID_Realize(OutMpu.yaw,0); //目标值为0
						Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
						MOTOR_LEFT_DIR(FORWARD);
						MOTOR_RIGH_DIR(FORWARD);
						MOTOR_LOAD_PWM(4500,4500);
						if(Index.hedata==(1+HEINIT))//第一次检测点，此处不允许停车，告诉何重新开始
						{
							//1.延时发送数据计时
							flag.totime=0;//开始计时
							//3.下一步
							Index.car2step=1;
						}
			break;
			case 1://时间到，交互数据
						if(flag.totime==1)
						{
							//1。发数据
								HAL_UART_Transmit(&huart3,"A",1,0xffff);//3输出
							//还是正常走
								Index.pwm=PID_Realize(OutMpu.yaw,0); //目标值为0
								Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
								MOTOR_LEFT_DIR(FORWARD);
								MOTOR_RIGH_DIR(FORWARD);
								MOTOR_LOAD_PWM(4500,4500);
								//2.下一步
								Index.car2step=2;
						}
			break;
						
			case 2://收何数据//第二次
						if(Index.hedata==(2+HEINIT))//第二次
						{
							flag.totime=0;//开始计时不需要的数据
							Index.car2step=3;
						}
			break;
			case 3://时间到，发信息，继续直行
						if(flag.totime==1)
						{
							//1。发数据
							HAL_UART_Transmit(&huart3,"A",1,0xffff);//2输出
							//还是正常走
							Index.pwm=PID_Realize(OutMpu.yaw,0); //目标值为0
							Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
							MOTOR_LEFT_DIR(FORWARD);
							MOTOR_RIGH_DIR(FORWARD);
							MOTOR_LOAD_PWM(4500,4500);
							//2.下一步
							Index.car2step=4;
						}
			break;
			case 4://接收何有效数据，第三次
						if(Index.hedata==(3+HEINIT))//第三次
						{
							flag.time_one=0;//开始计时//目的停车   1s定时
							//需要停车
							Motor_Set_Disable();
							//蜂鸣器打开
							HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//响
							Index.car2step=5;
						}
			break;
			case 5://等待时间到达
						if(flag.time_one==1)
						{
							//1。发数据
							HAL_UART_Transmit(&huart3,"B",1,0xffff);//关闭摄像头
							//蜂鸣器关闭
							HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//不响
							
							//开始侧库计时
							flag.time2_back=0;///右倒库开始
							//2.下一步
							Index.car2step=6;//开始测库倒车
						}
			break;
						
						//上无问题
			case 6://侧库
						Servo_X_Angle_Init(70);//右打死  -90~90
						MOTOR_LEFT_DIR(BACK);
						MOTOR_RIGH_DIR(BACK);
						MOTOR_LOAD_PWM(4500,4500);
			
						if(flag.time2_back==1)//时间到
						{
							//停车一段时间
						
							flag.time_Leftdasi=0;//开始计时
							//2下一步
							Index.car2step=7;
						}
			break;
			case 7:
						Servo_X_Angle_Init(-70);//打死  -90~90
						MOTOR_LEFT_DIR(BACK);
						MOTOR_RIGH_DIR(BACK);
						MOTOR_LOAD_PWM(4500,4500);
						if(flag.time_Leftdasi==1)
						{
							Motor_Set_Disable();
							
							flag.time_qianjin=0;
							Index.car2step=8;
						}
//						if(flag.totime==1)
//						{
//							//左打死计时操作
//							flag.time_Leftdasi=0;//开始计时
//							//下一步
//							Index.car2step=8;
//						}
			break;
			case 8://进库之后前进
						Servo_X_Angle_Init(5);//左打
						MOTOR_LEFT_DIR(FORWARD);
						MOTOR_RIGH_DIR(FORWARD);
						MOTOR_LOAD_PWM(4500,4500);
						if(flag.time_qianjin==1)
						{
							HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//响
							Motor_Set_Disable();
							flag.totime=0;
							Index.car2step=9;
						}
			break;
			case 9:
							if(flag.totime==1)
							{
								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//不响
								//5s计时开始
								flag.time5s=0;
								Index.car2step=10;
							}
			break;
			case 10:
							if(flag.time5s==1)
							{
								flag.time_qianjin=0;
								Index.car2step=11;
							}
			break;			
			case 11:
							Servo_X_Angle_Init(5);//左打
							MOTOR_LEFT_DIR(BACK);
							MOTOR_RIGH_DIR(BACK);
							MOTOR_LOAD_PWM(4500,4500);
							if(flag.time_qianjin==1)
							{
								flag.time_qianjinzuo=0;
								Index.car2step=12;
							}
			break;	
			case 12:
							Servo_X_Angle_Init(-40);//左打
							MOTOR_LEFT_DIR(FORWARD);
							MOTOR_RIGH_DIR(FORWARD);
							MOTOR_LOAD_PWM(4400,5500);
//							HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//响
							if(flag.time_qianjinzuo==1)
							{
//								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//不响
								flag.totime=0;
								Index.car2step=13;
							}
				
			break;
			case 13:
							if(flag.totime==1)
							{
								flag.time_qianjinzuo=0;//右打死出库
								Index.car2step=14;
							}
			break;
							
			case 14: 
							Servo_X_Angle_Init(80);//右打
							MOTOR_LEFT_DIR(FORWARD);
							MOTOR_RIGH_DIR(FORWARD);
							MOTOR_LOAD_PWM(5500,4500);
							if(flag.time_qianjinzuo==1)
							{ 
								Servo_X_Angle_Init(0);
								Motor_Set_Disable();
								Index.car2step=15;
							}
							
			break;
			
			
		}
	}
	else 
	{Motor_Set_Disable();}
}
void zhuhanshu(void)//计划放在主函数里
{
//泊车启动之后
	if(flag.carqidong==1)
		{
			switch(Index.carstep)
			{
				case 0://直线行驶
							Index.pwm=PID_Realize(OutMpu.yaw,INIT); //目标值为0
							Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
							MOTOR_LEFT_DIR(FORWARD);
							MOTOR_RIGH_DIR(FORWARD);
							MOTOR_LOAD_PWM(4500,4500);
							if(Index.hedata==1)//第一次检测点，此处不允许停车，告诉何重新开始
							{
								//1.延时发送数据计时
								flag.totime=0;//开始计时
								//3.下一步
								Index.carstep=1;
							}
							
				break;
				case 1://时间到，发送数据
							if(flag.totime==1)
							{
								//1。发数据
								HAL_UART_Transmit(&huart3,"A",1,0xffff);//2输出
								//还是正常走
								Index.pwm=PID_Realize(OutMpu.yaw,INIT); //目标值为0
								Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
								MOTOR_LEFT_DIR(FORWARD);
								MOTOR_RIGH_DIR(FORWARD);
								MOTOR_LOAD_PWM(4500,4500);
								//2.下一步
								Index.carstep=2;
							}
				break;
							
							
				case 2://收何数据
							if(Index.hedata==2)//第二次
							{
								flag.totime=0;//开始计时不需要的数据
								Index.carstep=3;
							}
				break;
				case 3://时间到
							if(flag.totime==1)
							{
								//1。发数据
								HAL_UART_Transmit(&huart3,"A",1,0xffff);//2输出
								//还是正常走
								Index.pwm=PID_Realize(OutMpu.yaw,INIT); //目标值为0
								Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
								MOTOR_LEFT_DIR(FORWARD);
								MOTOR_RIGH_DIR(FORWARD);
								MOTOR_LOAD_PWM(4500,4500);
								//2.下一步
								Index.carstep=4;
							}					
				break;
				
				case 4://何数据第三次
							if(Index.hedata==3)//第三次
							{
								flag.totime=0;//开始计时不需要的数据
								Index.carstep=5;
							}
				break;
				case 5://时间到
							if(flag.totime==1)
							{
								//1。发数据
								HAL_UART_Transmit(&huart3,"A",1,0xffff);//2输出
								//还是正常走
								Index.pwm=PID_Realize(OutMpu.yaw,INIT); //目标值为0
								Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
								MOTOR_LEFT_DIR(FORWARD);
								MOTOR_RIGH_DIR(FORWARD);
								MOTOR_LOAD_PWM(4500,4500);
								//2.下一步
								Index.carstep=6;
							}					
				break;
							
				case 6://收何有效数据
							if(Index.hedata==4)//第四次
							{
								flag.time_one=0;//开始计时//目的停车
								//需要停车
								Motor_Set_Disable();
								//蜂鸣器打开
								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//响
								Index.carstep=7;
							}
				break;
				case 7://停车时间到
							if(flag.time_one==1)
							{
								//1。发数据
								HAL_UART_Transmit(&huart3,"B",1,0xffff);//
								//蜂鸣器关闭
								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//不响
								//开始倒车计时
								flag.time_back=0;
								//2.下一步
								Index.carstep=8;//开始倒车
							}
				break;	///上没问题
							
							
				case 8://倒车
								Servo_X_Angle_Init(-2);////记不得了
								MOTOR_LEFT_DIR(BACK);
								MOTOR_RIGH_DIR(BACK);
								MOTOR_LOAD_PWM(4500,4500);
								if(flag.time_back==1)
								{
									//需要停车
									Motor_Set_Disable();
									//下一步
									Index.carstep=9;
								}	
							
				break;
							
				case 9:////////参数调整  /********入库*********/
							Servo_X_Angle_Init(65);//右打死  -90~90
							MOTOR_LEFT_DIR(BACK);
							MOTOR_RIGH_DIR(FORWARD);
//							angle_Judge(4500,60);

//							MOTOR_LOAD_PWM(Index.left_Target,Index.Righ_Target);
							MOTOR_LOAD_PWM(5800,4700);//4000~7000//范围内
							flag.time_daoche=0;//入库时间开始//
							Index.carstep=10;
							
				break;
							
				case 10:
						if(flag.time_daoche==1)//时间到,调整参数时间
							{
								flag.houtui=0;
//								Motor_Set_Disable();
//								flag.time_turn=0;//开始计时
								Index.carstep=11;//
							}
				break;
				case 11:
							Servo_X_Angle_Init(-8);//
							MOTOR_LEFT_DIR(BACK);
							MOTOR_RIGH_DIR(BACK);
							MOTOR_LOAD_PWM(4500,4500);
							if(flag.houtui==1)//后退
							{
								flag.totime=0;
								Index.carstep=12;
							}
				break;
				case 12:
							if(flag.totime==1)
							{
								Servo_X_Angle_Init(0);
								Motor_Set_Disable();
								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//响
								flag.time5s=0;
								flag.totime=0;
								Index.carstep=13;
							}
					break;
				case 13:
								if(flag.totime==1)
								{
									HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//不响
								}
								if(flag.time5s==1)//
								{
									//前进
									flag.time_one=0;
									Index.carstep=14;
								}
				break;
				case 14:
							Servo_X_Angle_Init(-8);//
							MOTOR_LEFT_DIR(FORWARD);
							MOTOR_RIGH_DIR(FORWARD);
							MOTOR_LOAD_PWM(4600,4600);
							if(flag.time_one==1)//出库前进
							{
								flag.chuku=0;
								Index.carstep=15;
							}
					break;
				case 15:
							Servo_X_Angle_Init(80);//
							MOTOR_LEFT_DIR(FORWARD);
							MOTOR_RIGH_DIR(FORWARD);
							MOTOR_LOAD_PWM(4500,4500);
							if(flag.chuku==1)
							{
								Servo_X_Angle_Init(-10);
								Motor_Set_Disable();
								Index.carstep=16;
							}
				break;
//				case 11://延时
//							Servo_X_Angle_Init(-8);//
//							MOTOR_LEFT_DIR(BACK);
//							MOTOR_RIGH_DIR(BACK);
//							MOTOR_LOAD_PWM(4300,4300);
//							
//							if(flag.time_turn==1)
//							{
//								Servo_X_Angle_Init(-7);
//								Motor_Set_Disable();
//								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//响
//								flag.time5s=0;
//								flag.totime=0;
//								Index.carstep=12;
//							}
//				break;
//				case 12:
//								if(flag.totime==1)
//								{
//									HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//不响
//								}
//								
//								if(flag.time5s==1)//
//								{
////									HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//不响
//									//前进
//									flag.time_back=0;
//									Index.carstep=13;
//								}
//				break;//////////////无问题
//				
//								
//				case 13:
//							Servo_X_Angle_Init(0);
//							MOTOR_LEFT_DIR(FORWARD);
//							MOTOR_RIGH_DIR(FORWARD);
//							MOTOR_LOAD_PWM(4500,4500);
//							if(flag.time_back==1)
//							{
//								//下一步
//								//计时
////								flag.
//								HAL_UART_Transmit(&huart3,"A",1,0xffff);
//								Index.carstep=14;
//							}
//					
//				break;
//				case 14:
//							
//							Servo_X_Angle_Init(80);
//							MOTOR_LEFT_DIR(FORWARD);
//							MOTOR_RIGH_DIR(FORWARD);
//							MOTOR_LOAD_PWM(5500,4400);
//							if(Index.hedata==5)
//							{
//								Servo_X_Angle_Init(-10);
//								Motor_Set_Disable();
//								Index.carstep=15;
//							}
//				break;
							
				
			}
		}

		else 
		{Motor_Set_Disable();}
}
#define TVALUE 18
#define LVALUE 15
#define PWMDEADLINE 4000
#define PWMMANVALUE 7000
void angle_Judge(int16_t speed,int16_t jiaodu)
{
	Index.left_Target=speed*(1+TVALUE*tan(jiaodu)/2/LVALUE);
	Index.Righ_Target=speed*(1-TVALUE*tan(jiaodu)/2/LVALUE);
	if(Index.left_Target>PWMMANVALUE)//限幅 
	{
		Index.left_Target=PWMMANVALUE;
	}
	if(Index.Righ_Target<PWMDEADLINE&&Index.left_Target>0)
	{
		Index.Righ_Target=PWMDEADLINE; 
	}
	else if(Index.Righ_Target<0)
	{
		Index.Righ_Target=-PWMDEADLINE;
	}
	//serve_pwm=servo_Init+jiaodu*xishu;//暂时不调整 
	
} 
void ALL_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim5);//每10ms触发一次中断 
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	Servo_Angle_Init();
	Motor_TIM_Init();
	Encoder_TIM_Init();
	Motor_Set_Enable();
	Servo_X_Angle_Init(0);
	HAL_Delay(100);
	Index.pwm=PID_Realize(OutMpu.yaw,0); //目标值为0
						Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
	HAL_UART_Receive_IT(&huart2,UART_Receive_buffer, 1);
	HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//不响
	param_Init();
	PID_Param_Init();
	
	HAL_UART_Receive_IT(&huart3,UART_Receive_buffer, 1);
	HAL_UART_Transmit(&huart3,"C",1,0xffff);
}













/*****************************************************END OF FILE*********************************************************/	
