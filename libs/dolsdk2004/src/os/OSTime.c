#include <dolphin/exi.h>
#include <dolphin/os.h>

#include "__os.h"

// End of each month in standard year
static int YearDays[MONTH_MAX] = {0,   31,  59,  90,  120, 151,
                                  181, 212, 243, 273, 304, 334};
// End of each month in leap year
static int LeapYearDays[MONTH_MAX] = {0,   31,  60,  91,  121, 152,
                                      182, 213, 244, 274, 305, 335};

#ifdef __GEKKO__
/**
 * Assembly: reads the 64-bit CPU time base (TBU:TBL), which ticks at one quarter of the bus clock,
 * rereading TBU until it does not change so a carry from TBL cannot corrupt the value.
 */
asm OSTime OSGetTime(void) {
jump:
    nofralloc

    mftbu r3
    mftb r4

    // Check for possible carry from TBL to TBU
    mftbu r5
    cmpw r3, r5
    bne jump

    blr
}

/** Assembly: reads only the low 32 bits of the time base (TBL). */
asm OSTick OSGetTick(void){
    nofralloc

    mftb r3
    blr
}

/** Assembly: writes the 64-bit time base (TBL is zeroed first so a carry cannot disturb TBU). */
asm static void __SetTime(OSTime time) {
    nofralloc
    li r5, 0
    mttbl r5
    mttbu r3
    mttbl r4
    blr
}
#endif

/**
 * Sets the time base to time.
 * The difference from the old value is added to the system-time offset so __OSGetSystemTime stays continuous,
 * and the EXI probe state is reset.
 */
void __OSSetTime(OSTime time) {
    BOOL enabled;
    OSTime * timeAdjustAddr;

    timeAdjustAddr = __OSSystemTime;
    enabled = OSDisableInterrupts();

    *timeAdjustAddr += OSGetTime() - time;
    __SetTime(time);
    EXIProbeReset();
    OSRestoreInterrupts(enabled);
}

/**
 * Returns OSGetTime plus the system-time offset kept in low memory, read with interrupts disabled.
 * Used by the OS for alarms and timeouts.
 */
OSTime __OSGetSystemTime() {
    BOOL enabled;
    OSTime* timeAdjustAddr;
    OSTime result;

    timeAdjustAddr = __OSSystemTime;
    enabled = OSDisableInterrupts();

    result = OSGetTime() + *timeAdjustAddr;
    OSRestoreInterrupts(enabled);
    return result;
}

/** Converts a raw time-base value to system time by adding the stored offset. */
OSTime __OSTimeToSystemTime(OSTime time) {
    BOOL enabled;
    OSTime* timeAdjustAddr = __OSSystemTime;
    OSTime result;

    enabled = OSDisableInterrupts();
    result = *timeAdjustAddr + time;
    OSRestoreInterrupts(enabled);
    return result;
}

#ifdef __GEKKO__
/** Assembly: writes the low time-base register (TBL). */
asm void __OSSetTick(register OSTick newTicks) {
    nofralloc
    mttbl newTicks
    blr
}
#endif

/** Returns nonzero when year is a leap year in the Gregorian calendar. */
static int IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * Returns the number of days from the start of the year up to the start of month mon (0 based),
 * allowing for leap years.
 */
static int GetYearDays(int year, int mon) {
    int* md = (IsLeapYear(year)) ? LeapYearDays : YearDays;

    return md[mon];
}

/** Returns the number of leap days that have occurred before the given year, used to turn years into a day count. */
static int GetLeapDays(int year) {
    ASSERTLINE(286, 0 <= year);
    
    if (year < 1) {
        return 0;
    }
    return (year + 3) / 4 - (year - 1) / 100 + (year - 1) / 400;
}

/** Turns a day count since year 0 into year, month, day of month, day of year and weekday in td. */
static void GetDates(int days, OSCalendarTime* td) {
    int year;
    int n;
    int month;
    int * md;

    ASSERTLINE(311, 0 <= days);

    td->wday = (days + 6) % WEEK_DAY_MAX;

    for (year = days / YEAR_DAY_MAX;
         days < (n = year * YEAR_DAY_MAX + GetLeapDays(year)); year--) {
        ;
    }

    days -= n;
    td->year = year;
    td->yday = days;

    md = IsLeapYear(year) ? LeapYearDays : YearDays;
    for (month = MONTH_MAX; days < md[--month];) {
        ;
    }
    td->mon = month;
    td->mday = days - md[month] + 1;
}

/**
 * Converts time-base ticks (counted from the year 2000) into a calendar date and time (year, month, day, hour,
 * minute, second, millisecond, microsecond) in td.
 */
void OSTicksToCalendarTime(OSTime ticks, OSCalendarTime* td) {
    int days;
    int secs;
    OSTime d;

    d = ticks % OS_SEC_TO_TICKS(1);    
    if (d < 0) {
        d += OS_SEC_TO_TICKS(1);
        ASSERTLINE(356, 0 <= d);
    }

    td->usec = OS_TICKS_TO_USEC(d) % USEC_MAX;
    td->msec = OS_TICKS_TO_MSEC(d) % MSEC_MAX;

    ASSERTLINE(360, 0 <= td->usec);
    ASSERTLINE(361, 0 <= td->msec);

    ticks -= d;

    ASSERTLINE(364, ticks % OSSecondsToTicks(1) == 0);
    ASSERTLINE(368, 0 <= OSTicksToSeconds(ticks) / 86400 + BIAS && OSTicksToSeconds(ticks) / 86400 + BIAS <= INT_MAX);

    days = (OS_TICKS_TO_SEC(ticks) / SECS_IN_DAY) + BIAS;    
    secs = OS_TICKS_TO_SEC(ticks) % SECS_IN_DAY;
    if (secs < 0) {
        days -= 1;
        secs += SECS_IN_DAY;
        ASSERTLINE(375, 0 <= secs);
    }

    GetDates(days, td);
    td->hour = secs / 60 / 60;
    td->min = secs / 60 % 60;
    td->sec = secs % 60;
}

/**
 * Converts a calendar date and time in td back into time-base ticks counted from 2000.
 * Out-of-range months are carried into the year.
 */
OSTime OSCalendarTimeToTicks(OSCalendarTime* td) {
    OSTime secs;
    int ov_mon;
    int mon;
    int year;

    ov_mon = td->mon / MONTH_MAX;
    mon = td->mon - (ov_mon * MONTH_MAX);

    if (mon < 0) {
        mon += MONTH_MAX;
        ov_mon--;
    }

    ASSERTLINE(412, (ov_mon <= 0 && 0 <= td->year + ov_mon) || (0 < ov_mon && td->year <= INT_MAX - ov_mon));
    
    year = td->year + ov_mon;

    secs = (OSTime)SECS_IN_YEAR * year +
           (OSTime)SECS_IN_DAY * (GetLeapDays(year) + GetYearDays(year, mon) + td->mday - 1) +
           (OSTime)SECS_IN_HOUR * td->hour +
           (OSTime)SECS_IN_MIN * td->min +
           td->sec -
           (OSTime)0xEB1E1BF80ULL;

    return OS_SEC_TO_TICKS(secs) + OS_MSEC_TO_TICKS((OSTime)td->msec) +
           OS_USEC_TO_TICKS((OSTime)td->usec);
}
