#include "mario/mariost.h"

#include "battle/battle.h"

#include "driver/animdrv.h"
#include "driver/arcdrv.h"
#include "driver/bgdrv.h"
#include "driver/camdrv.h"
#include "driver/casedrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "driver/envdrv.h"
#include "driver/extdrv.h"
#include "driver/fadedrv.h"
#include "driver/hitdrv.h"
#include "driver/icondrv.h"
#include "driver/imgdrv.h"
#include "driver/itemdrv.h"
#include "driver/lightdrv.h"
#include "driver/mapdrv.h"
#include "driver/mobjdrv.h"
#include "driver/msgdrv.h"
#include "driver/npcdrv.h"
#include "driver/offscreendrv.h"
#include "driver/seqdrv.h"
#include "driver/shadowdrv.h"
#include "driver/swdrv.h"
#include "driver/windowdrv.h"

#include "evt/evt_badgeshop.h"
#include "evt/evt_johoya.h"
#include "evt/evt_yuugijou.h"

#include "mario/mario.h"

#include "manager/arammgr.h"
#include "manager/cardmgr.h"
#include "manager/dvdmgr.h"
#include "manager/evtmgr.h"
#include "manager/filemgr.h"
#include "manager/fontmgr.h"
#include "manager/winmgr.h"

#include "sdk/DEMOInit.h"

#include "win/win_main.h"

#include "countdown.h"
#include "error_handler.h"
#include "memory.h"
#include "nameent.h"
#include "pmario_sound.h"
#include "romfont.h"
#include "statuswindow.h"
#include "system.h"

#include <dolphin/vi.h>
#include <string.h>

extern void DEMOPadInit(void);
extern void N_setupErrorHandler(void);
extern void SoundSetOutputMode(s32 mode);
extern void SoundOpenCover(void);
extern void SoundCloseCover(void);
#define OSIsRestart() ((OSGetResetCode() & 0x80000000) ? TRUE : FALSE)
extern BOOL g_bFirstSmartAlloc;

//.bss
GlobalWork marioSt;
OSThread DvdCheckThread;

//.sdata
GlobalWork* gp = &marioSt;
#pragma explicit_zero_data on
BOOL off_trg_669[4] = {FALSE, FALSE, FALSE, FALSE};
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_80410324_sdata = 0;
OSTime off_time_670[4] = {0, 0, 0, 0};
#pragma explicit_zero_data reset

//.sbss
OSTime none_key;
s32 _mariostSystemLevel;
BOOL DvdCheckTreadOn;

//.data
GXRenderModeObj sRMObjHReso = {
	VI_TVMODE_NTSC_INT, //viTVmode
	0x260, //fbWidth
	0x1C0, //efbHeight
	0x1C0, //xfbHeight
	0x1B, //viXOrigin
	0x10, //viYOrigin
	0x29A, //viWidth
	0x1C0, //viHeight
	VI_XFBMODE_DF, //xFBmode
	0, //field_rendering
	0, //aa
	6, 6, 6, 6, 6, 6, //pix 0
	6, 6, 6, 6, 6, 6, //pix 1
	6, 6, 6, 6, 6, 6, //pix 2
	6, 6, 6, 6, 6, 6, //pix 3
	8, 8, 10, 12, 10, 8, 8, //vfilter
};

GXRenderModeObj sRMObjHReso_prog = {
	VI_TVMODE_NTSC_PROG, //viTVmode
	0x260, //fbWidth
	0x1C0, //efbHeight
	0x1C0, //xfbHeight
	0x1B, //viXOrigin
	0x10, //viYOrigin
	0x29A, //viWidth
	0x1C0, //viHeight
	VI_XFBMODE_SF, //xFBmode
	0, //field_rendering
	0, //aa
	6, 6, 6, 6, 6, 6, //pix 0
	6, 6, 6, 6, 6, 6, //pix 1
	6, 6, 6, 6, 6, 6, //pix 2
	6, 6, 6, 6, 6, 6, //pix 3
	8, 8, 10, 12, 10, 8, 8, //vfilter
};

GXRenderModeObj GXNtsc480IntDfMarioSt = {
	VI_TVMODE_NTSC_INT, //viTVmode
	0x260, //fbWidth
	0x1E0, //efbHeight
	0x1E0, //xfbHeight
	0x1E, //viXOrigin
	0x0, //viYOrigin
	0x294, //viWidth
	0x1E0, //viHeight
	VI_XFBMODE_DF, //xFBmode
	0, //field_rendering
	0, //aa
	6, 6, 6, 6, 6, 6, //pix 0
	6, 6, 6, 6, 6, 6, //pix 1
	6, 6, 6, 6, 6, 6, //pix 2
	6, 6, 6, 6, 6, 6, //pix 3
	8, 8, 10, 12, 10, 8, 8, //vfilter
};

GXRenderModeObj GXNtsc480ProgMarioSt = {
	VI_TVMODE_NTSC_PROG, //viTVmode
	0x260, //fbWidth
	0x1E0, //efbHeight
	0x1E0, //xfbHeight
	0x1E, //viXOrigin
	0x0, //viYOrigin
	0x294, //viWidth
	0x1E0, //viHeight
	VI_XFBMODE_SF, //xFBmode
	0, //field_rendering
	0, //aa
	6, 6, 6, 6, 6, 6, //pix 0
	6, 6, 6, 6, 6, 6, //pix 1
	6, 6, 6, 6, 6, 6, //pix 2
	6, 6, 6, 6, 6, 6, //pix 3
	8, 8, 10, 12, 10, 8, 8, //vfilter
};

//local prototypes
void viPostCallback(u32 retraceCount);
void* gcDvdCheckThread(void* param);
void gcRumbleCheck(void);
void L_gcResetCheck(void);

static u8 stack_659[0x1000];

