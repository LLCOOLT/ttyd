// evt_kinopio.c: inn scripts and helpers (evt_kinopio_setup, bed and payment commands); kinopio is Toad.
#pragma once

#include "evt/evt_cmd.h"
#include "dolphin/types.h"
#include "version.h"

USER_FUNC(evt_kinopio_setup);
extern EvtWord kinopio_house_talk_evt[];

extern EvtWord evt_50[];

// helpers for the inn scripts
#if VERSION >= VERSION_JP
USER_FUNC(N_cameraman_on);
#endif
