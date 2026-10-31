// Ms. Mowz (chuchu): partner init, follow and the treasure search ability.
#include "driver/itemdrv.h"
#include "driver/mobjdrv.h"
#include "evt/evt_cmd.h"
#include "mario/mario.h"
#include "mario/mario_motion.h"
#include "mario/mario_party.h"
#include "mario/mario_sbr.h"
#include "mario/mariost.h"
#include "party.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/mtx.h>
#include <string.h>
#include "party/party_hit.h"
#include "party/party_move.h"
#include "manager/evtmgr_cmd.h"
#include "eff/eff_fukidashi.h"
#include "version.h"
// FAKE: party_chuchu.c calls effFukidashiEntry through this prototype (the types it was compiled with) instead of the one in eff/eff_fukidashi.h; same registers, behaviour-identical.
typedef void* (*EffFukidashiEntryRetVoidptrS32Fn)(s32, s32, s32, f32, f32, f32, f32, f32, s32);

typedef struct ChuchuParty {
    u32 flags;             // 0x0
    u8 pad4[0x8 - 0x4];    // 0x4
    u32 trigFlags;         // 0x8
    u8 padC[0x24 - 0xC];   // 0xC
    s32 timer;             // 0x24
    u8 pad28[0x32 - 0x28]; // 0x28
    u8 moveKind;           // 0x32
    u8 memberKind;         // 0x33
    u8 pad34[0x39 - 0x34]; // 0x34
    u8 state;              // 0x39
    u8 pad3A;              // 0x3A
    u8 moveMode;           // 0x3B
#if VERSION <= VERSION_DEMO_US
    u8 pad3C[0x54 - 0x3C]; // 0x3C, the demo PartyEntry is 4 bytes shorter here
#else
    u8 pad3C[0x58 - 0x3C]; // 0x3C
#endif
    Vec position;          // 0x58
    u8 pad64[0x94 - 0x64]; // 0x64
    Vec target;            // 0x94
#if VERSION <= VERSION_DEMO_US
    u8 padA0[0xD8 - 0x9C]; // 0xA0, the demo PartyEntry is 0x14 shorter here
#else
    u8 padA0[0xF0 - 0xA0]; // 0xA0
#endif
    f32 height;    // 0xF0
    f32 width;     // 0xF4
    f32 camDir;    // 0xF8
    f32 moveDir;   // 0xFC
    f32 targetDir; // 0x100
    f32 moveSpeed; // 0x104
#if VERSION >= VERSION_JP
    u8 pad108[0x10C - 0x108]; // 0x108, PartyEntry.targetSpeed (not in the demo)
#endif
    f32 displayDirection;       // 0x10C
    f32 displayDirectionTarget; // 0x110
    f32 velY;                   // 0x114
    u8 pad118[0x160 - 0x118];   // 0x118
    MarioWork* player;          // 0x160
} ChuchuParty;

typedef struct ChuchuTreasure {
    const char* map;
    u32 flag;
    s32 x;
    s32 y;
    s32 z;
} ChuchuTreasure;

#if VERSION <= VERSION_DEMO_US
extern s32 mobjCheckKururingFloorItem(MapObjectEntry* mobj);
#endif
extern USER_FUNC(evt_msg_print);

char* mobj_list[] = {
#if VERSION >= VERSION_JP
    "MOBJ_TreasureBox",
    "MOBJ_BigTreasureBox",
    "MOBJ_GrayTreasureBox",
    "MOBJ_BlackTreasureBox",
    "MOBJ_KururinFloor",
#endif
    "MOBJ_HatenaBlock",
    "MOBJ_BadgeBlock",
    "MOBJ_10CountBlock",
    "MOBJ_HiddenHatenaBlock",
    "MOBJ_HiddenBadgeBlock",
    "MOBJ_Hidden10CountBlock",
    "MOBJ_BrickHatenaBlock",
    "MOBJ_BrickBadgeBlock",
    "MOBJ_PowerUpBlock",
    NULL,
};

