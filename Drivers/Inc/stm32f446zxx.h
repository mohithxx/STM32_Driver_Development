/*Here is your cleaned-up, well-organized, and beautifully formatted **`stm32f446zxx.h`** header file.

### Key Improvements Made:

* **Fixed Bugs:** Corrected the Clock Disable (`_DI`) macros for GPIOs, which were all mistakenly hardcoded to clear bit 7 (`GPIOH`). They now properly target their respective bits using `&= ~(1U << X)`.
* **Fixed `GPIO_TO_PORT` Macro:** Fixed the copy-paste errors where `GPIOB` was written repeatedly instead of checking `GPIOC`, `GPIOD`, etc.
* **Formatting & Readability:** Standardized alignment, added clean section dividers, and grouped related definitions logically.

```c
/*
 * stm32f446zxx.h
 *
 * Created on: May 18, 2026
 * Author: Srujan
 */

#ifndef INC_STM32F446ZXX_H_
#define INC_STM32F446ZXX_H_

#include <stdint.h>

/* ========================================================================== */
/* GENERIC DEFINITIONS                              */
/* ========================================================================== */
#define ENABLE          1
#define DISABLE         0
#define SET             ENABLE
#define RESET           DISABLE

#define _vol            volatile

/* ========================================================================== */
/* MEMORY & BUS BASE ADDRESSES                          */
/* ========================================================================== */
#define FLASH_BASE_ADR  0x08000000UL
#define SRAM1_BASE_ADR  0x20000000UL /* 112 KB */
#define SRAM2_BASE_ADR  0x2001C000UL /* 16 KB */

/* Bus Domains */
#define PERIPHERAL_BASE_ADR 0x40000000UL
#define APB1_BASE_ADR       PERIPHERAL_BASE_ADR
#define APB2_BASE_ADR       0x40010000UL
#define AHB1_BASE_ADR       0x40020000UL
#define AHB2_BASE_ADR       0x50000000UL

/* ========================================================================== */
/* RCC PERIPHERAL                                 */
/* ========================================================================== */

/* RCC Register Definition Structure */
typedef struct {
    _vol uint32_t CR;
    _vol uint32_t PLLCFGR;
    _vol uint32_t CFGR;
    _vol uint32_t CIR;
    _vol uint32_t AHB1RSTR;
    _vol uint32_t AHB2RSTR;
    _vol uint32_t AHB3RSTR;
    _vol uint32_t RESERVED0;
    _vol uint32_t APB1RSTR;
    _vol uint32_t APB2RSTR;
    _vol uint32_t RESERVED1[2];
    _vol uint32_t AHB1ENR;
    _vol uint32_t AHB2ENR;
    _vol uint32_t AHB3ENR;
    _vol uint32_t RESERVED2;
    _vol uint32_t APB1ENR;
    _vol uint32_t APB2ENR;
    _vol uint32_t RESERVED3[2];
    _vol uint32_t AHB1LPENR;
    _vol uint32_t AHB2LPENR;
    _vol uint32_t AHB3LPENR;
    _vol uint32_t RESERVED4;
    _vol uint32_t APB1LPENR;
    _vol uint32_t APB2LPENR;
    _vol uint32_t RESERVED5[2];
    _vol uint32_t BDCR;
    _vol uint32_t CSR;
    _vol uint32_t RESERVED6[2];
    _vol uint32_t SSCGR;
    _vol uint32_t PLLI2SCFGR;
    _vol uint32_t PLLSAICFGR;
    _vol uint32_t DCKCFGR;
    _vol uint32_t CKGATENR;
    _vol uint32_t DCKCFGR2;
} RCC_RegDef_t;

#define RCC_BASE_ADR    (AHB1_BASE_ADR + 0x3800U)
#define RCC             ((RCC_RegDef_t*)RCC_BASE_ADR)

/* System Clock Selection (RCC_CFGR_SW) */
#define RCC_SYSCLK_HSI       (0x00UL)
#define RCC_SYSCLK_HSE       (0x01UL)
#define RCC_SYSCLK_PLL_P     (0x10UL)
#define RCC_SYSCLK_PLL_R     (0x11UL)

/* APB Low-Speed Prescaler (PPRE1 - Max 45 MHz) */
#define RCC_APB1_DIV1        (0x00UL) 
#define RCC_APB1_DIV2        (0x04UL) 
#define RCC_APB1_DIV4        (0x05UL) 
#define RCC_APB1_DIV8        (0x06UL) 
#define RCC_APB1_DIV16       (0x07UL) 

