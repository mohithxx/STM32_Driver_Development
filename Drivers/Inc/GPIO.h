/*
 * GPIO.h
 *
 *  Created on: May 23, 2026
 *      Author: Srujan
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_
#include "stm32f446zxx.h"
#include <stdint.h>

/* GPIO Port Mode (MODER) */
#define GPIO_MODE_INPUT      0 /* Reset State */
#define GPIO_MODE_OUTPUT     1
#define GPIO_MODE_AF         2
#define GPIO_MODE_ANALOG     3
#define GPIO_MODE_IT_RT		 4
#define GPIO_MODE_IT_FT		 5
#define GPIO_MODE_IT_RFT     6

/* GPIO Output Type (OTYPER) */
#define GPIO_OTYPE_PP        0 /* Push-Pull (Reset State) */
#define GPIO_OTYPE_OD        1 /* Open-Drain */

/* GPIO Output Speed (OSPEEDR) */
#define GPIO_SPEED_LOW       0
#define GPIO_SPEED_MEDIUM    1
#define GPIO_SPEED_FAST      2
#define GPIO_SPEED_HIGH      3

/* GPIO Pull-Up/Pull-Down (PUPDR) */
#define GPIO_PULL_NONE       0 /* Floating (Reset State) */
#define GPIO_PULL_UP         1
#define GPIO_PULL_DOWN       2



/*PIN NUMBER OF GPIO*/
#define PIN_0 	0
#define PIN_1 	1
#define PIN_2 	2
#define PIN_3 	3
#define PIN_4 	4
#define PIN_5 	5
#define PIN_6 	6
#define PIN_7 	7
#define PIN_8 	8
#define PIN_9 	9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_14 14
#define PIN_15 15



typedef struct{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPd_control;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_AltFuncMode;

}GPIO_Config_t;



typedef struct{
	GPIO_RegDef_t* GPIOx;
	GPIO_Config_t pinConfig;
}GPIO_Handle_t;

void GPIO_ClockControl(GPIO_RegDef_t* pGPIOx, uint8_t EN_DI );
void GPIO_init(GPIO_Handle_t* GPIO_Handle);
void GPIO_deInit(GPIO_RegDef_t* pGPIOx);
void GPIO_WriteToPin(GPIO_RegDef_t* pGPIOx,uint8_t pinNumber,uint8_t value);
void GPIO_WriteToPort(GPIO_RegDef_t* pGPIOx, uint16_t value);
uint8_t GPIO_ReadPin(GPIO_RegDef_t* pGPIOx,uint8_t pinNumber);
uint16_t GPIO_ReadPort(GPIO_RegDef_t* pGPIOx);




#endif /* INC_GPIO_H_ */
