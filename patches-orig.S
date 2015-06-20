@---------------------------------------------------------------------------------
@	Patch file format
@
@	0	4	Header - 'PPOR'
@	4	4	offset to index
@
@	index entry
@	0	4	Firmware revision this patch set applies to
@	8	4	Offset in file to patch set
@
@	patch set
@	0	4	Header	- 'PTCH'
@	4	4	Number of patches
@
@	for each patch
@	0	4	size of patch
@	4	4	offset in user settings to patch
@	8	...	patch data
@---------------------------------------------------------------------------------

	.arm
	.text

	.global	_start
@---------------------------------------------------------------------------------
_start:
	.word	0x524f5050
	.word	index

@---------------------------------------------------------------------------------
patch_G_W_description:
@---------------------------------------------------------------------------------

	.asciz	"4.x    Launcher.dat"

@---------------------------------------------------------------------------------
patch_G_W_1:
@---------------------------------------------------------------------------------

	.word	GW_1_end - GW_1_start
	.word	0

@---------------------------------------------------------------------------------
GW_1_start:
@---------------------------------------------------------------------------------

	.word 0x0010F2B9
	.word 0x00272BAE
	.word 0xBADC0DED
	.word 0x0018F19C
	.word 0x0010B690
	.word 0x00FAB000
	.word 0x00200200
	.word 0x0010F2B9
	.word 0x00279000
	.word 0x00000001
	.word 0x001549E1
	.word 0x00276F38  @ Offset for launcher path
	.word 0x001B82AC
	.word 0x0018D5DC
	.word 0x00278340
	.word 0x00100200
	.word 0x000048CC
	.word 0x00143D60
	.word 0x0010F2B9
	.word 0x00279000
	.word 0x002B0000
	.word 0x0010538C
	.word 0x00009000
	.word 0x001002F9
	.word 0x001002F9
	.word 0x001002F9
	.word 0x001002F9
	.word 0x001549E1
	.word 0x00000000
	.word 0x001549E1
	.word 0x00279020
	.word 0x001B3958
	.word 0x002104E5
	.word 0x0019DA00
	.word 0x00017500
	.word 0x0021DF86
	.word 0x001AC100
	.word 0x001DDA22
	.word 0x001B449B
	.word 0x00100100
	.word 0x00144CBC
	.word 0x002B0000
	.word 0x00009000
	.word 0x001549E1
	.word 0x77777777
	.word 0x0022EFAC
	.word 0x00105C88
	.word 0x000E0000
	.word 0x00250390
	.word 0x001EFAC0
	.word 0x0016FE91
	.word 0x0010538C
	.word 0x00036B28
	.word 0x00143D60

@---------------------------------------------------------------------------------
GW_1_end:
@---------------------------------------------------------------------------------

@---------------------------------------------------------------------------------
patch_G_W_2:
@---------------------------------------------------------------------------------

	.word	GW_2_end - GW_2_start
	.word	0x1b4

@---------------------------------------------------------------------------------
GW_2_start:
@---------------------------------------------------------------------------------

	.word 0x0010F2B9
	.word 0x0001FE00
	.word 0x00000100
	.word 0x001C4FC4
	.word 0x00279400
	.word 0x001334FC
	.word 0xFFFFFFFE
	.word 0x001549B1
	.word 0x001002F9
	.word 0x00000000
	.word 0x00279400
	.word 0x00143D8C
	.word 0x0000002D
	.word 0x0010B690
	.word 0x002793F0
	.word 0x002793E8
	.word 0x00000000
	.word 0x0019FB09

@---------------------------------------------------------------------------------
GW_2_end:
@---------------------------------------------------------------------------------

.ascii "GW_END"

@---------------------------------------------------------------------------------
patch_R_X_description:
@---------------------------------------------------------------------------------

	.asciz	"4.x     rxTools.dat"

@---------------------------------------------------------------------------------
patch_R_X_1:
@---------------------------------------------------------------------------------

	.word	RX_1_end - RX_1_start
	.word	0

