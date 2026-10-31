// Battle damage: computes damage, defense, status effects, counterattacks and the resulting hit events.
#include "eff/eff_nice.h"
#include "eff/n64/eff_vapor_n64.h"
#include "version.h"
#include "battle/battle_audience.h"
// this unit is size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
// inlining off for BattleDamageDirect, BattleCheckPikkyoro, BattleCalculateDamage and 14 more, as in the original (the object differs without it)
#pragma dont_inline on
#include "battle/battle_damage.h"
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_unit_event.h"
#include "battle/battle_database_common.h"
#include "eff/eff_hit.h"
#include "eff/eff_miss_star.h"
#include "eff/n64/eff_kemuri12_n64.h"
#include <string.h>
#include "battle/battle_mario.h"
#include "battle/battle_ac_help.h"
#include "battle/battle_disp.h"
#include "eff/eff_bomb.h"
#include "eff/eff_damage_star.h"
#include "eff/eff_recovery.h"
#include "eff/n64/eff_ice_n64.h"
#include "system.h"
#include "pmario_sound.h"
#include "eff/eff_fukidashi.h"
#include "battle/battle_status_effect.h"
// FAKE: battle_damage.c calls BtlUnit_GetStatus through this prototype (the types it was compiled with) instead of the one in battle/battle_unit.h; same registers, behaviour-identical.
typedef void (*BtlUnit_GetStatusS8Fn)(BattleUnit*, s8, s8*, s8*);
// FAKE: battle_damage.c calls BtlUnit_SetStatus through this prototype (the types it was compiled with) instead of the one in battle/battle_unit.h; same registers, behaviour-identical.
typedef BOOL (*BtlUnit_SetStatusS8Fn)(BattleUnit*, s8, s8, s8);

static void _getSickStatusParam(BattleUnit* unit, BattleWeapon* weapon, u32 type, s8* outTime, s8* outStrength);
static s32 BattleSetStatusDamage(u32* result, BattleUnit* unit, BattleUnitPart* part, u32 special, s32 type, s32 rate, s32 levelDiff, s8 time, s8 strength);
static u32 BattleCheckPikkyoro(BattleWeapon* weapon, u32* flags);
static s32 BattleCalculateDamage(BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, u32* result, u32 flags);
static s32 BattleCalculateFpDamage(BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, u32* resultFlags, u32 flags);
static s32 _checkDamageCode_EmergencyRevival(BattleUnit* unit, u32* flags);
static void __declare(s32 unitIdx, s32 partIdx, s32* outUnit, s32* outPart);

void BtlActRec_AddCount(u8* count);
// FAKE: local prototype: BtlActRec_AddPoint takes the points as u8 (battle_actrecord.h: s32); this file was compiled with it and the header prototype changes the code.
void BtlActRec_AddPoint(u8* rec, u8 points);

void BattleDamageDirect(s32 unitId, BattleUnit* target, BattleUnitPart* part, s32 damage, s32 fpDamage, u32 result, u32 pattern, s32 flag) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* attacker;
    Vec pos;

    if (unitId != -5) {
        attacker = BattleGetUnitPtr(wp, unitId);
    } else {
        attacker = NULL;
    }
    if (damage > 99) {
        damage = 99;
    } else if (damage < -99) {
        damage = -99;
    }
    if (attacker) {
        attacker->totalDamageDealt += damage;
    }
    if (part) {
        target->currentTarget = part;
    } else {
        part = target->currentTarget = BtlUnit_GetPartsPtr(target, BtlUnit_GetBodyPartsId(target));
    }
    target->damagePattern = pattern;
    if (target->attributeFlags & UNIT_ATTR_NO_KNOCKBACK_POSE) {
        if ((u32)target->damagePattern == 0x15 || (u32)target->damagePattern == 0x16 ||
            (u32)target->damagePattern == 0x17 || (u32)target->damagePattern == 0x18) {
            target->damagePattern = 0;
        }
    }
    BtlUnit_GetHitPos(target, part, &pos.x, &pos.y, &pos.z);

    if (!(result & DAMAGE_FLAG_HEAL)) {
        if (damage != 0 || fpDamage != 0) {
            f32 x, y, z;
            BtlUnit_GetHitPos(target, part, &x, &y, &z);
            switch ((u8)result) {
                case DAMAGE_HIT_FIRE:
                case DAMAGE_HIT_EXPLOSION:
                    effKemuri12N64Entry(0, 0x1e, x, y, z, 1.0f);
                    effHitEntry(1, 3, x, y, z, 1.0f);
                    break;
                case DAMAGE_HIT_ELECTRIC:
                    effHitEntry(2, 3, x, y, z, 1.0f);
                    break;
                case DAMAGE_HIT_ICE:
                    effIceN64Entry(0, x, y, z);
                    effHitEntry(3, 3, x, y, z, 1.0f);
                    break;
                default:
                    effHitEntry(0, 3, x, y, z, 1.0f);
                    break;
            }
            if (BtlUnit_GetBelong(target) == 0) {
                if (damage != 0 && !(target->attributeFlags & UNIT_ATTR_NO_DAMAGE_NUMBER)) {
                    effDamageStarEntry(0, damage, x - 8.0f, 5.0f + y, z, 10.0f, 30.0f);
                }
                if (fpDamage != 0) {
                    if (damage != 0) {
                        effDamageStarEntry(1, fpDamage, x - 8.0f, 5.0f + y, z, 10.0f, 60.0f);
                    } else {
                        effDamageStarEntry(1, fpDamage, x - 8.0f, 5.0f + y, z, 10.0f, 30.0f);
                    }
                }
            } else {
                if (damage != 0 && !(target->attributeFlags & UNIT_ATTR_NO_DAMAGE_NUMBER)) {
                    effDamageStarEntry(0, damage, x, 10.0f + y, z, 10.0f, -30.0f);
                }
                if (fpDamage != 0) {
                    if (damage != 0) {
                        effDamageStarEntry(1, fpDamage, x, 10.0f + y, z, 10.0f, -60.0f);
                    } else {
                        effDamageStarEntry(1, fpDamage, x, 10.0f + y, z, 10.0f, -30.0f);
                    }
                }
            }
            if (unitId != -5 && attacker && attacker->badgesEquipped.MegaRush &&
                attacker->currentHp <= attacker->kindParams->perilHP) {
                f32 x2, y2, z2;
                BtlUnit_GetHitPos(target, part, &x2, &y2, &z2);
                effFukidashiEntry(0, 0, 0, x2, y2, z2, 10.0f, 0.0f, 0x3c);
            }
        } else {
            f32 x, y, z;
            BtlUnit_GetHitPos(target, part, &x, &y, &z);
            if (pattern != 2 && pattern != 3 && pattern != 0x15 && pattern != 0x16 && pattern != 0x14 &&
                pattern != 0x13 && pattern != 0x1b && pattern != 7 && (u8)result != DAMAGE_HIT_STATUS_ONLY) {
                s32 dir = BtlUnit_GetBelong(target) == 0 ? -1 : 1;
                if (result & DAMAGE_FLAG_AC_SUCCESS) {
                    effMissStarEntry(1, 1, x, y, z, dir);
                } else {
                    effMissStarEntry(0, 1, x, y, z, dir);
                }
            }
        }
    } else {
        f32 x, y, z;
        BtlUnit_GetHitPos(target, part, &x, &y, &z);
        effRecoveryEntry(0, __fabs(damage), x, y, z);
    }

    if (!(result & DAMAGE_FLAG_HEAL) && damage > 0) {
#if VERSION <= VERSION_DEMO_US
        s32 i = target->badgesEquipped.PityFlower;
        for (; i > 0; i--) {
            irand(100);
        }
#else
        s32 n = 0;
        s32 i = target->badgesEquipped.PityFlower;
        for (; i > 0; i--) {
            if (irand(100) < 30) {
                n++;
            }
        }
        if (n > 0) {
            f32 x, y, z;
            BtlUnit_RecoverFp(target, n);
            BtlUnit_GetPos(target, &x, &y, &z);
            y += target->sizeMultiplier * BtlUnit_GetHeight(target) + 5.0f;
            effRecoveryEntry(1, n, x, y, z);
        }
#endif
    }

    if (pattern != 0x13 && pattern != 0x1b) {
        if (result & DAMAGE_FLAG_ATTACK_FX_R) {
            psndSFXOn_3D("SFX_MARIO_HAMMER_PIKKYO_R1", &pos);
#if VERSION <= VERSION_DEMO_US
        } else if (result & DAMAGE_FLAG_ATTACK_FX_Y) {
            psndSFXOn_3D("SFX_MARIO_HAMMER_PIKKYO_B1", &pos);
        } else if (result & DAMAGE_FLAG_ATTACK_FX_B) {
            psndSFXOn_3D("SFX_MARIO_HAMMER_PIKKYO_G1", &pos);
        } else if (result & DAMAGE_FLAG_ATTACK_FX_G) {
            psndSFXOn_3D("SFX_MARIO_HAMMER_PIKKYO_Y1", &pos);
#else
        } else if (result & DAMAGE_FLAG_ATTACK_FX_Y) {
            psndSFXOn_3D("SFX_MARIO_HAMMER_PIKKYO_Y1", &pos);
        } else if (result & DAMAGE_FLAG_ATTACK_FX_B) {
            psndSFXOn_3D("SFX_MARIO_HAMMER_PIKKYO_B1", &pos);
        } else if (result & DAMAGE_FLAG_ATTACK_FX_G) {
            psndSFXOn_3D("SFX_MARIO_HAMMER_PIKKYO_G1", &pos);
#endif
        } else if (result & DAMAGE_FLAG_ATTACK_FX_P) {
            psndSFXOn_3D("SFX_MARIO_HAMMER_PIKKYO_P1", &pos);
        } else if (BtlUnit_GetBelong(target) == 0 && (result & DAMAGE_FLAG_GUARDED)) {
            psndSFXOn_3D("SFX_MARIO_GUARD1", &pos);
        } else {
            if (damage > 0) {
                switch ((u8)result) {
                    case DAMAGE_HIT_FIRE:
                        psndSFXOn_3D(target->kindParams->fireDamageSfxName, &pos);
                        psndSFXOn_3D(target->kindParams->damageSfxName, &pos);
                        break;
                    case DAMAGE_HIT_ICE:
                        psndSFXOn_3D(target->kindParams->iceDamageSfxName, &pos);
                        psndSFXOn_3D(target->kindParams->damageSfxName, &pos);
                        break;
                    case DAMAGE_HIT_ELECTRIC:
                        psndSFXOn_3D(target->kindParams->explosionDamageSfxName, &pos);
                        psndSFXOn_3D(target->kindParams->damageSfxName, &pos);
                        break;
                    default:
                        psndSFXOn_3D(target->kindParams->damageSfxName, &pos);
                        break;
                }
            }
            if (fpDamage > 0 && BtlUnit_GetBelong(target) == 0) {
                psndSFXOn_3D("SFX_MARIO_DAMAGE_FP1", &pos);
            }
        }
    }

    target->hpDamageTaken = damage;
    target->totalHpDamageTaken += target->hpDamageTaken;
    target->fpDamageTaken = fpDamage;
    target->fpLost = fpDamage;
    target->totalFpDamageTaken += target->fpDamageTaken;
    if (!(target->attributeFlags & UNIT_ATTR_HP_LOCKED) && !(part->attributes & PART_ATTR_NO_HP_LOSS)) {
        target->hpGauge.prevHp = target->currentHp;
        target->currentHp -= target->hpDamageTaken;
        if (target->currentHp > target->maxHp) {
            target->currentHp = target->maxHp;
        }
        if (target->currentHp < 0) {
            target->currentHp = 0;
        }
        target->hpGauge.targetHp = target->currentHp;
        if (target->hpDamageTaken) {
            target->hpGauge.drainTimer = target->hpGauge.drainLength;
            target->hpGauge.visibleTimer = target->hpGauge.visibleLength;
        }
        if (result & DAMAGE_FLAG_LAST_HIT) {
            target->hpGauge.flags |= HP_GAUGE_FADE_OUT;
        } else {
            target->hpGauge.flags &= ~HP_GAUGE_FADE_OUT;
        }
    }
    if (target->fpDamageTaken) {
        s32 fp = BtlUnit_GetFp(target);
        s32 newFp;
        if (fp < fpDamage) {
            target->fpLost = fp;
        } else {
            target->fpLost = fpDamage;
        }
        newFp = fp - fpDamage;
        if (newFp < 0) {
            newFp = 0;
        }
        BtlUnit_SetFp(target, newFp);
        target->totalFpLost += target->fpLost;
    }
    if (damage > 0) {
        if (target->currentKind == UNIT_MARIO) {
            BtlActRec_AddCount(&wp->actRecord.marioHitsTaken);
            BtlActRec_AddPoint(&wp->actRecord.marioDamageTaken, damage);
        } else if (target->currentKind >= TYPE_PARTNER_MIN && target->currentKind < TYPE_PARTNER_MAX) {
            BtlActRec_AddCount(&wp->actRecord.partnerHitsTaken);
            BtlActRec_AddPoint(&wp->actRecord.partnerDamageTaken, damage);
        }
    }
    if (flag && (damage > 0 || fpDamage > 0) && BtlUnit_CheckStatus(target, STATUS_SLEEP) && irand(100) < 50) {
        f32 x, y, z;
        target->sleepTurns = 1;
        target->sleepStrength = 100;
        BtlUnit_CheckRecoveryStatus(target, STATUS_SLEEP);
        BtlUnit_GetPos(target, &x, &y, &z);
        y += BtlUnit_GetHeight(target) / 2;
        effFukidashiEntry(0, 0, 0, x, y, z, 10.0f, 0.0f, 0x3c);
    }
    if (target->currentKind == UNIT_MARIO) {
        BattleAudience_Case_MarioBigDamage(target->hpDamageTaken);
    }
    if (target->currentHp <= 0) {
        target->currentHp = 0;
        if (result & DAMAGE_FLAG_LAST_HIT) {
            result |= DAMAGE_FLAG_KO;
            if (target->attributeFlags & UNIT_ATTR_REVIVES_AFTER_KO) {
                switch ((u8)result) {
                    case DAMAGE_HIT_FIRE:
                    case DAMAGE_HIT_EXPLOSION:
                    case DAMAGE_HIT_COUNTER_FIERY:
                    case DAMAGE_HIT_COUNTER_EXPLOSIVE:
                    case DAMAGE_HIT_COUNTER_VOLATILE_EXPLOSIVE:
                    case DAMAGE_HIT_COUNTER_HOLD_FAST:
                        result |= DAMAGE_FLAG_DEFEATED;
                        break;
                }
            } else {
                result |= DAMAGE_FLAG_DEFEATED;
                _checkDamageCode_EmergencyRevival(target, &result);
            }
            if ((u32)target->damagePattern == 0x19) {
                s32 b = 1;
                if ((result & DAMAGE_FLAG_DEFEATED) && !(result & DAMAGE_FLAG_LIFE_SHROOM) && (result & DAMAGE_FLAG_LAST_HIT) && target->vulnStatus->galeForceRate) {
                    b = 0;
                }
                if (b) {
                    target->damagePattern = 0;
                }
            }
            if (result & DAMAGE_FLAG_DEFEATED) {
                if (target->currentKind >= TYPE_PARTNER_MIN && target->currentKind < TYPE_PARTNER_MAX) {
                    BattleAudience_Case_PartyDown();
                }
                if (target->currentKind >= UNIT_GOOMBA && target->currentKind < UNIT_UNUSED_TREE) {
                    BattleAudience_Case_KillEnemy(target->level);
                    BattleAudience_Case_FinalAttack();
                }
            }
        }
    } else if ((u32)target->damagePattern == 0x19) {
        target->damagePattern = 0;
    }
    target->tokenFlags |= TOKEN_FLAG_WAS_HIT;
    BattleRunHitEvent(target, result);
}

