#include "driver/mobjdrv.h"
#include "driver/mapdrv.h"
#include "driver/npcdrv.h"
#include "mario/mario_party.h"
#include "party.h"
#include "dolphin/mtx.h"
#include "dolphin/types.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/hitdrv.h"
#include "driver/offscreendrv.h"
#include "driver/itemdrv.h"
#include "manager/evtmgr.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include <string.h>


extern u8 cubeDJ[0x68];
extern u8 headDJ[0x68];
extern u8 frontDJ[0x68];
extern u8 front2DJ[0x68];
HitEntry* hitEntryMOBJ(MapFileJoint* joint, Mtx mtx);

#define MAX_MOBJ_WORK 3

extern GlobalWork* gp;

//.sbss
BOOL koopaRunFlag;

//.bss
static MapObjectWork work[MAX_MOBJ_WORK];

#define mobjGetWorkFlag(flag) (flag ? &work[1] : &work[0])

void mobjKoopaOn(void) {
    if (!koopaRunFlag) {
        MapObjectWork* wp = &work[2];

        koopaRunFlag = TRUE;
        wp->count = 128;
        wp->entries = _mapAlloc(sizeof(MapObjectEntry) * wp->count);
        memset(wp->entries, 0, sizeof(MapObjectEntry) * wp->count);
    }
}

inline MapObjectWork* mobjGetWork(void) {
    if (koopaRunFlag) {
        return &work[2];
    } else {
        return mobjGetWorkFlag(gp->inBattle);
    }
}

inline void calcMtx(MapObjectEntry* entry, Mtx dest, Vec position) { // guessing, always inlined
    Mtx trans, scale, xrot, yrot, zrot;

    MTXTrans(trans, position.x, position.y, position.z);
    MTXScale(scale, entry->scale2.x, entry->scale2.y, entry->scale2.z);
    MTXRotRad(xrot, 'x', MTXDegToRad(entry->rotation.x));
    MTXRotRad(yrot, 'y', MTXDegToRad(entry->rotation.y));
    MTXRotRad(zrot, 'z', MTXDegToRad(entry->rotation.z));
    MTXConcat(trans, zrot, trans);
    MTXConcat(trans, yrot, trans);
    MTXConcat(trans, xrot, trans);
    MTXConcat(trans, scale, dest);
}

inline int mobjCheckKururingFloorItem(MapObjectEntry* entry) { // was always inlined in retail but not in demo
    if (!strcmp(entry->animName, "MOBJ_KururinFloor")) {
        ItemEntry* item = itemNameToPtr(entry->name);
        if ((item != NULL && (item->flags & 1) && evtGetValue(0, entry->unk1E4) == 0))
            return 1;
        else if ((evtGetValue(0, entry->unk1E4) != 0))
            return 1;
        else
            return 2;
    } else {
        return 0;
    }
}

void mobjDispXLU(CameraId camId, void* param) {
    MapObjectEntry* entry = param; // cast to correct type

    if (entry->flags & 0x400) {
        animSetPaperTexMtx(entry->paperTexMtx, NULL, NULL);
        animSetPaperTexObj(&entry->paperTexObj, NULL, NULL, entry->unk208, NULL, NULL, 1, 1);
    }
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 1);
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 2);
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 3);
    if (entry->flags & 0x400) {
        animSetPaperTexMtx(NULL, NULL, NULL);
        animSetPaperTexObj(NULL, NULL, NULL, NULL, NULL, NULL, 1, 1);
    }
}

void mobjDisp(CameraId camId, void* param) {
    MapObjectEntry* entry = param; // cast to correct type
    DispEntry* disp;

    if (entry->flags & 0x400) {
        animSetPaperTexMtx(entry->paperTexMtx, NULL, NULL);
        animSetPaperTexObj(&entry->paperTexObj, NULL, NULL, entry->unk208, NULL, NULL, 1, 1);
    }
    disp = dispGetCurWork();
    switch (disp->renderMode) {
        case 0:
            animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                         10.0f * entry->scale.x, 1);
            break;
        case 1:
            animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                         10.0f * entry->scale.x, 2);
            break;
        case 2:
        default:
            animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                         10.0f * entry->scale.x, 3);
            break;
    }
    if (entry->flags & 0x400) {
        animSetPaperTexMtx(NULL, NULL, NULL);
        animSetPaperTexObj(NULL, NULL, NULL, NULL, NULL, NULL, 1, 1);
    }
}

