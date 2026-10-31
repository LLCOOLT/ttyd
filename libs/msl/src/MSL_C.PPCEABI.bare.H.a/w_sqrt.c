double __ieee754_sqrt(double);

/** Standard sqrt(): wrapper over __ieee754_sqrt. */
double sqrt(double x) {
    return __ieee754_sqrt(x);
}
