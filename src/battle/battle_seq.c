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
USER_FUNC(_set_haikei_entry_scale);
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
USER_FUNC(_set_effect_luck);

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


static const GXColor c = {0, 0, 0, 0xFF};
static const GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};

const char* _rule_msg_table_2bu[] = {
	"a", str_802EF310, "a", str_802EF320, "a", str_802EF330, str_802EF340, "a",
	"a", "a", "a", "a", "a", "a", "a", "a",
	"a", "a", str_802EF350, "a", "a", "a", "a", "a",
	"a", "a", str_802EF360, "a", "a", "a", "a", "a",
	str_802EF370, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF380, "a", "a", "a", "a",
	str_802EF390, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF3A0, "a", "a", "a", "a",
	"a", "a", "a", "a",
};

const char* _rule_msg_table_1bu[] = {
	"test", str_802EF3B0, "a", str_802EF3C0, "a", str_802EF3D0, str_802EF3E0, "a",
	"a", "a", "a", str_802EF3F0, "a", "a", "a", "a",
	"a", "a", str_802EF400, "a", str_802EF410, "a", "a", "a",
	"a", "a", str_802EF420, "a", "a", "a", "a", "a",
	str_802EF430, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF440, "a", "a", "a", "a",
	str_802EF450, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF460, "a", "a", "a", str_802EF470,
	str_802EF480, str_802EF490, "a", "a",
};

