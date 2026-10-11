// include: manager/evtmgr_cmd.h
// include: dolphin/gx.h
// decl: #define KUSURI_COL (*(GXColor*)g_Kusuri_Col)
// decl: #define KUSURI_SRC ((GXColor*)g_Kusuri_Src_Col)
// proto: USER_FUNC(kusuri_color_get);
USER_FUNC(kusuri_color_get) {
    s32* args = event->args;

    evtSetValue(event, args[0], KUSURI_COL.r);
    evtSetValue(event, args[1], KUSURI_COL.g);
    evtSetValue(event, args[2], KUSURI_COL.b);
    return EVT_RETURN_DONE;
}
