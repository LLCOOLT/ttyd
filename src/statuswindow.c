#include "statuswindow.h"
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "driver/dispdrv.h"
#include "driver/icondrv.h"
#include "driver/seqdrv.h"
#include "driver/swdrv.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "memory.h"
#include "pmario_sound.h"
#include <string.h>

extern GlobalWork* gp;
double cos(double);

typedef struct SVal {
    s16 hp;         // 0x0
    s16 maxHp;      // 0x2
    s16 fp;         // 0x4
    s16 maxFp;      // 0x6
    s16 party;      // 0x8
    s16 partyHp;    // 0xA
    s16 partyMaxHp; // 0xC
    s16 starPoints; // 0xE
    s16 coins;      // 0x10
    s16 ap;         // 0x12
    s16 maxAp;      // 0x14
    s16 pad16;      // 0x16
} SVal;

typedef struct SWork {
    u8 field_0x0[0x4];  // 0x0
    u16 flags;          // 0x4
    u8 align_0x6[2];    // 0x6
    f32 timer;          // 0x8
    f32 duration;       // 0xC
    f32 t;              // 0x10
    f32 tStart;         // 0x14
    f32 tEnd;           // 0x18
    f32 speed;          // 0x1C
    f32 x;              // 0x20
    f32 y;              // 0x24
    u8 field_0x28[0x8]; // 0x28
    f32 openX;          // 0x30
    f32 openY;          // 0x34
    u8 field_0x38[0x8]; // 0x38
    f32 closeX;         // 0x40
    f32 closeY;         // 0x44
    u8 field_0x48[0x8]; // 0x48
    SVal cur;           // 0x50
    Vec prevPos;        // 0x68
    s32 idle;           // 0x74
    s32 forceTimer;     // 0x78
    s32 forcedClose;    // 0x7C
    s32 blink;          // 0x80
    s32 pendingBlink;   // 0x84
    s32 blinkTimer;     // 0x88
} SWork;

typedef struct alwaysDtEntry {
    s16 xpos;   // 0x0
    s16 ypos;   // 0x2
    u16 iconId; // 0x4
    f32 scale;  // 0x8
} alwaysDtEntry;

//.data
alwaysDtEntry alwaysDt[] = {
    { 108, 40, 464, 1.0f }, // red hp banner
    { 38, 40, 419, 1.0f },  // mario hp icon
    { 124, 34, 472, 1.0f }, // division sign
    { 288, 40, 465, 1.0f }, // orange fp banner
    { 220, 40, 433, 1.0f }, // fp icon
    { 305, 34, 472, 1.0f }, // division sign
    { 492, 40, 467, 1.0f }, // green item banner
    { 400, 40, 435, 1.0f }, // star points
    { 490, 40, 436, 1.0f }, // coin icon
    { 422, 34, 470, 1.0f }, // "x"
    { 512, 34, 470, 1.0f }, // "x"
    { 360, 76, 466, 1.0f }, // blue sp banner
    { 220, 80, 434, 0.9f }  // star
};

//.sdata
alwaysDtEntry partysDt[] = {
    { 108, 76, 464, 1.0f },
    { 38, 80, 420, 1.0f },
    { 124, 70, 472, 1.0f },
};
u16 party_icon[8] = { 0x1A4, 0x1A4, 0x1A5, 0x1A6, 0x1A7, 0x1AE, 0x1AF, 0x1B0 };
u16 gauge_back[8] = { 0x1B7, 0x1B8, 0x1B9, 0x1BA, 0x1BB, 0x1BC, 0x1BD, 0x1BE };
u16 gauge_wakka[16] = { 0x1C0, 0x1C1, 0x1C2, 0x1C3, 0x1C4, 0x1C5, 0x1C6, 0x1C7,
                        0x1C8, 0x1C9, 0x1CA, 0x1CB, 0x1CC, 0x1CD, 0x1CE, 0x1CF };

//.sbss
static SWork* wp;

