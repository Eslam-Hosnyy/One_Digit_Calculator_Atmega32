/************************************/
/*	Author		: ESLAM_HOSNY		*/
/*	SWC			: KeyPad	 		*/
/*	Layer		: HAL				*/
/*	Version   	: 1.0				*/
/*	Date	  	: October 27, 2022	*/
/*	Last Edit 	: N/A				*/
/************************************/

#ifndef _KPD_CONFIG_H
#define _KPD_CONFIG_H

#define KPD_PORT            MDIO_PORTC

#define KPD_COLUMN0_PIN     PIN4
#define KPD_COLUMN1_PIN     PIN5
#define KPD_COLUMN2_PIN     PIN6
#define KPD_COLUMN3_PIN     PIN7

#define KPD_ROW0_PIN        PIN0
#define KPD_ROW1_PIN        PIN1
#define KPD_ROW2_PIN        PIN2
#define KPD_ROW3_PIN        PIN3

#define NO_PRESSED_KEY      0xff
#define KPD_ARRAY_VAL       {{'1','2','3','+'},{'4','5','6','-'},{'7','8','9','C'},{'*','0','#','/'}}


#endif // KPD_CONFIG_H