const char* _rule_msg_table_after[] = {
	"a", str_802EF4A0, "a", str_802EF4B0, "a", str_802EF4C0, str_802EF4D0, "a",
	"a", "a", "a", str_802EF4E0, "a", "a", "a", "a",
	"a", "a", str_802EF4F0, "a", str_802EF500, "a", "a", "a",
	"a", "a", str_802EF510, "a", "a", "a", "a", "a",
	str_802EF520, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF530, "a", "a", "a", "a",
	str_802EF540, "a", "a", "a", "a", "a", "a", "a",
	"a", "a", "a", str_802EF550, "a", "a", "a", str_802EF560,
	str_802EF570, str_802EF580, "a", "a",
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

#ifdef NONMATCHING
void BattleCheckAllPinchStatus(BattleWork* wp, BOOL a2) { //1:1, needs stmw forced
	BattleUnit* unit;
	BOOL v6;
	int i;

	for (i = 0; i < 64; i++) {
		unit = BattleGetUnitPtr(wp, i);
		if (unit) {
			BtlUnit_CheckPinchStatus(unit, a2);
		}
	}

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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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


//==== written below (reverse order) ====

#ifdef NONMATCHING  // restored C definition (nmrepair)
const s32 N_weapon_lucky_start[48] = {
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x64000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x01004020, 0x10000000, 0x00000302, 0x00000000, 0x00020108, 0x000007FF, 0x80002004,
	0x00000000, 0x00000000, 0x00000064, 0x03640300, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
	0x00000000, 0x00000000, 0x00000302, 0x03020000, 0x00000000, 0x00000064, 0x00000000, 0x00000000,
};
#endif
#ifdef NONMATCHING
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


#ifdef NONMATCHING
void _rule_disp(CameraId cameraId, void* param) {
	FieldBattleInfo* info = _battleWorkPointer->fbatInfo;
	char buf[256];
	f32 x;
	f32 y;
	u16 lines;
	u16 width;

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


#ifdef NONMATCHING
BOOL BattlePhaseEndCheck(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleUnit* unit;
	int i;

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

#ifdef NONMATCHING
void btlseqAct(BattleWork* wp) {
	BattleUnit* unit;
	EventEntry* evt;
	BOOL cantMove;
	BOOL decrement;

	switch (BattleGetSeq(wp, SEQ_ACT)) {
		case 0x6000000: {
			BattleUnit* unit;
			BOOL cantMove;

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


#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
void battleMakePhaseEvtTable(BattleWork* wp) {
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
	}
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#pragma dont_inline on
#ifdef NONMATCHING
USER_FUNC(_set_haikei_entry_scale) {
	BattleWork* wp = _battleWorkPointer;
	BOOL busy = FALSE;
	f32 sx, sy;
	BattleStageObject* obj;
	int i;

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
			}
		}
	}
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
	}
	return busy ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap): BattleSequenceManager (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const u32 N_weapon_lucky_start[48] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x64000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01004020, 0x10000000, 0x00000302, 0x00000000, 0x00020108, 0x000007FF, 0x80002004, 0x00000000, 0x00000000, 0x00000064, 0x03640300, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000302, 0x03020000, 0x00000000, 0x00000064, 0x00000000, 0x00000000 };
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
__declspec(section ".rodata") const f64 double_to_int_802ef590 = 4503601774854144;
__declspec(section ".rodata") const char str_802EF598[] = "SFX_REST_CONDITION1";
__declspec(section ".rodata") const char str_802EF5AC[] = "SFX_CONDITION_BREAK_ICE1\000\000\000";
__declspec(section ".rodata") const char str_802EF5C8[] = "SFX_SYSTEM_LUCKY1\000\000";
__declspec(section ".rodata") const char str_802EF5DC[] = "SFX_OFF_BTL_START_CURTAIN_UP1\000\000";
__declspec(section ".rodata") const char str_802EF5FC[] = "p_b_st\000";
__declspec(section ".rodata") const char str_802EF604[] = "p_jyabara\000\000";
__declspec(section ".rodata") const char str_802EF610[] = "p_kaiten_h\000";
__declspec(section ".rodata") const char str_802EF61C[] = "SFX_BTL_DANGER1";
__declspec(section ".rodata") const char str_802EF62C[] = "SFX_BTL_PINCH1\000";
__declspec(section ".rodata") const u32 gap_04_802EF63C_rodata[1] = { 0x00000000 };
#pragma force_active reset
__declspec(section ".sdata2") const char str_8041C27C[4] = "A1\0";
__declspec(section ".sdata2") const f32 float_0_8041c280 = 0.0f;
__declspec(section ".sdata2") const f32 float_1_8041c284 = 1.0f;
__declspec(section ".sdata2") const char str_8041C288[4] = "A2\0";
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

void BSE_TurnFirstProcessEffectEntry(struct BattleUnit* unit, s16 active);
BOOL BSE_TurnFirstProcessEffectMain(struct BattleUnit* unit);
void BattleAudience_ActInit(void);
BOOL BattleAudience_CheckReaction(void);
BOOL BattleAudience_CheckReactionPerPhase(void);
void BattleAudience_PerAct(void);
void BattleAudience_PerPhase(u32 value);
BOOL BattleCheckEndUnitInitEvent(BattleWork* wp);
BattleUnit* BattleGetPartyPtr(BattleWork* wp);
s32 BattleGetSeq(BattleWork* wp, BattleSequence seq);
BattleUnit* BattleGetSystemPtr(BattleWork* work);
BattleUnit* BattleGetUnitPtr(BattleWork* wp, s32 index);
void BattleIncSeq(BattleWork* wp, BattleSequence seq);
BOOL BattlePadCheckTrigger(s32 mask);
s32 BattleRunPhaseEvent(BattleUnit* unit, BOOL isUnison);
void BattleSetSeq(BattleWork* wp, BattleSequence seq, u32 value);
void BtlUnit_CheckPinchStatus(BattleUnit* unit, BOOL a2);
BOOL BtlUnit_CheckRecoveryStatus(BattleUnit* unit, StatusEffectType type);
BOOL BtlUnit_CheckStatus(BattleUnit* unit, StatusEffectType type);
s32 BtlUnit_CheckStatusFlag(BattleUnit* unit, s32 flags);
s8 BtlUnit_GetBelong(BattleUnit* unit);
s32 BtlUnit_GetBodyPartsId(BattleUnit* unit);
void* BtlUnit_GetData(BattleUnit* unit, s32 tag);
s32 BtlUnit_GetHeight(BattleUnit* unit);
void BtlUnit_GetHomePos(BattleUnit* unit, f32* x, f32* y, f32* z);
BattleUnitPart* BtlUnit_GetPartsPtr(BattleUnit* unit, s32 partNum);
void BtlUnit_GetPartsWorldPos(BattleUnitPart* part, f32* x, f32* y, f32* z);
void BtlUnit_GetPos(BattleUnit* unit, f32* x, f32* y, f32* z);
void BtlUnit_GetStatus(BattleUnit* unit, StatusEffectType type, s8* turns, s8* strength);
void BtlUnit_OffStatusFlag(BattleUnit* unit, s32 flags);
void BtlUnit_RecoverFp(BattleUnit* unit, s32 value);
void BtlUnit_RecoverHp(BattleUnit* unit, s32 value);
void BtlUnit_ResetMoveStatus(BattleUnit* unit);
BOOL BtlUnit_SetStatus(BattleUnit* unit, StatusEffectType type, s8 turns, s8 strength);
BOOL Btl_UnitSetup(BattleWork* work);
void FontDrawMessage(s32 x, s32 y, const char* msg);
void FontDrawStart(void);
u16 FontGetMessageWidthLine(const char* msg, u16* lines);
BOOL animEffectAsync(const char* animName, u32 group);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
BOOL effNiceAsync(s32 group);
EffectEntry* effNiceEntry(s32 type, f32 x, f32 y, f32 z);
BOOL evtCheckID(s32 eventId);
void evtDeleteID(s32 eventId);
EventEntry* evtEntry(void* evtCode, u8 priority, u8 flags);
s32 evtGetValue(EventEntry* entry, s32 index);
void fadeEntry(s32 type, s32 duration, GXColor color);
s32 irand(s32 scalar);
MapObject* mapGetMapObj(const char* name);
s32 marioGetPartyId(void);
MarioWork* marioGetPtr(void);
void *memset(void *dest, int ch, size_t count);
const char* msgSearch(const char* tag);
PartyEntry* partyGetPtr(s32 index);
PouchData* pouchGetPtr(void);
void psndSFXOff(s32 id);
void psndSFXOn(const char* name);
s32 psndSFXOn_3D(const char* name, Vec* position);
int sprintf(char *s, const char *format, ...);
void windowDispGX_Waku_col(u16 gxTexMapID, GXColor color, f32 x, f32 y, f32 width, f32 height, f32 curve);
asm s32 _set_haikei_entry_scale(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x40(r1)
	psq_st f31, 0x48(r1), 0, 0
	stfd f30, 0x30(r1)
	psq_st f30, 0x38(r1), 0, 0
	stfd f29, 0x20(r1)
	psq_st f29, 0x28(r1), 0, 0
	stmw r26, 0x8(r1)
	cmpwi r4, 0x0
	lwz r31, _battleWorkPointer(r13)
	mr r29, r3
	li r30, 0x0
	beq L_g5_1
	li r3, 0x3c
	li r0, 0x0
	stw r3, 0x78(r29)
	la r3, str_8041C27C(r2)
	stw r0, 0x7c(r29)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq L_g5_2
	lfs f1, float_0_8041c280(r2)
	la r3, str_8041C27C(r2)
	lfs f3, float_1_8041c284(r2)
	fmr f2, f1
	bl mapObjScale
	L_g5_2:
	la r3, str_8041C288(r2)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq L_g5_1
	lfs f1, float_0_8041c280(r2)
	la r3, str_8041C288(r2)
	lfs f3, float_1_8041c284(r2)
	fmr f2, f1
	bl mapObjScale
	L_g5_1:
	lwz r3, 0x78(r29)
	cmpwi r3, 0x0
	ble L_g5_3
	subi r0, r3, 0x1
	stw r0, 0x78(r29)
	lwz r0, 0x78(r29)
	cmpwi r0, 0x0
	ble L_g5_3
	la r3, str_8041C27C(r2)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq L_g5_4
	lfs f1, float_0_8041c280(r2)
	la r3, str_8041C27C(r2)
	lfs f3, float_1_8041c284(r2)
	fmr f2, f1
	bl mapObjScale
	li r3, 0x0
	bl _mapobj_data_touch_scale
	L_g5_4:
	la r3, str_8041C288(r2)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq L_g5_5
	lfs f1, float_0_8041c280(r2)
	la r3, str_8041C288(r2)
	lfs f3, float_1_8041c284(r2)
	fmr f2, f1
	bl mapObjScale
	li r3, 0x1
	bl _mapobj_data_touch_scale
	L_g5_5:
	li r3, 0x0
	b L_g5_6
	L_g5_3:
	lwz r4, 0x7c(r29)
	la r3, str_8041C27C(r2)
	addi r0, r4, 0x1
	stw r0, 0x7c(r29)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq L_g5_7
	lwz r0, 0x7c(r29)
	cmpwi r0, 0x28
	blt L_g5_8
	lfs f1, float_1_8041c284(r2)
	la r3, str_8041C27C(r2)
	fmr f2, f1
	fmr f3, f1
	bl mapObjScale
	li r3, 0x0
	bl _mapobj_data_touch_scale
	b L_g5_7
	L_g5_8:
	cmpwi r0, 0xf
	li r30, 0x1
	bge L_g5_9
	lfs f1, float_0_8041c280(r2)
	la r3, str_8041C27C(r2)
	lfs f3, float_1_8041c284(r2)
	fmr f2, f1
	bl mapObjScale
	li r3, 0x0
	bl _mapobj_data_touch_scale
	b L_g5_7
	L_g5_9:
	lfs f1, float_1_8041c284(r2)
	la r3, str_8041C27C(r2)
	fmr f2, f1
	fmr f3, f1
	bl mapObjScale
	li r3, 0x0
	bl _mapobj_data_touch_scale
	lwz r3, 0x7c(r29)
	cmpwi r3, 0x19
	bge L_g5_10
	lfs f1, float_0_8041c280(r2)
	subi r4, r3, 0xf
	lfs f2, float_110_8041c28c(r2)
	li r3, 0x5
	li r5, 0xa
	bl intpl_sub
	fmr f29, f1
	b L_g5_11
	L_g5_10:
	cmpwi r3, 0x23
	bge L_g5_12
	lfs f1, float_110_8041c28c(r2)
	subi r4, r3, 0x19
	lfs f2, float_90_8041c290(r2)
	li r3, 0xb
	li r5, 0xa
	bl intpl_sub
	fmr f29, f1
	b L_g5_11
	L_g5_12:
	cmpwi r3, 0x28
	bge L_g5_11
	lfs f1, float_90_8041c290(r2)
	subi r4, r3, 0x23
	lfs f2, float_100_8041c294(r2)
	li r3, 0xb
	li r5, 0x5
	bl intpl_sub
	fmr f29, f1
	L_g5_11:
	lwz r3, 0x7c(r29)
	cmpwi r3, 0x19
	bge L_g5_13
	lfs f1, float_100_8041c294(r2)
	subi r4, r3, 0xf
	lfs f2, float_90_8041c290(r2)
	li r3, 0x5
	li r5, 0xa
	bl intpl_sub
	fmr f30, f1
	b L_g5_14
	L_g5_13:
	cmpwi r3, 0x23
	bge L_g5_15
	lfs f1, float_90_8041c290(r2)
	subi r4, r3, 0x19
	lfs f2, float_110_8041c28c(r2)
	li r3, 0xb
	li r5, 0xa
	bl intpl_sub
	fmr f30, f1
	b L_g5_14
	L_g5_15:
	cmpwi r3, 0x28
	bge L_g5_14
	lfs f1, float_110_8041c28c(r2)
	subi r4, r3, 0x23
	lfs f2, float_100_8041c294(r2)
	li r3, 0xb
	li r5, 0x5
	bl intpl_sub
	fmr f30, f1
	L_g5_14:
	lfs f31, float_100_8041c294(r2)
	li r26, 0x0
	li r28, 0x0
	L_g5_16:
	addis r27, r28, 0x1
	addi r27, r27, 0x7140
	add r27, r31, r27
	lwz r0, 0x0(r27)
	cmpwi r0, 0x0
	ble L_g5_17
	lwz r3, 0x64(r27)
	lhz r0, 0x6(r3)
	cmplwi r0, 0x0
	bne L_g5_17
	fdivs f1, f30, f31
	lwz r3, 0x0(r3)
	lfs f3, float_1_8041c284(r2)
	fdivs f2, f29, f31
	bl mapObjScale
	lwz r0, 0x68(r27)
	ori r0, r0, 0x2
	stw r0, 0x68(r27)
	L_g5_17:
	addi r26, r26, 0x1
	addi r28, r28, 0x7c
	cmpwi r26, 0x20
	blt L_g5_16
	L_g5_7:
	la r3, str_8041C288(r2)
	bl mapGetMapObj
	cmplwi r3, 0x0
	beq L_g5_18
	lwz r0, 0x7c(r29)
	cmpwi r0, 0x2d
	blt L_g5_19
	lfs f1, float_1_8041c284(r2)
	la r3, str_8041C288(r2)
	fmr f2, f1
	fmr f3, f1
	bl mapObjScale
	li r3, 0x1
	bl _mapobj_data_touch_scale
	b L_g5_18
	L_g5_19:
	cmpwi r0, 0x14
	li r30, 0x1
	bge L_g5_20
	lfs f1, float_0_8041c280(r2)
	la r3, str_8041C288(r2)
	lfs f3, float_1_8041c284(r2)
	fmr f2, f1
	bl mapObjScale
	li r3, 0x1
	bl _mapobj_data_touch_scale
	b L_g5_18
	L_g5_20:
	lfs f1, float_1_8041c284(r2)
	la r3, str_8041C288(r2)
	fmr f2, f1
	fmr f3, f1
	bl mapObjScale
	li r3, 0x1
	bl _mapobj_data_touch_scale
	lwz r3, 0x7c(r29)
	cmpwi r3, 0x1e
	bge L_g5_21
	lfs f1, float_0_8041c280(r2)
	subi r4, r3, 0x14
	lfs f2, float_110_8041c28c(r2)
	li r3, 0x5
	li r5, 0xa
	bl intpl_sub
	fmr f29, f1
	b L_g5_22
	L_g5_21:
	cmpwi r3, 0x28
	bge L_g5_23
	lfs f1, float_110_8041c28c(r2)
	subi r4, r3, 0x1e
	lfs f2, float_90_8041c290(r2)
	li r3, 0xb
	li r5, 0xa
	bl intpl_sub
	fmr f29, f1
	b L_g5_22
	L_g5_23:
	cmpwi r3, 0x2d
	bge L_g5_22
	lfs f1, float_90_8041c290(r2)
	subi r4, r3, 0x28
	lfs f2, float_100_8041c294(r2)
	li r3, 0xb
	li r5, 0x5
	bl intpl_sub
	fmr f29, f1
	L_g5_22:
	lwz r3, 0x7c(r29)
	cmpwi r3, 0x1e
	bge L_g5_24
	lfs f1, float_100_8041c294(r2)
	subi r4, r3, 0x14
	lfs f2, float_90_8041c290(r2)
	li r3, 0x5
	li r5, 0xa
	bl intpl_sub
	fmr f30, f1
	b L_g5_25
	L_g5_24:
	cmpwi r3, 0x28
	bge L_g5_26
	lfs f1, float_90_8041c290(r2)
	subi r4, r3, 0x1e
	lfs f2, float_110_8041c28c(r2)
	li r3, 0xb
	li r5, 0xa
	bl intpl_sub
	fmr f30, f1
	b L_g5_25
	L_g5_26:
	cmpwi r3, 0x2d
	bge L_g5_25
	lfs f1, float_110_8041c28c(r2)
	subi r4, r3, 0x28
	lfs f2, float_100_8041c294(r2)
	li r3, 0xb
	li r5, 0x5
	bl intpl_sub
	fmr f30, f1
	L_g5_25:
	lfs f31, float_100_8041c294(r2)
	li r28, 0x0
	li r29, 0x0
	L_g5_27:
	addis r27, r29, 0x1
	addi r27, r27, 0x7140
	add r27, r31, r27
	lwz r0, 0x0(r27)
	cmpwi r0, 0x0
	ble L_g5_28
	lwz r3, 0x64(r27)
	lhz r0, 0x6(r3)
	cmplwi r0, 0x1
	bne L_g5_28
	fdivs f1, f30, f31
	lwz r3, 0x0(r3)
	lfs f3, float_1_8041c284(r2)
	fdivs f2, f29, f31
	bl mapObjScale
	lwz r0, 0x68(r27)
	ori r0, r0, 0x2
	stw r0, 0x68(r27)
	L_g5_28:
	addi r28, r28, 0x1
	addi r29, r29, 0x7c
	cmpwi r28, 0x20
	blt L_g5_27
	L_g5_18:
	subfic r3, r30, 0x0
	li r0, 0x2
	subfe r3, r3, r3
	andc r3, r0, r3
	L_g5_6:
	psq_l f31, 0x48(r1), 0, 0
	lfd f31, 0x40(r1)
	psq_l f30, 0x38(r1), 0, 0
	lfd f30, 0x30(r1)
	psq_l f29, 0x28(r1), 0, 0
	lfd f29, 0x20(r1)
	lmw r26, 0x8(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

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
void btlseqTurn(BattleWork* wp);
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
void btlseqFirstAct(BattleWork* wp);
__declspec(section ".data") static void* jumptable_80361500[] = {
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
asm void _mapobj_data_touch_scale(s32 layer) {
	nofralloc
	li r0, 0x20
	lwz r6, _battleWorkPointer(r13)
	li r4, 0x0
	mtctr r0
	L_g5_1:
	addis r7, r4, 0x1
	addi r7, r7, 0x7140
	add r7, r6, r7
	lwz r0, 0x0(r7)
	cmpwi r0, 0x0
	ble L_g5_2
	lwz r5, 0x64(r7)
	lhz r0, 0x6(r5)
	cmpw r0, r3
	bne L_g5_2
	lwz r0, 0x68(r7)
	ori r0, r0, 0x2
	stw r0, 0x68(r7)
	L_g5_2:
	addi r4, r4, 0x7c
	bdnz L_g5_1
	blr
}

asm BOOL BattleCheckConcluded(BattleWork* wp) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r28, r3
	li r30, 0x0
	li r29, 0x0
	li r27, 0x0
	L_g5_1:
	add r31, r28, r27
	li r0, 0x0
	stw r0, 0xc(r31)
	lhz r0, 0x8(r31)
	cmplwi r0, 0x0
	bne L_g5_2
	li r0, 0x1
	addi r30, r30, 0x1
	stw r0, 0xc(r31)
	b L_g5_3
	L_g5_2:
	clrlwi. r0, r0, 31
	beq L_g5_4
	li r25, 0x0
	L_g5_5:
	mr r3, r28
	mr r4, r25
	bl BattleGetUnitPtr
	mr. r26, r3
	beq L_g5_6
	lbz r0, 0xc(r26)
	extsb r0, r0
	cmpw r0, r29
	bne L_g5_6
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_6
	lwz r3, 0x104(r26)
	rlwinm. r0, r3, 0, 14, 14
	bne L_g5_6
	rlwinm. r0, r3, 0, 3, 3
	beq L_g5_7
	L_g5_6:
	addi r25, r25, 0x1
	cmpwi r25, 0x40
	blt L_g5_5
	L_g5_7:
	cmpwi r25, 0x40
	blt L_g5_4
	li r0, 0x1
	addi r30, r30, 0x1
	stw r0, 0xc(r31)
	b L_g5_3
	L_g5_4:
	lhz r0, 0x8(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq L_g5_3
	li r25, 0x0
	L_g5_8:
	mr r3, r28
	mr r4, r25
	bl BattleGetUnitPtr
	mr. r26, r3
	beq L_g5_9
	lbz r0, 0xc(r26)
	extsb r0, r0
	cmpw r0, r29
	bne L_g5_9
	lwz r0, 0x104(r26)
	rlwinm. r0, r0, 0, 13, 13
	beq L_g5_9
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_9
	lwz r0, 0x104(r26)
	rlwinm. r0, r0, 0, 3, 3
	beq L_g5_10
	L_g5_9:
	addi r25, r25, 0x1
	cmpwi r25, 0x40
	blt L_g5_8
	L_g5_10:
	cmpwi r25, 0x40
	blt L_g5_3
	li r0, 0x1
	addi r30, r30, 0x1
	stw r0, 0xc(r31)
	L_g5_3:
	addi r29, r29, 0x1
	addi r27, r27, 0x8
	cmpwi r29, 0x3
	blt L_g5_1
	cmpwi r30, 0x2
	blt L_g5_11
	li r3, 0x1
	b L_g5_12
	L_g5_11:
	lwz r0, 0xef4(r28)
	rlwinm r3, r0, 0, 26, 27
	subic r0, r3, 0x1
	subfe r3, r0, r3
	L_g5_12:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm BOOL BattleWaitAllActiveEvtEnd_NoBgSetEndWait(BattleWork* wp) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r28, 0x10(r1)
	li r29, 0x1
	mr r30, r3
	li r28, 0x0
	L_g5_1:
	mr r3, r30
	mr r4, r28
	bl BattleGetUnitPtr
	mr. r31, r3
	beq L_g5_2
	b L_g5_3
	L_g5_4:
	bl evtCheckID
	cmpwi r3, 0x0
	beq L_g5_5
	li r29, 0x0
	b L_g5_6
	L_g5_5:
	li r0, 0x0
	stw r0, 0x298(r31)
	b L_g5_6
	L_g5_3:
	lwz r3, 0x298(r31)
	cmpwi r3, 0x0
	bne L_g5_4
	b L_g5_6
	L_g5_7:
	bl evtCheckID
	cmpwi r3, 0x0
	beq L_g5_8
	li r29, 0x0
	b L_g5_9
	L_g5_8:
	li r0, 0x0
	stw r0, 0x2a4(r31)
	b L_g5_9
	L_g5_6:
	lwz r3, 0x2a4(r31)
	cmpwi r3, 0x0
	bne L_g5_7
	b L_g5_9
	L_g5_10:
	bl evtCheckID
	cmpwi r3, 0x0
	beq L_g5_11
	li r29, 0x0
	b L_g5_12
	L_g5_11:
	li r0, 0x0
	stw r0, 0x2b0(r31)
	b L_g5_12
	L_g5_9:
	lwz r3, 0x2b0(r31)
	cmpwi r3, 0x0
	bne L_g5_10
	b L_g5_12
	L_g5_13:
	bl evtCheckID
	cmpwi r3, 0x0
	beq L_g5_14
	li r29, 0x0
	b L_g5_2
	L_g5_14:
	li r0, 0x0
	stw r0, 0x2b8(r31)
	b L_g5_2
	L_g5_12:
	lwz r3, 0x2b8(r31)
	cmpwi r3, 0x0
	bne L_g5_13
	L_g5_2:
	addi r28, r28, 0x1
	cmpwi r28, 0x40
	blt L_g5_1
	cmpwi r29, 0x0
	bne L_g5_15
	mr r3, r29
	b L_g5_16
	L_g5_15:
	bl BattleAfterReactionMain
	cmpwi r3, 0x0
	beq L_g5_17
	li r29, 0x0
	L_g5_17:
	mr r3, r29
	L_g5_16:
	lmw r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm BOOL BattleWaitAllActiveEvtEnd(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	addis r31, r3, 0x2
	bl BattleWaitAllActiveEvtEnd_NoBgSetEndWait
	cmpwi r3, 0x0
	bne L_g5_1
	b L_g5_2
	L_g5_1:
	lwz r3, -0x7d68(r31)
	cmpwi r3, 0x0
	beq L_g5_3
	bl evtCheckID
	cmpwi r3, 0x0
	beq L_g5_4
	li r3, 0x0
	b L_g5_2
	L_g5_4:
	li r0, 0x0
	stw r0, -0x7d68(r31)
	L_g5_3:
	lwz r3, -0x7d58(r31)
	cmpwi r3, 0x0
	beq L_g5_5
	bl evtCheckID
	cmpwi r3, 0x0
	beq L_g5_6
	li r3, 0x0
	b L_g5_2
	L_g5_6:
	li r0, 0x0
	stw r0, -0x7d58(r31)
	L_g5_5:
	lwz r3, -0x7f20(r31)
	cmpwi r3, 0x0
	beq L_g5_7
	bl evtCheckID
	cmpwi r3, 0x0
	beq L_g5_8
	li r3, 0x0
	b L_g5_2
	L_g5_8:
	li r0, 0x0
	stw r0, -0x7f20(r31)
	L_g5_7:
	lwz r3, -0x7d54(r31)
	cmpwi r3, 0x0
	beq L_g5_9
	bl evtCheckID
	cmpwi r3, 0x0
	beq L_g5_10
	li r3, 0x0
	b L_g5_2
	L_g5_10:
	li r0, 0x0
	stw r0, -0x7d54(r31)
	L_g5_9:
	lwz r3, -0x7d5c(r31)
	cmpwi r3, 0x0
	beq L_g5_11
	bl evtCheckID
	cmpwi r3, 0x0
	beq L_g5_12
	li r3, 0x0
	b L_g5_2
	L_g5_12:
	li r0, 0x0
	stw r0, -0x7d5c(r31)
	L_g5_11:
	li r3, 0x1
	L_g5_2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void battleMakePhaseEvtTable(BattleWork* wp) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	li r5, -0x1
	stw r0, 0x44(r1)
	li r0, 0x40
	stmw r26, 0x28(r1)
	mr r26, r3
	li r3, 0x0
	mr r4, r3
	addi r31, r26, 0x220
	mtctr r0
	L_g5_1:
	add r6, r31, r3
	addi r3, r3, 0x8
	stw r5, 0x0(r6)
	stw r4, 0x4(r6)
	bdnz L_g5_1
	li r30, 0x0
	li r29, 0x0
	li r27, 0x0
	L_g5_2:
	mr r3, r26
	mr r4, r27
	bl BattleGetUnitPtr
	cmplwi r3, 0x0
	beq L_g5_3
	lwz r0, 0x104(r3)
	rlwinm. r0, r0, 0, 12, 12
	bne L_g5_3
	add r28, r31, r29
	addi r4, r1, 0x10
	stw r27, 0x0(r28)
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	bl BtlUnit_GetHomePos
	lfs f1, 0x10(r1)
	lfs f0, float_0_8041c280(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne L_g5_4
	lfs f0, float_1000_8041c298(r2)
	fadds f0, f0, f1
	fctiwz f0, f0
	stfd f0, 0x20(r1)
	lwz r0, 0x24(r1)
	stw r0, 0x4(r28)
	b L_g5_5
	L_g5_4:
	fabs f0, f1
	fctiwz f0, f0
	stfd f0, 0x20(r1)
	lwz r0, 0x24(r1)
	stw r0, 0x4(r28)
	L_g5_5:
	addi r30, r30, 0x1
	addi r29, r29, 0x8
	L_g5_3:
	addi r27, r27, 0x1
	cmpwi r27, 0x40
	blt L_g5_2
	subi r0, r30, 0x1
	li r9, 0x0
	b L_g5_6
	L_g5_7:
	subf r3, r9, r30
	subic. r4, r3, 0x1
	li r3, 0x0
	mtctr r4
	ble L_g5_8
	L_g5_9:
	add r8, r31, r3
	lwz r7, 0x4(r8)
	lwz r6, 0xc(r8)
	cmpw r7, r6
	ble L_g5_10
	lwz r5, 0x0(r8)
	lwz r4, 0x8(r8)
	stw r5, 0x14(r1)
	stw r4, 0x0(r8)
	stw r6, 0x4(r8)
	stw r5, 0x8(r8)
	stw r7, 0x18(r1)
	stw r7, 0xc(r8)
	L_g5_10:
	addi r3, r3, 0x8
	bdnz L_g5_9
	L_g5_8:
	addi r9, r9, 0x1
	L_g5_6:
	cmpw r9, r0
	blt L_g5_7
	lmw r26, 0x28(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void battleSortPhaseMoveTable(BattleWork* wp, s32 count) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stmw r23, 0x2c(r1)
	mr. r30, r4
	mr r31, r3
	bgt L_g5_1
	li r0, 0x40
	li r30, 0x0
	li r3, 0x0
	mtctr r0
	L_g5_2:
	addi r0, r3, 0x120
	lwzx r0, r31, r0
	cmpwi r0, -0x1
	beq L_g5_1
	addi r30, r30, 0x1
	addi r3, r3, 0x4
	bdnz L_g5_2
	L_g5_1:
	subi r27, r30, 0x1
	li r24, 0x0
	b L_g5_3
	L_g5_4:
	subf r3, r24, r30
	li r23, 0x0
	subi r28, r3, 0x1
	li r29, 0x0
	b L_g5_5
	L_g5_6:
	add r26, r31, r29
	mr r3, r31
	lwz r4, 0x120(r26)
	bl BattleGetUnitPtr
	lwz r4, 0x124(r26)
	mr r25, r3
	mr r3, r31
	bl BattleGetUnitPtr
	mr r0, r3
	mr r3, r25
	mr r25, r0
	addi r4, r1, 0x1c
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	bl BtlUnit_GetHomePos
	mr r3, r25
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	bl BtlUnit_GetHomePos
	lfs f1, 0x1c(r1)
	lfs f0, 0x10(r1)
	fabs f1, f1
	fabs f0, f0
	fcmpo cr0, f1, f0
	ble L_g5_7
	lwz r3, 0x120(r26)
	lwz r0, 0x124(r26)
	stw r0, 0x120(r26)
	stw r3, 0x124(r26)
	L_g5_7:
	addi r23, r23, 0x1
	addi r29, r29, 0x4
	L_g5_5:
	cmpw r23, r28
	blt L_g5_6
	addi r24, r24, 0x1
	L_g5_3:
	cmpw r24, r27
	blt L_g5_4
	subi r28, r30, 0x1
	li r24, 0x0
	b L_g5_8
	L_g5_9:
	subf r3, r24, r30
	li r23, 0x0
	subi r26, r3, 0x1
	li r29, 0x0
	b L_g5_10
	L_g5_11:
	add r25, r31, r29
	mr r3, r31
	lwz r4, 0x120(r25)
	bl BattleGetUnitPtr
	lwz r4, 0x124(r25)
	mr r27, r3
	mr r3, r31
	bl BattleGetUnitPtr
	lwz r4, 0x28(r27)
	lwz r0, 0x28(r3)
	cmpw r4, r0
	bge L_g5_12
	lwz r3, 0x120(r25)
	lwz r0, 0x124(r25)
	stw r0, 0x120(r25)
	stw r3, 0x124(r25)
	L_g5_12:
	addi r23, r23, 0x1
	addi r29, r29, 0x4
	L_g5_10:
	cmpw r23, r26
	blt L_g5_11
	addi r24, r24, 0x1
	L_g5_8:
	cmpw r24, r28
	blt L_g5_9
	lmw r23, 0x2c(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void btlseqPhaseFirstProcess(BattleWork* wp) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	li r4, 0x0
	stw r0, 0x24(r1)
	li r0, 0x40
	stmw r27, 0xc(r1)
	mr r31, r3
	stw r4, 0x1c70(r3)
	stb r4, 0x1c74(r3)
	li r3, -0x1
	mtctr r0
	L_g5_1:
	addi r0, r4, 0x120
	addi r4, r4, 0x4
	stwx r3, r31, r0
	bdnz L_g5_1
	li r27, 0x0
	li r30, 0x0
	li r28, 0x0
	L_g5_2:
	mr r3, r31
	mr r4, r28
	bl BattleGetUnitPtr
	mr. r29, r3
	beq L_g5_3
	li r0, 0xff
	stb r0, 0x30d(r29)
	lbz r0, 0x20(r29)
	cmpwi r0, 0xa
	bne L_g5_4
	li r4, 0x14
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_3
	L_g5_4:
	mr r3, r31
	li r4, 0x4
	bl BattleGetSeq
	lwz r0, 0x2c(r29)
	cmpw r0, r3
	bne L_g5_3
	lwz r0, 0x104(r29)
	rlwinm. r0, r0, 0, 12, 12
	bne L_g5_3
	lwz r5, 0x0(r29)
	addi r4, r30, 0x120
	li r3, -0x1
	li r0, 0x1
	stwx r5, r31, r4
	stw r3, 0x13c(r29)
	lwz r4, 0x14(r29)
	b L_g5_5
	L_g5_6:
	lwz r3, 0x1c0(r4)
	cmpwi r3, -0x1
	beq L_g5_7
	stb r0, 0x4e4(r4)
	L_g5_7:
	lwz r4, 0x0(r4)
	L_g5_5:
	cmplwi r4, 0x0
	bne L_g5_6
	addi r27, r27, 0x1
	addi r30, r30, 0x4
	L_g5_3:
	addi r28, r28, 0x1
	cmpwi r28, 0x40
	blt L_g5_2
	mr r3, r31
	mr r4, r27
	bl battleSortPhaseMoveTable
	mr r3, r31
	bl battleMakePhaseEvtTable
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void btlseqTurnFirstProcess(BattleWork* wp) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r28, 0x10(r1)
	mr r31, r3
	bl BtlActRec_JudgeTurnRuleKeep
	lha r3, 0x0(r31)
	addi r0, r3, 0x1
	sth r0, 0x0(r31)
	lha r0, 0x0(r31)
	cmpwi r0, 0x2
	blt L_g5_1
	bl BattleMajinaiCheck
	L_g5_1:
	addis r4, r31, 0x2
	li r0, 0x0
	stw r0, -0x7024(r4)
	addis r3, r31, 0x1
	addi r3, r3, 0x6f3b
	stw r0, -0x7028(r4)
	bl BtlActRec_AddCount
	li r29, 0x0
	L_g5_2:
	mr r3, r31
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r28, r3
	beq L_g5_3
	lbz r4, 0x24(r28)
	addi r0, r4, 0x1
	stb r0, 0x24(r28)
	bl BtlUnit_ResetMoveStatus
	lwz r30, 0x10(r28)
	lbz r3, 0x89(r30)
	extsb r3, r3
	bl irand
	lbz r0, 0x89(r30)
	lis r4, 0x100
	lbz r5, 0x88(r30)
	extsb r0, r0
	extsb r5, r5
	srawi r0, r0, 1
	add r5, r5, r3
	mr r3, r28
	addze r0, r0
	subf r0, r0, r5
	stw r0, 0x28(r28)
	bl BtlUnit_CheckStatusFlag
	cmpwi r3, 0x0
	beq L_g5_3
	mr r3, r28
	lis r4, 0x100
	bl BtlUnit_OffStatusFlag
	L_g5_3:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_2
	bl BattleFogEndCheck
	lmw r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

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

asm BOOL BattlePhaseEndCheck(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r29, 0x14(r1)
	li r29, 0x0
	li r31, 0x0
	lwz r30, _battleWorkPointer(r13)
	L_g5_1:
	addi r0, r31, 0x120
	lwzx r4, r30, r0
	cmpwi r4, -0x1
	beq L_g5_2
	mr r3, r30
	bl BattleGetUnitPtr
	cmplwi r3, 0x0
	beq L_g5_2
	lbz r0, 0x20(r3)
	cmpwi r0, 0xa
	beq L_g5_2
	lbz r0, 0x22(r3)
	extsb. r0, r0
	ble L_g5_2
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	beq L_g5_3
	L_g5_2:
	addi r29, r29, 0x1
	addi r31, r31, 0x4
	cmpwi r29, 0x40
	blt L_g5_1
	L_g5_3:
	cmpwi r29, 0x40
	blt L_g5_4
	li r3, 0x1
	b L_g5_5
	L_g5_4:
	li r3, 0x0
	L_g5_5:
	lmw r29, 0x14(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

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

asm void btlseqPhase(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x4
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	bl BattleGetSeq
	lis r4, 0x400
	addi r0, r4, 0x6
	cmpw r3, r0
	beq L_g5_1
	bge L_g5_2
	cmpw r3, r4
	beq L_g5_3
	bge L_g5_4
	b L_g5_2
	L_g5_3:
	mr r3, r31
	li r4, 0x4
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x5
	lis r5, 0x500
	bl BattleSetSeq
	b L_g5_2
	L_g5_4:
	mr r3, r31
	bl btlseqMove
	b L_g5_2
	L_g5_1:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x4
	lis r5, 0x400
	bl BattleSetSeq
	L_g5_2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _rule_disp(CameraId cameraId, void* param) {
	nofralloc
	stwu r1, -0x150(r1)
	mflr r0
	stw r0, 0x154(r1)
	stfd f31, 0x140(r1)
	psq_st f31, 0x148(r1), 0, 0
	stmw r30, 0x138(r1)
	lwz r5, _battleWorkPointer(r13)
	lis r6, lbl_80360FE0@ha
	lis r4, 0xf5de
	li r3, 0x0
	lwz r30, 0x2738(r5)
	addi r31, r6, lbl_80360FE0@l
	addi r4, r4, 0x180
	bl evtGetValue
	cmpwi r3, 0xac
	bge L_g5_1
	lis r4, 0xf5de
	li r3, 0x0
	addi r4, r4, 0x3c4
	bl evtGetValue
	cmpwi r3, 0xb
	bge L_g5_2
	lbz r0, 0x18(r30)
	addi r3, r31, 0x150
	slwi r0, r0, 2
	lwzx r3, r3, r0
	bl msgSearch
	lbz r5, 0x1a(r30)
	mr r4, r3
	addi r3, r1, 0x10
	crclr 6
	bl sprintf
	b L_g5_3
	L_g5_2:
	lbz r0, 0x18(r30)
	addi r3, r31, 0x40
	slwi r0, r0, 2
	lwzx r3, r3, r0
	bl msgSearch
	lbz r5, 0x1a(r30)
	mr r4, r3
	addi r3, r1, 0x10
	crclr 6
	bl sprintf
	b L_g5_3
	L_g5_1:
	lbz r0, 0x18(r30)
	addi r3, r31, 0x260
	slwi r0, r0, 2
	lwzx r3, r3, r0
	bl msgSearch
	lbz r5, 0x1a(r30)
	mr r4, r3
	addi r3, r1, 0x10
	crclr 6
	bl sprintf
	L_g5_3:
	addi r3, r1, 0x10
	addi r4, r1, 0x8
	bl FontGetMessageWidthLine
	lhz r4, 0x8(r1)
	extrwi r0, r3, 15, 16
	lis r6, 0x4330
	clrlwi r5, r3, 16
	addi r8, r4, 0x1
	xoris r3, r0, 0x8000
	lis r4, double_to_int_802ef590@ha
	stw r6, 0x110(r1)
	lfd f4, double_to_int_802ef590@l(r4)
	clrlwi r0, r8, 16
	stw r3, 0x114(r1)
	mulli r3, r0, 0x1d
	addi r5, r5, 0x14
	lwz r7, color(r2)
	lfd f0, 0x110(r1)
	addi r4, r1, 0xc
	addi r0, r3, 0x3
	xoris r5, r5, 0x8000
	fsubs f0, f0, f4
	lfs f1, float_0_8041c280(r2)
	xoris r0, r0, 0x8000
	stw r5, 0x11c(r1)
	li r3, 0x0
	fsubs f31, f1, f0
	stw r6, 0x118(r1)
	lfs f5, float_10_8041c2a0(r2)
	lfd f0, 0x118(r1)
	stw r0, 0x124(r1)
	fsubs f1, f31, f5
	fsubs f3, f0, f4
	lfs f2, float_94_8041c2a4(r2)
	stw r6, 0x120(r1)
	lfd f0, 0x120(r1)
	sth r8, 0x8(r1)
	fsubs f4, f0, f4
	stw r7, 0xc(r1)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	lfs f0, float_120_8041c2a8(r2)
	fctiwz f1, f31
	addi r5, r1, 0x10
	fctiwz f0, f0
	stfd f1, 0x128(r1)
	stfd f0, 0x130(r1)
	lwz r3, 0x12c(r1)
	lwz r4, 0x134(r1)
	subi r4, r4, 0x1d
	bl FontDrawMessage
	psq_l f31, 0x148(r1), 0, 0
	lfd f31, 0x140(r1)
	lmw r30, 0x138(r1)
	lwz r0, 0x154(r1)
	mtlr r0
	addi r1, r1, 0x150
	blr
}

asm void btlseqTurn(BattleWork *wp) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	li r4, 0x3
	stw r0, 0x74(r1)
	stmw r25, 0x54(r1)
	mr r31, r3
	li r30, 0x0
	li r28, 0x0
	bl BattleGetSeq
	subis r0, r3, 0x300
	cmplwi r0, 0x4d
	bgt L_g5_1
	lis r3, jumptable_803613C8@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_803613C8@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_g5_2:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	b L_g5_1
	L_g5_3:
	mr r3, r31
	bl btlseqTurnFirstProcess
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_4:
	lha r0, 0x0(r31)
	cmpwi r0, 0x1
	beq L_g5_5
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_5:
	lwz r3, 0x2738(r31)
	lbz r0, 0x18(r3)
	cmplwi r0, 0x0
	bne L_g5_6
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_6:
	li r0, 0x78
	mr r3, r31
	stw r0, 0xefc(r31)
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_7:
	lwz r3, 0xefc(r31)
	cmpwi r3, 0x0
	beq L_g5_8
	subi r0, r3, 0x1
	stw r0, 0xefc(r31)
	L_g5_8:
	lwz r0, 0xefc(r31)
	cmpwi r0, 0x0
	ble L_g5_9
	li r3, 0x300
	bl BattlePadCheckTrigger
	cmpwi r3, 0x0
	beq L_g5_10
	L_g5_9:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	b L_g5_1
	L_g5_10:
	lis r3, _rule_disp@ha
	lfs f1, float_900_8041c2ac(r2)
	addi r5, r3, _rule_disp@l
	li r4, 0x1
	li r3, 0x8
	li r6, 0x0
	bl dispEntry
	b L_g5_1
	L_g5_11:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_12:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_13:
	mr r3, r31
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_1
	mr r3, r31
	bl BattleCheckConcluded
	cmpwi r3, 0x0
	beq L_g5_14
	mr r3, r31
	li r4, 0x0
	li r5, 0x3
	bl BattleSetSeq
	mr r3, r31
	li r4, 0x7
	lis r5, 0x700
	bl BattleSetSeq
	b L_g5_1
	L_g5_14:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	b L_g5_1
	L_g5_15:
	lis r3, subsetevt_status_recovery@ha
	li r25, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_16:
	mr r3, r31
	mr r4, r25
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0x1
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_17
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_18
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_18:
	li r30, 0x1
	L_g5_17:
	addi r25, r25, 0x1
	cmpwi r25, 0x40
	blt L_g5_16
	cmpwi r28, 0x0
	beq L_g5_19
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_19:
	cmpwi r30, 0x0
	bne L_g5_20
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_20:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	b L_g5_1
	L_g5_21:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_22:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0x2
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_23
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_24
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_24:
	li r30, 0x1
	L_g5_23:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_22
	cmpwi r28, 0x0
	beq L_g5_25
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_25:
	cmpwi r30, 0x0
	bne L_g5_26
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_26:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_27:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_28:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0x3
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_29
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_30
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_30:
	li r30, 0x1
	L_g5_29:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_28
	cmpwi r28, 0x0
	beq L_g5_31
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_31:
	cmpwi r30, 0x0
	bne L_g5_32
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_32:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_33:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_34:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0x5
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_35
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_36
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_36:
	li r30, 0x1
	L_g5_35:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_34
	cmpwi r28, 0x0
	beq L_g5_37
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_37:
	cmpwi r30, 0x0
	bne L_g5_38
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_38:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_39:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_40:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0x6
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_41
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_42
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_42:
	li r30, 0x1
	L_g5_41:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_40
	cmpwi r28, 0x0
	beq L_g5_43
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_43:
	cmpwi r30, 0x0
	bne L_g5_44
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_44:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_45:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_46:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0x7
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_47
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_48
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_48:
	li r30, 0x1
	L_g5_47:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_46
	cmpwi r28, 0x0
	beq L_g5_49
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_49:
	cmpwi r30, 0x0
	bne L_g5_50
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_50:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_51:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_52:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0x8
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_53
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_54
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_54:
	li r30, 0x1
	L_g5_53:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_52
	cmpwi r28, 0x0
	beq L_g5_55
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_55:
	cmpwi r30, 0x0
	bne L_g5_56
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_56:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_57:
	lis r3, str_802EF5AC@ha
	addi r27, r1, 0x44
	addi r29, r3, str_802EF5AC@l
	addi r28, r1, 0x40
	li r26, 0x0
	L_g5_58:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	li r4, 0x9
	mr r25, r3
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	beq L_g5_59
	mr r3, r25
	bl BtlUnit_CheckShadowGuard
	cmpwi r3, 0x0
	bne L_g5_60
	mr r4, r25
	li r3, -0x5
	li r5, 0x0
	li r6, 0x1
	li r7, 0x0
	li r8, 0x11a
	li r9, 0x0
	li r10, 0x1
	bl BattleDamageDirect
	L_g5_60:
	mr r3, r25
	mr r5, r28
	mr r6, r27
	addi r4, r1, 0x3c
	bl BtlUnit_GetPos
	mr r3, r25
	bl BtlUnit_GetHeight
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x4c(r1)
	lis r4, double_to_int_802ef590@ha
	lfd f3, double_to_int_802ef590@l(r4)
	li r3, 0x0
	stw r0, 0x48(r1)
	li r4, 0x1
	lfs f0, 0x40(r1)
	lfd f2, 0x48(r1)
	lfs f1, 0x3c(r1)
	fsubs f2, f2, f3
	lfs f3, 0x44(r1)
	lfs f4, float_1_8041c284(r2)
	fadds f2, f0, f2
	stfs f2, 0x40(r1)
	bl effFreezeN64Entry
	mr r3, r29
	addi r4, r1, 0x3c
	bl psndSFXOn_3D
	li r30, 0x1
	L_g5_59:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_58
	cmpwi r30, 0x0
	bne L_g5_61
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_61:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_62:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_63:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0xa
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_64
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_65
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_65:
	li r30, 0x1
	L_g5_64:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_63
	cmpwi r28, 0x0
	beq L_g5_66
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_66:
	cmpwi r30, 0x0
	bne L_g5_67
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_67:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_68:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_69:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0xb
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_70
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_71
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_71:
	li r30, 0x1
	L_g5_70:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_69
	cmpwi r28, 0x0
	beq L_g5_72
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_72:
	cmpwi r30, 0x0
	bne L_g5_73
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_73:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_74:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_75:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0x4
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_76
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_77
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_77:
	li r30, 0x1
	L_g5_76:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_75
	cmpwi r28, 0x0
	beq L_g5_78
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_78:
	cmpwi r30, 0x0
	bne L_g5_79
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_79:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_80:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_81:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0xc
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_82
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_83
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_83:
	li r30, 0x1
	L_g5_82:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_81
	cmpwi r28, 0x0
	beq L_g5_84
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_84:
	cmpwi r30, 0x0
	bne L_g5_85
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_85:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_86:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_87:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0xd
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_88
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_89
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_89:
	li r30, 0x1
	L_g5_88:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_87
	cmpwi r28, 0x0
	beq L_g5_90
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_90:
	cmpwi r30, 0x0
	bne L_g5_91
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_91:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_92:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_93:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0xe
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_94
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_95
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_95:
	li r30, 0x1
	L_g5_94:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_93
	cmpwi r28, 0x0
	beq L_g5_96
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_96:
	cmpwi r30, 0x0
	bne L_g5_97
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_97:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_98:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_99:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0xf
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_100
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_101
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_101:
	li r30, 0x1
	L_g5_100:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_99
	cmpwi r28, 0x0
	beq L_g5_102
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_102:
	cmpwi r30, 0x0
	bne L_g5_103
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_103:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_104:
	lis r3, subsetevt_status_recovery@ha
	li r26, 0x0
	addi r27, r3, subsetevt_status_recovery@l
	L_g5_105:
	mr r3, r31
	mr r4, r26
	bl BattleGetUnitPtr
	mr r29, r3
	li r4, 0x0
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_106
	mr r3, r27
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_107
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r29)
	lwz r0, 0x0(r29)
	stw r0, 0x160(r3)
	L_g5_107:
	li r30, 0x1
	L_g5_106:
	addi r26, r26, 0x1
	cmpwi r26, 0x40
	blt L_g5_105
	cmpwi r28, 0x0
	beq L_g5_108
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_108:
	cmpwi r30, 0x0
	bne L_g5_109
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_109:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_110:
	li r29, 0x0
	L_g5_111:
	mr r3, r31
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r27, r3
	beq L_g5_112
	li r4, 0x17
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_112
	lis r3, subsetevt_status_recovery@ha
	li r4, 0xa
	addi r3, r3, subsetevt_status_recovery@l
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_113
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r27)
	lwz r0, 0x0(r27)
	stw r0, 0x160(r3)
	L_g5_113:
	li r30, 0x1
	L_g5_112:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_111
	cmpwi r28, 0x0
	beq L_g5_114
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_114:
	cmpwi r30, 0x0
	bne L_g5_115
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_115:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_116:
	li r29, 0x0
	L_g5_117:
	mr r3, r31
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r27, r3
	beq L_g5_118
	li r4, 0x18
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_118
	lis r3, subsetevt_status_recovery@ha
	li r4, 0xa
	addi r3, r3, subsetevt_status_recovery@l
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_119
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r27)
	lwz r0, 0x0(r27)
	stw r0, 0x160(r3)
	L_g5_119:
	li r30, 0x1
	L_g5_118:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_117
	cmpwi r28, 0x0
	beq L_g5_120
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_120:
	cmpwi r30, 0x0
	bne L_g5_121
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_121:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_122:
	li r29, 0x0
	L_g5_123:
	mr r3, r31
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r27, r3
	beq L_g5_124
	li r4, 0x12
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_124
	lis r3, subsetevt_status_recovery@ha
	li r4, 0xa
	addi r3, r3, subsetevt_status_recovery@l
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_125
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r27)
	lwz r0, 0x0(r27)
	stw r0, 0x160(r3)
	L_g5_125:
	li r30, 0x1
	L_g5_124:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_123
	cmpwi r28, 0x0
	beq L_g5_126
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_126:
	cmpwi r30, 0x0
	bne L_g5_127
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_127:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_128:
	li r29, 0x0
	L_g5_129:
	mr r3, r31
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r27, r3
	beq L_g5_130
	li r4, 0x13
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_130
	lis r3, subsetevt_status_recovery@ha
	li r4, 0xa
	addi r3, r3, subsetevt_status_recovery@l
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_131
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r27)
	lwz r0, 0x0(r27)
	stw r0, 0x160(r3)
	L_g5_131:
	li r30, 0x1
	L_g5_130:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_129
	cmpwi r28, 0x0
	beq L_g5_132
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_132:
	cmpwi r30, 0x0
	bne L_g5_133
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_133:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_134:
	li r27, 0x0
	L_g5_135:
	mr r3, r31
	mr r4, r27
	bl BattleGetUnitPtr
	mr. r26, r3
	beq L_g5_136
	li r4, 0x14
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_136
	mr r3, r26
	bl BtlUnit_ResetMoveStatus
	lis r3, subsetevt_status_recovery@ha
	li r4, 0xa
	addi r3, r3, subsetevt_status_recovery@l
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_137
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r26)
	lwz r0, 0x0(r26)
	stw r0, 0x160(r3)
	L_g5_137:
	li r30, 0x1
	L_g5_136:
	addi r27, r27, 0x1
	cmpwi r27, 0x40
	blt L_g5_135
	cmpwi r28, 0x0
	beq L_g5_138
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_138:
	cmpwi r30, 0x0
	bne L_g5_139
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_139:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_140:
	li r29, 0x0
	L_g5_141:
	mr r3, r31
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r27, r3
	beq L_g5_142
	li r4, 0x15
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_142
	lis r3, subsetevt_status_recovery@ha
	li r4, 0xa
	addi r3, r3, subsetevt_status_recovery@l
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_143
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r27)
	lwz r0, 0x0(r27)
	stw r0, 0x160(r3)
	L_g5_143:
	li r30, 0x1
	L_g5_142:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_141
	cmpwi r28, 0x0
	beq L_g5_144
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_144:
	cmpwi r30, 0x0
	bne L_g5_145
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_145:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_146:
	li r29, 0x0
	L_g5_147:
	mr r3, r31
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r27, r3
	beq L_g5_148
	li r4, 0x16
	bl BtlUnit_CheckRecoveryStatus
	cmpwi r3, 0x0
	or r28, r28, r3
	beq L_g5_148
	lis r3, subsetevt_status_recovery@ha
	li r4, 0xa
	addi r3, r3, subsetevt_status_recovery@l
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_149
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r27)
	lwz r0, 0x0(r27)
	stw r0, 0x160(r3)
	L_g5_149:
	li r30, 0x1
	L_g5_148:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_147
	cmpwi r28, 0x0
	beq L_g5_150
	lis r3, str_802EF598@ha
	addi r3, r3, str_802EF598@l
	bl psndSFXOn
	L_g5_150:
	cmpwi r30, 0x0
	bne L_g5_151
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_151:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_152:
	li r27, 0x0
	L_g5_153:
	mr r3, r31
	mr r4, r27
	bl BattleGetUnitPtr
	mr. r26, r3
	beq L_g5_154
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_154
	lha r0, 0x10c(r26)
	cmpwi r0, 0x0
	ble L_g5_154
	mr r3, r26
	addi r5, r1, 0x9
	addi r6, r1, 0x8
	li r4, 0x4
	bl BtlUnit_GetStatus
	lbz r0, 0x8(r1)
	extsb. r0, r0
	ble L_g5_154
	mr r3, r26
	bl BtlUnit_CheckShadowGuard
	cmpwi r3, 0x0
	bne L_g5_154
	lbz r6, 0x8(r1)
	mr r4, r26
	li r30, 0x1
	li r3, -0x5
	extsb r6, r6
	li r5, 0x0
	li r7, 0x0
	li r8, 0x117
	li r9, 0x0
	li r10, 0x1
	bl BattleDamageDirect
	L_g5_154:
	addi r27, r27, 0x1
	cmpwi r27, 0x40
	blt L_g5_153
	cmpwi r30, 0x0
	bne L_g5_155
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_155:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_156:
	li r27, 0x0
	L_g5_157:
	mr r3, r31
	mr r4, r27
	bl BattleGetUnitPtr
	mr. r26, r3
	beq L_g5_158
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_158
	lha r0, 0x10c(r26)
	cmpwi r0, 0x0
	ble L_g5_158
	mr r3, r26
	addi r5, r1, 0x9
	addi r6, r1, 0x8
	li r4, 0x8
	bl BtlUnit_GetStatus
	lbz r0, 0x8(r1)
	extsb. r0, r0
	ble L_g5_158
	li r30, 0x1
	b L_g5_159
	L_g5_158:
	addi r27, r27, 0x1
	cmpwi r27, 0x40
	blt L_g5_157
	L_g5_159:
	cmpwi r30, 0x0
	bne L_g5_160
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_160:
	li r0, 0x0
	mr r3, r31
	sth r0, 0x2(r31)
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_161:
	lhz r3, 0x2(r31)
	cmpwi r3, 0x1
	beq L_g5_162
	bge L_g5_163
	cmpwi r3, 0x0
	bge L_g5_164
	b L_g5_163
	L_g5_164:
	addi r0, r3, 0x1
	li r27, 0x0
	sth r0, 0x2(r31)
	L_g5_165:
	mr r3, r31
	mr r4, r27
	bl BattleGetUnitPtr
	mr. r26, r3
	beq L_g5_166
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_166
	lha r0, 0x10c(r26)
	cmpwi r0, 0x0
	ble L_g5_166
	mr r3, r26
	addi r5, r1, 0x9
	addi r6, r1, 0x8
	li r4, 0x8
	bl BtlUnit_GetStatus
	lbz r0, 0x8(r1)
	extsb. r0, r0
	ble L_g5_166
	mr r3, r26
	li r4, 0x1
	bl BSE_TurnFirstProcessEffectEntry
	L_g5_166:
	addi r27, r27, 0x1
	cmpwi r27, 0x40
	blt L_g5_165
	L_g5_162:
	li r25, 0x1
	li r27, 0x0
	L_g5_167:
	mr r3, r31
	mr r4, r27
	bl BattleGetUnitPtr
	cmplwi r3, 0x0
	beq L_g5_168
	bl BSE_TurnFirstProcessEffectMain
	cmpwi r3, 0x0
	beq L_g5_168
	li r25, 0x0
	L_g5_168:
	addi r27, r27, 0x1
	cmpwi r27, 0x40
	blt L_g5_167
	cmpwi r25, 0x0
	beq L_g5_1
	lhz r3, 0x2(r31)
	addi r0, r3, 0x1
	sth r0, 0x2(r31)
	b L_g5_1
	L_g5_163:
	mr r3, r31
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_1
	mr r3, r31
	bl BattleCheckConcluded
	cmpwi r3, 0x0
	beq L_g5_169
	mr r3, r31
	li r4, 0x0
	li r5, 0x3
	bl BattleSetSeq
	mr r3, r31
	li r4, 0x7
	lis r5, 0x700
	bl BattleSetSeq
	b L_g5_1
	L_g5_169:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	b L_g5_1
	L_g5_170:
	li r29, 0x0
	L_g5_171:
	mr r3, r31
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r28, r3
	beq L_g5_172
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_172
	lha r0, 0x10c(r28)
	cmpwi r0, 0x0
	ble L_g5_172
	mr r3, r28
	addi r5, r1, 0x9
	addi r6, r1, 0x8
	li r4, 0x17
	bl BtlUnit_GetStatus
	lbz r4, 0x8(r1)
	extsb. r0, r4
	ble L_g5_172
	lwz r0, 0x104(r28)
	rlwinm. r0, r0, 0, 1, 1
	bne L_g5_173
	lha r0, 0x10c(r28)
	mr r3, r28
	stw r0, 0x204(r28)
	lbz r4, 0x8(r1)
	extsb r4, r4
	bl BtlUnit_RecoverHp
	lha r0, 0x10c(r28)
	stw r0, 0x208(r28)
	lha r0, 0x1fe(r28)
	sth r0, 0x1fc(r28)
	lha r0, 0x202(r28)
	sth r0, 0x200(r28)
	lhz r0, 0x1fa(r28)
	ori r0, r0, 0x1
	sth r0, 0x1fa(r28)
	b L_g5_174
	L_g5_173:
	mr r3, r28
	extsb r4, r4
	bl BtlUnit_RecoverHp
	L_g5_174:
	mr r3, r28
	bl BtlUnit_GetBodyPartsId
	mr r4, r3
	mr r3, r28
	bl BtlUnit_GetPartsPtr
	addi r4, r1, 0x38
	addi r5, r1, 0x34
	addi r6, r1, 0x30
	bl BtlUnit_GetPartsWorldPos
	mr r3, r28
	bl BtlUnit_GetHeight
	addi r3, r3, 0x5
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802ef590@ha
	stw r3, 0x4c(r1)
	addi r5, r4, double_to_int_802ef590@l
	lbz r4, 0x8(r1)
	li r3, 0x0
	stw r0, 0x48(r1)
	lfd f1, 0x0(r5)
	extsb r4, r4
	lfd f0, 0x48(r1)
	lfs f2, 0x114(r28)
	fsubs f4, f0, f1
	lfs f0, 0x34(r1)
	lfs f1, 0x38(r1)
	lfs f3, 0x30(r1)
	fmadds f2, f2, f4, f0
	stfs f2, 0x34(r1)
	bl effRecoveryEntry
	lis r3, subsetevt_regeneration@ha
	li r4, 0xa
	addi r3, r3, subsetevt_regeneration@l
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_175
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r28)
	lwz r0, 0x0(r28)
	stw r0, 0x160(r3)
	L_g5_175:
	li r30, 0x1
	L_g5_172:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_171
	cmpwi r30, 0x0
	bne L_g5_176
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_176:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_177:
	li r27, 0x0
	L_g5_178:
	mr r3, r31
	mr r4, r27
	bl BattleGetUnitPtr
	mr. r26, r3
	beq L_g5_179
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_179
	lha r0, 0x10c(r26)
	cmpwi r0, 0x0
	ble L_g5_179
	mr r3, r26
	addi r5, r1, 0x9
	addi r6, r1, 0x8
	li r4, 0x18
	bl BtlUnit_GetStatus
	lbz r4, 0x8(r1)
	extsb. r0, r4
	ble L_g5_179
	mr r3, r26
	extsb r4, r4
	bl BtlUnit_RecoverFp
	mr r3, r26
	bl BtlUnit_GetBodyPartsId
	mr r4, r3
	mr r3, r26
	bl BtlUnit_GetPartsPtr
	addi r4, r1, 0x2c
	addi r5, r1, 0x28
	addi r6, r1, 0x24
	bl BtlUnit_GetPartsWorldPos
	mr r3, r26
	bl BtlUnit_GetHeight
	addi r3, r3, 0x5
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802ef590@ha
	stw r3, 0x4c(r1)
	addi r5, r4, double_to_int_802ef590@l
	lbz r4, 0x8(r1)
	li r3, 0x1
	stw r0, 0x48(r1)
	lfd f1, 0x0(r5)
	extsb r4, r4
	lfd f0, 0x48(r1)
	lfs f2, 0x114(r26)
	fsubs f4, f0, f1
	lfs f0, 0x28(r1)
	lfs f1, 0x2c(r1)
	lfs f3, 0x24(r1)
	fmadds f2, f2, f4, f0
	stfs f2, 0x28(r1)
	bl effRecoveryEntry
	lis r3, subsetevt_regeneration@ha
	li r4, 0xa
	addi r3, r3, subsetevt_regeneration@l
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_180
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r26)
	lwz r0, 0x0(r26)
	stw r0, 0x160(r3)
	L_g5_180:
	li r30, 0x1
	L_g5_179:
	addi r27, r27, 0x1
	cmpwi r27, 0x40
	blt L_g5_178
	cmpwi r30, 0x0
	bne L_g5_181
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_181:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_182:
	lha r0, 0x0(r31)
	cmpwi r0, 0x1
	bgt L_g5_183
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_183:
	li r29, 0x0
	L_g5_184:
	mr r3, r31
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r28, r3
	beq L_g5_185
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_185
	lha r0, 0x10c(r28)
	cmpwi r0, 0x0
	ble L_g5_185
	lbz r25, 0x2ea(r28)
	li r27, 0x0
	b L_g5_186
	L_g5_187:
	lha r4, 0x10c(r28)
	li r3, 0x64
	lha r0, 0x108(r28)
	divw r0, r4, r0
	mulli r0, r0, 0x3
	subfic r26, r0, 0x21
	bl irand
	cmpw r3, r26
	bge L_g5_188
	addi r27, r27, 0x1
	L_g5_188:
	subi r25, r25, 0x1
	L_g5_186:
	cmpwi r25, 0x0
	bgt L_g5_187
	cmpwi r27, 0x0
	ble L_g5_185
	lha r0, 0x10c(r28)
	add r0, r0, r27
	sth r0, 0x10c(r28)
	lha r0, 0x10c(r28)
	lha r3, 0x108(r28)
	cmpw r0, r3
	ble L_g5_189
	sth r3, 0x10c(r28)
	L_g5_189:
	mr r3, r28
	bl BtlUnit_GetBodyPartsId
	mr r4, r3
	mr r3, r28
	bl BtlUnit_GetPartsPtr
	addi r4, r1, 0x20
	addi r5, r1, 0x1c
	addi r6, r1, 0x18
	bl BtlUnit_GetPartsWorldPos
	mr r3, r28
	bl BtlUnit_GetHeight
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802ef590@ha
	stw r3, 0x4c(r1)
	addi r3, r4, double_to_int_802ef590@l
	lfs f2, 0x114(r28)
	stw r0, 0x48(r1)
	mr r4, r27
	lfd f3, 0x0(r3)
	li r3, 0x0
	lfd f1, 0x48(r1)
	lfs f0, 0x1c(r1)
	fsubs f4, f1, f3
	lfs f1, 0x20(r1)
	lfs f3, 0x18(r1)
	fmadds f2, f2, f4, f0
	stfs f2, 0x1c(r1)
	bl effRecoveryEntry
	lis r3, subsetevt_happy_heart@ha
	li r4, 0xa
	addi r3, r3, subsetevt_happy_heart@l
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_190
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r28)
	lwz r0, 0x0(r28)
	stw r0, 0x160(r3)
	L_g5_190:
	li r30, 0x1
	L_g5_185:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_184
	cmpwi r30, 0x0
	bne L_g5_191
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_191:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	b L_g5_1
	L_g5_192:
	lha r0, 0x0(r31)
	cmpwi r0, 0x1
	bgt L_g5_193
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_193:
	li r29, 0x0
	L_g5_194:
	mr r3, r31
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r26, r3
	beq L_g5_195
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_195
	lha r0, 0x10c(r26)
	cmpwi r0, 0x0
	ble L_g5_195
	lbz r25, 0x2eb(r26)
	li r27, 0x0
	b L_g5_196
	L_g5_197:
	lha r4, 0x112(r26)
	li r3, 0x64
	lha r0, 0x10e(r26)
	divw r0, r4, r0
	mulli r0, r0, 0x3
	subfic r28, r0, 0x21
	bl irand
	cmpw r3, r28
	bge L_g5_198
	addi r27, r27, 0x1
	L_g5_198:
	subi r25, r25, 0x1
	L_g5_196:
	cmpwi r25, 0x0
	bgt L_g5_197
	cmpwi r27, 0x0
	ble L_g5_195
	mr r3, r26
	mr r4, r27
	bl BtlUnit_RecoverFp
	mr r3, r26
	bl BtlUnit_GetBodyPartsId
	mr r4, r3
	mr r3, r26
	bl BtlUnit_GetPartsPtr
	addi r4, r1, 0x14
	addi r5, r1, 0x10
	addi r6, r1, 0xc
	bl BtlUnit_GetPartsWorldPos
	mr r3, r26
	bl BtlUnit_GetHeight
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	lis r4, double_to_int_802ef590@ha
	stw r3, 0x4c(r1)
	addi r3, r4, double_to_int_802ef590@l
	lfs f2, 0x114(r26)
	stw r0, 0x48(r1)
	mr r4, r27
	lfd f3, 0x0(r3)
	li r3, 0x1
	lfd f1, 0x48(r1)
	lfs f0, 0x10(r1)
	fsubs f4, f1, f3
	lfs f1, 0x14(r1)
	lfs f3, 0xc(r1)
	fmadds f2, f2, f4, f0
	stfs f2, 0x10(r1)
	bl effRecoveryEntry
	lis r3, subsetevt_happy_flower@ha
	li r4, 0xa
	addi r3, r3, subsetevt_happy_flower@l
	li r5, 0x0
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_199
	lwz r0, 0x15c(r3)
	stw r0, 0x2a4(r26)
	lwz r0, 0x0(r26)
	stw r0, 0x160(r3)
	L_g5_199:
	li r30, 0x1
	L_g5_195:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_194
	cmpwi r30, 0x0
	bne L_g5_200
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_200:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_201:
	addis r4, r31, 0x2
	lwz r3, -0x6fc8(r4)
	cmpwi r3, 0x0
	beq L_g5_202
	subi r0, r3, 0x1
	stw r0, -0x6fc8(r4)
	L_g5_202:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_203:
	addis r4, r31, 0x2
	lwz r3, -0x6fc4(r4)
	cmpwi r3, 0x0
	beq L_g5_204
	subi r0, r3, 0x1
	stw r0, -0x6fc4(r4)
	L_g5_204:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_205:
	addis r4, r31, 0x2
	lwz r3, -0x6fc0(r4)
	cmpwi r3, 0x0
	beq L_g5_206
	subi r0, r3, 0x1
	stw r0, -0x6fc0(r4)
	L_g5_206:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_207:
	addis r4, r31, 0x2
	lwz r3, -0x6fbc(r4)
	cmpwi r3, 0x0
	beq L_g5_208
	subi r0, r3, 0x1
	stw r0, -0x6fbc(r4)
	L_g5_208:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_209:
	addis r4, r31, 0x2
	lwz r3, -0x6fb8(r4)
	cmpwi r3, 0x0
	beq L_g5_210
	subi r0, r3, 0x1
	stw r0, -0x6fb8(r4)
	L_g5_210:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_211:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	bl btlseqTurn
	b L_g5_1
	L_g5_212:
	mr r3, r31
	li r4, 0x3
	bl BattleIncSeq
	mr r3, r31
	li r4, 0x4
	lis r5, 0x400
	bl BattleSetSeq
	b L_g5_1
	L_g5_213:
	mr r3, r31
	bl btlseqPhase
	b L_g5_1
	L_g5_214:
	bl BattleAudience_Case_TurnEnd
	lis r4, 0x300
	mr r3, r31
	addi r5, r4, 0x1
	li r4, 0x3
	bl BattleSetSeq
	lwz r0, 0xef4(r31)
	rlwinm r0, r0, 0, 19, 17
	stw r0, 0xef4(r31)
	L_g5_1:
	lmw r25, 0x54(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

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

asm void btlseqFirstAct(BattleWork* wp) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	li r4, 0x2
	stw r0, 0x34(r1)
	stmw r28, 0x20(r1)
	mr r30, r3
	lwz r5, 0x2738(r3)
	lwz r31, 0x8(r5)
	bl BattleGetSeq
	subis r0, r3, 0x200
	cmplwi r0, 0xe
	bgt L_g5_1
	lis r3, jumptable_80361500@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_80361500@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_g5_2:
	cmpwi r31, 0x0
	beq L_g5_3
	b L_g5_4
	L_g5_3:
	li r0, 0x0
	la r3, _default_haikei_set_entry_event(r13)
	stw r0, 0xefc(r30)
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r3, 0x2738(r30)
	li r29, 0x0
	lwz r31, 0xc(r3)
	L_g5_5:
	mr r3, r30
	mr r4, r29
	bl BattleGetUnitPtr
	mr. r28, r3
	beq L_g5_6
	lwz r0, 0x2b4(r28)
	cmplwi r0, 0x0
	beq L_g5_6
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 11, 11
	beq L_g5_7
	lwz r0, 0x8(r28)
	cmpwi r0, 0xde
	beq L_g5_6
	cmpwi r0, 0xe0
	blt L_g5_7
	cmpwi r0, 0xe7
	blt L_g5_6
	L_g5_7:
	bl marioGetPtr
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x1a
	bne L_g5_8
	lwz r0, 0x8(r28)
	cmpwi r0, 0xde
	bne L_g5_8
	mr r3, r28
	li r4, 0x41
	bl BtlUnit_GetData
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	stw r0, 0x2b8(r28)
	lwz r0, 0x0(r28)
	stw r0, 0x160(r3)
	b L_g5_6
	L_g5_8:
	lwz r3, 0x2b4(r28)
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	stw r0, 0x2b8(r28)
	lwz r0, 0x0(r28)
	stw r0, 0x160(r3)
	L_g5_6:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_5
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0x1
	li r4, 0x2
	bl BattleSetSeq
	b L_g5_1
	L_g5_4:
	cmpwi r31, 0x4
	bge L_g5_9
	cmpwi r31, 0x1
	bge L_g5_10
	b L_g5_11
	L_g5_9:
	cmpwi r31, 0x9
	bge L_g5_11
	b L_g5_12
	L_g5_10:
	li r0, 0xa
	stw r0, 0xefc(r30)
	b L_g5_13
	L_g5_12:
	li r0, 0x0
	stw r0, 0xefc(r30)
	b L_g5_13
	L_g5_11:
	li r0, 0x0
	stw r0, 0xefc(r30)
	L_g5_13:
	lwz r0, 0xef4(r30)
	mr r3, r30
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	ori r0, r0, 0x2
	stw r0, 0xef4(r30)
	bl BattleGetFirstAttackUnit
	lwz r3, 0x10(r1)
	li r4, 0xa
	li r5, 0x20
	lwz r0, 0x0(r3)
	stw r0, 0x420(r30)
	lwz r3, 0x10(r1)
	lwz r0, 0x278(r3)
	ori r0, r0, 0x1000
	stw r0, 0x278(r3)
	lwz r3, 0xc(r1)
	lwz r3, 0x2ac(r3)
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_14
	lwz r4, 0xc(r1)
	li r0, 0x39
	lwz r4, 0x0(r4)
	stw r4, 0x160(r3)
	lwz r4, 0xc(r1)
	stw r0, 0x274(r4)
	lwz r0, 0x15c(r3)
	lwz r3, 0xc(r1)
	stw r0, 0x2b0(r3)
	L_g5_14:
	lwz r3, 0x10(r1)
	cmpwi r31, 0x9
	lwz r0, 0x1c(r3)
	oris r0, r0, 0x400
	stw r0, 0x1c(r3)
	bge L_g5_15
	mr r3, r31
	bl _GetFirstAttackWeapon
	lwz r4, 0xb0(r3)
	li r0, 0x0
	lwz r3, 0x10(r1)
	stw r4, 0x29c(r3)
	lwz r3, 0x10(r1)
	stw r0, 0x2a8(r3)
	bl BattleStatusWindowEventOff
	L_g5_15:
	lwz r3, 0x10(r1)
	bl BtlUnit_GetBelong
	extsb. r0, r3
	bne L_g5_16
	bl BattleAudience_Case_FirstAttack_Good
	b L_g5_17
	L_g5_16:
	bl BattleAudience_Case_FirstAttack_Bad
	L_g5_17:
	lwz r3, 0x10(r1)
	li r4, 0xa
	li r5, 0x0
	lwz r3, 0x29c(r3)
	bl evtEntry
	cmplwi r3, 0x0
	beq L_g5_18
	lwz r4, 0x10(r1)
	lwz r0, 0x0(r4)
	stw r0, 0x160(r3)
	lwz r0, 0x15c(r3)
	lwz r3, 0x10(r1)
	stw r0, 0x2a4(r3)
	L_g5_18:
	cmpwi r31, 0x7
	bge L_g5_19
	cmpwi r31, 0x1
	bge L_g5_20
	b L_g5_21
	L_g5_19:
	cmpwi r31, 0x9
	bge L_g5_21
	b L_g5_22
	L_g5_20:
	mr r3, r30
	bl BattleGetPartyPtr
	mr. r31, r3
	beq L_g5_21
	lwz r3, 0x2b4(r31)
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	stw r0, 0x2b8(r31)
	lwz r0, 0x0(r31)
	stw r0, 0x160(r3)
	b L_g5_21
	L_g5_22:
	mr r3, r30
	bl BattleGetMarioPtr
	mr. r31, r3
	beq L_g5_21
	lwz r3, 0x2b4(r31)
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	stw r0, 0x2b8(r31)
	lwz r0, 0x0(r31)
	stw r0, 0x160(r3)
	L_g5_21:
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0x1
	li r4, 0x2
	bl BattleSetSeq
	b L_g5_1
	L_g5_23:
	lwz r3, 0xefc(r30)
	subic. r0, r3, 0x1
	stw r0, 0xefc(r30)
	bgt L_g5_1
	lwz r0, c(r2)
	addi r5, r1, 0x8
	li r3, 0x17
	li r4, 0xc8
	stw r0, 0x8(r1)
	bl fadeEntry
	lis r3, str_802EF5DC@ha
	addi r3, r3, str_802EF5DC@l
	bl psndSFXOn
	addis r5, r30, 0x2
	lis r4, 0x200
	stw r3, -0x6fa0(r5)
	mr r3, r30
	addi r5, r4, 0x2
	li r4, 0x2
	bl BattleSetSeq
	L_g5_24:
	bl fadeIsFinish
	cmpwi r3, 0x0
	beq L_g5_25
	addis r3, r30, 0x2
	lwz r3, -0x6fa0(r3)
	addis r0, r3, 0x1
	cmplwi r0, 0xffff
	beq L_g5_25
	bl psndSFXOff
	addis r3, r30, 0x2
	li r0, -0x1
	stw r0, -0x6fa0(r3)
	L_g5_25:
	mr r3, r30
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_26
	bl BattleStatusWindowEventOn
	L_g5_26:
	mr r3, r30
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_1
	bl fadeIsFinish
	cmpwi r3, 0x0
	beq L_g5_1
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0x3
	li r4, 0x2
	bl BattleSetSeq
	lwz r4, 0x420(r30)
	mr r3, r30
	bl BattleGetUnitPtr
	cmplwi r3, 0x0
	beq L_g5_1
	lwz r0, 0x1c(r3)
	rlwinm r0, r0, 0, 6, 4
	stw r0, 0x1c(r3)
	b L_g5_1
	L_g5_27:
	mr r3, r30
	bl BattleCheckConcluded
	cmpwi r3, 0x0
	beq L_g5_28
	bl BattleAudience_PerAct
	mr r3, r30
	li r4, 0x0
	li r5, 0x3
	bl BattleSetSeq
	mr r3, r30
	li r4, 0x7
	lis r5, 0x700
	bl BattleSetSeq
	b L_g5_1
	L_g5_28:
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0x4
	li r4, 0x2
	bl BattleSetSeq
	mr r3, r30
	bl BattleStatusChangeMsgAdjust
	L_g5_29:
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
	li r4, 0x2
	bl BattleIncSeq
	L_g5_30:
	lwz r0, 0xef4(r30)
	rlwinm. r0, r0, 0, 26, 27
	bne L_g5_31
	bl BattleStatusWindowSystemOn
	L_g5_31:
	bl BattleConsumeReserveItem
	lwz r0, 0xef4(r30)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0xef4(r30)
	bl BattleAudience_PerAct
	mr r3, r30
	li r4, 0x2
	bl BattleIncSeq
	L_g5_32:
	bl BattleAudience_CheckReaction
	clrlwi. r0, r3, 24
	bne L_g5_1
	mr r3, r30
	bl BattleCheckConcluded
	cmpwi r3, 0x0
	bne L_g5_33
	bl BattleBreakSlot_CheckReaction
	clrlwi. r0, r3, 24
	bne L_g5_1
	L_g5_33:
	mr r3, r30
	li r4, 0x2
	bl BattleIncSeq
	L_g5_34:
	mr r3, r30
	bl BattleStatusChangeMsgMain
	mr r31, r3
	mr r3, r30
	bl BattleStatusChangeAnnouceMain
	or. r0, r3, r31
	bne L_g5_1
	mr r3, r30
	li r4, 0x2
	bl BattleIncSeq
	L_g5_35:
	mr r3, r30
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_1
	lwz r3, 0x2738(r30)
	lwz r3, 0xc(r3)
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_36
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0x9
	li r4, 0x2
	bl BattleSetSeq
	bl BattleStage_WallCloseCheck
	b L_g5_1
	L_g5_36:
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0xa
	li r4, 0x2
	bl BattleSetSeq
	b L_g5_1
	L_g5_37:
	addis r28, r30, 0x2
	lwz r3, -0x7d5c(r28)
	cmpwi r3, 0x0
	beq L_g5_38
	bl evtCheckID
	cmpwi r3, 0x0
	bne L_g5_38
	li r0, 0x0
	stw r0, -0x7d5c(r28)
	L_g5_38:
	lwz r0, -0x7d5c(r28)
	cmpwi r0, 0x0
	bne L_g5_1
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0xa
	li r4, 0x2
	bl BattleSetSeq
	b L_g5_1
	L_g5_39:
	addis r3, r30, 0x2
	li r0, 0x0
	stw r0, -0x6fb4(r3)
	li r28, 0x0
	li r29, 0x0
	L_g5_40:
	mr r3, r30
	mr r4, r29
	bl BattleGetUnitPtr
	cmplwi r3, 0x0
	beq L_g5_41
	lbz r0, 0x300(r3)
	cmplwi r0, 0x0
	beq L_g5_41
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_41
	li r28, 0x1
	L_g5_41:
	addi r29, r29, 0x1
	cmpwi r29, 0x40
	blt L_g5_40
	cmpwi r28, 0x0
	beq L_g5_42
	la r3, nanika_luck_event(r13)
	li r4, 0xa
	li r5, 0x0
	bl evtEntry
	li r0, -0x5
	addis r6, r30, 0x2
	stw r0, 0x160(r3)
	li r4, -0x1
	lwz r0, 0x15c(r3)
	mr r3, r30
	stw r0, -0x6fb4(r6)
	lwz r0, -0x7024(r6)
	lwz r5, -0x7028(r6)
	or r0, r0, r4
	stw r0, -0x7024(r6)
	or r0, r5, r4
	stw r0, -0x7028(r6)
	bl BattleStatusChangeMsgAdjust
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0xb
	li r4, 0x2
	bl BattleSetSeq
	addis r3, r30, 0x2
	li r0, 0x0
	sth r0, -0x701e(r3)
	b L_g5_1
	L_g5_42:
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0xc
	li r4, 0x2
	bl BattleSetSeq
	b L_g5_1
	L_g5_43:
	addis r4, r30, 0x2
	li r28, 0x1
	lhz r3, -0x701e(r4)
	cmplwi r3, 0x12c
	bge L_g5_44
	addi r0, r3, 0x1
	sth r0, -0x701e(r4)
	L_g5_44:
	addis r3, r30, 0x2
	lwz r3, -0x6fb4(r3)
	cmpwi r3, 0x0
	beq L_g5_45
	bl evtCheckID
	cmpwi r3, 0x0
	beq L_g5_46
	li r28, 0x0
	b L_g5_45
	L_g5_46:
	addis r3, r30, 0x2
	li r0, 0x0
	stw r0, -0x6fb4(r3)
	L_g5_45:
	mr r3, r30
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	bne L_g5_47
	li r28, 0x0
	L_g5_47:
	mr r3, r30
	bl BattleStatusChangeAnnouceMain
	cmpwi r3, 0x0
	beq L_g5_48
	li r28, 0x0
	L_g5_48:
	mr r3, r30
	bl BattleStatusChangeMsgMain
	cmpwi r3, 0x0
	beq L_g5_49
	li r28, 0x0
	L_g5_49:
	cmpwi r28, 0x0
	beq L_g5_1
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0xc
	li r4, 0x2
	bl BattleSetSeq
	b L_g5_1
	L_g5_50:
	lwz r0, 0xef4(r30)
	rlwinm. r0, r0, 0, 30, 30
	beq L_g5_51
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0xe
	li r4, 0x2
	bl BattleSetSeq
	b L_g5_1
	L_g5_51:
	li r3, 0x0
	bl BattleStage_NozzleWorkCheck
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0xd
	li r4, 0x2
	bl BattleSetSeq
	L_g5_52:
	mr r3, r30
	bl BattleWaitAllActiveEvtEnd
	cmpwi r3, 0x0
	beq L_g5_1
	lis r4, 0x200
	mr r3, r30
	addi r5, r4, 0xe
	li r4, 0x2
	bl BattleSetSeq
	L_g5_53:
	lwz r0, 0xef4(r30)
	mr r3, r30
	li r4, 0x0
	li r5, 0x2
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0xef4(r30)
	bl BattleSetSeq
	mr r3, r30
	li r4, 0x3
	lis r5, 0x300
	bl BattleSetSeq
	L_g5_1:
	lmw r28, 0x20(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

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

asm void btlseqInit(BattleWork* wp) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, N_weapon_lucky_start@ha
	stw r0, 0x14(r1)
	stmw r30, 0x8(r1)
	addi r31, r4, N_weapon_lucky_start@l
	mr r30, r3
	li r4, 0x1
	bl BattleGetSeq
	lis r4, 0x100
	addi r0, r4, 0x3
	cmpw r3, r0
	beq L_g5_1
	bge L_g5_2
	addi r5, r4, 0x1
	cmpw r3, r5
	beq L_g5_3
	bge L_g5_4
	cmpw r3, r4
	bge L_g5_5
	b L_g5_6
	L_g5_2:
	addi r5, r4, 0x5
	cmpw r3, r5
	beq L_g5_7
	bge L_g5_6
	b L_g5_8
	L_g5_5:
	mr r3, r30
	li r4, 0x1
	bl BattleSetSeq
	L_g5_3:
	bl marioGetPtr
	lwz r0, 0x4(r3)
	ori r0, r0, 0x1
	stw r0, 0x4(r3)
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq L_g5_9
	lwz r0, 0x4(r3)
	ori r0, r0, 0x1
	stw r0, 0x4(r3)
	L_g5_9:
	mr r3, r30
	bl Btl_UnitSetup
	lis r4, 0x100
	mr r3, r30
	addi r5, r4, 0x2
	li r4, 0x1
	bl BattleSetSeq
	b L_g5_6
	L_g5_4:
	mr r3, r30
	bl BattleCheckEndUnitInitEvent
	cmpwi r3, 0x0
	beq L_g5_6
	lis r4, 0x100
	mr r3, r30
	addi r5, r4, 0x3
	li r4, 0x1
	bl BattleSetSeq
	b L_g5_6
	L_g5_1:
	addi r3, r31, 0x3ac
	li r4, 0x1
	bl animEffectAsync
	cmpwi r3, 0x0
	beq L_g5_6
	addi r3, r31, 0x3b4
	li r4, 0x1
	bl animEffectAsync
	cmpwi r3, 0x0
	beq L_g5_6
	addi r3, r31, 0x3c0
	li r4, 0x1
	bl animEffectAsync
	cmpwi r3, 0x0
	beq L_g5_6
	li r3, 0x1
	bl effNiceAsync
	cmpwi r3, 0x0
	beq L_g5_6
	lis r4, 0x100
	mr r3, r30
	addi r5, r4, 0x4
	li r4, 0x1
	bl BattleSetSeq
	b L_g5_6
	L_g5_8:
	mr r3, r30
	li r4, 0x1
	bl BattleSetSeq
	b L_g5_6
	L_g5_7:
	bl BattleStatusWindowEventOn
	bl BattleStatusWindowSystemOn
	mr r3, r30
	li r4, 0x0
	li r5, 0x1
	bl BattleSetSeq
	mr r3, r30
	li r4, 0x2
	lis r5, 0x200
	bl BattleSetSeq
	L_g5_6:
	lmw r30, 0x8(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void BattleCheckAllPinchStatus(BattleWork* wp, BOOL a2) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r28, 0x10(r1)
	mr r31, r3
	mr r29, r4
	li r28, 0x0
	L_g5_1:
	mr r3, r31
	mr r4, r28
	bl BattleGetUnitPtr
	cmplwi r3, 0x0
	beq L_g5_2
	mr r4, r29
	bl BtlUnit_CheckPinchStatus
	L_g5_2:
	addi r28, r28, 0x1
	cmpwi r28, 0x40
	blt L_g5_1
	li r28, 0x0
	li r30, 0x0
	L_g5_3:
	mr r3, r31
	mr r4, r30
	bl BattleGetUnitPtr
	mr. r29, r3
	beq L_g5_4
	lwz r0, 0x138(r29)
	rlwinm. r0, r0, 0, 2, 2
	beq L_g5_4
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_4
	mr r3, r29
	bl BtlUnit_GetBelong
	extsb. r0, r3
	bne L_g5_4
	lwz r0, 0x8(r29)
	cmpwi r0, 0xde
	beq L_g5_5
	cmpwi r0, 0xe0
	blt L_g5_6
	cmpwi r0, 0xe7
	bge L_g5_6
	L_g5_5:
	lha r0, 0x10c(r29)
	cmpwi r0, 0x0
	ble L_g5_6
	li r28, 0x1
	b L_g5_6
	L_g5_4:
	addi r30, r30, 0x1
	cmpwi r30, 0x40
	blt L_g5_3
	L_g5_6:
	cmpwi r28, 0x0
	beq L_g5_7
	addis r4, r31, 0x2
	lbz r3, -0x7020(r4)
	subi r0, r3, 0x1
	stb r0, -0x7020(r4)
	lbz r0, -0x7020(r4)
	extsb. r0, r0
	bgt L_g5_8
	li r0, 0x3c
	stb r0, -0x7020(r4)
	lwz r0, 0x1720(r31)
	clrlwi. r0, r0, 31
	beq L_g5_8
	lis r3, str_802EF61C@ha
	addi r3, r3, str_802EF61C@l
	bl psndSFXOn
	b L_g5_8
	L_g5_7:
	li r28, 0x0
	mr r30, r28
	L_g5_9:
	mr r3, r31
	mr r4, r30
	bl BattleGetUnitPtr
	mr. r29, r3
	beq L_g5_10
	lwz r0, 0x138(r29)
	rlwinm. r0, r0, 0, 3, 3
	beq L_g5_10
	li r4, 0x1b
	bl BtlUnit_CheckStatus
	cmpwi r3, 0x0
	bne L_g5_10
	mr r3, r29
	bl BtlUnit_GetBelong
	extsb. r0, r3
	bne L_g5_10
	lwz r0, 0x8(r29)
	cmpwi r0, 0xde
	beq L_g5_11
	cmpwi r0, 0xe0
	blt L_g5_12
	cmpwi r0, 0xe7
	bge L_g5_12
	L_g5_11:
	lha r0, 0x10c(r29)
	cmpwi r0, 0x0
	ble L_g5_12
	li r28, 0x1
	b L_g5_12
	L_g5_10:
	addi r30, r30, 0x1
	cmpwi r30, 0x40
	blt L_g5_9
	L_g5_12:
	cmpwi r28, 0x0
	beq L_g5_13
	addis r4, r31, 0x2
	lbz r3, -0x7020(r4)
	subi r0, r3, 0x1
	stb r0, -0x7020(r4)
	lbz r0, -0x7020(r4)
	extsb. r0, r0
	bgt L_g5_8
	li r0, 0x3c
	stb r0, -0x7020(r4)
	lwz r0, 0x1720(r31)
	clrlwi. r0, r0, 31
	beq L_g5_8
	lis r3, str_802EF62C@ha
	addi r3, r3, str_802EF62C@l
	bl psndSFXOn
	b L_g5_8
	L_g5_13:
	mr r3, r31
	bl BattleGetMarioPtr
	cmplwi r3, 0x0
	beq L_g5_14
	li r0, 0x0
	stw r0, 0x234(r3)
	L_g5_14:
	addis r3, r31, 0x2
	li r0, 0x0
	stb r0, -0x7020(r3)
	L_g5_8:
	lmw r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void BattleSequenceManager(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	lwz r3, _battleWorkPointer(r13)
	mr r31, r3
	bl BattleGetSeq
	cmpwi r3, 0x2
	beq L_g5_1
	bge L_g5_2
	cmpwi r3, 0x0
	beq L_g5_3
	bge L_g5_4
	b L_g5_5
	L_g5_2:
	cmpwi r3, 0x4
	beq L_g5_5
	bge L_g5_5
	b L_g5_6
	L_g5_3:
	mr r3, r31
	bl btlseqInit
	mr r3, r31
	li r4, 0x1
	bl BattleCheckAllPinchStatus
	b L_g5_5
	L_g5_4:
	mr r3, r31
	li r4, 0x0
	bl BattleCheckAllPinchStatus
	mr r3, r31
	bl btlseqFirstAct
	b L_g5_5
	L_g5_1:
	mr r3, r31
	li r4, 0x0
	bl BattleCheckAllPinchStatus
	mr r3, r31
	bl btlseqTurn
	b L_g5_5
	L_g5_6:
	mr r3, r31
	bl btlseqEnd
	L_g5_5:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata2") const u32 gap_09_8041C2BC_sdata2[1] = {0};
#pragma force_active reset
#pragma force_active reset
