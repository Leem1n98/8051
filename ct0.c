// 20151016®ý¦¿·Å¦{¤u¶TSTC¶}µoª©
/*	High On			Low On
;0:00111111B(3FH)11000000B(C0H)
;1:00000110B(06H)11111001B(F9H)
;2:01011011B(5BH)10100100B(A4H)
;3:01001111B(4FH)10110000B(B0H)
;4:01100110B(66H)10011001B(99H)
;5:01101101B(6DH)10010010B(92H)
;6:01111101B(7DH)10000010B(82H)
;7:00000111B(07H)11111000B(F8H)
;8:01111111B(7FH)10000000B(80H)
;9:01101111B(6FH)10010000B(90H)
;A:01110111B(77H)10001000B(88H)
;b:01111100B(7CH)10000011B(83H)
;C:00111001B(39H)11000110B(C6H)
;d:01011110B(5EH)10100001B(A1H)
;E:01111001B(79H)10000110B(86H)
;F:01110001B(71H)10001110B(8EH)
*/

#include"reg51.h"
void delay(int s);
//	unsigned char code H7seg[] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//	unsigned char code H7seg[] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
	unsigned char code L7seg[] ={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
//	unsigned char code L7Dseg[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,0x08,0x03,0x46,0x21,0x06,0x0E};
	char count0,count1;
	unsigned char i,num;
	unsigned char ATEMP, DPLTEMP,DPHTEMP;

void main()
{
	TMOD = 0xD1; //	SET TIMER0 MODE 1. (11010001B)
	TH0  = (65536-5000)/256;
	TL0  = (65536-5000)%256;
	PT0 = 1; //IP.1 SET TIMER0 INTERRUPT HIGH PRIORITY
	TF0=0; //TCON.5 CLEAR TIMER0 OVERFLOW
	TR0=1; //TCON.4 SET TIMER0 RUN
// IE.7(SET ALL INTERRUPT ENABLE);IE.1(ENABLE TIMER0 INTERRUPT)
	IE   = 0x82; // 10000010B

	i=0;

	count0=0;
	count1=99;

	while(1)
	{

	}
}




/******************************************************************************
;               USE TIMER0_INT 
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

	num = i%4;
	if (num==0)
	{
		P2=0xF7;// scan  11110111
		ACC= L7seg[count0%10];
		P0 = ACC;
	}
	if (num==1)
	{
		P2=0xFB;// scan  11111011
		ACC= L7seg[count0/10];
		P0 = ACC;
	}
	if (num==2)
	{
		P2=0xFd;// scan  11111101
		ACC= L7seg[count1%10];
		P0 = ACC;
	}
	if (num==3)
	{
		P2=0xFE;// scan  11111110
		ACC= L7seg[count1/10];
		P0 = ACC;
	}

	i=i+1;
	if (i==200)
	{
		i=0;

		if (count0==99)
		{
			count0=0;
		}
		else
		{
			count0=count0+1;
		}
		
		if (count1==0)
		{
			count1=99;
		}
		else
		{
			count1=count1-1;
		}
	}

// RETURN:
	ACC=ATEMP;
	DPL=DPLTEMP;
	DPH=DPHTEMP;
}

/*
void main()
void INT0 (void) interrupt 0 using 0 // using bank0
void Timer0 (void) interrupt 1 using 1 // using bank1
void INT1 (void) interrupt 2 using 2 // using bank2
void Timer1 (void) interrupt 3 using 3 // using bank3
void Serial (void) interrupt 4

	ORG     0000H           ;
	JMP     START           ;

	ORG     0003H           ;
	JMP     EXTERNAL_INT0   ;EXTERNAL INT0 INTERRUPT

	ORG     000BH           ;
	JMP     TIMER0_INT      ;INTERNAL TIMER0 INTERRUPT

	ORG     0013H           ;
	JMP     EXTERNAL_INT1   ;EXTERNAL INT1 INTERRUPT

	ORG     001BH           ;
	JMP     TIMER1_INT      ;INTERNAL TIMER1 INTERRUPT

	ORG     0023H           ;
	JMP     SERIAL_TRANS    ;SERIAL TRANSMISSION INTERRUPT
*/