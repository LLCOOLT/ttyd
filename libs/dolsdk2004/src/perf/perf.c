#include <dolphin.h>
#include <dolphin/gx.h>
#include <dolphin/perf.h>
#include "fake_tgmath.h"

#include "__perf.h"
#include "../gx/__gx.h"

#if DEBUG
const char* __PERFVersion = "<< Dolphin SDK - PERF\tdebug build: Apr  5 2004 03:57:10 (0x2301) >>";
#else
const char* __PERFVersion = "<< Dolphin SDK - PERF\trelease build: Apr  5 2004 04:15:51 (0x2301) >>";
#endif

#define TOKEN_MAX 0xFFFF

static OSAlarm PERFAlarm;

static volatile s32 CurrAutoSample = 0xFFFFFFFF;
static volatile u32 CurrToken = 0x0000FFFF;

static volatile u8 magic;
static void* (*PerfAlloc)(u32);
static void (*PerfFree)(void*);
static void (*DSCB)(u16);
u32 PERFNumFrames;
u32 PERFNumEvents;
u32 PERFNumSamples;
Frame* PERFFrames;
PerfEvent* PERFEvents;
u32 PERFCurrFrame;
volatile s32 PERFCurrSample;

// prototypes
static void PERFResetAllMemMetrics(void);
static void PERFGetAllMemMetrics(PerfSample* s, u32 i);
void PERFSetDrawSyncCallback(void (*cb)(u16));
static void PERFTokenCallback(u16 token);
u32 PERFInit(u32 numSamples, u32 numFramesHistory, u32 numTypes, PERFAllocator allocator, PERFDeallocator deallocator, void (*initDraw)());
void PERFSetEvent(u8 id, char* name, PerfType type);
void PERFSetEventColor(u8 id, GXColor color);
void PERFStartFrame(void);
void PERFEndFrame(void);
void PERFEventStart(u8 id);
__declspec(weak) s32 PERFGetNewSample(void);
void PERFEventEnd(u8 id);
static void PERFStartAutoSample(void);
static void PERFEndAutoSample(void);
static void PERFTimerCallback(OSAlarm* alarm, OSContext* context);
void PERFStartAutoSampling(f32 msInterval);
void PERFStopAutoSampling(void);

#ifndef DEBUG
/**
 * Hands out the next free sample slot of the current frame (PERFCurrSample++);
 * once the table is full it keeps returning the last slot instead of overflowing.
 */
inline s32 PERFGetNewSample(void) {
    if (PERFCurrSample >= (PERFNumSamples - 1)) {
        PERFCurrSample = PERFNumSamples - 1;
        return PERFCurrSample;
    }
    return PERFCurrSample++;
}
#endif

/**
 * Zeroes the twenty 16-bit memory-interface counter registers (__memReg[25] to [44]) that count CP, TC,
 * CPU read/write, DSP, IO, VI, PE, RF and FI memory requests, before a frame is measured.
 */
static void PERFResetAllMemMetrics(void) {
    ((u16*)__memReg)[25] = 0;
    ((u16*)__memReg)[26] = 0;
    ((u16*)__memReg)[27] = 0;
    ((u16*)__memReg)[28] = 0;
    ((u16*)__memReg)[30] = 0;
    ((u16*)__memReg)[29] = 0;
    ((u16*)__memReg)[32] = 0;
    ((u16*)__memReg)[31] = 0;
    ((u16*)__memReg)[34] = 0;
    ((u16*)__memReg)[33] = 0;
    ((u16*)__memReg)[36] = 0;
    ((u16*)__memReg)[35] = 0;
    ((u16*)__memReg)[38] = 0;
    ((u16*)__memReg)[37] = 0;
    ((u16*)__memReg)[40] = 0;
    ((u16*)__memReg)[39] = 0;
    ((u16*)__memReg)[42] = 0;
    ((u16*)__memReg)[41] = 0;
    ((u16*)__memReg)[44] = 0;
    ((u16*)__memReg)[43] = 0;
}

