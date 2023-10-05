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
motion.o:     file format elf64-littleriscv


Disassembly of section .text:

00000000000100b0 <register_fini>:
   100b0:	ffff0797          	auipc	a5,0xffff0
   100b4:	f5078793          	addi	a5,a5,-176 # 0 <register_fini-0x100b0>
   100b8:	00078863          	beqz	a5,100c8 <register_fini+0x18>
   100bc:	00000517          	auipc	a0,0x0
   100c0:	14850513          	addi	a0,a0,328 # 10204 <__libc_fini_array>
   100c4:	0f80006f          	j	101bc <atexit>
   100c8:	00008067          	ret

00000000000100cc <_start>:
   100cc:	00002197          	auipc	gp,0x2
   100d0:	d4418193          	addi	gp,gp,-700 # 11e10 <__global_pointer$>
   100d4:	f6018513          	addi	a0,gp,-160 # 11d70 <_edata>
   100d8:	f9818613          	addi	a2,gp,-104 # 11da8 <__BSS_END__>
   100dc:	40a60633          	sub	a2,a2,a0
   100e0:	00000593          	li	a1,0
   100e4:	210000ef          	jal	ra,102f4 <memset>
   100e8:	00000517          	auipc	a0,0x0
   100ec:	11c50513          	addi	a0,a0,284 # 10204 <__libc_fini_array>
   100f0:	0cc000ef          	jal	ra,101bc <atexit>
   100f4:	16c000ef          	jal	ra,10260 <__libc_init_array>
   100f8:	00012503          	lw	a0,0(sp)
   100fc:	00810593          	addi	a1,sp,8
   10100:	00000613          	li	a2,0
   10104:	080000ef          	jal	ra,10184 <main>
   10108:	0c80006f          	j	101d0 <exit>

000000000001010c <__do_global_dtors_aux>:
   1010c:	f601c783          	lbu	a5,-160(gp) # 11d70 <_edata>
   10110:	04079463          	bnez	a5,10158 <__do_global_dtors_aux+0x4c>
   10114:	ffff0797          	auipc	a5,0xffff0
   10118:	eec78793          	addi	a5,a5,-276 # 0 <register_fini-0x100b0>
   1011c:	02078863          	beqz	a5,1014c <__do_global_dtors_aux+0x40>
   10120:	ff010113          	addi	sp,sp,-16
   10124:	00001517          	auipc	a0,0x1
   10128:	4cc50513          	addi	a0,a0,1228 # 115f0 <__FRAME_END__>
   1012c:	00113423          	sd	ra,8(sp)
   10130:	00000097          	auipc	ra,0x0
   10134:	000000e7          	jalr	zero # 0 <register_fini-0x100b0>
   10138:	00813083          	ld	ra,8(sp)
   1013c:	00100793          	li	a5,1
   10140:	f6f18023          	sb	a5,-160(gp) # 11d70 <_edata>
   10144:	01010113          	addi	sp,sp,16
   10148:	00008067          	ret
   1014c:	00100793          	li	a5,1
   10150:	f6f18023          	sb	a5,-160(gp) # 11d70 <_edata>
   10154:	00008067          	ret
   10158:	00008067          	ret

000000000001015c <frame_dummy>:
   1015c:	ffff0797          	auipc	a5,0xffff0
   10160:	ea478793          	addi	a5,a5,-348 # 0 <register_fini-0x100b0>
   10164:	00078c63          	beqz	a5,1017c <frame_dummy+0x20>
   10168:	f6818593          	addi	a1,gp,-152 # 11d78 <object.5473>
   1016c:	00001517          	auipc	a0,0x1
   10170:	48450513          	addi	a0,a0,1156 # 115f0 <__FRAME_END__>
   10174:	00000317          	auipc	t1,0x0
   10178:	00000067          	jr	zero # 0 <register_fini-0x100b0>
   1017c:	00008067          	ret

0000000000010180 <readpindetails>:
   10180:	0000006f          	j	10180 <readpindetails>

0000000000010184 <main>:
   10184:	ff010113          	addi	sp,sp,-16
   10188:	00113423          	sd	ra,8(sp)
   1018c:	ff5ff0ef          	jal	ra,10180 <readpindetails>

