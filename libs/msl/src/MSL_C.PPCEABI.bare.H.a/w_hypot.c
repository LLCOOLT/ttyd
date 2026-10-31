double __ieee754_hypot(double, double);

/** Standard hypot(): wrapper over __ieee754_hypot. */
double hypot(double x, double y) {
    return __ieee754_hypot(x, y);
}
