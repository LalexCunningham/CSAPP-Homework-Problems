typedef long data_t;

/* Create an abstract data type for vector */
typedef struct {
    long len;
    data_t *data;
} vec_rec, *vec_ptr;

/* Inner product. Accumulate in temporary */

void inner4(vec_ptr u, vec_ptr v, data_t *dest) {
    long i;
    long length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t) 0;

    for(i = 0; i < length; i++) {
        sum = sum + udata[i] * vdata[i];
    }

    *dest = sum;
}

/*
data_t = double, OP = *
udata in %rbp, vdata in %rax, sum in %xmm0
i in %rcx, limit in %rbx
.L15:
    vmovsd      0(%rbp, %rcx, 8), %xmm1
    vmulsd      (%rax, %rcx, 8), %xmm1, %xmm1
    vaddsd      %xmm1, %xmm0, %xmm0
    addq        $1, %rcx
    cmpq        %rbx, %rcx
    jne         .L15
*/

/*
B. For type double, what lower bound on the CPE is determined by the critical path?
    1 (LOAD) + 5 (MUL) + 3 (ADD) = 9.0 CPE
C. Same for int
    1 (LOAD) + 3 (MUL) + 1 (ADD) = 5.0 CPE
D. Explain how the floating-point versions can have CPEs of 3.00, even though
the multiplication operation requires 5 clock cycles.
    Jaysus haven't a clue

*/