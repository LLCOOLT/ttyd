#include "mario/mario.h"
#include "driver/animdrv.h"
#include "driver/hitdrv.h"
#include "driver/seqdrv.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "mario/mario_party.h"
#include "mario/mario_sbr.h"
#include "mario/mariost.h"
#include "party/party_vivian.h"
#include "party.h"
#include "system.h"
#include <string.h>


//external prototypes (TODO: move to headers)
s32 marioShipChanging(void);
BOOL marioRollKeyDisable(void);
BOOL marioSlitKeyDisable(void);
s32 christineGetStatus(void);
BOOL mario_bomhei_keychk2(void);
s32 yoshiGetStatus(void);
BOOL nokonoko_holdItem(void);
void marioYoshiForceCancel(void);

//.data
const char* dotMarioPose[4][6] = {
	{"Z_1", "S_1", "W_1", "R_1", "U_1", "J_1"},
	{"Z_15", "S_2", "W_15", "R_15", "U_2", "J_2"},
	{"Z_17", "S_3", "W_17", "R_17", "U_3", "J_3"},
	{"Z_18", "S_4", "W_18", "R_18", "U_4", "J_4"}
};

//.sdata
const char* marioAnimeGroupData[4][3] = {
	{"a_mario", "a_mario_r", "e_mario"},
	{"a_mario_l", "a_mario_lr", "e_mario_l"},
	{"a_mario_w", "a_mario_wr", "e_mario_w"},
	{"a_mario_wl", "a_mario_wlr", "e_mario_wl"}
};

//.bss
Vec blurPos[8];

//.sbss
s32 blurPosId;
Vec R_last_position;
MarioWork* mp;

//local prototypes
void marioDispBlurSub(Mtx mtx, s32 blurId);
const char* toRearPose(const char* name);
const char* toFrontPose(const char* name);

MarioWork* marioGetPtr(void) {
	return mp;
}

s32 marioGetColor(void) {
	return mp->colorId;
}

void marioSetCharMode(s32 mode) {

}

void marioSetFamicomMode(s32 mode) {

}

void marioSetSpec(void) {
	MarioWork* wp = mp;

	if (wp->characterId == 1) {
		(wp->wPlayerCollisionBox).x = 20.0f;
		(wp->wPlayerCollisionBox).y = 47.0f;
		wp->mBaseWalkSpeed = 1.0f;
		wp->mBaseDashSpeed = 2.0f;
	}
	else if (wp->characterId == 2) {
		wp->mBaseWalkSpeed = 1.0f;
		wp->mBaseDashSpeed = 2.25f;
	}
	else {
		if (!(wp->flags & 0x2000000)) {
			(wp->wPlayerCollisionBox).x = 20.0f;
			(wp->wPlayerCollisionBox).y = 37.0f;
		}
		else {
			(wp->wPlayerCollisionBox).x = 10.0f;
			(wp->wPlayerCollisionBox).y = 25.9f;
		}
		wp->mBaseWalkSpeed = 1.0f;
		wp->mBaseDashSpeed = 2.25f;
	}
}

//TODO: finish
void marioEntry(void) {
	/*
	mp->flags |= 1;
	if (!(mp->dispFlags & 2)) {
		if (!mp->animName || strcmp(mp->animName, "M_S_1")) {

		}
	}
	if (mp->flags & 0x2000000) {
		if (mp->currMotionId == kSlit) {
			mp->flags |= 0x100000;
			marioSlitForceCancel();
		}
	}
	else {
		switch (mp->currMotionId) {
			case kShip:
				marioReInit_ship();
				break;
			case kRoll:
				marioReInit_roll();
				break;
			case kSlit:
				marioReInit_slit();
				break;
			case kYoshi:
				marioRideYoshi();
				break;
			default:
				marioChgMot(kStay);

		}
	}
	*/
}

void marioItemGetDisable(void) {
	MarioWork* wp = mp;
	wp->flags |= 0x4000;
	wp->field_0x7A = 0x14;
}

void marioItemGetChk(void) {
	MarioWork* work;
	s32 var;

	work = mp;
	var = mp->field_0x7A;
	if (var > 0) {
		var--;
		work->field_0x7A = (s16)var;
		if ((s16)var <= 0) {
			work->field_0x7A = 0;
			mp->flags &= ~0x4000u;
		}
	}
}

BOOL marioItemGetOk(void) {
	return (mp->flags & 0x4000) == 0;
}

BOOL marioCaseEventValidChk(void) {
	if (mp->currMotionId == MARIO_MOTION_PLANE) {
		return FALSE;
	}
	else {
		return vivianGetStatus() == 0;
	}
}

BOOL unk_8005bb80(void) {
	if (mp->currMotionId == MARIO_MOTION_ROLL || mp->flags & 0x100000) {
		return FALSE;
	}
	return TRUE;
}

BOOL marioCheckMenuDisable(void) {
	return TRUE;
}

