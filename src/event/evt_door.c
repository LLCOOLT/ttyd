// Scripts and commands for house doors: opening, walking in and out, inside/outside map groups
// and NPC visibility.
#include "data_tables.h"
#include "evt/evt_door.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "driver/animdrv.h"
#include "driver/hitdrv.h"
#include "driver/icondrv.h"
#include "driver/itemdrv.h"
#include "driver/mapdrv.h"
#include "driver/mobjdrv.h"
#include "driver/npcdrv.h"
#include "mario/mario.h"
#include "party.h"
#include "memory.h"
#include "pmario_sound.h"
#include <dolphin/mtx.h>
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_hit.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_party.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "version.h"
#include "driver/casedrv.h"
#include "libc_decls.h"

static USER_FUNC(snd_door_in);
static USER_FUNC(snd_door_out);

typedef struct HouseData {
    s32 type;            // 0x0
    const char* hit[4];  // 0x4, hit object names
    s32 anim[4];         // 0x14
    s32 outside;         // 0x24
    s32 door;            // 0x28
    s32 inside[2];       // 0x2C
    s32 initInside[2];   // 0x34
    const char** npcs;   // 0x3C
    const char** noclip; // 0x40
    const char** mobjs;  // 0x44
    const char** items;  // 0x48
} HouseData;

typedef struct HouseWork {
    HouseData* data; // 0x0
    Vec in;          // 0x4
    Vec out;         // 0x10
} HouseWork;

s32 DoorFLAG;
s32 door_mapflag;

void door_dark_flag_sub(BOOL on, const char** npcs, const char** mobjs, const char** items);

static USER_FUNC(animation);
static USER_FUNC(door_group);
static USER_FUNC(get_noclip_map);
static USER_FUNC(in_pos);
static USER_FUNC(init_inside_group);
static USER_FUNC(inout_hit);
static USER_FUNC(inside_group);
static USER_FUNC(npc_dark);
static USER_FUNC(npc_hide_onoff);
static USER_FUNC(npc_light);
static USER_FUNC(out_pos);
static USER_FUNC(outside_group);

extern EvtWord door_down_se[];
extern EvtWord house_open_se[];
extern EvtWord evt_dark[];
extern EvtWord evt_dark2[];
extern EvtWord evt_light2[];
extern EvtWord in_houseanim[];
extern EvtWord out_houseanim[];
extern EvtWord in_dooranim[];
extern EvtWord out_dooranim[];
extern EvtWord house_in[];
extern EvtWord house_out[];
extern EvtWord door_dark2[];

/**
 * Plays the door-open sound for a DoorParam (LW(0)) at its map object's position;
 * the sound comes from DoorParam.se (1 plain, 2-4 wood, 5-6 iron, 7 grille, 8 sliding, 9 turning, 10 electric,
 * 11 stone, 12-13 castle, 14 metal); 0 stays silent.
 */
EVT_BEGIN(door_open_se)
    CALL(evt_door_param, LW(0), 8, LW(1))
    CALL(evt_door_param, LW(0), 1, LW(2), LW(3), LW(4))
    CALL(evt_hit_get_position, LW(3), LW(10), LW(11), LW(12))
    SWITCH(LW(1))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(2)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_WOOD1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(3)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_WOOD2"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(4)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_WOOD3"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(5)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_IRON1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(6)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_IRON2"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(7)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_GRILLE1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(8)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_SLIDE1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(9)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_TURN1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(10)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_ELEC1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(11)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_STONE1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(12)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_CASTLE1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(13)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_CASTLE2"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(14)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN_METAL1"), LW(10), LW(11), LW(12), 0)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Plays the door-shut sound matching DoorParam.se at the door's map object;
 * same table as door_open_se, except se 4 reuses the second wood sound.
 */
EVT_BEGIN(door_close_se)
    CALL(evt_door_param, LW(0), 8, LW(1))
    CALL(evt_door_param, LW(0), 1, LW(2), LW(3), LW(4))
    CALL(evt_hit_get_position, LW(3), LW(10), LW(11), LW(12))
    SWITCH(LW(1))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(2)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_WOOD1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(3)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_WOOD2"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(4)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_WOOD2"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(5)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_IRON1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(6)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_IRON2"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(7)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_GRILLE1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(8)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_SLIDE1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(9)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_TURN1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(10)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_ELEC1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(11)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_STONE1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(12)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_CASTLE1"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(13)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_CASTLE2"), LW(10), LW(11), LW(12), 0)
        CASE_EQUAL(14)
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT_METAL1"), LW(10), LW(11), LW(12), 0)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Plays SFX_DOOR_FALL1 at the door's map object for any nonzero DoorParam.se;
 * spawned by evt_door_open when the door has a wall event (evtWall).
 */
EVT_BEGIN(door_down_se)
    CALL(evt_door_param, LW(0), 8, LW(1))
    CALL(evt_door_param, LW(0), 1, LW(2), LW(3), LW(4))
    CALL(evt_hit_get_position, LW(3), LW(10), LW(11), LW(12))
    SWITCH(LW(1))
        CASE_EQUAL(0)
        CASE_DEFAULT
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_FALL1"), LW(10), LW(11), LW(12), 0)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Plays SFX_HOUSE_OPEN1 at the door's map object when the house front swings open,
 * unless DoorParam.flags bit 2 asks for no sound.
 */
EVT_BEGIN(house_open_se)
    CALL(evt_door_param, LW(0), 9, LW(1))
    IF_BITS_SET(LW(1), 2)
        RETURN
    END_IF
    CALL(evt_door_param, LW(0), 1, LW(2), LW(3), LW(4))
    CALL(evt_hit_get_position, LW(3), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_OPEN1"), LW(10), LW(11), LW(12), 0)
    RETURN
EVT_END()

/**
 * Sets PSND_FLAG_MUTE_DOOR_SFX once Mario is inside,
 * silencing door-muted sounds until he leaves (snd_door_out) or the map changes.
 * The demo defines this pair at the end of the file.
 */
#if VERSION >= VERSION_JP
static USER_FUNC(snd_door_in) {
    psndSetFlag(PSND_FLAG_MUTE_DOOR_SFX);
    return EVT_RETURN_DONE;
}

/** Clears PSND_FLAG_MUTE_DOOR_SFX after Mario walks back out, letting door-muted sounds play again. */
static USER_FUNC(snd_door_out) {
    psndClearFlag(PSND_FLAG_MUTE_DOOR_SFX);
    return EVT_RETURN_DONE;
}
#endif

/**
 * Sets up a house for evt_door_setup: allocates a HouseWork on the map heap for the HouseData in args[0],
 * works out where Mario stands outside (from hit[1]) and inside (from hit[3]),
 * and returns the HouseWork in args[1].
 */
static USER_FUNC(door_entry) {
    EvtWord* args = event->args;
    HouseData* d = (HouseData*)evtGetValue(event, args[0]);
    Vec pos = {0.0f, 0.0f, 0.0f};
    Vec nrm = {0.0f, 0.0f, 0.0f};
    HouseWork* w = _mapAlloc(sizeof(HouseWork));

    w->data = d;
    switch (d->type) {
        case 0:
        case 1:
            hitObjGetPos(d->hit[1], &pos);
            hitObjGetNormal(d->hit[1], &nrm);
            w->out.x = pos.x + 40.0f * nrm.x - 10.0f * nrm.z;
            w->out.z = pos.z + 40.0f * nrm.z + 10.0f * nrm.x;
            hitObjGetPos(d->hit[3], &pos);
            hitObjGetNormal(d->hit[3], &nrm);
            w->in.x = pos.x + 30.0f * nrm.x;
            w->in.z = pos.z + 30.0f * nrm.z;
            break;
        case 2:
            hitObjGetPos(d->hit[1], &pos);
            hitObjGetNormal(d->hit[1], &nrm);
            w->out.x = pos.x + 40.0f * nrm.x + 10.0f * nrm.z;
            w->out.z = pos.z + 40.0f * nrm.z - 10.0f * nrm.x;
            hitObjGetPos(d->hit[3], &pos);
            hitObjGetNormal(d->hit[3], &nrm);
            w->in.x = pos.x + 30.0f * nrm.x;
            w->in.z = pos.z + 30.0f * nrm.z;
            break;
        case 3:
            hitObjGetPos(d->hit[1], &pos);
            hitObjGetNormal(d->hit[1], &nrm);
            w->out.x = pos.x + 40.0f * nrm.x;
            w->out.z = pos.z + 40.0f * nrm.z;
            hitObjGetPos(d->hit[3], &pos);
            hitObjGetNormal(d->hit[3], &nrm);
            w->in.x = pos.x + 40.0f * nrm.x;
            w->in.z = pos.z + 40.0f * nrm.z;
            break;
    }
    evtSetValue(event, args[1], (EvtWord)w);
    return EVT_RETURN_DONE;
}

#if VERSION <= VERSION_DEMO_JP
/** the demo defines house_close_se right after house_open_se */
EVT_BEGIN(house_close_se)
    CALL_CHILD(house_open_se)
    RETURN
EVT_END()
#endif

/**
 * Fades the map's first blend colour from white to black over 300 ms,
 * darkening everything not flagged NO_BLEND (the town around a house); spawned by house_in.
 */
EVT_BEGIN(evt_dark)
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, 300)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 0)
    RETURN
