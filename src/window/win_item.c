#include "win/win_main.h"
#include "driver/msgdrv.h"
#include "manager/fontmgr.h"
#include "manager/winmgr.h"
#include "mario/mario_pouch.h"
#include "system.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "data/item_data.h"
#include <dolphin/gx.h>
#include "mario/mariost.h"
#include "driver/swdrv.h"
#include "manager/filemgr.h"
#include "data/mail_data.h"

typedef struct ITexRef {
    TEXPalette* tpl;
} ITexRef;

typedef struct IRes {
    u8 pad_0[0xA0];
    ITexRef* tex;
} IRes;

typedef struct IWinPos {
    f32 x;
    f32 y;
    f32 scroll;
    f32 width;
    u8 pad[4];
} IWinPos;

typedef struct ItemWork {
    /* 0x000 */ u16 flags;
    /* 0x002 */ u8 pad_2[2];
    /* 0x004 */ u32 trg;
    /* 0x008 */ u32 rep;
    /* 0x00C */ u32 dtrg;
    /* 0x010 */ u32 drep;
    /* 0x014 */ u8 pad_14[0x28 - 0x14];
    /* 0x028 */ IRes* res;
    /* 0x02C */ FileEntry* mailTex;
    /* 0x030 */ u8 pad_30[0xC4 - 0x30];
    /* 0x0C4 */ IWinPos pos[3];
    /* 0x100 */ u8 pad_100[0x124 - 0x100];
    /* 0x124 */ s32 saved;
    /* 0x128 */ u8 pad_128[0x150 - 0x128];
    /* 0x150 */ f32 f150;
    /* 0x154 */ f32 f154;
    /* 0x158 */ f32 msgX;
    /* 0x15C */ f32 msgY;
    /* 0x160 */ u8 pad_160[0x1E0 - 0x160];
    /* 0x1E0 */ s32 partyCount;
    /* 0x1E4 */ u8 pad_1E4[0x20C - 0x1E4];
    /* 0x20C */ s32 state;
    /* 0x210 */ s32 mode;
    /* 0x214 */ s32 cursor[2];
    /* 0x21C */ s32 page[2];
    /* 0x224 */ f32 curX;
    /* 0x228 */ f32 curY;
    /* 0x22C */ f32 tgtX;
    /* 0x230 */ f32 tgtY;
    /* 0x234 */ f32 box[8];
    /* 0x254 */ s32 mailCount;
    /* 0x258 */ s32 f258;
    /* 0x25C */ s32 f25C;
    /* 0x260 */ f32 scrollCur;
    /* 0x264 */ f32 scrollTgt;
    /* 0x268 */ s32 line;
    /* 0x26C */ u16 lines;
    /* 0x26E */ u8 mail[45][2];
    /* 0x2C8 */ s32 bookIdx;
    /* 0x2CC */ s32 bookPages;
    /* 0x2D0 */ s32 bookPage;
    /* 0x2D4 */ s32 f2D4;
    /* 0x2D8 */ s32 f2D8;
    /* 0x2DC */ s32 sel;
    /* 0x2E0 */ s32 blink;
    /* 0x2E4 */ u8 pad_2E4[0x4];
    /* 0x2E8 */ s16 skip[0x48];
    /* 0x378 */ u8 pad_378[0x3DA - 0x378];
    /* 0x3DA */ s16 skipCount;
    /* 0x3DC */ u8 pad_3DC[0x1208 - 0x3DC];
    /* 0x1208 */ s32 winId0;
    /* 0x120C */ s32 winId1;
} ItemWork;

void winMsgEntry(ItemWork* w, s32 a, const char* msg, s32 b);
void winFontInit(void);
void winFontSet(Vec translate, Vec scale, GXColor color, const char* fmt, ...);
void winItemInit(ItemWork* w);
void itemUseDisp(WinMgrEntry* entry);
void itemUseDisp2(WinMgrEntry* entry);
void itemUseDisp(WinMgrEntry* entry);
void itemUseDisp2(WinMgrEntry* entry);
void item_disp(ItemWork* w, f32 xo, f32 yo);
void winBgGX(ItemWork* w, s32 a, f32 x, f32 y);
void winKirinukiGX(ItemWork* w, s32 a, f32 x, f32 y, f32 w_, f32 h);
void winTexInit_x2(TEXPalette* tpl);
void winTexSet_x2(u32 a, u32 b, Vec translate, Vec scale, GXColor color);
void winIconInit(void);
void winIconGrayInit(void);
void winIconSet(u32 id, Vec translate, Vec scale, GXColor color);
void winFontSetPitch(f32 pitch, Vec translate, Vec scale, GXColor color, const char* fmt, ...);
void winBookGX(ItemWork* w, s32 a);
extern ItemData itemDataTable[];
void winFontSetR(Vec translate, Vec scale, GXColor color, const char* fmt, ...);

