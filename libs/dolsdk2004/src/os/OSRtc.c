#include <dolphin/exi.h>
#include <dolphin/os.h>

#include "__os.h"

static SramControl Scb ATTRIBUTE_ALIGN(DOLPHIN_ALIGNMENT);

// prototypes
static int GetRTC(u32* rtc);
static int ReadSram(void* buffer);
static void WriteSramCallback(s32, OSContext*);
static int WriteSram(void* buffer, u32 offset, u32 size);
static void* LockSram(u32 offset);
static int UnlockSram(int commit, u32 offset);
static void __OSReadROMCallback(s32 chan);

/**
 * One attempt to read the 32-bit real-time-clock counter from the RTC chip (EXI channel 0, device 1, command
 * 0x20000000); returns nonzero on success.
 */
static int GetRTC(u32* rtc) {
    int err;
    u32 cmd;

    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = 0x20000000;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIImm(0, &cmd, 4, 0, 0);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    rtc[0] = cmd;
    return !err;
}

/**
 * Reads the RTC counter twice in a row, up to 16 times, until both reads agree,
 * so a tick in the middle of a read is not returned. Returns nonzero on success.
 */
int __OSGetRTC(u32* rtc) {
    int err;
    u32 t0;
    u32 t1;
    int i;

    for(i = 0; i < 16; i++) {
        err = 0;
        err |= !GetRTC(&t0);
        err |= !GetRTC(&t1);
        if (err) {
            break;
        }
        if (t0 == t1) {
            rtc[0] = t0;
            return 1;
        }
    }
    return 0;
}

/**
 * Writes a new 32-bit counter value to the RTC chip over EXI (command 0xA0000000);
 * used when the console time is changed.
 */