static u32 BattleCheckPikkyoro(BattleWeapon* weapon, u32* flags) {
    BattleWork* wp = _battleWorkPointer;
    s32 table[5] = {0};
    s32 count = 0;
    s32 idx = 0;
    u32 result = 0;
    u32 f;
    s32 r;

    if (flags) {
        result = *flags;
    }
    if (weapon->special & SPECIAL_ATTACK_FX) {
        f = (u32)wp->badgeEquippedFlags;
        if (f & BADGE_FLAG_ATTACK_FX_R) {
            table[0] = 1;
            idx = 0;
            count++;
        }
        if (f & BADGE_FLAG_ATTACK_FX_Y) {
            table[1] = 1;
            idx = 1;
            count++;
        }
        if (f & BADGE_FLAG_ATTACK_FX_B) {
            table[2] = 1;
            idx = 2;
            count++;
        }
        if (f & BADGE_FLAG_ATTACK_FX_G) {
            table[3] = 1;
            idx = 3;
            count++;
        }
        if (f & BADGE_FLAG_ATTACK_FX_P) {
            table[4] = 1;
            idx = 4;
            count++;
        }
    }
    if (count > 0) {
        if (count >= 2) {
            r = irand(count);
            for (idx = 4; idx > 0; idx--) {
                r -= table[idx];
                if (r < 0) {
                    break;
                }
            }
        }
        switch (idx) {
            case 0:
                result |= DAMAGE_FLAG_ATTACK_FX_R;
                break;
            case 1:
                result |= DAMAGE_FLAG_ATTACK_FX_Y;
                break;
            case 2:
                result |= DAMAGE_FLAG_ATTACK_FX_B;
                break;
            case 3:
                result |= DAMAGE_FLAG_ATTACK_FX_G;
                break;
            case 4:
                result |= DAMAGE_FLAG_ATTACK_FX_P;
                break;
        }
    }
    if (flags) {
        *flags = result;
    }
    return result;
}

