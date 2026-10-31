#include "fdlibm.h"

/**
 * Sine of x in radians (fdlibm): |x| < about pi/4 uses __kernel_sin directly, NaN/infinity return x - x,
 * otherwise __ieee754_rem_pio2 reduces the argument and the quadrant selects +-sin or +-cos of the remainder.
 */
double sin(double x) {
    double y[2], z = 0.0;
    int n, ix;

    ix = __HI(x);

    ix &= 0x7fffffff;
    if (ix <= 0x3fe921fb) return __kernel_sin(x, z, 0);

    else if (ix >= 0x7ff00000) return x - x;

    else {
        n = __ieee754_rem_pio2(x, y);
        switch (n & 3) {
            case 0: return __kernel_sin(y[0], y[1], 1);
            case 1: return __kernel_cos(y[0], y[1]);
            case 2: return -__kernel_sin(y[0], y[1], 1);
            default:
                return -__kernel_cos(y[0], y[1]);
        }
    }
}
