/*
 * SPI_simple.c
 *
 *  Created on: Oct 17, 2020
 *      Author: amrith
 */


#include "SPI_simple.h"
#include "stm32f407xx.h"
#include "stm32f407xx_gpio.h"
#include "stm32f407xx_SPI.h"
#include "string.h"

//SPI2
//pb14 -- > MISO
//pb15 --> MOSI
//pb13 --> SCK
//pb12  --> NSS
//AF mode 5 from table alteranate functions

void SPI_pinConfig()
{
	GPIO_handle_t pSPI;
	pSPI.pGPIOx=GPIOB;

	pSPI.GPIO_PinConfig.GPIO_Mode=GPIO_MODE_AF;
	pSPI.GPIO_PinConfig.GPIO_PinAltFunMode=5;
	pSPI.GPIO_PinConfig.GPIOx_PinOPType=GPIO_OP_TYPE_PP;
	pSPI.GPIO_PinConfig.GPIO_PinSpeed=GPIO_OP_SP_HIGH;
	pSPI.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_NO_PUPD;

	//MISO
	//pSPI.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_14;
	//GPIO_Init(&pSPI);


	//MOSI
	pSPI.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_15;
	GPIO_Init(&pSPI);

	//NSS
	pSPI.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_12;
	GPIO_Init(&pSPI);

	//SCLK
	pSPI.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_13;
	GPIO_Init(&pSPI);

}


void SPI2_Init()
{
	SPI_Handle_t pSPI2;
	pSPI2.pSPIx=SPI2;
	pSPI2.SPI_Config.SPI_DeviceMode=SPI_MODE_MASTER;
	pSPI2.SPI_Config.SPI_BusConfig=SPI_FULL_DUPLEX;
	pSPI2.SPI_Config.SPI_SCLKSpeed=SPI_BAUD_DIV8;
	pSPI2.SPI_Config.SPI_DFF=SPI_DFF_8bit;
	pSPI2.SPI_Config.SPI_CPOL=SPI_CPOL_LOW;
	pSPI2.SPI_Config.SPI_CPHA=SPI_CPHA_LOW;
	pSPI2.SPI_Config.SPI_SSM=SPI_SSM_DI;
	SPI_Init(&pSPI2);


}

void SPI_test()
{

	char user_data[]="hello world";
	SPI_pinConfig();
	SPI2_Init();

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

	SPI_RegDef_t *pSPI2=SPI2;
	SPI_SSIConf(pSPI2, ENABLE);



	while(1)
	{
		if(GPIO_ReadPin(btn.pGPIOx, 0))
		{
			SPI_enable(pSPI2,ENABLE);
			SPI_SendData(SPI2, (uint8_t *)user_data, strlen(user_data));

			for(uint32_t i=0;i<1000000/2;i++);
			GPIO_WritePin(led.pGPIOx, 12, SET);
			for(uint32_t i=0;i<1000000/2;i++);
			GPIO_WritePin(led.pGPIOx, 12, RESET);

			SPI_enable(pSPI2,DISABLE);

		}
		else
		{
			GPIO_WritePin(led.pGPIOx, 12, RESET);
		}
	}




}
