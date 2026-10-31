// evt_memcard.c: the memory card save/load scripts and commands (cardmgr).
#pragma once

#include "dolphin/types.h"
#include "evt/evt_word.h"
#include "version.h"

extern EvtWord evt_memcard_save[];

extern EvtWord evt_memcard_check[];
extern EvtWord evt_memcard_copy[];
extern EvtWord evt_memcard_delete[];
#if VERSION >= VERSION_US
extern EvtWord evt_memcard_save_wrapper[];
#endif
extern EvtWord evt_memcard_start[];

#include "evt/evt_cmd.h"

#if VERSION >= VERSION_JP
USER_FUNC(memcard_buf_reset);
USER_FUNC(memcard_watch_start);
USER_FUNC(memcard_watch_chk);
USER_FUNC(memcard_watch_end);
#endif
