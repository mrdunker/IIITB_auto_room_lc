## IIITB_RISCV_Automated_Room_Lighting_control

This Repository summarizes the work progress made in The RISC-V-based project.
<br />

## Motive

This project aims to create a system for the automation of appliances in a room based on the user's proximity. Most rooms are not equipped to automatically turn ON and OFF essential appliances like lights and fans when people enter and exit rooms respectively. This saves a lot of net electricity and helps improve cost efficiency and power saving. This particular design is more tailor-made for office and school spaces(working spaces) rather than homes.<br />

## Requirement

Here we will be using a PIR sensor. A passive infrared sensor (PIR sensor) is an electronic sensor that measures infrared (IR) light radiating from objects in its field of view. They are most often used in PIR-based motion detectors. This will detect the presence of any individuals in the vicinity. If yes our board is programmed to turn on the light(s) in a defined space. If not it will turn OFF automatically.

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

void delaytime(int);
void readpindetails();

int main()
{   

    readpindetails();
    return 0;
        
}
void readpindetails() {

    int led_pin,sensor_pin,led_pin_reg;
    led_pin = 0; // initialize the output pin as LOW initially
    led_pin_reg = led_pin*2;
    //printf("Motion sensor-based room light control started.\n");

    asm volatile(
	"or x30, x30, %0\n\t" 
	:
	:"r"(led_pin_reg)
	:"x30"
	);

    asm volatile(
	"andi %0, x30, 1\n\t"
	:"=r"(sensor_pin)
	:
	:
	);
	
    while (1) {

        if (sensor_pin == 1) {
            // Motion detected, turn on the room light
            //digitalWrite(LIGHT_PIN, HIGH);
            //printf("Motion detected. Light turned ON.\n");
            led_pin = 1;
            led_pin_reg = led_pin*2;
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(led_pin_reg)
		:"x30"
		);
            delaytime(3000);// Almost 6 second delay is given
            // You can add a delay here to control how long the light stays on
        } else {
            // No motion detected, turn off the room light
            //digitalWrite(LIGHT_PIN, LOW);
            //printf("No motion detected. Light turned OFF.\n");
            led_pin = 0;
            led_pin_reg = led_pin*2;
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(led_pin_reg)
		:"x30"
		);
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

```

## Assembly code conversion

The above C program is compiled using the RISC-V GNU toolchain and the assembly code is dumped into a text file.<br />

Below codes are run on the terminal to get the assembly code.<br />

```
/home/emil/riscv32-toolchain/bin/riscv32-unknown-elf-gcc -mabi=ilp32 -march=rv32i -ffreestanding -nostdlib -o ./out motion.c

/home/emil/riscv32-toolchain/bin/riscv32-unknown-elf-objdump -d -r out > motion_assembly.txt
```

```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <main>:
   10074:	ff010113          	add	sp,sp,-16
   10078:	00112623          	sw	ra,12(sp)
   1007c:	00812423          	sw	s0,8(sp)
   10080:	01010413          	add	s0,sp,16
   10084:	01c000ef          	jal	100a0 <readpindetails>
   10088:	00000793          	li	a5,0
   1008c:	00078513          	mv	a0,a5
   10090:	00c12083          	lw	ra,12(sp)
   10094:	00812403          	lw	s0,8(sp)
   10098:	01010113          	add	sp,sp,16
   1009c:	00008067          	ret

000100a0 <readpindetails>:
   100a0:	fe010113          	add	sp,sp,-32
   100a4:	00112e23          	sw	ra,28(sp)
   100a8:	00812c23          	sw	s0,24(sp)
   100ac:	02010413          	add	s0,sp,32
   100b0:	fe042623          	sw	zero,-20(s0)
   100b4:	fec42783          	lw	a5,-20(s0)
   100b8:	00179793          	sll	a5,a5,0x1
   100bc:	fef42423          	sw	a5,-24(s0)
   100c0:	fe842783          	lw	a5,-24(s0)
   100c4:	00ff6f33          	or	t5,t5,a5
   100c8:	001f7793          	and	a5,t5,1
   100cc:	fef42223          	sw	a5,-28(s0)
   100d0:	fe442703          	lw	a4,-28(s0)
   100d4:	00100793          	li	a5,1
   100d8:	02f71863          	bne	a4,a5,10108 <readpindetails+0x68>
   100dc:	00100793          	li	a5,1
   100e0:	fef42623          	sw	a5,-20(s0)
   100e4:	fec42783          	lw	a5,-20(s0)
   100e8:	00179793          	sll	a5,a5,0x1
   100ec:	fef42423          	sw	a5,-24(s0)
   100f0:	fe842783          	lw	a5,-24(s0)
   100f4:	00ff6f33          	or	t5,t5,a5
   100f8:	000017b7          	lui	a5,0x1
   100fc:	bb878513          	add	a0,a5,-1096 # bb8 <main-0xf4bc>
   10100:	024000ef          	jal	10124 <delaytime>
   10104:	fcdff06f          	j	100d0 <readpindetails+0x30>
   10108:	fe042623          	sw	zero,-20(s0)
   1010c:	fec42783          	lw	a5,-20(s0)
   10110:	00179793          	sll	a5,a5,0x1
   10114:	fef42423          	sw	a5,-24(s0)
   10118:	fe842783          	lw	a5,-24(s0)
   1011c:	00ff6f33          	or	t5,t5,a5
   10120:	fb1ff06f          	j	100d0 <readpindetails+0x30>

00010124 <delaytime>:
   10124:	fd010113          	add	sp,sp,-48
   10128:	02812623          	sw	s0,44(sp)
   1012c:	03010413          	add	s0,sp,48
   10130:	fca42e23          	sw	a0,-36(s0)
   10134:	fe042623          	sw	zero,-20(s0)
   10138:	0340006f          	j	1016c <delaytime+0x48>
   1013c:	fe042423          	sw	zero,-24(s0)
   10140:	0100006f          	j	10150 <delaytime+0x2c>
   10144:	fe842783          	lw	a5,-24(s0)
   10148:	00178793          	add	a5,a5,1
   1014c:	fef42423          	sw	a5,-24(s0)
   10150:	fe842703          	lw	a4,-24(s0)
   10154:	000f47b7          	lui	a5,0xf4
   10158:	23f78793          	add	a5,a5,575 # f423f <__global_pointer$+0xe28b3>
   1015c:	fee7d4e3          	bge	a5,a4,10144 <delaytime+0x20>
   10160:	fec42783          	lw	a5,-20(s0)
   10164:	00178793          	add	a5,a5,1
   10168:	fef42623          	sw	a5,-20(s0)
   1016c:	fec42703          	lw	a4,-20(s0)
   10170:	fdc42783          	lw	a5,-36(s0)
   10174:	fcf744e3          	blt	a4,a5,1013c <delaytime+0x18>
   10178:	00000013          	nop
   1017c:	00000013          	nop
   10180:	02c12403          	lw	s0,44(sp)
   10184:	03010113          	add	sp,sp,48
   10188:	00008067          	ret

```

<br />
The above assembly code was run on a Python script to find the different instructions used:
<br />

```
Number of different instructions: 16
List of unique instructions:
sw
mv
lw
or
nop
bne
blt
bge
jal
sll
lui
ret
and
j
add
li

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

