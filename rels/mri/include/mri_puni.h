#pragma once

#include <dolphin/types.h>
#include "evt/evt_cmd.h"
#include "driver/npcdrv.h"
#include "driver/effdrv.h"
#include <dolphin/mtx.h>
#include "driver/hitdrv.h"

typedef struct PuniTarget {
    s32 flags;           // 0x0
    Vec pos;             // 0x4
    HitEntry* hit;       // 0x10
} PuniTarget;

#define PUNI_DATA_MAX 211
#define PUNI_TEX_INFO_MAX 200

typedef struct PuniAnimSet {
    s16* table[10]; // 0x0
    s16 count[10];  // 0x28
    s16 end[10];    // 0x3C
} PuniAnimSet;

typedef struct PuniWork {
    s32 systemMode;           // 0x0
    PuniAnimSet anim[2];      // 0x4
    u8 unkA4[0x324 - 0xA4];   // 0xA4
    u32 unk324;               // 0x324
    s32 unk328;               // 0x328
    f32 posY[4];              // 0x32C
    s32 ymode;                // 0x33C
    s32 mapKind;              // 0x340
    Vec unk344;               // 0x344
    u8 unk350[0x360 - 0x350]; // 0x350
    s32 unk360;               // 0x360
    u8 unk364[0x374 - 0x364]; // 0x364
    PuniTarget targets[10];   // 0x374
    s32 unk43C;               // 0x43C
    s32 unk440;               // 0x440
    BOOL showPuniCounter; //0x444
    BOOL unk448; //0x448
    s32 puniCounterAlpha; //0x44C
    s32 seed0;                // 0x450
    s32 seed1;                // 0x454
    u32 sfx458;               // 0x458
    u8 unk45C[0x468 - 0x45C]; // 0x45C
    u32 sfx468;               // 0x468
    u8 unk46C[0x4CC - 0x46C]; // 0x46C
    s32 unk4CC;               // 0x4CC
} PuniWork;

typedef struct PuniData {
    NpcEntry* npc;        // 0x0
    s32 unk4;             // 0x4
    s32 unk8;             // 0x8
    u16 unkC;             // 0xC
    u16 unkE;             // 0xE
    u8 unk10[0x114 - 0x10]; // 0x10
    u16 unk114;           // 0x114
    u8 unk116[0x118 - 0x116]; // 0x116
    s16 unk118;           // 0x118
    s16 unk11A;           // 0x11A
    u16 anim;             // 0x11C
    s16 unk11E;           // 0x11E
    u8 unk120;            // 0x120
    u8 unk121;            // 0x121
    u8 unk122[0x124 - 0x122]; // 0x122
    s32 unk124;           // 0x124
    s32 unk128;           // 0x128
    Vec pos;              // 0x12C
    Vec unk138;           // 0x138
    u8 unk144[0x148 - 0x144]; // 0x144
    f32 unk148;           // 0x148
    u8 unk14C[0x15C - 0x14C]; // 0x14C
    Vec vel;              // 0x15C
    u8 unk168[0x174 - 0x168]; // 0x168
    f32 unk174;           // 0x174
    u8 unk178[0x180 - 0x178]; // 0x178
    f32 dir;              // 0x180
    f32 spin;             // 0x184
    f32 unk188;           // 0x188
    f32 alpha;            // 0x18C
    Vec unk190;           // 0x190
    u8 unk19C[0x1A0 - 0x19C]; // 0x19C
    f32 unk1A0;           // 0x1A0
    f32 unk1A4;           // 0x1A4
    f32 unk1A8;           // 0x1A8
    f32 unk1AC;           // 0x1AC
    f32 unk1B0;           // 0x1B0
    s32 unk1B4;           // 0x1B4
    f32 unk1B8;           // 0x1B8
    s32 unk1BC;           // 0x1BC
    f32 unk1C0;           // 0x1C0
    u8 unk1C4[0x1D0 - 0x1C4]; // 0x1C4
    struct PuniData* parent; // 0x1D0
    struct PuniData* child1; // 0x1D4
    struct PuniData* child2; // 0x1D8
    s32 unk1DC;           // 0x1DC
    s32 unk1E0;           // 0x1E0
    u8 unk1E4[0x1F8 - 0x1E4]; // 0x1E4
    Vec unk1F8;           // 0x1F8
    u8 unk204[0x218 - 0x204]; // 0x204
    EffectEntry* effect;  // 0x218
    u8 unk21C[0x56C - 0x21C]; // 0x21C
    void (*modeFunc)(struct PuniData*); // 0x56C
    void (*moveFunc)(struct PuniData*); // 0x570
    s16 hp;               // 0x574
    s16 maxHp;            // 0x576
    s16 regen;            // 0x578
    s16 regenTimer;       // 0x57A
    s16 regenInterval;    // 0x57C
    s16 unk57E;           // 0x57E
    s16 unk580;           // 0x580
    s16 unk582;           // 0x582
    s16 damage;           // 0x584
    s16 unk586;           // 0x586
    s16 unk588;           // 0x588
    s16 unk58A;           // 0x58A
    u8 unk58C[0x5A8 - 0x58C]; // 0x58C
} PuniData;

typedef struct PuniMap {
    f32 x;                // 0x0
    f32 z;                // 0x4
    s32 width;            // 0x8
    s32 height;           // 0xC
    s32 size;             // 0x10
    s32 enabled;          // 0x14
    void* src;            // 0x18
    s32 unk1C;            // 0x1C
    u16* data;            // 0x20
} PuniMap;

typedef struct PuniTexInfo {
    char* unk0; // 0x0
    char* unk4; // 0x4
    f32 unk8;   // 0x8
} PuniTexInfo;

USER_FUNC(evt_puni_mem_init);
