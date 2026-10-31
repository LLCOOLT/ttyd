#include <dolphin/card.h>
#include <dolphin/exi.h>

#include "os/__os.h"
#include "__card.h"

static u32 SectorSizeTable[8] = {
    8 * 1024, 16 * 1024, 32 * 1024, 64 * 1024, 128 * 1024, 256 * 1024, 0, 0,
};

static u32 LatencyTable[8] = {
    4, 8, 16, 32, 64, 128, 256, 512,
};

// prototypes
static s32 DoMount(s32 chan);
static void DoUnmount(s32 chan, s32 result);

/**
 * Decides from the EXI ID read at attach time whether the device is a usable memory card:
 * the ID bits, a capacity of 4 to 128 megabits, a known sector size and at least 8 sectors.
 * The special ID 0x80000004 is accepted only if a vendor ID has been set.
 */
static BOOL IsCard(u32 id) {
    u32 size;
    s32 sectorSize;
    if (id & (0xFFFF0000) && (id != 0x80000004 || __CARDVendorID == 0xFFFF)) {
        return FALSE;
    }

    if ((id & 3) != 0) {
        return FALSE;
    }

    size = id & 0xfc;
    switch (size) {
    case 4:
    case 8:
    case 16:
    case 32:
    case 64:
    case 128:
        break;
    default:
        return FALSE;
        break;
    }

    sectorSize = SectorSizeTable[(id & 0x00003800) >> 11];
    if (sectorSize == 0) {
        return FALSE;
    }

    if ((size * 1024 * 1024 / 8) / sectorSize < 8) {
        return FALSE;
    }

    return TRUE;
}

/**
 * Sets or clears bit 0x80 of a byte in low memory (0x800030E3) that makes CARDProbe,
 * CARDProbeEx and CARDMountAsync report no card.
 */
void __CARDDisable(BOOL disable) {
    BOOL enabled = OSDisableInterrupts();

    __gUnknown800030E3 &= ~0x80;
    if (disable) {
        __gUnknown800030E3 |= 0x80;
    }

    OSRestoreInterrupts(enabled);
}

/**
 * Returns nonzero if a device is plugged into the channel's slot (EXIProbe),
 * or 0 if card access is disabled by __CARDDisable.
 */
int CARDProbe(s32 chan) {
    if (__gUnknown800030E3 & 0x80) {
        return 0;
    } else {
        return EXIProbe(chan);
    }
}

/**
 * Like CARDProbe but with details: returns NOCARD, BUSY (not yet identified),
 * WRONGDEVICE (not a memory card) or READY, and reports the card's capacity in megabits
 * and sector size in bytes through the pointers (either may be NULL).
 */
s32 CARDProbeEx(s32 chan, s32* memSize, s32* sectorSize) {
    u32 id;
    CARDControl* card;
    BOOL enabled;
    s32 result;
    int probe;

    if (chan < 0 || 2 <= chan)
        return CARD_RESULT_FATAL_ERROR;

    if (__gUnknown800030E3 & 0x80) {
        return CARD_RESULT_NOCARD;
    }

    card = &__CARDBlock[chan];
    enabled = OSDisableInterrupts();

    probe = EXIProbeEx(chan);
    if (probe == -1)
        result = CARD_RESULT_NOCARD;
    else if (probe == 0)
        result = CARD_RESULT_BUSY;
    else if (card->attached) {
        if (card->mountStep < 1)
            result = CARD_RESULT_BUSY;
        else {
            if (memSize)
                *memSize = card->size;

            if (sectorSize)
                *sectorSize = card->sectorSize;

            result = CARD_RESULT_READY;
        }
    }
    else if ((EXIGetState(chan) & 8))
        result = CARD_RESULT_WRONGDEVICE;
    else if (!EXIGetID(chan, 0, &id))
        result = CARD_RESULT_BUSY;
    else if (IsCard(id)) {
        if (memSize)
            *memSize = (s32)(id & 0xfc);
        
        if (sectorSize)
            *sectorSize = SectorSizeTable[(id & 0x00003800) >> 11];
        result = CARD_RESULT_READY;
    } else {
        result = CARD_RESULT_WRONGDEVICE;
    }

    OSRestoreInterrupts(enabled);
    return result;
}

/**
 * One step of the mount sequence, repeated from __CARDMountCallback.
 * Step 0 reads the EXI ID and derives size, sector size, block count and latency,
 * reads the vendor ID (512-byte pages in fast mode on 0xEC cards, 128 otherwise), clears the status and,
 * if the card is still locked, starts __CARDUnlock
 * and saves the flash ID in SRAM (otherwise checks the saved ID's checksum). Step 1 enables the card interrupt.
 * Later steps read the system blocks one at a time into the work area.
 */
