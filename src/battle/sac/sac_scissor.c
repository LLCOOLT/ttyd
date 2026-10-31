// Star-power special move Art Attack (sac_scissor): drawing around enemies with the star to damage them.
#include "eff/eff_starstone.h"
#include "icon_ids.h"
// this unit is size-optimised, as in the original (the object differs without it)
#pragma optimize_for_size on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "driver/effdrv.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "memory.h"
#include "system.h"
#include "pmario_sound.h"
#include "mario/mariost.h"
#include "driver/dispdrv.h"
#include "driver/camdrv.h"
#include "driver/offscreendrv.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/sac/sac_common.h"
#include "evt/evt_img.h"
#include "evt/evt_offscreen.h"
#include "evt/evt_paper.h"
#include "evt/evt_snd.h"
#include "battle/battle_sub.h"
#include "battle/battle_disp.h"
#include "battle/sac/sac_scissor.h"
#include "manager/fontmgr.h"
#include "libc_decls.h"
#include <dolphin/os.h>

double fabs(double);
/** Absolute value through the __fabs intrinsic; scissor_intersection uses it to pick each segment's major axis. */
static inline double my_fabsf(float x) {
    return __fabs(x);
}
static void scissor_disp_control(CameraId camera, void* param);

typedef struct ScissorTri {
    f32 x[3]; // 0x0
    f32 y[3]; // 0xC
} ScissorTri;

typedef struct ScissorWork {
    /* 0x000 */ u32 flags;
    /* 0x004 */ u8 reserved_04[8]; // 0x004, never accessed
    /* 0x00C */ s32 cutCount;
    /* 0x010 */ s32 blinkTimer;
    /* 0x014 */ s32 triCount;
    /* 0x018 */ s32 unitIds[16];
    /* 0x058 */ s32 power[16];
    /* 0x098 */ u8 audienceVol;
    /* 0x09C */ struct ScissorStars {
        /* 0x09C */ s32 count;
        /* 0x0A0 */ s32 unusedA0; // only ever cleared
        /* 0x0A4 */ f32 prevStickX;
        /* 0x0A8 */ f32 prevStickY;
        /* 0x0AC */ f32 stickX;
        /* 0x0B0 */ f32 stickY;
        /* 0x0B4 */ f32 headX;
        /* 0x0B8 */ f32 headY;
        /* 0x0BC */ f32 lastX;
        /* 0x0C0 */ f32 lastY;
        /* 0x0C4 */ u8 reserved_C4[0xD4 - 0xC4]; // 0x0C4, never accessed
        /* 0x0D4 */ f32 velX;
        /* 0x0D8 */ f32 velY;
        /* 0x0DC */ f32 starX[4]; // other stars (idx 1..4), x
        /* 0x0EC */ f32 starY[4]; // other stars (idx 1..4), y
    } stars;
    /* 0x0FC */ s32 state;
    /* 0x100 */ s32 step;
    /* 0x104 */ s32 timer;
    /* 0x108 */ f32 timerX;
    /* 0x10C */ f32 timerY;
    /* 0x110 */ u8 reserved_110[4];      // 0x110, never accessed
    /* 0x114 */ void* strokePts;         // Pt[stars.count] stroke points traced by the star
    /* 0x118 */ struct ScissorTri* tris; // triangle list (0x3000 bytes), drawn by scissor_ofscreen_ok
    /* 0x11C */ s32 phase;
    /* 0x120 */ s32 phaseTimer;
    /* 0x124 */ Vec pos;
    /* 0x130 */ Vec from;
    /* 0x13C */ Vec to;
    /* 0x148 */ u8 reserved_148[0xC]; // 0x148, never accessed
    /* 0x154 */ Vec scale;
    /* 0x160 */ Vec rot;
    /* 0x16C */ EffectEntry* eff;
    /* 0x170 */ smartEntry* smart;
} ScissorWork;

typedef struct Pt {
    f32 x, y;
} Pt;
ScissorWork* GetScissorPtr(void);
static void scissor_disp_region(CameraId camera, void* param);
static void scissor_capture(CameraId camera, void* param);
static void tess(Pt* buf, s32 count);
static void star_disp2D_sub(s32 idx, s32 alpha);
static s32 scissor_damage_sub2(Vec pt);
static void scissor_damage_sub(BattleUnit* unit, s32* out);
static s32 scissor_intersection(f32, f32, f32, f32, f32, f32, f32, f32, f32*, f32*);

static s32 star_stone_appear();
static s32 wait_star_standby();
static s32 scissor_end();
static s32 scissor_init();
static s32 scissor_offscreen();
static s32 scissor_ofscreen_ok();
static s32 scissor_damage();
static s32 scissor_control();
static s32 scissor_timer_main();
static s32 scissor_timer_get();
static s32 star_control();
static s32 scissor_tess();

BattleWeapon weapon_scissor;
BattleWeapon weapon_scissor_finish;

/**
 * Art Attack's per-loop hit: scissor_damage hits each enemy inside a closed loop with it, for the power
 * weaponGetPower_Scissor worked out (0 to 3); it always hits, pierces defense and cannot be guarded.
 */
