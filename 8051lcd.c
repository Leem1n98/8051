/* LCD Pin
;1:GND
;2:5V
;3:Vo(5V-0.9k-Vo-2.3K-GND)
;4:RS(P2.0)
;5:R/W\(P2.1)
;6:E(P2.2)Low->High->Low
;7:DB0(P0.0)
;8:DB1(P0.1)
;9:DB2(P0.2)
;10:DB3(P0.3)
;11:DB4(P0.4)
;12:DB5(P0.5)
;13:DB6(P0.6)
;14:DB7(P0.7)
;(R/W\,Rs)=(0,0):Data write to LCD Command Register
;(R/W\,Rs)=(0,1):Data write to LCD Data Register
;(R/W\,Rs)=(1,0):Read LCD address(DB6~DB0) and status flag(BF)
;(R/W\,Rs)=(1,1):Read LCD Data
*/
/*
put ir(0x01); DDRAM Data all clear as 0x20(space),Address Counter(AC)=0, cursor move to up-left
put_ir(0x02); DDRAM Data all unchanged, AC=0, cursor move to up-left
put ir(0x03); Same as (0x02)
put ir(0x04); Write data to DDRAM, AC-1, All char not move, cursor shift left-one
put ir(0x05); Write data to DDRAM, AC-1, All char shift right-one, cursor not move
put ir(0x06); Write data to DDRAM, AC+1, All char not move, cursor shift right-one
put ir(0x07); Write data to DDRAM, AC+1, All char shift left-one, cursor not move
put ir(00001DCB); D=1:open LCD, D=0:close LCD; C=1:show cursor, C=0, no cursor; B=1, cursor flash, B=0 cursor not flash
put ir(001LNFxx); L=1:Data 8bit, L=0:Data 4bit; N=1:2-line display, N=0: single-line display; F=1:5x10, F=0:5x7
*/
#include "reg51.h"
#define D0  	0
#define B3b 	1
#define	C4		2
#define	D4		3
#define	E4		4
#define	F4		5
#define	G4b		6
#define	G4		7
#define	A4		8
#define	B4b		9
#define	C5		10
//unsigned char SHOW[]={"TIME"};
//unsigned char *pt=SHOW;
unsigned char lcd[]={'0','1','2','3','4','5','6','7','8','9'};
unsigned char hour1=0, hour0=0, min1=0, min0=0, sec1=0, sec0=0;
unsigned int num=200; //200x5ms=1 second
unsigned char ATEMP, DPLTEMP,DPHTEMP;

void melody(int pitch);
void delay(int s);
void set_lcd();
void put_ir(int cntl_word);
void put_dr(int cntl_word);
void check_busy();
void cursor_home();
void clock();


void main()
{
	int night_dancer[]={
	G4, G4, D0, G4, D0,		//0
	G4b, D0, G4b, D0, D4,	//1
	D0,	C4,	D0, B3b, D0,	//2
	C4, D0, B3b, D0, C4,	//3
	D0, B3b, D0, D4, D4,	//4
	D0, B3b, D0, C4, D0.	//5
	B3b, D0, C4, D0 ,D4,	//6
	D0, F4, D0, D4, D0,		//7
	C4, D0 ,B3b, D0, C4,	//8
	D0, D4, D0 ,D4, D4,		//9
	D0, G4, D0, B4b, D0,	//10
	C4, D0, B3b, D0, G4,	//11
	G4, D0, G4, D0, G4b,	//12
	D0, G4b, D0, D4, D0,	//13
	C4, D0, B3b, D0, A4,	//14
	D0, G4, D0, A4, D0,		//15
	G4, D0, B4b, D0, C5,	//16
	D0, B4b, D0, B3b, D0,	//17
	B3b, D0, B3b, D0, D4,	//18
	D0, F4, D0, C4, D0,		//19
	B3b, B3b, D0, G4, D0	//20
	G4, D0, B4b, D0, C4		//21
	D0, B3b	};
	
	set_lcd();
	cursor_home();

	TMOD = 0xD1; //	SET TIMER0 MODE 1. (11010001B)
	TH0  = (65536-5000)/256; //ECH
	TL0  = (65536-5000)%256;	//00H
	PT0 = 1; //IP.1 SET TIMER0 INTERRUPT HIGH PRIORITY
	TF0=0; //TCON.5 CLEAR TIMER0 OVERFLOW
	TR0=1; //TCON.4 SET TIMER0 RUN
// IE.7(SET ALL INTERRUPT ENABLE);IE.1(ENABLE TIMER0 INTERRUPT)
	IE   = 0x82; // 10000010B
	int i,j,k; 
	char a[]={ 'M', 'e', 'r', 'r', 'y',' ',
				'X', 'm', 'a', 's' };
	while(1)
	{
		for(int T= 0; T<= 112; T++){
			melody(night_dancer[T]);
		}
		if (num == 200)
		{
		 	clock();
		}
	}
}