void statusWinDisp(CameraId camId, void* param);
void gaugeDisp(s32 sp, f32 x, f32 y);
void statusGetValue(SVal* values);
BOOL valueCheck(void);
void valueUpdate(void);
void statusWinOpen(void);
void statusWinClose(void);
BOOL statusWinCheck(void);

void statusWinInit(void) {
    wp = __memAlloc(HEAP_DEFAULT, sizeof(SWork));
    memset(wp, 0, sizeof(SWork));
    wp->speed = 1.0f;
    wp->openX = -304.0f;
    wp->openY = 208.0f;
    wp->closeX = -304.0f;
    wp->closeY = 334.0f;
    wp->idle = 0;
    wp->forceTimer = 0;
    wp->flags &= ~0xA;
    wp->flags |= 5;
}

void statusWinReInit(void) {
    wp->idle = 0;
    wp->forceTimer = 0;
    if (wp->flags & 0x10) {
        wp->flags &= ~0x10;
        wp->flags &= ~0xA;
        wp->flags |= 5;
    } else if (wp->flags & 1) {
        wp->flags &= ~0xA;
        wp->flags |= 5;
    }
    if (wp->flags & 0x20) {
        wp->flags &= ~0x20;
        wp->flags |= 0xA;
        wp->flags &= ~5;
    } else if (wp->flags & 2) {
        wp->flags |= 0xA;
        wp->flags &= ~5;
    }
}

void statusWinMain(void) {
    MarioWork* mario;
    f32 t, inv;

    mario = marioGetPtr();
    if (mario->characterId) {
        wp->flags = 2;
        wp->duration = 1.0f;
        wp->timer = 1.0f;
        wp->tEnd = 0.0f;
        wp->t = 0.0f;
        return;
    }
    if (!strcmp(gp->currentAreaName, "yuu")) {
        return;
    }
    switch (seqGetSeq()) {
        case 2:
        case 3:
            if ((marioChkCtrl() ? FALSE : TRUE) || (marioChkKey() ? FALSE : TRUE) || !(mario->flags & 1)) {
                if (statusWinCheck()) {
                    statusWinClose();
                }
                valueCheck();
                wp->idle = 0;
                wp->forceTimer = 0;
            } else {
                if (VECDistance(&wp->prevPos, &mario->position) < 1.0f) {
                    wp->idle++;
                    if (wp->idle > gp->framerate * 10) {
                        wp->idle = gp->framerate * 10;
                        if (!wp->forcedClose && !wp->forceTimer && !statusWinCheck()) {
                            statusWinOpen();
                            wp->flags |= 0x100;
                        }
                    }
                } else {
                    wp->idle = 0;
                    wp->forcedClose = 0;
                    if (!wp->forceTimer && statusWinCheck()) {
                        statusWinClose();
                    }
                }
                if (mario->field_0x248 & 0x10) {
                    if (!statusWinCheck()) {
                        statusWinOpen();
                        wp->forceTimer = gp->framerate * 10;
                        psndSFXOn((const char*)0x2A);
                        wp->flags |= 0x100;
                    } else {
                        statusWinClose();
                        wp->forceTimer = gp->framerate * 10;
                        wp->forcedClose = 1;
                        psndSFXOn((const char*)0x2B);
                    }
                }
                if (valueCheck()) {
                    wp->forceTimer = gp->framerate * 2;
                    if (!statusWinCheck()) {
                        statusWinOpen();
                    }
                }
            }
            if (wp->forceTimer) {
                wp->forceTimer--;
            }
            wp->prevPos = mario->position;
            if (wp->flags & 0x10) {
                wp->flags &= ~0xA;
            }
            if (wp->flags & 0x20) {
                wp->flags &= ~5;
            }
            break;
        case 4:
            break;
        default:
            if (statusWinCheck()) {
                statusWinClose();
            }
            break;
    }
    if (wp->flags & 4 || wp->flags & 8 || wp->flags & 0x40 || wp->flags & 0x80) {
        wp->tStart = wp->t;
        wp->tEnd = (wp->flags & 0x44) ? 1.0f : 0.0f;
        wp->timer = 0.0f;
        wp->duration = (wp->flags & 0x44) ? 16.0f / wp->speed : 28.0f / wp->speed;
        wp->flags &= ~4;
        wp->flags &= ~8;
        wp->flags &= ~0x40;
        wp->flags &= ~0x80;
    }
    wp->timer += 1.0f;
    if (wp->timer >= wp->duration) {
        wp->timer = wp->duration;
        wp->t = wp->tEnd;
        if (wp->t == 0.0f) {
            wp->flags &= ~0x100;
        }
    } else {
        inv = (f32)cos(3.1415927f * wp->timer / wp->duration);
        wp->t = wp->tStart + (wp->tEnd - wp->tStart) * (1.0f - inv) / 2.0f;
    }
    t = wp->t;
    inv = 1.0f - t;
    wp->x = wp->openX * t + wp->closeX * inv;
    wp->y = wp->openY * t + wp->closeY * inv;
    valueUpdate();
    if (!(wp->flags & 0x1000)) {
        dispEntry(CAMERA_2D, 0, 500.0f, statusWinDisp, NULL);
    }
}

