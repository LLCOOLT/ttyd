#include "battle/battle_audience.h"
#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/icondrv.h"
#include "driver/windowdrv.h"
#include "data/item_data.h"
#include "driver/npcdrv.h"
#include "mario/mario_pouch.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>
#include <dolphin/gx.h>

#pragma optimize_for_size on
#pragma dont_inline on

extern BattleWork* _battleWorkPointer;
extern s32 swGet(s32);
extern int sprintf(char* str, const char* format, ...);
extern s32 weaponGetPowerFromMarioHammerLv();
extern s32 weaponGetPowerDefault();

// BattleAudienceSound with the leading fields named (header keeps field_0x0 for sac_common)
typedef struct AudSound {
    s32 flags;                     // 0x0
    s32 sfxId;                     // 0x4
    u8 kind;                       // 0x8
    u8 field_0x9[0xC - 0x9];       // 0x9
    s32 duration;                  // 0xC
    s32 mFadeoutTime;              // 0x10
    s32 mForceFadeTimer;           // 0x14
    s32 mForceFadeLength;          // 0x18
    u8 mBaseSfxVolume;             // 0x1C
    u8 mCurrentBaseSfxVolume;      // 0x1D
    u8 mVolumeMultiplier;          // 0x1E
    u8 mFadeStartVolumeMultiplier; // 0x1F
    u8 mFadeEndVolumeMultiplier;   // 0x20
    u8 field_0x21[3];              // 0x21
} AudSound;

#define AudSoundGetPtr(id) ((AudSound*)BattleAudienceSoundGetPtr(id))

#define AUD_SOUND_START(sound, dur, fade)                                           if ((sound)->sfxId != -1) {                                                         (sound)->flags |= 1;                                                            (sound)->duration = (dur);                                                      (sound)->mFadeoutTime = (fade);                                                 (sound)->mBaseSfxVolume = (sound)->mCurrentBaseSfxVolume = psndSFX_get_vol((sound)->sfxId);         (sound)->mForceFadeLength = 0;                                                  (sound)->mForceFadeTimer = 0;                                                   (sound)->mVolumeMultiplier = 100;                                           }

s32 psndSFXChk(s32 id);
void psndSFX_vol(s32 id, s32 vol);
void psndSFX_pit(s32 id, s32 pitch);
u8 psndSFX_get_vol(s32 id);
char* strcpy(char* dst, const char* src);

// local prototypes
FileEntry* tplRead(const char* path);
BOOL check_exe_phase_evt_status(s32 index, s32 type);
void BattleAudienceSettingAudience(void);
void BattleAudienceGuestTPLRead(s32 index, AudienceMemberType member, const char* tplName);
void BattleAudienceCtrlProcess(void);
BOOL BattleAudienceItemOn(s32 index, u16 itemId, s32 numItems);
void BattleAudienceSetThrowItemMax(void);
BattleUnit* BattleAudienceDetectTargetAll(void);
BattleUnit* BattleAudienceDetectTargetPlayer(void);
void BattleAudienceItemCtrlProcess(void);
void BattleAudienceApSrcCtrlProcess(void);
BOOL BattleAudienceApSrcEntry(void);
void BattleAudienceWinCtrlProcess(void);
void BattleAudienceGXInit(void);
void BattleAudienceAnimProcess(void);
void BattleAudienceDispAudience(CameraId camId, void* param);
void BattleAudienceDispItem(CameraId camId, void* param);
void BattleAudienceDispApSrc(CameraId camId, void* param);
void BattleAudienceDispWin(CameraId camId, void* param);
void BattleAudience_Entry_Sub(s32 index, s32 type, u8 status);
BOOL BattleAudience_GetAnimEnd(s32 index);
BOOL BattleAudience_GetFront(s32 index);
BOOL BattleAudience_GetEscapeChangeOK(s32 index);
s32 BattleAudience_GetAudienceNoFromOffset(s32 index, s32 column, s32 row);
s32 BattleAudience_NoUsedHaitiRand(void);
s32 BattleAudience_NoUsedFCHaitiRand(void);
s32 BattleAudience_GetPPAudienceNum(void);
s32 BattleAudience_GetPPAudienceNumKind(s32 type);
s32 BattleAudience_GetPPAudienceNum_R(void);
s32 BattleAudience_GetPPAudienceNum_L(void);
s32 BattleAudience_GetPPAudienceNum_RL_Sub(s32 offset);
BOOL BattleAudience_GetPPAudienceNum_Sub(s32 id);
void BattleAudience_ApRecoveryBuild(StarPowerInfo* info);
double sqrt(double);
s32 BattleBreakSlot_GetBreakTurn();
void* BattleBreakSlotGetPtr();
void BattleBreakSlot_PointInc();
extern s32 audience_kind[];
void BattleAudienceNumToTarget(void);
s32 BattleAudienceNumToTargetSub(void);
void BattleAudienceAddTargetNum(f32 value, f32 value2);
void BattleAudienceAddTargetNumSub(f32 value);
s32 BattleAudienceAddAudienceNum(s32 num);
void BattleAudiencePuniAllEscape(void);
void BattleAudienceAddPuni(s32 num);
void BattleAudienceAddPhaseEvtList(s32 type);
void BattleAudienceCheer(s32 type);
void BattleAudienceJoy(s32 type);
void BattleAudienceJoySACLecture(void);
void BattleAudienceJoyEnding(void);
void BattleAudienceJoy_Sub(s32 a, s32 b, s32 c, s32 type);
s32 BattleAudienceDetectPakkunEatTargetSub2(s32 index, s32 dir);
s32 BattleAudienceDetectPakkunEatTargetSub(s32 index, s32 dir1, s32 dir2);
s32 BattleAudienceDetectPakkunEatTarget(s32 index);
void BattleAudienceSoundBooing(void);
void BattleAudienceSoundBooingKind(s32 kind);
void BattleAudienceSoundClap(s32 duration, s32 fade);
void BattleAudienceSoundNoiseAlways(void);
void BattleAudienceSoundCheer(s32 duration, s32 fade);
void BattleAudienceSoundCheerKind(s32 kind, s32 duration, s32 fade);
void BattleAudienceSoundWhistle(void);
void BattleAudienceSoundWhistleKind(s32 kind);
void BattleAudienceSoundCallKind(s32 kind);
void BattleAudienceSoundHandBeat(void);
void BattleAudienceSoundItemThrow(s32 kind, s32 index);
void BattleAudienceSoundRun(s32 kind);
void BattleAudienceSoundSleep(s32 index);
void BattleAudienceSoundZZZ(s32 index);
void BattleAudienceSoundSing(s32 index);
void BattleAudienceSoundShell(s32 index);
void BattleAudienceSoundBombIgnite(s32 index, s32 duration, s32 fade);
void BattleAudienceSoundBombFire(s32 index);
void BattleAudienceSoundPakkunEat(s32 index);
void BattleAudienceSoundSetVol(s32 index, u8 a2, s32 a3);
void BattleAudienceSoundSetVolAll(u8 vol, s32 length);
u32 BattleAudienceSoundCheck(s32 index);
void BattleAudienceSoundStop(s32 index);
s32 BattleAudienceSound0(const char* name);
s32 BattleAudienceSound1(const char* name, s32 right, s32 left);
void BattleAudienceSoundGetInfo1(s32 right, s32 left, u8* vol, Vec* pos);
s32 BattleAudienceSound2(const char* name, s32 index);
void BattleAudienceSoundGetInfo2(s32 index, Vec* pos);
void BattleAudienceSoundMain(void);
void BattleAudienceNoiseMain(void);

#define AUD_U8CALL(fn, i) (((u8 (*)(s32))(fn))(i))
#define AUD_S32(a, off) (*(s32*)((u8*)(a) + (off)))
#define AUD_F32(a, off) (*(f32*)((u8*)(a) + (off)))
#define AUD_U8(a, off) (*(u8*)((u8*)(a) + (off)))

extern ItemData itemDataTable[];

typedef struct AudItem {
    u32 flags;         // 0x0
    s32 state;         // 0x4
    u8 pad8[0x10 - 0x8];
    ItemType itemType; // 0x10
    Vec pos;           // 0x14
    f32 scale;         // 0x20
    f32 rotZ;          // 0x24
    u8 pad28[0x48 - 0x28];
} AudItem;

typedef struct AudApSrc {
    s32 flags;         // 0x0
    u8 pad4[0x8 - 0x4];
    f32 x;             // 0x8
    f32 y;             // 0xC
    u8 pad10[0x38 - 0x10];
    Vec scale;         // 0x38
    u8 pad44[0x5C - 0x44];
    u8 alpha;          // 0x5C
    u8 pad5d[0x60 - 0x5D];
} AudApSrc;

// overlay for the phase-event list / joy level fields of BattleAudience
typedef struct AudPhaseEvt {
    u8 pad[0x13794];
    s32 weights[12]; // 0x13794
    u8 pad2[0x138CC - 0x137C4];
    s32 list[14];   // 0x138CC
    s32 count;      // 0x13904
    s32 field_13908;
    s32 joyLevel;   // 0x1390C
} AudPhaseEvt;

typedef struct AudMemberAnim {
    s32 flags;        // 0x0
    u8 pad[0x20 - 0x4];
    s32** animTable;  // 0x20
    s32* curAnim;     // 0x24
    s32* animPtr;     // 0x28
    s32 animTimer;    // 0x2C
    s32 field_0x30;   // 0x30
    s32 field_0x34[3]; // 0x34
    u8 field_0x40;    // 0x40
    u8 pad41[0x134 - 0x41];
} AudMemberAnim;

void BattleStatusWindowAPRecoveryOn(void);

s32 weapon_data_akikan[] = {
    0, 0, 236, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17825888, 536870912, 770, 0, 72, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_data_brick[] = {
    0, 0, 237, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17825888, 536870912, 770, 0, 72, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_data_bone[] = {
    0, 0, 238, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17825888, 536870912, 770, 0, 72, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

s32 weapon_data_hammer[] = {
    0, 0, 239, 0, 1677721602, 0, 0, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17825888, 536870912, 770, 0, 72, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};
s32 haiti_data[][10] = {
	{ 18, 16, 16, 0, 0, 0, 0, 0, 0, 0 },
	{ 18, 18, 18, 16, 16, 14, 0, 0, 0, 0 },
	{ 20, 20, 20, 20, 18, 18, 18, 16, 0, 0 },
	{ 20, 20, 20, 20, 20, 20, 20, 20, 20, 20 },
};

//@@ tplRead
FileEntry* tplRead(const char* path) {
	return fileAllocf(4, "%s/%s", getMarioStDvdRoot(), path);
}

//@@ BattleAudienceBaseGetPtr
BattleAudience* BattleAudienceBaseGetPtr(void) {
	return &_battleWorkPointer->audience;
}

//@@ BattleAudienceGetPtr
BattleAudienceMember* BattleAudienceGetPtr(s32 id) {
	return &BattleAudienceBaseGetPtr()->members[id];
}

//@@ BattleAudienceItemGetPtr
BattleAudienceItem* BattleAudienceItemGetPtr(s32 id) {
	return &BattleAudienceBaseGetPtr()->items[id];
}

//@@ BattleAudienceWinGetPtr
BattleAudienceWindow* BattleAudienceWinGetPtr(void) {
	return &BattleAudienceBaseGetPtr()->window;
}

//@@ BattleAudienceSoundGetPtr
BattleAudienceSound* BattleAudienceSoundGetPtr(s32 id) {
	return &BattleAudienceBaseGetPtr()->sounds[id];
}

//@@ BattleAudience_Init
void BattleAudience_Init(void) {
	BattleAudience* audience;
	BattleAudienceWindow* window;
	int i, j, index;
	u8 status;

	audience = BattleAudienceBaseGetPtr();
	window = BattleAudienceWinGetPtr();
	if (1) {
	pouchGetPtr(); //useless call
	memset(audience, 0, sizeof(BattleAudience));
	}
	BattleAudienceSettingAudience();
	audience->normalTex = tplRead("battle/audience/audience_normal.tpl");
	BattleAudienceGuestTPLRead(0, AUDIENCE_LUIGI, "audience_luigi.tpl");
	BattleAudienceSetThrowItemMax();

	audience->mTurnEndPhaseEventChance = 0;

	audience->mCurrentAudienceIntCountLeft = 0;
	audience->mCurrentAudienceIntCountRight = 0;
	audience->mCurrentAudienceIntCount = 0;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			index = (i * 20) + j + 10;
			if (AUD_U8CALL(BattleAudience_GetExist, index) == TRUE) {
				status = BattleAudienceGetPtr(index)->status;
				if (status != 12 && status != 11) { //TODO: add status enum
					audience->mCurrentAudienceIntCountRight++;
				}
			}
		}
	}

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			index = (i * 20) + j;
			if (AUD_U8CALL(BattleAudience_GetExist, index) == TRUE) {
				status = BattleAudienceGetPtr(index)->status;
				if (status != 12 && status != 11) { //TODO: add status enum
					audience->mCurrentAudienceIntCountLeft++;
				}
			}
		}
	}

	audience->mCurrentAudienceIntCount = audience->mCurrentAudienceIntCountRight + audience->mCurrentAudienceIntCountLeft;
	window->count = (f32)audience->mCurrentAudienceIntCount;
	BattleAudienceSoundNoiseAlways();
	BattleAudienceSoundSetVol(2, 60, 180);
	audience->excited = FALSE;
	BattleAudienceNumToTarget();
}

//@@ BattleAudience_Main
void BattleAudience_Main(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleAudience* audience = BattleAudienceBaseGetPtr();

	if (!(audience->flags & 0x10000) && wp->flags & 0x80) {
		BattleAudience_WinSetActive(1);
	}
	BattleAudienceCtrlProcess();
	BattleAudienceItemCtrlProcess();
	BattleAudienceApSrcCtrlProcess();
	BattleAudienceWinCtrlProcess();
	BattleAudienceSoundMain();
	if (wp->flags & 0x80) {
		audience->flags |= 0x10000;
	}
	else {
		audience->flags &= ~0x10000;
	}
}

//@@ BattleAudience_ActInit
void BattleAudience_ActInit(void) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	audience->mNumStylishCommandsThisAttack = 0;
	audience->flags &= ~0x10;
	audience->flags &= ~0x20;
	audience->flags &= ~0x40;
	audience->flags &= ~0x80;
	audience->flags &= ~0x100;
	audience->flags &= ~0x200;
	audience->flags &= ~0x400;
	audience->flags &= ~0x800;
	audience->flags &= ~0x1000;
}

//@@ BattleAudience_PerAct
void BattleAudience_PerAct(void) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	pouchGetPtr();
	//TODO: finish
}

//@@ BattleAudience_CheckReaction
BOOL BattleAudience_CheckReaction(void) {
	BattleAudience* audience;
	EventEntry* evt;

	audience = BattleAudienceBaseGetPtr();
	BattleAudienceGetPtr(0); //unused
	evt = audience->event;
	if (evt && evtCheckID(evt->eventId)) {
		return TRUE;
	}
	audience->event = NULL;
	return FALSE;
}

//@@ check_exe_phase_evt_status
BOOL check_exe_phase_evt_status(s32 index, s32 type) {
	BattleAudienceMember* member;
	u8 status;

	member = BattleAudienceGetPtr(index);
	if (!(u8)BattleAudience_GetSysCtrl(index)) {
		return FALSE;
	}
	if (member->type != type) {
		return FALSE;
	}
	status = member->status;
	if (status == 13) return FALSE;
	if (status == 12) return FALSE;
	if (status == 11) return FALSE;
	if (status == 21) return FALSE;
	if (status == 22) return FALSE;
	return (member->flags >> 3) & 1;
}

