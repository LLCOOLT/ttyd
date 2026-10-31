double __ieee754_fmod(double, double);

/** Standard fmod(): wrapper over __ieee754_fmod. */
double fmod(double x, double y) {
    return __ieee754_fmod(x, y);
}