0000000000010190 <delaytime>:
   10190:	00000713          	li	a4,0
   10194:	000f46b7          	lui	a3,0xf4
   10198:	24068693          	addi	a3,a3,576 # f4240 <__global_pointer$+0xe2430>
   1019c:	00a05e63          	blez	a0,101b8 <delaytime+0x28>
   101a0:	00068793          	mv	a5,a3
   101a4:	fff7879b          	addiw	a5,a5,-1
   101a8:	fe079ee3          	bnez	a5,101a4 <delaytime+0x14>
   101ac:	0017071b          	addiw	a4,a4,1
   101b0:	fee518e3          	bne	a0,a4,101a0 <delaytime+0x10>
   101b4:	00008067          	ret
   101b8:	00008067          	ret

00000000000101bc <atexit>:
   101bc:	00050593          	mv	a1,a0
   101c0:	00000693          	li	a3,0
   101c4:	00000613          	li	a2,0
   101c8:	00000513          	li	a0,0
   101cc:	2040006f          	j	103d0 <__register_exitproc>

00000000000101d0 <exit>:
   101d0:	ff010113          	addi	sp,sp,-16
   101d4:	00000593          	li	a1,0
   101d8:	00813023          	sd	s0,0(sp)
   101dc:	00113423          	sd	ra,8(sp)
   101e0:	00050413          	mv	s0,a0
   101e4:	298000ef          	jal	ra,1047c <__call_exitprocs>
   101e8:	f4818793          	addi	a5,gp,-184 # 11d58 <_global_impure_ptr>
   101ec:	0007b503          	ld	a0,0(a5)
   101f0:	05853783          	ld	a5,88(a0)
   101f4:	00078463          	beqz	a5,101fc <exit+0x2c>
   101f8:	000780e7          	jalr	a5
   101fc:	00040513          	mv	a0,s0
   10200:	3a0000ef          	jal	ra,105a0 <_exit>

0000000000010204 <__libc_fini_array>:
   10204:	fe010113          	addi	sp,sp,-32
   10208:	00813823          	sd	s0,16(sp)
   1020c:	00001797          	auipc	a5,0x1
   10210:	40478793          	addi	a5,a5,1028 # 11610 <__fini_array_end>
   10214:	00001417          	auipc	s0,0x1
   10218:	3f440413          	addi	s0,s0,1012 # 11608 <__init_array_end>
   1021c:	408787b3          	sub	a5,a5,s0
   10220:	00913423          	sd	s1,8(sp)
   10224:	00113c23          	sd	ra,24(sp)
   10228:	4037d493          	srai	s1,a5,0x3
   1022c:	02048063          	beqz	s1,1024c <__libc_fini_array+0x48>
   10230:	ff878793          	addi	a5,a5,-8
   10234:	00878433          	add	s0,a5,s0
   10238:	00043783          	ld	a5,0(s0)
   1023c:	fff48493          	addi	s1,s1,-1
   10240:	ff840413          	addi	s0,s0,-8
   10244:	000780e7          	jalr	a5
   10248:	fe0498e3          	bnez	s1,10238 <__libc_fini_array+0x34>
   1024c:	01813083          	ld	ra,24(sp)
   10250:	01013403          	ld	s0,16(sp)
   10254:	00813483          	ld	s1,8(sp)
   10258:	02010113          	addi	sp,sp,32
   1025c:	00008067          	ret

0000000000010260 <__libc_init_array>:
   10260:	fe010113          	addi	sp,sp,-32
   10264:	00813823          	sd	s0,16(sp)
   10268:	01213023          	sd	s2,0(sp)
   1026c:	00001417          	auipc	s0,0x1
   10270:	38840413          	addi	s0,s0,904 # 115f4 <__preinit_array_end>
   10274:	00001917          	auipc	s2,0x1
   10278:	38090913          	addi	s2,s2,896 # 115f4 <__preinit_array_end>
   1027c:	40890933          	sub	s2,s2,s0
   10280:	00113c23          	sd	ra,24(sp)
   10284:	00913423          	sd	s1,8(sp)
   10288:	40395913          	srai	s2,s2,0x3
   1028c:	00090e63          	beqz	s2,102a8 <__libc_init_array+0x48>
   10290:	00000493          	li	s1,0
   10294:	00043783          	ld	a5,0(s0)
   10298:	00148493          	addi	s1,s1,1
   1029c:	00840413          	addi	s0,s0,8
   102a0:	000780e7          	jalr	a5
   102a4:	fe9918e3          	bne	s2,s1,10294 <__libc_init_array+0x34>
   102a8:	00001417          	auipc	s0,0x1
   102ac:	35040413          	addi	s0,s0,848 # 115f8 <__init_array_start>
   102b0:	00001917          	auipc	s2,0x1
   102b4:	35890913          	addi	s2,s2,856 # 11608 <__init_array_end>
   102b8:	40890933          	sub	s2,s2,s0
   102bc:	40395913          	srai	s2,s2,0x3
   102c0:	00090e63          	beqz	s2,102dc <__libc_init_array+0x7c>
   102c4:	00000493          	li	s1,0
   102c8:	00043783          	ld	a5,0(s0)
   102cc:	00148493          	addi	s1,s1,1
   102d0:	00840413          	addi	s0,s0,8
   102d4:	000780e7          	jalr	a5
   102d8:	fe9918e3          	bne	s2,s1,102c8 <__libc_init_array+0x68>
   102dc:	01813083          	ld	ra,24(sp)
   102e0:	01013403          	ld	s0,16(sp)
   102e4:	00813483          	ld	s1,8(sp)
   102e8:	00013903          	ld	s2,0(sp)
   102ec:	02010113          	addi	sp,sp,32
   102f0:	00008067          	ret

