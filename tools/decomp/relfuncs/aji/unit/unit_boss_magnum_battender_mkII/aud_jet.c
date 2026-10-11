// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: driver/effdrv.h
// include: dolphin/mtx.h
// decl: typedef struct BattenEffWork { s32 field_0x0; Vec pos; u8 field_0x10[0x28 - 0x10]; Mtx mtx; } BattenEffWork;
// decl: EffectEntry* effBattenEntry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);
// decl: s32 jetCount;
// decl: EffectEntry* eff_jet[2];
// proto: USER_FUNC(aud_jet);
USER_FUNC(aud_jet) {
    s32 id = BattleTransID(event, evtGetValue(event, event->args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    Mtx mtx;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    BattenEffWork* ew;

    BtlUnit_GetPos(unit, &x, &y, &z);
    if (isFirstCall) {
        for (i = 0; i < 2; i++) {
            eff_jet[i] = effBattenEntry(3, 1000, 0.0f, -1000.0f, 0.0f, 3.0f);
        }
        jetCount = 0;
    }
    PSMTXRotRad(mtx, 'z', -0.34906584f);
    ew = eff_jet[0]->userdata;
    ew->pos.x = x - 60.0f;
    ew->pos.y = 22.5f + y;
    ew->pos.z = z;
    PSMTXCopy(mtx, ((BattenEffWork*)eff_jet[0]->userdata)->mtx);
    ew = eff_jet[1]->userdata;
    ew->pos.x = x - 15.0f;
    ew->pos.y = 22.5f + y;
    ew->pos.z = 70.0f + z;
    PSMTXCopy(mtx, ((BattenEffWork*)eff_jet[1]->userdata)->mtx);
    if (jetCount == 1) {
        for (i = 0; i < 2; i++) {
            effDelete(eff_jet[i]);
        }
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
