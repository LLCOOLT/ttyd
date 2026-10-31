#include <libc/string.h>

#include <dolphin/gx.h>
#include <dolphin/os.h>

#include "__gx.h"

static __GXFifoObj DisplayListFifo;
static volatile __GXFifoObj* OldCPUFifo;
static GXData __savedGXdata;

/**
 * Starts recording GX commands into the buffer list (size in bytes, 32 byte aligned) instead of the real FIFO:
 * saves the CPU FIFO (and the GX state if a context save is wanted) and points the CPU FIFO at the buffer.
 */
void GXBeginDisplayList(void* list, u32 size) {
    __GXFifoObj* CPUFifo = (__GXFifoObj*)GXGetCPUFifo();

    CHECK_GXBEGIN(137, "GXBeginDisplayList");
    ASSERTMSGLINE(138, !__GXData->inDispList, "GXBeginDisplayList: display list already in progress");
    ASSERTMSGLINE(139, (size & 0x1F) == 0, "GXBeginDisplayList: size is not 32 byte aligned");
    ASSERTMSGLINE(140, ((u32)list & 0x1F) == 0, "GXBeginDisplayList: list is not 32 byte aligned");

    if (__GXData->dirtyState != 0) {
        __GXSetDirtyState();
    }

    if (__GXData->dlSaveContext != 0) {
        memcpy(&__savedGXdata, __GXData, sizeof(__savedGXdata));
    }

    DisplayListFifo.base = (u8*)list;
    DisplayListFifo.top = (u8*)list + size - 4;
    DisplayListFifo.size = size;
    DisplayListFifo.count = 0;
    DisplayListFifo.rdPtr = list;
    DisplayListFifo.wrPtr = list;
    __GXData->inDispList = 1;
    GXSaveCPUFifo((GXFifoObj*)CPUFifo);
    OldCPUFifo = CPUFifo;
    GXSetCPUFifo((GXFifoObj*)&DisplayListFifo);
    GXResetWriteGatherPipe();
}

/**
 * Stops recording: restores the real CPU FIFO (and the saved GX state) and returns the number of bytes recorded,
 * or 0 if the buffer overflowed.
 */
u32 GXEndDisplayList(void) {
    u32 ov;
#ifdef DEBUG
    u32 reg;
#endif
    BOOL enabled;
    u32 cpenable;

    CHECK_GXBEGIN(195, "GXEndDisplayList");
    ASSERTMSGLINE(196, __GXData->inDispList == TRUE, "GXEndDisplayList: no display list in progress");
    GXFlush();
#ifdef DEBUG
    reg = GX_GET_PI_REG(5);
    ov = (reg >> 26) & 1;
#else
    ov = (GX_GET_PI_REG(5) >> 26) & 1;
#endif
    __GXSaveCPUFifoAux(&DisplayListFifo);
    ASSERTMSGLINE(213, !ov, "GXEndDisplayList: display list commands overflowed buffer");
    GXSetCPUFifo((GXFifoObj*)OldCPUFifo);

    if (__GXData->dlSaveContext != 0) {
        enabled = OSDisableInterrupts();
        cpenable = __GXData->cpEnable;
        memcpy(__GXData, &__savedGXdata, sizeof(*__GXData));
        __GXData->cpEnable = cpenable;
        OSRestoreInterrupts(enabled);
    }

    __GXData->inDispList = 0;
    if (!ov) {
        return DisplayListFifo.count;
    }

    return 0;
}

/**
 * Flushes any dirty state and then queues a command that makes the GPU run the display list at list for nbytes
 * bytes.
 */
void GXCallDisplayList(void* list, u32 nbytes) {
    CHECK_GXBEGIN(254, "GXCallDisplayList");
    ASSERTMSGLINE(255, !__GXData->inDispList, "GXCallDisplayList: display list already in progress");
    ASSERTMSGLINE(256, (nbytes & 0x1F) == 0, "GXCallDisplayList: nbytes is not 32 byte aligned");
    ASSERTMSGLINE(257, ((u32)list & 0x1F) == 0, "GXCallDisplayList: list is not 32 byte aligned");

    if (__GXData->dirtyState != 0) {
        __GXSetDirtyState();
    }

#if DEBUG
    __GXShadowDispList(list, nbytes);
#endif

    if (*(u32*)&__GXData->vNumNot == 0) {  // checks both vNum and bpSent
        __GXSendFlushPrim();
    }

    GX_WRITE_U8(GX_CMD_CALL_DL);
    GX_WRITE_U32(list);
    GX_WRITE_U32(nbytes);
}
