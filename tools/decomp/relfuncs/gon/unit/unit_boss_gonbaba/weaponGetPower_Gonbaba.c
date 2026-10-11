// include: battle/battle_unit.h
// proto: s32 weaponGetPower_Gonbaba(BattleUnit* unit, s32* weapon);
s32 weaponGetPower_Gonbaba(BattleUnit* unit, s32* weapon) {
    s32 power = weapon[8];

    power -= unit->work[0];
    if (power <= 0) {
        power = 1;
    }
    return power;
}
