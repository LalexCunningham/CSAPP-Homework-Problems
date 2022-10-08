#include <stdio.h>

int main(int argc, char const *argv[])
{
	long arr[3] = {3, 2, 1};

	printf("%ld\n", *arr);
	printf("%ld\n", *(arr+1+1));
	//printf("%ld\n", *arr+1+1);

	bubble_p(arr, 3);


	printf("Sorted:\n");
	for (int i = 0; i < 3; i++) {
		printf("%ld,", arr[i]);
	}
	printf("\n");
	return 0;
}

/* Bubble sort: Pointer Version */

void bubble_p(long *data, long count) {
	long i, last;
	for (last = count-1; last > 0; last--) {
		for (i = 0; i < last; i++) {
			printf("%lu, %lu, %lu, %lu;\n", (data+i), (data+i+1), *(data+i), *(data+i+1));
			if(*(data+i+1) < *(data+i)) {
				long t = *(data+i+1);
				*(data+i+1) = *(data+i);
				*(data+i) = t;
			}
		}
	}
}

/*
	data in %rdi, count in %rsi
	%rdx, %rcx, %r8, %r9

bubble_p:
	rrmovq %rdi, %r12	// %r12 = data
	irmovq $1, %r11
	irmovq $0, %r10
	irmovq $8, %r8
	subq %r11, %rsi // %rsi = last
	jmpl end
outerloop:
innerloop:
	addq %r8, %r12	// %r12 = (data + i)
	rrmovq %r12, %r13
	addq %r8, %r13	// %r13 = (data + i + 1)
	
	mrmovq (%r12), %r9 *(data + i)
	mrmovq (%r13), %r14	*(data + i + 1)
	rrmovq %r14, %rax
	subq %r9, %rax
	jmple innertest
	rrmovq %r14, %rax
	rmmovq %r9, (%r13)
	rmmovq %rax, (%r12)
innertest:
	rrmovq %rsi, %rdx
	addq %r11, %r10
	subq %r10, %rdx
	jmpg innerloop
outertest:
	subq %r11, %rsi
	jmpge outerloop
end:
	ret

Test change

*/