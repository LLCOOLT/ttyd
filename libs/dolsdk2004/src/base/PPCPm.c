#include <dolphin.h>
#include <dolphin/base/PPCArch.h>

/**
 * Clears the performance monitor control registers MMCR0 and MMCR1 and counters PMC1-4,
 * then programs MMCR0 = 0x4F and MMCR1 = 0x78800000, which by the PPCArch.h selector values counts processor
 * cycles in PMC1, L1 instruction fetch misses in PMC2, cycles caused by L1 load misses in PMC3
 * and completed instructions in PMC4.
 */
void PMBegin(void) {
    PPCMtmmcr0(0);
    PPCMtmmcr1(0);
    PPCMtpmc1(0);
    PPCMtpmc2(0);
    PPCMtpmc3(0);
    PPCMtpmc4(0);
    PPCMtmmcr0(0x4F);
    PPCMtmmcr1(0x78800000);
}

/** Stops the performance monitor by clearing MMCR0 and MMCR1. */
void PMEnd(void) {
    PPCMtmmcr0(0);
    PPCMtmmcr1(0);
}

/** Reads PMC1 (the result is left in the return register): processor cycles since PMBegin. */
void PMCycles(void) {
    PPCMfpmc1();
}

/** Reads PMC2 (the result is left in the return register): L1 instruction fetch misses since PMBegin. */
void PML1FetchMisses(void) {
    PPCMfpmc2();
}

/** Reads PMC3 (the result is left in the return register): cycles caused by L1 load misses since PMBegin. */
void PML1MissCycles(void) {
    PPCMfpmc3();
}

/** Reads PMC4 (the result is left in the return register): instructions completed since PMBegin. */
void PMInstructions(void) {
    PPCMfpmc4();
}