static s32 BattleCalculateDamage(BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, u32* result, u32 flags) {
    u32 defaultResult;
    BattleWork* wp = _battleWorkPointer;
    s32 damage;
    s32 defense;
    s32 defenseAttr;
    u8 element;
    s32 n;
    u32 isJump;
    s8 turns;
    s8 strength;
    WeaponPowerFn fn;

    if (target->tokenFlags & TOKEN_FLAG_GUARDING) {
        flags |= DAMAGE_FLAG_GUARDING;
    }
    element = weapon->element;
    if (attacker && (weapon->special & SPECIAL_FIERY_IF_BURNED) && BtlUnit_CheckStatus(attacker, STATUS_BURN)) {
        element = 1;
    }
    defaultResult = flags | DAMAGE_HIT_NONE;
    *result = defaultResult;
    fn = weapon->hpDamageFn;
    if (fn == NULL) {
        return 0;
    }
    if (part->attributes & PART_ATTR_IMMUNE_TO_DAMAGE_OR_STATUS) {
        return 0;
    }
    if (attacker && (weapon->special & SPECIAL_BADGE_BUFFABLE) && attacker->badgesEquipped.AllOrNothing &&
        !((u32)wp->actionCommands.result & 2) && !(flags & DAMAGE_FLAG_AC_SUCCESS)) {
        return 0;
    }
    damage = weapon->hpDamageWork[0];
    if (fn) {
        damage = fn(attacker, weapon, target, part);
    }
    if (wp->majinaiState == 1 && (weapon->special & SPECIAL_STATUS_BUFFABLE)) {
        damage += 3;
    }
    if (weapon->special & SPECIAL_BADGE_BUFFABLE) {
        damage += attacker->badgesEquipped.PowerPlus;
        damage += attacker->badgesEquipped.PUpDDown;
        if (attacker->badgesEquipped.AllOrNothing) {
            if (((u32)wp->actionCommands.result & 2) || (flags & DAMAGE_FLAG_AC_SUCCESS)) {
                damage += attacker->badgesEquipped.AllOrNothing;
            } else {
                damage = 0;
                goto skip;
            }
        }
        if (attacker->currentHp <= attacker->kindParams->perilHP && attacker->badgesEquipped.MegaRush) {
            damage += attacker->badgesEquipped.MegaRush * 5;
        }
#if VERSION <= VERSION_DEMO_US
        else
#endif
            if (attacker->currentHp <= attacker->kindParams->dangerHP && attacker->badgesEquipped.PowerRush) {
            damage += attacker->badgesEquipped.PowerRush * 2;
        }
        if (attacker->badgesEquipped.IcePower && (part->attributes & PART_ATTR_WEAK_TO_ICE_POWER)) {
            damage += attacker->badgesEquipped.IcePower;
        }
    }
    if (weapon->special & SPECIAL_CHARGE_BUFFABLE) {
        if (BtlUnit_CheckStatus(attacker, STATUS_CHARGE)) {
            BtlUnit_GetStatus(attacker, STATUS_CHARGE, &turns, &strength);
            if ((damage += strength) < 0) {
                damage = 0;
            }
        }
        attacker->tokenFlags |= TOKEN_FLAG_CHARGE_EXPENDED;
    }
    if ((weapon->special & SPECIAL_STATUS_BUFFABLE) && BtlUnit_CheckStatus(attacker, STATUS_HUGE)) {
        BtlUnit_GetStatus(attacker, STATUS_HUGE, &turns, &strength);
        if ((damage += strength) < 0) {
            damage = 0;
        }
    }
    if ((weapon->special & SPECIAL_STATUS_BUFFABLE) && BtlUnit_CheckStatus(attacker, STATUS_ATTACK_UP)) {
        BtlUnit_GetStatus(attacker, STATUS_ATTACK_UP, &turns, &strength);
        if ((damage += strength) < 0) {
            damage = 0;
        }
    }
    isJump = (weapon->special & SPECIAL_BADGE_BUFFABLE) != 0;
    if (isJump) {
        damage -= attacker->badgesEquipped.PDownDUp;
    }
    if (isJump && attacker->badgesEquipped.HpDrain) {
        damage -= attacker->badgesEquipped.HpDrain;
    }
    if (isJump && attacker->badgesEquipped.FpDrain) {
        damage -= attacker->badgesEquipped.FpDrain;
    }
    if ((weapon->special & SPECIAL_STATUS_BUFFABLE) && BtlUnit_CheckStatus(attacker, STATUS_TINY)) {
        BtlUnit_GetStatus(attacker, STATUS_TINY, &turns, &strength);
        if ((damage += strength) < 0) {
            damage = 0;
        }
    }
    if ((weapon->special & SPECIAL_STATUS_BUFFABLE) && BtlUnit_CheckStatus(attacker, STATUS_ATTACK_DOWN)) {
        BtlUnit_GetStatus(attacker, STATUS_ATTACK_DOWN, &turns, &strength);
        if ((damage += strength) < 0) {
            damage = 0;
        }
    }
    if (damage < 0) {
        damage = 0;
    }
skip:
    defense = part->defense->defenses[element];
    defenseAttr = part->defenseAttr->defenseAttrs[element];
    switch (element) {
        case 1:
            *result = flags | DAMAGE_HIT_FIRE;
            break;
        case 2:
            *result = flags | DAMAGE_HIT_ICE;
            break;
        case 4:
            *result = flags | DAMAGE_HIT_ELECTRIC;
            break;
        case 3:
            *result = flags | DAMAGE_HIT_EXPLOSION;
            break;
        case 0:
        default:
            *result = flags | DAMAGE_HIT_NORMAL;
            break;
    }
    if (defenseAttr != 3) {
        if (target->badgesEquipped.DefendPlus) {
            defense += target->badgesEquipped.DefendPlus;
        }
        if (target->badgesEquipped.DamageDodge && (flags & DAMAGE_FLAG_GUARDED)) {
            defense += target->badgesEquipped.DamageDodge;
        }
#if VERSION <= VERSION_DEMO_US
        if (element == 1 && target->badgesEquipped.IcePower) {
            defense += target->badgesEquipped.IcePower;
        }
#endif
        if (BtlUnit_CheckStatusFlag(target, STATUS_FLAG_DEFENDING)) {
            defense++;
        }
        if (BtlUnit_CheckStatus(target, STATUS_DEFENSE_UP)) {
            BtlUnit_GetStatus(target, STATUS_DEFENSE_UP, &turns, &strength);
            defense += strength;
        }
        if (BtlUnit_CheckStatus(target, STATUS_DEFENSE_DOWN)) {
            BtlUnit_GetStatus(target, STATUS_DEFENSE_DOWN, &turns, &strength);
            if ((defense += strength) < 0) {
                defense = 0;
            }
        }
        if (wp->majinaiState == 2 && target->currentKind == UNIT_MARIO) {
            defense += 3;
        }
        if (part->attributes & PART_ATTR_WEAK_TO_ATTACK_FX_R) {
            if ((defense += target->work[1]) < 0) {
                defense = 0;
            }
        }
        if ((weapon->special & SPECIAL_PIERCES_DEFENSE) && defense > 0) {
            defense = 0;
        }
    }
    damage = (defenseAttr == 3) ? damage : damage - defense;
    if ((damage += target->badgesEquipped.PUpDDown) > 0) {
        if (weapon->special & SPECIAL_DIMINISHING_BY_HIT) {
            if ((damage -= target->hpDamageCount) <= 0) {
                damage = 1;
            }
        }
        if (weapon->special & SPECIAL_DIMINISHING_BY_TARGET) {
            if ((damage -= attacker->superguardedCount) <= 0) {
                damage = 1;
            }
        }
    }
    if (flags & DAMAGE_FLAG_GUARDED) {
        damage--;
    }
#if VERSION >= VERSION_JP
    if (element == 1 && target->badgesEquipped.IcePower) {
        damage -= target->badgesEquipped.IcePower;
    }
#endif
    damage -= target->badgesEquipped.PDownDUp;
    if (target->badgesEquipped.DoublePain) {
        damage *= target->badgesEquipped.DoublePain + 1;
    }
    if (target->badgesEquipped.LastStand && target->currentHp <= target->kindParams->dangerHP) {
#if VERSION <= VERSION_DEMO_US
        n = target->badgesEquipped.LastStand;
#else
        n = target->badgesEquipped.LastStand + 1;
#endif
        damage = (damage + n - 1) / n;
    }
    switch (defenseAttr) {
        case 1:
            damage++;
            break;
        case 2:
            damage = 0;
            break;
        case 4:
            if (!(flags & DAMAGE_FLAG_PIERCE_IMMUNE)) {
                damage = 0;
            }
            break;
        case 3:
            break;
    }
    if (damage < 0) {
        damage = 0;
    }
    if (defenseAttr == 3) {
        *result |= DAMAGE_FLAG_HEAL;
        return (u32)damage * -1;
    }
    if (damage <= 0) {
        *result = defaultResult;
        return 0;
    }
    if (flags & DAMAGE_FLAG_LAST_HIT) {
        if ((weapon->special & SPECIAL_FORCE_RESULT_10000) || !(target->attributeFlags & UNIT_ATTR_NO_LAST_HIT_RESULT)) {
            *result |= 0x10000;
        }
    }
    return damage;
}

static s32 BattleCalculateFpDamage(BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, u32* resultFlags, u32 flags) {
    BattleWork* wp = _battleWorkPointer;
    s32 damage = 0;
    s32 reduce = 0;
    WeaponPowerFn fn;

    if (*resultFlags & DAMAGE_FLAG_HEAL) {
        return 0;
    }
    fn = weapon->fpDamageFn;
    if (fn == NULL) {
        return 0;
    }
    if (part->attributes & PART_ATTR_IMMUNE_TO_DAMAGE_OR_STATUS) {
        return 0;
    }
    if (attacker && (weapon->special & SPECIAL_BADGE_BUFFABLE) && attacker->badgesEquipped.AllOrNothing &&
        !((u32)wp->actionCommands.result & 2)) {
        return 0;
    }
    if (fn) {
        damage = fn(attacker, weapon, target, part);
    }
    if (flags & DAMAGE_FLAG_GUARDED) {
        reduce = 1;
    }
    damage -= reduce;
    if (damage < 0) {
        damage = 0;
    }
    if (damage > 0 && (*resultFlags & DAMAGE_HIT_MASK) == DAMAGE_HIT_NONE) {
        *resultFlags = (*resultFlags & ~DAMAGE_HIT_MASK) | DAMAGE_HIT_NORMAL;
    }
    return damage;
}

static s32 _getSickStatusRate(BattleWeapon* weapon, s32 type) {
    BattleWeapon* w = weapon;
    switch (type) {
        case 1:
            return w->sleepChance;
        case 2:
            return w->stopChance;
        case 3:
            return w->dizzyChance;
        case 4:
            return w->poisonChance;
        case 5:
            return w->confuseChance;
        case 6:
            return w->electricChance;
        case 7:
            return w->dodgyChance;
        case 8:
            return w->burnChance;
        case 9:
            return w->freezeChance;
        case 10:
            if (w->sizeChangeStrength > 0) {
                return w->sizeChangeChance;
            }
            return 0;
        case 11:
            if (w->sizeChangeStrength <= 0) {
                return w->sizeChangeChance;
            }
            return 0;
        case 12:
            if (w->atkChangeStrength > 0) {
                return w->atkChangeChance;
            }
            return 0;
        case 13:
            if (w->atkChangeStrength <= 0) {
                return w->atkChangeChance;
            }
            return 0;
        case 14:
            if (w->defChangeStrength > 0) {
                return w->defChangeChance;
            }
            return 0;
        case 15:
            if (w->defChangeStrength <= 0) {
                return w->defChangeChance;
            }
            return 0;
        case 0:
            return w->allergicChance;
        case 19:
            return w->fastChance;
        case 20:
            return w->slowChance;
        case 25:
            return w->frightChance;
        case 26:
            return w->galeForceChance;
        case 27:
            return (u8)w->ohkoChance;
        case 18:
            return w->invisibleChance;
        case 23:
            return w->hpRegenTime > 0 ? 100 : 0;
        case 24:
            return w->fpRegenTime > 0 ? 100 : 0;
#if VERSION <= VERSION_DEMO_US
        case 16:
            return w->chargeStrength > 0 ? 100 : 0;
        case 21:
            return w->paybackTime > 0 ? 100 : 0;
#else
        case 16:
            return w->chargeStrength != 0 ? 100 : 0;
        case 21:
            return w->paybackTime != 0 ? 100 : 0;
#endif
        case 22:
            return w->holdFastTime > 0 ? 100 : 0;
        case 17:
            return 0;
    }
    return 0;
}