//@@ BattleAudience_PerPhase
void BattleAudience_PerPhase(u32 value) {
	BattleAudience* audience;
	BattleAudienceMember* member;
	s32 i;

	audience = BattleAudienceBaseGetPtr();
	if (value == 0x4000002 && !(audience->flags & 0x40000)) {
		for (i = 0; i < 200; i++) {
			member = BattleAudienceGetPtr(i);
			if ((u8)BattleAudience_GetExist(i) == 1 && member->status == 7) {
				if (member->itemId != -1) {
					BattleAudienceItemGetPtr(member->itemId)->flags = 0;
				}
				member->itemId = -1;
				BattleAudience_ChangeStatus(i, 0);
			}
		}
		for (i = 0; i < 100; i++) {
			if (BattleAudienceItemGetPtr(i)->state <= 1) {
				BattleAudienceItemGetPtr(i)->flags = 0;
			}
		}
	}
	if (value == 0x4000004) {
		BattleAudienceSetThrowItemMax();
		audience->flags |= 8;
		audience->mCheckPhaseReactionState = 0;
	}
}

//@@ BattleAudience_CheckReactionPerPhase
BOOL BattleAudience_CheckReactionPerPhase(void) {
	BattleAudience* audience;
	BattleAudienceMember* member;
	s32 counter, i;

	audience = BattleAudienceBaseGetPtr();
	pouchGetPtr();
	if (!(audience->flags & 8)) {
		return FALSE;
	}
	switch (audience->mCheckPhaseReactionState) {
		case 0:
			audience->mCheckPhaseReactionState = 5;
			if (audience->flags & 0x40000) {
				audience->mCheckPhaseReactionState = 15;
				return TRUE;
			}
			//no break
		case 5:
			for (counter = 0, i = 0; i < 200; i++) {
				member = BattleAudienceGetPtr(i);
				if (BattleAudience_GetSysCtrl(i) && member->type == AUDIENCE_BULKY_BOBOMB &&
						member->status == 18 && --member->field_0x12C <= 0) {
					BattleAudience_ChangeStatus(i, 19);
					counter++;
				}
			}
			if (counter < 1) {
				audience->mCheckPhaseReactionState = 7;
			}
			else {
				audience->mCheckPhaseReactionState = 6;
			}
			//no break
		case 6:
		case 7:
			for (i = 0; i < 200; i++) {
				member = BattleAudienceGetPtr(i);
				if (BattleAudience_GetSysCtrl(i) && member->type == AUDIENCE_BULKY_BOBOMB &&
						member->status == 19) {
					break;
				}
			}
			if (i == 200) { //didn't meet that condition
				if (audience->mCheckPhaseReactionState == 6) {
					audience->mCheckPhaseReactionState = 8;
				}
				else {
					audience->mCheckPhaseReactionState = 13;
				}
			}
			return TRUE;
		case 8:
			//audience->evt = evtEntry(&msg_heavy_bomb_fire, 0, 0x20);
			audience->mCheckPhaseReactionState = 9;
			return TRUE;
		case 9:
			if (!evtCheckID(audience->event->eventId)) {
				audience->event = NULL;
				audience->mCheckPhaseReactionState = 10;
			}
			return TRUE;
		case 10:
			if (audience->flags & 0x8000) {
				//audience->evt = evtEntry(&msg_puni_all_escape, 0, 0x20);
				audience->flags &= ~0x8000;
				audience->mCheckPhaseReactionState = 11;
			}
			else {
				audience->mCheckPhaseReactionState = 15;
			}
			return TRUE;
		case 11:
			if (!evtCheckID(audience->event->eventId)) {
				audience->event = NULL;
				audience->mCheckPhaseReactionState = 15;
			}
			return TRUE;












	}




	return FALSE; //TODO: finish, a lot
}

//@@ BattleAudience_Disp
void BattleAudience_Disp(void) {
	BattleAudienceBaseGetPtr();
	BattleAudienceAnimProcess();
	if (!(BattleAudienceBaseGetPtr()->flags & 0x20000)) {
		dispEntry(CAMERA_3D, 0.0f, 1, BattleAudienceDispAudience, NULL);
		dispEntry(CAMERA_3D, 0.0f, 2, BattleAudienceDispAudience, NULL);
		dispEntry(CAMERA_3D, 0.0f, 1, BattleAudienceDispItem, NULL);
		dispEntry(CAMERA_2D, 499.0f, 0, BattleAudienceDispApSrc, NULL);
	}
	if (*(u16*)&pouchGetPtr()->mStarPowersObtained) {
		dispEntry(CAMERA_2D, 499.0f, 1, BattleAudienceDispWin, NULL);
	}
}

//@@ BattleAudience_End
void BattleAudience_End(void) {
	BattleAudience* audience;
	FileEntry* obj;
	int i;

	audience = BattleAudienceBaseGetPtr();
	for (i = 0; i < 2; i++) {
		obj = audience->guestTex[i];
		if (obj) {
			fileFree(obj);
		}
	}

	obj = audience->normalTex;
	if (obj) {
		fileFree(obj);
	}

	if (*(u16*)&pouchGetPtr()->mStarPowersObtained) {
		if (audience->mTargetAudienceCount < 0.0f) {
			audience->mTargetAudienceCount = 0.0f;
		}
		if (1) {
		if (audience->mTargetAudienceCount > (f32)audience->mMaxAudience) {
			audience->mTargetAudienceCount = (f32)audience->mMaxAudience;
		}
		pouchSetAudienceNum(audience->mTargetAudienceCount);
		}
	}
}

//@@ BattleAudienceSettingAudience
void BattleAudienceSettingAudience(void) {
	//TODO: very long and terrible
}

//@@ BattleAudienceGuestTPLRead
void BattleAudienceGuestTPLRead(s32 id, AudienceMemberType member, const char* path) {
	char full_path[256];

	BattleAudience* audience = BattleAudienceBaseGetPtr();
	if (id < 2) {
		sprintf(full_path, "battle/audience/%s", path);
		audience->guestTex[id] = tplRead(full_path);
		audience->guestType[id] = member;
	}
}

//@@ BattleAudienceCtrlProcess
extern void BattleAudienceCtrlProcessKinopio(s32 index);
extern s32 irand(s32);

void BattleAudienceCtrlProcess(void) {
	s32 chance;
	BattleWork* wp = _battleWorkPointer;
	u32* bflags = (u32*)((u8*)wp + 0x19068);
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	BattleAudienceMember* member;
	s32 i, j, index;
	u8 status;
	s32 order[200];

	audience->mCurrentAudienceIntCountLeft = 0;
	audience->mCurrentAudienceIntCountRight = 0;
	audience->mCurrentAudienceIntCount = 0;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			index = (i * 20) + j + 10;
			if (AUD_U8CALL(BattleAudience_GetExist, index) == TRUE) {
				status = BattleAudienceGetPtr(index)->status;
				if (status != 12 && status != 11) {
					audience->mCurrentAudienceIntCountRight++;
				}
			}
		}
	}

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			index = (i * 20) + j;
			if (AUD_U8CALL(BattleAudience_GetExist, index) == TRUE) {
				status = BattleAudienceGetPtr(index)->status;
				if (status != 12 && status != 11) {
					audience->mCurrentAudienceIntCountLeft++;
				}
			}
		}
	}

	audience->mCurrentAudienceIntCount = audience->mCurrentAudienceIntCountRight + audience->mCurrentAudienceIntCountLeft;

	i = 0;
	member = BattleAudienceGetPtr(0);
	for (; i < 200; i++, member++) {
		if (member->flags & 0x10) {
			f32* f = (f32*)((u8*)member + 0xD0);
			f[0] += f[3];
			f[3] += f[5];
			if (f[0] <= 0.0f) {
				f[0] = 0.0f;
				f[3] = 0.0f;
				f[5] = 0.0f;
			}
		} else if (AUD_U8CALL(BattleAudience_GetExist, i)) {
			switch (member->type) {
			case 0: BattleAudienceCtrlProcessKinopio(i); break;
			case 1: BattleAudienceCtrlProcessKinopio(i); break;
			case 2: BattleAudienceCtrlProcessKinopio(i); break;
			case 3: BattleAudienceCtrlProcessKinopio(i); break;
			case 4: BattleAudienceCtrlProcessKinopio(i); break;
			case 5: BattleAudienceCtrlProcessKinopio(i); break;
			case 6: BattleAudienceCtrlProcessKinopio(i); break;
			case 7: BattleAudienceCtrlProcessKinopio(i); break;
			case 8: BattleAudienceCtrlProcessKinopio(i); break;
			case 9: BattleAudienceCtrlProcessKinopio(i); break;
			case 10: BattleAudienceCtrlProcessKinopio(i); break;
			case 11: BattleAudienceCtrlProcessKinopio(i); break;
			case 12: BattleAudienceCtrlProcessKinopio(i); break;
			}
		}
	}

	if (*bflags & 0x20000) {
		*(s32*)&audience->field_137F0[4] = 10000;
	}
	if (wp->flags & 0x80) {
		if (*(s32*)&audience->field_137F0[0] < *(s32*)&audience->field_137F0[4]) {
			switch (*(s32*)&audience->field_137F0[0]) {
			case 0: chance = 1800; break;
			case 1: chance = 6000; break;
			case 2: chance = 30000; break;
			}
			if (*bflags & 0x20000) {
				chance = 60;
			}
			if (irand(chance) == 0) {
				for (i = 0; i < 200; i++) {
					order[i] = i;
				}
				for (i = 0; i < 1000; i++) {
					s32 a = irand(200);
					s32 b = irand(200);
					s32 t = order[a];
					order[a] = order[b];
					order[b] = t;
				}
				for (i = 0; i < 200; i++) {
					if (BattleAudienceItemOn(order[i], 0, 1) == TRUE) {
						(*(s32*)&audience->field_137F0[0])++;
						return;
					}
				}
			}
		}
	}
}

//@@ BattleAudienceItemOn
BOOL BattleAudienceItemOn(s32 index, u16 itemId, s32 numItems) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	BattleAudienceMember* member = BattleAudienceGetPtr(index);
	BattleAudienceItem* item;
	s32 st;
	u8 ust;

	if (audience->flags & 0x40000) return FALSE;
	if (*(s32*)audience_kind[member->type * 8 + 2] == 0) return FALSE;
	if (itemId >= 0x79 && itemId < 0xEC && swGet(0xEB) == 0) return FALSE;
	st = index % 20;
	if (st < 4 || st > 15) return FALSE;
	if (!AUD_U8CALL(BattleAudience_GetExist, index)) return FALSE;
	ust = member->status;
	if (ust == 7) return FALSE;
	if (ust == 8) return FALSE;
	if (ust == 13) return FALSE;
	if (ust == 12) return FALSE;
	if (ust == 11) return FALSE;
	if (ust == 18) return FALSE;
	if (ust == 17) return FALSE;
	if (ust == 21) return FALSE;
	if (ust == 10) return FALSE;
	if (member->flags & 8) {
		s32 i = 0;
		item = BattleAudienceItemGetPtr(0);
		for (; i < numItems; i++, item++) {
			if (!(item->flags & 1)) {
				item->flags |= 1;
				item->state = 0;
				*(s32*)((u8*)item + 0xC) = index;
				item->mItemType = itemId;
				BattleAudience_ChangeStatus(index, 7);
				member->itemId = i;
				return TRUE;
			}
		}
	}
	return FALSE;
}

//@@ BattleAudienceSetThrowItemMax
void BattleAudienceSetThrowItemMax(void) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	s32 r = irand(100);

	if (r < 80) {
		AUD_S32(audience, 0x137F4) = 0;
	} else if (r < 90) {
		AUD_S32(audience, 0x137F4) = 1;
	} else if (r < 95) {
		AUD_S32(audience, 0x137F4) = 2;
	} else if (r < 100) {
		AUD_S32(audience, 0x137F4) = 3;
	}
	AUD_S32(audience, 0x137F0) = 0;
	AUD_S32(audience, 0x137F8) = 0;
}

//@@ BattleAudienceDetectTargetAll
BattleUnit* BattleAudienceDetectTargetAll(void) {
	s32 i;
	BattleWork* wp = _battleWorkPointer;
	BattleUnit* unit;
	s32 count;
	BattleUnitPart* part;
	s32 ids[64];

	BattleAudienceBaseGetPtr();
	count = 0;
	for (i = 0; i < 64; i++) {
		unit = wp->units[i];
		if (unit != NULL) {
			part = BattleGetUnitPartsPtr(i, BtlUnit_GetBodyPartsId(unit));
			if (!(part->attributes & 0x10000) && unit->currentHp > 0 &&
			    (unit->currentKind < 0xD8 || unit->currentKind >= 0xDA)) {
				ids[count++] = i;
			}
		}
	}
	if (count == 0) {
		return NULL;
	}
	i = irand(count);
	return BattleGetUnitPtr(wp, ids[i]);
}

//@@ BattleAudienceDetectTargetPlayer
BattleUnit* BattleAudienceDetectTargetPlayer(void) {
	s32 i;
	BattleWork* wp = _battleWorkPointer;
	BattleUnit* unit;
	s32 count;
	BattleUnitPart* part;
	s32 ids[64];

	BattleAudienceBaseGetPtr();
	count = 0;
	for (i = 0; i < 64; i++) {
		unit = wp->units[i];
		if (unit != NULL) {
			part = BattleGetUnitPartsPtr(i, BtlUnit_GetBodyPartsId(unit));
			if (unit->mAlliance == 0 && unit->currentHp > 0 && !(part->attributes & 0x10000)) {
				ids[count++] = i;
			}
		}
	}
	if (count == 0) {
		return NULL;
	}
	i = irand(count);
	return BattleGetUnitPtr(wp, ids[i]);
}