EVT_END()

/** Same fade as evt_dark on the map's second blend colour (objects not flagged NO_BLEND2). */
EVT_BEGIN(evt_dark2)
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, 300)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 1, LW(0), LW(0), LW(0), 255)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_map_set_blend, 1, LW(0), LW(0), LW(0), 0)
    RETURN
EVT_END()

/** Fades the first blend colour back from black to white over 300 ms, then turns the blend off; house_out. */
static EVT_BEGIN(evt_light)
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 300)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_map_blend_off, 0)
    RETURN
EVT_END()

/** Fades the second blend colour back from black to white over 300 ms, then turns it off; house_out. */
EVT_BEGIN(evt_light2)
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 300)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_map_set_blend, 1, LW(0), LW(0), LW(0), 255)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_map_blend_off, 1)
    RETURN
EVT_END()

/** Empty: evt_door_close spawns it where a door-raise sound would go, but it plays nothing. */
EVT_BEGIN(door_up_se)
    RETURN
EVT_END()

/** House-front closing sound for evt_door_close: just plays house_open_se again. */
#if VERSION >= VERSION_JP
EVT_BEGIN(house_close_se)
    CALL_CHILD(house_open_se)
    RETURN
EVT_END()
#endif

/**
 * Plays the house's opening map animation (HouseData.anim[0]) when Mario goes in,
 * with the shop-shutter rattle for "S_mise_open" or the plain house-open sound otherwise,
 * and waits for the animation to finish.
 */
EVT_BEGIN(in_houseanim)
    WAIT_MS(500)
    CALL(animation, LW(10), LW(0), LW(1), LW(2), LW(3))
    IF_INT_NOT_EQUAL(LW(0), 0)
        BEGIN_INLINE_EVENT
            IF_STR_EQUAL(LW(0), STRING("S_mise_open"))
                CALL(door_group, LW(10), LW(0))
                CALL(evt_mapobj_get_position, LW(0), LW(2), LW(3), LW(4))
                CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_OPEN1"), LW(2), LW(3), LW(4), 0)
                LOOP(4)
                    WAIT_MS(166)
                    CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(2), LW(3), LW(4), 0)
                END_LOOP
            ELSE
                CALL(door_group, LW(10), LW(0))
                CALL(evt_mapobj_get_position, LW(0), LW(2), LW(3), LW(4))
                CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_OPEN1"), LW(2), LW(3), LW(4), 0)
            END_IF
        END_INLINE_EVENT
        CALL(evt_map_playanim, LW(0), 0, 0)
        CALL(evt_map_checkanim, LW(0), LW(4), LW(5))
        WAIT_MS(LW(5))
    END_IF
    RETURN
EVT_END()

/**
 * Plays the house's closing map animation (HouseData.anim[2]) when Mario leaves,
 * with the shutter rattle for "S_mise_close", waits for it, then plays the house-shut sound.
 */
EVT_BEGIN(out_houseanim)
    CALL(animation, LW(10), LW(0), LW(1), LW(2), LW(3))
    IF_INT_NOT_EQUAL(LW(2), 0)
        BEGIN_INLINE_EVENT
            IF_STR_EQUAL(LW(2), STRING("S_mise_close"))
                CALL(door_group, LW(10), LW(0))
                CALL(evt_mapobj_get_position, LW(0), LW(2), LW(3), LW(4))
                LOOP(4)
                    CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_DOWN1"), LW(2), LW(3), LW(4), 0)
                    WAIT_MS(166)
                END_LOOP
            END_IF
        END_INLINE_EVENT
        CALL(evt_map_playanim, LW(2), 0, 0)
        CALL(evt_map_checkanim, LW(2), LW(4), LW(5))
        WAIT_MS(LW(5))
        BEGIN_INLINE_EVENT
            CALL(door_group, LW(10), LW(0))
            CALL(evt_mapobj_get_position, LW(0), LW(2), LW(3), LW(4))
            CALL(evt_snd_sfxon_3d, STRING("SFX_HOUSE_SHUT1"), LW(2), LW(3), LW(4), 0)
        END_INLINE_EVENT
    END_IF
    RETURN
EVT_END()

/**
 * Swings the house's door group open 80 degrees and shut again, then tips it 90 degrees over, with the open,
 * shut and fall sounds; spawned by house_in.
 */
EVT_BEGIN(in_dooranim)
    CALL(door_group, LW(10), LW(9))
    BEGIN_INLINE_EVENT
        CALL(evt_mapobj_get_position, LW(9), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN1"), LW(2), LW(3), LW(4), 0)
        WAIT_MS(1500)
        CALL(evt_mapobj_get_position, LW(9), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT1"), LW(2), LW(3), LW(4), 0)
        WAIT_MS(500)
        CALL(evt_mapobj_get_position, LW(9), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_FALL1"), LW(2), LW(3), LW(4), 0)
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 5, 0, 80, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
    CALL(evt_mapobj_rotate, 1, LW(9), 0, LW(0), 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    WAIT_MS(500)
    CALL(evt_sub_intpl_msec_init, 2, 80, 0, 500)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
    CALL(evt_mapobj_rotate, 1, LW(9), 0, LW(0), 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    CALL(evt_sub_intpl_msec_init, 2, 0, 90, 500)
    LABEL(2)
    CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
    CALL(evt_mapobj_rotate, 1, LW(9), LW(0), 0, 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(2)
    END_IF
    RETURN
EVT_END()

/** Reverse of in_dooranim for house_out: stands the door back up, swings it open and shut with sounds. */
EVT_BEGIN(out_dooranim)
    CALL(door_group, LW(10), LW(9))
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_mapobj_get_position, LW(9), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN1"), LW(2), LW(3), LW(4), 0)
        WAIT_MS(1000)
        CALL(evt_mapobj_get_position, LW(9), LW(2), LW(3), LW(4))
        CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT1"), LW(2), LW(3), LW(4), 0)
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 5, 90, 0, 500)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
    CALL(evt_mapobj_rotate, 1, LW(9), LW(0), 0, 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_sub_intpl_msec_init, 5, 0, 80, 500)
    LABEL(1)
    CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
    CALL(evt_mapobj_rotate, 1, LW(9), 0, LW(0), 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(1)
    END_IF
    WAIT_MS(500)
    CALL(evt_sub_intpl_msec_init, 5, 80, 0, 500)
    LABEL(2)
    CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
    CALL(evt_mapobj_rotate, 1, LW(9), 0, LW(0), 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(2)
    END_IF
    RETURN
EVT_END()

/**
 * Case event (from evt_door_setup) that takes Mario into a house:
 * dips the music, locks controls, shows the inside groups and hits,
 * walks Mario and partners in while the town fades dark and the front opens.
 * LW(10) is the HouseWork; DoorFLAG blocks re-entry while it runs.
 */
EVT_BEGIN(house_in)
    PEEK_INT(LW(0), PTR(&DoorFLAG))
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    POKE_INT(1, PTR(&DoorFLAG))
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_envoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_env_lpf, 0, 800)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam_letter_box_disable, 1)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(in_pos, LW(10), LW(0), LW(2))
        ADD(LW(1), 1)
        CALL(evt_cam3d_evt_set_xyz, LW(0), LW(1), LW(2), 0, 150, 11)
    END_INLINE_EVENT
    SET_VALUE(LW(0), 0)
    LOOP(0)
        CALL(get_noclip_map, LW(10), LW(0), LW(1))
        IF_INT_EQUAL(LW(1), -1)
            BREAK_LOOP
        END_IF
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_BBOX_CULL)
        ADD(LW(0), 1)
    END_LOOP
    CALL(outside_group, LW(10), LW(0))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_NO_BLEND)
    CALL(door_group, LW(10), LW(0))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_NO_BLEND)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_NO_BLEND2)
    CALL(inside_group, LW(10), LW(0), LW(1))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(0), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, LW(1), 1, 1)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_NO_BLEND)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_NO_BLEND2)