static const Vec vecA = {0.0f, 0.0f, 0.0f};

static USER_FUNC(set_msg);
static USER_FUNC(search_result);
static USER_FUNC(post_msg);

/**
 * Ms. Mowz's search report, run by chuchu_use after her sniff:
 * set_msg finds the nearest hidden thing, search_result plays the reaction,
 * the message from the party group is printed, and post_msg lets chuchu_use end.
 */
EVT_BEGIN(msg_evt)
    CALL(set_msg)
    CALL(search_result)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, LW(0), 0, STRING("party"))
    END_IF
    CALL(post_msg)
    RETURN
EVT_END()

#if VERSION >= VERSION_JP
ChuchuTreasure chuchu_treasure_tbl[] = {
    {"hei_00", 0xF840715E, -468, 139, -127},
    {"hei_00", 0xF8406272, -408, 139, -127},
    {"hei_01", 0xF840628A, -200, 0, 120},
    {"hei_01", 0xF8406278, 190, 0, -70},
    {"hei_01", 0xF8406288, -285, 0, 85},
    {"hei_02", 0xF8407160, -645, 50, -70},
    {"hei_02", 0xF840627A, 192, 92, -120},
    {"hei_04", 0xF840627E, 364, 75, -95},
    {"hei_04", 0xF8406289, 320, 75, -55},
    {"hei_04", 0xF840627F, 17, 90, -122},
    {"hei_06", 0xF8406282, 200, 75, 60},
    {"nok_01", 0xF9718884, -407, 70, -148},
    {"win_00", 0xF84065FD, -694, 111, -130},
    {"win_01", 0xF84065FE, 312, 106, -122},
    {"win_03", 0xF8407169, -333, 72, -24},
    {"mri_01", 0xF840668C, -240, 0, -20},
    {"mri_04", 0xF8406696, 85, 0, 85},
    {"mri_05", 0xF840669C, 225, -309, -40},
    {"mri_06", 0xF840716E, -95, -310, -52},
    {"mri_12", 0xF84066AC, -190, -309, 65},
    {"mri_13", 0xF84066AE, -190, -309, 115},
    {"mri_15", 0xF8407170, -37, 0, 96},
    {"mri_18", 0xF84066B9, 50, -320, -35},
    {"mri_20", 0xF84066BB, 250, -320, 130},
    {"usu_00", 0xF840717C, 130, 0, 455},
    {"usu_00", 0xF840630D, 330, 0, 275},
    {"jin_01", 0xF9718882, 798, 50, -40},
    {"muj_02", 0xF84067D2, 323, 0, 50},
    {"muj_02", 0xF8407189, -500, 0, 110},
    {"muj_02", 0xF84067D0, -350, 90, -70},
    {"muj_03", 0xF84067D3, -250, 10, 95},
    {"muj_03", 0xF84067D4, 175, 210, -50},
    {"muj_05", 0xF84067D5, 235, 0, 90},
    {"rsh_02_a", 0xF8406906, -265, 0, -250},
    {"rsh_02_b", 0xF8406906, -265, 0, -250},
    {"rsh_02_c", 0xF8406906, -265, 0, -250},
    {"rsh_04_a", 0xF8407194, -265, 0, -250},
    {"rsh_04_b", 0xF8407194, -265, 0, -250},
    {"rsh_04_c", 0xF8407194, -265, 0, -250},
    {"tou_05", 0xF8407179, 100, 0, -28},};

static const Vec vecB = {0.0f, 0.0f, 0.0f};
#endif

/**
 * Script helper: reads set_msg's result (LW0 message, LW1 2 near / 1 far / 0 nothing) and,
 * if something was found, plays a 42-frame sniff (sound 0x945, pose PCH_Y_1) and
 * then a 1.5 s speech-bubble effect over her. In the retail versions a far find skips the sniff.
 */
