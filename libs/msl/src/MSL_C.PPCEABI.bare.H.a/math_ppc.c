double tan(double x);
double sin(double x);
double cos(double x);

/** Single-precision tangent: calls the double tan() and narrows the result. */
float tanf(float x) {
    return tan(x);
}

/** Single-precision sine: calls the double sin() and narrows the result. */
float sinf(float x) {
    return sin(x);
}

/** Single-precision cosine: calls the double cos() and narrows the result. */
float cosf(float x) {
    return cos(x);
}
