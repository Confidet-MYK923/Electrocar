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
		HAL_UART_Receive_IT(&huart3,UART_Receive_buffer, 1);//3�յ�����
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

//#define TIMEMUBIAO 60//Ŀ��ʱ��(������Ҫ����ʱ��)
//#define DUOCHE 170//����ʱ��
//#define TURN 20//ת��ʱ��
//#define WUMIAO 500//5sͣ��
//#define BACKTIME 95//����ʱ��
//#define TIMEONE 100//1sͣ��ʱ��
#define TIMEMUBIAO 55//Ŀ��ʱ��(������Ҫ����ʱ��)
#define DUOCHE 130//����ʱ��
#define TURN 20//ת��ʱ��
#define WUMIAO 500//5sͣ��
#define BACKTIME 100//����ʱ��
#define TIMEONE 100//1sͣ��ʱ��

#define HOUTUI 1
#define CHUKU 400

////////////////
#define INIT 1
////////////////////�෽
#define BACK2TIME 280//�෽�ҵ���
#define LEFTDASI 250//�������ʱ
#define QIANJIN 50//ǰ��ʱ��
#define QIANJINZUO 50//����ǰ��ʱ��
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance ==TIM5)//10ms
	{
		mpu_dmp_get_data(&OutMpu.pitch, &OutMpu.roll, &OutMpu.yaw);
		OutMpu.yaw=OutMpu.yaw+0.9;
//		Index.Lcnt = -Read_Speed(2);//�������ٶ�
//		Index.Rcnt = Read_Speed(4);
		if(flag.totime==0)//,������ʱ���ͣ�ͣ��
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
		if(flag.time2_back==0)//�Ҵ���
		{
			Index.to2_back++;
			if(Index.to2_back==BACK2TIME)
			{
				flag.time2_back=1;
				Index.to2_back=0;
			}
		}
		if(flag.time_Leftdasi==0)//�����
		{
			Index.to_dasi++;
			if(Index.to_dasi==LEFTDASI)
			{
				flag.time_Leftdasi=1;
				Index.to_dasi=0;
			}
		}
	
		if(flag.time_qianjin==0)//�����
		{
			Index.to_qianjin++;
			if(Index.to_qianjin==QIANJIN)
			{
				flag.time_qianjin=1;
				Index.to_qianjin=0;
			}
		}
//		if(flag.time_qianjinzuo==0)//�����
//		{
//			Index.to_qianjinzuo++;
//			if(Index.to_qianjin==QIANJIN)
//			{
//				flag.time_qianjinzuo=1;
//				Index.to_qianjinzuo=0;
//			}
//		}
		
		if(flag.time_qianjinzuo==0)//�����
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
#define HEINIT 0//�����ƫ��ͨ�ŵ�ַ

void zhuhanshu2(void)
{
	if(flag.carqidong2==1)
	{
		switch(Index.car2step)
		{
			case 0://ֱ����ʻ
						Index.pwm=PID_Realize(OutMpu.yaw,0); //Ŀ��ֵΪ0
						Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
						MOTOR_LEFT_DIR(FORWARD);
						MOTOR_RIGH_DIR(FORWARD);
						MOTOR_LOAD_PWM(4500,4500);
						if(Index.hedata==(1+HEINIT))//��һ�μ��㣬�˴�������ͣ�������ߺ����¿�ʼ
						{
							//1.��ʱ�������ݼ�ʱ
							flag.totime=0;//��ʼ��ʱ
							//3.��һ��
							Index.car2step=1;
						}
			break;
			case 1://ʱ�䵽����������
						if(flag.totime==1)
						{
							//1��������
								HAL_UART_Transmit(&huart3,"A",1,0xffff);//3���
							//����������
								Index.pwm=PID_Realize(OutMpu.yaw,0); //Ŀ��ֵΪ0
								Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
								MOTOR_LEFT_DIR(FORWARD);
								MOTOR_RIGH_DIR(FORWARD);
								MOTOR_LOAD_PWM(4500,4500);
								//2.��һ��
								Index.car2step=2;
						}
			break;
						
			case 2://�պ�����//�ڶ���
						if(Index.hedata==(2+HEINIT))//�ڶ���
						{
							flag.totime=0;//��ʼ��ʱ����Ҫ������
							Index.car2step=3;
						}
			break;
			case 3://ʱ�䵽������Ϣ������ֱ��
						if(flag.totime==1)
						{
							//1��������
							HAL_UART_Transmit(&huart3,"A",1,0xffff);//2���
							//����������
							Index.pwm=PID_Realize(OutMpu.yaw,0); //Ŀ��ֵΪ0
							Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
							MOTOR_LEFT_DIR(FORWARD);
							MOTOR_RIGH_DIR(FORWARD);
							MOTOR_LOAD_PWM(4500,4500);
							//2.��һ��
							Index.car2step=4;
						}
			break;
			case 4://���պ���Ч���ݣ�������
						if(Index.hedata==(3+HEINIT))//������
						{
							flag.time_one=0;//��ʼ��ʱ//Ŀ��ͣ��   1s��ʱ
							//��Ҫͣ��
							Motor_Set_Disable();
							//��������
							HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//��
							Index.car2step=5;
						}
			break;
			case 5://�ȴ�ʱ�䵽��
						if(flag.time_one==1)
						{
							//1��������
							HAL_UART_Transmit(&huart3,"B",1,0xffff);//�ر�����ͷ
							//�������ر�
							HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//����
							
							//��ʼ����ʱ
							flag.time2_back=0;///�ҵ��⿪ʼ
							//2.��һ��
							Index.car2step=6;//��ʼ��⵹��
						}
			break;
						
						//��������
			case 6://���
						Servo_X_Angle_Init(70);//�Ҵ���  -90~90
						MOTOR_LEFT_DIR(BACK);
						MOTOR_RIGH_DIR(BACK);
						MOTOR_LOAD_PWM(4500,4500);
			
						if(flag.time2_back==1)//ʱ�䵽
						{
							//ͣ��һ��ʱ��
						
							flag.time_Leftdasi=0;//��ʼ��ʱ
							//2��һ��
							Index.car2step=7;
						}
			break;
			case 7:
						Servo_X_Angle_Init(-70);//����  -90~90
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
//							//�������ʱ����
//							flag.time_Leftdasi=0;//��ʼ��ʱ
//							//��һ��
//							Index.car2step=8;
//						}
			break;
			case 8://����֮��ǰ��
						Servo_X_Angle_Init(5);//���
						MOTOR_LEFT_DIR(FORWARD);
						MOTOR_RIGH_DIR(FORWARD);
						MOTOR_LOAD_PWM(4500,4500);
						if(flag.time_qianjin==1)
						{
							HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//��
							Motor_Set_Disable();
							flag.totime=0;
							Index.car2step=9;
						}
			break;
			case 9:
							if(flag.totime==1)
							{
								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//����
								//5s��ʱ��ʼ
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
							Servo_X_Angle_Init(5);//���
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
							Servo_X_Angle_Init(-40);//���
							MOTOR_LEFT_DIR(FORWARD);
							MOTOR_RIGH_DIR(FORWARD);
							MOTOR_LOAD_PWM(4400,5500);
//							HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//��
							if(flag.time_qianjinzuo==1)
							{
//								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//����
								flag.totime=0;
								Index.car2step=13;
							}
				
			break;
			case 13:
							if(flag.totime==1)
							{
								flag.time_qianjinzuo=0;//�Ҵ�������
								Index.car2step=14;
							}
			break;
							
			case 14: 
							Servo_X_Angle_Init(80);//�Ҵ�
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
void zhuhanshu(void)//�ƻ�������������
{
//��������֮��
	if(flag.carqidong==1)
		{
			switch(Index.carstep)
			{
				case 0://ֱ����ʻ
							Index.pwm=PID_Realize(OutMpu.yaw,INIT); //Ŀ��ֵΪ0
							Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
							MOTOR_LEFT_DIR(FORWARD);
							MOTOR_RIGH_DIR(FORWARD);
							MOTOR_LOAD_PWM(4500,4500);
							if(Index.hedata==1)//��һ�μ��㣬�˴�������ͣ�������ߺ����¿�ʼ
							{
								//1.��ʱ�������ݼ�ʱ
								flag.totime=0;//��ʼ��ʱ
								//3.��һ��
								Index.carstep=1;
							}
							
				break;
				case 1://ʱ�䵽����������
							if(flag.totime==1)
							{
								//1��������
								HAL_UART_Transmit(&huart3,"A",1,0xffff);//2���
								//����������
								Index.pwm=PID_Realize(OutMpu.yaw,INIT); //Ŀ��ֵΪ0
								Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
								MOTOR_LEFT_DIR(FORWARD);
								MOTOR_RIGH_DIR(FORWARD);
								MOTOR_LOAD_PWM(4500,4500);
								//2.��һ��
								Index.carstep=2;
							}
				break;
							
							
				case 2://�պ�����
							if(Index.hedata==2)//�ڶ���
							{
								flag.totime=0;//��ʼ��ʱ����Ҫ������
								Index.carstep=3;
							}
				break;
				case 3://ʱ�䵽
							if(flag.totime==1)
							{
								//1��������
								HAL_UART_Transmit(&huart3,"A",1,0xffff);//2���
								//����������
								Index.pwm=PID_Realize(OutMpu.yaw,INIT); //Ŀ��ֵΪ0
								Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
								MOTOR_LEFT_DIR(FORWARD);
								MOTOR_RIGH_DIR(FORWARD);
								MOTOR_LOAD_PWM(4500,4500);
								//2.��һ��
								Index.carstep=4;
							}					
				break;
				
				case 4://�����ݵ�����
							if(Index.hedata==3)//������
							{
								flag.totime=0;//��ʼ��ʱ����Ҫ������
								Index.carstep=5;
							}
				break;
				case 5://ʱ�䵽
							if(flag.totime==1)
							{
								//1��������
								HAL_UART_Transmit(&huart3,"A",1,0xffff);//2���
								//����������
								Index.pwm=PID_Realize(OutMpu.yaw,INIT); //Ŀ��ֵΪ0
								Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
								MOTOR_LEFT_DIR(FORWARD);
								MOTOR_RIGH_DIR(FORWARD);
								MOTOR_LOAD_PWM(4500,4500);
								//2.��һ��
								Index.carstep=6;
							}					
				break;
							
				case 6://�պ���Ч����
							if(Index.hedata==4)//���Ĵ�
							{
								flag.time_one=0;//��ʼ��ʱ//Ŀ��ͣ��
								//��Ҫͣ��
								Motor_Set_Disable();
								//��������
								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//��
								Index.carstep=7;
							}
				break;
				case 7://ͣ��ʱ�䵽
							if(flag.time_one==1)
							{
								//1��������
								HAL_UART_Transmit(&huart3,"B",1,0xffff);//
								//�������ر�
								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//����
								//��ʼ������ʱ
								flag.time_back=0;
								//2.��һ��
								Index.carstep=8;//��ʼ����
							}
				break;	///��û����
							
							
				case 8://����
								Servo_X_Angle_Init(-2);////�ǲ�����
								MOTOR_LEFT_DIR(BACK);
								MOTOR_RIGH_DIR(BACK);
								MOTOR_LOAD_PWM(4500,4500);
								if(flag.time_back==1)
								{
									//��Ҫͣ��
									Motor_Set_Disable();
									//��һ��
									Index.carstep=9;
								}	
							
				break;
							
				case 9:////////��������  /********���*********/
							Servo_X_Angle_Init(65);//�Ҵ���  -90~90
							MOTOR_LEFT_DIR(BACK);
							MOTOR_RIGH_DIR(FORWARD);
//							angle_Judge(4500,60);

//							MOTOR_LOAD_PWM(Index.left_Target,Index.Righ_Target);
							MOTOR_LOAD_PWM(5800,4700);//4000~7000//��Χ��
							flag.time_daoche=0;//���ʱ�俪ʼ//
							Index.carstep=10;
							
				break;
							
				case 10:
						if(flag.time_daoche==1)//ʱ�䵽,��������ʱ��
							{
								flag.houtui=0;
//								Motor_Set_Disable();
//								flag.time_turn=0;//��ʼ��ʱ
								Index.carstep=11;//
							}
				break;
				case 11:
							Servo_X_Angle_Init(-8);//
							MOTOR_LEFT_DIR(BACK);
							MOTOR_RIGH_DIR(BACK);
							MOTOR_LOAD_PWM(4500,4500);
							if(flag.houtui==1)//����
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
								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//��
								flag.time5s=0;
								flag.totime=0;
								Index.carstep=13;
							}
					break;
				case 13:
								if(flag.totime==1)
								{
									HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//����
								}
								if(flag.time5s==1)//
								{
									//ǰ��
									flag.time_one=0;
									Index.carstep=14;
								}
				break;
				case 14:
							Servo_X_Angle_Init(-8);//
							MOTOR_LEFT_DIR(FORWARD);
							MOTOR_RIGH_DIR(FORWARD);
							MOTOR_LOAD_PWM(4600,4600);
							if(flag.time_one==1)//����ǰ��
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
//				case 11://��ʱ
//							Servo_X_Angle_Init(-8);//
//							MOTOR_LEFT_DIR(BACK);
//							MOTOR_RIGH_DIR(BACK);
//							MOTOR_LOAD_PWM(4300,4300);
//							
//							if(flag.time_turn==1)
//							{
//								Servo_X_Angle_Init(-7);
//								Motor_Set_Disable();
//								HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_RESET);//��
//								flag.time5s=0;
//								flag.totime=0;
//								Index.carstep=12;
//							}
//				break;
//				case 12:
//								if(flag.totime==1)
//								{
//									HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//����
//								}
//								
//								if(flag.time5s==1)//
//								{
////									HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//����
//									//ǰ��
//									flag.time_back=0;
//									Index.carstep=13;
//								}
//				break;//////////////������
//				
//								
//				case 13:
//							Servo_X_Angle_Init(0);
//							MOTOR_LEFT_DIR(FORWARD);
//							MOTOR_RIGH_DIR(FORWARD);
//							MOTOR_LOAD_PWM(4500,4500);
//							if(flag.time_back==1)
//							{
//								//��һ��
//								//��ʱ
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
	if(Index.left_Target>PWMMANVALUE)//�޷� 
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
	//serve_pwm=servo_Init+jiaodu*xishu;//��ʱ������ 
	
} 
void ALL_Init(void)
{
	HAL_TIM_Base_Start_IT(&htim5);//ÿ10ms����һ���ж� 
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	Servo_Angle_Init();
	Motor_TIM_Init();
	Encoder_TIM_Init();
	Motor_Set_Enable();
	Servo_X_Angle_Init(0);
	HAL_Delay(100);
	Index.pwm=PID_Realize(OutMpu.yaw,0); //Ŀ��ֵΪ0
						Servo_X_Angle_Init((int)(OutMpu.yaw+Index.pwm));
	HAL_UART_Receive_IT(&huart2,UART_Receive_buffer, 1);
	HAL_GPIO_WritePin(GPIOE, BEEP_Pin, GPIO_PIN_SET);//����
	param_Init();
	PID_Param_Init();
	
	HAL_UART_Receive_IT(&huart3,UART_Receive_buffer, 1);
	HAL_UART_Transmit(&huart3,"C",1,0xffff);
}













/*****************************************************END OF FILE*********************************************************/	