static USER_FUNC(search_result) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());

    if (isFirstCall) {
        if ((u32)event->lwData[0] == 0 || event->lwData[1] == 0) {
            return EVT_RETURN_DONE;
        }
#if VERSION >= VERSION_JP
        if (event->lwData[1] == 1) {
            if (party) {
                ((EffFukidashiEntryRetVoidptrS32Fn)effFukidashiEntry)(6, 0, -2, 0.0f, 18.0f, 0.0f, 0.0f, 0.0f, sysMsec2Frame(1500));
            }
            return EVT_RETURN_DONE;
        }
#endif
        psndSFXOn_3D((const char*)0x945, &party->position);
        event->userdata3 = 42;
        partyChgPose(party, "PCH_Y_1");
    }
    partyChkGnd(party);
    if ((s32)--event->userdata3 > 0) {
        return EVT_RETURN_BLOCK;
    }
    if (party) {
        ((EffFukidashiEntryRetVoidptrS32Fn)effFukidashiEntry)(6, 0, -2, 0.0f, 18.0f, 0.0f, 0.0f, 0.0f, sysMsec2Frame(1500));
    }
    return EVT_RETURN_DONE;
}

#if VERSION <= VERSION_DEMO_US
/**
 * The demo stops at the first item or block in range and has no buried treasure table.
 * Script helper: looks for an item and then a block from mobj_list within 150 units of Mario, then anywhere;
 * sets LW0 to map_exist_near / map_exist_far / map_no_exist and LW1 to 2 / 1 / 0, and turns Ms. Mowz to face it.
 */
static USER_FUNC(set_msg) {
    int pass;
    ChuchuParty* cp = (ChuchuParty*)partyGetPtr(marioGetPartyId());
    MarioWork* player = cp->player;
    PartyEntry* party = (PartyEntry*)cp;
    ItemEntry* item;
    MapObjectEntry* mobj;
    f32 range;

    event->lwData[0] = 0;
    event->lwData[1] = 0;
    if (!party) {
        return EVT_RETURN_DONE;
    }
    for (pass = 0; pass < 2; pass++) {
        if (pass == 0) {
            range = 150.0f;
        } else {
            range = 10000.0f;
        }
        item = itemNearDistCheck(player->position.x, player->position.y, player->position.z, range);
        if (item) {
            event->lwData[0] = (EvtWord)(pass == 0 ? "map_exist_near" : "map_exist_far");
            event->lwData[1] = (pass == 0) + 1;
            cp->displayDirectionTarget = (revise360(angleABf(cp->position.x, cp->position.z, item->position.x, item->position.z) - cp->camDir) <= 180.0f) ? 180.0f : 0.0f;
            cp->moveDir = partyToMovedir(party, cp->displayDirectionTarget);
            cp->targetDir = cp->moveDir;
            return EVT_RETURN_DONE;
        }
        mobj = mobjNearDistCheck2(player->position.x, player->position.y, player->position.z, range, mobj_list);
        if (mobj) {
            event->lwData[0] = (EvtWord)(pass == 0 ? "map_exist_near" : "map_exist_far");
            event->lwData[1] = (pass == 0) + 1;
            cp->displayDirectionTarget = (revise360(angleABf(cp->position.x, cp->position.z, mobj->position.x, mobj->position.z) - cp->camDir) <= 180.0f) ? 180.0f : 0.0f;
            cp->moveDir = partyToMovedir(party, cp->displayDirectionTarget);
            cp->targetDir = cp->moveDir;
            return EVT_RETURN_DONE;
        }
    }
    event->lwData[0] = (EvtWord) "map_no_exist";
    event->lwData[1] = 0;
    return EVT_RETURN_DONE;
}
#else
/**
 * Finds the nearest entry of chuchu_treasure_tbl on the current map whose flag is still 0
 * and within range of Mario; returns 1 and its position if there is one.
 * Guess: the table lists hidden floor items such as buried Star Pieces.
 */
