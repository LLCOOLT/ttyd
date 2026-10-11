double __ieee754_hypot(double, double);

double hypot(double x, double y) {
    return __ieee754_hypot(x, y);
}
