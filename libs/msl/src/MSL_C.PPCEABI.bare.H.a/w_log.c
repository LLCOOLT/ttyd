double __ieee754_log(double);

/** Standard log(): wrapper over __ieee754_log. */
double log(double x) {
    return __ieee754_log(x);
}
