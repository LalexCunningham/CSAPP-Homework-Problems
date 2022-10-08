#define NR	n*3
#define NC	n*4+1

long sum_col(long n, long A[NR(n)][NC(n)], long j) {
	long i;
	long result = 0;
	for(i = 0; i < NR(n); i++) {
		result += A[i][j];
	}

	return result;
}

/*
n in %rdi, A in %rsi, j in %rdx

sum_col:
	leaq		1(,%rdi,4), %r8			1 + n * 4		%r8 = distance between each row's entry
	leaq		(%rdi,%rdi,2), %rax		n + n * 2	(or n * 3)
	movq		%rax, %rdi				n = n + n * 2
	testq		%rax, %rax				n > 0
	jle			.L4
	salq		$3, %r8					(1 + n * 4) << 3 (or * 8) == (1 + n * 4) * 8; 
	leaq		(%rsi,%rdx,8), %rcx		A + j * 8
	movl		$0, %eax				result = 0
	movl		$0, %edx				i = 0
.L3 (loop):
	addq		(%rcx), %rax			(%rcx) is a pointer to A[i][j] / result += A[i][j]
	addq		$1, %rdx				i++
	addq		%r8, %rcx				update %rcx
	cmpq		%rdi, %rdx				%rdi = NR(n)
	jne			.L3
	rep; ret
.L4:
	movl		$0, %eax				return 0
	ret

Determine the definitions of NR and NC
NR = n*3
NC = 


T D[R][C];
eq 3.1: &D[i][j] = Xd + L(C * i + j)



*/