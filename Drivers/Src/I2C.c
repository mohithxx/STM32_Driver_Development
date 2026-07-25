#include"I2C.h"
void I2C_DeInit(I2C_Handler_t *pI2Cx){
    if(pI2Cx->pI2Cx==I2C1){
        I2C1_CLK_DI();
    }else if(pI2Cx->pI2Cx==I2C2){
        I2C2_CLK_DI();
    }
}

void I2C_ClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi){
    if(EnorDi==ENABLE){
        if(pI2Cx==I2C1){
            I2C1_CLK_EN();
        }else if(pI2Cx==I2C2){
            I2C2_CLK_EN();
        }
    }else{
        if(pI2Cx==I2C1){
            I2C1_CLK_DI();
        }else if(pI2Cx==I2C2){
            I2C2_CLK_DI();
        }
    }
}

void I2C_peripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi){
    if(EnorDi==ENABLE){
        pI2Cx->CR1 |= (1<<I2C_CR1_PE);
    }else{
        pI2Cx->CR1 &= ~(1<<I2C_CR1_PE);
    }
}
void I2C_Init(I2C_Handler_t *pI2Cx){
    uint32_t tempreg=0;
     //1. Configure the Mode (standard mode or fast mode) and the SCL speed
     tempreg |= pI2Cx->pConfig.I2C_Mode << I2C_CCR_FS;

     //2. configure the speed of the serial clock line (SCL) in the CR2 register
    

     //3. configure the device address in the OAR1 register


     //4. configure the ACK control bit in the CR1 register



   
} 