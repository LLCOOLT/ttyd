// Battle units: creating, spawning, deleting and updating the units and parts that fight in a battle.
#pragma optimize_for_size on
// no automatic inlining in this unit, as in the original (the object differs without it)
#pragma auto_inline off
#include "battle/battle_unit.h"
#include "battle/battle.h"
#include "system.h"
#include <string.h>

#include "battle/battle_disp.h"
#include "mario/mario_pouch.h"
#include "driver/npcdrv.h"
#include "pmario_sound.h"
#include "driver/animdrv.h"
#include "manager/evtmgr.h"
#include "memory.h"
#include "version.h"
#include "battle/battle_status_effect.h"
// FAKE: battle_unit.c calls BtlUnit_snd_se_pos through this prototype (the types it was compiled with) instead of the one in battle/battle_unit.h; same registers, behaviour-identical.
typedef s32 (*BtlUnit_snd_se_posS32PitchFn)(BattleUnit*, const char*, s32, s32, Vec*);

double pow(double, double);
// FAKE: local prototype: BtlActRec_AddPoint takes the points as u8 (battle_actrecord.h: s32); this file was compiled with it and the header prototype changes the code.
void BtlActRec_AddPoint(u8* rec, u8 points);
void BtlActRec_AddCount(u8* rec);

#define PART_POSE_SOUND(part) (&(part)->poseSound)

s32 _enemy_can_use_item_table[] = {
    ITEM_THUNDER_BOLT, ITEM_FIRE_FLOWER, ITEM_POW_BLOCK, ITEM_THUNDER_RAGE, ITEM_SHOOTING_STAR, ITEM_ICE_STORM,
    ITEM_EARTH_QUAKE, ITEM_HP_DRAIN_ITEM, ITEM_SLEEPY_SHEEP, ITEM_STOPWATCH, ITEM_DIZZY_DIAL, ITEM_MINI_MR_MINI,
    ITEM_MR_SOFTENER, ITEM_RUIN_POWDER, ITEM_POWER_PUNCH, ITEM_COURAGE_SHELL, ITEM_BOOS_SHEET, ITEM_VOLT_SHROOM,
    ITEM_REPEL_CAPE, ITEM_MUSHROOM, ITEM_SUPER_SHROOM, ITEM_ULTRA_SHROOM, ITEM_LIFE_SHROOM, ITEM_DRIED_SHROOM,
    ITEM_TASTY_TONIC, ITEM_HONEY_SYRUP, ITEM_MAPLE_SYRUP, ITEM_JAMMIN_JELLY, ITEM_SLOW_SHROOM, ITEM_GRADUAL_SYRUP,
    ITEM_HOT_DOG, ITEM_CAKE, 0,
};

// local prototypes
void _CheckMoveCount(BattleUnit* unit);

BOOL BtlUnit_Init(void) {
    int i;
    BattleWork* wp = _battleWorkPointer;

    for (i = 0; i < 64; i++) {
        BattleSetUnitPtr(wp, i, NULL);
    }
    return TRUE;
}

void BtlUnit_HpGaugeInit(BattleUnit* unit);

BattleUnit* BtlUnit_Entry(BattleUnitSetup* setup) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    BattleUnitPart* part;
    BattleUnitKindPart* kpart;
    s32 n;
    s32 i;
    BattleUnitPart* body;
    EventEntry* evt;

    for (i = 0; i < BATTLE_UNIT_MAX; i++) {
        if (!BattleGetUnitPtr(wp, i))
            break;
    }
    if (i >= 64)
        return NULL;

    unit = (BattleUnit*)BattleAlloc(sizeof(BattleUnit));
    if (!unit)
        return NULL;

    memset(unit, 0, sizeof(BattleUnit));
    BattleSetUnitPtr(wp, i, unit);
    unit->unitId = i;
    unit->kindParams = setup->unitKindParams;
    unit->dataTable = unit->kindParams->dataTable;
    unit->initialKind = setup->unitKindParams->unitType;
    unit->currentKind = setup->unitKindParams->unitType;
    BattleStatusEffectInit(unit);
    BattleStatusIconInit(unit);
    BattleStatusChangeInfoWorkInit(unit);
    unit->groupSetupId = -1;
    unit->alliance = setup->alliance;
    unit->level = unit->kindParams->level;
    if (unit->currentKind == UNIT_MARIO || (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX)) {
        unit->level = pouchGetPtr()->level;
    }
    unit->attackPhase = setup->attackPhase;
    unit->unisonPhaseEventCode = NULL;
    unit->phaseEventCode = NULL;
    unit->phaseEventId = 0;
    unit->waitEventCode = NULL;
    unit->waitEventId = 0;
    unit->attackEventCode = NULL;
    unit->attackEventId = 0;
    BtlUnit_SetPos(unit, setup->position.x, setup->position.y, setup->position.z);
    BtlUnit_SetOffsetPos(unit, setup->position.x, setup->position.y, setup->position.z);
    BtlUnit_SetHomePos(unit, setup->position.x, setup->position.y, setup->position.z);
    BtlUnit_SetBaseRotate(unit, 0.0f, 0.0f, 0.0f);
    BtlUnit_SetRotate(unit, 0.0f, 0.0f, 0.0f);
    BtlUnit_SetRotateOffset(unit, 0.0f, 0.0f, 0.0f);
    BtlUnit_SetScale(unit, 1.0f, 1.0f, 1.0f);
    BtlUnit_SetBaseScale(unit, 1.0f, 1.0f, 1.0f);
    unit->offsetCenter = unit->kindParams->centerOffset;
    unit->heldItemBaseOffset = unit->kindParams->heldItemBaseOffset;
    unit->bintaHitOffset = unit->kindParams->bintaHitOffset;
    unit->kissHitOffset = unit->kindParams->kissHitOffset;
    unit->baseMaxHp = setup->unitKindParams->maxHp;
    unit->maxHp = unit->baseMaxHp;
    unit->currentHp = setup->unitKindParams->maxHp;
    unit->baseMaxFp = setup->unitKindParams->maxFp;
    unit->maxFp = unit->baseMaxFp;
    unit->currentFp = setup->unitKindParams->maxFp;
    unit->sizeMultiplier = 1.0f;
    unit->tokenFlags = 0;
    unit->statusFlags = 0;
    unit->protectId = -1;
    BtlUnit_HpGaugeInit(unit);
    unit->width = unit->kindParams->width;
    unit->height = unit->kindParams->height;
    unit->statusIconOffset[0] = unit->kindParams->hitOffset[0];
    unit->statusIconOffset[1] = unit->kindParams->hitOffset[1];
    unit->hpGaugeOffset[0] = unit->kindParams->hpGaugeOffset[0];
    unit->hpGaugeOffset[1] = unit->kindParams->hpGaugeOffset[1];
    unit->cutBaseOffset = unit->kindParams->cutBaseOffset;
    unit->cutWidth = unit->kindParams->cutWidth;
    unit->cutHeight = unit->kindParams->cutHeight;
    unit->swallowRate = unit->kindParams->swallowChance;
    unit->swallowAttribute = unit->kindParams->swallowAttributes;
    BtlUnit_ClearStatus(unit);
    unit->attributeFlags = unit->kindParams->attributeFlags;
    unit->vulnStatus = (BattleVulnerableStatus*)unit->kindParams->statusVulnerability;
    unit->maxMoveCount = 1;
    unit->movesRemaining = 1;
    unit->moveDirection = 0;
    unit->faceDirection = wp->alliances[unit->alliance].attackDirection;
    unit->work[0] = setup->unitWork[0];
    unit->work[1] = setup->unitWork[1];
    unit->work[2] = setup->unitWork[2];
    unit->work[3] = setup->unitWork[3];

    n = (u8)unit->kindParams->numParts;
    part = (BattleUnitPart*)BattleAlloc(n * sizeof(BattleUnitPart));
    memset(part, 0, n * sizeof(BattleUnitPart));
    unit->parts = part;
    kpart = unit->kindParams->parts;
    while (TRUE) {
        part->kindPartParams = kpart;
        part->owner = unit;
        part->attributes = part->kindPartParams->attributes;
        part->counterAttributes = part->kindPartParams->counterAttributes;
        if (part->attributes & PART_ATTR_MAIN) {
            unit->talkPartId = part->kindPartParams->partNum;
        }
        part->defense = part->kindPartParams->defense;
        part->defenseAttr = part->kindPartParams->defenseAttr;
        part->shadowSize = part->kindPartParams->shadowSize;
        part->hitHeight = part->kindPartParams->hitHeight;
        part->shadowScale = 1.0f;
        part->moveDirection = 0;
        part->faceDirection = wp->alliances[unit->alliance].attackDirection;
        part->positionOffset.x = part->kindPartParams->positionOffset.x;
        part->positionOffset.y = part->kindPartParams->positionOffset.y;
        part->positionOffset.z = part->kindPartParams->positionOffset.z;
        BtlUnit_SetPartsBaseScale(part, 1.0f, 1.0f, 1.0f);
        BtlUnit_SetPartsScale(part, 1.0f, 1.0f, 1.0f);
        BtlUnit_SetPartsBaseRotate(part, 0.0f, 0.0f, 0.0f);
        BtlUnit_SetPartsRotate(part, 0.0f, 0.0f, 0.0f);
        BtlUnit_SetPartsRotateOffset(part, 0.0f, 0.0f, 0.0f);
        part->rotationOrder = 0;
        part->hitBaseOffset.x = part->kindPartParams->hitBaseOffset.x;
        part->hitBaseOffset.y = part->kindPartParams->hitBaseOffset.y;
        part->hitBaseOffset.z = part->kindPartParams->hitBaseOffset.z;
        part->hitOffset.x = 0.0f;
        part->hitOffset.y = 0.0f;
        part->hitOffset.z = 0.0f;
        part->hitCursorBaseOffset.x = part->kindPartParams->hitCursorBaseOffset.x;
        part->hitCursorBaseOffset.y = part->kindPartParams->hitCursorBaseOffset.y;
        part->hitCursorBaseOffset.z = part->kindPartParams->hitCursorBaseOffset.z;
        part->hitCursorOffset.x = 0.0f;
        part->hitCursorOffset.y = 0.0f;
        part->hitCursorOffset.z = 0.0f;
        part->color = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
        part->hitOffsetX = setup->hitOffsetX;
        part->poseTable = kpart->poseTable;
        part->poseId = -1;
        part->poseName[0] = 0;
        part->animSpeed = 1.0f;
        part->animSpeed2 = 1.0f;
        part->poseType = 0;
        part->poseState = 0;
        part->handle = -1;
        part->partName = part->kindPartParams->partName;
        if (--n <= 0)
            break;
        body = part;
        part++;
        body->nextPart = part;
        kpart++;
    }
    part->nextPart = NULL;

    body = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
    unit->talkPose = BtlUnit_GetPoseNameFromType(body, BTL_POSE_TALK);
    unit->stayPose = BtlUnit_GetPoseNameFromType(body, BTL_POSE_STAY);
    unit->moveColorLv = 0xFF;
    unit->moveColorLvDisp = 0xFF;
    btlDispEntAnime(unit);
    unit->countersetWeapon = NULL;
    unit->deleteFunc = NULL;
    switch (unit->currentKind) {
        case 0xD0:
            unit->countersetWeapon = BattleAlloc(0x44);
            break;
        case 0xDE:
            break;
    }
    BtlUnit_SetParamFromPouch(unit);
    unit->initEventId = 0;
    if (unit->kindParams->initEventCode) {
        evt = evtEntry(unit->kindParams->initEventCode, 10, 0);
        evt->unitId = unit->unitId;
        unit->initEventId = evt->eventId;
    }
    return unit;
}