void marioStInit(void) {
	if (!OSIsRestart() || (OSGetResetCode() & OS_RESET_SHUTDOWN)) {
		DEMOInit(&GXNtsc480IntDfMarioSt);
	}
	else {
		switch (OSGetResetCode() & OS_RESET_HOTRESET) {
			case 0:
				DEMOInit(&GXNtsc480IntDfMarioSt);
				break;
			case 1:
				DEMOInit(&GXNtsc480ProgMarioSt);
				break;
		}
	}
	DEMOEnableGPHangWorkaround(5);
	N_setupErrorHandler();
	DEMOPadInit();
	GXSetCopyClear((GXColor){0, 0, 0, 0}, 0xFFFFFF);
	__GXSetIndirectMask(0);
	memset(gp, 0, sizeof(GlobalWork));
	gp->fbWidth = DEMOGetRenderModeObj()->fbWidth;
	gp->efbHeight = DEMOGetRenderModeObj()->efbHeight;
	gp->rumbleEnabled = 1;
	gp->unk1274 = 0;

	gp->retraceLocalTime = 0;
	gp->retraceDeltaTime = 0;
	gp->retraceTime = OSGetTime();

	gp->renderFieldTime = 0;
	gp->renderTime = 0;

	gp->systemLv3Time = 0;
	gp->systemLv2Time = 0;
	gp->systemLv1Time = 0;
	gp->systemLv0Time = 0;

	gp->mapFadeOutType = FADE_IN_BLACK;
	gp->mapFadeOutDuration = 300;
	gp->mapFadeInType = FADE_OUT_BLACK;
	gp->mapFadeInDuration = 300;
	gp->areaFadeOutType = FADE_IN_BLACK;
	gp->areaFadeOutDuration = 300;
	gp->areaFadeInType = FADE_OUT_BLACK;
	gp->areaFadeInDuration = 300;
	if ((OSGetFontEncode() == OS_FONT_ENCODE_SJIS) && !(gp->flags & 0x1000))
		gp->language = 0;
	else
		gp->language = 1;
	gp->framerate = 60;
	gp->systemLevelFlags = 0;
	badgeShop_init(); //Badge Shop
	yuugijou_init(); //Pianta Parlor
	johoya_init(); //?????
	gp->mapAlloc = __memAlloc(HEAP_DEFAULT, 660 * 1024);
	VISetPostRetraceCallback(viPostCallback);
	romFontInit();
	OSCreateThread(&DvdCheckThread, gcDvdCheckThread, NULL, (void*)((u32)&stack_659 + sizeof(stack_659)), sizeof(stack_659), 16, OS_THREAD_ATTR_DETACH);
	DvdCheckTreadOn = TRUE;
	OSResumeThread(&DvdCheckThread);
	DVDMgrInit();
	psndInit();
	aramMgrInit();
	fileInit();
	smartInit();
	dispInit();
	camInit();
	fontmgrInit();
	windowInit();
	mapInit();
	hitInit();
	itemInit();
	iconInit();
	fadeInit();
	bgInit();
	shadowInit();
	evtmgrInit();
	animInit();
	msgInit();
	npcInit();
	mobjInit();
	effInit();
	marioInit();
	caseInit();
	imgInit();
	lightInit();
	offscreenInit();
	arcInit();
	extInit();
	swInit();
	cardInit();
	winInit();
	statusWinInit();
	envInit();
	countDownInit();
	nameEntInit();
	winMgrInit();
	seqInit_MARIOSTORY();
	seqSetSeq(0, NULL, NULL);
	gp->unk1274 = 0;
	if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
		SoundSetOutputMode(0);
	}
	else {
		SoundSetOutputMode(1);
	}
}

#ifdef NONMATCHING
void marioStMain(void) {
	int i;

	while (gp->dvdError) {
		OSYieldThread();
	}
	makeKey();
	seqMain();
	cardMain();
	bgMain();
	shadowMain();
	animMain();
	battleMain();
	camMain();
	windowMain();
	mapMain();
	hitMain();
	evtmgrMain();
	mapDisp();
	marioMain();
	mobjMain();
	npcMain();
	fadeMain();
	imgMain();
	lightMain();
	offscreenMain();
	itemMain();
	caseMain();
	iconMain();
	extMain();
	psndMain();
	winMain();
	statusWinMain();
	envMain();
	countDownMain();
	nameEntMain();
	winMgrMain();
	effMain();
	L_gcResetCheck();
	if (gp->flags & 0x1000) {
		for (i = 0; i < 4; i++) {
			if (gp->dirs[i]) break;
			if (gp->button[i]) break;
			if (gp->stickX[i]) break;
			if (gp->stickY[i]) break;
			if (gp->substickX[i]) break;
			if (gp->substickY[i]) break;
			if (gp->triggerLeft[i]) break;
			if (gp->triggerRight[i]) break;
		}
		if (i >= 4) {
			if (OSTicksToSeconds(OSGetTime() - none_key) > 120 && (seqGetSeq() == 2 || seqGetSeq() == 4)) {
				gp->flags |= 0x2000;
			}
		}
		else {
			none_key = OSGetTime();
		}
	}
}
#endif

#ifdef NONMATCHING
void marioStDisp(void) {
	camDraw();
	g_bFirstSmartAlloc = FALSE;
}
#endif

#ifdef NONMATCHING
void marioStSystemLevel(s32 level) {
	switch (level) {
		case 0:
			_mariostSystemLevel = level;
			gp->systemLevelFlags &= ~0xF;
			evtStartAll(0xEF);
			break;
		case 1:
			_mariostSystemLevel = level;
			gp->systemLevelFlags &= ~0xE;
			gp->systemLevelFlags |= 1;
			evtStopAll(1);
			break;
		case 2:
			_mariostSystemLevel = level;
			gp->systemLevelFlags &= ~0xC;
			gp->systemLevelFlags |= 3;
			evtStopAll(2);
			break;
		case 3:
			_mariostSystemLevel = level;
			gp->systemLevelFlags &= ~8;
			gp->systemLevelFlags |= 7;
			evtStopAll(0x10);
			break;
		case 4:
			_mariostSystemLevel = level;
			gp->systemLevelFlags |= 0xF;
			evtStopAll(0xEF);
			break;
	}
}
#endif

