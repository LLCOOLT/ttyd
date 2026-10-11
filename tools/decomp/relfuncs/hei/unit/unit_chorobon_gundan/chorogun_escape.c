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
// proto: USER_FUNC(chorogun_escape);
USER_FUNC(chorogun_escape) {
    f32 dist[1000];
    s32 idx[1000];
    BattleUnit* unit = chorogun_get_ptr();
    s32 i, j, m;
    s32 n = 0;
    Chorogun* c;
    ExtPose* pose = extGetPosePtr();
    f32 dx, dz, d, tf;
    s32 ti;

    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        if (chorogun[i].flags & 1) {
            dx = unit->mHomePosition.x - pose->mtx[0][3];
            dz = unit->mHomePosition.z - pose->mtx[2][3];
            d = dx * dx + dz * dz;
            if (n >= 50) {
                if (d <= 2500.0f) {
                    dist[n] = d;
                    idx[n] = i;
                    n++;
                }
            } else {
                dist[n] = d;
                idx[n] = i;
                n++;
            }
        }
    }
    for (i = 0; i < n - 1; i++) {
        for (j = 1; j < n; j++) {
            if (dist[i] > dist[j]) {
                tf = dist[i];
                ti = idx[i];
                dist[i] = dist[j];
                idx[i] = idx[j];
                dist[j] = tf;
                idx[j] = ti;
            }
        }
    }
    m = n >= 50 ? 50 : n;
    for (i = 0; i < m; i++) {
        c = &chorogun[idx[i]];
        c->flags &= ~1;
        c->state = 60;
    }
    return 2;
}
