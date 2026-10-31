// evt_msg.c: script commands for message windows: printing, choices, inserted strings and closing.
#pragma once

#include <dolphin/types.h>
#include "evt/evt_cmd.h"

// Flag word (first argument) of evt_msg_print, evt_msg_print_insert, evt_msg_print_add(_insert) and evt_msg_select.
#define MSG_PRINT_DIRECT 0x1      // the message argument is the text itself, not a message id for msgSearch
#define MSG_PRINT_BATTLE_UNIT 0x2 // evt_msg_print: the speaker is a battle unit (MSG_WIN_FLAG_BATTLE_UNIT)

void evt_msg_init(void);

USER_FUNC(evt_msg_close);
USER_FUNC(evt_msg_continue);
USER_FUNC(evt_msg_print);
USER_FUNC(evt_msg_print_add);
USER_FUNC(evt_msg_print_battle_party);
USER_FUNC(evt_msg_print_party);
USER_FUNC(evt_msg_repeat);
USER_FUNC(evt_msg_select);
USER_FUNC(evt_msg_toge);

extern char msg_article_buf[0xA00];
extern char msg_count_buf[0xA00];
extern char msg_num_buf[0xA00];
extern char msg_plural_buf[0xA00];

USER_FUNC(evt_msg_print_party_add);
USER_FUNC(evt_msg_print_insert);
USER_FUNC(evt_msg_print_add_insert);
USER_FUNC(evt_msg_togelr);
USER_FUNC(evt_msg_pri);
USER_FUNC(evt_msg_npc);
USER_FUNC(evt_msg_fmt_str);
USER_FUNC(evt_msg_fmt_int);
void evtMsgFmtInt(char* buf, s32 count);
void evtMsgFmtStr(char* buf, const char* name);
