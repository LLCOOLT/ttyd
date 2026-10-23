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

extern s32 battle_flower_drop_param_default[];
extern s32 battle_flower_drop_param_default2[];
extern s32 battle_flower_drop_param_default3[];
extern s32 battle_flower_drop_param_default4[];
extern s32 battle_flower_drop_param_default5[];
extern s32 battle_heart_drop_param_default[];
extern s32 battle_heart_drop_param_default2[];
extern s32 battle_heart_drop_param_default3[];
extern s32 battle_heart_drop_param_default4[];
extern s32 battle_heart_drop_param_default5[];
extern s32 battle_item_NONE[];
extern s32 battle_item_atmic_teresa[];
extern s32 battle_item_badge_borodo[];
extern s32 battle_item_barriern[];
extern s32 battle_item_barriern_custom[];
extern s32 battle_item_barriern_z[];
extern s32 battle_item_basabasa[];
extern s32 battle_item_basabasa_chururu[];
extern s32 battle_item_basabasa_green[];
extern s32 battle_item_bllizard[];
extern s32 battle_item_bomhei[];
extern s32 battle_item_boomerang_bros[];
extern s32 battle_item_borodo[];
extern s32 battle_item_borodo_king[];
extern s32 battle_item_bubble[];
extern s32 battle_item_burst_wanwan[];
extern s32 battle_item_champion[];
extern s32 battle_item_chorobon[];
extern s32 battle_item_churantalar[];
extern s32 battle_item_cortez[];
extern s32 battle_item_dark_keeper[];
extern s32 battle_item_default_param_list[];
extern s32 battle_item_dokugassun[];
extern s32 battle_item_faker_mario[];
extern s32 battle_item_fire_bros[];
extern s32 battle_item_flower_chorobon[];
extern s32 battle_item_gesso[];
extern s32 battle_item_giant_bomb[];
extern s32 battle_item_gold_chorobon[];
extern s32 battle_item_gonbaba[];
extern s32 battle_item_green_chorobon[];
extern s32 battle_item_gundan_zako[];
extern s32 battle_item_gundan_zako_elite[];
extern s32 battle_item_gundan_zako_magician[];
extern s32 battle_item_hammer_bros[];
extern s32 battle_item_hannya[];
extern s32 battle_item_heavy_bom[];
extern s32 battle_item_hennya[];
extern s32 battle_item_hermos[];
extern s32 battle_item_hinnya[];
extern s32 battle_item_honenoko[];
extern s32 battle_item_hyper_jyugem[];
extern s32 battle_item_hyper_kuriboo[];
extern s32 battle_item_hyper_patakuri[];
extern s32 battle_item_hyper_sinemon[];
extern s32 battle_item_hyper_sinnosuke[];
extern s32 battle_item_hyper_togekuri[];
extern s32 battle_item_hyper_togemet[];
extern s32 battle_item_ice_pakkun[];
extern s32 battle_item_iron_sinemon[];
extern s32 battle_item_iron_sinemon2[];
extern s32 battle_item_jyugem[];
extern s32 battle_item_kamec[];
extern s32 battle_item_kanbu1[];
extern s32 battle_item_karon[];
extern s32 battle_item_killer[];
extern s32 battle_item_killer_cannon[];
extern s32 battle_item_kuriboo[];
extern s32 battle_item_kurikuri[];
extern s32 battle_item_kurokumorn[];
extern s32 battle_item_macho_gance[];
extern s32 battle_item_magnum_battender[];
extern s32 battle_item_mahorn[];
extern s32 battle_item_mahorn_custom[];
extern s32 battle_item_met[];
extern s32 battle_item_moamoa[];
extern s32 battle_item_monban[];
extern s32 battle_item_monochrome__pakkun[];
extern s32 battle_item_monochrome_kurokumorn[];
extern s32 battle_item_monochrome_sinemon[];
extern s32 battle_item_nokonoko[];
extern s32 battle_item_nokonoko_fighter[];
extern s32 battle_item_pakkun_flower[];
extern s32 battle_item_pansy[];
extern s32 battle_item_patakuri[];
extern s32 battle_item_patamet[];
extern s32 battle_item_patapata[];
extern s32 battle_item_patapata_fighter[];
extern s32 battle_item_patatogemet[];
extern s32 battle_item_phantom[];
extern s32 battle_item_piders[];
extern s32 battle_item_poison_pakkun[];
extern s32 battle_item_purple_teresa[];
extern s32 battle_item_rampell[];
extern s32 battle_item_red_honenoko[];
extern s32 battle_item_sambo[];
extern s32 battle_item_sambo_mummy[];
extern s32 battle_item_sinemon[];
extern s32 battle_item_sinnosuke[];
extern s32 battle_item_super_killer[];
extern s32 battle_item_super_killer_cannon[];
extern s32 battle_item_super_mahorn[];
extern s32 battle_item_teresa[];
extern s32 battle_item_togedaruma[];
extern s32 battle_item_togekuri[];
extern s32 battle_item_togemet[];
extern s32 battle_item_togenoko[];
extern s32 battle_item_togenoko_ace[];
extern s32 battle_item_togezo[];
extern s32 battle_item_twinkling_pansy[];
extern s32 battle_item_ura_noko[];
extern s32 battle_item_ura_pata[];
extern s32 battle_item_vivian1[];
extern s32 battle_item_wanwan[];
extern s32 battle_item_yami_kuriboo[];
extern s32 battle_item_yami_noko[];
extern s32 battle_item_yami_patakuri[];
extern s32 battle_item_yami_togekuri[];
extern s32 battle_item_yamitogedaruma[];
extern s32 battle_item_zonbaba[];
