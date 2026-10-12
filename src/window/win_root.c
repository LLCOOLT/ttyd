#include "win/win_main.h"
#include "battle/battle_monosiri.h"
#include "data/item_data.h"
#include "data/mail_data.h"
#include "driver/camdrv.h"
#include "driver/mapdrv.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/gx.h>

extern int sprintf(char* str, const char* format, ...);
extern int strcmp(const char* a, const char* b);
extern char* strncpy(char* dst, const char* src, unsigned long n);
extern ItemData itemDataTable[];
void qqsort(void* base, u32 n, u32 size, s32 (*compare)(const void*, const void*));
void unk_800d06b4(const char* msg, char* out);

typedef struct WinSortEnt {
    u8 kind; // 0x0
    u8 id;   // 0x1
} WinSortEnt;

typedef struct WinBadgeEnt {
    s32 equipped; // 0x0
    s32 idx;      // 0x4
    s32 id;       // 0x8
} WinBadgeEnt;

typedef struct WinPauseWork {
    /* 0x000 */ u8 pad_0[0x128];
    /* 0x128 */ f32 msgOfsX;
    /* 0x12C */ f32 msgOfsY;
    /* 0x130 */ s32 msgState;
    /* 0x134 */ s32 msgTimer;
    /* 0x138 */ s32 msgX;
    /* 0x13C */ const char* msg;
    /* 0x140 */ s32 msgY;
    /* 0x144 */ const char* lastMsg;
    /* 0x148 */ s32 msgLine;
    /* 0x14C */ s32 msgLines;
    /* 0x150 */ u8 pad_150[0x164 - 0x150];
    /* 0x164 */ f32 sortPosX;
    /* 0x168 */ f32 sortPosY;
    /* 0x16C */ f32 sortTgtX;
    /* 0x170 */ f32 sortTgtY;
    /* 0x174 */ s32 sortSel;
    /* 0x178 */ s32 sortNum;
    /* 0x17C */ s32 sortActive;
    /* 0x180 */ s32 sortRev;
    /* 0x184 */ s32 sortType;
    /* 0x188 */ u8 pad_188[0x214 - 0x188];
    /* 0x214 */ s32 itemSel[2];
    /* 0x21C */ s32 itemPage[2];
    /* 0x224 */ u8 pad_224[0x254 - 0x224];
    /* 0x254 */ s32 mailNum;
    /* 0x258 */ s32 mailSel;
    /* 0x25C */ s32 mailPage;
    /* 0x260 */ u8 pad_260[0x26E - 0x260];
    /* 0x26E */ WinSortEnt mailList[0x80];
    /* 0x36E */ u8 pad_36E[0x3E4 - 0x36E];
    /* 0x3E4 */ s32 badgeSel[2];
    /* 0x3EC */ s32 badgePage[2];
    /* 0x3F4 */ u8 pad_3F4[0x404 - 0x3F4];
    /* 0x404 */ WinBadgeEnt badgeList[200];
    /* 0xD64 */ s32 badgeNum;
    /* 0xD68 */ u8 pad_D68[0xE94 - 0xD68];
    /* 0xE94 */ s32 recipeNum;
    /* 0xE98 */ s32 recipeSel;
    /* 0xE9C */ s32 recipePage;
    /* 0xEA0 */ u8 pad_EA0[0xEB8 - 0xEA0];
    /* 0xEB8 */ s16 recipeList[0x6C];
    /* 0xF90 */ s32 badgeLogNum;
    /* 0xF94 */ s32 badgeLogSel;
    /* 0xF98 */ s32 badgeLogPage;
    /* 0xF9C */ u8 pad_F9C[0xFB4 - 0xF9C];
    /* 0xFB4 */ s16 badgeLogList[0x42];
    /* 0x1038 */ s32 tattleNum;
    /* 0x103C */ u8 pad_103C[0x1040 - 0x103C];
    /* 0x1040 */ s32 tattleSel;
    /* 0x1044 */ s32 tattlePage;
    /* 0x1048 */ u8 pad_1048[0x1050 - 0x1048];
    /* 0x1050 */ WinSortEnt tattleList[0xE0];
} WinPauseWork;

typedef struct WinSortData {
    const char* name;
    void (*func)(WinPauseWork* wp);
} WinSortData;

void winMakeSkipList(WinPauseWork* wp);
void winMakeEquipList(WinPauseWork* wp);

