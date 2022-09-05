long A[R][S][T];

long store_ele(long i, long j, long k, long *dest) {
	*dest = A[i][j][k];
	return sizeof(A);
}

/*
A. Extend equation 3.1 from two dimensions to three to provide a formula for the location of array element A[i][j][k]
	
	T D[R][C];
	eq 3.1: &D[i][j] = Xd + L(C * i + j)

	L = size of data type

	&D[i][j][k] = Xd + L(i * R * S + j * 5 + k)

B. Use your reverse engineering skills to determine the values of R, S, T based on the assembly code

i in %rdi, j in %rsi, k in %rdx, dest in %rcx
store_ele:
	leaq		(%rsi, %rsi, 2), %rax	j + j * 2 = j * 3
	leaq		(%rsi, %rax, 4), %rax	j + (j * 3) * 4
*/