00000000000102f4 <memset>:
   102f4:	00f00313          	li	t1,15
   102f8:	00050713          	mv	a4,a0
   102fc:	02c37a63          	bgeu	t1,a2,10330 <memset+0x3c>
   10300:	00f77793          	andi	a5,a4,15
   10304:	0a079063          	bnez	a5,103a4 <memset+0xb0>
   10308:	06059e63          	bnez	a1,10384 <memset+0x90>
   1030c:	ff067693          	andi	a3,a2,-16
   10310:	00f67613          	andi	a2,a2,15
   10314:	00e686b3          	add	a3,a3,a4
   10318:	00b73023          	sd	a1,0(a4)
   1031c:	00b73423          	sd	a1,8(a4)
   10320:	01070713          	addi	a4,a4,16
   10324:	fed76ae3          	bltu	a4,a3,10318 <memset+0x24>
   10328:	00061463          	bnez	a2,10330 <memset+0x3c>
   1032c:	00008067          	ret
   10330:	40c306b3          	sub	a3,t1,a2
   10334:	00269693          	slli	a3,a3,0x2
   10338:	00000297          	auipc	t0,0x0
   1033c:	005686b3          	add	a3,a3,t0
   10340:	00c68067          	jr	12(a3)
   10344:	00b70723          	sb	a1,14(a4)
   10348:	00b706a3          	sb	a1,13(a4)
   1034c:	00b70623          	sb	a1,12(a4)
   10350:	00b705a3          	sb	a1,11(a4)
   10354:	00b70523          	sb	a1,10(a4)
   10358:	00b704a3          	sb	a1,9(a4)
   1035c:	00b70423          	sb	a1,8(a4)
   10360:	00b703a3          	sb	a1,7(a4)
   10364:	00b70323          	sb	a1,6(a4)
   10368:	00b702a3          	sb	a1,5(a4)
   1036c:	00b70223          	sb	a1,4(a4)
   10370:	00b701a3          	sb	a1,3(a4)
   10374:	00b70123          	sb	a1,2(a4)
   10378:	00b700a3          	sb	a1,1(a4)
   1037c:	00b70023          	sb	a1,0(a4)
   10380:	00008067          	ret
   10384:	0ff5f593          	andi	a1,a1,255
   10388:	00859693          	slli	a3,a1,0x8
   1038c:	00d5e5b3          	or	a1,a1,a3
   10390:	01059693          	slli	a3,a1,0x10
   10394:	00d5e5b3          	or	a1,a1,a3
   10398:	02059693          	slli	a3,a1,0x20
   1039c:	00d5e5b3          	or	a1,a1,a3
   103a0:	f6dff06f          	j	1030c <memset+0x18>
   103a4:	00279693          	slli	a3,a5,0x2
   103a8:	00000297          	auipc	t0,0x0
   103ac:	005686b3          	add	a3,a3,t0
   103b0:	00008293          	mv	t0,ra
   103b4:	f98680e7          	jalr	-104(a3)
   103b8:	00028093          	mv	ra,t0
   103bc:	ff078793          	addi	a5,a5,-16
   103c0:	40f70733          	sub	a4,a4,a5
   103c4:	00f60633          	add	a2,a2,a5
   103c8:	f6c374e3          	bgeu	t1,a2,10330 <memset+0x3c>
   103cc:	f3dff06f          	j	10308 <memset+0x14>

