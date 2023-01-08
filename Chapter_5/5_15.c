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
    data_t acc1, acc2, acc3, acc4, acc5, acc6;

    for(i = 0; i < length - 6; i += 6) {
        acc1 += udata[i] * vdata[i];
        acc2 += udata[i+1] * vdata[i+1];
        acc3 += udata[i+2] * vdata[i+2];
        acc4 += udata[i+3] * vdata[i+3];
        acc5 += udata[i+4] * vdata[i+4];
        acc6 += udata[i+5] * vdata[i+5];
    }

    sum = acc1+acc2+acc3+acc4+acc5+acc6;

    while (i < length) {
        sum += udata[i] * vdata[i];
        i++;
    }

    *dest = sum;
}

/*
A. What factor limits the CPE of 1.00?

    
*/

