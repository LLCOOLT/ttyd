#include "win/win_main.h"
#include "data/item_data.h"
#include "driver/animdrv.h"
#include "mario/mario.h"
#include "mario/mario_pouch.h"
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
    u8 pad_2C[0x158 - 0x2C];      // 0x2C
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
    u8 pad[0xC];
    const char* desc;
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
        strcat(tmp2, tbl[buf[i] - '0']);
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
            strcat(unk_803dfbf8, tbl[buf[i - (digits - strlen(buf))] - '0']);
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
