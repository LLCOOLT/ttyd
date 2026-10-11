// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_stage_object.h
// include: system.h
// include: dolphin/mtx.h
// decl: typedef struct ZakoGun { s8 field_0x0; s8 state; s32 timer; s32 timerMax; Vec pos; Vec home; s32 poseBase; s32 poseNum; s32 poseDiv; s32 poseCount; Vec start; Vec target; Vec vel; Vec ofs; Vec rot; } ZakoGun;
// decl: typedef struct ZakoGunWork { s32 flag; s32 targetId; s32 state; s32 timer; Vec pos; u8 field_0x1c[0x34 - 0x1c]; f32 radius; f32 angle; f32 speed; u8 field_0x40[0x48 - 0x40]; Vec start; Vec end; s32 timer2; s32 steps; s32 count; s32 sfx; } ZakoGunWork;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: extern ZakoGun* zakogun;
// decl: extern ZakoGunWork* work_20_bss_6C;
// decl: ExtPose* extGetPosePtr(void);
// decl: BattleUnit* zakogun_get_ptr(void);
// decl: s32 zakogun_get_kanbu_id(void);
// decl: void zakogun_set_pose(ZakoGun* zako, s32 base, s32 num, s32 div);
// decl: void zakogun_ext_init123_common(ExtPose* pose, s32 i);
// decl: void psndSFXOff(s32 id);
// decl: int rand(void);
// decl: double sqrt(double x);
// proto: USER_FUNC(zakogun_ext_init3);
USER_FUNC(zakogun_ext_init3) {
    s32 i;
    ExtPose* pose = extGetPosePtr();
    BattleUnit* kanbu;
    s32 a;
    s32 b;
    f32 dx, dy, dz, dist;

    work_20_bss_6C->flag = 2;
    for (i = 0; i < 500; i++, pose++) {
        zakogun_ext_init123_common(pose, i);
        zakogun[i].home.x = -50.0f + 20.0f * (i % 12) + (5.0f * rand() / 32767.0f - 2.5f);
        zakogun[i].home.y = 0.0f;
        zakogun[i].home.z = -80.0f + 4.0f * (i / 12) + (5.0f * rand() / 32767.0f - 2.5f);
        kanbu = BattleGetUnitPtr(_battleWorkPointer, zakogun_get_kanbu_id());
        dx = zakogun[i].home.x - kanbu->mHomePosition.x;
        dy = zakogun[i].home.y - kanbu->mHomePosition.y;
        dz = zakogun[i].home.z - kanbu->mHomePosition.z;
        dist = sqrt(dx * dx + dy * dy + dz * dz);
        if (dist <= 30.0f) {
            zakogun[i].home.x += 30.0f * (dx / dist);
            zakogun[i].home.y += 30.0f * (dy / dist);
            zakogun[i].home.z += 30.0f * (dz / dist);
        }
    }
    for (i = 0; i < 250; i++) {
        Vec tmp;
        a = irand(500);
        b = irand(500);
        tmp = zakogun[a].home;
        zakogun[a].home = zakogun[b].home;
        zakogun[b].home = tmp;
    }
    return EVT_RETURN_DONE;
}
