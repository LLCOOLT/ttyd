#include <dolphin.h>
#include <dolphin/os.h>

/** Sets a stopwatch's name and clears its total, hit count and maximum; the minimum starts at 0xFFFFFFFF ticks. */
void OSInitStopwatch(OSStopwatch* sw, char* name) {
    sw->name = name;
    sw->total = 0;
    sw->hits = 0;
    sw->min = 0x00000000FFFFFFFF;
    sw->max = 0;
}

/** Starts timing a run: marks the stopwatch running and records the current OS time. */
void OSStartStopwatch(OSStopwatch* sw) {
    sw->running = TRUE;
    sw->last = OSGetTime();
}

/** If running, ends the run: adds it to the total, counts a hit, and updates the minimum and maximum run lengths. */
void OSStopStopwatch(OSStopwatch* sw) {
    OSTime interval;

    if (sw->running) {
        interval = OSGetTime() - sw->last;
        sw->total += interval;
        sw->running = FALSE;
        sw->hits++;
        if (sw->max < interval) {
            sw->max = interval;
        }
        if (interval < sw->min) {
            sw->min = interval;
        }
    }
}

/** Returns the total ticks so far including the run in progress, without stopping it. */
OSTime OSCheckStopwatch(OSStopwatch* sw) {
    OSTime currTotal;

    currTotal = sw->total;
    if (sw->running) {
        currTotal += OSGetTime() - sw->last;
    }
    return currTotal;
}

/** Clears the stopwatch's counters by re-initialising it with its own name. */
void OSResetStopwatch(OSStopwatch* sw) {
    OSInitStopwatch(sw, sw->name);
}

/**
 * Prints the stopwatch's name, total, hit count, minimum,
 * maximum and mean (total divided by hits) through OSReport, times in microseconds.
 */
void OSDumpStopwatch(OSStopwatch* sw) {
    OSReport("Stopwatch [%s]	:\n", sw->name);
    OSReport("\tTotal= %lld us\n",    OSTicksToMicroseconds(sw->total));
    OSReport("\tHits = %d \n",        sw->hits);
    OSReport("\tMin  = %lld us\n",    OSTicksToMicroseconds(sw->min));
    OSReport("\tMax  = %lld us\n",    OSTicksToMicroseconds(sw->max));
    OSReport("\tMean = %lld us\n",    OSTicksToMicroseconds(sw->total/sw->hits));
}
