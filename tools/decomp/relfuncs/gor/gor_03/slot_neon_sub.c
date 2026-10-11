// include: driver/camdrv.h
// include: system.h
// decl: typedef struct GoryuuWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } GoryuuWork;
// decl: typedef struct SlotWork { u32 flags; s32 phase; f32 reberAngle; f32 angle[2][3]; f32 speed[3]; s8 state[3]; s8 face[2][3]; s8 stopCount[3]; s32 wait[3]; s32 extra[3]; s32 counter; s32 neonCount; s32 monteCount; s32 nowSlot; s32 caseId[2]; EventEntry* monteEvt; s32 sfxId; s16 cursor; } SlotWork;
// decl: typedef struct SlotDrum { const char* drum[3]; const char* reber; const char* anim; const char* window[3][3]; const char* neon[3]; } SlotDrum;
// decl: #define DRUMNAME ((SlotDrum*)drumname)
// decl: #define UPSIDEGARA ((s32(*)[3][8])upsidegara)
// decl: void mapPlayAnimationLv(const char* name, s32 a, s32 b);
// decl: void goryuugijo_upsidewindow_disp_sub(s32 slot, s32 reel);
// decl: void goryuugijo_upsidewindow_dispoff_sub(s32 slot, s32 reel);
// proto: void slot_neon_sub(GoryuuWork* wp, SlotWork* data);
void slot_neon_sub(GoryuuWork* wp, SlotWork* data) {
    s32 i;
    s32 r;

    if (data->neonCount > 78) {
        return;
    }
    if (data->neonCount == 0) {
        if (irand(10) == 0) {
            data->flags |= 2;
        }
        data->flags &= ~2;
    }
    if (data->neonCount < 27) {
        if (data->neonCount & 1) {
            for (i = 0; i < 3; i++) {
                r = irand(8);
                while (data->face[data->nowSlot][i] == UPSIDEGARA[data->nowSlot][i][r]) {
                    r = (r + 1) & 7;
                }
                data->face[data->nowSlot][i] = UPSIDEGARA[data->nowSlot][i][r];
                if (data->flags & 2) {
                    goryuugijo_upsidewindow_disp_sub(data->nowSlot, i);
                } else {
                    goryuugijo_upsidewindow_dispoff_sub(data->nowSlot, i);
                }
            }
        }
    } else if (data->neonCount == 27) {
        for (i = 0; i < 3; i++) {
            data->face[data->nowSlot][i] = i;
            goryuugijo_upsidewindow_disp_sub(data->nowSlot, i);
        }
        if (data->face[data->nowSlot][0] == data->face[data->nowSlot][1] && data->face[data->nowSlot][1] == data->face[data->nowSlot][2]) {
            data->flags |= 4;
        }
        if ((data->flags & 4) && (data->flags & 2)) {
            data->speed[0] = data->speed[1] = data->speed[2] = 2.8125f;
        } else {
            data->speed[0] = data->speed[1] = data->speed[2] = 11.25f;
        }
        data->state[0] = data->state[1] = data->state[2] = 2;
    } else if (data->flags & 4) {
        if (data->neonCount == 33 || data->neonCount == 51 || data->neonCount == 69) {
            for (i = 0; i < 3; i++) {
                goryuugijo_upsidewindow_dispoff_sub(data->nowSlot, i);
            }
        }
        if (data->neonCount == 42 || data->neonCount == 60 || data->neonCount == 78) {
            for (i = 0; i < 3; i++) {
                goryuugijo_upsidewindow_disp_sub(data->nowSlot, i);
            }
        }
    }
    if (data->flags & 2) {
        if (data->neonCount == 0 || data->neonCount == 12 || data->neonCount == 24) {
            mapPlayAnimationLv(DRUMNAME[data->nowSlot].neon[0], 0, 0);
        }
        if (data->neonCount == 6 || data->neonCount == 18) {
            mapPlayAnimationLv(DRUMNAME[data->nowSlot].neon[1], 0, 0);
        }
    } else if (data->neonCount == 24) {
        mapPlayAnimationLv(DRUMNAME[data->nowSlot].neon[0], 0, 0);
    }
    if (data->neonCount <= 78) {
        data->neonCount++;
    }
}