void mobjDisp_OffscreenXLU(CameraId camId, void* param) {
    MapObjectEntry* entry = param; // cast to correct type
    u16 left, top, right, bottom;

    sysWaitDrawSync();
    GXClearBoundingBox();
    if (entry->flags & 0x400) {
        animSetPaperTexMtx(entry->paperTexMtx, NULL, NULL);
        animSetPaperTexObj(&entry->paperTexObj, NULL, NULL, entry->unk208, NULL, NULL, 1, 1);
    }
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 1);
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 2);
    animPoseDraw(entry->poseId, entry->position.x, entry->position.y, entry->position.z, entry->rotation.y,
                 10.0f * entry->scale.x, 3);
    if (entry->flags & 0x400) {
        animSetPaperTexMtx(NULL, NULL, NULL);
        animSetPaperTexObj(NULL, NULL, NULL, NULL, NULL, NULL, 1, 1);
    }
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    offscreenAddBoundingBox(entry->offscreenId, left, top, right, bottom);
}

void mobjInit(void) {
    MapObjectWork* wp = &work[0];

    wp->count = 16;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(MapObjectEntry) * wp->count);
    memset(wp->entries, 0, sizeof(MapObjectEntry) * wp->count);

    wp = &work[1];
    wp->count = 8;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(MapObjectEntry) * wp->count);
    memset(wp->entries, 0, sizeof(MapObjectEntry) * wp->count);

    koopaRunFlag = FALSE;
}

void mobjReset(BOOL inBattle) {
    MapObjectWork* wp = mobjGetWorkFlag(inBattle);
    memset(wp->entries, 0, sizeof(MapObjectEntry) * wp->count);
    koopaRunFlag = FALSE;
}

