#pragma once

#include <dolphin/types.h>

typedef struct MailData {
    u32 flags;         // 0x0
    s32 id;            // 0x4
    const char* name;  // 0x8, message tag of the mail's title
    const char* body;  // 0xC, message tag of the mail's text
    s32 field_0x10;    // 0x10
} MailData;

extern MailData mail_data[44];

MailData* mailGetPtr(s32 id);
