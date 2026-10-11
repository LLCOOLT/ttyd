// include: driver/punidrv.h
// include: memory.h
// proto: void puniLoadTexture(void);
void puniLoadTexture(void) {
    PunidrvWork* wp = work;
    PunidrvTex* tex = wp->texs;
    s32 i;
    u32 offset = 0;
    u32 size;

    GXInvalidateTexAll();
    for (i = 0; i < wp->texNum; i++, tex++) {
        size = GXGetTexBufferSize(GXGetTexObjWidth(&tex->obj), GXGetTexObjHeight(&tex->obj),
                                  GXGetTexObjFmt(&tex->obj), GX_FALSE, 0);
        if (offset < 0x80000 && offset + size >= 0x80000) {
            offset = 0x80000;
        }
        GXInitTexPreLoadRegion(&tex->region, offset, size, 0, 0);
        GXPreLoadEntireTexture(smartTexObj(&tex->obj, tex->image), &tex->region);
        offset += size;
    }
    wp->usedTmem = offset;
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
}
