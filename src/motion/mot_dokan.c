#include "dolphin/types.h"
#include "mario/mario.h"
#include "mario/mario_cam.h"
#include "mario/mario_motion.h"
#include "mario/mario_party.h"
#include "mario/mario_sbr.h"
#include "party.h"
#include "system.h"

void partyChgRunMode(PartyEntry* party, s32 mode);
void partyShadowOff(PartyEntry* party);
void partyDokanEnd(s32 id, s32 type);
s32 partyEntry2Pos(s32 memberId, f32 x, f32 y, f32 z);
s32 partyEntryPos(s32 memberId, f32 x, f32 y, f32 z);
f32 toMovedirSimple(f32 angle);
void marioSlitForceCancel(void);

#define MW(m, off, T) (*(T*)((u8*)(m) + (off)))

static void _partyEntry(s32 flag) {
	MarioWork* mario;
	s32 i;
	s32 count;
	PartyEntry* party;
	s32 id;
	f32 off;
	s32 prev;
	f32 x, y, z;

	mario = marioGetPtr();
	if (mario->flags & MARIO_FLAG_BG_MODE) {
		return;
	}
	count = 0;
	if (partyGetPtr(mario->currPartySlotId[0]) != NULL) {
		count = 1;
	}
	if (partyGetPtr(mario->currPartySlotId[1]) != NULL) {
		count++;
	}
	for (i = 0; i < 2; i++) {
		if (mario->currPartySlotId[i] < 0) {
			prev = mario->prevPartyMemberId[i];
			x = mario->position.x;
			y = mario->position.y;
			z = mario->position.z;
			if (prev == 0) {
				continue;
			}
			if (i == 0) {
				id = partyEntryPos(prev, x, y, z);
			} else {
				id = partyEntry2Pos(prev, x, y, z);
			}
			if (id < 0) {
				continue;
			}
			mario->currPartySlotId[i] = id;
			party = partyGetPtr(id);
			partyChgRunMode(party, 10);
			if (flag == 0) {
				Vec zero = {0.0f, 0.0f, 0.0f};
				party->scale = zero;
			}
			party->flags |= 0x4000000;
			party->flags |= 0x2000000;
			if (count == 1) {
				off = 180.0f;
			} else {
				off = 120.0f;
			}
			party->flags2 &= ~1;
			party->displayDirectionTarget = revise360(mario->displayDirection + off);
			party->displayDirection = mario->displayDirection;
			party->moveDir = mario->moveDirection;
		} else {
			party = partyGetPtr(mario->currPartySlotId[i]);
			partyChgRunMode(party, 10);
			if (flag == 0) {
				Vec zero = {0.0f, 0.0f, 0.0f};
				party->scale = zero;
			}
			party->flags |= 0x4000000;
			party->flags |= 0x2000000;
			if (count == 1) {
				off = 180.0f;
			} else {
				off = -120.0f;
			}
			party->flags2 &= ~1;
			party->displayDirectionTarget = revise360(mario->displayDirection + off);
			party->displayDirection = mario->displayDirection;
			party->moveDir = mario->moveDirection;
		}
	}
}

