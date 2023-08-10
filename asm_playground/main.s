	.file	"main.c"
	.text
	.globl	foo
	.bss
	.align 4
	.type	foo, @object
	.size	foo, 4
foo:
	.zero	4
	.globl	bar
	.align 4
	.type	bar, @object
	.size	bar, 4
bar:
	.zero	4
	.globl	a
	.data
	.align 4
	.type	a, @object
	.size	a, 4
a:
	.long	1
	.globl	x
	.bss
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.zero	4
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$125, foo(%rip)
	movl	a(%rip), %eax
	testl	%eax, %eax
	je	.L2
	movl	$111, x(%rip)
	jmp	.L3
.L2:
	movl	$222, x(%rip)
.L3:
	movl	$250, bar(%rip)
	movl	$12, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
