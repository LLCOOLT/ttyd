// include: battle/battle.h
// include: battle/battle_unit.h
// include: dolphin/mtx.h
// include: system.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Chorogun { u8 flags; u8 state; u8 pad_2[2]; Vec vel; f32 speed; Vec pos; s32 timer; Vec target; } Chorogun;
// decl: Chorogun* chorogun;
// decl: s32 chorogun_targetId;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: int rand(void);
// proto: void chorogun_ext_init(void);
void chorogun_ext_init(void) {
    s32 i;
    s32 a, b;
    f32 tx, ty, tz;
    ExtPose* pose = extGetPosePtr();

    chorogun = BattleAlloc(sizeof(Chorogun) * 1000);
    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        pose->flags = 1;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = 0.0f;
        pose->mtx[1][3] = -1000.0f;
        pose->mtx[2][3] = 0.0f;
        pose->rot = 90.0f;
        chorogun[i].flags = 0;
        chorogun[i].state = 0;
        chorogun[i].vel = (Vec){0.0f, 0.0f, 0.0f};
        if (i == 0) {
            chorogun[i].timer = 22;
        } else {
            chorogun[i].timer = irand(45);
        }
        chorogun[i].pos.x = -50.0f + 5.0f * (i % 50) + (10.0f * rand() / 32767.0f - 5.0f);
        chorogun[i].pos.y = 0.0f;
        chorogun[i].pos.z = -70.0f + 7.0f * (i / 50) + (5.0f * rand() / 32767.0f - 2.5f);
    }
    for (i = 0; i < 500; i++) {
        a = irand(extGetPoseNum());
        b = irand(extGetPoseNum());
        tx = chorogun[a].pos.x;
        ty = chorogun[a].pos.y;
        tz = chorogun[a].pos.z;
        chorogun[a].pos.x = chorogun[b].pos.x;
        chorogun[a].pos.y = chorogun[b].pos.y;
        chorogun[a].pos.z = chorogun[b].pos.z;
        chorogun[b].pos.x = tx;
        chorogun[b].pos.y = ty;
        chorogun[b].pos.z = tz;
    }
}
