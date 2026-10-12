#include "win/win_main.h"
#include "data/item_data.h"
#include "driver/animdrv.h"
#include "mario/mario.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "driver/msgdrv.h"
#include "manager/fontmgr.h"
#include "pmario_sound.h"
#include <dolphin/gx.h>
#include <string.h>

extern ItemData itemDataTable[];
extern int sprintf(char* str, const char* format, ...);
void winMsgEntry(void* wp, s32 a, const char* msg, s32 b);
void winIconInit(void);
void winIconSet(u32 id, Vec translate, Vec scale, GXColor color);

typedef struct WinMarioWork {
    u16 flags;                    // 0x0
    u8 pad_2[2];                  // 0x2
    u32 buttonTrg;                // 0x4
    u32 buttonRep;                // 0x8
    u32 dirTrg;                   // 0xC
    u32 dirRep;                   // 0x10
    u8 pad_14[0x28 - 0x14];       // 0x14
    struct { u8 pad[0xA0]; void** data; }* file; // 0x28
    u8 pad_2C[0xC0 - 0x2C];       // 0x2C
    struct { s32 field_0x0; f32 x; f32 y; f32 w; f32 h; } pos[2]; // 0xC0
    u8 pad_E8[0x158 - 0xE8];      // 0xE8
    f32 msgX;                     // 0x158
    f32 msgY;                     // 0x15C
    s32 idx;                      // 0x160
    u8 pad_164[0x188 - 0x164];    // 0x164
    s32 poseId;                   // 0x188
    s32 f18C;                     // 0x18C
    s32 f190;                     // 0x190
    s32 f194;                     // 0x194
    s32 f198;                     // 0x198
} WinMarioWork;

typedef struct LinkDt {
    s16 x;              // 0x0
    s16 y;              // 0x2
    const char* pose0;  // 0x4
    const char* pose1;  // 0x8
    const char* pose2;  // 0xC
    u16 item;           // 0x10
    u16 f12;            // 0x12
    const char* msg;    // 0x14
    u8 links[4];        // 0x18
} LinkDt;

typedef struct SuperAction {
    const char* name;  // 0x0
    u8 pad_4[0xC - 0x4];
    const char* desc;  // 0xC
    u8 pad_10[2];
    u8 cost;           // 0x12
} SuperAction;
extern SuperAction* superActionTable[];