void mobjHitEntry(MapObjectEntry* entry, s32 type) {
    AnimationPoseData* pose;
    Mtx mtx;
    Vec min;
    Vec max;
    Vec position;
    s32 i;

    pose = animPoseGetAnimBaseDataPtr(entry->poseId);
    min = (Vec){pose->bboxMin.x, pose->bboxMin.y, pose->bboxMin.z};
    max = (Vec){pose->bboxMax.x, pose->bboxMax.y, pose->bboxMax.z};
    for (i = 0; i < 2; i++) {
        if (entry->hitObj[i].hitObject != NULL)
            hitDelete(entry->hitObj[i].name);
    }
    PSVECAdd(&max, &min, &entry->translation);
    PSVECScale(&entry->translation, &entry->translation, 0.5f);
    PSVECScale(&entry->translation, &entry->translation, 10.0f);
    entry->translation.y = 0.0f;
    entry->scale2.x = 10.0f * (entry->scale.x * (f32)__fabs(max.x - min.x));
    entry->scale2.y = 10.0f * (entry->scale.y * (f32)__fabs(max.y));
    entry->scale2.z = 10.0f * (entry->scale.z * (f32)__fabs(max.z - min.z));
    if (strncmp(pose->fileName, "HOBJ_", strlen("HOBJ_")) == 0) {
        entry->translation.z = 0.0f;
        entry->scale2.z = 10.0f * (2.5f * entry->scale.z);
    }
    switch (type) {
        case 0:
            PSVECAdd(&entry->position, &entry->translation, &position);
            {
                Mtx trans, scale, xrot, yrot, zrot;
                MTXTrans(trans, position.x, position.y, position.z);
                MTXScale(scale, entry->scale2.x, entry->scale2.y, entry->scale2.z);
                MTXRotRad(xrot, 'x', MTXDegToRad(entry->rotation.x));
                MTXRotRad(yrot, 'y', MTXDegToRad(entry->rotation.y));
                MTXRotRad(zrot, 'z', MTXDegToRad(entry->rotation.z));
                MTXConcat(trans, zrot, trans);
                MTXConcat(trans, yrot, trans);
                MTXConcat(trans, xrot, trans);
                MTXConcat(trans, scale, mtx);
            }
            memcpy((u8*)&entry->hitObj[0] + 0x1C, cubeDJ, 0x68);
            strcpy(entry->hitObj[0].name, "MOBJ_");
            strcat(entry->hitObj[0].name, entry->name);
            *(char**)((u8*)&entry->hitObj[0] + 0x1C) = entry->hitObj[0].name;
            entry->hitObj[0].hitObject = hitEntryMOBJ((MapFileJoint*)((u8*)&entry->hitObj[0] + 0x1C), mtx);
            *(MapObjectEntry**)((u8*)entry->hitObj[0].hitObject + 0xD0) = entry;
            break;
        case 1:
            PSVECAdd(&entry->position, &entry->translation, &position);
            {
                Mtx trans, scale, xrot, yrot, zrot;
                MTXTrans(trans, position.x, position.y, position.z);
                MTXScale(scale, entry->scale2.x, entry->scale2.y, entry->scale2.z);
                MTXRotRad(xrot, 'x', MTXDegToRad(entry->rotation.x));
                MTXRotRad(yrot, 'y', MTXDegToRad(entry->rotation.y));
                MTXRotRad(zrot, 'z', MTXDegToRad(entry->rotation.z));
                MTXConcat(trans, zrot, trans);
                MTXConcat(trans, yrot, trans);
                MTXConcat(trans, xrot, trans);
                MTXConcat(trans, scale, mtx);
            }
            memcpy((u8*)&entry->hitObj[0] + 0x1C, headDJ, 0x68);
            strcpy(entry->hitObj[0].name, "MOBJ_");
            strcat(entry->hitObj[0].name, entry->name);
            *(char**)((u8*)&entry->hitObj[0] + 0x1C) = entry->hitObj[0].name;
            entry->hitObj[0].hitObject = hitEntryMOBJ((MapFileJoint*)((u8*)&entry->hitObj[0] + 0x1C), mtx);
            *(MapObjectEntry**)((u8*)entry->hitObj[0].hitObject + 0xD0) = entry;
            break;
        case 2:
            PSVECAdd(&entry->position, &entry->translation, &position);
            {
                Mtx trans, scale, xrot, yrot, zrot;
                MTXTrans(trans, position.x, position.y, position.z);
                MTXScale(scale, entry->scale2.x, entry->scale2.y, entry->scale2.z);
                MTXRotRad(xrot, 'x', MTXDegToRad(entry->rotation.x));
                MTXRotRad(yrot, 'y', MTXDegToRad(entry->rotation.y));
                MTXRotRad(zrot, 'z', MTXDegToRad(entry->rotation.z));
                MTXConcat(trans, zrot, trans);
                MTXConcat(trans, yrot, trans);
                MTXConcat(trans, xrot, trans);
                MTXConcat(trans, scale, mtx);
            }
            memcpy((u8*)&entry->hitObj[0] + 0x1C, frontDJ, 0x68);
            strcpy(entry->hitObj[0].name, "MOBJ_");
            strcat(entry->hitObj[0].name, entry->name);
            *(char**)((u8*)&entry->hitObj[0] + 0x1C) = entry->hitObj[0].name;
            entry->hitObj[0].hitObject = hitEntryMOBJ((MapFileJoint*)((u8*)&entry->hitObj[0] + 0x1C), mtx);
            *(MapObjectEntry**)((u8*)entry->hitObj[0].hitObject + 0xD0) = entry;
            memcpy((u8*)&entry->hitObj[1] + 0x1C, front2DJ, 0x68);
            strcpy(entry->hitObj[1].name, "MOBJ~");
            strcat(entry->hitObj[1].name, entry->name);
            *(char**)((u8*)&entry->hitObj[1] + 0x1C) = entry->hitObj[1].name;
            entry->hitObj[1].hitObject = hitEntryMOBJ((MapFileJoint*)((u8*)&entry->hitObj[1] + 0x1C), mtx);
            *(MapObjectEntry**)((u8*)entry->hitObj[1].hitObject + 0xD0) = entry;
            break;
    }
}

