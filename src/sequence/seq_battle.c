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
#include "pmario_sound.h"
#include "seq/seq_title.h"
#include "system.h"
#include <dolphin/mtx.h>

typedef struct BattleSeqWork {
    s32 sequence;   // 0x0
    s32 state;      // 0x4
    u8 unk8[8];     // 0x8
    s32 counter;    // 0x10
} BattleSeqWork;

typedef struct FBatView {
    s16 mode;           // 0x0
    u8 unk2[6];         // 0x2
    NpcEntry* target;   // 0x8
    u8 unkC[4];         // 0xC
    u32 flags;          // 0x10
    s32 partner;        // 0x14
    u8 unk18[4];        // 0x18
    u32 flags1C;        // 0x1C
    FieldBattleInfo info; // 0x20
    u8 unk3C[0x550 - 0x3C];
    s32 fsEnabled;      // 0x550
    u32 fs554;          // 0x554
    s32 fsType;         // 0x558
    u8 unk55C[0x570 - 0x55C];
    s32 waitCount;      // 0x570
} FBatView;

typedef struct LightView {
    u8 unk0[0x24];
    Vec pos; // 0x24
} LightView;

BOOL bmapLoad(const char* a, const char* b);
void bmapUnLoad(void);
LightView* lightGetPaperCraft(void);
BattleUnitType BattleTransPartyIdToUnitKind(s32 id);
void unk_800d7270(u32 a, u32 b, u32 c, u32 d);
BOOL psndBGMOff(u32 flags);
BOOL psndENVOn(u32 a, char* b);
typedef struct PartyView {
    u8 unk0[0x31];
    s8 id;
} PartyView;
PartyView* partyGetPtr(s32 index);
void partyCtrlOn(void);
void partyCtrlOff(void);
void mobjReset(BOOL inBattle);
void animPoseAutoRelease(BOOL inBattle);

s32 debug_battle_flag;
s32 seq_battle_unk_8041874c;


static inline BOOL loadTpl(const char* path) {
    return (u32)fileAsyncf(4, NULL, "%s/%s", getMarioStDvdRoot(), path) != 0;
}
#define GSW0 (-170000000)

void seq_battleInit(BattleSeqWork* work) {
    FBatView* fbat;
    NpcEntry* npc;

    debug_battle_flag = gp->field_C;
    fbat = (FBatView*)fbatGetPointer();
    npc = fbat->target;
    if (evtGetValue(NULL, GSW0) < 109 || evtGetValue(NULL, GSW0) >= 111) {
        if (evtGetValue(NULL, GSW0) != 402) {
            psndBGMOff(0x400);
            psndBGMOn(1, *(char**)((u8*)npc + 0x2F0));
        }
    }
    psndENVOff(0x400);
    padRumbleOff(0);
    evtStopAll(4);
    psndSetFlag(0x80);
    switch (((FBatView*)fbatGetPointer())->flags) {
        case 0x1000000:
        case 0x800000:
            if (debug_battle_flag == 0) {
                marioCtrlOff();
                partyCtrlOff();
                padRumbleOff(0);
            }
            break;
    }
}

void seq_battleExit(BattleSeqWork* work) {
    battle_exit();
}

static const char gon11[7];
static const char bti01[7];
static const char bti02[7];
static const char bti03[7];
static const char bti04[7];

