## IIITB_RISCV_Automated_Room_Lighting_control

This Repository summarizes the work progress made in The RISC-V-based project.
<br />

## Motive

This project aims to create a system for the automation of appliances in a room based on the user's proximity. Most rooms are not equipped to automatically turn ON and OFF essential appliances like lights and fans when people enter and exit rooms respectively. This saves a lot of net electricity and helps improve cost efficiency and power saving. This particular design is more tailor-made for office and school spaces(working spaces) rather than homes.<br />

## Requirement

Here we will be using a PIR sensor. A passive infrared sensor (PIR sensor) is an electronic sensor that measures infrared (IR) light radiating from objects in its field of view. They are most often used in PIR-based motion detectors. This will detect the presence of any individuals in the vicinity. If yes our board is programmed to turn on the light(s) in a defined space. If not it will turn OFF automatically.Also putting an off Switch to the system.

## Block Diagram

![Screenshot from 2023-10-03 15-58-31](https://github.com/mrdunker/IIITB_home_aa_proximity/assets/38190245/22d7ebfd-5d77-4f17-97dc-ce7abe30fbdf)

## Assumed circuit 

The below shown is an assumed circuit(not entirely accurate).<br />
![Screenshot from 2023-10-04 22-00-41](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/a8f97e11-ff3e-45ed-ba8c-8e7785635908)



## Testing the code

1. Open a terminal window
2. Navigate to the directory when the .c file is present
3. Compile the code designed using gcc and verify the output.

```
gcc motion.c
./a.out
```
<br />

The following output is observed.<br />
When input from the sensor is HIGH:<br />
![Screenshot from 2023-10-03 11-20-58](https://github.com/mrdunker/IIITB_home_aa_proximity/assets/38190245/671b40bf-3639-4f5c-a90a-965b181e8bdf)
<br />

When input from the sensor is LOW:<br />
![Screenshot from 2023-10-03 11-21-37](https://github.com/mrdunker/IIITB_home_aa_proximity/assets/38190245/69fd662b-6de3-48ef-839e-b06de21c5103)


## C code for the design

```
int main()
{

 int led_pin,sensor_pin,led_pin_reg,i,j,reset_high;
 int mask1 = 0xFFFFFFFB;
 led_pin = 0; // initialize the output pin as LOW initially
 led_pin_reg = led_pin*4;
 
 
    /*asm volatile(
	"or x30, x30, %0\n\t" 
	:
	:"r"(led_pin_reg)
	:"x30"
	);*/
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

        if ((sensor_pin == 1) && (reset_high ==1)) {
            // Motion detected, turn on the room light
            //digitalWrite(LIGHT_PIN, HIGH);
            //printf("Motion detected. Light turned ON.\n");
            led_pin = 1;
            led_pin_reg = led_pin*4;
            /*asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(led_pin_reg)
		:"x30"
		);*/
		
		asm volatile(
		"and x30, x30, %1\n\t"
        	"or x30, x30, %0\n\t"
        	:
        	: "r"(led_pin_reg), "r"(mask1)
        	: "x30"
        	);
	    
	
		
	// Almost 6 second delay is given
        // You can add a delay here to control how long the light stays on
	    for (i = 0; i < 3000; i++) {
        	for (j = 0; j < 100000; j++) {
            	// Adding a loop inside to approximate seconds
        	}
    	    }
    	}//end of if statement
    	else
    	{
    	    //No motion detected or manual switch is off, turn off the room light
            //digitalWrite(LIGHT_PIN, LOW);
            //printf("No motion detected. Light turned OFF.\n");
            led_pin = 0;
            led_pin_reg = led_pin*4;
            /*asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(led_pin_reg)
		:"x30"
		);*/
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

```

## Assembly code conversion

The above C program is compiled using the RISC-V GNU toolchain and the assembly code is dumped into a text file.<br />

Below codes are run on the terminal to get the assembly code.<br />

```
riscv64-unknown-elf-gcc -mabi=ilp32 -march=rv32i -ffreestanding -nostdlib -o ./out motion.c 
riscv64-unknown-elf-objdump -d -r out > asm.txt

```


### Assembly code:

```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fd010113          	addi	sp,sp,-48
   10058:	02812623          	sw	s0,44(sp)
   1005c:	03010413          	addi	s0,sp,48
   10060:	ffb00793          	li	a5,-5
   10064:	fef42223          	sw	a5,-28(s0)
   10068:	fe042023          	sw	zero,-32(s0)
   1006c:	fe042783          	lw	a5,-32(s0)
   10070:	00279793          	slli	a5,a5,0x2
   10074:	fcf42e23          	sw	a5,-36(s0)
   10078:	fdc42783          	lw	a5,-36(s0)
   1007c:	fe442703          	lw	a4,-28(s0)
   10080:	00ef7f33          	and	t5,t5,a4
   10084:	00ff6f33          	or	t5,t5,a5
   10088:	001f7793          	andi	a5,t5,1
   1008c:	fcf42c23          	sw	a5,-40(s0)
   10090:	002f7793          	andi	a5,t5,2
   10094:	fcf42a23          	sw	a5,-44(s0)
   10098:	fd442703          	lw	a4,-44(s0)
   1009c:	00100793          	li	a5,1
   100a0:	08f71063          	bne	a4,a5,10120 <main+0xcc>
   100a4:	fd842703          	lw	a4,-40(s0)
   100a8:	00100793          	li	a5,1
   100ac:	06f71a63          	bne	a4,a5,10120 <main+0xcc>
   100b0:	00100793          	li	a5,1
   100b4:	fef42023          	sw	a5,-32(s0)
   100b8:	fe042783          	lw	a5,-32(s0)
   100bc:	00279793          	slli	a5,a5,0x2
   100c0:	fcf42e23          	sw	a5,-36(s0)
   100c4:	fdc42783          	lw	a5,-36(s0)
   100c8:	fe442703          	lw	a4,-28(s0)
   100cc:	00ef7f33          	and	t5,t5,a4
   100d0:	00ff6f33          	or	t5,t5,a5
   100d4:	fe042623          	sw	zero,-20(s0)
   100d8:	0340006f          	j	1010c <main+0xb8>
   100dc:	fe042423          	sw	zero,-24(s0)
   100e0:	0100006f          	j	100f0 <main+0x9c>
   100e4:	fe842783          	lw	a5,-24(s0)
   100e8:	00178793          	addi	a5,a5,1
   100ec:	fef42423          	sw	a5,-24(s0)
   100f0:	fe842703          	lw	a4,-24(s0)
   100f4:	000187b7          	lui	a5,0x18
   100f8:	69f78793          	addi	a5,a5,1695 # 1869f <__global_pointer$+0x6d5b>
   100fc:	fee7d4e3          	bge	a5,a4,100e4 <main+0x90>
   10100:	fec42783          	lw	a5,-20(s0)
   10104:	00178793          	addi	a5,a5,1
   10108:	fef42623          	sw	a5,-20(s0)
   1010c:	fec42703          	lw	a4,-20(s0)
   10110:	000017b7          	lui	a5,0x1
   10114:	bb778793          	addi	a5,a5,-1097 # bb7 <main-0xf49d>
   10118:	fce7d2e3          	bge	a5,a4,100dc <main+0x88>
   1011c:	0240006f          	j	10140 <main+0xec>
   10120:	fe042023          	sw	zero,-32(s0)
   10124:	fe042783          	lw	a5,-32(s0)
   10128:	00279793          	slli	a5,a5,0x2
   1012c:	fcf42e23          	sw	a5,-36(s0)
   10130:	fdc42783          	lw	a5,-36(s0)
   10134:	fe442703          	lw	a4,-28(s0)
   10138:	00ef7f33          	and	t5,t5,a4
   1013c:	00ff6f33          	or	t5,t5,a5
   10140:	f49ff06f          	j	10088 <main+0x34>

```

<br />
The above assembly code was run on a Python script to find the different instructions used:
<br />

```
Number of different instructions: 12
List of unique instructions:
slli
addi
lw
sw
or
lui
li
bne
andi
j
and
bge

```

## Acknowledgement

1. Kunal Ghosh, VSD Corp. Pvt. Ltd.
2. Sumanto Kar,VSD Corp.
3. Mayank Kabra, IIIT-Bangalore
4. Alwin Shaju, Colleague, IIIT-Bangalore
5. Kanish R, Colleague, IIIT-Bangalore

## References

1. https://github.com/SakethGajawada/RISCV-GNU
2. https://github.com/kunalg123