static inline int chuchu_findTreasure2(ChuchuParty* cpp, f32 range, Vec* bestPos) {
    u32 i;
    int found;
    MarioWork* mario;
    ChuchuTreasure* tbl;
    f32 minDist;

    found = 0;
    mario = cpp->player;
    minDist = 10000.0f;
    tbl = chuchu_treasure_tbl;
    for (i = 0; i < 40; i++, tbl++) {
        if (strcmp(gp->currentMapName, tbl->map) == 0 && evtGetValue(NULL, tbl->flag) == 0) {
            Vec pos;
            Vec p = vecB;
            f32 d;
            p.x = tbl->x;
            p.y = tbl->y;
            p.z = tbl->z;
            pos = p;
            d = PSVECDistance(&mario->position, &pos);
            if (!(range < d) && minDist > d) {
                minDist = d;
                found = 1;
                bestPos->x = pos.x;
                bestPos->y = pos.y;
                bestPos->z = pos.z;
            }
        }
    }
    return found;
}

/**
 * Script helper: looks within 150 units of Mario, then anywhere, for the nearest item,
 * block from mobj_list or hidden spot from chuchu_treasure_tbl;
 * sets LW0 to map_exist_near / map_exist_far / map_no_exist and LW1 to 2 / 1 / 0,
 * and turns Ms. Mowz left or right toward it.
 */
static USER_FUNC(set_msg) {
    MapObjectEntry* mobj;
    ItemEntry* item;
    int found;
    MarioWork* player;
    int pass;
    int type;
    ChuchuParty* cp = (ChuchuParty*)partyGetPtr(marioGetPartyId());
    PartyEntry* party = (PartyEntry*)cp;
    f32 range;
    f32 minDist;
    f32 angle;
    f32 d;
    Vec bestPos;
    Vec tmp;
    Vec ip;
    Vec p;
    Vec pos;

    player = cp->player;
    event->lwData[0] = 0;
    event->lwData[1] = 0;
    if (!party) {
        return EVT_RETURN_DONE;
    }

    for (pass = 0; pass < 2; pass++) {
        if (pass == 0) {
            range = 150.0f;
        } else {
            range = 10000.0f;
        }
        type = -1;
        item = itemNearDistCheck(player->position.x, player->position.y, player->position.z, range);
        mobj = mobjNearDistCheck2(player->position.x, player->position.y, player->position.z, range, mobj_list);
        found = chuchu_findTreasure2(cp, range, &bestPos);

        minDist = 10000.0f;
        if (item) {
            ip = vecA;
            ip.x = item->position.x;
            ip.y = item->position.y;
            ip.z = item->position.z;
            tmp = ip;
            if (minDist > PSVECDistance(&tmp, &player->position)) {
                minDist = PSVECDistance(&tmp, &player->position);
                angle = revise360(angleABf(cp->position.x, cp->position.z, item->position.x, item->position.z) - cp->camDir);
                type = 0;
            }
        }
        if (mobj) {
            if (minDist > PSVECDistance(&mobj->position, &player->position)) {
                minDist = PSVECDistance(&mobj->position, &player->position);
                angle = revise360(angleABf(cp->position.x, cp->position.z, mobj->position.x, mobj->position.z) - cp->camDir);
                type = 1;
            }
        }
        if (found) {
            if (minDist > PSVECDistance(&bestPos, &player->position)) {
                minDist = PSVECDistance(&bestPos, &player->position);
                angle = revise360(angleABf(cp->position.x, cp->position.z, bestPos.x, bestPos.z) - cp->camDir);
                type = 2;
            }
        }
        if (type >= 0) {
            break;
        }
    }

    if (type >= 0) {
        if (range == 150.0f) {
            event->lwData[0] = (EvtWord) "map_exist_near";
            event->lwData[1] = 2;
        } else {
            event->lwData[0] = (EvtWord) "map_exist_far";
            event->lwData[1] = 1;
        }
        cp->displayDirectionTarget = (angle <= 180.0f) ? 180.0f : 0.0f;
        cp->moveDir = partyToMovedir(party, cp->displayDirectionTarget);
        cp->targetDir = cp->moveDir;
    } else {
        event->lwData[0] = (EvtWord) "map_no_exist";
        event->lwData[1] = 0;
    }
    return EVT_RETURN_DONE;
}
#endif

