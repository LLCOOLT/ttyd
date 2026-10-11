// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// include: eff/eff_syuryou.h
// decl: s32 irand(s32 scalar);
// decl: EffectEntry* effGlassN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 scale);
// proto: USER_FUNC(check_satellite);
USER_FUNC(check_satellite) {
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part;
    BattleUnitPart* part2;
    EventEntry* evt;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 count;
    BOOL all;

    count = 0;
    all = FALSE;
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    for (i = 9; i < 13; i++) {
        if (unit->work[i] != -1) {
            if (BattleGetUnitPtr(_battleWorkPointer, unit->work[i]) != NULL) {
                count++;
            } else {
                unit->work[i] = -1;
            }
        }
    }
    if (count >= 4) {
        all = TRUE;
    }
    if (!all) {
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        part2 = BtlUnit_GetPartsPtr(unit, 2);
        if (part->attributes & 0x40000000) {
            evt = evtEntryType(hakai_snd_event, event->priority, 0, event->type);
            evt->unitId = event->unitId;
            evt->ownerNPC = event->ownerNPC;
            for (i = 0; i < 16; i++) {
                evt->lwData[i] = event->lwData[i];
            }
            for (i = 0; i < 3; i++) {
                evt->lfData[i] = event->lfData[i];
            }
            evt->uwBase = event->uwBase;
            evt->ufBase = event->ufBase;
            effDelete((EffectEntry*)unit->work[8]);
            unit->work[8] = 0;
            BtlUnit_GetPos(unit, &x, &y, &z);
            for (i = 0; i < 20; i++) {
                s32 w = BtlUnit_GetWidth(unit) + 15;
                s32 h = BtlUnit_GetHeight(unit) + 15;
                s32 dx = irand(w) - w / 2;
                s32 dy = irand(h) - h / 2;

                effGlassN64Entry(2, 60, x + dx, y + dy, z, 1.0f);
            }
        }
        part->attributes &= ~0x40000000;
        part2->attributes &= ~0x20000000;
        part->defenseAttr = &defence_attr;
        for (i = 0; i < 5; i++) {
            part->defense->defenses[i] = ((u8*)defencecopy)[i];
        }
        part->defense->defenses[0] += count;
    } else {
        part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
        part2 = BtlUnit_GetPartsPtr(unit, 2);
        if (!(part->attributes & 0x40000000)) {
            f32 px;
            f32 py;
            f32 pz;

            BtlUnit_snd_se(unit, "SFX_BOSS_SRYO_LIGHT_ROUND1", 0xF1194D80, 0);
            BtlUnit_GetPos(unit, &px, &py, &pz);
            unit->work[8] = (s32)effSyuryouEntry(1, 1000, 0.0f, -1000.0f, 0.0f);
        }
        if (unit->work[8] != 0) {
            f32* ud = ((EffectEntry*)unit->work[8])->userdata;
            f32 ex;
            f32 ey;
            f32 ez;

            BtlUnit_GetPos(unit, &ex, &ey, &ez);
            ud[1] = ex;
            ud[2] = ey - 12.5f * unit->mSizeMultiplier;
            ud[3] = 10.0f + ez;

            ud[4] = 2.5f * unit->mSizeMultiplier;
        }
        part->attributes |= 0x40000000;
        part2->attributes |= 0x20000000;
        part->defenseAttr = (BattleUnitDefenseAttr*)defence_attr_muteki;
        for (i = 0; i < 5; i++) {
            part->defense->defenses[i] = ((u8*)defencecopy)[i];
        }
        part->defense->defenses[0] += count;
    }
    return EVT_RETURN_DONE;
}