BOOL marioChkKey(void) {
	PartyEntry* party = partyGetPtr(marioGetPartyId());

	if (seqGetSeq() != SEQ_GAME) {
		return FALSE;
	}
	if (mp->keyOffCount) {
		return FALSE;
	}
	if (marioShipChanging() == 1 || marioShipChanging() == 2) {
		return FALSE;
	}
	if (!marioRollKeyDisable()) {
		return FALSE;
	}
	if (!marioSlitKeyDisable()) {
		return FALSE;
	}
	if (!party) {
		return TRUE;
	}
	if (christineGetStatus() == 1) {
		return FALSE;
	}
	if (!mario_bomhei_keychk2()) {
		return FALSE;
	}
	if (yoshiGetStatus()) {
		return FALSE;
	}
	if (party->flags & 0x100) {
		if (party->currentMemberId == 7 || party->currentMemberId == 5 || party->currentMemberId == 6) {
			return FALSE;
		}
	}
	if (nokonoko_holdItem()) {
		return FALSE;
	}
	return TRUE;
}

BOOL marioChkCtrl(void) {
	return mp->ctrlOffCount == 0;
}

BOOL N_marioChkUseParty(void) {
	if ((u16)gp->buttonNew[0] & 0x100F) {
		return TRUE;
	}
	return mp->ctrlOffCount;
}

void marioFBattlePrepare(void) {
	MarioWork* wp = mp;

	R_last_position = wp->position;
	marioAdjustMoveDir();
	if (wp->currMotionId != MARIO_MOTION_JABARA) {
		wp->flags |= 0x1000;
	}
	partyUsePost(partyGetPtr(marioGetPartyId()));
	((void (*)(void))partyCtrlOff)();
}

void marioFBattlePost(void) {
	MarioWork* wp = mp;

	wp->flags &= ~0x1000;
	if (wp->currMotionId == MARIO_MOTION_JABARA) {
		wp->position = R_last_position;
	}
	if (wp->currMotionId == MARIO_MOTION_YOSHI) {
		marioYoshiForceCancel();
	}
	((void (*)(void))partyCtrlOn)();
	if (wp->currMotionId == MARIO_MOTION_HAMMER || wp->currMotionId == MARIO_MOTION_JABARA) {
		marioChgMot(MARIO_MOTION_STAY);
	}
}

s32 marioCtrlOffChk(void) {
	return mp->ctrlOffCount;
}

s32 marioKeyOffChk(void) {
	return mp->keyOffCount;
}

s32 marioCtrlOff(void) {
	MarioWork* wp = mp;

	wp->flags |= 2;
	wp->ctrlOffCount++;
	return wp->ctrlOffCount;
}

s32 marioCtrlOn(void) {
	MarioWork* wp = mp;

	wp->ctrlOffCount--;
	if (wp->ctrlOffCount == 0) {
		wp->flags &= ~2;
	}
	return wp->ctrlOffCount;
}

s32 marioCtrlOff2(void) {
	MarioWork* wp = mp;

	wp->flags |= 4;
	wp->flags |= 2;
	wp->ctrlOffCount++;
	return wp->ctrlOffCount;
}

s32 marioCtrlOn2(void) {
	MarioWork* wp = mp;

	wp->flags &= ~4;
	wp->ctrlOffCount--;
	if (wp->ctrlOffCount == 0) {
		wp->flags &= ~2;
	}
	return wp->ctrlOffCount;
}

s32 marioKeyOff(void) {
	MarioWork* wp = mp;

	wp->flags |= 8;
	wp->keyOffCount++;
	return wp->keyOffCount;
}

s32 marioKeyOn(void) {
	MarioWork* wp = mp;

	wp->keyOffCount--;
	if (wp->keyOffCount == 0) {
		wp->flags &= ~8;
	}
	return wp->keyOffCount;
}

s16 marioSetMutekiTime(s32 msec) {
	MarioWork* wp = mp;
	PartyEntry* party;

	wp->unk4C = sysMsec2Frame(msec);
	party = partyGetPtr(marioGetPartyId());
	if (party) {
		*(s16*)((u8*)party + 0x2A) = wp->unk4C;
	}
	return wp->unk4C;
}

BOOL marioBgmodeChk(void) {
	return (mp->flags >> 25) & 1;
}

void marioBgmodeOn(void) {
	mp->flags |= 0x2000000;
	marioSetSpec();
	camFollowYOff();
}

void marioBgmodeOff(void) {
	mp->flags &= ~0x2000000;
	marioSetSpec();
	camFollowYOn();
}

BOOL marioChkSts(s32 flags) {
	MarioWork* wp = mp;
	BOOL ret = FALSE;

	if (flags & 1 && wp->flags & 0x10000) {
		ret = TRUE;
	}
	if (flags & 2 && wp->flags & 0x20000) {
		ret = TRUE;
	}
	if (flags & 4 && wp->flags & 0x100000) {
		ret = TRUE;
	}
	if (flags & 0x20 && wp->currMotionId == MARIO_MOTION_KAZE) {
		ret = TRUE;
	}
	if (flags & 0x10 && wp->currMotionId == MARIO_MOTION_ROLL) {
		ret = TRUE;
	}
	if (flags & 8 && wp->currMotionId == MARIO_MOTION_JABARA) {
		ret = TRUE;
	}
	return ret;
}