/**
 * Snapshots the GX transform/raster metrics (GXReadXfRasMetric) and the ten 32-bit memory request counters (CP,
 * TC, CPU read, CPU write, DSP, IO, VI, PE, RF, FI) into slot i (0 = start, 1 = end) of a sample.
 */
static void PERFGetAllMemMetrics(PerfSample* s, u32 i) {
    u32 ctrl;
    u32 ctrh;

    GXReadXfRasMetric(&s->xfWaitIn[i], &s->xfWaitOut[i], &s->rasBusy[i], &s->rasClocks[i]);

    ctrl = ((u16*)__memReg)[26];
    ctrh = ((u16*)__memReg)[25];
    s->cpReq[i] = ((ctrh << 0x10) | ctrl);

    ctrl = ((u16*)__memReg)[28];
    ctrh = ((u16*)__memReg)[27];
    s->tcReq[i] = ((ctrh << 0x10) | ctrl);

    ctrl = ((u16*)__memReg)[30];
    ctrh = ((u16*)__memReg)[29];
    s->cpuRdReq[i] = ((ctrh << 0x10) | ctrl);

    ctrl = ((u16*)__memReg)[32];
    ctrh = ((u16*)__memReg)[31];
    s->cpuWrReq[i] = ((ctrh << 0x10) | ctrl);

    ctrl = ((u16*)__memReg)[34];
    ctrh = ((u16*)__memReg)[33];
    s->dspReq[i] = ((ctrh << 0x10) | ctrl);

    ctrl = ((u16*)__memReg)[36];
    ctrh = ((u16*)__memReg)[35];
    s->ioReq[i] = ((ctrh << 0x10) | ctrl);

    ctrl = ((u16*)__memReg)[38];
    ctrh = ((u16*)__memReg)[37];
    s->viReq[i] = ((ctrh << 0x10) | ctrl);

    ctrl = ((u16*)__memReg)[40];
    ctrh = ((u16*)__memReg)[39];
    s->peReq[i] = ((ctrh << 0x10) | ctrl);

    ctrl = ((u16*)__memReg)[42];
    ctrh = ((u16*)__memReg)[41];
    s->rfReq[i] = ((ctrh << 0x10) | ctrl);

    ctrl = ((u16*)__memReg)[44];
    ctrh = ((u16*)__memReg)[43];
    s->fiReq[i] = ((ctrh << 0x10) | ctrl);
}

/**
 * Registers the game's own GXSetDrawSync callback,
 * which the profiler calls for tokens it does not use (it installs its own callback on the GX draw-sync
 * interrupt).
 */
void PERFSetDrawSyncCallback(void (*cb)(u16)) {
    DSCB = cb;
}

/**
 * GX draw-sync interrupt callback.
 * Tokens of 0xE000 and above whose magic nibble matches the current frame belong to the profiler:
 * they record the GP-side timestamp (performance counter 4), cache misses and instructions,
 * and memory counters when a GP event starts or ends. Other tokens go to the game's callback.
 */
