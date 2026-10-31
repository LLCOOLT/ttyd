#include <dolphin/dsp.h>

#include "__dsp.h"

/** Debug print that does nothing in this build. */
void __DSP_debug_printf(const char* fmt, ...) {}

/** Returns the task the DSP is currently running (or the head of the queue when idle). */
DSPTaskInfo* __DSPGetCurrentTask(void) {
    return __DSP_curr_task;
}
