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
#ifndef NONMATCHING
__declspec(section ".sdata2") u32 gap_10_80422FCC_sbss2[1];
__declspec(section ".rodata") extern const f32 vec3_802c47e0[3];
#define val (sym)

#endif

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
#ifndef NONMATCHING
#pragma explicit_zero_data on
#endif
BOOL off_trg_669[4] = {FALSE, FALSE, FALSE, FALSE};
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_80410324_sdata = 0;
OSTime off_time_670[4] = {0, 0, 0, 0};
#ifndef NONMATCHING
#pragma explicit_zero_data reset
#endif

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

void marioStDisp(void) {
	camDraw();
	g_bFirstSmartAlloc = FALSE;
}

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

s32 marioStGetSystemLevel(void) {
	return gp->systemLevelFlags;
}

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

//TODO: fuck up float conversions for 1:1 cuz this is cleaner
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
#ifdef NONMATCHING
				MTXPerspective(mtx, 25.0f, 1.2666667f, 1.0f, 10000.0f);
#endif
#ifndef NONMATCHING
				MTXPerspective(mtx, 25.0f, 1.2666667f, 1.0f, 10000.0f);
#endif
				GXSetProjection(mtx, GX_PERSPECTIVE);
				xpos = -width / 2.0f;
#ifdef NONMATCHING
				romFontPrintGX(xpos, 60.0f, 1.0f, &(GXColor){0xFF, 0xFF, 0xFF, 0xFF}, message);
#endif
#ifndef NONMATCHING
				romFontPrintGX(xpos, 60.0f, 1.0f, &(GXColor){0xFF, 0xFF, 0xFF, 0xFF}, message);
#endif
			}
			DEMODoneRender();
			makeKey();
			L_gcResetCheck();
		}
		OSYieldThread();
	}
}

