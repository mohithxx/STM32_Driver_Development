/*
 * SPI.h
 *
 *  Created on: Jun 22, 2026
 *      Author: Srujan
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_
#include "stm32f446zxx.h"
#include <stdint.h>

//SPI MACROS



typedef struct{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_DFF;
	uint8_t CPHA;
	uint8_t CPOL;
	uint8_t SSM;
	uint8_t Speed;
	uint8_t SPI_periState;
	
}SPI_config_t;

typedef struct{
	SPI_RegDef_t* pSPIx;
	SPI_config_t pConfig;
}SPI_Handler;


void SPI_ClockControl(SPI_Handler* pSPIx, uint8_t EN_DI);
void SPI_init(SPI_Handler* pSPIx);
void SPI_Dinit(SPI_Handler* pSPIx);


void SPI_Send(SPI_Handler* pSPIx,uint8_t *pBuffer,uint32_t Len);
void SPI_Receive(SPI_Handler* pSPIx,uint8_t *pBuffer,uint32_t Len);


#endif /* INC_SPI_H_ */
