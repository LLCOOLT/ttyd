// Declares the battle unit structure, flags and unit control functions.
#pragma once

#include <dolphin/types.h>
#include "version.h"
#include "evt/evt_word.h"
#include "battle/battle_damage.h"
#include "battle/battle_status_effect.h"
#include "battle/battle_status_icon.h"
#include "driver/effdrv.h"
#include "mario/mario_pouch.h"

#define UNIT_ALLIANCE_ENEMY (unit->alliance == 0)
#define UNIT_ALLIANCE_PARTY (unit->alliance == 1)

// BattleUnit.flags (btlevtcmd_OnUnitFlag / OffUnitFlag / CheckUnitFlag).
typedef enum BattleUnit_Flags {
    UNIT_FLAG_SHOW_HP_GAUGE = 0x1,              // HP gauge shown after damage until its timer runs out
    UNIT_FLAG_MOVE_COLOR_CHANGING = 0x2,        // moveColorLvDisp is still moving toward moveColorLv
    UNIT_FLAG_KIND_CHANGED = 0x4,               // the unit changed kind in battle (a winged enemy lost its wings)
    UNIT_FLAG_NOT_ACTIVE_PARTNER = 0x8,         // skipped by BattleGetPartyPtr; nothing in C sets it
    UNIT_FLAG_FUSE_LIT = 0x10,                  // Bulky Bob-omb's fuse is lit (set by its scripts; no C reader)
    UNIT_FLAG_SHARED_SHADOW = 0x10000,          // Vivian's Veil: one shadow between the unit and its partner
    UNIT_FLAG_FLOAT = 0x100000,                 // the unit hovers (floatOffsetControl)
    UNIT_FLAG_FLOAT_ACTIVE = 0x200000,          // the hover bob runs (cleared around jumps and moves)
    UNIT_FLAG_NO_BACKFACE_FLIP = 0x1000000,     // big boss models: no mirror flip when facing away, material light flag 8
    UNIT_FLAG_FORCE_SHOW_ITEM = 0x2000000,      // draw the held item even with UNIT_FLAG_TURN_SKIPPED
    UNIT_FLAG_TURN_SKIPPED = 0x4000000,         // spending this act unable to move; held item hidden
    UNIT_FLAG_HIDE_HELD_ITEM = 0x8000000,       // no held/stolen item sprite (dying, dead)
    UNIT_FLAG_HOLDING_STOLEN_ITEM = 0x40000000, // heldItem was stolen from Mario
    UNIT_FLAG_DELETE_PENDING = 0x80000000,      // killed; BattleCheckUnitBroken deletes it
} BattleUnit_Flags;

// BattleUnit.statusFlags.
typedef enum BattleUnitStatus_Flags {
    STATUS_FLAG_FLIPPED = 0x1,          // a shelled unit (or Koops) is flipped over and can't act
    STATUS_FLAG_DEFENDING = 0x1000000,  // the Defend command: +1 defense this turn
    STATUS_FLAG_EXTRA_MOVE = 0x2000000, // a pending bonus action (Rally Wink)
    STATUS_FLAG_DANGER = 0x10000000,    // HP at or below dangerHP
    STATUS_FLAG_PERIL = 0x20000000,     // HP at or below perilHP
} BattleUnitStatus_Flags;

// BattleUnit.tokenFlags: per-action and per-turn state of a unit.
typedef enum BattleUnitToken_Flags {
    TOKEN_FLAG_WAS_HIT = (1 << 0),           // 0x1, set at the end of BattleDamageDirect; such a unit can't step in to guard
    TOKEN_FLAG_GUARDING = (1 << 1),          // 0x2, this unit stepped in to protect another (its hits get damage flag 0x1000)
    TOKEN_FLAG_GUARD_DECLARED = (1 << 2),    // 0x4, a guard step-in was declared for or by this unit this action
    TOKEN_FLAG_CHARGE_EXPENDED = (1 << 3),   // 0x8, Charge was used up; its status is cleared at the end of the action
    TOKEN_FLAG_CONFUSED_ACTION = (1 << 4),   // 0x10, acting while confused
    TOKEN_FLAG_CURRENTLY_ACTING = (1 << 12), // 0x1000
    TOKEN_FLAG_RALLY_WINK = (1 << 13),       // 0x2000, an extra (Rally Wink) turn while slowed; kept over the turn reset
    TOKEN_FLAG_PERSISTENT = (1 << 31)        // 0x80000000, kept by the turn-start reset; nothing sets it
} BattleUnitToken_Flags;

// BattleUnitPart.attributes. JP and the demo number two bits lower than US/PAL in the 0x10-0x80 range.
typedef enum PartsAttribute_Flags {      // 32-bit size
    PART_ATTR_MAIN = (1 << 0),           // 0x1
    PART_ATTR_IMPORTANT = (1 << 1),      // 0x2
    PART_ATTR_SEMI_IMPORTANT = (1 << 2), // 0x4
    PART_ATTR_GUARD_COVER = (1 << 3),    // 0x8, the part a protecting unit offers when it steps in to guard
#if VERSION >= VERSION_US
    PART_ATTR_NOT_ANY_PART_TARGET = (1 << 4), // 0x10, not a TARGET_CLASS_ANY_PART target (US only)
    PART_ATTR_INTANGIBLE = (1 << 6),          // 0x40, every hit passes through (BattlePreCheckDamage returns 4)
    PART_ATTR_WEAK_TO_ATTACK_FX_R = (1 << 7), // 0x80, defense changed by the unit's work[1] (Hooktail: Attack FX R)
#else
    PART_ATTR_INTANGIBLE = (1 << 4),          // 0x10, every hit passes through (BattlePreCheckDamage returns 4)
    PART_ATTR_WEAK_TO_ATTACK_FX_R = (1 << 5), // 0x20, defense changed by the unit's work[1] (Hooktail: Attack FX R)
#endif
    PART_ATTR_WEAK_TO_ICE_POWER = (1 << 8),             // 0x100
    PART_ATTR_WINGED = (1 << 11),                       // 0x800
    PART_ATTR_SHELLED = (1 << 12),                      // 0x1000
    PART_ATTR_BOMB_FLIPPABLE = (1 << 13),               // 0x2000
    PART_ATTR_EVASIVE = (1 << 14),                      // 0x4000, always dodges unless the weapon has SPECIAL_HITS_EVASIVE_PARTS
    PART_ATTR_NO_TRANSLUCENT_POSE = (1 << 15),          // 0x8000, Dodgy/Invisible don't make it translucent
    PART_ATTR_NOT_TARGETABLE = (1 << 16),               // 0x10000
    PART_ATTR_NO_TARGET_SORT_OFFSET = (1 << 17),        // 0x20000, exempt from the unit's UNIT_ATTR_TARGET_SORT_OFFSET
    PART_ATTR_NOT_PART_TARGET = (1 << 18),              // 0x40000, not a TARGET_CLASS_MAIN_PARTS or ANY_PART target
    PART_ATTR_UNTATTLEABLE = (1 << 19),                 // 0x80000
    PART_ATTR_JUMPLIKE_CANNOT_TARGET = (1 << 20),       // 0x100000
    PART_ATTR_HAMMERLIKE_CANNOT_TARGET = (1 << 21),     // 0x200000
    PART_ATTR_SHELL_TOSSLIKE_CANNOT_TARGET = (1 << 22), // 0x400000
    PART_ATTR_NO_HP_LOSS = (1 << 23),                   // 0x800000, damage doesn't lower HP
    PART_ATTR_HIDDEN = (1 << 24),                       // 0x1000000, not drawn
    PART_ATTR_NO_SHADOW = (1 << 25),                    // 0x2000000, no shadow
    PART_ATTR_BLUR = (1 << 26),                         // 0x4000000, drawn with afterimages
    PART_ATTR_IGNORE_UNIT_SCALE = (1 << 27),            // 0x8000000, a world-position part ignores the unit's size
    PART_ATTR_WORLD_POSITION = (1 << 28),               // 0x10000000, position is absolute, not relative to the unit
    PART_ATTR_IMMUNE_TO_DAMAGE_OR_STATUS = (1 << 29),   // 0x20000000, no HP, FP or status damage
    PART_ATTR_IMMUNE_TO_MOST_STATUS = (1 << 30),        // 0x40000000, blocks most status types (BattleSetStatusDamage)
    PART_ATTR_IMMUNE_TO_STATUS = (1 << 31)              // 0x80000000, blocks every status
} PartsAttribute_Flags;

