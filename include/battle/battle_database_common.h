// Declares the weapon special flags and shared battle drop-table types.
#pragma once

#include <dolphin/types.h>
#include "evt/evt_word.h"

// BattleWeapon.special. Read in battle_damage.c (BattleCalculateDamage, BattlePreCheckDamage, BattleSetStatusDamage,
// BattleCheckDamage) unless noted.
typedef enum BattleWeaponSpecialFlags {
    SPECIAL_BADGE_BUFFABLE = 0x1,                // Power Plus, P-Up D-Down, All or Nothing, Mega/Power Rush, Ice Power, HP/FP Drain apply
    SPECIAL_STATUS_BUFFABLE = 0x2,               // Huge, Attack Up, Tiny, Attack Down and Merlee's power bonus apply
    SPECIAL_CHARGE_BUFFABLE = 0x4,               // Charge adds its strength (and is used up)
    SPECIAL_ALWAYS_HITS = 0x8,                   // skips the Invisible, Veil, Lucky, Dodgy and accuracy checks
    SPECIAL_DIMINISHING_BY_HIT = 0x10,           // damage minus the target's hpDamageCount (at least 1)
    SPECIAL_DIMINISHING_BY_TARGET = 0x20,        // damage minus the attacker's per-action hit count (at least 1)
    SPECIAL_PIERCES_DEFENSE = 0x40,              // defense counts as 0
    SPECIAL_SHATTERS_FREEZE = 0x80,              // frozen-target hit code 0x8717 (its roll, irand(100) < 0, never passes)
    SPECIAL_IGNORE_STATUS_VULNERABILITY = 0x100, // status chance not scaled by the target's resistance or levels
    SPECIAL_UNUSED_200 = 0x200,                  // set only on Flurrie's breath attack; never read
    SPECIAL_FIERY_IF_BURNED = 0x400,             // a burned attacker's hit is fire (and sets off explosive counters)
    SPECIAL_ATTACK_FX = 0x800,                   // an equipped Attack FX badge replaces the hit sound (BattleCheckPikkyoro)
    SPECIAL_FLIPS_SHELLED = 0x1000,              // flips a shelled part
    SPECIAL_FLIPS_BOMB_FLIPPABLE = 0x2000,       // flips a part that a bomb can flip
    SPECIAL_GROUNDS_WINGED = 0x4000,             // knocks a winged part to the ground
    SPECIAL_FORCE_RESULT_10000 = 0x8000,         // with damage flag 0x100: result bit 0x10000 even on unit attribute 0x100; no weapon sets it
    SPECIAL_USABLE_IF_CONFUSED = 0x10000,        // a confused unit may still pick it (battle_seq_command.c, battle_enemy_item.c)
    SPECIAL_UNGUARDABLE = 0x20000,               // skips the guard and superguard check
    SPECIAL_HITS_EVASIVE_PARTS = 0x40000,        // hits parts that otherwise always dodge (part attribute 0x4000); no weapon sets it
} BattleWeaponSpecialFlags;

struct BattleUnit;
struct BattleUnitPart;
struct BattleWeapon;
// BattleWeapon.hpDamageFn / fpDamageFn: the base power of the hit (battle_weapon_power.c and the sac_*.c moves).
typedef s32 (*WeaponPowerFn)(struct BattleUnit* attacker, struct BattleWeapon* weapon, struct BattleUnit* target,
                             struct BattleUnitPart* part);

