// itemdrv.c: the field item driver (ItemEntry, ITEM_FLAG_*, item status flags): drops, coins and pickups.
#pragma once

#include "driver/effdrv.h"
#include "evt/evt_word.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>

// ItemEntry.flags (itemFlagOn/itemFlagOff/itemFlag). Meanings from the readers in itemdrv.c.
enum ItemFlags {
    ITEM_FLAG_USED = 0x1,
    ITEM_FLAG_NO_TOUCH = 0x2,         // itemHitCheck ignores it: not picked up by walking into it
    ITEM_FLAG_INSTANT_GET = 0x4,      // coins, hearts, flowers: straight into the pouch, no get sequence
    ITEM_FLAG_BGM_SILENT = 0x8,       // the field BGM was silent at the get: leave it off afterwards
    ITEM_FLAG_CUSTOM_BOUNCE = 0x10,   // the launch keeps the caller's bounceFactor/gravityScale/maxBounces
    ITEM_FLAG_COLLECT_GSWF = 0x20,    // collectFlag is a GSWF, set on pickup
    ITEM_FLAG_COLLECT_LSWF = 0x40,    // collectFlag is an LSWF, set on pickup
    ITEM_FLAG_ELASTIC = 0x80,         // bounces keep their speed; no setter in C
    ITEM_FLAG_BADGE_RETURN = 0x100,   // retail: a badge goes back to the pouch when the item is deleted
                                      // (the demo reads the bit the other way round: set = stays out)
    ITEM_FLAG_RESTORE_MOTION = 0x200, // first bounce restores savedDirection/savedSpeed; no setter in C
    ITEM_FLAG_REPLACEABLE = 0x400,    // a dropped coin/heart/flower itemEntry may delete when the list is full
    ITEM_FLAG_NO_CEILING = 0x800,     // itemseq_Bound skips the ceiling check
    ITEM_FLAG_FORCE_GET = 0x1000,     // itemForceGet: the get does not wait for Mario's get motion
    ITEM_FLAG_JINGLE_DONE = 0x2000,   // the get jingle has finished and the BGM is back
    ITEM_FLAG_KOOPS_GET = 0x4000,     // itemNokoForceGet: fetched by Koops's shell (waits for the motion)
    ITEM_FLAG_NO_JINGLE = 0x8000,     // no get jingle
};

// ItemEntry.status (itemStatusOn/itemStatus). Meanings from the readers in itemdrv.c.
enum ItemStatusFlags {
    ITEM_STATUS_IN_POUCH = 0x1,                 // itemGetPouch put it into the pouch
    ITEM_STATUS_END_WAIT = 0x2,                 // ends the evt_item get waits; no setter in C
    ITEM_STATUS_LAUNCH = 0x4,                   // launched: not collectable until it falls or bounces
    ITEM_STATUS_THROWN = 0x8,                   // thrown back out: not collectable until the first bounce
    ITEM_STATUS_CUSTOM_LAUNCH = 0x10,           // the next bounce start keeps the caller's speed/direction/velocityY
    ITEM_STATUS_VANISH_ON_FALL = 0x20,          // mode 10: deleted in a stardust puff once it starts to fall
    ITEM_STATUS_SCATTER = 0x40,                 // dropped coin: directions spread in 132 degree steps
    ITEM_STATUS_BLINK_HIDDEN = 0x100,           // hidden this frame (blinking before it times out)
    ITEM_STATUS_PARTY_HOLD = 0x1000,            // itemPickUp: carried by the partner (mode 8)
    ITEM_STATUS_IMPORTANT = 0x2000,             // items 7, 8, 10, 11: the get ends with the important-item lecture
    ITEM_STATUS_TIMER_HOLD = 0x4000,            // the despawn timer waits until the item lands
    ITEM_STATUS_NO_Z_MOVE = 0x8000,             // no Z motion (set when Mario has flag 0x2000000)
    ITEM_STATUS_GET_ENDED = 0x10000,            // the get sequence is over (evt_item get waits end)
    ITEM_STATUS_IN_WATER = 0x100000,            // fell into water or lava (hit attr 0x600): not collectable
    ITEM_STATUS_CTRL_OFF = 0x1000000,           // the get turned Mario's control off; itemGetEnd turns it back on
    ITEM_STATUS_NO_KOOPS = 0x2000000,           // Koops's shell and itemNearDistCheck ignore it
    ITEM_STATUS_SAVED_BADGE_RETURN = 0x4000000, // ITEM_FLAG_BADGE_RETURN saved over the get sequence
};