//@@ BattleAudienceItemCtrlProcess
typedef struct AudItemX {
	u32 flags;
	s32 state;
	s32 timer;
	s32 audId;
	s32 itemType;
	Vec pos;
	f32 scale;
	f32 rotZ;
	Vec vel;
	Vec acc;
	BattleUnit* target;
	s32 mode;
} AudItemX;
extern Vec vec3_802f972c[];
extern Vec vec3_802f9738[];
extern u8 lbl_80399940[];
extern void BattleAudience_SetPresentItemType(s32);
extern void BattleAudience_SetPresentTargetUnitId(s32);
extern void BattleAudience_SetPresentItemNo(s32);
extern s32 BattleAudience_GetPresentItemType(void);
extern s32 BtlUnit_CheckShadowGuard(BattleUnit*);
extern double __fabs(double);
static inline double fabs(double x) { return __fabs(x); }
void BattleAudienceItemCtrlProcess(void) {
	BattleWork* wp = _battleWorkPointer;
	u8* base = (u8*)BattleAudienceBaseGetPtr();
	AudItemX* it;
	s32 i;
	u8* aud;
	u8* kd;
	u8* d = lbl_80399940;
	s32 j;

	it = (AudItemX*)BattleAudienceItemGetPtr(0);
	for (i = 0; i < 100; i++, it++) {
		if (!(it->flags & 1)) {
			continue;
		}
		aud = (u8*)BattleAudienceGetPtr(it->audId);
		kd = (u8*)audience_kind + aud[0x1b] * 32;
		if (aud[0x19] == 13 || aud[0x19] == 19 || aud[0x19] == 21 || aud[0x19] == 12 ||
		    !(u8)BattleAudience_GetExist(it->audId)) {
			goto kill;
		}
		if ((u32)it->state > 7) {
			continue;
		}
		switch (it->state) {
		case 0: {
			it->flags |= 2;
			if (it->itemType == 0) {
				s32* tbl = *(s32**)(kd + 8);
				s32 cnt = 0;
				s32 sum = 0;
				s32 acc;
				s32 r;
				for (j = 0; tbl[j * 2] != 0; j++) {
					cnt++;
					sum += tbl[j * 2 + 1];
				}
				if (cnt == 0) {
					goto done;
				}
				r = irand(sum);
				acc = 0;
				for (j = 0;; j++) {
					if (r >= acc && r < acc + tbl[j * 2 + 1]) {
						break;
					}
					acc += tbl[j * 2 + 1];
				}
				it->itemType = tbl[j * 2];
			}
			it->timer = i + 180;
			it->scale = 1.0f;
			it->rotZ = 0.0f;
			{
				Vec v = vec3_802f972c[0];
				v.x = *(f32*)(aud + 0x48) + *(f32*)(kd + 0xc);
				v.y = (*(f32*)(aud + 0x4c) + *(f32*)(kd + 0x10)) - 10.0f;
				v.z = 1.0f + *(f32*)(aud + 0x50);
				it->pos = v;
			}
			it->state++;
		}
		/* fallthrough */
		case 1: {
			if (it->timer <= 0) {
				BattleUnit* t;
				f32 hx, hy, hz, dx, n;
				for (j = 0; j < 100; j++) {
					if (j != i && (((AudItemX*)BattleAudienceItemGetPtr(j))->flags & 1) &&
					    ((AudItemX*)BattleAudienceItemGetPtr(j))->state == 1) {
						it->mode = 2;
						break;
					}
				}
				if (j == 100) {
					it->mode = 1;
				}
				t = BattleAudienceDetectTargetPlayer();
				if (t == NULL) {
					goto done;
				}
				it->target = t;
				BtlUnit_GetHitPos(t, BtlUnit_GetPartsPtr(t, BtlUnit_GetBodyPartsId(t)), &hx, &hy, &hz);
				dx = hx - it->pos.x;
				n = 30.0f + fabs(dx) / 15.0f;
				it->vel.x = dx / n;
				it->acc.x = 0.0f;
				it->vel.y = 7.0f;
				it->acc.y = 2.0f * ((hy - it->pos.y) - it->vel.y * n) / (n * n);
				it->vel.z = (hz - it->pos.z) / n;
				it->acc.z = 0.0f;
				it->timer = (s32)n;
				it->state++;
			} else {
				s32 k = 180 - it->timer;
				Vec v = vec3_802f9738[0];
				f32 ox;
				if (k >= 5) {
					k = 5;
				}
				v.x = *(f32*)(aud + 0xc0) + *(f32*)(kd + 0xc);
				ox = intplGetValue(0, k, 5, -10.0f, 0.0f);
				it->pos.x = v.x;
				v.y = (*(f32*)(aud + 0xc4) + *(f32*)(kd + 0x10)) + ox;
				v.z = 1.0f + *(f32*)(aud + 0xc8);
				it->pos.y = v.y;
				it->pos.z = v.z;
			}
			break;
		}
		case 2: {
			if (!(*(u32*)((u8*)wp + 0xef4) & 0x80)) {
				it->mode = 0;
			}
			if (it->timer == 20) {
				BattleAudience_ChangeStatus(it->audId, 0);
			}
			if (it->timer == 0) {
				it->state++;
			}
			if (it->timer > 0) {
				it->pos.x += it->vel.x;
				it->pos.y += it->vel.y;
				it->pos.z += it->vel.z;
				it->vel.x += it->acc.x;
				it->vel.y += it->acc.y;
				it->vel.z += it->acc.z;
				if (it->itemType == 0xef) {
					it->rotZ += 18.0f;
				}
				it->timer--;
			}
			break;
		}
		case 3: {
			BattleUnit* t;
			s8 a, b;
			if (!(*(u32*)((u8*)wp + 0xef4) & 0x80)) {
				it->mode = 0;
			}
			t = it->target;
			BtlUnit_GetStatus(t, 0x12, &a, &b);
			if (a >= 1 || BtlUnit_CheckShadowGuard(t)) {
				it->mode = 0;
			}
			if (it->flags & 4) {
				it->mode = 0;
			}
			if (it->itemType >= 0x80 && it->itemType < 0xec && pouchGetEmptyHaveItemCnt() <= 0) {
				it->mode = 0;
			}
			if (it->mode != 0) {
				s32* cnt = (s32*)(base + 0x137f8);
				(*cnt)++;
				if (*cnt > 3) {
					*cnt = 3;
				}
				if (it->mode == 2) {
					it->state = 4;
					goto s4;
				}
				if (it->itemType >= 0x79 && it->itemType < 0xec) {
					BattleAudience_SetPresentItemType(0);
				} else if (it->itemType >= 0xec && it->itemType < 0xf0) {
					BattleAudience_SetPresentItemType(1);
				}
				BattleAudience_SetPresentTargetUnitId(BtlUnit_GetUnitId(t));
				switch (it->itemType) {
				case 0xec:
					memcpy(base + 0x137fc, d + 0x40, 0xc0);
					*(s32*)(base + 0x1381c) = *cnt + *(s32*)(base + 0x1381c) - 1;
					break;
				case 0xed:
					memcpy(base + 0x137fc, d + 0x100, 0xc0);
					*(s32*)(base + 0x1381c) = *cnt + *(s32*)(base + 0x1381c) - 1;
					break;
				case 0xee:
					memcpy(base + 0x137fc, d + 0x1c0, 0xc0);
					*(s32*)(base + 0x1381c) = *cnt + *(s32*)(base + 0x1381c) - 1;
					break;
				case 0xef:
					memcpy(base + 0x137fc, d + 0x280, 0xc0);
					*(s32*)(base + 0x1381c) = *cnt + *(s32*)(base + 0x1381c) - 1;
					break;
				}
				BattleAudience_SetPresentItemNo(it->itemType);
				switch (BattleAudience_GetPresentItemType()) {
				case 0:
					it->flags &= ~2;
					it->timer = 5;
					it->state = 7;
					break;
				case 1:
					BattleAudienceSoundStop(10);
					BattleAudienceSoundStop(11);
					if (it->vel.x < 0.0f) {
						it->vel.x *= -0.2f;
					}
					it->vel.y = 1.5f;
					it->vel.z = 0.0f;
					it->state = 4;
					break;
				}
				*cnt = 0;
			} else {
				it->state = 4;
			}
			if (it->state != 4) {
				break;
			}
		}
		/* fallthrough */
		case 4:
		s4: {
			it->pos.x += it->vel.x;
			it->pos.y += it->vel.y;
			it->pos.z += it->vel.z;
			it->vel.x += it->acc.x;
			it->vel.y += it->acc.y;
			it->vel.z += it->acc.z;
			if (it->pos.y <= 0.0f) {
				BattleAudienceSoundStop(10);
				BattleAudienceSoundStop(11);
				it->state = 5;
				it->pos.y = 0.1f;
				it->vel.y = 1.0f;
				it->acc.y = 0.0f;
			}
			break;
		}
		case 5: {
			it->pos.x += it->vel.x;
			it->pos.y += it->vel.y;
			it->pos.z += it->vel.z;
			it->vel.x += it->acc.x;
			it->vel.y += it->acc.y;
			it->vel.z += it->acc.z;
			if (it->pos.y <= 0.0f) {
				it->timer = 60;
				it->state = 6;
				it->pos.y = 0.0f;
			}
			break;
		}
		case 6: {
			if (it->timer <= 0) {
				goto done;
			}
			if (it->timer < 30) {
				if ((it->timer & 3) <= 1) {
					it->flags |= 2;
				} else {
					it->flags &= ~2;
				}
			}
			it->timer--;
			break;
		}
		case 7: {
			it->timer--;
			if (it->timer > 0) {
				break;
			}
		}
		done:
			BattleAudienceSoundStop(10);
			BattleAudienceSoundStop(11);
			if (it->audId != -1) {
				BattleAudienceGetPtr(it->audId);
				BattleAudience_ChangeStatus(it->audId, 0);
			}
		kill:
			it->flags = 0;
			it->timer = 0;
			it->state = 0;
			if (it->audId != -1) {
				*(s16*)((u8*)BattleAudienceGetPtr(it->audId) + 0x1c) = -1;
			}
			break;
		}
	}
}

//@@ BattleAudienceApSrcCtrlProcess
extern Vec vec3_802f9744[];
extern double asin(double);
extern double cos(double);
extern double sin(double);
extern void statusGetApPos(Vec* pos);
void BattleAudienceApSrcCtrlProcess(void) {
	BattleAudience* base = BattleAudienceBaseGetPtr();
	AudApSrc* star;
	s32 cnt;
	s32 i;
	s32 k;
	f32 dy;
	f32 dx;
	Vec tmp;
	Vec tmp2;

	if (!(*(u32*)base & 2)) {
		return;
	}
	cnt = 0;
	star = (AudApSrc*)((u8*)base + 0x10E7C);
	for (i = 0; i < 100; i++) {
		if (*(u32*)((u8*)base + 0x10E7C + i * 0x60) & 1) {
			cnt++;
		}
	}
	if (psndSFXChk(((s32*)base)[2]) != -1) {
		psndSFX_vol(((s32*)base)[2], 63.0f * cnt / 100.0f + 64.0f);
	}
	if (*(s32*)((u8*)base + 0x137C4) > 0) {
		if (BattleAudienceApSrcEntry() == TRUE) {
			(*(s32*)((u8*)base + 0x137C4))--;
		}
		if (cnt == 0 && psndSFXChk(((s32*)base)[2]) == -1) {
			((s32*)base)[2] = ((s32 (*)(const char*))psndSFXOn)("SFX_BTL_AUDIENCE_AP_FLOW1");
		}
	} else {
		for (k = 0, i = 0; i < 100; i++) {
			if (*(u32*)((u8*)base + 0x10E7C + i * 0x60) & 1) {
				break;
			}
			k++;
		}
		if (k == 100) {
			*(u32*)base &= ~2;
			psndSFXOff(((s32*)base)[2]);
			((s32*)base)[2] = 0;
			*(s32*)((u8*)base + 0x137C4) = 0;
			BattleStatusWindowAPRecoveryOff();
			return;
		}
	}
	for (i = 0; i < 100; i++) {
		AudApSrc* s = (AudApSrc*)((u8*)base + 0x10E7C + i * 0x60);
		u8* p = (u8*)s;
		pouchGetPtr();
		if (!(s->flags & 1)) {
			continue;
		}
		switch (*(s32*)(p + 4)) {
		case 0:
			*(s32*)(p + 4) = 5;
			*(Vec*)(p + 0x2C) = *(Vec*)(p + 0x8);
			*(Vec*)(p + 0x20) = *(Vec*)(p + 0x2C);
			*(f32*)(p + 0x2C) += 50.0f * rand() / 32767.0f - 25.0f;
			*(f32*)(p + 0x30) += 25.0f;
			*(s32*)(p + 0x44) = 0;
			*(s32*)(p + 0x48) = 30;
			/* fallthrough */
		case 5:
			(*(s32*)(p + 0x44))++;
			s->x = intplGetValue(5, *(s32*)(p + 0x44), *(s32*)(p + 0x48), *(f32*)(p + 0x20), *(f32*)(p + 0x2C));
			s->y = intplGetValue(5, *(s32*)(p + 0x44), *(s32*)(p + 0x48), *(f32*)(p + 0x24), *(f32*)(p + 0x30));
			if (*(s32*)(p + 0x44) >= *(s32*)(p + 0x48) - 20) {
				s->scale.y = intplGetValue(4, *(s32*)(p + 0x44) - (*(s32*)(p + 0x48) - 20), 10, 0.9f, 0.8f);
			}
			if (*(s32*)(p + 0x44) >= *(s32*)(p + 0x48)) {
				*(s32*)(p + 4) = 10;
				*(s32*)(p + 0x44) = 0;
				*(s32*)(p + 0x48) = 15 + irand(10);
				s->scale = vec3_802f9744[0];
			}
			break;
		case 10:
			(*(s32*)(p + 0x44))++;
			if (*(s32*)(p + 0x44) >= *(s32*)(p + 0x48)) {
				*(s32*)(p + 4) = 15;
				*(s32*)(p + 0x44) = 0;
				*(s32*)(p + 0x48) = 20 + irand(20);
				*(Vec*)(p + 0x20) = *(Vec*)(p + 0x8);
				statusGetApPos(&tmp);
				*(Vec*)(p + 0x2C) = tmp;
				dy = *(f32*)(p + 0x24) - *(f32*)(p + 0x30);
				dx = *(f32*)(p + 0x20) - *(f32*)(p + 0x2C);
				*(f32*)(p + 0x4C) = *(f32*)(p + 0x50) =
				    sqrt(dx * dx + dy * dy);
				*(f32*)(p + 0x54) = asin(dy / *(f32*)(p + 0x4C));
				*(f32*)(p + 0x58) = 0.05f + 0.2f * rand() / 32767.0f;
			}
			break;
		case 15:
			(*(s32*)(p + 0x44))++;
			*(f32*)(p + 0x4C) = intplGetValue(4, *(s32*)(p + 0x44), *(s32*)(p + 0x48), *(f32*)(p + 0x50), 0.0f);
			*(f32*)(p + 0x54) += *(f32*)(p + 0x58);
			if (*(f32*)(p + 0x54) < 0.0f) {
				*(f32*)(p + 0x54) += 6.2832f;
			}
			s->x = *(f32*)(p + 0x4C) * (f32)cos(*(f32*)(p + 0x54)) + *(f32*)(p + 0x2C);
			s->y = *(f32*)(p + 0x4C) * (f32)sin(*(f32*)(p + 0x54)) + *(f32*)(p + 0x30);
			if (*(s32*)(p + 0x44) >= *(s32*)(p + 0x48)) {
				*(s32*)(p + 4) = 20;
				*(s32*)(p + 0x44) = 0;
				*(s32*)(p + 0x48) = 15;
				statusGetApPos(&tmp2);
				*(Vec*)(p + 0x8) = tmp2;
			}
			break;
		case 20:
			(*(s32*)(p + 0x44))++;
			s->alpha = intplGetValue(4, *(s32*)(p + 0x44), *(s32*)(p + 0x48), 128.0f, 0.0f);
			if (*(s32*)(p + 0x44) >= *(s32*)(p + 0x48)) {
				s->flags = 0;
				pouchAddAP(1);
			}
			break;
		}
	}
}