void marioResetHitObj(const char* name) {
	MarioWork* wp = mp;

	if (wp->field_0x1DC && !strcmp(hitGetName((HitEntry*)wp->field_0x1DC), name)) {
		wp->field_0x1DC = 0;
	}
	if (wp->field_0x1E0 && !strcmp(hitGetName((HitEntry*)wp->field_0x1E0), name)) {
		wp->field_0x1E0 = 0;
	}
	if (wp->hitobjStandOn && !strcmp(hitGetName(wp->hitobjStandOn), name)) {
		wp->hitobjStandOn = NULL;
	}
	if (wp->hitobjJumpFrom && !strcmp(hitGetName(wp->hitobjJumpFrom), name)) {
		wp->hitobjJumpFrom = NULL;
	}
	if (wp->hitobjPush && !strcmp(hitGetName(wp->hitobjPush), name)) {
		wp->hitobjPush = NULL;
	}
	if (wp->field_0x1F0 && !strcmp(hitGetName((HitEntry*)wp->field_0x1F0), name)) {
		wp->field_0x1F0 = 0;
	}
	if (wp->field_0x1F4 && !strcmp(hitGetName((HitEntry*)wp->field_0x1F4), name)) {
		wp->field_0x1F4 = 0;
	}
	if (wp->field_0x1F8 && !strcmp(hitGetName((HitEntry*)wp->field_0x1F8), name)) {
		wp->field_0x1F8 = 0;
	}
	if (wp->field_0x1FC && !strcmp(hitGetName((HitEntry*)wp->field_0x1FC), name)) {
		wp->field_0x1FC = 0;
	}
}

void marioReset(void) {
	MarioWork* wp = mp;

	marioSetSpec();
	wp->flags &= ~0x100000;
	wp->flags &= ~0x1000000;
	marioPaperOff();
	marioChgPaper(NULL);
	wp->dispFlags &= ~8;
	wp->dispFlags &= ~0x100;
	marioOfsRotReset();
	wp->baseSpeed = 0.0f;
	marioChgMot(MARIO_MOTION_STAY);
}

void marioOfsRotReset(void) {
	MarioWork* wp = mp;

	wp->rot = (Vec){0.0f, 0.0f, 0.0f};
	wp->rotOfs = (Vec){0.0f, 0.0f, 0.0f};
	wp->field_0x98 = (Vec){0.0f, 0.0f, 0.0f};
	wp->field_0xA4 = (Vec){0.0f, 0.0f, 0.0f};
}

void marioSoundInit(void) {
	MarioWork* wp = mp;

	wp->soundId[0] = -1;
	wp->soundId[1] = -1;
	wp->soundId[2] = -1;
}

void marioPoseInit(void) {
	MarioWork* wp = mp;

	wp->paperAnimGroupId[0] = animPoseEntry(marioAnimeGroupData[mp->colorId][0], 2);
	wp->paperAnimGroupId[1] = animPoseEntry(marioAnimeGroupData[mp->colorId][1], 2);
	wp->paperAnimGroupId[2] = animPoseEntry(marioAnimeGroupData[mp->colorId][2], 2);
}

void marioInit(void) {

}

void marioReInit(void) {

}

void marioMain(void) {

}

void marioCtrlOff2Main(void) {

}

void marioMove(void) {

}

void marioMoveMain(void) {

}

BOOL marioChkPushAnime(void) {
	MarioWork* wp = mp;
	BOOL valid = FALSE;
	if (!strcmp(wp->animName, "M_O_1") || !strcmp(wp->animName, "M_O_2") || !strcmp(wp->animName, "M_O_2R")) {
		valid = TRUE;
	}
	return valid;
}

s32 marioAnimeId(void) {
	s32 flags = mp->dispFlags;
	s32 id;
	if (flags & 0x10000000) {
		id = 2;
	}
	else if (flags & 0x80000000) {
		id = 1;
	}
	else {
		id = 0;
	}
	return id;
}

inline void marioChgPoseChk(const char* name) {
	if (mp->dispFlags & 0x1000000) {
		return;
	}
	marioChgPose(name);
}

void unk_80058374(void) {
	MarioWork* wp = mp;
	MarioMotion mot = wp->currMotionId;

	if (mot != MARIO_MOTION_SHIP && mot != MARIO_MOTION_ROLL && mot != MARIO_MOTION_PLANE && mot != MARIO_MOTION_JABARA && mot != MARIO_MOTION_YOSHI) {
		marioChgPoseChk("M_D_1");
	}
}

void marioChgEvtPose(const char* name) {
	MarioWork* wp = mp;
	const char* animName;

	if (!(mp->dispFlags & 2) && !(mp->flags & 0x80000000)) {
		animName = mp->animName;
		if (!animName || strcmp(animName, name)) {
			wp->animName = name;
			wp->dispFlags &= ~0x20000000;
			wp->dispFlags |= 0x10000000;
			wp->trigFlags |= 0x1000;
		}
	}
}

