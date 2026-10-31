#include <dolphin.h>
#include <dolphin/mcc.h>

#ifdef DEBUG
/**
 * Version string of the TTY (text console over the memory card channel) library in the debug build, kept in
 * the binary as a build stamp.
 */
const char* __TTYVersion = "<< Dolphin SDK - TTY\tdebug build: Apr  5 2004 03:57:08 (0x2301) >>";
#else
/**
 * Version string of the TTY (text console over the memory card channel) library in the release build, kept in
 * the binary as a build stamp.
 */
const char* __TTYVersion = "<< Dolphin SDK - TTY\trelease build: Apr  5 2004 04:15:50 (0x2301) >>";
#endif

volatile static u8 gBuf[0x2000];

static u32 gOldEvent;
volatile static MCC_CHANNEL gChID;
volatile static int gQuery;
volatile static u32 gReadDone;
volatile static u32 gPrintfID;
volatile static u32 gBufHead;
volatile static u32 gBufTail;

// prototypes
static int ttyIsInitialized(void);
static void ShowChannelInfo(MCC_CHANNEL chID);
static void ttyMccChannelEvent(MCC_CHANNEL chID, u32 event, u32 value);
static void ttyClearProperty(MCC_CHANNEL chID);
static int ttyWaiting(int timeout, volatile int* flag);
static int ttyWrite(u32 offset, void* data, s32 size);
static int ttyFlush(u32 msgID, BOOL waitResult);

/** Returns whether the TTY channel is open (gChID is non-zero). */
static int ttyIsInitialized(void) {
    BOOL bResult = gChID != 0;
    return bResult;
}

/** Prints an MCC channel's first block, block count, connection state and lock state with OSReport. */
static void ShowChannelInfo(MCC_CHANNEL chID) {
    MCC_Info info;

    MCCGetChannelInfo(chID, &info);
    OSReport("%2d: FirstBlock:%02d,BlockLength:%02d,Connect:%s,Lock:%s.\n", chID, 
             info.firstBlock,info.blockLength,
             (info.connect == MCC_CONNECT_DISCONNECT)   ? "DISCONNECT" : 
             (info.connect == MCC_CONNECT_HOST_OPEN)    ? "HOST_OPEN" : 
             (info.connect == MCC_CONNECT_TARGET_OPEN)  ? "TARGET_OPEN" : 
             (info.connect == MCC_CONNECT_CONNECTED)    ? "CONNECTED" : "UNKNOWN",
             (info.isLocked == FALSE)                   ? "UNLOCKED" : 
             (info.isLocked == TRUE)                    ? "LOCKED" : "UNKNOWN");
}

/**
 * MCC event callback for the TTY channel: records the channel on connect and clears it on disconnect;
 * answers the query notify (protocol 0x210), and on the host's "text consumed" notify (0x400000) advances the
 * ring-buffer head by the block count and records the message id in gReadDone.
 */
static void ttyMccChannelEvent(MCC_CHANNEL chID, u32 event, u32 value) {
    u32 notify;
    u32 size;
    u32 msgID;

    switch(event) {
    case MCC_EVENT_CONNECT:
        gChID = chID;
        return;
    case MCC_EVENT_DISCONNECT:
        gChID = 0;
        return;
    case MCC_EVENT_UNK_0x100:
        notify = (value & (0xF00000));
        switch(notify) {
        case 0x200000:                              
            if ((u16)value == 0x210) {
                gQuery = 1;
            }
            return;
        case 0x400000:                              
            size = (value >> 8) & 0xFF;
            msgID = (value) & 0xFF;
            if ((gBufTail - gBufHead) >= 0x2000) {
                gBufHead = ((u32) gBufHead < 0x2000U) ? gBufHead : gBufHead - 0x2000;
                gBufTail = ((u32) gBufTail < 0x2000U) ? gBufTail : gBufTail - 0x2000;
            }
            if ((u32) gBufHead >= 0x2000U) {
                gBufHead -= 0x2000;
                gBufTail -= 0x2000;
            }
            if (size == 0) {
                gBufHead += size << 5;
                gReadDone = (u32) msgID;
                return;
            }
            gBufHead += size << 5;
            gReadDone = (u32) msgID;
        }
    }
}

/**
 * Opens an MCC channel (one block) as a debug text console:
 * MCCInit with 5 second timeout, MCCOpen with ttyMccChannelEvent, event mask 0x30 (no read/write events).
 * Returns 0 if already initialised or on failure.
 */
int TTYInit(MCC_EXI exiChannel, MCC_CHANNEL chID) {
    if (ttyIsInitialized()) {
        return 0;
    }

    OSRegisterVersion(__TTYVersion);

    if (MCCInit(exiChannel, 5, NULL) && MCCOpen(chID, 1, ttyMccChannelEvent)) {
        gOldEvent = MCCSetChannelEventMask(chID, 0x30);
        ttyClearProperty(chID);
        return 1;
    }

    return 0;
}

/** Restores the old event mask, closes the TTY channel and clears its state. */
void TTYExit(void) {
    if (ttyIsInitialized()) {
        MCCSetChannelEventMask(gChID, gOldEvent);
        if (MCCClose(gChID) != 0) {
            ttyClearProperty(0);
        }
    }
}

