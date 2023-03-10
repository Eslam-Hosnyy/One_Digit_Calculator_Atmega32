/************************************/
/*	Author		: ESLAM_HOSNY		*/
/*	SWC			: CLCD		 		*/
/*	Layer		: HAL				*/
/*	Version   	: 1.0				*/
/*	Date	  	: October 23, 2022	*/
/*	Last Edit 	: N/A				*/
/************************************/

#ifndef _CLCD_INTERFACE_H
#define _CLCD_INTERFACE_H

#define Shift_Left	0
#define Shift_Right	1

void CLCD_voidInit(void);
void CLCD_voidClear(void);
void CLCD_voidGoToXY(u8 ARG_Y, u8 ARG_X);
void CLCD_voidSendCommand (u8 ARG_u8Command);
void CLCD_voidSendData(u8 ARG_u8Data);
void CLCD_voidSendDataXY(u8 ARG_Y, u8 ARG_X,u8 ARG_u8Character);
void CLCD_voidSendString(const char *ARG_u8String);
void CLCD_voidSendStringXY(u8 ARG_Y, u8 ARG_X, const char *ARG_u8String);
void CLCD_voidSendSpecialCharacter(u8 *ARG_u8Pattern, u8 ARG_u8CGRBlockNumber, u8 ARG_Y, u8 ARG_X);
void CLCD_voidWriteNumber(f32 ARG_f32Num);
void CLCD_voidShift_Cursor(u8 ARG_u8Direction);
void CLCD_voidShift_Display(u8 ARG_u8Direction);


#endif
