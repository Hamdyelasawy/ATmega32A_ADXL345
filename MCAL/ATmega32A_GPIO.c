/*
 * ATmega32A_GPIO.c
 *
 * Created: 5/3/2019 11:02:05 AM
 *  Author: Hamdy
 */ 

	#include "ATmega32A_GPIO.h"
	
	void	GPIO_DirectionSet(
								gpio *		 G,
								Gpio_pins	 pin,
								pinModes mode
							)
				{
					switch(mode)
					{
						case INPUTFLOAT:
							/* Config pin as an input */
							 CLEARBIT(G->ddr.data , pin);
							/* Make sure pin is in float mode */
							 CLEARBIT(G->port.data , pin);
							 break;
						case INPUTPULLUP:
							/* Config pin as an input */
							CLEARBIT(G->ddr.data , pin);
							/* Set  pin  in PULLUP  mode */
							SETBIT(G->port.data , pin);
							break;
						case OUTPUT:
							/* Config pin in output Mode */
							SETBIT(G->ddr.data , pin);
							break;
					}
					
					
					void 	GPIO_OutputHandle(
												gpio *    Gp,
												Gpio_pins pin,
												digitalSignal State)
										{
											if ( HIGH == State)
											{
												SETBIT(Gp->port.data , pin);
											}
											else
											{
												CLEARBIT(Gp->port.data , pin);
											}
										}

				}
				
				
				digitalSignal    GPIO_InputHandle(
													gpio * Gp,
													Gpio_pins pin)
				{
								return ISBITSET(Gp->pin.data , pin);
				}