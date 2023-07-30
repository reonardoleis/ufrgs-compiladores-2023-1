.section .data

print_str_int:
	.string	"%d"
print_str_real:
	.string	"%f"
print_str_char:
	.string	"%c"
_1: .long 1
_2: .long 2
__VAR_TEMP_3d801aa5_1: .long 0
_12: .long 12
__VAR_TEMP_3d801aa5_0: .long 0
_a: .long 1
_b: .long 1
_x: .long 2

.section .text

.main:
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	_b(%rip), %edx
	movl	_2(%rip), %eax
	subl	%eax, %edx
	movl	%edx, __VAR_TEMP_3d801aa5_0(%rip)
	movl	__VAR_TEMP_3d801aa5_0(%rip), %edx
	movl	_a(%rip), %eax
	subl	%eax, %edx
	movl	%edx, __VAR_TEMP_3d801aa5_1(%rip)
	movl __VAR_TEMP_3d801aa5_1(%rip), %eax
	movl %eax, _a(%rip)
	movl _a(%rip), %esi
	leaq	print_str_int(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$12, %eax
	popq	%rbp
	ret
