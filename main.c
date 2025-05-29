#include <LPC21xx.H>
#include "delay.h"
#include "lcd.h"
#include "defines.h"
#include "rtc.h"
#include "keypad.h"

#define SW1 19//P0.19
#define SW2 20//P0.20

#define BUZZER  0//P0.0

//rtc time variable
u32 hour,min,sec,day,date,month,year,x;

// store morning,afternoon,evening time value
int arr[3][7]={{8,14,10},{1,14,15},{20,14,20}};

//display current time
void display_time()
{
    CmdLCD(0x80);
	  StrLCD("----CURRENT TIME----");
		RTCGetTime(&hour,&min,&sec);		
		DisplayRTCTime(hour,min,sec);
		RTCGetDate(&date,&month,&year);
	  DisplayRTCDate(date,month,year);
		RTCGetDay(&day);
		DisplayRTCDay(day);

}
//display madicine time
void display_medi_time(int i)
{
	int hr,mi,se; 
	CmdLCD(0x01);	
	StrLCD("------MEDICINE------");
	
	CmdLCD(0XC0);
  
	if((i==0))
	{
		  StrLCD("MORNING TIME ");
		  CmdLCD(0x94);
	    hr=arr[0][0];mi=arr[0][1];se=arr[0][2];
  		CharLCD((hr/10)+48);
    	CharLCD((hr%10)+48);
	    CharLCD(':');
	    CharLCD((mi/10)+48);
			CharLCD((mi%10)+48);
			CharLCD(':');
	    CharLCD((se/10)+48);
	    CharLCD((se%10)+48);	
	}
  else if(i==1)
	{
			StrLCD("AFTERNOON TIME ");
			CmdLCD(0x94);
			hr=arr[1][0];mi=arr[1][1];se=arr[1][2];
			CharLCD((hr/10)+48);
			CharLCD((hr%10)+48);
			CharLCD(':');
			CharLCD((mi/10)+48);
			CharLCD((mi%10)+48);
			CharLCD(':');
			CharLCD((se/10)+48);
			CharLCD((se%10)+48);	
	  
	}
	else if(i==2)
	{
			StrLCD("EVENING TIME ");
			CmdLCD(0x94);
			hr=arr[2][0];mi=arr[2][1];se=arr[2][2];
			CharLCD((hr/10)+48);
			CharLCD((hr%10)+48);
			CharLCD(':');
			CharLCD((mi/10)+48);
			CharLCD((mi%10)+48);
			CharLCD(':');
			CharLCD((se/10)+48);
			CharLCD((se%10)+48);		   
	}
}
//check time is medicine time or not
int check()
{
			if((arr[0][0]==hour)&&(arr[0][1]==min)&&(arr[0][2]==sec))
			{
						return 1;
			}
			else if((arr[1][0]==hour)&&(arr[1][1]==min)&&(arr[1][2]==sec))
			{
					return 2;
			}
			else if((arr[2][0]==hour)&&(arr[2][1]==min)&&(arr[2][2]==sec))
			{
					return 3;
			}
			return 0;

}
//display which value you want to modify
void display(int ed)
{
            if(ed=='1')
						{
						StrLCD("HOUR--> ");
						}
						else if(ed=='2')
						{
						StrLCD("MINUTE--> ");
						}
						else if(ed=='3')
						{
						StrLCD("SECOND--> ");
						}
						else if(ed=='4')
						{
						StrLCD("DATE--> ");
						}
						else if(ed=='5')
						{
						StrLCD("MONTH--> ");
						}
						else if(ed=='6')
						{
						StrLCD("YEAR--> ");
						}
						else if(ed=='7')
						{
						StrLCD("DAY--> ");
						}
					
}
//current time editing..
void time_editing()
{
   	int ed,p;
		CmdLCD(0x01);
    while(1)
		{ //dispaly menu
		 	CmdLCD(0x01);
			StrLCD("1.HOUR   2.MINUTE");
			CmdLCD(0xc0);
			StrLCD("3.SECOND 4.DATE");
			CmdLCD(0X94);
			StrLCD("5.MONTH  6.YEAR");
			CmdLCD(0XD4);
			StrLCD("7.DAY    8.EXIT");
			ed=KeyDetect();
			//check if any key press or not b/w 1 to 8
		  if(((ed>='1')&&(ed<='8')))
			{  
				 //exit if 8 press
			   if(ed=='8')
				 { 
						return;
				 }
				 else
				 {
					CmdLCD(0x01);
					//dispaly current time
					display_time();
					CmdLCD(0xd4);
					while(1){	
						   //display which thing you want to modify
						   display(ed);
						   //read the value of time parameter
						   p=ReadNum();
						   //if invalid input than true this condition
						   if(((ed=='1')&&((p>23)||(p<0)))||((ed=='2')&&((p>59)||(p<0)))||((ed=='3')&&((p>59)||(p<0)))||((ed=='4')&&((p>31)||(p<1)))||((ed=='5')&&((p>12)||(p<1)))||
								 ((ed=='6')&&((p<1)||(p>2026)))||((ed=='7')&&((p>7)||(p<1))))
							 {
									 CmdLCD(0xd4);
								   StrLCD("INCORRECT INPUT...");
									 delay_ms(500);									 
									 break;
							}
					  	else if(ed=='1')
							{ //hour value you want to change
							   hour=p;
								 RTCSetTime(hour,min,sec);	
							   break;
						  }
						  else if(ed=='2')
							{  //minute value you want to change
							   min=p;
						     RTCSetTime(hour,min,sec);	
							   break;
						  }
						  else if(ed=='3')
						  {  //second value you want to change
						     sec=p;
							   RTCSetTime(hour,min,sec);	
							   break;
						  }
						  else if(ed=='4')
							{  //date value you want to change
							   date=p;
							   RTCSetDate(date,month,year);
							   break;
						  }
						  else if(ed=='5')
							{//month value you want to change
							   month=p;
						     RTCSetDate(date,month,year);
							   break;
					   	}
						  else if(ed=='6')
							{ //year value you want to change
							   year=p;
						     RTCSetDate(date,month,year);
							   break;
						  }
						  else if(ed=='7')
							{  //day value you want to change
							   day=p-1;
								 RTCSetDay(day);
							   break;
	 					  }	 				
					}
				}
			}
		}			

}
//medicine time edit
void medicine_editing(){
  int ed,k,m1,i,p,c=0;
	CmdLCD(0X01);
	StrLCD("------PASSWORD------");
	CmdLCD(0XC8);
	//for enter the password..
	k=PSReadNum();
	CmdLCD(0x94);
	//password not matched...
	if(k!=123)
	{
	   StrLCD("INVALID INPUT...");
		 delay_ms(500);	 
		 return;
	}
	else{
		 //password match;
		 c=0;
		 StrLCD("ACCESS GRANTED...");
		 delay_ms(500);
	   CmdLCD(0x01);
  	 StrLCD("1.MORNING MEDICINE ");
  	 CmdLCD(0xc0);
		 StrLCD("2.AFTERNOON MEDICINE ");
		 CmdLCD(0x94);
		 StrLCD("3.NIGHT MEDICINE ");
		 CmdLCD(0xd4);
  	 StrLCD("4.EXIT     -> ");
		 while(1)
		 {  //which time you want to modify
				m1=ReadNum();
				if(m1>0 && m1<5)
				{
					 if(m1==4)
					 {//exit
						 	c=1;
							break;
					 }
					 else
					 {
							i=m1-1;
							break;
					 }
				}
				else
				{
									  CmdLCD(0xe2);
										StrLCD("       ");
										CmdLCD(0xe2);
				}
										
		}
		if(c)
		{  //exit return there
			  return;
		}
	}
			
	CmdLCD(0x01);
	while(1)
	{   //display which value you want to change
			CmdLCD(0x01);
			StrLCD("1.HOUR ");
			CmdLCD(0xc0);
			StrLCD("2.MINUTE ");
			CmdLCD(0X94);
			StrLCD("3.SECOND ");
			CmdLCD(0XD4);
			StrLCD("4.EXIT ");
			ed=KeyDetect();
		  //check the correct input b/w 1 to 4
		  if(((ed>='1')&&(ed<='4')))
			{  //exit value is 4
			   if(ed=='4')
				 { 
				   break;
				 }
			   else
				 {
		  		 CmdLCD(0x01);
					 //diaplay previous medicine time of i index present
					 display_medi_time(i);
					 CmdLCD(0xd4);
					 while(1)
					 {  //dispay you want to change
						   display(ed);
						  //read new value time parameter
						   p=ReadNum();
						   
						 // incorrect input...
						   if(((ed=='1')&&((p>23)||(p<0)))||((ed=='2')&&((p>59)||(p<0)))||((ed=='3')&&((p>59))||(p<0)))
							 {
									 CmdLCD(0xd4);
								   StrLCD("INCORRECT INPUT...");
									 delay_s(1);									 
									 break;
							}
					  	else if(ed=='1')
							{  //hour value you want to change
							   arr[i][0]=p;
								 break;
						  }
						  else if(ed=='2')
							{  //minute value you want to change
							   arr[i][1]=p;
						     break;
						  }
						  else if(ed=='3')
							{  //second value you want to change
						     arr[i][2]=p;
							   break;
						  }
	 			  }	 				
		 	 }					 
		}
	}
}

