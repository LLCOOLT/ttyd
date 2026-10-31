#include <stddef.h>
#include <dolphin/base/PPCArch.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "__gx.h"

static GXDrawSyncCallback TokenCB;
static GXDrawDoneCallback DrawDoneCB;
static u8 DrawDone;
static OSThreadQueue FinishQueue;

/**
 * Sets a miscellaneous GX option by token: the XF flush vertex count (GX_MT_XF_FLUSH),
 * whether display lists save and restore the context (GX_MT_DL_SAVE_CONTEXT),
 * and the abort-wait-for-copy setting.
 */
void GXSetMisc(GXMiscToken token, u32 val) {
    switch (token) {
    case GX_MT_XF_FLUSH:
        __GXData->vNum = val;
        __GXData->vNumNot = !__GXData->vNum;
        __GXData->bpSentNot = 1;

        if (__GXData->vNum != 0) {
            __GXData->dirtyState |= 8;
        }
        break;
    case GX_MT_DL_SAVE_CONTEXT:
        ASSERTMSGLINE(223, !__GXData->inDispList, "GXSetMisc: Cannot change DL context setting while making a display list");
        __GXData->dlSaveContext = (val != 0);
        break;
    case GX_MT_ABORT_WAIT_COPYOUT:
        __GXData->abtWaitPECopy = (val != 0);
        break;
    case GX_MT_NULL:
        break;
    default:
#if DEBUG
        OSReport("GXSetMisc: bad token %d (val %d)\n", token, val);
#endif
        break;
    }
}

/**
 * Flushes pending dirty state, then writes eight zero words (32 bytes) to the FIFO and syncs
 * so the CPU's write-gather buffer is pushed out to the GPU.
 */
void GXFlush(void) {
    CHECK_GXBEGIN(270, "GXFlush");
    if (__GXData->dirtyState) {
        __GXSetDirtyState();
    }
    
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);
    GX_WRITE_U32(0);

    PPCSync();
}

/**
 * Waits until the write-gather pipe reports empty, then reloads WPAR with the FIFO address,
 * which discards the gather position.
 */
void GXResetWriteGatherPipe(void) {
    while (PPCMfwpar() & 1) {
    }
    PPCMtwpar(OSUncachedToPhysical((void *)GXFIFO_ADDR));
}

/** Busy-waits until the time base has advanced by clocks / 4 ticks. */
static void __GXAbortWait(u32 clocks) {
    OSTime time0;
    OSTime time1;

    time0 = OSGetTime();
    do {
        time1 = OSGetTime();
    } while (time1 - time0 <= (clocks / 4));
}

/**
 * Polls the memory-controller pixel-engine counter every 32 clocks until it stops changing,
 * i.e. the EFB copy in flight has finished.
 */
static void __GXAbortWaitPECopyDone(void) {
    u32 peCnt0;
    u32 peCnt1;

    peCnt0 = __GXReadMEMCounterU32(0x28, 0x27);
    do {
        peCnt1 = peCnt0;
        __GXAbortWait(32);

        peCnt0 = __GXReadMEMCounterU32(0x28, 0x27);
    } while (peCnt0 != peCnt1);
}

/**
 * Resets the graphics pipeline: optionally waits for a pending EFB copy,
 * then sets the reset bit in PI register 0x18 for 200 clocks, clears it and waits 20 more.
 */
void __GXAbort(void) {
    if (__GXData->abtWaitPECopy && GXGetGPFifo() != (GXFifoObj*)NULL) {
        __GXAbortWaitPECopyDone();
    }

    __PIRegs[0x18 / 4] = 1;
    __GXAbortWait(200);
    __PIRegs[0x18 / 4] = 0;
    __GXAbortWait(20);
}

/**
 * Abandons the frame in progress: resets the GPU with __GXAbort, and if a GP FIFO exists cleans it,
 * re-applies the revision bits, clears the dirty state and flushes.
 */
