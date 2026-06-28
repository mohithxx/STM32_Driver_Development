/*
 * SPI.c
 *
 *  Created on: Jun 22, 2026
 *      Author: Srujan
 */


#include "SPI.h"
#include "stm32f446zxx.h"

void SPI_ClockControl(SPI_Handler* pSPIx, uint8_t EN_DI )
{
	if (EN_DI == ENABLE){
		if (&(pSPIx->pSPIx) == SPI1)
		{
			SPI1_CLK_DI();
		}

	}
	else if(EN_DI == DISABLE)
	{
		SPI1_CLK_DI();
	}

}

void SPI_init(SPI_Handler* pSPIx){
	uint32_t temp = 0;

	//1. Device type
	temp|= (pSPIx->pConfig.SPI_DeviceMode << SPI_CR1_MSTR);

	//2. CPOL
	temp|= (pSPIx->pConfig.CPOL << SPI_CR1_CPOL);

	//3. CPHA
	temp|= (pSPIx->pConfig.CPHA << SPI_CR1_CPHA);

	//4. Baudrate
	temp|= (pSPIx->pConfig.Speed << SPI_CR1_BR);

	//5. communication mode
	if (pSPIx->pConfig.SPI_BusConfig == FULL_DUPLEX){
		temp &= ~(1 << SPI_CR1_BIDIOE);

	}else if(pSPIx->pConfig.SPI_BusConfig == HALF_DUPLEX){
		temp |= (1 << SPI_CR1_BIDIMODE);

	}else if(pSPIx->pConfig.SPI_BusConfig == SIMPLEX){
		temp &= ~ (1 << SPI_CR1_BIDIMODE);
		temp |= (1 << SPI_CR1_BIDIOE);

	}

	//6. SSM bit

		temp |= (pSPIx->pConfig.SSM << SPI_CR1_SSM);


	//7. DFF

		temp &= ~(pSPIx->pConfig.SPI_DFF << SPI_CR1_DFF);

	//	pSPIx->pSPIx.CR1 &= ~(0x7FF);
		pSPIx->pSPIx.CR1 = temp;


}

void SPI_Dinit(SPI_Handler* pSPIx){

}