BOOL BtlUnit_Delete(BattleUnit* unit) {
    BattleWork* wp = _battleWorkPointer;
    s32 i;
    BattleUnitPart* part;
    s32 j;
    s32 id;

    if (!unit)
        return FALSE;
    for (i = 0; i < BATTLE_UNIT_MAX; i++) {
        if (BattleGetUnitPtr(wp, i) == unit)
            break;
    }
    if (i >= 64)
        return FALSE;

    if (unit->waitEventId) {
        evtDeleteID(unit->waitEventId);
        unit->waitEventId = 0;
    }
    if (unit->phaseEventId) {
        evtDeleteID(unit->phaseEventId);
        unit->phaseEventId = 0;
    }
    if (unit->damageEventId) {
        evtDeleteID(unit->damageEventId);
        unit->damageEventId = 0;
    }
    id = unit->unitId;
    for (j = 0; j < BATTLE_UNIT_MAX; j++) {
        if (wp->movePriorityQueue[j] == id) {
            wp->movePriorityQueue[j] = -1;
        }
    }
    if (unit->flags & UNIT_FLAG_HOLDING_STOLEN_ITEM) {
        NpcBattleInfo* info = wp->fbatInfo->setup;
        if (unit->groupSetupId >= 0) {
            info->stolenItems[unit->groupSetupId] = unit->heldItem;
        }
    }
    BattleStatusEffectDelete(unit);
    BattleStatusIconDelete(unit);
    if (unit->countersetWeapon) {
        if (unit->deleteFunc) {
            unit->deleteFunc(unit);
        } else {
            BattleFree(unit->countersetWeapon);
        }
    }
    if ((void*)unit->screenTexBuf) {
        smartFree(unit->screenTexBuf);
        unit->screenTexBuf = NULL;
    }
    for (part = unit->parts; part; part = part->nextPart) {
        if (part->handle != -1) {
            part->handle = -1;
        }
        if (part->poseId != -1) {
            animPoseSetEffect(part->poseId, NULL, 0);
            animPoseRelease(part->poseId);
        }
    }
    BattleFree(unit->parts);
    BattleFree(unit);
    BattleSetUnitPtr(wp, i, NULL);
    return TRUE;
}

BattleUnit* BtlUnit_Spawn(BattleUnitSetup* setup, s32 flags) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 i;
    s32 id;
    s32 tmp;

    unit = BtlUnit_Entry(setup);
    if (!unit)
        return unit;
    if (flags & 2) {
        unit->moveState = 0;
        id = unit->unitId;
        for (i = 0; i < BATTLE_UNIT_MAX; i++) {
            if (id == -1)
                break;
            if (wp->movePriorityQueue[i] == -1) {
                wp->movePriorityQueue[i] = id;
                break;
            }
            tmp = wp->movePriorityQueue[i];
            wp->movePriorityQueue[i] = id;
            id = tmp;
        }
    } else if (flags & 1) {
        unit->moveState = 0;
        id = unit->unitId;
        for (i = 63; i >= 0; i--) {
            if (id == -1)
                break;
            if (wp->movePriorityQueue[i] == -1) {
                wp->movePriorityQueue[i] = id;
                break;
            }
            tmp = wp->movePriorityQueue[i];
            wp->movePriorityQueue[i] = id;
            id = tmp;
        }
    }
    return unit;
}

s32 BtlUnit_GetUnitId(BattleUnit* unit) {
    return unit->unitId;
}

BattleUnitPart* BtlUnit_GetPartsPtr(BattleUnit* unit, s32 partNum) {
    BattleUnitPart* part = unit->parts;

    if (partNum < 0) {
        return part;
    }
    if (!part->nextPart) {
        return part;
    }
    for (; part; part = part->nextPart) {
        if (part->kindPartParams->partNum == partNum) {
            return part;
        }
    }
    return part;
}

s32 BtlUnit_GetBodyPartsId(BattleUnit* unit) {
    BattleUnitPart* part;
    s32 ret = -1;

    if (unit) {
        for (part = unit->parts; part; part = part->nextPart) {
            if (part->attributes & PART_ATTR_MAIN) {
                ret = part->kindPartParams->partNum;
                break;
            }
        }
    }
    return ret;
}

void BtlUnit_GetPos(BattleUnit* unit, f32* x, f32* y, f32* z) {
    *x = unit->position.x;
    *y = unit->position.y;
    *z = unit->position.z;
}

void BtlUnit_SetPos(BattleUnit* unit, f32 x, f32 y, f32 z) {
    unit->position.x = x;
    unit->position.y = y;
    unit->position.z = z;
}

void BtlUnit_AddPos(BattleUnit* unit, f32 x, f32 y, f32 z) {
    unit->position.x += x;
    unit->position.y += y;
    unit->position.z += z;
}

void BtlUnit_GetPartsPos(BattleUnitPart* part, f32* x, f32* y, f32* z) {
    *x = part->position.x;
    *y = part->position.y;
    *z = part->position.z;
}

void BtlUnit_SetPartsPos(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    part->position.x = x;
    part->position.y = y;
    part->position.z = z;
}

void BtlUnit_AddPartsPos(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    part->position.x += x;
    part->position.y += y;
    part->position.z += z;
}

void BtlUnit_GetPartsWorldPos(BattleUnitPart* part, f32* x, f32* y, f32* z) {
    BattleUnit* unit = part->owner;
    f32 ux, ox, uy, oy, uz, oz;

    if (part->attributes & PART_ATTR_WORLD_POSITION) {
        *x = part->position.x;
        *y = part->position.y;
        *z = part->position.z;
    } else {
        BtlUnit_GetPos(unit, &ux, &uy, &uz);
        BtlUnit_GetPartsOffsetPos(part, &ox, &oy, &oz);
        *x = ox * unit->faceDirection + ux;
        *y = uy + oy;
        *z = uz + oz;
    }
}

void BtlUnit_GetHitPos(BattleUnit* unit, BattleUnitPart* part, f32* x, f32* y, f32* z) {
    f32 y_multiply = 1.0f;
    s32 direction = _battleWorkPointer->alliances[unit->alliance].attackDirection;
    BtlUnit_GetPartsWorldPos(part, x, y, z);
    // add hit base offset
    *x = ((f32)direction * (part->hitBaseOffset.x * unit->sizeMultiplier)) + *x;
    *y = (y_multiply * (part->hitBaseOffset.y * unit->sizeMultiplier)) + *y;
    *z = (part->hitBaseOffset.z * unit->sizeMultiplier) + *z;
    // add hit offset
    *x = ((f32)direction * (part->hitOffset.x * unit->sizeMultiplier)) + *x;
    *y = (y_multiply * (part->hitOffset.y * unit->sizeMultiplier)) + *y;
    *z = (part->hitOffset.z * unit->sizeMultiplier) + *z;
}

