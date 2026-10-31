// Declares the damage and counterattack work structures and the damage functions.
#pragma once

#include <dolphin/types.h>

struct BattleUnit;
struct BattleUnitPart;
struct BattleWeapon;

// Damage codes. BattleCheckDamage takes DAMAGE_FLAG_* bits from the attack script and builds the code it passes to
// BattleDamageDirect and BattleRunHitEvent; the target keeps it in BattleUnit.damageCode, which scripts read with
// btlevtcmd_GetDamageCode (the low byte, DAMAGE_HIT_*) and btlevtcmd_CheckDamageCode (any bits).
typedef enum BattleDamageCode {
    DAMAGE_HIT_STATUS_ONLY = 0x16, // no damage, but a status took hold
    DAMAGE_HIT_NORMAL = 0x17,
    DAMAGE_HIT_FIRE = 0x18,
    DAMAGE_HIT_EXPLOSION = 0x19,
    DAMAGE_HIT_ICE = 0x1A,
    DAMAGE_HIT_ELECTRIC = 0x1B,
    DAMAGE_HIT_FRIGHT = 0x1C,     // Fright landed
    DAMAGE_HIT_GALE_FORCE = 0x1D, // Gale Force landed
    DAMAGE_HIT_NONE = 0x1E,       // no damage and no status
    DAMAGE_HIT_SUPERGUARDED = 0x2A,
    DAMAGE_HIT_COUNTER_TOP_SPIKY = 0x2B, // 0x2B-0x36: the attacker is hurt by the target's counter (BattleCheckCounter)
    DAMAGE_HIT_COUNTER_PREEMPTIVE_SPIKY = 0x2C,
    DAMAGE_HIT_COUNTER_FRONT_SPIKY = 0x2D,
    DAMAGE_HIT_COUNTER_FIERY = 0x2E,
    DAMAGE_HIT_COUNTER_ICY = 0x2F,
    DAMAGE_HIT_COUNTER_ELECTRIC = 0x30,
    DAMAGE_HIT_COUNTER_EXPLOSIVE = 0x31,
    DAMAGE_HIT_COUNTER_VOLATILE_EXPLOSIVE = 0x32,
    DAMAGE_HIT_COUNTER_POISON = 0x33,
    DAMAGE_HIT_COUNTER_ELECTRIFIED = 0x34, // the target is electrified (status or part)
    DAMAGE_HIT_COUNTER_PAYBACK = 0x35,     // Payback status or the Return Postage badge
    DAMAGE_HIT_COUNTER_HOLD_FAST = 0x36,
    DAMAGE_HIT_SUPERGUARD_COUNTER = 0x37, // the attacker hit back by a Superguard (also used by a few items)
    DAMAGE_HIT_MASK = 0xFF,

    DAMAGE_FLAG_LAST_HIT = 0x100,        // the last (or only) hit of the move: it can knock out and inflict status
    DAMAGE_FLAG_KO = 0x200,              // the hit took the target to 0 HP
    DAMAGE_FLAG_DEFEATED = 0x400,        // ... and the target is out (a reviving unit only from fire or explosions)
    DAMAGE_FLAG_LIFE_SHROOM = 0x800,     // ... and a Life Shroom will revive it
    DAMAGE_FLAG_GUARDING = 0x1000,       // the target used the Defend command
    DAMAGE_FLAG_HEAL = 0x2000,           // the target absorbs the hit as healing (defense attribute 3)
    DAMAGE_FLAG_BACKFIRE = 0x4000,       // btldefaultevt_Damage then runs _backfire; nothing in the damage code sets it
    DAMAGE_FLAG_SHATTER = 0x8000,        // the frozen target shatters (never happens: the chance is 0)
    DAMAGE_FLAG_AC_SUCCESS = 0x20000,    // the attacker's action command succeeded
    DAMAGE_FLAG_GUARDED = 0x40000,       // the target guarded (A at the right time)
    DAMAGE_FLAG_SUPERGUARDED = 0x80000,  // the target superguarded (B at the right time)
    DAMAGE_FLAG_ALWAYS_HIT = 0x100000,   // no luck badge, Dodgy or accuracy roll (BattlePreCheckDamage)
    DAMAGE_FLAG_FLIPPED = 0x200000,      // a shelled or bomb-flippable part was flipped
    DAMAGE_FLAG_GROUNDED = 0x400000,     // a winged part was knocked down
    DAMAGE_FLAG_ATTACK_FX_R = 0x1000000, // 0x1000000-0x10000000: the hit sound of the chosen Attack FX badge
    DAMAGE_FLAG_ATTACK_FX_Y = 0x2000000, // (the demo plays B, G and Y for these three)
    DAMAGE_FLAG_ATTACK_FX_B = 0x4000000,
    DAMAGE_FLAG_ATTACK_FX_G = 0x8000000,
    DAMAGE_FLAG_ATTACK_FX_P = 0x10000000,
    DAMAGE_FLAG_NO_STATUS = 0x20000000,      // the weapon's statuses are not applied
    DAMAGE_FLAG_STATUS_ANY_HIT = 0x40000000, // the statuses are applied on every hit, not only the last
    DAMAGE_FLAG_PIERCE_IMMUNE = 0x80000000,  // hurts parts whose defense attribute is 4 (immune to other hits)
} BattleDamageCode;

