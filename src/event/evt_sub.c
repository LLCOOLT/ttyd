// Miscellaneous script commands and scripts: tree and bush shaking, mail, star stones, splines,
// countdowns, play time, area and language queries.
#include "version.h"
#include "mario/mario_cam.h"
#include "eff/eff_stageclear.h"
#include "eff/eff_itemget.h"
#include "icon_ids.h"
#include "evt/evt_cmd.h"
#include "countdown.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/effdrv.h"
#include "eff/eff_starstone.h"
#include "driver/itemdrv.h"
#include "driver/npcdrv.h"
#include "driver/swdrv.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "pmario_sound.h"
#include "driver/icondrv.h"
#include "memory.h"
#include "mario/mario_pouch.h"
#include "evt/evt_mario.h"
#include "evt/evt_memcard.h"
#include "evt/evt_sub.h"
#include "libc_decls.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_eff.h"
#include "evt/evt_fade.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_party.h"
#include "evt/evt_pouch.h"
#include "evt/evt_snd.h"
#include "evt/evt_window.h"
#include "mario/mario_motion.h"
#include "statuswindow.h"
#include "driver/mapdrv.h"
#include "evt/evt_story.h"
#include <dolphin/pad.h>
#include "driver/casedrv.h"
// FAKE: evt_sub.c calls spline_getvalue through this prototype (the types it was compiled with) instead of the one in driver/mapdrv.h; same registers, behaviour-identical.
typedef void (*Spline_getvalueLocalFn)(f32*, f32, s32, Vec*, f32*, Vec*);

#include "system.h"
#include "driver/msgdrv.h"
#include "manager/fontmgr.h"
#include "manager/winmgr.h"
#include <stdio.h>
#include <dolphin/os.h>

#define KEYFN(name, fn)                         \
    USER_FUNC(name) {                           \
        EvtWord* args = event->args;            \
        s32 chan = evtGetValue(event, args[0]); \
        evtSetValue(event, args[1], fn(chan));  \
        return EVT_RETURN_DONE;                 \
    }

s32 stop;

typedef struct SplineWork {
    s32 n;        // 0x0
    f32* ts;      // 0x4
    Vec* pts;     // 0x8
    Vec* tbl;     // 0xC
    s32 cur;      // 0x10
    s32 steps;    // 0x14
    s32 mode;     // 0x18
    s32 msec;     // 0x1C
    OSTime start; // 0x20
    s32 manual;   // 0x28
} SplineWork;

#if VERSION >= VERSION_JP
// coin_fmt is only used by a function the linker stripped; force_active keeps the string in .rodata
#pragma force_active on
static const char coin_fmt[] = "%f%f%f";
#pragma force_active reset
#endif

static const GXColor coin_black = {0x00, 0x00, 0x00, 0xFF};

static USER_FUNC(bgm_start_wait);
#if VERSION >= VERSION_US
USER_FUNC(evt_sub_scale_by_fps);
#endif
static USER_FUNC(get_stop);
static USER_FUNC(irai_mail_check);
static USER_FUNC(mail_evt_gor_04_keyoff_check);
static USER_FUNC(set_stop);
static USER_FUNC(stageclear_wait);
static USER_FUNC(stone_bg);
static USER_FUNC(stone_bg_open);
static USER_FUNC(stone_ry);
static void coingetDisp(WinMgrEntry* entry);

#if VERSION <= VERSION_DEMO_US
extern EvtWord evt_sub_starstone[1030];
#else
extern EvtWord evt_sub_starstone[VERSION_PICK(1043, 1084)];
#endif
extern EvtWord evt_sub_mail_vibration[26];
#if VERSION <= VERSION_JP
s32 evt_sub_mail_event_end[1];
#endif

// the demo keeps this file's data in definition order: stopwatch, the tree data and scripts, the grass data and
// scripts, then the coin window (retail puts the small objects in .sdata)
#if VERSION <= VERSION_DEMO_US
EVT_BEGIN(evt_sub_stopwatch)
    LOOP(0)
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()
#endif

s32 tree_data[] = {
    FLOAT(0.0f), FLOAT(0.0f), FLOAT(0.0f), FLOAT(-0.535f), FLOAT(1.447f), FLOAT(1.624f), FLOAT(-1.171f), FLOAT(3.175f),
    FLOAT(3.567f), FLOAT(-1.605f), FLOAT(4.339f), FLOAT(4.872f), FLOAT(-1.534f), FLOAT(4.091f), FLOAT(4.581f), FLOAT(-0.686f),
    FLOAT(1.747f), FLOAT(1.893f), FLOAT(0.716f), FLOAT(-2.068f), FLOAT(-2.483f), FLOAT(2.229f), FLOAT(-6.232f), FLOAT(-7.24f),
    FLOAT(3.412f), FLOAT(-9.6245f), FLOAT(-11.073f), FLOAT(3.823f), FLOAT(-11.1245f), FLOAT(-12.675f), FLOAT(3.102f), FLOAT(-9.989f),
    FLOAT(-11.147f), FLOAT(1.544f), FLOAT(-6.963f), FLOAT(-7.358f), FLOAT(-0.31f), FLOAT(-3.166f), FLOAT(-2.659f), FLOAT(-1.923f),
    FLOAT(0.289f), FLOAT(1.598f), FLOAT(-2.754f), FLOAT(2.28f), FLOAT(4.061f), FLOAT(-2.552f), FLOAT(2.416f), FLOAT(4.261f),
    FLOAT(-1.677f), FLOAT(1.44f), FLOAT(3.099f), FLOAT(-0.505f), FLOAT(-0.055f), FLOAT(1.279f), FLOAT(0.584f), FLOAT(-1.478f),
    FLOAT(-0.493f), FLOAT(1.215f), FLOAT(-2.236f), FLOAT(-1.51f), FLOAT(1.304f), FLOAT(-2.22f), FLOAT(-1.662f), FLOAT(1.102f),
    FLOAT(-1.828f), FLOAT(-1.4165f), FLOAT(0.735f), FLOAT(-1.218f), FLOAT(-0.944f), FLOAT(0.326f), FLOAT(-0.555f), FLOAT(-0.416f),
    FLOAT(0.0f), FLOAT(0.0f), FLOAT(0.0f),
};

#if VERSION >= VERSION_JP
EVT_BEGIN(evt_sub_stopwatch)
    LOOP(0)
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static s32 kusa_data[] = {
    FLOAT(0.0f), FLOAT(-1.874f), FLOAT(-2.999f), FLOAT(-2.22f), FLOAT(-0.776f), FLOAT(0.0f), FLOAT(-0.776f), FLOAT(-2.22f),
    FLOAT(-2.999f), FLOAT(-2.443f), FLOAT(-1.22f), FLOAT(0.0f),
};

WinMgrDesc coinget_window_desc[] = {
    {0, 0, 8, -175, 120, 350, 42, {0xE1, 0xD7, 0x9B, 0xFF}, NULL, coingetDisp},
};
#endif