//@@ BattleAudienceApSrcEntry
extern Vec vec3_802f9750[];
extern Vec vec3_802f975c[];
BOOL BattleAudienceApSrcEntry(void) {
	AudApSrc* star;
	CameraEntry* cam;
	s32 list[200];
	s32 i;
	s32 count;
	BattleAudience* base = BattleAudienceBaseGetPtr();
	BattleAudienceMember* m;
	star = (AudApSrc*)((u8*)base + 0x10E7C);
	for (i = 0; i < 100; i++, star++) {
		if (!(star->flags & 1)) {
			break;
		}
	}
	count = i;
	if (count == 100) {
		return FALSE;
	}
	count = 0;
	BattleAudienceGetPtr(0);
	for (i = 0; i < 200; i++) {
		if ((u8)BattleAudience_GetExist(i) == 1) {
			list[count++] = i;
		}
	}
	if (count == 0) {
		return TRUE;
	}
	star->flags = 1;
	*(s32*)((u8*)star + 4) = 0;
	*(s32*)((u8*)star + 0x44) = 0;
	star->scale = vec3_802f9750[0];
	star->alpha = 0x80;
	m = BattleAudienceGetPtr(list[irand(count)]);
	star->x = *(f32*)((u8*)m + 0x48);
	star->y = 20.0f + *(f32*)((u8*)m + 0x4C);
	*(f32*)((u8*)star + 0x10) = 1.0f + *(f32*)((u8*)m + 0x50);
	cam = camGetPtr(CAMERA_3D);
	PSMTXMultVec((void*)((u8*)cam + 0x11C), (Vec*)&star->x, (Vec*)&star->x);
	PSMTX44MultVec((void*)((u8*)cam + 0x15C), (Vec*)&star->x, (Vec*)&star->x);
	star->x *= 304.0f;
	star->y *= 240.0f;
	*(f32*)((u8*)star + 0x10) = 0.0f;
	*(f32*)((u8*)star + 0x14) = 40.0f * rand() / 32767.0f - 20.0f;
	*(f32*)((u8*)star + 0x18) = 10.0f * rand() / 32767.0f;
	*(f32*)((u8*)star + 0x1C) = 0.0f;
	*(Vec*)((u8*)star + 0x20) = *(Vec*)&star->x;
	*(Vec*)((u8*)star + 0x2C) = vec3_802f975c[0];
	return TRUE;
}

//@@ BattleAudienceWinCtrlProcess
void BattleAudienceWinCtrlProcess(void) {
	BattleAudience* base = BattleAudienceBaseGetPtr();
	BattleAudienceWindow* win = BattleAudienceWinGetPtr();
	f32 diff = (f32)base->mCurrentAudienceIntCount - win->count;
	f32 step;

	if (diff != 0.0f) {
		if (diff > 0.0f) {
			step = (0.1f * diff < 0.1f) ? 0.1f : 0.1f * diff;
			win->count += step;
			if ((f32)base->mCurrentAudienceIntCount - win->count < 0.0f) {
				win->count = (f32)base->mCurrentAudienceIntCount;
			}
		} else {
			step = (-0.1f < 0.1f * diff) ? 0.1f : -0.1f * diff;
			win->count -= step;
			if ((f32)base->mCurrentAudienceIntCount - win->count > 0.0f) {
				win->count = (f32)base->mCurrentAudienceIntCount;
			}
		}
	}

	if (win->mActive) {
		((s32*)win)[5]++;
		if (((s32*)win)[5] > 15) {
			((s32*)win)[5] = 15;
		}
	} else {
		((s32*)win)[5]--;
		if (((s32*)win)[5] < 0) {
			((s32*)win)[5] = 0;
		}
	}
	((f32*)win)[2] = intplGetValue(4, ((s32*)win)[5], 15, -500.0f, -280.0f);
	((f32*)win)[3] = -160.0f;
	((f32*)win)[4] = 0.0f;
}