static void _getSickStatusParam(BattleUnit* unit, BattleWeapon* weapon, u32 type, s8* outTime, s8* outStrength) {
    BattleWeapon* w = weapon;
    s32 time;
    s32 strength;
    s32 badge;
    s32 n;

    switch (type) {
        case 1:
            time = strength = w->sleepTime;
            break;
        case 2:
            time = strength = w->stopTime;
            break;
        case 3:
            time = strength = w->dizzyTime;
            break;
        case 4:
            time = w->poisonTime;
            strength = w->poisonStrength;
            break;
        case 5:
            time = strength = w->confuseTime;
            break;
        case 6:
            time = strength = w->electricTime;
            break;
        case 7:
            time = strength = w->dodgyTime;
            break;
        case 8:
            time = strength = w->burnTime;
            break;
        case 9:
            time = strength = w->freezeTime;
            break;
        case 10:
            if (w->sizeChangeStrength > 0) {
                time = w->sizeChangeTime;
                strength = w->sizeChangeStrength;
            } else {
                strength = 0;
                time = 0;
            }
            break;
        case 11:
            if (w->sizeChangeStrength < 0) {
                time = w->sizeChangeTime;
                strength = w->sizeChangeStrength;
            } else {
                strength = 0;
                time = 0;
            }
            break;
        case 12:
            if (w->atkChangeStrength > 0) {
                time = w->atkChangeTime;
                strength = w->atkChangeStrength;
            } else {
                strength = 0;
                time = 0;
            }
            break;
        case 13:
            if (w->atkChangeStrength < 0) {
                time = w->atkChangeTime;
                strength = w->atkChangeStrength;
            } else {
                strength = 0;
                time = 0;
            }
            break;
        case 14:
            if (w->defChangeStrength > 0) {
                time = w->defChangeTime;
                strength = w->defChangeStrength;
            } else {
                strength = 0;
                time = 0;
            }
            break;
        case 15:
            if (w->defChangeStrength < 0) {
                time = w->defChangeTime;
                strength = w->defChangeStrength;
            } else {
                strength = 0;
                time = 0;
            }
            break;
        case 0:
            time = strength = w->allergicTime;
            break;
        case 19:
            time = strength = w->fastTime;
            break;
        case 20:
            time = strength = w->slowTime;
            break;
        case 27:
            time = strength = w->ohkoChance;
            break;
        case 18:
            time = strength = w->invisibleTime;
            break;
        case 23:
            time = w->hpRegenTime;
            strength = w->hpRegenStrength;
            break;
        case 24:
            time = w->fpRegenTime;
            strength = w->fpRegenStrength;
            break;
        case 16:
            time = w->chargeStrength;
            strength = w->chargeStrength;
            break;
        case 21:
            time = strength = w->paybackTime;
            break;
        case 22:
            time = strength = w->holdFastTime;
            break;
        default:
            strength = 0;
            time = 0;
            break;
    }

    badge = weapon->itemId;
    n = 0;
    if (badge >= 0xF0 && badge < 0x153) {
        n = pouchEquipCheckBadge(badge);
    }
    if (n > 0) {
        switch (badge) {
            case 0xF4:
                if (type == 11) {
                    time += (n - 1) * 2;
                }
                break;
            case 0xF5:
                if (type == 1) {
                    time += (n - 1) * 2;
                }
                break;
            case 0xF6:
                if (type == 15) {
                    time += (n - 1) * 2;
                }
                break;
            case 0xFB:
                if (type == 5) {
                    time += (n - 1) * 2;
                }
                break;
            case 0xFD:
                if (type == 9) {
                    time += (n - 1) * 2;
                }
                break;
            case 0x14F:
            case 0x150:
                if (type == 14 && unit->badgesEquipped.DefendUnused >= 2) {
                    strength += unit->badgesEquipped.DefendUnused - 1;
                }
                break;
        }
    }
    if (type == 16) {
        if (weapon == &badgeWeapon_Charge || weapon == &badgeWeapon_ChargeP) {
            if (unit->currentKind == UNIT_MARIO) {
                n = pouchEquipCheckBadge(ITEM_CHARGE);
            } else {
                n = pouchEquipCheckBadge(ITEM_CHARGE_P);
            }
            if (n >= 2) {
                strength += n - 1;
            }
        } else if (weapon == &badgeWeapon_SuperCharge || weapon == &badgeWeapon_SuperChargeP) {
            if (unit->currentKind == UNIT_MARIO) {
                n = pouchEquipCheckBadge(ITEM_SUPER_CHARGE);
            } else {
                n = pouchEquipCheckBadge(ITEM_SUPER_CHARGE_P);
            }
            if (n >= 2) {
                strength += (n - 1) * 2;
            }
        }
#if VERSION >= VERSION_JP
        if (strength >= 10) {
            strength = 9;
        }
#endif
    }
    *outTime = time;
    *outStrength = strength;
}

static u8 _getRegistStatus(BattleUnit* unit, s32 type) {
    BattleVulnerableStatus* v = unit->vulnStatus;
    switch (type) {
        case 1:
            return v->sleepRate;
        case 2:
            return v->stopRate;
        case 3:
            return v->dizzyRate;
        case 4:
            return v->poisonRate;
        case 5:
            return v->confuseRate;
        case 6:
            return v->electricRate;
        case 8:
            return v->burnRate;
        case 9:
            return v->freezeRate;
        case 10:
            return v->hugeRate;
        case 11:
            return v->tinyRate;
        case 12:
            return v->attackUpRate;
        case 13:
            return v->attackDownRate;
        case 14:
            return v->defenseUpRate;
        case 15:
            return v->defenseDownRate;
        case 0:
            return v->allergicRate;
        case 27:
            return v->instaKillRate;
        case 19:
            return v->fastRate;
        case 20:
            return v->slowRate;
        case 25:
            return v->frightRate;
        case 26:
            return v->galeForceRate;
        case 7:
            return v->dodgyRate;
        case 18:
            return v->invisibleRate;
    }
    return 100;
}

#include "eff/n64/eff_stamp_n64.h"
// FAKE: local prototype: effUpdownEntry declares the parameters as (s32, s32, s32, f32, f32, f32) (eff_updown.h: (s32, f32, f32, f32, s32, s32), same registers); this file was compiled with it and the header prototype changes the code.
EffectEntry* effUpdownEntry(s32 type, s32 strength, s32 time, f32 x, f32 y, f32 z);

#define STAMP_COL(e, r0, g0, b0, r1, g1, b1)      \
    ((EffStampN64Work*)(e)->userdata)->r = (r0);  \
    ((EffStampN64Work*)(e)->userdata)->g = (g0);  \
    ((EffStampN64Work*)(e)->userdata)->b = (b0);  \
    ((EffStampN64Work*)(e)->userdata)->r2 = (r1); \
    ((EffStampN64Work*)(e)->userdata)->g2 = (g1); \
    ((EffStampN64Work*)(e)->userdata)->b2 = (b1)

