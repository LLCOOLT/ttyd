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
// proto: USER_FUNC(chorogun_dive_target);
USER_FUNC(chorogun_dive_target) {
    ExtPose* pose;
    s32 frames;
    s32 n;
    s32 sel;
    s32* args;
    Chorogun* c;
    s32 list[1000];
    s32 i;
    f32 t;
    f32* row;
    f32 x, y, z;
    f32 dx, dy, dz;
    ExtPose* p;
    BattleUnit* unit;

    args = event->args;
    n = 0;
    frames = evtGetValue(event, args[0]);
    t = frames;
    pose = extGetPosePtr();
    for (i = 0; i < extGetPoseNum(); i++) {
        if (chorogun[i & 0xFFFFFFFFFFFFFFFFu].flags & 1) {
            list[n++] = i;
        }
    }
    sel = list[irand(n)];
    c = &chorogun[sel];
    c->state = 45;
    c->timer = frames;
    BtlUnit_GetPos(BattleGetUnitPtr(_battleWorkPointer, chorogun_targetId), &x, &y, &z);
    p = &pose[sel];
    row = p->mtx[2];
    dx = x - p->mtx[0][3];
    dy = y - row[3];
    dz = z - row[3];
    c->vel.x = dx / t;
    c->vel.y = (2.0f * dy - -0.5f * t * t) / (2.0f * t);
    c->vel.z = dz / t;
    evtSetValue(event, args[1], sel);
    unit = chorogun_get_ptr();
    BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_CHORO_ATTACK1", 0x80, 0, &(Vec){p->mtx[0][3], p->mtx[1][3], p->mtx[2][3]});
    return 2;
}
