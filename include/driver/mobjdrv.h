// mobjdrv.c: the map object (mobj) driver (MapObjectEntry, MOBJ_FLAG_*): blocks, item boxes, switches.
#pragma once

#include "dolphin/gx/GXStruct.h"
#include "driver/camdrv.h"
#include "driver/hitdrv.h"
#include <dolphin/types.h>
#include "evt/evt_word.h"
#include <dolphin/mtx.h>
#include "version.h"

typedef struct MapObjectHitEntry {
    HitEntry* hitObject;       // 0x0
    char name[16];             // 0x4
    u8 jointData[0x88 - 0x14]; // 0x14, 0x1C: MapFileJoint copied from the cube/head/front joint templates (jointData + 8)
} MapObjectHitEntry;

// MapObjectEntry.flags, low half. Meanings from the readers in mobjdrv.c and the setters in evt_mobj.c.
enum MapObjectFlags {
    MOBJ_FLAG_USED = 0x1,
    MOBJ_FLAG_NO_SHADOW = 0x2,      // mobjMain skips shadowEntry (switches pressed down, landed falling blocks)
    MOBJ_FLAG_CALC_MTX = 0x4,       // mobjMain rebuilds the matrix this frame, then clears the bit
    MOBJ_FLAG_HIT = 0x8,            // hit this frame (the kind is in hitFlag); the type's mainFunc clears it
    MOBJ_FLAG_HIT_EVENT_OFF = 0x10, // evt_mobj_hitevt_onoff; no reader in this tree
    MOBJ_FLAG_HINT = 0x20,          // mobjGetHint: Mario shows the "!" balloon at it (locks, item boxes)
    MOBJ_FLAG_FALL = 0x40,          // falls under gravity and bounce until it lands
    MOBJ_FLAG_NO_CULL = 0x80,       // drawn even when its position is outside the view
    MOBJ_FLAG_NO_HIT = 0x100,       // MOBJ_FLAG_HIT is cleared every frame
    MOBJ_FLAG_BUSY = 0x200,         // mobjCheckExec: blocks the pause menu (win_main.c); no setter in C
    MOBJ_FLAG_PAPER_TEX = 0x400,    // drawn with paperTexObj (rotating floor, evt_mobj.c); US: also keeps
                                    // running while a field battle starts
    MOBJ_FLAG_HIDDEN = 0x800,       // hidden block (kind >= 10) until hit: no shadow
    MOBJ_FLAG_EXEC_CANCEL = 0x1000, // evt_mobj_exec_cancel: the type's mainFunc aborts its sequence
    MOBJ_FLAG_BLINK = 0x2000,       // drawn only every other 8 frames
    MOBJ_FLAG_INVISIBLE = 0x4000,   // not drawn
};

// High half of MapObjectEntry.flags: the hit kinds the object reacts to. hitFlag holds the one that hit.
enum MapObjectHitFlags {
    MOBJ_HIT_HAMMER = 0x10000,            // Mario's hammer, from no higher than 5 above the object
    MOBJ_HIT_FRONT_ACTION = 0x40000,      // A button while touching the front (not during a partner action)
    MOBJ_HIT_KOOPA_FRONT = 0x80000,       // Bowser touching the front
    MOBJ_HIT_STAND_ON = 0x200000,         // stood on (Mario or Bowser)
    MOBJ_HIT_FROM_BELOW = 0x400000,       // Mario's head from below; such objects also get a round shadow
    MOBJ_HIT_PARTY_ACTION = 0x800000,     // partner action hitbox, or Bobbery's blast within range
    MOBJ_HIT_SPIN_JUMP = 0x1000000,       // stood on during marioChkHipBump (spin jump)
    MOBJ_HIT_BOMB = 0x2000000,            // Bobbery's blast hitbox (partner 3)
    MOBJ_HIT_KOOPA_HEAD = 0x4000000,      // one of Bowser's head hitboxes
    MOBJ_HIT_KOOPA_LEVEL3 = 0x8000000,    // Bowser's body at level 3
    MOBJ_HIT_KOOPA_HIP_DROP = 0x10000000, // Bowser's hip drop
    MOBJ_HIT_KOOPA_FLAME = 0x20000000,    // Bowser's flame
};