void GXAbortFrame(void) {
    __GXAbort();

    if (GXGetGPFifo() != (GXFifoObj*)NULL) {
        __GXCleanGPFifo();
        __GXInitRevisionBits();
        __GXData->dirtyState = 0;
        GXFlush();
    }
}

/**
 * With interrupts off, writes a 16-bit token to the pixel engine through two BP registers (0x48 and 0x47)
 * and flushes; when the GPU gets there the token register changes
 * and the token interrupt calls the draw-sync callback.
 */
void GXSetDrawSync(u16 token) {
    BOOL enabled;
    u32 reg;

    CHECK_GXBEGIN(430, "GXSetDrawSync");

    enabled = OSDisableInterrupts();
    reg = token | 0x48000000;
    GX_WRITE_RAS_REG(reg);
    SET_REG_FIELD(443, reg, 16, 0, token);
    SET_REG_FIELD(443, reg, 8, 24, 0x47);
    GX_WRITE_RAS_REG(reg);
    GXFlush();
    OSRestoreInterrupts(enabled);
    __GXData->bpSentNot = 0;
}

/** Returns the last token the GPU has processed (pixel-engine register 7). */
u16 GXReadDrawSync(void) {
    u16 token = GX_GET_PE_REG(7);
    return token;
}

/**
 * With interrupts off, clears the draw-done flag, writes the finish command (BP 0x45000002) and flushes;
 * the GPU raises the finish interrupt when it has drained everything before it.
 */
void GXSetDrawDone(void) {
    u32 reg;
    BOOL enabled;

    CHECK_GXBEGIN(488, "GXSetDrawDone");
    enabled = OSDisableInterrupts();
    reg = 0x45000002;
    GX_WRITE_RAS_REG(reg);
    GXFlush();
    DrawDone = 0;
    OSRestoreInterrupts(enabled);
}

/** Sleeps the calling thread on a queue until the finish interrupt handler sets the draw-done flag. */
void GXWaitDrawDone(void) {
    BOOL enabled;

    CHECK_GXBEGIN(534, "GXWaitDrawDone");

    enabled = OSDisableInterrupts();
    while (!DrawDone) {
        OSSleepThread(&FinishQueue);
    }
    OSRestoreInterrupts(enabled);
}

/** Waits for the GPU to finish all queued drawing (GXSetDrawDone then GXWaitDrawDone). */
void GXDrawDone(void) {
    CHECK_GXBEGIN(566, "GXDrawDone");
    GXSetDrawDone();
    GXWaitDrawDone();
}

/**
 * Rewrites the cached pixel-engine control register (BP 0x43),
 * which makes the pixel engine wait for earlier draws before applying the mode.
 */
void GXPixModeSync(void) {
    CHECK_GXBEGIN(601, "GXPixModeSync");
    GX_WRITE_RAS_REG(__GXData->peCtrl);
    __GXData->bpSentNot = 0;
}

/** Writes BP 0x63000000, which makes the texture unit wait for earlier draws before texture state changes. */
void GXTexModeSync(void) {
    u32 reg;

    CHECK_GXBEGIN(625, "GXTexModeSync");
    reg = 0x63000000;
    GX_WRITE_RAS_REG(reg);
    __GXData->bpSentNot = 0;
}

#if DEBUG
/** Debug builds only: writes an arbitrary BP register word to the FIFO. */
void __GXBypass(u32 reg) {
    CHECK_GXBEGIN(647, "__GXBypass");
    GX_WRITE_RAS_REG(reg);
    __GXData->bpSentNot = 0;
}

/** Debug builds only: reads a 16-bit pixel-engine register. */
u16 __GXReadPEReg(u32 reg) {
    return GX_GET_PE_REG(reg);
}
#endif

/** Writes the alpha compare function and threshold used for CPU pokes to the EFB into pixel-engine register 3. */
void GXPokeAlphaMode(GXCompare func, u8 threshold) {
    u32 reg;

    reg = (func << 8) | threshold;
    GX_SET_PE_REG(3, reg);
}

