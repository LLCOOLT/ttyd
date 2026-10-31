// Inn scripts and helpers: the innkeeper talk, payment, sleeping in the bed and breakfast.
#include "evt/evt_cmd.h"
#include "evt/evt_cam.h"
#include "evt/evt_fade.h"
#include "evt/evt_npc.h"
#include "evt/evt_snd.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/itemdrv.h"
#include "driver/npcdrv.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "pmario_sound.h"
#include <string.h>
#include "evt/evt_kinopio.h"
#include "libc_decls.h"
#include "version.h"
#include "evt/evt_story.h"

extern USER_FUNC(evt_eff);
extern USER_FUNC(evt_eff_fukidashi);
extern USER_FUNC(evt_fade_end_wait);
extern USER_FUNC(evt_fade_set_spot_pos);
extern USER_FUNC(evt_mario_adjust_dir);
extern USER_FUNC(evt_mario_dispflag_onoff);
extern USER_FUNC(evt_mario_flag_onoff);
extern USER_FUNC(evt_mario_get_exparty);
extern USER_FUNC(evt_mario_get_party);
extern USER_FUNC(evt_mario_get_pos);
extern USER_FUNC(evt_mario_goodbye_party);
extern USER_FUNC(evt_mario_jump_pos);
extern USER_FUNC(evt_mario_key_onoff);
extern USER_FUNC(evt_mario_mov_pos2);
extern USER_FUNC(evt_mario_set_dir_npc);
extern USER_FUNC(evt_mario_set_party_pos);
extern USER_FUNC(evt_mario_set_pos);
extern USER_FUNC(evt_msg_print);
extern USER_FUNC(evt_msg_print_add);
extern USER_FUNC(evt_msg_print_insert);
extern USER_FUNC(evt_msg_select);
extern USER_FUNC(evt_npc_set_tribe);
extern USER_FUNC(evt_party_run);
extern USER_FUNC(evt_party_set_dir_npc);
extern USER_FUNC(evt_party_set_pos);
extern USER_FUNC(evt_pouch_add_coin);
extern USER_FUNC(evt_pouch_all_party_recovery);
extern USER_FUNC(evt_pouch_check_item);
extern USER_FUNC(evt_pouch_mario_recovery);
extern USER_FUNC(evt_pouch_remove_item);
extern USER_FUNC(evt_set_dir_to_target);
extern USER_FUNC(evt_snd_bgmoff);
extern USER_FUNC(evt_snd_sfxon);
extern USER_FUNC(evt_sub_get_coin);
extern USER_FUNC(evt_sub_get_mapname);
extern USER_FUNC(evt_win_coin_off);
extern USER_FUNC(evt_win_coin_on);

typedef struct KinopioParty {
    u16 flags;
    s16 maximumHP;
    s16 pad4;
    s16 currentHP;
    s16 pad8[3];
} KinopioParty;

typedef s32 (*KinopioGetter)(void);

typedef struct KinopioWork {
    s32 breakfastItem; // 0x0
    Vec breakfastPos;  // 0x4
    s32 ryoukin;       // 0x10
    Vec bed;           // 0x14
    Vec bedside;       // 0x20
    f32 cam[6];        // 0x2C
    f32 bedDeg;        // 0x44
    Vec npcTalk;       // 0x48
    char* npcName;     // 0x54
    s32 msg[14];       // 0x58
    s32 toBedEvt;      // 0x90
    s32 fromBedEvt;    // 0x94
} KinopioWork;

static USER_FUNC(paper_off);
static USER_FUNC(paper_on);

//.sbss
static KinopioWork* work;

//.sdata
static KinopioWork** wp = &work;

USER_FUNC(evt_kinopio_setup) {
    KinopioWork* w = (KinopioWork*)evtGetValue(event, event->args[0]);
    NpcEntry* npc = npcNameToPtr(w->npcName);
    if (!animGroupBaseAsync("p_slit", 0, NULL)) {
        return 0;
    }
    npc->talkEvt = kinopio_house_talk_evt;
    *wp = w;
    return 2;
}

