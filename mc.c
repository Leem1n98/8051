
// 20240315 MUSIC look up Table and scan

/*
;					8051                                        
;	LSi 247 Hz 4048us/2=2024us=8usx253
;1	Do	262 Hz 3817us/2=1908us=8usx238.5
;2	Re	294 Hz 3401us/2=1700us=8usx212.5
;3	Mi	329 Hz 3040us/2=1520us=8usx190
;4	Fa	349 Hz 2865us/2=1432us=8usx179
;5	So	392 Hz 2551us/2=1275us=8usx159.4
;6	La	440 Hz 2273us/2=1136us=8usx142
;7	Si	494 Hz 2024us/2=1012us=8usx126.5
;8	HDo	524 Hz 1908us/2= 954us=8usx119.25
;9	HRe 588 Hz 1700us/2= 850us=8usx106
;10	HMi 658 Hz 1520us/2= 760us=8usx95
;11	HFa	698 Hz 1432us/2= 716us=8usx89
;12	HSo 784 Hz 1275us/2= 638us=8usx80
;13	HLa 880 Hz 1136us/2= 568us=8usx71
;14	HSi 988 Hz 1012us/2= 506us=8usx63
*/

#include"reg51.h"
void delay(unsigned char s);
void main()
{
	unsigned char code L7seg[] ={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};

	unsigned char code song[]={5,3,3,4,2,2,1,2,3,4,5,5,5,5,3,3,4,2,2,1,3,5,5,1};
	unsigned char code mtime[]={61,65,73,82,87,98,110,123,131,147,164,174,196,220,247};
	unsigned char code mdelay[]={253,238,212,190,179,159,142,126,119,106,95,89,80,71,63};
	unsigned char count;
	unsigned char n;

	unsigned char num0, num1;
	num0=0;
	num1=99;

	while(1)
	{
		for (count=0;count<24;count++)
		{
			if (song[count]==0)
			{
				for (n=0;n<mtime[song[count]];n++)
				{
					P1=0x55;//nosound
					delay(mdelay[song[count]]);
					P1=0x55;//nosound
					delay(mdelay[song[count]]);
				}
			}
			else
			{
				for (n=0;n<mtime[song[count]];n++)
				{
					
					P2=0xF7;// scan  11110111
					ACC= L7seg[num0%10];
					P0 = ACC;
					
					P1=0xAA;
					delay(mdelay[song[count]]);

					P2=0xFB;// scan  11111011
					ACC= L7seg[num0/10];
					P0 = ACC;

					P1=0x55;
					delay(mdelay[song[count]]);

/////////////////////////////////////////////////

					P2=0xFD;// scan  11111101
					ACC= L7seg[num1%10];
					P0 = ACC;
					
					P1=0xAA;
					delay(mdelay[song[count]]);

					P2=0xFE;// scan  11111110
					ACC= L7seg[num1/10];
					P0 = ACC;

					P1=0x55;
					delay(mdelay[song[count]]);
				}
			} //end of else

				if(num0 == 99)
				{
					num0 =0;
				}
				else
				{
					num0 = num0+1;
				}

				if(num1 == 0)
				{
					num1 =99;
				}
				else
				{
					num1 = num1-1;
				}

				P1=0x55;//nosound
				delay(25);

		} // for music
	} //while
}//main

void delay(unsigned char s)
{
	unsigned char m;
	for(m=0;m<s;m++);
}