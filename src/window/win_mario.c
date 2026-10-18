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
extern const char str_802F5650[];
extern const char str_802F5664[];
extern const char str_802F567C[];
extern const char str_802F5690[];
extern const char str_802F56A4[];
extern const char str_802F56B8[];
extern const char str_802F56C4[];
extern const char str_802F56D0[];
extern const char str_802F56DC[];
extern const char str_802F56E8[];
extern const char str_802F56FC[];
extern const char str_802F5710[];
extern const char str_802F5728[];
extern const char str_802F573C[];
extern const char str_802F5754[];
extern const char str_802F576C[];
extern const char str_802F5780[];
extern const char str_802F5790[];
extern const char str_802F57A0[];
extern const char str_802F57B0[];
extern const char str_802F57BC[];
extern const char str_802F57C8[];
extern const char str_8041D578[];
extern const char str_8041D580[];
extern const char str_8041D584[];
extern const char str_8041D58C[];
extern const char str_8041D590[];
extern const char str_8041D598[];
extern const char str_8041D5A0[];

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
    {-268, 142, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5650), {6, 1, 11, 9}},
    {-268, 118, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5664), {0, 2, 11, 7}},
    {-272, 68, ((char*)str_8041D584), NULL, ((char*)str_8041D58C), 9, 0, NULL, {1, 3, 11, 7}},
    {-242, 24, ((char*)str_8041D590), NULL, ((char*)str_8041D58C), 6, 0, NULL, {2, 4, 11, 8}},
    {-270, -34, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F567C), {3, 5, 13, 13}},
    {-270, -68, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5690), {4, 6, 13, 13}},
    {-270, -102, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F56A4), {5, 0, 13, 13}},
    {-100, 90, ((char*)str_8041D578), ((char*)str_8041D578), ((char*)str_8041D580), 2, 0, ((char*)str_802F56B8), {9, 10, 2, 9}},
    {-100, 20, ((char*)str_8041D578), ((char*)str_8041D578), ((char*)str_8041D580), 4, 0, ((char*)str_802F56C4), {10, 4, 3, 10}},
    {-50, 130, ((char*)str_8041D578), ((char*)str_8041D578), ((char*)str_8041D580), 5, 0, ((char*)str_802F56D0), {0, 7, 0, 11}},
    {-50, 60, ((char*)str_8041D578), ((char*)str_8041D578), ((char*)str_8041D580), 3, 0, ((char*)str_802F56DC), {7, 8, 8, 12}},
    {20, 106, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F56E8), {17, 12, 9, 0}},
    {20, 70, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F56FC), {11, 13, 10, 0}},
    {3, 10, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5710), {12, 14, 4, 4}},
    {3, -18, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5728), {13, 15, 4, 4}},
    {3, -46, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F573C), {14, 16, 4, 4}},
    {3, -74, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F5754), {15, 17, 4, 4}},
    {3, -102, ((char*)str_8041D578), NULL, ((char*)str_8041D580), 0, 0, ((char*)str_802F576C), {16, 11, 4, 4}},
};
const char* hammer_help[] = {NULL, ((char*)str_802F5780), ((char*)str_802F5790), ((char*)str_802F57A0)};
const char* boots_help[] = {NULL, ((char*)str_802F57B0), ((char*)str_802F57BC), ((char*)str_802F57C8)};
const char* hammer_pose[] = {NULL, ((char*)str_8041D584), ((char*)str_8041D598), ((char*)str_8041D5A0)};

#ifdef NONMATCHING
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
            case 3: name = "a_mario_wl\0\0\0\0\0"; break;
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
#endif


#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
void winMarioExit(WinMarioWork* w) {
    animPoseRelease(w->poseId);
}
#endif

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

#ifdef NONMATCHING
s32 winMarioMain(WinMarioWork* w) {
    const char* anims[2];
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
                    COLOR_ANIM(anims[1], "S_1")
                } else {
                    anims[1] = "M_S_1";
                }
                animPoseSetAnim(w->poseId, anims[1], 0);
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
                    COLOR_ANIM(anims[0], lp->pose2)
                } else {
                    anims[0] = hammer_pose[pouchGetHammerLv()];
                }
                animPoseSetAnim(w->poseId, anims[0], 0);
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
                    COLOR_ANIM(anims[0], lp->pose2)
                } else {
                    anims[0] = lp->pose0;
                }
                animPoseSetAnim(w->poseId, anims[0], 0);
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
#endif

#ifdef NONMATCHING
void winMarioMain2(void) {
}
#endif

#ifdef NONMATCHING
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
#endif

// FAKE: tmp2 (target local static, .bss after unk_803dfbf8) folded in as unk_803dfbf8+0x100; MWCC would not emit them in target order
char unk_803dfbf8[0x200];

#ifdef NONMATCHING
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
#endif