/**
 * Asks the host if a TTY listener exists: sends notify 0x100210 and waits up to 5 seconds;
 * stalls 5 seconds before returning 0 on failure.
 */
int TTYQuery(void) {
    u32 tick;

    if (ttyIsInitialized()) {
        gQuery = 0;
        if (MCCNotify(gChID, 0x100210)) {
            return ttyWaiting(5, &gQuery);
        }
    }

    tick = OSGetTick();
    do {} while(OSTicksToSeconds(OSGetTick() - tick) < 5);
    return 0;
}

/**
 * printf to the host console: formats up to 8179 characters into a packet (protocol 0x210) with a running
 * message id, copies it into the 8 KB ring buffer through MCCWrite (waiting for space with ttyFlush if needed),
 * and flushes when the text has a newline or the id wraps at 0xFF.
 */
int TTYPrintf(const char* format, ...) {
    if (ttyIsInitialized() && format != NULL) {
        MCC_Hdr* hdr;
        u32* id;
        char* str;
        u32 maxDataSize;
        u32 formatLength;
        u32 dataSize;
        int err;
        char* eof;
        va_list argptr;
        u32 prosecced;

        hdr = (void*)&gBuf;
        id = (u32*)(hdr + 1);
        str = (char*)(id + 1);
    
        maxDataSize = 8179;
        formatLength = strlen(format);
        if (formatLength > maxDataSize) {
            eof = (void*)((-1 + maxDataSize + (u32)format));
            *(eof) = 0;
        }
    
        va_start(argptr, format);
        err = vsprintf(str, format, argptr);
        if (strlen(str) < maxDataSize) {
            str[strlen(str)] = 0;
        } else {
            err = -1;
        }
    
        if (err < 0) {
            return 0;
        }
    
        hdr->length = strlen(str) + 13;
        hdr->rsvd = 0;
        hdr->protocol = 0x210;
        dataSize = OSRoundUp32B(hdr->length) & ~1;
        if ((0x2000 - (gBufTail - gBufHead)) <= dataSize) {
            ttyFlush(gPrintfID, 1);
        }
    
        gPrintfID += 1;
        gPrintfID = (u8) gPrintfID;
        *id = gPrintfID;
    
        if ((0x2000 - (gBufTail & 0x1FFF)) < dataSize) {
            prosecced = 0x2000 - (gBufTail & 0x1FFF);
            ttyWrite(gBufTail & 0x1FFF, (char*)&gBuf, prosecced);
            ttyWrite(0, (char*)&gBuf + prosecced, dataSize - prosecced);
        } else {
            ttyWrite(gBufTail & 0x1FFF, (char*)&gBuf, dataSize);
        }
    
        gBufTail += dataSize;
        if (strchr(str, '\n') != 0) {
            ttyFlush(gPrintfID, TRUE);
        } else if (gPrintfID == 0xFF) {
            ttyFlush(gPrintfID, TRUE);
        }
    
        va_end(format);
        return 1;
    }

    return 0;
}

/**
 * Public flush: notifies the host of the newest message id and waits until the host has read it;
 * 1 if nothing is pending.
 */
int TTYFlush(void) {
    if (!ttyIsInitialized()) {
        return 0;
    }

    return ttyFlush(gPrintfID, TRUE);
}

/** Sets the channel id and zeroes the query flag, read-done id, message id and ring buffer head and tail. */
static void ttyClearProperty(MCC_CHANNEL chID) {
    gChID = chID;
    gQuery = 0;
    gReadDone = 0;
    gPrintfID = 0;
    gBufHead = 0;
    gBufTail = 0;
}

/** Spins until *flag becomes non-zero or the timeout expires; returns 1 if the flag was set. */
static int ttyWaiting(int timeout, volatile int* flag) {
    u32 tickStart;
    u32 tickDist;

    tickStart = OSGetTick();
    timeout = OSSecondsToTicks(timeout);
    while(*flag == 0) {
        tickDist = OSGetTick() - tickStart;
        tickDist = (tickDist & 0x80000000) ? (0x80000000 - tickStart) + OSGetTick() : tickDist;
        if (OSTicksToSeconds(tickDist) >= timeout) {
            return 0;
        }
    }

    return 1;
}

/** Writes size bytes at offset of the TTY channel buffer with MCCWrite; returns 1 on success. */
static int ttyWrite(u32 offset, void* data, s32 size) {
    if (MCCWrite(gChID, offset, data, size, 0)) {
        return 1;
    }
    return 0;
}

/**
 * Sends notify 0x300000 with the message id (nothing if the ring buffer is empty) and, if waitResult,
 * spins until the host reports that id read; hangs forever if the notify cannot be sent.
 */
static int ttyFlush(u32 msgID, BOOL waitResult) {
    u32 notify;

    notify = msgID | 0x300000;

    if ((gBufTail - gBufHead) == 0) {
        return 1;
    }

    if (MCCNotify(gChID, notify) == 0) {
        while(1)
            ;
    }

    if (waitResult) {
        do {} while (gReadDone != msgID);
    }

    return 1;
}
