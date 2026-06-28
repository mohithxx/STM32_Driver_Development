/*
 * stm32f446zxx.h
 *
 *  Created on: May 18, 2026
 *      Author: Srujan
 */

#ifndef INC_STM32F446ZXX_H_
#define INC_STM32F446ZXX_H_
#include <stdint.h>

/*Generic Defines*/
#define ENABLE 		1
#define DISABLE 	0
#define SET			ENABLE
#define RESET		DISABLE

/* Base addresses of the different BUS Domains */
#define PERIPHERAL_BASE_ADR	0x40000000UL
#define APB1_BASE_ADR		PERIPHERAL_BASE_ADR
#define AHB1_BASE_ADR		0x40020000UL
#define AHB2_BASE_ADR		0x50000000UL
#define APB2_BASE_ADR		0x40010000UL

#define FLASH_BASE_ADR	0x08000000UL
#define SRAM1_BASE_ADR  0x20000000UL // 112KB
#define SRAM2_BASE_ADR	0x2001C000UL // 16KB
#define _vol 			volatile


//**********************SPI_SPECIFIC_MACROS********************************************

#define MASTER 	0
#define SLAVE	1

#define FCLK_2 		0
#define FCLK_4 		1
#define FCLK_8 		2
#define FCLK_16		3
#define FCLK_32		4
#define FCLK_64 	5
#define FCLK_128 	6
#define FCLK_256	7

#define FULL_DUPLEX	0
#define HALF_DUPLEX	1
#define SIMPLEX		2

#define SSM_DI		0
#define SSM_EN		1

#define DFF_8B		0
#define DFF_16B		1



/* SPI SPECIFIC BIT POSITIONS*/
#define SPI_CR1_CPHA 		0
#define SPI_CR1_CPOL 		1
#define SPI_CR1_MSTR 		2
#define SPI_CR1_BR   		3
#define SPI_CR1_SPE	 		6
#define SPI_CR1_LSBFIRST 	7
#define SPI_CR1_SSI 		8
#define SPI_CR1_SSM 		9
#define SPI_CR1_RXONLY 		10
#define SPI_CR1_DFF 		11
#define SPI_CR1_CRCNEXT		12
#define SPI_CR1_CRCEN 		13
#define SPI_CR1_BIDIOE 		14
#define SPI_CR1_BIDIMODE	15


// SPI_CR2
#define SPI_CR2_RXDMAEN		0
#define SPI_CR2_TXDMAEN		1
#define SPI_CR2_SSOE		2
#define SPI_CR2_FRF			4
#define SPI_CR2_ERRIE		5
#define SPI_CR2_RXNEIE		6
#define SPI_CR2_TXEIE		7


//SPI_SR
#define SPI_SR_RXNE			0
#define SPI_SR_TXE			1
#define SPI_SR_CHSIDE		2
#define SPI_SR_UDR			3
#define SPI_SR_CRCERR		4
#define SPI_SR_MODF			5
#define SPI_SR_OVR			6
#define SPI_SR_BSY			7
#define SPI_SR_FRE			8

//********************************************************************************************************



/********************************************************RCC MACROS***************************************/
/* System Clock Selection (RCC_CFGR_SW) */
#define RCC_SYSCLK_HSI       (0x00UL)
#define RCC_SYSCLK_HSE       (0x01UL)
#define RCC_SYSCLK_PLL_P     (0x10UL)
#define RCC_SYSCLK_PLL_R     (0x11UL)

/* APB Low-Speed Prescaler (PPRE1 - Max 45 MHz) */
#define RCC_APB1_DIV1        (0x00UL) /* 0xx: AHB clock not divided */
#define RCC_APB1_DIV2        (0x04UL) /* 100: AHB/2 */
#define RCC_APB1_DIV4        (0x05UL) /* 101: AHB/4 */
#define RCC_APB1_DIV8        (0x06UL) /* 110: AHB/8 */
#define RCC_APB1_DIV16       (0x07UL) /* 111: AHB/16 */

/* APB High-Speed Prescaler (PPRE2 - Max 90 MHz) */
#define RCC_APB2_DIV1        (0x00UL)
#define RCC_APB2_DIV2        (0x04UL)
#define RCC_APB2_DIV4        (0x05UL)\







