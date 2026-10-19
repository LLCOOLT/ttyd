#pragma optimize_for_size on
#include "battle/battle_seq.h"
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_unit_event.h"
#include "driver/animdrv.h"
#include "driver/mapdrv.h"
#include "eff/eff_nice.h"
#include "battle/battle_database_common.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "mario/mario_party.h"
#include "party.h"
#include "pmario_sound.h"
#include "system.h"
#include "driver/dispdrv.h"
#include "battle/battle_status_effect.h"
#include "driver/msgdrv.h"
#include "driver/windowdrv.h"
#include "manager/fontmgr.h"
#include "driver/camdrv.h"
#include <stdio.h>
#include <string.h>
#ifndef NONMATCHING
#include "mario/mario.h"
__declspec(section ".rodata") extern const f64 double_to_int_802ef590;
__declspec(section ".rodata") extern const char str_802EF5AC[];
__declspec(section ".rodata") extern const char str_802EF5C8[];
__declspec(section ".rodata") extern const char str_802EF5DC[];
__declspec(section ".rodata") extern const char str_802EF5FC[];
__declspec(section ".rodata") extern const char str_802EF604[];
__declspec(section ".rodata") extern const char str_802EF610[];
__declspec(section ".rodata") extern const char str_802EF61C[];
__declspec(section ".rodata") extern const char str_802EF62C[];
__declspec(section ".rodata") extern const u32 gap_04_802EF63C_rodata;
__declspec(section ".sdata2") extern const u32 dat_8041c268;
__declspec(section ".sdata2") extern const u32 dat_8041c26c;
__declspec(section ".sdata2") extern const char str_8041C270[];
__declspec(section ".sdata2") extern const char str_8041C274[];
__declspec(section ".sdata2") extern const char str_8041C27C[];
__declspec(section ".sdata2") extern const f32 float_0_8041c280;
__declspec(section ".sdata2") extern const f32 float_1_8041c284;
__declspec(section ".sdata2") extern const char str_8041C288[];
__declspec(section ".sdata2") extern const f32 float_110_8041c28c;
__declspec(section ".sdata2") extern const f32 float_90_8041c290;
__declspec(section ".sdata2") extern const f32 float_100_8041c294;
__declspec(section ".sdata2") extern const f32 float_1000_8041c298;
__declspec(section ".sdata2") extern const f32 float_2_8041c29c;
__declspec(section ".sdata2") extern const f32 float_10_8041c2a0;
__declspec(section ".sdata2") extern const f32 float_94_8041c2a4;
__declspec(section ".sdata2") extern const f32 float_120_8041c2a8;
__declspec(section ".sdata2") extern const f32 float_900_8041c2ac;
__declspec(section ".sdata2") extern const f32 float_45_8041c2b0;
__declspec(section ".sdata2") extern const f32 float_60_8041c2b4;
__declspec(section ".sdata2") extern const f32 float_0p75_8041c2b8;
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const s32 N_weapon_lucky_start[48];
#define c (*(const GXColor*)&dat_8041c268)
#define color (*(const GXColor*)&dat_8041c26c)
#endif
// G5 keepall: asm stopgap reaches data via section-relative relocs; keep it from being stripped
#pragma force_active on
extern const char str_802EF310[];
extern const char str_802EF320[];
extern const char str_802EF330[];
extern const char str_802EF340[];
extern const char str_802EF350[];
extern const char str_802EF360[];
extern const char str_802EF370[];
extern const char str_802EF380[];
extern const char str_802EF390[];
extern const char str_802EF3A0[];
extern const char str_802EF3B0[];
extern const char str_802EF3C0[];
extern const char str_802EF3D0[];
extern const char str_802EF3E0[];
extern const char str_802EF3F0[];
extern const char str_802EF400[];
extern const char str_802EF410[];
extern const char str_802EF420[];
extern const char str_802EF430[];
extern const char str_802EF440[];
extern const char str_802EF450[];
extern const char str_802EF460[];
extern const char str_802EF470[];
extern const char str_802EF480[];
extern const char str_802EF490[];
extern const char str_802EF4A0[];
extern const char str_802EF4B0[];
extern const char str_802EF4C0[];
extern const char str_802EF4D0[];
extern const char str_802EF4E0[];
extern const char str_802EF4F0[];
extern const char str_802EF500[];
extern const char str_802EF510[];
extern const char str_802EF520[];
extern const char str_802EF530[];
extern const char str_802EF540[];
extern const char str_802EF550[];
extern const char str_802EF560[];
extern const char str_802EF570[];
extern const char str_802EF580[];
extern const char str_802EF598[];

extern BattleWork* _battleWorkPointer;

#define FIELD(p, type, off) (*(type*)((u8*)(p) + (off)))

// subset of BattleStageObjectWork (battle_stage_object.c), lives in BattleWork at 0x180C0
typedef struct BattleSeqStageWork {
	u8 field_0x0[0x20];             // 0x0
	s32 bgDestroyEvtId;             // 0x20
	u8 field_0x24[0x1D8 - 0x24];    // 0x24
	s32 nozzleWorkEvtId;            // 0x1D8
	u8 field_0x1DC[0x1E4 - 0x1DC];  // 0x1DC
	s32 closeWallEvtId;             // 0x1E4
	s32 fallFrameEvtId;             // 0x1E8
	s32 objectFallEvtId;            // 0x1EC
} BattleSeqStageWork;

#define STAGE_WORK(wp) ((BattleSeqStageWork*)(wp)->field_180C0)

// external prototypes
f32 intpl_sub(s32 type, f32 start, f32 end, s32 cur, s32 max);
void mapObjScale(const char* name, f32 x, f32 y, f32 z);
BOOL BattleAfterReactionMain(void);
void BtlActRec_JudgeTurnRuleKeep(void);
void BtlActRec_AddCount(u8* count);
void BattleMajinaiCheck(void);
void BattleFogEndCheck(void);
void BattleStatusWindowEventOn(void);
void BattleStatusWindowSystemOn(void);
void BattleStatusWindowSystemOff(void);
void BattleStatusWindowEventOff(void);
void BattleCommandInit(BattleWork* wp);
BOOL BattleCommandInput(BattleWork* wp);
f32 battleCameraGetPosMoveSpeed(void);
void BattleStatusChangeMsgAdjust(BattleWork* wp);
BOOL BattleStatusChangeMsgMain(BattleWork* wp);
BOOL BattleStatusChangeAnnouceMain(BattleWork* wp);
void BattleConsumeReserveItem(void);
BOOL BattleBreakSlot_CheckReaction(void);
extern s32 btldefaultevt_CantMoveZeroGravity[];
extern s32 btldefaultevt_BiribiriMove[];
void BattleMajinaiDone(void);
void BattleMajinaiEndCheck(void);
extern s32 marioAttackEvent_MajinaiDefenceUp[];
void BtlUnit_SetTotalHitDamage(BattleUnit* unit, s32 damage);
BOOL BtlUnit_CheckShadowGuard(BattleUnit* unit);
s32 BattleDamageDirect(s32 unitIdx, BattleUnit* unit, BattleUnitPart* part, s32 damage, s32 fpDamage, u32 stopFlags, u32 damageEffect, u32 pattern);
void effRecoveryEntry(s32 type, s32 amount, f32 x, f32 y, f32 z);
void effFreezeN64Entry(s32 a, s32 b, f32 x, f32 y, f32 z, f32 scale);
void BattleAudience_Case_TurnEnd(void);
extern s32 subsetevt_status_recovery[];
extern s32 subsetevt_regeneration[];
extern s32 subsetevt_happy_heart[];
extern s32 subsetevt_happy_flower[];
void BattleSetStatusDamageFromWeapon(BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, u32 flags);
extern s32 marioDefaultWeapon_Jump[];
extern s32 marioWeapon_KururinJump[];
extern s32 marioDefaultWeapon_Hammer[];
extern s32 marioDefaultWeapon_FirstAttackKaitenHammer[];
extern s32 marioDefaultWeapon_FirstAttackUltraHammer[];
extern s32 partyWeapon_NokotarouFirstAttack[];
extern s32 partyWeapon_SandersFirstAttack[];

//local prototypes
#ifdef NONMATCHING
USER_FUNC(_set_haikei_entry_scale);
#endif
#ifndef NONMATCHING
s32 _set_haikei_entry_scale(EventEntry* event, BOOL isFirstCall);
#endif
void _mapobj_data_touch_scale(s32 layer);
BOOL BattleCheckConcluded(BattleWork* wp);
BOOL BattleWaitAllActiveEvtEnd_NoBgSetEndWait(BattleWork* wp);
BOOL BattleWaitAllActiveEvtEnd(BattleWork* wp);
void battleMakePhaseEvtTable(BattleWork* wp);
void battleSortPhaseMoveTable(BattleWork* wp, s32 count);
void btlseqPhaseFirstProcess(BattleWork* wp);
void btlseqTurnFirstProcess(BattleWork* wp);
void btlseqAct(BattleWork* wp);
BOOL BattlePhaseEndCheck(void);
void btlseqMove(BattleWork* wp);
void btlseqPhase(BattleWork* wp);
void _rule_disp(CameraId cameraId, void* param);
#ifdef NONMATCHING
USER_FUNC(_set_effect_luck);
#endif
#ifndef NONMATCHING
s32 _set_effect_luck(EventEntry* event, BOOL isFirstCall);
#endif

extern s32 btlevtcmd_WaitEventEnd(EventEntry* event, BOOL isFirstCall);
s32 _set_haikei_entry_scale(EventEntry* event, BOOL isFirstCall);
__declspec(section ".sdata") s32 nanika_luck_event[] = {
	0x1006f, (s32)0xfe363c8f, 0x10009, 0x3c, 0x70, 0x1005b, (s32)_set_effect_luck, 0x2005b,
	(s32)btlevtcmd_WaitEventEnd, (s32)0xfe363c8f, 2, 1,
};
__declspec(section ".sdata") s32 _default_haikei_set_entry_event[] = {
	0x1005b, (s32)_set_haikei_entry_scale, 2, 1,
};

BattleWeapon* _GetFirstAttackWeapon(s32 type);
void BattleCheckAllPinchStatus(BattleWork* wp, BOOL a2);
void btlseqInit(BattleWork* wp);
void btlseqFirstAct(BattleWork* wp);
void btlseqTurn(BattleWork* wp);
void btlseqEnd(BattleWork* wp);

// static data from an inlined header function (see unit_party_sanders.c)
__declspec(section ".data") s32 lbl_80360FE0[] = {
	-1082130432, 1065353216,
};
static __declspec(section ".data") s32 seq_negone_one_374[] = {
	-1082130432, 1065353216,
};
__declspec(section ".data") s32 lbl_80360FF0[] = {
	1065353216, -1082130432,
};
static __declspec(section ".data") s32 seq_one_negone_373[] = {
	1065353216, -1082130432,
};
__declspec(section ".data") s32 lbl_80361000[] = {
	-1082130432, 1065353216,
};
static __declspec(section ".data") s32 seq_negone_one_360[] = {
	-1082130432, 1065353216,
};
__declspec(section ".data") s32 lbl_80361010[] = {
	1065353216, -1082130432,
};
static __declspec(section ".data") s32 seq_one_negone_359[] = {
	1065353216, -1082130432,
};


#ifdef NONMATCHING
static const GXColor c = {0, 0, 0, 0xFF};
static const GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
#endif

#ifndef NONMATCHING
#define S_a str_8041C270
#define S_test str_8041C274
#endif
const char* _rule_msg_table_2bu[] = {
#ifdef NONMATCHING
	"a", str_802EF310, "a", str_802EF320, "a", str_802EF330, str_802EF340, "a",
	"a", "a", "a", "a", "a", "a", "a", "a",
	"a", "a", str_802EF350, "a", "a", "a", "a", "a",
	"a", "a", str_802EF360, "a", "a", "a", "a", "a",
	str_802EF370, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF380, "a", "a", "a", "a",
	str_802EF390, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF3A0, "a", "a", "a", "a",
	"a", "a", "a", "a",
#endif
#ifndef NONMATCHING
	S_a, str_802EF310, S_a, str_802EF320, S_a, str_802EF330, str_802EF340, S_a,
	S_a, S_a, S_a, S_a, S_a, S_a, S_a, S_a,
	S_a, S_a, str_802EF350, S_a, S_a, S_a, S_a, S_a,
	S_a, S_a, str_802EF360, S_a, S_a, S_a, S_a, S_a,
	str_802EF370, S_a, S_a, S_a, S_a, S_a, S_a, S_a,
	S_a, S_a, S_a, str_802EF380, S_a, S_a, S_a, S_a,
	str_802EF390, S_a, S_a, S_a, S_a, S_a, S_a, S_a,
	S_a, S_a, S_a, str_802EF3A0, S_a, S_a, S_a, S_a,
	S_a, S_a, S_a, S_a,
#endif
};

const char* _rule_msg_table_1bu[] = {
#ifdef NONMATCHING
	"test", str_802EF3B0, "a", str_802EF3C0, "a", str_802EF3D0, str_802EF3E0, "a",
	"a", "a", "a", str_802EF3F0, "a", "a", "a", "a",
	"a", "a", str_802EF400, "a", str_802EF410, "a", "a", "a",
	"a", "a", str_802EF420, "a", "a", "a", "a", "a",
	str_802EF430, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF440, "a", "a", "a", "a",
	str_802EF450, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF460, "a", "a", "a", str_802EF470,
	str_802EF480, str_802EF490, "a", "a",
#endif
#ifndef NONMATCHING
	S_test, str_802EF3B0, S_a, str_802EF3C0, S_a, str_802EF3D0, str_802EF3E0, S_a,
	S_a, S_a, S_a, str_802EF3F0, S_a, S_a, S_a, S_a,
	S_a, S_a, str_802EF400, S_a, str_802EF410, S_a, S_a, S_a,
	S_a, S_a, str_802EF420, S_a, S_a, S_a, S_a, S_a,
	str_802EF430, S_a, S_a, S_a, S_a, S_a, S_a, S_a,
	S_a, S_a, S_a, str_802EF440, S_a, S_a, S_a, S_a,
	str_802EF450, S_a, S_a, S_a, S_a, S_a, S_a, S_a,
	S_a, S_a, S_a, str_802EF460, S_a, S_a, S_a, str_802EF470,
	str_802EF480, str_802EF490, S_a, S_a,
#endif
};

const char* _rule_msg_table_after[] = {
#ifdef NONMATCHING
	"a", str_802EF4A0, "a", str_802EF4B0, "a", str_802EF4C0, str_802EF4D0, "a",
	"a", "a", "a", str_802EF4E0, "a", "a", "a", "a",
	"a", "a", str_802EF4F0, "a", str_802EF500, "a", "a", "a",
	"a", "a", str_802EF510, "a", "a", "a", "a", "a",
	str_802EF520, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF530, "a", "a", "a", "a",
	str_802EF540, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF550, "a", "a", "a", str_802EF560,
	str_802EF570, str_802EF580, "a", "a",
#endif
#ifndef NONMATCHING
	S_a, str_802EF4A0, S_a, str_802EF4B0, S_a, str_802EF4C0, str_802EF4D0, S_a,
	S_a, S_a, S_a, str_802EF4E0, S_a, S_a, S_a, S_a,
	S_a, S_a, str_802EF4F0, S_a, str_802EF500, S_a, S_a, S_a,
	S_a, S_a, str_802EF510, S_a, S_a, S_a, S_a, S_a,
	str_802EF520, S_a, S_a, S_a, S_a, S_a, S_a, S_a,
	S_a, S_a, S_a, str_802EF530, S_a, S_a, S_a, S_a,
	str_802EF540, S_a, S_a, S_a, S_a, S_a, S_a, S_a,
	S_a, S_a, S_a, str_802EF550, S_a, S_a, S_a, str_802EF560,
	str_802EF570, str_802EF580, S_a, S_a,
#endif
};

#ifdef NONMATCHING
void BattleSequenceManager(void) { //1:1
	BattleWork* wp = _battleWorkPointer;
	switch (BattleGetSeq(wp, SEQ_UNKNOWN)) {
		case 0:
			btlseqInit(wp);
			BattleCheckAllPinchStatus(wp, TRUE);
			break;
		case 1:
			BattleCheckAllPinchStatus(wp, FALSE);
			btlseqFirstAct(wp);
			break;
		case 2:
			BattleCheckAllPinchStatus(wp, FALSE);
			btlseqTurn(wp);
			break;
		case 3:
			btlseqEnd(wp);
			break;
		case 4:
			break;
	}
}
#endif
#ifndef NONMATCHING
void BattleSequenceManager(void);
#endif

#ifdef NONMATCHING
void BattleCheckAllPinchStatus(BattleWork* wp, BOOL a2) { //1:1, needs stmw forced
	BattleUnit* unit;
	BOOL v6;
	int i;
#endif
#ifndef NONMATCHING
BOOL BattleAudience_CheckReaction(void);
void BattleAudience_PerAct(void);
BOOL BattlePadCheckTrigger(s32 mask);
s32 evtGetValue(EventEntry* entry, s32 index);
void fadeEntry(s32 type, s32 duration, GXColor col);
int sprintf(char *s, const char *format, ...);
void BattleAudience_Case_FirstAttack_Bad(void);
void BattleAudience_Case_FirstAttack_Good(void);
void BattleGetFirstAttackUnit(BattleWork* wp, BattleUnit** a, BattleUnit** b);
void BattleStage_NozzleWorkCheck(s32 a);
void BattleStage_WallCloseCheck(void);
BOOL fadeIsFinish(void);
extern void* jumptable_80361500[];
void BattleCheckAllPinchStatus(BattleWork* wp, BOOL a2);
#endif

#ifdef NONMATCHING
	for (i = 0; i < 64; i++) {
		unit = BattleGetUnitPtr(wp, i);
		if (unit) {
			BtlUnit_CheckPinchStatus(unit, a2);
		}
	}
#endif
#ifndef NONMATCHING
void btlseqInit(BattleWork* wp);
#endif

#ifdef NONMATCHING
	v6 = FALSE;
	for (i = 0; i < 64; i++) {
		unit = BattleGetUnitPtr(wp, i);
		if (unit) {
			if ((unit->mStatusFlags & 0x20000000) &&
				!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL) &&
				!BtlUnit_GetBelong(unit))
			{
				if (unit->currentKind == UNIT_MARIO ||
					unit->currentKind >= TYPE_PARTNER_MIN &&
					unit->currentKind < TYPE_PARTNER_MAX) {
					if (unit->currentHp > 0) {
						v6 = TRUE;
					}
				}
				break;
			}
		}
	}

	if (v6) {
		wp->alertTick--;
		if (wp->alertTick <= 0) {
			wp->alertTick = 60;
			if (wp->commandMenu.field_4 & 1) {
				psndSFXOn("SFX_BTL_DANGER1");
			}
		}
	}
	else {
		v6 = FALSE;
		for (i = 0; i < 64; i++) {
			unit = BattleGetUnitPtr(wp, i);
			if (unit) {
				if ((unit->mStatusFlags & 0x10000000) &&
					!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL) &&
					!BtlUnit_GetBelong(unit))
				{
					if (unit->currentKind == UNIT_MARIO ||
						unit->currentKind >= TYPE_PARTNER_MIN &&
						unit->currentKind < TYPE_PARTNER_MAX) {
						if (unit->currentHp > 0) {
							v6 = TRUE;
						}
					}
					break;
				}
			}
		}
		if (v6) {
			wp->alertTick--;
			if (wp->alertTick <= 0) {
				wp->alertTick = 60;
				if (wp->commandMenu.field_4 & 1) {
					psndSFXOn("SFX_BTL_PINCH1\0\0\0\0\0");
				}
			}
		}
		else {
			unit = BattleGetMarioPtr(wp);
			if (unit) {
				unit->work[8] = 0;
			}
			wp->alertTick = 0;
		}
	}
}

void btlseqInit(BattleWork* wp) { //1:1, needs stmw
	MarioWork* mario;
	PartyEntry* party;

	switch (BattleGetSeq(wp, SEQ_INIT)) {
		case 0x1000000: //continues through to 0x1000001
			BattleSetSeq(wp, SEQ_INIT, 0x1000001);

		case 0x1000001:
			mario = marioGetPtr();
			mario->dispFlags |= 1;
			party = partyGetPtr(marioGetPartyId());
			if (party) {
				party->flags2 |= 1;
			}
			Btl_UnitSetup(wp);
			BattleSetSeq(wp, SEQ_INIT, 0x1000002);
			break;

		case 0x1000002:
			if (BattleCheckEndUnitInitEvent(wp)) {
				BattleSetSeq(wp, SEQ_INIT, 0x1000003u);
			}
			break;

		case 0x1000003:
			if (animEffectAsync("p_b_st", 1) &&
				animEffectAsync("p_jyabara", 1) &&
				animEffectAsync("p_kaiten_h", 1) &&
				effNiceAsync(1))
			{
				BattleSetSeq(wp, SEQ_INIT, 0x1000004);
			}
			break;

		case 0x1000004:
			BattleSetSeq(wp, SEQ_INIT, 0x1000005);
			break;

		case 0x1000005:
			BattleStatusWindowEventOn();
			BattleStatusWindowSystemOn();
			BattleSetSeq(wp, SEQ_UNKNOWN, 1);
			BattleSetSeq(wp, SEQ_FIRST_ACT, 0x2000000);
			break;
	}
}

BattleWeapon* _GetFirstAttackWeapon(s32 type) {
	switch (type) {
		case 1:
			return (BattleWeapon*)marioDefaultWeapon_Jump;
		case 2:
			return (BattleWeapon*)marioWeapon_KururinJump;
		case 3:
			return (BattleWeapon*)marioDefaultWeapon_Jump;
		case 4:
			return (BattleWeapon*)marioDefaultWeapon_Hammer;
		case 5:
			return (BattleWeapon*)marioDefaultWeapon_FirstAttackKaitenHammer;
		case 6:
			return (BattleWeapon*)marioDefaultWeapon_FirstAttackUltraHammer;
		case 7:
			return (BattleWeapon*)partyWeapon_NokotarouFirstAttack;
		case 8:
			return (BattleWeapon*)partyWeapon_SandersFirstAttack;
		case 0:
		default:
			return NULL;
	}
}
#endif
#ifndef NONMATCHING
BattleWeapon* _GetFirstAttackWeapon(s32 type);
#endif


BattleUnit* BattleGetMarioPtr(BattleWork* wp);
void BattleAudience_Case_FirstAttack_Good(void);
void BattleAudience_Case_FirstAttack_Bad(void);
void BattleStage_WallCloseCheck(void);
void BattleStage_NozzleWorkCheck(s32 a);
void BattleGetFirstAttackUnit(BattleWork* wp, BattleUnit** a, BattleUnit** b);
BOOL fadeIsFinish(void);

#define U_EVT(u) FIELD(u, s32*, 0x2B4)
#define U_EVTID(u) FIELD(u, s32, 0x2B8)

