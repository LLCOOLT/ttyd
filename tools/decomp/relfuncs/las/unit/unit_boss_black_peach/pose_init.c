// include: battle/battle.h
// include: battle/battle_sub.h
// include: battle/battle_unit.h
// include: battle/battle_audience.h
// include: driver/animdrv.h
// include: driver/dispdrv.h
// include: driver/effdrv.h
// include: driver/npcdrv.h
// include: mario/mariost.h
// include: memory.h
// include: string.h
// include: system.h
// include: dolphin/mtx.h
// include: dolphin/os.h
// include: manager/evtmgr_cmd.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct HandElem { u16 flip; u8 field_0x2[2]; s32 animIdx; OSTime time; s16 ofs; s16 phase; f32 speed; Vec pos; s32 field_0x24; } HandElem;
// decl: typedef struct HandAnim { char name[16]; char anim[8]; f32 rate; s32 start; s32 count; } HandAnim;
// decl: typedef struct HandWork { HandElem* elems; s32 num; HandAnim anim[32]; u8 field_0x488[0x49C - 0x488]; f32 y; u8 field_0x4a0[4]; s32 animNum; s32 timer; s32 state; } HandWork;
// decl: typedef struct HandData { const char* name; const char* anim; f32 rate; } HandData;
// decl: typedef struct QueenConnect { s32 poseId[3]; u8 field_0xc[0x40 - 0xC]; s32 idx[2]; } QueenConnect;
// decl: HandData hand_data[32];
// decl: HandWork* hand_wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: void extLoadRenderMode(void);
// decl: void extLoadVertex(void);
// decl: void extLoadTexture(void);
// decl: void extLoadTev(void);
// decl: void extDraw(void);
// decl: void extLoadTextureExit(void);
// decl: s32 psndSFXOn_3D(const char* name, Vec* position);
// decl: void BattleAudienceAddTargetNum(f32 a, f32 b);
// decl: s32* BattleBreakSlotGetPtr(void);
// decl: u8* lightGetPaperCraft(void);
// decl: EffectEntry* effShockN64Entry(s32 type, f32 x, f32 y, f32 z, f32 a, f32 b);
// decl: EffectEntry* effPokopiThunderN64Entry(s32 type, s32 lifetime, f32 x, f32 y, f32 z, f32 tx, f32 ty, f32 tz, f32 scale);
// decl: EffectEntry* effStardust2N64Entry(s32 type, s32 arg1, s32 arg2, f32 x, f32 y, f32 z, f32 arg6, f32 arg7);
// decl: void btl_camera_shake_w(s32 a, s32 b, s32 c, f32 d, f32 e);
// decl: void BtlUnit_SetAnim(BattleUnitPart* part, const char* anim);
// decl: double cos(double);
// proto: static void pose_init(void);
static void pose_init(void) {
    char name[32];
    char anim[32];
    HandData* d = hand_data;
    s32 i = 0;
    s32 start;

    // hand_light_init is an inline helper defined by hand before EVT_BEGIN(shadow_queen_1000) in the
    // rels/ source: its (Vec){-200, 100, 500} template must sit there in .rodata
    hand_light_init();
    strcpy(name, "");
    strcpy(anim, "");
    hand_wp->animNum = -1;
    do {
        if (strcmp(d->name, name) != 0) {
            strcpy(name, d->name);
            strcpy(anim, "");
        }
        if (strcmp(d->anim, anim) != 0) {
            strcpy(anim, d->anim);
            start = i;
            hand_wp->animNum++;
        }
        strcpy(hand_wp->anim[hand_wp->animNum].name, name);
        strcpy(hand_wp->anim[hand_wp->animNum].anim, anim);
        hand_wp->anim[hand_wp->animNum].start = start;
        hand_wp->anim[hand_wp->animNum].count = i - start + 1;
        hand_wp->anim[hand_wp->animNum].rate = d->rate;
        i++;
        d++;
    } while (d->name != NULL);
    hand_wp->animNum++;
}
