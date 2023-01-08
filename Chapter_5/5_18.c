/* a0 + a1x + a2x**2 a3x**3 ... anx**n */
double poly(double a[], double x, long n) {
    long i;
    double result = a[0];
    double xpwr = x;

    for(i = 1; i <= n - 4; i += 4) {
        result += a[i] * xpwr;
        xpwr *= x;
        result += a[i+1] * xpwr;
        xpwr *= x;
        result += a[i+2] * xpwr;
        xpwr *= x;
        result += a[i+3] * xpwr;
        xpwr *= x;
    }

    while(i < n) {
        result += a[i] * xpwr;
        xpwr *= x;
        i++;
    }

    return result;
}

/* https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter5/5.18/ */