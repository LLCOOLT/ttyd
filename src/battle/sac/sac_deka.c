#include "battle/battle.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"

extern BattleWork* _battleWorkPointer;

typedef struct DekaWork {
    /* 0x000 */ u8 pad0[0x30];
    /* 0x030 */ s32 state;
    /* 0x034 */ u8 pad34[0x10];
    /* 0x044 */ s32 result;
    /* 0x048 */ u8 pad48[0x3f0 - 0x48];
    /* 0x3F0 */ s32 starState;
} DekaWork;

#pragma dont_inline on
static DekaWork* get_ptr(void) {
    return (DekaWork*)((u8*)_battleWorkPointer + 0x1f4c);
}
#pragma dont_inline reset

s32 weaponGetPower_Deka(void) {
    return get_ptr()->result + 1;
}

s32 wait_star_stone_take_on(EventEntry* evt, BOOL isFirstCall) {
    return get_ptr()->starState == 4 ? 2 : 0;
}

static s32 start_game(EventEntry* evt, BOOL isFirstCall) {
    get_ptr()->state = 1;
    return 2;
}

static s32 wait_game_end(EventEntry* evt, BOOL isFirstCall) {
    return get_ptr()->state == 5 ? 2 : 0;
}

static s32 star_stone_appear(EventEntry* evt, BOOL isFirstCall) {
    get_ptr()->starState = 1;
    return 2;
}

static s32 star_stone_attack(EventEntry* evt, BOOL isFirstCall) {
    DekaWork* w = get_ptr();
    if (isFirstCall) {
        w->starState = 10;
    }
    return w->starState == 13 ? 2 : 0;
}

s32 get_result(EventEntry* evt, BOOL isFirstCall) {
    DekaWork* w = get_ptr();
    evtSetValue(evt, evt->args[0], w->result);
    return 2;
}
