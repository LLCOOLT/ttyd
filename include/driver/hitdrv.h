// hitdrv.c: the hit driver (HitEntry, HitCheckQuery): map collision objects and the ray and sphere checks.
#pragma once

#include <dolphin/mtx.h>
#include "driver/mapdrv.h"
#include "version.h"

// Collision object attribute bits (HitEntry.attributes, hitGetAttr, hitObjAttrOn/Off, hitGrpAttrOn/Off). The map
// file gives each object its bits (MapFileDrawMode.hitAttributes); the names come from the checks that read them.
// The plane panel bits 0x8/0x10/0x20 (only read together, mario_sbr.c marioChkPlanePlace) and the footstep
// surface bits 0x100000/0x200000/0x400000 (mot_walk.c marioWalkDashSe, mario_kemuri.c) have no names yet.
#pragma enumsalwaysint off
typedef enum HitAttr {
    HIT_ATTR_HAMMER_PASS = 0x1,          // Guess: the hammer and Koops's shell miss it (mot_hammer, chkfilterNokotaro)
    HIT_ATTR_PASS_THROUGH = 0x4,         // Mario's and partners' rays skip it (Mario's not with HIT_ATTR_PARTY_PASS)
    HIT_ATTR_ALWAYS_SOLID = 0x80,        // rays test it despite pass bits; Mario pushes on it only in Boat Mode
    HIT_ATTR_SHALLOW_WATER = 0x100,      // *_FLAG_IN_SHALLOW_WATER: slower walk, splash steps and dust
    HIT_ATTR_DEEP_WATER = 0x200,         // sinks Mario (MARIO_MOTION_DAMAGE); items float (ITEM_STATUS_IN_WATER)
    HIT_ATTR_DAMAGE_LIQUID = 0x400,      // Guess: items float in it, but Mario gets MARIO_MOTION_DAMAGE_TOGE
    HIT_ATTR_SPIKES = 0x800,             // hurts Mario (MARIO_MOTION_DAMAGE_TOGE); partners do not stand on it
    HIT_ATTR_GRASS = 0x1000,             // kemuri_mugi dust and grass footsteps (plain steps on the mri maps)
    HIT_ATTR_PAPER_SLIT = 0x2000,        // a gap Mario or a partner slips through in Paper Mode (mot_slit.c)
    HIT_ATTR_DOCK_NEG_Z = 0x4000,        // boat panel (marioChkShipPlace); mot_ship.c harborKind 1
    HIT_ATTR_DOCK_POS_Z = 0x8000,        // boat panel; harborKind 2
    HIT_ATTR_DOCK_NEG_X = 0x10000,       // boat panel; harborKind 3
    HIT_ATTR_DOCK_POS_X = 0x20000,       // boat panel; harborKind 4
    HIT_ATTR_SPRING_GRAB = 0x40000,      // a ceiling Mario's Spring Jump grabs and swings from (mot_jabara.c)
    HIT_ATTR_TUBE_PASS = 0x80000,        // Tube Mode and Vivian's shadow pass through; other rays always test it
    HIT_ATTR_PARTY_PASS = 0x800000,      // partner rays skip it; Mario's rays test it even with HIT_ATTR_PASS_THROUGH
    HIT_ATTR_DAMAGE_RETURN = 0x40000000, // hitDamageReturnSet: hazard floor with a return point (damageHit)
    HIT_ATTR_MOBJ = 0x80000000,          // the collision object of a map object (mobjHitObjPtrToPtr)
} HitAttr;
#pragma enumsalwaysint on

typedef struct HitCheckQuery HitCheckQuery;
typedef struct HitEntry HitEntry;
typedef BOOL (*HitFilterCallback)(HitCheckQuery* query, struct HitEntry* entry);

typedef struct HitVector {
    Vec v0;     // 0x0
    Vec v1;     // 0xC
    Vec v2;     // 0x18
    Vec edge0;  // 0x24, v2 - v0
    Vec edge1;  // 0x30, v0 - v1
    Vec edge2;  // 0x3C, v1 - v2
    Vec normal; // 0x48
} HitVector;

struct HitCheckQuery {
    BOOL singleSided;   // 0x0
    s32 user0;          // 0x4
    s32 user1;          // 0x8
    Vec targetPos;      // 0xC
    Vec targetDir;      // 0x18
    Vec hitPos;         // 0x24
    Vec hitNormal;      // 0x30
    f32 targetDistance; // 0x3C
};

