// include: driver/camdrv.h
// include: driver/msgdrv.h
// include: driver/swdrv.h
// include: driver/windowdrv.h
// include: manager/fontmgr.h
// include: dolphin/gx.h
// decl: typedef struct IraiWork { s32 state; s32 count; s32 list[30]; s32 cursor; s32 last; s32 top; s32 yubiX; s32 yubiY; s32 field_0x94; f32 scroll; char client[30][21]; char contents[30][31]; u8 field_0x6B4[0x416C - 0x6B4]; } IraiWork;
// decl: void FontDrawString(const char* message, f32 x, f32 y);
// decl: void FontDrawScale(f32 scale);
// proto: void irai_window_disp(CameraId camera, void* param);
void irai_window_disp(CameraId camera, void* param) {
    IraiWork* wp = param;
    u32 left;
    u32 top;
    u32 width;
    u32 height;
    const char* msg;
    s32 i;
    s32 no;

    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA3, 0xFF, 0xFF}, -280.0f, 170.0f, 135.0f, 90.0f, 12.0f);
    FontDrawStart();
    FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    FontDrawScale(0.85f);
    msg = msgSearch("irai_name1_win");
    FontDrawEdge();
    FontDrawString(msg, -270.0f, 152.0f);
    FontDrawString(msgSearch("irai_name2_win"), -270.0f, 127.0f);
    FontDrawEdgeOff();
    windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -129.0f, 170.0f, 410.0f, 340.0f, 12.0f);
    windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA3, 0xFF, 0xFF}, -103.0f, 190.0f, 120.0f, 40.0f, 12.0f);
    windowDispGX_Waku_col(0, (GXColor){0x2B, 0xA3, 0xFF, 0xFF}, 91.0f, 190.0f, 120.0f, 40.0f, 12.0f);
    FontDrawStart();
    FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    FontDrawScale(0.85f);
    msg = msgSearch("irai_client_win");
    FontDrawEdge();
    FontDrawString(msg, -77.0f, 180.0f);
    FontDrawEdgeOff();
    msg = msgSearch("irai_contents_win");
    FontDrawEdge();
    FontDrawString(msg, 115.0f, 180.0f);
    FontDrawEdgeOff();
    GXGetScissor(&left, &top, &width, &height);
    GXSetScissor(175, 98, 410, 304);
    FontDrawStart();
    FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
    FontDrawScale(0.85f);
    for (i = 0; i < wp->count; i++) {
        if (swGet(wp->list[i] + 5374)) {
            FontDrawColor((GXColor){0x80, 0x80, 0x80, 0xFF});
        } else {
            FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
        }
        if (wp->list[i] == swByteGet(1420)) {
            FontDrawColor((GXColor){0xFF, 0x00, 0x00, 0xFF});
        }
        no = wp->list[i] - 1;
        FontDrawString(wp->client[no], -119.0f, wp->scroll + (140 - i * 30));
        FontDrawString(wp->contents[no], 51.0f, wp->scroll + (140 - i * 30));
    }
    GXSetScissor(left, top, width, height);
}
