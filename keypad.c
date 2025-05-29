#include <LPC21xx.H>

#include "types.h"
#include "lcd_defines.h"
#include "defines.h"
#include "lcd.h"
#include "delay.h"

/* Keypad pin connections */
//rows are connected to P1.16 to P1.19
#define ROW0 16
#define ROW1 17
#define ROW2 18
#define ROW3 19

//cols are connected to P1.20 to P1.23
#define COL0 20
#define COL1 21
#define COL2 22
#define COL3 23


//keypad lookup table
/*
unsigned char keypad_lut[4][4] = {'1','2','3',A,
																	'4','5','6','B',
																	'7','8','9','C',
																	'=','0','#','D'};
*/
unsigned char keypad_lut[4][4] = {'7','8','9','/',
																	'4','5','6','*',
																	'1','2','3','-',
																	'C','0','=','+'};

//u8 rowno[] = {14,13,11,7};																	

void Keypad_Init(void)																	
{
	//configuring the rows port pins as output port pins	
	WRITENIBBLE(IODIR1,ROW0,15);
	//initially making all rows to zero
	//by default zero 
	//initially making all columns to one
	//by default one
}


u32 ColScan(void)
{
	return READNIBBLE(IOPIN1,COL0)<15?0:1;	
}

u32 RowCheck(void)
{
	u32 rNo;
	//row0 identification
	for(rNo=0;rNo<=3;rNo++)
	{
		//WRITENIBBLE(IOPIN1,ROW0,rowno[rNo]);
		WRITENIBBLE(IOPIN1,ROW0,((1<<rNo)^15));
		if(ColScan() == 0)
			break;		
	}
	return rNo;
}

u32 ColCheck(void)
{
	u32 cNo;
	//columns identification process
	for(cNo=0;cNo<=3;cNo++)
	{
		if(READBIT(IOPIN1,(COL0+cNo)) == 0)
			break;
	}	
	return cNo;
}

u32 KeyDetect(void)
{
	u32 rowval,colval;
	
	IOCLR1 = ((1<<ROW0)|(1<<ROW1)|(1<<ROW2)|(1<<ROW3));
	
	//waiting for switch press
	while(ColScan());
	//row identification process
	rowval = RowCheck();
	//columns identification process
	colval = ColCheck();
	//waiting for switch release
	while(!ColScan());
	delay_ms(200);
	return keypad_lut[rowval][colval];	
}

s32 ReadNum(void)
{
	u32 KeyC,num=0,p=1,i=0;
	//CmdLCD(CLEAR_LCD);
	while(1)
	{
		KeyC = KeyDetect();
		if((KeyC>='0') && (KeyC<='9'))
		{p=0;
			i++;
			CharLCD(KeyC);
			num = (num*10) + (KeyC-48);
		}
		else if(KeyC == 'C')//for backspace
		{ 
			if(num>0)
			{p=1;
				i--;
				num = num/10;
				CmdLCD(SHIFT_CUR_LEFT);
				CharLCD(' ');
				CmdLCD(SHIFT_CUR_LEFT);
			}
			else if(i>0){
				p=1;
				i--;
				CmdLCD(SHIFT_CUR_LEFT);
				CharLCD(' ');
				CmdLCD(SHIFT_CUR_LEFT);
			
			}
		}
		else if(KeyC == '=')//for enter
			break;
	}
	if(p && (num==0)&&(i==0))
		return -1;
	
	return num;	
}
s32 PSReadNum(void)
{
	u32 KeyC,num=0,p=1,i=0;
	//CmdLCD(CLEAR_LCD);
	while(1)
	{
		KeyC = KeyDetect();
		if((KeyC>='0') && (KeyC<='9'))
		{  p=0;
			i++;
			CharLCD(KeyC);
			delay_ms(100);
			CmdLCD(0x10);
			CharLCD('*');
			num = (num*10) + (KeyC-48);
		}
		else if(KeyC == 'C')//for backspace
		{
			if(num>0)
			{p=1;
				i--;
				num = num/10;
				CmdLCD(SHIFT_CUR_LEFT);
				CharLCD(' ');
				CmdLCD(SHIFT_CUR_LEFT);
			}
			else if(i>0){
				p=1;
				i--;
				CmdLCD(SHIFT_CUR_LEFT);
				CharLCD(' ');
				CmdLCD(SHIFT_CUR_LEFT);			  
			}
		}
		else if(KeyC == '=')//for enter
			break;
	}
	if(p && (num==0)&&(i==0))
		return -1;
	return num;	
}
