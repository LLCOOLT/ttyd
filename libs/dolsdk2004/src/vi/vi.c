#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>
#include <dolphin/si.h>
#include <dolphin/hw_regs.h>

#include "__gx.h"
#include "__os.h"
#include "__vi.h"

#ifdef DEBUG
const char* __VIVersion = "<< Dolphin SDK - VI\tdebug build: Apr  7 2004 03:55:59 (0x2301) >>";
#else
const char* __VIVersion = "<< Dolphin SDK - VI\trelease build: Apr  7 2004 04:13:59 (0x2301) >>";
#endif

typedef struct {
    u8 equ;
    u16 acv;
    u16 prbOdd;
    u16 prbEven;
    u16 psbOdd;
    u16 psbEven;
    u8 bs1;
    u8 bs2;
    u8 bs3;
    u8 bs4;
    u16 be1;
    u16 be2;
    u16 be3;
    u16 be4;
    u16 nhlines;
    u16 hlw;
    u8 hsy;
    u8 hcs;
    u8 hce;
    u8 hbe640;
    u16 hbs640;
    u8 hbeCCIR656;
    u16 hbsCCIR656;
} VITiming;

typedef struct {
    u16 DispPosX;
    u16 DispPosY;
    u16 DispSizeX;
    u16 DispSizeY;
    u16 AdjustedDispPosX;
    u16 AdjustedDispPosY;
    u16 AdjustedDispSizeY;
    u16 AdjustedPanPosY;
    u16 AdjustedPanSizeY;
    u16 FBSizeX;
    u16 FBSizeY;
    u16 PanPosX;
    u16 PanPosY;
    u16 PanSizeX;
    u16 PanSizeY;
    VIXFBMode FBMode;
    u32 nonInter;
    u32 tv;
    u8 wordPerLine;
    u8 std;
    u8 wpl;
    u32 bufAddr;
    u32 tfbb;
    u32 bfbb;
    u8 xof;
    BOOL black;
    BOOL threeD;
    u32 rbufAddr;
    u32 rtfbb;
    u32 rbfbb;
    VITiming* timing;
} SomeVIStruct;

static BOOL IsInitialized;
static volatile u32 retraceCount;

static volatile u32 flushFlag;
static OSThreadQueue retraceQueue;
static void (*PreCB)(u32);
static void (*PostCB)(u32);
static void (*PositionCallback)(s16, s16);
static u32 encoderType;
static s16 displayOffsetH;
static s16 displayOffsetV;
static volatile u32 changeMode;
static volatile u64 changed;
static volatile u32 shdwChangeMode;
static volatile u16 regs[59];
static volatile u64 shdwChanged;
static VITiming* CurrTiming;
static u32 CurrTvMode;
static u32 NextBufAddr;
static u32 CurrBufAddr;
static volatile u16 shdwRegs[59];

#define MARK_CHANGED(index) (changed |= 1LL << (63 - (index)))

static VITiming timing[10] = {
    { 6, 240, 24, 25, 3, 2, 12, 13, 12, 13, 520, 519, 520, 519, 525, 429, 64, 71, 105, 162, 373, 122, 412 },
    { 6, 240, 24, 24, 4, 4, 12, 12, 12, 12, 520, 520, 520, 520, 526, 429, 64, 71, 105, 162, 373, 122, 412 },
    { 5, 287, 35, 36, 1, 0, 13, 12, 11, 10, 619, 618, 617, 620, 625, 432, 64, 75, 106, 172, 380, 133, 420 },
    { 5, 287, 33, 33, 2, 2, 13, 11, 13, 11, 619, 621, 619, 621, 624, 432, 64, 75, 106, 172, 380, 133, 420 },
    { 6, 240, 24, 25, 3, 2, 16, 15, 14, 13, 518, 517, 516, 519, 525, 429, 64, 78, 112, 162, 373, 122, 412 },
    { 6, 240, 24, 24, 4, 4, 16, 14, 16, 14, 518, 520, 518, 520, 526, 429, 64, 78, 112, 162, 373, 122, 412 },
    { 12, 480, 48, 48, 6, 6, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 162, 373, 122, 412 },
    { 12, 480, 44, 44, 10, 10, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 168, 379, 122, 412 },
    { 6, 241, 24, 25, 1, 0, 12, 13, 12, 13, 520, 519, 520, 519, 525, 429, 64, 71, 105, 159, 370, 122, 412 },
    { 12, 480, 48, 48, 6, 6, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 180, 391, 122, 412 }
};

static u16 taps[25] = {
    0x01F0, 0x01DC,
    0x01AE, 0x0174,
    0x0129, 0x00DB,
    0x008E, 0x0046,
    0x000C, 0x00E2,
    0x00CB, 0x00C0,
    0x00C4, 0x00CF,
    0x00DE, 0x00EC,
    0x00FC, 0x0008,
    0x000F, 0x0013,
    0x0013, 0x000F,
    0x000C, 0x0008,
    0x0001
};

static SomeVIStruct HorVer;
static u32 FBSet;
static VITiming* timingExtra;

// prototypes
static u32 getCurrentFieldEvenOdd(void);
VITiming* __VISetExtraTiming(VITiming* t);
void __VIEnableRawPositionInterrupt(s16 x, s16 y, void (*callback)(s16, s16));
void (*__VIDisableRawPositionInterrupt())(s16, s16);
void __VIDisplayPositionToXY(u32 hct, u32 vct, s16* x, s16* y);
void __VISetLatchMode(u32 mode);
int __VIGetLatch0Position(s16* px, s16* py);
int __VIGetLatch1Position(s16* px, s16* py);
int __VIGetLatchPosition(u32 port, s16* px, s16* py);


/** Returns the video encoder type; always 1 in this build, so the Philips encoder setup is never used. */
static u32 getEncoderType(void) {
    return 1;
}

/**
 * Counts the leading zero bits of a 64-bit value, using cntlzw on each half;
 * used to find the lowest-numbered changed VI register.
 */
static s32 cntlzd(u64 bit) {
    u32 hi;
    u32 lo;
    s32 value;

    hi = bit >> 32;
    lo = bit & 0xFFFFFFFF;
    value = __cntlzw(hi);
    if (value < 32) {
        return value;
    }
    return __cntlzw(lo) + 32;
}

/**
 * Applies the flushed register changes at the right moment:
 * for each register flagged in shdwChanged (a 64-bit mask) writes the shadow value to the hardware,
 * then updates the current timing, TV mode and frame buffer.
 * Waits for the odd field when the mode changed; returns 1 when done and 0 to retry on the next retrace.
 */
static int VISetRegs(void) {
    s32 regIndex;

    if (shdwChangeMode != 1 || getCurrentFieldEvenOdd() != 0) {
        while (shdwChanged != 0) {
            regIndex = cntlzd(shdwChanged);
            __VIRegs[regIndex] = shdwRegs[regIndex];
            shdwChanged &= ~((u64)1 << (63 - regIndex));
        }

        shdwChangeMode = 0;
        CurrTiming = HorVer.timing;
        CurrTvMode = HorVer.tv;
        CurrBufAddr = NextBufAddr;
        return 1;
    }

    return 0;
}