#ifdef NONMATCHING
s32 marioStGetSystemLevel(void) {
	return gp->systemLevelFlags;
}
#endif

#ifdef NONMATCHING
void viPostCallback(u32 retraceCount) {
	OSTime time;
	u32 reset = PAD_BUTTON_B | PAD_BUTTON_X | PAD_BUTTON_START; //TODO: make sure it inlines right

	time = OSGetTime();
	gp->retraceDeltaTime = time - gp->retraceTime;
	gp->retraceLocalTime += gp->retraceDeltaTime;
	if (gp->retraceLocalTime > (OS_TIMER_CLOCK * (OSTime)359999999)) {
		gp->retraceLocalTime = (OS_TIMER_CLOCK * (OSTime)359999999);
	}
	if (!(gp->systemLevelFlags & 8)) {
		gp->systemLv3Time += gp->retraceDeltaTime;
	}
	if (!(gp->systemLevelFlags & 4)) {
		gp->systemLv2Time += gp->retraceDeltaTime;
	}
	if (!(gp->systemLevelFlags & 2)) {
		gp->systemLv1Time += gp->retraceDeltaTime;
	}
	if (!(gp->systemLevelFlags & 1)) {
		gp->systemLv0Time += gp->retraceDeltaTime;
	}
	if (!gp->dvdError && !winCheck()) {
		gp->renderTime += gp->retraceDeltaTime;
		if (!gp->inBattle) {
			gp->renderFieldTime += gp->retraceDeltaTime;
		}
	}
	gp->retraceTime = time;
	gp->retraceCount = retraceCount;
	if (battleDisableHResetCheck()) {
		gp->resetButtonDown = FALSE;
	}
	else {
		if (!gp->resetButtonDown) {
			if (OSGetResetButtonState()) {
				gp->resetButtonDown = TRUE;
			}
		}
		else {
			if (!OSGetResetButtonState()) {
				gp->resetType = 1;
			}
		}
		if (gp->keyDataValid) {
			if (OSIsRestart() && !gp->restartChecked) {
				if ((keyGetButton(0) & reset) == reset) {
					gp->resetType = 0;
					goto exitcheck;
				}
				else {
					gp->restartChecked = TRUE;
				}
			}
			if ((keyGetButton(0) & reset) == reset) {
				if (!gp->softResetWait) {
					gp->softResetWait = TRUE;
					gp->softResetTimeout = OSGetTime();
				}
				if (OSTicksToMilliseconds(OSGetTime() - gp->softResetTimeout) > 500) {
					gp->resetType = 1;
				}
			}
			else {
				gp->softResetWait = FALSE;
			}
			if (DVDGetDriveStatus() == -1) {
				gp->resetType = 0;
			}
		}
	}
exitcheck:
	gcRumbleCheck();
	psndMainInt();
}
#endif

//TODO: fuck up float conversions for 1:1 cuz this is cleaner
#ifdef NONMATCHING
void* gcDvdCheckThread(void* param) {
	const char* message;
	s32 msgId;
	s32 width;
	f32 xpos;
	Mtx44 mtx;

	while (1) {
		msgId = 0;
		switch (DVDGetDriveStatus()) {
			case DVD_STATE_COVER_OPEN:
				msgId = 5;
				gp->dvdError = TRUE;
				break;
			case DVD_STATE_NO_DISK:
				msgId = 6;
				gp->dvdError = TRUE;
				break;
			case DVD_STATE_WRONG_DISK:
				msgId = 6;
				gp->dvdError = TRUE;
				break;
			case DVD_STATE_RETRY:
				msgId = 7;
				gp->dvdError = TRUE;
				break;
			case DVD_RESULT_FATAL_ERROR:
				msgId = 8;
				gp->dvdError = TRUE;
				break;
			default:
				gp->dvdError = FALSE;
				break;
			case DVD_STATE_BUSY:
				break;
		}
		if (gp->dvdError) {
			SoundOpenCover();
		}
		else {
			SoundCloseCover();
		}
		if (gp->dvdError) {
			if (cardIsExec()) {
				gp->dvdError = FALSE;
			}
		}
		if (gp->dvdError) {
			DEMOBeforeRender();
			if (msgId) {
				message = romFontGetMessage(msgId);
				width = (f32)romFontGetWidth(message);
				MTXPerspective(mtx, 25.0f, 1.2666667f, 1.0f, 10000.0f);
				GXSetProjection(mtx, GX_PERSPECTIVE);
				xpos = -width / 2.0f;
				romFontPrintGX(xpos, 60.0f, 1.0f, &(GXColor){0xFF, 0xFF, 0xFF, 0xFF}, message);
			}
			DEMODoneRender();
			makeKey();
			L_gcResetCheck();
		}
		OSYieldThread();
	}
}
#endif