// BattleUnit.attributeFlags.
typedef enum BattleUnitAttribute_Flags {        // 32-bit size
    UNIT_ATTR_TARGET_SORT_OFFSET = (1 << 0),    // 0x1, target order shifted by direction * 300 (switches, trees)
    UNIT_ATTR_CEILING = (1 << 1),               // 0x2
    UNIT_ATTR_FLOATING = (1 << 2),              // 0x4
    UNIT_ATTR_INTANGIBLE = (1 << 3),            // 0x8, hits pass through and the unit is drawn at half alpha
    UNIT_ATTR_VEILED = (1 << 4),                // 0x10
    UNIT_ATTR_SHELL_SHIELDED = (1 << 5),        // 0x20
    UNIT_ATTR_NOT_SAMPLED_AS_TARGET = (1 << 6), // 0x40, skipped when building target lists
    UNIT_ATTR_NO_LAST_HIT_RESULT = (1 << 8),    // 0x100, suppresses damage result bit 0x10000 (see SPECIAL_FORCE_RESULT_10000)
    UNIT_ATTR_NO_GRAVITY_BOB = (1 << 12),       // 0x1000, no zero-gravity bobbing
    UNIT_ATTR_ACTS_IN_ZERO_GRAVITY = (1 << 13), // 0x2000, may still act in zero gravity
    UNIT_ATTR_NO_HAMMER_KNOCKBACK = (1 << 14),  // 0x4000, hammer knockback damage patterns 0xE and 0x10 become 0
    UNIT_ATTR_REVIVES_AFTER_KO = (1 << 16),     // 0x10000, keeps taking turns while KO'd (Dry Bones)
    UNIT_ATTR_INACTIVE = (1 << 17),             // 0x20000
    UNIT_ATTR_REQUIRED_FOR_CLEAR = (1 << 18),   // 0x40000, the battle is won when no living unit has this
    UNIT_ATTR_NO_TURN = (1 << 19),              // 0x80000, never in the phase move queue
    UNIT_ATTR_NO_KNOCKBACK_POSE = (1 << 21),    // 0x200000, damage patterns 0x15-0x18 become 0
    UNIT_ATTR_NO_DAMAGE_NUMBER = (1 << 22),     // 0x400000, no damage-star number
    UNIT_ATTR_HIDDEN = (1 << 24),               // 0x1000000, body not drawn
    UNIT_ATTR_NO_HP_GAUGE = (1 << 25),          // 0x2000000, no enemy HP gauge
    UNIT_ATTR_BILLBOARD = (1 << 26),            // 0x4000000, parts face the camera
    UNIT_ATTR_IGNORE_FOR_CLEAR = (1 << 28),     // 0x10000000, not counted by the battle-clear checks
    UNIT_ATTR_NO_SHADOW = (1 << 29),            // 0x20000000
    UNIT_ATTR_HP_LOCKED = (1 << 30)             // 0x40000000, HP unchanged by damage, regeneration and healing
} BattleUnitAttribute_Flags;

typedef enum PartsCounterAttribute_Flags {          // 32-bit size
    COUNTER_ATTR_TOP_SPIKY = (1 << 0),              // 0x1
    COUNTER_ATTR_PREEMPTIVE_FRONT_SPIKY = (1 << 1), // 0x2
    COUNTER_ATTR_FRONT_SPIKY = (1 << 2),            // 0x4
    COUNTER_ATTR_FIERY = (1 << 4),                  // 0x10
    COUNTER_ATTR_FIERY_STATUS = (1 << 5),           // 0x20
    COUNTER_ATTR_ICY = (1 << 6),                    // 0x40
    COUNTER_ATTR_ICY_STATUS = (1 << 7),             // 0x80
    COUNTER_ATTR_POISON = (1 << 8),                 // 0x100
    COUNTER_ATTR_POISON_STATUS = (1 << 9),          // 0x200
    COUNTER_ATTR_ELECTRIC = (1 << 10),              // 0x400
    COUNTER_ATTR_ELECTRIC_STATUS = (1 << 11),       // 0x800
    COUNTER_ATTR_EXPLOSIVE = (1 << 12),             // 0x1000
    COUNTER_ATTR_VOLATILE_EXPLOSIVE = (1 << 13)     // 0x2000
} PartsCounterAttribute_Flags;

