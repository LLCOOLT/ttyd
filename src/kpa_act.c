// Bowser interlude score display: coins and score counters.
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include "driver/dispdrv.h"
#include "mario/mario.h"
#include "mario/mario_pouch.h"
#include "memory.h"
#include <string.h>
#include "kpa_act.h"

typedef struct KpaScore {
    char str[8];
    u8 timer;
    u8 pad_9[3];
    Vec pos;
} KpaScore;

KpaScore* ksdp;
static USER_FUNC(kpa_score_disp_main);
/** Endless loop that runs kpa_score_disp_main once a frame, keeping the Super Bowser score popups moving. */
EVT_BEGIN(kpa_score_disp_evt)
    LOOP(0)
        CALL(kpa_score_disp_main)
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static void kpaScoreDisp(void);

/** Draws every active score popup as half-size white font text at its position. */
static void kpaScoreDisp(void) {
    Mtx m;
    Mtx scale;
    s32 i;
    PSMTXScale(scale, 0.5f, 0.5f, 0.5f);
    FontDrawStart();
    FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    for (i = 0; i < 50; i++) {
        if (ksdp[i].timer != 0) {
            PSMTXTrans(m, ksdp[i].pos.x, ksdp[i].pos.y, 300.0f);
            PSMTXConcat(m, scale, m);
            FontDrawStringMtx(m, ksdp[i].str);
        }
    }
}

/**
 * Script helper run every frame by kpa_score_disp_evt:
 * floats each active score popup up one unit, counts down its 30-frame timer and queues kpaScoreDisp.
 */
static USER_FUNC(kpa_score_disp_main) {
    s32 i;
    for (i = 0; i < 50; i++) {
        if (ksdp[i].timer != 0) {
            ksdp[i].pos.y += 1.0f;
            ksdp[i].timer--;
        }
    }
    dispEntry((CameraId)4, 0.0f, 2, (DispCallback)kpaScoreDisp, 0);
    return EVT_RETURN_DONE;
}

/**
 * Script helper for the Super Bowser stages: starts kpa_score_disp_evt as a child that copies the caller's LW/LF
 * variables and owner, and allocates and clears the 50 score popup slots on the map heap. No arguments.
 */
USER_FUNC(kpa_score_disp_init) {
    EventEntry* e;
    u32 i;
    e = evtEntryType(kpa_score_disp_evt, event->priority, 0, event->type);
    e->unitId = event->unitId;
    e->ownerNPC = event->ownerNPC;
    for (i = 0; i < 16; i++) {
        e->lwData[i] = event->lwData[i];
    }
    for (i = 0; i < 3; i++) {
        e->lfData[i] = event->lfData[i];
    }
    e->uwBase = event->uwBase;
    e->ufBase = event->ufBase;
    ksdp = _mapAlloc(0x4B0);
    for (i = 0; (s32)i < 50; i++) {
        ksdp[i].str[0] = 0;
        ksdp[i].timer = 0;
        ksdp[i].pos = (Vec){0.0f, 0.0f, 0.0f};
    }
    return EVT_RETURN_DONE;
}

/**
 * Adds Super Bowser coins: every 100 coins also gives 1000 points, and each pickup scores 500 per coin,
 * capped at
 * 10000. Called when Bowser touches a coin (evt_mobj).
 */
void kpaAddCoin(s32 coins) {
    s32 score;
    if (pouchAddKpaCoin(coins)) {
        pouchAddKpaScore(1000);
    }
    score = coins * 500;
    if (score > 10000) {
        score = 10000;
    }
    pouchAddKpaScore(score);
}

/**
 * Takes the first free popup slot and shows score (without leading zeros) centred 20 units above pos for 30
 * frames; does nothing when all 50 are in use.
 */
static inline void kpaSetScoreStr(s32 score, Vec* pos) {
    char* p;
    char* str;
    s32 t;
    s8 d[5];
    s32 j;
    s32 n;
    s32 i;
    for (i = 0; i < 50; i++) {
        if (ksdp[i].timer == 0) {
            d[0] = score / 10000;
            t = score % 10000;
            d[1] = t / 1000;
            t %= 1000;
            d[2] = t / 100;
            t %= 100;
            d[3] = t / 10;
            d[4] = t % 10;
            p = ksdp[i].str;
            str = ksdp[i].str;
            n = 0;
            for (j = 0; j < 5; j++) {
                if (n != 0 || d[j] != 0) {
                    *p++ = d[j] + '0';
                    n++;
                }
            }
            str[n] = 0;
            ksdp[i].timer = 30;
            ksdp[i].pos.x = pos->x - 0.5f * (10.0f * (f32)strlen(ksdp[i].str));
            ksdp[i].pos.y = 20.0f + pos->y;
            ksdp[i].pos.z = 0.0f;
            break;
        }
    }
}

/**
 * Same as kpaAddCoin, and also shows the points scored as a popup above pos.
 * Nothing in the decompiled code calls it.
 */
void kpaAddCoinPos(s32 coins, Vec* pos) {
    s32 score;
    if (pouchAddKpaCoin(coins)) {
        pouchAddKpaScore(1000);
    }
    score = coins * 500;
    if (score > 10000) {
        score = 10000;
    }
    pouchAddKpaScore(score);
    kpaSetScoreStr(score, pos);
}

/** Adds score points (capped at 10000 per call) to the Super Bowser total. */
void kpaAddScore(s32 score) {
    if (score > 10000) {
        score = 10000;
    }
    pouchAddKpaScore(score);
}

/**
 * Adds score points (capped at 10000 per call) to the Super Bowser total and shows them as a popup above pos.
 * Used for stomped enemies (npcdrv) and power-ups (evt_mobj).
 */
void kpaAddScorePos(s32 score, Vec* pos) {
    s32 sc = score;
    if (score > 10000) {
        sc = 10000;
    }
    pouchAddKpaScore(sc);
    kpaSetScoreStr(sc, pos);
}

/** Script helper: switches the player character's (Bowser's) animation to the pose named by args[0]. */
USER_FUNC(kpa_chg_pose) {
    marioChgPose((const char*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}
