#include "win/win_main.h"
#include "driver/animdrv.h"
#include "driver/effdrv.h"
#include "driver/swdrv.h"
#include "manager/filemgr.h"
#include "memory.h"
#include <string.h>
#include "battle/battle_monosiri.h"
#include "driver/dispdrv.h"
#include "mario/mariost.h"
#include "sdk/texPalette.h"
#include "mario/mario_pouch.h"
#include "data/item_data.h"
#include "manager/evtmgr_cmd.h"
#include <dolphin/gx.h>

typedef struct TubuDt {
    s16 x;
    s16 y;
    u8 big;
    u8 type;
    u16 id;
    const char* map;
} TubuDt;

typedef struct MonosiriWork {
    s32 state;          // 0x0
    s32 id;             // 0x4
    FileEntry* file1;   // 0x8
    FileEntry* file2;   // 0xC
    f32 curX;           // 0x10
    f32 curY;           // 0x14
    f32 x;              // 0x18
    f32 y;              // 0x1C
    s32 pose1;          // 0x20
    s32 pose2;          // 0x24
    smartEntry* smart;  // 0x28
    s32 alpha;          // 0x2C
} MonosiriWork;

typedef struct WinLogPage {
    f32 x;       // 0x0
    f32 tx;      // 0x4
    f32 y;       // 0x8
    f32 ty;      // 0xC
    s32 num;     // 0x10
    s32 cursor;  // 0x14
    s32 idx;     // 0x18
    f32 f1C;     // 0x1C
    f32 tf1C;    // 0x20
    f32 f24;     // 0x24
    f32 tf24;    // 0x28
    f32 f2C;     // 0x2C
    f32 tf2C;    // 0x30
} WinLogPage;

typedef struct WinLogMenu {
    s32 id;           // 0x0
    f32 x;            // 0x4
    f32 y;            // 0x8
    f32 tx;           // 0xC
    f32 ty;           // 0x10
    s32 state;        // 0x14
    s32 timer;        // 0x18
    const char* msg;  // 0x1C
} WinLogMenu;

typedef struct WinLogEnemy {
    u8 sort;
    u8 id;
} WinLogEnemy;

typedef struct WinLogTex {
    TEXPalette* tpl;
} WinLogTex;

typedef struct WinLogRes {
    u8 pad_0[0xA0];
    WinLogTex* tex;  // 0xA0
} WinLogRes;

typedef struct WinLogPos {
    f32 x;
    f32 y;
    u8 pad_8[0xC];
} WinLogPos;

typedef struct WinLogWork {
    u16 flags;                // 0x0
    u8 pad_2[2];
    u32 trg;                  // 0x4
    u32 rep;                  // 0x8
    u32 dtrg;                 // 0xC
    u32 drep;                 // 0x10
    u8 pad_14[0x28 - 0x14];
    WinLogRes* res;           // 0x28
    u8 pad_2c[0x30 - 0x2C];
    FileEntry* file;          // 0x30
    u8 pad_34[0xC4 - 0x34];
    WinLogPos pos[3];         // 0xC4
    u8 pad_100[0x124 - 0x100];
    s32 saved;                // 0x124
    u8 pad_128[0x158 - 0x128];
    f32 msgX;                 // 0x158
    f32 msgY;                 // 0x15C
    u8 pad_160[0x188 - 0x160];
    s32 f188;                 // 0x188
    u8 pad_18c[0xD68 - 0x18C];
    s32 fD68;                 // 0xD68
    s32 cursor;               // 0xD6C
    s32 count;                // 0xD70
    WinLogMenu menu[5];       // 0xD74
    s32 fE14;                 // 0xE14
    s32 mapIdx;               // 0xE18
    s32 pose;                 // 0xE1C
    f32 mapX;                 // 0xE20
    f32 mapY;                 // 0xE24
    f32 fE28;                 // 0xE28
    f32 fE2C;                 // 0xE2C
    f32 fE30;                 // 0xE30
    f32 fE34;                 // 0xE34
    f32 scrollX;              // 0xE38
    f32 scrollY;              // 0xE3C
    s32 stoneNum;             // 0xE40
    EffectEntry* eff[7];      // 0xE44
    s32 fE60;                 // 0xE60
    f32 fE64;                 // 0xE64
    f32 fE68;                 // 0xE68
    f32 fE6C;                 // 0xE6C
    f32 fE70;                 // 0xE70
    f32 fE74;                 // 0xE74
    f32 fE78;                 // 0xE78
    f32 fE7C;                 // 0xE7C
    f32 fE80;                 // 0xE80
    WinLogPage page0;         // 0xE84
    u16 list0[100];           // 0xEB8
    WinLogPage page1;         // 0xF80
    u16 list1[58];            // 0xFB4
    f32 f1028;                // 0x1028
    f32 f102C;                // 0x102C
    f32 f1030;                // 0x1030
    f32 f1034;                // 0x1034
    s32 enemyNum;             // 0x1038
    s32 enemyKnown;           // 0x103C
    s32 f1040;                // 0x1040
    s32 f1044;                // 0x1044
    f32 f1048;                // 0x1048
    f32 f104C;                // 0x104C
    WinLogEnemy enemy[0xD8];  // 0x1050
    MonosiriWork* mono;       // 0x1200
} WinLogWork;

typedef struct EffStarStoneWork {
    s32 type;
    u16 flags;  // 0x4
    u8 pad_6[0x8 - 0x6];
    f32 x, y, z;  // 0x8
    u8 pad_14[0x38 - 0x14];
    s32 cam;    // 0x38
    u8 pad_3c[0x5C - 0x3C];
    u8 r, g, b, a;  // 0x5C
} EffStarStoneWork;

EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
void qqsort(void* base, u32 n, u32 size, int (*compare)(void*, void*));
int compare_func5_2(void* a, void* b);
int compare_func6_2(void* a, void* b);
extern u8 enemy_monoshiri_sort_table[];
extern ItemData itemDataTable[];

void winMsgEntry(void* wp, s32 a, const char* msg, const char* b);
void capture(CameraId camera, void* param);
void monosiri_disp(CameraId camera, void* param);

TubuDt tubuDt[] = {
    {14, -34, 1, 0, 3, "gor"},
    {-4, -31, 0, 2, 12, "gor"},
    {-20, -31, 0, 2, 12, "gor"},
    {-33, -38, 1, 2, 12, "tik"},
    {118, 30, 1, 0, 23, "hei"},
    {134, 22, 0, 0, 26, "hei"},
    {150, 14, 0, 0, 26, "hei"},
    {176, 9, 0, 0, 26, "hei"},
    {200, 6, 1, 0, 26, "nok"},
    {136, 39, 0, 3, 35, "hei"},
    {152, 48, 0, 3, 35, "hei"},
    {165, 53, 0, 3, 35, "hei"},
    {165, 68, 1, 3, 35, "gon"},
    {0, 36, 1, 0, 71, "win"},
    {0, 56, 0, 0, 74, "win"},
    {0, 75, 1, 0, 74, "mri"},
    {16, 44, 0, 0, 81, "win"},
    {27, 53, 0, 0, 81, "win"},
    {42, 65, 1, 0, 81, "hou"},
    {30, -17, 0, 0, 127, "gor"},
    {36, 0, 0, 0, 127, "gor"},
    {46, 15, 0, 0, 127, "gor"},
    {55, 32, 0, 0, 127, "gor"},
    {74, 45, 0, 0, 127, "gor"},
    {83, 61, 0, 0, 127, "gor"},
    {83, 75, 0, 0, 127, "gor"},
    {83, 93, 0, 0, 127, "gor"},
    {72, 101, 0, 0, 127, "gor"},
    {71, 114, 0, 0, 127, "gor"},
    {71, 132, 0, 0, 127, "gor"},
    {80, 141, 0, 0, 127, "gor"},
    {97, 150, 1, 0, 127, "tou"},
    {-181, -90, 1, 0, 178, "usu"},
    {-163, -90, 0, 4, 184, "usu"},
    {-145, -90, 0, 4, 184, "usu"},
    {-135, -77, 0, 4, 184, "usu"},
    {-143, -63, 0, 4, 184, "usu"},
    {-159, -63, 0, 4, 184, "usu"},
    {-176, -63, 0, 4, 184, "usu"},
    {-191, -63, 0, 4, 184, "usu"},
    {-206, -63, 0, 4, 184, "usu"},
    {-228, -63, 1, 4, 184, "gra"},
    {-228, -44, 0, 0, 193, "gra"},
    {-216, -31, 0, 0, 193, "gra"},
    {-198, -27, 0, 0, 193, "gra"},
    {-181, -29, 0, 0, 193, "gra"},
    {-160, -33, 0, 0, 193, "gra"},
    {-139, -33, 1, 0, 193, "jin"},
    {13, -56, 0, 0, 232, "gor"},
    {13, -70, 0, 0, 232, "gor"},
    {12, -84, 0, 0, 232, "gor"},
    {-3, -94, 0, 0, 232, "gor"},
    {-14, -104, 0, 0, 232, "gor"},
    {-31, -115, 0, 0, 232, "gor"},
    {-45, -128, 0, 0, 232, "gor"},
    {-48, -143, 0, 0, 232, "gor"},
    {-38, -158, 0, 0, 232, "gor"},
    {-11, -163, 1, 0, 232, "muj"},
    {7, -163, 0, 0, 243, "muj"},
    {21, -163, 0, 0, 243, "muj"},
    {41, -163, 1, 0, 243, "dou"},
    {36, -34, 0, 0, 310, "gor"},
    {53, -27, 0, 0, 310, "gor"},
    {69, -12, 0, 0, 310, "gor"},
    {85, 1, 0, 0, 310, "gor"},
    {109, 7, 0, 0, 310, "gor"},
    {132, 4, 0, 0, 310, "gor"},
    {149, -8, 0, 0, 310, "gor"},
    {158, -25, 1, 0, 310, "eki"},
    {143, -40, 0, 0, 334, "eki"},
    {133, -52, 0, 0, 334, "eki"},
    {132, -66, 0, 0, 334, "eki"},
    {132, -82, 0, 0, 334, "eki"},
    {155, -90, 1, 0, 334, "pik"},
    {175, -90, 0, 0, 336, "pik"},
    {193, -91, 0, 0, 336, "pik"},
    {211, -91, 1, 0, 336, "sin"},
    {-167, 17, 1, 0, 353, "bom"},
    {-167, 37, 0, 0, 358, "bom"},
    {-167, 50, 0, 0, 358, "bom"},
    {-167, 64, 0, 0, 358, "bom"},
    {-167, 82, 0, 0, 358, "bom"},
    {-167, 99, 0, 0, 358, "bom"},
    {-167, 116, 0, 0, 358, "bom"},
    {-167, 133, 0, 0, 358, "bom"},
    {-167, 151, 1, 0, 358, "moo"},
    {-171, 169, 0, 0, 361, "moo"},
    {-185, 177, 0, 0, 361, "moo"},
    {-200, 171, 0, 0, 361, "moo"},
    {-209, 159, 1, 0, 361, "aji"},
    {-33, -50, 0, 0, 382, "gor"},
    {-33, -62, 0, 0, 382, "gor"},
    {-33, -74, 1, 0, 382, "las"},
};

