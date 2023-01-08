void psum1(float a[], float p[], long n) {
    long i;
    p[0] = a[0];
    for(i = 1; i < n; i++) {
        p[i] = p[i-1] + a[i];
    }
}