typedef struct WinPartyDt {
    s32 partyId;
    s32 nameMsgId;
    const char* name;
    const char* msg;
    const char* poseName;
    const char* animName;
    const char* poseName2;
    const char* animName2;
    void* waza;
} WinPartyDt;
extern WinPartyDt winPartyDt[7];
void psndSFXOn(s32 id);
void winSortEntry(ItemWork* w, s32 a, f32 x, f32 y);
s32 winSortWait(ItemWork* w);
s32 unk_8009fcbc(void);
BOOL U_marioSlitContinueChk(void);
BOOL pouchRemoveItemIndex(s32 id, s32 index);

static const char* luigi_book_1[] = {
    "msg_luigi_book1_txt1\000\000\000",
    "msg_luigi_book1_txt2\000\000\000",
    "msg_luigi_book1_txt3\000\000\000",
    "msg_luigi_book1_txt4\000\000\000",
    "msg_luigi_book1_txt5\000\000\000",
    "msg_luigi_book1_txt6\000\000\000",
    "msg_luigi_book1_txt7\000\000\000",
    "msg_luigi_book1_txt8\000\000\000",
    "msg_luigi_book1_txt9\000\000\000",
    "msg_luigi_book1_txt10\000\000",
    "msg_luigi_book1_txt11\000\000",
    "msg_luigi_book1_txt12\000\000",
    NULL,
};

static const char* luigi_book_2[] = {
    "msg_luigi_book2_txt1\000\000\000",
    "msg_luigi_book2_txt2\000\000\000",
    "msg_luigi_book2_txt3\000\000\000",
    "msg_luigi_book2_txt4\000\000\000",
    "msg_luigi_book2_txt5\000\000\000",
    "msg_luigi_book2_txt6\000\000\000",
    "msg_luigi_book2_txt7\000\000\000",
    "msg_luigi_book2_txt8\000\000\000",
    "msg_luigi_book2_txt9\000\000\000",
    "msg_luigi_book2_txt10\000\000",
    "msg_luigi_book2_txt11\000\000",
    "msg_luigi_book2_txt12\000\000",
    NULL,
};

static const char* luigi_book_3[] = {
    "msg_luigi_book3_txt1\000\000\000",
    "msg_luigi_book3_txt2\000\000\000",
    "msg_luigi_book3_txt3\000\000\000",
    "msg_luigi_book3_txt4\000\000\000",
    "msg_luigi_book3_txt5\000\000\000",
    "msg_luigi_book3_txt6\000\000\000",
    "msg_luigi_book3_txt7\000\000\000",
    "msg_luigi_book3_txt8\000\000\000",
    "msg_luigi_book3_txt9\000\000\000",
    "msg_luigi_book3_txt10\000\000",
    "msg_luigi_book3_txt11\000\000",
    "msg_luigi_book3_txt12\000\000",
    NULL,
};

static const char* luigi_book_4[] = {
    "msg_luigi_book4_txt1\000\000\000",
    "msg_luigi_book4_txt2\000\000\000",
    "msg_luigi_book4_txt3\000\000\000",
    "msg_luigi_book4_txt4\000\000\000",
    "msg_luigi_book4_txt5\000\000\000",
    "msg_luigi_book4_txt6\000\000\000",
    "msg_luigi_book4_txt7\000\000\000",
    "msg_luigi_book4_txt8\000\000\000",
    "msg_luigi_book4_txt9\000\000\000",
    "msg_luigi_book4_txt10\000\000",
    "msg_luigi_book4_txt11\000\000",
    "msg_luigi_book4_txt12\000\000",
    NULL,
};

static const char* luigi_book_5[] = {
    "msg_luigi_book5_txt1\000\000\000",
    "msg_luigi_book5_txt2\000\000\000",
    "msg_luigi_book5_txt3\000\000\000",
    "msg_luigi_book5_txt4\000\000\000",
    "msg_luigi_book5_txt5\000\000\000",
    "msg_luigi_book5_txt6\000\000\000",
    "msg_luigi_book5_txt7\000\000\000",
    "msg_luigi_book5_txt8\000\000\000",
    "msg_luigi_book5_txt9\000\000\000",
    "msg_luigi_book5_txt10\000\000",
    "msg_luigi_book5_txt11\000\000",
    "msg_luigi_book5_txt12\000\000",
    NULL,
};

const char** luigi_book_list[] = {luigi_book_1, luigi_book_2, luigi_book_3, luigi_book_4, luigi_book_5};

u16 menu_skip_list[] = {9, 10, 11, 6, 7, 8, 5, 3, 2, 4, 0x32, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78};


static WinMgrDesc window_desc[2] = {
    {0, 0, 8, -70, 150, 350, 264, {0xF0, 0xF0, 0xF0, 0xFF}, 0, itemUseDisp},
    {2, 0, 8, -280, 145, 200, 50, {0xFF, 0x99, 0x00, 0xFF}, 0, itemUseDisp2},
};

