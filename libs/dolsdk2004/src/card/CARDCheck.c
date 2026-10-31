#include <dolphin/card.h>

#include "os/__os.h"
#include "__card.h"

// prototypes
static s32 VerifyID(CARDControl* card);
static s32 VerifyDir(CARDControl* card, int* pcurrent);
static s32 VerifyFAT(CARDControl* card, int* pcurrent);

/**
 * Computes the two 16-bit checksums the card file system uses:
 * the sum of the words and the sum of their bitwise inverses (a result of 0xFFFF is stored as 0).
 */
void __CARDCheckSum(void* ptr, int length, u16* checksum, u16* checksumInv) {
    u16* p;
    int i;

    ASSERTLINE(82, length % sizeof(u16) == 0);

    length /= sizeof(u16);
    *checksum = *checksumInv = 0;
    for (i = 0, p = ptr; i < length; i++, p++) {
        *checksum += *p;
        *checksumInv += ~*p;
    }

    if (*checksum == 0xFFFF)
        *checksum = 0;

    if (*checksumInv == 0xFFFF)
        *checksumInv = 0;
}

/**
 * Checks the card header block: device ID and size, its checksums,
 * the 12-byte serial number against the flash ID stored in SRAM (through a linear congruential sequence),
 * and the font encoding. Returns BROKEN, ENCODING or READY.
 */
static s32 VerifyID(CARDControl* card) {
    CARDID* id;
    u16 checksum;
    u16 checksumInv;
    OSSramEx* sramEx;
    OSTime rand;
    int i;

    id = card->workArea;

    if (id->deviceID != 0 || id->size != card->size)
        return CARD_RESULT_BROKEN;

    __CARDCheckSum(id, sizeof(CARDID) - sizeof(u32), &checksum, &checksumInv);
    if (id->checkSum != checksum || id->checkSumInv != checksumInv)
        return CARD_RESULT_BROKEN;

    rand = *(OSTime*)&id->serial[12];
    sramEx = __OSLockSramEx();
    for (i = 0; i < 12; i++) {
        rand = (rand * 1103515245 + 12345) >> 16;
        if (id->serial[i] != (u8)(sramEx->flashID[card - __CARDBlock][i] + rand)) {
            __OSUnlockSramEx(FALSE);
            return CARD_RESULT_BROKEN;
        }
        rand = ((rand * 1103515245 + 12345) >> 16) & 0x7FFF;
    }

    __OSUnlockSramEx(FALSE);

    if (id->encode != __CARDGetFontEncode())
        return CARD_RESULT_ENCODING;

    return CARD_RESULT_READY;
}

/**
 * Checks both directory copies' checksums.
 * Returns the number of bad copies; when both are good it picks the one with the newer check code as current
 * and copies it over the other.
 */
static s32 VerifyDir(CARDControl* card, int* pcurrent) {
    CARDDir* dir[2];
    CARDDirCheck* check[2];
    u16 checkSum;
    u16 checkSumInv;
    int i;
    int errors;
    int current;

    current = errors = 0;
    for (i = 0; i < 2; i++) {
        dir[i] = (CARDDir*)((u8*)card->workArea + (1 + i) * CARD_SYSTEM_BLOCK_SIZE);
        check[i] = CARDGetDirCheck(dir[i]);
        __CARDCheckSum(dir[i], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &checkSum, &checkSumInv);
        if (check[i]->checkSum != checkSum || check[i]->checkSumInv != checkSumInv) {
            ++errors;
            current = i;
            card->currentDir = 0;
        }
    }

    if (0 == errors) {
        if (card->currentDir == 0) {
            if ((check[0]->checkCode - check[1]->checkCode) < 0)
                current = 0;
            else
                current = 1;
            card->currentDir = dir[current];
            memcpy(dir[current], dir[current ^ 1], CARD_SYSTEM_BLOCK_SIZE);
        } else {
            current = (card->currentDir == dir[0]) ? 0 : 1;
        }
    }

    if (pcurrent)
        *pcurrent = current;

    return errors;
}

/**
 * Checks both FAT copies: checksum and that the stored free-block count matches the number of free entries.
 * Returns the number of bad copies; when both are good it picks the newer and copies it over the other.
 */
