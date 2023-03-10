/****************************************/
/*	Author		:	ESLAM_HOSNY			*/
/*	SWC			:	DIO					*/
/*	Layer		:	MCAL				*/
/*	Version		:	1.1					*/
/*	Date		:	October  08,2022	*/
/*	Last Edit	:	October  26,2022	*/
/****************************************/

#ifndef	_MDIO_INTERFACE_H_
#define	_MDIO_INTERFACE_H_

#define PIN0		0
#define PIN1		1
#define PIN2		2
#define PIN3		3
#define PIN4		4
#define PIN5		5
#define PIN6		6
#define PIN7		7

#define	MDIO_PORTA	1
#define	MDIO_PORTB	4
#define	MDIO_PORTC	19
#define	MDIO_PORTD	97

#define	MDIO_OUTPUT	1
#define	MDIO_INPUT	0
#define MDIO_LOW	0
#define MDIO_HIGH	1

u8 MDIO_u8SetPortValue (u8 ARG_u8Port, u8 ARG_u8Value);
u8 MDIO_u8GetPortValue (u8 ARG_u8Port, u8 *L_u8ReturnValue);
u8 MDIO_u8SetPinValue (u8 ARG_u8Port, u8 ARG_u8Pin, u8 ARG_u8Value);
u8 MDIO_u8GetPinValue (u8 ARG_u8Port, u8 ARG_u8Pin, u8 *L_u8ReturnValue);

#endif