#if VERSION >= VERSION_JP
    CALL(N_evt_mario_party_door_halve_hitbox)
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(out_pos, LW(10), LW(0), LW(2))
    CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(135.0f))
    CALL(evt_party_move_beside_mario, 0)
    CALL(evt_party_move_beside_mario, 1)
    SPAWN_EVENT_GET_ID(PTR(in_dooranim), LW(15))
    BEGIN_INLINE_EVENT
        CALL(npc_dark, LW(10))
        CALL_CHILD(in_houseanim)
        SPAWN_EVENT(evt_dark2)
    END_INLINE_EVENT
    WAIT_MS(300)
    SPAWN_EVENT(evt_dark)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(in_pos, LW(10), LW(0), LW(2))
    CALL(evt_mario_party_door_move, LW(0), LW(2), FLOAT(135.0f))
    CALL(evt_cam3d_evt_xyz_off, 0, 11)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    LOOP(0)
        IS_EVENT_RUNNING(LW(15), LW(0))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
#if VERSION >= VERSION_JP
    CALL(snd_door_in)
#endif
    POKE_INT(0, PTR(&DoorFLAG))
    RETURN
EVT_END()

/**
 * Case event that walks Mario back out of a house:
 * restores the music, plays the closing animation, fades the town back in,
 * then hides the inside groups and hits and resets the blend flags. LW(10) is the HouseWork.
 */
EVT_BEGIN(house_out)
    PEEK_INT(LW(0), PTR(&DoorFLAG))
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
    POKE_INT(1, PTR(&DoorFLAG))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam_letter_box_disable, 1)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(out_pos, LW(10), LW(0), LW(2))
        ADD(LW(1), 1)
        CALL(evt_cam3d_evt_set_xyz, LW(0), LW(1), LW(2), 0, 150, 11)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SPAWN_EVENT(evt_light2)
        CALL_CHILD(out_houseanim)
        SPAWN_EVENT(evt_light)
    END_INLINE_EVENT
    SPAWN_EVENT_GET_ID(PTR(out_dooranim), LW(15))
    WAIT_MS(1000)
#if VERSION >= VERSION_JP
    CALL(N_evt_mario_party_door_halve_hitbox)
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(out_pos, LW(10), LW(0), LW(2))
    CALL(evt_mario_party_door_move, LW(0), LW(2), FLOAT(135.0f))
    SET_VALUE(LW(0), 0)
    LOOP(0)
        CALL(get_noclip_map, LW(10), LW(0), LW(1))
        IF_INT_EQUAL(LW(1), -1)
            BREAK_LOOP
        END_IF
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_BBOX_CULL)
        ADD(LW(0), 1)
    END_LOOP
    CALL(evt_cam3d_evt_xyz_off, 100, 11)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    LOOP(0)
        IS_EVENT_RUNNING(LW(15), LW(0))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    POKE_INT(0, PTR(&DoorFLAG))
    CALL(inside_group, LW(10), LW(0), LW(1))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, LW(1), 1, 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(0), MAPOBJ_FLAG_NO_BLEND)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(0), MAPOBJ_FLAG_NO_BLEND2)
    CALL(outside_group, LW(10), LW(0))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(0), MAPOBJ_FLAG_NO_BLEND)
    CALL(door_group, LW(10), LW(0))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(0), MAPOBJ_FLAG_NO_BLEND)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(0), MAPOBJ_FLAG_NO_BLEND2)
    CALL(npc_light, LW(10))
#if VERSION >= VERSION_JP
    CALL(snd_door_out)
#endif
    RETURN
EVT_END()

/**
 * Map-init setup for a house whose whole front opens (Koopa Village, nok_00/nok_01): LW(0) is its HouseData.
 * Hides the inside, then registers house_in and house_out as case events on the entry and exit hits.
 */
EVT_BEGIN(evt_door_setup)
    CALL(door_entry, LW(0), LW(10))
    POKE_INT(0, PTR(&DoorFLAG))
    CALL(init_inside_group, LW(10), LW(0), LW(1))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(0), MAPOBJ_FLAG_HIDE)
    END_IF
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_hitobj_onoff, LW(1), 1, 0)
    END_IF
    CALL(inout_hit, LW(10), LW(0), LW(1), LW(2), LW(3))
    CALL(evt_run_case_evt, LW(0), 1, LW(1), 0, PTR(house_in), 0)
    CALL(evt_run_case_evt, LW(2), 1, LW(3), 0, PTR(house_out), 0)
    RETURN
EVT_END()

/**
 * Fades the map's first blend colour from white to black over 300 ms,
 * darkening the outside (anything not flagged NO_BLEND) once Mario steps through a door;
 * used by the evt_door_open family.
 */
EVT_BEGIN(door_dark)
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, 300)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 0)
    RETURN
EVT_END()

/** Same as door_dark on the map's second blend colour (objects not flagged NO_BLEND2). */
EVT_BEGIN(door_dark2)
    CALL(evt_sub_intpl_msec_init, 11, 255, 0, 300)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_map_set_blend, 1, LW(0), LW(0), LW(0), 255)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_map_set_blend, 1, LW(0), LW(0), LW(0), 0)
    RETURN
EVT_END()

/**
 * Fades the first blend colour back from black to white over 300 ms and turns the blend off;
 * used when Mario leaves through a door (evt_door_close, evt_door_close_roll).
 */
EVT_BEGIN(door_light)
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 300)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_map_set_blend, 0, LW(0), LW(0), LW(0), 255)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_map_blend_off, 0)
    RETURN
EVT_END()

/** Same as door_light on the map's second blend colour; also spawned directly by usu_01 (Twilight Town). */
EVT_BEGIN(door_light2)
    CALL(evt_sub_intpl_msec_init, 11, 0, 255, 300)
    LABEL(0)
    CALL(evt_sub_intpl_msec_get_value)
    CALL(evt_map_set_blend, 1, LW(0), LW(0), LW(0), 255)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(evt_map_blend_off, 1)
    RETURN
EVT_END()

/**
 * Front-A case event (registered by evt_door_entry) that takes Mario in through a door:
 * shows the inside, keeps Mario, partners and the listed NPCs lit, swings the door open,
 * walks the party in and darkens the outside.
 * LW(0) is the DoorParam; LW(15) bits: 2 = no darkening, 4 = start the wall event early.
 */