USER_FUNC(msg_no) {
    EvtWord* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    evtSetValue(event, args[1], (*wp)->msg[idx]);
    return 2;
}

USER_FUNC(power_chk) {
    EvtWord* args = event->args;
    s32 ok;
    s32 i;
    KinopioParty* pouch = (KinopioParty*)pouchGetPtr();
    ok = 1;
    for (i = 0; i < 8; i++) {
        if ((pouch[i].flags & 1) && pouch[i].currentHP != pouch[i].maximumHP) {
            ok = 0;
            break;
        }
    }
    if (((KinopioGetter)pouchGetHP)() == ((KinopioGetter)pouchGetMaxHP)() && ((KinopioGetter)pouchGetFP)() == ((KinopioGetter)pouchGetMaxFP)() && ((KinopioGetter)pouchGetAP)() == ((KinopioGetter)pouchGetMaxAP)() && ok) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return 2;
}

USER_FUNC(coin_chk) {
    EvtWord* args = event->args;
    if (pouchGetCoin() < (*wp)->ryoukin) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return 2;
}

USER_FUNC(get_ryoukin) {
    evtSetValue(event, event->args[0], (*wp)->ryoukin);
    return 2;
}

USER_FUNC(get_npcname) {
    evtSetValue(event, event->args[0], (EvtWord)(*wp)->npcName);
    return 2;
}

USER_FUNC(get_bed) {
    EvtWord* args = event->args;
    evtSetFloat(event, args[0], (*wp)->bed.x);
    evtSetFloat(event, args[1], (*wp)->bed.y);
    evtSetFloat(event, args[2], (*wp)->bed.z);
    return 2;
}

USER_FUNC(get_bedside) {
    EvtWord* args = event->args;
    evtSetFloat(event, args[0], (*wp)->bedside.x);
    evtSetFloat(event, args[1], (*wp)->bedside.y);
    evtSetFloat(event, args[2], (*wp)->bedside.z);
    return 2;
}

USER_FUNC(get_beddeg) {
    evtSetFloat(event, event->args[0], (*wp)->bedDeg);
    return 2;
}

USER_FUNC(get_npctalk) {
    EvtWord* args = event->args;
    evtSetFloat(event, args[0], (*wp)->npcTalk.x);
    evtSetFloat(event, args[1], (*wp)->npcTalk.y);
    evtSetFloat(event, args[2], (*wp)->npcTalk.z);
    return 2;
}

USER_FUNC(get_cam) {
    EvtWord* args = event->args;
    evtSetFloat(event, args[0], (*wp)->cam[0]);
    evtSetFloat(event, args[1], (*wp)->cam[1]);
    evtSetFloat(event, args[2], (*wp)->cam[2]);
    evtSetFloat(event, args[3], (*wp)->cam[3]);
    evtSetFloat(event, args[4], (*wp)->cam[4]);
    evtSetFloat(event, args[5], (*wp)->cam[5]);
    return 2;
}

USER_FUNC(get_to_bed_evt) {
    evtSetValue(event, event->args[0], (*wp)->toBedEvt);
    return 2;
}

USER_FUNC(get_from_bed_evt) {
    evtSetValue(event, event->args[0], (*wp)->fromBedEvt);
    return 2;
}

