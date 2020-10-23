/*
 * led_toggle.c
 *
 *  Created on: Oct 12, 2020
 *      Author: amrith
 */
#include "stm32f407xx.h"
#include "stm32f407xx_gpio.h"


GPIO_handle_t led;
GPIO_handle_t btn;


void led_blink_it()
{

	led.pGPIOx=GPIOD;
	led.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_12;
	led.GPIO_PinConfig.GPIO_Mode=GPIO_MODE_OUT;
	led.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_NO_PUPD;
	led.GPIO_PinConfig.GPIO_PinSpeed=GPIO_OP_SP_MED;
	led.GPIO_PinConfig.GPIOx_PinOPType=GPIO_OP_TYPE_PP;
	GPIO_PeriphCLKControl(led.pGPIOx,ENABLE);
	GPIO_Init(&led);


	btn.pGPIOx=GPIOA;

	btn.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_0;
	btn.GPIO_PinConfig.GPIO_Mode=GPIO_IT_FE;
	btn.GPIO_PinConfig.GPIO_PinSpeed=GPIO_OP_SP_MED;
	btn.GPIO_PinConfig.GPIOx_PinOPType=GPIO_PIN_PU;
	GPIO_PeriphCLKControl(btn.pGPIOx, ENABLE);
	GPIO_Init(&btn);
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, 15);
    GPIO_IRQITConfig(IRQ_NO_EXTI0, ENABLE);


	while(1)
	{

	}

}
void EXTI0_IRQHandler()
{

	GPIO_TogglePin(led.pGPIOx, 12);
	for(uint32_t i=0;i<200000;i++ );
	GPIO_TogglePin(led.pGPIOx, 12);
	for(uint32_t i=0;i<200000;i++ );
	GPIO_TogglePin(led.pGPIOx, 12);
	for(uint32_t i=0;i<200000;i++ );
	GPIO_TogglePin(led.pGPIOx, 12);
	for(uint32_t i=0;i<200000;i++ );
	GPIO_IrqHandling(0);


}
