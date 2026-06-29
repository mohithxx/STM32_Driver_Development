/*
 * GPIO.c
 *
 * Created on: May 23, 2026
 * Author: Srujan
 */
#include "stm32f446zxx.h"
#include <stdint.h>
#include "GPIO.h"

void GPIO_ClockControl(GPIO_RegDef_t* pGPIOx, uint8_t EN_DI)
{
    if (EN_DI == ENABLE){
        if (pGPIOx == GPIOA)      { GPIOA_CLK_EN(); }
        else if (pGPIOx == GPIOB) { GPIOB_CLK_EN(); }
        else if (pGPIOx == GPIOC) { GPIOC_CLK_EN(); }
        else if (pGPIOx == GPIOD) { GPIOD_CLK_EN(); }
        else if (pGPIOx == GPIOE) { GPIOE_CLK_EN(); }
        else if (pGPIOx == GPIOF) { GPIOF_CLK_EN(); }
        else if (pGPIOx == GPIOG) { GPIOG_CLK_EN(); }
        else if (pGPIOx == GPIOH) { GPIOH_CLK_EN(); }
    } else {
        if (pGPIOx == GPIOA)      { GPIOA_CLK_DI(); }
        else if (pGPIOx == GPIOB) { GPIOB_CLK_DI(); }
        else if (pGPIOx == GPIOC) { GPIOC_CLK_DI(); }
        else if (pGPIOx == GPIOD) { GPIOD_CLK_DI(); }
        else if (pGPIOx == GPIOE) { GPIOE_CLK_DI(); }
        else if (pGPIOx == GPIOF) { GPIOF_CLK_DI(); }
        else if (pGPIOx == GPIOG) { GPIOG_CLK_DI(); }
        else if (pGPIOx == GPIOH) { GPIOH_CLK_DI(); }
    }
}

void GPIO_init(GPIO_Handle_t* GPIO_Handle)
{
    uint32_t temp = 0;

    // 1. Configure non-interrupt regular modes
    if (GPIO_Handle->pinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) {

        // Configure Pin Mode
        temp = (GPIO_Handle->pinConfig.GPIO_PinMode << (2 * GPIO_Handle->pinConfig.GPIO_PinNumber));
        GPIO_Handle->GPIOx->MODER &= ~(3U << (2 * GPIO_Handle->pinConfig.GPIO_PinNumber));
        GPIO_Handle->GPIOx->MODER |= temp;

        // Pin Speed
        temp = (GPIO_Handle->pinConfig.GPIO_PinSpeed << (2 * GPIO_Handle->pinConfig.GPIO_PinNumber));
        GPIO_Handle->GPIOx->OSPEEDR &= ~(3U << (2 * GPIO_Handle->pinConfig.GPIO_PinNumber));
        GPIO_Handle->GPIOx->OSPEEDR |= temp;

        // Pin Output Type
        temp = (GPIO_Handle->pinConfig.GPIO_PinOPType << GPIO_Handle->pinConfig.GPIO_PinNumber);
        GPIO_Handle->GPIOx->OTYPER &= ~(1U << GPIO_Handle->pinConfig.GPIO_PinNumber);
        GPIO_Handle->GPIOx->OTYPER |= temp;

        // Pull-Up / Pull-Down Control (Fixed shifting logic bug here)
        temp = (GPIO_Handle->pinConfig.GPIO_PinPuPd_control << (2 * GPIO_Handle->pinConfig.GPIO_PinNumber));
        GPIO_Handle->GPIOx->PUPDR &= ~(3U << (2 * GPIO_Handle->pinConfig.GPIO_PinNumber));
        GPIO_Handle->GPIOx->PUPDR |= temp;

        // Alternate Function Selection
        if (GPIO_Handle->pinConfig.GPIO_PinMode == GPIO_MODE_AF) {
            uint8_t temp1 = GPIO_Handle->pinConfig.GPIO_PinNumber / 8;
            uint8_t temp2 = GPIO_Handle->pinConfig.GPIO_PinNumber % 8;

            GPIO_Handle->GPIOx->AFR[temp1] &= ~((0xFU) << (temp2 * 4));
            GPIO_Handle->GPIOx->AFR[temp1] |= (GPIO_Handle->pinConfig.GPIO_AltFuncMode) << (temp2 * 4);
        }

    } else {
        // 2. Configure Interrupt Modes (EXTI)
        if (GPIO_Handle->pinConfig.GPIO_PinMode == GPIO_MODE_IT_RT) {
            EXTI->RTSR |= (1U << GPIO_Handle->pinConfig.GPIO_PinNumber);
            EXTI->FTSR &= ~(1U << GPIO_Handle->pinConfig.GPIO_PinNumber);
        } 
        else if (GPIO_Handle->pinConfig.GPIO_PinMode == GPIO_MODE_IT_FT) {
            EXTI->FTSR |= (1U << GPIO_Handle->pinConfig.GPIO_PinNumber);
            EXTI->RTSR &= ~(1U << GPIO_Handle->pinConfig.GPIO_PinNumber);
        } 
        else { // Rising and Falling Edge (Fixed structural bitmask inversion bugs here)
            EXTI->RTSR |= (1U << GPIO_Handle->pinConfig.GPIO_PinNumber);
            EXTI->FTSR |= (1U << GPIO_Handle->pinConfig.GPIO_PinNumber);
        }

        // 3. Route GPIO Port to EXTI lines using SYSCFG
        // Enable SYSCFG Clock (Bit 14 in APB2ENR)
        RCC->APB2ENR |= (1U << 14);

        uint8_t exti_reg_idx = GPIO_Handle->pinConfig.GPIO_PinNumber / 4;
        uint8_t exti_bit_pos = (GPIO_Handle->pinConfig.GPIO_PinNumber % 4) * 4;
        uint8_t port_code = GPIO_TO_PORT(GPIO_Handle->GPIOx);

        SYSCFG->EXTICR[exti_reg_idx] &= ~((0xFU) << exti_bit_pos);
        SYSCFG->EXTICR[exti_reg_idx] |= (port_code << exti_bit_pos);

        // 4. Enable EXTI Interrupt delivery using Interrupt Mask Register (IMR)
        EXTI->IMR |= (1U << GPIO_Handle->pinConfig.GPIO_PinNumber);
    }
}

