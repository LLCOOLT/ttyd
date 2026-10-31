double __ieee754_atan2(double, double);

/**
 * Standard atan2() wrapper over __ieee754_atan2,
 * passing its two arguments straight through (this copy names them x, y).
 */
double atan2(double x, double y) {
    return __ieee754_atan2(x, y);
}
