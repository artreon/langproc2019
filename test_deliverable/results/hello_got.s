.file	1 "test_deliverable/test_cases/hello.c"
.section .mdebug.abi32
.previous
.nan	legacy
.module	fp=xx
.module	nooddspreg
.abicalls
.text
.align	2
.globl f
.set	nomips16
.set	nomicromips
.ent f
.type f, @function
f:
.frame	$fp,32,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
.mask	0x40000000,-28
.fmask	0x00000000,0
.set	noreorder
.set	nomacro
addiu	$sp,$sp,-32
sw $fp,28($sp)
move	$fp,$sp
addiu $2,$0, 5
sw $2, 0($fp)      #variable b
addiu $2,$0, 5
sw $2, 4($fp)      #variable c
lw  $2, 0($fp)
move	$sp,$fp
lw	$fp,28($sp)
addiu	$sp,$sp,32
j $31
nop

.set	macro
.set	reorder
.end	f
.size	f, .-f
.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