typedef enum BattleUnitType {
    UNIT_NULL,                            // 0x0
    UNIT_GOOMBA,                          // 0x1
    UNIT_PARAGOOMBA,                      // 0x2
    UNIT_SPIKY_GOOMBA,                    // 0x3
    UNIT_SPINIA,                          // 0x4
    UNIT_SPANIA,                          // 0x5
    UNIT_LORD_CRUMP_PROLOGUE,             // 0x6
    UNIT_GUS,                             // 0x7
    UNIT_BLOOPER,                         // 0x8
    UNIT_BLOOPER_LEFT_TENTACLE,           // 0x9
    UNIT_BLOOPER_RIGHT_TENTACLE,          // 0xA
    UNIT_KOOPATROL,                       // 0xB
    UNIT_MAGIKOOPA,                       // 0xC
    UNIT_MAGIKOOPA_CLONE,                 // 0xD
    UNIT_KOOPA_TROOPA,                    // 0xE
    UNIT_PARATROOPA,                      // 0xF
    UNIT_FUZZY,                           // 0x10
    UNIT_DULL_BONES,                      // 0x11
    UNIT_BALD_CLEFT,                      // 0x12
    UNIT_BRISTLE,                         // 0x13
    UNIT_GOLD_FUZZY,                      // 0x14
    UNIT_FUZZY_HORDE,                     // 0x15
    UNIT_RED_BONES,                       // 0x16
    UNIT_HOOKTAIL,                        // 0x17
    UNIT_DARK_PUFF,                       // 0x18
    UNIT_PALE_PIRANHA,                    // 0x19
    UNIT_CLEFT,                           // 0x1A
    UNIT_PIDER,                           // 0x1B
    UNIT_X_NAUT,                          // 0x1C
    UNIT_YUX,                             // 0x1D
    UNIT_MINI_YUX,                        // 0x1E
    UNIT_BELDAM_CHAPTER2,                 // 0x1F
    UNIT_MARILYN_CHAPTER2,                // 0x20
    UNIT_VIVIAN_CHAPTER2,                 // 0x21
    UNIT_MAGNUS,                          // 0x22
    UNIT_X_FIST,                          // 0x23
    UNIT_GOOMBA_GLITZVILLE,               // 0x24
    UNIT_KP_KOOPA,                        // 0x25
    UNIT_KP_PARATROOPA,                   // 0x26
    UNIT_POKEY,                           // 0x27
    UNIT_LAKITU,                          // 0x28
    UNIT_SPINY,                           // 0x29
    UNIT_HYPER_BALD_CLEFT,                // 0x2A
    UNIT_BOB_OMB,                         // 0x2B
    UNIT_BANDIT,                          // 0x2C
    UNIT_BIG_BANDIT,                      // 0x2D
    UNIT_RED_SPIKY_BUZZY,                 // 0x2E
    UNIT_SHADY_KOOPA,                     // 0x2F
    UNIT_SHADY_PARATROOPA,                // 0x30
    UNIT_RED_MAGIKOOPA,                   // 0x31
    UNIT_RED_MAGIKOOPA_CLONE,             // 0x32
    UNIT_WHITE_MAGIKOOPA,                 // 0x33
    UNIT_WHITE_MAGIKOOPA_CLONE,           // 0x34
    UNIT_GREEN_MAGIKOOPA,                 // 0x35
    UNIT_GREEN_MAGIKOOPA_CLONE,           // 0x36
    UNIT_DARK_CRAW,                       // 0x37
    UNIT_HAMMER_BRO,                      // 0x38
    UNIT_BOOMERANG_BRO,                   // 0x39
    UNIT_FIRE_BRO,                        // 0x3A
    UNIT_RED_CHOMP,                       // 0x3B
    UNIT_DARK_KOOPATROL,                  // 0x3C
    UNIT_IRON_CLEFT_RED,                  // 0x3D
    UNIT_IRON_CLEFT_GREEN,                // 0x3E
    UNIT_BOWSER_CHAPTER3,                 // 0x3F
    UNIT_RAWK_HAWK,                       // 0x40
    UNIT_MACHO_GRUBBA,                    // 0x41
    UNIT_HYPER_GOOMBA,                    // 0x42
    UNIT_HYPER_PARAGOOMBA,                // 0x43
    UNIT_HYPER_SPIKY_GOOMBA,              // 0x44
    UNIT_CRAZEE_DAYZEE,                   // 0x45
    UNIT_AMAZY_DAYZEE,                    // 0x46
    UNIT_HYPER_CLEFT,                     // 0x47
    UNIT_BUZZY_BEETLE,                    // 0x48
    UNIT_SPIKE_TOP,                       // 0x49
    UNIT_SWOOPER,                         // 0x4A
    UNIT_BOO,                             // 0x4B
    UNIT_ATOMIC_BOO,                      // 0x4C
    UNIT_DOOPLISS_CHAPTER4_FIGHT1,        // 0x4D
    UNIT_DOOPLISS_CHAPTER4_INVINCIBLE,    // 0x4E
    UNIT_DOOPLISS_CHAPTER4_FIGHT2,        // 0x4F
    UNIT_GOOMBELLA_CHAPTER4,              // 0x50
    UNIT_KOOPS_CHAPTER4,                  // 0x51
    UNIT_YOSHI_CHAPTER4,                  // 0x52
    UNIT_FLURRIE_CHAPTER4,                // 0x53
    UNIT_EMBER,                           // 0x54
    UNIT_LAVA_BUBBLE,                     // 0x55
    UNIT_GREEN_FUZZY,                     // 0x56
    UNIT_FLOWER_FUZZY,                    // 0x57
    UNIT_PUTRID_PIRANHA,                  // 0x58
    UNIT_PARABUZZY,                       // 0x59
    UNIT_BILL_BLASTER,                    // 0x5A
    UNIT_BULLET_BILL,                     // 0x5B
    UNIT_BULKY_BOB_OMB,                   // 0x5C
    UNIT_CORTEZ,                          // 0x5D
    UNIT_CORTEZ_BONE_PILE,                // 0x5E
    UNIT_CORTEZ_SWORD,                    // 0x5F
    UNIT_CORTEZ_HOOK,                     // 0x60
    UNIT_CORTEZ_RAPIER,                   // 0x61
    UNIT_CORTEZ_SABER,                    // 0x62
    UNIT_LORD_CRUMP_CHAPTER5,             // 0x63
    UNIT_X_NAUTS_CRUMP_FORMATION1,        // 0x64
    UNIT_X_NAUTS_CRUMP_FORMATION2,        // 0x65
    UNIT_X_NAUTS_CRUMP_FORMATION3,        // 0x66
    UNIT_RUFF_PUFF,                       // 0x67
    UNIT_POISON_POKEY,                    // 0x68
    UNIT_SPIKY_PARABUZZY,                 // 0x69
    UNIT_DARK_BOO,                        // 0x6A
    UNIT_SMORG,                           // 0x6B
    UNIT_SMORG_MIASMA_TENTACLE_A,         // 0x6C
    UNIT_SMORG_MIASMA_TENTACLE_B,         // 0x6D
    UNIT_SMORG_MIASMA_TENTACLE_C,         // 0x6E
    UNIT_SMORG_MIASMA_CLAW,               // 0x6F
    UNIT_ICE_PUFF,                        // 0x70
    UNIT_FROST_PIRANHA,                   // 0x71
    UNIT_MOON_CLEFT,                      // 0x72
    UNIT_Z_YUX,                           // 0x73
    UNIT_MINI_Z_YUX,                      // 0x74
    UNIT_X_YUX,                           // 0x75
    UNIT_MINI_X_YUX,                      // 0x76
    UNIT_X_NAUT_PHD,                      // 0x77
    UNIT_ELITE_X_NAUT,                    // 0x78
    UNIT_MAGNUS2_0,                       // 0x79
    UNIT_X_PUNCH,                         // 0x7A
    UNIT_SWOOPULA,                        // 0x7B
    UNIT_PHANTOM_EMBER,                   // 0x7C
    UNIT_BOMBSHELL_BILL_BLASTER,          // 0x7D
    UNIT_BOMBSHELL_BILL,                  // 0x7E
    UNIT_CHAIN_CHOMP,                     // 0x7F
    UNIT_DARK_WIZZERD,                    // 0x80
    UNIT_DARK_WIZZERD_CLONE,              // 0x81
    UNIT_DRY_BONES,                       // 0x82
    UNIT_DARK_BONES,                      // 0x83
    UNIT_GLOOMTAIL,                       // 0x84
    UNIT_BELDAM_CHAPTER8,                 // 0x85
    UNIT_MARILYN_CHAPTER8,                // 0x86
    UNIT_DOOPLISS_CHAPTER8,               // 0x87
    UNIT_DOOPLISS_CHAPTER8_MARIO,         // 0x88
    UNIT_DOOPLISS_CHAPTER8_GOOMBELLA,     // 0x89
    UNIT_DOOPLISS_CHAPTER8_KOOPS,         // 0x8A
    UNIT_DOOPLISS_CHAPTER8_YOSHI,         // 0x8B
    UNIT_DOOPLISS_CHAPTER8_FLURRIE,       // 0x8C
    UNIT_DOOPLISS_CHAPTER8_VIVIAN,        // 0x8D
    UNIT_DOOPLISS_CHAPTER8_BOBBERY,       // 0x8E
    UNIT_DOOPLISS_CHAPTER8_MS_MOWZ,       // 0x8F
    UNIT_BOWSER_CHAPTER8,                 // 0x90
    UNIT_KAMMY_KOOPA,                     // 0x91
    UNIT_GRODUS,                          // 0x92
    UNIT_GRODUS_X,                        // 0x93
    UNIT_SHADOW_QUEEN_PEACH,              // 0x94
    UNIT_SHADOW_QUEEN_INVINCIBLE,         // 0x95
    UNIT_SHADOW_QUEEN_DEMON,              // 0x96
    UNIT_SHADOW_QUEEN_LEFT_RIGHT_HAND,    // 0x97
    UNIT_SHADOW_QUEEN_DEAD_HANDS,         // 0x98
    UNIT_GLOOMBA,                         // 0x99
    UNIT_PARAGLOOMBA,                     // 0x9A
    UNIT_SPIKY_GLOOMBA,                   // 0x9B
    UNIT_DARK_KOOPA,                      // 0x9C
    UNIT_DARK_PARATROOPA,                 // 0x9D
    UNIT_BADGE_BANDIT,                    // 0x9E
    UNIT_DARK_LAKITU,                     // 0x9F
    UNIT_SKY_BLUE_SPINY,                  // 0xA0
    UNIT_WIZZERD,                         // 0xA1
    UNIT_PIRANHA_PLANT,                   // 0xA2
    UNIT_SPUNIA,                          // 0xA3
    UNIT_ARANTULA,                        // 0xA4
    UNIT_DARK_BRISTLE,                    // 0xA5
    UNIT_POISON_PUFF,                     // 0xA6
    UNIT_SWAMPIRE,                        // 0xA7
    UNIT_BOB_ULK,                         // 0xA8
    UNIT_ELITE_WIZZERD,                   // 0xA9
    UNIT_ELITE_WIZZERD_CLONE,             // 0xAA
    UNIT_BONETAIL,                        // 0xAB
    UNIT_UNUSED_RED_BUZZY,                // 0xAC
    UNIT_UNUSED_RED_PARABUZZY,            // 0xAD
    UNIT_UNUSED_RED_SPIKY_PARABUZZY,      // 0xAE
    UNIT_UNUSED_HYPER_BOB_OMB,            // 0xAF
    UNIT_UNUSED_ULTRA_BOB_OMB,            // 0xB0
    UNIT_TUTORIAL_GOOMBELLA,              // 0xB1
    UNIT_TUTORIAL_FRANKLY_B2,             // 0xB2
    UNIT_TUTORIAL_FRANKLY_B3,             // 0xB3
    UNIT_TUTORIAL_FRANKLY_B4,             // 0xB4
    UNIT_EPILOGUE_DOOPLISS_MARIO,         // 0xB5
    UNIT_EPILOGUE_FLURRIE,                // 0xB6
    UNIT_EPILOGUE_BOO,                    // 0xB7
    UNIT_EPILOGUE_ATOMIC_BOO,             // 0xB8
    UNIT_EPILOGUE_MALE_TOAD,              // 0xB9
    UNIT_EPILOGUE_FEMALE_TOAD,            // 0xBA
    UNIT_UNUSED_TEST,                     // 0xBB
    UNIT_UNUSED_CRUMP2,                   // 0xBC
    UNIT_UNUSED_BELDAM2,                  // 0xBD
    UNIT_UNUSED_MARILYN2,                 // 0xBE
    UNIT_UNUSED_VIVIAN2,                  // 0xBF
    UNIT_UNUSED_BELDAM3,                  // 0xC0
    UNIT_UNUSED_MARILYN3,                 // 0xC1
    UNIT_UNUSED_MECHA_KURI,               // 0xC2
    UNIT_UNUSED_MECHA_KAME,               // 0xC3
    UNIT_UNUSED_OKORL,                    // 0xC4
    UNIT_UNUSED_YOWARL,                   // 0xC5
    UNIT_UNUSED_TUYONARL,                 // 0xC6
    UNIT_UNUSED_WANAWANA,                 // 0xC7
    UNIT_UNUSED_MINARAI_KAMEC,            // 0xC8
    UNIT_UNUSED_SHY_GUY,                  // 0xC9
    UNIT_UNUSED_GROOVE_GUY,               // 0xCA
    UNIT_UNUSED_PYRO_GUY,                 // 0xCB
    UNIT_UNUSED_SPY_GUY,                  // 0xCC
    UNIT_UNUSED_ANTI_GUY,                 // 0xCD
    UNIT_UNUSED_BZZAP,                    // 0xCE
    UNIT_UNUSED_MINI_BZZAP,               // 0xCF
    UNIT_UNUSED_UFO,                      // 0xD0
    UNIT_UNUSED_PENNINGTON,               // 0xD1
    UNIT_UNUSED_FIGHTER,                  // 0xD2
    UNIT_UNUSED_ZESS_T,                   // 0xD3
    UNIT_UNUSED_MASTER,                   // 0xD4
    UNIT_UNUSED_REPORTER,                 // 0xD5
    UNIT_UNUSED_HOTDOG_MASTER,            // 0xD6
    UNIT_UNUSED_FLAVIO,                   // 0xD7
    UNIT_UNUSED_TREE,                     // 0xD8
    UNIT_UNUSED_SWITCH,                   // 0xD9
    UNIT_UNUSED_TESTNPC,                  // 0xDA
    UNIT_BOMB_SQUAD_BOMB,                 // 0xDB
    UNIT_SYSTEM,                          // 0xDC
    UNIT_PROLOGUE_GOOMBELLA,              // 0xDD
    UNIT_MARIO,                           // 0xDE
    UNIT_SHELL_SHIELD,                    // 0xDF
    UNIT_GOOMBELLA,                       // 0xE0
#define TYPE_PARTNER_MIN UNIT_GOOMBELLA   // 0xE0
    UNIT_KOOPS,                           // 0xE1
    UNIT_YOSHI,                           // 0xE2
    UNIT_FLURRIE,                         // 0xE3
    UNIT_VIVIAN,                          // 0xE4
    UNIT_BOBBERY,                         // 0xE5
    UNIT_MS_MOWZ,                         // 0xE6
#define TYPE_PARTNER_MAX UNIT_MS_MOWZ + 1 // 0xE7
    UNIT_MAX,                             // 0xE7
} BattleUnitType;