/* APB High-Speed Prescaler (PPRE2 - Max 90 MHz) */
#define RCC_APB2_DIV1        (0x00UL)
#define RCC_APB2_DIV2        (0x04UL)
#define RCC_APB2_DIV4        (0x05UL)

/* ========================================================================== */
/* GPIO PERIPHERAL                                */
/* ========================================================================== */

/* GPIO Register Definition Structure */
typedef struct {
    _vol uint32_t MODER;
    _vol uint32_t OTYPER;
    _vol uint32_t OSPEEDR;
    _vol uint32_t PUPDR;
    _vol uint32_t IDR;
    _vol uint32_t ODR;
    _vol uint32_t BSRR;
    _vol uint32_t LCKR;
    _vol uint32_t AFR[2];
} GPIO_RegDef_t;

/* GPIO Peripheral Base Addresses */
#define GPIOA           ((GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x0000U))
#define GPIOB           ((GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x0400U))
#define GPIOC           ((GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x0800U))
#define GPIOD           ((GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x0C00U))
#define GPIOE           ((GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x1000U))
#define GPIOF           ((GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x1400U))
#define GPIOG           ((GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x1800U))
#define GPIOH           ((GPIO_RegDef_t*)(AHB1_BASE_ADR + 0x1C00U))

/* GPIO Clock Enable Macros */
#define GPIOA_CLK_EN()  (RCC->AHB1ENR |= (1U << 0))
#define GPIOB_CLK_EN()  (RCC->AHB1ENR |= (1U << 1))
#define GPIOC_CLK_EN()  (RCC->AHB1ENR |= (1U << 2))
#define GPIOD_CLK_EN()  (RCC->AHB1ENR |= (1U << 3))
#define GPIOE_CLK_EN()  (RCC->AHB1ENR |= (1U << 4))
#define GPIOF_CLK_EN()  (RCC->AHB1ENR |= (1U << 5))
#define GPIOG_CLK_EN()  (RCC->AHB1ENR |= (1U << 6))
#define GPIOH_CLK_EN()  (RCC->AHB1ENR |= (1U << 7))

/* GPIO Clock Disable Macros */
#define GPIOA_CLK_DI()  (RCC->AHB1ENR &= ~(1U << 0))
#define GPIOB_CLK_DI()  (RCC->AHB1ENR &= ~(1U << 1))
#define GPIOC_CLK_DI()  (RCC->AHB1ENR &= ~(1U << 2))
#define GPIOD_CLK_DI()  (RCC->AHB1ENR &= ~(1U << 3))
#define GPIOE_CLK_DI()  (RCC->AHB1ENR &= ~(1U << 4))
#define GPIOF_CLK_DI()  (RCC->AHB1ENR &= ~(1U << 5))
#define GPIOG_CLK_DI()  (RCC->AHB1ENR &= ~(1U << 6))
#define GPIOH_CLK_DI()  (RCC->AHB1ENR &= ~(1U << 7))

/* GPIO Reset Macros */
#define GPIOA_REG_RST()  do{(RCC->AHB1RSTR |= (1U << 0)); (RCC->AHB1RSTR &= ~(1U << 0));}while(0)
#define GPIOB_REG_RST()  do{(RCC->AHB1RSTR |= (1U << 1)); (RCC->AHB1RSTR &= ~(1U << 1));}while(0)
#define GPIOC_REG_RST()  do{(RCC->AHB1RSTR |= (1U << 2)); (RCC->AHB1RSTR &= ~(1U << 2));}while(0)
#define GPIOD_REG_RST()  do{(RCC->AHB1RSTR |= (1U << 3)); (RCC->AHB1RSTR &= ~(1U << 3));}while(0)
#define GPIOE_REG_RST()  do{(RCC->AHB1RSTR |= (1U << 4)); (RCC->AHB1RSTR &= ~(1U << 4));}while(0)
#define GPIOF_REG_RST()  do{(RCC->AHB1RSTR |= (1U << 5)); (RCC->AHB1RSTR &= ~(1U << 5));}while(0)
#define GPIOG_REG_RST()  do{(RCC->AHB1RSTR |= (1U << 6)); (RCC->AHB1RSTR &= ~(1U << 6));}while(0)
#define GPIOH_REG_RST()  do{(RCC->AHB1RSTR |= (1U << 7)); (RCC->AHB1RSTR &= ~(1U << 7));}while(0)

/* Helper Macro to convert GPIO Base Address to Port Code */
#define GPIO_TO_PORT(x) ((x == GPIOA) ? 0 :\
                         (x == GPIOB) ? 1 :\
                         (x == GPIOC) ? 2 :\
                         (x == GPIOD) ? 3 :\
                         (x == GPIOE) ? 4 :\
                         (x == GPIOF) ? 5 :\
                         (x == GPIOG) ? 6 :\
                         (x == GPIOH) ? 7 : 0)

