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
addu $2, $0, $0 
addiu $2,$0, 5
sw $2, 0($fp)      #variable b
addu $2, $0, $0 
addiu $2,$0, 5
sw $2, 4($fp)      #variable c
lw  $2, 0($fp)       #variable b in reg2
lw  $3, 4($fp)       #variable c in reg3
addu $24, $2, $3
lw  $4, 0($fp)       #variable b in reg4
addiu $26, $4, 3
lw  $5, 4($fp)       #variable c in reg5
addiu $27, $5, 6
addiu $2,$0,0
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
