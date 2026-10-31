#include "dolphin/PPCArch.h"
#include "musyx/musyx_priv.h"

SND_PROF_USERCALLBACK sndProfUserCallback = NULL;

/**
 * Installs the callback that would receive the per-frame profile;
 * snd_handle_irq has its calls commented out in this build.
 */
void sndProfSetCallback(SND_PROF_USERCALLBACK callback) { sndProfUserCallback = callback; }

/** Copies the running music and sound-effect voice counts into the profile info. */
void sndProfUpdateMisc(SND_PROFILE_INFO* info) {
  info->numMusicVoices = voiceMusicRunning;
  info->numSFXVoices = voiceFxRunning;
}

/**
 * Zeroes the four PowerPC performance counters and every total, peak and count in the profile record,
 * leaving it paused.
 */
void sndProfResetPMC(SND_PROFILE_DATA* info) {
  PPCMtpmc1(0);
  PPCMtpmc2(0);
  PPCMtpmc3(0);
  PPCMtpmc4(0);
  info->sumLoadStores = info->loadStores = 0;
  info->sumMissCycles = info->missCycles = 0;
  info->sumCycles = info->cycles = 0;
  info->sumInstructions = info->instructions = 0;
  info->peekLoadStores = 0;
  info->peekMissCycles = 0;
  info->peekCycles = 0;
  info->peekInstructions = 0;
  info->cnt = 0;
  info->paused = 1;
}
/**
 * Snapshots the PMC1-4 counters (instructions, load/stores, miss cycles, cycles) into the record
 * and starts counting.
 */
void sndProfStartPMC(SND_PROFILE_DATA* info) {
  PPCMtmmcr0(0);
  PPCMtmmcr1(0);
  info->paused = 0;
  info->_loadStores = PPCMfpmc2();
  info->_missCycles = PPCMfpmc3();
  info->_cycles = PPCMfpmc4();
  info->_instructions = PPCMfpmc1();
  PPCMtmmcr1(0x78400000);
  PPCMtmmcr0(0xc08b);
}

/** Stops counting and adds the counter deltas since the last start to the record's running totals. */
void sndProfPausePMC(SND_PROFILE_DATA* info) {
  PPCMtmmcr0(0);
  PPCMtmmcr1(0);
  info->loadStores += PPCMfpmc2() - info->_loadStores;
  info->missCycles += PPCMfpmc3() - info->_missCycles;
  info->cycles += PPCMfpmc4() - info->_cycles;
  info->instructions += PPCMfpmc1() - info->_instructions;
  info->paused = 1;
  PPCMtmmcr1(0x78400000);
  PPCMtmmcr0(0xc08b);
}
/**
 * Finishes a profiled section: adds the last deltas, then updates the count, sums, averages,
 * last values and peaks for load/stores, miss cycles, cycles and instructions,
 * and clears the per-section counters.
 */
void sndProfStopPMC(SND_PROFILE_DATA* info) {
  PPCMtmmcr0(0);
  PPCMtmmcr1(0);
  if (info->paused == 0) {
    info->loadStores = info->loadStores + (PPCMfpmc2() - info->_loadStores);
    info->missCycles = info->missCycles + (PPCMfpmc3() - info->_missCycles);
    info->cycles = info->cycles + (PPCMfpmc4() - info->_cycles);
    info->instructions = info->instructions + (PPCMfpmc1() - info->_instructions);
    info->paused = 1;
  }
  info->cnt = info->cnt + 1;
  info->sumLoadStores += info->loadStores;
  info->sumMissCycles += info->missCycles;

  info->sumCycles += info->cycles;
  info->sumInstructions += info->instructions;
  info->avgLoadStores = info->sumLoadStores / info->cnt;
  info->avgMissCycles = info->sumMissCycles / info->cnt;
  info->avgCycles = info->sumCycles / info->cnt;
  info->avgInstructions = info->sumInstructions / info->cnt;
  info->lastLoadStores = info->loadStores;
  info->lastMissCycles = info->missCycles;
  info->lastCycles = info->cycles;
  info->lastInstructions = info->instructions;
  if (info->loadStores > info->peekLoadStores) {
    info->peekLoadStores = info->loadStores;
  }
  if (info->missCycles > info->peekMissCycles) {
    info->peekMissCycles = info->missCycles;
  }
  if (info->cycles > info->peekCycles) {
    info->peekCycles = info->cycles;
  }
  if (info->instructions > info->peekInstructions) {
    info->peekInstructions = info->instructions;
  }
  info->loadStores = 0;
  info->missCycles = 0;
  info->cycles = 0;
  info->instructions = 0;
  PPCMtmmcr1(0x78400000);
  PPCMtmmcr0(0xc08b);
}