void mot_dokan(void) {
	MarioWork* mario = marioGetPtr();
	PartyEntry* party;

	if (mario->trigFlags & 1) {
		mario->trigFlags &= ~1;
		mario->dispFlags |= 0x1000;
		mario->dispFlags |= 8;
		mario->dispFlags |= 0x100;
		MW(mario, 0x2A4, f32) = 0.0f;
		mario->wCamVal1 = mario->position.z;
		mario->multiTimer = 0;
		mario->airTimer = 0;
		mario->baseSpeed = 0.0f;
		if (MW(mario, 0x3E, s8) == 2) {
			mario->currSubMotionId = 10;
		} else if (MW(mario, 0x3E, s8) == 3) {
			mario->currSubMotionId = 10;
		} else if (MW(mario, 0x3E, s8) == 1) {
			marioPaperOn("p_dokan_y");
			marioChgPaper("PM_D_1A");
			marioChgPose("M_Z_1");
			marioPaperLightOff();
			mario->dispFlags |= 8;
			mario->dispFlags |= 0x100;
			mario->displayDirection = mario->displayDirectionTarget;
			mario->currSubMotionId = 20;
			MW(mario, 0x2A0, f32) = 0.0f;
			MW(mario, 0x2A0, f32) = 30.0f;
			{
				Vec v = {0.0f, 0.0f, 0.0f};
				mario->scale = v;
			}
			_partyEntry(1);
		} else if (MW(mario, 0x3E, s8) == 0) {
			_partyEntry(0);
			mario->currSubMotionId = 30;
		} else if (MW(mario, 0x3E, s8) == 5) {
			mario->dispFlags |= 0x1000;
			party = partyGetPtr(0);
			if (party != NULL) {
				partyShadowOff(party);
			}
			party = partyGetPtr(1);
			if (party != NULL) {
				partyShadowOff(party);
			}
			{
				Vec v0 = {0.0f, 0.0f, 0.0f};
				mario->dispOfs = v0;
			}
			{
				Vec v1 = {0.0f, 0.0f, 0.0f};
				mario->dispOfs2 = v1;
			}
			{
				Vec v2 = {0.0f, 0.0f, 0.0f};
				mario->rot = v2;
			}
			{
				Vec v3 = {0.0f, 16.0f, 0.0f};
				mario->rotOfs = v3;
			}
			marioSlitForceCancel();
			marioPaperOn("p_dokan_x");
			marioPaperLightOff();
			marioChgPaper("PM_D_1A");
			marioChgPose("M_Z_1");
			mario->displayDirection = mario->displayDirectionTarget;
			MW(mario, 0x2A0, f32) = 30.0f;
			mario->multiTimer = 20;
			mario->currSubMotionId = 0;
		} else if (MW(mario, 0x3E, s8) == 4) {
			{
				Vec v0 = {0.0f, 0.0f, 0.0f};
				mario->scale = v0;
			}
			{
				Vec v1 = {0.0f, 0.0f, 0.0f};
				mario->dispOfs = v1;
			}
			{
				Vec v2 = {0.0f, 0.0f, 0.0f};
				mario->dispOfs2 = v2;
			}
			{
				Vec v3 = {0.0f, 0.0f, 0.0f};
				mario->rot = v3;
			}
			{
				Vec v4 = {0.0f, 16.0f, 0.0f};
				mario->rotOfs = v4;
			}
			mario->directionView = toMovedir(mario->displayDirection);
			mario->moveDirection = mario->directionView;
			marioPaperOn("p_dokan_x");
			marioPaperLightOff();
			marioChgPaper("PM_D_1A");
			marioChgPose("M_Z_1");
			mario->displayDirection = mario->displayDirectionTarget;
			MW(mario, 0x2A0, f32) = 30.0f;
			mario->currSubMotionId = 40;
			_partyEntry(1);
			mario->dispFlags |= 0x1000;
			partyShadowOff(partyGetPtr(marioGetPartyId()));
			partyShadowOff(partyGetPtr(marioGetExtraPartyId()));
		}
	}

	switch (mario->currSubMotionId) {
	case 10:
		mario->displayDirection = revise360(mario->displayDirection + MW(mario, 0x2A0, f32));
		mario->scale.x += -0.005f;
		if (mario->scale.x < 0.0f) {
			mario->scale.x = 0.0f;
		}
		mario->scale.y = mario->scale.x;
		mario->scale.z = mario->scale.x;
		break;
	case 20: {
		Vec v = {0.0f, 0.0f, 0.0f};
		mario->scale = v;
		mario->currSubMotionId = 21;
		if (mario->flags & MARIO_FLAG_BG_MODE) {
			mario->dispOfs2.y = -2.0f;
		}
	}
	case 21:
		mario->displayDirection = revise360(mario->displayDirection + MW(mario, 0x2A0, f32));
		if (mario->flags & MARIO_FLAG_BG_MODE) {
			mario->scale.x += 0.03f;
			if (mario->scale.x >= 1.0f) {
				mario->scale.x = 1.0f;
			}
			mario->scale.y = mario->scale.x;
			mario->scale.z = mario->scale.x;
		} else {
			mario->scale.x += 0.05f;
			if (mario->scale.x >= 1.0f) {
				mario->scale.x = 1.0f;
			}
			mario->scale.y = mario->scale.x;
			mario->scale.z = mario->scale.x;
		}
		break;
	case 30:
		mario->displayDirection = revise360(mario->displayDirection + MW(mario, 0x2A0, f32));
		break;
	case 0:
		if (--MW(mario, 0x48, s32) <= 0) {
			mario->rot.x += MW(mario, 0x2A0, f32);
			mario->scale.x += -0.02f;
			if (mario->scale.x < 0.0f) {
				mario->scale.x = 0.0f;
			}
			mario->scale.y = mario->scale.x;
			mario->scale.z = mario->scale.x;
			mario->field_0xB4 = 16.0f * mario->scale.x;
			mario->dispOfs.y = 16.0f - mario->field_0xB4;
			mario->dispOfs.z = -3.0f;
		}
		break;
	case 40:
		mario->rot.x += MW(mario, 0x2A0, f32);
		mario->scale.x += 0.03f;
		if (mario->scale.x >= 1.0f) {
			mario->scale.x = 1.0f;
		}
		mario->scale.y = mario->scale.x;
		mario->scale.z = mario->scale.x;
		mario->field_0xB4 = 16.0f * mario->scale.x;
		mario->dispOfs.y = 16.0f - mario->field_0xB4;
		mario->dispOfs.z = -3.0f;
		party = partyGetPtr(marioGetPartyId());
		if (party != NULL) {
			party->position = mario->position;
			party->scale.x = mario->scale.x;
			party->scale.y = mario->scale.y;
			party->scale.z = mario->scale.z;
			party->field_8C = mario->field_0xB4;
			MW(party, 0x80, f32) = mario->dispOfs.y;
			MW(party, 0x84, f32) = mario->dispOfs.z;
		}
		party = partyGetPtr(marioGetExtraPartyId());
		if (party != NULL) {
			party->position = mario->position;
			party->scale.x = mario->scale.x;
			party->scale.y = mario->scale.y;
			party->scale.z = mario->scale.z;
			party->field_8C = mario->field_0xB4;
			MW(party, 0x80, f32) = mario->dispOfs.y;
			MW(party, 0x84, f32) = mario->dispOfs.z;
		}
		mario->camTarget.y = mario->position.y;
		break;
	case 100:
		if (MW(mario, 0x3E, s8) == 1) {
			mario->currSubMotionId = 110;
		} else if (MW(mario, 0x3E, s8) == 4) {
			marioUpdateCamPos();
			mario->rot.x = 0.0f;
			marioChgPaper("PM_D_1B");
			mario->multiTimer = 20;
			mario->currSubMotionId = 102;
			partyDokanEnd(marioGetPartyId(), MW(mario, 0x3E, s8));
			partyDokanEnd(marioGetExtraPartyId(), MW(mario, 0x3E, s8));
		} else if (MW(mario, 0x3E, s8) == 1) {
			mario->currSubMotionId = 101;
		} else if (MW(mario, 0x3E, s8) == 0) {
			marioUpdateCamPos();
			mario->currSubMotionId = 101;
		} else {
			mario->currSubMotionId = 102;
		}
		break;
	case 101:
		mario->displayDirection += MW(mario, 0x2A0, f32);
		if (mario->displayDirection >= 540.0f) {
			marioChgPaper("PM_D_1B");
			mario->multiTimer = 20;
			mario->currSubMotionId = 102;
			mario->rot.x = 0.0f;
			mario->displayDirectionTarget = revise360(180.0f + mario->displayDirectionTarget);
			mario->displayDirection = mario->displayDirectionTarget;
			mario->directionView = toMovedirSimple(mario->displayDirection);
			mario->moveDirection = mario->directionView;
			partyDokanEnd(marioGetPartyId(), MW(mario, 0x3E, s8));
			partyDokanEnd(marioGetExtraPartyId(), MW(mario, 0x3E, s8));
		}
		break;
	case 102:
		if (--MW(mario, 0x48, s32) <= 0) {
			mario->currSubMotionId = 103;
		}
		break;
	case 103: {
		MW(mario, 0xE0, Vec) = mario->position;
		{
			Vec v = {1.0f, 1.0f, 1.0f};
			mario->scale = v;
		}
		marioOfsRotReset();
		mario->dispFlags &= ~8;
		mario->dispFlags &= ~0x100;
		mario->dispFlags &= ~0x1000;
		marioPaperOff();
		marioChgMot(MARIO_MOTION_STAY);
		mario->displayDirection = revise360(mario->displayDirection);
		mario->displayDirectionTarget = mario->displayDirection;
		mario->directionView = toMovedirSimple(mario->displayDirection);
		mario->moveDirection = mario->directionView;
		if ((s32)MW(mario, 0x3E, u8) == 4) {
			camFollowYOn();
			mario->camTarget.y = mario->position.y;
		}
		mario->flags &= ~0x100;
		break;
	}
	}

	switch (mario->currSubMotionId) {
	case 110:
		if (!(mario->flags & MARIO_FLAG_BG_MODE)) {
			mario->camTarget.y = mario->position.y;
		}
		marioUpdateCamPos();
		camFollowYOff();
		mario->currSubMotionId = 111;
	case 111:
		mario->displayDirection += MW(mario, 0x2A0, f32);
		if (mario->displayDirection >= 540.0f) {
			if (!(mario->flags & MARIO_FLAG_BG_MODE)) {
				camFollowYOn();
			}
			marioChgPaper("PM_D_1B");
			mario->multiTimer = 20;
			mario->currSubMotionId = 112;
			mario->rot.x = 0.0f;
			mario->displayDirectionTarget = revise360(mario->displayDirection);
			mario->displayDirection = mario->displayDirectionTarget;
			mario->directionView = toMovedirSimple(mario->displayDirection);
			mario->moveDirection = mario->directionView;
			partyDokanEnd(marioGetPartyId(), MW(mario, 0x3E, s8));
			partyDokanEnd(marioGetExtraPartyId(), MW(mario, 0x3E, s8));
		}
		break;
	case 112:
		if (--MW(mario, 0x48, s32) <= 0) {
			mario->currSubMotionId = 113;
		}
		break;
	case 113: {
		MW(mario, 0xE0, Vec) = mario->position;
		{
			Vec v = {1.0f, 1.0f, 1.0f};
			mario->scale = v;
		}
		marioOfsRotReset();
		mario->dispFlags &= ~8;
		mario->dispFlags &= ~0x100;
		mario->dispFlags &= ~0x1000;
		marioPaperOff();
		marioChgMot(MARIO_MOTION_STAY);
		mario->displayDirection = revise360(mario->displayDirection);
		mario->displayDirectionTarget = mario->displayDirection;
		mario->directionView = toMovedirSimple(mario->displayDirection);
		mario->moveDirection = mario->directionView;
		if (!(mario->flags & MARIO_FLAG_BG_MODE)) {
			camFollowYOn();
		}
		mario->flags &= ~0x100;
		break;
	}
	}
}
