// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// include: driver/icondrv.h
// include: driver/swdrv.h
// include: system.h
// decl: typedef struct IraiWork { s32 state; s32 count; s32 list[30]; s32 cursor; s32 last; s32 top; s32 yubiX; s32 yubiY; s32 field_0x94; f32 scroll; char client[30][21]; char contents[30][31]; u8 field_0x6B4[0x416C - 0x6B4]; } IraiWork;
// decl: void psndSFXOn(const char* name);
// decl: void irai_window_disp(CameraId camera, void* param);
// proto: USER_FUNC(irai_main_func);
USER_FUNC(irai_main_func) {
    IraiWork* wp = (IraiWork*)event->lwData[10];
    s32 prev;
    s32 n;

    switch (wp->state) {
        case 0:
            iconEntry2D("iraiYubi", 0x1F0);
            iconFlagOn("iraiYubi", 4);
            iconEntry2D("iraiArrowUp", 0x205);
            iconFlagOn("iraiArrowUp", 8);
            iconEntry2D("iraiArrowDown", 0x205);
            iconEntry2D("iraiLButton", 0x7E);
            iconSetScale("iraiLButton", 0.8f);
            iconEntry2D("iraiRButton", 0x80);
            iconSetScale("iraiRButton", 0.8f);
            iconFlagOn("iraiYubi", 2);
            iconFlagOn("iraiArrowUp", 2);
            iconFlagOn("iraiArrowDown", 2);
            iconFlagOn("iraiLButton", 2);
            iconFlagOn("iraiRButton", 2);
            wp->state = 1;
            psndSFXOn((const char*)0x2A);
            break;
        case 1:
            if ((keyGetButtonTrg(0) & 0x100) && swByteGet(1420) == 0 && !swGet(wp->list[wp->cursor] + 5374)) {
                psndSFXOn((const char*)0x12);
                wp->state = 100;
                break;
            }
            if (keyGetButtonTrg(0) & 0x200) {
                psndSFXOn((const char*)0x13);
                wp->state = 101;
                break;
            }
            prev = wp->cursor;
            if (keyGetDirRep(0) & 0x2000) {
                if (wp->count - 1 <= wp->cursor) {
                    if (keyGetDirTrg(0) & 0x2000) {
                        psndSFXOn((const char*)5);
                        wp->cursor++;
                    }
                } else {
                    psndSFXOn((const char*)5);
                    wp->cursor++;
                }
            }
            if (keyGetDirRep(0) & 0x1000) {
                if (wp->cursor <= 0) {
                    if (keyGetDirTrg(0) & 0x1000) {
                        psndSFXOn((const char*)5);
                        wp->cursor--;
                    }
                } else {
                    psndSFXOn((const char*)5);
                    wp->cursor--;
                }
            }
            if (wp->cursor >= wp->count) {
                wp->cursor = 0;
                wp->top = 0;
            }
            if (wp->cursor < 0) {
                wp->cursor = wp->count - 1;
                n = wp->count - 10;
                if (n > 0) {
                    wp->top = n;
                }
            }
            if (prev < wp->cursor) {
                if (wp->cursor - wp->top > 7 && wp->top < wp->count - 10) {
                    wp->top++;
                }
            } else if (prev > wp->cursor) {
                if (wp->cursor - wp->top < 3 && wp->top > 0) {
                    wp->top--;
                }
            }
            if (wp->top > 0 && (keyGetButtonTrg(0) & 0x40)) {
                n = 10;
                if (wp->top < 10) {
                    n = wp->top;
                }
                wp->top -= n;
                wp->cursor -= n;
                psndSFXOn((const char*)5);
            }
            if (wp->top < wp->count - 10 && (keyGetButtonTrg(0) & 0x20)) {
                n = 10;
                if (-wp->top + (wp->count - 10) < 10) {
                    n = -wp->top + (wp->count - 10);
                }
                wp->top += n;
                wp->cursor += n;
                psndSFXOn((const char*)5);
            }
            if (wp->cursor != wp->last) {
                wp->field_0x94 = 0;
            }
            wp->last = wp->cursor;
            wp->scroll += (wp->top * 30 - wp->scroll) / 6.0f;
            wp->yubiX = -129;
            wp->yubiY = 120 - (wp->cursor - wp->top) * 30;
            iconSetPos("iraiYubi", wp->yubiX, wp->yubiY, 0.0f);
            iconFlagOff("iraiYubi", 2);
            iconSetPos("iraiArrowUp", 231.0f, 178.0f, 0.0f);
            iconSetPos("iraiArrowDown", 231.0f, -190.0f, 0.0f);
            iconSetPos("iraiLButton", 261.0f, 146.0f, 0.0f);
            iconSetPos("iraiRButton", 261.0f, -190.0f, 0.0f);
            if (wp->top == 0) {
                iconFlagOn("iraiArrowUp", 2);
                iconFlagOn("iraiLButton", 2);
            } else {
                iconFlagOff("iraiArrowUp", 2);
                iconFlagOff("iraiLButton", 2);
            }
            if (wp->top >= wp->count - 10) {
                iconFlagOn("iraiArrowDown", 2);
                iconFlagOn("iraiRButton", 2);
            } else {
                iconFlagOff("iraiArrowDown", 2);
                iconFlagOff("iraiRButton", 2);
            }
            break;
        case 100:
            event->lwData[0] = wp->list[wp->cursor];
            wp->state = 0;
            iconDelete("iraiYubi");
            iconDelete("iraiArrowUp");
            iconDelete("iraiArrowDown");
            iconDelete("iraiLButton");
            iconDelete("iraiRButton");
            psndSFXOn((const char*)0x2B);
            return EVT_RETURN_DONE;
        case 101:
            event->lwData[0] = -1;
            wp->state = 0;
            iconDelete("iraiYubi");
            iconDelete("iraiArrowUp");
            iconDelete("iraiArrowDown");
            iconDelete("iraiLButton");
            iconDelete("iraiRButton");
            psndSFXOn((const char*)0x2B);
            return EVT_RETURN_DONE;
    }
    dispEntry(CAMERA_2D, 300.0f, 0, irai_window_disp, wp);
    return EVT_RETURN_BLOCK;
}
