// include: driver/punidrv.h
// decl: extern u32 anim_ext_tex_size;
// decl: void animPoseDisp_MakeExtTexture(const char* group, const char* anim, f32 frame, f32 scale, GXTexObj* obj, void*** image, s32* x0, s32* y0, s32* x1, s32* y1);
// proto: void puniMakeTexture(CameraId camId, void* param);
void puniMakeTexture(CameraId camId, void* param) {
    PunidrvWork* wp = work;
    PunidrvTexInfo* info = param;
    PunidrvTex* tex = wp->texs;
    s32 i;
    s32 n;
    s32 v;
    f32 scale = 0.34246576f;
    s32 x0, y0, x1, y1;

    anim_ext_tex_size = 0;
    for (i = 0; i < wp->texNum; i++, info++, tex++) {
        n = i * 12;
        animPoseDisp_MakeExtTexture(info->group, info->anim, info->frame, 5.84f, &tex->obj, &tex->image, &x0, &y0, &x1, &y1);
        wp->vtx[n++] = x0 * scale;
        wp->vtx[n++] = -y0 * scale;
        wp->vtx[n++] = 0.0f;
        wp->vtx[n++] = x1 * scale;
        wp->vtx[n++] = -y0 * scale;
        wp->vtx[n++] = 0.0f;
        wp->vtx[n++] = x1 * scale;
        wp->vtx[n++] = -y1 * scale;
        wp->vtx[n++] = 0.0f;
        wp->vtx[n++] = x0 * scale;
        wp->vtx[n++] = -y1 * scale;
        wp->vtx[n++] = 0.0f;
        GXBeginDisplayList(&wp->dl[i * 0x80], 0x80);
        v = i * 4;
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition1x16(v++);
        GXTexCoord1x16(0);
        GXPosition1x16(v++);
        GXTexCoord1x16(1);
        GXPosition1x16(v++);
        GXTexCoord1x16(2);
        GXPosition1x16(v++);
        GXTexCoord1x16(3);
        GXEnd();
        wp->dlSize[i] = GXEndDisplayList();
    }
}
