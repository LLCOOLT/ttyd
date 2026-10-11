// include: memory.h
// include: string.h
// include: stdlib.h
// include: system.h
// include: manager/filemgr.h
// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// include: driver/camdrv.h
// decl: typedef struct SightWork { FileEntry* tpl; s32 level[5]; f32 rot; s32 dir; s32 count1; s32 count2; } SightWork;
// decl: SightWork* sight_wp;
// include: win/win_main.h
// include: sdk/texPalette.h
// include: dolphin/gx.h
// proto: void drawNum(s32 num, s32 digits, f32 x, f32 y, f32 scale);
void drawNum(s32 num, s32 digits, f32 x, f32 y, f32 scale) {
    GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
    GXTexObj obj;
    s32 i;
    s32 id;
    f32 w;
    s32 n = num < 0 ? -num : num;

    winTexInit(*sight_wp->tpl->data);
    for (i = 0; i < digits; i++) {
        id = n % 10 + 13;
        TEXGetGXTexObjFromPalette(*sight_wp->tpl->data, &obj, id);
        w = scale * GXGetTexObjWidth(&obj);
        w += 2.0f;
        winTexSet(id, (Vec){x + w * (digits - i - 1), y, 0.0f},
                  (Vec){scale, scale, scale}, color);
        n /= 10;
    }
}