static s32 VerifyFAT(CARDControl* card, int* pcurrent) {
    u16* fat[2];
    u16* fatp;
    u16 nBlock;
    u16 cFree;
    int i;
    u16 checkSum;
    u16 checkSumInv;
    int errors;
    int current;

    current = errors = 0;
    for (i = 0; i < 2; i++) {
        fatp = fat[i] = (u16*)((u8*)card->workArea + (3 + i) * CARD_SYSTEM_BLOCK_SIZE);

        __CARDCheckSum(&fatp[CARD_FAT_CHECKCODE], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32), &checkSum, &checkSumInv);
        if (fatp[CARD_FAT_CHECKSUM] != checkSum || fatp[CARD_FAT_CHECKSUMINV] != checkSumInv) {
            ++errors;
            current = i;
            card->currentFat = 0;
            continue;
        }

        cFree = 0;
        for (nBlock = CARD_NUM_SYSTEM_BLOCK; nBlock < card->cBlock; nBlock++) {
            if (fatp[nBlock] == CARD_FAT_AVAIL)
                cFree++;
        }

        if (cFree != fatp[CARD_FAT_FREEBLOCKS]) {
            ++errors;
            current = i;
            card->currentFat = 0;
            continue;
        }
    }

    if (0 == errors) {
        if (card->currentFat == 0) {
            if (((s16)fat[0][CARD_FAT_CHECKCODE] - (s16)fat[1][CARD_FAT_CHECKCODE]) < 0)
                current = 0;
            else
                current = 1;
            card->currentFat = fat[current];
            memcpy(fat[current], fat[current ^ 1], CARD_SYSTEM_BLOCK_SIZE);
        } else
            current = (card->currentFat == fat[0]) ? 0 : 1;
    }

    if (pcurrent)
        *pcurrent = current;

    return errors;
}

/**
 * Mount-time check: header, then directory and FAT.
 * A single bad directory or FAT copy counts as BROKEN here; READY only when nothing is wrong.
 */
s32 __CARDVerify(CARDControl* card) {
    s32 result;
    int errors;

    result = VerifyID(card);
    if (result < 0)
        return result;

    errors = VerifyDir(card, NULL);
    errors += VerifyFAT(card, NULL);
    switch (errors) {
    case 0: 
        ASSERTLINE(301, card->currentDir);
        ASSERTLINE(302, card->currentFat);
        return CARD_RESULT_READY;
    case 1:
        return CARD_RESULT_BROKEN;
    default:
        return CARD_RESULT_BROKEN;
    }
}

/**
 * Checks the mounted card and repairs it where possible.
 * One bad directory or FAT copy is rebuilt from the good one;
 * then every file's block chain is walked (a bad, shared or wrongly sized chain gives BROKEN),
 * blocks no file owns are returned to the free list and the free count is corrected.
 * If a write is needed, 'xferBytes' is set to 8 KiB and the directory or FAT is saved before the callback runs.
 */