EVT_BEGIN(evt_door_open)
    // Lock the controls and run the door's own open script, if it has one.
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    POKE_INT(1, PTR(&DoorFLAG))
    CALL(evt_door_param, LW(0), 7, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        SET_VALUE(LF(0), 0)
        SPAWN_EVENT(LW(1))
    END_IF
    // Set up the rooms: the outside stops culling and fading, the camera heads for the door,
    // the door itself stays solid, and the inside is revealed with its collision switched on.
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_door_save_mapflag, LW(1))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_BBOX_CULL)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_door_param, LW(0), 4, LW(1), LW(2), LW(3))
        CALL(evt_mario_get_pos, 0, LW(4), LW(5), LW(6))
        ADD(LW(5), 2)
        CALL(evt_cam3d_evt_set_xyz, LW(1), LW(5), LW(3), 0, 150, 11)
    END_INLINE_EVENT
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
    END_IF
    CALL(evt_door_param, LW(0), 1, LW(1), LW(2), LW(3))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    CALL(evt_door_param, LW(0), 3, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    IF_INT_NOT_EQUAL(LW(2), 0)
        CALL(evt_hitobj_onoff, LW(2), 1, 1)
    END_IF
    // Hide the door's NPCs if it asks for that,
    // and keep Mario, partners and NPCs lit while the outside darkens.
    CALL(evt_door_param, LW(0), 9, LW(1))
    IF_BITS_SET(LW(1), 1)
        CALL(npc_hide_onoff, LW(0), 0)
    END_IF
    CALL(door_dark_flag, LW(0), 1)
    // With bit 4 the house wall swings open early, half a second in.
    IF_BITS_SET(LW(15), 4)
        CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
        IF_INT_NOT_EQUAL(LW(9), 0)
            BEGIN_INLINE_EVENT
                WAIT_MS(500)
                SPAWN_EVENT(house_open_se)
                CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
                SET_VALUE(LW(6), 0)
                CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
                LABEL(2)
                CALL(evt_sub_intpl_msec_get_value)
                SET_VALUE(LW(5), LW(1))
                SET_VALUE(LW(1), 0)
                SET_VALUE(LF(0), 0)
                SPAWN_EVENT(LW(9))
                SET_VALUE(LW(6), 1)
                WAIT_FRAMES(1)
                IF_INT_EQUAL(LW(5), 1)
                    GOTO(2)
                END_IF
            END_INLINE_EVENT
        END_IF
    END_IF
#if VERSION >= VERSION_JP
    CALL(N_evt_mario_party_door_halve_hitbox)
#endif
    // Mario walks to the spot outside the door with the partners beside him,
    // and the outside starts to darken.
    CALL(evt_door_param, LW(0), 5, LW(1), LW(2), LW(3))
    CALL(evt_mario_mov_pos2, LW(1), LW(3), FLOAT(135.0f))
    CALL(evt_party_move_beside_mario, 0)
    CALL(evt_party_move_beside_mario, 1)
    IF_BITS_CLEAR(LW(15), 2)
        SPAWN_EVENT(door_dark)
    END_IF
    // The door swings open with its sound.
    SPAWN_EVENT(door_open_se)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(7), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 5, 0, 180, 500)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 0)
            SET_VALUE(LF(0), 0)
            SPAWN_EVENT(LW(7))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(0)
            END_IF
        END_INLINE_EVENT
    END_IF
    // The party walks in to the inside spot while the door swings shut behind them.
    WAIT_MS(500)
    CALL(evt_door_param, LW(0), 4, LW(1), LW(2), LW(3))
    CALL(evt_mario_party_door_move, LW(1), LW(3), FLOAT(135.0f))
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(7), 0)
        BEGIN_INLINE_EVENT
            SPAWN_EVENT(door_close_se)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 1)
            SET_VALUE(LF(0), 0)
            SPAWN_EVENT(LW(7))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(1)
            END_IF
        END_INLINE_EVENT
    END_IF
    // Otherwise the house wall swings open now.
    IF_BITS_CLEAR(LW(15), 4)
        CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
        IF_INT_NOT_EQUAL(LW(9), 0)
            BEGIN_INLINE_EVENT
                SPAWN_EVENT(house_open_se)
                CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
                SET_VALUE(LW(6), 0)
                CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
                LABEL(2)
                CALL(evt_sub_intpl_msec_get_value)
                SET_VALUE(LW(5), LW(1))
                SET_VALUE(LW(1), 0)
                SET_VALUE(LF(0), 0)
                SPAWN_EVENT(LW(9))
                SET_VALUE(LW(6), 1)
                WAIT_FRAMES(1)
                IF_INT_EQUAL(LW(5), 1)
                    GOTO(2)
                END_IF
            END_INLINE_EVENT
        END_IF
    END_IF
    // The outside finishes darkening, and the door's out-piece, if any, swings down with its sound.
    WAIT_MS(500)
    IF_BITS_CLEAR(LW(15), 2)
        SPAWN_EVENT(door_dark2)
    END_IF
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(8), 0)
        BEGIN_INLINE_EVENT
            WAIT_MS(500)
            SPAWN_EVENT(door_down_se)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
            LABEL(3)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LF(0), 0)
            SPAWN_EVENT(LW(8))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(3)
            END_IF
        END_INLINE_EVENT
    END_IF
    // The camera is released, the controls come back and the indoor sound takes over.
    WAIT_MS(500)
    CALL(evt_cam3d_evt_xyz_off, 0, 11)
    POKE_INT(0, PTR(&DoorFLAG))
    WAIT_FRAMES(2)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    CALL(snd_door_in)
    RETURN
EVT_END()

/**
 * Fahr Outpost (bom_01) cutscene variant of evt_door_open: no camera or Mario movement;
 * sets GF(0) and holds the door open until the map's script clears it, then closes it and darkens the outside.
 */
EVT_BEGIN(evt_door_open_bom_01)
    // Run the door's open script, then set up the rooms as evt_door_open does, without moving the camera.
    CALL(evt_door_param, LW(0), 7, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        SPAWN_EVENT(LW(1))
    END_IF
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_door_save_mapflag, LW(1))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_BBOX_CULL)
    END_IF
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
    END_IF
    CALL(evt_door_param, LW(0), 1, LW(1), LW(2), LW(3))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    CALL(evt_door_param, LW(0), 3, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    IF_INT_NOT_EQUAL(LW(2), 0)
        CALL(evt_hitobj_onoff, LW(2), 1, 1)
    END_IF
    CALL(door_dark_flag, LW(0), 1)
    // The door swings open with its sound.
    SPAWN_EVENT(door_open_se)
#if VERSION == VERSION_JP
    CALL(N_evt_mario_party_door_halve_hitbox)
#endif
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(7), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 5, 0, 180, 500)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 0)
            SPAWN_EVENT(LW(7))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(0)
            END_IF
        END_INLINE_EVENT
    END_IF
    // Hold the door open until the map's cutscene clears GF(0).
    WAIT_MS(500)
    SET_VALUE(GF(0), 1)
    LOOP(0)
        IF_INT_EQUAL(GF(0), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    // The outside darkens and the door swings shut.
    SPAWN_EVENT(door_dark)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(7), 0)
        BEGIN_INLINE_EVENT
            SPAWN_EVENT(door_close_se)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 2, 180, 0, 500)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 1)
            SPAWN_EVENT(LW(7))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(1)
            END_IF
        END_INLINE_EVENT
    END_IF
    // The house wall swings open, the outside finishes darkening and the out-piece swings down.
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(9), 0)
        BEGIN_INLINE_EVENT
            SPAWN_EVENT(house_open_se)
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            SET_VALUE(LW(6), 0)
            CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
            LABEL(2)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 0)
            SPAWN_EVENT(LW(9))
            SET_VALUE(LW(6), 1)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(2)
            END_IF
        END_INLINE_EVENT
    END_IF
    WAIT_MS(500)
    SPAWN_EVENT(door_dark2)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(8), 0)
        BEGIN_INLINE_EVENT
            WAIT_MS(500)
            SPAWN_EVENT(door_down_se)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
            LABEL(3)
            CALL(evt_sub_intpl_msec_get_value)
            SPAWN_EVENT(LW(8))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(3)
            END_IF
        END_INLINE_EVENT
    END_IF
    // The indoor sound takes over.
    WAIT_MS(500)
    CALL(snd_door_in)
    RETURN
