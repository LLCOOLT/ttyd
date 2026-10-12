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
    u16 flags;
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
    u8 pad_0[0x28];
    WinLogRes* res;           // 0x28
    u8 pad_2c[0x30 - 0x2C];
    FileEntry* file;          // 0x30
    u8 pad_34[0xC4 - 0x34];
    WinLogPos pos[3];         // 0xC4
    u8 pad_100[0x158 - 0x100];
    f32 msgX;                 // 0x158
    f32 msgY;                 // 0x15C
    u8 pad_160[0xD68 - 0x160];
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

void winMsgEntry(void* wp, s32 a, const char* msg, s32 b);
void capture(CameraId camera, void* param);
void monosiri_disp(CameraId camera, void* param);

TubuDt tubuDt[] = {
    {14, -34, 0x100, 3, "gor"},
    {-4, -31, 0x2, 12, "gor"},
    {-20, -31, 0x2, 12, "gor"},
    {-33, -38, 0x102, 12, "tik"},
    {118, 30, 0x100, 23, "hei"},
    {134, 22, 0x0, 26, "hei"},
    {150, 14, 0x0, 26, "hei"},
    {176, 9, 0x0, 26, "hei"},
    {200, 6, 0x100, 26, "nok"},
    {136, 39, 0x3, 35, "hei"},
    {152, 48, 0x3, 35, "hei"},
    {165, 53, 0x3, 35, "hei"},
    {165, 68, 0x103, 35, "gon"},
    {0, 36, 0x100, 71, "win"},
    {0, 56, 0x0, 74, "win"},
    {0, 75, 0x100, 74, "mri"},
    {16, 44, 0x0, 81, "win"},
    {27, 53, 0x0, 81, "win"},
    {42, 65, 0x100, 81, "hou"},
    {30, -17, 0x0, 127, "gor"},
    {36, 0, 0x0, 127, "gor"},
    {46, 15, 0x0, 127, "gor"},
    {55, 32, 0x0, 127, "gor"},
    {74, 45, 0x0, 127, "gor"},
    {83, 61, 0x0, 127, "gor"},
    {83, 75, 0x0, 127, "gor"},
    {83, 93, 0x0, 127, "gor"},
    {72, 101, 0x0, 127, "gor"},
    {71, 114, 0x0, 127, "gor"},
    {71, 132, 0x0, 127, "gor"},
    {80, 141, 0x0, 127, "gor"},
    {97, 150, 0x100, 127, "tou"},
    {-181, -90, 0x100, 178, "usu"},
    {-163, -90, 0x4, 184, "usu"},
    {-145, -90, 0x4, 184, "usu"},
    {-135, -77, 0x4, 184, "usu"},
    {-143, -63, 0x4, 184, "usu"},
    {-159, -63, 0x4, 184, "usu"},
    {-176, -63, 0x4, 184, "usu"},
    {-191, -63, 0x4, 184, "usu"},
    {-206, -63, 0x4, 184, "usu"},
    {-228, -63, 0x104, 184, "gra"},
    {-228, -44, 0x0, 193, "gra"},
    {-216, -31, 0x0, 193, "gra"},
    {-198, -27, 0x0, 193, "gra"},
    {-181, -29, 0x0, 193, "gra"},
    {-160, -33, 0x0, 193, "gra"},
    {-139, -33, 0x100, 193, "jin"},
    {13, -56, 0x0, 232, "gor"},
    {13, -70, 0x0, 232, "gor"},
    {12, -84, 0x0, 232, "gor"},
    {-3, -94, 0x0, 232, "gor"},
    {-14, -104, 0x0, 232, "gor"},
    {-31, -115, 0x0, 232, "gor"},
    {-45, -128, 0x0, 232, "gor"},
    {-48, -143, 0x0, 232, "gor"},
    {-38, -158, 0x0, 232, "gor"},
    {-11, -163, 0x100, 232, "muj"},
    {7, -163, 0x0, 243, "muj"},
    {21, -163, 0x0, 243, "muj"},
    {41, -163, 0x100, 243, "dou"},
    {36, -34, 0x0, 310, "gor"},
    {53, -27, 0x0, 310, "gor"},
    {69, -12, 0x0, 310, "gor"},
    {85, 1, 0x0, 310, "gor"},
    {109, 7, 0x0, 310, "gor"},
    {132, 4, 0x0, 310, "gor"},
    {149, -8, 0x0, 310, "gor"},
    {158, -25, 0x100, 310, "eki"},
    {143, -40, 0x0, 334, "eki"},
    {133, -52, 0x0, 334, "eki"},
    {132, -66, 0x0, 334, "eki"},
    {132, -82, 0x0, 334, "eki"},
    {155, -90, 0x100, 334, "pik"},
    {175, -90, 0x0, 336, "pik"},
    {193, -91, 0x0, 336, "pik"},
    {211, -91, 0x100, 336, "sin"},
    {-167, 17, 0x100, 353, "bom"},
    {-167, 37, 0x0, 358, "bom"},
    {-167, 50, 0x0, 358, "bom"},
    {-167, 64, 0x0, 358, "bom"},
    {-167, 82, 0x0, 358, "bom"},
    {-167, 99, 0x0, 358, "bom"},
    {-167, 116, 0x0, 358, "bom"},
    {-167, 133, 0x0, 358, "bom"},
    {-167, 151, 0x100, 358, "moo"},
    {-171, 169, 0x0, 361, "moo"},
    {-185, 177, 0x0, 361, "moo"},
    {-200, 171, 0x0, 361, "moo"},
    {-209, 159, 0x100, 361, "aji"},
    {-33, -50, 0x0, 382, "gor"},
    {-33, -62, 0x0, 382, "gor"},
    {-33, -74, 0x100, 382, "las"},
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
    if (!strcmp(gp->currentMapName, "muj_10") || !strcmp(gp->currentMapName, "muj_11") || !strcmp(gp->currentMapName, "muj_12")) area = "dou";

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

void winLogDisp(CameraId cam, WinLogWork* w, s32 idx) {
    GXColor c3;
    GXColor c1 = {0xFF, 0xFF, 0xFF, 0xFF};
    GXColor c2 = (c3 = c1);
    Mtx m1;
    Mtx m2;
    f32 x;
    f32 y;
    s32 i;
    EffStarStoneWork* wk;

    x = w->pos[idx].x;
    y = w->pos[idx].y;
    winBgGX(w, 4, x, y);
    if (y + w->fE34 > -480.0f) {
        mapGX(w, x + w->fE2C, y + w->fE34);
    }
    if (y + w->fE70 > -480.0f) {
        GXColor col = {0xFF, 0xFF, 0xFF, 0x00};
        winTexInit(w->res->tex->tpl);
        col.a = w->fE78;
        winTexSet(0x24, (Vec){x + w->fE68, y + w->fE70, 0.0f}, (Vec){60.0f, 1.0f, 1.0f}, col);
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
        if (swGet((s16)w->list0[w->page0.cursor] + 0x80)) {
            winIconInit();
            winIconSet(itemDataTable[(s16)w->list0[w->page0.cursor] + 0xF0].icon_id, (Vec){x + w->page0.f24, (y + w->page0.f2C) - 4.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, c2);
        }
    }
    if (w->page1.x < 320.0f && w->page1.y > -240.0f) {
        winHakoGX(w, 1, x + w->page1.x, y + w->page1.y);
        winTexInit(w->res->tex->tpl);
        winTexSet(0x96, (Vec){x + w->page1.f24, y + w->page1.f2C, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, c2);
        if (swGet((s16)w->list1[w->page1.cursor] + 0x41)) {
            winIconInit();
            winIconSet(itemDataTable[(s16)w->list1[w->page1.cursor] + 0xB3].icon_id, (Vec){x + w->page1.f24, (y + w->page1.f2C) - 10.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, c2);
        }
    }
    switch (w->fD68) {
    case 14:
    case 20:
    case 21:
    case 22:
    case 1001:
        monoshiriGX(w, x - 170.0f, 130.0f + y);
        break;
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
    const char* lang[2] = {"jp", "us"};
    u16 h;
    s32 group;
    GXTexObj tex;
    TattleEntry* t;
    group = gp->inBattle != 0;

    if (!m) return;
    switch (m->state) {
    case 0:
        if (!((void* (*)(u8, FileCallback, const char*, ...))fileAsyncf)(4, NULL, "%s/w/%s/win.tpl", getMarioStDvdRoot(), lang[gp->language])) break;
        if (!((void* (*)(u8, FileCallback, const char*, ...))fileAsyncf)(0, NULL, "%s/w/jp/mono.dat", getMarioStDvdRoot())) break;
        m->file1 = fileAllocf(4, "%s/w/%s/win.tpl", getMarioStDvdRoot(), lang[gp->language]);
        m->file2 = fileAllocf(0, "%s/w/jp/mono.dat", getMarioStDvdRoot());
        m->state++;
        TEXGetGXTexObjFromPalette(*(TEXPalette**)m->file1->data, &tex, 0x37);
        h = GXGetTexObjHeight(&tex);
        m->smart = smartAlloc(GXGetTexBufferSize(GXGetTexObjWidth(&tex), h, 5, 0, 0), 0);
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
