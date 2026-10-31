#include <dolphin.h>
#include <dolphin/os.h>

#include "__os.h"
#include "__dvd.h"

typedef struct {
    OSAlarm* head;
    OSAlarm* tail;
} OSAlarmQueue;

// prototypes
static void SetTimer(OSAlarm * alarm);
static void InsertAlarm(OSAlarm* alarm, OSTime fire, OSAlarmHandler handler);
static void DecrementerExceptionCallback(register __OSException exception, register OSContext* context);
static void DecrementerExceptionHandler(__OSException exception, OSContext* context);
static BOOL OnReset(BOOL final);

/** Registers OnReset (priority 0xFFFFFFFF) with the OS so pending alarms are cancelled before a reset. */
static OSResetFunctionInfo ResetFunctionInfo = {OnReset, 0xFFFFFFFF, NULL, NULL};
static OSAlarmQueue AlarmQueue;

#define ASSERTREPORT(line, cond) \
    if (!(cond)) { OSReport("OSCheckAlarmQueue: Failed " #cond " in %d", line); return 0; }

/**
 * Debug sanity check of the alarm queue's head, tail and prev/next links;
 * prints the failed condition and returns FALSE when the list is corrupt.
 */
BOOL OSCheckAlarmQueue(void) {
    OSAlarm* alarm;

    ASSERTREPORT(146, AlarmQueue.head == NULL && AlarmQueue.tail == NULL || AlarmQueue.head != NULL && AlarmQueue.tail != NULL);
    ASSERTREPORT(147, AlarmQueue.head == NULL || AlarmQueue.head->prev == NULL);
    ASSERTREPORT(148, AlarmQueue.tail == NULL || AlarmQueue.tail->next == NULL);

    for(alarm = AlarmQueue.head; alarm; alarm = alarm->next) {
        ASSERTREPORT(151, alarm->next == NULL || alarm->next->prev == alarm);
        ASSERTREPORT(152, alarm->next != NULL || AlarmQueue.tail == alarm);
    }
    return TRUE;
}

/**
 * Programs the decrementer for an alarm: 0 if it is already due, the remaining ticks if they fit in 31 bits,
 * otherwise 0x7FFFFFFF.
 */
static void SetTimer(OSAlarm* alarm) {
    OSTime delta = alarm->fire - __OSGetSystemTime();

    if (delta < 0) {
        PPCMtdec(0);
    } else if (delta < 0x80000000) {
        PPCMtdec((u32)delta);
    } else {
        PPCMtdec(0x7fffffff);
    }
}

/**
 * Installs the decrementer exception handler (exception 8),
 * empties the alarm queue and registers the reset callback; does nothing if already installed.
 * Called from OSInit.
 */
void OSInitAlarm(void) {
    if (__OSGetExceptionHandler(8) != DecrementerExceptionHandler) {
        AlarmQueue.head = AlarmQueue.tail = NULL;
        __OSSetExceptionHandler(8, DecrementerExceptionHandler);
        OSRegisterResetFunction(&ResetFunctionInfo);
    }
}

/** Readies an OSAlarm for use by clearing its handler and tag; it does not start it. */
void OSCreateAlarm(OSAlarm* alarm) {
    alarm->handler = 0;
    alarm->tag = 0;
}

/**
 * Puts an alarm in the fire-time-ordered queue with its handler.
 * For a periodic alarm it first computes the next fire time on the start-plus-n-periods grid.
 * Reprograms the timer when the alarm became the earliest.
 */
static void InsertAlarm(OSAlarm* alarm, OSTime fire, OSAlarmHandler handler) {
    OSAlarm* next;
    OSAlarm* prev;
    
    if (0 < alarm->period) {
        OSTime time = __OSGetSystemTime();
        
        fire = alarm->start;
        if (alarm->start < time) {
            fire += alarm->period * ((time - alarm->start) / alarm->period + 1);
        }
    }
    
    ASSERTLINE(251, alarm->handler == 0);
    
    alarm->handler = handler;
    alarm->fire = fire;
    
    for (next = AlarmQueue.head; next; next = next->next) {
        if (next->fire <= fire) {
            continue;
        }
        
        alarm->prev = next->prev;
        next->prev = alarm;
        alarm->next = next;
        prev = alarm->prev;

        if (prev) {
            prev->next = alarm;
        } else {
            AlarmQueue.head = alarm;
            SetTimer(alarm);
        }

        return;
    }

    ASSERTLINE(280, next == 0);

    alarm->next = 0;
    prev = AlarmQueue.tail;
    AlarmQueue.tail = alarm;
    alarm->prev = prev;

    if (prev) {
        prev->next = alarm;
    } else {
        AlarmQueue.head = AlarmQueue.tail = alarm;
        SetTimer(alarm);
    }
}

/** Starts a one-shot alarm that calls its handler once, tick time-base ticks from now. */
void OSSetAlarm(OSAlarm* alarm, OSTime tick, OSAlarmHandler handler) {
    BOOL enabled;
    ASSERTMSGLINE(313, tick > 0, "OSSetAlarm(): tick was less than zero.");
    ASSERTMSGLINE(314, handler, "OSSetAlarm(): null handler was specified.");
    enabled = OSDisableInterrupts();
    alarm->period = 0;
    InsertAlarm(alarm, __OSGetSystemTime() + tick, handler);
    ASSERTLINE(321, OSCheckAlarmQueue());
    OSRestoreInterrupts(enabled);
}

/** Starts a one-shot alarm that fires at an absolute time-base value. */
void OSSetAbsAlarm(OSAlarm* alarm, OSTime time, OSAlarmHandler handler) {
    BOOL enabled;

    ASSERTMSGLINE(343, handler, "OSSetAbsAlarm(): null handler was specified.");
    enabled = OSDisableInterrupts();
    alarm->period = 0;
    InsertAlarm(alarm, __OSTimeToSystemTime(time), handler);
    ASSERTLINE(350, OSCheckAlarmQueue());
    OSRestoreInterrupts(enabled);
}

/** Starts an alarm that first fires at the absolute time start and then every period ticks. */
void OSSetPeriodicAlarm(OSAlarm* alarm, OSTime start, OSTime period, OSAlarmHandler handler) {
    BOOL enabled;
    ASSERTMSGLINE(374, period > 0, "OSSetPeriodicAlarm(): period was less than zero.");
    ASSERTMSGLINE(375, handler, "OSSetPeriodicAlarm(): null handler was specified.");
    enabled = OSDisableInterrupts();
    alarm->period = period;
    alarm->start = __OSTimeToSystemTime(start);
    InsertAlarm(alarm, 0, handler);
    ASSERTLINE(383, OSCheckAlarmQueue());
    OSRestoreInterrupts(enabled);
}

/**
 * Removes a pending alarm from the queue (reprogramming the timer if it was first) so its handler will not run;
 * harmless if it is not queued.
 */
void OSCancelAlarm(OSAlarm* alarm) {
    OSAlarm* next;
    BOOL enabled;

    enabled = OSDisableInterrupts();

    if (alarm->handler == 0) {
        OSRestoreInterrupts(enabled);
        return;
    }

    next = alarm->next;
    if (next == 0) {
        AlarmQueue.tail = alarm->prev;
    } else {
        next->prev = alarm->prev;
    }
    if (alarm->prev) {
        alarm->prev->next = next;
    } else {
        AlarmQueue.head = next;
        if (next) {
            SetTimer(next);
        }
    }
    alarm->handler = 0;
    ASSERTLINE(434, OSCheckAlarmQueue());
    OSRestoreInterrupts(enabled);
}

/**
 * Decrementer exception body: pops the alarm at the head of the queue
 * if it is due (otherwise just re-arms the timer), re-queues it if periodic,
 * re-arms the timer for the next alarm, then runs the alarm handler inside a scratch OS context with the
 * scheduler disabled and reschedules before returning to the interrupted context.
 */
static void DecrementerExceptionCallback(register __OSException exception,
                                         register OSContext* context) {
    OSAlarm* alarm;
    OSAlarm* next;
    OSAlarmHandler handler;
    OSTime time;
    OSContext exceptionContext;

    time = __OSGetSystemTime();
    alarm = AlarmQueue.head;
    if (alarm == 0) {
        OSLoadContext(context);
    }

    if (time < alarm->fire) {
        SetTimer(alarm);
        OSLoadContext(context);
    }

    next = alarm->next;
    AlarmQueue.head = next;
    if (next == 0) {
        AlarmQueue.tail = 0;
    } else {
        next->prev = 0;
    }

    ASSERTLINE(492, OSCheckAlarmQueue());

    handler = alarm->handler;
    alarm->handler = 0;
    if (0 < alarm->period) {
        InsertAlarm(alarm, 0, handler);
        ASSERTLINE(502, OSCheckAlarmQueue());
    }

    if (AlarmQueue.head) {
        SetTimer(AlarmQueue.head);
    }

    OSDisableScheduler();
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    handler(alarm, context);
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
    OSEnableScheduler();
    __OSReschedule();
    OSLoadContext(context);
}

#ifdef __GEKKO__
/**
 * Assembly entry installed for the decrementer exception:
 * saves the GPRs into the interrupted context, then branches to DecrementerExceptionCallback.
 */
static asm void DecrementerExceptionHandler(register __OSException exception,
                                            register OSContext* context) {
    nofralloc 
    OS_EXCEPTION_SAVE_GPRS(context)
    stwu r1, -8(r1)
    b DecrementerExceptionCallback
}
#endif

/** Sets a nonzero tag on an alarm so a group of alarms can be cancelled with OSCancelAlarms. */
void OSSetAlarmTag(OSAlarm* alarm, u32 tag) {
    alarm->tag = tag;
}

/** Cancels every queued alarm that carries the given nonzero tag. */
void OSCancelAlarms(u32 tag) {
    BOOL enabled;
    OSAlarm* alarm;
    OSAlarm* next;

    ASSERTMSGLINE(569, tag != 0, "OSCancelAlarms(): invalid tag. (tag zero is used by the operating system.)");

    if (tag != 0) {
        enabled = OSDisableInterrupts();
        ASSERTLINE(575, OSCheckAlarmQueue());

        alarm = AlarmQueue.head;
        next = (alarm) ? alarm->next : NULL;

        while (alarm != 0) {
            if (alarm->tag == tag) {
                OSCancelAlarm(alarm);
            }

            alarm = next;
            next = (alarm) ? alarm->next : NULL;
        }

        ASSERTLINE(585, OSCheckAlarmQueue());
        OSRestoreInterrupts(enabled);
    }
}

/** Reset callback: on the final pass it cancels every queued alarm except the DVD driver's own. */
static BOOL OnReset(BOOL final) {
    OSAlarm* alarm;
    OSAlarm* next;

    if (final != FALSE) {
        ASSERTLINE(606, OSCheckAlarmQueue());

        alarm = AlarmQueue.head;
        next = (alarm) ? alarm->next : NULL;

        while (alarm != 0) {
            if (__DVDTestAlarm(alarm) == FALSE) {
                OSCancelAlarm(alarm);
            }

            alarm = next;
            next = (alarm) ? alarm->next : NULL;
        }

        ASSERTLINE(616, OSCheckAlarmQueue());
    }

    return TRUE;
}