/**
 * Handler for the VI interrupt (exception 0x18), which fires on the four display interrupt registers.
 * Position interrupts (3 and 4) call the position callback;
 * the retrace interrupts bump the retrace count, call the pre-retrace callback,
 * apply flushed registers with VISetRegs (and refresh the SI sampling rate),
 * call the post-retrace callback and wake threads waiting in VIWaitForRetrace.
 */
static void __VIRetraceHandler(__OSInterrupt unused, OSContext* context) {
    OSContext exceptionContext;
    u16 reg;
    u32 inter;
#if DEBUG
    static u32 dbgCount;
#endif

    inter = 0;
    reg = __VIRegs[0x18];
    if (reg & 0x8000) {
        __VIRegs[0x18] = reg & ~0x8000;
        inter |= 1;
    }
    reg = __VIRegs[0x1A];
    if (reg & 0x8000) {
        __VIRegs[0x1A] = reg & ~0x8000;
        inter |= 2;
    }
    reg = __VIRegs[0x1C];
    if (reg & 0x8000) {
        __VIRegs[0x1C] = reg & ~0x8000;
        inter |= 4;
    }
    reg = __VIRegs[0x1E];
    if (reg & 0x8000) {
        __VIRegs[0x1E] = reg & ~0x8000;
        inter |= 8;
    }
    reg = __VIRegs[0x1E];

    if ((inter & 4) || (inter & 8)) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);

        if (PositionCallback != 0) {
            s16 x, y;
            __VIGetCurrentPosition(&x, &y);
            (*PositionCallback)(x, y);
        }

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
        return;
    }

    if (inter == 0) {
        ASSERTLINE(955, FALSE);
    }

    retraceCount += 1;
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);

    if (PreCB) {
        PreCB(retraceCount);
    }

    if (flushFlag != 0) {
#if DEBUG
        dbgCount = 0;
#endif
        if (VISetRegs() != 0) {
            flushFlag = 0;
            SIRefreshSamplingRate();
        }
    }
#if DEBUG
    else if (changed != 0) {
        dbgCount++;
        if (dbgCount > 60) {
            OSReport("Warning: VIFlush() was not called for 60 frames although VI settings were changed\n");
            dbgCount = 0;
        }
    }
#endif

    if (PostCB) {
        OSClearContext(&exceptionContext);
        PostCB(retraceCount);
    }

    OSWakeupThread(&retraceQueue);
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

/**
 * Registers a function called at the start of each retrace, before the VI registers are updated,
 * with the retrace count; returns the previous one.
 */
VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback cb) {
    BOOL enabled;
    VIRetraceCallback oldcb;

    oldcb = PreCB;
    enabled = OSDisableInterrupts();
    PreCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}

/**
 * Registers a function called at each retrace after the VI registers were updated (the usual place to swap frame
 * buffers), with the retrace count; returns the previous one.
 */
VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback cb) {
    BOOL enabled;
    VIRetraceCallback oldcb;

    oldcb = PostCB;
    enabled = OSDisableInterrupts();
    PostCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}

/** Sets the custom VITiming table used by the extra TV modes (28, 29 and 30); returns the previous one. */
VITiming* __VISetExtraTiming(VITiming* t) {
    VITiming* old = timingExtra;

    timingExtra = t;
    return old;
}

#pragma dont_inline on
/**
 * Returns the timing table for a TV mode: NTSC (also used for EuRGB60), PAL, MPAL,
 * progressive and the DEBUG_PAL variants, with interlaced and double-strike entries; NULL for an unknown mode.
 */
static VITiming* getTiming(VITVMode mode) {
    switch (mode) {
    case VI_TVMODE_NTSC_INT:        return &timing[0];
    case VI_TVMODE_NTSC_DS:         return &timing[1];
    case VI_TVMODE_PAL_INT:         return &timing[2];
    case VI_TVMODE_PAL_DS:          return &timing[3];
    case VI_TVMODE_EURGB60_INT:     return &timing[0];
    case VI_TVMODE_EURGB60_DS:      return &timing[1];
    case VI_TVMODE_MPAL_INT:        return &timing[4];
    case VI_TVMODE_MPAL_DS:         return &timing[5];
    case VI_TVMODE_NTSC_PROG:       return &timing[6];
    case 3:                         return &timing[7];
    case VI_TVMODE_DEBUG_PAL_INT:   return &timing[2];
    case VI_TVMODE_DEBUG_PAL_DS:    return &timing[3];
    case 24:                        return &timing[8];
    case 26:                        return &timing[9];
    case 29:
    case 30:
    case 28:
        return timingExtra;
    default:
        return NULL;
    }
}
#pragma dont_inline reset

/**
 * Resets the VI and programs the timing registers of TV mode mode (horizontal and vertical sync, blanking,
 * equalisation, burst intervals) and the display configuration;
 * also stores the TV format in low memory at 0xCC for the OS.
 */