void GPIO_deInit(GPIO_RegDef_t* pGPIOx)
{
    if      (pGPIOx == GPIOA) { GPIOA_REG_RST(); }
    else if (pGPIOx == GPIOB) { GPIOB_REG_RST(); }
    else if (pGPIOx == GPIOC) { GPIOC_REG_RST(); }
    else if (pGPIOx == GPIOD) { GPIOD_REG_RST(); }
    else if (pGPIOx == GPIOE) { GPIOE_REG_RST(); }
    else if (pGPIOx == GPIOF) { GPIOF_REG_RST(); }
    else if (pGPIOx == GPIOG) { GPIOG_REG_RST(); }
    else if (pGPIOx == GPIOH) { GPIOH_REG_RST(); }
}

void GPIO_WriteToPin(GPIO_RegDef_t* pGPIOx, uint8_t pinNumber, uint8_t value)
{
    if (value) {
        pGPIOx->ODR |= (1U << pinNumber);
    } else {
        pGPIOx->ODR &= ~(1U << pinNumber);
    }
}

// Fixed: Expanded value size parameter to uint16_t to address full port
void GPIO_WriteToPort(GPIO_RegDef_t* pGPIOx, uint16_t value)
{
    pGPIOx->ODR = value;
}

uint8_t GPIO_ReadPin(GPIO_RegDef_t* pGPIOx, uint8_t pinNumber)
{
    return (uint8_t)((pGPIOx->IDR >> pinNumber) & 0x00000001U);
}

uint16_t GPIO_ReadPort(GPIO_RegDef_t* pGPIOx)
{
    return (uint16_t)pGPIOx->IDR;
}

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EN_DI) {
    if (EN_DI == ENABLE) {
        if (IRQNumber <= 31) {
            // Program ISER0 register
            *NVIC_ISER0 = (1 << IRQNumber);
        } else if (IRQNumber > 31 && IRQNumber < 64) {
            // Program ISER1 register
            *NVIC_ISER1 = (1 << (IRQNumber % 32));
        } else if (IRQNumber >= 64 && IRQNumber < 96) {
            // Program ISER2 register
            *NVIC_ISER3 = (1 << (IRQNumber % 64));
        }   
    } else {
        if (IRQNumber <= 31) {
            // Program ICER0 register
            *NVIC_ICER0 = (1 << IRQNumber);
        } else if (IRQNumber > 31 && IRQNumber < 64) {
            // Program ICER1 register
            *NVIC_ICER1 = (1 << (IRQNumber % 32));
        } else if (IRQNumber >= 64 && IRQNumber < 96) {
            // Program ICER2 register
            *NVIC_ICER3 = (1 << (IRQNumber % 64));
        }
    }
}


void GPIO_IRQ_PrioConfig(uint8_t IRQNumber ,uint8_t IRQPriority){
    
}