static s32 DoMount(s32 chan) {
    CARDControl* card;
    u32 id;
    u8 status;
    s32 result;
    OSSramEx* sram;
    int i;
    u8 checkSum;
    int step;

    ASSERTLINE(399, 0 <= chan && chan < 2);

    card = &__CARDBlock[chan];
    if (card->mountStep == 0) {
        if (EXIGetID(chan, 0, &id) == 0) {
            result = CARD_RESULT_NOCARD;
        } else if (IsCard(id)) {
            result = CARD_RESULT_READY;
        } else {
            result = CARD_RESULT_WRONGDEVICE;
        }

        if (result < 0)
            goto error;

        card->cid = id;
        card->size = (u16)(id & 0xFC);
        ASSERTLINE(424, card->size);
        
        card->sectorSize = SectorSizeTable[(id & 0x00003800) >> 11];
        ASSERTLINE(426, card->sectorSize);

        card->cBlock = (u16)((card->size * 1024 * 1024 / 8) / card->sectorSize);
        ASSERTLINE(428, 8 <= card->cBlock);

        card->latency = LatencyTable[(id & 0x00000700) >> 8];

        result = __CARDReadVendorID(chan, &card->vendorID);
        if (result < 0)
            goto error;

        if (CARDGetFastMode() && (card->vendorID >> 8) == 0xEC) {
            card->pageSize = 512;
        } else {
            card->pageSize = 128;
        }

        result = __CARDClearStatus(chan);
        if (result < 0)
            goto error;

        result = __CARDReadStatus(chan, &status);
        if (result < 0)
            goto error;

        if (!EXIProbe(chan)) {
            result = CARD_RESULT_NOCARD;
            goto error;
        }

        if (!(status & 0x40)) {
            result = __CARDUnlock(chan, card->id);
            if (result < 0)
                goto error;

            checkSum = 0;
            sram = __OSLockSramEx();
            for (i = 0; i < 12; i++) {
                sram->flashID[chan][i] = card->id[i];
                checkSum += card->id[i];
            }
            sram->flashIDCheckSum[chan] = (u8)~checkSum;
            __OSUnlockSramEx(TRUE);

            return result;
        } else {
            card->mountStep = 1;

            checkSum = 0;
            sram = __OSLockSramEx();
            for (i = 0; i < 12; i++)
                checkSum += sram->flashID[chan][i];

            __OSUnlockSramEx(FALSE);
            if (sram->flashIDCheckSum[chan] != (u8)~checkSum) {
                result = CARD_RESULT_IOERROR;
                goto error;
            }
        }
    }

    if (card->mountStep == 1) {
        if (card->cid == 0x80000004) {
            u16 vendorID;

            sram = __OSLockSramEx();
            vendorID = *(u16*)sram->flashID[chan];
            __OSUnlockSramEx(FALSE);

            if (__CARDVendorID == 0xFFFF || vendorID != __CARDVendorID) {
                result = CARD_RESULT_WRONGDEVICE;
                goto error;
            }
        }

        card->mountStep = 2;

        result = __CARDEnableInterrupt(chan, TRUE);
        if (result < 0)
            goto error;

        EXISetExiCallback(chan, __CARDExiHandler);
        EXIUnlock(chan);
        DCInvalidateRange(card->workArea, CARD_WORKAREA_SIZE);
    }

    step = card->mountStep - 2;
    result = __CARDRead(chan, (u32)card->sectorSize * step, CARD_SYSTEM_BLOCK_SIZE,
                        (u8 *)card->workArea + (CARD_SYSTEM_BLOCK_SIZE * step), __CARDMountCallback);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;

error:
    EXIUnlock(chan);
    DoUnmount(chan, result);
    return result;
}

/**
 * Completion callback of each mount step: on READY it advances to the next step or,
 * after the last block is read, verifies the card with __CARDVerify;
 * on UNLOCKED it takes the channel and continues; on IOERROR or NOCARD it unmounts.
 * When finished it releases the channel and calls the attach callback with the result.
 */
