// filemgr.c: the file manager (FileEntry, FileManagerWork): loads files into the smart heap and caches them by name.
#pragma once

#include "manager/dvdmgr.h"
#include <dolphin/types.h>

typedef struct FileEntry FileEntry;

typedef void (*FileCallback)(FileEntry* file);

struct FileEntry {
    u8 state;               // 0x0
    s8 type;                // 0x1, fileAlloc(name, type); passed to fileGarbageDataAdrSet
    s16 references;         // 0x2
    void* dataSlot;         // 0x4, data points here unless the data is in a smart block
    u8 pad_8[0x20 - 0x8];   // 0x8
    char filename[64];      // 0x20
    u8 pad_60[0xA0 - 0x60]; // 0x60
    void** data;            // 0xA0
    FileEntry* next;        // 0xA4
    FileCallback callback;  // 0xA8
    DVDEntry* entry;        // 0xAC
};

typedef struct FileManagerWork {
    FileEntry* entries;        // 0x0
    s32 archiveType;           // 0x4
    FileEntry* firstused;      // 0x8
    FileEntry* lastused;       // 0xC
    FileEntry* firstavailable; // 0x10
    FileEntry* lastavailable;  // 0x14
} FileManagerWork;

void fileInit(void);
void fileGarbageMoveMem(void* data, FileEntry* file);
void _fileGarbage(BOOL mode);
FileEntry* fileAllocf(s32 type, const char* format, ...);
FileEntry* fileAlloc(const char* filename, s32 type);
void fileFree(FileEntry* handle);
// fileAsync/fileAsyncf start an asynchronous read and return the file once it is loaded, NULL while the read
// is pending, or FILE_ASYNC_MISSING when the file does not exist
#define FILE_ASYNC_MISSING ((FileEntry*)-1)
// The game tests the -1 as a signed word (cmpwi), so callers use this rather than comparing pointers.
static inline BOOL fileAsyncMissing(FileEntry* file) {
    return (s32)file == -1;
}
FileEntry* fileAsyncf(s32 type, FileCallback callback, const char* format, ...);
FileEntry* fileAsync(const char* filename, s32 type, FileCallback callback);
void fileSetCurrentArchiveType(s32 type);