// BattleSetStatusDamage result bits.
typedef enum BattleStatusResult {
    STATUS_RESULT_AILMENT = 0x1, // a status with turns that counts as a hit (DAMAGE_HIT_NORMAL)
    STATUS_RESULT_OTHER = 0x2,   // a buff or a status without turns (DAMAGE_HIT_STATUS_ONLY)
    STATUS_RESULT_FRIGHT = 0x4,
    STATUS_RESULT_GALE_FORCE = 0x8,
    STATUS_RESULT_INSTANT_KILL = 0x10,
    STATUS_RESULT_SLEEP = 0x20, // the target fell asleep: the hit does not wake it
} BattleStatusResult;

// BattleCheckCounter result: what the target's counter attributes do back to the attacker.
typedef struct CounterWork {
    s32 noHazard;        // 0x0, 1 until a spike/fire/ice/electric counter hits
    s32 payback;         // 0x4, poison counter or Payback: half the damage back
    s32 inflictBurn;     // 0x8
    s32 inflictPoison;   // 0xC
    s32 inflictElectric; // 0x10
    s32 inflictFreeze;   // 0x14
    s32 holdFast;        // 0x18
    s32 returnPostage;   // 0x1C
    s32 type;            // 0x20
    u32 msg;             // 0x24
    s32 count;           // 0x28
    u32 hitEvent;        // 0x2C, hit event run on the target
} CounterWork;

typedef struct BattleVulnerableStatus {
    u8 sleepRate;       // 0x0
    u8 stopRate;        // 0x1
    u8 dizzyRate;       // 0x2
    u8 poisonRate;      // 0x3
    u8 confuseRate;     // 0x4
    u8 electricRate;    // 0x5
    u8 burnRate;        // 0x6
    u8 freezeRate;      // 0x7
    u8 hugeRate;        // 0x8
    u8 tinyRate;        // 0x9
    u8 attackUpRate;    // 0xA
    u8 attackDownRate;  // 0xB
    u8 defenseUpRate;   // 0xC
    u8 defenseDownRate; // 0xD
    u8 allergicRate;    // 0xE
    u8 frightRate;      // 0xF
    u8 galeForceRate;   // 0x10
    u8 fastRate;        // 0x11
    u8 slowRate;        // 0x12
    u8 dodgyRate;       // 0x13
    u8 invisibleRate;   // 0x14
    u8 instaKillRate;   // 0x15
} BattleVulnerableStatus;

s32 BattleCheckDamage(struct BattleUnit* unit1, struct BattleUnit* unit2, struct BattleUnitPart* part, struct BattleWeapon* weapon, s32 flags);

struct BattleWork;

void BattleInitCounterPreCheckWork(CounterWork* work);
s32 BattleCheckCounter(CounterWork* work, struct BattleUnit* attacker, struct BattleUnit* target, struct BattleUnitPart* part, struct BattleWeapon* weapon, u32* flags);
s32 BattlePreCheckDamage(struct BattleUnit* attacker, struct BattleUnit* target, struct BattleUnitPart* part, struct BattleWeapon* weapon, u32 flags);
void BattleAttackDeclare(s32* unitIdx, s32* partIdx);
void BattleAttackDeclareAll(struct BattleWork* wp);
void BattleDamageDirect(s32 unitId, struct BattleUnit* target, struct BattleUnitPart* part, s32 damage, s32 fpDamage, u32 result, u32 pattern, s32 flag);
s32 BattleSetStatusDamageFromWeapon(struct BattleUnit* attacker, struct BattleUnit* target, struct BattleUnitPart* part, struct BattleWeapon* weapon, u32 flags);
