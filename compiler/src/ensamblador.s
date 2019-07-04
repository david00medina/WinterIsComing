		.section	.rodata
		.align 4
.F0:
		.float 500.182617
		.section	.rodata
		.align 4
.F1:
		.float 500.182617

		.section	.text
		.globl main
main:
		pushl	%ebp				# Save previous scope
		movl	%esp, %ebp			# Set new scope up
		movl	$1, %eax			# Move bool to %eax
		movl	$1, %ebx			# Move bool to %ebx
		movl	$1, %ecx			# Load true registry (%ecx)
		cmpl	%eax, %ecx			# Is first operand true?
		je	.C2				# 1st test passed?
		movl	$0, %eax			# Failed test! (AND)
		jmp	.C4				# Jump to the end of AND structure
.C2:
		cmpl	%ebx, %ecx			# Is second operand true?
		je	.C3				# 2nd test passed?
		movl	$0, %eax			# Failed test! (AND)
		jmp	.C4				# Jump to the end of the AND structure
.C3:
		movl	$1, %eax			# Successful test! (AND)
.C4:
		movl	$1, %ebx			# Set true register to 1
		cmpl	%ebx, %eax			# 'IF' condition accomplished?
		jne	.C5				# Jump to next 'IF' condition at .C5
		movl	$12, %eax			# Move int to %eax
		movl	$12, %ebx			# Move int to %ebx
		movl	$0, %edx			# %edx = 0
		cltd					# %edx:%eax
		idivl	%ebx				# %ebx = %eax / %ebx
		movl	%eax, %ebx			# Save quotient to %ebx
		jmp	.C1				# 'IF' clause got to an end
.C5:
		movl	$0, %eax			# Move bool to %eax
		movl	$0, %ecx			# Move bool to %ecx
		movl	$1, %edx			# Load true registry (%edx)
		cmpl	%eax, %edx			# Is first operand true?
		je	.C6				# 1st chance passed?
		cmpl	%ecx, %edx			# Is second operand true?
		je	.C6				# 2nd chance passed?
		movl	$0, %eax			# Failed test! (OR)
		jmp	.C7				# Jump to the end of the OR structure
.C6:
		movl	$1, %eax			# Successful test! (OR)
.C7:
		movl	$1, %ecx			# Set true register to 1
		cmpl	%ecx, %eax			# 'IF' condition accomplished?
		jne	.C0				# Jump to 'ELSE' at .C0
		movl	$97, %eax			# Move char to %eax
		movss	.F0, %xmm0			# Move real to %xmm0
		cvtsi2ss	%eax, %xmm1			# Convert int to real (%eax)
		addss	%xmm1, %xmm0			# %xmm0 = %xmm1 + %xmm0
		jmp	.C1				# 'IF' clause got to an end
.C0:
		movl	$12, %eax			# Move int to %eax
		movss	.F1, %xmm1			# Move real to %xmm1
		cvtsi2ss	%eax, %xmm2			# Convert int to real (%eax)
		subss	%xmm2, %xmm1			# %xmm1 = %xmm2 - %xmm1
.C1:
		leave					# Leave the main program