s32 mobjEntry(const char* name, const char* animPoseName) {
    MapObjectWork* wp = mobjGetWork();
    s32 entryCount;
    s32 idx;
    MapObjectEntry* entry;

    entryCount = wp->count;
    for (idx = 0, entry = wp->entries; idx < entryCount; idx++, entry++) {
        if ((entry->flags & 1) && (strcmp(entry->name, name) == 0))
            break;
    }
    // SPM uses this to assert the name isn't duplicate, here it's just pointless

    for (idx = 0, entry = wp->entries; idx < entryCount; idx++, entry++) {
        if ((entry->flags & 1) == 0)
            break;
    }

    memset(entry, 0, sizeof(*entry));
    entry->flags |= 1;
    strcpy(entry->name, name);

    entry->position = (Vec){ 0.0f, 0.0f, 0.0f };
    entry->scale = (Vec){ 1.0f, 1.0f, 1.0f };
    entry->rotation = (Vec){ 0.0f, 0.0f, 0.0f };
    entry->unk5C = (Vec){ 0.0f, 0.0f, 0.0f };
    entry->unk68 = 1.0f;
    entry->unk6C = 1.0f;
    entry->camId = CAMERA_3D;
    entry->poseId = animPoseEntry(animPoseName, gp->inBattle != 0);
    animPosePeraOff(entry->poseId);
    strcpy(entry->animName, animPoseName);
    animPoseSetAnim(entry->poseId, "S_1", 1);
    animPoseSetMaterialLightFlagOn(entry->poseId, 2);
    mobjHitEntry(entry, 0);
    entry->offscreenId = -1;
    return idx;
}

void mobjDelete(const char* name) {
    MapObjectWork* wp = mobjGetWork();
    s32 entryCount;
    int i;
    MapObjectEntry* entry;

    entryCount = wp->count;
    entry = wp->entries;
    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & 1) && strcmp(entry->name, name) == 0) {
            for (i = 0; i < 2; i++) {
                if ((entry->hitObj[i].name) != NULL) {
                    if (!gp->inBattle) {
                        marioResetHitObj(entry->hitObj[i].name);
                    }
                    hitDelete(entry->hitObj[i].name);
                }
            }
            entry->flags &= ~1;
            break;
        }
    }
}

void mobjSetPosition(const char* name, f32 x, f32 y, f32 z) {
    MapObjectWork* wp = mobjGetWork();
    MapObjectEntry* entry;
    s32 entryCount;
    int i;

    entryCount = wp->count;
    entry = wp->entries;
    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & 1) && strcmp(entry->name, name) == 0) {
            break;
        }
    }

    entry->position.x = x;
    entry->position.y = y + 0.1f;
    entry->position.z = z;
}

s32 marioChkHipBump(void);