EVT_END()

/**
 * Opens a house without the door swing or Mario walking in: shows the inside, darkens the outside
 * and runs the wall events.
 * Run by the case events of Rogueport houses with unusual entrances: gor_02 house 03, after Mario rolls in
 * (SFX_STG4_MARIO_ROLL_DOWN1/2), and gor_03 house 3, entered through a chest of drawers.
 * Guess: "roll" refers to that rolling entrance.
 */
EVT_BEGIN(evt_door_open_roll)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_door_param, LW(0), 7, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        SPAWN_EVENT(LW(1))
    END_IF
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_door_save_mapflag, LW(1))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_BBOX_CULL)
    END_IF
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
    END_IF
    CALL(evt_door_param, LW(0), 1, LW(1), LW(2), LW(3))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    CALL(evt_door_param, LW(0), 3, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    IF_INT_NOT_EQUAL(LW(2), 0)
        CALL(evt_hitobj_onoff, LW(2), 1, 1)
    END_IF
    CALL(door_dark_flag, LW(0), 1)
    SPAWN_EVENT(door_dark)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(9), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            SET_VALUE(LW(6), 0)
            CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
            LABEL(2)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 0)
            SPAWN_EVENT(LW(9))
            SET_VALUE(LW(6), 1)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(2)
            END_IF
        END_INLINE_EVENT
    END_IF
    WAIT_MS(500)
    SPAWN_EVENT(door_dark2)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(8), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 2, 0, 180, 500)
            LABEL(3)
            CALL(evt_sub_intpl_msec_get_value)
            SPAWN_EVENT(LW(8))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(3)
            END_IF
        END_INLINE_EVENT
    END_IF
    WAIT_MS(500)
    CALL(evt_cam3d_evt_xyz_off, 0, 11)
    CALL(evt_mario_key_onoff, 1)
    CALL(snd_door_in)
    RETURN
EVT_END()

/**
 * Front-A case event (registered by evt_door_entry) that takes Mario back out:
 * undoes evt_door_open, walking the party out, closing the door, restoring the outside and hiding the inside.
 * LW(15) bits: 1 = keep the inside shown, 2 = no fade, 8 = don't walk Mario,
 * 16 = use the exit spot measured from Mario (evt_door_param 11).
 */
EVT_BEGIN(evt_door_close)
    // Lock the controls, run the door's close script and send the camera to the spot outside the door.
    CALL(evt_cam_letter_box_disable, 1)
    CALL(evt_mario_key_onoff, 0)
    POKE_INT(1, PTR(&DoorFLAG))
    CALL(evt_door_param, LW(0), 7, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(2), 0)
        SET_VALUE(LF(0), 1)
        SPAWN_EVENT(LW(2))
    END_IF
    BEGIN_INLINE_EVENT
        IF_BITS_CLEAR(LW(15), 16)
            CALL(evt_door_param, LW(0), 5, LW(1), LW(2), LW(3))
        ELSE
            CALL(evt_door_param, LW(0), 11, LW(1), LW(2), LW(3))
        END_IF
        CALL(evt_mario_get_pos, 0, LW(4), LW(5), LW(6))
        ADD(LW(5), 2)
        CALL(evt_cam3d_evt_set_xyz, LW(1), LW(5), LW(3), 0, 150, 11)
    END_INLINE_EVENT
    // The outside starts to light up again and the out-piece swings back up with its sound.
    IF_BITS_CLEAR(LW(15), 2)
        SPAWN_EVENT(door_light2)
    END_IF
    SPAWN_EVENT(door_up_se)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(8), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
            LABEL(3)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LF(0), 1)
            SPAWN_EVENT(LW(8))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(3)
            END_IF
        END_INLINE_EVENT
    END_IF
    // The house wall swings shut with its sound.
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(9), 0)
        BEGIN_INLINE_EVENT
            WAIT_MS(400)
            SPAWN_EVENT(house_close_se)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            SET_VALUE(LW(6), 0)
            CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
            LABEL(2)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 3)
            SET_VALUE(LF(0), 1)
            SPAWN_EVENT(LW(9))
            SET_VALUE(LW(6), 1)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(2)
            END_IF
        END_INLINE_EVENT
    END_IF
    // The outside finishes lighting up and the door swings open.
    WAIT_MS(500)
    IF_BITS_CLEAR(LW(15), 2)
        SPAWN_EVENT(door_light)
    END_IF
    SPAWN_EVENT(door_open_se)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(7), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 5, 0, 180, 500)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 2)
            SET_VALUE(LF(0), 1)
            SPAWN_EVENT(LW(7))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(1)
            END_IF
        END_INLINE_EVENT
    END_IF
    // The party walks out (unless bit 8) and the door swings shut behind them.
    WAIT_MS(500)
    IF_BITS_CLEAR(LW(15), 16)
        CALL(evt_door_param, LW(0), 5, LW(1), LW(2), LW(3))
    ELSE
        CALL(evt_door_param, LW(0), 11, LW(1), LW(2), LW(3))
    END_IF
    IF_BITS_CLEAR(LW(15), 8)
        CALL(evt_mario_party_door_move, LW(1), LW(3), FLOAT(135.0f))
    END_IF
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(7), 0)
        BEGIN_INLINE_EVENT
            SPAWN_EVENT(door_close_se)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 3)
            SET_VALUE(LF(0), 1)
            SPAWN_EVENT(LW(7))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(0)
            END_IF
        END_INLINE_EVENT
        WAIT_MS(500)
    END_IF
    // The camera returns to normal, the door's NPCs show again and the inside is hidden (kept with bit 1).
    CALL(evt_cam3d_evt_xyz_off, 100, 11)
    CALL(door_dark_flag, LW(0), 0)
    CALL(evt_door_param, LW(0), 9, LW(1))
    IF_BITS_SET(LW(1), 1)
        CALL(npc_hide_onoff, LW(0), 1)
    END_IF
    CALL(evt_door_param, LW(0), 3, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        IF_BITS_CLEAR(LW(15), 1)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_HIDE)
        END_IF
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    IF_INT_NOT_EQUAL(LW(2), 0)
        CALL(evt_hitobj_onoff, LW(2), 1, 0)
    END_IF
    // The outside and the door are drawn as before, and the outside's saved culling state is restored.
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_NO_BLEND)
    END_IF
    CALL(evt_door_param, LW(0), 1, LW(1), LW(2), LW(3))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_door_load_mapflag, LW(1))
    END_IF
    // The controls come back and the outdoor sound returns.
    POKE_INT(0, PTR(&DoorFLAG))
    WAIT_FRAMES(2)
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_cam_letter_box_disable, 0)
    CALL(snd_door_out)
    RETURN
EVT_END()

/**
 * Counterpart of evt_door_open_roll: restores the outside and hides the inside without the door swing
 * or Mario walking out. gor_03's case script for house 4 runs it.
 */