const char* toDotMarioPose(const char* name) {
	const char* dot = NULL;

	if (!strcmp("M_Z_1", name)) {
		dot = dotMarioPose[mp->colorId][0];
	}
	else if (!strcmp("M_S_1", name)) {
		dot = dotMarioPose[mp->colorId][1];
	}
	else if (!strcmp("M_W_1", name)) {
		dot = dotMarioPose[mp->colorId][2];
	}
	else if (!strcmp("M_R_1", name)) {
		dot = dotMarioPose[mp->colorId][3];
	}
	else if (!strcmp("M_J_1B", name)) {
		dot = dotMarioPose[mp->colorId][5];
	}
	else if (!strcmp("M_J_1C", name)) {
		dot = dotMarioPose[mp->colorId][5];
	}

	return dot;
}

void marioChgPose(const char* name) {
	MarioWork* wp = mp;
	const char* dot;

	if (!(wp->dispFlags & 2)) {
		if (!wp->animName || strcmp(wp->animName, name)) {
			if (!(wp->flags & 0x80000000)) {
				wp->animName = name;
				wp->poseTime = 0;
				wp->dispFlags &= ~0x30000000;
				wp->trigFlags |= 0x1000;
			}
			else {
				dot = toDotMarioPose(name);
				if (dot) {
					wp->animName = dot;
					wp->poseTime = 0;
					wp->dispFlags &= ~0x30000000;
					wp->trigFlags |= 0x1000;
				}
			}
		}
	}
}

void marioChgPoseTime(const char* name, s16 frames) {
	MarioWork* wp = mp;
	const char* animName;

	if (!(mp->dispFlags & 2) && !(mp->flags & 0x80000000)) {
		animName = mp->animName;
		if (!animName || strcmp(animName, name)) {
			wp->animName = name;
			wp->poseTime = frames;
			wp->dispFlags &= ~0x30000000;
			wp->trigFlags |= 0x1000;
		}
	}
}

void marioChgPaper(const char* name) {
	MarioWork* wp = mp;
	s32 flags = wp->dispFlags;
	const char* animName;

	if (flags & 0x40000000 && !(flags & 2) && !(mp->flags & 0x80000000)) {
		animName = mp->paperAnimName;
		if (!animName || strcmp(animName, name)) { //if different, do stuff
			wp->paperAnimName = name;
			wp->poseTime = 0;
			wp->trigFlags |= 0x4000;
		}
	}
}

void marioSetPaperAnimeLocalTime(s32 frames) {
	MarioWork* wp = mp;

	wp->poseTime = frames;
	animPoseSetLocalTime(wp->paperPoseId, frames);
	animPoseSetLocalTime(wp->paperAnimGroupId[marioAnimeId()], frames);
}

//TODO: move below marioPaperOff when -inline deferred is on
inline void marioPaperRelease(void) {
	MarioWork* wp = mp;
	s32 poseId;

	poseId = wp->paperPoseId;
	if (poseId >= 0) {
		animPaperPoseRelease(poseId);
		wp->paperPoseId = -1;
	}
}

BOOL marioPaperOn(const char* name) {
	MarioWork* wp = mp;
	BOOL flag;
	s32 poseId;

	poseId = wp->paperPoseId;
	if (poseId >= 0) {
		animPaperPoseRelease(poseId);
		wp->paperPoseId = -1;
	}
	wp->dispFlags |= 0x40000000; //paper on
	wp->paperPoseId = animPaperPoseEntry(name, 2);
	flag = FALSE;
	if (   !strcmp(name, "p_roll")
		|| !strcmp(name, "p_plane")
		|| !strcmp(name, "p_hune")
		|| !strcmp(name, "p_jyabara")
		|| !strcmp(name, "p_dokan_x")
		|| !strcmp(name, "p_dokan_y"))
	{
		flag = TRUE;
	}
	animPoseSetPaperAnimGroup(wp->paperAnimGroupId[0], name, !flag);
	return TRUE;
}

void marioPaperOff(void) { //1:1
	MarioWork* wp = mp;

	if (wp->dispFlags & 0x40000000) {
		if (wp->paperAnimName) {
			animPoseSetPaperAnimGroup(mp->paperAnimGroupId[0], NULL, FALSE);
			wp->paperAnimName = 0;
			wp->dispFlags &= ~0x40000000;
			marioPaperRelease();
		}
	}
}

void marioPaperLightOn(void) { //1:1
	animPoseSetMaterialLightFlagOn(mp->paperAnimGroupId[0], 1);
}

void marioPaperLightOff(void) { //1:1
	animPoseSetMaterialLightFlagOff(mp->paperAnimGroupId[0], 1);
}

