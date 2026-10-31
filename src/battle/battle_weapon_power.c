// Weapon power calculation: how much damage each kind of attack deals from levels, HP and badges.
#include "battle/battle_weapon_power.h"
#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_unit.h"

s32 weaponGetPowerDefault(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    return weapon->hpDamageWork[0];
}

s32 weaponGetFPPowerDefault(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    return weapon->fpDamageWork[0];
}

s32 weaponGetPowerFromMarioJumpLv(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    s32 acSuccess;
    s32 slot;
    u32 power;

    acSuccess = (_battleWorkPointer->actionCommands.result >> 1) & 1;
    slot = acSuccess + 2 * (pouchGetPtr()->jumpLevel - 1);
    if (slot >= 6) {
        slot = 5;
    }
    power = weapon->hpDamageWork[slot];
    if (attacker->badgesEquipped.Jumpman) {
        power += attacker->badgesEquipped.Jumpman;
    }
    return power;
}

s32 weaponGetPowerFromMarioHammerLv(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    s32 acSuccess;
    s32 slot;
    u32 power;

    acSuccess = (_battleWorkPointer->actionCommands.result >> 1) & 1;
    slot = acSuccess + 2 * (pouchGetPtr()->hammerLevel - 1);
    if (slot >= 6) {
        slot = 5;
    }
    power = weapon->hpDamageWork[slot];
    if (attacker->badgesEquipped.Hammerman) {
        power += attacker->badgesEquipped.Hammerman;
    }
    return power;
}

s32 weaponGetPowerOverlapJump1(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    u32 jumpPower;
    u32 perBadge;

    jumpPower = weaponGetPowerFromMarioJumpLv(attacker, weapon, target, part);
    perBadge = weapon->hpDamageWork[7];
    return jumpPower + perBadge * pouchEquipCheckBadge(weapon->hpDamageWork[6]);
}

s32 weaponGetPowerOverlapHammer1(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    u32 hammerPower;
    u32 perBadge;

    hammerPower = weaponGetPowerFromMarioHammerLv(attacker, weapon, target, part);
    perBadge = weapon->hpDamageWork[7];
    return hammerPower + perBadge * pouchEquipCheckBadge(weapon->hpDamageWork[6]);
}

s32 weaponGetPowerFromPartyAttackLv(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    BattleWork* wp = _battleWorkPointer;
    PartyId partyId;
    s32 acSuccess;
    s32 slot;

    partyId = BattleTransPartyId(attacker->currentKind);
    acSuccess = (wp->actionCommands.result >> 1) & 1;
    slot = acSuccess + 2 * pouchGetPartyAttackLv(partyId);
    if (slot >= 6) {
        slot = 5;
    }
    return weapon->hpDamageWork[slot];
}

s32 weaponGetPowerFromGulliblePartyAttackLv(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target,
                                            BattleUnitPart* part) {
    PartyId partyId;
    s32 partyAttackLv;

    partyId = BattleTransPartyId(attacker->currentKind);
    partyAttackLv = pouchGetPartyAttackLv(partyId);
    if (partyAttackLv >= 6) {
        partyAttackLv = 5;
    }
    return weapon->hpDamageWork[partyAttackLv];
}

s32 weaponGetACOutputParam(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    s32 result;

    result = _battleWorkPointer->actionCommands.outputParams[weapon->hpDamageWork[0]] + weapon->hpDamageWork[1];
    if (result < 0) {
        result = 0;
    }
    return result;
}

s32 weaponGetPowerHPHalf(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    s32 hp = target->currentHp;

    if ((hp & 1) == 1) {
        return hp / 2 + 1;
    }
    return hp / 2;
}

s32 weaponGetPowerHPHalf2(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    return target->currentHp / 2;
}

s32 weaponGetFPPowerFPHalf(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    s32 fp = target->currentFp;

    if ((fp & 1) == 1) {
        return fp / 2 + 1;
    }
    return fp / 2;
}

s32 weaponGetPowerTatsumaki(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    u32 power;

    BattleGetMarioPtr(_battleWorkPointer);
    power = weapon->hpDamageWork[0];
    power += weapon->hpDamageWork[1] * pouchEquipCheckBadge(ITEM_TORNADO_JUMP);
    return power;
}