EVT_BEGIN(evt_door_close_roll)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_door_param, LW(0), 7, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(2), 0)
        SPAWN_EVENT(LW(2))
    END_IF
    BEGIN_INLINE_EVENT
        CALL(evt_door_param, LW(0), 5, LW(1), LW(2), LW(3))
        CALL(evt_mario_get_pos, 0, LW(4), LW(5), LW(6))
        ADD(LW(5), 2)
        CALL(evt_cam3d_evt_set_xyz, LW(1), LW(5), LW(3), 0, 150, 11)
    END_INLINE_EVENT
    SPAWN_EVENT(door_light2)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(8), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
            LABEL(3)
            CALL(evt_sub_intpl_msec_get_value)
            SPAWN_EVENT(LW(8))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(3)
            END_IF
        END_INLINE_EVENT
    END_IF
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(9), 0)
        BEGIN_INLINE_EVENT
            CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
            SET_VALUE(LW(6), 0)
            CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
            LABEL(2)
            CALL(evt_sub_intpl_msec_get_value)
            SET_VALUE(LW(5), LW(1))
            SET_VALUE(LW(1), 3)
            SPAWN_EVENT(LW(9))
            SET_VALUE(LW(6), 1)
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(5), 1)
                GOTO(2)
            END_IF
        END_INLINE_EVENT
    END_IF
    WAIT_MS(500)
    SPAWN_EVENT(door_light)
    CALL(evt_cam3d_evt_xyz_off, 100, 11)
    CALL(door_dark_flag, LW(0), 0)
    CALL(evt_door_param, LW(0), 3, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        IF_BITS_CLEAR(LW(15), 1)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_HIDE)
        END_IF
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    IF_INT_NOT_EQUAL(LW(2), 0)
        CALL(evt_hitobj_onoff, LW(2), 1, 0)
    END_IF
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_NO_BLEND)
    END_IF
    CALL(evt_door_param, LW(0), 1, LW(1), LW(2), LW(3))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_door_load_mapflag, LW(1))
    END_IF
    CALL(evt_mario_key_onoff, 1)
    CALL(snd_door_out)
    RETURN
EVT_END()

/**
 * Puts a door straight into its "inside" state with no animation or fade:
 * blend colours black, wall events at their end angle, camera snapped.
 * Used when a map starts with Mario indoors (aaa_00, Rogueport maps).
 */
EVT_BEGIN(evt_door_open_quick)
    CALL(evt_door_param, LW(0), 7, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        SPAWN_EVENT(LW(1))
    END_IF
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_door_save_mapflag, LW(1))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_BBOX_CULL)
    END_IF
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(10), LW(0))
        CALL(evt_door_param, LW(10), 4, LW(0), LW(1), LW(2))
        CALL(evt_mario_get_pos, 0, LW(4), LW(5), LW(6))
        SET_VALUE(LW(1), LW(5))
        CALL(evt_cam3d_get_shift, LW(0), LW(1), LW(2), LW(3))
        CALL(evt_cam3d_event_from_road, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5), LW(6), LW(7), LW(8), LW(9))
        CALL(evt_cam3d_evt_set, LW(4), LW(5), LW(6), LW(7), LW(8), LW(9), 0, 11)
        WAIT_FRAMES(1)
        CALL(evt_cam3d_evt_off, 0, 11)
    END_INLINE_EVENT
    CALL(evt_door_param, LW(0), 2, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
    END_IF
    CALL(evt_door_param, LW(0), 1, LW(1), LW(2), LW(3))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    CALL(evt_door_param, LW(0), 3, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, LW(1), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_NO_BLEND2)
    END_IF
    IF_INT_NOT_EQUAL(LW(2), 0)
        CALL(evt_hitobj_onoff, LW(2), 1, 1)
    END_IF
    CALL(door_dark_flag, LW(0), 1)
    CALL(evt_map_set_blend, 0, 0, 0, 0, 0)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(9), 0)
        BEGIN_INLINE_EVENT
            SET_VALUE(LW(0), 180)
            SPAWN_EVENT(LW(9))
        END_INLINE_EVENT
    END_IF
    CALL(evt_map_set_blend, 1, 0, 0, 0, 0)
    CALL(evt_door_param, LW(0), 6, LW(7), LW(8), LW(9))
    IF_INT_NOT_EQUAL(LW(8), 0)
        BEGIN_INLINE_EVENT
            SET_VALUE(LW(0), 180)
            SPAWN_EVENT(LW(8))
        END_INLINE_EVENT
    END_IF
    CALL(snd_door_in)
    RETURN
EVT_END()

/**
 * Map-init setup for an ordinary door (DoorParam in LW(0)):
 * hides the inside and its hits, registers evt_door_open on hitOut
 * and evt_door_close on hitIn as A-in-front case events, and hides the listed NPCs.
 */
EVT_BEGIN(evt_door_entry)
    CALL(evt_door_param, LW(0), 3, LW(1), LW(2))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, LW(1), MAPOBJ_FLAG_HIDE)
    END_IF
    IF_INT_NOT_EQUAL(LW(2), 0)
        CALL(evt_hitobj_onoff, LW(2), 1, 0)
    END_IF
    CALL(evt_door_param, LW(0), 1, LW(1), LW(2), LW(3))
    IF_INT_NOT_EQUAL(LW(2), 0)
        SET_VALUE(LW(15), 0)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(2), 0, PTR(evt_door_close), 0)
    END_IF
    IF_INT_NOT_EQUAL(LW(3), 0)
        SET_VALUE(LW(15), 0)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(3), 0, PTR(evt_door_open), 0)
    END_IF
    CALL(evt_door_param, LW(0), 9, LW(1))
    IF_BITS_SET(LW(1), 1)
        CALL(npc_hide_onoff, LW(0), 1)
    END_IF
    RETURN
EVT_END()

/**
 * Returns HouseData.hit[0..3] of the HouseWork in args[0] into args[1..4]:
 * case condition and hit name pairs for the way in and the way out (evt_door_setup).
 */
static USER_FUNC(inout_hit) {
    EvtWord* args = event->args;
    HouseWork* w = (HouseWork*)evtGetValue(event, args[0]);
    evtSetValue(event, args[1], (EvtWord)w->data->hit[0]);
    evtSetValue(event, args[2], (EvtWord)w->data->hit[1]);
    evtSetValue(event, args[3], (EvtWord)w->data->hit[2]);
    evtSetValue(event, args[4], (EvtWord)w->data->hit[3]);
    return EVT_RETURN_DONE;
}

/** Returns the X and Z of the spot outside the house that door_entry worked out. */
static USER_FUNC(out_pos) {
    EvtWord* args = event->args;
    HouseWork* w = (HouseWork*)evtGetValue(event, args[0]);
    evtSetValue(event, args[1], w->out.x);
    evtSetValue(event, args[2], w->out.z);
    return EVT_RETURN_DONE;
}

/** Returns the X and Z of the spot inside the house that door_entry worked out. */
static USER_FUNC(in_pos) {
    EvtWord* args = event->args;
    HouseWork* w = (HouseWork*)evtGetValue(event, args[0]);
    evtSetValue(event, args[1], w->in.x);
    evtSetValue(event, args[2], w->in.z);
    return EVT_RETURN_DONE;
}

/** Returns the house's outside map group name (HouseData.outside). */
static USER_FUNC(outside_group) {
    EvtWord* args = event->args;
    HouseWork* w = (HouseWork*)evtGetValue(event, args[0]);
    evtSetValue(event, args[1], w->data->outside);
    return EVT_RETURN_DONE;
}

/** Returns the house's door map group name (HouseData.door); also used as the sound position. */
static USER_FUNC(door_group) {
    EvtWord* args = event->args;
    HouseWork* w = (HouseWork*)evtGetValue(event, args[0]);
    evtSetValue(event, args[1], w->data->door);
    return EVT_RETURN_DONE;
}

/** Returns HouseData.inside: the interior map group and its hit object, shown while Mario is inside. */
static USER_FUNC(inside_group) {
    EvtWord* args = event->args;
    HouseWork* w = (HouseWork*)evtGetValue(event, args[0]);
    evtSetValue(event, args[1], w->data->inside[0]);
    evtSetValue(event, args[2], w->data->inside[1]);
    return EVT_RETURN_DONE;
}

/** Returns HouseData.initInside: the map group and hit object evt_door_setup hides at map start. */
static USER_FUNC(init_inside_group) {
    EvtWord* args = event->args;
    HouseWork* w = (HouseWork*)evtGetValue(event, args[0]);
    evtSetValue(event, args[1], w->data->initInside[0]);
    evtSetValue(event, args[2], w->data->initInside[1]);
    return EVT_RETURN_DONE;
}

