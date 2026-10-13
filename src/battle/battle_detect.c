#pragma optimize_for_size on
#include "battle/battle.h"
#include "battle/battle_monosiri.h"
#include "battle/battle_unit.h"
#include "data/item_data.h"
#include "system.h"

extern ItemData itemDataTable[];

BOOL BtlUnit_CanActStatus(BattleUnit* unit);
s32 BtlCompForwardLv(s32 dir, f32 x);

#pragma inline_max_size(10000)
#pragma inline_max_total_size(100000)

typedef struct DetTarget {
    s16 unitIdx;   // 0x0
    s16 partIdx;   // 0x2
    s16 posX;      // 0x4
    s16 posY;      // 0x6
    s16 posZ;      // 0x8
    s16 pad_0xA;   // 0xA
    s32 x;         // 0xC
    s32 y;         // 0x10
    s32 z;         // 0x14
    s32 score;     // 0x18
    u8 forwardLv;  // 0x1C
    s8 side;       // 0x1D
    u8 pad_0x1E[2];
    s32 field_0x20; // 0x20
} DetTarget;

typedef struct DetWork {
    BattleWeapon* weapon; // 0x0
    DetTarget t[74];      // 0x4
    s8 numTargets;        // 0xA6C
    s8 idx[74];           // 0xA6D
    s8 curTarget;         // 0xAB7
    s32 unitId;           // 0xAB8
    s8 belong;            // 0xABC
    u32 classFlags;       // 0xAC0
    u32 propFlags;        // 0xAC4
    s8 direction;         // 0xAC8
} DetWork;



