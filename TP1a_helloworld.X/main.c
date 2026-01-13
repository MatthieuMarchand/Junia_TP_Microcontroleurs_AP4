/** 
Résultats obtenus : 
Les 4 premières et dernières leds s'allument à un intervalle d'environ 1s
*/ 

#include "../Ressources/configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

// Allume les LEDs D1-8 de la carte Microchip Explorer 8 
// MCU : PIC16F1719 
//
// MCU : PIC16F1719 
//
// | LED   | Registre |
// |-------|----------|
// | D1-D4 | LATD     |
// | D5-D8 | LATB     |
//
// | LED | Registre       | Pin |
// |-----|----------------|-----|
// | D1  | LATDbits.LATD0 | R5  |
// | D2  | LATDbits.LATD1 | R6  |
// | D3  | LATDbits.LATD2 | R7  |
// | D4  | LATDbits.LATD3 | R8  |
// | D5  | LATBbits.LATB0 | R9  |
// | D6  | LATBbits.LATB1 | R10 |
// | D7  | LATBbits.LATB2 | R11 |
// | D8  | LATBbits.LATB3 | R12 |

void allumer_que_d1_a_d4(void);
void allumer_que_d5_a_d8(void);
void delai_approx(void);

void main(void) {
    TRISD &= 0xF0;
    TRISB &= 0xF0;

    while(1) {
        allumer_que_d1_a_d4();
        delai_approx();
        allumer_que_d5_a_d8();
        delai_approx();
    };
}

// Attendre approximativement 1s
void delai_approx(void) {
    for (long i = 0; i < 90000; i++); // Obtenu expérimentalement
}

void allumer_que_d1_a_d4(void) {
    LATB  &= 0xF0;
    LATD  |= 0x0F;
}

void allumer_que_d5_a_d8(void) {
    LATD  &= 0xF0;
    LATB  |= 0x0F;
}