void __VIInit(VITVMode mode) {
    VITiming* tm;
    u32 nonInter;
    u32 tv;
    u32 tvForReg;
    volatile u32 a;
    u16 hct;
    u16 vct;
    u32 encoderType;

    encoderType = getEncoderType();
    if (encoderType == 0) {
        __VIInitPhilips();
    }

    nonInter = mode & 3;
    tv = (u32)mode >> 2;
    *(u32*)OSPhysicalToCached(0xCC) = tv;
    if (encoderType == 0) {
        tv = 3;
    }
    tm = getTiming(mode);
    __VIRegs[1] = 2;

    // why?
    for (a = 0; a < 1000; a++) {}

    __VIRegs[1] = 0;
    __VIRegs[3] = (u32)tm->hlw;
    __VIRegs[2] = tm->hce | (tm->hcs << 8);
    __VIRegs[5] = tm->hsy | ((tm->hbe640 & 0x1FF) << 7);
    __VIRegs[4] = (tm->hbe640 >> 9) | ((tm->hbs640 & 0xFFFF) << 1);
    if (encoderType == 0) {
        __VIRegs[0x39] = tm->hbeCCIR656 | 0x8000;
        __VIRegs[0x3A] = (u32)tm->hbsCCIR656;
    }
    __VIRegs[0] = (u32)tm->equ;
    __VIRegs[7] = (u32)(tm->prbOdd + (tm->acv * 2) - 2);
    __VIRegs[6] = (u32)(tm->psbOdd + 2);
    __VIRegs[9] = (u32)(tm->prbEven + (tm->acv * 2) - 2);
    __VIRegs[8] = (u32)(tm->psbEven + 2);
    __VIRegs[11] = tm->bs1 | (tm->be1 << 5);
    __VIRegs[10] = tm->bs3 | (tm->be3 << 5);
    __VIRegs[13] = tm->bs2 | (tm->be2 << 5);
    __VIRegs[12] = tm->bs4 | (tm->be4 << 5);
    __VIRegs[36] = 0x2828;
    __VIRegs[27] = 1;
    __VIRegs[26] = 0x1001;
    hct = tm->hlw + 1;
    vct = (tm->nhlines / 2) + 1;
    __VIRegs[25] = (u16)(u32)hct;
    __VIRegs[24] = vct | 0x1000;

    switch (tv) {
    case 1:
    case 2:
    case 3:
        tvForReg = tv;
        break;
    default:
        tvForReg = 0;
    }

    if (nonInter == 0 || nonInter == 1) {
        __VIRegs[1] = ((nonInter << 2) & 4) | 1 | (tvForReg << 8);
        __VIRegs[54] = 0;
        return;
    }

    __VIRegs[1] = (tvForReg << 8) | 5;
    __VIRegs[54] = 1;
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CLAMP(val, min, max) ((val) > (max) ? (max) : (val) < (min) ? (min) : (val))

/**
 * Applies the user's screen offset (displayOffsetH and V) to the display and pan rectangle,
 * clamping so the picture stays inside the active video lines acv.
 */
static void AdjustPosition(u16 acv) {
    s32 coeff;
    s32 frac;

    HorVer.AdjustedDispPosX = CLAMP((s16)HorVer.DispPosX + displayOffsetH, 0, 0x2D0 - HorVer.DispSizeX);
    coeff = (HorVer.FBMode == VI_XFBMODE_SF) ? 2 : 1;
    frac = HorVer.DispPosY & 1;
    HorVer.AdjustedDispPosY = MAX((s16)HorVer.DispPosY + displayOffsetV, frac);
    HorVer.AdjustedDispSizeY = HorVer.DispSizeY
                             + MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0)
                             - MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV - (((s16)acv * 2) - frac), 0);
    HorVer.AdjustedPanPosY = HorVer.PanPosY
                           - (MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) / coeff);
    HorVer.AdjustedPanSizeY = HorVer.PanSizeY
                            + (MIN((s16)HorVer.DispPosY + displayOffsetV - frac, 0) / coeff)
                            - (MAX((s16)HorVer.DispPosY + (s16)HorVer.DispSizeY + displayOffsetV - (((s16)acv * 2) - frac), 0) / coeff);
}

/**
 * Reads the saved horizontal display offset from SRAM (the system menu's screen position setting);
 * the vertical offset is set to 0.
 */
static void ImportAdjustingValues(void) {
    OSSram* sram = __OSLockSram();

    ASSERTLINE(1322, sram);
    displayOffsetH = sram->displayOffsetH;
    displayOffsetV = 0;
    __OSUnlockSram(0);
}

/**
 * Initialises the video interface once: if the VI is not running, starts it in NTSC interlaced mode;
 * loads the video filter coefficients, imports the display offset,
 * detects the TV mode from the VI and the boot ROM (PAL boot ROM with an NTSC register means EuRGB60),
 * sets the default 640x(2*acv) display and installs the retrace interrupt handler.
 */
void VIInit(void) {
    u16 dspCfg;
    u32 value;
    u32 tv;
    u32 tvInBootrom;

    if (IsInitialized) {
        return;
    }

    OSRegisterVersion(__VIVersion);
    IsInitialized = TRUE;

    encoderType = getEncoderType();
    if (!(__VIRegs[1] & 1)) {
        __VIInit(VI_TVMODE_NTSC_INT);
    }

    retraceCount = 0;
    changed = 0;
    shdwChanged = 0;
    changeMode = 0;
    shdwChangeMode = 0;
    flushFlag = 0;

    __VIRegs[39] = taps[0] | ((taps[1] & 0x3F) << 10);
    __VIRegs[38] = (taps[1] >> 6) | (taps[2] << 4);
    __VIRegs[41] = taps[3] | ((taps[4] & 0x3F) << 10);
    __VIRegs[40] = (taps[4] >> 6) | (taps[5] << 4);
    __VIRegs[43] = taps[6] | ((taps[7] & 0x3F) << 10);
    __VIRegs[42] = (taps[7] >> 6) | (taps[8] << 4);
    __VIRegs[45] = taps[9] | (taps[10] << 8);
    __VIRegs[44] = taps[11] | (taps[12] << 8);
    __VIRegs[47] = taps[13] | (taps[14] << 8);
    __VIRegs[46] = taps[15] | (taps[16] << 8);
    __VIRegs[49] = taps[17] | (taps[18] << 8);
    __VIRegs[48] = taps[19] | (taps[20] << 8);
    __VIRegs[51] = taps[21] | (taps[22] << 8);
    __VIRegs[50] = taps[23] | (taps[24] << 8);
    __VIRegs[56] = 0x280;
    ImportAdjustingValues();

    tvInBootrom = *(u32*)OSPhysicalToCached(0xCC);
    dspCfg = __VIRegs[1];
    HorVer.nonInter = (s32) ((dspCfg >> 2U) & 1);
    HorVer.tv = ((u32)(dspCfg) & 0x300) >> 8;

    if (tvInBootrom == VI_PAL && HorVer.tv == VI_NTSC) {
        HorVer.tv = VI_EURGB60;
    }

    tv = (HorVer.tv == 3) ? 0 : HorVer.tv;
    HorVer.timing = getTiming((tv << 2) + HorVer.nonInter);
    regs[1] = dspCfg;

    CurrTiming = HorVer.timing;
    CurrTvMode = HorVer.tv;

    HorVer.DispSizeX = 640;
    HorVer.DispSizeY = CurrTiming->acv * 2;
    HorVer.DispPosX = (720 - HorVer.DispSizeX) / 2;
    HorVer.DispPosY = 0;
    AdjustPosition(CurrTiming->acv);
    HorVer.FBSizeX = 640;
    HorVer.FBSizeY = CurrTiming->acv * 2;
    HorVer.PanPosX = 0;
    HorVer.PanPosY = 0;
    HorVer.PanSizeX = 640;
    HorVer.PanSizeY = CurrTiming->acv * 2;
    HorVer.FBMode = 0;

    HorVer.wordPerLine = 40;
    HorVer.std = 40;
    HorVer.wpl = 40;
    HorVer.xof = 0;
    HorVer.black = 1;
    HorVer.threeD = 0;
    OSInitThreadQueue(&retraceQueue);
    value = __VIRegs[24];
    value &= ~0x8000;
#if !DEBUG
    value = (u16)value;
#endif
    __VIRegs[24] = value;
    value = __VIRegs[26];
    value = value & ~0x8000;
#if !DEBUG
    value = (u16)value;
#endif
    __VIRegs[26] = value;
    PreCB = NULL;
    PostCB = NULL;
    __OSSetInterruptHandler(0x18, __VIRetraceHandler);
    __OSUnmaskInterrupts(0x80);
}

