#pragma once

#include <dolphin/types.h>

typedef enum BattleWeaponSpecialFlags { SPECIAL_UNGUARDABLE = 0x20000 } BattleWeaponSpecialFlags;

typedef struct BattleWeapon {
    const char* name;                 // 0x0, msg tag
    u16 icon;                         // 0x4
    u8 field_0x6[0x8 - 0x6];          // 0x6
    s32 itemId;                       // 0x8
    const char* description;          // 0xC
    s8 baseAccuracy;                  // 0x10
    s8 baseFpCost;                    // 0x11
    s8 baseSpCost;                    // 0x12
    s8 superguardsAllowed;            // 0x13
    f32 field_0x14;                   // 0x14
    s8 mStylishCommandMultiplier;     // 0x18
    s8 field_0x19;                    // 0x19
    s8 mBingoSlotChance;              // 0x1A
    s8 field_0x1B;                    // 0x1B
    void* hpDamageFn;                 // 0x1C
    u32 hpDamageWork[8];              // 0x20
    void* fpDamageFn;                 // 0x40, TODO rename
    u32 fpDamageWork[8];              // 0x44
    u32 targetClassFlags;             // 0x64
    u32 targetPropertyFlags;          // 0x68
    s8 element;                       // 0x6C
    s8 damagePattern;                 // 0x6D
    s8 acLevel;                       // 0x6E
    s8 field_0x6F;                    // 0x6F
    const char* acHelpMsg;            // 0x70
    BattleWeaponSpecialFlags special; // 0x74
    u8 field_78[0x8B - 0x78];         // 0x78
    s8 electricChance;                // 0x8B
    s8 electricTime;                  // 0x8C
    s8 dodgyChance;                   // 0x8D
    s8 dodgyTime;                     // 0x8E
    u8 field_8F[0xA7 - 0x8F];         // 0x8F
    u8 field_0xA7;                    // 0xA7
    u8 field_A8[0xAA - 0xA8];         // 0xA8
    s8 hpRegenTime;                   // 0xAA
    s8 hpRegenStrength;               // 0xAB
    s8 fpRegenTime;                   // 0xAC
    s8 fpRegenStrength;               // 0xAD
    u8 field_AE[0xB0 - 0xAE];         // 0xAE
    void* mAttackEvtScript;           // 0xB0
    u8 field_B4[0xC0 - 0xB4];         // 0xB4
} BattleWeapon;
