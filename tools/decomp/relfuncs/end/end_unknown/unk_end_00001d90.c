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
// proto: USER_FUNC(unk_end_00001d90);
USER_FUNC(unk_end_00001d90) {
    s32 id = evtGetValue(event, event->args[0]);
    BOOL inBattle;
    CreditActor* actor;
    f32 x;
    f32 y;
    f32 r;
    Mtx m3;
    Mtx m2;
    Mtx m1;
    Vec v;
    u32 type;

    inBattle = gp->inBattle != 0;
    if (R_credits_npc_info[id].evt != NULL) {
        evtEntry(R_credits_npc_info[id].evt, 0, 0);
        if (id + 5 < ARRAY_SIZE(R_credits_npc_info)) {
            animGroupBaseAsync(R_credits_npc_info[id + 5].agb, inBattle, NULL);
        }
        return 2;
    }
    if (isFirstCall) {
        actor = _mapAlloc(sizeof(CreditActor));
        memset(actor, 0, sizeof(CreditActor));
        actor->state = 0;
        actor->pos = dat_ptr_end_00003218->pos;
        switch (actor->pos) {
            case 0:
                actor->angle = -20.0f;
                actor->limit = 90.0f + actor->angle + 30.0f;
                break;
            case 1:
            case 4:
                actor->angle = 160.0f;
                actor->limit = 90.0f + actor->angle + 30.0f;
                break;
            case 2:
                actor->angle = 250.0f;
                actor->limit = 90.0f + actor->angle + 30.0f;
                break;
            default:
                actor->angle = 70.0f;
                actor->limit = 90.0f + actor->angle + 30.0f;
                break;
        }
        if (id + 5 < ARRAY_SIZE(R_credits_npc_info)) {
            animGroupBaseAsync(R_credits_npc_info[id + 5].agb, inBattle, NULL);
        }
        event->userdatap[0] = actor;
    }
    actor = event->userdatap[0];
    switch (actor->pos) {
        case 0:
            x = 304.0f;
            y = -240.0f;
            r = 100.0f;
            break;
        case 1:
        case 4:
            x = -304.0f;
            y = 240.0f;
            r = 100.0f;
            break;
        case 2:
            x = -304.0f;
            y = -240.0f;
            r = 100.0f;
            break;
        default:
            x = 304.0f;
            y = 240.0f;
            r = 100.0f;
            break;
    }
    if (!animGroupBaseAsync(R_credits_npc_info[id].agb, inBattle, NULL)) {
        return 0;
    }
    switch (actor->state) {
        case 0:
            EXIGetType(0, 2, &type);
            if (type != 0x05070000) {
                actor->poseId = animPoseEntry(R_credits_npc_info[id].agb, inBattle);
                animPoseSetAnim(actor->poseId, R_credits_npc_info[id].anim, 1);
            } else {
                actor->poseId = animPoseEntry("a_mario", inBattle);
                animPoseSetAnim(actor->poseId, "M_W_1", 1);
            }
            actor->state++;
            break;
        case 1:
            actor->angle += 0.15f;
            if (actor->angle > actor->limit) {
                animPoseRelease(actor->poseId);
                _mapFree(actor);
                return 2;
            }
            break;
    }
    PSMTXTrans(m1, 0.0f, r, 0.0f);
    PSMTXRotRad(m2, 'z', 0.017453292f * actor->angle);
    PSMTXConcat(m2, m1, m1);
    PSMTXTrans(m2, x * 0.5f, y * 0.5f, 0.0f);
    PSMTXConcat(m2, m1, actor->mtx);
    PSMTXScale(m3, 1.0f, 1.0f, 0.01f);
    PSMTXConcat(actor->mtx, m3, actor->mtx);
    if (animPoseGetVivianType(actor->poseId)) {
        v = (Vec){0.0f, 0.0f, 0.0f};
        v.x = actor->mtx[0][3];
        v.y = actor->mtx[1][3];
        v.z = actor->mtx[2][3];
        animPoseVivianMain(actor->poseId, &v);
    }
    if (strcmp((const char*)animPoseGetCurrentAnim(actor->poseId), "GAZ_A_1") == 0 && animPoseGetLoopTimes(actor->poseId) > 0.9f) {
        animPoseSetAnim(actor->poseId, "GAZ_A_1", 1);
    }
    animPoseMain(actor->poseId);
    dispEntry(CAMERA_3D, 0.0f, 1, unk_end_000023ac, actor);
    return 0;
}
