## IIITB_RISCV_Automated_Room_Lighting_control

This Repository summarizes the work progress made in The RISC-V-based project.
<br />

## Motive

This project aims to create a system for the automation of appliances in a room based on the user's proximity. Most rooms are not equipped to automatically turn ON and OFF essential appliances like lights and fans when people enter and exit rooms respectively. This saves a lot of net electricity and helps improve cost efficiency and power saving. This particular design is more tailor-made for office and school spaces(working spaces) rather than homes.<br />

## Requirement

Here we will be using a PIR sensor. A passive infrared sensor (PIR sensor) is an electronic sensor that measures infrared (IR) light radiating from objects in its field of view. They are most often used in PIR-based motion detectors. This will detect the presence of any individuals in the vicinity. If yes our board is programmed to turn on the light(s) in a defined space. If not it will turn OFF automatically. Also, we are using putting an **ON-OFF main switch** for the system.

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

The following output is observed after doing GCC compilation.<br />
When input from the sensor and main switch are both HIGH:<br />
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
   10064:	fef42423          	sw	a5,-24(s0)
   10068:	fe042223          	sw	zero,-28(s0)
   1006c:	fe442783          	lw	a5,-28(s0)
   10070:	00279793          	slli	a5,a5,0x2
   10074:	fef42023          	sw	a5,-32(s0)
   10078:	fe042783          	lw	a5,-32(s0)
   1007c:	fe842703          	lw	a4,-24(s0)
   10080:	00ef7f33          	and	t5,t5,a4
   10084:	00ff6f33          	or	t5,t5,a5
   10088:	001f7793          	andi	a5,t5,1
   1008c:	fcf42e23          	sw	a5,-36(s0)
   10090:	002f7793          	andi	a5,t5,2
   10094:	fcf42c23          	sw	a5,-40(s0)
   10098:	fd842783          	lw	a5,-40(s0)
   1009c:	04078a63          	beqz	a5,100f0 <main+0x9c>
   100a0:	fdc42783          	lw	a5,-36(s0)
   100a4:	04078663          	beqz	a5,100f0 <main+0x9c>
   100a8:	00100793          	li	a5,1
   100ac:	fef42223          	sw	a5,-28(s0)
   100b0:	fe442783          	lw	a5,-28(s0)
   100b4:	00279793          	slli	a5,a5,0x2
   100b8:	fef42023          	sw	a5,-32(s0)
   100bc:	fe042783          	lw	a5,-32(s0)
   100c0:	fe842703          	lw	a4,-24(s0)
   100c4:	00ef7f33          	and	t5,t5,a4
   100c8:	00ff6f33          	or	t5,t5,a5
   100cc:	fe042623          	sw	zero,-20(s0)
   100d0:	0100006f          	j	100e0 <main+0x8c>
   100d4:	fec42783          	lw	a5,-20(s0)
   100d8:	00178793          	addi	a5,a5,1
   100dc:	fef42623          	sw	a5,-20(s0)
   100e0:	fec42703          	lw	a4,-20(s0)
   100e4:	06300793          	li	a5,99
   100e8:	fee7d6e3          	bge	a5,a4,100d4 <main+0x80>
   100ec:	0240006f          	j	10110 <main+0xbc>
   100f0:	fe042223          	sw	zero,-28(s0)
   100f4:	fe442783          	lw	a5,-28(s0)
   100f8:	00279793          	slli	a5,a5,0x2
   100fc:	fef42023          	sw	a5,-32(s0)
   10100:	fe042783          	lw	a5,-32(s0)
   10104:	fe842703          	lw	a4,-24(s0)
   10108:	00ef7f33          	and	t5,t5,a4
   1010c:	00ff6f33          	or	t5,t5,a5
   10110:	f79ff06f          	j	10088 <main+0x34>
 
```

<br />
The above assembly code was run on a Python script to find the different instructions used:
<br />

```
Number of different instructions: 11
List of unique instructions:
slli
sw
lw
addi
and
li
andi
or
beqz
bge
j

```

## Spike Simulation

Now spike simulation is done using following commands.<br />

```
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out motion.c
spike pk out