void BtlUnit_SetHitOffset(BattleUnit* unit, BattleUnitPart* part, f32 x, f32 y, f32 z) {
    part->hitOffset.x = x;
    part->hitOffset.y = y;
    part->hitOffset.z = z;
}

void BtlUnit_SetHitCursorOffset(BattleUnit* unit, BattleUnitPart* part, f32 x, f32 y, f32 z) {
    part->hitCursorOffset.x = x;
    part->hitCursorOffset.y = y;
    part->hitCursorOffset.z = z;
}

void BtlUnit_GetHomePos(BattleUnit* unit, f32* x, f32* y, f32* z) {
    *x = unit->homePosition.x;
    *y = unit->homePosition.y;
    *z = unit->homePosition.z;
}

void BtlUnit_SetHomePos(BattleUnit* unit, f32 x, f32 y, f32 z) {
    unit->homePosition.x = x;
    unit->homePosition.y = y;
    unit->homePosition.z = z;
}

void BtlUnit_AddHomePos(BattleUnit* unit, f32 x, f32 y, f32 z) {
    unit->homePosition.x += x;
    unit->homePosition.y += y;
    unit->homePosition.z += z;
}

void BtlUnit_SetPartsHomePos(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    part->homePosition.x = x;
    part->homePosition.y = y;
    part->homePosition.z = z;
}

void BtlUnit_SetRotate(BattleUnit* unit, f32 x, f32 y, f32 z) {
    f32 new_x, new_y, new_z;

    new_x = reviseAngle(x);
    if (new_x >= 360.0f) {
        new_x = 0.0f;
    }
    unit->rotation.x = new_x;

    new_y = reviseAngle(y);
    if (new_y >= 360.0f) {
        new_y = 0.0f;
    }
    unit->rotation.y = new_y;

    new_z = reviseAngle(z);
    if (new_z >= 360.0f) {
        new_z = 0.0f;
    }
    unit->rotation.z = new_z;
}

void BtlUnit_GetRotate(BattleUnit* unit, f32* x, f32* y, f32* z) {
    *x = unit->rotation.x;
    *y = unit->rotation.y;
    *z = unit->rotation.z;
}

void BtlUnit_AddRotate(BattleUnit* unit, f32 x, f32 y, f32 z) {
    unit->rotation.x = reviseAngle(unit->rotation.x + x);
    if (unit->rotation.x >= 360.0f) {
        unit->rotation.x = 0.0f;
    }
    unit->rotation.y = reviseAngle(unit->rotation.y + y);
    if (unit->rotation.y >= 360.0f) {
        unit->rotation.y = 0.0f;
    }
    unit->rotation.z = reviseAngle(unit->rotation.z + z);
    if (unit->rotation.z >= 360.0f) {
        unit->rotation.z = 0.0f;
    }
}

void BtlUnit_SetPartsRotate(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    part->rotation.x = x;
    part->rotation.y = y;
    part->rotation.z = z;
}

void BtlUnit_GetPartsRotate(BattleUnitPart* part, f32* x, f32* y, f32* z) {
    *x = part->rotation.x;
    *y = part->rotation.y;
    *z = part->rotation.z;
}

void BtlUnit_AddPartsRotate(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    part->rotation.x += x;
    if (part->rotation.x > 360.0f) {
        part->rotation.x -= 360.0f;
    } else if (part->rotation.x < 0.0f) {
        part->rotation.x += 360.0f;
    }

    part->rotation.y += y;
    if (part->rotation.y > 360.0f) {
        part->rotation.y -= 360.0f;
    } else if (part->rotation.y < 0.0f) {
        part->rotation.y += 360.0f;
    }

    part->rotation.z += z;
    if (part->rotation.z > 360.0f) {
        part->rotation.z -= 360.0f;
    } else if (part->rotation.z < 0.0f) {
        part->rotation.z += 360.0f;
    }
}

void BtlUnit_SetBaseRotate(BattleUnit* unit, f32 x, f32 y, f32 z) {
    unit->baseRotation.x = reviseAngle(x);
    unit->baseRotation.y = reviseAngle(y);
    unit->baseRotation.z = reviseAngle(z);
}

void BtlUnit_GetBaseRotate(BattleUnit* unit, f32* x, f32* y, f32* z) {
    *x = unit->baseRotation.x;
    *y = unit->baseRotation.y;
    *z = unit->baseRotation.z;
}

void BtlUnit_SetPartsBaseRotate(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    part->baseRotation.x = x;
    part->baseRotation.y = y;
    part->baseRotation.z = z;
}

void BtlUnit_GetPartsBaseRotate(BattleUnitPart* part, f32* x, f32* y, f32* z) {
    *x = part->baseRotation.x;
    *y = part->baseRotation.y;
    *z = part->baseRotation.z;
}

void BtlUnit_SetRotateOffset(BattleUnit* unit, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        unit->rotationOffset.x = x;
    }
    if (thefuckyone != y) {
        unit->rotationOffset.y = y;
    }
    if (thefuckyone != z) {
        unit->rotationOffset.z = z;
    }
}

void BtlUnit_SetPartsRotateOffset(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        part->rotationOffset.x = x;
    }
    if (thefuckyone != y) {
        part->rotationOffset.y = y;
    }
    if (thefuckyone != z) {
        part->rotationOffset.z = z;
    }
}

void BtlUnit_AddPartsRotateOffset(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    part->rotationOffset.x += x;
    part->rotationOffset.y += y;
    part->rotationOffset.z += z;
}

void BtlUnit_SetBaseScale(BattleUnit* unit, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        unit->baseScale.x = x;
    }
    if (thefuckyone != y) {
        unit->baseScale.y = y;
    }
    if (thefuckyone != z) {
        unit->baseScale.z = z;
    }
}

void BtlUnit_GetScale(BattleUnit* unit, f32* x, f32* y, f32* z) {
    *x = unit->scale.x;
    *y = unit->scale.y;
    *z = unit->scale.z;
}

void BtlUnit_SetScale(BattleUnit* unit, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        unit->scale.x = x;
    }
    if (thefuckyone != y) {
        unit->scale.y = y;
    }
    if (thefuckyone != z) {
        unit->scale.z = z;
    }
}

void BtlUnit_AddScale(BattleUnit* unit, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        unit->scale.x += x;
    }
    if (thefuckyone != y) {
        unit->scale.y += y;
    }
    if (thefuckyone != z) {
        unit->scale.z += z;
    }
}

void BtlUnit_SetPartsBaseScale(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        part->baseScale.x = x;
    }
    if (thefuckyone != y) {
        part->baseScale.y = y;
    }
    if (thefuckyone != z) {
        part->baseScale.z = z;
    }
}

void BtlUnit_SetPartsScale(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        part->scale.x = x;
    }
    if (thefuckyone != y) {
        part->scale.y = y;
    }
    if (thefuckyone != z) {
        part->scale.z = z;
    }
}

void BtlUnit_AddPartsScale(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        part->scale.x += x;
    }
    if (thefuckyone != y) {
        part->scale.y += y;
    }
    if (thefuckyone != z) {
        part->scale.z += z;
    }
}

s32 BtlUnit_GetWidth(BattleUnit* unit) {
    return unit->width;
}

s32 BtlUnit_GetHeight(BattleUnit* unit) {
    return unit->height;
}

void BtlUnit_SetHeight(BattleUnit* unit, s16 height) {
    unit->height = height;
}

void BtlUnit_SetOffsetPos(BattleUnit* unit, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        unit->positionOffset.x = x;
    }
    if (thefuckyone != y) {
        unit->positionOffset.y = y;
    }
    if (thefuckyone != z) {
        unit->positionOffset.z = z;
    }
}

void BtlUnit_GetPartsOffsetPos(BattleUnitPart* part, f32* x, f32* y, f32* z) {
    *x = part->positionOffset.x;
    *y = part->positionOffset.y;
    *z = part->positionOffset.z;
}

void BtlUnit_SetPartsOffsetPos(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        part->positionOffset.x = x;
    }
    if (thefuckyone != y) {
        part->positionOffset.y = y;
    }
    if (thefuckyone != z) {
        part->positionOffset.z = z;
    }
}

void BtlUnit_AddPartsOffsetPos(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    part->positionOffset.x += x;
    part->positionOffset.y += y;
    part->positionOffset.z += z;
}

void BtlUnit_SetDispOffset(BattleUnit* unit, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        unit->displayOffset.x = x;
    }
    if (thefuckyone != y) {
        unit->displayOffset.y = y;
    }
    if (thefuckyone != z) {
        unit->displayOffset.z = z;
    }
}

void BtlUnit_SetPartsDispOffset(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        part->displayOffset.x = x;
    }
    if (thefuckyone != y) {
        part->displayOffset.y = y;
    }
    if (thefuckyone != z) {
        part->displayOffset.z = z;
    }
}

void BtlUnit_AddPartsDispOffset(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        part->displayOffset.x += x;
    }
    if (thefuckyone != y) {
        part->displayOffset.y += y;
    }
    if (thefuckyone != z) {
        part->displayOffset.z += z;
    }
}