void mobjMain(void) {
    MapObjectWork* wp;
    MapObjectEntry* entry;
    MarioWork* mario;
    void* party;
    void* fbat;
    s32 i;
    s32 j;
    Mtx mtx;

    wp = mobjGetWork();
    entry = wp->entries;
    mario = marioGetPtr();
    party = partyGetPtr(marioGetPartyId());
    fbat = fbatGetPointer();
    /* TODO: block at 0x68-0x22c: 5x hitGetName/strcmp ride/hit checks on mario & party */

    for (i = 0; i < wp->count; i++, entry++) {
        if (!(entry->flags & 1)) {
            continue;
        }
        /* TODO: 0x23c-0x264 flag/type filter (else goto anim section 0xd0c) */
        {
            if (strcmp(entry->name, "") == 0 || strcmp(entry->name, "") == 0 ||
                strcmp(entry->name, "") == 0 || strcmp(entry->name, "") == 0) {
                /* TODO: 0x2bc-0x2d8 */
            }
            /* TODO: 0x2dc type == 2 branch */
            if (entry->flags == 2) {
                PSVECAdd(&entry->position, &entry->position, &entry->position);
                PSMTXTrans(mtx, 0.0f, 0.0f, 0.0f);
                PSMTXScale(mtx, 1.0f, 1.0f, 1.0f);
                PSMTXRotRad(mtx, 'x', 0.0f);
                PSMTXRotRad(mtx, 'y', 0.0f);
                PSMTXRotRad(mtx, 'z', 0.0f);
                PSMTXConcat(mtx, mtx, mtx);
                PSMTXConcat(mtx, mtx, mtx);
                PSMTXConcat(mtx, mtx, mtx);
                PSMTXConcat(mtx, mtx, mtx);
                for (j = 0; j < 2; j++) {
                    if (entry->hitObj[j].hitObject != NULL) {
                        hitReCalcMatrix(entry->hitObj[j].hitObject, mtx);
                    }
                }
            } else {
                PSVECAdd(&entry->position, &entry->position, &entry->position);
                animPoseGetAnimBaseDataPtr(entry->poseId);
                /* TODO: block at 0x3ec-0x4e8 joint search */
                if (strncmp(entry->name, "", strlen("")) == 0) {
                    /* TODO: 0x504-0x524 */
                }
                PSMTXTrans(mtx, 0.0f, 0.0f, 0.0f);
                PSMTXScale(mtx, 1.0f, 1.0f, 1.0f);
                PSMTXRotRad(mtx, 'x', 0.0f);
                PSMTXRotRad(mtx, 'y', 0.0f);
                PSMTXRotRad(mtx, 'z', 0.0f);
                PSMTXConcat(mtx, mtx, mtx);
                PSMTXConcat(mtx, mtx, mtx);
                PSMTXConcat(mtx, mtx, mtx);
                PSMTXConcat(mtx, mtx, mtx);
                for (j = 0; j < 2; j++) {
                    if (entry->hitObj[j].hitObject != NULL) {
                        hitReCalcMatrix(entry->hitObj[j].hitObject, mtx);
                    }
                }
            }
        }
        if (entry->flags & 0x10) {
            /* TODO: block at 0x624-0x710 (hitCheckFilter) */
            hitCheckFilter(NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
            PSVECAdd(&entry->position, &entry->position, &entry->position);
            animPoseGetAnimBaseDataPtr(entry->poseId);
            /* TODO: block at 0x72c-0x828 */
            if (strncmp(entry->name, "", strlen("")) == 0) {
                /* TODO: 0x844-0x864 */
            }
            PSMTXTrans(mtx, 0.0f, 0.0f, 0.0f);
            PSMTXScale(mtx, 1.0f, 1.0f, 1.0f);
            PSMTXRotRad(mtx, 'x', 0.0f);
            PSMTXRotRad(mtx, 'y', 0.0f);
            PSMTXRotRad(mtx, 'z', 0.0f);
            PSMTXConcat(mtx, mtx, mtx);
            PSMTXConcat(mtx, mtx, mtx);
            PSMTXConcat(mtx, mtx, mtx);
            PSMTXConcat(mtx, mtx, mtx);
            for (j = 0; j < 2; j++) {
                if (entry->hitObj[j].hitObject != NULL) {
                    hitReCalcMatrix(entry->hitObj[j].hitObject, mtx);
                }
            }
        }
        /* TODO: block at 0x944-0xc88 attack checks: marioGetPtr, marioChkHipBump,
           unk_8005bb80, PSVECDistance x2, kpaGetHitobjHead/Ride, kpaHipAttackCheck,
           kpaGetHitobj, kpaGetLevel, kpaGetHitFlame */
        marioStGetSystemLevel();
        marioGetPtr();
        /* TODO: 0xcd0-0xd08 callback (bctrl) */
        /* TODO: 0xd0c-0xdfc shadow: mapGetWork, mapGetBlend, mapGetBlend2,
           animPoseGetMaterialFlag x2, shadowEntry, shadowSetType, shadowSetSize */
        animPoseMain(entry->poseId);
        animPoseGetMaterialEvtColor(entry->poseId);
        /* TODO: 0xe20-0xe8c camGetPtr, PSMTXMultVec, PSMTX44MultVec cull */
        if (entry->flags & 0x20) {
            if (animPoseGetMaterialFlag(entry->poseId) & 1) {
                dispEntry(CAMERA_3D, 1, dispCalcZ(&entry->position), NULL, entry);
            } else {
                dispEntry(CAMERA_3D, 1, dispCalcZ(&entry->position), NULL, entry);
                dispEntry(CAMERA_3D, 1, dispCalcZ(&entry->position), NULL, entry);
                dispEntry(CAMERA_3D, 1, dispCalcZ(&entry->position), NULL, entry);
            }
        } else {
            if (animPoseGetMaterialFlag(entry->poseId) & 1) {
                dispEntry(CAMERA_3D, 1, dispCalcZ(&entry->position), NULL, entry);
            } else {
                dispEntry(CAMERA_3D, 1, dispCalcZ(&entry->position), NULL, entry);
                dispEntry(CAMERA_3D, 1, dispCalcZ(&entry->position), NULL, entry);
                dispEntry(CAMERA_3D, 1, dispCalcZ(&entry->position), NULL, entry);
            }
        }
    }
}

MapObjectEntry* mobjNameToPtr(const char* name) {
    int i;
    s32 entryCount;
    MapObjectEntry* entry;
    MapObjectWork* wp = mobjGetWork();

    entryCount = wp->count;
    entry = wp->entries;
    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & 1) && strcmp(entry->name, name) == 0) {
            break;
        }
    }

    return entry;
}