//@@ BattleAudienceGXInit
void BattleAudienceGXInit(void) {
	BattleAudienceBaseGetPtr();
	GXSetCullMode(GX_CULL_NONE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GXSetNumChans(1);
	GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
	GXSetNumTexGens(1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
	GXSetNumTevStages(1);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
}

//@@ BattleAudienceAnimProcess
void BattleAudienceAnimProcess(void) {
	typedef struct AudAnimMember {
		s32 flags;
		u8 pad0[0x1A - 4];
		u8 v1A;
		u8 pad1[0x24 - 0x1B];
		s32* start;
		s32* pc;
		s32 wait;
		s32 loop[4];
		u8 depth;
		u8 pad2[0x134 - 0x41];
	} AudAnimMember;
	AudAnimMember* m;
	s32 i;
	s32* pc;
	s32 n;
	s32 target;

	BattleAudienceBaseGetPtr();
	m = (AudAnimMember*)BattleAudienceGetPtr(0);
	for (i = 0; i < 200; i++, m++) {
		if (!(m->flags & 1)) continue;
		if (!(m->flags & 4)) continue;
		pc = m->pc;
		if (m->wait > 0) {
			m->wait--;
			continue;
		}
		switch (pc[0]) {
		case -2:
			m->v1A = pc[1];
			m->wait = pc[2];
			m->pc += 3;
			break;
		case -3:
			m->pc = m->start;
			break;
		case -4:
			m->pc += 2;
			break;
		case -5:
			target = pc[1];
			m->pc = m->start;
			while (!(m->pc[0] == -4 && m->pc[1] == target)) {
				m->pc++;
			}
			break;
		case -6:
			m->loop[m->depth] = pc[1];
			m->depth++;
			m->pc += 2;
			break;
		case -7:
			m->loop[m->depth - 1]--;
			if (m->loop[m->depth - 1] <= 0) {
				m->depth--;
				m->pc += 1;
			} else {
				n = 1;
				do {
					m->pc--;
					if (m->pc[0] == -6) n--;
					if (m->pc[0] == -7) n++;
				} while (n > 0);
				m->pc += 2;
			}
			break;
		case -8:
			m->wait = pc[1];
			m->pc += 2;
			break;
		case -1:
			break;
		}
	}
}

//@@ BattleAudienceDispAudience
void BattleAudienceDispAudience(CameraId camId, void* param) {

}

//@@ BattleAudienceDispItem
void BattleAudienceDispItem(CameraId camId, void* param) {
	AudItem* item;
	s32 i;
	u16 iconId;
	Mtx mtx;
	Mtx rot;

	BattleAudienceGXInit();
	i = 0;
	item = (AudItem*)BattleAudienceItemGetPtr(0);
	for (; i < 100; i++, item++) {
		if ((item->flags & 1) && (item->flags & 2)) {
			iconId = itemDataTable[item->itemType].icon_id;
			PSMTXTrans(mtx, 0.0f, -20.0f, 0.0f);
			PSMTXRotRad(rot, 'z', 0.017453292f * item->rotZ);
			PSMTXConcat(rot, mtx, mtx);
			PSMTXTransApply(mtx, mtx, 0.0f, 20.0f, 0.0f);
			PSMTXScaleApply(mtx, mtx, item->scale, item->scale, 1.0f);
			PSMTXTransApply(mtx, mtx, item->pos.x, item->pos.y, item->pos.z);
			((void (*)(Mtx, s16, u16))iconDispGx2)(mtx, 0, iconId);
		}
	}
}

//@@ BattleAudienceDispApSrc
void BattleAudienceDispApSrc(CameraId camId, void* param) {
	s32 i;
	AudApSrc* star;
	Mtx rot;
	Mtx scale;
	Mtx trans;
	Mtx mtx;
	GXColor arg;

	star = (AudApSrc*)BattleAudienceBaseGetPtr();
	camGetPtr(CAMERA_2D);
	BattleAudienceGXInit();
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
	star = (AudApSrc*)((u8*)star + 0x10E7C);
	for (i = 0; i < 100; i++, star++) {
		if (star->flags & 1) {
			PSMTXScale(scale, star->scale.x, star->scale.y, star->scale.z);
			PSMTXRotRad(rot, 'z', 0.0f);
			PSMTXTrans(trans, star->x, star->y, 0.0f);
			PSMTXConcat(scale, rot, mtx);
			PSMTXConcat(trans, mtx, mtx);
			{
				GXColor col = {0xFF, 0xFF, 0xFF, 0x00};
				col.a = star->alpha;
				arg = col;
			}
			iconDispGxCol(mtx, 0x10, 0x1B2, arg);
		}
	}
}
//@@ BattleAudienceDispWin
void BattleAudienceDispWin(CameraId camId, void* param) {
	BattleAudienceWindow* win;
	Mtx mtx;

	BattleAudienceBaseGetPtr();
	win = BattleAudienceWinGetPtr();
	{
		GXColor col = {0xFF, 0xFF, 0xFF, 0xCF};
		windowDispGX_Waku_col(0, col, AUD_F32(win, 0x8), AUD_F32(win, 0xC), 90.0f, 40.0f, 10.0f);
	}
	{
		Vec pos = {0.0f, 0.0f, 0.0f};
		pos.x = 17.0f + AUD_F32(win, 0x8);
		pos.y = AUD_F32(win, 0xC) - 40.0f;
		iconDispGx(&pos, 0x10, 0x209, 0.8f);
	}
	PSMTXTrans(mtx, 75.0f + AUD_F32(win, 0x8), AUD_F32(win, 0xC) - 40.0f, 0.0f);
	{
		GXColor numCol = {0xFF, 0xFF, 0xFF, 0xFF};
		iconNumberDispGx(mtx, win->count, 0, numCol);
	}
}

//@@ BattleAudience_Entry
BOOL BattleAudience_Entry(s32 index, AudienceMemberType type, u8 status) {
	BattleAudienceMember* m;
	f32 x;

	BattleAudienceBaseGetPtr();
	BattleStageGetPtr();
	m = BattleAudienceGetPtr(index);
	if (!(((u8*)audience_kind)[(type & 0xFF) * 32] & 1)) {
		if (m->flags & 1) {
			return FALSE;
		}
		if (m->flags & 0x100) {
			return FALSE;
		}
		m->flags = 5;
		x = (index % 20) * 25 + rand() * 10 / 0x7fff - 0xeb;
		m->position.x = x;
		m->mHomePosition.x = x;
		BattleAudience_Entry_Sub(index, (u8)type, (u8)status);
	} else {
		if (index % 2 == 1) {
			return FALSE;
		}
		if (m->flags & 1) {
			return FALSE;
		}
		if (m->flags & 0x100) {
			return FALSE;
		}
		m->flags = 0x85;
		x = 12.5f + (f32)((index % 20) * 25 - 230) + (f32)(rand() * 10 / 0x7fff) - 5.0f;
		m->position.x = x;
		m->mHomePosition.x = x;
		BattleAudience_Entry_Sub(index, (u8)type, (u8)status);
		m[1].flags = 0x101;
	}
	return TRUE;
}

//@@ BattleAudience_Entry_Sub
void BattleAudience_Entry_Sub(s32 index, s32 type, u8 status) {
	static const Vec v0 = {0.0f, 0.0f, 0.0f};
	static const Vec v1 = {0.0f, 0.0f, -1.0f};
	static const Vec v2 = {0.0f, 0.0f, 0.0f};
	static const Vec v3 = {0.0f, 0.0f, 0.0f};
	static const Vec v4 = {1.0f, 1.0f, 1.0f};
	static const Vec v5 = {1.0f, 1.0f, 1.0f};
	static const Vec v6 = {0.0f, 0.0f, 0.0f};
	BattleAudienceMember* m;
	u8* stage;
	s32 row;
	f32 y, z;

	BattleAudienceBaseGetPtr();
	stage = (u8*)BattleStageGetPtr();
	m = (BattleAudienceMember*)BattleAudienceGetPtr(index);
	m->field_0x4 = 0;
	m->field_0x8 = 0;
	m->status = status;
	m->type = type;
	m->itemId = -1;
	m->animTable = (s32**)audience_kind[type * 8 + 1];
	m->field_0x30 = 0;
	BattleAudience_SetAnim(index, 1, TRUE);
	*((u8*)m + 0x40) = 0;
	m->field_0x43 = 0;
	m->field_0x42 = 0;
	m->field_0x41 = 0;
	m->field_0x44 = 255;
	row = index / 20;
	y = *(f32*)(stage + 0xB34);
	m->position.y = y;
	m->mHomePosition.y = y;
	z = 0.1f * (f32)(index % 20) + (f32)(row * 30 + 0x73);
	m->position.z = z;
	m->mHomePosition.z = z;
	if (m->type == 11) {
		m->mHomePosition.z += 0.2f;
		m->position.z += 0.2f;
	}
	if (m->status == 11) {
		m->position.y = -2000.0f;
	}
	*(Vec*)m->field_0x84 = v0;
	m->field_0x78 = *(Vec*)m->field_0x84;
	m->field_0x90 = v1;
	m->mRotation = v2;
	m->mRotationOffset = v3;
	*(Vec*)m->field_0x54 = v4;
	m->field_0x60 = v5;
	m->field_0x6C = v6;
	m->field_0xE8 = 270.0f;
	if ((index >= 4 && index <= 15) || (index >= 24 && index <= 35) || (index >= 44 && index <= 55)) {
		m->flags |= 8;
	}
}

//@@ BattleAudience_Delete
void BattleAudience_Delete(s32 index) {
	BattleAudienceMember* member;

	BattleAudienceBaseGetPtr();
	member = BattleAudienceGetPtr(index);
	if (member->flags & 0x80) {
		member[1].flags = 0;
	}
	member->flags = 0;
}

//@@ BattleAudience_SetAnim
void BattleAudience_SetAnim(s32 id, s32 animId, BOOL force) {
	AudMemberAnim* member;
	s32* anim;
	s32 i;

	BattleAudienceBaseGetPtr();
	member = (AudMemberAnim*)BattleAudienceGetPtr(id);
	if (!(member->flags & 1)) {
		return;
	}
	if (member->flags & 0x100) {
		return;
	}
	anim = member->animTable[animId];
	if (member->curAnim != NULL && member->curAnim == anim && !force) {
		return;
	}
	member->curAnim = anim;
	member->animPtr = anim;
	member->animTimer = 0;
	for (i = 0; i < 3; i++) {
		member->field_0x34[i] = 0;
	}
	member->field_0x40 = 0;
}

//@@ BattleAudience_GetAnimEnd
BOOL BattleAudience_GetAnimEnd(s32 index) {
	AudMemberAnim* member = (AudMemberAnim*)BattleAudienceGetPtr(index);

	if (*member->animPtr != -1) {
		return FALSE;
	}
	return member->animTimer <= 0;
}

//@@ BattleAudience_GetPosition
void BattleAudience_GetPosition(s32 index, f32* x, f32* y, f32* z) {
	BattleAudienceMember* member;

	member = BattleAudienceGetPtr(index);
	*x = member->position.x;
	*y = member->position.y;
	*z = member->position.z;
}

//@@ BattleAudience_GetHomePosition
void BattleAudience_GetHomePosition(s32 index, f32* x, f32* y, f32* z) {
	BattleAudienceMember* member;

	member = BattleAudienceGetPtr(index);
	*x = member->mHomePosition.x;
	*y = member->mHomePosition.y;
	*z = member->mHomePosition.z;
}

//@@ BattleAudience_GetRotate
void BattleAudience_GetRotate(s32 index, f32* x, f32* y, f32* z) {
	BattleAudienceMember* member;

	member = BattleAudienceGetPtr(index);
	*x = member->mRotation.x;
	*y = member->mRotation.y;
	*z = member->mRotation.z;
}

//@@ BattleAudience_SetPosition
void BattleAudience_SetPosition(s32 index, f32 x, f32 y, f32 z) {
	BattleAudienceMember* member;

	member = BattleAudienceGetPtr(index);
	member->position.x = x;
	member->position.y = y;
	member->position.z = z;
}

//@@ BattleAudience_SetRotate
void BattleAudience_SetRotate(s32 index, f32 x, f32 y, f32 z) {
	BattleAudienceMember* member;

	member = BattleAudienceGetPtr(index);
	member->mRotation.x = x;
	member->mRotation.y = y;
	member->mRotation.z = z;
}

//@@ BattleAudience_SetRotateOffset
void BattleAudience_SetRotateOffset(s32 index, f32 x, f32 y, f32 z) {
	BattleAudienceMember* member;

	member = BattleAudienceGetPtr(index);
	member->mRotationOffset.x = x;
	member->mRotationOffset.y = y;
	member->mRotationOffset.z = z;
}

//@@ BattleAudience_GetItemOn
void BattleAudience_GetItemOn(s32* memberId, f32* x, f32* y, f32* z, ItemType* itemType) {
	BattleAudience* audience;
	BattleAudienceMember* member;
	BattleAudienceItem* item;
	int i;

	audience = BattleAudienceBaseGetPtr();
	for (i = 0, member = BattleAudienceGetPtr(0); i < 200; i++, member++) {
		if ((member->flags & 1) && !(member->flags & 0x100) && !(member->flags & 2) && member->itemId != -1) {
			item = BattleAudienceItemGetPtr(member->itemId);
			if (item->state <= 4 || item->state == 7) {
				if (memberId) {
					audience->mItemOnMemberId = i;
					*memberId = i;
				}
				audience->mItemOnMemberPos.x = member->position.x;
				audience->mItemOnMemberPos.y = member->position.y;
				audience->mItemOnMemberPos.z = member->position.z + 3.0f;

				if (x) {
					*x = audience->mItemOnMemberPos.x;
				}
				if (y) {
					*y = audience->mItemOnMemberPos.y;
				}
				if (z) {
					*z = audience->mItemOnMemberPos.z;
				}

				if (itemType) {
					if (member->itemId < 0) {
						*itemType = ITEM_NULL;
					}
					else {
						*itemType = audience->items[member->itemId].mItemType;
					}
				}
				return;
			}
		}
	}
	*memberId = -1;
}

//@@ BattleAudience_GetItemOn2
void BattleAudience_GetItemOn2(s32* memberId, f32* x, f32* y, f32* z, ItemType* itemType) {
	BattleAudience* audience;
	BattleAudienceMember* member;

	audience = BattleAudienceBaseGetPtr();
	member = BattleAudienceGetPtr(audience->mItemOnMemberId);
	if (memberId) {
		*memberId = audience->mItemOnMemberId;
	}

	if (x) {
		*x = audience->mItemOnMemberPos.x;
	}
	if (y) {
		*y = audience->mItemOnMemberPos.y;
	}
	if (z) {
		*z = audience->mItemOnMemberPos.z;
	}

	if (itemType) {
		if (member->itemId < 0) {
			*itemType = ITEM_NULL;
		}
		else {
			*itemType = audience->items[member->itemId].mItemType;
		}
	}
}

//@@ BattleAudience_SetTarget
void BattleAudience_SetTarget(s32 index) {
	BattleAudienceMember* member;
	s32 i;

	BattleAudienceGetPtr(index)->flags |= 0x20;
	for (i = 0; i < 200; i++) {
		if (i != index && (u8)BattleAudience_GetExist(i)) {
			member = BattleAudienceGetPtr(i);
			if (member->status == 7) {
				BattleAudienceItemGetPtr(member->itemId)->flags = 0;
				member->itemId = -1;
				BattleAudience_ChangeStatus(i, 0);
			}
		}
	}
}

//@@ BattleAudience_Attack
void BattleAudience_Attack(s32 index) {
	BattleAudienceGetPtr(index)->flags |= 0x40;
}

//@@ BattleAudience_GetFront
BOOL BattleAudience_GetFront(s32 index) {
	BattleAudienceMember* member;
	CameraEntry* camera;
	Vec dir;

	BattleAudienceBaseGetPtr();
	member = BattleAudienceGetPtr(index);
	camera = camGetPtr(CAMERA_3D);
	dir.x = camera->cameraAt.x - camera->cameraPos.x;
	dir.y = camera->cameraAt.y - camera->cameraPos.y;
	dir.z = camera->cameraAt.z - camera->cameraPos.z;
	return !(dir.x * member->field_0x90.x + dir.y * member->field_0x90.y + dir.z * member->field_0x90.z >= 0.0f);
}

//@@ BattleAudience_ChangeStatus
void BattleAudience_ChangeStatus(s32 index, s32 status) {
	BattleAudienceMember* member;

	BattleAudienceBaseGetPtr();
	member = BattleAudienceGetPtr(index);
	if (member->flags & 1) {
		if (member->flags & 0x100) {
			if (index >= 1) {
				BattleAudience_ChangeStatus(index - 1, status);
			}
		}
		else {
			member->field_0x43 = 0;
			member->field_0x42 = 0;
			member->field_0x41 = 0;
			member->field_0x44 = 0xFF;
			member->mRotation = (Vec){0.0f, 0.0f, 0.0f};
			member->field_0x6C = (Vec){0.0f, 0.0f, 0.0f};
			member->field_0x60 = (Vec){1.0f, 1.0f, 1.0f};
			member->field_0x78 = (Vec){0.0f, 0.0f, 0.0f};
			member->field_0x30 = 0;
			member->field_0x4 = 0;
			member->field_0x8 = 0;
			member->field_0x14 = 0.0f;
			member->field_0x10 = 0.0f;
			member->field_0xC = 0.0f;
			member->status = status;
		}
	}
}

//@@ BattleAudience_GetExist
BOOL BattleAudience_GetExist(s32 index) {
	BattleAudienceMember* member;

	BattleAudienceBaseGetPtr();
	member = BattleAudienceGetPtr(index);
	if (!(member->flags & 1)) {
		return FALSE;
	}
	if (member->flags & 0x100) {
		return FALSE;
	}
	return !(member->flags & 2);
}

//@@ BattleAudience_GetSysCtrl
BOOL BattleAudience_GetSysCtrl(s32 index) {
	BattleAudienceMember* member;

	BattleAudienceBaseGetPtr();
	member = BattleAudienceGetPtr(index);
	if ((u8)BattleAudience_GetExist(index) == FALSE) {
		return FALSE;
	}
	return !(member->flags & 0x10);
}

//@@ BattleAudience_GetWaiting
BOOL BattleAudience_GetWaiting(s32 index) {
	BattleAudienceMember* member;

	BattleAudienceBaseGetPtr();
	member = BattleAudienceGetPtr(index);
	if (!(u8)BattleAudience_GetSysCtrl(index)) {
		return FALSE;
	}
	if (member->itemId != -1) {
		return FALSE;
	}
	return (u8)(member->status <= 3);
}

//@@ BattleAudience_GetEscapeChangeOK
BOOL BattleAudience_GetEscapeChangeOK(s32 index) {
	BattleAudience* audience;
	BattleAudienceMember* member;

	audience = BattleAudienceBaseGetPtr();
	member = BattleAudienceGetPtr(index);
	if (audience->flags & 0x4000) {
		return FALSE;
	}
	if (!(u8)BattleAudience_GetSysCtrl(index)) {
		return FALSE;
	}
	if (member->flags & 0x200) {
		return FALSE;
	}
	if (member->status == 13) {
		return FALSE;
	}
	if (member->status == 17) {
		return FALSE;
	}
	if (member->status == 18) {
		return FALSE;
	}
	if (member->status == 14) {
		return FALSE;
	}
	if (member->status == 15) {
		return FALSE;
	}
	if (member->status == 21) {
		return FALSE;
	}
	if (member->status == 22) {
		return FALSE;
	}
	return member->status != 12;
}

//@@ BattleAudience_GetAudienceNoFromOffset
s32 BattleAudience_GetAudienceNoFromOffset(s32 index, s32 column, s32 row) {
	s32 audienceNo;

	BattleAudience* audience = BattleAudienceBaseGetPtr();
	BattleAudienceMember* member = BattleAudienceGetPtr(index);
	if (index % 20 + column < 0 || index % 20 + column >= 20) {
		return -1;
	}

	audienceNo = column + (index - (row * 20));
	if (audienceNo < 0 || audienceNo >= 200) {
		return -1;
	}
	return audienceNo;
}

//@@ BattleAudience_HaitiRandForFallObject
s32 BattleAudience_HaitiRandForFallObject(void) {
	s32 row = irand(3);
	s32 col = 10;

	irand(12);
	switch (row) {
	case 0:
		col = irand(12) + 4;
		break;
	case 1:
		col = irand(10) + 5;
		break;
	case 2:
		col = irand(8) + 6;
		break;
	}
	return col + row * 20;
}

//@@ BattleAudience_NoUsedHaitiRand
s32 BattleAudience_NoUsedHaitiRand(void) {
	s32* haiti;
	s32 id;
	s32 j;
	s32 k;
	s32 count;
	s32 i;
	s32 list[200];
	BattleAudienceBaseGetPtr();
	haiti = haiti_data[pouchGetPtr()->rank];
	count = 0;
	for (i = 0; i < 10; i++) {
		for (j = 0, k = (20 - haiti[i]) / 2; j < haiti[i]; j++, k++) {
			id = k + i * 20;
			if (!(BattleAudienceGetPtr(id)->flags & 1) && !(BattleAudienceGetPtr(id)->flags & 0x100)) {
				list[count++] = id;
			}
		}
	}
	if (count >= 1) {
		return list[irand(count)];
	}
	return -1;
}

//@@ BattleAudience_NoUsedFCHaitiRand
s32 BattleAudience_NoUsedFCHaitiRand(void) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	s32 rank = pouchGetPtr()->rank;
	s32* haiti;
	s32 count = 0;
	s32 total = 0;
	s32 rowW[10] = { 10000, 1000, 100, 10, 5, 2, 1, 1, 1, 1 };
	s32 colW[20] = { 1, 1, 2, 2, 4, 4, 8, 8, 16, 16, 16, 16, 8, 8, 4, 4, 2, 2, 1, 1 };
	s32 list[200];
	s32 cumul[200];
	s32 i, j, k, id, w, r;

	haiti = haiti_data[rank];
	for (i = 0; i < 10; i++) {
		for (j = 0, k = (20 - haiti[i]) / 2; j < haiti[i]; j++, k++) {
			id = k + i * 20;
			if (!(BattleAudienceGetPtr(id)->flags & 1) && !(BattleAudienceGetPtr(id)->flags & 0x100)) {
				w = rowW[i] * colW[k] + 1;
				list[count] = id;
				if (count) {
					cumul[count] = w + cumul[count - 1];
				} else {
					cumul[count] = w;
				}
				total += w;
				count++;
			}
		}
	}
	r = (f32)total * (f32)rand() / 32767.0f;
	for (i = 0; i < count; i++) {
		if (r < cumul[i]) {
			return list[i];
		}
	}
	return -1;
}

//@@ BattleAudience_GetAudienceNum
s32 BattleAudience_GetAudienceNum(void) {
	return BattleAudienceBaseGetPtr()->mCurrentAudienceIntCount;
}

//@@ BattleAudience_GetPPAudienceNum
s32 BattleAudience_GetPPAudienceNum(void) {
	return BattleAudience_GetPPAudienceNum_R() + BattleAudience_GetPPAudienceNum_L();
}

//@@ BattleAudience_GetPPAudienceNumKind
s32 BattleAudience_GetPPAudienceNumKind(s32 type) {
	s32 i, count;

	BattleAudienceBaseGetPtr();
	count = 0;
	for (i = 0; i < 200; i++) {
		if (BattleAudience_GetPPAudienceNum_Sub(i) && type == BattleAudienceGetPtr(i)->type) {
			count++;
		}
	}
	return count;
}

//@@ BattleAudience_GetPPAudienceNum_R
s32 BattleAudience_GetPPAudienceNum_R(void) {
	return BattleAudience_GetPPAudienceNum_RL_Sub(10);
}

//@@ BattleAudience_GetPPAudienceNum_L
s32 BattleAudience_GetPPAudienceNum_L(void) {
	return BattleAudience_GetPPAudienceNum_RL_Sub(0);
}

//@@ BattleAudience_GetPPAudienceNum_RL_Sub
#pragma push
#pragma opt_loop_invariants off
s32 BattleAudience_GetPPAudienceNum_RL_Sub(s32 offset) {
	s32 i, j, index, count;

	BattleAudienceBaseGetPtr();
	count = 0;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			index = offset + ((i * 20) + j);
			if (BattleAudience_GetPPAudienceNum_Sub(index) == TRUE) {
				count++;
			}
		}
	}
	return count;
}
#pragma pop

//@@ BattleAudience_GetPPAudienceNum_Sub
BOOL BattleAudience_GetPPAudienceNum_Sub(s32 id) {
	BattleAudienceMember* member = BattleAudienceGetPtr(id);

	if (!AUD_U8CALL(BattleAudience_GetExist, id)) {
		return FALSE;
	}
	if (member->status >= 13 && member->status <= 13) {
		return FALSE;
	}
	if (member->status == 17) {
		return FALSE;
	}
	return member->status != 12;
}

//@@ BattleAudience_ApRecoveryBuild
void BattleAudience_ApRecoveryBuild(StarPowerInfo* info) {
	BattleWork* bw = _battleWorkPointer;
	u8* base = (u8*)BattleAudienceBaseGetPtr();
	BattleUnit* mario;
	BattleUnit* party;
	f32 pm, mm, root, b, a, cnt, sum;
	s32 i, j;

	if (*(void**)(base + 0x137C8) == NULL) {
		*(void**)(base + 0x137C8) = BattleAlloc(0xC);
	}
	memcpy(*(void**)(base + 0x137C8), info, 0xC);
	mario = BattleGetMarioPtr(bw);
	party = BattleGetPartyPtr(bw);
	sum = 0.0f;
	for (i = 0, j = 0; i < 13; i++, j += 0x20) {
		sum += *(f32*)((u8*)audience_kind + j + 0x14) * (f32)BattleAudience_GetPPAudienceNumKind(i);
	}
	root = sqrt(sum);
	a = info->mSpAcSuccessMultiplier;
	b = (f32)(u8)info->mStylishCommandMultiplier;
	cnt = 0.0f;
	if (a > 0.0f) {
		cnt += 1.0f;
	}
	if (b > 0.0f) {
		cnt += 1.0f;
	}
	if (*(u32*)((u8*)mario + 0x138) & 0x20000000) {
		mm = 3.0f;
	} else if (*(u32*)((u8*)mario + 0x138) & 0x10000000) {
		mm = 2.0f;
	} else {
		mm = 1.0f;
	}
	if (party != NULL) {
		if (*(u32*)((u8*)party + 0x138) & 0x20000000) {
			pm = 2.0f;
		} else if (*(u32*)((u8*)party + 0x138) & 0x10000000) {
			pm = 1.5f;
		} else {
			pm = 1.0f;
		}
	} else {
		pm = 1.0f;
	}
	if (BattleBreakSlot_GetBreakTurn() >= 1) {
		f32* slot = (f32*)BattleBreakSlotGetPtr();
		*(s32*)(base + 0x137C4) += (s32)(pm * (mm * (cnt * (1.0f * (f32)(f64)root * (a + b)))) * slot[5]);
	} else {
		*(s32*)(base + 0x137C4) += (s32)(pm * (mm * (cnt * (1.0f * (f32)(f64)root * (a + b)))));
	}
	if (irand(100) < ((u8*)info)[0xA]) {
		BattleBreakSlot_PointInc();
	}
}

