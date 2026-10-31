#include "musyx/platform.h"

#if MUSY_TARGET == MUSY_TARGET_PC
#include <pthread.h>
#include "musyx/assert.h"
#include "musyx/hardware.h"
#include "musyx/sal.h"
#include <string.h>

static volatile u32 oldState = 0;
static volatile u16 hwIrqLevel = 0;
static volatile u32 salDspInitIsDone = 0;
static volatile u64 salLastTick = 0;
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

#define DMA_BUFFER_LEN 0x280
pthread_mutex_t globalMutex;
pthread_mutex_t globalInterrupt;

u32 salGetStartDelay();
/** PC build version of the frame callback runner (interrupt control compiled out). */
static void callUserCallback() {
  if (salLogicActive) {
    return;
  }
  salLogicActive = 1;
  // OSEnableInterrupts();
  userCallback();
  // OSDisableInterrupts();
  salLogicActive = 0;
}

/** PC build: advances the output buffer index and runs or defers the frame callback; AI DMA calls are commented out. */
void salCallback() {
  salAIBufferIndex = (salAIBufferIndex + 1) % 4;
  // AIInitDMA(OSCachedToPhysical(salAIBufferBase) + (salAIBufferIndex * DMA_BUFFER_LEN),
  //           DMA_BUFFER_LEN);
  salLastTick = 0; // OSGetTick();
  if (salDspIsDone) {
    callUserCallback();
  } else {
    salLogicIsWaiting = 1;
  }
}

/** PC build: marks the (nonexistent) DSP as booted. */
void dspInitCallback() {
  salDspIsDone = TRUE;
  salDspInitIsDone = TRUE;
}

/** PC build: marks the DSP done and runs a deferred frame callback. */
void dspResumeCallback() {
  salDspIsDone = TRUE;
  if (salLogicIsWaiting) {
    salLogicIsWaiting = FALSE;
    callUserCallback();
  }
}

/** PC build: allocates the four output buffers and reports 32000 Hz, without registering an AI DMA callback. */
bool salInitAi(SND_SOME_CALLBACK callback, u32 unk, u32* outFreq) {
  if ((salAIBufferBase = salMalloc(DMA_BUFFER_LEN * 4)) != NULL) {
    memset(salAIBufferBase, 0, DMA_BUFFER_LEN * 4);
    // DCFlushRange(salAIBufferBase, DMA_BUFFER_LEN * 4);
    salAIBufferIndex = TRUE;
    salLogicIsWaiting = FALSE;
    salDspIsDone = TRUE;
    salLogicActive = FALSE;
    userCallback = callback;
    // AIRegisterDMACallback(salCallback);
    // AIInitDMA(OSCachedToPhysical(salAIBufferBase) + (salAIBufferIndex * 0x280), 0x280);
    synthInfo.numSamples = 0x20;
    *outFreq = 32000;
    MUSY_DEBUG("MusyX AI interface initialized.\n");
    return TRUE;
  }

  return FALSE;
}

/** PC build: does nothing (the GameCube version starts AI DMA). */
bool salStartAi() { } //AIStartDMA(); }

/** PC build: frees the output buffers. */
bool salExitAi() {
  salFree(salAIBufferBase);
  return TRUE;
}

/** PC build: computes the destination index but returns NULL. */
void* salAiGetDest() {
  u8 index; // r31
  index = (salAIBufferIndex + 2) % 4;
  return NULL;
}

/** PC build: nothing to start, returns TRUE. */
bool salInitDsp(u32) { return TRUE; }

/** PC build: empty. */
bool salExitDsp() {}

/** PC build: empty. */
void salStartDsp(u16* cmdList) {}

/** PC build: builds the command list but there is no DSP to send it to. */
void salCtrlDsp(s16* dest) {
  salBuildCommandList(dest, salGetStartDelay());
  salStartDsp(dspCmdList);
}

/** PC build: always 0. */
u32 salGetStartDelay() { return 0; }

/** PC build: sets the nesting level to 1 and creates the robust global mutex used as the "interrupt" lock. */
void hwInitIrq() {
  // oldState = OSDisableInterrupts();
  hwIrqLevel = 1;
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ROBUST);
  pthread_mutex_init(&globalMutex, &attr);
}

/** PC build: empty. */
void hwExitIrq() {}

/** PC build: drops the nesting level (the interrupt restore is commented out). */
void hwEnableIrq() {
  if (--hwIrqLevel == 0) {
    // OSRestoreInterrupts(oldState);
  }
}

/** PC build: raises the nesting level (the interrupt disable is commented out). */
void hwDisableIrq() {
  if ((hwIrqLevel++) == 0) {
    // oldState = OSDisableInterrupts();
  }
}

/** PC build: takes the global mutex. */
void hwIRQEnterCritical() {
  pthread_mutex_lock(&globalMutex);
}

/** PC build: releases the global mutex. */
void hwIRQLeaveCritical() {
  pthread_mutex_unlock(&globalMutex);
}
#endif
