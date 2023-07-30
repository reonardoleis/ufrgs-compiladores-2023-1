.main:
	.text
	.globl	main
	.type	main, @function
_2: .long 2
_3: .long 3
_5: .long 5
__VAR_TEMP_3d801aa5_1: .long 0
_10: .long 10
__VAR_TEMP_3d801aa5_2: .long 0
_20: .long 20
_12: .long 12
__VAR_TEMP_3d801aa5_0: .long 0
a: .long 10
b: .long 20
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl _VAR_TEMP_3d801aa5_2(%rip), %esi
	leaq	.print_str(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$12, %eax
	popq	%rbp
	ret
