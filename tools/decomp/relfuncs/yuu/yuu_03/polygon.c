// include: dolphin/gx.h
// proto: static void polygon(f32 x, f32 y, f32 w, f32 h, f32 u, f32 v);
static void polygon(f32 x, f32 y, f32 w, f32 h, f32 u, f32 v) {
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x, y, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(x + w, y, 0.0f);
    GXTexCoord2f32(u, 0.0f);
    GXPosition3f32(x + w, y - h, 0.0f);
    GXTexCoord2f32(u, v);
    GXPosition3f32(x, y - h, 0.0f);
    GXTexCoord2f32(0.0f, v);
}