typedef struct HitDamageReturn {
    const char* mapobjName; // 0x0
    Vec position;           // 0x4
} HitDamageReturn;

// HitEntry.flags (hitObjFlagOn/Off, hitGrpFlagOn/Off and evt_hitobj_onoff)
#define HIT_FLAG_OFF 0x1            // collision off (evt_hitobj_onoff): every check skips it
#define HIT_FLAG_ANIM_MTX 0x10      // moved by a map animation: the world matrix uses animMtx, not localMtx
#define HIT_FLAG_BOUND 0x20         // bound to a map object (hitBindMapObj): its transformMtx applies
#define HIT_FLAG_MTX_DIRTY 0x40     // world matrix and triangles are recomputed by the next hitReCalcMatrix2
#define HIT_FLAG_DELETED 0x80       // removed by hitDelete: every check and name lookup skips it
#define HIT_FLAG_NO_GEOMETRY 0x8000 // demo: an object without triangles (partCount 0); the checks skip it
struct HitEntry {
    u16 flags;               // 0x0
    u8 pad_02[0x4 - 0x2];    // 0x2, never accessed
    s32 attributes;          // 0x4
    MapFileJoint* joint;     // 0x8
    Mtx worldMtx;            // 0xC
    Mtx localMtx;            // 0x3C
    Mtx animMtx;             // 0x6C, joint animation matrix (output of mapCalcAnimMatrix, concatenated into worldMtx)
    Vec centerLocal;         // 0x9C
    s16 vectorCount;         // 0xA8, number of HitVector triangles (set from hitCalcVtxPosition)
    s16 mapIndex;            // 0xAA
    HitVector* vectors;      // 0xAC
    HitDamageReturn* damage; // 0xB0
    u8 pad_B4[0xC0 - 0xB4];  // 0xB4, never accessed
    Vec centerWorld;         // 0xC0
    f32 radius;              // 0xCC
    union {                  // 0xD0, owner: map object, or the mobj for mobj hit objects
        MapObject* mapObj;
        struct MapObjectEntry* mobj;
    };
    struct HitEntry* parent;  // 0xD4
    struct HitEntry* child;   // 0xD8
    struct HitEntry* sibling; // 0xDC
#if VERSION >= VERSION_JP
    struct HitEntry* nextActive; // 0xE0, next entry in the hitActiveListTop list (not in the demo)
#endif
};

void hitInit(void);
void hitMain(void);

void hitReCalcMatrix(HitEntry* hit, Mtx mtx);
HitEntry* hitCheckVecFilter(HitCheckQuery* query, HitFilterCallback callback);
HitEntry* hitCheckFilter(HitFilterCallback callback, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX,
                         f32* hitNY, f32* hitNZ, f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz);
BOOL hitCheckVecHitObjXZ(HitCheckQuery* query, HitEntry* entry);
HitEntry* hitCheckAttr(s32 user0, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX, f32* hitNY, f32* hitNZ,
                       f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz);
HitEntry* hitCheckSphereFilter(HitFilterCallback callback, f32 x, f32 y, f32 z, f32 distance);
HitEntry* hitNameToPtr(const char* name);
void hitObjGetPos(const char* name, Vec* position);
void hitObjGetNormal(const char* name, Vec* normal);
const char* hitGetName(HitEntry* hit);
s32 hitGetAttr(HitEntry* hit);
void hitGrpDamageReturnSet(const char* name, HitDamageReturn* damage);
Vec* hitGetDamageReturnPos(HitEntry* hit);
void hitBindMapObj(const char* hitName, const char* mapobjName);

void hitDelete(const char* name);

void hitBindUpdate(const char* name);
void hitObjFlagOff(const char* name, u16 mask);
HitEntry* hitEntryMOBJ(MapFileJoint* joint, Mtx mtx);
HitEntry* hitEntry(MapFileJoint* root, Mtx rootMtx, s32 mapIndex);
void hitReInit(void);
void hitGrpAttrOff(const char* name, u32 mask);
void hitGrpAttrOn(const char* name, u32 mask);
void hitGrpFlagOff(const char* name, u16 mask);
void hitGrpFlagOn(const char* name, u16 mask);
void hitObjAttrOff(const char* name, u32 mask);
void hitObjAttrOn(const char* name, u32 mask);
void hitObjFlagOn(const char* name, u16 mask);
