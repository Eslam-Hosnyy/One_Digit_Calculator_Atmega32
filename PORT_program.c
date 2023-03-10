/************************************/
/*	Author		: ESLAM_HOSNY		*/
/*	SWC			: PORT     			*/
/*	Layer		: MCAL				*/
/*	Version   	: 1.0				*/
/*	Date	  	: October 26, 2022	*/
/*	Last Edit 	: N/A           	*/
/************************************/

#include "LSTD_types.h"
#include "PORT_config.h"
#include "PORT_private.h"
#include "PORT_interface.h"

void PORT_voidInit(void)
{
    GPIOA_DDR = PORTA_DIR;
    GPIOB_DDR = PORTB_DIR;
    GPIOC_DDR = PORTC_DIR;
    GPIOD_DDR = PORTD_DIR;

    GPIOA_PORT = PORTA_INIT_VALUE;
    GPIOB_PORT = PORTB_INIT_VALUE;
    GPIOC_PORT = PORTC_INIT_VALUE;
    GPIOD_PORT = PORTD_INIT_VALUE;
}