void BtlUnit_SetMoveStartPos(BattleUnit* unit, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        unit->moveStartPos.x = x;
    }
    if (thefuckyone != y) {
        unit->moveStartPos.y = y;
    }
    if (thefuckyone != z) {
        unit->moveStartPos.z = z;
    }
}

void BtlUnit_SetPartsMoveStartPos(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        part->moveStartPos.x = x;
    }
    if (thefuckyone != y) {
        part->moveStartPos.y = y;
    }
    if (thefuckyone != z) {
        part->moveStartPos.z = z;
    }
}

void BtlUnit_SetMoveCurrentPos(BattleUnit* unit, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        unit->moveCurrentPos.x = x;
    }
    if (thefuckyone != y) {
        unit->moveCurrentPos.y = y;
    }
    if (thefuckyone != z) {
        unit->moveCurrentPos.z = z;
    }
}

void BtlUnit_SetPartsMoveCurrentPos(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        part->moveCurrentPos.x = x;
    }
    if (thefuckyone != y) {
        part->moveCurrentPos.y = y;
    }
    if (thefuckyone != z) {
        part->moveCurrentPos.z = z;
    }
}

void BtlUnit_SetMoveTargetPos(BattleUnit* unit, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        unit->moveTargetPos.x = x;
    }
    if (thefuckyone != y) {
        unit->moveTargetPos.y = y;
    }
    if (thefuckyone != z) {
        unit->moveTargetPos.z = z;
    }
}

void BtlUnit_SetPartsMoveTargetPos(BattleUnitPart* part, f32 x, f32 y, f32 z) {
    f32 thefuckyone = -250000000.0f;
    if (thefuckyone != x) {
        part->moveTargetPos.x = x;
    }
    if (thefuckyone != y) {
        part->moveTargetPos.y = y;
    }
    if (thefuckyone != z) {
        part->moveTargetPos.z = z;
    }
}

void BtlUnit_SetFallAccel(BattleUnit* unit, f32 fallAccel) {
    unit->fallAccel = fallAccel;
}

void BtlUnit_SetPartsFallAccel(BattleUnitPart* part, f32 fallAccel) {
    part->fallAccel = fallAccel;
}

void BtlUnit_SetMoveSpeed(BattleUnit* unit, f32 moveSpeedXZ) {
    unit->moveSpeedXZ = moveSpeedXZ;
}

void BtlUnit_SetPartsMoveSpeed(BattleUnitPart* part, f32 moveSpeedXZ) {
    part->moveSpeedXZ = moveSpeedXZ;
}

void BtlUnit_SetJumpSpeed(BattleUnit* unit, f32 moveSpeedY) {
    unit->moveSpeedY = moveSpeedY;
}

s8 BtlUnit_GetBelong(BattleUnit* unit) {
    return unit->alliance;
}

void _CheckMoveCount(BattleUnit* unit) {
    s8 maxmoves;

    if (!(unit->tokenFlags & TOKEN_FLAG_CURRENTLY_ACTING)) {
        maxmoves = unit->maxMovesThisTurn;
        if (maxmoves > 0 && maxmoves == unit->movesRemaining) {
            BtlUnit_ResetMoveStatus(unit);
        }
    }
}

void BtlUnit_GetStatus(BattleUnit* unit, StatusEffectType type, s8* turns, s8* strength) {
    s8 status_turns = 0;
    s8 status_strength = 0;

    switch ((s8)type) {
        case STATUS_SLEEP:
            status_strength = unit->sleepTurns;
            status_turns = status_strength;
            break;
        case STATUS_STOP:
            status_strength = unit->stopTurns;
            status_turns = status_strength;
            break;
        case STATUS_DIZZY:
            status_strength = unit->dizzyTurns;
            status_turns = status_strength;
            break;
        case STATUS_POISON:
            status_turns = unit->poisonTurns;
            status_strength = unit->poisonStrength;
            break;
        case STATUS_CONFUSE:
            status_strength = unit->confusionTurns;
            status_turns = status_strength;
            break;
        case STATUS_ELECTRIC:
            status_strength = unit->electricTurns;
            status_turns = status_strength;
            break;
        case STATUS_DODGY:
            status_strength = unit->dodgyTurns;
            status_turns = status_strength;
            break;
        case STATUS_BURN:
            status_strength = unit->burnTurns;
            status_turns = status_strength;
            break;
        case STATUS_FREEZE:
            status_strength = unit->freezeTurns;
            status_turns = status_strength;
            break;
        case STATUS_HUGE:
            if (unit->sizeChangeStrength > 0) {
                status_turns = unit->sizeChangeTurns;
                status_strength = unit->sizeChangeStrength;
            }
            break;
        case STATUS_TINY:
            if (unit->sizeChangeStrength < 0) {
                status_turns = unit->sizeChangeTurns;
                status_strength = unit->sizeChangeStrength;
            }
            break;
        case STATUS_ATTACK_UP:
            if (unit->atkChangeStrength > 0) {
                status_turns = unit->atkChangeTurns;
                status_strength = unit->atkChangeStrength;
            }
            break;
        case STATUS_ATTACK_DOWN:
            if (unit->atkChangeStrength < 0) {
                status_turns = unit->atkChangeTurns;
                status_strength = unit->atkChangeStrength;
            }
            break;
        case STATUS_DEFENSE_UP:
            if (unit->defChangeStrength > 0) {
                status_turns = unit->defChangeTurns;
                status_strength = unit->defChangeStrength;
            }
            break;
        case STATUS_DEFENSE_DOWN:
            if (unit->defChangeStrength < 0) {
                status_turns = unit->defChangeTurns;
                status_strength = unit->defChangeStrength;
            }
            break;
        case STATUS_FAST:
            status_strength = unit->fastTurns;
            status_turns = status_strength;
            break;
        case STATUS_SLOW:
            status_strength = unit->slowTurns;
            status_turns = status_strength;
            break;
        case STATUS_CHARGE:
            status_strength = unit->chargeStrength;
            status_turns = status_strength;
            break;
        case STATUS_ALLERGIC:
            status_strength = unit->allergicTurns;
            status_turns = status_strength;
            break;
        case STATUS_FLIPPED:
            status_strength = unit->flippedTurns;
            status_turns = status_strength;
            break;
        case STATUS_INVISIBLE:
            status_strength = unit->invisibleTurns;
            status_turns = status_strength;
            break;
        case STATUS_PAYBACK:
            status_strength = unit->paybackTurns;
            status_turns = status_strength;
            break;
        case STATUS_HOLD_FAST:
            status_strength = unit->holdFastTurns;
            status_turns = status_strength;
            break;
        case STATUS_HP_REGEN:
            status_turns = unit->hpRegenTurns;
            status_strength = unit->hpRegenStrength;
            break;
        case STATUS_FP_REGEN:
            status_turns = unit->fpRegenTurns;
            status_strength = unit->fpRegenStrength;
            break;
        case STATUS_INSTANT_KILL:
            status_strength = unit->instantKillStrength;
            status_turns = status_strength;
            break;
        default:
            break;
    }
    if (turns) {
        *turns = status_turns;
    }
    if (strength) {
        *strength = status_strength;
    }
}