void marioGetScreenPos(Vec position, f32* x, f32* y, f32* z) { //1:1
	CameraEntry* camera;
	f32 proj[7];
	f32 view[6];

	camera = camGetPtr(CAMERA_3D);
	GXSetProjection(camera->projection, camera->projType);
	GXGetProjectionv(proj);
	GXGetViewportv(view);
	GXProject(position.x, position.y, position.z, camera->view, proj, view, x, y, z);
}

BOOL marioChkInScreen(s32 x, s32 y) { //1:1
	BOOL valid = FALSE;
	if (x >= 0 && x <= 600 && y >= 0 && y <= 535) {
		valid = TRUE;
	}
	return valid != FALSE; //why
}

f32 marioGetScale(void) { //1:1
	return mp->flags & 0x2000000 ? 1.2f : 2.0f;
}

void marioMakeDispDir(void) {

}

void marioRearAnime(void) {

}

void marioPreDisp(void) {

}

inline BOOL marioChkRevDir(f32 angle) {
	BOOL ret = FALSE;

	if (angle >= 90.0f && angle <= 270.0f) {
		ret = TRUE;
	}
	return ret;
}

void marioDispBlurSub(Mtx unused, s32 blurId) {
	MarioWork* wp = mp;
	Mtx mtx;
	Mtx rotMtx;
	Mtx scaleMtx;
	f32 scale;
	f32 angle;
	f32 yofs = 0.0f;

	scale = marioGetScale();
	MTXScale(mtx, wp->scale.x * scale, wp->scale.y * scale, wp->scale.z * scale);
	if (!(wp->dispFlags & 8) && wp->currMotionId == MARIO_MOTION_JABARA) {
		MTXScale(scaleMtx, 1.0f, 1.0f, marioChkRevDir(revise360(wp->rot.x)) ? -1.0f : 1.0f);
		MTXConcat(scaleMtx, mtx, mtx);
	}
	if (!(wp->dispFlags & 0xC00)) {
		if (!(wp->dispFlags & 8)) {
			MTXScale(scaleMtx, 1.0f, 1.0f, marioChkRevDir(revise360(wp->unk1A8)) ? -1.0f : 1.0f);
			MTXConcat(scaleMtx, mtx, mtx);
		}
	}
	else {
		if (wp->dispFlags & 0x400) {
			MTXScale(scaleMtx, 1.0f, 1.0f, 1.0f);
		}
		else {
			MTXScale(scaleMtx, 1.0f, 1.0f, -1.0f);
		}
		MTXConcat(scaleMtx, mtx, mtx);
	}
	MTXTrans(rotMtx, -wp->rotOfs.x, -wp->rotOfs.y, -wp->rotOfs.z);
	MTXConcat(rotMtx, mtx, mtx);
	if (wp->currMotionId == MARIO_MOTION_PLANE) {
		MTXRotRad(rotMtx, 'x', 0.017453292f * wp->rot.x);
		MTXConcat(rotMtx, mtx, mtx);
		MTXRotRad(rotMtx, 'z', 0.017453292f * wp->rot.z);
		MTXConcat(rotMtx, mtx, mtx);
	}
	else {
		MTXRotRad(rotMtx, 'z', 0.017453292f * wp->rot.z);
		MTXConcat(rotMtx, mtx, mtx);
		MTXRotRad(rotMtx, 'x', 0.017453292f * wp->rot.x);
		MTXConcat(rotMtx, mtx, mtx);
	}
	MTXRotRad(rotMtx, 'y', 0.017453292f * revise360(wp->unk1A8 - wp->targetYaw));
	MTXConcat(rotMtx, mtx, mtx);
	if (wp->dispFlags & 0xC00) {
		angle = revise360(wp->unk1A8);
		if (angle >= 90.0f && angle <= 270.0f) {
			MTXRotRad(rotMtx, 'y', 0.017453292f * ((wp->dispFlags & 0x400) ? 180.0f : 0.0f));
			MTXConcat(rotMtx, mtx, mtx);
		}
		else {
			MTXRotRad(rotMtx, 'y', 0.017453292f * ((wp->dispFlags & 0x400) ? 0.0f : 180.0f));
			MTXConcat(rotMtx, mtx, mtx);
		}
	}
	MTXTrans(rotMtx, wp->rotOfs.x, wp->rotOfs.y, wp->rotOfs.z);
	MTXConcat(rotMtx, mtx, mtx);
	if (wp->flags & 0x1000000) {
		MTXScale(scaleMtx, 1.0f, wp->unk130, 1.0f);
		MTXConcat(scaleMtx, mtx, mtx);
	}
	if (wp->currMotionId == MARIO_MOTION_YOSHI) {
		MTXRotRad(rotMtx, 'z', 0.017453292f * wp->unk2B8);
		MTXConcat(rotMtx, mtx, mtx);
	}
	MTXTrans(rotMtx,
		wp->field_0xA4.x + (wp->field_0x98.x + blurPos[blurId].x),
		yofs + (wp->field_0xA4.y + (wp->field_0x98.y + blurPos[blurId].y)),
		wp->field_0xA4.z + (wp->field_0x98.z + blurPos[blurId].z));
	MTXConcat(rotMtx, mtx, mtx);
	animPoseSetMaterialFlagOn(wp->paperAnimGroupId[marioAnimeId()], 0x40);
	animPoseSetMaterialEvtColor(wp->paperAnimGroupId[marioAnimeId()], (GXColor){0xFF, 0xFF, 0xFF, 0x80 - (blurId << 4)});
	animPoseDrawMtx(wp->paperAnimGroupId[marioAnimeId()], mtx, 1, 0.0f, 1.0f);
	animPoseDrawMtx(wp->paperAnimGroupId[marioAnimeId()], mtx, 2, 0.0f, 1.0f);
	animPoseDrawMtx(wp->paperAnimGroupId[marioAnimeId()], mtx, 3, 0.0f, 1.0f);
}

