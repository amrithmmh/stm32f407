/*
 * stm32f407xx_SPI.h
 *
 *  Created on: Oct 16, 2020
 *      Author: amrith
 */

#ifndef INC_STM32F407XX_SPI_H_
#define INC_STM32F407XX_SPI_H_

#include "stm32f407xx.h"

#define SPI_MODE_MASTER 1
#define SPI_MODE_SLAVE 0

#define SPI_FULL_DUPLEX  		1
#define SPI_HALF_DUPLEX   		2
#define SPI_SIMPLEX_RX_ONLY		3

#define SPI_BAUD_DIV2  		1
#define SPI_BAUD_DIV4  		2
#define SPI_BAUD_DIV8  		3
#define SPI_BAUD_DIV16 		4
#define SPI_BAUD_DIV32  	5
#define SPI_BAUD_DIV64  	6
#define SPI_BAUD_DIV128  	7
#define SPI_BAUD_DIV256 	8


#define SPI_DFF_8bit	0
#define SPI_DFF_16bit	1

#define SPI_CPOL_HIGH 	1
#define SPI_CPOL_LOW 	0

#define SPI_CPHA_HIGH 	1
#define SPI_CPHA_LOW 	0


#define SPI_SSM_EN 	1
#define SPI_SSM_DI 	0

#define SPI_SR_RXNE		0
#define SPI_SR_TXE		1
#define SPI_SR_CHSIDE	2
#define SPI_SR_UDR		3
#define SPI_SR_CRCERR	4
#define SPI_SR_MODF		5
#define SPI_SR_OVR		6
#define SPI_SR_BSY		7
#define SPI_SR_FRE		8


typedef struct
{
	  uint8_t SPI_DeviceMode;//master slave
	  uint8_t SPI_BusConfig; //duplex,siplex,half duplex
	  uint8_t SPI_SCLKSpeed;
	  uint8_t SPI_DFF;
	  uint8_t SPI_CPOL;
	  uint8_t SPI_CPHA;
	  uint8_t SPI_SSM;

}SPI_Config_t;

typedef struct
{

	SPI_Config_t SPI_Config;
	SPI_RegDef_t *pSPIx;


}SPI_Handle_t;


void SPI_PeriphCLKControl(SPI_RegDef_t *pSPIx,uint8_t EnDi );

void SPI_enable(SPI_RegDef_t *pSPI_Handle,uint8_t ENorD);
void SPI_SSIConf(SPI_RegDef_t *pSPI_Handle,uint8_t ENorD);

void SPI_Init(SPI_Handle_t *pSPI_Handle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

//void SPI_RecieveData(SPI_Handle_t *pSPI_Handle);
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t * data,uint32_t length);
//void SPI_IRQITConfig();
//void SPI_IRQPriorityConfig():
//void SPI_IrqHandling();


#endif /* INC_STM32F407XX_SPI_H_ */