int __OSSetRTC(u32 rtc) {
    int err;
    u32 cmd;

    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = 0xA0000000;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIImm(0, &rtc, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

/**
 * Reads the SRAM block (SRAM_SIZE bytes, command 0x20000100) from the RTC chip over EXI channel 0 by DMA into
 * buffer; returns nonzero on success.
 */
static int ReadSram(void* buffer) {
    int err;
    u32 cmd;

    DCInvalidateRange(buffer, SRAM_SIZE);
    if (!EXILock(0, 1, NULL) ) {
        return 0;
    }
    if (!EXISelect(0, 1, 3)) {
        EXIUnlock(0);
        return 0;
    }
    cmd = 0x20000100;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, SRAM_SIZE, 0, NULL);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

/**
 * EXI unlock callback that retries the pending SRAM write (from Scb.offset to the end of the block)
 * after the EXI channel became free.
 */
static void WriteSramCallback(s32, OSContext*) {
    ASSERTLINE(258, !Scb.locked);
    Scb.sync = WriteSram(&Scb.sram[Scb.offset], Scb.offset, SRAM_SIZE - Scb.offset);
    if (Scb.sync != 0) {
        Scb.offset = SRAM_SIZE;
    }
    ASSERTLINE(264, Scb.sync);
}

/**
 * Writes size bytes of the SRAM image to the RTC chip at offset over EXI channel 0 (device 1).
 * If the channel is busy, WriteSramCallback retries it later.
 */
static int WriteSram(void* buffer, u32 offset, u32 size) {
    int err;
    u32 cmd;

    if (!EXILock(0, 1, WriteSramCallback)) {
        return 0;
    }
    if (!EXISelect(0, 1, 3)) {
        EXIUnlock(0);
        return 0;
    }
    offset <<= 6;
    cmd = ((offset + 0x100) | 0xA0000000);
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIImmEx(0, buffer, size, 1);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

/**
 * Reads the SRAM block into the OS's cached copy at start-up,
 * then re-sets the GBS mode so invalid values are cleared.
 */
void __OSInitSram(void) {
    Scb.locked = Scb.enabled = FALSE;
    Scb.sync = ReadSram(&Scb);
    ASSERTLINE(318, Scb.sync);
    Scb.offset = SRAM_SIZE;

    OSSetGbsMode(OSGetGbsMode());
}

/**
 * Disables interrupts and takes the lock on the cached SRAM image,
 * returning a pointer offset bytes into it (NULL if already locked); pair with UnlockSram.
 */
static void* LockSram(u32 offset) {
    BOOL enabled;

    enabled = OSDisableInterrupts();
    ASSERTLINE(341, !Scb.locked);
    if (Scb.locked) {
        OSRestoreInterrupts(enabled);
        return NULL;
    }
    Scb.enabled = enabled;
    Scb.locked = TRUE;
    return &Scb.sram[offset];
}

/** Locks the SRAM cache and returns it as the standard OSSram layout (flags, language, display offset and so on). */
OSSram* __OSLockSram(void) {
    return (OSSram*)LockSram(0);
}

/**
 * Locks the SRAM cache and returns the extended OSSramEx part that follows the standard OSSram (GBS mode,
 * wireless pad IDs).
 */
OSSramEx* __OSLockSramEx(void) {
    return (OSSramEx*)LockSram(sizeof(OSSram));
}

/**
 * Releases the SRAM lock.
 * With commit set it fixes the flags and recomputes the checksums of the standard block (if offset is 0),
 * clears an invalid GBS mode, starts writing the changed bytes back to the RTC chip,
 * and restores the interrupt state saved by the lock.
 */
static int UnlockSram(int commit, u32 offset) {
    u16* p;

    ASSERTLINE(375, Scb.locked);
    if (commit != 0) {
        if (offset == 0) {
            OSSram* sram  = (OSSram*)Scb.sram;
            if (2u < (sram->flags & 3)) {
                sram->flags &= ~3;
            }

            sram->checkSum = sram->checkSumInv = 0;
            for(p = (u16*)&sram->counterBias; p < ((u16*)&Scb.sram[0x14]); p++) {
                sram->checkSum += *p;
                sram->checkSumInv += ~(*p);
            }
        }
        if (offset < Scb.offset) {
            Scb.offset = offset;
        }

        if (Scb.offset <= 0x14) {
            OSSramEx* sram = (OSSramEx*)(Scb.sram + sizeof(OSSram));
            if (((u32)sram->gbs & 0x7c00) == 0x5000 || ((u32)sram->gbs & 0xc0) == 0xc0) {
                sram->gbs = 0;
            }
        }

        Scb.sync = WriteSram(&Scb.sram[Scb.offset], Scb.offset, SRAM_SIZE - Scb.offset);
        if (Scb.sync != 0) {
            Scb.offset = SRAM_SIZE;
        }
    }
    Scb.locked = FALSE;
    OSRestoreInterrupts(Scb.enabled);
    return Scb.sync;
}

/** Unlocks the standard SRAM block, optionally committing the changes to the chip. */
int __OSUnlockSram(int commit) {
    return UnlockSram(commit, 0);
}

/** Unlocks the extended SRAM block, optionally committing the changes to the chip. */
int __OSUnlockSramEx(int commit) {
    return UnlockSram(commit, sizeof(OSSram));
}

/** Returns the result of the last SRAM write (nonzero when it was accepted). */
int __OSSyncSram(void) {
    return Scb.sync;
}

/**
 * Recomputes the checksum and inverse checksum over the standard SRAM block and returns nonzero
 * when they match the stored values. SRAM must be locked.
 */
int __OSCheckSram(void) {
    u16* p;
    u16 checkSum;
    u16 checkSumInv;
    OSSram* sram;
    int unused;

    ASSERTLINE(466, Scb.locked);

    checkSum = checkSumInv = 0;

    sram = (OSSram*)Scb.sram;

    for (p = (void*)&sram->counterBias; p < (u16*)&Scb.sram[0x14]; p++) {
        checkSum += *p;
        checkSumInv += ~(*p);
    }

    return (sram->checkSum == checkSum && sram->checkSumInv == checkSumInv);
}

/**
 * Reads length bytes (at most 1024) from the console's boot ROM at offset over EXI channel 0 (device 1) by DMA,
 * blocking until done.
 */
int __OSReadROM(void * buffer, s32 length, s32 offset) {
    int err;
    u32 cmd;

    ASSERTLINE(497, length <= 1024);
    DCInvalidateRange(buffer, length);
    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = offset << 6;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, length, 0, NULL);
    err |= !EXISync(0);
    err |= !EXIDeselect(0);
    EXIUnlock(0);
    return !err;
}

/** EXI DMA completion callback: releases the EXI channel and calls the callback saved by __OSReadROMAsync. */
static void __OSReadROMCallback(s32 chan) {
    void (*callback)();

    EXIDeselect(chan);
    EXIUnlock(chan);
    callback = Scb.callback;
    if (callback) {
        Scb.callback = NULL;
        callback();
    }
}

/** Starts a non-blocking boot-ROM read of at most 1024 bytes over EXI; callback runs when the DMA finishes. */
int __OSReadROMAsync(void* buffer, s32 length, s32 offset, void (*callback)()) {
    int err;
    u32 cmd;

    ASSERTLINE(556, length <= 1024);
    ASSERTLINE(557, callback);
    DCInvalidateRange(buffer, length);
    Scb.callback = callback;
    if (EXILock(0, 1, NULL) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 3) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = offset << 6;
    err = 0;
    err |= !EXIImm(0, &cmd, 4, 1, 0);
    err |= !EXISync(0);
    err |= !EXIDma(0, buffer, length, 0, (void*)__OSReadROMCallback);
    return !err;
}

/** Returns the console's sound setting from SRAM flags bit 2: 0 for mono, 1 for stereo. */
u32 OSGetSoundMode(void) {
    OSSram* sram = __OSLockSram();
    u32 mode = (sram->flags & 4) ? 1 : 0;

    __OSUnlockSram(0);
    return mode;
}

/** Stores the sound setting (0 mono, 1 stereo) in SRAM flags bit 2, writing back only when it changed. */
void OSSetSoundMode(u32 mode) {
    OSSram* sram;
    int unused;

    ASSERTLINE(617, mode == OS_SOUND_MODE_MONO || mode == OS_SOUND_MODE_STEREO);
    mode *= 4;
    mode &= 4;
    sram = __OSLockSram();
    if (mode == (sram->flags & 4)) {
        __OSUnlockSram(0);
        return;
    }
    sram->flags &= 0xFFFFFFFB;
    sram->flags |= mode;
    __OSUnlockSram(1);
}

/** Returns whether progressive-scan output is enabled (SRAM flags bit 7). */
u32 OSGetProgressiveMode(void) {
    OSSram* sram;
    u32 on;

    sram = __OSLockSram();
    on = (sram->flags & 0x80) >> 7;
    __OSUnlockSram(FALSE);
    return on;
}

/** Stores the progressive-scan flag in SRAM flags bit 7, writing back only when it changed. */
void OSSetProgressiveMode(u32 on) {
#ifndef DEBUG
    u32 padding[1];
#endif
    OSSram* sram;

    ASSERTLINE(670, on == OS_PROGRESSIVE_MODE_OFF || on == OS_PROGRESSIVE_MODE_ON);

    on <<= 7;
    on &= 0x80;

    sram = __OSLockSram();
    if (on == (sram->flags & 0x80)) {
        __OSUnlockSram(FALSE);
        return;
    }

    sram->flags &= ~0x80;
    sram->flags |= on;
    __OSUnlockSram(TRUE);
}

/** Returns the video mode in the low two bits of the SRAM flags (0 if the stored value is above 2). */
u32 OSGetVideoMode(void) {
    OSSram* sram = __OSLockSram();
    u32 mode = sram->flags & 3;

    __OSUnlockSram(0);

    if (mode > 2) {
        mode = 0;
    }

    return mode;
}

/**
 * Stores the video mode in the low two bits of the SRAM flags (values above 2 become 0),
 * writing back only when it changed.
 */
void OSSetVideoMode(u32 mode) {
    OSSram* sram;
    int unused;

    ASSERTLINE(731, OS_VIDEO_MODE_NTSC <= mode && mode <= OS_VIDEO_MODE_MPAL);

    if (mode > 2) {
        mode = 0;
    }

    sram = __OSLockSram();

    if (mode == (sram->flags & 3)) {
        __OSUnlockSram(0);
        return;
    }
    sram->flags &= 0xFFFFFFFC;
    sram->flags |= mode;
    __OSUnlockSram(1);
}

/** Returns the console language selected in the system menu, from SRAM. */
u8 OSGetLanguage(void) {
    OSSram* sram = __OSLockSram();
    u8 language = sram->language;

    __OSUnlockSram(0);
    return language;
}

/** Stores the console language in SRAM, writing back only when it changed. */
void OSSetLanguage(u8 language) {
    OSSram* sram = __OSLockSram();
    int unused;

    if (language == sram->language) {
        __OSUnlockSram(0);
        return;
    }
    sram->language = language;
    __OSUnlockSram(1);
}

/** Returns bit 0x80 of the SRAM ntd byte (the boot-mode flag). */
u8 __OSGetBootMode(void) {
    OSSram* sram = __OSLockSram();
    u8 ntd = sram->ntd;
    __OSUnlockSram(0);
    return ntd & 0x80;
}

/** Writes the boot-mode flag (bit 0x80 of the SRAM ntd byte), writing back only when it changed. */
void __OSSetBootMode(u8 ntd) {
    OSSram* sram;
    int unused;

    ntd &= 0x80;
    sram = __OSLockSram();
    if (ntd == (sram->ntd & 0x80U)) {
        __OSUnlockSram(0);
        return;
    }
    sram->ntd &= 0xFFFFFF7F;
    sram->ntd |= ntd;
    __OSUnlockSram(1);
}

/** Returns whether EuRGB60 (60 Hz PAL) video is enabled (bit 0x40 of the SRAM ntd byte). */
u32 OSGetEuRgb60Mode(void) {
    OSSram* sram;
    u32 on;

    sram = __OSLockSram();
    on = (sram->ntd & 0x40) >> 6;
    __OSUnlockSram(0);
    return on;
}

/** Stores the EuRGB60 flag (bit 0x40 of the SRAM ntd byte), writing back only when it changed. */
void OSSetEuRgb60Mode(u32 on) {
#ifndef DEBUG
    u32 padding[1];
#endif
    OSSram* sram;

    ASSERTLINE(895, on == OS_EURGB60_OFF || on == OS_EURGB60_ON);
    on <<= 6;
    on &= 0x40;

    sram = __OSLockSram();
    if (on == (sram->ntd & 0x40)) {
        __OSUnlockSram(0);
    } else {
        sram->ntd &= ~0x40;
        sram->ntd |= on;
        __OSUnlockSram(1);
    }
}

/** Returns the wireless controller ID stored in extended SRAM for controller port chan. */
u16 OSGetWirelessID(s32 chan) {
    OSSramEx* sram;
    u16 id;

    sram = __OSLockSramEx();
    id = sram->wirelessPadID[chan];
    __OSUnlockSramEx(FALSE);
    return id;
}

/** Stores the wireless controller ID for port chan in extended SRAM, writing back only when it changed. */
void OSSetWirelessID(s32 chan, u16 id) {
    OSSramEx* sram;

    sram = __OSLockSramEx();
    if (sram->wirelessPadID[chan] != id) {
        sram->wirelessPadID[chan] = id;
        __OSUnlockSramEx(TRUE);
        return;
    }

    __OSUnlockSramEx(FALSE);
}

/** Returns the Game Boy Player (GBS) mode word from extended SRAM. */
u16 OSGetGbsMode(void) {
    OSSramEx* sram;
    u16 mode;

    sram = __OSLockSramEx();
    mode = sram->gbs;
    __OSUnlockSramEx(FALSE);
    return mode;
}

/**
 * Stores the Game Boy Player mode word in extended SRAM (values with invalid bit patterns become 0),
 * writing back only when it changed.
 */
void OSSetGbsMode(u16 mode) {
#ifndef DEBUG
    u32 padding[1];
#endif
    OSSramEx* sram;

    if (((u32)mode & 0x7c00) == 0x5000 || ((u32)mode & 0xc0) == 0xc0) {
        mode = 0;
    }

    sram = __OSLockSramEx();

    if (mode == sram->gbs) {
        __OSUnlockSramEx(FALSE);
        return;
    }
    sram->gbs = mode;

    __OSUnlockSramEx(TRUE);
}
