// winmgr.c: the window manager (WinMgrDesc, WinMgrEntry, winMgrEntry/Main) and the winMgrSelect* lists.
#pragma once

#include "driver/dispdrv.h"
#include "evt/evt_word.h"
#include <dolphin/gx.h>
#include <dolphin/types.h>
#include "evt/evt_cmd.h"

struct EventEntry;

typedef struct WinMgrDesc WinMgrDesc;
typedef struct WinMgrEntry WinMgrEntry;

struct WinMgrDesc {
    s32 type;                         // 0x0
    s32 dispType;                     // 0x4
    s32 camId;                        // 0x8, CameraId
    s32 x;                            // 0xC, entry->x
    s32 y;                            // 0x10, entry->y
    s32 width;                        // 0x14, entry->width
    s32 height;                       // 0x18, entry->height
    GXColor color;                    // 0x1C
    void (*main)(WinMgrEntry* entry); // 0x20
    void (*disp)(WinMgrEntry* entry); // 0x24
};

// WinMgrEntry.flags
enum WinMgrEntryFlags {
    WINMGR_ENTRY_IN_USE = 0x1,      // the window slot is taken (winMgrEntry)
    WINMGR_ENTRY_VISIBLE = 0x2,     // open or animating: winMgrMain queues its drawing
    WINMGR_ENTRY_ANIMATING = 0x4,   // the open or close animation is running (winMgrAction)
    WINMGR_ENTRY_AUTO_DELETE = 0x8, // winMgrCloseAutoDelete: free the slot once closed
};

struct WinMgrEntry {
    s32 flags;               // 0x0
    s32 state;               // 0x4
    s32 timer;               // 0x8
    s32 alpha;               // 0xC
    f32 scale;               // 0x10
    f32 rotation;            // 0x14
    s32 x;                   // 0x18
    s32 y;                   // 0x1C
    s32 width;               // 0x20
    s32 height;              // 0x24
    WinMgrDesc* description; // 0x28
    void* param;             // 0x2C
    s32 priority;            // 0x30, gets cast to float for dispEntry
    const char* msg;         // 0x34
    s32 scroll;              // 0x38
    s32 lines;               // 0x3C
    u8 pad_40[0x44 - 0x40];  // 0x40
};

typedef struct WinMgrWork {
    s32 numEntries;       // 0x0
    WinMgrEntry* entries; // 0x4
} WinMgrWork;

// WinMgrSelectItem.flags
enum WinMgrSelectItemFlags {
    WINMGR_ITEM_GRAY = 0x1,     // drawn grayed out (already used, already upgraded, ...)
    WINMGR_ITEM_DISABLED = 0x2, // A only plays the error sound; no price or cost is drawn
    WINMGR_ITEM_OVER_CAP = 0x4, // retail level-up menu: the stat would go over its cap
    WINMGR_ITEM_EQUIPPED = 0x8, // US/PAL badge lists: the badge is equipped (drawn with a mark)
};

typedef struct WinMgrSelectItem {
    u16 flags; // 0x0, WinMgrSelectItemFlags
    u16 id;    // 0x2
} WinMgrSelectItem;

// WinMgrSelect.flags
enum WinMgrSelectFlags {
    WINMGR_SELECT_CANCELABLE = 0x100, // B cancels (and the new-item slot, if any, counts as cancel)
    WINMGR_SELECT_DONE = 0x1000,      // the windows have closed; winMgrSelect returns the choice
    WINMGR_SELECT_CANCELED = 0x2000,  // B was pressed; winMgrSelect returns -1
};

typedef struct WinMgrSelect {
    u16 flags;               // 0x0, WinMgrSelectFlags
    u16 pad_2;               // 0x2
    s32 type;                // 0x4
    s32 state;               // 0x8
    s32 cursor;              // 0xC
    s32 scrollTop;           // 0x10
    f32 cursorX;             // 0x14, hand cursor (icon 0x1F0) x, eased toward the selected row
    f32 cursorY;             // 0x18, hand cursor y
    f32 scrollY;             // 0x1C, list scroll offset, eased toward 24 * scrollTop
    s32 numDescriptors;      // 0x20
    s32 descriptorId[3];     // 0x24
    WinMgrSelectItem* items; // 0x30
    s32 numItems;            // 0x34
    s32 newItem;             // 0x38, item being picked up when the bag is full (row 0 above a divider; picking it returns -1)
} WinMgrSelect;

void winMgrInit(void);
void winMgrReInit(void);
void winMgrMain(void);
s32 winMgrEntry(WinMgrDesc* desc);
void winMgrSetParam(s32 id, void* param);
void winMgrOpen(s32 id);
void winMgrClose(s32 id);
void winMgrCloseAutoDelete(s32 id);
void winMgrDelete(s32 id);
BOOL winMgrAction(s32 id);
void winMgrSetSize(s32 id, s32 x, s32 y, s32 width, s32 height);
void winMgrSetPriority(s32 id, s32 priority);
WinMgrEntry* winMgrGetPtr(s32 id);
void winMgrHelpInit(WinMgrEntry* entry);
void winMgrHelpMain(WinMgrEntry* entry);
void winMgrHelpDraw(WinMgrEntry* entry);
WinMgrSelect* winMgrSelectEntry(EvtWord type, s32 newItem, BOOL cancelable);
s32 winMgrSelect(WinMgrSelect* select);
s32 winMgrSelectOther(WinMgrSelect* select, struct EventEntry* evt);
void winMgrSelectDelete(WinMgrSelect* select);

USER_FUNC(evt_win_party_lankup_chk);
USER_FUNC(evt_win_party_lankdown_chk);
s32 winMgrSelectGetCursor(WinMgrSelect* sel);
