
/*
 * SPI.c
 *
 * Created on: Jun 22, 2026
 * Author: Srujan
 */

#include "SPI.h"
#include "stm32f446zxx.h"
#include <stdint.h>


static void SPI_Enable(SPI_RegDef_t* pSPIx, uint8_t EN_DI) {
    if (EN_DI == ENABLE) {
        pSPIx->CR1 |= (1 << 6); // Set SPE bit
    } else {
        pSPIx->CR1 &= ~(1 << 6); // Clear SPE bit
    }
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

    // 7. DFF
    temp |= (pSPIx->pConfig.SPI_DFF << SPI_CR1_DFF);

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
void SPI_Receive(SPI_Handler *pSPIx, uint8_t *pBuffer, uint32_t Len) {
    while (Len > 0) {
        // 1. Send a dummy byte to generate the clock ticks
        // Wait for RXE to be ready
        while( !(pSPIx->pSPIx->SR & (1U << SPI_SR_RXNE)) );
        
        if ((pSPIx->pSPIx->CR1 & (1U << SPI_CR1_DFF)) == 0) {
            pSPIx->pSPIx->DR = 0xFF; // 8-bit dummy data
        } else {
            pSPIx->pSPIx->DR = 0xFFFF; // 16-bit dummy data
        }

        // 2. Now wait for the incoming data to shift in
        while( !(pSPIx->pSPIx->SR & (1U << SPI_SR_RXNE)) );

        // 3. Read the data
        if ((pSPIx->pSPIx->CR1 & (1U << SPI_CR1_DFF)) == 0) {
            *pBuffer = pSPIx->pSPIx->DR;
            pBuffer++;
            Len--;
        } else {
            *((uint16_t*)pBuffer) = pSPIx->pSPIx->DR;    
            pBuffer += 2;
            Len -= 2;
        }
    }
}

uint8_t SPI_SendDataIT(SPI_Handler* pSPIx,uint8_t *pBuffer,uint32_t Len){
    uint8_t state = pSPIx->TxState;

    if (state != SPI_BSY_IN_TX){
        
    //1. save the Tx buffer address and len info
    pSPIx->pTxBuffer = pBuffer;
    pSPIx->TxLen = Len;

    //2. mark the SPI state as busy
    pSPIx->TxState = SPI_BSY_IN_TX;

    //3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in S
    pSPIx->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);
    }

    return state;
}

uint8_t SPI_ReceiveDataIT(SPI_Handler* pSPIx,uint8_t *pBuffer,uint32_t Len){
    uint8_t state = pSPIx->RxState;
    if(state != SPI_BSY_IN_RX){
        //1. save the Tx buffer address and len info
        pSPIx->pRxBuffer = pBuffer;
        pSPIx->RxLen = Len;

        //2. mark the SPI state as busy
        pSPIx->RxState = SPI_BSY_IN_RX;

        //3. Enable the TXEIE control bit to get interrupt whenever TXE flag is set in SR
        pSPIx->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);
        
        
    }
    return state;
}


void SPI_IRQHandler(SPI_Handler *pSPIx){
    if ((pSPIx->pSPIx->SR & (1 << SPI_SR_TXE) && (pSPIx->TxState == SPI_BSY_IN_TX))){
        while(pSPIx->TxLen > 0){
            if ((pSPIx->pSPIx->CR1 & (1 << SPI_CR1_DFF)) == 0){
                pSPIx->pSPIx->DR = *(pSPIx->pTxBuffer);
                pSPIx->pTxBuffer++;
                pSPIx->TxLen--;
            }else if ((pSPIx->pSPIx->CR1 & (1 << SPI_CR1_DFF)) != 0){
             
                pSPIx->pSPIx->DR = *((uint16_t*)pSPIx->pTxBuffer);
                pSPIx->pTxBuffer += 2;
                pSPIx->TxLen -= 2;
            }
        }
        pSPIx->TxState = SPI_READY;
        pSPIx->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);

    }else if ((pSPIx->pSPIx->SR & (1 << SPI_SR_RXNE) && (pSPIx->RxState == SPI_BSY_IN_RX))){
        while(pSPIx->RxLen > 0){
            if ((pSPIx->pSPIx->CR1 & (1 << SPI_CR1_DFF)) == 0){
                *(pSPIx->pRxBuffer) = pSPIx->pSPIx->DR;
                pSPIx->pRxBuffer++;
                pSPIx->RxLen--;
            }else if ((pSPIx->pSPIx->CR1 & (1 << SPI_CR1_DFF)) != 0){
                *((uint16_t*)pSPIx->pRxBuffer) = pSPIx->pSPIx->DR;
                *((uint16_t*)pSPIx->pRxBuffer) = pSPIx->pSPIx->DR;
                pSPIx->pRxBuffer += 2;
                pSPIx->RxLen -= 2;
            }
        }
        
        pSPIx->TxState = SPI_READY;
        pSPIx->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);
    }


        
 }

