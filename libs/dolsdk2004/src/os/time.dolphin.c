#include <dolphin.h>
#include <dolphin/os.h>

#include "__os.h"

/** Returns the system time in time-base ticks (__OSGetSystemTime); hook for the MSL C library's clock(). */
OSTime __get_clock(void) {
    return __OSGetSystemTime();
}

/**
 * Returns the current time in seconds, from the time base, minus the constant 0x43E83E00;
 * hook for the MSL C library's time().
 */
u32 __get_time(void) {
    return OSTicksToSeconds(OSGetTime()) - 0x43E83E00;
}

/** MSL hook for converting local time to GMT; returns 0 because the console keeps no time-zone offset. */
int __to_gm_time(void) {
    return 0;
}
