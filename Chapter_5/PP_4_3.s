# Rewrite sum to make use of the iaddq instruction 

# Execution begins at address 0
	.pos 0
	irmovq stack, %rsp # Set up stack pointer
	call main # Execute main program
	halt # Terminate program

# Array of 4 elements
	.align 8
array:
	.quad 0x000d000d000d
	.quad 0x00c000c000c0
	.quad 0x0b000b000b00
	.quad 0xa000a000a000

main:
	irmovq array,%rdi
	irmovq $4,%rsi
	call sum # sum(array, 4)
	ret

# long sum(long *start, long count)
# start in %rdi, count in %rsi
sum:
	xorq %rax,%rax # sum = 0
	andq %rsi,%rsi # Set CC
	jmp test # Goto test
loop:
	mrmovq (%rdi),%r10 # Get *start
	addq %r10,%rax # Add to sum
	iaddq $8,%rdi # start++
	iaddq $-1,%rsi # count--. Set CC
test:
	jne loop # Stop when 0
	ret # Return

# Stack starts here and grows to lower addresses
	.pos 0x200
stack: