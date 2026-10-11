double __ieee754_fmod(double, double);

double fmod(double x, double y) {
    return __ieee754_fmod(x, y);
}
