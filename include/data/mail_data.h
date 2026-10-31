// mail_data.c: the Mail Box SP letter table (MailData, mail_data) and the mailGetPtr lookup.
#pragma once

#include <dolphin/types.h>

typedef struct MailData {
    u16 flags;        // 0x0, sender group 1/2/4/8 (win_root picks the list icon from 1/2/4); 0x1000 = has a picture (icon)
    u16 pad_2;        // 0x2
    s32 id;           // 0x4
    const char* name; // 0x8, message tag of the mail's title
    const char* body; // 0xC, message tag of the mail's text
    s32 icon;         // 0x10, texture drawn next to the title when flags & 0x1000 (win_root mail list)
} MailData;

extern MailData mail_data[44];

MailData* mailGetPtr(s32 id);
