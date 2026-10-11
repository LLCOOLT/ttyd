#include "fdlibm.h"

#define FP_NAN 1
#define FP_INFINITE 2
#define FP_ZERO 3
#define FP_NORMAL 4
#define FP_SUBNORMAL 5

inline int __fpclassifyd(double x) {
    switch (__HI(x) & 0x7ff00000) {
        case 0x7ff00000:
            if ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff)) return FP_NAN;
            else return FP_INFINITE;
        case 0:
            if ((__HI(x) & 0x000fffff) || (__LO(x) & 0xffffffff)) return FP_SUBNORMAL;
            else return FP_ZERO;
    }
    return FP_NORMAL;
}

#define isfinite(x) (__fpclassifyd(x) > FP_INFINITE)

static const double
two54 = 1.80143985094819840000e+16,
twom54 = 5.55111512312578270212e-17,
huge = 1.0e+300,
tiny = 1.0e-300;

double ldexp(double x, int n) {
    int k, hx, lx;
    if (!isfinite(x) || x == 0.0) return x;
    hx = __HI(x);
    lx = __LO(x);
    k = (hx & 0x7ff00000) >> 20;
    if (k == 0) {
        if ((lx | (hx & 0x7fffffff)) == 0) return x;
        x *= two54;
        hx = __HI(x);
        k = ((hx & 0x7ff00000) >> 20) - 54;
        if (n < -50000) return tiny * x;
    }
    if (k == 0x7ff) return x + x;
    k = k + n;
    if (k > 0x7fe) return huge * copysign(huge, x);
    if (k > 0) {
        __HI(x) = (hx & 0x800fffff) | (k << 20);
        return x;
    }
    if (k <= -54)
        if (n > 50000)
            return huge * copysign(huge, x);
        else
            return tiny * copysign(tiny, x);
    k += 54;
    __HI(x) = (hx & 0x800fffff) | (k << 20);
    return x * twom54;
}
