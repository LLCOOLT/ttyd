#include "driver/hitdrv.h"
#include "dolphin/os.h"
#include "driver/mapdrv.h"
#include "memory.h"
#include "party.h"
#include <string.h>
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
extern const u32 lbl_802C1538;
extern const f32 vec3_802c153c[3];
extern const f32 vec3_802c1548[3];
extern const f32 vec3_802c1554[3];
extern const f32 vec3_802c1560[3];
extern const f32 vec3_802c156c[3];
extern const f32 vec3_802c1578[3];
extern const f32 vec3_802c1584[3];
extern const f64 double_to_int_802c1590;
extern const f32 float_0_80419758;
extern const f32 float_0p1_8041975c;
extern const f32 float_10_80419760;
extern const f32 float_1_80419764;
extern const f32 float_neg1_80419768;
extern const f32 float_0p5_8041976c;
extern const f32 float_deg2rad_80419770;
extern const u32 gap_09_80419774_sdata2;
#endif

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
        VECScale(&hit->centerLocal, &hit->centerLocal, EXT_LIT(float_0p5_8041976c, 0.5f));
    } else {
        hit->centerLocal = joint->translation;
    }
    MTXMultVec(hit->worldMtx, &hit->centerLocal, &hit->centerWorld);

    joint->bboxMin.x -= EXT_LIT(float_0p1_8041975c, 0.1f);
    joint->bboxMin.y -= EXT_LIT(float_0p1_8041975c, 0.1f);
    joint->bboxMin.z -= EXT_LIT(float_0p1_8041975c, 0.1f);
    joint->bboxMax.x += EXT_LIT(float_0p1_8041975c, 0.1f);
    joint->bboxMax.y += EXT_LIT(float_0p1_8041975c, 0.1f);
    joint->bboxMax.z += EXT_LIT(float_0p1_8041975c, 0.1f);

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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
HitEntry* _hitEnt(MapFileJoint* joint, HitEntry* parent, Mtx parentMtx, s32 mapIndex) {
	asm volatile {
		opword 0x9421FEE0
		opword 0x7C0802A6
		opword 0x90010124
		opword 0xBF61010C
		opword 0x7C7E1B78
		opword 0x7C9B2378
		opword 0x7CBC2B78
		opword 0x7CDD3378
		bl mapGetWork
		opword 0x1C9D0178
		opword 0x38040158
		opword 0x7C03002E
		opword 0x7C632214
		opword 0x83E3015C
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x40810018
		opword 0x801F0008
		opword 0x28000000
		opword 0x4182000C
		opword 0x3BFF00E4
		opword 0x4200FFF0
		opword 0x38000000
		opword 0x386100D4
		opword 0xB01F0000
		opword 0x93DF0008
		opword 0xB3BF00AA
		opword 0xC03E0030
		opword 0xC05E0034
		opword 0xC07E0038
		bl PSMTXTrans
		opword 0xC03E0018
		opword 0x386100A4
		opword 0xC05E001C
		opword 0xC07E0020
		bl PSMTXScale
		lfs f1, float_deg2rad_80419770(r2)
		opword 0x38610074
		opword 0xC01E0024
		opword 0x38800078
		opword 0xEC210032
		bl PSMTXRotRad
		lfs f1, float_deg2rad_80419770(r2)
		opword 0x38610044
		opword 0xC01E0028
		opword 0x38800079
		opword 0xEC210032
		bl PSMTXRotRad
		lfs f1, float_deg2rad_80419770(r2)
		opword 0x38610014
		opword 0xC01E002C
		opword 0x3880007A
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x386100D4
		opword 0x38810014
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100D4
		opword 0x38810044
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100D4
		opword 0x38810074
		opword 0x7C651B78
		bl PSMTXConcat
		opword 0x386100D4
		opword 0x388100A4
		opword 0x38BF003C
		bl PSMTXConcat
		opword 0x7F83E378
		opword 0x389F003C
		opword 0x38BF000C
		bl PSMTXConcat
		opword 0x937F00D4
		opword 0x38000000
		opword 0x901F00DC
		opword 0x901F00D8
		opword 0x901F00AC
		opword 0x807E0058
		opword 0x28030000
		opword 0x41820010
		opword 0x80030008
		opword 0x901F0004
		opword 0x48000008
		opword 0x901F0004
		opword 0x801E005C
		opword 0x2C000000
		opword 0x41820028
		opword 0x387E003C
		opword 0x389E0048
		opword 0x38BF009C
		bl PSVECAdd
		opword 0x387F009C
		lfs f1, float_0p5_8041976c(r2)
		opword 0x7C641B78
		bl PSVECScale
		opword 0x4800001C
		opword 0x807E0030
		opword 0x801E0034
		opword 0x907F009C
		opword 0x901F00A0
		opword 0x801E0038
		opword 0x901F00A4
		opword 0x387F000C
		opword 0x389F009C
		opword 0x38BF00C0
		bl PSMTXMultVec
		opword 0xC01E003C
		opword 0x387F000C
		lfs f1, float_0p1_8041975c(r2)
		opword 0x38A10008
		opword 0xEC000828
		opword 0xD01E003C
		opword 0xC01E0040
		opword 0xEC000828
		opword 0xD01E0040
		opword 0xC01E0044
		opword 0xEC000828
		opword 0xD01E0044
		opword 0xC01E0048
		opword 0xEC00082A
		opword 0xD01E0048
		opword 0xC01E004C
		opword 0xEC00082A
		opword 0xD01E004C
		opword 0xC01E0050
		opword 0xEC00082A
		opword 0xD01E0050
		opword 0x809F0008
		opword 0x38840048
		bl PSMTXMultVec
		opword 0x38610008
		opword 0x389F00C0
		bl PSVECDistance
		opword 0xD03F00CC
		opword 0x38C00000
		opword 0x39000000
		opword 0x38600000
		opword 0x809F0008
		opword 0x8004005C
		opword 0x48000214
		opword 0x38A30064
		opword 0x7D24282E
		opword 0x28090000
		opword 0x418201FC
		opword 0x88A90003
		opword 0x28050000
		opword 0x408200FC
		opword 0x80A90004
		opword 0x38E00000
		opword 0x2C050000
		opword 0x408101E0
		opword 0x2C050008
		opword 0x3965FFF8
		opword 0x408100A8
		opword 0x394B0007
		opword 0x7D3E4B78
		opword 0x554AE8FE
		opword 0x7D4903A6
		opword 0x2C0B0000
		opword 0x40810090
		opword 0x817E0010
		opword 0x38E70008
		opword 0x815E0014
		opword 0x818B0000
		opword 0x817E0018
		opword 0x7CCC3214
		opword 0x818A0000
		opword 0x38C6FFFE
		opword 0x815E001C
		opword 0x7CCC3214
		opword 0x818B0000
		opword 0x38C6FFFE
		opword 0x817E0020
		opword 0x7CCC3214
		opword 0x818A0000
		opword 0x38C6FFFE
		opword 0x815E0024
		opword 0x7CCC3214
		opword 0x818B0000
		opword 0x38C6FFFE
		opword 0x817E0028
		opword 0x7CCC3214
		opword 0x818A0000
		opword 0x38C6FFFE
		opword 0x815E002C
		opword 0x7CCC3214
		opword 0x816B0000
		opword 0x38C6FFFE
		opword 0x814A0000
		opword 0x7CCB3214
		opword 0x3BDE0020
		opword 0x38C6FFFE
		opword 0x7CCA3214
		opword 0x38C6FFFE
		opword 0x4200FF78
		opword 0x54EB103A
		opword 0x7D472850
		opword 0x7D295A14
		opword 0x7D4903A6
		opword 0x7C072800
		opword 0x40800118
		opword 0x80A90010
		opword 0x39290004
		opword 0x38E70001
		opword 0x80A50000
		opword 0x7CC53214
		opword 0x38C6FFFE
		opword 0x4200FFE8
		opword 0x480000F8
		opword 0x81690004
		opword 0x39800000
		opword 0x2C0B0000
		opword 0x408100E8
		opword 0x2C0B0008
		opword 0x38EBFFF8
		opword 0x408100A8
		opword 0x38A70007
		opword 0x7D2A4B78
		opword 0x54A5E8FE
		opword 0x7CA903A6
		opword 0x2C070000
		opword 0x40810090
		opword 0x80AA0010
		opword 0x398C0008
		opword 0x80EA0018
		opword 0xA0A50001
		opword 0x83CA0020
		opword 0x7CC53214
		opword 0xA0A70001
		opword 0x38C6FFFE
		opword 0x80EA0028
		opword 0x7CC53214
		opword 0xA0BE0001
		opword 0x38C6FFFE
		opword 0x83CA0030
		opword 0x7CC53214
		opword 0xA0A70001
		opword 0x38C6FFFE
		opword 0x80EA0038
		opword 0x7CC53214
		opword 0xA0BE0001
		opword 0x38C6FFFE
		opword 0x83CA0040
		opword 0x7CC53214
		opword 0xA0E70001
		opword 0x38C6FFFE
		opword 0x80AA0048
		opword 0x7CC73214
		opword 0xA0FE0001
		opword 0x38C6FFFE
		opword 0xA0A50001
		opword 0x7CC73214
		opword 0x394A0040
		opword 0x38C6FFFE
		opword 0x7CC53214
		opword 0x38C6FFFE
		opword 0x4200FF78
		opword 0x55871838
		opword 0x7CAC5850
		opword 0x7CE93A14
		opword 0x7CA903A6
		opword 0x7C0C5800
		opword 0x40800020
		opword 0x80A70010
		opword 0x38E70008
		opword 0x398C0001
		opword 0xA0A50001
		opword 0x7CC53214
		opword 0x38C6FFFE
		opword 0x4200FFE8
		opword 0x38630008
		opword 0x39080001
		opword 0x7C080000
		opword 0x4180FDEC
		opword 0x2C060000
		opword 0x4081001C
		opword 0x1C660054
		bl _mapAlloc
		opword 0x907F00AC
		opword 0x7FE3FB78
		bl hitCalcVtxPosition
		opword 0xB07F00A8
		opword 0x7FE3FB78
		opword 0xBB61010C
		opword 0x80010124
		opword 0x7C0803A6
		opword 0x38210120
	}
}
#pragma pop
#endif

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

