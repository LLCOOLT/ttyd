// The Great Tree (mri): the Puni crowd system's types (PuniWork, PuniData, PuniMap) and its user functions.
#pragma once

#include <dolphin/types.h>
#include "evt/evt_cmd.h"
#include "driver/npcdrv.h"
#include "driver/effdrv.h"
#include <dolphin/mtx.h>
#include "driver/hitdrv.h"
#include "version.h"

typedef struct PuniTarget {
    s32 flags;     // 0x0
    Vec pos;       // 0x4
    HitEntry* hit; // 0x10
} PuniTarget;

#define PUNI_DATA_MAX 211
#define PUNI_TEX_INFO_MAX 200

// Punidat slot ranges. Punidat[0] is Mario's stand-in (PUNI_FLAG_MARIO).
#define PUNI_ALLY_LAST 102   // Punidat[1..102]: the punis (PUNI_FLAG_ALLY); their saved positions are LSW slots 0..101
#define PUNI_SOLID_FIRST 103 // Punidat[103..109]: one fixed blocker per pipe, indexed by loading zone (PUNI_FLAG2_SOLID)
#define PUNI_ENEMY_FIRST 110 // Punidat[110..209]: the Jabbis (PUNI_FLAG_ENEMY)
#define PUNI_ENEMY_END 210
#define PUNI_LSW_SLOT_SIZE 7 // LSW bytes per saved puni position (layout above puniswGetindex in mri_puni.c)

typedef struct PuniAnimSet {
    s16* table[10]; // 0x0
    s16 count[10];  // 0x28
    s16 end[10];    // 0x3C
} PuniAnimSet;

typedef struct PuniWork {
    s32 systemMode;              // 0x0
    PuniAnimSet anim[2];         // 0x4
    char animNames[4][10][16];   // 0xA4, NPC pose names per guide NPC (guide, sister, Jabbi, rival) and anim id
    u32 flags;                   // 0x324
    s32 floor;                   // 0x328
    f32 posY[4];                 // 0x32C
    s32 ymode;                   // 0x33C
    s32 mapKind;                 // 0x340
    Vec recoverPos;              // 0x344
    f32 stuckTop0;               // 0x350
    f32 stuckBottom0;            // 0x354
    f32 stuckTop1;               // 0x358
    f32 stuckBottom1;            // 0x35C
    struct PuniData* marioPuni;  // 0x360
    struct PuniData* guidePuni;  // 0x364, the puni drawn by the guide NPC (evt_puni_setup / evt_puni_init_puni slot 1, PUNI_FLAG_NPC_GUIDE); not read
    struct PuniData* sisterPuni; // 0x368, the guide's sister (slot 2, PUNI_FLAG_NPC_SISTER); not read
    struct PuniData* jabbiPuni;  // 0x36C, the little Jabbi (slot 3, PUNI_FLAG_NPC_JABBI); not read
    struct PuniData* rivalPuni;  // 0x370, the rival puni (slot 4, PUNI_FLAG_NPC_RIVAL); not read
    PuniTarget targets[10];      // 0x374
    s32 allMode;                 // 0x43C
    s32 prevAllMode;             // 0x440
    BOOL showPuniCounter;        // 0x444
    BOOL showRemaining;          // 0x448
    s32 puniCounterAlpha;        // 0x44C
    s32 seed0;                   // 0x450
    s32 seed1;                   // 0x454
    u32 sfx458;                  // 0x458
    s32 puniMoveCount;           // 0x45C
    s32 puniMoveLevel;           // 0x460
    u8 pad_464[0x468 - 0x464];   // 0x464
    u32 sfx468;                  // 0x468
    s32 togeMoveCount;           // 0x46C
    s32 togeMoveLevel;           // 0x470
    s32 togeMoveLevelPrev;       // 0x474
    u32 sfxTogetti;              // 0x478
    s32 beroMode;                // 0x47C
    Vec beroStart;               // 0x480
    Vec beroEnd;                 // 0x48C
    u8 pad_498[0x4B0 - 0x498];   // 0x498
    f32 beroStartRange;          // 0x4B0
    f32 beroEndRange;            // 0x4B4
    u8 pad_4B8[0x4C0 - 0x4B8];   // 0x4B8
    s32 fightSfxCount1;          // 0x4C0
    s32 fightSfxCount2;          // 0x4C4
    u8 pad_4C8[0x4CC - 0x4C8];   // 0x4C8
    s32 windDisabled;            // 0x4CC
} PuniWork;

