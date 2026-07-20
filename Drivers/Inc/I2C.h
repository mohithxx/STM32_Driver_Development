#ifndef INC_I2C_H_
#define INC_I2C_H_
#include"stm32f446zxx.h"

typedef struct {
    uint32_t I2C_SCLSpeed;
    uint8_t  I2C_DeviceAddress;
    uint8_t  I2C_ACKControl;
    uint8_t  I2C_FMDutyCycle;
} I2C_Config_t;

typedef struct{
    I2C_Config_t *pConfig;
    I2C_RegDef_t *pI2Cx;
    

}I2C_Handler_t;

#endif