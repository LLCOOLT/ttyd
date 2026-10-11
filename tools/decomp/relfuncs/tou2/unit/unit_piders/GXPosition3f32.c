// include: dolphin/gx.h
// proto: void GXPosition3f32_(f32 x, f32 y, f32 z);
#pragma dont_inline on
void GXPosition3f32_(f32 x, f32 y, f32 z) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}
#pragma dont_inline reset
