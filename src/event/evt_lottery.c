// Script commands for the Pianta Parlor lottery ticket.
#include "evt/evt_lottery.h"
#include "evt/evt_cmd.h"
#include "mario/mariost.h"
#include <dolphin/os.h>
#include "libc_decls.h"
#include "manager/evtmgr_cmd.h"
#include "version.h"

//.sbss
BOOL dbg_lotteryinfo;
static s32 lotteryUnused;

/** Returns the lottery state kept in the save data (gp->lotteryInfo); the shop menus read the ticket number from it. */
lottery_info* lotteryGetPtr(void) {
    return &gp->lotteryInfo;
}

// Updates the lottery from the console clock when a seller (args[0] = 0 or 1) is visited: once a day draws today's
// number (todayNum), and on the ticket's secret prize days makes it match 4/3/2/1 digits (flags 0x1000-0x8000).
// Flag 4 marks a clock set backwards. Writes the flags to args[1] and today's number to args[2].
#if VERSION <= VERSION_DEMO_JP
/**
 * the demo checks the draw day before the per-shop times,
 * never rerolls a prize number and keeps the buy times when the clock went back
 */
USER_FUNC(evt_lottery) {
    lottery_info* lot;
    s32 day;
    s32 v;
    OSCalendarTime a1, a2, d1, d2, b1, b2, e;
    EvtWord* args = event->args;
    s32 idx = evtGetValue(event, args[0]);

    OSTime now = OSGetTime();

    dbg_lotteryinfo = TRUE;
    lot = &gp->lotteryInfo;

    lot->flags &= ~LOTTERY_FLAG_MATCH_4;
    lot->flags &= ~LOTTERY_FLAG_MATCH_3;
    lot->flags &= ~LOTTERY_FLAG_MATCH_2;
    lot->flags &= ~LOTTERY_FLAG_MATCH_1;

    if (lot->flags & LOTTERY_FLAG_BOUGHT_IN_ERROR) {
        if (lot->buyTime < now) {
            OSTicksToCalendarTime(lot->buyTime, &a1);
            OSTicksToCalendarTime(now, &a2);
            if (a1.year != a2.year || a1.mon != a2.mon || a1.mday != a2.mday) {
                lot->flags &= ~LOTTERY_FLAG_CLOCK_ERROR;
                lot->flags &= ~LOTTERY_FLAG_BOUGHT_IN_ERROR;
            }
        } else {
            lot->flags |= LOTTERY_FLAG_CLOCK_ERROR;
            lot->flags &= ~LOTTERY_FLAG_BOUGHT_IN_ERROR;
        }
    }

    if (!(lot->flags & LOTTERY_FLAG_DRAWN)) {
        lot->flags |= LOTTERY_FLAG_DRAWN;
        lot->lastTime = now;
        lot->todayNum = rand() % 10000;
    } else if (lot->lastTime < now) {
        OSTicksToCalendarTime(lot->lastTime, &d1);
        OSTicksToCalendarTime(now, &d2);
        if (d1.year != d2.year || d1.mon != d2.mon || d1.mday != d2.mday) {
            if (idx == 1) {
                lot->lastTime = now;
            }
            if (!(lot->flags & LOTTERY_FLAG_TICKET)) {
                lot->todayNum = rand() % 10000;
            } else if (!(now < lot->buyTime)) {
                day = (now - lot->buyTime) / OS_TIMER_CLOCK / 60 / 60 / 24;
                v = lot->days[0];
                if (day > v) {
                    while (day > v) {
                        v += 395 - rand() % 60;
                    }
                    lot->days[0] = v - day;
                }
                v = lot->days[1];
                if (day > v) {
                    while (day > v) {
                        v += 115 - rand() % 30;
                    }
                    lot->days[1] = v - day;
                }
                v = lot->days[2];
                if (day > v) {
                    while (day > v) {
                        v += 35 - rand() % 10;
                    }
                    lot->days[2] = v - day;
                }
                v = lot->days[3];
                if (day > v) {
                    while (day > v) {
                        v += 10 - rand() % 6;
                    }
                    lot->days[3] = v - day;
                }
                if (day == lot->days[0]) {
                    lot->todayNum = lot->number;
                    lot->flags |= LOTTERY_FLAG_MATCH_4;
                } else if (day == lot->days[1]) {
                    lot->todayNum = lot->number % 1000 + rand() % 10 * 1000;
                    lot->flags |= LOTTERY_FLAG_MATCH_3;
                } else if (day == lot->days[2]) {
                    lot->todayNum = lot->number % 100 + rand() % 100 * 100;
                    lot->flags |= LOTTERY_FLAG_MATCH_2;
                } else if (day == lot->days[3]) {
                    lot->todayNum = lot->number % 10 + rand() % 1000 * 10;
                    lot->flags |= LOTTERY_FLAG_MATCH_1;
                } else {
                    for (;;) {
                        lot->todayNum = rand() % 10000;
                        if (lot->todayNum != lot->number) {
                            break;
                        }
                    }
                }
            } else {
                lot->flags |= LOTTERY_FLAG_CLOCK_ERROR;
                lot->todayNum = -1;
            }
        }
    } else {
        lot->flags |= LOTTERY_FLAG_CLOCK_ERROR;
        lot->todayNum = -1;
        if (idx == 1) {
            lot->lastTime = now;
        }
    }

    if (lot->flags & LOTTERY_FLAG_TICKET) {
        if (lot->times[idx] < now) {
            OSTicksToCalendarTime(lot->times[idx], &b1);
            OSTicksToCalendarTime(now, &b2);
            if (b1.year == b2.year && b1.mon == b2.mon && b1.mday == b2.mday) {
                lot->flags &= ~LOTTERY_FLAG_NEW_DAY_VISIT;
            } else {
                lot->flags |= LOTTERY_FLAG_NEW_DAY_VISIT;
                lot->times[idx] = now;
            }
        } else {
            lot->flags |= LOTTERY_FLAG_CLOCK_ERROR;
            lot->todayNum = -1;
            lot->flags |= LOTTERY_FLAG_NEW_DAY_VISIT;
            lot->times[idx] = now;
        }
    }

    evtSetValue(event, args[1], lot->flags);
    evtSetValue(event, args[2], lot->todayNum);
    OSTicksToCalendarTime(now, &e);
    if (lot->flags & LOTTERY_FLAG_TICKET) {
        OSTime bt;
        OSTicksToCalendarTime(lot->buyTime, &e);
        bt = lot->buyTime;
        OSTicksToCalendarTime(bt + (OSTime)OS_TIMER_CLOCK * 86400 * lot->days[0], &e);
        bt = lot->buyTime;
        OSTicksToCalendarTime(bt + (OSTime)OS_TIMER_CLOCK * 86400 * lot->days[1], &e);
        bt = lot->buyTime;
        bt += (OSTime)OS_TIMER_CLOCK * 86400 * lot->days[2];
        OSTicksToCalendarTime(bt, &e);
        bt = lot->buyTime;
        bt += (OSTime)OS_TIMER_CLOCK * 86400 * lot->days[3];
        OSTicksToCalendarTime(bt, &e);
    }
    return EVT_RETURN_DONE;
}
#else
/**
 * Retail evt_lottery: as the demo version, but checks the seller's daily visit first
 * and redraws numbers that match the ticket by accident.
 */