```

Here, We have **two inputs** and only **one output**, so there are only **four** test cases and out of those four only **one** of them will result in the output being high and in the rest of the three cases, the output is expected as low.For the sake of simulation in spice we are not using an infinite loop but just one iteration of it.<br />
For spike simulation, the two inputs are hard coded for the four test cases.<br />

### For Both Main Switch and Sensor **HIGH** the Spike simulation output is shown below:
This is the only case in which output is of a High value.There are very small logic LOWs in the output high due to the masking we have done.<br />

![Screenshot from 2023-10-25 15-11-07](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/00767b2b-64dd-4495-bce0-1b5a6a5f8e87)

### When Main supply is **ON** and Sensor is **LOW** :
In this case the Output is shown LOW as there is no motion sensed and input sensor is LOW.<br />
![Screenshot from 2023-10-25 15-11-53](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/700a21b7-1bdc-45b7-97c3-b415e7ae0834)

### Remaining two test cases where the main switch is **OFF** are shown below:
In these two cases the main switch is OFF so by default regardless of input sensor output will stay LOW.<br />
![Screenshot from 2023-10-25 15-12-38](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/95be1cb3-b8fa-4284-94a5-b853a0912257)
![Screenshot from 2023-10-25 15-13-05](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/ec0880fa-0367-4274-9ace-482b9420bfda)

## Functional Verification on GTKWave

Since the core is generated we have to check for the functionality in GTKwave. Nessasary modifications must be made in the testbench and the following observations were made.<br />

### The below screenshot shows the only case where in output will be high
i.e if both the input pins be high the output will be high.The delay in the output is due to a delay given in the testbench.<br />

![Screenshot from 2023-10-27 14-11-34](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/ae80f687-0bad-4ef8-be25-a1e8dd72dd60)

The output is becoming high at ```fe042623``` as shown below.<br />

![Screenshot from 2023-10-31 11-21-15](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/92181914-d999-4d55-b9aa-342f0ca57357)

The below screenshot illustrates the change in instructions throughout.<br />
![image](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/e421e2c3-4772-48a5-af57-6ad54f7c4994)


### The below screenshots are of mutiple possible cases of inputs
We see the input ```11``` produces a more Width in ouput waveform because there is a small delay in the design.This casusd the output High of input ```11``` to be of more width that compared to other inputs like ```00``` ,```01``` and ```10```.<br /> 
![Screenshot from 2023-10-27 11-42-21](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/e16810a4-d899-4c6a-ad19-b6cc16681279)

The output is becoming high at ```fe042623``` as shown below.The This is the same instruction at different instances of which output becomes 1.<br />

![Screenshot from 2023-10-31 11-18-40](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/5a0b44e9-9ae9-4802-bed8-f1abba7be76c)

When the output is becoming low  the instruction is ```00FF6f33``` as shown below.<br />
Here the input is ```01``` and hence will lead to a LOW output.<br />

![Screenshot from 2023-10-31 11-16-25](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/19cbdc0b-fafd-486b-b283-b93865b7d17a)


## Instruction Verification

We will consider the link : https://en.wikichip.org/wiki/risc-v/registers for reference<br />

$signal$43, $signa$45, and $signal$58 are essentially registers. $signal$43 holds the hardwired wire zero registers (x0), $signal$45 stores the stack pointer (x2) register, and $signal$58 represents the a5 register.This can be infered from the above link.<br />

Some of the instructions in the above assembly code were tested in GTKWave and was verified.<br />

### addi sp,sp,-48

Here we will conside the assembly code line:<br />
```10054:	fd010113          	addi	sp,sp,-48```  <br />

The $signal$45 is the stack pointer and the value at the instuction ```fd010113``` is 000000CF which is 207.

![Screenshot from 2023-10-27 15-01-45](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/6c0b4fd0-7504-499a-ae33-85ac4f3521c0)

### li	a5,-5

Here we will conside the assembly code line:<br />
```10060:	ffb00793          	li	a5,-5``` <br />

The $signal$58 is a5 register and the value at instruction ```ffb00793``` is FFFFFFFB which is -5.

![Screenshot from 2023-10-27 15-06-07](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/794c62bb-936e-4cd7-bf68-afe40992d9c6)

### addi	s0,sp,48


```1005c:	03010413          	addi	s0,sp,48``` <br />
This instruction comes after the ```addi sp,sp,-48``` and  ```sw s0,44(sp)``` instructions.<br />

We can see for the instruction```03010413``` in the register s0 which is $signal$53 will be 000000FF which is 255.

![addi_48](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/88b8a730-7e93-4fba-b0ee-084d6f2e22d8)


## Gate Level Synthesis

Here we do Synthesis of our processor on yosys using the following commands:

```
read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib 
read_verilog processor.v 
synth -top wrapper
dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib 
abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
write_verilog <filename.v>

