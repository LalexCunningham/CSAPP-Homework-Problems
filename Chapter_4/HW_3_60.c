
int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

long loop(long x, int n) {
	long result = 0;
	long mask;
	for(mask = 1; mask != 0 ; mask <<= n) {
		result |= (x & mask);
	}
	return result;
}

/*
long loop(long x, int n)
x in %rdi, n in %esi

loop:
	movl 	%esi, %ecx	// %ecx = n
	movl 	$1, %edx	// %edx = 1 (mask)
	movl 	$0, %eax	// %eax = 0	(result)
	jmp 	.L2
.L3
	movq 	%rdi, %r8	// %r8 = x
	andq 	%rdx, %r8	// x & mask
	orq 	%r8, %rax	
	salq 	%cl, %rdx
.L2
	testq 	%rdx, %rdx	// mask != 0
	jne		.L3
	rep; ret
*/