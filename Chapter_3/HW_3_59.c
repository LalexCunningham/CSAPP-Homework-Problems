#include <stdio.h>

typedef __int128 int128_t;

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}

void store_prod(int128_t *dest, int64_t x, int64_t y) {
	*dest = x * (int128_t) y;
}

/*
store_prod:
	movq	%rdx, %rax
	cqto
	movq	%rsi, %rcx
	sarq	$63, %rcx
	imulq	%rax, %rxc
	imulq	%rsi, %rdx
	addq	%rdx, %rcx
	mulq	%rsi
	addq	%rcx, %rdx
	movq 	%rax, (%rdi)
	movq	%rdx, 8(%rdi)
	ret
*/