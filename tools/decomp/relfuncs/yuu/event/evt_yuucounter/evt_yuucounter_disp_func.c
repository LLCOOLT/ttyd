// include: dolphin/os.h
// include: dolphin/mtx.h
// include: mario/mario.h
// include: mario/mariost.h
// include: driver/camdrv.h
// decl: typedef struct YuuCounterWork { EventEntry* event; u16 flags; u32 dispFlags; s32 type; f32 x; f32 y; s32 data; s32 field_0x1C; s64 elapsed; OSTime lastTime; s32 limit; s32 field_0x34; } YuuCounterWork;
// decl: static YuuCounterWork* _wp;
// decl: static const GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
// decl: static const GXColor bgColor = {0xFF, 0xFF, 0xFF, 0x99};
// decl: s32 yuunpc_juni(Vec* pos);
// decl: void iconDispGxCol(Mtx pos, s16 flags, u16 iconId, GXColor color);
// proto: void evt_yuucounter_disp_func(CameraId camera, void* param);
void evt_yuucounter_disp_func(CameraId camera, void* param) {
    YuuCounterWork* wp = param;
    GXColor color = white;
    GXColor numColor;
    GXColor iconColor;
    f32 scale;
    f32 xOfs;
    s32 value;
    s32 j;
    s32 secs;
    BOOL skip;
    BOOL skip2;
    s32 k;
    s32 i;
    s32 msecs;
    s32 iconId;
    s32 digit;
    s32 digits[4];
    Mtx mtx;
    Mtx scaleMtx;
    Mtx base;
    Vec pos;
    MarioWork* mario;

    iconColor = white;
    numColor = white;
    switch (wp->type) {
        case 0:
            if (!(wp->dispFlags & 2)) {
                mario = marioGetPtr();
                wp->data = (s32)(200.0f * (1300.0f + mario->position.x));
            }
            scale = 2.5f;
            xOfs = -50.0f;
            iconId = 0x202;
            if (wp->data < 0) {
                return;
            }
            break;
        case 1:
            if (!(wp->dispFlags & 2)) {
                if (wp->data >= 0) {
                    if (wp->dispFlags & 4) {
                        wp->dispFlags &= ~4;
                        wp->lastTime = gp->renderTime;
                    }
                    wp->elapsed += (s32)gp->renderTime - (s32)wp->lastTime;
                    wp->lastTime = gp->renderTime;
                    wp->data = wp->limit - OSTicksToMilliseconds(wp->elapsed);
                } else {
                    wp->data = -1;
                }
            }
            scale = 3.0f;
            iconId = 0x201;
            xOfs = -42.0f;
            break;
        case 2:
            if (!(wp->dispFlags & 2)) {
                mario = marioGetPtr();
                pos = mario->position;
                wp->data = yuunpc_juni(&pos);
            }
            scale = 2.5f;
            iconId = -1;
            xOfs = -46.0f;
            break;
    }

    if (wp->dispFlags & 1) {
        return;
    }
    value = wp->data;
    if (value < 0) {
        value = 0;
    }
    secs = value / 1000;
    msecs = value % 1000;
    PSMTXTrans(base, wp->x, wp->y, 0.0f);
    PSMTXScale(scaleMtx, scale, 1.0f, 1.0f);
    PSMTXConcat(base, scaleMtx, mtx);
    iconDispGxCol(mtx, 0x10, 0x1F6, bgColor);

    switch (wp->type) {
        case 0: {
            BOOL skip;
            skip = TRUE;
            digits[0] = secs / 100;
            secs %= 100;
            digits[1] = secs / 10;
            digits[2] = secs % 10;
            for (j = 0; j < 3; j++) {
                digit = digits[j];
                if (digit != 0 || j == 2) {
                    skip = FALSE;
                }
                if (!skip) {
                    PSMTXTrans(mtx, xOfs + (f32)(j * 30), 8.0f, 0.0f);
                    PSMTXConcat(base, mtx, mtx);
                    iconDispGxCol(mtx, 0x10, digit + 0x1F7, numColor);
                }
            }
            break;
        }
        case 1:
            digits[0] = secs / 60;
            secs %= 60;
            digits[1] = secs / 10;
            digits[2] = secs % 10;
            for (i = 0; i < 3; i++) {
                PSMTXTrans(mtx, xOfs + (f32)(i * 30) - (f32)((i == 0) * 16), 8.0f, 0.0f);
                PSMTXConcat(base, mtx, mtx);
                iconDispGxCol(mtx, 0x10, digits[i] + 0x1F7, numColor);
            }
            PSMTXTrans(mtx, 8.0f + xOfs, 12.0f, 0.0f);
            PSMTXScale(scaleMtx, 2.0f, 2.0f, 2.0f);
            PSMTXConcat(mtx, scaleMtx, mtx);
            PSMTXConcat(base, mtx, mtx);
            iconDispGxCol(mtx, 0x10, iconId, iconColor);
            break;
        case 2:
            skip2 = TRUE;
            value = (value + 1) % 100000;
            digits[0] = value / 1000;
            value %= 1000;
            digits[1] = value / 100;
            value %= 100;
            digits[2] = value / 10;
            digits[3] = value % 10;
            for (k = 0; k < 4; k++) {
                digit = digits[k];
                if (digit != 0 || k == 3) {
                    skip2 = FALSE;
                }
                if (!skip2) {
                    PSMTXTrans(mtx, xOfs + (f32)(k * 30), 8.0f, 0.0f);
                    PSMTXConcat(base, mtx, mtx);
                    iconDispGxCol(mtx, 0x10, digit + 0x1F7, numColor);
                }
            }
            break;
    }

    if (iconId != -1) {
        PSMTXTrans(mtx, 90.0f + xOfs - 12.0f, 10.0f, 0.0f);
        PSMTXConcat(base, mtx, mtx);
        iconDispGxCol(mtx, 0x10, iconId, iconColor);
    }

    switch (wp->type) {
        case 0:
        case 1:
            digits[0] = msecs / 100;
            digits[1] = (msecs % 100) / 10;
            for (i = 0; i < 2; i++) {
                PSMTXTrans(mtx, 90.0f + xOfs + (f32)(i * 15), 8.0f, 0.0f);
                PSMTXScale(scaleMtx, 0.5f, 0.5f, 0.5f);
                PSMTXConcat(mtx, scaleMtx, mtx);
                PSMTXConcat(base, mtx, mtx);
                iconDispGxCol(mtx, 0x10, digits[i] + 0x1F7, numColor);
            }
            break;
        case 2:
            break;
    }
}