static s32 BattleSetStatusDamage(u32* result, BattleUnit* unit, BattleUnitPart* part, u32 special, s32 type, s32 rate, s32 levelDiff, s8 time, s8 strength) {
    s32 ok;
    s32 announce;
    s32 chance;
    s32 regist;
    f32 x, y, z;
    EffectEntry* eff;
    Vec hitPos;
    s8 prevStrength;
    s8 curTurns;
    s8 curStrength;

#if VERSION <= VERSION_DEMO_US
    BtlUnit_GetStatus(unit, STATUS_CHARGE, NULL, &prevStrength);
#else
    ok = 0;
    BtlUnit_GetStatus(unit, STATUS_CHARGE, NULL, &prevStrength);
    switch (type) {
        case 0x16:
        case 0x17:
        case 0x18:
            break;
        case 0x13:
        case 0x14:
            if (time <= 0) {
                ok = 1;
            }
            break;
        case 0:
        case 0x15:
            if (time <= 0) {
                ok = 1;
            }
            break;
        case 0xa:
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xe:
        case 0xf:
            if (strength == 0) {
                ok = 1;
            }
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if (time == 0) {
                ok = 1;
            }
            break;
    }
#endif
    if (part->attributes & PART_ATTR_IMMUNE_TO_DAMAGE_OR_STATUS) {
        return 0;
    }
    if (part->attributes & PART_ATTR_IMMUNE_TO_STATUS) {
        return 0;
    }
#if VERSION >= VERSION_JP
    if (BtlUnit_CheckStatus(unit, STATUS_ALLERGIC) && !ok) {
        return 0;
    }
#endif
    if (part->attributes & PART_ATTR_IMMUNE_TO_MOST_STATUS) {
        switch (type) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 8:
            case 9:
            case 0xb:
            case 0xd:
            case 0xf:
            case 0x14:
            case 0x19:
            case 0x1a:
            case 0x1b:
#if VERSION <= VERSION_DEMO_US
                return 0;
#else
                if (!ok) {
                    return 0;
                }
                break;
#endif
        }
    }
    if (unit->badgesEquipped.FeelingFine) {
        switch (type) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 0xb:
            case 0xd:
            case 0xf:
            case 0x1b:
                return 0;
        }
    }
    if ((u32)type == 8 && unit->badgesEquipped.IcePower) {
        return 0;
    }
    chance = rate;
    if (chance <= 0) {
        return 0;
    }
    regist = _getRegistStatus(unit, type);
    if (!(special & SPECIAL_IGNORE_STATUS_VULNERABILITY) || regist == 0) {
        chance = chance * regist / 100;
        if (!(special & SPECIAL_IGNORE_STATUS_VULNERABILITY) && regist > 0) {
            chance += levelDiff;
        }
    }
    if (irand(100) >= chance) {
        return 0;
    }

    ok = 0;
    if ((u32)type == STATUS_FRIGHT) {
        *result |= STATUS_RESULT_FRIGHT;
    } else if ((u32)type == STATUS_GALE_FORCE) {
        *result |= STATUS_RESULT_GALE_FORCE;
    } else {
        if ((u32)type == STATUS_SLEEP) {
            *result |= STATUS_RESULT_SLEEP;
        }
        if ((u32)type == STATUS_INSTANT_KILL) {
            *result |= STATUS_RESULT_INSTANT_KILL;
        }
        ok = ((BtlUnit_SetStatusS8Fn)BtlUnit_SetStatus)(unit, type, time, strength);
    }
    switch (type) {
        case 6:
        case 7:
        case 0xa:
        case 0xc:
        case 0xe:
        case 0x10:
        case 0x12:
        case 0x13:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
            *result |= STATUS_RESULT_OTHER;
            break;
        default:
            if (time > 0) {
                *result |= STATUS_RESULT_AILMENT;
            } else {
                *result |= STATUS_RESULT_OTHER;
            }
            break;
    }

    if (ok) {
        BtlUnit_GetPos(unit, &x, &y, &z);
        if (unit->attributeFlags & UNIT_ATTR_CEILING) {
            y -= BtlUnit_GetHeight(unit) / 2;
        } else {
            y += BtlUnit_GetHeight(unit) / 2;
        }
#if VERSION <= VERSION_DEMO_US
        switch (type) {
            case 1:
                effStampN64Entry(0, x, y, 10.0f + z);
                break;
            case 5:
                effStampN64Entry(1, x, y, 10.0f + z);
                break;
            case 0xe:
            case 0xf:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 0, 0, 200, 0, 0, 10);
                break;
            case 0xa:
            case 0xb:
            case 0xc:
            case 0xd:
            case 0x10:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 200, 0, 0, 10, 0, 0);
                break;
            default:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 200, 200, 200, 10, 10, 10);
                break;
        }
#else
        switch (unit->currentKind) {
            case 0x17:
            case 0x84:
            case 0xab:
                x -= 300.0f;
                z += 30.0f;
                break;
#if VERSION >= VERSION_US
            case 0x95:
            case 0x96:
                z += 40.0f;
                break;
#endif
        }
        switch (type) {
            case 1:
                effStampN64Entry(0, x, y, 10.0f + z);
                break;
            case 5:
                effStampN64Entry(1, x, y, 10.0f + z);
                break;
            case 2:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 110, 110, 10, 10, 10);
                break;
            case 3:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 0, 110, 220, 10, 10, 10);
                break;
            case 4:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 0, 220, 0, 10, 10, 10);
                break;
            case 6:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 0, 10, 10, 10);
                break;
            case 0x10:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 220, 220, 220, 0);
                break;
            case 0x15:
            case 0x16:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 0, 0, 0, 220);
                break;
            case 0xa:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 220, 220, 0, 0);
                break;
            case 0xb:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 0, 0, 10, 10, 10);
                break;
            case 0xc:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 220, 220, 0, 0);
                break;
            case 0xd:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 0, 0, 10, 10, 10);
                break;
            case 0xe:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 220, 0, 0, 220);
                break;
            case 0xf:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 0, 0, 220, 10, 10, 10);
                break;
            case 0x13:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 220, 220, 110, 0);
                break;
            case 0x14:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 110, 0, 10, 10, 10);
                break;
            case 8:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 0, 220, 0, 0);
                break;
            case 9:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 220, 0, 110, 220);
                break;
            case 0:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 160, 220, 0, 10, 10, 10);
                break;
            case 0x12:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 220, 110, 110, 110);
                break;
            case 0x17:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 220, 220, 110, 110);
                break;
            case 0x18:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 220, 160, 220, 0);
                break;
            case 7:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 220, 0, 220, 0);
                break;
            case 0x1b:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 220, 220, 220, 10, 10, 10);
                break;
            default:
                eff = effStampN64Entry(2, x, y, 10.0f + z);
                STAMP_COL(eff, 200, 200, 200, 10, 10, 10);
                break;
        }
#endif
        switch (type) {
            case 0xe:
            case 0xf:
                effUpdownEntry(1, strength, 0x3c, x, y, 20.0f + z);
                break;
            case 0xa:
            case 0xb:
            case 0xc:
            case 0xd:
            case 0x10:
                effUpdownEntry(0, strength, 0x3c, x, y, 15.0f + z);
                break;
        }
    } else {
        BtlUnit_GetPos(unit, &x, &y, &z);
        y += BtlUnit_GetHeight(unit) / 2;
        switch (type) {
            case 8:
                if (unit->iceEff) {
                    effSoftDelete(unit->iceEff);
                }
                break;
            case 9:
                eff = effVaporN64Entry(0, 0x3c, x, y, z, 1.0f);
                ((EffVaporN64Work*)eff->userdata)->r1 = 0xff;
                ((EffVaporN64Work*)eff->userdata)->g1 = 0xff;
                ((EffVaporN64Work*)eff->userdata)->b1 = 0xff;
                ((EffVaporN64Work*)eff->userdata)->r2 = 0xff;
                ((EffVaporN64Work*)eff->userdata)->g2 = 0xff;
                ((EffVaporN64Work*)eff->userdata)->b2 = 0xff;
                break;
        }
    }

    announce = 0;
    if (ok) {
        ((BtlUnit_GetStatusS8Fn)BtlUnit_GetStatus)(unit, type, &curTurns, &curStrength);
        switch (type) {
            case 0x10:
                if (curStrength > 0) {
                    if (prevStrength != curStrength) {
                        BattleStatusChangeInfoSetAnnouce(unit, type, curStrength, 1);
                        BattleStatusChangeMsgSetAnnouce(unit, type, 1);
                        announce = 1;
                    } else {
                        BattleStatusChangeInfoSetAnnouce(unit, type, curStrength, 0);
                        BattleStatusChangeMsgSetAnnouce(unit, type, 0);
                        announce = 1;
                    }
                }
                break;
            case 4:
                if (curStrength > 0) {
                    BattleStatusChangeInfoSetAnnouce(unit, type, curStrength, 1);
                    BattleStatusChangeMsgSetAnnouce(unit, type, 1);
                    announce = 1;
                }
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 0xa:
            case 0xb:
            case 0xc:
            case 0xd:
            case 0xe:
            case 0xf:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x17:
            case 0x18:
                if (curTurns > 0) {
                    BattleStatusChangeInfoSetAnnouce(unit, type, curTurns, 1);
                    BattleStatusChangeMsgSetAnnouce(unit, type, 1);
                    announce = 1;
                }
                break;
        }
    }
    BtlUnit_GetHitPos(unit, part, &hitPos.x, &hitPos.y, &hitPos.z);
    if (announce) {
        switch (type) {
            case 1:
                psndSFXOn_3D("SFX_CONDITION_SLEEP1", &hitPos);
                break;
            case 2:
                psndSFXOn_3D("SFX_CONDITION_STOP1", &hitPos);
                break;
            case 3:
                psndSFXOn_3D("SFX_CONDITION_GURUGURU1", &hitPos);
                break;
            case 5:
                psndSFXOn_3D("SFX_CONDITION_CONFUSE1", &hitPos);
                break;
            case 4:
                psndSFXOn_3D("SFX_CONDITION_POISON1", &hitPos);
                break;
            case 7:
                psndSFXOn_3D("SFX_CONDITION_YOKEYOKE1", &hitPos);
                break;
            case 6:
                psndSFXOn_3D("SFX_CONDITION_BIRIBIRI1", &hitPos);
                break;
            case 0xa:
                psndSFXOn_3D("SFX_CONDITION_DEKADEKA1", &hitPos);
                break;
            case 0xb:
                psndSFXOn_3D("SFX_CONDITION_MINIMINI1", &hitPos);
                break;
            case 0xe:
                psndSFXOn_3D("SFX_CONDITION_KATIKATI1", &hitPos);
                break;
            case 0xf:
                psndSFXOn_3D("SFX_BTL_FUNYA1", &hitPos);
                break;
            case 0x14:
                psndSFXOn_3D("SFX_CONDITION_SLOW1", &hitPos);
                break;
            case 8:
                psndSFXOn_3D("SFX_CONDITION_FIRE1", &hitPos);
                break;
            case 9:
                psndSFXOn_3D("SFX_CONDITION_ICE1", &hitPos);
                break;
            case 0x13:
                psndSFXOn_3D("SFX_CONDITION_FAST1", &hitPos);
                break;
            case 0x17:
                psndSFXOn_3D("SFX_CONDITION_REST_HP_SLOW1", &hitPos);
                break;
            case 0x18:
                psndSFXOn_3D("SFX_CONDITION_REST_FP_SLOW1", &hitPos);
                break;
            case 0:
                psndSFXOn_3D("SFX_CONDITION_ALLERGY1", &hitPos);
                break;
            case 0xc:
                psndSFXOn_3D("SFX_CONDITION_TUYOTUYO1", &hitPos);
                break;
            case 0xd:
                psndSFXOn_3D("SFX_CONDITION_YOWAYOWA1", &hitPos);
                break;
            case 0x10:
                psndSFXOn_3D("SFX_CONDITION_CHARGE1", &hitPos);
                break;
            case 0x12:
                psndSFXOn_3D("SFX_CONDITION_TOUMEI1", &hitPos);
                break;
            case 0x15:
                psndSFXOn_3D("SFX_CONDITION_COUNTER1", &hitPos);
                break;
            case 0x16:
                psndSFXOn_3D("SFX_BTL_THUNDERS_COUNTER1", &hitPos);
                break;
        }
    }
    return 1;
}

