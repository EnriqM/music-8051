//#include <reg51.h>
#include "c8051F340.h"
#include "Configuracion.c"

sbit P1_0=P1^0;
unsigned int semillas_notas[2][7] =
{{0xFC4D, 0xFCB6, 0xFD0A, 0xFD39, 0xFD88, 0xFDC7, 0xFE06}
,{0xFE26, 0xFE5B, 0xFE85, 0xFE9C, 0xFEC4, 0xFEE3, 0xFF03}};

unsigned char semillaH,semillaL;
unsigned int semilla;

enum notas {DO=0,RE=1,MI=2,FA=3,SOL=4,LA=5,sI=6};
char elementos_fragmento[17]= {DO, DO, DO, FA, LA, DO, DO, DO, FA, LA, FA, FA, MI, MI, RE, RE, DO};
void Init_Device(void);

void main(void)
{
	char i,j,nota;
	unsigned int k,espera;
	Init_Device();
	IE=0x82; //Interrupción por desbordamiento del timer O
	TMOD=0x01; // Timer 0 como temporizador de 16 bits
	TCON=0x10; // Arrancamos el timer 0
	//CKCON=0x01;
	//OSCICN=0x83; //Probar también con 0x81;
	P1_0=0;

	while(1)
	{
		for(i=0;i<2;i++)
		{
			for (j=0;j<17;j++)
			{
				nota=elementos_fragmento[j];	// se selecciona la nota
				semilla=semillas_notas[i][nota];
				semillaL=semilla;
				semillaH=semilla>>8;
				TH0=semillaH;
				TL0=semillaL;
				for(k=0;k<15000;k++);
			}
			TR0=0;   
	 		for(espera=0;espera<60000;espera++);   // 2 segundos hasta la siguiente nota
	 		TR0=1;   
		}
	}
}

void Timer0_ISR(void) interrupt 1
{
  	TH0=semillaH; // Recargamos las semillas
	TL0=semillaL;
	P1_0=!P1_0;
}
