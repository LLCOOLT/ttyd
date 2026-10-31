// Target detection: picks which enemies a weapon can hit and who attacks first.
#include "version.h"
// this unit is size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
#include "battle/battle.h"
#include "battle/battle_monosiri.h"
#include "battle/battle_unit.h"
#include "data/item_data.h"
#include "battle/battle_sub.h"
#include "system.h"

/**
 * Builds d->targets: one entry per targetable part of every living unit, with its cursor position,
 * sort score and front/back side, then drops every entry the weapon's class
 * and property flags rule out (only Mario, no partner, alliance, floating or ceiling units, jump/hammer reach,
 * ...) and orders the rest in d->targetIndices by x along the attack direction.
 * numTargets is -1 for weapons with TARGET_CLASS_NONE.
 */
static void _btlSamplingEnemy(BattleWorkWeaponTargets* d) {
    BattleUnitKindPart* kp;
    BattleWorkTarget* tg4;
    s32 k;
    s32 n = 0;
    BattleWorkTarget* t = d->targets;
    BattleWork* wp = _battleWorkPointer;
    s32 j;
    BattleUnitPart* part;
    s32 i;
    BOOL ok4;
    BattleUnit* u1;
    BattleWorkTarget* o4;
    s32 np2;
    BattleUnit* u2;

    if (d->classFlags & TARGET_CLASS_NONE) {
        d->numTargets = -1;
        return;
    }
    {
        for (i = 0; i < BATTLE_UNIT_MAX; i++) {
            BattleUnit* unit = BattleGetUnitPtr(wp, i);
            if (unit && !BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL) && !(unit->attributeFlags & UNIT_ATTR_NOT_SAMPLED_AS_TARGET)) {
                part = unit->parts;
                np2 = unit->kindParams->numParts & 0xFF;
                for (j = 0; j < np2; j++) {

                    s32 dir;
                    f32 x, y, z;
                    f32 ox, oy, oz;
                    if (part->attributes & PART_ATTR_NOT_TARGETABLE) {
                        part = part->nextPart;
                        continue;
                    }
                    kp = part->kindPartParams;
                    dir = part->faceDirection;
                    BtlUnit_GetPartsWorldPos(part, &x, &y, &z);
                    if (!(unit->attributeFlags & UNIT_ATTR_CEILING)) {
                        y += part->positionOffset.y * unit->sizeMultiplier;
                    }
                    ox = x;
                    oy = y;
                    oz = 5.0f + z;
                    x += dir * (unit->sizeMultiplier * (part->hitCursorBaseOffset.x + part->hitCursorOffset.x));
                    y += unit->sizeMultiplier * (part->hitCursorBaseOffset.y + part->hitCursorOffset.y);
                    z += unit->sizeMultiplier * (part->hitCursorBaseOffset.z + part->hitCursorOffset.z);
                    t->unitIdx = i;
                    t->partIdx = kp->partNum;
                    t->posX = x;
                    t->posY = y;
                    t->posZ = z;
                    t->score = 0;
                    t->reserved_20 = -1;
                    if ((unit->attributeFlags & UNIT_ATTR_TARGET_SORT_OFFSET) && !(part->attributes & PART_ATTR_NO_TARGET_SORT_OFFSET)) {
                        t->score += d->direction * 300;
                    }
                    t->score += part->hitOffsetX * dir;
                    t->x = (s16)(ox + t->score);
                    t->y = (s16)oy;
                    t->z = (s16)oz;
                    t->forwardLv = BtlCompForwardLv(d->direction, t->x);
                    if (t->z < -30) {
                        t->side = 0;
                    } else {
                        t->side = 1;
                    }
                    part = part->nextPart;
                    n++;
                    t++;
                }
            }
        }
    }
    {
        d->currentTarget = i = 0;
        d->numTargets = n;
        n = d->numTargets;
        t = d->targets;
        for (; n > i; i++) {
            BattleWorkTarget* tg = &t[i];
            BattleUnit* unit = BattleGetUnitPtr(wp, tg->unitIdx);
            BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, tg->partIdx);
            {
                BOOL ok;
                do {
                    u32 flags = d->classFlags;
                    if (flags & TARGET_CLASS_NONE) {
                        {
                            ok = FALSE;
                            break;
                        }
                    }
                    if (flags & TARGET_CLASS_ONLY_MARIO) {
                        if (unit->currentKind != UNIT_MARIO) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_ONLY_TREE_OR_SWITCH) {
                        if (unit->currentKind < UNIT_UNUSED_TREE || unit->currentKind >= UNIT_UNUSED_TESTNPC) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_NO_MARIO) {
#if VERSION <= VERSION_DEMO_JP
                        if (unit->currentKind == UNIT_MARIO) {
#else
                        if (unit->currentKind == UNIT_MARIO || unit->currentKind == UNIT_SHELL_SHIELD) {
#endif
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_NO_PARTNER) {
                        if (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_NO_ENEMY) {
                        if (unit->currentKind >= UNIT_GOOMBA && unit->currentKind < UNIT_UNUSED_TREE) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_NO_SYSTEM_UNIT) {
                        if (unit->currentKind >= UNIT_UNUSED_TESTNPC && unit->currentKind < UNIT_MARIO) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_NO_TREE_OR_SWITCH) {
                        if (unit->currentKind >= UNIT_UNUSED_TREE && unit->currentKind < UNIT_UNUSED_TESTNPC) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_NO_SELF) {
                        if (d->unitId == unit->unitId) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_NO_OPPOSING_ALLIANCE) {
                        if (d->belong == unit->alliance) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_NO_OWN_ALLIANCE) {
                        if (d->belong != unit->alliance && unit->alliance != 2) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_NO_SAME_KIND) {
                        if (d->unitId != unit->unitId && unit->currentKind == BattleGetUnitPtr(wp, d->unitId)->currentKind) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    flags = d->classFlags;
                    if (flags & TARGET_CLASS_ONLY_SELF) {
                        if (d->unitId != unit->unitId) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_MAIN_PARTS) {
                        u32 a = part->attributes;
                        if (!((a & PART_ATTR_MAIN) || (a & PART_ATTR_IMPORTANT)) || (a & PART_ATTR_NOT_PART_TARGET)) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (flags & TARGET_CLASS_ANY_PART) {
                        u32 a = part->attributes;
#if VERSION >= VERSION_US
                        if (!((a & PART_ATTR_MAIN) || (a & PART_ATTR_IMPORTANT) || (a & PART_ATTR_SEMI_IMPORTANT)) || (a & PART_ATTR_NOT_ANY_PART_TARGET) || (a & PART_ATTR_NOT_PART_TARGET)) {
#else
                        if (!((a & PART_ATTR_MAIN) || (a & PART_ATTR_IMPORTANT) || (a & PART_ATTR_SEMI_IMPORTANT)) || (a & PART_ATTR_NOT_PART_TARGET)) {
#endif
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    ok = TRUE;
                } while (0);
                if (!ok) {
                    for (k = i; k < n - 1; k++) {
                        d->targets[k] = d->targets[k + 1];
                    }
                    n--;
                    i--;
                }
            }
        }
    }

    {
        for (i = 0; n > i; i++) {
            BattleWorkTarget* tg = &t[i];
            BattleUnit* unit = BattleGetUnitPtr(wp, tg->unitIdx);
            BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, tg->partIdx);
            {
                BOOL ok;
                do {
                    if (d->propFlags & TARGET_PROP_TATTLE) {
                        if (part->attributes & PART_ATTR_UNTATTLEABLE) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                        if (!battleGetUnitMonosiriPtr(unit->currentKind)) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                        if (!battleGetUnitMonosiriPtr(unit->currentKind)->tattleBtlTag) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (d->propFlags & TARGET_PROP_NO_FLOATING) {
                        if (unit->attributeFlags & UNIT_ATTR_FLOATING) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (d->propFlags & TARGET_PROP_NO_CEILING) {
                        if (unit->attributeFlags & UNIT_ATTR_CEILING) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (d->propFlags & TARGET_PROP_NO_FLOATING_2) {
                        if (unit->attributeFlags & UNIT_ATTR_FLOATING) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (d->propFlags & TARGET_PROP_ONLY_AIRBORNE) {
                        u32 a = unit->attributeFlags;
                        if (!(a & 4) && !(a & 2)) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (d->propFlags & TARGET_PROP_JUMPLIKE) {
                        if (part->attributes & PART_ATTR_JUMPLIKE_CANNOT_TARGET) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (d->propFlags & TARGET_PROP_HAMMERLIKE) {
                        if (part->attributes & PART_ATTR_HAMMERLIKE_CANNOT_TARGET) {
#if VERSION <= VERSION_DEMO_JP
                            {
                                ok = FALSE;
                                break;
                            }
#else
                            if (!(d->propFlags & TARGET_PROP_RECOIL) || d->unitId != unit->unitId) {
                                {
                                    ok = FALSE;
                                    break;
                                }
                            }
#endif
                        }
                    }
                    if (d->propFlags & TARGET_PROP_SHELL_TOSS_LIKE) {
                        if (part->attributes & PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (d->propFlags & TARGET_PROP_ONLY_SHELL_TOSS_IMMUNE) {
                        if (!(part->attributes & PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (d->propFlags & TARGET_PROP_NO_SHELL_SHIELDED) {
                        if (unit->attributeFlags & UNIT_ATTR_SHELL_SHIELDED) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    if (d->propFlags & TARGET_PROP_NO_PART_ATTR_2000000) {
                        if (part->attributes & PART_ATTR_NO_SHADOW) {
                            {
                                ok = FALSE;
                                break;
                            }
                        }
                    }
                    ok = TRUE;
                } while (0);
                if (!ok) {
                    for (k = i; k < n - 1; k++) {
                        d->targets[k] = d->targets[k + 1];
                    }
                    n--;
                    i--;
                }
            }
        }
    }

    if (d->classFlags & TARGET_CLASS_MAIN_PARTS) {
        {
            for (i = 0; n > i; i++) {
                BattleWorkTarget* tg = &t[i];
                BattleUnitPart* part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(wp, tg->unitIdx), tg->partIdx);
                BOOL keep = TRUE;
                if (part->attributes & PART_ATTR_IMPORTANT) {
                    for (j = 0; j < n; j++) {
                        BattleWorkTarget* o = &t[j];
                        if (tg != o && tg->unitIdx == o->unitIdx) {
                            if (BtlUnit_GetPartsPtr(BattleGetUnitPtr(wp, o->unitIdx), o->partIdx)->attributes & PART_ATTR_MAIN) {
                                keep = FALSE;
                                break;
                            }
                        }
                    }
                }
                if (!keep) {
                    for (k = i; k < n - 1; k++) {
                        d->targets[k] = d->targets[k + 1];
                    }
                    n--;
                    i--;
                }
            }
        }
    }

    {
        for (i = 0; n > i; i++) {
            BOOL keep;
            BattleUnitPart* part;
            tg4 = &t[i];
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(wp, tg4->unitIdx), tg4->partIdx);
            do {
                if ((d->propFlags & TARGET_PROP_FRONTMOST) && !(part->attributes & PART_ATTR_INTANGIBLE)) {
                    ok4 = TRUE;
                    for (j = 0; j < n; j++) {
                        s32 a;
                        s32 b;
                        o4 = &t[j];
                        if (tg4 == o4 || tg4->side != o4->side) {
                            continue;
                        }
                        a = tg4->x;
                        b = o4->x;
                        if (d->direction < 0) {
                            a *= -1;
                            b *= -1;
                        }
                        if (a > b) {
                            BattleUnitPart* op = BattleGetUnitPartsPtr(o4->unitIdx, o4->partIdx);
                            if (!(op->attributes & PART_ATTR_INTANGIBLE) && !(op->attributes & PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET)) {
                                u1 = BattleGetUnitPtr(wp, d->unitId);
                                u2 = BattleGetUnitPtr(wp, o4->unitIdx);
                                if (!(u1->tokenFlags & TOKEN_FLAG_CONFUSED_ACTION) || u1 != u2) {
                                    ok4 = FALSE;
                                    break;
                                }
                            }
                        }
                    }
                    if (!ok4) {
                        keep = FALSE;
                        break;
                    }
                }
                keep = TRUE;
            } while (0);

            if (!keep) {
                for (k = i; k < n - 1; k++) {
                    d->targets[k] = d->targets[k + 1];
                }
                n--;
                i--;
            }
        }
    }

    d->numTargets = n;
    {
        s8* idx = d->targetIndices;
        t = d->targets;
        n = d->numTargets;
        for (i = 0; i < n; i++) {
            idx[i] = i;
        }
        if (d->direction > 0) {
            for (i = 0; i < n - 1; i++) {
                for (j = i + 1; j < n; j++) {
                    BattleWorkTarget* ta = &t[idx[i]];
                    BattleWorkTarget* tb = &t[idx[j]];
                    if (ta->posX + ta->score * 10 > tb->posX + tb->score * 10) {
                        {
                            s8 a = idx[i];
                            idx[i] = idx[j];
                            idx[j] = a;
                        }
                    }
                }
            }
        } else {
            for (i = 0; i < n - 1; i++) {
                for (j = i + 1; j < n; j++) {
                    BattleWorkTarget* ta = &t[idx[i]];
                    BattleWorkTarget* tb = &t[idx[j]];
                    if (ta->posX + ta->score * 10 <= tb->posX + tb->score * 10) {
                        {
                            s8 a = idx[i];
                            idx[i] = idx[j];
                            idx[j] = a;
                        }
                    }
                }
            }
        }
    }
}

/**
 * Fills d with the attack's parameters (weapon, attacker unitId, enemy side belong,
 * target class and property flags, direction) and builds its target list with _btlSamplingEnemy.
 * A confused attacker gets the "own side" and "opposing side" class flags swapped so it targets its allies;
 * returns TRUE when that swap happened.
 */
BOOL BattleSamplingEnemy(BattleWorkWeaponTargets* d, BattleWeapon* weapon, s32 unitId, s8 belong, u32 classFlags, u32 propFlags,
                         s8 direction) {
    BOOL r = FALSE;
    d->weapon = weapon;
    d->unitId = unitId;
    d->belong = belong;
    d->classFlags = classFlags;
    d->propFlags = propFlags;
    d->direction = direction;
    if (BattleGetUnitPtr(_battleWorkPointer, unitId)->tokenFlags & TOKEN_FLAG_CONFUSED_ACTION) {
        if ((d->classFlags & TARGET_CLASS_NO_OPPOSING_ALLIANCE) && !(d->classFlags & TARGET_CLASS_NO_OWN_ALLIANCE)) {
            r = TRUE;
            d->classFlags &= ~TARGET_CLASS_NO_OPPOSING_ALLIANCE;
            d->classFlags |= TARGET_CLASS_NO_OWN_ALLIANCE;
        } else if (!(d->classFlags & TARGET_CLASS_NO_OPPOSING_ALLIANCE) && (d->classFlags & TARGET_CLASS_NO_OWN_ALLIANCE)) {
            r = TRUE;
            d->classFlags |= TARGET_CLASS_NO_OPPOSING_ALLIANCE;
            d->classFlags &= ~TARGET_CLASS_NO_OWN_ALLIANCE;
        }
    }
    _btlSamplingEnemy(d);
    return r;
}

/**
 * Rebuilds the target list for a weapon; the command menu calls it each time the selection cursor needs fresh
 * targets.
 */
void BattleSamplingEnemyUpdate(BattleWorkWeaponTargets* d) {
    _btlSamplingEnemy(d);
}

/**
 * Picks the unit and part an AI attack hits.
 * Each candidate gets a weight from flags (TARGET_WEIGHT_PREFER_MARIO, low HP, in Peril, front/back, ...),
 * then the heaviest wins, or with TARGET_WEIGHT_RANDOM one is drawn in proportion to the weights.
 * Outputs -1/0 when there is no target. Used by enemy scripts, stage hazards and the UFO.
 */
void BattleChoiceSamplingEnemy(BattleWorkWeaponTargets* d, u32 flags, s32* unitOut, s32* partOut) {
    BattleUnit* unit;
    BattleWork* wp = _battleWorkPointer;
    s32 w[74];
    s32 i;
    BattleUnit* active;

    *unitOut = -1;
    *partOut = 0;
    if (d->numTargets > 0) {
        active = BattleGetUnitPtr(wp, d->unitId);
        i = d->targetIndices[0];
        *unitOut = d->targets[i].unitIdx;
        *partOut = d->targets[i].partIdx;
        for (i = 0; i < 74; i++) {
            w[i] = 0;
        }
        w[d->targetIndices[0]] += 10;
        for (i = 0; i < d->numTargets; i++) {
            s32 id = d->targetIndices[i];
            unit = BattleGetUnitPtr(wp, d->targets[id].unitIdx);
            w[id] += 100;
            if ((flags & TARGET_WEIGHT_PREFER_MARIO) && unit->currentKind == UNIT_MARIO) {
                w[id] = 1.5f * w[id];
            }
            if ((flags & TARGET_WEIGHT_PREFER_PARTNER) && unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX) {
                w[id] = 1.5f * w[id];
            }
            if ((flags & TARGET_WEIGHT_PREFER_FRONT)) {
                f32 t = 0.4f * (d->numTargets - i);
                w[id] *= 0.1f + t;
            }
            if ((flags & TARGET_WEIGHT_PREFER_BACK)) {
                f32 t = 0.4f * i;
                w[id] = (0.5f + t) * w[id];
            }
            if ((flags & TARGET_WEIGHT_PREFER_OWN_ALLIANCE) && active->alliance == unit->alliance) {
                w[id] = 1.5f * w[id];
            }
            if ((flags & TARGET_WEIGHT_PREFER_OPPOSING_ALLIANCE) && active->alliance != unit->alliance && unit->alliance != 2) {
                w[id] = 1.5f * w[id];
            }
            if ((flags & TARGET_WEIGHT_PREFER_LOW_HP_RATIO)) {
                w[id] = (2.0f - (f32)unit->currentHp / (f32)unit->maxHp) * w[id];
            }
            if ((flags & TARGET_WEIGHT_PREFER_HIGH_HP_RATIO)) {
                w[id] = (1.0f + (f32)unit->currentHp / (f32)unit->maxHp) * w[id];
            }
            if ((flags & TARGET_WEIGHT_PREFER_LOW_HP)) {
                w[id] = (1.5f - 0.05f * unit->currentHp) * w[id];
            }
            if ((flags & TARGET_WEIGHT_PREFER_HIGH_HP)) {
                w[id] = (1.0f + 0.05f * unit->currentHp) * w[id];
            }
            if ((flags & TARGET_WEIGHT_PREFER_IN_PERIL) && unit->currentHp <= unit->kindParams->perilHP) {
                w[id] = 1.5f * w[id];
            }
            if (d->weapon) {
                if (unit->attributeFlags & UNIT_ATTR_INACTIVE) {
                    w[id] = 1;
                }
                switch (d->weapon->itemId) {
                    case ITEM_NULL:
                        break;
                    case ITEM_POWER_PUNCH:
                        if (!BtlUnit_CanActStatus(unit) || BtlUnit_CheckStatus(unit, STATUS_HUGE)) {
                            w[id] = 1;
                        }
                        break;
                    case ITEM_MINI_MR_MINI:
                        if (BtlUnit_CheckStatus(unit, STATUS_TINY)) {
                            w[id] = 1;
                        }
                        break;
                    case ITEM_MR_SOFTENER:
                        if (BtlUnit_CheckStatus(unit, STATUS_DEFENSE_DOWN)) {
                            w[id] = 1;
                        }
                        break;
                    case ITEM_COURAGE_SHELL:
                        if (BtlUnit_CheckStatus(unit, STATUS_DEFENSE_UP)) {
                            w[id] = 1;
                        }
                        break;
                    case ITEM_BOOS_SHEET:
                        if (BtlUnit_CheckStatus(unit, STATUS_INVISIBLE)) {
                            w[id] = 1;
                        }
                        break;
                    case ITEM_VOLT_SHROOM:
                        if (BtlUnit_CheckStatus(unit, STATUS_ELECTRIC)) {
                            w[id] = 1;
                        }
                        break;
                    case ITEM_REPEL_CAPE:
                        if (BtlUnit_CheckStatus(unit, STATUS_DODGY)) {
                            w[id] = 1;
                        }
                        break;
                    case ITEM_RUIN_POWDER:
                        if (BtlUnit_CheckStatus(unit, STATUS_CONFUSE)) {
                            w[id] = 1;
                        }
                        break;
                    case ITEM_TASTY_TONIC:
                        if (!BtlUnit_CheckStatus(unit, STATUS_SLEEP) && !BtlUnit_CheckStatus(unit, STATUS_STOP) && !BtlUnit_CheckStatus(unit, STATUS_DIZZY) && !BtlUnit_CheckStatus(unit, STATUS_POISON) && !BtlUnit_CheckStatus(unit, STATUS_CONFUSE) && !BtlUnit_CheckStatus(unit, STATUS_BURN) && !BtlUnit_CheckStatus(unit, STATUS_FREEZE) && !BtlUnit_CheckStatus(unit, STATUS_TINY) && !BtlUnit_CheckStatus(unit, STATUS_DEFENSE_DOWN) && !BtlUnit_CheckStatus(unit, STATUS_SLOW)) {
                            w[id] = 1;
                        }
                        break;
                    default:
                        if (itemDataTable[d->weapon->itemId].fp_restored) {
                            s32 mx = BtlUnit_GetMaxFp(unit);
                            if (BtlUnit_GetFp(unit) < mx) {
                                mx = BtlUnit_GetMaxFp(unit);
                                w[id] = w[id] * (1.0f + 0.1f * (mx - BtlUnit_GetFp(unit)));
                            } else if (!itemDataTable[d->weapon->itemId].hp_restored && !itemDataTable[d->weapon->itemId].sp_restored) {
                                w[id] = 1;
                            }
                        }
                        break;
                }
            }
        }
        if (!(flags & TARGET_WEIGHT_RANDOM)) {
            s32 best = 0;
            s32 bestVal = 0;
            for (i = 0; i < 74; i++) {
                if (w[i] > bestVal) {
                    best = i;
                    bestVal = w[i];
                }
            }
            *unitOut = d->targets[best].unitIdx;
            *partOut = d->targets[best].partIdx;
        } else {
            s32 sum = 0;
            s32 r;
            s32 pick;
            for (i = 0; i < 74; i++) {
                sum += w[i];
            }
            r = irand(sum);
            pick = 0;
            for (i = 0; i < 74; i++) {
                r -= w[i];
                if (r <= 0) {
                    break;
                }
                pick++;
            }
            *unitOut = d->targets[pick].unitIdx;
            *partOut = d->targets[pick].partIdx;
        }
    }
}

/**
 * Picks the attacker and victim of a First Strike from fbatInfo->partyId:
 * 1-6 Mario strikes first, 7-8 his partner, 9 (and anything else) the first enemy strikes Mario.
 * Called by battle_seq when the battle opens.
 */
void BattleGetFirstAttackUnit(BattleWork* wp, BattleUnit** a, BattleUnit** b) {
    BattleUnit* found;
    BattleUnit* other;
    BattleUnit* tmp;
    s32 i;
    for (i = 0; i < BATTLE_UNIT_MAX; i++) {
        found = BattleGetUnitPtr(wp, i);
        if (found && found->alliance == 1) {
            break;
        }
    }
    switch (wp->fbatInfo->partyId) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            tmp = BattleGetMarioPtr(wp);
            other = found;
            found = tmp;
            break;
        case 7:
        case 8:
            tmp = BattleGetPartnerPtr(wp, BattleGetMarioPtr(wp));
            other = found;
            found = tmp;
            break;
        case 9:
        default:
            other = BattleGetMarioPtr(wp);
            break;
    }
    *a = found;
    *b = other;
}