#if VERSION >= VERSION_US
EVT_BEGIN(tree_evt)
    SET_TYPE(0)
    SET_VALUE(LF(0), 0)
    IF_INT_NOT_EQUAL(LW(3), 0)
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_NOT_EQUAL(LW(4), 0)
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_mapobj_get_position, LW(2), LW(13), LW(14), LW(15))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HIT_TREE1"), LW(13), LW(14), LW(15), 0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_HIT_TREE1_LEAVES1"), LW(13), LW(14), LW(15), 0)
        CALL(evt_mapobj_get_position, LW(2), LW(13), LW(14), LW(15))
        CALL(evt_mapobj_get_position, LW(3), LW(10), LW(11), LW(12))
        SET_VALUE(LW(14), LW(11))
        CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
        SET_VALUE(LW(15), LW(12))
        SUBTRACT(LW(14), 25)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 0, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(1)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 3, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(2)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 4, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(3)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 4, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(4)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 3, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(5)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 2, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(6)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 2, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
        END_SWITCH
    END_IF
    IF_INT_NOT_EQUAL(LW(5), 0)
        SPAWN_EVENT(LW(5))
    END_IF
    SET_INT_READ_ADDR(PTR(tree_data))
    LOOP(25)
        READ_INT3(LW(10), LW(11), LW(12))
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(evt_mapobj_rotate, 1, LW(2), FLOAT(0.0f), FLOAT(0.0f), LW(10))
        END_IF
        IF_INT_NOT_EQUAL(LW(3), 0)
            CALL(evt_mapobj_trans, 1, LW(3), LW(11), FLOAT(0.0f), FLOAT(0.0f))
        END_IF
        IF_INT_NOT_EQUAL(LW(4), 0)
            CALL(evt_mapobj_trans, 1, LW(4), LW(12), FLOAT(0.0f), FLOAT(0.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()
#elif VERSION <= VERSION_DEMO_US
EVT_BEGIN(tree_evt)
    SET_VALUE(LF(0), 0)
    IF_INT_NOT_EQUAL(LW(3), 0)
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_NOT_EQUAL(LW(4), 0)
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_mapobj_get_position, LW(2), LW(13), LW(14), LW(15))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HIT_TREE1"), LW(13), LW(14), LW(15), 0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_HIT_TREE1_LEAVES1"), LW(13), LW(14), LW(15), 0)
        CALL(evt_mapobj_get_position, LW(2), LW(13), LW(14), LW(15))
        CALL(evt_mapobj_get_position, LW(3), LW(10), LW(11), LW(12))
        SET_VALUE(LW(14), LW(11))
        CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
        SET_VALUE(LW(15), LW(12))
        SUBTRACT(LW(14), 25)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 0, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(1)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 3, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(2)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 4, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(3)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 4, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(4)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 3, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(5)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 2, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(6)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 2, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
        END_SWITCH
    END_IF
    IF_INT_NOT_EQUAL(LW(5), 0)
        SPAWN_EVENT(LW(5))
    END_IF
    SET_INT_READ_ADDR(PTR(tree_data))
    LOOP(25)
        READ_INT3(LW(10), LW(11), LW(12))
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(evt_mapobj_rotate, 1, LW(2), FLOAT(0.0f), FLOAT(0.0f), LW(10))
        END_IF
        IF_INT_NOT_EQUAL(LW(3), 0)
            CALL(evt_mapobj_trans, 1, LW(3), LW(11), FLOAT(0.0f), FLOAT(0.0f))
        END_IF
        IF_INT_NOT_EQUAL(LW(4), 0)
            CALL(evt_mapobj_trans, 1, LW(4), LW(12), FLOAT(0.0f), FLOAT(0.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()
#else
EVT_BEGIN(tree_evt)
    SET_TYPE(0)
    SET_VALUE(LF(0), 0)
    IF_INT_NOT_EQUAL(LW(3), 0)
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_NOT_EQUAL(LW(4), 0)
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_mapobj_get_position, LW(2), LW(13), LW(14), LW(15))
        CALL(evt_snd_sfxon_3d, STRING("SFX_HIT_TREE1"), LW(13), LW(14), LW(15), 0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_HIT_TREE1_LEAVES1"), LW(13), LW(14), LW(15), 0)
        CALL(evt_mapobj_get_position, LW(2), LW(13), LW(14), LW(15))
        CALL(evt_mapobj_get_position, LW(3), LW(10), LW(11), LW(12))
        SET_VALUE(LW(14), LW(11))
        CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
        SET_VALUE(LW(15), LW(12))
        SUBTRACT(LW(14), 25)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 0, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(1)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 3, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(2)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 4, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(3)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 4, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(4)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 3, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(5)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 2, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
            CASE_EQUAL(6)
            CALL(evt_eff64, 0, STRING("fall_leaf_n64"), 2, LW(13), LW(14), LW(15), 60, 0, 0, 0, 0, 0, 0, 0)
        END_SWITCH
    END_IF
    IF_INT_NOT_EQUAL(LW(5), 0)
        SPAWN_EVENT(LW(5))
    END_IF
    SET_INT_READ_ADDR(PTR(tree_data))
    LOOP(25)
        READ_INT3(LW(10), LW(11), LW(12))
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(evt_mapobj_rotate, 1, LW(2), FLOAT(0.0f), FLOAT(0.0f), LW(10))
        END_IF
        IF_INT_NOT_EQUAL(LW(3), 0)
            CALL(evt_mapobj_trans, 1, LW(3), LW(11), FLOAT(0.0f), FLOAT(0.0f))
        END_IF
        IF_INT_NOT_EQUAL(LW(4), 0)
            CALL(evt_mapobj_trans, 1, LW(4), LW(12), FLOAT(0.0f), FLOAT(0.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()
#endif

EVT_BEGIN(evt_sub_tree_access_entry)
    SET_INT_READ_ADDR(LW(0))
    LOOP(0)
        READ_INT3(LW(0), LW(1), LW(2))
        READ_INT3(LW(3), LW(4), LW(5))
        IF_INT_EQUAL(LW(0), 7)
            BREAK_LOOP
        END_IF
        CALL(evt_run_case_evt, CASE_COND_HAMMER, 1, LW(1), 0, PTR(tree_evt), 0)
    END_LOOP
    RETURN
EVT_END()

#if VERSION <= VERSION_DEMO_US
static s32 kusa_data[] = {
    FLOAT(0.0f), FLOAT(-1.874f), FLOAT(-2.999f), FLOAT(-2.22f), FLOAT(-0.776f), FLOAT(0.0f), FLOAT(-0.776f), FLOAT(-2.22f),
    FLOAT(-2.999f), FLOAT(-2.443f), FLOAT(-1.22f), FLOAT(0.0f),
};
#endif

#if VERSION >= VERSION_US
EVT_BEGIN(kusa_evt)
    SET_TYPE(0)
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_GRASS_SHAKE1"), LW(10), LW(11), LW(12), 0)
    IF_INT_NOT_EQUAL(LW(3), 0)
        SPAWN_EVENT(LW(3))
    END_IF
    SET_INT_READ_ADDR(PTR(kusa_data))
    LOOP(12)
        READ_INT(LW(10))
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(evt_mapobj_trans, 1, LW(2), LW(10), FLOAT(0.0f), FLOAT(0.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()
#elif VERSION <= VERSION_DEMO_US
EVT_BEGIN(kusa_evt)
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_GRASS_SHAKE1"), LW(10), LW(11), LW(12), 0)
    IF_INT_NOT_EQUAL(LW(3), 0)
        SPAWN_EVENT(LW(3))
    END_IF
    SET_INT_READ_ADDR(PTR(kusa_data))
    LOOP(12)
        READ_INT(LW(10))
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(evt_mapobj_trans, 1, LW(2), LW(10), FLOAT(0.0f), FLOAT(0.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()
#else
EVT_BEGIN(kusa_evt)
    SET_TYPE(0)
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_GRASS_SHAKE1"), LW(10), LW(11), LW(12), 0)
    IF_INT_NOT_EQUAL(LW(3), 0)
        SPAWN_EVENT(LW(3))
    END_IF
    SET_INT_READ_ADDR(PTR(kusa_data))
    LOOP(12)
        READ_INT(LW(10))
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(evt_mapobj_trans, 1, LW(2), LW(10), FLOAT(0.0f), FLOAT(0.0f))
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()
#endif

EVT_BEGIN(evt_sub_kusa_access_entry)
    SET_INT_READ_ADDR(LW(0))
    LOOP(0)
        READ_INT3(LW(0), LW(1), LW(2))
        READ_INT(LW(3))
        IF_INT_EQUAL(LW(0), 4)
            BREAK_LOOP
        END_IF
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(1), 0, PTR(kusa_evt), 0)
    END_LOOP
    RETURN
EVT_END()

#if VERSION <= VERSION_DEMO_US
WinMgrDesc coinget_window_desc[] = {
    {0, 0, 8, -175, 120, 350, 42, {0xE1, 0xD7, 0x9B, 0xFF}, NULL, coingetDisp},
};
#endif

#if VERSION >= VERSION_US
EVT_BEGIN(evt_sub_starstone)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_pouch_get_starstone, 1)
        CALL(evt_pouch_add_item, ITEM_DIAMOND_STAR, LW(2))
        CASE_EQUAL(2)
        CALL(evt_pouch_get_starstone, 2)
        CALL(evt_pouch_add_item, ITEM_EMERALD_STAR, LW(2))
        CASE_EQUAL(3)
        CALL(evt_pouch_get_starstone, 3)
        CALL(evt_pouch_add_item, ITEM_GOLD_STAR, LW(2))
        CASE_EQUAL(4)
        CALL(evt_pouch_get_starstone, 4)
        CALL(evt_pouch_add_item, ITEM_RUBY_STAR, LW(2))
        CASE_EQUAL(5)
        CALL(evt_pouch_get_starstone, 5)
        CALL(evt_pouch_add_item, ITEM_SAPPHIRE_STAR, LW(2))
        CASE_EQUAL(6)
        CALL(evt_pouch_get_starstone, 6)
        CALL(evt_pouch_add_item, ITEM_GARNET_STAR, LW(2))
        CASE_EQUAL(7)
        CALL(evt_pouch_get_starstone, 7)
        CALL(evt_pouch_add_item, ITEM_CRYSTAL_STAR, LW(2))
        CASE_EQUAL(-1)
    END_SWITCH
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LF(1), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 2)
        SET_VALUE(LF(2), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 3)
        SET_VALUE(LF(3), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 4)
        SET_VALUE(LF(4), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 5)
        SET_VALUE(LF(5), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 6)
        SET_VALUE(LF(6), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 7)
        SET_VALUE(LF(7), 1)
    END_IF
    IF_INT_EQUAL(LW(0), -1)
        SET_VALUE(LF(8), 1)
    END_IF
    CALL(set_stop, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(9700)
        CALL(set_stop, 1)
    END_INLINE_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_EVT_STARSTONE_WHITEOUT1"), 0)
    CALL(evt_fade_entry, FADE_OUT_BLACK, 300, 255, 255, 255)
    CALL(evt_fade_end_wait)
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_npc_get_position, STRING("にせマリオ"), LW(2), LW(3), LW(4))
    ELSE
        CALL(evt_mario_get_pos, 0, LW(2), LW(3), LW(4))
    END_IF
    CALL(evt_sub_get_sincos, 0, LW(5), LW(6))
    MULTIPLY_FLOAT(LW(5), FLOAT(40.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(40.0f))
    ADD_FLOAT(LW(5), LW(2))
    ADD_FLOAT(LW(6), LW(4))
    CALL(evt_item_set_position, LW(1), LW(5), LW(3), LW(6))
    CALL(evt_mario_adjust_dir)
    WAIT_MS(500)
    IF_INT_EQUAL(LF(8), 0)
        CALL(evt_mario_set_pose, STRING("M_N_3"))
    END_IF
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_GET_STARSTONE1"))
    CALL(bgm_start_wait)
    CALL(evt_fade_entry, FADE_IN_BLACK, 300, 255, 255, 255)
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_cam3d_evt_set_npc_rel, STRING("にせマリオ"), 0, 50, 397, 0, 70, 25, 2000, 11)
    ELSE
        CALL(evt_cam3d_evt_set_rel, 0, 50, 397, 0, 70, 25, 2000, 11)
    END_IF
    CALL(evt_snd_sfxon_3d, STRING("SFX_SE2_EVT_STARSTONE_GET1"), LW(5), LW(3), LW(6), 0)
    SET_VALUE(LW(7), LW(1))
    SET_FLOAT_VALUE(LW(8), FLOAT(35.0f))
    SET_FLOAT_VALUE(LW(9), LW(3))
    CALL(evt_sub_intpl_msec_init, 4, 0, 3600, 2833)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        IF_INT_EQUAL(LF(8), 1)
            CALL(evt_npc_get_position, STRING("にせマリオ"), LW(2), LW(3), LW(4))
        ELSE
            CALL(evt_mario_get_pos, 0, LW(2), LW(3), LW(4))
        END_IF
        CALL(evt_sub_get_sincos, LW(0), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), LW(8))
        MULTIPLY_FLOAT(LW(6), LW(8))
        ADD_FLOAT(LW(5), LW(2))
        ADD_FLOAT(LW(6), LW(4))
        CALL(evt_item_set_position, LW(7), LW(5), LW(9), LW(6))
        CALL(stone_ry, LW(7), LW(0))
        SET_FLOAT_VALUE(LW(2), FLOAT(0.20507813f))
        SET_FLOAT_VALUE(LW(3), FLOAT(0.28222656f))
        CALL(evt_sub_scale_by_fps, LW(2), LW(3))
        SUBTRACT_FLOAT(LW(8), LW(2))
        ADD_FLOAT(LW(9), LW(3))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_npc_get_position, STRING("にせマリオ"), LW(2), LW(3), LW(4))
    ELSE
        CALL(evt_mario_get_pos, 0, LW(2), LW(3), LW(4))
    END_IF
    ADD(LW(3), 48)
    CALL(evt_item_set_position, LW(7), LW(2), LW(3), LW(4))
    IF_INT_NOT_EQUAL(LF(8), 1)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAPPY1"), LW(0), LW(1), LW(2), 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_npc_set_anim, STRING("にせマリオ"), STRING("EM_I_1"))
    ELSE
        CALL(evt_mario_set_pose, STRING("M_P_2"))
    END_IF
    CALL(evt_item_get_position, LW(7), LW(0), LW(1), LW(2))
    ADD(LW(1), 16)
    CALL(evt_eff64, STRING("sub_hikari"), STRING("radiation_n64"), 12, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    ADD(LW(2), -10)
    CALL(evt_eff, STRING("sub_bg"), STRING("itemget"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(stone_bg, LW(7))
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_msg_print, 0, STRING("stg1_gon_33_18"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_msg_print, 0, STRING("stg2_mri_e25_03"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        CALL(evt_msg_print, 0, STRING("stg3_tou_475"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_39"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        CALL(evt_msg_print, 0, STRING("stg5_dou_29_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        CALL(evt_msg_print, 0, STRING("stg6_pik_20"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        CALL(evt_msg_print, 0, STRING("stg7_aji_42_02"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_10_02"), 0, 0)
    END_IF
    LOOP(0)
        CALL(get_stop, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STAGE_CLEAR1"))
    CALL(evt_snd_envoff, PSND_FADE_OUT)
    CALL(evt_eff_softdelete, STRING("sub_hikari"))
    CALL(stone_bg_open, LW(7))
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LF(1), 1)
            SET_VALUE(LW(0), STRING("gon_11_S"))
        END_IF
        IF_INT_EQUAL(LF(2), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(3), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(4), 1)
            SET_VALUE(LW(0), STRING("S_jin04"))
        END_IF
        IF_INT_EQUAL(LF(5), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(6), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(7), 1)
            SET_VALUE(LW(0), STRING("S_aji_14"))
        END_IF
        IF_INT_EQUAL(LF(8), 1)
            SET_VALUE(LW(0), STRING("S_jin04"))
        END_IF
        WAIT_FRAMES(10)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_HIDE)
    END_INLINE_EVENT
    CALL(evt_fade_entry, FADE_CURTAIN_ENTER_3D, 0, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_eff, STRING("sub_clear"), STRING("stageclear"), 10, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(stageclear_wait)
    IF_INT_NOT_EQUAL(LF(8), 1)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAPPY2"), LW(0), LW(1), LW(2), 0)
    END_IF
    WAIT_MS(2000)
    CALL(evt_fade_entry, FADE_CURTAIN_CENTER_A2_3D, 0, 0, 0, 0)
    CALL(evt_fade_end_wait)
    CALL(evt_item_delete, LW(7))
    WAIT_MS(1000)
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_msg_print, 0, STRING("stg1_gon_34"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_msg_print, 0, STRING("stg2_mri_e25_04"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        CALL(evt_msg_print, 0, STRING("stg3_tou_475_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_39_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        CALL(evt_msg_print, 0, STRING("stg5_dou_29_02"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        CALL(evt_msg_print, 0, STRING("stg6_pik_20_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        CALL(evt_msg_print, 0, STRING("stg7_aji_42_03"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_10_03"), 0, 0)
    END_IF
    WAIT_MS(1000)
    IF_INT_EQUAL(LF(1), 1)
        SET_VALUE(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        SET_VALUE(LW(0), 4)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        SET_VALUE(LW(0), 7)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        SET_VALUE(LW(0), 10)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        SET_VALUE(LW(0), 13)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        SET_VALUE(LW(0), 16)
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        SET_VALUE(LW(0), 19)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        SET_VALUE(LW(0), 22)
    END_IF
    SET_VALUE(LF(10), 0)
    CALL_CHILD(evt_memcard_save_wrapper)
    CALL(evt_mario_init_camid)
    CALL(evt_party_init_camid, 0)
    CALL(evt_party_init_camid, 1)
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("aji_10"), 0)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("aji_10"), 0)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("aji_10"), 0)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        CALL(evt_fade_set_mapchange_type, 1, FADE_OUT_WHITE, 800, FADE_IN_WHITE, 800)
        CALL(evt_bero_mapchange, STRING("usu_00"), 0)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        CALL(evt_fade_set_mapchange_type, 1, FADE_OUT_WHITE, 800, FADE_IN_WHITE, 800)
        CALL(evt_bero_mapchange, STRING("muj_12"), 0)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        CALL(evt_fade_set_mapchange_type, 0, FADE_OUT_WHITE, 800, FADE_IN_WHITE, 800)
        CALL(evt_bero_mapchange, STRING("pik_03"), STRING("next"))
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("pik_01"), 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_eff_delete, STRING("sub_bg"))
        CALL(evt_eff_delete, STRING("sub_clear"))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_jin04"), MAPOBJ_FLAG_HIDE)
        CALL(evt_fade_reset, 1)
        CALL(evt_npc_set_camid, STRING("にせマリオ"), 4)
        CALL(evt_mario_set_pose, STRING("M_D_2"))
        CALL(evt_fade_entry, FADE_IN_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
#elif VERSION <= VERSION_DEMO_US
EVT_BEGIN(evt_sub_starstone)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_pouch_get_starstone, 1)
        CALL(evt_pouch_add_item, ITEM_DIAMOND_STAR, LW(2))
        CASE_EQUAL(2)
        CALL(evt_pouch_get_starstone, 2)
        CALL(evt_pouch_add_item, ITEM_EMERALD_STAR, LW(2))
        CASE_EQUAL(3)
        CALL(evt_pouch_get_starstone, 3)
        CALL(evt_pouch_add_item, ITEM_GOLD_STAR, LW(2))
        CASE_EQUAL(4)
        CALL(evt_pouch_get_starstone, 4)
        CALL(evt_pouch_add_item, ITEM_RUBY_STAR, LW(2))
        CASE_EQUAL(5)
        CALL(evt_pouch_get_starstone, 5)
        CALL(evt_pouch_add_item, ITEM_SAPPHIRE_STAR, LW(2))
        CASE_EQUAL(6)
        CALL(evt_pouch_get_starstone, 6)
        CALL(evt_pouch_add_item, ITEM_GARNET_STAR, LW(2))
        CASE_EQUAL(7)
        CALL(evt_pouch_get_starstone, 7)
        CALL(evt_pouch_add_item, ITEM_CRYSTAL_STAR, LW(2))
        CASE_EQUAL(-1)
    END_SWITCH
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LF(1), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 2)
        SET_VALUE(LF(2), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 3)
        SET_VALUE(LF(3), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 4)
        SET_VALUE(LF(4), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 5)
        SET_VALUE(LF(5), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 6)
        SET_VALUE(LF(6), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 7)
        SET_VALUE(LF(7), 1)
    END_IF
    IF_INT_EQUAL(LW(0), -1)
        SET_VALUE(LF(8), 1)
    END_IF
    CALL(set_stop, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(9700)
        CALL(set_stop, 1)
    END_INLINE_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_EVT_STARSTONE_WHITEOUT1"), 0)
    CALL(evt_fade_entry, FADE_OUT_BLACK, 300, 255, 255, 255)
    CALL(evt_fade_end_wait)
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_npc_get_position, STRING("にせマリオ"), LW(2), LW(3), LW(4))
    ELSE
        CALL(evt_mario_get_pos, 0, LW(2), LW(3), LW(4))
    END_IF
    CALL(evt_sub_get_sincos, 0, LW(5), LW(6))
    MULTIPLY_FLOAT(LW(5), FLOAT(40.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(40.0f))
    ADD_FLOAT(LW(5), LW(2))
    ADD_FLOAT(LW(6), LW(4))
    CALL(evt_item_set_position, LW(1), LW(5), LW(3), LW(6))
    CALL(evt_mario_adjust_dir)
    WAIT_MS(500)
    IF_INT_EQUAL(LF(8), 0)
        CALL(evt_mario_set_pose, STRING("M_N_3"))
    END_IF
    CALL(evt_fade_entry, FADE_IN_BLACK, 300, 255, 255, 255)
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_GET_STARSTONE1"))
    CALL(bgm_start_wait)
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_cam3d_evt_set_npc_rel, STRING("にせマリオ"), 0, 50, 397, 0, 70, 25, 2000, 11)
    ELSE
        CALL(evt_cam3d_evt_set_rel, 0, 50, 397, 0, 70, 25, 2000, 11)
    END_IF
    CALL(evt_snd_sfxon_3d, STRING("SFX_SE2_EVT_STARSTONE_GET1"), LW(5), LW(3), LW(6), 0)
    SET_VALUE(LW(7), LW(1))
    SET_FLOAT_VALUE(LW(8), FLOAT(35.0f))
    SET_FLOAT_VALUE(LW(9), LW(3))
    CALL(evt_sub_intpl_init, 4, 0, 3600, 170)
    LOOP(171)
        CALL(evt_sub_intpl_get_value)
        IF_INT_EQUAL(LF(8), 1)
            CALL(evt_npc_get_position, STRING("にせマリオ"), LW(2), LW(3), LW(4))
        ELSE
            CALL(evt_mario_get_pos, 0, LW(2), LW(3), LW(4))
        END_IF
        CALL(evt_sub_get_sincos, LW(0), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), LW(8))
        MULTIPLY_FLOAT(LW(6), LW(8))
        ADD_FLOAT(LW(5), LW(2))
        ADD_FLOAT(LW(6), LW(4))
        CALL(evt_item_set_position, LW(7), LW(5), LW(9), LW(6))
        CALL(stone_ry, LW(7), LW(0))
        SUBTRACT_FLOAT(LW(8), FLOAT(0.205078125f))
        ADD_FLOAT(LW(9), FLOAT(0.2822265625f))
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_NOT_EQUAL(LF(8), 1)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAPPY1"), LW(0), LW(1), LW(2), 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_npc_set_anim, STRING("にせマリオ"), STRING("EM_I_1"))
    ELSE
        CALL(evt_mario_set_pose, STRING("M_P_2"))
    END_IF
    CALL(evt_item_get_position, LW(7), LW(0), LW(1), LW(2))
    ADD(LW(1), 16)
    CALL(evt_eff64, STRING("sub_hikari"), STRING("radiation_n64"), 12, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    ADD(LW(2), -10)
    CALL(evt_eff, STRING("sub_bg"), STRING("itemget"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(stone_bg, LW(7))
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_msg_print, 0, STRING("stg1_gon_33_18"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_msg_print, 0, STRING("stg2_mri_e25_03"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        CALL(evt_msg_print, 0, STRING("stg3_tou_475"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_39"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        CALL(evt_msg_print, 0, STRING("stg5_dou_29_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        CALL(evt_msg_print, 0, STRING("stg6_pik_20"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        CALL(evt_msg_print, 0, STRING("stg7_aji_42_02"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_10_02"), 0, 0)
    END_IF
    LOOP(0)
        CALL(get_stop, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STAGE_CLEAR1"))
    CALL(evt_eff_softdelete, STRING("sub_hikari"))
    CALL(stone_bg_open, LW(7))
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LF(1), 1)
            SET_VALUE(LW(0), STRING("gon_11_S"))
        END_IF
        IF_INT_EQUAL(LF(2), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(3), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(4), 1)
            SET_VALUE(LW(0), STRING("S_jin04"))
        END_IF
        IF_INT_EQUAL(LF(5), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(6), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(7), 1)
            SET_VALUE(LW(0), STRING("S_aji_14"))
        END_IF
        IF_INT_EQUAL(LF(8), 1)
            SET_VALUE(LW(0), STRING("S_jin04"))
        END_IF
        WAIT_FRAMES(10)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_HIDE)
    END_INLINE_EVENT
    CALL(evt_fade_entry, FADE_CURTAIN_ENTER_3D, 0, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_eff, STRING("sub_clear"), STRING("stageclear"), 10, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(stageclear_wait)
    IF_INT_NOT_EQUAL(LF(8), 1)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAPPY2"), LW(0), LW(1), LW(2), 0)
    END_IF
    WAIT_MS(2000)
    CALL(evt_fade_entry, FADE_CURTAIN_CENTER_A2_3D, 0, 0, 0, 0)
    CALL(evt_fade_end_wait)
    CALL(evt_item_delete, LW(7))
    WAIT_MS(1000)
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_msg_print, 0, STRING("stg1_gon_34"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_msg_print, 0, STRING("stg2_mri_e25_04"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        CALL(evt_msg_print, 0, STRING("stg3_tou_475_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_39_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        CALL(evt_msg_print, 0, STRING("stg5_dou_29_02"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        CALL(evt_msg_print, 0, STRING("stg6_pik_20_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        CALL(evt_msg_print, 0, STRING("stg7_aji_42_03"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_10_03"), 0, 0)
    END_IF
    WAIT_MS(1000)
    IF_INT_EQUAL(LF(1), 1)
        SET_VALUE(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        SET_VALUE(LW(0), 4)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        SET_VALUE(LW(0), 7)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        SET_VALUE(LW(0), 10)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        SET_VALUE(LW(0), 13)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        SET_VALUE(LW(0), 16)
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        SET_VALUE(LW(0), 19)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        SET_VALUE(LW(0), 22)
    END_IF
    SET_VALUE(LF(10), 0)
    CALL_CHILD(evt_memcard_save)
    CALL(evt_mario_init_camid)
    CALL(evt_party_init_camid, 0)
    CALL(evt_party_init_camid, 1)
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("aji_10"), 0)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("aji_10"), 0)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("aji_10"), 0)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        CALL(evt_fade_set_mapchange_type, 1, FADE_OUT_WHITE, 800, FADE_IN_WHITE, 800)
        CALL(evt_bero_mapchange, STRING("usu_00"), 0)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        CALL(evt_fade_set_mapchange_type, 1, FADE_OUT_WHITE, 800, FADE_IN_WHITE, 800)
        CALL(evt_bero_mapchange, STRING("muj_12"), 0)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        CALL(evt_fade_set_mapchange_type, 0, FADE_OUT_WHITE, 800, FADE_IN_WHITE, 800)
        CALL(evt_bero_mapchange, STRING("pik_03"), STRING("next"))
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("pik_01"), 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_eff_delete, STRING("sub_bg"))
        CALL(evt_eff_delete, STRING("sub_clear"))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_jin04"), MAPOBJ_FLAG_HIDE)
        CALL(evt_fade_reset, 1)
        CALL(evt_npc_set_camid, STRING("にせマリオ"), 4)
        CALL(evt_mario_set_pose, STRING("M_D_2"))
        CALL(evt_fade_entry, FADE_IN_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
#else
EVT_BEGIN(evt_sub_starstone)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    SWITCH(LW(0))
        CASE_EQUAL(1)
        CALL(evt_pouch_get_starstone, 1)
        CALL(evt_pouch_add_item, ITEM_DIAMOND_STAR, LW(2))
        CASE_EQUAL(2)
        CALL(evt_pouch_get_starstone, 2)
        CALL(evt_pouch_add_item, ITEM_EMERALD_STAR, LW(2))
        CASE_EQUAL(3)
        CALL(evt_pouch_get_starstone, 3)
        CALL(evt_pouch_add_item, ITEM_GOLD_STAR, LW(2))
        CASE_EQUAL(4)
        CALL(evt_pouch_get_starstone, 4)
        CALL(evt_pouch_add_item, ITEM_RUBY_STAR, LW(2))
        CASE_EQUAL(5)
        CALL(evt_pouch_get_starstone, 5)
        CALL(evt_pouch_add_item, ITEM_SAPPHIRE_STAR, LW(2))
        CASE_EQUAL(6)
        CALL(evt_pouch_get_starstone, 6)
        CALL(evt_pouch_add_item, ITEM_GARNET_STAR, LW(2))
        CASE_EQUAL(7)
        CALL(evt_pouch_get_starstone, 7)
        CALL(evt_pouch_add_item, ITEM_CRYSTAL_STAR, LW(2))
        CASE_EQUAL(-1)
    END_SWITCH
    IF_INT_EQUAL(LW(0), 1)
        SET_VALUE(LF(1), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 2)
        SET_VALUE(LF(2), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 3)
        SET_VALUE(LF(3), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 4)
        SET_VALUE(LF(4), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 5)
        SET_VALUE(LF(5), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 6)
        SET_VALUE(LF(6), 1)
    END_IF
    IF_INT_EQUAL(LW(0), 7)
        SET_VALUE(LF(7), 1)
    END_IF
    IF_INT_EQUAL(LW(0), -1)
        SET_VALUE(LF(8), 1)
    END_IF
    CALL(set_stop, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(9700)
        CALL(set_stop, 1)
    END_INLINE_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_EVT_STARSTONE_WHITEOUT1"), 0)
    CALL(evt_fade_entry, FADE_OUT_BLACK, 300, 255, 255, 255)
    CALL(evt_fade_end_wait)
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_npc_get_position, STRING("にせマリオ"), LW(2), LW(3), LW(4))
    ELSE
        CALL(evt_mario_get_pos, 0, LW(2), LW(3), LW(4))
    END_IF
    CALL(evt_sub_get_sincos, 0, LW(5), LW(6))
    MULTIPLY_FLOAT(LW(5), FLOAT(40.0f))
    MULTIPLY_FLOAT(LW(6), FLOAT(40.0f))
    ADD_FLOAT(LW(5), LW(2))
    ADD_FLOAT(LW(6), LW(4))
    CALL(evt_item_set_position, LW(1), LW(5), LW(3), LW(6))
    CALL(evt_mario_adjust_dir)
    WAIT_MS(500)
    IF_INT_EQUAL(LF(8), 0)
        CALL(evt_mario_set_pose, STRING("M_N_3"))
    END_IF
    CALL(evt_fade_entry, FADE_IN_BLACK, 300, 255, 255, 255)
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_GET_STARSTONE1"))
    CALL(bgm_start_wait)
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_cam3d_evt_set_npc_rel, STRING("にせマリオ"), 0, 50, 397, 0, 70, 25, 2000, 11)
    ELSE
        CALL(evt_cam3d_evt_set_rel, 0, 50, 397, 0, 70, 25, 2000, 11)
    END_IF
    CALL(evt_snd_sfxon_3d, STRING("SFX_SE2_EVT_STARSTONE_GET1"), LW(5), LW(3), LW(6), 0)
    SET_VALUE(LW(7), LW(1))
    SET_FLOAT_VALUE(LW(8), FLOAT(35.0f))
    SET_FLOAT_VALUE(LW(9), LW(3))
    CALL(evt_sub_intpl_init, 4, 0, 3600, 170)
    LOOP(171)
        CALL(evt_sub_intpl_get_value)
        IF_INT_EQUAL(LF(8), 1)
            CALL(evt_npc_get_position, STRING("にせマリオ"), LW(2), LW(3), LW(4))
        ELSE
            CALL(evt_mario_get_pos, 0, LW(2), LW(3), LW(4))
        END_IF
        CALL(evt_sub_get_sincos, LW(0), LW(5), LW(6))
        MULTIPLY_FLOAT(LW(5), LW(8))
        MULTIPLY_FLOAT(LW(6), LW(8))
        ADD_FLOAT(LW(5), LW(2))
        ADD_FLOAT(LW(6), LW(4))
        CALL(evt_item_set_position, LW(7), LW(5), LW(9), LW(6))
        CALL(stone_ry, LW(7), LW(0))
        SUBTRACT_FLOAT(LW(8), FLOAT(0.20507813f))
        ADD_FLOAT(LW(9), FLOAT(0.28222656f))
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_NOT_EQUAL(LF(8), 1)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAPPY1"), LW(0), LW(1), LW(2), 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_npc_set_anim, STRING("にせマリオ"), STRING("EM_I_1"))
    ELSE
        CALL(evt_mario_set_pose, STRING("M_P_2"))
    END_IF
    CALL(evt_item_get_position, LW(7), LW(0), LW(1), LW(2))
    ADD(LW(1), 16)
    CALL(evt_eff64, STRING("sub_hikari"), STRING("radiation_n64"), 12, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    ADD(LW(2), -10)
    CALL(evt_eff, STRING("sub_bg"), STRING("itemget"), 0, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(stone_bg, LW(7))
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_msg_print, 0, STRING("stg1_gon_33_18"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_msg_print, 0, STRING("stg2_mri_e25_03"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        CALL(evt_msg_print, 0, STRING("stg3_tou_475"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_39"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        CALL(evt_msg_print, 0, STRING("stg5_dou_29_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        CALL(evt_msg_print, 0, STRING("stg6_pik_20"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        CALL(evt_msg_print, 0, STRING("stg7_aji_42_02"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_10_02"), 0, 0)
    END_IF
    LOOP(0)
        CALL(get_stop, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STAGE_CLEAR1"))
    CALL(evt_snd_envoff, PSND_FADE_OUT)
    CALL(evt_eff_softdelete, STRING("sub_hikari"))
    CALL(stone_bg_open, LW(7))
    BEGIN_INLINE_EVENT
        IF_INT_EQUAL(LF(1), 1)
            SET_VALUE(LW(0), STRING("gon_11_S"))
        END_IF
        IF_INT_EQUAL(LF(2), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(3), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(4), 1)
            SET_VALUE(LW(0), STRING("S_jin04"))
        END_IF
        IF_INT_EQUAL(LF(5), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(6), 1)
            SET_VALUE(LW(0), STRING("S"))
        END_IF
        IF_INT_EQUAL(LF(7), 1)
            SET_VALUE(LW(0), STRING("S_aji_14"))
        END_IF
        IF_INT_EQUAL(LF(8), 1)
            SET_VALUE(LW(0), STRING("S_jin04"))
        END_IF
        WAIT_FRAMES(10)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_HIDE)
    END_INLINE_EVENT
    CALL(evt_fade_entry, FADE_CURTAIN_ENTER_3D, 0, 0, 0, 0)
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    CALL(evt_eff, STRING("sub_clear"), STRING("stageclear"), 10, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(stageclear_wait)
    IF_INT_NOT_EQUAL(LF(8), 1)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_HAPPY2"), LW(0), LW(1), LW(2), 0)
    END_IF
    WAIT_MS(2000)
    CALL(evt_fade_entry, FADE_CURTAIN_CENTER_A2_3D, 0, 0, 0, 0)
    CALL(evt_fade_end_wait)
    CALL(evt_item_delete, LW(7))
    WAIT_MS(1000)
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_msg_print, 0, STRING("stg1_gon_34"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_msg_print, 0, STRING("stg2_mri_e25_04"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        CALL(evt_msg_print, 0, STRING("stg3_tou_475_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_39_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        CALL(evt_msg_print, 0, STRING("stg5_dou_29_02"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        CALL(evt_msg_print, 0, STRING("stg6_pik_20_01"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        CALL(evt_msg_print, 0, STRING("stg7_aji_42_03"), 0, 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_msg_print, 0, STRING("stg4_jin_10_03"), 0, 0)
    END_IF
    WAIT_MS(1000)
    IF_INT_EQUAL(LF(1), 1)
        SET_VALUE(LW(0), 1)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        SET_VALUE(LW(0), 4)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        SET_VALUE(LW(0), 7)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        SET_VALUE(LW(0), 10)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        SET_VALUE(LW(0), 13)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        SET_VALUE(LW(0), 16)
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        SET_VALUE(LW(0), 19)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        SET_VALUE(LW(0), 22)
    END_IF
    SET_VALUE(LF(10), 0)
    CALL_CHILD(evt_memcard_save)
    CALL(evt_mario_init_camid)
    CALL(evt_party_init_camid, 0)
    CALL(evt_party_init_camid, 1)
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("aji_10"), 0)
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("aji_10"), 0)
    END_IF
    IF_INT_EQUAL(LF(3), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("aji_10"), 0)
    END_IF
    IF_INT_EQUAL(LF(4), 1)
        CALL(evt_fade_set_mapchange_type, 1, FADE_OUT_WHITE, 800, FADE_IN_WHITE, 800)
        CALL(evt_bero_mapchange, STRING("usu_00"), 0)
    END_IF
    IF_INT_EQUAL(LF(5), 1)
        CALL(evt_fade_set_mapchange_type, 1, FADE_OUT_WHITE, 800, FADE_IN_WHITE, 800)
        CALL(evt_bero_mapchange, STRING("muj_12"), 0)
    END_IF
    IF_INT_EQUAL(LF(6), 1)
        CALL(evt_fade_set_mapchange_type, 0, FADE_OUT_WHITE, 800, FADE_IN_WHITE, 800)
        CALL(evt_bero_mapchange, STRING("pik_03"), STRING("next"))
    END_IF
    IF_INT_EQUAL(LF(7), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_fade_set_mapchange_type, 1, FADE_STORY_MARIO_A1, 0, FADE_STORY_MARIO_A3, 0)
        CALL(evt_bero_mapchange, STRING("pik_01"), 0)
    END_IF
    IF_INT_EQUAL(LF(8), 1)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_envoff_f, PSND_FADE_OUT, 2000)
        CALL(evt_snd_sfx_all_stop)
        CALL(evt_fade_entry, FADE_OUT_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
        WAIT_MS(2000)
        CALL(evt_eff_delete, STRING("sub_bg"))
        CALL(evt_eff_delete, STRING("sub_clear"))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_jin04"), MAPOBJ_FLAG_HIDE)
        CALL(evt_fade_reset, 1)
        CALL(evt_npc_set_camid, STRING("にせマリオ"), 4)
        CALL(evt_mario_set_pose, STRING("M_D_2"))
        CALL(evt_fade_entry, FADE_IN_WHITE, 1000, 0, 0, 0)
        CALL(evt_fade_end_wait)
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
#endif

EVT_BEGIN(evt_sub_mail_vibration)
    LOOP(10)
        LOOP(10)
            CALL(evt_sub_rumble_onoff, 0, 0)
            WAIT_MS(50)
            CALL(evt_sub_rumble_onoff, 1, 0)
            WAIT_MS(50)
        END_LOOP
        CALL(evt_sub_rumble_onoff, 2, 0)
        WAIT_MS(2000)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mail_evt)
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_party_yoshi_ride, 0, 0)
    CALL(evt_mario_wait_rideon)
    CALL(evt_mario_balloon_bikkuri)
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_MAIL_RECEPTION3"))
    SPAWN_EVENT_GET_ID(PTR(evt_sub_mail_vibration), LW(10))
    WAIT_MS(500)
    CALL(evt_win_one_message, 0)
    DELETE_EVENT(LW(10))
    WAIT_FRAMES(1)
    CALL(evt_sub_rumble_onoff, 1, 0)
    CALL(evt_mario_balloon_off)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_TUTORIAL_SEEN), 0)
        SET_VALUE(GSWF(GSWF_MAIL_TUTORIAL_SEEN), 1)
        CALL(evt_msg_print, 0, STRING("mail_first_hit"), 0, 0)
    ELSE
        IF_INT_EQUAL(GSWF(GSWF_MAIL_OPENED_ONCE), 0)
            CALL(evt_msg_print, 0, STRING("mail_first_hit"), 0, 0)
        END_IF
    END_IF
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_nok_01)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_FRANKLY_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), 190, -2000, 190, 2000, LW(5))
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG1_02_TALKING_WITH_KROOP)
            IF_INT_EQUAL(LW(5), 1)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_FRANKLY_SENT), 1)
    CALL(evt_pouch_receive_mail, 16)
    CALL(evt_pouch_receive_mail, 26)
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_gor_03)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), -100, -2000, -100, 2000, LW(5))
        IF_INT_EQUAL(LW(5), 1)
            SET_VALUE(LF(0), 0)
            IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG2_47_AFTER_GETTING_THE_TICKET)
                IF_INT_EQUAL(GSWF(GSWF_MAIL_KOOPLEY_SENT), 0)
                    SET_VALUE(GSWF(GSWF_MAIL_KOOPLEY_SENT), 1)
                    CALL(evt_pouch_receive_mail, 17)
                    SET_VALUE(LF(0), 1)
                END_IF
            END_IF
            CALL(irai_mail_check, 0, LW(5))
            IF_INT_EQUAL(LW(5), 1)
                CALL(irai_mail_check, 1, LW(5))
                SET_VALUE(LF(0), 1)
            END_IF
            IF_INT_EQUAL(LF(0), 1)
                CALL_CHILD(mail_evt)
                SET_VALUE(LF(0), 0)
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_gor_02)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), -280, -50, -230, 220, LW(5))
        IF_INT_EQUAL(LW(5), 1)
            SET_VALUE(LF(0), 0)
            IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_51_FRANKLYS_HOUSE)
                IF_INT_EQUAL(GSWF(GSWF_MAIL_KOOPIE_KOO_SENT), 0)
                    SET_VALUE(GSWF(GSWF_MAIL_KOOPIE_KOO_SENT), 1)
                    CALL(evt_pouch_receive_mail, 18)
                    SET_VALUE(LF(0), 1)
                END_IF
            END_IF
            CALL(irai_mail_check, 0, LW(5))
            IF_INT_EQUAL(LW(5), 1)
                CALL(irai_mail_check, 1, LW(5))
                SET_VALUE(LF(0), 1)
            END_IF
            IF_INT_EQUAL(LF(0), 1)
                CALL_CHILD(mail_evt)
                SET_VALUE(LF(0), 0)
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_gor_01)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_PETUNI_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), 350, -2000, 350, 2000, LW(5))
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG4_37_TO_THE_PORT)
            IF_INT_EQUAL(LW(5), 1)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_PETUNI_SENT), 1)
    CALL(evt_pouch_receive_mail, 19)
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_gor_04)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), 30, -2000, 30, 2000, LW(5))
        CALL(mail_evt_gor_04_keyoff_check, LW(3))
        IF_INT_GREATER(LW(3), 0)
            SET_VALUE(LW(5), 0)
        END_IF
        IF_INT_EQUAL(LW(5), 1)
            SET_VALUE(LF(0), 0)
            IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_66_BELDAM_FINDS_OUT)
                IF_INT_EQUAL(GSWF(GSWF_MAIL_BOO_SENT), 0)
                    SET_VALUE(GSWF(GSWF_MAIL_BOO_SENT), 1)
                    CALL(evt_pouch_receive_mail, 20)
                    SET_VALUE(LF(0), 1)
                END_IF
            END_IF
            CALL(irai_mail_check, 0, LW(5))
            IF_INT_EQUAL(LW(5), 1)
                CALL(irai_mail_check, 1, LW(5))
                SET_VALUE(LF(0), 1)
            END_IF
            IF_INT_EQUAL(LF(0), 1)
                CALL_CHILD(mail_evt)
                SET_VALUE(LF(0), 0)
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_rsh_03_a)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_PA_PATCH_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#if VERSION >= VERSION_US
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), -100, -2000, -100, 2000, LW(5))
#else
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), 400, -2000, 400, 2000, LW(5))
#endif
        IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_45_DAY_3_STARTS)
            IF_INT_EQUAL(LW(5), 1)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_PA_PATCH_SENT), 1)
    CALL(evt_pouch_receive_mail, 21)
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_hom_00)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_KING_K_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), -600, -2000, -600, 2000, LW(5))
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_42_DRAWBRIDGE_DOWN)
            IF_INT_EQUAL(LW(5), 1)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_KING_K_SENT), 1)
    CALL(evt_pouch_receive_mail, 22)
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_gor_02_2)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_ZIP_TOAD_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), -1000, -4226, 1000, 7374, LW(5))
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_71_FRANKLYS_HOUSE)
            IF_INT_EQUAL(LW(5), 1)