void marioDispBlur(CameraId camId, void* param) {
	MarioWork* wp = param;
	s32 i;
	u32 flag;
	f32 angle;
	Mtx mtx;

	flag = animPoseGetMaterialFlag(wp->paperAnimGroupId[marioAnimeId()]);
	angle = 6.2831855f * wp->targetYaw / 360.0f;
	if (angle <= 3.1415927f) {
		if (angle <= 1.5707964f) {
		}
		else {
		}
	}
	else if (angle <= 4.712389f) {
	}
	if (angle <= 3.1415927f) {
		if (angle <= 1.5707964f) {
		}
		else {
		}
	}
	else if (angle <= 4.712389f) {
	}
	for (i = 7; i > 0; i--) {
		marioDispBlurSub(mtx, i);
	}
	animPoseSetMaterialFlagOff(wp->paperAnimGroupId[marioAnimeId()], 0x40);
	animPoseSetMaterialFlagOn(wp->paperAnimGroupId[marioAnimeId()], flag);
}

void marioDisp(CameraId camId, void* param) {
	MarioWork* wp = mp;
	Mtx mtx;
	Mtx rotMtx;
	Mtx scaleMtx;
	f32 scale;
	f32 angle;

	scale = marioGetScale();
	MTXScale(mtx, wp->scale.x * scale, wp->scale.y * scale, wp->scale.z * scale);
	if (!(wp->dispFlags & 8) && wp->currMotionId == MARIO_MOTION_JABARA) {
		MTXScale(scaleMtx, 1.0f, 1.0f, marioChkRevDir(revise360(wp->rot.x)) ? -1.0f : 1.0f);
		MTXConcat(scaleMtx, mtx, mtx);
	}
	if (!(wp->dispFlags & 0xC00)) {
		if (wp->dispFlags & 0x10) {
			MTXScale(scaleMtx, 1.0f, 1.0f, -1.0f);
			MTXConcat(scaleMtx, mtx, mtx);
		}
		else if (!(wp->dispFlags & 8)) {
			MTXScale(scaleMtx, 1.0f, 1.0f, marioChkRevDir(revise360(wp->unk1A8)) ? -1.0f : 1.0f);
			MTXConcat(scaleMtx, mtx, mtx);
		}
	}
	else {
		if (wp->dispFlags & 0x400) {
			MTXScale(scaleMtx, 1.0f, 1.0f, 1.0f);
		}
		else {
			MTXScale(scaleMtx, 1.0f, 1.0f, -1.0f);
		}
		MTXConcat(scaleMtx, mtx, mtx);
	}
	MTXTrans(rotMtx, -wp->rotOfs.x, -wp->rotOfs.y, -wp->rotOfs.z);
	MTXConcat(rotMtx, mtx, mtx);
	if (wp->currMotionId == MARIO_MOTION_PLANE) {
		MTXRotRad(rotMtx, 'x', 0.017453292f * wp->rot.x);
		MTXConcat(rotMtx, mtx, mtx);
		MTXRotRad(rotMtx, 'z', 0.017453292f * wp->rot.z);
		MTXConcat(rotMtx, mtx, mtx);
	}
	else {
		MTXRotRad(rotMtx, 'z', 0.017453292f * wp->rot.z);
		MTXConcat(rotMtx, mtx, mtx);
		MTXRotRad(rotMtx, 'x', 0.017453292f * wp->rot.x);
		MTXConcat(rotMtx, mtx, mtx);
	}
	MTXRotRad(rotMtx, 'y', 0.017453292f * revise360(wp->unk1A8 - wp->targetYaw));
	MTXConcat(rotMtx, mtx, mtx);
	if (wp->dispFlags & 0xC00) {
		angle = revise360(wp->unk1A8);
		if (angle >= 90.0f && angle <= 270.0f) {
			MTXRotRad(rotMtx, 'y', 0.017453292f * ((wp->dispFlags & 0x400) ? 180.0f : 0.0f));
			MTXConcat(rotMtx, mtx, mtx);
		}
		else {
			MTXRotRad(rotMtx, 'y', 0.017453292f * ((wp->dispFlags & 0x400) ? 0.0f : 180.0f));
			MTXConcat(rotMtx, mtx, mtx);
		}
	}
	MTXTrans(rotMtx, wp->rotOfs.x, wp->rotOfs.y, wp->rotOfs.z);
	MTXConcat(rotMtx, mtx, mtx);
	if (wp->flags & 0x1000000) {
		MTXScale(scaleMtx, 1.0f, wp->unk130, 1.0f);
		MTXConcat(scaleMtx, mtx, mtx);
	}
	MTXTrans(rotMtx,
		wp->field_0xA4.x + (wp->position.x + wp->field_0x98.x),
		wp->field_0xA4.y + (wp->position.y + wp->field_0x98.y),
		wp->field_0xA4.z + (wp->position.z + wp->field_0x98.z));
	MTXConcat(rotMtx, mtx, mtx);
	animPoseDrawMtx(wp->paperAnimGroupId[marioAnimeId()], mtx, 2, 0.0f, 1.0f);
	animPoseDrawMtx(wp->paperAnimGroupId[marioAnimeId()], mtx, 1, 0.0f, 1.0f);
	animPoseSetLocalTimeRate(wp->paperAnimGroupId[marioAnimeId()], (wp->flags & 0x4000000) ? 0.75f : 1.0f);
}

