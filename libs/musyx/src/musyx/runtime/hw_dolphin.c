#include "musyx/platform.h"

#if MUSY_TARGET == MUSY_TARGET_DOLPHIN
#include "dolphin/dsp.h"
#include "musyx/assert.h"
#include "musyx/dsp_import.h"
#include "musyx/hardware.h"
#include "musyx/sal.h"
#include "dolphin/ai.h"
#include "dolphin/base/PPCArch.h"

static DSPTaskInfo dsp_task ATTRIBUTE_ALIGN(8);
static u16 dram_image[4096] ATTRIBUTE_ALIGN(32);

#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 3)
// Uninitialized, so MWCC lays these out in reverse declaration order
static SND_SOME_CALLBACK userCallback;
static u8 salAIBufferIndex;
void* salAIBufferBase;
static volatile u32 salDspIsDone;
static volatile u32 salLogicIsWaiting;
static volatile u32 salLogicActive;
static volatile OSTick salLastTick;
static volatile u32 salDspInitIsDone;
static OSThreadQueue salWaitForDSPThreadQueue;
static volatile u16 hwIrqLevel;
static volatile u32 oldState;
#else
static volatile u32 oldState = 0;
static volatile u16 hwIrqLevel = 0;
static volatile u32 salDspInitIsDone = 0;
static volatile OSTick salLastTick = 0;
static volatile u32 salLogicActive = 0;
static volatile u32 salLogicIsWaiting = 0;
static volatile u32 salDspIsDone = 0;
/** Base address of the audio output buffers in memory. */
void* salAIBufferBase = NULL;
/**
 * Index of the audio output buffer being filled, and the callback the application registered for each
 * finished buffer.
 */
static u8 salAIBufferIndex = 0;
static SND_SOME_CALLBACK userCallback = NULL;
#endif

#define DMA_BUFFER_LEN 0x280

u32 salGetStartDelay();
/** Runs the registered per-frame callback (snd_handle_irq) with interrupts enabled, unless it is already running
 * (salLogicActive guards against re-entry). */
static void callUserCallback() {
  if (salLogicActive) {
    return;
  }
  salLogicActive = 1;
  OSEnableInterrupts();
  userCallback();
  OSDisableInterrupts();
  salLogicActive = 0;
}

/** AI DMA-complete interrupt: advances to the next of the four 0x280-byte output buffers and queues it with AIInitDMA,
 * records the tick, then runs the frame callback if the DSP has finished its previous frame; otherwise marks it as
 * waiting for the DSP. */
void salCallback() {
  salAIBufferIndex = (salAIBufferIndex + 1) % 4;
  AIInitDMA(OSCachedToPhysical(salAIBufferBase) + (salAIBufferIndex * DMA_BUFFER_LEN),
            DMA_BUFFER_LEN);
  salLastTick = OSGetTick();
  if (salDspIsDone) {
    callUserCallback();
  } else {
    salLogicIsWaiting = 1;
  }
}

// DSP task init callback: marks the DSP as done and booted (salDspInitIsDone), which releases the wait in salInitDsp.
void dspInitCallback() {
  salDspIsDone = TRUE;
  salDspInitIsDone = TRUE;
}

/** DSP task resume callback, fired when the DSP finishes a frame: marks it done and, if the AI interrupt came in
 * meanwhile, runs the frame callback now. */
void dspResumeCallback() {
  salDspIsDone = TRUE;
  if (salLogicIsWaiting) {
    salLogicIsWaiting = FALSE;
    callUserCallback();
  }
}

#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 3)
/** DSP task done callback: wakes the threads waiting on salWaitForDSPThreadQueue. */
void dspDoneCallback() { OSWakeupThread(&salWaitForDSPThreadQueue); }
#endif

/** Allocates four 0x280-byte AI output buffers (5 ms of 32 kHz stereo each), registers salCallback as the AI DMA
 * callback, queues the first buffer, sets 32 samples per synth step and returns 32000 through outFreq. Returns FALSE if
 * the allocation fails. */
u32 salInitAi(SND_SOME_CALLBACK callback, u32 unk, u32* outFreq) {
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 3)
  if ((salAIBufferBase = salMallocPhysical(DMA_BUFFER_LEN * 4)) != NULL) {
#else
  if ((salAIBufferBase = salMalloc(DMA_BUFFER_LEN * 4)) != NULL) {
#endif
    memset(salAIBufferBase, 0, DMA_BUFFER_LEN * 4);
    DCFlushRange(salAIBufferBase, DMA_BUFFER_LEN * 4);
    salAIBufferIndex = TRUE;
    salLogicIsWaiting = FALSE;
    salDspIsDone = TRUE;
    salLogicActive = FALSE;
    userCallback = callback;
    AIRegisterDMACallback(salCallback);
    AIInitDMA(OSCachedToPhysical(salAIBufferBase) + (salAIBufferIndex * 0x280), 0x280);
    synthInfo.numSamples = 0x20;
    *outFreq = 32000;
    MUSY_DEBUG("MusyX AI interface initialized.\n");
    return TRUE;
  }

  return FALSE;
}