void seq_battleMain(BattleSeqWork* work) {
    FBatView* fbat;
    BattleStageData* stage;
    PouchData* pouch;

    switch (work->state) {
        case 0: {
            GXColor color = {0, 0, 0, 255};
            fadeEntry(0x16, 1000, color);
            work->state++;
            work->counter = 0;
            break;
        }
        case 1:
            if (!loadTpl("battle/audience/audience_normal.tpl")) {
                break;
            }
            if (!loadTpl("battle/audience/audience_luigi.tpl\0")) {
                break;
            }
            work->counter++;
            if (fadeIsFinish()) {
                work->state++;
            }
            break;
        case 2:
            pouchGetPtr();
            switch (((FBatView*)fbatGetPointer())->flags) {
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
            fbat = (FBatView*)fbatGetPointer();
            fbat->waitCount = 0;
            work->state++;
        case 3: {
            BOOL wait;
            fbat = (FBatView*)fbatGetPointer();
            stage = fbat->target->battleInfo.stageData;
            pouch = pouchGetPtr();
            if (fbat->fsEnabled != 0) {
                BOOL ok = TRUE;
                switch (fbat->fsType) {
                    case 1:
                    case 2:
                        if (fbat->fs554 != 0) {
                            ok = FALSE;
                        }
                        break;
                }
                if (ok == FALSE) {
                    fbat->waitCount++;
                    if (fbat->waitCount < 200) {
                        wait = TRUE;
                        goto check;
                    }
                }
            }
            switch (pouch->rank) {
                case 0:
                    bmapLoad(bti01, stage->mSpecificStageDataDir);
                    break;
                case 1:
                    bmapLoad(bti02, stage->mSpecificStageDataDir);
                    break;
                case 2:
                    bmapLoad(bti03, stage->mSpecificStageDataDir);
                    break;
                case 3:
                default:
                    bmapLoad(bti04, stage->mSpecificStageDataDir);
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
            Vec pos;
            if (battleSeqEndCheck()) {
                work->counter = 0;
                work->state++;
                if (gp->field_C) {
                    work->state = 11;
                }
            }
            marioGetPtr();
            camGetPtr(4);
            pos.x = 0.0f;
            pos.y = 0.0f;
            pos.z = 400.0f;
            if (*(u32*)((u8*)_battleWorkPointer + 0xEF4) & 0x100) {
                pos.z += 200.0f;
            }
            psndSetPosDirListener(&pos, *(f32*)((u8*)camGetPtr(4) + 0x114));
            break;
        }
        case 6:
            if (++work->counter > 30) {
                if ((gp->flags & 0x1000) && (gp->flags & 0x2000)) {
                    seqSetSeq(5, (const char*)1, NULL);
                } else {
                    seqSetSeq(2, (const char*)1, NULL);
                }
            }
            break;
        case 10: {
            GXColor color = {0, 0, 0, 255};
            fadeEntry(0x16, 200, color);
            work->state++;
            break;
        }
        case 11:
            if (fadeIsFinish()) {
                gp->field_C = 0;
                seqSetSeq(5, (const char*)1, NULL);
            }
            break;
    }
}

BOOL battle_init(void) {
    FBatView* fbat;
    NpcEntry* npc;
    PouchData* pouch;
    FieldBattleInfo* info;
    PartyView* party;

    fbat = (FBatView*)fbatGetPointer();
    npc = fbat->target;
    pouch = pouchGetPtr();
    camSetMode(4, 2);
    if (gp->field_C) {
        const char* msg = DbgBtlSel_GetMsgDataPtr();
        if (msg) {
            msgLoad(msg, 0);
        } else {
            msgLoad(gon11, 0);
        }
    }
    memClear(4);
    smartAutoFree(2);
    _battleWorkPointer = NULL;
    animPoseBattleInit();
    npcReleaseFieldNpc();
    gp->inBattle = 1;
    evtmgrReInit();
    psndSetFlag(0x10);
    info = &fbat->info;
    BattleInformationInit(info);
    BattleInformationSetMode(info, 0);
    party = partyGetPtr(marioGetPartyId());
    if (party) {
        s32 id = party->id;
        BattleUnitType kind = BattleTransPartyIdToUnitKind(id);
        if (!(pouch->partyData[id].flags & 2)) {
            BattleInformationSetParty(info, kind);
        }
    }
    if (fbat->flags1C & 1) {
        BattleInformationSetFirstAttack(info, 0);
    } else {
        switch (fbat->flags) {
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
                BattleInformationSetFirstAttack(info, fbat->partner);
                break;
            default:
                BattleInformationSetFirstAttack(info, 0);
                break;
        }
    }
    BattleInfomationSetBattleSetupInfo(info, &npc->battleInfo);
    info->field_0x18 = npc->battleInfo.battleRule[0];
    info->field_0x1A = npc->battleInfo.battleRule[1];
    info->field_0x1B = npc->battleInfo.battleRule[2];
    BattleInit(info);
    return FALSE;
}

void battle_exit(void) {
    LightView* light;
    Mtx mtx;

    BattleEnd();
    itemReInit();
    iconReInit();
    extReset();
    bmapUnLoad();
    if (camGetPtr(4)->flags & 4) {
        camSetMode(4, 1);
    } else {
        camSetMode(4, 3);
    }
    npcReset(TRUE);
    mobjReset(TRUE);
    offscreenReset(TRUE);
    imgAutoRelease(1);
    effAutoRelease(TRUE);
    animPoseAutoRelease(TRUE);
    evtmgrReInit();
    npcRecoveryFieldNpc();
    gp->inBattle = 0;
    memClear(4);
    evtStartAll(4);
    if (debug_battle_flag == 0) {
        marioCtrlOn();
        partyCtrlOn();
        marioGetPtr()->flags |= 1;
    }
    L_psndBGM_stop();
    psndClearFlag(0x80);
    light = lightGetPaperCraft();
    { Vec v = {-200.0f, 100.0f, 100.0f}; light->pos = v; }
    PSMTXScale(mtx, 3.0f, 3.0f, 3.0f);
    PSMTXMultVec(mtx, &light->pos, &light->pos);
    if (evtGetValue(NULL, GSW0) >= 109 && evtGetValue(NULL, GSW0) < 111) {
        unk_800d7270(0x120, 0, 0x2EE, 1);
    } else if (evtGetValue(NULL, GSW0) != 402 && seqGetNextSeq() != 5) {
        psndBGMOn(0x120, NULL);
        psndENVOn(0x120, NULL);
    }
}

static const char gon11[] = "gon_11";
static const char bti01[] = "bti_01";
static const char bti02[] = "bti_02";
static const char bti03[] = "bti_03";
static const char bti04[] = "bti_04";