/** Puts the calling thread to sleep until the next vertical retrace. */
void VIWaitForRetrace(void) {
    BOOL enabled;
    u32 count;

    enabled = OSDisableInterrupts();
    count = retraceCount;
    do {
        OSSleepThread(&retraceQueue);
    } while (count == retraceCount);
    OSRestoreInterrupts(enabled);
}

/**
 * Sets the VI display interrupt position registers (horizontal and vertical count) to the middle of the frame
 * from the timing table.
 */
static void setInterruptRegs(VITiming* tm) {
#if DEBUG
    u16 vct, hct;
#else
    u16 hct, vct;
#endif
    u16 borrow;

    vct = tm->nhlines / 2;
    borrow = tm->nhlines % 2;
    if (borrow != 0) {
        hct = tm->hlw;
    } else {
        hct = 0;
    }
    vct++;
    hct++;
    regs[25] = (u16)(u32)hct;
    MARK_CHANGED(25);
    regs[24] = vct | 0x1000;
    MARK_CHANGED(24);

    vct;  // fixes regalloc
}

/**
 * Calculates the picture configuration: words per frame buffer line (fbSizeX / 16 rounded up),
 * the stride (doubled for double-field buffers),
 * the pan x-offset within a 16-pixel block and the words to read per line.
 */
static void setPicConfig(u16 fbSizeX, VIXFBMode xfbMode, u16 panPosX, u16 panSizeX, u8* wordPerLine, u8* std, u8* wpl, u8* xof) {
    *wordPerLine = (fbSizeX + 15) / 16;
    *std = (xfbMode == VI_XFBMODE_SF) ? *wordPerLine : (u8)(*wordPerLine * 2);
    *xof = panPosX % 16;
    *wpl = (*xof + panSizeX + 15) / 16;
    regs[0x24] = *std | (*wpl << 8);
    changed |= 0x8000000;
}

/** Sets the four burst-blanking interval registers from the timing table. */
static void setBBIntervalRegs(VITiming* tm) {
    u16 val;

    val = tm->bs1 | (tm->be1 << 5);
    regs[11] = val;
    changed |= 0x10000000000000;

    val = tm->bs3 | (tm->be3 << 5);
    regs[10] = val;
    changed |= 0x20000000000000;

    val = tm->bs2 | (tm->be2 << 5);
    regs[13] = val;
    changed |= 0x4000000000000;

    val = tm->bs4 | (tm->be4 << 5);
    regs[12] = val;
    changed |= (1LL << (63-12));
}

/**
 * Sets the horizontal scaling register so panSizeX source pixels (doubled in 3D mode) are stretched to dispSizeX
 * display pixels; no scaling when the source is not narrower.
 */
static void setScalingRegs(u16 panSizeX, u16 dispSizeX, BOOL threeD) {
    u32 scale;

    panSizeX = threeD ? (panSizeX << 1) : panSizeX;
    if (panSizeX < dispSizeX) {
        scale = (u32)(dispSizeX + (panSizeX << 8) - 1) / dispSizeX;
        regs[37] = scale | 0x1000;
        changed |= 0x04000000;
        regs[56] = (u32)panSizeX;
        changed |= 0x80;
    } else {
        regs[37] = 0x100;
        changed |= 0x04000000;
    }
}

/**
 * Computes the physical top and bottom field frame buffer addresses for the pan position (a single-field buffer
 * uses the same lines for both, a double-field buffer starts the bottom one line later) and swaps them
 * when the display starts on an odd line.
 */
static void calcFbbs(u32 bufAddr, u16 panPosX, u16 panPosY, u8 wordPerLine, VIXFBMode xfbMode, u16 dispPosY, u32* tfbb, u32* bfbb) {
    u32 bytesPerLine;
    u32 xoffInWords;
    u32 tmp;

    xoffInWords = (panPosX & ~0xF) >> 4;
    bytesPerLine = (wordPerLine & 0xFF) << 5;
    *tfbb = bufAddr + (xoffInWords << 5) + (bytesPerLine * panPosY);
    *bfbb = (xfbMode == VI_XFBMODE_SF) ? *tfbb : *tfbb + bytesPerLine;
    if (dispPosY % 2 == 1) {
        tmp = *tfbb;
        *tfbb = *bfbb;
        *bfbb = tmp;
    }
    *tfbb &= 0x3FFFFFFF;
    *bfbb &= 0x3FFFFFFF;
}

/**
 * Writes the top and bottom (and, in 3D mode, right-eye) frame buffer address registers.
 * Addresses that do not fit in 24 bits are stored shifted right by 5 with a flag.
 */
static void setFbbRegs(SomeVIStruct* HorVer, u32* tfbb, u32* bfbb, u32* rtfbb, u32* rbfbb) {
    u32 shifted;

    calcFbbs(HorVer->bufAddr, HorVer->PanPosX, HorVer->AdjustedPanPosY, HorVer->wordPerLine, HorVer->FBMode, HorVer->AdjustedDispPosY, tfbb, bfbb);
    if (HorVer->threeD) {
        calcFbbs(HorVer->rbufAddr, HorVer->PanPosX, HorVer->AdjustedPanPosY, HorVer->wordPerLine, HorVer->FBMode, HorVer->AdjustedDispPosY, rtfbb, rbfbb);
    }

    if (*tfbb < 0x01000000U && *bfbb < 0x01000000U && *rtfbb < 0x01000000U && *rbfbb < 0x01000000U) {
        shifted = 0;
    } else {
        shifted = 1;
    }

    if (shifted) {
        *tfbb >>= 5;
        *bfbb >>= 5;
        *rtfbb >>= 5;
        *rbfbb >>= 5;
    }

    regs[15] = (u16)*tfbb & 0xFFFF;
    MARK_CHANGED(15);
    regs[14] = (shifted << 12) | ((*tfbb >> 16) | (HorVer->xof << 8));
    MARK_CHANGED(14);
    regs[19] = (u16)*bfbb & 0xFFFF;
    MARK_CHANGED(19);
    regs[18] = (*bfbb >> 16);
    MARK_CHANGED(18);

    if (HorVer->threeD) {
        regs[17] = (u16)*rtfbb & 0xFFFF;
        MARK_CHANGED(17);
        regs[16] = *rtfbb >> 16;
        MARK_CHANGED(16);
        regs[21] = (u16)*rbfbb & 0xFFFF;
        MARK_CHANGED(21);
        regs[20] = *rbfbb >> 16;
        MARK_CHANGED(20);
    }
}

/**
 * Sets the horizontal timing registers (line width, colour burst, sync,
 * blanking start and end) from the timing table and the display position and width.
 */
static void setHorizontalRegs(VITiming* tm, u16 dispPosX, u16 dispSizeX) {
    u32 hbe;
    u32 hbs;
    u32 hbeLo;
    u32 hbeHi;

    regs[3] = (u16)(u32)tm->hlw;
    MARK_CHANGED(3);
    regs[2] = tm->hce | (tm->hcs << 8);
    MARK_CHANGED(2);
    hbe = tm->hbe640 - 40 + dispPosX;
    hbs = tm->hbs640 + 40 + dispPosX - (720 - dispSizeX);
    hbeLo = hbe & 0x1FF;
    hbeHi = hbe >> 9;
    regs[5] = tm->hsy | (hbeLo << 7);
    MARK_CHANGED(5);
    regs[4] = hbeHi | (hbs * 2);
    MARK_CHANGED(4);
}

