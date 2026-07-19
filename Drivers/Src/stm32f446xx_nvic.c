#include "stm32f446zxx_nvic.h"
#include "stm32f446zxx.h"

void NVIC_IRQConfig(uint8_t IRQNumber, uint8_t EN_DI){
    if (EN_DI == ENABLE){
        if (IRQNumber <= 31)
        {
            *NVIC_ISER0 |= (1 << IRQNumber);
        }else if(IRQNumber > 31 && IRQNumber <= 63)
        {
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }else if(IRQNumber > 63 && IRQNumber < 95)
        {
            *NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
    }else{
        if (IRQNumber <= 31)
        {
            *NVIC_ICER0 |= (1 << IRQNumber);
        }else if(IRQNumber > 31 && IRQNumber <= 63)
        {
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }else if(IRQNumber > 63 && IRQNumber < 95)
        {
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
    }   
}

void NVIC_IRQ_PrioConfig(uint8_t IRQNumber ,uint8_t IRQPriority){
    uint8_t iprx = IRQNumber/4;
    uint8_t iprx_sec = IRQNumber%4;

    *(NVIC_IPR0+(iprx)) |= (IRQPriority << ((iprx_sec * 8) + (8 - NO_PR_BITS_IMPLEMENTED)));


}

