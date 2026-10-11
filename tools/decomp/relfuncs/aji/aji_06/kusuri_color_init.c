// include: manager/evtmgr_cmd.h
// include: dolphin/gx.h
// decl: #define KUSURI_COL (*(GXColor*)g_Kusuri_Col)
// decl: #define KUSURI_SRC ((GXColor*)g_Kusuri_Src_Col)
// decl: s32 g_Kusuri_R;
// decl: s32 g_Kusuri_G;
// decl: s32 g_Kusuri_B;
// proto: USER_FUNC(kusuri_color_init);
USER_FUNC(kusuri_color_init) {
    KUSURI_COL.r = 0;
    KUSURI_COL.g = 0;
    KUSURI_COL.b = 0;
    g_Kusuri_R = 0;
    g_Kusuri_G = 0;
    g_Kusuri_B = 0;
    return EVT_RETURN_DONE;
}
