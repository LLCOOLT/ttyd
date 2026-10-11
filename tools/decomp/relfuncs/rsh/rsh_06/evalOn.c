// include: manager/evtmgr.h
// include: driver/mapdrv.h
// include: string.h
// include: memory.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: mario/mariost.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 field_0x28; f32 field_0x2c; Vec field_0x30; s16 pose; u8 field_0x3e[2]; OSTime startTime; s16 group; s16 order; u8 kind; u8 field_0x4d[3]; } Moamoa;
// decl: typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; MapObject* mobj; f32 mobjY; Vec target[3]; s16 field_0x38; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 field_0x42; void* escapeEvt; s32 animPoseId; s32 numDefs; MoamoaPoseDef defs[32]; f32 angle; f32 dist; s32 field_0x558; f32 breathDir; f32 breathDist; Vec breathPos; s16 chainNum[128]; s16 chainIdx[128][2]; } MoamoaWork;
// decl: typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
// decl: static MoamoaWork* wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: void extReset(void);
// decl: int rand(void);
// decl: static f32 randf(f32 min, f32 max);
// decl: static void moamoa_pose_init(void);
// decl: static void moamoa_pose_main(void);
// decl: static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
// include: driver/npcdrv.h
// include: driver/animdrv.h
// decl: extern const char* g_moamoa_chain_tbl[][2];
// decl: extern const s32 dat_80419a28;
// proto: void evalOn(void);
void evalOn(void) {
    NpcEntry* npc = npcNameToPtr("base");
    AnimationPose* anim;
    Moamoa* moa;
    s32 i;
    s32 j;
    Vec* pos;
    s32 n;

    animPoseWorldPositionEvalOn(npc->poseId);
    wp->animPoseId = npc->poseId;
    anim = animPoseGetAnimPosePtr(npc->poseId);
    pos = anim->worldPositions[0];
    n = anim->numWorldPositions;
    for (i = 0; i < n; i++) {
        pos[i] = (Vec){0.0f, -1000.0f, 0.0f};
    }
    for (i = 0; i < dat_80419a28; i++) {
        wp->chainIdx[i][0] = animPoseGetGroupIdx(npc->poseId, g_moamoa_chain_tbl[i][0]);
        wp->chainIdx[i][1] = animPoseGetGroupIdx(npc->poseId, g_moamoa_chain_tbl[i][1]);
    }
    moa = wp->moa;
    for (j = 0; j < wp->count; j++, moa++) {
        moa->group = j % dat_80419a28;
        moa->order = wp->chainNum[moa->group]++;
    }
    moa = wp->moa;
    for (j = 0; j < wp->count; j++, moa++) {
        if (moa->group == 0 || moa->group == 5 || moa->group == 10 || moa->group == 15 || moa->group == 30 ||
            moa->group == 34 || moa->group == 38 || moa->group == 42 || moa->group == 46) {
            moa->kind = 1;
        }
        if (moa->order == 0) {
            if (moa->group == 3) {
                moa->kind = 2;
            }
            if (moa->group == 4) {
                moa->kind = 3;
            }
            if (moa->group == 7) {
                moa->kind = 4;
            }
            if (moa->group == 8) {
                moa->kind = 5;
            }
            if (moa->group == 9) {
                moa->kind = 6;
            }
            if (moa->group == 12) {
                moa->kind = 7;
            }
            if (moa->group == 13) {
                moa->kind = 8;
            }
            if (moa->group == 14) {
                moa->kind = 9;
            }
        }
    }
}