static USER_FUNC(paper_on) {
    EvtWord* args = event->args;
    f32 amount = evtGetFloat(event, *args++);
    MarioWork* mario = marioGetPtr();
    if (isFirstCall) {
        marioPaperOn("p_slit");
        marioChgPose("M_S_1");
        marioChgPaper("PM_S_3A");
#if VERSION != VERSION_DEMO
        event->userdata[0] = 0;
#endif
    }
#if VERSION != VERSION_DEMO
    // the demo only turns Mario, without the 30-frame slide
    if (event->userdata[0] < 30) {
        f32 ang;
        if (strcmp(gp->currentMapName, "pik_04") == 0) {
            ang = 6.2831855f * amount / 360.0f;
            mario->position.x -= 0.2f * (f32)cos(ang);
            mario->position.z -= 0.2f * (f32)sin(ang);
        } else {
            ang = 6.2831855f * amount / 360.0f;
            mario->position.x += 0.2f * (f32)cos(ang);
            mario->position.z += 0.2f * (f32)sin(ang);
        }
        event->userdata[0]++;
    }
#endif
    mario->displayDirectionTarget = amount;
    mario->displayDirection = amount;
    return 0;
}

static USER_FUNC(paper_off) {
    marioPaperOff();
    return 2;
}

USER_FUNC(offset) {
    EvtWord* args = event->args;
    f32 dist = evtGetFloat(event, args[0]);
    f32 ang = 6.2831855f * (90.0f + camGetPtr(CAMERA_3D)->viewYaw) / 360.0f;
    evtSetFloat(event, args[1], dist * -(f32)sin(ang));
    evtSetFloat(event, args[2], dist * (f32)cos(ang));
    return 2;
}

USER_FUNC(breakfast) {
    ItemEntry* item = itemNameToPtr("breakfast");
    if (item == NULL || !(item->flags & ITEM_FLAG_USED)) {
        KinopioWork* w = *wp;
        if (w->breakfastItem != 0) {
#if VERSION == VERSION_DEMO
            itemEntry(w->breakfastPos.x, w->breakfastPos.y, w->breakfastPos.z, "breakfast", w->breakfastItem, 0xF, -1, 0);
#else
            itemEntry(w->breakfastPos.x, w->breakfastPos.y, w->breakfastPos.z, "breakfast", w->breakfastItem, 0x10, -1, 0);
#endif
        }
    }
    return 2;
}

USER_FUNC(snd_off) {
    psndSetFlag(PSND_FLAG_MUTE_SFX);
    return 2;
}

USER_FUNC(snd_on) {
    psndClearFlag(PSND_FLAG_MUTE_SFX);
    return 2;
}

#if VERSION != VERSION_DEMO
USER_FUNC(N_cameraman_on) {
    NpcEntry* npc = npcNameToPtr("宿屋のカメラマン");
    animPoseSetMaterialFlagOn(npc->poseId, ANIM_MATERIAL_FLAG_NO_BLEND | ANIM_MATERIAL_FLAG_NO_BLEND2);
    return 2;
}
#endif