s32 BattleSetStatusDamageFromWeapon(BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, u32 flags) {
    s32 rate;
    u32 i;
    s32 levelDiff;
    u32 result = 0;
    s8 time;
    s8 strength;

    if (!(flags & DAMAGE_FLAG_NO_STATUS)) {
        for (i = 0; i < 28; i++) {
            _getSickStatusParam(attacker, weapon, i, &time, &strength);
            rate = (s8)_getSickStatusRate(weapon, i);
            levelDiff = 0;
            switch (i) {
                case 10:
                    if (!time && !strength) {
                        continue;
                    }
                    break;
                case 14:
                    if (!time && !strength) {
                        continue;
                    }
                    break;
                case 12:
                    if (!time && !strength) {
                        continue;
                    }
                    break;
                case 26:
                    if (rate > 0) {
                        levelDiff = attacker->level - target->level;
                    }
                    break;
            }
#if VERSION <= VERSION_DEMO_US
            BattleSetStatusDamage(&result, target, part, weapon->special, i, (s8)rate, levelDiff, time, strength);
#else
            if (BattleSetStatusDamage(&result, target, part, weapon->special, i, (s8)rate, levelDiff, time, strength) && i == 18) {
                btlDispPoseAnime(part);
            }
#endif
        }
    }
    return result;
}

s32 BattlePreCheckDamage(BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, u32 flags) {
    BattleWork* wp = _battleWorkPointer;
    s32 n;

    if (!target || !part) {
        return 1;
    }
    if (weapon->special & SPECIAL_CHARGE_BUFFABLE) {
        attacker->tokenFlags |= TOKEN_FLAG_CHARGE_EXPENDED;
    }
    if ((part->attributes & PART_ATTR_EVASIVE) && !(weapon->special & SPECIAL_HITS_EVASIVE_PARTS)) {
        return 2;
    }
    if (weapon->special & SPECIAL_ALWAYS_HITS) {
        return 1;
    }
    if (BtlUnit_CheckStatus(target, STATUS_INVISIBLE) || (target->attributeFlags & UNIT_ATTR_INTANGIBLE)) {
        return 4;
    }
    if (target->attributeFlags & UNIT_ATTR_VEILED) {
        return 4;
    }
    if ((part->counterAttributes & COUNTER_ATTR_PREEMPTIVE_FRONT_SPIKY) && !(weapon->counterResistFlags & COUNTER_RESIST_PREEMPTIVE_SPIKY) && !attacker->badgesEquipped.SpikeShield) {
        return 5;
    }
    if (part->attributes & PART_ATTR_INTANGIBLE) {
        return 4;
    }
    if (flags & DAMAGE_FLAG_ALWAYS_HIT) {
        return 1;
    }
    if (target->badgesEquipped.PrettyLucky) {
        for (n = target->badgesEquipped.PrettyLucky; n > 0; n--) {
            if (irand(100) >= 90) {
                return 3;
            }
        }
    }
    if (target->badgesEquipped.LuckyDay) {
        for (n = target->badgesEquipped.LuckyDay; n > 0; n--) {
            if (irand(100) >= 75) {
                return 3;
            }
        }
    }
    if (target->currentHp <= target->kindParams->dangerHP && target->badgesEquipped.CloseCall) {
        for (n = target->badgesEquipped.CloseCall; n > 0; n--) {
            if (irand(100) >= 67) {
                return 3;
            }
        }
    }
    if (BtlUnit_CheckStatus(target, STATUS_DODGY) && !BtlUnit_CheckStatus(target, STATUS_SLEEP) && !BtlUnit_CheckStatus(target, STATUS_STOP) && irand(100) >= 50) {
        return 6;
    }
    n = (u8)weapon->baseAccuracy;
    if (BtlUnit_CheckStatus(attacker, STATUS_DIZZY)) {
        n = n * 50 / 100;
    }
    if (wp->stageObjectWork.fogEffect) {
        n *= 0.5f;
    }
    if (irand(100) >= n) {
        return 2;
    }
    return 1;
}

static s32 _checkDamageCode_EmergencyRevival(BattleUnit* unit, u32* flags) {
    s32 kind = unit->currentKind;
    if (kind == 0xDE) {
        if ((s32)pouchCheckItem(ITEM_LIFE_SHROOM) > 0) {
            *flags |= DAMAGE_FLAG_LIFE_SHROOM;
            return 1;
        }
        return 0;
    }
    if (kind >= 0xE0 && kind < 0xE7) {
        if ((s32)pouchCheckItem(ITEM_LIFE_SHROOM) > 0) {
            *flags |= DAMAGE_FLAG_LIFE_SHROOM;
            return 1;
        }
        return 0;
    }
    if (unit->heldItem == 0x97) {
        *flags |= DAMAGE_FLAG_LIFE_SHROOM;
        return 1;
    }
    return 0;
}