s32 CARDCheckExAsync(s32 chan, s32* xferBytes, CARDCallback callback) {
    CARDControl* card;
    CARDDir* dir[2];
    u16* fat[2];
    u16* map;
    s32 result;
    int errors;
    int currentFat;
    int currentDir;
    s32 fileNo;
    u16 iBlock;
    u16 cBlock;
    u16 cFree;
    BOOL updateFat = FALSE;
    BOOL updateDir = FALSE;
    BOOL updateOrphan = FALSE;

    ASSERTLINE(346, 0 <= chan && chan < 2);

    if (xferBytes) {
        *xferBytes = 0;
    }

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    result = VerifyID(card);
    if (result < 0) {
        return __CARDPutControlBlock(card, result);
    }

    errors = VerifyDir(card, &currentDir);
    errors += VerifyFAT(card, &currentFat);
    if (1 < errors) {
        return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
    }

    dir[0] = (CARDDir*)((u8*)card->workArea + (1 + 0) * CARD_SYSTEM_BLOCK_SIZE);
    dir[1] = (CARDDir*)((u8*)card->workArea + (1 + 1) * CARD_SYSTEM_BLOCK_SIZE);
    fat[0] = (u16*)((u8*)card->workArea + (3 + 0) * CARD_SYSTEM_BLOCK_SIZE);
    fat[1] = (u16*)((u8*)card->workArea + (3 + 1) * CARD_SYSTEM_BLOCK_SIZE);

    ASSERTLINE(377, errors == 0 || errors == 1);

    switch (errors) {
    case 0:
        ASSERTLINE(381, card->currentDir);
        ASSERTLINE(382, card->currentFat);
        break;
    case 1:
        if (!card->currentDir) {
            ASSERTLINE(387, card->currentFat);
            card->currentDir = dir[currentDir];
            memcpy(dir[currentDir], dir[currentDir ^ 1], CARD_SYSTEM_BLOCK_SIZE);
            updateDir = TRUE;
        } else {
            ASSERTLINE(394, !card->currentFat);
            card->currentFat = fat[currentFat];
            memcpy(fat[currentFat], fat[currentFat ^ 1], CARD_SYSTEM_BLOCK_SIZE);
            updateFat = TRUE;
        }
        break;
    }

    map = fat[currentFat ^ 1];
    memset(map, 0, CARD_SYSTEM_BLOCK_SIZE);

    for (fileNo = 0; fileNo < CARD_MAX_FILE; fileNo++) {
        CARDDir* ent;

        ent = &card->currentDir[fileNo];
        if (ent->gameName[0] == 0xff) {
            continue;
        }

        for (iBlock = ent->startBlock, cBlock = 0; iBlock != 0xFFFF && cBlock < ent->length;
             iBlock = card->currentFat[iBlock], ++cBlock)
        {
            if (!CARDIsValidBlockNo(card, iBlock) || 1 < ++map[iBlock]) {
                return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
            }
        }

        if (cBlock != ent->length || iBlock != 0xFFFF) {
            return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
        }
    }

    cFree = 0;
    for (iBlock = CARD_NUM_SYSTEM_BLOCK; iBlock < card->cBlock; iBlock++) {
        u16 nextBlock;

        nextBlock = card->currentFat[iBlock];
        if (map[iBlock] == 0) {
            if (nextBlock != CARD_FAT_AVAIL) {
                card->currentFat[iBlock] = CARD_FAT_AVAIL;
                updateOrphan = TRUE;
            }
            cFree++;
        } else if (!CARDIsValidBlockNo(card, nextBlock) && nextBlock != 0xFFFF) {
            return __CARDPutControlBlock(card, CARD_RESULT_BROKEN);
        }
    }

    if (cFree != card->currentFat[CARD_FAT_FREEBLOCKS]) {
        card->currentFat[CARD_FAT_FREEBLOCKS] = cFree;
        updateOrphan = TRUE;
    }

    if (updateOrphan) {
        __CARDCheckSum(&card->currentFat[CARD_FAT_CHECKCODE], CARD_SYSTEM_BLOCK_SIZE - sizeof(u32),
                       &card->currentFat[CARD_FAT_CHECKSUM],
                       &card->currentFat[CARD_FAT_CHECKSUMINV]);
    }

    memcpy(fat[currentFat ^ 1], fat[currentFat], CARD_SYSTEM_BLOCK_SIZE);

    if (updateDir) {
        if (xferBytes) {
            *xferBytes = CARD_SYSTEM_BLOCK_SIZE;
        }
        return __CARDUpdateDir(chan, callback);
    }

    if (updateFat | updateOrphan) {
        if (xferBytes) {
            *xferBytes = CARD_SYSTEM_BLOCK_SIZE;
        }
        return __CARDUpdateFatBlock(chan, card->currentFat, callback);
    }

    __CARDPutControlBlock(card, CARD_RESULT_READY);
    if (callback) {
        BOOL enabled = OSDisableInterrupts();
        callback(chan, CARD_RESULT_READY);
        OSRestoreInterrupts(enabled);
    }
    return CARD_RESULT_READY;
}

/** Asynchronous CARDCheckExAsync that discards the transferred-bytes count. */
s32 CARDCheckAsync(s32 chan, CARDCallback callback) {
    s32 xferBytes;
    return CARDCheckExAsync(chan, &xferBytes, callback);
}

/** Blocking CARDCheckExAsync: waits for the check and its repair write to finish. */
s32 CARDCheckEx(s32 chan, s32* xferBytes) {
    s32 result = CARDCheckExAsync(chan, xferBytes, __CARDSyncCallback);
    if (result < 0 || xferBytes == 0) {
        return result;
    }

    return __CARDSync(chan);
}

/** Blocking check of the card's file system; see CARDCheckExAsync. */
s32 CARDCheck(s32 chan) {
    s32 xferBytes;
    return CARDCheckEx(chan, &xferBytes);
}
