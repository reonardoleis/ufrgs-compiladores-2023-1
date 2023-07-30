# code section
.main:
	.text
	.globl	main
	.type	main, @function

main:
	pushq	%rbp	# always do
	movq	%rsp, %rbp # always do

	
	movl	.A_var(%rip), %esi # printf first argument goes into esi


	leaq	.A_str(%rip), %rax # printf formatted string goes into rax
	movq	%rax, %rdi		   # then into rdi
	call	printf@PLT		   # call printf

	movl	$66, %eax 		   # function return

	

	popq	%rbp	# always do

	ret	# always do, return to caller


# data section
.print_str_int:
	.string	"%d"

.print_str_real:
	.string	"%f"

.print_str_char:
	.string	"%c"

.A_var:
	.long	1002
