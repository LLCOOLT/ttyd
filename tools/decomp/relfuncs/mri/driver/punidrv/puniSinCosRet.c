// include: driver/punidrv.h
// proto: void puniSinCosRet(u32 deg, f32* x, f32* z, f32 rx, f32 rz);
void puniSinCosRet(u32 deg, f32* x, f32* z, f32 rx, f32 rz) {
    deg %= 360;
    *x += rx * sintbl[deg];
    *z += rz * sintbl[deg + 90];
}