void gaugeDisp(s32 sp, f32 x, f32 y) {
    s32 i;
    s32 max;
    s32 full;
    s32 part;
    Vec pos;
    Vec pos2;

    max = 0;
    for (i = 0; i < sizeof(gauge_back) / sizeof(gauge_back[0]); i++) {
        if (*(u16*)&pouchGetPtr()->mStarPowersObtained & (1 << i)) {
            max += 100;
        }
    }
    if (sp > max) {
        sp = max;
    }
    if (sp < 0) {
        sp = 0;
    }
    full = sp / 100;
    part = sp % 100;
    part = part * 15 / 99;
    if (sp % 100 && sp && !part) {
        part = 1;
    }
    if (part) {
        pos.x = x + (f32)(full * 32);
        pos.y = y;
        pos.z = 0.0f;
        iconDispGx(&pos, 0x10, gauge_wakka[part], 1.0f);
    }
    y = 12.0f + y;
    for (i = 0; i < sizeof(gauge_back) / sizeof(gauge_back[0]); i++) {
        if (!(*(u16*)&pouchGetPtr()->mStarPowersObtained & (1 << i))) {
            break;
        }
        pos2.x = x + (f32)(i * 32);
        pos2.y = y;
        pos2.z = 0.0f;
        iconDispGx(&pos2, 0x10, i < full ? gauge_back[i] : 0x1BF, 1.0f);
    }
}