#ifdef NONMATCHING
void btlseqFirstAct(BattleWork* wp) {
	s32 type;
	int i;
	BattleUnit* unit;
	BattleUnit* a;
	BattleUnit* b;
	EventEntry* evt;
	int found;
	s32 flag;
	int k;
	u8* fb = (u8*)wp->fbatInfo;
	u8* info;
	type = FIELD(fb, s32, 8);

	switch (BattleGetSeq(wp, SEQ_FIRST_ACT)) {
		case 0x2000000:
			switch (type) {
			case 0:
			{
				wp->ruleDispTimer = 0;
				evtEntry(_default_haikei_set_entry_event, 10, 0);
				info = FIELD(wp->fbatInfo, u8*, 0xC);
				for (i = 0; i < 64; i++) {
					unit = BattleGetUnitPtr(wp, i);
					if (unit && U_EVT(unit)) {
						if ((FIELD(info, u32, 4) & 0x100000) && (unit->currentKind == 0xDE || (unit->currentKind >= 0xE0 && unit->currentKind < 0xE7))) {
							continue;
						}
						if (FIELD(marioGetPtr(), u16, 0x2E) == 0x1A && unit->currentKind == 0xDE) {
							evt = evtEntry((s32*)BtlUnit_GetData(unit, 0x41), 10, 0);
							U_EVTID(unit) = evt->eventId;
							evt->unitId = unit->unitId;
						}
						else {
							evt = evtEntry(U_EVT(unit), 10, 0);
							U_EVTID(unit) = evt->eventId;
							evt->unitId = unit->unitId;
						}
					}
				}
				BattleSetSeq(wp, SEQ_FIRST_ACT, 0x2000001);
				goto done_fa;
			}
			}
			switch (type) {
			case 1: case 2: case 3:
				wp->ruleDispTimer = 10;
				break;
			case 4: case 5: case 6: case 7: case 8:
				wp->ruleDispTimer = 0;
				break;
			default:
				wp->ruleDispTimer = 0;
				break;
			}
			wp->flags |= 2;
			BattleGetFirstAttackUnit(wp, &a, &b);
			wp->activeUnitId = a->unitId;
			FIELD(a, u32, 0x278) |= 0x1000;
			evt = evtEntry(b->damageEventCode, 10, 0x20);
			if (evt) {
				evt->unitId = b->unitId;
				b->damageCode = 0x39;
				b->damageEventId = evt->eventId;
			}
			FIELD(a, u32, 0x1C) |= 0x4000000;
			if (type < 9) {
				FIELD(a, s32, 0x29C) = FIELD(_GetFirstAttackWeapon(type), s32, 0xB0);
				a->attackEventFlags = 0;
				BattleStatusWindowEventOff();
			}
			if (BtlUnit_GetBelong(a) == 0) {
				BattleAudience_Case_FirstAttack_Good();
			}
			else {
				BattleAudience_Case_FirstAttack_Bad();
			}
			evt = evtEntry(a->attackEventCode, 10, 0);
			if (evt) {
				evt->unitId = a->unitId;
				a->attackEventId = evt->eventId;
			}
			switch (type) {
			case 1: case 2: case 3: case 4: case 5: case 6:
				unit = BattleGetPartyPtr(wp);
				if (unit) {
					evt = evtEntry(U_EVT(unit), 10, 0);
					U_EVTID(unit) = evt->eventId;
					evt->unitId = unit->unitId;
				}
				break;
			case 7: case 8:
				unit = BattleGetMarioPtr(wp);
				if (unit) {
					evt = evtEntry(U_EVT(unit), 10, 0);
					U_EVTID(unit) = evt->eventId;
					evt->unitId = unit->unitId;
				}
			}
			BattleSetSeq(wp, SEQ_FIRST_ACT, 0x2000001);
		done_fa:
			break;

		case 0x2000001:
			if (--wp->ruleDispTimer > 0) {
				break;
			}
			{
				fadeEntry(0x17, 200, c);
			}
			wp->field_19060 = ((s32 (*)(const char*))psndSFXOn)("SFX_OFF_BTL_START_CURTAIN_UP1");
			BattleSetSeq(wp, SEQ_FIRST_ACT, 0x2000002);

		case 0x2000002:
			if (fadeIsFinish() && (u32)wp->field_19060 != 0xFFFFFFFFU) {
				psndSFXOff(wp->field_19060);
				wp->field_19060 = -1;
			}
			if (BattleWaitAllActiveEvtEnd(wp)) {
				BattleStatusWindowEventOn();
			}
			if (BattleWaitAllActiveEvtEnd(wp) && fadeIsFinish()) {
				BattleSetSeq(wp, SEQ_FIRST_ACT, 0x2000003);
				unit = BattleGetUnitPtr(wp, wp->activeUnitId);
				if (unit) {
					FIELD(unit, u32, 0x1C) &= ~0x4000000;
				}
			}
			break;

		case 0x2000003:
			if (BattleCheckConcluded(wp)) {
				BattleAudience_PerAct();
				BattleSetSeq(wp, SEQ_UNKNOWN, 3);
				BattleSetSeq(wp, 7, 0x7000000);
				break;
			}
			BattleSetSeq(wp, SEQ_FIRST_ACT, 0x2000004);
			BattleStatusChangeMsgAdjust(wp);

		case 0x2000004:
			if (!BattleWaitAllActiveEvtEnd(wp)) {
				break;
			}
			if (BattleStatusChangeAnnouceMain(wp) | BattleStatusChangeMsgMain(wp)) {
				break;
			}
			BattleIncSeq(wp, SEQ_FIRST_ACT);

		case 0x2000005:
			if (!(wp->flags & 0x30)) {
				BattleStatusWindowSystemOn();
			}
			BattleConsumeReserveItem();
			wp->flags &= ~4;
			BattleAudience_PerAct();
			BattleIncSeq(wp, SEQ_FIRST_ACT);

		case 0x2000006:
			if ((u8)BattleAudience_CheckReaction()) {
				break;
			}
			if (!BattleCheckConcluded(wp) && (u8)BattleBreakSlot_CheckReaction()) {
				break;
			}
			BattleIncSeq(wp, SEQ_FIRST_ACT);

		case 0x2000007:
			if (BattleStatusChangeAnnouceMain(wp) | BattleStatusChangeMsgMain(wp)) {
				break;
			}
			BattleIncSeq(wp, SEQ_FIRST_ACT);

		case 0x2000008:
			if (!BattleWaitAllActiveEvtEnd(wp)) {
				break;
			}
			if (FIELD(FIELD(wp->fbatInfo, u8*, 0xC), u32, 4) & 0x10) {
				BattleSetSeq(wp, SEQ_FIRST_ACT, 0x2000009);
				BattleStage_WallCloseCheck();
			}
			else {
				BattleSetSeq(wp, SEQ_FIRST_ACT, 0x200000A);
			}
			break;

		case 0x2000009:
		{
			s32* id = &FIELD(wp, s32, 0x182A4);
			if (*id != 0 && !evtCheckID(*id)) {
				*id = 0;
			}
			if (*id == 0) {
				BattleSetSeq(wp, SEQ_FIRST_ACT, 0x200000A);
			}
		}
			break;

		case 0x200000A:
			wp->luckEventId = 0;
			flag = 0;
			k = 0;
			do {
				unit = BattleGetUnitPtr(wp, k);
				if (unit && FIELD(unit, u8, 0x300) && !BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL)) {
					flag = 1;
				}
			} while (++k < 64);
			if (flag) {
				evt = evtEntry(nanika_luck_event, 10, 0);
				evt->unitId = -5;
				wp->luckEventId = evt->eventId;
				FIELD(wp, s64, 0x18FD8) |= -1;
				BattleStatusChangeMsgAdjust(wp);
				BattleSetSeq(wp, SEQ_FIRST_ACT, 0x200000B);
				wp->luckTimer = 0;
			}
			else {
				BattleSetSeq(wp, SEQ_FIRST_ACT, 0x200000C);
			}
			break;

		case 0x200000B:
			found = 1;
			if (wp->luckTimer < 300) {
				wp->luckTimer++;
			}
			if (wp->luckEventId != 0) {
				if (evtCheckID(wp->luckEventId)) {
					found = 0;
				}
				else {
					wp->luckEventId = 0;
				}
			}
			if (!BattleWaitAllActiveEvtEnd(wp)) {
				found = 0;
			}
			if (BattleStatusChangeAnnouceMain(wp)) {
				found = 0;
			}
			if (BattleStatusChangeMsgMain(wp)) {
				found = 0;
			}
			if (found) {
				BattleSetSeq(wp, SEQ_FIRST_ACT, 0x200000C);
			}
			break;

		case 0x200000C:
			if (wp->flags & 2) {
				BattleSetSeq(wp, SEQ_FIRST_ACT, 0x200000E);
				break;
			}
			BattleStage_NozzleWorkCheck(0);
			BattleSetSeq(wp, SEQ_FIRST_ACT, 0x200000D);

		case 0x200000D:
			if (!BattleWaitAllActiveEvtEnd(wp)) {
				break;
			}
			BattleSetSeq(wp, SEQ_FIRST_ACT, 0x200000E);

		case 0x200000E:
			wp->flags &= ~2;
			BattleSetSeq(wp, SEQ_UNKNOWN, 2);
			BattleSetSeq(wp, 3, 0x3000000);
			break;
	}
}
#endif
#ifndef NONMATCHING
void btlseqFirstAct(BattleWork* wp);
#endif


//==== written below (reverse order) ====

#ifdef NONMATCHING
const s32 N_weapon_lucky_start[48] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x64000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x01004020, 0x10000000, 0x00000302, 0x00000000, 0x00020108, 0x000007FF, 0x80002004,
	0x00000000, 0x00000000, 0x00000064, 0x03640300, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000302, 0x03020000, 0x00000000, 0x00000064, 0x00000000, 0x00000000,
};
USER_FUNC(_set_effect_luck) {
	BattleWork* wp = _battleWorkPointer;
	f32* pz;
	f32* py;
	BattleWeapon weapon = *(BattleWeapon*)N_weapon_lucky_start;
	f32 z;
	f32 y;
	BattleWeapon* pw;
	f32 x;
	const char* sfx;
	BattleUnit* unit;
	BattleUnitPart* part;
	NiceEffectWork* effect;
	int i;

	sfx = (0, "SFX_SYSTEM_LUCKY1");
	pw = &weapon;
	pz = &z;
	py = &y;
	for (i = 0; i < 64; i++) {
		unit = BattleGetUnitPtr(wp, i);
		if (unit && unit->badgesEquipped.LuckyStart && !BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL)) {
			switch (irand(4)) {
				case 0:
					weapon.dodgyChance = 0;
					weapon.dodgyTime = 0;
					weapon.hpRegenTime = 0;
					weapon.hpRegenStrength = 0;
					weapon.fpRegenTime = 0;
					weapon.fpRegenStrength = 0;
					break;
				case 1:
					weapon.electricChance = 0;
					weapon.electricTime = 0;
					weapon.hpRegenTime = 0;
					weapon.hpRegenStrength = 0;
					weapon.fpRegenTime = 0;
					weapon.fpRegenStrength = 0;
					break;
				case 2:
					weapon.electricChance = 0;
					weapon.electricTime = 0;
					weapon.dodgyChance = 0;
					weapon.dodgyTime = 0;
					weapon.fpRegenTime = 0;
					weapon.fpRegenStrength = 0;
					break;
				default:
					weapon.electricChance = 0;
					weapon.electricTime = 0;
					weapon.dodgyChance = 0;
					weapon.dodgyTime = 0;
					weapon.hpRegenTime = 0;
					weapon.hpRegenStrength = 0;
					break;
			}
			part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
			BattleSetStatusDamageFromWeapon(BattleGetSystemPtr(wp), unit, part, pw, 0x100);
			BtlUnit_GetPos(unit, &x, py, pz);
			psndSFXOn(sfx);
			{
				EffectEntry* e = effNiceEntry(6, x - 45.0f, 60.0f + y, z);
				effect = e->userdata;
				effect->field_0x1C = 0.75f;
			}
		}
	}
	return EVT_RETURN_DONE;
}
#endif
#ifndef NONMATCHING
s32 _set_effect_luck(EventEntry* event, BOOL isFirstCall);
#endif


#define TURN_NEXT(wp) \
	BattleIncSeq(wp, SEQ_TURN); \
	btlseqTurn(wp)

#define TURN_SKIP(wp) \
	BattleIncSeq(wp, SEQ_TURN); \
	BattleIncSeq(wp, SEQ_TURN); \
	btlseqTurn(wp)

#define TURN_WAIT_CASE(wp) \
	if (!BattleWaitAllActiveEvtEnd(wp)) { \
		break; \
	} \
	if (BattleCheckConcluded(wp)) { \
		BattleSetSeq(wp, SEQ_UNKNOWN, 3); \
		BattleSetSeq(wp, SEQ_END, 0x7000000); \
	} \
	else { \
		BattleIncSeq(wp, SEQ_TURN); \
	} \
	break

#define TURN_RECOVERY_CASE(wp, status) \
	for (i = 0; i < 64; i++) { \
		unit = BattleGetUnitPtr(wp, i); \
		ret = BtlUnit_CheckRecoveryStatus(unit, status); \
		sfx |= ret; \
		if (ret) { \
			evt = evtEntry(subsetevt_status_recovery, 10, 0); \
			if (evt) { \
				unit->attackEventId = evt->eventId; \
				evt->unitId = unit->unitId; \
			} \
			found = TRUE; \
		} \
	} \
	if (sfx) { \
		psndSFXOn(str_802EF598); \
	} \
	if (!found) { \
		TURN_SKIP(wp); \
		break; \
	} \
	TURN_NEXT(wp); \
	break

#define TURN_RECOVERY_CASE2(wp, status) \
	for (i = 0; i < 64; i++) { \
		unit = BattleGetUnitPtr(wp, i); \
		if (unit) { \
			ret = BtlUnit_CheckRecoveryStatus(unit, status); \
			sfx |= ret; \
			if (ret) { \
				evt = evtEntry(subsetevt_status_recovery, 10, 0); \
				if (evt) { \
					unit->attackEventId = evt->eventId; \
					evt->unitId = unit->unitId; \
				} \
				found = TRUE; \
			} \
		} \
	} \
	if (sfx) { \
		psndSFXOn(str_802EF598); \
	} \
	if (!found) { \
		TURN_SKIP(wp); \
		break; \
	} \
	TURN_NEXT(wp); \
	break

#define TURN_COMMAND_DISABLED_CASE(wp, n) \
	if (wp->commandDisabled[n]) { \
		wp->commandDisabled[n]--; \
	} \
	TURN_SKIP(wp); \
	break

#ifdef NONMATCHING
void btlseqTurn(BattleWork *wp)
{
  Vec pos;
  f32 hpX;
  f32 hpY;
  f32 hpZ;
  f32 fpX;
  f32 fpY;
  f32 fpZ;
  f32 heartX;
  f32 heartY;
  f32 heartZ;
  f32 flowerX;
  f32 flowerY;
  f32 flowerZ;
  s8 turns;
  s8 strength;
  BattleUnit *unit;
  EventEntry *evt;
  BOOL found;
  BOOL sfx;
  BOOL ret;
  BOOL done;
  s32 count;
  s32 n;
  s32 rate;
  int i;
  found = 0;
  sfx = 0;
  switch (BattleGetSeq(wp, SEQ_TURN))
  {
    case 0x3000000:
      BattleIncSeq(wp, SEQ_TURN);
      break;

    case 0x3000001:
      btlseqTurnFirstProcess(wp);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000003:
      if (wp->turnCount != 1)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      if (wp->fbatInfo->field_0x18 == 0)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      wp->ruleDispTimer = 120;
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000004:
      if (wp->ruleDispTimer)
    {
      wp->ruleDispTimer--;
    }
      if ((wp->ruleDispTimer <= 0) || BattlePadCheckTrigger(0x300))
    {
      BattleIncSeq(wp, SEQ_TURN);
      break;
    }
      dispEntry(CAMERA_2D, 900.0f, 1, _rule_disp, (void *) 0);
      break;

    case 0x3000002:
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000005:
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000007:

    case 0x300000B:

    case 0x300000D:

    case 0x300000F:

    case 0x3000011:

    case 0x3000013:

    case 0x3000015:

    case 0x3000017:

    case 0x3000019:

    case 0x300001B:

    case 0x300001D:

    case 0x300001F:

    case 0x3000021:

    case 0x3000023:

    case 0x3000025:

    case 0x3000027:

    case 0x3000029:

    case 0x300002B:

    case 0x300002D:

    case 0x300002F:

    case 0x3000031:

    case 0x3000033:

    case 0x3000035:

    case 0x3000037:

    case 0x3000039:

    case 0x300003B:

    case 0x300003D:

    case 0x300003F:

    case 0x3000041:

    case 0x3000043:

    case 0x3000045:

    case 0x3000047:

    case 0x3000049:
      if (!BattleWaitAllActiveEvtEnd(wp))
    {
      break;
    }
      if (BattleCheckConcluded(wp))
    {
      BattleSetSeq(wp, SEQ_UNKNOWN, 3);
      BattleSetSeq(wp, SEQ_END, 0x7000000);
    }
    else
    {
      BattleIncSeq(wp, SEQ_TURN);
    }
      break;

    case 0x3000012:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 1);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      break;

    case 0x3000014:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 2);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000016:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 3);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000018:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 5);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300001A:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 6);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300001C:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 7);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300001E:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 8);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
 dummy_label_899231: ;
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000020:
    {
      BattleUnit *unit;
      const char *sfxName = (0, "SFX_CONDITION_BREAK_ICE1");
      for (i = 0; i < 64; i++)
      {
        unit = BattleGetUnitPtr(wp, i);
        if (BtlUnit_CheckRecoveryStatus(unit, 9))
        {
          if (!BtlUnit_CheckShadowGuard(unit))
          {
            BattleDamageDirect(-5, unit, (void *) 0, 1, 0, 0x11A, 0, 1);
          }
          BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
          pos.y += BtlUnit_GetHeight(unit);
          effFreezeN64Entry(0, 1, pos.x, pos.y, pos.z, 1.0f);
          psndSFXOn_3D(sfxName, &pos);
          found = 1;
        }
      }

      if (!found)
      {
        BattleIncSeq(wp, SEQ_TURN);
        BattleIncSeq(wp, SEQ_TURN);
        btlseqTurn(wp);
        break;
      }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }

    case 0x3000022:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 10);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000024:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 11);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000026:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 4);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000028:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 12);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300002A:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 13);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300002C:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 14);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300002E:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 15);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000030:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      ret = BtlUnit_CheckRecoveryStatus(unit, 0);
      sfx |= ret;
      if (ret)
      {
        evt = evtEntry(subsetevt_status_recovery, 10, 0);
        if (evt)
        {
          unit->attackEventId = evt->eventId;
          evt->unitId = unit->unitId;
        }
        found = 1;
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000032:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if (unit)
      {
        ret = BtlUnit_CheckRecoveryStatus(unit, 0x17);
        sfx |= ret;
        if (ret)
        {
          evt = evtEntry(subsetevt_status_recovery, 10, 0);
          if (evt)
          {
            unit->attackEventId = evt->eventId;
            evt->unitId = unit->unitId;
          }
          found = 1;
        }
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000034:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if (unit)
      {
        ret = BtlUnit_CheckRecoveryStatus(unit, 0x18);
        sfx |= ret;
        if (ret)
        {
          evt = evtEntry(subsetevt_status_recovery, 10, 0);
          if (evt)
          {
            unit->attackEventId = evt->eventId;
            evt->unitId = unit->unitId;
          }
          found = 1;
        }
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000036:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if (unit)
      {
        ret = BtlUnit_CheckRecoveryStatus(unit, 0x12);
        sfx |= ret;
        if (ret)
        {
          evt = evtEntry(subsetevt_status_recovery, 10, 0);
          if (evt)
          {
            unit->attackEventId = evt->eventId;
            evt->unitId = unit->unitId;
          }
          found = 1;
        }
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000038:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if (unit)
      {
        ret = BtlUnit_CheckRecoveryStatus(unit, 0x13);
        sfx |= ret;
        if (ret)
        {
          evt = evtEntry(subsetevt_status_recovery, 10, 0);
          if (evt)
          {
            unit->attackEventId = evt->eventId;
            evt->unitId = unit->unitId;
          }
          found = 1;
        }
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300003A:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if (unit)
      {
        ret = BtlUnit_CheckRecoveryStatus(unit, 0x14);
        sfx |= ret;
        if (ret)
        {
          BtlUnit_ResetMoveStatus(unit);
          evt = evtEntry(subsetevt_status_recovery, 10, 0);
          if (evt)
          {
            unit->attackEventId = evt->eventId;
            evt->unitId = unit->unitId;
          }
          found = 1;
        }
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300003C:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if (unit)
      {
        ret = BtlUnit_CheckRecoveryStatus(unit, 0x15);
        sfx |= ret;
        if (ret)
        {
          evt = evtEntry(subsetevt_status_recovery, 10, 0);
          if (evt)
          {
            unit->attackEventId = evt->eventId;
            evt->unitId = unit->unitId;
          }
          found = 1;
        }
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300003E:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if (unit)
      {
        ret = BtlUnit_CheckRecoveryStatus(unit, 0x16);
        sfx |= ret;
        if (ret)
        {
          evt = evtEntry(subsetevt_status_recovery, 10, 0);
          if (evt)
          {
            unit->attackEventId = evt->eventId;
            evt->unitId = unit->unitId;
          }
          found = 1;
        }
      }
    }

      if (sfx)
    {
      psndSFXOn("SFX_REST_CONDITION1");
    }
      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000006:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if ((unit && (!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL))) && (unit->currentHp > 0))
      {
        BtlUnit_GetStatus(unit, 4, &turns, &strength);
        if ((strength > 0) && (!BtlUnit_CheckShadowGuard(unit)))
        {
          found = 1;
          BattleDamageDirect(-5, unit, (void *) 0, strength, 0, 0x117, 0, 1);
        }
      }
    }

      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000008:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if ((unit && (!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL))) && (unit->currentHp > 0))
      {
        BtlUnit_GetStatus(unit, 8, &turns, &strength);
        if (strength > 0)
        {
          found = 1;
          break;
        }
      }
    }

      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      wp->turnSubSeq = 0;
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000009:
      switch (wp->turnSubSeq)
    {
      case 0:
        wp->turnSubSeq++;
        for (i = 0; i < 64; i++)
      {
        unit = BattleGetUnitPtr(wp, i);
        if ((unit && (!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL))) && (unit->currentHp > 0))
        {
          BtlUnit_GetStatus(unit, 8, &turns, &strength);
          if (strength > 0)
          {
            BSE_TurnFirstProcessEffectEntry(unit, 1);
          }
        }
      }
#endif
#ifndef NONMATCHING
void btlseqAct(BattleWork* wp);
__declspec(section ".data") static void* jumptable_80361350[] = {
    (char*)btlseqAct + 0x40,
    (char*)btlseqAct + 0x1FC,
    (char*)btlseqAct + 0x220,
    (char*)btlseqAct + 0x290,
    (char*)btlseqAct + 0x2C8,
    (char*)btlseqAct + 0x254,
    (char*)btlseqAct + 0x304,
    (char*)btlseqAct + 0x500,
    (char*)btlseqAct + 0x524,
    (char*)btlseqAct + 0x55C,
    (char*)btlseqAct + 0x760,
    (char*)btlseqAct + 0x794,
    (char*)btlseqAct + 0x7BC,
    (char*)btlseqAct + 0x83C,
    (char*)btlseqAct + 0x87C,
};
void btlseqMove(BattleWork* wp);
__declspec(section ".data") static void* jumptable_8036138C[] = {
    (char*)btlseqMove + 0x48,
    (char*)btlseqMove + 0x64,
    (char*)btlseqMove + 0x78,
    (char*)btlseqMove + 0x114,
    (char*)btlseqMove + 0x138,
    (char*)btlseqMove + 0x184,
    (char*)btlseqMove + 0x1A8,
    (char*)btlseqMove + 0x23C,
    (char*)btlseqMove + 0x29C,
    (char*)btlseqMove + 0x4FC,
    (char*)btlseqMove + 0x508,
    (char*)btlseqMove + 0x5E0,
    (char*)btlseqMove + 0x60C,
    (char*)btlseqMove + 0x648,
    (char*)btlseqMove + 0x658,
};
__declspec(section ".data") static void* jumptable_803613C8[] = {
    (char*)btlseqTurn + 0x48,
    (char*)btlseqTurn + 0x58,
    (char*)btlseqTurn + 0x15C,
    (char*)btlseqTurn + 0x78,
    (char*)btlseqTurn + 0xFC,
    (char*)btlseqTurn + 0x174,
    (char*)btlseqTurn + 0x1388,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1468,
    (char*)btlseqTurn + 0x151C,
    (char*)btlseqTurn + 0x1650,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x17F8,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1954,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1B0C,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1E0,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x298,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x358,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x418,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x4D8,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x598,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x658,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x718,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x840,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x900,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x9C0,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0xA80,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0xB40,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0xC00,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0xCC0,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0xD80,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0xE40,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0xF00,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0xFC0,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1080,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1140,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1208,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x12C8,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1CB8,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1CF4,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1D30,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1D6C,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1DA8,
    (char*)btlseqTurn + 0x18C,
    (char*)btlseqTurn + 0x1DE4,
    (char*)btlseqTurn + 0x1DFC,
    (char*)btlseqTurn + 0x1E1C,
    (char*)btlseqTurn + 0x1E28,
};
__declspec(section ".data") void* jumptable_80361500[] = {
    (char*)btlseqFirstAct + 0x48,
    (char*)btlseqFirstAct + 0x32C,
    (char*)btlseqFirstAct + 0x37C,
    (char*)btlseqFirstAct + 0x414,
    (char*)btlseqFirstAct + 0x468,
    (char*)btlseqFirstAct + 0x4A0,
    (char*)btlseqFirstAct + 0x4D0,
    (char*)btlseqFirstAct + 0x504,
    (char*)btlseqFirstAct + 0x52C,
    (char*)btlseqFirstAct + 0x584,
    (char*)btlseqFirstAct + 0x5CC,
    (char*)btlseqFirstAct + 0x6AC,
    (char*)btlseqFirstAct + 0x754,
    (char*)btlseqFirstAct + 0x794,
    (char*)btlseqFirstAct + 0x7B8,
};
BattleWeapon* _GetFirstAttackWeapon(s32 type);
__declspec(section ".data") static void* jumptable_8036153C[] = {
    (char*)_GetFirstAttackWeapon + 0x80,
    (char*)_GetFirstAttackWeapon + 0x20,
    (char*)_GetFirstAttackWeapon + 0x2C,
    (char*)_GetFirstAttackWeapon + 0x38,
    (char*)_GetFirstAttackWeapon + 0x44,
    (char*)_GetFirstAttackWeapon + 0x50,
    (char*)_GetFirstAttackWeapon + 0x5C,
    (char*)_GetFirstAttackWeapon + 0x68,
    (char*)_GetFirstAttackWeapon + 0x74,
};
void btlseqTurn(BattleWork *wp);
#endif


#ifdef NONMATCHING
      case 1:
        done = 1;
        for (i = 0; i < 64; i++)
      {
        unit = BattleGetUnitPtr(wp, i);
        if (unit && BSE_TurnFirstProcessEffectMain(unit))
        {
          done = 0;
        }
      }

        if (done)
      {
        wp->turnSubSeq++;
      }
        break;

      default:
        if (!BattleWaitAllActiveEvtEnd(wp))
      {
        break;
      }
        if (BattleCheckConcluded(wp))
      {
        BattleSetSeq(wp, SEQ_UNKNOWN, 3);
        BattleSetSeq(wp, SEQ_END, 0x7000000);
      }
      else
      {
        BattleIncSeq(wp, SEQ_TURN);
      }
        break;

    }

      break;

    case 0x300000A:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if ((unit && (!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL))) && (unit->currentHp > 0))
      {
        BtlUnit_GetStatus(unit, 0x17, &turns, &strength);
        if (strength > 0)
        {
          if (!(unit->mAttributeFlags & 0x40000000))
          {
            unit->hpGauge.field_0xC = unit->currentHp;
            BtlUnit_RecoverHp(unit, strength);
            unit->hpGauge.field_0x10 = unit->currentHp;
            unit->hpGauge.field_0x4 = unit->hpGauge.field_0x6;
            unit->hpGauge.field_0x8 = unit->hpGauge.field_0xA;
            unit->hpGauge.field_0x2 |= 1;
          }
          else
          {
            BtlUnit_RecoverHp(unit, strength);
          }
          BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &hpX, &hpY, &hpZ);
          hpY += unit->mSizeMultiplier * (BtlUnit_GetHeight(unit) + 5);
          effRecoveryEntry(0, strength, hpX, hpY, hpZ);
          evt = evtEntry(subsetevt_regeneration, 10, 0);
          if (evt)
          {
            unit->attackEventId = evt->eventId;
            evt->unitId = unit->unitId;
          }
          found = 1;
        }
      }
    }

      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300000C:
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if ((unit && (!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL))) && (unit->currentHp > 0))
      {
        BtlUnit_GetStatus(unit, 0x18, &turns, &strength);
        if (strength > 0)
        {
          BtlUnit_RecoverFp(unit, strength);
          BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &fpX, &fpY, &fpZ);
          fpY += unit->mSizeMultiplier * (BtlUnit_GetHeight(unit) + 5);
          effRecoveryEntry(1, strength, fpX, fpY, fpZ);
          evt = evtEntry(subsetevt_regeneration, 10, 0);
          if (evt)
          {
            unit->attackEventId = evt->eventId;
            evt->unitId = unit->unitId;
          }
          found = 1;
        }
      }
    }

      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300000E:
      if (wp->turnCount <= 1)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if ((unit && (!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL))) && (unit->currentHp > 0))
      {
        n = 0;
        for (count = unit->badgesEquipped.HappyHeart; count > 0; count--)
        {
          rate = 33 - ((unit->currentHp / unit->maxHp) * 3);
          if (irand(100) < rate)
          {
            n++;
          }
        }

        if (n > 0)
        {
          unit->currentHp += n;
          if (unit->currentHp > unit->maxHp)
          {
            unit->currentHp = unit->maxHp;
          }
          BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &heartX, &heartY, &heartZ);
          heartY += unit->mSizeMultiplier * BtlUnit_GetHeight(unit);
          effRecoveryEntry(0, n, heartX, heartY, heartZ);
          evt = evtEntry(subsetevt_happy_heart, 10, 0);
          if (evt)
          {
            unit->attackEventId = evt->eventId;
            evt->unitId = unit->unitId;
          }
          found = 1;
        }
      }
    }

      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      break;

    case 0x3000010:
      if (wp->turnCount <= 1)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      for (i = 0; i < 64; i++)
    {
      unit = BattleGetUnitPtr(wp, i);
      if ((unit && (!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL))) && (unit->currentHp > 0))
      {
        n = 0;
        for (rate = unit->badgesEquipped.HappyFlower; rate > 0; rate--)
        {
          count = 33 - ((unit->currentFp / unit->maxFp) * 3);
          if (irand(100) < count)
          {
            n++;
          }
        }

        if (n > 0)
        {
          BtlUnit_RecoverFp(unit, n);
          BtlUnit_GetPartsWorldPos(BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), &flowerX, &flowerY, &flowerZ);
          flowerY += unit->mSizeMultiplier * BtlUnit_GetHeight(unit);
          effRecoveryEntry(1, n, flowerX, flowerY, flowerZ);
          evt = evtEntry(subsetevt_happy_flower, 10, 0);
          if (evt)
          {
            unit->attackEventId = evt->eventId;
            evt->unitId = unit->unitId;
          }
          found = 1;
        }
      }
    }

      if (!found)
    {
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;
    }
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000040:
      if (wp->commandDisabled[0])
    {
      wp->commandDisabled[0]--;
    }
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000042:
      if (wp->commandDisabled[1])
    {
      wp->commandDisabled[1]--;
    }
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000044:
      if (wp->commandDisabled[2])
    {
      wp->commandDisabled[2]--;
    }
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000046:
      if (wp->commandDisabled[3])
    {
      wp->commandDisabled[3]--;
    }
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x3000048:
      if (wp->commandDisabled[4])
    {
      wp->commandDisabled[4]--;
    }
      BattleIncSeq(wp, SEQ_TURN);
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300004A:
      BattleIncSeq(wp, SEQ_TURN);
      btlseqTurn(wp);
      break;

    case 0x300004B:
      BattleIncSeq(wp, SEQ_TURN);
      BattleSetSeq(wp, SEQ_PHASE, 0x4000000);
      break;

    case 0x300004C:
      btlseqPhase(wp);
      break;

    case 0x300004D:
      BattleAudience_Case_TurnEnd();
      BattleSetSeq(wp, SEQ_TURN, 0x3000001);
      wp->flags &= ~0x2000;
      break;

  }

}
#endif
#ifndef NONMATCHING
void _rule_disp(CameraId cameraId, void* param);
#endif


