// include: battle/battle.h
// proto: void piders_get_target(s32* unitIdx, s32* partIdx);
#pragma dont_inline on
void piders_get_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;
    BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];

    *unitIdx = target->unitIdx;
    *partIdx = target->partIdx;
}
#pragma dont_inline reset
