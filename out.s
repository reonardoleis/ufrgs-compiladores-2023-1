.section .data

print_str_int:
	.string	"%d"
print_str_real:
	.string	"%f"
print_str_char:
	.string	"%c"
_temp_13: .long 0
_string_1: .string "--\n\n"
_0: .long 0
_1: .long 1
_2: .long 2
_3: .long 3
_4: .long 4
_5: .long 5
_6: .long 6
_7: .long 7
_8: .long 8
_9: .long 9
_temp_8: .long 0
_temp_12: .long 0
_i: .long 0
_j: .long 0
_temp_11: .long 0
_temp_5: .long 0
_aux: .long 0
_temp_10: .long 0
_temp_2: .long 0
_temp_9: .long 0
_temp: .long 0
_10: .long 10
_temp_6: .long 0
_temp_3: .long 0
_temp_0: .long 0
_dir: .long 0
_temp_18: .long 0
_temp_7: .long 0
_temp_17: .long 0
_string_2: .string "\n"
_temp_4: .long 0
_temp_16: .long 0
_startPos: .long 0
_temp_15: .long 0
_temp_1: .long 0
_temp_14: .long 0
_vec_size: .long 10
_void: .long 0

.section .text

	# TAC_VARDEC
	# TAC_SYMBOL
	# TAC_VECDEC
	.globl	_vec
	.data
	.align 8
	.type	_vec, @object
	.size	_vec, 40
