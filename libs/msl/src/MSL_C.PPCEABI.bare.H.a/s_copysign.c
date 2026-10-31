#define __HI(x) *(int*)&x

/** Returns x with the sign of y. */
double copysign(double x, double y) {
    __HI(x) = (__HI(x) & 0x7fffffff) | (__HI(y) & 0x80000000);
    return x;
}