// PuniData.flags
enum PuniFlags {
    PUNI_FLAG_ALLY = 0x1,                // puni side (Punidat[1..102]): searches the Jabbis (puniSearch, puniModeChangeAttack); puni_init_para, evt_puni_init_puni
    PUNI_FLAG_ENEMY = 0x2,               // Jabbi side (Punidat[110..209]): toge_init_para, evt_toge_setup, evt_puni_init_teki; only these get dizzy (puniModePiyori)
    PUNI_FLAG_MARIO = 0x4,               // Punidat[0], the stand-in that tracks Mario (puni_puni_init)
    PUNI_FLAG_ANIM_PUNI = 0x8,           // texture anim set 0, puni (puniAnimation, evt_puni_korokoro)
    PUNI_FLAG_ANIM_TOGE = 0x10,          // texture anim set 1, Jabbi (puniAnimation, evt_toge_setup)
    PUNI_FLAG_NPC_GUIDE = 0x20,          // drawn by the guide NPC "ガイドsp" (puniAnimation, puniModeTrap_sub, evt_puni_setup slot 1)
    PUNI_FLAG_NPC_SISTER = 0x40,         // drawn by "ガイド妹sp", the guide's sister (slot 2)
    PUNI_FLAG_NPC_JABBI = 0x80,          // drawn by "ちびトゲsp", the little Jabbi (slot 3; puniModeAwayjump plays the Jabbi jump sfx)
    PUNI_FLAG_NPC_RIVAL = 0x100,         // drawn by "ライバルsp", the rival puni (slot 4)
    PUNI_FLAG_MOVE_STOP = 0x200,         // frozen in place (evt_puni_all_movestop; puniModeParent, puni_puni_main skip it)
    PUNI_FLAG_ACTIVE = 0x400,            // slot in use: updated, drawn, counted (puni_puni_main, puniAnimation, evt_puni_count)
    PUNI_FLAG_HIDDEN = 0x800,            // not drawn although active (puniAnimation; puniModeWater, puniModeDokan, puniTrapNpcOn)
    PUNI_FLAG_WALL_CHECK = 0x1000,       // move against map hit (puniMoveAtari, puniMoveHit); off while walking in through a loading zone (evt_puni_setup, puniModeEnter)
    PUNI_FLAG_KNOCKBACK = 0x2000,        // lost an exchange, damage pending (puniParaAttack sets, puniModeDamage clears on landing)
    PUNI_FLAG_DEFEATED = 0x4000,         // hp hit 0 (puniParaDamage, puniModeDamage); skipped by the search* functions and evt_puni_zenmetsu_check
    PUNI_FLAG_STRAY = 0x8000,            // not following Mario: set per mode in puniModeMain/puni_puni_main (mass, away, hagure, updraft, fall...); evt_puni_count skips it, evt_puni_all_save/evt_puni_exit save its position
    PUNI_FLAG_KEEP_NPC_ANIM = 0x20000,   // puniAnimation moves the stand-in NPC but leaves its pose to the script
    PUNI_FLAG_NPC_MANUAL = 0x40000,      // puniAnimation leaves the stand-in NPC alone; scripts set it while moving the guide NPCs themselves (mri_01, mri_06...)
    PUNI_FLAG_IN_GROUP = 0x80000,        // part of a follow chain, can be a parent (searchParent); PuniDokuritsu clears it
    PUNI_FLAG_COLLIDE = 0x100000,        // pushes and is pushed by other punis (puniOption, puniCollideAll); evt_puni_dokan_onoff, puniModeWind/Fall/Exit clear it
    PUNI_FLAG_WALL_CONTACT = 0x400000,   // the last move hit a wall (puniMoveDecel, puniMoveNormal, puniMoveMain)
    PUNI_FLAG_NO_SAVE = 0x800000,        // script-placed puni outside Mario's party: evt_puni_exit/evt_puni_all_save skip it, scripts clear it when it joins (mri_01 rival_nakama)
    PUNI_FLAG_ANIM_FREE_RUN = 0x1000000, // animTime counts up on its own instead of following retraceCount (puniAnimation; puniModeAwayjump, puniModeWonder)
    PUNI_FLAG_STEPPED = 0x2000000,       // mode already run this frame (puni_puni_main: attackers first, then the rest)
    PUNI_FLAG_FRAME_INIT = 0x4000000,    // per-frame setup (death check, breath, distances) done (puni_puni_main)
    PUNI_FLAG_DIZZY = 0x8000000,         // dizzy Jabbi, always loses the next exchange (puniModePiyori, puniParaAttack)
    PUNI_FLAG_PUSHING = 0x10000000,      // overlapping a neighbour and being pushed apart (puniOption, puniCollideAll)
    PUNI_FLAG_CROWDED = 0x20000000,      // a neighbour is within push range this frame; PUSHING ends when this is clear (puniOption, puniCollideAll)
    PUNI_FLAG_SKIP_SETUP = 0x40000000,   // left as is by the next evt_puni_setup (set by evt_puni_exit on a stray puni when there is no next map)
};