/** Sets how alpha is read back from the EFB for pokes (pixel-engine register 4). */
void GXPokeAlphaRead(GXAlphaReadMode mode) {
    u32 reg;

    reg = 0;
    SET_REG_FIELD(693, reg, 2, 0, mode);
    SET_REG_FIELD(693, reg, 1, 2, 1);
    GX_SET_PE_REG(4, reg);
}

/** Enables or disables alpha writes (bit 4 of pixel-engine register 1) for CPU pokes. */
void GXPokeAlphaUpdate(GXBool update_enable) {
    u32 reg;

    reg = GX_GET_PE_REG(1);
    SET_REG_FIELD(704, reg, 1, 4, update_enable);
    GX_SET_PE_REG(1, reg);
}

/**
 * Sets the blend mode (blend or subtract enable, logic op enable,
 * factors and logic op) used for CPU pokes in pixel- engine register 1.
 */
void GXPokeBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op) {
    u32 reg;

    reg = GX_GET_PE_REG(1);
    SET_REG_FIELD(720, reg, 1, 0, (type == GX_BM_BLEND) || (type == GX_BM_SUBTRACT));
    SET_REG_FIELD(721, reg, 1, 11, (type == GX_BM_SUBTRACT));
    SET_REG_FIELD(723, reg, 1, 1, (type == GX_BM_LOGIC));
    SET_REG_FIELD(724, reg, 4, 12, op);
    SET_REG_FIELD(725, reg, 3, 8, src_factor);
    SET_REG_FIELD(726, reg, 3, 5, dst_factor);
    SET_REG_FIELD(726, reg, 8, 24, 0x41);
    GX_SET_PE_REG(1, reg);
}

/** Enables or disables colour writes (bit 3 of pixel-engine register 1) for CPU pokes. */
void GXPokeColorUpdate(GXBool update_enable) {
    u32 reg;

    reg = GX_GET_PE_REG(1);
    SET_REG_FIELD(738, reg, 1, 3, update_enable);
    GX_SET_PE_REG(1, reg);
}

/** Sets whether a constant alpha is written for CPU pokes, and its value (pixel-engine register 2). */
void GXPokeDstAlpha(GXBool enable, u8 alpha) {
    u32 reg = 0;

    SET_REG_FIELD(747, reg, 8, 0, alpha);
    SET_REG_FIELD(748, reg, 1, 8, enable);
    GX_SET_PE_REG(2, reg);
}

/** Enables or disables dithering (bit 2 of pixel-engine register 1) for CPU pokes. */
void GXPokeDither(GXBool dither) {
    u32 reg;

    reg = GX_GET_PE_REG(1);
    SET_REG_FIELD(758, reg, 1, 2, dither);
    GX_SET_PE_REG(1, reg);
}

/** Sets the Z compare enable, function and update flag used for CPU pokes (pixel-engine register 0). */
void GXPokeZMode(GXBool compare_enable, GXCompare func, GXBool update_enable) {
    u32 reg = 0;

    SET_REG_FIELD(767, reg, 1, 0, compare_enable);
    SET_REG_FIELD(768, reg, 3, 1, func);
    SET_REG_FIELD(769, reg, 1, 4, update_enable);
    GX_SET_PE_REG(0, reg);
}

/**
 * Reads one EFB pixel as ARGB: the CPU loads from the EFB window at physical 0x08000000 with x in bits 2-11
 * and y in bits 12-21 of the address.
 */
void GXPeekARGB(u16 x, u16 y, u32* color) {
    u32 addr = (u32)OSPhysicalToUncached(0x08000000);

    SET_REG_FIELD(792, addr, 10, 2, x);
    SET_REG_FIELD(793, addr, 10, 12, y);
    SET_REG_FIELD(793, addr, 2, 22, 0);
    *color = *(u32*)addr;
}

/**
 * Writes one EFB pixel as ARGB through the EFB window at physical 0x08000000 (x in bits 2-11, y in bits 12-21 of
 * the address).
 */
