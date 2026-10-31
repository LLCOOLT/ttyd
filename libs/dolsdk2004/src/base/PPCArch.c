#include <dolphin.h>
#include <dolphin/base/PPCArch.h>

/** Reads the PowerPC Machine State Register. Original assembly. */
asm u32 PPCMfmsr() {
    nofralloc
    mfmsr r3
    blr    
}

/** Writes the Machine State Register. Original assembly. */
asm void PPCMtmsr(register u32 newMSR) {
    nofralloc
    mtmsr newMSR
    blr
}

/** Returns the MSR ORed with 'value' (it does not write the result back to the MSR). Original assembly. */
asm u32 PPCOrMsr(register u32 value) {
    nofralloc
    mfmsr r4
    or value, r4, value
    blr
}

/** Returns the MSR ANDed with 'value' (it does not write the result back to the MSR). Original assembly. */
asm u32 PPCAndMsr(register u32 value) {
    nofralloc
    mfmsr r4
    and value, r4, value
    blr
}

/**
 * Returns the MSR with the bits of 'value' cleared (it does not write the result back to the MSR).
 * Original assembly.
 */
asm u32 PPCAndCMsr(register u32 value) {
    nofralloc
    mfmsr r4
    andc value, r4, value
    blr
}

/** Reads the hardware implementation register HID0. Original assembly. */
asm u32 PPCMfhid0() {
    nofralloc
    mfspr r3, HID0
    blr
}

/** Writes HID0. Original assembly. */
asm void PPCMthid0(register u32 newHID0) {
    nofralloc
    mtspr HID0, newHID0
    blr
}

/** Reads the hardware implementation register HID1. Original assembly. */
asm u32 PPCMfhid1() {
    nofralloc
    mfspr r3, HID1
    blr
}

/** Reads the L2 cache control register L2CR. Original assembly. */
asm u32 PPCMfl2cr() {
    nofralloc
    mfspr r3, L2CR
    blr
}

/** Writes the L2 cache control register. Original assembly. */
asm void PPCMtl2cr(register u32 newL2cr) {
    nofralloc
    mtspr L2CR, newL2cr
    blr
}

/** Writes the decrementer register, the countdown timer that raises the decrementer interrupt. Original assembly. */
asm void PPCMtdec(register u32 newDec) {
    nofralloc
    mtdec newDec
    blr
}

/** Reads the decrementer register. Original assembly. */
asm u32 PPCMfdec() {
    nofralloc
    mfdec r3
    blr
}

/** Executes a system-call instruction (sc), which acts as a context-synchronizing barrier here. Original assembly. */
asm void PPCSync() {
    nofralloc
    sc
    blr
}

/**
 * Issues an eieio barrier with interrupts masked:
 * clears the MSR interrupt-enable bit and sets a bit in HID0 around the eieio and isync, then restores both.
 * Original assembly.
 */
asm void PPCEieio() {
    nofralloc
    mfmsr r5
    rlwinm r6, r5, 0, 17, 15
    mtmsr r6
    mfspr r3, HID0
    ori r4, r3, 0x8
    mtspr HID0, r4
    isync
    eieio
    isync
    mtspr HID0, r3
    mtmsr r5
    isync
    blr
}

/** Stops the processor: a sync followed by an endless loop of nops. Original assembly. */
asm void PPCHalt() {
    nofralloc
    sync
loop:
    nop
    li r3, 0
    nop
    b loop
}

/** Reads performance monitor control register MMCR0. Original assembly. */
asm u32 PPCMfmmcr0() {
    nofralloc
    mfspr r3, MMCR0
    blr
}

/** Writes performance monitor control register MMCR0. Original assembly. */
asm void PPCMtmmcr0(register u32 newMmcr0) {
    nofralloc
    mtspr MMCR0, newMmcr0
    blr
}

/** Reads performance monitor control register MMCR1. Original assembly. */
asm u32 PPCMfmmcr1() {
    nofralloc
    mfspr r3, MMCR1
    blr
}

/** Writes performance monitor control register MMCR1. Original assembly. */
asm void PPCMtmmcr1(register u32 newMmcr1) {
    nofralloc
    mtspr MMCR1, newMmcr1
    blr
}

/** Reads performance counter PMC1. Original assembly. */
asm u32 PPCMfpmc1() {
    nofralloc
    mfspr r3, PMC1
    blr
}

/** Writes performance counter PMC1. Original assembly. */
asm void PPCMtpmc1(register u32 newPmc1) {
    nofralloc
    mtspr PMC1, newPmc1
    blr
}

