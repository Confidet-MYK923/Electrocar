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
 #include "key.h"
/* define ---------------------------------------------------------------------------------------------------------------*/

#define KEY0 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4)
#define KEY1 HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3)
#define KEY0_PRES   1	//KEY3按下
#define KEY1_PRES   2	//KEY3按下


uint8_t KEY_Scan(uint8_t mode)
{	 
	static uint8_t key_up=1;//按键按松开标志
	if(mode)key_up = 1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0))
	{
		key_up=0;
		if(KEY1==0)return  KEY1_PRES;
		else if(KEY0==0)return  KEY0_PRES;
	}else if (KEY1==1&&KEY0==1)key_up=1; 	    
 	return 0;// 无按键按下
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
		 case KEY1_PRES:flag.carqidong2^=1;break;//模拟数据
		 default:break;
	 }	
	}
}