MapObjectEntry* mobjNameToPtrNoAssert(const char* name) {
    int i;
    s32 entryCount;
    MapObjectEntry* entry;
    MapObjectWork* wp = mobjGetWork();

    entryCount = wp->count;
    entry = wp->entries;
    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & 1) && strcmp(entry->name, name) == 0) {
            break;
        }
    }

    if (i >= entryCount) {
        return NULL;
    }

    return entry;
}

MapObject* mobjHitObjPtrToPtr(HitEntry* hitObj) {
    if (hitObj->attributes & (1 << 31)) {
        return hitObj->mapObj;
    }

    return NULL;
}

EventEntry* mobjRunEvent(MapObjectEntry* entry, s32* eventCode) {
    EventEntry* event;

    if (eventCode == NULL) {
        return NULL;
    }
    if (evtCheckID(entry->eventId)) {
        return NULL;
    }

    entry->eventId = 0;
    event = evtEntryType(eventCode, 0x1E, 0, 0x1A);
    event->thisMapObj = entry;
    entry->eventId = event->eventId;

    return event;
}

void mobjCalcMtx(MapObjectEntry* entry) {
    AnimationPoseData* pose;
    Mtx mtx;
    Mtx trans, scale, xrot, yrot, zrot;
    Vec position;
    Vec min;
    Vec max;
    s32 i;

    PSVECAdd(&entry->position, &entry->translation, &position);
    pose = animPoseGetAnimBaseDataPtr(entry->poseId);
    min = (Vec){pose->bboxMin.x, pose->bboxMin.y, pose->bboxMin.z};
    max = (Vec){pose->bboxMax.x, pose->bboxMax.y, pose->bboxMax.z};
    entry->scale2.x = 10.0f * (entry->scale.x * (f32)__fabs(max.x - min.x));
    entry->scale2.y = 10.0f * (entry->scale.y * (f32)__fabs(max.y));
    entry->scale2.z = 10.0f * (entry->scale.z * (f32)__fabs(max.z - min.z));
    if (strncmp(pose->fileName, "HOBJ_", strlen("HOBJ_")) == 0) {
        entry->translation.z = 0.0f;
        entry->scale2.z = 10.0f * (2.5f * entry->scale.z);
    }
    {
                Mtx trans, scale, xrot, yrot, zrot;
                MTXTrans(trans, position.x, position.y, position.z);
                MTXScale(scale, entry->scale2.x, entry->scale2.y, entry->scale2.z);
                MTXRotRad(xrot, 'x', MTXDegToRad(entry->rotation.x));
                MTXRotRad(yrot, 'y', MTXDegToRad(entry->rotation.y));
                MTXRotRad(zrot, 'z', MTXDegToRad(entry->rotation.z));
                MTXConcat(trans, zrot, trans);
                MTXConcat(trans, yrot, trans);
                MTXConcat(trans, xrot, trans);
                MTXConcat(trans, scale, mtx);
            }
    for (i = 0; i < 2; i++) {
        if (entry->hitObj[i].hitObject != NULL)
            hitReCalcMatrix(entry->hitObj[i].hitObject, mtx);
    }
}

