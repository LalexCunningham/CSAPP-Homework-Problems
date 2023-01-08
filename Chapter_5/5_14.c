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

    for(i = 0; i < length - 6; i += 6) {
        sum += udata[i] * vdata[i];
        sum += udata[i+1] * vdata[i+1];
        sum += udata[i+2] * vdata[i+2];
        sum += udata[i+3] * vdata[i+3];
        sum += udata[i+4] * vdata[i+4];
        sum += udata[i+5] * vdata[i+5];
    }

    while (i < length) {
        sum += udata[i] * vdata[i];
        i++;
    }

    *dest = sum;
}

/*
A. explain why any (scalar) version of an inner product 
running on an intel COre i7 Haswell processor cannot achieve a CPE of less than
    Throuput bound of 1.00 for addition?

B. Explain why the performance for floating point did not improve with loop
unrolling

*/

