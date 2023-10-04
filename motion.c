#include <stdio.h>
void delaytime(int);
void readpindetails();

int main()
{   

    readpindetails();
    return 0;
        
}
void readpindetails() {

    int led_pin,sensor_pin,led_pin_reg;

    led_pin_reg = led_pin*2;
    //printf("Motion sensor-based room light control started.\n");
    asm(
	"or x30, x30, %0\n\t" 
	:"=r"(led_pin_reg));
    asm(
	"andi %0, x30, 0\n\t"
	:"=r"(sensor_pin));
	
    while (1) {

        if (sensor_pin == 1) {
            // Motion detected, turn on the room light
            //digitalWrite(LIGHT_PIN, HIGH);
            printf("Motion detected. Light turned ON.\n");
            led_pin = 1;
            led_pin_reg = led_pin*2;
            asm(
		"or x30, x30, %0\n\t" 
		:"=r"(led_pin_reg));
            delaytime(3000);// Almost 6 second delay is given
            // You can add a delay here to control how long the light stays on
        } else {
            // No motion detected, turn off the room light
            //digitalWrite(LIGHT_PIN, LOW);
            printf("No motion detected. Light turned OFF.\n");
            led_pin = 0;
            led_pin_reg = led_pin*2;
            asm(
		"or x30, x30, %0\n\t" 
		:"=r"(led_pin_reg));
        }
    }

}
void delaytime(int seconds) {
    int i, j;
    for (i = 0; i < seconds; i++) {
        for (j = 0; j < 1000000; j++) {
            // Adding a loop inside to approximate seconds
        }
    }
}

