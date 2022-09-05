#include <complex.h>

double c_imag(double complex x) {
	return cimag(x);
}

double c_real(double complex x) {
	return creal(x);
}

double complex c_sub(double complex x, double complex y) {
	return x - y;
}

/*
c_imag:
	movapd	%xmm1, %xmm0
	ret

c_real:
	rep; ret

c_sub:
	subsd	%xmm2, %xmm0
	subsd 	%xmm3, %xmm1
	ret

A. How are complex arguments passed to a function?
	%xmm1 -> ...
B. How are complex values returned from a function?
	%xmm1
*/