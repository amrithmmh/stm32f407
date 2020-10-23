/*
 * stm32f407xx_gpio.c
 *
 *  Created on: Oct 12, 2020
 *      Author: amrith
 */


#include "stm32f407xx.h"
#include "stm32f407xx_gpio.h"



/************GPIO APIs****************/


/*********************************************************************
 * @fn      		  - GPIO_PeriClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none
 */
void GPIO_PeriphCLKControl(GPIO_RegDef_t *pGPIOx,uint8_t EnDi ) //just enabling/disabling clock of gpio peripheral
{
	if(EnDi==ENABLE)
	{

		if(pGPIOx==GPIOA)
		{
			GPIOA_CLK_EN();
		}
		else if(pGPIOx==GPIOB)
		{
			GPIOB_CLK_EN();
		}
		else if(pGPIOx==GPIOC)
		{
			GPIOC_CLK_EN();
		}
		else if(pGPIOx==GPIOD)
		{
			GPIOD_CLK_EN();
		}
		else if(pGPIOx==GPIOE)
		{
			GPIOE_CLK_EN();

		}
		else if(pGPIOx==GPIOF)
		{
			GPIOF_CLK_EN();

		}
		else if(pGPIOx==GPIOG)
		{
			GPIOG_CLK_EN();

		}
		else if(pGPIOx==GPIOH)
		{
			GPIOH_CLK_EN();

		}
		else if(pGPIOx==GPIOI)
		{
			GPIOI_CLK_EN();

		}


	}
	else if(EnDi==DISABLE)
	{

		if(pGPIOx==GPIOA)
		{
			GPIOA_CLK_DI();
		}
		else if(pGPIOx==GPIOB)
		{
			GPIOB_CLK_DI();
		}
		else if(pGPIOx==GPIOC)
		{
			GPIOC_CLK_DI();
		}
		else if(pGPIOx==GPIOD)
		{
			GPIOD_CLK_DI();
		}
		else if(pGPIOx==GPIOE)
		{
			GPIOE_CLK_DI();

		}
		else if(pGPIOx==GPIOF)
		{
			GPIOF_CLK_DI();

		}
		else if(pGPIOx==GPIOG)
		{
			GPIOG_CLK_DI();

		}
		else if(pGPIOx==GPIOH)
		{
			GPIOH_CLK_DI();

		}
		else if(pGPIOx==GPIOI)
		{
			GPIOI_CLK_DI();

		}
	}
}



//initialize GPIO


/*********************************************************************
 * @fn      		  - GPIO_Init
 *
 * @brief             - This function initialises the GPIO to a mode and speed
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE macros
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none
 */

