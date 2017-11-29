#ifndef Display_H_
#define Display_H_

#include "PCD8544.h"

// NOKIA 5510           MSP430g2553
// 1. VCC               VCC
// 2. GND               GND
// 3. SCE               P1.0
// 4. RST               47KOhm -- VCC
// 5. D/C               P1.1
// 6. DN<MOSI>          P1.7
// 7. SCLK              P1.5
// 8. LED
#define LCD5110_SCLK_PIN BIT5
#define LCD5110_DN_PIN BIT7
#define LCD5110_SCE_PIN BIT0
#define LCD5110_DC_PIN BIT1
#define LCD5110_SELECT P1OUT &= ~LCD5110_SCE_PIN
#define LCD5110_DESELECT P1OUT |= LCD5110_SCE_PIN
#define LCD5110_SET_COMMAND P1OUT &= ~LCD5110_DC_PIN
#define LCD5110_SET_DATA P1OUT |= LCD5110_DC_PIN
#define LCD5110_COMMAND 0
#define LCD5110_DATA 1

#define SPI_MSB_FIRST UCB0CTL0 |= UCMSB // or UCA0CTL0 |= UCMSB (USCIA) or USICTL0 &= ~USILSB (USI)
#define SPI_LSB_FIRST UCB0CTL0 &= ~UCMSB // or UCA0CTL0 &= ~UCMSB or USICTL0 |= USILSB (USI)

void writeToLCD(unsigned char dataCommand, unsigned char data);
void writeCharToLCD(char c);
void writeStringToLCD(const char *string);
void writeIntToLCD(int n);
void clearLCD();
void setAddr(unsigned char xAddr, unsigned char yAddr);
void initLCD();

#endif