// BattleWeapon.targetClassFlags: which units and parts a weapon may target.
// Read by _btlSamplingEnemy (battle_detect.c) unless noted. "Opposing" is the
// alliance passed to BattleSamplingEnemy as `belong`, the attacker's enemy side;
// a confused attacker gets the two alliance flags swapped (BattleSamplingEnemy).
typedef enum BattleWeaponTargetClassFlags {
    TARGET_CLASS_NO_MARIO = 0x1,                // not Mario (nor the Shell Shield, except in the demo)
    TARGET_CLASS_NO_PARTNER = 0x2,              // not a partner
    TARGET_CLASS_UNUSED_4 = 0x4,                // never read
    TARGET_CLASS_UNUSED_8 = 0x8,                // never read
    TARGET_CLASS_NO_ENEMY = 0x10,               // not an enemy (kinds below UNIT_UNUSED_TREE)
    TARGET_CLASS_NO_TREE_OR_SWITCH = 0x20,      // not UNIT_UNUSED_TREE or UNIT_UNUSED_SWITCH
    TARGET_CLASS_NO_SYSTEM_UNIT = 0x40,         // not UNIT_UNUSED_TESTNPC..UNIT_PROLOGUE_GOOMBELLA
    TARGET_CLASS_NO_OPPOSING_ALLIANCE = 0x100,  // not the opposing alliance
    TARGET_CLASS_NO_OWN_ALLIANCE = 0x200,       // only the opposing alliance (or alliance 2)
    TARGET_CLASS_NO_SELF = 0x1000,              // not the attacker
    TARGET_CLASS_NO_SAME_KIND = 0x2000,         // not another unit of the attacker's kind
    TARGET_CLASS_ONLY_SELF = 0x4000,            // only the attacker
    TARGET_CLASS_ONLY_MARIO = 0x10000,          // only Mario
    TARGET_CLASS_ONLY_TREE_OR_SWITCH = 0x20000, // only UNIT_UNUSED_TREE or UNIT_UNUSED_SWITCH
    TARGET_CLASS_MAIN_PARTS = 0x100000,         // main or important parts; an important part is dropped when its unit's main part is a target
    TARGET_CLASS_ANY_PART = 0x200000,           // main, important or semi-important parts
    TARGET_CLASS_SINGLE = 0x1000000,            // one target (btlevtcmd_CheckWeaponPluralTarget, the command menu)
    TARGET_CLASS_MULTIPLE = 0x2000000,          // all targets at once (the command menu)
    TARGET_CLASS_NONE = 0x80000000,             // no targets: numTargets = -1
} BattleWeaponTargetClassFlags;

// BattleWeapon.targetPropertyFlags: further target filters (_btlSamplingEnemy)
// and where the command-menu cursor starts (_btlcmd_SelectWeaponDecide).
typedef enum BattleWeaponTargetPropertyFlags {
    TARGET_PROP_TATTLE = 0x1,                     // only parts that can be tattled
    TARGET_PROP_NO_FLOATING = 0x2,                // not a floating unit (UNIT_ATTR_FLOATING)
    TARGET_PROP_NO_CEILING = 0x4,                 // not a unit on the ceiling (UNIT_ATTR_CEILING)
    TARGET_PROP_NO_FLOATING_2 = 0x8,              // the same test as TARGET_PROP_NO_FLOATING
    TARGET_PROP_ONLY_AIRBORNE = 0x10,             // only floating or ceiling units
    TARGET_PROP_JUMPLIKE = 0x1000,                // not parts with PART_ATTR_JUMPLIKE_CANNOT_TARGET
    TARGET_PROP_HAMMERLIKE = 0x2000,              // not parts with PART_ATTR_HAMMERLIKE_CANNOT_TARGET
    TARGET_PROP_SHELL_TOSS_LIKE = 0x4000,         // not parts with PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET
    TARGET_PROP_ONLY_SHELL_TOSS_IMMUNE = 0x8000,  // only parts with PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET
    TARGET_PROP_RECOIL = 0x100000,                // with HAMMERLIKE, the attacker's own hammer-immune parts stay targets (not in the demo)
    TARGET_PROP_FRONTMOST = 0x1000000,            // only the frontmost target on each side
    TARGET_PROP_NO_SHELL_SHIELDED = 0x2000000,    // not a unit behind the Shell Shield (UNIT_ATTR_SHELL_SHIELDED)
    TARGET_PROP_NO_PART_ATTR_2000000 = 0x4000000, // not parts with attribute 0x2000000; no weapon sets it
    TARGET_PROP_START_OWN_SIDE = 0x10000000,      // cursor starts on the attacker's alliance (and btlevtcmd_SamplingEnemy flips the direction)
    TARGET_PROP_START_OPPOSING_SIDE = 0x20000000, // cursor starts on the opposing alliance
} BattleWeaponTargetPropertyFlags;

