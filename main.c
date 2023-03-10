
/************************************/
/*	Author		: Eslam_Hosny		*/
/*	SWC			: ONE_DIGIT_CAL		*/
/*	Layer		: APP				*/
/*	Version   	: 1.0				*/
/*	Date	  	: November, 7, 2022	*/
/*	Last Edit 	: N/A				*/
/************************************/
#define F_CPU	8000000UL
#include "util/delay.h"
#include "LSTD_types.h"
#include "LBIT_math.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "INFIX_POSTFIX_interface.h"


int main (void)
{
	PORT_voidInit();
	CLCD_voidInit();
	CLCD_voidClear();



	CALCULAT_voidCal();

	return 0;
}