void sort_1_1_func(WinPauseWork* wp);
void sort_1_2_func(WinPauseWork* wp);
void sort_2_1_func(WinPauseWork* wp);
void sort_2_2_func(WinPauseWork* wp);
void sort_3_1_func(WinPauseWork* wp);
void sort_3_2_func(WinPauseWork* wp);
void sort_3_3_func(WinPauseWork* wp);
void sort_4_1_func(WinPauseWork* wp);
void sort_4_2_func(WinPauseWork* wp);
void sort_4_3_func(WinPauseWork* wp);
void sort_5_1_func(WinPauseWork* wp);
void sort_5_2_func(WinPauseWork* wp);
void sort_5_3_func(WinPauseWork* wp);
void sort_6_1_func(WinPauseWork* wp);
void sort_6_2_func(WinPauseWork* wp);
void sort_7_1_func(WinPauseWork* wp);
void sort_7_2_func(WinPauseWork* wp);
void sort_7_3_func(WinPauseWork* wp);
void sort_8_1_func(WinPauseWork* wp);
void sort_8_2_func(WinPauseWork* wp);

u8 enemy_monoshiri_sort_table[] = {
    0x00, 0x01, 0x02, 0x03, 0x2F, 0x30, 0x94, 0x2A, 0x62, 0x95, 0x96, 0x12, 0x24, 0x24, 0x0A, 0x0B,
    0x32, 0x14, 0x4D, 0x54, 0x33, 0x32, 0x15, 0x63, 0x43, 0x38, 0x4F, 0x3E, 0x6B, 0x6E, 0x6F, 0x79,
    0x7A, 0x7B, 0x75, 0x99, 0x01, 0x0C, 0x0D, 0x36, 0x1B, 0x1D, 0x4E, 0x56, 0x2C, 0x2D, 0x23, 0x0E,
    0x0F, 0x25, 0x25, 0x26, 0x26, 0x27, 0x27, 0x2B, 0x18, 0x19, 0x1A, 0x5A, 0x13, 0x50, 0x51, 0x29,
    0x66, 0x67, 0x04, 0x05, 0x06, 0x3C, 0x3D, 0x52, 0x1F, 0x20, 0x40, 0x47, 0x48, 0x68, 0x9A, 0x9B,
    0x9C, 0x9D, 0x9E, 0x9F, 0x4A, 0x4B, 0x34, 0x35, 0x39, 0x21, 0x5B, 0x5C, 0x57, 0x69, 0xA0, 0xA1,
    0xA2, 0xA3, 0xA4, 0x77, 0x6B, 0x6B, 0x6B, 0x44, 0x37, 0x22, 0x49, 0x6A, 0xA5, 0xA6, 0xA7, 0xA8,
    0x45, 0x3A, 0x53, 0x70, 0x71, 0x72, 0x73, 0x6C, 0x6D, 0x76, 0xA9, 0x41, 0x4C, 0x5D, 0x5E, 0x59,
    0x5F, 0x5F, 0x16, 0x17, 0x64, 0x79, 0x7A, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68, 0x68,
    0x29, 0x28, 0x78, 0x74, 0x7C, 0x7C, 0x7C, 0x7C, 0x7C, 0x07, 0x08, 0x09, 0x10, 0x11, 0x2E, 0x1C,
    0x1E, 0x60, 0x3B, 0x31, 0x3F, 0x55, 0x46, 0x42, 0x58, 0x61, 0x61, 0x65, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0x00,
};

// TODO: not yet decompiled (stub only carries the function-static data)
void winRootMain(void) {
    static char* msg_help[] = {
        "msg_menu_mario", "msg_menu_nakama", "msg_menu_mochimono", "msg_menu_badge", "msg_menu_kiroku",
    };

    msg_help[0] = msg_help[1];
}

// TODO: not yet decompiled
void winRootDisp(void) {
}

// TODO: not yet decompiled
void winBgMain(void) {
}

// TODO: not yet decompiled
void winBgGX(void) {
}

void winMsgMain(WinPauseWork* wp) {
    switch (wp->msgState) {
        case 0:
            wp->msgOfsX = -800.0f;
            wp->msgOfsY = -170.0f;
            wp->msgTimer = 0;
            wp->msgState++;
            break;
        case 1:
            wp->msgOfsX = intplGetValue(11, wp->msgTimer++, 16, -800.0f, 0.0f);
            if (wp->msgTimer > 16) {
                wp->msgState++;
            }
            break;
        case 2:
            if (keyGetDirTrg(0) & 0x100) {
                wp->msgLine -= 2;
                if (wp->msgLine < 0) {
                    wp->msgLine = 0;
                } else {
                    ((void (*)(s32))psndSFXOn)(0x20006);
                }
            } else if (keyGetDirTrg(0) & 0x200) {
                if (wp->msgLine / 2 < (wp->msgLines + 1) / 2 - 1) {
                    wp->msgLine += 2;
                    ((void (*)(s32))psndSFXOn)(0x20006);
                }
            }
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            break;
        case 10:
            wp->msgTimer = 0;
            wp->msgState++;
            break;
        case 11:
            wp->msgOfsX = intplGetValue(11, wp->msgTimer++, 16, 0.0f, -800.0f);
            if (wp->msgTimer > 16) {
                wp->msgState++;
            }
            break;
        case 12:
            break;
    }
}

