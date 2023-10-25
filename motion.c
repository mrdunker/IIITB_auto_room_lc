
int main()
{

 int led_pin,sensor_pin,led_pin_reg,i,j,reset_high;
 int mask1 = 0xFFFFFFFB;
 led_pin = 0; // initialize the output pin as LOW initially
 led_pin_reg = led_pin*4;
 
	asm volatile(
	"and x30, x30, %1\n\t"
        "or x30, x30, %0\n\t"
        :
        : "r"(led_pin_reg), "r"(mask1)
        : "x30"
        );	
//for(int z=0;z<1;z++)
while(1)
 {
    //Off switch- if the reset_high is low it should be off fully.
        asm volatile(
	"andi %0, x30, 1\n\t"
	:"=r"(reset_high)
	:
	:
	);
    //"Motion sensor-based room light control started"
    asm volatile(
	"andi %0, x30, 2\n\t"
	:"=r"(sensor_pin)
	:
	:
	);
	//sensor_pin=1;
	//reset_high=1;

        if ((sensor_pin) && (reset_high)) {
            // Motion detected, turn on the room light
            //digitalWrite(LIGHT_PIN, HIGH);
            //printf("Motion detected. Light turned ON.\n");
            led_pin = 1;
            led_pin_reg = led_pin*4;
		
		asm volatile(
		"and x30, x30, %1\n\t"
        	"or x30, x30, %0\n\t"
        	:
        	: "r"(led_pin_reg), "r"(mask1)
        	: "x30"
        	);
	    // You can add a delay here to control how long the light stays on
	    for (i = 0; i < 100; i++) {
        	
    	    }
    	}//end of if statement
    	else
    	{
    	    //No motion detected or manual switch is off, turn off the room light
            //digitalWrite(LIGHT_PIN, LOW);
            //printf("No motion detected. Light turned OFF.\n");
            led_pin = 0;
            led_pin_reg = led_pin*4;

		asm volatile(
		"and x30, x30, %1\n\t"
        	"or x30, x30, %0\n\t"
        	:
        	: "r"(led_pin_reg), "r"(mask1)
        	: "x30"
        	);	
    	}//end of else statement
    	}//end while loop
    	
    return 0;
}