BattleWeapon weapon_scissor = {
    "btl_wn_sac_scissor", // name
    ICON_19C, // icon
    {0}, // pad_06
    0, // itemId
    "msg_scissor", // description
    100, // baseAccuracy
    0, // baseFpCost
    4, // baseSpCost
    0, // superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPower_Scissor, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_sac_5", // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_PIERCES_DEFENSE | SPECIAL_SHATTERS_FREEZE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    0, 0, 0, 0, 0, 0, 0, // holdFastTime..fpRegenStrength
    {0}, // pad_AE
    marioAttackEvent_Scissor, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Art Attack's finishing hit: no damage of its own, given by marioAttackEvent_Scissor to each enemy
 * that took damage during the drawing, with damage pattern 27 for the hurt pose.
 */
BattleWeapon weapon_scissor_finish = {
    "btl_wn_sac_scissor", // name
    0, // icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, // element
    27, // damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_SHATTERS_FREEZE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    0, 0, 0, 0, 0, 0, 0, // holdFastTime..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

// FAKE: inlining off (FAKES.md); without it GetScissorPtr is inlined into its callers (17 shrink, e.g. star_stone_appear 11 -> 5 instructions)
#pragma dont_inline on
/** The minigame's work area, kept in the battle's shared action-command work buffer. */
ScissorWork* GetScissorPtr(void) {
    return (ScissorWork*)_battleWorkPointer->actionCommands.work;
}
#pragma dont_inline reset

/**
 * Intersects segments (x1,y1)-(x2,y2) and (x3,y3)-(x4,y4) in screen space,
 * handling vertical and horizontal ones separately;
 * returns 1 with the crossing point in *ox, *oy when they cross, 0 otherwise.
 */
static s32 scissor_intersection(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, f32 x4, f32 y4, f32* ox, f32* oy) {
    f32 a1, a2, d;
    f32 dx1, dy1, dx2, dy2;
    f32 minx, miny, maxx, maxy;
    f32 minx2, miny2, maxx2, maxy2;
    s32 f1, f2;

    if (x1 <= x2) {
        minx = x1;
        maxx = x2;
    } else {
        minx = x2;
        maxx = x1;
    }
    if (y1 <= y2) {
        miny = y1;
        maxy = y2;
    } else {
        miny = y2;
        maxy = y1;
    }
    if (x3 <= x4) {
        minx2 = x3;
        maxx2 = x4;
    } else {
        minx2 = x4;
        maxx2 = x3;
    }
    if (y3 <= y4) {
        miny2 = y3;
        maxy2 = y4;
    } else {
        miny2 = y4;
        maxy2 = y3;
    }
    dx1 = x2 - x1;
    f1 = 0;
    if (dx1 == 0.0f) {
        f1 = 1;
    }
    dy1 = y2 - y1;
    if (dy1 == 0.0f) {
        f1 = 2;
    }
    dx2 = x4 - x3;
    f2 = 0;
    if (dx2 == 0.0f) {
        f2 = 1;
    }
    dy2 = y4 - y3;
    if (dy2 == 0.0f) {
        f2 = 2;
    }

    if (f1 == 0 && f2 == 0) {
        if (my_fabsf(dx1) > my_fabsf(dy1)) {
            a1 = dy1 / dx1;
            if (my_fabsf(dx2) > my_fabsf(dy2)) {
                a2 = dy2 / dx2;
                if (a1 - a2 != 0.0f) {
                    d = a1 - a2;
                } else {
                    d = 1e-6f;
                }
                *ox = ((y3 - y1) + (a1 * x1 - a2 * x3)) / d;
                *oy = a1 * (*ox - x1) + y1;
            } else {
                a2 = dx2 / dy2;
                if (a1 * a2 != 1.0f) {
                    d = 1.0f - a1 * a2;
                } else {
                    d = 1e-6f;
                }
                *ox = (a2 * ((-a1 * x1 + y1) - y3) + x3) / d;
                *oy = a1 * (*ox - x1) + y1;
            }
        } else {
            a1 = dx1 / dy1;
            if (my_fabsf(dx2) > my_fabsf(dy2)) {
                a2 = dy2 / dx2;
                if (a1 * a2 != 1.0f) {
                    d = 1.0f - a1 * a2;
                } else {
                    d = 1e-6f;
                }
                *oy = (a2 * ((-a1 * y1 + x1) - x3) + y3) / d;
                *ox = a1 * (*oy - y1) + x1;
            } else {
                a2 = dx2 / dy2;
                if (a1 - a2 != 0.0f) {
                    d = a1 - a2;
                } else {
                    d = 1e-6f;
                }
                *oy = ((x3 - x1) + (a1 * y1 - a2 * y3)) / d;
                *ox = a1 * (*oy - y1) + x1;
            }
        }
        if (*ox >= minx && *ox <= maxx && *oy >= miny && *oy <= maxy && *ox >= minx2 && *ox <= maxx2 &&
            *oy >= miny2 && *oy <= maxy2) {
            return 1;
        }
        return 0;
    }
    if (f1 == 0 && f2 == 1) {
        a1 = dy1 / dx1;
        *ox = x3;
        *oy = a1 * (*ox - x1) + y1;
        if (*ox >= minx && *ox <= maxx && *oy >= miny2 && *oy <= maxy2) {
            return 1;
        }
        return 0;
    }
    if (f1 == 1 && f2 == 0) {
        a2 = dy2 / dx2;
        *ox = x1;
        *oy = a2 * (*ox - x3) + y3;
        if (*ox >= minx2 && *ox <= maxx2 && *oy >= miny && *oy <= maxy) {
            return 1;
        }
        return 0;
    }
    if (f1 == 0 && f2 == 2) {
        a1 = dy1 / dx1;
        *oy = y3;
        *ox = (*oy - y1 + a1 * x1) / a1;
        if (*oy >= miny && *oy <= maxy && *ox >= minx2 && *ox <= maxx2) {
            return 1;
        }
        return 0;
    }
    if (f1 == 2 && f2 == 0) {
        a2 = dy2 / dx2;
        *oy = y1;
        *ox = (*oy - y3 + a2 * x3) / a2;
        if (*oy >= miny2 && *oy <= maxy2 && *ox >= minx && *ox <= maxx) {
            return 1;
        }
        return 0;
    }
    if (f1 == 1 && f2 == 1) {
        if (x1 == x3) {
            *ox = x3;
            *oy = y3;
            if ((y1 >= miny2 && y1 <= maxy2) || (y2 >= miny2 && y2 <= maxy2)) {
                return 1;
            }
        }
        return 0;
    }
    if (f1 == 1 && f2 == 2) {
        *ox = x1;
        *oy = y3;
        if (x1 >= minx2 && x1 <= maxx2 && y3 >= miny && y3 <= maxy) {
            return 1;
        }
        return 0;
    }
    if (f1 == 2 && f2 == 1) {
        *ox = x3;
        *oy = y1;
        if (x3 >= minx && x3 <= maxx && y1 >= miny2 && y1 <= maxy2) {
            return 1;
        }
        return 0;
    }
    if (f1 == 2 && f2 == 2) {
        if (y1 == y3) {
            *ox = x3;
            *oy = y3;
            if ((x1 >= minx2 && x1 <= maxx2) || (x2 >= minx2 && x2 <= maxx2)) {
                return 1;
            }
        }
        return 0;
    }
    return 0;
}

// FAKE: inlining off (FAKES.md); without it scissor_intersection2 is inlined into scissor_cross (267 -> 291 instructions)
#pragma dont_inline on
/** scissor_intersection, but segments that share an endpoint do not count as crossing. */
static s32 scissor_intersection2(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, f32 x4, f32 y4, f32* ox, f32* oy) {
    if (x1 == x3 && y1 == y3) {
        return 0;
    }
    if (x1 == x4 && y1 == y4) {
        return 0;
    }
    if (x2 == x3 && y2 == y3) {
        return 0;
    }
    if (x2 == x4 && y2 == y4) {
        return 0;
    }
    return scissor_intersection(x1, y1, x2, y2, x3, y3, x4, y4, ox, oy);
}

#pragma dont_inline reset
// FAKE: inlining off (FAKES.md); without it scissor_intersection3 is inlined into scissor_cross (267 -> 298 instructions; one other caller grows)
#pragma dont_inline on
/**
 * scissor_intersection with the first segment stretched 1000 units both ways,
 * testing that whole line against the second segment.
 */
static s32 scissor_intersection3(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, f32 x4, f32 y4, f32* ox, f32* oy) {
    f32 dx = x2 - x1;
    f32 slope;
    if (dx != 0.0f) {
        slope = (y2 - y1) / dx;
        if (x1 >= x2) {
            slope = 1000.0f * slope;
            x1 += 1000.0f;
            x2 -= 1000.0f;
            y1 += slope;
            y2 -= slope;
        } else {
            slope = 1000.0f * slope;
            x1 -= 1000.0f;
            x2 += 1000.0f;
            y1 -= slope;
            y2 += slope;
        }
    } else if (y1 >= y2) {
        y1 = 1000.0f;
        y2 = -1000.0f;
    } else {
        y1 = -1000.0f;
        y2 = 1000.0f;
    }
    return scissor_intersection(x1, y1, x2, y2, x3, y3, x4, y4, ox, oy);
}
#pragma dont_inline reset

// FAKE: inlining off (FAKES.md); without it scissor_intersection4 is inlined into scissor_cross (267 -> 299 instructions)
#pragma dont_inline on
/** scissor_intersection3, but a shared endpoint counts as a crossing at that point. */
static s32 scissor_intersection4(f32 x1, f32 y1, f32 x2, f32 y2, f32 x3, f32 y3, f32 x4, f32 y4, f32* ox, f32* oy) {
    if (x1 == x3 && y1 == y3) {
        *ox = x1;
        *oy = y1;
        return 1;
    }
    if (x1 == x4 && y1 == y4) {
        *ox = x1;
        *oy = y1;
        return 1;
    }
    if (x2 == x3 && y2 == y3) {
        *ox = x2;
        *oy = y2;
        return 1;
    }
    if (x2 == x4 && y2 == y4) {
        *ox = x2;
        *oy = y2;
        return 1;
    }
    return scissor_intersection3(x1, y1, x2, y2, x3, y3, x4, y4, ox, oy);
}

#pragma dont_inline reset
/**
 * Whether chord a-b is a usable diagonal of polygon pts (n points):
 * it must cross no edge and its midpoint must lie inside (crossings counted along the chord's line).
 * Returns 1 if so; used by tess.
 */
static s32 scissor_cross(Pt* a, Pt* b, Pt* pts, s32 n) {
    f32 xs[512];
    f32 ys[512];
    Pt* cur;
    Pt* next;
    f32 ox, oy, tx, ty;
    Pt* last;
    s32 i, j, k, found;
    s32 cnt;
    f32 mid;
    for (k = 0; k < n; k++) {
        if (scissor_intersection2(a->x, a->y, b->x, b->y, pts[k].x, pts[k].y, pts[(k + 1) % n].x, pts[(k + 1) % n].y, &ox, &oy)) {
            return 0;
        }
    }
    xs[0] = -1000.0f;
    ys[0] = -1000.0f;
    last = &pts[n - 1];
    cnt = 1;
    for (i = 0; i < n; i++) {
        cur = &pts[i];
        next = &pts[(i + 1) % n];
        if (scissor_intersection4(1.0f + a->x, a->y, 1.0f + b->x, b->y, cur->x, cur->y, next->x, next->y, &ox, &oy)) {
            found = 0;
            if (cur->x == ox && cur->y == oy) {
                Pt* prev;
                if (i == 0) {
                    prev = last;
                } else {
                    prev = &pts[i - 1];
                }
                if (scissor_intersection3(a->x, a->y, b->x, b->y, prev->x, prev->y, next->x, next->y, &tx, &ty)) {
                    found = 1;
                }
            }
            if (found == 1) {
                for (k = 0; k < n; k++) {
                    if (ox == xs[k] && oy == ys[k]) {
                        break;
                    }
                }
                if (k == n) {
                    xs[cnt] = ox;
                    ys[cnt] = oy;
                    cnt++;
                }
            } else {
                xs[cnt] = ox;
                ys[cnt] = oy;
                cnt++;
            }
        }
    }
    xs[cnt] = 1000.0f;
    ys[cnt] = 1000.0f;
    if (a->x != b->x) {
        for (i = 0; i < cnt; i++) {
            for (j = i + 1; j < cnt + 1; j++) {
                if (xs[i] > xs[j]) {
                    f32 t0 = xs[i];
                    f32 t1 = ys[i];
                    xs[i] = xs[j];
                    ys[i] = ys[j];
                    xs[j] = t0;
                    ys[j] = t1;
                }
            }
        }
        mid = 0.5f * (a->x + b->x);
        for (k = 0; k < cnt; k++) {
            if (mid >= xs[k] && mid < xs[k + 1]) {
                return k & 1;
            }
        }
    } else {
        for (i = 0; i < cnt; i++) {
            for (j = i + 1; j < cnt + 1; j++) {
                if (ys[i] > ys[j]) {
                    f32 t0 = xs[i];
                    f32 t1 = ys[i];
                    xs[i] = xs[j];
                    ys[i] = ys[j];
                    xs[j] = t0;
                    ys[j] = t1;
                }
            }
        }
        mid = 0.5f * (a->y + b->y);
        for (k = 0; k < cnt; k++) {
            if (mid >= ys[k] && mid < ys[k + 1]) {
                return k & 1;
            }
        }
    }
    return 0;
}

/**
 * Triangulates the closed loop the player drew (a copy of the stroke points) into the triangle list
 * and flushes it for the GPU, so the region can be drawn and hit-tested.
 */
static s32 scissor_tess(void) {
    ScissorWork* w = GetScissorPtr();
    void* p = BattleAlloc(w->stars.count * 8);
    memcpy(p, w->strokePts, w->stars.count * 8);
    w->triCount = 0;
    tess(p, w->stars.count);
    DCFlushRange(w->tris, 0x3000);
    return 2;
}

static s32 scissor_cross(Pt* a, Pt* b, Pt* pts, s32 n);
/**
 * Splits polygon pts (n points) recursively along the first usable diagonal into triangles appended to the
 * triangle list; frees pts.
 */
static void tess(Pt* pts, s32 n) {
    ScissorWork* w = GetScissorPtr();
    s32 i, j, k;
    s32 n1, n2;
    Pt* a;
    Pt* b;
    if (n == 3) {
        ScissorTri* tri = &w->tris[w->triCount];
        for (k = 0; k < 3; k++) {
            tri->x[k] = pts[k].x;
            tri->y[k] = pts[k].y;
        }
        w->triCount++;
        BattleFree(pts);
        return;
    }
    for (i = 0; i < n; i++) {
        for (j = 2; j < n - 1; j++) {
            if (scissor_cross(&pts[i], &pts[(i + j) % n], pts, n) == 1) {
                n1 = j + 1;
                a = BattleAlloc(n1 * 8);
                for (k = 0; k < n1; k++) {
                    a[k] = pts[(i + k) % n];
                }
                n2 = n - j + 1;
                b = BattleAlloc(n2 * 8);
                b[0] = pts[i];
                for (k = 0; k < n2 - 1; k++) {
                    b[k + 1] = pts[(i + j + k) % n];
                }
                BattleFree(pts);
                tess(a, n1);
                tess(b, n2);
                return;
            }
        }
    }
    {
        ScissorTri* tri = &w->tris[w->triCount];
        for (k = 0; k < 3; k++) {
            tri->x[k] = pts[k].x;
            tri->y[k] = pts[k].y;
        }
        w->triCount++;
        BattleFree(pts);
    }
}

/**
 * Damage function of Art Attack: the power scissor_damage worked out for the target enemy (0 to 3),
 * 0 for anything else.
 */
s32 weaponGetPower_Scissor(BattleUnit* attacker, BattleWeapon* weapon, BattleUnit* target, BattleUnitPart* part) {
    ScissorWork* w = GetScissorPtr();
    s32 i;
    if (target == NULL) {
        return 0;
    }
    if ((s32)(u8)target->alliance == 1) {
        for (i = 0; i < 16; i++) {
            if (w->unitIds[i] == BtlUnit_GetUnitId(target)) {
                return w->power[i];
            }
        }
    }
    return 0;
}

static void star_disp2D(CameraId camera, void* param);

/**
 * Event helper for the star: rises out of Mario spinning, flies up off screen,
 * then drops in as the drawing cursor and stays there.
 * Keeps a four-point trail and registers star_disp2D from the cursor phase on.
 */
static s32 star_control(EventEntry* evt, BOOL first) {
    ScissorWork* w = GetScissorPtr();
    struct ScissorStars* t = &w->stars;
    BattleUnit* mario = BattleGetMarioPtr(_battleWorkPointer);
    s32 i;

    if (!(gp->retraceCount & 3)) {
        for (i = 3; i > 0; i--) {
            t->starX[i] = t->starX[i - 1];
            t->starY[i] = t->starY[i - 1];
        }
        t->starX[0] = t->headX;
        t->starY[0] = t->headY;
    }
    switch (w->phase) {
        case 1:
            w->phase = 2;
            w->phaseTimer = 0;
            w->eff = effStarStoneEntry(3, 0.0f, -1000.0f, 0.0f, 1.0f);
            BtlUnit_GetPos(mario, &w->pos.x, &w->pos.y, &w->pos.z);
            w->pos.y += mario->sizeMultiplier * (f32)mario->height + 37.0f;
            w->from = w->pos;
            w->to = w->pos;
            w->to.y += 50.0f;
            w->to.z += -1.0f;
            w->scale = (Vec){0.0f, 0.0f, 0.0f};
            w->rot = (Vec){0.0f, 0.0f, 0.0f};
        case 2:
            w->phaseTimer++;
            if (w->phaseTimer <= 100) {
                w->pos.x = intplGetValue(0, w->from.x, w->to.x, w->phaseTimer, 100);
                w->pos.y = intplGetValue(0, w->from.y, w->to.y, w->phaseTimer, 100);
                w->pos.z = intplGetValue(0, w->from.z, w->to.z, w->phaseTimer, 100);
                w->scale.x = w->scale.y = w->scale.z = intplGetValue(0, 0.0f, 2.0f, w->phaseTimer, 100);
            } else {
                w->pos.x = w->to.x;
                w->pos.y = w->to.y;
                w->pos.z = w->to.z;
                w->scale.x = w->scale.y = w->scale.z = 2.0f;
            }
            w->rot.y = intplGetValue(4, 0.0f, 2160.0f, w->phaseTimer, 120);
            if (w->phaseTimer >= 120) {
                w->phase = 3;
                w->phaseTimer = 0;
                w->from = w->pos;
                w->to.y = 300.0f;
            }
            break;
        case 3:
            w->phaseTimer++;
            w->pos.y = intplGetValue(1, w->from.y, w->to.y, w->phaseTimer, 60);
            if (w->phaseTimer >= 60) {
                w->phase = 4;
                w->phaseTimer = 0;
                w->pos = (Vec){0.0f, 300.0f, 0.0f};
                w->scale = (Vec){1.0f, 1.0f, 1.0f};
                w->rot = (Vec){0.0f, 0.0f, 0.0f};
                w->from.y = w->pos.y;
                w->to.y = 0.0f;
                t->headX = w->pos.x;
                t->headY = w->pos.y;
                for (i = 0; i < 4; i++) {
                    t->starX[i] = 0.0f;
                    t->starY[i] = -1000.0f;
                }
            }
            break;
        case 4:
            w->phaseTimer++;
            w->pos.y = intplGetValue(4, w->from.y, w->to.y, w->phaseTimer, 60);
            t->headX = w->pos.x;
            t->headY = w->pos.y;
            if (w->phaseTimer >= 60) {
                w->phase = 5;
                w->phaseTimer = 0;
            }
            break;
        case 5:
        case 6:
            break;
    }
    if (w->eff) {
        EffStarStoneWork* e = w->eff->userdata;
        if (w->phase >= 4) {
            e->position.x = 0.0f;
            e->position.y = -1000.0f;
            e->position.z = 0.0f;
        } else {
            e->position.x = w->pos.x;
            e->position.y = w->pos.y;
            e->position.z = w->pos.z;
        }
        e->spinY = w->rot.x;
        e->rotY = w->rot.y;
        e->tiltZ = w->rot.z;
        e->scale = 1.5f * w->scale.x;
    }
    if (w->phase >= 4 && w->phase <= 6) {
        dispEntry(CAMERA_2D, 0.0f, 2, star_disp2D, NULL);
    }
    return 0;
}

/** Draws the drawing cursor with its four fading trail copies. */
static void star_disp2D(CameraId camera, void* param) {
    ScissorWork* w = GetScissorPtr();
    if (w->phase >= 2 && w->phase <= 6) {
        star_disp2D_sub(0, 255);
        star_disp2D_sub(1, 192);
        star_disp2D_sub(2, 128);
        star_disp2D_sub(3, 64);
        star_disp2D_sub(4, 32);
    }
}

// FAKE: inlining off (FAKES.md); without it star_disp2D_sub is inlined into star_disp2D (28 -> 410 instructions)
#pragma dont_inline on
/**
 * Draws star idx (0 the cursor, 1-4 the trail) as the Art Attack icon at the given alpha;
 * once time is up (phase 6) fades them all out over 30 frames.
 */
static void star_disp2D_sub(s32 idx, s32 alpha) {
    ScissorWork* w = GetScissorPtr();
    Mtx rotMtx;
    Mtx transMtx;
    Mtx rotX;
    Mtx rotY;
    Mtx rotZ;
    Mtx scaleMtx;
    struct ScissorStars* s = &w->stars;
    f32 x, y, z;
    GXColor col;
    if (w->phase >= 6) {
        w->phaseTimer++;
        if (w->phaseTimer > 30) {
            w->phaseTimer = 30;
        }
        alpha = (s32)intplGetValue(0, (f32)(u8)alpha, 0.0f, w->phaseTimer, 30);
    }
    col = (GXColor){0xFF, 0xFF, 0xFF, 0x00};
    col.a = alpha;
    if (idx == 0) {
        x = s->headX;
        y = s->headY;
        z = 0.0f;
    } else {
        z = 0.0f;
        x = s->starX[idx - 1];
        y = s->starY[idx - 1];
    }
    PSMTXTrans(transMtx, x, y - 20.0f, z);
    PSMTXScale(scaleMtx, w->scale.x, w->scale.y, w->scale.z);
    PSMTXRotRad(rotX, 0x78, 0.017453292f * w->rot.x);
    PSMTXRotRad(rotY, 0x79, 0.017453292f * w->rot.y);
    PSMTXRotRad(rotZ, 0x7A, 0.017453292f * w->rot.z);
    PSMTXConcat(rotZ, rotY, rotMtx);
    PSMTXConcat(rotX, rotMtx, rotMtx);
    PSMTXConcat(scaleMtx, rotMtx, rotMtx);
    PSMTXConcat(transMtx, rotMtx, rotMtx);
    iconDispGxCol(rotMtx, ICON_DISP_2D, ICON_19C, col);
}
#pragma dont_inline reset

/** Returns the frames left on the drawing timer in args[0]; at 59 or less also starts the star fade. */
static s32 scissor_timer_get(EventEntry* evt) {
    ScissorWork* w = GetScissorPtr();
    EvtWord* args = evt->args;
    if (w->timer <= 59) {
        w->phase = 6;
    }
    evtSetValue(evt, args[0], w->timer);
    return 2;
}

/**
 * The drawing timer: slides the timer in, counts down the 959-frame limit,
 * slides it back out at 59 frames left and finishes when it reaches 0.
 */
static s32 scissor_timer_main(void) {
    ScissorWork* w = GetScissorPtr();
    switch (w->state) {
        case 0:
            w->timerX = 320.0f;
            w->timerY = 185.0f;
            w->state = 5;
            w->step = 0;
        case 5:
            w->timerX = intplGetValue(4, 320.0f, 120.0f, w->step, 15);
            w->step++;
            if (w->step > 15) {
                w->state = 10;
            }
            break;
        case 10:
            w->timer--;
            if (w->timer <= 59) {
                w->state = 15;
                w->step = 0;
            }
            break;
        case 15:
            w->timerX = intplGetValue(4, 120.0f, 320.0f, w->step, 15);
            w->step++;
            if (w->step > 15) {
                w->state = 20;
            }
            w->timer--;
            if (w->timer < 0) {
                w->timer = 0;
            }
            break;
        case 20:
            w->timer--;
            if (w->timer < 0) {
                w->timer = 0;
                return 2;
            }
            break;
    }
    return 0;
}

static void scissor_disp_control(CameraId camera, void* param);
static void scissor_disp_region(CameraId camera, void* param);

/**
 * The player's drawing: moves the star with the Control Stick, records a point every 6 frames,
 * and finishes once the newest segment crosses an earlier one, closing the loop and capturing the screen.
 * Also finishes when time runs out; until then draws the line each frame.
 */
static s32 scissor_control(EventEntry* evt, BOOL first) {
    ScissorWork* w = GetScissorPtr();
    Pt* buf = (Pt*)w->strokePts;
    Pt* p;
    f32 ox, oy;
    s32 i, k;
    if (first) {
        w->stars.count = 0;
        w->stars.prevStickY = 0.0f;
        w->stars.prevStickX = 0.0f;
        w->stars.stickY = 0.0f;
        w->stars.stickX = 0.0f;
        w->stars.unusedA0 = 0;
        w->stars.velX = 0.0f;
        w->stars.velY = 0.0f;
        memset(buf, 0, 0x1000);
        w->flags &= ~1;
    }
    w->stars.prevStickX = w->stars.stickX;
    w->stars.prevStickY = w->stars.stickY;
    w->stars.stickX = (f32)keyGetStickX(0);
    w->stars.stickY = (f32)keyGetStickY(0);
    sqrt(w->stars.prevStickX * w->stars.prevStickX + w->stars.prevStickY * w->stars.prevStickY);
    if ((f32)sqrt(w->stars.stickX * w->stars.stickX + w->stars.stickY * w->stars.stickY) > 42.0f) {
        w->stars.velX += w->stars.stickX / 50.0f;
        w->stars.velY += w->stars.stickY / 50.0f;
    }
    w->stars.velX *= 0.86f;
    w->stars.velY *= 0.86f;
    w->stars.headX += w->stars.velX;
    w->stars.headY += w->stars.velY;
    if (w->stars.headX < -300.0f) {
        w->stars.headX = -300.0f;
    }
    if (w->stars.headX > 300.0f) {
        w->stars.headX = 300.0f;
    }
    if (w->stars.headY < -200.0f) {
        w->stars.headY = -200.0f;
    }
    if (w->stars.headY > 200.0f) {
        w->stars.headY = 200.0f;
    }
    if (w->timer <= 59) {
        w->phase = 6;
        return 2;
    }
    if (gp->retraceCount % 6 == 0 && w->stars.count < 0x200) {
        if (w->stars.lastX != w->stars.headX || w->stars.lastY != w->stars.headY) {
            if (__fabs(w->stars.headX - w->stars.lastX) >= 5.0 || __fabs(w->stars.headY - w->stars.lastY) >= 5.0) {
                psndSFXOn("SFX_BTL_SAC_KAKONDEPON1");
            }
            buf[w->stars.count].x = w->stars.headX;
            buf[w->stars.count].y = w->stars.headY;
            w->stars.lastX = w->stars.headX;
            w->stars.lastY = w->stars.headY;
            w->stars.count++;
        }
    }
    if (w->stars.count > 3) {
        for (i = 0; i < w->stars.count - 3; i++) {
            p = &buf[i];
            if (scissor_intersection(p[0].x, p[0].y, p[1].x, p[1].y, buf[w->stars.count - 2].x, buf[w->stars.count - 2].y,
                                     buf[w->stars.count - 1].x, buf[w->stars.count - 1].y, &ox, &oy)) {
                buf[i].x = buf[w->stars.count - 1].x = ox;
                buf[i].y = buf[w->stars.count - 1].y = oy;
                for (k = 0; k < i; k++) {
                    buf[k] = *p;
                }
                if (w->smart != NULL) {
                    smartFree(w->smart);
                    w->smart = NULL;
                }
                w->smart = smartAlloc(GXGetTexBufferSize(0x260, 0x1E0, 4, 0, 0), 1);
                dispEntry(CAMERA_2D, 0, 0.0f, scissor_capture, NULL);
                return 2;
            }
        }
    }
    dispEntry(CAMERA_2D, 0, 0.0f, scissor_disp_control, NULL);
    return 0;
}

#include "battle/battle_audience.h"
#include "evt/evt_cmd.h"
#include "battle/battle_database_common.h"
#include "version.h"

/**
 * Applies one closed loop: scores every enemy the loop covers (skipping KO'd, evasive,
 * untargetable and immune ones and some defense attributes) and hits each with Art Attack.
 * args[0] gets the rating level for the popup when every enemy was hit, else -1; the crowd cheers louder.
 */
static s32 scissor_damage(EventEntry* evt, BOOL first) {
    BattleWork* wp;
    BattleUnit* mario;
    BattleUnit* unit;
    ScissorWork* w;
    s32 aud;
    s32 i, hit;
    EvtWord* args;
    s32 n, ok;
    args = evt->args;
    wp = _battleWorkPointer;
    mario = BattleGetMarioPtr(wp);
    w = GetScissorPtr();
    n = 0;
    ok = 1;
    aud = BattleAudience_GetAudienceNum();
    hit = 0;
    for (i = 0; i < BATTLE_UNIT_MAX; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (unit != NULL && BtlUnit_GetBelong(unit) == 1) {
            BattleUnitPart* part = BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit));
            s32 res;
            if (BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL) != 1 && !(part->attributes & PART_ATTR_EVASIVE) && !(part->attributes & PART_ATTR_IMMUNE_TO_DAMAGE_OR_STATUS) &&
#if VERSION <= VERSION_DEMO_US
                !(part->attributes & PART_ATTR_NOT_TARGETABLE) && *(s8*)part->defenseAttr != 4) {
#else
                !(part->attributes & PART_ATTR_NOT_TARGETABLE) && *(s8*)part->defenseAttr != 4 && *(s8*)part->defenseAttr != 2) {
#endif
                scissor_damage_sub(unit, &res);
                w->unitIds[n] = i;
                w->power[n] = res;
                n++;
                if (res < 1) {
                    ok = 0;
                }
            }
        }
    }
    if (n == 0) {
        ok = 0;
    }
    for (i = 0; i < n; i++) {
        if (w->unitIds[i] != -1 && w->power[i] >= 1) {
            unit = BattleGetUnitPtr(wp, w->unitIds[i]);
            BattleCheckDamage(mario, unit, BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit)), (void*)&weapon_scissor, 0);
            hit = 1;
        }
    }
    if (ok == 1) {
        s32 v;
        w->cutCount++;
        v = w->cutCount + 1;
        if (v >= 7) {
            v = 6;
        }
        evtSetValue(evt, args[0], v);
    } else {
        evtSetValue(evt, args[0], -1);
    }
    if (hit == 1) {
        if (aud >= 1 && aud <= 49) {
            BattleAudienceSoundCallKind(1);
        }
        if (aud >= 50 && aud <= 99) {
            BattleAudienceSoundCallKind(1);
            BattleAudienceSoundHandBeat();
        }
        if (aud >= 100 && aud <= 149) {
            BattleAudienceSoundCallKind(2);
        }
        if (aud >= 150) {
            BattleAudienceSoundCallKind(2);
            BattleAudienceSoundHandBeat();
        }
        w->audienceVol += 20;
        if (w->audienceVol >= 100) {
            w->audienceVol = 100;
        }
        BattleAudienceSoundSetVol(4, w->audienceVol, 30);
    }
    return 2;
}

