union ele {
	struct {
		long *p;
		long y;
	} e1;
	struct {
		long x;
		union ele *next;
	} e2;
}

void proc (union ele *up) {
	up->e2.x = *(up.e2.next) - up.e1.y;
}

/*
A. What are the offsets (in bytes) of the following fields?
	e1.p = 0
	e1.y = 8
	e2.x = 0
	e2.next = 8 

B. How many total bytes does the structure require?
	16 bytes

C. The compiler generates the following assembly for proc

up in %rdi
proc:
	movq	8(%rdi), %rax 
	movq	(%rax), %rdx
	movq	(%rdx), %rdx
	subq	8(%rax), %rdx
	movq	%rdx, (%rdi)
	ret

%rdi = up
%rax = up.e2.next
%rdx = x

*/