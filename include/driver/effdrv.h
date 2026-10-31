// effdrv.c: the effect driver (EffectEntry, EffectSet, EFFECT_FLAG_*, effEntry): the effect pool and effect textures.
#pragma once

#include <dolphin/dvd.h>
#include "manager/filemgr.h"
#include "eff/eff_maya_data.h"
#include "sdk/texPalette.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include "version.h"

typedef struct EffectEntry EffectEntry;

typedef void (*EffectCallback)(EffectEntry* effect);

struct EffectEntry {
    u32 flags;               // 0x0, EFFECT_FLAG_*
    u32 inBattle;            // 0x4
    s32 count;               // 0x8
    void* userdata;          // 0xC, for effects to store their own data
    EffectCallback callback; // 0x10
    const char* type;        // 0x14
    char name[16];           // 0x18
};

// EffectEntry.flags
#define EFFECT_FLAG_IN_USE 0x1           // set by effEntry; auto-release and the name lookups test it
#define EFFECT_FLAG_SOFT_DELETE 0x2      // the effect's Main handles effSoftDelete itself
#define EFFECT_FLAG_DELETE_REQUESTED 0x4 // set by effSoftDelete, acted on (and cleared) by the effect's Main

typedef struct EffectSet {
    s16 id;           // 0x0
    const char* name; // 0x4
#if VERSION == VERSION_DEMO
    const char* jpName;     // 0x8, debug name (Japanese)
    const char** typeNames; // 0xC, NULL-terminated debug names of the effect's types, or NULL
#endif
} EffectSet; // size 0x8, 0x10 demo

typedef struct EffectWork {
    s32 count;            // 0x0
    EffectEntry* entries; // 0x4
    TEXPalette* texture;  // 0x8
    BOOL texLoaded;       // 0xC
    FileEntry* handle;    // 0x10
    s32 language;         // 0x14
} EffectWork;

// Maya-exported effect animation (eff_damage_star, eff_ice, eff_recovery): a list of polygon pieces,
// each with its own key track (MayaHermitKey) and its triangle fans.
typedef struct MayaPoly {
    s32 keyCount;        // 0x0
    MayaHermitKey* keys; // 0x4
    s32 stripCount;      // 0x8
    s16** strips;        // 0xC, each: vertex count, then x, y, z, s, t per vertex
} MayaPoly;

typedef struct MayaPolyList {
    s32 count;       // 0x0
    MayaPoly* polys; // 0x4
} MayaPolyList;

typedef struct MayaAnimData {
    u8 pad_0[4];            // 0x0, zero in every table, never read
    f32 endTime;            // 0x4, frames
    MayaPolyList* polyList; // 0x8
} MayaAnimData;

// Result of effCalcMayaAnim for one MayaPoly.
typedef struct MayaJoint {
    Mtx mtx;   // 0x00
    f32 alpha; // 0x30, 0..1
} MayaJoint;

// MayaAnim.flags
#define MAYA_ANIM_FLAG_PLAYING 0x1
#define MAYA_ANIM_FLAG_ENDED 0x2

typedef struct MayaAnim {
    u16 flags;           // 0x00, MAYA_ANIM_FLAG_*
    f32 time;            // 0x04, frames since effPlayMayaAnim
    OSTime startTime;    // 0x08, milliseconds
    MayaAnimData* data;  // 0x10
    MayaJoint joints[1]; // 0x14, one per MayaPoly (allocated to data->polyList->count)
} MayaAnim;

void effInit(void);
void effTexSetup(void);
void effGetTexObj(u32 id, GXTexObj* obj);
void effAutoRelease(BOOL inBattle);
EffectEntry* effEntry(void);
void effSetName(EffectEntry* effect, const char* name);
void effMain(void);
void effDelete(EffectEntry* effect);
void effSoftDelete(EffectEntry* effect);
EffectEntry* effNameToPtr(const char* name);
EffectSet* effGetSet(const char* name);
void effCalcMayaAnimMatrix(MayaAnim* anim, MayaPoly* poly, f32* mtx, f32* alpha);
MayaAnim* effMayaAnimAlloc(MayaAnimData* data);
void effDeleteMayaAnim(MayaAnim* anim);
void effPlayMayaAnim(MayaAnim* anim);
void effCalcMayaAnim(MayaAnim* anim);
void effDrawMayaPoly(MayaPoly* poly);
