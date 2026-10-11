// include: battle/battle.h
// proto: static void barriern_wawawa_get_target(s32* unitIdx, s32* partIdx);
static void barriern_wawawa_get_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;
    BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];

    *unitIdx = target->unitIdx;
    *partIdx = target->partIdx;
}