/**
 * Samples a 10x10 grid over the unit's cut box on screen
 * and sets *out to the power from the share inside the loop: 1 from 30%, 2 from 60%, 3 from 90%.
 */
static void scissor_damage_sub(BattleUnit* unit, s32* out) {
    Vec pos;
    Vec p;
    s32 i, j;
    s32 hits;
    f32 hw, hh, w, h, sign;
    f32 ratio;
    hits = 0;
    if (unit->attributeFlags & UNIT_ATTR_CEILING) {
        sign = -1.0f;
    } else {
        sign = 1.0f;
    }
    w = unit->cutWidth * unit->sizeMultiplier;
    h = unit->cutHeight * unit->sizeMultiplier;
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x = unit->cutBaseOffset.x * unit->sizeMultiplier + pos.x;
    pos.y = sign * (unit->cutBaseOffset.y * unit->sizeMultiplier) + pos.y;
    hh = 0.5f * -h;
    hw = 0.5f * w;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            p.x = pos.x - hw + ((f32)i * w) / 9.0f;
            p.y = sign * (hh + ((f32)j * h) / 9.0f) + pos.y;
            p.z = pos.z;
            btlGetScreenPoint(&p, &p);
            if (scissor_damage_sub2(p)) {
                hits++;
            }
        }
    }
    ratio = (f32)hits / 100.0f;
    *out = 0;
    if (ratio >= 0.3f) {
        *out = 1;
    }
    if (ratio >= 0.6f) {
        *out = 2;
    }
    if (ratio >= 0.9f) {
        *out = 3;
    }
}