//******
void melody(int pitch)
{
	switch(pitch){
		case D0:
		for( i=0; i<= 200; i++){
			for( j=0; j<= 250; j++){
				
			}
		}
		break;
		
		case B3b:		//B3b
		for( i=0; i<= 29; i++){
			P1=0x01;
			for( j=0; j<= 8; j++){
				for( k=0; k<= 134; k++){
				}
			}
			P0=0x00;
			for( j=0; j<= 8; j++){
				for( k=0; k<= 134; k++){
				}
			}
		}
		break;
		
		case C4:		//C4
		for( i=0; i<= 33; i++){
			P1=0x01;
			for( j=0; j<= 9; j++){
				for( k=0; k<= 106; k++){
				}
			}
			P0=0x00;
			for( j=0; j<= 9; j++){
				for( k=0; k<= 106; k++){
				}
			}
		}		
		break;
		
		case D4:		//D4
		for( i=0; i<= 37; i++){
			P1=0x01;
			for( j=0; j<= 10; j++){
				for( k=0; k<= 85; k++){
				}
			}
			P0=0x00;
			for( j=0; j<= 10; j++){
				for( k=0; k<= 85; k++){
				}
			}
		}			
		break;
		
		case E4:		//E4
		for( i=0; i<= 41; i++){
			P1=0x01;
			for( j=0; j<= 10; j++){
				for( k=0; k<= 76; k++){
				}
			}
			P0=0x00;
			for( j=0; j<= 10; j++){
				for( k=0; k<= 76; k++){
				}
			}
		}			
		break;
		
		case F4:		//F4	
		for( i=0; i<= 44; i++){
			P1=0x01;
			for( j=0; j<= 4; j++){
				for( k=0; k<= 179; k++){
				}
			}
			P0=0x00;
			for( j=0; j<= 4; j++){
				for( k=0; k<= 179; k++){
				}
			}
		}			
		break;
		
		case G4b:		//G4b
		for( i=0; i<= 46; i++){
			P1=0x01;
			for( j=0; j<= 4; j++){
				for( k=0; k<= 169; k++){
				}
			}
			P0=0x00;
			for( j=0; j<= 4; j++){
				for( k=0; k<= 169; k++){
				}
			}
		}			
		break;
		
		case G4:		//G4
		for( i=0; i<= 49; i++){
			P1=0x01;
			for( j=0; j<= 11; j++){
				for( k=0; k<= 58; k++){
				}
			}
			P0=0x00;
			for( j=0; j<= 11; j++){
				for( k=0; k<= 58; k++){
				}
			}
		}			
		break;
		

		case A4:		//A4
		for( i=0; i<= 55; i++){
			P1=0x01;
			for( j=0; j<= 4; j++){
				for( k=0; k<= 142; k++){
				}
			}
			P0=0x00;
			for( j=0; j<= 4; j++){
				for( k=0; k<= 142; k++){
				}
			}
		}			
		break;
		
		case B4b:		//B4b
		for( i=0; i<= 58; i++){
			P1=0x01;
			for( j=0; j<= 4; j++){
				for( k=0; k<= 134; k++){
				}
			}
			P0=0x00;
			for( j=0; j<= 4; j++){
				for( k=0; k<= 134; k++){
				}
			}
		}			
		break;
		
		case C5:		//C5
		for( i=0; i<= 66; i++){
			P1=0x01;
			for( j=0; j<= 3; j++){
				for( k=0; k<= 159; k++){
				}
			}
			P0=0x00;
			for( j=0; j<= 3; j++){
				for( k=0; k<= 159; k++){
				}
			}
		}			
		break;
			
	}
}



