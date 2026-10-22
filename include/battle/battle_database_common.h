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
    u32 counterResistFlags;           // 0x78
    u32 targetWeightFlags;            // 0x7C
    u8 sleepChance;                   // 0x80, status chances are % (0-100), times in turns
    s8 sleepTime;                     // 0x81
    u8 stopChance;                    // 0x82
    s8 stopTime;                      // 0x83
    u8 dizzyChance;                   // 0x84
    s8 dizzyTime;                     // 0x85
    u8 poisonChance;                  // 0x86
    s8 poisonTime;                    // 0x87
    s8 poisonStrength;                // 0x88
    u8 confuseChance;                 // 0x89
    s8 confuseTime;                   // 0x8A
    s8 electricChance;                // 0x8B
    s8 electricTime;                  // 0x8C
    s8 dodgyChance;                   // 0x8D
    s8 dodgyTime;                     // 0x8E
    u8 burnChance;                    // 0x8F
    s8 burnTime;                      // 0x90
    u8 freezeChance;                  // 0x91
    s8 freezeTime;                    // 0x92
    u8 sizeChangeChance;              // 0x93
    s8 sizeChangeTime;                // 0x94
    s8 sizeChangeStrength;            // 0x95, >0 grow, <0 shrink
    u8 atkChangeChance;               // 0x96
    s8 atkChangeTime;                 // 0x97
    s8 atkChangeStrength;             // 0x98, >0 up, <0 down
    u8 defChangeChance;               // 0x99
    s8 defChangeTime;                 // 0x9A
    s8 defChangeStrength;             // 0x9B, >0 up, <0 down
    u8 allergicChance;                // 0x9C
    s8 allergicTime;                  // 0x9D
    s8 ohkoChance;                    // 0x9E
    s8 chargeStrength;                // 0x9F
    u8 fastChance;                    // 0xA0
    s8 fastTime;                      // 0xA1
    u8 slowChance;                    // 0xA2
    s8 slowTime;                      // 0xA3
    u8 frightChance;                  // 0xA4
    u8 galeForceChance;               // 0xA5
    s8 paybackTime;                   // 0xA6
    u8 holdFastTime;                  // 0xA7
    u8 invisibleChance;               // 0xA8
    s8 invisibleTime;                 // 0xA9
    s8 hpRegenTime;                   // 0xAA
    s8 hpRegenStrength;               // 0xAB
    s8 fpRegenTime;                   // 0xAC
    s8 fpRegenStrength;               // 0xAD
    u8 field_AE[0xB0 - 0xAE];         // 0xAE
    void* mAttackEvtScript;           // 0xB0
    u8 field_B4[0xC0 - 0xB4];         // 0xB4
} BattleWeapon;