typedef struct BattleDataEntry {
    s32 tag;    // 0x0, lookup key for BtlUnit_GetData, 0 ends the table
    void* data; // 0x4
} BattleDataEntry;

typedef struct BattleUnitDefense {
    s8 defenses[5]; // 0x0
} BattleUnitDefense;

typedef struct BattleUnitDefenseAttr {
    s8 defenseAttrs[5]; // 0x0
} BattleUnitDefenseAttr;

typedef struct StatusVulnerability {
    u8 sleep;       // 0x0
    u8 stop;        // 0x1
    u8 dizzy;       // 0x2
    u8 poison;      // 0x3
    u8 confuse;     // 0x4
    u8 electric;    // 0x5
    u8 burn;        // 0x6
    u8 freeze;      // 0x7
    u8 huge;        // 0x8
    u8 tiny;        // 0x9
    u8 attackUp;    // 0xA
    u8 attackDown;  // 0xB
    u8 defenseUp;   // 0xC
    u8 defenseDown; // 0xD
    u8 allergic;    // 0xE
    u8 fright;      // 0xF
    u8 galeForce;   // 0x10
    u8 fast;        // 0x11
    u8 slow;        // 0x12
    u8 dodgy;       // 0x13
    u8 invisible;   // 0x14
    u8 ohko;        // 0x15
} StatusVulnerability;

typedef struct PoseTableEntry {
    s32 poseType;         // 0x0
    const char* poseName; // 0x4
} PoseTableEntry;

// PoseTableEntry.poseType. A table is scanned in order for the requested type or its group's fallback (the first
// match wins), up to the first entry >= BTL_POSE_MAX: status poses up to 28 fall back to BTL_POSE_NORMAL, hurt
// poses 29-39 to BTL_POSE_DAMAGE, action poses 40-69 to BTL_POSE_STAY_DEFAULT (BtlUnit_GetPoseNameFromType).
// Types up to 28 are StatusEffectType ids. Retail added two poses at 58 and 59 (kissed by Goombella's and
// Ms. Mowz's kiss moves), so every pose from 60 up is 2 lower in the demo.
typedef enum BattlePoseType {
    BTL_POSE_NORMAL = 28, // no status; fallback for the status poses
    BTL_POSE_DAMAGE = 39, // generic hurt; fallback for 29-39
    BTL_POSE_WALK = 40,
    BTL_POSE_RUN = 42,
    BTL_POSE_STAY = 43,     // unit->stayPose
    BTL_POSE_DEFEND = 45,   // the Defend command
    BTL_POSE_ITEM_USE = 52, // holding up an item
    BTL_POSE_DANGER = 56,   // low HP (status flag 0x10000000)
    BTL_POSE_PERIL = 57,    // very low HP (status flag 0x20000000)
#if VERSION <= VERSION_DEMO_US
    BTL_POSE_ESCAPE_FAIL = 58, // failed Run Away: tumble
#else
    BTL_POSE_KISSED_CHRISTINE = 58, // target of Goombella's kiss move
    BTL_POSE_KISSED_CHUCHURINA,     // target of Ms. Mowz's kiss move
    BTL_POSE_ESCAPE_FAIL,           // failed Run Away: tumble
#endif
    BTL_POSE_ESCAPE_FAIL_END, // failed Run Away: aftermath
    BTL_POSE_HAPPY_HEART,     // Happy Heart restores HP
    BTL_POSE_HAPPY_FLOWER,    // Happy Flower restores FP
    BTL_POSE_ZERO_GRAVITY,    // can't move in zero gravity
    BTL_POSE_TALK,            // unit->talkPose
    BTL_POSE_APPEAL,          // appealing to the audience
    BTL_POSE_COMMAND_WAIT,    // waiting at the command menu
    BTL_POSE_SHELL_SHIELD,    // Koops' shell shield (unit_koura)
    BTL_POSE_STAY_DEFAULT,    // standing; fallback for the action poses
    BTL_POSE_MAX,             // end of the pose type range
} BattlePoseType;

// BattleUnitPart.animFlags (battle_disp.c; scripts set them through btlevtcmd_AnimeFlagOnOff).
typedef enum BattlePartAnimFlags {
    PART_ANIM_CHANGE = 0x1,        // pose change pending: btlDispMain starts the new pose next frame
    PART_ANIM_MANUAL_POSE = 0x2,   // the pose was set by name (btlDispChangeAnime), not picked from the pose table
    PART_ANIM_PERA = 0x4,          // a paper effect animation runs (btlDispChangePeraAnime): no translucency change
    PART_ANIM_HURT_POSE = 0x8,     // a hurt pose (29-39) set by name: still gets the status draw type
    PART_ANIM_BLACKEN = 0x10,      // drawn black (hurt poses 29 and 30)
    PART_ANIM_BLACKEN_EVT = 0x20,  // drawn black, set by scripts
    PART_ANIM_XLU = 0x40,          // the pose is drawn translucent
    PART_ANIM_COMMAND_WAIT = 0x80, // the command-wait pose (BtlUnit_SetCommandAnimPose): still gets the status draw type
    PART_ANIM_NO_DISP = 0x100,     // not drawn (Ms. Mowz's screen copy, set by scripts)
    PART_ANIM_RESTART = 0x200,     // set by scripts; see the BUG note in btlDispMain
} BattlePartAnimFlags;

// BattleUnit.attackEventFlags: how battle_seq's act step runs the unit's attackEventCode (set by the command menu).
typedef enum BattleAttackEventFlags {
    ATTACK_EVENT_KEEP_STATUS_WINDOW = 0x1, // the status window stays up during the act
    ATTACK_EVENT_IGNORE_STATUS = 0x2,      // runs even when sleep, stop, freeze or KO would block the act
    ATTACK_EVENT_SHELL_FOLLOWS = 0x4,      // a Shell Shield in front keeps tracking the unit while the event runs
    ATTACK_EVENT_ZERO_GRAVITY_OK = 0x8,    // allowed in zero gravity
    ATTACK_EVENT_ALWAYS_RUN = 0x10,        // runs whatever the status or gravity (nothing if there is no event)
} BattleAttackEventFlags;

typedef struct BattleUnitKindPart {
    s32 partNum;                                   // 0x0
    const char* partName;                          // 0x4
    const char* modelName;                         // 0x8
    Vec positionOffset;                            // 0xC
    Vec hitBaseOffset;                             // 0x18
    Vec hitCursorBaseOffset;                       // 0x24
    s16 shadowSize;                                // 0x30, -> BattleUnitPart.shadowSize
    s16 hitHeight;                                 // 0x32, -> BattleUnitPart.hitHeight
    s16 baseAlpha;                                 // 0x34
    BattleUnitDefense* defense;                    // 0x38
    BattleUnitDefenseAttr* defenseAttr;            // 0x3C
    PartsAttribute_Flags attributes;               // 0x40
    PartsCounterAttribute_Flags counterAttributes; // 0x44
    PoseTableEntry* poseTable;                     // 0x48
} BattleUnitKindPart;

// movement sound loop state (BtlUnit_SetSeMode / _MoveSoundControlCore)
typedef struct BecSndWork {
    const char* name0; // 0x0
    const char* name1; // 0x4
    s16 reserved_08;   // 0x8, BtlUnit_SetSeMode arg a
    s16 reserved_0A;   // 0xA, BtlUnit_SetSeMode arg b
    s16 delay;         // 0xC, start delay
    s16 period0;       // 0xE
    s16 period1;       // 0x10
    s16 timer;         // 0x12
    s16 count;         // 0x14
    s32 sfxId;         // 0x18
} BecSndWork;