static void PERFTokenCallback(u16 token) {
    s32 sample;

    if ((token < 0xE000) || (((int)((u32)token >> 8) & 0xF) != magic) || (PERFCurrSample == 0)) {
        if (DSCB) {
            DSCB(token);
        }
    } else {
        if (token >= 0xF000) {
            if (CurrToken == TOKEN_MAX) {
                ASSERTLINE(341, CurrAutoSample >= 0);
                PERFEndAutoSample();
                PERFStartAutoSample();
                return;
            }

            sample = (u8)(u32)token;
            if ((u8)(u16)CurrToken != sample) {
                sample = (u8)(u16)CurrToken;
            }

            ASSERTLINE(357, sample < PERFCurrSample);

            PERFFrames[PERFCurrFrame].samples[sample].gpTimeStampEnd = PPCMfpmc4();
            PERFFrames[PERFCurrFrame].samples[sample].cacheMisses[1] = PPCMfpmc3();
            PERFFrames[PERFCurrFrame].samples[sample].instructions[1] = PPCMfpmc1();
            PERFGetAllMemMetrics(&PERFFrames[PERFCurrFrame].samples[sample], 1);
            if (CurrAutoSample >= 0) {
                ASSERTLINE(369, CurrToken == TOKEN_MAX);
                PERFEndAutoSample();
            }
            CurrToken = 0xFFFF;
            PERFStartAutoSample();
            return;
        }

        if (CurrToken < 0xFFFF) {
            ASSERTLINE(384, CurrAutoSample < 0);
            sample = (u8)(u16)CurrToken;
            PERFFrames[PERFCurrFrame].samples[sample].gpTimeStampEnd = PPCMfpmc4();
            PERFFrames[PERFCurrFrame].samples[sample].cacheMisses[1] = PPCMfpmc3();
            PERFFrames[PERFCurrFrame].samples[sample].instructions[1] = PPCMfpmc1();
            PERFGetAllMemMetrics(&PERFFrames[PERFCurrFrame].samples[sample], 1);
        } else {
            ASSERTLINE(394, CurrAutoSample >= 0);
            PERFEndAutoSample();
        }

        sample = (u8)(u32)token;
        PERFFrames[PERFCurrFrame].samples[sample].cacheMisses[0] = PPCMfpmc3();
        PERFFrames[PERFCurrFrame].samples[sample].instructions[0] = PPCMfpmc1();
        PERFFrames[PERFCurrFrame].samples[sample].gpTimeStampStart = PERFFrames[PERFCurrFrame].samples[sample].origgpStart = PPCMfpmc4();
        PERFGetAllMemMetrics(&PERFFrames[PERFCurrFrame].samples[sample], 0);
        CurrToken = (u32)(u16)token;
    }
}

/**
 * Allocates the profiler's tables with the given allocator:
 * numFramesHistory frames of numSamples samples (0xB0 bytes each) plus numTypes event slots.
 * Sets up the overlay (initDraw is the game's callback to restore its GX state),
 * installs the draw-sync callback and starts the GX transform/raster metrics.
 * Returns the number of bytes allocated.
 */
u32 PERFInit(u32 numSamples, u32 numFramesHistory, u32 numTypes, PERFAllocator allocator, PERFDeallocator deallocator, void (*initDraw)()) {
    u32 i;
    u32 size;

    OSRegisterVersion(__PERFVersion);

    PerfAlloc = allocator;
    PerfFree = deallocator;
    PERFNumFrames = numFramesHistory;
    PERFNumEvents = numTypes;
    PERFNumSamples = numSamples;
    
    size = (numFramesHistory * 0x10);
    size += (numFramesHistory * (numSamples * 0xB0));
    size += (numTypes* 0x10);
    
    PERFFrames = (Frame*)PerfAlloc(numFramesHistory * 0x10);

    for (i = 0; i < PERFNumFrames; i++) {
        PERFFrames[i].samples = (PerfSample *)PerfAlloc(numSamples* 0xB0);
        PERFFrames[i].lastSample = 0;
    }

    PERFEvents = (PerfEvent *)PerfAlloc(numTypes* 0x10);

    for (i = 0; i < numTypes; i++) {
        PERFEvents[i].name = 0;
        PERFEvents[i].currSample = -1;
    }

    __PERFDrawInit(initDraw);
    GXSetDrawSyncCallback(PERFTokenCallback);
    GXInitXfRasMetric();
    return size;
}

/**
 * Names event id and sets its type (PERF_CPU_EVENT,
 * PERF_GP_EVENT or PERF_CPU_GP_EVENT) with the default red-orange colour.
 */
void PERFSetEvent(u8 id, char* name, PerfType type) {
    GXColor def = {0xFF, 0x19, 0x00, 0xC8};

    PERFEvents[id].name = name;
    PERFEvents[id].type = type;
    PERFEvents[id].currSample = -1;
    PERFEvents[id].color = def;
}

/** Sets the colour used to draw event id in the overlay. */
void PERFSetEventColor(u8 id, GXColor color) {
    PERFEvents[id].color = color; 
}

