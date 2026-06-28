/*
 * GPIO.c
 *
 *  Created on: May 23, 2026
 *      Author: Srujan
 */
#include "stm32f446zxx.h"
#include "stdint.h"
#include "GPIO.h"


void GPIO_ClockControl(GPIO_RegDef_t* pGPIOx, uint8_t EN_DI )
{
	if (EN_DI == ENABLE){
		if (pGPIOx == GPIOA){
			GPIOA_ClK_EN();
		}else if (pGPIOx == GPIOB){
			GPIOB_ClK_EN();
		}else if (pGPIOx == GPIOC){
			GPIOC_ClK_EN();
		}else if (pGPIOx == GPIOD){
			GPIOD_ClK_EN();
		}else if (pGPIOx == GPIOE){
			GPIOE_ClK_EN();
		}else if (pGPIOx == GPIOF){
			GPIOF_ClK_EN();
		}else if (pGPIOx == GPIOG){
			GPIOG_ClK_EN();
		}else if (pGPIOx == GPIOH){
			GPIOH_ClK_EN();
		}
	}else{
		if (pGPIOx == GPIOA){
					GPIOA_ClK_DI();
				}else if (pGPIOx == GPIOB){
					GPIOB_ClK_DI();
				}else if (pGPIOx == GPIOC){
					GPIOC_ClK_DI();
				}else if (pGPIOx == GPIOD){
					GPIOD_ClK_DI();
				}else if (pGPIOx == GPIOE){
					GPIOE_ClK_DI();
				}else if (pGPIOx == GPIOF){
					GPIOF_ClK_DI();
				}else if (pGPIOx == GPIOG){
					GPIOG_ClK_DI();
				}else if (pGPIOx == GPIOH){
					GPIOH_ClK_DI();
				}
	}

}


void GPIO_init(GPIO_Handle_t* GPIO_Handle)
{
	uint32_t temp = 0;
	if (GPIO_Handle->pinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){

		// configure PIN Mode
		temp =  (GPIO_Handle->pinConfig.GPIO_PinMode << 2* GPIO_Handle->pinConfig.GPIO_PinNumber);

		GPIO_Handle->GPIOx->MODER &= ~(3U << 2* GPIO_Handle->pinConfig.GPIO_PinNumber);
		GPIO_Handle->GPIOx->MODER |= temp;
		temp = 0;

		//Pin speed
		temp = (GPIO_Handle->pinConfig.GPIO_PinSpeed << 2* GPIO_Handle->pinConfig.GPIO_PinNumber);
		GPIO_Handle->GPIOx->OSPEEDR  &= ~(3U << (GPIO_Handle->pinConfig.GPIO_PinNumber*2));
		GPIO_Handle->GPIOx->OSPEEDR |= temp;

		temp = 0;

		//pin type
		temp = (GPIO_Handle->pinConfig.GPIO_PinOPType << GPIO_Handle->pinConfig.GPIO_PinNumber);
		GPIO_Handle->GPIOx->OTYPER &= ~(1U << GPIO_Handle->pinConfig.GPIO_PinNumber);
		GPIO_Handle->GPIOx->OTYPER |= temp;
		temp = 0;

		//pull up and pull down
		temp = (GPIO_Handle->pinConfig.GPIO_PinPuPd_control << 2*GPIO_Handle->pinConfig.GPIO_PinPuPd_control );
		GPIO_Handle->GPIOx->PUPDR &= ~(3U << (GPIO_Handle->pinConfig.GPIO_PinNumber*2));
		GPIO_Handle->GPIOx->PUPDR |= temp;
		temp = 0;

		//alternate function
		uint8_t temp1 = 0, temp2 = 0;
		if (GPIO_Handle->pinConfig.GPIO_PinMode == GPIO_MODE_AF){
			temp1 = GPIO_Handle->pinConfig.GPIO_PinNumber / 8;
			temp2 = GPIO_Handle->pinConfig.GPIO_PinNumber % 8;

			GPIO_Handle->GPIOx->AFR[temp1] &= ~((0xF)<<(temp2*4));
			GPIO_Handle->GPIOx->AFR[temp1] |= (GPIO_Handle->pinConfig.GPIO_AltFuncMode )<<(temp2*4);
		}


	}else{
			//Interrupt
			if(GPIO_Handle->pinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
				EXTI->RTSR |= (1 << GPIO_Handle->pinConfig.GPIO_PinNumber);
				EXTI->FTSR &= ~(1 << GPIO_Handle->pinConfig.GPIO_PinNumber);

			}else if (GPIO_Handle->pinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){
				EXTI->FTSR |= (1 << GPIO_Handle->pinConfig.GPIO_PinNumber);
				EXTI->RTSR &= ~(1 << GPIO_Handle->pinConfig.GPIO_PinNumber);
			}else{
				EXTI->FTSR |= ~(1 << GPIO_Handle->pinConfig.GPIO_PinNumber);
				EXTI->RTSR |= ~(1 << GPIO_Handle->pinConfig.GPIO_PinNumber);
			}
	}

}
void GPIO_deInit(GPIO_RegDef_t* pGPIOx){
	if (pGPIOx == GPIOA){
				GPIOA_ClK_EN();
			}else if (pGPIOx == GPIOB){
				GPIOB_ClK_EN();
			}else if (pGPIOx == GPIOC){
				GPIOC_ClK_EN();
			}else if (pGPIOx == GPIOD){
				GPIOD_ClK_EN();
			}else if (pGPIOx == GPIOE){
				GPIOE_ClK_EN();
			}else if (pGPIOx == GPIOF){
				GPIOF_ClK_EN();
			}else if (pGPIOx == GPIOG){
				GPIOG_ClK_EN();
			}else if (pGPIOx == GPIOH){
				GPIOH_ClK_EN();
			}


}
void GPIO_WriteToPin(GPIO_RegDef_t* pGPIOx,uint8_t pinNumber,uint8_t value){


	if (value){
		pGPIOx->ODR |= (value << pinNumber);
	}else{
		pGPIOx->ODR &= ~(1 << pinNumber);
	}


}
void GPIO_WriteToPort(GPIO_RegDef_t* pGPIOx, uint8_t value){
	pGPIOx->ODR &= ~(0xF);
	pGPIOx->ODR |= value;
}
uint8_t GPIO_ReadPin(GPIO_RegDef_t* pGPIOx,uint8_t pinNumber){
	uint8_t value = 0;

	value |= ((pGPIOx->IDR >> pinNumber) & (0x00000001));

	return value;
}
uint16_t GPIO_ReadPort(GPIO_RegDef_t* pGPIOx){
	uint16_t value = 0 ;

	value = pGPIOx->IDR;
	return value;
}