#ifdef NONMATCHING
void _rule_disp(CameraId cameraId, void* param) {
	FieldBattleInfo* info = _battleWorkPointer->fbatInfo;
	char buf[256];
	f32 x;
	f32 y;
	u16 lines;
	u16 width;
#endif
#ifndef NONMATCHING
void btlseqPhase(BattleWork* wp);
#endif

#ifdef NONMATCHING
	if (evtGetValue(NULL, GSW(0)) < 0xAC) {
		if (evtGetValue(NULL, GSW(580)) < 11) {
			sprintf(buf, msgSearch(_rule_msg_table_1bu[info->field_0x18]), info->field_0x1A);
		}
		else {
			sprintf(buf, msgSearch(_rule_msg_table_2bu[info->field_0x18]), info->field_0x1A);
		}
	}
	else {
		sprintf(buf, msgSearch(_rule_msg_table_after[info->field_0x18]), info->field_0x1A);
	}
	width = FontGetMessageWidthLine(buf, &lines);
	lines++;
	y = 0.0f;
	x = y - (f32)(width / 2);
	windowDispGX_Waku_col(0, color, x - 10.0f, 94.0f, (f32)(width + 20), (f32)(lines * 29 + 3), 10.0f);
	FontDrawStart();
	y = 120.0f;
	FontDrawMessage((s32)x, (s32)y - 29, buf);
}
#endif
#ifndef NONMATCHING
void btlseqMove(BattleWork* wp);
#endif


#ifdef NONMATCHING
void btlseqPhase(BattleWork* wp) {
	switch (BattleGetSeq(wp, SEQ_PHASE)) {
		case 0x4000000:
			BattleIncSeq(wp, SEQ_PHASE);
			BattleSetSeq(wp, SEQ_MOVE, 0x5000000);
			break;
		case 0x4000001:
		case 0x4000002:
		case 0x4000003:
		case 0x4000004:
		case 0x4000005:
			btlseqMove(wp);
			break;
		case 0x4000006:
			BattleIncSeq(wp, SEQ_TURN);
			BattleSetSeq(wp, SEQ_PHASE, 0x4000000);
			break;
	}
}
#endif
#ifndef NONMATCHING
BOOL BattlePhaseEndCheck(void);
#endif

#ifdef NONMATCHING
void btlseqMove(BattleWork* wp) {
	int j;
	BattleUnit* unit;
	PouchData* pouch;
	BattleUnit* mario;
	EventEntry* evt;
	BOOL loop;
	s32 id;
	s32 state;
	BOOL end;
	int i;

	do {
		loop = FALSE;
		switch (BattleGetSeq(wp, SEQ_MOVE)) {
			case 0x5000000:
				btlseqPhaseFirstProcess(wp);
				BattleIncSeq(wp, SEQ_MOVE);
				loop = TRUE;
				break;
			case 0x5000001:
				BattleIncSeq(wp, SEQ_MOVE);
				loop = TRUE;
				break;
			case 0x5000002:
				pouch = pouchGetPtr();
				mario = BattleGetMarioPtr(wp);
				if (pouch->mMerleeNextCurseType != 2 || BattleGetSeq(wp, SEQ_PHASE) != 0x4000004) {
					BattleIncSeq(wp, SEQ_MOVE);
					BattleIncSeq(wp, SEQ_MOVE);
					loop = TRUE;
					break;
				}
				wp->majinaiState = 2;
				BattleMajinaiDone();
				BattleMajinaiEndCheck();
				evt = evtEntry(marioAttackEvent_MajinaiDefenceUp, 10, 0);
				evt->unitId = mario->unitId;
				mario->attackEventId = evt->eventId;
				BattleIncSeq(wp, SEQ_MOVE);
			case 0x5000003:
				if (!BattleWaitAllActiveEvtEnd(wp)) {
					break;
				}
				BattleIncSeq(wp, SEQ_MOVE);
				loop = TRUE;
				break;
			case 0x5000004:
				for (j = 0; j < 64; j++) {
					unit = BattleGetUnitPtr(wp, j);
					if (unit && unit->unisonPhaseEventCode) {
						BattleRunPhaseEvent(unit, TRUE);
					}
				}
				BattleIncSeq(wp, SEQ_MOVE);
				loop = TRUE;
				break;
			case 0x5000005:
				if (!BattleWaitAllActiveEvtEnd(wp)) {
					break;
				}
				BattleIncSeq(wp, SEQ_MOVE);
				loop = TRUE;
				break;
			case 0x5000006:
				for (i = 0; i < 64; i++) {
					if (wp->phaseEvtTable[i].unitId != -1) {
						unit = BattleGetUnitPtr(wp, wp->phaseEvtTable[i].unitId);
						if (unit && unit->phaseEventCode) {
							break;
						}
					}
				}
				if (i < 64) {
					BattleRunPhaseEvent(unit, FALSE);
					wp->phaseEvtTable[i].unitId = -1;
					BattleIncSeq(wp, SEQ_MOVE);
				}
				else {
					BattleSetSeq(wp, SEQ_MOVE, 0x500000A);
					loop = TRUE;
				}
				break;
			case 0x5000007:
				if (!BattleWaitAllActiveEvtEnd(wp)) {
					break;
				}
				if (BattleCheckConcluded(wp)) {
					BattleSetSeq(wp, SEQ_UNKNOWN, 3);
					BattleSetSeq(wp, SEQ_END, 0x7000000);
				}
				else {
					BattleSetSeq(wp, SEQ_MOVE, 0x5000006);
					loop = TRUE;
				}
				break;
			case 0x5000008:
				memset(&wp->impendingBonuses, 0, sizeof(wp->impendingBonuses));
				for (i = 0; i < 64; i++) {
					unit = BattleGetUnitPtr(wp, i);
					if (unit) {
						unit->mTokenFlags &= 0x80002000;
						unit->totalHpDamageTaken = 0;
						unit->hpDamageTaken = 0;
						unit->hpDamageCount = 0;
						FIELD(unit, s8, 0x26F) = 0;
						FIELD(unit, s32, 0x264) = 0;
						unit->fpDamageTaken = 0;
						FIELD(unit, s32, 0x268) = 0;
						FIELD(unit, s8, 0x26E) = 0;
						FIELD(unit, s32, 0x27C) = 0;
					}
				}
				for (i = 0; i < 64; i++) {
					id = wp->movePriorityQueue[i];
					if (id != -1) {
						unit = BattleGetUnitPtr(wp, id);
						if (unit && unit->movesRemaining > 0) {
							state = unit->moveState;
							if (state != 10 && (!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL) || (unit->mAttributeFlags & 0x10000))) {
								if (state != 1) {
									break;
								}
								unit->moveState = 0;
							}
						}
					}
				}
				wp->activeUnitId = id;
				BattleGetUnitPtr(wp, id)->mTokenFlags |= 0x1000;
				BattleIncSeq(wp, SEQ_MOVE);
				BattleSetSeq(wp, SEQ_ACT, 0x6000000);
				for (i = 0; i < 64; i++) {
					id = wp->movePriorityQueue[i];
					if (id != -1) {
						unit = BattleGetUnitPtr(wp, id);
						if (unit && unit->moveState == 1) {
							unit->moveState = 0;
						}
					}
				}
				unit = BattleGetUnitPtr(wp, wp->activeUnitId);
				if (unit->currentKind == UNIT_MARIO) {
					pouch = pouchGetPtr();
					wp->flags |= 0x600;
					for (i = 0; i < 200; i++) {
						if (pouch->equippedBadges[i] >= 0xF0 && pouch->equippedBadges[i] < 0xF7) {
							wp->flags &= ~0x200;
							break;
						}
					}
					if (pouch->jumpLevel >= 2) {
						wp->flags &= ~0x200;
					}
					for (i = 0; i < 200; i++) {
						if (pouch->equippedBadges[i] >= 0xF7 && pouch->equippedBadges[i] < 0xFE) {
							wp->flags &= ~0x400;
							break;
						}
					}
					if (pouch->hammerLevel >= 2) {
						wp->flags &= ~0x400;
					}
				}
				break;
			case 0x5000009:
				btlseqAct(wp);
				break;
			case 0x500000A:
				if (BattleCheckConcluded(wp)) {
					BattleSetSeq(wp, SEQ_UNKNOWN, 3);
					BattleSetSeq(wp, SEQ_END, 0x7000000);
					break;
				}
				for (i = 0; i < 64; i++) {
					unit = BattleGetUnitPtr(wp, i);
					if (unit) {
						BtlUnit_SetTotalHitDamage(unit, 0);
						unit->mTokenFlags &= ~0x1000;
					}
				}
				end = BattlePhaseEndCheck();
				if (wp->flags & 0x2000) {
					end = TRUE;
				}
				if (end) {
					if (wp->majinaiState == 2) {
						wp->majinaiState = 0;
					}
					BattleAudience_PerPhase(BattleGetSeq(wp, SEQ_PHASE));
					BattleIncSeq(wp, SEQ_MOVE);
				}
				else {
					BattleSetSeq(wp, SEQ_MOVE, 0x5000008);
				}
				break;
			case 0x500000B:
				if ((u8)BattleAudience_CheckReactionPerPhase()) {
					break;
				}
				if (!BattleWaitAllActiveEvtEnd(wp)) {
					break;
				}
				BattleIncSeq(wp, SEQ_MOVE);
				break;
			case 0x500000C:
				if (BattleStatusChangeAnnouceMain(wp) | BattleStatusChangeMsgMain(wp)) {
					break;
				}
				BattleIncSeq(wp, SEQ_PHASE);
				BattleSetSeq(wp, SEQ_MOVE, 0x5000000);
				break;
			case 0x500000D:
				BattleIncSeq(wp, SEQ_MOVE);
				break;
			case 0x500000E:
				BattleIncSeq(wp, SEQ_PHASE);
				BattleSetSeq(wp, SEQ_MOVE, 0x5000000);
				break;
		}
	} while (loop);
}
#endif
#ifndef NONMATCHING
void btlseqAct(BattleWork* wp);
#endif


#ifdef NONMATCHING
BOOL BattlePhaseEndCheck(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleUnit* unit;
	int i;
#endif
#ifndef NONMATCHING
void btlseqTurnFirstProcess(BattleWork* wp);
#endif

#ifdef NONMATCHING
	for (i = 0; i < 64; i++) {
		if (wp->movePriorityQueue[i] != -1) {
			unit = BattleGetUnitPtr(wp, wp->movePriorityQueue[i]);
			if (unit && unit->moveState != 10 && unit->movesRemaining > 0 &&
				!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL)) {
				break;
			}
		}
	}
	if (i >= 64) {
		return TRUE;
	}
	return FALSE;
}
#endif
#ifndef NONMATCHING
void btlseqPhaseFirstProcess(BattleWork* wp);
#endif

#ifdef NONMATCHING
void btlseqAct(BattleWork* wp) {
	BattleUnit* unit;
	EventEntry* evt;
	BOOL cantMove;
	BOOL decrement;
#endif
#ifndef NONMATCHING
void battleSortPhaseMoveTable(BattleWork* wp, s32 count);
#endif

#ifdef NONMATCHING
	switch (BattleGetSeq(wp, SEQ_ACT)) {
		case 0x6000000: {
			BattleUnit* unit;
			BOOL cantMove;
#endif
#ifndef NONMATCHING
void battleMakePhaseEvtTable(BattleWork* wp);
#endif

#ifdef NONMATCHING
			unit = BattleGetUnitPtr(wp, wp->activeUnitId);
			effNiceAsync(1);
			unit->totalDamageDealt = 0;
			FIELD(unit, s32, 0x2CC) = 0;
			BattleAudience_ActInit();
			cantMove = TRUE;
			switch (unit->currentKind) {
				case UNIT_MARIO:
					if (!BtlUnit_CheckStatus(unit, 1) &&
						!BtlUnit_CheckStatus(unit, 2) &&
						!BtlUnit_CheckStatus(unit, 9) &&
						!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL)) {
						cantMove = FALSE;
					}
					break;
				default:
					if (unit->currentKind >= TYPE_PARTNER_MIN && unit->currentKind < TYPE_PARTNER_MAX) {
						if (!BtlUnit_CheckStatus(unit, 1) &&
							!BtlUnit_CheckStatus(unit, 2) &&
							!BtlUnit_CheckStatus(unit, 9) &&
							!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL)) {
							cantMove = FALSE;
						}
					}
					break;
			}
			if (cantMove) {
				BattleSetSeq(wp, SEQ_ACT, 0x6000003);
			}
			else if (unit->mAttributeFlags & 0x10) {
				BattleSetSeq(wp, SEQ_ACT, 0x6000004);
			}
			else if (unit->currentKind == UNIT_VIVIAN && (BattleGetMarioPtr(wp)->mAttributeFlags & 0x10)) {
				BattleSetSeq(wp, SEQ_ACT, 0x6000004);
			}
			else if (unit->flippedTurns) {
				BattleSetSeq(wp, SEQ_ACT, 0x6000005);
			}
			else {
				BattleCommandInit(wp);
				BattleSetSeq(wp, SEQ_ACT, 0x6000001);
			}
			break;
		}
		case 0x6000001:
			if (battleCameraGetPosMoveSpeed() > 2.0f) {
				break;
			}
			BattleSetSeq(wp, SEQ_ACT, 0x6000002);
		case 0x6000002:
			if (!BattleCommandInput(wp)) {
				break;
			}
			wp->flags &= ~0x80;
			BattleSetSeq(wp, SEQ_ACT, 0x6000006);
			break;
		case 0x6000005:
			unit = BattleGetUnitPtr(wp, wp->activeUnitId);
			unit->attackEventCode = BtlUnit_GetData(unit, 2);
			unit->attackEventFlags = 1;
			BattleSetSeq(wp, SEQ_ACT, 0x6000006);
			break;
		case 0x6000003:
			unit = BattleGetUnitPtr(wp, wp->activeUnitId);
			unit->attackEventFlags = 1;
			unit->flags |= 0x4000000;
			BattleSetSeq(wp, SEQ_ACT, 0x6000006);
			break;
		case 0x6000004:
			unit = BattleGetUnitPtr(wp, wp->activeUnitId);
			unit->attackEventCode = BtlUnit_GetData(unit, 3);
			unit->attackEventFlags = 0x1B;
			BattleSetSeq(wp, SEQ_ACT, 0x6000006);
			break;
		case 0x6000006:
			unit = BattleGetUnitPtr(wp, wp->activeUnitId);
			if (!(unit->attackEventFlags & 1)) {
				BattleStatusWindowSystemOff();
			}
			unit = BattleGetUnitPtr(wp, wp->activeUnitId);
			evt = NULL;
			if ((wp->flags & 0x40000000) && !(unit->mAttributeFlags & 0x2000) &&
				!(unit->attackEventFlags & 8) && !(unit->attackEventFlags & 0x10)) {
				evt = evtEntry(btldefaultevt_CantMoveZeroGravity, 10, 0);
			}
			else if (unit->attackEventFlags & 0x10) {
				if (unit->attackEventCode) {
					evt = evtEntry(unit->attackEventCode, 10, 0);
				}
			}
			else if (unit->attackEventFlags & 2) {
				evt = evtEntry(unit->attackEventCode, 10, 0);
			}
			else if (!BtlUnit_CheckStatus(unit, 1) &&
				!BtlUnit_CheckStatus(unit, 2) &&
				!BtlUnit_CheckStatus(unit, 9) &&
				(!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL) || (unit->mAttributeFlags & 0x10000))) {
				if (BtlUnit_CheckStatus(unit, 6) && irand(100) < 0) {
					evt = evtEntry(btldefaultevt_BiribiriMove, 10, 0);
				}
				else if (BtlUnit_CheckStatus(unit, 5) && irand(100) < 50) {
					unit->mTokenFlags |= 0x10;
					evt = evtEntry(unit->confusionEventCode, 10, 0);
				}
				else {
					evt = evtEntry(unit->attackEventCode, 10, 0);
				}
			}
			if (evt) {
				unit->attackEventId = evt->eventId;
				evt->unitId = unit->unitId;
				if (unit->waitEventId) {
					evtDeleteID(unit->waitEventId);
					unit->waitEventId = 0;
				}
			}
			BattleIncSeq(wp, SEQ_ACT);
			break;
		case 0x6000007:
			if (!BattleWaitAllActiveEvtEnd(wp)) {
				break;
			}
			BattleIncSeq(wp, SEQ_ACT);
			BattleStatusChangeMsgAdjust(wp);
		case 0x6000008:
			if (!BattleWaitAllActiveEvtEnd(wp)) {
				break;
			}
			if (BattleStatusChangeAnnouceMain(wp) | BattleStatusChangeMsgMain(wp)) {
				break;
			}
			BattleIncSeq(wp, SEQ_ACT);
		case 0x6000009:
			if (!(wp->flags & 0x30)) {
				BattleStatusWindowSystemOn();
			}
			unit = BattleGetUnitPtr(wp, wp->activeUnitId);
			if (unit) {
				unit->flags &= ~0x4000000;
				if (unit->mTokenFlags & 8) {
					BtlUnit_SetStatus(unit, 0x10, 1, -99);
					unit->mTokenFlags &= ~8;
				}
				if (wp->majinaiState == 1) {
					wp->majinaiState = 0;
				}
				FIELD(unit, s32, 0x258) = 0;
				switch (unit->moveState) {
					case 5:
						unit->moveState = 6;
						break;
					case 6:
						unit->moveState = 7;
						break;
					case 8:
						unit->moveState = 9;
						break;
					case 7:
					case 9:
						unit->moveState = 0;
						break;
				}
				if (unit->moveState == 0) {
					decrement = TRUE;
					if (wp->flags & 0x2000) {
						decrement = TRUE;
					}
					if (decrement) {
						if (BtlUnit_CheckStatusFlag(unit, 0x2000000)) {
							BtlUnit_OffStatusFlag(unit, 0x2000000);
						}
						else {
							unit->movesRemaining--;
						}
						if (wp->flags & 0x2000) {
							unit->movesRemaining = 0;
						}
						if (unit->movesRemaining <= 0) {
							unit->moveState = 10;
							if (!(unit->mTokenFlags & 0x2000)) {
								unit->activeTurns = 0;
							}
							else {
								unit->mTokenFlags &= ~0x2000;
							}
							if (!BtlUnit_GetBelong(unit) && unit->attackPhase == 0x4000002 &&
								!BattlePhaseEndCheck() && !(wp->flags & 0x2000)) {
								unit->mMoveColorLv = 0x60;
							}
						}
					}
				}
				else if (unit->moveState == 3) {
					unit->moveState = 0;
				}
				else if (unit->moveState == 4) {
					unit->moveState = 0;
				}
			}
			BattleConsumeReserveItem();
			wp->flags &= ~4;
			BattleAudience_PerAct();
			BattleIncSeq(wp, SEQ_ACT);
		case 0x600000A:
			if ((u8)BattleAudience_CheckReaction()) {
				break;
			}
			if (!BattleCheckConcluded(wp) && (u8)BattleBreakSlot_CheckReaction()) {
				break;
			}
			BattleIncSeq(wp, SEQ_ACT);
		case 0x600000B:
			if (BattleStatusChangeAnnouceMain(wp) | BattleStatusChangeMsgMain(wp)) {
				break;
			}
			BattleIncSeq(wp, SEQ_ACT);
		case 0x600000C:
			if (!BattleWaitAllActiveEvtEnd(wp)) {
				break;
			}
			unit = BattleGetUnitPtr(wp, wp->activeUnitId);
			if (unit) {
				FIELD(unit, s32, 0x2C8) = 0;
				if (FIELD(unit, void*, 0x2C4)) {
					evt = evtEntry(FIELD(unit, void*, 0x2C4), 10, 0);
					if (evt) {
						FIELD(unit, s32, 0x2C8) = evt->eventId;
						evt->unitId = unit->unitId;
						if (unit->waitEventId) {
							evtDeleteID(unit->waitEventId);
							unit->waitEventId = 0;
						}
					}
				}
			}
			BattleIncSeq(wp, SEQ_ACT);
		case 0x600000D:
			unit = BattleGetUnitPtr(wp, wp->activeUnitId);
			if (unit && FIELD(unit, s32, 0x2C8)) {
				if (evtCheckID(FIELD(unit, s32, 0x2C8))) {
					break;
				}
				FIELD(unit, s32, 0x2C8) = 0;
			}
			BattleIncSeq(wp, SEQ_ACT);
		case 0x600000E:
			if (!BattleWaitAllActiveEvtEnd(wp)) {
				break;
			}
			BattleIncSeq(wp, SEQ_MOVE);
			break;
	}
}
#endif
#ifndef NONMATCHING
BOOL BattleWaitAllActiveEvtEnd(BattleWork* wp);
#endif

