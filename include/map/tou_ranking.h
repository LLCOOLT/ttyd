#pragma once

// Glitz Pit fighter ranking: the tables and work shared by the tou and tou2 RELs (tou.c and tou2.c each
// carry the ranking code).

#include <dolphin/types.h>

typedef struct RankEntry {
    u16 flags; // 0x0, RankFlags
    s32 id;    // 0x4, FighterId
    union {
        s16 total;   // ranking points
        u8 bytes[2]; // saved byte by byte in GSW 0x207 + id * 2
    } points;        // 0x8
} RankEntry;

typedef enum RankFlags {
    RANK_BELOW = 1 << 0,  // This fighter is below us in the rankings
    RANK_HIDDEN = 1 << 1, // This fighter is hidden from us
    RANK_PLAYER = 1 << 2, // This is the player
} RankFlags;

typedef struct RankData {
    s32 count;          // 0x0
    RankEntry* entries; // 0x4
} RankData;

typedef struct FighterData {
    u16 flags;           // 0x00, FighterFlags
    const char* name;    // 0x04
    const char* title;   // 0x08
    s32 setupId;         // 0x0C, index into btlsetup_tou_tbl
    const char* taunt;   // 0x10
    const char* victory; // 0x14
    s16 initPoints;      // 0x18, starting ranking points
} FighterData;

typedef enum FighterFlags {
    FIGHT_MAJOR = 1 << 0,
    FIGHT_MINOR = 1 << 1,
    FIGHT_CHAMPION = 1 << 2,
    FIGHT_PLAYER = 1 << 3,
    FIGHT_BANDITS = 1 << 8,
    FIGHT_KOOPAS = 1 << 9,
    FIGHT_GOOMBAS = 1 << 10,
    FIGHT_CLEFTS = 1 << 11,
    FIGHT_KOOPATROL = 1 << 12,
} FighterFlags;

typedef enum FighterId {
    FIGHTER_RAWK_HAWK = 0,
    FIGHTER_KOOPINATOR = 1,
    FIGHTER_CHOMPS = 2,
    FIGHTER_BROS = 3,
    FIGHTER_CRAW = 4,
    FIGHTER_MAGIKOOPA = 5,
    FIGHTER_FUZZY = 6,
    FIGHTER_SHADY_KOOPAS = 7,
    FIGHTER_BRISTLES = 8,
    FIGHTER_SPIKE_TOPS = 9,
    FIGHTER_IRON_CLEFTS = 10,
    FIGHTER_BANDITS = 11,
    FIGHTER_BOB_OMB = 12,
    FIGHTER_BALD_CLEFTS = 13,
    FIGHTER_BOGGLY = 14,
    FIGHTER_LAKITU = 15,
    FIGHTER_DULL_BONES = 16,
    FIGHTER_POKEYS = 17,
    FIGHTER_KP_KOOPAS = 18,
    FIGHTER_GOOMBAS = 19,
    FIGHTER_PLAYER = 20,
    FIGHTER_SWOOPS = 21,
    FIGHTER_SPINIA = 22,
} FighterId;

typedef struct RuleData {
    const char* name; // 0x00
    const char* desc; // 0x04
    s32 id;           // 0x08
    s32 param;        // 0x0C
    s32 param2;       // 0x10
} RuleData;

// Scrolling of the ranking board.
typedef struct RankDispWork {
    f32 scroll; // 0x0
    f32 target; // 0x4, page * 220
    s32 page;   // 0x8
} RankDispWork;
