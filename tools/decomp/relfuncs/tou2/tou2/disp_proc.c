// include: tou2.h
// include: dolphin/types.h
// include: dolphin/mtx.h
// include: dolphin/gx.h
// include: driver/swdrv.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: driver/camdrv.h
// include: driver/effdrv.h
// include: driver/dispdrv.h
// include: driver/windowdrv.h
// include: driver/icondrv.h
// include: driver/msgdrv.h
// include: manager/fontmgr.h
// include: manager/evtmgr_cmd.h
// include: evt/evt_cmd.h
// include: battle/battle_monosiri.h
// include: data/mapdata.h
// include: mario/mario_pouch.h
// include: pmario_sound.h
// include: system.h
// include: memory.h
// include: string.h
// include: stdio.h
// note: tou2.c is hand-maintained (typed data/structs are defined there); this snippet mirrors it
// proto: static void disp_proc(CameraId cameraId, void* param);
static void disp_proc(CameraId cameraId, void* param) {
    FighterData* fighters;
    f32 winW;
    f32 left;
    f32 top;
    f32 x;
    s32 width;
    u16 scissorX;
    u16 scissorW;
    s32 i;
    s32 num;
    f32 y;
    Mtx scale;
    Mtx mtx;
    char buf[0x100];

    fighters = evtGetValue(NULL, GSW(0)) < 172 ? fighterDt : fighterDt_re;
    winW = 250.0f;
    left = -winW / 2.0f;
    windowDispGX_System(0, 0xFF, left - 30.0f, 165.0f, 310.0f, 330.0f);
    FontDrawStart();
    FontDrawScale(1.0f);
    width = FontGetMessageWidth("\x83\x89\x83\x93\x83\x4C\x83\x93\x83\x4F");
    {
        GXColor color = titleColor;
        FontDrawColor(color);
    }
    top = 135.0f;
    FontDrawMessage(-width / 2, top, "\x83\x89\x83\x93\x83\x4C\x83\x93\x83\x4F");
    {
        f32 sy = 145.0f;
        f32 sh = 220.0f;
        scissorX = 304.0f + left;
        scissorW = winW;
        GXSetScissor(scissorX, (u16)sy, scissorW, (u16)sh);
    }


    num = 0;
    for (i = 0; i < rank_wp->count; i++) {
        x = 10.0f + left;
        y = dwp->scroll + (top - num * 20 - 40.0f);
        if (rank_wp->entries[i].flags & RANK_HIDDEN) {
            continue;
        }
        PSMTXScale(scale, 0.8f, 0.8f, 0.8f);
        if (num != 0) {
            sprintf(buf, "%s%s", num / 10 ? suuji[num / 10] : "", suuji[num % 10]);
            FontDrawStart();
            {
                GXColor color = numberColor;
                FontDrawColor(color);
            }
            PSMTXTrans(mtx, x, y, 0.0f);
            PSMTXConcat(mtx, scale, mtx);
            FontDrawMessageMtx(mtx, buf);
        }
        FontDrawStart();
        if (rank_wp->entries[i].flags & RANK_PLAYER) {
            GXColor color = playerColor;
            FontDrawColor(color);
        } else {
            GXColor color = nameColor;
            FontDrawColor(color);
        }
        x = 40.0f + x;
        PSMTXTrans(mtx, x, y, 0.0f);
        PSMTXConcat(mtx, scale, mtx);
        FontDrawMessageMtx(mtx, msgSearch(fighters[rank_wp->entries[i].id].name));
        num++;
    }
    {
        f32 sy = 137.0f;
        f32 sh = 228.0f;
        GXSetScissor(scissorX, (u16)sy, scissorW, (u16)sh);
    }
    {
        f32 y = 95.0f + dwp->scroll;
        Vec pos = cursorPos;
        pos.x = 15.0f + left;
        pos.y = y - 24.0f;
        iconDispGx(&pos, 0x10, 0x123, 0.8f);
    }
    GXSetScissor(0, 0, 608, 480);
    if (dwp->page > 0) {
        {
            Vec pos = upArrowPos;
            pos.x = left + winW;
            iconDispGx(&pos, 0x10, 0x205, -1.0f);
        }
        {
            Vec pos = upButtonPos;
            pos.x = left + winW;
            iconDispGx(&pos, 0x10, 0x7E, 0.6f);
        }
    }
    if (dwp->page < 1) {
        {
            Vec pos = downArrowPos;
            pos.x = left + winW;
            iconDispGx(&pos, 0x10, 0x205, 1.0f);
        }
        {
            Vec pos = downButtonPos;
            pos.x = left + winW;
            iconDispGx(&pos, 0x10, 0x80, 0.6f);
        }
    }
}