//@@ BattleAudience_WinSetActive
void BattleAudience_WinSetActive(u8 active) {
	BattleAudienceWinGetPtr()->mActive = active;
}

//@@ BattleAudienceNumToTarget
void BattleAudienceNumToTarget(void) {
	s32 num;
	BattleAudience* audience = BattleAudienceBaseGetPtr();

	if (audience->flags & 0x40000) {
		return;
	}
	num = audience->mTargetAudienceCount + audience->mAddedAudienceCount;
	if (num < 0) {
		num = 0;
	}
	if (num > audience->mMaxAudience) {
		num = audience->mMaxAudience;
	}
	BattleAudienceAddAudienceNum(num - BattleAudienceNumToTargetSub());
}

//@@ BattleAudienceNumToTargetSub
s32 BattleAudienceNumToTargetSub(void) {
	s32 i, count;

	BattleAudienceBaseGetPtr();
	count = 0;
	for (i = 0; i < 200; i++) {
		if (AUD_U8CALL(BattleAudience_GetExist, i) == TRUE && BattleAudienceGetPtr(i)->status != 12) {
			count++;
		}
	}
	return count;
}

//@@ BattleAudienceAddTargetNum
void BattleAudienceAddTargetNum(f32 value, f32 value2) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();

	audience->mAddedAudienceCount += value2;
	if (audience->mAddedAudienceCount > 0.0f && value < 0.0f) {
		audience->mAddedAudienceCount += value;
		if (audience->mAddedAudienceCount < 0.0f) {
			value = audience->mAddedAudienceCount;
			audience->mAddedAudienceCount = 0.0f;
		} else {
			value = 0.0f;
		}
	} else if (audience->mAddedAudienceCount < 0.0f && value > 0.0f) {
		audience->mAddedAudienceCount += value;
		if (audience->mAddedAudienceCount > 0.0f) {
			value = audience->mAddedAudienceCount;
			audience->mAddedAudienceCount = 0.0f;
		} else {
			value = 0.0f;
		}
	}
	BattleAudienceAddTargetNumSub(value);
	if (audience->mTargetAudienceCount < 0.0f) {
		audience->mTargetAudienceCount = 0.0f;
	}
	if (audience->mTargetAudienceCount > audience->mMaxAudience) {
		audience->mTargetAudienceCount = audience->mMaxAudience;
	}
	if (audience->mAddedAudienceCount < -1000.0f) {
		audience->mAddedAudienceCount = -1000.0f;
	}
	if (audience->mAddedAudienceCount > 1000.0f) {
		audience->mAddedAudienceCount = 1000.0f;
	}
}

//@@ BattleAudienceAddTargetNumSub
void BattleAudienceAddTargetNumSub(f32 value) {
	f32 subtract;
	s32 skew;

	BattleAudience* audience = BattleAudienceBaseGetPtr();
	while (1) {
		if (value == 0.0f) {
			return;
		}
		if (value > 0.0f) {
			subtract = value < 1.0f ? value : 1.0f;
			value -= subtract;
			if (value < 0.0f) {
				value = 0.0f;
			}
		}
		if (value < 0.0f) {
			subtract = value > -1.0f ? value : -1.0f;
			value -= subtract;
			if (value > 0.0f) {
				value = 0.0f;
			}
		}
		if (subtract > 0.0f) {
			skew = (s32)(((audience->mTargetAudienceCount / audience->mAudienceDeltaMultiplier) - 1.0f) / 0.25f);
			if (skew >= 1) {
				audience->mTargetAudienceCount += subtract / (skew + 1);
				continue;
			}
		}
		if (subtract < 0.0f) {
			skew = (s32)(((audience->mTargetAudienceCount / audience->mAudienceDeltaMultiplier) - 1.0f) / 0.25f);
			if (skew <= -1) {
				audience->mTargetAudienceCount -= subtract / (skew - 1);
				continue;
			}
		}
		audience->mTargetAudienceCount += subtract;
	}
}

//@@ BattleAudienceAddAudienceNum
s32 BattleAudienceAddAudienceNum(s32 num) {
	s32 total;
	s32 list[200];
	BattleWork* wp;
	AudPhaseEvt* audience;
	s32 i, j, r, sum, id, count;
	u8 type;
	s32 added;

	wp = _battleWorkPointer;
	audience = (AudPhaseEvt*)BattleAudienceBaseGetPtr();
	total = 0;
	added = 0;
	if (*(u16*)&pouchGetPtr()->mStarPowersObtained == 0) {
		return 0;
	}
	if (num == 0) {
		return 0;
	}
	if (wp->flags & 0x100) {
		return 0;
	}
	if (num > 0) {
		for (i = 0; i < 12; i++) {
			total += audience->weights[i];
		}
		for (i = 0; i < num; i++) {
			sum = 0;
			r = irand(total);
			for (j = 0; j < 12; j++) {
				sum += audience->weights[j];
				if (r < sum) {
					type = j;
					break;
				}
			}
			id = BattleAudience_NoUsedFCHaitiRand();
			if (id == -1) {
				break;
			}
			if (BattleAudience_Entry(id, type, 11) == TRUE) {
				added++;
				BattleAudienceGetPtr(id)->field_0x8 = added;
			}
		}
	} else {
		for (i = 0; i > num; i--) {
			count = 0;
			for (j = 0; j < 200; j++) {
				if (AUD_U8CALL(BattleAudience_GetEscapeChangeOK, j)) {
					list[count++] = j;
				}
			}
			if (count >= 1) {
				id = list[irand(count)];
				BattleAudience_ChangeStatus(id, 12);
				added--;
				BattleAudienceGetPtr(id)->field_0x8 = -added;
			}
		}
	}
	return added;
}

//@@ BattleAudiencePuniAllEscape
void BattleAudiencePuniAllEscape(void) {
	BattleAudienceMember* member;
	BattleAudience* audience;
	s32 i;
	s32 count;

	audience = BattleAudienceBaseGetPtr();
	count = 0;
	for (i = 0; i < 200; i++) {
		member = BattleAudienceGetPtr(i);
		if (AUD_U8CALL(BattleAudience_GetEscapeChangeOK, i) && member->type == 7) {
			BattleAudience_ChangeStatus(i, 12);
			audience->mAddedAudienceCount -= 1.0f;
			count++;
		}
	}
	if (count >= 1) {
		audience->flags |= 0x8000;
	}
}

//@@ BattleAudienceAddPuni
void BattleAudienceAddPuni(s32 num) {
	BattleAudience* audience;
	BattleWork* wp = _battleWorkPointer;
	s32 i;

	audience = BattleAudienceBaseGetPtr();
	if (*(u16*)&pouchGetPtr()->mStarPowersObtained != 0 && ((AudPhaseEvt*)audience)->weights[7] > 0 && num > 0 && !(wp->flags & 0x100)) {
		for (i = 0; i < num; i++) {
			s32 id = BattleAudience_NoUsedFCHaitiRand();
			if (id == -1) {
				return;
			}
			if (BattleAudience_Entry(id, 7, 11) == TRUE) {
				audience->mAddedAudienceCount += 1.0f;
			}
		}
	}
}

//@@ BattleAudienceAddPhaseEvtList
void BattleAudienceAddPhaseEvtList(s32 type) {
	s32 i;
	AudPhaseEvt* p = (AudPhaseEvt*)BattleAudienceBaseGetPtr();

	for (i = 0; i < p->count; i++) {
		if (p->list[i] == type) {
			return;
		}
	}
	p->list[p->count] = type;
	p->count++;
}

//@@ BattleAudienceCheer
void BattleAudienceCheer(s32 type) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();

	if (audience->field_137C4 > 800) {
		audience->field_137C4 = 800;
	}
	if (audience->field_137C4 > 0) {
		if (pouchGetPtr()->maximumSP == 0) {
			audience->field_137C4 = 0;
		} else {
			audience->flags |= 2;
		}
		BattleAudienceJoy(type);
		if (audience->field_137C4 != 0) {
			BattleStatusWindowAPRecoveryOn();
		}
	}
}

//@@ BattleAudienceJoy
void BattleAudienceJoy(s32 type) {
	AudPhaseEvt* audience = (AudPhaseEvt*)BattleAudienceBaseGetPtr();

	switch (type) {
	case 0:
		BattleAudienceJoy_Sub(100, 0, 0, type);
		break;
	case 1:
		BattleAudienceJoy_Sub(0, 100, 0, type);
		break;
	case 2:
		BattleAudienceJoy_Sub(70, 30, 0, type);
		break;
	case 3:
		switch (audience->joyLevel) {
		case 0:
			BattleAudienceJoy_Sub(50, 40, 10, type);
			break;
		case 1:
			BattleAudienceJoy_Sub(40, 40, 20, type);
			break;
		case 2:
			BattleAudienceJoy_Sub(30, 40, 30, type);
			break;
		case 3:
			BattleAudienceJoy_Sub(20, 40, 40, type);
			break;
		case 4:
			BattleAudienceJoy_Sub(10, 40, 50, type);
			break;
		default:
			BattleAudienceJoy_Sub(50, 40, 10, type);
			break;
		}
		audience->joyLevel++;
		if (audience->joyLevel > 4) {
			audience->joyLevel = 4;
		}
		break;
	}
}

//@@ BattleAudienceJoySACLecture
void BattleAudienceJoySACLecture(void) {
	BattleAudienceSoundCheer(120, 60);
	BattleAudienceJoy(2);
}

//@@ BattleAudienceJoyEnding
void BattleAudienceJoyEnding(void) {
	BattleAudienceJoy(3);
}

//@@ BattleAudienceJoy_Sub
#pragma push
#pragma opt_loop_invariants off
void BattleAudienceJoy_Sub(s32 a, s32 b, s32 c, s32 type) {
	BattleAudienceMember* member;
	s32 i;
	s32 total;
	s32 r;

	BattleAudienceBaseGetPtr();
	total = b + c;
	total += a;
	for (i = 0, member = BattleAudienceGetPtr(0); i < 200; i++, member++) {
		if (!AUD_U8CALL(BattleAudience_GetWaiting, i)) {
			continue;
		}
		if (member->type == 11) {
			BattleAudience_ChangeStatus(i, 4);
			if (type == 3) {
				member->field_0xC = 3.0f;
			} else {
				member->field_0xC = 2.0f;
			}
		} else {
			r = irand(total);
			if (r < a) {
				BattleAudience_ChangeStatus(i, 4);
				if (type == 3) {
					member->field_0xC = 3.0f;
				} else {
					member->field_0xC = 2.0f;
				}
			} else if (r < a + b) {
				BattleAudience_ChangeStatus(i, 5);
			} else if (r < c + (a + b)) {
				BattleAudience_ChangeStatus(i, 6);
			}
		}
	}
}

#pragma pop

//@@ BattleAudienceDetectPakkunEatTargetSub2
s32 BattleAudienceDetectPakkunEatTargetSub2(s32 index, s32 dir) {
	s32 id;

	BattleAudienceBaseGetPtr();
	id = BattleAudience_GetAudienceNoFromOffset(index, dir, 0);
	if (id == -1) {
		return -1;
	}
	BattleAudienceGetPtr(id);
	if (AUD_U8CALL(BattleAudience_GetSysCtrl, id) == TRUE) {
		return id;
	}
	return -1;
}

//@@ BattleAudienceDetectPakkunEatTargetSub
s32 BattleAudienceDetectPakkunEatTargetSub(s32 index, s32 dir1, s32 dir2) {
	s32 a = BattleAudienceDetectPakkunEatTargetSub2(index, dir1);
	s32 b = BattleAudienceDetectPakkunEatTargetSub2(index, dir2);

	if (a != -1) {
		return a;
	}
	if (b != -1) {
		return b;
	}
	return -1;
}

//@@ BattleAudienceDetectPakkunEatTarget
s32 BattleAudienceDetectPakkunEatTarget(s32 index) {
	if (irand(2) == 0) {
		return BattleAudienceDetectPakkunEatTargetSub(index, -1, 1);
	}
	return BattleAudienceDetectPakkunEatTargetSub(index, 1, -1);
}

//@@ BattleAudienceSoundBooing
void BattleAudienceSoundBooing(void) {
	s32 kind;
	s32 num;

	BattleAudienceBaseGetPtr();
	kind = 0;
	num = BattleAudience_GetPPAudienceNum_R() + BattleAudience_GetPPAudienceNum_L();
	if (num >= 0 && num <= 49) {
		kind = 1;
	}
	if (num >= 50 && num <= 99) {
		kind = 2;
	}
	if (num >= 100 && num <= 149) {
		kind = 3;
	}
	if (num >= 150) {
		kind = 4;
	}
	BattleAudienceSoundBooingKind(kind);
}

//@@ BattleAudienceSoundBooingKind
void BattleAudienceSoundBooingKind(s32 kind) {
	char name[64];
	AudSound* sound;
	s32 right, left;

	BattleAudienceBaseGetPtr();
	sound = AudSoundGetPtr(0);
	right = BattleAudience_GetPPAudienceNum_R();
	left = BattleAudience_GetPPAudienceNum_L();
	BattleAudienceSoundStop(0);
	if (kind == 1) {
		strcpy(name, "SFX_AUDIENCE_BOO_ALLY1");
		sound->kind = 1;
	}
	if (kind == 2) {
		strcpy(name, "SFX_AUDIENCE_BOO_ALLY2");
		sound->kind = 2;
	}
	if (kind == 3) {
		strcpy(name, "SFX_AUDIENCE_BOO_ALLY3");
		sound->kind = 3;
	}
	if (kind == 4) {
		strcpy(name, "SFX_AUDIENCE_BOO_ALLY4");
		sound->kind = 4;
	}
	if (kind == 5) {
		strcpy(name, "SFX_AUDIENCE_BOO_ENEMY1");
		sound->kind = 5;
	}
	if (kind == 6) {
		strcpy(name, "SFX_AUDIENCE_BOO_ENEMY2");
		sound->kind = 6;
	}
	if (kind == 7) {
		strcpy(name, "SFX_AUDIENCE_BOO_ENEMY3");
		sound->kind = 7;
	}
	if (kind == 8) {
		strcpy(name, "SFX_AUDIENCE_BOO_ENEMY4");
		sound->kind = 8;
	}
	sound->sfxId = BattleAudienceSound1(name, right, left);
	AUD_SOUND_START(sound, -1, 0);
}

//@@ BattleAudienceSoundClap
void BattleAudienceSoundClap(s32 duration, s32 fade) {
	char name[64];
	AudSound* sound;
	s32 right, left, sum;

	BattleAudienceBaseGetPtr();
	sound = AudSoundGetPtr(1);
	right = BattleAudience_GetPPAudienceNum_R();
	left = BattleAudience_GetPPAudienceNum_L();
	sum = right + left;
	BattleAudienceSoundStop(1);
	if (sum >= 1 && sum <= 49) {
		strcpy(name, "SFX_AUDIENCE_CLAPPING1");
		sound->kind = 1;
	}
	if (sum >= 50 && sum <= 99) {
		strcpy(name, "SFX_AUDIENCE_CLAPPING2");
		sound->kind = 2;
	}
	if (sum >= 100 && sum <= 149) {
		strcpy(name, "SFX_AUDIENCE_CLAPPING3");
		sound->kind = 3;
	}
	if (sum >= 150) {
		strcpy(name, "SFX_AUDIENCE_CLAPPING4");
		sound->kind = 4;
	}
	sound->sfxId = BattleAudienceSound1(name, right, left);
	AUD_SOUND_START(sound, duration + fade, fade);
}

