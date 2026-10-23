#include "version.h"
#include "win/win_main.h"
#include "data/item_data.h"
#include "driver/animdrv.h"
#include "driver/msgdrv.h"
#include "manager/fontmgr.h"
#include "mario/mario_pouch.h"
#include <dolphin/gx.h>
#include "mario/mariost.h"
#include "icon_ids.h"
#include "libc_decls.h"

extern ItemData itemDataTable[];

typedef struct BTexRef {
    TEXPalette* tpl;
} BTexRef;

typedef struct BRes {
    u8 pad_0[0xA0];
    BTexRef* tex;
} BRes;

typedef struct BEnt {
    s32 equipped;
    s32 idx;
    s32 id;
} BEnt;

typedef struct BWinPos {
    f32 x;
    f32 y;
    u8 pad[0xC];
} BWinPos;

typedef struct BWin {
    /* 0x000 */ u16 flags;
    /* 0x002 */ u8 pad_2[2];
    /* 0x004 */ u32 trg;
    /* 0x008 */ u32 rep;
    /* 0x00C */ u32 dtrg;
    /* 0x010 */ u32 drep;
    /* 0x014 */ u8 pad_14[0x28 - 0x14];
    /* 0x028 */ BRes* res;
    /* 0x02C */ u8 pad_2C[0xC4 - 0x2C];
    /* 0x0C4 */ BWinPos pos[4];
    /* 0x114 */ u8 pad_114[0x124 - 0x114];
    /* 0x124 */ s32 savedState;
    /* 0x128 */ u8 pad_128[0x158 - 0x128];
    /* 0x158 */ f32 msgX;
    /* 0x15C */ f32 msgY;
    /* 0x160 */ u8 pad_160[0x188 - 0x160];
    /* 0x188 */ s32 poseA;
    /* 0x18C */ u8 pad_18C[0x3DC - 0x18C];
    /* 0x3DC */ s32 state;
    /* 0x3E0 */ s32 tab;
    /* 0x3E4 */ s32 sel[2];
    /* 0x3EC */ s32 page[2];
    /* 0x3F4 */ f32 cur[2];
    /* 0x3FC */ f32 tgt[2];
    /* 0x404 */ BEnt list[200];
    /* 0xD64 */ s32 count;
    /* 0xD68 */ u8 pad_D68[0xE1C - 0xD68];
    /* 0xE1C */ s32 poseB;
} BWin;

