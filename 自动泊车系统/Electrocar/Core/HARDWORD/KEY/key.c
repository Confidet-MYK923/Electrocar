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
 #include "key.h"
/* define ---------------------------------------------------------------------------------------------------------------*/

#define KEY0 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4)
#define KEY1 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3)
#define KEY0_PRES   1	//KEY3����
#define KEY1_PRES   2	//KEY3����


uint8_t KEY_Scan(uint8_t mode)
{	 
	static uint8_t key_up=1;//�������ɿ���־
	if(mode)key_up = 1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0))
	{
		key_up=0;
		if(KEY1==0)return  KEY1_PRES;
		else if(KEY0==0)return  KEY0_PRES;
	}else if (KEY1==1&&KEY0==1)key_up=1; 	    
 	return 0;// �ް�������
}

void Key_Proc(void)
{
  uint8_t KeyRead;
	KeyRead= KEY_Scan(0);
	if(KeyRead)
	{
	 switch (KeyRead)
	 {
		 case KEY0_PRES:flag.carqidong^=1;break;
		 case KEY1_PRES:flag.carqidong2^=1;break;//ģ������
		 default:break;
	 }	
	}
}