LinkDt linkDt[18] = {
    {-268, 142, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_mario_lv", {6, 1, 11, 9}},
    {-268, 118, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_mario_star_r", {0, 2, 11, 7}},
    {-272, 68, "M_H_1", NULL, "R_1", 9, 0, NULL, {1, 3, 11, 7}},
    {-242, 24, "M_R_1", NULL, "R_1", 6, 0, NULL, {2, 4, 11, 8}},
    {-270, -34, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_mario_hp", {3, 5, 13, 13}},
    {-270, -68, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_mario_fp", {4, 6, 13, 13}},
    {-270, -102, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_mario_bp", {5, 0, 13, 13}},
    {-100, 90, "M_S_1", "M_S_1", "S_1", 2, 0, "msg_slit", {9, 10, 2, 9}},
    {-100, 20, "M_S_1", "M_S_1", "S_1", 4, 0, "msg_plane", {10, 4, 3, 10}},
    {-50, 130, "M_S_1", "M_S_1", "S_1", 5, 0, "msg_ship", {0, 7, 0, 11}},
    {-50, 60, "M_S_1", "M_S_1", "S_1", 3, 0, "msg_roll", {7, 8, 8, 12}},
    {20, 106, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_star_power", {17, 12, 9, 0}},
    {20, 70, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_mario_waza", {11, 13, 10, 0}},
    {3, 10, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_mario_star_p", {12, 14, 4, 4}},
    {3, -18, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_mario_coin", {13, 15, 4, 4}},
    {3, -46, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_mario_kakera", {14, 16, 4, 4}},
    {3, -74, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_mario_scoin", {15, 17, 4, 4}},
    {3, -102, "M_S_1", NULL, "S_1", 0, 0, "msg_menu_mario_time", {16, 11, 4, 4}},
};

const char* hammer_help[] = {NULL, "msg_hammer_1", "msg_hammer_2", "msg_hammer_3"};
const char* boots_help[] = {NULL, "msg_boots_1", "msg_boots_2", "msg_boots_3"};
const char* hammer_pose[] = {NULL, "M_H_1", "M_H_4", "M_H_7"};

char unk_803dfbf8[0x100];

void winMarioInit(WinMarioWork* w) {
    PouchData* pouch;
    const char* name;
    s32 i;

    pouch = pouchGetPtr();
    if (w->flags & 0x2000) {
        name = "S_1";
        switch (marioGetColor()) {
            case 0:
                name = "S_1";
                break;
            case 1:
                name = "S_2";
                break;
            case 2:
                name = "S_3";
                break;
            case 3:
                name = "S_4";
                break;
        }
        w->poseId = animPoseEntry("d_mario", 0);
        animPoseSetAnim(w->poseId, name, 1);
    } else {
        name = "a_mario";
        switch (marioGetColor()) {
            case 0: name = "a_mario"; break;
            case 1: name = "a_mario_l"; break;
            case 2: name = "a_mario_w"; break;
            case 3: name = "a_mario_wl"; break;
        }
        w->poseId = animPoseEntry(name, 0);
        animPoseSetAnim(w->poseId, "M_S_1", 1);
    }
    animPoseSetMaterialFlagOn(w->poseId, 0x1800);
    if (marioGetPtr()->flags & 0x40000000) {
        animPoseSetMaterialFlagOn(w->poseId, 0x0A000000);
    }
    w->f18C = 0;
    w->f190 = 0;
    w->f194 = 0;
    w->f198 = 0;
    for (i = 0; i < 8; i++) {
        if (*(u16*)&pouch->mStarPowersObtained & (1 << i)) {
            w->f198++;
        }
    }
}


void winMarioInit2(WinMarioWork* w) {
    w->idx = 0;
    w->msgX = w->msgX = linkDt[w->idx].x;
    w->msgY = w->msgY = linkDt[w->idx].y;
    switch (w->idx) {
    case 2:
        winMsgEntry(w, 0, hammer_help[pouchGetHammerLv()], 0);
        break;
    case 3:
        winMsgEntry(w, 0, boots_help[pouchGetJumpLv()], 0);
        break;
    default:
        winMsgEntry(w, 0, linkDt[w->idx].msg, 0);
        break;
    }
    w->f18C = 0;
    w->f190 = 0;
    w->f194 = 0;
}

void winMarioExit(WinMarioWork* w) {
    animPoseRelease(w->poseId);
}

#define COLOR_ANIM(var, base)                         \
    if (strcmp(base, "S_1") == 0) {                   \
        switch (marioGetColor()) {                    \
            case 0: var = "S_1"; break;               \
            case 1: var = "S_2"; break;               \
            case 2: var = "S_3"; break;               \
            case 3: var = "S_4"; break;               \
        }                                             \
    } else {                                          \
        switch (marioGetColor()) {                    \
            case 0: var = "R_1"; break;               \
            case 1: var = "R_15"; break;              \
            case 2: var = "R_17"; break;              \
            case 3: var = "R_18"; break;              \
        }                                             \
    }

#define NAV(n)                                                        \
    w->idx = linkDt[w->idx].links[n];                                 \
    p = &linkDt[w->idx];                                              \
    while (1) {                                                       \
        if (w->idx == 11 || w->idx == 12) {                           \
            if (w->f198 != 0) break;                                  \
        } else if (p->item == 0 || ((s32(*)(u32))pouchCheckItem)(p->item) != 0) {    \
            break;                                                    \
        }                                                             \
        w->idx = p->links[n];                                         \
        p = &linkDt[w->idx];                                          \
    }                                                                 \
    psndSFXOn((const char*)0x20005);

s32 winMarioMain(WinMarioWork* w) {
    const char* anim2;
    const char* anim;
    LinkDt* lp;
    LinkDt* p;

    switch (w->f190) {
        case 0:
            if (w->buttonTrg & 0x100) {
                if (w->idx == 12) {
                    w->f190 = 1;
                    w->f194 = 0;
                    psndSFXOn((const char*)0x20012);
                }
            } else if (w->buttonTrg & 0x200) {
                psndSFXOn((const char*)0x20013);
                if (w->flags & 0x2000) {
                    COLOR_ANIM(anim, "S_1")
                } else {
                    anim = "M_S_1";
                }
                animPoseSetAnim(w->poseId, anim, 0);
                return -1;
            } else if (w->buttonTrg & 0x1000) {
                return -2;
            } else if (w->dirRep & 0x1000) {
                NAV(0)
            } else if (w->dirRep & 0x2000) {
                NAV(1)
            } else if (w->dirRep & 0x4000) {
                NAV(2)
            } else if (w->dirRep & 0x8000) {
                NAV(3)
            }
            lp = &linkDt[w->idx];
            w->msgX = lp->x;
            w->msgY = lp->y;
            switch (w->idx) {
            case 2:
                if (w->flags & 0x2000) {
                    COLOR_ANIM(anim2, lp->pose2)
                } else {
                    anim2 = hammer_pose[pouchGetHammerLv()];
                }
                animPoseSetAnim(w->poseId, anim2, 0);
                if (w->f18C == 0) {
                    if (animPoseGetLoopTimes(w->poseId) >= 0.89f) {
                        w->f18C = 30;
                    }
                } else {
                    w->f18C--;
                }
                if (w->flags & 0x2000) {
                    w->f18C = 0;
                }
                break;
            default:
                w->f18C = 0;
                if (w->flags & 0x2000) {
                    COLOR_ANIM(anim2, lp->pose2)
                } else {
                    anim2 = lp->pose0;
                }
                animPoseSetAnim(w->poseId, anim2, 0);
                break;
            }
            switch (w->idx) {
                case 2:
                    winMsgEntry(w, 0, hammer_help[pouchGetHammerLv()], 0);
                    break;
                case 3:
                    winMsgEntry(w, 0, boots_help[pouchGetJumpLv()], 0);
                    break;
                default:
                    winMsgEntry(w, 0, lp->msg, 0);
                    break;
            }
            break;
        case 1:
            if (w->dirRep & 0x1000) {
                w->f194--;
                if (w->f194 < 0) {
                    w->f194 = w->f198 - 1;
                }
                psndSFXOn((const char*)0x20005);
            } else if (w->dirRep & 0x2000) {
                w->f194++;
                if (w->f194 >= w->f198) {
                    w->f194 = 0;
                }
                psndSFXOn((const char*)0x20005);
            } else if (w->buttonTrg & 0x200) {
                w->f190 = 0;
                psndSFXOn((const char*)0x20013);
            } else if (w->buttonTrg & 0x1000) {
                return -2;
            }
            w->msgX = -280.0f;
            w->msgY = 10.0f + (120.0f - 26.0f * w->f194 - 12.0f);
            winMsgEntry(w, 0, superActionTable[w->f194]->desc, 0);
            break;
    }
    return 0;
}

void winMarioMain2(void) {
}

const char* winZenkakuStr(s32 n) {
    const char* tbl[10] = {"\x82\x4f", "\x82\x50", "\x82\x51", "\x82\x52", "\x82\x53",
                           "\x82\x54", "\x82\x55", "\x82\x56", "\x82\x57", "\x82\x58"};
    static char tmp2[0x100];
    char buf[0x100];
    u32 i;
    if (n < 0) {
        strcpy(tmp2, "\x81\x7c");
        n = -n;
    } else {
        strcpy(tmp2, "");
    }
    sprintf(buf, "%d", n);
    for (i = 0; i < strlen(buf); i++) {
        strcat(tmp2, tbl[(s8)buf[i] - '0']);
    }
    return tmp2;
}

char* unk_8016af5c(s32 n, s32 digits) {
    const char* tbl[10] = {"\x82\x4f", "\x82\x50", "\x82\x51", "\x82\x52", "\x82\x53",
                           "\x82\x54", "\x82\x55", "\x82\x56", "\x82\x57", "\x82\x58"};
    char buf[0x100];
    s32 i;
    if (n < 0) {
        strcpy(unk_803dfbf8, "\x81\x7c");
        n = -n;
    } else {
        strcpy(unk_803dfbf8, "");
    }
    sprintf(buf, "%d", n);
    for (i = 0; i < digits; i++) {
        if ((u32)i < (u32)(digits - strlen(buf))) {
            strcat(unk_803dfbf8, "\x82\x4f");
        } else {
            strcat(unk_803dfbf8, tbl[(s8)buf[i - (digits - strlen(buf))] - '0']);
        }
    }
    return unk_803dfbf8;
}


static inline void fukiKey(WinMarioWork* w, u16 icon, f32 x, f32 y) {
    winTexInit(*w->file->data);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    winTexSet(0xB1, (Vec){x + 5.0f, y - 5.0f, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, (GXColor){0x00, 0x00, 0x00, 0x80});
    winTexSet(0xB1, (Vec){x, y, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, (GXColor){0xE1, 0xE1, 0xE1, 0xFE});
    winIconInit();
    winIconSet(icon, (Vec){x + 6.0f, y, 0.0f}, (Vec){0.7f, 0.7f, 0.7f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
}

static inline void fukiTool(WinMarioWork* w, u16 icon, f32 x, f32 y) {
    winTexInit(*w->file->data);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    winTexSet(0xB1, (Vec){x + 5.0f, y - 5.0f, 0.0f}, (Vec){-0.8f, 0.8f, 0.8f}, (GXColor){0x00, 0x00, 0x00, 0x80});
    winTexSet(0xB1, (Vec){x, y, 0.0f}, (Vec){-0.8f, 0.8f, 0.8f}, (GXColor){0xE1, 0xE1, 0xE1, 0xFE});
    winIconInit();
    winIconSet(icon, (Vec){x - 6.0f, y, 0.0f}, (Vec){0.7f, 0.7f, 0.7f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
}

void fukidashi(WinMarioWork* w, u32 idx, f32 x, f32 y) {
    switch (idx) {
        case 2:
            if (pouchGetHammerLv() > 0) {
                fukiTool(w, itemDataTable[pouchGetHammerLv() + 8].icon_id, x - 230.0f, y + 72.0f);
            }
            break;
        case 3:
            if (pouchGetJumpLv() > 0) {
                fukiTool(w, itemDataTable[pouchGetJumpLv() + 5].icon_id, x - 210.0f, y + 20.0f);
            }
            break;
        case 7:
            if (((s32(*)(u32))pouchCheckItem)(2)) {
                fukiKey(w, itemDataTable[2].icon_id, x - 80.0f, y + 90.0f);
            }
            break;
        case 8:
            if (((s32(*)(u32))pouchCheckItem)(4)) {
                fukiKey(w, itemDataTable[4].icon_id, x - 80.0f, y + 20.0f);
            }
            break;
        case 9:
            if (((s32(*)(u32))pouchCheckItem)(5)) {
                fukiKey(w, itemDataTable[5].icon_id, x - 30.0f, y + 130.0f);
            }
            break;
        case 10:
            if (((s32(*)(u32))pouchCheckItem)(3)) {
                fukiKey(w, itemDataTable[3].icon_id, x - 30.0f, y + 60.0f);
            }
            break;
    }
}

void winBgGX(WinMarioWork* w, s32 a, f32 x, f32 y);
void winNameGX(WinMarioWork* w, s32 a, f32 x, f32 y, f32 w_, f32 h);
void winKirinukiGX(WinMarioWork* w, s32 a, f32 x, f32 y, f32 w_, f32 h);
void winWazaGX(WinMarioWork* w, s32 a, f32 x, f32 y, f32 w_, f32 h);
void winKageGX(WinMarioWork* w, GXColor color, f32 x, f32 y, f32 z, f32 scale);
void winZClear(void);
void winFontInit(void);
void winFontSet(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetR(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetEdge(Vec pos, Vec scale, GXColor color, const char* fmt, ...);
void winFontSetLabel(Vec pos, Vec scale, GXColor color, const char* msg);
const char* BattleGetRankNameLabel(s32 level);

void winMarioDisp(s32 camId, WinMarioWork* w, s32 idx) {
    static s32 pri[6] = {3, 2, 8, 10, 7, 9};
    GXColor white2;
    GXColor black2;
    GXColor white;
    GXColor black;
    PouchData* pouch;
    f32 x;
    f32 y;
    f32 v29;
    f32 v28;
    f32 v27;
    f32 v26;
    f32 v25;
    f32 v24;
    f32 v23;
    f32 v22;
    f32 v21;
    f32 v20;
    f32 v19;
    f32 v18;
    s32 i;
    u64 secs;
    s32 hour;
    s32 min;
    AnimData* anim;
    Mtx mtx;
    char buf[0x100];

    pouch = pouchGetPtr();
    white = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
    white2 = white;
    black = (GXColor){0x00, 0x00, 0x00, 0xFF};
    black2 = black;
    x = w->pos[idx].x;
    y = w->pos[idx].y;
    winBgGX(w, 0, x, y);
    winNameGX(w, 2, x - 265.0f, 154.0f + y, 190.0f, 24.0f);
    v18 = 10.0f + (x - 265.0f);
    winFontInit();
    v25 = 152.0f + y;
    winFontSetEdge((Vec){v18, v25, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, msgSearch("name_mario"));
    v18 += 0.8f * FontGetMessageWidth(msgSearch("name_mario"));
    v18 += 20.0f;
    winIconInit();
    winIconSet(0x19E, (Vec){v18, 142.0f + y, 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, white);
    v18 += 20.0f;
    winFontInit();
    winFontSetEdge((Vec){v18, v25, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, msgSearch("msg_menu_mario_level"));
    sprintf(buf, "%s", winZenkakuStr(pouch->level));
    winFontInit();
    winFontSetEdge((Vec){(190.0f + (x - 265.0f)) - 0.8f * FontGetMessageWidth(buf) - 10.0f, v25, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, buf);
    winTexInit(*w->file->data);
    winTexSet(0xB0, (Vec){x - 255.0f, 112.0f + y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    winFontInit();
    winFontSet((Vec){x - 240.0f, 124.0f + y, 0.0f}, (Vec){0.7f, 0.7f, 0.7f}, black, msgSearch(BattleGetRankNameLabel(pouch->level)));

    for (i = 0; i < 6; i++) {
        if (w->idx != pri[i]) {
            fukidashi(w, pri[i], x, y);
        }
    }
    fukidashi(w, w->idx, x, y);

    winKirinukiGX(w, 0, x - 270.0f, y - 10.0f, 264.0f, 110.0f);
    v24 = 50.0f + (x - 270.0f);
    v25 = v24 - 2.0f;
    for (i = 0; i < 3; i++) {
        GXColor cols[3] = {{0xCB, 0x8C, 0xA2, 0xFE}, {0xCB, 0xBE, 0x89, 0xFE}, {0x94, 0xB9, 0xC7, 0xFE}};
        GXColor reds[3] = {{0xA7, 0x3C, 0x3C, 0xFF}, {0x37, 0x69, 0x1E, 0xFF}, {0x0F, 0x21, 0x7A, 0xFF}};
        const char* N_stat_name_tbl[3] = {"\x82\x67\x82\x6F", "\x82\x65\x82\x6F", "\x82\x61\x82\x6F"};
        const char* ruby[3] = {"msg_menu_mario_ruby_hp", "msg_menu_mario_ruby_fp", "msg_menu_mario_ruby_bp"};

        v23 = FontGetMessageWidth(N_stat_name_tbl[i]);
        v22 = 0.5f * FontGetMessageWidth(msgSearch(ruby[i]));
        winTexInit(*w->file->data);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        v18 = (y - 38.0f) - (f32)(i * 34);
        winTexSet(0xAF, (Vec){v25, v18 - 4.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, cols[i]);
        winFontInit();
        winFontSet((Vec){v24 - v23 * 0.5f, 12.0f + v18, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black2, N_stat_name_tbl[i]);
        winFontSet((Vec){v24 - v22 * 0.5f, 21.0f + v18, 0.0f}, (Vec){0.5f, 0.5f, 0.5f}, reds[i], msgSearch(ruby[i]));
    }

    winIconInit();
    v18 = 110.0f + (x - 270.0f);
    v26 = 4.0f + (y - 38.0f);
    winIconSet(0x19F, (Vec){v18, v26, 0.0f}, (Vec){0.82f, 0.82f, 0.82f}, white);
    v24 = (y - 38.0f) - 34.0f;
    v27 = 4.0f + v24;
    winIconSet(0x1A0, (Vec){v18, v27, 0.0f}, (Vec){0.82f, 0.82f, 0.82f}, white);
    v25 = (y - 38.0f) - 68.0f;
    winIconSet(0x1A1, (Vec){v18, 4.0f + v25, 0.0f}, (Vec){0.82f, 0.82f, 0.82f}, white);
    winFontInit();
    v18 = 130.0f + (x - 270.0f);
    v28 = 4.0f + (12.0f + (y - 38.0f));
    winFontSetR((Vec){v18, v28, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->currentHP));
    v24 = 4.0f + (12.0f + v24);
    winFontSetR((Vec){v18, v24, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->currentFP));
    winFontSetR((Vec){v18, 4.0f + (12.0f + v25), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->maximumBP));
    winTexInit(*w->file->data);
    v18 = 190.0f + (x - 270.0f);
    winTexSet(0x10, (Vec){v18, v26, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    winTexSet(0x10, (Vec){v18, v27, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    winFontInit();
    v18 = 200.0f + (x - 270.0f);
    winFontSet((Vec){v18, v28, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->maximumHP));
    winFontSet((Vec){v18, v24, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->maximumFP));

    if (w->f198 > 0) {
        winKirinukiGX(w, 0, 10.0f + x, (20.0f + (130.0f + y)) - 20.0f, 260.0f, 80.0f);
        winIconInit();
        v18 = 10.0f + (40.0f + x);
        v24 = 106.0f + y;
        winIconSet(0x20F, (Vec){v18, v24, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white);
        v19 = 70.0f + y;
        winIconSet(0x197, (Vec){v18, v19, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white);
        winFontInit();
        winFontSet((Vec){10.0f + (70.0f + x), 10.0f + v19, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, msgSearch("msg_menu_mario_special"));
        winIconInit();
        v19 = 10.0f + (80.0f + x);
        for (i = 0; i < w->f198; i++) {
            if (i < pouch->currentSP / 100) {
                winIconSet(0x1B7 + i, (Vec){v19 + (f32)(i * 22), v24, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white2);
            } else {
                winIconSet(0x1BF, (Vec){v19 + (f32)(i * 22), v24, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white2);
            }
        }
    }

    v23 = 10.0f + x;
    winKirinukiGX(w, 0, v23, 10.0f + (20.0f + y), 260.0f, 150.0f);
    winIconInit();
    v24 = 10.0f + (20.0f + x);
    winIconSet(0x18C, (Vec){v24, 10.0f + y, 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x18B, (Vec){v24, 10.0f + (y - 28.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x18D, (Vec){v24, 10.0f + (y - 56.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x102, (Vec){v24, 10.0f + (y - 84.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x1A2, (Vec){v24, 10.0f + (y - 112.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winFontInit();
    v24 = 10.0f + (35.0f + x);
    v25 = 12.0f + y;
    v26 = 10.0f + v25;
    winFontSet((Vec){v24, v26, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_sp"));
    v27 = 10.0f + (v25 - 28.0f);
    winFontSet((Vec){v24, v27, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_coin"));
    v28 = 10.0f + (v25 - 56.0f);
    winFontSet((Vec){v24, v28, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_hoshi"));
    v29 = 10.0f + (v25 - 84.0f);
    winFontSet((Vec){v24, v29, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_super_coin"));
    v25 = 10.0f + (v25 - 112.0f);
    winFontSet((Vec){v24, v25, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_playtime"));
    v18 = 2.0f + (8.0f + (205.0f + x));
    winFontSetR((Vec){v18, v26, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->mStarPoints));
    winFontSetR((Vec){v18, v27, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->coins));
    winFontSetR((Vec){v18, v28, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->mStarPieceCount));
    winFontSetR((Vec){v18, v29, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->mShineSpriteCount));

    secs = gp->retraceLocalTime / (*(u32*)0x800000F8 >> 2);
    if (secs > 359999) {
        hour = 99;
        min = 59;
    } else {
        hour = secs / 3600;
        min = secs % 3600 / 60;
    }
    winFontSetR((Vec){2.0f + (2.0f + ((8.0f + (172.0f + x)) - 16.0f)), v25, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", unk_8016af5c(hour, 2));
    winFontSetR((Vec){v18, v25, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", unk_8016af5c(min, 2));

    winTexInit(*w->file->data);
    v19 = 10.0f + (190.0f + x);
    for (i = 0; i < 4; i++) {
        winTexSet(0x11, (Vec){v19, 10.0f + (y - (f32)(i * 28)), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    }
    v24 = 220.0f + x;
    winTexSet(0x12, (Vec){v24, (10.0f + (2.0f + (y - 112.0f))) - 2.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);

    animPoseGetAnimPosePtr(w->poseId);
    anim = animPoseGetAnimDataPtr(w->poseId);
    if (w->f18C == 0) {
        animPoseSetLocalTime(w->poseId, (f32)(gp->retraceCount % (s32)(*(f32*)(*(u8**)((u8*)anim + 0x24) + 8))));
    }
    animPoseMain(w->poseId);
    winKageGX(w, (GXColor){0x00, 0x00, 0x00, 0x80}, x - 150.0f, y, 0.0f, 1.0f);
    PSMTXTrans(mtx, x - 150.0f, y, 0.0f);
    winZClear();
    animPoseDrawMtx(w->poseId, mtx, 2, 0.0f, 5.0f);

    if (w->f190) {
        winWazaGX(w, 0, x - 270.0f, 160.0f, 270.0f, 254.0f);
        winFontInit();
        winFontSetEdge((Vec){(90.0f + x) - 270.0f, 155.0f, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, msgSearch("msg_menu_mario_sac_waza"));
        winFontSetEdge((Vec){v24 - 270.0f, 155.0f, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, "\x82\x72\x82\x6F");
        v20 = (228.0f + x) - 270.0f;
        v19 = 10.0f + (v23 - 270.0f);
        v21 = 4.0f + ((17.0f + v24) - 270.0f);
        for (i = 0; i < w->f198; i++) {
            char sbuf[0x20];

            winFontSetLabel((Vec){v19, (f32)(130 - i * 26), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black2, superActionTable[i]->name);
            sprintf(sbuf, "%s", winZenkakuStr(superActionTable[i]->cost));
            winFontSet((Vec){v20 - (f32)(FontGetMessageWidth(sbuf) / 2), (f32)(130 - i * 26), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black2, sbuf);
            winFontSet((Vec){v21, (f32)(120 - i * 26), 0.0f}, (Vec){0.5f, 0.5f, 0.5f}, black2, "\x82\x72\x82\x6F");
        }
    }
}