//@@ BattleAudienceSoundNoiseAlways
void BattleAudienceSoundNoiseAlways(void) {
	char name[64];
	BattleAudience* audience;
	AudSound* sound;
	s32 right, left, sum;

	audience = BattleAudienceBaseGetPtr();
	sound = AudSoundGetPtr(2);
	right = BattleAudience_GetPPAudienceNum_R();
	left = BattleAudience_GetPPAudienceNum_L();
	sum = right + left;
	if (!(sound->flags & 1)) {
		if (sum == 0) {
			sound->kind = 0;
		}
		if (sum >= 1 && sum <= 49) {
			strcpy(name, "SFX_AUDIENCE_NOISY1");
			sound->kind = 1;
		}
		if (sum >= 50 && sum <= 99) {
			strcpy(name, "SFX_AUDIENCE_NOISY2");
			sound->kind = 2;
		}
		if (sum >= 100 && sum <= 149) {
			strcpy(name, "SFX_AUDIENCE_NOISY3");
			sound->kind = 3;
		}
		if (sum >= 150) {
			strcpy(name, "SFX_AUDIENCE_NOISY4");
			sound->kind = 4;
		}
		sound->sfxId = BattleAudienceSound1(name, right, left);
		if (sound->sfxId != -1) {
			sound->flags |= 1;
			sound->duration = -1;
			sound->mFadeoutTime = 0;
			sound->mBaseSfxVolume = sound->mCurrentBaseSfxVolume = psndSFX_get_vol(sound->sfxId);
			sound->mForceFadeLength = 0;
			sound->mForceFadeTimer = 0;
			sound->mVolumeMultiplier = 100;
			audience->flags |= 0x2000;
		}
	}
}

//@@ BattleAudienceSoundCheer
void BattleAudienceSoundCheer(s32 duration, s32 fade) {
	s32 kind;
	s32 num;

	BattleAudienceBaseGetPtr();
	kind = 0;
	num = BattleAudience_GetPPAudienceNum_R() + BattleAudience_GetPPAudienceNum_L();
	if (num >= 1 && num <= 49) {
		kind = 1;
	}
	if (num >= 50 && num <= 99) {
		kind = 2;
	}
	if (num >= 100 && num <= 149) {
		kind = 3;
	}
	if (num >= 150) {
		kind = 4;
	}
	BattleAudienceSoundCheerKind(kind, duration, fade);
}

//@@ BattleAudienceSoundCheerKind
void BattleAudienceSoundCheerKind(s32 kind, s32 duration, s32 fade) {
	char name[64];
	AudSound* sound;
	AudSound* sound5;
	s32 right, left;
	s32 lowPitch;

	BattleAudienceBaseGetPtr();
	lowPitch = 0;
	right = BattleAudience_GetPPAudienceNum_R();
	left = BattleAudience_GetPPAudienceNum_L();
	sound = AudSoundGetPtr(4);
	sound5 = AudSoundGetPtr(5);
	if ((sound->flags & 1) && (sound5->flags & 1)) {
		if (sound->duration <= sound5->duration) {
			BattleAudienceSoundStop(4);
			sound = AudSoundGetPtr(4);
		}
		else {
			BattleAudienceSoundStop(5);
			sound = AudSoundGetPtr(5);
		}
	}
	else if (sound->flags & 1) {
		sound = AudSoundGetPtr(5);
		lowPitch = 1;
	}
	else if (sound5->flags & 1) {
		sound = AudSoundGetPtr(4);
		lowPitch = 1;
	}
	else {
		sound = AudSoundGetPtr(4);
	}
	if (kind == 1) {
		strcpy(name, "SFX_AUDIENCE_CHEER_ALLY1");
		sound->kind = 1;
	}
	if (kind == 2) {
		strcpy(name, "SFX_AUDIENCE_CHEER_ALLY2");
		sound->kind = 2;
	}
	if (kind == 3) {
		strcpy(name, "SFX_AUDIENCE_CHEER_ALLY3");
		sound->kind = 3;
	}
	if (kind == 4) {
		strcpy(name, "SFX_AUDIENCE_CHEER_ALLY4");
		sound->kind = 4;
	}
	if (lowPitch == 1) {
		sound->sfxId = BattleAudienceSound1(name, right, left);
		psndSFX_pit(sound->sfxId, 0x7F);
	}
	else {
		sound->sfxId = BattleAudienceSound1(name, right, left);
	}
	AUD_SOUND_START(sound, duration + fade, fade);
}

//@@ BattleAudienceSoundWhistle
void BattleAudienceSoundWhistle(void) {
	BattleAudienceSoundWhistleKind(irand(3) + 1);
}

//@@ BattleAudienceSoundWhistleKind
void BattleAudienceSoundWhistleKind(s32 kind) {
	Vec pos;
	s32 id, idx;
	s32 list[200];
	s32 i;
	s32 count;
	AudSound* sound;

	count = 0;
	for (i = 0; i < 200; i++) {
		if ((u8)BattleAudience_GetWaiting(i) == TRUE) {
			list[count] = i;
			count++;
		}
	}
	if (count != 0) {
		idx = list[irand(count)];
		BattleAudienceSoundGetInfo2(idx, &pos);
		if (pos.x <= 0.0f) {
			id = 6;
		}
		else {
			id = 7;
		}
		sound = AudSoundGetPtr(id);
		BattleAudienceSoundStop(id);
		switch (kind) {
			case 1:
				sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_WHISTLE1", idx);
				break;
			case 2:
				sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_WHISTLE2", idx);
				break;
			case 3:
				sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_WHISTLE3", idx);
				break;
		}
		AUD_SOUND_START(sound, -1, 0);
	}
}

//@@ BattleAudienceSoundCallKind
void BattleAudienceSoundCallKind(s32 kind) {
	AudSound* sound;
	s32 right, left;

	BattleAudienceBaseGetPtr();
	sound = AudSoundGetPtr(8);
	right = BattleAudience_GetPPAudienceNum_R();
	left = BattleAudience_GetPPAudienceNum_L();
	BattleAudienceSoundStop(8);
	switch (kind) {
		case 1:
			sound->sfxId = BattleAudienceSound1("SFX_AUDIENCE_CALL_ALLY1", right, left);
			break;
		case 2:
			sound->sfxId = BattleAudienceSound1("SFX_AUDIENCE_CALL_ALLY2", right, left);
			break;
	}
	AUD_SOUND_START(sound, -1, 0);
}

//@@ BattleAudienceSoundHandBeat
void BattleAudienceSoundHandBeat(void) {
	s32 right;
	AudSound* sound;
	s32 left;
	s32 sum;

	BattleAudienceBaseGetPtr();
	sound = AudSoundGetPtr(9);
	right = BattleAudience_GetPPAudienceNum_R();
	left = BattleAudience_GetPPAudienceNum_L();
	sum = right + left;
	BattleAudienceSoundStop(9);
	sound->sfxId = BattleAudienceSound1("SFX_AUDIENCE_HANDBEAT1", right, left);
	if (sound->sfxId != -1) {
		sound->flags |= 1;
		sound->duration = -1;
		right = 0;
		sound->mFadeoutTime = right;
		sound->mForceFadeLength = right;
		sound->mForceFadeTimer = right;
		if (sum == 0) {
			right = 0;
		}
		else {
			right = 75.0f + sum * (26.0f + irand(26)) / 200.0f;
		}
		psndSFX_vol(sound->sfxId, right);
		sound->mCurrentBaseSfxVolume = right;
		sound->mBaseSfxVolume = right;
		sound->mVolumeMultiplier = 100;
	}
}

//@@ BattleAudienceSoundItemThrow
void BattleAudienceSoundItemThrow(s32 kind, s32 index) {
	Vec pos;
	s32 id;
	AudSound* sound;

	BattleAudienceSoundGetInfo2(index, &pos);
	if (pos.x <= 0.0f) {
		id = 10;
	}
	else {
		id = 11;
	}
	sound = AudSoundGetPtr(id);
	BattleAudienceSoundStop(id);
	switch (kind) {
		case 0:
			sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_THROW_OBJECT1", index);
			break;
		default:
			sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_THROW_OBJECT2", index);
			break;
	}
	AUD_SOUND_START(sound, -1, 0);
}

//@@ BattleAudienceSoundRun
void BattleAudienceSoundRun(s32 kind) {
	AudSound* sound = AudSoundGetPtr(13);

	BattleAudienceSoundStop(13);
	switch (kind) {
		case 0:
			sound->sfxId = BattleAudienceSound0("SFX_AUDIENCE_RUN1");
			break;
		case 1:
			sound->sfxId = BattleAudienceSound0("SFX_AUDIENCE_RUN2");
			break;
	}
	AUD_SOUND_START(sound, -1, 0);
}

//@@ BattleAudienceSoundSleep
void BattleAudienceSoundSleep(s32 index) {
	Vec pos;
	s32 id;
	AudSound* sound;

	BattleAudienceSoundGetInfo2(index, &pos);
	if (pos.x <= 0.0f) {
		id = 14;
	}
	else {
		id = 15;
	}
	sound = AudSoundGetPtr(id);
	BattleAudienceSoundStop(id);
	switch (irand(3)) {
		case 0:
			sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_SLEEP1", index);
			break;
		case 1:
			sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_SLEEP2", index);
			break;
		case 2:
			sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_SLEEP3", index);
			break;
	}
	AUD_SOUND_START(sound, -1, 0);
}

//@@ BattleAudienceSoundZZZ
void BattleAudienceSoundZZZ(s32 index) {
	AudSound* sound = AudSoundGetPtr(16);

	BattleAudienceSoundStop(16);
	BattleAudienceSound2("SFX_AUDIENCE_ZZZ1", index);
	AUD_SOUND_START(sound, -1, 0);
}

//@@ BattleAudienceSoundSing
void BattleAudienceSoundSing(s32 index) {
	AudSound* sound = AudSoundGetPtr(17);

	BattleAudienceSoundStop(17);
	sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_PANSY_SINGING1", index);
	AUD_SOUND_START(sound, -1, 0);
}

//@@ BattleAudienceSoundShell
void BattleAudienceSoundShell(s32 index) {
	Vec pos;
	s32 id;
	AudSound* sound;

	BattleAudienceSoundGetInfo2(index, &pos);
	if (pos.x <= 0.0f) {
		id = 18;
	}
	else {
		id = 19;
	}
	sound = AudSoundGetPtr(id);
	BattleAudienceSoundStop(id);
	sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_SHELL_TRANSFORM1", index);
	AUD_SOUND_START(sound, -1, 0);
}

//@@ BattleAudienceSoundBombIgnite
void BattleAudienceSoundBombIgnite(s32 index, s32 duration, s32 fade) {
	AudSound* sound = AudSoundGetPtr(20);

	BattleAudienceSoundStop(20);
	sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_BOMB_READY1", index);
	AUD_SOUND_START(sound, duration + fade, fade);
}

//@@ BattleAudienceSoundBombFire
void BattleAudienceSoundBombFire(s32 index) {
	Vec pos;
	s32 id;
	AudSound* sound;

	BattleAudienceSoundGetInfo2(index, &pos);
	if (pos.x <= 0.0f) {
		id = 21;
	}
	else {
		id = 22;
	}
	sound = AudSoundGetPtr(id);
	BattleAudienceSoundStop(id);
	sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_BOMB_BURST1", index);
	AUD_SOUND_START(sound, -1, 0);
}

//@@ BattleAudienceSoundPakkunEat
void BattleAudienceSoundPakkunEat(s32 index) {
	AudSound* sound = AudSoundGetPtr(23);

	BattleAudienceSoundStop(23);
	sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_PAKU_EAT1", index);
	AUD_SOUND_START(sound, -1, 0);
}

//@@ BattleAudienceSoundSetVol
void BattleAudienceSoundSetVol(s32 index, u8 a2, s32 a3) {
	BattleAudienceSound* sound;

	sound = BattleAudienceSoundGetPtr(index);
	sound->mFadeStartVolumeMultiplier = sound->mVolumeMultiplier;
	sound->mFadeEndVolumeMultiplier = a2;
	sound->mForceFadeTimer = 0;
	sound->mForceFadeLength = a3;
	sound->mFadeoutTime = 0;
}

//@@ BattleAudienceSoundSetVolAll
void BattleAudienceSoundSetVolAll(u8 vol, s32 length) {
	s32 i;

	for (i = 0; i < 24; i++) {
		BattleAudienceSoundSetVol(i, vol, length);
	}
}

//@@ BattleAudienceSoundCheck
u32 BattleAudienceSoundCheck(s32 index) {
	return AudSoundGetPtr(index)->flags & 1;
}

//@@ BattleAudienceSoundStop
void BattleAudienceSoundStop(s32 index) {
	AudSound* sound = AudSoundGetPtr(index);

	if (sound->flags & 1) {
		psndSFXOff(sound->sfxId);
		sound->flags &= ~1;
	}
}

//@@ BattleAudienceSound0
s32 BattleAudienceSound0(const char* name) {
	return ((s32 (*)(const char*))psndSFXOn)(name);
}

//@@ BattleAudienceSound1
s32 BattleAudienceSound1(const char* name, s32 right, s32 left) {
	u8 vol;
	Vec pos;
	s32 id;

	BattleAudienceSoundGetInfo1(right, left, &vol, &pos);
	id = psndSFXOn_3D(name, &pos);
	psndSFX_vol(id, vol);
	return id;
}

//@@ BattleAudienceSoundGetInfo1
void BattleAudienceSoundGetInfo1(s32 right, s32 left, u8* vol, Vec* pos) {
	s32 sum = right + left;

	if (sum == 0) {
		*vol = 0;
	}
	else {
		*vol = 100.0f + 26.0f * sum / 200.0f;
	}
	if (left == 0 || sum == 0) {
		pos->x = 250.0f;
	}
	else {
		pos->x = (u8)(250.0f * (right - left) / sum);
	}
	pos->y = 0.0f;
	pos->z = 0.0f;
}

//@@ BattleAudienceSound2
s32 BattleAudienceSound2(const char* name, s32 index) {
	Vec pos;

	BattleAudienceSoundGetInfo2(index, &pos);
	return psndSFXOn_3D(name, &pos);
}

//@@ BattleAudienceSoundGetInfo2
void BattleAudienceSoundGetInfo2(s32 index, Vec* pos) {
	BattleAudienceMember* member = BattleAudienceGetPtr(index);

	pos->x = member->position.x;
	pos->y = member->position.y;
	pos->z = member->position.z;
}