@---------------------------------------------------------------------------------
RX_1_start:
@---------------------------------------------------------------------------------

	.word 0x0010F2B9
	.word 0x00272BAE
	.word 0x00000001
	.word 0x0018F19C
	.word 0xF027949C
	.word 0xF027949C
	.word 0x0010538C
	.word 0x0010F2B9
	.word 0x00279000
	.word 0x00000001
	.word 0x001549E1
	.word 0x00295E0C
	.word 0x001B82AC
	.word 0x00009000
	.word 0x001334FC
	.word 0x00009000
	.word 0x002F003A
	.word 0x0010538C
	.word 0x0010F2B9
	.word 0x00279000
	.word 0x002B0000
	.word 0x001549E1
	.word 0x00279020
	.word 0x0010538C
	.word 0x00009000
	.word 0x001B3958
	.word 0x00144CBC
	.word 0x00279020
	.word 0x0010F2B9
	.word 0x0010F2B9
	.word 0x0001FE00
	.word 0x00000100
	.word 0x0016FE91
	.word 0x0022EFAC
	.word 0x00144CBC
	.word 0x002B0000
	.word 0x00009000
	.word 0x001549E1
	.word 0x0022EFAC
	.word 0x0022EFAC
	.word 0x0010538C
	.word 0x00001460
	.word 0x00143D60
	.word 0x00009000
	.word 0x001002F9
	.word 0x0010538C
	.word 0x00036B40
	.word 0x00143D60
	.word 0x00036B40
	.word 0x0010538C
	.word 0x001549E1
	.word 0x00144CBC
	.word 0x0DE01319
	.word 0x0010F2B9

@---------------------------------------------------------------------------------
RX_1_end:
@---------------------------------------------------------------------------------

@---------------------------------------------------------------------------------
patch_R_X_2:
@---------------------------------------------------------------------------------

	.word	RX_2_end - RX_2_start
	.word	0x1b4

@---------------------------------------------------------------------------------
RX_2_start:
@---------------------------------------------------------------------------------

	.word 0x0010F2B9
	.word 0x0001FE00
	.word 0x00000100
	.word 0x001549E1
	.word 0x00279400
	.word 0x001334FC
	.word 0x3A370052
	.word 0x0010538C
	.word 0xF027949C
	.word 0x00143D60
	.word 0x003F0001
	.word 0x00009000
	.word 0x002F003A
	.word 0x00610064
	.word 0x0018F19C
	.word 0x0072001D
	.word 0x3A370052
	.word 0x00279000

@---------------------------------------------------------------------------------
RX_2_end:
@---------------------------------------------------------------------------------


@---------------------------------------------------------------------------------
patch_4_x_description:
@---------------------------------------------------------------------------------
	.asciz	"4.x MsetForBoss.dat"

#define	P4_LOAD_ADDRESS		0x00279400
#define	P4_S2_LOAD_ADDRESS	0x002b0000
#define	P4_DATA_ADDRESS		0x00279000
#define P4_READ_SIZE		0x9000

@---------------------------------------------------------------------------------
patch_4_x_1:
@---------------------------------------------------------------------------------
	.word	p4_1_end - p4_1_start
	.word	0

@---------------------------------------------------------------------------------
p4_1_start:
@---------------------------------------------------------------------------------
	.word 0x0010f2b9		@ pop {r0,r2,pc}
	.word 0x00272bae		@ (r0) (char * "YS:")
	.word 0xdeadbeef		@ (r2)
	.word 0x0018f19c		@ FS_MOUNTSDMC(), ends with  ldmfd   sp!, {r3-r5,pc}
	.word 0xdeadbeef		@ (r3)
	.word 0xdeadbeef		@ (r4)
	.word 0xdeadbeef		@ (r5)
	.word 0x0010f2b9		@ pop {r0,r2,pc}
	.word P4_DATA_ADDRESS		@ (r0) _this
	.word 0x00000001		@ (r2) openflags
	.word 0x001549e1		@ pop {r1,pc}
	.word 0x00276f64		@ (utf16* "YS:/MsetForBoss.dat")
	.word 0x001b82ac		@ IFile_Open(): r0=_this r1=UTF16 path r2=openflags, ends with ldmfd sp!, {r4-r8,pc}
	.word 0xdeadbeef		@ (r4)
	.word 0xdeadbeef		@ (r5)
	.word 0xdeadbeef		@ (r6)
	.word 0xdeadbeef		@ (r7)
	.word 0xdeadbeef		@ (r8)
	.word 0x0010f2b9		@ pop {r0,r2,pc}
	.word P4_DATA_ADDRESS		@ (r0) _this
	.word P4_S2_LOAD_ADDRESS	@ (r2) buffer
	.word 0x001549e1		@ pop {r1,pc}
	.word P4_DATA_ADDRESS + 32	@ (r1) &readbytes
	.word 0x0010538c		@ pop {r3,pc}
	.word P4_READ_SIZE		@ (r3) size
	.word 0x001b3958		@ IFile_Read(): r0=_this r1=&readbytes r2=readbuf r3=size, ends with ldmfd sp!,{r4-r9,pc}
					@ This reads the first READ_SIZE bytes from the file to S2_LOAD_ADDRESS.
	.word 0xdeadbeef		@ (r4)
	.word 0xdeadbeef		@ (r5)
	.word 0xbadc0ded		@ (r6) - gets overwritten with counter and CRC1
	.word 0xdeadbeef		@ (r7)
	.word 0xdeadbeef		@ (r8)
	.word 0xdeadbeef		@ (r9)
	.word 0x0010538c		@ pop {r3,pc}

	.word (P4_S2_LOAD_ADDRESS-(P4_LOAD_ADDRESS+p4_1_end-p4_1_start))

	.word 0x00143d60		@ add sp,sp,r3 | ldr pc,[sp],#4
