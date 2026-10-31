#include <dolphin.h>
#include <dolphin/db.h>
#include <dolphin/os.h>

#include "__os.h"

#define HID2 920

// prototypes
void DMAErrorHandler(OSError error, OSContext* context, ...);

/** Assembly: sets the HID0 data-cache flash-invalidate bit, discarding the whole L1 data cache. */
#ifdef __GEKKO__
asm void DCFlashInvalidate(void) {
    nofralloc
    mfspr r3, HID0
    ori r3, r3, 0x400
    mtspr HID0, r3
    blr
}

/** Assembly: syncs and sets the HID0 data-cache enable bit. */
asm void DCEnable(void) {
    nofralloc
    sync
    mfspr r3, HID0
    ori   r3, r3, 0x4000
    mtspr HID0, r3
    blr
}

/** Assembly: syncs and clears the HID0 data-cache enable bit. */
asm void DCDisable(void) {
    nofralloc
    sync
    mfspr r3, HID0
    rlwinm r3, r3, 0, 18, 16
    mtspr HID0, r3
    blr
}

/** Assembly: sets the HID0 data-cache lock bit so misses stop allocating lines. */
asm void DCFreeze(void) {
    nofralloc
    sync
    mfspr r3, HID0
    ori r3, r3, 0x1000
    mtspr HID0, r3
    blr
}

/** Assembly: clears the HID0 data-cache lock bit. */
asm void DCUnfreeze(void) {
    nofralloc
    mfspr r3, HID0
    rlwinm r3, r3, 0, 20, 18
    mtspr HID0, r3
    blr
}

/** Assembly: dcbt, hints the line containing addr into the data cache. */
asm void DCTouchLoad(register void* addr) {
    nofralloc
    dcbt r0, addr
    blr
}

/** Assembly: dcbz, zeroes the 32-byte cache line at addr without reading memory. */
asm void DCBlockZero(register void* addr) {
    nofralloc
    dcbz r0, addr
    blr
}

/** Assembly: dcbst, writes the line at addr back to memory but leaves it cached. */
asm void DCBlockStore(register void* addr) {
    nofralloc
    dcbst r0, addr
    blr
}

/** Assembly: dcbf, writes the line at addr back to memory and invalidates it. */
asm void DCBlockFlush(register void* addr) {
    nofralloc
    dcbf r0, addr
    blr
}

/** Assembly: dcbi, invalidates the line at addr without writing it back. */
asm void DCBlockInvalidate(register void* addr) {
    nofralloc
    dcbi r0, addr
    blr
}

/**
 * Assembly: invalidates all cache lines covering [addr, addr + nBytes), discarding changes;
 * used before the CPU reads memory that a DMA wrote.
 */
asm void DCInvalidateRange(register void* addr, register u32 nBytes) {
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add    nBytes, nBytes, r5
    addi   nBytes, nBytes, 31
    srwi   nBytes, nBytes, 5
    mtctr  nBytes

@1
    dcbi r0, addr
    addi addr, addr, 32
    bdnz @1
    blr
}

/**
 * Assembly: writes back and invalidates all cache lines covering [addr, addr + nBytes), then syncs;
 * used before a DMA reads memory the CPU wrote.
 */
asm void DCFlushRange(register void* addr, register u32 nBytes) {
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add nBytes, nBytes, r5
    addi nBytes, nBytes, 31
    srwi nBytes, nBytes, 5
    mtctr nBytes

@1
    dcbf r0, addr
    addi addr, addr, 32
    bdnz @1
    sc
    blr
}

/** Assembly: writes back (without invalidating) all lines covering the range, then syncs. */
asm void DCStoreRange(register void* addr, register u32 nBytes) {
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add nBytes, nBytes, r5
    addi nBytes, nBytes, 31
    srwi nBytes, nBytes, 5
    mtctr nBytes

@1
    dcbst r0, addr
    addi addr, addr, 32
    bdnz @1
    sc

    blr
}

/** Assembly: like DCFlushRange but without the closing sync. */
asm void DCFlushRangeNoSync(register void* addr, register u32 nBytes) {
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add nBytes, nBytes, r5
    addi nBytes, nBytes, 31
    srwi nBytes, nBytes, 5
    mtctr nBytes

@1
    dcbf r0, addr
    addi addr, addr, 32
    bdnz @1
    blr
}