// BattleWeapon.counterResistFlags: counters the weapon ignores (BattlePreCheckDamage
// and BattleCheckCounter, battle_damage.c).
typedef enum BattleWeaponCounterResistFlags {
    COUNTER_RESIST_ELECTRIC = 0x1,
    COUNTER_RESIST_TOP_SPIKY = 0x2,
    COUNTER_RESIST_PREEMPTIVE_SPIKY = 0x4,
    COUNTER_RESIST_FRONT_SPIKY = 0x8,
    COUNTER_RESIST_FIERY = 0x10,
    COUNTER_RESIST_ICY = 0x20,
    COUNTER_RESIST_POISON = 0x40,
    COUNTER_RESIST_EXPLOSIVE = 0x80,
    COUNTER_RESIST_VOLATILE_EXPLOSIVE = 0x100,
    COUNTER_RESIST_PAYBACK = 0x200, // Payback status and Return Postage
    COUNTER_RESIST_HOLD_FAST = 0x400,
    COUNTER_RESIST_ALL = 0x7FF,
} BattleWeaponCounterResistFlags;

// BattleWeapon.targetWeightFlags: how BattleChoiceSamplingEnemy (battle_detect.c)
// weights the targets when the game picks one for an AI or a random attack.
typedef enum BattleWeaponTargetWeightFlags {
    TARGET_WEIGHT_PREFER_MARIO = 0x1,
    TARGET_WEIGHT_PREFER_PARTNER = 0x2,
    TARGET_WEIGHT_PREFER_FRONT = 0x4,
    TARGET_WEIGHT_PREFER_BACK = 0x8,
    TARGET_WEIGHT_PREFER_OWN_ALLIANCE = 0x10,
    TARGET_WEIGHT_PREFER_OPPOSING_ALLIANCE = 0x20,
    TARGET_WEIGHT_PREFER_LOW_HP_RATIO = 0x100,
    TARGET_WEIGHT_PREFER_HIGH_HP_RATIO = 0x200,
    TARGET_WEIGHT_PREFER_LOW_HP = 0x400,
    TARGET_WEIGHT_PREFER_HIGH_HP = 0x800,
    TARGET_WEIGHT_PREFER_IN_PERIL = 0x1000,
    TARGET_WEIGHT_UNUSED_2000 = 0x2000, // set on many weapons, never read
    TARGET_WEIGHT_RANDOM = 0x80000000,  // pick by weighted chance instead of the highest weight
} BattleWeaponTargetWeightFlags;

// BattleWeapon.element: picks the target part's defence and defence attribute (defenses[element]) and the hit
// type in BattleCalculateDamage; fire, explosion and electric set off explosive counters.
typedef enum BattleWeaponElement {
    ELEMENT_NORMAL = 0,    // DAMAGE_HIT_NORMAL
    ELEMENT_FIRE = 1,      // DAMAGE_HIT_FIRE; Ice Power reduces it; SPECIAL_FIERY_IF_BURNED switches to it
    ELEMENT_ICE = 2,       // DAMAGE_HIT_ICE
    ELEMENT_EXPLOSION = 3, // DAMAGE_HIT_EXPLOSION
    ELEMENT_ELECTRIC = 4,  // DAMAGE_HIT_ELECTRIC
} BattleWeaponElement;