// FAKE: inlining off (FAKES.md); without it scissor_damage_sub2 is inlined into scissor_damage_sub (154 -> 217 instructions)
#pragma dont_inline on
/** Whether screen point pt is inside any triangle of the drawn loop. */
static s32 scissor_damage_sub2(Vec pt) {
    ScissorWork* w = GetScissorPtr();
    s32 n = w->triCount;
    f32 y0, x0;
    f32* q;
    f32 c[3];
    s32 i, j;
    for (i = 0; i < n; i++) {
        ScissorTri* t = &w->tris[i];
        for (j = 0; j < 3; j++) {
            s32 k = (j + 1) % 3;
            // FAKE: y[j] read through q = &x[j] (index = the x-to-y distance in floats) keeps the target register order (t->y[j] / t->x[j]: 99.65%)
            q = &t->x[j];
            y0 = q[(offsetof(ScissorTri, y) - offsetof(ScissorTri, x)) / sizeof(f32)];
            x0 = q[0];
            c[j] = (pt.x - x0) * (t->y[k] - y0) - (pt.y - y0) * (t->x[k] - x0);
        }
        if ((c[0] > 0.0f && c[1] > 0.0f && c[2] > 0.0f) || (c[0] < 0.0f && c[1] < 0.0f && c[2] < 0.0f)) {
            return 1;
        }
    }
    return 0;
}

