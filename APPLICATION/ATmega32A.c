/*
 * ATmega32A_MCAL.c
 *
 * Created: 5/3/2019 9:54:04 AM
 *  Author: Hamdy
 */ 

#include "ATmega32A_GPIO.h"
#include "ATmega32A_USART.h"
#include "i2c.h"
#include "ADXL345.h"
#include "LCD.h"
ADXL345_Data TestData;
int main()
{
	GPIO_DirectionSet(GPIOA,PIN0,INPUTPULLUP);
	TWI_Init(I2C_PRESCALE4,I2C_intDisable,400000,0x07);
	LCD_init();
	Accelerometor_init(ADXL345_MessureMode,ADXL345_ALTERNATIVE_ADDRESS);
	LCD_DisplayString("HELLO \n");
	_delay_ms(500);
	LCD_Clear();
	while(1)
	{
		Accelerometor_ReadAxis(ADXL345_ALTERNATIVE_ADDRESS,&TestData);
		LCD_DisplayString("X = ");
		LCD_DisplayInt((uint16)TestData.X_Axis);
		LCD_DisplayString("  Y=");
		LCD_DisplayInt((uint16)TestData.Y_Axis);
		LCD_Select_RowCol(1,0);
		LCD_DisplayString("Z=");
		LCD_DisplayInt((uint16)TestData.Z_Axis);
		_delay_ms(250);
		LCD_Clear();
	}
}