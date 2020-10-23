/*
 * led_toggle.c
 *
 *  Created on: Oct 12, 2020
 *      Author: amrith
 */
#include "stm32f407xx.h"
#include "stm32f407xx_gpio.h"



void led_blink()
{
	GPIO_handle_t led;
	led.pGPIOx=GPIOD;
	led.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_12;
	led.GPIO_PinConfig.GPIO_Mode=GPIO_MODE_OUT;
	led.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_NO_PUPD;
	led.GPIO_PinConfig.GPIO_PinSpeed=GPIO_OP_SP_MED;
	led.GPIO_PinConfig.GPIOx_PinOPType=GPIO_OP_TYPE_PP;
	GPIO_PeriphCLKControl(led.pGPIOx,ENABLE);
	GPIO_Init(&led);

	GPIO_handle_t btn;
	btn.pGPIOx=GPIOA;
	btn.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_0;
	btn.GPIO_PinConfig.GPIO_Mode=GPIO_MODE_IN;
	btn.GPIO_PinConfig.GPIO_PinSpeed=GPIO_OP_SP_MED;
	btn.GPIO_PinConfig.GPIOx_PinOPType=GPIO_NO_PUPD;
	GPIO_PeriphCLKControl(btn.pGPIOx, ENABLE);
	GPIO_Init(&btn);


	while(1)
	{
		if(GPIO_ReadPin(btn.pGPIOx, 0))
		{
			for(uint32_t i=0;i<500000/2;i++);
			GPIO_WritePin(led.pGPIOx, 12, SET);
		}
		else
		{
			GPIO_WritePin(led.pGPIOx, 12, RESET);
		}
	}

}
