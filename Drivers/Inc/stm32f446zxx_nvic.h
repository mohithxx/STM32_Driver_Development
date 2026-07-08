#ifndef INC_STM32F446ZXX_NVIC_H_
#define INC_STM32F446ZXX_NVIC_H_

#include "stm32f446zxx.h"
#include <stdint.h>



void NVIC_IRQ_PrioConfig(uint8_t IRQNumber ,uint8_t IRQPriority);
void NVIC_IRQConfig(uint8_t IRQNumber, uint8_t EN_DI);





#endif /* INC_STM32F446ZXX_INTERRUPTS_H_ */