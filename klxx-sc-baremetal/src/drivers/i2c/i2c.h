/*
 * File:        k60_i2c.h
 * Purpose:     I2C header
 *
 * Notes:
 *
 */


#define ACCEL_I2C_ADDRESS                         0x1C

#define i2c_DisableAck()       I2C1_C1 |= I2C_C1_TXAK_MASK

#define i2c_RepeatedStart()    I2C1_C1 |= I2C_C1_RSTA_MASK;

#define i2c_Start()            I2C1_C1 |= I2C_C1_TX_MASK;\
                               I2C1_C1 |= I2C_C1_MST_MASK

#define i2c_Stop()             I2C1_C1 &= ~I2C_C1_MST_MASK;\
                               I2C1_C1 &= ~I2C_C1_TX_MASK

#define i2c_EnterRxMode()      I2C1_C1 &= ~I2C_C1_TX_MASK;\
                               I2C1_C1 &= ~I2C_C1_TXAK_MASK

#define i2c_Wait()               while((I2C1_S & I2C_S_IICIF_MASK)==0) {} \
                                  I2C1_S |= I2C_S_IICIF_MASK;

#define i2c_write_byte(data)   I2C1_D = data


///////////////////////////////////////////////////////////////////////////////////
// I2C0 functions
///////////////////////////////////////////////////////////////////////////////////
                                   
#define i2c0_DisableAck()       I2C0_C1 |= I2C_C1_TXAK_MASK

#define i2c0_RepeatedStart()    I2C0_C1 |= I2C_C1_RSTA_MASK;

#define i2c0_Start()            I2C0_C1 |= I2C_C1_TX_MASK;\
                               I2C0_C1 |= I2C_C1_MST_MASK

#define i2c0_Stop()             I2C0_C1 &= ~I2C_C1_MST_MASK;\
                               I2C0_C1 &= ~I2C_C1_TX_MASK

#define i2c0_EnterRxMode()      I2C0_C1 &= ~I2C_C1_TX_MASK;\
                               I2C0_C1 &= ~I2C_C1_TXAK_MASK

#define i2c0_Wait()               while((I2C0_S & I2C_S_IICIF_MASK)==0) {} \
                                  I2C0_S |= I2C_S_IICIF_MASK;
                               
#define i2c0_WBusy()            while((I2C0_S & I2C_S_BUSY_MASK));

#define i2c0_write_byte(data)   I2C0_D = data

#define MWSR                   0x00  /* Master write  */
#define MRSW                   0x01  /* Master read */

void init_I2C(void);
void init_I2C0(void);
void IIC_StartTransmission (unsigned char SlaveID, unsigned char Mode);
void I2CWriteRegister(unsigned char SlaveAddr, unsigned char u8RegisterAddress, unsigned char u8Data);
unsigned char I2CReadRegister(unsigned char u8RegisterAddress);
unsigned char I2CReadMultiRegisters(unsigned char SlaveAddr, unsigned char u8RegisterAddress, unsigned char bytes, char buf[]);
void I2CWriteMultiRegister(unsigned char SlaveAddr, unsigned char u8RegisterAddress, unsigned char *u8Data, unsigned int length);


////////////////////////////////////////////////////////////////////////////////////////////
// Declare I2C0 Functions
////////////////////////////////////////////////////////////////////////////////////////////
void IIC0_StartTransmission (unsigned char SlaveID, unsigned char Mode);
void I2C0WriteRegister(unsigned char SlaveAddr, unsigned char u8RegisterAddress, unsigned char u8Data);
unsigned char I2C0ReadRegister(unsigned char SlaveAddr, unsigned char u8RegisterAddress);
unsigned char I2C0ReadMultiRegisters(unsigned char SlaveAddr, unsigned char u8RegisterAddress, unsigned char bytes, char buf[]);
void I2C0WriteMultiRegister(unsigned char SlaveAddr, unsigned char u8RegisterAddress, unsigned char *u8Data, unsigned int length);
