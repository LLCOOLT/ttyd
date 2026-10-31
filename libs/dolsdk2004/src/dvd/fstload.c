#include <dolphin.h>
#include <dolphin/os.h>
#include <dolphin/dvd.h>

#include "__dvd.h"

static u8 bb2Buf[OSRoundUp32B(sizeof(DVDBB2)) + 31];

static u32 status;
static DVDBB2* bb2;
static DVDDiskID* idTmp;

// prototypes
static void cb(s32 result, DVDCommandBlock* block);

/**
 * DVD callback that chains the boot reads.
 * After the disc ID read it reads the 32-byte DVDBB2 block at disc offset 0x420;
 * after that it reads the FST to the address and offset that block gives.
 * On result -4 it resets the drive and restarts from the disc ID read.
 */
static void cb(s32 result, DVDCommandBlock* block) {
    if (result > 0) {
        switch(status) {
        case 0:
            status = 1;
            DVDReadAbsAsyncForBS(block, bb2, 0x20, 0x420, cb);
            return;
        case 1:
            status = 2;
            DVDReadAbsAsyncForBS(block, bb2->FSTAddress, (bb2->FSTLength + 0x1F) & 0xFFFFFFE0, bb2->FSTPosition, cb);
        default:
            return;
        }
    }

    if (result == -1) {
        return;
    } else if (result == -4) {
        status = 0;
        DVDReset();
        DVDReadDiskID(block, idTmp, cb);
    }
}

/**
 * Boot-time loader: reads the disc ID, the DVDBB2 block and then the FST into memory through cb,
 * polling until the drive is idle.
 * It then records the FST address and maximum size and the disc ID in the OS boot info, prints the game name,
 * company, disc number, version and streaming flag, and lowers the top of the arena to the FST address.
 */
void __fstLoad(void) {
    OSBootInfo* bootInfo;
    DVDDiskID* id;
    u8 idTmpBuf[63];
    s32 state;
    void* arenaHi;
    static DVDCommandBlock block;

    arenaHi = OSGetArenaHi();
    bootInfo = (void*)OSPhysicalToCached(0);
    idTmp = (void*)OSRoundUp32B(idTmpBuf);
    bb2 = (void*)OSRoundUp32B(bb2Buf);

    DVDReset();
    DVDReadDiskID(&block, idTmp, cb);

    while (1) {
        state = DVDGetDriveStatus();
        if (state == 0) {
            break;
        }

        // weird switch that seemingly wont do anything but break out of its own switch. What was this for? Early DVD development pre-hardware?
        switch(state) {
        case DVD_STATE_FATAL_ERROR: break;
        case DVD_STATE_BUSY: break;
        case DVD_STATE_WAITING: break;
        case DVD_STATE_COVER_CLOSED: break;
        case DVD_STATE_NO_DISK: break;
        case DVD_STATE_COVER_OPEN: break;
        case DVD_STATE_MOTOR_STOPPED: break;
        }
    }

    bootInfo->FSTLocation = (void*)bb2->FSTAddress;
    bootInfo->FSTMaxLength = bb2->FSTMaxLength;
    id = &bootInfo->DVDDiskID;
    memcpy(id, idTmp, 0x20);
    OSReport("\n");
    OSReport("  Game Name ... %c%c%c%c\n", id->gameName[0], id->gameName[1], id->gameName[2], id->gameName[3]);
    OSReport("  Company ..... %c%c\n", id->company[0], id->company[1]);
    OSReport("  Disk # ...... %d\n", id->diskNumber);
    OSReport("  Game ver .... %d\n", id->gameVersion);
    OSReport("  Streaming ... %s\n", !(id->streaming) ? "OFF" : "ON");
    OSReport("\n");
    OSSetArenaHi(bb2->FSTAddress);
}
