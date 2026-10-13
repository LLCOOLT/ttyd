#include "seq/seq_mapchange.h"
#include "data/mapdata.h"
#include "driver/bgdrv.h"
#include "driver/mapdrv.h"
#include "driver/msgdrv.h"
#include "evt/evt_badgeshop.h"
#include "mario/mario_party.h"
#include "mario/mariost.h"
#include "party.h"
#include "pmario_sound.h"
#include <stdio.h>
#include <string.h>

extern BadgeShopWork* bdsw;
extern BOOL dbg_lotteryinfo; // evt_lottery

//.sbss
char _next_bero[0x20];
char _next_map[0x20];
char _next_area[0x20];

void seq_mapChangeMain(SequenceWork* work) {
    /*
    BOOL newarea;
    char* area_name;

    newarea = strcmp(_next_area, gp->mCurrentAreaName) != 0;
    switch (work->field_0x4) {
    case 0:
            if (strcmp(_next_map, "sys_01")) {
                    if (newarea) {
                            fadeEntry(gp->mNextAreaChangeFadeInType, gp->mNextAreaChangeFadeInDuration, (GXColor) { 0,
    0, 0, 0xFF });
                    }
                    else {
                            fadeEntry(gp->mNextMapChangeFadeInType, gp->mNextMapChangeFadeInDuration, (GXColor) { 0, 0,
    0, 0xFF });
                    }
            }
            else {
                    if (gp->mNextAreaChangeFadeInType != 10) {
                            fadeEntry(gp->mNextAreaChangeFadeInType, gp->mNextAreaChangeFadeInDuration, (GXColor) { 0,
    0, 0, 0xFF });
                    }
                    fadeEntry(17, 2000, (GXColor) { 0, 0, 0, 0xFF });
            }
            gp->mNextMapChangeFadeInType = 10;
            gp->mNextMapChangeFadeInDuration = 300;
            gp->mNextAreaChangeFadeInType = 10;
            gp->mNextAreaChangeFadeInDuration = 300;
            psndSFXAllOff();
            gp->mbAreaChanged = newarea;
            if (strcmp(_next_map, "tou_03")) {
                    area_name = _next_area;
                    if (!strcmp(_next_area, "tou")) {
                            if (seqGetSeq() == 1) {
                                    area_name = "tou2";
                            }
                            else if (!strcmp(_next_map, "tou_03")) {
                                    area_name = "tou2";
                            }
                    }
                    fileAsyncf(0, 0, "%s/rel/%s.rel", getMarioStDvdRoot(), area_name);
            }
            work->field_0x4++;
            break;

    case 1:
            psndSFXAllOff();
            if (fadeIsFinish()) {
                    if (gp->mpRelFileBase) {
                            ((void(*)(void))gp->mpRelFileBase->epilog)();
                            OSUnlink(&gp->mpRelFileBase->info);
                    }
            }
            break;
    }*/
}

void seq_mapChangeExit(SequenceWork* work) {
    GXResetOverflowCount();
    dbg_lotteryinfo = FALSE;
}

void seq_mapChangeInit(SequenceWork* work) {
    strcpy(_next_area, "");
    strcpy(_next_map, "");
    strcpy(_next_bero, "");
    if (work->mapName) {
        strncpy(_next_area, work->mapName, 3);
        strncpy(_next_map, work->mapName, 0x20);
    }
    if (work->beroName) {
        strncpy(_next_bero, work->beroName, 0x20);
    }
    psndENVOff(0x200);
    psndENVOff(0x201);
    {
    int c0 = strcmp(gp->currentMapName, "");
    int c1 = strcmp(gp->currentMapName, "gor_01");
    int c2 = strcmp(_next_map, "gor_01");
    if (c0 && c1 && c2) {
        bdsw->field_0x114 |= 1;
    } else if (!c2 && bdsw->field_0x114 & 1) {
        badgeShop_bargainGeneration();
        badgeShop_bottakuruGeneration();
        bdsw->field_0x114 &= 0xFFFE;
    }
    }
}

void _relUnLoad(void) {
    if (gp->relocationBase) {
        (*(void (**)(void))((u8*)gp->relocationBase + 0x38))();
        OSUnlink(gp->relocationBase);
        if (gp->relocationBase != gp->mapAlloc) {
            _mapFree(gp->relocationBase);
        }
        gp->relocationBase = NULL;
    }
}