USER_FUNC(evt_lottery) {
    lottery_info* lot;
    s32 day;
    s32 v;
    OSCalendarTime a1, a2, b1, b2, c1, c2, d1, d2, e;
    EvtWord* args = event->args;
    s32 idx = evtGetValue(event, args[0]);

    OSTime now = OSGetTime();

    dbg_lotteryinfo = TRUE;
    lot = &gp->lotteryInfo;

    lot->flags &= ~LOTTERY_FLAG_MATCH_4;
    lot->flags &= ~LOTTERY_FLAG_MATCH_3;
    lot->flags &= ~LOTTERY_FLAG_MATCH_2;
    lot->flags &= ~LOTTERY_FLAG_MATCH_1;

    if (lot->flags & LOTTERY_FLAG_BOUGHT_IN_ERROR) {
        if (lot->buyTime < now) {
            OSTicksToCalendarTime(lot->buyTime, &a1);
            OSTicksToCalendarTime(now, &a2);
            if (a1.year != a2.year || a1.mon != a2.mon || a1.mday != a2.mday) {
                lot->flags &= ~LOTTERY_FLAG_CLOCK_ERROR;
                lot->flags &= ~LOTTERY_FLAG_BOUGHT_IN_ERROR;
            }
        } else {
            lot->flags |= LOTTERY_FLAG_CLOCK_ERROR;
            lot->flags &= ~LOTTERY_FLAG_BOUGHT_IN_ERROR;
        }
    }

    if (lot->flags & LOTTERY_FLAG_TICKET) {
        if (lot->times[idx] < now) {
            OSTicksToCalendarTime(lot->times[idx], &b1);
            OSTicksToCalendarTime(now, &b2);
            if (b1.year == b2.year && b1.mon == b2.mon && b1.mday == b2.mday) {
                lot->flags &= ~LOTTERY_FLAG_NEW_DAY_VISIT;
            } else {
                if (!(lot->flags & LOTTERY_FLAG_BOUGHT_IN_ERROR)) {
                    lot->flags |= LOTTERY_FLAG_NEW_DAY_VISIT;
                }
                lot->times[idx] = now;
            }
        } else {
            OSTicksToCalendarTime(lot->times[idx], &c1);
            OSTicksToCalendarTime(now, &c2);
            if (c1.year == c2.year && c1.mon == c2.mon && c1.mday == c2.mday) {
                lot->flags &= ~LOTTERY_FLAG_NEW_DAY_VISIT;
            } else {
                lot->flags |= LOTTERY_FLAG_NEW_DAY_VISIT;
                lot->times[idx] = now;
            }
            lot->flags |= LOTTERY_FLAG_CLOCK_ERROR;
        }
    } else {
        lot->times[idx] = 0;
    }

    if (!(lot->flags & LOTTERY_FLAG_DRAWN)) {
        lot->flags |= LOTTERY_FLAG_DRAWN;
        lot->lastTime = now;
        lot->todayNum = rand() % 10000;
    } else if (lot->lastTime < now) {
        OSTicksToCalendarTime(lot->lastTime, &d1);
        OSTicksToCalendarTime(now, &d2);
        if (d1.year != d2.year || d1.mon != d2.mon || d1.mday != d2.mday) {
            if (idx == 1) {
                lot->lastTime = now;
            }
            if (!(lot->flags & LOTTERY_FLAG_TICKET)) {
                lot->todayNum = rand() % 10000;
            } else if (!(now < lot->buyTime)) {
                day = (now - lot->buyTime) / OS_TIMER_CLOCK / 60 / 60 / 24;
                v = lot->days[0];
                if (day > v) {
                    while (day > v) {
                        v += 395 - rand() % 60;
                    }
                    lot->days[0] = v - day;
                }
                v = lot->days[1];
                if (day > v) {
                    while (day > v) {
                        v += 115 - rand() % 30;
                    }
                    lot->days[1] = v - day;
                }
                v = lot->days[2];
                if (day > v) {
                    while (day > v) {
                        v += 35 - rand() % 10;
                    }
                    lot->days[2] = v - day;
                }
                v = lot->days[3];
                if (day > v) {
                    while (day > v) {
                        v += 10 - rand() % 6;
                    }
                    lot->days[3] = v - day;
                }
                if (day == lot->days[0]) {
                    lot->todayNum = lot->number;
                    lot->flags |= LOTTERY_FLAG_MATCH_4;
                } else if (day == lot->days[1]) {
                    do {
                        lot->todayNum = lot->number % 1000 + rand() % 10 * 1000;
                    } while (lot->todayNum == lot->number);
                    lot->flags |= LOTTERY_FLAG_MATCH_3;
                } else if (day == lot->days[2]) {
                    do {
                        lot->todayNum = lot->number % 100 + rand() % 100 * 100;
                    } while (lot->todayNum == lot->number || lot->todayNum % 1000 == lot->number % 1000);
                    lot->flags |= LOTTERY_FLAG_MATCH_2;
                } else if (day == lot->days[3]) {
                    do {
                        lot->todayNum = lot->number % 10 + rand() % 1000 * 10;
                    } while (lot->todayNum == lot->number || lot->todayNum % 1000 == lot->number % 1000 ||
                             lot->todayNum % 100 == lot->number % 100);
                    lot->flags |= LOTTERY_FLAG_MATCH_1;
                } else {
                    do {
                        lot->todayNum = rand() % 10000;
                    } while (lot->todayNum == lot->number || lot->number % 1000 == lot->todayNum % 1000 ||
                             lot->number % 100 == lot->todayNum % 100 || lot->number % 10 == lot->todayNum % 10);
                }
            } else {
                lot->flags |= LOTTERY_FLAG_CLOCK_ERROR;
                lot->todayNum = -1;
            }
        }
    } else {
        lot->flags |= LOTTERY_FLAG_CLOCK_ERROR;
        lot->todayNum = -1;
        lot->lastTime = now;
    }

    evtSetValue(event, args[1], lot->flags);
    evtSetValue(event, args[2], lot->todayNum);
    OSTicksToCalendarTime(now, &e);
    if (lot->flags & LOTTERY_FLAG_TICKET) {
        OSTime bt;
        OSTicksToCalendarTime(lot->buyTime, &e);
        bt = lot->buyTime;
        OSTicksToCalendarTime(bt + (OSTime)OS_TIMER_CLOCK * 86400 * lot->days[0], &e);
        bt = lot->buyTime;
        OSTicksToCalendarTime(bt + (OSTime)OS_TIMER_CLOCK * 86400 * lot->days[1], &e);
        bt = lot->buyTime;
        bt += (OSTime)OS_TIMER_CLOCK * 86400 * lot->days[2];
        OSTicksToCalendarTime(bt, &e);
        bt = lot->buyTime;
        bt += (OSTime)OS_TIMER_CLOCK * 86400 * lot->days[3];
        OSTicksToCalendarTime(bt, &e);
    }
    return EVT_RETURN_DONE;
}
#endif