const char* toRearPose(const char* name) { //1:1
	const char* rear = NULL;
	if (mp->characterId == 1 && !(mp->peachFlags & 0x2000)) {
		if (!strcmp(name, "P_Z_1")) {
			rear = "P_Z_1R";
		}
		else if (!strcmp(name, "P_S_1")) {
			rear = "P_S_1R";
		}
		else if (!strcmp(name, "P_W_1")) {
			rear = "P_W_1R";
		}
		else if (!strcmp(name, "P_R_1")) {
			rear = "P_R_1R";
		}
		else if (!strcmp(name, "P_T_1")) {
			rear = "P_T_1R";
		}
		else if (!strcmp(name, "P_Z_2")) {
			rear = "P_Z_2R";
		}
		else if (!strcmp(name, "P_S_2")) {
			rear = "P_S_2R";
		}
		else if (!strcmp(name, "P_W_2")) {
			rear = "P_W_2R";
		}
		else if (!strcmp(name, "P_R_2")) {
			rear = "P_R_2R";
		}
		else if (!strcmp(name, "P_T_2")) {
			rear = "P_T_2R";
		}
		else if (!strcmp(name, "P_Z_3")) {
			rear = "P_Z_3R";
		}
		else if (!strcmp(name, "P_S_3")) {
			rear = "P_S_3R";
		}
		else if (!strcmp(name, "P_W_3")) {
			rear = "P_W_3R";
		}
		else if (!strcmp(name, "P_R_3")) {
			rear = "P_R_3R";
		}
		else if (!strcmp(name, "P_T_3")) {
			rear = "P_T_3R";
		}
		else if (!strcmp(name, "P_O_Z_1")) {
			rear = "P_O_Z_1R";
		}
		else if (!strcmp(name, "P_O_S_1")) {
			rear = "P_O_S_1R";
		}
		else if (!strcmp(name, "P_O_F_1")) {
			rear = "P_O_F_1R";
		}
		else if (!strcmp(name, "P_O_R_1")) {
			rear = "P_O_R_1R";
		}
		else if (!strcmp(name, "P_O_N_1")) {
			rear = "P_O_N_1R";
		}
		else if (!strcmp(name, "P_O_S_2")) {
			rear = "P_O_S_2R";
		}
		else if (!strcmp(name, "P_O_F_2")) {
			rear = "P_O_F_2R";
		}
		else if (!strcmp(name, "P_O_R_2")) {
			rear = "P_O_R_2R";
		}
		else if (!strcmp(name, "P_O_N_2")) {
			rear = "P_O_N_2R";
		}
		else if (!strcmp(name, "P_O_D_1")) {
			rear = "P_O_D_1R";
		}
		else if (!strcmp(name, "P_O_D_2")) {
			rear = "P_O_D_2R";
		}
		else if (!strcmp(name, "P_A_1")) {
			rear = "P_A_1R";
		}
		return rear;
	}
	else {
		if (!strcmp(name, "M_Z_1")) {
			rear = "M_Z_1R";
		}
		else if (!strcmp(name, "M_S_1")) {
			rear = "M_S_1R";
		}
		else if (!strcmp(name, "M_W_1")) {
			rear = "M_W_1R";
		}
		else if (!strcmp(name, "M_R_1")) {
			rear = "M_R_1R";
		}
		else if (!strcmp(name, "M_J_1B")) {
			rear = "M_J_1BR";
		}
		else if (!strcmp(name, "M_J_1C")) {
			rear = "M_J_1CR";
		}
		else if (!strcmp(name, "M_H_1")) {
			rear = "M_H_1R";
		}
		else if (!strcmp(name, "M_H_2")) {
			rear = "M_H_2R";
		}
		else if (!strcmp(name, "M_H_4")) {
			rear = "M_H_4R";
		}
		else if (!strcmp(name, "M_H_5")) {
			rear = "M_H_5R";
		}
		else if (!strcmp(name, "M_H_7")) {
			rear = "M_H_7R";
		}
		else if (!strcmp(name, "M_H_8")) {
			rear = "M_H_8R";
		}
		else if (!strcmp(name, "M_O_2")) {
			rear = "M_O_1R";
		}
		else if (!strcmp(name, "M_I_2")) {
			rear = "M_I_2R";
		}
		else if (!strcmp(name, "M_U_2")) {
			rear = "M_U_2R";
		}
		else if (!strcmp(name, "M_C_1")) {
			rear = "M_C_1R";
		}
		return rear;
	}
}