/** Script helper: clears LW0 and advances Ms. Mowz's use step (22 to 23) so chuchu_use ends the search. */
static USER_FUNC(post_msg) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());

    event->lwData[0] = 0;
    if (party) {
        party->useMotionId++;
    }
    return EVT_RETURN_DONE;
}

#if VERSION <= VERSION_DEMO_US
/**
 * Whether there is something to sniff within 150 units of Mario (an item, an unopened item box,
 * a Kururin floor item or a block from mobj_list);
 * party_motion.c and party_move.c play her sniffing pose while it is TRUE.
 */
BOOL chuchu_searchObject(void) {
    char** name;
    ChuchuParty* cp = (ChuchuParty*)partyGetPtr(marioGetPartyId());
    MapObjectEntry* mobj;
    MarioWork* mario = cp->player;

    if (itemNearDistCheck(mario->position.x, mario->position.y, mario->position.z, 150.0f)) {
        return TRUE;
    }
    mobj = mobjNearDistCheck(mario->position.x, mario->position.y, mario->position.z, 150.0f);
    if (mobj) {
        if (mobjCheckItemboxOpen(mobj) == 1) {
            return TRUE;
        }
        if (mobjCheckKururingFloorItem(mobj) == 2) {
            return TRUE;
        }
        for (name = mobj_list; *name != NULL; name++) {
            if (strcmp(mobj->animName, *name) == 0) {
                return TRUE;
            }
        }
    }
    return FALSE;
}
#else
/** Whether any unfound chuchu_treasure_tbl entry on the current map is within range of Mario. */
static inline int chuchu_findTreasure(ChuchuParty* cpp, f32 range) {
    u32 i;
    int found;
    MarioWork* mario;
    ChuchuTreasure* tbl;
    f32 minDist;

    found = 0;
    mario = cpp->player;
    tbl = chuchu_treasure_tbl;
    minDist = 10000.0f;
    for (i = 0; i < 40; i++, tbl++) {
        if (strcmp(gp->currentMapName, tbl->map) == 0 && evtGetValue(NULL, tbl->flag) == 0) {
            Vec pos;
            Vec p = vecB;
            f32 d;
            p.x = tbl->x;
            p.y = tbl->y;
            p.z = tbl->z;
            pos = p;
            d = PSVECDistance(&mario->position, &pos);
            if (!(range < d) && minDist > d) {
                minDist = d;
                found = 1;
            }
        }
    }
    return found;
}

/**
 * Whether there is something to sniff within 150 units of Mario (an item,
 * a block or box from mobj_list or a chuchu_treasure_tbl spot);
 * party_motion.c and party_move.c play her sniffing pose while it is TRUE.
 */
BOOL chuchu_searchObject(void) {
    ChuchuParty* cp = (ChuchuParty*)partyGetPtr(marioGetPartyId());
    MarioWork* player = cp->player;
    ChuchuTreasure* tbl;
    MarioWork* player2;
    int found;
    u32 i;
    f32 minDist;

    if (itemNearDistCheck(player->position.x, player->position.y, player->position.z, 150.0f)) {
        return TRUE;
    }
    if (mobjNearDistCheck2(player->position.x, player->position.y, player->position.z, 150.0f, mobj_list)) {
        return TRUE;
    }
    return chuchu_findTreasure(cp, 150.0f) != 0;
}
#endif

/** Party table init handler: Ms. Mowz is member kind 7, 20 units tall and 24 wide. */
void chuchu_init(PartyEntry* party) {
    ChuchuParty* cp = (ChuchuParty*)party;

    cp->memberKind = 7;
    cp->moveKind = 0;
    cp->height = 20.0f;
    cp->width = 24.0f;
}

/** Called from partyReInit when Ms. Mowz is the partner; does nothing. */
void chuchu_reinit(PartyEntry* party) {
}

