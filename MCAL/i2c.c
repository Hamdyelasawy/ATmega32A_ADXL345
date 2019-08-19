/*
 * I2c.c
 *
 *  Created on: 3/2/2017
 *  Author: Eng.Hamdy Ahmed Hamdy 
 */

#include "i2c.h"


void TWI_Init(I2C_Prescaler Prescale , I2C_interruptState int_state , uint32 F_SCL , uint8 Address)
{
	TWAR = Address<<1;
	 /*  Calculating Bit Rate: */
	switch (Prescale)
	{
		case I2C_PRESCALE1:
								TWBR = (uint8) (((float)F_CPU/(2.0*F_SCL)) -8);
								break;
		case I2C_PRESCALE4:
								TWBR = (uint8) (((float)F_CPU/(8.0*F_SCL)) -2);
								break;
		case I2C_PRESCALE16:
								TWBR = (uint8) (((float)F_CPU/(32*F_SCL)) -0.5);
								break;
		case I2C_PRESCALE64:
								TWBR = (uint8) (((float)F_CPU/(128*F_SCL)) -0.125);
								break;
		default:
					break;
	}
   
	
	TWSR |= (Prescale & 0x03);
	TWCR |= (1<<TWEN) | (int_state & 0x01) ;
}

void TWI_Start(void)
{
	 
	/* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
	
	TWCR &= 0X07;
	TWCR |= (1<<TWINT) | (1<<TWSTA);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
   while(ISBETCLEAR(TWCR,TWINT));
}

void TWI_Stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR &= 0X07;
	
    TWCR |=  (1<<TWINT) | (1<<TWSTO);
 
}

void TWI_Write(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
	TWCR &= 0X07;
	
   TWCR |=(1<<TWINT);
   
   /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
   while(ISBETCLEAR(TWCR,TWINT));
}

uint8 TWI_Read_With_ACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
	TWCR &= 0X07;
    TWCR |= (1<<TWINT) | (1<<TWEA);
	    
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(ISBETCLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_Read_With_NACK(void)
{

	TWCR &= 0X07;
	TWCR |= (1<<TWINT);
	
	
	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while(ISBETCLEAR(TWCR,TWINT));
	/* Read Data */
	return TWDR;
}

uint8 TWI_Get_Status(void)
{
   
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    return (TWSR & 0xF8);
}


I2C_States I2C_ByteWrite(uint8 SL_Address,uint8 Reg_Address ,uint8 Data )
{
	TWI_Start();
	if (TWI_Get_Status() != TW_START)
	{
		TWI_Stop();
		return TWI_Get_Status();
	}
	
	TWI_Write((SL_Address<<1));
if (TWI_Get_Status() != TW_MT_SLA_W_ACK)
	{

		TWI_Stop();
		return TWI_Get_Status();
	}
	
	TWI_Write(Reg_Address);
if (TWI_Get_Status() != TW_MT_DATA_ACK)
	{
		TWI_Stop();
		return TWI_Get_Status();
	}
	
TWI_Write(Data);
if (TWI_Get_Status() != TW_MT_DATA_ACK)
	{

		TWI_Stop();
		return TWI_Get_Status();
	}
	
	TWI_Stop(); // Send A stop  // Release The Clock Bus 
	return 0;
}




 

 
I2C_States I2C_ByteRead(uint8 SL_Address , uint8 Reg_Address , uint8 * DataRcv)
{
	
	TWI_Start();
	if (TWI_Get_Status() != TW_START)
	{
		TWI_Stop();
		return TWI_Get_Status();
	}
	
	
	
	TWI_Write((SL_Address<<1));
	if (TWI_Get_Status() != TW_MT_SLA_W_ACK)
	{

		TWI_Stop();
		return TWI_Get_Status();
	}
	
	TWI_Write(Reg_Address);
	if (TWI_Get_Status() != TW_MT_DATA_ACK)
	{
		TWI_Stop();
		return TWI_Get_Status();
	}
	
	TWI_Start(); //rep start
	if (TWI_Get_Status() != TW_REP_START)
	{
		TWI_Stop();
		return TWI_Get_Status();
	}
	
	TWI_Write((SL_Address<<1) | READ);
	if (TWI_Get_Status() != TW_MT_SLA_R_ACK)
	{

		TWI_Stop();
		return TWI_Get_Status();
	}
	
	*DataRcv=TWI_Read_With_NACK();
	TWI_Stop();
	

	return 0;		
}
 
