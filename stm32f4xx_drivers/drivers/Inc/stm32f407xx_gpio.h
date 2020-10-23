/*
 * stm32f407xx_gpio.h
 *
 *  Created on: Oct 12, 2020
 *      Author: amrith
 */

#ifndef STM32F407XX_GPIO_H_
#define STM32F407XX_GPIO_H_



typedef struct
{
	uint32_t GPIO_PinNumber;
	uint32_t GPIO_Mode;						/*!< possible values from @GPIO_PIN_MODES >*/
	uint32_t GPIO_PinSpeed;					/*!< possible values from @GPIO_PIN_SPEED >*/
	uint32_t GPIO_PinPuPdControl;			/*!< possible values from @GPIO_PUPD >*/
	uint32_t GPIOx_PinOPType;				/*!< possible values from @GPIO_PIN_OTYPE >*/
	uint32_t GPIO_PinAltFunMode;			/*!< possible values from @GPIO_PIN_ALTFN >*/

}GPIO_PinConfig_t;

typedef struct
{
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_handle_t;


/*
 * @GPIO_PIN_MODES
 * gpio modes moder
 */

#define GPIO_MODE_IN 			0
#define GPIO_MODE_OUT 			1
#define GPIO_MODE_AF 			2
#define GPIO_MODE_ANALOG 		3

/*
 *INTERRUPT
 *interrupt input modes
 */
#define GPIO_IT_FE	 			4
#define GPIO_IT_RE 				5
#define GPIO_IT_RF 				6

/*
 * @GPIO_PIN_OTYPE
 * output type
 */
#define GPIO_OP_TYPE_PP 		0
#define GPIO_OP_TYPE_OD 		1

/*OUTPUT SPEED
 * @GPIO_PIN_SPEED
 */
#define GPIO_OP_SP_LOW			0
#define GPIO_OP_SP_MED			1
#define GPIO_OP_SP_HIGH			2
#define GPIO_OP_SP_VHIGH		3

/*INPUT TYPE PUPD
 * @GPIO_PUPD
 */
#define GPIO_NO_PUPD			0
#define GPIO_PIN_PU				1
#define GPIO_PIN_PD				2

#define GPIO_PIN_0 	0
#define GPIO_PIN_1 	1
#define GPIO_PIN_2 	2
#define GPIO_PIN_3 	3
#define GPIO_PIN_4 	4
#define GPIO_PIN_5 	5
#define GPIO_PIN_6 	6
#define GPIO_PIN_7 	7
#define GPIO_PIN_8 	8
#define GPIO_PIN_9 	9
#define GPIO_PIN_10 10
#define GPIO_PIN_11 11
#define GPIO_PIN_12 12
#define GPIO_PIN_13 13
#define GPIO_PIN_14 14
#define GPIO_PIN_15 15


/************GPIO APIs****************/

//initialize GPIO
void GPIO_Init(GPIO_handle_t *pGPIO_Handle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

void GPIO_PeriphCLKControl(GPIO_RegDef_t *pGPIOx,uint8_t EnDi ); //just enabling/disabling clock of gpio peripheral

//READ and WRITE to pin/port

uint8_t GPIO_ReadPin(GPIO_RegDef_t *pGPIOx,uint8_t pin);
uint16_t GPIO_ReadPort(GPIO_RegDef_t *pGPIOx);

void GPIO_WritePin(GPIO_RegDef_t *pGPIOx,uint8_t pin, uint8_t value);
void GPIO_WritePort(GPIO_RegDef_t *pGPIOx,uint16_t value);
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx,uint8_t pin);
//ISR init and handling

void GPIO_IRQITConfig(uint8_t IRQ_number,uint8_t ENorD);
void GPIO_IRQPriorityConfig(uint8_t IRQ_number,uint8_t IRQ_priority);
void GPIO_IrqHandling(uint8_t pinnumber);


#endif /* STM32F407XX_GPIO_H_ */