// PuniData.flags2
enum PuniFlags2 {
    PUNI_FLAG2_HEALED = 0x1,     // hp regenerated (puniParaRecover); evt_icon_disp_func clears it after 30 frames
    PUNI_FLAG2_DIZZY_ICON = 0x2, // draw the dizzy stars (evt_icon_disp_func); set and cleared with PUNI_FLAG_DIZZY
    PUNI_FLAG2_PUSHED = 0x4,     // moved by a push this frame (puniModeAway, puniModeWind); cleared each frame in puni_puni_main; lets it past the _ymode_mri_16 slope edge
    PUNI_FLAG2_ON_SLOPE = 0x8,   // on the mri_16 slope (_ymode_mri_16_00/_01)
    PUNI_FLAG2_KILLED = 0x10,    // just defeated: puni_puni_main switches it to PUNI_MODE_DEAD next frame
    PUNI_FLAG2_SOLID = 0x20,     // fixed blocker slot (Punidat[103..109], evt_puni_setup): pushes others out without being pushed (puniOption, puniCollideAll)
};

// PuniWork.flags
enum PuniWorkFlags {
    PUNIGP_FLAG_BERO_WEST = 0x1,     // loading zone direction 6 (evt_puni_setup, evt_puni_exit); punis scale in/out at side exits (puniModeEnter/Exit)
    PUNIGP_FLAG_BERO_EAST = 0x2,     // loading zone direction 2
    PUNIGP_FLAG_BERO_UP = 0x4,       // loading zone direction 8
    PUNIGP_FLAG_BERO_DOWN = 0x8,     // loading zone direction 9 (puniModeEnter waits longer, evt_puni_setup offsets the end point)
    PUNIGP_FLAG_EXIT_NO_MAP = 0x10,  // evt_puni_exit was called without a next map
    PUNIGP_FLAG_BATTLE_FLOOR = 0x20, // floor 9 or 12, the puni vs. Jabbi battle floors (evt_puni_setup; puni_puni_main)
};

// PuniTarget.flags
enum PuniTargetFlags {
    PUNI_TARGET_FLAG_ON = 0x1,   // target in use (puniTargetSearch, puni_puni_main, evt_target_flag_onoff)
    PUNI_TARGET_FLAG_MASS = 0x2, // punis gather at it (massTarget; puniModeFunbari)
    PUNI_TARGET_FLAG_AWAY = 0x4, // punis flee from it (awayTarget; puni_piders_check_func sets it on Pider NPCs)
};

// PuniData.mode / prevMode: the state puniModeMain runs each frame (the puniMode* function of the same name).
enum PuniMode {
    PUNI_MODE_IDLE = 0,        // waits; joins once Mario is within 150 (or blown away by a gust)
    PUNI_MODE_JOIN = 1,        // finds a parent (searchParent) and starts following
    PUNI_MODE_PARENT = 2,      // follows its parent in the chain (puniModeParent)
    PUNI_MODE_SEARCH = 3,      // looks for a Jabbi to fight (puniModeSearch)
    PUNI_MODE_MASS = 4,        // gathers at a mass target (puniModeMass)
    PUNI_MODE_AWAYJUMP = 5,    // jumps away (puniModeAwayjump)
    PUNI_MODE_AWAY = 6,        // runs from an away target (puniModeAway)
    PUNI_MODE_ATTACK = 7,      // fights (puniModeAttack)
    PUNI_MODE_ESCAPE = 8,      // escapes (puniModeEscape)
    PUNI_MODE_DAMAGE = 9,      // knocked back (puniModeDamage)
    PUNI_MODE_PIYORI = 10,     // dizzy (puniModePiyori)
    PUNI_MODE_RECOVER = 11,    // recovers (puniModeRecover)
    PUNI_MODE_DEAD = 12,       // defeated (puniModeDead)
    PUNI_MODE_WIND = 13,       // blown by Flurrie's gust (puniModeWind)
    PUNI_MODE_STOP = 14,       // does nothing: scripts park punis here; evt_puni_exit uses it for mri_00
    PUNI_MODE_CHECKPOS = 15,   // stray: walks back to its saved spot (puniModeCheckPos)
    PUNI_MODE_HAGURE = 16,     // lost from the group (puniModeHagure)
    PUNI_MODE_FALL = 17,       // falls (puniModeFall)
    PUNI_MODE_PREUPDRAFT = 18, // waits on an updraft (puniModePreupdraft)
    PUNI_MODE_UPDRAFT = 19,    // rides an updraft (puniModeUpdraft)
    PUNI_MODE_WONDER = 20,     // wanders (puniModeWonder)
    PUNI_MODE_FUNBARI = 21,    // braces against the wind (puniModeFunbari)
    PUNI_MODE_WATER = 22,      // in the water (puniModeWater)
    PUNI_MODE_DODAI = 23,      // stands on a pedestal (puniModeDodai)
    PUNI_MODE_TRAP = 24,       // caught in a trap (puniModeTrap)
    PUNI_MODE_ENTER = 25,      // walks in through a loading zone (puniModeEnter)
    PUNI_MODE_EXIT = 26,       // walks out through a loading zone (puniModeExit)
    PUNI_MODE_POINT = 27,      // walks to a point (puniModePoint)
    PUNI_MODE_DOKAN = 28,      // goes through a pipe (puniModeDokan)
    PUNI_MODE_FUNC = 29,       // runs PuniData.modeFunc
    PUNI_MODE_INERT = 30,      // no handler: Mario's stand-in (Punidat[0]) and punis that finished an exit
};

