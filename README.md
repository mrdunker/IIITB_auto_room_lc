## IIITB_RISCV_Automated_Room_Lighting_control

This Repository summarizes the work progress made in The RISC-V-based project.
<br />

## Motive

This project aims to create a system for the automation of appliances in a room based on the user's proximity. Most rooms are not equipped to automatically turn ON and OFF essential appliances like lights and fans when people enter and exit rooms respectively. This saves a lot of net electricity and helps improve cost efficiency and power saving. This particular design is made predominantly for office and school spaces rather than homes.<br />

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

    led_pin_reg = led_pin*2;
    //printf("Motion sensor-based room light control started.\n");
    asm(
	"or x30, x30, %0\n\t" 
	:"=r"(led_pin_reg));
    asm(
	"andi %0, x30, 1\n\t"
	:"=r"(sensor_pin));
	
    while (1) {

        if (sensor_pin == 1) {
            // Motion detected, turn on the room light
            //digitalWrite(LIGHT_PIN, HIGH);
            //printf("Motion detected. Light turned ON.\n");
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
            //printf("No motion detected. Light turned OFF.\n");
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

```

## Assembly code conversion

The above C program is compiled using the RISC-V GNU toolchain and the assembly code is dumped into a text file.

```
motion.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <main>:
   0:	ff010113          	add	sp,sp,-16
   4:	00112623          	sw	ra,12(sp)
   8:	00812423          	sw	s0,8(sp)
   c:	01010413          	add	s0,sp,16
  10:	00000097          	auipc	ra,0x0
  14:	000080e7          	jalr	ra # 10 <main+0x10>
  18:	00000793          	li	a5,0
  1c:	00078513          	mv	a0,a5
  20:	00c12083          	lw	ra,12(sp)
  24:	00812403          	lw	s0,8(sp)
  28:	01010113          	add	sp,sp,16
  2c:	00008067          	ret

00000030 <readpindetails>:
  30:	fe010113          	add	sp,sp,-32
  34:	00112e23          	sw	ra,28(sp)
  38:	00812c23          	sw	s0,24(sp)
  3c:	02010413          	add	s0,sp,32
  40:	fec42783          	lw	a5,-20(s0)
  44:	00179793          	sll	a5,a5,0x1
  48:	fef42423          	sw	a5,-24(s0)
  4c:	00ff6f33          	or	t5,t5,a5
  50:	fef42423          	sw	a5,-24(s0)
  54:	000f7793          	and	a5,t5,0
  58:	fef42223          	sw	a5,-28(s0)

0000005c <.L6>:
  5c:	fe442703          	lw	a4,-28(s0)
  60:	00100793          	li	a5,1
  64:	02f71a63          	bne	a4,a5,98 <.L4>
  68:	00100793          	li	a5,1
  6c:	fef42623          	sw	a5,-20(s0)
  70:	fec42783          	lw	a5,-20(s0)
  74:	00179793          	sll	a5,a5,0x1
  78:	fef42423          	sw	a5,-24(s0)
  7c:	00ff6f33          	or	t5,t5,a5
  80:	fef42423          	sw	a5,-24(s0)
  84:	000017b7          	lui	a5,0x1
  88:	bb878513          	add	a0,a5,-1096 # bb8 <.L8+0xabc>
  8c:	00000097          	auipc	ra,0x0
  90:	000080e7          	jalr	ra # 8c <.L6+0x30>
  94:	fc9ff06f          	j	5c <.L6>

00000098 <.L4>:
  98:	fe042623          	sw	zero,-20(s0)
  9c:	fec42783          	lw	a5,-20(s0)
  a0:	00179793          	sll	a5,a5,0x1
  a4:	fef42423          	sw	a5,-24(s0)
  a8:	00ff6f33          	or	t5,t5,a5
  ac:	fef42423          	sw	a5,-24(s0)
  b0:	fadff06f          	j	5c <.L6>

000000b4 <delaytime>:
  b4:	fd010113          	add	sp,sp,-48
  b8:	02812623          	sw	s0,44(sp)
  bc:	03010413          	add	s0,sp,48
  c0:	fca42e23          	sw	a0,-36(s0)
  c4:	fe042623          	sw	zero,-20(s0)
  c8:	0340006f          	j	fc <.L8>

000000cc <.L11>:
  cc:	fe042423          	sw	zero,-24(s0)
  d0:	0100006f          	j	e0 <.L9>

000000d4 <.L10>:
  d4:	fe842783          	lw	a5,-24(s0)
  d8:	00178793          	add	a5,a5,1
  dc:	fef42423          	sw	a5,-24(s0)

000000e0 <.L9>:
  e0:	fe842703          	lw	a4,-24(s0)
  e4:	000f47b7          	lui	a5,0xf4
  e8:	23f78793          	add	a5,a5,575 # f423f <.L8+0xf4143>
  ec:	fee7d4e3          	bge	a5,a4,d4 <.L10>
  f0:	fec42783          	lw	a5,-20(s0)
  f4:	00178793          	add	a5,a5,1
  f8:	fef42623          	sw	a5,-20(s0)

000000fc <.L8>:
  fc:	fec42703          	lw	a4,-20(s0)
 100:	fdc42783          	lw	a5,-36(s0)
 104:	fcf744e3          	blt	a4,a5,cc <.L11>
 108:	00000013          	nop
 10c:	00000013          	nop
 110:	02c12403          	lw	s0,44(sp)
 114:	03010113          	add	sp,sp,48
 118:	00008067          	ret


```

<br />
The above assembly code was run on a Python script to find the different instructions used:
<br />

```
Number of different instructions: 17
List of unique instructions:
sw
nop
bge
add
sll
lui
and
jalr
lw
ret
bne
auipc
or
mv
blt
j
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

