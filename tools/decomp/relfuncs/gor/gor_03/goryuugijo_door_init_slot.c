// include: driver/camdrv.h
// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: void mapObjRotate(const char* name, f32 x, f32 y, f32 z);
// decl: void goryuugijo_upsidewindow_disp_sub(s32 slot, s32 reel);
// include: system.h
// decl: typedef struct GoryuuWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } GoryuuWork;
// decl: typedef struct SlotWork { u32 flags; s32 phase; f32 reberAngle; f32 angle[2][3]; f32 speed[3]; s8 state[3]; s8 face[2][3]; s8 stopCount[3]; s32 wait[3]; s32 extra[3]; s32 counter; s32 neonCount; s32 monteCount; s32 nowSlot; s32 caseId[2]; EventEntry* monteEvt; s32 sfxId; s16 cursor; } SlotWork;
// decl: typedef struct SlotDrum { const char* drum[3]; const char* reber; const char* anim; const char* window[3][3]; const char* neon[3]; } SlotDrum;
// decl: #define DRUMNAME ((SlotDrum*)drumname)
// decl: #define UPSIDEGARA ((s32(*)[3][8])upsidegara)
// proto: USER_FUNC(goryuugijo_door_init_slot);
USER_FUNC(goryuugijo_door_init_slot) {
    GoryuuWork* wp = (GoryuuWork*)evtGetValue(event, event->args[0]);
    SlotWork* data = wp->data;
    s32 j;
    s32 i;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            data->angle[i][j] = 0.0f;
            if (data->angle[i][j] >= 360.0f) {
                data->angle[i][j] -= 360.0f;
            }
            data->angle[i][j] = 45.0f * irand(8);
            mapObjRotate(DRUMNAME[i].drum[j], 0.0f, 0.0f, data->angle[i][j]);
            data->face[i][j] = UPSIDEGARA[i][j][irand(8)];
            goryuugijo_upsidewindow_disp_sub(i, j);
        }
    }
    return EVT_RETURN_DONE;
}