//@@ BattleAudienceSoundMain
void BattleAudienceSoundMain(void) {
	AudSound* sound;
	s32 i;

	BattleAudienceBaseGetPtr();
	BattleAudienceNoiseMain();
	for (i = 0, sound = AudSoundGetPtr(0); i < 24; i++, sound++) {
		if (psndSFXChk(sound->sfxId) == -1) {
			sound->flags &= ~1;
			continue;
		}
		if (sound->duration == 0) {
			psndSFXOff(sound->sfxId);
			sound->flags &= ~1;
			continue;
		}
		if (sound->mForceFadeLength > 0) {
			sound->mForceFadeTimer++;
			sound->mVolumeMultiplier = intplGetValue(0, sound->mForceFadeTimer, sound->mForceFadeLength,
			                                         sound->mFadeStartVolumeMultiplier, sound->mFadeEndVolumeMultiplier);
			psndSFX_vol(sound->sfxId, (u8)(sound->mCurrentBaseSfxVolume * sound->mVolumeMultiplier / 100));
			if (sound->mForceFadeTimer >= sound->mForceFadeLength) {
				sound->mForceFadeLength = 0;
			}
		}
		if (sound->duration > 0) {
			if (sound->duration == sound->mFadeoutTime) {
				sound->mFadeStartVolumeMultiplier = sound->mVolumeMultiplier;
				sound->mFadeEndVolumeMultiplier = 0;
			}
			if (sound->duration <= sound->mFadeoutTime) {
				sound->mVolumeMultiplier = intplGetValue(0, sound->mFadeoutTime - sound->duration, sound->mFadeoutTime,
				                                         sound->mFadeStartVolumeMultiplier, sound->mFadeEndVolumeMultiplier);
				psndSFX_vol(sound->sfxId, (u8)(sound->mCurrentBaseSfxVolume * sound->mVolumeMultiplier / 100));
			}
			sound->duration--;
		}
	}
}

//@@ BattleAudienceNoiseMain
void BattleAudienceNoiseMain(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	AudSound* sound = AudSoundGetPtr(2);
	s32 num = BattleAudience_GetPPAudienceNum();

	if (!(audience->flags & 0x10000) && (wp->flags & 0x80)) {
		BattleAudienceSoundSetVol(2, 60, 80);
	}
	if ((audience->flags & 0x10000) && !(wp->flags & 0x80)) {
		BattleAudienceSoundSetVol(2, 0, 80);
	}
	if (num == 0 && sound->kind != 0) {
		psndSFXOff(sound->sfxId);
		sound->kind = 0;
	}
	if (num >= 1 && num <= 49 && sound->kind != 1) {
		BattleAudienceSoundNoiseAlways();
		sound->kind = 1;
	}
	if (num >= 50 && num <= 99 && sound->kind != 2) {
		BattleAudienceSoundNoiseAlways();
		sound->kind = 2;
	}
	if (num >= 100 && num <= 149 && sound->kind != 3) {
		BattleAudienceSoundNoiseAlways();
		sound->kind = 3;
	}
	if (num >= 150 && num <= 200 && sound->kind != 4) {
		BattleAudienceSoundNoiseAlways();
		sound->kind = 4;
	}
	if (!(audience->flags & 0x2000)) {
		sound->mCurrentBaseSfxVolume = 0;
	}
	else if (num == 0) {
		sound->mCurrentBaseSfxVolume = 0;
	}
	else {
		sound->mCurrentBaseSfxVolume = 63.0f + 63.0f * num / 200.0f;
	}
}

//@@ BattleAudience_Case_KillEnemy
void BattleAudience_Case_KillEnemy(void) {
	BattleAudienceBaseGetPtr()->flags |= 0x1000;
}

//@@ BattleAudience_Case_ActionCommandGood
void BattleAudience_Case_ActionCommandGood(void) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	s32 i;
	s32 count = 0;

	for (i = 0; i < 200; i++) {
		if ((u8)BattleAudience_GetWaiting(i) == TRUE) {
			count++;
		}
	}
	if (count != 0) {
		BattleAudienceSoundCheer(180, 120);
		BattleAudienceJoy(0);
	}
	audience->flags |= 0x10;
}

//@@ BattleAudience_Case_ActionCommandBad
void BattleAudience_Case_ActionCommandBad(BattleWeapon* weapon) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	s32 count = 0;
	s32 i;

	for (i = 0; i < 200; i++) {
		if ((u8)BattleAudience_GetWaiting(i) == TRUE) {
			count++;
		}
	}
	if (count != 0) {
		BattleAudienceSoundBooing();
		BattleAudienceJoy(0);
		if (weapon->hpDamageFn == weaponGetPowerFromMarioHammerLv) {
			BattleAudienceAddPhaseEvtList(7);
		}
	}
	audience->flags |= 0x20;
}

//@@ BattleAudience_Case_GuardGood
void BattleAudience_Case_GuardGood(void) {
	BattleAudienceBaseGetPtr()->flags |= 0x40;
}

//@@ BattleAudience_Case_GuardBad
void BattleAudience_Case_GuardBad(void) {
	BattleAudienceBaseGetPtr()->flags |= 0x80;
}

//@@ BattleAudience_Case_AcrobatGood
void BattleAudience_Case_AcrobatGood(void) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	s32 count = 0;
	s32 i;

	for (i = 0; i < 200; i++) {
		if ((u8)BattleAudience_GetWaiting(i) == TRUE) {
			count++;
		}
	}
	if (count >= 1) {
		BattleAudienceSoundCheer(180, 120);
		BattleAudienceSoundClap(180, 120);
		BattleAudienceJoy(1);
	}
	audience->mNumStylishCommandsThisAttack++;
	if (audience->mNumStylishCommandsThisAttack > 5) {
		audience->mNumStylishCommandsThisAttack = 5;
	}
	audience->flags |= 0x100;
}

//@@ BattleAudience_Case_AcrobatBad
void BattleAudience_Case_AcrobatBad(void) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	s32 count = 0;
	s32 i;

	for (i = 0; i < 200; i++) {
		if ((u8)BattleAudience_GetWaiting(i) == TRUE) {
			count++;
		}
	}
	if (count >= 1) {
		BattleAudienceSoundBooing();
		BattleAudienceJoy(0);
	}
	audience->flags |= 0x200;
}

//@@ BattleAudience_Case_AcrobatNoTry
void BattleAudience_Case_AcrobatNoTry(void) {
	BattleAudienceBaseGetPtr();
}

//@@ BattleAudience_Case_MarioBigDamage
void BattleAudience_Case_MarioBigDamage(void) {
	BattleAudienceBaseGetPtr();
}

//@@ BattleAudience_Case_MarioPinch
void BattleAudience_Case_MarioPinch(void) {
	BattleAudienceAddTargetNum(0.049999997f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
}

//@@ BattleAudience_Case_MarioDanger
void BattleAudience_Case_MarioDanger(void) {
	BattleAudienceAddTargetNum(0.14999999f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
}

//@@ BattleAudience_Case_PartyDown
void BattleAudience_Case_PartyDown(void) {
	BattleAudienceAddTargetNum(-0.25f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
}

//@@ BattleAudience_Case_JumpNewRecord
void BattleAudience_Case_JumpNewRecord(void) {
}

//@@ BattleAudience_Case_FinalAttack
void BattleAudience_Case_FinalAttack(void) {
}

//@@ BattleAudience_Case_TurnEnd
void BattleAudience_Case_TurnEnd(void) {
	BattleWork* wp = _battleWorkPointer;
	BattleUnit* mario = BattleGetMarioPtr(wp);
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	s32 i, sum, turns;
	BattleGroupSetup* group;
	BattleUnitSetup* setup;

	pouchGetPtr();
	sum = 0;
	group = wp->fbatInfo->setup->groupSetup;
	setup = group->enemyData;
	if (!(audience->flags & 0x40000)) {
		audience->mTurnEndPhaseEventChance += 3;
		if (audience->mTurnEndPhaseEventChance > 100) {
			audience->mTurnEndPhaseEventChance = 100;
		}
		for (i = 0; i < group->numEnemies; i++, setup++) {
			sum += setup->mUnitKindParams->mLevel;
		}
		turns = sum * 2 / mario->mLevel;
		if (turns < 5) {
			turns = 5;
		}
		if (wp->turnCount >= turns) {
			BattleAudienceAddTargetNum(-0.049999997f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
		}
		if (wp->turnCount == turns) {
			BattleAudienceAddPhaseEvtList(6);
		}
		if (irand(100) < audience->mTurnEndPhaseEventChance) {
			if (wp->turnCount >= turns) {
				BattleAudienceAddPhaseEvtList(1);
			}
			BattleAudienceAddPhaseEvtList(4);
			BattleAudienceAddPhaseEvtList(9);
			BattleAudienceAddPhaseEvtList(10);
			BattleAudienceAddPhaseEvtList(11);
			BattleAudienceAddPhaseEvtList(12);
			BattleAudienceAddPhaseEvtList(13);
			audience->mTurnEndPhaseEventChance = 0;
		}
		BattleAudienceNumToTarget();
	}
}

//@@ BattleAudience_Case_Appeal
void BattleAudience_Case_Appeal(BattleUnit* unit) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();

	if (BattleAudience_GetPPAudienceNum() > 0.0f) {
		audience->field_137C4 += (s32)(BattleAudience_GetPPAudienceNum() / 4.0f) + 25;
		if (unit->badgesEquipped.SuperAppeal) {
			audience->field_137C4 += unit->badgesEquipped.SuperAppeal * 25;
		}
		BattleAudienceSoundCheer(180, 60);
		BattleAudienceSoundClap(180, 60);
		BattleAudienceJoy(0);
	}
	BattleAudienceAddTargetNum(0.049999997f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
}

//@@ BattleAudience_Case_Escape
void BattleAudience_Case_Escape(void) {
}

//@@ BattleAudience_Case_Escape_Good
void BattleAudience_Case_Escape_Good(void) {
	BattleAudienceAddTargetNum(-0.099999994f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
	BattleAudienceSoundSetVol(2, 100, 30);
	BattleAudienceSoundBooing();
}

//@@ BattleAudience_Case_Escape_Bad
void BattleAudience_Case_Escape_Bad(void) {
	BattleAudienceAddTargetNum(-0.19999999f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
	BattleAudienceSoundBooing();
}

//@@ BattleAudience_Case_EnemyDamage
void BattleAudience_Case_EnemyDamage(void) {
	BattleAudienceBaseGetPtr()->flags |= 0x400;
}

//@@ BattleAudience_Case_EnemyNoDamage
void BattleAudience_Case_EnemyNoDamage(void) {
	BattleAudienceBaseGetPtr()->flags |= 0x800;
}

//@@ BattleAudience_Case_Countered
void BattleAudience_Case_Countered(void) {
	BattleAudienceAddTargetNum(-0.099999994f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
	BattleAudienceAddPhaseEvtList(5);
}

//@@ BattleAudience_Case_HaikeiSet
void BattleAudience_Case_HaikeiSet(void) {
	BattleAudienceAddTargetNum(0.049999997f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
}

//@@ BattleAudience_Case_GreatVictory
void BattleAudience_Case_GreatVictory(void) {
	BattleAudienceAddTargetNum(0.14999999f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
}

//@@ BattleAudience_Case_FastVictory
void BattleAudience_Case_FastVictory(f32 rate) {
	BattleAudienceAddTargetNum(0.01f * (5.0f * rate) * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
}

//@@ BattleAudience_Case_FallObject_Stage
void BattleAudience_Case_FallObject_Stage(void) {
	BattleAudienceAddTargetNum(0.049999997f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
}

//@@ BattleAudience_Case_FallObject_Aud
void BattleAudience_Case_FallObject_Aud(s32 index, u8 type) {
	BattleAudience* audience = BattleAudienceBaseGetPtr();
	s32 near[8][2] = {
		{-1, 1}, {0, 1}, {1, 1}, {-1, 0}, {1, 0}, {-1, -1}, {0, -1}, {1, -1},
	};
	s32 far[24][2] = {
		{0, 3}, {-1, 2}, {0, 2}, {1, 2}, {-2, 1}, {-1, 1}, {0, 1}, {1, 1},
		{2, 1}, {-3, 0}, {-2, 0}, {-1, 0}, {1, 0}, {2, 0}, {3, 0}, {-2, -1},
		{-1, -1}, {0, -1}, {1, -1}, {2, -1}, {-1, -2}, {0, -2}, {1, -2}, {0, -3},
	};
	s32 i, no;

	switch (type) {
		case 0:
		case 1:
		case 3:
		case 4:
		case 5:
		case 8:
			if ((u8)BattleAudience_GetSysCtrl(index) == TRUE && BattleAudienceGetPtr(index)->status != 15) {
				BattleAudience_ChangeStatus(index, 10);
			}
			for (i = 0; i < 8; i++) {
				no = BattleAudience_GetAudienceNoFromOffset(index, near[i][0], near[i][1]);
				if (no != -1 && (u8)BattleAudience_GetEscapeChangeOK(no)) {
					BattleAudience_ChangeStatus(no, 12);
					audience->mTargetAudienceCount -= 1.0f;
				}
			}
			break;
		case 7:
			if ((u8)BattleAudience_GetSysCtrl(index) == TRUE && BattleAudienceGetPtr(index)->status != 15) {
				BattleAudience_ChangeStatus(index, 10);
			}
			for (i = 0; i < 24; i++) {
				no = BattleAudience_GetAudienceNoFromOffset(index, far[i][0], far[i][1]);
				if (no != -1 && (u8)BattleAudience_GetEscapeChangeOK(no)) {
					BattleAudience_ChangeStatus(no, 12);
					audience->mTargetAudienceCount -= 1.0f;
				}
			}
			break;
		case 6:
			if ((u8)BattleAudience_GetSysCtrl(index) == TRUE && BattleAudienceGetPtr(index)->status != 15) {
				BattleAudience_ChangeStatus(index, 10);
			}
			for (i = 0; i < 200; i++) {
				if ((u8)BattleAudience_GetEscapeChangeOK(i)) {
					BattleAudience_ChangeStatus(i, 12);
					audience->mTargetAudienceCount -= 1.0f;
				}
			}
		default:
			if ((u8)BattleAudience_GetSysCtrl(index) == TRUE && BattleAudienceGetPtr(index)->status != 15) {
				BattleAudience_ChangeStatus(index, 10);
			}
			audience->mTargetAudienceCount -= 1.0f;
			break;
	}
	BattleAudiencePuniAllEscape();
}

//@@ BattleAudience_Case_FirstAttack_Good
void BattleAudience_Case_FirstAttack_Good(void) {
	BattleAudienceAddTargetNum(0.02f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
}

//@@ BattleAudience_Case_FirstAttack_Bad
void BattleAudience_Case_FirstAttack_Bad(void) {
	BattleAudienceAddTargetNum(-0.049999997f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
}

//@@ BattleAudience_SetPresentItemNo
void BattleAudience_SetPresentItemNo(s32 no) {
	BattleAudienceBaseGetPtr()->presentItemNo = no;
}

//@@ BattleAudience_GetPresentItemNo
s32 BattleAudience_GetPresentItemNo(void) {
	return BattleAudienceBaseGetPtr()->presentItemNo;
}

//@@ BattleAudience_SetPresentTargetUnitId
void BattleAudience_SetPresentTargetUnitId(s32 unitId) {
	BattleAudienceBaseGetPtr()->presentTargetUnitId = unitId;
}

//@@ BattleAudience_GetPresentTargetUnitId
s32 BattleAudience_GetPresentTargetUnitId(void) {
	return BattleAudienceBaseGetPtr()->presentTargetUnitId;
}

//@@ BattleAudience_SetPresentItemType
void BattleAudience_SetPresentItemType(s32 type) {
	BattleAudienceBaseGetPtr()->presentItemType = type;
}

//@@ BattleAudience_GetPresentItemType
s32 BattleAudience_GetPresentItemType(void) {
	return BattleAudienceBaseGetPtr()->presentItemType;
}