// Buys a ticket: draws its number (written to args[0]), records the buy time and the four prize days (336-395,
// 86-115, 26-35 and 5-10 days out), and sets flag 2. Retail draws a number sharing no trailing digits with today's.
#if VERSION <= VERSION_DEMO_JP
/** the demo only marks a purchase made with a broken clock */
USER_FUNC(evt_lottery_buy) {
    EvtWord* args = event->args;
    OSTime now = OSGetTime();
    lottery_info* lot = &gp->lotteryInfo;

    do {
        lot->number = rand() % 10000;
    } while (lot->todayNum == lot->number);
    lot->buyTime = now;
    lot->days[0] = 395 - rand() % 60;
    lot->days[1] = 115 - rand() % 30;
    lot->days[2] = 35 - rand() % 10;
    lot->days[3] = 10 - rand() % 6;
    lot->flags |= LOTTERY_FLAG_TICKET;
    if (lot->flags & LOTTERY_FLAG_CLOCK_ERROR) {
        lot->flags |= LOTTERY_FLAG_BOUGHT_IN_ERROR;
    }
    evtSetValue(event, args[0], lot->number);
    return EVT_RETURN_DONE;
}
#else
/** Retail evt_lottery_buy: also resets the stored visit times when buying after a clock error or over an old ticket. */
USER_FUNC(evt_lottery_buy) {
    EvtWord* args = event->args;
    OSTime now = OSGetTime();
    lottery_info* lot = &gp->lotteryInfo;

    do {
        lot->number = rand() % 10000;
    } while (lot->number == lot->todayNum || lot->number % 1000 == lot->todayNum % 1000 ||
             lot->number % 100 == lot->todayNum % 100 || lot->number % 10 == lot->todayNum % 10);
    lot->buyTime = now;
    lot->days[0] = 395 - rand() % 60;
    lot->days[1] = 115 - rand() % 30;
    lot->days[2] = 35 - rand() % 10;
    lot->days[3] = 10 - rand() % 6;
    if (lot->flags & LOTTERY_FLAG_CLOCK_ERROR) {
        lot->flags |= LOTTERY_FLAG_BOUGHT_IN_ERROR;
        lot->lastTime = now;
        lot->times[0] = now;
        lot->times[1] = now;
    }
    if (lot->flags & LOTTERY_FLAG_TICKET) {
        lot->flags |= LOTTERY_FLAG_BOUGHT_IN_ERROR;
        lot->lastTime = now;
        lot->times[0] = now;
        lot->times[1] = now;
    }
    lot->flags |= LOTTERY_FLAG_TICKET;
    evtSetValue(event, args[0], lot->number);
    return EVT_RETURN_DONE;
}
#endif