s32 BattleCheckDamage(BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, s32 flags) {
    BattleWork* wp = _battleWorkPointer;
    u32 pattern;
    s32 ret = -1;
    u32 status = 0;
    s32 damage;
    s32 fpDamage;
    EffectEntry* eff;
    CounterWork cw;
    Vec hit;
    Vec hit2;
    CounterWork* cwp;
    Vec pos;
    u32 result;
    s32 code;
    s32 code2;
    u32 r1;
    u32 r2;
    u32 r3;
    u32 r4;
    s32 pierce;

    pierce = 0;
    cwp = &cw;
    BattleInitCounterPreCheckWork(cwp);
    if (!target) {
        return 18;
    }
    if (part) {
        target->currentTarget = part;
    }
    damage = 0;
    if (!(weapon->special & SPECIAL_UNGUARDABLE) && BtlUnit_GetACPossibility(target) && BattleActionCommandGetDefenceResult() == 5) {
        BtlUnit_GetHitPos(target, part, &hit.x, &hit.y, &hit.z);
        eff = effNiceEntry(2, hit.x - 60.0f, 45.0f + hit.y, hit.z - 10.0f);
        ((NiceEffectWork*)eff->userdata)->overallScale = 0.75f;
        flags |= DAMAGE_FLAG_SUPERGUARDED;
        psndSFXOn("SFX_SYSTEM_GREAT1");
        BattleAudience_Case_GuardGood();
        attacker->superguardedCount++;
        target->superguardCountTaken = attacker->superguardedCount;
        switch (weapon->superguardsAllowed) {
            case 2:
                result = flags | DAMAGE_HIT_SUPERGUARDED;
                BattleDamageDirect(attacker->unitId, target, part, 0, 0, result, weapon->damagePattern, 0);
                return 21;
            case 3:
                flags |= DAMAGE_FLAG_LAST_HIT;
                result = flags | DAMAGE_HIT_SUPERGUARDED;
                BattleDamageDirect(attacker->unitId, target, part, 0, 0, result, weapon->damagePattern, 0);
                return 21;
            case 4:
                flags |= DAMAGE_FLAG_LAST_HIT;
                result = flags | DAMAGE_HIT_SUPERGUARDED;
                BattleDamageDirect(attacker->unitId, target, part, 0, 0, result, weapon->damagePattern, 0);
                if (attacker->hitEventCode) {
                    BattleRunHitEventDirect(attacker, (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_SUPERGUARD_COUNTER), attacker->hitEventCode);
                } else {
                    BattleDamageDirect(-5, attacker, NULL, 1, 0, (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_SUPERGUARD_COUNTER), 0, 1);
                }
                return -1;
            case 1:
            default:
                flags |= DAMAGE_FLAG_LAST_HIT;
                result = flags | DAMAGE_HIT_SUPERGUARDED;
                BattleDamageDirect(attacker->unitId, target, part, 0, 0, result, weapon->damagePattern, 0);
                BattleDamageDirect(-5, attacker, NULL, 1, 0, (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_SUPERGUARD_COUNTER), 0, 1);
                return -1;
        }
    }
    BattleCheckCounter(cwp, attacker, target, part, weapon, (u32*)&flags);
    while (cw.noHazard) {
        if (flags & DAMAGE_FLAG_LAST_HIT) {
            if (part->counterAttributes & COUNTER_ATTR_VOLATILE_EXPLOSIVE) {
                BattleRunHitEvent(target, (DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_KO | DAMAGE_FLAG_DEFEATED | DAMAGE_HIT_EXPLOSION));
                ret = 18;
                break;
            }
            if ((part->counterAttributes & COUNTER_ATTR_EXPLOSIVE) &&
                (weapon->element == 3 || weapon->element == 4 || weapon->element == 1 ||
                 ((weapon->special & SPECIAL_FIERY_IF_BURNED) && BtlUnit_CheckStatus(attacker, STATUS_BURN)))) {
                BattleRunHitEvent(target, (DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_KO | DAMAGE_FLAG_DEFEATED | DAMAGE_HIT_EXPLOSION));
                ret = 18;
                break;
            }
        }
        if (!(weapon->special & SPECIAL_UNGUARDABLE) && BtlUnit_GetACPossibility(target)) {
            if (BattleActionCommandGetDefenceResult() > 3) {
                BtlUnit_GetHitPos(target, part, &hit2.x, &hit2.y, &hit2.z);
                eff = effNiceEntry(0, hit2.x - 60.0f, 45.0f + hit2.y, hit2.z - 10.0f);
                ((NiceEffectWork*)eff->userdata)->overallScale = 0.75f;
                flags |= DAMAGE_FLAG_GUARDED;
                psndSFXOn("SFX_SYSTEM_NICE1");
                BattleAudience_Case_GuardGood();
            } else {
                BattleAudience_Case_GuardBad();
            }
        }
        if ((weapon->special & SPECIAL_FLIPS_SHELLED) && (part->attributes & PART_ATTR_SHELLED)) {
            pierce = 1;
            flags |= DAMAGE_FLAG_FLIPPED;
        }
        if ((weapon->special & SPECIAL_FLIPS_BOMB_FLIPPABLE) && (part->attributes & PART_ATTR_BOMB_FLIPPABLE)) {
            pierce = 1;
            flags |= DAMAGE_FLAG_FLIPPED;
        }
        if ((weapon->special & SPECIAL_GROUNDS_WINGED) && (part->attributes & PART_ATTR_WINGED)) {
            pierce = 1;
            if (flags & DAMAGE_FLAG_LAST_HIT) {
                flags |= DAMAGE_FLAG_GROUNDED;
            }
        }
        BattleCheckPikkyoro(weapon, (u32*)&flags);
        damage = BattleCalculateDamage(attacker, target, part, weapon, &result, flags);
        fpDamage = BattleCalculateFpDamage(attacker, target, part, weapon, &result, flags);
        target->hpDamageCount++;
        if (!(flags & DAMAGE_FLAG_GUARDED)) {
            if (flags & DAMAGE_FLAG_STATUS_ANY_HIT) {
                status = BattleSetStatusDamageFromWeapon(attacker, target, part, weapon, flags);
            } else if (flags & DAMAGE_FLAG_LAST_HIT) {
                status = BattleSetStatusDamageFromWeapon(attacker, target, part, weapon, flags);
            }
        }
        if ((result & DAMAGE_HIT_MASK) == DAMAGE_HIT_NONE && pierce) {
            result = flags | DAMAGE_HIT_NORMAL;
        }
        if ((result & DAMAGE_HIT_MASK) == DAMAGE_HIT_NONE && (weapon->damagePattern == 0x13 || weapon->damagePattern == 0x1B)) {
            result = flags | DAMAGE_HIT_NORMAL;
        }
        if ((result & DAMAGE_HIT_MASK) == DAMAGE_HIT_NONE && status) {
            if (status & STATUS_RESULT_AILMENT) {
                result = flags | DAMAGE_HIT_NORMAL;
            } else {
                result = flags | DAMAGE_HIT_STATUS_ONLY;
            }
        }
        if (status & STATUS_RESULT_FRIGHT) {
            result = flags | DAMAGE_HIT_FRIGHT;
        }
        if (status & STATUS_RESULT_GALE_FORCE) {
            result = flags | DAMAGE_HIT_GALE_FORCE;
        }
        if (((u32)flags & DAMAGE_FLAG_LAST_HIT) && (status & STATUS_RESULT_INSTANT_KILL)) {
            code = (DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_KO | DAMAGE_FLAG_DEFEATED | DAMAGE_HIT_NORMAL);
            target->damagePattern = 0;
            _checkDamageCode_EmergencyRevival(target, (u32*)&code);
            BattleRunHitEvent(target, code);
            ret = 18;
            break;
        }
        if (((u32)flags & DAMAGE_FLAG_LAST_HIT) && (weapon->special & SPECIAL_SHATTERS_FREEZE) && BtlUnit_CheckStatus(target, STATUS_FREEZE) && irand(100) < 0) {
            code2 = (DAMAGE_FLAG_SHATTER | DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_KO | DAMAGE_FLAG_DEFEATED | DAMAGE_HIT_NORMAL);
            _checkDamageCode_EmergencyRevival(target, (u32*)&code2);
            BattleRunHitEvent(target, code2);
            ret = 18;
            break;
        }
        if (!status && !damage && !fpDamage && !pierce) {
            ret = 19;
            if (target->currentKind >= UNIT_GOOMBA && target->currentKind < UNIT_UNUSED_TREE && weapon->damagePattern != 0x1B) {
                BattleAudience_Case_EnemyNoDamage();
            }
        } else {
            ret = 18;
            if (target->currentKind >= UNIT_GOOMBA && target->currentKind < UNIT_UNUSED_TREE && (damage > 0 || status)) {
                BattleAudience_Case_EnemyDamage(damage);
            }
        }
        pattern = weapon->damagePattern;
        if (pattern == 0x14 && cw.msg) {
            pattern = 0;
        }
        if (pattern == 0xE || pattern == 0x10) {
            if (target->attributeFlags & UNIT_ATTR_NO_HAMMER_KNOCKBACK) {
                pattern = 0;
            }
            if (irand(100) >= target->kindParams->hammerKnockbackChance) {
                pattern = 0;
            }
            if (!(flags & DAMAGE_FLAG_AC_SUCCESS)) {
                pattern = 0;
            }
        }
        if (status & STATUS_RESULT_SLEEP) {
            BattleDamageDirect(attacker->unitId, target, part, damage, fpDamage, result, pattern, 0);
        } else {
            BattleDamageDirect(attacker->unitId, target, part, damage, fpDamage, result, pattern, 1);
        }
        break;
    }
    attacker->superguardedCount++;
    target->superguardCountTaken = attacker->superguardedCount;
    if (cw.msg) {
        if (cw.payback) {
            cw.count += damage * 50 / 100;
        }
        if (cw.holdFast) {
            cw.count += damage * 50 / 100;
        }
        if (cw.returnPostage) {
            cw.count += damage * 50 / 100;
        }
        if (cw.inflictPoison) {
            r1 = 0;
            BattleSetStatusDamage(&r1, attacker, part, 0, 4, 100, 0, 3, 1);
        }
        if (cw.inflictFreeze) {
            r2 = 0;
            BattleSetStatusDamage(&r2, attacker, part, 0, 9, 100, 0, 3, 1);
        }
        if (cw.inflictBurn) {
            r3 = 0;
            BattleSetStatusDamage(&r3, attacker, part, 0, 8, 100, 0, 3, 1);
        }
        if (cw.inflictElectric) {
            r4 = 0;
            BattleSetStatusDamage(&r4, attacker, part, 0, 6, 100, 0, 3, 1);
        }
        if (!cw.count) {
            cw.count = 1;
        }
        if (!attacker->alliance) {
            BattleAudience_Case_Countered();
        }
        if (cw.holdFast) {
            BtlUnit_GetHitPos(target, part, &pos.x, &pos.y, &pos.z);
            effBombEntry(0, pos.x, pos.y, pos.z, 1.0f);
            psndSFXOn_3D("SFX_BTL_THUNDERS_ATTACK4", &pos);
            BattleFogForceStop();
        }
        BattleActionCommandStop(wp);
        BattleAcHelpSetDispType(0);
        BattleDamageDirect(-5, attacker, NULL, cw.count, 0, cw.msg, 0, 1);
        if (cw.hitEvent) {
            target->damagePattern = 0;
            BattleRunHitEvent(target, cw.hitEvent);
        }
        return -1;
    }
    return ret;
}

void BattleAttackDeclare(s32* unitIdx, s32* partIdx) {
    s32 i;
    BattleUnit* unit;
    BattleUnitPart* part;
    BattleWork* wp;
    s32 j;
    s32 n;

    i = 0;
    wp = _battleWorkPointer;
    for (; i < BATTLE_UNIT_MAX; i++) {
        if (i == *unitIdx) {
            continue;
        }
        unit = BattleGetUnitPtr(wp, i);
        if (!unit) {
            continue;
        }
        if (unit->protectId != *unitIdx) {
            continue;
        }
        if (unit->tokenFlags & TOKEN_FLAG_WAS_HIT) {
            continue;
        }
        if (unit->tokenFlags & TOKEN_FLAG_GUARD_DECLARED) {
            continue;
        }
        if (!BtlUnit_CanGuardStatus(unit)) {
            continue;
        }
        n = (u8)unit->kindParams->numParts;
        part = unit->parts;
        for (j = 0; j < n; j++) {
            if (part->attributes & PART_ATTR_GUARD_COVER) {
                break;
            }
            part = part->nextPart;
        }
        if (j < n) {
            break;
        }
    }
    if (i < BATTLE_UNIT_MAX) {
        BattleGetUnitPtr(wp, *unitIdx)->damagePattern = 0;
        BattleRunHitEvent(BattleGetUnitPtr(wp, *unitIdx), 0x1029);
        BattleGetUnitPtr(wp, *unitIdx)->tokenFlags |= TOKEN_FLAG_GUARD_DECLARED;
        wp->flags |= BATTLE_FLAG_GUARD_MOVE;
        unit->damagePattern = 0;
        BattleRunHitEvent(unit, 0x1038);
        unit->tokenFlags |= TOKEN_FLAG_GUARDING;
        *unitIdx = i;
        *partIdx = part->kindPartParams->partNum;
    }
}

static void __declare(s32 unitIdx, s32 partIdx, s32* outUnit, s32* outPart) {
    s32 i;
    BattleUnit* unit;
    BattleUnitPart* part;
    BattleWork* wp;
    s32 j;
    s32 n;

    i = 0;
    wp = _battleWorkPointer;
    *outUnit = -1;
    *outPart = 0;
    for (; i < BATTLE_UNIT_MAX; i++) {
        if (i == unitIdx) {
            continue;
        }
        unit = BattleGetUnitPtr(wp, i);
        if (!unit) {
            continue;
        }
        if (unit->protectId != unitIdx) {
            continue;
        }
        if (unit->tokenFlags & TOKEN_FLAG_WAS_HIT) {
            continue;
        }
        if (unit->tokenFlags & TOKEN_FLAG_GUARD_DECLARED) {
            continue;
        }
        if (!BtlUnit_CanGuardStatus(unit)) {
            continue;
        }
        n = (u8)unit->kindParams->numParts;
        part = unit->parts;
        for (j = 0; j < n; j++) {
            if (part->attributes & PART_ATTR_GUARD_COVER) {
                break;
            }
            part = part->nextPart;
        }
        if (j < n) {
            break;
        }
    }
    if (i < BATTLE_UNIT_MAX) {
        BattleGetUnitPtr(wp, unitIdx)->damagePattern = 0;
        BattleRunHitEvent(BattleGetUnitPtr(wp, unitIdx), 0x1029);
        BattleGetUnitPtr(wp, unitIdx)->tokenFlags |= TOKEN_FLAG_GUARD_DECLARED;
        wp->flags |= BATTLE_FLAG_GUARD_MOVE;
        unit->damagePattern = 0;
        BattleRunHitEvent(unit, 0x1038);
        unit->tokenFlags |= TOKEN_FLAG_GUARDING;
        *outUnit = i;
        *outPart = part->kindPartParams->partNum;
    }
}

