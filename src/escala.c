//#include <reg51.h>
#include "C8051F340.h"

sbit P1_0=P1^0;
unsigned int semillas_notas[2][7] =
{{0xFC4D, 0xFCB6, 0xFD0A, 0xFD39, 0xFD88, 0xFDC7, 0xFE06}
,{0xFE26, 0xFE5B, 0xFE85, 0xFE9C, 0xFEC4, 0xFEE3, 0xFF03}};

unsigned char semillaH,semillaL;
unsigned int semilla;
void Init_Device(void);

void main(void)
{
	char i,j;
	unsigned int k;
	Init_Device();
	IE=0x82; //Interrupción por desbordamiento del timer O
	TMOD=0x01; // Timer 0 como temporizador de 16 bits
	TCON=0x10; // Arrancamos el timer 0
	P1_0=0;

	while(1)
	{
		for(i=0;i<2;i++)
		{
			for (j=0;j<8;j++)
			{
				semilla=semillas_notas[i][j];
				semillaL=semilla;
				semillaH=semilla>>8;
				TH0=semillaH;
				TL0=semillaL;
				for(k=0;k<15000;k++);
			}
		}
	}
}

void Timer0_ISR(void) interrupt 1
{
  	TH0=semillaH; // Recargamos las semillas
	TL0=semillaL;
	P1_0=!P1_0;
}
