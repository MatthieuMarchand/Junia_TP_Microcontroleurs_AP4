
#include "../Ressources/configbits.h"
#include <xc.h>  
#include "../Ressources/leds.h"
#include "../Ressources/leds.c"
#include "../Ressources/pot.h"
#include "../Ressources/pot.c"

void main(void) {
    int led;
    
    config_leds();
    config_pot();

    while(1){
        led = (read_pot() / 32) + 1;

        set_leds(0);
        set_led(led, 1);
    }
}