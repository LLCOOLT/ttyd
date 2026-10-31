#include <dolphin.h>
#include <dolphin/ax.h>

#include "__ax.h"

static u16 __AXCommandList[2][384];

static u32 __AXCommandListPosition;
static u16* __AXClWrite;
static u32 __AXCommandListCycles;
static u32 __AXCompressor;
u32 __AXClMode;

/** Returns the DSP cycle estimate accumulated while the current command list was built. */
u32 __AXGetCommandListCycles(void) {
    return __AXCommandListCycles;
}

/**
 * Returns the address of the command list built last frame (for the DSP to run now)
 * and switches to the other of the two command list buffers for writing the next one.
 */
u32 __AXGetCommandListAddress(void) {
    u32 address;

    address = (u32)&__AXCommandList[__AXCommandListPosition][0];
    __AXCommandListPosition += 1;
    __AXCommandListPosition &= 1;
    __AXClWrite = (void*)&__AXCommandList[__AXCommandListPosition][0];
    return address;
}

/** Appends one 16-bit word to the command list being built. */
void __AXWriteToCommandList(u16 data) {
    *__AXClWrite = data;
    __AXClWrite++;
}

/**
 * Builds the DSP command list for the next audio frame:
 * the studio block address, the output mix command for the current mode (mode 0 and 1 write a mix to the
 * surround buffer, mode 2 is Dolby Pro Logic II), the voice parameter block address,
 * commands for each active auxiliary bus (buffers, in Pro Logic II mode the four-channel variants),
 * the compressor if enabled, and the final output command with the surround and stereo buffers.
 * It tracks an estimate of the DSP cycles used and flushes the list to memory.
 */
void __AXNextFrame(void* sbuffer, void* buffer) {
    u32 data;
    u16* pCommandList;

    __AXCommandListCycles = 0x1A9;
    pCommandList = __AXClWrite;
    data = __AXGetStudio();
    __AXWriteToCommandList(0);
    __AXWriteToCommandList((u16)(data >> 0x10));
    __AXWriteToCommandList((u16)(data));
    __AXCommandListCycles += 0x2E44;

    switch (__AXClMode) {
    case 0:
        __AXWriteToCommandList(7);
        __AXWriteToCommandList((u16)((u32)sbuffer >> 0x10));
        __AXWriteToCommandList((u32)sbuffer);
        __AXCommandListCycles += 0x546;
        break;
    case 1:
        __AXWriteToCommandList(0x11);
        __AXWriteToCommandList((u16)((u32)sbuffer >> 0x10));
        __AXWriteToCommandList((u32)sbuffer);
        __AXCommandListCycles += 0x5E6;
        break;
    case 2:
        break;
    default:
        ASSERTMSGLINE(193, 0, "Unknown AX mode!");
    }

    data = (u32)__AXGetPBs();
    __AXWriteToCommandList(2);
    __AXWriteToCommandList((u16)(data >> 0x10));
    __AXWriteToCommandList((u16)data);
    __AXWriteToCommandList(3);

    if (__AXClMode == 2) {
        __AXGetAuxAInput(&data);
        if (data != 0) {
            __AXWriteToCommandList(0x13);
            __AXWriteToCommandList(data >> 0x10);
            __AXWriteToCommandList((u16)data);
            __AXGetAuxAInputDpl2(&data);
            __AXWriteToCommandList(data >> 0x10);
            __AXWriteToCommandList((u16)data);
            __AXGetAuxAOutput(&data);
            __AXWriteToCommandList(data >> 0x10);
            __AXWriteToCommandList((u16)data);
            __AXGetAuxAOutputDpl2R(&data);
            __AXWriteToCommandList(data >> 0x10);
            __AXWriteToCommandList((u16)data);
            __AXGetAuxAOutputDpl2Ls(&data);
            __AXWriteToCommandList(data >> 0x10);
            __AXWriteToCommandList((u16)data);
            __AXGetAuxAOutputDpl2Rs(&data);
            __AXWriteToCommandList(data >> 0x10);
            __AXWriteToCommandList((u16)data);
            __AXCommandListCycles += 0xDED;
        }
        __AXWriteToCommandList(0x10);
        __AXGetAuxBForDPL2(&data);
        __AXWriteToCommandList(data >> 0x10);
        __AXWriteToCommandList((u16)data);
        __AXGetAuxBOutputDPL2(&data);
        __AXWriteToCommandList(data >> 0x10);
        __AXWriteToCommandList((u16)data);
        __AXCommandListCycles += 0xDED;
    } else {
        __AXGetAuxAInput(&data);

        if (data != 0) {
            __AXWriteToCommandList(4);
            __AXWriteToCommandList((u16)(data >> 0x10));
            __AXWriteToCommandList((u16)data);
            __AXGetAuxAOutput(&data);
            __AXWriteToCommandList((u16)(data >> 0x10));
            __AXWriteToCommandList((u16)data);
            __AXCommandListCycles += 0xDED;
        }

        __AXGetAuxBInput(&data);
        if (data != 0) {
            __AXWriteToCommandList(5);
            __AXCommandListCycles += 0xDED;
            __AXWriteToCommandList((u16)(data >> 0x10));
            __AXWriteToCommandList((u16)data);
            __AXGetAuxBOutput(&data);
            __AXWriteToCommandList((u16)(data >> 0x10));
            __AXWriteToCommandList((u16)data);
        }
    }

    if (__AXCompressor) {
        __AXWriteToCommandList(0x12);
        __AXWriteToCommandList(0x8000);
        __AXWriteToCommandList(0xA);
        __AXWriteToCommandList((u32)__AXCompressorTable >> 0x10);
        __AXWriteToCommandList((u32)__AXCompressorTable);
        __AXCommandListCycles += 0xBB8;
    }
    
    __AXWriteToCommandList(0xE);
    __AXWriteToCommandList((u16)((u32)sbuffer >> 0x10));
    __AXWriteToCommandList((u32)sbuffer);
    __AXWriteToCommandList((u16)((u32)buffer >> 0x10));
    __AXWriteToCommandList((u32)buffer);
    __AXCommandListCycles += 0x2710;
    __AXWriteToCommandList(0xF);
    __AXCommandListCycles += 2;
    DCFlushRange(pCommandList, 0x300);
}

/** Initialises the command list module: output mode 0, first buffer, compressor on. */
void __AXClInit(void) {
#ifdef DEBUG
    OSReport("Initializing AXCL code module\n");
#endif
    ASSERTLINE(338, ((u32)&__AXCommandList[0][0] & 0x1F) == 0);
    ASSERTLINE(339, ((u32)&__AXCommandList[1][0] & 0x1F) == 0);
    __AXClMode = 0;
    __AXCommandListPosition = 0;
    __AXClWrite = (void*)&__AXCommandList;
    __AXCompressor = 1;
}

/** Shutdown hook of the command list module; only logs in debug builds. */
void __AXClQuit(void) {
#ifdef DEBUG
    OSReport("Shutting down AXCL code module\n");
#endif
}

/** Selects the output mode used when building command lists (0 stereo, 1 surround, 2 Dolby Pro Logic II). */
void AXSetMode(u32 mode) {
    if (__AXClMode != mode) {
        __AXClMode = mode;
    }
}

/** Returns the current output mode. */
u32 AXGetMode(void) {
    return __AXClMode;
}

/** Turns the output compressor on (nonzero) or off. */
void AXSetCompressor(u32 i) {
    __AXCompressor = i;
}