/******************************************************************************
;               USE TIMER0_INT DO POSITION INTERRUPT SERVICE ROUTINE ,TIME=2mS
;******************************************************************************/
void Timer0(void) interrupt 1 using 1
{
	ATEMP  =ACC;
	DPLTEMP=DPL;
	DPHTEMP=DPH;
	TR0=0; // STOP TIMER
	TH0  = (65536-5000)/256;
	TL0  = (65536-5000)%256;
	TR0=1; // TIMER0 TO BE CONTINUE

	num=num-1;
	if (num==0)
	{
		num=200; // 200x5ms = 1 second
		sec0 = sec0+1;
		if (sec0 == 10)
		{
		 	sec0 = 0;
			sec1 = sec1+1;
			if (sec1 == 6)
			{
			 	sec1 = 0;
				min0 = min0+1;
				if (min0 == 10)
				{
				 	min0 = 0;
					min1 = min1+1;
					if (min1 == 6)
					{
					 	min1 = 0;
						hour0 = hour0+1;
						if (hour1==2 && hour0==4)
						{
						 	hour1 = 0;
							hour0 = 0;
						}
						if (hour0 == 10)
						{
						 	hour0 = 0;
							hour1 = hour1+1;
						}
					}
				}
			}
		}
	}

// RETURN:
	ACC=ATEMP;
	DPL=DPLTEMP;
	DPH=DPHTEMP;
}

void delay(int s)
{
	int m; // 16us
	for (m=0;m<s;m++);
}

void set_lcd()
{
	put_ir(0x30); //?
	put_ir(0x06); //?
	put_ir(0x0c); //?
}

void put_ir(int cntl_word)
{
	check_busy();
	P3 = cntl_word;
	P2 = 0x00; // E=0,(R/W\,Rs)=(0,0):Data write to LCD Command Register
	P2 = 0x04; // E=1
	delay(100); // 100x16us
	P2 = 0x00; // E=0,(R/W\,Rs)=(0,0):Data write to LCD Command Register
}

void check_busy()
{
	int busy_flag;
	P2 = 0x02; // (R/W\,Rs)=(1,0):Read LCD address(DB6~DB0) and status flag(BF:DB7)
	P2 = 0x06; // E=1
	delay(100); // 100x16us
READ_AGAIN:
	busy_flag = P0; // Read
	busy_flag &= 0x80; // get BF(DB7)
	if (busy_flag == 0x80)
	{
	 	goto READ_AGAIN;
	}
	else
	{
		P2 = 0x02; // E=0,(R/W\,Rs)=(1,0):Read LCD address(DB6~DB0) and status flag(BF:DB7)
	}
}

void cursor_home()
{
 	put_ir(0x01);
	put_ir(0x02);
}

void put_dr(int data_word)
{
	check_busy();
	P3 = data_word;
	P2 = 0x01; // (R/W\,Rs)=(0,1):Data write to LCD Data Register
	P2 = 0x05; // E=1
	delay(100); // 100x16us
	P2 = 0x01; // E=0,(R/W\,Rs)=(0,1):Data write to LCD Data Register
}

void clock()
{
 	put_ir(0x87);
	put_dr(lcd[sec0]);
	delay(100);

 	put_ir(0x86);
	put_dr(lcd[sec1]);
	delay(100);

 	put_ir(0x85);
	put_dr(':');
	delay(100);

 	put_ir(0x84);
	put_dr(lcd[min0]);
	delay(100);

 	put_ir(0x83);
	put_dr(lcd[min1]);
	delay(100);

 	put_ir(0x82);
	put_dr(':');
	delay(100);

 	put_ir(0x81);
	put_dr(lcd[hour0]);
	delay(100);

 	
	_ir(0x80);
	put_dr(lcd[hour1]);
	delay(100);
}