void psndSFXOn(s32 id);
void winMsgEntry(BWin* w, s32 a, const char* msg, s32 b);
void winBgGX(BWin* w, s32 a, f32 x, f32 y);
void winKirinukiGX(BWin* w, s32 a, f32 x, f32 y, f32 w_, f32 h);
void winSortEntry(BWin* w, s32 a, f32 x, f32 y);
s32 winSortWait(BWin* w);
void winTexInit_x2(TEXPalette* tpl);
void winTexSet_x2(u32 a, u32 b, Vec translate, Vec scale, GXColor color);
void winIconInit(void);
void winIconGrayInit(void);
void winIconSet(u32 id, Vec translate, Vec scale, GXColor color);
void winFontInit(void);
void winFontSet(Vec translate, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetR(Vec translate, Vec scale, GXColor color, const char* fmt, ...);
const char* winZenkakuStr(s32 n);

void winMakeEquipList(BWin* w) {
    s32 n = 0;
    s32 i;
    PouchData* pouch = pouchGetPtr();

    for (i = 0; i < 200; i++) {
        if (pouch->equippedBadges[i] != 0) {
            w->list[n].equipped = 1;
            w->list[n].idx = i;
            w->list[n].id = pouch->equippedBadges[i];
            n++;
        }
    }
    w->count = n;
}

void winBadgeInit(BWin* w) {
    w->state = 0;
    w->tab = 0;
    w->sel[0] = 0;
    w->page[0] = 0;
    w->sel[1] = 0;
    w->page[1] = 0;
    winMakeEquipList(w);
}

void winBadgeInit2(BWin* w) {
    w->msgX = -270.0f;
    w->msgY = 125 - w->tab * 40;
    w->cur[0] = w->tgt[0] = 184.0f * w->page[0];
    w->cur[1] = w->tgt[1] = 184.0f * w->page[1];
    winMsgEntry(w, 0, w->tab == 0 ? "msg_menu_badge_all" : "msg_menu_badge_equip", 0);
    winMakeEquipList(w);
}

void winBadgeExit(void) {
}

void mario_change(BWin* w, s32 unused) {
    s32 hasLeft = pouchEquipCheckBadge(0x147);
    s32 hasRight = pouchEquipCheckBadge(0x148);
    const char* model;
    const char* animL;
    const char* animR;

    if (w->flags & 0x2000) {
        if (hasLeft && !hasRight) {
            animL = "S_2";
            animR = "W_15";
        } else if (!hasLeft && hasRight) {
            animL = "S_3";
            animR = "W_17";
        } else if (hasLeft && hasRight) {
            animL = "S_4";
            animR = "W_18";
        } else {
            animL = "S_1";
            animR = "W_1";
        }
        if (w->poseA != -1) {
            animPoseRelease(w->poseA);
            w->poseA = animPoseEntry("d_mario", 0);
            animPoseSetAnim(w->poseA, animL, 1);
            animPoseSetMaterialFlagOn(w->poseA, 0x1800);
        }
        if (w->poseB != -1) {
            animPoseRelease(w->poseB);
            w->poseB = animPoseEntry("d_mario", 0);
            animPoseSetAnim(w->poseB, animR, 1);
            animPoseSetMaterialFlagOn(w->poseB, 0x1800);
        }
    } else {
        if (hasLeft && !hasRight) {
            model = "a_mario_l";
        } else if (!hasLeft && hasRight) {
            model = "a_mario_w";
        } else if (hasLeft && hasRight) {
            model = "a_mario_wl";
        } else {
            model = "a_mario";
        }
        if (w->poseA != -1) {
            animPoseRelease(w->poseA);
            w->poseA = animPoseEntry(model, 0);
            animPoseSetAnim(w->poseA, "M_S_1", 1);
            animPoseSetMaterialFlagOn(w->poseA, 0x1800);
        }
        if (w->poseB != -1) {
            animPoseRelease(w->poseB);
            w->poseB = animPoseEntry(model, 0);
            animPoseSetAnim(w->poseB, "M_W_1", 1);
            animPoseSetMaterialFlagOn(w->poseB, 0x1800);
        }
    }
}

s32 winBadgeMain(BWin* w) {
    PouchData* pouch = pouchGetPtr();
    s32 tab;
    s32 cnt;
    s32 pages;
    s32 mode;
    s32 m;

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
            w->tab = 1 - w->tab;
            psndSFXOn(0x20005);
            if (w->tab) {
                winMakeEquipList(w);
            }
        } else if (w->trg & 0x100) {
            if (w->tab == 0 && !pouchGetHaveBadgeCnt()) {
                break;
            }
            if (w->tab == 1 && w->count == 0) {
                break;
            }
            psndSFXOn(0x20012);
            w->state = 10;
            break;
        } else if (w->trg & 0x10) {
            void* p = w;
            s32 m = 3;
            if (w->tab == 0) {
                m = 2;
            }
            winSortEntry(p, m, -310.0f, 150.0f);
            w->savedState = w->state;
            psndSFXOn(0x20012);
            w->state = 1000;
        }
        w->msgX = -270.0f;
        w->msgY = VERSION_PICK(125, 130) - w->tab * VERSION_PICK(40, 45);
        winMsgEntry(w, 0, w->tab == 0 ? "msg_menu_badge_all" : "msg_menu_badge_equip", 0);
        break;
    case 10:
        if (w->tab == 0) {
            cnt = pouchGetHaveBadgeCnt();
        } else {
            cnt = w->count;
        }
        pages = (cnt + 7) / 8;
        tab = w->tab;
        if (w->trg & 0x100) {
            if (tab == 0) {
                s32 idx = w->sel[tab];
                if (pouchEquipCheckBadgeIndex(idx)) {
                    psndSFXOn(0x20039);
                    pouchUnEquipBadgeIndex(idx);
                } else if (pouch->availableBP >= itemDataTable[pouchHaveBadge(idx)].bp_cost) {
                    psndSFXOn(0x20038);
                    pouchEquipBadgeIndex(idx);
                } else {
                    psndSFXOn(0x20014);
                }
                pouchReviseMarioParam();
                pouchRevisePartyParam();
                mario_change(w, pouchHaveBadge(idx));
            } else {
                BWin* wt = (BWin*)((s32*)w + tab);
                s32 idx = w->list[wt->sel[0]].idx;
                if (w->list[wt->sel[0]].equipped) {
                    psndSFXOn(0x20039);
                    pouchUnEquipBadgeIndex(idx);
                    w->list[wt->sel[0]].equipped = 0;
                } else if (pouch->availableBP >= itemDataTable[pouchHaveBadge(idx)].bp_cost) {
                    psndSFXOn(0x20038);
                    pouchEquipBadgeIndex(idx);
                    w->list[wt->sel[0]].equipped = 1;
                }
                pouchReviseMarioParam();
                pouchRevisePartyParam();
                mario_change(w, pouchHaveBadge(idx));
            }
        } else if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            w->state = 0;
        } else if (w->trg & 0x1000) {
            return -2;
        } else if (w->rep & 0x40) {
            w->page[tab]--;
            if (w->page[tab] < 0) {
                w->page[tab] = 0;
            }
            w->sel[tab] = w->page[tab] * 8;
            psndSFXOn(0x20035);
        } else if (w->rep & 0x20) {
            w->page[tab]++;
            if (w->page[tab] >= pages) {
                w->page[tab] = pages - 1;
            }
            w->sel[tab] = w->page[tab] * 8;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x1000) {
            w->sel[tab]--;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x2000) {
            w->sel[tab]++;
            psndSFXOn(0x20035);
        } else if (w->trg & 0x10) {
            void* p = w;
            m = 3;
            if (tab == 0) {
                m = 2;
            }
            winSortEntry(p, m, -310.0f, 150.0f);
            w->savedState = w->state;
            psndSFXOn(0x20012);
            w->state = 1000;
        }
        if (w->sel[tab] < 0) {
            w->sel[tab] = cnt - 1;
        }
        if (w->sel[tab] >= cnt) {
            w->sel[tab] = 0;
        }
        w->page[tab] = w->sel[tab] / 8;
        w->msgX = -110.0f;
        w->msgY = 110 - (w->sel[tab] % 8) * 23;
        if (w->tab == 0) {
            mode = pouchHaveBadge(w->sel[tab]);
        } else {
            mode = w->list[w->sel[tab]].id;
        }
        winMsgEntry(w, mode, itemDataTable[mode].menu_description, 0);
        break;
    case 1000:
        if (!winSortWait(w)) {
            w->state = w->savedState;
        }
        if (w->trg & 0x1000) {
            return -2;
        }
        break;
    }
    return 0;
}