void _btlSamplingEnemy(DetWork* d) {
    s32 i, j, k;
    s32 n = 0;
    DetTarget* t = d->t;
    BattleWork* wp = _battleWorkPointer;

    if (d->classFlags & 0x80000000) {
        d->numTargets = -1;
        return;
    }
    {
    for (i = 0; i < 64; i++) {
        BattleUnit* unit = BattleGetUnitPtr(wp, i);
        if (unit && !BtlUnit_CheckStatus(unit, 0x1B) && !(unit->mAttributeFlags & 0x40)) {
            BattleUnitPart* part = unit->mParts;
            u8 np = unit->mKindParams->numParts;
            for (j = 0; j < np; j++) {
                BattleUnitKindPart* kp;
                s32 dir;
                f32 x, y, z;
                f32 ox, oy, oz;
                if (part->attributes & 0x10000) {
                    part = part->mNextPart;
                    continue;
                }
                kp = part->mKindPartParams;
                dir = part->faceDirection;
                BtlUnit_GetPartsWorldPos(part, &x, &y, &z);
                if (!(unit->mAttributeFlags & 2)) {
                    y += part->mPositionOffset.y * unit->mSizeMultiplier;
                }
                ox = x;
                oy = y;
                oz = 5.0f + z;
                x += dir * (unit->mSizeMultiplier * (part->mHitCursorBaseOffset.x + part->mHitCursorOffset.x));
                y += unit->mSizeMultiplier * (part->mHitCursorBaseOffset.y + part->mHitCursorOffset.y);
                z += unit->mSizeMultiplier * (part->mHitCursorBaseOffset.z + part->mHitCursorOffset.z);
                t->unitIdx = i;
                t->partIdx = kp->partNum;
                t->posX = x;
                t->posY = y;
                t->posZ = z;
                t->score = 0;
                t->field_0x20 = -1;
                if ((unit->mAttributeFlags & 1) && !(part->attributes & 0x20000)) {
                    t->score += d->direction * 300;
                }
                t->score += part->field_0x1A0 * dir;
                t->x = (s16)(ox + t->score);
                t->y = (s16)oy;
                t->z = (s16)oz;
                t->forwardLv = BtlCompForwardLv(d->direction, t->x);
                if (t->z < -30) {
                    t->side = 0;
                } else {
                    t->side = 1;
                }
                part = part->mNextPart;
                n++;
                t++;
            }
        }
    }
    }
    {
    d->curTarget = i = 0;
    d->numTargets = n;
    n = d->numTargets;
    t = d->t;
        for (; n > i; i++) {
            DetTarget* tg = &t[i];
            BattleUnit* unit = BattleGetUnitPtr(wp, tg->unitIdx);
            BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, tg->partIdx);
            {
        BOOL ok;
        do {
            u32 flags = d->classFlags;
            if (flags & 0x80000000) {
                { ok = FALSE; break; }
            }
            if (flags & 0x10000) {
                if (unit->currentKind != 0xDE) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 0x20000) {
                if (unit->currentKind < 0xD8 || unit->currentKind >= 0xDA) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 1) {
                if (unit->currentKind == 0xDE || unit->currentKind == 0xDF) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 2) {
                if (unit->currentKind >= 0xE0 && unit->currentKind < 0xE7) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 0x10) {
                if (unit->currentKind >= 1 && unit->currentKind < 0xD8) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 0x40) {
                if (unit->currentKind >= 0xDA && unit->currentKind < 0xDE) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 0x20) {
                if (unit->currentKind >= 0xD8 && unit->currentKind < 0xDA) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 0x1000) {
                if (d->unitId == unit->unitId) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 0x100) {
                if (d->belong == unit->mAlliance) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 0x200) {
                if (d->belong != unit->mAlliance && unit->mAlliance != 2) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 0x2000) {
                if (d->unitId != unit->unitId && unit->currentKind == BattleGetUnitPtr(wp, d->unitId)->currentKind) {
                    { ok = FALSE; break; }
                }
            }
            flags = d->classFlags;
            if (flags & 0x4000) {
                if (d->unitId != unit->unitId) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 0x100000) {
                u32 a = part->attributes;
                if (!((a & 1) || (a & 2)) || (a & 0x40000)) {
                    { ok = FALSE; break; }
                }
            }
            if (flags & 0x200000) {
                u32 a = part->attributes;
                if (!((a & 1) || (a & 2) || (a & 4)) || (a & 0x40000)) {
                    { ok = FALSE; break; }
                }
            }
            ok = TRUE;
        } while (0);
        if (!ok) {
                for (k = i; k < n - 1; k++) {
                    d->t[k] = d->t[k + 1];
                }
                n--;
                i--;
            }
        }
        }
    }

    {
        for (i = 0; n > i; i++) {
            DetTarget* tg = &t[i];
            BattleUnit* unit = BattleGetUnitPtr(wp, tg->unitIdx);
            BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, tg->partIdx);
            {
        BOOL ok;
        do {
                        if (d->propFlags & 1) {
                if (part->attributes & 0x80000) {
                    { ok = FALSE; break; }
                }
                if (!battleGetUnitMonosiriPtr(unit->currentKind)) {
                    { ok = FALSE; break; }
                }
                if (!battleGetUnitMonosiriPtr(unit->currentKind)->tattleBtlTag) {
                    { ok = FALSE; break; }
                }
            }
            if (d->propFlags & 2) {
                if (unit->mAttributeFlags & 4) {
                    { ok = FALSE; break; }
                }
            }
            if (d->propFlags & 4) {
                if (unit->mAttributeFlags & 2) {
                    { ok = FALSE; break; }
                }
            }
            if (d->propFlags & 8) {
                if (unit->mAttributeFlags & 4) {
                    { ok = FALSE; break; }
                }
            }
            if (d->propFlags & 0x10) {
                u32 a = unit->mAttributeFlags;
                if (!(a & 4) && !(a & 2)) {
                    { ok = FALSE; break; }
                }
            }
            if (d->propFlags & 0x1000) {
                if (part->attributes & 0x100000) {
                    { ok = FALSE; break; }
                }
            }
            if (d->propFlags & 0x2000) {
                if (part->attributes & 0x200000) {
                    if (!(d->propFlags & 0x100000) || d->unitId != unit->unitId) {
                        { ok = FALSE; break; }
                    }
                }
            }
            if (d->propFlags & 0x4000) {
                if (part->attributes & 0x400000) {
                    { ok = FALSE; break; }
                }
            }
            if (d->propFlags & 0x8000) {
                if (!(part->attributes & 0x400000)) {
                    { ok = FALSE; break; }
                }
            }
            if (d->propFlags & 0x2000000) {
                if (unit->mAttributeFlags & 0x20) {
                    { ok = FALSE; break; }
                }
            }
            if (d->propFlags & 0x4000000) {
                if (part->attributes & 0x2000000) {
                    { ok = FALSE; break; }
                }
            }
            ok = TRUE;
        } while (0);
        if (!ok) {
                for (k = i; k < n - 1; k++) {
                    d->t[k] = d->t[k + 1];
                }
                n--;
                i--;
            }
        }
        }
    }

    if (d->classFlags & 0x100000) {
        {
            for (i = 0; n > i; i++) {
                DetTarget* tg = &t[i];
                BattleUnitPart* part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(wp, tg->unitIdx), tg->partIdx);
                BOOL keep = TRUE;
                if (part->attributes & 2) {
                    for (j = 0; j < n; j++) {
                        DetTarget* o = &t[j];
                        if (tg != o && tg->unitIdx == o->unitIdx) {
                            if (BtlUnit_GetPartsPtr(BattleGetUnitPtr(wp, o->unitIdx), o->partIdx)->attributes & 1) {
                                keep = FALSE;
                                break;
                            }
                        }
                    }
                }
                if (!keep) {
                    for (k = i; k < n - 1; k++) {
                        d->t[k] = d->t[k + 1];
                    }
                    n--;
                    i--;
                }
            }
        }
    }

    {
        for (i = 0; n > i; i++) {
            DetTarget* tg = &t[i];
            BattleUnitPart* part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(wp, tg->unitIdx), tg->partIdx);
            BOOL keep;
            if ((d->propFlags & 0x1000000) && !(part->attributes & 0x10)) {
                BOOL ok = TRUE;
                for (j = 0; j < n; j++) {
                    DetTarget* o = &t[j];
                    if (tg != o && tg->side == o->side) {
                        s32 a = tg->x;
                        s32 b = o->x;
                        if (d->direction < 0) {
                            a *= -1;
                            b *= -1;
                        }
                        if (a > b) {
                            u32 pa = BattleGetUnitPartsPtr(o->unitIdx, o->partIdx)->attributes;
                            if (!(pa & 0x10) && !(pa & 0x400000)) {
                                BattleUnit* u1 = BattleGetUnitPtr(wp, d->unitId);
                                BattleUnit* u2 = BattleGetUnitPtr(wp, o->unitIdx);
                                if (!(u1->mTokenFlags & 0x10) || u1 != u2) {
                                    ok = FALSE;
                                    break;
                                }
                            }
                        }
                    }
                }
                if (!ok) { keep = FALSE; goto done; }
            }
            keep = TRUE;
        done:

            if (!keep) {
                for (k = i; k < n - 1; k++) {
                    d->t[k] = d->t[k + 1];
                }
                n--;
                i--;
            }
        }
    }

    d->numTargets = n;
    {
    s8* idx = d->idx;
    t = d->t;
    n = d->numTargets;
    for (i = 0; i < n; i++) {
        idx[i] = i;
    }
    if (d->direction > 0) {
        for (i = 0; i < n - 1; i++) {
            for (j = i + 1; j < n; j++) {
                s8 a = idx[i];
                s8 b = idx[j];
                if (t[a].posX + t[a].score * 10 > t[b].posX + t[b].score * 10) {
                    idx[i] = b;
                    idx[j] = a;
                }
            }
        }
    } else {
        for (i = 0; i < n - 1; i++) {
            for (j = i + 1; j < n; j++) {
                s8 a = idx[i];
                s8 b = idx[j];
                if (t[a].posX + t[a].score * 10 <= t[b].posX + t[b].score * 10) {
                    idx[i] = b;
                    idx[j] = a;
                }
            }
        }
    }
    }
}