#ifdef NONMATCHING
static inline void fukiKey(WinMarioWork* w, u16 icon, f32 x, f32 y) {
    winTexInit(*w->file->data);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    winTexSet(0xB1, (Vec){x + 5.0f, y - 5.0f, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, (GXColor){0x00, 0x00, 0x00, 0x80});
    winTexSet(0xB1, (Vec){x, y, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, (GXColor){0xE1, 0xE1, 0xE1, 0xFE});
    winIconInit();
    winIconSet(icon, (Vec){x + 6.0f, y, 0.0f}, (Vec){0.7f, 0.7f, 0.7f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
}
#endif

#ifdef NONMATCHING
static inline void fukiTool(WinMarioWork* w, u16 icon, f32 x, f32 y) {
    winTexInit(*w->file->data);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    winTexSet(0xB1, (Vec){x + 5.0f, y - 5.0f, 0.0f}, (Vec){-0.8f, 0.8f, 0.8f}, (GXColor){0x00, 0x00, 0x00, 0x80});
    winTexSet(0xB1, (Vec){x, y, 0.0f}, (Vec){-0.8f, 0.8f, 0.8f}, (GXColor){0xE1, 0xE1, 0xE1, 0xFE});
    winIconInit();
    winIconSet(icon, (Vec){x - 6.0f, y, 0.0f}, (Vec){0.7f, 0.7f, 0.7f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
}
#endif

#ifdef NONMATCHING
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
#endif

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



#ifdef NONMATCHING
void winMarioDisp(s32 camId, void* param, s32 idx) {
    static s32 pri[6] = {3, 2, 8, 10, 7, 9};
    WinMarioWork* w;
    GXColor white;
    GXColor black;
    PouchData* pouch;
    f32 x;
    f32 y;
    f32 statX;
    f32 rowA;
    f32 rowB;
    f32 cx;
    f32 col;
    f32 nameW;
    f32 row2;
    f32 left;
    f32 row0;
    f32 row1;
    f32 numX;
    f32 costX;
    f32 row3;
    f32 rubyW;
    s32 i;
    s64 secs;
    u64 tsecs;
    s32 hour;
    s32 min;
    AnimData* anim;
    Mtx mtx;
    char buf[0x100];

    w = param;
    pouch = pouchGetPtr();
    white = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
    black = (GXColor){0x00, 0x00, 0x00, 0xFF};
    x = w->pos[idx].x;
    y = w->pos[idx].y;
    winBgGX(w, 0, x, y);
    winNameGX(w, 2, x - 265.0f, 154.0f + y, 190.0f, 24.0f);
    cx = 10.0f + (x - 265.0f);
    winFontInit();
    rowA = 152.0f + y;
    winFontSetEdge((Vec){cx, rowA, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, msgSearch("name_mario"));
    cx += 0.8f * FontGetMessageWidth(msgSearch("name_mario"));
    cx += 20.0f;
    winIconInit();
    winIconSet(0x19E, (Vec){cx, 142.0f + y, 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, white);
    cx += 20.0f;
    winFontInit();
    winFontSetEdge((Vec){cx, rowA, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, msgSearch("msg_menu_mario_level"));
    sprintf(buf, "%s", winZenkakuStr(pouch->level));
    winFontInit();
    winFontSetEdge((Vec){(190.0f + (x - 265.0f)) - 0.8f * FontGetMessageWidth(buf) - 10.0f, rowA, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, buf);
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
    rowA = 50.0f + (x - 270.0f) - 2.0f;
    statX = 50.0f + (x - 270.0f);
    for (i = 0; i < 3; i++) {
        GXColor cols[3] = {{0xCB, 0x8C, 0xA2, 0xFE}, {0xCB, 0xBE, 0x89, 0xFE}, {0x94, 0xB9, 0xC7, 0xFE}};
        GXColor reds[3] = {{0xA7, 0x3C, 0x3C, 0xFF}, {0x37, 0x69, 0x1E, 0xFF}, {0x0F, 0x21, 0x7A, 0xFF}};
        const char* const N_stat_name_tbl[3] = {"\x82\x67\x82\x6F", "\x82\x65\x82\x6F", "\x82\x61\x82\x6F"};
        const char* ruby[3] = {"msg_menu_mario_ruby_hp", "msg_menu_mario_ruby_fp", "msg_menu_mario_ruby_bp"};

        nameW = FontGetMessageWidth(N_stat_name_tbl[i]);
        rubyW = 0.5f * FontGetMessageWidth(msgSearch(ruby[i]));
        winTexInit(*w->file->data);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        winTexSet(0xAF, (Vec){rowA, (cx = (y - 38.0f) - (f32)(i * 34)) - 4.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, cols[i]);
        winFontInit();
        winFontSet((Vec){statX - nameW / 2.0f, 12.0f + cx, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, N_stat_name_tbl[i]);
        winFontSet((Vec){statX - rubyW / 2.0f, 21.0f + cx, 0.0f}, (Vec){0.5f, 0.5f, 0.5f}, reds[i], msgSearch(ruby[i]));
    }

    winIconInit();
    col = 110.0f + (x - 270.0f);
    row0 = 4.0f + (y - 38.0f);
    winIconSet(0x19F, (Vec){col, row0, 0.0f}, (Vec){0.82f, 0.82f, 0.82f}, white);
    rowB = (y - 38.0f) - 34.0f;
    row1 = 4.0f + rowB;
    winIconSet(0x1A0, (Vec){col, row1, 0.0f}, (Vec){0.82f, 0.82f, 0.82f}, white);
    rowA = (y - 38.0f) - 68.0f;
    winIconSet(0x1A1, (Vec){col, 4.0f + rowA, 0.0f}, (Vec){0.82f, 0.82f, 0.82f}, white);
    winFontInit();
    col = 130.0f + (x - 270.0f);
    row2 = 4.0f + (12.0f + (y - 38.0f));
    winFontSetR((Vec){col, row2, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->currentHP));
    rowB = 4.0f + (12.0f + rowB);
    winFontSetR((Vec){col, rowB, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->currentFP));
    winFontSetR((Vec){col, 4.0f + (12.0f + rowA), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->maximumBP));
    winTexInit(*w->file->data);
    col = 190.0f + (x - 270.0f);
    winTexSet(0x10, (Vec){col, row0, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    winTexSet(0x10, (Vec){col, row1, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    winFontInit();
    col = 200.0f + (x - 270.0f);
    winFontSet((Vec){col, row2, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->maximumHP));
    winFontSet((Vec){col, rowB, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, "%s", winZenkakuStr(pouch->maximumFP));

    if (w->f198 > 0) {
        winKirinukiGX(w, 0, 10.0f + x, (20.0f + (130.0f + y)) - 20.0f, 260.0f, 80.0f);
        winIconInit();
        col = 10.0f + (40.0f + x);
        rowB = 106.0f + y;
        winIconSet(0x20F, (Vec){col, rowB, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white);
        cx = 70.0f + y;
        winIconSet(0x197, (Vec){col, cx, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white);
        winFontInit();
        winFontSet((Vec){10.0f + (70.0f + x), 10.0f + cx, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, msgSearch("msg_menu_mario_special"));
        winIconInit();
        cx = 10.0f + (80.0f + x);
        for (i = 0; i < w->f198; i++) {
            if (i < pouch->currentSP / 100) {
                winIconSet(0x1B7 + i, (Vec){cx + (f32)(i * 22), rowB, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white);
            } else {
                winIconSet(0x1BF, (Vec){cx + (f32)(i * 22), rowB, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white);
            }
        }
    }

    left = 10.0f + x;
    winKirinukiGX(w, 0, left, 10.0f + (20.0f + y), 260.0f, 150.0f);
    winIconInit();
    rowB = 10.0f + (20.0f + x);
    winIconSet(0x18C, (Vec){rowB, 10.0f + y, 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x18B, (Vec){rowB, 10.0f + (y - 28.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x18D, (Vec){rowB, 10.0f + (y - 56.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x102, (Vec){rowB, 10.0f + (y - 84.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winIconSet(0x1A2, (Vec){rowB, 10.0f + (y - 112.0f), 0.0f}, (Vec){0.62f, 0.62f, 0.62f}, white);
    winFontInit();
    col = 10.0f + (35.0f + x);
    rowA = 12.0f + y;
    row0 = 10.0f + rowA;
    winFontSet((Vec){col, row0, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_sp"));
    row1 = 10.0f + (rowA - 28.0f);
    winFontSet((Vec){col, row1, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_coin"));
    row2 = 10.0f + (rowA - 56.0f);
    winFontSet((Vec){col, row2, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_hoshi"));
    row3 = 10.0f + (rowA - 84.0f);
    winFontSet((Vec){col, row3, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_super_coin"));
    rowA = 10.0f + (rowA - 112.0f);
    winFontSet((Vec){col, rowA, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, msgSearch("msg_menu_mario_num_playtime"));
    numX = 2.0f + (8.0f + (205.0f + x));
    winFontSetR((Vec){numX, row0, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->mStarPoints));
    winFontSetR((Vec){numX, row1, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->coins));
    winFontSetR((Vec){numX, row2, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->mStarPieceCount));
    winFontSetR((Vec){numX, row3, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", winZenkakuStr(pouch->mShineSpriteCount));

    tsecs = gp->retraceLocalTime / OS_TIMER_CLOCK;
    if (tsecs > 359999) {
        hour = 99;
        min = 59;
    } else {
        secs = tsecs;
        hour = (u64)secs / 3600;
        min = (u64)secs % 3600 / 60;
    }
    winFontSetR((Vec){2.0f + (2.0f + ((8.0f + (172.0f + x)) - 16.0f)), rowA, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", unk_8016af5c(hour, 2));
    winFontSetR((Vec){numX, rowA, 0.0f}, (Vec){0.9f, 0.9f, 0.9f}, black, "%s", unk_8016af5c(min, 2));

    winTexInit(*w->file->data);
    cx = 10.0f + (190.0f + x);
    for (i = 0; i < 4; i++) {
        winTexSet(0x11, (Vec){cx, 10.0f + (y - (f32)(i * 28)), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    }
    rowB = 220.0f + x;
    winTexSet(0x12, (Vec){rowB, (10.0f + (2.0f + (y - 112.0f))) - 2.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);

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
        winFontSetEdge((Vec){rowB - 270.0f, 155.0f, 0.0f}, (Vec){0.8f, 0.8f, 0.8f}, white, "\x82\x72\x82\x6F");
        cx = 10.0f + (left - 270.0f);
        costX = (228.0f + x) - 270.0f;
        rowA = 4.0f + ((17.0f + rowB) - 270.0f);
        for (i = 0; i < w->f198; i++) {
            char sbuf[0x20];

            winFontSetLabel((Vec){cx, (f32)(130 - i * 26), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, superActionTable[i]->name);
            sprintf(sbuf, "%s", winZenkakuStr(superActionTable[i]->cost));
            winFontSet((Vec){costX - (f32)(FontGetMessageWidth(sbuf) / 2), (f32)(130 - i * 26), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, black, sbuf);
            winFontSet((Vec){rowA, (f32)(120 - i * 26), 0.0f}, (Vec){0.5f, 0.5f, 0.5f}, black, "\x82\x72\x82\x6F");
        }
    }
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: winMarioInit (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const char str_802F5650[] = "msg_menu_mario_lv\000\000";
__declspec(section ".rodata") const char str_802F5664[] = "msg_menu_mario_star_r\000\000";
__declspec(section ".rodata") const char str_802F567C[] = "msg_menu_mario_hp\000\000";
__declspec(section ".rodata") const char str_802F5690[] = "msg_menu_mario_fp\000\000";
__declspec(section ".rodata") const char str_802F56A4[] = "msg_menu_mario_bp\000\000";
__declspec(section ".rodata") const char str_802F56B8[] = "msg_slit\000\000\000";
__declspec(section ".rodata") const char str_802F56C4[] = "msg_plane\000\000";
__declspec(section ".rodata") const char str_802F56D0[] = "msg_ship\000\000\000";
__declspec(section ".rodata") const char str_802F56DC[] = "msg_roll\000\000\000";
__declspec(section ".rodata") const char str_802F56E8[] = "msg_menu_star_power";
__declspec(section ".rodata") const char str_802F56FC[] = "msg_menu_mario_waza";
__declspec(section ".rodata") const char str_802F5710[] = "msg_menu_mario_star_p\000\000";
__declspec(section ".rodata") const char str_802F5728[] = "msg_menu_mario_coin";
__declspec(section ".rodata") const char str_802F573C[] = "msg_menu_mario_kakera\000\000";
__declspec(section ".rodata") const char str_802F5754[] = "msg_menu_mario_scoin\000\000\000";
__declspec(section ".rodata") const char str_802F576C[] = "msg_menu_mario_time";
__declspec(section ".rodata") const char str_802F5780[] = "msg_hammer_1\000\000\000";
__declspec(section ".rodata") const char str_802F5790[] = "msg_hammer_2\000\000\000";
__declspec(section ".rodata") const char str_802F57A0[] = "msg_hammer_3\000\000\000";
__declspec(section ".rodata") const char str_802F57B0[] = "msg_boots_1";
__declspec(section ".rodata") const char str_802F57BC[] = "msg_boots_2";
__declspec(section ".rodata") const char str_802F57C8[] = "msg_boots_3";
extern const char str_8041D5A8[];
extern const char str_8041D5AC[];
extern const char str_8041D5B0[];
extern const char str_8041D5B4[];
extern const char str_8041D5B8[];
extern const char str_8041D5BC[];
extern const char str_8041D5C0[];
extern const char str_8041D5C4[];
extern const char str_8041D5C8[];
extern const char str_8041D5CC[];
__declspec(section ".rodata") const char* const jumptable_802F57D4[20] = { str_8041D5A8, str_8041D5AC, str_8041D5B0, str_8041D5B4, str_8041D5B8, str_8041D5BC, str_8041D5C0, str_8041D5C4, str_8041D5C8, str_8041D5CC, str_8041D5A8, str_8041D5AC, str_8041D5B0, str_8041D5B4, str_8041D5B8, str_8041D5BC, str_8041D5C0, str_8041D5C4, str_8041D5C8, str_8041D5CC };
__declspec(section ".rodata") const f32 vec3_802f5824[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5830[3] = { 0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f583c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5848[3] = { 0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f5854[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5860[3] = { 0.7f, 0.7f, 0.7f };
__declspec(section ".rodata") const f32 vec3_802f586c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5878[3] = { -0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f5884[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5890[3] = { -0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f589c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f58a8[3] = { 0.7f, 0.7f, 0.7f };
__declspec(section ".rodata") const f32 vec3_802f58b4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f58c0[3] = { 0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f58cc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f58d8[3] = { 0.6f, 0.6f, 0.6f };
__declspec(section ".rodata") const f32 vec3_802f58e4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f58f0[3] = { 0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f58fc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5908[3] = { 0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f5914[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5920[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f592c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5938[3] = { 0.7f, 0.7f, 0.7f };
__declspec(section ".rodata") const u32 dat_802f5944[3] = { 0xCB8CA2FE, 0xCBBE89FE, 0x94B9C7FE };
__declspec(section ".rodata") const u32 dat_802f5950[3] = { 0xA73C3CFF, 0x37691EFF, 0x0F217AFF };
extern const char str_8041D5F0[];
extern const char str_8041D5F8[];
extern const char str_8041D600[];
__declspec(section ".rodata") const char* const N_stat_name_tbl[3] = { str_8041D5F0, str_8041D5F8, str_8041D600 };
__declspec(section ".rodata") const char str_802F5968[] = "msg_menu_mario_ruby_hp\000";
__declspec(section ".rodata") const char str_802F5980[] = "msg_menu_mario_ruby_fp\000";
__declspec(section ".rodata") const char str_802F5998[] = "msg_menu_mario_ruby_bp\000";
__declspec(section ".rodata") const char* const jumptable_802F59B0[3] = { str_802F5968, str_802F5980, str_802F5998 };
__declspec(section ".rodata") const f32 vec3_802f59bc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f59c8[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f59d4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f59e0[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f59ec[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f59f8[3] = { 0.5f, 0.5f, 0.5f };
__declspec(section ".rodata") const f32 vec3_802f5a04[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5a10[3] = { 0.82f, 0.82f, 0.82f };
__declspec(section ".rodata") const f32 vec3_802f5a1c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5a28[3] = { 0.82f, 0.82f, 0.82f };
__declspec(section ".rodata") const f32 vec3_802f5a34[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5a40[3] = { 0.82f, 0.82f, 0.82f };
__declspec(section ".rodata") const f32 vec3_802f5a4c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5a58[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5a64[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5a70[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5a7c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5a88[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5a94[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5aa0[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5aac[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5ab8[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5ac4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5ad0[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5adc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5ae8[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5af4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5b00[3] = { 0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f5b0c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5b18[3] = { 0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f5b24[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5b30[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5b3c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5b48[3] = { 0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f5b54[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5b60[3] = { 0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f5b6c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5b78[3] = { 0.62f, 0.62f, 0.62f };
__declspec(section ".rodata") const f32 vec3_802f5b84[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5b90[3] = { 0.62f, 0.62f, 0.62f };
__declspec(section ".rodata") const f32 vec3_802f5b9c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5ba8[3] = { 0.62f, 0.62f, 0.62f };
__declspec(section ".rodata") const f32 vec3_802f5bb4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5bc0[3] = { 0.62f, 0.62f, 0.62f };
__declspec(section ".rodata") const f32 vec3_802f5bcc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5bd8[3] = { 0.62f, 0.62f, 0.62f };
__declspec(section ".rodata") const f32 vec3_802f5be4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5bf0[3] = { 0.9f, 0.9f, 0.9f };
__declspec(section ".rodata") const f32 vec3_802f5bfc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5c08[3] = { 0.9f, 0.9f, 0.9f };
__declspec(section ".rodata") const f32 vec3_802f5c14[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5c20[3] = { 0.9f, 0.9f, 0.9f };
__declspec(section ".rodata") const f32 vec3_802f5c2c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5c38[3] = { 0.9f, 0.9f, 0.9f };
__declspec(section ".rodata") const f32 vec3_802f5c44[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5c50[3] = { 0.9f, 0.9f, 0.9f };
__declspec(section ".rodata") const f32 vec3_802f5c5c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5c68[3] = { 0.9f, 0.9f, 0.9f };
__declspec(section ".rodata") const f32 vec3_802f5c74[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5c80[3] = { 0.9f, 0.9f, 0.9f };
__declspec(section ".rodata") const f32 vec3_802f5c8c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5c98[3] = { 0.9f, 0.9f, 0.9f };
__declspec(section ".rodata") const f32 vec3_802f5ca4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5cb0[3] = { 0.9f, 0.9f, 0.9f };
__declspec(section ".rodata") const f32 vec3_802f5cbc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5cc8[3] = { 0.9f, 0.9f, 0.9f };
__declspec(section ".rodata") const f32 vec3_802f5cd4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5ce0[3] = { 0.9f, 0.9f, 0.9f };
__declspec(section ".rodata") const f32 vec3_802f5cec[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5cf8[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5d04[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5d10[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5d1c[3] = { 0.0f, 155.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5d28[3] = { 0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f5d34[3] = { 0.0f, 155.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5d40[3] = { 0.8f, 0.8f, 0.8f };
__declspec(section ".rodata") const f32 vec3_802f5d4c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5d58[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5d64[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5d70[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802f5d7c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802f5d88[3] = { 0.5f, 0.5f, 0.5f };
__declspec(section ".rodata") const char str_802F5D94[] = "name_mario\000";
__declspec(section ".rodata") const char str_802F5DA0[] = "msg_menu_mario_level\000\000\000";
__declspec(section ".rodata") const char str_802F5DB8[] = "msg_menu_mario_special\000";
__declspec(section ".rodata") const char str_802F5DD0[] = "msg_menu_mario_num_sp\000\000";
__declspec(section ".rodata") const char str_802F5DE8[] = "msg_menu_mario_num_coin";
__declspec(section ".rodata") const char str_802F5E00[] = "msg_menu_mario_num_hoshi\000\000\000";
__declspec(section ".rodata") const char str_802F5E1C[] = "msg_menu_mario_num_super_coin\000\000";
__declspec(section ".rodata") const char str_802F5E3C[] = "msg_menu_mario_num_playtime";
__declspec(section ".rodata") const char str_802F5E58[] = "msg_menu_mario_sac_waza";
__declspec(section ".rodata") const f64 double_to_int_mask_802f5e70 = 4503599627370496;
__declspec(section ".rodata") const f64 double_to_int_802f5e78 = 4503601774854144;
__declspec(section ".rodata") const char str_802F5E80[] = "d_mario";
__declspec(section ".rodata") const char str_802F5E88[] = "a_mario";
__declspec(section ".rodata") const char str_802F5E90[] = "a_mario_l\000\000";
__declspec(section ".rodata") const char str_802F5E9C[] = "a_mario_w\000\000";
__declspec(section ".rodata") const char str_802F5EA8[] = "a_mario_wl\000";
__declspec(section ".rodata") const u32 gap_04_802F5EB4_rodata[1] = { 0x00000000 };
__declspec(section ".sdata2") const char str_8041D578[8] = "M_S_1\0\0";
__declspec(section ".sdata2") const char str_8041D580[4] = "S_1";
__declspec(section ".sdata2") const char str_8041D584[8] = "M_H_1\000\000";
__declspec(section ".sdata2") const char str_8041D58C[4] = "R_1";
__declspec(section ".sdata2") const char str_8041D590[8] = "M_R_1\000\000";
__declspec(section ".sdata2") const char str_8041D598[8] = "M_H_4\000\000";
__declspec(section ".sdata2") const char str_8041D5A0[8] = "M_H_7\000\000";
__declspec(section ".sdata2") const char str_8041D5A8[4] = "\x82O\0";
__declspec(section ".sdata2") const char str_8041D5AC[4] = "\202P\000";
__declspec(section ".sdata2") const char str_8041D5B0[4] = "\202Q\000";
__declspec(section ".sdata2") const char str_8041D5B4[4] = "\202R\000";
__declspec(section ".sdata2") const char str_8041D5B8[4] = "\202S\000";
__declspec(section ".sdata2") const char str_8041D5BC[4] = "\202T\000";
__declspec(section ".sdata2") const char str_8041D5C0[4] = "\202U\000";
__declspec(section ".sdata2") const char str_8041D5C4[4] = "\202V\000";
__declspec(section ".sdata2") const char str_8041D5C8[4] = "\202W\000";
__declspec(section ".sdata2") const char str_8041D5CC[4] = "\202X\000";
__declspec(section ".sdata2") const u32 dat_8041d5d0 = 0x00000080;
__declspec(section ".sdata2") const u32 dat_8041d5d4 = 0xE1E1E1FE;
__declspec(section ".sdata2") const u32 dat_8041d5d8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d5dc = 0x00000080;
__declspec(section ".sdata2") const u32 dat_8041d5e0 = 0xE1E1E1FE;
__declspec(section ".sdata2") const u32 dat_8041d5e4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d5e8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041d5ec = 0x000000FF;
__declspec(section ".sdata2") const char str_8041D5F0[8] = "\202g\202o\000\000\000";
__declspec(section ".sdata2") const char str_8041D5F8[8] = "\202e\202o\000\000\000";
__declspec(section ".sdata2") const char str_8041D600[8] = "\202a\202o\000\000\000";
__declspec(section ".sdata2") const u32 dat_8041d608 = 0x00000080;
__declspec(section ".sdata2") const f32 float_265_8041d60c = 265.0f;
__declspec(section ".sdata2") const f32 float_154_8041d610 = 154.0f;
__declspec(section ".sdata2") const f32 float_190_8041d614 = 190.0f;
__declspec(section ".sdata2") const f32 float_24_8041d618 = 24.0f;
__declspec(section ".sdata2") const f32 float_10_8041d61c = 10.0f;
__declspec(section ".sdata2") const f32 float_152_8041d620 = 152.0f;
__declspec(section ".sdata2") const f32 float_0p8_8041d624 = 0.8f;
__declspec(section ".sdata2") const f32 float_20_8041d628 = 20.0f;
__declspec(section ".sdata2") const f32 float_142_8041d62c = 142.0f;
__declspec(section ".sdata2") const char str_8041D630[4] = "\x81|\0";
__declspec(section ".sdata2") const f32 float_0_8041d634 = 0.0f;
__declspec(section ".sdata2") const char str_8041D638[4] = "%d\0";
__declspec(section ".sdata2") const char str_8041D63C[4] = "%s\0";
__declspec(section ".sdata2") const f32 float_255_8041d640 = 255.0f;
__declspec(section ".sdata2") const f32 float_112_8041d644 = 112.0f;
__declspec(section ".sdata2") const f32 float_240_8041d648 = 240.0f;
__declspec(section ".sdata2") const f32 float_124_8041d64c = 124.0f;
__declspec(section ".sdata2") const f32 float_270_8041d650 = 270.0f;
__declspec(section ".sdata2") const f32 float_264_8041d654 = 264.0f;
__declspec(section ".sdata2") const f32 float_110_8041d658 = 110.0f;
__declspec(section ".sdata2") const f32 float_50_8041d65c = 50.0f;
__declspec(section ".sdata2") const f32 float_2_8041d660 = 2.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041d664 = 0.5f;
__declspec(section ".sdata2") const f32 float_38_8041d668 = 38.0f;
__declspec(section ".sdata2") const f32 float_4_8041d66c = 4.0f;
__declspec(section ".sdata2") const f32 float_12_8041d670 = 12.0f;
__declspec(section ".sdata2") const f32 float_21_8041d674 = 21.0f;
__declspec(section ".sdata2") const f32 float_34_8041d678 = 34.0f;
__declspec(section ".sdata2") const f32 float_68_8041d67c = 68.0f;
__declspec(section ".sdata2") const f32 float_130_8041d680 = 130.0f;
__declspec(section ".sdata2") const f32 float_200_8041d684 = 200.0f;
__declspec(section ".sdata2") const f32 float_260_8041d688 = 260.0f;
__declspec(section ".sdata2") const f32 float_80_8041d68c = 80.0f;
__declspec(section ".sdata2") const f32 float_40_8041d690 = 40.0f;
__declspec(section ".sdata2") const f32 float_106_8041d694 = 106.0f;
__declspec(section ".sdata2") const f32 float_70_8041d698 = 70.0f;
__declspec(section ".sdata2") const f32 float_150_8041d69c = 150.0f;
__declspec(section ".sdata2") const f32 float_28_8041d6a0 = 28.0f;
__declspec(section ".sdata2") const f32 float_56_8041d6a4 = 56.0f;
__declspec(section ".sdata2") const f32 float_84_8041d6a8 = 84.0f;
__declspec(section ".sdata2") const f32 float_35_8041d6ac = 35.0f;
__declspec(section ".sdata2") const f32 float_8_8041d6b0 = 8.0f;
__declspec(section ".sdata2") const f32 float_205_8041d6b4 = 205.0f;
__declspec(section ".sdata2") const f32 float_172_8041d6b8 = 172.0f;
__declspec(section ".sdata2") const f32 float_16_8041d6bc = 16.0f;
__declspec(section ".sdata2") const f32 float_220_8041d6c0 = 220.0f;
__declspec(section ".sdata2") const f32 float_0_8041d6c4 = 0.0f;
__declspec(section ".sdata2") const f32 float_1_8041d6c8 = 1.0f;
__declspec(section ".sdata2") const f32 float_5_8041d6cc = 5.0f;
__declspec(section ".sdata2") const f32 float_160_8041d6d0 = 160.0f;
__declspec(section ".sdata2") const f32 float_254_8041d6d4 = 254.0f;
__declspec(section ".sdata2") const f32 float_90_8041d6d8 = 90.0f;
__declspec(section ".sdata2") const char str_8041D6DC[8] = "\x82r\x82o\0\0\0";
__declspec(section ".sdata2") const f32 float_228_8041d6e4 = 228.0f;
__declspec(section ".sdata2") const f32 float_17_8041d6e8 = 17.0f;
__declspec(section ".sdata2") const f32 float_230_8041d6ec = 230.0f;
__declspec(section ".sdata2") const f32 float_72_8041d6f0 = 72.0f;
__declspec(section ".sdata2") const f32 float_6_8041d6f4 = 6.0f;
__declspec(section ".sdata2") const f32 float_210_8041d6f8 = 210.0f;
__declspec(section ".sdata2") const f32 float_30_8041d6fc = 30.0f;
__declspec(section ".sdata2") const f32 float_60_8041d700 = 60.0f;
__declspec(section ".sdata2") const char str_8041D704[4] = "S_2";
__declspec(section ".sdata2") const char str_8041D708[4] = "S_3";
__declspec(section ".sdata2") const char str_8041D70C[4] = "S_4";
__declspec(section ".sdata2") const char str_8041D710[8] = "R_15\0\0\0";
__declspec(section ".sdata2") const char str_8041D718[8] = "R_17\0\0\0";
__declspec(section ".sdata2") const char str_8041D720[8] = "R_18\0\0\0";
__declspec(section ".sdata2") const f32 float_0p89_8041d728 = 0.89f;
__declspec(section ".sdata2") const f32 float_neg280_8041d72c = -280.0f;
__declspec(section ".sdata2") const f32 float_120_8041d730 = 120.0f;
__declspec(section ".sdata2") const f32 float_26_8041d734 = 26.0f;

void fukidashi(WinMarioWork* w, u32 idx, f32 x, f32 y);
__declspec(section ".data") static void* jumptable_80374F08[] = {
    (char*)fukidashi + 0xB44,
    (char*)fukidashi + 0xB44,
    (char*)fukidashi + 0x58,
    (char*)fukidashi + 0x230,
    (char*)fukidashi + 0xB44,
    (char*)fukidashi + 0xB44,
    (char*)fukidashi + 0xB44,
    (char*)fukidashi + 0x408,
    (char*)fukidashi + 0x5D8,
    (char*)fukidashi + 0x7A8,
    (char*)fukidashi + 0x978,
};
void __div2i();
void __div2u();
void __mod2u();
static s32 fs_pri[6] = {3, 2, 8, 10, 7, 9};
extern void strcat();
// FAKE: whole-unit asm stopgap (C under NONMATCHING); data in target order, force_active, gaps
asm void winMarioDisp(s32 camId, void* param, s32 idx) {
	nofralloc
	stwu r1, -0x1940(r1)
	mflr r0
	stw r0, 0x1944(r1)
	li r0, 0x1938
	stfd f31, 0x1930(r1)
	psq_stx f31, r1, r0, 0, 0
	li r0, 0x1928
	stfd f30, 0x1920(r1)
	psq_stx f30, r1, r0, 0, 0
	li r0, 0x1918
	stfd f29, 0x1910(r1)
	psq_stx f29, r1, r0, 0, 0
	li r0, 0x1908
	stfd f28, 0x1900(r1)
	psq_stx f28, r1, r0, 0, 0
	li r0, 0x18f8
	stfd f27, 0x18f0(r1)
	psq_stx f27, r1, r0, 0, 0
	li r0, 0x18e8
	stfd f26, 0x18e0(r1)
	psq_stx f26, r1, r0, 0, 0
	li r0, 0x18d8
	stfd f25, 0x18d0(r1)
	psq_stx f25, r1, r0, 0, 0
	li r0, 0x18c8
	stfd f24, 0x18c0(r1)
	psq_stx f24, r1, r0, 0, 0
	li r0, 0x18b8
	stfd f23, 0x18b0(r1)
	psq_stx f23, r1, r0, 0, 0
	li r0, 0x18a8
	stfd f22, 0x18a0(r1)
	psq_stx f22, r1, r0, 0, 0
	li r0, 0x1898
	stfd f21, 0x1890(r1)
	psq_stx f21, r1, r0, 0, 0
	li r0, 0x1888
	stfd f20, 0x1880(r1)
	psq_stx f20, r1, r0, 0, 0
	li r0, 0x1878
	stfd f19, 0x1870(r1)
	psq_stx f19, r1, r0, 0, 0
	li r0, 0x1868
	stfd f18, 0x1860(r1)
	psq_stx f18, r1, r0, 0, 0
	stmw r19, 0x182c(r1)
	lis r3, str_802F5650@ha
	mr r19, r5
	mr r30, r4
	addi r31, r3, str_802F5650@l
	bl pouchGetPtr
	mulli r4, r19, 0x14
	lwz r6, dat_8041d5e8(r0)
	lwz r0, dat_8041d5ec(r0)
	mr r29, r3
	stw r6, 0xc(r1)
	mr r3, r30
	add r5, r30, r4
	stw r6, 0xd4(r1)
	lfs f31, 0xc4(r5)
	li r4, 0x0
	lfs f30, 0xc8(r5)
	fmr f1, f31
	stw r6, 0xdc(r1)
	fmr f2, f30
	stw r0, 0x8(r1)
	stw r0, 0xd0(r1)
	stw r0, 0xd8(r1)
	bl winBgGX
	lfs f1, float_265_8041d60c(r0)
	mr r3, r30
	lfs f0, float_154_8041d610(r0)
	li r4, 0x2
	fsubs f1, f31, f1
	lfs f3, float_190_8041d614(r0)
	fadds f2, f0, f30
	lfs f4, float_24_8041d618(r0)
	bl winNameGX
	lfs f0, float_265_8041d60c(r0)
	lfs f1, float_10_8041d61c(r0)
	fsubs f0, f31, f0
	fadds f18, f1, f0
	bl winFontInit
	lfs f0, float_152_8041d620(r0)
	addi r3, r31, 0x744
	lwz r4, 0x264(r31)
	lwz r0, 0x268(r31)
	fadds f25, f0, f30
	stw r4, 0x764(r1)
	lwz r5, 0x26c(r31)
	stw r0, 0x768(r1)
	lwz r9, 0xd4(r1)
	stfs f18, 0x764(r1)
	lwz r8, 0x270(r31)
	stfs f25, 0x768(r1)
	lwz r7, 0x274(r31)
	lwz r6, 0x278(r31)
	lwz r4, 0x764(r1)
	lwz r0, 0x768(r1)
	stw r9, 0xcc(r1)
	stw r8, 0x758(r1)
	stw r7, 0x75c(r1)
	stw r6, 0x760(r1)
	stw r5, 0x76c(r1)
	stw r4, 0x770(r1)
	stw r0, 0x774(r1)
	stw r5, 0x778(r1)
	bl msgSearch
	mr r6, r3
	addi r3, r1, 0x770
	addi r4, r1, 0x758
	addi r5, r1, 0xcc
	crclr 6
	bl winFontSetEdge
	addi r3, r31, 0x744
	bl msgSearch
	bl FontGetMessageWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x180c(r1)
	lfd f3, 0x820(r31)
	stw r0, 0x1808(r1)
	lfs f1, float_0p8_8041d624(r0)
	lfd f2, 0x1808(r1)
	lfs f0, float_20_8041d628(r0)
	fsubs f2, f2, f3
	fmadds f18, f1, f2, f18
	fadds f18, f18, f0
	bl winIconInit
	lfs f0, float_142_8041d62c(r0)
	addi r4, r1, 0x74c
	lwz r3, 0x27c(r31)
	addi r5, r1, 0x734
	lwz r0, 0x280(r31)
	fadds f0, f0, f30
	stw r3, 0x740(r1)
	addi r6, r1, 0xc8
	lwz r8, 0x284(r31)
	li r3, 0x19e
	stw r0, 0x744(r1)
	lwz r12, 0xd4(r1)
	stfs f18, 0x740(r1)
	lwz r11, 0x288(r31)
	stfs f0, 0x744(r1)
	lwz r10, 0x28c(r31)
	lwz r9, 0x290(r31)
	lwz r7, 0x740(r1)
	lwz r0, 0x744(r1)
	stw r12, 0xc8(r1)
	stw r11, 0x734(r1)
	stw r10, 0x738(r1)
	stw r9, 0x73c(r1)
	stw r8, 0x748(r1)
	stw r7, 0x74c(r1)
	stw r0, 0x750(r1)
	stw r8, 0x754(r1)
	bl winIconSet
	lfs f0, float_20_8041d628(r0)
	fadds f18, f18, f0
	bl winFontInit
	lwz r4, 0x294(r31)
	addi r3, r31, 0x750
	lwz r0, 0x298(r31)
	stw r4, 0x71c(r1)
	lwz r5, 0x29c(r31)
	stw r0, 0x720(r1)
	lwz r9, 0xd4(r1)
	stfs f18, 0x71c(r1)
	lwz r8, 0x2a0(r31)
	stfs f25, 0x720(r1)
	lwz r7, 0x2a4(r31)
	lwz r6, 0x2a8(r31)
	lwz r4, 0x71c(r1)
	lwz r0, 0x720(r1)
	stw r9, 0xc4(r1)
	stw r8, 0x710(r1)
	stw r7, 0x714(r1)
	stw r6, 0x718(r1)
	stw r5, 0x724(r1)
	stw r4, 0x728(r1)
	stw r0, 0x72c(r1)
	stw r5, 0x730(r1)
	bl msgSearch
	mr r6, r3
	addi r3, r1, 0x728
	addi r4, r1, 0x710
	addi r5, r1, 0xc4
	crclr 6
	bl winFontSetEdge
	lha r26, 0x8a(r29)
	lwz r11, 0x184(r31)
	lwz r10, 0x188(r31)
	cmpwi r26, 0x0
	lwz r9, 0x18c(r31)
	lwz r8, 0x190(r31)
	lwz r7, 0x194(r31)
	lwz r6, 0x198(r31)
	lwz r5, 0x19c(r31)
	lwz r4, 0x1a0(r31)
	lwz r3, 0x1a4(r31)
	lwz r0, 0x1a8(r31)
	stw r11, 0x9ac(r1)
	stw r10, 0x9b0(r1)
	stw r9, 0x9b4(r1)
	stw r8, 0x9b8(r1)
	stw r7, 0x9bc(r1)
	stw r6, 0x9c0(r1)
	stw r5, 0x9c4(r1)
	stw r4, 0x9c8(r1)
	stw r3, 0x9cc(r1)
	stw r0, 0x9d0(r1)
	bge L_at1
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r26, r26
	b L_at2
	L_at1:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at2:
	mr r5, r26
	addi r3, r1, 0x1604
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r22, r1, 0x1604
	addi r20, r3, (unk_803dfbf8+0x100)@l
	addi r19, r1, 0x9ac
	li r21, 0x0
	b L_at3
	L_at4:
	lbz r0, 0x0(r22)
	mr r3, r20
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r19, r0
	bl strcat
	addi r22, r22, 0x1
	addi r21, r21, 0x1
	L_at3:
	addi r3, r1, 0x1604
	bl strlen
	cmplw r21, r3
	blt L_at4
	lis r4, (unk_803dfbf8+0x100)@ha
	addi r3, r1, 0x1704
	addi r5, r4, (unk_803dfbf8+0x100)@l
	la r4, str_8041D63C(r0)
	crclr 6
	bl sprintf
	bl winFontInit
	lwz r9, 0xd4(r1)
	addi r3, r1, 0x1704
	lwz r8, 0x2b8(r31)
	lwz r7, 0x2bc(r31)
	lwz r6, 0x2c0(r31)
	lwz r5, 0x2ac(r31)
	lwz r4, 0x2b0(r31)
	lwz r0, 0x2b4(r31)
	stw r9, 0xc0(r1)
	stw r8, 0x6ec(r1)
	stw r7, 0x6f0(r1)
	stw r6, 0x6f4(r1)
	stw r5, 0x6f8(r1)
	stw r4, 0x6fc(r1)
	stw r0, 0x700(r1)
	bl FontGetMessageWidth
	clrlwi r3, r3, 16
	lfs f0, float_265_8041d60c(r0)
	lis r0, 0x4330
	stw r3, 0x180c(r1)
	fsubs f0, f31, f0
	lfs f1, float_190_8041d614(r0)
	stw r0, 0x1808(r1)
	addi r3, r1, 0x704
	lfd f4, 0x820(r31)
	addi r4, r1, 0x6ec
	lfd f3, 0x1808(r1)
	fadds f1, f1, f0
	lfs f2, float_0p8_8041d624(r0)
	addi r5, r1, 0xc0
	fsubs f3, f3, f4
	stfs f25, 0x6fc(r1)
	lfs f0, float_10_8041d61c(r0)
	lwz r7, 0x6fc(r1)
	addi r6, r1, 0x1704
	fnmsubs f1, f2, f3, f1
	lwz r0, 0x700(r1)
	stw r7, 0x708(r1)
	fsubs f0, f1, f0
	stw r0, 0x70c(r1)
	stfs f0, 0x6f8(r1)
	lwz r0, 0x6f8(r1)
	stw r0, 0x704(r1)
	crclr 6
	bl winFontSetEdge
	lwz r3, 0x28(r30)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lfs f1, float_255_8041d640(r0)
	addi r4, r1, 0x6e0
	lfs f0, float_112_8041d644(r0)
	addi r5, r1, 0x6c8
	lwz r3, 0x2c4(r31)
	fsubs f1, f31, f1
	lwz r0, 0x2c8(r31)
	fadds f0, f0, f30
	stw r3, 0x6d4(r1)
	addi r6, r1, 0xbc
	lwz r8, 0x2cc(r31)
	stw r0, 0x6d8(r1)
	li r3, 0xb0
	lwz r12, 0xd4(r1)
	stfs f1, 0x6d4(r1)
	lwz r11, 0x2d0(r31)
	stfs f0, 0x6d8(r1)
	lwz r10, 0x2d4(r31)
	lwz r9, 0x2d8(r31)
	lwz r7, 0x6d4(r1)
	lwz r0, 0x6d8(r1)
	stw r12, 0xbc(r1)
	stw r11, 0x6c8(r1)
	stw r10, 0x6cc(r1)
	stw r9, 0x6d0(r1)
	stw r8, 0x6dc(r1)
	stw r7, 0x6e0(r1)
	stw r0, 0x6e4(r1)
	stw r8, 0x6e8(r1)
	bl winTexSet
	bl winFontInit
	lfs f1, float_240_8041d648(r0)
	lfs f0, float_124_8041d64c(r0)
	lwz r3, 0x2dc(r31)
	fsubs f1, f31, f1
	lwz r0, 0x2e0(r31)
	fadds f0, f0, f30
	stw r3, 0x6b0(r1)
	lwz r4, 0x2e4(r31)
	stw r0, 0x6b4(r1)
	lwz r8, 0xd0(r1)
	stfs f1, 0x6b0(r1)
	lwz r7, 0x2e8(r31)
	stfs f0, 0x6b4(r1)
	lwz r6, 0x2ec(r31)
	lwz r5, 0x2f0(r31)
	lwz r3, 0x6b0(r1)
	lwz r0, 0x6b4(r1)
	stw r8, 0xb8(r1)
	stw r7, 0x6a4(r1)
	stw r6, 0x6a8(r1)
	stw r5, 0x6ac(r1)
	stw r3, 0x6bc(r1)
	stw r0, 0x6c0(r1)
	stw r4, 0x6c4(r1)
	stw r4, 0x6b8(r1)
	lha r3, 0x8a(r29)
	bl BattleGetRankNameLabel
	bl msgSearch
	mr r6, r3
	addi r3, r1, 0x6bc
	addi r4, r1, 0x6a4
	addi r5, r1, 0xb8
	crclr 6
	bl winFontSet
	li r20, 0x0
	la r19, fs_pri(r0)
	L_at5:
	lwz r0, 0x160(r30)
	lwz r4, 0x0(r19)
	cmpw r0, r4
	beq L_at6
	fmr f1, f31
	mr r3, r30
	fmr f2, f30
	bl fukidashi
	L_at6:
	addi r20, r20, 0x1
	addi r19, r19, 0x4
	cmpwi r20, 0x6
	blt L_at5
	fmr f1, f31
	lwz r4, 0x160(r30)
	fmr f2, f30
	mr r3, r30
	bl fukidashi
	lfs f1, float_270_8041d650(r0)
	mr r3, r30
	lfs f0, float_10_8041d61c(r0)
	li r4, 0x0
	fsubs f1, f31, f1
	lfs f3, float_264_8041d654(r0)
	fsubs f2, f30, f0
	lfs f4, float_110_8041d658(r0)
	bl winKirinukiGX
	lfs f1, float_270_8041d650(r0)
	li r20, 0x0
	lfs f0, float_38_8041d668(r0)
	mr r22, r20
	fsubs f2, f31, f1
	lfs f3, float_50_8041d65c(r0)
	lfs f1, float_2_8041d660(r0)
	fsubs f28, f30, f0
	lfd f26, 0x820(r31)
	addi r25, r1, 0x788
	fadds f24, f3, f2
	lfs f27, float_0p5_8041d664(r0)
	lfd f29, 0x828(r31)
	addi r24, r1, 0x77c
	lfs f19, float_4_8041d66c(r0)
	addi r23, r1, 0x7a0
	fsubs f25, f24, f1
	lwz r26, 0xd8(r1)
	lfs f20, float_12_8041d670(r0)
	addi r21, r1, 0x794
	lfs f21, float_21_8041d674(r0)
	lis r27, 0x4330
	L_at7:
	lwz r7, 0x30c(r31)
	lwz r6, 0x310(r31)
	lwz r3, 0x314(r31)
	lwz r19, 0x2f4(r31)
	lwz r12, 0x2f8(r31)
	lwz r11, 0x2fc(r31)
	lwz r10, 0x300(r31)
	lwz r9, 0x304(r31)
	lwz r8, 0x308(r31)
	lwz r5, 0x360(r31)
	lwz r4, 0x364(r31)
	lwz r0, 0x368(r31)
	stw r7, 0x788(r1)
	stw r6, 0x78c(r1)
	stw r3, 0x790(r1)
	stw r19, 0x7a0(r1)
	lwz r3, 0x0(r25)
	stw r12, 0x7a4(r1)
	stw r11, 0x7a8(r1)
	stw r10, 0x794(r1)
	stw r9, 0x798(r1)
	stw r8, 0x79c(r1)
	stw r5, 0x77c(r1)
	stw r4, 0x780(r1)
	stw r0, 0x784(r1)
	bl FontGetMessageWidth
	clrlwi r0, r3, 16
	stw r27, 0x1808(r1)
	lwz r3, 0x0(r24)
	stw r0, 0x180c(r1)
	lfd f0, 0x1808(r1)
	fsubs f23, f0, f26
	bl msgSearch
	bl FontGetMessageWidth
	clrlwi r0, r3, 16
	lwz r3, 0x28(r30)
	stw r0, 0x1814(r1)
	lwz r3, 0xa0(r3)
	stw r27, 0x1810(r1)
	lwz r3, 0x0(r3)
	lfd f0, 0x1810(r1)
	fsubs f0, f0, f26
	fmuls f22, f27, f0
	bl winTexInit
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x2
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x1
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	xoris r0, r22, 0x8000
	lwz r8, 0x374(r31)
	stw r0, 0x181c(r1)
	addi r4, r1, 0x698
	lwz r7, 0x36c(r31)
	addi r5, r1, 0x680
	stw r27, 0x1818(r1)
	addi r6, r1, 0xb4
	lwz r0, 0x370(r31)
	li r3, 0xaf
	lfd f0, 0x1818(r1)
	stw r7, 0x68c(r1)
	fsubs f0, f0, f29
	lwz r12, 0x0(r23)
	stfs f25, 0x68c(r1)
	lwz r11, 0x378(r31)
	fsubs f18, f28, f0
	lwz r10, 0x37c(r31)
	lwz r9, 0x380(r31)
	stw r0, 0x690(r1)
	fsubs f0, f18, f19
	lwz r7, 0x68c(r1)
	stw r12, 0xb4(r1)
	stfs f0, 0x690(r1)
	lwz r0, 0x690(r1)
	stw r11, 0x680(r1)
	stw r10, 0x684(r1)
	stw r9, 0x688(r1)
	stw r8, 0x694(r1)
	stw r7, 0x698(r1)
	stw r0, 0x69c(r1)
	stw r8, 0x6a0(r1)
	bl winTexSet
	bl winFontInit
	lwz r3, 0x384(r31)
	fnmsubs f1, f23, f27, f24
	lwz r0, 0x388(r31)
	fadds f0, f20, f18
	stw r3, 0x668(r1)
	addi r3, r1, 0x674
	lwz r8, 0x38c(r31)
	stw r0, 0x66c(r1)
	addi r4, r1, 0x65c
	lwz r11, 0x390(r31)
	addi r5, r1, 0xb0
	stfs f1, 0x668(r1)
	lwz r10, 0x394(r31)
	stfs f0, 0x66c(r1)
	lwz r9, 0x398(r31)
	lwz r7, 0x668(r1)
	lwz r0, 0x66c(r1)
	stw r26, 0xb0(r1)
	lwz r6, 0x0(r25)
	stw r11, 0x65c(r1)
	stw r10, 0x660(r1)
	stw r9, 0x664(r1)
	stw r8, 0x670(r1)
	stw r7, 0x674(r1)
	stw r0, 0x678(r1)
	stw r8, 0x67c(r1)
	crclr 6
	bl winFontSet
	lwz r3, 0x39c(r31)
	fnmsubs f1, f22, f27, f24
	lwz r0, 0x3a0(r31)
	fadds f0, f21, f18
	stw r3, 0x644(r1)
	lwz r5, 0x3a4(r31)
	stw r0, 0x648(r1)
	lwz r3, 0x0(r21)
	stfs f1, 0x644(r1)
	lwz r8, 0x3a8(r31)
	stfs f0, 0x648(r1)
	lwz r7, 0x3ac(r31)
	lwz r6, 0x3b0(r31)
	lwz r4, 0x644(r1)
	lwz r0, 0x648(r1)
	stw r3, 0xac(r1)
	lwz r3, 0x0(r24)
	stw r8, 0x638(r1)
	stw r7, 0x63c(r1)
	stw r6, 0x640(r1)
	stw r5, 0x64c(r1)
	stw r4, 0x650(r1)
	stw r0, 0x654(r1)
	stw r5, 0x658(r1)
	bl msgSearch
	mr r6, r3
	addi r3, r1, 0x650
	addi r4, r1, 0x638
	addi r5, r1, 0xac
	crclr 6
	bl winFontSet
	addi r20, r20, 0x1
	addi r24, r24, 0x4
	cmpwi r20, 0x3
	addi r23, r23, 0x4
	addi r22, r22, 0x22
	addi r21, r21, 0x4
	addi r25, r25, 0x4
	blt L_at7
	bl winIconInit
	lfs f1, float_270_8041d650(r0)
	addi r4, r1, 0x62c
	lfs f0, float_38_8041d668(r0)
	addi r5, r1, 0x614
	fsubs f2, f31, f1
	lwz r8, 0x3bc(r31)
	lfs f3, float_110_8041d658(r0)
	fsubs f0, f30, f0
	lfs f1, float_4_8041d66c(r0)
	addi r6, r1, 0xa8
	lwz r3, 0x3b4(r31)
	fadds f18, f3, f2
	lwz r0, 0x3b8(r31)
	fadds f26, f1, f0
	stw r3, 0x620(r1)
	li r3, 0x19f
	lwz r12, 0xd4(r1)
	stw r0, 0x624(r1)
	lwz r11, 0x3c0(r31)
	stfs f18, 0x620(r1)
	lwz r10, 0x3c4(r31)
	stfs f26, 0x624(r1)
	lwz r9, 0x3c8(r31)
	lwz r7, 0x620(r1)
	lwz r0, 0x624(r1)
	stw r12, 0xa8(r1)
	stw r11, 0x614(r1)
	stw r10, 0x618(r1)
	stw r9, 0x61c(r1)
	stw r8, 0x628(r1)
	stw r7, 0x62c(r1)
	stw r0, 0x630(r1)
	stw r8, 0x634(r1)
	bl winIconSet
	lfs f0, float_38_8041d668(r0)
	addi r4, r1, 0x608
	lwz r8, 0x3d4(r31)
	addi r5, r1, 0x5f0
	fsubs f1, f30, f0
	lfs f0, float_34_8041d678(r0)
	lwz r7, 0x3cc(r31)
	addi r6, r1, 0xa4
	lwz r0, 0x3d0(r31)
	li r3, 0x1a0
	fsubs f24, f1, f0
	lfs f0, float_4_8041d66c(r0)
	stw r7, 0x5fc(r1)
	lwz r12, 0xd4(r1)
	fadds f27, f0, f24
	stw r0, 0x600(r1)
	lwz r11, 0x3d8(r31)
	stfs f18, 0x5fc(r1)
	lwz r10, 0x3dc(r31)
	stfs f27, 0x600(r1)
	lwz r9, 0x3e0(r31)
	lwz r7, 0x5fc(r1)
	lwz r0, 0x600(r1)
	stw r12, 0xa4(r1)
	stw r11, 0x5f0(r1)
	stw r10, 0x5f4(r1)
	stw r9, 0x5f8(r1)
	stw r8, 0x604(r1)
	stw r7, 0x608(r1)
	stw r0, 0x60c(r1)
	stw r8, 0x610(r1)
	bl winIconSet
	lfs f0, float_38_8041d668(r0)
	addi r4, r1, 0x5e4
	lwz r8, 0x3ec(r31)
	addi r5, r1, 0x5cc
	fsubs f1, f30, f0
	lfs f0, float_68_8041d67c(r0)
	lwz r7, 0x3e4(r31)
	addi r6, r1, 0xa0
	lwz r0, 0x3e8(r31)
	li r3, 0x1a1
	fsubs f25, f1, f0
	lfs f0, float_4_8041d66c(r0)
	stw r7, 0x5d8(r1)
	lwz r12, 0xd4(r1)
	fadds f0, f0, f25
	stw r0, 0x5dc(r1)
	lwz r11, 0x3f0(r31)
	stfs f18, 0x5d8(r1)
	lwz r10, 0x3f4(r31)
	stfs f0, 0x5dc(r1)
	lwz r9, 0x3f8(r31)
	lwz r7, 0x5d8(r1)
	lwz r0, 0x5dc(r1)
	stw r12, 0xa0(r1)
	stw r11, 0x5cc(r1)
	stw r10, 0x5d0(r1)
	stw r9, 0x5d4(r1)
	stw r8, 0x5e0(r1)
	stw r7, 0x5e4(r1)
	stw r0, 0x5e8(r1)
	stw r8, 0x5ec(r1)
	bl winIconSet
	bl winFontInit
	lfs f0, float_38_8041d668(r0)
	lwz r25, 0x404(r31)
	fsubs f0, f30, f0
	lfs f2, float_270_8041d650(r0)
	lfs f1, float_12_8041d670(r0)
	lwz r3, 0x3fc(r31)
	fsubs f2, f31, f2
	fadds f0, f1, f0
	lfs f3, float_130_8041d680(r0)
	lfs f1, float_4_8041d66c(r0)
	lwz r0, 0x400(r31)
	fadds f18, f3, f2
	stw r3, 0x5b4(r1)
	fadds f28, f1, f0
	lwz r22, 0x408(r31)
	stw r0, 0x5b8(r1)
	lwz r21, 0x40c(r31)
	stfs f18, 0x5b4(r1)
	lwz r20, 0x410(r31)
	stfs f28, 0x5b8(r1)
	lwz r24, 0x5b4(r1)
	lwz r23, 0x5b8(r1)
	lwz r12, 0xd0(r1)
	lwz r11, 0x184(r31)
	lwz r10, 0x188(r31)
	lwz r9, 0x18c(r31)
	lwz r8, 0x190(r31)
	lwz r7, 0x194(r31)
	lwz r6, 0x198(r31)
	lwz r5, 0x19c(r31)
	lwz r4, 0x1a0(r31)
	lwz r3, 0x1a4(r31)
	lwz r0, 0x1a8(r31)
	stw r24, 0x5c0(r1)
	stw r23, 0x5c4(r1)
	stw r25, 0x5c8(r1)
	stw r22, 0x5a8(r1)
	stw r21, 0x5ac(r1)
	stw r20, 0x5b0(r1)
	stw r12, 0x9c(r1)
	lha r26, 0x70(r29)
	stw r25, 0x5bc(r1)
	cmpwi r26, 0x0
	stw r11, 0x984(r1)
	stw r10, 0x988(r1)
	stw r9, 0x98c(r1)
	stw r8, 0x990(r1)
	stw r7, 0x994(r1)
	stw r6, 0x998(r1)
	stw r5, 0x99c(r1)
	stw r4, 0x9a0(r1)
	stw r3, 0x9a4(r1)
	stw r0, 0x9a8(r1)
	bge L_at8
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r26, r26
	b L_at9
	L_at8:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at9:
	mr r5, r26
	addi r3, r1, 0x1504
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r22, r1, 0x1504
	addi r21, r3, (unk_803dfbf8+0x100)@l
	addi r20, r1, 0x984
	li r19, 0x0
	b L_at10
	L_at11:
	lbz r0, 0x0(r22)
	mr r3, r21
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r20, r0
	bl strcat
	addi r22, r22, 0x1
	addi r19, r19, 0x1
	L_at10:
	addi r3, r1, 0x1504
	bl strlen
	cmplw r19, r3
	blt L_at11
	lis r4, (unk_803dfbf8+0x100)@ha
	addi r3, r1, 0x5c0
	addi r7, r4, (unk_803dfbf8+0x100)@l
	addi r5, r1, 0x9c
	addi r4, r1, 0x5a8
	la r6, str_8041D63C(r0)
	crclr 6
	bl winFontSetR
	lfs f0, float_12_8041d670(r0)
	lwz r25, 0x41c(r31)
	fadds f0, f0, f24
	lfs f1, float_4_8041d66c(r0)
	lwz r3, 0x414(r31)
	lwz r0, 0x418(r31)
	fadds f24, f1, f0
	stw r3, 0x590(r1)
	lwz r22, 0x420(r31)
	stw r0, 0x594(r1)
	lwz r21, 0x424(r31)
	stfs f18, 0x590(r1)
	lwz r20, 0x428(r31)
	stfs f24, 0x594(r1)
	lwz r24, 0x590(r1)
	lwz r23, 0x594(r1)
	lwz r12, 0xd0(r1)
	lwz r11, 0x184(r31)
	lwz r10, 0x188(r31)
	lwz r9, 0x18c(r31)
	lwz r8, 0x190(r31)
	lwz r7, 0x194(r31)
	lwz r6, 0x198(r31)
	lwz r5, 0x19c(r31)
	lwz r4, 0x1a0(r31)
	lwz r3, 0x1a4(r31)
	lwz r0, 0x1a8(r31)
	stw r24, 0x59c(r1)
	stw r23, 0x5a0(r1)
	stw r25, 0x5a4(r1)
	stw r22, 0x584(r1)
	stw r21, 0x588(r1)
	stw r20, 0x58c(r1)
	stw r12, 0x98(r1)
	lha r26, 0x74(r29)
	stw r25, 0x598(r1)
	cmpwi r26, 0x0
	stw r11, 0x95c(r1)
	stw r10, 0x960(r1)
	stw r9, 0x964(r1)
	stw r8, 0x968(r1)
	stw r7, 0x96c(r1)
	stw r6, 0x970(r1)
	stw r5, 0x974(r1)
	stw r4, 0x978(r1)
	stw r3, 0x97c(r1)
	stw r0, 0x980(r1)
	bge L_at12
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r26, r26
	b L_at13
	L_at12:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at13:
	mr r5, r26
	addi r3, r1, 0x1404
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r22, r1, 0x1404
	addi r21, r3, (unk_803dfbf8+0x100)@l
	addi r20, r1, 0x95c
	li r19, 0x0
	b L_at14
	L_at15:
	lbz r0, 0x0(r22)
	mr r3, r21
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r20, r0
	bl strcat
	addi r22, r22, 0x1
	addi r19, r19, 0x1
	L_at14:
	addi r3, r1, 0x1404
	bl strlen
	cmplw r19, r3
	blt L_at15
	lis r4, (unk_803dfbf8+0x100)@ha
	addi r3, r1, 0x59c
	addi r7, r4, (unk_803dfbf8+0x100)@l
	addi r5, r1, 0x98
	addi r4, r1, 0x584
	la r6, str_8041D63C(r0)
	crclr 6
	bl winFontSetR
	lfs f0, float_12_8041d670(r0)
	lwz r25, 0x434(r31)
	fadds f0, f0, f25
	lfs f1, float_4_8041d66c(r0)
	lwz r3, 0x42c(r31)
	lwz r0, 0x430(r31)
	fadds f0, f1, f0
	stw r3, 0x56c(r1)
	lwz r22, 0x438(r31)
	stw r0, 0x570(r1)
	lwz r21, 0x43c(r31)
	stfs f18, 0x56c(r1)
	lwz r20, 0x440(r31)
	stfs f0, 0x570(r1)
	lwz r24, 0x56c(r1)
	lwz r23, 0x570(r1)
	lwz r12, 0xd0(r1)
	lwz r11, 0x184(r31)
	lwz r10, 0x188(r31)
	lwz r9, 0x18c(r31)
	lwz r8, 0x190(r31)
	lwz r7, 0x194(r31)
	lwz r6, 0x198(r31)
	lwz r5, 0x19c(r31)
	lwz r4, 0x1a0(r31)
	lwz r3, 0x1a4(r31)
	lwz r0, 0x1a8(r31)
	stw r24, 0x578(r1)
	stw r23, 0x57c(r1)
	stw r25, 0x580(r1)
	stw r22, 0x560(r1)
	stw r21, 0x564(r1)
	stw r20, 0x568(r1)
	stw r12, 0x94(r1)
	lha r26, 0x94(r29)
	stw r25, 0x574(r1)
	cmpwi r26, 0x0
	stw r11, 0x934(r1)
	stw r10, 0x938(r1)
	stw r9, 0x93c(r1)
	stw r8, 0x940(r1)
	stw r7, 0x944(r1)
	stw r6, 0x948(r1)
	stw r5, 0x94c(r1)
	stw r4, 0x950(r1)
	stw r3, 0x954(r1)
	stw r0, 0x958(r1)
	bge L_at16
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r26, r26
	b L_at17
	L_at16:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at17:
	mr r5, r26
	addi r3, r1, 0x1304
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r22, r1, 0x1304
	addi r21, r3, (unk_803dfbf8+0x100)@l
	addi r20, r1, 0x934
	li r19, 0x0
	b L_at18
	L_at19:
	lbz r0, 0x0(r22)
	mr r3, r21
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r20, r0
	bl strcat
	addi r22, r22, 0x1
	addi r19, r19, 0x1
	L_at18:
	addi r3, r1, 0x1304
	bl strlen
	cmplw r19, r3
	blt L_at19
	lis r4, (unk_803dfbf8+0x100)@ha
	addi r3, r1, 0x578
	addi r7, r4, (unk_803dfbf8+0x100)@l
	addi r5, r1, 0x94
	addi r4, r1, 0x560
	la r6, str_8041D63C(r0)
	crclr 6
	bl winFontSetR
	lwz r3, 0x28(r30)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lfs f0, float_270_8041d650(r0)
	addi r4, r1, 0x554
	lwz r8, 0x44c(r31)
	addi r5, r1, 0x53c
	fsubs f0, f31, f0
	lfs f1, float_190_8041d614(r0)
	lwz r7, 0x444(r31)
	addi r6, r1, 0x90
	lwz r0, 0x448(r31)
	li r3, 0x10
	stw r0, 0x54c(r1)
	fadds f18, f1, f0
	lwz r12, 0xd4(r1)
	stw r7, 0x548(r1)
	lwz r11, 0x450(r31)
	stfs f18, 0x548(r1)
	lwz r10, 0x454(r31)
	stfs f26, 0x54c(r1)
	lwz r9, 0x458(r31)
	lwz r7, 0x548(r1)
	lwz r0, 0x54c(r1)
	stw r12, 0x90(r1)
	stw r11, 0x53c(r1)
	stw r10, 0x540(r1)
	stw r9, 0x544(r1)
	stw r8, 0x550(r1)
	stw r7, 0x554(r1)
	stw r0, 0x558(r1)
	stw r8, 0x55c(r1)
	bl winTexSet
	lwz r3, 0x45c(r31)
	addi r4, r1, 0x530
	lwz r0, 0x460(r31)
	addi r5, r1, 0x518
	stw r3, 0x524(r1)
	addi r6, r1, 0x8c
	lwz r8, 0x464(r31)
	li r3, 0x10
	stw r0, 0x528(r1)
	lwz r12, 0xd4(r1)
	stfs f18, 0x524(r1)
	lwz r11, 0x468(r31)
	stfs f27, 0x528(r1)
	lwz r10, 0x46c(r31)
	lwz r9, 0x470(r31)
	lwz r7, 0x524(r1)
	lwz r0, 0x528(r1)
	stw r12, 0x8c(r1)
	stw r11, 0x518(r1)
	stw r10, 0x51c(r1)
	stw r9, 0x520(r1)
	stw r8, 0x52c(r1)
	stw r7, 0x530(r1)
	stw r0, 0x534(r1)
	stw r8, 0x538(r1)
	bl winTexSet
	bl winFontInit
	lfs f0, float_270_8041d650(r0)
	lwz r25, 0x47c(r31)
	fsubs f0, f31, f0
	lfs f1, float_200_8041d684(r0)
	lwz r3, 0x474(r31)
	lwz r0, 0x478(r31)
	fadds f18, f1, f0
	stw r3, 0x500(r1)
	lwz r22, 0x480(r31)
	stw r0, 0x504(r1)
	lwz r21, 0x484(r31)
	stfs f18, 0x500(r1)
	lwz r20, 0x488(r31)
	stfs f28, 0x504(r1)
	lwz r24, 0x500(r1)
	lwz r23, 0x504(r1)
	lwz r12, 0xd0(r1)
	lwz r11, 0x184(r31)
	lwz r10, 0x188(r31)
	lwz r9, 0x18c(r31)
	lwz r8, 0x190(r31)
	lwz r7, 0x194(r31)
	lwz r6, 0x198(r31)
	lwz r5, 0x19c(r31)
	lwz r4, 0x1a0(r31)
	lwz r3, 0x1a4(r31)
	lwz r0, 0x1a8(r31)
	stw r24, 0x50c(r1)
	stw r23, 0x510(r1)
	stw r25, 0x514(r1)
	stw r22, 0x4f4(r1)
	stw r21, 0x4f8(r1)
	stw r20, 0x4fc(r1)
	stw r12, 0x88(r1)
	lha r26, 0x72(r29)
	stw r25, 0x508(r1)
	cmpwi r26, 0x0
	stw r11, 0x90c(r1)
	stw r10, 0x910(r1)
	stw r9, 0x914(r1)
	stw r8, 0x918(r1)
	stw r7, 0x91c(r1)
	stw r6, 0x920(r1)
	stw r5, 0x924(r1)
	stw r4, 0x928(r1)
	stw r3, 0x92c(r1)
	stw r0, 0x930(r1)
	bge L_at20
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r26, r26
	b L_at21
	L_at20:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at21:
	mr r5, r26
	addi r3, r1, 0x1204
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r22, r1, 0x1204
	addi r21, r3, (unk_803dfbf8+0x100)@l
	addi r20, r1, 0x90c
	li r19, 0x0
	b L_at22
	L_at23:
	lbz r0, 0x0(r22)
	mr r3, r21
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r20, r0
	bl strcat
	addi r22, r22, 0x1
	addi r19, r19, 0x1
	L_at22:
	addi r3, r1, 0x1204
	bl strlen
	cmplw r19, r3
	blt L_at23
	lis r4, (unk_803dfbf8+0x100)@ha
	addi r3, r1, 0x50c
	addi r7, r4, (unk_803dfbf8+0x100)@l
	addi r5, r1, 0x88
	addi r4, r1, 0x4f4
	la r6, str_8041D63C(r0)
	crclr 6
	bl winFontSet
	lwz r3, 0x48c(r31)
	lwz r0, 0x490(r31)
	stw r3, 0x4dc(r1)
	lwz r25, 0x494(r31)
	stw r0, 0x4e0(r1)
	lwz r22, 0x498(r31)
	stfs f18, 0x4dc(r1)
	lwz r21, 0x49c(r31)
	stfs f24, 0x4e0(r1)
	lwz r24, 0x4dc(r1)
	lwz r23, 0x4e0(r1)
	lwz r20, 0x4a0(r31)
	lwz r12, 0xd0(r1)
	lwz r11, 0x184(r31)
	lwz r10, 0x188(r31)
	lwz r9, 0x18c(r31)
	lwz r8, 0x190(r31)
	lwz r7, 0x194(r31)
	lwz r6, 0x198(r31)
	lwz r5, 0x19c(r31)
	lwz r4, 0x1a0(r31)
	lwz r3, 0x1a4(r31)
	lwz r0, 0x1a8(r31)
	stw r24, 0x4e8(r1)
	stw r23, 0x4ec(r1)
	stw r25, 0x4f0(r1)
	stw r22, 0x4d0(r1)
	stw r21, 0x4d4(r1)
	stw r20, 0x4d8(r1)
	stw r12, 0x84(r1)
	lha r26, 0x76(r29)
	stw r25, 0x4e4(r1)
	cmpwi r26, 0x0
	stw r11, 0x8e4(r1)
	stw r10, 0x8e8(r1)
	stw r9, 0x8ec(r1)
	stw r8, 0x8f0(r1)
	stw r7, 0x8f4(r1)
	stw r6, 0x8f8(r1)
	stw r5, 0x8fc(r1)
	stw r4, 0x900(r1)
	stw r3, 0x904(r1)
	stw r0, 0x908(r1)
	bge L_at24
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r26, r26
	b L_at25
	L_at24:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at25:
	mr r5, r26
	addi r3, r1, 0x1104
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r22, r1, 0x1104
	addi r21, r3, (unk_803dfbf8+0x100)@l
	addi r20, r1, 0x8e4
	li r19, 0x0
	b L_at26
	L_at27:
	lbz r0, 0x0(r22)
	mr r3, r21
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r20, r0
	bl strcat
	addi r22, r22, 0x1
	addi r19, r19, 0x1
	L_at26:
	addi r3, r1, 0x1104
	bl strlen
	cmplw r19, r3
	blt L_at27
	lis r4, (unk_803dfbf8+0x100)@ha
	addi r3, r1, 0x4e8
	addi r7, r4, (unk_803dfbf8+0x100)@l
	addi r5, r1, 0x84
	addi r4, r1, 0x4d0
	la r6, str_8041D63C(r0)
	crclr 6
	bl winFontSet
	lwz r0, 0x198(r30)
	cmpwi r0, 0x0
	ble L_at28
	lfs f0, float_130_8041d680(r0)
	mr r3, r30
	lfs f1, float_10_8041d61c(r0)
	li r4, 0x0
	fadds f0, f0, f30
	lfs f2, float_20_8041d628(r0)
	fadds f1, f1, f31
	lfs f3, float_260_8041d688(r0)
	lfs f4, float_80_8041d68c(r0)
	fadds f0, f2, f0
	fsubs f2, f0, f2
	bl winKirinukiGX
	bl winIconInit
	lfs f0, float_40_8041d690(r0)
	addi r4, r1, 0x4c4
	lwz r8, 0x4ac(r31)
	addi r5, r1, 0x4ac
	fadds f1, f0, f31
	lfs f2, float_10_8041d61c(r0)
	lfs f0, float_106_8041d694(r0)
	addi r6, r1, 0x80
	lwz r7, 0x4a4(r31)
	li r3, 0x20f
	lwz r0, 0x4a8(r31)
	fadds f18, f2, f1
	stw r7, 0x4b8(r1)
	fadds f24, f0, f30
	lwz r12, 0xd4(r1)
	stw r0, 0x4bc(r1)
	lwz r11, 0x4b0(r31)
	stfs f18, 0x4b8(r1)
	lwz r10, 0x4b4(r31)
	stfs f24, 0x4bc(r1)
	lwz r9, 0x4b8(r31)
	lwz r7, 0x4b8(r1)
	lwz r0, 0x4bc(r1)
	stw r12, 0x80(r1)
	stw r11, 0x4ac(r1)
	stw r10, 0x4b0(r1)
	stw r9, 0x4b4(r1)
	stw r8, 0x4c0(r1)
	stw r7, 0x4c4(r1)
	stw r0, 0x4c8(r1)
	stw r8, 0x4cc(r1)
	bl winIconSet
	lfs f0, float_70_8041d698(r0)
	addi r4, r1, 0x4a0
	lwz r3, 0x4bc(r31)
	addi r5, r1, 0x488
	lwz r0, 0x4c0(r31)
	fadds f19, f0, f30
	stw r3, 0x494(r1)
	addi r6, r1, 0x7c
	lwz r8, 0x4c4(r31)
	li r3, 0x197
	stw r0, 0x498(r1)
	lwz r12, 0xd4(r1)
	stfs f18, 0x494(r1)
	lwz r11, 0x4c8(r31)
	stfs f19, 0x498(r1)
	lwz r10, 0x4cc(r31)
	lwz r9, 0x4d0(r31)
	lwz r7, 0x494(r1)
	lwz r0, 0x498(r1)
	stw r12, 0x7c(r1)
	stw r11, 0x488(r1)
	stw r10, 0x48c(r1)
	stw r9, 0x490(r1)
	stw r8, 0x49c(r1)
	stw r7, 0x4a0(r1)
	stw r0, 0x4a4(r1)
	stw r8, 0x4a8(r1)
	bl winIconSet
	bl winFontInit
	lfs f0, float_70_8041d698(r0)
	addi r3, r31, 0x768
	lwz r5, 0x4dc(r31)
	fadds f1, f0, f31
	lfs f2, float_10_8041d61c(r0)
	lwz r4, 0x4d4(r31)
	lwz r0, 0x4d8(r31)
	fadds f0, f2, f19
	fadds f1, f2, f1
	stw r4, 0x470(r1)
	lwz r9, 0xd0(r1)
	stw r0, 0x474(r1)
	lwz r8, 0x4e0(r31)
	stfs f1, 0x470(r1)
	lwz r7, 0x4e4(r31)
	stfs f0, 0x474(r1)
	lwz r6, 0x4e8(r31)
	lwz r4, 0x470(r1)
	lwz r0, 0x474(r1)
	stw r9, 0x78(r1)
	stw r8, 0x464(r1)
	stw r7, 0x468(r1)
	stw r6, 0x46c(r1)
	stw r5, 0x478(r1)
	stw r4, 0x47c(r1)
	stw r0, 0x480(r1)
	stw r5, 0x484(r1)
	bl msgSearch
	mr r6, r3
	addi r3, r1, 0x47c
	addi r4, r1, 0x464
	addi r5, r1, 0x78
	crclr 6
	bl winFontSet
	bl winIconInit
	lfs f0, float_80_8041d68c(r0)
	li r22, 0x0
	lis r3, 0x51ec
	lfs f1, float_10_8041d61c(r0)
	fadds f0, f0, f31
	mr r21, r22
	subi r26, r3, 0x7ae1
	fadds f19, f1, f0
	b L_at29
	L_at30:
	lha r0, 0x7a(r29)
	mulhw r0, r26, r0
	srawi r0, r0, 5
	srwi r3, r0, 31
	add r0, r0, r3
	cmpw r22, r0
	bge L_at31
	xoris r3, r21, 0x8000
	lis r0, 0x4330
	stw r3, 0x181c(r1)
	addi r3, r22, 0x1b7
	lwz r8, 0x4f4(r31)
	addi r4, r1, 0x458
	stw r0, 0x1818(r1)
	addi r5, r1, 0x440
	lfd f1, 0x828(r31)
	addi r6, r1, 0x74
	lfd f0, 0x1818(r1)
	lwz r7, 0x4ec(r31)
	fsubs f0, f0, f1
	lwz r0, 0x4f0(r31)
	lwz r12, 0xdc(r1)
	stw r0, 0x450(r1)
	fadds f0, f19, f0
	lwz r11, 0x4f8(r31)
	stw r7, 0x44c(r1)
	lwz r10, 0x4fc(r31)
	stfs f0, 0x44c(r1)
	lwz r9, 0x500(r31)
	stfs f24, 0x450(r1)
	lwz r7, 0x44c(r1)
	lwz r0, 0x450(r1)
	stw r12, 0x74(r1)
	stw r11, 0x440(r1)
	stw r10, 0x444(r1)
	stw r9, 0x448(r1)
	stw r8, 0x454(r1)
	stw r7, 0x458(r1)
	stw r0, 0x45c(r1)
	stw r8, 0x460(r1)
	bl winIconSet
	b L_at32
	L_at31:
	xoris r3, r21, 0x8000
	lis r0, 0x4330
	stw r3, 0x181c(r1)
	addi r4, r1, 0x434
	lwz r8, 0x50c(r31)
	addi r5, r1, 0x41c
	stw r0, 0x1818(r1)
	addi r6, r1, 0x70
	lfd f1, 0x828(r31)
	li r3, 0x1bf
	lfd f0, 0x1818(r1)
	lwz r7, 0x504(r31)
	fsubs f0, f0, f1
	lwz r0, 0x508(r31)
	lwz r12, 0xdc(r1)
	stw r0, 0x42c(r1)
	fadds f0, f19, f0
	lwz r11, 0x510(r31)
	stw r7, 0x428(r1)
	lwz r10, 0x514(r31)
	stfs f0, 0x428(r1)
	lwz r9, 0x518(r31)
	stfs f24, 0x42c(r1)
	lwz r7, 0x428(r1)
	lwz r0, 0x42c(r1)
	stw r12, 0x70(r1)
	stw r11, 0x41c(r1)
	stw r10, 0x420(r1)
	stw r9, 0x424(r1)
	stw r8, 0x430(r1)
	stw r7, 0x434(r1)
	stw r0, 0x438(r1)
	stw r8, 0x43c(r1)
	bl winIconSet
	L_at32:
	addi r21, r21, 0x16
	addi r22, r22, 0x1
	L_at29:
	lwz r0, 0x198(r30)
	cmpw r22, r0
	blt L_at30
	L_at28:
	lfs f2, float_10_8041d61c(r0)
	mr r3, r30
	lfs f0, float_20_8041d628(r0)
	li r4, 0x0
	fadds f23, f2, f31
	lfs f3, float_260_8041d688(r0)
	fadds f0, f0, f30
	lfs f4, float_150_8041d69c(r0)
	fmr f1, f23
	fadds f2, f2, f0
	bl winKirinukiGX
	bl winIconInit
	lfs f0, float_20_8041d628(r0)
	addi r4, r1, 0x410
	lwz r8, 0x524(r31)
	addi r5, r1, 0x3f8
	fadds f1, f0, f31
	lfs f2, float_10_8041d61c(r0)
	lwz r7, 0x51c(r31)
	addi r6, r1, 0x6c
	lwz r0, 0x520(r31)
	fadds f0, f2, f30
	stw r0, 0x408(r1)
	fadds f24, f2, f1
	lwz r12, 0xd4(r1)
	li r3, 0x18c
	stw r7, 0x404(r1)
	lwz r11, 0x528(r31)
	stfs f24, 0x404(r1)
	lwz r10, 0x52c(r31)
	stfs f0, 0x408(r1)
	lwz r9, 0x530(r31)
	lwz r7, 0x404(r1)
	lwz r0, 0x408(r1)
	stw r12, 0x6c(r1)
	stw r11, 0x3f8(r1)
	stw r10, 0x3fc(r1)
	stw r9, 0x400(r1)
	stw r8, 0x40c(r1)
	stw r7, 0x410(r1)
	stw r0, 0x414(r1)
	stw r8, 0x418(r1)
	bl winIconSet
	lfs f0, float_28_8041d6a0(r0)
	addi r4, r1, 0x3ec
	lwz r8, 0x53c(r31)
	addi r5, r1, 0x3d4
	fsubs f0, f30, f0
	lfs f1, float_10_8041d61c(r0)
	lwz r7, 0x534(r31)
	addi r6, r1, 0x68
	lwz r0, 0x538(r31)
	li r3, 0x18b
	stw r7, 0x3e0(r1)
	fadds f0, f1, f0
	lwz r12, 0xd4(r1)
	stw r0, 0x3e4(r1)
	lwz r11, 0x540(r31)
	stfs f24, 0x3e0(r1)
	lwz r10, 0x544(r31)
	stfs f0, 0x3e4(r1)
	lwz r9, 0x548(r31)
	lwz r7, 0x3e0(r1)
	lwz r0, 0x3e4(r1)
	stw r12, 0x68(r1)
	stw r11, 0x3d4(r1)
	stw r10, 0x3d8(r1)
	stw r9, 0x3dc(r1)
	stw r8, 0x3e8(r1)
	stw r7, 0x3ec(r1)
	stw r0, 0x3f0(r1)
	stw r8, 0x3f4(r1)
	bl winIconSet
	lfs f0, float_56_8041d6a4(r0)
	addi r4, r1, 0x3c8
	lwz r8, 0x554(r31)
	addi r5, r1, 0x3b0
	fsubs f0, f30, f0
	lfs f1, float_10_8041d61c(r0)
	lwz r7, 0x54c(r31)
	addi r6, r1, 0x64
	lwz r0, 0x550(r31)
	li r3, 0x18d
	stw r7, 0x3bc(r1)
	fadds f0, f1, f0
	lwz r12, 0xd4(r1)
	stw r0, 0x3c0(r1)
	lwz r11, 0x558(r31)
	stfs f24, 0x3bc(r1)
	lwz r10, 0x55c(r31)
	stfs f0, 0x3c0(r1)
	lwz r9, 0x560(r31)
	lwz r7, 0x3bc(r1)
	lwz r0, 0x3c0(r1)
	stw r12, 0x64(r1)
	stw r11, 0x3b0(r1)
	stw r10, 0x3b4(r1)
	stw r9, 0x3b8(r1)
	stw r8, 0x3c4(r1)
	stw r7, 0x3c8(r1)
	stw r0, 0x3cc(r1)
	stw r8, 0x3d0(r1)
	bl winIconSet
	lfs f0, float_84_8041d6a8(r0)
	addi r4, r1, 0x3a4
	lwz r8, 0x56c(r31)
	addi r5, r1, 0x38c
	fsubs f0, f30, f0
	lfs f1, float_10_8041d61c(r0)
	lwz r7, 0x564(r31)
	addi r6, r1, 0x60
	lwz r0, 0x568(r31)
	li r3, 0x102
	stw r7, 0x398(r1)
	fadds f0, f1, f0
	lwz r12, 0xd4(r1)
	stw r0, 0x39c(r1)
	lwz r11, 0x570(r31)
	stfs f24, 0x398(r1)
	lwz r10, 0x574(r31)
	stfs f0, 0x39c(r1)
	lwz r9, 0x578(r31)
	lwz r7, 0x398(r1)
	lwz r0, 0x39c(r1)
	stw r12, 0x60(r1)
	stw r11, 0x38c(r1)
	stw r10, 0x390(r1)
	stw r9, 0x394(r1)
	stw r8, 0x3a0(r1)
	stw r7, 0x3a4(r1)
	stw r0, 0x3a8(r1)
	stw r8, 0x3ac(r1)
	bl winIconSet
	lfs f0, float_112_8041d644(r0)
	addi r4, r1, 0x380
	lwz r8, 0x584(r31)
	addi r5, r1, 0x368
	fsubs f0, f30, f0
	lfs f1, float_10_8041d61c(r0)
	lwz r7, 0x57c(r31)
	addi r6, r1, 0x5c
	lwz r0, 0x580(r31)
	li r3, 0x1a2
	stw r7, 0x374(r1)
	fadds f0, f1, f0
	lwz r12, 0xd4(r1)
	stw r0, 0x378(r1)
	lwz r11, 0x588(r31)
	stfs f24, 0x374(r1)
	lwz r10, 0x58c(r31)
	stfs f0, 0x378(r1)
	lwz r9, 0x590(r31)
	lwz r7, 0x374(r1)
	lwz r0, 0x378(r1)
	stw r12, 0x5c(r1)
	stw r11, 0x368(r1)
	stw r10, 0x36c(r1)
	stw r9, 0x370(r1)
	stw r8, 0x37c(r1)
	stw r7, 0x380(r1)
	stw r0, 0x384(r1)
	stw r8, 0x388(r1)
	bl winIconSet
	bl winFontInit
	lfs f1, float_35_8041d6ac(r0)
	addi r3, r31, 0x780
	lfs f0, float_12_8041d670(r0)
	fadds f1, f1, f31
	lwz r5, 0x59c(r31)
	lfs f2, float_10_8041d61c(r0)
	fadds f25, f0, f30
	lwz r4, 0x594(r31)
	lwz r0, 0x598(r31)
	fadds f24, f2, f1
	stw r4, 0x350(r1)
	fadds f26, f2, f25
	lwz r9, 0xd0(r1)
	stw r0, 0x354(r1)
	lwz r8, 0x5a0(r31)
	stfs f24, 0x350(r1)
	lwz r7, 0x5a4(r31)
	stfs f26, 0x354(r1)
	lwz r6, 0x5a8(r31)
	lwz r4, 0x350(r1)
	lwz r0, 0x354(r1)
	stw r9, 0x58(r1)
	stw r8, 0x344(r1)
	stw r7, 0x348(r1)
	stw r6, 0x34c(r1)
	stw r5, 0x358(r1)
	stw r4, 0x35c(r1)
	stw r0, 0x360(r1)
	stw r5, 0x364(r1)
	bl msgSearch
	mr r6, r3
	addi r3, r1, 0x35c
	addi r4, r1, 0x344
	addi r5, r1, 0x58
	crclr 6
	bl winFontSet
	lfs f0, float_28_8041d6a0(r0)
	addi r3, r31, 0x798
	lwz r5, 0x5b4(r31)
	fsubs f0, f25, f0
	lfs f1, float_10_8041d61c(r0)
	lwz r4, 0x5ac(r31)
	lwz r0, 0x5b0(r31)
	fadds f27, f1, f0
	stw r4, 0x32c(r1)
	lwz r9, 0xd0(r1)
	stw r0, 0x330(r1)
	lwz r8, 0x5b8(r31)
	stfs f24, 0x32c(r1)
	lwz r7, 0x5bc(r31)
	stfs f27, 0x330(r1)
	lwz r6, 0x5c0(r31)
	lwz r4, 0x32c(r1)
	lwz r0, 0x330(r1)
	stw r9, 0x54(r1)
	stw r8, 0x320(r1)
	stw r7, 0x324(r1)
	stw r6, 0x328(r1)
	stw r5, 0x334(r1)
	stw r4, 0x338(r1)
	stw r0, 0x33c(r1)
	stw r5, 0x340(r1)
	bl msgSearch
	mr r6, r3
	addi r3, r1, 0x338
	addi r4, r1, 0x320
	addi r5, r1, 0x54
	crclr 6
	bl winFontSet
	lfs f0, float_56_8041d6a4(r0)
	addi r3, r31, 0x7b0
	lwz r5, 0x5cc(r31)
	fsubs f0, f25, f0
	lfs f1, float_10_8041d61c(r0)
	lwz r4, 0x5c4(r31)
	lwz r0, 0x5c8(r31)
	fadds f28, f1, f0
	stw r4, 0x308(r1)
	lwz r9, 0xd0(r1)
	stw r0, 0x30c(r1)
	lwz r8, 0x5d0(r31)
	stfs f24, 0x308(r1)
	lwz r7, 0x5d4(r31)
	stfs f28, 0x30c(r1)
	lwz r6, 0x5d8(r31)
	lwz r4, 0x308(r1)
	lwz r0, 0x30c(r1)
	stw r9, 0x50(r1)
	stw r8, 0x2fc(r1)
	stw r7, 0x300(r1)
	stw r6, 0x304(r1)
	stw r5, 0x310(r1)
	stw r4, 0x314(r1)
	stw r0, 0x318(r1)
	stw r5, 0x31c(r1)
	bl msgSearch
	mr r6, r3
	addi r3, r1, 0x314
	addi r4, r1, 0x2fc
	addi r5, r1, 0x50
	crclr 6
	bl winFontSet
	lfs f0, float_84_8041d6a8(r0)
	addi r3, r31, 0x7cc
	lwz r5, 0x5e4(r31)
	fsubs f0, f25, f0
	lfs f1, float_10_8041d61c(r0)
	lwz r4, 0x5dc(r31)
	lwz r0, 0x5e0(r31)
	fadds f29, f1, f0
	stw r4, 0x2e4(r1)
	lwz r9, 0xd0(r1)
	stw r0, 0x2e8(r1)
	lwz r8, 0x5e8(r31)
	stfs f24, 0x2e4(r1)
	lwz r7, 0x5ec(r31)
	stfs f29, 0x2e8(r1)
	lwz r6, 0x5f0(r31)
	lwz r4, 0x2e4(r1)
	lwz r0, 0x2e8(r1)
	stw r9, 0x4c(r1)
	stw r8, 0x2d8(r1)
	stw r7, 0x2dc(r1)
	stw r6, 0x2e0(r1)
	stw r5, 0x2ec(r1)
	stw r4, 0x2f0(r1)
	stw r0, 0x2f4(r1)
	stw r5, 0x2f8(r1)
	bl msgSearch
	mr r6, r3
	addi r3, r1, 0x2f0
	addi r4, r1, 0x2d8
	addi r5, r1, 0x4c
	crclr 6
	bl winFontSet
	lfs f0, float_112_8041d644(r0)
	addi r3, r31, 0x7ec
	lwz r5, 0x5fc(r31)
	fsubs f0, f25, f0
	lfs f1, float_10_8041d61c(r0)
	lwz r4, 0x5f4(r31)
	lwz r0, 0x5f8(r31)
	fadds f25, f1, f0
	stw r4, 0x2c0(r1)
	lwz r9, 0xd0(r1)
	stw r0, 0x2c4(r1)
	lwz r8, 0x600(r31)
	stfs f24, 0x2c0(r1)
	lwz r7, 0x604(r31)
	stfs f25, 0x2c4(r1)
	lwz r6, 0x608(r31)
	lwz r4, 0x2c0(r1)
	lwz r0, 0x2c4(r1)
	stw r9, 0x48(r1)
	stw r8, 0x2b4(r1)
	stw r7, 0x2b8(r1)
	stw r6, 0x2bc(r1)
	stw r5, 0x2c8(r1)
	stw r4, 0x2cc(r1)
	stw r0, 0x2d0(r1)
	stw r5, 0x2d4(r1)
	bl msgSearch
	mr r6, r3
	addi r3, r1, 0x2cc
	addi r4, r1, 0x2b4
	addi r5, r1, 0x48
	crclr 6
	bl winFontSet
	lfs f0, float_205_8041d6b4(r0)
	lwz r24, 0x614(r31)
	fadds f0, f0, f31
	lfs f1, float_8_8041d6b0(r0)
	lwz r3, 0x60c(r31)
	lwz r0, 0x610(r31)
	fadds f0, f1, f0
	lfs f1, float_2_8041d660(r0)
	stw r0, 0x2a0(r1)
	lwz r22, 0x618(r31)
	fadds f18, f1, f0
	stw r3, 0x29c(r1)
	lwz r21, 0x61c(r31)
	stfs f26, 0x2a0(r1)
	lwz r20, 0x620(r31)
	stfs f18, 0x29c(r1)
	lwz r23, 0x2a0(r1)
	lwz r0, 0x29c(r1)
	lwz r12, 0xd0(r1)
	stw r0, 0x2a8(r1)
	lwz r11, 0x184(r31)
	lwz r10, 0x188(r31)
	lwz r9, 0x18c(r31)
	lwz r8, 0x190(r31)
	lwz r7, 0x194(r31)
	lwz r6, 0x198(r31)
	lwz r5, 0x19c(r31)
	lwz r4, 0x1a0(r31)
	lwz r3, 0x1a4(r31)
	lwz r0, 0x1a8(r31)
	stw r23, 0x2ac(r1)
	stw r24, 0x2b0(r1)
	stw r22, 0x290(r1)
	stw r21, 0x294(r1)
	stw r20, 0x298(r1)
	stw r12, 0x44(r1)
	lha r26, 0x96(r29)
	stw r24, 0x2a4(r1)
	cmpwi r26, 0x0
	stw r11, 0x8bc(r1)
	stw r10, 0x8c0(r1)
	stw r9, 0x8c4(r1)
	stw r8, 0x8c8(r1)
	stw r7, 0x8cc(r1)
	stw r6, 0x8d0(r1)
	stw r5, 0x8d4(r1)
	stw r4, 0x8d8(r1)
	stw r3, 0x8dc(r1)
	stw r0, 0x8e0(r1)
	bge L_at33
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r26, r26
	b L_at34
	L_at33:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at34:
	mr r5, r26
	addi r3, r1, 0x1004
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r22, r1, 0x1004
	addi r21, r3, (unk_803dfbf8+0x100)@l
	addi r20, r1, 0x8bc
	li r19, 0x0
	b L_at35
	L_at36:
	lbz r0, 0x0(r22)
	mr r3, r21
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r20, r0
	bl strcat
	addi r22, r22, 0x1
	addi r19, r19, 0x1
	L_at35:
	addi r3, r1, 0x1004
	bl strlen
	cmplw r19, r3
	blt L_at36
	lis r4, (unk_803dfbf8+0x100)@ha
	addi r3, r1, 0x2a8
	addi r7, r4, (unk_803dfbf8+0x100)@l
	addi r5, r1, 0x44
	addi r4, r1, 0x290
	la r6, str_8041D63C(r0)
	crclr 6
	bl winFontSetR
	lwz r3, 0x624(r31)
	lwz r0, 0x628(r31)
	stw r3, 0x278(r1)
	lwz r25, 0x62c(r31)
	stw r0, 0x27c(r1)
	lwz r22, 0x630(r31)
	stfs f18, 0x278(r1)
	lwz r21, 0x634(r31)
	stfs f27, 0x27c(r1)
	lwz r24, 0x278(r1)
	lwz r23, 0x27c(r1)
	lwz r20, 0x638(r31)
	lwz r12, 0xd0(r1)
	lwz r11, 0x184(r31)
	lwz r10, 0x188(r31)
	lwz r9, 0x18c(r31)
	lwz r8, 0x190(r31)
	lwz r7, 0x194(r31)
	lwz r6, 0x198(r31)
	lwz r5, 0x19c(r31)
	lwz r4, 0x1a0(r31)
	lwz r3, 0x1a4(r31)
	lwz r0, 0x1a8(r31)
	stw r24, 0x284(r1)
	stw r23, 0x288(r1)
	stw r25, 0x28c(r1)
	stw r22, 0x26c(r1)
	stw r21, 0x270(r1)
	stw r20, 0x274(r1)
	stw r12, 0x40(r1)
	lha r26, 0x78(r29)
	stw r25, 0x280(r1)
	cmpwi r26, 0x0
	stw r11, 0x894(r1)
	stw r10, 0x898(r1)
	stw r9, 0x89c(r1)
	stw r8, 0x8a0(r1)
	stw r7, 0x8a4(r1)
	stw r6, 0x8a8(r1)
	stw r5, 0x8ac(r1)
	stw r4, 0x8b0(r1)
	stw r3, 0x8b4(r1)
	stw r0, 0x8b8(r1)
	bge L_at37
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r26, r26
	b L_at38
	L_at37:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at38:
	mr r5, r26
	addi r3, r1, 0xf04
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r22, r1, 0xf04
	addi r21, r3, (unk_803dfbf8+0x100)@l
	addi r20, r1, 0x894
	li r19, 0x0
	b L_at39
	L_at40:
	lbz r0, 0x0(r22)
	mr r3, r21
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r20, r0
	bl strcat
	addi r22, r22, 0x1
	addi r19, r19, 0x1
	L_at39:
	addi r3, r1, 0xf04
	bl strlen
	cmplw r19, r3
	blt L_at40
	lis r4, (unk_803dfbf8+0x100)@ha
	addi r3, r1, 0x284
	addi r7, r4, (unk_803dfbf8+0x100)@l
	addi r5, r1, 0x40
	addi r4, r1, 0x26c
	la r6, str_8041D63C(r0)
	crclr 6
	bl winFontSetR
	lwz r3, 0x63c(r31)
	lwz r0, 0x640(r31)
	stw r3, 0x254(r1)
	lwz r25, 0x644(r31)
	stw r0, 0x258(r1)
	lwz r22, 0x648(r31)
	stfs f18, 0x254(r1)
	lwz r21, 0x64c(r31)
	stfs f28, 0x258(r1)
	lwz r24, 0x254(r1)
	lwz r23, 0x258(r1)
	lwz r20, 0x650(r31)
	lwz r12, 0xd0(r1)
	lwz r11, 0x184(r31)
	lwz r10, 0x188(r31)
	lwz r9, 0x18c(r31)
	lwz r8, 0x190(r31)
	lwz r7, 0x194(r31)
	lwz r6, 0x198(r31)
	lwz r5, 0x19c(r31)
	lwz r4, 0x1a0(r31)
	lwz r3, 0x1a4(r31)
	lwz r0, 0x1a8(r31)
	stw r24, 0x260(r1)
	stw r23, 0x264(r1)
	stw r25, 0x268(r1)
	stw r22, 0x248(r1)
	stw r21, 0x24c(r1)
	stw r20, 0x250(r1)
	stw r12, 0x3c(r1)
	lha r26, 0x9a(r29)
	stw r25, 0x25c(r1)
	cmpwi r26, 0x0
	stw r11, 0x86c(r1)
	stw r10, 0x870(r1)
	stw r9, 0x874(r1)
	stw r8, 0x878(r1)
	stw r7, 0x87c(r1)
	stw r6, 0x880(r1)
	stw r5, 0x884(r1)
	stw r4, 0x888(r1)
	stw r3, 0x88c(r1)
	stw r0, 0x890(r1)
	bge L_at41
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r26, r26
	b L_at42
	L_at41:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at42:
	mr r5, r26
	addi r3, r1, 0xe04
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r22, r1, 0xe04
	addi r21, r3, (unk_803dfbf8+0x100)@l
	addi r20, r1, 0x86c
	li r19, 0x0
	b L_at43
	L_at44:
	lbz r0, 0x0(r22)
	mr r3, r21
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r20, r0
	bl strcat
	addi r22, r22, 0x1
	addi r19, r19, 0x1
	L_at43:
	addi r3, r1, 0xe04
	bl strlen
	cmplw r19, r3
	blt L_at44
	lis r4, (unk_803dfbf8+0x100)@ha
	addi r3, r1, 0x260
	addi r7, r4, (unk_803dfbf8+0x100)@l
	addi r5, r1, 0x3c
	addi r4, r1, 0x248
	la r6, str_8041D63C(r0)
	crclr 6
	bl winFontSetR
	lwz r3, 0x654(r31)
	lwz r0, 0x658(r31)
	stw r3, 0x230(r1)
	lwz r25, 0x65c(r31)
	stw r0, 0x234(r1)
	lwz r22, 0x660(r31)
	stfs f18, 0x230(r1)
	lwz r21, 0x664(r31)
	stfs f29, 0x234(r1)
	lwz r24, 0x230(r1)
	lwz r23, 0x234(r1)
	lwz r20, 0x668(r31)
	lwz r12, 0xd0(r1)
	lwz r11, 0x184(r31)
	lwz r10, 0x188(r31)
	lwz r9, 0x18c(r31)
	lwz r8, 0x190(r31)
	lwz r7, 0x194(r31)
	lwz r6, 0x198(r31)
	lwz r5, 0x19c(r31)
	lwz r4, 0x1a0(r31)
	lwz r3, 0x1a4(r31)
	lwz r0, 0x1a8(r31)
	stw r24, 0x23c(r1)
	stw r23, 0x240(r1)
	stw r25, 0x244(r1)
	stw r22, 0x224(r1)
	stw r21, 0x228(r1)
	stw r20, 0x22c(r1)
	stw r12, 0x38(r1)
	lha r26, 0x9c(r29)
	stw r25, 0x238(r1)
	cmpwi r26, 0x0
	stw r11, 0x844(r1)
	stw r10, 0x848(r1)
	stw r9, 0x84c(r1)
	stw r8, 0x850(r1)
	stw r7, 0x854(r1)
	stw r6, 0x858(r1)
	stw r5, 0x85c(r1)
	stw r4, 0x860(r1)
	stw r3, 0x864(r1)
	stw r0, 0x868(r1)
	bge L_at45
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r26, r26
	b L_at46
	L_at45:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at46:
	mr r5, r26
	addi r3, r1, 0xd04
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r22, r1, 0xd04
	addi r21, r3, (unk_803dfbf8+0x100)@l
	addi r20, r1, 0x844
	li r19, 0x0
	b L_at47
	L_at48:
	lbz r0, 0x0(r22)
	mr r3, r21
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r20, r0
	bl strcat
	addi r22, r22, 0x1
	addi r19, r19, 0x1
	L_at47:
	addi r3, r1, 0xd04
	bl strlen
	cmplw r19, r3
	blt L_at48
	lis r4, (unk_803dfbf8+0x100)@ha
	addi r3, r1, 0x23c
	addi r7, r4, (unk_803dfbf8+0x100)@l
	addi r5, r1, 0x38
	addi r4, r1, 0x224
	la r6, str_8041D63C(r0)
	crclr 6
	bl winFontSetR
	lis r3, 0x8000
	lwz r4, gp(r0)
	lwz r0, 0xf8(r3)
	li r5, 0x0
	lwz r3, 0x20(r4)
	lwz r4, 0x24(r4)
	srwi r6, r0, 2
	bl __div2i
	lis r5, 0x5
	mr r7, r4
	addi r0, r5, 0x7e3f
	li r6, 0x0
	mr r5, r3
	subfc r0, r7, r0
	subfe r0, r5, r6
	subfe r0, r28, r28
	neg. r0, r0
	beq L_at49
	li r20, 0x63
	li r21, 0x3b
	b L_at50
	L_at49:
	mr r21, r7
	mr r19, r5
	li r5, 0x0
	li r6, 0xe10
	bl __div2u
	mr r20, r4
	mr r3, r19
	mr r4, r21
	li r5, 0x0
	li r6, 0xe10
	bl __mod2u
	li r5, 0x0
	li r6, 0x3c
	bl __div2u
	mr r21, r4
	L_at50:
	lfs f0, float_172_8041d6b8(r0)
	cmpwi r20, 0x0
	lwz r28, 0x674(r31)
	mr r26, r20
	fadds f0, f0, f31
	lfs f1, float_8_8041d6b0(r0)
	lwz r3, 0x66c(r31)
	lwz r0, 0x670(r31)
	fadds f1, f1, f0
	lfs f0, float_16_8041d6bc(r0)
	stw r0, 0x210(r1)
	lwz r24, 0x678(r31)
	fsubs f0, f1, f0
	lfs f1, float_2_8041d660(r0)
	stfs f25, 0x210(r1)
	lwz r23, 0x67c(r31)
	fadds f0, f1, f0
	lwz r25, 0x210(r1)
	lwz r22, 0x680(r31)
	lwz r12, 0xd0(r1)
	fadds f0, f1, f0
	stw r3, 0x20c(r1)
	lwz r11, 0x1ac(r31)
	lwz r10, 0x1b0(r31)
	stfs f0, 0x20c(r1)
	lwz r9, 0x1b4(r31)
	lwz r27, 0x20c(r1)
	lwz r8, 0x1b8(r31)
	lwz r7, 0x1bc(r31)
	lwz r6, 0x1c0(r31)
	lwz r5, 0x1c4(r31)
	lwz r4, 0x1c8(r31)
	lwz r3, 0x1cc(r31)
	lwz r0, 0x1d0(r31)
	stw r28, 0x214(r1)
	stw r27, 0x218(r1)
	stw r25, 0x21c(r1)
	stw r28, 0x220(r1)
	stw r24, 0x200(r1)
	stw r23, 0x204(r1)
	stw r22, 0x208(r1)
	stw r12, 0x34(r1)
	stw r11, 0x81c(r1)
	stw r10, 0x820(r1)
	stw r9, 0x824(r1)
	stw r8, 0x828(r1)
	stw r7, 0x82c(r1)
	stw r6, 0x830(r1)
	stw r5, 0x834(r1)
	stw r4, 0x838(r1)
	stw r3, 0x83c(r1)
	stw r0, 0x840(r1)
	bge L_at51
	lis r3, unk_803dfbf8@ha
	la r4, str_8041D630(r0)
	addi r3, r3, unk_803dfbf8@l
	bl strcpy
	neg r26, r20
	b L_at52
	L_at51:
	lis r3, unk_803dfbf8@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, unk_803dfbf8@l
	bl strcpy
	L_at52:
	mr r5, r26
	addi r3, r1, 0xc04
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	li r19, 0x0
	L_at53:
	addi r3, r1, 0xc04
	bl strlen
	subfic r0, r3, 0x2
	cmplw r19, r0
	bge L_at54
	lis r3, unk_803dfbf8@ha
	la r4, str_8041D5A8(r0)
	addi r3, r3, unk_803dfbf8@l
	bl strcat
	b L_at55
	L_at54:
	addi r3, r1, 0xc04
	bl strlen
	subfic r0, r3, 0x2
	lis r3, unk_803dfbf8@ha
	subf r0, r0, r19
	addi r4, r1, 0xc04
	lbzx r0, r4, r0
	addi r4, r1, 0x81c
	addi r3, r3, unk_803dfbf8@l
	extsb r0, r0
	slwi r5, r0, 2
	subi r0, r5, 0xc0
	lwzx r4, r4, r0
	bl strcat
	L_at55:
	addi r19, r19, 0x1
	cmpwi r19, 0x2
	blt L_at53
	lis r4, unk_803dfbf8@ha
	addi r3, r1, 0x218
	addi r7, r4, unk_803dfbf8@l
	addi r5, r1, 0x34
	addi r4, r1, 0x200
	la r6, str_8041D63C(r0)
	crclr 6
	bl winFontSetR
	lwz r3, 0x684(r31)
	cmpwi r21, 0x0
	lwz r0, 0x688(r31)
	mr r26, r21
	stw r3, 0x1e8(r1)
	lwz r27, 0x68c(r31)
	stw r0, 0x1ec(r1)
	lwz r23, 0x690(r31)
	stfs f18, 0x1e8(r1)
	lwz r22, 0x694(r31)
	stfs f25, 0x1ec(r1)
	lwz r25, 0x1e8(r1)
	lwz r24, 0x1ec(r1)
	lwz r20, 0x698(r31)
	lwz r12, 0xd0(r1)
	lwz r11, 0x1ac(r31)
	lwz r10, 0x1b0(r31)
	lwz r9, 0x1b4(r31)
	lwz r8, 0x1b8(r31)
	lwz r7, 0x1bc(r31)
	lwz r6, 0x1c0(r31)
	lwz r5, 0x1c4(r31)
	lwz r4, 0x1c8(r31)
	lwz r3, 0x1cc(r31)
	lwz r0, 0x1d0(r31)
	stw r27, 0x1f0(r1)
	stw r25, 0x1f4(r1)
	stw r24, 0x1f8(r1)
	stw r27, 0x1fc(r1)
	stw r23, 0x1dc(r1)
	stw r22, 0x1e0(r1)
	stw r20, 0x1e4(r1)
	stw r12, 0x30(r1)
	stw r11, 0x7f4(r1)
	stw r10, 0x7f8(r1)
	stw r9, 0x7fc(r1)
	stw r8, 0x800(r1)
	stw r7, 0x804(r1)
	stw r6, 0x808(r1)
	stw r5, 0x80c(r1)
	stw r4, 0x810(r1)
	stw r3, 0x814(r1)
	stw r0, 0x818(r1)
	bge L_at56
	lis r3, unk_803dfbf8@ha
	la r4, str_8041D630(r0)
	addi r3, r3, unk_803dfbf8@l
	bl strcpy
	neg r26, r21
	b L_at57
	L_at56:
	lis r3, unk_803dfbf8@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, unk_803dfbf8@l
	bl strcpy
	L_at57:
	mr r5, r26
	addi r3, r1, 0xb04
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	li r19, 0x0
	L_at58:
	addi r3, r1, 0xb04
	bl strlen
	subfic r0, r3, 0x2
	cmplw r19, r0
	bge L_at59
	lis r3, unk_803dfbf8@ha
	la r4, str_8041D5A8(r0)
	addi r3, r3, unk_803dfbf8@l
	bl strcat
	b L_at60
	L_at59:
	addi r3, r1, 0xb04
	bl strlen
	subfic r0, r3, 0x2
	lis r3, unk_803dfbf8@ha
	subf r0, r0, r19
	addi r4, r1, 0xb04
	lbzx r0, r4, r0
	addi r4, r1, 0x7f4
	addi r3, r3, unk_803dfbf8@l
	extsb r0, r0
	slwi r5, r0, 2
	subi r0, r5, 0xc0
	lwzx r4, r4, r0
	bl strcat
	L_at60:
	addi r19, r19, 0x1
	cmpwi r19, 0x2
	blt L_at58
	lis r4, unk_803dfbf8@ha
	addi r3, r1, 0x1f4
	addi r7, r4, unk_803dfbf8@l
	addi r5, r1, 0x30
	addi r4, r1, 0x1dc
	la r6, str_8041D63C(r0)
	crclr 6
	bl winFontSetR
	lwz r3, 0x28(r30)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lfs f0, float_190_8041d614(r0)
	li r22, 0x0
	lfs f24, float_10_8041d61c(r0)
	mr r19, r22
	fadds f0, f0, f31
	lwz r21, 0xdc(r1)
	lfd f22, 0x828(r31)
	lis r20, 0x4330
	fadds f19, f24, f0
	L_at61:
	xoris r0, r19, 0x8000
	lwz r8, 0x6a4(r31)
	stw r0, 0x181c(r1)
	addi r4, r1, 0x1d0
	lwz r7, 0x69c(r31)
	addi r5, r1, 0x1b8
	stw r20, 0x1818(r1)
	addi r6, r1, 0x2c
	lwz r0, 0x6a0(r31)
	li r3, 0x11
	lfd f0, 0x1818(r1)
	stw r7, 0x1c4(r1)
	fsubs f0, f0, f22
	lwz r11, 0x6a8(r31)
	stfs f19, 0x1c4(r1)
	lwz r10, 0x6ac(r31)
	fsubs f0, f30, f0
	lwz r9, 0x6b0(r31)
	lwz r7, 0x1c4(r1)
	stw r0, 0x1c8(r1)
	fadds f0, f24, f0
	stw r21, 0x2c(r1)
	stfs f0, 0x1c8(r1)
	lwz r0, 0x1c8(r1)
	stw r11, 0x1b8(r1)
	stw r10, 0x1bc(r1)
	stw r9, 0x1c0(r1)
	stw r8, 0x1cc(r1)
	stw r7, 0x1d0(r1)
	stw r0, 0x1d4(r1)
	stw r8, 0x1d8(r1)
	bl winTexSet
	addi r22, r22, 0x1
	addi r19, r19, 0x1c
	cmpwi r22, 0x4
	blt L_at61
	lfs f0, float_112_8041d644(r0)
	addi r4, r1, 0x1ac
	lwz r8, 0x6bc(r31)
	addi r5, r1, 0x194
	fsubs f0, f30, f0
	lfs f1, float_2_8041d660(r0)
	lfs f3, float_220_8041d6c0(r0)
	addi r6, r1, 0x28
	lwz r7, 0x6b4(r31)
	li r3, 0x12
	fadds f0, f1, f0
	lfs f2, float_10_8041d61c(r0)
	lwz r0, 0x6b8(r31)
	fadds f24, f3, f31
	stw r7, 0x1a0(r1)
	fadds f0, f2, f0
	stfs f24, 0x1a0(r1)
	lwz r12, 0xd4(r1)
	fsubs f0, f0, f1
	stw r0, 0x1a4(r1)
	lwz r11, 0x6c0(r31)
	lwz r10, 0x6c4(r31)
	stfs f0, 0x1a4(r1)
	lwz r9, 0x6c8(r31)
	lwz r7, 0x1a0(r1)
	lwz r0, 0x1a4(r1)
	stw r12, 0x28(r1)
	stw r11, 0x194(r1)
	stw r10, 0x198(r1)
	stw r9, 0x19c(r1)
	stw r8, 0x1a8(r1)
	stw r7, 0x1ac(r1)
	stw r0, 0x1b0(r1)
	stw r8, 0x1b4(r1)
	bl winTexSet
	lwz r3, 0x188(r30)
	bl animPoseGetAnimPosePtr
	lwz r3, 0x188(r30)
	bl animPoseGetAnimDataPtr
	lwz r0, 0x18c(r30)
	cmpwi r0, 0x0
	bne L_at62
	lwz r3, 0x24(r3)
	lis r0, 0x4330
	lwz r4, gp(r0)
	lfs f0, 0x8(r3)
	lwz r5, 0x1c(r4)
	fctiwz f0, f0
	stw r0, 0x1810(r1)
	lfd f1, 0x820(r31)
	lwz r3, 0x188(r30)
	stfd f0, 0x1818(r1)
	lwz r4, 0x181c(r1)
	divwu r0, r5, r4
	mullw r0, r0, r4
	subf r0, r0, r5
	stw r0, 0x1814(r1)
	lfd f0, 0x1810(r1)
	fsubs f1, f0, f1
	bl animPoseSetLocalTime
	L_at62:
	lwz r3, 0x188(r30)
	bl animPoseMain
	lfs f0, float_150_8041d69c(r0)
	fmr f2, f30
	lwz r0, dat_8041d608(r0)
	mr r3, r30
	fsubs f1, f31, f0
	lfs f3, float_0_8041d6c4(r0)
	stw r0, 0x24(r1)
	lfs f4, float_1_8041d6c8(r0)
	addi r4, r1, 0x24
	bl winKageGX
	lfs f0, float_150_8041d69c(r0)
	fmr f2, f30
	lfs f3, float_0_8041d6c4(r0)
	addi r3, r1, 0x9d4
	fsubs f1, f31, f0
	bl PSMTXTrans
	bl winZClear
	lwz r3, 0x188(r30)
	addi r4, r1, 0x9d4
	lfs f1, float_0_8041d6c4(r0)
	li r5, 0x2
	lfs f2, float_5_8041d6cc(r0)
	bl animPoseDrawMtx
	lwz r0, 0x190(r30)
	cmpwi r0, 0x0
	beq L_at63
	lfs f3, float_270_8041d650(r0)
	mr r3, r30
	lfs f2, float_160_8041d6d0(r0)
	li r4, 0x0
	fsubs f1, f31, f3
	lfs f4, float_254_8041d6d4(r0)
	bl winWazaGX
	bl winFontInit
	lfs f0, float_90_8041d6d8(r0)
	addi r3, r31, 0x808
	lwz r5, 0x6d0(r31)
	fadds f1, f0, f31
	lwz r4, 0x6d4(r31)
	lfs f0, float_270_8041d650(r0)
	lwz r0, 0x6cc(r31)
	fsubs f0, f1, f0
	lwz r9, 0xd4(r1)
	stw r0, 0x17c(r1)
	lwz r8, 0x6d8(r31)
	stfs f0, 0x17c(r1)
	lwz r7, 0x6dc(r31)
	lwz r6, 0x6e0(r31)
	lwz r0, 0x17c(r1)
	stw r9, 0x20(r1)
	stw r8, 0x170(r1)
	stw r7, 0x174(r1)
	stw r6, 0x178(r1)
	stw r5, 0x180(r1)
	stw r4, 0x184(r1)
	stw r0, 0x188(r1)
	stw r5, 0x18c(r1)
	stw r4, 0x190(r1)
	bl msgSearch
	mr r6, r3
	addi r3, r1, 0x188
	addi r4, r1, 0x170
	addi r5, r1, 0x20
	crclr 6
	bl winFontSetEdge
	lfs f0, float_270_8041d650(r0)
	addi r3, r1, 0x164
	lwz r0, 0x6e4(r31)
	addi r4, r1, 0x14c
	fsubs f0, f24, f0
	lwz r8, 0x6e8(r31)
	stw r0, 0x158(r1)
	addi r5, r1, 0x1c
	lwz r7, 0x6ec(r31)
	la r6, str_8041D6DC(r0)
	stfs f0, 0x158(r1)
	lwz r12, 0xd4(r1)
	lwz r11, 0x6f0(r31)
	lwz r10, 0x6f4(r31)
	lwz r9, 0x6f8(r31)
	lwz r0, 0x158(r1)
	stw r12, 0x1c(r1)
	stw r11, 0x14c(r1)
	stw r10, 0x150(r1)
	stw r9, 0x154(r1)
	stw r8, 0x15c(r1)
	stw r7, 0x160(r1)
	stw r0, 0x164(r1)
	stw r8, 0x168(r1)
	stw r7, 0x16c(r1)
	crclr 6
	bl winFontSetEdge
	lfs f0, float_17_8041d6e8(r0)
	lis r4, superActionTable@ha
	lfs f4, float_270_8041d650(r0)
	lis r3, (unk_803dfbf8+0x100)@ha
	fadds f0, f0, f24
	lfs f1, float_228_8041d6e4(r0)
	li r24, 0x0
	fsubs f3, f23, f4
	fadds f2, f1, f31
	lfs f5, float_10_8041d61c(r0)
	fsubs f0, f0, f4
	lfs f1, float_4_8041d66c(r0)
	fsubs f20, f2, f4
	lwz r26, 0xd8(r1)
	fadds f19, f5, f3
	lfd f22, 0x828(r31)
	fadds f21, f1, f0
	addi r22, r4, superActionTable@l
	addi r29, r3, (unk_803dfbf8+0x100)@l
	mr r21, r24
	addi r28, r1, 0x7cc
	lis r27, 0x4330
	b L_at64
	L_at65:
	subfic r23, r21, 0x82
	lwz r8, 0x704(r31)
	xoris r0, r23, 0x8000
	lwz r6, 0x6fc(r31)
	stw r0, 0x181c(r1)
	addi r3, r1, 0x140
	lwz r0, 0x700(r31)
	addi r4, r1, 0x128
	stw r27, 0x1818(r1)
	addi r5, r1, 0x18
	lwz r11, 0x708(r31)
	lfd f0, 0x1818(r1)
	stw r6, 0x134(r1)
	fsubs f0, f0, f22
	lwz r10, 0x70c(r31)
	stw r0, 0x138(r1)
	lwz r9, 0x710(r31)
	stfs f19, 0x134(r1)
	lwz r6, 0x0(r22)
	stfs f0, 0x138(r1)
	lwz r7, 0x134(r1)
	lwz r0, 0x138(r1)
	stw r26, 0x18(r1)
	stw r11, 0x128(r1)
	stw r10, 0x12c(r1)
	stw r9, 0x130(r1)
	stw r7, 0x140(r1)
	stw r0, 0x144(r1)
	stw r8, 0x148(r1)
	stw r8, 0x13c(r1)
	lwz r6, 0x0(r6)
	bl winFontSetLabel
	lwz r3, 0x0(r22)
	lwz r11, 0x184(r31)
	lbz r25, 0x12(r3)
	lwz r10, 0x188(r31)
	lwz r9, 0x18c(r31)
	cmpwi r25, 0x0
	lwz r8, 0x190(r31)
	lwz r7, 0x194(r31)
	lwz r6, 0x198(r31)
	lwz r5, 0x19c(r31)
	lwz r4, 0x1a0(r31)
	lwz r3, 0x1a4(r31)
	lwz r0, 0x1a8(r31)
	stw r11, 0x7cc(r1)
	stw r10, 0x7d0(r1)
	stw r9, 0x7d4(r1)
	stw r8, 0x7d8(r1)
	stw r7, 0x7dc(r1)
	stw r6, 0x7e0(r1)
	stw r5, 0x7e4(r1)
	stw r4, 0x7e8(r1)
	stw r3, 0x7ec(r1)
	stw r0, 0x7f0(r1)
	bge L_at66
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r25, r25
	b L_at67
	L_at66:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at67:
	mr r5, r25
	addi r3, r1, 0xa04
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	addi r20, r1, 0xa04
	li r19, 0x0
	b L_at68
	L_at69:
	lbz r0, 0x0(r20)
	mr r3, r29
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r28, r0
	bl strcat
	addi r20, r20, 0x1
	addi r19, r19, 0x1
	L_at68:
	addi r3, r1, 0xa04
	bl strlen
	cmplw r19, r3
	blt L_at69
	mr r5, r29
	addi r3, r1, 0x7ac
	la r4, str_8041D63C(r0)
	crclr 6
	bl sprintf
	lwz r8, 0x720(r31)
	addi r3, r1, 0x7ac
	lwz r7, 0x724(r31)
	lwz r6, 0x728(r31)
	lwz r5, 0x714(r31)
	lwz r4, 0x718(r31)
	lwz r0, 0x71c(r31)
	stw r26, 0x14(r1)
	stw r8, 0x104(r1)
	stw r7, 0x108(r1)
	stw r6, 0x10c(r1)
	stw r5, 0x110(r1)
	stw r4, 0x114(r1)
	stw r0, 0x118(r1)
	bl FontGetMessageWidth
	extrwi r0, r3, 15, 16
	xoris r7, r23, 0x8000
	xoris r3, r0, 0x8000
	lwz r0, 0x118(r1)
	stw r3, 0x181c(r1)
	addi r3, r1, 0x11c
	addi r4, r1, 0x104
	addi r5, r1, 0x14
	stw r27, 0x1818(r1)
	addi r6, r1, 0x7ac
	lfd f0, 0x1818(r1)
	stw r7, 0x1814(r1)
	fsubs f1, f0, f22
	stw r27, 0x1810(r1)
	lfd f0, 0x1810(r1)
	fsubs f1, f20, f1
	stw r0, 0x124(r1)
	fsubs f0, f0, f22
	stfs f1, 0x110(r1)
	stfs f0, 0x114(r1)
	lwz r7, 0x110(r1)
	lwz r0, 0x114(r1)
	stw r7, 0x11c(r1)
	stw r0, 0x120(r1)
	crclr 6
	bl winFontSet
	subfic r0, r21, 0x78
	lwz r8, 0x734(r31)
	xoris r0, r0, 0x8000
	lwz r7, 0x72c(r31)
	stw r0, 0x180c(r1)
	addi r3, r1, 0xf8
	lwz r0, 0x730(r31)
	addi r4, r1, 0xe0
	stw r27, 0x1808(r1)
	addi r5, r1, 0x10
	lwz r11, 0x738(r31)
	la r6, str_8041D6DC(r0)
	lfd f0, 0x1808(r1)
	stw r7, 0xec(r1)
	fsubs f0, f0, f22
	lwz r10, 0x73c(r31)
	stw r0, 0xf0(r1)
	lwz r9, 0x740(r31)
	stfs f21, 0xec(r1)
	stfs f0, 0xf0(r1)
	lwz r7, 0xec(r1)
	lwz r0, 0xf0(r1)
	stw r26, 0x10(r1)
	stw r11, 0xe0(r1)
	stw r10, 0xe4(r1)
	stw r9, 0xe8(r1)
	stw r8, 0xf4(r1)
	stw r7, 0xf8(r1)
	stw r0, 0xfc(r1)
	stw r8, 0x100(r1)
	crclr 6
	bl winFontSet
	addi r21, r21, 0x1a
	addi r22, r22, 0x4
	addi r24, r24, 0x1
	L_at64:
	lwz r0, 0x198(r30)
	cmpw r24, r0
	blt L_at65
	L_at63:
	li r0, 0x1938
	psq_lx f31, r1, r0, 0, 0
	lfd f31, 0x1930(r1)
	li r0, 0x1928
	psq_lx f30, r1, r0, 0, 0
	lfd f30, 0x1920(r1)
	li r0, 0x1918
	psq_lx f29, r1, r0, 0, 0
	lfd f29, 0x1910(r1)
	li r0, 0x1908
	psq_lx f28, r1, r0, 0, 0
	lfd f28, 0x1900(r1)
	li r0, 0x18f8
	psq_lx f27, r1, r0, 0, 0
	lfd f27, 0x18f0(r1)
	li r0, 0x18e8
	psq_lx f26, r1, r0, 0, 0
	lfd f26, 0x18e0(r1)
	li r0, 0x18d8
	psq_lx f25, r1, r0, 0, 0
	lfd f25, 0x18d0(r1)
	li r0, 0x18c8
	psq_lx f24, r1, r0, 0, 0
	lfd f24, 0x18c0(r1)
	li r0, 0x18b8
	psq_lx f23, r1, r0, 0, 0
	lfd f23, 0x18b0(r1)
	li r0, 0x18a8
	psq_lx f22, r1, r0, 0, 0
	lfd f22, 0x18a0(r1)
	li r0, 0x1898
	psq_lx f21, r1, r0, 0, 0
	lfd f21, 0x1890(r1)
	li r0, 0x1888
	psq_lx f20, r1, r0, 0, 0
	lfd f20, 0x1880(r1)
	li r0, 0x1878
	psq_lx f19, r1, r0, 0, 0
	lfd f19, 0x1870(r1)
	li r0, 0x1868
	psq_lx f18, r1, r0, 0, 0
	lfd f18, 0x1860(r1)
	lmw r19, 0x182c(r1)
	lwz r0, 0x1944(r1)
	mtlr r0
	addi r1, r1, 0x1940
	blr
}

asm void fukidashi(WinMarioWork* w, u32 idx, f32 x, f32 y) {
	nofralloc
	stwu r1, -0x300(r1)
	mflr r0
	stw r0, 0x304(r1)
	stfd f31, 0x2f0(r1)
	psq_st f31, 0x2f8(r1), 0, 0
	stfd f30, 0x2e0(r1)
	psq_st f30, 0x2e8(r1), 0, 0
	stw r31, 0x2dc(r1)
	stw r30, 0x2d8(r1)
	fmr f30, f1
	cmplwi r4, 0xa
	lis r5, str_802F5650@ha
	fmr f31, f2
	mr r30, r3
	addi r31, r5, str_802F5650@l
	bgt L_at1
	lis r3, jumptable_80374F08@ha
	slwi r0, r4, 2
	addi r3, r3, jumptable_80374F08@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_at2:
	bl pouchGetHammerLv
	cmpwi r3, 0x0
	ble L_at1
	bl pouchGetHammerLv
	lwz r4, 0x28(r30)
	mulli r6, r3, 0x28
	lis r5, itemDataTable@ha
	lwz r3, 0xa0(r4)
	addi r0, r5, itemDataTable@l
	add r4, r0, r6
	lwz r3, 0x0(r3)
	lhz r30, 0x160(r4)
	bl winTexInit
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x2
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x1
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	lfs f1, float_230_8041d6ec(r0)
	addi r4, r1, 0x26c
	lfs f0, float_72_8041d6f0(r0)
	addi r5, r1, 0x284
	fsubs f1, f30, f1
	lwz r8, 0x224(r31)
	lfs f2, float_5_8041d6cc(r0)
	fadds f31, f0, f31
	lwz r3, 0x21c(r31)
	addi r6, r1, 0x44
	lwz r0, 0x220(r31)
	fadds f1, f2, f1
	stw r3, 0x278(r1)
	fsubs f0, f31, f2
	lwz r12, dat_8041d5dc(r0)
	li r3, 0xb1
	stw r0, 0x27c(r1)
	lwz r11, 0x228(r31)
	stfs f1, 0x278(r1)
	lwz r10, 0x22c(r31)
	stfs f0, 0x27c(r1)
	lwz r9, 0x230(r31)
	lwz r7, 0x278(r1)
	lwz r0, 0x27c(r1)
	stw r12, 0x44(r1)
	stw r11, 0x284(r1)
	stw r10, 0x288(r1)
	stw r9, 0x28c(r1)
	stw r8, 0x280(r1)
	stw r7, 0x26c(r1)
	stw r0, 0x270(r1)
	stw r8, 0x274(r1)
	bl winTexSet
	lfs f0, float_230_8041d6ec(r0)
	addi r4, r1, 0x290
	lwz r3, 0x234(r31)
	addi r5, r1, 0x2a8
	lwz r0, 0x238(r31)
	fsubs f0, f30, f0
	stw r3, 0x29c(r1)
	addi r6, r1, 0x48
	lwz r8, 0x23c(r31)
	li r3, 0xb1
	stw r0, 0x2a0(r1)
	lwz r12, dat_8041d5e0(r0)
	stfs f0, 0x29c(r1)
	lwz r11, 0x240(r31)
	stfs f31, 0x2a0(r1)
	lwz r10, 0x244(r31)
	lwz r9, 0x248(r31)
	lwz r7, 0x29c(r1)
	lwz r0, 0x2a0(r1)
	stw r12, 0x48(r1)
	stw r11, 0x2a8(r1)
	stw r10, 0x2ac(r1)
	stw r9, 0x2b0(r1)
	stw r8, 0x2a4(r1)
	stw r7, 0x290(r1)
	stw r0, 0x294(r1)
	stw r8, 0x298(r1)
	bl winTexSet
	bl winIconInit
	lfs f0, float_230_8041d6ec(r0)
	mr r3, r30
	lwz r8, 0x254(r31)
	addi r4, r1, 0x2b4
	fsubs f1, f30, f0
	lfs f0, float_6_8041d6f4(r0)
	lwz r7, 0x24c(r31)
	addi r5, r1, 0x2cc
	lwz r0, 0x250(r31)
	addi r6, r1, 0x4c
	stw r0, 0x2c4(r1)
	fsubs f0, f1, f0
	lwz r12, dat_8041d5e4(r0)
	stw r7, 0x2c0(r1)
	lwz r11, 0x258(r31)
	stfs f0, 0x2c0(r1)
	lwz r10, 0x25c(r31)
	stfs f31, 0x2c4(r1)
	lwz r9, 0x260(r31)
	lwz r7, 0x2c0(r1)
	lwz r0, 0x2c4(r1)
	stw r12, 0x4c(r1)
	stw r11, 0x2cc(r1)
	stw r10, 0x2d0(r1)
	stw r9, 0x2d4(r1)
	stw r8, 0x2c8(r1)
	stw r7, 0x2b4(r1)
	stw r0, 0x2b8(r1)
	stw r8, 0x2bc(r1)
	bl winIconSet
	b L_at1
	L_at3:
	bl pouchGetJumpLv
	cmpwi r3, 0x0
	ble L_at1
	bl pouchGetJumpLv
	lwz r4, 0x28(r30)
	mulli r6, r3, 0x28
	lis r5, itemDataTable@ha
	lwz r3, 0xa0(r4)
	addi r0, r5, itemDataTable@l
	add r4, r0, r6
	lwz r3, 0x0(r3)
	lhz r30, 0xe8(r4)
	bl winTexInit
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x2
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x1
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	lfs f1, float_210_8041d6f8(r0)
	addi r4, r1, 0x200
	lfs f0, float_20_8041d628(r0)
	addi r5, r1, 0x218
	fsubs f1, f30, f1
	lwz r8, 0x224(r31)
	lfs f2, float_5_8041d6cc(r0)
	fadds f31, f0, f31
	lwz r3, 0x21c(r31)
	addi r6, r1, 0x38
	lwz r0, 0x220(r31)
	fadds f1, f2, f1
	stw r3, 0x20c(r1)
	fsubs f0, f31, f2
	lwz r12, dat_8041d5dc(r0)
	li r3, 0xb1
	stw r0, 0x210(r1)
	lwz r11, 0x228(r31)
	stfs f1, 0x20c(r1)
	lwz r10, 0x22c(r31)
	stfs f0, 0x210(r1)
	lwz r9, 0x230(r31)
	lwz r7, 0x20c(r1)
	lwz r0, 0x210(r1)
	stw r12, 0x38(r1)
	stw r11, 0x218(r1)
	stw r10, 0x21c(r1)
	stw r9, 0x220(r1)
	stw r8, 0x214(r1)
	stw r7, 0x200(r1)
	stw r0, 0x204(r1)
	stw r8, 0x208(r1)
	bl winTexSet
	lfs f0, float_210_8041d6f8(r0)
	addi r4, r1, 0x224
	lwz r3, 0x234(r31)
	addi r5, r1, 0x23c
	lwz r0, 0x238(r31)
	fsubs f0, f30, f0
	stw r3, 0x230(r1)
	addi r6, r1, 0x3c
	lwz r8, 0x23c(r31)
	li r3, 0xb1
	stw r0, 0x234(r1)
	lwz r12, dat_8041d5e0(r0)
	stfs f0, 0x230(r1)
	lwz r11, 0x240(r31)
	stfs f31, 0x234(r1)
	lwz r10, 0x244(r31)
	lwz r9, 0x248(r31)
	lwz r7, 0x230(r1)
	lwz r0, 0x234(r1)
	stw r12, 0x3c(r1)
	stw r11, 0x23c(r1)
	stw r10, 0x240(r1)
	stw r9, 0x244(r1)
	stw r8, 0x238(r1)
	stw r7, 0x224(r1)
	stw r0, 0x228(r1)
	stw r8, 0x22c(r1)
	bl winTexSet
	bl winIconInit
	lfs f0, float_210_8041d6f8(r0)
	mr r3, r30
	lwz r8, 0x254(r31)
	addi r4, r1, 0x248
	fsubs f1, f30, f0
	lfs f0, float_6_8041d6f4(r0)
	lwz r7, 0x24c(r31)
	addi r5, r1, 0x260
	lwz r0, 0x250(r31)
	addi r6, r1, 0x40
	stw r0, 0x258(r1)
	fsubs f0, f1, f0
	lwz r12, dat_8041d5e4(r0)
	stw r7, 0x254(r1)
	lwz r11, 0x258(r31)
	stfs f0, 0x254(r1)
	lwz r10, 0x25c(r31)
	stfs f31, 0x258(r1)
	lwz r9, 0x260(r31)
	lwz r7, 0x254(r1)
	lwz r0, 0x258(r1)
	stw r12, 0x40(r1)
	stw r11, 0x260(r1)
	stw r10, 0x264(r1)
	stw r9, 0x268(r1)
	stw r8, 0x25c(r1)
	stw r7, 0x248(r1)
	stw r0, 0x24c(r1)
	stw r8, 0x250(r1)
	bl winIconSet
	b L_at1
	L_at4:
	li r3, 0x2
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq L_at1
	lwz r3, 0x28(r30)
	lis r4, itemDataTable@ha
	addi r4, r4, itemDataTable@l
	lwz r3, 0xa0(r3)
	lhz r30, 0x70(r4)
	lwz r3, 0x0(r3)
	bl winTexInit
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x2
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x1
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	lfs f1, float_80_8041d68c(r0)
	addi r4, r1, 0x194
	lfs f0, float_90_8041d6d8(r0)
	addi r5, r1, 0x1ac
	fsubs f1, f30, f1
	lwz r8, 0x1dc(r31)
	lfs f2, float_5_8041d6cc(r0)
	fadds f31, f0, f31
	lwz r3, 0x1d4(r31)
	addi r6, r1, 0x2c
	lwz r0, 0x1d8(r31)
	fadds f1, f2, f1
	stw r3, 0x1a0(r1)
	fsubs f0, f31, f2
	lwz r12, dat_8041d5d0(r0)
	li r3, 0xb1
	stw r0, 0x1a4(r1)
	lwz r11, 0x1e0(r31)
	stfs f1, 0x1a0(r1)
	lwz r10, 0x1e4(r31)
	stfs f0, 0x1a4(r1)
	lwz r9, 0x1e8(r31)
	lwz r7, 0x1a0(r1)
	lwz r0, 0x1a4(r1)
	stw r12, 0x2c(r1)
	stw r11, 0x1ac(r1)
	stw r10, 0x1b0(r1)
	stw r9, 0x1b4(r1)
	stw r8, 0x1a8(r1)
	stw r7, 0x194(r1)
	stw r0, 0x198(r1)
	stw r8, 0x19c(r1)
	bl winTexSet
	lfs f0, float_80_8041d68c(r0)
	addi r4, r1, 0x1b8
	lwz r3, 0x1ec(r31)
	addi r5, r1, 0x1d0
	lwz r0, 0x1f0(r31)
	fsubs f0, f30, f0
	stw r3, 0x1c4(r1)
	addi r6, r1, 0x30
	lwz r8, 0x1f4(r31)
	li r3, 0xb1
	stw r0, 0x1c8(r1)
	lwz r12, dat_8041d5d4(r0)
	stfs f0, 0x1c4(r1)
	lwz r11, 0x1f8(r31)
	stfs f31, 0x1c8(r1)
	lwz r10, 0x1fc(r31)
	lwz r9, 0x200(r31)
	lwz r7, 0x1c4(r1)
	lwz r0, 0x1c8(r1)
	stw r12, 0x30(r1)
	stw r11, 0x1d0(r1)
	stw r10, 0x1d4(r1)
	stw r9, 0x1d8(r1)
	stw r8, 0x1cc(r1)
	stw r7, 0x1b8(r1)
	stw r0, 0x1bc(r1)
	stw r8, 0x1c0(r1)
	bl winTexSet
	bl winIconInit
	lfs f0, float_80_8041d68c(r0)
	mr r3, r30
	lwz r8, 0x20c(r31)
	addi r4, r1, 0x1dc
	fsubs f0, f30, f0
	lfs f1, float_6_8041d6f4(r0)
	lwz r7, 0x204(r31)
	addi r5, r1, 0x1f4
	lwz r0, 0x208(r31)
	addi r6, r1, 0x34
	stw r0, 0x1ec(r1)
	fadds f0, f1, f0
	lwz r12, dat_8041d5d8(r0)
	stw r7, 0x1e8(r1)
	lwz r11, 0x210(r31)
	stfs f0, 0x1e8(r1)
	lwz r10, 0x214(r31)
	stfs f31, 0x1ec(r1)
	lwz r9, 0x218(r31)
	lwz r7, 0x1e8(r1)
	lwz r0, 0x1ec(r1)
	stw r12, 0x34(r1)
	stw r11, 0x1f4(r1)
	stw r10, 0x1f8(r1)
	stw r9, 0x1fc(r1)
	stw r8, 0x1f0(r1)
	stw r7, 0x1dc(r1)
	stw r0, 0x1e0(r1)
	stw r8, 0x1e4(r1)
	bl winIconSet
	b L_at1
	L_at5:
	li r3, 0x4
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq L_at1
	lwz r3, 0x28(r30)
	lis r4, itemDataTable@ha
	addi r4, r4, itemDataTable@l
	lwz r3, 0xa0(r3)
	lhz r30, 0xc0(r4)
	lwz r3, 0x0(r3)
	bl winTexInit
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x2
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x1
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	lfs f1, float_80_8041d68c(r0)
	addi r4, r1, 0x128
	lfs f0, float_20_8041d628(r0)
	addi r5, r1, 0x140
	fsubs f1, f30, f1
	lwz r8, 0x1dc(r31)
	lfs f2, float_5_8041d6cc(r0)
	fadds f31, f0, f31
	lwz r3, 0x1d4(r31)
	addi r6, r1, 0x20
	lwz r0, 0x1d8(r31)
	fadds f1, f2, f1
	stw r3, 0x134(r1)
	fsubs f0, f31, f2
	lwz r12, dat_8041d5d0(r0)
	li r3, 0xb1
	stw r0, 0x138(r1)
	lwz r11, 0x1e0(r31)
	stfs f1, 0x134(r1)
	lwz r10, 0x1e4(r31)
	stfs f0, 0x138(r1)
	lwz r9, 0x1e8(r31)
	lwz r7, 0x134(r1)
	lwz r0, 0x138(r1)
	stw r12, 0x20(r1)
	stw r11, 0x140(r1)
	stw r10, 0x144(r1)
	stw r9, 0x148(r1)
	stw r8, 0x13c(r1)
	stw r7, 0x128(r1)
	stw r0, 0x12c(r1)
	stw r8, 0x130(r1)
	bl winTexSet
	lfs f0, float_80_8041d68c(r0)
	addi r4, r1, 0x14c
	lwz r3, 0x1ec(r31)
	addi r5, r1, 0x164
	lwz r0, 0x1f0(r31)
	fsubs f0, f30, f0
	stw r3, 0x158(r1)
	addi r6, r1, 0x24
	lwz r8, 0x1f4(r31)
	li r3, 0xb1
	stw r0, 0x15c(r1)
	lwz r12, dat_8041d5d4(r0)
	stfs f0, 0x158(r1)
	lwz r11, 0x1f8(r31)
	stfs f31, 0x15c(r1)
	lwz r10, 0x1fc(r31)
	lwz r9, 0x200(r31)
	lwz r7, 0x158(r1)
	lwz r0, 0x15c(r1)
	stw r12, 0x24(r1)
	stw r11, 0x164(r1)
	stw r10, 0x168(r1)
	stw r9, 0x16c(r1)
	stw r8, 0x160(r1)
	stw r7, 0x14c(r1)
	stw r0, 0x150(r1)
	stw r8, 0x154(r1)
	bl winTexSet
	bl winIconInit
	lfs f0, float_80_8041d68c(r0)
	mr r3, r30
	lwz r8, 0x20c(r31)
	addi r4, r1, 0x170
	fsubs f0, f30, f0
	lfs f1, float_6_8041d6f4(r0)
	lwz r7, 0x204(r31)
	addi r5, r1, 0x188
	lwz r0, 0x208(r31)
	addi r6, r1, 0x28
	stw r0, 0x180(r1)
	fadds f0, f1, f0
	lwz r12, dat_8041d5d8(r0)
	stw r7, 0x17c(r1)
	lwz r11, 0x210(r31)
	stfs f0, 0x17c(r1)
	lwz r10, 0x214(r31)
	stfs f31, 0x180(r1)
	lwz r9, 0x218(r31)
	lwz r7, 0x17c(r1)
	lwz r0, 0x180(r1)
	stw r12, 0x28(r1)
	stw r11, 0x188(r1)
	stw r10, 0x18c(r1)
	stw r9, 0x190(r1)
	stw r8, 0x184(r1)
	stw r7, 0x170(r1)
	stw r0, 0x174(r1)
	stw r8, 0x178(r1)
	bl winIconSet
	b L_at1
	L_at6:
	li r3, 0x5
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq L_at1
	lwz r3, 0x28(r30)
	lis r4, itemDataTable@ha
	addi r4, r4, itemDataTable@l
	lwz r3, 0xa0(r3)
	lhz r30, 0xe8(r4)
	lwz r3, 0x0(r3)
	bl winTexInit
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x2
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x1
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	lfs f1, float_30_8041d6fc(r0)
	addi r4, r1, 0xbc
	lfs f0, float_130_8041d680(r0)
	addi r5, r1, 0xd4
	fsubs f1, f30, f1
	lwz r8, 0x1dc(r31)
	lfs f2, float_5_8041d6cc(r0)
	fadds f31, f0, f31
	lwz r3, 0x1d4(r31)
	addi r6, r1, 0x14
	lwz r0, 0x1d8(r31)
	fadds f1, f2, f1
	stw r3, 0xc8(r1)
	fsubs f0, f31, f2
	lwz r12, dat_8041d5d0(r0)
	li r3, 0xb1
	stw r0, 0xcc(r1)
	lwz r11, 0x1e0(r31)
	stfs f1, 0xc8(r1)
	lwz r10, 0x1e4(r31)
	stfs f0, 0xcc(r1)
	lwz r9, 0x1e8(r31)
	lwz r7, 0xc8(r1)
	lwz r0, 0xcc(r1)
	stw r12, 0x14(r1)
	stw r11, 0xd4(r1)
	stw r10, 0xd8(r1)
	stw r9, 0xdc(r1)
	stw r8, 0xd0(r1)
	stw r7, 0xbc(r1)
	stw r0, 0xc0(r1)
	stw r8, 0xc4(r1)
	bl winTexSet
	lfs f0, float_30_8041d6fc(r0)
	addi r4, r1, 0xe0
	lwz r3, 0x1ec(r31)
	addi r5, r1, 0xf8
	lwz r0, 0x1f0(r31)
	fsubs f0, f30, f0
	stw r3, 0xec(r1)
	addi r6, r1, 0x18
	lwz r8, 0x1f4(r31)
	li r3, 0xb1
	stw r0, 0xf0(r1)
	lwz r12, dat_8041d5d4(r0)
	stfs f0, 0xec(r1)
	lwz r11, 0x1f8(r31)
	stfs f31, 0xf0(r1)
	lwz r10, 0x1fc(r31)
	lwz r9, 0x200(r31)
	lwz r7, 0xec(r1)
	lwz r0, 0xf0(r1)
	stw r12, 0x18(r1)
	stw r11, 0xf8(r1)
	stw r10, 0xfc(r1)
	stw r9, 0x100(r1)
	stw r8, 0xf4(r1)
	stw r7, 0xe0(r1)
	stw r0, 0xe4(r1)
	stw r8, 0xe8(r1)
	bl winTexSet
	bl winIconInit
	lfs f0, float_30_8041d6fc(r0)
	mr r3, r30
	lwz r8, 0x20c(r31)
	addi r4, r1, 0x104
	fsubs f0, f30, f0
	lfs f1, float_6_8041d6f4(r0)
	lwz r7, 0x204(r31)
	addi r5, r1, 0x11c
	lwz r0, 0x208(r31)
	addi r6, r1, 0x1c
	stw r0, 0x114(r1)
	fadds f0, f1, f0
	lwz r12, dat_8041d5d8(r0)
	stw r7, 0x110(r1)
	lwz r11, 0x210(r31)
	stfs f0, 0x110(r1)
	lwz r10, 0x214(r31)
	stfs f31, 0x114(r1)
	lwz r9, 0x218(r31)
	lwz r7, 0x110(r1)
	lwz r0, 0x114(r1)
	stw r12, 0x1c(r1)
	stw r11, 0x11c(r1)
	stw r10, 0x120(r1)
	stw r9, 0x124(r1)
	stw r8, 0x118(r1)
	stw r7, 0x104(r1)
	stw r0, 0x108(r1)
	stw r8, 0x10c(r1)
	bl winIconSet
	b L_at1
	L_at7:
	li r3, 0x3
	bl pouchCheckItem
	cmpwi r3, 0x0
	beq L_at1
	lwz r3, 0x28(r30)
	lis r4, itemDataTable@ha
	addi r4, r4, itemDataTable@l
	lwz r3, 0xa0(r3)
	lhz r30, 0x98(r4)
	lwz r3, 0x0(r3)
	bl winTexInit
	li r3, 0x0
	li r4, 0xf
	li r5, 0xf
	li r6, 0xf
	li r7, 0x2
	bl GXSetTevColorIn
	li r3, 0x0
	li r4, 0x7
	li r5, 0x1
	li r6, 0x4
	li r7, 0x7
	bl GXSetTevAlphaIn
	lfs f1, float_30_8041d6fc(r0)
	addi r4, r1, 0x50
	lfs f0, float_60_8041d700(r0)
	addi r5, r1, 0x68
	fsubs f1, f30, f1
	lwz r8, 0x1dc(r31)
	lfs f2, float_5_8041d6cc(r0)
	fadds f31, f0, f31
	lwz r3, 0x1d4(r31)
	addi r6, r1, 0x8
	lwz r0, 0x1d8(r31)
	fadds f1, f2, f1
	stw r3, 0x5c(r1)
	fsubs f0, f31, f2
	lwz r12, dat_8041d5d0(r0)
	li r3, 0xb1
	stw r0, 0x60(r1)
	lwz r11, 0x1e0(r31)
	stfs f1, 0x5c(r1)
	lwz r10, 0x1e4(r31)
	stfs f0, 0x60(r1)
	lwz r9, 0x1e8(r31)
	lwz r7, 0x5c(r1)
	lwz r0, 0x60(r1)
	stw r12, 0x8(r1)
	stw r11, 0x68(r1)
	stw r10, 0x6c(r1)
	stw r9, 0x70(r1)
	stw r8, 0x64(r1)
	stw r7, 0x50(r1)
	stw r0, 0x54(r1)
	stw r8, 0x58(r1)
	bl winTexSet
	lfs f0, float_30_8041d6fc(r0)
	addi r4, r1, 0x74
	lwz r3, 0x1ec(r31)
	addi r5, r1, 0x8c
	lwz r0, 0x1f0(r31)
	fsubs f0, f30, f0
	stw r3, 0x80(r1)
	addi r6, r1, 0xc
	lwz r8, 0x1f4(r31)
	li r3, 0xb1
	stw r0, 0x84(r1)
	lwz r12, dat_8041d5d4(r0)
	stfs f0, 0x80(r1)
	lwz r11, 0x1f8(r31)
	stfs f31, 0x84(r1)
	lwz r10, 0x1fc(r31)
	lwz r9, 0x200(r31)
	lwz r7, 0x80(r1)
	lwz r0, 0x84(r1)
	stw r12, 0xc(r1)
	stw r11, 0x8c(r1)
	stw r10, 0x90(r1)
	stw r9, 0x94(r1)
	stw r8, 0x88(r1)
	stw r7, 0x74(r1)
	stw r0, 0x78(r1)
	stw r8, 0x7c(r1)
	bl winTexSet
	bl winIconInit
	lfs f0, float_30_8041d6fc(r0)
	mr r3, r30
	lwz r8, 0x20c(r31)
	addi r4, r1, 0x98
	fsubs f0, f30, f0
	lfs f1, float_6_8041d6f4(r0)
	lwz r7, 0x204(r31)
	addi r5, r1, 0xb0
	lwz r0, 0x208(r31)
	addi r6, r1, 0x10
	stw r0, 0xa8(r1)
	fadds f0, f1, f0
	lwz r12, dat_8041d5d8(r0)
	stw r7, 0xa4(r1)
	lwz r11, 0x210(r31)
	stfs f0, 0xa4(r1)
	lwz r10, 0x214(r31)
	stfs f31, 0xa8(r1)
	lwz r9, 0x218(r31)
	lwz r7, 0xa4(r1)
	lwz r0, 0xa8(r1)
	stw r12, 0x10(r1)
	stw r11, 0xb0(r1)
	stw r10, 0xb4(r1)
	stw r9, 0xb8(r1)
	stw r8, 0xac(r1)
	stw r7, 0x98(r1)
	stw r0, 0x9c(r1)
	stw r8, 0xa0(r1)
	bl winIconSet
	L_at1:
	psq_l f31, 0x2f8(r1), 0, 0
	lfd f31, 0x2f0(r1)
	psq_l f30, 0x2e8(r1), 0, 0
	lfd f30, 0x2e0(r1)
	lwz r31, 0x2dc(r1)
	lwz r0, 0x304(r1)
	lwz r30, 0x2d8(r1)
	mtlr r0
	addi r1, r1, 0x300
	blr
}

asm char* unk_8016af5c(s32 n, s32 digits) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	lis r5, jumptable_802F57D4+0x28@ha
	stw r0, 0x144(r1)
	addi r12, r5, jumptable_802F57D4+0x28@l
	stw r31, 0x13c(r1)
	mr r31, r4
	stw r30, 0x138(r1)
	mr. r30, r3
	lwz r11, 0x0(r12)
	lwz r10, 0x4(r12)
	lwz r9, 0x8(r12)
	lwz r8, 0xc(r12)
	lwz r7, 0x10(r12)
	lwz r6, 0x14(r12)
	lwz r5, 0x18(r12)
	lwz r4, 0x1c(r12)
	lwz r3, 0x20(r12)
	lwz r0, 0x24(r12)
	stw r11, 0x8(r1)
	stw r10, 0xc(r1)
	stw r9, 0x10(r1)
	stw r8, 0x14(r1)
	stw r7, 0x18(r1)
	stw r6, 0x1c(r1)
	stw r5, 0x20(r1)
	stw r4, 0x24(r1)
	stw r3, 0x28(r1)
	stw r0, 0x2c(r1)
	bge L_at1
	lis r3, unk_803dfbf8@ha
	la r4, str_8041D630(r0)
	addi r3, r3, unk_803dfbf8@l
	bl strcpy
	neg r30, r30
	b L_at2
	L_at1:
	lis r3, unk_803dfbf8@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, unk_803dfbf8@l
	bl strcpy
	L_at2:
	mr r5, r30
	addi r3, r1, 0x30
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	li r30, 0x0
	b L_at3
	L_at4:
	addi r3, r1, 0x30
	bl strlen
	subf r0, r3, r31
	cmplw r30, r0
	bge L_at5
	lis r3, unk_803dfbf8@ha
	la r4, str_8041D5A8(r0)
	addi r3, r3, unk_803dfbf8@l
	bl strcat
	b L_at6
	L_at5:
	addi r3, r1, 0x30
	bl strlen
	subf r0, r3, r31
	lis r3, unk_803dfbf8@ha
	subf r0, r0, r30
	addi r4, r1, 0x30
	lbzx r0, r4, r0
	addi r4, r1, 0x8
	addi r3, r3, unk_803dfbf8@l
	extsb r0, r0
	slwi r5, r0, 2
	subi r0, r5, 0xc0
	lwzx r4, r4, r0
	bl strcat
	L_at6:
	addi r30, r30, 0x1
	L_at3:
	cmpw r30, r31
	blt L_at4
	lwz r0, 0x144(r1)
	lis r3, unk_803dfbf8@ha
	lwz r31, 0x13c(r1)
	addi r3, r3, unk_803dfbf8@l
	lwz r30, 0x138(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm const char* winZenkakuStr(s32 n) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	lis r4, jumptable_802F57D4@ha
	stw r0, 0x144(r1)
	addi r12, r4, jumptable_802F57D4@l
	stw r31, 0x13c(r1)
	stw r30, 0x138(r1)
	stw r29, 0x134(r1)
	stw r28, 0x130(r1)
	mr. r28, r3
	lwz r11, 0x0(r12)
	lwz r10, 0x4(r12)
	lwz r9, 0x8(r12)
	lwz r8, 0xc(r12)
	lwz r7, 0x10(r12)
	lwz r6, 0x14(r12)
	lwz r5, 0x18(r12)
	lwz r4, 0x1c(r12)
	lwz r3, 0x20(r12)
	lwz r0, 0x24(r12)
	stw r11, 0x8(r1)
	stw r10, 0xc(r1)
	stw r9, 0x10(r1)
	stw r8, 0x14(r1)
	stw r7, 0x18(r1)
	stw r6, 0x1c(r1)
	stw r5, 0x20(r1)
	stw r4, 0x24(r1)
	stw r3, 0x28(r1)
	stw r0, 0x2c(r1)
	bge L_at1
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, str_8041D630(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	neg r28, r28
	b L_at2
	L_at1:
	lis r3, (unk_803dfbf8+0x100)@ha
	la r4, float_0_8041d634(r0)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	bl strcpy
	L_at2:
	mr r5, r28
	addi r3, r1, 0x30
	la r4, str_8041D638(r0)
	crclr 6
	bl sprintf
	lis r3, (unk_803dfbf8+0x100)@ha
	addi r29, r1, 0x30
	addi r30, r3, (unk_803dfbf8+0x100)@l
	addi r31, r1, 0x8
	li r28, 0x0
	b L_at3
	L_at4:
	lbz r0, 0x0(r29)
	mr r3, r30
	extsb r0, r0
	slwi r4, r0, 2
	subi r0, r4, 0xc0
	lwzx r4, r31, r0
	bl strcat
	addi r29, r29, 0x1
	addi r28, r28, 0x1
	L_at3:
	addi r3, r1, 0x30
	bl strlen
	cmplw r28, r3
	blt L_at4
	lwz r0, 0x144(r1)
	lis r3, (unk_803dfbf8+0x100)@ha
	lwz r31, 0x13c(r1)
	addi r3, r3, (unk_803dfbf8+0x100)@l
	lwz r30, 0x138(r1)
	lwz r29, 0x134(r1)
	lwz r28, 0x130(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm void winMarioMain2(void) {
	nofralloc
	blr
}

asm s32 winMarioMain(WinMarioWork* w) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	mr r29, r3
	stw r28, 0x20(r1)
	lwz r0, 0x190(r3)
	cmpwi r0, 0x1
	beq L_at1
	bge L_at2
	cmpwi r0, 0x0
	bge L_at3
	b L_at2
	L_at3:
	lwz r3, 0x4(r29)
	rlwinm. r0, r3, 0, 23, 23
	beq L_at4
	lwz r0, 0x160(r29)
	cmpwi r0, 0xc
	bne L_at5
	li r0, 0x1
	lis r3, 0x2
	stw r0, 0x190(r29)
	li r0, 0x0
	addi r3, r3, 0x12
	stw r0, 0x194(r29)
	bl psndSFXOn
	b L_at5
	L_at4:
	rlwinm. r0, r3, 0, 22, 22
	beq L_at6
	lis r3, 0x2
	addi r3, r3, 0x13
	bl psndSFXOn
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 18, 18
	beq L_at7
	la r3, str_8041D580(r0)
	la r4, str_8041D580(r0)
	bl strcmp
	cmpwi r3, 0x0
	bne L_at8
	bl marioGetColor
	cmpwi r3, 0x2
	beq L_at9
	bge L_at10
	cmpwi r3, 0x0
	beq L_at11
	bge L_at12
	b L_at13
	L_at10:
	cmpwi r3, 0x4
	bge L_at13
	b L_at14
	L_at11:
	la r30, str_8041D580(r0)
	b L_at13
	L_at12:
	la r30, str_8041D704(r0)
	b L_at13
	L_at9:
	la r30, str_8041D708(r0)
	b L_at13
	L_at14:
	la r30, str_8041D70C(r0)
	b L_at13
	L_at8:
	bl marioGetColor
	cmpwi r3, 0x2
	beq L_at15
	bge L_at16
	cmpwi r3, 0x0
	beq L_at17
	bge L_at18
	b L_at13
	L_at16:
	cmpwi r3, 0x4
	bge L_at13
	b L_at19
	L_at17:
	la r30, str_8041D58C(r0)
	b L_at13
	L_at18:
	la r30, str_8041D710(r0)
	b L_at13
	L_at15:
	la r30, str_8041D718(r0)
	b L_at13
	L_at19:
	la r30, str_8041D720(r0)
	b L_at13
	L_at7:
	la r30, str_8041D578(r0)
	L_at13:
	lwz r3, 0x188(r29)
	mr r4, r30
	li r5, 0x0
	bl animPoseSetAnim
	li r3, -0x1
	b L_at20
	L_at6:
	rlwinm. r0, r3, 0, 19, 19
	beq L_at21
	li r3, -0x2
	b L_at20
	L_at21:
	lwz r3, 0x10(r29)
	rlwinm. r0, r3, 0, 19, 19
	beq L_at22
	lwz r0, 0x160(r29)
	lis r3, linkDt@ha
	addi r30, r3, linkDt@l
	mulli r0, r0, 0x1c
	add r3, r30, r0
	lbz r0, 0x18(r3)
	stw r0, 0x160(r29)
	lwz r0, 0x160(r29)
	mulli r0, r0, 0x1c
	add r28, r30, r0
	L_at23:
	lwz r0, 0x160(r29)
	cmpwi r0, 0xb
	beq L_at24
	cmpwi r0, 0xc
	bne L_at25
	L_at24:
	lwz r0, 0x198(r29)
	cmpwi r0, 0x0
	bne L_at26
	b L_at27
	L_at25:
	lhz r3, 0x10(r28)
	cmplwi r3, 0x0
	beq L_at26
	bl pouchCheckItem
	cmpwi r3, 0x0
	bne L_at26
	L_at27:
	lbz r0, 0x18(r28)
	stw r0, 0x160(r29)
	lwz r0, 0x160(r29)
	mulli r0, r0, 0x1c
	add r28, r30, r0
	b L_at23
	L_at26:
	lis r3, 0x2
	addi r3, r3, 0x5
	bl psndSFXOn
	b L_at5
	L_at22:
	rlwinm. r0, r3, 0, 18, 18
	beq L_at28
	lwz r0, 0x160(r29)
	lis r3, linkDt@ha
	addi r30, r3, linkDt@l
	mulli r0, r0, 0x1c
	add r3, r30, r0
	lbz r0, 0x19(r3)
	stw r0, 0x160(r29)
	lwz r0, 0x160(r29)
	mulli r0, r0, 0x1c
	add r28, r30, r0
	L_at29:
	lwz r0, 0x160(r29)
	cmpwi r0, 0xb
	beq L_at30
	cmpwi r0, 0xc
	bne L_at31
	L_at30:
	lwz r0, 0x198(r29)
	cmpwi r0, 0x0
	bne L_at32
	b L_at33
	L_at31:
	lhz r3, 0x10(r28)
	cmplwi r3, 0x0
	beq L_at32
	bl pouchCheckItem
	cmpwi r3, 0x0
	bne L_at32
	L_at33:
	lbz r0, 0x19(r28)
	stw r0, 0x160(r29)
	lwz r0, 0x160(r29)
	mulli r0, r0, 0x1c
	add r28, r30, r0
	b L_at29
	L_at32:
	lis r3, 0x2
	addi r3, r3, 0x5
	bl psndSFXOn
	b L_at5
	L_at28:
	rlwinm. r0, r3, 0, 17, 17
	beq L_at34
	lwz r0, 0x160(r29)
	lis r3, linkDt@ha
	addi r30, r3, linkDt@l
	mulli r0, r0, 0x1c
	add r3, r30, r0
	lbz r0, 0x1a(r3)
	stw r0, 0x160(r29)
	lwz r0, 0x160(r29)
	mulli r0, r0, 0x1c
	add r28, r30, r0
	L_at35:
	lwz r0, 0x160(r29)
	cmpwi r0, 0xb
	beq L_at36
	cmpwi r0, 0xc
	bne L_at37
	L_at36:
	lwz r0, 0x198(r29)
	cmpwi r0, 0x0
	bne L_at38
	b L_at39
	L_at37:
	lhz r3, 0x10(r28)
	cmplwi r3, 0x0
	beq L_at38
	bl pouchCheckItem
	cmpwi r3, 0x0
	bne L_at38
	L_at39:
	lbz r0, 0x1a(r28)
	stw r0, 0x160(r29)
	lwz r0, 0x160(r29)
	mulli r0, r0, 0x1c
	add r28, r30, r0
	b L_at35
	L_at38:
	lis r3, 0x2
	addi r3, r3, 0x5
	bl psndSFXOn
	b L_at5
	L_at34:
	rlwinm. r0, r3, 0, 16, 16
	beq L_at5
	lwz r0, 0x160(r29)
	lis r3, linkDt@ha
	addi r30, r3, linkDt@l
	mulli r0, r0, 0x1c
	add r3, r30, r0
	lbz r0, 0x1b(r3)
	stw r0, 0x160(r29)
	lwz r0, 0x160(r29)
	mulli r0, r0, 0x1c
	add r28, r30, r0
	L_at40:
	lwz r0, 0x160(r29)
	cmpwi r0, 0xb
	beq L_at41
	cmpwi r0, 0xc
	bne L_at42
	L_at41:
	lwz r0, 0x198(r29)
	cmpwi r0, 0x0
	bne L_at43
	b L_at44
	L_at42:
	lhz r3, 0x10(r28)
	cmplwi r3, 0x0
	beq L_at43
	bl pouchCheckItem
	cmpwi r3, 0x0
	bne L_at43
	L_at44:
	lbz r0, 0x1b(r28)
	stw r0, 0x160(r29)
	lwz r0, 0x160(r29)
	mulli r0, r0, 0x1c
	add r28, r30, r0
	b L_at40
	L_at43:
	lis r3, 0x2
	addi r3, r3, 0x5
	bl psndSFXOn
	L_at5:
	lwz r5, 0x160(r29)
	lis r0, 0x4330
	lis r4, linkDt@ha
	lis r3, double_to_int_802f5e78@ha
	mulli r5, r5, 0x1c
	stw r0, 0x8(r1)
	addi r4, r4, linkDt@l
	lfd f1, double_to_int_802f5e78@l(r3)
	stw r0, 0x10(r1)
	add r30, r4, r5
	lha r0, 0x0(r30)
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f1
	stfs f0, 0x158(r29)
	lha r0, 0x2(r30)
	xoris r0, r0, 0x8000
	stw r0, 0x14(r1)
	lfd f0, 0x10(r1)
	fsubs f0, f0, f1
	stfs f0, 0x15c(r29)
	lwz r0, 0x160(r29)
	cmpwi r0, 0x2
	beq L_at45
	b L_at46
	L_at45:
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 18, 18
	beq L_at47
	lwz r3, 0xc(r30)
	la r4, str_8041D580(r0)
	bl strcmp
	cmpwi r3, 0x0
	bne L_at48
	bl marioGetColor
	cmpwi r3, 0x2
	beq L_at49
	bge L_at50
	cmpwi r3, 0x0
	beq L_at51
	bge L_at52
	b L_at53
	L_at50:
	cmpwi r3, 0x4
	bge L_at53
	b L_at54
	L_at51:
	la r31, str_8041D580(r0)
	b L_at53
	L_at52:
	la r31, str_8041D704(r0)
	b L_at53
	L_at49:
	la r31, str_8041D708(r0)
	b L_at53
	L_at54:
	la r31, str_8041D70C(r0)
	b L_at53
	L_at48:
	bl marioGetColor
	cmpwi r3, 0x2
	beq L_at55
	bge L_at56
	cmpwi r3, 0x0
	beq L_at57
	bge L_at58
	b L_at53
	L_at56:
	cmpwi r3, 0x4
	bge L_at53
	b L_at59
	L_at57:
	la r31, str_8041D58C(r0)
	b L_at53
	L_at58:
	la r31, str_8041D710(r0)
	b L_at53
	L_at55:
	la r31, str_8041D718(r0)
	b L_at53
	L_at59:
	la r31, str_8041D720(r0)
	b L_at53
	L_at47:
	bl pouchGetHammerLv
	slwi r0, r3, 2
	la r3, hammer_pose(r0)
	lwzx r31, r3, r0
	L_at53:
	lwz r3, 0x188(r29)
	mr r4, r31
	li r5, 0x0
	bl animPoseSetAnim
	lwz r3, 0x18c(r29)
	cmpwi r3, 0x0
	bne L_at60
	lwz r3, 0x188(r29)
	bl animPoseGetLoopTimes
	lfs f0, float_0p89_8041d728(r0)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne L_at61
	li r0, 0x1e
	stw r0, 0x18c(r29)
	b L_at61
	L_at60:
	subi r0, r3, 0x1
	stw r0, 0x18c(r29)
	L_at61:
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 18, 18
	beq L_at62
	li r0, 0x0
	stw r0, 0x18c(r29)
	b L_at62
	L_at46:
	li r0, 0x0
	stw r0, 0x18c(r29)
	lhz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 18, 18
	beq L_at63
	lwz r3, 0xc(r30)
	la r4, str_8041D580(r0)
	bl strcmp
	cmpwi r3, 0x0
	bne L_at64
	bl marioGetColor
	cmpwi r3, 0x2
	beq L_at65
	bge L_at66
	cmpwi r3, 0x0
	beq L_at67
	bge L_at68
	b L_at69
	L_at66:
	cmpwi r3, 0x4
	bge L_at69
	b L_at70
	L_at67:
	la r31, str_8041D580(r0)
	b L_at69
	L_at68:
	la r31, str_8041D704(r0)
	b L_at69
	L_at65:
	la r31, str_8041D708(r0)
	b L_at69
	L_at70:
	la r31, str_8041D70C(r0)
	b L_at69
	L_at64:
	bl marioGetColor
	cmpwi r3, 0x2
	beq L_at71
	bge L_at72
	cmpwi r3, 0x0
	beq L_at73
	bge L_at74
	b L_at69
	L_at72:
	cmpwi r3, 0x4
	bge L_at69
	b L_at75
	L_at73:
	la r31, str_8041D58C(r0)
	b L_at69
	L_at74:
	la r31, str_8041D710(r0)
	b L_at69
	L_at71:
	la r31, str_8041D718(r0)
	b L_at69
	L_at75:
	la r31, str_8041D720(r0)
	b L_at69
	L_at63:
	lwz r31, 0x4(r30)
	L_at69:
	lwz r3, 0x188(r29)
	mr r4, r31
	li r5, 0x0
	bl animPoseSetAnim
	L_at62:
	lwz r0, 0x160(r29)
	cmpwi r0, 0x3
	beq L_at76
	bge L_at77
	cmpwi r0, 0x2
	bge L_at78
	b L_at77
	L_at78:
	bl pouchGetHammerLv
	slwi r0, r3, 2
	la r3, hammer_help(r0)
	lwzx r5, r3, r0
	mr r3, r29
	li r4, 0x0
	li r6, 0x0
	bl winMsgEntry
	b L_at2
	L_at76:
	bl pouchGetJumpLv
	slwi r0, r3, 2
	la r3, boots_help(r0)
	lwzx r5, r3, r0
	mr r3, r29
	li r4, 0x0
	li r6, 0x0
	bl winMsgEntry
	b L_at2
	L_at77:
	lwz r5, 0x14(r30)
	mr r3, r29
	li r4, 0x0
	li r6, 0x0
	bl winMsgEntry
	b L_at2
	L_at1:
	lwz r3, 0x10(r29)
	rlwinm. r0, r3, 0, 19, 19
	beq L_at79
	lwz r3, 0x194(r29)
	subi r0, r3, 0x1
	stw r0, 0x194(r29)
	lwz r0, 0x194(r29)
	cmpwi r0, 0x0
	bge L_at80
	lwz r3, 0x198(r29)
	subi r0, r3, 0x1
	stw r0, 0x194(r29)
	L_at80:
	lis r3, 0x2
	addi r3, r3, 0x5
	bl psndSFXOn
	b L_at81
	L_at79:
	rlwinm. r0, r3, 0, 18, 18
	beq L_at82
	lwz r3, 0x194(r29)
	addi r0, r3, 0x1
	stw r0, 0x194(r29)
	lwz r3, 0x194(r29)
	lwz r0, 0x198(r29)
	cmpw r3, r0
	blt L_at83
	li r0, 0x0
	stw r0, 0x194(r29)
	L_at83:
	lis r3, 0x2
	addi r3, r3, 0x5
	bl psndSFXOn
	b L_at81
	L_at82:
	lwz r3, 0x4(r29)
	rlwinm. r0, r3, 0, 22, 22
	beq L_at84
	li r0, 0x0
	lis r3, 0x2
	stw r0, 0x190(r29)
	addi r3, r3, 0x13
	bl psndSFXOn
	b L_at81
	L_at84:
	rlwinm. r0, r3, 0, 19, 19
	beq L_at81
	li r3, -0x2
	b L_at20
	L_at81:
	lfs f0, float_neg280_8041d72c(r0)
	lis r0, 0x4330
	lis r4, double_to_int_802f5e78@ha
	lis r3, superActionTable@ha
	stfs f0, 0x158(r29)
	addi r5, r3, superActionTable@l
	lfd f3, double_to_int_802f5e78@l(r4)
	mr r3, r29
	lwz r6, 0x194(r29)
	li r4, 0x0
	stw r0, 0x10(r1)
	xoris r0, r6, 0x8000
	lfs f4, float_26_8041d734(r0)
	stw r0, 0x14(r1)
	li r6, 0x0
	lfs f1, float_120_8041d730(r0)
	lfd f2, 0x10(r1)
	lfs f0, float_12_8041d670(r0)
	fsubs f2, f2, f3
	lfs f3, float_10_8041d61c(r0)
	fnmsubs f1, f4, f2, f1
	fsubs f0, f1, f0
	fadds f0, f3, f0
	stfs f0, 0x15c(r29)
	lwz r0, 0x194(r29)
	slwi r0, r0, 2
	lwzx r5, r5, r0
	lwz r5, 0xc(r5)
	bl winMsgEntry
	L_at2:
	li r3, 0x0
	L_at20:
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	lwz r28, 0x20(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void winMarioExit(WinMarioWork* w) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, 0x188(r3)
	bl animPoseRelease
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void winMarioInit2(WinMarioWork* w) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, linkDt@ha
	stw r0, 0x24(r1)
	li r0, 0x0
	addi r4, r4, linkDt@l
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r0, 0x160(r3)
	lis r0, 0x4330
	lis r3, double_to_int_802f5e78@ha
	lwz r5, 0x160(r31)
	stw r0, 0x8(r1)
	mulli r5, r5, 0x1c
	lfd f1, double_to_int_802f5e78@l(r3)
	stw r0, 0x10(r1)
	lhax r0, r4, r5
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f1
	stfs f0, 0x158(r31)
	stfs f0, 0x158(r31)
	lwz r0, 0x160(r31)
	mulli r0, r0, 0x1c
	add r3, r4, r0
	lha r0, 0x2(r3)
	xoris r0, r0, 0x8000
	stw r0, 0x14(r1)
	lfd f0, 0x10(r1)
	fsubs f0, f0, f1
	stfs f0, 0x15c(r31)
	stfs f0, 0x15c(r31)
	lwz r0, 0x160(r31)
	cmpwi r0, 0x3
	beq L_at1
	bge L_at2
	cmpwi r0, 0x2
	bge L_at3
	b L_at2
	L_at3:
	bl pouchGetHammerLv
	slwi r0, r3, 2
	la r3, hammer_help(r0)
	lwzx r5, r3, r0
	mr r3, r31
	li r4, 0x0
	li r6, 0x0
	bl winMsgEntry
	b L_at4
	L_at1:
	bl pouchGetJumpLv
	slwi r0, r3, 2
	la r3, boots_help(r0)
	lwzx r5, r3, r0
	mr r3, r31
	li r4, 0x0
	li r6, 0x0
	bl winMsgEntry
	b L_at4
	L_at2:
	mulli r0, r0, 0x1c
	lis r4, linkDt@ha
	mr r3, r31
	addi r4, r4, linkDt@l
	add r5, r4, r0
	li r4, 0x0
	lwz r5, 0x14(r5)
	li r6, 0x0
	bl winMsgEntry
	L_at4:
	li r0, 0x0
	stw r0, 0x18c(r31)
	stw r0, 0x190(r31)
	stw r0, 0x194(r31)
	lwz r31, 0x1c(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void winMarioInit(WinMarioWork* w) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, str_802F5650@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	addi r30, r4, str_802F5650@l
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	bl pouchGetPtr
	lhz r0, 0x0(r28)
	mr r31, r3
	rlwinm. r0, r0, 0, 18, 18
	beq L_at1
	la r29, str_8041D580(r0)
	bl marioGetColor
	cmpwi r3, 0x2
	beq L_at2
	bge L_at3
	cmpwi r3, 0x0
	beq L_at4
	bge L_at5
	b L_at6
	L_at3:
	cmpwi r3, 0x4
	bge L_at6
	b L_at7
	L_at4:
	la r29, str_8041D580(r0)
	b L_at6
	L_at5:
	la r29, str_8041D704(r0)
	b L_at6
	L_at2:
	la r29, str_8041D708(r0)
	b L_at6
	L_at7:
	la r29, str_8041D70C(r0)
	L_at6:
	addi r3, r30, 0x830
	li r4, 0x0
	bl animPoseEntry
	stw r3, 0x188(r28)
	mr r4, r29
	li r5, 0x1
	lwz r3, 0x188(r28)
	bl animPoseSetAnim
	b L_at8
	L_at1:
	addi r29, r30, 0x838
	bl marioGetColor
	cmpwi r3, 0x2
	beq L_at9
	bge L_at10
	cmpwi r3, 0x0
	beq L_at11
	bge L_at12
	b L_at11
	L_at10:
	cmpwi r3, 0x4
	bge L_at11
	b L_at13
	b L_at11
	L_at12:
	addi r29, r30, 0x840
	b L_at11
	L_at9:
	addi r29, r30, 0x84c
	b L_at11
	L_at13:
	addi r29, r30, 0x858
	L_at11:
	mr r3, r29
	li r4, 0x0
	bl animPoseEntry
	stw r3, 0x188(r28)
	la r4, str_8041D578(r0)
	li r5, 0x1
	lwz r3, 0x188(r28)
	bl animPoseSetAnim
	L_at8:
	lwz r3, 0x188(r28)
	li r4, 0x1800
	bl animPoseSetMaterialFlagOn
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 1, 1
	beq L_at14
	lwz r3, 0x188(r28)
	lis r4, 0xa00
	bl animPoseSetMaterialFlagOn
	L_at14:
	li r3, 0x0
	li r0, 0x0
	stw r3, 0x18c(r28)
	li r4, 0x1
	slw r0, r4, r0
	stw r3, 0x190(r28)
	stw r3, 0x194(r28)
	stw r3, 0x198(r28)
	lhz r3, 0x8c(r31)
	and. r0, r3, r0
	beq L_at15
	lwz r3, 0x198(r28)
	addi r0, r3, 0x1
	stw r0, 0x198(r28)
	L_at15:
	li r0, 0x1
	lhz r3, 0x8c(r31)
	slw r0, r4, r0
	and. r0, r3, r0
	beq L_at16
	lwz r3, 0x198(r28)
	addi r0, r3, 0x1
	stw r0, 0x198(r28)
	L_at16:
	li r0, 0x2
	lhz r3, 0x8c(r31)
	slw r0, r4, r0
	and. r0, r3, r0
	beq L_at17
	lwz r3, 0x198(r28)
	addi r0, r3, 0x1
	stw r0, 0x198(r28)
	L_at17:
	li r0, 0x3
	lhz r3, 0x8c(r31)
	slw r0, r4, r0
	and. r0, r3, r0
	beq L_at18
	lwz r3, 0x198(r28)
	addi r0, r3, 0x1
	stw r0, 0x198(r28)
	L_at18:
	li r0, 0x4
	lhz r3, 0x8c(r31)
	slw r0, r4, r0
	and. r0, r3, r0
	beq L_at19
	lwz r3, 0x198(r28)
	addi r0, r3, 0x1
	stw r0, 0x198(r28)
	L_at19:
	li r0, 0x5
	lhz r3, 0x8c(r31)
	slw r0, r4, r0
	and. r0, r3, r0
	beq L_at20
	lwz r3, 0x198(r28)
	addi r0, r3, 0x1
	stw r0, 0x198(r28)
	L_at20:
	li r0, 0x6
	lhz r3, 0x8c(r31)
	slw r0, r4, r0
	and. r0, r3, r0
	beq L_at21
	lwz r3, 0x198(r28)
	addi r0, r3, 0x1
	stw r0, 0x198(r28)
	L_at21:
	li r0, 0x7
	lhz r3, 0x8c(r31)
	slw r0, r4, r0
	and. r0, r3, r0
	beq L_at22
	lwz r3, 0x198(r28)
	addi r0, r3, 0x1
	stw r0, 0x198(r28)
	L_at22:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}
// clang-format on
#endif
#pragma force_active on
#pragma explicit_zero_data on
__declspec(section ".data") u32 gap_05_80374F34_data[1] = {0};
#pragma explicit_zero_data reset
