// mail_data.c: the Mail Box SP letter table (MailData, mail_data) and the mailGetPtr lookup.
#pragma once

#include <dolphin/types.h>

// MailData.flags: the sender group (list colour in win_root) and whether the letter has a picture.
enum MailFlags {
    MAIL_FLAG_PEACH = 0x1,      // Princess Peach's chapter letters
    MAIL_FLAG_TROUBLE = 0x2,    // the Trouble Center follow-up letters (irai_*)
    MAIL_FLAG_NEWS = 0x4,       // the RDM news letters (info_mail_*)
    MAIL_FLAG_MYSTERY = 0x8,    // the anonymous chapter 3 hint letters (msg_mail_nazo_*)
    MAIL_FLAG_PICTURE = 0x1000, // friends' letters with a picture: icon is drawn next to the title
};

typedef struct MailData {
    u16 flags;        // 0x0, MailFlags
    u16 pad_2;        // 0x2
    s32 id;           // 0x4
    const char* name; // 0x8, message tag of the mail's title
    const char* body; // 0xC, message tag of the mail's text
    s32 icon;         // 0x10, texture drawn next to the title with MAIL_FLAG_PICTURE (win_root mail list)
} MailData;

extern MailData mail_data[44];

MailData* mailGetPtr(s32 id);
