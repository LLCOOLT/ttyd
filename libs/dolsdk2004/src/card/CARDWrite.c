#include <dolphin/card.h>

#include "__card.h"

// prototypes
static void WriteCallback(s32 chan, s32 result);
static void EraseCallback(s32 chan, s32 result);

/**
 * Completion callback for each sector written by CARDWriteAsync: stops with CANCELED if cancelled;
 * after the last sector it stamps the modification time and saves the directory,
 * otherwise follows the FAT to the next block and erases it.
 */
static void WriteCallback(s32 chan, s32 result) {
    CARDControl* card;
    CARDCallback callback;
    u16* fat;
    CARDDir* dir;
    CARDDir* ent;
    CARDFileInfo* fileInfo;

    card = &__CARDBlock[chan];
    if (result >= 0) {
        fileInfo = card->fileInfo;
        if (fileInfo->length < 0) {
            result = CARD_RESULT_CANCELED;
            goto after;
        }
        fileInfo->length -= card->sectorSize;
        if (fileInfo->length <= 0) {
            dir = __CARDGetDirBlock(card);
            ent = dir + fileInfo->fileNo;
            ent->time = OSGetTime()/(__OSBusClock/4);
            callback = card->apiCallback;
            card->apiCallback = NULL;
            result = __CARDUpdateDir(chan, callback);
            goto check;
        } else {
            fat = __CARDGetFatBlock(card);
            fileInfo->offset += card->sectorSize;
            fileInfo->iBlock = fat[fileInfo->iBlock];
            if ((fileInfo->iBlock < 5) || (fileInfo->iBlock >= card->cBlock)) {
                result = CARD_RESULT_BROKEN;
                goto after;
            }
            result = __CARDEraseSector(chan, card->sectorSize * fileInfo->iBlock, EraseCallback);
check:;
            if (result < 0) {
                goto after;
            }
        }
    } else {
after:;
        callback = card->apiCallback;
        card->apiCallback = NULL;
        __CARDPutControlBlock(card, result);
        ASSERTLINE(0x86, callback);
        callback(chan, result);
    }
}

/** Completion callback for the sector erase of CARDWriteAsync: writes one sector from the buffer into that sector. */
static void EraseCallback(s32 chan, s32 result) {
    CARDControl* card;
    CARDCallback callback;
    CARDFileInfo* fileInfo;

    card = &__CARDBlock[chan];
    if (result >= 0) {
        fileInfo = card->fileInfo;
        ASSERTLINE(161, OFFSET(fileInfo->offset, card->sectorSize) == 0);
        result = __CARDWrite(chan, card->sectorSize * fileInfo->iBlock, card->sectorSize, card->buffer, WriteCallback);
        if (result < 0) {
            goto after;
        }
    } else {
after:;
        callback = card->apiCallback;
        card->apiCallback = NULL;
        __CARDPutControlBlock(card, result);
        ASSERTLINE(175, callback);
        callback(chan, result);
    }
}

/**
 * Writes 'length' bytes at 'offset' of an open file, erasing and rewriting one sector at a time;
 * both must be multiples of the sector size and the file must be writable. Completes through the callback.
 */
s32 CARDWriteAsync(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset, CARDCallback callback) {
    CARDControl* card;
    s32 result;
    CARDDir* dir;
    CARDDir* ent;

    ASSERTLINE(210, buf && ((u32) buf % 32) == 0);
    ASSERTLINE(211, 0 < length);

    result = __CARDSeek(fileInfo, length, offset, &card);
    if (result < 0) {
        return result;
    }

    ASSERTLINE(217, OFFSET(offset, card->sectorSize) == 0);
    ASSERTLINE(218, OFFSET(length, card->sectorSize) == 0);

    if (OFFSET(offset, card->sectorSize) != 0 || OFFSET(length, card->sectorSize) != 0)
        return __CARDPutControlBlock(card, CARD_RESULT_FATAL_ERROR);

    dir = __CARDGetDirBlock(card);
    ent = &dir[fileInfo->fileNo];
    result = __CARDIsWritable(card, ent);
    if (result < 0)
        return __CARDPutControlBlock(card, result);

    DCStoreRange((void*)buf, (u32)length);
    card->apiCallback = callback ? callback : __CARDDefaultApiCallback;
    card->buffer = (void*)buf;

    result = __CARDEraseSector(fileInfo->chan, card->sectorSize * (u32)fileInfo->iBlock, EraseCallback);
    if (result < 0)
        __CARDPutControlBlock(card, result);
    return result;
}

/** Blocking CARDWriteAsync; how a game saves its data. */
s32 CARDWrite(CARDFileInfo* fileInfo, void* buf, s32 length, s32 offset) {
    s32 result = CARDWriteAsync(fileInfo, buf, length, offset, __CARDSyncCallback);
    if (result < 0) {
        return result;
    }

    return __CARDSync(fileInfo->chan);
}