#ifndef NONMATCHING
OSTime OSGetTime(void);
int __div2i();
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
#endif
void gcRumbleCheck(void) {
#ifdef NONMATCHING
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
#endif
#ifndef NONMATCHING
	char _af_pad[16];
	asm {
		lis r3, vec3_802c47e0@ha
		addi r6, r3, vec3_802c47e0@l
	}
	asm volatile {
		opword 0x80A60000
		opword 0x80860004
		opword 0x80660008
		opword 0x8006000C
		stw r5, _af_pad+0(r1)
		opword 0x9081000C
		opword 0x90610010
		opword 0x90010014
		bl OSGetTime
		opword 0x7C9E2378
		opword 0x7C7F1B78
		opword 0x3B410008
		li r24, 0x0
		opword 0x3BA00000
		la r28, off_trg_669(r13)
		la r27, off_time_670(r13)
		lwz r5, gp(r13)
		opword 0x7F25C214
		opword 0x881912E8
		opword 0x28000000
		opword 0x40820190
		opword 0x7F03C378
		bl padGetRumbleStatus
		opword 0x5460063E
		opword 0x28000001
		opword 0x408200D8
		lwz r4, gp(r13)
		opword 0x38B812C0
		opword 0x7C0428AE
		opword 0x28000000
		opword 0x40820020
		opword 0x38600001
		opword 0x381D12C8
		opword 0x7C6429AE
		lwz r3, gp(r13)
		opword 0x7C630214
		opword 0x93C30004
		opword 0x93E30000
		opword 0x3C808000
		opword 0x3C601062
		opword 0x800400F8
		opword 0x38634DD3
		lwz r25, gp(r13)
		opword 0x389D12C8
		opword 0x5400F0BE
		opword 0x38A00000
		opword 0x7C030016
		opword 0x7C792214
		opword 0x80630004
		opword 0x7C83F050
		opword 0x7C83FE70
		opword 0x5406D1BE
		bl __div2i
		opword 0x38000000
		opword 0x38C07530
		opword 0x6C058000
		opword 0x6C638000
		opword 0x7C043010
		opword 0x7C632910
		opword 0x7C652910
		opword 0x7C6300D1
		opword 0x4182003C
		opword 0x389812EC
		opword 0x7C1920AE
		opword 0x28000000
		opword 0x4082002C
		opword 0x38A00001
		opword 0x387812E8
		opword 0x7CB921AE
		opword 0x381D12F0
		lwz r4, gp(r13)
		opword 0x7CA419AE
		lwz r3, gp(r13)
		opword 0x7C630214
		opword 0x93C30004
		opword 0x93E30000
		opword 0x38000000
		opword 0x901C0000
		opword 0x48000128
		lwz r3, gp(r13)
		opword 0x381812C0
		opword 0x7C0300AE
		opword 0x28000000
		opword 0x41820114
		opword 0x801C0000
		opword 0x2C000000
		opword 0x40820014
		opword 0x93DB0004
		opword 0x38000001
		opword 0x901C0000
		opword 0x93FB0000
		opword 0x801C0000
		opword 0x2C000000
		opword 0x418200EC
		opword 0x3C808000
		opword 0x3C601062
		opword 0x800400F8
		opword 0x38634DD3
		opword 0x809B0004
		opword 0x38A00000
		opword 0x5400F0BE
		opword 0x7C030016
		opword 0x7C84F050
		opword 0x7C83FE70
		opword 0x5406D1BE
		bl __div2i
		opword 0x38000064
		opword 0x38C00000
		opword 0x6CC58000
		opword 0x6C638000
		opword 0x7C040010
		opword 0x7C632910
		opword 0x7C652910
		opword 0x7C6300D1
		opword 0x41820098
		opword 0x90DC0000
		opword 0x381812C0
		lwz r3, gp(r13)
		opword 0x7CC301AE
		opword 0x48000084
		opword 0x3C808000
		opword 0x3C601062
		opword 0x800400F8
		opword 0x389D12F0
		opword 0x7C852214
		opword 0x38634DD3
		opword 0x5400F0BE
		opword 0x80840004
		opword 0x7C030016
		opword 0x38A00000
		opword 0x7C84F050
		opword 0x7C83FE70
		opword 0x5406D1BE
		bl __div2i
		opword 0x38007530
		opword 0x38C00000
		opword 0x6CC58000
		opword 0x6C638000
		opword 0x7C040010
		opword 0x7C632910
		opword 0x7C652910
		opword 0x7C6300D1
		opword 0x41820020
		opword 0x98D912EC
		opword 0x387812E8
		opword 0x381812C0
		lwz r4, gp(r13)
		opword 0x7CC419AE
		lwz r3, gp(r13)
		opword 0x7CC301AE
		opword 0x38000001
		opword 0x901A0000
		lwz r3, gp(r13)
		opword 0x80030010
		opword 0x2C000000
		opword 0x4182000C
		opword 0x38000001
		opword 0x901A0000
		lwz r3, gp(r13)
		opword 0x80030018
		opword 0x28000000
		opword 0x4182000C
		opword 0x38000001
		opword 0x901A0000
		opword 0x801A0000
		opword 0x2C000000
		opword 0x41820018
		lwz r3, gp(r13)
		opword 0x38181310
		opword 0x38800001
		opword 0x7C8301AE
		opword 0x48000014
		lwz r3, gp(r13)
		opword 0x38181310
		opword 0x38800000
		opword 0x7C8301AE
		opword 0x3B180001
		opword 0x3B9C0004
		opword 0x2C180004
		opword 0x3B7B0008
		opword 0x3B5A0004
		opword 0x3BBD0008
		opword 0x4180FD68
#endif
	}
}
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
#pragma dont_inline on
#endif
#pragma dont_inline on
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
#pragma dont_inline reset

#ifndef NONMATCHING
#pragma dont_inline reset
#endif


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
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c47e0[3] = {0.0f, 0.0f, 0.0f};

#endif