HitEntry* hitEntry(MapFileJoint* root, Mtx rootMtx, s32 mapIndex) {
    MapWork* wp = mapGetWork();
    u32 size;

    wp->entries[mapIndex].hitNumJoints = mapGetJoints(root);
    size = OSRoundUp32B(((wp->entries[mapIndex].hitNumJoints + 128) * sizeof(HitEntry)));
    wp->entries[mapIndex].hitEntries = _mapAlloc(size);
    memset(wp->entries[mapIndex].hitEntries, 0, size);
    return hitEntrySub(root, NULL, rootMtx, TRUE, mapIndex);
}

HitEntry* hitEntryMOBJ(MapFileJoint* joint, Mtx mtx) {
    MapWork* wp = mapGetWork();

    wp->entries[0].hitNumJoints += mapGetJoints(joint);
    return hitEntrySub(joint, NULL, mtx, TRUE, 0);
}

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
            PSMTXScale(mtx, EXT_LIT(float_10_80419760, 10.0f), EXT_LIT(float_10_80419760, 10.0f), EXT_LIT(float_10_80419760, 10.0f));
            hitReCalcMatrix2(entry->rootHitObj, mtx, FALSE);
        }
    }
}


void hitFlgOn(HitEntry* hit, u16 mask, s32 r);
void hitFlgOff(HitEntry* hit, u16 mask, s32 r);
void hitAtrOn(HitEntry* hit, u32 mask, s32 r);
void hitAtrOff(HitEntry* hit, u32 mask, s32 r);

void hitObjFlagOn(const char* name, u16 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hit->flags |= mask;
}

void hitObjFlagOff(const char* name, u16 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hit->flags &= ~mask;
}

void hitFlgOn(HitEntry* hit, u16 mask, s32 r) {
    hit->flags |= mask;
    if (hit->child != NULL) {
        hitFlgOn(hit->child, mask, 1);
    }
    if (r != 0 && hit->sibling != NULL) {
        hitFlgOn(hit->sibling, mask, 1);
    }
}

void hitFlgOff(HitEntry* hit, u16 mask, s32 r) {
    hit->flags &= ~mask;
    if (hit->child != NULL) {
        hitFlgOff(hit->child, mask, 1);
    }
    if (r != 0 && hit->sibling != NULL) {
        hitFlgOff(hit->sibling, mask, 1);
    }
}

void hitGrpFlagOn(const char* name, u16 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hitFlgOn(hit, mask, 0);
}

void hitGrpFlagOff(const char* name, u16 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hitFlgOff(hit, mask, 0);
}


void hitObjAttrOn(const char* name, u32 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hit->attributes |= mask;
}

void hitObjAttrOff(const char* name, u32 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hit->attributes &= ~mask;
}

void hitAtrOn(HitEntry* hit, u32 mask, s32 r) {
    hit->attributes |= mask;
    if (hit->child != NULL) {
        hitAtrOn(hit->child, mask, 1);
    }
    if (r != 0 && hit->sibling != NULL) {
        hitAtrOn(hit->sibling, mask, 1);
    }
}

void hitAtrOff(HitEntry* hit, u32 mask, s32 r) {
    hit->attributes &= ~mask;
    if (hit->child != NULL) {
        hitAtrOff(hit->child, mask, 1);
    }
    if (r != 0 && hit->sibling != NULL) {
        hitAtrOff(hit->sibling, mask, 1);
    }
}


void hitGrpAttrOn(const char* name, u32 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hitAtrOn(hit, mask, 0);
}

void hitGrpAttrOff(const char* name, u32 mask) {
    HitEntry* hit = hitNameToPtr(name);
    if (hit == NULL) {
        mapErrorEntry(1, name);
        return;
    }
    hitAtrOff(hit, mask, 0);
}

void hitReCalcMatrix(HitEntry* hit, Mtx mtx) {
    Vec world;

    hit->flags |= 0x40;
    hitReCalcMatrix2(hit, mtx, FALSE);
    MTXMultVec(hit->worldMtx, &hit->joint->bboxMax, &world);
    hit->radius = PSVECDistance(&world, &hit->centerWorld);
}

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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 hitCalcVtxPosition(HitEntry* hit) {
	char _af_pad[32];
	asm volatile {
		opword 0x7C7B1B78
		opword 0x3BC00000
		opword 0x800300AC
		opword 0x28000000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000468
		opword 0x3BE00000
		opword 0x3A800000
		opword 0x48000448
		opword 0x38140064
		opword 0x7FA3002E
		opword 0x281D0000
		opword 0x41820430
		opword 0x881D0003
		opword 0x28000000
		opword 0x40820140
		opword 0x7FB9EB78
		opword 0x3A200000
		opword 0x48000124
		opword 0x82790010
		mulli r16, r30, 0x54
		opword 0x3A400000
		opword 0x7E7C9B78
		opword 0x480000F8
		opword 0x38120001
		opword 0x38D20002
		opword 0x809D000C
		opword 0x1CE00018
		opword 0xA81C0004
		opword 0x387B000C
		opword 0x80BB00AC
		opword 0x3BDE0001
		opword 0x80840000
		opword 0x7EE58214
		opword 0x38A70004
		opword 0x7EB32AAE
		opword 0x1CC60018
		opword 0x3B040004
		opword 0x7EE5BB78
		opword 0x38860004
		opword 0x3A100054
		opword 0x1C00000C
		opword 0x7ED322AE
		opword 0x7C980214
		bl PSMTXMultVec
		opword 0x564007FE
		opword 0x7EA3AB78
		opword 0x7C000034
		opword 0x541AD97F
		opword 0x41820008
		opword 0x7EC3B378
		opword 0x7C600734
		opword 0x387B000C
		opword 0x1C00000C
		opword 0x38B7000C
		opword 0x7C980214
		bl PSMTXMultVec
		opword 0x2C1A0000
		opword 0x7EC0B378
		opword 0x387B000C
		opword 0x41820008
		opword 0x7EA0AB78
		opword 0x7C000734
		opword 0x38B70018
		opword 0x1C00000C
		opword 0x7C980214
		bl PSMTXMultVec
		opword 0x7EE4BB78
		opword 0x38770018
		opword 0x38B70024
		bl PSVECSubtract
		opword 0x7EE3BB78
		opword 0x3897000C
		opword 0x38B70030
		bl PSVECSubtract
		opword 0x3877000C
		opword 0x38970018
		opword 0x38B7003C
		bl PSVECSubtract
		opword 0x38770024
		opword 0x38970030
		opword 0x38B70048
		bl PSVECCrossProduct
		opword 0x3B9C0018
		opword 0x3A520001
		opword 0x80730000
		opword 0x3803FFFE
		opword 0x7C120000
		opword 0x4180FF00
		opword 0x3B390004
		opword 0x3A310001
		opword 0x801D0004
		opword 0x7C110000
		opword 0x4180FED8
		opword 0x480002E8
		bl mapGetWork
		opword 0x819D0008
		opword 0x3A000000
		opword 0x39400001
		opword 0x39200002
		opword 0x7D8B8430
		opword 0x39000003
		opword 0x7D8A5430
		opword 0x7D894C30
		opword 0x7D874430
		opword 0x38C00004
		opword 0x7D863430
		opword 0x38A00005
		opword 0x7D842C30
		opword 0x556B07FE
		opword 0x554807FE
		opword 0x3A000006
		opword 0x39400007
		opword 0x552507FE
		opword 0x7C0B4214
		opword 0x7D8B8430
		opword 0x7D8A5430
		opword 0x39200008
		opword 0x7C002A14
		opword 0x54E707FE
		opword 0x7D894C30
		opword 0x39000009
		opword 0x7C003A14
		opword 0x54C507FE
		opword 0x7D874430
		opword 0x38C0000A
		opword 0x7C002A14
		opword 0x548407FE
		opword 0x7D863430
		opword 0x38A0000B
		opword 0x7C002214
		opword 0x556B07FE
		opword 0x7D842C30
		opword 0x554807FE
		opword 0x7C005A14
		opword 0x552507FE
		opword 0x7C004214
		opword 0x54E707FE
		opword 0x7C002A14
		opword 0x54C507FE
		opword 0x7C003A14
		opword 0x548407FE
		opword 0x7C002A14
		lfs f31, float_0_80419758(r2)
		opword 0x7C002214
		opword 0x7C7A1B78
		opword 0x1EBE0054
		opword 0x7FB6EB78
		opword 0x5413083C
		opword 0x3A400000
		opword 0x480001FC
		opword 0x82160010
		opword 0x3A200000
		opword 0x7EB9AB78
		opword 0xA0700001
		opword 0x7E388B78
		opword 0x3AE3FFFE
		opword 0x480001D0
		opword 0x38110001
		opword 0x38910002
		opword 0x7CB301D6
		opword 0x7C70C214
		opword 0x562007FE
		opword 0x80FD000C
		opword 0xA0630003
		opword 0x7C000034
		opword 0x81070000
		opword 0x7C9321D6
		opword 0x80FB00AC
		opword 0x7CB02A14
		opword 0x5406D97F
		opword 0xA0050003
		opword 0x7F87CA14
		opword 0x7CB02214
		opword 0x1C830003
		opword 0xA1250003
		opword 0x7C050378
		opword 0x38680004
		opword 0x41820008
		opword 0x7D254B78
		opword 0x54A5043E
		opword 0x2C060000
		opword 0x1CA50003
		opword 0x7D264B78
		opword 0x41820008
		opword 0x7C060378
		opword 0xA81B00AA
		opword 0x54C6043E
		opword 0x1CC60003
		opword 0x1CE00178
		opword 0x380700A4
		opword 0x7CFA002E
		opword 0x80070044
		opword 0x5400402E
		opword 0x60070007
		opword 0x54E0801E
		opword 0x7CE00378
		opword 0x7C15E3A6
		opword 0x5480083C
		opword 0x1003068C
		opword 0x38040001
		opword 0x5400083C
		stfs f0, _af_pad+24(r1)
		opword 0x1003068C
		opword 0x38040002
		opword 0x5400083C
		opword 0xD0010024
		opword 0x1003068C
		opword 0x54A0083C
		opword 0xD0010028
		opword 0x1003068C
		opword 0x38050001
		opword 0x5400083C
		opword 0xD0010014
		opword 0x1003068C
		opword 0x38050002
		opword 0x5400083C
		opword 0xD0010018
		opword 0x1003068C
		opword 0x54C0083C
		opword 0xD001001C
		opword 0x1003068C
		opword 0x38060001
		opword 0x5400083C
		opword 0xD0010008
		opword 0x1003068C
		opword 0x38060002
		opword 0x5400083C
		opword 0xD001000C
		opword 0x1003068C
		opword 0x7F85E378
		opword 0x387B000C
		opword 0x38810020
		opword 0xD0010010
		bl PSMTXMultVec
		opword 0x387B000C
		opword 0x38810014
		opword 0x38BC000C
		bl PSMTXMultVec
		opword 0x387B000C
		opword 0x38810008
		opword 0x38BC0018
		bl PSMTXMultVec
		opword 0x7F84E378
		opword 0x387C0018
		opword 0x38BC0024
		bl PSVECSubtract
		opword 0x7F83E378
		opword 0x389C000C
		opword 0x38BC0030
		bl PSVECSubtract
		opword 0x387C000C
		opword 0x389C0018
		opword 0x38BC003C
		bl PSVECSubtract
		opword 0x387C0024
		opword 0x389C0030
		opword 0x38BC0048
		bl PSVECCrossProduct
		opword 0xC01C0048
		opword 0xFC00F800
		opword 0x4082001C
		opword 0xC01C004C
		opword 0xFC00F800
		opword 0x40820010
		opword 0xC01C0050
		opword 0xFC00F800
		opword 0x41820010
		opword 0x3B390054
		opword 0x3AB50054
		opword 0x3BDE0001
		opword 0x7F189A14
		opword 0x3A310001
		opword 0x7C11B800
		opword 0x4180FE30
		opword 0x3AD60008
		opword 0x3A520001
		opword 0x801D0004
		opword 0x7C120000
		opword 0x4180FE00
		opword 0x3A940008
		opword 0x3BFF0001
		opword 0x807B0008
		opword 0x8003005C
		opword 0x7C1F0000
		opword 0x4180FBB0
		opword 0x7FC3F378
	}
}
#pragma pop
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
        if (dotProduct < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        if (((sp80.z * vector->edge0.x) - (sp80.x * vector->edge0.z)) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp8C);
        if (((sp8C.z * vector->edge1.x) - (sp8C.x * vector->edge1.z)) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp98);
        if (((sp98.z * vector->edge2.x) - (sp98.x * vector->edge2.z)) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
    } else {
        if ((vector->normal.y * dotProduct) <= EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        if ((dotProduct * ((sp80.z * vector->edge0.x) - (sp80.x * vector->edge0.z))) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp8C);
        if ((dotProduct * ((sp8C.z * vector->edge1.x) - (sp8C.x * vector->edge1.z))) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp98);
        if ((dotProduct * ((sp98.z * vector->edge2.x) - (sp98.x * vector->edge2.z))) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
    }
    temp_f2 = -vector->normal.y;
    if ((query->targetDistance >= EXT_LIT(float_0_80419758, 0.0f)) && ((-dotProduct / temp_f2) >= query->targetDistance)) {
        return 0;
    }
    query->targetDistance = -dotProduct / temp_f2;
    query->hitPos.x = query->targetPos.x;
    query->hitPos.y = query->targetPos.y - query->targetDistance;
    query->hitPos.z = query->targetPos.z;
    if (dotProduct >= EXT_LIT(float_0_80419758, 0.0f)) {
        query->hitNormal = vector->normal;
    } else {
        PSVECScale(&vector->normal, &query->hitNormal, EXT_LIT(float_neg1_80419768, -1.0f));
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
        if (dotProduct < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        if (((sp5C.z * vector->edge0.x) - (sp5C.x * vector->edge0.z)) > EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp68);
        if (((sp68.z * vector->edge1.x) - (sp68.x * vector->edge1.z)) > EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp74);
        if (((sp74.z * vector->edge2.x) - (sp74.x * vector->edge2.z)) > EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
    } else {
        if ((vector->normal.y * dotProduct) >= EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        if ((dotProduct * ((sp5C.z * vector->edge0.x) - (sp5C.x * vector->edge0.z))) > EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp68);
        if ((dotProduct * ((sp68.z * vector->edge1.x) - (sp68.x * vector->edge1.z))) > EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp74);
        if ((dotProduct * ((sp74.z * vector->edge2.x) - (sp74.x * vector->edge2.z))) > EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
    }
    temp_f2 = vector->normal.y;
    if ((query->targetDistance >= EXT_LIT(float_0_80419758, 0.0f)) && ((-dotProduct / temp_f2) >= query->targetDistance)) {
        return 0;
    }
    query->targetDistance = -dotProduct / temp_f2;
    query->hitPos.x = query->targetPos.x;
    query->hitPos.y = query->targetPos.y + query->targetDistance;
    query->hitPos.z = query->targetPos.z;
    if (dotProduct >= EXT_LIT(float_0_80419758, 0.0f)) {
        query->hitNormal = vector->normal;
    } else {
        PSVECScale(&vector->normal, &query->hitNormal, EXT_LIT(float_neg1_80419768, -1.0f));
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
        if (dotProduct < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECCrossProduct(&query->targetDir, &vector->edge0, &sp2C);
        if (PSVECDotProduct(&sp8, &sp2C) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp14);
        PSVECCrossProduct(&query->targetDir, &vector->edge1, &sp38);
        if (PSVECDotProduct(&sp14, &sp38) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp20);
        PSVECCrossProduct(&query->targetDir, &vector->edge2, &sp44);
        if (PSVECDotProduct(&sp20, &sp44) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        var_f27 = PSVECDotProduct(&vector->normal, &query->targetDir);
    } else {
        var_f27 = PSVECDotProduct(&vector->normal, &query->targetDir);
        if ((var_f27 * dotProduct) >= EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECCrossProduct(&query->targetDir, &vector->edge0, &sp2C);
        if ((dotProduct * PSVECDotProduct(&sp8, &sp2C)) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &sp14);
        PSVECCrossProduct(&query->targetDir, &vector->edge1, &sp38);
        if ((dotProduct * PSVECDotProduct(&sp14, &sp38)) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &sp20);
        PSVECCrossProduct(&query->targetDir, &vector->edge2, &sp44);
        if ((dotProduct * PSVECDotProduct(&sp20, &sp44)) < EXT_LIT(float_0_80419758, 0.0f)) {
            return 0;
        }
    }

    if ((query->targetDistance >= EXT_LIT(float_0_80419758, 0.0f)) && ((-dotProduct / var_f27) >= query->targetDistance)) {
        return 0;
    }
    query->targetDistance = -dotProduct / var_f27;
    PSVECScale(&query->targetDir, &sp50, query->targetDistance);
    PSVECAdd(&query->targetPos, &sp50, &query->hitPos);
    if (dotProduct >= EXT_LIT(float_0_80419758, 0.0f)) {
        query->hitNormal = vector->normal;
    } else {
        PSVECScale(&vector->normal, &query->hitNormal, EXT_LIT(float_neg1_80419768, -1.0f));
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
    var_f29 = EXT_LIT(float_neg1_80419768, -1.0f);
    temp = EXT_LIT(float_0p5_8041976c, 0.5f);
    temp_f28 = query->targetDistance * temp;
    PSVECScale(&query->targetDir, &spA4, temp_f28);
    PSVECAdd(&query->targetPos, &spA4, &spA4);
    var_r29 = unk_80418408;
    if (query->targetDir.y == EXT_LIT(float_0_80419758, 0.0f)) {
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
                            !(PSVECDotProduct(&var_r31->normal, &query->targetDir) >= EXT_LIT(float_0_80419758, 0.0f))) {
                            if (checkTriVec_xz(query, var_r31) && (var_f29 < EXT_LIT(float_0_80419758, 0.0f) || var_f29 > query->targetDistance)) {
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
    } else if (query->targetDir.x == EXT_LIT(float_0_80419758, 0.0f) && query->targetDir.z == EXT_LIT(float_0_80419758, 0.0f)) {
        if (query->targetDir.y == EXT_LIT(float_neg1_80419768, -1.0f)) {
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
                            if (query->singleSided == 0 || !(vector->normal.y <= EXT_LIT(float_0_80419758, 0.0f))) {
                                if (tempfunc(query, vector) && (var_f29 < EXT_LIT(float_0_80419758, 0.0f) || var_f29 > query->targetDistance)) {
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
        } else if (query->targetDir.y == EXT_LIT(float_1_80419764, 1.0f)) {
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
                            if (query->singleSided == 0 || !(vector->normal.y >= EXT_LIT(float_0_80419758, 0.0f))) {
                                if (tempfunc2(query, vector) && (var_f29 < EXT_LIT(float_0_80419758, 0.0f) || var_f29 > query->targetDistance)) {
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
                        if (query->singleSided == 0 || !(PSVECDotProduct(&vector->normal, &query->targetDir) >= EXT_LIT(float_0_80419758, 0.0f))) {
                            if (tempfunc3(query, vector) && (var_f29 < EXT_LIT(float_0_80419758, 0.0f) || var_f29 > query->targetDistance)) {
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* hitCheckVecFilter(HitCheckQuery* query, HitFilterCallback callback) {
	char _af_pad[200];
	asm volatile {
		mr r26, r3
		opword 0x7C9B2378
		bl mapGetWork
		opword 0x387A0018
		opword 0x3B800000
		bl PSVECSquareMag
		lfs f0, float_0_80419758(r2)
		opword 0xFC010000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000C68
		opword 0xC03A003C
		opword 0x387A0018
		lfs f0, float_0p5_8041976c(r2)
		la r4, _af_pad+156
		lfs f29, float_neg1_80419768(r2)
		opword 0xEF810032
		opword 0xFC20E090
		bl PSVECScale
		opword 0x388100A4
		opword 0x387A000C
		opword 0x7C852378
		bl PSVECAdd
		lfs f1, float_0_80419758(r2)
		opword 0xC05A001C
		lwz r29, unk_80418408(r13)
		opword 0xFC011000
		opword 0x40820130
		opword 0x48000120
		opword 0x281B0000
		opword 0x41820020
		opword 0x7F6CDB78
		opword 0x7F43D378
		opword 0x7FA4EB78
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x2C030000
		opword 0x418200F8
		opword 0x386100A4
		opword 0x389D00C0
		bl PSVECDistance
		opword 0xC01D00CC
		opword 0xEC1C002A
		opword 0xFC010040
		opword 0x418100DC
		opword 0x807D0008
		opword 0x80630058
		opword 0x88030001
		opword 0x28000001
		opword 0x40820010
		opword 0x38000001
		opword 0x901A0000
		opword 0x4800000C
		opword 0x38000000
		opword 0x901A0000
		opword 0x83FD00AC
		opword 0x3BC00000
		opword 0x4800009C
		opword 0x801A0000
		opword 0x2C000000
		opword 0x41820020
		opword 0x387F0048
		opword 0x389A0018
		bl PSVECDotProduct
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4182006C
		opword 0x7F43D378
		opword 0x7FE4FB78
		bl checkTriVec_xz
		opword 0x2C030000
		opword 0x41820058
		lfs f0, float_0_80419758(r2)
		opword 0xFC1D0040
		opword 0x41800010
		opword 0xC01A003C
		opword 0xFC1D0040
		opword 0x40810040
		opword 0xC3BA003C
		opword 0x7FBCEB78
		opword 0x80DA0024
		opword 0x80BA0028
		opword 0xFFC0E890
		opword 0x809A002C
		opword 0x807A0030
		opword 0x801A0034
		opword 0x90C100C8
		opword 0x906100BC
		opword 0x900100C0
		opword 0x801A0038
		opword 0x90A100CC
		opword 0x908100D0
		opword 0x900100C4
		opword 0x3BDE0001
		opword 0x3BFF0054
		opword 0xA81D00A8
		opword 0x7C1E0000
		opword 0x4180FF60
		opword 0x83BD00E0
		opword 0x281D0000
		opword 0x4082FEE0
		opword 0x48000AA4
		opword 0xC01A0018
		opword 0xFC010000
		opword 0x40820A90
		opword 0xC01A0020
		opword 0xFC010000
		opword 0x40820A84
		lfs f0, float_neg1_80419768(r2)
		opword 0xFC001000
		opword 0x4082036C
		opword 0x4800035C
		opword 0x281B0000
		opword 0x41820020
		opword 0x7F6CDB78
		opword 0x7F43D378
		opword 0x7FA4EB78
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x2C030000
		opword 0x41820334
		opword 0x386100A4
		opword 0x389D00C0
		bl PSVECDistance
		opword 0xC01D00CC
		opword 0xEC1C002A
		opword 0xFC010040
		opword 0x41810318
		opword 0x807D0008
		opword 0x80630058
		opword 0x88030001
		opword 0x28000001
		opword 0x40820010
		opword 0x38000001
		opword 0x901A0000
		opword 0x4800000C
		opword 0x38000000
		opword 0x901A0000
		opword 0x83DD00AC
		opword 0x3BE00000
		opword 0x480002D8
		opword 0x801A0000
		opword 0x2C000000
		opword 0x41820018
		opword 0xC03E004C
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x418202B0
		opword 0x7FC4F378
		opword 0x387A000C
		opword 0x38A10080
		bl PSVECSubtract
		opword 0x387E0048
		opword 0x38810080
		bl PSVECDotProduct
		opword 0x801A0000
		opword 0xFFE00890
		opword 0x2C000000
		opword 0x418200B8
		lfs f3, float_0_80419758(r2)
		opword 0xFC1F1840
		opword 0x4080000C
		opword 0x38000000
		opword 0x48000214
		opword 0xC0210080
		opword 0xC01E002C
		opword 0xC0410088
		opword 0xEC010032
		opword 0xC03E0024
		opword 0xEC020078
		opword 0xFC001840
		opword 0x4080000C
		opword 0x38000000
		opword 0x480001EC
		opword 0x387A000C
		opword 0x389E000C
		opword 0x38A1008C
		bl PSVECSubtract
		opword 0xC021008C
		opword 0xC01E0038
		opword 0xC0610094
		opword 0xEC210032
		opword 0xC05E0030
		lfs f0, float_0_80419758(r2)
		opword 0xEC2308B8
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x480001B0
		opword 0x387A000C
		opword 0x389E0018
		opword 0x38A10098
		bl PSVECSubtract
		opword 0xC0210098
		opword 0xC01E0044
		opword 0xC06100A0
		opword 0xEC210032
		opword 0xC05E003C
		lfs f0, float_0_80419758(r2)
		opword 0xEC2308B8
		opword 0xFC010040
		opword 0x408000D8
		opword 0x38000000
		opword 0x48000174
		opword 0xC01E004C
		lfs f3, float_0_80419758(r2)
		opword 0xEC0007F2
		opword 0xFC001840
		opword 0x4C401382
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000154
		opword 0xC0210080
		opword 0xC01E002C
		opword 0xC0410088
		opword 0xEC010032
		opword 0xC03E0024
		opword 0xEC020078
		opword 0xEC1F0032
		opword 0xFC001840
		opword 0x4080000C
		opword 0x38000000
		opword 0x48000128
		opword 0x387A000C
		opword 0x389E000C
		opword 0x38A1008C
		bl PSVECSubtract
		opword 0xC021008C
		opword 0xC01E0038
		opword 0xC0610094
		opword 0xEC210032
		opword 0xC05E0030
		lfs f0, float_0_80419758(r2)
		opword 0xEC2308B8
		opword 0xEC3F0072
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x480000E8
		opword 0x387A000C
		opword 0x389E0018
		opword 0x38A10098
		bl PSVECSubtract
		opword 0xC0210098
		opword 0xC01E0044
		opword 0xC06100A0
		opword 0xEC210032
		opword 0xC05E003C
		lfs f0, float_0_80419758(r2)
		opword 0xEC2308B8
		opword 0xEC3F0072
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x480000A8
		opword 0xC07A003C
		lfs f0, float_0_80419758(r2)
		opword 0xC03E004C
		opword 0xFC030040
		opword 0xFC400850
		opword 0x4C411382
		opword 0x40820020
		opword 0xFC00F850
		opword 0xEC001024
		opword 0xFC001840
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000070
		opword 0xFC20F850
		lfs f0, float_0_80419758(r2)
		opword 0xFC1F0040
		opword 0xEC011024
		opword 0xD01A003C
		opword 0xC01A000C
		opword 0xD01A0024
		opword 0xC03A0010
		opword 0xC01A003C
		opword 0xEC010028
		opword 0xD01A0028
		opword 0xC01A0014
		opword 0xD01A002C
		opword 0x4C411382
		opword 0x40820020
		opword 0x807E0048
		opword 0x801E004C
		opword 0x907A0030
		opword 0x901A0034
		opword 0x801E0050
		opword 0x901A0038
		opword 0x48000014
		lfs f1, float_neg1_80419768(r2)
		opword 0x387E0048
		opword 0x389A0030
		bl PSVECScale
		opword 0x38000001
		opword 0x2C000000
		opword 0x41820058
		lfs f0, float_0_80419758(r2)
		opword 0xFC1D0040
		opword 0x41800010
		opword 0xC01A003C
		opword 0xFC1D0040
		opword 0x40810040
		opword 0xC3BA003C
		opword 0x7FBCEB78
		opword 0x80DA0024
		opword 0x80BA0028
		opword 0xFFC0E890
		opword 0x809A002C
		opword 0x807A0030
		opword 0x801A0034
		opword 0x90C100C8
		opword 0x906100BC
		opword 0x900100C0
		opword 0x801A0038
		opword 0x90A100CC
		opword 0x908100D0
		opword 0x900100C4
		opword 0x3BFF0001
		opword 0x3BDE0054
		opword 0xA81D00A8
		opword 0x7C1F0000
		opword 0x4180FD24
		opword 0x83BD00E0
		opword 0x281D0000
		opword 0x4082FCA4
		opword 0x48000718
		lfs f0, float_1_80419764(r2)
		opword 0xFC001000
		opword 0x40820704
		opword 0x48000358
		opword 0x281B0000
		opword 0x41820020
		opword 0x7F6CDB78
		opword 0x7F43D378
		opword 0x7FA4EB78
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x2C030000
		opword 0x41820330
		opword 0x386100A4
		opword 0x389D00C0
		bl PSVECDistance
		opword 0xC01D00CC
		opword 0xEC1C002A
		opword 0xFC010040
		opword 0x41810314
		opword 0x807D0008
		opword 0x80630058
		opword 0x88030001
		opword 0x28000001
		opword 0x40820010
		opword 0x38000001
		opword 0x901A0000
		opword 0x4800000C
		opword 0x38000000
		opword 0x901A0000
		opword 0x83DD00AC
		opword 0x3BE00000
		opword 0x480002D4
		opword 0x801A0000
		opword 0x2C000000
		opword 0x41820018
		opword 0xC03E004C
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x418202AC
		opword 0x7FC4F378
		opword 0x387A000C
		opword 0x38A1005C
		bl PSVECSubtract
		opword 0x387E0048
		opword 0x3881005C
		bl PSVECDotProduct
		opword 0x801A0000
		opword 0xFFE00890
		opword 0x2C000000
		opword 0x418200B8
		lfs f3, float_0_80419758(r2)
		opword 0xFC1F1840
		opword 0x4080000C
		opword 0x38000000
		opword 0x48000210
		opword 0xC021005C
		opword 0xC01E002C
		opword 0xC0410064
		opword 0xEC010032
		opword 0xC03E0024
		opword 0xEC020078
		opword 0xFC001840
		opword 0x4081000C
		opword 0x38000000
		opword 0x480001E8
		opword 0x387A000C
		opword 0x389E000C
		opword 0x38A10068
		bl PSVECSubtract
		opword 0xC0210068
		opword 0xC01E0038
		opword 0xC0610070
		opword 0xEC210032
		opword 0xC05E0030
		lfs f0, float_0_80419758(r2)
		opword 0xEC2308B8
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38000000
		opword 0x480001AC
		opword 0x387A000C
		opword 0x389E0018
		opword 0x38A10074
		bl PSVECSubtract
		opword 0xC0210074
		opword 0xC01E0044
		opword 0xC061007C
		opword 0xEC210032
		opword 0xC05E003C
		lfs f0, float_0_80419758(r2)
		opword 0xEC2308B8
		opword 0xFC010040
		opword 0x408100D8
		opword 0x38000000
		opword 0x48000170
		opword 0xC01E004C
		lfs f3, float_0_80419758(r2)
		opword 0xEC0007F2
		opword 0xFC001840
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000150
		opword 0xC021005C
		opword 0xC01E002C
		opword 0xC0410064
		opword 0xEC010032
		opword 0xC03E0024
		opword 0xEC020078
		opword 0xEC1F0032
		opword 0xFC001840
		opword 0x4081000C
		opword 0x38000000
		opword 0x48000124
		opword 0x387A000C
		opword 0x389E000C
		opword 0x38A10068
		bl PSVECSubtract
		opword 0xC0210068
		opword 0xC01E0038
		opword 0xC0610070
		opword 0xEC210032
		opword 0xC05E0030
		lfs f0, float_0_80419758(r2)
		opword 0xEC2308B8
		opword 0xEC3F0072
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38000000
		opword 0x480000E4
		opword 0x387A000C
		opword 0x389E0018
		opword 0x38A10074
		bl PSVECSubtract
		opword 0xC0210074
		opword 0xC01E0044
		opword 0xC061007C
		opword 0xEC210032
		opword 0xC05E003C
		lfs f0, float_0_80419758(r2)
		opword 0xEC2308B8
		opword 0xEC3F0072
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38000000
		opword 0x480000A4
		opword 0xC03A003C
		lfs f0, float_0_80419758(r2)
		opword 0xC05E004C
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820020
		opword 0xFC00F850
		opword 0xEC001024
		opword 0xFC000840
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000070
		opword 0xFC20F850
		lfs f0, float_0_80419758(r2)
		opword 0xFC1F0040
		opword 0xEC011024
		opword 0xD01A003C
		opword 0xC01A000C
		opword 0xD01A0024
		opword 0xC03A0010
		opword 0xC01A003C
		opword 0xEC01002A
		opword 0xD01A0028
		opword 0xC01A0014
		opword 0xD01A002C
		opword 0x4C411382
		opword 0x40820020
		opword 0x807E0048
		opword 0x801E004C
		opword 0x907A0030
		opword 0x901A0034
		opword 0x801E0050
		opword 0x901A0038
		opword 0x48000014
		lfs f1, float_neg1_80419768(r2)
		opword 0x387E0048
		opword 0x389A0030
		bl PSVECScale
		opword 0x38000001
		opword 0x2C000000
		opword 0x41820058
		lfs f0, float_0_80419758(r2)
		opword 0xFC1D0040
		opword 0x41800010
		opword 0xC01A003C
		opword 0xFC1D0040
		opword 0x40810040
		opword 0xC3BA003C
		opword 0x7FBCEB78
		opword 0x80DA0024
		opword 0x80BA0028
		opword 0xFFC0E890
		opword 0x809A002C
		opword 0x807A0030
		opword 0x801A0034
		opword 0x90C100C8
		opword 0x906100BC
		opword 0x900100C0
		opword 0x801A0038
		opword 0x90A100CC
		opword 0x908100D0
		opword 0x900100C4
		opword 0x3BFF0001
		opword 0x3BDE0054
		opword 0xA81D00A8
		opword 0x7C1F0000
		opword 0x4180FD28
		opword 0x83BD00E0
		opword 0x281D0000
		opword 0x4082FCA8
		opword 0x480003A8
		opword 0x4800039C
		opword 0x281B0000
		opword 0x41820020
		opword 0x7F6CDB78
		opword 0x7F43D378
		opword 0x7FA4EB78
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x2C030000
		opword 0x41820374
		opword 0x386100A4
		opword 0x389D00C0
		bl PSVECDistance
		opword 0xC01D00CC
		opword 0xEC1C002A
		opword 0xFC010040
		opword 0x41810358
		opword 0x807D0008
		opword 0x80630058
		opword 0x88030001
		opword 0x28000001
		opword 0x40820010
		opword 0x38000001
		opword 0x901A0000
		opword 0x4800000C
		opword 0x38000000
		opword 0x901A0000
		opword 0x83DD00AC
		opword 0x3BE00000
		opword 0x48000318
		opword 0x801A0000
		opword 0x2C000000
		opword 0x41820020
		opword 0x387E0048
		opword 0x389A0018
		bl PSVECDotProduct
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x418202E8
		opword 0x7FC4F378
		opword 0x387A000C
		opword 0x38A10008
		bl PSVECSubtract
		opword 0x387E0048
		opword 0x38810008
		bl PSVECDotProduct
		opword 0x801A0000
		opword 0xFFE00890
		opword 0x2C000000
		opword 0x418200DC
		lfs f0, float_0_80419758(r2)
		opword 0xFC1F0040
		opword 0x4080000C
		opword 0x38000000
		opword 0x4800024C
		opword 0x387A0018
		opword 0x389E0024
		opword 0x38A1002C
		bl PSVECCrossProduct
		opword 0x38610008
		opword 0x3881002C
		bl PSVECDotProduct
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x4800021C
		opword 0x387A000C
		opword 0x389E000C
		opword 0x38A10014
		bl PSVECSubtract
		opword 0x387A0018
		opword 0x389E0030
		opword 0x38A10038
		bl PSVECCrossProduct
		opword 0x38610014
		opword 0x38810038
		bl PSVECDotProduct
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x480001DC
		opword 0x387A000C
		opword 0x389E0018
		opword 0x38A10020
		bl PSVECSubtract
		opword 0x387A0018
		opword 0x389E003C
		opword 0x38A10044
		bl PSVECCrossProduct
		opword 0x38610020
		opword 0x38810044
		bl PSVECDotProduct
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x4800019C
		opword 0x387E0048
		opword 0x389A0018
		bl PSVECDotProduct
		fmr f27, f1
		opword 0x480000EC
		opword 0x387E0048
		opword 0x389A0018
		bl PSVECDotProduct
		opword 0xFF600890
		lfs f0, float_0_80419758(r2)
		opword 0xEC3B07F2
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800015C
		opword 0x387A0018
		opword 0x389E0024
		opword 0x38A1002C
		bl PSVECCrossProduct
		opword 0x38610008
		opword 0x3881002C
		bl PSVECDotProduct
		opword 0xEC3F0072
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x48000128
		opword 0x387A000C
		opword 0x389E000C
		opword 0x38A10014
		bl PSVECSubtract
		opword 0x387A0018
		opword 0x389E0030
		opword 0x38A10038
		bl PSVECCrossProduct
		opword 0x38610014
		opword 0x38810038
		bl PSVECDotProduct
		opword 0xEC3F0072
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x480000E4
		opword 0x387A000C
		opword 0x389E0018
		opword 0x38A10020
		bl PSVECSubtract
		opword 0x387A0018
		opword 0x389E003C
		opword 0x38A10044
		bl PSVECCrossProduct
		opword 0x38610020
		opword 0x38810044
		bl PSVECDotProduct
		opword 0xEC3F0072
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x480000A0
		opword 0xC03A003C
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820020
		opword 0xFC00F850
		opword 0xEC00D824
		opword 0xFC000840
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000070
		opword 0xFC00F850
		opword 0x387A0018
		opword 0x38810050
		opword 0xEC00D824
		opword 0xD01A003C
		opword 0xC03A003C
		bl PSVECScale
		opword 0x387A000C
		opword 0x38810050
		opword 0x38BA0024
		bl PSVECAdd
		lfs f0, float_0_80419758(r2)
		opword 0xFC1F0040
		opword 0x4C411382
		opword 0x40820020
		opword 0x807E0048
		opword 0x801E004C
		opword 0x907A0030
		opword 0x901A0034
		opword 0x801E0050
		opword 0x901A0038
		opword 0x48000014
		lfs f1, float_neg1_80419768(r2)
		opword 0x387E0048
		opword 0x389A0030
		bl PSVECScale
		opword 0x38000001
		opword 0x2C000000
		opword 0x41820058
		lfs f0, float_0_80419758(r2)
		opword 0xFC1D0040
		opword 0x41800010
		opword 0xC01A003C
		opword 0xFC1D0040
		opword 0x40810040
		opword 0xC3BA003C
		opword 0x7FBCEB78
		opword 0x80DA0024
		opword 0x80BA0028
		opword 0xFFC0E890
		opword 0x809A002C
		opword 0x807A0030
		opword 0x801A0034
		opword 0x90C100C8
		opword 0x906100BC
		opword 0x900100C0
		opword 0x801A0038
		opword 0x90A100CC
		opword 0x908100D0
		opword 0x900100C4
		opword 0x3BFF0001
		opword 0x3BDE0054
		opword 0xA81D00A8
		opword 0x7C1F0000
		opword 0x4180FCE4
		opword 0x83BD00E0
		opword 0x281D0000
		opword 0x4082FC64
		opword 0x281C0000
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000048
		opword 0x386100BC
		opword 0x388100B0
		bl PSVECNormalize
		opword 0xD3DA003C
		opword 0x7F83E378
		opword 0x800100C8
		opword 0x808100CC
		opword 0x901A0024
		opword 0x800100D0
		opword 0x909A0028
		opword 0x901A002C
		opword 0x808100B0
		opword 0x800100B4
		opword 0x909A0030
		opword 0x901A0034
		opword 0x800100B8
		opword 0x901A0038
	}
}
#pragma pop
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
HitEntry* hitCheckFilter(HitFilterCallback callback, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX,
                         f32* hitNY, f32* hitNZ, f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz) {
	char _af_pad[88];
	asm {
		lis r12, lbl_802C1538@ha
		lis r11, vec3_802c153c+0x8@ha
	}
	asm volatile {
		addi r24, r12, lbl_802C1538@l
		addi r12, r11, vec3_802c153c+0x8@l
		opword 0x7CFC3B78
		mr r22, r3
		opword 0x7C992378
		opword 0x7CBA2B78
		opword 0x7CDB3378
		opword 0x7D3E4B78
		la r3, _af_pad+24
		opword 0x7D5F5378
		opword 0x7EC4B378
		opword 0x83B80000
		opword 0x82F80004
		opword 0x93A10014
		opword 0x7D1D4378
		opword 0x83180008
		opword 0x816C0000
		opword 0x80EC0004
		opword 0x800C0008
		opword 0x92E10018
		opword 0x9301001C
		opword 0x91610008
		opword 0x90E1000C
		opword 0x90010010
		opword 0xD0210014
		opword 0xD0410018
		opword 0x81210014
		opword 0xD061001C
		opword 0x81010018
		opword 0xD0810008
		opword 0x80E1001C
		opword 0xD0A1000C
		opword 0x80C10008
		opword 0xD0C10010
		opword 0x80A1000C
		opword 0x80010010
		opword 0x9121002C
		opword 0x91010030
		opword 0x90E10034
		opword 0x90C10038
		opword 0x90A1003C
		opword 0x90010040
		opword 0xC01C0000
		opword 0xD001005C
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x4800003C
		opword 0xC001005C
		opword 0xD01C0000
		opword 0xC0010044
		opword 0xD0190000
		opword 0xC0010048
		opword 0xD01A0000
		opword 0xC001004C
		opword 0xD01B0000
		opword 0xC0010050
		opword 0xD01D0000
		opword 0xC0010054
		opword 0xD01E0000
		opword 0xC0010058
		opword 0xD01F0000
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
BOOL checkTriVec_xz(HitCheckQuery* query, HitVector* vector) {
    Vec v1, v2, v3;
    f32 cosAngle;
    f32 distToTrianglePlane;

    PSVECSubtract(&query->targetPos, &vector->v0, &v1);
    distToTrianglePlane = PSVECDotProduct(&vector->normal, &v1);
    if (query->singleSided != 0) {
        if (distToTrianglePlane < EXT_LIT(float_0_80419758, 0.0f)) {
            return FALSE;
        }
        if ((v1.x * (-vector->edge0.y * query->targetDir.z)) +
                (v1.y * ((vector->edge0.x * query->targetDir.z) - (vector->edge0.z * query->targetDir.x))) +
                (v1.z * (vector->edge0.y * query->targetDir.x)) <
            EXT_LIT(float_0_80419758, 0.0f)) {
            return FALSE;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &v2);
        if ((v2.x * (-vector->edge1.y * query->targetDir.z)) +
                (v2.y * ((vector->edge1.x * query->targetDir.z) - (vector->edge1.z * query->targetDir.x))) +
                (v2.z * (vector->edge1.y * query->targetDir.x)) <
            EXT_LIT(float_0_80419758, 0.0f)) {
            return FALSE;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &v3);
        if ((v3.x * (-vector->edge2.y * query->targetDir.z)) +
                (v3.y * ((vector->edge2.x * query->targetDir.z) - (vector->edge2.z * query->targetDir.x))) +
                (v3.z * (vector->edge2.y * query->targetDir.x)) <
            EXT_LIT(float_0_80419758, 0.0f)) {
            return FALSE;
        }
    } else {
        if (((vector->normal.x * query->targetDir.x) + (vector->normal.z * query->targetDir.z)) * distToTrianglePlane >=
            EXT_LIT(float_0_80419758, 0.0f)) {
            return FALSE;
        }
        if (((v1.x * (-vector->edge0.y * query->targetDir.z)) +
             (v1.y * ((vector->edge0.x * query->targetDir.z) - (vector->edge0.z * query->targetDir.x))) +
             (v1.z * (vector->edge0.y * query->targetDir.x))) *
                distToTrianglePlane <
            EXT_LIT(float_0_80419758, 0.0f)) {
            return FALSE;
        }
        PSVECSubtract(&query->targetPos, &vector->v1, &v2);
        if (((v2.x * (-vector->edge1.y * query->targetDir.z)) +
             (v2.y * ((vector->edge1.x * query->targetDir.z) - (vector->edge1.z * query->targetDir.x))) +
             (v2.z * (vector->edge1.y * query->targetDir.x))) *
                distToTrianglePlane <
            EXT_LIT(float_0_80419758, 0.0f)) {
            return FALSE;
        }
        PSVECSubtract(&query->targetPos, &vector->v2, &v3);
        if (((v3.x * (-vector->edge2.y * query->targetDir.z)) +
             (v3.y * ((vector->edge2.x * query->targetDir.z) - (vector->edge2.z * query->targetDir.x))) +
             (v3.z * (vector->edge2.y * query->targetDir.x))) *
                distToTrianglePlane <
            EXT_LIT(float_0_80419758, 0.0f)) {
            return FALSE;
        }
    }
    cosAngle = (vector->normal.x * query->targetDir.x) + (vector->normal.z * query->targetDir.z);
    if (query->targetDistance >= EXT_LIT(float_0_80419758, 0.0f) && -distToTrianglePlane / cosAngle >= query->targetDistance) {
        return FALSE;
    }
    query->targetDistance = -distToTrianglePlane / cosAngle;
    query->hitPos.x = query->targetPos.x + (query->targetDir.x * query->targetDistance);
    query->hitPos.y = query->targetPos.y;
    query->hitPos.z = query->targetPos.z + (query->targetDir.z * query->targetDistance);
    if (distToTrianglePlane >= EXT_LIT(float_0_80419758, 0.0f)) {
        query->hitNormal = vector->normal;
    } else {
        PSVECScale(&vector->normal, &query->hitNormal, EXT_LIT(float_neg1_80419768, -1.0f));
    }
    return TRUE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
BOOL checkTriVec_xz(HitCheckQuery* query, HitVector* vector) {
	asm volatile {
		opword 0x9421FFB0
		opword 0x7C0802A6
		opword 0x90010054
		opword 0xDBE10040
		opword 0xF3E10048
		opword 0x93E1003C
		opword 0x93C10038
		opword 0x7C7E1B78
		opword 0x7C9F2378
		opword 0x387E000C
		opword 0x38A10020
		bl PSVECSubtract
		opword 0x387F0048
		opword 0x38810020
		bl PSVECDotProduct
		opword 0x801E0000
		opword 0xFFE00890
		opword 0x2C000000
		opword 0x41820130
		lfs f6, float_0_80419758(r2)
		opword 0xFC1F3040
		opword 0x4080000C
		opword 0x38600000
		opword 0x48000330
		opword 0xC09E0018
		opword 0xC01F002C
		opword 0xC0BF0028
		opword 0xEC000132
		opword 0xC0FE0020
		opword 0xC03F0024
		opword 0xFC602850
		opword 0xC0410024
		opword 0xECA50132
		opword 0xEC0101F8
		opword 0xC0810020
		opword 0xEC2301F2
		opword 0xC0610028
		opword 0xEC020032
		opword 0xEC04007A
		opword 0xEC03017A
		opword 0xFC003040
		opword 0x4080000C
		opword 0x38600000
		opword 0x480002E0
		opword 0x387E000C
		opword 0x389F000C
		opword 0x38A10014
		bl PSVECSubtract
		opword 0xC09E0018
		opword 0xC01F0038
		opword 0xC0BF0034
		opword 0xEC000132
		opword 0xC0DE0020
		opword 0xC03F0030
		opword 0xFC602850
		opword 0xC0410018
		opword 0xECA50132
		opword 0xEC2101B8
		opword 0xC0810014
		opword 0xEC6301B2
		opword 0xC0C1001C
		lfs f0, float_0_80419758(r2)
		opword 0xEC220072
		opword 0xEC2408FA
		opword 0xEC26097A
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600000
		opword 0x4800027C
		opword 0x387E000C
		opword 0x389F0018
		opword 0x38A10008
		bl PSVECSubtract
		opword 0xC09E0018
		opword 0xC01F0044
		opword 0xC0BF0040
		opword 0xEC000132
		opword 0xC0DE0020
		opword 0xC03F003C
		opword 0xFC602850
		opword 0xC041000C
		opword 0xECA50132
		opword 0xEC2101B8
		opword 0xC0810008
		opword 0xEC6301B2
		opword 0xC0C10010
		lfs f0, float_0_80419758(r2)
		opword 0xEC220072
		opword 0xEC2408FA
		opword 0xEC26097A
		opword 0xFC010040
		opword 0x4080015C
		opword 0x38600000
		opword 0x48000218
		opword 0xC01F0050
		opword 0xC11E0020
		opword 0xC03F0048
		opword 0xEC000232
		opword 0xC0BE0018
		lfs f7, float_0_80419758(r2)
		opword 0xEC01017A
		opword 0xEC1F0032
		opword 0xFC003840
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38600000
		opword 0x480001E4
		opword 0xC01F002C
		opword 0xC0DF0028
		opword 0xEC000172
		opword 0xC03F0024
		opword 0xFC603050
		opword 0xC0410024
		opword 0xC0810020
		opword 0xECA60172
		opword 0xEC010238
		opword 0xC0C10028
		opword 0xEC230232
		opword 0xEC020032
		opword 0xEC04007A
		opword 0xEC06017A
		opword 0xEC1F0032
		opword 0xFC003840
		opword 0x4080000C
		opword 0x38600000
		opword 0x48000198
		opword 0x387E000C
		opword 0x389F000C
		opword 0x38A10014
		bl PSVECSubtract
		opword 0xC09E0018
		opword 0xC01F0038
		opword 0xC0BF0034
		opword 0xEC000132
		opword 0xC0DE0020
		opword 0xC03F0030
		opword 0xFC602850
		opword 0xC0410018
		opword 0xECA50132
		opword 0xEC2101B8
		opword 0xC0810014
		opword 0xEC6301B2
		opword 0xC0C1001C
		lfs f0, float_0_80419758(r2)
		opword 0xEC220072
		opword 0xEC2408FA
		opword 0xEC26097A
		opword 0xEC3F0072
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600000
		opword 0x48000130
		opword 0x387E000C
		opword 0x389F0018
		opword 0x38A10008
		bl PSVECSubtract
		opword 0xC09E0018
		opword 0xC01F0044
		opword 0xC0BF0040
		opword 0xEC000132
		opword 0xC0DE0020
		opword 0xC03F003C
		opword 0xFC602850
		opword 0xC041000C
		opword 0xECA50132
		opword 0xEC2101B8
		opword 0xC0810008
		opword 0xEC6301B2
		opword 0xC0C10010
		lfs f0, float_0_80419758(r2)
		opword 0xEC220072
		opword 0xEC2408FA
		opword 0xEC26097A
		opword 0xEC3F0072
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38600000
		opword 0x480000C8
		opword 0xC05F0050
		opword 0xC03E0020
		opword 0xC09E003C
		lfs f0, float_0_80419758(r2)
		opword 0xEC220072
		opword 0xC07F0048
		opword 0xC05E0018
		opword 0xFC040040
		opword 0xEC4308BA
		opword 0x4C411382
		opword 0x40820020
		opword 0xFC00F850
		opword 0xEC001024
		opword 0xFC002040
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38600000
		opword 0x48000080
		opword 0xFC20F850
		lfs f0, float_0_80419758(r2)
		opword 0xFC1F0040
		opword 0xEC011024
		opword 0xD01E003C
		opword 0xC05E0018
		opword 0xC03E003C
		opword 0xC01E000C
		opword 0xEC02007A
		opword 0xD01E0024
		opword 0xC01E0010
		opword 0xD01E0028
		opword 0xC05E0020
		opword 0xC03E003C
		opword 0xC01E0014
		opword 0xEC02007A
		opword 0xD01E002C
		opword 0x4C411382
		opword 0x40820020
		opword 0x807F0048
		opword 0x801F004C
		opword 0x907E0030
		opword 0x901E0034
		opword 0x801F0050
		opword 0x901E0038
		opword 0x48000014
		lfs f1, float_neg1_80419768(r2)
		opword 0x387F0048
		opword 0x389E0030
		bl PSVECScale
		opword 0x38600001
		opword 0xE3E10048
		opword 0x80010054
		opword 0xCBE10040
		opword 0x83E1003C
		opword 0x83C10038
		opword 0x7C0803A6
		opword 0x38210050
	}
}
#pragma pop
#endif

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
        if ((query->singleSided == 0 || !(PSVECDotProduct(&vector->normal, &query->targetDir) >= EXT_LIT(float_0_80419758, 0.0f))) &&
            checkTriVec_xz(query, vector)) {
            return 1;
        }
    }
    return 0;
}

BOOL chkFilterAttr(HitCheckQuery* query, HitEntry* entry) { // 1:1
    return (entry->attributes & query->user0) == 0;
}

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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
HitEntry* hitCheckAttr(s32 user0, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX, f32* hitNY, f32* hitNZ,
                       f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz) {
	char _af_pad[92];
	asm {
		lis r11, vec3_802c1548+0x8@ha
		lis r12, vec3_802c1554+0x8@ha
		la r0, _af_pad+24
	}
	asm volatile {
		addi r23, r11, vec3_802c1548+0x8@l
		addi r26, r12, vec3_802c1554+0x8@l
		lis r11, chkFilterAttr@ha
		opword 0x7CFC3B78
		opword 0x7C992378
		addi r7, r11, chkFilterAttr@l
		opword 0x7D1D4378
		opword 0x7D3E4B78
		opword 0x7CE43B78
		opword 0x83770000
		opword 0x83F70004
		opword 0x93610014
		opword 0x7CDB3378
		opword 0x82F70008
		opword 0x93E10018
		opword 0x7D5F5378
		opword 0x831A0000
		opword 0x819A0004
		opword 0x817A0008
		opword 0x7CBA2B78
		opword 0x92E1001C
		opword 0x93010008
		opword 0x9181000C
		opword 0x91610010
		opword 0xD0210014
		opword 0xD0410018
		opword 0x81410014
		opword 0xD061001C
		opword 0x81210018
		opword 0xD0810008
		opword 0x8101001C
		opword 0xD0A1000C
		opword 0x80E10008
		opword 0xD0C10010
		opword 0x80C1000C
		opword 0x80A10010
		opword 0x9141002C
		opword 0x91210030
		opword 0x91010034
		opword 0x90E10038
		opword 0x90C1003C
		opword 0x90A10040
		opword 0xC01C0000
		opword 0x90610024
		opword 0x7C030378
		opword 0xD001005C
		bl hitCheckVecFilter
		opword 0x28030000
		opword 0x4082000C
		opword 0x38600000
		opword 0x4800003C
		opword 0xC001005C
		opword 0xD01C0000
		opword 0xC0010044
		opword 0xD0190000
		opword 0xC0010048
		opword 0xD01A0000
		opword 0xC001004C
		opword 0xD01B0000
		opword 0xC0010050
		opword 0xD01D0000
		opword 0xC0010054
		opword 0xD01E0000
		opword 0xC0010058
		opword 0xD01F0000
	}
}
#pragma pop
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

    var_f28 = EXT_LIT(float_neg1_80419768, -1.0f);
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
                            if (var_f28 < EXT_LIT(float_0_80419758, 0.0f) || var_f28 > temp_f1) {
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
    if (var_f28 < (EXT_LIT(float_0p5_8041976c, 0.5f) * var_f31)) {
        return &map[entryId].hitEntries[objectId];
    }
    map = &map[entryId];
    temp_r27 = &map->hitEntries[objectId];
    PSVECSubtract(&temp_r27->centerWorld, &sp68, &query->targetDir);
    PSVECNormalize(&query->targetDir, &query->targetDir);
    var_f30 = EXT_LIT(float_neg1_80419768, -1.0f);
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
        if ((query->singleSided == 0) || !(PSVECDotProduct(&vector->normal, &query->targetDir) >= EXT_LIT(float_0_80419758, 0.0f))) {
            if (tempfunc3(query, vector) && ((var_f30 < EXT_LIT(float_0_80419758, 0.0f)) || (var_f30 > query->targetDistance))) {
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* hitCheckSphereFilter(HitFilterCallback callback, f32 x, f32 y, f32 z,
                               f32 distance) {
	char _af_pad[172];
	asm volatile {
		fmr f26, f1
		opword 0x7C791B78
		opword 0xFF601090
		opword 0xFFC01890
		opword 0xFFA02090
		bl mapGetWork
		lis r4, vec3_802c1560+0x8@ha
		opword 0x7C7E1B78
		addi r5, r4, vec3_802c1560+0x8@l
		lfs f28, float_neg1_80419768(r2)
		opword 0x80850000
		opword 0x7FDFF378
		opword 0x80650004
		la r26, _af_pad+108
		opword 0x80050008
		opword 0x3B80FFFF
		opword 0x9081005C
		opword 0x3BA00000
		opword 0x90610060
		opword 0x90010064
		opword 0xD341005C
		opword 0xD3610060
		opword 0x8081005C
		opword 0xD3C10064
		opword 0x80610060
		opword 0x80010064
		opword 0x90810068
		opword 0x9061006C
		opword 0x90010070
		opword 0x480000C4
		lwz r23, 0x15c(r31)
		opword 0x3B000000
		opword 0x480000A4
		opword 0x80170004
		opword 0x54000001
		opword 0x41820090
		opword 0x80770008
		opword 0x8003005C
		opword 0x2C000000
		opword 0x41820080
		opword 0xA0770000
		opword 0x546007FF
		opword 0x40820074
		opword 0x54600631
		opword 0x4082006C
		opword 0x38610068
		opword 0x389700C0
		bl PSVECDistance
		opword 0xC01700CC
		opword 0xFFC00890
		opword 0xEC1D002A
		opword 0xFC1E0040
		opword 0x4181004C
		opword 0x28190000
		opword 0x41820020
		opword 0x7F2CCB78
		opword 0x7F43D378
		opword 0x7EE4BB78
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x2C030000
		opword 0x41820028
		lfs f0, float_0_80419758(r2)
		opword 0xFC1C0040
		opword 0x4180000C
		opword 0xFC1CF040
		opword 0x40810014
		opword 0xFF80F090
		opword 0xC3F700CC
		opword 0x7F1CC378
		opword 0x7FBBEB78
		opword 0x3B180001
		opword 0x3AF700E4
		opword 0x801F0158
		opword 0x7C180000
		opword 0x4180FF58
		opword 0x3BFF0178
		opword 0x3BBD0001
		opword 0x801E0000
		opword 0x7C1D0000
		opword 0x4180FF38
		opword 0x2C1C0000
		opword 0x4080000C
		opword 0x38600000
		opword 0x480003C4
		lfs f0, float_0p5_8041976c(r2)
		opword 0xEC0007F2
		opword 0xFC1C0040
		opword 0x4080001C
		opword 0x1C1B0178
		opword 0x7C7E0214
		opword 0x1C1C00E4
		opword 0x8063015C
		opword 0x7C630214
		opword 0x4800039C
		opword 0x1C1B0178
		opword 0x38810068
		opword 0x38BA0018
		opword 0x7FDE0214
		opword 0x1FFC00E4
		opword 0x801E015C
		opword 0x7F60FA14
		opword 0x387B00C0
		bl PSVECSubtract
		opword 0x387A0018
		opword 0x7C641B78
		bl PSVECNormalize
		opword 0x80810068
		opword 0x3B80FFFF
		opword 0x8061006C
		opword 0x80010070
		opword 0x90810080
		lfs f30, float_neg1_80419768(r2)
		opword 0x90610084
		opword 0x90010088
		opword 0xD3A100B0
		opword 0x807B0008
		opword 0x80630058
		opword 0x88030001
		opword 0x28000001
		opword 0x40820010
		opword 0x38000001
		opword 0x90010074
		opword 0x4800000C
		opword 0x38000000
		opword 0x90010074
		opword 0x82FB00AC
		opword 0x3B200000
		opword 0x480002E0
		opword 0x80010074
		opword 0x2C000000
		opword 0x41820020
		opword 0x38770048
		opword 0x389A0018
		bl PSVECDotProduct
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x418202B0
		opword 0x7EE4BB78
		opword 0x387A000C
		opword 0x38A10008
		bl PSVECSubtract
		opword 0x38770048
		opword 0x38810008
		bl PSVECDotProduct
		opword 0x80010074
		opword 0xFFE00890
		opword 0x2C000000
		opword 0x418200DC
		lfs f0, float_0_80419758(r2)
		opword 0xFC1F0040
		opword 0x4080000C
		opword 0x38000000
		opword 0x48000248
		opword 0x387A0018
		opword 0x38970024
		opword 0x38A1002C
		bl PSVECCrossProduct
		opword 0x38610008
		opword 0x3881002C
		bl PSVECDotProduct
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x48000218
		opword 0x387A000C
		opword 0x3897000C
		opword 0x38A10014
		bl PSVECSubtract
		opword 0x387A0018
		opword 0x38970030
		opword 0x38A10038
		bl PSVECCrossProduct
		opword 0x38610014
		opword 0x38810038
		bl PSVECDotProduct
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x480001D8
		opword 0x387A000C
		opword 0x38970018
		opword 0x38A10020
		bl PSVECSubtract
		opword 0x387A0018
		opword 0x3897003C
		opword 0x38A10044
		bl PSVECCrossProduct
		opword 0x38610020
		opword 0x38810044
		bl PSVECDotProduct
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x48000198
		opword 0x38770048
		opword 0x389A0018
		bl PSVECDotProduct
		opword 0xFF800890
		opword 0x480000EC
		opword 0x38770048
		opword 0x389A0018
		bl PSVECDotProduct
		opword 0xFF800890
		lfs f0, float_0_80419758(r2)
		opword 0xEC3C07F2
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000158
		opword 0x387A0018
		opword 0x38970024
		opword 0x38A1002C
		bl PSVECCrossProduct
		opword 0x38610008
		opword 0x3881002C
		bl PSVECDotProduct
		opword 0xEC3F0072
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x48000124
		opword 0x387A000C
		opword 0x3897000C
		opword 0x38A10014
		bl PSVECSubtract
		opword 0x387A0018
		opword 0x38970030
		opword 0x38A10038
		bl PSVECCrossProduct
		opword 0x38610014
		opword 0x38810038
		bl PSVECDotProduct
		opword 0xEC3F0072
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x480000E0
		opword 0x387A000C
		opword 0x38970018
		opword 0x38A10020
		bl PSVECSubtract
		opword 0x387A0018
		opword 0x3897003C
		opword 0x38A10044
		bl PSVECCrossProduct
		opword 0x38610020
		opword 0x38810044
		bl PSVECDotProduct
		opword 0xEC3F0072
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4080000C
		opword 0x38000000
		opword 0x4800009C
		opword 0xC02100B0
		lfs f0, float_0_80419758(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820020
		opword 0xFC00F850
		opword 0xEC00E024
		opword 0xFC000840
		opword 0x4C411382
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800006C
		opword 0xFC00F850
		opword 0x387A0018
		opword 0x38810050
		opword 0xEC20E024
		opword 0xD02100B0
		bl PSVECScale
		opword 0x387A000C
		opword 0x38810050
		opword 0x38BA0024
		bl PSVECAdd
		lfs f0, float_0_80419758(r2)
		opword 0xFC1F0040
		opword 0x4C411382
		opword 0x40820020
		opword 0x80770048
		opword 0x8017004C
		opword 0x906100A4
		opword 0x900100A8
		opword 0x80170050
		opword 0x900100AC
		opword 0x48000014
		lfs f1, float_neg1_80419768(r2)
		opword 0x38770048
		opword 0x389A0030
		bl PSVECScale
		opword 0x38000001
		opword 0x2C000000
		opword 0x41820024
		lfs f0, float_0_80419758(r2)
		opword 0xFC1E0040
		opword 0x41800010
		opword 0xC00100B0
		opword 0xFC1E0040
		opword 0x4081000C
		opword 0xC3C100B0
		opword 0x3B800001
		opword 0x3B390001
		opword 0x3AF70054
		opword 0xA81B00A8
		opword 0x7C190000
		opword 0x4180FD1C
		opword 0xFC1EE840
		opword 0x4081000C
		opword 0x38600000
		opword 0x4800001C
		opword 0x2C1C0000
		opword 0x4080000C
		opword 0x38600000
		opword 0x4800000C
		opword 0x801E015C
		opword 0x7C60FA14
	}
}
#pragma pop
#endif

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

#ifdef NONMATCHING
void hitObjGetPos(const char* name, Vec* position) { // 1:1
    Vec spC;
    s32 counter;
    HitEntry* hit;

    counter = 0;
    spC = (Vec){ EXT_LIT(float_0_80419758, 0.0f), EXT_LIT(float_0_80419758, 0.0f), EXT_LIT(float_0_80419758, 0.0f) };
    hit = hitNameToPtr(name);
    if (hit == NULL) {
        *position = (Vec){ EXT_LIT(float_0_80419758, 0.0f), EXT_LIT(float_0_80419758, 0.0f), EXT_LIT(float_0_80419758, 0.0f) };
        return;
    }
    hitObjGetPosSub(hit, &spC, &counter, 0);
    PSVECScale(&spC, position, EXT_LIT(float_1_80419764, 1.0f) / (f32)counter);
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void hitObjGetPos(const char* name, Vec* position) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		lis r5, vec3_802c156c+0x8@ha
		opword 0x90010044
		opword 0x38000000
		addi r6, r5, vec3_802c156c+0x8@l
		opword 0xBF210024
		opword 0x7C791B78
		opword 0x7C9F2378
		opword 0x90010008
		opword 0x80A60000
		opword 0x80660004
		opword 0x80060008
		opword 0x90A1000C
		opword 0x90610010
		opword 0x90010014
		bl mapGetWork
		opword 0x28190000
		opword 0x7C7B1B78
		opword 0x4082000C
		opword 0x3BC00000
		opword 0x48000070
		opword 0x7F7ADB78
		opword 0x3BA00000
		opword 0x48000054
		opword 0x83DA015C
		opword 0x3B800000
		opword 0x48000034
		opword 0xA01E0000
		opword 0x54000631
		opword 0x40820020
		opword 0x807E0008
		opword 0x7F24CB78
		opword 0x80630000
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x48000030
		opword 0x3B9C0001
		opword 0x3BDE00E4
		opword 0x801A0158
		opword 0x7C1C0000
		opword 0x4180FFC8
		opword 0x3B5A0178
		opword 0x3BBD0001
		opword 0x801B0000
		opword 0x7C1D0000
		opword 0x4180FFA8
		opword 0x3BC00000
		opword 0x281E0000
		opword 0x40820028
		lis r3, vec3_802c1578+0x8@ha
		addi r4, r3, vec3_802c1578+0x8@l
		opword 0x80640000
		opword 0x80040004
		opword 0x907F0000
		opword 0x901F0004
		opword 0x80040008
		opword 0x901F0008
		opword 0x48000050
		opword 0x7FC3F378
		opword 0x3881000C
		opword 0x38A10008
		opword 0x38C00000
		bl hitObjGetPosSub
		opword 0x80810008
		opword 0x3C004330
		opword 0x90010018
		lis r3, double_to_int_802c1590@ha
		opword 0x6C808000
		lfd f1, double_to_int_802c1590@l(r3)
		opword 0x9001001C
		opword 0x7FE4FB78
		lfs f2, float_1_80419764(r2)
		opword 0x3861000C
		opword 0xC8010018
		opword 0xEC000828
		opword 0xEC220024
		bl PSVECScale
		opword 0xBB210024
		opword 0x80010044
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop
#endif

void hitObjGetNormal(const char* name, Vec* normal) { // 1:1
    HitEntry* hit;

    hit = hitNameToPtr(name);
    if (hit != NULL && hit->joint->partCount > 0) {
        PSVECNormalize(&hit->vectors->normal, normal);
    }
}

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

s32 hitGetAttr(HitEntry* hit) { // 1:1
    return hit != NULL ? hit->attributes : 0;
}

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

void hitGrpDamageReturnSet(const char* name, HitDamageReturn* damage) { // 1:1
    HitEntry* hit;

    hit = hitNameToPtr(name);
    if (hit != NULL) {
        hitDamageReturnSet(hit, damage, FALSE);
    }
}

Vec* hitGetDamageReturnPos(HitEntry* hit) {
    return &hit->damage->position;
}

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
        PSMTXScale(mtx, EXT_LIT(float_10_80419760, 10.0f), EXT_LIT(float_10_80419760, 10.0f), EXT_LIT(float_10_80419760, 10.0f));
        hitReCalcMatrix(hit, mtx);
    }
}
/*
#ifdef NONMATCHING
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
    f[0] = EXT_LIT(float_0_80419758, 0.0f);
    f[1] = EXT_LIT(float_0p1
#endif_8041975c, 0.1f);
}
#endif

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const u32 lbl_802C1538 = 0x00000000;
__declspec(section ".rodata") const f32 vec3_802c153c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1548[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1554[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1560[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c156c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1578[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c1584[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_802c1590 = 4503601774854144.0;
__declspec(section ".sdata2") const f32 float_0_80419758 = 0.0f;
__declspec(section ".sdata2") const f32 float_0p1_8041975c = 0.1f;
__declspec(section ".sdata2") const f32 float_10_80419760 = 10.0f;
__declspec(section ".sdata2") const f32 float_1_80419764 = 1.0f;
__declspec(section ".sdata2") const f32 float_neg1_80419768 = -1.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041976c = 0.5f;
__declspec(section ".sdata2") const f32 float_deg2rad_80419770 = 0.017453292f;
__declspec(section ".sdata2") const u32 gap_09_80419774_sdata2 = 0x00000000;
#endif
