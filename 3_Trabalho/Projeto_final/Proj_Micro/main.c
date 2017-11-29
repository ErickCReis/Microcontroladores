#include "msp430g2553.h"
#include <Display.h>
#include <Exercicios.h>

void tela_padrao();
int medir_dist();
void reset_ex();
void exer();
void fim();
void config_display();
void config_sensor();
void config_botoes();

#define BTN  BIT1   //Botão Nivel
#define Reset  BIT0 //Botão Reset
#define Botoes (BTN+Reset)

#define ECHO  BIT4  //Echo sensor ultras.
#define TRIG  BIT3  //Trig sensor ultras.
int miliseconds;
long sensor;

unsigned int nivel, ex, sr, rep;

pvoid main() {
    WDTCTL = WDTPW + WDTHOLD;   // Desabilitar WDT
    BCSCTL1 = CALBC1_1MHZ;      // Clock 1MHz
    DCOCTL = CALDCO_1MHZ;

    config_display();
    config_sensor();
    config_botoes();

    initLCD();
    clearLCD();
    tela_padrao();
    reset_ex();

    while(1){

    exer();

    setAddr(72, 0);
    writeIntToLCD(nivel + 1);
    setAddr(0, 3);
    writeStringToLCD(&nome[ex][0]);
    setAddr(72, 4);
    writeIntToLCD(sr + 1);
    setAddr(72, 5);
    writeIntToLCD(rep);
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
    if(P1IFG&ECHO){                 // Interrupção gerada pelo sensor ultrassônico
        if(!(P1IES&ECHO)){
            TA0CTL |= TACLR;
            miliseconds = 0;
            P1IES |= ECHO;
        }
        else sensor = (long)miliseconds*1000 + (long)TAR;
        P1IFG &= ~ECHO;
    }
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void){
    if(P2IFG&Reset){                 // Interrupção gerada pelo botão reset
        while((P2IN&Reset)==0);
        WDTCTL = 0;
    }
    if(P2IFG&BTN){                  // Interrupção gerada pelo botão
        __delay_cycles(100000);
        while((P2IN&BTN)==0);
        nivel++;
        if (nivel==6) nivel = 0;
        reset_ex();
        P2IFG &= ~BTN;
    }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void){   //Contagem de tempo do sensor ultrassônico
    miliseconds++;
    TA0CTL &= ~TAIFG;
}

void config_display(){
    P1OUT |= LCD5110_SCE_PIN + LCD5110_DC_PIN;
    P1DIR |= LCD5110_SCE_PIN + LCD5110_DC_PIN;
    P1SEL |= LCD5110_SCLK_PIN + LCD5110_DN_PIN;
    P1SEL2 |= LCD5110_SCLK_PIN + LCD5110_DN_PIN;
    UCB0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;    // 3-pin, 8-bit SPI master
    UCB0CTL1 |= UCSSEL_2;                           // SMCLK
    UCB0BR0 |= 0x01;                                // 1:1
    UCB0BR1 = 0;
    UCB0CTL1 &= ~UCSWRST;                           // clear SW
}

void config_sensor(){
    CCTL0 = CCIE;
    TA0CCR0 = 1000;
    TA0CTL = TASSEL_2 + MC_1;
    P1DIR |= TRIG;
    P1DIR &= ~ECHO;
    P1IE |= ECHO;
    P1IES &= ~ECHO;
}

void config_botoes(){
    P2DIR &= ~Botoes;
    P2REN |= Botoes;
    P2OUT |= Botoes;
    P2IES |= Botoes;
    P2IE |= Botoes;
    _BIS_SR(GIE);
}

int medir_dist(){
    int distancia;
    P1OUT |= TRIG;                  // gera um pulso
    __delay_cycles(10);             // espera 10 us
    P1OUT &= ~TRIG;                 // para o pulso
    P1IES &= ~ECHO;
    __delay_cycles(30000);          // tempo limite do sensor
    distancia = sensor/58;          // convertendo tempo em cm
    return distancia;
}

void tela_padrao(){
    setAddr(0, 0);
    writeStringToLCD("Nivel:");
    setAddr(0, 2);
    writeStringToLCD("Exercicio:");
    setAddr(0, 4);
    writeStringToLCD("Series:");
    setAddr(0, 5);
    writeStringToLCD("Repeticoes:");
}

void exer(){
    if(sr==0 && rep==0){
        __delay_cycles(5000000);
        ex++;
        sr = series[ex][nivel];
        rep = repeticoes[ex][nivel];
    }
    if(rep==0){
        __delay_cycles(5000000);
        sr--;
        rep = repeticoes[ex][nivel];
    }
    if(medir_dist()<=30){
        rep--;
        while(medir_dist()<=40) __delay_cycles(500000);
    }
    if(ex>2){
        fim();
    }
}

void reset_ex(){
    ex = 0;
    sr = series[ex][nivel];
    rep = repeticoes[ex][nivel];
}

void fim(){
    __delay_cycles(500000);
    clearLCD();
    reset_ex();
    setAddr(0, 2);
    writeStringToLCD("  Exercicios   ");
    setAddr(0, 3);
    writeStringToLCD("  Concluidos   ");
    _BIS_SR(LPM4_bits);
}