static inline void numDisp(f32 x, f32 y, s32 value, BOOL small) {
    Mtx m;
    MTXTrans(m, x, y, 0.0f);
    iconNumberDispGx(m, value, small, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
}

void statusWinDisp(CameraId camId, void* param) {
    alwaysDtEntry* e;
    s32 i;
    s32 blinkOn;
    s32 blink;
    f32 x, y, y2;
    Mtx m, s;
    Mtx m2, s2;

    x = wp->x;
    y = wp->y;
    blinkOn = 1;
    if (wp->blinkTimer > 0) {
        wp->blinkTimer--;
        blinkOn = (wp->blinkTimer % 16) >= 6;
    }

    e = alwaysDt;
    for (i = 0; i < sizeof(alwaysDt) / sizeof(alwaysDt[0]); i++, e++) {
        if (e->iconId == 466 && !*(u16*)&pouchGetPtr()->mStarPowersObtained) {
            break;
        }
        if (!blinkOn) {
            blink = wp->blink;
            if (blink & 1 && i == 1) {
                continue;
            }
            if (blink & 2 && i == 4) {
                continue;
            }
            if (blink & 0x10 && i == 8) {
                continue;
            }
            if (blink & 4 && i == 12) {
                continue;
            }
        }
        MTXTrans(m, x + (f32)e->xpos, y - (f32)e->ypos, 0.0f);
        MTXScale(s, e->scale, e->scale, e->scale);
        MTXConcat(m, s, m);
        iconDispGxCol(m, 0x10, e->iconId, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
    }

    if (!(wp->blink & 1) || blinkOn) {
        numDisp(120.0f + x - 6.0f - 10.0f, 2.0f + (y - 38.0f), wp->cur.hp, 0);
    }
    numDisp(186.0f + x - 6.0f - 10.0f, 3.0f + (y - 38.0f), wp->cur.maxHp, 1);
    if (!(wp->blink & 2) || blinkOn) {
        numDisp(292.0f + x - 6.0f, 2.0f + (y - 38.0f), wp->cur.fp, 0);
    }
    numDisp(358.0f + x - 6.0f, 3.0f + (y - 38.0f), wp->cur.maxFp, 1);
    numDisp(462.0f + x, 2.0f + (y - 38.0f), wp->cur.starPoints, 0);
    if (!(wp->blink & 0x10) || blinkOn) {
        numDisp(572.0f + x, 2.0f + (y - 38.0f), wp->cur.coins, 0);
    }
    if (!(wp->blink & 4) || blinkOn) {
        gaugeDisp(wp->cur.ap, 260.0f + x, 4.0f + (y - 87.0f));
    }

    if (wp->cur.party) {
        partysDt[1].iconId = party_icon[wp->cur.party];
        if (wp->cur.party == 4) {
            switch (pouchGetPartyColor(4)) {
                case 0:
                    partysDt[1].iconId = 0x1A7;
                    break;
                case 1:
                    partysDt[1].iconId = 0x1A8;
                    break;
                case 2:
                    partysDt[1].iconId = 0x1A9;
                    break;
                case 3:
                    partysDt[1].iconId = 0x1AA;
                    break;
                case 4:
                    partysDt[1].iconId = 0x1AB;
                    break;
                case 5:
                    partysDt[1].iconId = 0x1AC;
                    break;
                case 6:
                default:
                    partysDt[1].iconId = 0x1AD;
                    break;
            }
        }
        e = partysDt;
        for (i = 0; i < sizeof(partysDt) / sizeof(partysDt[0]); i++, e++) {
            if (wp->blink & 8 && !blinkOn && i == 1) {
                continue;
            }
            MTXTrans(m, x + (f32)e->xpos, y - (f32)e->ypos, 0.0f);
            MTXScale(s, e->scale, e->scale, e->scale);
            MTXConcat(m, s, m);
            iconDispGxCol(m, 0x10, e->iconId, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
        }
        if (!(wp->blink & 8) || blinkOn) {
            numDisp(120.0f + x - 6.0f - 10.0f, 4.0f + (2.0f + (y - 78.0f)), wp->cur.partyHp, 0);
        }
        numDisp(186.0f + x - 6.0f - 10.0f, 4.0f + (2.0f + (y - 78.0f)), wp->cur.partyMaxHp, 1);
    }

    if (wp->flags & 0x100 && !gp->inBattle) {
        y2 = -180.0f + (wp->openY - wp->y);
        MTXTrans(m2, -190.0f, y2, 0.0f);
        MTXScale(s2, 0.75f, 0.75f, 0.75f);
        MTXConcat(m2, s2, m2);
        iconDispGxCol(m2, 0x10, 0x212, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
        if (swByteGet(0) >= 7 || partyChkJoin(1)) {
            MTXTrans(m2, -250.0f, 16.0f + y2, 0.0f);
            MTXScale(s2, 0.75f, 0.75f, 0.75f);
            MTXConcat(m2, s2, m2);
            iconDispGxCol(m2, 0x10, 0x213, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
        }
        MTXTrans(m2, -190.0f, 50.0f + y2, 0.0f);
        MTXScale(s2, 0.75f, 0.75f, 0.75f);
        MTXConcat(m2, s2, m2);
        iconDispGxCol(m2, 0x10, 0x214, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
        if (swByteGet(0) >= 20 || pouchGetHaveBadgeCnt()) {
            MTXTrans(m2, -130.0f, 16.0f + y2, 0.0f);
            MTXScale(s2, 0.75f, 0.75f, 0.75f);
            MTXConcat(m2, s2, m2);
            iconDispGxCol(m2, 0x10, 0x215, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
        }
        MTXTrans(m2, -190.0f, y2 - 25.0f, 0.0f);
        MTXScale(s2, 0.75f, 0.75f, 0.75f);
        MTXConcat(m2, s2, m2);
        iconDispGxCol(m2, 0x10, 0x216, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
    }
}

void statusGetValue(SVal* values) {
    BattleWork* bw;
    BattleUnit* mario;
    BattleUnit* party;

    if (!gp->inBattle) {
        values->hp = pouchGetHP();
        values->maxHp = pouchGetMaxHP();
        values->fp = pouchGetFP();
        values->maxFp = pouchGetMaxFP();
        values->ap = pouchGetAP();
        values->maxAp = pouchGetMaxAP();
        values->starPoints = pouchGetStarPoint();
        values->coins = pouchGetCoin();
        if (!marioBgmodeChk()) {
            values->party = ((s16 (*)(void))marioGetParty)();
        } else {
            values->party = marioGetPtr()->prevPartyMemberId[0];
        }
        values->partyHp = pouchGetPtr()->partyData[values->party].currentHP;
        values->partyMaxHp = pouchGetPtr()->partyData[values->party].maximumHP;
    } else {
        bw = _battleWorkPointer;
        mario = BattleGetMarioPtr(bw);
        party = BattleGetPartyPtr(bw);
        values->hp = mario->currentHp;
        values->maxHp = mario->maxHp;
        values->fp = mario->currentFp;
        values->maxFp = mario->maxFp;
        values->ap = pouchGetAP();
        values->maxAp = pouchGetMaxAP();
        values->starPoints = pouchGetStarPoint();
        values->coins = pouchGetCoin();
        if (party) {
            values->party = BattleTransPartyId(party->currentKind);
            values->partyHp = party->currentHp;
            values->partyMaxHp = party->maxHp;
        } else {
            values->party = 0;
            values->partyHp = 0;
            values->partyMaxHp = 0;
        }
    }
}

BOOL valueCheck(void) {
    SVal v;
    BOOL changed = FALSE;

    statusGetValue(&v);
    if (wp->cur.hp != v.hp) {
        changed = TRUE;
        wp->pendingBlink |= 1;
    }
    if (wp->cur.maxHp != v.maxHp) {
        changed = TRUE;
    }
    if (wp->cur.fp != v.fp) {
        changed = TRUE;
        wp->pendingBlink |= 2;
    }
    if (wp->cur.maxFp != v.maxFp) {
        changed = TRUE;
    }
    if (wp->cur.ap != v.ap) {
        changed = TRUE;
    }
    if (wp->cur.maxAp != v.maxAp) {
        changed = TRUE;
    }
    if (wp->cur.party != v.party) {
        wp->cur.party = v.party;
    } else if (wp->cur.party) {
        if (wp->cur.partyHp != v.partyHp) {
            changed = TRUE;
            wp->pendingBlink |= 8;
        }
        if (wp->cur.partyMaxHp != v.partyMaxHp) {
            changed = TRUE;
        }
    }
    if (wp->cur.starPoints != v.starPoints) {
        changed = TRUE;
    }
    if (wp->cur.coins != v.coins) {
        changed = TRUE;
        wp->pendingBlink |= 0x10;
    }
    if (!changed) {
        if (wp->pendingBlink != 0U) {
            wp->blink = wp->pendingBlink;
            wp->pendingBlink = 0;
            wp->blinkTimer = gp->framerate * 2;
        }
    } else {
        wp->blink = 0;
    }
    return changed;
}

static inline s32 calcStep(s32 target, s32 cur) {
    s32 d = target - cur;
    if (d) {
        d /= 10;
        if (!d) {
            d = -1;
            if (target > cur) {
                d = 1;
            }
        }
    }
    return d;
}

void valueUpdate(void) {
    static s32 count;
    SVal v;
    s32 d;

    statusGetValue(&v);
    count++;
    count %= 1200;
    if (count & 1) {
        return;
    }
    if (!statusWinCheck()) {
        return;
    }
    d = calcStep(v.coins, wp->cur.coins);
    if (d && !(count % 8)) {
        psndSFXOn("SFX_COUNT_COIN1");
    }
    wp->cur.hp += calcStep(v.hp, wp->cur.hp);
    wp->cur.maxHp += calcStep(v.maxHp, wp->cur.maxHp);
    wp->cur.fp += calcStep(v.fp, wp->cur.fp);
    wp->cur.maxFp += calcStep(v.maxFp, wp->cur.maxFp);
    wp->cur.ap += calcStep(v.ap, wp->cur.ap);
    wp->cur.maxAp += calcStep(v.maxAp, wp->cur.maxAp);
    wp->cur.starPoints += calcStep(v.starPoints, wp->cur.starPoints);
    wp->cur.coins += calcStep(v.coins, wp->cur.coins);
    wp->cur.party = v.party;
    if (wp->cur.party) {
        wp->cur.partyHp += calcStep(v.partyHp, wp->cur.partyHp);
        wp->cur.partyMaxHp += calcStep(v.partyMaxHp, wp->cur.partyMaxHp);
    }
    if (wp->cur.starPoints > 99) {
        wp->cur.starPoints = 99;
    }
    if (wp->cur.coins > 999) {
        wp->cur.coins = 999;
    }
}

void statusWinOpen(void) {
    wp->flags &= ~0xA;
    wp->flags |= 5;
}

void statusWinClose(void) {
    wp->flags |= 0xA;
    wp->flags &= ~5;
}

void statusWinForceOpen(void) {
    wp->flags &= ~0xA;
    wp->flags &= ~0xA0;
    wp->flags |= 0x50;
}

void statusWinForceClose(void) {
    wp->flags &= ~5;
    wp->flags &= ~0x50;
    wp->flags |= 0xA0;
}

void statusWinForceCloseClear(void) {
    wp->flags &= ~0xA0;
}

void statusWinForceOff(void) {
    if (wp->flags & 0x10) {
        wp->flags &= ~0x10;
        statusWinOpen();
    } else if (wp->flags & 1) {
        statusWinOpen();
    }
    if (wp->flags & 0x20) {
        wp->flags &= ~0x20;
        statusWinClose();
    } else if (wp->flags & 2) {
        statusWinClose();
    }
}

void statusWinDispOn(void) {
    wp->flags &= ~0x1000;
}

void statusWinDispOff(void) {
    wp->flags |= 0x1000;
}

BOOL statusWinCheck(void) {
    return (wp->flags & 0x11) ? TRUE : FALSE;
}

BOOL statusWinCheckUpdate(void) {
    return valueCheck() != 0;
}

void statusWinForceUpdate(void) {
    SVal v;

    statusGetValue(&v);
    wp->cur.hp = v.hp;
    wp->cur.maxHp = v.maxHp;
    wp->cur.fp = v.fp;
    wp->cur.maxFp = v.maxFp;
    wp->cur.ap = v.ap;
    wp->cur.maxAp = v.maxAp;
    wp->cur.starPoints = v.starPoints;
    wp->cur.coins = v.coins;
    wp->cur.party = v.party;
    if (wp->cur.party) {
        wp->cur.partyHp = v.partyHp;
        wp->cur.partyMaxHp = v.partyMaxHp;
    }
}

void statusWinForceUpdateCoin(void) {
    SVal v;

    statusGetValue(&v);
    wp->cur.coins = v.coins;
}

Vec statusGetApPos(void) {
    Vec pos;
    pos.x = wp->x + (f32)alwaysDt[12].xpos;
    pos.y = wp->y - (f32)alwaysDt[12].ypos;
    pos.z = 0.0f;
    return pos;
}

void statusAPBlink(s32 frames) {
    wp->blink = 0;
    wp->blink |= 4;
    wp->blinkTimer = frames;
}

void N_statusClearBlink(void) {
    wp->blink = 0;
}

void statusFPBlink(s32 frames) {
    wp->blink |= 2;
    wp->blinkTimer = frames;
}

void statusMarioHPBlink(s32 frames) {
    wp->blink |= 1;
    wp->blinkTimer = frames;
}

void statusPartyHPBlink(s32 frames) {
    wp->blink |= 8;
    wp->blinkTimer = frames;
}