const char* toFrontPose(const char* name) { //1:1
	const char* front = NULL;
	if (mp->characterId == 1 && !(mp->peachFlags & 0x2000)) {
		if (!strcmp(name, "P_Z_1R")) {
			front = "P_Z_1";
		}
		else if (!strcmp(name, "P_S_1R")) {
			front = "P_S_1";
		}
		else if (!strcmp(name, "P_W_1R")) {
			front = "P_W_1";
		}
		else if (!strcmp(name, "P_R_1R")) {
			front = "P_R_1";
		}
		else if (!strcmp(name, "P_T_1R")) {
			front = "P_T_1";
		}
		else if (!strcmp(name, "P_Z_2R")) {
			front = "P_Z_2";
		}
		else if (!strcmp(name, "P_S_2R")) {
			front = "P_S_2";
		}
		else if (!strcmp(name, "P_W_2R")) {
			front = "P_W_2";
		}
		else if (!strcmp(name, "P_R_2R")) {
			front = "P_R_2";
		}
		else if (!strcmp(name, "P_T_2R")) {
			front = "P_T_2";
		}
		else if (!strcmp(name, "P_Z_3R")) {
			front = "P_Z_3";
		}
		else if (!strcmp(name, "P_S_3R")) {
			front = "P_S_3";
		}
		else if (!strcmp(name, "P_W_3R")) {
			front = "P_W_3";
		}
		else if (!strcmp(name, "P_R_3R")) {
			front = "P_R_3";
		}
		else if (!strcmp(name, "P_T_3R")) {
			front = "P_T_3";
		}
		else if (!strcmp(name, "P_O_Z_1R")) {
			front = "P_O_Z_1";
		}
		else if (!strcmp(name, "P_O_S_1R")) {
			front = "P_O_S_1";
		}
		else if (!strcmp(name, "P_O_F_1R")) {
			front = "P_O_F_1";
		}
		else if (!strcmp(name, "P_O_R_1R")) {
			front = "P_O_R_1";
		}
		else if (!strcmp(name, "P_O_N_1R")) {
			front = "P_O_N_1";
		}
		else if (!strcmp(name, "P_O_S_2R")) {
			front = "P_O_S_2";
		}
		else if (!strcmp(name, "P_O_F_2R")) {
			front = "P_O_F_2";
		}
		else if (!strcmp(name, "P_O_R_2R")) {
			front = "P_O_R_2";
		}
		else if (!strcmp(name, "P_O_N_2R")) {
			front = "P_O_N_2";
		}
		else if (!strcmp(name, "P_O_D_1R")) {
			front = "P_O_D_1";
		}
		else if (!strcmp(name, "P_O_D_2R")) {
			front = "P_O_D_2";
		}
		else if (!strcmp(name, "P_A_1R")) {
			front = "P_A_1";
		}
		return front;
	}
	else {
		if (!strcmp(name, "M_Z_1R")) {
			front = "M_Z_1";
		}
		else if (!strcmp(name, "M_S_1R")) {
			front = "M_S_1";
		}
		else if (!strcmp(name, "M_W_1R")) {
			front = "M_W_1";
		}
		else if (!strcmp(name, "M_R_1R")) {
			front = "M_R_1";
		}
		else if (!strcmp(name, "M_J_1BR")) {
			front = "M_J_1B";
		}
		else if (!strcmp(name, "M_J_1CR")) {
			front = "M_J_1C";
		}
		else if (!strcmp(name, "M_H_1R")) {
			front = "M_H_1";
		}
		else if (!strcmp(name, "M_H_2R")) {
			front = "M_H_2";
		}
		else if (!strcmp(name, "M_H_4R")) {
			front = "M_H_4";
		}
		else if (!strcmp(name, "M_H_5R")) {
			front = "M_H_5";
		}
		else if (!strcmp(name, "M_H_7R")) {
			front = "M_H_7";
		}
		else if (!strcmp(name, "M_H_8R")) {
			front = "M_H_8";
		}
		else if (!strcmp(name, "M_O_2R")) {
			front = "M_O_1";
		}
		else if (!strcmp(name, "M_I_2R")) {
			front = "M_I_2";
		}
		else if (!strcmp(name, "M_U_2R")) {
			front = "M_U_2";
		}
		else if (!strcmp(name, "M_C_1R")) {
			front = "M_C_1";
		}
		return front;
	}
}
