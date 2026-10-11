// proto: u16 krb_comp_dir(f32 x, f32 z);
double hypot(double x, double y);

u16 krb_comp_dir(f32 x, f32 z) {
    f32 dist = hypot(x, z);
    f32 s = __fabs(z) / dist;
    u16 i;
    u16 lo = 0;
    u16 hi = 90;
    u16 mid;

    for (i = 0; i < 7; i++) {
        mid = lo + (hi - lo) / 2;
        if (((f32*)SinTable)[mid] < s) {
            lo = mid;
        }
        if (!(((f32*)SinTable)[(u16)mid] < s)) {
            hi = mid;
        }
    }
    mid = __fabs(((f32*)SinTable)[lo] - s) < __fabs(((f32*)SinTable)[hi] - s) ? lo : hi;
    if (x < 0.0f && z >= 0.0f) {
        mid = 180 - mid;
    }
    if (x < 0.0f && z < 0.0f) {
        mid += 180;
    }
    if (x >= 0.0f && z < 0.0f) {
        mid = 360 - mid;
    }
    return (u16)mid;
}