/*GPIO*/
typedef struct{
	_vol uint32_t MODER;
	_vol uint32_t OTYPER;
	_vol uint32_t OSPEEDR;
	_vol uint32_t PUPDR;
	_vol uint32_t IDR;
	_vol uint32_t ODR;
	_vol uint32_t BSRR;
	_vol uint32_t LCKR;
	_vol uint32_t AFR[2];

}GPIO_RegDef_t;

//GPIO BASE ADDRESS
#define GPIOA (GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x0000U)
#define GPIOB (GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x0400U)
#define GPIOC (GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x0800U)
#define GPIOD (GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x0C00U)
#define GPIOE (GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x1000U)
#define GPIOF (GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x1400U)
#define GPIOG (GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x1800U)
#define GPIOH (GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x1C00U)


//RCC BASE ADDRESS
#define RCC_BASE_ADR (AHB1_BASE_ADR+0x3800U)


//RCC REGISTERS
typedef struct{
	_vol	uint32_t CR;
	_vol	uint32_t PLLCFGR;
	_vol	uint32_t CFGR;
	_vol	uint32_t CIR;
	_vol	uint32_t AHB1RSTR;
	_vol	uint32_t AHB2RSTR;
	_vol	uint32_t AHB3RSTR;
	_vol	uint32_t RESERVED0;
	_vol	uint32_t APB1RSTR;
	_vol	uint32_t APB2RSTR;
	_vol	uint32_t RESERVED1[2];
	_vol	uint32_t AHB1ENR;
	_vol	uint32_t AHB2ENR;
	_vol	uint32_t AHB3ENR;
	_vol	uint32_t RESERVED2;
	_vol	uint32_t APB1ENR;
	_vol	uint32_t APB2ENR;
	_vol	uint32_t RESERVED3[2];
	_vol	uint32_t AHB1LPENR;
	_vol	uint32_t AHB2LPENR;
	_vol	uint32_t AHB3LPENR;
	_vol	uint32_t RESERVED4;
	_vol	uint32_t APB1LPENR;
	_vol	uint32_t APB2LPENR;
	_vol	uint32_t RESERVED5[2];
	_vol	uint32_t BDCR;
	_vol	uint32_t CSR;
	_vol	uint32_t RESERVED6[2];
	_vol	uint32_t SSCGR;
	_vol	uint32_t PLLI2SCFGR;
	_vol	uint32_t PLLSAICFGR;
	_vol	uint32_t DCKCFGR;
	_vol	uint32_t CKGATENR;
	_vol	uint32_t DCKCFGR2;
}RCC_RegDef_t;

//RCC POINTER TO RCC BASE ADRESS ALLOWS US TO ACCESS ALL THE REGISTERS OF THE RCC
#define RCC ((RCC_RegDef_t*)RCC_BASE_ADR)



//Enable clocks
#define GPIOA_ClK_EN() (RCC->AHB1ENR |= (1U<<0))
#define GPIOB_ClK_EN() (RCC->AHB1ENR |= (1U<<1))
#define GPIOC_ClK_EN() (RCC->AHB1ENR |= (1U<<2))
#define GPIOD_ClK_EN() (RCC->AHB1ENR |= (1U<<3))
#define GPIOE_ClK_EN() (RCC->AHB1ENR |= (1U<<4))
#define GPIOF_ClK_EN() (RCC->AHB1ENR |= (1U<<5))
#define GPIOG_ClK_EN() (RCC->AHB1ENR |= (1U<<6))
#define GPIOH_ClK_EN() (RCC->AHB1ENR |= (1U<<7))

#define GPIOA_ClK_DI() (RCC->AHB1ENR &= ~(1U<<7))
#define GPIOB_ClK_DI() (RCC->AHB1ENR &= ~(1U<<7))
#define GPIOC_ClK_DI() (RCC->AHB1ENR &= ~(1U<<7))
#define GPIOD_ClK_DI() (RCC->AHB1ENR &= ~(1U<<7))
#define GPIOE_ClK_DI() (RCC->AHB1ENR &= ~(1U<<7))
#define GPIOF_ClK_DI() (RCC->AHB1ENR &= ~(1U<<7))
#define GPIOG_ClK_DI() (RCC->AHB1ENR &= ~(1U<<7))
#define GPIOH_ClK_DI() (RCC->AHB1ENR &= ~(1U<<7))


