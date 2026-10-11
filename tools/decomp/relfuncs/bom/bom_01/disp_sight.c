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
// include: sdk/texPalette.h
// include: dolphin/gx.h
// include: win/win_main.h
// decl: typedef struct BomSoundWork { u8 pad_0[0x330]; u16 sampleBank; u8 pad_332[0x5C0 - 0x332]; s16 samples[2][0x400]; u32 sampleIndex; } BomSoundWork;
// include: mario/mariost.h
// decl: extern BomSoundWork sound;
// decl: void drawBG(s32 id, f32 x, f32 y, f32 sx, f32 sy, f32 rot);
// decl: void drawNum(s32 num, s32 digits, f32 x, f32 y, f32 scale);
// proto: void disp_sight(CameraId camera, void* param);
void disp_sight(CameraId camera, void* param) {
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXColor black = {0x00, 0x00, 0x00, 0xFF};
    s32 i;
    s32 j;
    s32 n;
    s32 id;
    s32 on;
    f32 x;
    f32 y;

    drawBG(0, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    drawBG(0, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
    drawBG(0, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f);
    drawBG(0, 0.0f, 0.0f, -1.0f, -1.0f, 0.0f);
    drawBG(1, 0.0f, 0.0f, 1.0f, 1.0f, sight_wp->rot);
    drawBG(1, 0.0f, 0.0f, -1.0f, 1.0f, -sight_wp->rot);
    drawBG(1, 0.0f, 0.0f, 1.0f, -1.0f, -sight_wp->rot);
    drawBG(1, 0.0f, 0.0f, -1.0f, -1.0f, sight_wp->rot);
    if (sight_wp->dir == 2) {
        sight_wp->rot += 2.0f;
    } else if (sight_wp->dir == 3) {
        sight_wp->rot -= 2.0f;
    } else if (sight_wp->dir == 0) {
        sight_wp->rot -= 2.0f;
    } else {
        sight_wp->rot += 1.0f;
    }

    winTexInit(*sight_wp->tpl->data);
    winTexSet(5, (Vec){0.0f, 0.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black);
    for (id = 0; id < 3; id++) {
        if ((s32)(gp->retraceCount % 30) / 10 != id) {
            i = 4 - id;
            drawBG(i, 100.0f, 60.0f, 1.0f, 1.0f, 0.0f);
            drawBG(i, -100.0f, 60.0f, -1.0f, 1.0f, 0.0f);
            drawBG(i, 100.0f, -60.0f, 1.0f, -1.0f, 0.0f);
            drawBG(i, -100.0f, -60.0f, -1.0f, -1.0f, 0.0f);
        }
    }

    winTexInit(*sight_wp->tpl->data);
    winTexSet(23, (Vec){-200.0f, 150.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    drawNum(gp->renderTime / 100 / 1000, 10, 90.0f, 180.0f, 0.6f);
    drawNum(gp->renderTime / 200 / 1000, 8, 126.0f, 150.0f, 0.6f);
    drawNum(gp->renderTime / 300 / 1000, 6, 162.0f, 120.0f, 0.6f);
    drawNum(gp->renderTime / 400 / 1000, 6, 162.0f, 90.0f, 0.6f);
    drawNum(gp->retraceCount / 4, 4, 110.0f, -160.0f, 1.0f);
    drawNum(gp->retraceCount / 8, 2, 230.0f, -170.0f, 0.8f);

    winTexSet(8, (Vec){-210.0f, -140.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    if ((gp->retraceCount & 3) == 0) {
        for (i = 0; i < 4; i++) {
            sight_wp->level[i] = sight_wp->level[i + 1];
        }
        sight_wp->level[4] = abs(sound.samples[sound.sampleBank][sound.sampleIndex]);
    }
    for (i = 0; i < 5; i++) {
        n = sight_wp->level[i];
        n /= 300;
        if (n > 7) {
            n = 7;
        }
        x = -240.0f + 20.0f * i;
        for (j = 0; j < n; j++) {
            y = -190.0f + 16.0f * j;
            if (j == 6) {
                drawBG(10, x, y, 1.0f, 1.0f, 0.0f);
            } else {
                drawBG(9, x, y, 1.0f, 1.0f, 0.0f);
            }
        }
        for (j = n; j < 7; j++) {
            y = -190.0f + 16.0f * j;
            if (j == 6) {
                drawBG(12, x, y, 1.0f, 1.0f, 0.0f);
            } else {
                drawBG(11, x, y, 1.0f, 1.0f, 0.0f);
            }
        }
    }

    winTexInit(*sight_wp->tpl->data);
    for (i = 0; i < 4; i++) {
        on = (gp->retraceCount % 20 > 6 && i == sight_wp->dir) ? 1 : 0;
        id = 7;
        if (on) {
            id = 6;
        }
        if (sight_wp->dir == 4) {
            on = 0;
            id = 7;
        }
        switch (i) {
            case 0:
                drawBG(id, 16.0f, 180.0f, 1.0f, 1.0f, 90.0f);
                break;
            case 1:
                drawBG(id, -16.0f, -180.0f, 1.0f, 1.0f, 270.0f);
                break;
            case 2:
                drawBG(id, -180.0f, 16.0f, 1.0f, 1.0f, 180.0f);
                if (on && (gp->retraceCount & 3) == 0) {
                    sight_wp->count1++;
                }
                break;
            case 3:
                drawBG(id, 180.0f, -16.0f, 1.0f, 1.0f, 0.0f);
                if (on && (gp->retraceCount & 3) == 0) {
                    sight_wp->count2++;
                }
                break;
        }
    }
    drawNum(sight_wp->count1, 2, -220.0f, 0.0f, 0.8f);
    drawNum(sight_wp->count2, 2, 200.0f, 0.0f, 0.8f);
}
