/************************************/
/*	Author		: ESLAM_HOSNY		*/
/*	SWC			: DIO     			*/
/*	Layer		: MCAL				*/
/*	Version   	: 1.1				*/
/*	Date	  	: October 08,2022	*/
/*	Last Edit 	: October 26,2022	*/
/************************************/

#include "LSTD_types.h"
#include "LBIT_math.h"
#include "MDIO_private.h"
#include "MDIO_interface.h"

u8 MDIO_u8SetPortValue (u8 ARG_u8Port , u8 ARG_u8Value)
{
	u8 L_u8ErrorState=0;
	switch (ARG_u8Port)
	{
		case MDIO_PORTA: GPIOA_PORT = ARG_u8Value; break;
		case MDIO_PORTB: GPIOB_PORT = ARG_u8Value; break;
		case MDIO_PORTC: GPIOC_PORT = ARG_u8Value; break;
		case MDIO_PORTD: GPIOD_PORT = ARG_u8Value; break;
		default : L_u8ErrorState=1 ;break; // Report Error
		}
	return L_u8ErrorState;
}


u8 MDIO_u8SetPinValue (u8 ARG_u8Port , u8 ARG_u8Pin , u8 ARG_u8Value)
{
	u8 L_u8ErrorState=0;
	if (7>=ARG_u8Pin && 0<=ARG_u8Pin)
	{
		if (MDIO_LOW==ARG_u8Value)
		{
			switch(ARG_u8Port)
			{
				case MDIO_PORTA : CLEAR_BIT(GPIOA_PORT, ARG_u8Pin); break;
				case MDIO_PORTB : CLEAR_BIT(GPIOB_PORT, ARG_u8Pin); break;
				case MDIO_PORTC : CLEAR_BIT(GPIOC_PORT, ARG_u8Pin); break;
				case MDIO_PORTD : CLEAR_BIT(GPIOD_PORT, ARG_u8Pin); break;
				default : L_u8ErrorState=1; break;
			}
		}
		else if (MDIO_HIGH==ARG_u8Value)
		{
			switch(ARG_u8Port)
			{
				case MDIO_PORTA : SET_BIT(GPIOA_PORT, ARG_u8Pin); break;
				case MDIO_PORTB : SET_BIT(GPIOB_PORT, ARG_u8Pin); break;
				case MDIO_PORTC : SET_BIT(GPIOC_PORT, ARG_u8Pin); break;
				case MDIO_PORTD : SET_BIT(GPIOD_PORT, ARG_u8Pin); break;
				default : L_u8ErrorState=1; break;
			}
		}
		else
		{
			L_u8ErrorState=1;
		}
	}
	else
	{
		L_u8ErrorState=1;
	}
	return L_u8ErrorState;
}


u8 MDIO_u8GetPortValue (u8 ARG_u8Port, u8 *L_u8ReturnValue)
{
	u8 L_u8ErrorState;
	switch(ARG_u8Port)
	{
		case MDIO_PORTA	: *L_u8ReturnValue = GPIOA_PIN; break;
		case MDIO_PORTB	: *L_u8ReturnValue = GPIOB_PIN; break;
		case MDIO_PORTC	: *L_u8ReturnValue = GPIOC_PIN; break;
		case MDIO_PORTD	: *L_u8ReturnValue = GPIOD_PIN; break;
		default : L_u8ErrorState = 1; break;
	}
	return L_u8ErrorState;
}


u8 MDIO_u8GetPinValue (u8 ARG_u8Port , u8 ARG_u8Pin, u8 *L_u8ReturnValue)
{
	u8 L_u8ErrorState;
	switch(ARG_u8Port)
	{
		case MDIO_PORTA	: *L_u8ReturnValue = GET_BIT(GPIOA_PIN , ARG_u8Pin); break;
		case MDIO_PORTB	: *L_u8ReturnValue = GET_BIT(GPIOB_PIN , ARG_u8Pin); break;
		case MDIO_PORTC	: *L_u8ReturnValue = GET_BIT(GPIOC_PIN , ARG_u8Pin); break;
		case MDIO_PORTD	: *L_u8ReturnValue = GET_BIT(GPIOD_PIN , ARG_u8Pin); break;
		default : L_u8ErrorState = 1; break;
	}
	return L_u8ErrorState;
}