s32 stone_tbl[] = {0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78};

static inline void winLogAddMenu(WinLogWork* w, s32 id) {
    static const char* msg_help[] = {
        "msg_menu_kiroku_map",
        "msg_menu_kiroku_stone",
        "msg_menu_kiroku_badge",
        "msg_menu_kiroku_ryori",
        "msg_menu_kiroku_mono",
    };
    WinLogMenu* m = &w->menu[w->count];
    s32 i;
    m->id = id;
    m->timer = 0;
    m->state = 0;
    m->msg = msg_help[id];
    w->count++;
    for (i = 0; i < w->count; i++) {
        w->menu[i].x = 0.0f;
        w->menu[i].tx = 0.0f;
        w->menu[i].ty = w->menu[i].y = 45.0f * w->count / 2.0f - 45.0f * i;
    }
}

void winLogInit(WinLogWork* w) {
    u32 k;
    const char* area;
    s32 i;
    s32 j;
    TattleEntry* t;
    EffectEntry* e;
    WinLogEnemy tmp;

    w->fD68 = 0;
    w->cursor = 0;
    w->count = 0;
    winLogAddMenu(w, 0);
    if (swByteGet(0) >= 0x13) winLogAddMenu(w, 1);
    if (swByteGet(0) >= 7) winLogAddMenu(w, 4);
    if (swByteGet(0) >= 0x14) winLogAddMenu(w, 2);
    if (swGet(0x40)) winLogAddMenu(w, 3);

    w->stoneNum = 0;
    for (i = 0; i < 7; i++) {
        if (((s32 (*)(s32))pouchCheckItem)(stone_tbl[i])) {
            w->stoneNum++;
        }
    }
    for (i = 0; i < 7; i++) {
        if (i < w->stoneNum) {
            e = effStarStoneEntry(i, 0.0f, -1000.0f, 0.0f, 2.0f);
            w->eff[i] = e;
        } else {
            e = effStarStoneEntry(i + 7, 0.0f, -1000.0f, 0.0f, 2.0f);
            w->eff[i] = e;
            ((EffStarStoneWork*)e->userdata)->r = 0x20;
            ((EffStarStoneWork*)e->userdata)->g = 0x20;
            ((EffStarStoneWork*)e->userdata)->b = 0x20;
        }
        ((EffStarStoneWork*)e->userdata)->cam = 8;
        ((EffStarStoneWork*)e->userdata)->flags &= ~4;
        ((EffStarStoneWork*)e->userdata)->flags |= 0x20;
    }

    w->file = NULL;
    w->pose = -1;
    w->fE14 = -1;
    w->mapIdx = 0;
    w->mapX = w->mapY = 0.0f;
    w->fE28 = w->fE2C = 0.0f;
    w->fE30 = w->fE34 = -480.0f;
    w->scrollX = w->scrollY = 0.0f;

    area = gp->currentAreaName;
    if (!strcmp(gp->currentMapName, "pik_02") || !strcmp(gp->currentMapName, "pik_03")) area = "sin";
    if (!strcmp(gp->currentMapName, "win_04") || !strcmp(gp->currentMapName, "win_05")) area = "hou";
    if (!strncmp(gp->currentMapName, "rsh", 3)) {
        if (swByteGet(0) < 0x136) {
            area = "gor";
        } else if (swByteGet(0) < 0x14E || swGet(0xDFB)) {
            area = "eki";
        } else if (swGet(0xDFC)) {
            area = "pik";
        } else {
            switch (swByteGet(0x366)) {
            case 0:
                area = "gor";
                break;
            case 1:
                area = "eki";
                break;
            case 2:
                area = "pik";
                break;
            case 3:
                area = "gor";
                break;
            }
        }
    }
    if (!strncmp(gp->currentMapName, "hom", 3)) area = "eki";
    if (!strncmp(gp->currentMapName, "jon", 3)) area = "tik";
    if (!strcmp(gp->currentMapName, "gra_06")) area = "jin";
    if (!strcmp(gp->currentMapName, "muj_10") || !strcmp(gp->currentMapName, "muj_11") || !strcmp(gp->currentMapName, "muj_12\0")) area = "dou";

    {
        for (k = 0; k < 93; k++) {
            if (!area || !strcmp(area, tubuDt[k].map)) break;
        }
        if (k < 93) w->mapIdx = k;
    }
    w->mapX = 304.0f + tubuDt[w->mapIdx].x;
    w->mapY = 240.0f + tubuDt[w->mapIdx].y;
    {
        s32 dx = w->mapX + w->scrollX - 230.0f;
        s32 dy = w->mapY + w->scrollY - 120.0f;
        w->scrollX -= dx;
        w->scrollY -= dy;
    }
    if (w->scrollX > 0.0f) w->scrollX = 0.0f;
    if (w->scrollY > 0.0f) w->scrollY = 0.0f;
    if (w->scrollX < -148.0f) w->scrollX = -148.0f;
    if (w->scrollY < -240.0f) w->scrollY = -240.0f;

    w->fE60 = 0;
    w->fE80 = w->fE7C = 51.42857f * w->fE60;
    w->fE64 = w->fE68 = 0.0f;
    w->fE6C = w->fE70 = -480.0f;
    w->fE74 = w->fE78 = 0.0f;

    w->page0.num = 0;
    for (i = 0xF0; i < 0x153; i++) {
        if (itemDataTable[i].type_sort_order != -1) {
            w->list0[w->page0.num++] = i - 0xF0;
        }
    }
    qqsort(w->list0, w->page0.num, 2, compare_func5_2);
    w->page0.cursor = 0;
    w->page0.x = w->page0.tx = 320.0f;
    w->page0.y = w->page0.ty = -240.0f;
    w->page0.idx = 0;
    w->page0.f1C = w->page0.tf1C = 0.0f;
    w->page0.f24 = w->page0.tf24 = -200.0f;
    w->page0.f2C = w->page0.tf2C = -300.0f;

    w->page1.num = 0;
    for (i = 0xB3; i < 0xEC; i++) {
        if (itemDataTable[i].type_sort_order != -1) {
            w->list1[w->page1.num++] = i - 0xB3;
        }
    }
    qqsort(w->list1, w->page1.num, 2, compare_func6_2);
    w->page1.cursor = 0;
    w->page1.x = w->page1.tx = 320.0f;
    w->page1.y = w->page1.ty = -240.0f;
    w->page1.idx = 0;
    w->page1.f1C = w->page1.tf1C = 0.0f;
    w->page1.f24 = w->page1.tf24 = -200.0f;
    w->page1.f2C = w->page1.tf2C = -300.0f;

    w->enemyNum = 0;
    for (i = 1; i < 0xD8; i++) {
        t = battleGetUnitMonosiriPtr(i);
        if (!t->tattleLogTag) continue;
        if (evtGetValue(NULL, 0xF5DE0180) < 0x187) {
            if (i == 0x85 || i == 0x86 || i == 0x87) continue;
        } else {
            if (i == 0x1F || i == 0x20 || i == 0x4D) continue;
        }
        if (evtGetValue(NULL, 0xF5DE0180) < 0x190) {
            if (i == 0x90) continue;
        } else {
            if (i == 0x3F) continue;
        }
        w->enemy[w->enemyNum].sort = enemy_monoshiri_sort_table[i];
        w->enemy[w->enemyNum++].id = i;
    }
    for (i = 0; i < w->enemyNum - 1; i++) {
        for (j = i + 1; j < w->enemyNum; j++) {
            if (w->enemy[i].sort > w->enemy[j].sort) {
                tmp = w->enemy[i];
                w->enemy[i] = w->enemy[j];
                w->enemy[j] = tmp;
            }
        }
    }
    w->f1040 = 0;
    w->f1028 = w->f102C = 0.0f;
    w->f1030 = w->f1034 = 0.0f;
    w->f1044 = 0;
    w->f1048 = w->f104C = 0.0f;
    w->enemyKnown = 0;
    for (i = 1; i < 0xD8; i++) {
        t = battleGetUnitMonosiriPtr(i);
        if (!t->tattleLogTag) continue;
        if (i == 0x1F || i == 0x20 || i == 0x4D || i == 0x3F) continue;
        if (swGet(i + 0x117A)) {
            w->enemyKnown++;
        }
    }
}

