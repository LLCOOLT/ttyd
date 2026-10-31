// Declares the weapon power calculation functions.
#pragma once

#include <dolphin/types.h>
#include "battle/battle_unit.h"
#include "battle/battle_database_common.h"

s32 weaponGetACOutputParam(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetFPPowerDefault(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetFPPowerFPHalf(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetPowerDefault(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetPowerFromGulliblePartyAttackLv(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetPowerFromMarioHammerLv(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetPowerFromMarioJumpLv(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetPowerFromPartyAttackLv(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetPowerHPHalf(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetPowerHPHalf2(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetPowerOverlapHammer1(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetPowerOverlapJump1(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
s32 weaponGetPowerTatsumaki(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part);