BOOL BtlUnit_SetStatus(BattleUnit* unit, StatusEffectType type, s8 turns, s8 strength) {
    switch ((s8)type) {
        case STATUS_SLEEP:
            unit->sleepTurns = turns;
            unit->sleepStrength = 0;
            break;
        case STATUS_STOP:
            unit->stopTurns = turns;
            break;
        case STATUS_DIZZY:
            unit->dizzyTurns = turns;
            break;
        case STATUS_POISON:
            unit->poisonTurns = turns;
            unit->poisonStrength = strength;
            break;
        case STATUS_CONFUSE:
            unit->confusionTurns = turns;
            break;
        case STATUS_ELECTRIC:
            unit->electricTurns = turns;
            break;
        case STATUS_DODGY:
            unit->dodgyTurns = turns;
            break;
        case STATUS_BURN:
            if (unit->freezeTurns) {
                unit->freezeTurns = 0;
                return FALSE;
            }
            unit->burnTurns = turns;
            break;
        case STATUS_FREEZE:
            if (unit->burnTurns) {
                unit->burnTurns = 0;
                return FALSE;
            }
            unit->freezeTurns = turns;
            break;
        case STATUS_HUGE:
        case STATUS_TINY:
            if (!strength) {
                if ((s8)type == STATUS_HUGE) {
                    if (unit->sizeChangeStrength >= 0) {
                        unit->sizeChangeTurns = 0;
                        unit->sizeChangeStrength = 0;
                        return FALSE;
                    }
                } else if (unit->sizeChangeStrength <= 0) {
                    unit->sizeChangeTurns = 0;
                    unit->sizeChangeStrength = 0;
                    return FALSE;
                }
                return FALSE;
            }
            unit->sizeChangeTurns = turns;
            unit->sizeChangeStrength = strength;
            break;
        case STATUS_ATTACK_UP:
            if (!strength) {
                if (unit->atkChangeStrength >= 0) {
                    unit->atkChangeTurns = 0;
                    unit->atkChangeStrength = 0;
                }
                return FALSE;
            }
            unit->atkChangeTurns = turns;
            unit->atkChangeStrength = strength;
            break;
        case STATUS_ATTACK_DOWN:
            if (!strength) {
                if (unit->atkChangeStrength <= 0) {
                    unit->atkChangeTurns = 0;
                    unit->atkChangeStrength = 0;
                }
                return FALSE;
            }
            unit->atkChangeTurns = turns;
            unit->atkChangeStrength = strength;
            break;
        case STATUS_DEFENSE_UP:
        case STATUS_DEFENSE_DOWN:
            if (strength > 0) {
                if (unit->defChangeStrength < 0) {
                    unit->defChangeTurns = 0;
                    unit->defChangeStrength = 0;
                    return FALSE;
                }
                unit->defChangeTurns = turns;
                unit->defChangeStrength = strength;
            } else if (strength == 0) {
                if ((s8)type == STATUS_DEFENSE_DOWN) {
                    if (unit->defChangeStrength <= 0) {
                        unit->defChangeTurns = 0;
                        unit->defChangeStrength = 0;
                    }
                } else if (unit->defChangeStrength >= 0) {
                    unit->defChangeTurns = 0;
                    unit->defChangeStrength = 0;
                }
                return FALSE;
            } else {
                if (unit->defChangeStrength > 0) {
                    unit->defChangeTurns = 0;
                    unit->defChangeStrength = 0;
                    return FALSE;
                }
                unit->defChangeTurns = turns;
                unit->defChangeStrength = strength;
            }
            break;
        case STATUS_CHARGE:
            unit->chargeStrength += strength;
#if VERSION <= VERSION_DEMO_US
            if (unit->chargeStrength < 0) {
                unit->chargeStrength = 0;
            } else if (unit->chargeStrength > 99) {
                unit->chargeStrength = 99;
            }
            break;
        case STATUS_ALLERGIC:
            unit->allergicTurns = turns;
            break;
#else
            if (unit->chargeStrength < 0) {
                unit->chargeStrength = 0;
                return FALSE;
            }
            if (unit->chargeStrength > 99) {
                unit->chargeStrength = 99;
            }
            break;
        case STATUS_ALLERGIC:
            if (turns > 0) {
                unit->allergicTurns = turns;
            } else {
                unit->allergicTurns = 0;
                return FALSE;
            }
            break;
#endif
        case STATUS_FLIPPED:
            unit->flippedTurns = turns;
            break;
        case STATUS_INVISIBLE:
            unit->invisibleTurns = turns;
            break;
        case STATUS_PAYBACK:
#if VERSION <= VERSION_DEMO_US
            unit->paybackTurns = turns;
#else
            if (turns > 0) {
                unit->paybackTurns = turns;
            } else {
                unit->paybackTurns = 0;
                return FALSE;
            }
#endif
            break;
        case STATUS_HOLD_FAST:
            unit->holdFastTurns = turns;
            break;
        case STATUS_FAST:
            if (unit->slowTurns > 0) {
                if (turns > 0) {
                    unit->slowTurns = 0;
                    _CheckMoveCount(unit);
                    return FALSE;
                }
                unit->fastTurns = turns;
            } else {
                unit->fastTurns = turns;
            }
            _CheckMoveCount(unit);
            break;
        case STATUS_SLOW:
            if (unit->fastTurns > 0) {
                if (turns > 0) {
                    unit->fastTurns = 0;
                    _CheckMoveCount(unit);
                    return FALSE;
                }
                unit->slowTurns = turns;
            } else {
                unit->slowTurns = turns;
            }
            _CheckMoveCount(unit);
            break;
        case STATUS_HP_REGEN:
            unit->hpRegenTurns = turns;
            unit->hpRegenStrength = strength;
            break;
        case STATUS_FP_REGEN:
            unit->fpRegenTurns = turns;
            unit->fpRegenStrength = strength;
            break;
        case STATUS_INSTANT_KILL:
            unit->instantKillStrength = turns;
            break;
        default:
            break;
    }
    return TRUE;
}

// clears the 0x1E bytes of status turns and strengths from sleepTurns on
void BtlUnit_ClearStatus(BattleUnit* unit) {
    memset(&unit->sleepTurns, 0, 0x1Eu);
    BtlUnit_SetStatus(unit, STATUS_CHARGE, 1, -99);
#if VERSION >= VERSION_JP
    BattleStatusChangeInfoWorkInit(unit);
#endif
}

BOOL BtlUnit_CheckRecoveryStatus(BattleUnit* unit, StatusEffectType type) {
    s8 turns, strength;

    if (!unit) {
        return FALSE;
    }
    if (BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL)) {
        return FALSE;
    }
    if (unit->currentHp <= 0) {
        return FALSE;
    }
    BtlUnit_GetStatus(unit, type, &turns, &strength);
    if (!turns) {
        return FALSE;
    }
    switch ((s8)type) {
        case STATUS_SLEEP:
            if (turns > 1) {
                turns--;
            } else {
                turns = 0;
            }
            unit->sleepTurns = turns;
            if (!turns) {
                return TRUE;
            }
            return FALSE;
        case STATUS_ALLERGIC:
        case STATUS_STOP:
        case STATUS_DIZZY:
        case STATUS_CONFUSE:
        case STATUS_ELECTRIC:
        case STATUS_DODGY:
        case STATUS_BURN:
        case STATUS_FREEZE:
        case STATUS_INVISIBLE:
        case STATUS_FAST:
        case STATUS_SLOW:
        case STATUS_PAYBACK:
        case STATUS_HOLD_FAST:
            if (turns >= 0) {
                turns--;
            } else {
                turns++;
            }
            if (strength >= 0) {
                strength--;
            } else {
                strength++;
            }
            if (!turns) {
                strength = 0;
            }
            BtlUnit_SetStatus(unit, type, turns, strength);
            if (!turns) {
                return TRUE;
            }
            return FALSE;
        case STATUS_HUGE:
        case STATUS_TINY:
            if (turns > 0) {
                turns--;
            } else if (turns < 0) {
                turns++;
            } else {
                return FALSE;
            }
            if (!turns) {
                strength = 0;
            }
            unit->sizeChangeTurns = turns;
            unit->sizeChangeStrength = strength;
            if (!turns) {
                return TRUE;
            }
            return FALSE;
        case STATUS_ATTACK_UP:
        case STATUS_ATTACK_DOWN:
            if (turns > 0) {
                turns--;
            } else if (turns < 0) {
                turns++;
            } else {
                return FALSE;
            }
            if (!turns) {
                strength = 0;
            }
            unit->atkChangeTurns = turns;
            unit->atkChangeStrength = strength;
            if (!turns) {
                return TRUE;
            }
            return FALSE;
        case STATUS_POISON:
        case STATUS_DEFENSE_UP:
        case STATUS_DEFENSE_DOWN:
        case STATUS_HP_REGEN:
        case STATUS_FP_REGEN:
            if (turns >= 0) {
                turns--;
            } else {
                turns++;
            }
            if (!turns) {
                strength = 0;
            }
            BtlUnit_SetStatus(unit, type, turns, strength);
            if (!turns) {
                return TRUE;
            }
            return FALSE;
        default:
            return FALSE;
    }
}

BOOL BtlUnit_CheckStatus(BattleUnit* unit, StatusEffectType type) {
    s8 turns, strength;

    if (!unit) {
        return FALSE;
    }
    BtlUnit_GetStatus(unit, type, &turns, &strength);
    if (turns) {
        return TRUE;
    }
    if ((s8)type == STATUS_ELECTRIC && unit->badgesEquipped.ZapTap) {
        return TRUE;
    }
    return FALSE;
}

s32 BtlUnit_CheckStatusFlag(BattleUnit* unit, s32 flags) {
    if (unit) {
        return unit->statusFlags & flags;
    }
    return 0;
}

void BtlUnit_OnStatusFlag(BattleUnit* unit, s32 flags) {
    unit->statusFlags |= flags;
}

void BtlUnit_OffStatusFlag(BattleUnit* unit, s32 flags) {
    unit->statusFlags &= ~flags;
}

s32 BtlUnit_CheckUnitFlag(BattleUnit* unit, s32 flags) {
    return unit->flags & flags;
}

void BtlUnit_OnUnitFlag(BattleUnit* unit, s32 flags) {
    unit->flags |= flags;
}

void BtlUnit_OffUnitFlag(BattleUnit* unit, s32 flags) {
    unit->flags &= ~flags;
}

const char* BtlUnit_GetPoseNameFromType(BattleUnitPart* part, s32 type) {
    PoseTableEntry* pose = part->poseTable;
    s32 alt;

    if (type <= BTL_POSE_NORMAL) {
        alt = BTL_POSE_NORMAL;
    } else if (type < BTL_POSE_WALK) {
        alt = BTL_POSE_DAMAGE;
    } else if (type < BTL_POSE_MAX) {
        alt = BTL_POSE_STAY_DEFAULT;
    } else {
        return NULL;
    }
    while (pose) {
        if (pose->poseType >= BTL_POSE_MAX) {
            return NULL;
        }
        if (pose->poseType != type && pose->poseType != alt) {
            pose++;
            continue;
        }
        return pose->poseName;
    }
    return NULL;
}