#if VERSION == VERSION_EU
                CALL(evt_mario_get_motion, LW(5))
                IF_INT_NOT_EQUAL(LW(5), 25)
                    BREAK_LOOP
                END_IF
#else
                BREAK_LOOP
#endif
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_ZIP_TOAD_SENT), 1)
    CALL(evt_pouch_receive_mail, 23)
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_bom_01)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_RAWK_HAWK_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), -230, -2000, -230, 2000, LW(5))
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG7_02_MAYOR_BOB)
            IF_INT_EQUAL(GSWF(GSWF_PIK00_GOLDBOB_CANNON_APPROVAL), 1)
                IF_INT_EQUAL(LW(5), 1)
                    BREAK_LOOP
                END_IF
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_RAWK_HAWK_SENT), 1)
    CALL(evt_pouch_receive_mail, 24)
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_tik_00)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_GHOST_T_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), 470, -2000, 470, 2000, LW(5))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), -500, -2000, -500, 2000, LW(6))
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG7_50_A_WAITING_PROF_FRANKLY)
            IF_INT_EQUAL(LW(5), 1)
                BREAK_LOOP
            END_IF
            IF_INT_EQUAL(LW(6), 1)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_GHOST_T_SENT), 1)
    CALL(evt_pouch_receive_mail, 25)
    CALL(evt_pouch_receive_mail, 33)
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_win_01)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_RDM_ISSUE1_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), 390, -2000, 390, 2000, LW(5))
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG2_09_FLURRIE_JOINS)
            IF_INT_EQUAL(LW(5), 1)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_RDM_ISSUE1_SENT), 1)
    CALL(evt_pouch_receive_mail, 27)
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_tou_01)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_RDM_ISSUE2_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), -50, -2000, -50, 2000, LW(5))
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_12_MINI_YOSHI_EGG)
            IF_INT_EQUAL(LW(5), 1)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_RDM_ISSUE2_SENT), 1)
    CALL(evt_pouch_receive_mail, 28)
    SET_VALUE(GSWF(GSWF_MRI07_DOUBLE_POINTS_SALE), 1)
    CALL(evt_sub_save_playtime, GSW(GSW_MRI07_DOUBLE_POINTS_TIME))
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_usu_01)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_RDM_ISSUE3_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
#if VERSION <= VERSION_DEMO_US
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), 300, -2000, 300, 2000, LW(5))
#else
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), 110, -2000, 110, 2000, LW(5))
#endif
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG4_04_01_PAPER_MAGE_TUBE_MOD)
            IF_INT_EQUAL(LW(5), 1)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_RDM_ISSUE3_SENT), 1)
    CALL(evt_pouch_receive_mail, 29)
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_gor_01_2)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), -2000, 200, 2000, 200, LW(5))
        IF_INT_EQUAL(LW(5), 1)
            SET_VALUE(LF(0), 0)
            IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG5_59_01_A_MAIL_FROM_PEACH)
                IF_INT_EQUAL(GSWF(GSWF_MAIL_RDM_ISSUE4_SENT), 0)
                    SET_VALUE(GSWF(GSWF_MAIL_RDM_ISSUE4_SENT), 1)
                    CALL(evt_pouch_receive_mail, 30)
                    SET_VALUE(GSWF(GSWF_USU01_DOUBLE_POINTS_SALE), 1)
                    CALL(evt_sub_save_playtime, GSW(GSW_USU01_DOUBLE_POINTS_TIME))
                    SET_VALUE(LF(0), 1)
                END_IF
            END_IF
            CALL(irai_mail_check, 0, LW(5))
            IF_INT_EQUAL(LW(5), 1)
                CALL(irai_mail_check, 1, LW(5))
                SET_VALUE(LF(0), 1)
            END_IF
            IF_INT_EQUAL(LF(0), 1)
                CALL_CHILD(mail_evt)
                SET_VALUE(LF(0), 0)
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_rsh_03_a_2)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_RDM_ISSUE5_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), 400, -2000, 400, 2000, LW(5))
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_21_DAY_2)
            IF_INT_EQUAL(LW(5), 1)
                BREAK_LOOP
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_RDM_ISSUE5_SENT), 1)
    CALL(evt_pouch_receive_mail, 31)
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

