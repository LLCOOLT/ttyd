// include: manager/evtmgr_cmd.h
// include: dolphin/gx.h
// include: mario/mariost.h
// include: dolphin/os.h
// decl: #define KUSURI_COL (*(GXColor*)g_Kusuri_Col)
// decl: #define KUSURI_SRC ((GXColor*)g_Kusuri_Src_Col)
// decl: s32 g_Kusuri_R;
// decl: s32 g_Kusuri_G;
// decl: s32 g_Kusuri_B;
// proto: USER_FUNC(kusuri_color_set);
USER_FUNC(kusuri_color_set) {
    s32* args = event->args;
    s32 no = evtGetValue(event, args[0]);
    s32 frames = evtGetValue(event, args[1]);
    OSTime now = gp->renderTime;
    s32 elapsed;
    BOOL done;
    f32 t;
    s32 r, g, b;

    if (isFirstCall) {
        event->lwData[8] = frames;
        event->lwData[9] = (KUSURI_COL.r << 16) | (KUSURI_COL.g << 8) | KUSURI_COL.b;
        event->userdata[0] = ((u64)now >> 32) & 0xFFFFFFFF;
        event->userdata[1] = now & 0xFFFFFFFF;
    }
    elapsed = OSTicksToMilliseconds((u64)(s32)((u32)now - event->userdata[1]));
    if (elapsed < event->lwData[8]) {
        done = FALSE;
        t = (f32)elapsed / (f32)event->lwData[8];
    } else {
        done = TRUE;
        t = 1.0f;
    }
    r = t * KUSURI_SRC[no - 1].r + g_Kusuri_R;
    g = t * KUSURI_SRC[no - 1].g + g_Kusuri_G;
    b = t * KUSURI_SRC[no - 1].b + g_Kusuri_B;
    if (r > g) {
        if (r > b) {
            KUSURI_COL.r = 255;
            KUSURI_COL.g = 255.0f * ((f32)g / (f32)r);
            KUSURI_COL.b = 255.0f * ((f32)b / (f32)r);
        } else {
            KUSURI_COL.r = 255.0f * ((f32)r / (f32)b);
            KUSURI_COL.g = 255.0f * ((f32)g / (f32)b);
            KUSURI_COL.b = 255;
        }
    } else if (g > b) {
        KUSURI_COL.r = 255.0f * ((f32)r / (f32)g);
        KUSURI_COL.g = 255;
        KUSURI_COL.b = 255.0f * ((f32)b / (f32)g);
    } else {
        KUSURI_COL.r = 255.0f * ((f32)r / (f32)b);
        KUSURI_COL.g = 255.0f * ((f32)g / (f32)b);
        KUSURI_COL.b = 255;
    }
    if (done) {
        g_Kusuri_R = r;
        g_Kusuri_G = g;
        g_Kusuri_B = b;
    }
    if (done) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
