// Battle sequence: loads the battle REL and map, runs the battle and returns to the field.
#include "version.h"
#include "battle/battle.h"
#include "battle/battle_information.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include "driver/extdrv.h"
#include "driver/fadedrv.h"
#include "driver/icondrv.h"
#include "driver/imgdrv.h"
#include "driver/itemdrv.h"
#include "driver/msgdrv.h"
#include "driver/npcdrv.h"
#include "driver/lightdrv.h"
#include "driver/offscreendrv.h"
#include "driver/seqdrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "manager/filemgr.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "memory.h"
#include "party.h"
#include "pmario_sound.h"
#include "seq/seq_title.h"
#include "seq/seq_battle.h"
#include "driver/mapdrv.h"
#include "data/mapdata.h"
#include "system.h"
#include <dolphin/mtx.h>
#include "evt/evt_story.h"

static void battle_exit(void);
#if VERSION <= VERSION_DEMO_US
static void battle_init(void);
#else
static BOOL battle_init(void);
#endif

s32 debug_battle_flag;

/** Requests an async load of a TPL under the disc root; true once the file is resident (seq_battleMain polls it). */
static inline BOOL loadTpl(const char* path) {
    return fileAsyncf(4, NULL, "%s/%s", getMarioStDvdRoot(), path) != NULL;
}

// battle map names (defined at the end of the file)
static const char gon11[7];
static const char bti01[7];
static const char bti02[7];
static const char bti03[7];
static const char bti04[7];

/**
 * Enters the battle sequence: switches to the enemy's battle BGM (kept during the Great Tree time-bomb countdown
 * and after the final battle), stops field events and rumble and mutes field sound effects.
 * Later versions take Mario's control here for hit kinds 0x800000/0x1000000;
 * the demos start preloading the audience map for Mario's rank.
 */
void seq_battleInit(SequenceWork* work) {
    FieldBattleData* fbat;
    NpcEntry* npc;
#if VERSION <= VERSION_DEMO_US
    MapData* map;
#endif

    debug_battle_flag = gp->debugBattle;
#if VERSION <= VERSION_DEMO_US
    // the demo starts reading the battle map now
    fbatGetPointer();
    switch (pouchGetPtr()->rank) {
        case 0:
            map = mapDataPtr(bti01);
            break;
        case 1:
            map = mapDataPtr(bti02);
            break;
        case 2:
            map = mapDataPtr(bti03);
            break;
        case 3:
        default:
            map = mapDataPtr(bti04);
            break;
    }
    bmapPreLoad(map->mapName, NULL);
#endif
    fbat = fbatGetPointer();
    npc = fbat->target;
    if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG2_23_TIME_BOMB_ACTIVATED || evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) >= STORY_STG2_24_BOSS_BATTLE) {
        if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) != STORY_STG8_END_AFTER_THE_BATTLE) {
            psndBGMOff(PSND_FADE_HOLD);
            psndBGMOn(PSND_CH(1), (char*)npc->battleInfo.bgmName);
        }
    }
    psndENVOff(PSND_FADE_HOLD);
    padRumbleOff(0);
    evtStopAll(4);
    psndSetFlag(PSND_FLAG_MUTE_SFX);
#if VERSION >= VERSION_JP
    switch (fbatGetPointer()->hitKind) {
        case 0x1000000:
        case 0x800000:
            if (debug_battle_flag == 0) {
                marioCtrlOff();
                partyCtrlOff();
                padRumbleOff(0);
            }
            break;
    }
#endif
}

/** Leaves the battle sequence; battle_exit tears the battle down and restores the field. */
void seq_battleExit(SequenceWork* work) {
    battle_exit();
}

/**
 * Per-frame battle sequence: curtain fade, audience texture loads,
 * waits out a pending first strike (up to 200 frames), loads the bti_01..04 audience stage for Mario's rank,
 * starts the battle via battle_init, then once the battle ends returns to the field (or game over on a kiosk
 * timeout; states 10/11 end a debug battle).
 */
