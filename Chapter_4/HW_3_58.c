#include <stdio.h>

long decode2(long x, long y, long z);

int main(int argc, char const *argv[])
{
	printf("%d", decode2(13, 14, 15));
	return 0;
}

long decode2(long x, long y, long z) {
	// x in %rdi, y in %rsi, z in %rdx

	/*
		long val1 = y - z
		long val2 = (y - z) * x
		val1 << 63
		val1 >> 63
		return val1 ^ val2 
	*/

	long val1 = y - z;
	long val2 = val1 * x;
	
	val1 << 63;
	val1 >> 63;

	return val1 ^ val2;
}