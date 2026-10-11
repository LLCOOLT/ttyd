// include: dolphin/gx.h
// proto: void GXSetTexCoordGen_(GXTexCoordID dst, GXTexGenType func, GXTexGenSrc src, u32 mtx);
#pragma dont_inline on
void GXSetTexCoordGen_(GXTexCoordID dst, GXTexGenType func, GXTexGenSrc src, u32 mtx) {
    GXSetTexCoordGen2(dst, func, src, mtx, GX_FALSE, GX_PTIDENTITY);
}
#pragma dont_inline reset
