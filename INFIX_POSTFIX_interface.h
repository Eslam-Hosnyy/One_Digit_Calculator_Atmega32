/****************************************/
/*	Author		:	Eslam_Hosny			*/
/*	SWC			:	CLCULATOR			*/
/*	Layer		:	HAL					*/
/*	Version		:	1.0					*/
/*	Date		:	November  8, 2022	*/
/*	Last Edit	:	N/A					*/
/****************************************/

#ifndef _INFIXPOSTFIX_H_
#define _INFIXPOSTFIX_H_


typedef struct stack{
	f16 Entry[20];
	u8 top;
}Stack;

void Stack_voidCreate(Stack *ps);
void Stack_voidPush(f16 ARG_f16e, Stack *ps);
void Stack_voidPop(f16 *ARG_f16pe, Stack *ps);
void Stack_voidTop(f16 *ARG_f16e, Stack *ps);
s8 Stack_s8IsEmpty(Stack *ps);

void Transfer_voidInfix_to_Postfix(s8 infix[], s8 postfix[]);
f16 Transfer_f16EvaluatePostfix(s8 postfix[]);
s8 Transfer_s8IsDigit(s8 ARG_s8Character);
s8 Transfer_s8Precedent(s8 ARG_s8Oprand1, s8 ARG_s8Oprand2);
f16 Transfer_f16Operation(s8 ARG_s8Oprator, f16 ARG_s8Oprand1, f16 ARG_s8Oprand2);
f16 Transfer_f16Power(f16 ARG_s8Oprand1, f16 ARG_s8Oprand2);
s8 Transfer_s8Correct(s8 infix[], s8 L_s8Idx);
void CALCULAT_voidCal();


#endif