#ifdef NONMATCHING
void gcRumbleCheck(void) {
	static BOOL off_trg[4] = {FALSE, FALSE, FALSE, FALSE};
	static OSTime off_time[4] = {0, 0, 0, 0};
	OSTime now;
	OSTime diff;
	BOOL array[4] = {0};
	int i;

	now = OSGetTime();
	for (i = 0; i < 4; i++) {
		if (!gp->rumbleForcedOff[i]) {
			if (padGetRumbleStatus(i) == 1) {
				if (!gp->rumbleStart[i]) {
					gp->rumbleStart[i] = TRUE;
					gp->rumbleStartTime[i] = now;
				}
diff = (s32)now - (s32)gp->rumbleStartTime[i];
				if (OSTicksToMilliseconds(diff) > 30000) {
					if (!gp->rumbleForcedOffLatch[i]) {
						gp->rumbleForcedOffLatch[i] = TRUE;
						gp->rumbleForcedOff[i] = TRUE;
						gp->rumbleForcedOffTime[i] = now;
					}
				}
				off_trg[i] = FALSE;
			}
			else if (gp->rumbleStart[i]) {
				if (!off_trg[i]) {
					off_trg[i] = TRUE;
					off_time[i] = now;
				}
				if (off_trg[i]) {
diff = (s32)now - (s32)off_time[i];
					if (OSTicksToMilliseconds(diff) > 100) {
						off_trg[i] = FALSE;
						gp->rumbleStart[i] = FALSE;
					}
				}
			}
		}
		else {
diff = (s32)now - (s32)gp->rumbleForcedOffTime[i];
			if (OSTicksToMilliseconds(diff) > 30000) {
				gp->rumbleForcedOffLatch[i] = FALSE;
				gp->rumbleForcedOff[i] = FALSE;
				gp->rumbleStart[i] = FALSE;
			}
			array[i] = TRUE;
		}
		if (gp->dvdError) {
			array[i] = TRUE;
		}
		if (gp->systemLevelFlags != 0U) {
			array[i] = TRUE;
		}
		if (array[i]) {
			gp->rumbleHardStop[i] = TRUE;
		}
		else {
			gp->rumbleHardStop[i] = FALSE;
		}
	}
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
void L_gcResetCheck(void) {
	u32 code;

	if (gp->resetType) {
		VISetBlack(TRUE);
		VIFlush();
		VIWaitForRetrace();
		VIWaitForRetrace();
		VIWaitForRetrace();
		psndExit();
		DVDMgrDelete();
		if ((OSGetCurrentThread() != &DvdCheckThread) && DvdCheckTreadOn) {
			OSCancelThread(&DvdCheckThread);
			DvdCheckTreadOn = FALSE;
		}
		while (cardIsExec()) {
			cardMain();
			VIWaitForRetrace();
		}
		if (gp->resetType != 2) {
			if (!(gp->flags & 4)) {
				code = OS_RESET_SHUTDOWN;
			}
			else {
				if (!(gp->flags & 8)) {
					code = OS_RESET_RESTART;
				}
				else {
					code = OS_RESET_HOTRESET;
				}
			}
			OSResetSystem(OS_RESET_RESTART, code, FALSE);
		}
		else {
			OSResetSystem(OS_RESET_HOTRESET, 0, TRUE);
		}
		while (1) {}
	}
}
#endif
#pragma dont_inline reset


// prototypes for asm stopgap forward references
void L_gcResetCheck(void);
void gcRumbleCheck(void);
void* gcDvdCheckThread(void* param);
void viPostCallback(u32 retraceCount);
s32 marioStGetSystemLevel(void);
void marioStSystemLevel(s32 level);
void marioStDisp(void);
void marioStMain(void);
#ifndef NONMATCHING
// ASM-STOPGAP: marioStMain (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c47e0[3] = { 0.0f, 0.0f, 0.0f };
#pragma force_active on
__declspec(section ".rodata") const f64 double_to_int_802c47f0 = 4503601774854144;
#pragma force_active reset
#pragma force_active on
__declspec(section ".sdata2") const u32 dat_8041a250 = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_25_8041a254 = 25.0f;
__declspec(section ".sdata2") const f32 float_1p2667_8041a258 = 1.2666667f;
__declspec(section ".sdata2") const f32 float_1_8041a25c = 1.0f;
__declspec(section ".sdata2") const f32 float_10000_8041a260 = 10000.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041a264 = 0.5f;
__declspec(section ".sdata2") const f32 float_60_8041a268 = 60.0f;
#pragma explicit_zero_data on
__declspec(section ".sdata2") const f32 float_0_8041a26c = 0.0f;
#pragma explicit_zero_data reset

void* gcDvdCheckThread(void* param);
#pragma force_active on
__declspec(section ".data") static void* jumptable_8030ACA8[] = {
    (char*)gcDvdCheckThread + 0x90,
    (char*)gcDvdCheckThread + 0xA4,
    (char*)gcDvdCheckThread + 0xB0,
    (char*)gcDvdCheckThread + 0xA4,
    (char*)gcDvdCheckThread + 0xA4,
    (char*)gcDvdCheckThread + 0x54,
    (char*)gcDvdCheckThread + 0x40,
    (char*)gcDvdCheckThread + 0x68,
    (char*)gcDvdCheckThread + 0xA4,
    (char*)gcDvdCheckThread + 0xA4,
    (char*)gcDvdCheckThread + 0xA4,
    (char*)gcDvdCheckThread + 0xA4,
    (char*)gcDvdCheckThread + 0x7C,
};
void __div2i();
asm void L_gcResetCheck(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, gp(r13)
	lwz r0, 0x1278(r3)
	cmpwi r0, 0x0
	beq @1
	li r3, 0x1
	bl VISetBlack
	bl VIFlush
	bl VIWaitForRetrace
	bl VIWaitForRetrace
	bl VIWaitForRetrace
	bl psndExit
	bl DVDMgrDelete
	bl OSGetCurrentThread
	lis r4, stack_659+0x1000@ha
	addi r4, r4, stack_659+0x1000@l
	cmplw r3, r4
	beq @2
	lwz r0, DvdCheckTreadOn(r13)
	cmpwi r0, 0x0
	beq @2
	mr r3, r4
	bl OSCancelThread
	li r0, 0x0
	stw r0, DvdCheckTreadOn(r13)
	b @2
	@3:
	bl cardMain
	bl VIWaitForRetrace
	@2:
	bl cardIsExec
	cmpwi r3, 0x0
	bne @3
	lwz r3, gp(r13)
	lwz r0, 0x1278(r3)
	cmpwi r0, 0x2
	beq @4
	lwz r3, 0x0(r3)
	rlwinm. r0, r3, 0, 29, 29
	bne @5
	li r4, 0x2
	b @6
	@5:
	rlwinm. r0, r3, 0, 28, 28
	bne @7
	li r4, 0x0
	b @6
	@7:
	li r4, 0x1
	@6:
	li r3, 0x0
	li r5, 0x0
	bl OSResetSystem
	b @8
	@4:
	li r3, 0x1
	li r4, 0x0
	li r5, 0x1
	bl OSResetSystem
	@8:
	b @8
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void gcRumbleCheck(void) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	lis r3, vec3_802c47e0@ha
	stw r0, 0x44(r1)
	addi r6, r3, vec3_802c47e0@l
	stmw r24, 0x20(r1)
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	lwz r3, 0x8(r6)
	lwz r0, 0xc(r6)
	stw r5, 0x8(r1)
	stw r4, 0xc(r1)
	stw r3, 0x10(r1)
	stw r0, 0x14(r1)
	bl OSGetTime
	mr r30, r4
	mr r31, r3
	addi r26, r1, 0x8
	li r24, 0x0
	li r29, 0x0
	la r28, off_trg_669(r13)
	la r27, off_time_670(r13)
	@1:
	lwz r5, gp(r13)
	add r25, r5, r24
	lbz r0, 0x12e8(r25)
	cmplwi r0, 0x0
	bne @2
	mr r3, r24
	bl padGetRumbleStatus
	clrlwi r0, r3, 24
	cmplwi r0, 0x1
	bne @3
	lwz r4, gp(r13)
	addi r5, r24, 0x12c0
	lbzx r0, r4, r5
	cmplwi r0, 0x0
	bne @4
	li r3, 0x1
	addi r0, r29, 0x12c8
	stbx r3, r4, r5
	lwz r3, gp(r13)
	add r3, r3, r0
	stw r30, 0x4(r3)
	stw r31, 0x0(r3)
	@4:
	lis r4, 0x8000
	lis r3, 0x1062
	lwz r0, 0xf8(r4)
	addi r3, r3, 0x4dd3
	lwz r25, gp(r13)
	addi r4, r29, 0x12c8
	srwi r0, r0, 2
	li r5, 0x0
	mulhwu r0, r3, r0
	add r3, r25, r4
	lwz r3, 0x4(r3)
	subf r4, r3, r30
	srawi r3, r4, 31
	srwi r6, r0, 6
	bl __div2i
	li r0, 0x0
	li r6, 0x7530
	xoris r5, r0, 0x8000
	xoris r3, r3, 0x8000
	subfc r0, r4, r6
	subfe r3, r3, r5
	subfe r3, r5, r5
	neg. r3, r3
	beq @5
	addi r4, r24, 0x12ec
	lbzx r0, r25, r4
	cmplwi r0, 0x0
	bne @5
	li r5, 0x1
	addi r3, r24, 0x12e8
	stbx r5, r25, r4
	addi r0, r29, 0x12f0
	lwz r4, gp(r13)
	stbx r5, r4, r3
	lwz r3, gp(r13)
	add r3, r3, r0
	stw r30, 0x4(r3)
	stw r31, 0x0(r3)
	@5:
	li r0, 0x0
	stw r0, 0x0(r28)
	b @6
	@3:
	lwz r3, gp(r13)
	addi r0, r24, 0x12c0
	lbzx r0, r3, r0
	cmplwi r0, 0x0
	beq @6
	lwz r0, 0x0(r28)
	cmpwi r0, 0x0
	bne @7
	stw r30, 0x4(r27)
	li r0, 0x1
	stw r0, 0x0(r28)
	stw r31, 0x0(r27)
	@7:
	lwz r0, 0x0(r28)
	cmpwi r0, 0x0
	beq @6
	lis r4, 0x8000
	lis r3, 0x1062
	lwz r0, 0xf8(r4)
	addi r3, r3, 0x4dd3
	lwz r4, 0x4(r27)
	li r5, 0x0
	srwi r0, r0, 2
	mulhwu r0, r3, r0
	subf r4, r4, r30
	srawi r3, r4, 31
	srwi r6, r0, 6
	bl __div2i
	li r0, 0x64
	li r6, 0x0
	xoris r5, r6, 0x8000
	xoris r3, r3, 0x8000
	subfc r0, r4, r0
	subfe r3, r3, r5
	subfe r3, r5, r5
	neg. r3, r3
	beq @6
	stw r6, 0x0(r28)
	addi r0, r24, 0x12c0
	lwz r3, gp(r13)
	stbx r6, r3, r0
	b @6
	@2:
	lis r4, 0x8000
	lis r3, 0x1062
	lwz r0, 0xf8(r4)
	addi r4, r29, 0x12f0
	add r4, r5, r4
	addi r3, r3, 0x4dd3
	srwi r0, r0, 2
	lwz r4, 0x4(r4)
	mulhwu r0, r3, r0
	li r5, 0x0
	subf r4, r4, r30
	srawi r3, r4, 31
	srwi r6, r0, 6
	bl __div2i
	li r0, 0x7530
	li r6, 0x0
	xoris r5, r6, 0x8000
	xoris r3, r3, 0x8000
	subfc r0, r4, r0
	subfe r3, r3, r5
	subfe r3, r5, r5
	neg. r3, r3
	beq @8
	stb r6, 0x12ec(r25)
	addi r3, r24, 0x12e8
	addi r0, r24, 0x12c0
	lwz r4, gp(r13)
	stbx r6, r4, r3
	lwz r3, gp(r13)
	stbx r6, r3, r0
	@8:
	li r0, 0x1
	stw r0, 0x0(r26)
	@6:
	lwz r3, gp(r13)
	lwz r0, 0x10(r3)
	cmpwi r0, 0x0
	beq @9
	li r0, 0x1
	stw r0, 0x0(r26)
	@9:
	lwz r3, gp(r13)
	lwz r0, 0x18(r3)
	cmplwi r0, 0x0
	beq @10
	li r0, 0x1
	stw r0, 0x0(r26)
	@10:
	lwz r0, 0x0(r26)
	cmpwi r0, 0x0
	beq @11
	lwz r3, gp(r13)
	addi r0, r24, 0x1310
	li r4, 0x1
	stbx r4, r3, r0
	b @12
	@11:
	lwz r3, gp(r13)
	addi r0, r24, 0x1310
	li r4, 0x0
	stbx r4, r3, r0
	@12:
	addi r24, r24, 0x1
	addi r28, r28, 0x4
	cmpwi r24, 0x4
	addi r27, r27, 0x8
	addi r26, r26, 0x4
	addi r29, r29, 0x8
	blt @1
	lmw r24, 0x20(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void* gcDvdCheckThread(void* param) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stw r31, 0x6c(r1)
	stw r30, 0x68(r1)
	@1:
	li r31, 0x0
	bl DVDGetDriveStatus
	addi r0, r3, 0x1
	cmplwi r0, 0xc
	bgt @2
	lis r3, jumptable_8030ACA8@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_8030ACA8@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@3:
	lwz r3, gp(r13)
	li r0, 0x1
	li r31, 0x5
	stw r0, 0x10(r3)
	b @4
	@5:
	lwz r3, gp(r13)
	li r0, 0x1
	li r31, 0x6
	stw r0, 0x10(r3)
	b @4
	@6:
	lwz r3, gp(r13)
	li r0, 0x1
	li r31, 0x6
	stw r0, 0x10(r3)
	b @4
	@7:
	lwz r3, gp(r13)
	li r0, 0x1
	li r31, 0x7
	stw r0, 0x10(r3)
	b @4
	@8:
	lwz r3, gp(r13)
	li r0, 0x1
	li r31, 0x8
	stw r0, 0x10(r3)
	b @4
	@2:
	lwz r3, gp(r13)
	li r0, 0x0
	stw r0, 0x10(r3)
	@4:
	lwz r3, gp(r13)
	lwz r0, 0x10(r3)
	cmpwi r0, 0x0
	beq @9
	bl SoundOpenCover
	b @10
	@9:
	bl SoundCloseCover
	@10:
	lwz r3, gp(r13)
	lwz r0, 0x10(r3)
	cmpwi r0, 0x0
	beq @11
	bl cardIsExec
	cmpwi r3, 0x0
	beq @11
	lwz r3, gp(r13)
	li r0, 0x0
	stw r0, 0x10(r3)
	@11:
	lwz r3, gp(r13)
	lwz r0, 0x10(r3)
	cmpwi r0, 0x0
	beq @12
	bl DEMOBeforeRender
	cmpwi r31, 0x0
	beq @13
	mr r3, r31
	bl romFontGetMessage
	mr r31, r3
	bl romFontGetWidth
	xoris r3, r3, 0x8000
	lis r0, 0x4330
	stw r3, 0x54(r1)
	lis r4, double_to_int_802c47f0@ha
	lfd f3, double_to_int_802c47f0@l(r4)
	addi r3, r1, 0xc
	stw r0, 0x50(r1)
	lfs f1, float_25_8041a254(r2)
	lfd f0, 0x50(r1)
	lfs f2, float_1p2667_8041a258(r2)
	fsubs f0, f0, f3
	lfs f3, float_1_8041a25c(r2)
	lfs f4, float_10000_8041a260(r2)
	fctiwz f0, f0
	stfd f0, 0x58(r1)
	lwz r30, 0x5c(r1)
	bl C_MTXPerspective
	addi r3, r1, 0xc
	li r4, 0x0
	bl GXSetProjection
	neg r3, r30
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lis r4, double_to_int_802c47f0@ha
	stw r3, 0x64(r1)
	addi r5, r4, double_to_int_802c47f0@l
	lwz r6, dat_8041a250(r2)
	mr r4, r31
	stw r0, 0x60(r1)
	addi r3, r1, 0x8
	lfd f2, 0x0(r5)
	lfd f1, 0x60(r1)
	lfs f0, float_0p5_8041a264(r2)
	fsubs f1, f1, f2
	stw r6, 0x8(r1)
	lfs f2, float_60_8041a268(r2)
	lfs f3, float_1_8041a25c(r2)
	fmuls f1, f1, f0
	crset 6
	bl romFontPrintGX
	@13:
	bl DEMODoneRender
	bl makeKey
	bl L_gcResetCheck
	@12:
	bl OSYieldThread
	b @1
}

asm void viPostCallback(u32 retraceCount) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	bl OSGetTime
	lwz r6, gp(r13)
	mr r30, r4
	mr r31, r3
	lis r5, 0x1575
	lwz r0, 0x34(r6)
	lis r3, 0x8000
	lwz r4, 0x30(r6)
	addi r5, r5, 0x29ff
	subfc r0, r0, r30
	li r7, 0x0
	stw r0, 0x2c(r6)
	subfe r0, r4, r31
	mullw r4, r7, r5
	stw r0, 0x28(r6)
	lwz r10, gp(r13)
	lwz r9, 0x24(r10)
	lwz r0, 0x2c(r10)
	lwz r8, 0x20(r10)
	lwz r6, 0x28(r10)
	addc r0, r9, r0
	stw r0, 0x24(r10)
	adde r0, r8, r6
	stw r0, 0x20(r10)
	lwz r0, 0xf8(r3)
	lwz r10, gp(r13)
	srwi r8, r0, 2
	mulhwu r0, r8, r5
	lwz r3, 0x20(r10)
	lwz r9, 0x24(r10)
	xoris r3, r3, 0x8000
	mullw r6, r8, r5
	add r5, r0, r4
	mullw r4, r8, r7
	subfc r0, r9, r6
	add r4, r5, r4
	xoris r0, r4, 0x8000
	subfe r3, r3, r0
	subfe r3, r0, r0
	neg. r3, r3
	beq @1
	stw r6, 0x24(r10)
	stw r4, 0x20(r10)
	@1:
	lwz r6, gp(r13)
	lwz r0, 0x18(r6)
	rlwinm. r0, r0, 0, 28, 28
	bne @2
	lwz r5, 0x64(r6)
	lwz r0, 0x2c(r6)
	lwz r4, 0x60(r6)
	lwz r3, 0x28(r6)
	addc r0, r5, r0
	stw r0, 0x64(r6)
	adde r0, r4, r3
	stw r0, 0x60(r6)
	@2:
	lwz r6, gp(r13)
	lwz r0, 0x18(r6)
	rlwinm. r0, r0, 0, 29, 29
	bne @3
	lwz r5, 0x5c(r6)
	lwz r0, 0x2c(r6)
	lwz r4, 0x58(r6)
	lwz r3, 0x28(r6)
	addc r0, r5, r0
	stw r0, 0x5c(r6)
	adde r0, r4, r3
	stw r0, 0x58(r6)
	@3:
	lwz r6, gp(r13)
	lwz r0, 0x18(r6)
	rlwinm. r0, r0, 0, 30, 30
	bne @4
	lwz r5, 0x54(r6)
	lwz r0, 0x2c(r6)
	lwz r4, 0x50(r6)
	lwz r3, 0x28(r6)
	addc r0, r5, r0
	stw r0, 0x54(r6)
	adde r0, r4, r3
	stw r0, 0x50(r6)
	@4:
	lwz r6, gp(r13)
	lwz r0, 0x18(r6)
	clrlwi. r0, r0, 31
	bne @5
	lwz r5, 0x4c(r6)
	lwz r0, 0x2c(r6)
	lwz r4, 0x48(r6)
	lwz r3, 0x28(r6)
	addc r0, r5, r0
	stw r0, 0x4c(r6)
	adde r0, r4, r3
	stw r0, 0x48(r6)
	@5:
	lwz r3, gp(r13)
	lwz r0, 0x10(r3)
	cmpwi r0, 0x0
	bne @6
	bl winCheck
	cmpwi r3, 0x0
	bne @6
	lwz r6, gp(r13)
	lwz r5, 0x3c(r6)
	lwz r0, 0x2c(r6)
	lwz r4, 0x38(r6)
	lwz r3, 0x28(r6)
	addc r0, r5, r0
	stw r0, 0x3c(r6)
	adde r0, r4, r3
	stw r0, 0x38(r6)
	lwz r6, gp(r13)
	lwz r0, 0x14(r6)
	cmpwi r0, 0x0
	bne @6
	lwz r5, 0x44(r6)
	lwz r0, 0x2c(r6)
	lwz r4, 0x40(r6)
	lwz r3, 0x28(r6)
	addc r0, r5, r0
	stw r0, 0x44(r6)
	adde r0, r4, r3
	stw r0, 0x40(r6)
	@6:
	lwz r3, gp(r13)
	stw r30, 0x34(r3)
	stw r31, 0x30(r3)
	lwz r3, gp(r13)
	stw r29, 0x1c(r3)
	bl battleDisableHResetCheck
	cmpwi r3, 0x0
	beq @7
	lwz r3, gp(r13)
	li r0, 0x0
	stw r0, 0x127c(r3)
	b @8
	@7:
	lwz r3, gp(r13)
	lwz r0, 0x127c(r3)
	cmpwi r0, 0x0
	bne @9
	bl OSGetResetButtonState
	cmpwi r3, 0x0
	beq @10
	lwz r3, gp(r13)
	li r0, 0x1
	stw r0, 0x127c(r3)
	b @10
	@9:
	bl OSGetResetButtonState
	cmpwi r3, 0x0
	bne @10
	lwz r3, gp(r13)
	li r0, 0x1
	stw r0, 0x1278(r3)
	@10:
	lwz r3, gp(r13)
	lwz r0, 0x1324(r3)
	cmpwi r0, 0x0
	beq @8
	bl OSGetResetCode
	srwi. r0, r3, 31
	beq @11
	lwz r3, gp(r13)
	lwz r0, 0x1290(r3)
	cmpwi r0, 0x0
	bne @11
	li r3, 0x0
	bl keyGetButton
	andi. r0, r3, 0x1600
	cmplwi r0, 0x1600
	bne @12
	lwz r3, gp(r13)
	li r0, 0x0
	stw r0, 0x1278(r3)
	b @8
	@12:
	lwz r3, gp(r13)
	li r0, 0x1
	stw r0, 0x1290(r3)
	@11:
	li r3, 0x0
	bl keyGetButton
	andi. r0, r3, 0x1600
	cmplwi r0, 0x1600
	bne @13
	lwz r3, gp(r13)
	lwz r0, 0x1280(r3)
	cmpwi r0, 0x0
	bne @14
	li r0, 0x1
	stw r0, 0x1280(r3)
	bl OSGetTime
	lwz r5, gp(r13)
	stw r4, 0x128c(r5)
	stw r3, 0x1288(r5)
	@14:
	bl OSGetTime
	lis r5, 0x8000
	lwz r29, gp(r13)
	lwz r0, 0xf8(r5)
	lis r5, 0x1062
	lwz r7, 0x128c(r29)
	addi r5, r5, 0x4dd3
	srwi r0, r0, 2
	lwz r6, 0x1288(r29)
	mulhwu r0, r5, r0
	subfc r4, r7, r4
	subfe r3, r6, r3
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	li r0, 0x0
	li r6, 0x1f4
	xoris r5, r0, 0x8000
	xoris r3, r3, 0x8000
	subfc r0, r4, r6
	subfe r3, r3, r5
	subfe r3, r5, r5
	neg. r3, r3
	beq @15
	li r0, 0x1
	stw r0, 0x1278(r29)
	b @15
	@13:
	lwz r3, gp(r13)
	li r0, 0x0
	stw r0, 0x1280(r3)
	@15:
	bl DVDGetDriveStatus
	cmpwi r3, -0x1
	bne @8
	lwz r3, gp(r13)
	li r0, 0x0
	stw r0, 0x1278(r3)
	@8:
	bl gcRumbleCheck
	bl psndMainInt
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 marioStGetSystemLevel(void) {
	nofralloc
	lwz r3, gp(r13)
	lwz r3, 0x18(r3)
	blr
}

asm void marioStSystemLevel(s32 level) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	cmpwi r3, 0x2
	stw r0, 0x14(r1)
	beq @1
	bge @2
	cmpwi r3, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r3, 0x4
	beq @6
	bge @5
	b @7
	@3:
	stw r3, _mariostSystemLevel(r13)
	li r3, 0xef
	lwz r4, gp(r13)
	lwz r0, 0x18(r4)
	clrrwi r0, r0, 4
	stw r0, 0x18(r4)
	bl evtStartAll
	b @5
	@4:
	stw r3, _mariostSystemLevel(r13)
	li r3, 0x1
	lwz r4, gp(r13)
	lwz r0, 0x18(r4)
	rlwinm r0, r0, 0, 31, 27
	stw r0, 0x18(r4)
	lwz r4, gp(r13)
	lwz r0, 0x18(r4)
	ori r0, r0, 0x1
	stw r0, 0x18(r4)
	bl evtStopAll
	b @5
	@1:
	stw r3, _mariostSystemLevel(r13)
	li r3, 0x2
	lwz r4, gp(r13)
	lwz r0, 0x18(r4)
	rlwinm r0, r0, 0, 30, 27
	stw r0, 0x18(r4)
	lwz r4, gp(r13)
	lwz r0, 0x18(r4)
	ori r0, r0, 0x3
	stw r0, 0x18(r4)
	bl evtStopAll
	b @5
	@7:
	stw r3, _mariostSystemLevel(r13)
	li r3, 0x10
	lwz r4, gp(r13)
	lwz r0, 0x18(r4)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x18(r4)
	lwz r4, gp(r13)
	lwz r0, 0x18(r4)
	ori r0, r0, 0x7
	stw r0, 0x18(r4)
	bl evtStopAll
	b @5
	@6:
	stw r3, _mariostSystemLevel(r13)
	li r3, 0xef
	lwz r4, gp(r13)
	lwz r0, 0x18(r4)
	ori r0, r0, 0xf
	stw r0, 0x18(r4)
	bl evtStopAll
	@5:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void marioStDisp(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl camDraw
	li r0, 0x0
	stw r0, g_bFirstSmartAlloc(r13)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void marioStMain(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	b @1
	@2:
	bl OSYieldThread
	@1:
	lwz r3, gp(r13)
	lwz r0, 0x10(r3)
	cmpwi r0, 0x0
	bne @2
	bl makeKey
	bl seqMain
	bl cardMain
	bl bgMain
	bl shadowMain
	bl animMain
	bl battleMain
	bl camMain
	bl windowMain
	bl mapMain
	bl hitMain
	bl evtmgrMain
	bl mapDisp
	bl marioMain
	bl mobjMain
	bl npcMain
	bl fadeMain
	bl imgMain
	bl lightMain
	bl offscreenMain
	bl itemMain
	bl caseMain
	bl iconMain
	bl extMain
	bl psndMain
	bl winMain
	bl statusWinMain
	bl envMain
	bl countDownMain
	bl nameEntMain
	bl winMgrMain
	bl effMain
	bl L_gcResetCheck
	lwz r4, gp(r13)
	lwz r0, 0x0(r4)
	rlwinm. r0, r0, 0, 19, 19
	beq @3
	li r0, 0x2
	mr r3, r4
	li r5, 0x0
	mtctr r0
	@4:
	lwz r0, 0x1378(r4)
	cmplwi r0, 0x0
	bne @5
	lwz r0, 0x1328(r4)
	cmplwi r0, 0x0
	bne @5
	lbz r0, 0x13b8(r3)
	extsb. r0, r0
	bne @5
	lbz r0, 0x13bc(r3)
	extsb. r0, r0
	bne @5
	lbz r0, 0x13c0(r3)
	extsb. r0, r0
	bne @5
	lbz r0, 0x13c4(r3)
	extsb. r0, r0
	bne @5
	lbz r0, 0x13c8(r3)
	cmplwi r0, 0x0
	bne @5
	lbz r0, 0x13cc(r3)
	cmplwi r0, 0x0
	bne @5
	lwz r0, 0x137c(r4)
	addi r5, r5, 0x1
	cmplwi r0, 0x0
	bne @5
	lwz r0, 0x132c(r4)
	cmplwi r0, 0x0
	bne @5
	lbz r0, 0x13b9(r3)
	extsb. r0, r0
	bne @5
	lbz r0, 0x13bd(r3)
	extsb. r0, r0
	bne @5
	lbz r0, 0x13c1(r3)
	extsb. r0, r0
	bne @5
	lbz r0, 0x13c5(r3)
	extsb. r0, r0
	bne @5
	lbz r0, 0x13c9(r3)
	cmplwi r0, 0x0
	bne @5
	lbz r0, 0x13cd(r3)
	cmplwi r0, 0x0
	bne @5
	addi r4, r4, 0x8
	addi r3, r3, 0x2
	addi r5, r5, 0x1
	bdnz @4
	@5:
	cmpwi r5, 0x4
	blt @6
	bl OSGetTime
	lwz r6, none_key+0x4(r13)
	lis r5, 0x8000
	lwz r0, 0xf8(r5)
	li r5, 0x0
	subfc r4, r6, r4
	lwz r7, none_key(r13)
	srwi r6, r0, 2
	subfe r3, r7, r3
	bl __div2i
	li r0, 0x0
	li r6, 0x78
	xoris r5, r0, 0x8000
	xoris r3, r3, 0x8000
	subfc r0, r4, r6
	subfe r3, r3, r5
	subfe r3, r5, r5
	neg. r3, r3
	beq @3
	bl seqGetSeq
	cmpwi r3, 0x2
	beq @7
	bl seqGetSeq
	cmpwi r3, 0x4
	bne @3
	@7:
	lwz r3, gp(r13)
	lwz r0, 0x0(r3)
	ori r0, r0, 0x2000
	stw r0, 0x0(r3)
	b @3
	@6:
	bl OSGetTime
	stw r4, none_key+0x4(r13)
	stw r3, none_key(r13)
	@3:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif
