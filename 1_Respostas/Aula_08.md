Para todas as questões, utilize os LEDs e/ou os botões da placa Launchpad do MSP430.

1. Escreva um código em C que pisca os LEDs ininterruptamente.

```C
#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
#define LEDS (LED1|LED2)
#define BTN  BIT3

void atraso(volatile unsigned int i)
{
	while((i--)>0);
}

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	P1OUT |= LEDS;
	P1DIR |= LEDS;
	while(1)
	{
		atraso(0xbfff);
		P1OUT ^= LEDS;
	}
	return 0;
}

```

2. Escreva um código em C que pisca os LEDs ininterruptamente. No ciclo que pisca os LEDs, o tempo que os LEDs ficam ligados deve ser
duas vezes maior do que o tempo que eles ficam desligados.

```C
#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
#define LEDS (LED1|LED2)
#define BTN  BIT3

void atraso(volatile unsigned int i)
{
  while((i--)>0);
}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT |= LEDS;
  P1DIR |= LEDS;
  while(1)
  {
    atraso(0xbfff);
    atraso(0xbfff);
    P1OUT ^= LEDS;
    atraso(0xbfff);
    P1OUT ^= LEDS;    
  }
  return 0;
}

```

3. Escreva um código em C que acende os LEDs quando o botão é pressionado.


```C
#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
#define LEDS (LED1|LED2)
#define BTN  BIT3

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;
	P1OUT |= LEDS;
	P1DIR |= LEDS;
	P1DIR &= ~BTN;
	P1REN |= BTN;
	P1OUT |= BTN;
	while(1)
	{
		if((P1IN&BTN)==0)
			P1OUT = LEDS+BTN;
		else
			P1OUT &= ~LEDS;
	}
	return 0;
}

```

4. Escreva um código em C que pisca os LEDs ininterruptamente somente se o botão for pressionado.

```C
#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
#define LEDS (LED1|LED2)
#define BTN  BIT3

void atraso(volatile unsigned int i)
{
  while((i--)>0);
}

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT |= LEDS;
  P1DIR |= LEDS;
  P1DIR &= ~BTN;
  P1REN |= BTN;
  P1OUT |= BTN;
  while(1)
  {
    if((P1IN&BTN)==0){
    P1OUT ^= LEDS; 
    atraso(0xbfff);
    }
    else
      P1OUT &= ~LEDS;
  }
  return 0;
}

```

5. Escreva um código em C que acende os LEDs quando o botão é pressionado. Deixe o MSP430 em modo de baixo consumo, e habilite a 
interrupção do botão.

```C

#include <msp430g2553.h>
#include <legacymsp430.h> // Para rodar interrupcoes
#define LED1 BIT0
#define LED2 BIT6
#define LEDS (LED1|LED2)
#define BTN  BIT3

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;
  P1OUT &= ~LEDS;
  P1DIR |= LEDS;
  P1DIR &= ~BTN;
  P1REN |= BTN;
  P1OUT |= BTN;
  P1IES |= BTN;
  P1IE |= BTN;
  _BIS_SR(GIE + LPM4_bits);
  return 0;
}

interrupt(PORT1_VECTOR) Interrupcao_P1(void)
{
  P1OUT ^= LEDS;
  while((P1IN&BTN)==0);
  P1OUT ^= LEDS;
  P1IFG &= ~BTN;
}

```
