double __ieee754_pow(double, double);

/** Standard pow(): wrapper over __ieee754_pow. */
double pow(double x, double y) {
    return __ieee754_pow(x, y);
}