EVT_BEGIN(mail_evt_pik_00)
    IF_INT_EQUAL(GSWF(GSWF_MAIL_RDM_ISSUE6_SENT), 1)
        RETURN
    END_IF
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        SET_VALUE(LW(11), LW(1))
        SET_VALUE(LW(12), LW(2))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_sub_check_intersect, LW(0), LW(2), LW(10), LW(12), -60, -2000, -60, 2000, LW(5))
        IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG7_02_MAYOR_BOB)
            IF_INT_EQUAL(GSWF(GSWF_PIK00_GOLDBOB_CANNON_APPROVAL), 1)
                IF_INT_EQUAL(LW(5), 1)
                    BREAK_LOOP
                END_IF
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(GSWF(GSWF_MAIL_RDM_ISSUE6_SENT), 1)
    CALL(evt_pouch_receive_mail, 32)
    SET_VALUE(GSWF(GSWF_RSH03_DOUBLE_POINTS_SALE), 1)
    CALL(evt_sub_save_playtime, GSW(GSW_RSH03_DOUBLE_POINTS_TIME))
    CALL_CHILD(mail_evt)
    RETURN
EVT_END()

// Written out instead of EVT_BEGIN/EVT_END: JP and the demos end it without the end opcode (evt_sub_mail_event_end
// below follows it in .data)
EvtWord evt_sub_mail_event[] = {
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), GLOBAL_FLAG_KIOSK)
        RETURN
    END_IF
    CALL(evt_mario_get_mode, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("nok_01"))
        CALL_CHILD(mail_evt_nok_01)
        RETURN
    END_IF
    IF_STR_EQUAL(LW(0), STRING("gor_03"))
        CALL_CHILD(mail_evt_gor_03)
        RETURN
    END_IF
    IF_STR_EQUAL(LW(0), STRING("gor_02"))
        SPAWN_EVENT(mail_evt_gor_02)
        CALL_CHILD(mail_evt_gor_02_2)
        RETURN
    END_IF
    IF_STR_EQUAL(LW(0), STRING("gor_01"))
        SPAWN_EVENT(mail_evt_gor_01_2)
        CALL_CHILD(mail_evt_gor_01)
        RETURN
    END_IF
    IF_STR_EQUAL(LW(0), STRING("gor_04"))
        CALL_CHILD(mail_evt_gor_04)
        RETURN
    END_IF