// one movement sound set (BtlUnit_LoadSeMode)
typedef struct BtlPoseSoundEntry {
    const char* name0;
    const char* name1;
    s16 delay;   // start delay frames
    s16 period0; // frames between name0 plays
    s16 period1; // frames between name1 plays
} BtlPoseSoundEntry;

typedef struct BtlPoseSoundTable {
    const char* jumpName0;      // 0x0, mode 2: jump start
    const char* jumpName1;      // 0x4, mode 2/3: landing
    BtlPoseSoundEntry entry[3]; // 0x8, mode 0 run, 1 walk, 4 dive (btlevtcmd_Set*RunSound/WalkSound/DiveSound)
} BtlPoseSoundTable;

// pose-synced sound playback (BtlUnit_PoseSoundMain)
typedef struct BtlPoseSoundData {
    const char* animName;                                                 // 0x0
    f32 time;                                                             // 0x4
    s32 (*callback)(struct BattleUnit*, struct BtlPoseSoundData*, void*); // 0x8
    const char* sfxName;                                                  // 0xC
    s16 pitch;                                                            // 0x10
    u16 flags;                                                            // 0x12
} BtlPoseSoundData;

typedef struct BtlPartPoseSound {
    BtlPoseSoundData* table; // 0x0
    u32 loopCount;           // 0x4
    f32 time;                // 0x8
    f32 prevTime;            // 0xC
    s32 count;               // 0x10
    u8 flag;                 // 0x14
} BtlPartPoseSound;

typedef struct BattleWorkUnitPartBlurEntry {
    s32 flags;            // 0x0
    Mtx orientation;      // 0x4
    f32 rotation;         // 0x34
    GXColor base;         // 0x38
    GXColor blurColor[2]; // 0x3C, newest / oldest after-image tint (copied from BattleWorkUnitPartBlur.color)
} BattleWorkUnitPartBlurEntry;

typedef struct BattleWorkUnitPartBlur {
    s32 flags;                            // 0x0
    GXColor color[2];                     // 0x4, after-image tint, newest / oldest (btlevtcmd_SetPartsBlur)
    BattleWorkUnitPartBlurEntry work[10]; // 0xC
} BattleWorkUnitPartBlur;

typedef struct BattleUnitPart {
    struct BattleUnitPart* nextPart;    // 0x0
    BattleUnitKindPart* kindPartParams; // 0x4
    const char* partName;               // 0x8
    Vec homePosition;                   // 0xC
    Vec position;                       // 0x18
    Vec positionOffset;                 // 0x24
    Vec displayOffset;                  // 0x30
    Vec baseRotation;                   // 0x3C
    Vec rotation;                       // 0x48
    Vec rotationOffset;                 // 0x54
    Vec scale;                          // 0x60
    Vec baseScale;                      // 0x6C
    f32 shadowScale;                    // 0x78, extra shadow size multiplier
    Vec moveStartPos;                   // 0x7C
    Vec moveCurrentPos;                 // 0x88
    Vec moveTargetPos;                  // 0x94
    s32 moveTotalFrames;                // 0xA0, frame count of the current parts move/jump
    f32 moveSpeedXZ;                    // 0xA4
    f32 fallAccel;                      // 0xA8
    f32 moveSpeedY;                     // 0xAC, jump vertical speed, minus fallAccel per frame
    f32 moveAngle;                      // 0xB0, XZ angle to the move target
    f32 moveDistance;                   // 0xB4, XZ distance to the move target (then the per-frame remainder)
    f32 moveFrame;                      // 0xB8, current frame of an interpolated parts move
    s8 moveDirection;                   // 0xBC
    s8 faceDirection;                   // 0xBD
    BecSndWork moveSnd;                 // 0xC0, move-sound loop (BtlUnit_LoadSeMode / _MoveSoundControlCore)
    u8 reserved_DC[0xF8 - 0xDC];        // 0xDC, never accessed
    BtlPoseSoundTable moveSndTable;     // 0xF8, btlevtcmd_SetPartsJump/Run/Walk/DiveSound
    union {
        EvtWord work[16];  // 0x130, part work words (btlevtcmd_SetPartsWork / GetPartsWork): numbers and table pointers
        void* workPtr[16]; // 0x130, the same words when they hold a pointer
    };
    Vec hitBaseOffset;                                 // 0x170, guess
    Vec hitOffset;                                     // 0x17C
    Vec hitCursorBaseOffset;                           // 0x188, guess
    Vec hitCursorOffset;                               // 0x194
    s16 hitOffsetX;                                    // 0x1A0, target-cursor X offset (btl_hitoffsetx)
    s16 shadowSize;                                    // 0x1A2, from kind part 0x30; scales shadowEntry
    s16 hitHeight;                                     // 0x1A4, copied from BattleUnitKindPart.hitHeight; height of the part's box (shadowSize wide) in PAL battle_ufo, its only reader
    u16 gravityTimer;                                  // 0x1A6, frame counter for the gravity bob offset
    u16 floatTimer;                                    // 0x1A8, frame counter for the floating offset
    PartsAttribute_Flags attributes;                   // 0x1AC
    PartsCounterAttribute_Flags counterAttributes;     // 0x1B0
    BattleUnitDefense* defense;                        // 0x1B4
    BattleUnitDefenseAttr* defenseAttr;                // 0x1B8
    PoseTableEntry* poseTable;                         // 0x1BC
    s32 poseId;                                        // 0x1C0
    char poseName[0x40];                               // 0x1C4, current pose name (strcmp'd in unit scripts)
    u32 animFlags;                                     // 0x204, BattlePartAnimFlags
    f32 animSpeed;                                     // 0x208, init 1.0
    f32 animSpeed2;                                    // 0x20C, init 1.0
    void (*dispCallback)(struct BattleUnitPart*, s32); // 0x210, called before (0) and after (1) drawing
    u8 poseState;                                      // 0x214
    u8 poseType;                                       // 0x215
    u16 poseTimer;                                     // 0x216
    GXColor drawColor;                                 // 0x218, material colour set per frame from dispColor
    BattleWorkUnitPartBlur blurWork;                   // 0x21C
    BtlPartPoseSound poseSound;                        // 0x4D0, btlevtcmd_AnimeSetPoseSoundTable
    s32 handle;                                        // 0x4E8, -1 at entry, reset to -1 on unit delete; never set otherwise in C
    struct BattleUnit* owner;                          // 0x4EC
    GXColor color;                                     // 0x4F0
    GXColor dispColor;                                 // 0x4F4, color with alpha = baseAlpha * color.a
    f32 dispZOffset;                                   // 0x4F8, added to z for the display sort
    s8 rotationOrder;                                  // 0x4FC, selects the rotation matrix concat order
} BattleUnitPart;

typedef struct BattleWorkUnitBadgesEquipped {
    u8 CloseCall;     // 0x0
    u8 PrettyLucky;   // 0x1
    u8 LuckyDay;      // 0x2
    u8 reserved_03;   // 0x3, badge count slot 3, never read
    u8 PowerPlus;     // 0x4
    u8 PUpDDown;      // 0x5
    u8 AllOrNothing;  // 0x6
    u8 MegaRush;      // 0x7
    u8 PowerRush;     // 0x8
    u8 PDownDUp;      // 0x9
    u8 DoublePain;    // 0xA
    u8 LastStand;     // 0xB
    u8 DefendPlus;    // 0xC
    u8 DamageDodge;   // 0xD
    u8 HappyHeart;    // 0xE
    u8 HappyFlower;   // 0xF
    u8 ReturnPostage; // 0x10
    u8 HpPlus;        // 0x11
    u8 FpPlus;        // 0x12
    u8 DoubleDip;     // 0x13
    u8 TripleDip;     // 0x14
    u8 FlowerSaver;   // 0x15
    u8 FeelingFine;   // 0x16
    u8 ZapTap;        // 0x17
    u8 PityFlower;    // 0x18
    u8 HpDrain;       // 0x19
    u8 FpDrain;       // 0x1A
    u8 Refund;        // 0x1B
    u8 Charge;        // 0x1C
    u8 SuperCharge;   // 0x1D
    u8 DefendUnused;  // 0x1E
    u8 Jumpman;       // 0x1F
    u8 Hammerman;     // 0x20
    u8 IcePower;      // 0x21
    u8 SpikeShield;   // 0x22
    u8 SuperAppeal;   // 0x23
    u8 LuckyStart;    // 0x24
    u8 Simplifier;    // 0x25
    u8 Unsimplifier;  // 0x26
    u8 AutoCommand;   // 0x27
} BattleWorkUnitBadgesEquipped;

// BattleWorkHpGauge.flags
enum BattleHpGaugeFlags {
    HP_GAUGE_FADE_OUT = 0x1, // fades out over the last 20 visible frames (set by the last hit of an attack)
};

