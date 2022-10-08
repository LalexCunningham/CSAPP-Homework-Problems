#include <stdio.h>

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t find_range_2(float x);

int main(int argc, char const *argv[])
{
	printf("%d", find_range_2(0.0 / 0.0));
	return 0;
}

// range_t find_range(float x) {
// 	int result;
// 	if (x < 0) {
// 		result = NEG;
// 	} else if (x == 0) {
// 		result = ZERO;
// 	} else if (x > 0) {
// 		result = POS;
// 	} else {
// 		result = OTHER;
// 	}
// 	return result;
// }

range_t find_range_2(float x) {
	asm(
		"vxorps 	%xmm1, %xmm1, %xmm1\n\t"
		"vucomiss	%xmm0, %xmm1\n\t"	// %xmm1 - %xmm0
		"jp   	.L4\n\t"
		"ja		.L1\n\t"
		"jb		.L3\n\t"
		"je		.L2\n\t"
		".L1:\n\t"
		"movl 		$0, %eax\n\t"
		"jmp		.L5\n\t"
		".L2:\n\t"
		"movl 		$1, %eax\n\t"
		"jmp		.L5\n\t"
		".L3:\n\t"
		"movl 		$2, %eax\n\t"
		"jmp		.L5\n\t"
		".L4:\n\t"
		"movl 		$3, %eax\n\t"
		".L5:\n\t"
	);
}


/*
Write a function in assembly code that matches the behavior of the function find_
range in Figure 3.51. Your code should contain only one floating-point comparison
instruction, and then it should use conditional branches to generate the correct
result. Test your code on all 2 32 possible argument values. Web Aside asm:easm
on page 214 describes how to incorporate functions written in assembly code into
C programs.






3.51:
x in %xmm0
find_range:
	vxorps		%xmm1, %xmm1, %xmm1		Set %xmm1 to 0
	vucomiss	%xmm0, %xmm1			x < 0
	ja			.L5						
	vucomiss	%xmm1, %xmm0
	jp			.L8						parity - NaN, go .L8
	movl		$1, %eax				x == 0; return 1 (ZERO)
	je			.L3
.L8
	vucomiss	.LC0(%rip), %xmm0		
	setbe		%al
	movzbl		%al, %eax
	addl		$2, %eax
	ret
.L5
	movl 		$0, %eax				return 0; // NEG 
.L3
	rep; ret	



*/