void edit_mode(){
	int key;
  CmdLCD(0x01);
	while(1)
	{  //dispay menu of editing
			CmdLCD(0x01);
		  StrLCD("--------EDIT----------");
		  CmdLCD(0XC0);
		  StrLCD("1.CURRENT TIME ");
			CmdLCD(0x94);
			StrLCD("2.MEDICINE TIME ");
			CmdLCD(0xD4);
			StrLCD("3.EXIT");
		  key=KeyDetect();	
      if(key=='3')
		  {   //exit
			  	break;
			}			
			else if(key=='2')
			{ //for medicine time edit
				medicine_editing();			
			}
			else if(key=='1')
			{//for current time value editing
				time_editing();			
			}				
	}
		
}

int main(){
//intialised all parameter
		IODIR0 |= (1<<0);
  	InitLCD();
	  CmdLCD(0x0c);
	  RTC_Init();
		Keypad_Init();
	  
// rtc set tme intial
    RTCSetTime(8,14,0);
  	RTCSetDate(29,5,2025);
  	RTCSetDay(3);
	
	  while(1)
		{
			 //display current time
	     display_time();
			 //check the medicine time
		   x=check();
			 //for edit mode open SW1/p0.19
		   if(READBIT(IOPIN0,SW1))
			 {
		      edit_mode();
			    CmdLCD(0x01);
		   }
		   else if(x)
			 {   
			    CmdLCD(0x01);	
          //display medicine time				 
			    display_medi_time((x-1)); 
					CmdLCD(0xd4);
					StrLCD("TAKE MEDICINE...");   		
		      while(1)
					{
						  //buzzer on off using rtc 
						  RTCGetTime(&hour,&min,&sec);	
						  if(sec%2){
								SCLRBIT(IOCLR0,BUZZER);
							}
							else{
								SSETBIT(IOSET0,BUZZER);
							}
						 //if SW2-p0.20 to off buzzer
					    if(READBIT(IOPIN0,SW2))
						  {
							    break;
						  }						 
				 }
				 CmdLCD(0x01);
			}
	}
	
}