typedef struct BattleWorkHpGauge {
    u16 mode;          // 0x0, gauge style; 1 = trailing bar
    u16 flags;         // 0x2, BattleHpGaugeFlags
    s16 drainTimer;    // 0x4, frames left of the bar animation
    s16 drainLength;   // 0x6, bar animation length (20, or 40 in mode 1)
    s16 visibleTimer;  // 0x8, frames the gauge stays up; fades out below 20
    s16 visibleLength; // 0xA, drainLength + 30
    s32 prevHp;        // 0xC, HP the bar animates from
    s32 targetHp;      // 0x10, HP the bar animates to
    f32 barRatio;      // 0x14, main bar fill, 0..1
    f32 trailRatio;    // 0x18, trailing (lost HP) bar fill, 0..1
} BattleWorkHpGauge;

typedef struct ItemDropData {
    ItemType type;  // 0x0
    s16 holdWeight; // 0x4
    s16 dropWeight; // 0x6
} ItemDropData;

// note to self: +4 is near mUnk_HpGauge at 0x1FC
typedef struct StChgInfo {
    s8 type;         // 0x0, -1 = free
    s8 strength;     // 0x1, status strength being announced
    u8 stagger;      // 0x2, 10 per queued entry
    u8 stackOffset;  // 0x3, 0x3C or 0x50, +10 per entry from the newest
    s32 reserved_04; // 0x4, always set to 0
    s32 changed;     // 0x8, 1: strength changed / newly inflicted (selects msg1)
} StChgInfo;         // status-change message queue entry

typedef struct BtlStatusCopy {
    u8 data[0x1E]; // BattleUnit status turns/strengths from sleepTurns, copied as one block
} BtlStatusCopy;

typedef struct BattleUnit {
    s32 unitId;                               // 0x0
    BattleUnitType initialKind;               // 0x4
    BattleUnitType currentKind;               // 0x8
    s8 alliance;                              // 0xC
    u8 level;                                 // 0xD
    s8 groupSetupId;                          // 0xE
    struct BattleUnitKind* kindParams;        // 0x10
    BattleUnitPart* parts;                    // 0x14
    BattleDataEntry* dataTable;               // 0x18
    s32 flags;                                // 0x1C
    s8 moveState;                             // 0x20
    s8 maxMoveCount;                          // 0x21
    s8 movesRemaining;                        // 0x22
    s8 maxMovesThisTurn;                      // 0x23
    s8 activeTurns;                           // 0x24
    s8 swallowRate;                           // 0x25
    s8 swallowAttribute;                      // 0x26
    s32 movePriority;                         // 0x28
    s32 attackPhase;                          // 0x2C, BattlePhase in which the unit acts
    Vec homePosition;                         // 0x30
    Vec position;                             // 0x3C
    Vec positionOffset;                       // 0x48
    Vec displayOffset;                        // 0x54
    Vec baseRotation;                         // 0x60
    Vec rotation;                             // 0x6C
    Vec rotationOffset;                       // 0x78
    Vec offsetCenter;                         // 0x84
    Vec scale;                                // 0x90
    Vec baseScale;                            // 0x9C
    Vec togeOffset;                           // 0xA8
    Vec heldItemBaseOffset;                   // 0xB4, copied from BattleUnitKind.heldItemBaseOffset
    Vec heldItemOffset;                       // 0xC0
    s16 width;                                // 0xCC
    s16 height;                               // 0xCE
    s16 statusIconOffset[2];                  // 0xD0
    s16 hpGaugeOffset[2];                     // 0xD4
    Vec cutBaseOffset;                        // 0xD8
    f32 cutWidth;                             // 0xE4
    f32 cutHeight;                            // 0xE8
    Vec bintaHitOffset;                       // 0xEC, Love Slap
    Vec kissHitOffset;                        // 0xF8, Lip Lock
    BattleUnitAttribute_Flags attributeFlags; // 0x104
    s16 maxHp;                                // 0x108
    s16 baseMaxHp;                            // 0x10A
    s16 currentHp;                            // 0x10C
    s16 maxFp;                                // 0x10E
    s16 baseMaxFp;                            // 0x110
    s16 currentFp;                            // 0x112
    f32 sizeMultiplier;                       // 0x114
    union {
        struct {
            s8 sleepTurns;          // 0x118
            s8 sleepStrength;       // 0x119
            s8 stopTurns;           // 0x11A
            s8 dizzyTurns;          // 0x11B
            s8 poisonTurns;         // 0x11C
            s8 poisonStrength;      // 0x11D
            s8 confusionTurns;      // 0x11E
            s8 electricTurns;       // 0x11F
            s8 dodgyTurns;          // 0x120
            s8 burnTurns;           // 0x121
            s8 freezeTurns;         // 0x122
            s8 sizeChangeTurns;     // 0x123
            s8 sizeChangeStrength;  // 0x124
            s8 atkChangeTurns;      // 0x125
            s8 atkChangeStrength;   // 0x126
            s8 defChangeTurns;      // 0x127
            s8 defChangeStrength;   // 0x128
            s8 chargeStrength;      // 0x129
            s8 allergicTurns;       // 0x12A
            s8 flippedTurns;        // 0x12B, turn count left until flipping back
            s8 invisibleTurns;      // 0x12C
            s8 paybackTurns;        // 0x12D
            s8 holdFastTurns;       // 0x12E
            s8 fastTurns;           // 0x12F
            s8 slowTurns;           // 0x130
            s8 hpRegenTurns;        // 0x131
            s8 hpRegenStrength;     // 0x132
            s8 fpRegenTurns;        // 0x133
            s8 fpRegenStrength;     // 0x134
            s8 instantKillStrength; // 0x135
        };
        BtlStatusCopy statusTurns; // 0x118, the 0x1E status bytes as one block (party info save/restore)
    };
    s32 statusFlags; // 0x138
#if VERSION >= VERSION_US
    u16 usCommandDisabled[2]; // US only (+4 from here): per-unit turns left for the two command blocks JP keeps in BattleWork commandDisabled[3..4]
#endif
    s32 protectId;                      // 0x13C
    BattleVulnerableStatus* vulnStatus; // 0x140
    Vec moveStartPos;                   // 0x144
    Vec moveCurrentPos;                 // 0x150
    Vec moveTargetPos;                  // 0x15C
    s32 moveFrames;                     // 0x168, move/jump frame count (BEC_MVFRAME)
    f32 moveSpeedXZ;                    // 0x16C
    f32 fallAccel;                      // 0x170
    f32 moveSpeedY;                     // 0x174
    f32 moveAngle;                      // 0x178
    f32 moveDistance;                   // 0x17C, XZ distance of the move (moveSpeedXZ = this / moveFrames)
    f32 moveProgress;                   // 0x180, elapsed frames of a move (intpl_sub cur); the jump commands use it as the arc height and the fall step
    s8 moveDirection;                   // 0x184
    s8 faceDirection;                   // 0x185
    BecSndWork moveSnd;                 // 0x188 (US 0x18C)
    Vec jumpStep;                       // 0x1A4 (US 0x1A8), per-frame XZ/Y step of btlevtcmd_MarioJumpPosition
    f32 jumpAngle;                      // 0x1B0 (US 0x1B4), arc angle in degrees
    f32 jumpAngleStep;                  // 0x1B4 (US 0x1B8), arc angle added per frame
    f32 jumpBaseY;                      // 0x1B8 (US 0x1BC), last Y position of the jump
    u8 reserved_1BC[0x1C0 - 0x1BC];     // 0x1BC (US 0x1C0), never accessed
    BtlPoseSoundTable moveSndTable;     // 0x1C0 (US 0x1C4), jump names + run/walk/dive entries (btlevtcmd_SetJump/Run/Walk/DiveSound)
    BattleWorkHpGauge hpGauge;          // 0x1F8
    union {
        EvtWord work[16];  // 0x214, unit work words (btlevtcmd_SetUnitWork / GetUnitWork): numbers, effect and work pointers; floats stored in the word (SetUnitWorkFloat / GetUnitWorkFloat)
        void* workPtr[16]; // 0x214, the same words when they hold an effect or a BTL_ALLOC block
    };
    BattleUnitPart* currentTarget;    // 0x254
    s32 reserved_258;                 // 0x258 (US 0x25C), only cleared at turn start (battle_seq)
    s16 hpDamageCount;                // 0x25C, number of damaging moves
    s32 totalHpDamageTaken;           // 0x260
    s32 totalFpDamageTaken;           // 0x264 (US 0x268), sum of fpDamageTaken this turn
    s32 totalFpLost;                  // 0x268 (US 0x26C), sum of fpLost this turn
    s8 hpDamageTaken;                 // 0x26C
    s8 fpDamageTaken;                 // 0x26D
    s8 fpLost;                        // 0x26E (US 0x272), FP actually lost by the last hit (fpDamageTaken clamped to current FP)
    s8 superguardCountTaken;          // 0x26F (US 0x273), attacker's superguardedCount when this unit superguarded it
    s32 damagePattern;                // 0x270, damage pattern of the last hit (selects the hurt pose), 0 when cleared
    s32 damageCode;                   // 0x274
    BattleUnitToken_Flags tokenFlags; // 0x278
    s32 superguardedCount;            // 0x27C (US 0x280), times this unit was superguarded this turn; weapon special 0x20 subtracts it from damage
    s32 totalDamageDealt;             // 0x280, damage this unit dealt as attacker
    s32 initEventId;                  // 0x284
    EvtWord* waitEventCode;           // 0x288
    s32 waitEventId;                  // 0x28C
    EvtWord* unisonPhaseEventCode;    // 0x290
    EvtWord* phaseEventCode;          // 0x294
    s32 phaseEventId;                 // 0x298
    EvtWord* attackEventCode;         // 0x29C, btlevtcmd_SetEventAttack / BtlUnit_GetData(unit, 2/3)
    EvtWord* confusionEventCode;      // 0x2A0, btlevtcmd_SetEventConfusion
    s32 attackEventId;                // 0x2A4
    s32 attackEventFlags;             // 0x2A8, BattleAttackEventFlags (0 by SetEventAttack)
    EvtWord* damageEventCode;         // 0x2AC
    s32 damageEventId;                // 0x2B0
    EvtWord* entryEventCode;          // 0x2B4 (US 0x2B8), btlevtcmd_SetEventEntry
    s32 entryEventId;                 // 0x2B8 (US 0x2BC)
    EvtWord* ceilFallEventCode;       // 0x2BC (US 0x2C0), btlevtcmd_SetEventCeilFall, run by the stage ceiling fall
    s32 ceilFallEventId;              // 0x2C0 (US 0x2C4)
    EvtWord* actEndEvent;             // 0x2C4 (US 0x2C8), run when the unit's action ends (battle_seq)
    s32 actEndEventId;                // 0x2C8 (US 0x2CC)
#if VERSION == VERSION_EU
    s32 slideReturnEventId; // PAL only (+4 from here): enemy_slide_return_evt of sac_enemy_slide_return, waited on by BattleWaitAllActiveEvtEnd_NoBgSetEndWait
#endif
    EvtWord* hitEventCode; // 0x2CC (US 0x2D0), run on the attacker by BattleRunHitEventDirect
    s32 talkPartId;        // 0x2D0 (US 0x2D4)
    const char* talkPose;  // 0x2D4 (US 0x2D8), pose type 0x41 (btlevtcmd talk anim)
    const char* stayPose;  // 0x2D8 (US 0x2DC), pose type 0x2B
    union {
        BattleWorkUnitBadgesEquipped badgesEquipped;          // 0x2DC
        u8 badgeCounts[sizeof(BattleWorkUnitBadgesEquipped)]; // 0x2DC, the same 40 counters by index
    };
    ItemType heldItem;                      // 0x304, 4 bytes
    ItemDropData* dropTable;                // 0x308
    u8 stolenCoins;                         // 0x30C, coins a Bandit (borodo) stole; dropped back as its held coin item
    u8 moveColorLv;                         // 0x30D
    u8 moveColorLvDisp;                     // 0x30E, current move colour level, ramps toward moveColorLv
    struct BattleWeapon* countersetWeapon;  // 0x310
    void (*deleteFunc)(struct BattleUnit*); // 0x314 (US 0x318), called by BtlUnit_Delete
    struct smartEntry* screenTexBuf;        // 0x318 (US 0x31C), smartAlloc EFB copy (0x260x0x1E0, unit_party_chuchurina), freed on unit delete
    u8 reserved_31C[0x320 - 0x31C];         // 0x31C (US 0x320), never accessed
    EffectEntry* sleepEff;                  // 0x320, BSE_Sleep
    EffectEntry* fireEff;                   // 0x324
    EffectEntry* iceEff;                    // 0x328
    EffectEntry* sparkEff;                  // 0x32C
    struct IconEntry* kageIcon;             // 0x330, BSE_Kagegakure
    u16 burnDamageFlameState;               // 0x334
    u16 burnDamageFlameActive;              // 0x336
    s32 burnDamageFlameAnimTimer;           // 0x338
    f32 burnDamageFlameScale;               // 0x33C
    EffectEntry* burnDamageFlameEff;        // 0x340
    BattleWorkStatusIcon statusIconWork;    // 0x344
    StChgInfo statusChangeInfo[6];          // 0xAE4, BattleStatusChangeInfoWorkInit
    s32 stageObjectId;                      // 0xB2C
} BattleUnit;