/**
 * Sets the vertical timing registers (equalisation, active lines,
 * pre- and post-blanking for the odd and even fields) for the display position and height;
 * in black mode it sets the active lines to 0 so the screen is black.
 */
static void setVerticalRegs(u16 dispPosY, u16 dispSizeY, u8 equ, u16 acv, u16 prbOdd, u16 prbEven, u16 psbOdd, u16 psbEven, BOOL black) {
    u16 actualPrbOdd;
    u16 actualPrbEven;
    u16 actualPsbOdd;
    u16 actualPsbEven;
    u16 actualAcv;
    u16 c;
    u16 d;

    if (regs[54] & 1) {
        c = 1;
        d = 2;
    } else {
        c = 2;
        d = 1;
    }

    if ((dispPosY % 2) == 0) {
        actualPrbOdd = prbOdd + (d * dispPosY);
        actualPsbOdd = psbOdd + (d * (((c * acv) - dispSizeY) - dispPosY));
        actualPrbEven = prbEven + (d * dispPosY);
        actualPsbEven = psbEven + (d * (((c * acv) - dispSizeY) - dispPosY));
    } else {
        actualPrbOdd = prbEven + (d * dispPosY);
        actualPsbOdd = psbEven + (d * (((c * acv) - dispSizeY) - dispPosY));
        actualPrbEven = prbOdd + (d * dispPosY);
        actualPsbEven = psbOdd + (d * (((c * acv) - dispSizeY) - dispPosY));
    }

    actualAcv = dispSizeY / c;

    if (black) {
        actualPrbOdd += 2 * actualAcv - 2;
        actualPsbOdd += 2;
        actualPrbEven += 2 * actualAcv - 2;
        actualPsbEven += 2;
        actualAcv = 0;
    }

    regs[0] = equ | (actualAcv << 4);
    MARK_CHANGED(0);
    regs[7] = (u16)(u32)actualPrbOdd;
    MARK_CHANGED(7);
    regs[6] = (u16)(u32)actualPsbOdd;
    MARK_CHANGED(6);
    regs[9] = (u16)(u32)actualPrbEven;
    MARK_CHANGED(9);
    regs[8] = (u16)(u32)actualPsbEven;
    MARK_CHANGED(8);
}

/**
 * Prints, once, a warning through OSReport that the DEBUG_PAL TV format is a temporary solution
 * and not for use in real games.
 */
static void PrintDebugPalCaution(void) {
    static u32 message;

    if (message == 0) {
        message = 1;
        OSReport("***************************************\n");
        OSReport(" ! ! ! C A U T I O N ! ! !             \n");
        OSReport("This TV format \"DEBUG_PAL\" is only for \n");
        OSReport("temporary solution until PAL DAC board \n");
        OSReport("is available. Please do NOT use this   \n");
        OSReport("mode in real games!!!                  \n");
        OSReport("***************************************\n");
    }
}

/**
 * Configures the VI from a GXRenderModeObj: scan mode (interlaced, non-interlaced, progressive or 3D),
 * display position and size, frame buffer size and XFB mode.
 * Panics if the mode would change between NTSC-type and PAL-type formats of the boot ROM.
 * Updates the shadow registers; call VIFlush to apply them at the next retrace.
 */
void VIConfigure(const GXRenderModeObj* rm) {
    VITiming* tm;
    u32 regDspCfg;
    u32 regClksel;
    BOOL enabled;
    u32 newNonInter;
    u32 tvInBootrom;
    u32 tvInGame;

    enabled = OSDisableInterrupts();
    newNonInter = rm->viTVmode & 3;

    if (HorVer.nonInter != newNonInter) {
        changeMode = 1;
        HorVer.nonInter = newNonInter;
    }

    ASSERTMSGLINEV(1926, (rm->viHeight & 1) == 0,
        "VIConfigure(): Odd number(%d) is specified to viHeight\n",
        rm->viHeight);

#ifdef DEBUG
    if (rm->xFBmode == VI_XFBMODE_DF || newNonInter == VI_TVMODE_NTSC_PROG || newNonInter == 3) {
        ASSERTMSGLINEV(1933, rm->xfbHeight == rm->viHeight,
            "VIConfigure(): xfbHeight(%d) is not equal to viHeight(%d) when DF XFB mode or progressive mode is specified\n",
            rm->xfbHeight, rm->viHeight);
    }

    if (rm->xFBmode == VI_XFBMODE_SF && newNonInter != VI_TVMODE_NTSC_PROG && newNonInter != 3) {
        ASSERTMSGLINEV(1941, rm->viHeight == rm->xfbHeight * 2,
            "VIConfigure(): xfbHeight(%d) is not as twice as viHeight(%d) when SF XFB mode is specified\n",
            rm->xfbHeight, rm->viHeight);
    }
#endif

    tvInGame = (u32)rm->viTVmode >> 2;
    tvInBootrom = *(u32*)OSPhysicalToCached(0xCC);
    
    if (tvInGame == VI_DEBUG_PAL) {
        PrintDebugPalCaution();
    }

    switch (tvInBootrom) {
    case VI_MPAL:
    case VI_NTSC:
    case 6:
    case 7:
        if (tvInGame == VI_NTSC || tvInGame == VI_MPAL || tvInGame == 6 || tvInGame == 7) {
            break;
        }
        goto panic;
    case VI_PAL:
    case VI_EURGB60:
        if (tvInGame == VI_PAL || tvInGame == VI_EURGB60) {
            break;
        }
    default:
    panic:
        OSPanic(__FILE__, 1979,
                "VIConfigure(): Tried to change mode from (%d) to (%d), which is forbidden\n",
                tvInBootrom, tvInGame);
    }

    if ((tvInGame == VI_NTSC) || (tvInGame == VI_MPAL)) {
        HorVer.tv = tvInBootrom;
    } else {
        HorVer.tv = tvInGame;
    }

    HorVer.DispPosX  = rm->viXOrigin;
    HorVer.DispPosY  = (HorVer.nonInter == 1) ? (u16)(rm->viYOrigin * 2) : rm->viYOrigin;
    HorVer.DispSizeX = rm->viWidth;
    HorVer.FBSizeX   = rm->fbWidth;
    HorVer.FBSizeY   = rm->xfbHeight;
    HorVer.FBMode    = rm->xFBmode;
    HorVer.PanSizeX  = HorVer.FBSizeX;
    HorVer.PanSizeY  = HorVer.FBSizeY;
    HorVer.PanPosX   = 0;
    HorVer.PanPosY   = 0;
    HorVer.DispSizeY = (HorVer.nonInter == 2)           ? HorVer.PanSizeY :
                       (HorVer.nonInter == 3)           ? HorVer.PanSizeY :
                       (HorVer.FBMode == VI_XFBMODE_SF) ? (u16)(HorVer.PanSizeY * 2) :
                                                          HorVer.PanSizeY;
    HorVer.threeD = (HorVer.nonInter == 3) ? TRUE : FALSE;

    tm = getTiming((HorVer.tv << 2) + HorVer.nonInter);
    HorVer.timing = tm;

    AdjustPosition(tm->acv);
    ASSERTMSGLINEV(2022, rm->viXOrigin <= tm->hlw + 40 - tm->hbe640,
        "VIConfigure(): viXOrigin(%d) cannot be greater than %d in this TV mode\n",
        rm->viXOrigin, tm->hlw + 40 - tm->hbe640);
    ASSERTMSGLINEV(2027,  rm->viXOrigin + rm->viWidth >= 680 - tm->hbs640,
        "VIConfigure(): viXOrigin + viWidth (%d) cannot be less than %d in this TV mode\n",
        rm->viXOrigin + rm->viWidth, 680 - tm->hbs640);

    if (encoderType == 0) {
        HorVer.tv = 3;
    }
    setInterruptRegs(tm);

    regDspCfg = regs[1];
    regClksel = regs[54];
    if (HorVer.nonInter == VI_PROGRESSIVE || HorVer.nonInter == 3) {
        regDspCfg = (((u32)(regDspCfg)) & ~0x00000004) | (((u32)(1)) << 2);
        regClksel = (((u32)(regClksel)) & ~0x00000001) | (((u32)(1)) << 0);
    } else {
        OLD_SET_REG_FIELD(2052, regDspCfg, 1, 2, HorVer.nonInter & 1);
        regClksel = (((u32)(regClksel)) & ~0x00000001);
    }

    OLD_SET_REG_FIELD(2056, regDspCfg, 1, 3, HorVer.threeD);

    if ((HorVer.tv == VI_PAL) || (HorVer.tv == VI_MPAL) || (HorVer.tv == 3)) {
        OLD_SET_REG_FIELD(2060, regDspCfg, 2, 8, HorVer.tv);
    } else {
        regDspCfg = (((u32)(regDspCfg)) & ~0x00000300);
    }

    regs[1] = regDspCfg;
    regs[54] = (u16)regClksel;

    MARK_CHANGED(1);    
    MARK_CHANGED(54);

    setScalingRegs(HorVer.PanSizeX, HorVer.DispSizeX, HorVer.threeD);
    setHorizontalRegs(tm, HorVer.AdjustedDispPosX, HorVer.DispSizeX);
    setBBIntervalRegs(tm);
    setPicConfig(HorVer.FBSizeX, HorVer.FBMode, HorVer.PanPosX, HorVer.PanSizeX, &HorVer.wordPerLine, &HorVer.std, &HorVer.wpl, &HorVer.xof);
    if (FBSet != 0) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    }
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.AdjustedDispSizeY, tm->equ, tm->acv, tm->prbOdd, tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.black);
    OSRestoreInterrupts(enabled);
}

