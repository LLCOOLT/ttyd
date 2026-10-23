#pragma once

#include "mario/mario.h"
#include <dolphin/types.h>

#pragma enumsalwaysint off
typedef enum PartyMember {
    PARTY_MEMBER_NONE,      // 0
    PARTY_MEMBER_GOOMBELLA, // 1
    PARTY_MEMBER_KOOPS,     // 2
    PARTY_MEMBER_BOBBERY,   // 3
    PARTY_MEMBER_YOSHI,     // 4
    PARTY_MEMBER_FLURRIE,   // 5
    PARTY_MEMBER_VIVIAN,    // 6
    PARTY_MEMBER_MS_MOWZ,   // 7
#define MAIN_PARTY_MEMBER_MAX PARTY_MEMBER_MS_MOWZ + 1
    PARTY_MEMBER_EGG,                // 8
    PARTY_MEMBER_FLAVIO,             // 9
    PARTY_MEMBER_PUNIO,              // 10
    PARTY_MEMBER_FRANKLY,            // 11
    PARTY_MEMBER_CRAW,               // 12
    PARTY_MEMBER_GOOMBELLA_FOLLOWER, // 13
    PARTY_MEMBER_KOOPS_FOLLOWER,     // 14
    PARTY_MEMBER_BOBBERY_FOLLOWER,   // 15
    PARTY_MEMBER_YOSHI_FOLLOWER,     // 16
    PARTY_MEMBER_FLURRIE_FOLLOWER,   // 17
    PARTY_MEMBER_VIVIAN_FOLLOWER,    // 18
    PARTY_MEMBER_MS_MOWZ_FOLLOWER    // 19
} PartyMember;
#pragma enumsalwaysint on

#pragma enumsalwaysint off
typedef enum PartyFlags {
    PARTY_FLAG_IS_ACTIVE = (1 << 0),
    PARTY_FLAG_IS_GROUNDED = (1 << 1),
    PARTY_FLAG_IS_FOLLOWER = (1 << 2),
    PARTY_FLAG_IS_PARTNER = (1 << 3),
    PARTY_FLAG_IS_JUMPING = (1 << 4),
    PARTY_FLAG_IS_FALLING = (1 << 5),
    PARTY_FLAG_IS_STEPPING = (1 << 6),
    PARTY_FLAG_IN_SHALLOW_WATER = (1 << 7),
    PARTY_FLAG_IS_BEING_USED = (1 << 8),
    PARTY_FLAG_PAPER_MODE = (1 << 12),
    PARTY_FLAG_MOT_SLIT_FLOOR = (1 << 13),
    PARTY_FLAG_IS_RIDING_PLANE = (1 << 16),
    PARTY_FLAG_IS_RIDING_SHIP = (1 << 17),
    PARTY_FLAG_IS_BEHIND_MARIO = (1 << 19),
    PARTY_FLAG_SLEEP_ON = (1 << 22),
    PARTY_FLAG_BG_MODE = (1 << 23),
    PARTY_FLAG_DISABLE_FRONT_WALL_CHK = (1 << 24),
    PARTY_FLAG_FORCE_FALL = (1 << 25),
    PARTY_FLAG_DISABLE_FLOORS = (1 << 26),
    PARTY_FLAG_RUN_OFF = (1 << 28),
    PARTY_FLAG_CTRL_OFF = (1 << 29),
    PARTY_FLAG_CTRL_OFF_2 = (1 << 30),
    PARTY_FLAG_IS_EVT_USE = (1 << 31)
} PartyFlags;
#pragma enumsalwaysint on

#pragma enumsalwaysint off
typedef enum PartySlotId {
    PARTY_SLOT_PARTY = 0,    // 0x0
    PARTY_SLOT_FOLLOWER = 1, // 0x1
    PARTY_SLOT_NONE = -1
} PartySlotId;
#pragma enumsalwaysint on

struct HitEntry;
struct EffectEntry;

/* PartyEntry 0x174-0x187: per-partner scratch. Each partner file uses its own view.
   Field types copy the existing casts exactly (signedness is load-bearing). */
typedef struct PartyWorkCommon { // party.c, evt_party.c (generic jump arcs)
    f32 accelY;                  // 0x174, added to velY each frame
    u8 pad178[0x188 - 0x178];    // 0x178
} PartyWorkCommon;

typedef struct PartyWorkYoshi {  // party_yoshi.c
    f32 gravityVel;              // 0x174, gravity += this
    f32 gravityAccel;            // 0x178, this += accelY
    u8 pad17C[0x188 - 0x17C];    // 0x17C
} PartyWorkYoshi;

typedef struct PartyWorkNokonoko { // party_nokonoko.c
    u32 heldItem;                // 0x174, ItemEntry* picked up while in the shell (PW u32)
    union {
        u32 shellSpinBits;       // 0x178, zeroed as u32
        f32 shellSpin;           // 0x178, 50.0 then -= 2.2 per frame
    };
    union {
        u32 word17C;             // 0x17C, zeroed as u32
        struct {
            s16 dashed;          // 0x17C, PH s16 0/1
            s16 shellFlags;      // 0x17E, PH s16 bits 1, 2
        };
    };
    u32 word180;                 // 0x180, zeroed only
    u8 pad184[0x188 - 0x184];    // 0x184
} PartyWorkNokonoko;

