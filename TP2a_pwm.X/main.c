/*
 * File:   main.c
 * Author: maatt
 *
 * Created on January 20, 2026, 3:38 PM
 */


// Datasheet : https://ww1.microchip.com/downloads/en/DeviceDoc/PIC16F1717_8_9-data-sheet-40001740C.pdf

// Stratégie de dev que l'on a suivi pour valider pas à pas notre avancée.
// 1. Allumer une led à 100% du cycle avec le PWM
// 2. Allumer une led à 10% du cycle avec le PWM
// 3. Allumer et éteindre une led avec le bouton
// 4. Allumer la led 100% ou 10% du cycle en fonction du bouton


#include "../Ressources/configbits.h"
#include <xc.h>  
#include "../Ressources/leds.h"
#include "../Ressources/leds.c"
#include "../Ressources/button.h"
#include "../Ressources/button.c"
#include "../Ressources/pwm.h"
#include "../Ressources/pwm.c"

void main(void) {
    config_leds();
    config_button();

    set_led_from_pps(1, PPS_PWM4OUT);

    config_pwm();

    set_leds(0);

    while(1) {
        // Ajuster pour aller à 10% ou 100%
        if(BTN_S1) {
            set_pwm_percentage(100);
        } else {
            set_pwm_percentage(10);
        }
    };
}