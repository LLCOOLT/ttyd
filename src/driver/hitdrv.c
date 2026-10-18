#include "driver/hitdrv.h"
#include "dolphin/os.h"
#include "driver/mapdrv.h"
#include "memory.h"
#include "party.h"
#include <string.h>

// prototypes for asm stopgap forward references
void hitBindUpdate(const char* name);
void hitBindMapObj(const char* hitName, const char* mapobjName);
Vec* hitGetDamageReturnPos(HitEntry* hit);
void hitGrpDamageReturnSet(const char* name, HitDamageReturn* damage);
void hitDamageReturnSet(HitEntry* hit, HitDamageReturn* damage, BOOL recursion);
s32 hitGetAttr(HitEntry* hit);
const char* hitGetName(HitEntry* hit);
void hitObjGetNormal(const char* name, Vec* normal);
void hitObjGetPos(const char* name, Vec* position);
void hitObjGetPosSub(HitEntry* hit, Vec* position, s32* counter, BOOL recursion);
HitEntry* hitNameToPtr(const char* name);
BOOL chkFilterAttr(HitCheckQuery* query, HitEntry* entry);
BOOL hitCheckVecHitObjXZ(HitCheckQuery* query, HitEntry* entry);
BOOL checkTriVec_xz(HitCheckQuery* query, HitVector* vector);
HitEntry* hitCheckVecFilter(HitCheckQuery* query, HitFilterCallback callback);
s32 hitCalcVtxPosition(HitEntry* hit);
void hitReCalcMatrix2(HitEntry* hit, Mtx mtx, BOOL recursion);
void hitReCalcMatrix(HitEntry* hit, Mtx mtx);
void hitGrpAttrOff(const char* name, u32 mask);
void hitGrpAttrOn(const char* name, u32 mask);
void hitAtrOff(HitEntry* hit, u32 mask, s32 r);
void hitAtrOn(HitEntry* hit, u32 mask, s32 r);
void hitObjAttrOff(const char* name, u32 mask);
void hitObjAttrOn(const char* name, u32 mask);
void hitGrpFlagOff(const char* name, u16 mask);
void hitGrpFlagOn(const char* name, u16 mask);
void hitFlgOff(HitEntry* hit, u16 mask, s32 r);
void hitFlgOn(HitEntry* hit, u16 mask, s32 r);
void hitObjFlagOff(const char* name, u16 mask);
void hitObjFlagOn(const char* name, u16 mask);
void hitMain(void);
void hitDelete(const char* name);
HitEntry* hitEntryMOBJ(MapFileJoint* joint, Mtx mtx);
HitEntry* hitEntry(MapFileJoint* root, Mtx rootMtx, s32 mapIndex);
HitEntry* hitEntrySub(MapFileJoint* joint, HitEntry* parent, Mtx parentMtx, BOOL ignoreSiblings, s32 mapIndex);
HitEntry* _hitEnt(MapFileJoint* joint, HitEntry* parent, Mtx parentMtx, s32 mapIndex);

/*
    00012b2c 000004 8001810c  4 hitInit 	hitdrv.o
    00012a94 000098 80018074  4 hitReInit 	hitdrv.o
    0001260c 000488 80017bec  4 _hitEnt 	hitdrv.o
    00012394 000278 80017974  4 hitEntrySub 	hitdrv.o
    000122fc 000098 800178dc  4 hitEntry 	hitdrv.o
    0001228c 000070 8001786c  4 hitEntryMOBJ 	hitdrv.o
    000121e8 0000a4 800177c8  4 hitDelete 	hitdrv.o
    00011fc4 000224 800175a4  4 hitMain 	hitdrv.o
    00011ef0 0000d4 800174d0  4 hitObjFlagOn 	hitdrv.o
    00011e1c 0000d4 800173fc  4 hitObjFlagOff 	hitdrv.o
    00011b0c 000310 800170ec  4 hitFlgOn 	hitdrv.o
    000117f4 000318 80016dd4  4 hitFlgOff 	hitdrv.o
    0001171c 0000d8 80016cfc  4 hitGrpFlagOn 	hitdrv.o
    00011644 0000d8 80016c24  4 hitGrpFlagOff 	hitdrv.o
    00011570 0000d4 80016b50  4 hitObjAttrOn 	hitdrv.o
    0001149c 0000d4 80016a7c  4 hitObjAttrOff 	hitdrv.o
    0001118c 000310 8001676c  4 hitAtrOn 	hitdrv.o
    00010e78 000314 80016458  4 hitAtrOff 	hitdrv.o
    00010da0 0000d8 80016380  4 hitGrpAttrOn 	hitdrv.o
    00010cc8 0000d8 800162a8  4 hitGrpAttrOff 	hitdrv.o
    00010c68 000060 80016248  4 hitReCalcMatrix 	hitdrv.o
    000107bc 0004ac 80015d9c  4 hitReCalcMatrix2 	hitdrv.o
    00010308 0004b4 800158e8  4 hitCalcVtxPosition 	hitdrv.o
    0000f878 000a90 80014e58  4 hitCheckVecFilter 	hitdrv.o
    0000f750 000128 80014d30  4 hitCheckFilter 	hitdrv.o
    0000f3a4 0003ac 80014984  4 checkTriVec_xz 	hitdrv.o
    0000f2c0 0000e4 800148a0  4 hitCheckVecHitObjXZ 	hitdrv.o
    0000f2a8 000018 80014888  4 chkFilterAttr 	hitdrv.o
    0000f174 000134 80014754  4 hitCheckAttr 	hitdrv.o
    UNUSED   00002c ........ chkFilterAttr2 hitdrv.o
    UNUSED   000138 ........ hitCheckAttrOnly hitdrv.o
    0000ec18 00055c 800141f8  4 hitCheckSphereFilter 	hitdrv.o
    UNUSED   000088 ........ hitPreCheck hitdrv.o
    0000eb68 0000b0 80014148  4 hitNameToPtr 	hitdrv.o
    0000e5fc 00056c 80013bdc  4 hitObjGetPosSub 	hitdrv.o
    0000e4ac 000150 80013a8c  4 hitObjGetPos 	hitdrv.o
    0000e3d4 0000d8 800139b4  4 hitObjGetNormal 	hitdrv.o
    0000e3b8 00001c 80013998  4 hitGetName 	hitdrv.o
    0000e3a0 000018 80013980  4 hitGetAttr 	hitdrv.o
    0000e054 00034c 80013634  4 hitDamageReturnSet 	hitdrv.o
    0000df8c 0000c8 8001356c  4 hitGrpDamageReturnSet 	hitdrv.o
    0000df80 00000c 80013560  4 hitGetDamageReturnPos 	hitdrv.o
    0000de88 0000f8 80013468  4 hitBindMapObj 	hitdrv.o
    0000dd7c 00010c 8001335c  4 hitBindUpdate 	hitdrv.o
    UNUSED   0006a4 ........ dbg_hitObjDisp hitdrv.o
    UNUSED   00022c ........ bounding_sphere hitdrv.o
    UNUSED   000528 ........ bounding_box hitdrv.o
    UNUSED   000038 ........ hitGetEntNum hitdrv.o
    UNUSED   00004c ........ hitNumberToPtr hitdrv.o
    0000dd7c 005e1c 8001335c  1 .text 	hitdrv.o
*/

s32 unk_8041840C;
HitEntry* unk_80418408; // TODO: proper name

// local prototypes
void hitReCalcMatrix2(HitEntry* hit, Mtx mtx, BOOL recursion);
s32 hitCalcVtxPosition(HitEntry* hit);

inline BOOL tempfunc(HitCheckQuery* query, HitVector* vector);
inline BOOL tempfunc2(HitCheckQuery* query, HitVector* vector);
inline BOOL tempfunc3(HitCheckQuery* query, HitVector* vector);
BOOL checkTriVec_xz(HitCheckQuery* query, HitVector* vector);
BOOL chkFilterAttr(HitCheckQuery* query, HitEntry* entry);
void hitObjGetPosSub(HitEntry* hit, Vec* position, s32* counter, BOOL recursion);
void hitDamageReturnSet(HitEntry* hit, HitDamageReturn* damage, BOOL recursion);
s32 hitGetEntNum(HitEntry* hitObject);

void hitInit(void) {
    ; // stubbed in retail
}

void hitReInit(void) {
    MapEntry* entry;
    MapWork* wp;
    s32 j;
    s32 i;
    HitEntry* hit;

    wp = mapGetWork();
    entry = wp->entries;
    for (i = 0; i < wp->entries->count; entry++, i++) {
        hit = entry->hitEntries;
        if (hit != NULL) {
            for (j = 0; j < entry->hitNumJoints; j++, hit++) {
                if (hit->vectors != NULL) {
                    _mapFree(hit->vectors);
                }
            }
            _mapFree(entry->hitEntries);
            entry->hitEntries = NULL;
            entry->hitNumJoints = 0;
        }
    }
}

// This function is cursed, managed to hit 99% - https://decomp.me/scratch/FjwSA
#ifdef NONMATCHING
HitEntry* _hitEnt(MapFileJoint* joint, HitEntry* parent, Mtx parentMtx, s32 mapIndex) {
    MapWork* wp = mapGetWork();
    HitEntry* hit = wp->entries[mapIndex].hitEntries;
    Mtx trans, scale, rotX, rotY, rotZ;
    Vec vtmp;
    s32 i;

    for (i = 0; i < wp->entries[mapIndex].hitNumJoints; hit++, i++) {
        if (!hit->joint) {
            break;
        }
    }

    hit->flags = 0;
    hit->joint = joint;
    hit->mapIndex = mapIndex;

    MTXTrans(trans, joint->translation.x, joint->translation.y, joint->translation.z);
    MTXScale(scale, joint->scale.x, joint->scale.y, joint->scale.z);
    MTXRotRad(rotX, 'x', MTXDegToRad(joint->rotation.x));
    MTXRotRad(rotY, 'y', MTXDegToRad(joint->rotation.y));
    MTXRotRad(rotZ, 'z', MTXDegToRad(joint->rotation.z));
    MTXConcat(trans, rotZ, trans);
    MTXConcat(trans, rotY, trans);
    MTXConcat(trans, rotX, trans);
    MTXConcat(trans, scale, hit->localMtx);
    MTXConcat(parentMtx, hit->localMtx, hit->worldMtx);

    hit->parent = parent;
    hit->sibling = NULL;
    hit->child = NULL;
    hit->vectors = NULL;

    if (joint->drawMode != NULL) {
        hit->attributes = joint->drawMode->unk8;
    } else {
        hit->attributes = 0;
    }

    if (joint->partCount) {
        VECAdd(&joint->bboxMin, &joint->bboxMax, &hit->centerLocal);
        VECScale(&hit->centerLocal, &hit->centerLocal, 0.5f);
    } else {
        hit->centerLocal = joint->translation;
    }
    MTXMultVec(hit->worldMtx, &hit->centerLocal, &hit->centerWorld);

    joint->bboxMin.x -= 0.1f;
    joint->bboxMin.y -= 0.1f;
    joint->bboxMin.z -= 0.1f;
    joint->bboxMax.x += 0.1f;
    joint->bboxMax.y += 0.1f;
    joint->bboxMax.z += 0.1f;

    MTXMultVec(hit->worldMtx, &hit->joint->bboxMax, &vtmp);
    hit->radius = PSVECDistance(&vtmp, &hit->centerWorld);

    {
        s32 numVectors, j, k;
        s32 partIdx;
        for (numVectors = 0, partIdx = 0; partIdx < hit->joint->partCount; partIdx++) {
            MapFileMesh* mesh = hit->joint->parts[partIdx].mesh;
            if (mesh == NULL) {
                continue;
            }

            if (!mesh->isPackedDisplay) {
                for (j = 0; j < mesh->displayListCount; j++) {
                    numVectors += *(s32*)mesh->displayLists.normalLists[j] - 2;
                }
            } else {
                for (k = 0; k < mesh->displayListCount; k++) {
                    j = *(u16*)((u8*)mesh->displayLists.packedLists[k].offset + 1);
                    numVectors += j - 2;
                }
            }
        }

        if (numVectors > 0) {
            hit->vectors = _mapAlloc(sizeof(HitVector) * numVectors);
            hit->vectorCount = hitCalcVtxPosition(hit);
        }
    }
    return hit;
}
#endif

#ifdef NONMATCHING
HitEntry* hitEntrySub(MapFileJoint* joint, HitEntry* parent, Mtx parentMtx, BOOL ignoreSiblings, s32 mapIndex) {
    HitEntry* entry = _hitEnt(joint, parent, parentMtx, mapIndex);
    if (joint->child != NULL) {
        entry->child = hitEntrySub(joint->child, entry, entry->worldMtx, FALSE, mapIndex);
    }
    if (!ignoreSiblings && joint->next != NULL) {
        entry->sibling = hitEntrySub(joint->next, parent, parentMtx, FALSE, mapIndex);
    }
    return entry;
}
#endif

#ifdef NONMATCHING
HitEntry* hitEntry(MapFileJoint* root, Mtx rootMtx, s32 mapIndex) {
    MapWork* wp = mapGetWork();
    u32 size;

    wp->entries[mapIndex].hitNumJoints = mapGetJoints(root);
    size = OSRoundUp32B(((wp->entries[mapIndex].hitNumJoints + 128) * sizeof(HitEntry)));
    wp->entries[mapIndex].hitEntries = _mapAlloc(size);
    memset(wp->entries[mapIndex].hitEntries, 0, size);
    return hitEntrySub(root, NULL, rootMtx, TRUE, mapIndex);
}
#endif

#ifdef NONMATCHING
HitEntry* hitEntryMOBJ(MapFileJoint* joint, Mtx mtx) {
    MapWork* wp = mapGetWork();

    wp->entries[0].hitNumJoints += mapGetJoints(joint);
    return hitEntrySub(joint, NULL, mtx, TRUE, 0);
}
#endif

void mapCalcAnimMatrix(Mtx out, Mtx in, void* anim, void* joint);

typedef struct HitAnimJointList {
    s32 count;
    void* joints[1];
} HitAnimJointList;

inline void hitPreCheck(void) {
    MapEntry* entry;
    s32 i;
    s32 j;
    MapWork* wp = mapGetWork();
    HitEntry* hit;
    HitEntry* prev;

    prev = unk_80418408 = NULL;
    i = 0;
    entry = wp->entries;
    for (; i < wp->entries->count; entry++, i++) {
        hit = entry->hitEntries;
        for (j = 0; j < entry->hitNumJoints; j++, hit++) {
            if (hit->joint->partCount != 0 && !(hit->flags & 0x81)) {
                if (prev == NULL) {
                    unk_80418408 = hit;
                    prev = hit;
                } else {
                    prev->siblingActive = hit;
                    prev = hit;
                }
            }
        }
    }
    if (prev != NULL) {
        prev->siblingActive = NULL;
    }
}
inline HitEntry* hitNameToPtrNoChk(const char* name) {
    MapWork* wp = mapGetWork();
    MapEntry* map;
    HitEntry* hit;
    s32 i, j;

    map = wp->entries;
    for (i = 0; i < wp->entries->count; map++, i++) {
        hit = map->hitEntries;
        for (j = 0; j < map->hitNumJoints; j++, hit++) {
            if (!(hit->flags & 0x80) && !strcmp(hit->joint->name, name)) {
                return hit;
            }
        }
    }
    return NULL;
}

#ifdef NONMATCHING
void hitDelete(const char* name) {
    MapWork* wp = mapGetWork();
    s32 j;
    s32 i;

    for (i = 0; i < wp->entries->count; i++) {
        HitEntry* hit;

        for (j = 0, hit = wp->entries[i].hitEntries; j < wp->entries[i].hitNumJoints; j++, hit++) {
            if (hit->flags & 0x80) {
                continue;
            }
            if (strcmp(name, hit->joint->name) == 0) {
                hit->flags |= 0x80;
                hitPreCheck();
                return;
            }
        }
    }
}
#endif

#ifdef NONMATCHING
void hitMain(void) {
    void** joints;
    MapEntry* entry;
    MapWork* wp = mapGetWork();
    s32 j;
    s32 k;
    s32 i;
    MapEntryAnimData* anim;
    BOOL recalc;
    HitAnimJointList* list;
    HitEntry* hit;
    Mtx mtx;

    hitPreCheck();
    entry = wp->entries;
    for (i = 0; i < wp->entries->count; entry++, i++) {
        anim = entry->animData;
        for (recalc = FALSE, j = 0; j < entry->numAnims; j++, anim++) {
            list = *(HitAnimJointList**)(*(u8**)((u8*)anim + 0x18) + 0xC);
            if (!(anim->flags & 1)) {
                continue;
            }
            if ((anim->flags & 2) && (anim->flags & 0x1000)) {
                continue;
            }
            if (list == NULL) {
                continue;
            }
            joints = (void**)list;
            for (k = 0; k < list->count; joints++, k++) {
                hit = hitNameToPtr(*(const char**)joints[1]);
                if (hit != NULL) {
                    mapCalcAnimMatrix(hit->animMtx, hit->localMtx, anim, joints[1]);
                    recalc = TRUE;
                    hit->flags |= 0x10;
                    hit->flags |= 0x40;
                    anim->flags |= 0x1000;
                }
            }
        }
        if (recalc) {
            PSMTXScale(mtx, 10.0f, 10.0f, 10.0f);
            hitReCalcMatrix2(entry->rootHitObj, mtx, FALSE);
        }
    }
}
#endif


void hitFlgOn(HitEntry* hit, u16 mask, s32 r);
void hitFlgOff(HitEntry* hit, u16 mask, s32 r);
void hitAtrOn(HitEntry* hit, u32 mask, s32 r);
void hitAtrOff(HitEntry* hit, u32 mask, s32 r);

#ifdef NONMATCHING
void hitObjFlagOn(const char* name, u16 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hit->flags |= mask;
}
#endif

#ifdef NONMATCHING
void hitObjFlagOff(const char* name, u16 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hit->flags &= ~mask;
}
#endif

#ifdef NONMATCHING
void hitFlgOn(HitEntry* hit, u16 mask, s32 r) {
    hit->flags |= mask;
    if (hit->child != NULL) {
        hitFlgOn(hit->child, mask, 1);
    }
    if (r != 0 && hit->sibling != NULL) {
        hitFlgOn(hit->sibling, mask, 1);
    }
}
#endif

#ifdef NONMATCHING
void hitFlgOff(HitEntry* hit, u16 mask, s32 r) {
    hit->flags &= ~mask;
    if (hit->child != NULL) {
        hitFlgOff(hit->child, mask, 1);
    }
    if (r != 0 && hit->sibling != NULL) {
        hitFlgOff(hit->sibling, mask, 1);
    }
}
#endif

#ifdef NONMATCHING
void hitGrpFlagOn(const char* name, u16 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hitFlgOn(hit, mask, 0);
}
#endif

#ifdef NONMATCHING
void hitGrpFlagOff(const char* name, u16 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hitFlgOff(hit, mask, 0);
}
#endif


#ifdef NONMATCHING
void hitObjAttrOn(const char* name, u32 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hit->attributes |= mask;
}
#endif

#ifdef NONMATCHING
void hitObjAttrOff(const char* name, u32 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hit->attributes &= ~mask;
}
#endif

#ifdef NONMATCHING
void hitAtrOn(HitEntry* hit, u32 mask, s32 r) {
    hit->attributes |= mask;
    if (hit->child != NULL) {
        hitAtrOn(hit->child, mask, 1);
    }
    if (r != 0 && hit->sibling != NULL) {
        hitAtrOn(hit->sibling, mask, 1);
    }
}
#endif

#ifdef NONMATCHING
void hitAtrOff(HitEntry* hit, u32 mask, s32 r) {
    hit->attributes &= ~mask;
    if (hit->child != NULL) {
        hitAtrOff(hit->child, mask, 1);
    }
    if (r != 0 && hit->sibling != NULL) {
        hitAtrOff(hit->sibling, mask, 1);
    }
}
#endif


#ifdef NONMATCHING
void hitGrpAttrOn(const char* name, u32 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hitAtrOn(hit, mask, 0);
}
#endif

#ifdef NONMATCHING
void hitGrpAttrOff(const char* name, u32 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hitAtrOff(hit, mask, 0);
}
#endif

#ifdef NONMATCHING
void hitReCalcMatrix(HitEntry* hit, Mtx mtx) {
    Vec world;

    hit->flags |= 0x40;
    hitReCalcMatrix2(hit, mtx, FALSE);
    MTXMultVec(hit->worldMtx, &hit->joint->bboxMax, &world);
    hit->radius = PSVECDistance(&world, &hit->centerWorld);
}
#endif

#ifdef NONMATCHING
void hitReCalcMatrix2(HitEntry* hit, Mtx mtx, BOOL recursion) {
    int var_r3_3;

    var_r3_3 = 0;
    if (hit->flags & 0x40) {
        var_r3_3 = 1;
    }
    if (recursion != 0) {
        var_r3_3 = 1;
    }
    if (var_r3_3 != 0) {
        if (hit->flags & 0x10) {
            PSMTXConcat(mtx, hit->animMtx, hit->worldMtx);
        } else {
            PSMTXConcat(mtx, hit->localMtx, hit->worldMtx);
        }
        if (hit->flags & 0x20) {
            PSMTXConcat(hit->worldMtx, hit->mapObj->unkAC, hit->worldMtx);
        }
        PSMTXMultVec(hit->worldMtx, &hit->centerLocal, &hit->centerWorld);
        hitCalcVtxPosition(hit);
        hit->flags &= ~0x40;
        if (hit->child != NULL) {
            hitReCalcMatrix2(hit->child, hit->worldMtx, TRUE);
        }
        if (hit->sibling != NULL) {
            hitReCalcMatrix2(hit->sibling, mtx, recursion);
        }
    } else {
        if (hit->child != NULL) {
            hitReCalcMatrix2(hit->child, hit->worldMtx, recursion);
        }
        if (hit->sibling != NULL) {
            hitReCalcMatrix2(hit->sibling, mtx, recursion);
        }
    }
}
#endif

static inline f32 hitDequant(register s16* base, register s32 idx) {
    register f32 r;
    register s32 off = idx * 2;
    asm { psq_lx r, base, off, 1, 5 }
    return r;
}

