/************************************/
/*	Author		: ESLAM_HOSNY		*/
/*	SWC			: DIO     			*/
/*	Layer		: MCAL				*/
/*	Version   	: 1.1				*/
/*	Date	  	: October 7, 2022	*/
/*	Last Edit 	: October 26, 2022	*/
/************************************/

#ifndef	_MDIO_PRIVATE_H_
#define	_MDIO_PRIVATE_H_

#define	GPIOA_PIN   *((volatile u8*)0x39)
#define	GPIOB_PIN   *((volatile u8*)0x36)
#define	GPIOC_PIN   *((volatile u8*)0x33)
#define	GPIOD_PIN   *((volatile u8*)0x30)

#define	GPIOA_PORT  *((volatile u8*)0x3B)
#define	GPIOB_PORT  *((volatile u8*)0x38)
#define	GPIOC_PORT  *((volatile u8*)0x35)
#define	GPIOD_PORT  *((volatile u8*)0x32)


#endif