/**
 * Chooses which part of the frame buffer is displayed (pan origin and size) and updates the scaling,
 * picture configuration, frame buffer and vertical registers; applied at the next VIFlush.
 */
void VIConfigurePan(u16 xOrg, u16 yOrg, u16 width, u16 height) {
    BOOL enabled;
    VITiming* tm;

#if DEBUG
    ASSERTMSGLINEV(2118, (xOrg & 1) == 0,
        "VIConfigurePan(): Odd number(%d) is specified to xOrg\n",
        xOrg);
    if (HorVer.FBMode == VI_XFBMODE_DF) {
        ASSERTMSGLINEV(2123, (height & 1) == 0,
            "VIConfigurePan(): Odd number(%d) is specified to height when DF XFB mode\n",
            height);
    }
#endif
    enabled = OSDisableInterrupts();
    HorVer.PanPosX   = xOrg;
    HorVer.PanPosY   = yOrg;
    HorVer.PanSizeX  = width;
    HorVer.PanSizeY  = height;
    HorVer.DispSizeY = (HorVer.nonInter == 2)           ? HorVer.PanSizeY :
                       (HorVer.nonInter == 3)           ? HorVer.PanSizeY :
                       (HorVer.FBMode == VI_XFBMODE_SF) ? (u16)(HorVer.PanSizeY * 2) :
                                                          HorVer.PanSizeY;
    tm = HorVer.timing;
    AdjustPosition(tm->acv);
    setScalingRegs(HorVer.PanSizeX, HorVer.DispSizeX, HorVer.threeD);
    setPicConfig(HorVer.FBSizeX, HorVer.FBMode, HorVer.PanPosX, HorVer.PanSizeX, &HorVer.wordPerLine, &HorVer.std, &HorVer.wpl, &HorVer.xof);
    if (FBSet != 0) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    }
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.DispSizeY, tm->equ, tm->acv, tm->prbOdd, tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.black);
    OSRestoreInterrupts(enabled);
}

/**
 * Commits all VI register changes made since the last flush by copying them to the shadow registers
 * and flagging the next retrace to write them to the hardware.
 */
void VIFlush(void) {
    BOOL enabled;
    s32 regIndex;

    enabled = OSDisableInterrupts();
    shdwChangeMode |= changeMode;
    changeMode = 0;
    shdwChanged |= changed;

    while (changed != 0) {
        regIndex = cntlzd(changed);
        shdwRegs[regIndex] = regs[regIndex];
        changed &= ~((u64)1 << (63 - regIndex));
    }

    flushFlag = 1;
    NextBufAddr = HorVer.bufAddr;
    OSRestoreInterrupts(enabled);
}

/**
 * Sets the frame buffer (32-byte aligned) the VI will display from the next flush and retrace on,
 * and updates the frame buffer address registers.
 */
void VISetNextFrameBuffer(void* fb) {
    BOOL enabled;

    ASSERTMSGLINEV(2216, ((u32)fb & 0x1F) == 0,
        "VISetNextFrameBuffer(): Frame buffer address(0x%08x) is not 32byte aligned\n",
        fb);
    enabled = OSDisableInterrupts();
    HorVer.bufAddr = (u32)fb;
    FBSet = 1;
    setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    OSRestoreInterrupts(enabled);
}

/** Returns the frame buffer that has been flushed to be displayed next. */
void* VIGetNextFrameBuffer(void) {
    return *(void**)(&NextBufAddr);
}

/** Returns the frame buffer being displayed now. */
void* VIGetCurrentFrameBuffer(void) {
    return *(void**)(&CurrBufAddr);
}

/** Sets the right-eye frame buffer for stereoscopic (3D) mode and updates the frame buffer address registers. */
void VISetNextRightFrameBuffer(void* fb) {
    BOOL enabled;

    ASSERTMSGLINEV(2284, ((u32)fb & 0x1F) == 0,
        "VISetNextFrameBuffer(): Frame buffer address(0x%08x) is not 32byte aligned\n",
        fb);
    enabled = OSDisableInterrupts();
    HorVer.rbufAddr = (u32)fb;
    FBSet = 1;
    setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    OSRestoreInterrupts(enabled);
}

