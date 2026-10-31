#include <dolphin.h>
#include <dolphin/gx.h>
#include <demo.h>
#include "fake_tgmath.h"

static s16 __AVX_internal_buffer[3200] ATTRIBUTE_ALIGN(32);

static void (*__AVX_save_isr)(void);

static u32 __AVX_num_frames;
static u32 __AVX_num_filled;
static u32 __AVX_curr_frame;

static u16* __AVX_buffer;
static s16* __AVX_left_buffer;
static s16* __AVX_right_buffer;
static u32 __AVX_write_ptr = 0;
static u32 __AVX_buffer_size = 0;

static BOOL flag = FALSE;

/**
 * Audio interface DMA callback installed by DEMOAVXAttach.
 * Runs the previously registered callback first,
 * then copies the 640 bytes (160 stereo 16-bit samples) of the buffer the AI DMA just started into the next
 * frame slot of the capture ring and advances the ring. Sets 'flag' once the ring has passed its fifth frame.
 */
static void __DEMOAVX_isr(void) {
    u32 frame_address;

    if (__AVX_save_isr) {
        (*__AVX_save_isr)();

        frame_address = 0x80000000 | AIGetDMAStartAddr();
        ASSERTMSGLINE(83, frame_address, "AVX: frame address is NULL!\n");

        DCInvalidateRange((void*)frame_address, 640);
        memcpy((void *)&__AVX_buffer[__AVX_curr_frame * 320], (void*)frame_address, 640);
        DCFlushRange((void*)&__AVX_buffer[__AVX_curr_frame * 320], 640);

        __AVX_curr_frame = (__AVX_curr_frame + 1) % __AVX_num_frames;
        __AVX_num_filled = (__AVX_num_filled + 1) % 10;
        if (__AVX_curr_frame > 4) {
            flag = TRUE;
        }
    }
}

/**
 * Returns how many frames the interrupt has captured since the last call (counted modulo 10)
 * and resets the count, with interrupts disabled.
 */
u32 DEMOAVXGetNumFilled(void) {
    u32 tmp;
    BOOL old;

    old = OSDisableInterrupts();

    tmp = __AVX_num_filled;
    __AVX_num_filled = 0;

    OSRestoreInterrupts(old);
    return tmp;
}

/** Returns the capture ring's current write frame index. */
u32 DEMOAVXGetFrameCounter(void) {
    return __AVX_curr_frame;
}

/**
 * Moves the newly captured frames out of the ring into the caller's left and right sample buffers,
 * splitting the interleaved stereo samples.
 * Reports the first and last positions written in the left/right buffers through 'start_index'
 * and 'end_index' (wrapping at the buffer size) and returns the number of samples per channel (160 per frame);
 * 0 if nothing is ready yet.
 */
u32 DEMOAVXRefreshBuffer(u32* start_index, u32* end_index) {
    u32 num_filled;
    u32 curr_frame;
    u32 i;
    u32 j;

    if (flag) {
        num_filled = DEMOAVXGetNumFilled();
        curr_frame = (__AVX_num_frames + DEMOAVXGetFrameCounter() - num_filled) % __AVX_num_frames;

        *start_index = __AVX_write_ptr;

        for (i = 0; i < num_filled; i++) {
            DCInvalidateRange((void*)&__AVX_buffer[curr_frame * 320], 640);

            for (j = 0; j < 320; j += 2) {
                __AVX_left_buffer [__AVX_write_ptr] = __AVX_buffer[curr_frame * 320 + j];
                __AVX_right_buffer[__AVX_write_ptr] = __AVX_buffer[curr_frame * 320 + j + 1];
                __AVX_write_ptr = (__AVX_write_ptr + 1) % __AVX_buffer_size;
            }

            curr_frame = (curr_frame + 1) % __AVX_num_frames;
        }

        *end_index = __AVX_write_ptr;
        return num_filled * 160;
    }

    return 0;
}

/**
 * Starts audio capture into the given left and right buffers (size samples each) using the library's own
 * 10-frame ring.
 */
void DEMOAVXInit(s16* left, s16* right, u32 size) {
    __AVX_left_buffer  = left;
    __AVX_right_buffer = right;
    __AVX_write_ptr = 0;
    __AVX_buffer_size = size;

    DEMOAVXAttach(__AVX_internal_buffer, 10);
}

/**
 * Clears a ring of 'num_frames' frames (320 halfwords each) and hooks __DEMOAVX_isr onto the AI DMA callback,
 * saving the old callback so it still runs.
 */
void DEMOAVXAttach(void* buffer, u32 num_frames) {
    BOOL old;
    u32 i;

    __AVX_buffer = (u16*)buffer;
    __AVX_num_frames = num_frames;
    __AVX_num_filled = 0;
    __AVX_curr_frame = 0;
    
    for (i = 0; i < num_frames * 320; i++) {
        __AVX_buffer[i] = 0;
    }

    DCFlushRange(__AVX_buffer, num_frames * 320);

    old = OSDisableInterrupts();
    __AVX_save_isr = AIRegisterDMACallback(__DEMOAVX_isr);
    OSRestoreInterrupts(old);
}