@---------------------------------------------------------------------------------
p4_1_end:
@---------------------------------------------------------------------------------

@---------------------------------------------------------------------------------
patch_4_x_2:
@---------------------------------------------------------------------------------
	.word	p4_2_end - p4_2_start
	.word	0x1b4

@---------------------------------------------------------------------------------
p4_2_start:
@---------------------------------------------------------------------------------
	.word 0x0010f2b9			@ pop {r0,r2,pc}
	.word 0x0001fe00			@ (r0) offset in firmware
	.word 0x00000100			@ (r2) size
	.word 0x001549e1			@ pop {r1,pc}
	.word P4_LOAD_ADDRESS			@ (r1) dst
	.word 0x001334fc			@ cfg:nor::ReadData(offset,dst,size), ends with ldmfd   sp!,{r4,pc}
	.word 0xdeadbeef			@ (r4)
	.word 0x0010538c			@ pop {r3,pc}
	.word P4_LOAD_ADDRESS - 0x0fffff64	@ (r3)
	.word 0x00143d60			@ add sp,sp,r3 | ldr pc,[sp],#4
@---------------------------------------------------------------------------------
p4_2_end:
@---------------------------------------------------------------------------------

@---------------------------------------------------------------------------------
patch_6_x_description:
@---------------------------------------------------------------------------------
	.asciz	"4.x   ropCustom.txt"

@---------------------------------------------------------------------------------
#define	P6_DATAADR	0x00287000
#define	P6_SECPAYADR	0x00297000
#define	P6_TRDPAYADR	0x00290000
@---------------------------------------------------------------------------------

@---------------------------------------------------------------------------------
patch_6_x_1:
@---------------------------------------------------------------------------------
	.word	p6_1_end - p6_1_start
	.word	0

@---------------------------------------------------------------------------------
p6_1_start:
@---------------------------------------------------------------------------------
	.word 0x0010f2b9		@ pop {r0,r2,pc}
	.word 0x00272bae		@ (r0) (char * "YS:")
	.word 0xdeadbeef		@ (r2)
	.word 0x0018f19c		@ FS_MOUNTSDMC(), ends with  ldmfd   sp!, {r3-r5,pc}
	.word 0xdeadbeef		@ (r3)
	.word 0xdeadbeef		@ (r4)
	.word 0xdeadbeef		@ (r5)
	.word 0x0010f2b9		@ pop {r0,r2,pc}
	.word P4_DATA_ADDRESS		@ (r0) _this
	.word 0x00000001		@ (r2) openflags
	.word 0x001549e1		@ pop {r1,pc}
	.word 0x00295e64		@ (utf16* "YS:/custom!") 64 5E 29 00
	.word 0x001b82ac		@ IFile_Open(): r0=_this r1=UTF16 path r2=openflags, ends with ldmfd sp!, {r4-r8,pc}
	.word 0xdeadbeef		@ (r4)
	.word 0xdeadbeef		@ (r5)
	.word 0xdeadbeef		@ (r6)
	.word 0xdeadbeef		@ (r7)
	.word 0xdeadbeef		@ (r8)
	.word 0x0010f2b9		@ pop {r0,r2,pc}
	.word P4_DATA_ADDRESS		@ (r0) _this
	.word P4_S2_LOAD_ADDRESS	@ (r2) buffer
	.word 0x001549e1		@ pop {r1,pc}
	.word P4_DATA_ADDRESS + 32	@ (r1) &readbytes
	.word 0x0010538c		@ pop {r3,pc}
	.word P4_READ_SIZE		@ (r3) size
	.word 0x001b3958		@ IFile_Read(): r0=_this r1=&readbytes r2=readbuf r3=size, ends with ldmfd sp!,{r4-r9,pc}
					@ This reads the first READ_SIZE bytes from the file to S2_LOAD_ADDRESS.
	.word 0xdeadbeef		@ (r4)
	.word 0xdeadbeef		@ (r5)
	.word 0xbadc0ded		@ (r6) - gets overwritten with counter and CRC1
	.word 0xdeadbeef		@ (r7)
	.word 0xdeadbeef		@ (r8)
	.word 0xdeadbeef		@ (r9)
	.word 0x0010538c		@ pop {r3,pc}

	.word (P4_S2_LOAD_ADDRESS-(P4_LOAD_ADDRESS+p4_1_end-p4_1_start))

	.word 0x00143d60		@ add sp,sp,r3 | ldr pc,[sp],#4