#if VERSION >= VERSION_US
    IF_STR_EQUAL(LW(0), STRING("rsh_02_a"))
        CALL_CHILD(mail_evt_rsh_03_a)
        RETURN
    END_IF
#endif
    IF_STR_EQUAL(LW(0), STRING("rsh_03_a"))
        CALL_CHILD(mail_evt_rsh_03_a_2)
#if VERSION <= VERSION_JP
        CALL_CHILD(mail_evt_rsh_03_a)
#endif
        RETURN
    END_IF
    IF_STR_EQUAL(LW(0), STRING("hom_00"))
        CALL_CHILD(mail_evt_hom_00)
        RETURN
    END_IF
    IF_STR_EQUAL(LW(0), STRING("bom_01"))
        CALL_CHILD(mail_evt_bom_01)
        RETURN
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tik_00"))
        CALL_CHILD(mail_evt_tik_00)
        RETURN
    END_IF
    IF_STR_EQUAL(LW(0), STRING("win_01"))
        CALL_CHILD(mail_evt_win_01)
        RETURN
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_01"))
        CALL_CHILD(mail_evt_tou_01)
        RETURN
    END_IF
    IF_STR_EQUAL(LW(0), STRING("usu_01"))
        CALL_CHILD(mail_evt_usu_01)
        RETURN
    END_IF
    IF_STR_EQUAL(LW(0), STRING("pik_00"))
        CALL_CHILD(mail_evt_pik_00)
        RETURN
    END_IF
    RETURN
