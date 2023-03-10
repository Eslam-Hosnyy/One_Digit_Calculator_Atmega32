/************************************/
/*	Author		: ESLAM_HOSNY		*/
/*	SWC			: KeyPad	 		*/
/*	Layer		: HAL				*/
/*	Version   	: 1.0				*/
/*	Date	  	: October 27, 2022	*/
/*	Last Edit 	: N/A				*/
/************************************/

#include "LSTD_types.h"
#include "MDIO_interface.h"
#include "KPD_config.h"
#include "KPD_private.h"
#include "KPD_interface.h"

u8 KPD_u8PressedKey(void)
{
    u8 L_u8PressedKey = NO_PRESSED_KEY, L_u8ColumnIdx, L_u8RowIdx, L_u8PinState=MDIO_HIGH;

    static u8 L_u8Arr[ROW_NUM][COLUMN_NUM] = KPD_ARRAY_VAL;
    static u8 L_u8ColumnArr[COLUMN_NUM]= {KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
    static u8 L_u8RowArr[ROW_NUM]= {KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};

    for(L_u8ColumnIdx=0; L_u8ColumnIdx<COLUMN_NUM; L_u8ColumnIdx++)
    {
        /*Activate The Current Column*/
        MDIO_u8SetPinValue(KPD_PORT,L_u8ColumnArr[L_u8ColumnIdx],MDIO_LOW);

        for(L_u8RowIdx=0; L_u8RowIdx<ROW_NUM; L_u8RowIdx++)
        {
          /*Read The Current Row*/
          MDIO_u8GetPinValue(KPD_PORT,L_u8RowArr[L_u8RowIdx],&L_u8PinState);

          /*Check if Pressed Key*/
          if(MDIO_LOW==L_u8PinState)
          {
        	  L_u8PressedKey=L_u8Arr[L_u8RowIdx][L_u8ColumnIdx];

              /*Polling(Busy_Wait) Until The Key is Released*/
              while(MDIO_LOW==L_u8PinState)
              {
                  MDIO_u8GetPinValue(KPD_PORT,L_u8RowArr[L_u8RowIdx],&L_u8PinState);
              }

              return L_u8PressedKey;
          }
        }
        /*Deactivate The Current Column*/
        MDIO_u8SetPinValue(KPD_PORT,L_u8ColumnArr[L_u8ColumnIdx],MDIO_HIGH);
    }

    return L_u8PressedKey;
}


u8 KPD_u8PressedKey_2(void)
{
	u8 L_u8PressedKey = NO_PRESSED_KEY, L_u8RowIdx, L_u8ColumnIdx, L_u8PinState;
	static u8 L_u8Arr[ROW_NUM][COLUMN_NUM] = KPD_ARRAY_VAL;
	MDIO_u8SetPortValue(KPD_PORT, 0xFF);
	
	while(1)
	{
		for(L_u8RowIdx=0; L_u8RowIdx<4; L_u8RowIdx++)
		{
			MDIO_u8SetPortValue(KPD_PORT, ((~(1<<L_u8RowIdx<<4)) | 0x0F));
			
			L_u8ColumnIdx = ~MDIO_u8GetPortValue(KPD_PORT,&L_u8PinState) & 0x0F;
			
			if(0 != L_u8ColumnIdx)
			{
				break;
			}
		}
		
		if(L_u8RowIdx < 4)
		{
			break;
		}
	}
	
	switch(L_u8ColumnIdx)
	{
		case 1: L_u8ColumnIdx = 3; break;
		case 2: L_u8ColumnIdx = 2; break;
		case 4: L_u8ColumnIdx = 1; break;
		case 8: L_u8ColumnIdx = 0; break;
		default: L_u8ColumnIdx = 4; break;
	}
	
	L_u8PressedKey=L_u8Arr[L_u8RowIdx][L_u8ColumnIdx];
	
	return L_u8PressedKey;
}