void GXPokeARGB(u16 x, u16 y, u32 color) {
    u32 addr = (u32)OSPhysicalToUncached(0x08000000);

    SET_REG_FIELD(0x322, addr, 10, 2, x);
    SET_REG_FIELD(0x323, addr, 10, 12, y);
    SET_REG_FIELD(0x323, addr, 2, 22, 0);
    *(u32*)addr = color;
}

/**
 * Reads one EFB pixel's Z value through the EFB window (the same window,
 * with the Z select bits set in the address).
 */
void GXPeekZ(u16 x, u16 y, u32* z) {
    u32 addr = (u32)OSPhysicalToUncached(0x08000000);

    SET_REG_FIELD(812, addr, 10, 2, x);
    SET_REG_FIELD(813, addr, 10, 12, y);
    SET_REG_FIELD(813, addr, 2, 22, 1);
    *z = *(u32*)addr;
}

/**
 * Writes one EFB pixel's Z value through the EFB window (the same window,
 * with the Z select bits set in the address).
 */
void GXPokeZ(u16 x, u16 y, u32 z) {
    u32 addr = (u32)OSPhysicalToUncached(0x08000000);

    SET_REG_FIELD(822, addr, 10, 2, x);
    SET_REG_FIELD(823, addr, 10, 12, y);
    SET_REG_FIELD(823, addr, 2, 22, 1);
    *(u32*)addr = z;
}

/**
 * Installs the callback run from the token interrupt with each token the GPU reaches;
 * interrupts are off while swapping. Returns the previous callback.
 */
GXDrawSyncCallback GXSetDrawSyncCallback(GXDrawSyncCallback cb) {
    GXDrawSyncCallback oldcb;
    BOOL enabled;

    oldcb = TokenCB;
    enabled = OSDisableInterrupts();
    TokenCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}

/**
 * Interrupt handler (OS interrupt 0x12) for the pixel-engine token:
 * reads the token, calls TokenCB with it inside a scratch OS context,
 * then acknowledges the interrupt in pixel-engine register 5.
 */
static void GXTokenInterruptHandler(__OSInterrupt interrupt, OSContext* context) {
    u16 token;
    OSContext exceptionContext;
    u32 reg;

    token = GX_GET_PE_REG(7);
    if (TokenCB != NULL) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        TokenCB(token);
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
    reg = GX_GET_PE_REG(5);
    SET_REG_FIELD(0, reg, 1, 2, 1);
    GX_SET_PE_REG(5, reg);
}

/**
 * Installs the callback run when the finish interrupt fires; interrupts are off while swapping.
 * Returns the previous callback.
 */
GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback cb) {
    GXDrawDoneCallback oldcb;
    BOOL enabled;

    oldcb = DrawDoneCB;
    enabled = OSDisableInterrupts();
    DrawDoneCB = cb;
    OSRestoreInterrupts(enabled);
    return oldcb;
}

/**
 * Interrupt handler (OS interrupt 0x13) for the pixel-engine finish:
 * acknowledges it, sets the draw-done flag, calls the draw-done callback in a scratch OS context
 * and wakes threads sleeping in GXWaitDrawDone.
 */
static void GXFinishInterruptHandler(__OSInterrupt interrupt, OSContext* context) {
    OSContext exceptionContext;
    u32 reg;

    reg = GX_GET_PE_REG(5);
    SET_REG_FIELD(0, reg, 1, 3, 1);
    GX_SET_PE_REG(5, reg);
    DrawDone = 1;
    if (DrawDoneCB != NULL) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        DrawDoneCB();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
    OSWakeupThread(&FinishQueue);
}

/**
 * Installs the token and finish interrupt handlers (OS interrupts 0x12 and 0x13),
 * initialises the finish thread queue, unmasks both interrupts and enables them in pixel-engine register 5.
 */
void __GXPEInit(void) {
    u32 reg;
    __OSSetInterruptHandler(0x12, GXTokenInterruptHandler);
    __OSSetInterruptHandler(0x13, GXFinishInterruptHandler);
    OSInitThreadQueue(&FinishQueue);
    __OSUnmaskInterrupts(0x2000);
    __OSUnmaskInterrupts(0x1000);
    reg = GX_GET_PE_REG(5);
    SET_REG_FIELD(0, reg, 1, 2, 1);
    SET_REG_FIELD(0, reg, 1, 3, 1);
    SET_REG_FIELD(0, reg, 1, 0, 1);
    SET_REG_FIELD(0, reg, 1, 1, 1);
    GX_SET_PE_REG(5, reg);
}

