void psum1(float a[], float p[], long n) {
    long i;
    p[0] = a[0];
    for(i = 1; i < n; i++) {
        p[i] = p[i-1];
    }
}
/*
a in %rdi, i in %rax, cnt in %rdx
.L5:
    vmovss      -4(%rsi, %rax, 4), %xmm0
    vaddss      (%rdi, %rax, 4), %xmm0, %xmm0
    vmovss      %xmm0, (%rsi, %rax, 4)
    addq        $1, %rax
    cmpq        %rdx, %rax
    jne         .L5
*/