void _load(const char* prevMapName, const char* newMapName, const char* beroName) {
    MapData* map;
    char mapFile[64];

    map = mapDataPtr(newMapName);
    strcpy(gp->beroEnterName, beroName ? beroName : "");
    strcpy(gp->currentMapName, map->mapName);
    strncpy(gp->currentAreaName, map->mapName, 3);
    if (!strcmp(newMapName, "dmo_00")) {
        mapLoad("gor_01");
    } else {
        mapLoad(map->mapName);
    }
    camCtrlOff(4);
    if (gp->field_C) {
        msgLoad("gon_11", 0);
    } else {
        memset(mapFile, 0, sizeof(mapFile));
        strncpy(mapFile, map->mapName, 6);
        msgLoad(mapFile, 0);
    }
    setupDataLoad(map->mapName);
    sprintf(mapFile, "./b/%s.tpl", newMapName);
    bgEntry(mapFile);
    if (gp->flags & 1) {
        MarioWork* mario;
        PartyEntry* party;
        // TODO: verify this is e.g. Flavio and the Egg from Glitzville and rename accordingly
        PartyEntry* extraParty;

        mario = marioGetPtr();
        party = partyGetPtr(marioGetPartyId());
        extraParty = partyGetPtr(marioGetExtraPartyId());
        mario->field_EC = mario->position = gp->savePlayerPos;
        camRoadReset();
        camShiftReset();
        if (party) {
            party->position = gp->savePlayerPos;
        }
        if (extraParty) {
            extraParty->position = gp->savePlayerPos;
        }
    } else {
        Vec pos;
        Vec hit;
        Vec norm;
        f32 dist;
        f32 ang;
        int i;
        MarioWork* mw;
        CameraEntry* cam;
        static const char* dir_str[8] = {"n", "ne", "e", "se", "s", "sw", "w", "nw"};
        if (beroName) {
            dist = 100000.0f;
            hitObjGetPos(beroName, &pos);
            for (i = 0; i < 8; i++) {
                if (!strncmp(dir_str[i], beroName, strlen(dir_str[i]))) {
                    ang = 0.125f * (3.1416f * (2.0f * (f32)i));
                    pos.x += -30.0f * (f32)cos(ang);
                    pos.z += 30.0f * (f32)sin(ang);
                    break;
                }
            }
            if (i < 8) {
                if (hitCheckFilter(NULL, &hit.x, &hit.y, &hit.z, &dist, &norm.x, &norm.y, &norm.z, pos.x, 10.0f + pos.y, pos.z, 0.0f, -1.0f, 0.0f)) {
                    Vec t;
                    t.x = hit.x;
                    t.y = hit.y;
                    t.z = hit.z;
                    marioGetPtr()->position = t;
                } else {
                    Vec t = {0.0f, 0.0f, 0.0f};
                    marioGetPtr()->position = t;
                }
            } else {
                Vec t = {0.0f, 0.0f, 0.0f};
                marioGetPtr()->position = t;
            }
        } else {
            Vec t = {0.0f, 0.0f, 0.0f};
            marioGetPtr()->position = t;
        }
        mw = marioGetPtr();
        cam = camGetPtr(4);
        cam->marioPos.x = mw->position.x;
        cam->marioPos.y = 0.01f + mw->position.y;
        cam->marioPos.z = mw->position.z;
        cam->marioAt.x = cam->marioPos.x;
        cam->marioAt.y = cam->marioPos.y;
        cam->marioAt.z = cam->marioPos.z;
        mw->field_EC = mw->position;
        camRoadReset();
        camShiftReset();
    }
}

void _unload(const char* prevMap, const char* nextMap, const char* bero) {
    extern void* nanNPCWork;
    BOOL swReinit = FALSE;
    int i;

    if (prevMap && nextMap && strncmp(prevMap, nextMap, 3)) {
        swReinit = TRUE;
    }
    marioReInit();
    marioInitCamId();
    mapUnLoad();
    npcReset(0);
    extReset();
    mobjReset(0);
    offscreenReset(0);
    imgAutoRelease(0);
    effAutoRelease(0);
    animPoseAutoRelease(0);
    evtmgrReInit();
    caseReInit();
    itemReInit();
    iconReInit();
    windowReInit();
    winReInit();
    statusWinReInit();
    bgReInit();
    winMgrReInit();
    if (seqGetPrevSeq() != 6 && seqGetPrevSeq() != 1 && strcmp(prevMap, "sys_00") &&
        strcmp(prevMap, "sys_01") && strcmp(prevMap, "dig_00")) {
        fadeReset(1);
        gp->flags &= ~0x10;
    }
    for (i = 0; i < 4; i++) {
        padRumbleHardOff(i);
    }
    if (swReinit) {
        swReInit();
    }
    memClear(1);
    memClear(2);
    smartAutoFree(1);
    nanNPCWork = NULL;
}