void winMakeSkipList(ItemWork* w) {
    s32 i;
    u32 j;
    u16 id;
    w->skipCount = 0;
    for (i = 0; i < 0x79; i++) {
        id = pouchKeyItem(i);
        if (id) {
            for (j = 0; j < 0x12; j++) {
                if (id == menu_skip_list[j]) {
                    break;
                }
            }
            if (j >= 0x12) {
                w->skip[w->skipCount] = id;
                w->skipCount++;
            }
        }
    }
}

void winItemInit(ItemWork* w) {
    s32 i;
    w->state = 0;
    w->mode = 0;
    w->cursor[0] = 0;
    w->page[0] = 0;
    w->cursor[1] = 0;
    w->page[1] = 0;
    w->box[0] = w->box[1] = 320.0f;
    w->box[2] = w->box[3] = -240.0f;
    w->box[4] = w->box[5] = 320.0f;
    w->box[6] = w->box[7] = -240.0f;
    if (!((s32 (*)(s32))pouchCheckItem)(0x36)) {
        pouchGetItem(0x36);
    }
    w->mailCount = pouchReceiveMailCount();
    w->f258 = 0;
    w->f25C = 0;
    w->scrollCur = w->scrollTgt = 0.0f;
    for (i = 0; i < w->mailCount; i++) {
        w->mail[i][0] = w->mailCount - i - 1;
        w->mail[i][1] = ((u8*)pouchGetPtr())[w->mailCount - i + 0x519];
    }
    w->f2D4 = 0;
    winMakeSkipList(w);
    w->winId0 = winMgrEntry(&window_desc[0]);
    w->winId1 = winMgrEntry(&window_desc[1]);
    winMgrSetPriority(w->winId0, -200);
    winMgrSetPriority(w->winId1, -100);
    fileAsyncf(4, 0, "%s/w/jp/mail.tpl\000\000\000\000\000\000\000", getMarioStDvdRoot());
}

void winItemInit2(ItemWork* w) {
    w->msgX = -275.0f;
    w->msgY = (f32)(125 - w->mode * 40);
    w->curX = w->tgtX = 190.0f * (f32)w->page[0];
    w->curY = w->tgtY = 190.0f * (f32)w->page[1];
    w->box[0] = w->box[1] = 320.0f;
    w->box[2] = w->box[3] = -240.0f;
    w->box[4] = w->box[5] = 320.0f;
    w->box[6] = w->box[7] = -240.0f;
    w->scrollCur = w->scrollTgt = (f32)(w->f258 * 200);
    winMsgEntry(w, 0, w->mode == 0 ? "msg_menu_mochi_item" : "msg_menu_mochi_daiji\000\000\000", 0);
    w->f2D4 = 0;
}

void winItemExit(ItemWork* w) {
    winMgrDelete(w->winId0);
    winMgrDelete(w->winId1);
}

