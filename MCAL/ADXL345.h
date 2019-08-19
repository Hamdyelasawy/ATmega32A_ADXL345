/*
 * ADXL345.h
 *
 * Created: 2/4/2017 7:05:10 PM
 *  Author: Hamdy
 */ 


#ifndef ADXL345_H_
		#define  ADXL345_H_

#include "uc_Config.h"
#include "StandardTypes.h"
#include "MACROSh.h"
#include "i2c.h"

		typedef enum {
			ADXL345_MessureMode=0x08,
		}ADX345_PowerModes;

	typedef enum {
					 ADXL345_MAIN_ADDRESS =(0x1D),
					 ADXL345_ALTERNATIVE_ADDRESS=(0x53),
				 }ADXL345_Address;
		  

	typedef struct {
						float X_Axis;
						float Y_Axis;
						float Z_Axis;
		}ADXL345_Data;
// Register Table From Data Sheet
typedef enum {
			  ADXL345_FULLRANGE =0,
			  INT_ENABLE        =0x2E,
			  ADXL345_RANGE2G   =0x00,
			  POWER_CTRL        =0x2D,		  
			  ACCS_THRESH_TAP   = 0x1D,
			  ACCS_OFSX	        = 0x1E, 
			  ACCS_OFSY	        =  0x1F,
			  ACCS_OFSZ	        =   0x20,
			  ACCS_DUR		    = 0X21,
			  ACCS_Latent       =	 0x22,
			  ACCS_Window	    =	 0x23,
			  ACCS_DATAX0	    =	 0x32,
			  ACCS_DATAX1	    =	 0x33,
			  ACCS_DATAY0	    =	 0x34,
			  ACCS_DATAY1	    =	 0x35,
			  ACCS_DATAZ0	    =	 0x36,
			  ACCS_DATAZ1	    =	 0x37,
			  ACCS_DATA_FORMAT  =	 0x31,
			  ACCS_FIFO_CTL	    =	 0x38,
			  ACCS_FIFO_STATUS  =	 0x39,
			}ADXL345_RegAddress;


void Accelerometor_init
					(ADX345_PowerModes Mode,
					ADXL345_Address EFF_Address);



void Accelerometor_ReadAxis(
							ADXL345_Address EFF_Address ,
							volatile ADXL345_Data * Data_ptr);


#endif /* ADXL345_H_ */