/**
 * Starts profiling a frame with interrupts off:
 * resets the sample counter, GX and memory metrics
 * and the PowerPC performance counters (counter 4 is the cycle timer), selects the monitored events,
 * and starts the first automatic sample.
 */
void PERFStartFrame(void) {
    BOOL enabled = OSDisableInterrupts();

    PERFCurrSample = 0;
    CurrToken = 0xFFFF;
    GXSetDrawSyncCallback(PERFTokenCallback);
    PERFFrames[PERFCurrFrame].lastSample = 0;
    PERFResetAllMemMetrics();
    GXClearGPMetric(); 
    PPCMtpmc1(0);
    PPCMtpmc2(0);
    PPCMtpmc3(0);
    PPCMtpmc4(0);
    PPCMtmmcr0(0x8B);
    PPCMtmmcr1(0x78400000);
    PERFStartAutoSample();
    OSRestoreInterrupts(enabled);
}

/**
 * Ends the frame: closes the automatic sample, restores the game's draw-sync callback,
 * records the frame's end time and total cache-miss cycles, advances to the next frame in the history ring,
 * and steps the 4-bit magic that tags this frame's tokens.
 */
void PERFEndFrame(void) {
    u32 i;
    BOOL enabled;

    enabled =  OSDisableInterrupts();
    PERFEndAutoSample();
    GXSetDrawSyncCallback(DSCB);
    PERFFrames[PERFCurrFrame].end = PPCMfpmc4();
    PERFFrames[PERFCurrFrame].lastSample = PERFCurrSample;
    PERFFrames[PERFCurrFrame].cachemisscycles = PPCMfpmc3();
    PERFCurrFrame = (PERFCurrFrame + 1) % PERFNumFrames;
    PERFCurrSample = 0;

    for (i = 0; i < PERFNumEvents; i++) {
        PERFEvents[i].currSample = -1;
    }

    magic += 1;

    if ((u8)magic >= 0x10) {
        magic = 0;
    }

    OSRestoreInterrupts(enabled);
}

/**
 * Marks the start of event id: takes a sample slot, records the CPU start time, cache misses and instructions,
 * and for GP events inserts a GXSetDrawSync token so the GP start time is captured when the GPU reaches it.
 * Reports through OSReport if the event is already open.
 */
void PERFEventStart(u8 id) {
    BOOL enabled;
    s32 sample;

    enabled = OSDisableInterrupts();

    sample = PERFEvents[id].currSample;
    if (sample < 0) {
        sample = PERFGetNewSample();
        PERFEvents[id].currSample = sample;
        PERFFrames[PERFCurrFrame].samples[sample].id = id;
        PERFFrames[PERFCurrFrame].samples[sample].interrupted = 0;

        switch(PERFEvents[id].type) {
        case PERF_GP_EVENT:
            PERFFrames[PERFCurrFrame].samples[sample].cacheMisses[0] = 0;
            PERFFrames[PERFCurrFrame].samples[sample].instructions[0] = 0;
            PERFFrames[PERFCurrFrame].samples[sample].gpTimeStampStart = 0;
            PERFFrames[PERFCurrFrame].samples[sample].gpTimeStampEnd = 0;
            GXSetDrawSync(((u16)sample + 0x10000) + (((u16)magic << 8) & 0xFF00) - 0x2000);
            break;
        case PERF_CPU_GP_EVENT:
            PERFFrames[PERFCurrFrame].samples[sample].gpTimeStampStart = 0;
            PERFFrames[PERFCurrFrame].samples[sample].gpTimeStampEnd = 0;
            PERFFrames[PERFCurrFrame].samples[sample].cacheMisses[0] = PPCMfpmc3();
            PERFFrames[PERFCurrFrame].samples[sample].instructions[0] = PPCMfpmc1();
            GXSetDrawSync(((u16)sample + 0x10000) + (((u16)magic << 8) & 0xFF00) - 0x2000);
            // fallthrough
        case PERF_CPU_EVENT:
            PERFFrames[PERFCurrFrame].samples[sample].cacheMisses[2] = PPCMfpmc3();
            PERFFrames[PERFCurrFrame].samples[sample].instructions[2] = PPCMfpmc1();
            PERFFrames[PERFCurrFrame].samples[sample].origcpuStart = PERFFrames[PERFCurrFrame].samples[sample].cpuTimeStampStart = PPCMfpmc4();
            PERFFrames[PERFCurrFrame].samples[sample].cpuTimeStampEnd = 0;
            break;
        default:
            OSReport("PERF : Unknown event type for ID %d - possibly out of memory\n", id);
            break;
        }
    } else {
        OSReport("PERF : event is still open for CPU!\n");
    }

    OSRestoreInterrupts(enabled);
}

