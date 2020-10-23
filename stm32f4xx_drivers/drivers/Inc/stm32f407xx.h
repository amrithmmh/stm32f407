/*
 * stm32f407xx.h
 *
 *  Created on: Oct 10, 2020
 *      Author: amrith
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

/**********PROCESSOR SPECIFIC DETAILS*********/
//set enable
#define NVIC_ISER0 ((__vo uint32_t *)0xE000E100)
#define NVIC_ISER1 ((__vo uint32_t *)0xE000E104)
#define NVIC_ISER2 ((__vo uint32_t *)0xE000E108)
#define NVIC_ISER3 ((__vo uint32_t *)0xE000E10C)

//clear enable
#define NVIC_ICER0 ((__vo uint32_t *)0XE000E180)
#define NVIC_ICER1 ((__vo uint32_t *)0XE000E184)
#define NVIC_ICER2 ((__vo uint32_t *)0XE000E188)
#define NVIC_ICER3 ((__vo uint32_t *)0XE000E18C)

#define NVIC_IPR ((__vo uint32_t *)0xE000E400)

/***********MEMORY BASE ADDR*****************/

#define FLASH_BASEADDR		(0x08000000U)
#define SRAM1_BASEADDR		(0x20000000U)
#define SRAM2_BASEADDR		(0x2001C000U)
#define ROM_BASEADDR		(0x1FFF0000U)
#define SRAM				SRAM1_BASEADDR

/***********PERIPHERAL BUS MEMORY BASE ADDR*****************/

#define PERIPH_BASEADDR		(0x40000000U)
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		(0x40010000U)
#define AHB1PERIPH_BASEADDR		(0x40020000U)
#define AHB2PERIPH_BASEADDR		(0x50000000U)
#define AHB3PERIPH_BASEADDR		(0xA0000000U)

/***********PERIPHERALS MEMORY BASE ADDR*****************/

//GPIO
#define GPIOA_BASEADDR		(0x40020000U)
#define GPIOB_BASEADDR		(0x40020400U)
#define GPIOC_BASEADDR		(0x40020800U)
#define GPIOD_BASEADDR		(0x40020C00U)
#define GPIOE_BASEADDR		(0x40021000U)
#define GPIOF_BASEADDR		(0x40021400U)
#define GPIOG_BASEADDR		(0x40021800U)
#define GPIOH_BASEADDR		(0x40021C00U)
#define GPIOI_BASEADDR		(0x40022000U)


#define I2C1_BASEADDR		(0x40005400U)
#define I2C2_BASEADDR		(0x40005800U)
#define I2C3_BASEADDR		(0x40005C00U)

#define SPI1_BASEADDR		(0x40013000U)
#define SPI2_BASEADDR		(0x40003800U)
#define SPI3_BASEADDR		(0x40003C00U)
#define SPI4_BASEADDR		(0x40013400U)



#define USART1_BASEADDR		(0x40011000U)
#define USART2_BASEADDR		(0x40004400U)
#define USART3_BASEADDR		(0x40004800U)
#define UART4_BASEADDR		(0x40004C00U)
#define UART5_BASEADDR		(0x40005000U)
#define USART6_BASEADDR		(0x40011400U)

#define EXTI_BASEADDR		(0x40013C00U)


#define SYSCFG_BASEADDR		(0x40013800U)

#define __vo volatile

typedef struct
{
	__vo uint32_t EXTI_IMR;
	__vo uint32_t EXTI_EMR;
	__vo uint32_t EXTI_RTSR;
	__vo uint32_t EXTI_FTSR;
	__vo uint32_t EXTI_SWIER;
	__vo uint32_t EXTI_PR;

}EXTI_RegDef_t;

#define EXTI ((EXTI_RegDef_t *) EXTI_BASEADDR)

typedef struct
{
	__vo uint32_t SYSCFG_MEMRMP;
	__vo uint32_t SYSCFG_PMC;
	__vo uint32_t SYSCFG_EXTICR[4];
	//__vo uint32_t SYSCFG_CMPCR; offset is 0x20 add reserved

}SYSCFG_RegDef_t;

#define SYSCFG ((SYSCFG_RegDef_t *) SYSCFG_BASEADDR)
#define GPIO_PIN_TO_CODE(x)  ((x==GPIOA)? 0: \
							 (x==GPIOB)? 1: \
							 (x==GPIOC)? 2: \
						     (x==GPIOD)? 3: \
						     (x==GPIOE)? 4: \
						     (x==GPIOF)? 5: \
						     (x==GPIOG)? 6: \
						     (x==GPIOH)? 7: \
						     (x==GPIOI)? 8:0)

#define IRQ_NO_EXTI0 		6
#define IRQ_NO_EXTI1 		7
#define IRQ_NO_EXTI2 		8
#define IRQ_NO_EXTI3 		9
#define IRQ_NO_EXTI4 		10
#define IRQ_NO_EXTI9_5      23
#define IRQ_NO_EXTI15_10 	40



typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
}GPIO_RegDef_t;

#define GPIOA ((GPIO_RegDef_t *) GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t *) GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t *) GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t *) GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t *) GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t *) GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t *) GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t *) GPIOH_BASEADDR)
#define GPIOI ((GPIO_RegDef_t *) GPIOI_BASEADDR)


typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	     uint32_t RESERVED1;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	 	 uint32_t RESERVED2;
	 	 uint32_t RESERVED3;
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	    uint32_t RESERVED4;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	uint32_t RESERVED5;
	uint32_t RESERVED6;
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	uint32_t RESERVED7;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	 uint32_t RESERVED8;
	 uint32_t RESERVED9;
	 __vo uint32_t BDCR;
	 __vo uint32_t CSR;
	 uint32_t RESERVED10;
	 uint32_t RESERVED11;
	 __vo uint32_t SSCGR;
	 __vo uint32_t PLLI2SCFGR;

}RCC_RegDef_t;

