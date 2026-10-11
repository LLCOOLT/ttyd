#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/fontmgr.h"
#include "driver/dispdrv.h"
#include "mario/mario.h"
#include "mario/mario_pouch.h"
#include "memory.h"
#include <string.h>

typedef struct KpaScore {
	char str[8];
	u8 timer;
	u8 pad_9[3];
	Vec pos;
} KpaScore;

KpaScore* ksdp;
extern const Vec vec3_802fe200;
USER_FUNC(kpa_score_disp_main);
s32 kpa_score_disp_evt[] = {0x00010005, 0, 0x0001005B, (s32)kpa_score_disp_main, 0x00010009, 1, 6, 2, 1};

void kpaScoreDisp(void);

void kpaScoreDisp(void) {
	Mtx m;
	Mtx scale;
	s32 i;
	PSMTXScale(scale, 0.5f, 0.5f, 0.5f);
	FontDrawStart();
	FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
	for (i = 0; i < 50; i++) {
		if (ksdp[i].timer != 0) {
			PSMTXTrans(m, ksdp[i].pos.x, ksdp[i].pos.y, 300.0f);
			PSMTXConcat(m, scale, m);
			FontDrawStringMtx(m, ksdp[i].str);
		}
	}
}

USER_FUNC(kpa_score_disp_main) {
	s32 i;
	for (i = 0; i < 50; i++) {
		if (ksdp[i].timer != 0) {
			ksdp[i].pos.y += 1.0f;
			ksdp[i].timer--;
		}
	}
	dispEntry((CameraId)4, 0.0f, 2, (DispCallback)kpaScoreDisp, 0);
	return EVT_RETURN_DONE;
}

USER_FUNC(kpa_score_disp_init) {
	EventEntry* e;
	s32 i;
	e = evtEntryType(kpa_score_disp_evt, event->priority, 0, event->type);
	e->unitId = event->unitId;
	e->ownerNPC = event->ownerNPC;
	e->lwData[0] = event->lwData[0];
	e->lwData[1] = event->lwData[1];
	e->lwData[2] = event->lwData[2];
	e->lwData[3] = event->lwData[3];
	e->lwData[4] = event->lwData[4];
	e->lwData[5] = event->lwData[5];
	e->lwData[6] = event->lwData[6];
	e->lwData[7] = event->lwData[7];
	e->lwData[8] = event->lwData[8];
	e->lwData[9] = event->lwData[9];
	e->lwData[10] = event->lwData[10];
	e->lwData[11] = event->lwData[11];
	e->lwData[12] = event->lwData[12];
	e->lwData[13] = event->lwData[13];
	e->lwData[14] = event->lwData[14];
	e->lwData[15] = event->lwData[15];
	e->lfData[0] = event->lfData[0];
	e->lfData[1] = event->lfData[1];
	e->lfData[2] = event->lfData[2];
	e->uwBase = event->uwBase;
	e->ufBase = event->ufBase;
	ksdp = _mapAlloc(0x4B0);
	for (i = 0; i < 50; i++) {
		ksdp[i].str[0] = 0;
		ksdp[i].timer = 0;
		ksdp[i].pos = *(Vec*)&vec3_802fe200;
	}
	return EVT_RETURN_DONE;
}

void kpaAddCoin(s32 coins) {
	s32 score;
	if (((s32 (*)(s32))pouchAddKpaCoin)(coins)) {
		pouchAddKpaScore(1000);
	}
	score = coins * 500;
	if (score > 10000) {
		score = 10000;
	}
	pouchAddKpaScore(score);
}

static inline void kpaSetScoreStr(s32 score, Vec* pos) {
	s32 i;
	s32 n;
	s8 d0, d1, d2, d3, d4;
	s32 t;
	char* p;
	for (i = 0; i < 50; i++) {
		if (ksdp[i].timer == 0) {
			p = ksdp[i].str;
			n = 0;
			d0 = score / 10000;
			t = score % 10000;
			d1 = t / 1000;
			t %= 1000;
			d2 = t / 100;
			t %= 100;
			d3 = t / 10;
			d4 = t % 10;
			if (n != 0 || d0 != 0) { *p++ = d0 + '0'; n = 1; }
			if (n != 0 || d1 != 0) { *p++ = d1 + '0'; n++; }
			if (n != 0 || d2 != 0) { *p++ = d2 + '0'; n++; }
			if (n != 0 || d3 != 0) { *p++ = d3 + '0'; n++; }
			if (n != 0 || d4 != 0) { *p++ = d4 + '0'; n++; }
			ksdp[i].str[n] = 0;
			ksdp[i].timer = 30;
			ksdp[i].pos.x = pos->x - 0.5f * (10.0f * (f32)strlen(ksdp[i].str));
			ksdp[i].pos.y = 20.0f + pos->y;
			ksdp[i].pos.z = 0.0f;
			break;
		}
	}
}

void kpaAddCoinPos(s32 coins, Vec* pos) {
	s32 score;
	if (((s32 (*)(s32))pouchAddKpaCoin)(coins)) {
		pouchAddKpaScore(1000);
	}
	score = coins * 500;
	if (score > 10000) {
		score = 10000;
	}
	pouchAddKpaScore(score);
	kpaSetScoreStr(score, pos);
}

void kpaAddScore(s32 score) {
	if (score > 10000) {
		score = 10000;
	}
	pouchAddKpaScore(score);
}

void kpaAddScorePos(s32 score, Vec* pos) {
	if (score > 10000) {
		score = 10000;
	}
	pouchAddKpaScore(score);
	kpaSetScoreStr(score, pos);
}

USER_FUNC(kpa_chg_pose) {
	marioChgPose((const char*)evtGetValue(event, event->args[0]));
	return EVT_RETURN_DONE;
}

const Vec vec3_802fe200 = {0.0f, 0.0f, 0.0f};