void BtlUnit_SetAnimType(BattleUnitPart* part, s32 type) {
    const char* name = BtlUnit_GetPoseNameFromType(part, type);

    if (type >= 0x1D && type < 0x28) {
        btlDispChangeAnime(part, name, 1);
    } else {
        btlDispChangeAnime(part, name, 0);
    }
    switch (type) {
        case 0x1D:
        case 0x1E:
            part->animFlags |= PART_ANIM_BLACKEN;
            break;
    }
}

void BtlUnit_SetAnim(BattleUnitPart* part, const char* name) {
    btlDispChangeAnime(part, name, 0);
}

void BtlUnit_SetBodyAnimType(BattleUnit* unit, s32 type) {
    s32 id = BtlUnit_GetBodyPartsId(unit);
    BtlUnit_SetAnimType(BtlUnit_GetPartsPtr(unit, id), type);
}

void BtlUnit_SetBodyAnim(BattleUnit* unit, const char* name) {
    s32 id = BtlUnit_GetBodyPartsId(unit);
    btlDispChangeAnime(BtlUnit_GetPartsPtr(unit, id), name, 0);
}

void BtlUnit_ChangeTalkAnim(s32 unitId) {
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, unitId);
    btlDispChangeAnime(BtlUnit_GetPartsPtr(unit, unit->talkPartId), unit->talkPose, 0);
}

void BtlUnit_ChangeStayAnim(s32 unitId) {
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, unitId);
    btlDispChangeAnime(BtlUnit_GetPartsPtr(unit, unit->talkPartId), unit->stayPose, 0);
}

void BtlUnit_GetTalkTogePos(s32 unitId, f32* x, f32* y, f32* z) {
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, unitId);
    f32 posX, posY, posZ;

    BtlUnit_GetPos(unit, &posX, &posY, &posZ);
    posX += unit->faceDirection * (unit->kindParams->talkTogeBaseOffset.x + unit->togeOffset.x);
    posY += unit->kindParams->talkTogeBaseOffset.y + unit->togeOffset.y;
    posZ += unit->kindParams->talkTogeBaseOffset.z + unit->togeOffset.z;
    *x = posX;
    *y = posY;
    *z = posZ;
}

BOOL BtlUnit_GetEnemyBelong(BattleUnit* unit) {
    s32 belong = unit->alliance;
    switch (belong) {
        case 0:
            belong = 1;
            break;
        case 1:
            belong = 0;
            break;
    }
    return belong;
}

s32 BtlUnit_GetHitDamage(BattleUnit* unit) {
    return unit->hpDamageTaken;
}

s32 BtlUnit_GetTotalHitDamage(BattleUnit* unit) {
    return unit->totalHpDamageTaken;
}

void BtlUnit_SetTotalHitDamage(BattleUnit* unit, s16 damage) {
    unit->totalHpDamageTaken = damage;
}

BOOL BtlUnit_GetACPossibility(BattleUnit* unit) {
    if (unit->alliance) {
        return FALSE;
    }
    if (unit->currentKind == UNIT_SHELL_SHIELD) {
        return FALSE;
    }
    if (BtlUnit_CheckStatus(unit, STATUS_SLEEP) || BtlUnit_CheckStatus(unit, STATUS_STOP) ||
        BtlUnit_CheckStatus(unit, STATUS_FREEZE) || BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL)) {
        return FALSE;
    }
    return !BtlUnit_CheckStatusFlag(unit, 1);
}

void* BtlUnit_GetData(BattleUnit* unit, s32 tag) {
    BattleDataEntry* entry = unit->dataTable;
    if (!entry) {
        return NULL;
    }
    while (entry->tag) {
        if (entry->tag == tag) {
            return entry->data;
        }
        entry++;
    }
    return NULL;
}

BOOL BtlUnit_CheckData(BattleUnit* unit, s32 tag) {
    BattleDataEntry* entry = unit->dataTable;
    if (!entry) {
        return FALSE;
    }
    while (entry->tag) {
        if (entry->tag == tag) {
            return TRUE;
        }
        entry++;
    }
    return FALSE;
}

BOOL BtlUnit_CanGuardStatus(BattleUnit* unit) {
    return BtlUnit_CanActStatus(unit);
}

BOOL BtlUnit_CanActStatus(BattleUnit* unit) {
    if (BtlUnit_CheckStatus(unit, STATUS_SLEEP) || BtlUnit_CheckStatus(unit, STATUS_STOP) ||
        BtlUnit_CheckStatus(unit, STATUS_FREEZE) || BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL)) {
        return FALSE;
    }
    return !BtlUnit_CheckStatusFlag(unit, 1);
}

void BtlUnit_SetParamFromPouch(BattleUnit* unit) {
    BattleWork* wp = _battleWorkPointer;
    PouchData* pouch = pouchGetPtr();
    BattleWorkPartyInfo* info;

    if (unit->currentKind == UNIT_MARIO) {
        unit->currentHp = pouch->currentHP;
        unit->currentFp = pouch->currentFP;
        BtlUnit_ReviseHpFp(unit);
    } else if (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX) {
        s32 id = BattleTransPartyId(unit->currentKind);
        PouchPartyData* party = &pouch->partyData[id];
        unit->currentHp = party->currentHP;
        BtlUnit_ReviseHpFp(unit);
        info = &wp->partyInfo[unit->currentKind - TYPE_PARTNER_MIN];
        unit->sizeMultiplier = info->sizeMultiplier;
        unit->statusFlags = info->statusFlags;
        unit->statusTurns = info->statusTurns;
#if VERSION >= VERSION_US
        unit->usCommandDisabled[0] = info->usCommandDisabled[0];
        unit->usCommandDisabled[1] = info->usCommandDisabled[1];
#endif
        if (unit->currentHp <= 0) {
            BtlUnit_SetStatus(unit, STATUS_INSTANT_KILL, 1, 1);
        }
    }
}

void BtlUnit_ReviseHpFp(BattleUnit* unit) {
    PouchData* pouch = pouchGetPtr();
    PouchPartyData* party;

    if (unit->currentKind == UNIT_MARIO) {
        unit->baseMaxHp = pouch->baseMaxHP;
        unit->maxHp = pouch->baseMaxHP + unit->badgesEquipped.HpPlus * 5;
        unit->baseMaxFp = pouch->baseMaxFP;
        unit->maxFp = pouch->baseMaxFP + unit->badgesEquipped.FpPlus * 5;
        if (unit->currentHp > unit->maxHp) {
            unit->currentHp = unit->maxHp;
        }
        if (unit->currentFp > unit->maxFp) {
            unit->currentFp = unit->maxFp;
        }
    } else if (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX) {
        party = &pouch->partyData[BattleTransPartyId(unit->currentKind)];
        unit->baseMaxHp = party->baseMaxHP;
        unit->maxHp = party->baseMaxHP + unit->badgesEquipped.HpPlus * 5;
        unit->currentHp = party->currentHP;
        if (unit->currentHp > unit->maxHp) {
            unit->currentHp = unit->maxHp;
        }
    } else {
        unit->maxHp = unit->baseMaxHp + unit->badgesEquipped.HpPlus * 5;
        if (unit->currentHp > unit->maxHp) {
            unit->currentHp = unit->maxHp;
        }
        unit->maxFp = unit->baseMaxFp + unit->badgesEquipped.FpPlus * 5;
        if (unit->currentFp > unit->maxFp) {
            unit->currentFp = unit->maxFp;
        }
    }
}

void BtlUnit_SetParamToPouch(BattleUnit* unit) {
    BattleWork* wp = _battleWorkPointer;
    PouchData* pouch = pouchGetPtr();
    BattleWorkPartyInfo* info;

    if (unit->currentKind == UNIT_MARIO) {
        pouch->currentHP = unit->currentHp;
        pouch->currentFP = unit->currentFp;
    } else if (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX) {
        s32 id = BattleTransPartyId(unit->currentKind);
        PouchPartyData* party = &pouch->partyData[id];
        party->currentHP = unit->currentHp;
        info = &wp->partyInfo[unit->currentKind - TYPE_PARTNER_MIN];
        info->sizeMultiplier = unit->sizeMultiplier;
        info->statusFlags = unit->statusFlags;
        info->statusTurns = unit->statusTurns;
#if VERSION >= VERSION_US
        info->usCommandDisabled[0] = unit->usCommandDisabled[0];
        info->usCommandDisabled[1] = unit->usCommandDisabled[1];
#endif
    }
}

