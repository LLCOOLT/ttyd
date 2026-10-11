// include: battle/battle.h
// proto: void hammer_bros_get_next_target(s32* unitIdx, s32* partIdx);
void hammer_bros_get_next_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;

    wt->currentTarget++;
    if (wt->currentTarget < wt->numTargets) {
        BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];
        *unitIdx = target->unitIdx;
        *partIdx = target->partIdx;
    } else {
        *unitIdx = -1;
        *partIdx = 0;
    }
}
