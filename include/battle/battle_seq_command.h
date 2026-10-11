#pragma once

#include <dolphin/types.h>

struct BattleWeapon;

typedef struct BattleCommandCursor {
    s32 field_0; // 0x0, absolute position
    s32 field_4; // 0x4, relative position
    s32 unk8;    // 0x8, number of options
} BattleCursor;

typedef struct BattleCommandAct {
    s32 type;          // 0x0
    s32 enabled;       // 0x4
    const char* name;  // 0x8
    s16 icon;          // 0xC
    u8 padE[2];        // 0xE
    s32 disableReason; // 0x10
} BattleCommandAct;

typedef struct BattleCommandWeapon {
    struct BattleWeapon* weapon; // 0x0
    s32 enabled;                 // 0x4
    const char* name;            // 0x8
    s16 icon;                    // 0xC
    u8 padE[2];                  // 0xE
    s32 index;                   // 0x10
    s32 itemId;                  // 0x14
    s32 disableReason;           // 0x18
} BattleCommandWeapon;

typedef struct BattleCommandOperation {
    s32 type;          // 0x0
    s32 enabled;       // 0x4
    s32 disableReason; // 0x8
    const char* name;  // 0xC
    s16 icon;          // 0x10
    u8 pad12[2];       // 0x12
    const char* help;  // 0x14
    s32 cost;          // 0x18
} BattleCommandOperation;

typedef struct BattleCommandParty {
    s32 kind;          // 0x0
    s32 enabled;       // 0x4
    const char* name;  // 0x8
    s16 icon;          // 0xC
    u8 padE[2];        // 0xE
    const char* help;  // 0x10
    s16 hp;            // 0x14
    s16 maxHp;         // 0x16
} BattleCommandParty;

typedef struct BattleCommandMultiItem {
    s32 enabled;       // 0x0
    const char* name;  // 0x4
    const char* help;  // 0x8
    s16 icon;          // 0xC
    u8 padE[2];        // 0xE
    s32 cost;          // 0x10
    s32 disableReason; // 0x14
} BattleCommandMultiItem;

typedef struct BattleCommand {
    s32 unk0;                                // 0x0
    s32 field_4;                             // 0x4
    BattleCommandAct act[6];                 // 0x8
    BattleCommandWeapon weapon[21];          // 0x80
    BattleCommandOperation operation[7];     // 0x2CC
    BattleCommandParty party[8];             // 0x390
    BattleCommandMultiItem multiItem[3];     // 0x450
    BattleCursor cursor[14];                 // 0x498
    u8 unk540[0x55C - 0x540];                // 0x540
    void* field_55C;                         // 0x55C
    u8 unk560[0x574 - 0x560];                // 0x560
} BattleCommand;