typedef struct PartyWorkBomhei { // party_bomhei.c
    u8 pad174[0x178 - 0x174];    // 0x174
    s16 timer;                   // 0x178
    u8 state;                    // 0x17A, 10/20/30/40/100...
    u8 syncFrame;                // 0x17B, index into m_w_7_sync
    s32 unk17C;                  // 0x17C, init -1
    s32 sfxId;                   // 0x180, fuse sfx (0x93C)
    s32 sfxId2;                  // 0x184, sfx 0x93D
} PartyWorkBomhei;

typedef struct PartyWorkCloud {  // party_cloud.c
    s32 unk174;                  // 0x174, zeroed in cloud_init only
    struct EffectEntry* breathEffect; // 0x178, KumokumoN64 breath cloud (zeroed as s32 too)
    union {
        f32 hoverAngle;          // 0x17C, cloud_hover_*: -= hoverSpeed, revise360
        s32 hoverAngleBits;      // 0x17C, zeroed as s32 (cloud_init, N__cloud_use)
    };
    union {
        f32 hoverSpeed;          // 0x180, 4.25
        s32 hoverSpeedBits;      // 0x180, zeroed as s32
    };
    s32 lockAnims;               // 0x184, US N_cloudLockAnimationsOn/Off (unused on JP)
} PartyWorkCloud;

typedef struct PartyWorkVivian { // party_vivian.c
    f32 shadowSize;              // 0x174, 10..20; party.c reads it as the in-use shadow size
    u8 pad178[0x17C - 0x178];    // 0x178
    f32 followOfs;               // 0x17C, 0..-13, movePos distance behind Mario
    u8 pad180[0x182 - 0x180];    // 0x180
    s16 marioAnimTime;           // 0x182, local time for Mario's paper anim while hidden
    struct EffectEntry* rippleEffect; // 0x184, effRippleEntry; NULLed when the effect dies (flags == 0)
} PartyWorkVivian;

typedef union PartyWork {
    PartyWorkCommon common;
    PartyWorkYoshi yoshi;
    PartyWorkNokonoko nokonoko;
    PartyWorkBomhei bomhei;
    PartyWorkCloud cloud;
    PartyWorkVivian vivian;
} PartyWork;