typedef struct BattleUnitKind {
    BattleUnitType unitType;                  // 0x0
    const char* name;                         // 0x4
    s16 maxHp;                                // 0x8
    s16 maxFp;                                // 0xA
    u8 dangerHP;                              // 0xC
    u8 perilHP;                               // 0xD
    u8 level;                                 // 0xE
    u8 bonusExp;                              // 0xF
    u8 bonusCoin;                             // 0x10
    u8 bonusCoinRate;                         // 0x11
    u8 baseCoin;                              // 0x12
    u8 runRate;                               // 0x13
    u16 pbSoftCap;                            // 0x14
    s16 width;                                // 0x16
    s16 height;                               // 0x18
    s16 hitOffset[2];                         // 0x1A
    Vec centerOffset;                         // 0x20
    s16 hpGaugeOffset[2];                     // 0x2C
    Vec talkTogeBaseOffset;                   // 0x30
    Vec heldItemBaseOffset;                   // 0x3C
    Vec burnFlameOffset;                      // 0x48
    f32 vivianOffsetX;                        // 0x54, _get_vivian_attack_position: x offset (times facing and scale x)
    f32 vivianOffsetZ;                        // 0x58, _get_vivian_attack_position: z offset (times scale z)
    Vec bintaHitOffset;                       // 0x5C
    Vec kissHitOffset;                        // 0x68
    Vec cutBaseOffset;                        // 0x74
    f32 cutWidth;                             // 0x80
    f32 cutHeight;                            // 0x84
    s8 turnOrder;                             // 0x88
    s8 turnOrderVariance;                     // 0x89
    s8 swallowChance;                         // 0x8A
    u8 swallowAttributes;                     // 0x8B
    u8 hammerKnockbackChance;                 // 0x8C
    u8 itemStealParam;                        // 0x8D
    Vec starPointDispOffset;                  // 0x90
    const char* damageSfxName;                // 0x9C
    const char* fireDamageSfxName;            // 0xA0
    const char* iceDamageSfxName;             // 0xA4
    const char* explosionDamageSfxName;       // 0xA8
    u32 attributeFlags;                       // 0xAC
    StatusVulnerability* statusVulnerability; // 0xB0
    s8 numParts;                              // 0xB4
    BattleUnitKindPart* parts;                // 0xB8
    EvtWord* initEventCode;                   // 0xBC
    BattleDataEntry* dataTable;               // 0xC0
} BattleUnitKind;

// SEQ_PHASE steps (BattleGetSeq(wp, SEQ_PHASE)): each turn runs phases 1-5 in order, and a unit takes its
// actions in the phase its attackPhase names (btlseqMove queues the units whose attackPhase equals the step).
typedef enum BattlePhase {
    BATTLE_PHASE_INIT = 0x4000000,          // first step of a turn's phase sequence; moves on to phase 1
    BATTLE_PHASE_BEFORE_PLAYER = 0x4000001, // tutorial helpers, Koops's Shell Shield and Bobbery's bombs act here
    BATTLE_PHASE_PLAYER = 0x4000002,        // Mario, the partner and the system unit
    BATTLE_PHASE_AFTER_PLAYER = 0x4000003,  // no unit setup uses it
    BATTLE_PHASE_ENEMY = 0x4000004,         // enemies; the audience throws items and reacts in this phase
    BATTLE_PHASE_AFTER_ENEMY = 0x4000005,   // stage objects (trees, switches)
    BATTLE_PHASE_END = 0x4000006            // the turn's phases are over: next SEQ_TURN step
} BattlePhase;

typedef struct BattleUnitSetup {
    BattleUnitKind* unitKindParams; // 0x0
    s8 alliance;                    // 0x4, -> BattleUnit.alliance (BtlUnit_Entry); 2 for stage objects
    u8 pad_05[3];                   // 0x5, never read
    s32 attackPhase;                // 0x8, BattlePhase; -> BattleUnit.attackPhase
    Vec position;                   // 0xC, -> unit pos/offset pos/home pos
    s32 hitOffsetX;                 // 0x18, -> every BattleUnitPart.hitOffsetX
    s32 unitWork[4];                // 0x1C, -> BattleUnit.work[0..3]
    ItemDropData* itemDropTable;    // 0x2C
} BattleUnitSetup;

