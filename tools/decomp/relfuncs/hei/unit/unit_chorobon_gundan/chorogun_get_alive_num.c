// include: battle/battle.h
// include: battle/battle_unit.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Chorogun { u8 flags; u8 state; u8 pad_2[2]; Vec vel; f32 speed; Vec pos; s32 timer; Vec target; } Chorogun;
// decl: Chorogun* chorogun;
// decl: s32 chorogun_targetId;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: s32 BtlUnit_snd_se_pos(BattleUnit* unit, const char* name, s32 vol, s32 pan, Vec* pos);
// decl: int rand(void);
// decl: double sqrt(double x);
// proto: USER_FUNC(chorogun_get_alive_num);
USER_FUNC(chorogun_get_alive_num) {
    s32* args = event->args;
    s32 i;
    s32 n = 0;

    for (i = 0; i < extGetPoseNum(); i++) {
        if (chorogun[i].flags & 1) {
            n++;
        }
    }
    evtSetValue(event, args[0], n);
    return 2;
}
