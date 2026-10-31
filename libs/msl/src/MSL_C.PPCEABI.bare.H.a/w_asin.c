double __ieee754_asin(double);

/** Standard asin(): wrapper over __ieee754_asin. */
double asin(double x) {
    return __ieee754_asin(x);
}
