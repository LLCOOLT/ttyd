// include: driver/animdrv.h
// include: driver/npcdrv.h
// include: driver/dispdrv.h
// include: driver/camdrv.h
// include: driver/mapdrv.h
// include: driver/msgdrv.h
// include: driver/windowdrv.h
// include: driver/swdrv.h
// include: manager/evtmgr.h
// include: manager/evtmgr_cmd.h
// include: manager/filemgr.h
// include: manager/fontmgr.h
// include: mario/mariost.h
// include: memory.h
// include: string.h
// include: stdio.h
// include: pmario_sound.h
// include: system.h
// include: sdk/texPalette.h
// include: data/mapdata.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: #define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct EndMoa { Vec pos; s32 chain; s32 idx; } EndMoa;
// decl: typedef struct EndExtData { const char* anim; const char* pose; f32 speed; } EndExtData;
// decl: typedef struct EndWork { FileEntry* tpl; s32 mode; s32 alpha; s32 alpha2; s32 tevAlpha; s32 win1[3]; s32 win2[3]; s32 field_0x2c; s32 pos; EventEntry* evt; } EndWork;
// decl: typedef struct CreditMsg { s32 field_0x0; s32 pos; s32 type; const char* msg1[3]; const char* msg2[3]; } CreditMsg;
// decl: typedef struct CreditNpc { const char* agb; const char* anim; s32* evt; } CreditNpc;
// decl: typedef struct CreditActor { s32 state; s32 poseId; f32 angle; f32 limit; s32 pos; Mtx mtx; } CreditActor;
// decl: EndMoa* unk_end_bss00000000;
// decl: EndExtData* unk_end_bss00000004;
// decl: s32* unk_end_bss00000008;
// decl: s32 (*unk_end_bss0000000c)[2];
// decl: EndWork unk_end_bss00000010;
// decl: extern EndWork* dat_ptr_end_00003218;
// decl: extern CreditMsg unk_end_0000321c[50];
// decl: extern CreditNpc R_credits_npc_info[152];
// decl: extern const char* dat_ptr_end_00005034;
// decl: extern const char* dat_ptr_end_00005038;
// decl: extern const char* g_moamoa_chain_tbl[][2];
// decl: extern const s32 dat_80419a28;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: void extReset(void);
// decl: void extLoadRenderMode(void);
// decl: void extLoadVertex(void);
// decl: void extLoadTexture(void);
// decl: void extLoadTev(void);
// decl: void extDraw(void);
// decl: void extLoadTextureExit(void);
// decl: int rand(void);
// decl: double tan(double x);
// decl: s32 EXIGetType(s32 chan, u32 dev, u32* type);
// decl: void L_animPoseWorldPositionEvalOff(s32 poseId);
// decl: void animPoseVivianMain(s32 poseId, Vec* pos);
// decl: s32 msgWindow_Entry(const char* msg, s32 a, s32 b);
// decl: void msgWindow_Continue(s32 id);
// decl: void JUTFont_Free(void);
// decl: void JUTFontSetup(s32 mode);
// proto: USER_FUNC(unk_end_00000bc8);
USER_FUNC(unk_end_00000bc8) {
    s32 state = event->userdata[0];
    s32 idx = event->userdata[1];
    s32 i;
    s32 x;
    s32 y;
    s32 wx;
    s32 wy;
    s32 n;
    const char* msg;
    char buf2[0x400];
    char buf1[0x400];

    if (isFirstCall) {
        state = 0;
        idx = 0;
        for (i = 0; i < 3; i++) {
            dat_ptr_end_00003218->win1[i] = -1;
        }
        for (i = 0; i < 3; i++) {
            dat_ptr_end_00003218->win2[i] = -1;
        }
        evtSetValue(event, GW(10), 0);
        dat_ptr_end_00003218->evt = evtEntry(unk_evt_end_000042e0, 0, 0);
    }
    dat_ptr_end_00003218->pos = unk_end_0000321c[idx].pos;
    switch (dat_ptr_end_00003218->pos) {
        case 0:
            x = -274;
            y = -24;
            break;
        case 1:
            x = 274;
            y = 250;
            break;
        case 2:
            x = 274;
            y = -24;
            break;
        case 3:
            x = -274;
            y = 250;
            break;
        case 4:
            x = 0;
            y = -60;
            break;
    }
    switch (state) {
        case 0:
            for (i = 0; i < 3; i++) {
                if (unk_end_0000321c[idx].msg1[i] != NULL) {
                    msg = msgSearch(unk_end_0000321c[idx].msg1[i]);
                    wx = x;
                    wy = y - i * 22 - 4;
                    if (x == 0) {
                        wx = x - 0.8f * FontGetMessageWidth(msg) * 0.5f;
                    } else if (x > 0) {
                        wx = x - 0.8f * FontGetMessageWidth(msg);
                    }
                    sprintf(buf1, "<clear><dkey><wpos %d %d 400 200><col f0f0f0ff><speed 0><scale 0.8>%s</scale></speed></col><wait 500></dkey><once_stop>", wx - 62, wy, msg);
                    dat_ptr_end_00003218->win1[i] = msgWindow_Entry(buf1, 0, 0);
                }
            }
            for (i = 0; i < 3; i++) {
                if (unk_end_0000321c[idx].msg2[i] != NULL) {
                    msg = msgSearch(unk_end_0000321c[idx].msg2[i]);
                    wx = x;
                    wy = y - i * 24 - 50;
                    if (x == 0) {
                        wx = x - FontGetMessageWidth(msg) * 0.5f;
                    } else if (x > 0) {
                        wx = x - FontGetMessageWidth(msg);
                    }
                    sprintf(buf2, "<clear><dkey><wpos %d %d 400 200><col f0f0f0ff><speed 0>%s</speed></col><wait 5200></dkey><once_stop>", wx - 62, wy, msg);
                    dat_ptr_end_00003218->win2[i] = msgWindow_Entry(buf2, 0, 0);
                } else {
                    dat_ptr_end_00003218->win2[i] = -1;
                }
            }
            evtSetValue(event, GW(10), 1);
            evtSetValue(event, GW(11), unk_end_0000321c[idx].type);
            evtSetValue(event, GW(12), unk_end_0000321c[idx].pos);
            state++;
            break;
        case 1:
            for (i = 0; i < 3; i++) {
                if (dat_ptr_end_00003218->win1[i] != -1 && windowCheckID(dat_ptr_end_00003218->win1[i])) {
                    break;
                }
            }
            if (i < 3) {
                break;
            }
            for (i = 0; i < 3; i++) {
                if (dat_ptr_end_00003218->win2[i] != -1 && windowCheckID(dat_ptr_end_00003218->win2[i])) {
                    break;
                }
            }
            if (i < 3) {
                break;
            }
            state++;
            break;
        case 2:
            n = idx + 1;
            if (n < ARRAY_SIZE(unk_end_0000321c)) {
                for (i = 0; i < 3; i++) {
                    if (unk_end_0000321c[n].msg1[i] != NULL) {
                        break;
                    }
                }
            } else {
                i = 0;
            }
            if (i < 3) {
                for (i = 0; i < 3; i++) {
                    if (dat_ptr_end_00003218->win1[i] != -1) {
                        msgWindow_Continue(dat_ptr_end_00003218->win1[i]);
                    }
                }
            }
            for (i = 0; i < 3; i++) {
                if (dat_ptr_end_00003218->win2[i] != -1) {
                    msgWindow_Continue(dat_ptr_end_00003218->win2[i]);
                }
            }
            evtSetValue(event, GW(10), 2);
            if (n < ARRAY_SIZE(unk_end_0000321c)) {
                state++;
            } else {
                state += 2;
            }
            break;
        case 3:
            if (evtGetValue(event, GW(10)) == 0) {
                state = 0;
                idx++;
            }
            break;
        case 4:
            return 2;
    }
    event->userdata[0] = state;
    event->userdata[1] = idx;
    return 0;
}
