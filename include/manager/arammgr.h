// arammgr.c: the ARAM manager (ARAMEntry, ARAMWork): auxiliary RAM allocation and ARQ transfers.
#pragma once

#include <dolphin/ar.h>
#include <dolphin/arq.h>

// ARAMEntry.flags bits.
enum ARAMEntryFlags {
    ARAM_ENTRY_IN_USE = 0x1,        // the entry slot is taken
    ARAM_ENTRY_TO_ARAM = 0x2,       // an upload to ARAM was posted
    ARAM_ENTRY_TO_ARAM_DONE = 0x4,  // the upload finished (arqCallbackToAram)
    ARAM_ENTRY_TO_MRAM = 0x8,       // a download back to main RAM was posted
    ARAM_ENTRY_TO_MRAM_DONE = 0x10, // the download finished (arqCallbackToMram)
    ARAM_ENTRY_SPENT = 0x20,        // read back; the next compaction frees the entry
};

typedef struct ARAMEntry {
    vu16 flags;             // 0x0
    u8 pad_0x2[2];          // 0x2
    ARQRequest request;     // 0x4
    u32 size;               // 0x24
    u32 aramAddr;           // 0x28
    void* mramAddr;         // 0x2C
    void* dest;             // 0x30
    struct ARAMEntry* next; // 0x34
} ARAMEntry;

typedef struct ARAMWork {
    u32 arStack[8];     // 0x0
    u32 nextAddr;       // 0x20
    u32 baseAddr;       // 0x24
    u32 size;           // 0x28
    ARAMEntry* entries; // 0x2C
    s32 count;          // 0x30
    ARAMEntry* head;    // 0x34
    ARAMEntry* tail;    // 0x38
    ARQRequest request; // 0x3C
    volatile s32 busy;  // 0x5C
    void* buffer;       // 0x60
    u32 bufferSize;     // 0x64
} ARAMWork;

void aramMgrInit(void);
ARAMEntry* aramMgrToAramAsync(void* src, u32 size);
ARAMEntry* aramMgrToAram(void* src, u32 size);
void aramMgrToMram(ARAMEntry* entry, void* dest);