#if DEBUG
__declspec(weak) s32 PERFGetNewSample(void) {
    if (PERFCurrSample >= (PERFNumSamples - 1)) {
        PERFCurrSample = PERFNumSamples - 1;
        return PERFCurrSample;
    }
    return PERFCurrSample++;
}
#endif

/**
 * Marks the end of event id: records the CPU end time, cache misses and instructions,
 * and for GP events inserts the GXSetDrawSync token for the GP end.
 * Reports through OSReport if the event never started.
 */
void PERFEventEnd(u8 id) {
    BOOL enabled;
    s32 sample;

    enabled = OSDisableInterrupts();
    sample = PERFEvents[id].currSample;
    if (sample < 0) {
        OSReport("PERF : ending an event that never started!\n");
        OSRestoreInterrupts(enabled);
        return;
    }

    switch(PERFEvents[id].type) {
    case PERF_GP_EVENT:
        GXSetDrawSync(((u16)sample + 0x10000) + (((u16)magic << 8) & 0xFF00) - 0x1000);
        break;
    case PERF_CPU_GP_EVENT:
        GXSetDrawSync(((u16)sample + 0x10000) + (((u16)magic << 8) & 0xFF00) - 0x1000);
    case PERF_CPU_EVENT:
        PERFFrames[PERFCurrFrame].samples[sample].cpuTimeStampEnd = PPCMfpmc4();
        PERFFrames[PERFCurrFrame].samples[sample].cacheMisses[3] = PPCMfpmc3();
        PERFFrames[PERFCurrFrame].samples[sample].instructions[3] = PPCMfpmc1();
        break;
    }

    PERFEvents[id].currSample = -1;
    OSRestoreInterrupts(enabled);
}

/**
 * Begins a background (id 0xFF) sample used for the bandwidth, CPU and GPU bars,
 * snapshotting the counters at its start.
 */
static void PERFStartAutoSample(void) {
    CurrAutoSample = PERFGetNewSample();
    PERFFrames[PERFCurrFrame].samples[CurrAutoSample].id = 0xFF;
    PERFFrames[PERFCurrFrame].samples[CurrAutoSample].interrupted = 0;
    PERFGetAllMemMetrics(&PERFFrames[PERFCurrFrame].samples[CurrAutoSample], 0);
    PERFFrames[PERFCurrFrame].samples[CurrAutoSample].gpTimeStampStart = PPCMfpmc4();
    PERFFrames[PERFCurrFrame].samples[CurrAutoSample].gpTimeStampEnd = 0;
    PERFFrames[PERFCurrFrame].samples[CurrAutoSample].cacheMisses[0] = PPCMfpmc3();
    PERFFrames[PERFCurrFrame].samples[CurrAutoSample].instructions[0] = PPCMfpmc1();
}

/** Closes the current background sample by snapshotting the counters at its end. */
static void PERFEndAutoSample(void) {
    if (CurrAutoSample >= 0) {
        PERFFrames[PERFCurrFrame].samples[CurrAutoSample].gpTimeStampEnd = PPCMfpmc4();
        PERFGetAllMemMetrics(&PERFFrames[PERFCurrFrame].samples[CurrAutoSample], 1);
        PERFFrames[PERFCurrFrame].samples[CurrAutoSample].cacheMisses[1] = PPCMfpmc3();
        PERFFrames[PERFCurrFrame].samples[CurrAutoSample].instructions[1] = PPCMfpmc1();
    }
    CurrAutoSample = -1;
}

