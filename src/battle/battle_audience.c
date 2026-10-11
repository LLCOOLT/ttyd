#include "battle/battle_audience.h"
#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/npcdrv.h"
#include "mario/mario_pouch.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>

#pragma optimize_for_size on
#pragma dont_inline on

extern BattleWork* _battleWorkPointer;
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
BOOL check_exe_phase_evt_status(s32 index, AudienceMemberType type);
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
void BattleAudience_Entry_Sub(s32 index, u8 type, u8 status);
BOOL BattleAudience_GetAnimEnd(s32 index);
BOOL BattleAudience_GetFront(s32 index);
BOOL BattleAudience_GetEscapeChangeOK(s32 index);
s32 BattleAudience_GetAudienceNoFromOffset(s32 index, s32 column, s32 row);
s32 BattleAudience_NoUsedHaitiRand(void);
s32 BattleAudience_NoUsedFCHaitiRand(void);
s32 BattleAudience_GetPPAudienceNum(void);
s32 BattleAudience_GetPPAudienceNumKind(u8 type);
s32 BattleAudience_GetPPAudienceNum_R(void);
s32 BattleAudience_GetPPAudienceNum_L(void);
s32 BattleAudience_GetPPAudienceNum_RL_Sub(s32 offset);
BOOL BattleAudience_GetPPAudienceNum_Sub(s32 id);
void BattleAudience_ApRecoveryBuild(void);
void BattleAudienceNumToTarget(void);
void BattleAudienceNumToTargetSub(void);
void BattleAudienceAddTargetNum(f32 value, f32 value2);
void BattleAudienceAddTargetNumSub(f32 value);
void BattleAudienceAddAudienceNum(void);
void BattleAudiencePuniAllEscape(void);
void BattleAudienceAddPuni(void);
void BattleAudienceAddPhaseEvtList(s32 type);
void BattleAudienceCheer(void);
void BattleAudienceJoy(s32 type);
void BattleAudienceJoySACLecture(void);
void BattleAudienceJoyEnding(void);
void BattleAudienceJoy_Sub(void);
void BattleAudienceDetectPakkunEatTargetSub2(void);
void BattleAudienceDetectPakkunEatTargetSub(void);
void BattleAudienceDetectPakkunEatTarget(void);
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
	pouchGetPtr(); //useless call
	memset(audience, 0, sizeof(BattleAudience));
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
			if ((u8)BattleAudience_GetExist(index)) { //TODO: u8 needed?
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
			if ((u8)BattleAudience_GetExist(index)) { //TODO: u8 needed?
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
BOOL check_exe_phase_evt_status(s32 index, AudienceMemberType type) {
	BattleAudienceMember* member;

	member = BattleAudienceGetPtr(index);
	if (!BattleAudience_GetSysCtrl(index)) {
		return FALSE;
	}
	if (member->type != type) {
		return FALSE;
	}
	switch (member->status) { //TODO: check if switch, might be IDA
		case 13:
			return FALSE;
		case 12:
			return FALSE;
		case 11:
			return FALSE;
		case 21:
			return FALSE;
		case 22:
			return FALSE;
		default:
			return (member->flags >> 3) & 1;
	}
}

//@@ BattleAudience_PerPhase
void BattleAudience_PerPhase(u32 value) {
	BattleAudience* audience;
	BattleAudienceMember* member;
	s32 i, itemId;

	audience = BattleAudienceBaseGetPtr();
	if (value == 0x4000002 && !(audience->flags & 0x40000)) {
		for (i = 0; i < 200; i++) {
			member = BattleAudienceGetPtr(i);
			if (BattleAudience_GetExist(i) && member->status == 7) {
				itemId = member->itemId;
				if (itemId != -1) {
					BattleAudienceItemGetPtr(itemId)->flags = 0;
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
	if (pouchGetPtr()->mStarPowersObtained) {
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

	if (pouchGetPtr()->mStarPowersObtained) {
		if (audience->mTargetAudienceCount < 0.0f) {
			audience->mTargetAudienceCount = 0.0f;
		}
		if (audience->mTargetAudienceCount > (f32)audience->mMaxAudience) {
			audience->mTargetAudienceCount = (f32)audience->mMaxAudience;
		}
		pouchSetAudienceNum(audience->mTargetAudienceCount);
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
void BattleAudienceCtrlProcess(void) {
	//TODO: very long and terrible
}

//@@ BattleAudienceItemOn
BOOL BattleAudienceItemOn(s32 index, u16 itemId, s32 numItems) {
	return FALSE;
}

//@@ BattleAudienceSetThrowItemMax
void BattleAudienceSetThrowItemMax(void) {

}

//@@ BattleAudienceDetectTargetAll
BattleUnit* BattleAudienceDetectTargetAll(void) {
	return NULL;
}

//@@ BattleAudienceDetectTargetPlayer
BattleUnit* BattleAudienceDetectTargetPlayer(void) {
	return NULL;
}

//@@ BattleAudienceItemCtrlProcess
void BattleAudienceItemCtrlProcess(void) {

}

//@@ BattleAudienceApSrcCtrlProcess
void BattleAudienceApSrcCtrlProcess(void) {

}

//@@ BattleAudienceApSrcEntry
BOOL BattleAudienceApSrcEntry(void) {
	return FALSE;
}

//@@ BattleAudienceWinCtrlProcess
void BattleAudienceWinCtrlProcess(void) {

}

//@@ BattleAudienceGXInit
void BattleAudienceGXInit(void) {

}

//@@ BattleAudienceAnimProcess
void BattleAudienceAnimProcess(void) {

}

//@@ BattleAudienceDispAudience
void BattleAudienceDispAudience(CameraId camId, void* param) {

}

//@@ BattleAudienceDispItem
void BattleAudienceDispItem(CameraId camId, void* param) {

}

//@@ BattleAudienceDispApSrc
void BattleAudienceDispApSrc(CameraId camId, void* param) {

}

//@@ BattleAudienceDispWin
void BattleAudienceDispWin(CameraId camId, void* param) {

}

//@@ BattleAudience_Entry
BOOL BattleAudience_Entry(s32 index, AudienceMemberType type, u8 status) {
	return FALSE;
}

//@@ BattleAudience_Entry_Sub
void BattleAudience_Entry_Sub(s32 index, u8 type, u8 status) {

}

//@@ BattleAudience_Delete
void BattleAudience_Delete(s32 index) {

}

//@@ BattleAudience_SetAnim
void BattleAudience_SetAnim(s32 id, s32 animId, BOOL force) {

}

//@@ BattleAudience_GetAnimEnd
BOOL BattleAudience_GetAnimEnd(s32 index) {
	return FALSE;
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
	for (i = 0; i < 200; i++) {
		member = BattleAudienceGetPtr(i); //TODO: get (0) out of loop and ++?
		//TODO: invert this to multiple break; checks?
		if ((member->flags & 1) && !(member->flags & 0x100) && !(member->flags & 2)) {
			if (member->itemId != -1) {
				item = BattleAudienceItemGetPtr(member->itemId);
				if (item->state <= 4 || item->state == 7) {
					break; //TODO: better way to handle this compare?
				}
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
					if (member->itemId >= 0) {
						*itemType = audience->items[member->itemId].mItemType;
					}
					else {
						*itemType = ITEM_NULL;
					}
				}
				//has to pass the 4 checks up top, otherwise we keep looking at all 200 members
				return;
			}
		}
	}
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
		if (member->itemId >= 0) {
			*itemType = audience->items[member->itemId].mItemType;
		}
		else {
			*itemType = ITEM_NULL;
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
			Vec rot = {0.0f, 0.0f, 0.0f};
			Vec v6C = {0.0f, 0.0f, 0.0f};
			Vec scale = {1.0f, 1.0f, 1.0f};
			Vec v78 = {0.0f, 0.0f, 0.0f};
			member->field_0x43 = 0;
			member->field_0x42 = 0;
			member->field_0x41 = 0;
			member->field_0x44 = 0xFF;
			member->mRotation = rot;
			member->field_0x6C = v6C;
			member->field_0x60 = scale;
			member->field_0x78 = v78;
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
	return 0;
}

//@@ BattleAudience_NoUsedHaitiRand
s32 BattleAudience_NoUsedHaitiRand(void) {
	return 0;
}

//@@ BattleAudience_NoUsedFCHaitiRand
s32 BattleAudience_NoUsedFCHaitiRand(void) {
	return 0;
}

//@@ BattleAudience_GetAudienceNum
s32 BattleAudience_GetAudienceNum(void) {
	return BattleAudienceBaseGetPtr()->mCurrentAudienceIntCount;
}

//@@ BattleAudience_GetPPAudienceNum
s32 BattleAudience_GetPPAudienceNum(void) {
	return 0;
}

//@@ BattleAudience_GetPPAudienceNumKind
s32 BattleAudience_GetPPAudienceNumKind(u8 type) {
	return 0;
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
s32 BattleAudience_GetPPAudienceNum_RL_Sub(s32 offset) {
	BattleAudience* audience = BattleAudienceBaseGetPtr(); //unused
	s32 i, j, index, count = 0;

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			index = ((i * 20) + offset) + j;
			if (BattleAudience_GetPPAudienceNum_Sub(index)) {
				count++;
			}
		}
	}
	return count;
}

//@@ BattleAudience_GetPPAudienceNum_Sub
BOOL BattleAudience_GetPPAudienceNum_Sub(s32 id) {
	BattleAudienceMember* member = BattleAudienceGetPtr(id);

	if (!BattleAudience_GetExist(id)) {
		return FALSE;
	}

	if (13 <= member->status <= 13) {
		return FALSE;
	}

	if (member->status == 17) {
		return FALSE;
	}

	return member->status != 12;
}

//@@ BattleAudience_ApRecoveryBuild
void BattleAudience_ApRecoveryBuild(void) {
}

//@@ BattleAudience_WinSetActive
void BattleAudience_WinSetActive(u8 active) {
	BattleAudienceWinGetPtr()->mActive = active;
}

//@@ BattleAudienceNumToTarget
void BattleAudienceNumToTarget(void) {

}

//@@ BattleAudienceNumToTargetSub
void BattleAudienceNumToTargetSub(void) {
}

//@@ BattleAudienceAddTargetNum
void BattleAudienceAddTargetNum(f32 value, f32 value2) {
}

//@@ BattleAudienceAddTargetNumSub
void BattleAudienceAddTargetNumSub(f32 value) {
	f32 subtract;
	s32 skew;

	BattleAudience* audience = BattleAudienceBaseGetPtr();
	while (1) {
		if (value == 0.0f) return;
		if (value > 0.0f) { //positive
			subtract = min(value, 1.0f);
			value -= subtract;
			if (value < 0.0f) {
				value = 0.0f;
			}
		}
		if (value < 0.0f) { //negative
			subtract = max(value, -1.0f);
			value -= subtract;
			if (value > 0.0f) {
				value = 0.0f;
			}
		}
		if (subtract > 0.0f) {
			skew = (s32)(((audience->mTargetAudienceCount / audience->mAudienceDeltaMultiplier) - 1.0f) / 0.25f);
			if (skew <= 1) {
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
void BattleAudienceAddAudienceNum(void) {
}

//@@ BattleAudiencePuniAllEscape
void BattleAudiencePuniAllEscape(void) {
}

//@@ BattleAudienceAddPuni
void BattleAudienceAddPuni(void) {
}

//@@ BattleAudienceAddPhaseEvtList
void BattleAudienceAddPhaseEvtList(s32 type) {
}

//@@ BattleAudienceCheer
void BattleAudienceCheer(void) {
}

//@@ BattleAudienceJoy
void BattleAudienceJoy(s32 type) {
}

//@@ BattleAudienceJoySACLecture
void BattleAudienceJoySACLecture(void) {
}

//@@ BattleAudienceJoyEnding
void BattleAudienceJoyEnding(void) {
}

//@@ BattleAudienceJoy_Sub
void BattleAudienceJoy_Sub(void) {
}

//@@ BattleAudienceDetectPakkunEatTargetSub2
void BattleAudienceDetectPakkunEatTargetSub2(void) {
}

//@@ BattleAudienceDetectPakkunEatTargetSub
void BattleAudienceDetectPakkunEatTargetSub(void) {
}

//@@ BattleAudienceDetectPakkunEatTarget
void BattleAudienceDetectPakkunEatTarget(void) {
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
	s32 list[200];
	s32 count;
	s32 i;
	s32 id;
	AudSound* sound;

	count = 0;
	for (i = 0; i < 200; i++) {
		if ((u8)BattleAudience_GetWaiting(i) == TRUE) {
			list[count] = i;
			count++;
		}
	}
	if (count != 0) {
		i = list[irand(count)];
		BattleAudienceSoundGetInfo2(i, &pos);
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
				sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_WHISTLE1", i);
				break;
			case 2:
				sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_WHISTLE2", i);
				break;
			case 3:
				sound->sfxId = BattleAudienceSound2("SFX_AUDIENCE_WHISTLE3", i);
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
	AudSound* sound;
	s32 right;
	s32 left;
	s32 sum;
	s32 vol;

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
		vol = 0;
		sound->mFadeoutTime = 0;
		sound->mForceFadeLength = 0;
		sound->mForceFadeTimer = 0;
		if (sum == 0) {
		}
		else {
			vol = 75.0f + sum * (26.0f + irand(26)) / 200.0f;
		}
		psndSFX_vol(sound->sfxId, vol);
		sound->mCurrentBaseSfxVolume = vol;
		sound->mBaseSfxVolume = vol;
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