typedef struct PuniData {
    NpcEntry* npc; // 0x0
    s32 flags;     // 0x4
    s32 flags2;    // 0x8
    u16 mode;      // 0xC, PuniMode
    u16 prevMode;  // 0xE, PuniMode
#if VERSION <= VERSION_DEMO_JP
    s32 modeHistIdx;   // 0x10, demo: index into modeHist (0-127)
    u16 modeHist[128]; // 0x14, demo: mode of each of the last 128 frames
#else
    u8 pad_10[0x114 - 0x10]; // 0x10
#endif
    u16 modeStep;              // 0x114
    s16 index;                 // 0x116
    s16 groupId;               // 0x118
    s16 depth;                 // 0x11A
    u16 anim;                  // 0x11C
    u16 prevAnim;              // 0x11E
    u8 animHoldCount;          // 0x120
    u8 flag1Timer;             // 0x121
    u8 pad_122[0x124 - 0x122]; // 0x122
    s32 animTime;              // 0x124
    s32 timer;                 // 0x128
    Vec pos;                   // 0x12C
    Vec prevPos;               // 0x138
    Vec dispOfs;               // 0x144, added to pos for the npc/shadow matrix
    Vec savedPos;              // 0x150, pos saved on a wall hit; intpl target
    Vec vel;                   // 0x15C
    Vec pushDir;               // 0x168
    f32 maxSpeed;              // 0x174
    f32 accelStep;             // 0x178
    u8 pad_17C[0x180 - 0x17C]; // 0x17C
    f32 dir;                   // 0x180
    f32 spin;                  // 0x184
    f32 rotOffsetY;            // 0x188
    f32 scale;                 // 0x18C, -> npc->scale.x/y and PunidrvPose.scale; ramps 0 -> 1
    Vec radius;                // 0x190
    f32 followRange;           // 0x19C
    f32 breathPower;           // 0x1A0
    f32 marioDist;             // 0x1A4
    f32 parentDist;            // 0x1A8
    f32 moveDist;              // 0x1AC
    f32 prevParentDist;        // 0x1B0
    s32 massTarget;            // 0x1B4
    f32 massTargetDistSq;      // 0x1B8
    s32 awayTarget;            // 0x1BC
    f32 awayTargetDistSq;      // 0x1C0
    u8 pad_1C4[0x1C8 - 0x1C4]; // 0x1C4
    union {
        OSTime startTime; // 0x1C8, gp->renderTime when the timed move started
        struct {
            s32 startTimeHi; // 0x1C8
            s32 startTimeLo; // 0x1CC, low word: elapsed ticks = renderTime - this
        };
    };
    struct PuniData* parent;            // 0x1D0
    struct PuniData* child1;            // 0x1D4
    struct PuniData* child2;            // 0x1D8
    struct PuniData* target;            // 0x1DC
    s32 modeVar0;                       // 0x1E0
    s32 modeVar1;                       // 0x1E4
    s32 modeVar2;                       // 0x1E8
    f32 modeF0;                         // 0x1EC, per-mode float (jump: base height; wind: speed)
    f32 modeF1;                         // 0x1F0, per-mode float (jump: initial vertical term; wind: acceleration)
    f32 modeF2;                         // 0x1F4, per-mode float (jump: linear term; wind: speed cap)
    Vec moveStart;                      // 0x1F8
    Vec moveEnd;                        // 0x204, intpl end point (moveStart = start)
    HitEntry* hitMove;                  // 0x210
    HitEntry* hitCheck;                 // 0x214
    EffectEntry* effect;                // 0x218
    u8 pad_21C[0x2AC - 0x21C];          // 0x21C
    Vec bubblePos;                      // 0x2AC, hagure speech-bubble anchor; passed to effFukidashiEntry as a fake NpcEntry's position
    u8 pad_2B8[0x560 - 0x2B8];          // 0x2B8
    Vec wallNrm;                        // 0x560, wall normal at the last hit; pushDir = -wallNrm
    void (*modeFunc)(struct PuniData*); // 0x56C
    void (*moveFunc)(struct PuniData*); // 0x570
    s16 hp;                             // 0x574
    s16 maxHp;                          // 0x576
    s16 regen;                          // 0x578
    s16 regenTimer;                     // 0x57A
    s16 regenInterval;                  // 0x57C
    s16 attack;                         // 0x57E
    s16 defense;                        // 0x580
    s16 reserved_582;                   // 0x582
    s16 damage;                         // 0x584
    s16 attacked;                       // 0x586
    s16 hitRate;                        // 0x588
    s16 hitRateGuard;                   // 0x58A
    s32 recoverReason;                  // 0x58C, puniPositionCheck result that sent the puni back to recoverPos (1 outside the stuck bands, 2 no floor); not read
    Vec recoverFromPos;                 // 0x590, position before the last recovery; not read
    Vec recoverToPos;                   // 0x59C, position after the last recovery (recoverPos plus jitter); not read
} PuniData;