/** Assembly: like DCStoreRange but without the closing sync. */
asm void DCStoreRangeNoSync(register void* addr, register u32 nBytes) {
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add nBytes, nBytes, r5
    addi nBytes, nBytes, 31
    srwi nBytes, nBytes, 5
    mtctr nBytes

@1
    dcbst r0, addr
    addi addr, addr, 32
    bdnz @1

    blr
}

/** Assembly: zeroes all cache lines covering the range with dcbz; fast memset for 32-byte aligned buffers. */
asm void DCZeroRange(register void* addr, register u32 nBytes) {
  nofralloc
  cmplwi nBytes, 0
  blelr
  clrlwi r5, addr, 27
  add nBytes, nBytes, r5
  addi nBytes, nBytes, 31
  srwi nBytes, nBytes, 5
  mtctr nBytes

@1
  dcbz r0, addr
  addi addr, addr, 32
  bdnz @1

  blr
}

/** Assembly: prefetches all lines covering the range into the data cache. */
asm void DCTouchRange(register void* addr, register u32 nBytes) {
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add nBytes, nBytes, r5
    addi nBytes, nBytes, 31
    srwi nBytes, nBytes, 5
    mtctr nBytes

@1
    dcbt r0, addr
    addi addr, addr, 32
    bdnz @1

    blr
}

/**
 * Assembly: invalidates all instruction cache lines covering the range, then syncs and isyncs;
 * needed after writing code (module loading, exception vectors).
 */
asm void ICInvalidateRange(register void* addr, register u32 nBytes) {
    nofralloc
    cmplwi nBytes, 0
    blelr
    clrlwi r5, addr, 27
    add nBytes, nBytes, r5
    addi nBytes, nBytes, 31
    srwi nBytes, nBytes, 5
    mtctr nBytes

@1
    icbi r0, addr
    addi addr, addr, 32
    bdnz @1
    sync
    isync

    blr
}

/** Assembly: sets the HID0 instruction-cache flash-invalidate bit. */
asm void ICFlashInvalidate(void) {
    nofralloc
    mfspr r3, HID0
    ori r3, r3, 0x800
    mtspr HID0, r3
    blr
}

/** Assembly: isyncs and sets the HID0 instruction-cache enable bit. */
asm void ICEnable(void) {
    nofralloc
    isync
    mfspr r3, HID0
    ori r3, r3, 0x8000
    mtspr HID0, r3
    blr
}

/** Assembly: isyncs and clears the HID0 instruction-cache enable bit. */
asm void ICDisable(void) {
    nofralloc
    isync
    mfspr r3, HID0
    rlwinm r3, r3, 0, 17, 15
    mtspr HID0, r3
    blr
}

/** Assembly: sets the HID0 instruction-cache lock bit. */
asm void ICFreeze(void) {
    nofralloc
    isync
    mfspr r3, HID0
    ori r3, r3, 0x2000
    mtspr HID0, r3
    blr
}

/** Assembly: clears the HID0 instruction-cache lock bit. */
asm void ICUnfreeze(void) {
    nofralloc
    mfspr r3, HID0
    rlwinm r3, r3, 0, 19, 17
    mtspr HID0, r3
    blr
}

/** Assembly: icbi, invalidates the instruction cache line at addr. */
asm void ICBlockInvalidate(register void* addr) {
    nofralloc
    icbi r0, addr
    blr
}

/** Assembly: isync, so following instructions are refetched. */
asm void ICSync(void) {
    nofralloc
    isync
    blr
}

#define LC_LINES    512
#define CACHE_LINES 1024

/**
 * Assembly worker for LCEnable: flushes the data cache by touching 1024 lines,
 * sets the locked-cache enable bits in HID2, maps the locked cache with DBAT3 at the LC base address
 * and allocates its 512 lines with dcbz_l.
 */
