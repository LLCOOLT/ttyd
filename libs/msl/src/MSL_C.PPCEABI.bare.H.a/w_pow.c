double __ieee754_pow(double, double);

double pow(double x, double y) {
    return __ieee754_pow(x, y);
}