typedef struct PartyEntry {
    u32 flags;                   // 0x0
    u32 flags2;                  // 0x4
    u32 field_8;                 // 0x8
    s32 paperAnimGroup;          // 0xC
    s32 field_10;                // 0x10
    s32 paperPoseId;             // 0x14
    char* animName;              // 0x18, current pose name (strcmp'd with "PYS_S_2" etc.)
    u32 field_1C;                // 0x1C, unsigned
    u16 field_20;                // 0x20
    u8 field_22[0x24 - 0x22];    // 0x22
    s32 moveFrames;              // 0x24, frames left in a move/jump (16 at jump start)
    s16 field_28;                // 0x28
    s16 unk2A;                   // 0x2A
    s8 unk2C;                    // 0x2C
    s8 unk2D;                    // 0x2D
    s8 unk2E;                    // 0x2E, direction kind (1/4) switched on by partyChgPose*
    s8 currentSlotId;            // 0x2F
    s8 port;                     // 0x30, controller port (partyUpdateKeyData)
    s8 currentMemberId;          // 0x31, PartyMembers
    u8 moveKind;                 // 0x32, 1 = flying partner (cloud, vivian); was field_32[0] in evt_mario
    u8 memberKind;               // 0x33, set by each *_init to its PartyMember id (kuribo 1, nokonoko 2, yoshi 4, cloud 5, vivian 6)
    u8 runMode;                  // 0x34, partyChgRunMode
    u8 prevRunMode;              // 0x35, saved by partyChgRunMode
    u8 field_36;                 // 0x36
    u8 field_37;                 // 0x37
    u8 field_38;                 // 0x38
    u8 useMotionId;              // 0x39
    u8 field_3A;                 // 0x3A
    u8 field_3B;                 // 0x3B
    u8 field_3C;                 // 0x3C
    u8 field_3D;                 // 0x3D
    u8 unk3E;                    // 0x3E
    s8 unk3F;                    // 0x3F
    f32 unk40;                   // 0x40
    u32 unk44;                   // 0x44
    u8 field_48[0x4C - 0x48];    // 0x48
    s8 unk4C;                    // 0x4C
    u8 field_4D[0x4F - 0x4D];    // 0x4D
    s8 field_4F;                 // 0x4F, vivian: bit 0 = tail off (VivianTail bitfield)
    u8 field_50[0x51 - 0x50];    // 0x50
    s8 unk51;                    // 0x51
    s16 unk52;                   // 0x52
    f32 unk54;                   // 0x54
    Vec position;                // 0x58
    union {
        Vec rot;                 // 0x64, same layout as MarioWork.rot
        struct {
            u8 field_64[0x6C - 0x64]; // 0x64
            f32 rotation;        // 0x6C, rot.z: degrees, fmod 360
        };
    };
    Vec scale;                   // 0x70
    Vec dispOfs;                 // 0x7C, added to position when drawing (cloud hover bob, vivian sink)
    union {
        Vec rotOfs;              // 0x88, rotation pivot (MarioWork.rotOfs)
        struct {
            u8 field_88[0x8C - 0x88]; // 0x88
            f32 field_8C;        // 0x8C, half height times scale
            f32 unk90;           // 0x90
        };
    };
    Vec moveTarget;              // 0x94, move/jump destination (partyGetAppearPos)
    f32 unkA0;                   // 0xA0
    u8 field_A4[0xA8 - 0xA4];    // 0xA4
    f32 unkA8;                   // 0xA8
    union {
        Vec floorMove;           // 0xAC, movement from a moving floor (MarioWork.unk174)
        struct {
            f32 field_AC;        // 0xAC
            f32 unkB0;           // 0xB0
            f32 field_B4;        // 0xB4
        };
    };
    Vec field_B8;                // 0xB8
    union {
        Vec groundRot;           // 0xC4, floor normal as x/z rotation angles (partyNrmSet)
        struct {
            u8 field_C4[0xC8 - 0xC4]; // 0xC4
            f32 unkC8;           // 0xC8
            f32 unkCC;           // 0xCC
        };
    };
    u8 field_D0[0xE0 - 0xD0];    // 0xD0
    f32 unkE0;                   // 0xE0
    f32 unkE4;                   // 0xE4
    f32 unkE8;                   // 0xE8
    f32 unkEC;                   // 0xEC
    f32 height;                  // 0xF0
    f32 width;                   // 0xF4
    f32 unkF8;                   // 0xF8
    f32 moveDir;                 // 0xFC, copied from targetDir when moving
    f32 targetDir;               // 0x100, angleABf from position to the move target
    f32 moveSpeed;               // 0x104, distance/18 etc.
    f32 unk108;                  // 0x108
    f32 displayDirection;        // 0x10C, copied from MarioWork displayDirection
    f32 displayDirectionTarget;  // 0x110, copied from MarioWork displayDirectionTarget
    f32 velY;                    // 0x114, vertical velocity; jump ends when <= 0
    f32 accelY;                  // 0x118, vertical acceleration (-dy at jump start, -1.6 when falling)
    f32 gravity;                 // 0x11C, subtracted from velY each frame (1.6 / 0.4)
    f32 unk120;                  // 0x120
    f32 unk124;                  // 0x124
    f32 moveDistance;            // 0x128, distABf to moveTarget; moveSpeed = moveDistance / moveFrames
    struct HitEntry* hitobjFront; // 0x12C, front wall (partySearchFrontWall)
    struct HitEntry* hitobjAction; // 0x130, object hit by the partner action (bomb rock, shell, case type 15)
    struct HitEntry* hitobjPush; // 0x134, front wall while moving
    struct HitEntry* field_138;  // 0x138, hit object stood on
    struct HitEntry* hitobjJumpFrom; // 0x13C, field_138 at jump start
    struct HitEntry* hitobjHead; // 0x140, ceiling (partySearchHead)
    void* field_144;             // 0x144
    s32 unk148;                  // 0x148
    u8 field_14C[0x150 - 0x14C]; // 0x14C
    u16 buttonHold;              // 0x150, partyUpdateKeyData: gp->button
    u16 buttonTrg;               // 0x152, gp->buttonNew
    u16 buttonRep;               // 0x154, gp->buttonRepeat
    u16 buttonUp;                // 0x156, gp->buttonUp
    s8 stickX;                   // 0x158
    s8 stickY;                   // 0x159, negated
    s8 subStickX;                // 0x15A
    s8 subStickY;                // 0x15B, negated
    s8 triggerL;                 // 0x15C
    s8 triggerR;                 // 0x15D
    s8 unk15E;                   // 0x15E
    s8 unk15F;                   // 0x15F
    MarioWork* playerPtr;        // 0x160
    s32 camId;                   // 0x164
    u32 yoshiPsndSFXId;          // 0x168
    s32 unk16C;                  // 0x16C
    void* useStruct;             // 0x170, per-partner heap work (PartyCloud*, YoshiWork*, ...)
    PartyWork work;              // 0x174, per-partner scratch views
} PartyEntry; // size 0x188

PartyEntry* partyGetPtr(s32 index);
void partyCtrlOn(PartyEntry* party);
void partyCtrlOff(PartyEntry* party);
PartyEntry* anotherPartyGetPtr(s32 index);
BOOL partyPaperOn(PartyEntry* party, const char* animName);

void L_partyClearCont(PartyEntry* party);
extern s32 partyCtrlNo;
f32 partyGetHeight(PartyEntry* party);
void partyInitCamId(PartyEntry* party);
void partyKeyOff(void);
void partyKeyOn(void);
void partyRestoreRunMode(PartyEntry* party);
void partyRun(PartyEntry* party);
void partyStop(PartyEntry* party);
void party_force_ride_yoshi(PartyEntry* party);
void party_ride_yoshi_force_move(void);

extern char* yoshigroup[7];
