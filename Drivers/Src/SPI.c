
/*
 * SPI.c
 *
 * Created on: Jun 22, 2026
 * Author: Srujan
 */

#include "SPI.h"
#include "stm32f446zxx.h"
#include <stdint.h>

static void SPI_Enable(SPI_RegDef_t* pSPIx, uint8_t EN_DI){
    pSPIx->CR1 |= (EN_DI << 6);
}

void SPI_ClockControl(SPI_Handler* pSPIx, uint8_t EN_DI)
{
    if (EN_DI == ENABLE){
        if (pSPIx->pSPIx == SPI1)
        {
            SPI1_CLK_EN(); // Fixed: Changed from _DI to _EN
        }
    }
    else if(EN_DI == DISABLE)
    {
        if (pSPIx->pSPIx == SPI1)
        {
            SPI1_CLK_DI();
        }
    }
}

void SPI_init(SPI_Handler* pSPIx){
    uint32_t temp = 0;

    //1. Device type
    temp |= (pSPIx->pConfig.SPI_DeviceMode << SPI_CR1_MSTR);

    //2. CPOL
    temp |= (pSPIx->pConfig.CPOL << SPI_CR1_CPOL);

    //3. CPHA
    temp |= (pSPIx->pConfig.CPHA << SPI_CR1_CPHA);

    //4. Baudrate
    temp |= (pSPIx->pConfig.Speed << SPI_CR1_BR);

    //5. communication mode
    if (pSPIx->pConfig.SPI_BusConfig == FULL_DUPLEX){
        temp &= ~(1 << SPI_CR1_BIDIOE);
    }else if(pSPIx->pConfig.SPI_BusConfig == HALF_DUPLEX){
        temp |= (1 << SPI_CR1_BIDIMODE);
    }else if(pSPIx->pConfig.SPI_BusConfig == SIMPLEX){
        temp &= ~(1 << SPI_CR1_BIDIMODE);
        temp |= (1 << SPI_CR1_BIDIOE);
    }

    //6. SSM bit
    temp |= (pSPIx->pConfig.SSM << SPI_CR1_SSM);

    //7. DFF
    temp &= ~(pSPIx->pConfig.SPI_DFF << SPI_CR1_DFF);

    pSPIx->pSPIx->CR1 &= ~(0x7FF);
    pSPIx->pSPIx->CR1 = temp;

    SPI_Enable(pSPIx->pSPIx, pSPIx->pConfig.SPI_periState);
}

void SPI_Dinit(SPI_Handler* pSPIx){
    if (pSPIx->pSPIx == SPI1)
    {
        SPI1_CLK_DI();
    }
}

/* Polling method*/
void SPI_Send(SPI_Handler* pSPIx, uint8_t *pBuffer, uint32_t Len) {
    // 1. Loop until all data bytes are written to the Data Register
    while(Len > 0) {
        // Wait until TXE (Transmit buffer empty) flag is SET
        while( !(pSPIx->pSPIx->SR & (1U << SPI_SR_TXE)) );
        
        // Check DFF bit for 8-bit or 16-bit transmission
        if ((pSPIx->pSPIx->CR1 & (1U << SPI_CR1_DFF)) == 0) {
            // 8-bit Data Frame
            pSPIx->pSPIx->DR = *pBuffer;
            pBuffer++;
            Len--;
        } else {
            // 16-bit Data Frame
            pSPIx->pSPIx->DR = *((uint16_t*)pBuffer);
            pBuffer += 2;
            Len -= 2;
        }
    }

    // 2. Safe Guard: Wait until SPI is completely finished transmitting over the wire
    while( pSPIx->pSPIx->SR & (1U << SPI_SR_BSY) );
}

void SPI_Receive(SPI_Handler *pSPIx, uint8_t *pBuffer, uint32_t Len){
    while (Len > 0) {
        // Wait until RXNE (Receive buffer not empty) flag is SET
        while( !(pSPIx->pSPIx->SR & (1U << SPI_SR_RXNE)) );

        if ((pSPIx->pSPIx->CR1 & (1U << SPI_CR1_DFF)) == 0) {
            // 8-bit Data Frame
            *pBuffer = pSPIx->pSPIx->DR;
            pBuffer++;
            Len--;
        } else {
            // 16-bit Data Frame
            *((uint16_t*)pBuffer) = pSPIx->pSPIx->DR;    
            pBuffer += 2;
            Len -= 2;
        }
    }
}
