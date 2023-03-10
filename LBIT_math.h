/****************************************/
/*	Author		: ESLAM_HOSNY			*/
/*	SWC			: DIO     				*/
/*	Layer		: LIB					*/
/*	Version   	: 1.1					*/
/*	Date	  	: September 19, 2022	*/
/*	Last Edit 	: November	10, 2022	*/
/****************************************/

#ifndef _LBIT_MATH_H_
#define _LBIT_MATH_H_

#define	SET_BIT(reg, bit)		reg|=(1<<bit)
#define	CLEAR_BIT(reg, bit)		reg&=~(1<<bit)
#define	TOGGLE_BIT(reg, bit)	reg^=(1<<bit)
#define	GET_BIT(reg, bit) 		((reg>>bit)&1)

#endif