/** Starts AI DMA. */
u32 salStartAi() { AIStartDMA(); }

/** Unregisters the AI callback, stops AI DMA and frees the buffers. */
u32 salExitAi() {
  AIRegisterDMACallback(NULL);
  AIStopDMA();
  salFree(salAIBufferBase);
  return TRUE;
}

/** Returns the AI buffer two slots ahead of the one now playing; the DSP mixes the next frame into it. */
void* salAiGetDest() {
  u8 index; // r31
  index = (salAIBufferIndex + 2) % 4;
  return (void*)((u8*)salAIBufferBase + index * DMA_BUFFER_LEN);
}

/** Fills in the DSP task (MusyX slave microcode in IRAM, 0x2000-word DRAM image), initializes the DSP, adds the task
 * and waits (with interrupts enabled) until dspInitCallback reports it has booted. */
u32 salInitDsp() {
  u8 _[8];
  dsp_task.iram_mmem_addr = (u16*)dspSlave;
  dsp_task.iram_length = dspSlaveLength;
  dsp_task.iram_addr = 0;
  dsp_task.dram_mmem_addr = (u16*)dram_image;
  dsp_task.dram_length = 0x2000;
  dsp_task.dram_addr = 0;
  dsp_task.dsp_init_vector = 0x10;
  dsp_task.dsp_resume_vector = 0x30;
  dsp_task.init_cb = dspInitCallback;
  dsp_task.res_cb = dspResumeCallback;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 3)
  dsp_task.done_cb = dspDoneCallback;
#else
  dsp_task.done_cb = NULL;
#endif
  dsp_task.req_cb = NULL;
  dsp_task.priority = 0;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 3)
  OSInitThreadQueue(&salWaitForDSPThreadQueue);
#endif
  DSPInit();
  DSPAddTask(&dsp_task);
  salDspInitIsDone = FALSE;
  hwEnableIrq();
  while (!salDspInitIsDone)
    ;
  hwDisableIrq();
  return TRUE;
}

/** Halts the DSP, waits for outstanding DSP DMA and resets it. */
u32 salExitDsp() {
  DSPHalt();
  while (DSPGetDMAStatus())
    ;
  DSPReset();

  return TRUE;
}
/** Starts one DSP frame: clears the done flag and sends the DSP two mailbox words, the command list size tagged 0xBABE
 * and the (32-byte aligned) command list address. */
void salStartDsp(u16* cmdList) {
  salDspIsDone = FALSE;
  PPCSync();
  /* clang-format off */
  MUSY_ASSERT(((u32)cmdList&0x1F) == 0);
  /* clang-format on */
  DSPSendMailToDSP(dspCmdFirstSize | 0xbabe0000);

  while (DSPCheckMailToDSP())
    ;
  DSPSendMailToDSP((u32)cmdList);
  while (DSPCheckMailToDSP())
    ;
}

/** Builds this frame's command list for the output buffer dest, passing the time since the last AI interrupt, and sends
 * it to the DSP. */
void salCtrlDsp(s16* dest) {
  salBuildCommandList(dest, salGetStartDelay());
  salStartDsp(dspCmdList);
}

/** Returns the microseconds since the last AI DMA interrupt. */
u32 salGetStartDelay() { return OSTicksToMicroseconds(OSGetTick() - salLastTick); }

/** Disables interrupts and sets the nesting level to 1; hwEnableIrq undoes it when the init finishes. */
void hwInitIrq() {
  oldState = OSDisableInterrupts();
  hwIrqLevel = 1;
}

/** Empty. */
void hwExitIrq() {}

/** Drops one level of interrupt disable nesting and restores the saved interrupt state when it reaches 0. */
void hwEnableIrq() {
  if (--hwIrqLevel == 0) {
    OSRestoreInterrupts(oldState);
  }
}

/** Adds one level of interrupt disable nesting, saving the interrupt state on the first. */
void hwDisableIrq() {
  if ((hwIrqLevel++) == 0) {
    oldState = OSDisableInterrupts();
  }
}

/** Disables interrupts (the return value is not kept; hwIRQLeaveCritical just enables them again). */
void hwIRQEnterCritical() { OSDisableInterrupts(); }

/** Enables interrupts. */
void hwIRQLeaveCritical() { OSEnableInterrupts(); }
#endif