void seq_battleMain(SequenceWork* work) {
#if VERSION >= VERSION_JP
    FieldBattleData* fbat;
    BattleStageData* stage;
    PouchData* pouch;
#endif

    switch (work->state) {
        case 0: {
            GXColor color = {0, 0, 0, 255};
            fadeEntry(FADE_CURTAIN_VERTICAL_A1, 1000, color);
            work->state++;
            work->counter = 0;
            break;
        }
        case 1:
            if (!loadTpl("battle/audience/audience_normal.tpl")) {
                break;
            }
            if (!loadTpl("battle/audience/audience_luigi.tpl")) {
                break;
            }
            work->counter++;
            if (fadeIsFinish()) {
                work->state++;
            }
            break;
#if VERSION <= VERSION_DEMO_US
        // the demo loads the battle map in battle_init
        case 2:
            battle_init();
            work->state++;
        case 3: {
#else
        case 2:
            pouchGetPtr();
            switch (fbatGetPointer()->hitKind) {
                case 0x1000000:
                case 0x800000:
                    if (debug_battle_flag == 0) {
                        marioGetPtr()->flags &= ~1;
                    }
                    break;
                default:
                    if (debug_battle_flag == 0) {
                        marioCtrlOff();
                        partyCtrlOff();
                        marioGetPtr()->flags &= ~1;
                        padRumbleOff(0);
                    }
                    break;
            }
            fbat = fbatGetPointer();
            fbat->battleWait = 0;
            work->state++;
        case 3: {
            BOOL wait;
            fbat = fbatGetPointer();
            stage = fbat->target->battleInfo.stageData;
            pouch = pouchGetPtr();
            if (fbat->firstStrike.enabled != 0) {
                BOOL ok = TRUE;
                switch (fbat->firstStrike.type) {
                    case 1:
                    case 2:
                        if (fbat->firstStrike.hitKind != 0) {
                            ok = FALSE;
                        }
                        break;
                }
                if (ok == FALSE) {
                    fbat->battleWait++;
                    if (fbat->battleWait < 200) {
                        wait = TRUE;
                        goto check;
                    }
                }
            }
            switch (pouch->rank) {
                case 0:
                    bmapLoad(bti01, stage->specificStageDataDir);
                    break;
                case 1:
                    bmapLoad(bti02, stage->specificStageDataDir);
                    break;
                case 2:
                    bmapLoad(bti03, stage->specificStageDataDir);
                    break;
                case 3:
                default:
                    bmapLoad(bti04, stage->specificStageDataDir);
                    break;
            }
            wait = FALSE;
        check:
            if (wait != 0) {
                break;
            }
            work->state++;
        }
        case 4:
            if (battle_init()) {
                break;
            }
            work->state++;
        case 5: {
#endif
            Vec pos;
            if (battleSeqEndCheck()) {
                work->counter = 0;
                work->state++;
                if (gp->debugBattle) {
                    work->state = 11;
                }
            }
            marioGetPtr();
            camGetPtr(CAMERA_3D);
            pos.x = 0.0f;
            pos.y = 0.0f;
            pos.z = 400.0f;
            if (_battleWorkPointer->flags & 0x100) {
                pos.z += 200.0f;
            }
            psndSetPosDirListener(&pos, camGetPtr(CAMERA_3D)->viewYaw);
            break;
        }
#if VERSION <= VERSION_DEMO_US
        case 4:
#else
        case 6:
#endif
            if (++work->counter > 30) {
                // A non-NULL map name tells seq_gameOver to skip its iris fade (the battle has already
                // faded out); seq_game does not read it.
                if ((gp->flags & GLOBAL_FLAG_KIOSK) && (gp->flags & GLOBAL_FLAG_KIOSK_TIMEOUT)) {
                    seqSetSeq(SEQ_GAME_OVER, (const char*)1, NULL);
                } else {
                    seqSetSeq(SEQ_GAME, (const char*)1, NULL);
                }
            }
            break;
        case 10: {
            GXColor color = {0, 0, 0, 255};
            fadeEntry(FADE_CURTAIN_VERTICAL_A1, 200, color);
            work->state++;
            break;
        }
        case 11:
            if (fadeIsFinish()) {
                gp->debugBattle = 0;
                seqSetSeq(SEQ_GAME_OVER, (const char*)1, NULL);
            }
            break;
    }
}

/**
 * Sets up the battle: frees field memory, parks the field NPCs, resets the event manager,
 * then fills the FieldBattleInfo (partner, first-attack kind from the field hit, setup and rules from the enemy)
 * and calls BattleInit.
 * The demos also take control and load the stage map here; later versions return FALSE (done in one call).
 */
#if VERSION <= VERSION_DEMO_US
static void battle_init(void) {
#else
/** Later versions: same setup, returning FALSE once done (seq_battleMain state 4 retries while TRUE). */
static BOOL battle_init(void) {
#endif
    FieldBattleData* fbat;
    NpcEntry* npc;
    PouchData* pouch;
#if VERSION <= VERSION_DEMO_US
    MapData* map;
    MapData* map2;
    BattleStageData* stage;
#endif
    FieldBattleInfo* info;
    PartyEntry* party;

    fbat = fbatGetPointer();
    npc = fbat->target;
#if VERSION <= VERSION_DEMO_US
    stage = npc->battleInfo.stageData;
#endif
    pouch = pouchGetPtr();
#if VERSION <= VERSION_DEMO_US
    // the demo takes Mario's control and loads the battle map here (later versions: seq_battleMain states 2 and 3)
    if (debug_battle_flag == 0) {
        marioCtrlOff();
        partyCtrlOff();
        marioGetPtr()->flags &= ~1;
        padRumbleOff(0);
    }
    switch (pouch->rank) {
        case 0:
            map = mapDataPtr(bti01);
            break;
        case 1:
            map = mapDataPtr(bti02);
            break;
        case 2:
            map = mapDataPtr(bti03);
            break;
        case 3:
        default:
            map = mapDataPtr(bti04);
            break;
    }
    map2 = NULL;
    if (stage->specificStageDataDir) {
        map2 = mapDataPtr(stage->specificStageDataDir);
    }
    bmapLoad(map->mapName, stage->specificStageDataDir);
#endif
    camSetMode(CAMERA_3D, 2);
    if (gp->debugBattle) {
        const char* msg = DbgBtlSel_GetMsgDataPtr();
        if (msg) {
            msgLoad(msg, 0);
        } else {
            msgLoad(gon11, 0);
        }
    }
#if VERSION >= VERSION_US
    N_battleMapAlloc();
#else
    memClear(4);
    smartAutoFree(2);
#endif
    _battleWorkPointer = NULL;
    animPoseBattleInit();
    npcReleaseFiledNpc();
    gp->inBattle = 1;
    evtmgrReInit();
#if VERSION <= VERSION_DEMO_US
    if (map && map->eventAddr) {
        evtEntry(map->eventAddr, 0, 0);
    }
    if (map2 && map2->eventAddr) {
        evtEntry(map2->eventAddr, 0, 0);
    }
#endif
    psndSetFlag(PSND_FLAG_SFX_WITH_BGM);
    info = &fbat->info;
    BattleInformationInit(info);
    BattleInformationSetMode(info, 0);
    party = partyGetPtr(marioGetPartyId());
    if (party) {
        s32 id = party->currentMemberId;
        BattleUnitType kind = BattleTransPartyIdToUnitKind(id);
        if (!(pouch->partyData[id].flags & 2)) {
            BattleInformationSetParty(info, kind);
        }
    }
    if (fbat->firstAttackFlags & 1) {
        BattleInformationSetFirstAttack(info, 0);
    } else {
        switch (fbat->hitKind) {
            case 0x20000:
                BattleInformationSetFirstAttack(info, 1);
                break;
            case 0x40000:
                BattleInformationSetFirstAttack(info, 2);
                break;
            case 0x80000:
                BattleInformationSetFirstAttack(info, 3);
                break;
            case 0x100000:
                BattleInformationSetFirstAttack(info, 4);
                break;
            case 0x200000:
                BattleInformationSetFirstAttack(info, 5);
                break;
            case 0x400000:
                BattleInformationSetFirstAttack(info, 6);
                break;
            case 0x800000:
                BattleInformationSetFirstAttack(info, 7);
                break;
            case 0x1000000:
                BattleInformationSetFirstAttack(info, 8);
                break;
            case 0x10000000:
                BattleInformationSetFirstAttack(info, fbat->firstAttackParam);
                break;
            default:
                BattleInformationSetFirstAttack(info, 0);
                break;
        }
    }
    BattleInfomationSetBattleSetupInfo(info, &npc->battleInfo);
    info->ruleType = npc->battleInfo.battleRule[0];
    info->ruleParam = npc->battleInfo.battleRule[1];
    info->ruleParam2 = npc->battleInfo.battleRule[2];
    BattleInit(info);
#if VERSION >= VERSION_JP
    return FALSE;
#endif
}

/**
 * Tears the battle down and restores the field:
 * frees battle data and drivers, restores the camera mode and field NPCs,
 * resumes field events and Mario's control, resets the paper-craft light,
 * and resumes the field BGM and ambience unless heading to game over (or, in later versions,
 * resumes the time-bomb music in the Great Tree).
 */
static void battle_exit(void) {
    LightEntry* light;
    Mtx mtx;

    BattleEnd();
#if VERSION >= VERSION_US
    N_battleMapFree();
    smartAutoFree(2);
#endif
    itemReInit();
    iconReInit();
    extReset();
    bmapUnLoad();
    if (camGetPtr(CAMERA_3D)->flags & CAM_FLAG_ROAD_LOADED) {
        camSetMode(CAMERA_3D, 1);
    } else {
        camSetMode(CAMERA_3D, 3);
    }
    npcReset(TRUE);
    mobjReset(TRUE);
    offscreenReset(TRUE);
    imgAutoRelease(1);
    effAutoRelease(TRUE);
    animPoseAutoRelease(TRUE);
    evtmgrReInit();
    npcRecoveryFiledNpc();
    gp->inBattle = 0;
#if VERSION <= VERSION_JP
    memClear(4);
#endif
    evtStartAll(4);
    if (debug_battle_flag == 0) {
        marioCtrlOn();
        partyCtrlOn();
        marioGetPtr()->flags |= 1;
    }
#if VERSION <= VERSION_DEMO_US
    psndClearFlag(PSND_FLAG_SFX_WITH_BGM);
#else
    L_psndBGM_stop();
#endif
    psndClearFlag(PSND_FLAG_MUTE_SFX);
    light = lightGetPaperCraft();
    {
        Vec v = {-200.0f, 100.0f, 100.0f};
        light->position = v;
    }
    PSMTXScale(mtx, 3.0f, 3.0f, 3.0f);
    PSMTXMultVec(mtx, &light->position, &light->position);
#if VERSION <= VERSION_DEMO_US
    if ((evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG2_23_TIME_BOMB_ACTIVATED || evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) >= STORY_STG2_24_BOSS_BATTLE) && evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) != STORY_STG8_END_AFTER_THE_BATTLE && seqGetNextSeq() != SEQ_GAME_OVER) {
#else
    if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) >= STORY_STG2_23_TIME_BOMB_ACTIVATED && evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG2_24_BOSS_BATTLE) {
        psndBGMOn_f(PSND_FADE_RESUME | PSND_FADE_IN, 0, 0x2EE, 1);
    } else if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) != STORY_STG8_END_AFTER_THE_BATTLE && seqGetNextSeq() != SEQ_GAME_OVER) {
#endif
        psndBGMOn(PSND_FADE_RESUME | PSND_FADE_IN, NULL);
        psndENVOn(PSND_FADE_RESUME | PSND_FADE_IN, NULL);
    }
}

// the demo defines the names in another order (their order in .rodata)
#if VERSION <= VERSION_DEMO_US
static const char bti01[] = "bti_01";
static const char bti02[] = "bti_02";
static const char bti03[] = "bti_03";
static const char bti04[] = "bti_04";
static const char gon11[] = "gon_11";
#else
static const char gon11[] = "gon_11";
static const char bti01[] = "bti_01";
static const char bti02[] = "bti_02";
static const char bti03[] = "bti_03";
static const char bti04[] = "bti_04";
#endif