/** Returns the house's four map animation names (HouseData.anim): [0] opening, [2] closing; 0 for none. */
static USER_FUNC(animation) {
    EvtWord* args = event->args;
    HouseWork* w = (HouseWork*)evtGetValue(event, args[0]);
    evtSetValue(event, args[1], w->data->anim[0]);
    evtSetValue(event, args[2], w->data->anim[1]);
    evtSetValue(event, args[3], w->data->anim[2]);
    evtSetValue(event, args[4], w->data->anim[3]);
    return EVT_RETURN_DONE;
}

// the item flag the dark/light helpers toggle on field items: 0x80 in the demo, 0x40 in retail
#if VERSION <= VERSION_DEMO_JP
#define DOOR_ITEM_DARK_FLAG 0x80
#else
#define DOOR_ITEM_DARK_FLAG 0x40
#endif

#define NPC_LIGHT_BODY(FN, ICONFN)                               \
    HouseWork* w = (HouseWork*)evtGetValue(event, *event->args); \
    MarioWork* mario = marioGetPtr();                            \
    PartyEntry* party = partyGetPtr(0);                          \
    PartyEntry* follower = partyGetPtr(1);                       \
    const char** list;                                           \
    if (mario) {                                                 \
        FN(marioGetPtr()->paperAnimGroupId[0], 0x1800);          \
        FN(marioGetPtr()->paperAnimGroupId[1], 0x1800);          \
        FN(marioGetPtr()->paperAnimGroupId[2], 0x1800);          \
    }                                                            \
    if (party) {                                                 \
        FN(party->paperAnimGroup, 0x1800);                       \
    }                                                            \
    if (follower) {                                              \
        FN(follower->paperAnimGroup, 0x1800);                    \
    }                                                            \
    list = w->data->npcs;                                        \
    if (list) {                                                  \
        for (; *list; list++) {                                  \
            NpcEntry* npc = npcNameToPtr_NoAssert(*list);        \
            if (npc) {                                           \
                FN(npc->poseId, 0x1800);                         \
            }                                                    \
        }                                                        \
    }                                                            \
    list = w->data->mobjs;                                       \
    if (list) {                                                  \
        for (; *list; list++) {                                  \
            MapObjectEntry* mobj = mobjNameToPtrNoAssert(*list); \
            if (mobj) {                                          \
                FN(mobj->poseId, 0x1800);                        \
            }                                                    \
        }                                                        \
    }                                                            \
    list = w->data->items;                                       \
    if (list) {                                                  \
        for (; *list; list++) {                                  \
            ItemEntry* item = itemNameToPtr((char*)*list);       \
            if (item) {                                          \
                ICONFN(item->name, DOOR_ITEM_DARK_FLAG);         \
            }                                                    \
        }                                                        \
    }                                                            \
    return EVT_RETURN_DONE;

/**
 * Keeps Mario, both partners and the house's listed NPCs,
 * map objects and items lit (exempt from the map blend) while house_in darkens the town.
 */
static USER_FUNC(npc_dark) {
    NPC_LIGHT_BODY(animPoseSetMaterialFlagOn, iconFlagOn)
}

/** Undoes npc_dark when Mario leaves the house, letting the map blend reach them again. */
static USER_FUNC(npc_light) {
    NPC_LIGHT_BODY(animPoseSetMaterialFlagOff, iconFlagOff)
}

/**
 * Returns entry args[1] of HouseData.noclip (map groups whose view culling is turned off while Mario is inside),
 * or -1 past the end of the list.
 */
static USER_FUNC(get_noclip_map) {
    EvtWord* args = event->args;
    HouseWork* w = (HouseWork*)evtGetValue(event, args[0]);
    s32 idx = evtGetValue(event, args[1]);
    const char** list = w->data->noclip;

    if (list && list[idx]) {
        evtSetValue(event, args[2], (EvtWord)list[idx]);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[2], -1);
    return EVT_RETURN_DONE;
}

#define DOOR_POS_GET(HIT)              \
    if (!mario) {                      \
        hitObjGetPos(HIT, &pos);       \
    } else {                           \
        pos = marioGetPtr()->position; \
    }                                  \
    hitObjGetNormal(HIT, &nrm);

/**
 * Works out where Mario stands outside (out) and inside (in) a door from the hit objects' positions and normals;
 * the outside spot is offset sideways by half the door map object's width according to the hinge side (type).
 * With mario set, Mario's own position replaces the hit positions. Only X and Z are written.
 */
void door_position_sub(s32 type, const char* map, const char* hitIn, const char* hitOut, Vec* in, Vec* out, BOOL mario) {
    Mtx inv;
    Mtx m;
    Vec pos;
    Vec nrm;
    Vec max;
    Vec min;
    Vec d;
    MapObject* obj = mapGetMapObj(map);
    f32 w = 10.0f;
    f32 a, b;
    f32 t;

    if (!mario) {
        a = 40.0f;
        b = 30.0f;
    } else {
        a = 50.0f;
        b = a;
    }
    if (obj) {
        PSMTXInverse(obj->transformMtx, inv);
        PSMTXConcat(obj->modelWorldMtx, inv, m);
        PSMTXMultVec(m, &obj->joints->bboxMin, &min);
        PSMTXMultVec(m, &obj->joints->bboxMax, &max);
        PSVECSubtract(&max, &min, &d);
        if (d.x) {
            t = d.x / (f32)cos((f32)atan(d.z / d.x));
            w = t / 2.0f;
        } else {
            w = d.z / 2.0f;
        }
        t = w;
        w = t;
    }
    switch (type) {
        case 0:
        case 1:
            if (hitOut) {
                DOOR_POS_GET(hitOut)
                out->x = pos.x + nrm.x * a - nrm.z * w;
                out->z = pos.z + nrm.z * a + nrm.x * w;
            } else {
                *out = marioGetPtr()->position;
            }
            if (hitIn) {
                DOOR_POS_GET(hitIn)
                in->x = pos.x + nrm.x * b;
                in->z = pos.z + nrm.z * b;
            } else {
                *in = marioGetPtr()->position;
            }
            break;
        case 2:
            if (hitOut) {
                DOOR_POS_GET(hitOut)
                out->x = pos.x + nrm.x * a + nrm.z * w;
                out->z = pos.z + nrm.z * a - nrm.x * w;
            } else {
                *out = marioGetPtr()->position;
            }
            if (hitIn) {
                DOOR_POS_GET(hitIn)
                in->x = pos.x + nrm.x * b;
                in->z = pos.z + nrm.z * b;
            } else {
                *in = marioGetPtr()->position;
            }
            break;
        case 3:
            if (hitOut) {
                DOOR_POS_GET(hitOut)
                out->x = pos.x + nrm.x * a;
                out->z = pos.z + nrm.z * a;
            } else {
                *out = marioGetPtr()->position;
            }
            if (hitIn) {
                DOOR_POS_GET(hitIn)
                in->x = pos.x + nrm.x * a;
                in->z = pos.z + nrm.z * a;
            } else {
                *in = marioGetPtr()->position;
            }
            break;
    }
}

#define DARK_SUB_BODY(FN, ICONFN)                                \
    if (mario) {                                                 \
        FN(mario->paperAnimGroupId[0], 0x1800);                  \
        FN(mario->paperAnimGroupId[1], 0x1800);                  \
        FN(mario->paperAnimGroupId[2], 0x1800);                  \
    }                                                            \
    if (party) {                                                 \
        FN(party->paperAnimGroup, 0x1800);                       \
    }                                                            \
    if (follower) {                                              \
        FN(follower->paperAnimGroup, 0x1800);                    \
    }                                                            \
    if (npcs) {                                                  \
        for (list = npcs; *list; list++) {                       \
            NpcEntry* npc = npcNameToPtr_NoAssert(*list);        \
            if (npc) {                                           \
                FN(npc->poseId, 0x1800);                         \
            }                                                    \
        }                                                        \
    }                                                            \
    if (mobjs) {                                                 \
        for (list = mobjs; *list; list++) {                      \
            MapObjectEntry* mobj = mobjNameToPtrNoAssert(*list); \
            if (mobj) {                                          \
                FN(mobj->poseId, 0x1800);                        \
            }                                                    \
        }                                                        \
    }                                                            \
    if (items) {                                                 \
        for (list = items; *list; list++) {                      \
            ItemEntry* item = itemNameToPtr((char*)*list);       \
            if (item) {                                          \
                ICONFN(item->name, DOOR_ITEM_DARK_FLAG);         \
            }                                                    \
        }                                                        \
    }