s32 winItemMain(ItemWork* w) {
    s32 cnt;
    s32 col;
    f32 width;

    f32 scroll;
    s32 mode;
    s32 pages;
    s32 id;
    s32 c;
    s32 old;
    s32 ok;
    s32 gray;
    const char** book;
    WinMgrEntry* entry;
    MarioWork* mp;
    MailData* mail;
    WinPartyDt* list[10];
    s32 party;
    s32 n;
    s32 i;
    f32 yoff;

    switch (w->state) {
    case 0:
        if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            return -1;
        }
        if (w->trg & 0x1000) {
            return -2;
        }
        if (w->drep & 0x3000) {
            w->mode = 1 - w->mode;
            psndSFXOn(0x20005);
        } else if (w->trg & 0x100) {
            if (w->mode == 0 && pouchGetHaveItemCnt() == 0) {
                break;
            }
            if (w->mode == 1 && w->skipCount == 0) {
                break;
            }
            w->state = 10;
            psndSFXOn(0x20012);
            break;
        } else if (w->trg & 0x10) {
            winSortEntry(w, w->mode != 0, -310.0f, 150.0f);
            w->saved = w->state;
            psndSFXOn(0x20012);
            w->state = 1000;
        }
        w->msgX = -275.0f;
        w->msgY = (f32)(125 - w->mode * 40);
        winMsgEntry(w, 0, w->mode == 0 ? "msg_menu_mochi_item" : "msg_menu_mochi_daiji\000\000\000", 0);
        break;
    case 10:
        if (w->mode == 0) {
            cnt = pouchGetHaveItemCnt();
        } else {
            cnt = w->skipCount;
        }
        mode = w->mode;
        pages = (cnt + 9) / 10;
        if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            w->state = 0;
        }
        if (w->trg & 0x100) {
            if (w->mode == 0) {
                id = pouchHaveItem(w->cursor[mode]);
                if ((*(u16*)&itemDataTable[id].usable_locations & 4) != 0) {
                    w->f2D4 = id;
                    w->f2D8 = w->cursor[mode];
                    w->state = 300;
                    w->sel = 0;
                    w->blink = 0;
                    psndSFXOn(0x20012);
                    entry = winMgrGetPtr(w->winId0);
                    winMgrSetSize(w->winId0, entry->x, entry->y, entry->width, w->partyCount * 28 + 68);
                    winMgrOpen(w->winId0);
                    winMgrOpen(w->winId1);
                }
            } else {
                c = w->skip[w->cursor[mode]];
                if ((u32)(c - 0x37) <= 3 || c == 0x3B) {
                    w->state = 100;
                    w->box[1] = -170.0f;
                    w->box[3] = 160.0f;
                    w->flags |= 0x8000;
                    book = luigi_book_list[c - 0x37];
                    w->bookIdx = c - 0x37;
                    w->bookPage = 0;
                    for (w->bookPages = 0; book[w->bookPages] != NULL; w->bookPages++) {
                    }
                    w->bookPages = (w->bookPages + 1) / 2;
                    psndSFXOn(0x20012);
                } else if (c == 0x36 && pouchReceiveMailCount()) {
                    w->state = 200;
                    w->box[5] = -144.0f;
                    w->box[7] = 180.0f;
                    psndSFXOn(0x20012);
                } else if (c == 0x4E) {
                    w->f2D4 = c;
                    psndSFXOn(0x20012);
                    return -2;
                }
            }
        } else if (w->rep & 0x40) {
            w->page[mode]--;
            if (w->page[mode] < 0) {
                w->page[mode] = 0;
            }
            w->cursor[mode] = w->page[mode] * 10;
            psndSFXOn(0x20035);
        } else if (w->rep & 0x20) {
            w->page[mode]++;
            if (w->page[mode] >= pages) {
                w->page[mode] = pages - 1;
            }
            w->cursor[mode] = w->page[mode] * 10;
            psndSFXOn(0x20035);
        } else if (w->drep & 0xC000) {
            if (w->cursor[mode] % 2) {
                if ((n = w->cursor[mode] - 1) >= 0 && n < cnt) {
                    w->cursor[mode]--;
                }
            } else {
                if ((n = w->cursor[mode] + 1) >= 0 && n < cnt) {
                    w->cursor[mode]++;
                }
            }
            psndSFXOn(0x20035);
        } else if (w->drep & 0x1000) {
            c = w->cursor[mode];
            if ((n = c - 2) >= 0 && n < cnt) {
                w->cursor[mode] = c - 2;
            }
            w->page[mode] = w->cursor[mode] / 10;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x2000) {
            c = w->cursor[mode];
            if ((n = c + 2) >= 0 && n < cnt) {
                w->cursor[mode] = c + 2;
            } else if (c + (c & 1) < cnt) {
                w->cursor[mode] = cnt - 1;
            }
            w->page[mode] = w->cursor[mode] / 10;
            psndSFXOn(0x20035);
        } else if (w->trg & 0x10) {
            winSortEntry(w, w->mode != 0, -310.0f, 150.0f);
            w->saved = w->state;
            psndSFXOn(0x20012);
            w->state = 1000;
        } else if (w->trg & 0x1000) {
            return -2;
        }
        w->msgX = (f32)(w->cursor[mode] % 10 % 2 * 204 - 155);
        w->msgY = (f32)(110 - w->cursor[mode] % 10 / 2 * 38);
        if (w->mode == 0) {
            id = pouchHaveItem(w->cursor[mode]);
        } else {
            id = w->skip[w->cursor[mode]];
        }
        winMsgEntry(w, id, itemDataTable[id].description, 0);
        break;
    case 100:
        if (w->trg & 0x100) {
            psndSFXOn(0x20012);
            w->bookPage++;
            if (w->bookPage >= w->bookPages) {
                w->bookPage = w->bookPages - 1;
                w->state = 10;
                w->box[1] = 320.0f;
                w->box[3] = -240.0f;
                w->flags &= ~0x8000;
                w->f150 = w->msgX;
                w->f154 = w->msgY;
            }
        } else if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            w->bookPage--;
            if (w->bookPage < 0) {
                w->bookPage = 0;
                w->state = 10;
                w->box[1] = 320.0f;
                w->box[3] = -240.0f;
                w->flags &= ~0x8000;
                w->f150 = w->msgX;
                w->f154 = w->msgY;
            }
        } else if (w->trg & 0x1000) {
            w->box[1] = 320.0f;
            w->box[3] = -240.0f;
            w->flags &= ~0x8000;
            w->f150 = w->msgX;
            w->f154 = w->msgY;
            return -2;
        }
        w->msgX = -170.0f;
        w->msgY = 150.0f;
        break;
    case 200:
        if (w->trg & 0x100) {
            if ((s32)pouchCheckMail(w->mail[w->f258][1]) == 1) {
                pouchOpenMail(w->mail[w->f258][1]);
            }
            swSet(0x26);
            psndSFXOn(0x20036);
            w->state = 201;
            mail = mailGetPtr(w->mail[w->f258][1]);
            FontGetMessageWidthLine(msgSearch(mail->body), &w->lines);
            w->lines++;
            w->line = 0;
            if (*(u16*)mail & 0x1000) {
                w->lines += 10;
            }
        } else if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            w->state = 10;
            w->box[5] = 320.0f;
            w->box[7] = -240.0f;
        } else if (w->drep & 0x1000) {
            old = w->f258;
            w->f258--;
            if (w->f258 < 0) {
                w->f258 = 0;
            }
            w->f25C = w->f258 / 5;
            w->line = 0;
            if (old != w->f258) {
                psndSFXOn(0x20036);
            }
        } else if (w->drep & 0x2000) {
            old = w->f258;
            w->f258++;
            if (w->f258 >= w->mailCount) {
                w->f258 = w->mailCount - 1;
            }
            w->f25C = w->f258 / 5;
            w->line = 0;
            if (old != w->f258) {
                psndSFXOn(0x20036);
            }
        } else if (w->rep & 0x40) {
            old = w->f25C;
            w->f25C--;
            if (w->f25C < 0) {
                w->f25C = 0;
            }
            w->f258 = w->f25C * 5;
            if (old != w->f25C) {
                psndSFXOn(0x20036);
            }
        } else if (w->rep & 0x20) {
            pages = (w->mailCount + 4) / 5;
            old = w->f25C;
            w->f25C++;
            if (w->f25C >= pages) {
                w->f25C = pages - 1;
            }
            w->f258 = w->f25C * 5;
            if (old != w->f25C) {
                psndSFXOn(0x20036);
            }
        } else if (w->trg & 0x10) {
            winSortEntry(w, 7, w->box[5], w->box[7] - 60.0f);
            w->saved = w->state;
            psndSFXOn(0x20012);
            w->state = 1000;
        } else if (w->trg & 0x1000) {
            w->box[5] = 320.0f;
            w->box[7] = -240.0f;
            return -2;
        }
        w->msgX = -96.0f;
        w->msgY = 120.0f - (f32)(w->f258 % 5 * 40);
        break;
    case 201:
        mail = mailGetPtr(w->mail[w->f258][1]);
        if (*(u16*)mail & 0x1000) {
            w->mailTex = (FileEntry*)fileAsyncf(4, 0, "%s/w/jp/mail.tpl\000\000\000\000\000\000\000", getMarioStDvdRoot());
            if (w->mailTex) {
                w->mailTex = fileAllocf(4, "%s/w/jp/mail.tpl\000\000\000\000\000\000\000", getMarioStDvdRoot());
                w->state++;
            }
        } else {
            w->mailTex = NULL;
            w->state++;
        }
        break;
    case 202:
        if (w->lines > 8) {
            if (keyGetDirRep(0) & 0x100) {
                if (w->line > 0) {
                    w->line--;
                }
            } else if (keyGetDirRep(0) & 0x200) {
                if (w->line + 6 < w->lines) {
                    w->line++;
                }
            }
        }
        if (w->trg & 0x200) {
            psndSFXOn(0x20036);
            if (w->mailTex) {
                fileFree(w->mailTex);
            }
            w->state = 200;
        } else if (w->trg & 0x1000) {
            if (w->mailTex) {
                fileFree(w->mailTex);
            }
            w->box[5] = 320.0f;
            w->box[7] = -240.0f;
            return -2;
        }
        w->msgX = -96.0f;
        w->msgY = 120.0f;
        break;
    case 300:
        if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            w->state = 10;
            w->f2D4 = 0;
            winMgrClose(w->winId0);
            winMgrClose(w->winId1);
        } else if (w->trg & 0x100) {
            mp = marioGetPtr();
            ok = 0;
            psndSFXOn(0x20012);
            if (mp->currMotionId == 0x19 || mp->currMotionId == 0x18) {
                ok = 1;
            }
            if (unk_8009fcbc() || U_marioSlitContinueChk()) {
                ok = 1;
            }
            if (w->sel > 0 && marioBgmodeChk()) {
                ok = 1;
            }
            if (w->sel > 1 && !marioBgmodeChk()) {
                ok = 1;
            }
            if (!ok) {
                winMgrClose(w->winId0);
                winMgrClose(w->winId1);
                return -2;
            }
            party = !marioBgmodeChk() ? marioGetParty() : marioGetPtr()->prevPartyMemberId[0];
            n = 0;
            for (i = 0; i < 7; i++) {
                if (party == winPartyDt[i].partyId) {
                    list[n++] = &winPartyDt[i];
                }
            }
            for (i = 0; i < 7; i++) {
                if (party != winPartyDt[i].partyId) {
                    list[n++] = &winPartyDt[i];
                }
            }
            if (w->sel < 1) {
                ((void (*)(s32))pouchSetHP)(((s32 (*)(void))pouchGetHP)() + (u8)itemDataTable[w->f2D4].hp_restored);
                ((void (*)(s32))pouchSetFP)(((s32 (*)(void))pouchGetFP)() + (u8)itemDataTable[w->f2D4].fp_restored);
                ((void (*)(s32))pouchSetAP)(((s32 (*)(void))pouchGetAP)() + (u8)itemDataTable[w->f2D4].sp_restored);
            } else {
                party = list[w->sel - 1]->partyId;
                ((void (*)(s32, s32))pouchSetPartyHP)(party, ((s32 (*)(s32))pouchGetPartyHP)(party) + (u8)itemDataTable[w->f2D4].hp_restored);
                ((void (*)(s32))pouchSetFP)(((s32 (*)(void))pouchGetFP)() + (u8)itemDataTable[w->f2D4].fp_restored);
                ((void (*)(s32))pouchSetAP)(((s32 (*)(void))pouchGetAP)() + (u8)itemDataTable[w->f2D4].sp_restored);
            }
            w->blink = 0;
            w->state = 301;
            break;
        } else if (w->drep & 0x1000) {
            old = w->sel;
            w->sel--;
            if (w->sel < 0) {
                w->sel = w->partyCount;
            }
            if (old != w->sel) {
                psndSFXOn(0x20005);
            }
        } else if (w->drep & 0x2000) {
            old = w->sel;
            w->sel++;
            if (w->sel >= w->partyCount + 1) {
                w->sel = 0;
            }
            if (old != w->sel) {
                psndSFXOn(0x20005);
            }
        } else if (w->trg & 0x1000) {
            w->f2D4 = 0;
            winMgrClose(w->winId0);
            winMgrClose(w->winId1);
            return -2;
        }
        w->msgX = -80.0f;
        old = w->sel;
        if (old == 0) {
            yoff = 0.0f;
        } else if (old == 1) {
            yoff = -16.0f;
        } else {
            yoff = -28.0f;
        }
        w->msgY = (130.0f - 28.0f * old) + yoff;
        break;
    case 301:
        w->blink++;
        if (w->blink > gp->framerate * 2) {
            w->blink = 0;
            pouchRemoveItemIndex(w->f2D4, w->f2D8);
            w->state = 10;
            w->f2D4 = 0;
            if (pouchGetHaveItemCnt() == 0) {
                w->state = 0;
            } else if (w->cursor[0] >= pouchGetHaveItemCnt()) {
                w->cursor[0] = pouchGetHaveItemCnt() - 1;
            }
            winMgrClose(w->winId0);
            winMgrClose(w->winId1);
        }
        break;
    case 1000:
        if (!winSortWait(w)) {
            w->state = w->saved;
        }
        if (w->trg & 0x1000) {
            return -2;
        }
        break;
    }
    return 0;
}

