1 . Dada uma variável `a` do tipo `char` (um byte), escreva os trechos de código em C para:

(a) Somente setar o bit menos significativo de `a`.
  
	a |= BIT0;
  
(b) Somente setar dois bits de `a`: o menos significativo e o segundo menos significativo.
	
	a |= BIT1 + BIT0;
  
(c) Somente zerar o terceiro bit menos significativo de `a`.
  
	a &= ~BIT2;
  
(d) Somente zerar o terceiro e o quarto bits menos significativo de `a`.
  
	a &= ~(BIT3 + BIT2);
  
(e) Somente inverter o bit mais significativo de `a`.
  
	a ^= BIT7;
  
(f) Inverter o nibble mais significativo de `a`, e setar o nibble menos significativo de `a`. 
  
	a ^= BIT7 + BIT6 + BIT5 + BIT4;
	a |= BIT3 + BIT2 + BIT1 + BIT0;
  

2 . Considerando a placa Launchpad do MSP430, escreva o código em C para piscar os dois LEDs ininterruptamente.

```C
#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
void main(void){
WDTCTL = WDTPW | WDTHOLD;
P1OUT = 0;
P1DIR = LED1 + LED2;
int i;
for(;;)
{
for(i=0; i<10 ; i++)
{
P1OUT ^= LED1 + LED2;
}
}
}
```


3 . Considerando a placa Launchpad do MSP430, escreva o código em C para piscar duas vezes os dois LEDs sempre que o usuário pressionar o botão.

```C
#include <msp430g2553.h>
#define BTN BIT2
#define LED1 BIT0
#define LED2 BIT6
void main(void){
WDTCTL = WDTPW | WDTHOLD;
P1OUT = 0;
P1DIR = LED1 + LED2;
int i,j;
for(;;)
{
while((P1IN & BTN) == 0){}
for(i=0; i<4 ; i++)
{
P1OUT ^= LED1 + LED2;
for(j=0; j<10 ; j++){}
}
}
}
```

4. Considerando a placa Launchpad do MSP430, faça uma função em C que pisca os dois LEDs uma vez.

```C
void pisca_led (){
int i, j;
for(i=0; i<2 ; i++)
{
P1OUT ^= LED1 + LED2;
for(j=0; j<10 ; j++){}
}
}
```

5. Reescreva o código da questão 2 usando a função da questão 4.

```C
#include <msp430g2553.h>
#define LED1 BIT0
#define LED2 BIT6
void main(void){
WDTCTL = WDTPW | WDTHOLD;
P1OUT = 0;
P1DIR = LED1 + LED2;
for(;;)
{
pisca_led();
}
}
```

6. Reescreva o código da questão 3 usando a função da questão 4.

```C
#include <msp430g2553.h>
#define BTN BIT2
#define LED1 BIT0
#define LED2 BIT6
void main(void){
WDTCTL = WDTPW | WDTHOLD;
P1OUT = 0;
P1DIR = LED1 + LED2;
int k;
for(;;)
{
while((P1IN & BTN) == 0){}
for(k=0; k<2 ; k++)
{
pisca_led();
}
}
}
```
