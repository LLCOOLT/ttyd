#include "manager/winmgr.h"
#include "data/item_data.h"
#include "driver/dispdrv.h"
#include "driver/icondrv.h"
#include "driver/msgdrv.h"
#include "driver/windowdrv.h"
#include "evt/evt_badgeshop.h"
#include "evt/evt_johoya.h"
#include "evt/evt_lottery.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include "mario/mario_party.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "memory.h"
#include "pmario_sound.h"
#include "system.h"
#include <stdio.h>
#include <string.h>

typedef struct WinMgrSelectTbl {
    u16 numDescriptors; // 0x0
    WinMgrDesc* descriptors; // 0x4
} WinMgrSelectTbl;

extern ItemData itemDataTable[];
extern u16 menu_skip_list[];
extern BadgeShopWork* bdsw;
extern s32 badge_bottakuru_table[];
extern s32 badge_bottakuru100_table[];
extern InformantWork _jdt;
void statusWinForceOpen(void);
void winFontInit(void);
void winFontSet(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetEdge(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void statusWinForceOff(void);
s16 johoya_get(u8* table, s16 id);
void qqsort(void* base, u32 n, u32 size, int (*compare)(void*, void*));
void winIconInit(void);
void winIconGrayInit(void);
void winIconSet(u32 id, Vec translate, Vec scale, GXColor color);

#define INTPL ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)

// local prototypes
void select_main(WinMgrEntry* entry);
void select_disp(WinMgrEntry* entry);
void select_disp_party(WinMgrEntry* entry);
void select_disp_mario(WinMgrEntry* entry);
void select_disp_luigi(WinMgrEntry* entry);
void select_disp2(WinMgrEntry* entry);
void select_main3(WinMgrEntry* entry);
void select_disp3(WinMgrEntry* entry);
void select_disp3_party(WinMgrEntry* entry);
void select_disp3_mario(WinMgrEntry* entry);
void winMgrDisp(CameraId camId, void* param);
void winMgrSeq(WinMgrEntry* entry);
int unk_802379e4(void* a, void* b);
int unk_80237a2c(void* a, void* b);
s32 unk_80237448(WinMgrSelect* sel);

//.data
WinMgrDesc select_desc[] = {
    {0, 1, 8, -24, 116, 300, 240, {0xFF, 0xFF, 0xFF, 0xFF}, select_main, select_disp},
    {2, 0, 8, -280, 120, 240, 45, {0xFF, 0xFF, 0xFF, 0xFF}, NULL, select_disp2},
    {0, 0, 8, -240, -130, 500, 80, {0xFF, 0xFF, 0xFF, 0xFF}, select_main3, select_disp3},
    {0, 1, 8, -24, 116, 300, 240, {0xFF, 0xFF, 0xFF, 0xFF}, select_main, select_disp},
    {2, 0, 8, -280, 120, 240, 69, {0xFF, 0xFF, 0xFF, 0xFF}, NULL, select_disp2},
    {0, 0, 8, -240, -130, 500, 80, {0xFF, 0xFF, 0xFF, 0xFF}, select_main3, select_disp3},
};

WinMgrDesc select_party_desc[] = {
    {0, 4, 8, -24, 116, 300, 240, {0xFF, 0xFF, 0xFF, 0xFF}, select_main, select_disp_party},
    {2, 0, 8, -280, 120, 240, 69, {0xFF, 0xFF, 0xFF, 0xFF}, NULL, select_disp2},
    {0, 0, 8, -240, -130, 500, 80, {0xFF, 0xFF, 0xFF, 0xFF}, select_main3, select_disp3_party},
};

WinMgrDesc select_mario_desc[] = {
    {0, 5, 8, -24, 116, 300, 240, {0xFF, 0xFF, 0xFF, 0xFF}, select_main, select_disp_mario},
    {2, 0, 8, -280, 120, 240, 69, {0xFF, 0xFF, 0xFF, 0xFF}, NULL, select_disp2},
    {0, 0, 8, -240, -130, 500, 80, {0xFF, 0xFF, 0xFF, 0xFF}, select_main3, select_disp3_mario},
};

WinMgrDesc select_luigi_desc[] = {
    {0, 1, 8, -24, 116, 300, 240, {0xFF, 0xFF, 0xFF, 0xFF}, select_main, select_disp_luigi},
    {2, 0, 8, -280, 120, 240, 45, {0xFF, 0xFF, 0xFF, 0xFF}, NULL, select_disp2},
};

WinMgrDesc select_johoya_perfect_desc[] = {
    {0, 1, 8, -24, 116, 300, 240, {0xFF, 0xFF, 0xFF, 0xFF}, select_main, select_disp_luigi},
    {2, 0, 8, -280, 120, 240, 45, {0xFF, 0xFF, 0xFF, 0xFF}, NULL, select_disp2},
};

WinMgrSelectTbl select_desc_tbl[] = {
    {3, select_desc},
    {3, select_desc},
    {3, select_desc},
    {3, select_desc},
    {3, select_desc},
    {3, select_desc},
    {3, select_party_desc},
    {3, select_party_desc},
    {3, select_party_desc},
    {3, select_mario_desc},
    {3, select_mario_desc},
    {3, select_desc},
    {3, select_desc},
    {3, &select_desc[3]},
    {3, select_desc},
    {3, select_desc},
    {3, &select_desc[3]},
    {2, select_johoya_perfect_desc},
    {2, select_luigi_desc},
};

//.sbss
static WinMgrWork work;
static s16* mario_status_point_table[3];

//.sdata
static WinMgrWork* wp = &work;
static u16 party_id_table[] = {1, 2, 5, 4, 6, 3, 7, 0};
static u16 party_icon_table[] = {0x155, 0x156, 0x15F, 0x158, 0x160, 0x157, 0x161, 0};
static const char* party_labelname_table[] = {"_kur", "_nok", "_win", "_yos", "_viv", "_bom", "_chu"};
static s32 mario_status_icon_table[] = {0x19F, 0x1A0, 0x1A1};
static const char* mario_status_labelname_table[] = {"_hp", "_fp", "_bp"};
static const char* mario_status_name_table[] = {"\x82\x67\x82\x6F", "\x82\x65\x82\x6F", "\x82\x61\x82\x6F"};
static s32 mario_status_henka_table[] = {5, 5, 3};
s32 mario_status_max_table[] = {200, 200, 99};

USER_FUNC(unk_80239b2c) {
    s32* args = event->args;
    PouchData* pouch;
    u16* p;
    s32 max;

    pouch = pouchGetPtr();
    for (p = party_id_table; *p != 0; p++) {
        if (partyChkJoin(*p)) {
            if (!evtGetValue(event, GSWF(1186))) {
                max = pouch->partyData[*p].techLevel >= 1 ? 1 : 0;
            }
            else {
                max = pouch->partyData[*p].techLevel >= 2 ? 2 : 0;
            }
            if (max == 0) {
                evtSetValue(event, args[0], 1);
                return EVT_RETURN_DONE;
            }
        }
    }
    evtSetValue(event, args[0], 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(unk_802399f8) {
    s32* args = event->args;
    PouchData* pouch;
    u16* p;
    s32 num, canRank, hasRank;
    s32 max;

    pouch = pouchGetPtr();
    canRank = 0;
    num = 0;
    hasRank = 0;
    for (p = party_id_table; *p != 0; p++) {
        if (partyChkJoin(*p)) {
            num++;
            if (pouch->partyData[*p].techLevel != 0) {
                hasRank = 1;
            }
            if (!evtGetValue(event, GSWF(1186))) {
                max = pouch->partyData[*p].techLevel >= 1 ? 1 : 0;
            }
            else {
                max = pouch->partyData[*p].techLevel >= 2 ? 2 : 0;
            }
            if (max == 0) {
                canRank = 1;
            }
        }
    }
    if (num > 1 && canRank && hasRank) {
        evtSetValue(event, args[0], 1);
    }
    else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}

void winMgrInit(void) {
    wp->mNumEntries = 32;
    wp->mEntries = (WinMgrEntry*)__memAlloc(HEAP_DEFAULT, wp->mNumEntries * sizeof(WinMgrEntry));
    memset(wp->mEntries, 0, wp->mNumEntries * sizeof(WinMgrEntry));
}

void winMgrReInit(void) {
    memset(wp->mEntries, 0, wp->mNumEntries * sizeof(WinMgrEntry));
}

void winMgrDisp(CameraId camId, void* param) {
    WinMgrEntry* entry = param;
    Mtx rot;
    Mtx scale;

    PSMTXRotRad(rot, 'z', 0.017453292f * entry->rotation);
    PSMTXScale(scale, entry->scale, entry->scale, entry->scale);
    PSMTXConcat(rot, scale, scale);
    windowDispGX2_Waku_col(scale, 0, (GXColor){entry->description->color.r, entry->description->color.g, entry->description->color.b, entry->alpha},
                           entry->x, entry->y, entry->width, entry->height, 20.0f);
    switch (entry->description->dispType) {
        case 0:
        case 2:
            break;
        case 1:
            windowDispGX2_Waku_col(scale, 0, (GXColor){0x2B, 0xA4, 0xFF, entry->alpha}, entry->x + (entry->width - 150) / 2, entry->y + 14, 150.0f, 28.0f, 8.0f);
            break;
        case 3:
            windowDispGX2_Waku_col(scale, 0, (GXColor){0x2B, 0xA4, 0xFF, entry->alpha}, entry->x + 10, entry->y + 14, 100.0f, 28.0f, 8.0f);
            windowDispGX2_Waku_col(scale, 0, (GXColor){0x2B, 0xA4, 0xFF, entry->alpha}, entry->x + entry->width / 2 - 10, entry->y + 14, 100.0f, 28.0f, 8.0f);
            break;
        case 4:
        case 5:
            windowDispGX2_Waku_col(scale, 0, (GXColor){0x2B, 0xA4, 0xFF, entry->alpha}, entry->x + ((entry->width * 3 / 5 - 120) * 2) / 3, entry->y + 14, 120.0f, 28.0f, 8.0f);
            windowDispGX2_Waku_col(scale, 0, (GXColor){0x2B, 0xA4, 0xFF, entry->alpha}, entry->x + entry->width * 3 / 5 + (entry->width * 2 / 5 - 85) / 3, entry->y + 14, 85.0f, 28.0f, 8.0f);
            break;
    }
    if (entry->description->disp) {
        entry->description->disp(entry);
    }
}

void winMgrMain(void) {
    WinMgrEntry* entry;
    int i;

    entry = wp->mEntries;
    for (i = 0; i < wp->mNumEntries; i++, entry++) {
        if (entry->flags & 1) {
            winMgrSeq(entry);
            if (entry->description->main) {
                entry->description->main(entry);
            }
            if (entry->flags & 2) {
                dispEntry((CameraId)entry->description->camId, entry->priority + 300, 0, winMgrDisp, entry);
            }
        }
    }
}

void winMgrSeq(WinMgrEntry* entry) {
    entry->flags |= 4;
    switch (entry->description->type) {
        case 0:
            switch (entry->state) {
                case 0:
                    entry->flags &= ~4;
                    break;
                case 1:
                    entry->flags |= 2;
                    entry->rotation = INTPL(30.0f, 0.0f, 12, entry->timer, 8);
                    entry->scale = INTPL(0.0f, 1.0f, 12, entry->timer, 8);
                    entry->alpha = 255;
                    entry->timer++;
                    if (entry->timer > 8) {
                        entry->state = 0;
                    }
                    break;
                case 2:
                    entry->rotation = INTPL(0.0f, 30.0f, 12, entry->timer, 8);
                    entry->scale = INTPL(1.0f, 0.0f, 12, entry->timer, 8);
                    entry->alpha = 255;
                    entry->timer++;
                    if (entry->timer > 8) {
                        entry->state = 0;
                        entry->flags &= ~2;
                        if (entry->flags & 8) {
                            entry->flags &= ~1;
                        }
                    }
                    break;
            }
            break;
        case 1:
            switch (entry->state) {
                case 0:
                    entry->flags &= ~4;
                    break;
                case 1:
                    entry->flags |= 2;
                    entry->rotation = 0.0f;
                    entry->scale = INTPL(0.0f, 1.0f, 12, entry->timer, 8);
                    entry->alpha = INTPL(0.0f, 255.0f, 12, entry->timer, 8);
                    entry->timer++;
                    if (entry->timer > 8) {
                        entry->state = 0;
                    }
                    break;
                case 2:
                    entry->rotation = 0.0f;
                    entry->scale = 1.0f;
                    entry->alpha = INTPL(255.0f, 0.0f, 12, entry->timer, 8);
                    entry->timer++;
                    if (entry->timer > 8) {
                        entry->state = 0;
                        entry->flags &= ~2;
                        if (entry->flags & 8) {
                            entry->flags &= ~1;
                        }
                    }
                    break;
            }
            break;
        case 2:
            switch (entry->state) {
                case 0:
                    entry->flags &= ~4;
                    break;
                case 1:
                    entry->flags |= 2;
                    entry->rotation = 0.0f;
                    entry->scale = 1.0f;
                    entry->alpha = 255;
                    entry->state = 0;
                    break;
                case 2:
                    entry->flags &= ~2;
                    entry->rotation = 0.0f;
                    entry->scale = 1.0f;
                    entry->alpha = 255;
                    entry->state = 0;
                    if (entry->flags & 8) {
                        entry->flags &= ~1;
                    }
                    break;
            }
            break;
    }
}

s32 winMgrEntry(WinMgrDesc* desc) {
    WinMgrEntry* entry;
    int i;

    entry = wp->mEntries;
    for (i = 0; i < wp->mNumEntries; i++, entry++) {
        if (!(entry->flags & 1)) {
            break;
        }
    }
    entry->flags = 0;
    entry->flags |= 1;
    entry->state = 0;
    entry->timer = 0;
    entry->description = desc;
    entry->x = entry->description->x;
    entry->y = entry->description->y;
    entry->width = entry->description->width;
    entry->height = entry->description->height;
    entry->priority = 0;
    entry->param = NULL;
    entry->scroll = 0;
    entry->lines = 0;
    return i;
}

void winMgrSetParam(s32 id, void* param) {
    WinMgrEntry* entry;

    entry = &wp->mEntries[id];
    if (entry->flags & 1) {
        entry->param = param;
    }
}

void winMgrOpen(s32 id) {
    WinMgrEntry* entry;

    entry = &wp->mEntries[id];
    if (entry->flags & 1) {
        entry->state = 1;
        entry->timer = 0;
        entry->scroll = 0;
        entry->lines = 0;
        entry->msg = NULL;
    }
}

void winMgrClose(s32 id) {
    WinMgrEntry* entry;

    entry = &wp->mEntries[id];
    if (entry->flags & 1) {
        entry->state = 2;
        entry->timer = 0;
    }
}

void winMgrCloseAutoDelete(s32 id) {
    WinMgrEntry* entry;

    entry = &wp->mEntries[id];
    if (entry->flags & 1) {
        entry->state = 2;
        entry->timer = 0;
        entry->flags |= 8;
    }
}

void winMgrDelete(s32 id) {
    wp->mEntries[id].flags &= ~1;
}

BOOL winMgrAction(s32 id) {
    return (wp->mEntries[id].flags >> 2) & 1;
}

void winMgrSetSize(s32 id, s32 x, s32 y, s32 width, s32 height) {
    WinMgrEntry* entry;

    entry = &wp->mEntries[id];
    if (entry->flags & 1) {
        entry->x = x;
        entry->y = y;
        entry->width = width;
        entry->height = height;
    }
}

void winMgrSetPriority(s32 id, s32 priority) {
    WinMgrEntry* entry;

    entry = &wp->mEntries[id];
    if (entry->flags & 1) {
        entry->priority = priority;
    }
}

WinMgrEntry* winMgrGetPtr(s32 id) {
    return &wp->mEntries[id];
}

void winMgrHelpInit(WinMgrEntry* entry) {
    entry->scroll = 0;
    entry->lines = 0;
    entry->msg = NULL;
}

void winMgrHelpMain(WinMgrEntry* entry) {
    u16 lines = 0;

    if (!(entry->flags & 4)) {
        if (entry->msg) {
            FontGetMessageWidthLine(entry->msg, &lines);
            entry->lines = lines + 1;
        }
        if (entry->lines > 2) {
            if (keyGetDirTrg(0) & 0x100) {
                entry->scroll -= 2;
                if (entry->scroll < 0) {
                    entry->scroll = 0;
                }
            }
            else if (keyGetDirTrg(0) & 0x200) {
                if ((entry->lines + 1) / 2 - 1 > (entry->scroll + 1) / 2) {
                    entry->scroll += 2;
                }
            }
        }
    }
}

void winMgrHelpDraw(WinMgrEntry* entry) {
    Mtx mtx;
    Mtx scale;
    char buf[0x400];

    if (!(entry->flags & 4)) {
        GXSetScissor(0, 384, 608, 56);
        if (!strcmp(entry->msg, msgSearch("msg_lottery_number"))) {
            sprintf(buf, entry->msg, *(s16*)((u8*)lotteryGetPtr() + 0x20));
            FontDrawStart();
            FontDrawMessage(-210, -144.0f + 28.0f * entry->scroll, buf);
        }
        else {
            FontDrawStart();
            FontDrawMessage(-210, -144.0f + 28.0f * entry->scroll, entry->msg);
        }
        GXSetScissor(0, 0, 608, 480);
        if (entry->lines > 2) {
            if (entry->scroll == 0) {
                if ((gp->retraceCount & 31) < 20) {
                    PSMTXTrans(mtx, entry->x + entry->width - 12, entry->y - entry->height - 4, 0.0f);
                    PSMTXScale(scale, 0.6f, 0.6f, 0.6f);
                    PSMTXConcat(mtx, scale, mtx);
                    iconDispGx2(mtx, 16, 0x1B6);
                }
            }
            else if (entry->lines == entry->scroll + 2) {
                if ((gp->retraceCount & 31) < 20) {
                    PSMTXTrans(mtx, entry->x + entry->width - 12, entry->y - entry->height + 44, 0.0f);
                    PSMTXScale(scale, 0.6f, 0.6f, 0.6f);
                    PSMTXConcat(mtx, scale, mtx);
                    iconDispGx2(mtx, 16, 0x1B5);
                }
            }
            else if ((gp->retraceCount & 31) < 20) {
                PSMTXTrans(mtx, entry->x + entry->width - 12, entry->y - entry->height + 44, 0.0f);
                PSMTXScale(scale, 0.6f, 0.6f, 0.6f);
                PSMTXConcat(mtx, scale, mtx);
                iconDispGx2(mtx, 16, 0x1B5);
                PSMTXTrans(mtx, entry->x + entry->width - 12, entry->y - entry->height - 4, 0.0f);
                PSMTXScale(scale, 0.6f, 0.6f, 0.6f);
                PSMTXConcat(mtx, scale, mtx);
                iconDispGx2(mtx, 16, 0x1B6);
            }
            PSMTXTrans(mtx, entry->x + entry->width - 12, entry->y - entry->height + 10, 0.0f);
            PSMTXScale(scale, 0.6f, 0.6f, 0.6f);
            PSMTXConcat(mtx, scale, mtx);
            iconDispGx2(mtx, 16, 0x70);
        }
    }
}

WinMgrSelect* winMgrSelectEntry(s32 type, s32 a2, BOOL a3) {
    WinMgrDesc* desc;
    WinMgrSelect* sel;
    InformantWork* jdt;
    PouchData* pouch;
    WinMgrSelectTbl* table;
    WinMgrDesc* d;
    u16 id;
    s32 i, j, n;
    s32 cnt, over;
    u8* tbl;
    s32* list;

    pouch = pouchGetPtr();
    jdt = &_jdt;
    sel = __memAlloc(HEAP_DEFAULT, sizeof(WinMgrSelect));
    memset(sel, 0, sizeof(WinMgrSelect));
    sel->type = type;
    sel->cursor = 0;
    sel->scrollTop = 0;
    sel->field_0x18 = 0.0f;
    sel->field_0x14 = 0.0f;
    sel->field_0x1C = 0.0f;
    sel->field_0x38 = a2;
    if (a3) {
        sel->flags |= 0x100;
    }
    n = type;
    if (n < 0) {
        n = 0;
    }
    sel->numDescriptors = select_desc_tbl[n].numDescriptors;
    d = select_desc_tbl[n].descriptors;
    for (i = 0; i < sel->numDescriptors; i++) {
        sel->descriptorId[i] = winMgrEntry(d++);
        winMgrSetParam(sel->descriptorId[i], sel);
    }
    desc = select_desc_tbl[n].descriptors;
    sel->field_0x14 = desc->x;
    sel->field_0x18 = desc->y - 54;

    switch (sel->type) {
        case 0:
            sel->items = __memAlloc(HEAP_DEFAULT, 0x1E8);
            memset(sel->items, 0, 0x1E8);
            sel->numItems = 0;
            if (a2) {
                sel->items[sel->numItems++].id = a2;
            }
            for (i = 0; i < 121; i++) {
                id = (u16)pouchKeyItem(i);
                if (id) {
                    for (j = 0; j < 19; j++) {
                        if (id == menu_skip_list[j]) {
                            break;
                        }
                    }
                    if (j >= 19) {
                        sel->items[sel->numItems++].id = id;
                    }
                }
            }
            break;
        case 1:
        case 3:
        case 4:
            sel->items = __memAlloc(HEAP_DEFAULT, 0x54);
            memset(sel->items, 0, 0x54);
            sel->numItems = 0;
            if (a2) {
                sel->items[sel->numItems++].id = a2;
            }
            for (i = 0; i < 20; i++) {
                id = (u16)pouchHaveItem(i);
                if (id) {
                    sel->items[sel->numItems++].id = id;
                }
            }
            break;
        case 2:
        case 12:
            sel->items = __memAlloc(HEAP_DEFAULT, 0x324);
            memset(sel->items, 0, 0x324);
            sel->numItems = 0;
            if (a2) {
                sel->items[sel->numItems++].id = a2;
            }
            for (i = 0; i < 200; i++) {
                id = (u16)pouchHaveBadge(i);
                if (id) {
                    sel->items[sel->numItems++].id = id;
                }
            }
            break;
        case 5:
            sel->items = __memAlloc(HEAP_DEFAULT, 0x84);
            memset(sel->items, 0, 0x84);
            sel->numItems = 0;
            if (a2) {
                sel->items[sel->numItems++].id = a2;
            }
            for (i = 0; i < 32; i++) {
                id = (u16)pouchKeepItem(i);
                if (id) {
                    sel->items[sel->numItems++].id = id;
                }
            }
            break;
        case 6:
        case 7: {
            u16* p;
            sel->items = __memAlloc(HEAP_DEFAULT, 0x1C);
            memset(sel->items, 0, 0x1C);
            i = 0;
            p = party_id_table;
            sel->numItems = i;
            for (; *p != 0; p++, i++) {
                if (partyChkJoin(*p)) {
                    sel->items[sel->numItems].id = i;
                    if (!evtGetValue(NULL, GSWF(1186))) {
                        if (pouch->partyData[*p].techLevel >= 1) {
                            sel->items[sel->numItems].flags |= 3;
                        }
                    }
                    else {
                        if (pouch->partyData[*p].techLevel >= 2) {
                            sel->items[sel->numItems].flags |= 3;
                        }
                    }
                    sel->numItems++;
                }
            }
            break;
        }
        case 8: {
            u16* p;
            sel->items = __memAlloc(HEAP_DEFAULT, 0x1C);
            memset(sel->items, 0, 0x1C);
            i = 0;
            p = party_id_table;
            sel->numItems = i;
            for (; *p != 0; p++, i++) {
                if (partyChkJoin(*p) && *p != evtGetValue(NULL, GW(1))) {
                    sel->items[sel->numItems].id = i;
                    if (pouch->partyData[*p].techLevel == 0) {
                        sel->items[sel->numItems].flags |= 3;
                    }
                    sel->numItems++;
                }
            }
            break;
        }
        case 9:
            mario_status_point_table[0] = &pouchGetPtr()->baseMaxHP;
            mario_status_point_table[1] = &pouchGetPtr()->baseMaxFP;
            mario_status_point_table[2] = &pouchGetPtr()->maximumBP;
            sel->items = __memAlloc(HEAP_DEFAULT, 0xC);
            memset(sel->items, 0, 0xC);
            for (i = 0; i < 3; i++) {
                sel->items[i].id = i;
                cnt = 0;
                over = 0;
                for (j = 0; j < 3; j++) {
                    if (j != sel->items[i].id) {
                        if (*mario_status_point_table[j] - mario_status_henka_table[j] <= 0) {
                            cnt++;
                        }
                    }
                    else if (*mario_status_point_table[j] + mario_status_henka_table[j] > mario_status_max_table[j]) {
                        over = 1;
                    }
                }
                if (cnt == 2 || over) {
                    if (over) {
                        sel->items[i].flags |= 7;
                    }
                    else {
                        sel->items[i].flags |= 3;
                    }
                }
            }
            sel->numItems = 3;
            break;
        case 10:
            mario_status_point_table[0] = &pouchGetPtr()->baseMaxHP;
            mario_status_point_table[1] = &pouchGetPtr()->baseMaxFP;
            mario_status_point_table[2] = &pouchGetPtr()->maximumBP;
            sel->items = __memAlloc(HEAP_DEFAULT, 8);
            memset(sel->items, 0, 8);
            sel->numItems = 0;
            for (i = 0; i < 3; i++) {
                if (i != evtGetValue(NULL, GW(1))) {
                    sel->items[sel->numItems].id = i;
                    if (*mario_status_point_table[i] - mario_status_henka_table[i] <= 0) {
                        sel->items[sel->numItems].flags |= 3;
                    }
                    sel->numItems++;
                }
            }
            break;
        case 11:
            sel->items = __memAlloc(HEAP_DEFAULT, 0x18C);
            memset(sel->items, 0, 0x18C);
            sel->numItems = 0;
            for (i = 0; i < 99; i++) {
                n = (s16)badgeShop_get(bdsw->bargain_table, i + 240);
                if (n - badgeShop_ThrowCheck(i + 240) > 0) {
                    sel->items[sel->numItems++].id = i + 240;
                }
            }
            qqsort(sel->items, sel->numItems, 4, unk_802379e4);
            break;
        case 13:
            n = getBadgeStarmaniacTableMaxCount();
            sel->items = __memAlloc(HEAP_DEFAULT, n * 4);
            memset(sel->items, 0, n * 4);
            sel->numItems = 0;
            for (i = 0; i < 99; i++) {
                n = (s16)badgeShop_get(bdsw->starmaniac_table, i + 240);
                if (n - badgeShop_ThrowCheck(i + 240) > 0) {
                    sel->items[sel->numItems].id = i + 240;
                    if (itemDataTable[i + 240].star_piece_price > ((s32 (*)(void))pouchGetStarPiece)()) {
                        sel->items[sel->numItems].flags |= 3;
                    }
                    sel->numItems++;
                }
            }
            qqsort(sel->items, sel->numItems, 4, unk_80237a2c);
            break;
        case 14:
            sel->items = __memAlloc(HEAP_DEFAULT, 0x10);
            memset(sel->items, 0, 0x10);
            sel->numItems = 0;
            for (i = 0; i < 4; i++) {
                n = badge_bottakuru_table[evtGetValue(NULL, GSW(118) + i)];
                if (n) {
                    sel->items[sel->numItems++].id = n;
                }
            }
            break;
        case 15:
            n = getBadgeBottakuru100TableMaxCount();
            sel->items = __memAlloc(HEAP_DEFAULT, n * 4);
            memset(sel->items, 0, n * 4);
            sel->numItems = 0;
            for (i = 0; i < n; i++) {
                sel->items[sel->numItems++].id = badge_bottakuru100_table[i];
            }
            break;
        case 16:
            n = getBadgeBteresaTableMaxCount();
            sel->items = __memAlloc(HEAP_DEFAULT, n * 4);
            memset(sel->items, 0, n * 4);
            sel->numItems = 0;
            for (i = 0; i < 338; i++) {
                if ((s16)badgeShop_get(bdsw->bteresa_table, i + 1) > 0) {
                    sel->items[sel->numItems++].id = i + 1;
                }
            }
            break;
        case 17:
        case 18:
            if (sel->type == 17) {
                tbl = jdt->unk14.unkD;
            }
            else {
                tbl = jdt->unk14.unk1A;
            }
            sel->numItems = jdt->count;
            sel->items = __memAlloc(HEAP_DEFAULT, (sel->numItems + 1) * 4);
            memset(sel->items, 0, (sel->numItems + 1) * 4);
            for (i = 0; i < sel->numItems; i++) {
                sel->items[i].id = i;
                if (johoya_get(tbl, jdt->info[i].storyId)) {
                    sel->items[i].flags |= 1;
                }
            }
            break;
        default:
            if (type < 0) {
                n = 0;
                while (((s32*)type)[n++] != -1) {
                }
                sel->items = __memAlloc(HEAP_DEFAULT, (n + 1) * 4);
                memset(sel->items, 0, (n + 1) * 4);
                sel->numItems = 0;
                if (a2) {
                    sel->items[sel->numItems++].id = a2;
                }
                for (list = (s32*)type, i = 0; *list != -1; list++, i++) {
                    sel->items[sel->numItems++].id = ((s32*)type)[i];
                }
            }
            break;
    }
    if (sel->numItems < 8) {
        winMgrSetSize(sel->descriptorId[0], desc->x, desc->y, desc->width, desc->height - (8 - sel->numItems) * 24);
    }
    return sel;
}

int unk_80237a2c(void* a, void* b) {
    u16 x = itemDataTable[((WinMgrSelectItem*)a)->id].star_piece_price;
    u16 y = itemDataTable[((WinMgrSelectItem*)b)->id].star_piece_price;
    if (x > y) {
        return 1;
    }
    return -(x < y);
}

int unk_802379e4(void* a, void* b) {
    s16 x = itemDataTable[((WinMgrSelectItem*)a)->id].type_sort_order;
    s16 y = itemDataTable[((WinMgrSelectItem*)b)->id].type_sort_order;
    if (x > y) {
        return 1;
    }
    return -(x < y);
}

s32 winMgrSelect(WinMgrSelect* sel) {
    if (sel->flags & 0x1000) {
        if (sel->flags & 0x2000) {
            return -1;
        }
        if (sel->field_0x38 && sel->cursor == 0 && (sel->flags & 0x100)) {
            return -1;
        }
        return sel->items[sel->cursor].id;
    }
    return 0;
}

s32 winMgrSelectOther(WinMgrSelect* sel, EventEntry* evt) {
    InformantWork* jdt = &_jdt;
    s32 id;
    const char* name;
    char buf[0x40];

    if (sel->flags & 0x1000) {
    if (sel->flags & 0x2000) {
        return -1;
    }
    id = sel->items[sel->cursor].id;
    switch (sel->type) {
        case 6:
        case 7:
            evt->lwData[1] = party_id_table[id];
            switch (id) {
                case 0:
                    name = msgSearch("name_party0");
                    break;
                case 1:
                    name = msgSearch("name_party1");
                    break;
                case 2:
                    name = msgSearch("name_party4");
                    break;
                case 3:
                    name = pouchGetYoshiName();
                    break;
                case 4:
                    name = msgSearch("name_party5");
                    break;
                case 5:
                    name = msgSearch("name_party2");
                    break;
                case 6:
                    name = msgSearch("name_party6");
                    break;
            }
            evt->lwData[3] = (s32)name;
            break;
        case 8:
            evt->lwData[2] = party_id_table[id];
            switch (id) {
                case 0:
                    name = msgSearch("name_party0");
                    break;
                case 1:
                    name = msgSearch("name_party1");
                    break;
                case 2:
                    name = msgSearch("name_party4");
                    break;
                case 3:
                    name = pouchGetYoshiName();
                    break;
                case 4:
                    name = msgSearch("name_party5");
                    break;
                case 5:
                    name = msgSearch("name_party2");
                    break;
                case 6:
                    name = msgSearch("name_party6");
                    break;
            }
            evt->lwData[4] = (s32)name;
            break;
        case 9:
            evt->lwData[1] = id;
            evt->lwData[2] = (s32)mario_status_name_table[id];
            evt->lwData[5] = *mario_status_point_table[0];
            evt->lwData[6] = *mario_status_point_table[1];
            evt->lwData[7] = *mario_status_point_table[2];
            evt->lwData[5 + id] += mario_status_henka_table[id];
            break;
        case 10:
            evt->lwData[1] = id;
            evt->lwData[3] = (s32)mario_status_name_table[id];
            evt->lwData[5 + id] -= mario_status_henka_table[id];
            break;
        case 11:
            evt->lwData[1] = id;
            evt->lwData[2] = (s32)itemDataTable[id].id;
            evt->lwData[3] = itemDataTable[id].buy_price;
            evt->lwData[4] = itemDataTable[id].bp_cost;
            break;
        case 12:
            evt->lwData[1] = id;
            evt->lwData[2] = (s32)itemDataTable[id].id;
            evt->lwData[3] = itemDataTable[id].sell_price;
            evt->lwData[4] = sel->cursor;
            break;
        case 13:
            evt->lwData[1] = id;
            evt->lwData[2] = (s32)itemDataTable[id].id;
            evt->lwData[3] = itemDataTable[id].star_piece_price;
            evt->lwData[4] = itemDataTable[id].bp_cost;
            break;
        case 14:
            evt->lwData[1] = id;
            evt->lwData[2] = (s32)itemDataTable[id].id;
            evt->lwData[3] = (itemDataTable[id].buy_price * 12) / 10;
            evt->lwData[4] = itemDataTable[id].bp_cost;
            break;
        case 15:
            evt->lwData[1] = id;
            evt->lwData[2] = (s32)itemDataTable[id].id;
            evt->lwData[3] = ((evtGetValue(NULL, GSW(1321)) + 11) * itemDataTable[id].buy_price) / 10;
            evt->lwData[4] = itemDataTable[id].bp_cost;
            break;
        case 16:
            evt->lwData[1] = id;
            evt->lwData[2] = (s32)itemDataTable[id].id;
            evt->lwData[3] = (itemDataTable[id].buy_price * 2 + 2) / 3;
            evt->lwData[4] = itemDataTable[id].bp_cost;
            break;
        case 17:
            sprintf((char*)jdt->infoEnd, "%s_%04d", jdt->prefix, jdt->info[id].storyId);
            sprintf(buf, "jperfect_title_%04d", jdt->info[id].storyId);
            *(s32*)jdt->unk10 = id;
            name = msgSearch(buf);
            evt->lwData[1] = (s32)jdt->infoEnd;
            evt->lwData[2] = (s32)name;
            evt->lwData[3] = strlen(name);
            if (johoya_get(jdt->unk14.unkD, jdt->info[id].storyId)) {
                evt->lwData[4] = 0;
            }
            else {
                evt->lwData[4] = jdt->info[id].unkA;
            }
            break;
        case 18:
            sprintf((char*)jdt->infoEnd, "%s_%04d", jdt->prefix, jdt->info[id].storyId);
            *(s32*)jdt->unk10 = id;
            evt->lwData[1] = (s32)jdt->infoEnd;
            evt->lwData[2] = jdt->info[id].initEndPos;
            evt->lwData[3] = jdt->info[id].tagEndPos;
            if (johoya_get(jdt->unk14.unk1A, jdt->info[id].storyId)) {
                evt->lwData[4] = 0;
            }
            else {
                evt->lwData[4] = 1;
            }
            break;
    }
    return 1;
    }
    return 0;
}

void winMgrSelectDelete(WinMgrSelect* sel) {
    __memFree(HEAP_DEFAULT, sel->items);
    __memFree(HEAP_DEFAULT, sel);
}

s32 unk_80237448(WinMgrSelect* sel) {
    return sel->cursor;
}

void select_main(WinMgrEntry* entry) {
    WinMgrSelect* sel = entry->param;
    s32 prev;
    s32 i;

    switch (sel->state) {
        case 0:
            for (i = 0; i < sel->numDescriptors; i++) {
                winMgrOpen(sel->descriptorId[i]);
            }
            if (sel->numDescriptors >= 3) {
                winMgrHelpInit(winMgrGetPtr(sel->descriptorId[2]));
            }
            psndSFXOn((const char*)0x2002A);
            statusWinForceOpen();
            sel->state++;
            break;
        case 1:
            if ((wp->mEntries[sel->descriptorId[0]].flags & 4)) {
                break;
            }
            prev = sel->cursor;
            if (keyGetDirRep(0) & 0x2000) {
                sel->cursor++;
            }
            if (keyGetDirRep(0) & 0x1000) {
                sel->cursor--;
            }
            if (sel->cursor >= sel->numItems) {
                if (keyGetDirTrg(0) & 0x2000) {
                    sel->cursor = 0;
                    sel->scrollTop = 0;
                }
                else {
                    sel->cursor--;
                }
            }
            if (sel->cursor < 0) {
                if (keyGetDirTrg(0) & 0x1000) {
                    sel->cursor = sel->numItems - 1;
                    if ((i = sel->numItems - 8) > 0) {
                        sel->scrollTop = i;
                    }
                }
                else {
                    sel->cursor++;
                }
            }
            if (prev < sel->cursor) {
                if (sel->cursor > 5 && sel->scrollTop < sel->numItems - 8) {
                    sel->scrollTop++;
                }
            }
            else if (prev > sel->cursor) {
                if (sel->cursor - sel->scrollTop < 3 && sel->scrollTop > 0) {
                    sel->scrollTop--;
                }
            }
            if (prev != sel->cursor) {
                psndSFXOn((const char*)0x20005);
            }
            if (keyGetButtonTrg(0) & 0x100) {
                if (sel->items[sel->cursor].flags & 2) {
                    psndSFXOn((const char*)0x20014);
                }
                else {
                    psndSFXOn((const char*)0x20012);
                    sel->state++;
                }
            }
            else if (keyGetButtonTrg(0) & 0x200) {
                if (sel->flags & 0x100) {
                    psndSFXOn((const char*)0x20013);
                    sel->flags |= 0x2000;
                    sel->state++;
                }
            }
            sel->field_0x1C += (24.0f * sel->scrollTop - sel->field_0x1C) / 6.0f;
            sel->field_0x14 += (entry->x - sel->field_0x14) / 6.0f;
            sel->field_0x18 += ((entry->y - 54) - 24.0f * (sel->cursor - sel->scrollTop) - sel->field_0x18) / 6.0f;
            break;
        case 2:
            for (i = 0; i < sel->numDescriptors; i++) {
                winMgrClose(sel->descriptorId[i]);
            }
            psndSFXOn((const char*)0x2002B);
            statusWinForceOff();
            sel->state++;
            break;
        case 3:
            if ((wp->mEntries[sel->descriptorId[0]].flags & 4)) {
                break;
            }
            for (i = 0; i < sel->numDescriptors; i++) {
                winMgrDelete(sel->descriptorId[i]);
            }
            sel->flags |= 0x1000;
            sel->state++;
            break;
        case 4:
            break;
    }
}

void select_disp(WinMgrEntry* entry) {
}

static inline const char* select_party_name(u16 id) {
    const char* name;
    switch (id) {
        case 0:
            name = msgSearch("name_party0");
            break;
        case 1:
            name = msgSearch("name_party1");
            break;
        case 2:
            name = msgSearch("name_party4");
            break;
        case 3:
            name = pouchGetYoshiName();
            break;
        case 4:
            name = msgSearch("name_party5");
            break;
        case 5:
            name = msgSearch("name_party2");
            break;
        case 6:
            name = msgSearch("name_party6");
            break;
    }
    return name;
}

void select_disp_party(WinMgrEntry* entry) {
    WinMgrSelect* sel = entry->param;
    PouchData* pouch;
    u32 left, top, wd, ht;
    GXColor black = {0x00, 0x00, 0x00, 0xFF};
    GXColor gray = {0xA0, 0xA0, 0xA0, 0xFF};
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXColor iconcol = white;
    GXColor* col;
    s32 i;
    s32 j;
    s32 icon;
    const char* msg;
    u16 w;
    f32 sx;
    f32 ofs = 0.0f;

    pouch = pouchGetPtr();
    if (!(wp->mEntries[sel->descriptorId[0]].flags & 4)) {
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
        GXGetScissor(&left, &top, &wd, &ht);
        GXSetScissor(entry->x + 304, 274 - entry->y, entry->width, entry->height - 50);
        for (i = 0; i < sel->numItems; i++) {
            f32 py;
            py = sel->field_0x1C + (ofs + (entry->y - 44 - i * 24));
            if ((f32)entry->y < py - 32.0f || (f32)(entry->y - entry->height) > py + 32.0f) {
                continue;
            }
            if (sel->field_0x38 == 0) {
            }
            winFontInit();
            winFontSet((Vec){entry->x + 60, sel->field_0x1C + (ofs + (entry->y - 32 - i * 24)), 0.0f},
                       (Vec){FontGetMessageWidth(select_party_name(sel->items[i].id)) > 170 ? 170.0f / FontGetMessageWidth(select_party_name(sel->items[i].id)) : 1.0f, 1.0f, 1.0f},
                       *((sel->items[i].flags & 1) ? &gray : &black), select_party_name(sel->items[i].id));
            if (sel->items[i].flags & 1) {
                winIconGrayInit();
            } else {
                winIconInit();
            }
            icon = party_icon_table[sel->items[i].id];
            if (icon == 0x158) {
                switch (pouchGetPartyColor(4)) {
                    case 0:
                        icon = 0x158;
                        break;
                    case 1:
                        icon = 0x159;
                        break;
                    case 2:
                        icon = 0x15A;
                        break;
                    case 3:
                        icon = 0x15B;
                        break;
                    case 4:
                        icon = 0x15C;
                        break;
                    case 5:
                        icon = 0x15D;
                        break;
                    default:
                        icon = 0x15E;
                        break;
                }
            }
            winIconSet(icon, (Vec){entry->x + 35, sel->field_0x1C + (ofs + (entry->y - 44 - i * 24)), 0.0f}, (Vec){0.55f, 0.55f, 0.55f}, iconcol);
            for (j = 0; j < pouch->partyData[party_id_table[sel->items[i].id]].techLevel; j++) {
                if (sel->items[i].flags & 1) {
                    winIconGrayInit();
                } else {
                    winIconInit();
                }
                winIconSet(0x102, (Vec){entry->x + 253 + j * 27, sel->field_0x1C + (ofs + (entry->y - 44 - i * 24)), 0.0f}, (Vec){0.55f, 0.55f, 0.55f}, iconcol);
            }
        }
        GXSetScissor(left, top, wd, ht);
        msg = msgSearch("msg_window_title_7");
        w = (120 - FontGetMessageWidth(msg)) / 2;
        winFontInit();
        winFontSetEdge((Vec){entry->x + ((entry->width * 3 / 5 - 120) * 2 / 3 + w), entry->y + 14, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white, msg);
        msg = msgSearch("msg_window_title_8");
        w = (85 - FontGetMessageWidth(msg)) / 2;
        winFontInit();
        winFontSetEdge((Vec){entry->x + (entry->width * 3 / 5 + (entry->width * 2 / 5 - 85) / 3 + w), entry->y + 14, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white, msg);
        iconDispGx(&(Vec){sel->field_0x14, sel->field_0x18, 1.0f}, 20, 0x1F0, 1.0f);
        if (sel->numItems > 8 && (gp->retraceCount & 31) < 20) {
            if (sel->scrollTop != 0) {
                iconDispGx(&(Vec){entry->x + entry->width * 0.5f, entry->y - 36, 1.0f}, 16, 0x1B5, 0.6f);
            }
            if (sel->scrollTop != sel->numItems - 8) {
                iconDispGx(&(Vec){entry->x + entry->width * 0.5f, entry->y - entry->height - 12, 1.0f}, 16, 0x1B6, 0.6f);
            }
        }
    }
}

void select_disp_mario(WinMgrEntry* entry) {
    WinMgrSelect* sel = entry->param;
    PouchData* pouch;
    u32 left, top, wd, ht;
    GXColor black = {0x00, 0x00, 0x00, 0xFF};
    GXColor gray = {0xA0, 0xA0, 0xA0, 0xFF};
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXColor iconcol = white;
    GXColor* col;
    s32 i;
    s32 id;
    const char* msg;
    u16 w;
    char buf[4];
    f32 ofs = 0.0f;

    pouch = pouchGetPtr();
    if (!(wp->mEntries[sel->descriptorId[0]].flags & 4)) {
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
        GXGetScissor(&left, &top, &wd, &ht);
        GXSetScissor(entry->x + 304, 274 - entry->y, entry->width, entry->height - 50);
        for (i = 0; i < sel->numItems; i++) {
            f32 py;
            id = sel->items[i].id;
            py = sel->field_0x1C + (ofs + (entry->y - 44 - i * 24));
            if ((f32)entry->y < py - 32.0f || (f32)(entry->y - entry->height) > py + 32.0f) {
                continue;
            }
            if (sel->field_0x38 == 0) {
            }
            winFontInit();
            col = &black;
            if (sel->items[i].flags & 1) {
                col = &gray;
            }
            winFontSet((Vec){entry->x + 60, sel->field_0x1C + (ofs + (entry->y - 32 - i * 24)), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, *col, mario_status_name_table[id]);
            if (sel->items[i].flags & 1) {
                winIconGrayInit();
            } else {
                winIconInit();
            }
            winIconSet(mario_status_icon_table[id], (Vec){entry->x + 35, sel->field_0x1C + (ofs + (entry->y - 44 - i * 24)), 0.0f}, (Vec){0.55f, 0.55f, 0.55f}, iconcol);
            sprintf(buf, "%3d", *mario_status_point_table[id]);
            winFontInit();
            col = &black;
            if (sel->items[i].flags & 1) {
                col = &gray;
            }
            winFontSet((Vec){entry->x + 160, sel->field_0x1C + (ofs + (entry->y - 32 - i * 24)), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, *col, buf);
            if (sel->items[i].flags & 2) {
                continue;
            }
            switch (sel->type) {
                case 9:
                    sprintf(buf, "%3d", *mario_status_point_table[id] + mario_status_henka_table[id]);
                    break;
                case 10:
                default:
                    sprintf(buf, "%3d", *mario_status_point_table[id] - mario_status_henka_table[id]);
                    break;
            }
            winFontInit();
            col = &black;
            if (sel->items[i].flags & 1) {
                col = &gray;
            }
            winFontSet((Vec){entry->x + 240, sel->field_0x1C + (ofs + (entry->y - 32 - i * 24)), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, *col, buf);
            winIconInit();
            winIconSet(0x163, (Vec){entry->x + 220, sel->field_0x1C + (ofs + (entry->y - 44 - i * 24)), 0.0f}, (Vec){-0.55f, 0.55f, 0.55f}, iconcol);
        }
        GXSetScissor(left, top, wd, ht);
        msg = msgSearch("msg_window_title_9");
        w = (120 - FontGetMessageWidth(msg)) / 2;
        winFontInit();
        winFontSetEdge((Vec){entry->x + ((entry->width * 3 / 5 - 120) * 2 / 3 + w), entry->y + 14, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white, msg);
        msg = msgSearch("msg_window_title_10");
        w = (85 - FontGetMessageWidth(msg)) / 2;
        winFontInit();
        winFontSetEdge((Vec){entry->x + (entry->width * 3 / 5 + (entry->width * 2 / 5 - 85) / 3 + w), entry->y + 14, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white, msg);
        iconDispGx(&(Vec){sel->field_0x14, sel->field_0x18, 1.0f}, 20, 0x1F0, 1.0f);
        if (sel->numItems > 8 && (gp->retraceCount & 31) < 20) {
            if (sel->scrollTop != 0) {
                iconDispGx(&(Vec){entry->x + entry->width * 0.5f, entry->y - 36, 1.0f}, 16, 0x1B5, 0.6f);
            }
            if (sel->scrollTop != sel->numItems - 8) {
                iconDispGx(&(Vec){entry->x + entry->width * 0.5f, entry->y - entry->height - 12, 1.0f}, 16, 0x1B6, 0.6f);
            }
        }
    }
}

void select_disp_luigi(WinMgrEntry* entry) {
    WinMgrSelect* sel = entry->param;
    InformantWork* jdt = &_jdt;
    u32 left, top, wd, ht;
    GXColor black = {0x00, 0x00, 0x00, 0xFF};
    GXColor gray = {0xA0, 0xA0, 0xA0, 0xFF};
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXColor* col;
    InformantInfo* info;
    char* str;
    const char* msg;
    s32 i;
    u16 w;
    char save;
    f32 py;
    char buf[0x40];
    Mtx mtx;
    Mtx scale;

    if (!(wp->mEntries[sel->descriptorId[0]].flags & 4)) {
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
        GXGetScissor(&left, &top, &wd, &ht);
        GXSetScissor(entry->x + 304, 274 - entry->y, entry->width, entry->height - 50);
        info = jdt->info;
        for (i = 0; i < sel->numItems; i++, info++) {
            py = sel->field_0x1C + (0.0f + (entry->y - 44 - i * 24));
            if ((f32)entry->y < py - 32.0f || (f32)(entry->y - entry->height) > py + 32.0f) {
                continue;
            }
            winFontInit();
            str = (char*)info->initEndPos;
            save = str[info->tagEndPos];
            str[info->tagEndPos] = 0;
            col = &black;
            if (sel->items[i].flags & 1) {
                col = &gray;
            }
            winFontSet((Vec){entry->x + 25, sel->field_0x1C + (0.0f + (entry->y - 32 - i * 24)), 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, *col, str);
            str[info->tagEndPos] = save;
            if (sel->type == 17 && !(sel->items[i].flags & 1)) {
                sprintf(buf, "%3d", info->unkA);
                winFontInit();
                col = &black;
                if (sel->items[i].flags & 1) {
                    col = &gray;
                }
                winFontSet((Vec){entry->x + 245, sel->field_0x1C + (0.0f + (entry->y - 32 - i * 24)), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, *col, buf);
            }
        }
        GXSetScissor(left, top, wd, ht);
        switch (sel->type) {
            case 17:
                msg = msgSearch("msg_window_title_5");
                break;
            case 18:
            default:
                msg = msgSearch("msg_window_title_6");
                break;
        }
        w = (entry->width - FontGetMessageWidth(msg)) / 2;
        winFontInit();
        winFontSetEdge((Vec){entry->x + w, entry->y + 14, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white, msg);
        switch (sel->type) {
            case 17:
                PSMTXTrans(mtx, entry->x + 268, entry->y - 18, 0.0f);
                PSMTXScale(scale, 0.6f, 0.6f, 0.6f);
                PSMTXConcat(mtx, scale, mtx);
                iconDispGxCol(mtx, 16, 0x211, (GXColor){0xF0, 0xF0, 0xF0, 0xFF});
                iconDispGx(&(Vec){entry->x + 268, entry->y - 12, 0.0f}, 16, 0x18B, 0.6f);
                break;
        }
        iconDispGx(&(Vec){sel->field_0x14, sel->field_0x18, 1.0f}, 20, 0x1F0, 1.0f);
        if (sel->numItems > 8 && (gp->retraceCount & 31) < 20) {
            if (sel->scrollTop != 0) {
                iconDispGx(&(Vec){entry->x + entry->width * 0.5f, entry->y - 36, 1.0f}, 16, 0x1B5, 0.6f);
            }
            if (sel->scrollTop != sel->numItems - 8) {
                iconDispGx(&(Vec){entry->x + entry->width * 0.5f, entry->y - entry->height - 12, 1.0f}, 16, 0x1B6, 0.6f);
            }
        }
    }
}

void select_disp2(WinMgrEntry* entry) {
    WinMgrSelect* sel = entry->param;
    const char* msg;
    u16 w;
    u16 lines;

    msg = msgSearch("msg_window_select_1");
    switch (sel->type) {
        case 3:
        case 12:
            msg = msgSearch("msg_window_select_2");
            break;
        case 4:
            msg = msgSearch("msg_window_select_3");
            break;
        case 5:
            msg = msgSearch("msg_window_select_4");
            break;
        case 6:
        case 7:
            msg = msgSearch("msg_window_select_11");
            break;
        case 8:
            msg = msgSearch("msg_window_select_12");
            break;
        case 9:
            msg = msgSearch("msg_window_select_9");
            break;
        case 10:
            msg = msgSearch("msg_window_select_9_1");
            break;
        case 11:
        case 14:
        case 15:
            msg = msgSearch("msg_window_select_6");
            break;
        case 13:
        case 16:
            msg = msgSearch("msg_window_select_10");
            break;
        case 17:
            msg = msgSearch("msg_window_select_8");
            break;
        case 18:
            msg = msgSearch("msg_window_select_7");
            break;
    }
    if (!(wp->mEntries[sel->descriptorId[1]].flags & 4)) {
        w = (entry->width - FontGetMessageWidthLine(msg, &lines)) / 2;
        FontDrawStart();
        FontDrawMessage(entry->x + w, entry->y - (entry->height - (lines + 1) * 24) / 2, msg);
    }
}

void select_main3(WinMgrEntry* entry) {
    winMgrHelpMain(entry);
}

void select_disp3(WinMgrEntry* entry) {
    WinMgrSelect* sel = entry->param;

    if (!(wp->mEntries[sel->descriptorId[2]].flags & 4)) {
        entry->msg = msgSearch(itemDataTable[sel->items[sel->cursor].id].description);
        winMgrHelpDraw(entry);
    }
}

void select_disp3_party(WinMgrEntry* entry) {
    WinMgrSelect* sel = entry->param;
    PouchData* pouch;
    char buf[0x48];
    const char* help;
    const char* lank;
    s32 id;

    pouch = pouchGetPtr();
    if (!(wp->mEntries[sel->descriptorId[2]].flags & 4)) {
        help = "help";
        if (sel->items[sel->cursor].flags & 2) {
            help = "helperr";
        }
        if (sel->type == 6 || sel->type == 7) {
            lank = "lankup";
        }
        else {
            lank = "lankdown";
        }
        id = sel->items[sel->cursor].id;
        sprintf(buf, "%s_%s_lank%d%s", help, lank, pouch->partyData[party_id_table[id]].techLevel + 1,
                party_labelname_table[id]);
        entry->msg = msgSearch(buf);
        winMgrHelpDraw(entry);
    }
}

void select_disp3_mario(WinMgrEntry* entry) {
    WinMgrSelect* sel = entry->param;
    char buf[0x48];
    const char* help;

    pouchGetPtr();
    if (!(wp->mEntries[sel->descriptorId[2]].flags & 4)) {
        if (sel->items[sel->cursor].flags & 2) {
            if (sel->items[sel->cursor].flags & 4) {
                help = "helperr2";
            }
            else {
                help = "helperr";
            }
        }
        else {
            help = "help";
        }
        switch (sel->type) {
            case 9:
                sprintf(buf, "%s_levelup%s", help, mario_status_labelname_table[sel->items[sel->cursor].id]);
                break;
            default:
            case 10:
                sprintf(buf, "%s_leveldown%s", help, mario_status_labelname_table[sel->items[sel->cursor].id]);
                break;
        }
        entry->msg = msgSearch(buf);
        winMgrHelpDraw(entry);
    }
}
