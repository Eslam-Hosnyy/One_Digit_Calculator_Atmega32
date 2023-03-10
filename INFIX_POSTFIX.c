/****************************************/
/*	Author		:	Eslam_Hosny			*/
/*	SWC			:	CLCULATOR			*/
/*	Layer		:	HAL					*/
/*	Version		:	1.0					*/
/*	Date		:	November  8, 2022	*/
/*	Last Edit	:	N/A					*/
/****************************************/
#include "LSTD_types.h"
#include "INFIX_POSTFIX_config.h"
#include "INFIX_POSTFIX_interface.h"
#include "KPD_interface.h"
#include "CLCD_interface.h"

/**************** STACK_IMPLEMENTATION ******************/

/* Create and Intilization of Stack */
void Stack_voidCreate(Stack *ps)
{
	ps->top=0;
}

/* PUSH Function For Storing Characters */ 
void Stack_voidPush(f16 ARG_f16e, Stack *ps)
{
	if(ps->top != 20)
		ps->Entry[ps->top++]=ARG_f16e;
}

/* POP Function for Getting the Result (Larger Than 8-bits) From The Stack */ 
void Stack_voidPop(f16 *ARG_f16pe, Stack *ps)
{
	if(ps->top != 0)
		*ARG_f16pe=ps->Entry[--ps->top];
}

/* Top Function for Getting the Last Entered Element of The Stack */ 
void Stack_voidTop(f16 *ARG_f16e, Stack *ps)
{
	if(ps->top != 0)
		*ARG_f16e=ps->Entry[ps->top-1];
}

/* Check if the Stack is Empty */
s8 Stack_s8IsEmpty(Stack *ps)
{
	return ps->top==0;
}

/**************** INFIX_POSTFIX IMPLEMENTATION *********/

/* Function of Transfering The Infix String To Postfix */ 
void Transfer_voidInfix_to_Postfix(s8 infix[], s8 postfix[])
{
	s8 L_s8Iteration1, L_s8Iteration2=0;
	f16 L_s8Operator, L_s8Charcter;
	Stack S;
	Stack_voidCreate(&S);

	/* Loop for each Character in the Stack until the end of Stack */ 
	for(L_s8Iteration1=0; (L_s8Charcter=infix[L_s8Iteration1])!='\0'; L_s8Iteration1++)
		if(Transfer_s8IsDigit(L_s8Charcter))		//Check if digit or operator
		{
			postfix[L_s8Iteration2++]=L_s8Charcter;
		}
		else
		{
			if(!Stack_s8IsEmpty(&S))	//Check If Stack not Empty
			{
				Stack_voidTop(&L_s8Operator, &S);  //Get the top operator (the Biggest Precedent)

				/*Compere Between The Current Operator And the Top operator of The Stack */
				while(!Stack_s8IsEmpty(&S) && Transfer_s8Precedent(L_s8Operator,L_s8Charcter))
				{
					/* Adding the operators to the Postfix String */
					Stack_voidPop(&L_s8Operator,&S);
					postfix[L_s8Iteration2++]=L_s8Operator;
					if(!Stack_s8IsEmpty(&S))
						Stack_voidTop(&L_s8Operator,&S);
				}
			}
			/* Adding the Operator to the Stack After Poping all the least precedent */
			Stack_voidPush(L_s8Charcter,&S);
		}
	/*After Finshing Check if there are any operator still in the Stack and poping it to the postfix */
	while(!Stack_s8IsEmpty(&S))
	{
		Stack_voidPop(&L_s8Operator,&S);
		postfix[L_s8Iteration2++]=L_s8Operator;
	}
	postfix[L_s8Iteration2]='\0';
}

/* Function to Evaluate The Postfix */
f16 Transfer_f16EvaluatePostfix(s8 postfix[])
{
	s8 L_s8Iteration;
	f16 L_f16Value,L_s8Charcter,L_s8Operand1, L_s8Operand2;
	Stack S;
	Stack_voidCreate(&S);

	/* Loop for each Character in the Stack until the end of Stack */ 
	for(L_s8Iteration=0; (L_s8Charcter=postfix[L_s8Iteration])!='\0'; L_s8Iteration++)
		if(Transfer_s8IsDigit(L_s8Charcter))		//Check If current Character is digit or Operator */
			Stack_voidPush((f16)(L_s8Charcter-'0'),&S); //Push the digit to Stack after Casting to f32 */
		else
		{
			/* IF Operator ,So Get The Two Operands of it */
			Stack_voidPop(&L_s8Operand2,&S);
			Stack_voidPop(&L_s8Operand1,&S);
			/* Passing the Two Operands and the Operator To Operation Function */
			L_f16Value=Transfer_f16Operation(L_s8Charcter,L_s8Operand1,L_s8Operand2);
			if(0xff==L_f16Value)
				break;
			/* Push The Result of the Operation in the stack (It will be the oprand of the next Operation) */
			Stack_voidPush(L_f16Value,&S);
		}

	/*Return the Final Result */
	if(0xff==L_f16Value)
		return L_f16Value;
	else
	{
	Stack_voidPop(&L_f16Value,&S);
	return L_f16Value;
	}
}

/* Function Of Checking The Current Character is Digit or Operator */
s8 Transfer_s8IsDigit(s8 ARG_s8Character)
{
	return (ARG_s8Character>='0' && ARG_s8Character<='9');
}