@---------------------------------------------------------------------------------
p6_1_end:
@---------------------------------------------------------------------------------

@---------------------------------------------------------------------------------
patch_6_x_2:
@---------------------------------------------------------------------------------
	.word	p6_2_end - p6_2_start
	.word	0x1b4

@---------------------------------------------------------------------------------
p6_2_start:
@---------------------------------------------------------------------------------
	.word 0x0010f2b9			@ pop {r0,r2,pc}
	.word 0x0001fe00			@ (r0) offset in firmware
	.word 0x00000100			@ (r2) size
	.word 0x001549e1			@ pop {r1,pc}
	.word P4_LOAD_ADDRESS			@ (r1) dst
	.word 0x001334fc			@ cfg:nor::ReadData(offset,dst,size), ends with ldmfd   sp!,{r4,pc}
	.word 0xdeadbeef			@ (r4)
	.word 0x0010538c			@ pop {r3,pc}
	.word P4_LOAD_ADDRESS - 0x0fffff64	@ (r3)
	.word 0x00143d60			@ add sp,sp,r3 | ldr pc,[sp],#4


@---------------------------------------------------------------------------------
p6_2_end:
@---------------------------------------------------------------------------------

@---------------------------------------------------------------------------------
patch_count1:
@---------------------------------------------------------------------------------
	.word	2
	.word	0x70

	.word	0x51

@---------------------------------------------------------------------------------
patch_count2:
@---------------------------------------------------------------------------------

	.word	2
	.word	0x170

	.hword	0x52

@---------------------------------------------------------------------------------
patch_message_length:
@---------------------------------------------------------------------------------

	.word	2
	.word	0x150

	.hword	0x6e

@---------------------------------------------------------------------------------
patch_G_W:
@---------------------------------------------------------------------------------
	.word	0x50544348
	.word	5
	.word	patch_G_W_1
	.word	patch_G_W_2
	.word	patch_count1
	.word	patch_count2
	.word	patch_message_length

@---------------------------------------------------------------------------------
patch_R_X:
@---------------------------------------------------------------------------------
	.word	0x50544348
	.word	5
	.word	patch_R_X_1
	.word	patch_R_X_2
	.word	patch_count1
	.word	patch_count2
	.word	patch_message_length

@---------------------------------------------------------------------------------
patch_4_x:
@---------------------------------------------------------------------------------
	.word	0x50544348
	.word	5
	.word	patch_4_x_1
	.word	patch_4_x_2
	.word	patch_count1
	.word	patch_count2
	.word	patch_message_length


@---------------------------------------------------------------------------------
patch_6_x:
@---------------------------------------------------------------------------------
	.word	0x50544348
	.word	5
	.word	patch_6_x_1
	.word	patch_6_x_2
	.word	patch_count1
	.word	patch_count2
	.word	patch_message_length

@---------------------------------------------------------------------------------
index:
@---------------------------------------------------------------------------------
	.word	patch_G_W_description
	.word	patch_G_W
	
	.word	patch_R_X_description
	.word	patch_R_X

	.word	patch_4_x_description
	.word	patch_4_x

	.word	patch_6_x_description
	.word	patch_6_x
