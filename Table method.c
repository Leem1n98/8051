/*
B3b	233Hz T/2= 2415= 8*268
C4  262Hz T/2= 1908= 8*238
D4	294Hz T/2= 1700= 8*212
E4	329Hz T/2= 1520= 8*190
F4	349Hz T/2= 1432= 8*179
G4b 370Hz T/2= 1351= 8*169
G4  392Hz T/2= 1275= 8*159
A4  440Hz T/2= 1136= 8*142
B4b 466Hz T/2= 1073= 8*134
B4 494Hz T/2= 1012= 8*142
C5  523Hz T/2=  954= 8*119

*/
#include"reg51.h"

unsigned int num=200; //200x5ms=1 second
unsigned char ATEMP, DPLTEMP,DPHTEMP;

void delay(int s);
void set_lcd();
void put_ir(int cntl_word);
void put_dr(int cntl_word);
void check_busy();
void cursor_home();

void main()
{	/*short  unsigned int night_dancer[112]={
	G4, G4, D0, G4, D0,		//0
	G4b, D0, G4b, D0, D4,	//1
	D0,	C4,	D0, B3b, D0,	//2
	C4, D0, B3b, D0, C4,	//3
	D0, B3b, D0, D4, D4,	//4
	D0, B3b, D0, C4, D0,	//5
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
	B3b, B3b, D0, G4, D0,	//20
	G4, D0, B4b, D0, C4,	//21
	D0, B3b	};
*/
	unsigned char song[]=  {18,6,5,5,2,1,0,1,0,1,0,14,0,1,0,1,2,4,2,1,0,1,2,14,6,8,1,0,8,18,6,5,5,2,1,0,7,6,8,10,8,0,0,0,2,4,1,11,6,6,8,1,0};
	unsigned char dtime[]= { 58, 65, 73, 82, 87, 92, 98,110,116,123,131,     116,123,131,146,164,174,184,196,220,232,246,262};
	unsigned char mdelay[]={268,238,212,190,179,169,159,142,134,126,119,     268,253,238,212,190,179,169,159,142,134,126,119};
						/*	B3b, C4, D4, E4, F4,G4b, G4, A4,B4b, B4, C5,long B3b, B4, C4, D4, E4, F4, G4b, G4, A4,B4b,B4, C5 */
						/*    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,      11, 12, 13, 14, 15, 16,  17, 18, 19, 20,21, 22 */   
	unsigned char count; 
	unsigned char n;
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
	while(1)
	{
		for(count=0; count<=53; count++){
			for(n=0; n<=dtime[song[mdelay]]; n++){
				P1=0x01;
				delay(mdelay[song[count]]);
				P1=0x00;
				delay(mdelay[song[count]]);
			}
			delay(1000);
		}
	/*
		if (num == 200)
		{
		 	clock();
		}
	*/
	}
}

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
void delay(unsigned char s)
{
	unsigned char m;
	for(m=0;m<s;m++);
}