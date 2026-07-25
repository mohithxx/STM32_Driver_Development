#ifndef INC_I2C_H_
#define INC_I2C_H_
#include"stm32f446zxx.h"


#define I2C_SCL_SPEED_SM 100000
#define I2C_SCL_SPEED_FM2K 200000
#define I2C_SCL_SPEED_FM4K 400000

#define I2C_ACK_EN 1
#define I2C_ACK_DI 0

#define I2C_FM_DUTY_2 0
#define I2C_FM_DUTY_16_9 1









typedef struct {
    uint32_t I2C_SCLSpeed;
    uint8_t  I2C_DeviceAddress;
    uint8_t  I2C_ACKControl;
    uint8_t  I2C_FMDutyCycle;
    uint8_t I2C_Mode; // 0 for SM, 1 for FM
} I2C_Config_t;

typedef struct{
    I2C_Config_t pConfig;
    I2C_RegDef_t *pI2Cx;
    

}I2C_Handler_t;


void I2C_Init(I2C_Handler_t *pI2Cx);
void I2C_DeInit(I2C_Handler_t *pI2Cx);
void I2C_ClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);
void I2C_peripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

#endif