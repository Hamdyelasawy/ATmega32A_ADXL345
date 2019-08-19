/*
 * ADXL345.c
 *
 * Created: 2/4/2017 7:04:57 PM
 *  Author: Eng.Hamdy Ahmed Hamdy
 *
 */ 

 
#include "ADXL345.h"
#include "LCD.h"

void Accelerometor_init(ADX345_PowerModes Mode , ADXL345_Address EFF_Address)
{	
	I2C_ByteWrite(EFF_Address,POWER_CTRL,Mode);	
	//I2C_ByteWrite(EFF_Address,ACCS_DATA_FORMAT,0x0B);
	//I2C_ByteWrite(EFF_Address,ACCS_OFSX,-1);
//	I2C_ByteWrite(EFF_Address,ACCS_OFSY,0);
//	I2C_ByteWrite(EFF_Address,ACCS_OFSZ,-1);
	//I2C_ByteWrite(EFF_Address,ACCS_DATA_FORMAT,0);
	//I2C_ByteWrite(EFF_Address,ACCS_DATA_FORMAT,8);
			
}



void Accelerometor_ReadAxis(ADXL345_Address EFF_Address ,volatile ADXL345_Data * Data_ptr)  
{
	typedef  union
	{
		uint16 Data;
		struct
		{
			uint8 LSB;
			uint8 MSB;	
		}Byte;
	}ADXL_DA;
	
	ADXL_DA X,Y,Z;
	I2C_ByteRead(EFF_Address , ACCS_DATAX0,&(X.Byte.LSB));
		

	_delay_ms(1);
	I2C_ByteRead(EFF_Address , ACCS_DATAX1,&(X.Byte.MSB));
	_delay_ms(1);
	I2C_ByteRead(EFF_Address , ACCS_DATAY0,&(Y.Byte.LSB));
	_delay_ms(1);
	I2C_ByteRead(EFF_Address , ACCS_DATAY1,&(Y.Byte.MSB));
	_delay_ms(1);
	I2C_ByteRead(EFF_Address , ACCS_DATAZ0,&(Z.Byte.LSB));
	_delay_ms(1);
	I2C_ByteRead(EFF_Address , ACCS_DATAZ1,&(Z.Byte.MSB));
	_delay_ms(1);
	
	Data_ptr ->X_Axis = X.Data;
	Data_ptr ->Y_Axis=Y.Data;
	Data_ptr ->Z_Axis=Z.Data;
	
}