/** Reads performance counter PMC2. Original assembly. */
asm u32 PPCMfpmc2() {
    nofralloc
    mfspr r3, PMC2
    blr
}

/** Writes performance counter PMC2. Original assembly. */
asm void PPCMtpmc2(register u32 newPmc2) {
    nofralloc
    mtspr PMC2, newPmc2
    blr
}

/** Reads performance counter PMC3. Original assembly. */
asm u32 PPCMfpmc3() {
    nofralloc
    mfspr r3, PMC3
    blr
}

/** Writes performance counter PMC3. Original assembly. */
asm void PPCMtpmc3(register u32 newPmc3) {
    nofralloc
    mtspr PMC3, newPmc3
    blr
}

/** Reads performance counter PMC4. Original assembly. */
asm u32 PPCMfpmc4() {
    nofralloc
    mfspr r3, PMC4
    blr
}

/** Writes performance counter PMC4. Original assembly. */
asm void PPCMtpmc4(register u32 newPmc4) {
    nofralloc
    mtspr PMC4, newPmc4
    blr
}

/** Reads the sampled instruction address register SIA. Original assembly. */
asm u32 PPCMfsia() {
    nofralloc
    mfspr r3, SIA
    blr
}

/** Writes the sampled instruction address register SIA. Original assembly. */
asm void PPCMtsia(register u32 newSia) {
    nofralloc
    mtspr SIA, newSia
    blr
}

/**
 * Reads the floating-point status and control register by storing FPR 31 (loaded with mffs) to memory
 * and returning its low word. Inline assembly in a C function.
 */
u32 PPCMffpscr() {
    union FpscrUnion m;

    asm {
        mffs fp31
        stfd fp31, m.f;
    }

    return m.u.fpscr; 
}

/**
 * Writes the floating-point status and control register through FPR 31 with mtfsf, all fields.
 * Inline assembly in a C function.
 */
void PPCMtfpscr(register u32 newFPSCR) {
    union FpscrUnion m;

    asm {
        li    r4, 0
        stw   r4, m.u.fpscr_pad;
        stw   newFPSCR, m.u.fpscr
        lfd   fp31, m.f
        mtfsf 0xff, fp31
    }
}

/** Reads the Gekko extension register HID2. Original assembly. */
asm u32 PPCMfhid2() {
    nofralloc
    mfspr r3, HID2
    blr
}

/** Writes the Gekko extension register HID2. Original assembly. */
asm void PPCMthid2(register u32 newhid2) {
    nofralloc
    mtspr HID2, newhid2
    blr
}

/** Does a sync, then reads the write-gather pipe address register WPAR. Original assembly. */
asm u32 PPCMfwpar() {
    nofralloc
    sync
    mfspr r3, WPAR
    blr
}

/** Writes the write-gather pipe address register WPAR. Original assembly. */
asm void PPCMtwpar(register u32 newwpar) {
    nofralloc
    mtspr WPAR, newwpar
    blr
}

/** Reads the upper DMA register DMA_U. Original assembly. */
asm u32 PPCMfdmaU() {
    nofralloc
    mfspr r3, DMA_U
    blr
}

/** Reads the lower DMA register DMA_L. Original assembly. */
asm u32 PPCMfdmaL() {
    nofralloc
    mfspr r3, DMA_L
    blr
}

/** Writes the upper DMA register DMA_U. Original assembly. */
asm void PPCMtdmaU(register u32 newdmau) {
    nofralloc
    mtspr DMA_U, newdmau
    blr
}

/** Writes the lower DMA register DMA_L. Original assembly. */
asm void PPCMtdmaL(register u32 newdmal) {
    nofralloc
    mtspr DMA_L, newdmal
    blr
}

/** Reads the processor version register. Original assembly. */
asm u32 PPCMfpvr() {
    nofralloc
    mfspr r3, PVR
    blr
}

/** Clears the HID0 speculation-disable bit (HID0_SPD). */
void PPCEnableSpeculation(void) {
    PPCMthid0(PPCMfhid0() & ~HID0_SPD);
}

/** Sets the HID0 speculation-disable bit (HID0_SPD). */
void PPCDisableSpeculation(void) {
    PPCMthid0(PPCMfhid0() | HID0_SPD);
}

/** Clears FPSCR bit 29 (the non-IEEE mode bit) with mtfsb0. Original assembly. */
asm void PPCSetFpIEEEMode() {
	nofralloc
	mtfsb0 29
	blr
}

/** Sets FPSCR bit 29 (the non-IEEE mode bit) with mtfsb1. Original assembly. */
asm void PPCSetFpNonIEEEMode() {
	nofralloc
	mtfsb1 29
	blr
}
