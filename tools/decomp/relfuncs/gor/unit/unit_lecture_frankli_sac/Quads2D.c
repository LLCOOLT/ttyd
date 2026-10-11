// include: dolphin/gx.h
// proto: void Quads2D(f32 x0, f32 y0, f32 x1, f32 y1);
void Quads2D(f32 x0, f32 y0, f32 x1, f32 y1) {
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x0, y0, 0.0f);
    GXPosition3f32(x1, y0, 0.0f);
    GXPosition3f32(x1, y1, 0.0f);
    GXPosition3f32(x0, y1, 0.0f);
}