#pragma dont_inline on
#ifdef NONMATCHING
s32 hitCalcVtxPosition(HitEntry* hit) {
    s32 k, j, i;
    s32 count = 0;
    MapFileMesh* mesh;
    MapWork* wp;
    Vec* pos;
    Vec a, b, c;

    if (hit->vectors == NULL) {
        return 0;
    }
    for (i = 0; i < hit->joint->partCount; i++) {
        mesh = hit->joint->parts[i].mesh;
        if (mesh == NULL) {
            continue;
        }
        if (!mesh->isPackedDisplay) {
            for (j = 0; j < mesh->displayListCount; j++) {
                s32* list = (s32*)mesh->displayLists.normalLists[j];
                for (k = 0; k < *list - 2; k++) {
                    HitVector* vec;
                    s16 i1, i2;
                    s16* idx = (s16*)((u8*)list + k * 0x18 + 4);
                    i1 = *(s16*)((u8*)list + (k + 1) * 0x18 + 4);
                    i2 = *(s16*)((u8*)list + (k + 2) * 0x18 + 4);
                    vec = &hit->vectors[count++];
                    pos = (Vec*)(*(u8**)mesh->vcdTableOffset + 4);
                    MTXMultVec(hit->worldMtx, &pos[*idx], &vec->v0);
                    MTXMultVec(hit->worldMtx, &pos[!(k & 1) ? i2 : i1], &vec->v1);
                    MTXMultVec(hit->worldMtx, &pos[!(k & 1) ? i1 : i2], &vec->v2);
                    PSVECSubtract(&vec->v2, &vec->v0, &vec->edge0);
                    PSVECSubtract(&vec->v0, &vec->v1, &vec->edge1);
                    PSVECSubtract(&vec->v1, &vec->v2, &vec->edge2);
                    PSVECCrossProduct(&vec->edge0, &vec->edge1, &vec->normal);
                }
            }
        } else {
            u32 m;
            u32 bit;
            s32 stride;
            wp = mapGetWork();
            stride = 0;
            for (bit = 0; bit < 12; bit++) {
                stride += ((u32)mesh->elementMask >> bit) & 1;
            }
            stride *= 2;
            for (k = 0; k < mesh->displayListCount; k++) {
                s32 n;
                u8* list = (u8*)mesh->displayLists.packedLists[k].offset;
                n = *(u16*)(list + 1) - 2;
                for (j = 0; j < n; j++) {
                    u16 i0, i1, i2;
                    s32 o0, o1, o2;
                    BOOL even;
                    s16* base;
                    register u32 gqr;
                    HitVector* v2;
                    i0 = *(u16*)(list + j * stride + 3);
                    even = !(j & 1);
                    i1 = *(u16*)&list[stride * (j + 1) + 3];
                    i2 = *(u16*)&list[stride * (j + 2) + 3];
                    v2 = &hit->vectors[count];
                    base = (s16*)(*(u8**)mesh->vcdTableOffset + 4);
                    o0 = i0 * 3;
                    o1 = (u16)(even ? i2 : i1) * 3;
                    o2 = (u16)(even ? i1 : i2) * 3;
                    gqr = (*(s32*)(*(u8**)((u8*)&wp->entries[hit->mapIndex] + 0xA4) + 0x44) << 8) | 7;
                    gqr |= gqr << 16;
                    asm { mtspr GQR5, gqr }
                    a.x = hitDequant(base, o0);
                    a.y = hitDequant(base, o0 + 1);
                    a.z = hitDequant(base, o0 + 2);
                    b.x = hitDequant(base, o1);
                    b.y = hitDequant(base, o1 + 1);
                    b.z = hitDequant(base, o1 + 2);
                    c.x = hitDequant(base, o2);
                    c.y = hitDequant(base, o2 + 1);
                    c.z = hitDequant(base, o2 + 2);
                    MTXMultVec(hit->worldMtx, &a, &v2->v0);
                    MTXMultVec(hit->worldMtx, &b, &v2->v1);
                    MTXMultVec(hit->worldMtx, &c, &v2->v2);
                    PSVECSubtract(&v2->v2, &v2->v0, &v2->edge0);
                    PSVECSubtract(&v2->v0, &v2->v1, &v2->edge1);
                    PSVECSubtract(&v2->v1, &v2->v2, &v2->edge2);
                    PSVECCrossProduct(&v2->edge0, &v2->edge1, &v2->normal);
                    if (v2->normal.x || v2->normal.y || v2->normal.z) {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}
#endif
#pragma dont_inline reset

inline BOOL tempfunc(HitCheckQuery* query, HitVector* vector) {
    Vec sp80;
    Vec sp8C;
    Vec sp98;
    f32 dotProduct;
    f32 temp_f2;

    PSVECSubtract(&query->targetPos, &vector->v0, &sp80);
    dotProduct = PSVECDotProduct(&vector->normal, &sp80);
    if (query->singleSided) {
        if (dotProduct < 0.0f) {
            return 0;
        }
        if (((sp80.z * vector->edge0.x) - (sp80.x * vector->edge0.z)) < 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp8C);
        if (((sp8C.z * vector->edge1.x) - (sp8C.x * vector->edge1.z)) < 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp98);
        if (((sp98.z * vector->edge2.x) - (sp98.x * vector->edge2.z)) < 0.0f) {
            return 0;
        }
    } else {
        if ((vector->normal.y * dotProduct) <= 0.0f) {
            return 0;
        }
        if ((dotProduct * ((sp80.z * vector->edge0.x) - (sp80.x * vector->edge0.z))) < 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp8C);
        if ((dotProduct * ((sp8C.z * vector->edge1.x) - (sp8C.x * vector->edge1.z))) < 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp98);
        if ((dotProduct * ((sp98.z * vector->edge2.x) - (sp98.x * vector->edge2.z))) < 0.0f) {
            return 0;
        }
    }
    temp_f2 = -vector->normal.y;
    if ((query->targetDistance >= 0.0f) && ((-dotProduct / temp_f2) >= query->targetDistance)) {
        return 0;
    }
    query->targetDistance = -dotProduct / temp_f2;
    query->hitPos.x = query->targetPos.x;
    query->hitPos.y = query->targetPos.y - query->targetDistance;
    query->hitPos.z = query->targetPos.z;
    if (dotProduct >= 0.0f) {
        query->hitNormal = vector->normal;
    } else {
        PSVECScale(&vector->normal, &query->hitNormal, -1.0f);
    }
    return 1;
}

inline BOOL tempfunc2(HitCheckQuery* query, HitVector* vector) {
    Vec sp5C;
    Vec sp68;
    Vec sp74;
    f32 dotProduct;
    f32 temp_f2;

    PSVECSubtract(&query->targetPos, &vector->v0, &sp5C);
    dotProduct = PSVECDotProduct(&vector->normal, &sp5C);
    if (query->singleSided) {
        if (dotProduct < 0.0f) {
            return 0;
        }
        if (((sp5C.z * vector->edge0.x) - (sp5C.x * vector->edge0.z)) > 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp68);
        if (((sp68.z * vector->edge1.x) - (sp68.x * vector->edge1.z)) > 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp74);
        if (((sp74.z * vector->edge2.x) - (sp74.x * vector->edge2.z)) > 0.0f) {
            return 0;
        }
    } else {
        if ((vector->normal.y * dotProduct) >= 0.0f) {
            return 0;
        }
        if ((dotProduct * ((sp5C.z * vector->edge0.x) - (sp5C.x * vector->edge0.z))) > 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp68);
        if ((dotProduct * ((sp68.z * vector->edge1.x) - (sp68.x * vector->edge1.z))) > 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp74);
        if ((dotProduct * ((sp74.z * vector->edge2.x) - (sp74.x * vector->edge2.z))) > 0.0f) {
            return 0;
        }
    }
    temp_f2 = vector->normal.y;
    if ((query->targetDistance >= 0.0f) && ((-dotProduct / temp_f2) >= query->targetDistance)) {
        return 0;
    }
    query->targetDistance = -dotProduct / temp_f2;
    query->hitPos.x = query->targetPos.x;
    query->hitPos.y = query->targetPos.y + query->targetDistance;
    query->hitPos.z = query->targetPos.z;
    if (dotProduct >= 0.0f) {
        query->hitNormal = vector->normal;
    } else {
        PSVECScale(&vector->normal, &query->hitNormal, -1.0f);
    }
    return 1;
}

inline BOOL tempfunc3(HitCheckQuery* query, HitVector* vector) {
    Vec sp8;
    Vec sp14;
    Vec sp20;
    Vec sp2C;
    Vec sp38;
    Vec sp44;
    Vec sp50;
    f32 dotProduct;
    f32 var_f27;

    PSVECSubtract(&query->targetPos, &vector->v0, &sp8);
    dotProduct = PSVECDotProduct(&vector->normal, &sp8);
    if (query->singleSided) {
        if (dotProduct < 0.0f) {
            return 0;
        }
        PSVECCrossProduct(&query->targetDir, &vector->edge0, &sp2C);
        if (PSVECDotProduct(&sp8, &sp2C) < 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp14);
        PSVECCrossProduct(&query->targetDir, &vector->edge1, &sp38);
        if (PSVECDotProduct(&sp14, &sp38) < 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp20);
        PSVECCrossProduct(&query->targetDir, &vector->edge2, &sp44);
        if (PSVECDotProduct(&sp20, &sp44) < 0.0f) {
            return 0;
        }
        var_f27 = PSVECDotProduct(&vector->normal, &query->targetDir);
    } else {
        var_f27 = PSVECDotProduct(&vector->normal, &query->targetDir);
        if ((var_f27 * dotProduct) >= 0.0f) {
            return 0;
        }
        PSVECCrossProduct(&query->targetDir, &vector->edge0, &sp2C);
        if ((dotProduct * PSVECDotProduct(&sp8, &sp2C)) < 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp14);
        PSVECCrossProduct(&query->targetDir, &vector->edge1, &sp38);
        if ((dotProduct * PSVECDotProduct(&sp14, &sp38)) < 0.0f) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp20);
        PSVECCrossProduct(&query->targetDir, &vector->edge2, &sp44);
        if ((dotProduct * PSVECDotProduct(&sp20, &sp44)) < 0.0f) {
            return 0;
        }
    }

    if ((query->targetDistance >= 0.0f) && ((-dotProduct / var_f27) >= query->targetDistance)) {
        return 0;
    }
    query->targetDistance = -dotProduct / var_f27;
    PSVECScale(&query->targetDir, &sp50, query->targetDistance);
    PSVECAdd(&query->targetPos, &sp50, &query->hitPos);
    if (dotProduct >= 0.0f) {
        query->hitNormal = vector->normal;
    } else {
        PSVECScale(&vector->normal, &query->hitNormal, -1.0f);
    }
    return 1;
}

#ifdef NONMATCHING
HitEntry* hitCheckVecFilter(HitCheckQuery* query, HitFilterCallback callback) { // 1:1
    f32 temp;
    HitVector* vector;
    Vec position;
    Vec spBC;
    Vec normal;
    Vec spA4;
    HitEntry* var_r29;
    HitEntry* var_r28;
    int i;
    f32 distance;
    f32 var_f29;
    HitVector* var_r31;
    f32 temp_f28;

    mapGetWork();
    var_r28 = NULL;
    if (!PSVECSquareMag(&query->targetDir)) {
        return NULL;
    }
    var_f29 = -1.0f;
    temp = 0.5f;
    temp_f28 = query->targetDistance * temp;
    PSVECScale(&query->targetDir, &spA4, temp_f28);
    PSVECAdd(&query->targetPos, &spA4, &spA4);
    var_r29 = unk_80418408;
    if (query->targetDir.y == 0.0f) {
        while (var_r29 != NULL) {
            if (callback == NULL || callback(query, var_r29)) {
                if (!(PSVECDistance(&spA4, &var_r29->centerWorld) > temp_f28 + var_r29->radius)) {
                    if (var_r29->joint->drawMode->cullMode == 1) {
                        query->singleSided = 1;
                    } else {
                        query->singleSided = 0;
                    }
                    var_r31 = var_r29->vectors;
                    for (i = 0; i < var_r29->vectorCount; i++, var_r31++) {
                        if ((query->singleSided == 0) ||
                            !(PSVECDotProduct(&var_r31->normal, &query->targetDir) >= 0.0f)) {
                            if (checkTriVec_xz(query, var_r31) && (var_f29 < 0.0f || var_f29 > query->targetDistance)) {
                                var_f29 = query->targetDistance;
                                var_r28 = var_r29;
                                distance = var_f29;
                                position = query->hitPos;
                                spBC = query->hitNormal;
                            }
                        }
                    }
                }
            }
            var_r29 = var_r29->siblingActive;
        }
    } else if (query->targetDir.x == 0.0f && query->targetDir.z == 0.0f) {
        if (query->targetDir.y == -1.0f) {
            while (var_r29 != NULL) {
                if (callback == NULL || callback(query, var_r29)) {
                    if (!(PSVECDistance(&spA4, &var_r29->centerWorld) > temp_f28 + var_r29->radius)) {
                        if (var_r29->joint->drawMode->cullMode == 1) {
                            query->singleSided = 1;
                        } else {
                            query->singleSided = 0;
                        }
                        vector = var_r29->vectors;
                        for (i = 0; i < var_r29->vectorCount; i++, vector++) {
                            if (query->singleSided == 0 || !(vector->normal.y <= 0.0f)) {
                                if (tempfunc(query, vector) && (var_f29 < 0.0f || var_f29 > query->targetDistance)) {
                                    var_f29 = query->targetDistance;
                                    var_r28 = var_r29;
                                    distance = var_f29;
                                    position = query->hitPos;
                                    spBC = query->hitNormal;
                                }
                            }
                        }
                    }
                }
                var_r29 = var_r29->siblingActive;
            }
        } else if (query->targetDir.y == 1.0f) {
            while (var_r29 != NULL) {
                if (callback == NULL || callback(query, var_r29)) {
                    if (!(PSVECDistance(&spA4, &var_r29->centerWorld) > temp_f28 + var_r29->radius)) {
                        if (var_r29->joint->drawMode->cullMode == 1) {
                            query->singleSided = 1;
                        } else {
                            query->singleSided = 0;
                        }
                        vector = var_r29->vectors;
                        for (i = 0; i < var_r29->vectorCount; i++, vector++) {
                            if (query->singleSided == 0 || !(vector->normal.y >= 0.0f)) {
                                if (tempfunc2(query, vector) && (var_f29 < 0.0f || var_f29 > query->targetDistance)) {
                                    var_f29 = query->targetDistance;
                                    var_r28 = var_r29;
                                    distance = var_f29;
                                    position = query->hitPos;
                                    spBC = query->hitNormal;
                                }
                            }
                        }
                    }
                }
                var_r29 = var_r29->siblingActive;
            }
        } else {
            goto label_235;
        }
    } else {
    label_235:
        while (var_r29 != NULL) {
            if (callback == NULL || callback(query, var_r29)) {
                if (!(PSVECDistance(&spA4, &var_r29->centerWorld) > (temp_f28 + var_r29->radius))) {
                    if (var_r29->joint->drawMode->cullMode == 1) {
                        query->singleSided = 1;
                    } else {
                        query->singleSided = 0;
                    }
                    vector = var_r29->vectors;
                    for (i = 0; i < var_r29->vectorCount; i++, vector++) {
                        if (query->singleSided == 0 || !(PSVECDotProduct(&vector->normal, &query->targetDir) >= 0.0f)) {
                            if (tempfunc3(query, vector) && (var_f29 < 0.0f || var_f29 > query->targetDistance)) {
                                var_f29 = query->targetDistance;
                                var_r28 = var_r29;
                                distance = var_f29;
                                position = query->hitPos;
                                spBC = query->hitNormal;
                            }
                        }
                    }
                }
            }
            var_r29 = var_r29->siblingActive;
        }
    }
    if (var_r28 == NULL) {
        return NULL;
    }
    PSVECNormalize(&spBC, &normal);
    query->targetDistance = distance;
    query->hitPos = position;
    query->hitNormal = normal;
    return var_r28;
}
#endif

#ifdef NONMATCHING
HitEntry* hitCheckFilter(HitFilterCallback callback, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX,
                         f32* hitNY, f32* hitNZ, f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz) { // 1:1
    HitCheckQuery temp;
    HitCheckQuery* query = &temp;
    HitEntry* entry;

    query->targetPos = (Vec){ x, y, z };
    query->targetDir = (Vec){ nx, ny, nz };
    query->targetDistance = *distance;
    entry = hitCheckVecFilter(query, callback);
    if (entry == NULL) {
        return NULL;
    }
    *distance = query->targetDistance;
    *hitX = query->hitPos.x;
    *hitY = query->hitPos.y;
    *hitZ = query->hitPos.z;
    *hitNX = query->hitNormal.x;
    *hitNY = query->hitNormal.y;
    *hitNZ = query->hitNormal.z;
    return entry;
}
#endif

#ifdef NONMATCHING
BOOL checkTriVec_xz(HitCheckQuery* query, HitVector* vector) {
    Vec v1, v2, v3;
    f32 cosAngle;
    f32 distToTrianglePlane;

    PSVECSubtract(&query->targetPos, &vector->v0, &v1);
    distToTrianglePlane = PSVECDotProduct(&vector->normal, &v1);
    if (query->singleSided != 0) {
        if (distToTrianglePlane < 0.0f) {
            return FALSE;
        }
        if ((v1.x * (-vector->edge0.y * query->targetDir.z)) +
                (v1.y * ((vector->edge0.x * query->targetDir.z) - (vector->edge0.z * query->targetDir.x))) +
                (v1.z * (vector->edge0.y * query->targetDir.x)) <
            0.0f) {
            return FALSE;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &v2);
        if ((v2.x * (-vector->edge1.y * query->targetDir.z)) +
                (v2.y * ((vector->edge1.x * query->targetDir.z) - (vector->edge1.z * query->targetDir.x))) +
                (v2.z * (vector->edge1.y * query->targetDir.x)) <
            0.0f) {
            return FALSE;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &v3);
        if ((v3.x * (-vector->edge2.y * query->targetDir.z)) +
                (v3.y * ((vector->edge2.x * query->targetDir.z) - (vector->edge2.z * query->targetDir.x))) +
                (v3.z * (vector->edge2.y * query->targetDir.x)) <
            0.0f) {
            return FALSE;
        }
    } else {
        if (((vector->normal.x * query->targetDir.x) + (vector->normal.z * query->targetDir.z)) * distToTrianglePlane >=
            0.0f) {
            return FALSE;
        }
        if (((v1.x * (-vector->edge0.y * query->targetDir.z)) +
             (v1.y * ((vector->edge0.x * query->targetDir.z) - (vector->edge0.z * query->targetDir.x))) +
             (v1.z * (vector->edge0.y * query->targetDir.x))) *
                distToTrianglePlane <
            0.0f) {
            return FALSE;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &v2);
        if (((v2.x * (-vector->edge1.y * query->targetDir.z)) +
             (v2.y * ((vector->edge1.x * query->targetDir.z) - (vector->edge1.z * query->targetDir.x))) +
             (v2.z * (vector->edge1.y * query->targetDir.x))) *
                distToTrianglePlane <
            0.0f) {
            return FALSE;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &v3);
        if (((v3.x * (-vector->edge2.y * query->targetDir.z)) +
             (v3.y * ((vector->edge2.x * query->targetDir.z) - (vector->edge2.z * query->targetDir.x))) +
             (v3.z * (vector->edge2.y * query->targetDir.x))) *
                distToTrianglePlane <
            0.0f) {
            return FALSE;
        }
    }
    cosAngle = (vector->normal.x * query->targetDir.x) + (vector->normal.z * query->targetDir.z);
    if (query->targetDistance >= 0.0f && -distToTrianglePlane / cosAngle >= query->targetDistance) {
        return FALSE;
    }
    query->targetDistance = -distToTrianglePlane / cosAngle;
    query->hitPos.x = query->targetPos.x + (query->targetDir.x * query->targetDistance);
    query->hitPos.y = query->targetPos.y;
    query->hitPos.z = query->targetPos.z + (query->targetDir.z * query->targetDistance);
    if (distToTrianglePlane >= 0.0f) {
        query->hitNormal = vector->normal;
    } else {
        PSVECScale(&vector->normal, &query->hitNormal, -1.0f);
    }
    return TRUE;
}
#endif

#ifdef NONMATCHING
BOOL hitCheckVecHitObjXZ(HitCheckQuery* query, HitEntry* entry) { // 1:1
    int i;
    HitVector* vector;

    if (entry->joint->drawMode->cullMode == 1) {
        query->singleSided = 1;
    } else {
        query->singleSided = 0;
    }
    vector = entry->vectors;
    for (i = 0; i < entry->vectorCount; i++, vector++) {
        if ((query->singleSided == 0 || !(PSVECDotProduct(&vector->normal, &query->targetDir) >= 0.0f)) &&
            checkTriVec_xz(query, vector)) {
            return 1;
        }
    }
    return 0;
}
#endif

#ifdef NONMATCHING
BOOL chkFilterAttr(HitCheckQuery* query, HitEntry* entry) { // 1:1
    return (entry->attributes & query->user0) == 0;
}
#endif

#ifdef NONMATCHING
HitEntry* hitCheckAttr(s32 user0, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX, f32* hitNY, f32* hitNZ,
                       f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz) { // 1:1
    HitCheckQuery temp;
    HitCheckQuery* query = &temp;
    HitEntry* entry;

    query->targetPos = (Vec){ x, y, z };
    query->targetDir = (Vec){ nx, ny, nz };
    query->targetDistance = *distance;
    query->user0 = user0;
    entry = hitCheckVecFilter(query, chkFilterAttr);
    if (entry == NULL) {
        return NULL;
    }
    *distance = query->targetDistance;
    *hitX = query->hitPos.x;
    *hitY = query->hitPos.y;
    *hitZ = query->hitPos.z;
    *hitNX = query->hitNormal.x;
    *hitNY = query->hitNormal.y;
    *hitNZ = query->hitNormal.z;
    return entry;
}
#endif

#ifdef NONMATCHING
HitEntry* hitCheckSphereFilter(HitFilterCallback callback, f32 x, f32 y, f32 z,
                               f32 distance) { // almost 1:1, stubborn regalloc
    MapEntry* map = mapGetWork()->entries;
    MapEntry* var_r31 = map;
    int i;
    Vec sp68;
    int j;
    HitEntry* var_r23;
    HitVector* vector;
    f32 var_f28;
    s32 objectId;
    s32 fl;
    f32 temp_f1;
    f32 var_f30;
    f32 var_f31;
    s32 entryId;
    s32 var_r29;
    HitCheckQuery temp;
    HitCheckQuery* query;
    HitEntry* temp_r27;

    var_f28 = -1.0f;
    objectId = -1;
    query = &temp;
    sp68 = (Vec){ x, y, z };
    for (i = 0; i < map->count; var_r31++, i++) {
        var_r23 = var_r31->hitEntries;
        for (j = 0; j < var_r31->hitNumJoints; j++, var_r23++) {
            if ((var_r23->attributes & 0x80000000) && (var_r23->joint->partCount != 0)) {
                var_r29 = var_r23->flags;
                if (!(var_r29 & 1) && !(var_r29 & 0x80)) {
                    temp_f1 = PSVECDistance(&sp68, &var_r23->centerWorld);
                    if (!(temp_f1 > (distance + var_r23->radius))) {
                        if (callback == NULL || callback(query, var_r23)) {
                            if (var_f28 < 0.0f || var_f28 > temp_f1) {
                                var_f28 = temp_f1;
                                var_f31 = var_r23->radius;
                                objectId = j;
                                entryId = i;
                            }
                        }
                    }
                }
            }
        }
    }
    if (objectId < 0) {
        return 0;
    }
    if (var_f28 < (0.5f * var_f31)) {
        return &map[entryId].hitEntries[objectId];
    }
    map = &map[entryId];
    temp_r27 = &map->hitEntries[objectId];
    PSVECSubtract(&temp_r27->centerWorld, &sp68, &query->targetDir);
    PSVECNormalize(&query->targetDir, &query->targetDir);
    var_f30 = -1.0f;
    fl = -1;
    query->targetPos = sp68;
    query->targetDistance = distance;
    if (temp_r27->joint->drawMode->cullMode == 1) {
        query->singleSided = 1;
    } else {
        query->singleSided = 0;
    }
    vector = temp_r27->vectors;
    for (i = 0; i < temp_r27->vectorCount; i++, vector++) {
        if ((query->singleSided == 0) || !(PSVECDotProduct(&vector->normal, &query->targetDir) >= 0.0f)) {
            if (tempfunc3(query, vector) && ((var_f30 < 0.0f) || (var_f30 > query->targetDistance))) {
                var_f30 = query->targetDistance;
                fl = 1;
            }
        }
    }
    if (var_f30 > distance) {
        return 0;
    }
    if (fl < 0) {
        return 0;
    }
    return &map->hitEntries[objectId];
}
#endif

#ifdef NONMATCHING
HitEntry* hitNameToPtr(const char* name) { // 1:1
    MapEntry* map;
    MapWork* wp = mapGetWork();
    int j;
    MapEntry* new_var;
    MapEntry* new_var2;
    int i;
    HitEntry* hit;

    if (name == NULL) {
        return NULL;
    }
    for (i = 0; i < wp->entries->count; i++) {
        map = &wp->entries[i];
        hit = map->hitEntries;
        for (j = 0; j < map->hitNumJoints; j++, hit++) {
            if (!(hit->flags & 0x80) && !strcmp(hit->joint->name, name)) {
                return hit;
            }
        }
    }

    return NULL;
}
#endif

#ifdef NONMATCHING
void hitObjGetPosSub(HitEntry* hit, Vec* position, s32* counter, BOOL recursion) { // 1:1, awful inlining
    Vec sp8;

    if (hit->child != NULL) {
        hitObjGetPosSub(hit->child, position, counter, 1);
    } else {
        PSMTXMultVec(hit->worldMtx, &hit->centerLocal, &sp8);
        PSVECAdd(position, &sp8, position);
        (*counter)++;
    }
    if (recursion) {
        if (hit->sibling != NULL) {
            hitObjGetPosSub(hit->sibling, position, counter, 1);
        }
    }
}
#endif

#ifdef NONMATCHING
void hitObjGetPos(const char* name, Vec* position) { // 1:1
    Vec spC;
    s32 counter;
    HitEntry* hit;

    counter = 0;
    spC = (Vec){ 0.0f, 0.0f, 0.0f };
    hit = hitNameToPtr(name);
    if (hit == NULL) {
        *position = (Vec){ 0.0f, 0.0f, 0.0f };
        return;
    }
    hitObjGetPosSub(hit, &spC, &counter, 0);
    PSVECScale(&spC, position, 1.0f / (f32)counter);
}
#endif

#ifdef NONMATCHING
void hitObjGetNormal(const char* name, Vec* normal) { // 1:1
    HitEntry* hit;

    hit = hitNameToPtr(name);
    if (hit != NULL && hit->joint->partCount > 0) {
        PSVECNormalize(&hit->vectors->normal, normal);
    }
}
#endif

#ifdef NONMATCHING
const char* hitGetName(HitEntry* hit) { // 1:1
    MapEntry* map;
    s32 count;
    int i;
    u32 start, size;

    if (hit == NULL) {
        return NULL;
    }
    map = mapGetWork()->entries;
    count = map->count;
    for (i = 0; i < count; map++, i++) {
        start = (u32)map->hitEntries;
        size = OSRoundUp32B((map->hitNumJoints + 0x80) * sizeof(HitEntry));
        if ((u32)hit >= start && (u32)hit < start + size) {
            break;
        }
    }
    if (i >= count) {
        return NULL;
    }
    return hit->joint->name;
}
#endif

#ifdef NONMATCHING
s32 hitGetAttr(HitEntry* hit) { // 1:1
    return hit != NULL ? hit->attributes : 0;
}
#endif

#ifdef NONMATCHING
void hitDamageReturnSet(HitEntry* hit, HitDamageReturn* damage, BOOL recursion) { // 1:1
    hit->attributes |= 0x40000000;
    hit->damage = damage;
    if (hit->child != NULL) {
        hitDamageReturnSet(hit->child, damage, TRUE);
    }
    if (recursion != 0) {
        if (hit->sibling != NULL) {
            hitDamageReturnSet(hit->sibling, damage, TRUE);
        }
    }
}
#endif

#ifdef NONMATCHING
void hitGrpDamageReturnSet(const char* name, HitDamageReturn* damage) { // 1:1
    HitEntry* hit;

    hit = hitNameToPtr(name);
    if (hit != NULL) {
        hitDamageReturnSet(hit, damage, FALSE);
    }
}
#endif

#ifdef NONMATCHING
Vec* hitGetDamageReturnPos(HitEntry* hit) {
    return &hit->damage->position;
}
#endif

#ifdef NONMATCHING
void hitBindMapObj(const char* hitName, const char* mapobjName) {
    HitEntry* hit;
    MapObject* mapObj;

    hit = hitNameToPtr(hitName);
    mapObj = mapGetMapObj(mapobjName);
    if (mapObj == NULL) {
        mapErrorEntry(0, mapobjName);
        return;
    }
    if (hit == NULL) {
        mapErrorEntry(1, hitName);
        return;
    }
    hit->mapObj = mapObj;
    hit->flags |= 0x20;
}
#endif

#ifdef NONMATCHING
void hitBindUpdate(const char* name) {
    HitEntry* parent;
    HitEntry* hit;
    Mtx mtx;

    hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    if (hit->flags & 0x20) {
        parent = hit->parent;
        if (parent != NULL) {
            hitReCalcMatrix(hit, parent->worldMtx);
            return;
        }
        PSMTXScale(mtx, 10.0f, 10.0f, 10.0f);
        hitReCalcMatrix(hit, mtx);
    }
}
#endif
/*
s32 hitGetEntNum(HitEntry* hit) {
    s32 numVectors;
    s32 i, j;

    numVectors = 0;
    for (i = 0; i < hit->joint->partCount; i++) {
        MapFileMesh* mesh = hit->joint->parts[i].mesh;
        if (mesh == NULL) {
            continue;
        }

        if (!mesh->isPackedDisplay) {
            DisplayList* dls = (DisplayList*)mesh->displayLists;
            for (j = 0; j < mesh->displayListCount; j++) {
                numVectors += *(u16*)((u8*)dls[j].offset + 1) - 2;
            }
        } else {
            PackedDisplayList* dls = (PackedDisplayList*)mesh->displayLists;
            for (j = 0; j < mesh->displayListCount; j++) {
                numVectors += *(u16*)((u8*)dls[j].offset + 1) - 2;
            }
        }
    }

    return numVectors;
}
*/

#ifdef NONMATCHING
void hitStrippedPool(f32* f) {
    f[0] = 0.0f;
    f[1] = 0.1f;
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: _hitEnt (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const u32 lbl_802C1538[1] = { 0x00000000 };
__declspec(section ".rodata") const f32 vec3_802c153c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1548[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1554[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1560[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c156c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1578[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c1584[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_802c1590 = 4503601774854144;
__declspec(section ".sdata2") const f32 float_0_80419758 = 0.0f;
__declspec(section ".sdata2") const f32 float_0p1_8041975c = 0.1f;
__declspec(section ".sdata2") const f32 float_10_80419760 = 10.0f;
__declspec(section ".sdata2") const f32 float_1_80419764 = 1.0f;
__declspec(section ".sdata2") const f32 float_neg1_80419768 = -1.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041976c = 0.5f;
__declspec(section ".sdata2") const f32 float_deg2rad_80419770 = 0.017453292f;
#pragma force_active on
#pragma explicit_zero_data on
#pragma force_active on
__declspec(section ".sdata2") const u32 gap_sdata2_80419774 = 0;
#pragma explicit_zero_data reset
#pragma force_active reset

asm void hitBindUpdate(const char* name) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stmw r26, 0x38(r1)
	mr r26, r3
	bl mapGetWork
	cmplwi r26, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @8
	mr r4, r26
	li r3, 0x1
	bl mapErrorEntry
	b @9
	@8:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 26, 26
	beq @9
	lwz r4, 0xd4(r31)
	cmplwi r4, 0x0
	beq @10
	mr r3, r31
	addi r4, r4, 0xc
	bl hitReCalcMatrix
	b @9
	@10:
	lfs f1, float_10_80419760(r2)
	addi r3, r1, 0x8
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	mr r3, r31
	addi r4, r1, 0x8
	bl hitReCalcMatrix
	@9:
	lmw r26, 0x38(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void hitBindMapObj(const char* hitName, const char* mapobjName) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r26, r4
	bl mapGetWork
	cmplwi r25, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	mr r3, r26
	bl mapGetMapObj
	cmplwi r3, 0x0
	bne @8
	mr r4, r26
	li r3, 0x0
	bl mapErrorEntry
	b @9
	@8:
	cmplwi r31, 0x0
	bne @10
	mr r4, r25
	li r3, 0x1
	bl mapErrorEntry
	b @9
	@10:
	stw r3, 0xd0(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x20
	sth r0, 0x0(r31)
	@9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm Vec* hitGetDamageReturnPos(HitEntry* hit) {
	nofralloc
	lwz r3, 0xb0(r3)
	addi r3, r3, 0x4
	blr
}

asm void hitGrpDamageReturnSet(const char* name, HitDamageReturn* damage) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r26, r4
	bl mapGetWork
	cmplwi r25, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	beq @8
	mr r3, r31
	mr r4, r26
	li r5, 0x0
	bl hitDamageReturnSet
	@8:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitDamageReturnSet(HitEntry* hit, HitDamageReturn* damage, BOOL recursion) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r30, r4
	mr r29, r3
	mr r31, r5
	lwz r0, 0x4(r3)
	oris r0, r0, 0x4000
	stw r0, 0x4(r3)
	stw r30, 0xb0(r3)
	lwz r28, 0xd8(r3)
	cmplwi r28, 0x0
	beq @1
	lwz r0, 0x4(r28)
	oris r0, r0, 0x4000
	stw r0, 0x4(r28)
	stw r30, 0xb0(r28)
	lwz r27, 0xd8(r28)
	cmplwi r27, 0x0
	beq @2
	lwz r0, 0x4(r27)
	oris r0, r0, 0x4000
	stw r0, 0x4(r27)
	stw r30, 0xb0(r27)
	lwz r26, 0xd8(r27)
	cmplwi r26, 0x0
	beq @3
	lwz r0, 0x4(r26)
	oris r0, r0, 0x4000
	stw r0, 0x4(r26)
	stw r30, 0xb0(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @4
	li r5, 0x1
	bl hitDamageReturnSet
	@4:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @3
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@3:
	lwz r26, 0xdc(r27)
	cmplwi r26, 0x0
	beq @2
	lwz r0, 0x4(r26)
	oris r0, r0, 0x4000
	stw r0, 0x4(r26)
	stw r30, 0xb0(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @5
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@5:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @2
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@2:
	lwz r26, 0xdc(r28)
	cmplwi r26, 0x0
	beq @1
	lwz r0, 0x4(r26)
	oris r0, r0, 0x4000
	stw r0, 0x4(r26)
	stw r30, 0xb0(r26)
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @6
	lwz r0, 0x4(r27)
	oris r0, r0, 0x4000
	stw r0, 0x4(r27)
	stw r30, 0xb0(r27)
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @7
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@7:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @6
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@6:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @1
	lwz r0, 0x4(r26)
	oris r0, r0, 0x4000
	stw r0, 0x4(r26)
	stw r30, 0xb0(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @8
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@8:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @1
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@1:
	cmpwi r31, 0x0
	beq @9
	lwz r26, 0xdc(r29)
	cmplwi r26, 0x0
	beq @9
	lwz r0, 0x4(r26)
	oris r0, r0, 0x4000
	stw r0, 0x4(r26)
	stw r30, 0xb0(r26)
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @10
	lwz r0, 0x4(r27)
	oris r0, r0, 0x4000
	stw r0, 0x4(r27)
	stw r30, 0xb0(r27)
	lwz r28, 0xd8(r27)
	cmplwi r28, 0x0
	beq @11
	lwz r0, 0x4(r28)
	oris r0, r0, 0x4000
	stw r0, 0x4(r28)
	stw r30, 0xb0(r28)
	lwz r3, 0xd8(r28)
	cmplwi r3, 0x0
	beq @12
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@12:
	lwz r3, 0xdc(r28)
	cmplwi r3, 0x0
	beq @11
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@11:
	lwz r27, 0xdc(r27)
	cmplwi r27, 0x0
	beq @10
	lwz r0, 0x4(r27)
	oris r0, r0, 0x4000
	stw r0, 0x4(r27)
	stw r30, 0xb0(r27)
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @13
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@13:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @10
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@10:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @9
	lwz r0, 0x4(r26)
	oris r0, r0, 0x4000
	stw r0, 0x4(r26)
	stw r30, 0xb0(r26)
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @14
	lwz r0, 0x4(r27)
	oris r0, r0, 0x4000
	stw r0, 0x4(r27)
	stw r30, 0xb0(r27)
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @15
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@15:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @14
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@14:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @9
	lwz r0, 0x4(r26)
	oris r0, r0, 0x4000
	stw r0, 0x4(r26)
	stw r30, 0xb0(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @16
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@16:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @9
	mr r4, r30
	li r5, 0x1
	bl hitDamageReturnSet
	@9:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 hitGetAttr(HitEntry* hit) {
	nofralloc
	cmplwi r3, 0x0
	beq @1
	lwz r3, 0x4(r3)
	blr
	@1:
	li r3, 0x0
	blr
}

asm const char* hitGetName(HitEntry* hit) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr. r31, r3
	bne @1
	li r3, 0x0
	b @2
	@1:
	bl mapGetWork
	lwz r5, 0x0(r3)
	li r6, 0x0
	mtctr r5
	cmpwi r5, 0x0
	ble @3
	@4:
	lwz r4, 0x158(r3)
	lwz r7, 0x15c(r3)
	addi r0, r4, 0x80
	mulli r4, r0, 0xe4
	cmplw r31, r7
	addi r0, r4, 0x1f
	clrrwi r0, r0, 5
	blt @5
	add r0, r7, r0
	cmplw r31, r0
	blt @3
	@5:
	addi r3, r3, 0x178
	addi r6, r6, 0x1
	bdnz @4
	@3:
	cmpw r6, r5
	blt @6
	li r3, 0x0
	b @2
	@6:
	lwz r3, 0x8(r31)
	lwz r3, 0x0(r3)
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void hitObjGetNormal(const char* name, Vec* normal) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r26, r4
	bl mapGetWork
	cmplwi r25, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	beq @8
	lwz r3, 0x8(r31)
	lwz r0, 0x5c(r3)
	cmpwi r0, 0x0
	ble @8
	lwz r3, 0xac(r31)
	mr r4, r26
	addi r3, r3, 0x48
	bl PSVECNormalize
	@8:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitObjGetPos(const char* name, Vec* position) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	lis r5, vec3_802c156c+0x8@ha
	stw r0, 0x44(r1)
	li r0, 0x0
	addi r6, r5, vec3_802c156c+0x8@l
	stmw r25, 0x24(r1)
	mr r25, r3
	mr r31, r4
	stw r0, 0x8(r1)
	lwz r5, 0x0(r6)
	lwz r3, 0x4(r6)
	lwz r0, 0x8(r6)
	stw r5, 0xc(r1)
	stw r3, 0x10(r1)
	stw r0, 0x14(r1)
	bl mapGetWork
	cmplwi r25, 0x0
	mr r27, r3
	bne @1
	li r30, 0x0
	b @2
	@1:
	mr r26, r27
	li r29, 0x0
	b @3
	@4:
	lwz r30, 0x15c(r26)
	li r28, 0x0
	b @5
	@6:
	lhz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r30)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r28, r28, 0x1
	addi r30, r30, 0xe4
	@5:
	lwz r0, 0x158(r26)
	cmpw r28, r0
	blt @6
	addi r26, r26, 0x178
	addi r29, r29, 0x1
	@3:
	lwz r0, 0x0(r27)
	cmpw r29, r0
	blt @4
	li r30, 0x0
	@2:
	cmplwi r30, 0x0
	bne @8
	lis r3, vec3_802c1578+0x8@ha
	addi r4, r3, vec3_802c1578+0x8@l
	lwz r3, 0x0(r4)
	lwz r0, 0x4(r4)
	stw r3, 0x0(r31)
	stw r0, 0x4(r31)
	lwz r0, 0x8(r4)
	stw r0, 0x8(r31)
	b @9
	@8:
	mr r3, r30
	addi r4, r1, 0xc
	addi r5, r1, 0x8
	li r6, 0x0
	bl hitObjGetPosSub
	lwz r4, 0x8(r1)
	lis r0, 0x4330
	stw r0, 0x18(r1)
	lis r3, double_to_int_802c1590@ha
	xoris r0, r4, 0x8000
	lfd f1, double_to_int_802c1590@l(r3)
	stw r0, 0x1c(r1)
	mr r4, r31
	lfs f2, float_1_80419764(r2)
	addi r3, r1, 0xc
	lfd f0, 0x18(r1)
	fsubs f0, f0, f1
	fdivs f1, f2, f0
	bl PSVECScale
	@9:
	lmw r25, 0x24(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void hitObjGetPosSub(HitEntry* hit, Vec* position, s32* counter, BOOL recursion) {
	nofralloc
	stwu r1, -0xe0(r1)
	mflr r0
	stw r0, 0xe4(r1)
	stmw r25, 0xc4(r1)
	mr r28, r3
	mr r31, r4
	mr r30, r5
	mr r29, r6
	lwz r27, 0xd8(r3)
	cmplwi r27, 0x0
	beq @1
	lwz r26, 0xd8(r27)
	cmplwi r26, 0x0
	beq @2
	lwz r25, 0xd8(r26)
	cmplwi r25, 0x0
	beq @3
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @4
	li r6, 0x1
	bl hitObjGetPosSub
	b @5
	@4:
	addi r3, r25, 0xc
	addi r4, r25, 0x9c
	addi r5, r1, 0x5c
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x5c
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@5:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @6
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @6
	@3:
	addi r3, r26, 0xc
	addi r4, r26, 0x9c
	addi r5, r1, 0x8c
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x8c
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@6:
	lwz r25, 0xdc(r26)
	cmplwi r25, 0x0
	beq @7
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @8
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @9
	@8:
	addi r3, r25, 0xc
	addi r4, r25, 0x9c
	addi r5, r1, 0x50
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x50
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@9:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @7
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @7
	@2:
	addi r3, r27, 0xc
	addi r4, r27, 0x9c
	addi r5, r1, 0xa4
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0xa4
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@7:
	lwz r25, 0xdc(r27)
	cmplwi r25, 0x0
	beq @10
	lwz r26, 0xd8(r25)
	cmplwi r26, 0x0
	beq @11
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @12
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @13
	@12:
	addi r3, r26, 0xc
	addi r4, r26, 0x9c
	addi r5, r1, 0x44
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x44
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@13:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @14
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @14
	@11:
	addi r3, r25, 0xc
	addi r4, r25, 0x9c
	addi r5, r1, 0x80
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x80
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@14:
	lwz r25, 0xdc(r25)
	cmplwi r25, 0x0
	beq @10
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @15
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @16
	@15:
	addi r3, r25, 0xc
	addi r4, r25, 0x9c
	addi r5, r1, 0x38
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x38
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@16:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @10
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @10
	@1:
	addi r3, r28, 0xc
	addi r4, r28, 0x9c
	addi r5, r1, 0xb0
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0xb0
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@10:
	cmpwi r29, 0x0
	beq @17
	lwz r25, 0xdc(r28)
	cmplwi r25, 0x0
	beq @17
	lwz r26, 0xd8(r25)
	cmplwi r26, 0x0
	beq @18
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @19
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @20
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @21
	@20:
	addi r3, r27, 0xc
	addi r4, r27, 0x9c
	addi r5, r1, 0x2c
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x2c
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@21:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @22
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @22
	@19:
	addi r3, r26, 0xc
	addi r4, r26, 0x9c
	addi r5, r1, 0x74
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x74
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@22:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @23
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @24
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @25
	@24:
	addi r3, r26, 0xc
	addi r4, r26, 0x9c
	addi r5, r1, 0x20
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x20
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@25:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @23
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @23
	@18:
	addi r3, r25, 0xc
	addi r4, r25, 0x9c
	addi r5, r1, 0x98
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x98
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@23:
	lwz r25, 0xdc(r25)
	cmplwi r25, 0x0
	beq @17
	lwz r26, 0xd8(r25)
	cmplwi r26, 0x0
	beq @26
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @27
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @28
	@27:
	addi r3, r26, 0xc
	addi r4, r26, 0x9c
	addi r5, r1, 0x14
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x14
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@28:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @29
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @29
	@26:
	addi r3, r25, 0xc
	addi r4, r25, 0x9c
	addi r5, r1, 0x68
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x68
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@29:
	lwz r25, 0xdc(r25)
	cmplwi r25, 0x0
	beq @17
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @30
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	b @31
	@30:
	addi r3, r25, 0xc
	addi r4, r25, 0x9c
	addi r5, r1, 0x8
	bl PSMTXMultVec
	mr r3, r31
	mr r5, r31
	addi r4, r1, 0x8
	bl PSVECAdd
	lwz r3, 0x0(r30)
	addi r0, r3, 0x1
	stw r0, 0x0(r30)
	@31:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @17
	mr r4, r31
	mr r5, r30
	li r6, 0x1
	bl hitObjGetPosSub
	@17:
	lmw r25, 0xc4(r1)
	lwz r0, 0xe4(r1)
	mtlr r0
	addi r1, r1, 0xe0
	blr
}

asm HitEntry* hitNameToPtr(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r26, r3
	bl mapGetWork
	cmplwi r26, 0x0
	mr r30, r3
	bne @1
	li r3, 0x0
	b @2
	@1:
	mr r31, r30
	li r28, 0x0
	b @3
	@4:
	lwz r27, 0x15c(r31)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r27)
	mr r4, r26
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	mr r3, r27
	b @2
	@7:
	addi r29, r29, 0x1
	addi r27, r27, 0xe4
	@5:
	lwz r0, 0x158(r31)
	cmpw r29, r0
	blt @6
	addi r31, r31, 0x178
	addi r28, r28, 0x1
	@3:
	lwz r0, 0x0(r30)
	cmpw r28, r0
	blt @4
	li r3, 0x0
	@2:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm HitEntry* hitCheckSphereFilter(HitFilterCallback callback, f32 x, f32 y, f32 z,
                               f32 distance) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stfd f31, 0x130(r1)
	psq_st f31, 0x138(r1), 0, 0
	stfd f30, 0x120(r1)
	psq_st f30, 0x128(r1), 0, 0
	stfd f29, 0x110(r1)
	psq_st f29, 0x118(r1), 0, 0
	stfd f28, 0x100(r1)
	psq_st f28, 0x108(r1), 0, 0
	stfd f27, 0xf0(r1)
	psq_st f27, 0xf8(r1), 0, 0
	stfd f26, 0xe0(r1)
	psq_st f26, 0xe8(r1), 0, 0
	stmw r23, 0xbc(r1)
	fmr f26, f1
	mr r25, r3
	fmr f27, f2
	fmr f30, f3
	fmr f29, f4
	bl mapGetWork
	lis r4, vec3_802c1560+0x8@ha
	mr r30, r3
	addi r5, r4, vec3_802c1560+0x8@l
	lfs f28, float_neg1_80419768(r2)
	lwz r4, 0x0(r5)
	mr r31, r30
	lwz r3, 0x4(r5)
	addi r26, r1, 0x74
	lwz r0, 0x8(r5)
	li r28, -0x1
	stw r4, 0x5c(r1)
	li r29, 0x0
	stw r3, 0x60(r1)
	stw r0, 0x64(r1)
	stfs f26, 0x5c(r1)
	stfs f27, 0x60(r1)
	lwz r4, 0x5c(r1)
	stfs f30, 0x64(r1)
	lwz r3, 0x60(r1)
	lwz r0, 0x64(r1)
	stw r4, 0x68(r1)
	stw r3, 0x6c(r1)
	stw r0, 0x70(r1)
	b @1
	@2:
	lwz r23, 0x15c(r31)
	li r24, 0x0
	b @3
	@4:
	lwz r0, 0x4(r23)
	clrrwi. r0, r0, 31
	beq @5
	lwz r3, 0x8(r23)
	lwz r0, 0x5c(r3)
	cmpwi r0, 0x0
	beq @5
	lhz r3, 0x0(r23)
	clrlwi. r0, r3, 31
	bne @5
	rlwinm. r0, r3, 0, 24, 24
	bne @5
	addi r3, r1, 0x68
	addi r4, r23, 0xc0
	bl PSVECDistance
	lfs f0, 0xcc(r23)
	fmr f30, f1
	fadds f0, f29, f0
	fcmpo cr0, f30, f0
	bgt @5
	cmplwi r25, 0x0
	beq @6
	mr r12, r25
	mr r3, r26
	mr r4, r23
	mtctr r12
	bctrl
	cmpwi r3, 0x0
	beq @5
	@6:
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f28, f0
	blt @7
	fcmpo cr0, f28, f30
	ble @5
	@7:
	fmr f28, f30
	lfs f31, 0xcc(r23)
	mr r28, r24
	mr r27, r29
	@5:
	addi r24, r24, 0x1
	addi r23, r23, 0xe4
	@3:
	lwz r0, 0x158(r31)
	cmpw r24, r0
	blt @4
	addi r31, r31, 0x178
	addi r29, r29, 0x1
	@1:
	lwz r0, 0x0(r30)
	cmpw r29, r0
	blt @2
	cmpwi r28, 0x0
	bge @8
	li r3, 0x0
	b @9
	@8:
	lfs f0, float_0p5_8041976c(r2)
	fmuls f0, f0, f31
	fcmpo cr0, f28, f0
	bge @10
	mulli r0, r27, 0x178
	add r3, r30, r0
	mulli r0, r28, 0xe4
	lwz r3, 0x15c(r3)
	add r3, r3, r0
	b @9
	@10:
	mulli r0, r27, 0x178
	addi r4, r1, 0x68
	addi r5, r26, 0x18
	add r30, r30, r0
	mulli r31, r28, 0xe4
	lwz r0, 0x15c(r30)
	add r27, r0, r31
	addi r3, r27, 0xc0
	bl PSVECSubtract
	addi r3, r26, 0x18
	mr r4, r3
	bl PSVECNormalize
	lwz r4, 0x68(r1)
	li r28, -0x1
	lwz r3, 0x6c(r1)
	lwz r0, 0x70(r1)
	stw r4, 0x80(r1)
	lfs f30, float_neg1_80419768(r2)
	stw r3, 0x84(r1)
	stw r0, 0x88(r1)
	stfs f29, 0xb0(r1)
	lwz r3, 0x8(r27)
	lwz r3, 0x58(r3)
	lbz r0, 0x1(r3)
	cmplwi r0, 0x1
	bne @11
	li r0, 0x1
	stw r0, 0x74(r1)
	b @12
	@11:
	li r0, 0x0
	stw r0, 0x74(r1)
	@12:
	lwz r23, 0xac(r27)
	li r25, 0x0
	b @13
	@14:
	lwz r0, 0x74(r1)
	cmpwi r0, 0x0
	beq @15
	addi r3, r23, 0x48
	addi r4, r26, 0x18
	bl PSVECDotProduct
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq @16
	@15:
	mr r4, r23
	addi r3, r26, 0xc
	addi r5, r1, 0x8
	bl PSVECSubtract
	addi r3, r23, 0x48
	addi r4, r1, 0x8
	bl PSVECDotProduct
	lwz r0, 0x74(r1)
	fmr f31, f1
	cmpwi r0, 0x0
	beq @17
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f31, f0
	bge @18
	li r0, 0x0
	b @19
	@18:
	addi r3, r26, 0x18
	addi r4, r23, 0x24
	addi r5, r1, 0x2c
	bl PSVECCrossProduct
	addi r3, r1, 0x8
	addi r4, r1, 0x2c
	bl PSVECDotProduct
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @20
	li r0, 0x0
	b @19
	@20:
	addi r3, r26, 0xc
	addi r4, r23, 0xc
	addi r5, r1, 0x14
	bl PSVECSubtract
	addi r3, r26, 0x18
	addi r4, r23, 0x30
	addi r5, r1, 0x38
	bl PSVECCrossProduct
	addi r3, r1, 0x14
	addi r4, r1, 0x38
	bl PSVECDotProduct
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @21
	li r0, 0x0
	b @19
	@21:
	addi r3, r26, 0xc
	addi r4, r23, 0x18
	addi r5, r1, 0x20
	bl PSVECSubtract
	addi r3, r26, 0x18
	addi r4, r23, 0x3c
	addi r5, r1, 0x44
	bl PSVECCrossProduct
	addi r3, r1, 0x20
	addi r4, r1, 0x44
	bl PSVECDotProduct
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @22
	li r0, 0x0
	b @19
	@22:
	addi r3, r23, 0x48
	addi r4, r26, 0x18
	bl PSVECDotProduct
	fmr f28, f1
	b @23
	@17:
	addi r3, r23, 0x48
	addi r4, r26, 0x18
	bl PSVECDotProduct
	fmr f28, f1
	lfs f0, float_0_80419758(r2)
	fmuls f1, f28, f31
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @24
	li r0, 0x0
	b @19
	@24:
	addi r3, r26, 0x18
	addi r4, r23, 0x24
	addi r5, r1, 0x2c
	bl PSVECCrossProduct
	addi r3, r1, 0x8
	addi r4, r1, 0x2c
	bl PSVECDotProduct
	fmuls f1, f31, f1
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @25
	li r0, 0x0
	b @19
	@25:
	addi r3, r26, 0xc
	addi r4, r23, 0xc
	addi r5, r1, 0x14
	bl PSVECSubtract
	addi r3, r26, 0x18
	addi r4, r23, 0x30
	addi r5, r1, 0x38
	bl PSVECCrossProduct
	addi r3, r1, 0x14
	addi r4, r1, 0x38
	bl PSVECDotProduct
	fmuls f1, f31, f1
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @26
	li r0, 0x0
	b @19
	@26:
	addi r3, r26, 0xc
	addi r4, r23, 0x18
	addi r5, r1, 0x20
	bl PSVECSubtract
	addi r3, r26, 0x18
	addi r4, r23, 0x3c
	addi r5, r1, 0x44
	bl PSVECCrossProduct
	addi r3, r1, 0x20
	addi r4, r1, 0x44
	bl PSVECDotProduct
	fmuls f1, f31, f1
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @23
	li r0, 0x0
	b @19
	@23:
	lfs f1, 0xb0(r1)
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @27
	fneg f0, f31
	fdivs f0, f0, f28
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne @27
	li r0, 0x0
	b @19
	@27:
	fneg f0, f31
	addi r3, r26, 0x18
	addi r4, r1, 0x50
	fdivs f1, f0, f28
	stfs f1, 0xb0(r1)
	bl PSVECScale
	addi r3, r26, 0xc
	addi r4, r1, 0x50
	addi r5, r26, 0x24
	bl PSVECAdd
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f31, f0
	cror eq, gt, eq
	bne @28
	lwz r3, 0x48(r23)
	lwz r0, 0x4c(r23)
	stw r3, 0xa4(r1)
	stw r0, 0xa8(r1)
	lwz r0, 0x50(r23)
	stw r0, 0xac(r1)
	b @29
	@28:
	lfs f1, float_neg1_80419768(r2)
	addi r3, r23, 0x48
	addi r4, r26, 0x30
	bl PSVECScale
	@29:
	li r0, 0x1
	@19:
	cmpwi r0, 0x0
	beq @16
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f30, f0
	blt @30
	lfs f0, 0xb0(r1)
	fcmpo cr0, f30, f0
	ble @16
	@30:
	lfs f30, 0xb0(r1)
	li r28, 0x1
	@16:
	addi r25, r25, 0x1
	addi r23, r23, 0x54
	@13:
	lha r0, 0xa8(r27)
	cmpw r25, r0
	blt @14
	fcmpo cr0, f30, f29
	ble @31
	li r3, 0x0
	b @9
	@31:
	cmpwi r28, 0x0
	bge @32
	li r3, 0x0
	b @9
	@32:
	lwz r0, 0x15c(r30)
	add r3, r0, r31
	@9:
	psq_l f31, 0x138(r1), 0, 0
	lfd f31, 0x130(r1)
	psq_l f30, 0x128(r1), 0, 0
	lfd f30, 0x120(r1)
	psq_l f29, 0x118(r1), 0, 0
	lfd f29, 0x110(r1)
	psq_l f28, 0x108(r1), 0, 0
	lfd f28, 0x100(r1)
	psq_l f27, 0xf8(r1), 0, 0
	lfd f27, 0xf0(r1)
	psq_l f26, 0xe8(r1), 0, 0
	lfd f26, 0xe0(r1)
	lmw r23, 0xbc(r1)
	lwz r0, 0x144(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm HitEntry* hitCheckAttr(s32 user0, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX, f32* hitNY, f32* hitNZ,
                       f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	lis r11, vec3_802c1548+0x8@ha
	lis r12, vec3_802c1554+0x8@ha
	stw r0, 0x94(r1)
	addi r0, r1, 0x20
	stmw r23, 0x6c(r1)
	addi r23, r11, vec3_802c1548+0x8@l
	addi r26, r12, vec3_802c1554+0x8@l
	lis r11, chkFilterAttr@ha
	mr r28, r7
	mr r25, r4
	addi r7, r11, chkFilterAttr@l
	mr r29, r8
	mr r30, r9
	mr r4, r7
	lwz r27, 0x0(r23)
	lwz r31, 0x4(r23)
	stw r27, 0x14(r1)
	mr r27, r6
	lwz r23, 0x8(r23)
	stw r31, 0x18(r1)
	mr r31, r10
	lwz r24, 0x0(r26)
	lwz r12, 0x4(r26)
	lwz r11, 0x8(r26)
	mr r26, r5
	stw r23, 0x1c(r1)
	stw r24, 0x8(r1)
	stw r12, 0xc(r1)
	stw r11, 0x10(r1)
	stfs f1, 0x14(r1)
	stfs f2, 0x18(r1)
	lwz r10, 0x14(r1)
	stfs f3, 0x1c(r1)
	lwz r9, 0x18(r1)
	stfs f4, 0x8(r1)
	lwz r8, 0x1c(r1)
	stfs f5, 0xc(r1)
	lwz r7, 0x8(r1)
	stfs f6, 0x10(r1)
	lwz r6, 0xc(r1)
	lwz r5, 0x10(r1)
	stw r10, 0x2c(r1)
	stw r9, 0x30(r1)
	stw r8, 0x34(r1)
	stw r7, 0x38(r1)
	stw r6, 0x3c(r1)
	stw r5, 0x40(r1)
	lfs f0, 0x0(r28)
	stw r3, 0x24(r1)
	mr r3, r0
	stfs f0, 0x5c(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lfs f0, 0x5c(r1)
	stfs f0, 0x0(r28)
	lfs f0, 0x44(r1)
	stfs f0, 0x0(r25)
	lfs f0, 0x48(r1)
	stfs f0, 0x0(r26)
	lfs f0, 0x4c(r1)
	stfs f0, 0x0(r27)
	lfs f0, 0x50(r1)
	stfs f0, 0x0(r29)
	lfs f0, 0x54(r1)
	stfs f0, 0x0(r30)
	lfs f0, 0x58(r1)
	stfs f0, 0x0(r31)
	@2:
	lmw r23, 0x6c(r1)
	lwz r0, 0x94(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm BOOL chkFilterAttr(HitCheckQuery* query, HitEntry* entry) {
	nofralloc
	lwz r4, 0x4(r4)
	lwz r0, 0x4(r3)
	and r0, r4, r0
	cntlzw r0, r0
	srwi r3, r0, 5
	blr
}

asm BOOL hitCheckVecHitObjXZ(HitCheckQuery* query, HitEntry* entry) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r29, r4
	mr r28, r3
	lwz r3, 0x8(r4)
	lwz r3, 0x58(r3)
	lbz r0, 0x1(r3)
	cmplwi r0, 0x1
	bne @1
	li r0, 0x1
	stw r0, 0x0(r28)
	b @2
	@1:
	li r0, 0x0
	stw r0, 0x0(r28)
	@2:
	lwz r30, 0xac(r29)
	li r31, 0x0
	lfs f31, float_0_80419758(r2)
	b @3
	@4:
	lwz r0, 0x0(r28)
	cmpwi r0, 0x0
	beq @5
	addi r3, r30, 0x48
	addi r4, r28, 0x18
	bl PSVECDotProduct
	fcmpo cr0, f1, f31
	cror eq, gt, eq
	beq @6
	@5:
	mr r3, r28
	mr r4, r30
	bl checkTriVec_xz
	cmpwi r3, 0x0
	beq @6
	li r3, 0x1
	b @7
	@6:
	addi r31, r31, 0x1
	addi r30, r30, 0x54
	@3:
	lha r0, 0xa8(r29)
	cmpw r31, r0
	blt @4
	li r3, 0x0
	@7:
	psq_l f31, 0x28(r1), 0, 0
	lwz r0, 0x34(r1)
	lfd f31, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm BOOL checkTriVec_xz(HitCheckQuery* query, HitVector* vector) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	mr r30, r3
	mr r31, r4
	addi r3, r30, 0xc
	addi r5, r1, 0x20
	bl PSVECSubtract
	addi r3, r31, 0x48
	addi r4, r1, 0x20
	bl PSVECDotProduct
	lwz r0, 0x0(r30)
	fmr f31, f1
	cmpwi r0, 0x0
	beq @1
	lfs f6, float_0_80419758(r2)
	fcmpo cr0, f31, f6
	bge @2
	li r3, 0x0
	b @3
	@2:
	lfs f4, 0x18(r30)
	lfs f0, 0x2c(r31)
	lfs f5, 0x28(r31)
	fmuls f0, f0, f4
	lfs f7, 0x20(r30)
	lfs f1, 0x24(r31)
	fneg f3, f5
	lfs f2, 0x24(r1)
	fmuls f5, f5, f4
	fmsubs f0, f1, f7, f0
	lfs f4, 0x20(r1)
	fmuls f1, f3, f7
	lfs f3, 0x28(r1)
	fmuls f0, f2, f0
	fmadds f0, f4, f1, f0
	fmadds f0, f3, f5, f0
	fcmpo cr0, f0, f6
	bge @4
	li r3, 0x0
	b @3
	@4:
	addi r3, r30, 0xc
	addi r4, r31, 0xc
	addi r5, r1, 0x14
	bl PSVECSubtract
	lfs f4, 0x18(r30)
	lfs f0, 0x38(r31)
	lfs f5, 0x34(r31)
	fmuls f0, f0, f4
	lfs f6, 0x20(r30)
	lfs f1, 0x30(r31)
	fneg f3, f5
	lfs f2, 0x18(r1)
	fmuls f5, f5, f4
	fmsubs f1, f1, f6, f0
	lfs f4, 0x14(r1)
	fmuls f3, f3, f6
	lfs f6, 0x1c(r1)
	lfs f0, float_0_80419758(r2)
	fmuls f1, f2, f1
	fmadds f1, f4, f3, f1
	fmadds f1, f6, f5, f1
	fcmpo cr0, f1, f0
	bge @5
	li r3, 0x0
	b @3
	@5:
	addi r3, r30, 0xc
	addi r4, r31, 0x18
	addi r5, r1, 0x8
	bl PSVECSubtract
	lfs f4, 0x18(r30)
	lfs f0, 0x44(r31)
	lfs f5, 0x40(r31)
	fmuls f0, f0, f4
	lfs f6, 0x20(r30)
	lfs f1, 0x3c(r31)
	fneg f3, f5
	lfs f2, 0xc(r1)
	fmuls f5, f5, f4
	fmsubs f1, f1, f6, f0
	lfs f4, 0x8(r1)
	fmuls f3, f3, f6
	lfs f6, 0x10(r1)
	lfs f0, float_0_80419758(r2)
	fmuls f1, f2, f1
	fmadds f1, f4, f3, f1
	fmadds f1, f6, f5, f1
	fcmpo cr0, f1, f0
	bge @6
	li r3, 0x0
	b @3
	@1:
	lfs f0, 0x50(r31)
	lfs f8, 0x20(r30)
	lfs f1, 0x48(r31)
	fmuls f0, f0, f8
	lfs f5, 0x18(r30)
	lfs f7, float_0_80419758(r2)
	fmadds f0, f1, f5, f0
	fmuls f0, f31, f0
	fcmpo cr0, f0, f7
	cror eq, gt, eq
	bne @7
	li r3, 0x0
	b @3
	@7:
	lfs f0, 0x2c(r31)
	lfs f6, 0x28(r31)
	fmuls f0, f0, f5
	lfs f1, 0x24(r31)
	fneg f3, f6
	lfs f2, 0x24(r1)
	lfs f4, 0x20(r1)
	fmuls f5, f6, f5
	fmsubs f0, f1, f8, f0
	lfs f6, 0x28(r1)
	fmuls f1, f3, f8
	fmuls f0, f2, f0
	fmadds f0, f4, f1, f0
	fmadds f0, f6, f5, f0
	fmuls f0, f31, f0
	fcmpo cr0, f0, f7
	bge @8
	li r3, 0x0
	b @3
	@8:
	addi r3, r30, 0xc
	addi r4, r31, 0xc
	addi r5, r1, 0x14
	bl PSVECSubtract
	lfs f4, 0x18(r30)
	lfs f0, 0x38(r31)
	lfs f5, 0x34(r31)
	fmuls f0, f0, f4
	lfs f6, 0x20(r30)
	lfs f1, 0x30(r31)
	fneg f3, f5
	lfs f2, 0x18(r1)
	fmuls f5, f5, f4
	fmsubs f1, f1, f6, f0
	lfs f4, 0x14(r1)
	fmuls f3, f3, f6
	lfs f6, 0x1c(r1)
	lfs f0, float_0_80419758(r2)
	fmuls f1, f2, f1
	fmadds f1, f4, f3, f1
	fmadds f1, f6, f5, f1
	fmuls f1, f31, f1
	fcmpo cr0, f1, f0
	bge @9
	li r3, 0x0
	b @3
	@9:
	addi r3, r30, 0xc
	addi r4, r31, 0x18
	addi r5, r1, 0x8
	bl PSVECSubtract
	lfs f4, 0x18(r30)
	lfs f0, 0x44(r31)
	lfs f5, 0x40(r31)
	fmuls f0, f0, f4
	lfs f6, 0x20(r30)
	lfs f1, 0x3c(r31)
	fneg f3, f5
	lfs f2, 0xc(r1)
	fmuls f5, f5, f4
	fmsubs f1, f1, f6, f0
	lfs f4, 0x8(r1)
	fmuls f3, f3, f6
	lfs f6, 0x10(r1)
	lfs f0, float_0_80419758(r2)
	fmuls f1, f2, f1
	fmadds f1, f4, f3, f1
	fmadds f1, f6, f5, f1
	fmuls f1, f31, f1
	fcmpo cr0, f1, f0
	bge @6
	li r3, 0x0
	b @3
	@6:
	lfs f2, 0x50(r31)
	lfs f1, 0x20(r30)
	lfs f4, 0x3c(r30)
	lfs f0, float_0_80419758(r2)
	fmuls f1, f2, f1
	lfs f3, 0x48(r31)
	lfs f2, 0x18(r30)
	fcmpo cr0, f4, f0
	fmadds f2, f3, f2, f1
	cror eq, gt, eq
	bne @10
	fneg f0, f31
	fdivs f0, f0, f2
	fcmpo cr0, f0, f4
	cror eq, gt, eq
	bne @10
	li r3, 0x0
	b @3
	@10:
	fneg f1, f31
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f31, f0
	fdivs f0, f1, f2
	stfs f0, 0x3c(r30)
	lfs f2, 0x18(r30)
	lfs f1, 0x3c(r30)
	lfs f0, 0xc(r30)
	fmadds f0, f2, f1, f0
	stfs f0, 0x24(r30)
	lfs f0, 0x10(r30)
	stfs f0, 0x28(r30)
	lfs f2, 0x20(r30)
	lfs f1, 0x3c(r30)
	lfs f0, 0x14(r30)
	fmadds f0, f2, f1, f0
	stfs f0, 0x2c(r30)
	cror eq, gt, eq
	bne @11
	lwz r3, 0x48(r31)
	lwz r0, 0x4c(r31)
	stw r3, 0x30(r30)
	stw r0, 0x34(r30)
	lwz r0, 0x50(r31)
	stw r0, 0x38(r30)
	b @12
	@11:
	lfs f1, float_neg1_80419768(r2)
	addi r3, r31, 0x48
	addi r4, r30, 0x30
	bl PSVECScale
	@12:
	li r3, 0x1
	@3:
	psq_l f31, 0x48(r1), 0, 0
	lwz r0, 0x54(r1)
	lfd f31, 0x40(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm HitEntry* hitCheckFilter(HitFilterCallback callback, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX,
                         f32* hitNY, f32* hitNZ, f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz) {
	nofralloc
	stwu r1, -0x90(r1)
	mflr r0
	lis r12, lbl_802C1538@ha
	lis r11, vec3_802c153c+0x8@ha
	stw r0, 0x94(r1)
	stmw r22, 0x68(r1)
	addi r24, r12, lbl_802C1538@l
	addi r12, r11, vec3_802c153c+0x8@l
	mr r28, r7
	mr r22, r3
	mr r25, r4
	mr r26, r5
	mr r27, r6
	mr r30, r9
	addi r3, r1, 0x20
	mr r31, r10
	mr r4, r22
	lwz r29, 0x0(r24)
	lwz r23, 0x4(r24)
	stw r29, 0x14(r1)
	mr r29, r8
	lwz r24, 0x8(r24)
	lwz r11, 0x0(r12)
	lwz r7, 0x4(r12)
	lwz r0, 0x8(r12)
	stw r23, 0x18(r1)
	stw r24, 0x1c(r1)
	stw r11, 0x8(r1)
	stw r7, 0xc(r1)
	stw r0, 0x10(r1)
	stfs f1, 0x14(r1)
	stfs f2, 0x18(r1)
	lwz r9, 0x14(r1)
	stfs f3, 0x1c(r1)
	lwz r8, 0x18(r1)
	stfs f4, 0x8(r1)
	lwz r7, 0x1c(r1)
	stfs f5, 0xc(r1)
	lwz r6, 0x8(r1)
	stfs f6, 0x10(r1)
	lwz r5, 0xc(r1)
	lwz r0, 0x10(r1)
	stw r9, 0x2c(r1)
	stw r8, 0x30(r1)
	stw r7, 0x34(r1)
	stw r6, 0x38(r1)
	stw r5, 0x3c(r1)
	stw r0, 0x40(r1)
	lfs f0, 0x0(r28)
	stfs f0, 0x5c(r1)
	bl hitCheckVecFilter
	cmplwi r3, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lfs f0, 0x5c(r1)
	stfs f0, 0x0(r28)
	lfs f0, 0x44(r1)
	stfs f0, 0x0(r25)
	lfs f0, 0x48(r1)
	stfs f0, 0x0(r26)
	lfs f0, 0x4c(r1)
	stfs f0, 0x0(r27)
	lfs f0, 0x50(r1)
	stfs f0, 0x0(r29)
	lfs f0, 0x54(r1)
	stfs f0, 0x0(r30)
	lfs f0, 0x58(r1)
	stfs f0, 0x0(r31)
	@2:
	lmw r22, 0x68(r1)
	lwz r0, 0x94(r1)
	mtlr r0
	addi r1, r1, 0x90
	blr
}

asm HitEntry* hitCheckVecFilter(HitCheckQuery* query, HitFilterCallback callback) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stfd f31, 0x130(r1)
	psq_st f31, 0x138(r1), 0, 0
	stfd f30, 0x120(r1)
	psq_st f30, 0x128(r1), 0, 0
	stfd f29, 0x110(r1)
	psq_st f29, 0x118(r1), 0, 0
	stfd f28, 0x100(r1)
	psq_st f28, 0x108(r1), 0, 0
	stfd f27, 0xf0(r1)
	psq_st f27, 0xf8(r1), 0, 0
	stmw r26, 0xd8(r1)
	mr r26, r3
	mr r27, r4
	bl mapGetWork
	addi r3, r26, 0x18
	li r28, 0x0
	bl PSVECSquareMag
	lfs f0, float_0_80419758(r2)
	fcmpu cr0, f1, f0
	bne @1
	li r3, 0x0
	b @2
	@1:
	lfs f1, 0x3c(r26)
	addi r3, r26, 0x18
	lfs f0, float_0p5_8041976c(r2)
	addi r4, r1, 0xa4
	lfs f29, float_neg1_80419768(r2)
	fmuls f28, f1, f0
	fmr f1, f28
	bl PSVECScale
	addi r4, r1, 0xa4
	addi r3, r26, 0xc
	mr r5, r4
	bl PSVECAdd
	lfs f1, float_0_80419758(r2)
	lfs f2, 0x1c(r26)
	lwz r29, unk_80418408(r13)
	fcmpu cr0, f1, f2
	bne @3
	b @4
	@5:
	cmplwi r27, 0x0
	beq @6
	mr r12, r27
	mr r3, r26
	mr r4, r29
	mtctr r12
	bctrl
	cmpwi r3, 0x0
	beq @7
	@6:
	addi r3, r1, 0xa4
	addi r4, r29, 0xc0
	bl PSVECDistance
	lfs f0, 0xcc(r29)
	fadds f0, f28, f0
	fcmpo cr0, f1, f0
	bgt @7
	lwz r3, 0x8(r29)
	lwz r3, 0x58(r3)
	lbz r0, 0x1(r3)
	cmplwi r0, 0x1
	bne @8
	li r0, 0x1
	stw r0, 0x0(r26)
	b @9
	@8:
	li r0, 0x0
	stw r0, 0x0(r26)
	@9:
	lwz r31, 0xac(r29)
	li r30, 0x0
	b @10
	@11:
	lwz r0, 0x0(r26)
	cmpwi r0, 0x0
	beq @12
	addi r3, r31, 0x48
	addi r4, r26, 0x18
	bl PSVECDotProduct
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq @13
	@12:
	mr r3, r26
	mr r4, r31
	bl checkTriVec_xz
	cmpwi r3, 0x0
	beq @13
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f29, f0
	blt @14
	lfs f0, 0x3c(r26)
	fcmpo cr0, f29, f0
	ble @13
	@14:
	lfs f29, 0x3c(r26)
	mr r28, r29
	lwz r6, 0x24(r26)
	lwz r5, 0x28(r26)
	fmr f30, f29
	lwz r4, 0x2c(r26)
	lwz r3, 0x30(r26)
	lwz r0, 0x34(r26)
	stw r6, 0xc8(r1)
	stw r3, 0xbc(r1)
	stw r0, 0xc0(r1)
	lwz r0, 0x38(r26)
	stw r5, 0xcc(r1)
	stw r4, 0xd0(r1)
	stw r0, 0xc4(r1)
	@13:
	addi r30, r30, 0x1
	addi r31, r31, 0x54
	@10:
	lha r0, 0xa8(r29)
	cmpw r30, r0
	blt @11
	@7:
	lwz r29, 0xe0(r29)
	@4:
	cmplwi r29, 0x0
	bne @5
	b @15
	@3:
	lfs f0, 0x18(r26)
	fcmpu cr0, f1, f0
	bne @16
	lfs f0, 0x20(r26)
	fcmpu cr0, f1, f0
	bne @16
	lfs f0, float_neg1_80419768(r2)
	fcmpu cr0, f0, f2
	bne @17
	b @18
	@19:
	cmplwi r27, 0x0
	beq @20
	mr r12, r27
	mr r3, r26
	mr r4, r29
	mtctr r12
	bctrl
	cmpwi r3, 0x0
	beq @21
	@20:
	addi r3, r1, 0xa4
	addi r4, r29, 0xc0
	bl PSVECDistance
	lfs f0, 0xcc(r29)
	fadds f0, f28, f0
	fcmpo cr0, f1, f0
	bgt @21
	lwz r3, 0x8(r29)
	lwz r3, 0x58(r3)
	lbz r0, 0x1(r3)
	cmplwi r0, 0x1
	bne @22
	li r0, 0x1
	stw r0, 0x0(r26)
	b @23
	@22:
	li r0, 0x0
	stw r0, 0x0(r26)
	@23:
	lwz r30, 0xac(r29)
	li r31, 0x0
	b @24
	@25:
	lwz r0, 0x0(r26)
	cmpwi r0, 0x0
	beq @26
	lfs f1, 0x4c(r30)
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	beq @27
	@26:
	mr r4, r30
	addi r3, r26, 0xc
	addi r5, r1, 0x80
	bl PSVECSubtract
	addi r3, r30, 0x48
	addi r4, r1, 0x80
	bl PSVECDotProduct
	lwz r0, 0x0(r26)
	fmr f31, f1
	cmpwi r0, 0x0
	beq @28
	lfs f3, float_0_80419758(r2)
	fcmpo cr0, f31, f3
	bge @29
	li r0, 0x0
	b @30
	@29:
	lfs f1, 0x80(r1)
	lfs f0, 0x2c(r30)
	lfs f2, 0x88(r1)
	fmuls f0, f1, f0
	lfs f1, 0x24(r30)
	fmsubs f0, f2, f1, f0
	fcmpo cr0, f0, f3
	bge @31
	li r0, 0x0
	b @30
	@31:
	addi r3, r26, 0xc
	addi r4, r30, 0xc
	addi r5, r1, 0x8c
	bl PSVECSubtract
	lfs f1, 0x8c(r1)
	lfs f0, 0x38(r30)
	lfs f3, 0x94(r1)
	fmuls f1, f1, f0
	lfs f2, 0x30(r30)
	lfs f0, float_0_80419758(r2)
	fmsubs f1, f3, f2, f1
	fcmpo cr0, f1, f0
	bge @32
	li r0, 0x0
	b @30
	@32:
	addi r3, r26, 0xc
	addi r4, r30, 0x18
	addi r5, r1, 0x98
	bl PSVECSubtract
	lfs f1, 0x98(r1)
	lfs f0, 0x44(r30)
	lfs f3, 0xa0(r1)
	fmuls f1, f1, f0
	lfs f2, 0x3c(r30)
	lfs f0, float_0_80419758(r2)
	fmsubs f1, f3, f2, f1
	fcmpo cr0, f1, f0
	bge @33
	li r0, 0x0
	b @30
	@28:
	lfs f0, 0x4c(r30)
	lfs f3, float_0_80419758(r2)
	fmuls f0, f0, f31
	fcmpo cr0, f0, f3
	cror eq, lt, eq
	bne @34
	li r0, 0x0
	b @30
	@34:
	lfs f1, 0x80(r1)
	lfs f0, 0x2c(r30)
	lfs f2, 0x88(r1)
	fmuls f0, f1, f0
	lfs f1, 0x24(r30)
	fmsubs f0, f2, f1, f0
	fmuls f0, f31, f0
	fcmpo cr0, f0, f3
	bge @35
	li r0, 0x0
	b @30
	@35:
	addi r3, r26, 0xc
	addi r4, r30, 0xc
	addi r5, r1, 0x8c
	bl PSVECSubtract
	lfs f1, 0x8c(r1)
	lfs f0, 0x38(r30)
	lfs f3, 0x94(r1)
	fmuls f1, f1, f0
	lfs f2, 0x30(r30)
	lfs f0, float_0_80419758(r2)
	fmsubs f1, f3, f2, f1
	fmuls f1, f31, f1
	fcmpo cr0, f1, f0
	bge @36
	li r0, 0x0
	b @30
	@36:
	addi r3, r26, 0xc
	addi r4, r30, 0x18
	addi r5, r1, 0x98
	bl PSVECSubtract
	lfs f1, 0x98(r1)
	lfs f0, 0x44(r30)
	lfs f3, 0xa0(r1)
	fmuls f1, f1, f0
	lfs f2, 0x3c(r30)
	lfs f0, float_0_80419758(r2)
	fmsubs f1, f3, f2, f1
	fmuls f1, f31, f1
	fcmpo cr0, f1, f0
	bge @33
	li r0, 0x0
	b @30
	@33:
	lfs f3, 0x3c(r26)
	lfs f0, float_0_80419758(r2)
	lfs f1, 0x4c(r30)
	fcmpo cr0, f3, f0
	fneg f2, f1
	cror eq, gt, eq
	bne @37
	fneg f0, f31
	fdivs f0, f0, f2
	fcmpo cr0, f0, f3
	cror eq, gt, eq
	bne @37
	li r0, 0x0
	b @30
	@37:
	fneg f1, f31
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f31, f0
	fdivs f0, f1, f2
	stfs f0, 0x3c(r26)
	lfs f0, 0xc(r26)
	stfs f0, 0x24(r26)
	lfs f1, 0x10(r26)
	lfs f0, 0x3c(r26)
	fsubs f0, f1, f0
	stfs f0, 0x28(r26)
	lfs f0, 0x14(r26)
	stfs f0, 0x2c(r26)
	cror eq, gt, eq
	bne @38
	lwz r3, 0x48(r30)
	lwz r0, 0x4c(r30)
	stw r3, 0x30(r26)
	stw r0, 0x34(r26)
	lwz r0, 0x50(r30)
	stw r0, 0x38(r26)
	b @39
	@38:
	lfs f1, float_neg1_80419768(r2)
	addi r3, r30, 0x48
	addi r4, r26, 0x30
	bl PSVECScale
	@39:
	li r0, 0x1
	@30:
	cmpwi r0, 0x0
	beq @27
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f29, f0
	blt @40
	lfs f0, 0x3c(r26)
	fcmpo cr0, f29, f0
	ble @27
	@40:
	lfs f29, 0x3c(r26)
	mr r28, r29
	lwz r6, 0x24(r26)
	lwz r5, 0x28(r26)
	fmr f30, f29
	lwz r4, 0x2c(r26)
	lwz r3, 0x30(r26)
	lwz r0, 0x34(r26)
	stw r6, 0xc8(r1)
	stw r3, 0xbc(r1)
	stw r0, 0xc0(r1)
	lwz r0, 0x38(r26)
	stw r5, 0xcc(r1)
	stw r4, 0xd0(r1)
	stw r0, 0xc4(r1)
	@27:
	addi r31, r31, 0x1
	addi r30, r30, 0x54
	@24:
	lha r0, 0xa8(r29)
	cmpw r31, r0
	blt @25
	@21:
	lwz r29, 0xe0(r29)
	@18:
	cmplwi r29, 0x0
	bne @19
	b @15
	@17:
	lfs f0, float_1_80419764(r2)
	fcmpu cr0, f0, f2
	bne @16
	b @41
	@42:
	cmplwi r27, 0x0
	beq @43
	mr r12, r27
	mr r3, r26
	mr r4, r29
	mtctr r12
	bctrl
	cmpwi r3, 0x0
	beq @44
	@43:
	addi r3, r1, 0xa4
	addi r4, r29, 0xc0
	bl PSVECDistance
	lfs f0, 0xcc(r29)
	fadds f0, f28, f0
	fcmpo cr0, f1, f0
	bgt @44
	lwz r3, 0x8(r29)
	lwz r3, 0x58(r3)
	lbz r0, 0x1(r3)
	cmplwi r0, 0x1
	bne @45
	li r0, 0x1
	stw r0, 0x0(r26)
	b @46
	@45:
	li r0, 0x0
	stw r0, 0x0(r26)
	@46:
	lwz r30, 0xac(r29)
	li r31, 0x0
	b @47
	@48:
	lwz r0, 0x0(r26)
	cmpwi r0, 0x0
	beq @49
	lfs f1, 0x4c(r30)
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq @50
	@49:
	mr r4, r30
	addi r3, r26, 0xc
	addi r5, r1, 0x5c
	bl PSVECSubtract
	addi r3, r30, 0x48
	addi r4, r1, 0x5c
	bl PSVECDotProduct
	lwz r0, 0x0(r26)
	fmr f31, f1
	cmpwi r0, 0x0
	beq @51
	lfs f3, float_0_80419758(r2)
	fcmpo cr0, f31, f3
	bge @52
	li r0, 0x0
	b @53
	@52:
	lfs f1, 0x5c(r1)
	lfs f0, 0x2c(r30)
	lfs f2, 0x64(r1)
	fmuls f0, f1, f0
	lfs f1, 0x24(r30)
	fmsubs f0, f2, f1, f0
	fcmpo cr0, f0, f3
	ble @54
	li r0, 0x0
	b @53
	@54:
	addi r3, r26, 0xc
	addi r4, r30, 0xc
	addi r5, r1, 0x68
	bl PSVECSubtract
	lfs f1, 0x68(r1)
	lfs f0, 0x38(r30)
	lfs f3, 0x70(r1)
	fmuls f1, f1, f0
	lfs f2, 0x30(r30)
	lfs f0, float_0_80419758(r2)
	fmsubs f1, f3, f2, f1
	fcmpo cr0, f1, f0
	ble @55
	li r0, 0x0
	b @53
	@55:
	addi r3, r26, 0xc
	addi r4, r30, 0x18
	addi r5, r1, 0x74
	bl PSVECSubtract
	lfs f1, 0x74(r1)
	lfs f0, 0x44(r30)
	lfs f3, 0x7c(r1)
	fmuls f1, f1, f0
	lfs f2, 0x3c(r30)
	lfs f0, float_0_80419758(r2)
	fmsubs f1, f3, f2, f1
	fcmpo cr0, f1, f0
	ble @56
	li r0, 0x0
	b @53
	@51:
	lfs f0, 0x4c(r30)
	lfs f3, float_0_80419758(r2)
	fmuls f0, f0, f31
	fcmpo cr0, f0, f3
	cror eq, gt, eq
	bne @57
	li r0, 0x0
	b @53
	@57:
	lfs f1, 0x5c(r1)
	lfs f0, 0x2c(r30)
	lfs f2, 0x64(r1)
	fmuls f0, f1, f0
	lfs f1, 0x24(r30)
	fmsubs f0, f2, f1, f0
	fmuls f0, f31, f0
	fcmpo cr0, f0, f3
	ble @58
	li r0, 0x0
	b @53
	@58:
	addi r3, r26, 0xc
	addi r4, r30, 0xc
	addi r5, r1, 0x68
	bl PSVECSubtract
	lfs f1, 0x68(r1)
	lfs f0, 0x38(r30)
	lfs f3, 0x70(r1)
	fmuls f1, f1, f0
	lfs f2, 0x30(r30)
	lfs f0, float_0_80419758(r2)
	fmsubs f1, f3, f2, f1
	fmuls f1, f31, f1
	fcmpo cr0, f1, f0
	ble @59
	li r0, 0x0
	b @53
	@59:
	addi r3, r26, 0xc
	addi r4, r30, 0x18
	addi r5, r1, 0x74
	bl PSVECSubtract
	lfs f1, 0x74(r1)
	lfs f0, 0x44(r30)
	lfs f3, 0x7c(r1)
	fmuls f1, f1, f0
	lfs f2, 0x3c(r30)
	lfs f0, float_0_80419758(r2)
	fmsubs f1, f3, f2, f1
	fmuls f1, f31, f1
	fcmpo cr0, f1, f0
	ble @56
	li r0, 0x0
	b @53
	@56:
	lfs f1, 0x3c(r26)
	lfs f0, float_0_80419758(r2)
	lfs f2, 0x4c(r30)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @60
	fneg f0, f31
	fdivs f0, f0, f2
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne @60
	li r0, 0x0
	b @53
	@60:
	fneg f1, f31
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f31, f0
	fdivs f0, f1, f2
	stfs f0, 0x3c(r26)
	lfs f0, 0xc(r26)
	stfs f0, 0x24(r26)
	lfs f1, 0x10(r26)
	lfs f0, 0x3c(r26)
	fadds f0, f1, f0
	stfs f0, 0x28(r26)
	lfs f0, 0x14(r26)
	stfs f0, 0x2c(r26)
	cror eq, gt, eq
	bne @61
	lwz r3, 0x48(r30)
	lwz r0, 0x4c(r30)
	stw r3, 0x30(r26)
	stw r0, 0x34(r26)
	lwz r0, 0x50(r30)
	stw r0, 0x38(r26)
	b @62
	@61:
	lfs f1, float_neg1_80419768(r2)
	addi r3, r30, 0x48
	addi r4, r26, 0x30
	bl PSVECScale
	@62:
	li r0, 0x1
	@53:
	cmpwi r0, 0x0
	beq @50
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f29, f0
	blt @63
	lfs f0, 0x3c(r26)
	fcmpo cr0, f29, f0
	ble @50
	@63:
	lfs f29, 0x3c(r26)
	mr r28, r29
	lwz r6, 0x24(r26)
	lwz r5, 0x28(r26)
	fmr f30, f29
	lwz r4, 0x2c(r26)
	lwz r3, 0x30(r26)
	lwz r0, 0x34(r26)
	stw r6, 0xc8(r1)
	stw r3, 0xbc(r1)
	stw r0, 0xc0(r1)
	lwz r0, 0x38(r26)
	stw r5, 0xcc(r1)
	stw r4, 0xd0(r1)
	stw r0, 0xc4(r1)
	@50:
	addi r31, r31, 0x1
	addi r30, r30, 0x54
	@47:
	lha r0, 0xa8(r29)
	cmpw r31, r0
	blt @48
	@44:
	lwz r29, 0xe0(r29)
	@41:
	cmplwi r29, 0x0
	bne @42
	b @15
	b @16
	@64:
	cmplwi r27, 0x0
	beq @65
	mr r12, r27
	mr r3, r26
	mr r4, r29
	mtctr r12
	bctrl
	cmpwi r3, 0x0
	beq @66
	@65:
	addi r3, r1, 0xa4
	addi r4, r29, 0xc0
	bl PSVECDistance
	lfs f0, 0xcc(r29)
	fadds f0, f28, f0
	fcmpo cr0, f1, f0
	bgt @66
	lwz r3, 0x8(r29)
	lwz r3, 0x58(r3)
	lbz r0, 0x1(r3)
	cmplwi r0, 0x1
	bne @67
	li r0, 0x1
	stw r0, 0x0(r26)
	b @68
	@67:
	li r0, 0x0
	stw r0, 0x0(r26)
	@68:
	lwz r30, 0xac(r29)
	li r31, 0x0
	b @69
	@70:
	lwz r0, 0x0(r26)
	cmpwi r0, 0x0
	beq @71
	addi r3, r30, 0x48
	addi r4, r26, 0x18
	bl PSVECDotProduct
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq @72
	@71:
	mr r4, r30
	addi r3, r26, 0xc
	addi r5, r1, 0x8
	bl PSVECSubtract
	addi r3, r30, 0x48
	addi r4, r1, 0x8
	bl PSVECDotProduct
	lwz r0, 0x0(r26)
	fmr f31, f1
	cmpwi r0, 0x0
	beq @73
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f31, f0
	bge @74
	li r0, 0x0
	b @75
	@74:
	addi r3, r26, 0x18
	addi r4, r30, 0x24
	addi r5, r1, 0x2c
	bl PSVECCrossProduct
	addi r3, r1, 0x8
	addi r4, r1, 0x2c
	bl PSVECDotProduct
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @76
	li r0, 0x0
	b @75
	@76:
	addi r3, r26, 0xc
	addi r4, r30, 0xc
	addi r5, r1, 0x14
	bl PSVECSubtract
	addi r3, r26, 0x18
	addi r4, r30, 0x30
	addi r5, r1, 0x38
	bl PSVECCrossProduct
	addi r3, r1, 0x14
	addi r4, r1, 0x38
	bl PSVECDotProduct
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @77
	li r0, 0x0
	b @75
	@77:
	addi r3, r26, 0xc
	addi r4, r30, 0x18
	addi r5, r1, 0x20
	bl PSVECSubtract
	addi r3, r26, 0x18
	addi r4, r30, 0x3c
	addi r5, r1, 0x44
	bl PSVECCrossProduct
	addi r3, r1, 0x20
	addi r4, r1, 0x44
	bl PSVECDotProduct
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @78
	li r0, 0x0
	b @75
	@78:
	addi r3, r30, 0x48
	addi r4, r26, 0x18
	bl PSVECDotProduct
	fmr f27, f1
	b @79
	@73:
	addi r3, r30, 0x48
	addi r4, r26, 0x18
	bl PSVECDotProduct
	fmr f27, f1
	lfs f0, float_0_80419758(r2)
	fmuls f1, f27, f31
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @80
	li r0, 0x0
	b @75
	@80:
	addi r3, r26, 0x18
	addi r4, r30, 0x24
	addi r5, r1, 0x2c
	bl PSVECCrossProduct
	addi r3, r1, 0x8
	addi r4, r1, 0x2c
	bl PSVECDotProduct
	fmuls f1, f31, f1
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @81
	li r0, 0x0
	b @75
	@81:
	addi r3, r26, 0xc
	addi r4, r30, 0xc
	addi r5, r1, 0x14
	bl PSVECSubtract
	addi r3, r26, 0x18
	addi r4, r30, 0x30
	addi r5, r1, 0x38
	bl PSVECCrossProduct
	addi r3, r1, 0x14
	addi r4, r1, 0x38
	bl PSVECDotProduct
	fmuls f1, f31, f1
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @82
	li r0, 0x0
	b @75
	@82:
	addi r3, r26, 0xc
	addi r4, r30, 0x18
	addi r5, r1, 0x20
	bl PSVECSubtract
	addi r3, r26, 0x18
	addi r4, r30, 0x3c
	addi r5, r1, 0x44
	bl PSVECCrossProduct
	addi r3, r1, 0x20
	addi r4, r1, 0x44
	bl PSVECDotProduct
	fmuls f1, f31, f1
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	bge @79
	li r0, 0x0
	b @75
	@79:
	lfs f1, 0x3c(r26)
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @83
	fneg f0, f31
	fdivs f0, f0, f27
	fcmpo cr0, f0, f1
	cror eq, gt, eq
	bne @83
	li r0, 0x0
	b @75
	@83:
	fneg f0, f31
	addi r3, r26, 0x18
	addi r4, r1, 0x50
	fdivs f0, f0, f27
	stfs f0, 0x3c(r26)
	lfs f1, 0x3c(r26)
	bl PSVECScale
	addi r3, r26, 0xc
	addi r4, r1, 0x50
	addi r5, r26, 0x24
	bl PSVECAdd
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f31, f0
	cror eq, gt, eq
	bne @84
	lwz r3, 0x48(r30)
	lwz r0, 0x4c(r30)
	stw r3, 0x30(r26)
	stw r0, 0x34(r26)
	lwz r0, 0x50(r30)
	stw r0, 0x38(r26)
	b @85
	@84:
	lfs f1, float_neg1_80419768(r2)
	addi r3, r30, 0x48
	addi r4, r26, 0x30
	bl PSVECScale
	@85:
	li r0, 0x1
	@75:
	cmpwi r0, 0x0
	beq @72
	lfs f0, float_0_80419758(r2)
	fcmpo cr0, f29, f0
	blt @86
	lfs f0, 0x3c(r26)
	fcmpo cr0, f29, f0
	ble @72
	@86:
	lfs f29, 0x3c(r26)
	mr r28, r29
	lwz r6, 0x24(r26)
	lwz r5, 0x28(r26)
	fmr f30, f29
	lwz r4, 0x2c(r26)
	lwz r3, 0x30(r26)
	lwz r0, 0x34(r26)
	stw r6, 0xc8(r1)
	stw r3, 0xbc(r1)
	stw r0, 0xc0(r1)
	lwz r0, 0x38(r26)
	stw r5, 0xcc(r1)
	stw r4, 0xd0(r1)
	stw r0, 0xc4(r1)
	@72:
	addi r31, r31, 0x1
	addi r30, r30, 0x54
	@69:
	lha r0, 0xa8(r29)
	cmpw r31, r0
	blt @70
	@66:
	lwz r29, 0xe0(r29)
	@16:
	cmplwi r29, 0x0
	bne @64
	@15:
	cmplwi r28, 0x0
	bne @87
	li r3, 0x0
	b @2
	@87:
	addi r3, r1, 0xbc
	addi r4, r1, 0xb0
	bl PSVECNormalize
	stfs f30, 0x3c(r26)
	mr r3, r28
	lwz r0, 0xc8(r1)
	lwz r4, 0xcc(r1)
	stw r0, 0x24(r26)
	lwz r0, 0xd0(r1)
	stw r4, 0x28(r26)
	stw r0, 0x2c(r26)
	lwz r4, 0xb0(r1)
	lwz r0, 0xb4(r1)
	stw r4, 0x30(r26)
	stw r0, 0x34(r26)
	lwz r0, 0xb8(r1)
	stw r0, 0x38(r26)
	@2:
	psq_l f31, 0x138(r1), 0, 0
	lfd f31, 0x130(r1)
	psq_l f30, 0x128(r1), 0, 0
	lfd f30, 0x120(r1)
	psq_l f29, 0x118(r1), 0, 0
	lfd f29, 0x110(r1)
	psq_l f28, 0x108(r1), 0, 0
	lfd f28, 0x100(r1)
	psq_l f27, 0xf8(r1), 0, 0
	lfd f27, 0xf0(r1)
	lmw r26, 0xd8(r1)
	lwz r0, 0x144(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm s32 hitCalcVtxPosition(HitEntry* hit) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stmw r16, 0x30(r1)
	mr r27, r3
	li r30, 0x0
	lwz r0, 0xac(r3)
	cmplwi r0, 0x0
	bne @1
	li r3, 0x0
	b @2
	@1:
	li r31, 0x0
	li r20, 0x0
	b @3
	@4:
	addi r0, r20, 0x64
	lwzx r29, r3, r0
	cmplwi r29, 0x0
	beq @5
	lbz r0, 0x3(r29)
	cmplwi r0, 0x0
	bne @6
	mr r25, r29
	li r17, 0x0
	b @7
	@8:
	lwz r19, 0x10(r25)
	mulli r16, r30, 0x54
	li r18, 0x0
	mr r28, r19
	b @9
	@10:
	addi r0, r18, 0x1
	addi r6, r18, 0x2
	lwz r4, 0xc(r29)
	mulli r7, r0, 0x18
	lha r0, 0x4(r28)
	addi r3, r27, 0xc
	lwz r5, 0xac(r27)
	addi r30, r30, 0x1
	lwz r4, 0x0(r4)
	add r23, r5, r16
	addi r5, r7, 0x4
	lhax r21, r19, r5
	mulli r6, r6, 0x18
	addi r24, r4, 0x4
	mr r5, r23
	addi r4, r6, 0x4
	addi r16, r16, 0x54
	mulli r0, r0, 0xc
	lhax r22, r19, r4
	add r4, r24, r0
	bl PSMTXMultVec
	clrlwi r0, r18, 31
	mr r3, r21
	cntlzw r0, r0
	srwi. r26, r0, 5
	beq @11
	mr r3, r22
	@11:
	extsh r0, r3
	addi r3, r27, 0xc
	mulli r0, r0, 0xc
	addi r5, r23, 0xc
	add r4, r24, r0
	bl PSMTXMultVec
	cmpwi r26, 0x0
	mr r0, r22
	addi r3, r27, 0xc
	beq @12
	mr r0, r21
	@12:
	extsh r0, r0
	addi r5, r23, 0x18
	mulli r0, r0, 0xc
	add r4, r24, r0
	bl PSMTXMultVec
	mr r4, r23
	addi r3, r23, 0x18
	addi r5, r23, 0x24
	bl PSVECSubtract
	mr r3, r23
	addi r4, r23, 0xc
	addi r5, r23, 0x30
	bl PSVECSubtract
	addi r3, r23, 0xc
	addi r4, r23, 0x18
	addi r5, r23, 0x3c
	bl PSVECSubtract
	addi r3, r23, 0x24
	addi r4, r23, 0x30
	addi r5, r23, 0x48
	bl PSVECCrossProduct
	addi r28, r28, 0x18
	addi r18, r18, 0x1
	@9:
	lwz r3, 0x0(r19)
	subi r0, r3, 0x2
	cmpw r18, r0
	blt @10
	addi r25, r25, 0x4
	addi r17, r17, 0x1
	@7:
	lwz r0, 0x4(r29)
	cmpw r17, r0
	blt @8
	b @5
	@6:
	bl mapGetWork
	lwz r12, 0x8(r29)
	li r16, 0x0
	li r10, 0x1
	li r9, 0x2
	srw r11, r12, r16
	li r8, 0x3
	srw r10, r12, r10
	srw r9, r12, r9
	srw r7, r12, r8
	li r6, 0x4
	srw r6, r12, r6
	li r5, 0x5
	srw r4, r12, r5
	clrlwi r11, r11, 31
	clrlwi r8, r10, 31
	li r16, 0x6
	li r10, 0x7
	clrlwi r5, r9, 31
	add r0, r11, r8
	srw r11, r12, r16
	srw r10, r12, r10
	li r9, 0x8
	add r0, r0, r5
	clrlwi r7, r7, 31
	srw r9, r12, r9
	li r8, 0x9
	add r0, r0, r7
	clrlwi r5, r6, 31
	srw r7, r12, r8
	li r6, 0xa
	add r0, r0, r5
	clrlwi r4, r4, 31
	srw r6, r12, r6
	li r5, 0xb
	add r0, r0, r4
	clrlwi r11, r11, 31
	srw r4, r12, r5
	clrlwi r8, r10, 31
	add r0, r0, r11
	clrlwi r5, r9, 31
	add r0, r0, r8
	clrlwi r7, r7, 31
	add r0, r0, r5
	clrlwi r5, r6, 31
	add r0, r0, r7
	clrlwi r4, r4, 31
	add r0, r0, r5
	lfs f31, float_0_80419758(r2)
	add r0, r0, r4
	mr r26, r3
	mulli r21, r30, 0x54
	mr r22, r29
	slwi r19, r0, 1
	li r18, 0x0
	b @13
	@14:
	lwz r16, 0x10(r22)
	li r17, 0x0
	mr r25, r21
	lhz r3, 0x1(r16)
	mr r24, r17
	subi r23, r3, 0x2
	b @15
	@16:
	addi r0, r17, 0x1
	addi r4, r17, 0x2
	mullw r5, r19, r0
	add r3, r16, r24
	clrlwi r0, r17, 31
	lwz r7, 0xc(r29)
	lhz r3, 0x3(r3)
	cntlzw r0, r0
	lwz r8, 0x0(r7)
	mullw r4, r19, r4
	lwz r7, 0xac(r27)
	add r5, r16, r5
	srwi. r6, r0, 5
	lhz r0, 0x3(r5)
	add r28, r7, r25
	add r5, r16, r4
	mulli r4, r3, 0x3
	lhz r9, 0x3(r5)
	mr r5, r0
	addi r3, r8, 0x4
	beq @17
	mr r5, r9
	@17:
	clrlwi r5, r5, 16
	cmpwi r6, 0x0
	mulli r5, r5, 0x3
	mr r6, r9
	beq @18
	mr r6, r0
	@18:
	lha r0, 0xaa(r27)
	clrlwi r6, r6, 16
	mulli r6, r6, 0x3
	mulli r7, r0, 0x178
	addi r0, r7, 0xa4
	lwzx r7, r26, r0
	lwz r0, 0x44(r7)
	slwi r0, r0, 8
	ori r7, r0, 0x7
	slwi r0, r7, 16
	or r0, r7, r0
	mtspr GQR5, r0
	slwi r0, r4, 1
	psq_lx f0, r3, r0, 1, 5
	addi r0, r4, 0x1
	slwi r0, r0, 1
	stfs f0, 0x20(r1)
	psq_lx f0, r3, r0, 1, 5
	addi r0, r4, 0x2
	slwi r0, r0, 1
	stfs f0, 0x24(r1)
	psq_lx f0, r3, r0, 1, 5
	slwi r0, r5, 1
	stfs f0, 0x28(r1)
	psq_lx f0, r3, r0, 1, 5
	addi r0, r5, 0x1
	slwi r0, r0, 1
	stfs f0, 0x14(r1)
	psq_lx f0, r3, r0, 1, 5
	addi r0, r5, 0x2
	slwi r0, r0, 1
	stfs f0, 0x18(r1)
	psq_lx f0, r3, r0, 1, 5
	slwi r0, r6, 1
	stfs f0, 0x1c(r1)
	psq_lx f0, r3, r0, 1, 5
	addi r0, r6, 0x1
	slwi r0, r0, 1
	stfs f0, 0x8(r1)
	psq_lx f0, r3, r0, 1, 5
	addi r0, r6, 0x2
	slwi r0, r0, 1
	stfs f0, 0xc(r1)
	psq_lx f0, r3, r0, 1, 5
	mr r5, r28
	addi r3, r27, 0xc
	addi r4, r1, 0x20
	stfs f0, 0x10(r1)
	bl PSMTXMultVec
	addi r3, r27, 0xc
	addi r4, r1, 0x14
	addi r5, r28, 0xc
	bl PSMTXMultVec
	addi r3, r27, 0xc
	addi r4, r1, 0x8
	addi r5, r28, 0x18
	bl PSMTXMultVec
	mr r4, r28
	addi r3, r28, 0x18
	addi r5, r28, 0x24
	bl PSVECSubtract
	mr r3, r28
	addi r4, r28, 0xc
	addi r5, r28, 0x30
	bl PSVECSubtract
	addi r3, r28, 0xc
	addi r4, r28, 0x18
	addi r5, r28, 0x3c
	bl PSVECSubtract
	addi r3, r28, 0x24
	addi r4, r28, 0x30
	addi r5, r28, 0x48
	bl PSVECCrossProduct
	lfs f0, 0x48(r28)
	fcmpu cr0, f0, f31
	bne @19
	lfs f0, 0x4c(r28)
	fcmpu cr0, f0, f31
	bne @19
	lfs f0, 0x50(r28)
	fcmpu cr0, f0, f31
	beq @20
	@19:
	addi r25, r25, 0x54
	addi r21, r21, 0x54
	addi r30, r30, 0x1
	@20:
	add r24, r24, r19
	addi r17, r17, 0x1
	@15:
	cmpw r17, r23
	blt @16
	addi r22, r22, 0x8
	addi r18, r18, 0x1
	@13:
	lwz r0, 0x4(r29)
	cmpw r18, r0
	blt @14
	@5:
	addi r20, r20, 0x8
	addi r31, r31, 0x1
	@3:
	lwz r3, 0x8(r27)
	lwz r0, 0x5c(r3)
	cmpw r31, r0
	blt @4
	mr r3, r30
	@2:
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	lmw r16, 0x30(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm void hitReCalcMatrix2(HitEntry* hit, Mtx mtx, BOOL recursion) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r5
	stw r30, 0x18(r1)
	mr r30, r4
	li r4, 0x0
	stw r29, 0x14(r1)
	mr r29, r3
	stw r28, 0x10(r1)
	lhz r3, 0x0(r3)
	rlwinm. r0, r3, 0, 25, 25
	beq @1
	li r4, 0x1
	@1:
	cmpwi r31, 0x0
	beq @2
	li r4, 0x1
	@2:
	cmpwi r4, 0x0
	beq @3
	rlwinm. r0, r3, 0, 27, 27
	beq @4
	mr r3, r30
	addi r4, r29, 0x6c
	addi r5, r29, 0xc
	bl PSMTXConcat
	b @5
	@4:
	mr r3, r30
	addi r4, r29, 0x3c
	addi r5, r29, 0xc
	bl PSMTXConcat
	@5:
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 26, 26
	beq @6
	lwz r4, 0xd0(r29)
	addi r3, r29, 0xc
	mr r5, r3
	addi r4, r4, 0xac
	bl PSMTXConcat
	@6:
	addi r3, r29, 0xc
	addi r4, r29, 0x9c
	addi r5, r29, 0xc0
	bl PSMTXMultVec
	mr r3, r29
	bl hitCalcVtxPosition
	lhz r0, 0x0(r29)
	rlwinm r0, r0, 0, 26, 24
	sth r0, 0x0(r29)
	lwz r28, 0xd8(r29)
	cmplwi r28, 0x0
	beq @7
	lhz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 27, 27
	beq @8
	addi r3, r29, 0xc
	addi r4, r28, 0x6c
	addi r5, r28, 0xc
	bl PSMTXConcat
	b @9
	@8:
	addi r3, r29, 0xc
	addi r4, r28, 0x3c
	addi r5, r28, 0xc
	bl PSMTXConcat
	@9:
	lhz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 26, 26
	beq @10
	lwz r4, 0xd0(r28)
	addi r3, r28, 0xc
	mr r5, r3
	addi r4, r4, 0xac
	bl PSMTXConcat
	@10:
	addi r3, r28, 0xc
	addi r4, r28, 0x9c
	addi r5, r28, 0xc0
	bl PSMTXMultVec
	mr r3, r28
	bl hitCalcVtxPosition
	lhz r0, 0x0(r28)
	rlwinm r0, r0, 0, 26, 24
	sth r0, 0x0(r28)
	lwz r3, 0xd8(r28)
	cmplwi r3, 0x0
	beq @11
	addi r4, r28, 0xc
	li r5, 0x1
	bl hitReCalcMatrix2
	@11:
	lwz r3, 0xdc(r28)
	cmplwi r3, 0x0
	beq @7
	addi r4, r29, 0xc
	li r5, 0x1
	bl hitReCalcMatrix2
	@7:
	lwz r28, 0xdc(r29)
	cmplwi r28, 0x0
	beq @12
	lhz r4, 0x0(r28)
	li r3, 0x0
	rlwinm. r0, r4, 0, 25, 25
	beq @13
	li r3, 0x1
	@13:
	cmpwi r31, 0x0
	beq @14
	li r3, 0x1
	@14:
	cmpwi r3, 0x0
	beq @15
	rlwinm. r0, r4, 0, 27, 27
	beq @16
	mr r3, r30
	addi r4, r28, 0x6c
	addi r5, r28, 0xc
	bl PSMTXConcat
	b @17
	@16:
	mr r3, r30
	addi r4, r28, 0x3c
	addi r5, r28, 0xc
	bl PSMTXConcat
	@17:
	lhz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 26, 26
	beq @18
	lwz r4, 0xd0(r28)
	addi r3, r28, 0xc
	mr r5, r3
	addi r4, r4, 0xac
	bl PSMTXConcat
	@18:
	addi r3, r28, 0xc
	addi r4, r28, 0x9c
	addi r5, r28, 0xc0
	bl PSMTXMultVec
	mr r3, r28
	bl hitCalcVtxPosition
	lhz r0, 0x0(r28)
	rlwinm r0, r0, 0, 26, 24
	sth r0, 0x0(r28)
	lwz r3, 0xd8(r28)
	cmplwi r3, 0x0
	beq @19
	addi r4, r28, 0xc
	li r5, 0x1
	bl hitReCalcMatrix2
	@19:
	lwz r3, 0xdc(r28)
	cmplwi r3, 0x0
	beq @12
	mr r4, r30
	mr r5, r31
	bl hitReCalcMatrix2
	b @12
	@15:
	lwz r3, 0xd8(r28)
	cmplwi r3, 0x0
	beq @20
	mr r5, r31
	addi r4, r28, 0xc
	bl hitReCalcMatrix2
	@20:
	lwz r3, 0xdc(r28)
	cmplwi r3, 0x0
	beq @12
	mr r4, r30
	mr r5, r31
	bl hitReCalcMatrix2
	b @12
	@3:
	lwz r28, 0xd8(r29)
	cmplwi r28, 0x0
	beq @21
	lhz r4, 0x0(r28)
	li r3, 0x0
	rlwinm. r0, r4, 0, 25, 25
	beq @22
	li r3, 0x1
	@22:
	cmpwi r31, 0x0
	beq @23
	li r3, 0x1
	@23:
	cmpwi r3, 0x0
	beq @24
	rlwinm. r0, r4, 0, 27, 27
	beq @25
	addi r3, r29, 0xc
	addi r4, r28, 0x6c
	addi r5, r28, 0xc
	bl PSMTXConcat
	b @26
	@25:
	addi r3, r29, 0xc
	addi r4, r28, 0x3c
	addi r5, r28, 0xc
	bl PSMTXConcat
	@26:
	lhz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 26, 26
	beq @27
	lwz r4, 0xd0(r28)
	addi r3, r28, 0xc
	mr r5, r3
	addi r4, r4, 0xac
	bl PSMTXConcat
	@27:
	addi r3, r28, 0xc
	addi r4, r28, 0x9c
	addi r5, r28, 0xc0
	bl PSMTXMultVec
	mr r3, r28
	bl hitCalcVtxPosition
	lhz r0, 0x0(r28)
	rlwinm r0, r0, 0, 26, 24
	sth r0, 0x0(r28)
	lwz r3, 0xd8(r28)
	cmplwi r3, 0x0
	beq @28
	addi r4, r28, 0xc
	li r5, 0x1
	bl hitReCalcMatrix2
	@28:
	lwz r3, 0xdc(r28)
	cmplwi r3, 0x0
	beq @21
	mr r5, r31
	addi r4, r29, 0xc
	bl hitReCalcMatrix2
	b @21
	@24:
	lwz r3, 0xd8(r28)
	cmplwi r3, 0x0
	beq @29
	mr r5, r31
	addi r4, r28, 0xc
	bl hitReCalcMatrix2
	@29:
	lwz r3, 0xdc(r28)
	cmplwi r3, 0x0
	beq @21
	mr r5, r31
	addi r4, r29, 0xc
	bl hitReCalcMatrix2
	@21:
	lwz r28, 0xdc(r29)
	cmplwi r28, 0x0
	beq @12
	lhz r4, 0x0(r28)
	li r3, 0x0
	rlwinm. r0, r4, 0, 25, 25
	beq @30
	li r3, 0x1
	@30:
	cmpwi r31, 0x0
	beq @31
	li r3, 0x1
	@31:
	cmpwi r3, 0x0
	beq @32
	rlwinm. r0, r4, 0, 27, 27
	beq @33
	mr r3, r30
	addi r4, r28, 0x6c
	addi r5, r28, 0xc
	bl PSMTXConcat
	b @34
	@33:
	mr r3, r30
	addi r4, r28, 0x3c
	addi r5, r28, 0xc
	bl PSMTXConcat
	@34:
	lhz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 26, 26
	beq @35
	lwz r4, 0xd0(r28)
	addi r3, r28, 0xc
	mr r5, r3
	addi r4, r4, 0xac
	bl PSMTXConcat
	@35:
	addi r3, r28, 0xc
	addi r4, r28, 0x9c
	addi r5, r28, 0xc0
	bl PSMTXMultVec
	mr r3, r28
	bl hitCalcVtxPosition
	lhz r0, 0x0(r28)
	rlwinm r0, r0, 0, 26, 24
	sth r0, 0x0(r28)
	lwz r3, 0xd8(r28)
	cmplwi r3, 0x0
	beq @36
	addi r4, r28, 0xc
	li r5, 0x1
	bl hitReCalcMatrix2
	@36:
	lwz r3, 0xdc(r28)
	cmplwi r3, 0x0
	beq @12
	mr r4, r30
	mr r5, r31
	bl hitReCalcMatrix2
	b @12
	@32:
	lwz r3, 0xd8(r28)
	cmplwi r3, 0x0
	beq @37
	mr r5, r31
	addi r4, r28, 0xc
	bl hitReCalcMatrix2
	@37:
	lwz r3, 0xdc(r28)
	cmplwi r3, 0x0
	beq @12
	mr r4, r30
	mr r5, r31
	bl hitReCalcMatrix2
	@12:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void hitReCalcMatrix(HitEntry* hit, Mtx mtx) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	li r5, 0x0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	lhz r0, 0x0(r3)
	ori r0, r0, 0x40
	sth r0, 0x0(r3)
	bl hitReCalcMatrix2
	lwz r4, 0x8(r31)
	addi r3, r31, 0xc
	addi r5, r1, 0x8
	addi r4, r4, 0x48
	bl PSMTXMultVec
	addi r3, r1, 0x8
	addi r4, r31, 0xc0
	bl PSVECDistance
	stfs f1, 0xcc(r31)
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void hitGrpAttrOff(const char* name, u32 mask) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r26, r4
	bl mapGetWork
	cmplwi r25, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @8
	mr r4, r25
	li r3, 0x1
	bl mapErrorEntry
	b @9
	@8:
	mr r3, r31
	mr r4, r26
	li r5, 0x0
	bl hitAtrOff
	@9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitGrpAttrOn(const char* name, u32 mask) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r26, r4
	bl mapGetWork
	cmplwi r25, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @8
	mr r4, r25
	li r3, 0x1
	bl mapErrorEntry
	b @9
	@8:
	mr r3, r31
	mr r4, r26
	li r5, 0x0
	bl hitAtrOn
	@9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitAtrOff(HitEntry* hit, u32 mask, s32 r) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r31, r4
	nor r30, r31, r31
	mr r28, r3
	mr r29, r5
	lwz r0, 0x4(r3)
	and r0, r0, r30
	stw r0, 0x4(r3)
	lwz r27, 0xd8(r3)
	cmplwi r27, 0x0
	beq @1
	lwz r0, 0x4(r27)
	and r0, r0, r30
	stw r0, 0x4(r27)
	lwz r26, 0xd8(r27)
	cmplwi r26, 0x0
	beq @2
	lwz r0, 0x4(r26)
	and r0, r0, r30
	stw r0, 0x4(r26)
	lwz r25, 0xd8(r26)
	cmplwi r25, 0x0
	beq @3
	lwz r0, 0x4(r25)
	and r0, r0, r30
	stw r0, 0x4(r25)
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @4
	li r5, 0x1
	bl hitAtrOff
	@4:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @3
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@3:
	lwz r25, 0xdc(r26)
	cmplwi r25, 0x0
	beq @2
	lwz r0, 0x4(r25)
	and r0, r0, r30
	stw r0, 0x4(r25)
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @5
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@5:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @2
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@2:
	lwz r25, 0xdc(r27)
	cmplwi r25, 0x0
	beq @1
	lwz r0, 0x4(r25)
	and r0, r0, r30
	stw r0, 0x4(r25)
	lwz r26, 0xd8(r25)
	cmplwi r26, 0x0
	beq @6
	lwz r0, 0x4(r26)
	and r0, r0, r30
	stw r0, 0x4(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @7
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@7:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @6
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@6:
	lwz r25, 0xdc(r25)
	cmplwi r25, 0x0
	beq @1
	lwz r0, 0x4(r25)
	and r0, r0, r30
	stw r0, 0x4(r25)
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @8
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@8:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @1
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@1:
	cmpwi r29, 0x0
	beq @9
	lwz r25, 0xdc(r28)
	cmplwi r25, 0x0
	beq @9
	lwz r0, 0x4(r25)
	and r0, r0, r30
	stw r0, 0x4(r25)
	lwz r26, 0xd8(r25)
	cmplwi r26, 0x0
	beq @10
	lwz r0, 0x4(r26)
	and r0, r0, r30
	stw r0, 0x4(r26)
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @11
	lwz r0, 0x4(r27)
	and r0, r0, r30
	stw r0, 0x4(r27)
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @12
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@12:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @11
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@11:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @10
	lwz r0, 0x4(r26)
	and r0, r0, r30
	stw r0, 0x4(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @13
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@13:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @10
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@10:
	lwz r25, 0xdc(r25)
	cmplwi r25, 0x0
	beq @9
	lwz r0, 0x4(r25)
	and r0, r0, r30
	stw r0, 0x4(r25)
	lwz r26, 0xd8(r25)
	cmplwi r26, 0x0
	beq @14
	lwz r0, 0x4(r26)
	and r0, r0, r30
	stw r0, 0x4(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @15
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@15:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @14
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@14:
	lwz r25, 0xdc(r25)
	cmplwi r25, 0x0
	beq @9
	lwz r0, 0x4(r25)
	and r0, r0, r30
	stw r0, 0x4(r25)
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @16
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@16:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @9
	mr r4, r31
	li r5, 0x1
	bl hitAtrOff
	@9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitAtrOn(HitEntry* hit, u32 mask, s32 r) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r30, r4
	mr r29, r3
	mr r31, r5
	lwz r0, 0x4(r3)
	or r0, r0, r30
	stw r0, 0x4(r3)
	lwz r28, 0xd8(r3)
	cmplwi r28, 0x0
	beq @1
	lwz r0, 0x4(r28)
	or r0, r0, r30
	stw r0, 0x4(r28)
	lwz r27, 0xd8(r28)
	cmplwi r27, 0x0
	beq @2
	lwz r0, 0x4(r27)
	or r0, r0, r30
	stw r0, 0x4(r27)
	lwz r26, 0xd8(r27)
	cmplwi r26, 0x0
	beq @3
	lwz r0, 0x4(r26)
	or r0, r0, r30
	stw r0, 0x4(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @4
	li r5, 0x1
	bl hitAtrOn
	@4:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @3
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@3:
	lwz r26, 0xdc(r27)
	cmplwi r26, 0x0
	beq @2
	lwz r0, 0x4(r26)
	or r0, r0, r30
	stw r0, 0x4(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @5
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@5:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @2
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@2:
	lwz r26, 0xdc(r28)
	cmplwi r26, 0x0
	beq @1
	lwz r0, 0x4(r26)
	or r0, r0, r30
	stw r0, 0x4(r26)
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @6
	lwz r0, 0x4(r27)
	or r0, r0, r30
	stw r0, 0x4(r27)
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @7
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@7:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @6
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@6:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @1
	lwz r0, 0x4(r26)
	or r0, r0, r30
	stw r0, 0x4(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @8
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@8:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @1
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@1:
	cmpwi r31, 0x0
	beq @9
	lwz r26, 0xdc(r29)
	cmplwi r26, 0x0
	beq @9
	lwz r0, 0x4(r26)
	or r0, r0, r30
	stw r0, 0x4(r26)
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @10
	lwz r0, 0x4(r27)
	or r0, r0, r30
	stw r0, 0x4(r27)
	lwz r28, 0xd8(r27)
	cmplwi r28, 0x0
	beq @11
	lwz r0, 0x4(r28)
	or r0, r0, r30
	stw r0, 0x4(r28)
	lwz r3, 0xd8(r28)
	cmplwi r3, 0x0
	beq @12
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@12:
	lwz r3, 0xdc(r28)
	cmplwi r3, 0x0
	beq @11
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@11:
	lwz r27, 0xdc(r27)
	cmplwi r27, 0x0
	beq @10
	lwz r0, 0x4(r27)
	or r0, r0, r30
	stw r0, 0x4(r27)
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @13
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@13:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @10
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@10:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @9
	lwz r0, 0x4(r26)
	or r0, r0, r30
	stw r0, 0x4(r26)
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @14
	lwz r0, 0x4(r27)
	or r0, r0, r30
	stw r0, 0x4(r27)
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @15
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@15:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @14
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@14:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @9
	lwz r0, 0x4(r26)
	or r0, r0, r30
	stw r0, 0x4(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @16
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@16:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @9
	mr r4, r30
	li r5, 0x1
	bl hitAtrOn
	@9:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void hitObjAttrOff(const char* name, u32 mask) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r26, r4
	bl mapGetWork
	cmplwi r25, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @8
	mr r4, r25
	li r3, 0x1
	bl mapErrorEntry
	b @9
	@8:
	lwz r0, 0x4(r31)
	andc r0, r0, r26
	stw r0, 0x4(r31)
	@9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitObjAttrOn(const char* name, u32 mask) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r26, r4
	bl mapGetWork
	cmplwi r25, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @8
	mr r4, r25
	li r3, 0x1
	bl mapErrorEntry
	b @9
	@8:
	lwz r0, 0x4(r31)
	or r0, r0, r26
	stw r0, 0x4(r31)
	@9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitGrpFlagOff(const char* name, u16 mask) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r26, r4
	bl mapGetWork
	cmplwi r25, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @8
	mr r4, r25
	li r3, 0x1
	bl mapErrorEntry
	b @9
	@8:
	mr r3, r31
	mr r4, r26
	li r5, 0x0
	bl hitFlgOff
	@9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitGrpFlagOn(const char* name, u16 mask) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r26, r4
	bl mapGetWork
	cmplwi r25, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @8
	mr r4, r25
	li r3, 0x1
	bl mapErrorEntry
	b @9
	@8:
	mr r3, r31
	mr r4, r26
	li r5, 0x0
	bl hitFlgOn
	@9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitFlgOff(HitEntry* hit, u16 mask, s32 r) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	clrlwi r0, r4, 16
	stmw r25, 0x14(r1)
	mr r28, r3
	nor r30, r0, r0
	mr r31, r4
	mr r29, r5
	lhz r3, 0x0(r3)
	and r0, r3, r30
	sth r0, 0x0(r28)
	lwz r27, 0xd8(r28)
	cmplwi r27, 0x0
	beq @1
	lhz r0, 0x0(r27)
	and r0, r0, r30
	sth r0, 0x0(r27)
	lwz r26, 0xd8(r27)
	cmplwi r26, 0x0
	beq @2
	lhz r0, 0x0(r26)
	and r0, r0, r30
	sth r0, 0x0(r26)
	lwz r25, 0xd8(r26)
	cmplwi r25, 0x0
	beq @3
	lhz r0, 0x0(r25)
	and r0, r0, r30
	sth r0, 0x0(r25)
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @4
	li r5, 0x1
	bl hitFlgOff
	@4:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @3
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@3:
	lwz r25, 0xdc(r26)
	cmplwi r25, 0x0
	beq @2
	lhz r0, 0x0(r25)
	and r0, r0, r30
	sth r0, 0x0(r25)
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @5
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@5:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @2
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@2:
	lwz r25, 0xdc(r27)
	cmplwi r25, 0x0
	beq @1
	lhz r0, 0x0(r25)
	and r0, r0, r30
	sth r0, 0x0(r25)
	lwz r26, 0xd8(r25)
	cmplwi r26, 0x0
	beq @6
	lhz r0, 0x0(r26)
	and r0, r0, r30
	sth r0, 0x0(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @7
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@7:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @6
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@6:
	lwz r25, 0xdc(r25)
	cmplwi r25, 0x0
	beq @1
	lhz r0, 0x0(r25)
	and r0, r0, r30
	sth r0, 0x0(r25)
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @8
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@8:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @1
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@1:
	cmpwi r29, 0x0
	beq @9
	lwz r25, 0xdc(r28)
	cmplwi r25, 0x0
	beq @9
	lhz r0, 0x0(r25)
	and r0, r0, r30
	sth r0, 0x0(r25)
	lwz r26, 0xd8(r25)
	cmplwi r26, 0x0
	beq @10
	lhz r0, 0x0(r26)
	and r0, r0, r30
	sth r0, 0x0(r26)
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @11
	lhz r0, 0x0(r27)
	and r0, r0, r30
	sth r0, 0x0(r27)
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @12
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@12:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @11
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@11:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @10
	lhz r0, 0x0(r26)
	and r0, r0, r30
	sth r0, 0x0(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @13
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@13:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @10
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@10:
	lwz r25, 0xdc(r25)
	cmplwi r25, 0x0
	beq @9
	lhz r0, 0x0(r25)
	and r0, r0, r30
	sth r0, 0x0(r25)
	lwz r26, 0xd8(r25)
	cmplwi r26, 0x0
	beq @14
	lhz r0, 0x0(r26)
	and r0, r0, r30
	sth r0, 0x0(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @15
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@15:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @14
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@14:
	lwz r25, 0xdc(r25)
	cmplwi r25, 0x0
	beq @9
	lhz r0, 0x0(r25)
	and r0, r0, r30
	sth r0, 0x0(r25)
	lwz r3, 0xd8(r25)
	cmplwi r3, 0x0
	beq @16
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@16:
	lwz r3, 0xdc(r25)
	cmplwi r3, 0x0
	beq @9
	mr r4, r31
	li r5, 0x1
	bl hitFlgOff
	@9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitFlgOn(HitEntry* hit, u16 mask, s32 r) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r30, r4
	mr r29, r3
	mr r31, r5
	lhz r0, 0x0(r3)
	or r0, r0, r30
	sth r0, 0x0(r3)
	lwz r28, 0xd8(r3)
	cmplwi r28, 0x0
	beq @1
	lhz r0, 0x0(r28)
	or r0, r0, r30
	sth r0, 0x0(r28)
	lwz r27, 0xd8(r28)
	cmplwi r27, 0x0
	beq @2
	lhz r0, 0x0(r27)
	or r0, r0, r30
	sth r0, 0x0(r27)
	lwz r26, 0xd8(r27)
	cmplwi r26, 0x0
	beq @3
	lhz r0, 0x0(r26)
	or r0, r0, r30
	sth r0, 0x0(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @4
	li r5, 0x1
	bl hitFlgOn
	@4:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @3
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@3:
	lwz r26, 0xdc(r27)
	cmplwi r26, 0x0
	beq @2
	lhz r0, 0x0(r26)
	or r0, r0, r30
	sth r0, 0x0(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @5
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@5:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @2
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@2:
	lwz r26, 0xdc(r28)
	cmplwi r26, 0x0
	beq @1
	lhz r0, 0x0(r26)
	or r0, r0, r30
	sth r0, 0x0(r26)
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @6
	lhz r0, 0x0(r27)
	or r0, r0, r30
	sth r0, 0x0(r27)
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @7
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@7:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @6
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@6:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @1
	lhz r0, 0x0(r26)
	or r0, r0, r30
	sth r0, 0x0(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @8
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@8:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @1
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@1:
	cmpwi r31, 0x0
	beq @9
	lwz r26, 0xdc(r29)
	cmplwi r26, 0x0
	beq @9
	lhz r0, 0x0(r26)
	or r0, r0, r30
	sth r0, 0x0(r26)
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @10
	lhz r0, 0x0(r27)
	or r0, r0, r30
	sth r0, 0x0(r27)
	lwz r28, 0xd8(r27)
	cmplwi r28, 0x0
	beq @11
	lhz r0, 0x0(r28)
	or r0, r0, r30
	sth r0, 0x0(r28)
	lwz r3, 0xd8(r28)
	cmplwi r3, 0x0
	beq @12
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@12:
	lwz r3, 0xdc(r28)
	cmplwi r3, 0x0
	beq @11
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@11:
	lwz r27, 0xdc(r27)
	cmplwi r27, 0x0
	beq @10
	lhz r0, 0x0(r27)
	or r0, r0, r30
	sth r0, 0x0(r27)
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @13
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@13:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @10
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@10:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @9
	lhz r0, 0x0(r26)
	or r0, r0, r30
	sth r0, 0x0(r26)
	lwz r27, 0xd8(r26)
	cmplwi r27, 0x0
	beq @14
	lhz r0, 0x0(r27)
	or r0, r0, r30
	sth r0, 0x0(r27)
	lwz r3, 0xd8(r27)
	cmplwi r3, 0x0
	beq @15
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@15:
	lwz r3, 0xdc(r27)
	cmplwi r3, 0x0
	beq @14
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@14:
	lwz r26, 0xdc(r26)
	cmplwi r26, 0x0
	beq @9
	lhz r0, 0x0(r26)
	or r0, r0, r30
	sth r0, 0x0(r26)
	lwz r3, 0xd8(r26)
	cmplwi r3, 0x0
	beq @16
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@16:
	lwz r3, 0xdc(r26)
	cmplwi r3, 0x0
	beq @9
	mr r4, r30
	li r5, 0x1
	bl hitFlgOn
	@9:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void hitObjFlagOff(const char* name, u16 mask) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r26, r4
	bl mapGetWork
	cmplwi r25, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @8
	mr r4, r25
	li r3, 0x1
	bl mapErrorEntry
	b @9
	@8:
	lhz r0, 0x0(r31)
	andc r0, r0, r26
	sth r0, 0x0(r31)
	@9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitObjFlagOn(const char* name, u16 mask) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r26, r4
	bl mapGetWork
	cmplwi r25, 0x0
	mr r28, r3
	bne @1
	li r31, 0x0
	b @2
	@1:
	mr r27, r28
	li r30, 0x0
	b @3
	@4:
	lwz r31, 0x15c(r27)
	li r29, 0x0
	b @5
	@6:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @7
	lwz r3, 0x8(r31)
	mr r4, r25
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @7
	b @2
	@7:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@5:
	lwz r0, 0x158(r27)
	cmpw r29, r0
	blt @6
	addi r27, r27, 0x178
	addi r30, r30, 0x1
	@3:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @4
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @8
	mr r4, r25
	li r3, 0x1
	bl mapErrorEntry
	b @9
	@8:
	lhz r0, 0x0(r31)
	or r0, r0, r26
	sth r0, 0x0(r31)
	@9:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void hitMain(void) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stmw r17, 0x44(r1)
	bl mapGetWork
	mr r23, r3
	bl mapGetWork
	li r8, 0x0
	li r5, 0x0
	stw r8, unk_80418408(r13)
	mr r9, r3
	b @1
	@2:
	lwz r6, 0x15c(r9)
	li r7, 0x0
	b @3
	@4:
	lwz r4, 0x8(r6)
	lwz r0, 0x5c(r4)
	cmpwi r0, 0x0
	beq @5
	lhz r0, 0x0(r6)
	andi. r0, r0, 0x81
	bne @5
	cmplwi r5, 0x0
	bne @6
	stw r6, unk_80418408(r13)
	mr r5, r6
	b @5
	@6:
	stw r6, 0xe0(r5)
	mr r5, r6
	@5:
	addi r7, r7, 0x1
	addi r6, r6, 0xe4
	@3:
	lwz r0, 0x158(r9)
	cmpw r7, r0
	blt @4
	addi r9, r9, 0x178
	addi r8, r8, 0x1
	@1:
	lwz r0, 0x0(r3)
	cmpw r8, r0
	blt @2
	cmplwi r5, 0x0
	beq @7
	li r0, 0x0
	stw r0, 0xe0(r5)
	@7:
	mr r24, r23
	li r20, 0x0
	b @8
	@9:
	lwz r19, 0x164(r24)
	li r18, 0x0
	li r22, 0x0
	b @10
	@11:
	lhz r4, 0x0(r19)
	lwz r3, 0x18(r19)
	clrlwi. r0, r4, 31
	lwz r17, 0xc(r3)
	beq @12
	rlwinm. r0, r4, 0, 30, 30
	beq @13
	rlwinm. r0, r4, 0, 19, 19
	bne @12
	@13:
	cmplwi r17, 0x0
	beq @12
	mr r25, r17
	li r21, 0x0
	b @14
	@15:
	lwz r3, 0x4(r25)
	lwz r27, 0x0(r3)
	bl mapGetWork
	cmplwi r27, 0x0
	mr r28, r3
	bne @16
	li r31, 0x0
	b @17
	@16:
	mr r26, r28
	li r30, 0x0
	b @18
	@19:
	lwz r31, 0x15c(r26)
	li r29, 0x0
	b @20
	@21:
	lhz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	bne @22
	lwz r3, 0x8(r31)
	mr r4, r27
	lwz r3, 0x0(r3)
	bl strcmp
	cmpwi r3, 0x0
	bne @22
	b @17
	@22:
	addi r29, r29, 0x1
	addi r31, r31, 0xe4
	@20:
	lwz r0, 0x158(r26)
	cmpw r29, r0
	blt @21
	addi r26, r26, 0x178
	addi r30, r30, 0x1
	@18:
	lwz r0, 0x0(r28)
	cmpw r30, r0
	blt @19
	li r31, 0x0
	@17:
	cmplwi r31, 0x0
	beq @23
	lwz r6, 0x4(r25)
	mr r5, r19
	addi r3, r31, 0x6c
	addi r4, r31, 0x3c
	bl mapCalcAnimMatrix
	lhz r0, 0x0(r31)
	li r18, 0x1
	ori r0, r0, 0x10
	sth r0, 0x0(r31)
	lhz r0, 0x0(r31)
	ori r0, r0, 0x40
	sth r0, 0x0(r31)
	lhz r0, 0x0(r19)
	ori r0, r0, 0x1000
	sth r0, 0x0(r19)
	@23:
	addi r25, r25, 0x4
	addi r21, r21, 0x1
	@14:
	lwz r0, 0x0(r17)
	cmpw r21, r0
	blt @15
	@12:
	addi r22, r22, 0x1
	addi r19, r19, 0x20
	@10:
	lwz r0, 0x160(r24)
	cmpw r22, r0
	blt @11
	cmpwi r18, 0x0
	beq @24
	lfs f1, float_10_80419760(r2)
	addi r3, r1, 0x8
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	lwz r3, 0xac(r24)
	addi r4, r1, 0x8
	li r5, 0x0
	bl hitReCalcMatrix2
	@24:
	addi r24, r24, 0x178
	addi r20, r20, 0x1
	@8:
	lwz r0, 0x0(r23)
	cmpw r20, r0
	blt @9
	lmw r17, 0x44(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm void hitDelete(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r26, r3
	bl mapGetWork
	mr r30, r3
	li r28, 0x0
	mr r31, r30
	b @1
	@2:
	lwz r27, 0x15c(r31)
	li r29, 0x0
	b @3
	@4:
	lhz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 24, 24
	bne @5
	lwz r4, 0x8(r27)
	mr r3, r26
	lwz r4, 0x0(r4)
	bl strcmp
	cmpwi r3, 0x0
	bne @5
	lhz r0, 0x0(r27)
	ori r0, r0, 0x80
	sth r0, 0x0(r27)
	bl mapGetWork
	li r8, 0x0
	li r5, 0x0
	stw r8, unk_80418408(r13)
	mr r9, r3
	b @6
	@7:
	lwz r6, 0x15c(r9)
	li r7, 0x0
	b @8
	@9:
	lwz r4, 0x8(r6)
	lwz r0, 0x5c(r4)
	cmpwi r0, 0x0
	beq @10
	lhz r0, 0x0(r6)
	andi. r0, r0, 0x81
	bne @10
	cmplwi r5, 0x0
	bne @11
	stw r6, unk_80418408(r13)
	mr r5, r6
	b @10
	@11:
	stw r6, 0xe0(r5)
	mr r5, r6
	@10:
	addi r7, r7, 0x1
	addi r6, r6, 0xe4
	@8:
	lwz r0, 0x158(r9)
	cmpw r7, r0
	blt @9
	addi r9, r9, 0x178
	addi r8, r8, 0x1
	@6:
	lwz r0, 0x0(r3)
	cmpw r8, r0
	blt @7
	cmplwi r5, 0x0
	beq @12
	li r0, 0x0
	stw r0, 0xe0(r5)
	b @12
	@5:
	addi r29, r29, 0x1
	addi r27, r27, 0xe4
	@3:
	lwz r0, 0x158(r31)
	cmpw r29, r0
	blt @4
	addi r31, r31, 0x178
	addi r28, r28, 0x1
	@1:
	lwz r0, 0x0(r30)
	cmpw r28, r0
	blt @2
	@12:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm HitEntry* hitEntryMOBJ(MapFileJoint* joint, Mtx mtx) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	mr r30, r4
	stw r29, 0x14(r1)
	mr r29, r3
	bl mapGetWork
	mr r31, r3
	mr r3, r29
	bl mapGetJoints
	lwz r0, 0x158(r31)
	mr r5, r30
	li r4, 0x0
	li r6, 0x1
	add r0, r0, r3
	mr r3, r29
	stw r0, 0x158(r31)
	li r7, 0x0
	bl hitEntrySub
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm HitEntry* hitEntry(MapFileJoint* root, Mtx rootMtx, s32 mapIndex) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r26, r3
	mr r27, r4
	mr r28, r5
	bl mapGetWork
	mr r31, r3
	mr r3, r26
	bl mapGetJoints
	mulli r30, r28, 0x178
	add r4, r31, r30
	stw r3, 0x158(r4)
	lwz r3, 0x158(r4)
	addi r0, r3, 0x80
	mulli r3, r0, 0xe4
	addi r0, r3, 0x1f
	clrrwi r29, r0, 5
	mr r3, r29
	bl _mapAlloc
	add r6, r31, r30
	mr r5, r29
	stw r3, 0x15c(r6)
	li r4, 0x0
	lwz r3, 0x15c(r6)
	bl memset
	mr r3, r26
	mr r5, r27
	mr r7, r28
	li r4, 0x0
	li r6, 0x1
	bl hitEntrySub
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm HitEntry* hitEntrySub(MapFileJoint* joint, HitEntry* parent, Mtx parentMtx, BOOL ignoreSiblings, s32 mapIndex) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r21, 0x14(r1)
	mr r30, r7
	mr r29, r6
	mr r26, r3
	mr r27, r4
	mr r28, r5
	mr r6, r30
	bl _hitEnt
	lwz r22, 0xc(r26)
	mr r31, r3
	cmplwi r22, 0x0
	beq @1
	mr r3, r22
	mr r4, r31
	mr r6, r30
	addi r5, r31, 0xc
	bl _hitEnt
	lwz r21, 0xc(r22)
	mr r25, r3
	cmplwi r21, 0x0
	beq @2
	addi r23, r25, 0xc
	mr r3, r21
	mr r4, r25
	mr r6, r30
	mr r5, r23
	bl _hitEnt
	lwz r0, 0xc(r21)
	mr r24, r3
	cmplwi r0, 0x0
	beq @3
	mr r3, r0
	mr r4, r24
	mr r7, r30
	addi r5, r24, 0xc
	li r6, 0x0
	bl hitEntrySub
	stw r3, 0xd8(r24)
	@3:
	lwz r3, 0x10(r21)
	cmplwi r3, 0x0
	beq @4
	mr r4, r25
	mr r5, r23
	mr r7, r30
	li r6, 0x0
	bl hitEntrySub
	stw r3, 0xdc(r24)
	@4:
	stw r24, 0xd8(r25)
	@2:
	lwz r21, 0x10(r22)
	cmplwi r21, 0x0
	beq @5
	mr r3, r21
	mr r4, r31
	mr r6, r30
	addi r5, r31, 0xc
	bl _hitEnt
	lwz r0, 0xc(r21)
	mr r23, r3
	cmplwi r0, 0x0
	beq @6
	mr r3, r0
	mr r4, r23
	mr r7, r30
	addi r5, r23, 0xc
	li r6, 0x0
	bl hitEntrySub
	stw r3, 0xd8(r23)
	@6:
	lwz r3, 0x10(r21)
	cmplwi r3, 0x0
	beq @7
	mr r4, r31
	mr r7, r30
	addi r5, r31, 0xc
	li r6, 0x0
	bl hitEntrySub
	stw r3, 0xdc(r23)
	@7:
	stw r23, 0xdc(r25)
	@5:
	stw r25, 0xd8(r31)
	@1:
	cmpwi r29, 0x0
	bne @8
	lwz r21, 0x10(r26)
	cmplwi r21, 0x0
	beq @8
	mr r3, r21
	mr r4, r27
	mr r5, r28
	mr r6, r30
	bl _hitEnt
	lwz r22, 0xc(r21)
	mr r25, r3
	cmplwi r22, 0x0
	beq @9
	addi r24, r25, 0xc
	mr r3, r22
	mr r4, r25
	mr r6, r30
	mr r5, r24
	bl _hitEnt
	lwz r0, 0xc(r22)
	mr r23, r3
	cmplwi r0, 0x0
	beq @10
	mr r3, r0
	mr r4, r23
	mr r7, r30
	addi r5, r23, 0xc
	li r6, 0x0
	bl hitEntrySub
	stw r3, 0xd8(r23)
	@10:
	lwz r3, 0x10(r22)
	cmplwi r3, 0x0
	beq @11
	mr r4, r25
	mr r5, r24
	mr r7, r30
	li r6, 0x0
	bl hitEntrySub
	stw r3, 0xdc(r23)
	@11:
	stw r23, 0xd8(r25)
	@9:
	lwz r21, 0x10(r21)
	cmplwi r21, 0x0
	beq @12
	mr r3, r21
	mr r4, r27
	mr r5, r28
	mr r6, r30
	bl _hitEnt
	lwz r0, 0xc(r21)
	mr r23, r3
	cmplwi r0, 0x0
	beq @13
	mr r3, r0
	mr r4, r23
	mr r7, r30
	addi r5, r23, 0xc
	li r6, 0x0
	bl hitEntrySub
	stw r3, 0xd8(r23)
	@13:
	lwz r3, 0x10(r21)
	cmplwi r3, 0x0
	beq @14
	mr r4, r27
	mr r5, r28
	mr r7, r30
	li r6, 0x0
	bl hitEntrySub
	stw r3, 0xdc(r23)
	@14:
	stw r23, 0xdc(r25)
	@12:
	stw r25, 0xdc(r31)
	@8:
	mr r3, r31
	lmw r21, 0x14(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm HitEntry* _hitEnt(MapFileJoint* joint, HitEntry* parent, Mtx parentMtx, s32 mapIndex) {
	nofralloc
	stwu r1, -0x120(r1)
	mflr r0
	stw r0, 0x124(r1)
	stmw r27, 0x10c(r1)
	mr r30, r3
	mr r27, r4
	mr r28, r5
	mr r29, r6
	bl mapGetWork
	mulli r4, r29, 0x178
	addi r0, r4, 0x158
	lwzx r0, r3, r0
	add r3, r3, r4
	lwz r31, 0x15c(r3)
	mtctr r0
	cmpwi r0, 0x0
	ble @1
	@2:
	lwz r0, 0x8(r31)
	cmplwi r0, 0x0
	beq @1
	addi r31, r31, 0xe4
	bdnz @2
	@1:
	li r0, 0x0
	addi r3, r1, 0xd4
	sth r0, 0x0(r31)
	stw r30, 0x8(r31)
	sth r29, 0xaa(r31)
	lfs f1, 0x30(r30)
	lfs f2, 0x34(r30)
	lfs f3, 0x38(r30)
	bl PSMTXTrans
	lfs f1, 0x18(r30)
	addi r3, r1, 0xa4
	lfs f2, 0x1c(r30)
	lfs f3, 0x20(r30)
	bl PSMTXScale
	lfs f1, float_deg2rad_80419770(r2)
	addi r3, r1, 0x74
	lfs f0, 0x24(r30)
	li r4, 0x78
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lfs f1, float_deg2rad_80419770(r2)
	addi r3, r1, 0x44
	lfs f0, 0x28(r30)
	li r4, 0x79
	fmuls f1, f1, f0
	bl PSMTXRotRad
	lfs f1, float_deg2rad_80419770(r2)
	addi r3, r1, 0x14
	lfs f0, 0x2c(r30)
	li r4, 0x7a
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r3, r1, 0xd4
	addi r4, r1, 0x14
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xd4
	addi r4, r1, 0x44
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xd4
	addi r4, r1, 0x74
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0xd4
	addi r4, r1, 0xa4
	addi r5, r31, 0x3c
	bl PSMTXConcat
	mr r3, r28
	addi r4, r31, 0x3c
	addi r5, r31, 0xc
	bl PSMTXConcat
	stw r27, 0xd4(r31)
	li r0, 0x0
	stw r0, 0xdc(r31)
	stw r0, 0xd8(r31)
	stw r0, 0xac(r31)
	lwz r3, 0x58(r30)
	cmplwi r3, 0x0
	beq @3
	lwz r0, 0x8(r3)
	stw r0, 0x4(r31)
	b @4
	@3:
	stw r0, 0x4(r31)
	@4:
	lwz r0, 0x5c(r30)
	cmpwi r0, 0x0
	beq @5
	addi r3, r30, 0x3c
	addi r4, r30, 0x48
	addi r5, r31, 0x9c
	bl PSVECAdd
	addi r3, r31, 0x9c
	lfs f1, float_0p5_8041976c(r2)
	mr r4, r3
	bl PSVECScale
	b @6
	@5:
	lwz r3, 0x30(r30)
	lwz r0, 0x34(r30)
	stw r3, 0x9c(r31)
	stw r0, 0xa0(r31)
	lwz r0, 0x38(r30)
	stw r0, 0xa4(r31)
	@6:
	addi r3, r31, 0xc
	addi r4, r31, 0x9c
	addi r5, r31, 0xc0
	bl PSMTXMultVec
	lfs f0, 0x3c(r30)
	addi r3, r31, 0xc
	lfs f1, float_0p1_8041975c(r2)
	addi r5, r1, 0x8
	fsubs f0, f0, f1
	stfs f0, 0x3c(r30)
	lfs f0, 0x40(r30)
	fsubs f0, f0, f1
	stfs f0, 0x40(r30)
	lfs f0, 0x44(r30)
	fsubs f0, f0, f1
	stfs f0, 0x44(r30)
	lfs f0, 0x48(r30)
	fadds f0, f0, f1
	stfs f0, 0x48(r30)
	lfs f0, 0x4c(r30)
	fadds f0, f0, f1
	stfs f0, 0x4c(r30)
	lfs f0, 0x50(r30)
	fadds f0, f0, f1
	stfs f0, 0x50(r30)
	lwz r4, 0x8(r31)
	addi r4, r4, 0x48
	bl PSMTXMultVec
	addi r3, r1, 0x8
	addi r4, r31, 0xc0
	bl PSVECDistance
	stfs f1, 0xcc(r31)
	li r6, 0x0
	li r8, 0x0
	li r3, 0x0
	lwz r4, 0x8(r31)
	lwz r0, 0x5c(r4)
	b @7
	@8:
	addi r5, r3, 0x64
	lwzx r9, r4, r5
	cmplwi r9, 0x0
	beq @9
	lbz r5, 0x3(r9)
	cmplwi r5, 0x0
	bne @10
	lwz r5, 0x4(r9)
	li r7, 0x0
	cmpwi r5, 0x0
	ble @9
	cmpwi r5, 0x8
	subi r11, r5, 0x8
	ble @11
	addi r10, r11, 0x7
	mr r30, r9
	srwi r10, r10, 3
	mtctr r10
	cmpwi r11, 0x0
	ble @11
	@12:
	lwz r11, 0x10(r30)
	addi r7, r7, 0x8
	lwz r10, 0x14(r30)
	lwz r12, 0x0(r11)
	lwz r11, 0x18(r30)
	add r6, r12, r6
	lwz r12, 0x0(r10)
	subi r6, r6, 0x2
	lwz r10, 0x1c(r30)
	add r6, r12, r6
	lwz r12, 0x0(r11)
	subi r6, r6, 0x2
	lwz r11, 0x20(r30)
	add r6, r12, r6
	lwz r12, 0x0(r10)
	subi r6, r6, 0x2
	lwz r10, 0x24(r30)
	add r6, r12, r6
	lwz r12, 0x0(r11)
	subi r6, r6, 0x2
	lwz r11, 0x28(r30)
	add r6, r12, r6
	lwz r12, 0x0(r10)
	subi r6, r6, 0x2
	lwz r10, 0x2c(r30)
	add r6, r12, r6
	lwz r11, 0x0(r11)
	subi r6, r6, 0x2
	lwz r10, 0x0(r10)
	add r6, r11, r6
	addi r30, r30, 0x20
	subi r6, r6, 0x2
	add r6, r10, r6
	subi r6, r6, 0x2
	bdnz @12
	@11:
	slwi r11, r7, 2
	subf r10, r7, r5
	add r9, r9, r11
	mtctr r10
	cmpw r7, r5
	bge @9
	@13:
	lwz r5, 0x10(r9)
	addi r9, r9, 0x4
	addi r7, r7, 0x1
	lwz r5, 0x0(r5)
	add r6, r5, r6
	subi r6, r6, 0x2
	bdnz @13
	b @9
	@10:
	lwz r11, 0x4(r9)
	li r12, 0x0
	cmpwi r11, 0x0
	ble @9
	cmpwi r11, 0x8
	subi r7, r11, 0x8
	ble @14
	addi r5, r7, 0x7
	mr r10, r9
	srwi r5, r5, 3
	mtctr r5
	cmpwi r7, 0x0
	ble @14
	@15:
	lwz r5, 0x10(r10)
	addi r12, r12, 0x8
	lwz r7, 0x18(r10)
	lhz r5, 0x1(r5)
	lwz r30, 0x20(r10)
	add r6, r5, r6
	lhz r5, 0x1(r7)
	subi r6, r6, 0x2
	lwz r7, 0x28(r10)
	add r6, r5, r6
	lhz r5, 0x1(r30)
	subi r6, r6, 0x2
	lwz r30, 0x30(r10)
	add r6, r5, r6
	lhz r5, 0x1(r7)
	subi r6, r6, 0x2
	lwz r7, 0x38(r10)
	add r6, r5, r6
	lhz r5, 0x1(r30)
	subi r6, r6, 0x2
	lwz r30, 0x40(r10)
	add r6, r5, r6
	lhz r7, 0x1(r7)
	subi r6, r6, 0x2
	lwz r5, 0x48(r10)
	add r6, r7, r6
	lhz r7, 0x1(r30)
	subi r6, r6, 0x2
	lhz r5, 0x1(r5)
	add r6, r7, r6
	addi r10, r10, 0x40
	subi r6, r6, 0x2
	add r6, r5, r6
	subi r6, r6, 0x2
	bdnz @15
	@14:
	slwi r7, r12, 3
	subf r5, r12, r11
	add r7, r9, r7
	mtctr r5
	cmpw r12, r11
	bge @9
	@16:
	lwz r5, 0x10(r7)
	addi r7, r7, 0x8
	addi r12, r12, 0x1
	lhz r5, 0x1(r5)
	add r6, r5, r6
	subi r6, r6, 0x2
	bdnz @16
	@9:
	addi r3, r3, 0x8
	addi r8, r8, 0x1
	@7:
	cmpw r8, r0
	blt @8
	cmpwi r6, 0x0
	ble @17
	mulli r3, r6, 0x54
	bl _mapAlloc
	stw r3, 0xac(r31)
	mr r3, r31
	bl hitCalcVtxPosition
	sth r3, 0xa8(r31)
	@17:
	mr r3, r31
	lmw r27, 0x10c(r1)
	lwz r0, 0x124(r1)
	mtlr r0
	addi r1, r1, 0x120
	blr
}
// clang-format on
#endif