```

The following Command is used to run the synthesized netlist along with primitives.<br />

```
iverilog -o test testbench.v synth_processor_test.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v
```

The following waveforms are of GLS Simulation obtained using GTKWave and the same output is obtained as Functional Verification.<br />

![Screenshot from 2023-10-30 23-48-52](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/0a667943-7878-4c82-b6b7-32a64bc0ebd5)

![Screenshot from 2023-10-30 23-56-55](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/3cee3b94-90b0-43fa-a745-163290dd841b)

The following screenshot is of the wrapper module using the following command in yosys

```
show wrapper
```
![Screenshot from 2023-10-31 00-07-07](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/b79a8e6d-b681-425e-a010-ac37665ceaa5)


# Physical Design

Place and Route (PnR) is the core of any ASIC implementation and Openlane flow integrates into it several key open source tools which perform each of the respective stages of PnR. Below are the stages and the respective tools that are called by openlane for the functionalities as described:<br />

![Screenshot from 2023-11-13 16-44-36](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/79a6e0fc-976b-4523-bf4c-5133c770230e)


- Synthesis
  - Generating gate-level netlist
  -  Performing cell mapping
  -   Performing pre-layout STA
- Floorplaning
  - Defining the core area for the macro as well as the cell sites and the tracks
  - Placing the macro input and output ports
  - Generating the power distribution network
- Placement
  - Performing global placemen
  - Perfroming detailed placement to legalize the globally placed components
- Clock Tree Synthesis
  - Synthesizing the clock tree
- Routing
  - Performing global routing to generate a guide file for the detailed router
  - Performing detailed routing
- GDSII
  - Streaming out the final GDSII layout file from the routed def
 
## Preparing The Design

Preparing the design and including the lef files: The commands to prepare the design and overwite in a existing run folder the reports and results along with the command to include the lef files is given below:
<br />
``` sed -i's/max_transition   :0.04/max_transition   :0.75'*/*.lib```

```
make mount
%./flow.tcl -interactive
% package require openlane 0.9
% prep -design project

```

![Screenshot from 2023-11-13 12-03-01](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/d775bdfe-dfcd-45f6-bca4-f6987fc5f3e5)


## Synthesis

Logic synthesis uses the RTL netlist to perform HDL technology mapping. The synthesis process is normally performed in two major steps: <br />

1. GTECH Mapping – Consists of mapping the HDL netlist to generic gates what are used to perform logical optimization based on AIGERs and other topologies created from the generic mapped netlist.
2. Technology Mapping – Consists of mapping the post-optimized GTECH netlist to standard cells described in the PDK.

To synthesize the code run the following command.<br />

```
run_synthesis
```
![Screenshot from 2023-11-13 12-04-11](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/04a3bd31-84d6-41a5-896a-329ec4497358)

Synthesis report:<br />

![Screenshot from 2023-11-13 17-01-50](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/47a7fbd8-1141-47a5-ad84-8dc3158ffedf)


## Floorplan

Goal is to plan the silicon area and create a robust power distribution network (PDN) to power each of the individual components of the synthesized netlist. In addition, macro placement and blockages must be defined before placement occurs to ensure a legalized GDS file. In power planning we create the ring which is connected to the pads which brings power around the edges of the chip. We also include power straps to bring power to the middle of the chip using higher metal layers which reduces IR drop and electro-migration problem.<br />

Following command helps to run floorplan:<br />

``` run_floorplan ```

![Screenshot from 2023-11-13 12-04-33](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/ac43bcce-3ce5-40bd-a479-8f2cf9a04023)

We can check the layout with magic with the following command.<br />

```
magic -T /home/emil/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```

![Screenshot from 2023-11-13 12-05-32](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/073c9b0b-d217-4dba-94bf-ff4c05730f8e)

### Die Area (post floorplan)

![Screenshot from 2023-11-13 12-11-08](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/c5f659df-e71b-4d00-8713-cd43d7ee762a)

### Core Area (post floorplan)

![Screenshot from 2023-11-13 12-10-40](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/6436934e-a94b-4e65-a187-024ff7284056)


## Placement

Place the standard cells on the floorplane rows, aligned with sites defined in the technology lef file. Placement is done in two steps: Global and Detailed. In Global placement tries to find optimal position for all cells but they may be overlapping and not aligned to rows, detailed placement takes the global placement and legalizes all of the placements trying to adhere to what the global placement wants. The next step in the OpenLANE ASIC flow is placement. The synthesized netlist is to be placed on the floorplan. Placement is perfomed in 2 stages:<br />

1. Global Placement
2. Detailed Placement

run the following command to run the placement:<br />

```
run_placement
```

![Screenshot from 2023-11-13 12-12-28](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/e3d7f006-8ce5-4a58-932b-b82ba12d527d)

Now after placement we can see the layout in the placement directory. We view it with magic.<br />
We can check the layout with magic with the following command.<br />

```
magic -T /home/emil/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```

![Screenshot from 2023-11-13 12-12-29](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/6fa8c424-fa86-4754-9997-d769773e5242)

## Clock Tree Synthesis

Clock tree synteshsis is used to create the clock distribution network that is used to deliver the clock to all sequential elements. The main goal is to create a network with minimal skew across the chip. H-trees are a common network topology that is used to achieve this goal.<br />

The purpose of building a clock tree is enable the clock input to reach every element and to ensure a zero clock skew. H-tree is a common methodology followed in CTS.<br />
Following command is used to run CTS.<br />

```
run_cts
```

![Screenshot from 2023-11-13 12-13-47](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/7074a451-cc58-42f7-bf1c-7de42f521b61)

### Timing Report

![Screenshot from 2023-11-13 12-15-50](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/97f5c45e-fd9a-45ef-9909-09dff5e24826)

### Area Report

![Screenshot from 2023-11-13 12-16-30](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/6326d3ee-eae5-4c34-83c8-4b7d356153be)

### Skew Report

![Screenshot from 2023-11-13 12-17-09](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/8d1f3b81-3662-425f-aca2-ee1f1fab3587)

### Power Report

![Screenshot from 2023-11-13 12-17-21](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/375961c3-47d3-4939-9692-c82caf4ab5dc)

## Power distribution

The command ```gen_pdn``` is used to get the power distribution network.

![Screenshot from 2023-11-13 12-18-54](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/98b53302-47aa-4474-a967-e4ab095a889e)

## Routing

Implements the interconnect system between standard cells using the remaining available metal layers after CTS and PDN generation. The routing is performed on routing grids to ensure minimal DRC errors.<br />

OpenLANE uses the TritonRoute tool for routing. There are 2 stages of routing:<br />
1. Global Routing
2. Detailed Routing

In Global Routing Routing region is divided into rectangle grids which are represented as course 3D routes (Fastroute tool).<br />
In Detailed Finer grids and routing guides used to implement physical wiring (TritonRoute tool).<br />

Run the following command to run the routing<br />

```
run_routing
```
After completion it should show the following messages.Here we see no DRC violations.<br />

![Screenshot from 2023-11-13 13-40-10](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/cfb339b8-17e9-484c-a7f6-2c4ac9cb0b50)

We can check the routed layout with magic with the following command.<br />

```
magic -T /home/emil/.volare/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &
```

![Screenshot from 2023-11-13 10-20-28](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/5b2878dd-8bc6-4132-b555-e62787edc4b8)

![Screenshot from 2023-11-13 10-22-48](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/22980daf-f782-44d4-9507-5461f3237d23)

![Screenshot from 2023-11-13 10-21-30](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/9b74b0e9-43e3-425b-ba7c-1d2fef61f3c9)

### Post-Routing Timing Report

![Screenshot from 2023-11-13 15-45-52](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/9bee6add-7a7f-4992-a902-b4a9b7b45cfc)

### Post-Routing Area Report

![Screenshot from 2023-11-13 15-46-10](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/1d93144f-b757-4421-9f7c-8380ee6d7ca9)

### Post-Routing Power Report

![Screenshot from 2023-11-13 15-46-59](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/a06b7c44-d415-4a04-a032-eadc89d9b627)

### DRC Check Report

![Screenshot from 2023-11-13 15-51-28](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/7e40ff5f-c094-47f7-8791-6644f803de64)

## Performance Calculation

Given a Clock period of 25ns in Json file , setup slack we got after routing is 5.59ns.<br />

```
				1
Max Performance =  ------------------------
                     clock period - slack(setup)
```

```
Max Performance = 51.5198 MHz

```

## Signoff

Following commands are run post routing with no DRC violations

```
run_magic
run_magic_spice_export
run_magic_drc
run_antenna_check

```

![Screenshot from 2023-11-13 14-02-28](https://github.com/mrdunker/IIITB_auto_room_lc/assets/38190245/0b89ae19-6589-4dcd-8bdc-59eb5745f2e3)

## Non-Interactive flow

Run the following commands to do the non-interactive flow.<br />

```
cd Desktop/OpenLane 
make mount
./flow.tcl -design project

```

## Acknowledgement

1. Kunal Ghosh,Co-founder,VSD Corp. Pvt. Ltd.
2. Mayank Kabra,Founder, Chipcron Pvt. Ltd.
3. Sumanto Kar,VSD Corp.
4. Alwin Shaju, Colleague, IIIT-Bangalore
5. Kanish R, Colleague, IIIT-Bangalore

## References

1. https://github.com/SakethGajawada/RISCV-GNU
2. https://github.com/kunalg123
3. https://github.com/The-OpenROAD-Project/OpenLane
4. https://openlane.readthedocs.io/en/latest/

