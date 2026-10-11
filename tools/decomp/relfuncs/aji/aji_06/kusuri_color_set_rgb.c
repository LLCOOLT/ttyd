// include: manager/evtmgr_cmd.h
// include: dolphin/gx.h
// decl: #define KUSURI_COL (*(GXColor*)g_Kusuri_Col)
// decl: #define KUSURI_SRC ((GXColor*)g_Kusuri_Src_Col)
// proto: USER_FUNC(kusuri_color_set_rgb);
USER_FUNC(kusuri_color_set_rgb) {
    s32* args = event->args;
    s32 r = evtGetValue(event, args[0]);
    s32 g = evtGetValue(event, args[1]);
    s32 b = evtGetValue(event, args[2]);

    KUSURI_COL.r = r;
    KUSURI_COL.g = g;
    KUSURI_COL.b = b;
    return EVT_RETURN_DONE;
}