/** Party table exit handler; does nothing. */
void chuchu_exit(PartyEntry* party) {
}

/**
 * Party table move handler: on a run-mode change clears the in-use flag and starts walking;
 * then follows Mario (the retail versions also update her walk speed first).
 */
void chuchu_move(PartyEntry* party) {
    if (party->trigFlags & PARTY_TRIG_FLAG_CHG_RUN_MODE) {
        party->trigFlags &= ~PARTY_TRIG_FLAG_CHG_RUN_MODE;
        party->flags &= ~PARTY_FLAG_IS_BEING_USED;
        // FAKE: the call passes a second argument partyWalkInit does not take (no effect); the cast keeps it.
        ((void (*)(PartyEntry*, s32))partyWalkInit)(party, 1);
    }
#if VERSION >= VERSION_JP
    partyUpdMoveSpd(party);
#endif
    partyWalkMain(party);
}

/**
 * Party table use handler for her search ability:
 * freezes the game at system level 1, glides beside Mario over 4 frames, faces his way, waits 25 frames,
 * sniffs (sound 0x944, pose PCH_A2_1) for 30, runs msg_evt,
 * and once post_msg advances the step ends the use and unfreezes.
 */
void chuchu_use(PartyEntry* party) {
    ChuchuParty* cp = (ChuchuParty*)party;
    MarioWork* mario = cp->player;
    Vec pos;
    Vec pos1;

    if (cp->trigFlags & PARTY_TRIG_FLAG_CHG_RUN_MODE) {
        cp->trigFlags &= ~PARTY_TRIG_FLAG_CHG_RUN_MODE;
        cp->state = 0;
        marioStSystemLevel(1);
    }

    switch (cp->state) {
        case 0:
            partyGetAppearPos3(party, &pos);
            cp->target = pos;
            cp->timer = 4;
            cp->moveDir = angleABf(cp->position.x, cp->position.z, cp->target.x, cp->target.z);
            cp->targetDir = cp->moveDir;
            cp->displayDirection = mario->displayDirection;
            cp->displayDirectionTarget = mario->displayDirection;
            cp->moveSpeed = distABf(cp->position.x, cp->position.z, cp->target.x, cp->target.z) / cp->timer;
            cp->velY = 0.0f;
            cp->state = 1;
            break;
        case 1:
            partyGetAppearPos3(party, &pos1);
            cp->target = pos1;
            cp->position.x += (cp->target.x - cp->position.x) / cp->timer;
            cp->position.y += (cp->target.y - cp->position.y) / cp->timer;
            cp->position.z += (cp->target.z - cp->position.z) / cp->timer;
            if (--cp->timer > 0) {
                return;
            }
            partyChgPoseId(party, 1);
            cp->moveSpeed = 0.0f;
            cp->state = 10;
            break;
        case 10:
            cp->displayDirectionTarget = mario->displayDirectionTarget;
            cp->moveDir = toMovedir(cp->displayDirectionTarget);
            cp->targetDir = cp->moveDir;
            cp->state = 20;
            cp->timer = 25;
            break;
        case 20:
            if (--cp->timer > 0) {
                break;
            }
            psndSFXOn_3D((const char*)0x944, &cp->position);
            partyChgPose(party, "PCH_A2_1");
            cp->state = 21;
            cp->timer = 30;
        case 21:
            if (--cp->timer > 0) {
                break;
            }
            partyChgPoseId(party, 1);
            evtEntryType(msg_evt, 0, 0, 26);
            cp->state = 22;
            break;
        case 23:
            partyChgPoseId(party, 1);
            cp->state = 80;
            break;
    }

    switch (cp->state) {
        case 80:
            cp->flags &= ~0x100;
            partyChgRunMode(party, 2);
            cp->moveMode = 0;
            marioChgMot(MARIO_MOTION_STAY);
            marioStSystemLevel(0);
            break;
    }
    partyChkGnd(party);
}