#ifndef NONMATCHING
BOOL BattleWaitAllActiveEvtEnd_NoBgSetEndWait(BattleWork* wp);

BOOL BattleCheckConcluded(BattleWork* wp);

void _mapobj_data_touch_scale(s32 layer);

#pragma dont_inline on
s32 _set_haikei_entry_scale(EventEntry* event, BOOL isFirstCall);


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
#pragma force_active reset
#pragma force_active reset
#endif

void btlseqTurnFirstProcess(BattleWork* wp) {
	BattleUnitKind* kind;
	int i;
	BattleUnit* unit;

	BtlActRec_JudgeTurnRuleKeep();
	wp->turnCount++;
	if (wp->turnCount >= 2) {
		BattleMajinaiCheck();
	}
	wp->announce.field_36C = 0;
	wp->announce.field_368 = 0;
	BtlActRec_AddCount(&wp->field_16F3B);
	for (i = 0; i < 64; i++) {
		unit = BattleGetUnitPtr(wp, i);
		if (unit) {
			unit->activeTurns++;
			BtlUnit_ResetMoveStatus(unit);
			kind = unit->mKindParams;
			unit->movePriority = kind->turnOrder + irand(kind->turnOrderVariance) - kind->turnOrderVariance / 2;
			if (BtlUnit_CheckStatusFlag(unit, 0x1000000)) {
				BtlUnit_OffStatusFlag(unit, 0x1000000);
			}
		}
	}
	BattleFogEndCheck();
}