#define RCC_BASEADDR 0x40023800U
#define RCC ((RCC_RegDef_t *) RCC_BASEADDR)

//GPIO clock enable macros
#define GPIOA_CLK_EN() (RCC->AHB1ENR|=(1<<0))
#define GPIOB_CLK_EN() (RCC->AHB1ENR|=(1<<1))
#define GPIOC_CLK_EN() (RCC->AHB1ENR|=(1<<2))
#define GPIOD_CLK_EN() (RCC->AHB1ENR|=(1<<3))
#define GPIOE_CLK_EN() (RCC->AHB1ENR|=(1<<4))
#define GPIOF_CLK_EN() (RCC->AHB1ENR|=(1<<5))
#define GPIOG_CLK_EN() (RCC->AHB1ENR|=(1<<6))
#define GPIOH_CLK_EN() (RCC->AHB1ENR|=(1<<7))
#define GPIOI_CLK_EN() (RCC->AHB1ENR|=(1<<8))

//I2C clock enable macros
#define I2C1_CLK_EN() (RCC->APB1ENR|=(1<<21))
#define I2C2_CLK_EN() (RCC->APB1ENR|=(1<<22))
#define I2C3_CLK_EN() (RCC->APB1ENR|=(1<<23))


typedef struct
{
	__vo uint32_t SPI_CR1;
	 __vo uint32_t SPI_CR2;
	 __vo uint32_t SPI_SR;
	 __vo uint32_t SPI_DR;
	 __vo uint32_t SPI_CRCPR;
	 __vo uint32_t SPI_RXCRCR;
	 __vo uint32_t SPI_TXCRCR;
	 __vo uint32_t SPI_I2SCFGR;
	 __vo uint32_t SPI_I2SPR;

}SPI_RegDef_t;

#define SPI1 ((SPI_RegDef_t *)SPI1_BASEADDR)
#define SPI2 ((SPI_RegDef_t *)SPI2_BASEADDR)
#define SPI3 ((SPI_RegDef_t *)SPI3_BASEADDR)
#define SPI4 ((SPI_RegDef_t *)SPI4_BASEADDR)

//SPI clock enable macros
#define SPI1_CLK_EN() (RCC->APB2ENR|=(1<<12))
#define SPI2_CLK_EN() (RCC->APB1ENR|=(1<<14))
#define SPI3_CLK_EN() (RCC->APB1ENR|=(1<<15))

//syscfgr clock enable macro
#define SYSCFG_CLK_EN() (RCC->APB2ENR|=(1<<14))


//GPIO clock disable macros
#define GPIOA_CLK_DI() (RCC->AHB1ENR&=~(1<<0))
#define GPIOB_CLK_DI() (RCC->AHB1ENR&=~(1<<1))
#define GPIOC_CLK_DI() (RCC->AHB1ENR&=~(1<<2))
#define GPIOD_CLK_DI() (RCC->AHB1ENR&=~(1<<3))
#define GPIOE_CLK_DI() (RCC->AHB1ENR&=~(1<<4))
#define GPIOF_CLK_DI() (RCC->AHB1ENR&=~(1<<5))
#define GPIOG_CLK_DI() (RCC->AHB1ENR&=~(1<<6))
#define GPIOH_CLK_DI() (RCC->AHB1ENR&=~(1<<7))
#define GPIOI_CLK_DI() (RCC->AHB1ENR&=~(1<<8))

//I2C clock DISABLE macros
#define I2C1_CLK_DI() (RCC->APB1ENR&=~(1<<21))
#define I2C2_CLK_DI() (RCC->APB1ENR&=~(1<<22))
#define I2C3_CLK_DI() (RCC->APB1ENR&=~(1<<23))


//SPI clock DISABLE macros
#define SPI1_CLK_DI() (RCC->APB2ENR&=~(1<<12))
#define SPI2_CLK_DI() (RCC->APB1ENR&=~(1<<14))
#define SPI3_CLK_DI() (RCC->APB1ENR&=~(1<<15))

//syscfgr clock DISABLE macro
#define SYSCFG_CLK_DI() (RCC->APB2ENR&=~(1<<14))

//general macros
#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
//reset gpio macros
#define GPIOA_RST() do{(RCC->AHB1RSTR|=(1<<0)); (RCC->AHB1RSTR&=~(1<<0));}while(0)
#define GPIOB_RST() do{(RCC->AHB1RSTR|=(1<<1)); (RCC->AHB1RSTR&=~(1<<1));}while(0)
#define GPIOC_RST() do{(RCC->AHB1RSTR|=(1<<2)); (RCC->AHB1RSTR&=~(1<<2));}while(0)
#define GPIOD_RST() do{(RCC->AHB1RSTR|=(1<<3)); (RCC->AHB1RSTR&=~(1<<3));}while(0)
#define GPIOE_RST() do{(RCC->AHB1RSTR|=(1<<4)); (RCC->AHB1RSTR&=~(1<<4));}while(0)
#define GPIOF_RST() do{(RCC->AHB1RSTR|=(1<<5)); (RCC->AHB1RSTR&=~(1<<5));}while(0)
#define GPIOG_RST() do{(RCC->AHB1RSTR|=(1<<6)); (RCC->AHB1RSTR&=~(1<<6));}while(0)
#define GPIOH_RST() do{(RCC->AHB1RSTR|=(1<<7)); (RCC->AHB1RSTR&=~(1<<7));}while(0)
#define GPIOI_RST() do{(RCC->AHB1RSTR|=(1<<8)); (RCC->AHB1RSTR&=~(1<<8));}while(0)

#endif /* INC_STM32F407XX_H_ */
