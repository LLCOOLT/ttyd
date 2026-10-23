#pragma once

#include <dolphin/types.h>
#include "evt/evt_cmd.h"
#include "sdk/texPalette.h"

typedef struct WindowWork {
    u16 flags;                  // 0x0
    u8 align_2[2];              // 0x2
    u32 buttonTrg;              // 0x4
    u32 buttonRep;              // 0x8
    u32 dirTrg;                 // 0xC
    u32 dirRep;                 // 0x10
    union {
        u8 pad_14[0x20 - 0x14]; // 0x14, sizes the union
        struct {
            s32 lectureStep;            // 0x14
            EventEntry* lectureEvent;   // 0x18
            union {
                u8 pad_1C[0x20 - 0x1C]; // 0x1C
                s32 menuSel;                // 0x1C
            };
        };
    };
    s32 menuState;              // 0x20, TODO: rename?
    union {
        u8 pad_24[0x3C - 0x24]; // 0x24, sizes the union
        struct {
            s32 field_0x24_s32;     // 0x24
            void* res;              // 0x28, FileEntry*
        };
    };
    EventEntry* currentEvent;   // 0x3C
    union {
        u8 pad_40[0x1210 - 0x40]; // 0x40, sizes the union
        struct {
            u8 field_0x40_pad[0x1BC - 0x40]; // 0x40
            s32 partyIds[8];                 // 0x1BC
            s32 partySel;                    // 0x1DC
            u8 pad_1E0[0x2D4 - 0x1E0];   // 0x1E0
            s32 itemId;                      // 0x2D4
            s32 itemIdx;                     // 0x2D8
            s32 itemTarget;                  // 0x2DC
        };
    };
#ifdef VERSION_G8ME01
    u8 us_pad1210[8];           // 0x1210, US only: struct is 0x1218
#endif
} WindowWork;

typedef struct WindowPartyDt {
    s32 partyId;            // 0x0
    s32 nameMsgId;          // 0x4
    const char* name;       // 0x8
    const char* msg;        // 0xC
    const char* poseName;   // 0x10
    const char* animName;   // 0x14
    const char* poseName2;  // 0x18
    const char* animName2;  // 0x1C
    const char* waza; // 0x20, BattleWeapon** waza in win_party.c's WinPartyDt
} WindowPartyDt;            // same table as WinPartyDt (win_party.c / win_item.c)

WindowWork* winGetPtr(void);
void winInit(void);
void winReInit(void);
BOOL winCheck(void);
void winOpenEnable(void);
void winOpenDisable(void);
USER_FUNC(itemUseFunc);

void winMain(void);

void winTexInit(TEXPalette* texture);
void winTexSet(u32 textureId, Vec translate, Vec scale, GXColor color);

void winTexSetNearest(u32 textureId, Vec translate, Vec scale, GXColor color);

extern const volatile f32 float_0p5_8041dc98;