// TODO: not yet decompiled
void winMsgDisp(void) {
}

void winMsgEntry(WinPauseWork* wp, s32 x, const char* msg, s32 y) {
    static char _tmp[0x40];
    BOOL changed;
    u16 lines;

    changed = FALSE;
    if (msg) {
        if (wp->lastMsg != msg) {
            changed = TRUE;
        } else if (strcmp(_tmp, msg)) {
            changed = TRUE;
        }
        if (changed) {
            wp->msgX = x;
            wp->msg = msg;
            wp->msgY = y;
            FontGetMessageWidthLine(msgSearch(wp->msg), &lines);
            wp->msgLine = 0;
            wp->msgLines = lines + 1;
            wp->lastMsg = msg;
            strncpy(_tmp, msg, 60);
        }
    }
}

// TODO: not yet decompiled
void winKirinukiGX(void) {
}

// TODO: not yet decompiled
void winNameGX(void) {
}

// TODO: not yet decompiled
void winBookGX(void) {
}

// TODO: not yet decompiled
void winHalfBookGX(void) {
}

// TODO: not yet decompiled
void winMailGX(void) {
}

// TODO: not yet decompiled
void winHakoGX(void) {
}

// TODO: not yet decompiled
void winWazaGX(void) {
}

WinSortData sort_1[] = {
    {"msg_menu_sort_aiueo", sort_1_1_func},
    {"msg_menu_sort_kind", sort_1_2_func},
    {NULL, NULL},
};
WinSortData sort_2[] = {
    {"msg_menu_sort_aiueo", sort_2_1_func},
    {"msg_menu_sort_kind", sort_2_2_func},
    {NULL, NULL},
};
WinSortData sort_3[] = {
    {"msg_menu_sort_aiueo", sort_3_1_func},
    {"msg_menu_sort_kind", sort_3_2_func},
    {"msg_menu_sort_bp", sort_3_3_func},
    {NULL, NULL},
};
WinSortData sort_4[] = {
    {"msg_menu_sort_aiueo", sort_4_1_func},
    {"msg_menu_sort_kind", sort_4_2_func},
    {"msg_menu_sort_bp", sort_4_3_func},
    {NULL, NULL},
};
WinSortData sort_5[] = {
    {"msg_menu_sort_aiueo", sort_5_1_func},
    {"msg_menu_sort_kind", sort_5_2_func},
    {"msg_menu_sort_bp", sort_5_3_func},
    {NULL, NULL},
};
WinSortData sort_6[] = {
    {"msg_menu_sort_aiueo", sort_6_1_func},
    {"msg_menu_sort_kind", sort_6_2_func},
    {NULL, NULL},
};
WinSortData sort_7[] = {
    {"msg_menu_sort_number", sort_7_1_func},
    {"msg_menu_sort_place", sort_7_2_func},
    {"msg_menu_sort_aiueo", sort_7_3_func},
    {NULL, NULL},
};
WinSortData sort_8[] = {
    {"msg_menu_sort_aiueo", sort_8_1_func},
    {"msg_menu_sort_number", sort_8_2_func},
    {NULL, NULL},
};
WinSortData* sort_data[] = {sort_1, sort_2, sort_3, sort_4, sort_5, sort_6, sort_7, sort_8};


void sort_1_1_func(WinPauseWork* wp) {
    s32 sel = wp->itemSel[0];
    s32 mode;

    pouchGetHaveItemCnt();
    pouchHaveItem(sel);
    mode = 7;
    if (!wp->sortRev) {
        mode = 0;
    }
    pouchSortItem(mode);
    wp->sortRev = 1 - wp->sortRev;
    winMakeSkipList(wp);
    wp->itemSel[0] = 0;
    wp->itemPage[0] = wp->itemSel[0] / 10;
}

void sort_1_2_func(WinPauseWork* wp) {
    s32 sel = wp->itemSel[0];

    pouchGetHaveItemCnt();
    pouchHaveItem(sel);
    pouchSortItem(!wp->sortRev ? 1 : 8);
    wp->sortRev = 1 - wp->sortRev;
    winMakeSkipList(wp);
    wp->itemSel[0] = 0;
    wp->itemPage[0] = wp->itemSel[0] / 10;
}