void winBadgeMain2(BWin* w) {
    s32 i;
    for (i = 0; i < 2; i++) {
        w->tgt[i] = 184.0f * w->page[i];
        w->cur[i] += (w->tgt[i] - w->cur[i]) / 4.0f;
    }
}

#ifdef VERSION_G8ME01
void winFontSetWidth(Vec translate, Vec scale, GXColor color, f32 width, const char* fmt, ...);
#endif
void badge_disp(BWin* w, f32 xo, f32 yo);

#define Q ((pouch->maximumBP + 9) / 10)

void winBadgeDisp(s32 camId, void* param, s32 n) {
    BWin* w = param;
    GXColor white = {255, 255, 255, 255};
    GXColor black = {0, 0, 0, 255};
    s32 i;
    s32 off;
    PouchData* pouch = pouchGetPtr();
    f32 c;
    f32 b;
    f32 a;
    f32 yy;
    f32 d;
    f32 x = w->pos[n].x;
    f32 y = w->pos[n].y;
#ifdef VERSION_G8ME01
    f32 tw;
#endif

    winBgGX(w, 3, x, y);
    winKirinukiGX(w, 0, x - 100.0f, 20.0f + (120.0f + y), 365.0f, 210.0f);
    a = 105.0f + y;
    c = (x - 190.0f) - 4.0f;
    b = 4.0f + a;
    for (i = 0; i < 2; i++) {
        off = i * VERSION_PICK(40, 45);
        if (i == w->tab) {
            winTexInit(w->res->tex->tpl);
            winTexSet(0xB4, (Vec){x - 190.0f, VERSION_PICK(20.0f, 25.0f) + (a - off), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 0x80});
            winTexInit_x2(w->res->tex->tpl);
            winTexSet_x2(i + 0x1A, 0xB4, (Vec){c, VERSION_PICK(20.0f, 25.0f) + (b - off), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
        } else {
            winTexInit_x2(w->res->tex->tpl);
            winTexSet_x2(i + 0x1A, 0xB4, (Vec){x - 190.0f, VERSION_PICK(20.0f, 25.0f) + (a - off), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0x80, 0x80, 0x80, 0xFF});
        }
    }
    winKirinukiGX(w, 1, x - 260.0f, yy = 20.0f + (40.0f + y), 150.0f, 158 - (10 - Q) * 13);
    winFontInit();
#ifdef VERSION_G8ME01
    {
        // US: BP label per language (indexed by gp->language)
        const char* bpLabel[7] = {"\202a\202o", "BP", "OP", "PB", "PM", "PT", "BP"};
        winFontSet((Vec){x - 220.0f, yy = yy - 4.0f, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, black, bpLabel[gp->language]);
    }
#else
    winFontSet((Vec){x - 220.0f, yy = yy - 4.0f, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, black, "\202a\202o");
#endif
    winFontSetR((Vec){(x - 175.0f) - 18.0f, yy, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, black, "%s", winZenkakuStr(pouch->maximumBP));
#ifdef VERSION_G8ME01
    tw = FontGetMessageWidth(msgSearch("msg_menu_badge_nokori")) * 0.5f + 60.0f;
    winFontSet((Vec){4.0f + (16.0f + ((x - 260.0f) + (150.0f - tw))), ((20.0f + (y - 108.0f)) - 18.0f) + (10 - Q) * 13, 0.0f}, (Vec){0.5f, 0.5f, 0.5f}, black, msgSearch("msg_menu_badge_nokori"));
#else
    winFontSet((Vec){x - 180.0f, ((20.0f + (y - 108.0f)) - 18.0f) + (10 - Q) * 13, 0.0f}, (Vec){0.5f, 0.5f, 0.5f}, black, msgSearch("msg_menu_badge_nokori"));
#endif
    winFontSetR((Vec){VERSION_PICK((x - 145.0f) - 16.0f, 4.0f + ((x - 145.0f) - 16.0f)), ((20.0f + (y - 102.0f)) - 18.0f) + (10 - Q) * 13, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, black, "%s", winZenkakuStr(pouch->availableBP));
    winTexInit(w->res->tex->tpl);
    d = 28.0f + y;
    for (i = 0; i < pouch->availableBP; i++) {
        winTexSet(0x1C, (Vec){(x - 242.0f) + (i % 10) * 13, (20.0f + (d - (i / 10) * 13)) - 18.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    }
    for (i = pouch->availableBP; i < pouch->maximumBP; i++) {
        winTexSet(0x1D, (Vec){(x - 242.0f) + (i % 10) * 13, (20.0f + (d - (i / 10) * 13)) - 18.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    }
    badge_disp(w, x, y);
}

static inline s32 badgeTexA(s32 e) { s32 t = 0x1D; if (e) t = 0x1C; return t; }
static inline s32 badgeTexB(s32 e) { if (e) return 0x1C; return 0x1D; }
void badge_disp(BWin* w, f32 xo, f32 yo) {
    BWin* p0;
    ItemData* item;
    s8* cost;
    s32 j;
    GXColor colA = {255, 255, 255, 255};
    GXColor colB;
    GXColor colU;
    GXColor colD;
    char buf[64];
    s32 cnt;
    s32 rowOff;
    s32 i;
    s32 badge;
    s32 equipped;
    s32 gray;
    f32 scroll;
    f32 width;
    s32 tw;

    if (w->tab == 0) {
        cnt = pouchGetHaveBadgeCnt();
    } else {
        cnt = w->count;
    }
    GXSetScissor(0, 0x77, 0x260, 0xB8);
    p0 = w;
    for (i = 0, rowOff = 0; i < cnt; p0 = (BWin*)((u8*)p0 + 12), rowOff += 23, i++) {
        if (w->tab == 0) {
            badge = pouchHaveBadge(i);
        } else {
            badge = p0->list[0].id;
        }
        scroll = w->cur[w->tab];
        if (w->tab == 0) {
            equipped = pouchEquipCheckBadgeIndex(i);
        } else {
            equipped = p0->list[0].equipped;
        }
        if ((scroll + ((yo + 110.0f) - (f32)rowOff)) > 240.0f) {
            continue;
        }
        if ((scroll + ((yo + 110.0f) - (f32)rowOff)) < -240.0f) {
            break;
        }
        if (equipped) {
            winTexInit(w->res->tex->tpl);
            winTexSet(0x1E, (Vec){82.0f + xo, (scroll + ((yo + 110.0f) - (f32)rowOff)), 0.0f}, (Vec){44.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
        }
        if (!equipped && itemDataTable[badge].bp_cost > pouchGetPtr()->availableBP) {
            colB = (GXColor){0x7F, 0x7F, 0x7F, 0xFF};
            gray = 1;
        } else {
            colB = (GXColor){0, 0, 0, 0xFF};
            gray = 0;
        }
        if (!gray) {
            winIconInit();
        } else {
            winIconGrayInit();
        }
        winIconSet(itemDataTable[badge].icon_id, (Vec){xo - 75.0f, (scroll + ((yo + 110.0f) - (f32)rowOff)), 0.0f}, (Vec){0.54f, 0.54f, 0.54f}, colA);
        item = &itemDataTable[badge];
        winFontInit();
#ifdef VERSION_G8ME01
        winFontSetWidth((Vec){xo - 55.0f, scroll + (12.0f + ((yo + 110.0f) - (f32)rowOff)), 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, colB, 170.0f, msgSearch(item->name));
#else
        winFontSet((Vec){xo - 55.0f, scroll + (12.0f + ((yo + 110.0f) - (f32)rowOff)), 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, colB, item->id);
#endif
        cost = &item->bp_cost;
        sprintf(buf, "%s", winZenkakuStr(*cost));
        winFontSet((Vec){(142.0f + xo) - (f32)(FontGetMessageWidth(buf) / 2), scroll + (12.0f + ((yo + 110.0f) - (f32)rowOff)), 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, colB, buf);
        winTexInit(w->res->tex->tpl);
        for (j = 0; j < *cost; j++) {
            { s32 t; winTexSet((t = 0x1D, equipped ? t = 0x1C : 0, t), (Vec){(160.0f + xo) + j * 13, (scroll + ((yo + 110.0f) - (f32)rowOff)), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, colA); }
        }
    }
    GXSetScissor(0, 0, 0x260, 0x1E0);
    {
        f32 ax;
        colU = (GXColor){255, 255, 255, 255};
        colD = (GXColor){0, 0, 0, 255};

        if (w->page[w->tab] > 0) {
            winTexInit(w->res->tex->tpl);
            ax = 250.0f + xo;
            winTexSet(0x17, (Vec){ax, 20.0f + (18.0f + (110.0f + yo)), 0.0f}, (Vec){-1.0f, -1.0f, -1.0f}, colU);
            winIconInit();
            winIconSet(ICON_07E, (Vec){ax, 20.0f + (113.0f + yo), 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, colU);
        }
        if (cnt > w->page[w->tab] * 8 + 8) {
            winTexInit(w->res->tex->tpl);
            ax = 250.0f + xo;
            winTexSet(0x17, (Vec){ax, 20.0f + ((yo - 90.0f) - 15.0f), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, colU);
            winIconInit();
            winIconSet(ICON_080, (Vec){ax, 20.0f + (yo - 90.0f), 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, colU);
        }
        width = 0.7f * (f32)(u32)FontGetMessageWidth(msgSearch("msg_menu_sort_narabikae"));
        winFontInit();
        width = xo + (220.0f - width);
        winFontSet((Vec){width, 20.0f + ((yo - 92.0f) - 10.0f), 0.0f}, (Vec){0.7f, 0.7f, 0.7f}, colD, msgSearch("msg_menu_sort_narabikae"));
        winIconInit();
        winIconSet(ICON_217, (Vec){width - 30.0f, 20.0f + ((yo - 100.0f) - 10.0f), 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, colU);
        winFontInit();
        winFontSet((Vec){120.0f + xo, 135.0f + yo, 0.0f}, (Vec){0.5f, 0.5f, 0.5f}, colD, msgSearch("msg_menu_badge_hituyou"));
    }
}
