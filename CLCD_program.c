/************************************/
/*	Author		: ESLAM_HOSNY		*/
/*	SWC			: CLCD		 		*/
/*	Layer		: HAL				*/
/*	Version   	: 1.0				*/
/*	Date	  	: October 23, 2022	*/
/*	Last Edit 	: N/A				*/
/************************************/
#include <util/delay.h>
#include "LSTD_types.h"
#include "LBIT_math.h"
#include "CLCD_config.h"
#include "MDIO_interface.h"
#include "CLCD_interface.h"

void CLCD_voidInit(void)
{

	/* Wait for more 30ms */
	_delay_ms(40);

#if CLCD_MODE==0
	/* Function Set Command: 2 lines, 5*8 Font_Size */
	CLCD_voidSendCommand(0x38);

	/* Function ON OFF Control: Display enable, Disable_Curser, No_Blink */
	CLCD_voidSendCommand(0x0C);

	/* Clear Display */
	CLCD_voidSendCommand(0x01);

#elif CLCD_MODE==1
	/* Function Set Command: 2 lines, 5*8 Font_Size */
	CLCD_voidSendCommand(0x02);
	CLCD_voidSendCommand(0x28);

	/* Function ON OFF Control: Display enable, Disable_Curser, No_Blink */
	CLCD_voidSendCommand(0x0C);

	/* Clear Display */
	CLCD_voidSendCommand(0x06);
	CLCD_voidSendCommand(0x83);


#endif

}

void CLCD_voidClear(void)
{
	CLCD_voidSendCommand(0x01);
	CLCD_voidSendCommand(0x80);
}


void CLCD_voidGoToXY(u8 ARG_Y, u8 ARG_X)
{
	u8 L_u8Address;

	if(0 == ARG_Y)
	{
		L_u8Address = ARG_X;
	}
	else if (1 == ARG_Y)
	{
		L_u8Address = (ARG_X+0x40);
	}
	/* Send Address to DDRAM of LCD */
	CLCD_voidSendCommand(L_u8Address+128);
}


void CLCD_voidSendCommand (u8 ARG_u8Command)
{
	/* Set RS_Pin LOW for Command */
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_RS_PIN, MDIO_LOW);
	/* Set RW_Pin LOW for Write */
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_RW_PIN, MDIO_LOW);

#if CLCD_MODE==0
	/* Send Command for Port */
	MDIO_u8SetPortValue(CLCD_DATAPORT, ARG_u8Command);

	/* Enable E_Pin (Sending Pulse)*/
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_HIGH);
	_delay_ms(2);
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_LOW);

#elif CLCD_MODE==1
	/* Send The Last 4-bits of Command to Port */
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN0, (ARG_u8Command&(0x01<<4))>>4);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN1, (ARG_u8Command&(0x01<<5))>>5);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN2, (ARG_u8Command&(0x01<<6))>>6);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN3, (ARG_u8Command&(0x01<<7))>>7);
	/* Enable E_Pin (Sending Pulse)*/
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_HIGH);
	_delay_ms(2);
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_LOW);

	/* Send The First 4-bits of Command to Port */
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN0, (ARG_u8Command&(0x01<<0))>>0);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN1, (ARG_u8Command&(0x01<<1))>>1);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN2, (ARG_u8Command&(0x01<<2))>>2);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN3, (ARG_u8Command&(0x01<<3))>>3);
	/* Enable E_Pin (Sending Pulse)*/
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_HIGH);
	_delay_ms(2);
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_LOW);
#endif
}


void CLCD_voidSendData(u8 ARG_u8Data)
{
	/* Set RS_Pin HIGH for DATA */
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_RS_PIN, MDIO_HIGH);
	/* Set RW_Pin LOW for Write */
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_RW_PIN, MDIO_LOW);

#if CLCD_MODE==0
	/* Send DATA for Port */
	MDIO_u8SetPortValue(CLCD_DATAPORT, ARG_u8Data);

	/* Enable E_Pin (Sending Pulse)*/
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_HIGH);
	_delay_ms(2);
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_LOW);

#elif CLCD_MODE==1
	/* Masking For The First 4-bits And KEEPING the RS_PIN Is HIGH */
	/* Send The Last 4-bits of DATA to Port */
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN0, (ARG_u8Data&(0x01<<4))>>4);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN1, (ARG_u8Data&(0x01<<5))>>5);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN2, (ARG_u8Data&(0x01<<6))>>6);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN3, (ARG_u8Data&(0x01<<7))>>7);
	/* Enable E_Pin (Sending Pulse)*/
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_HIGH);
	_delay_ms(2);
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_LOW);

	/* Masking For The Last 4-bits And KEEPING the RS_PIN Is HIGH */
	/* Send The First 4-bits of DATA to Port */
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN0, (ARG_u8Data&(0x01<<0))>>0);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN1, (ARG_u8Data&(0x01<<1))>>1);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN2, (ARG_u8Data&(0x01<<2))>>2);
	MDIO_u8SetPinValue(CLCD_DATAPORT, CLCD_DATAPIN3, (ARG_u8Data&(0x01<<3))>>3);
	/* Enable E_Pin (Sending Pulse)*/
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_HIGH);
	_delay_ms(2);
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_LOW);
#endif
}