/**
 * Sets (on) or clears the no-blend material flags on Mario, both partners and the listed NPCs,
 * map objects and items, so they stay lit while the room around them is darkened.
 */
void door_dark_flag_sub(BOOL on, const char** npcs, const char** mobjs, const char** items) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    PartyEntry* follower = partyGetPtr(1);
    const char** list;

    if (on) {
        DARK_SUB_BODY(animPoseSetMaterialFlagOn, iconFlagOn)
    } else {
        DARK_SUB_BODY(animPoseSetMaterialFlagOff, iconFlagOff)
    }
}

/**
 * Script wrapper for door_dark_flag_sub: args[0] is the DoorParam (its npcs, mobjs and items lists),
 * args[1] turns the exemption on or off.
 */
USER_FUNC(door_dark_flag) {
    EvtWord* args = event->args;
    DoorParam* d = (DoorParam*)evtGetValue(event, args[0]);
    BOOL on = evtGetValue(event, args[1]);
    door_dark_flag_sub(on, d->npcs, d->mobjs, d->items);
    return EVT_RETURN_DONE;
}

#define DOOR_PARAM_POS(V, M)                                                  \
    door_position_sub(d->type, d->mapobj, d->hitIn, d->hitOut, &in, &out, M); \
    evtSetValue(event, args[2], V.x);                                         \
    evtSetValue(event, args[3], V.y);                                         \
    evtSetValue(event, args[4], V.z);

/**
 * Reads a field of the DoorParam in args[0] into args[2..];
 * args[1] picks it: 0 type, 1 map object and hits, 2 outside, 3 inside, 4/5 inside/outside standing spot,
 * 6 in/out/wall events, 7 open/close events, 8 sound set, 9 flags,
 * 10/11 the standing spots measured from Mario's position.
 */
USER_FUNC(evt_door_param) {
    EvtWord* args = event->args;
    DoorParam* d = (DoorParam*)evtGetValue(event, args[0]);
    s32 kind = evtGetValue(event, args[1]);
    Vec in = {0.0f, 0.0f, 0.0f};
    Vec out = {0.0f, 0.0f, 0.0f};

    switch (kind) {
        case 0:
            evtSetValue(event, args[2], d->type);
            break;
        case 1:
            evtSetValue(event, args[2], (EvtWord)d->mapobj);
            evtSetValue(event, args[3], (EvtWord)d->hitIn);
            evtSetValue(event, args[4], (EvtWord)d->hitOut);
            break;
        case 2:
            evtSetValue(event, args[2], (EvtWord)d->outside);
            evtSetValue(event, args[3], (EvtWord)d->outsideHit);
            break;
        case 3:
            evtSetValue(event, args[2], (EvtWord)d->inside);
            evtSetValue(event, args[3], (EvtWord)d->insideHit);
            break;
        case 4:
            DOOR_PARAM_POS(in, FALSE)
            break;
        case 5:
            DOOR_PARAM_POS(out, FALSE)
            break;
        case 6:
            evtSetValue(event, args[2], (EvtWord)d->evtIn);
            evtSetValue(event, args[3], (EvtWord)d->evtOut);
            evtSetValue(event, args[4], (EvtWord)d->evtWall);
            break;
        case 7:
            evtSetValue(event, args[2], (EvtWord)d->evtOpen);
            evtSetValue(event, args[3], (EvtWord)d->evtClose);
            break;
        case 8:
            evtSetValue(event, args[2], d->se);
            break;
        case 9:
            evtSetValue(event, args[2], d->flags);
            break;
        case 10:
            DOOR_PARAM_POS(in, TRUE)
            break;
        case 11:
            DOOR_PARAM_POS(out, TRUE)
            break;
    }
    return EVT_RETURN_DONE;
}

/**
 * Saves the flags of the map object named in args[0] into door_mapflag before a door changes them;
 * only one door's flags can be saved at a time.
 */
USER_FUNC(evt_door_save_mapflag) {
    const char* name = (const char*)evtGetValue(event, *event->args);
    MapObject* obj = mapGetMapObj(name);
    if (!obj) {
        mapErrorEntry(0, name);
        return EVT_RETURN_DONE;
    }
    door_mapflag = obj->flags;
    return EVT_RETURN_DONE;
}

/** Restores the flags saved by evt_door_save_mapflag onto the map object named in args[0]. */
USER_FUNC(evt_door_load_mapflag) {
    const char* name = (const char*)evtGetValue(event, *event->args);
    MapObject* obj = mapGetMapObj(name);
    if (!obj) {
        mapErrorEntry(0, name);
        return EVT_RETURN_DONE;
    }
    obj->flags = door_mapflag;
    return EVT_RETURN_DONE;
}

/**
 * Hides (args[1] on) or shows every NPC in the DoorParam's npcs list,
 * so NPCs on the other side of the door are only drawn while Mario is in their room.
 */
static USER_FUNC(npc_hide_onoff) {
    EvtWord* args = event->args;
    DoorParam* d = (DoorParam*)evtGetValue(event, args[0]);
    BOOL on = evtGetValue(event, args[1]);
    const char** list = d->npcs;
    s32 i;

    for (i = 0; list[i]; i++) {
        NpcEntry* npc = npcNameToPtr_NoAssert(list[i]);
        if (npc) {
            if (on) {
                npc->flags |= NPC_FLAG_NO_DISPLAY;
            } else {
                npc->flags &= ~NPC_FLAG_NO_DISPLAY;
            }
        }
    }
    return EVT_RETURN_DONE;
}

#if VERSION <= VERSION_DEMO_JP
/** the demo defines these with the door helpers at the end of the file */
static USER_FUNC(snd_door_in) {
    psndSetFlag(PSND_FLAG_MUTE_DOOR_SFX);
    return EVT_RETURN_DONE;
}

/** Clears PSND_FLAG_MUTE_DOOR_SFX after Mario walks back out. */
static USER_FUNC(snd_door_out) {
    psndClearFlag(PSND_FLAG_MUTE_DOOR_SFX);
    return EVT_RETURN_DONE;
}
#endif

/**
 * Copies the DoorParam in args[0] onto the map heap and returns the copy in args[1],
 * so a map can change it with evt_door_set_param (Rogueport, gor_01/gor_02).
 */
USER_FUNC(evt_door_data_copy) {
    EvtWord* args = event->args;
    DoorParam* src = (DoorParam*)evtGetValue(event, args[0]);
    DoorParam* dst = _mapAlloc(sizeof(DoorParam));
    *dst = *src;
    evtSetValue(event, args[1], (EvtWord)dst);
    return EVT_RETURN_DONE;
}

/**
 * Changes a field of a DoorParam: args[1] 0 replaces its npcs list with args[2]; other kinds do nothing.
 * Rogueport uses it to swap who is shown behind a door.
 */
USER_FUNC(evt_door_set_param) {
    EvtWord* args = event->args;
    DoorParam* d = (DoorParam*)evtGetValue(event, args[0]);
    s32 kind = evtGetValue(event, args[1]);
    EvtWord val = evtGetValue(event, args[2]);
    switch (kind) {
        case 0:
            d->npcs = (const char**)val;
            break;
    }
    return EVT_RETURN_DONE;
}

/** Blocks the calling script until no door open or close sequence is running (DoorFLAG is 0). */
USER_FUNC(evt_door_end_wait) {
    return DoorFLAG ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}
