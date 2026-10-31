// evt_lottery.c: the Pianta Parlor lottery (lottery_info, lotteryGetPtr, evt_lottery, evt_lottery_buy).
#pragma once

#include <dolphin/types.h>
#include <dolphin/os.h>
#include "evt/evt_cmd.h"

// lottery_info.flags bits (written to the scripts by evt_lottery and evt_lottery_flag).
enum LotteryFlags {
    LOTTERY_FLAG_DRAWN = 0x1,           // todayNum has been drawn once
    LOTTERY_FLAG_TICKET = 0x2,          // a ticket is held (evt_lottery_buy)
    LOTTERY_FLAG_CLOCK_ERROR = 0x4,     // the console clock went back since the last visit
    LOTTERY_FLAG_BOUGHT_IN_ERROR = 0x8, // the ticket was bought while the clock error stood (or over an old ticket)
    LOTTERY_FLAG_NEW_DAY_VISIT = 0x10,  // first visit to this seller today (with a ticket)
    LOTTERY_FLAG_MATCH_4 = 0x1000,      // today is the ticket's secret day: all four digits match
    LOTTERY_FLAG_MATCH_3 = 0x2000,      // the last three digits match
    LOTTERY_FLAG_MATCH_2 = 0x4000,      // the last two digits match
    LOTTERY_FLAG_MATCH_1 = 0x8000,      // the last digit matches
};

typedef struct lottery_info {
    u16 flags;        // 0x0
    u8 pad_0x2[0x6];  // 0x2
    OSTime lastTime;  // 0x8
    s16 todayNum;     // 0x10
    u8 pad_0x12[0x6]; // 0x12
    OSTime buyTime;   // 0x18
    s16 number;       // 0x20
    s16 days[4];      // 0x22
    u8 pad_0x2A[0x6]; // 0x2A
    OSTime times[2];  // 0x30
} lottery_info;

lottery_info* lotteryGetPtr(void);

extern BOOL dbg_lotteryinfo; // evt_lottery

USER_FUNC(evt_lottery);
USER_FUNC(evt_lottery_buy);
USER_FUNC(evt_lottery_flag);
USER_FUNC(evt_lottery_todaynum);
USER_FUNC(evt_lottery_error_check);