/** Writes the lottery flags (gp->lotteryInfo.flags) to args[0]. */
USER_FUNC(evt_lottery_flag) {
    evtSetValue(event, event->args[0], (&gp->lotteryInfo)->flags);
    return EVT_RETURN_DONE;
}

/** Writes today's drawn number to args[0] (-1 after a clock error). */
USER_FUNC(evt_lottery_todaynum) {
    evtSetValue(event, event->args[0], (&gp->lotteryInfo)->todayNum);
    return EVT_RETURN_DONE;
}

/**
 * Writes TRUE to args[0] when the console clock looks set backwards (flag 4, or now before any stored time),
 * unless a ticket was bought under that error on an earlier day.
 */
USER_FUNC(evt_lottery_error_check) {
    OSCalendarTime a, b;
    GlobalWork* g = gp;
    EvtWord* args = event->args;
    OSTime now = OSGetTime();
    lottery_info* lot = &g->lotteryInfo;
    u16 flags = lot->flags;
    BOOL err = FALSE;

    if (flags & LOTTERY_FLAG_CLOCK_ERROR) {
        err = TRUE;
    }
    if ((flags & LOTTERY_FLAG_TICKET) && now < lot->buyTime) {
        err = TRUE;
    }
    if (now < lot->times[0]) {
        err = TRUE;
    }
    if (now < lot->times[1]) {
        err = TRUE;
    }
    if (now < lot->lastTime) {
        err = TRUE;
    }
    if ((flags & LOTTERY_FLAG_BOUGHT_IN_ERROR) && lot->buyTime < now) {
        OSTicksToCalendarTime(lot->buyTime, &a);
        OSTicksToCalendarTime(now, &b);
        if (a.year != b.year || a.mon != b.mon || a.mday != b.mday) {
            err = FALSE;
        }
    }
    evtSetValue(event, args[0], err);
    return EVT_RETURN_DONE;
}
