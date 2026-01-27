#include "../Ressources/configbits.h"
#include <xc.h>  
#include "../Ressources/leds.h"
#include "../Ressources/leds.c"
#include "../Ressources/pot.h"
#include "../Ressources/pot.c"
#include "../Ressources/pwm.h"
#include "../Ressources/pwm.c"

void main(void) {
    int percentage;
    
    config_leds();
    config_pot();

    set_led_from_pps(1, PPS_PWM4OUT);
    set_led_from_pps(2, PPS_PWM4OUT);
    set_led_from_pps(3, PPS_PWM4OUT);
    set_led_from_pps(4, PPS_PWM4OUT);
    set_led_from_pps(5, PPS_PWM4OUT);
    set_led_from_pps(6, PPS_PWM4OUT);
    set_led_from_pps(7, PPS_PWM4OUT);
    set_led_from_pps(8, PPS_PWM4OUT);

    config_pwm();

    while(1){
        percentage = read_pot() * 100 / 255;

        set_pwm_percentage(percentage);
    }
}