.file	1 "hello.c"
.section .mdebug.abi32
.previous
.nan	legacy
.module	fp=xx
.module	nooddspreg
.abicalls
.text
.align	2
.globl main
.set	nomips16
.set	nomicromips
.ent main
.type main, @function
main:
.frame	$fp,32,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
.mask	0x40000000,-28
.fmask	0x00000000,0
.set	noreorder
.set	nomacro
addiu	$sp,$sp,-32
sw $fp,28($sp)
move	$fp,$sp
addiu $8,$0, 0
sw $8, 0($fp)      #variable a
lw  $8, 0($fp)      #variable a in reg 8
addiu $9,$0, 0
bne $8, $9, L0
lw  $10, 0($fp)      #variable a in reg 10
addiu $10,$0, 1
sw  $10, 0($fp)     #variable a
L0:
lw  $11, 0($fp)      #variable a in reg 11
move $2, $11
move	$sp,$fp
lw	$fp,28($sp)
addiu	$sp,$sp,32
j $31
nop

.set	macro
.set	reorder
.end	main
.size	main, .-main
.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
