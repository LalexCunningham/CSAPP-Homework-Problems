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
			if(*(data+i+1) < *(data+i)) {
				long t = *(data+i+1);
				*(data+i+1) = *(data+i);
				*(data+i) = t;
			}
		}
	}
}

/*
.pos 0
main:
    irmovq stack, %rsp
    
    irmovq array, %rdi     // data
    irmovq $6, %rsi     // count
    call bubble_p
    halt

.align 8
array:
    .quad 0x03
    .quad 0x05
    .quad 0x02
    .quad 0x01
    .quad 0x03
    .quad 0x04
    
bubble_p:
    irmovq $1, %r11     // constant 1
    irmovq $8, %r8      // constant 8
    
    subq %r11, %rsi 
    jl end
    rrmovq %rdi, %r12   // data
	
outerloop:
    irmovq $0, %r10     // i * 8
    irmovq $0, %r12     // i
	
innerloop:
    rrmovq %rdi, %rax
    addq %r10, %rax     // data + i
    rrmovq %rax, %rcx
    addq %r8, %rcx      // data + i + 1
    
    mrmovq (%rax), %rdx // *(data + i)
    mrmovq (%rcx), %rbx // *(data + i + 1)
    
    rrmovq %rbx, %r14   // temp
    subq %rdx, %r14
    jg skip
    
    // Swap
    rmmovq %rbx, (%rax)
    rmmovq %rdx, (%rcx)
    
skip:   
    addq %r11, %r12
    addq %r8, %r10      // i++
innertest:
    rrmovq %r12, %r13   // temp for test
    subq %rsi, %r13
    jl innerloop
    subq %r11, %rsi  // last--
outertest:
    jg outerloop
end:
    ret


    .pos 0x200
stack:
    
*/