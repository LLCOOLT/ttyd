// include: manager/evtmgr_cmd.h
// include: driver/swdrv.h
// include: memory.h
// decl: typedef struct RankEntry { u16 flags; s32 id; union { s16 score; u8 sw[2]; }; } RankEntry;
// decl: typedef struct RankWork { s32 num; RankEntry* entries; } RankWork;
// decl: typedef struct DispWork { f32 y; f32 targetY; s32 page; } DispWork;
// decl: typedef struct FighterData { u16 flags; const char* name; const char* name2; s32 info; s32 msg1; s32 msg2; s16 score; } FighterData;
// decl: typedef struct RuleData { s32 name; const char* msg; s32 id; s32 a; s32 b; } RuleData;
// decl: static __declspec(section ".data") RankWork* rank_wp;
// decl: static __declspec(section ".data") DispWork* dwp;
// include: manager/fontmgr.h
// include: driver/msgdrv.h
// include: driver/windowdrv.h
// include: driver/icondrv.h
// include: driver/camdrv.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// include: stdio.h
// decl: static s32 fighterDt_raw[161];
// decl: #define fighterDt ((FighterData*)fighterDt_raw)
// decl: static s32 fighterDt_re_raw[147];
// decl: #define fighterDt_re ((FighterData*)fighterDt_re_raw)
// decl: static __declspec(section ".data") const char* suuji[10];
// decl: void FontDrawMessageMtx(Mtx mtx, const char* msg);
// decl: void FontDrawScale(f32 scale);
// proto: static void disp_proc(CameraId cameraId, void* param);
static void disp_proc(CameraId cameraId, void* param) {
    FighterData* dt;
    f32 x;
    f32 tx;
    f32 y;
    u16 sx;
    u16 sw;
    s32 rank;
    s32 yoff;
    s32 i;
    u16 w;
    Mtx scale;
    Mtx mtx;
    char buf[0x100];

    if (evtGetValue(NULL, GSW(0)) < 0xAC) {
        dt = fighterDt;
    } else {
        dt = fighterDt_re;
    }
    x = -250.0f * 0.5f;
    windowDispGX_System(0, 0xFF, x - 30.0f, 165.0f, 310.0f, 330.0f);
    FontDrawStart();
    FontDrawScale(1.0f);
    w = FontGetMessageWidth("\203\211\203\223\203L\203\223\203O");
    {
        GXColor color = {0xDC, 0xC8, 0xDC, 0xFF};
        FontDrawColor(color);
    }
    FontDrawMessage(-w / 2, 135.0f, "\203\211\203\223\203L\203\223\203O");
    sx = 304.0f + x;
    sw = 250.0f;
    GXSetScissor(sx, (u16)145.0f, sw, (u16)220.0f);
    tx = 10.0f + x;
    rank = 0;
    yoff = 0;
    for (i = 0; i < rank_wp->num; i++) {
        y = dwp->y + (135.0f - yoff - 40.0f);
        if (!(rank_wp->entries[i].flags & 2)) {
            PSMTXScale(scale, 0.8f, 0.8f, 0.8f);
            if (rank != 0) {
                sprintf(buf, "%s%s", rank / 10 ? suuji[rank / 10] : "", suuji[rank % 10]);
                FontDrawStart();
                {
                    GXColor color = {0xDC, 0xC8, 0xDC, 0xFF};
                    FontDrawColor(color);
                }
                PSMTXTrans(mtx, tx, y, 0.0f);
                PSMTXConcat(mtx, scale, mtx);
                FontDrawMessageMtx(mtx, buf);
            }
            FontDrawStart();
            if (rank_wp->entries[i].flags & 4) {
                GXColor color = {0xFF, 0x00, 0x00, 0xFF};
                FontDrawColor(color);
            } else {
                GXColor color = {0xDC, 0xC8, 0xDC, 0xFF};
                FontDrawColor(color);
            }
            PSMTXTrans(mtx, 40.0f + tx, y, 0.0f);
            PSMTXConcat(mtx, scale, mtx);
            FontDrawMessageMtx(mtx, msgSearch(dt[rank_wp->entries[i].id].name));
            rank++;
            yoff += 20;
        }
    }
    GXSetScissor(sx, (u16)137.0f, sw, (u16)228.0f);
    {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = 15.0f + x;
        pos.y = 95.0f + dwp->y - 24.0f;
        iconDispGx(&pos, 0x10, 0x123, 0.8f);
    }
    GXSetScissor(0, 0, 0x260, 0x1E0);
    if (dwp->page > 0) {
        {
            Vec pos = {0.0f, 125.0f, 0.0f};
            pos.x = x + 250.0f;
            iconDispGx(&pos, 0x10, 0x205, -1.0f);
        }
        {
            Vec pos = {0.0f, 75.0f, 0.0f};
            pos.x = x + 250.0f;
            iconDispGx(&pos, 0x10, 0x7E, 0.6f);
        }
    }
    if (dwp->page < 1) {
        {
            Vec pos = {0.0f, -140.0f, 0.0f};
            pos.x = x + 250.0f;
            iconDispGx(&pos, 0x10, 0x205, 1.0f);
        }
        {
            Vec pos = {0.0f, -125.0f, 0.0f};
            pos.x = x + 250.0f;
            iconDispGx(&pos, 0x10, 0x80, 0.6f);
        }
    }
}
