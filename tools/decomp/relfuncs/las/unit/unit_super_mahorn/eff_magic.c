// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// decl: EffectEntry* effMahorn2Entry(s32 type, f32 x, f32 y, f32 z, f32 a, f32 b, f32 c, f32 scale, f32 speed);
// decl: double __fabs(double x);
// decl: static inline double mahorn_fabs(double x) { return __fabs(x); }
// proto: static USER_FUNC(eff_magic);
static USER_FUNC(eff_magic) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 a = evtGetFloat(event, args[1]);
    f32 b = evtGetFloat(event, args[2]);
    f32 c = evtGetFloat(event, args[3]);
    s32 time = evtGetValue(event, args[4]);
    f32 x;
    f32 y;
    f32 z;

    BtlUnit_GetPos(unit, &x, &y, &z);
    x += unit->mSizeMultiplier * unit->faceDirection;
    y += 18.0f * unit->mSizeMultiplier;
    z += 5.0f;
    unit->work[7] = (s32)effMahorn2Entry(0, x, y, z, a, y, z, unit->mSizeMultiplier, mahorn_fabs((a - x) / time));
    return EVT_RETURN_DONE;
}