/* ========================================================================== */
/* SPI PERIPHERAL                                 */
/* ========================================================================== */

/* SPI Register Definition Structure */
typedef struct {
    _vol uint32_t CR1;
    _vol uint32_t CR2;
    _vol uint32_t SR;
    _vol uint32_t DR;
    _vol uint32_t CRCPR;
    _vol uint32_t RXCRCR;
    _vol uint32_t TXCRCR;
    _vol uint32_t I2SCFGR;
    _vol uint32_t I2SPR;
} SPI_RegDef_t;

#define SPI1_BASE_ADR   (APB2_BASE_ADR + 0x3000U)
#define SPI1            ((SPI_RegDef_t*)SPI1_BASE_ADR)

/* SPI Configuration Options */
#define MASTER          0
#define SLAVE           1

#define FCLK_2          0
#define FCLK_4          1
#define FCLK_8          2
#define FCLK_16         3
#define FCLK_32         4
#define FCLK_64         5
#define FCLK_128        6
#define FCLK_256        7

#define FULL_DUPLEX     0
#define HALF_DUPLEX     1
#define SIMPLEX         2

#define SSM_DI          0
#define SSM_EN          1

#define DFF_8B          0
#define DFF_16B         1

#define CPOL_IDLE_LOW	0
#define CPOL_IDLE_HIGH	1

#define CPHA_FIRST_EDGE 0
#define CPHA_SEC_EDGE	1


/* SPI Bit Position Definitions */
/* SPI_CR1 */
#define SPI_CR1_CPHA        0
#define SPI_CR1_CPOL        1
#define SPI_CR1_MSTR        2
#define SPI_CR1_BR          3
#define SPI_CR1_SPE         6
#define SPI_CR1_LSBFIRST    7
#define SPI_CR1_SSI         8
#define SPI_CR1_SSM         9
#define SPI_CR1_RXONLY      10
#define SPI_CR1_DFF         11
#define SPI_CR1_CRCNEXT     12
#define SPI_CR1_CRCEN       13
#define SPI_CR1_BIDIOE      14
#define SPI_CR1_BIDIMODE    15

/* SPI_CR2 */
#define SPI_CR2_RXDMAEN     0
#define SPI_CR2_TXDMAEN     1
#define SPI_CR2_SSOE        2
#define SPI_CR2_FRF         4
#define SPI_CR2_ERRIE       5
#define SPI_CR2_RXNEIE      6
#define SPI_CR2_TXEIE       7

/* SPI_SR */
#define SPI_SR_RXNE         0
#define SPI_SR_TXE          1
#define SPI_SR_CHSIDE       2
#define SPI_SR_UDR          3
#define SPI_SR_CRCERR       4
#define SPI_SR_MODF         5
#define SPI_SR_OVR          6
#define SPI_SR_BSY          7
#define SPI_SR_FRE          8

/* SPI Clock Control Macros */
#define SPI1_CLK_EN()   (RCC->APB2ENR |= (1U << 12))
#define SPI1_CLK_DI()   do{(RCC->APB2RSTR |= (1U << 12)); (RCC->APB2RSTR &= ~(1U << 12));}while(0)

/* ========================================================================== */
/* EXTI PERIPHERAL                                */
/* ========================================================================== */

/* EXTI Register Definition Structure */
typedef struct {
    _vol uint32_t IMR;
    _vol uint32_t EMR;
    _vol uint32_t RTSR;
    _vol uint32_t FTSR;
    _vol uint32_t SWIER;
    _vol uint32_t PR;
} EXTI_RegDef_t;

#define EXTI_BASE_ADR   (APB2_BASE_ADR + 0x3C00U)
#define EXTI            ((EXTI_RegDef_t*)EXTI_BASE_ADR)

/* ========================================================================== */
/* SYSCFG PERIPHERAL                               */
/* ========================================================================== */

/* SYSCFG Register Definition Structure */
typedef struct {
    _vol uint32_t MEMRMP;
    _vol uint32_t PMC;
    _vol uint32_t EXTICR[4];
    _vol uint32_t CMPCR;
    _vol uint32_t CFGR;
} SYSCFG_RegDef_t;

#define SYSCFG_BASE_ADR (APB2_BASE_ADR + 0x3800U)
#define SYSCFG          ((SYSCFG_RegDef_t*)SYSCFG_BASE_ADR)

#endif /* INC_STM32F446ZXX_H_ */