/**
 * Converts a 24-bit Z to the 16-bit copy format: GX_ZC_LINEAR keeps the top 16 bits;
 * NEAR, MID and FAR use a 2-, 3- or 4-bit exponent (the count of leading ones of z24, capped) in the top bits
 * and the next mantissa bits below.
 */
u32 GXCompressZ16(u32 z24, GXZFmt16 zfmt) {
    u32 z16;
    u32 z24n;
    s32 exp;
    s32 shift;
#if DEBUG
#define temp exp
#else
    s32 temp;
    u8 unused[4];
#endif

    z24n = ~(z24 << 8);
    temp = __cntlzw(z24n);
    switch (zfmt) {
    case GX_ZC_LINEAR:
        z16 = (z24 >> 8) & 0xFFFF;
        break;
    case GX_ZC_NEAR:
        if (temp > 3) {
            exp = 3;
        } else {
            exp = temp;
        }
        if (exp == 3) {
            shift = 7;
        } else {
            shift = 9 - exp;
        }
        z16 = ((z24 >> shift) & 0x3FFF & ~0xFFFFC000) | (exp << 14);
        break;
    case GX_ZC_MID:
        if (temp > 7) {
            exp = 7;
        } else {
            exp = temp;
        }
        if (exp == 7) {
            shift = 4;
        } else {
            shift = 10 - exp;
        }
        z16 = ((z24 >> shift) & 0x1FFF & ~0xFFFFE000) | (exp << 13);
        break;
    case GX_ZC_FAR:
        if (temp > 12) {
            exp = 12;
        } else {
            exp = temp;
        }
        if (exp == 12) {
            shift = 0;
        } else {
            shift = 11 - exp;
        }
        z16 = ((z24 >> shift) & 0xFFF & ~0xFFFFF000) | (exp << 12);
        break;
    default:
        OSPanic(__FILE__, 1004, "GXCompressZ16: Invalid Z format\n");
        break;
    }
    return z16;
}

/**
 * Expands a 16-bit Z of the given format back to 24 bits,
 * the inverse of GXCompressZ16 (the dropped low bits come back as zero).
 */
u32 GXDecompressZ16(u32 z16, GXZFmt16 zfmt) {
    u32 z24;
    u32 cb1;
    s32 exp;
    s32 shift;

    cb1; cb1; cb1; z16; z16; z16;  // needed to match

    switch (zfmt) {
    case GX_ZC_LINEAR:
        z24 = (z16 << 8) & 0xFFFF00;
        break;
    case GX_ZC_NEAR:
        exp = (z16 >> 14) & 3;
        if (exp == 3) {
            shift = 7;
        } else {
            shift = 9 - exp;
        }
        cb1 = -1 << (24 - exp);
        z24 = (cb1 | ((z16 & 0x3FFF) << shift)) & 0xFFFFFF;
        break;
    case GX_ZC_MID:
        exp = (z16 >> 13) & 7;
        if (exp == 7) {
            shift = 4;
        } else {
            shift = 10 - exp;
        }
        cb1 = -1 << (24 - exp);
        z24 = (cb1 | ((z16 & 0x1FFF) << shift)) & 0xFFFFFF;
        break;
    case GX_ZC_FAR:
        exp = (z16 >> 12) & 0xF;
        if (exp == 12) {
            shift = 0;
        } else {
            shift = 11 - exp;
        }
        cb1 = -1 << (24 - exp);
        z24 = (cb1 | ((z16 & 0xFFF) << shift)) & 0xFFFFFF;
        break;
    default:
        OSPanic(__FILE__, 1054, "GXDecompressZ16: Invalid Z format\n");
        break;
    }
    return z24;
}
