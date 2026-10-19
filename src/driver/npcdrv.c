#define npcCheckInterrupt npcCheckInterrupt_hdr_void
#include "driver/npcdrv.h"
extern const char str_802C2FC8[];
extern const char str_802C2FE4[];
extern const char str_802C3000[];
extern const char str_802C301C[];
extern const char str_802C3038[];
extern const char str_802C3054[];
extern const char str_802C3070[];
extern const char str_802C308C[];
extern const char str_802C30A8[];
extern const char str_802C30C4[];
extern const char str_802C30E0[];
extern const char str_802C30F0[];
extern const char str_802C30FC[];
extern const char str_802C3104[];
extern const char str_802C310C[];
extern const char str_802C3128[];
extern const char str_802C3158[];
extern const char str_802C3168[];
extern const char str_802C317C[];
extern const char str_802C3198[];
extern const char str_802C31C0[];
extern const char str_802C31CC[];
extern const char str_802C31E0[];
#undef npcCheckInterrupt
BOOL npcCheckInterrupt(NpcEntry* npc);
#include "dolphin/gx/GXStruct.h"
#include "driver/animdrv.h"
#include "driver/msgdrv.h"
#include "driver/windowdrv.h"
#include "manager/fontmgr.h"
#include "mario/mario_party.h"
#include "party.h"
#include "driver/swdrv.h"
#include "data/mapdata.h"
#include "driver/effdrv.h"
#include "driver/hitdrv.h"
#include "driver/itemdrv.h"
#include "eff/eff_majinai.h"
#include "evt/evt_cmd.h"
#include "evt/evt_snd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_pouch.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include "driver/dispdrv.h"
#include "driver/offscreendrv.h"
#include "driver/seqdrv.h"
#include "battle/battle_information.h"
#include <string.h>
#ifndef NONMATCHING
__declspec(section ".rodata") extern const f32 vec3_802c2f78[3];
__declspec(section ".rodata") extern const f32 vec3_802c2f84[3];
__declspec(section ".rodata") extern const f32 vec3_802c2f90[3];
__declspec(section ".rodata") extern const u32 dat_802c2f9c[11];
__declspec(section ".rodata") extern const u32 gap_04_802C3134_rodata;
__declspec(section ".rodata") extern const f64 double_0p5_802c3138;
__declspec(section ".rodata") extern const f64 double_3_802c3140;
__declspec(section ".rodata") extern const f64 double_0_802c3148;
__declspec(section ".rodata") extern const f64 double_to_int_802c3150;
__declspec(section ".rodata") extern const f64 double_to_int_mask_802c31b8;
__declspec(section ".rodata") extern const f64 double_0p75_802c31d8;
__declspec(section ".sdata2") extern const u32 dat_80419b88;
__declspec(section ".sdata2") extern const u32 dat_80419b8c;
__declspec(section ".sdata2") extern const u32 dat_80419b90;
__declspec(section ".sdata2") extern const u32 dat_80419b94;
__declspec(section ".sdata2") extern const u32 dat_80419b98;
__declspec(section ".sdata2") extern const f32 float_0_80419b9c;
__declspec(section ".sdata2") extern const f32 float_0p5_80419ba0;
__declspec(section ".sdata2") extern const f32 float_60_80419ba4;
__declspec(section ".sdata2") extern const f32 float_365_80419ba8;
__declspec(section ".sdata2") extern const f32 float_16_80419bac;
__declspec(section ".sdata2") extern const f32 float_0p8_80419bb0;
__declspec(section ".sdata2") extern const f32 float_1_80419bb4;
__declspec(section ".sdata2") extern const f32 float_10_80419bb8;
__declspec(section ".sdata2") extern const f32 float_11_80419bbc;
__declspec(section ".sdata2") extern const f32 float_12_80419bc0;
__declspec(section ".sdata2") extern const f32 float_15_80419bc4;
__declspec(section ".sdata2") extern const f32 float_1000_80419bc8;
__declspec(section ".sdata2") extern const f32 float_1p5_80419bcc;
__declspec(section ".sdata2") extern const f32 float_90_80419bd0;
__declspec(section ".sdata2") extern const f32 float_30_80419bd4;
__declspec(section ".sdata2") extern const f32 float_neg90_80419bd8;
__declspec(section ".sdata2") extern const f32 float_rad2deg_80419bdc;
__declspec(section ".sdata2") extern const f32 float_360_80419be0;
__declspec(section ".sdata2") extern const f32 float_270_80419be4;
__declspec(section ".sdata2") extern const f32 float_neg270_80419be8;
__declspec(section ".sdata2") extern const f32 float_180_80419bec;
__declspec(section ".sdata2") extern const f32 float_neg180_80419bf0;
__declspec(section ".sdata2") extern const f32 float_0p75_80419bf4;
__declspec(section ".sdata2") extern const f32 float_neg1_80419bf8;
__declspec(section ".sdata2") extern const f32 float_0p1_80419bfc;
__declspec(section ".sdata2") extern const f32 float_20_80419c00;
__declspec(section ".sdata2") extern const f32 float_3p2_80419c04;
__declspec(section ".sdata2") extern const f32 float_3_80419c08;
__declspec(section ".sdata2") extern const f32 float_neg600_80419c0c;
__declspec(section ".sdata2") extern const f32 float_600_80419c10;
__declspec(section ".sdata2") extern const f32 float_0p2_80419c14;
__declspec(section ".sdata2") extern const f32 float_100_80419c18;
__declspec(section ".sdata2") extern const f32 float_0p4_80419c1c;
__declspec(section ".sdata2") extern const f32 float_45_80419c20;
__declspec(section ".sdata2") extern const f32 float_neg980_80419c24;
__declspec(section ".sdata2") extern const f32 float_0p15_80419c28;
__declspec(section ".sdata2") extern const f32 float_neg1000_80419c2c;
__declspec(section ".sdata2") extern const f32 float_5_80419c30;
__declspec(section ".sdata2") extern const f32 float_40_80419c34;
__declspec(section ".sdata2") extern const f32 float_6p2832_80419c38;
__declspec(section ".sdata2") extern const f32 float_0p00761_80419c3c;
__declspec(section ".sdata2") extern const f32 float_0p16605_80419c40;
__declspec(section ".sdata2") extern const f32 float_3p1416_80419c44;
__declspec(section ".sdata2") extern const f32 float_1p5708_80419c48;
__declspec(section ".sdata2") extern const f32 float_4p7124_80419c4c;
__declspec(section ".sdata2") extern const f32 float_0p03705_80419c50;
__declspec(section ".sdata2") extern const f32 float_0p4967_80419c54;
__declspec(section ".sdata2") extern const f32 float_4_80419c58;
__declspec(section ".sdata2") extern const f32 float_2_80419c5c;
__declspec(section ".sdata2") extern const f32 float_160_80419c60;
__declspec(section ".sdata2") extern const char str_80419C64[];
__declspec(section ".sdata2") extern const char str_80419C6C[];
__declspec(section ".sdata2") extern const f32 float_1E06_80419c74;
__declspec(section ".sdata2") extern const f32 float_0p05_80419c78;
__declspec(section ".sdata2") extern const f32 float_0p25_80419c7c;
__declspec(section ".sdata2") extern const f32 float_neg2_80419c80;
__declspec(section ".sdata2") extern const f32 float_5000_80419c84;
__declspec(section ".sdata2") extern const f32 float_10000_80419c88;
__declspec(section ".sdata2") extern const f32 float_1p33_80419c8c;
__declspec(section ".sdata2") extern const char str_80419C90[];
__declspec(section ".sdata2") extern const char str_80419C98[];
__declspec(section ".sdata2") extern const f32 float_deg2rad_80419ca0;
__declspec(section ".sdata2") extern const u32 gap_09_80419CA4_sdata2;
#define EXT_LIT(sym, val) (sym)

#endif

extern GlobalWork* gp;
extern NpcTribeInfo npcTribe[];

f32 cloudGetBreathPower(Vec pos, f32 width);
BOOL kpaMutekiCheck(void);
void kpaAddScorePos(s32 score, Vec* pos);
s32 kpaEnemyHitChk(f32 x, f32 y, f32 z, f32 height, f32 width);
void kpaPowDown(void);
void FontDrawEdge(void);
void marioChkWallAround(Vec* pos, s32 a1, f32 a2, f32 angle, f32 radius, f32 height);
#ifdef NONMATCHING
static inline f32 npc_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } return a; }
static inline f32 npc_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; } return a; }
#endif
void FontDrawScale(f32 scale);
void FontDrawStringShake(f32 x, f32 y, const char* message);

#define NPC_RAD2DEG(r) ((r) * 57.29579f)
extern int __float_nan[];
#ifdef NONMATCHING
static inline s32 npc_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 npc_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * (0.5 * guess * (3.0 - guess * guess * x)); } else if (x < 0.0) { return *(f32*)__float_nan; } else if (npc_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
USER_FUNC(btlevtcmd_ftomsec);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_msg_print);
#endif
#ifndef NONMATCHING
s32 btlevtcmd_ftomsec(EventEntry* event, BOOL isFirstCall);
s32 evt_mario_get_pos(EventEntry* event, BOOL isFirstCall);
s32 evt_msg_print(EventEntry* event, BOOL isFirstCall);
#endif

typedef struct NpcWork2 {
    NpcWork field;  // 0x0
    NpcWork battle; // 0x14
} NpcWork2;

//.data
char* luigi_pose[14][2] = { { "Z_1", "Z_1R" }, { "S_1", "S_1R" },   { "W_1", "W_1R" },   { "R_1", "R_1R" },
                            { "T_1", "T_1R" }, { "J_1A", "J_1RR" }, { "J_1B", "J_1BR" }, { "Z_2", "Z_2R" },
                            { "S_2", "S_2R" }, { "T_2", "T_2R" },   { "L_1", "L_1R" },   { "L_2", "L_2R" },
                            { "L_3", "L_3R" }, { "I_1", "I_1R" } };

//.sdata
#ifdef NONMATCHING
char MarioStayPose[32] = "KPA_S_1";
char MarioTalkPose[32] = "KPA_T_1";
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") char MarioStayPose[32] = "KPA_S_1";
__declspec(section ".sdata") char MarioTalkPose[32] = "KPA_T_1";
#endif

//.sbss
BOOL dbg_battleskip = 0;
u32 npcMainCount = 0;
NpcFieldEntry* release_wp = NULL;
#pragma force_active on
u32 gap_08_804186C4_sbss;
#pragma force_active reset
static NpcWork2 work;

// local prototypes
void mtx_setup(NpcEntry* entry, Mtx mtx, s32 history);
void npcDisp_xlu(CameraId cameraId, void* param);
void npcDisp(CameraId camId, void* param);
void npcDisp_offscreen_xlu(CameraId camId, void* param);
void npcDisp_offscreen(CameraId camId, void* param);
void npcDisp_blur(CameraId camId, void* param);
void _npcDeleteGroup(NpcEntry* entry);

#define npcGetWorkPtr2(inBattle) ((inBattle) ? &work.battle : &work.field)
// TODO: inlining?
#define npcGetWorkPtrInline() (gp->inBattle ? &work.battle : &work.field)

// TODO: inlining?
#ifndef NONMATCHING
NpcWork* npcGetWorkPtr(void);

void npcReleaseFieldNpc(void);

void npcRecoveryFieldNpc(void);

void GXClearBoundingBox(void);
void GXReadBoundingBox(u16* left, u16* top, u16* right, u16* bottom);
void PSMTX44MultVec(const Mtx44 m, const Vec* src, Vec* dst);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXIdentity(Mtx m);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScaleApply(const Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
f32 PSVECDistance(const Vec* a, const Vec* b);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
int __cvt_sll_flt();
int __div2i();
CameraEntry* camGetCurPtr(void);
CameraEntry* camGetPtr(CameraId cameraId);
EffectEntry* effSmallStarEntry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5, f32 arg6,
                               f32 arg7);
int itemEntry();
int itemFlagOn();
void *memset(void *dest, int ch, size_t count);
int partyChgPoseId();
s32 psndSFXOn_3D(const char* name, Vec* position);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
void BattleMajinaiDone(void);
BOOL N_itemPickUpFromFieldCheck(void);
void _npcDead(NpcEntry* npc, s32 reason);
void _npcGroupDead(NpcEntry* entry, s32 reason);
NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle);
NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r);
void animPoseVivianMain(s32 poseId, Vec* pos);
double atan2(double y, double x);
void fbatBattleMode(void);
void fbatEncountCheck(void);
void* fbatHitCheck(u32 flags, void* a1);
void fbatTalkMode(void);
s32 kpaFireAttackCheck(void);
s32 kpaJumpChk(void);
void marioChgMotJump2(void);
void marioChgMoveMotion(void);
BOOL marioChkTalkable(void);
f32 marioGetAngleKaitenHammer(void);
f32 marioGetDispDir(void);
s32 marioGetJabaraState(void);
s32 nokonokoGetStatus(PartyEntry* party);
BOOL npcCheckHitMarioSide(NpcEntry* npc);
HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz);
void npcKoopaModeEncountCheck(void);
void npcMoveG(NpcEntry* npc);
s32 shadowEntry(f32 x, f32 y, f32 z, f32 size);
void shadowSetCollision(s32 shadow, s32 val);
f32 sinfd(f32 degrees);
s32 vivianGetStatus(void);
void mtx_setup(NpcEntry* entry, Mtx mtx, s32 history);

double atan2(double y, double x);



void npcDisp_xlu(CameraId cameraId, void* param);

void npcDisp(CameraId camId, void* param);

void npcDisp_offscreen_xlu(CameraId camId, void* param);

void npcDisp_offscreen(CameraId camId, void* param);

#pragma opt_propagation off
#pragma opt_lifetimes off

void npcDisp_blur(CameraId camId, void* param);
#pragma opt_propagation reset
#pragma opt_lifetimes reset

void npcInit(void);

void npcReset(BOOL inBattle);

s32 npcGetReactionOfLivingBody(BOOL inBattle);

// TODO: fix entry->position delayed set-Vec with r6/r30
// TODO: a1 is desc/ription?
s32 npcEntry(const char* a1, const char* animName);

static const Vec sZeroVec3 = {0.0f, 0.0f, 0.0f};

NpcTribeInfo* npcGetTribe(const char* tribeName);

void npcDelete(NpcEntry* entry);

void _npcDeleteGroup(NpcEntry* entry);

void npcDeleteGroup(NpcEntry* entry);

void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param);
void fbatEncountCheck(void);
void fbatTalkMode(void);
void fbatBattleMode(void);
s32 kpaJumpChk(void);
s32 kpaFireAttackCheck(void);

void npcMoveG(NpcEntry* npc);
BOOL npcCheckHitMarioSide(NpcEntry* npc);
HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz);
s32 vivianGetStatus(void);
#define NPC_CHKMARIO(ok) do {     m = marioGetPtr();     if (*(u32*)m & 0x82000000) { ok = 0; break; }     if (*(u32*)m & 0xA) { ok = 0; break; }     if (*(s32*)((u8*)gp + 0x164) != 0) { ok = 0; break; }     if (seqGetSeq() != 2) { ok = 0; break; }     if (*(u16*)((u8*)m + 0x2E) == 0x19) { ok = 0; break; }     if (vivianGetStatus() != 0 && vivianGetStatus() != 1) { ok = 0; } else { ok = 1; } } while (0)
void shadowSetCollision(s32 shadow, s32 val);
s32 shadowEntry(f32 x, f32 y, f32 z, f32 size);
void animPoseVivianMain(s32 poseId, Vec* pos);
f32 sinfd(f32 degrees);
void npcKoopaModeMain(void);
BOOL npcCheckBlow(NpcEntry* npc);
void npcMain(void);

NpcEntry* npcNameToPtr(const char* name);

NpcEntry* npcNameToPtr_NoAssert(const char* name);

void npcSetMarioAutoTalkPose(const char* stayPose, const char* talkPose);

#pragma opt_propagation off
#pragma opt_lifetimes off
void npcSetTalkPose(const char* name);

void npcSetStayPose(const char* name);

BOOL npcCheckHitMarioSide(NpcEntry* npc);
#pragma opt_propagation reset
#pragma opt_lifetimes reset

void npcMoveG(NpcEntry* npc);

void npcTuningRy(NpcEntry* npc, f32 angle);

f32 npcTransRytoFaceDir(NpcEntry* npc);


HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz);

NpcEntry* npcNearDistCheck(f32 x, f32 y, f32 z, f32 range);

FieldBattleData* fbatGetPointer(void);

void fbatChangeMode(s16 mode);

void fbatSetAttackAnnounce(s32 a1);

void fbatSetAttackAnnounceEnable(void);


void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param);

#define FBAT_SUB(d) (((u8*)(d))[2])
#define FBAT_NPC(d) (*(NpcEntry**)((u8*)(d) + 4))
#define FBAT_EVTID(d) (*(s32*)((u8*)(d) + 0xC))

void partyKeyOn(void);
void partyKeyOff(void);
void marioChgTalkMotion(void);
void marioChgStayMotion(void);
BOOL marioChkTalkable(void);
void* fbatHitCheck(u32 flags, void* a1);

#include "eff/eff_small_star.h"
s32 _majinai_effect(EventEntry* event, BOOL isFirstCall);
s32 _check(EventEntry* event, BOOL isFirstCall);
s32 marioStGetSystemLevel(void);
BOOL N_itemPickUpFromFieldCheck(void);
void marioChgMotJump2(void);
f32 marioGetDispDir(void);
void npcKoopaModeEncountCheck(void);



void fbatEncountCheck(void);

void fbatTalkMode(void);

#define FBAT_U32(d, off) (*(u32*)((u8*)(d) + (off)))
#define NPC_ENEMY_LEVEL(npc) (*(u8*)((u8*)*(void**)(npc)->battleInfo.groupSetup->enemyData + 0xE))

void BattleMajinaiDone(void);
extern s32 _evt_majinai_coin_up_effect[];
void marioChgMoveMotion(void);

void fbatBattleMode(void);

void _npcDead(NpcEntry* npc, s32 reason);

void _npcGroupDead(NpcEntry* entry, s32 reason);

void npcGroupDead(NpcEntry* entry, BOOL reason);

NpcEntry* fbatNpcTalkCheck(void);

void fbatHitCheckAll(void);

#define FH(p, off, T) (*(T*)((u8*)(p) + (off)))

typedef struct FbatHitResult {
    u32 kind;   // 0x0
    s32 evtId;  // 0x4
    f32 dist;   // 0x8
    u32 bits; // 0xC
} FbatHitResult;

s32 vivianGetStatus(void);
s32 marioGetJabaraState(void);
s32 nokonokoGetStatus(PartyEntry* party);
f32 marioGetAngleKaitenHammer(void);
NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r);
NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle);


#define FH_NPC_FILTER(f1000, bit)                                                    \
    if (npc == NULL) continue;                                                       \
    if (!(npc->flags & 2)) continue;                                                 \
    if (f1000) { if (!(npc->flags & 8)) continue; } else { if (npc->flags & 8) continue; } \
    if (soft && !(FH(npc, 0x4, u32) & (bit))) continue;                              \
    if (npc->flags & 0x20000000) continue;                                           \
    if (npc->flags & 0x20) continue;                                                 \
    if (FH(npc, 0x1D4, u32) & 4) continue;                                           \
    if (npc->flags & 0x08000000) continue;

#define FH_NPC_FILTER2(f1000, bit)                                                        if (npc == NULL) continue;                                                           if (!(npc->flags & 2)) continue;                                                     if (f1000) { if (!(npc->flags & 8)) continue; } else { if (npc->flags & 8) continue; }     if (soft && !(FH(npc, 0x4, u32) & (bit))) continue;                                  if (npc->flags & 0x20000000) continue;                                               if (npc->flags & 0x20) continue;                                                     if (npc->flags & 0x08000000) continue;                                               if (FH(npc, 0x1D4, u32) & 4) continue;

typedef struct { s32 v[11]; } SinTbl;
static const SinTbl sSinTbl = {{0, 0, 0, 0, 45, 60, 90, 100, 101, 101, 101}};

void* fbatHitCheck(u32 flags, void* a1);


NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r);

NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle);

BOOL npcCheckInterrupt(NpcEntry* npc);

static inline void npcRandField(NpcBattleInfo* info, NpcSetupBattleInfo* setup) {
    s32 i;
    for (i = 0; i < 16; i++) {
        info->field_B0[i] = (u8)setup->field_20[i][0] + irand(setup->field_20[i][1] - setup->field_20[i][0] + 1);
    }
}

void npcSetupBattleInfo(NpcEntry* npc, NpcSetupBattleInfo* setup);

void npcSetBattleInfo(NpcEntry* npc, s32 battleInfoId);

void npcStopForEvent(void);

void npcStopForOneEvent(NpcEntry* npc);

void npcStartForEvent(void);

void npcStartForOneEvent(NpcEntry* npc);

void npcSetColor(const char* name, GXColor color);

void npcBlurOn(const char* name);

void npcBlurOff(const char* name);

s32 npcGetBtlSetupWork(NpcEntry* npc, s32 index);

void npcSetBtlSetupWork(NpcEntry* npc, s32 index, s32 value);

void npcSetSlave(NpcEntry* npc, NpcEntry* slave, s32 id);

void npcSetLink(NpcEntry* npc, NpcEntry* other);

NpcTerritoryType dbGetDefData(NpcTerritoryInfo* info, const char* description);

void npcExecAllInitEvt(void);

BOOL npcWaitAllInitEvtEnd(void);

void npcExecAllReglEvt(void);

s32 _check(EventEntry* event, BOOL isFirstCall);

s32 _majinai_effect(EventEntry* event, BOOL isFirstCall);

EVT_BEGIN(evt_majinai_effect_se_fld)
    CALL(btlevtcmd_ftomsec, 29, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C2FC8), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 200, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C2FE4), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 90, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3000), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 80, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C301C), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 5, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3038), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_majinai_effect_se_btl)
    CALL(btlevtcmd_ftomsec, 29, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3054), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 200, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3070), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 90, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C308C), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 80, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C30A8), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 5, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C30C4), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(_evt_majinai_coin_up_effect)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    SPAWN_EVENT(evt_majinai_effect_se_fld)
    CALL(_majinai_effect)
    CALL(evt_msg_print, 0, PTR((char*)str_802C30E0), 0, 0)
    CALL(_check, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, PTR((char*)str_802C30F0), 0, 0)
    END_IF
    RETURN
EVT_END()

void npcGetBackItemEntry(NpcEntry* npc);

void npcClearDeadInfo(void);



void npcKoopaModeEncountCheck(void);

s32 npcKoopaModeMobjBoundDeadCheck(HitEntry* hit);

void fbatSandersBombTriggerOn(void);

s32 npcCalcScore(NpcEntry* npc);

BOOL npcCheckBlow(NpcEntry* npc);

BOOL N_fbatPreventMarioEventChk(void);

#pragma force_active on
__declspec(section ".data") u32 gap_05_8030543C_data[1] = {0};
#pragma force_active reset


// prototypes for asm stopgap forward references
BOOL N_fbatPreventMarioEventChk(void);
BOOL npcCheckBlow(NpcEntry* npc);
s32 npcCalcScore(NpcEntry* npc);
void fbatSandersBombTriggerOn(void);
s32 npcKoopaModeMobjBoundDeadCheck(HitEntry* hit);
void npcKoopaModeEncountCheck(void);
void npcClearDeadInfo(void);
void npcGetBackItemEntry(NpcEntry* npc);
s32 _majinai_effect(EventEntry* event, BOOL isFirstCall);
s32 _check(EventEntry* event, BOOL isFirstCall);
void npcExecAllReglEvt(void);
BOOL npcWaitAllInitEvtEnd(void);
void npcExecAllInitEvt(void);
NpcTerritoryType dbGetDefData(NpcTerritoryInfo* info, const char* description);
void npcSetLink(NpcEntry* npc, NpcEntry* other);
void npcSetSlave(NpcEntry* npc, NpcEntry* slave, s32 id);
void npcSetBtlSetupWork(NpcEntry* npc, s32 index, s32 value);
s32 npcGetBtlSetupWork(NpcEntry* npc, s32 index);
void npcBlurOff(const char* name);
void npcBlurOn(const char* name);
void npcSetColor(const char* name, GXColor color);
void npcStartForOneEvent(NpcEntry* npc);
void npcStartForEvent(void);
void npcStopForOneEvent(NpcEntry* npc);
void npcStopForEvent(void);
void npcSetBattleInfo(NpcEntry* npc, s32 battleInfoId);
void npcSetupBattleInfo(NpcEntry* npc, NpcSetupBattleInfo* setup);
BOOL npcCheckInterrupt(NpcEntry* npc);
NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle);
NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r);
void* fbatHitCheck(u32 flags, void* a1);
void fbatHitCheckAll(void);
NpcEntry* fbatNpcTalkCheck(void);
void npcGroupDead(NpcEntry* entry, BOOL reason);
void _npcGroupDead(NpcEntry* entry, s32 reason);
void _npcDead(NpcEntry* npc, s32 reason);
void fbatBattleMode(void);
void fbatTalkMode(void);
void fbatEncountCheck(void);
void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param);
void fbatSetAttackAnnounceEnable(void);
void fbatSetAttackAnnounce(s32 a1);
void fbatChangeMode(s16 mode);
FieldBattleData* fbatGetPointer(void);
NpcEntry* npcNearDistCheck(f32 x, f32 y, f32 z, f32 range);
HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz);
f32 npcTransRytoFaceDir(NpcEntry* npc);
void npcTuningRy(NpcEntry* npc, f32 angle);
void npcMoveG(NpcEntry* npc);
BOOL npcCheckHitMarioSide(NpcEntry* npc);
void npcSetStayPose(const char* name);
void npcSetTalkPose(const char* name);
void npcSetMarioAutoTalkPose(const char* stayPose, const char* talkPose);
NpcEntry* npcNameToPtr_NoAssert(const char* name);
NpcEntry* npcNameToPtr(const char* name);
void npcMain(void);
void npcDeleteGroup(NpcEntry* entry);
void _npcDeleteGroup(NpcEntry* entry);
void npcDelete(NpcEntry* entry);
NpcTribeInfo* npcGetTribe(const char* tribeName);
s32 npcEntry(const char* a1, const char* animName);
s32 npcGetReactionOfLivingBody(BOOL inBattle);
void npcReset(BOOL inBattle);
void npcInit(void);
void npcDisp_blur(CameraId camId, void* param);
void npcDisp_offscreen(CameraId camId, void* param);
void npcDisp_offscreen_xlu(CameraId camId, void* param);
void npcDisp(CameraId camId, void* param);
void npcDisp_xlu(CameraId cameraId, void* param);
void mtx_setup(NpcEntry* entry, Mtx mtx, s32 history);
void npcRecoveryFieldNpc(void);
void npcReleaseFieldNpc(void);
NpcWork* npcGetWorkPtr(void);

static inline void npcStopForOneEvent__af_inl(NpcEntry* npc) {
    if (npc && npc->flags & 2 && npc->flags & 0x10000000) {
        npc->jumpFlags |= 0x10000;
        evtStopID(npc->regularEvtId);
        animPoseSetLocalTimeRate(npc->poseId, EXT_LIT(float_0_80419b9c, 0.0f));
    }
}
static inline void npcStartForOneEvent__af_inl(NpcEntry* npc) {
    if (npc && npc->flags & 2 && npc->flags & 0x10000000 && npc->jumpFlags & 0x10000) {
        npc->jumpFlags &= ~0x10000;
        evtStartID(npc->regularEvtId);
        animPoseSetLocalTimeRate(npc->poseId, EXT_LIT(float_1_80419bb4, 1.0f));
    }
}

void fbatSandersBombTriggerOn(void) {
    gp->fbatData->sandersBombTrigger = TRUE;
}

s32 npcCalcScore(NpcEntry* npc) {
    FieldBattleData* data = gp->fbatData;
    s32 score = 300;
    Vec pos = npc->position;

    pos.y += npc->tribe->height;
    if (npc->koopaEncounterType == 0x10) {
        score = 0;
    } else {
        if (npc->koopaEncounterType == 8) {
            score = 400;
        }
        if (kpaMutekiCheck()) {
            score += 100;
        }
        if (npc->koopaEncounterType == 2) {
            data->field_574++;
            score *= data->field_574;
        }
        if (npc->koopaEncounterType == 1) {
            data->field_578++;
            data->field_57C += score;
        }
        if (score > 9999) {
            score = 10000;
        }
    }
    if (score > 0) {
        kpaAddScorePos(score, &pos);
    }
    return score;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
BOOL npcCheckBlow(NpcEntry* npc) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0x93E1003C
		opword 0x7C7F1B78
		opword 0x80630000
		opword 0x54600085
		opword 0x4182000C
		opword 0x38600000
		opword 0x48000108
		opword 0x546006B5
		opword 0x4182000C
		opword 0x38600000
		opword 0x480000F8
		opword 0x80BF008C
		opword 0x38610020
		opword 0x809F0090
		opword 0x801F0094
		opword 0x90A1002C
		opword 0x90A10020
		opword 0x90810024
		opword 0x90010028
		opword 0x90810030
		opword 0xC03F014C
		opword 0x90010034
		bl cloudGetBreathPower
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38600001
		opword 0x480000B4
		opword 0x801F0090
		opword 0x38610014
		opword 0x80BF008C
		opword 0x90010030
		opword 0x809F0094
		opword 0xC05F0150
		lfs f1, float_0p5_80419ba0(r2)
		opword 0xC0010030
		opword 0x90A10014
		opword 0xEC02007C
		opword 0x9081001C
		opword 0xD0010030
		opword 0x80010030
		opword 0x90A1002C
		opword 0x90010018
		opword 0x90810034
		opword 0xC03F014C
		bl cloudGetBreathPower
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38600001
		opword 0x48000058
		opword 0x801F0090
		opword 0x38610008
		opword 0x80BF008C
		opword 0x90010030
		opword 0x809F0094
		opword 0xC01F0150
		opword 0xC0210030
		opword 0x90A10008
		opword 0xEC010028
		opword 0x90810010
		opword 0xD0010030
		opword 0x80010030
		opword 0x90A1002C
		opword 0x9001000C
		opword 0x90810034
		opword 0xC03F014C
		bl cloudGetBreathPower
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x7C000026
		opword 0x540317FE
		opword 0x80010044
		opword 0x83E1003C
		opword 0x7C0803A6
		opword 0x38210040
	}
}
#pragma pop

#pragma defer_codegen off
BOOL N_fbatPreventMarioEventChk(void) {
    s32 mode = gp->fbatData->mode;
    if (mode != 0 && mode != 1 && mode != 8) {
        return TRUE;
    }
    return FALSE;
}

#pragma defer_codegen reset

asm s32 npcKoopaModeMobjBoundDeadCheck(HitEntry* hit) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	la r3, work(r13)
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq L_af_1
	addi r3, r3, 0x14
L_af_1:
	cmplwi r27, 0x0
	lwz r30, 0x4(r3)
	li r28, 0x0
	bne L_af_2
	li r3, 0x0
	b L_af_3
L_af_2:
	lwz r29, 0xc(r3)
	li r31, 0x0
	b L_af_4
L_af_5:
	cmplwi r29, 0x0
	beq L_af_6
	lwz r3, 0x0(r29)
	clrlwi. r0, r3, 31
	beq L_af_6
	rlwinm. r0, r3, 0, 4, 4
	beq L_af_6
	lwz r0, 0x1d4(r29)
	rlwinm. r0, r0, 0, 29, 29
	bne L_af_6
	lhz r0, 0x31e(r29)
	rlwinm. r0, r0, 0, 28, 28
	bne L_af_6
	lwz r0, 0x300(r29)
	cmplw r0, r27
	bne L_af_6
	mr r3, r29
	li r4, 0x8
	bl npcGroupDead
	addi r28, r28, 0x1
L_af_6:
	addi r31, r31, 0x1
	addi r29, r29, 0x340
L_af_4:
	cmpw r31, r30
	blt L_af_5
	mr r3, r28
L_af_3:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcKoopaModeEncountCheck(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	la r3, work(r13)
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	lwz r4, 0x168(r4)
	cmpwi r0, 0x0
	beq L_af_1
	addi r3, r3, 0x14
L_af_1:
	lha r0, 0x0(r4)
	lwz r30, 0x4(r3)
	cmpwi r0, 0x1
	bne L_af_2
	lwz r29, 0xc(r3)
	li r31, 0x0
	b L_af_3
L_af_4:
	cmplwi r29, 0x0
	beq L_af_5
	lwz r3, 0x0(r29)
	clrlwi. r0, r3, 31
	beq L_af_5
	rlwinm. r0, r3, 0, 4, 4
	beq L_af_5
	lwz r0, 0x1d4(r29)
	rlwinm. r0, r0, 0, 29, 29
	bne L_af_5
	lfs f1, 0x8c(r29)
	lfs f2, 0x90(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x150(r29)
	lfs f5, 0x14c(r29)
	bl kpaEnemyHitChk
	cmpwi r3, 0x3
	beq L_af_6
	bge L_af_7
	cmpwi r3, 0x1
	beq L_af_8
	bge L_af_9
	b L_af_10
L_af_7:
	cmpwi r3, 0x5
	bge L_af_10
	b L_af_11
L_af_8:
	lhz r0, 0x31e(r29)
	clrlwi. r0, r0, 31
	bne L_af_5
	mr r3, r29
	li r4, 0x1
	bl npcGroupDead
	b L_af_5
L_af_9:
	lhz r0, 0x31e(r29)
	rlwinm. r0, r0, 0, 30, 30
	bne L_af_5
	mr r3, r29
	li r4, 0x2
	bl npcGroupDead
	b L_af_5
L_af_6:
	lhz r0, 0x31e(r29)
	rlwinm. r0, r0, 0, 29, 29
	bne L_af_5
	mr r3, r29
	li r4, 0x4
	bl npcGroupDead
	b L_af_5
L_af_11:
	bl kpaPowDown
	b L_af_5
L_af_10:
	lhz r0, 0x31e(r29)
	rlwinm. r0, r0, 0, 27, 27
	bne L_af_5
	lwz r3, 0x300(r29)
	cmplwi r3, 0x0
	beq L_af_5
	bl hitGetName
	lis r4, str_802C30FC@ha
	addi r4, r4, str_802C30FC@l
	bl strcmp
	cmpwi r3, 0x0
	bne L_af_5
	mr r3, r29
	li r4, 0x10
	bl npcGroupDead
L_af_5:
	addi r31, r31, 0x1
	addi r29, r29, 0x340
L_af_3:
	cmpw r31, r30
	blt L_af_4
L_af_2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

#endif
NpcWork* npcGetWorkPtr(void) {
    return gp->inBattle ? &work.battle : &work.field;
}

void npcReleaseFieldNpc(void) {
    NpcWork* wp;
    NpcFieldEntry* field;
    NpcEntry* entry;
    AnimationPose* pose;
    int i;

    wp = &work.field;
    field = release_wp;
    if (wp->flags & 2) {
        entry = wp->entries;
        for (i = 0; i < wp->total; i++, entry++) {
            // entry = &wp->entries[i];
            if (entry->flags & 1 && entry->flags & 2 && animPoseGetAnimPosePtr(entry->poseId)->paperId == -1) {
                if (entry->poseId >= 0) {
                    pose = animPoseGetAnimPosePtr(entry->poseId);
                    field->mFlags = pose->flags;
                    field->wCurrentRenderRotationMinus90Y = pose->peraRotY;
                    field->wRotationY = pose->rotationY;
                    field->wScaleZ_flip = pose->field_0x78;
                    field->wInitToZero4 = pose->peraTargetRotY;
                    strcpy(field->mModelName, animPoseGetAnimBaseDataPtr(entry->poseId)->fileName);
                    strcpy(field->mAnimName, animPoseGetCurrentAnim(entry->poseId)->name);
                    animPoseRelease(entry->poseId);
                    field++; // next release_wp entry
                    entry->poseId = -1;
                }
            }
        }
    }
}

void npcRecoveryFieldNpc(void) {
    NpcWork* wp;
    NpcFieldEntry* field;
    NpcEntry* entry;
    AnimationPose* pose;
    int i;

    wp = &work.field;
    field = release_wp;
    if (wp->flags & 2) {
        entry = wp->entries;
        for (i = 0; i < wp->total; i++, entry++) {
            if (entry->flags & 1 && entry->flags & 2 && entry->poseId == -1) {
                entry->poseId = animPoseEntry(field->mModelName, 0);
                animPoseSetAnim(entry->poseId, field->mAnimName, TRUE);
                pose = animPoseGetAnimPosePtr(entry->poseId);
                pose->flags = field->mFlags;
                pose->peraRotY = field->wCurrentRenderRotationMinus90Y;
                pose->rotationY = field->wRotationY;
                pose->field_0x78 = field->wScaleZ_flip;
                pose->peraTargetRotY = field->wInitToZero4;

                if (pose->flags & 0x40) {
                    pose->flags &= ~0x40;
                    animPoseWorldPositionEvalOn(entry->poseId);
                }
                if (pose->flags & 0x80) {
                    pose->flags &= ~0x80;
                    animPoseWorldMatrixEvalOn(entry->poseId);
                }
                animPoseMain(entry->poseId);
                field++; // next release_wp entry
            }
        }
        wp->flags &= ~2;
    }
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void mtx_setup(NpcEntry* entry, Mtx mtx, s32 history) {
#ifdef NONMATCHING
    f32 rotationAngle;
    f32 scaleSign;
    CameraEntry* camera;
    f32 tmpi2[2];
    f32 v15;
    Mtx mtxX, mtxY, mtxZ;
#endif
#ifndef NONMATCHING
	char _af_pad[144];
	asm volatile {
		mr r28, r3
		opword 0x80630000
		lfs f31, float_0_80419b9c(r2)
		opword 0x7C9D2378
		opword 0x5460018D
		lfs f30, float_1_80419bb4(r2)
		opword 0x7CBE2B78
		opword 0x4082004C
		opword 0x54600109
		opword 0x40820044
		bl camGetCurPtr
		opword 0x7C7F1B78
		opword 0xC023000C
		opword 0xC0430014
		opword 0xC0630018
		opword 0xC0830020
		bl angleABf
		opword 0xFFE00890
		opword 0xC03F000C
		opword 0xC05F0014
		opword 0xC07C008C
		opword 0xC09C0094
		bl angleABf
		opword 0xEC3F0828
		bl reviseAngle
		opword 0xFFE00890
		opword 0xC03C00F0
		bl reviseAngle
		bl reviseAngle
		lfs f0, float_90_80419bd0(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082001C
		lfs f0, float_270_80419be4(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082000C
		lfs f0, float_neg1_80419bf8(r2)
		opword 0xEFDE0032
		opword 0x7FA3EB78
		bl PSMTXIdentity
		lfs f2, float_1_80419bb4(r2)
		opword 0xC03C00E0
		opword 0xFC020800
		opword 0x40820024
		opword 0xC01C00E4
		opword 0xFC020000
		opword 0x40820018
		opword 0xC01C00E8
		opword 0xFC020000
		opword 0x4082000C
		opword 0xFC02F000
		opword 0x4182001C
		opword 0xC01C00E8
		opword 0x7FA3EB78
		opword 0xC05C00E4
		opword 0x7FA4EB78
		opword 0xEC6007B2
		bl PSMTXScaleApply
		opword 0xC07C00F8
		lfs f1, float_0_80419b9c(r2)
		opword 0xFC030800
		opword 0x4082001C
		opword 0xC01C00FC
		opword 0xFC000800
		opword 0x40820010
		opword 0xC01C0100
		opword 0xFC000800
		opword 0x41820024
		opword 0xC05C00FC
		opword 0xFC201850
		opword 0xC01C0100
		opword 0x7FA3EB78
		opword 0xFC401050
		opword 0x7FA4EB78
		opword 0xFC600050
		bl PSMTXTransApply
		opword 0xC03C00F4
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010000
		opword 0x41820028
		lfs f0, float_deg2rad_80419ca0(r2)
		la r3, _af_pad+0
		opword 0x3880007A
		opword 0xEC200072
		bl PSMTXRotRad
		opword 0x7FA4EB78
		opword 0x7FA5EB78
		opword 0x38610008
		bl PSMTXConcat
		opword 0xC03C00EC
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010000
		opword 0x41820028
		lfs f0, float_deg2rad_80419ca0(r2)
		opword 0x38610068
		opword 0x38800078
		opword 0xEC200072
		bl PSMTXRotRad
		opword 0x7FA4EB78
		opword 0x7FA5EB78
		opword 0x38610068
		bl PSMTXConcat
		opword 0xC03C00F0
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010000
		opword 0x4082000C
		opword 0xFC1F0000
		opword 0x4182002C
		opword 0xEC01F82A
		lfs f1, float_deg2rad_80419ca0(r2)
		opword 0x38610038
		opword 0x38800079
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x7FA4EB78
		opword 0x7FA5EB78
		opword 0x38610038
		bl PSMTXConcat
		opword 0xC03C00F8
		lfs f2, float_0_80419b9c(r2)
		opword 0xFC011000
		opword 0x4082001C
		opword 0xC01C00FC
		opword 0xFC001000
		opword 0x40820010
		opword 0xC01C0100
		opword 0xFC001000
		opword 0x41820018
		opword 0xC05C00FC
		opword 0x7FA3EB78
		opword 0xC07C0100
		opword 0x7FA4EB78
		bl PSMTXTransApply
		opword 0x2C1EFFFF
		opword 0x40820020
		opword 0xC03C008C
		opword 0x7FA3EB78
		opword 0xC05C0090
		opword 0x7FA4EB78
		opword 0xC07C0094
		bl PSMTXTransApply
		opword 0x48000024
		opword 0x1C1E000C
		opword 0x7FA3EB78
		opword 0x7FA4EB78
		opword 0x7CBC0214
		opword 0xC02500A4
		opword 0xC04500A8
		opword 0xC06500AC
		bl PSMTXTransApply
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    rotationAngle = 0.0f;
    scaleSign = 1.0f;
    if (!(entry->flags & 0x2000000) && !(entry->flags & 0x8000000)) {
        camera = camGetCurPtr();
        tmpi2[1] = angleABf(camera->cameraPos.x, camera->cameraPos.z, camera->cameraAt.x, camera->cameraAt.z);
        tmpi2[0] = angleABf(camera->cameraPos.x, camera->cameraPos.z, entry->position.x, entry->position.z);
        rotationAngle = reviseAngle(tmpi2[1] - tmpi2[0]);
    }
    v15 = reviseAngle(reviseAngle(entry->rotation.y));
    if (v15 >= 90.0f && v15 <= 270.0f) {
        scaleSign *= -1.0f;
    }
    MTXIdentity(mtx);
    if (entry->scale.x != 1.0f || entry->scale.y != 1.0f || entry->scale.z != 1.0f || scaleSign != 1.0f) {
        MTXScaleApply(mtx, mtx, entry->scale.x, entry->scale.y, entry->scale.z * scaleSign);
    }
    if (entry->rotationOffset.x || entry->rotationOffset.y || entry->rotationOffset.z) {
        MTXTransApply(mtx, mtx, -entry->rotationOffset.x, -entry->rotationOffset.y, -entry->rotationOffset.z);
    }
    if (entry->rotation.z) {
        MTXRotRad(mtxZ, 'z', entry->rotation.z * 0.017453292f);
        MTXConcat(mtxZ, mtx, mtx);
    }
    if (entry->rotation.x) {
        MTXRotRad(mtxX, 'x', entry->rotation.x * 0.017453292f);
        MTXConcat(mtxX, mtx, mtx);
    }
    if (entry->rotation.y || rotationAngle) {
        MTXRotRad(mtxY, 'y', (entry->rotation.y + rotationAngle) * 0.017453292f);
        MTXConcat(mtxY, mtx, mtx);
    }
    if (entry->rotationOffset.x || entry->rotationOffset.y || entry->rotationOffset.z) {
        MTXTransApply(mtx, mtx, entry->rotationOffset.x, entry->rotationOffset.y, entry->rotationOffset.z);
    }
    if (history == -1) {
        MTXTransApply(mtx, mtx, entry->position.x, entry->position.y, entry->position.z);
    } else {
        MTXTransApply(mtx, mtx, entry->positionHistory[history].x, entry->positionHistory[history].y,
                      entry->positionHistory[history].z);
    }
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void npcDisp_xlu(CameraId cameraId, void* param) {
	char _af_pad[48];
	asm volatile {
		opword 0xC0040144
		opword 0x7C9F2378
		opword 0xFC200050
		bl reviseAngle
		fmr f31, f1
		opword 0x7FE3FB78
		la r4, _af_pad+8
		opword 0x38A0FFFF
		bl mtx_setup
		opword 0x801F01D4
		opword 0x807F0114
		opword 0x54000253
		opword 0x9061000C
		opword 0x41820060
		opword 0x88A1000C
		opword 0x38810008
		opword 0x88C1000D
		opword 0x54A00FFE
		opword 0x8861000E
		opword 0x7C002A14
		opword 0x54C50FFE
		opword 0x7C070E70
		opword 0x54600FFE
		opword 0x7CA53214
		opword 0x7CA50E70
		opword 0x98E1000C
		opword 0x7C001A14
		opword 0x7C000E70
		opword 0x98A1000D
		opword 0x9801000E
		opword 0x8001000C
		opword 0x90010008
		opword 0x807F0104
		bl animPoseSetMaterialEvtColor
		opword 0x807F0104
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		opword 0x801F0000
		opword 0x54000211
		opword 0x41820168
		opword 0x807F0104
		bl animPoseGetCurrentAnim
		opword 0x807F0104
		bl animPoseGetAnimPosePtr
		opword 0x7C7E1B78
		opword 0x807F0104
		bl animPoseGetCurrentAnim
		opword 0x7C7D1B78
		opword 0x38600004
		bl camGetPtr
		opword 0xC0630018
		opword 0xC043000C
		opword 0xC0230020
		opword 0xC0030014
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC201050
		opword 0xFC400050
		bl atan2
		opword 0xFC200818
		lfs f0, float_rad2deg_80419bdc(r2)
		opword 0xEC200072
		bl reviseAngle
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f0, float_360_80419be0(r2)
		opword 0xEC21002A
		opword 0xC01E0074
		opword 0xEC210028
		bl reviseAngle
		lfs f0, float_90_80419bd0(r2)
		opword 0xFC010040
		opword 0x40810014
		lfs f0, float_270_80419be4(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x41820020
		lfs f0, float_neg90_80419bd8(r2)
		opword 0xFC010040
		opword 0x40800070
		lfs f0, float_neg270_80419be8(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820060
		lis r3, luigi_pose@ha
		opword 0x3BC00000
		addi r28, r3, luigi_pose@l
		opword 0x807C0000
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820014
		opword 0x3BDE0001
		opword 0x3B9C0008
		opword 0x281E000E
		opword 0x4180FFE0
		opword 0x281E000E
		opword 0x4080007C
		lis r3, luigi_pose@ha
		opword 0x57C01838
		addi r4, r3, luigi_pose@l
		opword 0x807F0104
		opword 0x7C840214
		opword 0x38A00000
		opword 0x80840004
		bl animPoseSetAnim
		opword 0x48000058
		lis r3, luigi_pose@ha
		opword 0x3BC00000
		addi r28, r3, luigi_pose@l
		opword 0x807C0004
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820014
		opword 0x3BDE0001
		opword 0x3B9C0008
		opword 0x281E000E
		opword 0x4180FFE0
		opword 0x281E000E
		opword 0x40800020
		lis r3, luigi_pose@ha
		opword 0x57C01838
		addi r4, r3, luigi_pose@l
		opword 0x807F0104
		opword 0x7C84002E
		opword 0x38A00000
		bl animPoseSetAnim
		opword 0x807F0104
		bl animPoseMain
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810010
		opword 0x38A00001
		bl animPoseDrawMtx
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810010
		opword 0x38A00002
		bl animPoseDrawMtx
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810010
		opword 0x38A00003
		bl animPoseDrawMtx
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
double atan2(double y, double x);
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void npcDisp(CameraId camId, void* param) {
	char _af_pad[48];
	asm volatile {
		opword 0xC0040144
		opword 0x7C9F2378
		opword 0xFC200050
		bl reviseAngle
		fmr f31, f1
		opword 0x7FE3FB78
		la r4, _af_pad+8
		opword 0x38A0FFFF
		bl mtx_setup
		bl dispGetCurWork
		opword 0x88030001
		opword 0x2C000001
		opword 0x41820224
		opword 0x40800010
		opword 0x2C000000
		opword 0x40800014
		opword 0x48000248
		opword 0x2C000003
		opword 0x40800240
		opword 0x48000224
		opword 0x801F01D4
		opword 0x807F0114
		opword 0x54000253
		opword 0x9061000C
		opword 0x41820060
		opword 0x88A1000C
		opword 0x38810008
		opword 0x88C1000D
		opword 0x54A00FFE
		opword 0x8861000E
		opword 0x7C002A14
		opword 0x54C50FFE
		opword 0x7C070E70
		opword 0x54600FFE
		opword 0x7CA53214
		opword 0x7CA50E70
		opword 0x98E1000C
		opword 0x7C001A14
		opword 0x7C000E70
		opword 0x98A1000D
		opword 0x9801000E
		opword 0x8001000C
		opword 0x90010008
		opword 0x807F0104
		bl animPoseSetMaterialEvtColor
		opword 0x807F0104
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		opword 0x801F0000
		opword 0x54000211
		opword 0x41820168
		opword 0x807F0104
		bl animPoseGetCurrentAnim
		opword 0x807F0104
		bl animPoseGetAnimPosePtr
		opword 0x7C7E1B78
		opword 0x807F0104
		bl animPoseGetCurrentAnim
		opword 0x7C7D1B78
		opword 0x38600004
		bl camGetPtr
		opword 0xC0630018
		opword 0xC043000C
		opword 0xC0230020
		opword 0xC0030014
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC201050
		opword 0xFC400050
		bl atan2
		opword 0xFC200818
		lfs f0, float_rad2deg_80419bdc(r2)
		opword 0xEC200072
		bl reviseAngle
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f0, float_360_80419be0(r2)
		opword 0xEC21002A
		opword 0xC01E0074
		opword 0xEC210028
		bl reviseAngle
		lfs f0, float_90_80419bd0(r2)
		opword 0xFC010040
		opword 0x40810014
		lfs f0, float_270_80419be4(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x41820020
		lfs f0, float_neg90_80419bd8(r2)
		opword 0xFC010040
		opword 0x40800070
		lfs f0, float_neg270_80419be8(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820060
		lis r3, luigi_pose@ha
		opword 0x3BC00000
		addi r28, r3, luigi_pose@l
		opword 0x807C0000
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820014
		opword 0x3BDE0001
		opword 0x3B9C0008
		opword 0x281E000E
		opword 0x4180FFE0
		opword 0x281E000E
		opword 0x4080007C
		lis r3, luigi_pose@ha
		opword 0x57C01838
		addi r4, r3, luigi_pose@l
		opword 0x807F0104
		opword 0x7C840214
		opword 0x38A00000
		opword 0x80840004
		bl animPoseSetAnim
		opword 0x48000058
		lis r3, luigi_pose@ha
		opword 0x3BC00000
		addi r28, r3, luigi_pose@l
		opword 0x807C0004
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820014
		opword 0x3BDE0001
		opword 0x3B9C0008
		opword 0x281E000E
		opword 0x4180FFE0
		opword 0x281E000E
		opword 0x40800020
		lis r3, luigi_pose@ha
		opword 0x57C01838
		addi r4, r3, luigi_pose@l
		opword 0x807F0104
		opword 0x7C84002E
		opword 0x38A00000
		bl animPoseSetAnim
		opword 0x807F0104
		bl animPoseMain
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810010
		opword 0x38A00001
		bl animPoseDrawMtx
		opword 0x48000038
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810010
		opword 0x38A00002
		bl animPoseDrawMtx
		opword 0x4800001C
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810010
		opword 0x38A00003
		bl animPoseDrawMtx
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
static inline void npcLuigiPoseFlip(NpcEntry* entry) {
    if (entry->flags & 0x800000) {
        AnimationPose* animPose;
        AnimTableEntry* anim;
        CameraEntry* camera;
        f32 dx, dz;
        f32 angle;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void npcDisp_offscreen_xlu(CameraId camId, void* param) {
	char _af_pad[64];
	asm volatile {
		opword 0x7C9F2378
		bl sysWaitDrawSync
		bl GXClearBoundingBox
		opword 0xC01F0144
		opword 0xFC200050
		bl reviseAngle
		fmr f31, f1
		opword 0x7FE3FB78
		la r4, _af_pad+16
		opword 0x38A0FFFF
		bl mtx_setup
		opword 0x801F01D4
		opword 0x807F0114
		opword 0x54000253
		opword 0x90610010
		opword 0x41820060
		opword 0x88A10010
		opword 0x38810014
		opword 0x88C10011
		opword 0x54A00FFE
		opword 0x88610012
		opword 0x7C002A14
		opword 0x54C50FFE
		opword 0x7C070E70
		opword 0x54600FFE
		opword 0x7CA53214
		opword 0x7CA50E70
		opword 0x98E10010
		opword 0x7C001A14
		opword 0x7C000E70
		opword 0x98A10011
		opword 0x98010012
		opword 0x80010010
		opword 0x90010014
		opword 0x807F0104
		bl animPoseSetMaterialEvtColor
		opword 0x807F0104
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		opword 0x801F0000
		opword 0x54000211
		opword 0x41820168
		opword 0x807F0104
		bl animPoseGetCurrentAnim
		opword 0x807F0104
		bl animPoseGetAnimPosePtr
		opword 0x7C7E1B78
		opword 0x807F0104
		bl animPoseGetCurrentAnim
		opword 0x7C7D1B78
		opword 0x38600004
		bl camGetPtr
		opword 0xC0630018
		opword 0xC043000C
		opword 0xC0230020
		opword 0xC0030014
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC201050
		opword 0xFC400050
		bl atan2
		opword 0xFC200818
		lfs f0, float_rad2deg_80419bdc(r2)
		opword 0xEC200072
		bl reviseAngle
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f0, float_360_80419be0(r2)
		opword 0xEC21002A
		opword 0xC01E0074
		opword 0xEC210028
		bl reviseAngle
		lfs f0, float_90_80419bd0(r2)
		opword 0xFC010040
		opword 0x40810014
		lfs f0, float_270_80419be4(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x41820020
		lfs f0, float_neg90_80419bd8(r2)
		opword 0xFC010040
		opword 0x40800070
		lfs f0, float_neg270_80419be8(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820060
		lis r3, luigi_pose@ha
		opword 0x3BC00000
		addi r28, r3, luigi_pose@l
		opword 0x807C0000
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820014
		opword 0x3BDE0001
		opword 0x3B9C0008
		opword 0x281E000E
		opword 0x4180FFE0
		opword 0x281E000E
		opword 0x4080007C
		lis r3, luigi_pose@ha
		opword 0x57C01838
		addi r4, r3, luigi_pose@l
		opword 0x807F0104
		opword 0x7C840214
		opword 0x38A00000
		opword 0x80840004
		bl animPoseSetAnim
		opword 0x48000058
		lis r3, luigi_pose@ha
		opword 0x3BC00000
		addi r28, r3, luigi_pose@l
		opword 0x807C0004
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820014
		opword 0x3BDE0001
		opword 0x3B9C0008
		opword 0x281E000E
		opword 0x4180FFE0
		opword 0x281E000E
		opword 0x40800020
		lis r3, luigi_pose@ha
		opword 0x57C01838
		addi r4, r3, luigi_pose@l
		opword 0x807F0104
		opword 0x7C84002E
		opword 0x38A00000
		bl animPoseSetAnim
		opword 0x807F0104
		bl animPoseMain
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810018
		opword 0x38A00001
		bl animPoseDrawMtx
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810018
		opword 0x38A00002
		bl animPoseDrawMtx
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810018
		opword 0x38A00003
		bl animPoseDrawMtx
		bl sysWaitDrawSync
		opword 0x3861000E
		opword 0x3881000C
		opword 0x38A1000A
		opword 0x38C10008
		bl GXReadBoundingBox
		opword 0x807F0110
		opword 0xA081000E
		opword 0xA0A1000C
		opword 0xA0C1000A
		opword 0xA0E10008
		bl offscreenAddBoundingBox
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
        animPoseGetCurrentAnim(entry->poseId);
        animPose = animPoseGetAnimPosePtr(entry->poseId);
        anim = animPoseGetCurrentAnim(entry->poseId);
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void npcDisp_offscreen(CameraId camId, void* param) {
	char _af_pad[64];
	asm volatile {
		opword 0x7C9F2378
		bl sysWaitDrawSync
		bl GXClearBoundingBox
		opword 0xC01F0144
		opword 0xFC200050
		bl reviseAngle
		fmr f31, f1
		opword 0x7FE3FB78
		la r4, _af_pad+16
		opword 0x38A0FFFF
		bl mtx_setup
		bl dispGetCurWork
		opword 0x88030001
		opword 0x2C000001
		opword 0x41820224
		opword 0x40800010
		opword 0x2C000000
		opword 0x40800014
		opword 0x48000248
		opword 0x2C000003
		opword 0x40800240
		opword 0x48000224
		opword 0x801F01D4
		opword 0x807F0114
		opword 0x54000253
		opword 0x90610010
		opword 0x41820060
		opword 0x88A10010
		opword 0x38810014
		opword 0x88C10011
		opword 0x54A00FFE
		opword 0x88610012
		opword 0x7C002A14
		opword 0x54C50FFE
		opword 0x7C070E70
		opword 0x54600FFE
		opword 0x7CA53214
		opword 0x7CA50E70
		opword 0x98E10010
		opword 0x7C001A14
		opword 0x7C000E70
		opword 0x98A10011
		opword 0x98010012
		opword 0x80010010
		opword 0x90010014
		opword 0x807F0104
		bl animPoseSetMaterialEvtColor
		opword 0x807F0104
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		opword 0x801F0000
		opword 0x54000211
		opword 0x41820168
		opword 0x807F0104
		bl animPoseGetCurrentAnim
		opword 0x807F0104
		bl animPoseGetAnimPosePtr
		opword 0x7C7E1B78
		opword 0x807F0104
		bl animPoseGetCurrentAnim
		opword 0x7C7D1B78
		opword 0x38600004
		bl camGetPtr
		opword 0xC0630018
		opword 0xC043000C
		opword 0xC0230020
		opword 0xC0030014
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC201050
		opword 0xFC400050
		bl atan2
		opword 0xFC200818
		lfs f0, float_rad2deg_80419bdc(r2)
		opword 0xEC200072
		bl reviseAngle
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f0, float_360_80419be0(r2)
		opword 0xEC21002A
		opword 0xC01E0074
		opword 0xEC210028
		bl reviseAngle
		lfs f0, float_90_80419bd0(r2)
		opword 0xFC010040
		opword 0x40810014
		lfs f0, float_270_80419be4(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x41820020
		lfs f0, float_neg90_80419bd8(r2)
		opword 0xFC010040
		opword 0x40800070
		lfs f0, float_neg270_80419be8(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820060
		lis r3, luigi_pose@ha
		opword 0x3BC00000
		addi r28, r3, luigi_pose@l
		opword 0x807C0000
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820014
		opword 0x3BDE0001
		opword 0x3B9C0008
		opword 0x281E000E
		opword 0x4180FFE0
		opword 0x281E000E
		opword 0x4080007C
		lis r3, luigi_pose@ha
		opword 0x57C01838
		addi r4, r3, luigi_pose@l
		opword 0x807F0104
		opword 0x7C840214
		opword 0x38A00000
		opword 0x80840004
		bl animPoseSetAnim
		opword 0x48000058
		lis r3, luigi_pose@ha
		opword 0x3BC00000
		addi r28, r3, luigi_pose@l
		opword 0x807C0004
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820014
		opword 0x3BDE0001
		opword 0x3B9C0008
		opword 0x281E000E
		opword 0x4180FFE0
		opword 0x281E000E
		opword 0x40800020
		lis r3, luigi_pose@ha
		opword 0x57C01838
		addi r4, r3, luigi_pose@l
		opword 0x807F0104
		opword 0x7C84002E
		opword 0x38A00000
		bl animPoseSetAnim
		opword 0x807F0104
		bl animPoseMain
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810018
		opword 0x38A00001
		bl animPoseDrawMtx
		opword 0x48000038
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810018
		opword 0x38A00002
		bl animPoseDrawMtx
		opword 0x4800001C
		opword 0xFC20F890
		opword 0x807F0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810018
		opword 0x38A00003
		bl animPoseDrawMtx
		bl sysWaitDrawSync
		opword 0x3861000E
		opword 0x3881000C
		opword 0x38A1000A
		opword 0x38C10008
		bl GXReadBoundingBox
		opword 0x807F0110
		opword 0xA081000E
		opword 0xA0A1000C
		opword 0xA0C1000A
		opword 0xA0E10008
		bl offscreenAddBoundingBox
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
        camera = camGetPtr(CAMERA_3D);
        dx = camera->cameraAt.x - camera->cameraPos.x;
        dz = camera->cameraAt.z - camera->cameraPos.z;
        angle = reviseAngle(NPC_RAD2DEG((f32)atan2(-dx, -dz)));
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        angle = angle - animPose->rotationY;
        angle = reviseAngle(angle);

        if ((angle > 90.0f && angle <= 270.0f) || (angle < -90.0f && angle >= -270.0f)) {
            u32 i;
            for (i = 0; i < 14; i++) {
                if (!strcmp(luigi_pose[i][0], anim->name)) {
                    break;
                }
            }
            if (i < 14) {
                animPoseSetAnim(entry->poseId, luigi_pose[i][1], FALSE);
            }
        } else {
            u32 i;
            for (i = 0; i < 14; i++) {
                if (!strcmp(luigi_pose[i][1], anim->name)) {
                    break;
                }
            }
            if (i < 14) {
                animPoseSetAnim(entry->poseId, luigi_pose[i][0], FALSE);
            }
        }
    }
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void npcDisp_blur(CameraId camId, void* param) {
	asm volatile {
		opword 0x9421FF80
		opword 0x7C0802A6
		opword 0x90010084
		opword 0xDBE10070
		opword 0xF3E10078
		opword 0xDBC10060
		opword 0xF3C10068
		opword 0xDBA10050
		opword 0xF3A10058
		opword 0x93E1004C
		opword 0x93C10048
		opword 0x93A10044
		opword 0x93810040
		opword 0xC0040144
		opword 0x7C7D1B78
		opword 0x7C9E2378
		opword 0xFC200050
		bl reviseAngle
		opword 0xFFE00890
		opword 0x807E0104
		bl animPoseGetMaterialFlag
		opword 0x7C601B78
		opword 0x7FA3EB78
		opword 0x7C1C0378
		bl camGetPtr
		opword 0xC0430114
		lfs f1, float_6p2832_80419c38(r2)
		lfs f0, float_360_80419be0(r2)
		opword 0xEC4100B2
		lfs f1, float_3p1416_80419c44(r2)
		lfs f4, float_0p00761_80419c3c(r2)
		lfs f3, float_0p16605_80419c40(r2)
		opword 0xECA20024
		lfs f2, float_1_80419bb4(r2)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820044
		lfs f1, float_1p5708_80419c48(r2)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0x48000068
		opword 0xEC050828
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0x4800004C
		lfs f0, float_4p7124_80419c4c(r2)
		opword 0xFC050040
		opword 0x40800020
		opword 0xECA50828
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		opword 0x48000024
		opword 0xEC050028
		lfs f1, float_1p5708_80419c48(r2)
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840172
		opword 0xFC802050
		lfs f0, float_2_80419c5c(r2)
		opword 0x7FA3EB78
		opword 0xEFC00132
		bl camGetPtr
		opword 0xC0430114
		lfs f1, float_6p2832_80419c38(r2)
		lfs f0, float_360_80419be0(r2)
		opword 0xEC4100B2
		lfs f1, float_3p1416_80419c44(r2)
		lfs f4, float_0p03705_80419c50(r2)
		lfs f3, float_0p4967_80419c54(r2)
		opword 0xECA20024
		lfs f2, float_1_80419bb4(r2)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820040
		lfs f1, float_1p5708_80419c48(r2)
		opword 0xFC050840
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0x4800005C
		opword 0xEC050828
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x48000040
		lfs f0, float_4p7124_80419c4c(r2)
		opword 0xFC050040
		opword 0x4080001C
		opword 0xECA50828
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC802050
		opword 0x4800001C
		opword 0xEC050028
		lfs f1, float_1p5708_80419c48(r2)
		opword 0xECA10028
		opword 0xEC050172
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xFC002050
		lfs f1, float_2_80419c5c(r2)
		opword 0x807E0104
		opword 0xEFA10032
		bl animPoseMain
		opword 0x3BA00004
		opword 0x3BE00064
		opword 0x7FC3F378
		opword 0x7FA5EB78
		opword 0x38810010
		bl mtx_setup
		opword 0xFC20F090
		opword 0x38610010
		opword 0xFC60E890
		lfs f2, float_0_80419b9c(r2)
		opword 0x7C641B78
		bl PSMTXTransApply
		opword 0x807E0104
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		lwz r3, dat_80419b88(r2)
		opword 0x201F0080
		opword 0x3881000C
		opword 0x90610008
		opword 0x9801000B
		opword 0x80010008
		opword 0x9001000C
		opword 0x807E0104
		bl animPoseSetMaterialEvtColor
		opword 0xFC20F890
		opword 0x807E0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810010
		opword 0x38A00001
		bl animPoseDrawMtx
		opword 0xFC20F890
		opword 0x807E0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810010
		opword 0x38A00002
		bl animPoseDrawMtx
		opword 0xFC20F890
		opword 0x807E0104
		lfs f2, float_2_80419c5c(r2)
		opword 0x38810010
		opword 0x38A00003
		bl animPoseDrawMtx
		opword 0x37BDFFFF
		opword 0x3BFFFFE7
		opword 0x4181FF58
		opword 0x807E0104
		opword 0x38800040
		bl animPoseSetMaterialFlagOff
		opword 0x807E0104
		opword 0x7F84E378
		bl animPoseSetMaterialFlagOn
		opword 0xE3E10078
		opword 0xCBE10070
		opword 0xE3C10068
		opword 0xCBC10060
		opword 0xE3A10058
		opword 0xCBA10050
		opword 0x83E1004C
		opword 0x83C10048
		opword 0x83A10044
		opword 0x80010084
		opword 0x83810040
		opword 0x7C0803A6
		opword 0x38210080
	}
#endif
}
#ifdef NONMATCHING

static inline void npcDimColor(NpcEntry* entry) {
    GXColor color = entry->color;
    if (entry->jumpFlags & 0x400000) {
        color.r /= 2;
        color.g /= 2;
        color.b /= 2;
        animPoseSetMaterialEvtColor(entry->poseId, color);
        animPoseSetMaterialFlagOn(entry->poseId, 0x40);
    }
}

void npcDisp_xlu(CameraId cameraId, void* param) {
    NpcEntry* entry = param; // cast to proper type
    Mtx mtx;
    GXColor color;
    f32 rotY;

    rotY = reviseAngle(-entry->direction);
    mtx_setup(entry, mtx, -1);

    color = entry->color;
    if (entry->jumpFlags & 0x400000) {
        color.r /= 2;
        color.g /= 2;
        color.b /= 2;
        animPoseSetMaterialEvtColor(entry->poseId, color);
        animPoseSetMaterialFlagOn(entry->poseId, 0x40);
    }

    npcLuigiPoseFlip(entry);
    animPoseMain(entry->poseId);
    animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
}

void npcDisp(CameraId camId, void* param) {
    NpcEntry* entry = param; // cast to proper type
    Mtx mtx;
    GXColor color;
    f32 rotY;
    AnimTableEntry* anim;
    const char* nm;

    rotY = reviseAngle(-entry->direction);
    mtx_setup(entry, mtx, -1);

    switch (dispGetCurWork()->renderMode) {
        case 0:
            color = entry->color;
            if (entry->jumpFlags & 0x400000) {
                color.r /= 2;
                color.g /= 2;
                if (rotY && rotY && rotY) {
                }
                color.b /= 2;
                animPoseSetMaterialEvtColor(entry->poseId, color);
                animPoseSetMaterialFlagOn(entry->poseId, 0x40);
            }

            npcLuigiPoseFlip(entry);
            animPoseMain(entry->poseId);
            animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
            break;
        case 1:
            animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
            break;
        case 2:
            animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
            break;
    }
}

void npcDisp_offscreen_xlu(CameraId camId, void* param) {
    NpcEntry* entry = param; // cast to proper type
    u16 left, top, right, bottom;
    Mtx mtx;
    GXColor color;
    f32 rotY;

    sysWaitDrawSync();
    GXClearBoundingBox();
    rotY = reviseAngle(-entry->direction);
    mtx_setup(entry, mtx, -1);

    npcDimColor(entry);

    npcLuigiPoseFlip(entry);
    if (!bottom) {
    }
    animPoseMain(entry->poseId);
    animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    offscreenAddBoundingBox(entry->offscreenId, left, top, right, bottom);
}

void npcDisp_offscreen(CameraId camId, void* param) {
    NpcEntry* entry = param; // cast to proper type
    u16 left, top, right, bottom;
    Mtx mtx;
    GXColor color;
    f32 rotY;

    sysWaitDrawSync();
    GXClearBoundingBox();
    rotY = reviseAngle(-entry->direction);
    mtx_setup(entry, mtx, -1);

    switch (dispGetCurWork()->renderMode) {
        case 0:
            npcDimColor(entry);

            npcLuigiPoseFlip(entry);
            animPoseMain(entry->poseId);
            animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
            break;
        case 1:
            animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
            break;
        case 2:
            animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
            break;
    }
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    offscreenAddBoundingBox(entry->offscreenId, left, top, right, bottom);
}

#pragma opt_propagation off
#pragma opt_lifetimes off

void npcDisp_blur(CameraId camId, void* param) {
    NpcEntry* entry = param;
    s32 i;
    s32 alpha;
    s32 flag;
    f32 rotY;
    f32 x;
    f32 z;
    Mtx mtx;

    rotY = reviseAngle(-entry->direction);
    flag = animPoseGetMaterialFlag(entry->poseId);
    x = 2.0f * npc_sin((6.2831855f * camGetPtr(camId)->viewYaw) / 360.0f);
    z = 2.0f * -npc_cos((6.2831855f * camGetPtr(camId)->viewYaw) / 360.0f);
    animPoseMain(entry->poseId);
    for (i = 4, alpha = 100; i > 0; i--, alpha -= 25) {
        mtx_setup(entry, mtx, i);
        MTXTransApply(mtx, mtx, x, 0.0f, z);
        animPoseSetMaterialFlagOn(entry->poseId, 0x40);
        animPoseSetMaterialEvtColor(entry->poseId, (GXColor){0xFF, 0xFF, 0xFF, (u8)(0x80 - alpha)});
        animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
        animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
        animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
    }
    animPoseSetMaterialFlagOff(entry->poseId, 0x40);
    animPoseSetMaterialFlagOn(entry->poseId, flag);
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
#endif
#ifndef NONMATCHING
#pragma pop
#endif

void npcInit(void) { // 1:1
    FieldBattleData* data;
    NpcWork* wp;

    wp = &work.field;
    wp->total = NPC_FIELD_MAX_COUNT;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(NpcEntry) * wp->total);
    memset(wp->entries, 0, sizeof(NpcEntry) * wp->total);

    release_wp = __memAlloc(HEAP_DEFAULT, sizeof(NpcFieldEntry) * wp->total);

    wp = &work.battle;
    wp->total = NPC_BATTLE_MAX_COUNT;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(NpcEntry) * wp->total);
    memset(wp->entries, 0, sizeof(NpcEntry) * wp->total);

    data = __memAlloc(HEAP_DEFAULT, sizeof(FieldBattleData));
    gp->fbatData = data;
    memset(gp->fbatData, 0, sizeof(FieldBattleData));
    data->mode = 0;
    npcMainCount = 0;
}

void npcReset(BOOL inBattle) {
    NpcWork* wp = npcGetWorkPtr2(inBattle);
    memset(wp->entries, 0, sizeof(NpcEntry) * wp->total);
    wp->count = 0;
    if (!inBattle) {
        gp->fbatData->mode = 0;
    }
    npcMainCount = 0;
}

s32 npcGetReactionOfLivingBody(BOOL inBattle) {
    return npcGetWorkPtr2(inBattle)->count;
}

#ifdef NONMATCHING
// TODO: fix entry->position delayed set-Vec with r6/r30
// TODO: a1 is desc/ription?
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
#endif
s32 npcEntry(const char* a1, const char* animName) {
#ifdef NONMATCHING
    NpcWork* wp;
    s32 i;
    NpcEntry* entry;
    s32 total;


    wp = gp->inBattle ? &work.battle : &work.field;
    total = wp->total;
    for (i = 0, entry = wp->entries; i < total; i++, entry++) {
        if (entry->flags & 1 && !strcmp(entry->description, a1)) {
            break;
        }
    }

    entry = wp->entries;
    for (i = 0; i < total; i++, entry++) {
        if (!(entry->flags & 1)) {
            break;
        }
    }
    memset(entry, 0, sizeof(NpcEntry));
    entry->flags = 3;
    strcpy(entry->description, a1);
    entry->poseId = animPoseEntry(animName, gp->inBattle != 0);
    if (entry->poseId == -2) {
        entry->poseId = animPoseEntry("hoshi", gp->inBattle != 0);
    }
    animPosePeraOn(entry->poseId);
    entry->position = (Vec){0.0f, 0.0f, 0.0f};
    entry->prevPosition = entry->position;
    entry->width = animPoseGetHeight(entry->poseId);
    entry->height = animPoseGetRadius(entry->poseId);
    entry->scale = (Vec){1.0f, 1.0f, 1.0f};
    entry->shadowScale = 1.0f;
    entry->field_108 = 0;
    entry->field_10C = "M_I_2";
    entry->field_198 = gp->renderTime;
    entry->field_188 = 0;
    entry->jumpGravity = 1.0f;
    entry->field_1D0 = 0.0f;
    entry->jumpYScale = 1.0f;
    entry->offscreenId = -1;
    entry->color = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    entry->cameraId = CAMERA_3D;
    entry->field_2F8 = 0;
    entry->balloonType = 1;
    if (animPoseGetVivianType(entry->poseId)) {
        entry->flags |= 0x4000000;
    }
    if (!strcmp(animName, (char*)str_802C31E0)) {
        entry->flags |= 0x800000u;
    }
    animPoseSetMaterialLightFlagOn(entry->poseId, 2);
    wp->count++;
    return i;
#endif
#ifndef NONMATCHING
	asm {
		lis r6, vec3_802c2f78@ha
	}
	asm volatile {
		mr r25, r3
		opword 0x7C9B2378
		addi r30, r6, vec3_802c2f78@l
		la r31, work(r13)
		lwz r5, gp(r13)
		opword 0x80050014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3BFF0014
		opword 0x835F0004
		opword 0x3B800000
		opword 0x83BF000C
		opword 0x4800002C
		opword 0x801D0000
		opword 0x540007FF
		opword 0x41820018
		opword 0x7F24CB78
		opword 0x387D0008
		bl strcmp
		opword 0x2C030000
		opword 0x41820014
		opword 0x3B9C0001
		opword 0x3BBD0340
		opword 0x7C1CD000
		opword 0x4180FFD4
		opword 0x839F000C
		opword 0x3BA00000
		opword 0x7F4903A6
		opword 0x2C1A0000
		opword 0x4081001C
		opword 0x801C0000
		opword 0x540007FF
		opword 0x41820010
		opword 0x3BBD0001
		opword 0x3B9C0340
		opword 0x4200FFEC
		opword 0x7F83E378
		opword 0x38800000
		opword 0x38A00340
		bl memset
		opword 0x38000003
		opword 0x7F24CB78
		opword 0x901C0000
		opword 0x387C0008
		bl strcpy
		lwz r4, gp(r13)
		opword 0x7F63DB78
		opword 0x80840014
		opword 0x7C0400D0
		opword 0x7C002378
		opword 0x54040FFE
		bl animPoseEntry
		opword 0x907C0104
		opword 0x801C0104
		opword 0x2C00FFFE
		opword 0x40820024
		lwz r4, gp(r13)
		la r3, str_80419C90(r2)
		opword 0x80840014
		opword 0x7C0400D0
		opword 0x7C002378
		opword 0x54040FFE
		bl animPoseEntry
		opword 0x907C0104
		opword 0x807C0104
		bl animPosePeraOn
		opword 0x807E0000
		opword 0x801E0004
		opword 0x907C008C
		opword 0x901C0090
		opword 0x801E0008
		opword 0x901C0094
		opword 0x807C008C
		opword 0x801C0090
		opword 0x907C0098
		opword 0x901C009C
		opword 0x801C0094
		opword 0x901C00A0
		opword 0x807C0104
		bl animPoseGetHeight
		opword 0xD03C014C
		opword 0x807C0104
		bl animPoseGetRadius
		opword 0xD03C0150
		opword 0x38E00000
		lfs f1, float_1_80419bb4(r2)
		la r5, str_80419C98(r2)
		opword 0x811E000C
		opword 0x3880FFFF
		opword 0x80DE0010
		opword 0x38600004
		lfs f0, float_0_80419b9c(r2)
		opword 0x38000001
		opword 0x911C00E0
		opword 0x90DC00E4
		opword 0x80DE0014
		opword 0x90DC00E8
		opword 0xD03C0154
		opword 0x90FC0108
		opword 0x90BC010C
		lwz r6, gp(r13)
		opword 0x80A60038
		opword 0x80C6003C
		opword 0x90DC019C
		opword 0x90BC0198
		opword 0x90FC018C
		opword 0x90FC0188
		opword 0xD03C01CC
		opword 0xD01C01D0
		opword 0xD03C01C8
		opword 0x909C0110
		lwz r4, dat_80419b8c(r2)
		opword 0x909C0114
		opword 0x907C01F4
		opword 0x90FC02F8
		opword 0x981C0317
		opword 0x807C0104
		bl animPoseGetVivianType
		opword 0x2C030000
		opword 0x41820010
		opword 0x801C0000
		opword 0x64000400
		opword 0x901C0000
		opword 0x7F63DB78
		opword 0x389E0268
		bl strcmp
		opword 0x2C030000
		opword 0x40820010
		opword 0x801C0000
		opword 0x64000080
		opword 0x901C0000
		opword 0x807C0104
		opword 0x38800002
		bl animPoseSetMaterialLightFlagOn
		opword 0x809F0000
		opword 0x7FA3EB78
		opword 0x38040001
		opword 0x901F0000
	}
#endif
}
#ifdef NONMATCHING

static const Vec sZeroVec3 = {0.0f, 0.0f, 0.0f};
#endif
#ifndef NONMATCHING
#pragma pop
#endif

NpcTribeInfo* npcGetTribe(const char* tribeName) { // 1:1
    NpcTribeInfo* tribe;

    for (tribe = npcTribe; tribe->nameJp; tribe++) {
        if (!strcmp(tribe->nameJp, tribeName)) {
            return tribe;
        }
    }
    return NULL;
}

void npcDelete(NpcEntry* entry) {
    int i;

    for (i = 0; i < 4; i++) {
        if (entry->slaves[i]) {
            entry->slaves[i]->master = NULL;
        }
        entry->slaves[i] = NULL;
    }

    if (entry->prev) {
        if (entry->next) {
            entry->prev->next = entry->next;
            entry->next->prev = entry->prev;
        } else {
            entry->prev->next = NULL;
        }
    } else {
        if (entry->next) {
            entry->next->prev = NULL;
        }
    }
    entry->flags &= ~2;
    if (entry->poseId >= 0) {
        animPoseRelease(entry->poseId);
    }
    entry->poseId = -1;
    entry->flags &= ~1;
    npcGetWorkPtrInline()->count--;
}

#ifdef NONMATCHING
void _npcDeleteGroup(NpcEntry* entry) { // recursively inlined, warning
    NpcEntry* s;
    int i;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void _npcDeleteGroup(NpcEntry* entry) {
	asm volatile {
		mr r27, r3
		opword 0x83E30328
		opword 0x281F0000
		opword 0x4182004C
		opword 0x807F0328
		opword 0x28030000
		opword 0x41820008
		bl _npcDeleteGroup
		opword 0x3BA00000
		opword 0x7FFEFB78
		opword 0x7FBCEB78
		opword 0x807E0330
		opword 0x28030000
		opword 0x4182000C
		bl npcDelete
		opword 0x939E0330
		opword 0x3BBD0001
		opword 0x3BDE0004
		opword 0x2C1D0004
		opword 0x4180FFE0
		opword 0x7FE3FB78
		bl npcDelete
		la r29, work(r13)
		opword 0x7F7FDB78
		opword 0x3B800000
		opword 0x3BBD0014
		opword 0x83DF0330
		opword 0x281E0000
		opword 0x41820108
		opword 0x807E0330
		opword 0x38000000
		opword 0x28030000
		opword 0x41820008
		opword 0x9003032C
		opword 0x901E0330
		opword 0x807E0334
		opword 0x28030000
		opword 0x41820008
		opword 0x9003032C
		opword 0x901E0334
		opword 0x389E0008
		opword 0x807E0338
		opword 0x28030000
		opword 0x41820008
		opword 0x9003032C
		opword 0x90040330
		opword 0x80640334
		opword 0x28030000
		opword 0x41820008
		opword 0x9003032C
		opword 0x90040334
		opword 0x807E0324
		opword 0x28030000
		opword 0x41820030
		opword 0x801E0328
		opword 0x28000000
		opword 0x41820018
		opword 0x90030328
		opword 0x801E0324
		opword 0x807E0328
		opword 0x90030324
		opword 0x48000024
		opword 0x38000000
		opword 0x90030328
		opword 0x48000018
		opword 0x807E0328
		opword 0x28030000
		opword 0x4182000C
		opword 0x38000000
		opword 0x90030324
		opword 0x801E0000
		opword 0x540007FA
		opword 0x901E0000
		opword 0x807E0104
		opword 0x2C030000
		opword 0x41800008
		bl animPoseRelease
		opword 0x3800FFFF
		opword 0x901E0104
		opword 0x801E0000
		opword 0x5400003C
		opword 0x901E0000
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x4182000C
		opword 0x7FA4EB78
		opword 0x48000008
		la r4, work(r13)
		opword 0x80640000
		opword 0x38000000
		opword 0x3863FFFF
		opword 0x90640000
		opword 0x901F0330
		opword 0x3B9C0001
		opword 0x3BFF0004
		opword 0x2C1C0004
		opword 0x4180FEE4
		opword 0x807B0330
		opword 0x38000000
		opword 0x28030000
		opword 0x41820008
		opword 0x9003032C
		opword 0x901B0330
		opword 0x807B0334
		opword 0x28030000
		opword 0x41820008
		opword 0x9003032C
		opword 0x901B0334
		opword 0x389B0008
		opword 0x807B0338
		opword 0x28030000
		opword 0x41820008
		opword 0x9003032C
		opword 0x90040330
		opword 0x80640334
		opword 0x28030000
		opword 0x41820008
		opword 0x9003032C
		opword 0x90040334
		opword 0x807B0324
		opword 0x28030000
		opword 0x41820030
		opword 0x801B0328
		opword 0x28000000
		opword 0x41820018
		opword 0x90030328
		opword 0x801B0324
		opword 0x807B0328
		opword 0x90030324
		opword 0x48000024
		opword 0x38000000
		opword 0x90030328
		opword 0x48000018
		opword 0x807B0328
		opword 0x28030000
		opword 0x4182000C
		opword 0x38000000
		opword 0x90030324
		opword 0x801B0000
		opword 0x540007FA
		opword 0x901B0000
		opword 0x807B0104
		opword 0x2C030000
		opword 0x41800008
		bl animPoseRelease
		opword 0x3800FFFF
		opword 0x901B0104
		opword 0x801B0000
		opword 0x5400003C
		opword 0x901B0000
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820008
		opword 0x48000008
		la r29, work(r13)
		opword 0x807D0000
		opword 0x3803FFFF
		opword 0x901D0000
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    if (entry->next) {
        _npcDeleteGroup(entry->next);
    }

    for (i = 0; i < 4; i++) {
        s = entry->slaves[i];
        if (s) {
            npcDelete(s);
            entry->slaves[i] = NULL;
        }
    }
    npcDelete(entry);
}

#endif
#ifndef NONMATCHING
#pragma dont_inline on
#endif
void npcDeleteGroup(NpcEntry* entry) {
    if (entry->master) {
        entry = entry->master;
    }
    while (entry->prev) {
        entry = entry->prev;
    }
    _npcDeleteGroup(entry);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param);
void fbatEncountCheck(void);
void fbatTalkMode(void);
void fbatBattleMode(void);
s32 kpaJumpChk(void);
s32 kpaFireAttackCheck(void);

void npcMoveG(NpcEntry* npc);
BOOL npcCheckHitMarioSide(NpcEntry* npc);
HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz);
s32 vivianGetStatus(void);
#define NPC_CHKMARIO(ok) do {     m = marioGetPtr();     if (*(u32*)m & 0x82000000) { ok = 0; break; }     if (*(u32*)m & 0xA) { ok = 0; break; }     if (*(s32*)((u8*)gp + 0x164) != 0) { ok = 0; break; }     if (seqGetSeq() != 2) { ok = 0; break; }     if (*(u16*)((u8*)m + 0x2E) == 0x19) { ok = 0; break; }     if (vivianGetStatus() != 0 && vivianGetStatus() != 1) { ok = 0; } else { ok = 1; } } while (0)
void shadowSetCollision(s32 shadow, s32 val);
s32 shadowEntry(f32 x, f32 y, f32 z, f32 size);
void animPoseVivianMain(s32 poseId, Vec* pos);
f32 sinfd(f32 degrees);
void npcKoopaModeMain(void);
BOOL npcCheckBlow(NpcEntry* npc);
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
void npcMain(void) {
#ifdef NONMATCHING
    const char* kpaSfx;
    NpcWork* npcwork;
    u8* fbat;
    NpcEntry* entry;
    int i;
    int total;
    f32 dir;
    f32 prio;
    f32 dist; Vec dv; Vec dv2;
    s32 fire, jump;

    npcwork = gp->inBattle ? &work.battle : &work.field;
    // npcwork = npcGetWorkPtr();
    marioGetPtr()->targetNpc = 0;
    kpaSfx = (char*)str_802C310C;

    npcMainCount++;

    total = npcwork->total;
    for (i = 0, entry = npcwork->entries; i < total; i++, entry++) {
        if (entry->flags & 1 && entry->flags & 2) {
            if (entry->flags & 0x8000) {
                animPoseGetAnimPosePtr(entry->poseId)->flags |= 0x100;
            } else {
                animPoseGetAnimPosePtr(entry->poseId)->flags &= ~0x100;
            }

            if (!(entry->flags & 0x100000)) {
                entry->jumpFlags |= 0x10;
            }
            if (entry->jumpFlags & 0x10000) {
                entry->jumpFlags &= ~0x10;
            }

            if (*(u16*)&entry->wFbatHitCheckRelated) {
                entry->wFbatHitCheckRelated = *(u16*)&entry->wFbatHitCheckRelated - 1;
            }

            if (entry->jumpFlags & 0x10) {
                entry->field_190 = gp->renderTime - entry->field_198;
                if (OSTicksToMilliseconds(entry->field_190) > 500) {
                    entry->field_190 = OSMillisecondsToTicks(16);
                }
                if (entry->flags & 0x20000) {
                    entry->field_178 += entry->field_190;
                } else {
                    entry->field_178 = 0;
                }
                entry->field_188 += entry->field_190;
                entry->field_198 = gp->renderTime;
                entry->field_1A0 = (f32)(OSTicksToMicroseconds(entry->field_188)) / 1000000.0f;
                entry->field_180 = (f32)(OSTicksToMicroseconds(entry->field_178)) / 1000000.0f;
                entry->moveDt = (f32)(OSTicksToMicroseconds(entry->field_190)) / 1000000.0f;
                entry->field_1A8 = (f32)(OSTicksToMicroseconds(entry->field_198)) / 1000000.0f;

            } else {
                entry->field_198 = gp->renderTime;
            }

            if (entry->flags & 2) {
                if (entry->jumpFlags & 0x100000) {
                    entry->jumpFlags |= 0x200000;
                } else {
                    entry->jumpFlags &= ~0x200000;
                }
                entry->jumpFlags &= ~0x100000;
                {
                    f32 f30v;
                    if (!strcmp(gp->currentMapName, (char*)str_802C3104) && !(entry->position.y > 365.0f)) {
                        entry->jumpFlags |= 0x100000;
                        if (!(entry->jumpFlags & 0x200000) && (entry->jumpFlags & 0x100000)) {
                            psndSFXOn_3D(kpaSfx, &entry->position);
                        }
                    }
                    if (entry->jumpFlags & 0x100000 && !(entry->jumpFlags & 0x10000000)) {
                        entry->field_1D0 = 100.0f;
                        f30v = 0.5f;
                    } else {
                        f30v = 1.0f;
                    }
                    if (entry->jumpFlags & 0x100000) {
                        entry->field_31E |= 1;
                    }
                    if (entry->jumpFlags & 0x10) {
                        if (entry->moveDt > 0.0f) {
                            f32 mx = entry->moveOffset.x;
                            f32 mz = entry->moveOffset.z;
                            if (entry->jumpFlags & 0x100000 && !(entry->jumpFlags & 0x10000000)) {
                                mx *= 0.5f;
                                mz *= 0.5f;
                            }
                            if (entry->flags & 0x8000000) {
                                mz = 0.0f;
                            }
                            if (entry->flags & 0x40000000) {
                                entry->position.x += mx;
                                entry->position.z += mz;
                            } else {
                                entry->wallHit = (u32)npcHitCheckSide(entry, &entry->position.x, &entry->position.z,
                                                                        &entry->moveDir, mx, mz);
                            }
                            entry->moveOffset.x = 0.0f;
                            entry->moveOffset.z = 0.0f;
                            npcMoveG(entry);
                        }
                        if (!(entry->flags & 8) && !(entry->flags & 0x20) && !(entry->flags & 0x4000)) {
                            npcCheckHitMarioSide(entry);
                        }
                        {
                            
                            PSVECSubtract(&entry->position, &entry->prevPosition, &dv);
                            if (entry->flags & 0x400 && entry->moveDt > 0.0f) {
                                f32 spd = npc_sqrtf(dv.x * dv.x + dv.z * dv.z) / entry->moveDt;
                                if (spd < 0.1f) {
                                    if (entry->field_108 != 1) {
                                        animPoseSetAnim(entry->poseId, entry->tribe->stayAnim, TRUE);
                                        entry->field_108 = 1;
                                    }
                                } else if (spd < entry->tribe->runStartSpeed * f30v) {
                                    if (entry->field_108 != 2) {
                                        animPoseSetAnim(entry->poseId, entry->tribe->walkAnimation, TRUE);
                                        entry->field_108 = 2;
                                    }
                                } else {
                                    if (entry->field_108 != 3) {
                                        animPoseSetAnim(entry->poseId, entry->tribe->runAnimation, TRUE);
                                        entry->field_108 = 3;
                                    }
                                }
                            }
                        }
                    }
                }
                if (entry->regularEvtId) {
                    EventEntry* evt = evtGetPtrID(entry->regularEvtId);
                    if (evt && !(evt->flags & 2)) {
                        s32 st = evt->wNpcEventType;
                        if (entry->blowEvent && st != 5 && st != 8) {
                            int trig;
                            trig = npcCheckBlow(entry);
                            if (trig) {
                                entry->interruptFlags |= 8;
                                goto interrupt;
                            }
                        }
                        if (entry->territoryType != 0 && (st == 1 || st == 2)) {
                            int trig;
                            trig = 0;
                            if (entry->territoryType == 1) {
                                f32 tz = entry->territoryBase.z - entry->position.z;
                                f32 tx = entry->territoryBase.x - entry->position.x;
                                f32 d = npc_sqrtf(tx * tx + tz * tz);
                                if (d > (st == 2 ? entry->territoryHoming.x : entry->territoryHoming.x)) {
                                    trig = 1;
                                }
                            } else if (entry->territoryType == 2) {
                                if (st == 2) {
                                    if (entry->position.x < entry->territoryBase.x - entry->territoryHoming.x ||
                                        entry->position.x > entry->territoryBase.x + entry->territoryHoming.x ||
                                        entry->position.z < entry->territoryBase.z - entry->territoryHoming.z ||
                                        entry->position.z > entry->territoryBase.z + entry->territoryHoming.z) {
                                        trig = 1;
                                    }
                                } else {
                                    if (entry->position.x < entry->territoryBase.x - entry->territoryLoiter.x ||
                                        entry->position.x > entry->territoryBase.x + entry->territoryLoiter.x ||
                                        entry->position.z < entry->territoryBase.z - entry->territoryLoiter.z ||
                                        entry->position.z > entry->territoryBase.z + entry->territoryLoiter.z) {
                                        trig = 1;
                                    }
                                }
                            }
                            if (trig) {
                                entry->interruptFlags |= 4;
                                goto interrupt;
                            }
                        }
                        if (st == 2) {
                            MarioWork* m = marioGetPtr();
                            f32 dx = m->position.x - entry->position.x;
                            f32 dy = m->position.y - entry->position.y;
                            f32 dz = m->position.z - entry->position.z;
                            int trig;
                            PSVECSubtract(&entry->prevPosition, &entry->position, &dv2);
                            dir = entry->direction;
                            if (entry->jumpFlags & 2) {
                                if (npc_sqrtf(dv2.x * dv2.x + dv2.z * dv2.z) > 0.05f) {
                                    dir = entry->moveDir;
                                }
                            }
                            trig = 0;
                            { s32 ok_; NPC_CHKMARIO(ok_); if (!ok_) {
                                trig = 1;
                            } else {
                                dist = npc_sqrtf(dx * dx + dz * dz);
                                if (dist > 0.25f * entry->homingRange) {
                                    if (dy > entry->territoryLoiter.y) {
                                        trig = 1;
                                    } else if (-dy > entry->territoryHoming.y) {
                                        trig = 1;
                                    } else if (dist > entry->homingRange) {
                                        trig = 1;
                                    } else if ((dist = angleABf(0.0f, 0.0f, dx, dz), __fabsf(compAngle(dir, dist))) >
                                               0.5f * entry->homingAngle) {
                                        trig = 1;
                                    }
                                }
                            }
                            }
                            if (trig) {
                                entry->interruptFlags |= 2;
                                goto interrupt;
                            }
                        }
                        if (st == 1 || st == 4) {
                            MarioWork* m = marioGetPtr();
                            f32 dx, dy, dz;
                            int trig;
                            Vec dv;
                            dx = m->position.x - entry->position.x;
                            dz = m->position.z - entry->position.z;
                            dy = m->position.y - entry->position.y;
                            dist = dx * dx + dz * dz;
                            npc_sqrtf(dist);
                            PSVECSubtract(&entry->prevPosition, &entry->position, &dv);
                            dir = reviseAngle(entry->direction) < 180.0f ? 90.0f : 270.0f;
                            trig = 1;
                            { s32 ok_; NPC_CHKMARIO(ok_); if (!ok_) {
                                trig = 0;
                            } else {
                                f32 a14;
                                dist = npc_sqrtf(dist);
                                if (dist > 0.25f * entry->searchRange) {
                                    if (dist > entry->searchRange) {
                                        trig = 0;
                                        goto done14;
                                    } else if ((a14 = angleABf(0.0f, 0.0f, dx, dz), __fabsf(compAngle(dir, a14))) >
                                               0.5f * entry->searchAngle) {
                                        trig = 0;
                                        goto done14;
                                    }
                                }
                                {
                                    if (dy > entry->territoryLoiter.y) {
                                        trig = 0;
                                    } else if (-dy > entry->territoryHoming.y) {
                                        trig = 0;
                                    } else if (st == 4) {
                                        if (entry->territoryType == 1) {
                                            f32 tz = entry->territoryBase.z - entry->position.z;
                                            f32 tx = entry->territoryBase.x - entry->position.x;
                                            f32 d = npc_sqrtf(tx * tx + tz * tz);
                                            if (d > 0.75 * entry->territoryHoming.x) {
                                                trig = 0;
                                            }
                                        } else {
                                            if (entry->position.x < entry->territoryBase.x - 0.75f * entry->territoryHoming.x ||
                                                entry->position.x > entry->territoryBase.x + 0.75f * entry->territoryHoming.x ||
                                                entry->position.z < entry->territoryBase.z - 0.75f * entry->territoryHoming.z ||
                                                entry->position.z > entry->territoryBase.z + 0.75f * entry->territoryHoming.z) {
                                                trig = 0;
                                            }
                                        }
                                    }
                                }
                            }
                            }
                            done14:
                            if (trig) {
                                entry->interruptFlags |= 1;
                            }
                        }
                    }
interrupt:
                    npcCheckInterrupt(entry);
                }
                if (!(entry->flags & 0x800)) {
                    CameraEntry* cam;

                    cam = camGetPtr((CameraId)4);
                    PSMTXMultVec((void*)((u8*)cam + 0x11C), &entry->position, &dv);
                    cam = camGetPtr((CameraId)4);
                    PSMTX44MultVec((void*)((u8*)cam + 0x15C), &dv, &dv);
                    if ((dv.z > -1.0f && dv.z < 0.0f && dv.x >= -2.0f && dv.x <= 2.0f && dv.y >= -2.0f && dv.y <= 2.0f) ||
                        (entry->flags & 0x40)) {
                        if (entry->color.r != 0xFF || entry->color.g != 0xFF || entry->color.b != 0xFF ||
                            entry->color.a != 0xFF) {
                            animPoseSetMaterialFlagOn(entry->poseId, 0x40);
                            animPoseSetMaterialEvtColor(entry->poseId, entry->color);
                        } else {
                            animPoseSetMaterialFlagOff(entry->poseId, 0x40);
                        }
                        prio = 5000.0f + 5000.0f * dv.z;
                        if (prio < 0.0f) {
                            prio = 0.0f;
                        } else if (prio > 10000.0f) {
                            prio = 10000.0f;
                        }
                        prio *= -1.0f;
                        if (!(entry->flags & 0x80) &&
                            (!(*(u16*)&entry->wFbatHitCheckRelated & 2) || (entry->jumpFlags & 0x10000))) {
                            if (entry->color.a != 0xFF) {
                                dispEntry((CameraId)entry->cameraId, prio, 2, npcDisp_xlu, entry);
                            } else {
                                dispEntry((CameraId)entry->cameraId, prio, 0, npcDisp, entry);
                                dispEntry((CameraId)entry->cameraId, prio, 1, npcDisp, entry);
                                dispEntry((CameraId)entry->cameraId, prio, 2, npcDisp, entry);
                            }
                            if (!(entry->flags & 0x4000000)) {
                                if (!(entry->flags & 0x40000)) {
                                    Vec sp = entry->position;
                                    if (entry->tribe) {
                                        sp.x += entry->tribe->shadowOffsetX * entry->scale.x * sinfd(reviseAngle(entry->direction) < 180.0f ? 90.0f : 270.0f);
                                        sp.y += entry->tribe->shadowOffsetY * entry->scale.y;
                                        sp.z += entry->tribe->shadowOffsetZ * entry->scale.z;
                                    }
                                    {
                                        s32 sh = shadowEntry(
                                            sp.x, sp.y, sp.z,
                                            1.33f * (entry->shadowScale * (entry->width / 3.0f * entry->scale.x)));
                                        if (entry->flags & 0x80000) {
                                            shadowSetCollision(sh, 0);
                                        }
                                    }
                                }
                            } else {
                                Vec vp = entry->position;
                                f32 o0, o1, o2, o3, o4, o5, o6;
                                o3 = 100.0f;
                                if (hitCheckFilter(NULL, &o0, &o1, &o2, &o3, &o4, &o5, &o6, vp.x, 1.0f + vp.y, vp.z,
                                                   0.0f, -1.0f, 0.0f)) {
                                    vp.y = o1;
                                }
                                animPoseVivianMain(entry->poseId, &vp);
                                {
                                    s32 sh = shadowEntry(entry->position.x, entry->position.y, entry->position.z,
                                                         entry->shadowScale * (entry->width / 3.0f * entry->scale.x));
                                    if (entry->flags & 0x80000) {
                                        shadowSetCollision(sh, 0);
                                    }
                                }
                            }
                            if (entry->flags & 0x100) {
                                dispEntry((CameraId)entry->cameraId, prio, 2, npcDisp_blur, entry);
                            }
                        }
                        if (entry->offscreenId != -1) {
                            if (entry->color.a != 0xFF) {
                                dispEntry((CameraId)1, prio, 2, npcDisp_offscreen_xlu, entry);
                            } else {
                                dispEntry((CameraId)1, prio, 0, npcDisp_offscreen, entry);
                                dispEntry((CameraId)1, prio, 1, npcDisp_offscreen, entry);
                                dispEntry((CameraId)1, prio, 2, npcDisp_offscreen, entry);
                            }
                        }
                    }
                }
                entry->prevPosition = entry->position;
                if (entry->flags & 0x100 && !(npcMainCount & 1)) {
                    entry->positionHistory[4] = entry->positionHistory[3];
                    entry->positionHistory[3] = entry->positionHistory[2];
                    entry->positionHistory[2] = entry->positionHistory[1];
                    entry->positionHistory[1] = entry->positionHistory[0];
                    entry->positionHistory[0] = entry->position;
                }
            }
            entry->jumpFlags &= ~0x10;
        }
    }

    fbat = *(u8**)((u8*)gp + 0x168);
    {
        u8* ann = fbat + 0x550;
        if (*(s32*)ann) {
            switch (*(s32*)(ann + 8)) {
            case 2:
                (*(s32*)(ann + 0xc))++;
                if (*(s32*)(ann + 0xc) < 20) {
                    *(f32*)(ann + 0x10) = intplGetValue(5, *(s32*)(ann + 0xc), 20, -600.0f, 0.0f);
                } else if (*(s32*)(ann + 0xc) < 80) {
                    *(f32*)(ann + 0x10) = 0.0f;
                } else if (*(s32*)(ann + 0xc) < 100) {
                    *(f32*)(ann + 0x10) = intplGetValue(1, *(s32*)(ann + 0xc) - 80, 20, 0.0f, 600.0f);
                } else {
                    *(s32*)(ann + 4) = 0;
                    break;
                }
                *(f32*)(ann + 0x14) = 0.0f;
                dispEntry((CameraId)9, 0.0f, 2, _fbatFirstAttackAnnouceDisp, ann);
                break;
            case 1:
                (*(s32*)(ann + 0xc))++;
                if (*(s32*)(ann + 0xc) > 60) {
                    *(s32*)(ann + 4) = 0;
                    break;
                }
                *(f32*)(ann + 0x10) = 0.0f;
                *(f32*)(ann + 0x14) = 0.0f;
                dispEntry((CameraId)9, 0.0f, 2, _fbatFirstAttackAnnouceDisp, ann);
                break;
            }
        }
        switch (*(s16*)fbat) {
        case 1:
            npcKoopaModeMain();
            break;
        case 2:
        case 3:
            fbatTalkMode();
            break;
        case 5:
            fbatBattleMode();
            break;
        case 6:
            break;
        }
        *(fbat + 0x54d) = 0;
    }
#endif
#ifndef NONMATCHING
	char _af_pad[176];
	asm volatile {
		lwz r3, gp(r13)
		lis r4, vec3_802c2f78@ha
		addi r30, r4, vec3_802c2f78@l
		la r25, work(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3B390014
		li r24, 0x0
		bl marioGetPtr
		opword 0x930301D8
		opword 0x3B7E0194
		opword 0x3BA00000
		lwz r3, npcMainCount(r13)
		opword 0x83990004
		opword 0x38030001
		opword 0x83F9000C
		stw r0, npcMainCount(r13)
		opword 0x48001624
		opword 0x807F0000
		opword 0x546007FF
		opword 0x41821610
		opword 0x546007BD
		opword 0x41821608
		opword 0x54600421
		opword 0x4182001C
		opword 0x807F0104
		bl animPoseGetAnimPosePtr
		opword 0x80030000
		opword 0x60000100
		opword 0x90030000
		opword 0x48000018
		opword 0x807F0104
		bl animPoseGetAnimPosePtr
		opword 0x80030000
		opword 0x5400062C
		opword 0x90030000
		opword 0x801F0000
		opword 0x540002D7
		opword 0x40820010
		opword 0x801F01D4
		opword 0x60000010
		opword 0x901F01D4
		opword 0x807F01D4
		opword 0x546003DF
		opword 0x4182000C
		opword 0x54600734
		opword 0x901F01D4
		opword 0xA07F0320
		opword 0x28030000
		opword 0x4182000C
		opword 0x3803FFFF
		opword 0xB01F0320
		opword 0x801F01D4
		opword 0x540006F7
		opword 0x4182021C
		lwz r5, gp(r13)
		opword 0x3C601062
		opword 0x38C34DD3
		opword 0x801F019C
		opword 0x8105003C
		opword 0x3C808000
		opword 0x80E50038
		opword 0x38A00000
		opword 0x807F0198
		opword 0x7C004010
		opword 0x901F0194
		opword 0x7C033910
		opword 0x901F0190
		opword 0x800400F8
		opword 0x807F0190
		opword 0x5400F0BE
		opword 0x809F0194
		opword 0x7C060016
		opword 0x5418D1BE
		opword 0x7F06C378
		bl __div2i
		opword 0x380001F4
		opword 0x38C00000
		opword 0x6CC58000
		opword 0x6C638000
		opword 0x7C040010
		opword 0x7C632910
		opword 0x7C652910
		opword 0x7C6300D1
		opword 0x41820010
		opword 0x57002036
		opword 0x901F0194
		opword 0x90DF0190
		opword 0x801F0000
		opword 0x5400039D
		opword 0x41820028
		opword 0x80BF017C
		opword 0x801F0194
		opword 0x809F0178
		opword 0x807F0190
		opword 0x7C050014
		opword 0x901F017C
		opword 0x7C041914
		opword 0x901F0178
		opword 0x48000010
		opword 0x38000000
		opword 0x901F017C
		opword 0x901F0178
		opword 0x80BF018C
		opword 0x3C60431C
		opword 0x801F0194
		opword 0x3C808000
		opword 0x80FF0188
		opword 0x3863DE83
		opword 0x7C050014
		opword 0x80DF0190
		opword 0x38A00000
		opword 0x901F018C
		opword 0x7C073114
		opword 0x901F0188
		lwz r6, gp(r13)
		opword 0x80060038
		opword 0x80C6003C
		opword 0x90DF019C
		opword 0x901F0198
		opword 0x800400F8
		opword 0x809F0188
		opword 0x5400F0BE
		opword 0x80DF018C
		opword 0x7C030016
		opword 0x54831838
		opword 0x54C41838
		opword 0x50C31F7E
		opword 0x54068BFE
		bl __div2i
		bl __cvt_sll_flt
		lfs f0, float_1E06_80419c74(r2)
		opword 0x3C60431C
		opword 0x3C808000
		opword 0x38A00000
		opword 0xEC010024
		opword 0x3863DE83
		opword 0xD01F01A0
		opword 0x800400F8
		opword 0x809F0178
		opword 0x5400F0BE
		opword 0x80DF017C
		opword 0x7C030016
		opword 0x54831838
		opword 0x54C41838
		opword 0x50C31F7E
		opword 0x54068BFE
		bl __div2i
		bl __cvt_sll_flt
		lfs f0, float_1E06_80419c74(r2)
		opword 0x3C60431C
		opword 0x3C808000
		opword 0x38A00000
		opword 0xEC010024
		opword 0x3863DE83
		opword 0xD01F0180
		opword 0x800400F8
		opword 0x809F0190
		opword 0x5400F0BE
		opword 0x80DF0194
		opword 0x7C030016
		opword 0x54831838
		opword 0x54C41838
		opword 0x50C31F7E
		opword 0x54068BFE
		bl __div2i
		bl __cvt_sll_flt
		lfs f0, float_1E06_80419c74(r2)
		opword 0x3C60431C
		opword 0x3C808000
		opword 0x38A00000
		opword 0xEC010024
		opword 0x3863DE83
		opword 0xD01F01A4
		opword 0x800400F8
		opword 0x809F0198
		opword 0x5400F0BE
		opword 0x80DF019C
		opword 0x7C030016
		opword 0x54831838
		opword 0x54C41838
		opword 0x50C31F7E
		opword 0x54068BFE
		bl __div2i
		bl __cvt_sll_flt
		lfs f0, float_1E06_80419c74(r2)
		opword 0xEC010024
		opword 0xD01F01A8
		opword 0x48000018
		lwz r3, gp(r13)
		opword 0x80030038
		opword 0x8063003C
		opword 0x907F019C
		opword 0x901F0198
		opword 0x801F0000
		opword 0x540007BD
		opword 0x41821344
		opword 0x807F01D4
		opword 0x546002D7
		opword 0x41820010
		opword 0x64600020
		opword 0x901F01D4
		opword 0x4800000C
		opword 0x546002D2
		opword 0x901F01D4
		opword 0x801F01D4
		opword 0x389E018C
		opword 0x54000314
		opword 0x901F01D4
		lwz r3, gp(r13)
		opword 0x3863012C
		bl strcmp
		opword 0x2C030000
		opword 0x40820040
		opword 0xC03F0090
		lfs f0, float_365_80419ba8(r2)
		opword 0xFC010040
		opword 0x41810030
		opword 0x801F01D4
		opword 0x64000010
		opword 0x901F01D4
		opword 0x807F01D4
		opword 0x54600295
		opword 0x40820018
		opword 0x546002D7
		opword 0x41820010
		opword 0x7F63DB78
		opword 0x389F008C
		bl psndSFXOn_3D
		opword 0x807F01D4
		opword 0x546002D7
		opword 0x4182001C
		opword 0x546000C7
		opword 0x40820014
		lfs f0, float_100_80419c18(r2)
		lfs f30, float_0p5_80419ba0(r2)
		opword 0xD01F01D0
		opword 0x48000008
		lfs f30, float_1_80419bb4(r2)
		opword 0x801F01D4
		opword 0x540002D7
		opword 0x41820010
		opword 0xA01F031E
		opword 0x60000001
		opword 0xB01F031E
		opword 0x807F01D4
		opword 0x546006F7
		opword 0x41820270
		opword 0xC03F01A4
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x40810088
		opword 0x546002D7
		opword 0xC03F01B4
		opword 0xC05F01BC
		opword 0x41820018
		opword 0x546000C7
		opword 0x40820010
		lfs f0, float_0p5_80419ba0(r2)
		opword 0xEC210032
		opword 0xEC420032
		opword 0x807F0000
		opword 0x54600109
		opword 0x41820008
		lfs f2, float_0_80419b9c(r2)
		opword 0x54600043
		opword 0x41820020
		opword 0xC01F008C
		opword 0xEC00082A
		opword 0xD01F008C
		opword 0xC01F0094
		opword 0xEC00102A
		opword 0xD01F0094
		opword 0x4800001C
		opword 0x7FE3FB78
		opword 0x389F008C
		opword 0x38BF0094
		opword 0x38DF01AC
		bl npcHitCheckSide
		opword 0x907F02FC
		lfs f0, float_0_80419b9c(r2)
		opword 0x7FE3FB78
		opword 0xD01F01B4
		opword 0xD01F01BC
		bl npcMoveG
		opword 0x807F0000
		opword 0x54600739
		opword 0x4082001C
		opword 0x546006B5
		opword 0x40820014
		opword 0x54600463
		opword 0x4082000C
		opword 0x7FE3FB78
		bl npcCheckHitMarioSide
		opword 0x387F008C
		opword 0x389F0098
		la r5, _af_pad+164
		bl PSVECSubtract
		opword 0x801F0000
		opword 0x5400056B
		opword 0x4182019C
		opword 0xC01F01A4
		lfs f2, float_0_80419b9c(r2)
		opword 0xFC001040
		opword 0x4081018C
		opword 0xC02100AC
		opword 0xC00100B4
		opword 0xEC210072
		opword 0xEC000032
		opword 0xEC81002A
		opword 0xFC041040
		opword 0x4081004C
		opword 0xFC202034
		opword 0xC87E01C0
		opword 0xC85E01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC010032
		opword 0xFC840032
		opword 0xFC802018
		opword 0x48000088
		opword 0xC81E01D0
		opword 0xFC040040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD081001C
		opword 0x3C007F80
		opword 0x8081001C
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0xC03F01A4
		lfs f0, float_0p1_80419bfc(r2)
		opword 0xEC240824
		opword 0xFC010040
		opword 0x40800030
		opword 0x801F0108
		opword 0x2C000001
		opword 0x41820084
		opword 0x809F0028
		opword 0x38A00001
		opword 0x807F0104
		opword 0x80840010
		bl animPoseSetAnim
		opword 0x38000001
		opword 0x901F0108
		opword 0x48000064
		opword 0x809F0028
		opword 0xC004003C
		opword 0xEC0007B2
		opword 0xFC010040
		opword 0x4080002C
		opword 0x801F0108
		opword 0x2C000002
		opword 0x41820044
		opword 0x807F0104
		opword 0x38A00001
		opword 0x80840018
		bl animPoseSetAnim
		opword 0x38000002
		opword 0x901F0108
		opword 0x48000028
		opword 0x801F0108
		opword 0x2C000003
		opword 0x4182001C
		opword 0x807F0104
		opword 0x38A00001
		opword 0x8084001C
		bl animPoseSetAnim
		opword 0x38000003
		opword 0x901F0108
		opword 0x807F011C
		opword 0x2C030000
		opword 0x41820B18
		bl evtGetPtrID
		opword 0x28030000
		opword 0x41820B04
		opword 0x88030008
		opword 0x540007BD
		opword 0x40820AF8
		opword 0x801F013C
		opword 0x8B430010
		opword 0x28000000
		opword 0x4182014C
		opword 0x2C1A0005
		opword 0x41820144
		opword 0x2C1A0008
		opword 0x4182013C
		opword 0x807F0000
		opword 0x54600085
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000110
		opword 0x546006B5
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000100
		opword 0x80BF008C
		opword 0x38610058
		opword 0x809F0090
		opword 0x801F0094
		opword 0x90A1004C
		opword 0x90A10058
		opword 0x9081005C
		opword 0x90010060
		opword 0x90810050
		opword 0xC03F014C
		opword 0x90010054
		bl cloudGetBreathPower
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38000001
		opword 0x480000BC
		opword 0x801F0090
		opword 0x38610064
		opword 0x80BF008C
		opword 0x90010050
		opword 0x809F0094
		opword 0xC05F0150
		lfs f1, float_0p5_80419ba0(r2)
		opword 0xC0010050
		opword 0x90A10064
		opword 0xEC02007C
		opword 0x9081006C
		opword 0xD0010050
		opword 0x80010050
		opword 0x90A1004C
		opword 0x90010068
		opword 0x90810054
		opword 0xC03F014C
		bl cloudGetBreathPower
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38000001
		opword 0x48000060
		opword 0x801F0090
		opword 0x38610070
		opword 0x80BF008C
		opword 0x90010050
		opword 0x809F0094
		opword 0xC01F0150
		opword 0xC0210050
		opword 0x90A10070
		opword 0xEC010028
		opword 0x90810078
		opword 0xD0010050
		opword 0x80010050
		opword 0x90A1004C
		opword 0x90010074
		opword 0x90810054
		opword 0xC03F014C
		bl cloudGetBreathPower
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38000001
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x41820014
		opword 0x801F0140
		opword 0x60000008
		opword 0x901F0140
		opword 0x480009A0
		opword 0x801F01F8
		opword 0x2C000000
		opword 0x41820200
		opword 0x2C1A0001
		opword 0x4182000C
		opword 0x2C1A0002
		opword 0x408201F0
		opword 0x2C000001
		opword 0x38A00000
		opword 0x40820120
		opword 0xC03F0204
		opword 0xC01F0094
		opword 0xC05F01FC
		opword 0xEC610028
		opword 0xC03F008C
		lfs f0, float_0_80419b9c(r2)
		opword 0xEC420828
		opword 0xEC2300F2
		opword 0xEC8208BA
		opword 0xFC040040
		opword 0x4081004C
		opword 0xFC202034
		opword 0xC87E01C0
		opword 0xC85E01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC010032
		opword 0xFC840032
		opword 0xFC802018
		opword 0x48000088
		opword 0xC81E01D0
		opword 0xFC040040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0810018
		opword 0x3C007F80
		opword 0x80810018
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0x2C1A0002
		opword 0x4082000C
		opword 0xC01F0214
		opword 0x48000008
		opword 0xC01F0214
		opword 0xFC040040
		opword 0x408100B8
		opword 0x38A00001
		opword 0x480000B0
		opword 0x2C000002
		opword 0x408200A8
		opword 0x2C1A0002
		opword 0x40820054
		opword 0xC05F01FC
		opword 0xC03F0214
		opword 0xC07F008C
		opword 0xEC020828
		opword 0xFC030040
		opword 0x41800034
		opword 0xEC02082A
		opword 0xFC030040
		opword 0x41810028
		opword 0xC05F0204
		opword 0xC03F021C
		opword 0xC07F0094
		opword 0xEC020828
		opword 0xFC030040
		opword 0x41800010
		opword 0xEC02082A
		opword 0xFC030040
		opword 0x40810058
		opword 0x38A00001
		opword 0x48000050
		opword 0xC05F01FC
		opword 0xC03F0208
		opword 0xC07F008C
		opword 0xEC020828
		opword 0xFC030040
		opword 0x41800034
		opword 0xEC02082A
		opword 0xFC030040
		opword 0x41810028
		opword 0xC05F0204
		opword 0xC03F0210
		opword 0xC07F0094
		opword 0xEC020828
		opword 0xFC030040
		opword 0x41800010
		opword 0xEC02082A
		opword 0xFC030040
		opword 0x40810008
		opword 0x38A00001
		opword 0x2C050000
		opword 0x41820014
		opword 0x801F0140
		opword 0x60000004
		opword 0x901F0140
		opword 0x48000798
		opword 0x2C1A0002
		opword 0x40820374
		bl marioGetPtr
		opword 0xC023008C
		opword 0x389F008C
		opword 0xC01F008C
		opword 0x38A100A0
		opword 0xC0630090
		opword 0xC05F0090
		opword 0xEFE10028
		opword 0xC0230094
		opword 0x387F0098
		opword 0xC01F0094
		opword 0xEFA31028
		opword 0xEF810028
		bl PSVECSubtract
		opword 0x801F01D4
		opword 0xC3DF0144
		opword 0x540007BD
		opword 0x41820100
		opword 0xC00100A0
		opword 0xC02100A8
		opword 0xEC400032
		lfs f0, float_0_80419b9c(r2)
		opword 0xEC210072
		opword 0xEC82082A
		opword 0xFC040040
		opword 0x4081004C
		opword 0xFC202034
		opword 0xC87E01C0
		opword 0xC85E01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC010032
		opword 0xFC840032
		opword 0xFC802018
		opword 0x48000088
		opword 0xC81E01D0
		opword 0xFC040040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0810014
		opword 0x3C007F80
		opword 0x80810014
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		lfs f0, float_0p05_80419c78(r2)
		opword 0xFC040040
		opword 0x40810008
		opword 0xC3DF01AC
		opword 0x3B200000
		bl marioGetPtr
		opword 0x7C781B78
		opword 0x80630000
		opword 0x74608200
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000078
		opword 0x7060000A
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000068
		lwz r3, gp(r13)
		opword 0x80030164
		opword 0x2C000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000050
		bl seqGetSeq
		opword 0x2C030002
		opword 0x4182000C
		opword 0x38000000
		opword 0x4800003C
		opword 0xA018002E
		opword 0x28000019
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000028
		bl vivianGetStatus
		opword 0x2C030000
		opword 0x41820018
		bl vivianGetStatus
		opword 0x2C030001
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x4082000C
		opword 0x3B200001
		opword 0x48000174
		opword 0xEC3C0732
		lfs f0, float_0_80419b9c(r2)
		opword 0xEC9F0FFA
		opword 0xFC040040
		opword 0x4081004C
		opword 0xFC202034
		opword 0xC87E01C0
		opword 0xC85E01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC010032
		opword 0xFC840032
		opword 0xFC802018
		opword 0x48000088
		opword 0xC81E01D0
		opword 0xFC040040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0810010
		opword 0x3C007F80
		opword 0x80810010
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		lfs f0, float_0p25_80419c7c(r2)
		opword 0xC05F0228
		opword 0xEC0000B2
		opword 0xFC040040
		opword 0x40810080
		opword 0xC01F020C
		opword 0xFC1D0040
		opword 0x4081000C
		opword 0x3B200001
		opword 0x4800006C
		opword 0xFC20E850
		opword 0xC01F0218
		opword 0xFC010040
		opword 0x4081000C
		opword 0x3B200001
		opword 0x48000054
		opword 0xFC041040
		opword 0x4081000C
		opword 0x3B200001
		opword 0x48000044
		lfs f1, float_0_80419b9c(r2)
		opword 0xFC60F890
		opword 0xFC80E090
		opword 0xFC400890
		bl angleABf
		opword 0xFC000890
		opword 0xFC20F090
		opword 0xFC400090
		bl compAngle
		lfs f2, float_0p5_80419ba0(r2)
		opword 0xFC200A10
		opword 0xC01F022C
		opword 0xEC020032
		opword 0xFC010040
		opword 0x40810008
		opword 0x3B200001
		opword 0x2C190000
		opword 0x41820014
		opword 0x801F0140
		opword 0x60000002
		opword 0x901F0140
		opword 0x48000420
		opword 0x2C1A0001
		opword 0x4182000C
		opword 0x2C1A0004
		opword 0x40820410
		bl marioGetPtr
		opword 0xC0230094
		opword 0xC01F0094
		opword 0xC043008C
		fsubs f27, f1, f0
		opword 0xC01F008C
		opword 0xC0630090
		opword 0xEF820028
		opword 0xC05F0090
		opword 0xEC3B06F2
		lfs f0, float_0_80419b9c(r2)
		opword 0xEFA31028
		opword 0xEFDC0F3A
		opword 0xFC1E0040
		opword 0x387F0098
		opword 0x389F008C
		opword 0x38A10094
		bl PSVECSubtract
		opword 0xC03F0144
		bl reviseAngle
		lfs f0, float_180_80419bec(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f31, float_90_80419bd0(r2)
		opword 0x48000008
		lfs f31, float_270_80419be4(r2)
		opword 0x3B200001
		bl marioGetPtr
		opword 0x7C781B78
		opword 0x80630000
		opword 0x74608200
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000078
		opword 0x7060000A
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000068
		lwz r3, gp(r13)
		opword 0x80030164
		opword 0x2C000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000050
		bl seqGetSeq
		opword 0x2C030002
		opword 0x4182000C
		opword 0x38000000
		opword 0x4800003C
		opword 0xA018002E
		opword 0x28000019
		opword 0x4082000C
		opword 0x38000000
		opword 0x48000028
		bl vivianGetStatus
		opword 0x2C030000
		opword 0x41820018
		bl vivianGetStatus
		opword 0x2C030001
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x4082000C
		opword 0x3B200000
		opword 0x480002F0
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC1E0040
		opword 0x4081004C
		opword 0xFC20F034
		opword 0xC87E01C0
		opword 0xC85E01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1E103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1E103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1E103C
		opword 0xFC010032
		opword 0xFFDE0032
		opword 0xFFC0F018
		opword 0x48000088
		opword 0xC81E01D0
		opword 0xFC1E0040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f30, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD3C1000C
		opword 0x3C007F80
		opword 0x8081000C
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f30, __float_nan@l(r3)
		lfs f0, float_0p25_80419c7c(r2)
		opword 0xC03F0220
		opword 0xEC000072
		opword 0xFC1E0040
		opword 0x40810058
		opword 0xFC1E0840
		opword 0x4081000C
		opword 0x3B200000
		opword 0x480001F4
		lfs f1, float_0_80419b9c(r2)
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFC400890
		bl angleABf
		opword 0xFC000890
		opword 0xFC20F890
		opword 0xFC400090
		bl compAngle
		lfs f2, float_0p5_80419ba0(r2)
		opword 0xFC200A10
		opword 0xC01F0224
		opword 0xEC020032
		opword 0xFC010040
		opword 0x4081000C
		opword 0x3B200000
		opword 0x480001B0
		opword 0xC01F020C
		opword 0xFC1D0040
		opword 0x4081000C
		opword 0x3B200000
		opword 0x4800019C
		opword 0xFC20E850
		opword 0xC01F0218
		opword 0xFC010040
		opword 0x4081000C
		opword 0x3B200000
		opword 0x48000184
		opword 0x2C1A0004
		opword 0x4082017C
		opword 0x801F01F8
		opword 0x2C000001
		opword 0x40820118
		opword 0xC03F0204
		opword 0xC01F0094
		opword 0xC05F01FC
		opword 0xEC610028
		opword 0xC03F008C
		lfs f0, float_0_80419b9c(r2)
		opword 0xEC420828
		opword 0xEC2300F2
		opword 0xEC8208BA
		opword 0xFC040040
		opword 0x4081004C
		opword 0xFC202034
		opword 0xC87E01C0
		opword 0xC85E01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC010032
		opword 0xFC840032
		opword 0xFC802018
		opword 0x48000088
		opword 0xC81E01D0
		opword 0xFC040040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0810008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0xC83E0260
		opword 0xC01F0214
		opword 0xFC010032
		opword 0xFC040040
		opword 0x40810064
		opword 0x3B200000
		opword 0x4800005C
		lfs f1, float_0p75_80419bf4(r2)
		opword 0xC01F0214
		opword 0xC07F01FC
		opword 0xEC410032
		opword 0xC09F008C
		opword 0xEC031028
		opword 0xFC040040
		opword 0x41800038
		opword 0xEC03102A
		opword 0xFC040040
		opword 0x4181002C
		opword 0xC01F021C
		opword 0xC05F0204
		opword 0xEC210032
		opword 0xC07F0094
		opword 0xEC020828
		opword 0xFC030040
		opword 0x41800010
		opword 0xEC02082A
		opword 0xFC030040
		opword 0x40810008
		opword 0x3B200000
		opword 0x2C190000
		opword 0x41820010
		opword 0x801F0140
		opword 0x60000001
		opword 0x901F0140
		opword 0x7FE3FB78
		bl npcCheckInterrupt
		opword 0x801F0000
		opword 0x54000529
		opword 0x40820438
		opword 0x38600004
		bl camGetPtr
		opword 0x3863011C
		opword 0x389F008C
		opword 0x38A100AC
		bl PSMTXMultVec
		opword 0x38600004
		bl camGetPtr
		opword 0x388100AC
		opword 0x3863015C
		opword 0x7C852378
		bl PSMTX44MultVec
		opword 0xC02100B4
		lfs f0, float_neg1_80419bf8(r2)
		opword 0xFC010040
		opword 0x40810050
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x40800044
		opword 0xC04100AC
		lfs f1, float_neg2_80419c80(r2)
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820030
		lfs f0, float_2_80419c5c(r2)
		opword 0xFC020040
		opword 0x4C401382
		opword 0x40820020
		opword 0xC04100B0
		opword 0xFC020840
		opword 0x4C411382
		opword 0x40820010
		opword 0xFC020040
		opword 0x4C401382
		opword 0x41820010
		opword 0x801F0000
		opword 0x54000673
		opword 0x418203A0
		opword 0x881F0114
		opword 0x280000FF
		opword 0x40820028
		opword 0x881F0115
		opword 0x280000FF
		opword 0x4082001C
		opword 0x881F0116
		opword 0x280000FF
		opword 0x40820010
		opword 0x881F0117
		opword 0x280000FF
		opword 0x41820028
		opword 0x807F0104
		opword 0x38800040
		bl animPoseSetMaterialFlagOn
		opword 0x801F0114
		opword 0x38810020
		opword 0x90010020
		opword 0x807F0104
		bl animPoseSetMaterialEvtColor
		opword 0x48000010
		opword 0x807F0104
		opword 0x38800040
		bl animPoseSetMaterialFlagOff
		lfs f2, float_5000_80419c84(r2)
		opword 0xC02100B4
		lfs f0, float_0_80419b9c(r2)
		opword 0xEFC2107A
		opword 0xFC1E0040
		opword 0x4080000C
		opword 0xFFC00090
		opword 0x48000014
		lfs f0, float_10000_80419c88(r2)
		opword 0xFC1E0040
		opword 0x40810008
		opword 0xFFC00090
		opword 0x801F0000
		lfs f0, float_neg1_80419bf8(r2)
		opword 0x54000631
		opword 0xEFDE0032
		opword 0x40820270
		opword 0xA01F0320
		opword 0x540007BD
		opword 0x41820010
		opword 0x801F01D4
		opword 0x540003DF
		opword 0x41820258
		opword 0x881F0117
		opword 0x280000FF
		opword 0x41820024
		lis r3, npcDisp_xlu@ha
		opword 0xFC20F090
		addi r5, r3, npcDisp_xlu@l
		opword 0x807F01F4
		opword 0x7FE6FB78
		opword 0x38800002
		bl dispEntry
		opword 0x48000058
		lis r3, npcDisp@ha
		opword 0xFC20F090
		addi r5, r3, npcDisp@l
		opword 0x807F01F4
		opword 0x7FE6FB78
		opword 0x38800000
		bl dispEntry
		lis r3, npcDisp@ha
		opword 0xFC20F090
		addi r5, r3, npcDisp@l
		opword 0x807F01F4
		opword 0x7FE6FB78
		opword 0x38800001
		bl dispEntry
		lis r3, npcDisp@ha
		opword 0xFC20F090
		addi r5, r3, npcDisp@l
		opword 0x807F01F4
		opword 0x7FE6FB78
		opword 0x38800002
		bl dispEntry
		opword 0x807F0000
		opword 0x5460014B
		opword 0x408200E4
		opword 0x5460035B
		opword 0x4082019C
		opword 0x801F0028
		opword 0x809F008C
		opword 0x807F0090
		opword 0x28000000
		opword 0x801F0094
		opword 0x90810088
		opword 0x9061008C
		opword 0x90010090
		opword 0x4182006C
		opword 0xC03F0144
		bl reviseAngle
		lfs f0, float_180_80419bec(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f1, float_90_80419bd0(r2)
		opword 0x48000008
		lfs f1, float_270_80419be4(r2)
		bl sinfd
		opword 0x807F0028
		opword 0xC01F00E0
		opword 0xC0630030
		opword 0xC0410088
		opword 0xECA30032
		opword 0xC0830034
		opword 0xC07F00E4
		opword 0xC001008C
		opword 0xECA5107A
		opword 0xC0430038
		opword 0xEC6400FA
		opword 0xC03F00E8
		opword 0xC0010090
		opword 0xD0A10088
		opword 0xEC02007A
		opword 0xD061008C
		opword 0xD0010090
		opword 0xC05F014C
		lfs f1, float_3_80419c08(r2)
		opword 0xC01F00E0
		opword 0xEC820824
		opword 0xC0BF0154
		lfs f6, float_1p33_80419c8c(r2)
		opword 0xC0210088
		opword 0xC041008C
		opword 0xC0610090
		opword 0xEC040032
		opword 0xEC050032
		opword 0xEC860032
		bl shadowEntry
		opword 0x801F0000
		opword 0x54000319
		opword 0x418200D0
		opword 0x38800000
		bl shadowSetCollision
		opword 0x480000C4
		opword 0x807F008C
		opword 0x3881003C
		opword 0x801F0090
		opword 0x38A10038
		lfs f4, float_0_80419b9c(r2)
		opword 0x38C10034
		opword 0x9061007C
		opword 0x38E10030
		lfs f1, float_1_80419bb4(r2)
		opword 0xFCC02090
		opword 0x90010080
		opword 0x3901002C
		lfs f3, float_100_80419c18(r2)
		opword 0x39210028
		opword 0x801F0094
		opword 0xC0010080
		opword 0x39410024
		opword 0x90010084
		opword 0x38600000
		opword 0xEC41002A
		opword 0xC021007C
		opword 0xD0610030
		opword 0xC0610084
		lfs f5, float_neg1_80419bf8(r2)
		bl hitCheckFilter
		opword 0x28030000
		opword 0x4182000C
		opword 0xC0010038
		opword 0xD0010080
		opword 0x807F0104
		opword 0x3881007C
		bl animPoseVivianMain
		opword 0xC05F014C
		lfs f1, float_3_80419c08(r2)
		opword 0xC01F00E0
		opword 0xEC820824
		opword 0xC0BF0154
		opword 0xC03F008C
		opword 0xC05F0090
		opword 0xC07F0094
		opword 0xEC040032
		opword 0xEC850032
		bl shadowEntry
		opword 0x801F0000
		opword 0x54000319
		opword 0x4182000C
		opword 0x38800000
		bl shadowSetCollision
		opword 0x801F0000
		opword 0x540005EF
		opword 0x41820020
		lis r3, npcDisp_blur@ha
		opword 0xFC20F090
		addi r5, r3, npcDisp_blur@l
		opword 0x807F01F4
		opword 0x7FE6FB78
		opword 0x38800002
		bl dispEntry
		opword 0x801F0110
		opword 0x2C00FFFF
		opword 0x41820084
		opword 0x881F0117
		opword 0x280000FF
		opword 0x41820024
		opword 0xFC20F090
		lis r3, npcDisp_offscreen_xlu@ha
		addi r5, r3, npcDisp_offscreen_xlu@l
		opword 0x7FE6FB78
		opword 0x38600001
		opword 0x38800002
		bl dispEntry
		opword 0x48000058
		opword 0xFC20F090
		lis r3, npcDisp_offscreen@ha
		addi r5, r3, npcDisp_offscreen@l
		opword 0x7FE6FB78
		opword 0x38600001
		opword 0x38800000
		bl dispEntry
		opword 0xFC20F090
		lis r3, npcDisp_offscreen@ha
		addi r5, r3, npcDisp_offscreen@l
		opword 0x7FE6FB78
		opword 0x38600001
		opword 0x38800001
		bl dispEntry
		opword 0xFC20F090
		lis r3, npcDisp_offscreen@ha
		addi r5, r3, npcDisp_offscreen@l
		opword 0x7FE6FB78
		opword 0x38600001
		opword 0x38800002
		bl dispEntry
		opword 0x807F008C
		opword 0x801F0090
		opword 0x907F0098
		opword 0x901F009C
		opword 0x801F0094
		opword 0x901F00A0
		opword 0x801F0000
		opword 0x540005EF
		opword 0x41820088
		lwz r0, npcMainCount(r13)
		opword 0x540007FF
		opword 0x4082007C
		opword 0x807F00C8
		opword 0x801F00CC
		opword 0x907F00D4
		opword 0x901F00D8
		opword 0x801F00D0
		opword 0x901F00DC
		opword 0x807F00BC
		opword 0x801F00C0
		opword 0x907F00C8
		opword 0x901F00CC
		opword 0x801F00C4
		opword 0x901F00D0
		opword 0x807F00B0
		opword 0x801F00B4
		opword 0x907F00BC
		opword 0x901F00C0
		opword 0x801F00B8
		opword 0x901F00C4
		opword 0x807F00A4
		opword 0x801F00A8
		opword 0x907F00B0
		opword 0x901F00B4
		opword 0x801F00AC
		opword 0x901F00B8
		opword 0x807F008C
		opword 0x801F0090
		opword 0x907F00A4
		opword 0x901F00A8
		opword 0x801F0094
		opword 0x901F00AC
		opword 0x801F01D4
		opword 0x54000734
		opword 0x901F01D4
		opword 0x3BBD0001
		opword 0x3BFF0340
		opword 0x7C1DE000
		opword 0x4180E9DC
		lwz r3, gp(r13)
		opword 0x83630168
		opword 0x3B1B0550
		opword 0x801B0550
		opword 0x2C000000
		opword 0x41820108
		opword 0x80180008
		opword 0x2C000002
		opword 0x41820014
		opword 0x408000F8
		opword 0x2C000001
		opword 0x408000A8
		opword 0x480000EC
		opword 0x8078000C
		opword 0x38030001
		opword 0x9018000C
		opword 0x8098000C
		opword 0x2C040014
		opword 0x40800020
		lfs f1, float_neg600_80419c0c(r2)
		opword 0x38600005
		lfs f2, float_0_80419b9c(r2)
		opword 0x38A00014
		bl intplGetValue
		opword 0xD0380010
		opword 0x4800004C
		opword 0x2C040050
		opword 0x40800010
		lfs f0, float_0_80419b9c(r2)
		opword 0xD0180010
		opword 0x48000038
		opword 0x2C040064
		opword 0x40800024
		lfs f1, float_0_80419b9c(r2)
		opword 0x3884FFB0
		lfs f2, float_600_80419c10(r2)
		opword 0x38600001
		opword 0x38A00014
		bl intplGetValue
		opword 0xD0380010
		opword 0x48000010
		opword 0x38000000
		opword 0x90180004
		opword 0x48000070
		lfs f1, float_0_80419b9c(r2)
		lis r3, _fbatFirstAttackAnnouceDisp@ha
		addi r5, r3, _fbatFirstAttackAnnouceDisp@l
		opword 0x7F06C378
		opword 0xD0380014
		opword 0x38600009
		opword 0x38800002
		bl dispEntry
		opword 0x4800004C
		opword 0x8078000C
		opword 0x38030001
		opword 0x9018000C
		opword 0x8018000C
		opword 0x2C00003C
		opword 0x40810010
		opword 0x38000000
		opword 0x90180004
		opword 0x48000028
		lfs f1, float_0_80419b9c(r2)
		lis r3, _fbatFirstAttackAnnouceDisp@ha
		addi r5, r3, _fbatFirstAttackAnnouceDisp@l
		opword 0x7F06C378
		opword 0xD0380010
		opword 0x38600009
		opword 0x38800002
		opword 0xD0380014
		bl dispEntry
		opword 0xA81B0000
		opword 0x2C000004
		opword 0x418200E8
		opword 0x40800014
		opword 0x2C000001
		opword 0x4182001C
		opword 0x408000CC
		opword 0x480000D4
		opword 0x2C000006
		opword 0x418200CC
		opword 0x408000C8
		opword 0x480000C0
		bl fbatEncountCheck
		lwz r3, gp(r13)
		opword 0x83430168
		bl marioGetPtr
		opword 0x8803003C
		opword 0x3B800000
		opword 0x7C791B78
		opword 0x2C000002
		opword 0x7F98E378
		opword 0x4082000C
		bl kpaJumpChk
		opword 0x7C7C1B78
		opword 0x8819003C
		opword 0x2C000002
		opword 0x4082000C
		bl kpaFireAttackCheck
		opword 0x7C781B78
		opword 0x2C1C0000
		opword 0x41820058
		opword 0x807A057C
		opword 0x2C030000
		opword 0x40810040
		opword 0x801A0578
		opword 0x2C000002
		opword 0x41800034
		opword 0x80B9008C
		opword 0x38810040
		opword 0x80190090
		lfs f0, float_60_80419ba4(r2)
		opword 0x90010044
		opword 0xC0210044
		opword 0x90A10040
		opword 0xEC01002A
		opword 0x80190094
		opword 0x90010048
		opword 0xD0010044
		bl kpaAddScorePos
		opword 0x38000000
		opword 0x901A0578
		opword 0x901A057C
		opword 0x2C180000
		opword 0x4082001C
		opword 0x38000000
		opword 0x901A0574
		opword 0x48000010
		bl fbatTalkMode
		opword 0x48000008
		bl fbatBattleMode
		opword 0x38000000
		opword 0x981B054D
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

NpcEntry* npcNameToPtr(const char* name) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;
    for (i = 0; i < total; i++, entry++) {
        if (entry->flags & 1 && !strcmp(entry->description, name)) {
            break;
        }
    }
    return entry;
}

NpcEntry* npcNameToPtr_NoAssert(const char* name) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;
    for (i = 0; i < total; i++, entry++) {
        if (entry->flags & 1 && !strcmp(entry->description, name)) {
            break;
        }
    }
    if (i >= total) {
        return NULL;
    }
    return entry;
}

void npcSetMarioAutoTalkPose(const char* stayPose, const char* talkPose) {
    strcpy(MarioStayPose, stayPose);
    strcpy(MarioTalkPose, talkPose);
}

#ifdef NONMATCHING
#pragma opt_propagation off
#pragma opt_lifetimes off
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void npcSetTalkPose(const char* name) {
#ifdef NONMATCHING
    PartyEntry* party;
    NpcEntry* npc;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x93C10018
		opword 0x93A10014
		opword 0x93810010
		opword 0x7C7C1B78
		opword 0x88030000
		opword 0x7C000775
		opword 0x41820110
		lis r4, str_802C31C0@ha
		addi r4, r4, str_802C31C0@l
		bl strcmp
		opword 0x2C030000
		opword 0x418200FC
		opword 0x7F83E378
		la r4, str_80419C64(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820020
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x418200D8
		opword 0x38800007
		bl partyChgPoseId
		opword 0x480000CC
		lis r4, str_802C31CC@ha
		opword 0x7F83E378
		addi r4, r4, str_802C31CC@l
		bl strcmp
		opword 0x2C030000
		opword 0x40820020
		bl marioGetExtraPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x418200A4
		opword 0x38800007
		bl partyChgPoseId
		opword 0x48000098
		opword 0x7F83E378
		la r4, str_80419C6C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820010
		la r3, MarioTalkPose(r13)
		bl marioChgPose
		opword 0x48000078
		lwz r3, gp(r13)
		la r4, work(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820008
		opword 0x38840014
		opword 0x83C40004
		opword 0x3BA00000
		opword 0x83E4000C
		opword 0x4800002C
		opword 0x801F0000
		opword 0x540007FF
		opword 0x41820018
		opword 0x7F84E378
		opword 0x387F0008
		bl strcmp
		opword 0x2C030000
		opword 0x41820014
		opword 0x3BBD0001
		opword 0x3BFF0340
		opword 0x7C1DF000
		opword 0x4180FFD4
		opword 0x801F0000
		opword 0x540005AD
		opword 0x41820014
		opword 0x807F0104
		opword 0x389F006C
		opword 0x38A00001
		bl animPoseSetAnim
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x83810010
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    if (*(s8*)name == 0) {
        return;
    }
    if (!strcmp(name, (char*)str_802C31C0)) {
        return;
    }
    if (!strcmp(name, "party")) {
        party = partyGetPtr(marioGetPartyId());
        if (party) {
            partyChgPoseId(party, 7);
        }
    } else if (!strcmp(name, (char*)str_802C31CC)) {
        party = partyGetPtr(marioGetExtraPartyId());
        if (party) {
            partyChgPoseId(party, 7);
        }
    } else if (!strcmp(name, "mario")) {
        marioChgPose(MarioTalkPose);
    } else {
        npc = npcNameToPtr(name);
        if (npc->flags & 0x200) {
            animPoseSetAnim(npc->poseId, npc->talkAnim, TRUE);
        }
    }
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void npcSetStayPose(const char* name) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x93C10018
		opword 0x93A10014
		opword 0x93810010
		opword 0x7C7C1B78
		opword 0x88030000
		opword 0x7C000775
		opword 0x41820110
		lis r4, str_802C31C0@ha
		addi r4, r4, str_802C31C0@l
		bl strcmp
		opword 0x2C030000
		opword 0x418200FC
		opword 0x7F83E378
		la r4, str_80419C64(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820020
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x418200D8
		opword 0x38800001
		bl partyChgPoseId
		opword 0x480000CC
		lis r4, str_802C31CC@ha
		opword 0x7F83E378
		addi r4, r4, str_802C31CC@l
		bl strcmp
		opword 0x2C030000
		opword 0x40820020
		bl marioGetExtraPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x418200A4
		opword 0x38800001
		bl partyChgPoseId
		opword 0x48000098
		opword 0x7F83E378
		la r4, str_80419C6C(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x40820010
		la r3, MarioStayPose(r13)
		bl marioChgPose
		opword 0x48000078
		lwz r3, gp(r13)
		la r4, work(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820008
		opword 0x38840014
		opword 0x83C40004
		opword 0x3BA00000
		opword 0x83E4000C
		opword 0x4800002C
		opword 0x801F0000
		opword 0x540007FF
		opword 0x41820018
		opword 0x7F84E378
		opword 0x387F0008
		bl strcmp
		opword 0x2C030000
		opword 0x41820014
		opword 0x3BBD0001
		opword 0x3BFF0340
		opword 0x7C1DF000
		opword 0x4180FFD4
		opword 0x801F0000
		opword 0x540005AD
		opword 0x41820014
		opword 0x807F0104
		opword 0x389F004C
		opword 0x38A00001
		bl animPoseSetAnim
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x83810010
		opword 0x7C0803A6
		opword 0x38210020
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
void npcSetStayPose(const char* name) {
    PartyEntry* party;
    NpcEntry* npc;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
BOOL npcCheckHitMarioSide(NpcEntry* npc) {
	char _af_pad[20];
	asm volatile {
		lis r4, vec3_802c2f78@ha
		mr r29, r3
		addi r30, r4, vec3_802c2f78@l
		bl marioGetPtr
		opword 0x7C7F1B78
		opword 0xC03D0090
		opword 0xC0430090
		opword 0xC00301B8
		opword 0xEC02002A
		opword 0xFC010040
		opword 0x4081000C
		opword 0x38600000
		opword 0x480004E4
		opword 0xC01D0150
		opword 0xEC01002A
		opword 0xFC020040
		opword 0x4081000C
		opword 0x38600000
		opword 0x480004CC
		opword 0xC01F008C
		la r3, _af_pad+4
		opword 0x389D008C
		opword 0xD001000C
		opword 0xC01F0094
		opword 0xD0010014
		opword 0xD0210010
		bl PSVECDistance
		opword 0xC05F01B4
		opword 0xC01D014C
		lfs f3, float_5_80419c30(r2)
		opword 0xEC42002A
		lfs f0, float_0p5_80419ba0(r2)
		opword 0xEC43102A
		opword 0xEFC20032
		opword 0xFC01F040
		opword 0x4081000C
		opword 0x38600000
		opword 0x48000480
		opword 0xC01D0098
		opword 0x3861000C
		opword 0x389D008C
		opword 0xD01D008C
		opword 0xC01D00A0
		opword 0xD01D0094
		bl PSVECDistance
		fmr f29, f1
		opword 0xFC1DF040
		opword 0x4081000C
		opword 0x38600000
		opword 0x48000450
		opword 0x93BF01D8
		opword 0xC03F008C
		opword 0xC05F0094
		opword 0xC07D008C
		opword 0xC09D0094
		bl angleABf
		opword 0xFFE00890
		opword 0xC05F01A0
		bl compAngle
		opword 0xFC200A10
		lfs f0, float_40_80419c34(r2)
		opword 0xFC010040
		opword 0x40800164
		lfs f2, float_6p2832_80419c38(r2)
		opword 0xC03F01A0
		lfs f0, float_360_80419be0(r2)
		opword 0xEC420072
		lfs f1, float_3p1416_80419c44(r2)
		lfs f4, float_0p00761_80419c3c(r2)
		lfs f3, float_0p16605_80419c40(r2)
		opword 0xECC20024
		lfs f2, float_1_80419bb4(r2)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820044
		lfs f1, float_1p5708_80419c48(r2)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC0601B2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC8401B2
		opword 0x48000068
		opword 0xEC060828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0x4800004C
		lfs f0, float_4p7124_80419c4c(r2)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC260828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000024
		opword 0xEC060028
		lfs f1, float_1p5708_80419c48(r2)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		lfs f2, float_3p1416_80419c44(r2)
		opword 0xECFEE828
		opword 0xFC002050
		lfs f5, float_0p03705_80419c50(r2)
		opword 0xFC061040
		lfs f4, float_0p4967_80419c54(r2)
		lfs f3, float_1_80419bb4(r2)
		opword 0xEC070032
		opword 0x4C401382
		opword 0x40820040
		lfs f2, float_1p5708_80419c48(r2)
		opword 0xFC061040
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC2601B2
		opword 0xECA52078
		opword 0xECA5187A
		opword 0x4800005C
		opword 0xEC261028
		opword 0xEC220828
		opword 0xEC210072
		opword 0xECA52078
		opword 0xECA5187A
		opword 0xFCA02850
		opword 0x48000040
		lfs f1, float_4p7124_80419c4c(r2)
		opword 0xFC060840
		opword 0x4080001C
		opword 0xEC261028
		opword 0xEC210072
		opword 0xECA52078
		opword 0xECA5187A
		opword 0xFCA02850
		opword 0x4800001C
		opword 0xEC260828
		lfs f2, float_1p5708_80419c48(r2)
		opword 0xEC220828
		opword 0xEC210072
		opword 0xECA52078
		opword 0xECA5187A
		opword 0xEC870172
		opword 0x4800016C
		lfs f1, float_6p2832_80419c38(r2)
		lfs f0, float_360_80419be0(r2)
		opword 0xEC4107F2
		lfs f1, float_3p1416_80419c44(r2)
		lfs f4, float_0p00761_80419c3c(r2)
		lfs f3, float_0p16605_80419c40(r2)
		opword 0xECC20024
		lfs f2, float_1_80419bb4(r2)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820044
		lfs f1, float_1p5708_80419c48(r2)
		opword 0xFC060840
		opword 0x4C401382
		opword 0x40820018
		opword 0xEC0601B2
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC8401B2
		opword 0x48000068
		opword 0xEC060828
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0x4800004C
		lfs f0, float_4p7124_80419c4c(r2)
		opword 0xFC060040
		opword 0x40800020
		opword 0xEC260828
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0x48000024
		opword 0xEC060028
		lfs f1, float_1p5708_80419c48(r2)
		opword 0xEC210028
		opword 0xEC010072
		opword 0xEC841838
		opword 0xEC84103A
		opword 0xEC840072
		opword 0xFC802050
		opword 0xC01D008C
		lfs f2, float_3p1416_80419c44(r2)
		opword 0xEC3E013C
		opword 0xC01F008C
		opword 0xFC061040
		lfs f5, float_0p03705_80419c50(r2)
		lfs f4, float_0p4967_80419c54(r2)
		opword 0xEC010028
		lfs f3, float_1_80419bb4(r2)
		opword 0x4C401382
		opword 0x40820040
		lfs f2, float_1p5708_80419c48(r2)
		opword 0xFC061040
		opword 0x4C401382
		opword 0x40820014
		opword 0xEC2601B2
		opword 0xECA52078
		opword 0xECA5187A
		opword 0x4800005C
		opword 0xEC261028
		opword 0xEC220828
		opword 0xEC210072
		opword 0xECA52078
		opword 0xECA5187A
		opword 0xFCA02850
		opword 0x48000040
		lfs f1, float_4p7124_80419c4c(r2)
		opword 0xFC060840
		opword 0x4080001C
		opword 0xEC261028
		opword 0xEC210072
		opword 0xECA52078
		opword 0xECA5187A
		opword 0xFCA02850
		opword 0x4800001C
		opword 0xEC260828
		lfs f2, float_1p5708_80419c48(r2)
		opword 0xEC220828
		opword 0xEC210072
		opword 0xECA52078
		opword 0xECA5187A
		opword 0xC05D0094
		opword 0xC03F0094
		opword 0xEC5E117A
		opword 0xEC820828
		opword 0xEC440132
		lfs f1, float_0_80419b9c(r2)
		opword 0xECC0103A
		opword 0xFC060840
		opword 0x4081004C
		opword 0xFC403034
		opword 0xC8BE01C0
		opword 0xC87E01C8
		opword 0xFC2200B2
		opword 0xFC4500B2
		opword 0xFC26187C
		opword 0xFC420072
		opword 0xFC2200B2
		opword 0xFC4500B2
		opword 0xFC26187C
		opword 0xFC420072
		opword 0xFC2200B2
		opword 0xFC4500B2
		opword 0xFC26187C
		opword 0xFC220072
		opword 0xFCC60072
		opword 0xFCC03018
		opword 0x48000088
		opword 0xC83E01D0
		opword 0xFC060840
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f6, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0C10008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f6, __float_nan@l(r3)
		opword 0xC05F01BC
		lfs f1, float_4_80419c58(r2)
		opword 0xFC020840
		opword 0x4081000C
		lfs f1, float_3_80419c08(r2)
		opword 0x48000008
		lfs f1, float_1p5_80419bcc(r2)
		opword 0xFC060840
		opword 0x40810014
		lfs f1, float_2_80419c5c(r2)
		opword 0xEC213024
		opword 0xEC000072
		opword 0xEC840072
		opword 0xC03F008C
		opword 0x387F008C
		lfs f2, float_160_80419c60(r2)
		opword 0x38800000
		opword 0xEC01002A
		lfs f1, float_0_80419b9c(r2)
		opword 0xEC42F82A
		lfs f3, float_20_80419c00(r2)
		opword 0xD01F008C
		opword 0xC01F0094
		opword 0xEC00202A
		opword 0xD01F0094
		opword 0xC09F01B8
		bl marioChkWallAround
		opword 0x38600001
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    if (*(s8*)name == 0) {
        return;
    }
    if (!strcmp(name, (char*)str_802C31C0)) {
        return;
    }
    if (!strcmp(name, "party")) {
        party = partyGetPtr(marioGetPartyId());
        if (party) {
            partyChgPoseId(party, 1);
        }
    } else if (!strcmp(name, (char*)str_802C31CC)) {
        party = partyGetPtr(marioGetExtraPartyId());
        if (party) {
            partyChgPoseId(party, 1);
        }
    } else if (!strcmp(name, "mario")) {
        marioChgPose(MarioStayPose);
    } else {
        npc = npcNameToPtr(name);
        if (npc->flags & 0x200) {
            animPoseSetAnim(npc->poseId, npc->stayAnim, TRUE);
        }
    }
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void npcMoveG(NpcEntry* npc) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x90010044
		opword 0xDBE10030
		opword 0xF3E10038
		opword 0x93E1002C
		lfs f0, float_0_80419b9c(r2)
		opword 0x7C7F1B78
		opword 0xC3E301B8
		opword 0xD00301B8
		opword 0x806301D4
		opword 0x546402D7
		opword 0x41820014
		opword 0x546000C7
		opword 0x4082000C
		lfs f0, float_0p5_80419ba0(r2)
		opword 0xEFFF0032
		opword 0x80BF0000
		lfs f3, float_0_80419b9c(r2)
		opword 0x54A0039D
		opword 0x418200BC
		opword 0xC09F0180
		opword 0x28040000
		opword 0xC0BF01A4
		opword 0xEC042828
		opword 0x4182000C
		opword 0x546000C7
		opword 0x41820028
		opword 0xEC000032
		lfs f2, float_neg980_80419c24(r2)
		opword 0xC03F01CC
		opword 0xC07F01C4
		opword 0xEC220072
		opword 0xEC040138
		opword 0xEC010032
		opword 0xEC63017A
		opword 0x48000034
		lfs f2, float_neg980_80419c24(r2)
		opword 0xEC000032
		opword 0xC03F01CC
		opword 0xC07F01C4
		opword 0xEC220072
		lfs f2, float_0p15_80419c28(r2)
		opword 0xEC040138
		lfs f4, float_0p4_80419c1c(r2)
		opword 0xEC630172
		opword 0xEC220072
		opword 0xEC010032
		opword 0xEC6400FA
		opword 0xC03F01C8
		opword 0xC05F01D0
		lfs f0, float_0_80419b9c(r2)
		opword 0xEC630072
		opword 0xFC020040
		opword 0x40810034
		opword 0x28040000
		opword 0x41820018
		opword 0xFC001050
		lfs f1, float_0p5_80419ba0(r2)
		opword 0xEC000172
		opword 0xEC010032
		opword 0x4800000C
		opword 0xFC001050
		opword 0xEC000172
		opword 0xFC030040
		opword 0x40800008
		opword 0xFC600090
		opword 0x54A006F7
		opword 0xEFFF182A
		opword 0x40820028
		opword 0xC03F0090
		lfs f0, float_neg1000_80419c2c(r2)
		opword 0xEC21F82A
		opword 0xD03F0090
		opword 0xC03F0090
		opword 0xFC010040
		opword 0x408000DC
		opword 0xD01F0090
		opword 0x480000D4
		lfs f4, float_0_80419b9c(r2)
		opword 0xFC04F800
		opword 0x418200C8
		opword 0xFC1F2040
		opword 0x40810020
		opword 0x801F01D4
		opword 0x60000001
		opword 0x901F01D4
		opword 0xC01F0090
		opword 0xEC00F82A
		opword 0xD01F0090
		opword 0x480000A4
		opword 0xFC40FA10
		lfs f1, float_0p8_80419bb0(r2)
		opword 0xC01F0150
		opword 0xFCC02090
		lfs f5, float_neg1_80419bf8(r2)
		opword 0x38810020
		opword 0xEC610032
		opword 0x38A1001C
		opword 0xFC001018
		opword 0x38C10018
		opword 0x38E10014
		opword 0x39010010
		opword 0xEC03002A
		opword 0x3921000C
		opword 0x39410008
		opword 0x38600000
		opword 0xD0010014
		opword 0xC01F0090
		opword 0xC03F008C
		opword 0xEC40182A
		opword 0xC07F0094
		bl hitCheckFilter
		opword 0x28030000
		opword 0x907F0300
		opword 0x40820020
		opword 0x801F01D4
		opword 0x60000001
		opword 0x901F01D4
		opword 0xC01F0090
		opword 0xEC00F82A
		opword 0xD01F0090
		opword 0x48000024
		opword 0x807F01D4
		opword 0x38000000
		opword 0x5463003C
		opword 0x907F01D4
		opword 0xC001001C
		opword 0xD01F0090
		opword 0x901F017C
		opword 0x901F0178
		opword 0xE3E10038
		opword 0x80010044
		opword 0xCBE10030
		opword 0x83E1002C
		opword 0x7C0803A6
		opword 0x38210040
	}
#endif
}
#ifdef NONMATCHING

BOOL npcCheckHitMarioSide(NpcEntry* npc) {
    MarioWork* mario; float new_var ; // FAKE: temp needed for 100% (99.97 without)
    Vec marioPos;
    f32 dist;
    f32 range;
    f32 angle;
    f32 dx; f32 dz;
    f32 rad;
    f32 len;
    f32 scale;

    mario = marioGetPtr();
    if (npc->position.y > ( mario->position.y + mario->wPlayerCollisionBox.y) ) {
        dz = mario->wPlayerCollisionBox.y;
        return FALSE;
    }
    if (mario->position.y > ( npc->position.y + npc->height) ) {
        return FALSE;
    }
    marioPos.x = mario->position.x;
    marioPos.z = mario->position.z;
    marioPos.y = npc->position.y;
    dist = PSVECDistance(&marioPos, &npc->position);
    new_var = 5.0f + (mario->wPlayerCollisionBox.x + npc->width); range = new_var ;
    range *= 0.5f;
    if (dist > range) {
        return FALSE;
    }
    npc->position.x = npc->prevPosition.x;
    npc->position.z = npc->prevPosition.z;
    dist = PSVECDistance(&marioPos, &npc->position);
    if (dist > range) {
        return FALSE;
    }
    mario->targetNpc = (s32)npc;
    angle = angleABf(mario->position.x, mario->position.z, npc->position.x, npc->position.z);
    if (__fabsf(compAngle(angle, mario->directionView)) < 40.0f) {
        dx = (range - dist) * ( -npc_sin((6.2831855f * mario->directionView) / 360.0f) );
        dz = (range - dist) * npc_cos((6.2831855f * mario->directionView) / 360.0f);

    } else {
        rad = (6.2831855f * angle) / 360.0f;
        dx = (npc->position.x - ( range * npc_sin(rad) )) - mario->position.x;
        dz = (npc->position.z + ( range * npc_cos(rad) )) - mario->position.z;
    }
    len = npc_sqrtf(( dx * dx ) + ( dz * dz) );
    if (len > ( (mario->wPlayerCollisionBox.z > 4.0f ) ? ( 3.0f ) : ( 1.5f))) { if (1 ) {
        scale = 2.0f / len;
        dx *= scale;
        dz *= scale;
    }
    }
    mario->position.x += dx;
    mario->position.z += dz;
    dz = mario->wPlayerCollisionBox.y;
    marioChkWallAround(&mario->position, 0, 0.0f, 160.0f + angle, 20.0f, dz);
    return TRUE;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

void npcMoveG(NpcEntry* npc) {
    f32 dy;
    f32 vel;
    f32 t;
    f32 dt;
    f32 tp;
    f32 limit;
    f32 hitX, hitY, hitZ, dist, hitNX, hitNY, hitNZ;
    f32 h;

    dy = npc->moveOffset.y;
    npc->moveOffset.y = 0.0f;
    if (npc->jumpFlags & 0x100000 && !(npc->jumpFlags & 0x10000000)) {
        dy *= 0.5f;
    }
    vel = 0.0f;
    if (npc->flags & 0x20000) {
        t = npc->field_180;
        dt = npc->moveDt;
        tp = t - dt;
        if (!(npc->jumpFlags & 0x100000) || npc->jumpFlags & 0x10000000) {
            vel = npc->jumpVelY * dt + (-980.0f * npc->jumpGravity) * (t * t - tp * tp);
        } else {
            vel = 0.4f * (npc->jumpVelY * dt) + (0.15f * (-980.0f * npc->jumpGravity)) * (t * t - tp * tp);
        }
        vel *= npc->jumpYScale;
        if (npc->field_1D0 > 0.0f) {
            if (npc->jumpFlags & 0x100000) {
                limit = 0.5f * (-npc->field_1D0 * dt);
            } else {
                limit = -npc->field_1D0 * dt;
            }
            if (vel < limit) {
                vel = limit;
            }
        }
    }
    dy += vel;
    if (!(npc->flags & 0x10)) {
        npc->position.y += dy;
        if (npc->position.y < -1000.0f) {
            npc->position.y = -1000.0f;
        }
    } else if (dy != 0.0f) {
        if (dy > 0.0f) {
            npc->jumpFlags |= 1;
            npc->position.y += dy;
        } else {
            f64 ad = __fabs(dy);
            f32 hh = 0.8f * npc->height;
            dist = hh + (f32)ad;
            if ((npc->field_0x300 = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &dist, &hitNX, &hitNY, &hitNZ,
                                              npc->position.x, npc->position.y + hh, npc->position.z, 0.0f,
                                              -1.0f, 0.0f)) == NULL) {
                npc->jumpFlags |= 1;
                npc->position.y += dy;
            } else {
                npc->jumpFlags &= ~1;
                npc->position.y = hitY;
                npc->field_178 = 0;
            }
        }
    }
}
#endif
#ifndef NONMATCHING
#pragma pop
#endif

void npcTuningRy(NpcEntry* npc, f32 angle) {
    npc->direction = reviseAngle(angle);
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
f32 npcTransRytoFaceDir(NpcEntry* npc) {
#ifdef NONMATCHING
    if (reviseAngle(npc->direction) < 180.0f) {
        return 90.0f;
    }
    return 270.0f;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0xC0230144
		bl reviseAngle
		lfs f0, float_180_80419bec(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f1, float_90_80419bd0(r2)
		opword 0x48000008
		lfs f1, float_270_80419be4(r2)
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
static inline void npcSideSlide(f32* outX, f32* outZ, f32 dx, f32 dz, f32 nx, f32 nz) {
    f32 d = dx * nx + dz * nz;
    f32 ax = 0.5f * (dx - d * nx);
    f32 az = 0.5f * (dz - d * nz);
    *outX += ax;
    *outZ += az;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz) {
	char _af_pad[72];
	asm volatile {
		mr r26, r3
		lis r3, vec3_802c2f78@ha
		opword 0xC07A008C
		opword 0x7C9B2378
		fmr f29, f1
		lfs f0, float_0_80419b9c(r2)
		opword 0xD0640000
		opword 0x7CBC2B78
		opword 0xFFC01090
		opword 0x7CDD3378
		opword 0xC03A0094
		opword 0xFC00E800
		addi r31, r3, vec3_802c2f78@l
		opword 0xD0250000
		opword 0x40820014
		opword 0xFC00F000
		opword 0x4082000C
		opword 0x38600000
		opword 0x4800087C
		lfs f1, float_0_80419b9c(r2)
		opword 0xFC60E890
		opword 0xFC80F090
		opword 0xFC400890
		bl angleABf
		la r3, _af_pad+20
		opword 0x38810018
		bl sincosf
		opword 0xEC3E07B2
		lfs f0, float_0_80419b9c(r2)
		opword 0xEFFD0F7A
		opword 0xFC1F0040
		opword 0x4081004C
		opword 0xFC20F834
		opword 0xC87F01C0
		opword 0xC85F01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC010032
		opword 0xFC7F0032
		opword 0xFC601818
		opword 0x48000090
		opword 0xC81F01D0
		opword 0xFC1F0040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000078
		opword 0xD3E10014
		opword 0x3C007F80
		opword 0x80810014
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x40820010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000008
		opword 0xFC60F890
		lfs f1, float_0p75_80419bf4(r2)
		opword 0xC01A014C
		lfs f2, float_0p2_80419c14(r2)
		opword 0xEC21183A
		lfs f0, float_10_80419bb8(r2)
		opword 0xD021002C
		opword 0xC03A0150
		opword 0xEC420072
		opword 0xFC020040
		opword 0x40810008
		opword 0xFC400090
		opword 0x801A0000
		opword 0x540004A5
		opword 0x41820048
		opword 0xC01A0090
		opword 0x38810038
		opword 0xC03A008C
		opword 0x38A10034
		opword 0xEC40102A
		opword 0xC07A0094
		opword 0xC081001C
		opword 0x38C10030
		lfs f5, float_0_80419b9c(r2)
		opword 0x38E1002C
		opword 0xC0C10018
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600004
		bl hitCheckAttr
		opword 0x48000044
		opword 0xC01A0090
		opword 0x38810038
		opword 0xC03A008C
		opword 0x38A10034
		opword 0xEC40102A
		opword 0xC07A0094
		opword 0xC081001C
		opword 0x38C10030
		lfs f5, float_0_80419b9c(r2)
		opword 0x38E1002C
		opword 0xC0C10018
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x7C7E1B78
		opword 0x418200CC
		opword 0xC0810020
		opword 0xC0210028
		opword 0xEC1E0132
		lfs f2, float_0p5_80419ba0(r2)
		opword 0xC07B0000
		opword 0xEC1D007A
		opword 0xEC20E87C
		opword 0xEC00F13C
		opword 0xEC220072
		opword 0xEC020032
		opword 0xEC23082A
		opword 0xD03B0000
		opword 0xC03C0000
		opword 0xEC01002A
		opword 0xD01C0000
		opword 0x801A0000
		opword 0x540003DF
		opword 0x4182007C
		lfs f1, float_180_80419bec(r2)
		opword 0xC01D0000
		opword 0xEC21002A
		bl reviseAngle
		opword 0xFFC00890
		lfs f1, float_0_80419b9c(r2)
		lfs f4, float_100_80419c18(r2)
		opword 0xC0610028
		opword 0xFC400890
		opword 0xC0010020
		opword 0xEC6400F2
		opword 0xEC840032
		bl angleABf
		bl reviseAngle
		opword 0xFFA00890
		opword 0xEC3DF028
		bl reviseAngle
		opword 0xEC3D082A
		bl reviseAngle
		opword 0xFC00081E
		opword 0x3C004330
		opword 0x90010048
		opword 0xC83F01D8
		opword 0xD8010040
		opword 0x80010044
		opword 0x6C008000
		opword 0x9001004C
		opword 0xC8010048
		opword 0xEC000828
		opword 0xD01D0000
		opword 0x7FC3F378
		opword 0x480005E4
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC1F0040
		opword 0x4081004C
		opword 0xFC20F834
		opword 0xC87F01C0
		opword 0xC85F01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC010032
		opword 0xFC7F0032
		opword 0xFC601818
		opword 0x48000090
		opword 0xC81F01D0
		opword 0xFC1F0040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000078
		opword 0xD3E10010
		opword 0x3C007F80
		opword 0x80810010
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x40820010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000008
		opword 0xFC60F890
		lfs f2, float_0p75_80419bf4(r2)
		opword 0xC01A014C
		lfs f1, float_0p4_80419c1c(r2)
		opword 0xEC02183A
		opword 0xD001002C
		opword 0x801A0000
		opword 0xC01A0150
		opword 0x540004A5
		opword 0xEC410032
		opword 0x41820048
		opword 0xC01A0090
		opword 0x38810038
		opword 0xC03A008C
		opword 0x38A10034
		opword 0xEC40102A
		opword 0xC07A0094
		opword 0xC081001C
		opword 0x38C10030
		lfs f5, float_0_80419b9c(r2)
		opword 0x38E1002C
		opword 0xC0C10018
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600004
		bl hitCheckAttr
		opword 0x48000044
		opword 0xC01A0090
		opword 0x38810038
		opword 0xC03A008C
		opword 0x38A10034
		opword 0xEC40102A
		opword 0xC07A0094
		opword 0xC081001C
		opword 0x38C10030
		lfs f5, float_0_80419b9c(r2)
		opword 0x38E1002C
		opword 0xC0C10018
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x7C7E1B78
		opword 0x418201DC
		opword 0xC0010028
		opword 0xC0210020
		opword 0xEC400032
		lfs f0, float_0_80419b9c(r2)
		opword 0xEC210072
		opword 0xEC62082A
		opword 0xFC030040
		opword 0x4081004C
		opword 0xFC201834
		opword 0xC89F01C0
		opword 0xC85F01C8
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC240072
		opword 0xFC03103C
		opword 0xFC010032
		opword 0xFC630032
		opword 0xFC601818
		opword 0x48000088
		opword 0xC81F01D0
		opword 0xFC030040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD061000C
		opword 0x3C007F80
		opword 0x8081000C
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f3, __float_nan@l(r3)
		lfs f1, float_0_80419b9c(r2)
		opword 0xC0010024
		opword 0xFC400890
		opword 0xFC800050
		bl angleABf
		lfs f0, float_45_80419c20(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x408200CC
		opword 0xC0810020
		opword 0xC0210028
		opword 0xEC1E0132
		lfs f2, float_0p5_80419ba0(r2)
		opword 0xC07B0000
		opword 0xEC1D007A
		opword 0xEC20E87C
		opword 0xEC00F13C
		opword 0xEC220072
		opword 0xEC020032
		opword 0xEC23082A
		opword 0xD03B0000
		opword 0xC03C0000
		opword 0xEC01002A
		opword 0xD01C0000
		opword 0x801A0000
		opword 0x540003DF
		opword 0x4182007C
		lfs f1, float_180_80419bec(r2)
		opword 0xC01D0000
		opword 0xEC21002A
		bl reviseAngle
		opword 0xFFC00890
		lfs f1, float_0_80419b9c(r2)
		lfs f4, float_100_80419c18(r2)
		opword 0xC0610028
		opword 0xFC400890
		opword 0xC0010020
		opword 0xEC6400F2
		opword 0xEC840032
		bl angleABf
		bl reviseAngle
		opword 0xFFA00890
		opword 0xEC3DF028
		bl reviseAngle
		opword 0xEC3D082A
		bl reviseAngle
		opword 0xFC00081E
		opword 0x3C004330
		opword 0x90010040
		opword 0xC83F01D8
		opword 0xD8010048
		opword 0x8001004C
		opword 0x6C008000
		opword 0x90010044
		opword 0xC8010040
		opword 0xEC000828
		opword 0xD01D0000
		opword 0x7FC3F378
		opword 0x48000274
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC1F0040
		opword 0x4081004C
		opword 0xFC20F834
		opword 0xC87F01C0
		opword 0xC85F01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC1F103C
		opword 0xFC010032
		opword 0xFFFF0032
		opword 0xFFE0F818
		opword 0x48000088
		opword 0xC81F01D0
		opword 0xFC1F0040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f31, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD3E10008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f31, __float_nan@l(r3)
		lfs f1, float_0p75_80419bf4(r2)
		opword 0xC01A014C
		opword 0xEC01F83A
		opword 0xD001002C
		opword 0x801A0000
		opword 0xC01A0150
		opword 0x540004A5
		opword 0xEC410032
		opword 0x41820048
		opword 0xC01A0090
		opword 0x38810038
		opword 0xC03A008C
		opword 0x38A10034
		opword 0xEC40102A
		opword 0xC07A0094
		opword 0xC081001C
		opword 0x38C10030
		lfs f5, float_0_80419b9c(r2)
		opword 0x38E1002C
		opword 0xC0C10018
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600004
		bl hitCheckAttr
		opword 0x48000044
		opword 0xC01A0090
		opword 0x38810038
		opword 0xC03A008C
		opword 0x38A10034
		opword 0xEC40102A
		opword 0xC07A0094
		opword 0xC081001C
		opword 0x38C10030
		lfs f5, float_0_80419b9c(r2)
		opword 0x38E1002C
		opword 0xC0C10018
		opword 0x39010028
		opword 0x39210024
		opword 0x39410020
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x7C7E1B78
		opword 0x418200CC
		opword 0xC0810020
		opword 0xC0210028
		opword 0xEC1E0132
		lfs f2, float_0p5_80419ba0(r2)
		opword 0xC07B0000
		opword 0xEC1D007A
		opword 0xEC20E87C
		opword 0xEC00F13C
		opword 0xEC220072
		opword 0xEC020032
		opword 0xEC23082A
		opword 0xD03B0000
		opword 0xC03C0000
		opword 0xEC01002A
		opword 0xD01C0000
		opword 0x801A0000
		opword 0x540003DF
		opword 0x4182007C
		lfs f1, float_180_80419bec(r2)
		opword 0xC01D0000
		opword 0xEC21002A
		bl reviseAngle
		opword 0xFFC00890
		lfs f1, float_0_80419b9c(r2)
		lfs f4, float_100_80419c18(r2)
		opword 0xC0610028
		opword 0xFC400890
		opword 0xC0010020
		opword 0xEC6400F2
		opword 0xEC840032
		bl angleABf
		bl reviseAngle
		opword 0xFFA00890
		opword 0xEC3DF028
		bl reviseAngle
		opword 0xEC3D082A
		bl reviseAngle
		opword 0xFC00081E
		opword 0x3C004330
		opword 0x90010040
		opword 0xC83F01D8
		opword 0xD8010048
		opword 0x8001004C
		opword 0x6C008000
		opword 0x90010044
		opword 0xC8010040
		opword 0xEC000828
		opword 0xD01D0000
		opword 0x7FC3F378
		opword 0x48000020
		opword 0xC01B0000
		opword 0x38600000
		opword 0xEC00E82A
		opword 0xD01B0000
		opword 0xC01C0000
		opword 0xEC00F02A
		opword 0xD01C0000
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz) {
    f32 hx, hy, hz, dist, nx, ny, nz;
    f32 lenSq, d, height;
    HitEntry* hit;
    f32 s, c;

    *outX = npc->position.x;
    *outZ = npc->position.z;
    if (dx == 0.0f && dz == 0.0f) {
        return NULL;
    }
    sincosf(&s, &c, angleABf(0.0f, 0.0f, dx, dz));

    dist = npc_sqrtf(dx * dx + dz * dz) + 0.75f * npc->width;
    height = 0.2f * npc->height;
    if (height > 10.0f) {
        height = 10.0f;
    }
    if (npc->flags & 0x2000) {
        hit = hitCheckAttr(4, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    } else {
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    }
    if (hit) {
        npcSideSlide(outX, outZ, dx, dz, nx, nz);
        if (npc->flags & 0x10000) {
            f32 a = reviseAngle(180.0f + *angle);
            f32 b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * nx, 100.0f * nz));
            *angle = (s32)reviseAngle(b + reviseAngle(b - a));
        }
        return hit;
    }

    dist = npc_sqrtf(dx * dx + dz * dz) + 0.75f * npc->width;
    height = 0.4f * npc->height;
    if (npc->flags & 0x2000) {
        hit = hitCheckAttr(4, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    } else {
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    }
    if (hit && angleABf(0.0f, 0.0f, npc_sqrtf(nx * nx + nz * nz), -ny) >= 45.0f) {
        npcSideSlide(outX, outZ, dx, dz, nx, nz);
        if (npc->flags & 0x10000) {
            f32 a = reviseAngle(180.0f + *angle);
            f32 b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * nx, 100.0f * nz));
            *angle = (s32)reviseAngle(b + reviseAngle(b - a));
        }
        return hit;
    }

    dist = npc_sqrtf(dx * dx + dz * dz) + 0.75f * npc->width;
    height = 0.75f * npc->height;
    if (npc->flags & 0x2000) {
        hit = hitCheckAttr(4, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    } else {
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    }
    if (hit) {
        npcSideSlide(outX, outZ, dx, dz, nx, nz);
        if (npc->flags & 0x10000) {
            f32 a = reviseAngle(180.0f + *angle);
            f32 b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * nx, 100.0f * nz));
            *angle = (s32)reviseAngle(b + reviseAngle(b - a));
        }
        return hit;
    }
    *outX += dx;
    *outZ += dz;
    return NULL;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
NpcEntry* npcNearDistCheck(f32 x, f32 y, f32 z, f32 range) {
	asm volatile {
		opword 0x9421FFF0
		lis r4, vec3_802c2f78@ha
		addi r5, r4, vec3_802c2f78@l
		lwz r3, gp(r13)
		la r4, work(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820008
		opword 0x38840014
		opword 0x80040004
		opword 0x38600000
		opword 0x80E4000C
		opword 0x7C0903A6
		opword 0x2C000000
		opword 0x40810130
		opword 0x80070000
		opword 0x540007FF
		opword 0x4182011C
		opword 0xC0A7008C
		opword 0xC0070094
		opword 0xECC12828
		opword 0xC0A70090
		opword 0xECE30028
		lfs f0, float_0_80419b9c(r2)
		opword 0xED622828
		opword 0xED2601B2
		opword 0xED4701F2
		opword 0xED09502A
		opword 0xFC080040
		opword 0x4081004C
		opword 0xFCA04034
		opword 0xC8E501C0
		opword 0xC8C501C8
		opword 0xFC050172
		opword 0xFCA70172
		opword 0xFC08303C
		opword 0xFCA50032
		opword 0xFC050172
		opword 0xFCA70172
		opword 0xFC08303C
		opword 0xFCA50032
		opword 0xFC050172
		opword 0xFCA70172
		opword 0xFC08303C
		opword 0xFC050032
		opword 0xFD080032
		opword 0xFD004018
		opword 0x48000088
		opword 0xC80501D0
		opword 0xFC080040
		opword 0x40800010
		lis r4, __float_nan@ha
		lfs f8, __float_nan@l(r4)
		opword 0x48000070
		opword 0xD1010008
		opword 0x3C007F80
		opword 0x80C10008
		opword 0x54C40050
		opword 0x7C040000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C040000
		opword 0x41820020
		opword 0x48000034
		opword 0x54C0027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x54C0027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r4, __float_nan@ha
		lfs f8, __float_nan@l(r4)
		opword 0xECAB4AFA
		lfs f0, float_0_80419b9c(r2)
		opword 0xECAA282A
		opword 0xFC050040
		opword 0xFC082040
		opword 0x40800008
		opword 0x7CE33B78
		opword 0x38E70340
		opword 0x4200FED8
		opword 0x38210010
	}
#endif
}
#ifdef NONMATCHING

NpcEntry* npcNearDistCheck(f32 x, f32 y, f32 z, f32 range) {
    NpcWork* wp;
    NpcEntry* entry;
    NpcEntry* found;
    s32 i;
    f32 dx, dy, dz;
    f32 dist;
    s32 total;

    wp = npcGetWorkPtrInline();
    found = NULL;
    entry = wp->entries;
    total = wp->total;
    for (i = 0; i < total; i++, entry++) {
        if (entry->flags & 1) {
            dx = x - entry->position.x;
            dz = z - entry->position.z;
            dy = y - entry->position.y;
            dist = npc_sqrtf(dx * dx + dz * dz);
            npc_sqrtf(dx * dx + dy * dy + dz * dz);
            if (dist < range) {
                found = entry;
            }
        }
    }
    return found;
}
#endif
#ifndef NONMATCHING
#pragma pop
#endif

FieldBattleData* fbatGetPointer(void) {
    return gp->fbatData;
}

void fbatChangeMode(s16 mode) {
    gp->fbatData->mode = mode;
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void fbatSetAttackAnnounce(s32 a1) {
#ifdef NONMATCHING
    FirstStrikeInfo* firstStrike = &gp->fbatData->firstStrike;

    firstStrike->enabled = FALSE;
    firstStrike->field_0x4 = a1;
    firstStrike->field_0xC = 0;
    switch (firstStrike->field_0x4) {
        case 0x20000:
        case 0x40000:
        case 0x80000:
        case 0x100000:
        case 0x200000:
        case 0x400000:
        case 0x800000:
        case 0x1000000:
            firstStrike->msg_tag = (char*)str_802C3158; // You struck first!
            firstStrike->type = 2;
            firstStrike->color = (GXColor){ 0xFF, 0x80, 0x80, 0xFF };
            break;
        case 0x10000000:
            firstStrike->msg_tag = (char*)str_802C3168; // Your foe struck first!
            firstStrike->type = 1;
            firstStrike->color = (GXColor){ 0x80, 0x80, 0xFF, 0xFF };
            break;
        default:
            firstStrike->type = 0;
            break;
    }
#endif
#ifndef NONMATCHING
	asm volatile {
		lwz r5, gp(r13)
		opword 0x38800000
		opword 0x3C000020
		opword 0x80A50168
		opword 0x90850550
		opword 0x90650554
		opword 0x9085055C
		opword 0x80650554
		opword 0x7C030000
		opword 0x41820088
		opword 0x40800044
		opword 0x3C000008
		opword 0x7C030000
		opword 0x41820078
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C030000
		opword 0x41820068
		opword 0x408000A4
		opword 0x3C000002
		opword 0x7C030000
		opword 0x41820058
		opword 0x48000094
		opword 0x3C000010
		opword 0x7C030000
		opword 0x41820048
		opword 0x48000084
		opword 0x3C000100
		opword 0x7C030000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C030000
		opword 0x41820028
		opword 0x40800064
		opword 0x3C000040
		opword 0x7C030000
		opword 0x41820018
		opword 0x48000054
		opword 0x3C001000
		opword 0x7C030000
		opword 0x41820028
		opword 0x48000044
		lis r3, str_802C3158@ha
		opword 0x38000002
		addi r3, r3, str_802C3158@l
		opword 0x90650568
		opword 0x90050558
		lwz r0, dat_80419b90(r2)
		opword 0x9005056C
		opword 0x4E800020
		lis r3, str_802C3168@ha
		opword 0x38000001
		addi r3, r3, str_802C3168@l
		opword 0x90650568
		opword 0x90050558
		lwz r0, dat_80419b94(r2)
		opword 0x9005056C
		opword 0x4E800020
		opword 0x38000000
		opword 0x90050558
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void fbatSetAttackAnnounceEnable(void) {
    gp->fbatData->firstStrike.enabled = TRUE;
}

#ifdef NONMATCHING
static inline f32 mulf(f32 a, f32 b) { return a * b; }
void npcStrippedAnnouncePool(f32* f) {
    f[0] = -600.0f;
    f[1] = 600.0f;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param) {
	asm volatile {
		opword 0x9421FF90
		opword 0x7C0802A6
		opword 0x90010074
		opword 0xDBE10060
		opword 0xF3E10068
		opword 0xDBC10050
		opword 0xF3C10058
		opword 0xDBA10040
		opword 0xF3A10048
		opword 0xDB810030
		opword 0xF3810038
		opword 0x93E1002C
		opword 0x93C10028
		opword 0x7C9E2378
		opword 0x80640018
		bl msgSearch
		opword 0xC3FE0010
		opword 0x7C7F1B78
		opword 0xC3DE0014
		bl FontGetMessageWidth
		opword 0x5464043E
		opword 0x3C004330
		lis r3, double_to_int_mask_802c31b8@ha
		opword 0x90810014
		addi r4, r3, double_to_int_mask_802c31b8@l
		opword 0x38602710
		opword 0x90010010
		opword 0xC8240000
		opword 0xC8010010
		opword 0xEF800828
		bl irand
		opword 0x3C806666
		opword 0x3C004330
		opword 0x38A46667
		opword 0x90010018
		opword 0x7CA51896
		lis r4, double_to_int_802c3150@ha
		lfd f1, double_to_int_802c3150@l(r4)
		opword 0x7CA00E70
		opword 0x54040FFE
		opword 0x7C002214
		opword 0x1C000005
		opword 0x7C001850
		opword 0x38602710
		opword 0x6C008000
		opword 0x9001001C
		opword 0xC8010018
		opword 0xEC000828
		opword 0xEFBF002A
		bl irand
		opword 0x3CA06666
		opword 0x3C804330
		opword 0x38056667
		lfs f2, float_10_80419bb8(r2)
		opword 0x7C001896
		lfs f0, float_20_80419c00(r2)
		lis r5, double_to_int_802c3150@ha
		lfs f1, float_0p5_80419ba0(r2)
		opword 0xEC5D1028
		opword 0x90810020
		opword 0x7C060E70
		opword 0xEFBC0072
		opword 0x54C70FFE
		opword 0x801E001C
		opword 0x7CC63A14
		opword 0xEC00E02A
		opword 0x1C860005
		opword 0xEC22E828
		lfs f2, float_0p1_80419bfc(r2)
		lfd f5, double_to_int_802c3150@l(r5)
		opword 0x7C641850
		opword 0xEC6000B2
		opword 0x6C638000
		opword 0x90610024
		opword 0xEC220072
		lfs f4, float_3p2_80419c04(r2)
		opword 0x3881000C
		opword 0xC8010020
		opword 0x38600000
		opword 0x9001000C
		opword 0xEC002828
		lfs f5, float_1_80419bb4(r2)
		opword 0xEC1E002A
		opword 0xEC4000B2
		bl windowDispGX_Waku_col
		bl FontDrawStart
		bl FontDrawEdge
		lwz r0, dat_80419b98(r2)
		opword 0x38610008
		opword 0x90010008
		bl FontDrawColor
		lfs f1, float_0p1_80419bfc(r2)
		bl FontDrawScale
		lfs f0, float_3_80419c08(r2)
		opword 0xEC3FE828
		lfs f2, float_0p1_80419bfc(r2)
		opword 0x7FE3FB78
		opword 0xEC1E0028
		opword 0xEC220072
		opword 0xEC4000B2
		bl FontDrawStringShake
		opword 0xE3E10068
		opword 0xCBE10060
		opword 0xE3C10058
		opword 0xCBC10050
		opword 0xE3A10048
		opword 0xCBA10040
		opword 0xE3810038
		opword 0xCB810030
		opword 0x83E1002C
		opword 0x80010074
		opword 0x83C10028
		opword 0x7C0803A6
		opword 0x38210070
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifdef NONMATCHING
void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param) {
    FirstStrikeInfo* firstStrike = param;
    const char* message;
    f32 x;
    f32 y;
    f32 width;
    f32 shakeX;
    f32 shakeY;

    message = msgSearch(firstStrike->msg_tag);
    x = firstStrike->field_0x10;
    y = firstStrike->field_0x14;
    width = FontGetMessageWidth(message);
    shakeX = x + (f32)(irand(10000) % 5);
    shakeY = y + (f32)(irand(10000) % 5);
    windowDispGX_Waku_col(0, firstStrike->color, mulf(0.1f, shakeX - 10.0f - width / 2.0f),
                          mulf(shakeY, 0.1f), mulf(20.0f + width, 0.1f), 3.2f, 1.0f);
    FontDrawStart();
    FontDrawEdge();
    FontDrawColor((GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
    FontDrawScale(0.1f);
    FontDrawStringShake(mulf(0.1f, x - width / 2.0f), mulf(y - 3.0f, 0.1f), message);
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void fbatEncountCheck(void) {
	char _af_pad[56];
	asm volatile {
		lwz r3, gp(r13)
		lis r4, vec3_802c2f78@ha
		addi r28, r4, vec3_802c2f78@l
		la r29, work(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820008
		opword 0x3BBD0014
		opword 0x837D0004
		bl marioGetPtr
		opword 0x38000000
		opword 0x7C7E1B78
		opword 0x901D0010
		bl marioStGetSystemLevel
		opword 0x28030000
		opword 0x40820AE0
		opword 0x801D0008
		opword 0x540007FF
		opword 0x40820020
		bl marioKeyOffChk
		opword 0x2C030000
		opword 0x40820AC8
		bl marioCtrlOffChk
		opword 0x2C030000
		opword 0x41820008
		opword 0x48000AB8
		bl N_itemPickUpFromFieldCheck
		opword 0x2C030000
		opword 0x40820AAC
		lwz r4, gp(r13)
		opword 0x386013F1
		opword 0x83040168
		opword 0x3B580010
		opword 0x7F44D378
		bl fbatHitCheck
		opword 0x7C7F1B79
		opword 0x4182050C
		opword 0xA8180000
		opword 0x2C000001
		opword 0x40820500
		lwz r3, gp(r13)
		opword 0x80830168
		opword 0xA8040000
		opword 0x2C000001
		opword 0x4182000C
		opword 0x38600000
		opword 0x48000020
		opword 0x38600005
		opword 0x38000000
		opword 0xB0640000
		opword 0x38600001
		opword 0x98040002
		opword 0x93E40004
		opword 0x93E40008
		opword 0x2C030000
		opword 0x41820A40
		opword 0x807A0000
		opword 0x3C000010
		opword 0x7C030000
		opword 0x418200B0
		opword 0x40800044
		opword 0x3C000004
		opword 0x7C030000
		opword 0x41820078
		opword 0x40800024
		opword 0x3C000002
		opword 0x7C030000
		opword 0x41820068
		opword 0x408000F4
		opword 0x3C000001
		opword 0x7C030000
		opword 0x418200E8
		opword 0x480000E4
		opword 0x3C000008
		opword 0x7C030000
		opword 0x41820048
		opword 0x480000D4
		opword 0x3C000080
		opword 0x7C030000
		opword 0x41820084
		opword 0x40800024
		opword 0x3C000040
		opword 0x7C030000
		opword 0x41820050
		opword 0x408000B4
		opword 0x3C000020
		opword 0x7C030000
		opword 0x41820040
		opword 0x480000A4
		opword 0x3C000100
		opword 0x7C030000
		opword 0x41820078
		opword 0x48000094
		bl marioChgMotJump2
		lwz r0, dbg_battleskip(r13)
		opword 0x2C000001
		opword 0x41820084
		opword 0x809F0028
		opword 0x38A00001
		opword 0x807F0104
		opword 0x80840020
		bl animPoseSetAnim
		opword 0x4800006C
		lwz r0, dbg_battleskip(r13)
		opword 0x2C000001
		opword 0x41820060
		opword 0x809F0028
		opword 0x38A00001
		opword 0x807F0104
		opword 0x80840020
		bl animPoseSetAnim
		opword 0x48000048
		lwz r0, dbg_battleskip(r13)
		opword 0x2C000001
		opword 0x4182003C
		opword 0x809F0028
		opword 0x38A00001
		opword 0x807F0104
		opword 0x80840020
		bl animPoseSetAnim
		opword 0x48000024
		lwz r0, dbg_battleskip(r13)
		opword 0x2C000001
		opword 0x41820018
		opword 0x809F0028
		opword 0x38A00001
		opword 0x807F0104
		opword 0x80840020
		bl animPoseSetAnim
		opword 0x807F0104
		bl animPoseGetAnimPosePtr
		opword 0xC01F0144
		opword 0x7C781B78
		opword 0xD01F0148
		opword 0xC03F008C
		opword 0xC05F0094
		opword 0xC07E008C
		opword 0xC09E0094
		bl angleABf
		opword 0xD03F0144
		opword 0xC01F0144
		opword 0xFC200050
		bl reviseAngle
		lfs f0, float_neg90_80419bd8(r2)
		opword 0x38600004
		fadds f28, f1, f0
		bl camGetPtr
		opword 0xC0630018
		opword 0xC043000C
		opword 0xC0230020
		opword 0xC0030014
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC201050
		opword 0xFC400050
		bl atan2
		opword 0xFC200818
		lfs f0, float_rad2deg_80419bdc(r2)
		opword 0xEC200072
		bl reviseAngle
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f0, float_360_80419be0(r2)
		opword 0xEC21002A
		opword 0xEC21E028
		bl reviseAngle
		lfs f0, float_90_80419bd0(r2)
		opword 0xFC010040
		opword 0x40810014
		lfs f0, float_270_80419be4(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x41820020
		lfs f0, float_neg90_80419bd8(r2)
		opword 0xFC010040
		opword 0x40800078
		lfs f0, float_neg270_80419be8(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820068
		opword 0x38600004
		bl camGetPtr
		opword 0xC0630018
		opword 0xC043000C
		opword 0xC0230020
		opword 0xC0030014
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC201050
		opword 0xFC400050
		bl atan2
		opword 0xFC200818
		lfs f0, float_rad2deg_80419bdc(r2)
		opword 0xEC200072
		bl reviseAngle
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f0, float_360_80419be0(r2)
		opword 0xEC21002A
		lfs f0, float_180_80419bec(r2)
		opword 0xEC20082A
		bl reviseAngle
		opword 0xD038007C
		opword 0x48000058
		opword 0x38600004
		bl camGetPtr
		opword 0xC0630018
		opword 0xC043000C
		opword 0xC0230020
		opword 0xC0030014
		opword 0xEC431028
		opword 0xEC010028
		opword 0xFC201050
		opword 0xFC400050
		bl atan2
		opword 0xFC200818
		lfs f0, float_rad2deg_80419bdc(r2)
		opword 0xEC200072
		bl reviseAngle
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC010040
		opword 0x4080000C
		lfs f0, float_360_80419be0(r2)
		opword 0xEC21002A
		opword 0xD038007C
		lfs f3, float_360_80419be0(r2)
		lfs f0, float_180_80419bec(r2)
		opword 0x48000010
		opword 0xC0380074
		opword 0xEC21182A
		opword 0xD0380074
		opword 0xC058007C
		opword 0xC0380074
		opword 0xEC220828
		opword 0xFC010040
		opword 0x4181FFE4
		lfs f3, float_360_80419be0(r2)
		lfs f0, float_neg180_80419bf0(r2)
		opword 0x48000010
		opword 0xC0380074
		opword 0xEC211828
		opword 0xD0380074
		opword 0xC058007C
		opword 0xC0380074
		opword 0xEC420828
		opword 0xFC020040
		opword 0x4180FFE4
		lfs f0, float_0p75_80419bf4(r2)
		opword 0x3C000020
		opword 0xEC0008BA
		opword 0xD0180074
		opword 0x807A0000
		opword 0x7C030000
		opword 0x41820088
		opword 0x40800044
		opword 0x3C000008
		opword 0x7C030000
		opword 0x41820078
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C030000
		opword 0x41820068
		opword 0x408000C0
		opword 0x3C000002
		opword 0x7C030000
		opword 0x41820058
		opword 0x480000B0
		opword 0x3C000010
		opword 0x7C030000
		opword 0x41820048
		opword 0x480000A0
		opword 0x3C000100
		opword 0x7C030000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C030000
		opword 0x41820028
		opword 0x40800080
		opword 0x3C000040
		opword 0x7C030000
		opword 0x41820018
		opword 0x48000070
		opword 0x3C001000
		opword 0x7C030000
		opword 0x41820038
		opword 0x48000060
		lfs f4, float_0_80419b9c(r2)
		opword 0x38600003
		opword 0xC05F0090
		opword 0x38800003
		opword 0xC01F0150
		opword 0xFCC02090
		opword 0xC03F008C
		opword 0xEC42002A
		opword 0xC07F0094
		lfs f5, float_neg1_80419bf8(r2)
		bl effSmallStarEntry
		opword 0x48000030
		lfs f4, float_0_80419b9c(r2)
		opword 0x38600003
		opword 0xC05E0090
		opword 0x38800003
		opword 0xC01E01B8
		opword 0xFCC02090
		opword 0xC03E008C
		opword 0xEC42002A
		opword 0xC07E0094
		lfs f5, float_neg1_80419bf8(r2)
		bl effSmallStarEntry
		opword 0x807A0000
		opword 0x3C000020
		opword 0x7C030000
		opword 0x41820088
		opword 0x40800044
		opword 0x3C000008
		opword 0x7C030000
		opword 0x41820078
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C030000
		opword 0x41820068
		opword 0x4080060C
		opword 0x3C000002
		opword 0x7C030000
		opword 0x41820058
		opword 0x480005FC
		opword 0x3C000010
		opword 0x7C030000
		opword 0x41820048
		opword 0x480005EC
		opword 0x3C000100
		opword 0x7C030000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C030000
		opword 0x41820028
		opword 0x408005CC
		opword 0x3C000040
		opword 0x7C030000
		opword 0x41820018
		opword 0x480005BC
		opword 0x3C001000
		opword 0x7C030000
		opword 0x41820020
		opword 0x480005AC
		opword 0x281F0000
		opword 0x418205A4
		opword 0x387C0204
		opword 0x389F008C
		bl psndSFXOn_3D
		opword 0x48000594
		opword 0x387C0220
		opword 0x389E008C
		bl psndSFXOn_3D
		opword 0x48000584
		lfs f30, float_1000_80419bc8(r2)
		bl marioChkTalkable
		opword 0x2C030000
		opword 0x418204A0
		opword 0x881E0039
		opword 0x7C000775
		opword 0x40820494
		opword 0x83FD000C
		opword 0x3B200000
		opword 0x3B400000
		opword 0x48000428
		opword 0x807F0000
		opword 0x546007BD
		opword 0x41820414
		opword 0x54600739
		opword 0x4082040C
		opword 0x801F0128
		opword 0x28000000
		opword 0x41820400
		opword 0xC05E0090
		opword 0x3B000000
		opword 0xC01E01B8
		opword 0xC03F0090
		opword 0xEC02002A
		opword 0xFC010040
		opword 0x41810340
		opword 0xC01F0150
		opword 0xEC01002A
		opword 0xFC020040
		opword 0x41810330
		opword 0xC01E008C
		la r3, _af_pad+40
		opword 0x389F008C
		opword 0xD0010030
		opword 0xC01E0094
		opword 0xD0010038
		opword 0xD0210034
		bl PSVECDistance
		opword 0xC05E01B4
		opword 0xC01F014C
		lfs f3, float_0p5_80419ba0(r2)
		opword 0xEC42002A
		lfs f0, float_10_80419bb8(r2)
		opword 0xEC0300BA
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820010
		opword 0xFC01F040
		opword 0x40800008
		opword 0x7FF9FB78
		opword 0x3AE00000
		opword 0x38600004
		bl camGetPtr
		opword 0xC3830114
		bl marioGetDispDir
		opword 0xEC21E028
		bl reviseAngle
		opword 0xFFE00890
		lfs f29, float_180_80419bec(r2)
		li r22, 0x0
		opword 0x2C160001
		opword 0x41820040
		opword 0x40800074
		opword 0x2C160000
		opword 0x40800008
		opword 0x48000068
		opword 0x38600004
		bl camGetPtr
		opword 0xC3830114
		opword 0xC03E008C
		opword 0xC05E0094
		opword 0xC07F008C
		opword 0xC09F0094
		bl angleABf
		opword 0xEC21E028
		bl reviseAngle
		opword 0x48000070
		opword 0x38600004
		bl camGetPtr
		lfs f2, float_0p5_80419ba0(r2)
		opword 0xC03F014C
		opword 0xC01F008C
		opword 0xC3830114
		opword 0xEC62007A
		opword 0xC03E008C
		opword 0xC05E0094
		opword 0xC09F0094
		bl angleABf
		opword 0xEC21E028
		bl reviseAngle
		opword 0x48000038
		opword 0x38600004
		bl camGetPtr
		lfs f2, float_0p5_80419ba0(r2)
		opword 0xC03F014C
		opword 0xC01F008C
		opword 0xC3830114
		opword 0xEC62007C
		opword 0xC03E008C
		opword 0xC05E0094
		opword 0xC09F0094
		bl angleABf
		opword 0xEC21E028
		bl reviseAngle
		opword 0xFC01E840
		opword 0x40800014
		opword 0xFC1FE840
		opword 0x4181001C
		opword 0x3AE00001
		opword 0x48000020
		opword 0xFC1FE840
		opword 0x4180000C
		opword 0x3AE00001
		opword 0x48000010
		opword 0x3AD60001
		opword 0x2C160003
		opword 0x4180FF20
		opword 0x2C170000
		opword 0x418201CC
		opword 0xC01E008C
		opword 0x38610030
		opword 0x389F008C
		opword 0xD0010030
		opword 0xC01E0094
		opword 0xD0010038
		opword 0xC01F0090
		opword 0xD0010034
		bl PSVECDistance
		opword 0xC05E01B4
		opword 0xFFE00890
		opword 0xC01F014C
		lfs f3, float_0p5_80419ba0(r2)
		opword 0xEC42002A
		lfs f0, float_10_80419bb8(r2)
		opword 0xEC0300BA
		opword 0xFC1F0040
		opword 0x41810184
		opword 0xC07F008C
		opword 0xC03E008C
		opword 0xC05F0094
		opword 0xC01E0094
		opword 0xEF830828
		lfs f1, float_0_80419b9c(r2)
		opword 0xEFA20028
		opword 0xFC400890
		opword 0xFC60E090
		opword 0xFC80E890
		bl angleABf
		opword 0x3861002C
		opword 0x38810028
		bl sincosf
		opword 0xEC3D0772
		lfs f0, float_0_80419b9c(r2)
		opword 0xEC9C0F3A
		opword 0xFC040040
		opword 0x4081004C
		opword 0xFC202034
		opword 0xC87C01C0
		opword 0xC85C01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC010032
		opword 0xFC840032
		opword 0xFC802018
		opword 0x48000088
		opword 0xC81C01D0
		opword 0xFC040040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0810008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0xD0810024
		opword 0x38810020
		lfs f3, float_0p75_80419bf4(r2)
		opword 0x38A1001C
		opword 0xC05E01B8
		opword 0x38C10018
		opword 0xC01E0090
		opword 0x38E10024
		opword 0xC03E008C
		opword 0x39010014
		opword 0xEC4300BA
		opword 0xC07E0094
		opword 0xC081002C
		opword 0x39210010
		lfs f5, float_0_80419b9c(r2)
		opword 0x3941000C
		opword 0xC0C10028
		opword 0x38600000
		bl hitCheckFilter
		opword 0x28030000
		opword 0x40820018
		opword 0xFC1FF040
		opword 0x3B000001
		opword 0x4080000C
		opword 0xFFC0F890
		opword 0x93FD0010
		opword 0x2C180000
		opword 0x41820060
		opword 0x801F01D4
		opword 0x54000085
		opword 0x40820094
		bl marioGetPtr
		opword 0x801F01D4
		opword 0x7C781B78
		opword 0x64002000
		opword 0x901F01D4
		opword 0xC01F0144
		opword 0xD01F0148
		opword 0x807F011C
		bl evtStopID
		opword 0x801F0000
		opword 0x540001CF
		opword 0x40820064
		opword 0xC03F008C
		opword 0xC05F0094
		opword 0xC078008C
		opword 0xC0980094
		bl angleABf
		bl reviseAngle
		opword 0xD03F0144
		opword 0x48000044
		opword 0x807F01D4
		opword 0x54600085
		opword 0x41820038
		opword 0x546000C2
		opword 0x901F01D4
		opword 0x801F0000
		opword 0x54000253
		opword 0x41820018
		opword 0xC01F0148
		opword 0xD01F0144
		opword 0x807F011C
		bl evtStartID
		opword 0x48000010
		opword 0x801F0140
		opword 0x64001000
		opword 0x901F0140
		opword 0x3B5A0001
		opword 0x3BFF0340
		opword 0x7C1AD800
		opword 0x4180FBD8
		opword 0x933E01D4
		opword 0x801D0010
		opword 0x28000000
		opword 0x41820048
		opword 0x38600000
		bl keyGetButtonTrg
		opword 0x546005EF
		opword 0x41820038
		lwz r3, gp(r13)
		opword 0x809D0010
		opword 0x80A30168
		opword 0xA8050000
		opword 0x2C000001
		opword 0x408200F4
		opword 0x38600002
		opword 0x38000000
		opword 0xB0650000
		opword 0x98050002
		opword 0x90850004
		opword 0x90040318
		opword 0x480000D8
		lwz r3, gp(r13)
		opword 0x83230168
		opword 0xA8190000
		opword 0x2C000001
		opword 0x408200C0
		opword 0x3AD90010
		opword 0x38602361
		opword 0x7EC4B378
		bl fbatHitCheck
		opword 0x7C781B79
		opword 0x418200A8
		opword 0xA8190000
		opword 0x2C000001
		opword 0x4082009C
		lwz r3, gp(r13)
		opword 0x80960000
		opword 0x80A30168
		opword 0xA8050000
		opword 0x2C000001
		opword 0x4082001C
		opword 0x38600003
		opword 0x38000000
		opword 0xB0650000
		opword 0x98050002
		opword 0x93050004
		opword 0x90980318
		opword 0x80760000
		opword 0x3C000004
		opword 0x7C030000
		opword 0x41820028
		opword 0x40800014
		opword 0x3C000002
		opword 0x7C030000
		opword 0x41820018
		opword 0x48000018
		opword 0x3C000008
		opword 0x7C030000
		opword 0x41820008
		opword 0x48000008
		bl marioChgMotJump2
		lfs f4, float_0_80419b9c(r2)
		opword 0x38600003
		opword 0xC0580090
		opword 0x38800003
		opword 0xC0180150
		opword 0xFCC02090
		opword 0xC038008C
		opword 0xEC42002A
		opword 0xC0780094
		lfs f5, float_neg1_80419bf8(r2)
		bl effSmallStarEntry
		opword 0x48000008
		bl npcKoopaModeEncountCheck
	}
#endif
}
#ifdef NONMATCHING

#define FBAT_SUB(d) (((u8*)(d))[2])
#define FBAT_NPC(d) (*(NpcEntry**)((u8*)(d) + 4))
#define FBAT_EVTID(d) (*(s32*)((u8*)(d) + 0xC))

void partyKeyOn(void);
void partyKeyOff(void);
void marioChgTalkMotion(void);
void marioChgStayMotion(void);
BOOL marioChkTalkable(void);
void* fbatHitCheck(u32 flags, void* a1);

#include "eff/eff_small_star.h"
s32 _majinai_effect(EventEntry* event, BOOL isFirstCall);
s32 _check(EventEntry* event, BOOL isFirstCall);
s32 marioStGetSystemLevel(void);
BOOL N_itemPickUpFromFieldCheck(void);
void marioChgMotJump2(void);
f32 marioGetDispDir(void);
void npcKoopaModeEncountCheck(void);

static inline f32 fbat_camAngle(void) {
    CameraEntry* camera = camGetPtr(CAMERA_3D);
    f32 dx = camera->cameraAt.x - camera->cameraPos.x;
    f32 dz = camera->cameraAt.z - camera->cameraPos.z;
    f32 angle = reviseAngle(NPC_RAD2DEG((f32)atan2(-dx, -dz)));
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

static inline BOOL fbat_setHit(NpcEntry* npc) {
    FieldBattleData* d = gp->fbatData;
    if (d->mode != 1) {
        return FALSE;
    }
    d->mode = 5;
    FBAT_SUB(d) = 0;
    FBAT_NPC(d) = npc;
    d->target = npc;
    return TRUE;
}

void fbatEncountCheck(void)
{
  NpcWork *wp = (gp->inBattle) ? (&work.battle) : (&work.field);
  s32 total = wp->total;
  MarioWork *mario = marioGetPtr();
  FieldBattleData *data;
  NpcEntry *npc;
  u32 *kind;
  s32 i;
  NpcEntry *talk;
  f32 best;
  wp->talkTarget = (void *) 0;
  if (((u32) marioStGetSystemLevel()) != 0)
  {
    return;
  }
  if (!(wp->flags & 1))
  {
    if ((!npc->width) && (!npc->width))
    {
    }
    if (marioKeyOffChk() || marioCtrlOffChk())
    {
      return;
    }
  }
  if (N_itemPickUpFromFieldCheck())
  {
    return;
  }
  data = gp->fbatData;
  kind = (u32 *) (((u8 *) data) + 0x10);
  npc = fbatHitCheck(0x13f1, kind);
  if (npc && (data->mode == 1))
  {
    AnimationPose *pose;
    f32 rel;
    f32 ang;
    if (!fbat_setHit(npc))
    {
      return;
    }
    switch (*kind)
    {
      case 0x10000:

      default:
        break;

      case 0x20000:

      case 0x40000:

      case 0x80000:
        marioChgMotJump2();
        if (dbg_battleskip != 1)
      {
        animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
      }
        break;

      case 0x100000:

      case 0x200000:

      case 0x400000:
        if (dbg_battleskip != 1)
      {
        animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
      }
        break;

      case 0x800000:
        if (dbg_battleskip != 1)
      {
        animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
      }
        break;

      case 0x1000000:
        if (dbg_battleskip != 1)
      {
        animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
      }
        break;

    }

    pose = animPoseGetAnimPosePtr(npc->poseId);
    npc->savedDirection = npc->direction;
    npc->direction = angleABf(npc->position.x, npc->position.z, mario->position.x, mario->position.z);
    rel = reviseAngle(-npc->direction);
    rel += -90.0f;
    ang = reviseAngle(fbat_camAngle() - rel);
    if (((ang > 90.0f) && (ang <= 270.0f)) || ((ang < (-90.0f)) && (ang >= (-270.0f))))
    {
      pose->peraTargetRotY = reviseAngle(180.0f + fbat_camAngle());
    }
    else
    {
      pose->peraTargetRotY = fbat_camAngle();
    }
    while ((pose->peraTargetRotY - pose->rotationY) > 180.0f)
    {
      pose->rotationY += 360.0f;
    }

    while ((pose->peraTargetRotY - pose->rotationY) < (-180.0f))
    {
      pose->rotationY -= 360.0f;
    }

    pose->rotationY += 0.75f * (pose->peraTargetRotY - pose->rotationY);
    switch (*kind)
    {
      case 0x20000:

      case 0x40000:

      case 0x80000:

      case 0x100000:

      case 0x200000:

      case 0x400000:

      case 0x800000:

      case 0x1000000:
        effSmallStarEntry(3, 3, npc->position.x, npc->position.y + npc->height, npc->position.z, 0.0f, -1.0f, 0.0f);
        break;

      case 0x10000000:
        effSmallStarEntry(3, 3, mario->position.x, mario->position.y + mario->wPlayerCollisionBox.y, mario->position.z, 0.0f, -1.0f, 0.0f);
        break;

    }

    switch (*kind)
    {
      case 0x20000:

      case 0x40000:

      case 0x80000:

      case 0x100000:

      case 0x200000:

      case 0x400000:

      case 0x800000:

      case 0x1000000:
        if (npc)
      {
        psndSFXOn_3D((char*)str_802C317C, &npc->position);
      }
        break;

      case 0x10000000:
        psndSFXOn_3D((char*)str_802C3198, &mario->position);
        break;

    }

    return;
  }
  best = 1000.0f;
  if (marioChkTalkable() && (!mario->keyOffCount))
  {
    talk = (void *) 0;
    npc = wp->entries;
    for (i = 0; i < total; i++, npc++)
    {
      BOOL hit;
      if (((!(npc->flags & 2)) || (npc->flags & 8)) || (!npc->talkEvt))
      {
        continue;
      }
      hit = 0;
      if ((!(npc->position.y > (mario->position.y + mario->wPlayerCollisionBox.y))) && (!(mario->position.y > (npc->position.y + npc->height))))
      {
        Vec pos;
        f32 dist;
        BOOL facing;
        s32 j;
        f32 dir;
        f32 a;
        f32 yaw;
        pos.x = mario->position.x;
        pos.z = mario->position.z;
        pos.y = npc->position.y;
        dist = PSVECDistance(&pos, &npc->position);
        if ((dist <= ((0.5f * (mario->wPlayerCollisionBox.x + npc->width)) + 10.0f)) && (dist < best))
        {
          talk = npc;
        }
        facing = 0;
        yaw = camGetPtr(CAMERA_3D)->viewYaw;
        dir = reviseAngle(marioGetDispDir() - yaw);
        for (j = 0; j < 3; j++)
        {
          switch (j)
          {
            case 0:
              yaw = camGetPtr(CAMERA_3D)->viewYaw;
              a = reviseAngle(angleABf(mario->position.x, mario->position.z, npc->position.x, npc->position.z) - yaw);
              break;

            case 1:
              yaw = camGetPtr(CAMERA_3D)->viewYaw;
              a = reviseAngle(angleABf(mario->position.x, mario->position.z, npc->position.x + (0.5f * npc->width), npc->position.z) - yaw);
              break;

            default:
              yaw = camGetPtr(CAMERA_3D)->viewYaw;
              a = reviseAngle(angleABf(mario->position.x, mario->position.z, npc->position.x - (0.5f * npc->width), npc->position.z) - yaw);
              break;

          }

          if (a < 180.0f)
          {
            if (!(dir > 180.0f))
            {
              facing = 1;
              break;
            }
          }
          else
            if (!(dir < 180.0f))
          {
            facing = 1;
            break;
          }
        }

        if (facing)
        {
          pos.x = mario->position.x;
          pos.z = mario->position.z;
          pos.y = npc->position.y;
          dist = PSVECDistance(&pos, &npc->position);
          if (!(dist > ((0.5f * (mario->wPlayerCollisionBox.x + npc->width)) + 10.0f)))
          {
            f32 dx = npc->position.x - mario->position.x;
            f32 dz = npc->position.z - mario->position.z;
            f32 s;
            f32 c;
            f32 len;
            f32 hx;
            f32 hy;
            f32 hz;
            f32 nx;
            f32 ny;
            f32 nz;
            sincosf(&s, &c, angleABf(0.0f, 0.0f, dx, dz));
            len = npc_sqrtf((dx * dx) + (dz * dz));
            if (!hitCheckFilter((void *) 0, &hx, &hy, &hz, &len, &nx, &ny, &nz, mario->position.x, mario->position.y + (0.75f * mario->wPlayerCollisionBox.y), mario->position.z, s, 0.0f, c))
            {
              hit = 1;
              if (dist < best)
              {
                best = dist;
                wp->talkTarget = npc;
              }
            }
          }
        }
      }
      if (hit)
      {
        if (!(npc->jumpFlags & 0x20000000))
        {
          MarioWork *m = marioGetPtr();
          npc->jumpFlags |= 0x20000000;
          npc->savedDirection = npc->direction;
          evtStopID(npc->regularEvtId);
          if (!(npc->flags & 0x01000000))
          {
            npc->direction = reviseAngle(angleABf(npc->position.x, npc->position.z, m->position.x, m->position.z));
          }
        }
      }
      else
        if (npc->jumpFlags & 0x20000000)
      {
        npc->jumpFlags &= ~0x20000000;
        if (npc->flags & 0x400000)
        {
          npc->direction = npc->savedDirection;
          evtStartID(npc->regularEvtId);
        }
        else
        {
          npc->interruptFlags |= 0x10000000;
        }
      }
    }

    *((NpcEntry **) (((u8 *) mario) + 0x1D4)) = talk;
    if (wp->talkTarget && (keyGetButtonTrg(0) & 0x100))
    {
      npc = wp->talkTarget;
      data = gp->fbatData;
      if (data->mode != 1)
      {
        return;
      }
      data->mode = 2;
      ((u8 *) data)[2] = 0;
      *((NpcEntry **) (((u8 *) data) + 4)) = npc;
      *((u32 *) npc->field_318) = 0;
      return;
    }
  }
  data = gp->fbatData;
  if (data->mode == 1)
  {
    u32 *kind = (u32 *) (((u8 *) data) + 0x10);
    npc = fbatHitCheck(0x2361, kind);
    if (npc && (data->mode == 1))
    {
      u32 k = *kind;
      FieldBattleData *d = gp->fbatData;
      if (d->mode == 1)
      {
        d->mode = 3;
        ((u8 *) d)[2] = 0;
        *((NpcEntry **) (((u8 *) d) + 4)) = npc;
        *((u32 *) npc->field_318) = k;
      }
      switch (*kind)
      {
        case 0x20000:

        case 0x40000:

        case 0x80000:
          marioChgMotJump2();
          break;

      }

      effSmallStarEntry(3, 3, npc->position.x, npc->position.y + npc->height, npc->position.z, 0.0f, -1.0f, 0.0f);
      return;
    }
  }
  npcKoopaModeEncountCheck();
}
#endif
#ifndef NONMATCHING
#pragma pop
#endif

void fbatTalkMode(void) {
    FieldBattleData* data = gp->fbatData;
    NpcEntry* npc = FBAT_NPC(data);
    MarioWork* mario = marioGetPtr();
    EventEntry* evt;

    switch (FBAT_SUB(data)) {
        case 0:
            evtStopID(FBAT_NPC(data)->regularEvtId);
            if (!(npc->flags & 0x01000000)) {
                npc->direction = reviseAngle(angleABf(npc->position.x, npc->position.z,
                                                      mario->position.x, mario->position.z));
            }
            marioKeyOff();
            partyKeyOff();
            switch (data->mode) {
                case 3:
                    evt = evtEntry(npc->deadEvent, 0, 0);
                    evt->wNpcEventType = 6;
                    break;
                default:
                    evt = evtEntry(npc->talkEvt, 0, 0);
                    evt->wNpcEventType = 6;
                    marioChgTalkMotion();
                    break;
            }
            evt->ownerNPC = npc;
            FBAT_EVTID(data) = evt->eventId;
            FBAT_SUB(data)++;
            break;
        case 1:
            if (!evtCheckID(FBAT_EVTID(data))) {
                if (!(npc->jumpFlags & 0x20000000)) {
                    evtStartID(FBAT_NPC(data)->regularEvtId);
                    npc->direction = npc->savedDirection;
                }
                if (npc->flags & 0x400) {
                    npc->field_108 = 0;
                }
                if (npc->flags & 0x200) {
                    animPoseSetAnim(npc->poseId, npc->currentAnim, 1);
                }
                marioKeyOn();
                partyKeyOn();
                marioChgStayMotion();
                data->mode = 1;
                npcGetWorkPtrInline()->talkTarget = NULL;
            }
            break;
    }
}

#ifdef NONMATCHING
#define FBAT_U32(d, off) (*(u32*)((u8*)(d) + (off)))
#define NPC_ENEMY_LEVEL(npc) (*(u8*)((u8*)*(void**)(npc)->battleInfo.groupSetup->enemyData + 0xE))

void BattleMajinaiDone(void);
extern s32 _evt_majinai_coin_up_effect[];
void marioChgMoveMotion(void);

#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void fbatBattleMode(void) {
#ifdef NONMATCHING
    FieldBattleInfo* info;
    NpcWork* wp;
    s32 num;
    EventEntry* evt;
    s32 result;
    s32 mult;
    NpcEntry* cur;
    s32 stolen;
    BOOL skip;
    BOOL win;
    NpcBattleInfo* binfo;
    FieldBattleData* data;
    PouchData* pouch;
    MarioWork* mario;
    data = gp->fbatData;
    cur = data->target;
    pouch = pouchGetPtr();
    mario = marioGetPtr();
    cur->rotation.y = 0.0f;
    switch (FBAT_SUB(data)) {
        case 0:
            if (dbg_battleskip == 1) {
                data->mode = 1;
                break;
            }
            if (!cur->battleInfo.groupSetup) {
                data->mode = 1;
                break;
            }
            if (gp->systemLevelFlags & 0x10) {
                data->mode = 1;
                break;
            }
            if (!cur->deadEvent) {
                data->mode = 1;
                break;
            }
            data->target->interruptFlags &= 0xF00;
            evtStopID(data->target->regularEvtId);
            info = &data->info;
            if (!(cur->battleInfo.field_4 & 0x10000000)) {
                if (pouchEquipCheckBadge(0x142) && NPC_ENEMY_LEVEL(cur) < pouch->level) {
                    skip = TRUE;
                    win = TRUE;
                    goto decided;
                }
                if (pouchEquipCheckBadge(0x141) && (FBAT_U32(data, 0x10) & 0x01FE0000) &&
                    NPC_ENEMY_LEVEL(cur) < pouch->level) {
                    skip = TRUE;
                    win = TRUE;
                    goto decided;
                }
            }
            if (dbg_battleskip == 2) {
                skip = TRUE;
                win = TRUE;
            } else {
                skip = FALSE;
                win = FALSE;
            }
        decided:
            if (!skip) {
                if (!win) {
                    gp->fbatData->firstStrike.enabled = TRUE;
                }
                marioFBattlePrepare();
                seqSetSeq(4, NULL, NULL);
                if (FBAT_U32(data, 0x10) == 0x10000000) {
                    unk_80058374();
                }
                FBAT_SUB(data) = 1;
            } else {
                if (win) {
                    BattleInformationSetResult(info, 2);
                } else {
                    BattleInformationSetResult(info, 5);
                }
                FBAT_SUB(data) = 4;
            }
            break;
        case 1:
            if (gp->inBattle) {
                FBAT_SUB(data)++;
            }
            break;
        case 2:
            if (!gp->inBattle) {
                data->field_54C = 0;
                result = BattleInformationGetResult(&data->info);
                if (pouch->mMerleeNextCurseType == 4 && result == 1) {
                    FBAT_SUB(data) = 3;
                    data->field_54C = 1;
                    evt = evtEntry(_evt_majinai_coin_up_effect, 0, 0);
                    FBAT_U32(data, 0x48) = evt->eventId;
                    BattleMajinaiDone();
                    marioKeyOff();
                    wp = npcGetWorkPtrInline();
                    num = wp->total;
                    for (result = 0, cur = wp->entries; result < num; result++, cur++) {
                        if (cur && (cur->flags & 2) && (cur->flags & 0x10000000)) {
                            cur->jumpFlags |= 0x10000;
                            evtStopID(cur->regularEvtId);
                            animPoseSetLocalTimeRate(cur->poseId, 0.0f);
                        }
                    }
                } else {
                    marioFBattlePost();
                    FBAT_SUB(data) = 4;
                }
            }
            break;
        case 3:
            if (!evtCheckID(FBAT_U32(data, 0x48))) {
                marioKeyOn();
                marioFBattlePost();
                FBAT_U32(data, 0x48) = 0;
                FBAT_SUB(data) = 4;
                wp = npcGetWorkPtrInline();
                num = wp->total;
                for (result = 0, cur = wp->entries; result < num; result++, cur++) {
                            if (cur && (cur->flags & 2) && (cur->flags & 0x10000000) &&
                        (cur->jumpFlags & 0x10000)) {
                        cur->jumpFlags &= ~0x10000;
                        evtStartID(cur->regularEvtId);
                        animPoseSetLocalTimeRate(cur->poseId, 1.0f);
                    }
                }
            }
            break;
        case 4:
            marioChgMoveMotion();
            if (!gp->inBattle) {
                info = &data->info;
                result = BattleInformationGetResult(info);
                stolen = FALSE;
                if (cur->battleInfo.stolenItems[0]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[1]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[2]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[3]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[4]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[5]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[6]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[7]) {
                    stolen = TRUE;
                }
                data->mode = 1;
                if (result == 1 || result == 2) {
                    mult = 1;
                    if (BattleInformationGetResult(info) == 1) {
                        cur->btlCoinDropCount = info->coins;
                    } else if (result == 1) {
                        cur->btlCoinDropCount = cur->baseCoinCount;
                    } else {
                        cur->btlCoinDropCount = 0;
                        mult = 0;
                        goto apply;
                    }
                    if (data->field_54C) {
                        mult = 3;
                    }
                    if (pouchEquipCheckBadge(0x139)) {
                        mult += pouchEquipCheckBadge(0x139);
                    }
                    if (cur->battleInfo.field_4 & 0x100) {
                        mult++;
                    }
                apply:
                    cur->btlCoinDropCount *= mult;
                    if (!stolen) {
                        npcGroupDead(cur, 0);
                        break;
                    }
                    if (cur->flags & 0x400) {
                        cur->field_108 = 0;
                    }
                    cur->wFbatHitCheckRelated = 90;
                    cur->interruptFlags &= ~0x100;
                    cur->interruptFlags |= 0x10000000;
                    if (cur->flags & 0x200) {
                        animPoseSetAnim(cur->poseId, cur->currentAnim, 1);
                    }
                    binfo = &cur->battleInfo;
                    for (result = 0; result < 8; result++) {
                        if (binfo->recoveredItems[result]) {
                            itemFlagOn(itemEntry(NULL, binfo->recoveredItems[result], 11, -1, 0,
                                                 cur->position.x, cur->position.y, cur->position.z),
                                       0x100);
                            binfo->recoveredItems[result] = 0;
                        }
                    }
                } else if (result == 4) {
                    if (cur->flags & 0x400) {
                        cur->field_108 = 0;
                    }
                    cur->interruptFlags |= 0x10000000;
                    marioSetMutekiTime(3000);
                    *(s16*)((u8*)mario + 0x2C0) = sysMsec2Frame(3000);
                    if (cur->flags & 0x200) {
                        animPoseSetAnim(cur->poseId, cur->currentAnim, 1);
                    }
                }
            }
            break;
    }
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0xBF410008
		lwz r3, gp(r13)
		opword 0x83C30168
		opword 0x83BE0008
		bl pouchGetPtr
		opword 0x7C7F1B78
		bl marioGetPtr
		lfs f0, float_0_80419b9c(r2)
		opword 0x7C7B1B78
		opword 0xD01D00F0
		opword 0x889E0002
		opword 0x2C040002
		opword 0x418201F4
		opword 0x40800014
		opword 0x2C040000
		opword 0x4182001C
		opword 0x408001C8
		opword 0x480005F8
		opword 0x2C040004
		opword 0x41820370
		opword 0x408005EC
		opword 0x480002C0
		lwz r0, dbg_battleskip(r13)
		opword 0x2C000001
		opword 0x40820010
		opword 0x38000001
		opword 0xB01E0000
		opword 0x480005D0
		opword 0x801D0248
		opword 0x28000000
		opword 0x40820010
		opword 0x38000001
		opword 0xB01E0000
		opword 0x480005B8
		lwz r3, gp(r13)
		opword 0x80030018
		opword 0x540006F7
		opword 0x41820010
		opword 0x38000001
		opword 0xB01E0000
		opword 0x4800059C
		opword 0x801D012C
		opword 0x28000000
		opword 0x40820010
		opword 0x38000001
		opword 0xB01E0000
		opword 0x48000584
		opword 0x807E0008
		opword 0x80030140
		opword 0x5400052E
		opword 0x90030140
		opword 0x807E0008
		opword 0x8063011C
		bl evtStopID
		opword 0x801D0234
		opword 0x3B9E0020
		opword 0x540000C7
		opword 0x40820080
		opword 0x38600142
		bl pouchEquipCheckBadge
		opword 0x2C030000
		opword 0x4182002C
		opword 0x807D0248
		opword 0xA81F008A
		opword 0x80630004
		opword 0x80630000
		opword 0x8863000E
		opword 0x7C030000
		opword 0x40800010
		opword 0x38000001
		opword 0x38600001
		opword 0x48000068
		opword 0x38600141
		bl pouchEquipCheckBadge
		opword 0x2C030000
		opword 0x41820038
		opword 0x801E0010
		opword 0x540001DD
		opword 0x4182002C
		opword 0x807D0248
		opword 0xA81F008A
		opword 0x80630004
		opword 0x80630000
		opword 0x8863000E
		opword 0x7C030000
		opword 0x40800010
		opword 0x38000001
		opword 0x38600001
		opword 0x48000024
		lwz r0, dbg_battleskip(r13)
		opword 0x2C000002
		opword 0x40820010
		opword 0x38000001
		opword 0x38600001
		opword 0x4800000C
		opword 0x38000000
		opword 0x38600000
		opword 0x2C000000
		opword 0x40820050
		opword 0x2C030000
		opword 0x40820014
		lwz r3, gp(r13)
		opword 0x38000001
		opword 0x80630168
		opword 0x90030550
		bl marioFBattlePrepare
		opword 0x38600004
		opword 0x38800000
		opword 0x38A00000
		bl seqSetSeq
		opword 0x807E0010
		opword 0x3C03F000
		opword 0x28000000
		opword 0x40820008
		bl unk_80058374
		opword 0x38000001
		opword 0x981E0002
		opword 0x48000468
		opword 0x2C030000
		opword 0x41820014
		opword 0x7F83E378
		opword 0x38800002
		bl BattleInformationSetResult
		opword 0x48000010
		opword 0x7F83E378
		opword 0x38800005
		bl BattleInformationSetResult
		opword 0x38000004
		opword 0x981E0002
		opword 0x48000438
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820428
		opword 0x38040001
		opword 0x981E0002
		opword 0x4800041C
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x4082040C
		opword 0x38000000
		opword 0x387E0020
		opword 0x981E054C
		bl BattleInformationGetResult
		opword 0x881F05BA
		opword 0x28000004
		opword 0x408200B8
		opword 0x2C030001
		opword 0x408200B0
		opword 0x38000003
		lis r3, _evt_majinai_coin_up_effect@ha
		opword 0x981E0002
		opword 0x38000001
		addi r3, r3, _evt_majinai_coin_up_effect@l
		opword 0x38800000
		opword 0x981E054C
		opword 0x38A00000
		bl evtEntry
		opword 0x8003015C
		opword 0x901E0048
		bl BattleMajinaiDone
		bl marioKeyOff
		lwz r3, gp(r13)
		la r4, work(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820008
		opword 0x38840014
		opword 0x83840004
		opword 0x3BA00000
		opword 0x8364000C
		opword 0x48000048
		opword 0x281B0000
		opword 0x41820038
		opword 0x807B0000
		opword 0x546007BD
		opword 0x4182002C
		opword 0x546000C7
		opword 0x41820024
		opword 0x801B01D4
		opword 0x64000001
		opword 0x901B01D4
		opword 0x807B011C
		bl evtStopID
		opword 0x807B0104
		lfs f1, float_0_80419b9c(r2)
		bl animPoseSetLocalTimeRate
		opword 0x3BBD0001
		opword 0x3B7B0340
		opword 0x7C1DE000
		opword 0x4180FFB8
		opword 0x4800033C
		bl marioFBattlePost
		opword 0x38000004
		opword 0x981E0002
		opword 0x4800032C
		opword 0x807E0048
		bl evtCheckID
		opword 0x2C030000
		opword 0x4082031C
		bl marioKeyOn
		bl marioFBattlePost
		opword 0x38600000
		opword 0x38000004
		opword 0x907E0048
		la r4, work(r13)
		opword 0x981E0002
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x41820008
		opword 0x38840014
		opword 0x83840004
		opword 0x3BA00000
		opword 0x8364000C
		opword 0x48000050
		opword 0x281B0000
		opword 0x41820040
		opword 0x807B0000
		opword 0x546007BD
		opword 0x41820034
		opword 0x546000C7
		opword 0x4182002C
		opword 0x807B01D4
		opword 0x546003DF
		opword 0x41820020
		opword 0x5460041C
		opword 0x901B01D4
		opword 0x807B011C
		bl evtStartID
		opword 0x807B0104
		lfs f1, float_1_80419bb4(r2)
		bl animPoseSetLocalTimeRate
		opword 0x3BBD0001
		opword 0x3B7B0340
		opword 0x7C1DE000
		opword 0x4180FFB0
		opword 0x48000284
		bl marioChgMoveMotion
		lwz r3, gp(r13)
		opword 0x80030014
		opword 0x2C000000
		opword 0x40820270
		opword 0x3BFE0020
		opword 0x7FE3FB78
		bl BattleInformationGetResult
		opword 0x801D028C
		opword 0x7C7C1B78
		opword 0x3B400000
		opword 0x2C000000
		opword 0x4182000C
		opword 0x3B400001
		opword 0x4800008C
		opword 0x801D0290
		opword 0x2C000000
		opword 0x4182000C
		opword 0x3B400001
		opword 0x48000078
		opword 0x801D0294
		opword 0x2C000000
		opword 0x4182000C
		opword 0x3B400001
		opword 0x48000064
		opword 0x801D0298
		opword 0x2C000000
		opword 0x4182000C
		opword 0x3B400001
		opword 0x48000050
		opword 0x801D029C
		opword 0x2C000000
		opword 0x4182000C
		opword 0x3B400001
		opword 0x4800003C
		opword 0x801D02A0
		opword 0x2C000000
		opword 0x4182000C
		opword 0x3B400001
		opword 0x48000028
		opword 0x801D02A4
		opword 0x2C000000
		opword 0x4182000C
		opword 0x3B400001
		opword 0x48000014
		opword 0x801D02A8
		opword 0x2C000000
		opword 0x41820008
		opword 0x3B400001
		opword 0x38000001
		opword 0x2C1C0001
		opword 0xB01E0000
		opword 0x4182000C
		opword 0x2C1C0002
		opword 0x40820150
		opword 0x7FE3FB78
		opword 0x3B600001
		bl BattleInformationGetResult
		opword 0x2C030001
		opword 0x40820010
		opword 0x801F0014
		opword 0x981D0315
		opword 0x48000028
		opword 0x2C1C0001
		opword 0x40820010
		opword 0x881D0316
		opword 0x981D0315
		opword 0x48000014
		opword 0x38000000
		opword 0x3B600000
		opword 0x981D0315
		opword 0x48000040
		opword 0x881E054C
		opword 0x28000000
		opword 0x41820008
		opword 0x3B600003
		opword 0x38600139
		bl pouchEquipCheckBadge
		opword 0x2C030000
		opword 0x41820010
		opword 0x38600139
		bl pouchEquipCheckBadge
		opword 0x7F7B1A14
		opword 0x801D0234
		opword 0x540005EF
		opword 0x41820008
		opword 0x3B7B0001
		opword 0x881D0315
		opword 0x2C1A0000
		opword 0x7C00D9D6
		opword 0x981D0315
		opword 0x40820014
		opword 0x7FA3EB78
		opword 0x38800000
		bl npcGroupDead
		opword 0x48000104
		opword 0x801D0000
		opword 0x5400056B
		opword 0x4182000C
		opword 0x38000000
		opword 0x901D0108
		opword 0x3800005A
		opword 0xB01D0320
		opword 0x801D0140
		opword 0x5400062C
		opword 0x901D0140
		opword 0x801D0140
		opword 0x64001000
		opword 0x901D0140
		opword 0x801D0000
		opword 0x540005AD
		opword 0x41820014
		opword 0x807D0104
		opword 0x389D002C
		opword 0x38A00001
		bl animPoseSetAnim
		opword 0x3B600000
		opword 0x3BDD0230
		opword 0x7F7CDB78
		opword 0x809E007C
		opword 0x2C040000
		opword 0x41820030
		opword 0xC03D008C
		opword 0x38600000
		opword 0xC05D0090
		opword 0x38A0000B
		opword 0xC07D0094
		opword 0x38C0FFFF
		opword 0x38E00000
		bl itemEntry
		opword 0x38800100
		bl itemFlagOn
		opword 0x939E007C
		opword 0x3B7B0001
		opword 0x3BDE0004
		opword 0x2C1B0008
		opword 0x4180FFBC
		opword 0x4800005C
		opword 0x2C1C0004
		opword 0x40820054
		opword 0x801D0000
		opword 0x5400056B
		opword 0x4182000C
		opword 0x38000000
		opword 0x901D0108
		opword 0x801D0140
		opword 0x38600BB8
		opword 0x64001000
		opword 0x901D0140
		bl marioSetMutekiTime
		opword 0x38600BB8
		bl sysMsec2Frame
		opword 0xB07B02C0
		opword 0x801D0000
		opword 0x540005AD
		opword 0x41820014
		opword 0x807D0104
		opword 0x389D002C
		opword 0x38A00001
		bl animPoseSetAnim
		opword 0xBB410008
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void _npcDead(NpcEntry* npc, s32 reason) {
    npc->interruptFlags |= 0x10;
    npc->jumpFlags |= 4;
    npc->koopaEncounterType = reason;
    if (npc->flags & 4) {
        fbatGetPointer()->deadInfo[0].mask |= 1 << npc->setupIndex;
    }
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void _npcGroupDead(NpcEntry* entry, s32 reason) {
#ifdef NONMATCHING
    int i;
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xBF010010
		opword 0x7C7C1B78
		opword 0x7C9D2378
		opword 0x83E30328
		opword 0x281F0000
		opword 0x4182021C
		opword 0x83DF0328
		opword 0x281E0000
		opword 0x41820104
		opword 0x833E0328
		opword 0x28190000
		opword 0x4182004C
		opword 0x80790328
		opword 0x28030000
		opword 0x41820008
		bl _npcGroupDead
		opword 0x3B400000
		opword 0x7F3BCB78
		opword 0x807B0330
		opword 0x28030000
		opword 0x4182000C
		opword 0x7FA4EB78
		bl _npcDead
		opword 0x3B5A0001
		opword 0x3B7B0004
		opword 0x2C1A0004
		opword 0x4180FFE0
		opword 0x7F23CB78
		opword 0x7FA4EB78
		bl _npcDead
		opword 0x7FD9F378
		opword 0x3B400000
		opword 0x3B600001
		opword 0x83190330
		opword 0x28180000
		opword 0x41820044
		opword 0x80180140
		opword 0x60000010
		opword 0x90180140
		opword 0x801801D4
		opword 0x60000004
		opword 0x901801D4
		opword 0xB3B8031C
		opword 0x80180000
		opword 0x5400077B
		opword 0x4182001C
		bl fbatGetPointer
		opword 0x88180314
		opword 0x8083005C
		opword 0x7F600030
		opword 0x7C800378
		opword 0x9003005C
		opword 0x3B5A0001
		opword 0x3B390004
		opword 0x2C1A0004
		opword 0x4180FFA8
		opword 0x801E0140
		opword 0x60000010
		opword 0x901E0140
		opword 0x801E01D4
		opword 0x60000004
		opword 0x901E01D4
		opword 0xB3BE031C
		opword 0x801E0000
		opword 0x5400077B
		opword 0x41820020
		bl fbatGetPointer
		opword 0x881E0314
		opword 0x38800001
		opword 0x80A3005C
		opword 0x7C800030
		opword 0x7CA00378
		opword 0x9003005C
		opword 0x38000002
		opword 0x7FE6FB78
		opword 0x38A00000
		opword 0x7C0903A6
		opword 0x80E60330
		opword 0x28070000
		opword 0x4182004C
		opword 0x80070140
		opword 0x60000010
		opword 0x90070140
		opword 0x800701D4
		opword 0x60000004
		opword 0x900701D4
		opword 0xB3A7031C
		opword 0x80070000
		opword 0x5400077B
		opword 0x41820024
		lwz r4, gp(r13)
		opword 0x38600001
		opword 0x88070314
		opword 0x80840168
		opword 0x7C600030
		opword 0x8064005C
		opword 0x7C600378
		opword 0x9004005C
		opword 0x80E60334
		opword 0x28070000
		opword 0x4182004C
		opword 0x80070140
		opword 0x60000010
		opword 0x90070140
		opword 0x800701D4
		opword 0x60000004
		opword 0x900701D4
		opword 0xB3A7031C
		opword 0x80070000
		opword 0x5400077B
		opword 0x41820024
		lwz r4, gp(r13)
		opword 0x38600001
		opword 0x88070314
		opword 0x80840168
		opword 0x7C600030
		opword 0x8064005C
		opword 0x7C600378
		opword 0x9004005C
		opword 0x38C60008
		opword 0x38A50001
		opword 0x4200FF50
		opword 0x801F0140
		opword 0x60000010
		opword 0x901F0140
		opword 0x801F01D4
		opword 0x60000004
		opword 0x901F01D4
		opword 0xB3BF031C
		opword 0x801F0000
		opword 0x5400077B
		opword 0x41820024
		lwz r4, gp(r13)
		opword 0x38600001
		opword 0x881F0314
		opword 0x80840168
		opword 0x7C600030
		opword 0x8064005C
		opword 0x7C600378
		opword 0x9004005C
		opword 0x38000002
		opword 0x7F85E378
		opword 0x38E00000
		opword 0x7C0903A6
		opword 0x80C50330
		opword 0x28060000
		opword 0x4182004C
		opword 0x80060140
		opword 0x60000010
		opword 0x90060140
		opword 0x800601D4
		opword 0x60000004
		opword 0x900601D4
		opword 0xB3A6031C
		opword 0x80060000
		opword 0x5400077B
		opword 0x41820024
		lwz r4, gp(r13)
		opword 0x38600001
		opword 0x88060314
		opword 0x80840168
		opword 0x7C600030
		opword 0x8064005C
		opword 0x7C600378
		opword 0x9004005C
		opword 0x80C50334
		opword 0x28060000
		opword 0x4182004C
		opword 0x80060140
		opword 0x60000010
		opword 0x90060140
		opword 0x800601D4
		opword 0x60000004
		opword 0x900601D4
		opword 0xB3A6031C
		opword 0x80060000
		opword 0x5400077B
		opword 0x41820024
		lwz r4, gp(r13)
		opword 0x38600001
		opword 0x88060314
		opword 0x80840168
		opword 0x7C600030
		opword 0x8064005C
		opword 0x7C600378
		opword 0x9004005C
		opword 0x38A50008
		opword 0x38E70001
		opword 0x4200FF50
		opword 0x801C0140
		opword 0x60000010
		opword 0x901C0140
		opword 0x801C01D4
		opword 0x60000004
		opword 0x901C01D4
		opword 0xB3BC031C
		opword 0x801C0000
		opword 0x5400077B
		opword 0x41820024
		lwz r4, gp(r13)
		opword 0x38600001
		opword 0x881C0314
		opword 0x80840168
		opword 0x7C600030
		opword 0x8064005C
		opword 0x7C600378
		opword 0x9004005C
		opword 0xBB010010
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
    if (entry->next) {
        _npcGroupDead(entry->next, reason);
    }
    for (i = 0; i < 4; i++) {
        if (entry->slaves[i]) {
            _npcDead(entry->slaves[i], reason);
        }
    }
    _npcDead(entry, reason);
}

#endif
#ifndef NONMATCHING
#pragma dont_inline on
#endif
void npcGroupDead(NpcEntry* entry, BOOL reason) {
    if (entry->master) {
        entry = entry->master;
    }
    while (entry->prev) {
        entry = entry->prev;
    }
    _npcGroupDead(entry, reason);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

NpcEntry* fbatNpcTalkCheck(void) {
    NpcWork* wp = npcGetWorkPtrInline();
    if (wp->talkTarget && marioChkTalkable()) {
        return wp->talkTarget;
    }
    return NULL;
}

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void fbatHitCheckAll(void) {
    fbatHitCheck(0x13f1, NULL);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifdef NONMATCHING
#define FH(p, off, T) (*(T*)((u8*)(p) + (off)))
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void* fbatHitCheck(u32 flags, void* a1) {
	char _af_pad[124];
	asm volatile {
		lwz r5, gp(r13)
		lis r6, vec3_802c2f78@ha
		opword 0x7C731B78
		opword 0x7C942378
		opword 0x80050014
		addi r29, r6, vec3_802c2f78@l
		opword 0x3B000000
		opword 0x3AE00000
		opword 0x2C000000
		la r30, work(r13)
		opword 0x41820008
		opword 0x3BDE0014
		bl marioGetPtr
		lwz r0, _af_pad+44(r1)
		opword 0x38800000
		lfs f0, float_1000_80419bc8(r2)
		opword 0x567904A5
		opword 0x5400003C
		opword 0x90810028
		opword 0x7C7F1B78
		opword 0xD0010030
		opword 0x90010034
		opword 0x4182000C
		opword 0x60000001
		opword 0x90010034
		opword 0x566006B7
		opword 0x41820AD4
		opword 0x567A06F7
		opword 0x82BE0004
		opword 0x82FE000C
		opword 0x41820010
		opword 0xA81F004C
		opword 0x2C000000
		opword 0x41810AB8
		bl marioGetPtr
		lwz r5, gp(r13)
		opword 0x7C761B78
		la r3, work(r13)
		opword 0x80050014
		opword 0x2C000000
		opword 0x41820008
		opword 0x38630014
		opword 0x80960000
		opword 0x74808200
		opword 0x4182000C
		opword 0x38000000
		opword 0x480000A4
		opword 0x80030008
		opword 0x540007FF
		opword 0x40820014
		opword 0x7080000A
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000088
		opword 0x80050164
		opword 0x2C000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000074
		bl seqGetSeq
		opword 0x2C030002
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000060
		opword 0xA016002E
		opword 0x28000019
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800004C
		bl vivianGetStatus
		opword 0x2C030000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000038
		opword 0xA016002E
		opword 0x2800001F
		opword 0x4182000C
		opword 0x28000020
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800001C
		opword 0xA0170320
		opword 0x28000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x418209DC
		opword 0x567C04E6
		opword 0x567B06B4
		opword 0x3AC00000
		opword 0x480009C4
		opword 0x28170000
		opword 0x418209B4
		opword 0x80770000
		opword 0x546007BD
		opword 0x418209A8
		opword 0x281C0000
		opword 0x41820010
		opword 0x54600739
		opword 0x41820998
		opword 0x4800000C
		opword 0x54600739
		opword 0x4082098C
		opword 0x28190000
		opword 0x41820010
		opword 0x80170004
		opword 0x540007FF
		opword 0x41820978
		opword 0x546006B5
		opword 0x40820970
		opword 0x801701D4
		opword 0x5400077B
		opword 0x40820964
		opword 0x54600109
		opword 0x4082095C
		opword 0xC0570090
		opword 0xC0170150
		opword 0xC03F0090
		opword 0xEC02002A
		opword 0xFC010040
		opword 0x4C411382
		opword 0x41820940
		opword 0xC01F01B8
		opword 0xEC01002A
		opword 0xFC001040
		opword 0x4C401382
		opword 0x4182092C
		opword 0xC03F0094
		opword 0xC0170094
		opword 0xC05F008C
		opword 0xEC610028
		opword 0xC037008C
		lfs f0, float_0_80419b9c(r2)
		opword 0xEC420828
		opword 0xEC2300F2
		opword 0xEC8208BA
		opword 0xFC040040
		opword 0x4081004C
		opword 0xFC202034
		opword 0xC87D01C0
		opword 0xC85D01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC010032
		opword 0xFC840032
		opword 0xFC802018
		opword 0x48000088
		opword 0xC81D01D0
		opword 0xFC040040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0810008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0xD0810024
		lfs f2, float_0p5_80419ba0(r2)
		opword 0xC03F01B4
		opword 0xC017014C
		opword 0xEC01002A
		opword 0xEC020032
		opword 0xFC040040
		opword 0x41810814
		opword 0xC0010030
		opword 0xFC040040
		opword 0x4C411382
		opword 0x41820804
		opword 0x281A0000
		opword 0x418203A0
		opword 0x801701D4
		opword 0x540003DF
		opword 0x40820394
		opword 0xA81F004C
		opword 0x2C000000
		opword 0x41810388
		opword 0x801702F8
		opword 0x2C000000
		opword 0x4182003C
		opword 0x8077011C
		bl evtGetPtrID
		opword 0x28030000
		opword 0x41820020
		opword 0x8077011C
		bl evtGetPtrID
		opword 0x88030010
		opword 0x20000005
		opword 0x7C000034
		opword 0x5400D97E
		opword 0x48000008
		opword 0x38000000
		opword 0x2C000000
		opword 0x4182011C
		opword 0x80170000
		opword 0x54000085
		opword 0x40820794
		opword 0xC0010024
		opword 0x3CA00001
		opword 0x28190000
		opword 0x90A10028
		opword 0x7EF8BB78
		opword 0xD0010030
		opword 0x4082031C
		lwz r3, gp(r13)
		opword 0x38800000
		opword 0x3C000020
		opword 0x80630168
		opword 0x90830550
		opword 0x90A30554
		opword 0x9083055C
		opword 0x80830554
		opword 0x7C040000
		opword 0x41820088
		opword 0x40800044
		opword 0x3C000008
		opword 0x7C040000
		opword 0x41820078
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C040000
		opword 0x41820068
		opword 0x4080009C
		opword 0x3C000002
		opword 0x7C040000
		opword 0x41820058
		opword 0x4800008C
		opword 0x3C000010
		opword 0x7C040000
		opword 0x41820048
		opword 0x4800007C
		opword 0x3C000100
		opword 0x7C040000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C040000
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C040000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C040000
		opword 0x41820024
		opword 0x4800003C
		opword 0x389D01E0
		opword 0x38000002
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b90(r2)
		opword 0x9003056C
		opword 0x48000254
		opword 0x389D01F0
		opword 0x38000001
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b94(r2)
		opword 0x9003056C
		opword 0x48000238
		opword 0x38000000
		opword 0x90030558
		opword 0x4800022C
		opword 0x38600140
		bl pouchEquipCheckBadge
		opword 0x2C030000
		opword 0x41820110
		opword 0xC0010024
		opword 0x3CA00001
		opword 0x28190000
		opword 0x90A10028
		opword 0x7EF8BB78
		opword 0xD0010030
		opword 0x40820200
		lwz r3, gp(r13)
		opword 0x38800000
		opword 0x3C000020
		opword 0x80630168
		opword 0x90830550
		opword 0x90A30554
		opword 0x9083055C
		opword 0x80830554
		opword 0x7C040000
		opword 0x41820088
		opword 0x40800044
		opword 0x3C000008
		opword 0x7C040000
		opword 0x41820078
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C040000
		opword 0x41820068
		opword 0x4080009C
		opword 0x3C000002
		opword 0x7C040000
		opword 0x41820058
		opword 0x4800008C
		opword 0x3C000010
		opword 0x7C040000
		opword 0x41820048
		opword 0x4800007C
		opword 0x3C000100
		opword 0x7C040000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C040000
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C040000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C040000
		opword 0x41820024
		opword 0x4800003C
		opword 0x389D01E0
		opword 0x38000002
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b90(r2)
		opword 0x9003056C
		opword 0x48000138
		opword 0x389D01F0
		opword 0x38000001
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b94(r2)
		opword 0x9003056C
		opword 0x4800011C
		opword 0x38000000
		opword 0x90030558
		opword 0x48000110
		opword 0xC0010024
		opword 0x3CA01000
		opword 0x28190000
		opword 0x90A10028
		opword 0x7EF8BB78
		opword 0xD0010030
		opword 0x408200EC
		lwz r3, gp(r13)
		opword 0x38800000
		opword 0x3C000020
		opword 0x80630168
		opword 0x90830550
		opword 0x90A30554
		opword 0x9083055C
		opword 0x80830554
		opword 0x7C040000
		opword 0x41820084
		opword 0x40800044
		opword 0x3C000008
		opword 0x7C040000
		opword 0x41820074
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C040000
		opword 0x41820064
		opword 0x40800098
		opword 0x3C000002
		opword 0x7C040000
		opword 0x41820054
		opword 0x48000088
		opword 0x3C000010
		opword 0x7C040000
		opword 0x41820044
		opword 0x48000078
		opword 0x3C000100
		opword 0x7C040000
		opword 0x41820034
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C040000
		opword 0x41820024
		opword 0x40800058
		opword 0x3C000040
		opword 0x7C040000
		opword 0x41820014
		opword 0x48000048
		opword 0x7C042800
		opword 0x41820024
		opword 0x4800003C
		opword 0x389D01E0
		opword 0x38000002
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b90(r2)
		opword 0x9003056C
		opword 0x48000028
		opword 0x389D01F0
		opword 0x38000001
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b94(r2)
		opword 0x9003056C
		opword 0x4800000C
		opword 0x38000000
		opword 0x90030558
		opword 0x801702F8
		opword 0x9001002C
		opword 0x281B0000
		opword 0x41820458
		opword 0x807F0000
		opword 0x5460039D
		opword 0x41820330
		opword 0x546003DF
		opword 0x40820328
		opword 0x80170000
		opword 0x54000085
		opword 0x4082031C
		opword 0xC0010024
		opword 0x7EF8BB78
		opword 0xD0010030
		bl marioGetJabaraState
		opword 0x2C030006
		opword 0x40820100
		opword 0x3CA00002
		opword 0x28190000
		opword 0x90A10028
		opword 0x40820410
		lwz r3, gp(r13)
		opword 0x38800000
		opword 0x3C000020
		opword 0x80630168
		opword 0x90830550
		opword 0x90A30554
		opword 0x9083055C
		opword 0x80830554
		opword 0x7C040000
		opword 0x41820084
		opword 0x40800040
		opword 0x3C000008
		opword 0x7C040000
		opword 0x41820074
		opword 0x40800020
		opword 0x3C000004
		opword 0x7C040000
		opword 0x41820064
		opword 0x40800098
		opword 0x7C042800
		opword 0x41820058
		opword 0x4800008C
		opword 0x3C000010
		opword 0x7C040000
		opword 0x41820048
		opword 0x4800007C
		opword 0x3C000100
		opword 0x7C040000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C040000
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C040000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C040000
		opword 0x41820024
		opword 0x4800003C
		opword 0x389D01E0
		opword 0x38000002
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b90(r2)
		opword 0x9003056C
		opword 0x4800034C
		opword 0x389D01F0
		opword 0x38000001
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b94(r2)
		opword 0x9003056C
		opword 0x48000330
		opword 0x38000000
		opword 0x90030558
		opword 0x48000324
		opword 0xA01F002E
		opword 0x28000010
		opword 0x40820100
		opword 0x3CA00004
		opword 0x28190000
		opword 0x90A10028
		opword 0x40820308
		lwz r3, gp(r13)
		opword 0x38800000
		opword 0x3C000020
		opword 0x80630168
		opword 0x90830550
		opword 0x90A30554
		opword 0x9083055C
		opword 0x80830554
		opword 0x7C040000
		opword 0x41820084
		opword 0x40800040
		opword 0x3C000008
		opword 0x7C040000
		opword 0x41820074
		opword 0x40800020
		opword 0x7C042800
		opword 0x41820068
		opword 0x4080009C
		opword 0x3C000002
		opword 0x7C040000
		opword 0x41820058
		opword 0x4800008C
		opword 0x3C000010
		opword 0x7C040000
		opword 0x41820048
		opword 0x4800007C
		opword 0x3C000100
		opword 0x7C040000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C040000
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C040000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C040000
		opword 0x41820024
		opword 0x4800003C
		opword 0x389D01E0
		opword 0x38000002
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b90(r2)
		opword 0x9003056C
		opword 0x48000244
		opword 0x389D01F0
		opword 0x38000001
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b94(r2)
		opword 0x9003056C
		opword 0x48000228
		opword 0x38000000
		opword 0x90030558
		opword 0x4800021C
		opword 0x3CA00002
		opword 0x28190000
		opword 0x90A10028
		opword 0x4082020C
		lwz r3, gp(r13)
		opword 0x38800000
		opword 0x3C000020
		opword 0x80630168
		opword 0x90830550
		opword 0x90A30554
		opword 0x9083055C
		opword 0x80830554
		opword 0x7C040000
		opword 0x41820084
		opword 0x40800040
		opword 0x3C000008
		opword 0x7C040000
		opword 0x41820074
		opword 0x40800020
		opword 0x3C000004
		opword 0x7C040000
		opword 0x41820064
		opword 0x40800098
		opword 0x7C042800
		opword 0x41820058
		opword 0x4800008C
		opword 0x3C000010
		opword 0x7C040000
		opword 0x41820048
		opword 0x4800007C
		opword 0x3C000100
		opword 0x7C040000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C040000
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C040000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C040000
		opword 0x41820024
		opword 0x4800003C
		opword 0x389D01E0
		opword 0x38000002
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b90(r2)
		opword 0x9003056C
		opword 0x48000148
		opword 0x389D01F0
		opword 0x38000001
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b94(r2)
		opword 0x9003056C
		opword 0x4800012C
		opword 0x38000000
		opword 0x90030558
		opword 0x48000120
		bl marioGetJabaraState
		opword 0x2C030006
		opword 0x40820114
		opword 0x80170000
		opword 0x54000085
		opword 0x40820108
		opword 0xC0010024
		opword 0x3CA00002
		opword 0x28190000
		opword 0x90A10028
		opword 0x7EF8BB78
		opword 0xD0010030
		opword 0x408200EC
		lwz r3, gp(r13)
		opword 0x38800000
		opword 0x3C000020
		opword 0x80630168
		opword 0x90830550
		opword 0x90A30554
		opword 0x9083055C
		opword 0x80830554
		opword 0x7C040000
		opword 0x41820084
		opword 0x40800040
		opword 0x3C000008
		opword 0x7C040000
		opword 0x41820074
		opword 0x40800020
		opword 0x3C000004
		opword 0x7C040000
		opword 0x41820064
		opword 0x40800098
		opword 0x7C042800
		opword 0x41820058
		opword 0x4800008C
		opword 0x3C000010
		opword 0x7C040000
		opword 0x41820048
		opword 0x4800007C
		opword 0x3C000100
		opword 0x7C040000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C040000
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C040000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C040000
		opword 0x41820024
		opword 0x4800003C
		opword 0x389D01E0
		opword 0x38000002
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b90(r2)
		opword 0x9003056C
		opword 0x48000028
		opword 0x389D01F0
		opword 0x38000001
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b94(r2)
		opword 0x9003056C
		opword 0x4800000C
		opword 0x38000000
		opword 0x90030558
		opword 0x3AD60001
		opword 0x3AF70340
		opword 0x7C16A800
		opword 0x4180F63C
		opword 0x56600673
		opword 0x41820648
		opword 0x4800063C
		opword 0x566006F7
		opword 0x41820010
		opword 0xA81F004C
		opword 0x2C000000
		opword 0x41810630
		bl marioGetPtr
		lwz r5, gp(r13)
		opword 0x7C761B78
		la r3, work(r13)
		opword 0x80050014
		opword 0x2C000000
		opword 0x41820008
		opword 0x38630014
		opword 0x80960000
		opword 0x74808200
		opword 0x4182000C
		opword 0x38000000
		opword 0x480000A4
		opword 0x80030008
		opword 0x540007FF
		opword 0x40820014
		opword 0x7080000A
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000088
		opword 0x80050164
		opword 0x2C000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000074
		bl seqGetSeq
		opword 0x2C030002
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000060
		opword 0xA016002E
		opword 0x28000019
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800004C
		bl vivianGetStatus
		opword 0x2C030000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000038
		opword 0xA016002E
		opword 0x2800001F
		opword 0x4182000C
		opword 0x28000020
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800001C
		opword 0xA0170320
		opword 0x28000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x41820554
		opword 0x566007FF
		opword 0x41820354
		opword 0xA01F002E
		opword 0x28000012
		opword 0x40820540
		lfs f1, float_1p5_80419bcc(r2)
		opword 0x38600004
		opword 0xC01F01B4
		opword 0xEFE10032
		bl camGetPtr
		opword 0xC03F01A8
		lfs f0, float_90_80419bd0(r2)
		opword 0xC0430114
		opword 0xEC010028
		opword 0xEC20102A
		bl reviseAngle
		opword 0xFFA00890
		bl marioGetPtr
		opword 0x7C761B78
		bl marioAnimeId
		opword 0x5460103A
		opword 0x7C760214
		opword 0x80630228
		bl animPoseGetAnimPosePtr
		opword 0x80160048
		opword 0x2C000014
		opword 0x40810008
		opword 0x3800000A
		opword 0x6C038000
		opword 0x3C004330
		opword 0x9061006C
		opword 0xC83D01D8
		opword 0x90010068
		opword 0xC8010068
		opword 0xEFC00828
		bl marioGetPtr
		lfs f0, float_0_80419b9c(r2)
		opword 0x7C761B78
		opword 0x819D0024
		opword 0x817D0028
		opword 0xFC1E0040
		opword 0x815D002C
		opword 0x813D0030
		opword 0x811D0034
		opword 0x80FD0038
		opword 0x80DD003C
		opword 0x80BD0040
		opword 0x809D0044
		opword 0x807D0048
		opword 0x801D004C
		opword 0x91810038
		opword 0x9161003C
		opword 0x91410040
		opword 0x91210044
		opword 0x91010048
		opword 0x90E1004C
		opword 0x90C10050
		opword 0x90A10054
		opword 0x90810058
		opword 0x9061005C
		opword 0x90010060
		opword 0x40800008
		opword 0xFFC00090
		lfs f0, float_11_80419bbc(r2)
		opword 0xFC1E0040
		opword 0x4C411382
		opword 0x40820008
		lfs f30, float_10_80419bb8(r2)
		opword 0xFC20E890
		opword 0x38610014
		opword 0x38810018
		bl sincosf
		opword 0xFC00F01E
		opword 0x3C004330
		opword 0x38A10038
		opword 0x90010078
		opword 0xC83D01D8
		opword 0x3861001C
		opword 0xD8010070
		opword 0x38810020
		opword 0x80010074
		opword 0x5400103A
		opword 0x7C05002E
		opword 0x6C008000
		opword 0x9001007C
		opword 0xC8010078
		opword 0xEC200828
		bl sincosf
		opword 0xC0210014
		opword 0x567A04E6
		opword 0xC0010018
		opword 0x3B600000
		opword 0xECA107F2
		opword 0xC0C1001C
		opword 0xC096008C
		opword 0xEC6007F2
		opword 0xC0560094
		opword 0xC0210020
		opword 0xC0160090
		opword 0xEFC6217A
		opword 0xEFA610FA
		opword 0x82FE000C
		opword 0xEFFF007A
		opword 0x480001B0
		opword 0x28170000
		opword 0x418201A0
		opword 0x80770000
		opword 0x546007BD
		opword 0x41820194
		opword 0x281A0000
		opword 0x41820010
		opword 0x54600739
		opword 0x41820184
		opword 0x4800000C
		opword 0x54600739
		opword 0x40820178
		opword 0x28190000
		opword 0x41820010
		opword 0x80170004
		opword 0x540007BD
		opword 0x41820164
		opword 0x54600085
		opword 0x4082015C
		opword 0x546006B5
		opword 0x40820154
		opword 0x54600109
		opword 0x4082014C
		opword 0x801701D4
		opword 0x5400077B
		opword 0x40820140
		opword 0xFC20F090
		lfs f4, float_12_80419bc0(r2)
		opword 0xFC40F890
		opword 0x7EE3BB78
		opword 0xFC60E890
		opword 0x38810024
		bl _npcHitCheckSphere
		opword 0x28030000
		opword 0x4182011C
		opword 0xC0210024
		opword 0xC0010030
		opword 0xFC010040
		opword 0x4C411382
		opword 0x41820108
		opword 0x3CA00010
		opword 0x28190000
		opword 0xD0210030
		opword 0x7EF8BB78
		opword 0x90A10028
		opword 0x408202FC
		lwz r4, gp(r13)
		opword 0x38600000
		opword 0x3C000020
		opword 0x80840168
		opword 0x90640550
		opword 0x90A40554
		opword 0x9064055C
		opword 0x80640554
		opword 0x7C030000
		opword 0x41820084
		opword 0x40800040
		opword 0x3C000008
		opword 0x7C030000
		opword 0x41820074
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C030000
		opword 0x41820064
		opword 0x40800098
		opword 0x3C000002
		opword 0x7C030000
		opword 0x41820054
		opword 0x48000088
		opword 0x7C032800
		opword 0x41820048
		opword 0x4800007C
		opword 0x3C000100
		opword 0x7C030000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C030000
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C030000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C030000
		opword 0x41820024
		opword 0x4800003C
		opword 0x387D01E0
		opword 0x38000002
		opword 0x90640568
		opword 0x90040558
		lwz r0, dat_80419b90(r2)
		opword 0x9004056C
		opword 0x48000238
		opword 0x387D01F0
		opword 0x38000001
		opword 0x90640568
		opword 0x90040558
		lwz r0, dat_80419b94(r2)
		opword 0x9004056C
		opword 0x4800021C
		opword 0x38000000
		opword 0x90040558
		opword 0x48000210
		opword 0x3B7B0001
		opword 0x3AF70340
		opword 0x7C1BA800
		opword 0x4180FE50
		opword 0x480001FC
		lfs f1, float_1p5_80419bcc(r2)
		opword 0x38600004
		opword 0xC01F01B4
		opword 0xEFC10032
		bl camGetPtr
		opword 0xC03F01A8
		lfs f0, float_90_80419bd0(r2)
		opword 0xC0430114
		opword 0xEC010028
		opword 0xEC20102A
		bl reviseAngle
		opword 0xFFE00890
		opword 0x82FE000C
		opword 0x567604E6
		opword 0x3B400000
		opword 0x480001A8
		opword 0x28170000
		opword 0x41820198
		opword 0x80770000
		opword 0x546007BD
		opword 0x4182018C
		opword 0x28160000
		opword 0x41820010
		opword 0x54600739
		opword 0x4182017C
		opword 0x4800000C
		opword 0x54600739
		opword 0x40820170
		opword 0x28190000
		opword 0x41820010
		opword 0x80170004
		opword 0x540007BD
		opword 0x4182015C
		opword 0x54600085
		opword 0x40820154
		opword 0x546006B5
		opword 0x4082014C
		opword 0x801701D4
		opword 0x5400077B
		opword 0x40820140
		opword 0x54600109
		opword 0x40820138
		opword 0xFC20F090
		opword 0x7EE3BB78
		opword 0xFC40F890
		opword 0x38810024
		bl _npcHitCheckHammerAllMotion
		opword 0x28030000
		opword 0x4182011C
		opword 0xC0210024
		opword 0xC0010030
		opword 0xFC010040
		opword 0x4C411382
		opword 0x41820108
		opword 0x3CA00010
		opword 0x28190000
		opword 0xD0210030
		opword 0x7EF8BB78
		opword 0x90A10028
		opword 0x4082010C
		lwz r4, gp(r13)
		opword 0x38600000
		opword 0x3C000020
		opword 0x80840168
		opword 0x90640550
		opword 0x90A40554
		opword 0x9064055C
		opword 0x80640554
		opword 0x7C030000
		opword 0x41820084
		opword 0x40800040
		opword 0x3C000008
		opword 0x7C030000
		opword 0x41820074
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C030000
		opword 0x41820064
		opword 0x40800098
		opword 0x3C000002
		opword 0x7C030000
		opword 0x41820054
		opword 0x48000088
		opword 0x7C032800
		opword 0x41820048
		opword 0x4800007C
		opword 0x3C000100
		opword 0x7C030000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C030000
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C030000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C030000
		opword 0x41820024
		opword 0x4800003C
		opword 0x387D01E0
		opword 0x38000002
		opword 0x90640568
		opword 0x90040558
		lwz r0, dat_80419b90(r2)
		opword 0x9004056C
		opword 0x48000048
		opword 0x387D01F0
		opword 0x38000001
		opword 0x90640568
		opword 0x90040558
		lwz r0, dat_80419b94(r2)
		opword 0x9004056C
		opword 0x4800002C
		opword 0x38000000
		opword 0x90040558
		opword 0x48000020
		opword 0x3B5A0001
		opword 0x3AF70340
		opword 0x7C1AA800
		opword 0x4180FE58
		opword 0x4800000C
		opword 0x28180000
		opword 0x4182F9C4
		opword 0x56600631
		opword 0x41820568
		opword 0x4800055C
		opword 0x566006F7
		opword 0x41820010
		opword 0xA81F004C
		opword 0x2C000000
		opword 0x41810550
		bl marioGetPtr
		lwz r5, gp(r13)
		opword 0x7C761B78
		la r3, work(r13)
		opword 0x80050014
		opword 0x2C000000
		opword 0x41820008
		opword 0x38630014
		opword 0x80960000
		opword 0x74808200
		opword 0x4182000C
		opword 0x38000000
		opword 0x480000A4
		opword 0x80030008
		opword 0x540007FF
		opword 0x40820014
		opword 0x7080000A
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000088
		opword 0x80050164
		opword 0x2C000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000074
		bl seqGetSeq
		opword 0x2C030002
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000060
		opword 0xA016002E
		opword 0x28000019
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800004C
		bl vivianGetStatus
		opword 0x2C030000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000038
		opword 0xA016002E
		opword 0x2800001F
		opword 0x4182000C
		opword 0x28000020
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800001C
		opword 0xA0170320
		opword 0x28000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x41820474
		opword 0x566007FF
		opword 0x41820254
		opword 0xA01F002E
		opword 0x28000013
		opword 0x40820460
		bl marioGetAngleKaitenHammer
		opword 0xFFA00890
		lfs f0, float_0_80419b9c(r2)
		opword 0xFC1D0040
		opword 0x4180044C
		lfs f1, float_1p5_80419bcc(r2)
		opword 0xC01F01B4
		opword 0xEFC10032
		bl marioGetPtr
		opword 0xFC20E890
		opword 0x7C771B78
		opword 0x3861000C
		opword 0x38810010
		bl sincosf
		opword 0xC021000C
		opword 0x567604E6
		opword 0xC017008C
		opword 0x3B400000
		opword 0xC0610010
		opword 0xC0570094
		opword 0xEFA107BA
		lfs f1, float_15_80419bc4(r2)
		opword 0xC0170090
		opword 0xEFE317BA
		opword 0x82FE000C
		opword 0xEFC1002A
		opword 0x480001D0
		opword 0x28170000
		opword 0x418201C0
		opword 0x80770000
		opword 0x546007BD
		opword 0x418201B4
		opword 0x28160000
		opword 0x41820010
		opword 0x54600739
		opword 0x418201A4
		opword 0x4800000C
		opword 0x54600739
		opword 0x40820198
		opword 0x28190000
		opword 0x41820010
		opword 0x80170004
		opword 0x540007BD
		opword 0x41820184
		opword 0x54600085
		opword 0x4082017C
		opword 0x546006B5
		opword 0x40820174
		opword 0x801701D4
		opword 0x5400077B
		opword 0x40820168
		opword 0x54600109
		opword 0x40820160
		opword 0xFC20E890
		lfs f4, float_12_80419bc0(r2)
		opword 0xFC40F090
		opword 0x7EE3BB78
		opword 0xFC60F890
		opword 0x38810024
		bl _npcHitCheckSphere
		opword 0x28030000
		opword 0x4182013C
		opword 0xC0210024
		opword 0xC0010030
		opword 0xFC010040
		opword 0x4C411382
		opword 0x41820128
		opword 0xD0210030
		opword 0x7EF8BB78
		bl pouchGetHammerLv
		opword 0x2C030003
		opword 0x40800010
		opword 0x3C000020
		opword 0x90010028
		opword 0x4800000C
		opword 0x3C000040
		opword 0x90010028
		opword 0x28190000
		opword 0x40820324
		lwz r3, gp(r13)
		opword 0x38800000
		opword 0x80A10028
		opword 0x3C000020
		opword 0x80630168
		opword 0x90830550
		opword 0x90A30554
		opword 0x9083055C
		opword 0x80830554
		opword 0x7C040000
		opword 0x41820088
		opword 0x40800044
		opword 0x3C000008
		opword 0x7C040000
		opword 0x41820078
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C040000
		opword 0x41820068
		opword 0x4080009C
		opword 0x3C000002
		opword 0x7C040000
		opword 0x41820058
		opword 0x4800008C
		opword 0x3C000010
		opword 0x7C040000
		opword 0x41820048
		opword 0x4800007C
		opword 0x3C000100
		opword 0x7C040000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C040000
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C040000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C040000
		opword 0x41820024
		opword 0x4800003C
		opword 0x389D01E0
		opword 0x38000002
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b90(r2)
		opword 0x9003056C
		opword 0x48000258
		opword 0x389D01F0
		opword 0x38000001
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b94(r2)
		opword 0x9003056C
		opword 0x4800023C
		opword 0x38000000
		opword 0x90030558
		opword 0x48000230
		opword 0x3B5A0001
		opword 0x3AF70340
		opword 0x7C1AA800
		opword 0x4180FE30
		opword 0x4800021C
		lfs f1, float_1p5_80419bcc(r2)
		opword 0x38600004
		opword 0xC01F01B4
		opword 0xEFE10032
		bl camGetPtr
		opword 0xC03F01A8
		lfs f0, float_90_80419bd0(r2)
		opword 0xC0430114
		opword 0xEC010028
		opword 0xEC20102A
		bl reviseAngle
		opword 0xFFC00890
		opword 0x82FE000C
		opword 0x567604E6
		opword 0x3B400000
		opword 0x480001C8
		opword 0x28170000
		opword 0x418201B8
		opword 0x80770000
		opword 0x546007BD
		opword 0x418201AC
		opword 0x28160000
		opword 0x41820010
		opword 0x54600739
		opword 0x4182019C
		opword 0x4800000C
		opword 0x54600739
		opword 0x40820190
		opword 0x28190000
		opword 0x41820010
		opword 0x80170004
		opword 0x540007BD
		opword 0x4182017C
		opword 0x54600085
		opword 0x40820174
		opword 0x546006B5
		opword 0x4082016C
		opword 0x801701D4
		opword 0x5400077B
		opword 0x40820160
		opword 0x54600109
		opword 0x40820158
		opword 0xFC20F890
		opword 0x7EE3BB78
		opword 0xFC40F090
		opword 0x38810024
		bl _npcHitCheckHammerAllMotion
		opword 0x28030000
		opword 0x4182013C
		opword 0xC0210024
		opword 0xC0010030
		opword 0xFC010040
		opword 0x4C411382
		opword 0x41820128
		opword 0xD0210030
		opword 0x7EF8BB78
		bl pouchGetHammerLv
		opword 0x2C030003
		opword 0x40800010
		opword 0x3C000020
		opword 0x90010028
		opword 0x4800000C
		opword 0x3C000040
		opword 0x90010028
		opword 0x28190000
		opword 0x40820114
		lwz r3, gp(r13)
		opword 0x38800000
		opword 0x80A10028
		opword 0x3C000020
		opword 0x80630168
		opword 0x90830550
		opword 0x90A30554
		opword 0x9083055C
		opword 0x80830554
		opword 0x7C040000
		opword 0x41820088
		opword 0x40800044
		opword 0x3C000008
		opword 0x7C040000
		opword 0x41820078
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C040000
		opword 0x41820068
		opword 0x4080009C
		opword 0x3C000002
		opword 0x7C040000
		opword 0x41820058
		opword 0x4800008C
		opword 0x3C000010
		opword 0x7C040000
		opword 0x41820048
		opword 0x4800007C
		opword 0x3C000100
		opword 0x7C040000
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C040000
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C040000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C040000
		opword 0x41820024
		opword 0x4800003C
		opword 0x389D01E0
		opword 0x38000002
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b90(r2)
		opword 0x9003056C
		opword 0x48000048
		opword 0x389D01F0
		opword 0x38000001
		opword 0x90830568
		opword 0x90030558
		lwz r0, dat_80419b94(r2)
		opword 0x9003056C
		opword 0x4800002C
		opword 0x38000000
		opword 0x90030558
		opword 0x48000020
		opword 0x3B5A0001
		opword 0x3AF70340
		opword 0x7C1AA800
		opword 0x4180FE38
		opword 0x4800000C
		opword 0x28180000
		opword 0x4182FAA4
		opword 0x566005EF
		opword 0x4182033C
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x7C7B1B78
		opword 0x48000324
		opword 0x566006F7
		opword 0x41820010
		opword 0xA81F004C
		opword 0x2C000000
		opword 0x41810318
		bl marioGetPtr
		lwz r5, gp(r13)
		opword 0x7C761B78
		la r3, work(r13)
		opword 0x80050014
		opword 0x2C000000
		opword 0x41820008
		opword 0x38630014
		opword 0x80960000
		opword 0x74808200
		opword 0x4182000C
		opword 0x38000000
		opword 0x480000A4
		opword 0x80030008
		opword 0x540007FF
		opword 0x40820014
		opword 0x7080000A
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000088
		opword 0x80050164
		opword 0x2C000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000074
		bl seqGetSeq
		opword 0x2C030002
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000060
		opword 0xA016002E
		opword 0x28000019
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800004C
		bl vivianGetStatus
		opword 0x2C030000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000038
		opword 0xA016002E
		opword 0x2800001F
		opword 0x4182000C
		opword 0x28000020
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800001C
		opword 0xA0170320
		opword 0x28000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x4182023C
		opword 0x567607FF
		opword 0x4182003C
		opword 0x281B0000
		opword 0x4182022C
		opword 0x881B0033
		opword 0x28000002
		opword 0x40820220
		opword 0x801B0000
		opword 0x540005EF
		opword 0x41820214
		opword 0x7F63DB78
		bl nokonokoGetStatus
		opword 0x2C030002
		opword 0x41800204
		opword 0x2C030005
		opword 0x418101FC
		opword 0x28160000
		opword 0x418201F4
		lfs f3, float_0p5_80419ba0(r2)
		opword 0x567604E6
		opword 0xC05B00F4
		opword 0x3B400000
		opword 0xC03B00F0
		opword 0xC01B005C
		fmuls f28, f3, f2
		opword 0xC3BB0058
		opword 0xEFC3007A
		opword 0xC3FB0060
		opword 0x82FE000C
		opword 0x480001B0
		opword 0x28170000
		opword 0x418201A0
		opword 0x80770000
		opword 0x546007BD
		opword 0x41820194
		opword 0x28160000
		opword 0x41820010
		opword 0x54600739
		opword 0x41820184
		opword 0x4800000C
		opword 0x54600739
		opword 0x40820178
		opword 0x28190000
		opword 0x41820010
		opword 0x80170004
		opword 0x5400077B
		opword 0x41820164
		opword 0x54600085
		opword 0x4082015C
		opword 0x546006B5
		opword 0x40820154
		opword 0x801701D4
		opword 0x5400077B
		opword 0x40820148
		opword 0x54600109
		opword 0x40820140
		opword 0xFC20E890
		opword 0x7EE3BB78
		opword 0xFC40F090
		opword 0x38810024
		opword 0xFC60F890
		opword 0xFC80E090
		bl _npcHitCheckSphere
		opword 0x28030000
		opword 0x4182011C
		opword 0xC0210024
		opword 0xC0010030
		opword 0xFC010040
		opword 0x4C411382
		opword 0x41820108
		opword 0x3CA00080
		opword 0x28190000
		opword 0xD0210030
		opword 0x7EF8BB78
		opword 0x90A10028
		opword 0x4082010C
		lwz r4, gp(r13)
		opword 0x38600000
		opword 0x3C000020
		opword 0x80840168
		opword 0x90640550
		opword 0x90A40554
		opword 0x9064055C
		opword 0x80640554
		opword 0x7C030000
		opword 0x41820084
		opword 0x40800044
		opword 0x3C000008
		opword 0x7C030000
		opword 0x41820074
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C030000
		opword 0x41820064
		opword 0x40800098
		opword 0x3C000002
		opword 0x7C030000
		opword 0x41820054
		opword 0x48000088
		opword 0x3C000010
		opword 0x7C030000
		opword 0x41820044
		opword 0x48000078
		opword 0x3C000100
		opword 0x7C030000
		opword 0x41820034
		opword 0x40800020
		opword 0x7C032800
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C030000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C030000
		opword 0x41820024
		opword 0x4800003C
		opword 0x387D01E0
		opword 0x38000002
		opword 0x90640568
		opword 0x90040558
		lwz r0, dat_80419b90(r2)
		opword 0x9004056C
		opword 0x48000048
		opword 0x387D01F0
		opword 0x38000001
		opword 0x90640568
		opword 0x90040558
		lwz r0, dat_80419b94(r2)
		opword 0x9004056C
		opword 0x4800002C
		opword 0x38000000
		opword 0x90040558
		opword 0x48000020
		opword 0x3B5A0001
		opword 0x3AF70340
		opword 0x7C1AA800
		opword 0x4180FE50
		opword 0x4800000C
		opword 0x28180000
		opword 0x4182FCDC
		opword 0x566005AD
		opword 0x41820310
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x7C7A1B78
		opword 0x480002F8
		opword 0x566006F7
		opword 0x41820010
		opword 0xA81F004C
		opword 0x2C000000
		opword 0x418102EC
		bl marioGetPtr
		lwz r5, gp(r13)
		opword 0x7C761B78
		la r3, work(r13)
		opword 0x80050014
		opword 0x2C000000
		opword 0x41820008
		opword 0x38630014
		opword 0x80960000
		opword 0x74808200
		opword 0x4182000C
		opword 0x38000000
		opword 0x480000A4
		opword 0x80030008
		opword 0x540007FF
		opword 0x40820014
		opword 0x7080000A
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000088
		opword 0x80050164
		opword 0x2C000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000074
		bl seqGetSeq
		opword 0x2C030002
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000060
		opword 0xA016002E
		opword 0x28000019
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800004C
		bl vivianGetStatus
		opword 0x2C030000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000038
		opword 0xA016002E
		opword 0x2800001F
		opword 0x4182000C
		opword 0x28000020
		opword 0x4082000C
		opword 0x38000000
		opword 0x4800001C
		opword 0xA0170320
		opword 0x28000000
		opword 0x4182000C
		opword 0x38000000
		opword 0x48000008
		opword 0x38000001
		opword 0x2C000000
		opword 0x41820210
		opword 0x566007FF
		opword 0x41820208
		opword 0x281A0000
		opword 0x41820200
		opword 0x881A0033
		opword 0x28000003
		opword 0x408201F4
		lwz r3, gp(r13)
		opword 0x80630168
		opword 0x8803054D
		opword 0x28000000
		opword 0x418201E0
		opword 0x82DE000C
		rlwinm r19, r19, 0, 19, 19
		opword 0x3AE00000
		opword 0x480001BC
		opword 0x28160000
		opword 0x418201AC
		opword 0x80760000
		opword 0x546007BD
		opword 0x418201A0
		opword 0x28130000
		opword 0x41820010
		opword 0x54600739
		opword 0x41820190
		opword 0x4800000C
		opword 0x54600739
		opword 0x40820184
		opword 0x28190000
		opword 0x41820010
		opword 0x80160004
		opword 0x54000739
		opword 0x41820170
		opword 0x54600085
		opword 0x40820168
		opword 0x546006B5
		opword 0x40820160
		opword 0x801601D4
		opword 0x5400077B
		opword 0x40820154
		opword 0x54600109
		opword 0x4082014C
		lfs f3, float_0p5_80419ba0(r2)
		opword 0x7EC3B378
		opword 0xC05A00F0
		opword 0x38810024
		opword 0xC01A005C
		opword 0xC03A0058
		opword 0xEC4300BA
		opword 0xC07A0060
		lfs f4, float_30_80419bd4(r2)
		bl _npcHitCheckSphere
		opword 0x28030000
		opword 0x4182011C
		opword 0xC0210024
		opword 0xC0010030
		opword 0xFC010040
		opword 0x4C411382
		opword 0x41820108
		opword 0x3CA00100
		opword 0x28190000
		opword 0xD0210030
		opword 0x7ED8B378
		opword 0x90A10028
		opword 0x4082010C
		lwz r4, gp(r13)
		opword 0x38600000
		opword 0x3C000020
		opword 0x80840168
		opword 0x90640550
		opword 0x90A40554
		opword 0x9064055C
		opword 0x80640554
		opword 0x7C030000
		opword 0x41820084
		opword 0x40800044
		opword 0x3C000008
		opword 0x7C030000
		opword 0x41820074
		opword 0x40800024
		opword 0x3C000004
		opword 0x7C030000
		opword 0x41820064
		opword 0x40800098
		opword 0x3C000002
		opword 0x7C030000
		opword 0x41820054
		opword 0x48000088
		opword 0x3C000010
		opword 0x7C030000
		opword 0x41820044
		opword 0x48000078
		opword 0x7C032800
		opword 0x41820038
		opword 0x40800024
		opword 0x3C000080
		opword 0x7C030000
		opword 0x41820028
		opword 0x4080005C
		opword 0x3C000040
		opword 0x7C030000
		opword 0x41820018
		opword 0x4800004C
		opword 0x3C001000
		opword 0x7C030000
		opword 0x41820024
		opword 0x4800003C
		opword 0x387D01E0
		opword 0x38000002
		opword 0x90640568
		opword 0x90040558
		lwz r0, dat_80419b90(r2)
		opword 0x9004056C
		opword 0x48000048
		opword 0x387D01F0
		opword 0x38000001
		opword 0x90640568
		opword 0x90040558
		lwz r0, dat_80419b94(r2)
		opword 0x9004056C
		opword 0x4800002C
		opword 0x38000000
		opword 0x90040558
		opword 0x48000020
		opword 0x3AF70001
		opword 0x3AD60340
		opword 0x7C17A800
		opword 0x4180FE44
		opword 0x4800000C
		opword 0x28180000
		opword 0x4182FD08
		opword 0x28140000
		opword 0x41820024
		opword 0x80610028
		opword 0x8001002C
		opword 0x90740000
		opword 0x80610030
		opword 0x90140004
		opword 0x80010034
		opword 0x90740008
		opword 0x9014000C
		opword 0x7F03C378
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
typedef struct FbatHitResult {
    u32 kind;   // 0x0
    s32 evtId;  // 0x4
    f32 dist;   // 0x8
    u32 bits; // 0xC
} FbatHitResult;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r) {
	asm volatile {
		opword 0x9421FFF0
		lis r5, vec3_802c2f78@ha
		addi r5, r5, vec3_802c2f78@l
		opword 0xC0C30090
		opword 0xC0A3008C
		opword 0xC0030094
		opword 0xFC023000
		opword 0xECA12828
		opword 0xEC223028
		opword 0xEC630028
		opword 0x41820040
		opword 0xFC023040
		opword 0x4C411382
		opword 0x40820020
		opword 0xC0030150
		opword 0xEC06002A
		opword 0xFC020040
		opword 0x4C401382
		opword 0x4082000C
		lfs f1, float_0_80419b9c(r2)
		opword 0x48000018
		opword 0xC0030150
		opword 0xEC06002A
		opword 0xFC020040
		opword 0x40810008
		opword 0xEC220028
		opword 0xEC210072
		lfs f0, float_0_80419b9c(r2)
		opword 0xEC25097A
		opword 0xECA308FA
		opword 0xFC050040
		opword 0x4081004C
		opword 0xFC202834
		opword 0xC86501C0
		opword 0xC84501C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC05103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC05103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC05103C
		opword 0xFC010032
		opword 0xFCA50032
		opword 0xFCA02818
		opword 0x48000088
		opword 0xC80501D0
		opword 0xFC050040
		opword 0x40800010
		lis r5, __float_nan@ha
		lfs f5, __float_nan@l(r5)
		opword 0x48000070
		opword 0xD0A10008
		opword 0x3C007F80
		opword 0x80C10008
		opword 0x54C50050
		opword 0x7C050000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C050000
		opword 0x41820020
		opword 0x48000034
		opword 0x54C0027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x54C0027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r5, __float_nan@ha
		lfs f5, __float_nan@l(r5)
		opword 0xD0A40000
		lfs f1, float_0p5_80419ba0(r2)
		opword 0xC003014C
		opword 0xC0440000
		opword 0xEC01203A
		opword 0xFC020040
		opword 0x40800008
		opword 0x48000008
		opword 0x38600000
		opword 0x38210010
	}
}
#pragma pop
#endif

#ifdef NONMATCHING
s32 vivianGetStatus(void);
s32 marioGetJabaraState(void);
s32 nokonokoGetStatus(PartyEntry* party);
f32 marioGetAngleKaitenHammer(void);
NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r);
NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle);

static inline BOOL fbat_canHit(NpcEntry* npc) {
    MarioWork* m = marioGetPtr();
    NpcWork* wp = npcGetWorkPtrInline();
    if (m->flags & 0x82000000) return FALSE;
    if (!(wp->flags & 1) && (m->flags & 0xA)) return FALSE;
    if (FH(gp, 0x164, s32)) return FALSE;
    if (seqGetSeq() != 2) return FALSE;
    if (FH(m, 0x2E, u16) == 0x19) return FALSE;
    if (vivianGetStatus()) return FALSE;
    if (FH(m, 0x2E, u16) == 0x1F || FH(m, 0x2E, u16) == 0x20) return FALSE;
    if (FH(npc, 0x320, u16)) return FALSE;
    return TRUE;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle) {
	char _af_pad[72];
	asm volatile {
		lfs f27, float_0_80419b9c(r2)
		lis r5, vec3_802c2f78@ha
		addi r30, r5, vec3_802c2f78@l
		opword 0xFF200890
		opword 0xFF401090
		lfs f29, float_11_80419bbc(r2)
		opword 0xFF80D890
		opword 0xCBDE01D8
		opword 0xFFE0D890
		lfs f22, float_0p5_80419ba0(r2)
		lfs f23, float_12_80419bc0(r2)
		opword 0x7C7C1B78
		lfs f24, float_1_80419bb4(r2)
		opword 0x7C9D2378
		la r26, _af_pad+20
		opword 0x3F604330
		opword 0x48000264
		opword 0xFEA0D890
		bl marioGetPtr
		opword 0x819E0024
		opword 0xFC1BE040
		opword 0x817E0028
		opword 0x7C7F1B78
		opword 0x815E002C
		opword 0x813E0030
		opword 0x811E0034
		opword 0x80FE0038
		opword 0x80DE003C
		opword 0x80BE0040
		opword 0x809E0044
		opword 0x807E0048
		opword 0x801E004C
		opword 0x9181001C
		opword 0x91610020
		opword 0x91410024
		opword 0x91210028
		opword 0x9101002C
		opword 0x90E10030
		opword 0x90C10034
		opword 0x90A10038
		opword 0x9081003C
		opword 0x90610040
		opword 0x90010044
		opword 0x40800008
		opword 0xFEA0E090
		opword 0xFC15E840
		opword 0x4C411382
		opword 0x40820008
		lfs f21, float_10_80419bb8(r2)
		opword 0xFC20D090
		opword 0x3861000C
		opword 0x38810010
		bl sincosf
		opword 0xFC00A81E
		opword 0x93610050
		opword 0x38610014
		opword 0x38810018
		opword 0xD8010048
		opword 0x8001004C
		opword 0x5400103A
		opword 0x7C1A002E
		opword 0x6C008000
		opword 0x90010054
		opword 0xC8010050
		opword 0xEC20F028
		bl sincosf
		opword 0xC021000C
		opword 0xC0010010
		opword 0xECA10672
		opword 0xC0C10014
		opword 0xC05F008C
		opword 0xEC200672
		opword 0xC01F0094
		opword 0xC0810018
		opword 0xC07F0090
		opword 0xECA6117A
		opword 0xC05C008C
		opword 0xEC26007A
		opword 0xC01C0094
		opword 0xECD9193A
		opword 0xC09C0090
		opword 0xEC651028
		opword 0xFC062000
		opword 0xEC462028
		opword 0xEC210028
		opword 0x41820040
		opword 0xFC062040
		opword 0x4C411382
		opword 0x40820020
		opword 0xC01C0150
		opword 0xEC04002A
		opword 0xFC060040
		opword 0x4C401382
		opword 0x4082000C
		lfs f2, float_0_80419b9c(r2)
		opword 0x48000018
		opword 0xC01C0150
		opword 0xEC04002A
		opword 0xFC060040
		opword 0x40810008
		opword 0xEC460028
		opword 0xEC0200B2
		opword 0xEC0300FA
		opword 0xEC81007A
		opword 0xFC04F840
		opword 0x4081004C
		opword 0xFC202034
		opword 0xC87E01C0
		opword 0xC85E01C8
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC210032
		opword 0xFC010072
		opword 0xFC230072
		opword 0xFC04103C
		opword 0xFC010032
		opword 0xFC840032
		opword 0xFC802018
		opword 0x48000088
		opword 0xC81E01D0
		opword 0xFC040040
		opword 0x40800010
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0x48000070
		opword 0xD0810008
		opword 0x3C007F80
		opword 0x80810008
		opword 0x54830050
		opword 0x7C030000
		opword 0x41820014
		opword 0x40800040
		opword 0x2C030000
		opword 0x41820020
		opword 0x48000034
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000001
		opword 0x48000028
		opword 0x38000002
		opword 0x48000020
		opword 0x5480027F
		opword 0x4182000C
		opword 0x38000005
		opword 0x48000010
		opword 0x38000003
		opword 0x48000008
		opword 0x38000004
		opword 0x2C000001
		opword 0x4082000C
		lis r3, __float_nan@ha
		lfs f4, __float_nan@l(r3)
		opword 0xC01C014C
		opword 0xFC202090
		opword 0xEC16B83A
		opword 0xFC040040
		opword 0x4080000C
		opword 0x7F80E378
		opword 0x48000008
		opword 0x38000000
		opword 0x28000000
		opword 0x7C030378
		opword 0x40820014
		opword 0xEF7BC02A
		opword 0xFC1BE840
		opword 0x4C401382
		opword 0x4182FD98
		opword 0xD03D0000
	}
#endif
}
#ifdef NONMATCHING

#define FH_NPC_FILTER(f1000, bit)                                                    \
    if (npc == NULL) continue;                                                       \
    if (!(npc->flags & 2)) continue;                                                 \
    if (f1000) { if (!(npc->flags & 8)) continue; } else { if (npc->flags & 8) continue; } \
    if (soft && !(FH(npc, 0x4, u32) & (bit))) continue;                              \
    if (npc->flags & 0x20000000) continue;                                           \
    if (npc->flags & 0x20) continue;                                                 \
    if (FH(npc, 0x1D4, u32) & 4) continue;                                           \
    if (npc->flags & 0x08000000) continue;

#define FH_NPC_FILTER2(f1000, bit)                                                        if (npc == NULL) continue;                                                           if (!(npc->flags & 2)) continue;                                                     if (f1000) { if (!(npc->flags & 8)) continue; } else { if (npc->flags & 8) continue; }     if (soft && !(FH(npc, 0x4, u32) & (bit))) continue;                                  if (npc->flags & 0x20000000) continue;                                               if (npc->flags & 0x20) continue;                                                     if (npc->flags & 0x08000000) continue;                                               if (FH(npc, 0x1D4, u32) & 4) continue;

typedef struct { s32 v[11]; } SinTbl;
static const SinTbl sSinTbl = {{0, 0, 0, 0, 45, 60, 90, 100, 101, 101, 101}};

void* fbatHitCheck(u32 flags, void* a1) {
    NpcEntry* npc = NULL;
    NpcEntry* hit = NULL;
    NpcWork* wp = npcGetWorkPtrInline();
    MarioWork* mario;
    FbatHitResult res;
    f32 dist;
    s32 i;
    u32 soft;
    s32 total;
    PartyEntry* party;

    mario = marioGetPtr();
    res.kind = 0;
    res.dist = 1000.0f;
    res.bits &= ~1;
    soft = flags & 0x2000;
    if (soft) {
        res.bits |= 1;
    }

    if (flags & 0x30) {
        u32 noJump = flags & 0x10;
        total = wp->total;
        npc = wp->entries;
        if (!noJump || mario->unk4C <= 0) {
            if (fbat_canHit(npc)) {
                u32 f1000 = flags & 0x1000;
                u32 f20 = flags & 0x20;
                for (i = 0; i < total; i++, npc++) {
                    f32 dx, dz;
                    if (npc == NULL) continue;
                    if (!(npc->flags & 2)) continue;
                    if (f1000) {
                        if (!(npc->flags & 8)) continue;
                    } else {
                        if (npc->flags & 8) continue;
                    }
                    if (soft && !(FH(npc, 0x4, u32) & 1)) continue;
                    if (npc->flags & 0x20) continue;
                    if (FH(npc, 0x1D4, u32) & 4) continue;
                    if (npc->flags & 0x08000000) continue;
                    if (mario->position.y >= FH(npc, 0x90, f32) + FH(npc, 0x150, f32)) continue;
                    if (mario->position.y + mario->wPlayerCollisionBox.y <= FH(npc, 0x90, f32)) continue;
                    dz = mario->position.z - FH(npc, 0x94, f32);
                    dx = mario->position.x - FH(npc, 0x8C, f32);
                    dist = npc_sqrtf(dx * dx + dz * dz);
                    if (dist > 0.5f * (mario->wPlayerCollisionBox.x + FH(npc, 0x14C, f32))) continue;
                    if (dist >= res.dist) continue;
                    if (noJump && !(FH(npc, 0x1D4, u32) & 0x10000) && mario->unk4C <= 0) {
                        if (FH(npc, 0x2F8, s32) == 0 ||
                            (evtGetPtrID(FH(npc, 0x11C, s32)) ? evtGetPtrID(FH(npc, 0x11C, s32))->wNpcEventType == 5 : 0)) {
                            if (npc->flags & 0x20000000) continue;
                            res.kind = 0x10000;
                            hit = npc;
                            res.dist = dist;
                            if (!soft) fbatSetAttackAnnounce(0x10000);
                        } else if (pouchEquipCheckBadge(0x140)) {
                            res.kind = 0x10000;
                            hit = npc;
                            res.dist = dist;
                            if (!soft) fbatSetAttackAnnounce(0x10000);
                        } else {
                            res.kind = 0x10000000;
                            hit = npc;
                            res.dist = dist;
                            if (!soft) {
                                fbatSetAttackAnnounce(0x10000000);
                            }
                            res.evtId = FH(npc, 0x2F8, s32);
                        }
                    }
                    if (!f20) continue;
                    if ((mario->flags & 0x20000) && !(mario->flags & 0x10000) &&
                        !(npc->flags & 0x20000000)) {
                        hit = npc;
                        res.dist = dist;
                        if (marioGetJabaraState() == 6) {
                            res.kind = 0x20000;
                            if (!soft) fbatSetAttackAnnounce(0x20000);
                        } else if (FH(mario, 0x2E, u16) == 0x10) {
                            res.kind = 0x40000;
                            if (!soft) fbatSetAttackAnnounce(0x40000);
                        } else {
                            res.kind = 0x20000;
                            if (!soft) fbatSetAttackAnnounce(0x20000);
                        }
                    } else if (marioGetJabaraState() == 6 && !(npc->flags & 0x20000000)) {
                        res.kind = 0x20000;
                        hit = npc;
                        res.dist = dist;
                        if (!soft) fbatSetAttackAnnounce(0x20000);
                    }
                }
            }
        }
    }

    if (flags & 0x40) {
        while (hit == NULL) {
            f32 r, angle;
            if ((flags & 0x10) && mario->unk4C > 0) break;
            if (!fbat_canHit(npc)) break;
            if (flags & 1) {
                MarioWork* m;
                s32 v;
                f32 f;
                f32 s1, c1, s2, c2;
                f32 z, x, y;
                u32 f1000;
                if (FH(mario, 0x2E, u16) != 0x12) break;
                r = 1.5f * mario->wPlayerCollisionBox.x;
                angle = reviseAngle(mario->displayDirection - 90.0f + FH(camGetPtr(CAMERA_3D), 0x114, f32));
                m = marioGetPtr();
                animPoseGetAnimPosePtr(FH(m, 0x228 + marioAnimeId() * 4, s32));
                v = FH(m, 0x48, s32);
                if (v > 20) v = 10;
                f = v;
                m = marioGetPtr();
                {
                    SinTbl tbl = sSinTbl;
                    if (f < 0.0f) f = 0.0f;
                    if (f >= 11.0f) f = 10.0f;
                    sincosf(&s1, &c1, angle);
                    sincosf(&s2, &c2, tbl.v[(s32)f]);
                }
                f1000 = flags & 0x1000;
                x = m->position.x + s2 * (s1 * r);
                z = m->position.z + s2 * (c1 * r);
                y = m->position.y + r * c2;
                npc = wp->entries;
                for (i = 0; i < total; i++, npc++) {
                    FH_NPC_FILTER2(f1000, 2)
                    if (!_npcHitCheckSphere(npc, &dist, x, y, z, 12.0f)) continue;
                    if (dist >= res.dist) continue;
                    res.dist = dist;
                    hit = npc;
                    res.kind = 0x100000;
                    if (!soft) fbatSetAttackAnnounce(0x100000);
                    break;
                }
            } else {
                u32 f1000;
                r = 1.5f * mario->wPlayerCollisionBox.x;
                angle = reviseAngle(mario->displayDirection - 90.0f + FH(camGetPtr(CAMERA_3D), 0x114, f32));
                npc = wp->entries;
                f1000 = flags & 0x1000;
                for (i = 0; i < total; i++, npc++) {
                    FH_NPC_FILTER(f1000, 2)
                    if (!_npcHitCheckHammerAllMotion(npc, &dist, r, angle)) continue;
                    if (dist >= res.dist) continue;
                    res.dist = dist;
                    hit = npc;
                    res.kind = 0x100000;
                    if (!soft) fbatSetAttackAnnounce(0x100000);
                    break;
                }
            }
            break;
        }
    }

    if (flags & 0x80) {
        while (hit == NULL) {
            f32 r, angle;
            if ((flags & 0x10) && mario->unk4C > 0) break;
            if (!fbat_canHit(npc)) break;
            if (flags & 1) {
                MarioWork* m;
                f32 s, c, x, y, z;
                u32 f1000;
                if (FH(mario, 0x2E, u16) != 0x13) break;
                angle = marioGetAngleKaitenHammer();
                if (angle < 0.0f) break;
                r = 1.5f * mario->wPlayerCollisionBox.x;
                m = marioGetPtr();
                sincosf(&s, &c, angle);
                f1000 = flags & 0x1000;
                x = s * r + m->position.x;
                z = c * r + m->position.z;
                y = 15.0f + m->position.y;
                npc = wp->entries;
                for (i = 0; i < total; i++, npc++) {
                    FH_NPC_FILTER(f1000, 2)
                    if (!_npcHitCheckSphere(npc, &dist, x, y, z, 12.0f)) continue;
                    if (dist >= res.dist) continue;
                    res.dist = dist;
                    hit = npc;
                    if (pouchGetHammerLv() < 3) {
                        res.kind = 0x200000;
                    } else {
                        res.kind = 0x400000;
                    }
                    if (!soft) fbatSetAttackAnnounce(res.kind);
                    break;
                }
            } else {
                u32 f1000;
                r = 1.5f * mario->wPlayerCollisionBox.x;
                angle = reviseAngle(mario->displayDirection - 90.0f + FH(camGetPtr(CAMERA_3D), 0x114, f32));
                npc = wp->entries;
                f1000 = flags & 0x1000;
                for (i = 0; i < total; i++, npc++) {
                    FH_NPC_FILTER(f1000, 2)
                    if (!_npcHitCheckHammerAllMotion(npc, &dist, r, angle)) continue;
                    if (dist >= res.dist) continue;
                    res.dist = dist;
                    hit = npc;
                    if (pouchGetHammerLv() < 3) {
                        res.kind = 0x200000;
                    } else {
                        res.kind = 0x400000;
                    }
                    if (!soft) fbatSetAttackAnnounce(res.kind);
                    break;
                }
            }
            break;
        }
    }

    if (flags & 0x100) {
        party = partyGetPtr(marioGetPartyId());
        while (hit == NULL) {
            u32 b;
            f32 x, y, z, r;
            u32 f1000;
            if ((flags & 0x10) && mario->unk4C > 0) break;
            if (!fbat_canHit(npc)) break;
            b = flags & 1;
            if (b) {
                s32 st;
                if (party == NULL) break;
                if (FH(party, 0x33, u8) != 2) break;
                if (!(party->flags & 0x100)) break;
                st = nokonokoGetStatus(party);
                if (st < 2 || st > 5) break;
            }
            if (!b) break;
            f1000 = flags & 0x1000;
            r = 0.5f * party->width;
            y = 0.5f * party->height + party->position.y;
            x = party->position.x;
            z = party->position.z;
            npc = wp->entries;
            for (i = 0; i < total; i++, npc++) {
                FH_NPC_FILTER(f1000, 4)
                if (!_npcHitCheckSphere(npc, &dist, x, y, z, r)) continue;
                if (dist >= res.dist) continue;
                res.dist = dist;
                hit = npc;
                res.kind = 0x800000;
                if (!soft) fbatSetAttackAnnounce(0x800000);
                break;
            }
            break;
        }
    }

    if (flags & 0x200) {
        party = partyGetPtr(marioGetPartyId());
        while (hit == NULL) {
            if ((flags & 0x10) && mario->unk4C > 0) break;
            if (!fbat_canHit(npc)) break;
            if (!(flags & 1)) break;
            if (party == NULL) break;
            if (FH(party, 0x33, u8) != 3) break;
            if (!FH(gp->fbatData, 0x54D, u8)) break;
            npc = wp->entries;
            flags &= 0x1000;
            for (i = 0; i < total; i++, npc++) {
                FH_NPC_FILTER(flags, 8)
                if (!_npcHitCheckSphere(npc, &dist, party->position.x, 0.5f * party->height + party->position.y,
                                        party->position.z, 30.0f)) continue;
                if (dist >= res.dist) continue;
                res.dist = dist;
                hit = npc;
                res.kind = 0x1000000;
                if (!soft) fbatSetAttackAnnounce(0x1000000);
                break;
            }
            break;
        }
    }

    if (a1) {
        *(FbatHitResult*)a1 = res;
    }
    return hit;
}

void npcStrippedHitPool(f32* f) {
    f[0] = 15.0f;
}

NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r) {
    f32 dx = x - npc->position.x;
    f32 dy = y - npc->position.y;
    f32 dz = z - npc->position.z;

    if (y != npc->position.y) {
        if (y >= npc->position.y && y <= npc->position.y + npc->height) {
            dy = 0.0f;
        } else if (y > npc->position.y + npc->height) {
            dy = y - (npc->position.y + npc->height);
        }
    }
    *dist = npc_sqrtf(dx * dx + dy * dy + dz * dz);
    if (*dist < 0.5f * npc->width + r) {
        return npc;
    }
    return NULL;
}

NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle) {
    f32 t;
    f32 d;
    float tmpi2;
    NpcEntry* hit;

    for (t = 0.0f; t <= 11.0f; t += 1.0f) {
        f32 f = t;
        MarioWork* mario = marioGetPtr();
        f32 c2, s2, c1, s1;
        f32 x, y, z;
        SinTbl tbl = *(volatile const SinTbl*)&sSinTbl; // FAKE: volatile copy needed for 100% (87.59 with a plain struct copy)

        if (f < 0.0f) {
            f = 0.0f;
        }
        if (f >= 11.0f) {
            f = 10.0f;
        }
        sincosf(&s1, &c1, angle);
        sincosf(&s2, &c2, tbl.v[(s32)f]);
        tmpi2 = mario->position.x + s2 * (s1 * r);
        x = tmpi2;
        z = mario->position.z + s2 * (c1 * r);
        y = mario->position.y + r * c2;
        hit = _npcHitCheckSphere(npc, &d, x, y, z, 12.0f);
        if (hit) {
            break;
        }
    }
    *dist = d;
    return hit;
}
#endif
#ifndef NONMATCHING
#pragma pop
#endif

BOOL npcCheckInterrupt(NpcEntry* npc) {
    EventEntry* evt;
    u32 flags;

    evtGetPtrID(npc->regularEvtId);
    flags = npc->interruptFlags;
    if (flags & ~0xF00) {
        evt = NULL;
        if ((flags & 0x10) && npc->deadEvent) {
            evt = evtEntry(npc->deadEvent, 0, 0x20);
            evt->wNpcEventType = 8;
            evt->ownerNPC = npc;
        } else if ((flags & 0x10000000) && npc->moveEvent) {
            evt = evtEntry(npc->moveEvent, 0, 0x20);
            evt->wNpcEventType = 1;
            evt->ownerNPC = npc;
        } else if ((flags & 8) && npc->blowEvent) {
            evt = evtEntry(npc->blowEvent, 0, 0x20);
            evt->wNpcEventType = 5;
            evt->ownerNPC = npc;
        } else if ((flags & 1) && npc->findEvent && !(npc->jumpFlags & 0x1000) &&
                   !(npc->flags & 0x200000) && !(flags & 0x100)) {
            evt = evtEntry(npc->findEvent, 0, 0x20);
            evt->wNpcEventType = 2;
            evt->ownerNPC = npc;
        } else if ((flags & 2) && npc->lostEvent && !(npc->jumpFlags & 0x1000) &&
                   !(npc->flags & 0x200000)) {
            evt = evtEntry(npc->lostEvent, 0, 0x20);
            evt->wNpcEventType = 3;
            evt->ownerNPC = npc;
        } else if ((flags & 4) && npc->returnEvent && !(npc->jumpFlags & 0x1000) &&
                   !(npc->flags & 0x200000)) {
            evt = evtEntry(npc->returnEvent, 0, 0x20);
            evt->wNpcEventType = 4;
            evt->ownerNPC = npc;
        }
        if (evt) {
            evtDeleteID(npc->regularEvtId);
            npc->regularEvtId = evt->eventId;
            npc->interruptFlags &= 0xF00;
            npc->jumpFlags &= ~0x1000;
            npc->field_188 = 0;
#ifdef NONMATCHING
            npc->moveSpeed = 0.0f;
#endif
#ifndef NONMATCHING
            npc->moveSpeed = EXT_LIT(float_0_80419b9c, 0.0f);
#endif
            return TRUE;
        }
    }
    npc->interruptFlags &= 0xF00;
    npc->jumpFlags &= ~0x1000;
    return FALSE;
#ifdef NONMATCHING
}

static inline void npcRandField(NpcBattleInfo* info, NpcSetupBattleInfo* setup) {
    s32 i;
    for (i = 0; i < 16; i++) {
        info->field_B0[i] = (u8)setup->field_20[i][0] + irand(setup->field_20[i][1] - setup->field_20[i][0] + 1);
    }
#endif
}

void npcSetupBattleInfo(NpcEntry* npc, NpcSetupBattleInfo* setup) {
    s32 i;
    s32 num;
    NpcBattleInfo* info;
    NpcBattleSelect* select;
    BattleUnitSetup* unit;
    ItemDropData* table;
    ItemDropData* drop;
    s32 total;

    info = &npc->battleInfo;
    memset(info, 0, sizeof(NpcBattleInfo));
    memset(info->recoveredItems, 0, sizeof(info->recoveredItems));
    if (setup && setup->name) {
        info->field_AC = setup->field_1C;
        switch (info->field_AC) {
            case 0:
            default:
                npcRandField(info, setup);
                break;
            case 1:
            case 2:
                break;
        }
        info->field_4 = setup->field_18;
        info->fixedItem = setup->fixedItem;
        info->itemDropped = 0;
        info->heartsDropped = 0;
        info->flowersDropped = 0;
        info->field_C0 = setup->field_40;
        if (setup->swFlag >= -EVTDAT_GSWF_BASE && setup->swFlag <= EVTDAT_GSWF_MAX) {
            if (swGet(setup->swFlag + EVTDAT_GSWF_BASE)) {
                select = setup->altSelect;
            } else {
                select = setup->select;
            }
        } else {
            select = setup->select;
        }
        info->groupSetup = NULL;
        if (select) {
            NpcBattleSelect* p;
            s32 w;

            total = 0;
            for (p = select; (w = p->weight) > 0; p++) {
                total += w;
            }
            if (total > 0) {
                total = irand(total);
                while (TRUE) {
                    if ((total -= select->weight) < 0) {
                        break;
                    }
                    select++;
                }
                info->groupSetup = select->groupSetup;
                info->stageData = select->stageData;
            }
        }
        if (info->groupSetup) {
            num = info->groupSetup->numEnemies;
            unit = info->groupSetup->enemyData;
            memset(info->heldItems, 0, sizeof(info->heldItems));
            for (i = 0; i < num; unit++, i++) {
                table = unit->itemDropTable;
                if (table) {
                    total = 0;
                    for (drop = table; drop->holdWeight > 0 || drop->type; drop++) {
                        total += drop->holdWeight;
                    }
                    if (total > 0) {
                        total = irand(total);
                        while (TRUE) {
                            if ((total -= table->holdWeight) < 0) {
                                info->heldItems[i] = table->type;
                                info->itemDropLists[i] = unit->itemDropTable;
                                break;
                            }
                            table++;
                        }
                    }
                }
            }
        }
        npc->baseCoinCount = 0;
        if (info->groupSetup) {
            npc->baseCoinCount = info->groupSetup->enemyData->mUnitKindParams->baseCoin;
        }
        npc->flags |= 0x10000000;
    }
}

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void npcSetBattleInfo(NpcEntry* npc, s32 battleInfoId) {
    NpcSetupBattleInfo* setup;
    char areaName[4];
    s32 i;

    if (battleInfoId == -1) {
        setup = NULL;
    } else {
        areaName[0] = gp->currentMapName[0];
        areaName[1] = gp->currentMapName[1];
        areaName[2] = gp->currentMapName[2];
        areaName[3] = '\0';
        setup = areaDataPtr(areaName)->btlSetupTbl;
        for (i = battleInfoId; i > 0; i--) {
            setup++;
        }
    }
    npcSetupBattleInfo(npc, setup);
    for (i = 0; i < 4; i++) {
        if (npc->slaves[i]) {
            npc->slaves[i]->battleInfo = npc->battleInfo;
        }
    }
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

#ifndef NONMATCHING
#define npcStopForOneEvent npcStopForOneEvent__af_inl
#endif
void npcStopForEvent(void) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;
    for (i = 0; i < total; i++, entry++) {
        npcStopForOneEvent(entry);
    }
}

#ifndef NONMATCHING
#undef npcStopForOneEvent

#endif
void npcStopForOneEvent(NpcEntry* npc) {
    if (npc && npc->flags & 2 && npc->flags & 0x10000000) {
        npc->jumpFlags |= 0x10000;
        evtStopID(npc->regularEvtId);
#ifdef NONMATCHING
        animPoseSetLocalTimeRate(npc->poseId, 0.0f);
#endif
#ifndef NONMATCHING
        animPoseSetLocalTimeRate(npc->poseId, EXT_LIT(float_0_80419b9c, 0.0f));
#endif
    }
}

#ifndef NONMATCHING
#define npcStartForOneEvent npcStartForOneEvent__af_inl
#endif
void npcStartForEvent(void) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;
    if (total) {
    }
    for (i = 0; i < total; i++, entry++) {
        npcStartForOneEvent(entry);
    }
}

#ifndef NONMATCHING
#undef npcStartForOneEvent

#endif
void npcStartForOneEvent(NpcEntry* npc) {
    if (npc && npc->flags & 2 && npc->flags & 0x10000000 && npc->jumpFlags & 0x10000) {
        npc->jumpFlags &= ~0x10000;
        evtStartID(npc->regularEvtId);
#ifdef NONMATCHING
        animPoseSetLocalTimeRate(npc->poseId, 1.0f);
#endif
#ifndef NONMATCHING
        animPoseSetLocalTimeRate(npc->poseId, EXT_LIT(float_1_80419bb4, 1.0f));
#endif
    }
}

void npcSetColor(const char* name, GXColor color) {
    npcNameToPtr(name)->color = color;
}

void npcBlurOn(const char* name) {
    NpcEntry* npc = npcNameToPtr(name);

    npc->flags |= 0x100;
    npc->positionHistory[0] = npc->position;
    npc->positionHistory[1] = npc->position;
    npc->positionHistory[2] = npc->position;
    npc->positionHistory[3] = npc->position;
    npc->positionHistory[4] = npc->position;
}

void npcBlurOff(const char* name) {
    npcNameToPtr(name)->flags &= ~0x100;
}

s32 npcGetBtlSetupWork(NpcEntry* npc, s32 index) {
    return npc->battleInfo.btlSetupWork[index];
}

void npcSetBtlSetupWork(NpcEntry* npc, s32 index, s32 value) {
    npc->battleInfo.btlSetupWork[index] = value;
}

void npcSetSlave(NpcEntry* npc, NpcEntry* slave, s32 id) {
    slave->master = npc;
    npc->slaves[id] = slave;
}

void npcSetLink(NpcEntry* npc, NpcEntry* other) {
    npc->next = other;
    other->prev = npc;
}

NpcTerritoryType dbGetDefData(NpcTerritoryInfo* info, const char* description) {
    NpcTerritoryType type;

    type = NPC_TERRITORY_TYPE_NOTHING;
    while (TRUE) {
        if (!info->description) {
            break;
        }
        if (!strcmp(info->description, description)) {
            type = info->type;
            break;
        }
        info++;
    }
    return type;
}

void npcExecAllInitEvt(void) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;
    EventEntry* evt;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;

    for (i = 0; i < total; i++, entry++) {
        if (entry && entry->flags & 1) {
            if (entry->initEvent) {
                if (entry->initEvtId) {
                    evtDeleteID(entry->initEvtId);
                }
                evt = evtEntry(entry->initEvent, 0, 0);
                evt->wNpcEventType = 0;
                evt->ownerNPC = entry;
                entry->initEvtId = evt->eventId;
            } else {
                entry->initEvtId = 0;
            }
        }
    }
}

BOOL npcWaitAllInitEvtEnd(void) {
    NpcWork* wp;
    BOOL done;
    s32 i;
    s32 total;
    NpcEntry* entry;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    done = TRUE;
    entry = wp->entries;

    for (i = 0; i < total; i++, entry++) {
        if (entry && entry->flags & 1 && !(entry->flags & 2)) {
            if (entry->initEvtId) {
                done = FALSE;
                if (!evtCheckID(entry->initEvtId)) {
                    entry->initEvtId = 0;
                    entry->flags |= 2;
                }
            } else {
                entry->flags |= 2;
            }
        }
    }
    return done;
}

void npcExecAllReglEvt(void) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;
    EventEntry* evt;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;

    for (i = 0; i < total; i++, entry++) {
        if (entry && entry->flags & 1 && entry->moveEvent) {
            if (entry->regularEvtId) {
                evtDeleteID(entry->regularEvtId);
            }
            evt = evtEntry(entry->moveEvent, 0, 0x20);
            evt->wNpcEventType = 1;
            evt->ownerNPC = entry;
            entry->regularEvtId = evt->eventId;
        }
    }
}

#ifdef NONMATCHING
USER_FUNC(_check) {
#endif
#ifndef NONMATCHING
s32 _check(EventEntry* event, BOOL isFirstCall) {
#endif
    s32* args = event->args;
    s32 index = *args++;

    if (pouchGetPtr()->mMerleeCurseUsesRemaining) {
        evtSetValue(event, index, 0);
    } else {
        evtSetValue(event, index, 1);
    }
    return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(_majinai_effect) {
    MarioWork* mario = marioGetPtr();
    EffectEntry* effect;

    if (isFirstCall) {
        event->userdatap[0] = effMajinaiEntry(0, mario->position.x, mario->position.y + mario->wPlayerCollisionBox.y + 16.0f, mario->position.z);
        effect = event->userdatap[0];
        ((f32*)effect->userdata)[4] = 0.8f;
        effSetName(event->userdatap[0], (char*)str_802C3128);
    }
    if (event->userdata[0] && effNameToPtr((char*)str_802C3128)) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 _majinai_effect(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0x93E1000C
		opword 0x7C9F2378
		opword 0x93C10008
		opword 0x7C7E1B78
		bl marioGetPtr
		opword 0x2C1F0000
		opword 0x7C641B78
		opword 0x4182004C
		opword 0xC0240090
		opword 0x38600000
		opword 0xC00401B8
		lfs f2, float_16_80419bac(r2)
		opword 0xEC01002A
		opword 0xC024008C
		opword 0xC0640094
		opword 0xEC42002A
		bl effMajinaiEntry
		opword 0x907E0078
		lis r3, str_802C3128@ha
		addi r4, r3, str_802C3128@l
		lfs f0, float_0p8_80419bb0(r2)
		opword 0x807E0078
		opword 0x8063000C
		opword 0xD0030010
		opword 0x807E0078
		bl effSetName
		opword 0x801E0078
		opword 0x2C000000
		opword 0x41820020
		lis r3, str_802C3128@ha
		addi r3, r3, str_802C3128@l
		bl effNameToPtr
		opword 0x28030000
		opword 0x4182000C
		opword 0x38600000
		opword 0x48000008
		opword 0x38600002
		opword 0x80010014
		opword 0x83E1000C
		opword 0x83C10008
		opword 0x7C0803A6
		opword 0x38210010
	}
#endif
}
#ifdef NONMATCHING

EVT_BEGIN(evt_majinai_effect_se_fld)
    CALL(btlevtcmd_ftomsec, 29, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C2FC8), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 200, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C2FE4), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 90, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3000), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 80, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C301C), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 5, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3038), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_majinai_effect_se_btl)
    CALL(btlevtcmd_ftomsec, 29, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3054), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 200, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3070), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 90, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C308C), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 80, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C30A8), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 5, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C30C4), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(_evt_majinai_coin_up_effect)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    SPAWN_EVENT(evt_majinai_effect_se_fld)
    CALL(_majinai_effect)
    CALL(evt_msg_print, 0, PTR((char*)str_802C30E0), 0, 0)
    CALL(_check, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, PTR((char*)str_802C30F0), 0, 0)
    END_IF
    RETURN
EVT_END()
#endif
#ifndef NONMATCHING
#pragma pop
#endif

void npcGetBackItemEntry(NpcEntry* npc) {
    NpcBattleInfo* info = &npc->battleInfo;
    s32 i;

    for (i = 0; i < 8; i++) {
        if (info->recoveredItems[i]) {
            itemFlagOn(itemEntry(NULL, info->recoveredItems[i], 11, -1, 0, npc->position.x,
                                 npc->position.y, npc->position.z),
                       0x100);
            info->recoveredItems[i] = 0;
        }
    }
}

void npcClearDeadInfo(void) {
    memset(gp->fbatData->deadInfo, 0, sizeof(gp->fbatData->deadInfo));
}

#ifdef NONMATCHING
void npcStrippedKoopaPool(f32* f, const char** p) {
    f[0] = 60.0f;
    f[1] = 365.0f;
    p[0] = (char*)str_802C3104;
    p[1] = (char*)str_802C310C;
}
#endif

#ifdef NONMATCHING
void npcKoopaModeMain(void) {
    s32 jump;
    u8* fb2;
    s32 fire;
    MarioWork* mario;
    fbatEncountCheck();
    fb2 = *(u8**)((u8*)gp + 0x168);
    mario = marioGetPtr();
    jump = 0;
    fire = jump;
    if (*((s8*)mario + 0x3c) == 2) jump = kpaJumpChk();
    if (*((s8*)mario + 0x3c) == 2) fire = kpaFireAttackCheck();
    if (jump) {
        if (*(s32*)(fb2 + 0x57c) > 0 && *(s32*)(fb2 + 0x578) >= 2) {
            Vec pos = *(Vec*)((u8*)mario + 0x8c);
            pos.y += 60.0f;
            kpaAddScorePos(*(s32*)(fb2 + 0x57c), &pos);
        }
        *(s32*)(fb2 + 0x578) = 0;
        *(s32*)(fb2 + 0x57c) = 0;
    }
    if (!fire) {
        *(s32*)(fb2 + 0x574) = 0;
    }
}

void npcKoopaModeEncountCheck(void) {
    NpcWork* wp;
    FieldBattleData* data;
    s32 i;
    s32 total;
    NpcEntry* entry;

    data = gp->fbatData;
    wp = npcGetWorkPtrInline();
    total = wp->total;

    if (data->mode == 1) {
        entry = wp->entries;
        for (i = 0; i < total; i++, entry++) {
            if (entry && entry->flags & 1 && entry->flags & 0x8000000 && !(entry->jumpFlags & 4)) {
                switch (kpaEnemyHitChk(entry->position.x, entry->position.y, entry->position.z, entry->height,
                                       entry->width)) {
                    case 1:
                        if (!(entry->field_31E & 1)) {
                            npcGroupDead(entry, 1);
                        }
                        break;
                    case 2:
                        if (!(entry->field_31E & 2)) {
                            npcGroupDead(entry, 2);
                        }
                        break;
                    case 3:
                        if (!(entry->field_31E & 4)) {
                            npcGroupDead(entry, 4);
                        }
                        break;
                    case 4:
                        kpaPowDown();
                        break;
                    default:
                        if (!(entry->field_31E & 0x10) && entry->field_0x300 &&
                            !strcmp(hitGetName(entry->field_0x300), (char*)str_802C30FC)) {
                            npcGroupDead(entry, 0x10);
                        }
                        break;
                }
            }
        }
    }
}

s32 npcKoopaModeMobjBoundDeadCheck(HitEntry* hit) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;
    s32 count;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    count = 0;

    if (hit == NULL) {
        return 0;
    }
    entry = wp->entries;
    for (i = 0; i < total; i++, entry++) {
        if (entry && entry->flags & 1 && entry->flags & 0x8000000 && !(entry->jumpFlags & 4) &&
            !(entry->field_31E & 8) && entry->field_0x300 == hit) {
            npcGroupDead(entry, 8);
            count++;
        }
    }
    return count;
}

void fbatSandersBombTriggerOn(void) {
    gp->fbatData->sandersBombTrigger = TRUE;
}

s32 npcCalcScore(NpcEntry* npc) {
    FieldBattleData* data = gp->fbatData;
    s32 score = 300;
    Vec pos = npc->position;

    pos.y += npc->tribe->height;
    if (npc->koopaEncounterType == 0x10) {
        score = 0;
    } else {
        if (npc->koopaEncounterType == 8) {
            score = 400;
        }
        if (kpaMutekiCheck()) {
            score += 100;
        }
        if (npc->koopaEncounterType == 2) {
            data->field_574++;
            score *= data->field_574;
        }
        if (npc->koopaEncounterType == 1) {
            data->field_578++;
            data->field_57C += score;
        }
        if (score > 9999) {
            score = 10000;
        }
    }
    if (score > 0) {
        kpaAddScorePos(score, &pos);
    }
    return score;
}

BOOL npcCheckBlow(NpcEntry* npc) {
    Vec pos;

    if (npc->flags & 0x20000000) {
        return FALSE;
    }
    if (npc->flags & 0x20) {
        return FALSE;
    }
    pos = npc->position;
    if (cloudGetBreathPower(pos, npc->width) > 0.0f) {
        return TRUE;
    }
    pos = npc->position;
    pos.y -= npc->height / 2.0f;
    if (cloudGetBreathPower(pos, npc->width) > 0.0f) {
        return TRUE;
    }
    pos = npc->position;
    pos.y -= npc->height;
    if (cloudGetBreathPower(pos, npc->width) > 0.0f) {
        return TRUE;
    }
    return FALSE;
}

BOOL N_fbatPreventMarioEventChk(void) {
    s32 mode = gp->fbatData->mode;
    if (mode != 0 && mode != 1 && mode != 8) {
        return TRUE;
    }
    return FALSE;
}

#endif
#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#endif
#pragma force_active on
#ifdef NONMATCHING
__declspec(section ".data") u32 gap_05_8030543C_data[1] = {0};
#pragma force_active reset
#endif
#ifndef NONMATCHING
__declspec(section ".rodata") const f32 vec3_802c2f78[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802c2f84[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802c2f90[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const u32 dat_802c2f9c[11] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000002D, 0x0000003C, 0x0000005A, 0x00000064, 0x00000065, 0x00000065, 0x00000065};
__declspec(section ".rodata") const char str_802C2FC8[] = "SFX_EVT_FLD_INCANT_CUBE1\0\0\0";
__declspec(section ".rodata") const char str_802C2FE4[] = "SFX_EVT_FLD_INCANT_CUBE2\0\0\0";
__declspec(section ".rodata") const char str_802C3000[] = "SFX_EVT_FLD_INCANT_CUBE3\0\0\0";
__declspec(section ".rodata") const char str_802C301C[] = "SFX_EVT_FLD_INCANT_CUBE4\0\0\0";
__declspec(section ".rodata") const char str_802C3038[] = "SFX_EVT_FLD_INCANT_CUBE5\0\0\0";
__declspec(section ".rodata") const char str_802C3054[] = "SFX_EVT_BTL_INCANT_CUBE1\0\0\0";
__declspec(section ".rodata") const char str_802C3070[] = "SFX_EVT_BTL_INCANT_CUBE2\0\0\0";
__declspec(section ".rodata") const char str_802C308C[] = "SFX_EVT_BTL_INCANT_CUBE3\0\0\0";
__declspec(section ".rodata") const char str_802C30A8[] = "SFX_EVT_BTL_INCANT_CUBE4\0\0\0";
__declspec(section ".rodata") const char str_802C30C4[] = "SFX_EVT_BTL_INCANT_CUBE5\0\0\0";
__declspec(section ".rodata") const char str_802C30E0[] = "msg_mj_coin_up\0";
__declspec(section ".rodata") const char str_802C30F0[] = "msg_mj_last";
__declspec(section ".rodata") const char str_802C30FC[] = "a_magu\0";
__declspec(section ".rodata") const char str_802C3104[] = "kpa_03\0";
__declspec(section ".rodata") const char str_802C310C[] = "SFX_KUPPA_3RD_WATER_FALL1\0\0";
__declspec(section ".rodata") const char str_802C3128[] = "mjef_coinup";
__declspec(section ".rodata") const u32 gap_04_802C3134_rodata = 0x00000000;
__declspec(section ".rodata") const f64 double_0p5_802c3138 = 0.5;
__declspec(section ".rodata") const f64 double_3_802c3140 = 3.0;
__declspec(section ".rodata") const f64 double_0_802c3148 = 0.0;
__declspec(section ".rodata") const f64 double_to_int_802c3150 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802C3158[] = "fb_sensei_shita";
__declspec(section ".rodata") const char str_802C3168[] = "fb_sensei_sareta\0\0\0";
__declspec(section ".rodata") const char str_802C317C[] = "SFX_BTL_FLD_ENEMY_DAMAGED1\0";
__declspec(section ".rodata") const char str_802C3198[] = "SFX_BTL_FLD_MARIO_DAMAGED1\0";
__declspec(section ".rodata") const f64 double_to_int_mask_802c31b8 = 4503599627370496.0;
__declspec(section ".rodata") const char str_802C31C0[] = "(^x^)party\0";
__declspec(section ".rodata") const char str_802C31CC[] = "extparty\0\0\0";
__declspec(section ".rodata") const f64 double_0p75_802c31d8 = 0.75;
__declspec(section ".rodata") const char str_802C31E0[] = "c_luigi";
__declspec(section ".sdata2") const u32 dat_80419b88 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_80419b8c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419b90 = 0xFF8080FF;
__declspec(section ".sdata2") const u32 dat_80419b94 = 0x8080FFFF;
__declspec(section ".sdata2") const u32 dat_80419b98 = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_0_80419b9c = 0.0f;
__declspec(section ".sdata2") const f32 float_0p5_80419ba0 = 0.5f;
__declspec(section ".sdata2") const f32 float_60_80419ba4 = 60.0f;
__declspec(section ".sdata2") const f32 float_365_80419ba8 = 365.0f;
__declspec(section ".sdata2") const f32 float_16_80419bac = 16.0f;
__declspec(section ".sdata2") const f32 float_0p8_80419bb0 = 0.8f;
__declspec(section ".sdata2") const f32 float_1_80419bb4 = 1.0f;
__declspec(section ".sdata2") const f32 float_10_80419bb8 = 10.0f;
__declspec(section ".sdata2") const f32 float_11_80419bbc = 11.0f;
__declspec(section ".sdata2") const f32 float_12_80419bc0 = 12.0f;
__declspec(section ".sdata2") const f32 float_15_80419bc4 = 15.0f;
__declspec(section ".sdata2") const f32 float_1000_80419bc8 = 1000.0f;
__declspec(section ".sdata2") const f32 float_1p5_80419bcc = 1.5f;
__declspec(section ".sdata2") const f32 float_90_80419bd0 = 90.0f;
__declspec(section ".sdata2") const f32 float_30_80419bd4 = 30.0f;
__declspec(section ".sdata2") const f32 float_neg90_80419bd8 = -90.0f;
__declspec(section ".sdata2") const f32 float_rad2deg_80419bdc = 57.29579f;
__declspec(section ".sdata2") const f32 float_360_80419be0 = 360.0f;
__declspec(section ".sdata2") const f32 float_270_80419be4 = 270.0f;
__declspec(section ".sdata2") const f32 float_neg270_80419be8 = -270.0f;
__declspec(section ".sdata2") const f32 float_180_80419bec = 180.0f;
__declspec(section ".sdata2") const f32 float_neg180_80419bf0 = -180.0f;
__declspec(section ".sdata2") const f32 float_0p75_80419bf4 = 0.75f;
__declspec(section ".sdata2") const f32 float_neg1_80419bf8 = -1.0f;
__declspec(section ".sdata2") const f32 float_0p1_80419bfc = 0.1f;
__declspec(section ".sdata2") const f32 float_20_80419c00 = 20.0f;
__declspec(section ".sdata2") const f32 float_3p2_80419c04 = 3.2f;
__declspec(section ".sdata2") const f32 float_3_80419c08 = 3.0f;
__declspec(section ".sdata2") const f32 float_neg600_80419c0c = -600.0f;
__declspec(section ".sdata2") const f32 float_600_80419c10 = 600.0f;
__declspec(section ".sdata2") const f32 float_0p2_80419c14 = 0.2f;
__declspec(section ".sdata2") const f32 float_100_80419c18 = 100.0f;
__declspec(section ".sdata2") const f32 float_0p4_80419c1c = 0.4f;
__declspec(section ".sdata2") const f32 float_45_80419c20 = 45.0f;
__declspec(section ".sdata2") const f32 float_neg980_80419c24 = -980.0f;
__declspec(section ".sdata2") const f32 float_0p15_80419c28 = 0.15f;
__declspec(section ".sdata2") const f32 float_neg1000_80419c2c = -1000.0f;
__declspec(section ".sdata2") const f32 float_5_80419c30 = 5.0f;
__declspec(section ".sdata2") const f32 float_40_80419c34 = 40.0f;
__declspec(section ".sdata2") const f32 float_6p2832_80419c38 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_0p00761_80419c3c = 0.00761f;
__declspec(section ".sdata2") const f32 float_0p16605_80419c40 = 0.16605f;
__declspec(section ".sdata2") const f32 float_3p1416_80419c44 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_1p5708_80419c48 = 1.5707964f;
__declspec(section ".sdata2") const f32 float_4p7124_80419c4c = 4.712389f;
__declspec(section ".sdata2") const f32 float_0p03705_80419c50 = 0.03705f;
__declspec(section ".sdata2") const f32 float_0p4967_80419c54 = 0.4967f;
__declspec(section ".sdata2") const f32 float_4_80419c58 = 4.0f;
__declspec(section ".sdata2") const f32 float_2_80419c5c = 2.0f;
__declspec(section ".sdata2") const f32 float_160_80419c60 = 160.0f;
__declspec(section ".sdata2") const char str_80419C64[] = "party\0\0";
__declspec(section ".sdata2") const char str_80419C6C[] = "mario\0\0";
__declspec(section ".sdata2") const f32 float_1E06_80419c74 = 1000000.0f;
__declspec(section ".sdata2") const f32 float_0p05_80419c78 = 0.05f;
__declspec(section ".sdata2") const f32 float_0p25_80419c7c = 0.25f;
__declspec(section ".sdata2") const f32 float_neg2_80419c80 = -2.0f;
__declspec(section ".sdata2") const f32 float_5000_80419c84 = 5000.0f;
__declspec(section ".sdata2") const f32 float_10000_80419c88 = 10000.0f;
__declspec(section ".sdata2") const f32 float_1p33_80419c8c = 1.33f;
__declspec(section ".sdata2") const char str_80419C90[] = "hoshi\0\0";
__declspec(section ".sdata2") const char str_80419C98[] = "M_I_2\0\0";
__declspec(section ".sdata2") const f32 float_deg2rad_80419ca0 = 0.017453292f;
__declspec(section ".sdata2") const u32 gap_09_80419CA4_sdata2 = 0x00000000;
#endif


#ifdef NONMATCHING
// prototypes for asm stopgap forward references
BOOL N_fbatPreventMarioEventChk(void);
BOOL npcCheckBlow(NpcEntry* npc);
s32 npcCalcScore(NpcEntry* npc);
void fbatSandersBombTriggerOn(void);
s32 npcKoopaModeMobjBoundDeadCheck(HitEntry* hit);
void npcKoopaModeEncountCheck(void);
void npcClearDeadInfo(void);
void npcGetBackItemEntry(NpcEntry* npc);
s32 _majinai_effect(EventEntry* event, BOOL isFirstCall);
s32 _check(EventEntry* event, BOOL isFirstCall);
void npcExecAllReglEvt(void);
BOOL npcWaitAllInitEvtEnd(void);
void npcExecAllInitEvt(void);
NpcTerritoryType dbGetDefData(NpcTerritoryInfo* info, const char* description);
void npcSetLink(NpcEntry* npc, NpcEntry* other);
void npcSetSlave(NpcEntry* npc, NpcEntry* slave, s32 id);
void npcSetBtlSetupWork(NpcEntry* npc, s32 index, s32 value);
s32 npcGetBtlSetupWork(NpcEntry* npc, s32 index);
void npcBlurOff(const char* name);
void npcBlurOn(const char* name);
void npcSetColor(const char* name, GXColor color);
void npcStartForOneEvent(NpcEntry* npc);
void npcStartForEvent(void);
void npcStopForOneEvent(NpcEntry* npc);
void npcStopForEvent(void);
void npcSetBattleInfo(NpcEntry* npc, s32 battleInfoId);
void npcSetupBattleInfo(NpcEntry* npc, NpcSetupBattleInfo* setup);
BOOL npcCheckInterrupt(NpcEntry* npc);
NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle);
NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r);
void* fbatHitCheck(u32 flags, void* a1);
void fbatHitCheckAll(void);
NpcEntry* fbatNpcTalkCheck(void);
void npcGroupDead(NpcEntry* entry, BOOL reason);
void _npcGroupDead(NpcEntry* entry, s32 reason);
void _npcDead(NpcEntry* npc, s32 reason);
void fbatBattleMode(void);
void fbatTalkMode(void);
void fbatEncountCheck(void);
void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param);
void fbatSetAttackAnnounceEnable(void);
void fbatSetAttackAnnounce(s32 a1);
void fbatChangeMode(s16 mode);
FieldBattleData* fbatGetPointer(void);
NpcEntry* npcNearDistCheck(f32 x, f32 y, f32 z, f32 range);
HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz);
f32 npcTransRytoFaceDir(NpcEntry* npc);
void npcTuningRy(NpcEntry* npc, f32 angle);
void npcMoveG(NpcEntry* npc);
BOOL npcCheckHitMarioSide(NpcEntry* npc);
void npcSetStayPose(const char* name);
void npcSetTalkPose(const char* name);
void npcSetMarioAutoTalkPose(const char* stayPose, const char* talkPose);
NpcEntry* npcNameToPtr_NoAssert(const char* name);
NpcEntry* npcNameToPtr(const char* name);
void npcMain(void);
void npcDeleteGroup(NpcEntry* entry);
void _npcDeleteGroup(NpcEntry* entry);
void npcDelete(NpcEntry* entry);
NpcTribeInfo* npcGetTribe(const char* tribeName);
s32 npcEntry(const char* a1, const char* animName);
s32 npcGetReactionOfLivingBody(BOOL inBattle);
void npcReset(BOOL inBattle);
void npcInit(void);
void npcDisp_blur(CameraId camId, void* param);
void npcDisp_offscreen(CameraId camId, void* param);
void npcDisp_offscreen_xlu(CameraId camId, void* param);
void npcDisp(CameraId camId, void* param);
void npcDisp_xlu(CameraId cameraId, void* param);
void mtx_setup(NpcEntry* entry, Mtx mtx, s32 history);
void npcRecoveryFieldNpc(void);
void npcReleaseFieldNpc(void);
NpcWork* npcGetWorkPtr(void);

#endif