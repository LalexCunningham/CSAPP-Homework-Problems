#define M 0;

void transpose(long A[M][M]) {
	long i, j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < i; j++) {
			long t = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = t;
		}
	}
}

/*
.L6
	movq		(%rdx), %rcx
	movq		(%rax), %rsi
	movq		%rsi, (%rdx)
	movq		%rcx, (%rax)
	addq		$8, %rdx		2nd Dimension (%rdx)
	addq		$120, %rax		1st	Dimension (%rax)
	cmpq		%rdi, %rax 
	jne			.L6
	
A. %rdx
B. %rax
C. 15

*/