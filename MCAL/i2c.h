/*
 * I2c.c
 *
 *  Created on: 3/2/2017
 *  Author: Eng.Hamdy Ahmed Hamdy 
 */


#ifndef I2C_H_
#define I2C_H_

#include "uc_Config.h"
#include "StandardTypes.h"
#include "MACROSh.h"

#define TWBR	(*(vuint8*)0x20)
#define TWCR	(*(vuint8*)0x56)
#define TWSR	(*(vuint8*)0x21)
#define TWDR	(*(vuint8*)0x23)
#define TWAR	(*(vuint8*)0x22)

#define TWINT	(7)
#define TWEA	(6)
#define TWSTA	(5)
#define TWSTO	(4)
#define TWEN	(2)
#define TWIE	(0)

/* I2C Status Bits in the TWSR Register */
// start has been sent
	typedef enum { 
				 TW_START=0x08,
				 TW_REP_START =0x10, 
				 TW_MT_SLA_W_ACK =0x18,
				 TW_MT_SLA_R_ACK =0x40,
				 TW_MT_DATA_ACK  =0x28,
				 TW_MR_DATA_ACK  =0x50, // Master received data and send ACK to slave
				 TW_MR_DATA_NACK =0x58,
				 TW_MT_SLA_W_NACK=0x20,
				 TW_MT_DATA_W_NACK=0x30,
				 TW_MT_SLA_ARB_LOST=0x38,
				 TW_MT_SLA_R_NACK=0x48,
				 }I2C_States;
				 
		typedef enum {WRITE=0,READ=1}ADDRESS_Mode;
		typedef enum {
					   I2C_intDisable = 0x00,
					   I2C_intEnable= 0x01,
					  }I2C_interruptState;
		typedef enum {
						I2C_PRESCALE1,
						I2C_PRESCALE4,
						I2C_PRESCALE16,
						I2C_PRESCALE64,
					  }I2C_Prescaler;
					  
void TWI_Init(
			  I2C_Prescaler Prescale,
			  I2C_interruptState int_state,
			  uint32 F_SCL,
			  uint8 I2C_Address);
			  
			  
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(uint8 data);
uint8 TWI_Read_With_ACK(void); //read with send Ack
uint8 TWI_Read_With_NACK(void); //read without send Ack
uint8 TWI_Get_Status(void);
I2C_States I2C_ByteWrite(uint8 SL_Address, uint8 Reg_Address ,uint8 Data);
I2C_States I2C_ByteRead(uint8 SL_Address , uint8 Reg_Address , uint8 * DataRcv);
#endif /* I2C_H_ */