void winItemMain2(ItemWork* w) {
    w->tgtX = 190.0f * (f32)w->page[0];
    w->curX += (w->tgtX - w->curX) / 4.0f;
    w->tgtY = 190.0f * (f32)w->page[1];
    w->curY += (w->tgtY - w->curY) / 4.0f;
    w->box[0] += (w->box[1] - w->box[0]) / 6.0f;
    w->box[2] += (w->box[3] - w->box[2]) / 6.0f;
    w->box[4] += (w->box[5] - w->box[4]) / 6.0f;
    w->box[6] += (w->box[7] - w->box[6]) / 6.0f;
    w->scrollTgt = (f32)(w->f25C * 200);
    w->scrollCur += (w->scrollTgt - w->scrollCur) / 4.0f;
}

void winItemDisp(s32 camId, void* param, s32 n) {
    GXColor white = {255, 255, 255, 255};
    f32 c;
    f32 b;
    f32 a;
    f32 x;
    f32 y;
    s32 off;
    ItemWork* w = param;
    s32 i;

    x = w->pos[n].x;
    y = w->pos[n].y;

    winBgGX(w, 2, x, y);
    winKirinukiGX(w, 0, x - 150.0f, 20.0f + (120.0f + y), 415.0f, 210.0f);
    a = 105.0f + y;
    c = (x - 215.0f) - 4.0f;
    b = 4.0f + a;
    for (i = 0, off = 0; i < 2; i++, off += 40) {
        if (i == w->mode) {
            winTexInit(w->res->tex->tpl);
            winTexSet(0xB3, (Vec){x - 215.0f, 20.0f + (a - off), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 0x80});
            winTexInit_x2(w->res->tex->tpl);
            winTexSet_x2(i + 0x18, 0xB3, (Vec){c, 20.0f + (b - off), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
        } else {
            winTexInit_x2(w->res->tex->tpl);
            winTexSet_x2(i + 0x18, 0xB3, (Vec){x - 215.0f, 20.0f + (a - off), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0x80, 0x80, 0x80, 0xFF});
        }
    }
    item_disp(w, x, y);
}

void item_disp(ItemWork* w, f32 xo, f32 yo) {
    GXColor white = {255, 255, 255, 255};
    GXColor white2;
    GXColor black = {0, 0, 0, 255};
    GXColor grayc = {0x80, 0x80, 0x80, 255};
    GXColor white3;
    GXColor white4;
    f32 yBase;
    ItemData* item;
    ItemWork* p;
    f32 y;
    s32 i;
    s32 id;
    s32 ok;
    s32 cnt;
    s32 gray;
    f32 scroll;
    f32 width;

    white4 = white;
    white2 = white4;
    white3 = white2;
    if (w->mode == 0) {
        cnt = pouchGetHaveItemCnt();
    } else {
        cnt = w->skipCount;
    }
    GXSetScissor(0, 0x6D, 0x260, 0xC0);
    p = w;
    for (i = 0; i < cnt; p = (ItemWork*)((s16*)p + 1), i++) {
        s32 col = i % 2;
        s32 row = i / 2;
        if (w->mode == 0) {
            id = pouchHaveItem(i);
        } else {
            id = p->skip[0];
        }
        scroll = (&w->curX)[w->mode];
        ok = w->mode != 0 || (*(u16*)&itemDataTable[id].usable_locations & 4);
        y = scroll + (20.0f + ((yBase = (100.0f + yo) - row * 38) - 10.0f));
        ok = ok == 0;
        if (y > 240.0f) {
            continue;
        }
        if (y < -240.0f) {
            break;
        }
        if (ok) {
            winIconGrayInit();
        } else {
            winIconInit();
        }
        winIconSet(itemDataTable[id].icon_id, (Vec){(xo - 125.0f) + col * 204, y, 0.0f}, w->mode == 0 ? (Vec){0.8f, 0.8f, 0.8f} : (Vec){0.6666667f, 0.6666667f, 0.6666667f}, white3);
        winFontInit();
        winFontSetPitch(20.0f, (Vec){(xo - 105.0f) + col * 204, scroll + (20.0f + yBase), 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, ok ? grayc : black, msgSearch(itemDataTable[id].name));
    }
    GXSetScissor(0, 0, 0x260, 0x1E0);
    if ((&w->page[0])[w->mode] > 0) {
        winTexInit(w->res->tex->tpl);
        width = 250.0f + xo;
        winTexSet(0x17, (Vec){width, 20.0f + (18.0f + (110.0f + yo)), 0.0f}, (Vec){-1.0f, -1.0f, -1.0f}, white2);
        winIconInit();
        winIconSet(0x7E, (Vec){width, 20.0f + (113.0f + yo), 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, white2);
    }
    if (cnt > (&w->page[0])[w->mode] * 10 + 10) {
        winTexInit(w->res->tex->tpl);
        width = 250.0f + xo;
        winTexSet(0x17, (Vec){width, 20.0f + ((yo - 90.0f) - 15.0f), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white2);
        winIconInit();
        winIconSet(0x80, (Vec){width, 20.0f + (yo - 90.0f), 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, white2);
    }
    width = 0.7f * (f32)(u32)FontGetMessageWidth(msgSearch("msg_menu_sort_narabikae"));
    winFontInit();
    width = xo + (220.0f - width);
    winFontSet((Vec){width, 20.0f + ((yo - 92.0f) - 10.0f), 0.0f}, (Vec){0.7f, 0.7f, 0.7f}, black, msgSearch("msg_menu_sort_narabikae"));
    winIconInit();
    winIconSet(0x217, (Vec){width - 30.0f, 20.0f + ((yo - 100.0f) - 10.0f), 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, white2);
    if (w->box[0] < 320.0f && w->box[2] > -240.0f) {
        winBookGX(w, 0);
    }
}

void itemUseDisp(WinMgrEntry* entry) {
    ItemWork* w = (ItemWork*)winGetPtr();
    GXColor black = {0, 0, 0, 255};
    GXColor white2;
    GXColor white3;
    GXColor white = {255, 255, 255, 255};
    WinPartyDt* list[11];
    const char* name;
    s32 party;
    s32 n;
    s32 i;
    s32 off;
    s32 off3;
    s32 gray;
    f32 yoff;

    white2 = white;
    white3 = white2;
    if (!winMgrAction(w->winId0)) {
        party = !marioBgmodeChk() ? marioGetParty() : marioGetPtr()->prevPartyMemberId[0];
        n = 0;
        for (i = 0; i < 7; i++) {
            if (party == winPartyDt[i].partyId) {
                list[n++] = &winPartyDt[i];
            }
        }
        for (i = 0; i < 7; i++) {
            if (party != winPartyDt[i].partyId) {
                list[n++] = &winPartyDt[i];
            }
        }
        for (i = 0; i < w->partyCount + 1; i++) {
            off = i * 22;
            if (i == 0) {
                yoff = 0.0f;
            } else if (i == 1) {
                yoff = -16.0f;
            } else {
                yoff = -28.0f;
            }
            gray = 0;
            if (w->blink) {
                if (i == w->sel) {
                    black = (GXColor){0, 0, 0, 255};
                } else {
                    black = (GXColor){0x80, 0x80, 0x80, 255};
                    gray = 1;
                }
            }
            if (i == 0) {
                if (w->blink % 20 > 15 && i == w->sel) {
                    continue;
                }
                if (gray) {
                    winIconGrayInit();
                } else {
                    winIconInit();
                }
                winIconSet(0x19E, (Vec){entry->x + 30, entry->y - 20 - off, 0.0f}, (Vec){0.65f, 0.65f, 0.65f}, white3);
                winTexInit(w->res->tex->tpl);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
                winTexSet(0xAF, (Vec){entry->x + 220 + 0.9f * FontGetMessageWidth("\202g\202o")  / 2, entry->y - 19 - off, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xCB, 0x8C, 0xA2, 0xFE});
                winTexSet(0xAF, (Vec){entry->x + 220 + 0.9f * FontGetMessageWidth("\202g\202o")  / 2, entry->y - 19 - (off3 = (i + 1) * 22), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xCB, 0xBE, 0x89, 0xFE});
                winFontInit();
                winFontSet((Vec){entry->x + 50, entry->y - 8 - off, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, msgSearch("name_mario\000"));
                winFontSet((Vec){entry->x + 220, entry->y - 8 - off, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "\202g\202o");
                winFontSetR((Vec){entry->x + 245, entry->y - 8 - off, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%d", ((s32 (*)(void))pouchGetHP)());
                winFontSetR((Vec){entry->x + 267, entry->y - 8 - off, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, black, "\201^");
                winFontSet((Vec){entry->x + 310, entry->y - 10 - off, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, black, "%d", ((s32 (*)(void))pouchGetMaxHP)());
                if (*(u8*)&itemDataTable[w->f2D4].fp_restored) {
                    if (w->blink % 20 > 15) {
                        continue;
                    }
                    black = (GXColor){0, 0, 0, 255};
                }
                winFontInit();
                winFontSet((Vec){entry->x + 220, entry->y - 8 - off3, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "\202e\202o");
                winFontSetR((Vec){entry->x + 245, entry->y - 8 - off3, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%d", ((s32 (*)(void))pouchGetFP)());
                winFontSetR((Vec){entry->x + 267, entry->y - 8 - off3, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, black, "\201^");
                winFontSet((Vec){entry->x + 310, entry->y - 10 - off3, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, black, "%d", ((s32 (*)(void))pouchGetMaxFP)());
            } else {
                name = list[i - 1]->partyId != 4 ? msgSearch(list[i - 1]->name) : pouchGetYoshiName();
                if (w->blink % 20 > 15 && i == w->sel) {
                    continue;
                }
                winTexInit(w->res->tex->tpl);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
                winTexSet(0xAF, (Vec){entry->x + 220 + 0.9f * FontGetMessageWidth("\202g\202o")  / 2, (yoff + (entry->y - 8 - i * 28)) - 14.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xCB, 0x8C, 0xA2, 0xF4});
                if (gray) {
                    winIconGrayInit();
                } else {
                    winIconInit();
                }
                winIconSet(list[i - 1]->nameMsgId, (Vec){entry->x + 30, yoff + (entry->y - 20 - i * 28), 0.0f}, (Vec){0.65f, 0.65f, 0.65f}, white3);
                winFontInit();
                winFontSet((Vec){entry->x + 50, yoff + (entry->y - 8 - i * 28), 0.0f}, (Vec){FontGetMessageWidth(name) < 160.0f ? 1.0f : 160.0f / FontGetMessageWidth(name), 1.0f, 1.0f}, black, name);
                winFontSet((Vec){entry->x + 220, yoff + (entry->y - 8 - i * 28), 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "\202g\202o");
                winFontSetR((Vec){entry->x + 245, yoff + (entry->y - 8 - i * 28), 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%d", pouchGetPtr()->partyData[list[i - 1]->partyId].currentHP);
                winFontSetR((Vec){entry->x + 267, yoff + (entry->y - 8 - i * 28), 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, black, "\201^");
                winFontSet((Vec){entry->x + 310, (yoff + (entry->y - 8 - i * 28)) - 2.0f, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, black, "%d", pouchGetPtr()->partyData[list[i - 1]->partyId].maximumHP);
            }
        }
        if (w->partyCount > 1) {
            winIconInit();
            for (i = 2; i < 30; i++) {
                winIconSet(0x1B7, (Vec){entry->x + (entry->width / 31) * i, entry->y - 84, 0.0f}, (Vec){0.15f, 0.15f, 0.15f}, black);
            }
        }
    }
    winTexInit(w->res->tex->tpl);
    winTexSet(0, (Vec){2.0f + w->f150, w->f154 - 2.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 0x80});
    winTexSet(0, (Vec){w->f150, w->f154, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
}

void itemUseDisp2(WinMgrEntry* entry) {
    ItemWork* wp = (ItemWork*)winGetPtr();
    GXColor color = {0, 0, 0, 255};
    if (!winMgrAction(wp->winId1)) {
        const char* msg = msgSearch("msg_window_select_5");
        f32 w = (f32)FontGetMessageWidth(msg);
        winFontInit();
        winFontSet((Vec){(f32)entry->x + ((f32)entry->width - w) / 2.0f, 134.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, color, msg);
    }
}


__declspec(section ".data") u32 gap_05_80374D0C_data[1] = {0};
