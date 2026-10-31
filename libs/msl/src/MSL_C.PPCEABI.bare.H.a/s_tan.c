#include "fdlibm.h"

/**
 * Tangent of x in radians (fdlibm): small arguments use __kernel_tan directly, NaN/infinity return x - x,
 * otherwise __ieee754_rem_pio2 reduces the argument and the quadrant parity picks tan or -1/tan.
 */
double tan(double x) {
    double y[2], z = 0.0;
    int n, ix;

    ix = __HI(x);

    ix &= 0x7fffffff;
    if (ix <= 0x3fe921fb) return __kernel_tan(x, z, 1);

    else if (ix >= 0x7ff00000) return x - x;

    else {
        n = __ieee754_rem_pio2(x, y);
        return __kernel_tan(y[0], y[1], 1 - ((n & 1) << 1));
    }
}
