#pragma once

// Moamoa (Smorg) swarm on the field: the ext-pose swarm code that eki_00 (Riverside Station), rsh_05
// and rsh_06 (Excess Express) each carry. rsh_00 uses only the pose tables.

#include "driver/mapdrv.h"
#include "manager/evtmgr.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <dolphin/types.h>

// One animation pose of the swarm: frames [start, start + count) of model/anim.
typedef struct MoamoaPoseDef {
    char model[16]; // 0x00
    char anim[8];   // 0x10
    s16 loop;       // 0x18
    f32 speed;      // 0x1C
    s32 start;      // 0x20
    s32 count;      // 0x24
} MoamoaPoseDef;

// ext_moamoa_data entry: an animation to split into MoamoaPoseDefs.
typedef struct MoamoaData {
    const char* model; // 0x0
    const char* anim;  // 0x4
    f32 speed;         // 0x8
} MoamoaData;

// Moamoa.flags bits (from their set/test sites in eki_00, rsh_05 and rsh_06).
#define MOAMOA_FLAG_TO_TARGET 0x1    // its last idle hop went toward its swarm target, not toward Mario
#define MOAMOA_FLAG_JUMPING 0x2      // in a moamoa_jump arc (cleared on landing)
#define MOAMOA_FLAG_DAMAGED 0x4      // hit (stomped, hammered or blown): plays only the D_ (damage) poses
#define MOAMOA_FLAG_KNOCKED 0x8      // hit hard enough to fly off (hammer, spin, shell): also DAMAGED
#define MOAMOA_FLAG_ESCAPING 0x10    // running away after the swarm took too many hits: plays only the R_ poses
#define MOAMOA_FLAG_GONE 0x20        // finished leaving (evt_moamoa_end_wait waits for every one)
#define MOAMOA_FLAG_OFF_FLOOR 0x40   // rsh_06: placed in the background with no floor under it
#define MOAMOA_FLAG_BLOWN 0x80       // blown away by Flurrie's breath: also DAMAGED
#define MOAMOA_FLAG_FUSING 0x100     // gathering to merge into Smorg (evt_moamoa_fusion)
#define MOAMOA_FLAG_GATHERED 0x200   // reached the merge point (evt_moamoa_fusion waits for every one)
#define MOAMOA_FLAG_MERGED 0x400     // part of the merged Smorg body (cleared by evt_moamoa_blow)
#define MOAMOA_FLAG_KIND_MODEL 0x800 // drawn with its kind's model and pose (group_tbl) instead of c_n_moa_a

// One Moamoa of the swarm.
typedef struct Moamoa {
    u16 flags;        // 0x00, MOAMOA_FLAG_*
    s16 state;        // 0x02
    s16 timer;        // 0x04
    u8 pad_6[2];      // 0x06
    Vec target;       // 0x08
    f32 vy;           // 0x14
    s16 jumpTimer;    // 0x18
    u8 pad_1a[2];     // 0x1A
    f32 speed;        // 0x1C
    f32 gravity;      // 0x20
    s16 next;         // 0x24, state to go to
    u8 pad_26[2];     // 0x26
    f32 lastX;        // 0x28
    f32 lastZ;        // 0x2C
    Vec jitter;       // 0x30
    s16 pose;         // 0x3C, index into MoamoaWork.defs
    u8 pad_3e[2];     // 0x3E
    OSTime startTime; // 0x40
    s16 group;        // 0x48, chain group
    s16 order;        // 0x4A, position in the chain
    u8 kind;          // 0x4C, row of group_tbl
    u8 pad_4d[3];     // 0x4D
} Moamoa;

// MoamoaWork.flags bits (scripts set them with evt_moamoa_flag_onoff).
#define MOAMOA_WORK_ACTIVE 0x1          // swarm drawn in the 3D camera and reacting to Mario
#define MOAMOA_WORK_DRAW_OFFSCREEN 0x2  // swarm drawn into CAMERA_OFFSCREEN2
#define MOAMOA_WORK_NO_HIT 0x4          // hit checks against Mario and the partners are off
#define MOAMOA_WORK_PARTNER_IN_USE 0x10 // a partner's field ability is in use (PARTY_FLAG_IS_BEING_USED): no floor push on Mario
#define MOAMOA_WORK_TARGET0_OFF 0x1000  // evt_moamoa_target_off(0): target 0 replaced by target 1
#define MOAMOA_WORK_TARGET1_OFF 0x2000  // evt_moamoa_target_off(1): target 1 replaced by target 0

typedef struct MoamoaWork {
    u16 flags;              // 0x000, MOAMOA_WORK_*
    u8 pad_2[2];            // 0x002
    s32 count;              // 0x004
    Moamoa* moa;            // 0x008
    MapObject* mobj;        // 0x00C
    f32 mobjY;              // 0x010
    Vec target[3];          // 0x014
    s16 hitCount;           // 0x038
    s16 targetHits[3];      // 0x03A
    s16 hammerFrames;       // 0x040
    s16 idleFrames;         // 0x042
    EventEntry* escapeEvt;  // 0x044
    s32 animPoseId;         // 0x048
    s32 numDefs;            // 0x04C
    MoamoaPoseDef defs[32]; // 0x050
    f32 angle;              // 0x550
    f32 dist;               // 0x554
    s32 bounceCount;        // 0x558
    f32 breathDir;          // 0x55C
    f32 breathDist;         // 0x560
    Vec breathPos;          // 0x564
    s16 chainNum[128];      // 0x570
    s16 chainIdx[128][2];   // 0x670
} MoamoaWork;