void mobjCalcMtx2(MapObjectEntry* entry) {
    Mtx mtx;
    Mtx zRot;
    Mtx yRot;
    Mtx xRot;
    Mtx scale;
    Mtx trans;
    Vec position;
    s32 i;

    PSVECAdd(&entry->position, &entry->translation, &position);

    // TODO: Try matching using calcMtx inline function - had issues with lining up the stack offsets
    // Matches fine here
    MTXTrans(trans, position.x, position.y, position.z);
    MTXScale(scale, entry->scale2.x, entry->scale2.y, entry->scale2.z);
    MTXRotRad(xRot, 'x', MTXDegToRad((0, entry->rotation.x)));
    MTXRotRad(yRot, 'y', MTXDegToRad(entry->rotation.y));
    MTXRotRad(zRot, 'z', MTXDegToRad(entry->rotation.z));
    MTXConcat(trans, zRot, trans);
    MTXConcat(trans, yRot, trans);
    MTXConcat(trans, xRot, trans);
    MTXConcat(trans, scale, mtx);

    for (i = 0; i < 2; i++) {
        if (entry->hitObj[i].hitObject != 0)
            hitReCalcMatrix(entry->hitObj[i].hitObject, mtx);
    }
}

BOOL mobjGetHint(MapObjectEntry* entry) {
    if (entry == NULL) {
        return 0;
    }
    return (entry->flags >> 5) & 1;
}

BOOL mobjCheckExec() {
    MapObjectWork* wp = mobjGetWork();
    int i;
    MapObjectEntry* entry;

    for (i = 0, entry = wp->entries; i < wp->count; entry++, i++) {
        if (entry->flags & (1 << 9))
            return TRUE;
    }
    return FALSE;
}

s32 mobjCheckItemboxOpen(MapObjectEntry* entry) {
    if (strcmp(entry->animName, "MOBJ_TreasureBox") == 0 || strcmp(entry->animName, "MOBJ_BigTreasureBox") == 0 ||
        strcmp(entry->animName, "MOBJ_GrayTreasureBox") == 0 || strcmp(entry->animName, "MOBJ_BlackTreasureBox") == 0) {
        if (entry->unk1DC == 99)
            return 2;
        else
            return 1;
    } else {
        return 0;
    }
}

MapObjectEntry* mobjNearDistCheck2(f32 x, f32 y, f32 z, f32 minMagnitude, char** names) {
    int entryCount;
    Vec pos;
    Vec dist;
    Vec _pos;
    MapObjectEntry* entry;
    MapObjectWork* wp = mobjGetWork();
    MapObjectEntry* ret;
    int i;
    float mag;
    char** animName;

    entryCount = wp->count;
    entry = wp->entries;
    ret = NULL;

    _pos = (Vec){ 0.0f, 0.0f, 0.0f };
    _pos.x = x;
    _pos.y = y;
    _pos.z = z;
    pos = _pos;

    for (i = 0; i < entryCount; i++, entry++) {
        if ((entry->flags & 1) == 0)
            continue;

        animName = names;
        while (*animName != NULL) {
            if (strcmp(entry->animName, *animName) == 0) {
                if (strcmp(entry->animName, "MOBJ_TreasureBox") == 0 ||
                    strcmp(entry->animName, "MOBJ_BigTreasureBox") == 0 ||
                    strcmp(entry->animName, "MOBJ_GrayTreasureBox") == 0 ||
                    strcmp(entry->animName, "MOBJ_BlackTreasureBox") == 0) {
                    if (mobjCheckItemboxOpen(entry) != 1) {
                        animName++;
                        continue;
                    }
                } else if (strcmp(entry->animName, "MOBJ_KururinFloor") == 0) {
                    if (mobjCheckKururingFloorItem(entry) != 2) {
                        animName++;
                        continue;
                    }
                }

                VECSubtract(&entry->position, &pos, &dist);
                mag = VECMag(&dist);
                if (mag < minMagnitude) {
                    minMagnitude = mag;
                    ret = entry;
                    break;
                }
                break;
            }
            animName++;
        }
    }

    return ret;
}