static asm void __LCEnable(void) {
    nofralloc
    mfmsr   r5
    ori     r5, r5, 0x1000
    mtmsr   r5

    lis     r3, OS_CACHED_REGION_PREFIX
    li      r4, CACHE_LINES
    mtctr   r4
_touchloop:
    dcbt    0,r3
    dcbst   0,r3
    addi    r3,r3,32
    bdnz    _touchloop
    mfspr   r4, HID2
    oris    r4, r4, 0x100F
    mtspr   HID2, r4

    nop 
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    lis     r3, LC_BASE_PREFIX
    ori     r3, r3, 0x0002
    mtspr   DBAT3L, r3
    ori     r3, r3, 0x01fe
    mtspr   DBAT3U, r3
    isync
    lis     r3, LC_BASE_PREFIX
    li      r6, LC_LINES
    mtctr   r6
    li      r6, 0

_lockloop:
    dcbz_l  r6, r3
    addi    r3, r3, 32
    bdnz+    _lockloop

    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    blr
}

/** Enables the locked cache (the 16 KB of data cache usable as fast scratch memory) with interrupts off. */
void LCEnable(void) {
    BOOL enabled;

    enabled = OSDisableInterrupts();
    __LCEnable();
    OSRestoreInterrupts(enabled);
}

/** Assembly: invalidates the 512 locked-cache lines and clears the locked-cache enable bit in HID2. */
asm void LCDisable(void) {
    nofralloc
    lis     r3, LC_BASE_PREFIX
    li      r4, LC_LINES
    mtctr r4
@1
    dcbi r0, r3
    addi r3, r3, 32
    bdnz @1
    mfspr r4, HID2
    rlwinm r4, r4, 0, 4, 2
    mtspr HID2, r4
    blr
}

/**
 * Assembly: allocates one locked-cache line for the address tag,
 * optionally invalidating it first (dcbi then dcbz_l).
 */
asm void LCAllocOneTag(register BOOL invalidate, register void* tag) {
    nofralloc
    cmpwi invalidate, 0
    beq @1
    dcbi r0, tag
@1
    dcbz_l r0, tag
    blr
}

/**
 * Assembly: allocates numBlocks consecutive locked-cache lines starting at startTag,
 * optionally invalidating each first.
 */
asm void LCAllocTags(register BOOL invalidate, register void* startTag, register u32 numBlocks) {
    nofralloc
    mflr r6
    cmplwi numBlocks, 0
    ble @3
    mtctr numBlocks
    cmpwi invalidate, 0
    beq @2
@1
    dcbi r0, startTag
    dcbz_l r0, startTag
    addi startTag, startTag, 32
    bdnz @1
    b @3
@2
    dcbz_l r0, startTag
    addi startTag, startTag, 32
    bdnz @2
@3
    mtlr r6
    blr
}

/**
 * Assembly: starts a locked-cache DMA from main memory at srcAddr into the locked cache at destTag for numBlocks
 * 32-byte blocks (0 means 128), through the DMA_U/DMA_L registers.
 */
asm void LCLoadBlocks(register void* destTag, register void* srcAddr, register u32 numBlocks) {
    nofralloc
    rlwinm  r6, numBlocks, 30, 27, 31
    rlwinm  srcAddr, srcAddr, 0, 4, 31
    or      r6, r6, srcAddr
    mtspr   DMA_U, r6
    rlwinm  r6, numBlocks, 2, 28, 29
    or      r6, r6, destTag
    ori     r6, r6, 0x12
    mtspr   DMA_L, r6
    blr
}

/**
 * Assembly: starts a locked-cache DMA from the locked cache at srcTag out to main memory at destAddr,
 * for numBlocks 32-byte blocks (0 means 128).
 */
asm void LCStoreBlocks(register void* destAddr, register void* srcTag, register u32 numBlocks) {
    nofralloc
    rlwinm  r6, numBlocks, 30, 27, 31
    rlwinm  destAddr, destAddr, 0, 4, 31
    or      r6, r6, destAddr
    mtspr   DMA_U, r6
    rlwinm  r6, numBlocks, 2, 28, 29
    or      r6, r6, srcTag
    ori     r6, r6, 0x2
    mtspr   DMA_L, r6
    blr
}
#endif

/**
 * Allocates locked-cache lines for nBytes at addr, enabling the locked cache first if it is off,
 * invalidating the lines.
 */
void LCAlloc(void* addr, u32 nBytes) {
    u32 numBlocks = nBytes >> 5;
    u32 hid2 = PPCMfhid2();

    ASSERTMSGLINE(1319, !((u32)addr & 31), "LCAlloc(): addr must be 32 byte aligned");
    ASSERTMSGLINE(1321, !((u32)nBytes & 31), "LCAlloc(): nBytes must be 32 byte aligned");

    if ((hid2 & 0x10000000) == 0) {
        LCEnable();
    }
    LCAllocTags(TRUE, addr, numBlocks);
}