void __CARDMountCallback(s32 chan, s32 result) {
    CARDControl* card;
    CARDCallback callback;

    ASSERTLINE(570, 0 <= chan && chan < 2);

    card = &__CARDBlock[chan];
    switch (result) {
    case CARD_RESULT_READY:
        if (++card->mountStep < CARD_MAX_MOUNT_STEP) {
            result = DoMount(chan);
            if (0 <= result)
                return;
        } else
            result = __CARDVerify(card);
        break;
    case CARD_RESULT_UNLOCKED:
        card->unlockCallback = __CARDMountCallback;
        if (!EXILock(chan, 0, __CARDUnlockedHandler)) {
            return;
        }
        card->unlockCallback = 0;

        result = DoMount(chan);
        if (result >= 0)
            return;
        break;
    case CARD_RESULT_IOERROR:
    case CARD_RESULT_NOCARD:
        DoUnmount(chan, result);
        break;
    }

    callback = card->apiCallback;
    card->apiCallback = NULL;
    __CARDPutControlBlock(card, result);
    ASSERTLINE(620, callback);
    callback(chan, result);
}

/**
 * Starts mounting the card in a channel using 'workArea' (CARD_WORKAREA_SIZE bytes) as scratch space
 * and permanent storage for the directory and FAT.
 * 'detachCallback' is called if the card is later removed; 'attachCallback' reports the result of the mount.
 * Returns right away with BUSY, NOCARD, WRONGDEVICE or READY.
 */
s32 CARDMountAsync(s32 chan, void* workArea, CARDCallback detachCallback, CARDCallback attachCallback) {
    CARDControl* card;
    BOOL enabled;

    ASSERTLINE(652, workArea && ((u32) workArea % 32 == 0));
    ASSERTLINE(653, 0 <= chan && chan < 2);

    if (chan < 0 || 2 <= chan)
        return CARD_RESULT_FATAL_ERROR;

    if (__gUnknown800030E3 & 0x80) {
        return CARD_RESULT_NOCARD;
    }

    card = &__CARDBlock[chan];

    enabled = OSDisableInterrupts();
    if (card->result == CARD_RESULT_BUSY) {
        OSRestoreInterrupts(enabled);
        return CARD_RESULT_BUSY;
    }

    if (!card->attached && (EXIGetState(chan) & 0x08)) {
        OSRestoreInterrupts(enabled);
        return CARD_RESULT_WRONGDEVICE;
    }

    card->result = CARD_RESULT_BUSY;
    card->workArea = workArea;
    card->extCallback = detachCallback;
    card->apiCallback = attachCallback ? attachCallback : __CARDDefaultApiCallback;
    card->exiCallback = 0;

    if (!card->attached && !EXIAttach(chan, __CARDExtHandler)) {
        card->result = CARD_RESULT_NOCARD;
        OSRestoreInterrupts(enabled);
        return CARD_RESULT_NOCARD;
    }

    card->mountStep = 0;
    card->attached = TRUE;
    EXISetExiCallback(chan, 0);
    OSCancelAlarm(&card->alarm);

    card->currentDir = 0;
    card->currentFat = 0;

    OSRestoreInterrupts(enabled);

    card->unlockCallback = __CARDMountCallback;
    if (!EXILock(chan, 0, __CARDUnlockedHandler))
        return CARD_RESULT_READY;

    card->unlockCallback = 0;
    return DoMount(chan);
}

/** Blocking CARDMountAsync: attaches to the card and waits until the mount sequence finishes. Games call this first. */
s32 CARDMount(s32 chan, void* workArea, CARDCallback detachCallback) {
    s32 result = CARDMountAsync(chan, workArea, detachCallback, __CARDSyncCallback);

    if (result < 0)
        return result;
    return __CARDSync(chan);
}

/**
 * Detaches a channel: clears the EXI callback, detaches from EXI, cancels the timeout alarm,
 * marks the card not attached and records 'result' as the channel result.
 */
static void DoUnmount(s32 chan, s32 result) {
    CARDControl* card;
    BOOL enabled;

    ASSERTLINE(758, 0 <= chan && chan < 2);

    card = &__CARDBlock[chan];
    enabled = OSDisableInterrupts();
    if (card->attached) {
        EXISetExiCallback(chan, 0);
        EXIDetach(chan);
        OSCancelAlarm(&card->alarm);
        card->attached = FALSE;
        card->result = result;
        card->mountStep = 0;
    }
    OSRestoreInterrupts(enabled);
}

/** Unmounts the card in a channel (BUSY if an operation is running); the card must be mounted again before use. */
s32 CARDUnmount(s32 chan) {
    CARDControl* card;
    s32 result;

    ASSERTLINE(793, 0 <= chan && chan < 2);

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0)
        return result;

    DoUnmount(chan, CARD_RESULT_NOCARD);
    return CARD_RESULT_READY;
}