void winLogInit2(WinLogWork* w) {
    w->msgX = -128.0f;
    w->msgY = 8.0f + (45.0f * w->count / 2.0f - 45.0f * w->cursor);
    w->page0.x = w->page0.tx = 320.0f;
    w->page0.y = w->page0.ty = -240.0f;
    w->page0.f1C = w->page0.tf1C = w->page0.idx * 0xE8;
    w->page0.f24 = w->page0.tf24 = -200.0f;
    w->page0.f2C = w->page0.tf2C = -300.0f;
    w->page1.x = w->page1.tx = 320.0f;
    w->page1.y = w->page1.ty = -240.0f;
    w->page1.f1C = w->page1.tf1C = w->page1.idx * 0xE8;
    w->page1.f24 = w->page1.tf24 = -200.0f;
    w->page1.f2C = w->page1.tf2C = -300.0f;
    winMsgEntry(w, 0, w->menu[w->cursor].msg, 0);
}

void winLogExit(WinLogWork* w) {
    s32 i;
    if (w->file) {
        fileFree(w->file);
        w->file = NULL;
    }
    if (w->pose != -1) {
        animPoseRelease(w->pose);
        w->pose = -1;
    }
    for (i = 0; i < 7; i++) {
        effSoftDelete(w->eff[i]);
    }
}

static inline BOOL tubuCheck(u8 type) {
    switch (type) {
    case 0:
        return FALSE;
    case 1:
        if (swGet(0xFD)) return TRUE;
        break;
    case 2:
        if (swGet(0xFE)) return TRUE;
        break;
    case 3:
        if (swGet(0xFF)) return TRUE;
        break;
    case 4:
        if (swGet(0x100)) return TRUE;
        break;
    }
    return FALSE;
}

void winSortEntry(WinLogWork* w, s32 a, f32 x, f32 y);
s32 winSortWait(WinLogWork* w);
MonosiriWork* monosiriInit(s32 id, f32 x, f32 y);
void monosiriMain(MonosiriWork* m);
void monosiriClose(MonosiriWork* m);
BOOL monosiriCloseWait(MonosiriWork* m);
void monosiriExit(MonosiriWork* m);
const char* winGetMapTplName(void);
f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
s8 keyGetStickX(u32 chan);
s8 keyGetStickY(u32 chan);
u32 keyGetButton(u32 chan);