typedef struct BattleWeapon {
    const char* name;                 // 0x0, msg tag
    u16 icon;                         // 0x4
    u8 pad_06[0x8 - 0x6];             // 0x6, always 0, never accessed
    s32 itemId;                       // 0x8
    const char* description;          // 0xC
    s8 baseAccuracy;                  // 0x10
    s8 baseFpCost;                    // 0x11
    u8 baseSpCost;                    // 0x12
    u8 superguardsAllowed;            // 0x13
    f32 reserved_14;                  // 0x14, 1.0f in every weapon table, never read
    s8 stylishCommandMultiplier;      // 0x18
    s8 reserved_19;                   // 0x19, 1 (5 on player moves); copied to StarPowerInfo.reserved_09 (battle_ac.c), never read
    s8 bingoSlotChance;               // 0x1A
    s8 reserved_1B;                   // 0x1B, 1 (50 on player moves), never read
    WeaponPowerFn hpDamageFn;         // 0x1C, base HP damage (NULL: no damage)
    u32 hpDamageWork[8];              // 0x20
    WeaponPowerFn fpDamageFn;         // 0x40, base FP damage (NULL: none)
    u32 fpDamageWork[8];              // 0x44
    u32 targetClassFlags;             // 0x64
    u32 targetPropertyFlags;          // 0x68
    u8 element;                       // 0x6C, BattleWeaponElement
    u8 damagePattern;                 // 0x6D
    s8 acLevel;                       // 0x6E
    s8 reserved_6F;                   // 0x6F, 2 in every weapon table, never read
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
    u8 electricChance;                // 0x8B
    s8 electricTime;                  // 0x8C
    u8 dodgyChance;                   // 0x8D
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
    s8 holdFastTime;                  // 0xA7
    u8 invisibleChance;               // 0xA8
    s8 invisibleTime;                 // 0xA9
    s8 hpRegenTime;                   // 0xAA
    s8 hpRegenStrength;               // 0xAB
    s8 fpRegenTime;                   // 0xAC
    s8 fpRegenStrength;               // 0xAD
    u8 pad_AE[0xB0 - 0xAE];           // 0xAE, always 0, never accessed
    EvtWord* attackEvtScript;         // 0xB0
    u8 stageEffectRates[0xC0 - 0xB4]; // 0xB4, btlevtcmd_WeaponAftereffect: [0..3] A1+A2 / A1 / A2 / none fall weights, [4] B destroy, [5] nozzle turn, [6] nozzle fire, [7] iron frame fall, [8] object fall (%), [9..11] unused
} BattleWeapon;

#include "driver/npcdrv.h" /* ItemDropData, PointDropData */

