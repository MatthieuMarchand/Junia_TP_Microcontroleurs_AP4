/*
Résultats obtenus : 

L'avantage de l'interruption est nettement visible : 
les deux chenillards cohabitent parfaitement. 

Le chenillard à interruption n'est pas impacté par la routine
lente et bloquante du second chenillard.
*/ 

#include "../Ressources/configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

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
//
// | BTN  | Registre      |
// |------|---------------|
// | BTN1 | PORTBbits.RB0 |


void config_interrupt(void);
void config_leds(void);
void config_button(void);
void config_timer2(void);

void handle_timer_interruption(void);
void update_chenillard(void);

void set_leds(unsigned char value);
void set_led(int led, unsigned char);

void delai_approx_1s(void);

int counter_ms = 0;
int led = 4;

void main(void) {
    config_leds();
    config_button();
    config_interrupt();
    config_timer2();

    set_leds(0);

    while(1) { // Chenillard lent et bloquant (D8 à D5)
        set_led(5, !PORTBbits.RB0);

        // set_led(5, 0);
        // set_led(8, 1);

        delai_approx_1s();

        // set_led(8, 0);
        // set_led(7, 1);

        // delai_approx_1s();

        // set_led(7, 0);
        // set_led(6, 1);

        // delai_approx_1s();

        // set_led(6, 0);
        // set_led(5, 1);

        // delai_approx_1s();
    };
    while(1);
}

void config_interrupt(void) {
    INTCONbits.GIE = 1; // Activer les interruptions globales
    INTCONbits.PEIE = 1; // Activer les interruptions périphériques
    
    PIE1bits.TMR2IE = 1; // Activer l'interruption TIMER2
    PIR1bits.TMR2IF = 0; // Initialiser le flag TIMER2 pour attendre l'interruption

    // TODO activer l'interruption sur le port RB0 sur front descendant (je crois, car le btn est à 1 quand non appuyé, et on veut l'interruption quand on appuie, donc quand on va de 1 à 0)
    // See page 160 https://ww1.microchip.com/downloads/en/DeviceDoc/PIC16F1717_8_9-data-sheet-40001740C.pdf
    //IOCBP0 = 1; // Activer l'interruption TIMER2
    //IOCBP0 = 0; // Initialiser le flag TIMER2 pour attendre l'interruption
}

void config_leds(void) {
    TRISD &= 0xF0; // Configuration des leds D1 à D4
    TRISB &= 0xF0; // Configuration des leds D5 à D8
}

void config_button(void) {
    TRISBbits.TRISB0 = 1; // Configuer le port du bouton S1 en lecture
}


/*
Configurer le Timer2 avec une période de 1 000 us.
Soit 1 ms. 

Voir ../TP1c_timer.X/main.c#config_timer2
*/
void config_timer2(void) {
 PR2 = 249; // Period register = 249
 T2CONbits.T2CKPS = 0b00; // Prescaler = 1:1
 T2CONbits.T2OUTPS = 0b0111; // Postscaler = 1:8
 T2CONbits.TMR2ON = 1; // Timer2 activé
}

void __interrupt() timer_handler (void){
    if (PIE1bits.TMR2IE && PIR1bits.TMR2IF){
        PIR1bits.TMR2IF = 0; // Ré-initialiser le flag TIMER2 pour attendre l'interruption
        
        handle_timer_interruption();
    }
}

void handle_timer_interruption(void) {
    if(++counter_ms >= 125) {
        counter_ms = 0; // Réinitialiser le compteur

        update_chenillard();
    }
}

void set_leds(unsigned char value) {
    // D1 à D4
    LATBbits.LATB3 = value;
    LATBbits.LATB2 = value;
    LATBbits.LATB1 = value;
    LATBbits.LATB0 = value;

    // D5 à D8
    LATDbits.LATD3 = value;
    LATDbits.LATD2 = value;
    LATDbits.LATD0 = value;
    LATDbits.LATD1 = value;
}

void set_led(int led, unsigned char value) {
    switch(led)
    {
        case 1:
            LATDbits.LATD0 = value;
            break;
        case 2:
            LATDbits.LATD1 = value; 
            break;
        case 3:
            LATDbits.LATD2 = value; 
            break;
        case 4:
            LATDbits.LATD3 = value; 
            break;
        case 5:
            LATBbits.LATB0 = value;
            break;
        case 6:
            LATBbits.LATB1 = value; 
            break;
        case 7:
            LATBbits.LATB2 = value; 
            break;
        case 8:
            LATBbits.LATB3 = value; 
            break;
    }
}

// Fonction qui éteint la led actuellement allumée et qui allume la led suivante
void update_chenillard(void) {
    set_led(led, 0);

    // Incrémenter la led, retour à la première led si on a atteint la dernière
    if(++led>4) { 
        led = 1; 
    }

    set_led(led, 1);
}

// Attendre approximativement 1s
void delai_approx_1s(void) {
    for (long i = 0; i < 90000; i++); // Obtenu expérimentalement
}