void BtlUnit_CheckPinchStatus(BattleUnit* unit, BOOL noAudience) {
    if (unit->currentHp <= unit->kindParams->perilHP && unit->currentHp < unit->maxHp) {
        if (!(unit->statusFlags & STATUS_FLAG_PERIL)) {
            unit->statusFlags |= STATUS_FLAG_PERIL;
            if (!noAudience && unit->currentKind == UNIT_MARIO) {
                BattleAudience_Case_MarioDanger();
            }
        }
    } else if (unit->statusFlags & STATUS_FLAG_PERIL) {
        unit->statusFlags &= ~STATUS_FLAG_PERIL;
    }
    if (unit->currentHp <= unit->kindParams->dangerHP && unit->currentHp < unit->maxHp) {
        if (!(unit->statusFlags & STATUS_FLAG_DANGER)) {
            unit->statusFlags |= STATUS_FLAG_DANGER;
            if (!(unit->statusFlags & STATUS_FLAG_PERIL) && !noAudience && unit->currentKind == UNIT_MARIO) {
                BattleAudience_Case_MarioPinch();
            }
        }
    } else if (unit->statusFlags & STATUS_FLAG_DANGER) {
        unit->statusFlags &= ~STATUS_FLAG_DANGER;
    }
}

s32 BtlUnit_GetExp(BattleUnit* unit) {
    BattleWork* wp = _battleWorkPointer;
    PouchData* pouch = pouchGetPtr();
    s32 level = pouch->level;
    s32 unitLevel = unit->level;
    FieldBattleInfo* fbat = wp->fbatInfo;
    f32 scale;

    if (level > unitLevel) {
        return 0;
    }
    switch (*(s32*)fbat->setup->groupSetup) {
        case 0:
        case 1:
        case 2:
            scale = 1.0f;
            break;
        case 3:
            scale = 1.1f;
            break;
        case 4:
            scale = 1.3f;
            break;
        case 5:
        default:
            scale = 1.5f;
            break;
    }
    {
        f32 t = scale * (f32)(unitLevel - level);
        return (s32)(t / 2.0f) + unit->kindParams->bonusExp;
    }
}

s32 BtlUnit_GetCoin(BattleUnit* unit) {
    s32 coins, i;

    if (!unit) {
        return 0;
    }
    coins = unit->kindParams->baseCoin;
    for (i = 0; i < unit->kindParams->bonusCoin; i++) {
        if (irand(100) < unit->kindParams->bonusCoinRate) {
            coins++;
        }
    }
    return coins;
}

s32 BtlUnit_GetFp(BattleUnit* unit) {
    BattleUnitType kind = unit->currentKind;
    BattleWork* wp = _battleWorkPointer;
    s32 result = unit->currentFp;
    if (kind >= TYPE_PARTNER_MIN && kind < TYPE_PARTNER_MAX) {
        result = BattleGetMarioPtr(wp)->currentFp;
    }
    return result;
}

void BtlUnit_SetFp(BattleUnit* unit, s32 value) {
    BattleUnitType kind = unit->currentKind;
    BattleWork* wp = _battleWorkPointer;
    if (kind >= TYPE_PARTNER_MIN && kind < TYPE_PARTNER_MAX) {
        BattleGetMarioPtr(wp)->currentFp = value;
    } else {
        unit->currentFp = value;
    }
}

void BtlUnit_RecoverHp(BattleUnit* unit, s32 value) {
    unit->currentHp += value;
    if (unit->currentHp > unit->maxHp) {
        unit->currentHp = unit->maxHp;
    }
}

void BtlUnit_RecoverFp(BattleUnit* unit, s32 value) {
    BattleUnitType kind = unit->currentKind;
    BattleWork* wp = _battleWorkPointer;
    s16 max;
    s16* fp;
    if (kind >= TYPE_PARTNER_MIN && kind < TYPE_PARTNER_MAX) {
        max = BtlUnit_GetMaxFp(BattleGetMarioPtr(wp));
        fp = &BattleGetMarioPtr(wp)->currentFp;
    } else {
        max = BtlUnit_GetMaxFp(unit);
        fp = &unit->currentFp;
    }
    *fp += value;
    if (*fp > max) {
        *fp = max;
    }
}

s32 BtlUnit_GetMaxFp(BattleUnit* unit) {
    BattleUnitType kind = unit->currentKind;
    BattleWork* wp = _battleWorkPointer;
    s32 result = unit->maxFp;
    if (kind >= TYPE_PARTNER_MIN && kind < TYPE_PARTNER_MAX) {
        result = BattleGetMarioPtr(wp)->maxFp;
    }
    return result;
}

void BtlUnit_SetMaxFp(BattleUnit* unit, s32 value) {
    BattleUnitType kind = unit->currentKind;
    BattleWork* wp = _battleWorkPointer;
    if (kind >= TYPE_PARTNER_MIN && kind < TYPE_PARTNER_MAX) {
        BattleGetMarioPtr(wp)->maxFp = value;
    } else {
        unit->maxFp = value;
    }
}

s32 BtlUnit_GetWeaponCost(BattleUnit* unit, BattleWeapon* weapon) {
    s32 cost = (u8)weapon->baseFpCost;
    s32 count;

    if (weapon->itemId) {
        count = pouchEquipCheckBadge(weapon->itemId);
        switch (weapon->itemId) {
            case 0xF0:
            case 0xF1:
            case 0xF2:
            case 0xF3:
            case 0xF7:
            case 0xF8:
            case 0xF9:
            case 0xFC:
            case 0x100:
            case 0x101:
            case 0x14C:
            case 0x14D:
            case 0x14E:
            case 0x151:
            case 0x152:
                cost = cost * pow(2.0, count - 1);
                break;
            case 0xF4:
            case 0xF5:
            case 0xF6:
            case 0xFB:
            case 0xFD:
                cost *= count;
                break;
        }
    }
    if (cost) {
        cost -= unit->badgesEquipped.FlowerSaver;
        if (cost <= 0) {
            cost = 1;
        }
    }
#if VERSION >= VERSION_JP
    if (cost >= 1000) {
        cost = 999;
    }
#endif
    return cost;
}

BOOL BtlUnit_CheckWeaponCost(BattleUnit* unit, BattleWeapon* weapon) {
    s32 fp = BtlUnit_GetFp(unit);
    if (fp < BtlUnit_GetWeaponCost(unit, weapon)) {
        return FALSE;
    }
    return pouchGetAP() >= weapon->baseSpCost * 100;
}

void BtlUnit_PayWeaponCost(BattleUnit* unit, BattleWeapon* weapon) {
    BattleWork* wp = _battleWorkPointer;
    s32 fp = BtlUnit_GetFp(unit);
    s32 cost = BtlUnit_GetWeaponCost(unit, weapon);

    BtlUnit_SetFp(unit, fp - cost);
    if (unit->currentKind == UNIT_MARIO) {
        BtlActRec_AddPoint(&wp->actRecord.marioFpSpent, cost);
        BtlActRec_AddCount(&wp->actRecord.marioFpMoves);
    } else if (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX) {
        BtlActRec_AddPoint(&wp->actRecord.partnerFpSpent, cost);
        BtlActRec_AddCount(&wp->actRecord.partnerFpMoves);
    }
    pouchAddAP(-weapon->baseSpCost * 100);
}

BattleUnit* BtlUnit_GetGuardKouraPtr(BattleUnit* unit) {
    BattleWork* wp = _battleWorkPointer;
    s32 i = 0;
    s32 id = unit->unitId;
    BattleUnit* other;

    for (; i < BATTLE_UNIT_MAX; i++) {
        other = BattleGetUnitPtr(wp, i);
        if (other && other->currentKind == UNIT_SHELL_SHIELD && other->work[0] == id) {
            break;
        }
    }
    if (i >= 64) {
        other = NULL;
    }
    return other;
}

void BtlUnit_ResetMoveStatus(BattleUnit* unit) {
    s32 n;

    unit->moveState = 0;
    unit->movesRemaining = unit->maxMoveCount;
    if (BtlUnit_CheckStatus(unit, STATUS_FAST)) {
        unit->movesRemaining *= 2;
    }
    if (BtlUnit_CheckStatus(unit, STATUS_SLOW)) {
        if (unit->movesRemaining >= 2) {
            unit->movesRemaining /= 2;
        } else {
            n = 2;
            if (unit->maxMoveCount < 1) {
                n *= 2;
            }
            if (unit->activeTurns >= n) {
                unit->movesRemaining = 1;
                unit->moveState = 0;
            } else {
                unit->movesRemaining = 0;
                unit->moveState = 10;
            }
        }
    }
    unit->maxMovesThisTurn = unit->movesRemaining;
    if (!unit->maxMovesThisTurn) {
        unit->movesRemaining = 0;
        unit->moveState = 10;
    }
}

void BtlUnit_LoadSeMode(s32 mode, s32 kind, BtlPoseSoundTable* table, BecSndWork* work) {
    work->count = 0;
    work->sfxId = -1;
    switch (kind) {
        case -1:
            switch (mode) {
                case 0:
                    work->name0 = table->entry[0].name0;
                    work->name1 = table->entry[0].name1;
                    work->delay = table->entry[0].delay;
                    work->period0 = table->entry[0].period0;
                    work->period1 = table->entry[0].period1;
                    break;
                case 1:
                    work->name0 = table->entry[1].name0;
                    work->name1 = table->entry[1].name1;
                    work->delay = table->entry[1].delay;
                    work->period0 = table->entry[1].period0;
                    work->period1 = table->entry[1].period1;
                    break;
                case 2:
                    work->name0 = table->jumpName0;
                    work->name1 = table->jumpName1;
                    work->delay = 0;
                    work->period0 = 0;
                    work->period1 = 0;
                    break;
                case 3:
                    work->name0 = table->entry[2].name0;
                    work->name1 = table->entry[2].name1;
                    work->delay = table->entry[2].delay;
                    work->period0 = table->entry[2].period0;
                    work->period1 = table->entry[2].period1;
                    break;
                default:
                    work->name0 = NULL;
                    work->name1 = NULL;
                    work->delay = 0;
                    work->period0 = 0;
                    work->period1 = 0;
                    break;
            }
            work->timer = work->delay;
            return;
        case -2:
            work->timer = work->delay;
            return;
        case 0:
            break;
    }
    work->name0 = NULL;
    work->name1 = NULL;
    work->delay = 0;
    work->period0 = 0;
    work->period1 = 0;
    work->timer = work->delay;
}

