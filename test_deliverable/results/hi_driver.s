	.file	1 "hi_driver.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,32,$31		# vars= 0, regs= 2/0, args= 16, gp= 8
	.mask	0xc0000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-32
	sw	$31,28($sp)
	sw	$fp,24($sp)
	move	$fp,$sp
	lui	$28,%hi(__gnu_local_gp)
	addiu	$28,$28,%lo(__gnu_local_gp)
	.cprestore	16
	lw	$2,%call16(f)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,f
1:	jalr	$25
	nop

	lw	$28,16($fp)
	move	$3,$2
	li	$2,10			# 0xa
	bne	$3,$2,$L2
	nop

	lw	$2,%call16(u)($28)
	move	$25,$2
	.reloc	1f,R_MIPS_JALR,u
1:	jalr	$25
	nop

	lw	$28,16($fp)
	move	$3,$2
	li	$2,6			# 0x6
	beq	$3,$2,$L3
	nop

$L2:
	li	$2,1			# 0x1
	b	$L5
	nop

$L3:
	move	$2,$0
$L5:
	move	$sp,$fp
	lw	$31,28($sp)
	lw	$fp,24($sp)
	addiu	$sp,$sp,32
	j	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