#if VERSION >= VERSION_US
    OPCODE_END_SCRIPT
#endif
};

// Nothing left in the code reads evt_sub_mail_event_end; force_active keeps it in the link
#pragma force_active on
#if VERSION <= VERSION_JP
__declspec(section ".data") s32 evt_sub_mail_event_end[] = {
    1,
};
#endif
#pragma force_active reset

USER_FUNC(evt_sub_intpl_init) {
    EvtWord* args = event->args;
    s32 mode = evtGetValue(event, args[0]);
    s32 start = evtGetValue(event, args[1]);
    s32 end = evtGetValue(event, args[2]);
    s32 steps = evtGetValue(event, args[3]);
    event->lwData[11] = mode;
    event->lwData[12] = start;
    event->lwData[13] = end;
    event->lwData[14] = 0;
    event->lwData[15] = steps;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_intpl_get_value) {
    event->lwData[0] = intplGetValue(event->lwData[11], event->lwData[12], event->lwData[13], event->lwData[14], event->lwData[15]);
    if (event->lwData[14] >= event->lwData[15]) {
        event->lwData[1] = 0;
    } else {
        event->lwData[1] = 1;
    }
    event->lwData[14]++;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_intpl_get_value_para) {
    EvtWord* args = event->args;
    evtSetFloat(event, args[0], intplGetValue(event->lwData[11], event->lwData[12], event->lwData[13], event->lwData[14], event->lwData[15]));
    if (event->lwData[14] >= event->lwData[15]) {
        evtSetValue(event, args[1], 0);
    } else {
        evtSetValue(event, args[1], 1);
    }
    event->lwData[14]++;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_intpl_init_float) {
    EvtWord* args = event->args;
    s32 mode = evtGetValue(event, args[0]);
    f32 start = evtGetFloat(event, args[1]);
    f32 end = evtGetFloat(event, args[2]);
    s32 steps = evtGetValue(event, args[3]);
    event->lwData[11] = mode;
    event->lwData[12] = FLOAT(start);
    event->lwData[13] = FLOAT(end);
    event->lwData[14] = 0;
    event->lwData[15] = steps;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_intpl_get_float) {
    EvtWord* args = event->args;
    s32 out = args[0];
    s32 done = args[1];
    f32 start = evtGetFloat(event, LW(12));
    f32 end = evtGetFloat(event, LW(13));
    f32 v = intplGetValue(event->lwData[11], start, end, event->lwData[14], event->lwData[15]);
    if (out != EVT_NULLPTR) {
        evtSetFloat(event, out, v);
    }
    if (done != EVT_NULLPTR) {
        if (event->lwData[14] >= event->lwData[15]) {
            evtSetValue(event, done, 0);
        } else {
            evtSetValue(event, done, 1);
        }
    }
    event->lwData[14]++;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_intpl_msec_init) {
    EvtWord* args = event->args;
    s32 mode = evtGetValue(event, args[0]);
    s32 start = evtGetValue(event, args[1]);
    s32 end = evtGetValue(event, args[2]);
    s32 msec = evtGetValue(event, args[3]);
    event->lwData[11] = mode;
    event->lwData[12] = start;
    event->lwData[13] = end;
    event->lwData[15] = msec;
    event->savedTime = event->lifetime;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_intpl_msec_get_value) {
    s32 ms = (u64)(s32)((s32)event->lifetime - (s32)event->savedTime) / (OS_TIMER_CLOCK / 1000);
    if (ms < event->lwData[15]) {
        event->lwData[0] = intplGetValue(event->lwData[11], event->lwData[12], event->lwData[13], ms, event->lwData[15]);
        event->lwData[1] = 1;
    } else {
        event->lwData[0] = event->lwData[13];
        event->lwData[1] = 0;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_intpl_msec_get_value_para) {
    EvtWord* args = event->args;
    s32 ms = (u64)(s32)((s32)event->lifetime - (s32)event->savedTime) / (OS_TIMER_CLOCK / 1000);
    if (ms < event->lwData[15]) {
        evtSetFloat(event, args[0], intplGetValue(event->lwData[11], event->lwData[12], event->lwData[13], ms, event->lwData[15]));
        evtSetValue(event, args[1], 1);
    } else {
        evtSetFloat(event, args[0], event->lwData[13]);
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_spline_init) {
    EvtWord* args = event->args;
    s32 manual = evtGetValue(event, args[0]);
    s32 mode = evtGetValue(event, args[1]);
    Vec* pts = (Vec*)evtGetValue(event, args[2]);
    s32 n = evtGetValue(event, args[3]);
    s32 steps = evtGetValue(event, args[4]);
    s32 msec = evtGetValue(event, args[5]);
    SplineWork* w = _mapAlloc(sizeof(SplineWork));
    event->lwData[15] = (EvtWord)w;
    w->n = n;
    w->ts = _mapAlloc(n * 4);
    w->pts = pts;
    w->tbl = _mapAlloc(n * 12);
    spline_maketable(n, w->pts, w->ts, w->tbl);
    w->manual = manual;
    w->mode = mode;
    w->cur = 0;
    w->steps = steps;
    w->msec = msec;
    w->start = event->lifetime;
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_spline_get_value) {
    EvtWord* args = event->args;
    SplineWork* w = (SplineWork*)event->lwData[15];
    f32 el;
    f32 v[3];
    f32 t;
    if (!w->manual) {
        t = intplGetValue(w->mode, 0.0f, 1.0f, w->cur, w->steps);
    } else {
        el = (u64)(event->lifetime - w->start) / (OS_TIMER_CLOCK / 1000);
        t = intplGetValue(w->mode, 0.0f, 1.0f, (s32)el, w->msec);
    }
    ((Spline_getvalueLocalFn)spline_getvalue)(v, t, w->n, w->pts, w->ts, w->tbl);
    evtSetValue(event, args[0], FLOAT(v[0]));
    evtSetValue(event, args[1], FLOAT(v[1]));
    evtSetValue(event, args[2], FLOAT(v[2]));
    w->cur++;
    if (!w->manual) {
        if (w->cur <= w->steps) {
            evtSetValue(event, args[3], 1);
            return EVT_RETURN_DONE;
        }
    } else if (el <= (f32)w->msec) {
        evtSetValue(event, args[3], 1);
        return EVT_RETURN_DONE;
    }
    _mapFree(w->ts);
    _mapFree(w->tbl);
    _mapFree(w);
    evtSetValue(event, args[3], 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_spline_get_value_manual) {
    EvtWord* args = event->args;
    SplineWork* w = (SplineWork*)event->lwData[15];
    f32 t = evtGetValue(event, args[0]);
    f32 v[3];
    t = t; // FAKE: self-assignment gives t a second definition, which keeps the target's float register order
    t = t / (w->manual ? (f32)w->msec : (f32)w->steps);
    ((Spline_getvalueLocalFn)spline_getvalue)(v, t, w->n, w->pts, w->ts, w->tbl);
    evtSetValue(event, args[1], FLOAT(v[0]));
    evtSetValue(event, args[2], FLOAT(v[1]));
    evtSetValue(event, args[3], FLOAT(v[2]));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_spline_free) {
    SplineWork* w = (SplineWork*)event->lwData[15];
    _mapFree(w->ts);
    _mapFree(w->tbl);
    _mapFree(w);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_get_sincos) {
    EvtWord* args = event->args;
    f32 rad = (3.141592f * evtGetFloat(event, args[0])) / 180.0f;
    f32 s = (f32)sin(rad);
    evtSetValue(event, args[1], FLOAT(s));
    s = (f32)cos(rad);
    evtSetValue(event, args[2], FLOAT(s));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_rumble_onoff) {
    EvtWord* args = event->args;
    s32 mode = evtGetValue(event, args[0]);
    s32 chan = evtGetValue(event, args[1]);
    switch (mode) {
        case 0:
            padRumbleOn(chan);
            break;
        case 1:
            padRumbleOff(chan);
            break;
        case 2:
            padRumbleHardOff(chan);
            break;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_random) {
    EvtWord* args = event->args;
    s32 n = evtGetValue(event, args[0]);
    evtSetValue(event, args[1], rand() % (n + 1));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_get_stopwatch) {
    EvtWord* args = event->args;
    s64* sw = (s64*)evtGetPtrID(evtGetValue(event, args[0]));
    s32 ms = *sw / (OS_TIMER_CLOCK / 1000);
    if (ms > 600000) {
        ms = 600000;
    }
    evtSetValue(event, args[1], ms);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_area_check) {
    EvtWord* args = event->args;
    s32 mode = evtGetValue(event, args[0]);
    f32 a1 = evtGetValue(event, args[1]);
    f32 a2 = evtGetValue(event, args[2]);
    f32 a3 = evtGetValue(event, args[3]);
    f32 a4 = evtGetValue(event, args[4]);
    f32 a5 = evtGetValue(event, args[5]);
    s32 result;
    switch (mode) {
        case 0: {
            f32 dist = distABf(a1, a2, a4, a5);
            if (a3 < dist) {
                result = 0;
            } else {
                result = 1;
            }
            break;
        }
        case 1:
            result = 1;
            if (a1 - a3 > a4) {
                result = 0;
            }
            if (a1 + a3 < a4) {
                result = 0;
            }
            if (a2 - a3 > a5) {
                result = 0;
            }
            if (a2 + a3 < a5) {
                result = 0;
            }
            break;
        default:
            result = 0;
            break;
    }
    evtSetValue(event, args[6], result);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_get_dist) {
    EvtWord* args = event->args;
    f32 x1 = evtGetValue(event, args[0]);
    f32 y1 = evtGetValue(event, args[1]);
    f32 x2 = evtGetValue(event, args[2]);
    f32 y2 = evtGetValue(event, args[3]);
    evtSetFloat(event, args[4], distABf(x1, y1, x2, y2));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_get_dir) {
    EvtWord* args = event->args;
    f32 x1 = evtGetValue(event, args[0]);
    f32 y1 = evtGetValue(event, args[1]);
    f32 x2 = evtGetValue(event, args[2]);
    f32 y2 = evtGetValue(event, args[3]);
    evtSetFloat(event, args[4], angleABf(x1, y1, x2, y2));
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_get_system_flag) {
    evtSetValue(event, event->args[0], gp->flags);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_system_flag_onoff) {
    EvtWord* args = event->args;
    s32 onoff = evtGetValue(event, args[0]);
    s32 flag = args[1];
    if (onoff) {
        gp->flags |= flag;
    } else {
        gp->flags &= ~flag;
    }
    return EVT_RETURN_DONE;
}

KEYFN(evt_key_get_dir, keyGetDir)

KEYFN(evt_key_get_button, keyGetButton)

KEYFN(evt_key_get_buttontrg, keyGetButtonTrg)

USER_FUNC(evt_sub_get_mapname) {
    evtSetValue(event, event->args[0], (EvtWord)gp->currentMapName);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_get_areaname) {
    evtSetValue(event, event->args[0], (EvtWord)gp->currentAreaName);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_status_gauge_force_open) {
    statusWinForceOpen();
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_status_gauge_force_close) {
    statusWinForceClose();
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_status_gauge_check_update) {
    EvtWord* args = event->args;
    if (statusWinCheckUpdate()) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_US
USER_FUNC(N_evt_sub_status_gauge_force_update) {
    statusWinForceUpdate();
    return EVT_RETURN_DONE;
}
#endif

USER_FUNC(evt_sub_save_playtime) {
    s32 base = event->args[0];
    u8 buf[8];
    *(s64*)buf = gp->retraceLocalTime;
    swByteSet(base + 0xA21FE80, buf[0]);
    swByteSet(base + 0xA21FE81, buf[1]);
    swByteSet(base + 0xA21FE82, buf[2]);
    swByteSet(base + 0xA21FE83, buf[3]);
    swByteSet(base + 0xA21FE84, buf[4]);
    swByteSet(base + 0xA21FE85, buf[5]);
    swByteSet(base + 0xA21FE86, buf[6]);
    swByteSet(base + 0xA21FE87, buf[7]);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_load_progresstime) {
    EvtWord* args = event->args;
    s32 base = args[0];
    u8 buf[8];
    s64 ms;
    buf[0] = swByteGet(base + 0xA21FE80);
    buf[1] = swByteGet(base + 0xA21FE81);
    buf[2] = swByteGet(base + 0xA21FE82);
    buf[3] = swByteGet(base + 0xA21FE83);
    buf[4] = swByteGet(base + 0xA21FE84);
    buf[5] = swByteGet(base + 0xA21FE85);
    buf[6] = swByteGet(base + 0xA21FE86);
    buf[7] = swByteGet(base + 0xA21FE87);
    ms = (gp->retraceLocalTime - *(s64*)buf) / (OS_TIMER_CLOCK / 1000);
    if (ms > 86400000) {
        ms = 86400000;
    }
    evtSetValue(event, args[1], ms);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_get_language) {
    evtSetValue(event, event->args[0], gp->language);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_animgroup_async) {
    const char* group = (const char*)evtGetValue(event, event->args[0]);
    s32 r = animGroupBaseAsync(group, gp->inBattle != 0, NULL);
    if (r == 0) {
        return EVT_RETURN_BLOCK;
    }
    if (r != 0) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_DONE;
}

#if VERSION == VERSION_EU
USER_FUNC(evt_sub_get_framerate) {
    evtSetValue(event, event->args[0], gp->framerate);
    return EVT_RETURN_DONE;
}

#endif
USER_FUNC(evt_sub_countdown_start) {
    EvtWord* args = event->args;
    s32 limit = evtGetValue(event, args[0]);
    s32 restart = evtGetValue(event, args[1]);
    countDownStart(limit, restart);
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_countdown_get_status) {
    EvtWord* args = event->args;
    evtSetValue(event, args[0], countDownGetStatus());
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_countdown_end) {
    countDownEnd();
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_countdown_flag_onoff) {
    EvtWord* args = event->args;
    s32 onoff = evtGetValue(event, args[0]);
    s32 flag = evtGetValue(event, args[1]);
    if (onoff) {
        countDownFlagOn(flag);
    } else {
        countDownFlagOff(flag);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_sub_countdown_set_restart_time) {
    countDownSetRestartTime(evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

static void coingetDisp(WinMgrEntry* entry) {
    s32* work = entry->param;
    char buf[0x400];
    if (work[1]) {
#if VERSION >= VERSION_US
        u16 lines;
        s32 w;

        if ((u32)gp->language == 0) {
            sprintf(buf, msgSearch("msg_window_coin_get"), work[0]);
        } else {
            strcpy(buf, msgSearch("msg_window_coin_get"));
            evtMsgFmtInt(buf, work[0]);
        }
        w = FontGetMessageWidthLine(buf, &lines) + 20;
        if (w > entry->width) {
            entry->width = w;
            entry->x = -entry->width / 2;
        }
        entry->height = entry->description->height + lines * 24;
#else
        sprintf(buf, msgSearch("msg_window_coin_get"), work[0]);
#endif
        FontDrawStart();
        FontDrawColor(coin_black);
        FontDrawMessage(-(s32)FontGetMessageWidth(buf) / 2, entry->y - 8, buf);
    }
}

static inline f32 coin_sin(f32 x) {
    f32 a = 0.00761f;
    f32 b = 0.16605f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * x;
        } else {
            y = 1.5707964f - (x - 1.5707964f);
            x2 = y * y;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * y;
        }
    } else if (x < 4.712389f) {
        y = x - 3.1415927f;
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * y;
        a = -a;
    } else {
        y = 1.5707964f - (x - 4.712389f);
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * y;
        a = -a;
    }
    return a;
}
static inline f32 coin_cos(f32 x) {
    f32 a = 0.03705f;
    f32 b = 0.4967f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
        } else {
            y = 1.5707964f - (x - 1.5707964f);
            x2 = y * y;
            a = a * x2 - b;
            a = a * x2 + c;
            a = -a;
        }
    } else if (x < 4.712389f) {
        y = x - 3.1415927f;
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = -a;
    } else {
        y = 1.5707964f - (x - 4.712389f);
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
    }
    return a;
}
// FAKE: turns off copy propagation so the temporaries and registers match the target; removing it changes the code
#pragma opt_propagation off
#pragma opt_lifetimes off
USER_FUNC(evt_sub_get_coin) {
    s32 coin = evtGetValue(event, event->args[0]);
    MarioWork* mario = marioGetPtr();
    Vec a = mario->position;
    Vec b = a;
#if VERSION <= VERSION_DEMO_US
    Vec scr;
#endif
    f32 rad = reviseAngle((100.0f * camGetPtr(CAMERA_3D)->viewYaw + 5.0f) / 100.0f);
    f32 s;
    f32 c;
    s32 state;
    EffectEntry* eff;
    s32* work;
    rad = 6.2831855f * rad / 360.0f;
    s = 10.0f * coin_sin(rad);
    c = 10.0f * coin_cos(rad);
    a.x += s;
    a.z -= c;
    a.y += 62.0f;
    b.x += s;
    b.y += 52.0f;
    b.z -= c;
    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdatap[1] = effItemGetEntry(7, a.x, a.y, a.z);
        event->userdata[2] = 0;
        event->userdata3 = 0;
        event->wInterpWork = _mapAlloc(8);
    }
    state = event->userdata[0];
    eff = event->userdatap[1];
    work = event->wInterpWork;
    switch (state) {
        case 0:
#if VERSION <= VERSION_DEMO_US
            // the demo draws the coin icon in 2D at Mario's screen position
            iconEntry2D("iraiCoin", ICON_18B);
            getScreenPoint(&b, &scr);
            iconSetPos("iraiCoin", scr.x, scr.y, scr.z);
            iconFlagOn("iraiCoin", 2);
#else
            iconEntry("iraiCoin", ICON_18B);
            iconSetPos("iraiCoin", b.x, b.y, b.z);
            iconFlagOn("iraiCoin", 0x102);
            ((ItemGetWork*)eff->userdata)->camera = 5;
#endif
            marioChgGetItemMotion();
            event->userdata3 = winMgrEntry(coinget_window_desc);
            winMgrOpen(event->userdata3);
            winMgrSetParam(event->userdata3, work);
            work[0] = coin;
            work[1] = 0;
            psndBGMOff(PSND_FADE_DIP_TO(40));
            psndBGMOn(PSND_FADE_OUT | PSND_CH(1), "BGM_FF_GET_ITEM1");
            event->userdata[2] = 200;
            event->savedTime = gp->renderTime;
            event->userdata[0] = 1;
            return EVT_RETURN_BLOCK;
        case 1:
            if ((s32)(((u32)gp->renderTime - (u32)event->savedTime) / (OS_TIMER_CLOCK / 1000)) > event->userdata[2]) {
                iconFlagOff("iraiCoin", 2);
                work[1] = 1;
                event->userdata[2] = 500;
                event->savedTime = gp->renderTime;
                event->userdata[0] = 2;
            }
            return EVT_RETURN_BLOCK;
        case 2:
            if ((s32)(((u32)gp->renderTime - (u32)event->savedTime) / (OS_TIMER_CLOCK / 1000)) > event->userdata[2]) {
                event->userdata[0] = 10;
            }
            return EVT_RETURN_BLOCK;
        case 10:
            if (keyGetButtonTrg(0) & PAD_BUTTON_A) {
                event->userdata[0] = 100;
            }
            return EVT_RETURN_BLOCK;
        case 100:
            pouchAddCoin(coin);
            effSoftDelete(eff);
            iconDelete("iraiCoin");
            marioChgStayMotion();
            psndBGMOn(PSND_FADE_RESUME | PSND_FADE_UNDIP, NULL);
            psndBGMOff(PSND_FADE_OUT | PSND_CH(1));
            winMgrCloseAutoDelete(event->userdata3);
            work[1] = 0;
            event->userdata[0] = 101;
            return EVT_RETURN_DONE;
        case 101:
            if (!winMgrAction(event->userdata3)) {
                _mapFree(work);
                return EVT_RETURN_DONE;
            }
            return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

static USER_FUNC(stone_ry) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    s32 ang = evtGetValue(event, args[1]);
    EffectEntry* item = itemNameToPtr(name)->effect;
    ((EffStarStoneWork*)item->userdata)->flags &= ~4;
    ((EffStarStoneWork*)item->userdata)->rotY = ang % 360;
    return EVT_RETURN_DONE;
}

static USER_FUNC(stone_bg) {
    char* name;
    CameraEntry* cam;
    EffectEntry* eff;
    u8* item;
    name = (char*)evtGetValue(event, event->args[0]);
    cam = camGetPtr(CAMERA_2D);
    cam->letterBoxCamId = 5;
    eff = effNameToPtr("sub_bg");
    ((ItemGetWork*)eff->userdata)->camera = 5;
    item = (u8*)itemNameToPtr(name);
    ((EffStarStoneWork*)((ItemEntry*)item)->effect->userdata)->cam = 5;
    if (npcNameToPtr_NoAssert("\x82\xC9\x82\xB9\x83\x7D\x83\x8A\x83\x49") != NULL && evtGetValue(event, GSW(GSW_STORY_PROGRESS)) < STORY_STG4_15_DOOPLISS_BATTLE_2) {
        npcNameToPtr_NoAssert("\x82\xC9\x82\xB9\x83\x7D\x83\x8A\x83\x49")->cameraId = 5;
    } else {
        marioSetCamId(5);
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(stone_bg_open) {
    EffectEntry* e = effNameToPtr("sub_bg");
    ((ItemGetWork*)e->userdata)->state = 1;
    return EVT_RETURN_DONE;
}

static USER_FUNC(stageclear_wait) {
    return effStageClearEndChk(effNameToPtr("sub_clear")) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

static USER_FUNC(set_stop) {
    stop = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(get_stop) {
    evtSetValue(event, event->args[0], stop);
    return EVT_RETURN_DONE;
}

static USER_FUNC(bgm_start_wait) {
    return psndBGMStartCheck(1) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

#if VERSION >= VERSION_US
USER_FUNC(evt_sub_scale_by_fps) {
    EvtWord* args = event->args;
    s32 a0 = args[0];
    f32 x = evtGetFloat(event, a0);
    s32 a1 = args[1];
    f32 y = evtGetFloat(event, a1);
    x *= 60.0f / gp->framerate;
    y *= 60.0f / gp->framerate;
    evtSetFloat(event, a0, x);
    evtSetFloat(event, a1, y);
    return EVT_RETURN_DONE;
}
#endif

USER_FUNC(evt_sub_check_intersect) {
    EvtWord* args = event->args;
    f32 a, b, c, d, e, f, g, h;
    f32 t1, t2;
    a = evtGetFloat(event, args[0]);
    b = evtGetFloat(event, args[1]);
    c = evtGetFloat(event, args[2]);
    d = evtGetFloat(event, args[3]);
    e = evtGetFloat(event, args[4]);
    f = evtGetFloat(event, args[5]);
    g = evtGetFloat(event, args[6]);
    h = evtGetFloat(event, args[7]);
    if (a >= c) {
        if ((a < e && a < g) || (c > e && c > g)) {
            evtSetValue(event, args[8], 0);
            return EVT_RETURN_DONE;
        }
    } else {
        if ((c < e && c < g) || (a > e && a > g)) {
            evtSetValue(event, args[8], 0);
            return EVT_RETURN_DONE;
        }
    }
    if (b >= d) {
        if ((b < f && b < h) || (d > f && d > h)) {
            evtSetValue(event, args[8], 0);
            return EVT_RETURN_DONE;
        }
    } else {
        if ((d < f && d < h) || (b > f && b > h)) {
            evtSetValue(event, args[8], 0);
            return EVT_RETURN_DONE;
        }
    }
    t1 = (a - c) * (f - b) + (b - d) * (a - e);
    t2 = (a - c) * (h - b) + (b - d) * (a - g);
    if (t1 * t2 > 0.0f) {
        evtSetValue(event, args[8], 0);
        return EVT_RETURN_DONE;
    }
    t1 = (e - g) * (b - f) + (f - h) * (e - a);
    t2 = (e - g) * (d - f) + (f - h) * (e - c);
    if (t1 * t2 > 0.0f) {
        evtSetValue(event, args[8], 0);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[8], 1);
    return EVT_RETURN_DONE;
}

#define IRAI_CHECK(flag, done, base, mail)                         \
    if (swGet(flag) && !swGet(done)) {                             \
        for (i = 0; i < 8; i++) {                                  \
            u.b[i] = swByteGet(base + i);                          \
        }                                                          \
        if (OSTicksToSeconds(gp->retraceLocalTime - u.t) > 7200) { \
            ret = 1;                                               \
            if (arg) {                                             \
                swSet(done);                                       \
                pouchReceiveMail(mail);                            \
            }                                                      \
        }                                                          \
    }
static USER_FUNC(irai_mail_check) {
    EvtWord* args = event->args;
    s32 arg = evtGetValue(event, args[0]);
    s32 ret = 0;
    s32 i;
    union {
        u8 b[8];
        OSTime t;
    } u;
    IRAI_CHECK(0x1505, 0x17, 0x58d, 0x25)
    IRAI_CHECK(0x150a, 0x18, 0x595, 0x26)
    IRAI_CHECK(0x150b, 0x19, 0x59d, 0x27)
    IRAI_CHECK(0x150d, 0x1a, 0x5a5, 0x28)
    IRAI_CHECK(0x1512, 0x1b, 0x5ad, 0x29)
    IRAI_CHECK(0x1518, 0x1c, 0x5b5, 0x2a)
    evtSetValue(event, args[1], ret);
    return EVT_RETURN_DONE;
}

static USER_FUNC(mail_evt_gor_04_keyoff_check) {
    EvtWord* args = event->args;
    s32 a = marioCtrlOffChk();
    s32 b = marioKeyOffChk();
    evtSetValue(event, args[0], b + a);
    return EVT_RETURN_DONE;
}