/*GPIO RESET PERIPHERAL REGISTER*/
#define GPIOA_REG_RST()			do{(RCC->AHB1RSTR |= (1 << 0 )); (RCC->AHB1RSTR &= ~(1 << 0));}while(0)
#define GPIOB_REG_RST()			do{(RCC->AHB1RSTR |= (1 << 1 )); (RCC->AHB1RSTR &= ~(1 << 1));}while(0)
#define GPIOC_REG_RST()			do{(RCC->AHB1RSTR |= (1 << 2 )); (RCC->AHB1RSTR &= ~(1 << 2));}while(0)
#define GPIOD_REG_RST()			do{(RCC->AHB1RSTR |= (1 << 3 )); (RCC->AHB1RSTR &= ~(1 << 3));}while(0)
#define GPIOR_REG_RST()			do{(RCC->AHB1RSTR |= (1 << 4 )); (RCC->AHB1RSTR &= ~(1 << 4));}while(0)
#define GPIOF_REG_RST()			do{(RCC->AHB1RSTR |= (1 << 5 )); (RCC->AHB1RSTR &= ~(1 << 5));}while(0)
#define GPIOG_REG_RST()			do{(RCC->AHB1RSTR |= (1 << 6 )); (RCC->AHB1RSTR &= ~(1 << 6));}while(0)
#define GPIOH_REG_RST()			do{(RCC->AHB1RSTR |= (1 << 7 )); (RCC->AHB1RSTR &= ~(1 << 7));}while(0)




/*Peripheral register defination for EXTI Peripheral*/
#define EXTI_BASE_ADR		(APB2_BASE_ADR + 0x3C00U)

typedef struct{
	_vol uint32_t IMR;
	_vol uint32_t EMR;
	_vol uint32_t RTSR;
	_vol uint32_t FTSR;
	_vol uint32_t SWIER;
	_vol uint32_t PR;
}EXTI_RegDef_t;


#define EXTI ((EXTI_RegDef_t*)EXTI_BASE_ADR)


#define SYSCFG_BASE_ADR (APB2_BASE_ADR + 0x3800U)

typedef struct{
	_vol uint32_t MEMRMP;
		_vol uint32_t PMC;
		_vol uint32_t EXTICR[4];
		_vol uint32_t CMPCR;
		_vol uint32_t CFGR;
}SYSCFG_RegDef_t;

#define SYSCFG ((SYSCFG_RegDef_t*)SYSCFG_BASE_ADR)

#define GPIO_TO_PORT(x) (x == GPIOA)?0:\
						(x == GPIOB)?1:\
						(x == GPIOB)?2:\
						(x == GPIOB)?4:\
						(x == GPIOB)?5:\
						(x == GPIOB)?6:\
						(x == GPIOB)?7:\
						(x == GPIOB)?8:0)




/***************************************SPI************************************************
 *
 *
 */
#define SPI1_BASE_ADR	(APB2_BASE_ADR + 0x3000U)

typedef struct{
	_vol uint32_t CR1;
	_vol uint32_t CR2;
	_vol uint32_t SR;
	_vol uint32_t DR;
	_vol uint32_t CRCPR;
	_vol uint32_t RXCRCR;
	_vol uint32_t TXCRCR;
	_vol uint32_t I2SCFGR;
	_vol uint32_t I2SPR;

}SPI_RegDef_t;



#define SPI1 ((SPI_RegDef_t*)SPI1_BASE_ADR)

//Enable clocks
#define SPI1_CLK_EN() (RCC->APB2ENR |= (1U<<12U))
#define SPI1_CLK_DI() do{(RCC->APB1RSTR |= (1 << 12 )); (RCC->APB1RSTR &= ~(1 << 12));}while(0)



#endif /* INC_STM32F446ZXX_H_ */