//.data
#if VERSION == VERSION_DEMO
EVT_BEGIN(kinopio_house_talk_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(get_ryoukin, LW(10))
    CALL(get_npcname, LW(11))
    CALL(evt_win_coin_on, 0, LW(12))
    CALL(msg_no, 0, LW(0))
    CALL(evt_msg_print_insert, 0, LW(0), 0, LW(11), LW(10))
    CALL(msg_no, 6, LW(0))
    CALL(evt_msg_select, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(msg_no, 2, LW(0))
        CALL(evt_msg_print_add, 0, LW(0))
        CALL(evt_mario_key_onoff, 1)
        CALL(evt_win_coin_off, LW(12))
        RETURN
    END_IF
    CALL(power_chk, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(msg_no, 1, LW(0))
        CALL(evt_msg_print_add, 0, LW(0))
        CALL(msg_no, 6, LW(0))
        CALL(evt_msg_select, 0, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(msg_no, 2, LW(0))
            CALL(evt_msg_print_add, 0, LW(0))
            CALL(evt_mario_key_onoff, 1)
            CALL(evt_win_coin_off, LW(12))
            RETURN
        END_IF
    END_IF
    SET_VALUE(LF(0), 0)
    CALL(evt_pouch_check_item, ITEM_INN_COUPON, LW(0))
    IF_INT_GREATER(LW(0), 0)
        CALL(msg_no, 7, LW(0))
        CALL(evt_msg_print_add, 0, LW(0))
        CALL(msg_no, 8, LW(0))
        CALL(evt_msg_select, 0, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LF(0), 1)
            CALL(evt_pouch_remove_item, ITEM_INN_COUPON, LW(0))
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        CALL(coin_chk, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(msg_no, 4, LW(0))
            CALL(evt_msg_print_add, 0, LW(0))
            CALL(evt_mario_key_onoff, 1)
            CALL(evt_win_coin_off, LW(12))
            RETURN
        END_IF
        CALL(get_ryoukin, LW(10))
        MULTIPLY(LW(10), -1)
        CALL(evt_pouch_add_coin, LW(10))
        WAIT_MS(1000)
    END_IF
    CALL(evt_win_coin_off, LW(12))
    CALL(msg_no, 3, LW(0))
    CALL(evt_msg_print_add, 0, LW(0))
    CALL(get_npcname, LW(0))
    CALL(evt_npc_flag_onoff, 1, LW(0), NPC_FLAG_INTANGIBLE)
    CALL(evt_mario_get_party, LW(11))
    CALL(evt_mario_get_exparty, LW(12))
    CALL(evt_mario_get_pos, 0, LW(13), LW(14), LW(15))
    CALL(evt_mario_goodbye_party, 1)
    CALL(evt_mario_goodbye_party, 0)
    CALL(get_to_bed_evt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        BEGIN_INLINE_EVENT
            WAIT_MS(1000)
            CALL(get_cam, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
            CALL(evt_cam3d_evt_set, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), 0, 11)
        END_INLINE_EVENT
        CALL(get_bedside, LW(0), LW(1), LW(2))
        CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(60.0f))
    ELSE
        BEGIN_INLINE_EVENT_GET_ID(LW(0))
            CALL_CHILD(LW(0))
        END_INLINE_EVENT
        LOOP(0)
            IS_EVENT_RUNNING(LW(0), LW(1))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(get_cam, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
        CALL(evt_cam3d_evt_set, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), 0, 11)
        WAIT_MS(500)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FLD_JUMP2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_flag_onoff, 1, 768)
    CALL(get_bed, LW(0), LW(1), LW(2))
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), FLOAT(400.0f), 0, -1000)
    CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
    CALL(evt_mario_adjust_dir)
    WAIT_MS(200)
    BEGIN_INLINE_EVENT_GET_ID(LW(10))
        CALL(get_beddeg, LW(0))
        CALL(paper_on, LW(0))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_MARIO_SLEEP1"), LW(0), LW(1), LW(2), 0)
        WAIT_MS(200)
        CALL(evt_snd_sfxon_3d, STRING("SFX_OFF_MARIO_SLEEP2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(snd_off)
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_GO_SLEEPING1"))
    CALL(evt_fade_entry, FADE_OUT_SPOT, 3000, 0, 0, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_fade_set_spot_pos, LW(0), LW(1), LW(2))
    CALL(evt_fade_end_wait)
    CALL(evt_fade_entry, FADE_OUT_BLACK_2D, 0, 0, 0, 0)
    CALL(evt_fade_end_wait)
    CALL(evt_pouch_mario_recovery)
    CALL(evt_pouch_all_party_recovery)
    CALL(breakfast)
    WAIT_MS(3000)
    DELETE_EVENT(LW(10))
    CALL(paper_off)
    IF_INT_NOT_EQUAL(LW(11), 0)
        CALL(get_bed, LW(0), LW(1), LW(2))
        CALL(evt_mario_set_party_pos, 0, LW(11), LW(0), LW(1), LW(2))
    END_IF
    IF_INT_NOT_EQUAL(LW(12), 0)
        CALL(get_bed, LW(0), LW(1), LW(2))
        CALL(offset, FLOAT(30.0f), LW(3), LW(4))
        ADD_FLOAT(LW(0), LW(3))
        ADD_FLOAT(LW(2), LW(4))
        CALL(evt_mario_set_party_pos, 1, LW(12), LW(0), LW(1), LW(2))
    END_IF
    CALL(evt_mario_flag_onoff, 0, 768)
    CALL(get_bedside, LW(0), LW(1), LW(2))
    CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
    CALL(get_npcname, LW(0))
    CALL(evt_set_dir_to_target, LW(0), STRING("mario"))
    CALL(evt_mario_set_dir_npc, LW(0))
    CALL(evt_party_set_dir_npc, 0, LW(0))
    CALL(evt_party_set_dir_npc, 1, LW(0))
    CALL(evt_mario_adjust_dir)
    CALL(evt_npc_flag_onoff, 1, LW(0), NPC_FLAG_INSTANT_TURN)
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_npc_flag_onoff, 0, LW(0), NPC_FLAG_INSTANT_TURN)
    ADD(GSW(GSW_INN_STAY_COUNT), 1)
    IF_INT_GREATER(GSW(GSW_INN_STAY_COUNT), 100)
        SET_VALUE(GSW(GSW_INN_STAY_COUNT), 100)
    END_IF
    IF_INT_EQUAL(GSW(GSW_INN_STAY_COUNT), 50)
        CALL_CHILD(evt_50)
        RETURN
    END_IF
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(snd_on)
    CALL(evt_fade_entry, FADE_IN_BLACK_2D, 1000, 0, 0, 0)
    CALL(evt_fade_end_wait)
    CALL(get_from_bed_evt, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        BEGIN_INLINE_EVENT_GET_ID(LW(10))
            CALL_CHILD(LW(0))
        END_INLINE_EVENT
        LOOP(0)
            IS_EVENT_RUNNING(LW(10), LW(11))
            IF_INT_EQUAL(LW(11), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_IF
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
    CALL(get_npctalk, LW(0), LW(1), LW(2))
    CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(60.0f))
    CALL(evt_fade_end_wait)
    CALL(get_npcname, LW(11))
    CALL(msg_no, 5, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(11))
    CALL(get_npcname, LW(0))
    CALL(evt_npc_flag_onoff, 0, LW(0), NPC_FLAG_INTANGIBLE)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
#else
EVT_BEGIN(kinopio_house_talk_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(get_ryoukin, LW(10))
    CALL(get_npcname, LW(11))
    CALL(evt_win_coin_on, 0, LW(12))
    CALL(msg_no, 0, LW(0))
    CALL(evt_msg_print_insert, 0, LW(0), 0, LW(11), LW(10))
    CALL(msg_no, 6, LW(0))
    CALL(evt_msg_select, 0, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(msg_no, 2, LW(0))
        CALL(evt_msg_print_add, 0, LW(0))
        CALL(evt_mario_key_onoff, 1)
        CALL(evt_win_coin_off, LW(12))
        RETURN
    END_IF
    CALL(power_chk, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(msg_no, 1, LW(0))
        CALL(evt_msg_print_add, 0, LW(0))
        CALL(msg_no, 6, LW(0))
        CALL(evt_msg_select, 0, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(msg_no, 2, LW(0))
            CALL(evt_msg_print_add, 0, LW(0))
            CALL(evt_mario_key_onoff, 1)
            CALL(evt_win_coin_off, LW(12))
            RETURN
        END_IF
    END_IF
    SET_VALUE(LF(0), 0)
    CALL(evt_pouch_check_item, ITEM_INN_COUPON, LW(0))
    IF_INT_GREATER(LW(0), 0)
        CALL(msg_no, 7, LW(0))
        CALL(evt_msg_print_add, 0, LW(0))
        CALL(msg_no, 8, LW(0))
        CALL(evt_msg_select, 0, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LF(0), 1)
            CALL(evt_pouch_remove_item, ITEM_INN_COUPON, LW(0))
        END_IF
    END_IF
    IF_INT_EQUAL(LF(0), 0)
        CALL(coin_chk, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL(msg_no, 4, LW(0))
            CALL(evt_msg_print_add, 0, LW(0))
            CALL(evt_mario_key_onoff, 1)
            CALL(evt_win_coin_off, LW(12))
            RETURN
        END_IF
        CALL(get_ryoukin, LW(10))
        MULTIPLY(LW(10), -1)
        CALL(evt_pouch_add_coin, LW(10))
        WAIT_MS(1000)
    END_IF
    CALL(evt_win_coin_off, LW(12))
    CALL(msg_no, 3, LW(0))
    CALL(evt_msg_print_add, 0, LW(0))
    CALL(get_npcname, LW(0))
    CALL(evt_npc_flag_onoff, 1, LW(0), NPC_FLAG_INTANGIBLE)
    CALL(evt_mario_get_party, LW(11))
    CALL(evt_mario_get_exparty, LW(12))
    CALL(evt_mario_get_pos, 0, LW(13), LW(14), LW(15))
    CALL(evt_mario_goodbye_party, 1)
    CALL(evt_mario_goodbye_party, 0)
    CALL(get_to_bed_evt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        BEGIN_INLINE_EVENT
            WAIT_MS(1000)
            CALL(get_cam, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
            CALL(evt_cam3d_evt_set, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), 0, 11)
        END_INLINE_EVENT
        CALL(get_bedside, LW(0), LW(1), LW(2))
        CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(90.0f))
    ELSE
        BEGIN_INLINE_EVENT_GET_ID(LW(0))
            CALL_CHILD(LW(0))
        END_INLINE_EVENT
        LOOP(0)
            IS_EVENT_RUNNING(LW(0), LW(1))
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(get_cam, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
        CALL(evt_cam3d_evt_set, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), 0, 11)
        WAIT_MS(500)
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, 131230, LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_flag_onoff, 1, 1792)
    CALL(get_bed, LW(0), LW(1), LW(2))
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), FLOAT(400.0f), 0, -1000)
    CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
    CALL(evt_mario_adjust_dir)
    WAIT_MS(200)
    CALL(evt_mario_dispflag_onoff, 1, MARIO_DISP_FLAG_NO_SHADOW)
    BEGIN_INLINE_EVENT_GET_ID(LW(10))
        CALL(get_beddeg, LW(0))
        CALL(paper_on, LW(0))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, 132026, LW(0), LW(1), LW(2), 0)
        WAIT_MS(200)
        CALL(evt_snd_sfxon_3d, 132027, LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(snd_off)
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_GO_SLEEPING1"))
#if VERSION >= VERSION_US
    CALL(evt_fade_entry, FADE_OUT_SPOT, 6000, 0, 0, 0)
#else
    CALL(evt_fade_entry, FADE_OUT_SPOT, 3000, 0, 0, 0)
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_fade_set_spot_pos, LW(0), LW(1), LW(2))
    CALL(evt_fade_end_wait)
    CALL(evt_fade_entry, FADE_OUT_BLACK_2D, 0, 0, 0, 0)
    CALL(evt_fade_end_wait)
    CALL(evt_pouch_mario_recovery)
    CALL(evt_pouch_all_party_recovery)
    CALL(breakfast)
    WAIT_MS(3000)
    DELETE_EVENT(LW(10))
    CALL(paper_off)
    CALL(evt_mario_dispflag_onoff, 0, MARIO_DISP_FLAG_NO_SHADOW)
    IF_INT_NOT_EQUAL(LW(11), 0)
        CALL(get_bed, LW(0), LW(1), LW(2))
        CALL(evt_mario_set_party_pos, 0, LW(11), LW(0), LW(1), LW(2))
    END_IF
    IF_INT_NOT_EQUAL(LW(12), 0)
        CALL(get_bed, LW(0), LW(1), LW(2))
        CALL(offset, FLOAT(30.0f), LW(3), LW(4))
        ADD_FLOAT(LW(0), LW(3))
        ADD_FLOAT(LW(2), LW(4))
        CALL(evt_mario_set_party_pos, 1, LW(12), LW(0), LW(1), LW(2))
    END_IF
    CALL(evt_mario_flag_onoff, 0, 1792)
    CALL(get_bedside, LW(0), LW(1), LW(2))
    CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
    CALL(get_npcname, LW(0))
    CALL(evt_set_dir_to_target, LW(0), STRING("mario"))
    CALL(evt_mario_set_dir_npc, LW(0))
    CALL(evt_party_set_dir_npc, 0, LW(0))
    CALL(evt_party_set_dir_npc, 1, LW(0))
    CALL(evt_npc_flag_onoff, 1, LW(0), NPC_FLAG_INSTANT_TURN)
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_npc_flag_onoff, 0, LW(0), NPC_FLAG_INSTANT_TURN)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(snd_on)
    ADD(GSW(GSW_INN_STAY_COUNT), 1)
    IF_INT_GREATER(GSW(GSW_INN_STAY_COUNT), 100)
        SET_VALUE(GSW(GSW_INN_STAY_COUNT), 100)
    END_IF
    IF_INT_EQUAL(GSW(GSW_INN_STAY_COUNT), 50)
        CALL_CHILD(evt_50)
        CALL(get_npcname, LW(0))
        CALL(evt_npc_flag_onoff, 0, LW(0), NPC_FLAG_INTANGIBLE)
        RETURN
    END_IF
    CALL(evt_mario_adjust_dir)
    CALL(evt_fade_entry, FADE_IN_BLACK_2D, 1000, 0, 0, 0)
    CALL(evt_fade_end_wait)
    CALL(get_from_bed_evt, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        BEGIN_INLINE_EVENT_GET_ID(LW(10))
            CALL_CHILD(LW(0))
        END_INLINE_EVENT
        LOOP(0)
            IS_EVENT_RUNNING(LW(10), LW(11))
            IF_INT_EQUAL(LW(11), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_IF
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
    CALL(get_npctalk, LW(0), LW(1), LW(2))
    CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(90.0f))
    CALL(evt_fade_end_wait)
    CALL(get_npcname, LW(11))
    CALL(evt_mario_set_dir_npc, LW(11))
    CALL(evt_party_set_dir_npc, 0, LW(11))
    CALL(get_npcname, LW(11))
    CALL(msg_no, 5, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(11))
    CALL(get_npcname, LW(0))
    CALL(evt_npc_flag_onoff, 0, LW(0), NPC_FLAG_INTANGIBLE)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
#endif

#if VERSION == VERSION_DEMO
EVT_BEGIN(evt_50)
    CALL(get_npcname, LW(10))
    CALL(msg_no, 9, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(10))
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(get_bed, LW(0), LW(1), LW(2))
    CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_fade_entry, FADE_IN_BLACK, 1000, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
    CALL(evt_eff, 0, STRING("confetti"), 3, LW(0), LW(1), LW(2), 600, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(msg_no, 10, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(10))
    CALL(get_bedside, LW(0), LW(1), LW(2))
    CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(60.0f))
    CALL(get_npctalk, LW(0), LW(1), LW(2))
    CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(60.0f))
    CALL(msg_no, 11, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(10))
    CALL(evt_fade_entry, FADE_OUT_SPOT, 100, 255, 255, 255)
    CALL(evt_fade_end_wait)
    CALL(evt_fade_entry, FADE_IN_SPOT, 100, 255, 255, 255)
    CALL(evt_fade_end_wait)
    CALL(msg_no, 12, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(10))
    CALL(evt_sub_get_coin, 200)
    CALL(msg_no, 13, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(10))
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
#else
EVT_BEGIN(evt_50)
    CALL(get_npcname, LW(10))
    CALL(evt_npc_get_position, LW(10), LW(13), LW(14), LW(15))
    CALL(evt_npc_entry, STRING("宿屋のカメラマン"), STRING("c_jugem_c"))
    CALL(evt_npc_set_tribe, STRING("宿屋のカメラマン"), STRING("カメラマン"))
    CALL(N_cameraman_on)
    CALL(evt_npc_flag_onoff, 1, STRING("宿屋のカメラマン"), NPC_FLAG_INSTANT_TURN)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("bom_02"))
        CALL(evt_npc_set_position, STRING("宿屋のカメラマン"), -365, 30, -170)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("gor_01"))
        CALL(evt_npc_set_position, STRING("宿屋のカメラマン"), 168, 154, -229)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("muj_01"))
        CALL(evt_npc_set_position, STRING("宿屋のカメラマン"), 270, 20, -145)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("nok_00"))
        CALL(evt_npc_set_position, STRING("宿屋のカメラマン"), -385, 25, -145)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("pik_04"))
        CALL(evt_npc_set_position, STRING("宿屋のカメラマン"), 310, 1329, -100)
        CALL(evt_npc_set_position, LW(10), 310, 1329, -65)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("usu_00"))
        CALL(evt_npc_set_position, STRING("宿屋のカメラマン"), 268, 0, -210)
    END_IF
    CALL(evt_set_dir_to_target, STRING("宿屋のカメラマン"), STRING("mario"))
    CALL(evt_set_dir_to_target, LW(10), STRING("mario"))
    CALL(evt_mario_set_dir_npc, STRING("宿屋のカメラマン"))
    CALL(evt_party_set_dir_npc, 0, STRING("宿屋のカメラマン"))
    CALL(msg_no, 9, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(10))
    CALL(get_bed, LW(0), LW(1), LW(2))
    CALL(evt_mario_set_pos, LW(0), LW(1), LW(2))
    ADD(LW(2), 5)
    CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_fade_entry, FADE_IN_BLACK, 1000, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 100)
    CALL(evt_eff, 0, STRING("confetti"), 3, LW(0), LW(1), LW(2), 600, 0, 0, 0, 0, 0, 0, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_eff_fukidashi, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    CALL(msg_no, 10, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(10))
    CALL(get_bedside, LW(0), LW(1), LW(2))
    CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(90.0f))
    CALL(get_npctalk, LW(0), LW(1), LW(2))
    CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(90.0f))
    CALL(evt_mario_set_dir_npc, LW(10))
    CALL(msg_no, 11, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(10))
    CALL(evt_mario_set_dir_npc, STRING("宿屋のカメラマン"))
    CALL(evt_party_set_dir_npc, 0, STRING("宿屋のカメラマン"))
    WAIT_MS(300)
    CALL(evt_snd_sfxon, STRING("SFX_EVT_50_HOTEL_SHUTTER1"), 0)
    CALL(evt_fade_entry, FADE_OUT_SPOT2, 150, 255, 255, 255)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 40)
    CALL(evt_fade_set_spot_pos, LW(0), LW(1), LW(2))
    CALL(evt_fade_end_wait)
    CALL(evt_fade_entry, FADE_IN_SPOT2, 150, 255, 255, 255)
    CALL(evt_fade_end_wait)
    CALL(msg_no, 12, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(10))
    CALL(evt_mario_set_dir_npc, LW(10))
    CALL(evt_party_set_dir_npc, 0, LW(10))
    WAIT_MS(300)
    CALL(evt_sub_get_coin, 200)
    CALL(msg_no, 13, LW(0))
    CALL(evt_msg_print, 0, LW(0), 0, LW(10))
    CALL(evt_fade_entry, FADE_OUT_BLACK, 1000, 0, 0, 0)
    CALL(evt_fade_end_wait)
    CALL(evt_npc_check_delete, STRING("宿屋のカメラマン"))
    CALL(evt_npc_set_position, LW(10), LW(13), LW(14), LW(15))
    CALL(evt_set_dir_to_target, LW(10), STRING("mario"))
    CALL(evt_fade_entry, FADE_IN_BLACK, 1000, 0, 0, 0)
    CALL(evt_fade_end_wait)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
#endif
