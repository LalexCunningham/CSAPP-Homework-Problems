void copy_array(long *src, long *dest, long n) {
    long i;
    for(i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

/*
Suppose a is an array of length 1,000 initialized so that each element a[i] 
equals i

A. What would be the effect of the call copy_array(a+1, a, 999)
a = {1, 2, 3, ... 998, 999, 999}

B. What would be the effect of the call copy_array(a, a+1, 999)
a = {0, 0, 1, ... 996, 997, 998} - wrong, sets all to 0

C. Our performance measurements indicate that the call of part A has a 
CPE of 1.2 (which drops to 1.0 when the loop is unrolled by 4), while
the call of part B has a CPE of 5.0. To what factor do you attribute this 
performance difference?

Loop unrolling drops to 1, that.2 is caused by overhead from loop?

- where is 5.0 coming from?
In A, we're reading from an unused or clean memory address, in B, the value 
is being written to an address that previously had a store instrucitons
meaning it has to clear the cache

5.0

Wrong, no 

*/