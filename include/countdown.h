// countdown.c: the on-screen countdown timer (CountdownWork, countDownStart/Stop/Main) that timed events use.
#pragma once

#include <dolphin/types.h>

// CountdownWork.flags (also the countDownFlagOn/Off arguments).
enum CountdownFlags {
    COUNTDOWN_FLAG_RUNNING = 0x1, // countDownStart; cleared when the slide-out ends (countDownGetStatus -1 without it)
    COUNTDOWN_FLAG_TIME_UP = 0x2, // the limit is reached: the display shows zero (countDownGetStatus 1)
    COUNTDOWN_FLAG_HIDDEN = 0x4,  // countDownDisp draws nothing
    COUNTDOWN_FLAG_FROZEN = 0x8,  // countDownStop: the clock no longer advances
};

typedef struct CountdownWork {
    u16 flags;              // 0x0, CountdownFlags
    u8 pad_2[0x8 - 0x2];    // 0x2
    s64 elapsed;            // 0x8
    s64 prevTime;           // 0x10
    u32 limit;              // 0x18
    u32 restart;            // 0x1c
    f32 x;                  // 0x20
    f32 y;                  // 0x24
    f32 offX;               // 0x28
    f32 offY;               // 0x2c
    s32 state;              // 0x30
    s32 counter;            // 0x34
    s32 sfxId;              // 0x38
    u8 pad_3C[0x40 - 0x3c]; // 0x3c
} CountdownWork;

void countDownInit(void);
void countDownSaveReStart(void);

void countDownMain(void);
void countDownStart(u32 limit, u32 restart);
void countDownSetRestartTime(u32 restart);
void countDownStop(void);
void countDownEnd(void);
void countDownFlagOn(u16 flag);
void countDownFlagOff(u16 flag);
s32 countDownGetStatus(void);
