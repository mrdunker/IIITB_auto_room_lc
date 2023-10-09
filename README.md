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

int led_pin,sensor_pin,led_pin_reg;

void delaytime(int);
void readpindetails();

int main()
{   
 
 led_pin = 0; // initialize the output pin as LOW initially
 led_pin_reg = led_pin*2;
 
    asm volatile(
	"or x30, x30, %0\n\t" 
	:
	:"r"(led_pin_reg)
	:"x30"
	);

 while(1){
    readpindetails();
    }
    return 0;
        
}
void readpindetails() {


    //"Motion sensor-based room light control started"

    asm volatile(
	"andi %0, x30, 1\n\t"
	:"=r"(sensor_pin)
	:
	:
	);

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


### Assembly code:

```

out:     file format elf32-littleriscv


Disassembly of section .text:

00010094 <main>:
   10094:	ff010113          	add	sp,sp,-16
   10098:	00112623          	sw	ra,12(sp)
   1009c:	00812423          	sw	s0,8(sp)
   100a0:	01010413          	add	s0,sp,16
   100a4:	000117b7          	lui	a5,0x11
   100a8:	1c07a423          	sw	zero,456(a5) # 111c8 <__DATA_BEGIN__>
   100ac:	000117b7          	lui	a5,0x11
   100b0:	1c87a783          	lw	a5,456(a5) # 111c8 <__DATA_BEGIN__>
   100b4:	00179713          	sll	a4,a5,0x1
   100b8:	80e1a423          	sw	a4,-2040(gp) # 111d0 <led_pin_reg>
   100bc:	8081a783          	lw	a5,-2040(gp) # 111d0 <led_pin_reg>
   100c0:	00ff6f33          	or	t5,t5,a5
   100c4:	008000ef          	jal	100cc <readpindetails>
   100c8:	ffdff06f          	j	100c4 <main+0x30>

000100cc <readpindetails>:
   100cc:	ff010113          	add	sp,sp,-16
   100d0:	00112623          	sw	ra,12(sp)
   100d4:	00812423          	sw	s0,8(sp)
   100d8:	01010413          	add	s0,sp,16
   100dc:	001f7713          	and	a4,t5,1
   100e0:	000117b7          	lui	a5,0x11
   100e4:	1ce7a623          	sw	a4,460(a5) # 111cc <sensor_pin>
   100e8:	000117b7          	lui	a5,0x11
   100ec:	1cc7a703          	lw	a4,460(a5) # 111cc <sensor_pin>
   100f0:	00100793          	li	a5,1
   100f4:	02f71c63          	bne	a4,a5,1012c <readpindetails+0x60>
   100f8:	000117b7          	lui	a5,0x11
   100fc:	00100713          	li	a4,1
   10100:	1ce7a423          	sw	a4,456(a5) # 111c8 <__DATA_BEGIN__>
   10104:	000117b7          	lui	a5,0x11
   10108:	1c87a783          	lw	a5,456(a5) # 111c8 <__DATA_BEGIN__>
   1010c:	00179713          	sll	a4,a5,0x1
   10110:	80e1a423          	sw	a4,-2040(gp) # 111d0 <led_pin_reg>
   10114:	8081a783          	lw	a5,-2040(gp) # 111d0 <led_pin_reg>
   10118:	00ff6f33          	or	t5,t5,a5
   1011c:	000017b7          	lui	a5,0x1
   10120:	bb878513          	add	a0,a5,-1096 # bb8 <main-0xf4dc>
   10124:	03c000ef          	jal	10160 <delaytime>
   10128:	0240006f          	j	1014c <readpindetails+0x80>
   1012c:	000117b7          	lui	a5,0x11
   10130:	1c07a423          	sw	zero,456(a5) # 111c8 <__DATA_BEGIN__>
   10134:	000117b7          	lui	a5,0x11
   10138:	1c87a783          	lw	a5,456(a5) # 111c8 <__DATA_BEGIN__>
   1013c:	00179713          	sll	a4,a5,0x1
   10140:	80e1a423          	sw	a4,-2040(gp) # 111d0 <led_pin_reg>
   10144:	8081a783          	lw	a5,-2040(gp) # 111d0 <led_pin_reg>
   10148:	00ff6f33          	or	t5,t5,a5
   1014c:	00000013          	nop
   10150:	00c12083          	lw	ra,12(sp)
   10154:	00812403          	lw	s0,8(sp)
   10158:	01010113          	add	sp,sp,16
   1015c:	00008067          	ret

00010160 <delaytime>:
   10160:	fd010113          	add	sp,sp,-48
   10164:	02812623          	sw	s0,44(sp)
   10168:	03010413          	add	s0,sp,48
   1016c:	fca42e23          	sw	a0,-36(s0)
   10170:	fe042623          	sw	zero,-20(s0)
   10174:	0340006f          	j	101a8 <delaytime+0x48>
   10178:	fe042423          	sw	zero,-24(s0)
   1017c:	0100006f          	j	1018c <delaytime+0x2c>
   10180:	fe842783          	lw	a5,-24(s0)
   10184:	00178793          	add	a5,a5,1
   10188:	fef42423          	sw	a5,-24(s0)
   1018c:	fe842703          	lw	a4,-24(s0)
   10190:	000f47b7          	lui	a5,0xf4
   10194:	23f78793          	add	a5,a5,575 # f423f <__global_pointer$+0xe2877>
   10198:	fee7d4e3          	bge	a5,a4,10180 <delaytime+0x20>
   1019c:	fec42783          	lw	a5,-20(s0)
   101a0:	00178793          	add	a5,a5,1
   101a4:	fef42623          	sw	a5,-20(s0)
   101a8:	fec42703          	lw	a4,-20(s0)
   101ac:	fdc42783          	lw	a5,-36(s0)
   101b0:	fcf744e3          	blt	a4,a5,10178 <delaytime+0x18>
   101b4:	00000013          	nop
   101b8:	00000013          	nop
   101bc:	02c12403          	lw	s0,44(sp)
   101c0:	03010113          	add	sp,sp,48
   101c4:	00008067          	ret

```

<br />
The above assembly code was run on a Python script to find the different instructions used:
<br />

```
Number of different instructions: 15
List of unique instructions:
sw
nop
lui
or
bge
bne
add
sll
li
and
jal
j
lw
blt
ret

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

