#include "stm32f10x.h"
#include "Delay.h"
/**
  * @brief  电机驱动
  * @param  xus 延时时长，范围：0~233015
  * @retval 无
  */
	
#define STEPMOTOR_1_PUL            GPIO_Pin_2
#define STEPMOTOR_1_ENA            GPIO_Pin_0
#define STEPMOTOR_1_DIR            GPIO_Pin_4
#define STEPMOTOR_1_GPIOx          GPIOA
#define STEPMOTOR_1_RCC_GPIOx      RCC_APB2Periph_GPIOA

void moter_init(void)
{
	RCC_APB2PeriphClockCmd(STEPMOTOR_1_RCC_GPIOx, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = STEPMOTOR_1_DIR|STEPMOTOR_1_ENA|STEPMOTOR_1_PUL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(STEPMOTOR_1_GPIOx, &GPIO_InitStructure);
}
void moter_run(int32_t speed,uint32_t num)
{
		if(speed>0)
		{
			GPIO_ResetBits(STEPMOTOR_1_GPIOx, STEPMOTOR_1_DIR);
		}
		else
		{
			GPIO_SetBits(STEPMOTOR_1_GPIOx, STEPMOTOR_1_DIR);
		}
		int i;
		if(speed<0)speed=-speed;
		for(i=0;i<num;i++)
		{
		GPIO_ResetBits(STEPMOTOR_1_GPIOx, STEPMOTOR_1_PUL);
		Delay_us(speed);
		GPIO_SetBits(STEPMOTOR_1_GPIOx, STEPMOTOR_1_PUL);
		Delay_us(speed);
		}
}
void moter_on()
{
	GPIO_ResetBits(STEPMOTOR_1_GPIOx, STEPMOTOR_1_ENA);
}
void moter_off()
{
	GPIO_SetBits(STEPMOTOR_1_GPIOx, STEPMOTOR_1_ENA);
}


void clip_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void clip_state(int32_t state)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_8, (BitAction)state);
	Delay_s(1); 
}
