#pragma once

#include <dolphin/types.h>

typedef struct MailData {
    u32 flags;         // 0x0
    s32 id;            // 0x4
    const char* name;  // 0x8, message tag of the mail's title
    const char* body;  // 0xC, message tag of the mail's text
    s32 icon;          // 0x10, texture drawn next to the title when flags & 0x1000 (win_root mail list)
} MailData;

extern MailData mail_data[44];

MailData* mailGetPtr(s32 id);