void CLCD_voidSendDataXY(u8 ARG_Y, u8 ARG_X,u8 ARG_u8Character)
{
	/* Set Local Address For Location */
	u8 L_u8Address;

	if(0 == ARG_Y)
	{
		L_u8Address = ARG_X;
	}
	else if (1 == ARG_Y)
	{
		L_u8Address = (ARG_X+0x40);
	}
	/* Send Address to DDRAM of LCD */
	CLCD_voidSendCommand(L_u8Address+128);

	/* Set RS_Pin LOW for Data */
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_RS_PIN, MDIO_HIGH);
	/* Set RW_Pin LOW for Write */
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_RW_PIN, MDIO_LOW);

	/* Send Data for Port */
	MDIO_u8SetPortValue(CLCD_DATAPORT, ARG_u8Character);

	/*  Enable E_Pin (Sending Pulse) */
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_HIGH);
	_delay_ms(2);
	MDIO_u8SetPinValue(CLCD_CTRLPORT, CLCD_E_PIN, MDIO_LOW);
}

void CLCD_voidSendString(const char *ARG_u8String)
{
	/* Set Local Counter For Characters in String */
	u8 L_u8Counter=0;

	/* Send Every Character */
	while('\0' != ARG_u8String[L_u8Counter])
	{
		CLCD_voidSendData(ARG_u8String[L_u8Counter]);
		L_u8Counter++;
	}
}


void CLCD_voidSendStringXY(u8 ARG_Y, u8 ARG_X, const char *ARG_u8String)
{
	/* Set Local Address For Location */
	u8 L_u8Address;
	/* Set Local Counter For Characters in String */
	u8 L_u8Counter=0;

	if(0 == ARG_Y)
	{
		L_u8Address = ARG_X;
	}
	else if (1 == ARG_Y)
	{
		L_u8Address = (ARG_X+0x40);
	}
	/* Send Address to DDRAM of LCD */
	CLCD_voidSendCommand(L_u8Address+128);

	/* Send Every Character */
	while('\0' != ARG_u8String[L_u8Counter])
	{
		CLCD_voidSendData(ARG_u8String[L_u8Counter]);
		L_u8Counter++;
	}
}


void CLCD_voidSendSpecialCharacter(u8 *ARG_u8Pattern, u8 ARG_u8CGRBlockNumber, u8 ARG_Y, u8 ARG_X)
{
	u8 L_u8CGRAdderess=0,L_u8Iteration;
	/* Calculate The CGRAM_Address whose each Address is 8 bytes */
	L_u8CGRAdderess = ARG_u8CGRBlockNumber*8;

	/* Send Address Command to LCD, with setting bit 6, clearing bit 7 */
	CLCD_voidSendCommand(L_u8CGRAdderess+64);

	/* Write Pattern in CGRAM */
	for(L_u8Iteration=0; L_u8Iteration<8; L_u8Iteration++)
	{
		CLCD_voidSendData(ARG_u8Pattern[L_u8Iteration]);
	}

	/*Go Back to DDRAM And Display */
	CLCD_voidSendDataXY(ARG_Y, ARG_X, ARG_u8CGRBlockNumber);

}


void CLCD_voidWriteNumber(f32 ARG_f32Num)
{
	/* Create counter and Copy of the Number */
	s8 L_s8counter=0, L_s8StartPos=0, L_s8iteration,L_s8Negative=0,L_s8Float=0, L_s8Size=0;
	u32 L_u32copy_Num;


	/*Check if The Number is Negative */
	if(ARG_f32Num<0)
	{
		L_s8Negative=1;
		ARG_f32Num*=(-1);
	}

	/* Trick to Check if The Number If Float */
	L_u32copy_Num=ARG_f32Num;

	if(L_u32copy_Num<ARG_f32Num)
	{
		ARG_f32Num*=1000;
		L_s8Float=1;
	}
	L_u32copy_Num=ARG_f32Num;

	/* Count the Digits in The Number */
	do
	{
		L_u32copy_Num/=10;
		++L_s8counter;

	}while(L_u32copy_Num!=0);

	L_u32copy_Num=ARG_f32Num;

	/* Check the Case To Set The Loops Initializaion */
	if(1==L_s8Float)
	{
		L_s8StartPos=L_s8counter;
		L_s8Size=L_s8counter+1;
		L_s8counter+=1;
	}
	else
	{
		L_s8StartPos=L_s8counter-1;
		L_s8Size=L_s8counter;

	}

	/* Create Array to Store The Digits */
	s8 Array[L_s8Size];

	/* Store The Digits in Reverse */
	for(L_s8iteration=0; L_s8iteration<L_s8Size; L_s8iteration++)
	{
		Array[L_s8StartPos]=(L_u32copy_Num%10);
		/* Push The Dot In Its Place Of The Array */
		if(1==L_s8Float&&2==L_s8iteration)
		{
			L_s8StartPos--;
			Array[L_s8StartPos]='.';
			L_s8Float=0;
		}
		L_u32copy_Num=(L_u32copy_Num/10);
		L_s8StartPos--;
	}
	if(1==L_s8Negative)
		CLCD_voidSendData('-');
	/*Sending Array Ascii_Values(Digits of the Number) To LCD */
	for(L_s8iteration=0; L_s8iteration<L_s8Size; L_s8iteration++)
	{
		/* Print The Dot In Its Place */
		if('.'==Array[L_s8iteration])
			CLCD_voidSendData('.');
		else
			CLCD_voidSendData('0'+Array[L_s8iteration]);
	}

}


void CLCD_voidShift_Cursor(u8 ARG_u8Direction)
{
	/*Check if Shift Cursor Left */
	if(Shift_Left == ARG_u8Direction)
		CLCD_voidSendCommand(0x18);

	/*Check if Shift Cursor Right */
	if(Shift_Right == ARG_u8Direction)
		CLCD_voidSendCommand(0x1C);

}

void CLCD_voidShift_Display(u8 ARG_u8Direction)
{
	/*Check if Shift Display Right */
	if(Shift_Right == ARG_u8Direction)
		CLCD_voidSendCommand(0x07);

	/*Check if Shift Display Left */
	if(Shift_Left == ARG_u8Direction)
		CLCD_voidSendCommand(0x05);

}