#pragma dont_inline reset
/** Returns 1 in args[0] when the loop drawn off-screen covered any pixels (scissor_disp_region), else 0. */
static s32 scissor_ofscreen_ok(EventEntry* evt) {
    EvtWord* args = evt->args;
    ScissorWork* w = GetScissorPtr();
    if (w->flags & 1) {
        evtSetValue(evt, args[0], 1);
    } else {
        evtSetValue(evt, args[0], 0);
    }
    return 2;
}

/** Copies the screen into the capture texture when a loop closes, for the cut-out image. */
static void scissor_capture(CameraId camera, void* param) {
    ScissorWork* w = GetScissorPtr();
    GXSetTexCopySrc(0, 0, 0x260, 0x1E0);
    GXSetTexCopyDst(0x260, 0x1E0, 4, 0);
    GXCopyTex(*(void**)w->smart, 0);
    GXPixModeSync();
}

/** Draws the player's line in shifting rainbow colours. The demos also outline each enemy's cut box in red. */
static void scissor_disp_control(CameraId camera, void* param) {
    ScissorWork* w = GetScissorPtr();
    f32* pts = (f32*)w->strokePts;
    s32 i;
#if VERSION <= VERSION_DEMO_US
    BattleWork* wp;
    BattleUnit* unit;
    Vec pos;
    Vec a;
    Vec b;
    f32 width;
    f32 height;
    f32 hw;
    f32 hh;
    f32 sign;
#endif
    w->blinkTimer = w->blinkTimer + 1;
    if (w->blinkTimer >= 60) {
        w->blinkTimer -= 60;
    }
    if (w->blinkTimer <= 29) {
        intplGetValue(0, 0.0f, 255.0f, w->blinkTimer, 29);
    } else {
        intplGetValue(0, 255.0f, 0.0f, w->blinkTimer - 30, 59);
    }
    GXSetCullMode(0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
    GXSetTevOp(0, 4);
    GXLoadPosMtxImm(camGetPtr(camera)->view, 0);
    GXSetCurrentMtx(0);
    GXSetLineWidth(16, 0);
    for (i = 0; i < w->stars.count - 1; i++) {
        GXColor hsv = {0x00, 0xFF, 0xFF, 0xFF};
        hsv.r = (gp->retraceCount + i * 2) % 127 * 2;
        GXSetChanMatColor(4, HSV2RGB(hsv));
        GXBegin(0xA8, 0, 2);
        GXPosition3f32(pts[i * 2], pts[i * 2 + 1], 0.0f);
        GXPosition3f32(pts[i * 2 + 2], pts[i * 2 + 3], 0.0f);
    }
#if VERSION <= VERSION_DEMO_US
    // The demo outlines each enemy's cut box in red (scissor_damage's box).
    wp = _battleWorkPointer;
    GXSetChanMatColor(4, (GXColor){0xFF, 0x00, 0x00, 0xFF});
    for (i = 0; i < BATTLE_UNIT_MAX; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (unit == NULL)
            continue;
        if (BtlUnit_GetBelong(unit) != 1)
            continue;
        if (BtlUnit_CheckStatus(unit, STATUS_INSTANT_KILL))
            continue;
        if (BtlUnit_GetPartsPtr(unit, BtlUnit_GetBodyPartsId(unit))->attributes & PART_ATTR_NOT_TARGETABLE)
            continue;
        if (unit->attributeFlags & UNIT_ATTR_CEILING) {
            sign = -1.0f;
        } else {
            sign = 1.0f;
        }
        width = unit->cutWidth * unit->sizeMultiplier;
        height = unit->cutHeight * unit->sizeMultiplier;
        BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
        pos.x = unit->cutBaseOffset.x * unit->sizeMultiplier + pos.x;
        hw = 0.5f * width;
        hh = 0.5f * height;
        pos.y = sign * (unit->cutBaseOffset.y * unit->sizeMultiplier) + pos.y;
        a.x = pos.x - hw;
        a.y = pos.y + hh;
        a.z = pos.z;
        btlGetScreenPoint(&a, &a);
        b.x = pos.x + hw;
        b.y = pos.y + hh;
        b.z = pos.z;
        btlGetScreenPoint(&b, &b);
        GXBegin(0xA8, 0, 2);
        GXPosition3f32(a.x, a.y, 0.0f);
        GXPosition3f32(b.x, b.y, 0.0f);
        a.x = pos.x + hw;
        a.y = pos.y + hh;
        a.z = pos.z;
        btlGetScreenPoint(&a, &a);
        b.x = pos.x + hw;
        b.y = pos.y - hh;
        b.z = pos.z;
        btlGetScreenPoint(&b, &b);
        GXBegin(0xA8, 0, 2);
        GXPosition3f32(a.x, a.y, 0.0f);
        GXPosition3f32(b.x, b.y, 0.0f);
        a.x = pos.x + hw;
        a.y = pos.y - hh;
        a.z = pos.z;
        btlGetScreenPoint(&a, &a);
        b.x = pos.x - hw;
        b.y = pos.y - hh;
        b.z = pos.z;
        btlGetScreenPoint(&b, &b);
        GXBegin(0xA8, 0, 2);
        GXPosition3f32(a.x, a.y, 0.0f);
        GXPosition3f32(b.x, b.y, 0.0f);
        a.x = pos.x - hw;
        a.y = pos.y - hh;
        a.z = pos.z;
        btlGetScreenPoint(&a, &a);
        b.x = pos.x - hw;
        b.y = pos.y + hh;
        b.z = pos.z;
        btlGetScreenPoint(&b, &b);
        GXBegin(0xA8, 0, 2);
        GXPosition3f32(a.x, a.y, 0.0f);
        GXPosition3f32(b.x, b.y, 0.0f);
    }
#endif
}

/** Registers scissor_disp_region on the off-screen camera to draw the closed loop. */
static s32 scissor_offscreen(void) {
    GetScissorPtr();
    dispEntry(CAMERA_OFFSCREEN2, 0.0f, 1, scissor_disp_region, NULL);
    return 2;
}

/**
 * Draws the closed loop's triangles off-screen, textured with the captured screen,
 * records whether anything was drawn, and gives the bounding box to the "ofs" off-screen used for the cut-out
 * image.
 */
static void scissor_disp_region(CameraId camera, void* param) {
    ScissorWork* w = GetScissorPtr();
    GXTexObj texObj;
    Mtx mtx;
    u16 left, top, right, bottom;
    s32 i;
    ScissorTri* t;
    sysWaitDrawSync();
    GXClearBoundingBox();
    GXSetCullMode(0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXInitTexObj(&texObj, *(void**)w->smart, 0x260, 0x1E0, 4, 0, 0, 0);
    GXInitTexObjLOD(&texObj, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    GXLoadTexObj(&texObj, 0);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    C_MTXLightOrtho(mtx, -240.0f, 240.0f, -304.0f, 304.0f, 0.5f, 0.5f, 0.5f, 0.5f);
    PSMTXConcat(mtx, camGetPtr(CAMERA_2D)->view, mtx);
    GXLoadTexMtxImm(mtx, 0x1E, 0);
    GXSetTexCoordGen2(0, 0, 0, 0x1E, 0, 0x7D);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 0, 0xFF);
    GXSetTevColorOp(0, 0, 0, 0, 1, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 1, 0);
    GXSetTevColorIn(0, 0xF, 0xF, 0xF, 8);
    GXSetTevAlphaIn(0, 7, 7, 7, 6);
    GXSetTevKAlphaSel(0, 0);
    GXLoadPosMtxImm(camGetPtr(CAMERA_2D)->view, 0);
    t = w->tris;
    GXBegin(0x90, 0, w->triCount * 3);
    for (i = 0; i < w->triCount; i++, t++) {
        GXPosition3f32(t->x[0], t->y[0], 0.0f);
        GXPosition3f32(t->x[1], t->y[1], 0.0f);
        GXPosition3f32(t->x[2], t->y[2], 0.0f);
    }
    sysWaitDrawSync();
    if (w->smart != NULL) {
        smartFree(w->smart);
        w->smart = NULL;
    }
    GXReadBoundingBox(&left, &top, &right, &bottom);
    if (left == 0x3FF && right == 0 && top == 0x3FF && bottom == 0) {
        w->flags &= ~1;
    } else {
        w->flags |= 1;
    }
    offscreenAddBoundingBox(offscreenNameToId("ofs"), left, top, right, bottom);
}

/** Sets up the work: the 959-frame timer, the stroke point and triangle buffers, the star at the centre. */
static s32 scissor_init(void) {
    ScissorWork* w = GetScissorPtr();
    memset(w, 0, 0x174);
    w->timer = 0x3BF;
    w->strokePts = BattleAlloc(0x1000);
    w->tris = BattleAlloc(0x3000);
    w->stars.headX = 0.0f;
    w->stars.headY = 0.0f;
    w->cutCount = 0;
    w->audienceVol = 0;
    return 2;
}

/** Cleanup when the move ends: deletes the star effect and frees the capture and the two buffers. */
static s32 scissor_end(void) {
    ScissorWork* w = GetScissorPtr();
    effDelete(((EffStarStoneWork*)w->eff->userdata)->dust);
    effDelete(w->eff);
    if (w->smart != NULL) {
        smartFree(w->smart);
        w->smart = NULL;
    }
    BattleFree(w->strokePts);
    BattleFree(w->tris);
    return 2;
}

/** Starts the star rising out of Mario (star_control). */
static s32 star_stone_appear(void) {
    ScissorWork* w = GetScissorPtr();
    w->phase = 1;
    return 2;
}

/** Waits until the star has dropped into place as the drawing cursor. */
static s32 wait_star_standby(void) {
    return GetScissorPtr()->phase == 5 ? 2 : 0;
}

/**
 * Attack event of Art Attack: after the star intro the player draws loops around enemies
 * until the timer runs out; each closed loop cuts out that part of the screen
 * and damages the enemies inside (scissor_damage).
 * Then pays the Star Power and gives each damaged enemy a finishing hit.
 */
EVT_BEGIN(marioAttackEvent_Scissor)
    // Art Attack's work is set up and the star's flight starts.
    CALL(scissor_init)
    BEGIN_SIBLING_EVENT
        CALL(star_control)
    END_SIBLING_EVENT
    // Crystal Star opening: Mario holds up the star item and the Crystal Star appears in stardust.
    CALL_CHILD(sac_start_camera_evt)
    WAIT_MS(500)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_SAC_START1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL_CHILD(sac_mario_item_on_evt)
    WAIT_MS(500)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_SAC_START2"), EVT_NULLPTR, 0, LW(11))
    CALL(star_stone_appear)
    BEGIN_SIBLING_EVENT
        CALL_CHILD(sac_start_stardust)
    END_SIBLING_EVENT
    WAIT_FRAMES(100)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_SAC_START3"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(evt_snd_sfxoff, LW(11))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(40)
    // Mario puts the item away and returns home, and the camera pulls back to show the whole stage.
    CALL_CHILD(sac_mario_item_on_end_evt)
    CALL_CHILD(sac_mario_back_home)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("M_I_Y"))
    BEGIN_SIBLING_EVENT
        WAIT_FRAMES(30)
        CALL(evt_btl_camera_set_mode, 0, 3)
#if VERSION <= VERSION_DEMO_US
        CALL(evt_btl_camera_set_moveto, 0, 75, 120, 600, 75, 70, 0, 30, 0)
#else
        CALL(evt_btl_camera_set_moveto, 0, 75, 105, 600, 75, 55, 0, 30, 0)
#endif
    END_SIBLING_EVENT
    // Once the star is in place as the drawing cursor, the timer runs, the crowd cheers and help shows.
    CALL(wait_star_standby)
    BEGIN_SIBLING_EVENT
        CALL(scissor_timer_main)
    END_SIBLING_EVENT
    BEGIN_SIBLING_EVENT
        CALL(sac_cheer, 1)
    END_SIBLING_EVENT
    CALL(sac_ac_help_on)
    LOOP(0)
        // Each pass: the screen is readied for a cut-out while the player draws; time running out ends it.
        SET_VALUE(LW(10), STRING("OFF_d_bom"))
        CALL(evt_paper_entry, LW(10))
        CALL(evt_offscreen_entry, STRING("ofs"))
        CALL(evt_img_entry, STRING("img"))
        CALL(evt_img_set_paper, STRING("img"), LW(10))
        CALL(evt_img_onoff, STRING("img"), 0)
        CALL(scissor_control)
        CALL(scissor_timer_get, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 59)
            CALL(evt_img_onoff, STRING("img"), 0)
            CALL(evt_img_set_shadow, STRING("img"), 0)
            CALL(evt_img_release, STRING("img"))
            CALL(evt_offscreen_delete, STRING("ofs"))
            CALL(evt_paper_delete, LW(10))
            GOTO(90)
        END_IF
        WAIT_FRAMES(1)
        // The drawn loop is closed and the area inside it is captured from the screen.
        CALL(scissor_tess)
        WAIT_FRAMES(1)
        CALL(scissor_offscreen)
        CALL(evt_img_alloc_capture, STRING("img"), 0, STRING("ofs"), 1, 0, 0, 0, 0)
        WAIT_FRAMES(1)
        CALL(scissor_ofscreen_ok, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            // The loop cuts that piece out and hurts the enemies inside; hitting them all earns a rating.
            CALL(evt_snd_sfxon, STRING("SFX_BTL_SAC_KAKONDEPON2"), 0)
            CALL(evt_img_onoff, STRING("img"), 1)
            CALL(evt_img_set_shadow, STRING("img"), 2)
            CALL(scissor_damage, LW(0))
            IF_INT_GREATER_OR_EQUAL(LW(0), 2)
                CALL(btlevtcmd_ACSuccessEffect, LW(0), 75, 100, -100)
            END_IF
            CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1"))
            CALL(evt_img_clear_virtual_point, STRING("img"))
            WAIT_FRAMES(60)
        END_IF
        // The cut-out is cleared before the next loop.
        CALL(evt_img_onoff, STRING("img"), 0)
        CALL(evt_img_set_shadow, STRING("img"), 0)
        CALL(evt_img_release, STRING("img"))
        CALL(evt_offscreen_delete, STRING("ofs"))
        CALL(evt_paper_delete, LW(10))
        CALL(scissor_timer_get, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 59)
            GOTO(90)
        END_IF
    END_LOOP
    LABEL(90)
    // Time's up: Mario pays the Star Power and each enemy that took damage gets the finishing hit.
    CALL(sac_ac_help_off)
    CALL(sac_cheer_end)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_WeaponAftereffect, LW(0))
    LABEL(95)
    IF_INT_EQUAL(LW(3), -1)
        GOTO(97)
    END_IF
    CALL(btlevtcmd_GetTotalDamage, LW(3), LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_scissor_finish), 256, LW(5))
    END_IF
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    GOTO(95)
    LABEL(97)
    // The camera resets and the drawing work is freed.
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(1000)
    CALL(scissor_end)
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()