void BtlUnit_SetSeMode(BecSndWork* work, const char* name0, const char* name1, s16 c, s16 e, s16 unused, s16 a, s16 b) {
    work->name0 = name0;
    work->name1 = name1;
    work->delay = c;
    work->period0 = e;
    work->period1 = e;
    work->count = 0;
    work->reserved_08 = a;
    work->reserved_0A = b;
    work->sfxId = -1;
}

void BtlUnit_SetCommandAnimPose(BattleUnit* unit) {
    BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
    BOOL special = FALSE;

    if (!(unit->statusFlags & (STATUS_FLAG_DANGER | STATUS_FLAG_PERIL)) && _GetStatusPoseType(unit) == BTL_POSE_NORMAL) {
        special = TRUE;
    }
    if (special) {
        BtlUnit_SetAnimType(part, BTL_POSE_COMMAND_WAIT);
        part->animFlags |= PART_ANIM_COMMAND_WAIT;
    } else {
        btlDispPoseAnime(part);
    }
}

void BtlUnit_PoseSoundInit(BattleUnitPart* part) {
    PART_POSE_SOUND(part)->loopCount = 0;
    PART_POSE_SOUND(part)->time = 0.0f;
    PART_POSE_SOUND(part)->prevTime = 0.0f;
}

#pragma push
// propagation optimisation off for BtlUnit_ControlPoseSoundMain, BtlUnit_snd_se, BtlUnit_snd_se_pos and 4 more: the original register allocation and scheduling need it
#pragma opt_propagation off
void BtlUnit_ControlPoseSoundMain(BattleUnitPart* part) {
    BattleWork* wp = _battleWorkPointer;
    BtlPartPoseSound* state;
    AnimTableEntry* anim;
    BtlPoseSoundData* entry;
    AnimationPose* pose;
    f32 time;
    s32 id;
    u8 vol;
    f64 dv;

    if (!part) {
        return;
    }
    state = PART_POSE_SOUND(part);
    entry = state->table;
    if (!entry) {
        return;
    }
    if (part->poseId == -1) {
        return;
    }
    pose = animPoseGetAnimPosePtr(part->poseId);
    if (!pose) {
        return;
    }
    time = pose->localFrame / 60.0f;
    if (state->loopCount > (u32)pose->loopTime) {
        state->time = time;
        state->prevTime = -1.0f;
        state->loopCount = (s32)pose->loopTime;
        state->count = 0;
        if (BattleGetSeq(wp, SEQ_PHASE) == BATTLE_PHASE_PLAYER || BattleGetSeq(wp, SEQ_PHASE) == BATTLE_PHASE_ENEMY) {
            state->flag = 1;
        }
    } else if (state->loopCount == (u32)pose->loopTime && state->time > time) {
        state->time = time;
        state->prevTime = -1.0f;
    } else if (state->loopCount < (u32)pose->loopTime) {
        state->time = time;
        state->prevTime = -1.0f;
        state->loopCount = (s32)pose->loopTime;
    } else {
        state->prevTime = state->time;
        state->time = time;
    }
    if (state->time == state->prevTime) {
        return;
    }
    anim = animPoseGetCurrentAnim(part->poseId);
    for (; entry->animName; entry++) {
        if (strcmp(entry->animName, (const char*)anim)) {
            continue;
        }
        if (entry->time <= state->time && entry->time > state->prevTime) {
            if (entry->flags & 1) {
                if (entry->callback) {
                    id = entry->callback(part->owner, entry, state);
                } else {
                    id = BtlUnit_snd_se(part->owner, entry->sfxName, -250000000, entry->pitch);
                }
                psndSFX_vol(id, vol = 0x7F);
                state->count++;
                if (part->owner->attackPhase != BattleGetSeq(wp, SEQ_PHASE)) {
                    f64 k;
                    dv = (f64)(u32)vol;
                    vol = dv * (k = 0.7);
                    psndSFX_vol(id, vol);
                }
            } else {
                if (entry->callback) {
                    entry->callback(part->owner, entry, state);
                } else {
                    BtlUnit_snd_se(part->owner, entry->sfxName, -250000000, entry->pitch);
                }
                state->count++;
            }
        }
    }
}
#pragma pop

s32 BtlUnit_snd_se(BattleUnit* unit, const char* sfxName, s32 volume, s32 pan) {
    Vec pos;
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    return ((BtlUnit_snd_se_posS32PitchFn)BtlUnit_snd_se_pos)(unit, sfxName, volume, pan, &pos);
}

s32 BtlUnit_snd_se_pos(BattleUnit* unit, const char* sfxName, s32 volume, s16 pitch, Vec* pos) {
    s32 id;
    s8 turns, strength;
    s16 pit = 0;
    s16 p;

    if (BtlUnit_CheckStatus(unit, STATUS_TINY)) {
        BtlUnit_GetStatus(unit, STATUS_TINY, &turns, &strength);
        pit = (strength * 2 - 1) * -0x155;
    }
    if (BtlUnit_CheckStatus(unit, STATUS_HUGE)) {
        BtlUnit_GetStatus(unit, STATUS_HUGE, &turns, &strength);
        pit = (strength * 2 + 1) * -0x155;
    }

    p = pitch;
    p += pit;
    p += irand(41) - 20;
    id = psndSFXOn_3D(sfxName, pos);
    psndSFX_pit(id, p);
    psndSFX_vol(id, volume == -250000000 ? psndSFX_get_vol(id) : (u8)volume);
    return id;
}

void BtlUnit_HpGaugeInit(BattleUnit* unit) {
    BattleWorkHpGauge* gauge = &unit->hpGauge;

    gauge->drainTimer = 0;
    gauge->visibleTimer = 0;
    gauge->mode = 0;
    gauge->prevHp = unit->currentHp;
    gauge->targetHp = unit->currentHp;
    gauge->trailRatio = gauge->barRatio = (f32)unit->currentHp / (f32)unit->maxHp;
    switch (gauge->mode) {
        case 1:
            gauge->drainLength = 40;
            gauge->visibleLength = gauge->drainLength + 30;
            break;
        default:
            gauge->drainLength = 20;
            gauge->visibleLength = gauge->drainLength + 30;
            break;
    }
}

void BtlUnit_HpGaugeMain(BattleUnit* unit) {
    BattleWorkHpGauge* gauge = &unit->hpGauge;
    s16 maxHp;

    if (gauge->drainTimer > 0) {
        gauge->drainTimer--;
        if (gauge->drainTimer <= 0) {
            gauge->prevHp = gauge->targetHp;
            gauge->barRatio = gauge->trailRatio = (f32)unit->currentHp / (f32)unit->maxHp;
        } else {
            switch (gauge->mode) {
                case 1:
                    gauge->barRatio = (f32)unit->currentHp / (f32)unit->maxHp;
                    gauge->trailRatio = gauge->barRatio + (f32)(gauge->prevHp - gauge->targetHp) * intplGetValue(2, 0.0f, 1.0f, gauge->drainTimer, gauge->drainLength) / (f32)unit->maxHp;
                    break;
                default:
                    gauge->trailRatio = 0.0f;
                    maxHp = unit->maxHp;
                    gauge->barRatio = (f32)(gauge->prevHp - gauge->targetHp) * intplGetValue(0, 0.0f, 1.0f, gauge->drainTimer, gauge->drainLength) / (f32)maxHp + (f32)unit->currentHp / (f32)maxHp;
                    break;
            }
        }
    }
    if (gauge->visibleTimer > 0) {
        gauge->visibleTimer--;
    }
    if ((unit->flags & UNIT_FLAG_SHOW_HP_GAUGE) && gauge->visibleTimer <= 0 && (gauge->flags & 1)) {
        unit->flags &= ~UNIT_FLAG_SHOW_HP_GAUGE;
        gauge->flags &= ~1;
    }
}

BOOL BtlUnit_EnemyItemCanUseCheck(s32 item) {
    s32* table = _enemy_can_use_item_table;

    if (item >= 0xF0 && item < 0x153) {
        return item;
    }
    while (*table) {
        if (*table == item) {
            return item;
        }
        table++;
    }
    return FALSE;
}

BOOL BtlUnit_CheckShadowGuard(BattleUnit* unit) {
    if (unit->attributeFlags & UNIT_ATTR_VEILED) {
        return TRUE;
    }
    if (unit->currentKind == UNIT_VIVIAN && unit->work[4] > 0) {
        return TRUE;
    }
    return FALSE;
}