void sort_2_1_func(WinPauseWork* wp) {
    pouchSortItem(!wp->sortRev ? 2 : 9);
    wp->sortRev = 1 - wp->sortRev;
    winMakeSkipList(wp);
    wp->itemSel[1] = 0;
    wp->itemPage[1] = wp->itemSel[1] / 10;
}

void sort_2_2_func(WinPauseWork* wp) {
    pouchSortItem(!wp->sortRev ? 3 : 10);
    wp->sortRev = 1 - wp->sortRev;
    winMakeSkipList(wp);
    wp->itemSel[1] = 0;
    wp->itemPage[1] = wp->itemSel[1] / 10;
}

void sort_3_1_func(WinPauseWork* wp) {
    s32 sel = wp->badgeSel[0];

    pouchGetHaveBadgeCnt();
    pouchHaveBadge(sel);
    pouchSortItem(!wp->sortRev ? 4 : 11);
    wp->sortRev = 1 - wp->sortRev;
    winMakeEquipList(wp);
    wp->badgeSel[0] = 0;
    wp->badgePage[0] = wp->badgeSel[0] / 8;
}

void sort_3_2_func(WinPauseWork* wp) {
    s32 sel = wp->badgeSel[0];

    pouchGetHaveBadgeCnt();
    pouchHaveBadge(sel);
    pouchSortItem(!wp->sortRev ? 5 : 12);
    wp->sortRev = 1 - wp->sortRev;
    winMakeEquipList(wp);
    wp->badgeSel[0] = 0;
    wp->badgePage[0] = wp->badgeSel[0] / 8;
}

void sort_3_3_func(WinPauseWork* wp) {
    s32 sel = wp->badgeSel[0];

    pouchGetHaveBadgeCnt();
    pouchHaveBadge(sel);
    pouchSortItem(!wp->sortRev ? 6 : 13);
    pouchSortItem(!wp->sortRev ? 6 : 13);
    wp->sortRev = 1 - wp->sortRev;
    winMakeEquipList(wp);
    wp->badgeSel[0] = 0;
    wp->badgePage[0] = wp->badgeSel[0] / 8;
}

s32 N_compare_func4_1(const void* a, const void* b) {
    char buf1[128];
    char buf2[128];
    s16 ia = ((WinBadgeEnt*)a)->id;
    s16 ib = ((WinBadgeEnt*)b)->id;

    unk_800d06b4(msgSearch(itemDataTable[ia].name), buf1);
    unk_800d06b4(msgSearch(itemDataTable[ib].name), buf2);
    return strcmp(buf1, buf2);
}

s32 N_compare_func4_1_r(const void* a, const void* b) {
    char buf1[128];
    char buf2[128];
    s16 ia = ((WinBadgeEnt*)a)->id;
    s16 ib = ((WinBadgeEnt*)b)->id;

    unk_800d06b4(msgSearch(itemDataTable[ia].name), buf1);
    unk_800d06b4(msgSearch(itemDataTable[ib].name), buf2);
    return strcmp(buf2, buf1);
}

s32 N_compare_func4_2(const void* a, const void* b) {
    s16 ia = itemDataTable[(s16)((WinBadgeEnt*)a)->id].type_sort_order;
    s16 ib = itemDataTable[(s16)((WinBadgeEnt*)b)->id].type_sort_order;

    if (ia > ib) {
        return 1;
    } else if (ia < ib) {
        return -1;
    }
    return 0;
}

s32 N_compare_func4_2_r(const void* a, const void* b) {
    s16 ia = itemDataTable[(s16)((WinBadgeEnt*)a)->id].type_sort_order;
    s16 ib = itemDataTable[(s16)((WinBadgeEnt*)b)->id].type_sort_order;

    if (ia < ib) {
        return 1;
    } else if (ia > ib) {
        return -1;
    }
    return 0;
}