void GPIO_Init(GPIO_handle_t *pGPIO_Handle)
{
	uint32_t temp=0;
	//1 . set mode (4 modes)
	if(pGPIO_Handle->GPIO_PinConfig.GPIO_Mode<=2)
	{
		temp=pGPIO_Handle->GPIO_PinConfig.GPIO_Mode<<(pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber*2);
		pGPIO_Handle->pGPIOx->MODER&=~(3<<pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber*2);
		pGPIO_Handle->pGPIOx->MODER|=temp;

	}
	else{

		//3 is analog mode
		//interrupts has to be programmed
		if(pGPIO_Handle->GPIO_PinConfig.GPIO_Mode>3)
		{
			//interrupts
			if(pGPIO_Handle->GPIO_PinConfig.GPIO_Mode==4){

					//falling edge
				EXTI->EXTI_FTSR|=(1<<pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
				EXTI->EXTI_RTSR &=~(1<<pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);

			}
			if(pGPIO_Handle->GPIO_PinConfig.GPIO_Mode==5)
			{
					//rising edge
				EXTI->EXTI_RTSR|=(1<<pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
				EXTI->EXTI_FTSR&=~(1<<pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);

			}
			if(pGPIO_Handle->GPIO_PinConfig.GPIO_Mode==6)
			{
				//falling and rising edge
				EXTI->EXTI_FTSR|=(1<<pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
				EXTI->EXTI_RTSR|=(1<<pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);

			}



			//syscfg exticr registers
			uint8_t temp1=pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber%4; //0-15
			uint8_t temp2=pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber/4; //0-15 numbers
			uint8_t value=GPIO_PIN_TO_CODE(pGPIO_Handle->pGPIOx);
			SYSCFG->SYSCFG_EXTICR[temp2]|=(value<<temp1);
			SYSCFG_CLK_EN();

            //exti IMR set
			EXTI->EXTI_IMR|=(1<<pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);


		}

	}

	//2. output type
	temp=0;
	temp=(pGPIO_Handle->GPIO_PinConfig.GPIOx_PinOPType<<(pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIO_Handle->pGPIOx->OTYPER&=~(1<<pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIO_Handle->pGPIOx->OTYPER|=temp;

	//3. output speed
	temp=0;
	temp=(pGPIO_Handle->GPIO_PinConfig.GPIO_PinSpeed<<(pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber*2));
	pGPIO_Handle->pGPIOx->OSPEEDR&=~(3<<(pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber*2));
	pGPIO_Handle->pGPIOx->OSPEEDR|=temp;

	//4. pullup pulldown
	temp=0;
	temp=(pGPIO_Handle->GPIO_PinConfig.GPIO_PinPuPdControl<<(pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber*2));
	pGPIO_Handle->pGPIOx->PUPDR&=~(3<<(pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber*2));
	pGPIO_Handle->pGPIOx->PUPDR|=temp;

	//5. alternate function settings

	if(pGPIO_Handle->GPIO_PinConfig.GPIO_PinAltFunMode)
	{

	uint32_t temp1=0;
	uint32_t temp2=0;
	temp1=pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber/8;
	temp2=pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber%8;
	pGPIO_Handle->pGPIOx->AFR[temp1]&=~(16<<(pGPIO_Handle->GPIO_PinConfig.GPIO_PinAltFunMode<<(4*temp2)));
	pGPIO_Handle->pGPIOx->AFR[temp1]|=pGPIO_Handle->GPIO_PinConfig.GPIO_PinAltFunMode<<(4*temp2);

	}


	GPIO_PeriphCLKControl(pGPIO_Handle->pGPIOx, ENABLE);
}

/*********************************************************************
 * @fn      		  - GPIO_DeInit
 *
 * @brief             - This function resets gpio port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  none
 *
 * @Note              -  none
 */

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{

	if(pGPIOx==GPIOA)
	{
		GPIOA_RST();
	}
	else if(pGPIOx==GPIOA)
	{
		GPIOB_RST();
	}
	else if(pGPIOx==GPIOC)
	{
		GPIOC_RST();
	}
	else if(pGPIOx==GPIOD)
	{
		GPIOD_RST();
	}
	else if(pGPIOx==GPIOE)
	{
		GPIOE_RST();

	}
	else if(pGPIOx==GPIOF)
	{
		GPIOF_RST();

	}
	else if(pGPIOx==GPIOG)
	{
		GPIOG_RST();

	}
	else if(pGPIOx==GPIOH)
	{
		GPIOH_RST();

	}
	else if(pGPIOx==GPIOI)
	{
		GPIOI_RST();

	}

}


//READ and WRITE to pin/port
/*********************************************************************
 * @fn      		  - GPIO_ReadPin
 *
 * @brief             - This function reads gpio port pin value
 *
 * @param[in]         - base address of the gpio peripheral and pin number
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  0 or 1
 *
 * @Note              -  none
 */

uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx,uint8_t pin)
{
	uint8_t value=0;
	value=(pGPIOx->IDR >>pin & 0x00000001);
	return value;

}

/*********************************************************************
 * @fn      		  - GPIO_ReadPort
 *
 * @brief             - This function reads gpio port
 *
 * @param[in]         - base address of the gpio peripheral and pin number
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  uint16_t
 *
 * @Note              -  none
 */
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOx){


	uint16_t value=0;
	value=pGPIOx->IDR ;
	return value;

}


/*********************************************************************
 * @fn      		  - GPIO_ReadPort
 *
 * @brief             - This function reads gpio port
 *
 * @param[in]         - base address of the gpio peripheral and pin number
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  uint16_t
 *
 * @Note              -  none
 */
void GPIO_WritePin(GPIO_RegDef_t *pGPIOx,uint8_t pin, uint8_t value){

if(value==SET)
{
	pGPIOx->ODR|=(1<<pin);
}
else
{
	pGPIOx->ODR&=~(1<<pin);
}

}
/*********************************************************************
 * @fn      		  - GPIO_ReadPort
 *
 * @brief             - This function reads gpio port
 *
 * @param[in]         - base address of the gpio peripheral and pin number
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  uint16_t
 *
 * @Note              -  none
 */
void GPIO_WritePort(GPIO_RegDef_t *pGPIOx,uint16_t value){

pGPIOx->ODR|=value;

}
/*********************************************************************
 * @fn      		  - GPIO_ReadPort
 *
 * @brief             - This function reads gpio port
 *
 * @param[in]         - base address of the gpio peripheral and pin number
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -  uint16_t
 *
 * @Note              -  none
 */
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx,uint8_t pin){
pGPIOx->ODR ^=(1<<pin);

}
//ISR init and handling

void GPIO_IRQPriorityConfig(uint8_t IRQ_number,uint8_t priority)
{
	uint8_t temp1=IRQ_number/4;
	uint8_t temp2=IRQ_number%4;
	priority=priority<<4;
	*(NVIC_IPR+(temp1))|= (priority<<( temp2 * 8 ) );
}

void GPIO_IRQITConfig(uint8_t IRQ_number,uint8_t ENorD)
{
	if(ENorD==1)
	{

		if(IRQ_number<32)
		{
			*NVIC_ISER0|=(1<<IRQ_number);
		}
		else if(IRQ_number>=32 && IRQ_number<64)
		{
			*NVIC_ISER1|=(1<<IRQ_number%32);
		}
		else if(IRQ_number>=64 && IRQ_number<96)
		{
			*NVIC_ISER2|=(1<<IRQ_number%64);
		}
	}
	else
	{
		if(IRQ_number<32)
		{
			*NVIC_ICER0|=(1<<IRQ_number);
		}
		else if(IRQ_number>=32 && IRQ_number<64)
		{
			*NVIC_ICER1|=(1<<IRQ_number%32);
		}
		else if(IRQ_number>=64 && IRQ_number<96)
		{
			*NVIC_ICER2|=(1<<IRQ_number%64);
		}

	}
}


void GPIO_IrqHandling(uint8_t pinnumber)
{
	if(EXTI->EXTI_PR&(1<<pinnumber))
	{
		EXTI->EXTI_PR|=(1<<pinnumber);
	}
}
