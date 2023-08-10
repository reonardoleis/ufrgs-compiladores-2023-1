.section .data

print_str_int:
	.string	"%d"
print_str_real:
	.string	"%f"
print_str_char:
	.string	"%c"
_0: .long 0
_1: .long 1
_int_temp_4: .long 0
_r: .long 0
_z: .long 0
_int_temp_1: .long 0
_10: .long 10
_int_temp_3: .long 0
_int_temp_0: .long 0
_string_1: .string "\n"
_int_temp_2: .long 0
_x: .long 0
_y: .long 0

.section .text

	# TAC_VARDEC
	# TAC_VARDEC
	# TAC_VARDEC
	# TAC_BEGINFUN
.main:
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_DIF
	movl _x(%rip), %edx
	movl _y(%rip), %eax
	cmpl %eax, %edx
	setne %al
	movzbl %al, %eax
	movl %eax, _int_temp_0(%rip)
	# TAC_COPY
	movl _int_temp_0(%rip), %eax
	movl %eax, _r(%rip)
	# TAC_LABEL
_loop_start_label_0:
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_LT
	movl _x(%rip), %edx
	movl _10(%rip), %eax
	cmpl %eax, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, _int_temp_1(%rip)
	# TAC_JFALSE
	movl _int_temp_1(%rip), %eax
	testl %eax, %eax
	je _loop_end_label'_1
	# TAC_SYMBOL
	# TAC_ARG
	# TAC_CALL
	# TAC_COPY
	movl _int_temp_2(%rip), %eax
	movl %eax, _y(%rip)
	# TAC_SYMBOL
	# TAC_PRINT_ARG
	movl _y(%rip), %esi
	leaq	print_str_int(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	# TAC_PRINT_ARG
	leaq _string_1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	# TAC_PRINT
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_ADD
	movl	_x(%rip), %edx
	movl	_1(%rip), %eax
	addl	%eax, %edx
	movl	%edx, _int_temp_3(%rip)
	# TAC_COPY
	movl _int_temp_3(%rip), %eax
	movl %eax, _x(%rip)
	# TAC_JUMP
	jmp _loop_start_label_0
	# TAC_LABEL
_loop_end_label'_1:
	# TAC_SYMBOL
	# TAC_RET
	movl _1(%rip), %eax
	# TAC_ENDFUN
	popq	%rbp
	ret
	# TAC_BEGINFUN
.plusten:
	.text
	.globl	plusten
	.type	plusten, @function
plusten:
	pushq	%rbp
	movq	%rsp, %rbp
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_ADD
	movl	_z(%rip), %edx
	movl	_10(%rip), %eax
	addl	%eax, %edx
	movl	%edx, _int_temp_4(%rip)
	# TAC_RET
	movl _int_temp_4(%rip), %eax
	# TAC_ENDFUN
	popq	%rbp
	ret