void sort_4_1_func(WinPauseWork* wp) {
    if (!wp->sortRev) {
        qqsort(wp->badgeList, wp->badgeNum, 12, N_compare_func4_1);
    } else {
        qqsort(wp->badgeList, wp->badgeNum, 12, N_compare_func4_1_r);
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->badgeSel[1] = 0;
    wp->badgePage[1] = wp->badgeSel[1] / 8;
}

void sort_4_2_func(WinPauseWork* wp) {
    if (!wp->sortRev) {
        qqsort(wp->badgeList, wp->badgeNum, 12, N_compare_func4_2);
    } else {
        qqsort(wp->badgeList, wp->badgeNum, 12, N_compare_func4_2_r);
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->badgeSel[1] = 0;
    wp->badgePage[1] = wp->badgeSel[1] / 8;
}

void sort_4_3_func(WinPauseWork* wp) {
    s16 a;
    s16 b;
    ItemData* da;
    ItemData* db;
    BOOL swap;
    s32 i;
    s32 j;

    if (!wp->sortRev) {
        for (i = 0; i < wp->badgeNum - 1; i++) {
            for (j = i + 1; j < wp->badgeNum; j++) {
                da = &itemDataTable[(s16)wp->badgeList[i].id];
                db = &itemDataTable[(s16)wp->badgeList[j].id];
                swap = FALSE;

                if (da->bp_cost > db->bp_cost) {
                    swap = TRUE;
                } else if (da->bp_cost == db->bp_cost) {
                    if (da->type_sort_order > db->type_sort_order) {
                        swap = TRUE;
                    }
                }
                if (swap) {
                    WinBadgeEnt tmp = wp->badgeList[i];
                    wp->badgeList[i] = wp->badgeList[j];
                    wp->badgeList[j] = tmp;
                }
            }
        }
    } else {
        for (i = 0; i < wp->badgeNum - 1; i++) {
            for (j = i + 1; j < wp->badgeNum; j++) {
                da = &itemDataTable[(s16)wp->badgeList[i].id];
                db = &itemDataTable[(s16)wp->badgeList[j].id];
                swap = FALSE;

                if (da->bp_cost < db->bp_cost) {
                    swap = TRUE;
                } else if (da->bp_cost == db->bp_cost) {
                    if (da->type_sort_order < db->type_sort_order) {
                        swap = TRUE;
                    }
                }
                if (swap) {
                    WinBadgeEnt tmp = wp->badgeList[i];
                    wp->badgeList[i] = wp->badgeList[j];
                    wp->badgeList[j] = tmp;
                }
            }
        }
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->badgeSel[1] = 0;
    wp->badgePage[1] = wp->badgeSel[1] / 8;
}

s32 compare_func5_1(const void* a, const void* b) {
    char buf1[128];
    char buf2[128];
    s16 ia = *(s16*)a + 0xF0;
    s16 ib = *(s16*)b + 0xF0;

    unk_800d06b4(msgSearch(itemDataTable[ia].name), buf1);
    unk_800d06b4(msgSearch(itemDataTable[ib].name), buf2);
    return strcmp(buf1, buf2);
}

s32 compare_func5_1_r(const void* a, const void* b) {
    char buf1[128];
    char buf2[128];
    s16 ia = *(s16*)a + 0xF0;
    s16 ib = *(s16*)b + 0xF0;

    unk_800d06b4(msgSearch(itemDataTable[ia].name), buf1);
    unk_800d06b4(msgSearch(itemDataTable[ib].name), buf2);
    return strcmp(buf2, buf1);
}

s32 compare_func5_2(const void* a, const void* b) {
    s16 ia = itemDataTable[(s16)(*(s16*)a + 0xF0)].type_sort_order;
    s16 ib = itemDataTable[(s16)(*(s16*)b + 0xF0)].type_sort_order;

    if (ia > ib) {
        return 1;
    } else if (ia < ib) {
        return -1;
    }
    return 0;
}

s32 compare_func5_2_r(const void* a, const void* b) {
    s16 ia = itemDataTable[(s16)(*(s16*)a + 0xF0)].type_sort_order;
    s16 ib = itemDataTable[(s16)(*(s16*)b + 0xF0)].type_sort_order;

    if (ia < ib) {
        return 1;
    } else if (ia > ib) {
        return -1;
    }
    return 0;
}

void sort_5_1_func(WinPauseWork* wp) {
    if (!wp->sortRev) {
        qqsort(wp->recipeList, wp->recipeNum, 2, compare_func5_1);
    } else {
        qqsort(wp->recipeList, wp->recipeNum, 2, compare_func5_1_r);
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->recipeSel = 0;
    wp->recipePage = wp->recipeSel / 28;
}

void sort_5_2_func(WinPauseWork* wp) {
    if (!wp->sortRev) {
        qqsort(wp->recipeList, wp->recipeNum, 2, compare_func5_2);
    } else {
        qqsort(wp->recipeList, wp->recipeNum, 2, compare_func5_2_r);
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->recipeSel = 0;
    wp->recipePage = wp->recipeSel / 28;
}

void sort_5_3_func(WinPauseWork* wp) {
    s16 a;
    s16 b;
    ItemData* da;
    ItemData* db;
    BOOL swap;
    s32 i;
    s32 j;

    if (!wp->sortRev) {
        for (i = 0; i < wp->recipeNum - 1; i++) {
            for (j = i + 1; j < wp->recipeNum; j++) {
                a = wp->recipeList[i];
                b = wp->recipeList[j];
                da = &itemDataTable[(s16)(a + 0xF0)];
                db = &itemDataTable[(s16)(b + 0xF0)];
                swap = FALSE;

                if (da->bp_cost > db->bp_cost) {
                    swap = TRUE;
                } else if (da->bp_cost == db->bp_cost) {
                    if (da->type_sort_order > db->type_sort_order) {
                        swap = TRUE;
                    }
                }
                if (swap) {
                    wp->recipeList[i] = b;
                    wp->recipeList[j] = a;
                }
            }
        }
    } else {
        for (i = 0; i < wp->recipeNum - 1; i++) {
            for (j = i + 1; j < wp->recipeNum; j++) {
                a = wp->recipeList[i];
                b = wp->recipeList[j];
                da = &itemDataTable[(s16)(a + 0xF0)];
                db = &itemDataTable[(s16)(b + 0xF0)];
                swap = FALSE;

                if (da->bp_cost < db->bp_cost) {
                    swap = TRUE;
                } else if (da->bp_cost == db->bp_cost) {
                    if (da->type_sort_order < db->type_sort_order) {
                        swap = TRUE;
                    }
                }
                if (swap) {
                    wp->recipeList[i] = b;
                    wp->recipeList[j] = a;
                }
            }
        }
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->recipeSel = 0;
    wp->recipePage = wp->recipeSel / 28;
}

s32 compare_func6_1(const void* a, const void* b) {
    char buf1[128];
    char buf2[128];
    s16 ia = *(s16*)a + 0xB3;
    s16 ib = *(s16*)b + 0xB3;

    unk_800d06b4(msgSearch(itemDataTable[ia].name), buf1);
    unk_800d06b4(msgSearch(itemDataTable[ib].name), buf2);
    return strcmp(buf1, buf2);
}

s32 compare_func6_1_r(const void* a, const void* b) {
    char buf1[128];
    char buf2[128];
    s16 ia = *(s16*)a + 0xB3;
    s16 ib = *(s16*)b + 0xB3;

    unk_800d06b4(msgSearch(itemDataTable[ia].name), buf1);
    unk_800d06b4(msgSearch(itemDataTable[ib].name), buf2);
    return strcmp(buf2, buf1);
}

s32 compare_func6_2(const void* a, const void* b) {
    s16 ia = itemDataTable[(s16)(*(s16*)a + 0xB3)].type_sort_order;
    s16 ib = itemDataTable[(s16)(*(s16*)b + 0xB3)].type_sort_order;

    if (ia > ib) {
        return 1;
    } else if (ia < ib) {
        return -1;
    }
    return 0;
}

s32 compare_func6_2_r(const void* a, const void* b) {
    s16 ia = itemDataTable[(s16)(*(s16*)a + 0xB3)].type_sort_order;
    s16 ib = itemDataTable[(s16)(*(s16*)b + 0xB3)].type_sort_order;

    if (ia < ib) {
        return 1;
    } else if (ia > ib) {
        return -1;
    }
    return 0;
}

void sort_6_1_func(WinPauseWork* wp) {
    if (!wp->sortRev) {
        qqsort(wp->badgeLogList, wp->badgeLogNum, 2, compare_func6_1);
    } else {
        qqsort(wp->badgeLogList, wp->badgeLogNum, 2, compare_func6_1_r);
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->badgeLogSel = 0;
    wp->badgeLogPage = wp->badgeLogSel / 28;
}

void sort_6_2_func(WinPauseWork* wp) {
    if (!wp->sortRev) {
        qqsort(wp->badgeLogList, wp->badgeLogNum, 2, compare_func6_2);
    } else {
        qqsort(wp->badgeLogList, wp->badgeLogNum, 2, compare_func6_2_r);
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->badgeLogSel = 0;
    wp->badgeLogPage = wp->badgeLogSel / 28;
}

s32 compare_func1(const void* a, const void* b) {
    if (*(u8*)a > *(u8*)b) {
        return 1;
    } else if (*(u8*)a < *(u8*)b) {
        return -1;
    }
    return 0;
}

s32 compare_func1_r(const void* a, const void* b) {
    if (*(u8*)a < *(u8*)b) {
        return 1;
    } else if (*(u8*)a > *(u8*)b) {
        return -1;
    }
    return 0;
}

void sort_7_1_func(WinPauseWork* wp) {
    if (!wp->sortRev) {
        qqsort(wp->tattleList, wp->tattleNum, 2, compare_func1);
    } else {
        qqsort(wp->tattleList, wp->tattleNum, 2, compare_func1_r);
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->tattleSel = 0;
    wp->tattlePage = wp->tattleSel / 16;
}

static inline u32 getMonosiriPlace(const char* place) {
    static char* tbl[] = {
        "nara", "gor", "tik", "shiga", "hei", "nok", "stn", "gon", "win", "hou", "mri", "tou", "usu",
        "gra", "jin", "muj", "dou", "hom", "eki", "rsh", "pik", "sin", "bom", "moo", "aji", "las",
    };
    char buf[64];
    u32 i;

    for (i = 0; i < 26; i++) {
        sprintf(buf, "menu_monosiri_%s", tbl[i]);
        if (!strcmp(buf, place)) {
            break;
        }
    }
    if (i >= 26) {
        i = 0;
    }
    return i;
}

s32 compare_func2(const void* a, const void* b) {
    TattleEntry* ta = battleGetUnitMonosiriPtr(((WinSortEnt*)a)->id);
    TattleEntry* tb = battleGetUnitMonosiriPtr(((WinSortEnt*)b)->id);
    s32 ia = getMonosiriPlace(ta->locationTag);
    s32 ib = getMonosiriPlace(tb->locationTag);

    if (ia > ib) {
        return 1;
    } else if (ia < ib) {
        return -1;
    }
    return 0;
}

s32 compare_func2_r(const void* a, const void* b) {
    TattleEntry* ta = battleGetUnitMonosiriPtr(((WinSortEnt*)a)->id);
    TattleEntry* tb = battleGetUnitMonosiriPtr(((WinSortEnt*)b)->id);
    s32 ia = getMonosiriPlace(ta->locationTag);
    s32 ib = getMonosiriPlace(tb->locationTag);

    if (ia < ib) {
        return 1;
    } else if (ia > ib) {
        return -1;
    }
    return 0;
}

void sort_7_2_func(WinPauseWork* wp) {
    if (!wp->sortRev) {
        qqsort(wp->tattleList, wp->tattleNum, 2, compare_func1);
        qqsort(wp->tattleList, wp->tattleNum, 2, compare_func2);
    } else {
        qqsort(wp->tattleList, wp->tattleNum, 2, compare_func1_r);
        qqsort(wp->tattleList, wp->tattleNum, 2, compare_func2_r);
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->tattleSel = 0;
    wp->tattlePage = wp->tattleSel / 16;
}

s32 compare_func3(const void* a, const void* b) {
    char buf1[128];
    char buf2[128];
    TattleEntry* ta = battleGetUnitMonosiriPtr(((WinSortEnt*)a)->id);
    TattleEntry* tb = battleGetUnitMonosiriPtr(((WinSortEnt*)b)->id);

    unk_800d06b4(msgSearch(ta->enemyTag), buf1);
    unk_800d06b4(msgSearch(tb->enemyTag), buf2);
    if (((WinSortEnt*)a)->id == 0x4D || ((WinSortEnt*)a)->id == 0x87) {
        if (evtGetValue(NULL, GSW(0)) < 210) {
            unk_800d06b4(msgSearch("btl_un_hatena"), buf1);
        } else {
            unk_800d06b4(msgSearch("btl_un_rampell"), buf1);
        }
    }
    if (((WinSortEnt*)b)->id == 0x4D || ((WinSortEnt*)b)->id == 0x87) {
        if (evtGetValue(NULL, GSW(0)) < 210) {
            unk_800d06b4(msgSearch("btl_un_hatena"), buf2);
        } else {
            unk_800d06b4(msgSearch("btl_un_rampell"), buf2);
        }
    }
    return strcmp(buf1, buf2);
}

s32 compare_func3_r(const void* a, const void* b) {
    char buf1[128];
    char buf2[128];
    TattleEntry* ta = battleGetUnitMonosiriPtr(((WinSortEnt*)a)->id);
    TattleEntry* tb = battleGetUnitMonosiriPtr(((WinSortEnt*)b)->id);

    unk_800d06b4(msgSearch(ta->enemyTag), buf1);
    unk_800d06b4(msgSearch(tb->enemyTag), buf2);
    if (((WinSortEnt*)a)->id == 0x4D || ((WinSortEnt*)a)->id == 0x87) {
        if (evtGetValue(NULL, GSW(0)) < 210) {
            unk_800d06b4(msgSearch("btl_un_hatena"), buf1);
        } else {
            unk_800d06b4(msgSearch("btl_un_rampell"), buf1);
        }
    }
    if (((WinSortEnt*)b)->id == 0x4D || ((WinSortEnt*)b)->id == 0x87) {
        if (evtGetValue(NULL, GSW(0)) < 210) {
            unk_800d06b4(msgSearch("btl_un_hatena"), buf2);
        } else {
            unk_800d06b4(msgSearch("btl_un_rampell"), buf2);
        }
    }
    return strcmp(buf2, buf1);
}

void sort_7_3_func(WinPauseWork* wp) {
    if (!wp->sortRev) {
        qqsort(wp->tattleList, wp->tattleNum, 2, compare_func1);
        qqsort(wp->tattleList, wp->tattleNum, 2, compare_func3);
    } else {
        qqsort(wp->tattleList, wp->tattleNum, 2, compare_func1_r);
        qqsort(wp->tattleList, wp->tattleNum, 2, compare_func3_r);
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->tattleSel = 0;
    wp->tattlePage = wp->tattleSel / 16;
}

s32 compare_func4(const void* a, const void* b) {
    MailData* ma = mailGetPtr(((WinSortEnt*)a)->id);
    MailData* mb = mailGetPtr(((WinSortEnt*)b)->id);
    const char* sa = msgSearch(ma->name);
    const char* sb = msgSearch(mb->name);

    return strcmp(sa, sb);
}

s32 compare_func4_r(const void* a, const void* b) {
    MailData* ma = mailGetPtr(((WinSortEnt*)a)->id);
    MailData* mb = mailGetPtr(((WinSortEnt*)b)->id);
    const char* sa = msgSearch(ma->name);
    const char* sb = msgSearch(mb->name);

    return strcmp(sb, sa);
}

void sort_8_1_func(WinPauseWork* wp) {
    if (!wp->sortRev) {
        qqsort(wp->mailList, wp->mailNum, 2, compare_func4);
    } else {
        qqsort(wp->mailList, wp->mailNum, 2, compare_func4_r);
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->mailSel = 0;
    wp->mailPage = wp->mailSel / 5;
}

s32 compare_func5(const void* a, const void* b) {
    if (*(u8*)a > *(u8*)b) {
        return 1;
    } else if (*(u8*)a < *(u8*)b) {
        return -1;
    }
    return 0;
}

s32 compare_func5_r(const void* a, const void* b) {
    if (*(u8*)a < *(u8*)b) {
        return 1;
    } else if (*(u8*)a > *(u8*)b) {
        return -1;
    }
    return 0;
}

void sort_8_2_func(WinPauseWork* wp) {
    if (!wp->sortRev) {
        qqsort(wp->mailList, wp->mailNum, 2, compare_func5);
    } else {
        qqsort(wp->mailList, wp->mailNum, 2, compare_func5_r);
    }
    wp->sortRev = 1 - wp->sortRev;
    wp->mailSel = 0;
    wp->mailPage = wp->mailSel / 5;
}

// TODO: not yet decompiled
void winSortMain(void) {
}

// TODO: not yet decompiled
void winSortGX(void) {
}

void winSortEntry(WinPauseWork* wp, s32 type, f32 x, f32 y) {
    WinSortData* sd = sort_data[type];
    s32 n;

    n = 0;
    while (sd->name != NULL) {
        sd++;
        n++;
    }
    wp->sortType = type;
    wp->sortNum = n;
    wp->sortSel = 0;
    wp->sortRev = 0;
    wp->sortPosX = -1000.0f;
    wp->sortTgtX = x;
    wp->sortPosY = y;
    wp->sortTgtY = y;
    wp->sortActive = 1;
}

BOOL winSortWait(WinPauseWork* wp) {
    return wp->sortActive != 0;
}

// TODO: not yet decompiled
void winKageGX(void) {
}

void winZClear(void) {
    Mtx mtx;

    PSMTXTrans(mtx, 0.0f, 0.0f, -1000.0f);
    PSMTXConcat(camGetCurPtr()->view, mtx, mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetColorUpdate(GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumTexGens(0);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-500.0f, 300.0f, 0.0f);
    GXPosition3f32(0.0f, 300.0f, 0.0f);
    GXPosition3f32(0.0f, -100.0f, 0.0f);
    GXPosition3f32(-500.0f, -100.0f, 0.0f);
    GXSetColorUpdate(GX_TRUE);
}

// TODO: not yet decompiled
void winMailDisp(void) {
}

typedef struct WinBgWork {
    u8 pad_0[0x34];
    void** tex; // 0x34
    s32 copied; // 0x38
} WinBgWork;

void unk_8014d5dc(s32 unused, WinBgWork* bg) {
    GXSetTexCopySrc(0, 0, gp->fbWidth, gp->efbHeight);
    GXSetTexCopyDst(gp->fbWidth, gp->efbHeight, GX_TF_RGB565, GX_FALSE);
    GXCopyTex(*bg->tex, GX_FALSE);
    GXTexModeSync();
    bg->copied = 1;
    N_mapDispOff();
    camDispOff((CameraId)4);
}

// TODO: not yet decompiled
void unk_8014d338(void) {
}