s32 winLogMain(WinLogWork* w) {
    static char name[0x40];
    static char help[0x40];
    s32 i;
    s32 sel;
    TubuDt* t;
    s32 pages;
    s32 old;
    u32 k;
    const char* anim;
    const char* model;
    f32 min;
    f32 x;
    f32 y;
    f32 bx;
    f32 by;
    f32 dx;
    f32 dy;
    s32 ix;
    s32 iy;

    switch (w->fD68) {
    case 0:
        if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            return -1;
        }
        if (w->trg & 0x1000) {
            return -2;
        }
        if (w->drep & 0x2000) {
            old = w->cursor;
            w->cursor++;
            if (w->cursor >= w->count) w->cursor = 0;
            if (old != w->cursor) psndSFXOn(0x20005);
        } else if (w->drep & 0x1000) {
            old = w->cursor;
            w->cursor--;
            if (w->cursor < 0) w->cursor = w->count - 1;
            if (old != w->cursor) psndSFXOn(0x20005);
        } else if (w->trg & 0x100) {
            for (i = 0; i < w->count; i++) {
                w->menu[i].state = 30;
            }
            w->menu[w->cursor].state = 10;
            w->fD68 = w->menu[w->cursor].id + 10;
            switch (w->menu[w->cursor].id) {
            case 0:
                w->fE30 = 20.0f;
                break;
            case 1:
                w->fE6C = 20.0f;
                w->fE74 = 255.0f;
                break;
            case 2:
                w->page0.tx = -130.0f;
                w->page0.ty = 120.0f;
                w->page0.tf24 = -200.0f;
                w->page0.tf2C = 60.0f;
                break;
            case 3:
                w->page1.tx = -130.0f;
                w->page1.ty = 120.0f;
                w->page1.tf24 = -200.0f;
                w->page1.tf2C = 60.0f;
                break;
            case 4:
                break;
            }
            psndSFXOn(0x20012);
        }
        w->msgX = -128.0f;
        w->msgY = 8.0f + (45.0f * w->count / 2.0f - 45.0f * w->cursor);
        winMsgEntry(w, 0, w->menu[w->cursor].msg, 0);
        break;
    case 10:
        if (!((void* (*)(u8, FileCallback, const char*, ...))fileAsyncf)(4, NULL, "%s/w/jp/%s", getMarioStDvdRoot(), winGetMapTplName())) break;
        if (!w->file) {
            w->file = fileAllocf(4, "%s/w/jp/%s", getMarioStDvdRoot(), winGetMapTplName());
        }
        if (w->pose == -1) {
            if (w->flags & 0x2000) {
                anim = "W_1";
                w->pose = animPoseEntry("d_mario", 0);
                switch (marioGetColor()) {
                case 0:
                    anim = "W_1";
                    break;
                case 1:
                    anim = "W_15";
                    break;
                case 2:
                    anim = "W_17";
                    break;
                case 3:
                    anim = "W_18";
                    break;
                }
                animPoseSetAnim(w->pose, anim, 1);
            } else {
                model = "a_mario";
                switch (marioGetColor()) {
                case 0:
                    model = "a_mario";
                    break;
                case 1:
                    model = "a_mario_l";
                    break;
                case 2:
                    model = "a_mario_w";
                    break;
                case 3:
                    model = "a_mario_wl";
                    break;
                }
                w->pose = animPoseEntry(model, 0);
                animPoseSetAnim(w->pose, "M_W_1", 1);
            }
            animPoseSetMaterialFlagOn(w->pose, 0x1800);
        }
        if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            for (i = 0; i < w->count; i++) {
                w->menu[i].state = 40;
            }
            w->menu[w->cursor].state = 20;
            w->fD68 = 0;
            w->fE30 = -480.0f;
            fileFree(w->file);
            w->file = NULL;
            if (w->pose != -1) animPoseRelease(w->pose);
            w->pose = -1;
        } else if (w->trg & 0x1000) {
            return -2;
        }
        min = 10000.0f;
        x = -230.0f + w->scrollX + w->mapX;
        y = -120.0f + w->scrollY + w->mapY;
        bx = 74.0f + w->scrollX;
        by = 120.0f + w->scrollY;
        for (k = 0; k < 0x5D; k++) {
            t = &tubuDt[k];
            if (swByteGet(0) >= t->id || tubuCheck(t->type)) {
                if (t->big) {
                    f32 d = distABf(bx + t->x, by + t->y, x, y);
                    if (min > d) {
                        min = d;
                        sel = k;
                    }
                }
            }
        }
        if (min < 50.0f) {
            sprintf(name, "menu_monosiri_%s", tubuDt[sel].map);
            sprintf(help, "menu_map_%s", tubuDt[sel].map);
            if (w->fE14 != sel) psndSFXOn(0x20035);
            w->fE14 = sel;
            winMsgEntry(w, 0, help, name);
        } else {
            w->fE14 = -1;
            winMsgEntry(w, 0, "msg_menu_kiroku_map", 0);
        }
        dx = keyGetStickX(0) / 8.0f;
        dy = keyGetStickY(0) / 8.0f;
        if (dx == 0.0f && dy == 0.0f) {
            if (keyGetButton(0) & 1) {
                dx = -8.0f;
            } else if (keyGetButton(0) & 2) {
                dx = 8.0f;
            }
            if (keyGetButton(0) & 8) {
                dy = 8.0f;
            } else if (keyGetButton(0) & 4) {
                dy = -8.0f;
            }
        }
        if (dx == 0.0f && dy == 0.0f && w->fE14 != -1) {
            dx = 304.0f + tubuDt[w->fE14].x - w->mapX;
            dy = 240.0f + tubuDt[w->fE14].y - w->mapY;
            dx *= 0.2f;
            dy *= 0.2f;
        }
        w->mapX += dx;
        w->mapY += dy;
        if (w->mapX < 16.0f) w->mapX = 16.0f;
        if (w->mapY < 8.0f) w->mapY = 8.0f;
        if (w->mapX >= 604.0f) w->mapX = 604.0f;
        if (w->mapY >= 468.0f) w->mapY = 468.0f;
        ix = w->mapX + w->scrollX - 230.0f;
        iy = w->mapY + w->scrollY - 120.0f;
        if (ix >= 166.0f) w->scrollX -= ix - 166.0f;
        if (ix <= -150.0f) w->scrollX -= 150.0f + ix;
        if (iy >= 80.0f) w->scrollY -= iy - 80.0f;
        if (iy <= -80.0f) w->scrollY -= 80.0f + iy;
        if (w->scrollX > 0.0f) w->scrollX = 0.0f;
        if (w->scrollY > 0.0f) w->scrollY = 0.0f;
        if (w->scrollX < -148.0f) w->scrollX = -148.0f;
        if (w->scrollY < -240.0f) w->scrollY = -240.0f;
        w->msgX = -230.0f + w->scrollX + w->mapX;
        w->msgY = -120.0f + w->scrollY + w->mapY;
        w->msgX -= 24.0f;
        w->msgY += 20.0f;
        break;
    case 11:
        if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            for (i = 0; i < w->count; i++) {
                w->menu[i].state = 40;
            }
            w->menu[w->cursor].state = 20;
            w->fD68 = 0;
            w->fE6C = -480.0f;
            w->fE74 = 0.0f;
        } else if (w->drep & 0x4000) {
            w->fE60--;
            while (w->fE60 < 0) w->fE60 += 7;
            w->fE7C = 51.42857f * w->fE60;
            while (w->fE80 < w->fE7C) w->fE80 += 360.0f;
            psndSFXOn(0x209D6);
            psndSFXOn(0x20037);
        } else if (w->drep & 0x8000) {
            w->fE60++;
            while (w->fE60 > 6) w->fE60 -= 7;
            w->fE7C = 51.42857f * w->fE60;
            while (w->fE80 > w->fE7C) w->fE80 -= 360.0f;
            psndSFXOn(0x209D6);
            psndSFXOn(0x20037);
        } else if (w->trg & 0x1000) {
            return -2;
        }
        w->msgY = w->msgX = -50.0f;
        if (w->fE60 < w->stoneNum) {
            winMsgEntry(w, -1, itemDataTable[stone_tbl[w->fE60]].description, itemDataTable[stone_tbl[w->fE60]].name);
        } else {
            winMsgEntry(w, -1, "msg_menu_stone_none_help", "msg_menu_stone_none_name");
        }
        break;
    case 12:
        pages = (w->page0.num + 27) / 28;
        if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            for (i = 0; i < w->count; i++) {
                w->menu[i].state = 40;
            }
            w->menu[w->cursor].state = 20;
            w->fD68 = 0;
            w->page0.tx = 330.0f;
            w->page0.ty = -250.0f;
            w->page0.tf24 = -200.0f;
            w->page0.tf2C = -300.0f;
        } else if (w->rep & 0x40) {
            w->page0.idx--;
            if (w->page0.idx < 0) w->page0.idx = 0;
            w->page0.cursor = w->page0.idx * 28;
            psndSFXOn(0x20035);
        } else if (w->rep & 0x20) {
            w->page0.idx++;
            if (w->page0.idx >= pages) w->page0.idx = pages - 1;
            w->page0.cursor = w->page0.idx * 28;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x8000) {
            if (w->page0.cursor % 7 < 6 && w->page0.cursor + 1 < w->page0.num) w->page0.cursor++;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x4000) {
            if (w->page0.cursor % 7 > 0) w->page0.cursor--;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x1000) {
            if ((s32)(w->page0.cursor - 7) >= 0 && w->page0.cursor - 7 < w->page0.num) { w->page0.cursor -= 7; }
            w->page0.idx = w->page0.cursor / 28;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x2000) {
            if ((s32)(w->page0.cursor + 7) >= 0 && w->page0.cursor + 7 < w->page0.num) {
                w->page0.cursor += 7;
            } else if (w->page0.cursor + (7 - w->page0.cursor % 7) < w->page0.num) {
                w->page0.cursor = w->page0.num - 1;
            }
            w->page0.idx = w->page0.cursor / 28;
            psndSFXOn(0x20035);
        } else if (w->trg & 0x10) {
            winSortEntry(w, 4, -310.0f, 150.0f);
            w->saved = w->fD68;
            psndSFXOn(0x20012);
            w->fD68 = 1000;
        } else if (w->trg & 0x1000) {
            return -2;
        }
        w->msgX = w->page0.cursor % 28 % 7 * 56 - 140;
        w->msgY = 90 - w->page0.cursor % 28 / 7 * 56;
        if (swGet(((s16*)w->list0)[w->page0.cursor] + 0x80)) {
            winMsgEntry(w, -2, itemDataTable[((s16*)w->list0)[w->page0.cursor] + 0xF0].menu_description, itemDataTable[((s16*)w->list0)[w->page0.cursor] + 0xF0].name);
        } else {
            winMsgEntry(w, -2, "msg_menu_stone_none_help", "msg_menu_stone_none_name");
        }
        break;
    case 13:
        pages = (w->page1.num + 27) / 28;
        if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            for (i = 0; i < w->count; i++) {
                w->menu[i].state = 40;
            }
            w->menu[w->cursor].state = 20;
            w->fD68 = 0;
            w->page1.tx = 330.0f;
            w->page1.ty = -250.0f;
            w->page1.tf24 = -200.0f;
            w->page1.tf2C = -300.0f;
        } else if (w->rep & 0x40) {
            w->page1.idx--;
            if (w->page1.idx < 0) w->page1.idx = 0;
            w->page1.cursor = w->page1.idx * 28;
            psndSFXOn(0x20035);
        } else if (w->rep & 0x20) {
            w->page1.idx++;
            if (w->page1.idx >= pages) w->page1.idx = pages - 1;
            w->page1.cursor = w->page1.idx * 28;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x8000) {
            if (w->page1.cursor % 7 < 6 && w->page1.cursor + 1 < w->page1.num) w->page1.cursor++;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x4000) {
            if (w->page1.cursor % 7 > 0) w->page1.cursor--;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x1000) {
            if ((s32)(w->page1.cursor - 7) >= 0 && w->page1.cursor - 7 < w->page1.num) { w->page1.cursor -= 7; }
            w->page1.idx = w->page1.cursor / 28;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x2000) {
            if ((s32)(w->page1.cursor + 7) >= 0 && w->page1.cursor + 7 < w->page1.num) {
                w->page1.cursor += 7;
            } else if (w->page1.cursor + (7 - w->page1.cursor % 7) < w->page1.num) {
                w->page1.cursor = w->page1.num - 1;
            }
            w->page1.idx = w->page1.cursor / 28;
            psndSFXOn(0x20035);
        } else if (w->trg & 0x10) {
            winSortEntry(w, 5, -310.0f, 150.0f);
            w->saved = w->fD68;
            psndSFXOn(0x20012);
            w->fD68 = 1000;
        } else if (w->trg & 0x1000) {
            return -2;
        }
        w->msgX = w->page1.cursor % 28 % 7 * 56 - 140;
        w->msgY = 90 - w->page1.cursor % 28 / 7 * 56;
        if (swGet(((s16*)w->list1)[w->page1.cursor] + 0x41)) {
            winMsgEntry(w, -2, itemDataTable[((s16*)w->list1)[w->page1.cursor] + 0xB3].menu_description, itemDataTable[((s16*)w->list1)[w->page1.cursor] + 0xB3].name);
        } else {
            winMsgEntry(w, -2, "msg_menu_stone_none_help", "msg_menu_stone_none_name");
        }
        break;
    case 14:
        pages = (w->enemyNum + 15) / 16;
        if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            for (i = 0; i < w->count; i++) {
                w->menu[i].state = 40;
            }
            w->menu[w->cursor].state = 20;
            w->fD68 = 0;
            w->f102C = 320.0f;
            w->f1034 = -240.0f;
        } else if (w->rep & 0x40) {
            w->f1044--;
            if (w->f1044 < 0) w->f1044 = 0;
            w->f1040 = w->f1044 * 16;
            psndSFXOn(0x20035);
        } else if (w->rep & 0x20) {
            w->f1044++;
            if (w->f1044 >= pages) w->f1044 = pages - 1;
            w->f1040 = w->f1044 * 16;
            psndSFXOn(0x20035);
        } else if (w->drep & 0xC000) {
            if (w->f1040 % 16 < 8) {
                w->f1040 += 8;
            } else {
                w->f1040 -= 8;
            }
            if (w->f1040 >= w->enemyNum) w->f1040 = w->enemyNum - 1;
            if (w->f1040 < 0) w->f1040 = 0;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x1000) {
            if (w->f1040 % 8 == 0) {
                w->f1040 -= 9;
            } else {
                w->f1040 -= 1;
            }
            if (w->f1040 < 0) w->f1040 = 0;
            w->f1044 = w->f1040 / 16;
            psndSFXOn(0x20035);
        } else if (w->drep & 0x2000) {
            if (w->f1040 % 8 == 7) {
                w->f1040 += 9;
            } else {
                w->f1040 += 1;
            }
            if (w->f1040 >= w->enemyNum) w->f1040 = w->enemyNum - 1;
            w->f1044 = w->f1040 / 16;
            psndSFXOn(0x20035);
        } else if (w->trg & 0x100) {
            if (swGet(w->enemy[w->f1040].id + 0x117A)) {
                psndSFXOn(0x20012);
                w->fD68 = 21;
                w->mono = monosiriInit(w->enemy[w->f1040].id, -60.0f, 150.0f);
            }
        } else if (w->trg & 0x10) {
            winSortEntry(w, 6, -310.0f, 150.0f);
            w->saved = w->fD68;
            psndSFXOn(0x20012);
            w->fD68 = 1001;
        } else if (w->trg & 0x1000) {
            return -2;
        }
        w->msgX = w->f1040 % 16 / 8 * 216 - 180;
        w->msgY = 106 - w->f1040 % 16 % 8 * 24;
        if (swGet(w->enemy[w->f1040].id + 0x117A)) {
            winMsgEntry(w, 0, battleGetUnitMonosiriPtr(w->enemy[w->f1040].id)->tattleLogTag, 0);
        } else {
            winMsgEntry(w, 0, "msg_menu_monosiri_enemy", 0);
        }
        break;
    case 21:
        if (w->trg & 0x200) {
            psndSFXOn(0x20013);
            w->fD68 = 22;
            monosiriClose(w->mono);
        } else if (w->trg & 0x1000) {
            monosiriExit(w->mono);
            return -2;
        } else {
            monosiriMain(w->mono);
        }
        break;
    case 22:
        if (monosiriCloseWait(w->mono)) {
            w->fD68 = 14;
            monosiriExit(w->mono);
        } else {
            monosiriMain(w->mono);
        }
        break;
    case 1000:
    case 1001:
        if (!winSortWait(w)) {
            w->fD68 = w->saved;
        }
        if (w->trg & 0x1000) {
            return -2;
        }
        break;
    }
    return 0;
}