/**
 * Turns the display black (no active lines) or back on by rewriting the vertical registers;
 * applied at the next VIFlush.
 */
void VISetBlack(BOOL black) {
    BOOL enabled;
    VITiming* tm;

    enabled = OSDisableInterrupts();
    HorVer.black = black;
    tm = HorVer.timing;
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.DispSizeY, tm->equ, tm->acv, tm->prbOdd, tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.black);
    OSRestoreInterrupts(enabled);
}

/**
 * Turns the stereoscopic 3D display mode flag on or off and recalculates the horizontal scaling;
 * applied at the next VIFlush.
 */
void VISet3D(BOOL threeD) {
    BOOL enabled;
    u32 reg;

    enabled = OSDisableInterrupts();
    HorVer.threeD = threeD;
    reg = regs[1];
    OLD_SET_REG_FIELD(2355, reg, 1, 3, HorVer.threeD);
    regs[1] = reg;
    MARK_CHANGED(1);
    setScalingRegs(HorVer.PanSizeX, HorVer.DispSizeX, HorVer.threeD);
    OSRestoreInterrupts(enabled);
}

/** Returns the number of vertical retraces counted since VIInit. */
u32 VIGetRetraceCount(void) {
    return retraceCount;
}

/**
 * Reads the beam position from the VI horizontal and vertical counters (hct, vct),
 * rereading until the vertical count is stable.
 */
static void GetCurrentDisplayPosition(u32* hct, u32* vct) {
    u32 hcount, vcount0, vcount;
    vcount = __VIRegs[VI_VERT_COUNT] & 0x7FF;

    do {
        vcount0 = vcount;
        hcount = __VIRegs[VI_HORIZ_COUNT] & 0x7FF;
        vcount = __VIRegs[VI_VERT_COUNT] & 0x7FF;
    } while (vcount0 != vcount);

    *hct = hcount;
    *vct = vcount;
}

/**
 * Returns the beam position in half-lines from the start of the frame,
 * computed from the horizontal and vertical counters and the line width of the current timing.
 */
static u32 getCurrentHalfLine(void) {
    u32 hcount, vcount;
    GetCurrentDisplayPosition(&hcount, &vcount);

    return ((vcount - 1) << 1) + ((hcount - 1) / CurrTiming->hlw);
}

/** Returns 1 when the beam is in the first field of the frame (the odd field) and 0 in the second. */
static u32 getCurrentFieldEvenOdd(void) {
    return (getCurrentHalfLine() < CurrTiming->nhlines) ? 1 : 0;
}

/**
 * Returns which field (0 or 1) will be displayed next,
 * taking into account whether the display starts on an odd line.
 */
u32 VIGetNextField(void) {
    s32 nextField;
    BOOL enabled;
#if !DEBUG
    u8 unused[4];
#endif

    enabled = OSDisableInterrupts();
    nextField = getCurrentFieldEvenOdd() ^ 1;
    OSRestoreInterrupts(enabled);
    return nextField ^ (HorVer.AdjustedDispPosY & 1);
}

/** Returns the line the beam is on now, counted from the start of the current field. */
u32 VIGetCurrentLine(void) {
    u32 halfLine;
    VITiming* tm;
    BOOL enabled;

    tm = CurrTiming;
    enabled = OSDisableInterrupts();
    halfLine = getCurrentHalfLine();
    OSRestoreInterrupts(enabled);
    if (halfLine >= tm->nhlines) {
        halfLine -= tm->nhlines;
    }
    return halfLine >> 1U;
}

/** Returns the active TV format: NTSC (also for DEBUG and modes 6 and 7), PAL (also DEBUG_PAL), EuRGB60 or MPAL. */
u32 VIGetTvFormat(void) {
    u32 format;
    BOOL enabled;

    enabled = OSDisableInterrupts();

    switch (CurrTvMode) {
    case VI_NTSC:
    case VI_DEBUG:
    case 6:
    case 7:
        format = VI_NTSC;
        break;
    case VI_PAL:
    case VI_DEBUG_PAL:
        format = VI_PAL;
        break;
    case VI_EURGB60:
    case VI_MPAL:
        format = CurrTvMode;
        break;
    default:
        ASSERTLINE(2527, FALSE);
    }
    
    OSRestoreInterrupts(enabled);
    return format;
}

/** Returns the scan mode from the VI registers: 2 progressive, 1 non-interlaced, 0 interlaced. */
u32 VIGetScanMode(void) {
    u32 scanMode;
    BOOL enabled = OSDisableInterrupts();

    if ((u32)(__VIRegs[54] & 1) == 1) {
        scanMode = 2;
    } else if (!((__VIRegs[1] & (1 << 2)) >> 2)) {
        scanMode = 0;
    } else {
        scanMode = 1;
    }
    
    OSRestoreInterrupts(enabled);
    return scanMode;
}

/**
 * Returns bit 0 of the VI digital TV status register,
 * which reports whether the component (digital TV) cable is connected.
 */
u32 VIGetDTVStatus(void) {
    u32 dtvStatus;
    BOOL enabled = OSDisableInterrupts();

    dtvStatus = __VIRegs[55] & 3;
    OSRestoreInterrupts(enabled);
    return dtvStatus & 1;
}

/** Sets the screen position offset (x, y) and applies it to the horizontal, frame buffer and vertical registers. */
void __VISetAdjustingValues(s16 x, s16 y) {
    BOOL enabled;
    VITiming* tm;

    ASSERTMSGLINE(2611, (y & 1) == 0, "__VISetAdjustValues(): y offset should be an even number");
    enabled = OSDisableInterrupts();
    displayOffsetH = x;
    displayOffsetV = y;
    tm = HorVer.timing;
    AdjustPosition(tm->acv);
    setHorizontalRegs(tm, HorVer.AdjustedDispPosX, HorVer.DispSizeX);
    if (FBSet != 0) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    }
    setVerticalRegs(HorVer.AdjustedDispPosY, HorVer.AdjustedDispSizeY, tm->equ, tm->acv, tm->prbOdd, tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.black);
    OSRestoreInterrupts(enabled);
}

/** Returns the screen position offset (x, y). */
void __VIGetAdjustingValues(s16* x, s16* y) {
    BOOL enabled;

    enabled = OSDisableInterrupts();
    *x = displayOffsetH;
    *y = displayOffsetV;
    OSRestoreInterrupts(enabled);
}