typedef struct MapObjectEntry {
    s32 flags;                   // 0x0, MapObjectFlags | MapObjectHitFlags
    u8 camId;                    // 0x4
    char name[16];               // 0x5
    char animName[16];           // 0x15
    u8 pad_25[0x38 - 0x25];      // 0x25, never accessed
    Vec position;                // 0x38
    Vec scale;                   // 0x44
    Vec rotation;                // 0x50
    Vec velocity;                // 0x5C, y used for falling/bouncing
    f32 gravity;                 // 0x68, subtracted from velocity.y each frame
    f32 bounce;                  // 0x6C, restitution on landing (-0.5 * bounce * vy)
    s32 poseId;                  // 0x70
    MapObjectHitEntry hitObj[2]; // 0x74
    Vec scale2;                  // 0x184
    Vec translation;             // 0x190
    s32 offscreenId;             // 0x19C
    union {                      // 0x1A0, per-block-type data (item id / item list, cost, state, ...; evt_mobj.c)
        s32 typeData[4];
        u32 typeDataU[4];
        void* typeDataP[4];
        s32* typeDataList[4]; // -1-terminated item id lists
        f32 typeDataF[4];
    };
    s32 timer;                               // 0x1B0, per-type countdown (timer switch, blinking, respawn delays)
    s32 typeWork;                            // 0x1B4, per-type: timer switch reload length; evt_mobj.c:4149 mobj loop SFX id
    char linkedName[0x1C8 - 0x1B8];          // 0x1B8, name of a paired mobj (mobjNameToPtr)
    struct EffectEntry* effect;              // 0x1C8, coin fukidashi effect (evt_mobj.c)
    s32 eventId;                             // 0x1CC
    s32 (*mainFunc)(struct MapObjectEntry*); // 0x1D0
    EvtWord event;                           // 0x1D4
    EvtWord extraEvent;                      // 0x1D8, second event script run via mobjRunEvent
    s32 state;                               // 0x1DC
    s32 hitFlag;                             // 0x1E0, the MapObjectHitFlags kind that hit (MOBJ_FLAG_HIT)
    s32 flagVar;                             // 0x1E4
    GXTexObj paperTexObj;                    // 0x1E8
    struct smartEntry* paperTexData;         // 0x208, texture data for paperTexObj
    Mtx paperTexMtx;                         // 0x20C
} MapObjectEntry;

typedef struct MapObjectWork {
    s32 count;               // 0x0
    MapObjectEntry* entries; // 0x4
    u8 pad_08[0x1C - 0x8];   // 0x8, never accessed
} MapObjectWork;

void mobjInit(void);
void mobjMain(void);
MapObjectEntry* mobjNameToPtrNoAssert(const char* name);
MapObjectEntry* mobjNameToPtr(const char* name);
void mobjCalcMtx(MapObjectEntry* mobj);
void mobjCalcMtx2(MapObjectEntry* mobj);

void mobjDelete(const char* name);
s32 mobjEntry(const char* name, const char* animPoseName);
void mobjHitEntry(MapObjectEntry* entry, s32 type);
MapObjectEntry* mobjHitObjPtrToPtr(HitEntry* hitObj);

extern const char kururinName[];

BOOL mobjCheckExec();
void mobjReset(BOOL inBattle);
void mobjSetPosition(const char* name, f32 x, f32 y, f32 z);

struct EventEntry;

void mobjKoopaOn(void);
struct EventEntry* mobjRunEvent(MapObjectEntry* entry, EvtWord* eventCode);
MapObjectEntry* mobjNearDistCheck(f32 x, f32 y, f32 z, f32 minMagnitude);
s32 mobjCheckItemboxOpen(MapObjectEntry* entry);
BOOL mobjGetHint(MapObjectEntry* entry);
MapObjectEntry* mobjNearDistCheck2(f32 x, f32 y, f32 z, f32 minMagnitude, char** names);
#if VERSION <= VERSION_DEMO_JP
// the demos keep it as a function; retail inlines it into mobjdrv.c
int mobjCheckKururingFloorItem(MapObjectEntry* entry);
#endif