void BattleSamplingEnemyUpdate(DetWork* d) {
    _btlSamplingEnemy(d);
}

BOOL BattleSamplingEnemy(DetWork* d, BattleWeapon* weapon, s32 unitId, s8 belong, u32 classFlags, u32 propFlags,
                         s8 direction) {
    BOOL r = FALSE;
    d->weapon = weapon;
    d->unitId = unitId;
    d->belong = belong;
    d->classFlags = classFlags;
    d->propFlags = propFlags;
    d->direction = direction;
    if (BattleGetUnitPtr(_battleWorkPointer, unitId)->mTokenFlags & 0x10) {
        if ((d->classFlags & 0x100) && !(d->classFlags & 0x200)) {
            r = TRUE;
            d->classFlags &= ~0x100;
            d->classFlags |= 0x200;
        } else if (!(d->classFlags & 0x100) && (d->classFlags & 0x200)) {
            r = TRUE;
            d->classFlags |= 0x100;
            d->classFlags &= ~0x200;
        }
    }
    _btlSamplingEnemy(d);
    return r;
}

void BattleChoiceSamplingEnemy(DetWork* d, u32 flags, s32* unitOut, s32* partOut) {
    BattleUnit* unit;
    BattleWork* wp = _battleWorkPointer;
    s32 w[74];
    s32 i;
    BattleUnit* active;

    *unitOut = -1;
    *partOut = 0;
    if (d->numTargets > 0) {
        active = BattleGetUnitPtr(wp, d->unitId);
        i = d->idx[0];
        *unitOut = d->t[i].unitIdx;
        *partOut = d->t[i].partIdx;
        for (i = 0; i < 74; i++) {
            w[i] = 0;
        }
        w[d->idx[0]] += 10;
        for (i = 0; i < d->numTargets; i++) {
            s32 id = d->idx[i];
            unit = BattleGetUnitPtr(wp, d->t[id].unitIdx);
            w[id] += 100;
            if ((flags & 1) && unit->currentKind == 0xDE) {
                w[id] = 1.5f * w[id];
            }
            if ((flags & 2) && unit->currentKind >= 0xE0 && unit->currentKind < 0xE7) {
                w[id] = 1.5f * w[id];
            }
            if ((flags & 4)) {
                f32 t = 0.4f * (d->numTargets - i);
                w[id] *= 0.1f + t;
            }
            if ((flags & 8)) {
                f32 t = 0.4f * i;
                w[id] = (0.5f + t) * w[id];
            }
            if ((flags & 0x10) && active->mAlliance == unit->mAlliance) {
                w[id] = 1.5f * w[id];
            }
            if ((flags & 0x20) && active->mAlliance != unit->mAlliance && unit->mAlliance != 2) {
                w[id] = 1.5f * w[id];
            }
            if ((flags & 0x100)) {
                w[id] = (2.0f - (f32)unit->currentHp / (f32)unit->maxHp) * w[id];
            }
            if ((flags & 0x200)) {
                w[id] = (1.0f + (f32)unit->currentHp / (f32)unit->maxHp) * w[id];
            }
            if ((flags & 0x400)) {
                w[id] = (1.5f - 0.05f * unit->currentHp) * w[id];
            }
            if ((flags & 0x800)) {
                w[id] = (1.0f + 0.05f * unit->currentHp) * w[id];
            }
            if ((flags & 0x1000) && unit->currentHp <= unit->mKindParams->mPerilHP) {
                w[id] = 1.5f * w[id];
            }
            if (d->weapon) {
                if (unit->mAttributeFlags & 0x20000) {
                    w[id] = 1;
                }
                switch (d->weapon->itemId) {
                case 0:
                    break;
                case 0x8E:
                    if (!BtlUnit_CanActStatus(unit) || BtlUnit_CheckStatus(unit, 10)) {
                        w[id] = 1;
                    }
                    break;
                case 0x92:
                    if (BtlUnit_CheckStatus(unit, 0xB)) {
                        w[id] = 1;
                    }
                    break;
                case 0x93:
                    if (BtlUnit_CheckStatus(unit, 0xF)) {
                        w[id] = 1;
                    }
                    break;
                case 0x8F:
                    if (BtlUnit_CheckStatus(unit, 0xE)) {
                        w[id] = 1;
                    }
                    break;
                case 0x86:
                    if (BtlUnit_CheckStatus(unit, 0x12)) {
                        w[id] = 1;
                    }
                    break;
                case 0x87:
                    if (BtlUnit_CheckStatus(unit, 6)) {
                        w[id] = 1;
                    }
                    break;
                case 0x88:
                    if (BtlUnit_CheckStatus(unit, 7)) {
                        w[id] = 1;
                    }
                    break;
                case 0x89:
                    if (BtlUnit_CheckStatus(unit, 5)) {
                        w[id] = 1;
                    }
                    break;
                case 0x99:
                    if (!BtlUnit_CheckStatus(unit, 1) && !BtlUnit_CheckStatus(unit, 2)
                        && !BtlUnit_CheckStatus(unit, 3) && !BtlUnit_CheckStatus(unit, 4)
                        && !BtlUnit_CheckStatus(unit, 5) && !BtlUnit_CheckStatus(unit, 8)
                        && !BtlUnit_CheckStatus(unit, 9) && !BtlUnit_CheckStatus(unit, 0xB)
                        && !BtlUnit_CheckStatus(unit, 0xF) && !BtlUnit_CheckStatus(unit, 0x14)) {
                        w[id] = 1;
                    }
                    break;
                default:
                    if (*(u8*)&itemDataTable[d->weapon->itemId].fp_restored) {
                        s32 mx = BtlUnit_GetMaxFp(unit);
                        if (BtlUnit_GetFp(unit) < mx) {
                            mx = BtlUnit_GetMaxFp(unit);
                            w[id] = w[id] * (1.0f + 0.1f * (mx - BtlUnit_GetFp(unit)));
                        } else if (!*(u8*)&itemDataTable[d->weapon->itemId].hp_restored
                                   && !*(u8*)&itemDataTable[d->weapon->itemId].sp_restored) {
                            w[id] = 1;
                        }
                    }
                    break;
                }
            }
        }
        if (!(flags & 0x80000000)) {
            s32 best = 0;
            s32 bestVal = 0;
            for (i = 0; i < 74; i++) {
                if (w[i] > bestVal) {
                    best = i;
                    bestVal = w[i];
                }
            }
            *unitOut = d->t[best].unitIdx;
            *partOut = d->t[best].partIdx;
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
            *unitOut = d->t[pick].unitIdx;
            *partOut = d->t[pick].partIdx;
        }
    }
}

void BattleGetFirstAttackUnit(BattleWork* wp, BattleUnit** a, BattleUnit** b) {
    BattleUnit* found;
    BattleUnit* other;
    BattleUnit* tmp;
    s32 i;
    for (i = 0; i < 64; i++) {
        found = BattleGetUnitPtr(wp, i);
        if (found && found->mAlliance == 1) {
            break;
        }
    }
    switch (wp->fbatInfo->partyId) {
    case 1: case 2: case 3: case 4: case 5: case 6:
        tmp = BattleGetMarioPtr(wp);
        other = found;
        found = tmp;
        break;
    case 7: case 8:
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