/* Function of Compere Between Two Operands */
s8 Transfer_s8Precedent(s8 ARG_s8Oprand1, s8 ARG_s8Oprand2)
{
	//if(ARG_s8Oprand1=='$') return 1;

	if((ARG_s8Oprand1=='*') || (ARG_s8Oprand1=='/'))
		return (ARG_s8Oprand2 != '$');

	if((ARG_s8Oprand1=='+') || (ARG_s8Oprand1=='-'))
		return ((ARG_s8Oprand2 != '*') && (ARG_s8Oprand2 != '/'));

	return 0;
}

/* Function of Calculate some of Mathmatical operations */
f16 Transfer_f16Operation(s8 ARG_s8Oprator, f16 ARG_f16Oprand1, f16 ARG_f16Oprand2)
{
	f16 result;
	switch(ARG_s8Oprator)
	{
	case '+':
	{result= (ARG_f16Oprand1+ARG_f16Oprand2); break;}
	case '-':
	{result= (ARG_f16Oprand1-ARG_f16Oprand2); break;}
	case '*':
	{result= (ARG_f16Oprand1*ARG_f16Oprand2); break;}
	case '/':
	{
		if(0==ARG_f16Oprand2)
		{result=0xff; break;}
		else
		{result= ((ARG_f16Oprand1)/(ARG_f16Oprand2+0.0)); break;}
	}
	/*case '$':
	{result=(Transfer_f16Power(ARG_s8Oprand1,ARG_s8Oprand2)); break;}*/
	}

	return result;
}

/* Function of Getting The Power */
f16 Transfer_f16Power(f16 ARG_f16Oprand1, f16 ARG_f16Oprand2)
{
	f16 ARG_Copy,result=1;
	for(ARG_Copy=ARG_f16Oprand2; ARG_Copy>0; ARG_Copy--)
	{
		result=result*ARG_f16Oprand1;
	}
	return result;
}

/*Function To Correct The Probabilty Of Wrong (In the Case of ReEenter The Value) */
s8 Transfer_s8Correct(s8 infixx[], s8 L_s8Idxx)
{
	s8 L_s8Correct=0;
	if('+'==infixx[L_s8Idxx-1] || '-'==infixx[L_s8Idxx-1])
		L_s8Correct=(0+'0');
	else if('*'==infixx[L_s8Idxx-1] || '/'==infixx[L_s8Idxx-1])
		L_s8Correct=(1+'0');

	return L_s8Correct;
}

/*Function of taking Characters From user by Keypad
 * And Doing Infix_to_Postfix Operation
 * And Display The Result on LCD
 */
void CALCULAT_voidCal()
{
	u8 L_u8key;
	s8 L_s8Idx=0, infix[INFIX_SIZE]={'0','+','0'}, postfix[POSTFIX_SIZE];
	f16 L_f16Result;

	CLCD_voidSendStringXY(0, 4, "WELLCOME");
	CLCD_voidSendStringXY(1, 1, "ONE_DIGIT_CALC");
	while(1)
	{
		do
		{
			L_u8key=KPD_u8PressedKey(); //Take The Value From User by Keypad

		}while(0xff==L_u8key);  //While NO_Pressed Key ,Check Again
		if(L_u8key!=0xff && L_s8Idx==0)
			CLCD_voidClear();

		if('#'==L_u8key)
		{
			/*Correct The Inadvertent Error Befor Calculate The Result*/
			infix[L_s8Idx]=Transfer_s8Correct(infix, L_s8Idx);
			/*Convert The Infix To Postfix And Evaluate The Postfix */
			Transfer_voidInfix_to_Postfix(infix,postfix);
			L_f16Result=Transfer_f16EvaluatePostfix(postfix);
			if(0xff==L_f16Result)
				CLCD_voidSendStringXY(1, 0,"Result=ERROR");
			else
			{
				CLCD_voidSendStringXY(1, 0,"Result=");
				CLCD_voidWriteNumber(L_f16Result);		//Send The Value To LCD
			}
			do
			{
				L_u8key=KPD_u8PressedKey();

			}while('#'!=L_u8key);	//Wait Until The User Press '#' To Repet The Opreation
			CLCD_voidClear();
			CALCULAT_voidCal();		//Recursion OF This Function

		}
		else if('C'==L_u8key)		/*ReEnter The Last Number (To Correct The Enterd-Value) */
		{
			L_s8Idx--;
			CLCD_voidGoToXY(0, L_s8Idx);
			CLCD_voidSendData(' ');
			CLCD_voidGoToXY(0, L_s8Idx);
			/*Correct The Inadvertent Error*/
			infix[L_s8Idx]=Transfer_s8Correct(infix, L_s8Idx);
		}
		else					//Store The Value to The Infix-Array And Display This on LCD
		{
			/*Check The Wrong of Entering more than one Operator or Digit (Not Accepted Input) */
			if(!Transfer_s8IsDigit(L_u8key) && !Transfer_s8IsDigit(infix[L_s8Idx-1]))
				continue;
			if((Transfer_s8IsDigit(L_u8key) && Transfer_s8IsDigit(infix[L_s8Idx-1])) && 0!=L_s8Idx)
				continue;
			else 				//Store The Value In in Infix
			{
				if(15==L_s8Idx)
					continue;
				else
				{
					infix[L_s8Idx]=L_u8key;
					CLCD_voidSendData(infix[L_s8Idx]);
					L_s8Idx++;
				}
			}
		}
	}
}