/** Same as LCAlloc but without invalidating the lines first. */
void LCAllocNoInvalidate(void* addr, u32 nBytes) {
    u32 numBlocks = nBytes >> 5;
    u32 hid2 = PPCMfhid2();

    ASSERTMSGLINE(1366, !((u32)addr & 31), "LCAllocNoFlush(): addr must be 32 byte aligned");
    ASSERTMSGLINE(1368, !((u32)nBytes & 31), "LCAllocNoFlush(): nBytes must be 32 byte aligned");

    if ((hid2 & 0x10000000) == 0) {
        LCEnable();
    }
    LCAllocTags(FALSE, addr, numBlocks);
}

/**
 * Loads nBytes from main memory into the locked cache,
 * split into DMA commands of at most 128 blocks (4096 bytes); returns the number of commands issued.
 */
u32 LCLoadData(void* destAddr, void* srcAddr, u32 nBytes) {
    u32 numBlocks = (nBytes + 31) / 32;
    u32 numTransactions = (numBlocks + 128 - 1) / 128;

    ASSERTMSGLINE(1426, !((u32)srcAddr & 31), "LCLoadData(): srcAddr not 32 byte aligned");
    ASSERTMSGLINE(1428, !((u32)destAddr & 31), "LCLoadData(): destAddr not 32 byte aligned");

    while (numBlocks > 0) {
        if (numBlocks < 128) {
            LCLoadBlocks(destAddr, srcAddr, numBlocks);
            numBlocks = 0;
        } else {
            LCLoadBlocks(destAddr, srcAddr, 0);
            numBlocks -= 128;
            destAddr = (void*)((u32)destAddr + 4096);
            srcAddr = (void*)((u32)srcAddr + 4096);
        }
    }

    return numTransactions;
}

/**
 * Stores nBytes from the locked cache to main memory, split into DMA commands of at most 128 blocks;
 * returns the number of commands issued.
 */
u32 LCStoreData(void* destAddr, void* srcAddr, u32 nBytes) {
    u32 numBlocks = (nBytes + 31) / 32;
    u32 numTransactions = (numBlocks + 128 - 1) / 128;

    ASSERTMSGLINE(1494, !((u32)srcAddr & 31), "LCStoreData(): srcAddr not 32 byte aligned");
    ASSERTMSGLINE(1496, !((u32)destAddr & 31), "LCStoreData(): destAddr not 32 byte aligned");

    while (numBlocks > 0) {
        if (numBlocks < 128) {
            LCStoreBlocks(destAddr, srcAddr, numBlocks);
            numBlocks = 0;
        } else {
            LCStoreBlocks(destAddr, srcAddr, 0);
            numBlocks -= 128;
            destAddr = (void*)((u32)destAddr + 4096);
            srcAddr = (void*)((u32)srcAddr + 4096);
        }
    }

    return numTransactions;
}

/** Assembly: returns the number of DMA commands still queued, read from HID2. */
#ifdef __GEKKO__
asm u32 LCQueueLength(void) {
    nofralloc
    mfspr   r4, HID2
    rlwinm  r3, r4, 8, 28, 31
    blr
}

/** Assembly: busy-waits until the locked-cache DMA queue holds no more than len commands. */
asm void LCQueueWait(register u32 len) {
    nofralloc
@1
    mfspr r4, HID2
    rlwinm r4, r4, 8, 28, 31
    cmpw r4, r3
    bgt @1
    blr
}
#endif

/** Pushes queued locked-cache DMA commands out by writing the flush bit to the DMA control registers, then syncs. */
void LCFlushQueue() {
    union {
        u32 val;
        struct {
            u32 lcAddr : 27;
            u32 dmaLd : 1;
            u32 dmaLenL : 2;
            u32 dmaTrigger : 1;
            u32 dmaFlush : 1;
        } f;
    } dmaL;

    dmaL.val = 0;
    dmaL.f.dmaFlush = 1;
    PPCMtdmaU(0);
    PPCMtdmaL(dmaL.val);
    PPCSync();
}

/**
 * Disables and globally invalidates the L2 cache with address translation temporarily on;
 * the setup step before L2Enable.
 */