/**
 * Periodic alarm callback for automatic sampling.
 * While a GP event is open it splits that event's sample (copying it so the interval before the split is kept
 * and restarting it); otherwise it closes the current background sample and starts the next.
 */
static void PERFTimerCallback(OSAlarm* alarm, OSContext* context) {
    s32 sample;
    s32 newsample;

    if (PERFCurrSample != 0) {
        if (CurrToken < 0xFFFF) {
            sample = (u8)(u16)CurrToken;
            // stupid CurrToken loading AGAIN
            if ((u8)((CurrToken >> 8) & 0xF) != (s32)magic) {
                PERFEndAutoSample();
                PERFStartAutoSample();
                return;
            }

            ASSERTLINE(884, CurrAutoSample < 0);

            newsample = PERFGetNewSample();
            memcpy(&PERFFrames[PERFCurrFrame].samples[newsample], &PERFFrames[PERFCurrFrame].samples[sample], 0xB0);
            PERFFrames[PERFCurrFrame].samples[newsample].gpTimeStampEnd = PPCMfpmc4();
            PERFFrames[PERFCurrFrame].samples[newsample].cacheMisses[1] = PPCMfpmc3();
            PERFFrames[PERFCurrFrame].samples[newsample].instructions[1] = PPCMfpmc1();
            PERFGetAllMemMetrics(&PERFFrames[PERFCurrFrame].samples[newsample], 1);
            PERFFrames[PERFCurrFrame].samples[newsample].id = 0xFF;
            PERFFrames[PERFCurrFrame].samples[sample].gpTimeStampStart = PPCMfpmc4();
            PERFFrames[PERFCurrFrame].samples[sample].cacheMisses[0] = PPCMfpmc3();
            PERFFrames[PERFCurrFrame].samples[sample].instructions[0] = PPCMfpmc1();
            PERFGetAllMemMetrics(&PERFFrames[PERFCurrFrame].samples[sample], 0);
            PERFFrames[PERFCurrFrame].samples[sample].interrupted = 1;
            CurrAutoSample = -1;
            return;
        }

        if (CurrAutoSample < 0) {
            OSReport("PERF : AUTOSAMPLE < 0!!!! SHOULD NEVER HAPPEN!\n");
            return;
        }

        PERFEndAutoSample();
        PERFStartAutoSample();
    }
}

/** Starts a periodic OS alarm that runs PERFTimerCallback every msInterval milliseconds. */
void PERFStartAutoSampling(f32 msInterval) {
    OSSetPeriodicAlarm(&PERFAlarm, OSGetTime(), (u32)OSMillisecondsToTicks(msInterval), PERFTimerCallback);
}

/** Closes the open background sample and cancels the sampling alarm. */
void PERFStopAutoSampling(void) {
    BOOL enabled = OSDisableInterrupts();

    if (CurrAutoSample >= 0) {
        PERFFrames[PERFCurrFrame].samples[CurrAutoSample].gpTimeStampEnd = PPCMfpmc4();
        PERFGetAllMemMetrics(&PERFFrames[PERFCurrFrame].samples[CurrAutoSample], 1);
    }

    OSCancelAlarm(&PERFAlarm);
    OSRestoreInterrupts(enabled);
}

/** Stops sampling, restores the game's draw-sync callback and frees the tables allocated by PERFInit. */
void PERFShutDown(void) {
    BOOL enabled;
    u32 i;

    enabled = OSDisableInterrupts();
    PERFStopAutoSampling();
    PERFEndAutoSample();
    GXSetDrawSyncCallback(DSCB);

    for (i = 0; i < PERFNumFrames; i++) {
        PerfFree(PERFFrames[i].samples);
    }

    PerfFree(PERFEvents);
    PerfFree(PERFFrames);
    OSRestoreInterrupts(enabled);
}