00000000000103d0 <__register_exitproc>:
   103d0:	f4818793          	addi	a5,gp,-184 # 11d58 <_global_impure_ptr>
   103d4:	0007b703          	ld	a4,0(a5)
   103d8:	1f873783          	ld	a5,504(a4)
   103dc:	06078063          	beqz	a5,1043c <__register_exitproc+0x6c>
   103e0:	0087a703          	lw	a4,8(a5)
   103e4:	01f00813          	li	a6,31
   103e8:	08e84663          	blt	a6,a4,10474 <__register_exitproc+0xa4>
   103ec:	02050863          	beqz	a0,1041c <__register_exitproc+0x4c>
   103f0:	00371813          	slli	a6,a4,0x3
   103f4:	01078833          	add	a6,a5,a6
   103f8:	10c83823          	sd	a2,272(a6)
   103fc:	3107a883          	lw	a7,784(a5)
   10400:	00100613          	li	a2,1
   10404:	00e6163b          	sllw	a2,a2,a4
   10408:	00c8e8b3          	or	a7,a7,a2
   1040c:	3117a823          	sw	a7,784(a5)
   10410:	20d83823          	sd	a3,528(a6)
   10414:	00200693          	li	a3,2
   10418:	02d50863          	beq	a0,a3,10448 <__register_exitproc+0x78>
   1041c:	00270693          	addi	a3,a4,2
   10420:	00369693          	slli	a3,a3,0x3
   10424:	0017071b          	addiw	a4,a4,1
   10428:	00e7a423          	sw	a4,8(a5)
   1042c:	00d787b3          	add	a5,a5,a3
   10430:	00b7b023          	sd	a1,0(a5)
   10434:	00000513          	li	a0,0
   10438:	00008067          	ret
   1043c:	20070793          	addi	a5,a4,512
   10440:	1ef73c23          	sd	a5,504(a4)
   10444:	f9dff06f          	j	103e0 <__register_exitproc+0x10>
   10448:	3147a683          	lw	a3,788(a5)
   1044c:	00000513          	li	a0,0
   10450:	00c6e633          	or	a2,a3,a2
   10454:	00270693          	addi	a3,a4,2
   10458:	00369693          	slli	a3,a3,0x3
   1045c:	0017071b          	addiw	a4,a4,1
   10460:	30c7aa23          	sw	a2,788(a5)
   10464:	00e7a423          	sw	a4,8(a5)
   10468:	00d787b3          	add	a5,a5,a3
   1046c:	00b7b023          	sd	a1,0(a5)
   10470:	00008067          	ret
   10474:	fff00513          	li	a0,-1
   10478:	00008067          	ret