#ifndef NONMATCHING
#pragma dont_inline on
#endif
void btlseqPhaseFirstProcess(BattleWork* wp) {
	BattleUnit* unit;
	BattleUnitPart* part;
	s32 count;
	int i;

	FIELD(wp, s32, 0x1C70) = 0;
	FIELD(wp, u8, 0x1C74) = 0;
	for (i = 0; i < 64; i++) {
		wp->movePriorityQueue[i] = -1;
	}
	count = 0;
	for (i = 0; i < 64; i++) {
		unit = BattleGetUnitPtr(wp, i);
		if (unit) {
			unit->mMoveColorLv = 0xFF;
			if (unit->moveState == 10 && !BtlUnit_CheckStatus(unit, 0x14)) {
				continue;
			}
			if (unit->attackPhase == BattleGetSeq(wp, SEQ_PHASE) &&
				!(unit->mAttributeFlags & 0x80000)) {
				wp->movePriorityQueue[count] = unit->unitId;
				unit->protectId = -1;
				for (part = unit->mParts; part; part = part->mNextPart) {
					if (part->poseId != -1) {
						FIELD(part, u8, 0x4E4) = 1;
					}
				}
				count++;
			}
		}
	}
	battleSortPhaseMoveTable(wp, count);
	battleMakePhaseEvtTable(wp);
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

void battleSortPhaseMoveTable(BattleWork* wp, s32 count) {
	int i, j;
	BattleUnit* unit1;
	BattleUnit* unit2;
	f32 x1, y1, z1;
	f32 x2, y2, z2;
	s32 tmp;
	void* w;

	w = (void*)wp;
	if (count <= 0) {
		count = 0;
		for (i = 0; i < 64; i++) {
			if (((BattleWork*)w)->movePriorityQueue[i] == -1) {
				break;
			}
			count = count + 1;
		}
	}
	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count - i - 1; j++) {
			unit1 = BattleGetUnitPtr(((BattleWork*)w), ((BattleWork*)w)->movePriorityQueue[j]);
			unit2 = BattleGetUnitPtr(((BattleWork*)w), ((BattleWork*)w)->movePriorityQueue[j + 1]);
			BtlUnit_GetHomePos(unit1, &x1, &y1, &z1);
			BtlUnit_GetHomePos(unit2, &x2, &y2, &z2);
			if (__fabs(x1) > __fabs(x2)) {
				tmp = ((BattleWork*)w)->movePriorityQueue[j];
				((BattleWork*)w)->movePriorityQueue[j] = ((BattleWork*)w)->movePriorityQueue[j + 1];
				((BattleWork*)w)->movePriorityQueue[j + 1] = tmp;
			}
		}
	}
	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count - i - 1; j++) {
			unit1 = BattleGetUnitPtr(((BattleWork*)w), ((BattleWork*)w)->movePriorityQueue[j]);
			unit2 = BattleGetUnitPtr(((BattleWork*)w), ((BattleWork*)w)->movePriorityQueue[j + 1]);
			if (unit1->movePriority < unit2->movePriority) {
				tmp = ((BattleWork*)w)->movePriorityQueue[j];
				((BattleWork*)w)->movePriorityQueue[j] = ((BattleWork*)w)->movePriorityQueue[j + 1];
				((BattleWork*)w)->movePriorityQueue[j + 1] = tmp;
			}
		}
	}
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void battleMakePhaseEvtTable(BattleWork* wp) {
#ifdef NONMATCHING
	BattlePhaseEvtEntry* table;
	int i;
	BattlePhaseEvtEntry* entry;
	BattleUnit* unit;
	BattlePhaseEvtEntry tmp;
	f32 x, y, z;
	s32 count;
	int j;

	table = wp->phaseEvtTable;
	for (i = 0; i < 64; i++) {
		table[i].unitId = -1;
		table[i].priority = 0;
	}
	count = 0;
	for (i = 0; i < 64; i++) {
		unit = BattleGetUnitPtr(wp, i);
		if (unit && !(unit->mAttributeFlags & 0x80000)) {
			table[count].unitId = i;
			BtlUnit_GetHomePos(unit, &x, &y, &z);
			if (x >= 0.0f) {
				table[count].priority = 1000.0f + x;
			}
			else {
				table[count].priority = __fabs(x);
			}
			count++;
		}
	}
	for (i = 0; i < count - 1; i++) {
		for (j = 0; j < count - i - 1; j++) {
			if (table[j].priority > table[j + 1].priority) {
				tmp = table[j];
				table[j] = table[j + 1];
				table[j + 1] = tmp;
			}
		}
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		opword 0x38A0FFFF
		opword 0x90010044
		opword 0x38000040
		opword 0xBF410028
		opword 0x7C7A1B78
		opword 0x38600000
		opword 0x7C641B78
		opword 0x3BFA0220
		opword 0x7C0903A6
		opword 0x7CDF1A14
		opword 0x38630008
		opword 0x90A60000
		opword 0x90860004
		opword 0x4200FFF0
		opword 0x3BC00000
		opword 0x3BA00000
		opword 0x3B600000
		opword 0x7F43D378
		opword 0x7F64DB78
		bl BattleGetUnitPtr
		opword 0x28030000
		opword 0x41820074
		opword 0x80030104
		opword 0x54000319
		opword 0x40820068
		opword 0x7F9FEA14
		opword 0x38810010
		opword 0x937C0000
		opword 0x38A1000C
		opword 0x38C10008
		bl BtlUnit_GetHomePos
		opword 0xC0210010
		lfs f0, float_0_8041c280(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820020
		lfs f0, float_1000_8041c298(r2)
		opword 0xEC00082A
		opword 0xFC00001E
		opword 0xD8010020
		opword 0x80010024
		opword 0x901C0004
		opword 0x48000018
		opword 0xFC000A10
		opword 0xFC00001E
		opword 0xD8010020
		opword 0x80010024
		opword 0x901C0004
		opword 0x3BDE0001
		opword 0x3BBD0008
		opword 0x3B7B0001
		opword 0x2C1B0040
		opword 0x4180FF74
		opword 0x381EFFFF
		opword 0x39200000
		opword 0x48000058
		opword 0x7C69F050
		opword 0x3483FFFF
		opword 0x38600000
		opword 0x7C8903A6
		opword 0x40810040
		opword 0x7D1F1A14
		opword 0x80E80004
		opword 0x80C8000C
		opword 0x7C073000
		opword 0x40810024
		opword 0x80A80000
		opword 0x80880008
		opword 0x90A10014
		opword 0x90880000
		opword 0x90C80004
		opword 0x90A80008
		opword 0x90E10018
		opword 0x90E8000C
		opword 0x38630008
		opword 0x4200FFC8
		opword 0x39290001
		opword 0x7C090000
		opword 0x4180FFA8
		opword 0xBB410028
		opword 0x80010044
		opword 0x7C0803A6
		opword 0x38210040
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
#pragma dont_inline on
#endif
BOOL BattleWaitAllActiveEvtEnd(BattleWork* wp) {
	BattleSeqStageWork* stage = STAGE_WORK(wp);
	BOOL ret = BattleWaitAllActiveEvtEnd_NoBgSetEndWait(wp);

	if (!ret) {
		return ret;
	}
	if (stage->nozzleWorkEvtId) {
		if (evtCheckID(stage->nozzleWorkEvtId)) {
			return FALSE;
		}
		stage->nozzleWorkEvtId = 0;
	}
	if (stage->fallFrameEvtId) {
		if (evtCheckID(stage->fallFrameEvtId)) {
			return FALSE;
		}
		stage->fallFrameEvtId = 0;
	}
	if (stage->bgDestroyEvtId) {
		if (evtCheckID(stage->bgDestroyEvtId)) {
			return FALSE;
		}
		stage->bgDestroyEvtId = 0;
	}
	if (stage->objectFallEvtId) {
		if (evtCheckID(stage->objectFallEvtId)) {
			return FALSE;
		}
		stage->objectFallEvtId = 0;
	}
	if (stage->closeWallEvtId) {
		if (evtCheckID(stage->closeWallEvtId)) {
			return FALSE;
		}
		stage->closeWallEvtId = 0;
	}
	return TRUE;
}
#ifndef NONMATCHING
#pragma dont_inline reset
#endif

BOOL BattleWaitAllActiveEvtEnd_NoBgSetEndWait(BattleWork* wp) {
	void* w; BattleUnit* unit; BOOL done; int i;
	done = TRUE;
	w = (void*)wp;
	for (i = 0; i < 0x40; i++) {
		unit = BattleGetUnitPtr((BattleWork*)w, i);
		if (unit) {
			while (unit->phaseEventId) {
				if (evtCheckID(unit->phaseEventId)) {
					done = FALSE;
					break;
				}
				unit->phaseEventId = 0;
				break;
			}
			while (unit->attackEventId) {
				if (evtCheckID(unit->attackEventId)) {
					done = FALSE;
					break;
				}
				unit->attackEventId = 0;
				break;
			}
			while (unit->damageEventId) {
				if (evtCheckID(unit->damageEventId)) {
					done = FALSE;
					break;
				}
				unit->damageEventId = 0;
				break;
			}
			while (FIELD(unit, s32, 0x2B8)) {
				if (evtCheckID(FIELD(unit, s32, 0x2B8))) {
					done = FALSE;
					break;
				}
				FIELD(unit, s32, 0x2B8) = 0;
				break;
			}
		}
	}
	if (!done) {
		return done;
	}
	if (BattleAfterReactionMain()) {
		done = FALSE;
	}
	return done;
}

BOOL BattleCheckConcluded(BattleWork* wp) {
	BattleUnit* unit;
	s32 count;
	s32 i;
	s32 j;

	count = 0;
	for (i = 0; i < 3; i++) {
		wp->alliances[i].clearConditionMet = 0;
		if (wp->alliances[i].allianceId == 0) {
			wp->alliances[i].clearConditionMet = 1;
			count++;
			continue;
		}
		if (wp->alliances[i].allianceId & 1) {
			for (j = 0; j < 64; j++) {
				unit = BattleGetUnitPtr(wp, j);
				if (unit && unit->mAlliance == i &&
					!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL) &&
					!(unit->mAttributeFlags & 0x20000) &&
					!(unit->mAttributeFlags & 0x10000000)) {
					break;
				}
			}
			if (j >= 64) {
				wp->alliances[i].clearConditionMet = 1;
				count++;
				continue;
			}
		}
		if (wp->alliances[i].allianceId & 2) {
			for (j = 0; j < 64; j++) {
				unit = BattleGetUnitPtr(wp, j);
				if (unit && unit->mAlliance == i &&
					(unit->mAttributeFlags & 0x40000) &&
					!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL) &&
					!(unit->mAttributeFlags & 0x10000000)) {
					break;
				}
			}
			if (j >= 64) {
				wp->alliances[i].clearConditionMet = 1;
				count++;
			}
		}
	}
	if (count >= 2) {
		return TRUE;
	}
	return (wp->flags & 0x30) != 0;
}

void _mapobj_data_touch_scale(s32 layer) {
	BattleWork* wp = _battleWorkPointer;
	BattleStageObject* obj;
	int i;

	for (i = 0; i < 32; i++) {
		obj = &wp->stageObjects[i];
		if (obj->id > 0 && obj->data->mLayer == layer) {
			obj->mFlags |= 2;
		}
	}
}

#ifdef NONMATCHING
#pragma dont_inline on
USER_FUNC(_set_haikei_entry_scale) {
#endif
#ifndef NONMATCHING
#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 _set_haikei_entry_scale(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x2C040000
		lwz r31, _battleWorkPointer(r13)
		opword 0x7C7D1B78
		opword 0x3BC00000
		opword 0x4182005C
		opword 0x3860003C
		opword 0x38000000
		opword 0x907D0078
		la r3, str_8041C27C(r2)
		opword 0x901D007C
		bl mapGetMapObj
		opword 0x28030000
		opword 0x41820018
		lfs f1, float_0_8041c280(r2)
		la r3, str_8041C27C(r2)
		lfs f3, float_1_8041c284(r2)
		opword 0xFC400890
		bl mapObjScale
		la r3, str_8041C288(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x41820018
		lfs f1, float_0_8041c280(r2)
		la r3, str_8041C288(r2)
		lfs f3, float_1_8041c284(r2)
		opword 0xFC400890
		bl mapObjScale
		opword 0x807D0078
		opword 0x2C030000
		opword 0x40810078
		opword 0x3803FFFF
		opword 0x901D0078
		opword 0x801D0078
		opword 0x2C000000
		opword 0x40810064
		la r3, str_8041C27C(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x41820020
		lfs f1, float_0_8041c280(r2)
		la r3, str_8041C27C(r2)
		lfs f3, float_1_8041c284(r2)
		opword 0xFC400890
		bl mapObjScale
		opword 0x38600000
		bl _mapobj_data_touch_scale
		la r3, str_8041C288(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x41820020
		lfs f1, float_0_8041c280(r2)
		la r3, str_8041C288(r2)
		lfs f3, float_1_8041c284(r2)
		opword 0xFC400890
		bl mapObjScale
		opword 0x38600001
		bl _mapobj_data_touch_scale
		opword 0x38600000
		opword 0x480003D0
		opword 0x809D007C
		la r3, str_8041C27C(r2)
		opword 0x38040001
		opword 0x901D007C
		bl mapGetMapObj
		opword 0x28030000
		opword 0x418201CC
		opword 0x801D007C
		opword 0x2C000028
		opword 0x41800024
		lfs f1, float_1_8041c284(r2)
		la r3, str_8041C27C(r2)
		opword 0xFC400890
		opword 0xFC600890
		bl mapObjScale
		opword 0x38600000
		bl _mapobj_data_touch_scale
		opword 0x480001A0
		opword 0x2C00000F
		opword 0x3BC00001
		opword 0x40800024
		lfs f1, float_0_8041c280(r2)
		la r3, str_8041C27C(r2)
		lfs f3, float_1_8041c284(r2)
		opword 0xFC400890
		bl mapObjScale
		opword 0x38600000
		bl _mapobj_data_touch_scale
		opword 0x48000174
		lfs f1, float_1_8041c284(r2)
		la r3, str_8041C27C(r2)
		opword 0xFC400890
		opword 0xFC600890
		bl mapObjScale
		opword 0x38600000
		bl _mapobj_data_touch_scale
		opword 0x807D007C
		opword 0x2C030019
		opword 0x40800024
		lfs f1, float_0_8041c280(r2)
		opword 0x3883FFF1
		lfs f2, float_110_8041c28c(r2)
		opword 0x38600005
		opword 0x38A0000A
		bl intpl_sub
		fmr f29, f1
		opword 0x48000050
		opword 0x2C030023
		opword 0x40800024
		lfs f1, float_110_8041c28c(r2)
		opword 0x3883FFE7
		lfs f2, float_90_8041c290(r2)
		opword 0x3860000B
		opword 0x38A0000A
		bl intpl_sub
		opword 0xFFA00890
		opword 0x48000028
		opword 0x2C030028
		opword 0x40800020
		lfs f1, float_90_8041c290(r2)
		opword 0x3883FFDD
		lfs f2, float_100_8041c294(r2)
		opword 0x3860000B
		opword 0x38A00005
		bl intpl_sub
		opword 0xFFA00890
		opword 0x807D007C
		opword 0x2C030019
		opword 0x40800024
		lfs f1, float_100_8041c294(r2)
		opword 0x3883FFF1
		lfs f2, float_90_8041c290(r2)
		opword 0x38600005
		opword 0x38A0000A
		bl intpl_sub
		opword 0xFFC00890
		opword 0x48000050
		opword 0x2C030023
		opword 0x40800024
		lfs f1, float_90_8041c290(r2)
		opword 0x3883FFE7
		lfs f2, float_110_8041c28c(r2)
		opword 0x3860000B
		opword 0x38A0000A
		bl intpl_sub
		opword 0xFFC00890
		opword 0x48000028
		opword 0x2C030028
		opword 0x40800020
		lfs f1, float_110_8041c28c(r2)
		opword 0x3883FFDD
		lfs f2, float_100_8041c294(r2)
		opword 0x3860000B
		opword 0x38A00005
		bl intpl_sub
		opword 0xFFC00890
		lfs f31, float_100_8041c294(r2)
		li r26, 0x0
		opword 0x3B800000
		opword 0x3F7C0001
		opword 0x3B7B7140
		opword 0x7F7FDA14
		opword 0x801B0000
		opword 0x2C000000
		opword 0x40810034
		opword 0x807B0064
		opword 0xA0030006
		opword 0x28000000
		opword 0x40820024
		opword 0xEC3EF824
		opword 0x80630000
		lfs f3, float_1_8041c284(r2)
		opword 0xEC5DF824
		bl mapObjScale
		opword 0x801B0068
		opword 0x60000002
		opword 0x901B0068
		opword 0x3B5A0001
		opword 0x3B9C007C
		opword 0x2C1A0020
		opword 0x4180FFAC
		la r3, str_8041C288(r2)
		bl mapGetMapObj
		opword 0x28030000
		opword 0x418201CC
		opword 0x801D007C
		opword 0x2C00002D
		opword 0x41800024
		lfs f1, float_1_8041c284(r2)
		la r3, str_8041C288(r2)
		opword 0xFC400890
		opword 0xFC600890
		bl mapObjScale
		opword 0x38600001
		bl _mapobj_data_touch_scale
		opword 0x480001A0
		opword 0x2C000014
		opword 0x3BC00001
		opword 0x40800024
		lfs f1, float_0_8041c280(r2)
		la r3, str_8041C288(r2)
		lfs f3, float_1_8041c284(r2)
		opword 0xFC400890
		bl mapObjScale
		opword 0x38600001
		bl _mapobj_data_touch_scale
		opword 0x48000174
		lfs f1, float_1_8041c284(r2)
		la r3, str_8041C288(r2)
		opword 0xFC400890
		opword 0xFC600890
		bl mapObjScale
		opword 0x38600001
		bl _mapobj_data_touch_scale
		opword 0x807D007C
		opword 0x2C03001E
		opword 0x40800024
		lfs f1, float_0_8041c280(r2)
		opword 0x3883FFEC
		lfs f2, float_110_8041c28c(r2)
		opword 0x38600005
		opword 0x38A0000A
		bl intpl_sub
		opword 0xFFA00890
		opword 0x48000050
		opword 0x2C030028
		opword 0x40800024
		lfs f1, float_110_8041c28c(r2)
		opword 0x3883FFE2
		lfs f2, float_90_8041c290(r2)
		opword 0x3860000B
		opword 0x38A0000A
		bl intpl_sub
		opword 0xFFA00890
		opword 0x48000028
		opword 0x2C03002D
		opword 0x40800020
		lfs f1, float_90_8041c290(r2)
		opword 0x3883FFD8
		lfs f2, float_100_8041c294(r2)
		opword 0x3860000B
		opword 0x38A00005
		bl intpl_sub
		opword 0xFFA00890
		opword 0x807D007C
		opword 0x2C03001E
		opword 0x40800024
		lfs f1, float_100_8041c294(r2)
		opword 0x3883FFEC
		lfs f2, float_90_8041c290(r2)
		opword 0x38600005
		opword 0x38A0000A
		bl intpl_sub
		opword 0xFFC00890
		opword 0x48000050
		opword 0x2C030028
		opword 0x40800024
		lfs f1, float_90_8041c290(r2)
		opword 0x3883FFE2
		lfs f2, float_110_8041c28c(r2)
		opword 0x3860000B
		opword 0x38A0000A
		bl intpl_sub
		opword 0xFFC00890
		opword 0x48000028
		opword 0x2C03002D
		opword 0x40800020
		lfs f1, float_110_8041c28c(r2)
		opword 0x3883FFD8
		lfs f2, float_100_8041c294(r2)
		opword 0x3860000B
		opword 0x38A00005
		bl intpl_sub
		opword 0xFFC00890
		lfs f31, float_100_8041c294(r2)
		opword 0x3B800000
		opword 0x3BA00000
		opword 0x3F7D0001
		opword 0x3B7B7140
		opword 0x7F7FDA14
		opword 0x801B0000
		opword 0x2C000000
		opword 0x40810034
		opword 0x807B0064
		opword 0xA0030006
		opword 0x28000001
		opword 0x40820024
		opword 0xEC3EF824
		opword 0x80630000
		lfs f3, float_1_8041c284(r2)
		opword 0xEC5DF824
		bl mapObjScale
		opword 0x801B0068
		opword 0x60000002
		opword 0x901B0068
		opword 0x3B9C0001
		opword 0x3BBD007C
		opword 0x2C1C0020
		opword 0x4180FFAC
		opword 0x207E0000
		opword 0x38000002
		opword 0x7C631910
		opword 0x7C031878
	}
}
#pragma pop

#pragma defer_codegen reset

asm void btlseqAct(BattleWork* wp) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	li r4, 0x6
	stw r0, 0x24(r1)
	stmw r29, 0x14(r1)
	mr r30, r3
	bl BattleGetSeq
	subis r0, r3, 0x600
	cmplwi r0, 0xe
	bgt L_g5_1
	lis r3, jumptable_80361350@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_80361350@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_g5_2:
	lwz r4, 0x420(r30)
	mr r3, r30
	bl BattleGetUnitPtr
	mr r0, r3
	li r3, 0x1
	mr r29, r0
	bl effNiceAsync
	li r0, 0x0
	stw r0, 0x280(r29)
	stw r0, 0x2cc(r29)
	bl BattleAudience_ActInit
	lwz r0, 0x8(r29)
	li r31, 0x1
	cmpwi r0, 0xde
	beq L_g5_3
	b L_g5_4
	L_g5_3:
	mr r3, r29
	li r4, 0x1
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_5
	mr r3, r29
	li r4, 0x2
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_5
	mr r3, r29
	li r4, 0x9
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_5
	mr r3, r29
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_5
	li r31, 0x0
	b L_g5_5
	L_g5_4:
	cmpwi r0, 0xe0
	blt L_g5_5
	cmpwi r0, 0xe7
	bge L_g5_5
	mr r3, r29
	li r4, 0x1
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_5
	mr r3, r29
	li r4, 0x2
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_5
	mr r3, r29
	li r4, 0x9
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_5
	mr r3, r29
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_5
	li r31, 0x0
	L_g5_5:
	cmpwi r31, 0x0
	beq L_g5_6
	lis r4, 0x600
	mr r3, r30
	addi r5, r4, 0x3
	li r4, 0x6
	bl BattleSetSeq
	b L_g5_1
	L_g5_6:
	lwz r0, 0x104(r29)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_7
	lis r4, 0x600
	mr r3, r30
	addi r5, r4, 0x4
	li r4, 0x6
	bl BattleSetSeq
	b L_g5_1
	L_g5_7:
	lwz r0, 0x8(r29)
	cmpwi r0, 0xe4
	bne L_g5_8
	mr r3, r30
	bl BattleGetMarioPtr
	lwz r0, 0x104(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_8
	lis r4, 0x600
	mr r3, r30
	addi r5, r4, 0x4
	li r4, 0x6
	bl BattleSetSeq
	b L_g5_1
	L_g5_8:
	lbz r0, 0x12b(r29)
	extsb. r0, r0
	beq L_g5_9
	lis r4, 0x600
	mr r3, r30
	addi r5, r4, 0x5
	li r4, 0x6
	bl BattleSetSeq
	b L_g5_1
	L_g5_9:
	mr r3, r30
	bl BattleCommandInit
	lis r4, 0x600
	mr r3, r30
	addi r5, r4, 0x1
	li r4, 0x6
	bl BattleSetSeq
	b L_g5_1
	L_g5_10:
	bl battleCameraGetPosMoveSpeed
	lfs f0, float_2_8041c29c(r2)
	fcmpo cr0, f1, f0
	bgt L_g5_1
	lis r4, 0x600
	mr r3, r30
	addi r5, r4, 0x2
	li r4, 0x6
	bl BattleSetSeq
	L_g5_11:
	mr r3, r30
	bl BattleCommandInput
	cmpwi r3, 0x0
	beq L_g5_1
	lwz r0, 0xef4(r30)
	lis r5, 0x600
	mr r3, r30
	li r4, 0x6
	rlwinm r0, r0, 0, 25, 23
	addi r5, r5, 0x6
	stw r0, 0xef4(r30)
	bl BattleSetSeq
	b L_g5_1
	L_g5_12:
	lwz r4, 0x420(r30)
	mr r3, r30
	bl BattleGetUnitPtr
	mr r31, r3
	li r4, 0x2
	bl BtlUnit_GetData
	stw r3, 0x29c(r31)
	li r0, 0x1
	lis r4, 0x600
	mr r3, r30
	stw r0, 0x2a8(r31)
	addi r5, r4, 0x6
	li r4, 0x6
	bl BattleSetSeq
	b L_g5_1
	L_g5_13:
	lwz r4, 0x420(r30)
	mr r3, r30
	bl BattleGetUnitPtr
	li r0, 0x1
	lis r4, 0x600
	stw r0, 0x2a8(r3)
	addi r5, r4, 0x6
	li r4, 0x6
	lwz r0, 0x1c(r3)
	oris r0, r0, 0x400
	stw r0, 0x1c(r3)
	mr r3, r30
	bl BattleSetSeq
	b L_g5_1
	L_g5_14:
	lwz r4, 0x420(r30)
	mr r3, r30
	bl BattleGetUnitPtr
	mr r31, r3
	li r4, 0x3
	bl BtlUnit_GetData
	stw r3, 0x29c(r31)
	li r0, 0x1b
	lis r4, 0x600
	mr r3, r30
	stw r0, 0x2a8(r31)
	addi r5, r4, 0x6
	li r4, 0x6
	bl BattleSetSeq
	b L_g5_1
	L_g5_15:
	lwz r4, 0x420(r30)
	mr r3, r30
	bl BattleGetUnitPtr
	lwz r0, 0x2a8(r3)
	clrlwi. r0, r0, 31
	bne L_g5_16
	bl BattleStatusWindowSystemOff
	L_g5_16:
	lwz r4, 0x420(r30)
	mr r3, r30
	bl BattleGetUnitPtr
	lwz r0, 0xef4(r30)
	mr r31, r3
	li r29, 0x0
	rlwinm. r0, r0, 0, 1, 1
	beq L_g5_17
	lwz r0, 0x104(r31)
	rlwinm. r0, r0, 0, 18, 18
	bne L_g5_17
	lwz r3, 0x2a8(r31)
	rlwinm. r0, r3, 0, 28, 28
	bne L_g5_17
	rlwinm. r0, r3, 0, 27, 27
	bne L_g5_17
	lis r3, btldefaultevt_CantMoveZeroGravity@ha
	li r4, 0xa
	addi r3, r3, btldefaultevt_CantMoveZeroGravity@l
	li r5, 0x0
	bl evtEntry
	mr r29, r3
	b L_g5_18
	L_g5_17:
	lwz r3, 0x2a8(r31)
	rlwinm. r0, r3, 0, 27, 27
	beq L_g5_19
	lwz r3, 0x29c(r31)
	cmplwi r3, 0x0
	beq L_g5_18
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	mr r29, r3
	b L_g5_18
	L_g5_19:
	rlwinm. r0, r3, 0, 30, 30
	beq L_g5_20
	lwz r3, 0x29c(r31)
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	mr r29, r3
	b L_g5_18
	L_g5_20:
	mr r3, r31
	li r4, 0x1
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_18
	mr r3, r31
	li r4, 0x2
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_18
	mr r3, r31
	li r4, 0x9
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_18
	mr r3, r31
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_21
	lwz r0, 0x104(r31)
	rlwinm. r0, r0, 0, 15, 15
	beq L_g5_18
	L_g5_21:
	mr r3, r31
	li r4, 0x6
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_22
	li r3, 0x64
	bl irand
	cmpwi r3, 0x0
	bge L_g5_22
	lis r3, btldefaultevt_BiribiriMove@ha
	li r4, 0xa
	addi r3, r3, btldefaultevt_BiribiriMove@l
	li r5, 0x0
	bl evtEntry
	mr r29, r3
	b L_g5_18
	L_g5_22:
	mr r3, r31
	li r4, 0x5
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_23
	li r3, 0x64
	bl irand
	cmpwi r3, 0x32
	bge L_g5_23
	lwz r0, 0x278(r31)
	li r4, 0xa
	li r5, 0x0
	ori r0, r0, 0x10
	stw r0, 0x278(r31)
	lwz r3, 0x2a0(r31)
	bl evtEntry
	mr r29, r3
	b L_g5_18
	L_g5_23:
	lwz r3, 0x29c(r31)
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	mr r29, r3
	L_g5_18:
	cmplwi r29, 0x0
	beq L_g5_24
	lwz r0, 0x15c(r29)
	stw r0, 0x2a4(r31)
	lwz r0, 0x0(r31)
	stw r0, 0x160(r29)
	lwz r3, 0x28c(r31)
	cmpwi r3, 0x0
	beq L_g5_24
	bl evtDeleteID
	li r0, 0x0
	stw r0, 0x28c(r31)
	L_g5_24:
	mr r3, r30
	li r4, 0x6
	bl BattleIncSeq
	b L_g5_1
	L_g5_25:
	mr r3, r30
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_1
	mr r3, r30
	li r4, 0x6
	bl BattleIncSeq
	mr r3, r30
	bl BattleStatusChangeMsgAdjust
	L_g5_26:
	mr r3, r30
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_1
	mr r3, r30
	bl BattleStatusChangeMsgMain
	mr r31, r3
	mr r3, r30
	bl BattleStatusChangeAnnouceMain
	or. r0, r3, r31
	bne L_g5_1
	mr r3, r30
	li r4, 0x6
	bl BattleIncSeq
	L_g5_27:
	lwz r0, 0xef4(r30)
	rlwinm. r0, r0, 0, 26, 27
	bne L_g5_28
	bl BattleStatusWindowSystemOn
	L_g5_28:
	lwz r4, 0x420(r30)
	mr r3, r30
	bl BattleGetUnitPtr
	mr. r31, r3
	beq L_g5_29
	lwz r0, 0x1c(r31)
	rlwinm r0, r0, 0, 6, 4
	stw r0, 0x1c(r31)
	lwz r0, 0x278(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_30
	li r4, 0x10
	li r5, 0x1
	li r6, -0x63
	bl BtlUnit_SetStatus
	lwz r0, 0x278(r31)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x278(r31)
	L_g5_30:
	addis r3, r30, 0x2
	lbz r0, -0x701f(r3)
	cmplwi r0, 0x1
	bne L_g5_31
	li r0, 0x0
	stb r0, -0x701f(r3)
	L_g5_31:
	li r0, 0x0
	stw r0, 0x258(r31)
	lbz r0, 0x20(r31)
	extsb r0, r0
	cmpwi r0, 0x7
	beq L_g5_32
	bge L_g5_33
	cmpwi r0, 0x5
	beq L_g5_34
	bge L_g5_35
	b L_g5_36
	L_g5_33:
	cmpwi r0, 0x9
	beq L_g5_32
	bge L_g5_36
	b L_g5_37
	L_g5_34:
	li r0, 0x6
	stb r0, 0x20(r31)
	b L_g5_36
	L_g5_35:
	li r0, 0x7
	stb r0, 0x20(r31)
	b L_g5_36
	L_g5_37:
	li r0, 0x9
	stb r0, 0x20(r31)
	b L_g5_36
	L_g5_32:
	li r0, 0x0
	stb r0, 0x20(r31)
	L_g5_36:
	lbz r3, 0x20(r31)
	extsb. r0, r3
	bne L_g5_38
	lwz r0, 0xef4(r30)
	li r3, 0x1
	rlwinm. r0, r0, 0, 18, 18
	beq L_g5_39
	li r3, 0x1
	L_g5_39:
	cmpwi r3, 0x0
	beq L_g5_29
	mr r3, r31
	lis r4, 0x200
	bl BtlUnit_CheckStatusFlag
	cmpwi r3, 0x0
	beq L_g5_40
	mr r3, r31
	lis r4, 0x200
	bl BtlUnit_OffStatusFlag
	b L_g5_41
	L_g5_40:
	lbz r3, 0x22(r31)
	subi r0, r3, 0x1
	stb r0, 0x22(r31)
	L_g5_41:
	lwz r0, 0xef4(r30)
	rlwinm. r0, r0, 0, 18, 18
	beq L_g5_42
	li r0, 0x0
	stb r0, 0x22(r31)
	L_g5_42:
	lbz r0, 0x22(r31)
	extsb. r0, r0
	bgt L_g5_29
	li r0, 0xa
	stb r0, 0x20(r31)
	lwz r3, 0x278(r31)
	rlwinm. r0, r3, 0, 18, 18
	bne L_g5_43
	li r0, 0x0
	stb r0, 0x24(r31)
	b L_g5_44
	L_g5_43:
	rlwinm r0, r3, 0, 19, 17
	stw r0, 0x278(r31)
	L_g5_44:
	mr r3, r31
	bl BtlUnit_GetBelong
	extsb. r0, r3
	bne L_g5_29
	lwz r3, 0x2c(r31)
	subis r0, r3, 0x400
	cmplwi r0, 0x2
	bne L_g5_29
	bl BattlePhaseEndCheck
	cmpwi r3, 0x0
	bne L_g5_29
	lwz r0, 0xef4(r30)
	rlwinm. r0, r0, 0, 18, 18
	bne L_g5_29
	li r0, 0x60
	stb r0, 0x30d(r31)
	b L_g5_29
	L_g5_38:
	extsb r0, r3
	cmpwi r0, 0x3
	bne L_g5_45
	li r0, 0x0
	stb r0, 0x20(r31)
	b L_g5_29
	L_g5_45:
	cmpwi r0, 0x4
	bne L_g5_29
	li r0, 0x0
	stb r0, 0x20(r31)
	L_g5_29:
	bl BattleConsumeReserveItem
	lwz r0, 0xef4(r30)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0xef4(r30)
	bl BattleAudience_PerAct
	mr r3, r30
	li r4, 0x6
	bl BattleIncSeq
	L_g5_46:
	bl BattleAudience_CheckReaction
	clrlwi. r0, r3, 24
	bne L_g5_1
	mr r3, r30
	bl BattleCheckConcluded
	cmpwi r3, 0x0
	bne L_g5_47
	bl BattleBreakSlot_CheckReaction
	clrlwi. r0, r3, 24
	bne L_g5_1
	L_g5_47:
	mr r3, r30
	li r4, 0x6
	bl BattleIncSeq
	L_g5_48:
	mr r3, r30
	bl BattleStatusChangeMsgMain
	mr r31, r3
	mr r3, r30
	bl BattleStatusChangeAnnouceMain
	or. r0, r3, r31
	bne L_g5_1
	mr r3, r30
	li r4, 0x6
	bl BattleIncSeq
	L_g5_49:
	mr r3, r30
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_1
	lwz r4, 0x420(r30)
	mr r3, r30
	bl BattleGetUnitPtr
	mr. r31, r3
	beq L_g5_50
	li r0, 0x0
	stw r0, 0x2c8(r31)
	lwz r3, 0x2c4(r31)
	cmplwi r3, 0x0
	beq L_g5_50
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_50
	lwz r0, 0x15c(r3)
	stw r0, 0x2c8(r31)
	lwz r0, 0x0(r31)
	stw r0, 0x160(r3)
	lwz r3, 0x28c(r31)
	cmpwi r3, 0x0
	beq L_g5_50
	bl evtDeleteID
	li r0, 0x0
	stw r0, 0x28c(r31)
	L_g5_50:
	mr r3, r30
	li r4, 0x6
	bl BattleIncSeq
	L_g5_51:
	lwz r4, 0x420(r30)
	mr r3, r30
	bl BattleGetUnitPtr
	mr. r31, r3
	beq L_g5_52
	lwz r3, 0x2c8(r31)
	cmpwi r3, 0x0
	beq L_g5_52
	bl evtCheckID
	cmpwi r3, 0x0
	bne L_g5_1
	li r0, 0x0
	stw r0, 0x2c8(r31)
	L_g5_52:
	mr r3, r30
	li r4, 0x6
	bl BattleIncSeq
	L_g5_53:
	mr r3, r30
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_1
	mr r3, r30
	li r4, 0x5
	bl BattleIncSeq
	L_g5_1:
	lmw r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

#pragma defer_codegen off
BOOL BattlePhaseEndCheck(void) {
#endif
	BattleWork* wp = _battleWorkPointer;
#ifdef NONMATCHING
	BOOL busy = FALSE;
	f32 sx, sy;
	BattleStageObject* obj;
#endif
#ifndef NONMATCHING
	BattleUnit* unit;
#endif
	int i;

#ifdef NONMATCHING
	if (isFirstCall) {
		event->userdata[0] = 60;
		event->userdata[1] = 0;
		if (mapGetMapObj("A1")) {
			mapObjScale("A1", 0.0f, 0.0f, 1.0f);
		}
		if (mapGetMapObj("A2")) {
			mapObjScale("A2", 0.0f, 0.0f, 1.0f);
		}
	}
	if (event->userdata[0] > 0) {
		event->userdata[0]--;
		if (event->userdata[0] > 0) {
			if (mapGetMapObj("A1")) {
				mapObjScale("A1", 0.0f, 0.0f, 1.0f);
				_mapobj_data_touch_scale(0);
			}
			if (mapGetMapObj("A2")) {
				mapObjScale("A2", 0.0f, 0.0f, 1.0f);
				_mapobj_data_touch_scale(1);
			}
			return EVT_RETURN_BLOCK;
		}
	}
	event->userdata[1]++;
	if (mapGetMapObj("A1")) {
		if (event->userdata[1] >= 40) {
			mapObjScale("A1", 1.0f, 1.0f, 1.0f);
			_mapobj_data_touch_scale(0);
		}
		else {
			busy = TRUE;
			if (event->userdata[1] < 15) {
				mapObjScale("A1", 0.0f, 0.0f, 1.0f);
				_mapobj_data_touch_scale(0);
			}
			else {
				mapObjScale("A1", 1.0f, 1.0f, 1.0f);
				_mapobj_data_touch_scale(0);
				if (event->userdata[1] < 25) {
					sy = intpl_sub(5, 0.0f, 110.0f, event->userdata[1] - 15, 10);
				}
				else if (event->userdata[1] < 35) {
					sy = intpl_sub(11, 110.0f, 90.0f, event->userdata[1] - 25, 10);
				}
				else if (event->userdata[1] < 40) {
					sy = intpl_sub(11, 90.0f, 100.0f, event->userdata[1] - 35, 5);
				}
				if (event->userdata[1] < 25) {
					sx = intpl_sub(5, 100.0f, 90.0f, event->userdata[1] - 15, 10);
				}
				else if (event->userdata[1] < 35) {
					sx = intpl_sub(11, 90.0f, 110.0f, event->userdata[1] - 25, 10);
				}
				else if (event->userdata[1] < 40) {
					sx = intpl_sub(11, 110.0f, 100.0f, event->userdata[1] - 35, 5);
				}
				for (i = 0; i < 32; i++) {
					obj = &wp->stageObjects[i];
					if (obj->id > 0 && obj->data->mLayer == 0) {
						mapObjScale(obj->data->name, sx / 100.0f, sy / 100.0f, 1.0f);
						obj->mFlags |= 2;
					}
				}
#endif
#ifndef NONMATCHING
	for (i = 0; i < 64; i++) {
		if (wp->movePriorityQueue[i] != -1) {
			unit = BattleGetUnitPtr(wp, wp->movePriorityQueue[i]);
			if (unit && unit->moveState != 10 && unit->movesRemaining > 0 &&
				!BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL)) {
				break;
#endif
			}
		}
	}
#ifdef NONMATCHING
	if (mapGetMapObj("A2")) {
		if (event->userdata[1] >= 45) {
			mapObjScale("A2", 1.0f, 1.0f, 1.0f);
			_mapobj_data_touch_scale(1);
		}
		else {
			busy = TRUE;
			if (event->userdata[1] < 20) {
				mapObjScale("A2", 0.0f, 0.0f, 1.0f);
				_mapobj_data_touch_scale(1);
			}
			else {
				mapObjScale("A2", 1.0f, 1.0f, 1.0f);
				_mapobj_data_touch_scale(1);
				if (event->userdata[1] < 30) {
					sy = intpl_sub(5, 0.0f, 110.0f, event->userdata[1] - 20, 10);
				}
				else if (event->userdata[1] < 40) {
					sy = intpl_sub(11, 110.0f, 90.0f, event->userdata[1] - 30, 10);
				}
				else if (event->userdata[1] < 45) {
					sy = intpl_sub(11, 90.0f, 100.0f, event->userdata[1] - 40, 5);
				}
				if (event->userdata[1] < 30) {
					sx = intpl_sub(5, 100.0f, 90.0f, event->userdata[1] - 20, 10);
				}
				else if (event->userdata[1] < 40) {
					sx = intpl_sub(11, 90.0f, 110.0f, event->userdata[1] - 30, 10);
				}
				else if (event->userdata[1] < 45) {
					sx = intpl_sub(11, 110.0f, 100.0f, event->userdata[1] - 40, 5);
				}
				for (i = 0; i < 32; i++) {
					obj = &wp->stageObjects[i];
					if (obj->id > 0 && obj->data->mLayer == 1) {
						mapObjScale(obj->data->name, sx / 100.0f, sy / 100.0f, 1.0f);
						obj->mFlags |= 2;
					}
				}
			}
		}
#endif
#ifndef NONMATCHING
	if (i >= 64) {
		return TRUE;
#endif
	}
#ifdef NONMATCHING
	return busy ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
#endif
#ifndef NONMATCHING
	return FALSE;
#endif
}

#ifndef NONMATCHING
#pragma defer_codegen reset
#endif

#ifdef NONMATCHING
// target pad words (G5: section sizes must match or later DOL addresses shift)
#endif
#ifndef NONMATCHING
asm void btlseqMove(BattleWork* wp) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r29, r3
	L_g5_1:
	mr r3, r29
	li r30, 0x0
	li r4, 0x5
	bl BattleGetSeq
	subis r0, r3, 0x500
	cmplwi r0, 0xe
	bgt L_g5_2
	lis r3, jumptable_8036138C@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_8036138C@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_g5_3:
	mr r3, r29
	bl btlseqPhaseFirstProcess
	mr r3, r29
	li r4, 0x5
	bl BattleIncSeq
	li r30, 0x1
	b L_g5_2
	L_g5_4:
	mr r3, r29
	li r4, 0x5
	bl BattleIncSeq
	li r30, 0x1
	b L_g5_2
	L_g5_5:
	bl pouchGetPtr
	mr r28, r3
	mr r3, r29
	bl BattleGetMarioPtr
	lbz r0, 0x5ba(r28)
	mr r28, r3
	cmplwi r0, 0x2
	bne L_g5_6
	mr r3, r29
	li r4, 0x4
	bl BattleGetSeq
	subis r0, r3, 0x400
	cmplwi r0, 0x4
	beq L_g5_7
	L_g5_6:
	mr r3, r29
	li r4, 0x5
	bl BattleIncSeq
	mr r3, r29
	li r4, 0x5
	bl BattleIncSeq
	li r30, 0x1
	b L_g5_2
	L_g5_7:
	addis r3, r29, 0x2
	li r0, 0x2
	stb r0, -0x701f(r3)
	bl BattleMajinaiDone
	bl BattleMajinaiEndCheck
	lis r3, marioAttackEvent_MajinaiDefenceUp@ha
	li r4, 0xa
	addi r3, r3, marioAttackEvent_MajinaiDefenceUp@l
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x0(r28)
	li r4, 0x5
	stw r0, 0x160(r3)
	lwz r0, 0x15c(r3)
	mr r3, r29
	stw r0, 0x2a4(r28)
	bl BattleIncSeq
	L_g5_8:
	mr r3, r29
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_2
	mr r3, r29
	li r4, 0x5
	bl BattleIncSeq
	li r30, 0x1
	b L_g5_2
	L_g5_9:
	li r27, 0x0
	L_g5_10:
	mr r3, r29
	mr r4, r27
	bl BattleGetUnitPtr
	mr. r31, r3
	beq L_g5_11
	lwz r0, 0x290(r31)
	cmplwi r0, 0x0
	beq L_g5_11
	li r4, 0x1
	bl BattleRunPhaseEvent
	L_g5_11:
	addi r27, r27, 0x1
	cmpwi r27, 0x40
	blt L_g5_10
	mr r3, r29
	li r4, 0x5
	bl BattleIncSeq
	li r30, 0x1
	b L_g5_2
	L_g5_12:
	mr r3, r29
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_2
	mr r3, r29
	li r4, 0x5
	bl BattleIncSeq
	li r30, 0x1
	b L_g5_2
	L_g5_13:
	li r25, 0x0
	li r28, 0x0
	L_g5_14:
	addi r0, r28, 0x220
	lwzx r4, r29, r0
	cmpwi r4, -0x1
	beq L_g5_15
	mr r3, r29
	bl BattleGetUnitPtr
	mr. r31, r3
	beq L_g5_15
	lwz r0, 0x294(r31)
	cmplwi r0, 0x0
	bne L_g5_16
	L_g5_15:
	addi r25, r25, 0x1
	addi r28, r28, 0x8
	cmpwi r25, 0x40
	blt L_g5_14
	L_g5_16:
	cmpwi r25, 0x40
	bge L_g5_17
	mr r3, r31
	li r4, 0x0
	bl BattleRunPhaseEvent
	slwi r3, r25, 3
	li r4, -0x1
	addi r0, r3, 0x220
	mr r3, r29
	stwx r4, r29, r0
	li r4, 0x5
	bl BattleIncSeq
	b L_g5_2
	L_g5_17:
	lis r4, 0x500
	mr r3, r29
	addi r5, r4, 0xa
	li r4, 0x5
	bl BattleSetSeq
	li r30, 0x1
	b L_g5_2
	L_g5_18:
	mr r3, r29
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_2
	mr r3, r29
	bl BattleCheckConcluded
	cmpwi r3, 0x0
	beq L_g5_19
	mr r3, r29
	li r4, 0x0
	li r5, 0x3
	bl BattleSetSeq
	mr r3, r29
	li r4, 0x7
	lis r5, 0x700
	bl BattleSetSeq
	b L_g5_2
	L_g5_19:
	lis r4, 0x500
	mr r3, r29
	addi r5, r4, 0x6
	li r4, 0x5
	bl BattleSetSeq
	li r30, 0x1
	b L_g5_2
	L_g5_20:
	addis r3, r29, 0x2
	li r4, 0x0
	li r5, 0xc
	subi r3, r3, 0x701c
	bl memset
	li r27, 0x0
	lis r3, 0x8000
	mr r28, r27
	addi r31, r3, 0x2000
	L_g5_21:
	mr r3, r29
	mr r4, r27
	bl BattleGetUnitPtr
	cmplwi r3, 0x0
	beq L_g5_22
	lwz r0, 0x278(r3)
	and r0, r0, r31
	stw r0, 0x278(r3)
	stw r28, 0x260(r3)
	stb r28, 0x26c(r3)
	sth r28, 0x25c(r3)
	stb r28, 0x26f(r3)
	stw r28, 0x264(r3)
	stb r28, 0x26d(r3)
	stw r28, 0x268(r3)
	stb r28, 0x26e(r3)
	stw r28, 0x27c(r3)
	L_g5_22:
	addi r27, r27, 0x1
	cmpwi r27, 0x40
	blt L_g5_21
	li r27, 0x0
	li r28, 0x0
	L_g5_23:
	addi r0, r28, 0x120
	lwzx r26, r29, r0
	cmpwi r26, -0x1
	beq L_g5_24
	mr r3, r29
	mr r4, r26
	bl BattleGetUnitPtr
	mr. r31, r3
	beq L_g5_24
	lbz r0, 0x22(r31)
	extsb. r0, r0
	ble L_g5_24
	lbz r25, 0x20(r31)
	extsb r25, r25
	cmpwi r25, 0xa
	beq L_g5_24
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_25
	lwz r0, 0x104(r31)
	rlwinm. r0, r0, 0, 15, 15
	beq L_g5_24
	L_g5_25:
	cmpwi r25, 0x1
	bne L_g5_26
	li r0, 0x0
	stb r0, 0x20(r31)
	L_g5_24:
	addi r27, r27, 0x1
	addi r28, r28, 0x4
	cmpwi r27, 0x40
	blt L_g5_23
	L_g5_26:
	stw r26, 0x420(r29)
	mr r3, r29
	mr r4, r26
	bl BattleGetUnitPtr
	lwz r0, 0x278(r3)
	li r4, 0x5
	ori r0, r0, 0x1000
	stw r0, 0x278(r3)
	mr r3, r29
	bl BattleIncSeq
	mr r3, r29
	li r4, 0x6
	lis r5, 0x600
	bl BattleSetSeq
	li r27, 0x0
	li r28, 0x0
	mr r31, r27
	L_g5_27:
	addi r0, r28, 0x120
	lwzx r26, r29, r0
	cmpwi r26, -0x1
	beq L_g5_28
	mr r3, r29
	mr r4, r26
	bl BattleGetUnitPtr
	cmplwi r3, 0x0
	beq L_g5_28
	lbz r0, 0x20(r3)
	cmpwi r0, 0x1
	bne L_g5_28
	stb r31, 0x20(r3)
	L_g5_28:
	addi r27, r27, 0x1
	addi r28, r28, 0x4
	cmpwi r27, 0x40
	blt L_g5_27
	lwz r4, 0x420(r29)
	mr r3, r29
	bl BattleGetUnitPtr
	lwz r0, 0x8(r3)
	mr r31, r3
	cmpwi r0, 0xde
	bne L_g5_2
	bl pouchGetPtr
	lwz r5, 0xef4(r29)
	li r0, 0xc8
	li r4, 0x0
	ori r5, r5, 0x600
	stw r5, 0xef4(r29)
	mtctr r0
	L_g5_29:
	addi r0, r4, 0x38a
	lhax r0, r3, r0
	cmpwi r0, 0xf0
	blt L_g5_30
	cmpwi r0, 0xf7
	bge L_g5_30
	lwz r0, 0xef4(r29)
	rlwinm r0, r0, 0, 23, 21
	stw r0, 0xef4(r29)
	b L_g5_31
	L_g5_30:
	addi r4, r4, 0x2
	bdnz L_g5_29
	L_g5_31:
	lbz r0, 0x98(r3)
	extsb r0, r0
	cmpwi r0, 0x2
	blt L_g5_32
	lwz r0, 0xef4(r29)
	rlwinm r0, r0, 0, 23, 21
	stw r0, 0xef4(r29)
	L_g5_32:
	li r0, 0xc8
	li r4, 0x0
	mtctr r0
	L_g5_33:
	addi r0, r4, 0x38a
	lhax r0, r3, r0
	cmpwi r0, 0xf7
	blt L_g5_34
	cmpwi r0, 0xfe
	bge L_g5_34
	lwz r0, 0xef4(r29)
	rlwinm r0, r0, 0, 22, 20
	stw r0, 0xef4(r29)
	b L_g5_35
	L_g5_34:
	addi r4, r4, 0x2
	bdnz L_g5_33
	L_g5_35:
	lbz r0, 0x99(r3)
	extsb r0, r0
	cmpwi r0, 0x2
	blt L_g5_2
	lwz r0, 0xef4(r29)
	rlwinm r0, r0, 0, 22, 20
	stw r0, 0xef4(r29)
	b L_g5_2
	L_g5_36:
	mr r3, r29
	bl btlseqAct
	b L_g5_2
	L_g5_37:
	mr r3, r29
	bl BattleCheckConcluded
	cmpwi r3, 0x0
	beq L_g5_38
	mr r3, r29
	li r4, 0x0
	li r5, 0x3
	bl BattleSetSeq
	mr r3, r29
	li r4, 0x7
	lis r5, 0x700
	bl BattleSetSeq
	b L_g5_2
	L_g5_38:
	li r28, 0x0
	L_g5_39:
	mr r3, r29
	mr r4, r28
	bl BattleGetUnitPtr
	mr. r31, r3
	beq L_g5_40
	li r4, 0x0
	bl BtlUnit_SetTotalHitDamage
	lwz r0, 0x278(r31)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x278(r31)
	L_g5_40:
	addi r28, r28, 0x1
	cmpwi r28, 0x40
	blt L_g5_39
	bl BattlePhaseEndCheck
	lwz r0, 0xef4(r29)
	rlwinm. r0, r0, 0, 18, 18
	beq L_g5_41
	li r3, 0x1
	L_g5_41:
	cmpwi r3, 0x0
	beq L_g5_42
	addis r3, r29, 0x2
	lbz r0, -0x701f(r3)
	cmplwi r0, 0x2
	bne L_g5_43
	li r0, 0x0
	stb r0, -0x701f(r3)
	L_g5_43:
	mr r3, r29
	li r4, 0x4
	bl BattleGetSeq
	bl BattleAudience_PerPhase
	mr r3, r29
	li r4, 0x5
	bl BattleIncSeq
	b L_g5_2
	L_g5_42:
	lis r4, 0x500
	mr r3, r29
	addi r5, r4, 0x8
	li r4, 0x5
	bl BattleSetSeq
	b L_g5_2
	L_g5_44:
	bl BattleAudience_CheckReactionPerPhase
	clrlwi. r0, r3, 24
	bne L_g5_2
	mr r3, r29
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_2
	mr r3, r29
	li r4, 0x5
	bl BattleIncSeq
	b L_g5_2
	L_g5_45:
	mr r3, r29
	bl BattleStatusChangeMsgMain
	mr r28, r3
	mr r3, r29
	bl BattleStatusChangeAnnouceMain
	or. r0, r3, r28
	bne L_g5_2
	mr r3, r29
	li r4, 0x4
	bl BattleIncSeq
	mr r3, r29
	li r4, 0x5
	lis r5, 0x500
	bl BattleSetSeq
	b L_g5_2
	L_g5_46:
	mr r3, r29
	li r4, 0x5
	bl BattleIncSeq
	b L_g5_2
	L_g5_47:
	mr r3, r29
	li r4, 0x4
	bl BattleIncSeq
	mr r3, r29
	li r4, 0x5
	lis r5, 0x500
	bl BattleSetSeq
	L_g5_2:
	cmpwi r30, 0x0
	bne L_g5_1
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void btlseqTurn(BattleWork *wp) {
	char _af_pad[68];
	asm {
		li r4, 0x3
	}
	asm volatile {
		opword 0x7C7F1B78
		opword 0x3BC00000
		opword 0x3B800000
		bl BattleGetSeq
		opword 0x3C03FD00
		opword 0x2800004D
		opword 0x41811E20
		lis r3, jumptable_803613C8@ha
		opword 0x5400103A
		addi r3, r3, jumptable_803613C8@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x48001DF8
		opword 0x7FE3FB78
		bl btlseqTurnFirstProcess
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001DD8
		opword 0xA81F0000
		opword 0x2C000001
		opword 0x41820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001DA8
		opword 0x807F2738
		opword 0x88030018
		opword 0x28000000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001D74
		opword 0x38000078
		opword 0x7FE3FB78
		opword 0x901F0EFC
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001D54
		opword 0x807F0EFC
		opword 0x2C030000
		opword 0x4182000C
		opword 0x3803FFFF
		opword 0x901F0EFC
		opword 0x801F0EFC
		opword 0x2C000000
		opword 0x40810014
		opword 0x38600300
		bl BattlePadCheckTrigger
		opword 0x2C030000
		opword 0x41820014
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x48001D14
		lis r3, _rule_disp@ha
		lfs f1, float_900_8041c2ac(r2)
		addi r5, r3, _rule_disp@l
		opword 0x38800001
		opword 0x38600008
		opword 0x38C00000
		bl dispEntry
		opword 0x48001CF4
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001CDC
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001CC4
		opword 0x7FE3FB78
		bl BattleWaitAllActiveEvtEnd
		opword 0x2C030000
		opword 0x41821CB4
		opword 0x7FE3FB78
		bl BattleCheckConcluded
		opword 0x2C030000
		opword 0x41820028
		opword 0x7FE3FB78
		opword 0x38800000
		opword 0x38A00003
		bl BattleSetSeq
		opword 0x7FE3FB78
		opword 0x38800007
		opword 0x3CA00700
		bl BattleSetSeq
		opword 0x48001C80
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x48001C70
		lis r3, subsetevt_status_recovery@ha
		li r25, 0x0
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F24CB78
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x38800001
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B390001
		opword 0x2C190040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001BC8
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x48001BB8
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x38800002
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001B10
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001AF8
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x38800003
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001A50
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001A38
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x38800005
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001990
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001978
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x38800006
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480018D0
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480018B8
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x38800007
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001810
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480017F8
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x38800008
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001750
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001738
		lis r3, str_802EF5AC@ha
		la r27, _af_pad+60
		addi r29, r3, str_802EF5AC@l
		opword 0x3B810040
		opword 0x3B400000
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x38800009
		opword 0x7C791B78
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x418200A8
		opword 0x7F23CB78
		bl BtlUnit_CheckShadowGuard
		opword 0x2C030000
		opword 0x40820028
		opword 0x7F24CB78
		opword 0x3860FFFB
		opword 0x38A00000
		opword 0x38C00001
		opword 0x38E00000
		opword 0x3900011A
		opword 0x39200000
		opword 0x39400001
		bl BattleDamageDirect
		opword 0x7F23CB78
		opword 0x7F85E378
		opword 0x7F66DB78
		opword 0x3881003C
		bl BtlUnit_GetPos
		opword 0x7F23CB78
		bl BtlUnit_GetHeight
		opword 0x6C638000
		opword 0x3C004330
		opword 0x9061004C
		lis r4, double_to_int_802ef590@ha
		lfd f3, double_to_int_802ef590@l(r4)
		opword 0x38600000
		opword 0x90010048
		opword 0x38800001
		opword 0xC0010040
		opword 0xC8410048
		opword 0xC021003C
		opword 0xEC421828
		opword 0xC0610044
		lfs f4, float_1_8041c284(r2)
		opword 0xEC40102A
		opword 0xD0410040
		bl effFreezeN64Entry
		opword 0x7FA3EB78
		opword 0x3881003C
		bl psndSFXOn_3D
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FF34
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001628
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001610
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x3880000A
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001568
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001550
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x3880000B
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480014A8
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001490
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x38800004
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480013E8
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480013D0
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x3880000C
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001328
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001310
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x3880000D
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001268
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001250
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x3880000E
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480011A8
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001190
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x3880000F
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480010E8
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480010D0
		lis r3, subsetevt_status_recovery@ha
		opword 0x3B400000
		addi r27, r3, subsetevt_status_recovery@l
		opword 0x7FE3FB78
		opword 0x7F44D378
		bl BattleGetUnitPtr
		opword 0x7C7D1B78
		opword 0x38800000
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820030
		opword 0x7F63DB78
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901D02A4
		opword 0x801D0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B5A0001
		opword 0x2C1A0040
		opword 0x4180FFA8
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48001010
		opword 0x3BA00000
		opword 0x7FE3FB78
		opword 0x7FA4EB78
		bl BattleGetUnitPtr
		opword 0x7C7B1B79
		opword 0x41820048
		opword 0x38800017
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820034
		lis r3, subsetevt_status_recovery@ha
		opword 0x3880000A
		addi r3, r3, subsetevt_status_recovery@l
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901B02A4
		opword 0x801B0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3BBD0001
		opword 0x2C1D0040
		opword 0x4180FFA0
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000F68
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000F50
		opword 0x3BA00000
		opword 0x7FE3FB78
		opword 0x7FA4EB78
		bl BattleGetUnitPtr
		opword 0x7C7B1B79
		opword 0x41820048
		opword 0x38800018
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820034
		lis r3, subsetevt_status_recovery@ha
		opword 0x3880000A
		addi r3, r3, subsetevt_status_recovery@l
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901B02A4
		opword 0x801B0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3BBD0001
		opword 0x2C1D0040
		opword 0x4180FFA0
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000EA8
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000E90
		opword 0x3BA00000
		opword 0x7FE3FB78
		opword 0x7FA4EB78
		bl BattleGetUnitPtr
		opword 0x7C7B1B79
		opword 0x41820048
		opword 0x38800012
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820034
		lis r3, subsetevt_status_recovery@ha
		opword 0x3880000A
		addi r3, r3, subsetevt_status_recovery@l
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901B02A4
		opword 0x801B0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3BBD0001
		opword 0x2C1D0040
		opword 0x4180FFA0
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000DE8
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000DD0
		opword 0x3BA00000
		opword 0x7FE3FB78
		opword 0x7FA4EB78
		bl BattleGetUnitPtr
		opword 0x7C7B1B79
		opword 0x41820048
		opword 0x38800013
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820034
		lis r3, subsetevt_status_recovery@ha
		opword 0x3880000A
		addi r3, r3, subsetevt_status_recovery@l
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901B02A4
		opword 0x801B0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3BBD0001
		opword 0x2C1D0040
		opword 0x4180FFA0
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000D28
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000D10
		opword 0x3B600000
		opword 0x7FE3FB78
		opword 0x7F64DB78
		bl BattleGetUnitPtr
		opword 0x7C7A1B79
		opword 0x41820050
		opword 0x38800014
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x4182003C
		opword 0x7F43D378
		bl BtlUnit_ResetMoveStatus
		lis r3, subsetevt_status_recovery@ha
		opword 0x3880000A
		addi r3, r3, subsetevt_status_recovery@l
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901A02A4
		opword 0x801A0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B7B0001
		opword 0x2C1B0040
		opword 0x4180FF98
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000C60
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000C48
		opword 0x3BA00000
		opword 0x7FE3FB78
		opword 0x7FA4EB78
		bl BattleGetUnitPtr
		opword 0x7C7B1B79
		opword 0x41820048
		opword 0x38800015
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820034
		lis r3, subsetevt_status_recovery@ha
		opword 0x3880000A
		addi r3, r3, subsetevt_status_recovery@l
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901B02A4
		opword 0x801B0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3BBD0001
		opword 0x2C1D0040
		opword 0x4180FFA0
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000BA0
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000B88
		opword 0x3BA00000
		opword 0x7FE3FB78
		opword 0x7FA4EB78
		bl BattleGetUnitPtr
		opword 0x7C7B1B79
		opword 0x41820048
		opword 0x38800016
		bl BtlUnit_CheckRecoveryStatus
		opword 0x2C030000
		opword 0x7F9C1B78
		opword 0x41820034
		lis r3, subsetevt_status_recovery@ha
		opword 0x3880000A
		addi r3, r3, subsetevt_status_recovery@l
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901B02A4
		opword 0x801B0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3BBD0001
		opword 0x2C1D0040
		opword 0x4180FFA0
		opword 0x2C1C0000
		opword 0x41820010
		lis r3, str_802EF598@ha
		addi r3, r3, str_802EF598@l
		bl psndSFXOn
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000AE0
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000AC8
		opword 0x3B600000
		opword 0x7FE3FB78
		opword 0x7F64DB78
		bl BattleGetUnitPtr
		opword 0x7C7A1B79
		opword 0x4182007C
		opword 0x3880001B
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x4082006C
		opword 0xA81A010C
		opword 0x2C000000
		opword 0x40810060
		opword 0x7F43D378
		opword 0x38A10009
		opword 0x38C10008
		opword 0x38800004
		bl BtlUnit_GetStatus
		opword 0x88010008
		opword 0x7C000775
		opword 0x40810040
		opword 0x7F43D378
		bl BtlUnit_CheckShadowGuard
		opword 0x2C030000
		opword 0x40820030
		opword 0x88C10008
		opword 0x7F44D378
		opword 0x3BC00001
		opword 0x3860FFFB
		opword 0x7CC60774
		opword 0x38A00000
		opword 0x38E00000
		opword 0x39000117
		opword 0x39200000
		opword 0x39400001
		bl BattleDamageDirect
		opword 0x3B7B0001
		opword 0x2C1B0040
		opword 0x4180FF6C
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000A00
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480009E8
		opword 0x3B600000
		opword 0x7FE3FB78
		opword 0x7F64DB78
		bl BattleGetUnitPtr
		opword 0x7C7A1B79
		opword 0x41820048
		opword 0x3880001B
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x40820038
		opword 0xA81A010C
		opword 0x2C000000
		opword 0x4081002C
		opword 0x7F43D378
		opword 0x38A10009
		opword 0x38C10008
		opword 0x38800008
		bl BtlUnit_GetStatus
		opword 0x88010008
		opword 0x7C000775
		opword 0x4081000C
		opword 0x3BC00001
		opword 0x48000010
		opword 0x3B7B0001
		opword 0x2C1B0040
		opword 0x4180FFA0
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000954
		opword 0x38000000
		opword 0x7FE3FB78
		opword 0xB01F0002
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000934
		opword 0xA07F0002
		opword 0x2C030001
		opword 0x41820088
		opword 0x408000D4
		opword 0x2C030000
		opword 0x40800008
		opword 0x480000C8
		opword 0x38030001
		opword 0x3B600000
		opword 0xB01F0002
		opword 0x7FE3FB78
		opword 0x7F64DB78
		bl BattleGetUnitPtr
		opword 0x7C7A1B79
		opword 0x4182004C
		opword 0x3880001B
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x4082003C
		opword 0xA81A010C
		opword 0x2C000000
		opword 0x40810030
		opword 0x7F43D378
		opword 0x38A10009
		opword 0x38C10008
		opword 0x38800008
		bl BtlUnit_GetStatus
		opword 0x88010008
		opword 0x7C000775
		opword 0x40810010
		opword 0x7F43D378
		opword 0x38800001
		bl BSE_TurnFirstProcessEffectEntry
		opword 0x3B7B0001
		opword 0x2C1B0040
		opword 0x4180FF9C
		opword 0x3B200001
		opword 0x3B600000
		opword 0x7FE3FB78
		opword 0x7F64DB78
		bl BattleGetUnitPtr
		opword 0x28030000
		opword 0x41820014
		bl BSE_TurnFirstProcessEffectMain
		opword 0x2C030000
		opword 0x41820008
		opword 0x3B200000
		opword 0x3B7B0001
		opword 0x2C1B0040
		opword 0x4180FFD4
		opword 0x2C190000
		opword 0x41820864
		opword 0xA07F0002
		opword 0x38030001
		opword 0xB01F0002
		opword 0x48000854
		opword 0x7FE3FB78
		bl BattleWaitAllActiveEvtEnd
		opword 0x2C030000
		opword 0x41820844
		opword 0x7FE3FB78
		bl BattleCheckConcluded
		opword 0x2C030000
		opword 0x41820028
		opword 0x7FE3FB78
		opword 0x38800000
		opword 0x38A00003
		bl BattleSetSeq
		opword 0x7FE3FB78
		opword 0x38800007
		opword 0x3CA00700
		bl BattleSetSeq
		opword 0x48000810
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x48000800
		opword 0x3BA00000
		opword 0x7FE3FB78
		opword 0x7FA4EB78
		bl BattleGetUnitPtr
		opword 0x7C7C1B79
		opword 0x41820144
		opword 0x3880001B
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x40820134
		opword 0xA81C010C
		opword 0x2C000000
		opword 0x40810128
		opword 0x7F83E378
		opword 0x38A10009
		opword 0x38C10008
		opword 0x38800017
		bl BtlUnit_GetStatus
		opword 0x88810008
		opword 0x7C800775
		opword 0x40810108
		opword 0x801C0104
		opword 0x54000043
		opword 0x40820044
		opword 0xA81C010C
		opword 0x7F83E378
		opword 0x901C0204
		opword 0x88810008
		opword 0x7C840774
		bl BtlUnit_RecoverHp
		opword 0xA81C010C
		opword 0x901C0208
		opword 0xA81C01FE
		opword 0xB01C01FC
		opword 0xA81C0202
		opword 0xB01C0200
		opword 0xA01C01FA
		opword 0x60000001
		opword 0xB01C01FA
		opword 0x48000010
		opword 0x7F83E378
		opword 0x7C840774
		bl BtlUnit_RecoverHp
		opword 0x7F83E378
		bl BtlUnit_GetBodyPartsId
		opword 0x7C641B78
		opword 0x7F83E378
		bl BtlUnit_GetPartsPtr
		opword 0x38810038
		opword 0x38A10034
		opword 0x38C10030
		bl BtlUnit_GetPartsWorldPos
		opword 0x7F83E378
		bl BtlUnit_GetHeight
		opword 0x38630005
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802ef590@ha
		opword 0x9061004C
		addi r5, r4, double_to_int_802ef590@l
		opword 0x88810008
		opword 0x38600000
		opword 0x90010048
		opword 0xC8250000
		opword 0x7C840774
		opword 0xC8010048
		opword 0xC05C0114
		opword 0xEC800828
		opword 0xC0010034
		opword 0xC0210038
		opword 0xC0610030
		opword 0xEC42013A
		opword 0xD0410034
		bl effRecoveryEntry
		lis r3, subsetevt_regeneration@ha
		opword 0x3880000A
		addi r3, r3, subsetevt_regeneration@l
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901C02A4
		opword 0x801C0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3BBD0001
		opword 0x2C1D0040
		opword 0x4180FEA4
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000670
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000658
		opword 0x3B600000
		opword 0x7FE3FB78
		opword 0x7F64DB78
		bl BattleGetUnitPtr
		opword 0x7C7A1B79
		opword 0x418200F8
		opword 0x3880001B
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x408200E8
		opword 0xA81A010C
		opword 0x2C000000
		opword 0x408100DC
		opword 0x7F43D378
		opword 0x38A10009
		opword 0x38C10008
		opword 0x38800018
		bl BtlUnit_GetStatus
		opword 0x88810008
		opword 0x7C800775
		opword 0x408100BC
		opword 0x7F43D378
		opword 0x7C840774
		bl BtlUnit_RecoverFp
		opword 0x7F43D378
		bl BtlUnit_GetBodyPartsId
		opword 0x7C641B78
		opword 0x7F43D378
		bl BtlUnit_GetPartsPtr
		opword 0x3881002C
		opword 0x38A10028
		opword 0x38C10024
		bl BtlUnit_GetPartsWorldPos
		opword 0x7F43D378
		bl BtlUnit_GetHeight
		opword 0x38630005
		opword 0x3C004330
		opword 0x6C638000
		lis r4, double_to_int_802ef590@ha
		opword 0x9061004C
		addi r5, r4, double_to_int_802ef590@l
		opword 0x88810008
		opword 0x38600001
		opword 0x90010048
		opword 0xC8250000
		opword 0x7C840774
		opword 0xC8010048
		opword 0xC05A0114
		opword 0xEC800828
		opword 0xC0010028
		opword 0xC021002C
		opword 0xC0610024
		opword 0xEC42013A
		opword 0xD0410028
		bl effRecoveryEntry
		lis r3, subsetevt_regeneration@ha
		opword 0x3880000A
		addi r3, r3, subsetevt_regeneration@l
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901A02A4
		opword 0x801A0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3B7B0001
		opword 0x2C1B0040
		opword 0x4180FEF0
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000514
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480004FC
		opword 0xA81F0000
		opword 0x2C000001
		opword 0x41810028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480004CC
		opword 0x3BA00000
		opword 0x7FE3FB78
		opword 0x7FA4EB78
		bl BattleGetUnitPtr
		opword 0x7C7C1B79
		opword 0x4182012C
		opword 0x3880001B
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x4082011C
		opword 0xA81C010C
		opword 0x2C000000
		opword 0x40810110
		opword 0x8B3C02EA
		opword 0x3B600000
		opword 0x48000030
		opword 0xA89C010C
		opword 0x38600064
		opword 0xA81C0108
		opword 0x7C0403D6
		opword 0x1C000003
		opword 0x23400021
		bl irand
		opword 0x7C03D000
		opword 0x40800008
		opword 0x3B7B0001
		opword 0x3B39FFFF
		opword 0x2C190000
		opword 0x4181FFD0
		opword 0x2C1B0000
		opword 0x408100C8
		opword 0xA81C010C
		opword 0x7C00DA14
		opword 0xB01C010C
		opword 0xA81C010C
		opword 0xA87C0108
		opword 0x7C001800
		opword 0x40810008
		opword 0xB07C010C
		opword 0x7F83E378
		bl BtlUnit_GetBodyPartsId
		opword 0x7C641B78
		opword 0x7F83E378
		bl BtlUnit_GetPartsPtr
		opword 0x38810020
		opword 0x38A1001C
		opword 0x38C10018
		bl BtlUnit_GetPartsWorldPos
		opword 0x7F83E378
		bl BtlUnit_GetHeight
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_802ef590@ha
		opword 0x9061004C
		addi r3, r4, double_to_int_802ef590@l
		opword 0xC05C0114
		opword 0x90010048
		opword 0x7F64DB78
		opword 0xC8630000
		opword 0x38600000
		opword 0xC8210048
		opword 0xC001001C
		opword 0xEC811828
		opword 0xC0210020
		opword 0xC0610018
		opword 0xEC42013A
		opword 0xD041001C
		bl effRecoveryEntry
		lis r3, subsetevt_happy_heart@ha
		opword 0x3880000A
		addi r3, r3, subsetevt_happy_heart@l
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901C02A4
		opword 0x801C0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3BBD0001
		opword 0x2C1D0040
		opword 0x4180FEBC
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000354
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x48000344
		opword 0xA81F0000
		opword 0x2C000001
		opword 0x41810028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000314
		opword 0x3BA00000
		opword 0x7FE3FB78
		opword 0x7FA4EB78
		bl BattleGetUnitPtr
		opword 0x7C7A1B79
		opword 0x41820118
		opword 0x3880001B
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x40820108
		opword 0xA81A010C
		opword 0x2C000000
		opword 0x408100FC
		opword 0x8B3A02EB
		opword 0x3B600000
		opword 0x48000030
		opword 0xA89A0112
		opword 0x38600064
		opword 0xA81A010E
		opword 0x7C0403D6
		opword 0x1C000003
		opword 0x23800021
		bl irand
		opword 0x7C03E000
		opword 0x40800008
		opword 0x3B7B0001
		opword 0x3B39FFFF
		opword 0x2C190000
		opword 0x4181FFD0
		opword 0x2C1B0000
		opword 0x408100B4
		opword 0x7F43D378
		opword 0x7F64DB78
		bl BtlUnit_RecoverFp
		opword 0x7F43D378
		bl BtlUnit_GetBodyPartsId
		opword 0x7C641B78
		opword 0x7F43D378
		bl BtlUnit_GetPartsPtr
		opword 0x38810014
		opword 0x38A10010
		opword 0x38C1000C
		bl BtlUnit_GetPartsWorldPos
		opword 0x7F43D378
		bl BtlUnit_GetHeight
		opword 0x6C638000
		opword 0x3C004330
		lis r4, double_to_int_802ef590@ha
		opword 0x9061004C
		addi r3, r4, double_to_int_802ef590@l
		opword 0xC05A0114
		opword 0x90010048
		opword 0x7F64DB78
		opword 0xC8630000
		opword 0x38600001
		opword 0xC8210048
		opword 0xC0010010
		opword 0xEC811828
		opword 0xC0210014
		opword 0xC061000C
		opword 0xEC42013A
		opword 0xD0410010
		bl effRecoveryEntry
		lis r3, subsetevt_happy_flower@ha
		opword 0x3880000A
		addi r3, r3, subsetevt_happy_flower@l
		opword 0x38A00000
		bl evtEntry
		opword 0x28030000
		opword 0x41820014
		opword 0x8003015C
		opword 0x901A02A4
		opword 0x801A0000
		opword 0x90030160
		opword 0x3BC00001
		opword 0x3BBD0001
		opword 0x2C1D0040
		opword 0x4180FED0
		opword 0x2C1E0000
		opword 0x40820028
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480001B0
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000198
		opword 0x3C9F0002
		opword 0x80649038
		opword 0x2C030000
		opword 0x4182000C
		opword 0x3803FFFF
		opword 0x90049038
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x4800015C
		opword 0x3C9F0002
		opword 0x8064903C
		opword 0x2C030000
		opword 0x4182000C
		opword 0x3803FFFF
		opword 0x9004903C
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000120
		opword 0x3C9F0002
		opword 0x80649040
		opword 0x2C030000
		opword 0x4182000C
		opword 0x3803FFFF
		opword 0x90049040
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480000E4
		opword 0x3C9F0002
		opword 0x80649044
		opword 0x2C030000
		opword 0x4182000C
		opword 0x3803FFFF
		opword 0x90049044
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x480000A8
		opword 0x3C9F0002
		opword 0x80649048
		opword 0x2C030000
		opword 0x4182000C
		opword 0x3803FFFF
		opword 0x90049048
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x4800006C
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		bl btlseqTurn
		opword 0x48000054
		opword 0x7FE3FB78
		opword 0x38800003
		bl BattleIncSeq
		opword 0x7FE3FB78
		opword 0x38800004
		opword 0x3CA00400
		bl BattleSetSeq
		opword 0x48000034
		opword 0x7FE3FB78
		bl btlseqPhase
		opword 0x48000028
		bl BattleAudience_Case_TurnEnd
		opword 0x3C800300
		opword 0x7FE3FB78
		opword 0x38A40001
		opword 0x38800003
		bl BattleSetSeq
		opword 0x801F0EF4
		opword 0x540004E2
		opword 0x901F0EF4
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void _rule_disp(CameraId cameraId, void* param) {
	char _af_pad[296];
	asm volatile {
		lwz r5, _battleWorkPointer(r13)
		lis r6, lbl_80360FE0@ha
		opword 0x3C80F5DE
		opword 0x38600000
		lwz r30, 0x2738(r5)
		addi r31, r6, lbl_80360FE0@l
		opword 0x38840180
		bl evtGetValue
		opword 0x2C0300AC
		opword 0x40800074
		opword 0x3C80F5DE
		opword 0x38600000
		opword 0x388403C4
		bl evtGetValue
		opword 0x2C03000B
		opword 0x40800030
		opword 0x881E0018
		opword 0x387F0150
		opword 0x5400103A
		opword 0x7C63002E
		bl msgSearch
		opword 0x88BE001A
		opword 0x7C641B78
		la r3, _af_pad+8
		opword 0x4CC63182
		bl sprintf
		opword 0x48000058
		opword 0x881E0018
		opword 0x387F0040
		opword 0x5400103A
		opword 0x7C63002E
		bl msgSearch
		opword 0x88BE001A
		opword 0x7C641B78
		opword 0x38610010
		opword 0x4CC63182
		bl sprintf
		opword 0x4800002C
		opword 0x881E0018
		opword 0x387F0260
		opword 0x5400103A
		opword 0x7C63002E
		bl msgSearch
		opword 0x88BE001A
		opword 0x7C641B78
		opword 0x38610010
		opword 0x4CC63182
		bl sprintf
		opword 0x38610010
		opword 0x38810008
		bl FontGetMessageWidthLine
		opword 0xA0810008
		opword 0x5460FC7E
		opword 0x3CC04330
		opword 0x5465043E
		opword 0x39040001
		opword 0x6C038000
		lis r4, double_to_int_802ef590@ha
		opword 0x90C10110
		lfd f4, double_to_int_802ef590@l(r4)
		opword 0x5500043E
		opword 0x90610114
		opword 0x1C60001D
		opword 0x38A50014
		lwz r7, dat_8041c26c(r2)
		opword 0xC8010110
		opword 0x3881000C
		opword 0x38030003
		opword 0x6CA58000
		opword 0xEC002028
		lfs f1, float_0_8041c280(r2)
		opword 0x6C008000
		opword 0x90A1011C
		opword 0x38600000
		fsubs f31, f1, f0
		opword 0x90C10118
		lfs f5, float_10_8041c2a0(r2)
		opword 0xC8010118
		opword 0x90010124
		opword 0xEC3F2828
		opword 0xEC602028
		lfs f2, float_94_8041c2a4(r2)
		opword 0x90C10120
		opword 0xC8010120
		opword 0xB1010008
		opword 0xEC802028
		opword 0x90E1000C
		bl windowDispGX_Waku_col
		bl FontDrawStart
		lfs f0, float_120_8041c2a8(r2)
		opword 0xFC20F81E
		opword 0x38A10010
		opword 0xFC00001E
		opword 0xD8210128
		opword 0xD8010130
		opword 0x8061012C
		opword 0x80810134
		opword 0x3884FFE3
		bl FontDrawMessage
	}
}
#pragma pop

#pragma dont_inline on
#pragma defer_codegen off
void btlseqPhase(BattleWork* wp) {
	switch (BattleGetSeq(wp, SEQ_PHASE)) {
		case 0x4000000:
			BattleIncSeq(wp, SEQ_PHASE);
			BattleSetSeq(wp, SEQ_MOVE, 0x5000000);
			break;
		case 0x4000001:
		case 0x4000002:
		case 0x4000003:
		case 0x4000004:
		case 0x4000005:
			btlseqMove(wp);
			break;
		case 0x4000006:
			BattleIncSeq(wp, SEQ_TURN);
			BattleSetSeq(wp, SEQ_PHASE, 0x4000000);
			break;
	}
}

#pragma defer_codegen reset
#pragma dont_inline reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm s32 _set_effect_luck(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	lis r3, N_weapon_lucky_start@ha
	stw r0, 0x104(r1)
	addi r3, r3, N_weapon_lucky_start@l
	li r0, 0x18
	addi r5, r1, 0x10
	stmw r24, 0xe0(r1)
	subi r4, r3, 0x4
	lwz r31, _battleWorkPointer(r13)
	mtctr r0
	L_g5_1:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz L_g5_1
	lis r3, str_802EF5C8@ha
	addi r30, r1, 0x14
	addi r27, r3, str_802EF5C8@l
	addi r29, r1, 0x10
	addi r28, r1, 0xc
	li r24, 0x0
	L_g5_2:
	mr r3, r31
	mr r4, r24
	bl BattleGetUnitPtr
	mr. r26, r3
	beq L_g5_3
	lbz r0, 0x300(r26)
	cmplwi r0, 0x0
	beq L_g5_3
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_3
	li r3, 0x4
	bl irand
	cmpwi r3, 0x1
	beq L_g5_4
	bge L_g5_5
	cmpwi r3, 0x0
	bge L_g5_6
	b L_g5_7
	L_g5_5:
	cmpwi r3, 0x3
	bge L_g5_7
	b L_g5_8
	L_g5_6:
	li r0, 0x0
	stb r0, 0xa1(r1)
	stb r0, 0xa2(r1)
	stb r0, 0xbe(r1)
	stb r0, 0xbf(r1)
	stb r0, 0xc0(r1)
	stb r0, 0xc1(r1)
	b L_g5_9
	L_g5_4:
	li r0, 0x0
	stb r0, 0x9f(r1)
	stb r0, 0xa0(r1)
	stb r0, 0xbe(r1)
	stb r0, 0xbf(r1)
	stb r0, 0xc0(r1)
	stb r0, 0xc1(r1)
	b L_g5_9
	L_g5_8:
	li r0, 0x0
	stb r0, 0x9f(r1)
	stb r0, 0xa0(r1)
	stb r0, 0xa1(r1)
	stb r0, 0xa2(r1)
	stb r0, 0xc0(r1)
	stb r0, 0xc1(r1)
	b L_g5_9
	L_g5_7:
	li r0, 0x0
	stb r0, 0x9f(r1)
	stb r0, 0xa0(r1)
	stb r0, 0xa1(r1)
	stb r0, 0xa2(r1)
	stb r0, 0xbe(r1)
	stb r0, 0xbf(r1)
	L_g5_9:
	mr r3, r26
	bl BtlUnit_GetBodyPartsId
	mr r4, r3
	mr r3, r26
	bl BtlUnit_GetPartsPtr
	mr r0, r3
	mr r3, r31
	mr r25, r0
	bl BattleGetSystemPtr
	mr r4, r26
	mr r5, r25
	mr r6, r30
	li r7, 0x100
	bl BattleSetStatusDamageFromWeapon
	mr r3, r26
	mr r5, r28
	mr r6, r29
	addi r4, r1, 0x8
	bl BtlUnit_GetPos
	mr r3, r27
	bl psndSFXOn
	lfs f3, 0x8(r1)
	li r3, 0x6
	lfs f1, float_45_8041c2b0(r2)
	lfs f2, float_60_8041c2b4(r2)
	lfs f0, 0xc(r1)
	fsubs f1, f3, f1
	lfs f3, 0x10(r1)
	fadds f2, f2, f0
	bl effNiceEntry
	lfs f0, float_0p75_8041c2b8(r2)
	lwz r3, 0xc(r3)
	stfs f0, 0x1c(r3)
	L_g5_3:
	addi r24, r24, 0x1
	cmpwi r24, 0x40
	blt L_g5_2
	lmw r24, 0xe0(r1)
	li r3, 0x2
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void btlseqFirstAct(BattleWork* wp) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x38800002
		opword 0x90010034
		opword 0xBF810020
		opword 0x7C7E1B78
		opword 0x80A32738
		opword 0x83E50008
		bl BattleGetSeq
		opword 0x3C03FE00
		opword 0x2800000E
		opword 0x418107B8
		lis r3, jumptable_80361500@ha
		opword 0x5400103A
		addi r3, r3, jumptable_80361500@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x2C1F0000
		opword 0x41820008
		opword 0x480000FC
		opword 0x38000000
		la r3, _default_haikei_set_entry_event(r13)
		opword 0x901E0EFC
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x807E2738
		opword 0x3BA00000
		opword 0x83E3000C
		opword 0x7FC3F378
		opword 0x7FA4EB78
		bl BattleGetUnitPtr
		opword 0x7C7C1B79
		opword 0x418200A0
		opword 0x801C02B4
		opword 0x28000000
		opword 0x41820094
		opword 0x801F0004
		opword 0x540002D7
		opword 0x41820020
		opword 0x801C0008
		opword 0x2C0000DE
		opword 0x4182007C
		opword 0x2C0000E0
		opword 0x4180000C
		opword 0x2C0000E7
		opword 0x4180006C
		bl marioGetPtr
		opword 0xA003002E
		opword 0x2800001A
		opword 0x4082003C
		opword 0x801C0008
		opword 0x2C0000DE
		opword 0x40820030
		opword 0x7F83E378
		opword 0x38800041
		bl BtlUnit_GetData
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x8003015C
		opword 0x901C02B8
		opword 0x801C0000
		opword 0x90030160
		opword 0x48000024
		opword 0x807C02B4
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x8003015C
		opword 0x901C02B8
		opword 0x801C0000
		opword 0x90030160
		opword 0x3BBD0001
		opword 0x2C1D0040
		opword 0x4180FF48
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A40001
		opword 0x38800002
		bl BattleSetSeq
		opword 0x4800069C
		opword 0x2C1F0004
		opword 0x40800010
		opword 0x2C1F0001
		opword 0x40800014
		opword 0x48000028
		opword 0x2C1F0009
		opword 0x40800020
		opword 0x48000010
		opword 0x3800000A
		opword 0x901E0EFC
		opword 0x48000018
		opword 0x38000000
		opword 0x901E0EFC
		opword 0x4800000C
		opword 0x38000000
		opword 0x901E0EFC
		opword 0x801E0EF4
		opword 0x7FC3F378
		opword 0x38810010
		opword 0x38A1000C
		opword 0x60000002
		opword 0x901E0EF4
		bl BattleGetFirstAttackUnit
		opword 0x80610010
		opword 0x3880000A
		opword 0x38A00020
		opword 0x80030000
		opword 0x901E0420
		opword 0x80610010
		opword 0x80030278
		opword 0x60001000
		opword 0x90030278
		opword 0x8061000C
		opword 0x806302AC
		bl evtEntry
		opword 0x28030000
		opword 0x41820028
		opword 0x8081000C
		opword 0x38000039
		opword 0x80840000
		opword 0x90830160
		opword 0x8081000C
		opword 0x90040274
		opword 0x8003015C
		opword 0x8061000C
		opword 0x900302B0
		opword 0x80610010
		opword 0x2C1F0009
		opword 0x8003001C
		opword 0x64000400
		opword 0x9003001C
		opword 0x40800028
		opword 0x7FE3FB78
		bl _GetFirstAttackWeapon
		opword 0x808300B0
		opword 0x38000000
		opword 0x80610010
		opword 0x9083029C
		opword 0x80610010
		opword 0x900302A8
		bl BattleStatusWindowEventOff
		opword 0x80610010
		bl BtlUnit_GetBelong
		opword 0x7C600775
		opword 0x4082000C
		bl BattleAudience_Case_FirstAttack_Good
		opword 0x48000008
		bl BattleAudience_Case_FirstAttack_Bad
		opword 0x80610010
		opword 0x3880000A
		opword 0x38A00000
		opword 0x8063029C
		bl evtEntry
		opword 0x28030000
		opword 0x4182001C
		opword 0x80810010
		opword 0x80040000
		opword 0x90030160
		opword 0x8003015C
		opword 0x80610010
		opword 0x900302A4
		opword 0x2C1F0007
		opword 0x40800010
		opword 0x2C1F0001
		opword 0x40800014
		opword 0x48000074
		opword 0x2C1F0009
		opword 0x4080006C
		opword 0x48000038
		opword 0x7FC3F378
		bl BattleGetPartyPtr
		opword 0x7C7F1B79
		opword 0x41820058
		opword 0x807F02B4
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x8003015C
		opword 0x901F02B8
		opword 0x801F0000
		opword 0x90030160
		opword 0x48000034
		opword 0x7FC3F378
		bl BattleGetMarioPtr
		opword 0x7C7F1B79
		opword 0x41820024
		opword 0x807F02B4
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x8003015C
		opword 0x901F02B8
		opword 0x801F0000
		opword 0x90030160
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A40001
		opword 0x38800002
		bl BattleSetSeq
		opword 0x480004BC
		opword 0x807E0EFC
		opword 0x3403FFFF
		opword 0x901E0EFC
		opword 0x418104AC
		lwz r0, dat_8041c268(r2)
		opword 0x38A10008
		opword 0x38600017
		opword 0x388000C8
		opword 0x90010008
		bl fadeEntry
		lis r3, str_802EF5DC@ha
		addi r3, r3, str_802EF5DC@l
		bl psndSFXOn
		opword 0x3CBE0002
		opword 0x3C800200
		opword 0x90659060
		opword 0x7FC3F378
		opword 0x38A40002
		opword 0x38800002
		bl BattleSetSeq
		bl fadeIsFinish
		opword 0x2C030000
		opword 0x41820028
		opword 0x3C7E0002
		opword 0x80639060
		opword 0x3C030001
		opword 0x2800FFFF
		opword 0x41820014
		bl psndSFXOff
		opword 0x3C7E0002
		opword 0x3800FFFF
		opword 0x90039060
		opword 0x7FC3F378
		bl BattleWaitAllActiveEvtEnd
		opword 0x2C030000
		opword 0x41820008
		bl BattleStatusWindowEventOn
		opword 0x7FC3F378
		bl BattleWaitAllActiveEvtEnd
		opword 0x2C030000
		opword 0x41820418
		bl fadeIsFinish
		opword 0x2C030000
		opword 0x4182040C
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A40003
		opword 0x38800002
		bl BattleSetSeq
		opword 0x809E0420
		opword 0x7FC3F378
		bl BattleGetUnitPtr
		opword 0x28030000
		opword 0x418203E4
		opword 0x8003001C
		opword 0x54000188
		opword 0x9003001C
		opword 0x480003D4
		opword 0x7FC3F378
		bl BattleCheckConcluded
		opword 0x2C030000
		opword 0x4182002C
		bl BattleAudience_PerAct
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A00003
		bl BattleSetSeq
		opword 0x7FC3F378
		opword 0x38800007
		opword 0x3CA00700
		bl BattleSetSeq
		opword 0x4800039C
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A40004
		opword 0x38800002
		bl BattleSetSeq
		opword 0x7FC3F378
		bl BattleStatusChangeMsgAdjust
		opword 0x7FC3F378
		bl BattleWaitAllActiveEvtEnd
		opword 0x2C030000
		opword 0x41820370
		opword 0x7FC3F378
		bl BattleStatusChangeMsgMain
		opword 0x7C7F1B78
		opword 0x7FC3F378
		bl BattleStatusChangeAnnouceMain
		opword 0x7C60FB79
		opword 0x40820354
		opword 0x7FC3F378
		opword 0x38800002
		bl BattleIncSeq
		opword 0x801E0EF4
		opword 0x540006B7
		opword 0x40820008
		bl BattleStatusWindowSystemOn
		bl BattleConsumeReserveItem
		opword 0x801E0EF4
		opword 0x540007B8
		opword 0x901E0EF4
		bl BattleAudience_PerAct
		opword 0x7FC3F378
		opword 0x38800002
		bl BattleIncSeq
		bl BattleAudience_CheckReaction
		opword 0x5460063F
		opword 0x4082030C
		opword 0x7FC3F378
		bl BattleCheckConcluded
		opword 0x2C030000
		opword 0x40820010
		bl BattleBreakSlot_CheckReaction
		opword 0x5460063F
		opword 0x408202F0
		opword 0x7FC3F378
		opword 0x38800002
		bl BattleIncSeq
		opword 0x7FC3F378
		bl BattleStatusChangeMsgMain
		opword 0x7C7F1B78
		opword 0x7FC3F378
		bl BattleStatusChangeAnnouceMain
		opword 0x7C60FB79
		opword 0x408202C8
		opword 0x7FC3F378
		opword 0x38800002
		bl BattleIncSeq
		opword 0x7FC3F378
		bl BattleWaitAllActiveEvtEnd
		opword 0x2C030000
		opword 0x418202AC
		opword 0x807E2738
		opword 0x8063000C
		opword 0x80030004
		opword 0x540006F7
		opword 0x41820020
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A40009
		opword 0x38800002
		bl BattleSetSeq
		bl BattleStage_WallCloseCheck
		opword 0x4800027C
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A4000A
		opword 0x38800002
		bl BattleSetSeq
		opword 0x48000264
		opword 0x3F9E0002
		opword 0x807C82A4
		opword 0x2C030000
		opword 0x41820018
		bl evtCheckID
		opword 0x2C030000
		opword 0x4082000C
		opword 0x38000000
		opword 0x901C82A4
		opword 0x801C82A4
		opword 0x2C000000
		opword 0x40820234
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A4000A
		opword 0x38800002
		bl BattleSetSeq
		opword 0x4800021C
		opword 0x3C7E0002
		opword 0x38000000
		opword 0x9003904C
		opword 0x3B800000
		opword 0x3BA00000
		opword 0x7FC3F378
		opword 0x7FA4EB78
		bl BattleGetUnitPtr
		opword 0x28030000
		opword 0x41820024
		opword 0x88030300
		opword 0x28000000
		opword 0x41820018
		opword 0x3880001B
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x40820008
		opword 0x3B800001
		opword 0x3BBD0001
		opword 0x2C1D0040
		opword 0x4180FFC4
		opword 0x2C1C0000
		opword 0x41820070
		la r3, nanika_luck_event(r13)
		opword 0x3880000A
		opword 0x38A00000
		bl evtEntry
		opword 0x3800FFFB
		opword 0x3CDE0002
		opword 0x90030160
		opword 0x3880FFFF
		opword 0x8003015C
		opword 0x7FC3F378
		opword 0x9006904C
		opword 0x80068FDC
		opword 0x80A68FD8
		opword 0x7C002378
		opword 0x90068FDC
		opword 0x7CA02378
		opword 0x90068FD8
		bl BattleStatusChangeMsgAdjust
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A4000B
		opword 0x38800002
		bl BattleSetSeq
		opword 0x3C7E0002
		opword 0x38000000
		opword 0xB0038FE2
		opword 0x48000154
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A4000C
		opword 0x38800002
		bl BattleSetSeq
		opword 0x4800013C
		opword 0x3C9E0002
		opword 0x3B800001
		opword 0xA0648FE2
		opword 0x2803012C
		opword 0x4080000C
		opword 0x38030001
		opword 0xB0048FE2
		opword 0x3C7E0002
		opword 0x8063904C
		opword 0x2C030000
		opword 0x41820024
		bl evtCheckID
		opword 0x2C030000
		opword 0x4182000C
		opword 0x3B800000
		opword 0x48000010
		opword 0x3C7E0002
		opword 0x38000000
		opword 0x9003904C
		opword 0x7FC3F378
		bl BattleWaitAllActiveEvtEnd
		opword 0x2C030000
		opword 0x40820008
		opword 0x3B800000
		opword 0x7FC3F378
		bl BattleStatusChangeAnnouceMain
		opword 0x2C030000
		opword 0x41820008
		opword 0x3B800000
		opword 0x7FC3F378
		bl BattleStatusChangeMsgMain
		opword 0x2C030000
		opword 0x41820008
		opword 0x3B800000
		opword 0x2C1C0000
		opword 0x418200AC
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A4000C
		opword 0x38800002
		bl BattleSetSeq
		opword 0x48000094
		opword 0x801E0EF4
		opword 0x540007BD
		opword 0x4182001C
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A4000E
		opword 0x38800002
		bl BattleSetSeq
		opword 0x48000070
		opword 0x38600000
		bl BattleStage_NozzleWorkCheck
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A4000D
		opword 0x38800002
		bl BattleSetSeq
		opword 0x7FC3F378
		bl BattleWaitAllActiveEvtEnd
		opword 0x2C030000
		opword 0x41820044
		opword 0x3C800200
		opword 0x7FC3F378
		opword 0x38A4000E
		opword 0x38800002
		bl BattleSetSeq
		opword 0x801E0EF4
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A00002
		opword 0x540007FA
		opword 0x901E0EF4
		bl BattleSetSeq
		opword 0x7FC3F378
		opword 0x38800003
		opword 0x3CA00300
		bl BattleSetSeq
		opword 0xBB810020
		opword 0x80010034
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop

#pragma defer_codegen reset

asm BattleWeapon* _GetFirstAttackWeapon(s32 type) {
	nofralloc
	cmplwi r3, 0x8
	bgt L_g5_1
	lis r4, jumptable_8036153C@ha
	slwi r0, r3, 2
	addi r3, r4, jumptable_8036153C@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_g5_2:
	lis r3, marioDefaultWeapon_Jump@ha
	addi r3, r3, marioDefaultWeapon_Jump@l
	blr
	L_g5_3:
	lis r3, marioWeapon_KururinJump@ha
	addi r3, r3, marioWeapon_KururinJump@l
	blr
	L_g5_4:
	lis r3, marioDefaultWeapon_Jump@ha
	addi r3, r3, marioDefaultWeapon_Jump@l
	blr
	L_g5_5:
	lis r3, marioDefaultWeapon_Hammer@ha
	addi r3, r3, marioDefaultWeapon_Hammer@l
	blr
	L_g5_6:
	lis r3, marioDefaultWeapon_FirstAttackKaitenHammer@ha
	addi r3, r3, marioDefaultWeapon_FirstAttackKaitenHammer@l
	blr
	L_g5_7:
	lis r3, marioDefaultWeapon_FirstAttackUltraHammer@ha
	addi r3, r3, marioDefaultWeapon_FirstAttackUltraHammer@l
	blr
	L_g5_8:
	lis r3, partyWeapon_NokotarouFirstAttack@ha
	addi r3, r3, partyWeapon_NokotarouFirstAttack@l
	blr
	L_g5_9:
	lis r3, partyWeapon_SandersFirstAttack@ha
	addi r3, r3, partyWeapon_SandersFirstAttack@l
	blr
	L_g5_1:
	li r3, 0x0
	blr
}

#pragma dont_inline on
void BattleSequenceManager(void) { //1:1
	BattleWork* wp = _battleWorkPointer;
	switch (BattleGetSeq(wp, SEQ_UNKNOWN)) {
		case 0:
			btlseqInit(wp);
			BattleCheckAllPinchStatus(wp, TRUE);
			break;
		case 1:
			BattleCheckAllPinchStatus(wp, FALSE);
			btlseqFirstAct(wp);
			break;
		case 2:
			BattleCheckAllPinchStatus(wp, FALSE);
			btlseqTurn(wp);
			break;
		case 3:
			btlseqEnd(wp);
			break;
		case 4:
			break;
	}
}
#pragma dont_inline reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void BattleCheckAllPinchStatus(BattleWork* wp, BOOL a2) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0xBF810010
		opword 0x7C7F1B78
		opword 0x7C9D2378
		opword 0x3B800000
		opword 0x7FE3FB78
		opword 0x7F84E378
		bl BattleGetUnitPtr
		opword 0x28030000
		opword 0x4182000C
		opword 0x7FA4EB78
		bl BtlUnit_CheckPinchStatus
		opword 0x3B9C0001
		opword 0x2C1C0040
		opword 0x4180FFDC
		opword 0x3B800000
		opword 0x3BC00000
		opword 0x7FE3FB78
		opword 0x7FC4F378
		bl BattleGetUnitPtr
		opword 0x7C7D1B79
		opword 0x41820060
		opword 0x801D0138
		opword 0x54000085
		opword 0x41820054
		opword 0x3880001B
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x40820044
		opword 0x7FA3EB78
		bl BtlUnit_GetBelong
		opword 0x7C600775
		opword 0x40820034
		opword 0x801D0008
		opword 0x2C0000DE
		opword 0x41820014
		opword 0x2C0000E0
		opword 0x4180002C
		opword 0x2C0000E7
		opword 0x40800024
		opword 0xA81D010C
		opword 0x2C000000
		opword 0x40810018
		opword 0x3B800001
		opword 0x48000010
		opword 0x3BDE0001
		opword 0x2C1E0040
		opword 0x4180FF88
		opword 0x2C1C0000
		opword 0x41820044
		opword 0x3C9F0002
		opword 0x88648FE0
		opword 0x3803FFFF
		opword 0x98048FE0
		opword 0x88048FE0
		opword 0x7C000775
		opword 0x41810118
		opword 0x3800003C
		opword 0x98048FE0
		opword 0x801F1720
		opword 0x540007FF
		opword 0x41820104
		lis r3, str_802EF61C@ha
		addi r3, r3, str_802EF61C@l
		bl psndSFXOn
		opword 0x480000F4
		opword 0x3B800000
		opword 0x7F9EE378
		opword 0x7FE3FB78
		opword 0x7FC4F378
		bl BattleGetUnitPtr
		opword 0x7C7D1B79
		opword 0x41820060
		opword 0x801D0138
		opword 0x540000C7
		opword 0x41820054
		opword 0x3880001B
		bl BtlUnit_CheckStatus
		opword 0x2C030000
		opword 0x40820044
		opword 0x7FA3EB78
		bl BtlUnit_GetBelong
		opword 0x7C600775
		opword 0x40820034
		opword 0x801D0008
		opword 0x2C0000DE
		opword 0x41820014
		opword 0x2C0000E0
		opword 0x4180002C
		opword 0x2C0000E7
		opword 0x40800024
		opword 0xA81D010C
		opword 0x2C000000
		opword 0x40810018
		opword 0x3B800001
		opword 0x48000010
		opword 0x3BDE0001
		opword 0x2C1E0040
		opword 0x4180FF88
		opword 0x2C1C0000
		opword 0x41820044
		opword 0x3C9F0002
		opword 0x88648FE0
		opword 0x3803FFFF
		opword 0x98048FE0
		opword 0x88048FE0
		opword 0x7C000775
		opword 0x4181004C
		opword 0x3800003C
		opword 0x98048FE0
		opword 0x801F1720
		opword 0x540007FF
		opword 0x41820038
		lis r3, str_802EF62C@ha
		addi r3, r3, str_802EF62C@l
		bl psndSFXOn
		opword 0x48000028
		opword 0x7FE3FB78
		bl BattleGetMarioPtr
		opword 0x28030000
		opword 0x4182000C
		opword 0x38000000
		opword 0x90030234
		opword 0x3C7F0002
		opword 0x38000000
		opword 0x98038FE0
		opword 0xBB810010
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void btlseqInit(BattleWork* wp) {
	asm {
		lis r4, N_weapon_lucky_start@ha
	}
	asm volatile {
		addi r31, r4, N_weapon_lucky_start@l
		mr r30, r3
		opword 0x38800001
		bl BattleGetSeq
		opword 0x3C800100
		opword 0x38040003
		opword 0x7C030000
		opword 0x418200B8
		opword 0x40800020
		opword 0x38A40001
		opword 0x7C032800
		opword 0x41820034
		opword 0x4080007C
		opword 0x7C032000
		opword 0x4080001C
		opword 0x48000134
		opword 0x38A40005
		opword 0x7C032800
		opword 0x41820100
		opword 0x40800124
		opword 0x480000E8
		opword 0x7FC3F378
		opword 0x38800001
		bl BattleSetSeq
		bl marioGetPtr
		opword 0x80030004
		opword 0x60000001
		opword 0x90030004
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820010
		opword 0x80030004
		opword 0x60000001
		opword 0x90030004
		opword 0x7FC3F378
		bl Btl_UnitSetup
		opword 0x3C800100
		opword 0x7FC3F378
		opword 0x38A40002
		opword 0x38800001
		bl BattleSetSeq
		opword 0x480000C8
		opword 0x7FC3F378
		bl BattleCheckEndUnitInitEvent
		opword 0x2C030000
		opword 0x418200B8
		opword 0x3C800100
		opword 0x7FC3F378
		opword 0x38A40003
		opword 0x38800001
		bl BattleSetSeq
		opword 0x480000A0
		opword 0x387F03AC
		opword 0x38800001
		bl animEffectAsync
		opword 0x2C030000
		opword 0x4182008C
		opword 0x387F03B4
		opword 0x38800001
		bl animEffectAsync
		opword 0x2C030000
		opword 0x41820078
		opword 0x387F03C0
		opword 0x38800001
		bl animEffectAsync
		opword 0x2C030000
		opword 0x41820064
		opword 0x38600001
		bl effNiceAsync
		opword 0x2C030000
		opword 0x41820054
		opword 0x3C800100
		opword 0x7FC3F378
		opword 0x38A40004
		opword 0x38800001
		bl BattleSetSeq
		opword 0x4800003C
		opword 0x7FC3F378
		opword 0x38800001
		bl BattleSetSeq
		opword 0x4800002C
		bl BattleStatusWindowEventOn
		bl BattleStatusWindowSystemOn
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A00001
		bl BattleSetSeq
		opword 0x7FC3F378
		opword 0x38800002
		opword 0x3CA00200
		bl BattleSetSeq
	}
}
#pragma pop


// literal pool in target order (asmfake --minimal)
#endif
#pragma force_active on
#ifdef NONMATCHING
__declspec(section ".sdata2") const u32 gap_09_8041C2BC_sdata2[1] = {0};
#pragma force_active reset
#pragma force_active reset
#endif
#ifndef NONMATCHING
__declspec(section ".rodata") const s32 N_weapon_lucky_start[48] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x64000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x01004020, 0x10000000, 0x00000302, 0x00000000, 0x00020108, 0x000007FF, 0x80002004,
	0x00000000, 0x00000000, 0x00000064, 0x03640300, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000302, 0x03020000, 0x00000000, 0x00000064, 0x00000000, 0x00000000,
};
__declspec(section ".rodata") const char str_802EF310[] = "stg3_tou_cp_001";
__declspec(section ".rodata") const char str_802EF320[] = "stg3_tou_cp_002";
__declspec(section ".rodata") const char str_802EF330[] = "stg3_tou_cp_004";
__declspec(section ".rodata") const char str_802EF340[] = "stg3_tou_cp_008";
__declspec(section ".rodata") const char str_802EF350[] = "stg3_tou_cp_000";
__declspec(section ".rodata") const char str_802EF360[] = "stg3_tou_cp_005";
__declspec(section ".rodata") const char str_802EF370[] = "stg3_tou_cp_006";
__declspec(section ".rodata") const char str_802EF380[] = "stg3_tou_cp_009";
__declspec(section ".rodata") const char str_802EF390[] = "stg3_tou_cp_003";
__declspec(section ".rodata") const char str_802EF3A0[] = "stg3_tou_cp_007";
__declspec(section ".rodata") const char str_802EF3B0[] = "stg3_tou_cp_011";
__declspec(section ".rodata") const char str_802EF3C0[] = "stg3_tou_cp_012";
__declspec(section ".rodata") const char str_802EF3D0[] = "stg3_tou_cp_014";
__declspec(section ".rodata") const char str_802EF3E0[] = "stg3_tou_cp_019";
__declspec(section ".rodata") const char str_802EF3F0[] = "stg3_tou_cp_020";
__declspec(section ".rodata") const char str_802EF400[] = "stg3_tou_cp_010";
__declspec(section ".rodata") const char str_802EF410[] = "stg3_tou_cp_018";
__declspec(section ".rodata") const char str_802EF420[] = "stg3_tou_cp_015";
__declspec(section ".rodata") const char str_802EF430[] = "stg3_tou_cp_016";
__declspec(section ".rodata") const char str_802EF440[] = "stg3_tou_cp_021";
__declspec(section ".rodata") const char str_802EF450[] = "stg3_tou_cp_013";
__declspec(section ".rodata") const char str_802EF460[] = "stg3_tou_cp_017";
__declspec(section ".rodata") const char str_802EF470[] = "stg3_tou_cp_024";
__declspec(section ".rodata") const char str_802EF480[] = "stg3_tou_cp_023";
__declspec(section ".rodata") const char str_802EF490[] = "stg3_tou_cp_022";
__declspec(section ".rodata") const char str_802EF4A0[] = "stg3_tou_cp_041";
__declspec(section ".rodata") const char str_802EF4B0[] = "stg3_tou_cp_042";
__declspec(section ".rodata") const char str_802EF4C0[] = "stg3_tou_cp_044";
__declspec(section ".rodata") const char str_802EF4D0[] = "stg3_tou_cp_049";
__declspec(section ".rodata") const char str_802EF4E0[] = "stg3_tou_cp_050";
__declspec(section ".rodata") const char str_802EF4F0[] = "stg3_tou_cp_040";
__declspec(section ".rodata") const char str_802EF500[] = "stg3_tou_cp_048";
__declspec(section ".rodata") const char str_802EF510[] = "stg3_tou_cp_045";
__declspec(section ".rodata") const char str_802EF520[] = "stg3_tou_cp_046";
__declspec(section ".rodata") const char str_802EF530[] = "stg3_tou_cp_051";
__declspec(section ".rodata") const char str_802EF540[] = "stg3_tou_cp_043";
__declspec(section ".rodata") const char str_802EF550[] = "stg3_tou_cp_047";
__declspec(section ".rodata") const char str_802EF560[] = "stg3_tou_cp_054";
__declspec(section ".rodata") const char str_802EF570[] = "stg3_tou_cp_053";
__declspec(section ".rodata") const char str_802EF580[] = "stg3_tou_cp_052";
__declspec(section ".rodata") const f64 double_to_int_802ef590 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802EF598[] = "SFX_REST_CONDITION1";
__declspec(section ".rodata") const char str_802EF5AC[] = "SFX_CONDITION_BREAK_ICE1\0\0\0";
__declspec(section ".rodata") const char str_802EF5C8[] = "SFX_SYSTEM_LUCKY1\0\0";
__declspec(section ".rodata") const char str_802EF5DC[] = "SFX_OFF_BTL_START_CURTAIN_UP1\0\0";
__declspec(section ".rodata") const char str_802EF5FC[] = "p_b_st\0";
__declspec(section ".rodata") const char str_802EF604[] = "p_jyabara\0\0";
__declspec(section ".rodata") const char str_802EF610[] = "p_kaiten_h\0";
__declspec(section ".rodata") const char str_802EF61C[] = "SFX_BTL_DANGER1";
__declspec(section ".rodata") const char str_802EF62C[] = "SFX_BTL_PINCH1\0";
__declspec(section ".rodata") const u32 gap_04_802EF63C_rodata = 0x00000000;
__declspec(section ".sdata2") const u32 dat_8041c268 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041c26c = 0xFFFFFFFF;
__declspec(section ".sdata2") const char str_8041C270[] = "a\0\0";
__declspec(section ".sdata2") const char str_8041C274[] = "test\0\0\0";
__declspec(section ".sdata2") const char str_8041C27C[] = "A1\0";
__declspec(section ".sdata2") const f32 float_0_8041c280 = 0.0f;
__declspec(section ".sdata2") const f32 float_1_8041c284 = 1.0f;
__declspec(section ".sdata2") const char str_8041C288[] = "A2\0";
__declspec(section ".sdata2") const f32 float_110_8041c28c = 110.0f;
__declspec(section ".sdata2") const f32 float_90_8041c290 = 90.0f;
__declspec(section ".sdata2") const f32 float_100_8041c294 = 100.0f;
__declspec(section ".sdata2") const f32 float_1000_8041c298 = 1000.0f;
__declspec(section ".sdata2") const f32 float_2_8041c29c = 2.0f;
__declspec(section ".sdata2") const f32 float_10_8041c2a0 = 10.0f;
__declspec(section ".sdata2") const f32 float_94_8041c2a4 = 94.0f;
__declspec(section ".sdata2") const f32 float_120_8041c2a8 = 120.0f;
__declspec(section ".sdata2") const f32 float_900_8041c2ac = 900.0f;
__declspec(section ".sdata2") const f32 float_45_8041c2b0 = 45.0f;
__declspec(section ".sdata2") const f32 float_60_8041c2b4 = 60.0f;
__declspec(section ".sdata2") const f32 float_0p75_8041c2b8 = 0.75f;
#endif
