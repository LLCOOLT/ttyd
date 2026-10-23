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
    f32 unk350;               // 0x350
    f32 unk354;               // 0x354
    f32 unk358;               // 0x358
    f32 unk35C;               // 0x35C
    s32 unk360;               // 0x360
    struct PuniData* unk364;  // 0x364
    struct PuniData* unk368;  // 0x368
    struct PuniData* unk36C;  // 0x36C
    struct PuniData* unk370;  // 0x370
    PuniTarget targets[10];   // 0x374
    s32 unk43C;               // 0x43C
    s32 unk440;               // 0x440
    BOOL showPuniCounter; //0x444
    BOOL unk448; //0x448
    s32 puniCounterAlpha; //0x44C
    s32 seed0;                // 0x450
    s32 seed1;                // 0x454
    u32 sfx458;               // 0x458
    s32 puniMoveCount;        // 0x45C
    s32 puniMoveLevel;        // 0x460
    u8 unk464[0x468 - 0x464]; // 0x464
    u32 sfx468;               // 0x468
    s32 togeMoveCount;        // 0x46C
    s32 togeMoveLevel;        // 0x470
    s32 togeMoveLevelPrev;    // 0x474
    u32 sfxTogetti;           // 0x478
    s32 beroMode;             // 0x47C
    Vec beroStart;            // 0x480
    Vec beroEnd;              // 0x48C
    u8 unk498[0x4B0 - 0x498]; // 0x498
    f32 beroStartRange;       // 0x4B0
    f32 beroEndRange;         // 0x4B4
    u8 unk4B8[0x4C0 - 0x4B8]; // 0x4B8
    s32 unk4C0;               // 0x4C0
    s32 unk4C4;               // 0x4C4
    u8 unk4C8[0x4CC - 0x4C8]; // 0x4C8
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
    s16 unk116;               // 0x116
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
    u8 unk14C[0x154 - 0x14C]; // 0x14C
    f32 unk154;               // 0x154
    f32 unk158;               // 0x158
    Vec vel;              // 0x15C
    Vec pushDir;          // 0x168
    f32 unk174;           // 0x174
    f32 accelStep;        // 0x178
    u8 unk17C[0x180 - 0x17C]; // 0x17C
    f32 dir;              // 0x180
    f32 spin;             // 0x184
    f32 unk188;           // 0x188
    f32 alpha;            // 0x18C
    Vec unk190;           // 0x190
    f32 unk19C;               // 0x19C
    f32 unk1A0;           // 0x1A0
    f32 unk1A4;           // 0x1A4
    f32 unk1A8;           // 0x1A8
    f32 unk1AC;           // 0x1AC
    f32 unk1B0;           // 0x1B0
    s32 unk1B4;           // 0x1B4
    f32 unk1B8;           // 0x1B8
    s32 unk1BC;           // 0x1BC
    f32 unk1C0;           // 0x1C0
    u8 unk1C4[0x1CC - 0x1C4]; // 0x1C4
    s32 unk1CC;               // 0x1CC
    struct PuniData* parent; // 0x1D0
    struct PuniData* child1; // 0x1D4
    struct PuniData* child2; // 0x1D8
    s32 unk1DC;           // 0x1DC
    s32 unk1E0;           // 0x1E0
    s32 unk1E4;               // 0x1E4
    s32 unk1E8;               // 0x1E8
    f32 upSpeed;          // 0x1EC
    f32 upAccel;          // 0x1F0
    f32 upMax;            // 0x1F4
    Vec unk1F8;           // 0x1F8
    u8 unk204[0x208 - 0x204]; // 0x204
    f32 unk208;               // 0x208
    f32 unk20C;               // 0x20C
    HitEntry* hitMove;    // 0x210
    HitEntry* hitCheck;   // 0x214
    EffectEntry* effect;  // 0x218
    u8 unk21C[0x2AC - 0x21C]; // 0x21C
    f32 unk2AC;               // 0x2AC
    f32 unk2B0;               // 0x2B0
    f32 unk2B4;               // 0x2B4
    u8 unk2B8[0x564 - 0x2B8]; // 0x2B8
    f32 unk564;               // 0x564
    f32 unk568;               // 0x568
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
    s32 unk58C;           // 0x58C
    Vec unk590;           // 0x590
    Vec unk59C;           // 0x59C
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
