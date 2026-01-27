#include <xc.h>
#include "pwm.h"
#include "timer.h"
#include "timer.c"

void set_pwm_percentage(int percentage) {
    // D'après nos calcul, si on veut  PWM_duty_cycle = percentage, avec HL = PWMxDCH:PWMxDCL<7:6>
    // => percentage/100 = HL / 4(PR2+1)
    // => HL = percentage/100 * 4(PR2+1)
    
    // Comme c'est un int, on divise par 100 à la fin seulement
    // Sinon, la division par 100 va tronquer et fausser le résultat
    int HL = percentage * 4 * (PR2+1) /100;
    
    // Attribution aux registres
    PWM4DCH = HL>>2;
    PWM4DCL = HL<<6;
}

void config_pwm(void) {
    // On suit la table Datasheet TABLE 17-2 p. 180 car Fosc = 8mHz
    // Pour avoir un PWM period de 0.31 kHz
    // PR2 = 0x65
    // Prescale = 1:64 = 0b11
    // Postscale = 1:1 = 0b0000
    // Note : le postscaler n'est pas pris en compte pour le calcul 
    // du cycle PWM, donc utilise le postscaler 1:1.

    // On suit la recette Datasheet 17.1.9 SETUP FOR PWM OPERATION USING PWMx PINS

    // 1. Disable the PWMx pin output driver(s) by setting the associated TRIS bit(s).
    // On veut allumer la LED D1 (port  RD0) de manière analogique
    // On se rend compte expérimentalement que cette étape ne nous sert pas.    


    // 2. Clear the PWMxCON register.
    // "Vous pourrez configurer votre signal à sur le module PWM4, dont la base de temps est par défaut générée par le Timer 2."
    // Donc on utilise le 4ème
    PWM4CON = 0;

    // 3. Load the PR2 register with the PWM period value
    PR2 = 0x65;

    // 4. Load the PWMxDCH register and bits <7:6> of the PWMxDCL register 
    // with the PWM duty cycle value.
    set_pwm_percentage(100);

    // 5. Configure and start Timer2
    config_timer2(PR2, 0b11, 0b0000);

    // 6.  Enable PWM output pin and wait until Timer2 overflows, TMR2IF bit of the PIR1 register is set.
    // Note : For operation with other peripherals only, disable PWMx pin outputs.
    // Rien à faire dans notre cas

    // 7.  Enable the PWMx pin output driver(s) by clearing the associated TRIS bit(s) and 
    // setting the desired pin PPS control bits PWMxCON register with the appropriate values.
    // À configurer avant d'appeler cette fonction
    // Utiliser led_from_pps()

    // 8. Configure the PWM module by loading the
    PWM4EN = 1; // Activer le module
    PWM4OUT = 0; // On laisse tel quel
    PWM4POL = 0; // PWM output is active high
}