static void L2Init(void) {
    u32 oldMSR;
    oldMSR = PPCMfmsr();
    __sync();
    PPCMtmsr(MSR_IR | MSR_DR);
    __sync();
    L2Disable();
    L2GlobalInvalidate();
    PPCMtmsr(oldMSR);
}

/** Turns the L2 cache on (L2E set, global-invalidate bit clear). */
void L2Enable(void) { 
    PPCMtl2cr((PPCMfl2cr() | L2CR_L2E) & ~L2CR_L2I);
}

/** Turns the L2 cache off, with syncs around the write. */
void L2Disable(void) {
    __sync();
    PPCMtl2cr(PPCMfl2cr() & ~0x80000000);
    __sync();
}

/** Disables the L2 cache and invalidates all of it, waiting for the hardware to finish. */
void L2GlobalInvalidate(void) {
    L2Disable();
    PPCMtl2cr(PPCMfl2cr() | 0x00200000);
    while (PPCMfl2cr() & 0x00000001u);

    PPCMtl2cr(PPCMfl2cr() & ~0x00200000);
    while (PPCMfl2cr() & 0x00000001u) {
        DBPrintf(">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n");
    }
}

/** Sets or clears the L2 data-only mode, in which the L2 cache holds data but not instructions. */
void L2SetDataOnly(BOOL dataOnly) {
    if (dataOnly) {
        PPCMtl2cr(PPCMfl2cr() | 0x400000);
        return;
    }
    PPCMtl2cr(PPCMfl2cr() & 0xFFBFFFFF);
}

/** Sets or clears L2 write-through mode (otherwise write-back). */
void L2SetWriteThrough(BOOL writeThrough) {
    if (writeThrough) {
        PPCMtl2cr(PPCMfl2cr() | 0x80000);
        return;
    }
    PPCMtl2cr(PPCMfl2cr() & 0xFFF7FFFF);
}

/**
 * Machine-check handler.
 * If the check was not a locked-cache DMA error it dumps the context and halts;
 * otherwise it reports which DMA errors occurred (duplicate tag, normal cache access, miss, queue overflow)
 * and clears them so execution continues.
 */
void DMAErrorHandler(OSError error, OSContext* context, ...) {
    u32 hid2 = PPCMfhid2();

    OSReport("Machine check received\n");
    OSReport("HID2 = 0x%x   SRR1 = 0x%x\n", hid2, context->srr1);
    if (!(hid2 & (HID2_DCHERR | HID2_DNCERR | HID2_DCMERR | HID2_DQOERR)) || !(context->srr1 & SRR1_DMA_BIT)) {
        OSReport("Machine check was not DMA/locked cache related\n");
        OSDumpContext(context);
        PPCHalt();
    }

    OSReport("DMAErrorHandler(): An error occurred while processing DMA.\n");
    OSReport("The following errors have been detected and cleared :\n");

    if (hid2 & HID2_DCHERR) {
        OSReport("\t- Requested a locked cache tag that was already in the cache\n");
    }

    if (hid2 & HID2_DNCERR) {
        OSReport("\t- DMA attempted to access normal cache\n");
    }

    if (hid2 & HID2_DCMERR) {
        OSReport("\t- DMA missed in data cache\n");
    }

    if (hid2 & HID2_DQOERR) {
        OSReport("\t- DMA queue overflowed\n");
    }

    // write hid2 back to clear the error bits
    PPCMthid2(hid2);
}

/**
 * Enables the L1 instruction and data caches and the L2 cache if they are off,
 * and installs DMAErrorHandler as the machine-check handler. Called from OSInit.
 */
void __OSCacheInit() {
    if (!(PPCMfhid0() & HID0_ICE)) {
        ICEnable();
        DBPrintf("L1 i-caches initialized\n");
    }

    if (!(PPCMfhid0() & HID0_DCE)) {
        DCEnable();
        DBPrintf("L1 d-caches initialized\n");
    }

    if (!(PPCMfl2cr() & L2CR_L2E)) {
        L2Init();
        L2Enable();
        DBPrintf("L2 cache initialized\n");
    }

    OSSetErrorHandler(OS_ERROR_MACHINE_CHECK, DMAErrorHandler);
    DBPrintf("Locked cache machine check handler installed\n");
}
