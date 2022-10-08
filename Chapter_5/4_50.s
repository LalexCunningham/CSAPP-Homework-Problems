.pos 0
main:
    irmovq stack, %rsp
    irmovq $0, %rcx
    call switchv
    halt

.align 8
jumptable:
    .quad   L5     
    .quad   L2     
    .quad   L4     
    .quad   L2     
    .quad   L2     
    .quad   L4     

    
switchv:
    irmovq $0, %rax
    irmovq $5, %rbx
    rrmovq %rcx, %rdx
    subq %rbx, %rdx
    jg L2

    irmovq $0, %rsi     
    irmovq jumptable, %rdi
    irmovq $1, %r8      
    irmovq $8, %r9      

addidx:      
    rrmovq %rcx, %rdx
    subq %rsi, %rdx
    je jump

    addq %r8, %rsi
    addq %r9, %rdi
    jmp addidx

jump:
    mrmovq (%rdi), %rdx
    pushq %rdx
    ret

L5:
    irmovq $2730, %rax // result = 0xaaa
    jmp L1

L4:
    irmovq $3003, %rax // result = 0xbbb
    jmp L1

L3:
    irmovq $3276, %rax // result = 0xccc
    jmp L1

L2:
    irmovq $3549, %rax // Default, result = 0xddd

L1:
    ret
    
    .pos 0x200
stack:
    