void winLogMain2(WinLogWork* w) {
    s32 i;

    for (i = 0; i < w->count; i++) {
        switch (w->menu[i].state) {
        case 10:
            w->menu[i].tx = 0.0f;
            w->menu[i].ty = 140.0f;
            w->menu[i].timer = 0;
            w->menu[i].state++;
            break;
        case 11:
            if (++w->menu[i].timer > 8) {
                w->menu[i].tx = -160.0f;
                w->menu[i].ty = 140.0f;
                w->menu[i].timer = 0;
                w->menu[i].state++;
            }
            break;
        case 20:
            w->menu[i].tx = 0.0f;
            w->menu[i].ty = 140.0f;
            w->menu[i].timer = 0;
            w->menu[i].state++;
            break;
        case 21:
            if (++w->menu[i].timer > 8) {
                w->menu[i].tx = 0.0f;
                w->menu[i].ty = 45.0f * w->count / 2.0f - 45.0f * i;
                w->menu[i].timer = 0;
                w->menu[i].state++;
            }
            break;
        case 30:
            w->menu[i].tx = 0.0f;
            w->menu[i].ty = -160.0f;
            w->menu[i].timer = 0;
            w->menu[i].state++;
            break;
        case 0:
        case 41:
            break;
        case 40:
            w->menu[i].tx = 0.0f;
            w->menu[i].ty = 45.0f * w->count / 2.0f - 45.0f * i;
            w->menu[i].timer = 0;
            w->menu[i].state++;
            break;
        }
        w->menu[i].x += (w->menu[i].tx - w->menu[i].x) / 8.0f;
        w->menu[i].y += (w->menu[i].ty - w->menu[i].y) / 8.0f;
    }
    w->fE2C += (w->fE28 - w->fE2C) / 8.0;
    w->fE34 += (w->fE30 - w->fE34) / 8.0;
    w->fE68 += (w->fE64 - w->fE68) / 8.0;
    w->fE70 += (w->fE6C - w->fE70) / 8.0;
    w->fE78 += (w->fE74 - w->fE78) / 8.0;
    w->fE80 += (w->fE7C - w->fE80) / 4.0f;
    w->page0.tf1C = w->page0.idx * 0xE8;
    w->page0.f1C += (w->page0.tf1C - w->page0.f1C) / 6.0f;
    w->page0.x += (w->page0.tx - w->page0.x) / 6.0f;
    w->page0.y += (w->page0.ty - w->page0.y) / 6.0f;
    w->page0.f24 += (w->page0.tf24 - w->page0.f24) / 6.0f;
    w->page0.f2C += (w->page0.tf2C - w->page0.f2C) / 6.0f;
    w->page1.tf1C = w->page1.idx * 0xE8;
    w->page1.f1C += (w->page1.tf1C - w->page1.f1C) / 6.0f;
    w->page1.x += (w->page1.tx - w->page1.x) / 6.0f;
    w->page1.y += (w->page1.ty - w->page1.y) / 6.0f;
    w->page1.f24 += (w->page1.tf24 - w->page1.f24) / 6.0f;
    w->page1.f2C += (w->page1.tf2C - w->page1.f2C) / 6.0f;
}

void winBgGX(WinLogWork* w, s32 a, f32 x, f32 y);
void winKageGX(WinLogWork* w, GXColor c, f32 x, f32 y, f32 z, f32 s);
void winHakoGX(WinLogWork* w, s32 a, f32 x, f32 y);
void winTexInit_x2(TEXPalette* t);
void winTexSet_x2(u32 a, u32 b, Vec translate, Vec scale, GXColor color);
void winIconInit(void);
void winIconSet(u32 id, Vec translate, Vec scale, GXColor color);
void effStarStoneDraw(CameraId cam, EffectEntry* e);
void mapGX(WinLogWork* w, f32 x, f32 y);
void monoshiriGX(WinLogWork* w, f32 x, f32 y);

