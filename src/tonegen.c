#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include "sintbl.h"

#define true  1 
#define false 0

#define  Xtal       10000000          // system clock frequency
#define  prescaler  1                // timer1 prescaler
#define  N_samples  128              // Number of samples in lookup table
#define  Fck        Xtal/prescaler   // Timer1 working frequency
#define OCRS	    OCR1A#define OCRS_OUTPUT()	DDRB|=1<<PB1;/*
unsigned char notes_tbbl[] = {
	8*sine_N*261*510ULL/Fck,
	8*sine_N*277*510ULL/Fck,
	8*sine_N*294*510ULL/Fck,
	8*sine_N*311*510ULL/Fck,
	8*sine_N*330*510ULL/Fck,
	8*sine_N*349*510ULL/Fck,
	8*sine_N*370*510ULL/Fck,
	8*sine_N*392*510ULL/Fck,
	8*sine_N*415*510ULL/Fck,
	8*sine_N*440*510ULL/Fck,
	8*sine_N*466*510ULL/Fck,
	8*sine_N*494*510ULL/Fck,
	8*sine_N*523*510ULL/Fck
};
*/

//unsigned char p [16] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15};
unsigned char p [16] = {3,6,9,15,15,15,15,15,15,15,15,15,15,9,6,3};
//unsigned char p [16] = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,1};
//unsigned char p [16] = {15,15,15,15,15,15,14,14,14,13,12,10,9,9,8,8};
//unsigned char p [16] = {15,15,15,15,15,15,15,15,15,15,15,15,10,6,3,0};
//unsigned char p [16] = {15,15,15,15,15,15,15,15,14,14,13,11,10,10,9,9};
//***************************  x_SW  ***************************************
//Table of x_SW (excess 8): x_SW = ROUND(8*N_samples*f*510/Fck)
//**************************************************************************

//**************************  global variables  ****************************
unsigned char x_SWa = 0x00;               // step width of high frequency
unsigned char x_SWb = 0x00;               // step width of low frequency
unsigned int  i_CurSinValA = 0;           // position freq. A in LUT (extended format)
unsigned int  i_CurSinValB = 0;           // position freq. B in LUT (extended format)
unsigned int  i_TmpSinValA;               // position freq. A in LUT (actual position)
unsigned int  i_TmpSinValB;               // position freq. B in LUT (actual position)

unsigned long DurationCnt;
unsigned long Duration;
char PlayFlag;
unsigned long SampleCnt;
unsigned int pIndex;
unsigned char q,t;
ISR (TIMER1_OVF_vect)           /* Note [2] */
{
	if(PlayFlag)
	{
 		// move Pointer about step width aheaed
  		i_CurSinValA += x_SWa;       
  		// normalize Temp-Pointer
  		i_TmpSinValA  =  (char)(((i_CurSinValA+4) >> 3)&(sine_N-1)); 
  		// calculate PWM value
		if(q<64) q++;
		if(DurationCnt<64) t=DurationCnt;
 	 	if(x_SWa)	OCRS = ((pgm_read_byte(&sine_tbl[i_TmpSinValA])*q)>>6)*t>>6;
			else OCRS = 0;
  		//SampleCnt++;
  		//DurationCnt--;
  		if(DurationCnt--==0){
  			PlayFlag=false;
			OCRS=0;
  		}
	}
}


//**************************************************************************
// Initialization
//**************************************************************************
void ToneGenInit (void)
{
  TIMSK  = 1<<TOIE1;                      // Int T1 Overflow enabled
  TCCR1A = (1<<COM1A1)+(1<<WGM10);   // non inverting / 8Bit PWM
  TCCR1B = (1<<CS10);                // CLK/1
  OCRS_OUTPUT();               // PD5 (OC1A) as output
  sei();                     	     // Interrupts enabled
  x_SWa=0;
  DurationCnt=0;
  PlayFlag=false;
  
}

void PlayTone(unsigned int freq,unsigned int len)
{
	//8*N_samples*f*510/Fck
	//x_SWa = (unsigned long long) 8*sine_N*freq*510/Fck;
	//x_SWa = (unsigned long) ((freq*(8*sine_N*51/100))/(Fck/1000));
	x_SWa = freq;
	q=0;t=64;
	DurationCnt=(unsigned long)(len*(Fck/10000))/51;
	Duration=DurationCnt;
	PlayFlag=true;
	SampleCnt=0;
	TCCR1A = (1<<COM1A1)+(1<<WGM10);
	TCCR1B = (1<<CS10);
}

char ToneIsComplete(void)
{
	return !PlayFlag;
}

void StopGen(void)
{
	TCCR1A = 0;
}
