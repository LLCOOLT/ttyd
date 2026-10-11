// include: manager/fontmgr.h
// include: mario/mariost.h
// include: sdk/DEMOInit.h
// decl: void FontDrawString(f32 x, f32 y, const char* str);
// proto: void movie_draw(CameraId camera, void* param);
void movie_draw(CameraId camera, void* param) {
    u16 width;
    u16 height;
    const char* msg;
    u32 type;

    EXIGetType(0, 2, &type);
    if (type == 0x05070000) {
        msg = "\202\261\202\261\202\311\203\200\201[\203r\201[\202\252\202\310\202\252\202\352\202\334\202\267";
        FontDrawStart();
        FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
        FontDrawString(-FontGetMessageWidth(msg) / 2, 0.0f, msg);
        (*DIG_WP)++;
    } else {
        width = gp->fbWidth;
        height = gp->efbHeight;
        if (THPSimpleDecode(0) != 1) {
            *DIG_WP = THPSimpleDrawCurrentFrame(DEMOGetRenderModeObj(), 0, 0, width, height);
        }
    }
}
