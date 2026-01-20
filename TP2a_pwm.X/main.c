/*
 * File:   main.c
 * Author: maatt
 *
 * Created on January 20, 2026, 3:38 PM
 */


#include "../Ressources/configbits.h"
#include <xc.h>  
#include "../Ressources/leds.h"
#include "../Ressources/leds.c"
#include "../Ressources/button.h"
#include "../Ressources/button.c"

void main(void) {
    config_leds();

    config_button();

    while(1) {
        set_leds(0);
        set_led(6, !BTN_S1);
    };

    // while(1);
}