000000000001047c <__call_exitprocs>:
   1047c:	fb010113          	addi	sp,sp,-80
   10480:	f4818793          	addi	a5,gp,-184 # 11d58 <_global_impure_ptr>
   10484:	01813023          	sd	s8,0(sp)
   10488:	0007bc03          	ld	s8,0(a5)
   1048c:	03313423          	sd	s3,40(sp)
   10490:	03413023          	sd	s4,32(sp)
   10494:	01513c23          	sd	s5,24(sp)
   10498:	01613823          	sd	s6,16(sp)
   1049c:	04113423          	sd	ra,72(sp)
   104a0:	04813023          	sd	s0,64(sp)
   104a4:	02913c23          	sd	s1,56(sp)
   104a8:	03213823          	sd	s2,48(sp)
   104ac:	01713423          	sd	s7,8(sp)
   104b0:	00050a93          	mv	s5,a0
   104b4:	00058b13          	mv	s6,a1
   104b8:	00100a13          	li	s4,1
   104bc:	fff00993          	li	s3,-1
   104c0:	1f8c3903          	ld	s2,504(s8)
   104c4:	02090863          	beqz	s2,104f4 <__call_exitprocs+0x78>
   104c8:	00892483          	lw	s1,8(s2)
   104cc:	fff4841b          	addiw	s0,s1,-1
   104d0:	02044263          	bltz	s0,104f4 <__call_exitprocs+0x78>
   104d4:	00349493          	slli	s1,s1,0x3
   104d8:	009904b3          	add	s1,s2,s1
   104dc:	040b0463          	beqz	s6,10524 <__call_exitprocs+0xa8>
   104e0:	2084b783          	ld	a5,520(s1)
   104e4:	05678063          	beq	a5,s6,10524 <__call_exitprocs+0xa8>
   104e8:	fff4041b          	addiw	s0,s0,-1
   104ec:	ff848493          	addi	s1,s1,-8
   104f0:	ff3416e3          	bne	s0,s3,104dc <__call_exitprocs+0x60>
   104f4:	04813083          	ld	ra,72(sp)
   104f8:	04013403          	ld	s0,64(sp)
   104fc:	03813483          	ld	s1,56(sp)
   10500:	03013903          	ld	s2,48(sp)
   10504:	02813983          	ld	s3,40(sp)
   10508:	02013a03          	ld	s4,32(sp)
   1050c:	01813a83          	ld	s5,24(sp)
   10510:	01013b03          	ld	s6,16(sp)
   10514:	00813b83          	ld	s7,8(sp)
   10518:	00013c03          	ld	s8,0(sp)
   1051c:	05010113          	addi	sp,sp,80
   10520:	00008067          	ret
   10524:	00892783          	lw	a5,8(s2)
   10528:	0084b703          	ld	a4,8(s1)
   1052c:	fff7879b          	addiw	a5,a5,-1
   10530:	04878e63          	beq	a5,s0,1058c <__call_exitprocs+0x110>
   10534:	0004b423          	sd	zero,8(s1)
   10538:	fa0708e3          	beqz	a4,104e8 <__call_exitprocs+0x6c>
   1053c:	31092783          	lw	a5,784(s2)
   10540:	008a16bb          	sllw	a3,s4,s0
   10544:	00892b83          	lw	s7,8(s2)
   10548:	00d7f7b3          	and	a5,a5,a3
   1054c:	0007879b          	sext.w	a5,a5
   10550:	00079e63          	bnez	a5,1056c <__call_exitprocs+0xf0>
   10554:	000700e7          	jalr	a4
   10558:	00892783          	lw	a5,8(s2)
   1055c:	f77792e3          	bne	a5,s7,104c0 <__call_exitprocs+0x44>
   10560:	1f8c3783          	ld	a5,504(s8)
   10564:	f92782e3          	beq	a5,s2,104e8 <__call_exitprocs+0x6c>
   10568:	f59ff06f          	j	104c0 <__call_exitprocs+0x44>
   1056c:	31492783          	lw	a5,788(s2)
   10570:	1084b583          	ld	a1,264(s1)
   10574:	00d7f7b3          	and	a5,a5,a3
   10578:	0007879b          	sext.w	a5,a5
   1057c:	00079c63          	bnez	a5,10594 <__call_exitprocs+0x118>
   10580:	000a8513          	mv	a0,s5
   10584:	000700e7          	jalr	a4
   10588:	fd1ff06f          	j	10558 <__call_exitprocs+0xdc>
   1058c:	00892423          	sw	s0,8(s2)
   10590:	fa9ff06f          	j	10538 <__call_exitprocs+0xbc>
   10594:	00058513          	mv	a0,a1
   10598:	000700e7          	jalr	a4
   1059c:	fbdff06f          	j	10558 <__call_exitprocs+0xdc>

00000000000105a0 <_exit>:
   105a0:	00000593          	li	a1,0
   105a4:	00000613          	li	a2,0
   105a8:	00000693          	li	a3,0
   105ac:	00000713          	li	a4,0
   105b0:	00000793          	li	a5,0
   105b4:	05d00893          	li	a7,93
   105b8:	00000073          	ecall
   105bc:	00054463          	bltz	a0,105c4 <_exit+0x24>
   105c0:	0000006f          	j	105c0 <_exit+0x20>
   105c4:	ff010113          	addi	sp,sp,-16
   105c8:	00813023          	sd	s0,0(sp)
   105cc:	00050413          	mv	s0,a0
   105d0:	00113423          	sd	ra,8(sp)
   105d4:	4080043b          	negw	s0,s0
   105d8:	00c000ef          	jal	ra,105e4 <__errno>
   105dc:	00852023          	sw	s0,0(a0)
   105e0:	0000006f          	j	105e0 <_exit+0x40>

00000000000105e4 <__errno>:
   105e4:	f5818793          	addi	a5,gp,-168 # 11d68 <_impure_ptr>
   105e8:	0007b503          	ld	a0,0(a5)
   105ec:	00008067          	ret


```

<br />
The above assembly code was run on a Python script to find the different instructions used:
<br />

```
Number of different instructions: 37
List of unique instructions:
slli
sw
lui
bnez
bne
blt
sd
j
auipc
jalr
bltz
negw
lw
jr
beq
addiw
bltu
srai
sllw
beqz
blez
ld
bgeu
add
sub
sext.w
sb
or
mv
li
and
addi
andi
ret
lbu
ecall
jal

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