void BattleAttackDeclareAll(BattleWork* wp) {
    s32 i;
    BattleWorkWeaponTargets* wt = &wp->weaponTargets;
    BattleWorkTarget* t;
    s32 j;
    s32 k;
    s32 unit;
    s32 part;

    for (i = 0; i < wt->numTargets; i++) {
        t = &wt->targets[wt->targetIndices[i]];
        __declare(t->unitIdx, t->partIdx, &unit, &part);
        if (unit != -1) {
            for (j = 0; j < wt->numTargets; j++) {
                if (wt->targets[wt->targetIndices[j]].unitIdx == unit) {
                    for (k = j; k < wt->numTargets - 1; k++) {
                        wt->targetIndices[k] = wt->targetIndices[k + 1];
                    }
                    if (j <= i) {
                        i--;
                    }
                    wt->numTargets--;
                    break;
                }
            }
            t->unitIdx = unit;
            t->partIdx = part;
        }
    }
    wt->currentTarget = 0;
}

void BattleInitCounterPreCheckWork(CounterWork* work) {
    memset(work, 0, sizeof(CounterWork));
    work->noHazard = 1;
}

s32 BattleCheckCounter(CounterWork* work, BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, u32* flags) {
    if (!attacker) {
        return 0;
    }
    work->count = 0;
    if ((part->counterAttributes & COUNTER_ATTR_TOP_SPIKY) && !attacker->badgesEquipped.SpikeShield && !(weapon->counterResistFlags & COUNTER_RESIST_TOP_SPIKY)) {
        work->type = DAMAGE_HIT_COUNTER_TOP_SPIKY;
        work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_TOP_SPIKY);
        work->count++;
        work->hitEvent = 0x1F;
        *flags |= DAMAGE_FLAG_LAST_HIT;
        work->noHazard = 0;
    } else if ((part->counterAttributes & COUNTER_ATTR_PREEMPTIVE_FRONT_SPIKY) && !attacker->badgesEquipped.SpikeShield && !(weapon->counterResistFlags & COUNTER_RESIST_PREEMPTIVE_SPIKY)) {
        work->type = DAMAGE_HIT_COUNTER_PREEMPTIVE_SPIKY;
        work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_PREEMPTIVE_SPIKY);
        work->count++;
        work->hitEvent = 0x20;
        *flags |= DAMAGE_FLAG_LAST_HIT;
        work->noHazard = 0;
    } else if ((part->counterAttributes & COUNTER_ATTR_FRONT_SPIKY) && !attacker->badgesEquipped.SpikeShield && !(weapon->counterResistFlags & COUNTER_RESIST_FRONT_SPIKY)) {
        work->type = DAMAGE_HIT_COUNTER_FRONT_SPIKY;
        work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_FRONT_SPIKY);
        work->count++;
        work->hitEvent = 0x21;
        *flags |= DAMAGE_FLAG_LAST_HIT;
        work->noHazard = 0;
    } else if (((part->counterAttributes & COUNTER_ATTR_FIERY) || (part->counterAttributes & COUNTER_ATTR_FIERY_STATUS)) && !attacker->badgesEquipped.IcePower && !(weapon->counterResistFlags & COUNTER_RESIST_FIERY)) {
        work->type = DAMAGE_HIT_COUNTER_FIERY;
        work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_FIERY);
        work->count++;
        work->hitEvent = 0x22;
        *flags |= DAMAGE_FLAG_LAST_HIT;
        work->noHazard = 0;
        if (part->counterAttributes & COUNTER_ATTR_FIERY_STATUS) {
            work->inflictBurn = 1;
        }
    } else if (((part->counterAttributes & COUNTER_ATTR_ICY) || (part->counterAttributes & COUNTER_ATTR_ICY_STATUS)) && !(weapon->counterResistFlags & COUNTER_RESIST_ICY)) {
        work->type = DAMAGE_HIT_COUNTER_ICY;
        work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_ICY);
        work->count++;
        work->hitEvent = 0x23;
        *flags |= DAMAGE_FLAG_LAST_HIT;
        work->noHazard = 0;
        if (part->counterAttributes & COUNTER_ATTR_ICY_STATUS) {
            work->inflictFreeze = 1;
        }
    } else if (((part->counterAttributes & COUNTER_ATTR_ELECTRIC) || (part->counterAttributes & COUNTER_ATTR_ELECTRIC_STATUS)) && !(weapon->counterResistFlags & COUNTER_RESIST_ELECTRIC) && !BtlUnit_CheckStatus(attacker, STATUS_ELECTRIC)) {
        work->type = DAMAGE_HIT_COUNTER_ELECTRIC;
        work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_ELECTRIC);
        work->count++;
        work->hitEvent = 0x24;
        *flags |= DAMAGE_FLAG_LAST_HIT;
        work->noHazard = 0;
        if (part->counterAttributes & COUNTER_ATTR_ELECTRIC_STATUS) {
            work->inflictElectric = 1;
        }
    } else {
        if ((part->counterAttributes & COUNTER_ATTR_EXPLOSIVE) && !(weapon->counterResistFlags & COUNTER_RESIST_EXPLOSIVE)) {
            if (weapon->element == 3 || weapon->element == 4 || weapon->element == 1 ||
                ((weapon->special & SPECIAL_FIERY_IF_BURNED) && BtlUnit_CheckStatus(attacker, STATUS_BURN))) {
                work->type = DAMAGE_HIT_COUNTER_EXPLOSIVE;
                work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_EXPLOSIVE);
                work->count++;
                *flags |= DAMAGE_FLAG_LAST_HIT;
            }
        }
        if ((part->counterAttributes & COUNTER_ATTR_VOLATILE_EXPLOSIVE) && !(weapon->counterResistFlags & COUNTER_RESIST_VOLATILE_EXPLOSIVE)) {
            work->type = DAMAGE_HIT_COUNTER_VOLATILE_EXPLOSIVE;
            work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_VOLATILE_EXPLOSIVE);
            work->count++;
            *flags |= DAMAGE_FLAG_LAST_HIT;
        }
        if ((BtlUnit_CheckStatus(target, STATUS_ELECTRIC) || (part->counterAttributes & COUNTER_ATTR_ELECTRIC) || (part->counterAttributes & COUNTER_ATTR_ELECTRIC_STATUS)) &&
            !(weapon->counterResistFlags & COUNTER_RESIST_ELECTRIC) && !BtlUnit_CheckStatus(attacker, STATUS_ELECTRIC)) {
            work->type = DAMAGE_HIT_COUNTER_ELECTRIFIED;
            work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_ELECTRIFIED);
            work->count++;
            *flags |= DAMAGE_FLAG_LAST_HIT;
            if (part->counterAttributes & COUNTER_ATTR_ELECTRIC_STATUS) {
                work->inflictElectric = 1;
            }
        }
        if (BtlUnit_CheckStatus(target, STATUS_PAYBACK) && !(weapon->counterResistFlags & COUNTER_RESIST_PAYBACK)) {
            work->type = DAMAGE_HIT_COUNTER_PAYBACK;
            work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_PAYBACK);
            *flags |= DAMAGE_FLAG_LAST_HIT;
            work->payback = 1;
        }
        if (((part->counterAttributes & COUNTER_ATTR_POISON) || (part->counterAttributes & COUNTER_ATTR_POISON_STATUS)) && !(weapon->counterResistFlags & COUNTER_RESIST_POISON)) {
            work->type = DAMAGE_HIT_COUNTER_POISON;
            work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_POISON);
            *flags |= DAMAGE_FLAG_LAST_HIT;
            work->payback = 1;
            if (part->counterAttributes & COUNTER_ATTR_POISON_STATUS) {
                work->inflictPoison = 1;
            }
        }
        if (BtlUnit_CheckStatus(target, STATUS_HOLD_FAST) && !(weapon->counterResistFlags & COUNTER_RESIST_HOLD_FAST)) {
            work->type = DAMAGE_HIT_COUNTER_HOLD_FAST;
            work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_HOLD_FAST);
            *flags |= DAMAGE_FLAG_LAST_HIT;
            work->holdFast = 1;
        }
        if (target->badgesEquipped.ReturnPostage && !(weapon->counterResistFlags & COUNTER_RESIST_PAYBACK)) {
            work->type = DAMAGE_HIT_COUNTER_PAYBACK;
            work->msg = (DAMAGE_FLAG_LAST_HIT | DAMAGE_HIT_COUNTER_PAYBACK);
            *flags |= DAMAGE_FLAG_LAST_HIT;
            work->returnPostage = 1;
        }
    }
    switch (work->type) {
        case DAMAGE_HIT_COUNTER_TOP_SPIKY:
            return 8;
        case DAMAGE_HIT_COUNTER_PREEMPTIVE_SPIKY:
            return 7;
        case DAMAGE_HIT_COUNTER_FRONT_SPIKY:
            return 9;
        case DAMAGE_HIT_COUNTER_FIERY:
            return 10;
        case DAMAGE_HIT_COUNTER_ICY:
            return 11;
        case DAMAGE_HIT_COUNTER_EXPLOSIVE:
            return 12;
        case DAMAGE_HIT_COUNTER_VOLATILE_EXPLOSIVE:
            return 13;
        case DAMAGE_HIT_COUNTER_ELECTRIFIED:
            if (1) {
                return 14;
            }
        case DAMAGE_HIT_COUNTER_POISON:
            return 15;
        case DAMAGE_HIT_COUNTER_PAYBACK:
            return 16;
        case DAMAGE_HIT_COUNTER_HOLD_FAST:
            return 17;
    }
    return 0;
}
