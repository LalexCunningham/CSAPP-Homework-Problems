#include <stdio.h>

typedef __int128 int128_t;

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

// computes the 128 bit product of two 64-bit signed values
void store_prod(int128_t *dest, int64_t x, int64_t y) {
	*dest = x * (int128_t) y;
}

/*
Argument Ordering:
dest in %rdi, x in %rsi, y in %rdx, %rcx

128 bit mult formula

(2**64 * xh + xl) * (2**64 * yh + yl)



store_prod:
	movq	%rdx, %rax	// y in %rax
	cqto				// Sign extend %rax into %rdx. Now y = %rax (low order bits), %rdx (high order bits)
	movq	%rsi, %rcx	// x in %rcx
	sarq	$63, %rcx 	// %rcx >> 63, looks to me like a sign extension so x = %rsi (low order), %rcx (high order)
	imulq	%rax, %rcx	// yl * xh
	imulq	%rsi, %rdx	// xl * yh
	addq	%rdx, %rcx	// (yl * xh) + (xl * yh)
	mulq	%rsi		// Uses %rdx, %rax unsigned? %rax * %rsi => %rax (low order), %rdx (high order)
	addq	%rcx, %rdx	
	movq 	%rax, (%rdi)	// Low order bits
	movq	%rdx, 8(%rdi) 	// High order bits
	ret
*/