extern PointDropData battle_flower_drop_param_default[];
extern PointDropData battle_flower_drop_param_default2[];
extern PointDropData battle_flower_drop_param_default3[];
extern PointDropData battle_flower_drop_param_default4[];
extern PointDropData battle_flower_drop_param_default5[];
extern PointDropData battle_heart_drop_param_default[];
extern PointDropData battle_heart_drop_param_default2[];
extern PointDropData battle_heart_drop_param_default3[];
extern PointDropData battle_heart_drop_param_default4[];
extern PointDropData battle_heart_drop_param_default5[];
extern ItemDropData battle_item_NONE[];
extern ItemDropData battle_item_atmic_teresa[];
extern ItemDropData battle_item_badge_borodo[];
extern ItemDropData battle_item_barriern[];
extern ItemDropData battle_item_barriern_custom[];
extern ItemDropData battle_item_barriern_z[];
extern ItemDropData battle_item_basabasa[];
extern ItemDropData battle_item_basabasa_chururu[];
extern ItemDropData battle_item_basabasa_green[];
extern ItemDropData battle_item_bllizard[];
extern ItemDropData battle_item_bomhei[];
extern ItemDropData battle_item_boomerang_bros[];
extern ItemDropData battle_item_borodo[];
extern ItemDropData battle_item_borodo_king[];
extern ItemDropData battle_item_bubble[];
extern ItemDropData battle_item_burst_wanwan[];
extern ItemDropData battle_item_champion[];
extern ItemDropData battle_item_chorobon[];
extern ItemDropData battle_item_churantalar[];
extern ItemDropData battle_item_cortez[];
extern ItemDropData battle_item_dark_keeper[];
extern ItemDropData battle_item_default_param_list[];
extern ItemDropData battle_item_dokugassun[];
extern ItemDropData battle_item_faker_mario[];
extern ItemDropData battle_item_fire_bros[];
extern ItemDropData battle_item_flower_chorobon[];
extern ItemDropData battle_item_gesso[];
extern ItemDropData battle_item_giant_bomb[];
extern ItemDropData battle_item_gold_chorobon[];
extern ItemDropData battle_item_gonbaba[];
extern ItemDropData battle_item_green_chorobon[];
extern ItemDropData battle_item_gundan_zako[];
extern ItemDropData battle_item_gundan_zako_elite[];
extern ItemDropData battle_item_gundan_zako_magician[];
extern ItemDropData battle_item_hammer_bros[];
extern ItemDropData battle_item_hannya[];
extern ItemDropData battle_item_heavy_bom[];
extern ItemDropData battle_item_hennya[];
extern ItemDropData battle_item_hermos[];
extern ItemDropData battle_item_hinnya[];
extern ItemDropData battle_item_honenoko[];
extern ItemDropData battle_item_hyper_jyugem[];
extern ItemDropData battle_item_hyper_kuriboo[];
extern ItemDropData battle_item_hyper_patakuri[];
extern ItemDropData battle_item_hyper_sinemon[];
extern ItemDropData battle_item_hyper_sinnosuke[];
extern ItemDropData battle_item_hyper_togekuri[];
extern ItemDropData battle_item_hyper_togemet[];
extern ItemDropData battle_item_ice_pakkun[];
extern ItemDropData battle_item_iron_sinemon[];
extern ItemDropData battle_item_iron_sinemon2[];
extern ItemDropData battle_item_jyugem[];
extern ItemDropData battle_item_kamec[];
extern ItemDropData battle_item_kanbu1[];
extern ItemDropData battle_item_karon[];
extern ItemDropData battle_item_killer[];
extern ItemDropData battle_item_killer_cannon[];
extern ItemDropData battle_item_kuriboo[];
extern ItemDropData battle_item_kurikuri[];
extern ItemDropData battle_item_kurokumorn[];
extern ItemDropData battle_item_macho_gance[];
extern ItemDropData battle_item_magnum_battender[];
extern ItemDropData battle_item_mahorn[];
extern ItemDropData battle_item_mahorn_custom[];
extern ItemDropData battle_item_met[];
extern ItemDropData battle_item_moamoa[];
extern ItemDropData battle_item_monban[];
extern ItemDropData battle_item_monochrome__pakkun[];
extern ItemDropData battle_item_monochrome_kurokumorn[];
extern ItemDropData battle_item_monochrome_sinemon[];
extern ItemDropData battle_item_nokonoko[];
extern ItemDropData battle_item_nokonoko_fighter[];
extern ItemDropData battle_item_pakkun_flower[];
extern ItemDropData battle_item_pansy[];
extern ItemDropData battle_item_patakuri[];
extern ItemDropData battle_item_patamet[];
extern ItemDropData battle_item_patapata[];
extern ItemDropData battle_item_patapata_fighter[];
extern ItemDropData battle_item_patatogemet[];
extern ItemDropData battle_item_phantom[];
extern ItemDropData battle_item_piders[];
extern ItemDropData battle_item_poison_pakkun[];
extern ItemDropData battle_item_purple_teresa[];
extern ItemDropData battle_item_rampell[];
extern ItemDropData battle_item_red_honenoko[];
extern ItemDropData battle_item_sambo[];
extern ItemDropData battle_item_sambo_mummy[];
extern ItemDropData battle_item_sinemon[];
extern ItemDropData battle_item_sinnosuke[];
extern ItemDropData battle_item_super_killer[];
extern ItemDropData battle_item_super_killer_cannon[];
extern ItemDropData battle_item_super_mahorn[];
extern ItemDropData battle_item_teresa[];
extern ItemDropData battle_item_togedaruma[];
extern ItemDropData battle_item_togekuri[];
extern ItemDropData battle_item_togemet[];
extern ItemDropData battle_item_togenoko[];
extern ItemDropData battle_item_togenoko_ace[];
extern ItemDropData battle_item_togezo[];
extern ItemDropData battle_item_twinkling_pansy[];
extern ItemDropData battle_item_ura_noko[];
extern ItemDropData battle_item_ura_pata[];
extern ItemDropData battle_item_vivian1[];
extern ItemDropData battle_item_wanwan[];
extern ItemDropData battle_item_yami_kuriboo[];
extern ItemDropData battle_item_yami_noko[];
extern ItemDropData battle_item_yami_patakuri[];
extern ItemDropData battle_item_yami_togekuri[];
extern ItemDropData battle_item_yamitogedaruma[];
extern ItemDropData battle_item_zonbaba[];