_vec:
	.long 6
	.long 9
	.long 5
	.long 2
	.long 7
	.long 8
	.long 1
	.long 10
	.long 3
	.long 4
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_SYMBOL
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
	# TAC_ARG
	movl _0(%rip), %eax
	movl %eax, _startPos(%rip)
	# TAC_CALL
	call print_vec
	movl %eax, _temp_0(%rip)
	# TAC_COPY
	movl _temp_0(%rip), %eax
	movl %eax, _void(%rip)
	# TAC_PRINT_ARG
	leaq _string_1(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	# TAC_PRINT
	# TAC_SYMBOL
	# TAC_ARG
	movl _0(%rip), %eax
	movl %eax, _i(%rip)
	# TAC_SYMBOL
	# TAC_ARG
	movl _0(%rip), %eax
	movl %eax, _j(%rip)
	# TAC_SYMBOL
	# TAC_ARG
	movl _0(%rip), %eax
	movl %eax, _temp(%rip)
	# TAC_SYMBOL
	# TAC_ARG
	movl _0(%rip), %eax
	movl %eax, _dir(%rip)
	# TAC_CALL
	call sort
	movl %eax, _temp_1(%rip)
	# TAC_COPY
	movl _temp_1(%rip), %eax
	movl %eax, _void(%rip)
	# TAC_SYMBOL
	# TAC_ARG
	movl _0(%rip), %eax
	movl %eax, _startPos(%rip)
	# TAC_CALL
	call print_vec
	movl %eax, _temp_2(%rip)
	# TAC_COPY
	movl _temp_2(%rip), %eax
	movl %eax, _void(%rip)
	# TAC_SYMBOL
	# TAC_RET
	movl _0(%rip), %eax
	# TAC_ENDFUN
	popq	%rbp
	ret
	# TAC_BEGINFUN
.print_vec:
	.text
	.globl	print_vec
	.type	print_vec, @function
print_vec:
	pushq	%rbp
	movq	%rsp, %rbp
	# TAC_SYMBOL
	# TAC_COPY
	movl _0(%rip), %eax
	movl %eax, _startPos(%rip)
	# TAC_LABEL
_loop_start_label_0:
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_LT
	movl _startPos(%rip), %edx
	movl _vec_size(%rip), %eax
	cmpl %eax, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, _temp_3(%rip)
	# TAC_JFALSE
	movl _temp_3(%rip), %eax
	testl %eax, %eax
	je _loop_end_label_1
	# TAC_SYMBOL
	# TAC_COPY
	movl _startPos(%rip), %eax
	cltq
	leaq 0(,%rax,4), %rdx
	leaq _vec(%rip), %rax
	movl (%rdx,%rax), %eax
	movl %eax, _temp_4(%rip)
	# TAC_PRINT_ARG
	movl _temp_4(%rip), %esi
	leaq	print_str_int(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	# TAC_PRINT_ARG
	leaq _string_2(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	# TAC_PRINT
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_ADD
	movl	_startPos(%rip), %edx
	movl	_1(%rip), %eax
	addl	%eax, %edx
	movl	%edx, _temp_5(%rip)
	# TAC_COPY
	movl _temp_5(%rip), %eax
	movl %eax, _startPos(%rip)
	# TAC_JUMP
	jmp _loop_start_label_0
	# TAC_LABEL
_loop_end_label_1:
	# TAC_SYMBOL
	# TAC_RET
	movl _0(%rip), %eax
	# TAC_ENDFUN
	popq	%rbp
	ret
	# TAC_VARDEC
	# TAC_BEGINFUN
.sort:
	.text
	.globl	sort
	.type	sort, @function
sort:
	pushq	%rbp
	movq	%rsp, %rbp
	# TAC_SYMBOL
	# TAC_COPY
	movl _0(%rip), %eax
	movl %eax, _i(%rip)
	# TAC_SYMBOL
	# TAC_COPY
	movl _0(%rip), %eax
	movl %eax, _j(%rip)
	# TAC_LABEL
_loop_start_label_8:
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_LT
	movl _i(%rip), %edx
	movl _vec_size(%rip), %eax
	cmpl %eax, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, _temp_6(%rip)
	# TAC_JFALSE
	movl _temp_6(%rip), %eax
	testl %eax, %eax
	je _loop_end_label_9
	# TAC_SYMBOL
	# TAC_COPY
	movl _0(%rip), %eax
	movl %eax, _j(%rip)
	# TAC_LABEL
_loop_start_label_6:
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_LT
	movl _j(%rip), %edx
	movl _vec_size(%rip), %eax
	cmpl %eax, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, _temp_7(%rip)
	# TAC_JFALSE
	movl _temp_7(%rip), %eax
	testl %eax, %eax
	je _loop_end_label_7
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_EQ
	movl _dir(%rip), %edx
	movl _0(%rip), %eax
	cmpl %eax, %edx
	sete %al
	movzbl %al, %eax
	movl %eax, _temp_8(%rip)
	# TAC_JFALSE
	movl _temp_8(%rip), %eax
	testl %eax, %eax
	je _else_label_2
	# TAC_SYMBOL
	# TAC_COPY
	movl _i(%rip), %eax
	cltq
	leaq 0(,%rax,4), %rdx
	leaq _vec(%rip), %rax
	movl (%rdx,%rax), %eax
	movl %eax, _temp_9(%rip)
	# TAC_SYMBOL
	# TAC_COPY
	movl _j(%rip), %eax
	cltq
	leaq 0(,%rax,4), %rdx
	leaq _vec(%rip), %rax
	movl (%rdx,%rax), %eax
	movl %eax, _temp_10(%rip)
	# TAC_GT
	movl _temp_9(%rip), %edx
	movl _temp_10(%rip), %eax
	cmpl %eax, %edx
	setg %al
	movzbl %al, %eax
	movl %eax, _temp_11(%rip)
	# TAC_COPY
	movl _temp_11(%rip), %eax
	movl %eax, _aux(%rip)
	# TAC_JUMP
	jmp _endif_label_4
	# TAC_LABEL
_else_label_2:
	# TAC_SYMBOL
	# TAC_COPY
	movl _i(%rip), %eax
	cltq
	leaq 0(,%rax,4), %rdx
	leaq _vec(%rip), %rax
	movl (%rdx,%rax), %eax
	movl %eax, _temp_12(%rip)
	# TAC_SYMBOL
	# TAC_COPY
	movl _j(%rip), %eax
	cltq
	leaq 0(,%rax,4), %rdx
	leaq _vec(%rip), %rax
	movl (%rdx,%rax), %eax
	movl %eax, _temp_13(%rip)
	# TAC_LT
	movl _temp_12(%rip), %edx
	movl _temp_13(%rip), %eax
	cmpl %eax, %edx
	setl %al
	movzbl %al, %eax
	movl %eax, _temp_14(%rip)
	# TAC_COPY
	movl _temp_14(%rip), %eax
	movl %eax, _aux(%rip)
	# TAC_LABEL
_endif_label_4:
	# TAC_SYMBOL
	# TAC_JFALSE
	movl _aux(%rip), %eax
	testl %eax, %eax
	je _if_label_5
	# TAC_SYMBOL
	# TAC_COPY
	movl _i(%rip), %eax
	cltq
	leaq 0(,%rax,4), %rdx
	leaq _vec(%rip), %rax
	movl (%rdx,%rax), %eax
	movl %eax, _temp_15(%rip)
	# TAC_COPY
	movl _temp_15(%rip), %eax
	movl %eax, _temp(%rip)
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_COPY
	movl _j(%rip), %eax
	cltq
	leaq 0(,%rax,4), %rdx
	leaq _vec(%rip), %rax
	movl (%rdx,%rax), %eax
	movl %eax, _temp_16(%rip)
	# TAC_COPY
	movl _i(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq _vec(%rip), %rax
	movl _temp_16(%rip), %ecx
	movl %ecx, (%rdx,%rax)
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_COPY
	movl _j(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq _vec(%rip), %rax
	movl _temp(%rip), %ecx
	movl %ecx, (%rdx,%rax)
	# TAC_LABEL
_if_label_5:
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_ADD
	movl	_j(%rip), %edx
	movl	_1(%rip), %eax
	addl	%eax, %edx
	movl	%edx, _temp_17(%rip)
	# TAC_COPY
	movl _temp_17(%rip), %eax
	movl %eax, _j(%rip)
	# TAC_JUMP
	jmp _loop_start_label_6
	# TAC_LABEL
_loop_end_label_7:
	# TAC_SYMBOL
	# TAC_SYMBOL
	# TAC_ADD
	movl	_i(%rip), %edx
	movl	_1(%rip), %eax
	addl	%eax, %edx
	movl	%edx, _temp_18(%rip)
	# TAC_COPY
	movl _temp_18(%rip), %eax
	movl %eax, _i(%rip)
	# TAC_JUMP
	jmp _loop_start_label_8
	# TAC_LABEL
_loop_end_label_9:
	# TAC_SYMBOL
	# TAC_RET
	movl _0(%rip), %eax
	# TAC_ENDFUN
	popq	%rbp
	ret