BOOL BtlUnit_Init(void);
BattleUnit* BtlUnit_Entry(BattleUnitSetup* setup);
BOOL BtlUnit_Delete(BattleUnit* unit);
BattleUnit* BtlUnit_Spawn(BattleUnitSetup* setup, s32 flags);
s32 BtlUnit_GetUnitId(BattleUnit* unit);
BattleUnitPart* BtlUnit_GetPartsPtr(BattleUnit* unit, s32 partNum);
s32 BtlUnit_GetBodyPartsId(BattleUnit* unit);
void BtlUnit_GetPos(BattleUnit* unit, f32* x, f32* y, f32* z);
void BtlUnit_SetPos(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_AddPos(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_GetPartsPos(BattleUnitPart* part, f32* x, f32* y, f32* z);
void BtlUnit_SetPartsPos(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_AddPartsPos(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_GetPartsWorldPos(BattleUnitPart* part, f32* x, f32* y, f32* z);
void BtlUnit_GetHitPos(BattleUnit* unit, BattleUnitPart* part, f32* x, f32* y, f32* z);
void BtlUnit_SetHitOffset(BattleUnit* unit, BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_SetHitCursorOffset(BattleUnit* unit, BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_GetHomePos(BattleUnit* unit, f32* x, f32* y, f32* z);
void BtlUnit_SetHomePos(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_AddHomePos(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_SetPartsHomePos(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_SetRotate(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_GetRotate(BattleUnit* unit, f32* x, f32* y, f32* z);
void BtlUnit_AddRotate(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_SetPartsRotate(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_GetPartsRotate(BattleUnitPart* part, f32* x, f32* y, f32* z);
void BtlUnit_AddPartsRotate(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_SetBaseRotate(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_GetBaseRotate(BattleUnit* unit, f32* x, f32* y, f32* z);
void BtlUnit_SetPartsBaseRotate(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_GetPartsBaseRotate(BattleUnitPart* part, f32* x, f32* y, f32* z);
void BtlUnit_SetRotateOffset(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_SetPartsRotateOffset(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_AddPartsRotateOffset(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_SetBaseScale(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_GetScale(BattleUnit* unit, f32* x, f32* y, f32* z);
void BtlUnit_SetScale(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_AddScale(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_SetPartsBaseScale(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_SetPartsScale(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_AddPartsScale(BattleUnitPart* part, f32 x, f32 y, f32 z);
s32 BtlUnit_GetWidth(BattleUnit* unit);
s32 BtlUnit_GetHeight(BattleUnit* unit);
void BtlUnit_SetHeight(BattleUnit* unit, s16 height);
void BtlUnit_SetOffsetPos(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_GetPartsOffsetPos(BattleUnitPart* part, f32* x, f32* y, f32* z);
void BtlUnit_SetPartsOffsetPos(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_AddPartsOffsetPos(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_SetDispOffset(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_SetPartsDispOffset(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_AddPartsDispOffset(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_SetMoveStartPos(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_SetPartsMoveStartPos(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_SetMoveCurrentPos(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_SetPartsMoveCurrentPos(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_SetMoveTargetPos(BattleUnit* unit, f32 x, f32 y, f32 z);
void BtlUnit_SetPartsMoveTargetPos(BattleUnitPart* part, f32 x, f32 y, f32 z);
void BtlUnit_SetFallAccel(BattleUnit* unit, f32 fallAccel);
void BtlUnit_SetPartsFallAccel(BattleUnitPart* part, f32 fallAccel);
void BtlUnit_SetMoveSpeed(BattleUnit* unit, f32 moveSpeedXZ);
void BtlUnit_SetPartsMoveSpeed(BattleUnitPart* part, f32 moveSpeedXZ);
void BtlUnit_SetJumpSpeed(BattleUnit* unit, f32 moveSpeedY);
s8 BtlUnit_GetBelong(BattleUnit* unit);
void BtlUnit_GetStatus(BattleUnit* unit, StatusEffectType type, s8* turns, s8* strength);
BOOL BtlUnit_SetStatus(BattleUnit* unit, StatusEffectType type, s8 turns, s8 strength);
void BtlUnit_ClearStatus(BattleUnit* unit);
BOOL BtlUnit_CheckRecoveryStatus(BattleUnit* unit, StatusEffectType type);
BOOL BtlUnit_CheckStatus(BattleUnit* unit, StatusEffectType type);
s32 BtlUnit_CheckStatusFlag(BattleUnit* unit, s32 flags);
void BtlUnit_OnStatusFlag(BattleUnit* unit, s32 flags);
void BtlUnit_OffStatusFlag(BattleUnit* unit, s32 flags);
s32 BtlUnit_CheckUnitFlag(BattleUnit* unit, s32 flags);
void BtlUnit_OnUnitFlag(BattleUnit* unit, s32 flags);
void BtlUnit_OffUnitFlag(BattleUnit* unit, s32 flags);
const char* BtlUnit_GetPoseNameFromType(BattleUnitPart* part, s32 type);

void BtlUnit_CheckPinchStatus(BattleUnit* unit, BOOL a2);

void BtlUnit_SetParamToPouch(BattleUnit* unit);

void BtlUnit_ResetMoveStatus(BattleUnit* unit);

s32 BtlUnit_GetFp(BattleUnit* unit);
void BtlUnit_SetFp(BattleUnit* unit, s32 value);
s32 BtlUnit_GetMaxFp(BattleUnit* unit);
void BtlUnit_SetMaxFp(BattleUnit* unit, s32 value);
void BtlUnit_RecoverHp(BattleUnit* unit, s32 value);
void BtlUnit_RecoverFp(BattleUnit* unit, s32 value);
s32 BtlUnit_GetHitDamage(BattleUnit* unit);
s32 BtlUnit_GetTotalHitDamage(BattleUnit* unit);
void* BtlUnit_GetData(BattleUnit* unit, s32 tag);
BOOL BtlUnit_CheckData(BattleUnit* unit, s32 tag);
BOOL BtlUnit_GetEnemyBelong(BattleUnit* unit);
void BtlUnit_ReviseHpFp(BattleUnit* unit);
void BtlUnit_SetParamFromPouch(BattleUnit* unit);
s32 BtlUnit_snd_se(BattleUnit* unit, const char* sfxName, s32 volume, s32 pan);
s32 BtlUnit_snd_se_pos(BattleUnit* unit, const char* sfxName, s32 volume, s16 pitch, Vec* pos);
BattleUnit* BtlUnit_GetGuardKouraPtr(BattleUnit* unit);

BOOL BtlUnit_CanActStatus(BattleUnit* unit);
void BtlUnit_SetAnim(BattleUnitPart* part, const char* name);
// BtlUnit_EquipItem flags
typedef enum EquipFlags {
    EQUIP_RESET = 1 << 0,   // 0x1, clear the equipped badges first
    EQUIP_MARIO = 1 << 1,   // 0x2, equip Mario's (non-P) badges
    EQUIP_PARTNER = 1 << 2, // 0x4, equip the partner (P) badges
} EquipFlags;
void BtlUnit_EquipItem(BattleUnit* unit, s32 flags, ItemType type); // flags: EquipFlags
void BtlUnit_SetAnimType(BattleUnitPart* part, s32 type);
void BtlUnit_SetBodyAnim(BattleUnit* unit, const char* name);
void BtlUnit_SetBodyAnimType(BattleUnit* unit, s32 type);

struct BattleWeapon;

void BtlUnit_ChangeTalkAnim(s32 unitId);
void BtlUnit_ChangeStayAnim(s32 unitId);
void BtlUnit_GetTalkTogePos(s32 unitId, f32* x, f32* y, f32* z);
BOOL BtlUnit_GetACPossibility(BattleUnit* unit);
BOOL BtlUnit_CanGuardStatus(BattleUnit* unit);
s32 BtlUnit_GetExp(BattleUnit* unit);
s32 BtlUnit_GetCoin(BattleUnit* unit);
s32 BtlUnit_GetWeaponCost(BattleUnit* unit, struct BattleWeapon* weapon);
void BtlUnit_PayWeaponCost(BattleUnit* unit, struct BattleWeapon* weapon);
void BtlUnit_LoadSeMode(s32 mode, s32 kind, BtlPoseSoundTable* table, BecSndWork* work);
void BtlUnit_SetSeMode(BecSndWork* work, const char* name0, const char* name1, s16 c, s16 e, s16 unused, s16 a, s16 b);
void BtlUnit_SetCommandAnimPose(BattleUnit* unit);
void BtlUnit_PoseSoundInit(BattleUnitPart* part);
void BtlUnit_ControlPoseSoundMain(BattleUnitPart* part);
void BtlUnit_HpGaugeMain(BattleUnit* unit);
BOOL BtlUnit_CheckShadowGuard(BattleUnit* unit);
BOOL BtlUnit_CheckWeaponCost(BattleUnit* unit, struct BattleWeapon* weapon);
BOOL BtlUnit_EnemyItemCanUseCheck(s32 item);
void BtlUnit_SetTotalHitDamage(BattleUnit* unit, s16 damage);
