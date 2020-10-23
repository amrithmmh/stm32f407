/*
 * stm32f407xx_SPI.c
 *
 *  Created on: Oct 16, 2020
 *      Author: amrith
 */
#include "stm32f407xx_SPI.h"
#include "stm32f407xx.h"


void SPI_PeriphCLKControl(SPI_RegDef_t *pSPIx,uint8_t EnDi ) //just enabling/disabling clock of gpio peripheral
{
	if(EnDi==ENABLE)
	{

		if(pSPIx==SPI1)
		{
			SPI1_CLK_EN();
		}
		else if(pSPIx==SPI2)
		{
			SPI2_CLK_EN();
		}
		else if(pSPIx==SPI3)
		{
			SPI3_CLK_EN();
		}



	}
	else if(EnDi==DISABLE)
	{

		if(pSPIx==SPI1)
		{
			   SPI1_CLK_DI();
		}
		else if(pSPIx==SPI2)
		{
				SPI2_CLK_DI();
		}
		else if(pSPIx==SPI3)
		{
				SPI3_CLK_DI();
	    }

	}
}


void SPI_Init(SPI_Handle_t *pSPI_Handle)
{
	uint32_t temp=0;

	temp|=pSPI_Handle->SPI_Config.SPI_DeviceMode<<2; //master slave config

	if(pSPI_Handle->SPI_Config.SPI_BusConfig==SPI_FULL_DUPLEX) //bus config
	{
        temp&=~(1<<15);

	}
	else if(pSPI_Handle->SPI_Config.SPI_BusConfig==SPI_HALF_DUPLEX)
	{
		temp|=(pSPI_Handle->SPI_Config.SPI_BusConfig<<15);
	}
	else if(pSPI_Handle->SPI_Config.SPI_BusConfig==SPI_SIMPLEX_RX_ONLY)
	{
		 temp&=~(1<<15);
		temp|=(pSPI_Handle->SPI_Config.SPI_BusConfig<<10);
	}
//clk speed config
	temp|=pSPI_Handle->SPI_Config.SPI_SCLKSpeed<<3;

//DFF
	temp|=pSPI_Handle->SPI_Config.SPI_DFF<<11;

//CPOL & CPHA
	temp|=pSPI_Handle->SPI_Config.SPI_CPOL<<1;//cpol
	temp|=pSPI_Handle->SPI_Config.SPI_CPHA<<0;//cpha


	pSPI_Handle->pSPIx->SPI_CR1=temp;


	SPI_PeriphCLKControl(pSPI_Handle->pSPIx, ENABLE);
}


void SPI_DeInit(SPI_RegDef_t *pSPIx)
{


}


uint8_t CheckStatusRegister(SPI_RegDef_t *pSPIx,uint8_t regName)
{
	if(pSPIx->SPI_SR & (1<<regName))
		return (SET);
	else
		return(RESET);


}

void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t * ptxBuffer,uint32_t length)
{

	while(length>0)
	{
		while(CheckStatusRegister(pSPIx,(1<<SPI_SR_TXE))==SET);//buffer not empty wait

		if(pSPIx->SPI_CR1 & (1<<11))// 16 bit
		{

			pSPIx->SPI_DR= *((uint16_t *)ptxBuffer);
			ptxBuffer++;
			ptxBuffer++;
			length-=2;

		}
		else
		{ //8bit

			pSPIx->SPI_DR|= *ptxBuffer;
			ptxBuffer++;
			length--;

		}
	}


}

void SPI_enable(SPI_RegDef_t *pSPI_Handle,uint8_t ENorD)
{

	if(ENorD==ENABLE){ pSPI_Handle->SPI_CR1|=(1<<6);}
	else
	{ pSPI_Handle->SPI_CR1 &=~(1<<6);}
}

void SPI_SSIConf(SPI_RegDef_t *pSPI_Handle,uint8_t ENorD)
{
	if(ENorD==ENABLE){ pSPI_Handle->SPI_CR1|=(1<<8);}
	else
	{ pSPI_Handle->SPI_CR1&=~(1<<8);}
}

