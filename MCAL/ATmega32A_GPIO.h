/*
 * ATmega32A_GPIO.h
 *
 * Created: 5/3/2019 11:01:57 AM
 *  Author: Hamdy
 */ 


#ifndef ATMEGA32A_GPIO_H_
#define ATMEGA32A_GPIO_H_

	#include "MACROSh.h"
	#include "StandardTypes.h"
	#include "uc_Config.h"
	
	#define GPIOA ((gpio *)(0x39))
	#define GPIOB ((gpio *)(0x36))
	#define GPIOC ((gpio *)(0x33))
	#define GPIOD ((gpio *)(0x30))
		
typedef enum
{
	INPUTFLOAT,
	INPUTPULLUP,
	OUTPUT,
}pinModes;

typedef enum
{
	PIN0,PIN1,PIN2,PIN3,PIN4,PIN5,PIN6,PIN7	
}Gpio_pins;

typedef enum
{
	LOW,
	HIGH,
}digitalSignal;

typedef union
{
	vuint8 data;
	struct  
	{
		vuint8 B0:1;
		vuint8 B1:1;
		vuint8 B2:1;
		vuint8 B3:1;
		vuint8 B4:1;
		vuint8 B5:1;
		vuint8 B6:1;
		vuint8 B7:1;
	}bits;
}reg8;


typedef struct 
{
	reg8 pin;
	reg8 ddr;
	reg8 port;
}gpio;

void	GPIO_DirectionSet(
							gpio *		 G   ,
							Gpio_pins	 pins,
							pinModes mode);
							
digitalSignal    GPIO_InputHandle(
							gpio * Gp,
							Gpio_pins pin);
	
void 	GPIO_OutputHandle(
						gpio *    Gp,
						Gpio_pins pin,
						digitalSignal State);

#endif /* ATMEGA32A_GPIO_H_ */