void winLogDisp(CameraId cam, void* param, s32 idx) {
    static const GXColor kW = {0xFF, 0xFF, 0xFF, 0xFF};
    WinLogWork* w = param;
    GXColor c1;
    GXColor c3;
    GXColor c2;
    Mtx m1;
    Mtx m2;
    f32 x;
    f32 y;
    s32 i;
    EffStarStoneWork* wk;

    c1 = kW;
    c2 = kW;
    c3 = kW;
    x = w->pos[idx].x;
    y = w->pos[idx].y;

    winBgGX(w, 4, x, y);
    if (y + w->fE34 > -480.0f) {
        mapGX(w, x + w->fE2C, y + w->fE34);
    }
    if (y + w->fE70 > -480.0f) {
        winTexInit(w->res->tex->tpl);
        winTexSet(0x24, (Vec){x + w->fE68, y + w->fE70, 0.0f}, (Vec){60.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, w->fE78});
        for (i = 0; i < 7; i++) {
            Vec v = {0.0f, 0.0f, 170.0f};
            PSMTXRotRad(m1, 'x', 0.43633232f);
            PSMTXRotRad(m2, 'y', 0.017453292f * (51.42857f * i - w->fE80));
            PSMTXMultVec(m2, &v, &v);
            PSMTXMultVec(m1, &v, &v);
            winKageGX(w, (GXColor){0x00, 0x00, 0x00, 0x80}, v.x + (x + w->fE68), (v.y + (y + w->fE70)) - 30.0f, v.z, 1.0f);
            wk = w->eff[i]->userdata;
            wk->x = v.x + (x + w->fE68);
            wk = w->eff[i]->userdata;
            wk->y = 20.0f + (v.y + (y + w->fE70));
            wk = w->eff[i]->userdata;
            wk->z = v.z;
        }
        for (i = 0; i < 7; i++) {
            effStarStoneDraw(8, w->eff[i]);
        }
    }
    if (w->page0.x < 320.0f && w->page0.y > -240.0f) {
        winHakoGX(w, 0, x + w->page0.x, y + w->page0.y);
        winTexInit(w->res->tex->tpl);
        winTexSet(0x95, (Vec){x + w->page0.f24, y + w->page0.f2C, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, c2);
        if (swGet(((s16*)w->list0)[w->page0.cursor] + 0x80)) {
            winIconInit();
            winIconSet(itemDataTable[((s16*)w->list0)[w->page0.cursor] + 0xF0].icon_id, (Vec){x + w->page0.f24, (y + w->page0.f2C) - 4.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, c2);
        }
    }
    if (w->page1.x < 320.0f && w->page1.y > -240.0f) {
        winHakoGX(w, 1, x + w->page1.x, y + w->page1.y);
        winTexInit(w->res->tex->tpl);
        winTexSet(0x96, (Vec){x + w->page1.f24, y + w->page1.f2C, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, c2);
        if (swGet(((s16*)w->list1)[w->page1.cursor] + 0x41)) {
            winIconInit();
            winIconSet(itemDataTable[((s16*)w->list1)[w->page1.cursor] + 0xB3].icon_id, (Vec){x + w->page1.f24, (y + w->page1.f2C) - 10.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, c2);
        }
    }
    if (w->fD68 == 14 || (u32)(w->fD68 - 20) <= 2 || w->fD68 == 1001) {
        monoshiriGX(w, x - 170.0f, 130.0f + y);
    }
    for (i = 0; i < w->count; i++) {
        if (i == w->cursor) {
            winTexInit(w->res->tex->tpl);
            winTexSet(0xB5, (Vec){x + w->menu[i].x, y + w->menu[i].y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0x00, 0x00, 0x00, 0x80});
            winTexInit_x2(w->res->tex->tpl);
            winTexSet_x2(w->menu[i].id + 0x1F, 0xB5, (Vec){(x + w->menu[i].x) - 8.0f, 8.0f + (y + w->menu[i].y), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, c3);
        } else {
            winTexInit_x2(w->res->tex->tpl);
            winTexSet_x2(w->menu[i].id + 0x1F, 0xB5, (Vec){x + w->menu[i].x, y + w->menu[i].y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0x80, 0x80, 0x80, 0xFF});
        }
    }
}

const char* winGetMapTplName(void) {
    if (swByteGet(0) < 0x13) return "map0.tpl";
    if (swByteGet(0) < 0x41) return "map1.tpl";
    if (swByteGet(0) < 0x79) return "map2.tpl";
    if (swByteGet(0) < 0xAF) return "map3.tpl";
    if (swByteGet(0) < 0xDE) return "map4.tpl";
    if (swByteGet(0) < 0x110) return "map5.tpl";
    if (swByteGet(0) < 0x15C) return "map6.tpl";
    return "map7.tpl";
}

double sin(double);
double __fabs(double);
static inline double fabs(double x) { return __fabs(x); }


void mapGX(WinLogWork* w, f32 x, f32 y) {
    static f32 pos_tbl[7][2] = {
        {165.0f, 68.0f}, {0.0f, 75.0f}, {97.0f, 150.0f}, {-139.0f, -33.0f},
        {41.0f, -163.0f}, {211.0f, -91.0f}, {-209.0f, 159.0f},
    };
    GXColor c2;
    GXColor c0;
    GXColor white = (c2 = (c0 = (GXColor){0xFF, 0xFF, 0xFF, 0xFF}));
    s32 tex;
    Mtx m;
    f32 top;
    f32 mx;
    f32 my;
    f32 s;
    f32 o;
    f32 scale;
    TubuDt* t;
    s32 i;
    s32 id;
    s32 k;
    s32 sw;
    AnimData* data;

    mx = 74.0f + (x + w->scrollX);
    my = 120.0f + (y + w->scrollY);
    if (w->file) {
        top = 120.0f + y;
        GXSetScissor(((304.0f + x) - 230.0f) - 2.0f, (240.0f - top) - 2.0f, 0x1D0, 0xF4);
        winTexInit(*(TEXPalette**)w->file->data);
        winTexSet(0, (Vec){mx, my, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
        winTexInit(w->res->tex->tpl);
        for (i = 0; i < sizeof(tubuDt) / sizeof(TubuDt); i++) {
            t = &tubuDt[i];
            if (swByteGet(0) >= t->id || tubuCheck(t->type)) {
                if (w->fE14 == i) {
                    winTexSet((tex = 0xBA, ((gp->retraceCount >> 4) & 1) ? tex = 0xB9 : 0, tex), (Vec){mx + t->x, my + t->y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
                } else {
                    winTexSet(t->big ? 0xBA : 0xB8, (Vec){mx + t->x, my + t->y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
                }
            }
        }
        sw = swByteGet(0);
        id = -1;
        if (sw >= 0x13 && sw < 0x37) {
            id = 0x197;
            k = 0;
        } else if (sw >= 0x41 && sw < 0x70) {
            id = 0x198;
            k = 1;
        } else if (sw >= 0x79 && sw < 0xA4) {
            id = 0x19A;
            k = 2;
        } else if (sw >= 0xAF && sw < 0xD5) {
            id = 0x19C;
            k = 3;
        } else if (sw >= 0xDE && sw < 0x105) {
            id = 0x19D;
            k = 4;
        } else if (sw >= 0x110 && sw < 0x152) {
            id = 0x199;
            k = 5;
        } else if (sw >= 0x15C && sw < 0x175) {
            id = 0x19B;
            k = 6;
        }
        if (id != -1) {
            winIconInit();
            winIconSet(id, (Vec){mx + pos_tbl[k][0], 45.0f + (my + pos_tbl[k][1]), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
        }
        if (w->pose != -1) {
            animPoseGetAnimPosePtr(w->f188);
            data = animPoseGetAnimDataPtr(w->f188);
            scale = 1.5f;
            if (w->flags & 0x2000) {
                scale = 3.0f;
            }
            PSMTXTrans(m, mx + tubuDt[w->mapIdx].x, my + tubuDt[w->mapIdx].y, 0.0f);
            animPoseSetLocalTime(w->pose, gp->retraceCount % (s32)(*(f32**)((u8*)data + 0x24))[2]);
            animPoseMain(w->pose);
            animPoseDrawMtx(w->pose, m, 1, 0.0f, scale);
            animPoseDrawMtx(w->pose, m, 2, 0.0f, scale);
            animPoseDrawMtx(w->pose, m, 3, 0.0f, scale);
        }
        GXSetScissor(0, 0, 0x260, 0x1E0);
        winTexInit(w->res->tex->tpl);
        winTexSet(0xBF, (Vec){(x - 230.0f) - 4.0f, y, 0.0f}, (Vec){1.0f, 32.0f, 1.0f}, white);
        winTexSet(0xBF, (Vec){4.0f + (230.0f + x), y, 0.0f}, (Vec){1.0f, 32.0f, 1.0f}, white);
        winTexSet(0xBF, (Vec){x, 4.0f + top, 0.0f}, (Vec){59.5f, 1.0f, 1.0f}, white);
        winTexSet(0xBF, (Vec){x, (y - 120.0f) - 4.0f, 0.0f}, (Vec){59.5f, 1.0f, 1.0f}, white);
        s = fabs(2.0f * (f32)sin((f32)gp->retraceCount / 8.0f));
        winTexInit(w->res->tex->tpl);
        o = -240.0f == w->scrollY ? 0.0f : s;
        winTexSet(0xBD, (Vec){x, top + o, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
        o = -148.0f == w->scrollX ? 0.0f : s;
        winTexInit(w->res->tex->tpl);
        winTexSet(0xBC, (Vec){(220.0f + x) + o, y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
        o = 0.0f == w->scrollY ? 0.0f : s;
        winTexInit(w->res->tex->tpl);
        winTexSet(0xBE, (Vec){x, (y - 120.0f) - o, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
        o = 0.0f == w->scrollX ? 0.0f : s;
        winTexInit(w->res->tex->tpl);
        winTexSet(0xBB, (Vec){(x - 220.0f) - o, y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    }
}

void winBookGX(WinLogWork* w, s32 a, f32 x, f32 y);
void winKirinukiGX(WinLogWork* w, s32 a, f32 x, f32 y, f32 w2, f32 h);
void winFontInit(void);
void winFontSet(Vec translate, Vec scale, GXColor color, const char* fmt, ...);
const char* msgSearch(const char* tag);
u16 FontGetMessageWidth(const char* msg);
int sprintf(char* buf, const char* fmt, ...);

void monoshiriGX(WinLogWork* w, f32 x, f32 y) {
    GXColor k1;
    GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXColor k2;
    char buf[256];
    char num[32];
    s32 i;
    s32 id;
    u16 tw;
    const char* msg;
    const char* name;
    TattleEntry* te;
    f32 fw;
    f32 ix;

    k1 = (GXColor){0x00, 0x00, 0x00, 0xFF};
    k2 = k1;
    winBookGX(w, 1, x, y);
    winKirinukiGX(w, 0, x - 110.0f, y - 160.0f, 100.0f, 50.0f);
    msg = msgSearch("msg_menu_monosiri_kazu");
    tw = 0.75f * FontGetMessageWidth(msg);
    winFontInit();
    winFontSet((Vec){(x - 108.0f) + (100 - tw) / 2, y - 166.0f, 0.0f}, (Vec){0.75f, 0.75f, 0.75f}, k1, msg);
    sprintf(buf, "%d\201^%d", w->enemyKnown, w->enemyNum);
    tw = 0.75f * FontGetMessageWidth(buf);
    winFontSet((Vec){(x - 108.0f) + (100 - tw) / 2, y - 184.0f, 0.0f}, (Vec){0.75f, 0.75f, 0.75f}, k1, buf);
    winFontInit();
    for (i = 0; i < 16; i++) {
        id = w->enemy[w->f1044 * 16 + i].id;
        te = battleGetUnitMonosiriPtr(id);
        if (w->f1044 * 16 + i >= w->enemyNum) break;
        if (swGet(id + 0x117A)) {
            if (id == 0x4D || id == 0x87) {
                if (evtGetValue(NULL, GSW(0)) < 0xD2) {
                    name = msgSearch("btl_un_hatena");
                } else {
                    name = msgSearch("btl_un_rampell");
                }
            } else {
                name = msgSearch(te->enemyTag);
            }
        } else {
            name = "\201H\201H\201H";
        }
        sprintf(num, "%d\201D", enemy_monoshiri_sort_table[id]);
        winFontSet((Vec){((24.0f + x) - 5.0f) + (i / 8) * 216, (y - 16.0f) - (i % 8) * 24, 0.0f}, (Vec){0.75f, 0.75f, 0.75f}, k2, num);
        winFontSet((Vec){(56.0f + x) + (i / 8) * 216, (y - 16.0f) - (i % 8) * 24, 0.0f}, (Vec){0.75f, 0.75f, 0.75f}, k2, name);
    }
    if (w->f1044 > 0) {
        winTexInit(w->res->tex->tpl);
        winTexSet(0x17, (Vec){440.0f + x, 18.0f + y, 0.0f}, (Vec){-1.0f, -1.0f, -1.0f}, white);
        winIconInit();
        winIconSet(0x7E, (Vec){440.0f + x, y, 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, white);
    }
    if (w->f1044 < (w->enemyNum + 15) / 16 - 1) {
        winTexInit(w->res->tex->tpl);
        winTexSet(0x17, (Vec){440.0f + x, (y - 15.0f) - 240.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
        winIconInit();
        winIconSet(0x80, (Vec){440.0f + x, y - 240.0f, 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, white);
    }
    msg = msgSearch("msg_menu_sort_narabikae");
    fw = 0.7f * FontGetMessageWidth(msg);
    winFontInit();
    ix = x + (420.0f - fw);
    winFontSet((Vec){ix, y - 210.0f, 0.0f}, (Vec){0.7f, 0.7f, 0.7f}, k1, msg);
    winIconInit();
    winIconSet(0x217, (Vec){ix - 30.0f, y - 220.0f, 0.0f}, (Vec){0.6f, 0.6f, 0.6f}, white);
}

MonosiriWork* monosiriInit(s32 id, f32 x, f32 y) {
    MonosiriWork* m = _mapAlloc(sizeof(MonosiriWork));
    memset(m, 0, sizeof(MonosiriWork));
    m->state = 0;
    m->id = id;
    m->x = x;
    m->y = y;
    m->curX = 500.0f;
    m->curY = -300.0f;
    m->alpha = 0;
    m->pose1 = -1;
    m->pose2 = -1;
    return m;
}

void monosiriMain(MonosiriWork* m) {
    s32 group = gp->inBattle ? 1 : 0;
    const char* lang[2] = {"jp", "us"};
    
    GXTexObj tex;
    TattleEntry* t;
    if (!m) return;
    switch (m->state) {
    case 0:
        if (!((void* (*)(u8, FileCallback, const char*, ...))fileAsyncf)(4, NULL, "%s/w/%s/win.tpl", getMarioStDvdRoot(), lang[gp->language])) break;
        if (!((void* (*)(u8, FileCallback, const char*, ...))fileAsyncf)(0, NULL, "%s/w/jp/mono.dat", getMarioStDvdRoot())) break;
        m->file1 = fileAllocf(4, "%s/w/%s/win.tpl", getMarioStDvdRoot(), lang[gp->language]);
        m->file2 = fileAllocf(0, "%s/w/jp/mono.dat", getMarioStDvdRoot());
        m->state++;
        TEXGetGXTexObjFromPalette(*(TEXPalette**)m->file1->data, &tex, 0x37);
        m->smart = smartAlloc(GXGetTexBufferSize(GXGetTexObjWidth(&tex), GXGetTexObjHeight(&tex), 5, 0, 0), 0);
        break;
    case 1:
        t = battleGetUnitMonosiriPtr(m->id);
        if (!animGroupBaseAsync(t->modelName, group, NULL)) break;
        if (m->id == 0x6B && !animGroupBaseAsync("c_n_moa_a", group, NULL)) break;
        m->alpha += 20;
        if (m->alpha > 255) m->alpha = 255;
        if (m->pose1 == -1) {
            if (m->id == 0x6B) {
                m->pose1 = animPoseEntry(t->modelName, group);
                animPoseSetAnim(m->pose1, t->poseName, 1);
                animPoseWorldPositionEvalOn(m->pose1);
                animPoseMain(m->pose1);
                m->pose2 = animPoseEntry("c_n_moa_a", group);
                animPoseSetAnim(m->pose2, "S_1", 1);
                animPoseMain(m->pose2);
            } else {
                m->pose1 = animPoseEntry(t->modelName, group);
                animPoseSetAnim(m->pose1, t->poseName, 1);
                animPoseMain(m->pose1);
            }
            dispEntry(2, 0.0f, 6, capture, m);
        }
        break;
    case 2:
        m->x = 600.0f;
        m->y = -400.0f;
        break;
    }
    m->curX += (m->x - m->curX) / 6.0f;
    m->curY += (m->y - m->curY) / 6.0f;
    if (m->state > 0) {
        dispEntry(8, 0.0f, 0, monosiri_disp, m);
    }
}

void monosiriClose(MonosiriWork* m) {
    if (m) {
        m->state = 2;
    }
}

BOOL monosiriCloseWait(MonosiriWork* m) {
    if (!m) return TRUE;
    if (m->curX > 500.0f && m->curY < -300.0f) return TRUE;
    return FALSE;
}

void monosiriExit(MonosiriWork* m) {
    if (m) {
        if (m->file1) {
            fileFree(m->file1);
            m->file1 = NULL;
        }
        if (m->file2) {
            fileFree(m->file2);
            m->file2 = NULL;
        }
        if (m->pose1 != -1) {
            animPoseRelease(m->pose1);
            m->pose1 = -1;
        }
        if (m->pose2 != -1) {
            animPoseRelease(m->pose2);
            m->pose2 = -1;
        }
        if (m->smart) {
            smartFree(m->smart);
            m->smart = NULL;
        }
        _mapFree(m);
    }
}

typedef struct MonoDat {
    s32 id;
    f32 x;
    f32 y;
    f32 scale;
} MonoDat;

typedef struct AnimBBox {
    u8 pad_0[0x44];
    f32 minX, minY, minZ;  // 0x44
    f32 maxX, maxY, maxZ;  // 0x50
} AnimBBox;

typedef struct MoaChain {
    const char* a;
    const char* b;
} MoaChain;

extern const s32 dat_80419a28;
extern MoaChain g_moamoa_chain_tbl[];
double tan(double);
void animPoseVivianMain(s32 poseId, Vec* v);




void capture(CameraId camera, void* param) {
    MonosiriWork* m = param;
    AnimBBox* data;
    Vec min;
    Vec max;
    CameraEntry bak;
    Mtx44 pm;
    Mtx view;
    Mtx t;
    Mtx sm;
    Mtx t2;
    GXTexObj tex;
    f32 vp[6];
    f32 proj[7];
    Vec v2;
    Vec v1;
    u16 bb0, bb1, bb2, bb3;
    u32 sx, sy, sw, sh;
    f32 cx;
    f32 cy;
    f32 dist;
    f32 tx, ty, s;
    f32 f;
    u16 tw;
    u16 th;
    s32 i;
    MonoDat* e;
    s32 n;
    Vec* gpos;
    s32* cnt;
    s32* idx;
    Vec* a;
    Vec* b;
    s32 k;

    data = (AnimBBox*)animPoseGetAnimDataPtr(m->pose1);
    min = (Vec){data->minX, data->minY, data->minZ};
    max = (Vec){data->maxX, data->maxY, data->maxZ};
    cx = (max.x + min.x) / 2.0f;
    cy = (max.y + min.y) / 2.0f;
    GXGetViewportv(vp);
    GXGetProjectionv(proj);
    GXGetScissor(&sx, &sy, &sw, &sh);
    TEXGetGXTexObjFromPalette(*(TEXPalette**)m->file1->data, &tex, 0x37);
    tw = GXGetTexObjWidth(&tex);
    th = GXGetTexObjHeight(&tex);
    GXSetViewport(0.0f, 0.0f, tw, th, 0.0f, 1.0f);
    GXSetScissor(1, 1, tw - 2, th - 2);
    C_MTXPerspective(pm, 25.0f, 1.2666667f, 1.0f, 1000.0f);
    GXSetProjection(pm, GX_PERSPECTIVE);
    if ((max.x - min.x) / tw > (max.y - min.y) / th) {
        dist = (max.x - cx) / (f32)tan(0.21816615760326385);
    } else {
        dist = ((608.0f * (max.y - cy)) / 480.0f) / (f32)tan(0.21816615760326385);
    }
    C_MTXLookAt(view, &(Vec){cx, cy, dist}, &(Vec){0.0f, 1.0f, 0.0f}, &(Vec){cx, cy, 0.0f});
    n = ((u32*)m->file2->data)[1] / sizeof(MonoDat);
    e = ((MonoDat**)m->file2->data)[0];
    for (i = 0; i < n; i++, e++) {
        if (e->id == m->id) break;
    }
    if (i < n) {
        tx = e->x;
        ty = e->y;
        s = e->scale;
    } else {
        ty = tx = 0.0f;
        s = 1.0f;
    }
    PSMTXTrans(t, tx, ty, 0.0f);
    PSMTXScale(sm, s, s, s);
    PSMTXConcat(t, sm, t);
    PSMTXConcat(view, t, view);
    sysWaitDrawSync();
    GXClearBoundingBox();
    bak = *camGetPtr(camera);
    PSMTXCopy(view, camGetCurPtr()->view);
    if (animPoseGetVivianType(m->pose1)) {
        animPoseVivianMain(m->pose1, &(Vec){0.0f, 0.0f, 0.0f});
    }
    animPoseSetMaterialFlagOn(m->pose1, 0x1800);
    animPosePeraOff(m->pose1);
    PSMTXIdentity(t);
    animPoseDrawMtx(m->pose1, t, 1, 0.0f, 1.0f);
    animPoseDrawMtx(m->pose1, t, 2, 0.0f, 1.0f);
    animPoseDrawMtx(m->pose1, t, 3, 0.0f, 1.0f);
    animPosePeraOn(m->pose1);
    if (m->id == 0x6B) {
        gpos = **(Vec***)((u8*)animPoseGetAnimPosePtr(m->pose1) + 0x15C);
        cnt = smartAlloc(dat_80419a28 * 4, 3)->address;
        idx = smartAlloc(2000, 3)->address;
        memset(cnt, 0, dat_80419a28 * 4);
        for (i = 0; 500 > i; i++) {
            idx[i] = cnt[i % dat_80419a28]++;
        }
        animPoseSetMaterialFlagOn(m->pose2, 0x1800);
        animPosePeraOff(m->pose2);
        for (i = 0; i < 500; i++) {
            k = i % dat_80419a28;
            f = (f32)idx[i] / (f32)cnt[k];
            a = &gpos[animPoseGetGroupIdx(m->pose1, g_moamoa_chain_tbl[k].a)];
            b = &gpos[animPoseGetGroupIdx(m->pose1, g_moamoa_chain_tbl[k].b)];
            PSVECScale(a, &v1, f);
            PSVECScale(b, &v2, 1.0f - f);
            PSVECAdd(&v1, &v2, &v1);
            PSMTXTrans(t2, v1.x + (5 - irand(10)), v1.y + (5 - irand(10)), v1.z + (5 - irand(10)));
            animPoseDrawMtx(m->pose2, t2, 1, 0.0f, 1.0f);
            animPoseDrawMtx(m->pose2, t2, 2, 0.0f, 1.0f);
            animPoseDrawMtx(m->pose2, t2, 3, 0.0f, 1.0f);
        }
        animPosePeraOn(m->pose2);
    }
    PSMTXCopy(bak.view, camGetCurPtr()->view);
    sysWaitDrawSync();
    GXReadBoundingBox(&bb0, &bb1, &bb2, &bb3);
    GXSetTexCopySrc(0, 0, tw, th);
    GXSetTexCopyDst(tw, th, GX_TF_RGB5A3, GX_FALSE);
    GXCopyTex(m->smart->address, GX_TRUE);
    GXPixModeSync();
    GXSetViewport(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
    GXSetProjectionv(proj);
    GXSetScissor(sx, sy, sw, sh);
}

void winHalfBookGX(TEXPalette* tpl, s32 a, f32 x, f32 y);
void winFontInit(void);
void winFontSet(Vec translate, Vec scale, GXColor color, const char* fmt, ...);
const char* msgSearch(const char* tag);
u16 FontGetMessageWidth(const char* msg);
int sprintf(char* buf, const char* fmt, ...);

void monosiri_disp(CameraId camera, void* param) {
    MonosiriWork* m = param;
    GXColor black = {0x00, 0x00, 0x00, 0xFF};
    char buf[256];
    Mtx t1;
    Mtx sc;
    Mtx t2;
    GXTexObj tex;
    f32 x;
    f32 y;
    f32 s;
    f32 w;
    f32 xx;
    s32 mtx;
    s32 i;
    s32 id;
    TattleEntry* te;
    u16 tw;
    u16 th;
    s32 d;
    GXColor c0;
    GXColor c;

    x = m->curX;
    y = m->curY;
    if (m->file1) {
        winHalfBookGX(*(TEXPalette**)m->file1->data, 0, x, y);
        TEXGetGXTexObjFromPalette(*(TEXPalette**)m->file1->data, &tex, 0x37);
        tw = GXGetTexObjWidth(&tex);
        th = GXGetTexObjHeight(&tex);
        TEXGetGXTexObjFromPalette(*(TEXPalette**)m->file1->data, &tex, 0x37);
        GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&tex, GX_TEXMAP0);
        GXInitTexObj(&tex, m->smart->address, tw, th, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&tex, GX_TEXMAP1);
        GXSetNumTexGens(8);
        for (i = 0; i < 8; i++) {
            mtx = GX_TEXMTX0 + i * 3;
            s = 1.0f - 0.04f * (7 - i);
            PSMTXTrans(t1, 0.5f, 0.5f, 0.0f);
            PSMTXScale(sc, s, s, s);
            PSMTXTrans(t2, -0.5f, -0.5f, 0.0f);
            PSMTXConcat(t1, sc, t1);
            PSMTXConcat(t1, t2, t1);
            GXLoadTexMtxImm(t1, mtx, GX_MTX2x4);
            GXSetTexCoordGen2(i, GX_TG_MTX2x4, GX_TG_TEX0, mtx, GX_FALSE, GX_PTIDENTITY);
        }
        GXSetTevColor(GX_TEVREG0, (GXColor){0xCF, 0xBC, 0x9E, 0xFF});
        GXSetTevColor(GX_TEVREG1, (GXColor){0x00, 0x00, 0x00, m->alpha});
        GXSetNumTevStages(12);
        for (i = 0; i < 8; i++) {
            GXSetTevOrder(i, i, GX_TEXMAP1, GX_COLOR_NULL);
            GXSetTevColorOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(i, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, 2);
            GXSetTevAlphaIn(i, 7, 4, 6, i == 0 ? GX_CA_ZERO : GX_CA_APREV);
            GXSetTevKAlphaSel(i, 7);
        }
        GXSetTevOrder(8, 7, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorOp(8, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(8, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(8, 0, 8, 9, 0xF);
        GXSetTevAlphaIn(8, 0, 7, 4, 4);
        GXSetTevOrder(9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevColorOp(9, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(9, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(9, 0xF, 0xF, 0xF, 0);
        GXSetTevAlphaIn(9, 7, 0, 2, 7);
        GXSetTevOrder(10, 7, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp(10, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(10, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(10, 0xF, 8, 0, 0xF);
        GXSetTevAlphaIn(10, 7, 7, 7, 0);
        GXSetTevOrder(11, 7, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp(11, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(11, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(11, 8, 0, 1, 0xF);
        GXSetTevAlphaIn(11, 7, 7, 7, 4);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        {
            f32 x1 = 32.0f + x;
            f32 y1 = y - 8.0f;
            f32 qw = 216.0f;
            GXPosition3f32(x1, y1, 0.0f);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(x1, y1 - 160.0f, 0.0f);
            GXTexCoord2f32(0.0f, 1.0f);
            GXPosition3f32(x1 + qw, y1 - 160.0f, 0.0f);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(x1 + qw, y1, 0.0f);
            GXTexCoord2f32(1.0f, 0.0f);
        }
        id = m->id;
        te = battleGetUnitMonosiriPtr(id);
        if (id == 0x4D || id == 0x87) {
            if (evtGetValue(NULL, GSW(0)) < 0xD2) {
                sprintf(buf, "%d\201D%s", enemy_monoshiri_sort_table[id], msgSearch("btl_un_hatena"));
            } else {
                sprintf(buf, "%d\201D%s", enemy_monoshiri_sort_table[id], msgSearch("btl_un_rampell"));
            }
        } else {
            sprintf(buf, "%d\201D%s", enemy_monoshiri_sort_table[id], msgSearch(te->enemyTag));
        }
        w = 0.75f * FontGetMessageWidth(buf);
        winFontInit();
        winFontSet((Vec){(16.0f + x) + (248.0f - w) / 2.0f, y - 180.0f, 0.0f}, (Vec){0.75f, 0.75f, 0.75f}, black, buf);
        sprintf(buf, "%s\201@%s", msgSearch("menu_monosiri_derutokoro"), msgSearch(te->locationTag));
        w = 0.75f * FontGetMessageWidth(buf);
        winFontSet((Vec){1.0f + ((16.0f + x) + (248.0f - w) / 2.0f), y - 210.0f, 0.0f}, (Vec){0.75f, 0.75f, 0.75f}, black, buf);
    }
}

#pragma force_active on
#pragma force_active reset