typedef struct PuniMap {
    f32 maxY;    // 0x0, the maze applies while minY <= pos.y <= maxY
    f32 minY;    // 0x4
    s32 width;   // 0x8
    s32 height;  // 0xC
    s32 size;    // 0x10
    s32 enabled; // 0x14
    void* src;   // 0x18
    s32 inRange; // 0x1C
    u16* data;   // 0x20
} PuniMap;

typedef struct PuniTexInfo {
    char* group; // 0x0
    char* anim;  // 0x4
    f32 frame;   // 0x8
} PuniTexInfo;

USER_FUNC(evt_puni_mem_init);

USER_FUNC(evt_puni_set_yuka);
USER_FUNC(evt_puni_set_hamari);
USER_FUNC(evt_puni_set_maze);
USER_FUNC(evt_puni_wait_systemmode);
USER_FUNC(evt_puni_init_puni);
USER_FUNC(evt_puni_get_position);
USER_FUNC(evt_puni_set_position);
USER_FUNC(evt_puni_get_dir);
USER_FUNC(evt_puni_set_dir);
USER_FUNC(evt_puni_set_anim);
USER_FUNC(evt_puni_korokoro);
USER_FUNC(evt_puni_move_position);
USER_FUNC(evt_puni_move_position2);
USER_FUNC(evt_puni_jump_position);
USER_FUNC(evt_puni_get_mode);
USER_FUNC(evt_puni_set_mode);
USER_FUNC(evt_puni_get_flag);
USER_FUNC(evt_puni_flag_onoff);
USER_FUNC(evt_puni_dokan_onoff);
USER_FUNC(evt_puni_get_lsw_index);
USER_FUNC(evt_puni_set_lsw_index);
USER_FUNC(evt_puni_get_trap_index);
USER_FUNC(evt_puni_set_trap_index);
USER_FUNC(evt_puni_set_ymode);
USER_FUNC(evt_puni_all_fall_check);
USER_FUNC(evt_puni_all_movestop);
USER_FUNC(evt_puni_count);
USER_FUNC(evt_puni_count_area);
USER_FUNC(evt_puni_zenmetsu_check);
USER_FUNC(evt_puni_landon_check);
USER_FUNC(evt_puni_pera_onoff);
USER_FUNC(evt_puni_attack_on);
USER_FUNC(evt_puni_puninum_onoff);
USER_FUNC(evt_puni_winddisable_onoff);
USER_FUNC(evt_puni_force_se_off);
USER_FUNC(evt_puni_all_save);
USER_FUNC(evt_target_flag_onoff);
USER_FUNC(evt_target_set_position);
USER_FUNC(evt_target_set_soko);
void PuniDokuritsu(PuniData* p);
PuniData* puniGetPunidat(void);
PuniWork* puniGetPunigp(void);
void puniswGetindex(s32 base, s32 idx, s32* val, Vec* pos);
void puniswTrapGetindex(s32 idx, s32* out);
void puniMoveDecel(PuniData* p);
int puniMoveAtari(PuniData* p, Vec start, Vec dir, int reflect, f32 dist);