/** DEBUG NONMATCHING - wrong reg use, equivalent */
void __VIEnableRawPositionInterrupt(s16 x, s16 y, void (*callback)(s16, s16)) {
    BOOL enabled;
    u32 halfLine;
    u32 halfLineOff;

    enabled = OSDisableInterrupts();
    __VIRegs[29] = x + 1U;
    __VIRegs[31] = x + 1U;

    if (HorVer.nonInter == 0) {
        if (y & 1) {
            halfLineOff = CurrTiming->prbEven + ((CurrTiming->equ * 3) + CurrTiming->nhlines);
            __VIRegs[30] = (((halfLineOff / 2) + (y / 2)) + 1) | 0x1000;
        } else {
            halfLineOff = CurrTiming->prbOdd + (CurrTiming->equ * 3);
            __VIRegs[28] = (((halfLineOff / 2) + (y / 2)) + 1) | 0x1000;
        }
    } else if (HorVer.nonInter == 1) {
        ASSERTLINE(2702, (y & 1) == 0);
        halfLine = CurrTiming->prbOdd + ((CurrTiming->equ * 3)) + y;
        __VIRegs[28] = ((halfLine / 2) + 1) | 0x1000;
        __VIRegs[30] = (((halfLine + CurrTiming->nhlines) / 2) + 1) | 0x1000;
    } else if (HorVer.nonInter == 2) {
        halfLine = CurrTiming->prbOdd + ((CurrTiming->equ * 3)) + y;
        __VIRegs[28] = (halfLine + 1) | 0x1000;
        __VIRegs[30] = 0;
    }

    PositionCallback = callback;
    OSRestoreInterrupts(enabled);
}

void (*__VIDisableRawPositionInterrupt())(s16, s16) {
    BOOL enabled;
    void (*old)(s16, s16);

    enabled = OSDisableInterrupts();
    __VIRegs[28] = 0;
    __VIRegs[30] = 0;

    old = PositionCallback;
    PositionCallback = 0;
    OSRestoreInterrupts(enabled);
    return old;
}

/**
 * Converts a beam position (hct, vct) to screen pixel coordinates:
 * x is hct - 1, y is the line within the active area for the current scan mode,
 * or -1 if the beam is in blanking.
 */
void __VIDisplayPositionToXY(u32 hct, u32 vct, s16* x, s16* y) {
    u32 halfLine = ((vct - 1) << 1) + ((hct - 1) / CurrTiming->hlw);

    if (HorVer.nonInter == VI_INTERLACE) {
        if (halfLine < CurrTiming->nhlines) {
            if (halfLine < CurrTiming->equ * 3 + CurrTiming->prbOdd) {
                *y = -1;
            } else if (halfLine >= CurrTiming->nhlines - CurrTiming->psbOdd) {
                *y = -1;
            } else {
                *y = (s16)((halfLine - CurrTiming->equ * 3 - CurrTiming->prbOdd) & ~1);
            }
        } else {
            halfLine -= CurrTiming->nhlines;

            if (halfLine < CurrTiming->equ * 3 + CurrTiming->prbEven) {
                *y = -1;
            } else if (halfLine >= CurrTiming->nhlines - CurrTiming->psbEven) {
                *y = -1;
            } else {
                *y = (s16)(((halfLine - CurrTiming->equ * 3 - CurrTiming->prbEven) & ~1) + 1);
            }
        }
    } else if (HorVer.nonInter == VI_NON_INTERLACE) {
        if (halfLine >= CurrTiming->nhlines) {
            halfLine -= CurrTiming->nhlines;
        }

        if (halfLine < CurrTiming->equ * 3 + CurrTiming->prbOdd) {
            *y = -1;
        } else if (halfLine >= CurrTiming->nhlines - CurrTiming->psbOdd) {
            *y = -1;
        } else {
            *y = (s16)((halfLine - CurrTiming->equ * 3 - CurrTiming->prbOdd) & ~1);
        }
    } else if (HorVer.nonInter == VI_PROGRESSIVE) {
        if (halfLine < CurrTiming->nhlines) {
            if (halfLine < CurrTiming->equ * 3 + CurrTiming->prbOdd) {
                *y = -1;
            } else if (halfLine >= CurrTiming->nhlines - CurrTiming->psbOdd) {
                *y = -1;
            } else {
                *y = (s16)(halfLine - CurrTiming->equ * 3 - CurrTiming->prbOdd);
            }
        } else {
            halfLine -= CurrTiming->nhlines;

            if (halfLine < CurrTiming->equ * 3 + CurrTiming->prbEven) {
                *y = -1;
            } else if (halfLine >= CurrTiming->nhlines - CurrTiming->psbEven) {
                *y = -1;
            } else
                *y = (s16)((halfLine - CurrTiming->equ * 3 - CurrTiming->prbEven) & ~1);
        }
    }

    *x = (s16)(hct - 1);
}

/** Returns the current beam position as screen coordinates (x, y). */
void __VIGetCurrentPosition(s16* x, s16* y) {
    u32 hcount, vcount;
    GetCurrentDisplayPosition(&hcount, &vcount);
    __VIDisplayPositionToXY(hcount, vcount, x, y);
}

/**
 * Sets the mode of both light-pen/gun latch inputs (fields 4 to 5 and 6 to 7 of the display configuration
 * register) to mode.
 */
void __VISetLatchMode(u32 mode) {
    u32 reg;

    reg = __VIRegs[1];
    OLD_SET_REG_FIELD(2834, reg, 2, 4, mode);
    OLD_SET_REG_FIELD(2835, reg, 2, 6, mode);
    __VIRegs[1] = reg;
}

#pragma dont_inline on
/**
 * If latch 0 has triggered, returns 1 and its screen position (clearing the latch);
 * otherwise returns 0 with (-1, -1).
 */
int __VIGetLatch0Position(s16* px, s16* py) {
    u32 hcount;
    u32 vcount;

    if (((__VIRegs[32] & 0x8000) >> 15) != 0) {
        vcount = __VIRegs[32] & 0x7FF;
        hcount = __VIRegs[33] & 0x7FF;
        __VIRegs[32] = 0;
        __VIRegs[33] = 0;
        __VIDisplayPositionToXY(hcount, vcount, px, py);
        return 1;
    }

    *px = *py = -1;
    return 0;
}
#pragma dont_inline reset

#pragma dont_inline on
/**
 * If latch 1 has triggered, returns 1 and its screen position (clearing the latch);
 * otherwise returns 0 with (-1, -1).
 */
int __VIGetLatch1Position(s16* px, s16* py) {
    u32 hcount;
    u32 vcount;

    if (((__VIRegs[34] & 0x8000) >> 15) != 0) {
        vcount = __VIRegs[34] & 0x7FF;
        hcount = __VIRegs[35] & 0x7FF;
        __VIRegs[34] = 0;
        __VIRegs[35] = 0;
        __VIDisplayPositionToXY(hcount, vcount, px, py);
        return 1;
    }

    *px = *py = -1;
    return 0;
}
#pragma dont_inline reset

/** Returns the position of latch 0 or 1 depending on port, through __VIGetLatch0Position or __VIGetLatch1Position. */
int __VIGetLatchPosition(u32 port, s16* px, s16* py) {
    if (port == 0) {
        return __VIGetLatch0Position(px, py);
    } else {
        return __VIGetLatch1Position(px, py);
    }
}