typedef struct ItemEntry {
    u16 flags;              // 0x0, ItemFlags
    u16 type;               // 0x2, entry type (itemEntry arg)
    s32 itemId;             // 0x4
    s32 collectFlag;        // 0x8, GSWF/LSWF flag set when collected, -1 for none
    char name[0x10];        // 0xC
    EffectEntry* effect;    // 0x1C
    EvtWord evtCode;        // 0x20, event script run on pickup (evtEntry)
    u16 mode;               // 0x24
    u16 subState;           // 0x26, per-sequence state
    s32 winId[3];           // 0x28
    u8 pad_34[0x38 - 0x34]; // 0x34, never accessed
    u32 status;             // 0x38, ItemStatusFlags
    Vec position;           // 0x3C
    f32 scale;              // 0x48
    u8 alpha;               // 0x4C
    u8 pad_4D[0x50 - 0x4D]; // 0x4D, never accessed
    f32 speed;              // 0x50
    s32 direction;          // 0x54
    f32 velocityY;          // 0x58
    u8 pad_5C[0x60 - 0x5C]; // 0x5C, never accessed
    s64 airTime;            // 0x60
    OSTime baseTime;        // 0x68, timestamp elapsed time is measured from
    OSTime curTime;         // 0x70
    s64 timer;              // 0x78
    f32 bounceFactor;       // 0x80
    f32 gravityScale;       // 0x84
    s32 maxBounces;         // 0x88
    s32 bounceCount;        // 0x8C
    s32 savedDirection;     // 0x90
    f32 savedSpeed;         // 0x94
} ItemEntry;

typedef struct ItemWork {
    s32 count;                     // 0x0
    ItemEntry* entries;            // 0x4
    u32 currId;                    // 0x8, next available itemId
    EffectEntry* effect;           // 0xC
    struct WinMgrSelect* select;   // 0x10
    struct EventEntry* lectureEvt; // 0x14
    s32 msgWindowId;               // 0x18
} ItemWork;

void itemInit(void);
void itemReInit(void);
void itemMain(void);
ItemEntry* itemNameToPtr(char*);

void itemNokoForceGet(ItemEntry* entry);
void itemPickUp(ItemEntry* entry);

void itemDelete(const char* name);
// The position comes first: every call site in the original binary evaluates x, y, z before the other
// arguments. type picks the start mode and despawn timer (the switch at the end of itemdrv.c itemEntry);
// collectFlag is a GSWF/LSWF set on pickup, or -1; pickupEvt runs on pickup (NULL for none).
// Returns NULL when collectFlag is already set or no slot is free.
ItemEntry* itemEntry(f32 x, f32 y, f32 z, const char* name, s32 itemId, u16 type, s32 collectFlag, EvtWord* pickupEvt);
void itemFlagOn(ItemEntry* entry, u16 flags);
void itemModeChange(ItemEntry* entry, s32 mode);

BOOL N_itemPickUpFromFieldCheck(void);
void itemSetPosition(ItemEntry* entry, f32 x, f32 y, f32 z);
void itemFlagOff(ItemEntry* entry, u16 flags);
u16 itemFlag(ItemEntry* entry, u16 flags);
u32 itemStatus(ItemEntry* entry, u32 flags);
void itemForceGet(ItemEntry* entry);
ItemEntry* itemHitCheck(f32 x, f32 y, f32 z, f32 range);
ItemEntry* itemNearDistCheck(f32 x, f32 y, f32 z, f32 range);
void itemStatusOn(ItemEntry* entry, u32 flags);
