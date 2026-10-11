// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// include: eff/eff_syuryou.h
// decl: s32 irand(s32 scalar);
// decl: EffectEntry* effGlassN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);
// proto: static USER_FUNC(_check_satellite);
static USER_FUNC(_check_satellite) {
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    s32* args = event->args;
    BattleUnitPart* part;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    BOOL alive;
    s32 j;

    alive = FALSE;
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    for (i = 4; i < 8; i++) {
        if (unit->work[i] != -1) {
            if (BattleGetUnitPtr(_battleWorkPointer, unit->work[i]) != NULL) {
                alive = TRUE;
            } else {
                unit->work[i] = -1;
            }
        }
    }
    if (!alive) {
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        if (part->attributes & 0x20000000) {
            effDelete((EffectEntry*)unit->work[3]);
            unit->work[3] = 0;
            BtlUnit_snd_se(unit, "SFX_ENM_BARRI_BARRIER_BREAK1", 0xF1194D80, 0);
            BtlUnit_GetPos(unit, &x, &y, &z);
            for (j = 0; j < 20; j++) {
                s32 w = BtlUnit_GetWidth(unit) + 15;
                s32 h = BtlUnit_GetHeight(unit) + 15;
                s32 dx = irand(w) - w / 2;
                s32 dy = irand(h) - h / 2;

                effGlassN64Entry(2, 60, x + dx, y + dy, z, 1.0f);
            }
        }
        part->attributes &= ~0x20000000;
        evtSetValue(event, args[0], 0);
    } else {
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        if (!(part->attributes & 0x20000000)) {
            f32 px;
            f32 py;
            f32 pz;

            BtlUnit_snd_se(unit, "SFX_ENM_BARRI_BARRIER1", 0xF1194D80, 0);
            BtlUnit_GetPos(unit, &px, &py, &pz);
            unit->work[3] = (s32)effSyuryouEntry(1, 1000, 0.0f, -1000.0f, 0.0f);
        }
        part->attributes |= 0x20000000;
        evtSetValue(event, args[0], 1);
        if (unit->work[3] != 0) {
            f32* ud = ((EffectEntry*)unit->work[3])->userdata;

            BtlUnit_GetPos(unit, &x, &y, &z);
            ud[1] = x;
            ud[2] = y - 32.0f * unit->mSizeMultiplier;
            ud[3] = 10.0f + z;
            ud[4] = 1.8f * unit->mSizeMultiplier;
        }
    }
    return EVT_RETURN_DONE;
}
