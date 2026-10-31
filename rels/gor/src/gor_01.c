// gor_01 (ゴロツキタウン, Rogueport): central plaza. Badge shop, Zess T. ("nancy" in the code) and her cooking,
// star-stone scenes. Hub between the harbor and the east and west sides.

#include "eff/eff_starstone.h"
#include "eff/eff_mahojin.h"
#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "manager/evtmgr_cmd.h"
#include "driver/npcdrv.h"
#include "evt/evt_npc.h"
#include "mario/mario.h"
#include "system.h"
#include "manager/filemgr.h"
#include "parse.h"
#include "data/item_data.h"
#include "dolphin/gx.h"
#include "string.h"
#include "evt/evt_cmd.h"
#include "dolphin/mtx.h"
#include "driver/animdrv.h"
#include "driver/mobjdrv.h"
#include "driver/effdrv.h"
#include "stdio.h"
#include "driver/camdrv.h"
#include "memory.h"
#include "mario/mario_pouch.h"
#include "driver/swdrv.h"
#include "evt/evt_bero.h"
#include "evt/evt_door.h"
#include "evt/evt_hit.h"
#include "evt/evt_item.h"
#include "evt/evt_kinopio.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_case.h"
#include "evt/evt_sub.h"
#include "gor.h"
#include "evt/evt_shop.h"
#include "data_tables.h"
#include "driver/msgdrv.h"
#include "eff/eff_fire.h"
#include "eff/n64/eff_kemuri12_n64.h"
#include "evt/evt_badgeshop.h"
#include "evt/evt_bg.h"
#include "evt/evt_cam.h"
#include "evt/evt_eff.h"
#include "evt/evt_fade.h"
#include "evt/evt_lecture.h"
#include "evt/evt_map.h"
#include "evt/evt_msg.h"
#include "evt/evt_party.h"
#include "evt/evt_pouch.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_urouro.h"
#include "evt/evt_win.h"
#include "evt/evt_window.h"
#include "kpa_act.h"
#include "pmario_sound.h"
#include "statuswindow.h"
#include "evt/evt_johoya.h"
#include "libc_decls.h"
#include "driver/envdrv.h"
#include "driver/itemdrv.h"
#include "eff/eff_kemuri.h"
#include "mario/mariost.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"
#include "driver/casedrv.h"

typedef struct ShopSel {
    u8 head[8];
    s32* items;
#if VERSION <= VERSION_DEMO_US
    u8 listState[0x18 - 0xC];
#else
    u8 listState[0x24 - 0xC];
#endif
    s32 sel;
} ShopSel; /* head: u16 flags first (cleared by disp_off); listState: never accessed */
s32* iri_09_item_tbl;
static s32 item_tbl[21];

static USER_FUNC(anim_tevcallback);
static USER_FUNC(anim_tevcallback_mobj);
static USER_FUNC(chk_cook_msg);
static USER_FUNC(chk_special_cook);
static USER_FUNC(cooking_flag);
static USER_FUNC(delete_npc_regl_evt);
static USER_FUNC(disp_off);
static USER_FUNC(evt_StatusClose);
static USER_FUNC(evt_StatusOpen);
static USER_FUNC(evt_osreport);
static USER_FUNC(get_value);
static USER_FUNC(iri_09_item_tbl_alloc);
static USER_FUNC(iri_09_item_tbl_free);
static USER_FUNC(iri_09_item_tbl_make);
static USER_FUNC(mario_keyoff_wait);
static USER_FUNC(set_fook_evt);
static USER_FUNC(starstone_entry);
static USER_FUNC(starstone_set_pos);
static USER_FUNC(starstone_set_ry);
static USER_FUNC(wait_mahojin);
static USER_FUNC(yami_view);

s32 item_tbl_nancy[2];
extern EvtWord nancy_talk[];
extern EvtWord chusan1_naguru[];
NpcSetupInfo kickEnt[2];
NpcSetupInfo torqueEnt[2];
NpcSetupInfo kick2Ent[2];
static EvtWord borodo2_talk[280];
static const char* door_data_01_npc[2];
const char* door_data_01_item[2];
static DoorParam door_data_01;
DoorParam door_data_01_01;
const char* door_data_02_npc_01[2];
DoorParam door_data_02_f1;
DoorParam door_data_02_f1_01;
const char* badgemise_npc[3];
UnitWinSell uwnobj_list[6];
DoorParam door_data_02_f2;
extern EvtWord marco_hitorigoto[];
const char* door_data_03_item[2];
DoorParam door_data_03_f1;
DoorParam door_data_03_f2;
static DoorParam door_data_04;
ShopItem goods_list2[6];
ShopItem goods_luigi1[6];
ShopItem goods_luigi2[6];
ShopItem goods_luigi3[6];
ShopItem goods_luigi4[6];
ShopItem goods_luigi5[6];
static ShopperData35 shopper_data;
static KinopioData kino_dt;
extern EvtWord christine_nakama[];
extern EvtWord maffia_assault[];
extern EvtWord christine_nakama_after[];
extern EvtWord iri_09_tentyo_talk[];
s32 iri_16_item_tbl[2];
extern EvtWord iri_16_tyutyu_talk[];
#if VERSION >= VERSION_JP
SimpleRecipe R_simple_recipe_table[26];
CookRecipe R_cookbook_recipe_table[VERSION_PICK(289, 292)];
#endif
s32 naniga_okorukana_list[20];
s32 special_cook_list[16];
s32 iri_18_item_tbl[2];
extern EvtWord cooking_evt[];

#if VERSION >= VERSION_JP
/**
 * Returns in args[0] how many special badges the badge shop currently has in stock (U_badgeShop_SpecialCheck).
 * JP and later releases.
 */
USER_FUNC(badgeshop_special_cnt) {
    EvtWord* args = event->args;

    evtSetValue(event, args[0], U_badgeShop_SpecialCheck());
    return EVT_RETURN_DONE;
}
#endif

/**
 * Zess T.'s ("Nancy") position-blocking helper, setup half:
 * remembers her current z in LW float 10 and 11 as the line she stands on,
 * and (JP and later) makes her keep running her events when Mario leaves the screen.
 */
static USER_FUNC(nancy_block_init_func) {
    NpcEntry* npc = evtNpcNameToPtr(event, "ナンシー");
    f32 z;

    z = npc->position.z;
    event->lwDataF[10] = z;
    event->lwDataF[11] = z;
#if VERSION >= VERSION_JP
    npc->flags |= NPC_FLAG_RESUME_ON_LEAVE;
#endif
    return EVT_RETURN_DONE;
}

/**
 * Per-frame half of Zess T.'s blocking: when Mario is between 30 and 130 units away,
 * she slides along z (4 units per frame, within 40 units of her post) to stay level with him
 * so he cannot slip past into the gap.
 */
static USER_FUNC(nancy_block_func) {
    MarioWork* mario = marioGetPtr();
    NpcEntry* npc = evtNpcNameToPtr(event, "ナンシー");
    f32 z;
    f32 base;
    f32 limit;

    event->lwDataF[10] = npc->position.z;
    if (distABf(npc->position.x, npc->position.z, mario->position.x, mario->position.z) < 30.0f) {
        return EVT_RETURN_DONE;
    }
    if (distABf(npc->position.x, npc->position.z, mario->position.x, mario->position.z) > 130.0f) {
        return EVT_RETURN_DONE;
    }
    z = mario->position.z;
    base = event->lwDataF[11];
    limit = z;
    if (z > 40.0f + base) {
        limit = 40.0f + base;
    }
    if (z < base - 40.0f) {
        limit = base - 40.0f;
    }
    if (npc->position.z <= limit) {
        npc->position.z += 4.0f;
        if (npc->position.z > limit) {
            npc->position.z = limit;
        }
    }
    if (npc->position.z > limit) {
        npc->position.z -= 4.0f;
        if (npc->position.z <= limit) {
            npc->position.z = limit;
        }
    }
    return EVT_RETURN_DONE;
}

/**
 * Sets or clears bit 0 of the NPC work flags (args[0] nonzero sets it);
 * Trouble Center job 5 turns it on so the target NPC keeps reacting to Mario hitting it.
 */
static USER_FUNC(chusan1_alwaysencont) {
    EvtWord* args = event->args;
    NpcWork* wp = npcGetWorkPtr();

    if (evtGetValue(event, args[0])) {
        wp->flags |= 1;
    } else {
        wp->flags &= ~1;
    }
    return EVT_RETURN_DONE;
}

/** Forces the status window (HP/FP/coins) open on screen. */
static USER_FUNC(evt_StatusOpen) {
    statusWinForceOpen();
    return EVT_RETURN_DONE;
}

/** Closes the status window opened by evt_StatusOpen. */
static USER_FUNC(evt_StatusClose) {
    statusWinForceOff();
    return EVT_RETURN_DONE;
}

/** Clears the display bit of the 16-bit flags word at the address in args[0]; used to hide a shop menu window. */
static USER_FUNC(disp_off) {
    *(u16*)evtGetValue(event, event->args[0]) &= ~1;
    return EVT_RETURN_DONE;
}

/**
 * Reads the shop window selection at args[0] and returns, for the highlighted item:
 * its name (message or id) in args[1], its item id in args[2],
 * its discounted price in args[3] and its badge BP cost in args[4].
 */
static USER_FUNC(get_value) {
    EvtWord* args = event->args;
    ShopSel* wp = (ShopSel*)evtGetValue(event, args[0]);

#if VERSION >= VERSION_US
    evtSetValue(event, args[1], (s32)msgSearch(itemDataTable[wp->items[wp->sel]].name));
#else
    evtSetValue(event, args[1], (EvtWord)itemDataTable[wp->items[wp->sel]].id);
#endif
    evtSetValue(event, args[2], wp->items[wp->sel]);
    evtSetValue(event, args[3], itemDataTable[wp->items[wp->sel]].discount_price);
    evtSetValue(event, args[4], itemDataTable[wp->items[wp->sel]].bp_cost);
    return EVT_RETURN_DONE;
}

// FAKE: switch on a negated bool; the if/else and ?: forms of "yield while a key is held" compile differently.
static USER_FUNC(mario_keyoff_wait) {
    switch (!marioChkKey()) {
        default:
            return EVT_RETURN_BLOCK;
        case 0:
            return EVT_RETURN_YIELD;
    }
}

#if VERSION <= VERSION_DEMO_US
/** The demo's badge shop: each step is a new message from the clerk, and the coin window opens with each menu */
static EVT_BEGIN(sell_evt)
    CALL(evt_pouch_get_havebadgecnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("badgeshop_06"), 0, STRING("バッジ店員"))
        RETURN
    END_IF
    LABEL(0)
    CALL(evt_win_coin_on, 0, LW(12))
    CALL(evt_win_other_select, 12)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("badgeshop_22"), 0, STRING("バッジ店員"))
        CALL(evt_win_coin_off, LW(12))
        RETURN
    END_IF
    CALL(evt_msg_print_insert, 0, STRING("badgeshop_08"), 0, STRING("バッジ店員"), LW(2), LW(3))
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    CALL(evt_msg_continue)
    IF_INT_EQUAL(LW(0), 1)
        GOTO(0)
    END_IF
    CALL(evt_pouch_remove_item, LW(1), LW(0))
    CALL(evt_badgeShop_throw_inc, LW(1))
    CALL(evt_pouch_add_coin, LW(3))
    CALL(evt_win_coin_wait, LW(12))
    WAIT_MS(500)
    CALL(evt_win_coin_off, LW(12))
    CALL(evt_pouch_get_havebadgecnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("badgeshop_11"), 0, STRING("バッジ店員"))
        RETURN
    END_IF
    CALL(evt_msg_print, 0, STRING("badgeshop_10"), 0, STRING("バッジ店員"))
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    CALL(evt_msg_continue)
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print, 0, STRING("badgeshop_22"), 0, STRING("バッジ店員"))
        RETURN
    END_IF
    GOTO(0)
    RETURN
EVT_END()
#else
/**
 * The badge shop's sell menu in the US and later releases:
 * tells the clerk's line if Mario owns no badges (badgeshop_06),
 * otherwise opens the coin window and a badge picker (win_other_select 12).
 * Mario confirms the sale price (the item name and price go through the message formatter)
 * and the badge is removed from the pouch with N_evt_pouch_remove_item_index,
 * added to the shop's resale list (evt_badgeShop_throw_inc) and its price added as coins.
 * It repeats until he has no badges left or cancels.
 */
static EVT_BEGIN(sell_evt)
    CALL(evt_pouch_get_havebadgecnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_06"))
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("badgeshop_07"))
    CALL(evt_win_coin_on, 0, LW(8))
    LABEL(0)
    CALL(evt_win_other_select, 12)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("badgeshop_22"), 0, STRING("バッジ店員"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(evt_sub_get_language, LW(0))
#if VERSION >= VERSION_US
    // US and PAL: the item name and price go through the message formatter outside Japanese
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(evt_msg_print_insert, 0, STRING("badgeshop_08"), 0, STRING("バッジ店員"), LW(2), LW(3))
        CASE_DEFAULT
        CALL(evt_msg_fmt_int, 0, LW(14), STRING("badgeshop_08"), LW(3))
        CALL(evt_msg_fmt_str, 1, LW(14), LW(14), LW(2))
        CALL(evt_msg_print, 1, LW(14), 0, STRING("バッジ店員"))
    END_SWITCH
#else
    // JP and the demo: other languages swap the two inserted values
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_insert, 0, STRING("badgeshop_08"), 0, STRING("バッジ店員"), LW(3), LW(2))
    ELSE
        CALL(evt_msg_print_insert, 0, STRING("badgeshop_08"), 0, STRING("バッジ店員"), LW(2), LW(3))
    END_IF
#endif
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_09"))
        GOTO(0)
    END_IF
    CALL(N_evt_pouch_remove_item_index, LW(1), LW(4), LW(0))
    CALL(evt_badgeShop_throw_inc, LW(1))
    CALL(evt_pouch_add_coin, LW(3))
    CALL(evt_win_coin_wait, LW(8))
    WAIT_MS(500)
    CALL(evt_win_coin_off, LW(8))
    CALL(evt_pouch_get_havebadgecnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_11"))
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("badgeshop_10"))
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_22"))
        RETURN
    END_IF
    CALL(evt_msg_continue)
    CALL(evt_win_coin_on, 0, LW(8))
    GOTO(0)
    RETURN
EVT_END()
#endif

#if VERSION >= VERSION_US
/**
 * Badge shop purchase menu for the stock ("zaiko") of ordinary badges:
 * tells Mario when the shelves are empty, otherwise lets him pick a badge, checks his coins and badge room,
 * adds the badge and takes the price, and offers to buy more until he declines or the stock runs out.
 * The text formatting differs per release and language.
 */
EVT_BEGIN(zaiko_buy_evt)
    CALL(evt_badgeShop_throw_get_kind_cnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(badgeshop_special_cnt, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_add, 0, STRING("badgeshop_37"))
        ELSE
            CALL(evt_msg_print_add, 0, STRING("badgeshop_40"))
        END_IF
        RETURN
    END_IF
    CALL(evt_msg_continue)
    CALL(evt_win_coin_on, 0, LW(8))
    LABEL(0)
    CALL(evt_win_other_select, 11)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("badgeshop_22"), 0, STRING("バッジ店員"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(evt_sub_get_language, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(evt_msg_print_insert, 0, STRING("badgeshop_00"), 0, STRING("バッジ店員"), LW(2), LW(3), LW(4))
        CASE_DEFAULT
        CALL(evt_msg_fmt_int, 0, LW(14), STRING("badgeshop_00"), LW(3))
        CALL(evt_msg_fmt_str, 1, LW(14), LW(14), LW(2))
        CALL(evt_msg_print_insert, 1, LW(14), 0, STRING("バッジ店員"), LW(4))
    END_SWITCH
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_continue)
        GOTO(0)
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_LESS(LW(0), LW(3))
        CALL(evt_msg_print_add, 0, STRING("badgeshop_01"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(evt_pouch_add_item, LW(1), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_02"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(evt_badgeShop_throw_dec, LW(1))
    MULTIPLY(LW(3), -1)
    CALL(evt_pouch_add_coin, LW(3))
    CALL(evt_win_coin_wait, LW(8))
    WAIT_MS(500)
    CALL(evt_win_coin_off, LW(8))
    CALL(evt_badgeShop_throw_get_kind_cnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_11"))
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("badgeshop_38"))
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_22"))
        RETURN
    END_IF
    CALL(evt_msg_continue)
    CALL(evt_win_coin_on, 0, LW(8))
    GOTO(0)
    RETURN
EVT_END()
#elif VERSION >= VERSION_JP
/**
 * Badge shop purchase menu for the stock ("zaiko") of ordinary badges:
 * tells Mario when the shelves are empty, otherwise lets him pick a badge, checks his coins and badge room,
 * adds the badge and takes the price, and offers to buy more until he declines or the stock runs out.
 * The text formatting differs per release and language.
 */
EVT_BEGIN(zaiko_buy_evt)
    CALL(evt_badgeShop_throw_get_kind_cnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(badgeshop_special_cnt, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_add, 0, STRING("badgeshop_37"))
        ELSE
            CALL(evt_msg_print_add, 0, STRING("badgeshop_40"))
        END_IF
        RETURN
    END_IF
    CALL(evt_msg_continue)
    CALL(evt_win_coin_on, 0, LW(8))
    LABEL(0)
    CALL(evt_win_other_select, 11)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("badgeshop_22"), 0, STRING("バッジ店員"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(evt_sub_get_language, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_insert, 0, STRING("badgeshop_00"), 0, STRING("バッジ店員"), LW(3), LW(2), LW(4))
    ELSE
        CALL(evt_msg_print_insert, 0, STRING("badgeshop_00"), 0, STRING("バッジ店員"), LW(2), LW(3), LW(4))
    END_IF
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_continue)
        GOTO(0)
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_LESS(LW(0), LW(3))
        CALL(evt_msg_print_add, 0, STRING("badgeshop_01"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(evt_pouch_add_item, LW(1), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_02"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(evt_badgeShop_throw_dec, LW(1))
    MULTIPLY(LW(3), -1)
    CALL(evt_pouch_add_coin, LW(3))
    CALL(evt_win_coin_wait, LW(8))
    WAIT_MS(500)
    CALL(evt_win_coin_off, LW(8))
    CALL(evt_badgeShop_throw_get_kind_cnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_11"))
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("badgeshop_38"))
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_22"))
        RETURN
    END_IF
    CALL(evt_msg_continue)
    CALL(evt_win_coin_on, 0, LW(8))
    GOTO(0)
    RETURN
EVT_END()
#else
/**
 * Badge shop purchase menu for the stock ("zaiko") of ordinary badges:
 * tells Mario when the shelves are empty, otherwise lets him pick a badge, checks his coins and badge room,
 * adds the badge and takes the price, and offers to buy more until he declines or the stock runs out.
 * The text formatting differs per release and language.
 */
EVT_BEGIN(zaiko_buy_evt)
    CALL(evt_badgeShop_throw_get_kind_cnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("badgeshop_37"), 0, STRING("バッジ店員"))
        RETURN
    END_IF
    LABEL(0)
    CALL(evt_win_coin_on, 0, LW(12))
    CALL(evt_win_other_select, 11)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("badgeshop_22"), 0, STRING("バッジ店員"))
        CALL(evt_win_coin_off, LW(12))
        RETURN
    END_IF
    CALL(evt_msg_print_insert, 0, STRING("badgeshop_00"), 0, STRING("バッジ店員"), LW(2), LW(3), LW(4))
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    CALL(evt_msg_continue)
    IF_INT_EQUAL(LW(0), 1)
        GOTO(0)
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_LESS(LW(0), LW(3))
        CALL(evt_msg_print, 0, STRING("badgeshop_01"), 0, STRING("バッジ店員"))
        CALL(evt_win_coin_off, LW(12))
        RETURN
    END_IF
    CALL(evt_pouch_add_item, LW(1), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_msg_print, 0, STRING("badgeshop_02"), 0, STRING("バッジ店員"))
        CALL(evt_win_coin_off, LW(12))
        RETURN
    END_IF
    CALL(evt_badgeShop_throw_dec, LW(1))
    MULTIPLY(LW(3), -1)
    CALL(evt_pouch_add_coin, LW(3))
    CALL(evt_win_coin_wait, LW(12))
    WAIT_MS(500)
    CALL(evt_win_coin_off, LW(12))
    CALL(evt_badgeShop_throw_get_kind_cnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("badgeshop_11"), 0, STRING("バッジ店員"))
        RETURN
    END_IF
    CALL(evt_msg_print, 0, STRING("badgeshop_38"), 0, STRING("バッジ店員"))
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    CALL(evt_msg_continue)
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print, 0, STRING("badgeshop_22"), 0, STRING("バッジ店員"))
        RETURN
    END_IF
    GOTO(0)
    RETURN
EVT_END()
#endif

#if VERSION <= VERSION_DEMO_US
/**
 * The badge shop's buy menu in the demos and earlier:
 * the clerk greets (badgeshop_36) and Mario picks one of three choices:
 * 0 says badgeshop_05, 1 runs zaiko_buy_evt (the stock list) and 2 leaves with badgeshop_22.
 */
static EVT_BEGIN(buy_evt)
    CALL(evt_msg_print, 0, STRING("badgeshop_36"), 0, STRING("バッジ店員"))
    CALL(evt_msg_select, 0, STRING("badgeshop_35"))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(evt_msg_continue)
        CALL(evt_msg_print, 0, STRING("badgeshop_05"), 0, STRING("バッジ店員"))
        CASE_EQUAL(1)
        CALL(evt_msg_continue)
        CALL_CHILD(zaiko_buy_evt)
        CASE_EQUAL(2)
        CALL(evt_msg_continue)
        CALL(evt_msg_print, 0, STRING("badgeshop_22"), 0, STRING("バッジ店員"))
    END_SWITCH
    RETURN
EVT_END()
#else
/**
 * The badge shop's buy menu in the JP and later releases:
 * the greeting is appended to the open message window and Mario picks from three choices:
 * 0 closes with badgeshop_37 or _39 (no special stock; depends on whether the shop holds badges Mario sold)
 * or badgeshop_05, 1 runs zaiko_buy_evt (the stock list) and 2 leaves with badgeshop_22.
 */
static EVT_BEGIN(buy_evt)
    CALL(evt_msg_print_add, 0, STRING("badgeshop_36"))
    CALL(evt_msg_select, 0, STRING("badgeshop_35"))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(badgeshop_special_cnt, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_badgeShop_throw_get_kind_cnt, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_print_add, 0, STRING("badgeshop_37"))
            ELSE
                CALL(evt_msg_print_add, 0, STRING("badgeshop_39"))
            END_IF
        ELSE
            CALL(evt_msg_print_add, 0, STRING("badgeshop_05"))
        END_IF
        CASE_EQUAL(1)
        CALL_CHILD(zaiko_buy_evt)
        CASE_EQUAL(2)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_22"))
    END_SWITCH
    RETURN
EVT_END()
#endif

#if VERSION <= VERSION_DEMO_US
/** The clerk greets Mario on his first visit (GSWF_GOR01_BADGE_SHOP_FIRST_TALK) instead of opening the menu */
static EVT_BEGIN(first_shopping_evt)
    CALL(evt_msg_print, 0, STRING("badgeshop_30"), 0, STRING("バッジ店員"))
    RETURN
EVT_END()

/**
 * Talk event of the badge shop clerk: asks whether Mario wants to buy, sell or leave,
 * then runs buy_evt or sell_evt.
 * The demos greet Mario once on his first visit (GSWF_GOR01_BADGE_SHOP_FIRST_TALK) instead of showing the menu.
 */
EVT_BEGIN(badgeshopper_talk_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(unitwin_get_work_ptr, LW(10))
    IF_INT_EQUAL(GSWF(GSWF_GOR01_BADGE_SHOP_FIRST_TALK), 0)
        CALL_CHILD(first_shopping_evt)
        SET_VALUE(GSWF(GSWF_GOR01_BADGE_SHOP_FIRST_TALK), 1)
        CALL(evt_mario_key_onoff, 1)
        RETURN
    END_IF
    CALL(evt_msg_print, 0, STRING("badgeshop_04"), 0, STRING("バッジ店員"))
    CALL(evt_msg_select, 0, STRING("badgeshop_23"))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(evt_msg_continue)
        CALL_CHILD(buy_evt)
        CASE_EQUAL(1)
        CALL(evt_msg_continue)
        CALL_CHILD(sell_evt)
        CASE_EQUAL(2)
        CALL(evt_msg_continue)
        CALL(evt_msg_print, 0, STRING("badgeshop_22"), 0, STRING("バッジ店員"))
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
#else
/**
 * Talk event of the badge shop clerk: asks whether Mario wants to buy, sell or leave,
 * then runs buy_evt or sell_evt.
 * The demos greet Mario once on his first visit (GSWF_GOR01_BADGE_SHOP_FIRST_TALK) instead of showing the menu.
 */
EVT_BEGIN(badgeshopper_talk_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(unitwin_get_work_ptr, LW(10))
    CALL(evt_msg_print, 0, STRING("badgeshop_04"), 0, STRING("バッジ店員"))
    CALL(evt_msg_select, 0, STRING("badgeshop_23"))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL_CHILD(buy_evt)
        CASE_EQUAL(1)
        CALL_CHILD(sell_evt)
        CASE_EQUAL(2)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_22"))
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
#endif

/**
 * Init event of the badge shop owner: hides him below the map while Trouble Center job 16 is active or solved,
 * and while Mario is in Glitzville (Chapter 3, up to Ms. Mowz).
 */
EVT_BEGIN(badgemaster_init)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 16)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_TROUBLE_16_SOLVED), 1)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_00_WELCOME_TO_GLITZVILLE)
        IF_INT_LESS_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_08_MS_MOWZ)
            CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        END_IF
    END_IF
    RETURN
EVT_END()

/** Talk event of the badge shop owner: one line per story stage (gor_01_024_00 to gor_01_024_08). */
EVT_BEGIN(badgemaster_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("gor_01_024_00"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_024_01"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_024_02"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("gor_01_024_03"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("gor_01_024_04"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("gor_01_024_05"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_024_06"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_024_07"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_024_08"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/** Init event of the old Toad ("kinoji"): empty. */
EVT_BEGIN(kinoji_init)
    RETURN
EVT_END()

/** Talk event of the old Toad: one line per story stage (gor_01_019 to gor_01_019_08). */
EVT_BEGIN(kinoji_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("gor_01_019"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_019_01"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_019_02"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("gor_01_019_03"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("gor_01_019_04"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("gor_01_019_05"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_019_06"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_019_07"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_019_08"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * Watches for Mario walking up to Zess T. ("Nancy") in the western alley before the contact lens quest:
 * when he enters the box near x -580 to -400 she stops pacing
 * and the first scene runs (gor_01_000 to gor_01_007), where she turns away, Mario bumps into her,
 * her glasses break and she ends up blocking the way. Sets GSWF_GOR01_ZESS_BLOCKS_GATE.
 */
EVT_BEGIN(nancy_init_check)
    CALL(evt_npc_change_interrupt, STRING("me"), 6, 0)
    // Wait until Mario walks into the alley zone in front of Zess T.
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
        SET_VALUE(LW(3), 0)
#if VERSION <= VERSION_DEMO_US
        IF_INT_GREATER(LW(10), -575)
#else
        IF_INT_GREATER(LW(10), -580)
#endif
            IF_INT_LESS(LW(10), -400)
                IF_INT_GREATER(LW(11), -10)
                    IF_INT_LESS(LW(11), 5)
                        IF_INT_GREATER(LW(12), 0)
                            IF_INT_LESS(LW(12), 180)
                                SET_VALUE(LW(3), 1)
                            END_IF
                        END_IF
                    END_IF
                END_IF
            END_IF
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(3), 1)
            BREAK_LOOP
        END_IF
    END_LOOP
    // Mario's controls are taken; Zess T. stops pacing and everyone turns to face her.
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_npc_get_reglid, STRING("ナンシー"), LW(0))
    DELETE_EVENT(LW(0))
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
        CALL(evt_mario_set_dir_npc, STRING("ナンシー"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
        CALL(evt_party_wait_landon, 0)
        CALL(evt_party_stop, 0)
        CALL(evt_party_set_dir_npc, 0, STRING("ナンシー"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(100)
        CALL(evt_party_wait_landon, 1)
        CALL(evt_party_stop, 1)
        CALL(evt_party_set_dir_npc, 1, STRING("ナンシー"))
    END_INLINE_EVENT
    // She yells at them to freeze.
    CALL(evt_msg_print, 0, STRING("gor_01_000"), 0, STRING("me"))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), LW(2))
    ADD(LW(1), 335)
    ADD(LW(2), -8)
    IF_INT_LESS_OR_EQUAL(LW(0), -520)
        SET_VALUE(LW(0), -520)
    END_IF
    CALL(evt_cam3d_evt_set, LW(0), 99, LW(1), LW(0), 39, LW(2), 500, 11)
    WAIT_MS(800)
    SET_VALUE(LW(3), 90)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    IF_INT_GREATER(LW(0), LW(10))
        ADD(LW(3), 180)
    END_IF
    CALL(evt_npc_set_ry, STRING("me"), LW(3))
    // She orders them not to move: someone bumped into her and she lost a contact lens. She paces and keeps
    // hissing the order.
    CALL(evt_msg_print, 0, STRING("gor_01_001"), 0, STRING("me"))
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(700)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING("gor_01_002"), 0, STRING("me"))
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(700)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(700)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(700)
    CALL(evt_npc_reverse_ry, STRING("me"))
    WAIT_MS(800)
    CALL(evt_msg_print, 0, STRING("gor_01_003"), 0, STRING("me"))
    WAIT_MS(300)
    CALL(evt_npc_restart_regular_event, STRING("me"))
    CALL(evt_cam3d_evt_off, 800, 11)
    WAIT_MS(800)
    // Control returns to Mario, who is expected to stay put; the script waits until he takes a step or one
    // second passes.
    CALL(evt_mario_key_onoff, 1)
#if VERSION >= VERSION_US
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
#endif
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            IF_INT_GREATER_OR_EQUAL(LW(0), -400)
                BREAK_LOOP
            END_IF
            IF_INT_LESS_OR_EQUAL(LW(0), -550)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    WAIT_WHILE(GF(0))
    LOOP(0)
        CALL(evt_mario_get_state, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(60)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_normalize)
    CALL(evt_mario_wait_landon)
#if VERSION >= VERSION_JP
    // Guess: if a partner is still in use, wait for that to finish before Mario resumes his normal pose.
    CALL(evt_mario_get_party, LW(0))
    IF_INT_EQUAL(LW(0), 5)
        LOOP(0)
            CALL(evt_mario_party_use_check, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_mario_set_pose, STRING("M_S_1"))
    END_IF
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    // Mario steps on the lens: it breaks with a squish.
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG0_LENS_BREAK1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("gor_01_004"), 0, 0)
    CALL(evt_npc_get_reglid, STRING("me"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), LW(2))
    ADD(LW(1), 250)
    ADD(LW(2), 30)
    IF_INT_LESS_OR_EQUAL(LW(0), -500)
        SET_VALUE(LW(0), -500)
    END_IF
    CALL(evt_cam3d_evt_set, LW(0), 80, LW(1), LW(0), 40, LW(2), 500, 11)
    WAIT_MS(400)
    CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
    // Zess T. screams that Mario crushed her lens and storms toward him.
    CALL(evt_msg_print, 0, STRING("gor_01_005"), 0, STRING("me"))
    CALL(evt_mario_set_dir_npc, STRING("me"))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
    IF_INT_LESS(LW(0), LW(10))
        IF_INT_LESS(LW(10), -550)
            GOTO(100)
        END_IF
        SUBTRACT(LW(10), 30)
        CALL(evt_npc_set_ry, STRING("me"), 90)
    ELSE
        LABEL(100)
        ADD(LW(10), 30)
        CALL(evt_npc_set_ry, STRING("me"), 270)
    END_IF
    WAIT_FRAMES(1)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_move_position, STRING("me"), LW(10), LW(12), 0, FLOAT(180.0f), 0)
    CALL(evt_mario_set_dir_npc, STRING("me"))
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
    IF_INT_LESS(LW(0), LW(10))
        CALL(evt_npc_set_ry, STRING("me"), 90)
    ELSE
        CALL(evt_npc_set_ry, STRING("me"), 270)
    END_IF
    WAIT_MS(300)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NO1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_B"))
    WAIT_MS(800)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    WAIT_MS(200)
    // She blames Mario and demands he pay for a new lens while he cowers.
    CALL(evt_msg_print, 0, STRING("gor_01_006"), 0, STRING("me"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NO1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_C"))
    WAIT_MS(400)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    WAIT_MS(400)
    CALL(evt_npc_set_ry, STRING("me"), 270)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    SET_VALUE(GF(0), 0)
    IF_INT_LESS_OR_EQUAL(LW(0), -540)
        SET_VALUE(GF(0), 1)
        BEGIN_INLINE_EVENT
            CALL(evt_mario_mov_pos2, -530, LW(2), FLOAT(180.0f))
            SET_VALUE(GF(0), 0)
            CALL(evt_mario_set_dir, 270, 200, 0)
        END_INLINE_EVENT
    END_IF
    // She walks back to the alley's west end to block the way.
    CALL(evt_npc_move_position, STRING("me"), -573, 56, 0, FLOAT(180.0f), 0)
    WAIT_WHILE(GF(0))
    CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_set_ry, STRING("me"), 90)
    WAIT_MS(300)
    // She announces she will block the west gate until Mario brings her a new contact lens.
    CALL(evt_msg_print, 0, STRING("gor_01_007"), 0, STRING("me"))
    CALL(evt_npc_restart_regular_event, STRING("me"))
    CALL(evt_npc_change_interrupt, STRING("me"), 6, PTR(nancy_talk))
    CALL(evt_cam3d_evt_off, 0, 11)
#if VERSION <= VERSION_JP
    CALL(evt_party_run, 0)
    CALL(evt_party_run, 1)
#endif
    CALL(evt_mario_key_onoff, 1)
    // Story flag set: the gate to the west side is now blocked.
    SET_VALUE(GSWF(GSWF_GOR01_ZESS_BLOCKS_GATE), 1)
    RETURN
EVT_END()

/**
 * Init event of Zess T. ("Nancy"): before the lens is delivered she paces near (-500, 0, 75)
 * and the check event is started; once she blocks the gate she stands at (-573, 0, 56);
 * after the lens is delivered she stands at her door at (-405, 10, -100).
 * Also switches the west exit "w_bero" off while she blocks.
 */
EVT_BEGIN(nancy_init)
    SET_VALUE(LSWF(1), 0)
    IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_DELIVERED), 0)
        IF_INT_EQUAL(GSWF(GSWF_GOR01_ZESS_BLOCKS_GATE), 0)
            CALL(evt_npc_set_ry, STRING("me"), 270)
            CALL(evt_npc_set_position, STRING("me"), -500, 0, 75)
            SPAWN_EVENT(nancy_init_check)
        ELSE
            CALL(evt_npc_set_ry, STRING("me"), 90)
            CALL(evt_npc_set_position, STRING("me"), -573, 0, 56)
        END_IF
        SET_VALUE(LW(0), STRING("w_bero"))
        CALL_CHILD(bero_case_switch_off)
        CALL(evt_hitobj_attr_onoff, 1, 0, STRING("w_bero"), 8388612)
    ELSE
        CALL(evt_npc_set_ry, STRING("me"), 270)
        CALL(evt_npc_set_position, STRING("me"), -405, 10, -100)
    END_IF
    RETURN
EVT_END()

/**
 * Animation of Zess T.'s front door ("S_ie_01_doa") opening to 108 degrees and closing again over a second,
 * with door sounds and its interior hidden; clears GF(0) when done.
 */
EVT_BEGIN(nancy_door_anime)
    CALL(evt_mapobj_get_position, STRING("S_ie_01_naka"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_ie_01_naka"), MAPOBJ_FLAG_HIDE)
    CALL(evt_sub_intpl_msec_init, 11, 0, 108, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        CALL(evt_mapobj_rotate, 1, STRING("S_ie_01_doa"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(500)
    CALL(evt_sub_intpl_msec_init, 11, 108, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        CALL(evt_mapobj_rotate, 1, STRING("S_ie_01_doa"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mapobj_get_position, STRING("S_ie_01_naka"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_ie_01_naka"), MAPOBJ_FLAG_HIDE)
    SET_VALUE(GF(0), 0)
    RETURN
EVT_END()

/**
 * Regular event of Zess T.: before the story step she wanders around (-500, 75);
 * while she blocks the gate (lens not delivered) she keeps following Mario with nancy_block_func every frame.
 */
EVT_BEGIN(nancy_regl)
    IF_INT_EQUAL(GSWF(GSWF_GOR01_ZESS_BLOCKS_GATE), 0)
        IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_DELIVERED), 0)
            CALL(urouro_init_func, STRING("me"), -500, 75, FLOAT(50.0f), FLOAT(45.0f), 0)
            CALL(urouro_main_func, STRING("me"))
        END_IF
    ELSE
        IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_DELIVERED), 0)
            CALL(nancy_block_init_func)
            LOOP(0)
                CALL(nancy_block_func)
                WAIT_FRAMES(1)
            END_LOOP
        END_IF
    END_IF
    RETURN
EVT_END()

/** Items offered in the item menu when giving Zess T. something: only the Contact Lens. */
s32 item_tbl_nancy[] = {
    ITEM_CONTACT_LENS, -1,
};

/**
 * Talk event of Zess T. Before the contact lens is delivered,
 * Mario can hand over a Contact Lens (the item list item_tbl_nancy);
 * she then thanks him, walks into her house, the west exit opens and GSWF_GOR01_LENS_DELIVERED is set.
 * After that talking to her runs cooking_evt.
 */
EVT_BEGIN(nancy_talk)
    IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_DELIVERED), 0)
        CALL(evt_pouch_check_item, ITEM_CONTACT_LENS, LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(0), 1)
            CALL(evt_msg_print, 0, STRING("gor_01_008"), 0, STRING("me"))
#if VERSION <= VERSION_DEMO_US
            CALL(evt_win_item_select, PTR(item_tbl_nancy), LW(1))
#else
            CALL(evt_win_item_select, 0, PTR(item_tbl_nancy), LW(1), 0)
#endif
            IF_INT_EQUAL(LW(1), -1)
                SET_VALUE(LW(0), 0)
            END_IF
        END_IF
        IF_INT_LESS(LW(0), 1)
            CALL(evt_mario_set_pose, STRING("M_N_B"))
            WAIT_MS(800)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            WAIT_MS(200)
            CALL(evt_msg_print, 0, STRING("gor_01_009"), 0, STRING("me"))
        ELSE
            CALL(evt_npc_get_reglid, STRING("me"), LW(10))
            DELETE_EVENT(LW(10))
            WAIT_MS(500)
            CALL(evt_npc_reverse_ry, STRING("me"))
            WAIT_MS(700)
            CALL(evt_npc_reverse_ry, STRING("me"))
            WAIT_MS(1000)
            CALL(evt_pouch_remove_item, ITEM_CONTACT_LENS, LW(0))
            CALL(evt_msg_print, 0, STRING("gor_01_010"), 0, STRING("me"))
            CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
            CALL(evt_npc_set_ry, STRING("me"), 90)
            CALL(evt_npc_move_position, STRING("me"), -380, 50, 0, FLOAT(120.0f), 0)
            CALL(evt_npc_jump_position_nohit, STRING("me"), -380, 10, 20, 200, 30)
            CALL(evt_npc_set_ry, STRING("me"), 270)
            WAIT_MS(60)
            CALL(evt_msg_print, 0, STRING("gor_01_011"), 0, STRING("me"))
            WAIT_MS(500)
            SET_VALUE(GF(0), 1)
            SPAWN_EVENT(nancy_door_anime)
            WAIT_MS(500)
            CALL(evt_npc_move_position, STRING("me"), -370, -30, 0, FLOAT(80.0f), 0)
            WAIT_WHILE(GF(0))
#if VERSION <= VERSION_JP
            CALL(evt_npc_set_position, STRING("me"), -455, 10, -170)
#else
            CALL(evt_npc_set_position, STRING("me"), -405, 10, -100)
#endif
            CALL(evt_npc_set_ry, STRING("me"), 270)
            CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
            SET_VALUE(LW(0), STRING("w_bero"))
            CALL_CHILD(bero_case_switch_on)
            CALL(evt_hitobj_attr_onoff, 1, 1, STRING("w_bero"), 8388612)
            SET_VALUE(GSWF(GSWF_GOR01_LENS_DELIVERED), 1)
            CALL(evt_door_set_param, GW(6), 0, PTR(&door_data_01_npc))
        END_IF
    ELSE
        CALL_CHILD(cooking_evt)
    END_IF
    RETURN
EVT_END()

/**
 * Init event of Flavio (Marco) in the central plaza:
 * from STORY_STG4_32_CHATTING_WITH_FLAVIO to STORY_STG5_59_ROGUEPORT_DOCK he is not here (he is at the harbor)
 * and is moved below the map.
 */
static EVT_BEGIN(marco_init)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG4_32_CHATTING_WITH_FLAVIO, STORY_STG5_59_ROGUEPORT_DOCK)
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Talk event of Flavio (Marco) in the plaza.
 * Before Frankly's house in Chapter 4 he says mac_4_005
 * and goes back to muttering to himself (marco_hitorigoto).
 * At STORY_STG4_31_FRANKLYS_HOUSE Mario and Flavio have the long talk (mac_4_007 to mac_4_023):
 * the camera frames them, Mario answers a question,
 * Flavio hands over the Magical Map (ITEM_MAGICAL_MAP_LARGE) and talks about the Skull Gem,
 * and the story advances to STORY_STG4_32_CHATTING_WITH_FLAVIO. Later stages only give short lines.
 */
static EVT_BEGIN(marco_talk)
    DELETE_EVENT(GW(0))
    CALL(evt_msg_close, STRING("mac_4_004"))
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG4_31_FRANKLYS_HOUSE)
        // Before Frankly's house: Flavio is startled, introduces himself and goes back to muttering to himself.
        CALL(evt_msg_print, 0, STRING("mac_4_005"), 0, STRING("me"))
        SET_VALUE(GSWF(GSWF_GOR01_FLAVIO_FIRST_TALK), 1)
        SPAWN_EVENT_GET_ID(PTR(marco_hitorigoto), GW(0))
        CASE_EQUAL(STORY_STG4_31_FRANKLYS_HOUSE)
        // Chapter 4 after Frankly's house: Mario and Flavio have the long talk. The camera frames them.
        CALL(evt_mario_dispflag_onoff, 1, 2)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        ADD(LW(0), LW(10))
        DIVIDE(LW(0), 2)
        CALL(evt_cam3d_evt_set, LW(0), 92, 128, LW(0), 40, -168, 500, 11)
        WAIT_MS(500)
        IF_INT_EQUAL(GSWF(GSWF_GOR01_FLAVIO_FIRST_TALK), 0)
            // Flavio introduces himself as a trader and asks Mario what he longs for in life; the answer only
            // changes his reply.
            CALL(evt_msg_print, 0, STRING("mac_4_007"), 0, STRING("me"))
        ELSE
            CALL(evt_msg_print, 0, STRING("mac_4_008"), 0, STRING("me"))
        END_IF
        CALL(evt_msg_select, 0, STRING("mac_4_007_select"))
        CALL(evt_mario_dispflag_onoff, 0, 2)
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(evt_msg_print_add, 0, STRING("mac_4_009"))
            CASE_EQUAL(1)
            CALL(evt_msg_print_add, 0, STRING("mac_4_010"))
            CASE_EQUAL(2)
            CALL(evt_msg_print_add, 0, STRING("mac_4_011"))
            CASE_EQUAL(3)
            CALL(evt_msg_print_add, 0, STRING("mac_4_012"))
        END_SWITCH
        // Flavio walks along the plaza, musing; the partner and Mario step up to him.
        CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
        CALL(evt_mario_get_pos, 0, LW(10), LW(11), LW(12))
        CALL(evt_npc_get_position, STRING("me"), LW(3), LW(1), LW(2))
        SET_VALUE(LW(11), LW(3))
        SET_VALUE(LW(12), LW(3))
        CALL(evt_npc_set_ry, STRING("me"), 270)
        SUBTRACT(LW(11), 70)
        SUBTRACT(LW(12), 50)
        CALL(evt_cam3d_evt_set, LW(11), 63, 152, LW(11), 45, -169, 1000, 11)
        BEGIN_INLINE_EVENT
            CALL(evt_party_move_pos2, 0, 215, -160, FLOAT(120.0f))
            CALL(evt_party_set_dir_npc, 0, STRING("me"))
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            CALL(evt_mario_mov_pos2, 250, -160, FLOAT(100.0f))
            CALL(evt_mario_set_dir_npc, STRING("me"))
        END_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("me"), LW(12), LW(2), 0, FLOAT(40.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING("me"))
        WAIT_MS(700)
        // Flavio is struck by the legend of Cortez's treasure on Keelhaul Key and decides to find it.
        CALL(evt_msg_print, 0, STRING("mac_4_013"), 0, STRING("me"))
        WAIT_MS(500)
        CALL(evt_npc_reverse_ry, STRING("me"))
        WAIT_MS(700)
        CALL(evt_msg_print, 0, STRING("mac_4_014"), 0, STRING("me"))
        WAIT_MS(500)
        CALL(evt_npc_reverse_ry, STRING("me"))
        WAIT_MS(1000)
        CALL(evt_msg_print, 0, STRING("mac_4_015"), 0, STRING("me"))
        CALL(evt_mario_set_pose, STRING("M_I_2"))
        WAIT_MS(800)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_npc_reverse_ry, STRING("me"))
        // Flavio asks about Mario's own treasure hunt and first brushes it off.
        CALL(evt_msg_print, 0, STRING("mac_4_016"), 0, STRING("me"))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_2"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_N_2"))
        WAIT_MS(800)
        CALL(evt_msg_print, 0, STRING("mac_4_017"), 0, STRING("me"))
        CALL(evt_mario_set_pose, STRING("M_I_2"))
        WAIT_MS(800)
        // Mario shows the treasure map; Flavio grabs it and recognises the way to Keelhaul Key.
        CALL(evt_msg_print, 0, STRING("mac_4_018"), 0, STRING("me"))
        CALL(evt_mario_set_pose, STRING("M_C_3"))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(0), 20)
        ADD(LW(1), 20)
        ADD(LW(2), 10)
        CALL(evt_item_entry, STRING("map00"), ITEM_MAGICAL_MAP_LARGE, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED, -1, 0)
        CALL(evt_item_flag_on, STRING("map00"), ITEM_FLAG_NO_TOUCH)
        CALL(evt_item_set_scale, STRING("map00"), FLOAT(0.5498047f))
        WAIT_MS(500)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        SET_VALUE(LW(3), LW(0))
        ADD(LW(3), -10)
        CALL(evt_npc_move_position, STRING("me"), LW(3), LW(2), 0, FLOAT(80.0f), 0)
        WAIT_MS(1000)
        // Flavio accuses Mario of stealing his treasure, then calms down when Mario explains the Crystal Stars.
        CALL(evt_msg_print, 0, STRING("mac_4_019"), 0, STRING("me"))
        CALL(evt_item_delete, STRING("map00"))
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_npc_move_position, STRING("me"), LW(0), LW(2), 0, FLOAT(40.0f), 0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NO1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_N_B"))
        WAIT_MS(1000)
        CALL(evt_mario_set_pose, STRING("M_I_2"))
        WAIT_MS(800)
        CALL(evt_msg_print, 0, STRING("mac_4_020"), 0, STRING("me"))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_N_2"))
        WAIT_MS(800)
        // Flavio hears there is no ship, laughs, then eagerly volunteers to lead the expedition.
        CALL(evt_msg_print, 0, STRING("mac_4_021"), 0, STRING("me"))
        CALL(evt_mario_set_pose, STRING("M_I_2"))
        WAIT_MS(800)
        CALL(evt_msg_print, 0, STRING("mac_4_022"), 0, STRING("me"))
        CALL(evt_mario_set_pose, STRING("M_N_2"))
        WAIT_MS(800)
        CALL(evt_msg_print, 0, STRING("mac_4_023"), 0, STRING("me"))
        CALL(evt_npc_set_ry, STRING("me"), 90)
        WAIT_MS(500)
        // The Skull Gem is taken from Mario and Flavio hurries off; he leaves the plaza.
        CALL(evt_del_case_evt, 0, GW(8))
        CALL(evt_item_delete, STRING("ドクロジュエル"))
        WAIT_MS(500)
        CALL(evt_npc_set_ry, STRING("me"), 270)
        WAIT_MS(500)
        CALL(evt_cam3d_evt_off, 500, 11)
        BEGIN_INLINE_EVENT
            CALL(evt_npc_move_position, STRING("me"), 260, -100, 0, FLOAT(120.0f), 0)
            CALL(evt_npc_move_position, STRING("me"), 110, -100, 0, FLOAT(120.0f), 0)
            CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        END_INLINE_EVENT
        WAIT_MS(3000)
        // Story advances: the expedition to Keelhaul Key is being arranged.
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG4_32_CHATTING_WITH_FLAVIO)
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        // Later stages: Flavio only has a short line.
        CALL(evt_msg_print, 0, STRING("gor_01_031_08_1"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_031_08_2"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_031_08_3"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_031_08_4"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * Init event of the bar owner (Podley, "master"):
 * during Professor Frankly's house step (STORY_STG4_31) he stands at (259, 0, -275).
 */
EVT_BEGIN(master_init)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG4_31_FRANKLYS_HOUSE)
        CALL(evt_npc_set_position, STRING("me"), 259, 0, -275)
    END_IF
    RETURN
EVT_END()

/**
 * Waits until Mario is 100 units or more away from the bar owner,
 * then makes him mutter irai_20_030 (Trouble Center job 20).
 */
EVT_BEGIN(iri_20_master_tubuyaki)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_npc_get_position, STRING("マスター"), LW(3), LW(4), LW(5))
        CALL(evt_sub_get_dist, LW(0), LW(2), LW(3), LW(5), LW(6))
        IF_INT_GREATER_OR_EQUAL(LW(6), 100)
            CALL(evt_msg_print, 0, STRING("irai_20_030"), 0, STRING("マスター"))
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Talk event of the bar owner (Podley).
 * Handles Trouble Center jobs 20 and 25, then by story: before Chapter 4 a line per stage;
 * after Admiral Bobbery's refusal (STORY_STG4_34) he tells Mario the story of Bobbery and, if Mario wants,
 * gives him the Old Letter and advances to STORY_STG4_35_ADVICE_FROM_PODLEY; afterwards a line per stage.
 */
EVT_BEGIN(master_talk)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 20)
        // Trouble Center job 20: Mario asks Podley about Eve; he is startled, then mutters a message for her.
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
        ELSE
            IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_1), 0)
                CALL(evt_msg_print, 0, STRING("irai_20_027"), 0, STRING("me"))
                CALL(evt_mario_set_pose, STRING("M_I_2"))
                WAIT_MS(1000)
                CALL(evt_mario_set_pose, STRING("M_S_1"))
                CALL(evt_cam3d_evt_set, 320, 99, -12, 322, 43, -271, 1000, 11)
                WAIT_MS(1000)
                CALL(evt_msg_print, 0, STRING("irai_20_028"), 0, STRING("me"))
                CALL(evt_mario_set_pose, STRING("M_N_5B"))
                WAIT_MS(500)
                CALL(evt_cam3d_evt_off, 1000, 11)
                WAIT_MS(1000)
                CALL(evt_msg_print, 0, STRING("irai_20_029"), 0, STRING("me"))
                SPAWN_EVENT(iri_20_master_tubuyaki)
                SET_VALUE(GSWF(GSWF_TROUBLE_WORK_1), 1)
                RETURN
            ELSE
                CALL(evt_msg_print, 0, STRING("irai_20_031"), 0, STRING("me"))
                RETURN
            END_IF
        END_IF
    END_IF
    // Trouble Center job 25: Podley says General White was just here.
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 25)
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_1), 1)
            IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_3), 0)
                CALL(evt_msg_print, 0, STRING("irai_25_00_1"), 0, 0)
                SET_VALUE(GSWF(GSWF_TROUBLE_WORK_2), 1)
                RETURN
            END_IF
        END_IF
    END_IF
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS_OR_EQUAL(STORY_STG4_32_CHATTING_WITH_FLAVIO)
        // Normal talk by story progress: early lines, then Bobbery's house is revealed once Mario meets him.
        CALL(evt_msg_print, 0, STRING("gor_01_016"), 0, STRING("me"))
        CASE_LESS_OR_EQUAL(STORY_STG4_33_MEET_BOBBERY)
        CALL(evt_msg_print, 0, STRING("mac_4_047"), 0, STRING("me"))
        SET_VALUE(GSWF(GSWF_GOR_BOBBERY_HOUSE_KNOWN), 1)
        CASE_EQUAL(STORY_STG4_34_BOBBERY_DECLINES)
        // After Bobbery declines the voyage: Mario and the partner step up to Podley's bar.
        SET_VALUE(GF(5), 0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_LESS(LW(0), 320)
            SET_VALUE(GF(5), 1)
        END_IF
        IF_INT_EQUAL(GF(5), 1)
            BEGIN_INLINE_EVENT
                CALL(evt_party_move_pos2, 0, 270, -275, FLOAT(150.0f))
                CALL(evt_party_set_dir, 0, 90, 0)
            END_INLINE_EVENT
            CALL(evt_mario_mov_pos2, 295, -270, FLOAT(150.0f))
            CALL(evt_mario_set_dir, 90, 0, 0)
        ELSE
            BEGIN_INLINE_EVENT
                CALL(evt_party_move_pos2, 0, 370, -275, FLOAT(150.0f))
                CALL(evt_party_set_dir, 0, 270, 0)
            END_INLINE_EVENT
            CALL(evt_mario_mov_pos2, 345, -270, FLOAT(150.0f))
            CALL(evt_mario_set_dir, 270, 0, 0)
        END_IF
        // If Podley already told the tale, he only asks again whether they want Bobbery back on the sea.
        IF_INT_EQUAL(GSWF(GSWF_GOR01_PODLEY_BOBBERY_TALE_DONE), 1)
            CALL(evt_snd_bgmoff_f, PSND_FADE_HOLD, 2000)
            CALL(evt_msg_print, 0, STRING("mac_4_071"), 0, STRING("me"))
            GOTO(100)
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_GOR01_PODLEY_BOBBERY_TALE_OFFERED), 0)
            // Podley asks if they really want Bobbery on the water and offers to tell his sad tale.
            CALL(evt_msg_print, 0, STRING("mac_4_061"), 0, STRING("me"))
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_5"), LW(0), LW(1), LW(2), 0)
            CALL(evt_mario_set_pose, STRING("M_N_2"))
            WAIT_MS(800)
            CALL(evt_mario_set_pose, STRING("M_I_2"))
            WAIT_MS(800)
            CALL(evt_msg_print, 0, STRING("mac_4_062"), 0, STRING("me"))
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            WAIT_MS(2000)
            CALL(evt_msg_print, 0, STRING("mac_4_063"), 0, STRING("me"))
            SET_VALUE(GSWF(GSWF_GOR01_PODLEY_BOBBERY_TALE_OFFERED), 1)
        ELSE
            CALL(evt_msg_print, 0, STRING("mac_4_064"), 0, STRING("me"))
        END_IF
        CALL(evt_msg_select, 0, STRING("mac_4_063_yesno"))
        IF_INT_EQUAL(LW(0), 1)
            CALL(evt_msg_print_add, 0, STRING("mac_4_065"))
            RETURN
        END_IF
        // Podley tells the tale of Bobbery and his wife Scarlette, with the camera pushed in.
        CALL(evt_msg_print_add, 0, STRING("mac_4_066"))
        CALL(evt_cam3d_evt_set, 300, 95, 27, 300, 43, -268, 1500, 11)
        CALL(evt_snd_bgmoff_f, PSND_FADE_HOLD, 2000)
        WAIT_MS(1500)
        CALL(evt_msg_print, 0, STRING("mac_4_067"), 0, STRING("me"))
        CALL(evt_npc_reverse_ry, STRING("me"))
        WAIT_MS(1000)
        CALL(evt_msg_print, 0, STRING("mac_4_068"), 0, STRING("me"))
        WAIT_MS(1000)
        CALL(evt_npc_reverse_ry, STRING("me"))
        WAIT_MS(1000)
#if VERSION == VERSION_EU
        CALL(evt_party_stop, 0)
#endif
        CALL(evt_msg_print_party, STRING("mac_4_069"))
#if VERSION == VERSION_EU
        CALL(evt_party_run, 0)
#endif
        SET_VALUE(GSWF(GSWF_GOR01_PODLEY_BOBBERY_TALE_DONE), 1)
        CALL(evt_cam3d_evt_off, 0, 11)
        // Podley asks whether they still want Bobbery at sea.
        CALL(evt_msg_print, 0, STRING("mac_4_070"), 0, STRING("me"))
        LABEL(100)
        CALL(evt_msg_select, 0, STRING("mac_4_070_yesno"))
        IF_INT_EQUAL(LW(0), 1)
            CALL(evt_msg_print_add, 0, STRING("mac_4_072"))
            CALL(evt_snd_bgmoff_f, PSND_FADE_OUT | PSND_CH(1), 1000)
            CALL(evt_snd_bgmon_f, PSND_FADE_RESUME | PSND_FADE_IN, 0, 1000)
            RETURN
        END_IF
        CALL(evt_msg_print_add, 0, STRING("mac_4_073"))
        // Podley agrees and walks out from behind the bar, jumping the counter.
        CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
        IF_INT_EQUAL(GF(5), 1)
            CALL(evt_npc_set_ry, STRING("me"), 90)
            CALL(evt_npc_move_position, STRING("me"), 345, -260, 0, FLOAT(40.0f), 0)
            CALL(evt_npc_sound_data_set, STRING("me"), EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR, 0, 0)
            CALL(evt_npc_jump_position_nohit, STRING("me"), 345, -20, -260, 500, 0)
            WAIT_MS(1000)
            CALL(evt_npc_jump_position_nohit, STRING("me"), 345, 0, -260, 500, 0)
            CALL(evt_npc_sound_data_reset, STRING("me"))
            CALL(evt_npc_set_ry, STRING("me"), 270)
        ELSE
            CALL(evt_npc_set_ry, STRING("me"), 270)
            CALL(evt_npc_move_position, STRING("me"), 295, -260, 0, FLOAT(40.0f), 0)
            CALL(evt_npc_jump_position_nohit, STRING("me"), 295, -20, -260, 500, 0)
            WAIT_MS(1000)
            CALL(evt_npc_jump_position_nohit, STRING("me"), 295, 0, -260, 500, 0)
            WAIT_MS(500)
            CALL(evt_npc_set_ry, STRING("me"), 90)
        END_IF
        CALL(evt_npc_move_position, STRING("me"), 325, -275, 0, FLOAT(40.0f), 0)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        // Mario receives the Old Letter.
        CALL(evt_item_entry, STRING("letter"), ITEM_OLD_LETTER, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED, -1, 0)
        CALL(evt_item_flag_on, STRING("letter"), ITEM_FLAG_BGM_SILENT | ITEM_FLAG_NO_TOUCH)
        CALL(evt_item_get_item, STRING("letter"))
        CALL(evt_cam3d_evt_set, 300, 95, 27, 300, 43, -268, 500, 11)
        WAIT_MS(800)
        // Podley explains that it is Scarlette's last letter and asks Mario to take it to Bobbery.
        CALL(evt_msg_print, 0, STRING("mac_4_075"), 0, STRING("me"))
        CALL(evt_cam3d_evt_off, 500, 11)
        WAIT_MS(800)
        CALL(evt_msg_print, 0, STRING("mac_4_076"), 0, STRING("me"))
#if VERSION == VERSION_EU
        CALL(evt_party_stop, 0)
#endif
        CALL(evt_msg_print_party, STRING("mac_4_077"))
#if VERSION == VERSION_EU
        CALL(evt_party_run, 0)
#endif
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_NOD1_4"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_N_2"))
        WAIT_MS(800)
        // Story advances: Podley's advice has been given.
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG4_35_ADVICE_FROM_PODLEY)
        CALL(evt_snd_bgmoff_f, PSND_FADE_OUT | PSND_CH(1), 1000)
        CALL(evt_snd_bgmon_f, PSND_FADE_RESUME | PSND_FADE_IN, 0, 1000)
        CASE_EQUAL(STORY_STG4_35_ADVICE_FROM_PODLEY)
        // Later stages: a short line, then a line per stage of the story.
        CALL(evt_msg_print, 0, STRING("mac_4_076"), 0, STRING("me"))
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("gor_01_016"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_016_01"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_016_02"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("gor_01_016_03"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_32_CHATTING_WITH_FLAVIO)
        CALL(evt_msg_print, 0, STRING("gor_01_016_04"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("gor_01_016_05"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("gor_01_016_06"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_016_07"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_016_08"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_016_09"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * Init event of the item shop clerk: while the contact lens order has arrived (GSWF_GOR01_LENS_ARRIVED) he
 * stands at (-75, 0, -30); from Chapter 4's Flavio step on he is hidden below the map.
 */
EVT_BEGIN(shoptender_init)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG4_32_CHATTING_WITH_FLAVIO)
        IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_ARRIVED), 1)
            CALL(evt_npc_set_position, STRING("me"), -75, 0, -30)
            CALL(evt_npc_set_ry, STRING("me"), 90)
        END_IF
    ELSE
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_IF
    RETURN
EVT_END()

/**
 * Talk event of the item shop clerk: handles ordering the Contact Lens for Zess T. (gor_01_012 to gor_01_015_01;
 * the order time is saved in GSW_GOR01_LENS_ORDER_TIME) and, once it was delivered,
 * a line per story stage (gor_01_015_02 to _05).
 */
EVT_BEGIN(shoptender_talk)
    DEBUG_PUT_MSG(STRING("店員TALK"))
    IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_DELIVERED), 0)
        DEBUG_PUT_MSG(STRING("店員TALK２"))
        IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_ARRIVED), 1)
            CALL(evt_pouch_check_item, ITEM_CONTACT_LENS, LW(0))
            IF_INT_LESS(LW(0), 1)
                CALL(evt_msg_print, 0, STRING("gor_01_015"), 0, STRING("me"))
            ELSE
                CALL(evt_msg_print, 0, STRING("gor_01_015_01"), 0, STRING("me"))
            END_IF
            RETURN
        END_IF
        SET_VALUE(LW(0), GSWF(GSWF_GOR01_LENS_ORDERED))
        ADD(LW(0), GSWF(GSWF_GOR01_LENS_ORDERED_ALT))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_msg_print, 0, STRING("gor_01_014"), 0, STRING("me"))
            RETURN
        END_IF
        CALL(evt_msg_print, 0, STRING("gor_01_012"), 0, STRING("me"))
        IF_INT_EQUAL(GSWF(GSWF_GOR01_ZESS_BLOCKS_GATE), 1)
            CALL(evt_mario_set_pose, STRING("M_I_2"))
            WAIT_MS(700)
            CALL(evt_mario_set_pose, STRING("M_S_1"))
            CALL(evt_npc_get_position, STRING("me"), LW(10), LW(11), LW(12))
            CALL(evt_msg_print, 0, STRING("gor_01_013"), 0, STRING("me"))
            CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
            CALL(evt_cam3d_evt_set, 358, 123, -301, -189, 75, -301, 2600, 11)
            CALL(evt_npc_set_ry, STRING("me"), 0)
            CALL(evt_npc_move_position, STRING("me"), LW(10), -330, 0, FLOAT(90.0f), 0)
            CALL(evt_npc_set_anim, STRING("me"), STRING("T_1"))
            WAIT_MS(1000)
            CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
            CALL(evt_npc_set_anim, STRING("店長"), STRING("T_1"))
            WAIT_MS(1000)
            CALL(evt_npc_set_anim, STRING("店長"), STRING("S_1"))
            CALL(evt_npc_set_anim, STRING("me"), STRING("T_1"))
            WAIT_MS(500)
            CALL(evt_npc_set_anim, STRING("me"), STRING("S_1"))
            WAIT_MS(500)
            CALL(evt_cam3d_evt_off, 2600, 11)
            CALL(evt_npc_set_ry, STRING("me"), 180)
            CALL(evt_npc_move_position, STRING("me"), LW(10), LW(12), 0, FLOAT(90.0f), 0)
            CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
            CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
            WAIT_MS(500)
            CALL(evt_msg_print, 0, STRING("gor_01_013_01"), 0, STRING("me"))
            IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG1_17_FATHER_AND_SON_REUNITED)
                SET_VALUE(GSWF(GSWF_GOR01_LENS_ORDERED), 1)
            ELSE
                SET_VALUE(GSWF(GSWF_GOR01_LENS_ORDERED_ALT), 1)
            END_IF
            CALL(evt_sub_save_playtime, GSW(GSW_GOR01_LENS_ORDER_TIME))
        END_IF
    ELSE
        DEBUG_PUT_MSG(STRING("店員TALK３"))
        SWITCH(GSW(GSW_STORY_PROGRESS))
            CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
            CALL(evt_msg_print, 0, STRING("gor_01_015_02"), 0, STRING("me"))
            CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
            CALL(evt_msg_print, 0, STRING("gor_01_015_03"), 0, STRING("me"))
            CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
            CALL(evt_msg_print, 0, STRING("gor_01_015_04"), 0, STRING("me"))
            CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
            CALL(evt_msg_print, 0, STRING("gor_01_015_05"), 0, STRING("me"))
        END_SWITCH
    END_IF
    RETURN
EVT_END()

/** Init event of the inn clerk: empty. */
EVT_BEGIN(yadotender_init)
    RETURN
EVT_END()

/** Talk event of the inn clerk: empty. */
EVT_BEGIN(yadotender_talk)
    RETURN
EVT_END()

/** Init event of the first street-stall seller: marks his status and lets him walk through walls. */
EVT_BEGIN(roten1_init)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT)
    RETURN
EVT_END()

/**
 * Regular event of the first street-stall seller:
 * loops forever walking between x=450 and x=-350 at z=150, pausing a second at each end.
 */
EVT_BEGIN(roten1_regl)
    LOOP(0)
        CALL(evt_npc_move_position, STRING("me"), 450, 150, 0, FLOAT(32.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_move_position, STRING("me"), -350, 150, 0, FLOAT(32.0f), 0)
        WAIT_MS(1000)
    END_LOOP
    RETURN
EVT_END()

/** Talk event of the first street-stall seller: one line per story stage (gor_01_025_00 to gor_01_025_08). */
EVT_BEGIN(roten1_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("gor_01_025_00"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_025_01"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_025_02"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("gor_01_025_03"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("gor_01_025_04"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("gor_01_025_05"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_025_06"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_025_07"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_025_08"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/** Init event of the second street-stall seller: lets him walk through walls. */
EVT_BEGIN(roten2_init)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT)
    RETURN
EVT_END()

/** Talk event of the second street-stall seller: one line per story stage (gor_01_025_00_2 to gor_01_025_08_2). */
EVT_BEGIN(roten2_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("gor_01_025_00_2"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_025_01_2"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_025_02_2"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("gor_01_025_03_2"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("gor_01_025_04_2"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("gor_01_025_05_2"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_025_06_2"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_025_07_2"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_025_08_2"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/** Init event of the first Goomba villager: marks his status and lets him walk through walls. */
EVT_BEGIN(kuribo1_init)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT)
    RETURN
EVT_END()

/**
 * Regular event of the first Goomba villager: loops forever walking between x=375 and x=-375 at z=390,
 * pausing a second at each end.
 */
EVT_BEGIN(kuribo1_regl)
    LOOP(0)
        CALL(evt_npc_move_position, STRING("me"), 375, 390, 0, FLOAT(40.0f), 0)
        WAIT_MS(1000)
        CALL(evt_npc_move_position, STRING("me"), -375, 390, 0, FLOAT(40.0f), 0)
        WAIT_MS(1000)
    END_LOOP
    RETURN
EVT_END()

/**
 * Talk event of the first Goomba villager.
 * While Trouble Center job 4 is active it gives the request (irai_04_001) and a reminder;
 * otherwise one line per story stage (gor_01_026_00 to _08).
 */
EVT_BEGIN(kuribo1_talk)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 4)
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
            CALL(evt_msg_print, 0, STRING("irai_04_001"), 0, STRING("me"))
            SET_VALUE(GSWF(GSWF_TROUBLE_WORK_BASE), 1)
        ELSE
            CALL(evt_msg_print, 0, STRING("irai_04_002"), 0, STRING("me"))
        END_IF
        RETURN
    END_IF
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("gor_01_026_00"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_026_01"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_026_02"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("gor_01_026_03"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("gor_01_026_04"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("gor_01_026_05"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_026_06"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_026_07"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_026_08"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/** Init event of the second Goomba villager: lets him walk through walls. */
EVT_BEGIN(kuribo2_init)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT)
    RETURN
EVT_END()

/** Regular event of the second Goomba villager: wanders with gor_villager_urouro. */
EVT_BEGIN(kuribo2_regl)
    CALL_CHILD(gor_villager_urouro)
    RETURN
EVT_END()

/** Talk event of the second Goomba villager: one line per story stage (gor_01_027_00 to _08). */
EVT_BEGIN(kuribo2_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("gor_01_027_00"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_027_01"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_027_02"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("gor_01_027_03"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("gor_01_027_04"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("gor_01_027_05"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_027_06"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_027_07"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_027_08"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/** Init event of the third Goomba villager: empty. */
EVT_BEGIN(kuribo3_init)
    RETURN
EVT_END()

/** Regular event of the third Goomba villager: wanders with gor_villager_urouro. */
EVT_BEGIN(kuribo3_regl)
    CALL_CHILD(gor_villager_urouro)
    RETURN
EVT_END()

/**
 * Talk event of the third Goomba villager.
 * During Trouble Center job 2 he hands Mario a box to deliver and pays 20 coins
 * when it comes back (GSWF_TROUBLE_02_SOLVED); otherwise one line per story stage (gor_01_028_00 to _08).
 */
EVT_BEGIN(kuribo3_talk)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 2)
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_1), 0)
            IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
                CALL(evt_msg_print, 0, STRING("irai_02_00"), 0, STRING("me"))
                CALL(evt_item_entry, STRING("irai_item"), ITEM_BOX, 0, -1000, 0, ITEM_ENTRY_FIXED, -1, 0)
                CALL(evt_item_flag_on, STRING("irai_item"), ITEM_FLAG_NO_TOUCH)
                CALL(evt_item_get_item, STRING("irai_item"))
                SET_VALUE(GSWF(GSWF_TROUBLE_WORK_BASE), 1)
            ELSE
                CALL(evt_msg_print, 0, STRING("irai_02_01"), 0, STRING("me"))
            END_IF
        ELSE
            CALL(evt_msg_print, 0, STRING("irai_02_02"), 0, STRING("me"))
            CALL(evt_sub_get_coin, 20)
            SET_VALUE(GSW(GSW_TROUBLE_ACTIVE), 0)
            SET_VALUE(GSWF(GSWF_TROUBLE_02_SOLVED), 1)
            CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
        END_IF
        RETURN
    END_IF
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("gor_01_028_00"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_028_01"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_028_02"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("gor_01_028_03"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("gor_01_028_04"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("gor_01_028_05"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_028_06"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_028_07"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_028_08"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * Init event of "Chusan" (Mr. Chu, the first NPC);
 * during Trouble Center job 5 he stands at (-80, 0, 40) and chusan1_naguru is started.
 */
EVT_BEGIN(chusan1_init)
    CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT)
    CALL(evt_npc_status_onoff, 1, STRING("me"), 2)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 5)
        CALL(evt_npc_set_position, STRING("me"), -80, 0, 40)
        CALL(evt_npc_set_ry, STRING("me"), 270)
        SET_VALUE(GF(9), 1)
        SPAWN_EVENT(chusan1_naguru)
    END_IF
    RETURN
EVT_END()

/**
 * Regular event of Chusan: wanders with gor_villager_urouro, except during Trouble Center job 5,
 * when he stands still.
 */
EVT_BEGIN(chusan1_regl)
    IF_INT_NOT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 5)
        DEBUG_PUT_MSG(STRING("マルチュロ：普段のうろうろ"))
        CALL_CHILD(gor_villager_urouro)
    END_IF
    DEBUG_PUT_MSG(STRING("マルチュロ：依頼時は何もしない"))
    RETURN
EVT_END()

/**
 * Interrupt of Chusan during Trouble Center job 5, fired each time Mario hits him:
 * plays a hit sound and a different complaint line (irai_05_004 to irai_05_014) for each of the 11 hits,
 * then lets him recover.
 */
EVT_BEGIN(chusan1_dead)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_REQUEST_DAMAGED1"), LW(0), LW(1), LW(2), 0)
    IF_INT_GREATER_OR_EQUAL(GW(9), 11)
        SET_VALUE(GW(9), 0)
    END_IF
    ADD(GW(9), 1)
    BEGIN_INLINE_EVENT
        SWITCH(GW(9))
            CASE_EQUAL(1)
            CALL(evt_msg_print, 0, STRING("irai_05_004"), 0, STRING("me"))
            CASE_EQUAL(2)
            CALL(evt_msg_print, 0, STRING("irai_05_005"), 0, STRING("me"))
            CASE_EQUAL(3)
            CALL(evt_msg_print, 0, STRING("irai_05_006"), 0, STRING("me"))
            CASE_EQUAL(4)
            CALL(evt_msg_print, 0, STRING("irai_05_007"), 0, STRING("me"))
            CASE_EQUAL(5)
            CALL(evt_msg_print, 0, STRING("irai_05_008"), 0, STRING("me"))
            CASE_EQUAL(6)
            CALL(evt_msg_print, 0, STRING("irai_05_009"), 0, STRING("me"))
            CASE_EQUAL(7)
            CALL(evt_msg_print, 0, STRING("irai_05_010"), 0, STRING("me"))
            CASE_EQUAL(8)
            CALL(evt_msg_print, 0, STRING("irai_05_011"), 0, STRING("me"))
            CASE_EQUAL(9)
            CALL(evt_msg_print, 0, STRING("irai_05_012"), 0, STRING("me"))
            CASE_EQUAL(10)
            CALL(evt_msg_print, 0, STRING("irai_05_013"), 0, STRING("me"))
            CASE_EQUAL(11)
            CALL(evt_msg_print, 0, STRING("irai_05_014"), 0, STRING("me"))
        END_SWITCH
    END_INLINE_EVENT
    WAIT_MS(1000)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

/**
 * Trouble Center job 5 timer: lets Mario hit Chusan (only the hammer key is enabled) for 15 seconds;
 * with 11 or more hits the job is done (GSWF_TROUBLE_05_SOLVED),
 * otherwise Chusan asks to try again (irai_05_016) and the event restarts.
 */
EVT_BEGIN(chusan1_naguru)
    WAIT_WHILE(GF(9))
    CALL(evt_mario_key_onoff, 0)
    CALL(chusan1_alwaysencont, 1)
    CALL(evt_npc_get_reglid, STRING("チューさん１"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_npc_reaction_flag_onoff, 1, STRING("チューさん１"), 2)
    CALL(evt_npc_change_interrupt, STRING("チューさん１"), 8, PTR(chusan1_dead))
    CALL(evt_mario_set_enable_key, 512)
    WAIT_MS(15000)
    CALL(evt_mario_set_enable_key, 0)
    CALL(evt_npc_reaction_flag_onoff, 0, STRING("チューさん１"), 2)
    IF_INT_GREATER_OR_EQUAL(GW(9), 11)
        CALL(evt_msg_print, 0, STRING("irai_05_015"), 0, STRING("チューさん１"))
        SET_VALUE(GSW(GSW_TROUBLE_ACTIVE), 0)
        SET_VALUE(GSWF(GSWF_TROUBLE_05_SOLVED), 1)
        CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
    ELSE
        CALL(evt_msg_print, 0, STRING("irai_05_016"), 0, STRING("チューさん１"))
        SET_VALUE(GF(9), 1)
        SPAWN_EVENT(chusan1_naguru)
    END_IF
    CALL(chusan1_alwaysencont, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Talk event of Chusan.
 * During Trouble Center job 5 Mario and the partners step up beside him
 * and he explains the request (irai_05_001 to _003); otherwise one line per story stage (gor_01_029_00 to _08).
 */
EVT_BEGIN(chusan1_talk)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 5)
        CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
        CALL(evt_npc_get_position, STRING("me"), LW(10), LW(11), LW(12))
        BEGIN_INLINE_EVENT
            ADD(LW(10), 60)
            CALL(evt_party_move_pos2, 0, LW(10), LW(12), FLOAT(120.0f))
            CALL(evt_party_set_dir, 0, 270, 200)
        END_INLINE_EVENT
        BEGIN_INLINE_EVENT
            ADD(LW(10), 90)
            CALL(evt_party_move_pos2, 1, LW(10), LW(12), FLOAT(120.0f))
            CALL(evt_party_set_dir, 1, 270, 200)
        END_INLINE_EVENT
        ADD(LW(10), 30)
        CALL(evt_mario_mov_pos2, LW(10), LW(12), FLOAT(120.0f))
        CALL(evt_mario_set_dir, 270, 200, 0)
        CALL(evt_set_dir_to_target, STRING("me"), STRING("mario"))
        WAIT_MS(500)
        CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
            CALL(evt_msg_print, 0, STRING("irai_05_001"), 0, STRING("me"))
            SET_VALUE(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
        ELSE
            CALL(evt_msg_print, 0, STRING("irai_05_002"), 0, STRING("me"))
        END_IF
        CALL(evt_msg_print, 0, STRING("irai_05_003"), 0, STRING("me"))
        SET_VALUE(GW(9), 0)
        SET_VALUE(GF(9), 0)
        RETURN
    END_IF
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("gor_01_029_00"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_029_01"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_029_02"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("gor_01_029_03"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("gor_01_029_04"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("gor_01_029_05"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_029_06"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_029_07"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_029_08"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/** Init event of the second Chusan: empty. */
EVT_BEGIN(chusan2_init)
    RETURN
EVT_END()

/** Talk event of the second Chusan: one line per story stage (gor_01_030_00 to _08). */
EVT_BEGIN(chusan2_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("gor_01_030_00"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_030_01"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_030_02"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("gor_01_030_03"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("gor_01_030_04"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("gor_01_030_05"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_030_06"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_030_07"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_030_08"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/** Init event of the Bob-omb villager: does nothing. */
static EVT_BEGIN(bomhei_init)
    RETURN
EVT_END()

/** Talk event of the Bob-omb villager: one line per story stage (gor_01_031_00 to _08). */
EVT_BEGIN(bomhei_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("gor_01_031_00"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_031_01"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("gor_01_031_02"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("gor_01_031_03"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("gor_01_031_04"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("gor_01_031_05"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("gor_01_031_06"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("gor_01_031_07"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("gor_01_031_08"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * Init event of Charlieton ("Bottakuru", the traveling merchant):
 * hidden below the map until Chapter 1's Father and Son reunion (Chapter 2 in the demos);
 * afterwards he stands in the plaza and GSWF_GOR01_CHARLIETON_BOUGHT is cleared.
 */
EVT_BEGIN(bottakuru_init)
#if VERSION <= VERSION_DEMO_US
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
#else
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG1_17_FATHER_AND_SON_REUNITED)
#endif
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
        RETURN
    END_IF
    CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT)
#if VERSION >= VERSION_JP
    CALL(evt_npc_set_ry, STRING("me"), 90)
#endif
    SET_VALUE(GSWF(GSWF_GOR01_CHARLIETON_BOUGHT), 0)
    RETURN
EVT_END()

#if VERSION >= VERSION_US
/**
 * Talk event of Charlieton, who sells special badges and items at high prices from the shop's special stock:
 * greets Mario, then loops through a buy menu (coins checked, item added to the pouch, stock decremented)
 * until Mario declines or the stock is empty. The US release formats prices with the message formatter.
 */
EVT_BEGIN(bottakuru_talk)
    // Charlieton is sold out, or has nothing Mario can still buy: he only thanks him.
    CALL(U_evt_badgeShop_get_special_zaiko, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("bottakuru_16"), 0, STRING("me"))
        RETURN
    ELSE
        CALL(evt_badgeShop_bottakuru_get_kind_cnt, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(evt_msg_print, 0, STRING("bottakuru_03"), 0, STRING("me"))
            RETURN
        END_IF
    END_IF
    // Charlieton's sales pitch (a longer one on the first visit), then he asks if Mario wants to shop.
    IF_INT_EQUAL(GSWF(GSWF_GOR01_CHARLIETON_FIRST_TALK), 0)
        CALL(evt_msg_print, 0, STRING("bottakuru_00"), 0, STRING("me"))
        SET_VALUE(GSWF(GSWF_GOR01_CHARLIETON_FIRST_TALK), 1)
    ELSE
        IF_INT_EQUAL(GSWF(GSWF_GOR01_CHARLIETON_BOUGHT), 0)
            CALL(evt_msg_print, 0, STRING("bottakuru_01"), 0, STRING("me"))
        ELSE
            CALL(evt_msg_print, 0, STRING("bottakuru_02"), 0, STRING("me"))
        END_IF
    END_IF
    // Asked whether to shop: if Mario says no, Charlieton says goodbye.
    CALL(evt_msg_select, 0, STRING("bottakuru_yesno"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_04"))
        RETURN
    END_IF
    CALL(evt_msg_continue)
    // Shopping loop: the stock window opens; backing out ends the visit, and too few coins sends Mario back to
    // the list.
    LABEL(0)
    CALL(evt_win_coin_on, 0, LW(12))
    CALL(evt_win_other_select, 14)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print, 0, STRING("bottakuru_14"), 0, STRING("me"))
        RETURN
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_LESS(LW(0), LW(3))
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print, 0, STRING("bottakuru_05"), 0, STRING("me"))
        GOTO(0)
    END_IF
    // Charlieton quotes the price of the chosen item; for a badge (id 240 and up) he also gives its BP cost.
    IF_INT_GREATER_OR_EQUAL(LW(1), 240)
        CALL(evt_sub_get_language, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(evt_msg_print_insert, 0, STRING("bottakuru_07"), 0, STRING("me"), LW(2), LW(3), LW(4))
            CASE_DEFAULT
            CALL(evt_msg_fmt_int, 0, LW(14), STRING("bottakuru_07"), LW(3))
            CALL(evt_msg_fmt_str, 1, LW(14), LW(14), LW(2))
            CALL(evt_msg_print_insert, 1, LW(14), 0, STRING("me"), LW(4))
        END_SWITCH
    ELSE
        CALL(evt_sub_get_language, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(evt_msg_print_insert, 0, STRING("bottakuru_06"), 0, STRING("me"), LW(2), LW(3))
            CASE_DEFAULT
            CALL(evt_msg_fmt_int, 0, LW(14), STRING("bottakuru_06"), LW(3))
            CALL(evt_msg_fmt_str, 1, LW(14), LW(14), LW(2))
            CALL(evt_msg_print, 1, LW(14), 0, STRING("me"))
        END_SWITCH
    END_IF
    // Mario confirms or declines the purchase.
    CALL(evt_msg_select, 0, STRING("bottakuru_yesno"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print_add, 0, STRING("bottakuru_08"))
        RETURN
    END_IF
    // The item goes into Mario's pouch; if the pouch is full, Charlieton says so and the sale is off.
    CALL(evt_pouch_add_item, LW(1), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_win_coin_off, LW(12))
        IF_INT_GREATER_OR_EQUAL(LW(1), 240)
            CALL(evt_msg_print_add, 0, STRING("bottakuru_12"))
        ELSE
            CALL(evt_msg_print_add, 0, STRING("bottakuru_13"))
        END_IF
        RETURN
    END_IF
    // The stock of that item drops by one, the coins are paid and the 'bought something' flag is set.
    CALL(evt_badgeShop_bottakuru_dec, LW(1))
    MULTIPLY(LW(3), -1)
    CALL(evt_pouch_add_coin, LW(3))
    CALL(evt_win_coin_wait, LW(12))
    WAIT_MS(500)
    CALL(evt_win_coin_off, LW(12))
    SET_VALUE(GSWF(GSWF_GOR01_CHARLIETON_BOUGHT), 1)
    // Charlieton thanks Mario; if he is now sold out or Mario has no coins left the visit ends, otherwise he
    // offers more.
    CALL(U_evt_badgeShop_get_special_zaiko, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_15"))
        RETURN
    ELSE
        CALL(evt_badgeShop_bottakuru_get_kind_cnt, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_add, 0, STRING("bottakuru_09"))
            RETURN
        END_IF
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_09"))
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("bottakuru_10"))
    CALL(evt_msg_select, 0, STRING("bottakuru_yesno"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_11"))
        RETURN
    END_IF
    CALL(evt_msg_continue)
    GOTO(0)
    RETURN
EVT_END()
#elif VERSION >= VERSION_JP
/**
 * Talk event of Charlieton, who sells special badges and items at high prices from the shop's special stock:
 * greets Mario, then loops through a buy menu (coins checked, item added to the pouch, stock decremented)
 * until Mario declines or the stock is empty. The US release formats prices with the message formatter.
 */
EVT_BEGIN(bottakuru_talk)
    // Charlieton is sold out, or has nothing Mario can still buy: he only thanks him.
    CALL(U_evt_badgeShop_get_special_zaiko, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("bottakuru_16"), 0, STRING("me"))
        RETURN
    ELSE
        CALL(evt_badgeShop_bottakuru_get_kind_cnt, LW(0))
        IF_INT_LESS_OR_EQUAL(LW(0), 0)
            CALL(evt_msg_print, 0, STRING("bottakuru_03"), 0, STRING("me"))
            RETURN
        END_IF
    END_IF
    // Charlieton's sales pitch (a longer one on the first visit), then he asks if Mario wants to shop.
    IF_INT_EQUAL(GSWF(GSWF_GOR01_CHARLIETON_FIRST_TALK), 0)
        CALL(evt_msg_print, 0, STRING("bottakuru_00"), 0, STRING("me"))
        SET_VALUE(GSWF(GSWF_GOR01_CHARLIETON_FIRST_TALK), 1)
    ELSE
        IF_INT_EQUAL(GSWF(GSWF_GOR01_CHARLIETON_BOUGHT), 0)
            CALL(evt_msg_print, 0, STRING("bottakuru_01"), 0, STRING("me"))
        ELSE
            CALL(evt_msg_print, 0, STRING("bottakuru_02"), 0, STRING("me"))
        END_IF
    END_IF
    // Asked whether to shop: if Mario says no, Charlieton says goodbye.
    CALL(evt_msg_select, 0, STRING("bottakuru_yesno"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_04"))
        RETURN
    END_IF
    CALL(evt_msg_continue)
    // Shopping loop: the stock window opens; backing out ends the visit, and too few coins sends Mario back to
    // the list.
    LABEL(0)
    CALL(evt_win_coin_on, 0, LW(12))
    CALL(evt_win_other_select, 14)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print, 0, STRING("bottakuru_14"), 0, STRING("me"))
        RETURN
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_LESS(LW(0), LW(3))
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print, 0, STRING("bottakuru_05"), 0, STRING("me"))
        GOTO(0)
    END_IF
    // Charlieton quotes the price of the chosen item; for a badge (id 240 and up) he also gives its BP cost.
    IF_INT_GREATER_OR_EQUAL(LW(1), 240)
        CALL(evt_sub_get_language, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_insert, 0, STRING("bottakuru_07"), 0, STRING("me"), LW(3), LW(2), LW(4))
        ELSE
            CALL(evt_msg_print_insert, 0, STRING("bottakuru_07"), 0, STRING("me"), LW(2), LW(3), LW(4))
        END_IF
    ELSE
        CALL(evt_sub_get_language, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_insert, 0, STRING("bottakuru_06"), 0, STRING("me"), LW(3), LW(2))
        ELSE
            CALL(evt_msg_print_insert, 0, STRING("bottakuru_06"), 0, STRING("me"), LW(2), LW(3))
        END_IF
    END_IF
    // Mario confirms or declines the purchase.
    CALL(evt_msg_select, 0, STRING("bottakuru_yesno"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print_add, 0, STRING("bottakuru_08"))
        RETURN
    END_IF
    // The item goes into Mario's pouch; if the pouch is full, Charlieton says so and the sale is off.
    CALL(evt_pouch_add_item, LW(1), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_win_coin_off, LW(12))
        IF_INT_GREATER_OR_EQUAL(LW(1), 240)
            CALL(evt_msg_print_add, 0, STRING("bottakuru_12"))
        ELSE
            CALL(evt_msg_print_add, 0, STRING("bottakuru_13"))
        END_IF
        RETURN
    END_IF
    // The stock of that item drops by one, the coins are paid and the 'bought something' flag is set.
    CALL(evt_badgeShop_bottakuru_dec, LW(1))
    MULTIPLY(LW(3), -1)
    CALL(evt_pouch_add_coin, LW(3))
    CALL(evt_win_coin_wait, LW(12))
    WAIT_MS(500)
    CALL(evt_win_coin_off, LW(12))
    SET_VALUE(GSWF(GSWF_GOR01_CHARLIETON_BOUGHT), 1)
    // Charlieton thanks Mario; if he is now sold out or Mario has no coins left the visit ends, otherwise he
    // offers more.
    CALL(U_evt_badgeShop_get_special_zaiko, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_15"))
        RETURN
    ELSE
        CALL(evt_badgeShop_bottakuru_get_kind_cnt, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_add, 0, STRING("bottakuru_09"))
            RETURN
        END_IF
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_09"))
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("bottakuru_10"))
    CALL(evt_msg_select, 0, STRING("bottakuru_yesno"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_11"))
        RETURN
    END_IF
    CALL(evt_msg_continue)
    GOTO(0)
    RETURN
EVT_END()
#else
/**
 * Talk event of Charlieton, who sells special badges and items at high prices from the shop's special stock:
 * greets Mario, then loops through a buy menu (coins checked, item added to the pouch, stock decremented)
 * until Mario declines or the stock is empty. The US release formats prices with the message formatter.
 */
EVT_BEGIN(bottakuru_talk)
    // If nothing is left to buy, Charlieton only thanks Mario.
    CALL(evt_badgeShop_bottakuru_get_kind_cnt, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, STRING("bottakuru_03"), 0, STRING("me"))
        RETURN
    END_IF
    // Charlieton's sales pitch (a longer one on the first visit), then he asks if Mario wants to shop.
    IF_INT_EQUAL(GSWF(GSWF_GOR01_CHARLIETON_FIRST_TALK), 0)
        CALL(evt_msg_print, 0, STRING("bottakuru_00"), 0, STRING("me"))
        SET_VALUE(GSWF(GSWF_GOR01_CHARLIETON_FIRST_TALK), 1)
    ELSE
        IF_INT_EQUAL(GSWF(GSWF_GOR01_CHARLIETON_BOUGHT), 0)
            CALL(evt_msg_print, 0, STRING("bottakuru_01"), 0, STRING("me"))
        ELSE
            CALL(evt_msg_print, 0, STRING("bottakuru_02"), 0, STRING("me"))
        END_IF
    END_IF
    // Asked whether to shop: if Mario says no, Charlieton says goodbye.
    CALL(evt_msg_select, 0, STRING("bottakuru_yesno"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_04"))
        RETURN
    END_IF
    CALL(evt_msg_continue)
    // Shopping loop: the stock window opens; backing out ends the visit, and too few coins sends Mario back to
    // the list.
    LABEL(0)
    CALL(evt_win_coin_on, 0, LW(12))
    CALL(evt_win_other_select, 14)
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print, 0, STRING("bottakuru_14"), 0, STRING("me"))
        RETURN
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_LESS(LW(0), LW(3))
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print, 0, STRING("bottakuru_05"), 0, STRING("me"))
        GOTO(0)
    END_IF
    // Charlieton quotes the price of the chosen item; for a badge (id 240 and up) he also gives its BP cost.
    IF_INT_GREATER_OR_EQUAL(LW(1), 240)
        CALL(evt_msg_print_insert, 0, STRING("bottakuru_07"), 0, STRING("me"), LW(2), LW(3), LW(4))
    ELSE
        CALL(evt_msg_print_insert, 0, STRING("bottakuru_06"), 0, STRING("me"), LW(2), LW(3))
    END_IF
    // Mario confirms or declines the purchase.
    CALL(evt_msg_select, 0, STRING("bottakuru_yesno"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_win_coin_off, LW(12))
        CALL(evt_msg_print_add, 0, STRING("bottakuru_08"))
        RETURN
    END_IF
    // The item goes into Mario's pouch; if the pouch is full, Charlieton says so and the sale is off.
    CALL(evt_pouch_add_item, LW(1), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_win_coin_off, LW(12))
        IF_INT_GREATER_OR_EQUAL(LW(1), 240)
            CALL(evt_msg_print_add, 0, STRING("bottakuru_12"))
        ELSE
            CALL(evt_msg_print_add, 0, STRING("bottakuru_13"))
        END_IF
        RETURN
    END_IF
    // The stock of that item drops by one, the coins are paid and the 'bought something' flag is set.
    CALL(evt_badgeShop_bottakuru_dec, LW(1))
    MULTIPLY(LW(3), -1)
    CALL(evt_pouch_add_coin, LW(3))
    CALL(evt_win_coin_wait, LW(12))
    WAIT_MS(500)
    CALL(evt_win_coin_off, LW(12))
    SET_VALUE(GSWF(GSWF_GOR01_CHARLIETON_BOUGHT), 1)
    // Charlieton thanks Mario; if he is now sold out or Mario has no coins left the visit ends, otherwise he
    // offers more.
    CALL(evt_badgeShop_bottakuru_get_kind_cnt, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_09"))
        RETURN
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_09"))
        RETURN
    END_IF
    CALL(evt_msg_print_add, 0, STRING("bottakuru_10"))
    CALL(evt_msg_select, 0, STRING("bottakuru_yesno"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("bottakuru_11"))
        RETURN
    END_IF
    CALL(evt_msg_continue)
    GOTO(0)
    RETURN
EVT_END()
#endif

/**
 * Init event of Luigi in the plaza: places him by story stage:
 * (380, 0, 300) from STORY_STG2_25 to STORY_STG3_31, (110, 0, -240) from STORY_STG4_15_05 to STORY_STG5_42,
 * and (230, 154, -300) from STORY_STG7_20_LORD_CRUMP_DEFEATED on.
 */
static EVT_BEGIN(luigi_init)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG2_25_AFTER_THE_BOSS_BATTLE, STORY_STG3_31_GRUBBAS_PLANS)
        CALL(evt_npc_set_position, STRING("me"), 380, 0, 300)
        CALL(evt_npc_set_ry_lr, STRING("me"), 0)
        CASE_BETWEEN(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT, STORY_STG5_42_PIRATES_VS_X_NAUTS)
        CALL(evt_npc_set_position, STRING("me"), 110, 0, -240)
        CALL(evt_npc_set_ry_lr, STRING("me"), 1)
        CASE_GREATER_OR_EQUAL(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_npc_set_position, STRING("me"), 230, 154, -300)
        CALL(evt_npc_set_ry_lr, STRING("me"), 0)
    END_SWITCH
    RETURN
EVT_END()

/** Talk event of Luigi: runs the shared first-talk scene luigi_gor_first_talk. */
static EVT_BEGIN(luigi_talk)
    CALL_CHILD(luigi_gor_first_talk)
    RETURN
EVT_END()

/**
 * Enters the NPC that walks with Luigi by story stage:
 * Kick ("c_lp_gesso") from STORY_STG2_25 to STORY_STG3_31,
 * Torque ("c_lp_met") from STORY_STG4_15_05 to STORY_STG5_42,
 * and a second Kick from STORY_STG7_20_LORD_CRUMP_DEFEATED, each with its NPC setup table.
 */
static EVT_BEGIN(luigi_npcEnt)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG2_25_AFTER_THE_BOSS_BATTLE, STORY_STG3_31_GRUBBAS_PLANS)
        CALL(evt_npc_entry, STRING("キック"), STRING("c_lp_gesso"))
        CALL(evt_npc_set_tribe, STRING("キック"), STRING("キック"))
        CALL(evt_npc_setup, PTR(kickEnt))
        CASE_BETWEEN(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT, STORY_STG5_42_PIRATES_VS_X_NAUTS)
        CALL(evt_npc_entry, STRING("トルク"), STRING("c_lp_met"))
        CALL(evt_npc_set_tribe, STRING("トルク"), STRING("トルク"))
        CALL(evt_npc_setup, PTR(torqueEnt))
        CASE_GREATER_OR_EQUAL(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_npc_entry, STRING("キック２"), STRING("c_lp_gesso"))
        CALL(evt_npc_set_tribe, STRING("キック２"), STRING("キック２"))
        CALL(evt_npc_setup, PTR(kick2Ent))
    END_SWITCH
    RETURN
EVT_END()

/** Init event of Kick, Luigi's friend in the Chapter 2 to 3 period: places him at (420, 0, 300). */
EVT_BEGIN(kick_init)
    CALL(evt_npc_set_position, STRING("me"), 420, 0, 300)
    CALL(evt_npc_set_ry_lr, STRING("me"), 0)
    RETURN
EVT_END()

/** Talk event of Kick: one line (luigi_npc_01). */
EVT_BEGIN(kick_talk)
    CALL(evt_msg_print, 0, STRING("luigi_npc_01"), 0, STRING("me"))
    RETURN
EVT_END()

/** NPC setup of Kick, Luigi's friend in chapters 2 and 3. */
NpcSetupInfo kickEnt[] = {
    {
        "キック", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        kick_init, // initEvent
        NULL, // regularEvent
        kick_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

/** Init event of Torque, Luigi's friend in the Chapter 4 to 5 period: places him at (160, 0, -240). */
EVT_BEGIN(torque_init)
    CALL(evt_npc_set_position, STRING("me"), 160, 0, -240)
    CALL(evt_npc_set_ry_lr, STRING("me"), 0)
    RETURN
EVT_END()

/** Talk event of Torque: one line (luigi_npc_03). */
EVT_BEGIN(torque_talk)
    CALL(evt_msg_print, 0, STRING("luigi_npc_03"), 0, STRING("me"))
    RETURN
EVT_END()

/** NPC setup of Torque, Luigi's friend in chapters 4 and 5. */
NpcSetupInfo torqueEnt[] = {
    {
        "トルク", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        torque_init, // initEvent
        NULL, // regularEvent
        torque_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

/**
 * Init event of the second Kick: standing at (270, 154, -300) on the rooftop between Lord Crump's defeat
 * and Grodus, hidden otherwise.
 */
EVT_BEGIN(kick2_init)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG7_20_LORD_CRUMP_DEFEATED, STORY_STG8_15_GRODUS)
        CALL(evt_npc_set_position, STRING("me"), 270, 154, -300)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    END_SWITCH
    CALL(evt_npc_set_ry_lr, STRING("me"), 0)
    RETURN
EVT_END()

/** Talk event of the second Kick: one line (luigi_npc_06). */
EVT_BEGIN(kick2_talk)
    CALL(evt_msg_print, 0, STRING("luigi_npc_06"), 0, STRING("me"))
    RETURN
EVT_END()

/** NPC setup of the second Kick, on the rooftop after Lord Crump's defeat. */
NpcSetupInfo kick2Ent[] = {
    {
        "キック２", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        kick2_init, // initEvent
        NULL, // regularEvent
        kick2_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

/**
 * Init event of the thief Borodo for the third stage of Trouble Center job 4:
 * if the earlier work flags are set and WORK_3 is clear,
 * enters him ("c_borodo_n") at (402, 0, -302) facing 90 with borodo2_talk as his talk event.
 */
static EVT_BEGIN(borodo2_init)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 4)
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 1)
            IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_1), 1)
                IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_2), 1)
                    IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_3), 0)
                        CALL(evt_npc_entry, STRING("ボロドー２"), STRING("c_borodo_n"))
                        CALL(evt_npc_set_tribe, STRING("ボロドー２"), STRING("盗賊"))
                        CALL(evt_npc_flag_onoff, 1, STRING("ボロドー２"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
                        CALL(evt_npc_set_position, STRING("ボロドー２"), 402, 0, -302)
                        CALL(evt_npc_set_ry, STRING("ボロドー２"), 90)
                        CALL(evt_npc_change_interrupt, STRING("ボロドー２"), 6, PTR(borodo2_talk))
                        RETURN
                    END_IF
                END_IF
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Talk event of Borodo for job 4 (irai_04_005):
 * he stops the Goomba (Kuribo 1)'s regular event and sends it off,
 * moving it to (229, 0, -400) and then to (420, -350);
 * the Goomba speaks (irai_04_006), the scene adds 20 coins (evt_sub_get_coin) and goes on through irai_04_008
 * and irai_04_009, ending with GSWF_TROUBLE_WORK_3.
 */
static EVT_BEGIN(borodo2_talk)
    CALL(evt_npc_get_reglid, STRING("クリボー１"), LW(0))
    DELETE_EVENT(LW(0))
    CALL(evt_msg_print, 0, STRING("irai_04_005"), 0, STRING("me"))
    CALL(evt_npc_flag_onoff, 1, STRING("me"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("クリボー１"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_set_position, STRING("クリボー１"), 229, 0, -400)
    CALL(evt_npc_set_ry, STRING("クリボー１"), 90)
    CALL(evt_npc_move_position, STRING("クリボー１"), 420, -400, 0, FLOAT(120.0f), 0)
    CALL(evt_npc_move_position, STRING("クリボー１"), 420, -350, 0, FLOAT(120.0f), 0)
    CALL(evt_set_dir_to_target, STRING("クリボー１"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("irai_04_006"), 0, STRING("クリボー１"))
    CALL(evt_sub_get_coin, 20)
    CALL(evt_npc_set_ry, STRING("クリボー１"), 270)
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("irai_04_008"), 0, STRING("クリボー１"))
    CALL(evt_msg_print, 0, STRING("irai_04_009"), 0, STRING("me"))
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("me"), 400, -400, 0, FLOAT(120.0f), 0)
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("クリボー１"), 420, -400, 0, FLOAT(120.0f), 0)
    CALL(evt_npc_set_ry, STRING("クリボー１"), 270)
    WAIT_MS(200)
    WAIT_WHILE(GF(0))
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        WAIT_MS(600)
        CALL(evt_npc_move_position, STRING("クリボー１"), 392, -400, 0, FLOAT(120.0f), 0)
        WAIT_MS(800)
        CALL(evt_npc_move_position, STRING("クリボー１"), 362, -400, 0, FLOAT(120.0f), 0)
        WAIT_MS(800)
        CALL(evt_npc_move_position, STRING("クリボー１"), 332, -400, 0, FLOAT(120.0f), 0)
        WAIT_MS(800)
        CALL(evt_npc_move_position, STRING("クリボー１"), 302, -400, 0, FLOAT(120.0f), 0)
        WAIT_MS(800)
        CALL(evt_npc_move_position, STRING("クリボー１"), 272, -400, 0, FLOAT(120.0f), 0)
        WAIT_MS(800)
        CALL(evt_npc_move_position, STRING("クリボー１"), 242, -400, 0, FLOAT(120.0f), 0)
        CALL(evt_npc_set_position, STRING("クリボー１"), -375, 0, 390)
        CALL(evt_npc_restart_regular_event, STRING("クリボー１"))
        CALL(evt_npc_flag_onoff, 0, STRING("クリボー１"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    CALL(evt_npc_set_ry, STRING("me"), 270)
    CALL(evt_npc_move_position, STRING("me"), 390, -395, 0, FLOAT(120.0f), 0)
    WAIT_MS(800)
    CALL(evt_npc_move_position, STRING("me"), 360, -395, 0, FLOAT(120.0f), 0)
    WAIT_MS(800)
    CALL(evt_npc_move_position, STRING("me"), 330, -395, 0, FLOAT(120.0f), 0)
    WAIT_MS(800)
    CALL(evt_npc_move_position, STRING("me"), 300, -395, 0, FLOAT(120.0f), 0)
    WAIT_MS(800)
    CALL(evt_npc_move_position, STRING("me"), 270, -395, 0, FLOAT(120.0f), 0)
    WAIT_MS(800)
    CALL(evt_npc_move_position, STRING("me"), 242, -395, 0, FLOAT(120.0f), 0)
    CALL(evt_npc_set_position, STRING("me"), 0, -1000, 0)
    WAIT_WHILE(GF(0))
    SET_VALUE(GSWF(GSWF_TROUBLE_WORK_3), 1)
    SET_VALUE(GSW(GSW_TROUBLE_ACTIVE), 0)
    SET_VALUE(GSWF(GSWF_TROUBLE_04_SOLVED), 1)
    CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
    RETURN
EVT_END()

/** Init event of the thief who stole Mario's coins: from STORY_STG0_08_STOLEN_COINS on he stands at (500, 0, -175). */
EVT_BEGIN(thief_init)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_GREATER_OR_EQUAL(STORY_STG0_08_STOLEN_COINS)
        CALL(evt_npc_set_position, STRING("me"), 500, 0, -175)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Talk event of the thief.
 * During the stolen coins quest the first talk returns the stolen coins (rebuilt from GSW_GOR_STOLEN_COINS_LO
 * and _HI, a base-256 pair) and sets GSWF_GOR01_THIEF_CONFRONTED;
 * later talks and every later story stage give a line.
 */
EVT_BEGIN(thief_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG0_08_STOLEN_COINS, STORY_STG0_END_TO_STAGE_1)
        IF_INT_EQUAL(GSWF(GSWF_GOR01_THIEF_CONFRONTED), 0)
            SET_VALUE(LF(0), 0)
            IF_INT_EQUAL(GSW(GSW_GOR_STOLEN_COINS_LO), 0)
                IF_INT_EQUAL(GSW(GSW_GOR_STOLEN_COINS_HI), 0)
                    SET_VALUE(LF(0), 1)
                END_IF
            END_IF
            IF_INT_EQUAL(LF(0), 0)
                CALL(evt_msg_print, 0, STRING("mac_0_065_01"), 0, STRING("me"))
                BEGIN_INLINE_EVENT
                    CALL(evt_StatusOpen)
                    WAIT_MS(1000)
                    CALL(evt_pouch_get_coin, LW(0))
                    ADD(LW(0), GSW(GSW_GOR_STOLEN_COINS_LO))
                    SET_VALUE(LW(1), GSW(GSW_GOR_STOLEN_COINS_HI))
                    MULTIPLY(LW(1), 256)
                    ADD(LW(0), LW(1))
                    CALL(evt_pouch_set_coin, LW(0))
                    WAIT_MS(2000)
                    CALL(evt_StatusClose)
                END_INLINE_EVENT
            ELSE
                CALL(evt_msg_print, 0, STRING("mac_0_065_02"), 0, STRING("me"))
            END_IF
            SET_VALUE(GSWF(GSWF_GOR01_THIEF_CONFRONTED), 1)
        ELSE
            IF_INT_EQUAL(GSWF(GSWF_GOR01_THIEF_LEFT_HOUSE), 0)
                CALL(evt_msg_print, 0, STRING("mac_0_065_03"), 0, STRING("me"))
            ELSE
                CALL(evt_msg_print, 0, STRING("mac_0_065_04"), 0, STRING("me"))
            END_IF
        END_IF
        CASE_LESS(STORY_STG1_17_FATHER_AND_SON_REUNITED)
        CALL(evt_msg_print, 0, STRING("mac_0_065_04"), 0, STRING("me"))
        CASE_LESS(STORY_STG2_25_AFTER_THE_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("mac_0_065_05"), 0, STRING("me"))
        CASE_LESS(STORY_STG3_32_BOSS_BATTLE)
        CALL(evt_msg_print, 0, STRING("mac_0_065_06"), 0, STRING("me"))
        CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
        CALL(evt_msg_print, 0, STRING("mac_0_065_07"), 0, STRING("me"))
        CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
        CALL(evt_msg_print, 0, STRING("mac_0_065_08"), 0, STRING("me"))
        CASE_LESS(STORY_STG6_54_WELCOME_BACK)
        CALL(evt_msg_print, 0, STRING("mac_0_065_09"), 0, STRING("me"))
        CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_msg_print, 0, STRING("mac_0_065_10"), 0, STRING("me"))
        CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
        CALL(evt_msg_print, 0, STRING("mac_0_065_11"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("mac_0_065_12"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * NPC setup of the central plaza: the badge shop owner and clerk, the old Toad, Zess T., Marco, the bar
 * owner, the shopkeepers, the inn clerk, the Goombas, the mice, the sailor Bob-omb, the rip-off merchant,
 * Luigi and the thief.
 */
static NpcSetupInfo npcEnt[] = {
    {
        "バッジ店長", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        badgemaster_init, // initEvent
        NULL, // regularEvent
        badgemaster_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "バッジ店員", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        npc_init_evt, // initEvent
        NULL, // regularEvent
        badgeshopper_talk_evt, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "キノじい", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        kinoji_init, // initEvent
        NULL, // regularEvent
        kinoji_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ナンシー", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        nancy_init, // initEvent
        nancy_regl, // regularEvent
        nancy_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "マルコ", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        marco_init, // initEvent
        NULL, // regularEvent
        marco_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "マスター", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        master_init, // initEvent
        NULL, // regularEvent
        master_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "店長", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // reactionFlags..returnEvent
        NULL, 0, // blowEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "店員", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        shoptender_init, // initEvent
        NULL, // regularEvent
        shoptender_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "宿店員", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        yadotender_init, // initEvent
        NULL, // regularEvent
        yadotender_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ロテン１", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        roten1_init, // initEvent
        roten1_regl, // regularEvent
        roten1_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ロテン２", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        roten2_init, // initEvent
        NULL, // regularEvent
        roten2_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "クリボー１", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        kuribo1_init, // initEvent
        kuribo1_regl, // regularEvent
        kuribo1_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "クリボー２", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        kuribo2_init, // initEvent
        NULL, // regularEvent
        kuribo2_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "クリボー３", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        kuribo3_init, // initEvent
        kuribo3_regl, // regularEvent
        kuribo3_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "チューさん１", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        chusan1_init, // initEvent
        chusan1_regl, // regularEvent
        chusan1_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "チューさん２", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        chusan2_init, // initEvent
        NULL, // regularEvent
        chusan2_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "水夫ボム兵", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        bomhei_init, // initEvent
        NULL, // regularEvent
        bomhei_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ボッタクール", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        bottakuru_init, // initEvent
        NULL, // regularEvent
        bottakuru_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "ルイージ", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        luigi_init, // initEvent
        NULL, // regularEvent
        luigi_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "盗賊", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        thief_init, // initEvent
        NULL, // regularEvent
        thief_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {
        "キノピコ", // name
        NPC_FLAG_SHADOW_NO_COLLISION | NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, NULL, NULL, NULL, NULL, NULL, NULL, NULL, // reactionFlags..returnEvent
        NULL, 0, // blowEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

/**
 * Enter event of the south exit "s_bero" (from the harbor):
 * when the story is at STORY_STG0_06_1000_X_NAUTS_AFTER it locks Mario's controls,
 * starts christine_nakama and returns 1 in LW(0); otherwise returns 0 and nothing happens.
 */
EVT_BEGIN(christine_nakama_before)
    IF_INT_NOT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG0_06_1000_X_NAUTS_AFTER)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_mario_key_onoff, 0)
    SPAWN_EVENT(christine_nakama)
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

/** Exits (beros) of this room: e_bero to gor_02, w_bero to gor_03 and s_bero to gor_00. */
static BeroEntry bero_entry_data[] = {
    {
        "e_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "gor_02", // nextMapName
        "w_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "w_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "gor_03", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "s_bero", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)christine_nakama_before, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "gor_00", // nextMapName
        "n_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

/**
 * Door animation callback of the house 01 door (Zess T.'s house):
 * rotates the door "S_ie_01_doa" about Y by 0.6 times the value in LW(0).
 */
static EVT_BEGIN(evt_door_01_00)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5996094f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_01_doa"), 0, LW(0), 0)
    RETURN
EVT_END()

/** Second door callback of house 01: rotates the door "S_ie_01_doa" about X by -0.5 times the value in LW(0). */
static EVT_BEGIN(evt_door_01_01)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_01_doa"), LW(0), 0, 0)
    RETURN
EVT_END()

/**
 * Wall callback of house 01: rotates the wall pieces "S_ie_01uB"
 * and "S_ie_01sB" about X by LW(0) in opposite directions, folding the front wall flat as the door opens.
 */
static EVT_BEGIN(evt_wall_01)
    SET_FLOAT_VALUE(LW(2), LW(0))
    SET_FLOAT_VALUE(LW(3), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(-1.0f))
    MULTIPLY_FLOAT(LW(3), FLOAT(1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_01uB"), LW(2), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_01sB"), LW(3), 0, 0)
    RETURN
EVT_END()

/**
 * NPCs of house 01 kept lit (exempt from the darkening) while Mario is inside: Zess T. Swapped into the
 * door's copy with evt_door_set_param once the Contact Lens is delivered.
 */
static const char* door_data_01_npc[] = {
    "ナンシー",
    NULL,
};

/** Field items of house 01 kept lit while Mario is inside: the Honey Shroom of Trouble Center request 18. */
const char* door_data_01_item[] = {
    "iri_18",
    NULL,
};

/** Called when the house 01 door opens: dips the music and ambience to 50 percent and low-passes the ambience. */
static EVT_BEGIN(evt_door_01_open)
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_envoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

/** Called when the house 01 door closes: brings the music and ambience back and removes the low-pass. */
static EVT_BEGIN(evt_door_01_close)
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

/**
 * Door of house 01 (Zess T.'s house) before the Contact Lens is delivered: the door model, hit areas, inside
 * and outside map groups and the scripts for opening and closing.
 */
static DoorParam door_data_01 = {
    0, // flags
    3, // type
    1, // se
    "S_ie_01_doa", // mapobj
    "A_ie_01_doa02", // hitIn
    "A_ie_01_doa01", // hitOut
    "S_ie_01_soto", // outside
    "A_ie_01_A", // outsideHit
    "S_ie_01_naka", // inside
    "A_ie_01_C", // insideHit
    evt_door_01_00, // evtIn
    evt_door_01_01, // evtOut
    evt_wall_01, // evtWall
    NULL, NULL, // npcs..mobjs
    door_data_01_item, // items
    evt_door_01_open, // evtOpen
    evt_door_01_close, // evtClose
};

/** Door of house 01 after the Contact Lens is delivered. */
DoorParam door_data_01_01 = {
    0, // flags
    3, // type
    1, // se
    "S_ie_01_doa", // mapobj
    "A_ie_01_doa02", // hitIn
    "A_ie_01_doa01", // hitOut
    "S_ie_01_soto", // outside
    "A_ie_01_A", // outsideHit
    "S_ie_01_naka", // inside
    "A_ie_01_C", // insideHit
    evt_door_01_00, // evtIn
    evt_door_01_01, // evtOut
    evt_wall_01, // evtWall
    (const char**)door_data_01_npc, // npcs
    NULL, // mobjs
    door_data_01_item, // items
    evt_door_01_open, // evtOpen
    evt_door_01_close, // evtClose
};

/**
 * Door callback for the ground floor of house 02 (the item shop):
 * rotates the door "S_ie_02_f1_doa" by LW(0) scaled by about 0.6 as Mario opens it.
 */
EVT_BEGIN(evt_door_02_00_f1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5996094f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_02_f1_doa"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Wall callback for house 02's ground floor: tilts the front wall pieces "S_ie_02_f1B",
 * "S_ie_02_f2uB" and "S_ie_02_f2sB" open by LW(0) degrees so the interior can be seen.
 */
EVT_BEGIN(evt_wall_02_f1)
    SET_FLOAT_VALUE(LW(2), LW(0))
    SET_FLOAT_VALUE(LW(3), LW(0))
    SET_FLOAT_VALUE(LW(4), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(-1.0f))
    MULTIPLY_FLOAT(LW(3), FLOAT(1.0f))
    MULTIPLY_FLOAT(LW(4), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_02_f1B"), 0, 0, LW(2))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_02_f2uB"), 0, 0, LW(3))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_02_f2sB"), 0, 0, LW(4))
    RETURN
EVT_END()

/**
 * NPCs of the item shop (house 02's ground floor) kept lit while Mario is inside: the shopkeeper and the
 * clerk.
 */
static const char* door_data_02_npc[] = {
    "店長",
    "店員",
    NULL,
};

/**
 * The same list while the Contact Lens has arrived (before STORY_STG4_32_CHATTING_WITH_FLAVIO): the
 * shopkeeper only.
 */
const char* door_data_02_npc_01[] = {
    "店長",
    NULL,
};

/**
 * Open callback for the item shop door: dips the music and ambience to half volume and low-passes the ambience
 * while Mario is inside.
 */
EVT_BEGIN(evt_door_02f1_open)
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_envoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_env_lpf, 0, 800)
    RETURN
EVT_END()

/** Close callback for the item shop door: brings the music and ambience back to normal. */
EVT_BEGIN(evt_door_02f1_close)
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    RETURN
EVT_END()

/** Door of house 02's ground floor (the item shop) in its normal state. */
DoorParam door_data_02_f1 = {
    0, // flags
    3, // type
    1, // se
    "S_ie_02_f1_doa", // mapobj
    "A_ie_02_f1_doa02", // hitIn
    "A_ie_02_f1_doa01", // hitOut
    "S_ie_02_f1_soto", // outside
    NULL, // outsideHit
    "S_ie_02_f1_naka", // inside
    "A_ie_02_f1_C", // insideHit
    evt_door_02_00_f1, // evtIn
    NULL, // evtOut
    evt_wall_02_f1, // evtWall
    door_data_02_npc, // npcs
    NULL, NULL, // mobjs..items
    evt_door_02f1_open, // evtOpen
    evt_door_02f1_close, // evtClose
};

/** Door of house 02's ground floor while the Contact Lens has arrived but not yet been delivered. */
DoorParam door_data_02_f1_01 = {
    0, // flags
    3, // type
    1, // se
    "S_ie_02_f1_doa", // mapobj
    "A_ie_02_f1_doa02", // hitIn
    "A_ie_02_f1_doa01", // hitOut
    "S_ie_02_f1_soto", // outside
    NULL, // outsideHit
    "S_ie_02_f1_naka", // inside
    "A_ie_02_f1_C", // insideHit
    evt_door_02_00_f1, // evtIn
    NULL, // evtOut
    evt_wall_02_f1, // evtWall
    door_data_02_npc_01, // npcs
    NULL, NULL, // mobjs..items
    evt_door_02f1_open, // evtOpen
    evt_door_02f1_close, // evtClose
};

/**
 * Message shown when the door of the badge shop upstairs is tried
 * while it is not open ("preparing", gor_01_024_00_00): locks the controls for the line, then unlocks them.
 */
EVT_BEGIN(evt_door_02_f2_junbityu)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("gor_01_024_00_00"), 0, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Door callback for the upstairs of house 02 (the badge shop):
 * rotates the door "S_ie_02_f2_doaD" by LW(0) scaled by about 0.6.
 */
EVT_BEGIN(evt_door_02_00_f2)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5996094f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_02_f2_doaD"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Wall callback for house 02's upstairs: tilts the wall pieces "S_ie_02_f1B",
 * "S_ie_02_f2uB" and "S_ie_02_f2sB" open by LW(0) degrees.
 */
EVT_BEGIN(evt_wall_02_f2)
    SET_FLOAT_VALUE(LW(2), LW(0))
    SET_FLOAT_VALUE(LW(3), LW(0))
    SET_FLOAT_VALUE(LW(4), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(-1.0f))
    MULTIPLY_FLOAT(LW(3), FLOAT(1.0f))
    MULTIPLY_FLOAT(LW(4), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_02_f1B"), 0, 0, LW(2))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_02_f2uB"), 0, 0, LW(3))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_02_f2sB"), 0, 0, LW(4))
    RETURN
EVT_END()

/** NPCs of the badge shop upstairs kept lit while Mario is inside: the badge shop owner and clerk. */
const char* badgemise_npc[] = {
    "バッジ店長",
    "バッジ店員",
    NULL,
};

#if VERSION >= VERSION_US
/**
 * Handler for the badge shop's display shelves ("S_item_07" to "S_item_11", see uwnobj_list):
 * when Mario picks a shelf item the clerk faces him, quotes the price,
 * and on a yes checks his coins and badge space, adds the badge, updates the shop stock and takes the coins.
 * The demo version is a simpler variant without the language switch.
 */
EVT_BEGIN(evt_badge_dummy)
    CALL(evt_mario_normalize)
    SET_VALUE(LW(10), LW(0))
    CALL(disp_off, LW(10))
    CALL(evt_set_dir_to_target, STRING("バッジ店員"), STRING("mario"))
    CALL(evt_mario_set_dir_npc, STRING("バッジ店員"))
    CALL(evt_win_coin_on, 0, LW(8))
    CALL(get_value, LW(10), LW(11), LW(12), LW(13), LW(14))
    CALL(evt_sub_get_language, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(evt_msg_print_insert, 0, STRING("badgeshop_00"), 0, STRING("バッジ店員"), LW(11), LW(13), LW(14))
        CASE_DEFAULT
        CALL(evt_msg_fmt_int, 0, LW(15), STRING("badgeshop_00"), LW(13))
        CALL(evt_msg_fmt_str, 1, LW(15), LW(15), LW(11))
        CALL(evt_msg_print_insert, 1, LW(15), 0, STRING("バッジ店員"), LW(14))
    END_SWITCH
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_22"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_LESS(LW(0), LW(13))
        CALL(evt_msg_print_add, 0, STRING("badgeshop_01"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(evt_pouch_add_item, LW(12), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_02"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(set_new_goods_list, LW(10), 0)
    CALL(evt_badgeShop_special_dec, LW(12))
    CALL(unitwin_set_bought, LW(10), LW(12))
    MULTIPLY(LW(13), -1)
    CALL(evt_pouch_add_coin, LW(13))
    CALL(evt_win_coin_wait, LW(8))
    WAIT_MS(200)
    CALL(evt_win_coin_off, LW(8))
    CALL(evt_msg_continue)
    RETURN
EVT_END()
#elif VERSION >= VERSION_JP
/**
 * Handler for the badge shop's display shelves ("S_item_07" to "S_item_11", see uwnobj_list):
 * when Mario picks a shelf item the clerk faces him, quotes the price,
 * and on a yes checks his coins and badge space, adds the badge, updates the shop stock and takes the coins.
 * The demo version is a simpler variant without the language switch.
 */
EVT_BEGIN(evt_badge_dummy)
    CALL(evt_mario_normalize)
    SET_VALUE(LW(10), LW(0))
    CALL(disp_off, LW(10))
    CALL(evt_set_dir_to_target, STRING("バッジ店員"), STRING("mario"))
    CALL(evt_mario_set_dir_npc, STRING("バッジ店員"))
    CALL(evt_win_coin_on, 0, LW(8))
    CALL(get_value, LW(10), LW(11), LW(12), LW(13), LW(14))
    CALL(evt_sub_get_language, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_insert, 0, STRING("badgeshop_00"), 0, STRING("バッジ店員"), LW(13), LW(11), LW(14))
    ELSE
        CALL(evt_msg_print_insert, 0, STRING("badgeshop_00"), 0, STRING("バッジ店員"), LW(11), LW(13), LW(14))
    END_IF
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_22"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_LESS(LW(0), LW(13))
        CALL(evt_msg_print_add, 0, STRING("badgeshop_01"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(evt_pouch_add_item, LW(12), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_msg_print_add, 0, STRING("badgeshop_02"))
        CALL(evt_win_coin_off, LW(8))
        RETURN
    END_IF
    CALL(set_new_goods_list, LW(10), 0)
    CALL(evt_badgeShop_special_dec, LW(12))
    CALL(unitwin_set_bought, LW(10), LW(12))
    MULTIPLY(LW(13), -1)
    CALL(evt_pouch_add_coin, LW(13))
    CALL(evt_win_coin_wait, LW(8))
    WAIT_MS(200)
    CALL(evt_win_coin_off, LW(8))
    CALL(evt_msg_continue)
    RETURN
EVT_END()
#else
/**
 * Handler for the badge shop's display shelves ("S_item_07" to "S_item_11", see uwnobj_list):
 * when Mario picks a shelf item the clerk faces him, quotes the price,
 * and on a yes checks his coins and badge space, adds the badge, updates the shop stock and takes the coins.
 * The demo version is a simpler variant without the language switch.
 */
EVT_BEGIN(evt_badge_dummy)
    SET_VALUE(LW(10), LW(0))
    CALL(disp_off, LW(10))
    CALL(evt_set_dir_to_target, STRING("バッジ店員"), STRING("mario"))
    CALL(evt_mario_set_dir_npc, STRING("バッジ店員"))
    IF_INT_EQUAL(GSWF(GSWF_GOR01_BADGE_SHOP_FIRST_TALK), 0)
        CALL_CHILD(first_shopping_evt)
        SET_VALUE(GSWF(GSWF_GOR01_BADGE_SHOP_FIRST_TALK), 1)
        RETURN
    END_IF
    CALL(unitwincoin_disp_onoff, 1)
    CALL(get_value, LW(10), LW(11), LW(12), LW(13), LW(14))
    CALL(evt_msg_print_insert, 0, STRING("badgeshop_00"), 0, STRING("バッジ店員"), LW(11), LW(13), LW(14))
    CALL(evt_msg_select, 0, STRING("badgeshop_24"))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_msg_continue)
        CALL(evt_msg_print, 0, STRING("badgeshop_22"), 0, STRING("バッジ店員"))
        CALL(unitwincoin_disp_onoff, 0)
        RETURN
    END_IF
    CALL(evt_pouch_get_coin, LW(0))
    IF_INT_LESS(LW(0), LW(13))
        CALL(evt_msg_continue)
        CALL(evt_msg_print, 0, STRING("badgeshop_01"), 0, STRING("バッジ店員"))
        CALL(unitwincoin_disp_onoff, 0)
        RETURN
    END_IF
    CALL(evt_pouch_add_item, LW(12), LW(0))
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_msg_continue)
        CALL(evt_msg_print, 0, STRING("badgeshop_02"), 0, STRING("バッジ店員"))
        CALL(unitwincoin_disp_onoff, 0)
        RETURN
    END_IF
    CALL(set_new_goods_list, LW(10), 0)
    SET_VALUE(LW(0), LW(10))
    CALL(evt_badgeShop_getBargainKind, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_badgeShop_special_dec, LW(12))
    ELSE
        CALL(evt_badgeShop_throw_dec, LW(12))
    END_IF
    MULTIPLY(LW(13), -1)
    CALL(evt_pouch_add_coin, LW(13))
    CALL(unitwincoin_wait)
    WAIT_MS(200)
    CALL(unitwincoin_disp_onoff, 0)
    CALL(evt_msg_continue)
    RETURN
EVT_END()
#endif

/**
 * Display pedestals of the badge shop upstairs in house 02: for each, the map object, its hit area and the
 * callback.
 */
UnitWinSell uwnobj_list[] = {
    {"S_item_07", "A_item_08", evt_badge_dummy},
    {"S_item_08", "A_item_09", evt_badge_dummy},
    {"S_item_09", "A_item_10", evt_badge_dummy},
    {"S_item_10", "A_item_11", evt_badge_dummy},
    {"S_item_11", "A_item_12", evt_badge_dummy},
    {0},
};

/**
 * Open callback for the badge shop (upstairs of house 02):
 * dips the music and ambience, then allocates the shop window
 * and fills it with the day's bargain badges (badgeShop_getBargainTable).
 */
EVT_BEGIN(evt_open_02_01_f2)
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_envoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_env_lpf, 0, 800)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_unitwin_alloc)
#else
    CALL(evt_unitwin_alloc, 1)
#endif
    CALL(badgeShop_getBargainTable, LW(0))
    CALL(evt_unitwin_selltable_setup, PTR(uwnobj_list), LW(0))
    RETURN
EVT_END()

/** Waits until Mario's controls are free again and then frees the badge shop window; run from evt_close_02_01_f2. */
EVT_BEGIN(evt_close_sub)
    CALL(mario_keyoff_wait)
    CALL(evt_unitwin_free)
    RETURN
EVT_END()

/** Close callback for the badge shop: brings the music and ambience back and starts evt_close_sub. */
EVT_BEGIN(evt_close_02_01_f2)
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    SPAWN_EVENT(evt_close_sub)
    RETURN
EVT_END()

/** Door of house 02's upstairs (the badge shop). */
DoorParam door_data_02_f2 = {
    0, // flags
    3, // type
    1, // se
    "S_ie_02_f2_doaD", // mapobj
    "A_ie_02_f2_doa02", // hitIn
    "A_ie_02_f2_doa01", // hitOut
    "S_ie_02_f2_soto", // outside
    NULL, // outsideHit
    "S_ie_02_f2_naka", // inside
    "A_ie_02_f2_C", // insideHit
    evt_door_02_00_f2, // evtIn
    NULL, // evtOut
    evt_wall_02_f2, // evtWall
    (const char**)badgemise_npc, // npcs
    NULL, NULL, // mobjs..items
    evt_open_02_01_f2, // evtOpen
    evt_close_02_01_f2, // evtClose
};

/**
 * Sets the colour of the bar's ground floor interior "S_i03_f1_naka" to a gray of level args[0] (0 black to 255
 * normal), for fading it in and out.
 */
static USER_FUNC(house03_f1_fade_func) {
    s32 v = evtGetValue(event, event->args[0]);

    mapGrpSetColor("S_i03_f1_naka", (GXColor){v, v, v, 0xFF});
    return EVT_RETURN_DONE;
}

/**
 * Sets the colour of the bar's upper floor interior "S_i03_f2_naka"
 * and its door "S_ie_03_f21_doa" to a gray of level args[0], for fading it in and out.
 */
static USER_FUNC(house03_f2_fade_func) {
    u8 v = evtGetValue(event, event->args[0]);

    mapGrpSetColor("S_i03_f2_naka", (GXColor){v, v, v, 0xFF});
    mapGrpSetColor("S_ie_03_f21_doa", (GXColor){v, v, v, 0xFF});
    return EVT_RETURN_DONE;
}

/**
 * Returns 1 in args[0] when the NPC Mario is currently able to talk to is Marco (Flavio), else 0.
 * Used to cut Marco's muttering when Mario is next to him.
 */
static USER_FUNC(chk_marco_fuki) {
    EvtWord* args = event->args;
    NpcEntry* npc;

    // The original passes marioGetPtr() to fbatNpcTalkCheck, which takes no arguments: the call stays.
    marioGetPtr();
    npc = fbatNpcTalkCheck();

    if (npc != NULL && strcmp(npc->description, "マルコ") == 0) {
        evtSetValue(event, args[0], 1);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[0], 0);
    return EVT_RETURN_DONE;
}

/**
 * Spawns a smoke puff effect at (args[0], args[1], args[2]);
 * used for the brawl cloud around the thieves in the Goombella scene.
 */
static USER_FUNC(maffia_kemuri) {
    EvtWord* args = event->args;
    f32 x = evtGetValue(event, args[0]);
    f32 y = evtGetValue(event, args[1]);
    f32 z = evtGetValue(event, args[2]);

    effKemuriEntry(1, x, y, z, 0.0f);
    return EVT_RETURN_DONE;
}

/**
 * Debug helper: with args[0] equal to 0, returns in args[1] a pointer to a string describing the current story
 * progress (search_evt_moji of GSW(GSW_STORY_PROGRESS)).
 */
static USER_FUNC(evt_osreport) {
    EvtWord* args = event->args;

    switch (evtGetValue(event, args[0])) {
        case 0:
            evtSetValue(event, args[1], (EvtWord)search_evt_moji(evtGetValue(event, GSW(GSW_STORY_PROGRESS))));
            break;
    }
    return EVT_RETURN_DONE;
}

/**
 * Per-frame NPC task: any NPC at or below y=-1000 (parked out of sight) gets NPC_FLAG_NO_DISPLAY
 * so it is not drawn, and the flag is removed once it comes back up.
 */
static s32 npc_process(void) {
    NpcWork* wp = npcGetWorkPtr();
    NpcEntry* npc = wp->entries;
    s32 i;

    for (i = 0; i < wp->total; i++, npc++) {
        if (npc->flags & NPC_FLAG_USED) {
            if (npc->position.y <= -1000.0f) {
                npc->flags |= NPC_FLAG_NO_DISPLAY;
            } else {
                npc->flags &= ~NPC_FLAG_NO_DISPLAY;
            }
        }
    }
    return 0;
}

/** Stops the regular event of the NPC named in args[0] and clears its move event. */
static USER_FUNC(delete_npc_regl_evt) {
    NpcEntry* npc = npcNameToPtr((const char*)evtGetValue(event, event->args[0]));

    if (npc->regularEvtId != 0) {
        evtDeleteID(npc->regularEvtId);
        npc->moveEvent = NULL;
        npc->regularEvtId = 0;
    }
    return EVT_RETURN_DONE;
}

/**
 * Runs while Mario is in the bar (house 03): each frame decides whether he is on the ground floor (y below 100)
 * or upstairs and sets the fade direction GW(14) and GW(15),
 * so the floor he is on fades in and the other one out.
 */
EVT_BEGIN(house03_f1f2_fade)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_GREATER_OR_EQUAL(LW(1), 100)
            SET_VALUE(GW(10), 2)
        ELSE
            SET_VALUE(GW(10), 1)
        END_IF
        IF_INT_EQUAL(GW(10), 1)
            SET_VALUE(GW(14), 1)
            SET_VALUE(GW(15), -1)
        ELSE
            SET_VALUE(GW(14), -1)
            SET_VALUE(GW(15), 1)
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Applies the fade level in LW(0) to the colour of Luigi and his friend (Torque) on the bar's ground floor,
 * depending on the story stage they stand in the bar.
 */
EVT_BEGIN(luigi_f1_fade_check)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG2_25_AFTER_THE_BOSS_BATTLE, STORY_STG3_31_GRUBBAS_PLANS)
        CASE_BETWEEN(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT, STORY_STG5_42_PIRATES_VS_X_NAUTS)
        CALL(evt_npc_set_color, STRING("ルイージ"), LW(0), LW(0), LW(0), 255)
        CALL(evt_npc_set_color, STRING("トルク"), LW(0), LW(0), LW(0), 255)
        CASE_GREATER_OR_EQUAL(STORY_STG7_20_LORD_CRUMP_DEFEATED)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Loops forever fading the ground floor of the bar (interior, Bob-omb sailor, Chusan,
 * plus Luigi's friends) toward white or black by 10 levels per frame, following GW(14).
 */
EVT_BEGIN(house03_f1_fade)
    LOOP(0)
        IF_INT_EQUAL(GW(14), 1)
            ADD(LW(0), 10)
            IF_INT_GREATER_OR_EQUAL(LW(0), 255)
                SET_VALUE(LW(0), 255)
            END_IF
        END_IF
        IF_INT_EQUAL(GW(14), -1)
            ADD(LW(0), -10)
            IF_INT_LESS_OR_EQUAL(LW(0), 0)
                SET_VALUE(LW(0), 0)
            END_IF
        END_IF
        CALL(house03_f1_fade_func, LW(0))
        CALL(evt_npc_set_color, STRING("水夫ボム兵"), LW(0), LW(0), LW(0), 255)
        CALL(evt_npc_set_color, STRING("チューさん２"), LW(0), LW(0), LW(0), 255)
        CALL_CHILD(luigi_f1_fade_check)
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Applies the fade level in LW(0) to the colour of Luigi and the second Kick on the bar's upper floor,
 * depending on the story stage.
 */
EVT_BEGIN(luigi_f2_fade_check)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_BETWEEN(STORY_STG2_25_AFTER_THE_BOSS_BATTLE, STORY_STG3_31_GRUBBAS_PLANS)
        CASE_BETWEEN(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT, STORY_STG5_42_PIRATES_VS_X_NAUTS)
        CASE_GREATER_OR_EQUAL(STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_npc_set_color, STRING("ルイージ"), LW(0), LW(0), LW(0), 255)
        CALL(evt_npc_set_color, STRING("キック２"), LW(0), LW(0), LW(0), 255)
    END_SWITCH
    RETURN
EVT_END()

/**
 * Loops forever fading the upper floor of the bar (interior, inn clerk, the old Toad,
 * plus Luigi's friends) toward white or black by 10 levels per frame, following GW(15).
 */
EVT_BEGIN(house03_f2_fade)
    LOOP(0)
        IF_INT_EQUAL(GW(15), 1)
            ADD(LW(0), 10)
            IF_INT_GREATER_OR_EQUAL(LW(0), 255)
                SET_VALUE(LW(0), 255)
            END_IF
        END_IF
        IF_INT_EQUAL(GW(15), -1)
            ADD(LW(0), -10)
            IF_INT_LESS_OR_EQUAL(LW(0), 0)
                SET_VALUE(LW(0), 0)
            END_IF
        END_IF
        CALL(house03_f2_fade_func, LW(0))
        CALL(evt_npc_set_color, STRING("宿店員"), LW(0), LW(0), LW(0), 255)
        CALL(evt_npc_set_color, STRING("キノじい"), LW(0), LW(0), LW(0), 255)
        CALL_CHILD(luigi_f2_fade_check)
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Loops forever playing the dripping water animation "sizuku" in the bar and its sound at the sink,
 * loud upstairs and quiet downstairs.
 */
EVT_BEGIN(house03_suiteki)
    LOOP(0)
        CALL(evt_map_playanim, STRING("sizuku"), 0, 0)
        CALL(evt_map_checkanim, STRING("sizuku"), LW(0), LW(1))
        WAIT_MS(LW(1))
        CALL(evt_mapobj_get_position, STRING("S_i03_f2_mizu"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG0_AMB_WATERDROP2"), LW(0), 300, LW(2), LW(3))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_GREATER(LW(1), 100)
            CALL(evt_snd_sfx_vol, LW(3), 127)
        ELSE
            CALL(evt_snd_sfx_vol, LW(3), 30)
        END_IF
    END_LOOP
    RETURN
EVT_END()

/**
 * Marco's (Flavio's) muttering while Mario is in the bar before Chapter 4's Flavio talk:
 * shows mac_4_004 over and over, cancelling it when Mario talks to him. Does nothing from STORY_STG4_32 on.
 */
EVT_BEGIN(marco_hitorigoto)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG4_32_CHATTING_WITH_FLAVIO)
        RETURN
    END_IF
    CALL(evt_mario_wait_movable)
    SET_VALUE(LSWF(2), 0)
    BEGIN_SIBLING_EVENT
        LOOP(0)
            CALL(chk_marco_fuki, LW(0))
            IF_INT_EQUAL(LW(0), 1)
                IF_INT_EQUAL(LSWF(2), 1)
                    CALL(evt_msg_close, STRING("mac_4_004"))
                END_IF
                SET_VALUE(LSWF(2), 0)
            ELSE
                SET_VALUE(LSWF(2), 1)
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    LOOP(0)
        LOOP(0)
            IF_INT_EQUAL(LSWF(2), 1)
                WAIT_FRAMES(1)
                IF_INT_EQUAL(LSWF(2), 1)
                    BREAK_LOOP
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_msg_print, 0, STRING("mac_4_004"), 0, STRING("マルコ"))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Door callback for house 03's ground floor (the bar):
 * rotates the door "S_ie_03_f1_doa" by LW(0) scaled by about 0.6.
 */
EVT_BEGIN(evt_door_03_00_f1)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5996094f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_03_f1_doa"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Second door callback for house 03's ground floor:
 * rotates the door "S_ie_03_f1_doa" the other way by half of LW(0).
 */
EVT_BEGIN(evt_door_03_01_f1)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_03_f1_doa"), LW(0), 0, 0)
    RETURN
EVT_END()

/**
 * Open callback for the bar's ground floor door:
 * dips the music and ambience, hides the roof of the upper floor, and starts the floor fading,
 * Marco's muttering and the dripping sound.
 */
EVT_BEGIN(house_03_f1_open)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_ie_03_f21_doa"), MAPOBJ_FLAG_NO_BLEND | MAPOBJ_FLAG_NO_BLEND2)
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_envoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_env_lpf, 0, 800)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_i03_f2_soto"), MAPOBJ_FLAG_HIDE)
    BEGIN_INLINE_EVENT
        CALL(evt_door_end_wait)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_i03_f2_soto"), MAPOBJ_FLAG_HIDE)
    END_INLINE_EVENT
    SET_VALUE(GW(10), 1)
    SET_VALUE(GW(14), 0)
    SET_VALUE(GW(15), 0)
    SPAWN_EVENT_GET_ID(PTR(house03_f1f2_fade), GW(11))
    SET_VALUE(LW(0), 255)
    SPAWN_EVENT_GET_ID(PTR(house03_f1_fade), GW(12))
    SET_VALUE(LW(0), 0)
    SPAWN_EVENT_GET_ID(PTR(house03_f2_fade), GW(13))
    SPAWN_EVENT_GET_ID(PTR(marco_hitorigoto), GW(0))
    SPAWN_EVENT_GET_ID(PTR(house03_suiteki), GW(7))
    RETURN
EVT_END()

/**
 * Close callback for the bar's ground floor door:
 * restores the doors, the music and ambience, and stops the fading, muttering and dripping events.
 */
EVT_BEGIN(house_03_f1_close)
    BEGIN_INLINE_EVENT
        WAIT_MS(1600)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_ie_03_f1_doa"), MAPOBJ_FLAG_NO_BLEND | MAPOBJ_FLAG_NO_BLEND2)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_ie_03_f21_doa"), MAPOBJ_FLAG_NO_BLEND | MAPOBJ_FLAG_NO_BLEND2)
        CALL(evt_mapobj_color, 1, STRING("S_ie_03_f21_doa"), 255, 255, 255, 255)
    END_INLINE_EVENT
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    SET_VALUE(GW(10), 0)
    DELETE_EVENT(GW(0))
    CALL(evt_msg_close, STRING("mac_4_004"))
    DELETE_EVENT(GW(7))
    DELETE_EVENT(GW(11))
    DELETE_EVENT(GW(12))
    DELETE_EVENT(GW(13))
    RETURN
EVT_END()

/**
 * Wall callback for the bar from the ground floor:
 * tilts the front wall pieces "S_ie_03_f1B", "S_i03_f2_sitaB" and "S_i03_f2_ueB" open by LW(0) degrees.
 */
EVT_BEGIN(evt_wall_03_f1)
    SET_FLOAT_VALUE(LW(2), LW(0))
    SET_FLOAT_VALUE(LW(3), LW(0))
    SET_FLOAT_VALUE(LW(4), LW(0))
    SET_FLOAT_VALUE(LW(5), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(1.0f))
    MULTIPLY_FLOAT(LW(3), FLOAT(0.5f))
    MULTIPLY_FLOAT(LW(4), FLOAT(-1.0f))
    MULTIPLY_FLOAT(LW(5), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_03_f1B"), LW(2), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_i03_f2_sitaB"), LW(3), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_i03_f2_ueB"), LW(4), 0, 0)
    RETURN
EVT_END()

/**
 * NPCs of house 03 kept lit while Mario is inside: the bar owner (Podley), the old Toad and the others
 * listed.
 */
static const char* door_data_03_npc[] = {
    "マスター",
    "キノじい",
    "宿店員",
    "チューさん２",
    "水夫ボム兵",
    "マルコ",
    "ルイージ",
    "トルク",
    "キック２",
    NULL,
};

/** Field items of house 03 kept lit while Mario is inside: the Skull Gem. */
const char* door_data_03_item[] = {
    "ドクロジュエル",
    NULL,
};

/** Door of house 03's ground floor (the bar). */
DoorParam door_data_03_f1 = {
    0, // flags
    3, // type
    1, // se
    "S_ie_03_f1_doa", // mapobj
    "A_ie_03_f1_doa02", // hitIn
    "A_ie_03_f1_doa01", // hitOut
    "S_ie_03_soto", // outside
    NULL, // outsideHit
    "S_ie_03_naka", // inside
    NULL, // insideHit
    evt_door_03_00_f1, // evtIn
    evt_door_03_01_f1, // evtOut
    evt_wall_03_f1, // evtWall
    door_data_03_npc, // npcs
    NULL, // mobjs
    door_data_03_item, // items
    house_03_f1_open, // evtOpen
    house_03_f1_close, // evtClose
};

/** Door callback for the bar's upper floor: rotates the door "S_ie_03_f21_doa" by LW(0) scaled by about 0.6. */
EVT_BEGIN(evt_door_03_00_f2)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5996094f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_03_f21_doa"), 0, LW(0), 0)
    RETURN
EVT_END()

/**
 * Open callback for the bar's upper floor door:
 * dips the music and ambience and starts the floor fading, Marco's muttering and the dripping sound,
 * with the upper floor visible first.
 */
EVT_BEGIN(house_03_f2_open)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_ie_03_f1_doa"), MAPOBJ_FLAG_NO_BLEND | MAPOBJ_FLAG_NO_BLEND2)
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_envoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_env_lpf, 0, 800)
    SET_VALUE(GW(10), 2)
    SET_VALUE(GW(14), 0)
    SET_VALUE(GW(15), 0)
    SPAWN_EVENT_GET_ID(PTR(house03_f1f2_fade), GW(11))
    SET_VALUE(LW(0), 0)
    SPAWN_EVENT_GET_ID(PTR(house03_f1_fade), GW(12))
    SET_VALUE(LW(0), 255)
    SPAWN_EVENT_GET_ID(PTR(house03_f2_fade), GW(13))
    SPAWN_EVENT_GET_ID(PTR(marco_hitorigoto), GW(0))
    SPAWN_EVENT_GET_ID(PTR(house03_suiteki), GW(7))
    RETURN
EVT_END()

/**
 * Close callback for the bar's upper floor door:
 * restores the doors, the music and ambience, and stops the fading, muttering and dripping events.
 */
EVT_BEGIN(house_03_f2_close)
#if VERSION >= VERSION_US
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_i03_f1_naka"), MAPOBJ_FLAG_HIDE)
#endif
    BEGIN_INLINE_EVENT
        WAIT_MS(1600)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_ie_03_f1_doa"), MAPOBJ_FLAG_NO_BLEND | MAPOBJ_FLAG_NO_BLEND2)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_ie_03_f21_doa"), MAPOBJ_FLAG_NO_BLEND | MAPOBJ_FLAG_NO_BLEND2)
    END_INLINE_EVENT
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    SET_VALUE(GW(10), 0)
    DELETE_EVENT(GW(0))
    CALL(evt_msg_close, STRING("mac_4_004"))
    DELETE_EVENT(GW(7))
    DELETE_EVENT(GW(11))
    DELETE_EVENT(GW(12))
    DELETE_EVENT(GW(13))
    RETURN
EVT_END()

/**
 * Wall callback for the bar from the upper floor:
 * tilts the front wall pieces and the ground floor door open by LW(0) degrees.
 */
EVT_BEGIN(evt_wall_03_f2)
    SET_FLOAT_VALUE(LW(2), LW(0))
    SET_FLOAT_VALUE(LW(3), LW(0))
    SET_FLOAT_VALUE(LW(4), LW(0))
    SET_FLOAT_VALUE(LW(5), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(1.0f))
    MULTIPLY_FLOAT(LW(3), FLOAT(0.5f))
    MULTIPLY_FLOAT(LW(4), FLOAT(-1.0f))
    MULTIPLY_FLOAT(LW(5), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_03_f1B"), LW(2), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_i03_f2_sitaB"), LW(3), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_i03_f2_ueB"), LW(4), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_03_f1_doa"), LW(5), 0, 0)
    RETURN
EVT_END()

/** Door of house 03's upstairs. */
DoorParam door_data_03_f2 = {
    0, // flags
    3, // type
    1, // se
    "S_ie_03_f21_doa", // mapobj
    "S_ie_03_f2_doa02", // hitIn
    "S_ie_03_f2_doa01", // hitOut
    "S_ie_03_soto", // outside
    NULL, // outsideHit
    "S_ie_03_naka", // inside
    NULL, // insideHit
    evt_door_03_00_f2, // evtIn
    NULL, // evtOut
    evt_wall_03_f2, // evtWall
    door_data_03_npc, // npcs
    NULL, // mobjs
    door_data_03_item, // items
    house_03_f2_open, // evtOpen
    house_03_f2_close, // evtClose
};

/**
 * Door animation callback of the house 04 door (the thieves' house):
 * rotates the door "S_ie_04_doa" about Y by 0.6 times the value in LW(0).
 */
static EVT_BEGIN(evt_door_04_00)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.5996094f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_04_doa"), 0, LW(0), 0)
    RETURN
EVT_END()

/** Second door callback of house 04: rotates the door "S_ie_04_doa" about X by -0.5 times the value in LW(0). */
static EVT_BEGIN(evt_door_04_01)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.5f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_04_doa"), LW(0), 0, 0)
    RETURN
EVT_END()

/**
 * Wall callback of house 04: rotates the wall pieces "S_ie_04uB"
 * and "S_ie_04sB" about X by LW(0) in opposite directions.
 */
static EVT_BEGIN(evt_wall_04)
    SET_FLOAT_VALUE(LW(2), LW(0))
    SET_FLOAT_VALUE(LW(3), LW(0))
    MULTIPLY_FLOAT(LW(2), FLOAT(1.0f))
    MULTIPLY_FLOAT(LW(3), FLOAT(-1.0f))
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_04uB"), LW(2), 0, 0)
    CALL(evt_mapobj_rotate, 1, STRING("S_ie_04sB"), LW(3), 0, 0)
    RETURN
EVT_END()

/**
 * Called when the house 04 door opens: dips the music and ambience to 50 percent,
 * low-passes the ambience and turns off blending on the cockroach object S_goki_01.
 */
static EVT_BEGIN(evt_door_04_open)
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_envoff, PSND_FADE_DIP_TO(50))
    CALL(evt_snd_env_lpf, 0, 800)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_goki_01"), MAPOBJ_FLAG_NO_BLEND | MAPOBJ_FLAG_NO_BLEND2)
    RETURN
EVT_END()

/**
 * Called when the house 04 door closes: brings the music and ambience back and removes the low-pass;
 * if Mario has confronted the thief (GSWF_GOR01_THIEF_CONFRONTED) it sets GSWF_GOR01_THIEF_LEFT_HOUSE.
 */
static EVT_BEGIN(evt_door_04_close)
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_envon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
    CALL(evt_snd_env_lpf, 0, 0)
    IF_INT_EQUAL(GSWF(GSWF_GOR01_THIEF_CONFRONTED), 1)
        SET_VALUE(GSWF(GSWF_GOR01_THIEF_LEFT_HOUSE), 1)
    END_IF
    RETURN
EVT_END()

/** NPCs of house 04 kept lit while Mario is inside: the thief. */
static const char* door_data_04_npc[] = {
    "盗賊",
    NULL,
};

/** Field items of house 04 kept lit while Mario is inside: the Star Piece (item_01). */
static const char* door_data_04_item[] = {
    "item_01",
    NULL,
};

/** Door of house 04 (the thieves' house). */
static DoorParam door_data_04 = {
    0, // flags
    3, // type
    1, // se
    "S_ie_04_doa", // mapobj
    "A_ie_04_doa02", // hitIn
    "A_ie_04_doa01", // hitOut
    "S_ie_04_soto", // outside
    NULL, // outsideHit
    "S_ie_04_naka", // inside
    "A_ie_04_C", // insideHit
    evt_door_04_00, // evtIn
    evt_door_04_01, // evtOut
    evt_wall_04, // evtWall
    door_data_04_npc, // npcs
    NULL, // mobjs
    door_data_04_item, // items
    evt_door_04_open, // evtOpen
    evt_door_04_close, // evtClose
};

/**
 * Loops forever, swinging the map object S_rop (the rope of the plaza's gallows: koushukei-dai, 絞首刑台) back and
 * forth between +10 and -10 degrees about X, one second each way.
 */
static EVT_BEGIN(koushukei_dai)
    LOOP(0)
        CALL(evt_sub_intpl_msec_init, 11, 10, -10, 1000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
            CALL(evt_mapobj_rotate, 0, STRING("S_rop"), LW(0), 0, 0)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        WAIT_FRAMES(1)
        CALL(evt_sub_intpl_msec_init, 11, -10, 10, 1000)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
            CALL(evt_mapobj_rotate, 0, STRING("S_rop"), LW(0), 0, 0)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/** Item pedestals of the shop in house 02: for each, the map object and its hit area. */
static ShopObj obj_list[] = {
    {"S_item_01", "A_item_01"},
    {"S_item_02", "A_item_02"},
    {"S_item_03", "A_item_03"},
    {"S_item_04", "A_item_04"},
    {"S_item_05", "A_item_05"},
    {"S_item_06", "A_item_06"},
};

/**
 * Goods of the item shop in house 02, item and price in coins: Mushroom 5, Honey Syrup 5, Tasty Tonic 3,
 * Fire Flower 10, Sleepy Sheep 8, Fright Mask 5. Sold before the Contact Lens arrives, and after it is
 * delivered whenever Mario already has every Super Luigi book the story stage allows.
 */
static ShopItem goods_list[] = {
    {ITEM_MUSHROOM, 5},
    {ITEM_HONEY_SYRUP, 5},
    {ITEM_TASTY_TONIC, 3},
    {ITEM_FIRE_FLOWER, 10},
    {ITEM_SLEEPY_SHEEP, 8},
    {ITEM_FRIGHT_MASK, 5},
};

/**
 * Goods of the item shop once the Contact Lens has arrived and until it is delivered:
 * the Contact Lens (10 coins) takes the Mushroom's place.
 */
ShopItem goods_list2[] = {
    {ITEM_CONTACT_LENS, 10},
    {ITEM_HONEY_SYRUP, 5},
    {ITEM_TASTY_TONIC, 3},
    {ITEM_FIRE_FLOWER, 10},
    {ITEM_SLEEPY_SHEEP, 8},
    {ITEM_FRIGHT_MASK, 5},
};

/**
 * Goods of the item shop after the lens is delivered while Mario has no Super Luigi book and the story allows
 * one: the first book, Super Luigi (64 coins), takes the Mushroom's place.
 */
ShopItem goods_luigi1[] = {
    {ITEM_SUPER_LUIGI1, 64},
    {ITEM_HONEY_SYRUP, 5},
    {ITEM_TASTY_TONIC, 3},
    {ITEM_FIRE_FLOWER, 10},
    {ITEM_SLEEPY_SHEEP, 8},
    {ITEM_FRIGHT_MASK, 5},
};

/**
 * Goods of the item shop while Mario has one Super Luigi book: Super Luigi 2 (128 coins) replaces the
 * Mushroom.
 */
ShopItem goods_luigi2[] = {
    {ITEM_SUPER_LUIGI2, 128},
    {ITEM_HONEY_SYRUP, 5},
    {ITEM_TASTY_TONIC, 3},
    {ITEM_FIRE_FLOWER, 10},
    {ITEM_SLEEPY_SHEEP, 8},
    {ITEM_FRIGHT_MASK, 5},
};

/**
 * Goods of the item shop while Mario has two Super Luigi books: Super Luigi 3 (128 coins) replaces the
 * Mushroom.
 */
ShopItem goods_luigi3[] = {
    {ITEM_SUPER_LUIGI3, 128},
    {ITEM_HONEY_SYRUP, 5},
    {ITEM_TASTY_TONIC, 3},
    {ITEM_FIRE_FLOWER, 10},
    {ITEM_SLEEPY_SHEEP, 8},
    {ITEM_FRIGHT_MASK, 5},
};

/**
 * Goods of the item shop while Mario has three Super Luigi books: Super Luigi 4 (128 coins) replaces the
 * Mushroom.
 */
ShopItem goods_luigi4[] = {
    {ITEM_SUPER_LUIGI4, 128},
    {ITEM_HONEY_SYRUP, 5},
    {ITEM_TASTY_TONIC, 3},
    {ITEM_FIRE_FLOWER, 10},
    {ITEM_SLEEPY_SHEEP, 8},
    {ITEM_FRIGHT_MASK, 5},
};

/**
 * Goods of the item shop while Mario has four Super Luigi books: Super Luigi 5 (256 coins) replaces the
 * Mushroom.
 */
ShopItem goods_luigi5[] = {
    {ITEM_SUPER_LUIGI5, 256},
    {ITEM_HONEY_SYRUP, 5},
    {ITEM_TASTY_TONIC, 3},
    {ITEM_FIRE_FLOWER, 10},
    {ITEM_SLEEPY_SHEEP, 8},
    {ITEM_FRIGHT_MASK, 5},
};

/**
 * Coins the item shop in house 02 pays when Mario sells these items (its stock plus a few others, such as the
 * Whacka Bump for 55); they replace the item table's sell prices only while the sell menu runs.
 */
static ShopDb trade_list[] = {
    {ITEM_MUSHROOM, 2, 0},
    {ITEM_HONEY_SYRUP, 2, 0},
    {ITEM_TASTY_TONIC, 1, 0},
    {ITEM_FIRE_FLOWER, 5, 0},
    {ITEM_SLEEPY_SHEEP, 4, 0},
    {ITEM_FRIGHT_MASK, 2, 0},
    {ITEM_WHACKA_BUMP, 55, 0},
    {ITEM_COCONUT, 2, 0},
    {ITEM_DRIED_BOUQUET, 12, 0},
    {ITEM_MYSTIC_EGG, 5, 0},
    {ITEM_GOLDEN_LEAF, 4, 0},
    {ITEM_KEEL_MANGO, 4, 0},
    {ITEM_FRESH_PASTA, 53, 0},
    {ITEM_CAKE_MIX, 8, 0},
    {ITEM_HOT_SAUCE, 11, 0},
    {ITEM_TURTLEY_LEAF, 2, 0},
    {ITEM_HORSETAIL, 2, 0},
    {ITEM_PEACHY_PEACH, 4, 0},
    {0},
};

/** Shopkeeper of the item shop in house 02: name and the shop's message keys. */
static ShopperData35 shopper_data = {
    "店長", // name
    NULL, NULL, // fook_evt..buy_evt
    {"gor_shop1_00", "gor_shop1_01", "gor_shop1_02", "gor_shop1_03", "gor_shop1_04", "gor_shop1_05", "gor_shop1_06", "gor_shop1_07", "gor_shop1_08", "gor_shop1_09", "gor_shop1_10", "gor_shop1_11", "gor_shop1_12", "gor_shop1_13", "gor_shop1_14", "gor_shop1_15", "gor_shop1_16", "gor_shop1_17", "gor_shop1_18", "gor_shop1_19", "gor_shop1_20", "gor_shop1_21", "gor_shop1_22", "gor_shop1_23", "gor_shop1_24", "gor_shop1_25", "gor_shop1_26", "gor_shop1_27", "gor_shop1_28", "gor_shop1_29", "gor_shop1_30", "gor_shop1_31", "gor_shop1_32", "gor_shop1_33", "gor_shop1_34"}, // msgs
};

/**
 * Sets up the item shop in house 02.
 * Before the lens is delivered it sells goods_list (goods_list2 with the Contact Lens once it has arrived);
 * afterwards it sells goods_luigi1 to goods_luigi5 in turn, adding the next Super Luigi book each time,
 * until Mario owns as many as the story stage allows.
 */
EVT_BEGIN(gor_01_shop_setup)
    IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_DELIVERED), 0)
        IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_ARRIVED), 0)
            CALL(evt_shop_setup, PTR(obj_list), PTR(goods_list), PTR(&shopper_data), PTR(trade_list))
        ELSE
            CALL(evt_shop_setup, PTR(obj_list), PTR(goods_list2), PTR(&shopper_data), PTR(trade_list))
        END_IF
    ELSE
        CALL(evt_pouch_check_item, ITEM_SUPER_LUIGI1, LW(1))
        CALL(evt_pouch_check_item, ITEM_SUPER_LUIGI2, LW(2))
        CALL(evt_pouch_check_item, ITEM_SUPER_LUIGI3, LW(3))
        CALL(evt_pouch_check_item, ITEM_SUPER_LUIGI4, LW(4))
        CALL(evt_pouch_check_item, ITEM_SUPER_LUIGI5, LW(5))
        SWITCH(GSW(GSW_STORY_PROGRESS))
            CASE_LESS(STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
            SET_VALUE(LW(11), 0)
            CASE_LESS(STORY_STG5_43_X_NAUTS_RETREAT)
            SET_VALUE(LW(11), 1)
            CASE_LESS(STORY_STG6_54_WELCOME_BACK)
            SET_VALUE(LW(11), 2)
            CASE_LESS(STORY_STG7_20_LORD_CRUMP_DEFEATED)
            SET_VALUE(LW(11), 3)
            CASE_LESS(STORY_STG8_16_SHADOW_QUEEN)
            SET_VALUE(LW(11), 4)
            CASE_DEFAULT
            SET_VALUE(LW(11), 5)
        END_SWITCH
        SET_VALUE(LW(12), 0)
        IF_INT_NOT_EQUAL(LW(1), 0)
            ADD(LW(12), 1)
        END_IF
        IF_INT_NOT_EQUAL(LW(2), 0)
            ADD(LW(12), 1)
        END_IF
        IF_INT_NOT_EQUAL(LW(3), 0)
            ADD(LW(12), 1)
        END_IF
        IF_INT_NOT_EQUAL(LW(4), 0)
            ADD(LW(12), 1)
        END_IF
        IF_INT_NOT_EQUAL(LW(5), 0)
            ADD(LW(12), 1)
        END_IF
        IF_INT_GREATER_OR_EQUAL(LW(12), LW(11))
            SET_VALUE(LW(10), PTR(goods_list))
        ELSE
            SWITCH(LW(12))
                CASE_EQUAL(0)
                SET_VALUE(LW(10), PTR(goods_luigi1))
                CASE_EQUAL(1)
                SET_VALUE(LW(10), PTR(goods_luigi2))
                CASE_EQUAL(2)
                SET_VALUE(LW(10), PTR(goods_luigi3))
                CASE_EQUAL(3)
                SET_VALUE(LW(10), PTR(goods_luigi4))
                CASE_EQUAL(4)
                SET_VALUE(LW(10), PTR(goods_luigi5))
            END_SWITCH
        END_IF
        CALL(evt_shop_setup, PTR(obj_list), LW(10), PTR(&shopper_data), PTR(trade_list))
    END_IF
    RETURN
EVT_END()

/**
 * Inn setup (evt_kinopio_setup): the price of a night (5 coins), the bed, the camera and the clerk's position
 * and the inn's message keys.
 */
static KinopioData kino_dt = {
    0, // breakfastItem
    {0}, // breakfastPos
    5, // ryoukin
    {368.0f, 170.0f, -295.0f}, // bed
    {330.0f, 154.0f, -250.0f}, // bedside
    {130.0f, 370.0f, -79.0f, 313.0f, 220.0f, -264.0f}, // cam
    -30.0f, // bedDeg
    {227.0f, 154.0f, -200.0f}, // npcTalk
    "宿店員", // npcName
    {"yado_00", "yado_01", "yado_02", "yado_03", "yado_04", "yado_05", "yado_06", "yado_07", "yado_08", "yado_09", "yado_10", "yado_11", "yado_12", "yado_13"}, // msg
    NULL, NULL, // toBedEvt..fromBedEvt
};

/**
 * Animation of the bar's front door "S_ie_03_f1_doa" opening to 108 degrees and closing again over a second,
 * with door sounds and its interior hidden; clears GF(0) when done.
 */
EVT_BEGIN(bar_door_anime)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_ie_03_naka"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_get_position, STRING("S_ie_03_f1_doa"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_OPEN1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_sub_intpl_msec_init, 11, 0, 108, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        CALL(evt_mapobj_rotate, 1, STRING("S_ie_03_f1_doa"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(500)
    CALL(evt_sub_intpl_msec_init, 11, 108, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        CALL(evt_mapobj_rotate, 1, STRING("S_ie_03_f1_doa"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mapobj_get_position, STRING("S_ie_03_f1_doa"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_DOOR_SHUT1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_ie_03_naka"), MAPOBJ_FLAG_HIDE)
    SET_VALUE(GF(0), 0)
    RETURN
EVT_END()

/**
 * Spawns the four NPCs of Goombella's joining scene (two mafia thugs and two bandit-gang members)
 * and parks them below the map.
 */
EVT_BEGIN(christine_nakama_init)
    CALL(evt_npc_entry, STRING("マフィア１"), STRING("c_m_buka"))
    CALL(evt_npc_set_tribe, STRING("マフィア１"), STRING("マフィア"))
    CALL(evt_npc_entry, STRING("マフィア２"), STRING("c_m_buka"))
    CALL(evt_npc_set_tribe, STRING("マフィア２"), STRING("マフィア"))
    CALL(evt_npc_entry, STRING("盗賊団１"), STRING("c_monban"))
    CALL(evt_npc_set_tribe, STRING("盗賊団１"), STRING("盗賊団"))
    CALL(evt_npc_entry, STRING("盗賊団２"), STRING("c_monban"))
    CALL(evt_npc_set_tribe, STRING("盗賊団２"), STRING("盗賊団"))
    CALL(evt_npc_set_position, STRING("マフィア１"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("マフィア２"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("盗賊団１"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("盗賊団２"), 0, -1000, 0)
    RETURN
EVT_END()

/**
 * Cutscene when Goombella joins the party (STORY_STG0_07_GOOMBELLA_JOINS):
 * she and Mario meet in the plaza, she kisses him in thanks,
 * they look at the Magical Map and the old Toad explains the town;
 * Goombella then gives Mario the partner lecture (all_party_lecture),
 * the plaza music returns and christine_nakama_after starts.
 */
EVT_BEGIN(christine_nakama)
    SET_VALUE(GF(10), 1)
    // The mafia brawl starts in the background; Goombella and Mario walk into the plaza.
    SPAWN_EVENT(maffia_assault)
    CALL(evt_mario_clear_party, 1)
    CALL(evt_cam3d_evt_set, 0, 134, 984, 0, 38, 442, 0, 11)
    CALL(evt_party_stop, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_pouch_party_join, 1)
        CALL(evt_mario_set_party_pos, 0, 1, 25, 0, 625)
        CALL(evt_party_set_dir, 0, 270, 0)
        CALL(evt_party_move_pos2, 0, 25, 500, FLOAT(150.0f))
        WAIT_FRAMES(1)
        CALL(evt_party_set_dir, 0, 270, 200)
    END_INLINE_EVENT
    CALL(evt_mario_set_dir, 90, 0, 0)
    CALL(evt_mario_dispflag_onoff, 1, 4)
    CALL(evt_mario_set_pos, -25, 0, 625)
    CALL(evt_mario_mov_pos2, -25, 500, FLOAT(150.0f))
    CALL(evt_mario_adjust_dir)
    CALL(evt_mario_dispflag_onoff, 0, 4)
    CALL(evt_npc_set_position, STRING("キノじい"), 160, 0, 500)
    CALL(evt_npc_set_ry, STRING("キノじい"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("キノじい"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("キノじい"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    BEGIN_INLINE_EVENT
        WAIT_MS(60)
        CALL(evt_mario_set_dir, 90, 200, 0)
    END_INLINE_EVENT
    WAIT_MS(500)
    // Goombella greets Mario and thanks him with a kiss.
    CALL(evt_msg_print_party, STRING("mac_0_034"))
    CALL(evt_cam3d_evt_set, 0, 55, 800, 0, 45, 440, 400, 11)
    WAIT_MS(400)
    CALL(evt_msg_print_party, STRING("mac_0_034_00"))
    CALL(evt_party_move_pos2, 0, -8, 495, FLOAT(120.0f))
    WAIT_MS(100)
    CALL(evt_party_set_pose, 0, STRING("PKR_A_2A"))
    CALL(evt_snd_sfxon, STRING("SFX_STG0_KURI_KISS1"), 0)
    WAIT_MS(300)
    CALL(evt_mario_set_pose, STRING("M_N_5B"))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), 15)
    ADD(LW(1), 35)
    ADD(LW(2), 10)
    CALL(evt_snd_sfxon, STRING("SFX_STG0_KURI_KISS2"), 0)
    CALL(evt_eff, 0, STRING("kiss"), 1, LW(0), LW(1), LW(2), 45, 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_party_move_pos2, 0, 25, 500, FLOAT(120.0f))
    CALL(evt_party_set_dir, 0, 270, 200)
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    // Mario is flustered; the two talk, then Goombella reads Princess Peach's Magical Map.
    CALL(evt_msg_print_party, STRING("mac_0_035"))
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(1000)
    CALL(evt_msg_print_party, STRING("mac_0_036"))
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("mac_0_037"))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_2"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_eff_fukidashi, 0, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    SET_VALUE(GF(10), 0)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("mac_0_038"))
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("mac_0_039"))
    CALL(evt_mario_set_pose, STRING("M_C_3"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(0), 20)
    ADD(LW(1), 20)
    ADD(LW(2), 10)
    // The Magical Map appears in Mario's hands while Goombella examines it.
    CALL(evt_item_entry, STRING("item00"), ITEM_MAGICAL_MAP_LARGE, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED, -1, 0)
    CALL(evt_item_flag_on, STRING("item00"), ITEM_FLAG_NO_TOUCH)
    CALL(evt_item_set_scale, STRING("item00"), FLOAT(0.5498047f))
    WAIT_MS(500)
    CALL(evt_party_move_pos2, 0, 0, 500, FLOAT(120.0f))
    WAIT_MS(500)
    CALL(evt_eff_fukidashi, 3, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    CALL(evt_msg_print_party, STRING("mac_0_040"))
    CALL(evt_item_delete, STRING("item00"))
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("mac_0_041"))
    CALL(evt_mario_set_dir, 90, 200, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_party_set_dir, 0, 90, 200)
        WAIT_MS(500)
        CALL(evt_party_move_pos2, 0, 25, 500, FLOAT(120.0f))
    END_INLINE_EVENT
    // Toadsworth runs up and is delighted to find Mario.
    CALL(evt_msg_print, 0, STRING("mac_0_042"), 0, STRING("キノじい"))
    SET_VALUE(GF(10), 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam3d_evt_set, 25, 55, 800, 25, 45, 440, 800, 11)
    END_INLINE_EVENT
    WAIT_MS(300)
    CALL(evt_npc_move_position, STRING("キノじい"), 75, 500, 0, FLOAT(55.0f), 0)
    // Toadsworth tells of Peach's letter and treasure map and asks where she is.
    CALL(evt_msg_print, 0, STRING("mac_0_043"), 0, STRING("キノじい"))
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("mac_0_044"), 0, STRING("キノじい"))
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    // Toadsworth says Peach has not come back; Mario jumps in alarm.
    CALL(evt_msg_print, 0, STRING("mac_0_045"), 0, STRING("キノじい"))
    CALL(evt_mario_set_pose, STRING("M_N_H"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_mario_dispflag_onoff, 1, 2)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED2_3"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mario_jump_pos, LW(0), LW(1), LW(2), 200, 1, -1000)
    WAIT_MS(500)
    CALL(evt_mario_dispflag_onoff, 0, 2)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    WAIT_WHILE(GF(11))
    // Toadsworth decides to wait at the inn and walks off to it.
    CALL(evt_msg_print, 0, STRING("mac_0_046"), 0, STRING("キノじい"))
    CALL(evt_mario_set_pose, STRING("M_I_2"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("mac_0_047"), 0, STRING("キノじい"))
    CALL(evt_mario_set_pose, STRING("M_I_G"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print, 0, STRING("mac_0_047_01"), 0, STRING("キノじい"))
    CALL(evt_npc_flag_onoff, 0, STRING("キノじい"), NPC_FLAG_TALK_ANIM)
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("キノじい"), 93, -46, 0, FLOAT(120.0f), 0)
        CALL(evt_npc_set_ry, STRING("キノじい"), 90)
        WAIT_MS(500)
        SPAWN_EVENT(bar_door_anime)
        CALL(evt_npc_move_position, STRING("キノじい"), 74, -25, 0, FLOAT(180.0f), 0)
        WAIT_MS(500)
        CALL(evt_npc_move_position, STRING("キノじい"), 105, -95, 0, FLOAT(180.0f), 0)
        WAIT_WHILE(GF(0))
        CALL(evt_npc_set_position, STRING("キノじい"), 320, 153, -200)
        CALL(evt_npc_set_ry, STRING("キノじい"), 270)
        CALL(evt_npc_flag_onoff, 0, STRING("キノじい"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_npc_get_position, STRING("キノじい"), LW(0), LW(1), LW(2))
        ADD(LW(1), 40)
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        // Toadsworth puffs and mutters as he goes upstairs.
        CALL(evt_msg_print, 0, STRING("mac_0_047_02"), 0, STRING("キノじい"))
        WAIT_MS(500)
        CALL(evt_npc_get_position, STRING("キノじい"), LW(0), LW(1), LW(2))
        ADD(LW(1), 40)
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_msg_print, 0, STRING("mac_0_047_02"), 0, STRING("キノじい"))
        WAIT_MS(1000)
    END_INLINE_EVENT
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, 0, 55, 800, 0, 45, 440, 500, 11)
    WAIT_MS(1000)
    CALL(evt_party_set_dir, 0, 270, 200)
    WAIT_MS(200)
    // Goombella suggests they search together and explains how partners work.
    CALL(evt_msg_print_party, STRING("mac_0_048"))
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("mac_0_049"))
    CALL(evt_mario_set_pose, STRING("M_I_Z"))
    WAIT_MS(1000)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("mac_0_050"))
    CALL(evt_mario_set_pose, STRING("M_N_2"))
    WAIT_MS(500)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("mac_0_051"))
    CALL(evt_cam3d_evt_set, 27, 45, 800, 27, 35, 440, 800, 11)
    WAIT_MS(800)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(9), 1)
    // The partner lecture plays; afterwards the plaza music returns.
    CALL_CHILD(all_party_lecture)
    CALL(evt_snd_bgmon_f, PSND_FADE_IN | PSND_FADE_OUT, STRING("BGM_STG0_GOR1"), 2000)
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG0_GOR1"))
    // Goombella's closing words, then control returns to Mario.
    CALL(evt_msg_print_party, STRING("mac_0_053"))
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_dispflag_onoff, 0, MARIO_DISP_FLAG_DIR_LOCK)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    // Story advances: Goombella has joined the party.
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG0_07_GOOMBELLA_JOINS)
    SPAWN_EVENT(christine_nakama_after)
    RETURN
EVT_END()

/**
 * Makes the two bandit-gang NPCs spin around twice (720 degrees over 0.36 seconds) with fight sounds
 * and smoke puffs, as part of the mafia brawl.
 */
EVT_BEGIN(maffia_turn)
    CALL(evt_snd_sfxon, STRING("SFX_STG0_THIEF_FIGHT1"), 0)
    CALL(evt_npc_get_position, STRING("盗賊団１"), LW(0), LW(1), LW(2))
    CALL(maffia_kemuri, LW(0), LW(1), LW(2))
    CALL(evt_npc_get_position, STRING("盗賊団２"), LW(0), LW(1), LW(2))
    CALL(maffia_kemuri, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon, STRING("SFX_STG0_THIEF_FIGHT2"), 0)
    CALL(evt_sub_intpl_msec_init, 0, 0, 720, 360)
    LOOP(0)
        SET_VALUE(LW(10), LW(0))
        IF_INT_GREATER_OR_EQUAL(LW(10), 360)
            SUBTRACT(LW(10), 360)
        END_IF
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_npc_set_rotate, STRING("盗賊団１"), 0, LW(10), 0)
        CALL(evt_npc_set_rotate, STRING("盗賊団２"), 0, LW(10), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_set_rotate, STRING("盗賊団１"), 0, 0, 0)
    CALL(evt_npc_set_rotate, STRING("盗賊団２"), 0, 0, 0)
    RETURN
EVT_END()

/**
 * Background brawl for Goombella's joining scene:
 * two mafia thugs run in and fight two bandit-gang members with smoke,
 * spinning and knock-down animations and a shouted exchange (mac_0_054 to mac_0_061), until the gang runs off.
 * Waits on GF(10) to sync with the main scene.
 */
EVT_BEGIN(maffia_assault)
#if VERSION >= VERSION_JP
    SET_VALUE(GF(11), 1)
#endif
    // Scene setup: the thugs are placed off to the south, out of sight.
    CALL(evt_npc_set_position, STRING("マフィア１"), 75, 0, -400)
    CALL(evt_npc_set_ry, STRING("マフィア１"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("マフィア１"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("マフィア１"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_set_position, STRING("マフィア２"), 95, 0, -390)
    CALL(evt_npc_set_ry, STRING("マフィア２"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("マフィア２"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("マフィア２"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    WAIT_WHILE(GF(10))
    // The two mafia thugs run in from the south.
    SET_VALUE(GF(10), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("マフィア２"), 45, -390, 0, FLOAT(300.0f), 0)
        WAIT_MS(1300)
        CALL(evt_npc_move_position, STRING("マフィア２"), 25, -390, 0, FLOAT(300.0f), 0)
        CALL(evt_npc_set_ry, STRING("マフィア２"), 90)
        CALL(evt_npc_move_position, STRING("マフィア２"), 25, -60, 0, FLOAT(300.0f), 0)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("マフィア１"), 25, -400, 0, FLOAT(300.0f), 0)
    WAIT_MS(1500)
    CALL(evt_npc_move_position, STRING("マフィア１"), 5, -390, 0, FLOAT(300.0f), 0)
    CALL(evt_npc_set_ry, STRING("マフィア１"), 90)
    CALL(evt_npc_move_position, STRING("マフィア１"), 5, -60, 0, FLOAT(300.0f), 0)
    WAIT_WHILE(GF(10))
    SET_VALUE(GF(10), 1)
    // The two bandit-gang members arrive from the east and the groups run at each other.
    CALL(evt_npc_set_position, STRING("盗賊団１"), 225, 0, 10)
    CALL(evt_npc_set_ry, STRING("盗賊団１"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("盗賊団１"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("盗賊団１"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_set_position, STRING("盗賊団２"), 255, 0, 30)
    CALL(evt_npc_set_ry, STRING("盗賊団２"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("盗賊団２"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("盗賊団２"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    SET_VALUE(GF(12), 1)
    SET_VALUE(GF(13), 1)
    SET_VALUE(GF(14), 1)
    SET_VALUE(GF(15), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("盗賊団１"), 125, 10, 0, FLOAT(100.0f), 0)
        SET_VALUE(GF(12), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("盗賊団２"), 165, 30, 0, FLOAT(100.0f), 0)
        SET_VALUE(GF(13), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("マフィア１"), 5, 15, 0, FLOAT(360.0f), 0)
        CALL(evt_npc_move_position, STRING("マフィア１"), 90, 15, 0, FLOAT(360.0f), 0)
        SET_VALUE(GF(14), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("マフィア２"), 25, 30, 0, FLOAT(360.0f), 0)
        CALL(evt_npc_move_position, STRING("マフィア２"), 200, 35, 0, FLOAT(360.0f), 0)
        CALL(evt_npc_set_ry, STRING("マフィア２"), 270)
        SET_VALUE(GF(15), 0)
    END_INLINE_EVENT
    WAIT_WHILE(GF(12))
    WAIT_WHILE(GF(13))
    WAIT_WHILE(GF(14))
    WAIT_WHILE(GF(15))
    CALL(evt_npc_flag_onoff, 0, STRING("マフィア１"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_flag_onoff, 0, STRING("マフィア２"), NPC_FLAG_MOVE_ANIM)
    BEGIN_INLINE_EVENT
        // The thugs beat up the bandits, spinning them around in the brawl.
        CALL(evt_npc_set_anim, STRING("マフィア２"), STRING("A_1"))
        CALL(evt_npc_move_position, STRING("マフィア２"), 180, 15, 0, FLOAT(360.0f), 0)
        CALL(evt_npc_move_position, STRING("マフィア２"), 200, 15, 0, FLOAT(360.0f), 0)
        WAIT_MS(500)
        CALL(evt_npc_move_position, STRING("マフィア２"), 180, 15, 0, FLOAT(360.0f), 0)
        CALL(evt_npc_move_position, STRING("マフィア２"), 200, 15, 0, FLOAT(360.0f), 0)
        WAIT_MS(500)
        CALL(evt_npc_move_position, STRING("マフィア２"), 180, 15, 0, FLOAT(360.0f), 0)
        CALL(evt_npc_move_position, STRING("マフィア２"), 200, 15, 0, FLOAT(360.0f), 0)
        CALL(evt_npc_set_anim, STRING("マフィア２"), STRING("S_1"))
    END_INLINE_EVENT
    CALL(evt_npc_set_anim, STRING("マフィア１"), STRING("A_1"))
    CALL(evt_npc_move_position, STRING("マフィア１"), 110, 15, 0, FLOAT(360.0f), 0)
    CALL(evt_npc_set_anim, STRING("盗賊団１"), STRING("D_1"))
    CALL(evt_npc_set_anim, STRING("盗賊団２"), STRING("D_1"))
    SPAWN_EVENT(maffia_turn)
    CALL(evt_npc_move_position, STRING("マフィア１"), 90, 15, 0, FLOAT(360.0f), 0)
    WAIT_MS(500)
    CALL(evt_npc_move_position, STRING("マフィア１"), 110, 15, 0, FLOAT(360.0f), 0)
    SPAWN_EVENT(maffia_turn)
    CALL(evt_npc_move_position, STRING("マフィア１"), 90, 15, 0, FLOAT(360.0f), 0)
    WAIT_MS(500)
    CALL(evt_npc_move_position, STRING("マフィア１"), 110, 15, 0, FLOAT(360.0f), 0)
    SPAWN_EVENT(maffia_turn)
    CALL(evt_npc_move_position, STRING("マフィア１"), 90, 15, 0, FLOAT(360.0f), 0)
    CALL(evt_npc_set_anim, STRING("マフィア１"), STRING("S_1"))
    // The first bandit yells as he takes a hit.
    CALL(evt_msg_print, 0, STRING("mac_0_054"), 0, STRING("盗賊団１"))
    CALL(evt_npc_set_anim, STRING("盗賊団１"), STRING("K_1"))
    WAIT_MS(500)
    CALL(evt_npc_set_anim, STRING("盗賊団１"), STRING("Y_1"))
    WAIT_MS(500)
    CALL(evt_npc_flag_onoff, 1, STRING("マフィア１"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("マフィア２"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_set_rotate_offset, STRING("盗賊団１"), 0, 0, 0)
    CALL(evt_sub_intpl_msec_init, 0, 0, 90, 150)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_npc_set_rotate, STRING("盗賊団１"), LW(0), 0, 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    // A bandit is knocked down and the mafia thugs taunt them.
    CALL(evt_snd_sfxon, STRING("SFX_STG0_THIEF_DOWN1"), 0)
    SET_VALUE(LW(10), STRING("盗賊団２"))
    CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(3), LW(0))
    ADD(LW(3), -20)
    CALL(evt_npc_move_position, LW(10), LW(3), LW(2), 0, FLOAT(200.0f), 0)
    WAIT_MS(200)
    CALL(evt_npc_set_anim, STRING("盗賊団２"), STRING("D_1"))
    CALL(evt_msg_print, 0, STRING("mac_0_055"), 0, STRING("盗賊団２"))
    CALL(evt_npc_set_anim, STRING("盗賊団２"), STRING("S_1"))
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(10), STRING("マフィア１"))
        CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
        SET_VALUE(LW(3), LW(0))
        ADD(LW(3), -20)
        CALL(evt_npc_move_position, LW(10), LW(3), LW(2), 0, FLOAT(200.0f), 0)
    END_INLINE_EVENT
    SET_VALUE(LW(10), STRING("マフィア２"))
    CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(3), LW(0))
    ADD(LW(3), -95)
    CALL(evt_npc_set_ry, LW(10), 90)
    CALL(evt_npc_move_position, LW(10), LW(3), LW(2), 0, FLOAT(200.0f), 0)
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("mac_0_056"), 0, STRING("マフィア１"))
    WAIT_MS(200)
    CALL(evt_msg_print, 0, STRING("mac_0_057"), 0, STRING("マフィア２"))
    SET_VALUE(GF(14), 1)
    SET_VALUE(GF(15), 1)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(10), STRING("マフィア１"))
        CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
        SET_VALUE(LW(3), LW(0))
        ADD(LW(3), -300)
        CALL(evt_npc_set_ry, LW(10), 270)
        CALL(evt_npc_move_position, LW(10), LW(3), LW(2), 0, FLOAT(360.0f), 0)
        CALL(evt_npc_set_position, LW(10), 0, -1000, 0)
        SET_VALUE(GF(14), 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(10), STRING("マフィア２"))
        CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
        SET_VALUE(LW(3), LW(0))
        ADD(LW(3), -300)
        CALL(evt_npc_set_ry, LW(10), 270)
        CALL(evt_npc_move_position, LW(10), LW(3), LW(2), 0, FLOAT(360.0f), 0)
        CALL(evt_npc_set_position, LW(10), 0, -1000, 0)
        SET_VALUE(GF(15), 0)
    END_INLINE_EVENT
    WAIT_WHILE(GF(14))
    WAIT_WHILE(GF(15))
    WAIT_MS(1000)
    CALL(evt_npc_set_anim, STRING("盗賊団２"), STRING("D_1"))
    // The bandits get up, curse the thugs and run off to the east.
    CALL(evt_msg_print, 0, STRING("mac_0_058"), 0, STRING("盗賊団２"))
    CALL(evt_npc_set_anim, STRING("盗賊団２"), STRING("S_1"))
    CALL(evt_sub_intpl_msec_init, 0, 90, 0, 150)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_npc_set_rotate, STRING("盗賊団１"), LW(0), 0, 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_set_anim, STRING("盗賊団１"), STRING("K_1"))
    CALL(evt_msg_print, 0, STRING("mac_0_059"), 0, STRING("盗賊団１"))
    WAIT_MS(200)
    CALL(evt_npc_set_anim, STRING("盗賊団２"), STRING("D_1"))
    CALL(evt_msg_print, 0, STRING("mac_0_060"), 0, STRING("盗賊団２"))
    CALL(evt_npc_set_anim, STRING("盗賊団２"), STRING("S_1"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("mac_0_061"), 0, STRING("盗賊団１"))
    WAIT_MS(200)
    BEGIN_INLINE_EVENT
        SET_VALUE(LW(10), STRING("盗賊団１"))
        CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
        SET_VALUE(LW(3), LW(0))
        ADD(LW(3), 300)
        CALL(evt_npc_set_ry, LW(10), 90)
        CALL(evt_npc_move_position, LW(10), LW(3), LW(2), 0, FLOAT(120.0f), 0)
        CALL(evt_npc_set_position, LW(10), 0, -1000, 0)
    END_INLINE_EVENT
    SET_VALUE(LW(10), STRING("盗賊団２"))
    CALL(evt_npc_get_position, LW(10), LW(0), LW(1), LW(2))
    SET_VALUE(LW(3), LW(0))
    ADD(LW(3), 300)
    CALL(evt_npc_set_ry, LW(10), 90)
    CALL(evt_npc_move_position, LW(10), LW(3), LW(2), 0, FLOAT(120.0f), 0)
    CALL(evt_npc_set_position, LW(10), 0, -1000, 0)
#if VERSION >= VERSION_JP
    // The brawl is over; the main scene may continue.
    SET_VALUE(GF(11), 0)
#endif
    RETURN
EVT_END()

/**
 * After Goombella has joined: waits until Mario walks to the save block area at the east end of the plaza (x >=
 * 440) and then has her remark on it (mac_0_061_01), setting GSWF_GOR01_GOOMBELLA_SAVE_TALK_DONE.
 * Does nothing if save blocks are switched off or the block was already used.
 */
EVT_BEGIN(christine_nakama_after)
    CALL(evt_sub_get_system_flag, LW(0))
    IF_BITS_SET(LW(0), GLOBAL_FLAG_SAVE_BLOCKS_OFF)
        RETURN
    END_IF
    LOOP(0)
        IF_INT_EQUAL(GSWF(GSWF_SAVE_BLOCK_USED_AFTER_GOOMBELLA), 1)
            RETURN
        END_IF
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_GREATER_OR_EQUAL(LW(0), 440)
            IF_INT_GREATER_OR_EQUAL(LW(2), -10)
                IF_INT_LESS_OR_EQUAL(LW(2), 190)
                    BREAK_LOOP
                END_IF
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_eff_fukidashi, 3, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 270, 200, 0)
    END_INLINE_EVENT
    CALL(evt_msg_print, 0, STRING("mac_0_061_01"), 0, STRING("party"))
    SET_VALUE(GSWF(GSWF_GOR01_GOOMBELLA_SAVE_TALK_DONE), 1)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Loops forever copying the position of the dummy NPC "ダミー" to the item block "mobj_box00"
 * so the block follows the NPC's jump.
 */
EVT_BEGIN(box_copy)
    LOOP(0)
        CALL(evt_npc_get_position, STRING("ダミー"), LW(0), LW(1), LW(2))
        CALL(evt_mobj_set_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Waits for Mario to jump-spin (hammer) at the spot near x 315 to 360, y 60 to 78, z -40 to 0,
 * then makes the hidden item block "mobj_box00" fall down to (275, 0, 75) with smoke puffs,
 * following a dummy NPC.
 */
EVT_BEGIN(ultrahammer_check)
    CALL(evt_npc_entry, STRING("ダミー"), STRING("c_kinopio"))
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("ダミー"), LW(0), LW(1), LW(2))
    CALL(evt_npc_flag_onoff, 1, STRING("ダミー"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("ダミー"), NPC_FLAG_HIDDEN)
    LOOP(0)
        SET_VALUE(LW(1), 0)
        CALL(evt_mario_get_motion, LW(10))
        IF_INT_EQUAL(LW(10), 20)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        END_IF
        IF_INT_GREATER_OR_EQUAL(LW(0), 315)
            IF_INT_LESS_OR_EQUAL(LW(0), 360)
                IF_INT_GREATER_OR_EQUAL(LW(1), 60)
                    IF_INT_LESS_OR_EQUAL(LW(1), 78)
                        IF_INT_GREATER_OR_EQUAL(LW(2), -40)
                            IF_INT_LESS_OR_EQUAL(LW(2), 0)
                                BREAK_LOOP
                            END_IF
                        END_IF
                    END_IF
                END_IF
            END_IF
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mobj_flag_onoff, 0, STRING("mobj_box00"), MOBJ_FLAG_FALL)
    SPAWN_EVENT(box_copy)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_TBOX_FALL1"), LW(0), LW(1), LW(2), LW(10))
    CALL(evt_npc_jump_position_nohit, STRING("ダミー"), 275, 0, 75, 500, FLOAT(100.0f))
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    ADD(LW(0), -25)
    ADD(LW(1), -5)
    ADD(LW(2), 30)
    CALL(evt_eff, 0, STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    ADD(LW(0), 0)
    ADD(LW(1), -5)
    ADD(LW(2), 30)
    CALL(evt_eff, 0, STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    ADD(LW(0), 25)
    ADD(LW(1), -5)
    ADD(LW(2), 30)
    CALL(evt_eff, 0, STRING("kemuri_test"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_cam_shake, 4, FLOAT(0.0f), FLOAT(0.01953125f), 500)
    END_INLINE_EVENT
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxoff, LW(10))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_TBOX_FALL2"), LW(0), LW(1), LW(2), 0)
    SET_VALUE(GSWF(GSWF_GOR01_ULTRA_HAMMER_CHEST_FALLEN), 1)
    RETURN
EVT_END()

/**
 * Item block event for "mobj_box00" once it has fallen:
 * when Mario opens it he is handed the Ultra Hammer as an important item (with the key item lecture)
 * and control returns when the pickup ends.
 */
EVT_BEGIN(ultrahammer_get)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("mobj_box00"), LW(0), LW(1), LW(2))
    CALL(lect_juyoitem_rel_set, PTR(all_juyoitem_lecture_rel))
    CALL(evt_item_entry, STRING("hammer"), ITEM_ULTRA_HAMMER, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("mobj_box00"))
    CALL(evt_item_get_important_item, STRING("hammer"))
    CALL(evt_item_get_item, STRING("hammer"))
    CALL(evt_item_get_item_end_wait, STRING("hammer"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Debug bulletin board (front side, "kj_omote"):
 * shows the message stored on the board for the current story step, or, if none (or several) match,
 * a Japanese debug note saying so with the event number. Not meant to appear in normal play.
 */
EVT_BEGIN(keijiban_omote_joho)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(keijiban_data_alloc, STRING("kj_omote"))
    CALL(keijiban_joho_check, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(keijiban_joho_makelabel, 0, LW(1))
        CALL(evt_msg_print, 0, LW(1), 0, 0)
    ELSE
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_osreport, 0, LW(1))
            CALL(evt_msg_print, 1, STRING("<plate>\nゆうこうな　データが\n見つかりませんでした\nメッセージを　とうろく　してください\n<key>\n<scrl_auto>\n<once_stop>\n"), 0, 0)
            CALL(evt_msg_print_add_insert, 1, STRING("げんざいの　イベントばんごうは\n『%s』\nです\n<key>"), LW(1))
        ELSE
            CALL(evt_osreport, 0, LW(1))
            CALL(evt_msg_print, 1, STRING("<plate>\nゆうこうな　データが\nじゅうふくして　みつかりました\nゆうこうな　メッセージは　１つにしてください\n<key>\n<scrl_auto>\n<once_stop>"), 0, 0)
            SET_VALUE(LW(2), 0)
            SET_VALUE(LW(3), LW(0))
            LOOP(LW(0))
                CALL(keijiban_joho_makelabel, LW(2), LW(1))
                CALL(evt_msg_print_add_insert, 1, STRING("『%s』\n<key>\n<scrl_auto>\n<once_stop>\n"), LW(1))
                ADD(LW(2), 1)
            END_LOOP
            CALL(evt_msg_print_add_insert, 1, STRING("いじょう　%dこが\nじゅうふくしている　メッセージです\n<key>"), LW(3))
        END_IF
    END_IF
    CALL(keijiban_data_free)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/** Same as keijiban_omote_joho for the back of the bulletin board ("kj_ura"). */
EVT_BEGIN(keijiban_ura_joho)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(keijiban_data_alloc, STRING("kj_ura"))
    CALL(keijiban_joho_check, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(keijiban_joho_makelabel, 0, LW(1))
        CALL(evt_msg_print, 0, LW(1), 0, 0)
    ELSE
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_osreport, 0, LW(1))
            CALL(evt_msg_print, 1, STRING("<plate>\nゆうこうな　データが\n見つかりませんでした\nメッセージを　とうろく　してください\n<key>\n<scrl_auto>\n<once_stop>\n"), 0, 0)
            CALL(evt_msg_print_add_insert, 1, STRING("げんざいの　イベントばんごうは\n『%s』\nです\n<key>"), LW(1))
        ELSE
            CALL(evt_osreport, 0, LW(1))
            CALL(evt_msg_print, 1, STRING("<plate>\nゆうこうな　データが\nじゅうふくして　みつかりました\nゆうこうな　メッセージは　１つにしてください\n<key>\n<scrl_auto>\n<once_stop>"), 0, 0)
            SET_VALUE(LW(2), 0)
            SET_VALUE(LW(3), LW(0))
            LOOP(LW(0))
                CALL(keijiban_joho_makelabel, LW(2), LW(1))
                CALL(evt_msg_print_add_insert, 1, STRING("『%s』\n<key>\n<scrl_auto>\n<once_stop>\n"), LW(1))
                ADD(LW(2), 1)
            END_LOOP
            CALL(evt_msg_print_add_insert, 1, STRING("いじょう　%dこが\nじゅうふくしている　メッセージです\n<key>"), LW(3))
        END_IF
    END_IF
    CALL(keijiban_data_free)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Loops forever: hides the town wall pieces "S_gai_kabe_k" and "S_gai_kabe_k_01"
 * while Mario is in the front (z > -100) so they do not block the view,
 * and shows them again when he goes behind the gate.
 */
EVT_BEGIN(gate_disp)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_GREATER(LW(2), -100)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_gai_kabe_k"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_gai_kabe_k_01"), MAPOBJ_FLAG_HIDE)
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_gai_kabe_k"), MAPOBJ_FLAG_HIDE)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_gai_kabe_k_01"), MAPOBJ_FLAG_HIDE)
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Loops forever, making the cockroach object S_goki_01 scuttle around:
 * it picks random loiter targets, avoids villagers (gor_villager_urouro_check_func),
 * moves in 50 steps and faces its direction of travel, then rests 0.5 to 3.5 seconds.
 */
static EVT_BEGIN(gor_goki1_urouro)
    SET_VALUE(LW(4), 0)
    SET_VALUE(LW(5), 0)
    LOOP(0)
        SET_VALUE(LW(0), LW(4))
        SET_VALUE(LW(1), LW(5))
        CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
        CALL(evt_npc_add_dirdist, LW(0), LW(1), LW(3), FLOAT(50.0f))
        CALL(evt_gor_villager_urouro_check_func, LW(0), LW(1), 0, 0, FLOAT(70.0f))
        CALL(evt_sub_get_dir, LW(4), LW(5), LW(0), LW(1), LW(3))
        IF_INT_GREATER(LW(3), 180)
            SET_VALUE(LW(6), 0)
        ELSE
            SET_VALUE(LW(6), 180)
        END_IF
        CALL(evt_goki_sub_intpl_init, 13, LW(4), LW(0), LW(5), LW(1), 50)
        LOOP(50)
            CALL(evt_goki_sub_intpl_get_value)
            SET_VALUE(LW(2), LW(0))
            SET_VALUE(LW(3), LW(1))
            ADD(LW(2), 480)
            ADD(LW(3), -180)
            CALL(evt_mapobj_trans, 1, STRING("S_goki_01"), LW(2), 0, LW(3))
            CALL(evt_mapobj_rotate, 1, STRING("S_goki_01"), 0, LW(6), 0)
            WAIT_FRAMES(1)
        END_LOOP
        SET_VALUE(LW(4), LW(0))
        SET_VALUE(LW(5), LW(1))
        CALL(evt_sub_random, 3000, LW(2))
        ADD(LW(2), 500)
        WAIT_MS(LW(2))
    END_LOOP
    RETURN
EVT_END()

/**
 * Same as gor_goki1_urouro for the second cockroach object,
 * S_goki_02 (a different base offset and avoidance distance).
 */
static EVT_BEGIN(gor_goki2_urouro)
    SET_VALUE(LW(4), 0)
    SET_VALUE(LW(5), 0)
    LOOP(0)
        SET_VALUE(LW(0), LW(4))
        SET_VALUE(LW(1), LW(5))
        CALL(evt_npc_get_loiter_dir, LW(3), FLOAT(120.0f), FLOAT(240.0f))
        CALL(evt_npc_add_dirdist, LW(0), LW(1), LW(3), FLOAT(50.0f))
        CALL(evt_gor_villager_urouro_check_func, LW(0), LW(1), 0, 0, FLOAT(65.0f))
        CALL(evt_sub_get_dir, LW(4), LW(5), LW(0), LW(1), LW(3))
        IF_INT_GREATER(LW(3), 180)
            SET_VALUE(LW(6), 0)
        ELSE
            SET_VALUE(LW(6), 180)
        END_IF
        CALL(evt_goki_sub_intpl_init, 13, LW(4), LW(0), LW(5), LW(1), 50)
        LOOP(50)
            CALL(evt_goki_sub_intpl_get_value)
            SET_VALUE(LW(2), LW(0))
            SET_VALUE(LW(3), LW(1))
            ADD(LW(2), -515)
            ADD(LW(3), -250)
            CALL(evt_mapobj_trans, 1, STRING("S_goki_02"), LW(2), 0, LW(3))
            CALL(evt_mapobj_rotate, 1, STRING("S_goki_02"), 0, LW(6), 0)
            WAIT_FRAMES(1)
        END_LOOP
        SET_VALUE(LW(4), LW(0))
        SET_VALUE(LW(5), LW(1))
        CALL(evt_sub_random, 3000, LW(2))
        ADD(LW(2), 500)
        WAIT_MS(LW(2))
    END_LOOP
    RETURN
EVT_END()

/**
 * Enters Kammy Koopa (Baba, model "c_kamek_be", tribe Kamek Baba) hidden below the map facing 270,
 * with move and talk animations, status icon off and width 30, height 40.
 */
static EVT_BEGIN(koopa_npc_entry)
    CALL(evt_npc_entry, STRING("ババ"), STRING("c_kamek_be"))
    CALL(evt_npc_set_tribe, STRING("ババ"), STRING("カメックババ"))
    CALL(evt_npc_set_position, STRING("ババ"), 0, -1000, 0)
    CALL(evt_npc_set_ry, STRING("ババ"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("ババ"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_status_onoff, 1, STRING("ババ"), 2)
    CALL(evt_npc_set_width, STRING("ババ"), 30)
    CALL(evt_npc_set_height, STRING("ババ"), 40)
    RETURN
EVT_END()

/**
 * Chapter 6 interlude with Bowser in the Rogueport plaza (STORY_STG6_55_01_PEACH_TEC_DELETED):
 * villagers flee in panic, Bowser looks around, Kammy Koopa flies in and the two argue, Luigi peeks out.
 * Ends by setting STORY_STG6_55_02_BOWSER_ROGUEPORT and changing to kpa_05.
 */
EVT_BEGIN(gor_01_koopa_evt)
    // Chapter 6 interlude: Bowser stomps into the plaza and the townsfolk are cleared out of his way.
    CALL(evt_mario_key_onoff, 0)
    CALL(delete_npc_regl_evt, STRING("ロテン１"))
    CALL(delete_npc_regl_evt, STRING("クリボー１"))
    CALL(delete_npc_regl_evt, STRING("クリボー２"))
    CALL(delete_npc_regl_evt, STRING("クリボー３"))
    CALL(delete_npc_regl_evt, STRING("チューさん１"))
    CALL(evt_mario_set_pos, 400, 0, 100)
    CALL(evt_npc_set_position, STRING("クリボー１"), 269, 0, 65)
    CALL(evt_npc_set_position, STRING("ロテン１"), 98, 0, 17)
    CALL(evt_npc_set_position, STRING("チューさん１"), 145, 0, 109)
    CALL(evt_npc_set_position, STRING("クリボー２"), 0, -1000, 0)
    CALL(evt_koopa_weary, 1)
    CALL(evt_npc_set_ry, STRING("クリボー１"), 90)
    CALL(evt_npc_set_ry, STRING("ロテン１"), 90)
    CALL(evt_npc_set_ry, STRING("チューさん１"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("クリボー１"), NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("ロテン１"), NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("チューさん１"), NPC_FLAG_INTANGIBLE)
    CALL(evt_cam3d_evt_set, 200, 160, 616, 200, 65, 74, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_fade_end_wait)
    BEGIN_INLINE_EVENT
        // The Goomba, the vendor and the other townsfolk scream and run off in all directions.
        WAIT_MS(200)
        CALL(evt_msg_print, 0, STRING("kpa_stg6_000"), 0, STRING("クリボー１"))
        CALL(evt_npc_status_onoff, 1, STRING("クリボー１"), 2)
        SPAWN_EVENT_GET_ID(PTR(evt_sub_stopwatch), LW(0))
        CALL(evt_npc_move_position, STRING("クリボー１"), 187, 65, 0, FLOAT(90.0f), 0)
        CALL(evt_sub_get_stopwatch, LW(0), LW(1))
        CALL(evt_npc_set_ry, STRING("クリボー１"), 90)
        WAIT_MS(300)
        CALL(evt_npc_move_position, STRING("クリボー１"), 142, 65, 0, FLOAT(90.0f), 0)
        CALL(evt_npc_set_ry, STRING("クリボー１"), 90)
        WAIT_MS(500)
        CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_PEAPLE_ESCAPE1"), 142, 0, 65, 0)
        CALL(evt_npc_move_position, STRING("クリボー１"), 142, 185, 0, FLOAT(150.0f), 0)
        CALL(evt_npc_move_position, STRING("クリボー１"), 380, 185, 0, FLOAT(150.0f), 0)
        CALL(evt_npc_flag_onoff, 1, STRING("クリボー１"), NPC_FLAG_HIDDEN)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_msg_print, 0, STRING("kpa_stg6_001"), 0, STRING("ロテン１"))
        CALL(evt_npc_status_onoff, 1, STRING("ロテン１"), 2)
        CALL(evt_npc_move_position, STRING("ロテン１"), 27, -55, 0, FLOAT(120.0f), 0)
        CALL(evt_npc_move_position, STRING("ロテン１"), 27, -250, 0, FLOAT(120.0f), 0)
        CALL(evt_npc_flag_onoff, 1, STRING("ロテン１"), NPC_FLAG_HIDDEN)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_msg_print, 0, STRING("kpa_stg6_002"), 0, STRING("チューさん１"))
        CALL(evt_npc_move_position, STRING("チューさん１"), 145, 340, 0, FLOAT(120.0f), 0)
        CALL(evt_npc_flag_onoff, 1, STRING("チューさん１"), NPC_FLAG_HIDDEN)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1300)
        CALL(evt_npc_get_position, STRING("ロテン１"), LW(0), LW(1), LW(2))
        CALL(evt_npc_get_position, STRING("チューさん１"), LW(3), LW(4), LW(5))
        ADD(LW(0), LW(3))
        ADD(LW(1), LW(4))
        ADD(LW(2), LW(5))
        DIVIDE(LW(0), 2)
        DIVIDE(LW(1), 2)
        DIVIDE(LW(2), 2)
        CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_PEAPLE_ESCAPE1"), LW(0), LW(1), LW(2), 0)
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_KOOPA_SATIATED2_1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_mov_pos2, 200, 100, FLOAT(60.0f))
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_2"), STRING("KPA_T_4"))
    // Bowser grumbles that he has no Crystal Stars and cannot find the Princess.
    CALL(evt_msg_print, 0, STRING("kpa_stg6_003"), 0, STRING("mario"))
    CALL(evt_npc_set_position, STRING("ババ"), 600, 280, 75)
    WAIT_MS(500)
    // Kammy Koopa calls out to Bowser and flies in on her broom.
    CALL(evt_msg_print, 0, STRING("kpa_stg6_004"), 0, STRING("ババ"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_KOOPA_SURPRISED1_1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_eff_fukidashi, 0, STRING(""), 0, 0, 0, 0, 0, 0, 0, 0, 60)
    CALL(evt_koopa_weary, 0)
    CALL(kpa_chg_pose, STRING("KPA_S_1"))
    CALL(evt_mario_set_dir, 90, 500, 0)
    WAIT_MS(700)
    CALL(evt_cam3d_evt_set, -225, 120, 755, 416, 150, -12, 0, 11)
    WAIT_FRAMES(1)
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_get_position, STRING("ババ"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_KAMEBABA_FLY1"), LW(0), LW(1), LW(2), 0)
            WAIT_FRAMES(10)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_kamek_kemuri1, STRING("ババ"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_glide_position, STRING("ババ"), 302, 25, 75, 0, FLOAT(80.0f), FLOAT(40.0f), 11, 0)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    WAIT_MS(2000)
    // Kammy reports that the scouts found a hidden underground chamber.
    CALL(evt_cam3d_evt_set, 255, 164, 587, 255, 120, 341, 2600, 11)
    WAIT_MS(3500)
    CALL(evt_msg_print, 0, STRING("kpa_stg6_005"), 0, STRING("ババ"))
    WAIT_MS(500)
    CALL(evt_npc_set_autotalkpose, STRING("mario"), STRING("KPA_S_1"), STRING("KPA_T_1"))
    // Bowser is pleased; Kammy adds that the Hammer Bros. cannot break in.
    CALL(evt_msg_print, 0, STRING("kpa_stg6_006"), 0, STRING("mario"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("kpa_stg6_007"), 0, STRING("ババ"))
    WAIT_MS(500)
    // Bowser says he will blast through, and Kammy flies off.
    CALL(evt_msg_print, 0, STRING("kpa_stg6_008"), 0, STRING("mario"))
    SET_VALUE(GF(0), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_npc_get_position, STRING("ババ"), LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_KUPPA_KAMEBABA_FLY1"), LW(0), LW(1), LW(2), 0)
            WAIT_FRAMES(10)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_npc_flag_onoff, 1, STRING("ババ"), NPC_FLAG_SKIP_HIT_ATTR4 | NPC_FLAG_INTANGIBLE)
        CALL(evt_npc_kamek_move_position, STRING("ババ"), 600, 100, 10, 0, FLOAT(120.0f), 0)
        SET_VALUE(GF(0), 1)
    END_INLINE_EVENT
    CALL(evt_mario_mov_pos2, 500, 100, FLOAT(120.0f))
    WAIT_MS(2000)
    // Luigi runs out, peeks around at the commotion and runs back.
    CALL(evt_npc_set_position, STRING("ルイージ"), 50, 0, 100)
    CALL(evt_npc_status_onoff, 1, STRING("ルイージ"), 2)
    CALL(evt_npc_move_position, STRING("ルイージ"), 200, 100, 0, 60, 0)
    WAIT_MS(300)
    CALL(evt_npc_reverse_ry, STRING("ルイージ"))
    WAIT_MS(500)
    CALL(evt_npc_reverse_ry, STRING("ルイージ"))
    WAIT_MS(500)
    CALL(evt_eff_fukidashi, 1, STRING(""), STRING("ルイージ"), 1, 0, 0, 0, 0, 0, 0, 60)
    WAIT_MS(1200)
    CALL(evt_npc_move_position, STRING("ルイージ"), 50, 100, 0, 60, 0)
    WAIT_MS(1000)
    // Story advances and the scene moves to the Bowser section.
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG6_55_02_BOWSER_ROGUEPORT)
    CALL(evt_bero_mapchange, STRING("kpa_05"), STRING(""))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

void envSetYamiView(Mtx mtx);

/**
 * Sets the "darkness" view matrix used by the Shadow Queen's darkening of Rogueport from a look-at at depth
 * args[0]. Used only by the Chapter 8 darkness scenes.
 */
static USER_FUNC(yami_view) {
    f32 z = evtGetFloat(event, event->args[0]);
    Mtx mtx;

    C_MTXLookAt(mtx, &(Vec){0.0f, 100.0f, 100.0f + z}, &(Vec){0.0f, 1.0f, 0.0f}, &(Vec){0.0f, 0.0f, z});
    envSetYamiView(mtx);
    return EVT_RETURN_DONE;
}

/**
 * Turns on TEV callback number args[1] (low 4 bits) for the animation pose of the NPC named in args[0],
 * if it exists; used to draw it in the darkness.
 */
static USER_FUNC(anim_tevcallback) {
    EvtWord* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 flag = evtGetValue(event, args[1]);
    NpcEntry* npc = npcNameToPtr_NoAssert(name);

    if (npc == NULL) {
        return EVT_RETURN_DONE;
    }
    animPoseSetMaterialFlagOn(npc->poseId, ANIM_MATERIAL_TEV_CALLBACK(flag & 0xF));
    return EVT_RETURN_DONE;
}

/** Same as anim_tevcallback for a map object named in args[0] (the save block or the chest). */
static USER_FUNC(anim_tevcallback_mobj) {
    EvtWord* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 flag = evtGetValue(event, args[1]);
    MapObjectEntry* mobj = mobjNameToPtrNoAssert(name);

    if (mobj == NULL) {
        return EVT_RETURN_DONE;
    }
    animPoseSetMaterialFlagOn(mobj->poseId, ANIM_MATERIAL_TEV_CALLBACK(flag & 0xF));
    return EVT_RETURN_DONE;
}

/**
 * Script run for each townsperson in the darkness scene (name in LW(0)):
 * waits until the NPC's Z position reaches the marker in GW(0), stops its regular event,
 * shows a speech bubble and then turns around at random intervals of 0.1 to 0.5 seconds.
 */
static EVT_BEGIN(sekai_yami_npc)
    LOOP(0)
        CALL(evt_npc_get_position, LW(0), LW(1), LW(2), LW(3))
        IF_INT_LESS_OR_EQUAL(GW(0), LW(3))
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_get_reglid, LW(0), LW(1))
    DELETE_EVENT(LW(1))
    CALL(evt_eff_fukidashi, 1, STRING(""), LW(0), 0, 0, 0, 0, 0, 0, 0, 48)
    WAIT_MS(1000)
    LOOP(0)
        CALL(evt_sub_random, 400, LW(1))
        ADD(LW(1), 100)
        WAIT_MS(LW(1))
        CALL(evt_npc_reverse_ry, LW(0))
        WAIT_FRAMES(1)
        CALL(evt_npc_wait_pera, LW(0))
    END_LOOP
    RETURN
EVT_END()

/**
 * Scene of the world darkening (Chapter 8 story step):
 * Mario and his partner are hidden, Toadsworth is placed at the plaza,
 * the map and NPCs get a darkness colour callback (envSetYami), the townspeople run sekai_yami_npc,
 * SFX_STG8_WORLD_DARK1 plays and the game changes to the nok_01 scene "sekai_yami1".
 */
static EVT_BEGIN(sekai_yami_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("キノじい"), 0, 0, 403)
    CALL(evt_cam3d_evt_set, 0, 350, 1530, 0, 150, 44, 0, 11)
    CALL(evt_seq_wait, 2)
    CALL(evt_map_set_tevcallback, 1, PTR(envSetYami))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S"), MAPOBJ_TEV_CALLBACK(1))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S"), MAPOBJ_FLAG_DISPLAY_LIST)
    CALL(anim_tevcallback, STRING("キノじい"), 1)
    CALL(anim_tevcallback, STRING("ロテン１"), 1)
    CALL(anim_tevcallback, STRING("クリボー１"), 1)
    CALL(anim_tevcallback, STRING("クリボー２"), 1)
    CALL(anim_tevcallback, STRING("チューさん１"), 1)
    CALL(anim_tevcallback, STRING("ボッタクール"), 1)
    CALL(anim_tevcallback_mobj, STRING("mobj_save"), 1)
    CALL(anim_tevcallback_mobj, STRING("mobj_box00"), 1)
    SET_VALUE(GW(0), 700)
    SET_VALUE(LW(0), STRING("キノじい"))
    SPAWN_EVENT(sekai_yami_npc)
    SET_VALUE(LW(0), STRING("ロテン１"))
    SPAWN_EVENT(sekai_yami_npc)
    SET_VALUE(LW(0), STRING("クリボー１"))
    SPAWN_EVENT(sekai_yami_npc)
    SET_VALUE(LW(0), STRING("チューさん１"))
    SPAWN_EVENT(sekai_yami_npc)
    SET_VALUE(LW(0), STRING("ボッタクール"))
    SPAWN_EVENT(sekai_yami_npc)
    CALL(evt_snd_sfxon, STRING("SFX_STG8_WORLD_DARK1"), 0)
    CALL(evt_sub_intpl_msec_init, 11, 700, -850, 5000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(yami_view, LW(0))
        SET_VALUE(GW(0), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(1200)
    CALL(evt_sub_intpl_msec_init, 11, 255, 64, 2000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        CALL(evt_bg_set_color, LW(0), LW(0), LW(0), 255)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_MS(2000)
    CALL(evt_fade_set_mapchange_type, 1, FADE_OUT_BLACK, 300, FADE_IN_BLACK, 300)
    CALL(evt_bero_mapchange, STRING("nok_01"), STRING("sekai_yami1"))
    RETURN
EVT_END()

/**
 * Scene of everyone's voices (Chapter 8 story step):
 * Mario and his partner and the townspeople are moved out of the way, the shop NPCs are removed,
 * a magic circle (mahojin) appears with SFX_STG8_STARSTONE_EFFECT1
 * and the game changes to the nok_01 scene "minnnanokoe" with BGM_EVT_STG8_VOICE1.
 */
static EVT_BEGIN(minnnanokoe_evt)
    // Controls are locked and Mario and his partner are moved off the map.
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_cont_onoff, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    CALL(evt_mario_set_pos, 0, -1000, 0)
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    // The shop, inn and street NPCs are put out of sight or removed so the plaza is empty.
    CALL(evt_npc_set_position, STRING("ロテン１"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("クリボー１"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("クリボー２"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("クリボー３"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("チューさん１"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("ボッタクール"), 0, -1000, 0)
    CALL(evt_npc_check_delete, STRING("バッジ店長"))
    CALL(evt_npc_check_delete, STRING("バッジ店員"))
    CALL(evt_npc_check_delete, STRING("店長"))
    CALL(evt_npc_check_delete, STRING("店員"))
    CALL(evt_npc_check_delete, STRING("ナンシー"))
    CALL(evt_npc_check_delete, STRING("キノじい"))
    CALL(evt_npc_check_delete, STRING("マスター"))
    CALL(evt_npc_check_delete, STRING("マルコ"))
    CALL(evt_npc_check_delete, STRING("宿店員"))
    CALL(evt_npc_check_delete, STRING("ロテン２"))
    CALL(evt_npc_check_delete, STRING("チューさん２"))
    CALL(evt_npc_check_delete, STRING("水夫ボム兵"))
    CALL(evt_npc_check_delete, STRING("ルイージ"))
    CALL(evt_npc_check_delete, STRING("盗賊"))
    CALL(evt_npc_check_delete, STRING("キノピオ"))
    CALL(evt_npc_check_delete, STRING("キック２"))
    // The camera looks down on the darkened plaza (Shadow Queen's darkness).
    CALL(evt_cam3d_evt_set, 0, 645, 824, 0, 55, 283, 0, 11)
    CALL(evt_map_set_tevcallback, 1, PTR(envSetYami))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S"), MAPOBJ_TEV_CALLBACK(1))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S"), MAPOBJ_FLAG_DISPLAY_LIST)
    CALL(anim_tevcallback_mobj, STRING("mobj_save"), 1)
    CALL(anim_tevcallback_mobj, STRING("mobj_box00"), 1)
    CALL(yami_view, -800)
    CALL(evt_bg_set_color, 64, 64, 64, 255)
    CALL(evt_seq_wait, 2)
    // A magic circle appears over the plaza.
    CALL(evt_eff, STRING("mahojin"), STRING("mahojin"), 8, 0, 5, 250, 0, 0, 0, 0, 0, 0, 0, 0)
    CALL(wait_mahojin)
    CALL(evt_snd_sfxon, STRING("SFX_STG8_STARSTONE_EFFECT1"), 0)
    WAIT_MS(7000)
    // A star stone rises out of the circle and spins as the voices theme starts.
    CALL(starstone_entry, 0, -50, 250)
    SET_FLOAT_VALUE(GW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(GW(1), FLOAT(-50.0f))
    SET_FLOAT_VALUE(GW(2), FLOAT(250.0f))
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(starstone_set_pos, GW(0), GW(1), GW(2))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
        LOOP(0)
            CALL(starstone_set_ry, LW(0))
            SUBTRACT_FLOAT(LW(0), FLOAT(3.0f))
            IF_INT_LESS_OR_EQUAL(LW(0), FLOAT(0.0f))
                ADD_FLOAT(LW(0), FLOAT(360.0f))
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STG8_VOICE1"))
    CALL(evt_sub_intpl_msec_init, 11, -50, 30, 3000)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value_para, LW(0), LW(1))
        SET_FLOAT_VALUE(GW(1), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    // The stone pulses in height while the camera pushes in.
    SET_VALUE(GF(0), 0)
    SET_VALUE(GF(1), 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_sub_intpl_msec_init, 11, 3000, 2500, 500)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            SET_FLOAT_VALUE(GW(1), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(1)
            END_IF
            IF_INT_NOT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            CALL(evt_sub_intpl_msec_init, 11, 2500, 3000, 500)
            LABEL(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            SET_FLOAT_VALUE(GW(1), LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(0)
            END_IF
        END_LOOP
        SET_VALUE(GF(1), 1)
    END_INLINE_EVENT
    WAIT_MS(3000)
    // The camera pulls back, then rises as the stone climbs into the sky.
    CALL(evt_cam3d_evt_set, 0, 110, 1093, 0, 110, 293, 1000, 11)
    WAIT_MS(1000)
    SET_VALUE(GF(0), 1)
    LOOP(0)
        IF_INT_NOT_EQUAL(GF(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    WAIT_MS(1500)
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_cam3d_evt_set, 0, -75, 999, 0, 300, 293, 2000, 1)
    END_INLINE_EVENT
    CALL(evt_sub_intpl_msec_init, 11, 25, 800, 2000)
    LABEL(3)
    CALL(evt_sub_intpl_msec_get_value)
    SET_VALUE(GW(1), LW(0))
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(3)
    END_IF
    WAIT_MS(2000)
    CALL(evt_fade_set_mapchange_type, 1, FADE_OUT_BLACK, 300, FADE_IN_BLACK, 300)
    // Fade out and change to the scene where everyone's voices are heard.
    CALL(evt_bero_mapchange, STRING("nok_01"), STRING("minnnanokoe"))
    RETURN
EVT_END()

/**
 * Init hook for Trouble Center job 9 (the Courage Shell collecting request):
 * while the job is active it routes the item shop manager's talk through iri_09_tentyo_talk.
 */
EVT_BEGIN(iri_09_init)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 9)
        CALL(set_fook_evt, PTR(&shopper_data), PTR(iri_09_tentyo_talk))
    END_IF
    RETURN
EVT_END()

/**
 * Trouble Center job 9: the shop manager asks Mario for Courage Shells.
 * Each shell Mario hands over is counted in GSW_TROUBLE_WORK_FIRST;
 * after 5 he rewards Mario with an Ultra Shroom and the job is solved (GSWF_TROUBLE_09_SOLVED).
 * Returns in LW(0) whether the normal shop menu should still open (0), is skipped (-1 or -100).
 */
EVT_BEGIN(iri_09_tentyo_talk)
    IF_INT_EQUAL(GSWF(GSWF_TROUBLE_09_SOLVED), 1)
        SET_VALUE(LW(0), 0)
        RETURN
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
        CALL(evt_msg_print, 0, STRING("irai_09_001"), 0, STRING("店長"))
        SET_VALUE(GSWF(GSWF_TROUBLE_WORK_BASE), 1)
        SET_VALUE(LW(0), -1)
    ELSE
        CALL(evt_msg_print, 0, STRING("irai_09_002"), 0, STRING("店長"))
        CALL(evt_pouch_check_item, ITEM_COURAGE_SHELL, LW(0))
        IF_INT_GREATER(LW(0), 0)
            CALL(iri_09_item_tbl_alloc, LW(0))
            LOOP(0)
                CALL(evt_msg_continue)
                CALL(iri_09_item_tbl_make, LW(0), LW(1))
#if VERSION <= VERSION_DEMO_US
                CALL(evt_win_item_select, LW(1), LW(2))
#else
                CALL(evt_win_item_select, 0, LW(1), LW(2), 0)
#endif
                IF_INT_EQUAL(LW(2), -1)
                    SET_VALUE(LF(0), 1)
                    BREAK_LOOP
                END_IF
                CALL(evt_msg_print, 0, STRING("irai_09_003"), 0, STRING("店長"))
                CALL(evt_pouch_remove_item, ITEM_COURAGE_SHELL, LW(1))
                ADD(GSW(GSW_TROUBLE_WORK_FIRST), 1)
                IF_INT_EQUAL(GSW(GSW_TROUBLE_WORK_FIRST), 5)
                    SET_VALUE(LF(0), 0)
                    BREAK_LOOP
                END_IF
                CALL(evt_pouch_check_item, ITEM_COURAGE_SHELL, LW(0))
                IF_INT_LESS_OR_EQUAL(LW(0), 0)
                    SET_VALUE(LF(0), 0)
                    BREAK_LOOP
                END_IF
            END_LOOP
            CALL(iri_09_item_tbl_free)
            IF_INT_LESS(GSW(GSW_TROUBLE_WORK_FIRST), 5)
                IF_INT_EQUAL(LF(0), 0)
                    CALL(evt_msg_print_add, 0, STRING("irai_09_006_1"))
                ELSE
                    CALL(evt_msg_print, 0, STRING("irai_09_006_1"), 0, STRING("店長"))
                END_IF
            ELSE
                CALL(evt_msg_print_add, 0, STRING("irai_09_004"))
                CALL(evt_item_entry, STRING("uk"), ITEM_ULTRA_SHROOM, 0, -1000, 0, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
                CALL(evt_item_get_item, STRING("uk"))
                CALL(evt_item_get_item_end_wait, STRING("uk"))
                CALL(evt_msg_print, 0, STRING("irai_09_006"), 0, STRING("店長"))
                SET_VALUE(GSW(GSW_TROUBLE_ACTIVE), 0)
                SET_VALUE(GSWF(GSWF_TROUBLE_09_SOLVED), 1)
                CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
                SET_VALUE(LW(0), -1)
                RETURN
            END_IF
        ELSE
            CALL(evt_msg_print_add, 0, STRING("irai_09_008"))
        END_IF
        SET_VALUE(LW(0), -100)
    END_IF
    RETURN
EVT_END()

/** Items offered in the item menu for Trouble Center job 16: only Attack FX B. */
s32 iri_16_item_tbl[] = {
    ITEM_ATTACK_FX_B_KEY_ITEM, -1,
};

/**
 * Map-init part of Trouble Center request 16: while it is active,
 * enters Ms. Mowz ("c_tyutyu") at (-516, 189, -110) facing 90 with iri_16_tyutyu_talk as her talk event.
 */
static EVT_BEGIN(iri_16_init)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 16)
        CALL(evt_npc_entry, STRING("チュチュリーナ"), STRING("c_tyutyu"))
        CALL(evt_npc_set_tribe, STRING("チュチュリーナ"), STRING("チュチュリーナ"))
        CALL(evt_npc_set_position, STRING("チュチュリーナ"), -516, 189, -110)
        CALL(evt_npc_set_ry, STRING("チュチュリーナ"), 90)
        CALL(evt_npc_flag_onoff, 1, STRING("チュチュリーナ"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
        CALL(evt_npc_change_interrupt, STRING("チュチュリーナ"), 6, PTR(iri_16_tyutyu_talk))
    END_IF
    RETURN
EVT_END()

/**
 * Trouble Center job 16: Ms. Mowz asks Mario for an item (the Mowz request key item),
 * kisses him when he hands it over and rewards him with the Attack FX B badge,
 * which she leaves on the floor if his badge list is already full (200 badges).
 * She then joins the party as a partner (all_party_lecture for partner 7).
 * The "Ms. Mowz" theme plays during the talk.
 */
EVT_BEGIN(iri_16_tyutyu_talk)
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 16)
        // Ms. Mowz's own theme replaces the plaza music for the whole talk.
        CALL(evt_snd_bgmoff_f, PSND_FADE_HOLD, 2000)
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_EVT_CYUCYURINA1"))
        // First talk: she explains what she is looking for.
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
            CALL(evt_msg_print, 0, STRING("irai_16_00"), 0, STRING("チュチュリーナ"))
            SET_VALUE(GSWF(GSWF_TROUBLE_WORK_BASE), 1)
        ELSE
            IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_2), 0)
                // Mario has not found it yet: she repeats her request.
                CALL(evt_msg_print, 0, STRING("irai_16_01"), 0, STRING("チュチュリーナ"))
            ELSE
                // Mario has the item: he and the partner walk up to her.
                CALL(evt_npc_flag_onoff, 1, STRING("チュチュリーナ"), NPC_FLAG_INTANGIBLE)
                CALL(evt_party_stop, 0)
                BEGIN_INLINE_EVENT
                    CALL(evt_party_move_pos2, 0, -448, -110, 60)
                    CALL(evt_party_set_dir_npc, 0, STRING("チュチュリーナ"))
                END_INLINE_EVENT
                CALL(evt_mario_mov_pos2, -485, -110, 60)
                CALL(evt_mario_set_dir_npc, STRING("チュチュリーナ"))
                WAIT_MS(500)
                CALL(evt_set_dir_to_target, STRING("チュチュリーナ"), STRING("mario"))
                WAIT_FRAMES(1)
                CALL(evt_npc_wait_pera, STRING("チュチュリーナ"))
                // She asks for the item; Mario picks it from the item menu.
                CALL(evt_msg_print, 0, STRING("irai_16_02"), 0, STRING("チュチュリーナ"))
#if VERSION <= VERSION_DEMO_US
                CALL(evt_win_item_select, PTR(iri_16_item_tbl), LW(0))
#else
                CALL(evt_win_item_select, 0, PTR(iri_16_item_tbl), LW(0), 0)
#endif
                IF_INT_NOT_EQUAL(LW(0), -1)
                    // Mario hands it over and Ms. Mowz is overjoyed.
                    CALL(evt_pouch_remove_item, ITEM_ATTACK_FX_B_KEY_ITEM, LW(0))
                    CALL(evt_msg_print, 0, STRING("irai_16_03"), 0, STRING("チュチュリーナ"))
                    CALL(evt_npc_set_anim, STRING("チュチュリーナ"), STRING("PCH_C_1"))
                    WAIT_MS(1000)
                    CALL(evt_msg_print, 0, STRING("irai_16_04"), 0, STRING("チュチュリーナ"))
                    CALL(evt_mario_set_pose, STRING("M_N_5B"))
                    WAIT_MS(600)
                    CALL(evt_mario_set_pose, STRING("M_S_1"))
                    CALL(evt_msg_print, 0, STRING("irai_16_05"), 0, STRING("チュチュリーナ"))
                    // Her reward is the Attack FX B badge, handed over only if Mario has room for another
                    // badge.
                    CALL(evt_pouch_get_havebadgecnt, LW(0))
                    IF_INT_LESS(LW(0), 200)
                        CALL(evt_msg_continue)
                        CALL(evt_item_entry, STRING("mb"), ITEM_ATTACK_FX_B, 0, -1000, 0, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
                        CALL(evt_item_get_item, STRING("mb"))
                        CALL(evt_item_get_item_end_wait, STRING("mb"))
                        SET_VALUE(GSWF(GSWF_GOR01_TROUBLE16_BADGE_LEFT), 1)
                    ELSE
                        // Badge list full: she hops over the rooftops and leaves the badge on the ground for
                        // Mario to pick up later.
                        CALL(evt_msg_print_add, 0, STRING("irai_16_05_1"))
                        BEGIN_INLINE_EVENT
                            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                            LOOP(0)
                                CALL(evt_npc_get_position, STRING("チュチュリーナ"), LW(3), LW(4), LW(5))
                                IF_INT_GREATER(LW(3), LW(0))
                                    BREAK_LOOP
                                END_IF
                                WAIT_FRAMES(1)
                            END_LOOP
                            CALL(evt_mario_set_dir_npc, STRING("チュチュリーナ"))
                        END_INLINE_EVENT
                        CALL(evt_npc_flag_onoff, 1, STRING("チュチュリーナ"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
                        CALL(evt_npc_get_position, STRING("チュチュリーナ"), LW(0), LW(1), LW(2))
                        CALL(evt_npc_set_ry, STRING("チュチュリーナ"), 90)
                        WAIT_FRAMES(1)
                        CALL(evt_npc_wait_pera, STRING("チュチュリーナ"))
                        CALL(evt_npc_jump_position_nohit, STRING("チュチュリーナ"), -150, 300, LW(2), 800, 100)
                        WAIT_MS(2000)
                        CALL(evt_npc_set_ry, STRING("チュチュリーナ"), 270)
                        WAIT_FRAMES(1)
                        CALL(evt_npc_wait_pera, STRING("チュチュリーナ"))
                        BEGIN_INLINE_EVENT
                            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                            LOOP(0)
                                CALL(evt_npc_get_position, STRING("チュチュリーナ"), LW(3), LW(4), LW(5))
                                IF_INT_LESS(LW(3), LW(0))
                                    BREAK_LOOP
                                END_IF
                                WAIT_FRAMES(1)
                            END_LOOP
                            CALL(evt_mario_set_dir_npc, STRING("チュチュリーナ"))
                        END_INLINE_EVENT
                        CALL(evt_npc_jump_position_nohit, STRING("チュチュリーナ"), LW(0), LW(1), LW(2), 800, 50)
                        CALL(evt_set_dir_to_target, STRING("チュチュリーナ"), STRING("mario"))
                        WAIT_FRAMES(1)
                        CALL(evt_npc_wait_pera, STRING("チュチュリーナ"))
                        CALL(evt_npc_flag_onoff, 0, STRING("チュチュリーナ"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_INTANGIBLE)
                        CALL(evt_msg_print, 0, STRING("irai_16_05_2"), 0, STRING("チュチュリーナ"))
                        CALL(evt_item_entry, STRING("iri_16"), ITEM_ATTACK_FX_B, -150, 153, -120, ITEM_ENTRY_FIXED, GSWF(GSWF_GOR01_TROUBLE16_BADGE_LEFT), 0)
                    END_IF
                    // She thanks Mario with a kiss.
                    CALL(evt_msg_print, 0, STRING("irai_16_06"), 0, STRING("チュチュリーナ"))
                    CALL(evt_npc_flag_onoff, 1, STRING("チュチュリーナ"), NPC_FLAG_INTANGIBLE)
                    CALL(evt_npc_get_position, STRING("チュチュリーナ"), LW(0), LW(1), LW(2))
                    CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
                    SUBTRACT(LW(3), 15)
                    CALL(evt_npc_move_position, STRING("チュチュリーナ"), LW(3), LW(5), 0, 40, 0)
                    WAIT_FRAMES(1)
                    CALL(evt_npc_set_anim, STRING("チュチュリーナ"), STRING("PCH_K_1"))
                    CALL(evt_mario_set_pose, STRING("M_I_O"))
                    BEGIN_INLINE_EVENT
                        CALL(evt_npc_get_position, STRING("チュチュリーナ"), LW(0), LW(1), LW(2))
                        ADD(LW(1), 30)
                        CALL(evt_eff, 0, STRING("kiss"), 0, LW(0), LW(1), LW(2), -45, 0, 0, 0, 0, 0, 0, 0)
                        CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_REQUEST_CHURINA_KISS1"), LW(0), LW(1), LW(2), 0)
                    END_INLINE_EVENT
                    WAIT_MS(400)
                    CALL(evt_npc_set_anim, STRING("チュチュリーナ"), STRING("PCH_S_1"))
                    WAIT_MS(500)
                    CALL(evt_mario_set_pose, STRING("M_S_1"))
                    CALL(evt_npc_move_position, STRING("チュチュリーナ"), LW(0), LW(2), 0, 40, 0)
                    WAIT_MS(1000)
#if VERSION <= VERSION_JP
                    CALL(evt_cam3d_evt_set, -525, 290, 230, -525, 225, -140, 800, 11)
#else
                    CALL(evt_cam3d_evt_set, -516, 290, 230, -516, 225, -140, 800, 11)
#endif
                    WAIT_MS(800)
                    // Ms. Mowz joins the party and the partner lecture plays.
                    SET_VALUE(LW(8), STRING("チュチュリーナ"))
                    SET_VALUE(LW(9), 7)
                    CALL_CHILD(all_party_lecture)
                    SET_VALUE(GSW(GSW_TROUBLE_ACTIVE), 0)
                    // The request is marked solved and the Trouble Center completion message appears.
                    SET_VALUE(GSWF(GSWF_TROUBLE_16_SOLVED), 1)
                    CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
                    CALL(evt_cam3d_evt_off, 500, 11)
                    CALL(evt_party_run, 0)
                END_IF
                CALL(evt_party_run, 0)
            END_IF
        END_IF
        // Ms. Mowz's theme fades out and the plaza music returns.
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
        RETURN
    END_IF
    RETURN
EVT_END()

/**
 * Case event for the Skull Gem item (A_jewel): shows Marco's (Flavio's) line mac_4_006 about it
 * and restarts his muttering.
 */
EVT_BEGIN(marco_jewel)
    CALL(evt_mario_key_onoff, 0)
    DELETE_EVENT(GW(0))
    CALL(evt_msg_close, STRING("mac_4_004"))
    CALL(evt_msg_print, 0, STRING("mac_4_006"), 0, STRING("マルコ"))
    SPAWN_EVENT_GET_ID(PTR(marco_hitorigoto), GW(0))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Enters Goombella ("c_pkr") at (55, 154, -110) facing 270
 * and Ms. Mowz ("c_tyutyu", hidden below the map) for the ending scene in the plaza,
 * both intangible and with move animation.
 */
static EVT_BEGIN(epilogue_npc_entry)
    CALL(evt_npc_entry, STRING("クリスチーヌ"), STRING("c_pkr"))
    CALL(evt_npc_set_tribe, STRING("クリスチーヌ"), STRING("クリスチーヌ"))
    CALL(evt_npc_set_position, STRING("クリスチーヌ"), 55, 154, -110)
    CALL(evt_npc_set_ry, STRING("クリスチーヌ"), 270)
    CALL(evt_npc_flag_onoff, 1, STRING("クリスチーヌ"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_MOVE_ANIM | NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_entry, STRING("チュチュリーナ"), STRING("c_tyutyu"))
    CALL(evt_npc_set_tribe, STRING("チュチュリーナ"), STRING("チュチュリーナ"))
    CALL(evt_npc_set_position, STRING("チュチュリーナ"), 0, -1000, 0)
    CALL(evt_npc_set_ry, STRING("チュチュリーナ"), 90)
    CALL(evt_npc_flag_onoff, 1, STRING("チュチュリーナ"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_MOVE_ANIM | NPC_FLAG_INTANGIBLE)
    RETURN
EVT_END()

/**
 * Background part of the badge shop ending scene:
 * opens the shop's doors in turn (door_data_03_f2, then door_data_02_f2), moves Goombella in,
 * then loops the badge shop owner's and Goombella's talk animations.
 */
static EVT_BEGIN(epilogue_evt_sub)
    SET_VALUE(LW(0), PTR(&door_data_03_f2))
    SPAWN_EVENT(door_open_se)
    CALL(evt_sub_intpl_msec_init, 5, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SPAWN_EVENT(evt_door_03_00_f2)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("クリスチーヌ"), -50, -110, 0, 60, 0)
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    WAIT_MS(1100)
    SET_VALUE(LW(0), PTR(&door_data_03_f2))
    SPAWN_EVENT(door_close_se)
    CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SPAWN_EVENT(evt_door_03_00_f2)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_WHILE(GF(0))
    SET_VALUE(LW(0), PTR(&door_data_02_f2))
    SPAWN_EVENT(door_open_se)
    CALL(evt_sub_intpl_msec_init, 5, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SPAWN_EVENT(evt_door_02_00_f2)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_move_position, STRING("バッジ店長"), -114, -100, 0, 60, 0)
    CALL(evt_set_dir_to_target, STRING("バッジ店長"), STRING("クリスチーヌ"))
    SET_VALUE(LW(0), PTR(&door_data_02_f2))
    SPAWN_EVENT(door_close_se)
    CALL(evt_sub_intpl_msec_init, 5, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        SPAWN_EVENT(evt_door_02_00_f2)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    LOOP(0)
        CALL(evt_npc_set_anim, STRING("バッジ店長"), STRING("CHU_T_1"))
        WAIT_MS(1500)
        CALL(evt_npc_set_anim, STRING("バッジ店長"), STRING("CHU_S_1"))
        CALL(evt_npc_set_anim, STRING("クリスチーヌ"), STRING("PKR_T_1"))
        SET_VALUE(GF(15), 0)
        WAIT_MS(1500)
        CALL(evt_npc_set_anim, STRING("クリスチーヌ"), STRING("PKR_S_1"))
    END_LOOP
    RETURN
EVT_END()

/**
 * The ending scene at the badge shop: the owner and Goombella meet (ep_43) with the shop camera,
 * then the owner and Ms. Mowz spin around together and swap places, hiding the owner and showing Ms. Mowz,
 * who jumps away across the rooftops while Goombella turns to follow; the game then changes to pik_04.
 */
static EVT_BEGIN(epilogue_evt)
    // The epilogue: Ms. Mowz's theme starts and the badge shop's rooms are set up for the scene.
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_CYUCYURINA1"))
    CALL(evt_snd_bgm_scope, 0, 1)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_dispflag_onoff, 1, 1)
    CALL(evt_npc_set_position, STRING("バッジ店長"), -114, 154, -173)
    CALL(evt_npc_flag_onoff, 1, STRING("バッジ店長"), NPC_FLAG_NO_WALL_HIT | NPC_FLAG_MOVE_ANIM | NPC_FLAG_INTANGIBLE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_ie_02_f2_naka"), MAPOBJ_FLAG_HIDE)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_unitwin_alloc)
#else
    CALL(evt_unitwin_alloc, 1)
#endif
    CALL(badgeShop_getBargainTable, LW(0))
    CALL(evt_unitwin_selltable_setup, PTR(uwnobj_list), LW(0))
    CALL(evt_cam3d_evt_set, -80, 225, 400, -80, 200, -100, 0, 11)
    CALL(evt_seq_wait, 2)
    SET_VALUE(GF(15), 1)
    SPAWN_EVENT_GET_ID(PTR(epilogue_evt_sub), LW(0))
    CALL(evt_fade_end_wait)
    WAIT_MS(1000)
    // The narrator tells what became of Ms. Mowz and the badge shop.
    CALL(evt_msg_print, 0, STRING("ep_43"), 0, 0)
    WAIT_WHILE(GF(15))
    DELETE_EVENT(LW(0))
    WAIT_MS(1000)
    CALL(evt_npc_set_anim, STRING("バッジ店長"), STRING("CHU_S_1"))
    CALL(evt_npc_set_anim, STRING("クリスチーヌ"), STRING("PKR_S_1"))
    WAIT_MS(500)
    CALL(evt_npc_flag_onoff, 1, STRING("チュチュリーナ"), NPC_FLAG_HIDDEN)
    CALL(evt_npc_get_position, STRING("バッジ店長"), LW(0), LW(1), LW(2))
    CALL(evt_npc_get_dir, STRING("バッジ店長"), LW(3))
    CALL(evt_npc_set_position, STRING("チュチュリーナ"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_ry, STRING("チュチュリーナ"), LW(3))
    CALL(evt_npc_flag_onoff, 1, STRING("チュチュリーナ"), NPC_FLAG_INSTANT_TURN)
    // The shop owner and Ms. Mowz spin together and trade places, revealing the owner as Ms. Mowz.
    CALL(evt_npc_set_anim, STRING("バッジ店長"), STRING("CHU_Z_1"))
    CALL(evt_npc_set_anim, STRING("チュチュリーナ"), STRING("PCH_Z_1"))
    SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
    SET_FLOAT_VALUE(LW(1), FLOAT(20.0f))
    SET_VALUE(LW(2), 0)
    LOOP(0)
        ADD_FLOAT(LW(0), LW(1))
        IF_INT_GREATER_OR_EQUAL(LW(0), FLOAT(360.0f))
            SUBTRACT_FLOAT(LW(0), FLOAT(360.0f))
            ADD(LW(2), 1)
            IF_INT_GREATER_OR_EQUAL(LW(2), 5)
                BREAK_LOOP
            END_IF
        END_IF
        IF_INT_GREATER_OR_EQUAL(LW(2), 4)
            SUBTRACT_FLOAT(LW(1), FLOAT(1.0f))
            IF_INT_LESS_OR_EQUAL(LW(1), FLOAT(5.0f))
                SET_FLOAT_VALUE(LW(1), FLOAT(5.0f))
            END_IF
        END_IF
        IF_INT_EQUAL(LW(2), 2)
            IF_INT_EQUAL(LW(0), FLOAT(180.0f))
                CALL(evt_npc_flag_onoff, 1, STRING("バッジ店長"), NPC_FLAG_HIDDEN)
                CALL(evt_npc_flag_onoff, 0, STRING("チュチュリーナ"), NPC_FLAG_HIDDEN)
            END_IF
        END_IF
        CALL(evt_npc_set_rotate, STRING("バッジ店長"), 0, LW(0), 0)
        CALL(evt_npc_set_rotate, STRING("チュチュリーナ"), 0, LW(0), 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_npc_set_rotate, STRING("チュチュリーナ"), 0, 0, 0)
    CALL(evt_npc_flag_onoff, 0, STRING("チュチュリーナ"), NPC_FLAG_INSTANT_TURN)
    CALL(evt_npc_set_anim, STRING("バッジ店長"), STRING("CHU_S_1"))
    CALL(evt_npc_set_anim, STRING("チュチュリーナ"), STRING("PCH_S_1"))
    WAIT_MS(300)
    // The camera pulls back as Ms. Mowz leaps away across the rooftops.
    CALL(evt_cam3d_evt_set, 0, 275, 1397, 0, 200, -100, 0, 11)
    WAIT_FRAMES(1)
    WAIT_MS(500)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_npc_get_position, STRING("チュチュリーナ"), LW(0), LW(1), LW(2))
            IF_INT_GREATER_OR_EQUAL(LW(0), -50)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_npc_set_ry, STRING("クリスチーヌ"), 90)
    END_INLINE_EVENT
    CALL(evt_npc_jump_position_nohit, STRING("チュチュリーナ"), -84, 302, -167, 700, 130)
    CALL(evt_npc_jump_position_nohit, STRING("チュチュリーナ"), 140, 354, -216, 700, 70)
    CALL(evt_npc_jump_position_nohit, STRING("チュチュリーナ"), 290, 354, -216, 700, 70)
    CALL(evt_npc_jump_position_nohit, STRING("チュチュリーナ"), 490, 504, -216, 700, 120)
    WAIT_MS(1000)
    // Music fades, then a fade to black and on to the next scene.
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 3000)
    CALL(evt_snd_envoff_f, PSND_FADE_OUT, 3000)
    CALL(evt_fade_set_mapchange_type, 1, FADE_OUT_BLACK, 900, FADE_IN_BLACK, 900)
    CALL(evt_bero_mapchange, STRING("pik_04"), STRING(""))
    RETURN
EVT_END()

#if VERSION >= VERSION_US
/**
 * Loops forever: shows the stage platform pieces "S_dai" only while Mario stands near x -60 to 60,
 * z -300 to -200 (the area near the fountain); hides it otherwise. US and later releases.
 */
EVT_BEGIN(dai_disp)
    LOOP(0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        SET_VALUE(LF(0), 0)
        IF_INT_LESS_OR_EQUAL(LW(0), 60)
            IF_INT_GREATER_OR_EQUAL(LW(0), -60)
                IF_INT_LESS_OR_EQUAL(LW(2), -200)
                    IF_INT_GREATER_OR_EQUAL(LW(2), -300)
                        SET_VALUE(LF(0), 1)
                    END_IF
                END_IF
            END_IF
        END_IF
        IF_INT_EQUAL(LF(0), 0)
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_dai"), MAPOBJ_FLAG_HIDE)
        ELSE
            CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_dai"), MAPOBJ_FLAG_HIDE)
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()
#endif
/**
 * Map init for gor_01 (Rogueport plaza).
 * Chooses the music by story stage, sets up the exits (east to gor_02, west to gor_03, south to the harbor),
 * creates the NPCs, buildings' doors, shops, the save block, the star pieces and chests,
 * and starts whichever story scene belongs to the current stage:
 * Goombella joining, the Skull Gem and Ultra Hammer events, Bowser's visit,
 * the Shadow Queen's darkness scenes and the epilogue.
 */
EVT_BEGIN(gor_01_init_evt)
    // Work out which special scene this visit belongs to: Bowser's visit in Chapter 6 or the darkness scenes in
    // Chapter 8.
    SET_VALUE(LF(0), 0)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG6_55_01_PEACH_TEC_DELETED)
        CALL(evt_mario_set_mode, 2)
        SET_VALUE(LF(0), 1)
    END_IF
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG8_15_GRODUS)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("sekai_yami1"))
            SET_VALUE(LF(1), 1)
        END_IF
        IF_STR_EQUAL(LW(0), STRING("minnnanokoe"))
            SET_VALUE(LF(1), 1)
        END_IF
    END_IF
    // Choose the music and ambience: darkness themes, Bowser's theme, or the plaza theme.
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG8_END_AFTER_THE_BATTLE)
        CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG0_GOR1"))
    ELSE
        IF_INT_EQUAL(LF(0), 0)
            IF_INT_EQUAL(LF(1), 1)
                CALL(evt_bero_get_entername, LW(0))
                IF_STR_EQUAL(LW(0), STRING("sekai_yami1"))
                    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STG8_WITCH"))
                    CALL(evt_snd_envoff, PSND_FADE_OUT)
                END_IF
                IF_STR_EQUAL(LW(0), STRING("minnnanokoe"))
                    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
                    CALL(evt_snd_envoff, PSND_FADE_OUT)
                    SET_VALUE(LF(1), 1)
                END_IF
            ELSE
                CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG0_GOR1"))
                CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
                CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG0_GOR1"))
            END_IF
        ELSE
            CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_KUPPA1"))
            CALL(evt_snd_bgm_scope, 0, 1)
            CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_UNDIP, 0)
            CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG0_GOR1"))
        END_IF
    END_IF
    // Register the exits and, if Goombella is about to join, prepare her scene's NPCs.
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG0_06_1000_X_NAUTS_AFTER)
        CALL_CHILD(christine_nakama_init)
    END_IF
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG0_07_GOOMBELLA_JOINS)
        IF_INT_EQUAL(GSWF(GSWF_GOR01_GOOMBELLA_SAVE_TALK_DONE), 0)
            SPAWN_EVENT(christine_nakama_after)
        END_IF
    END_IF
    // The ordered contact lens arrives once the story has moved on or enough time has passed.
    IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_ARRIVED), 0)
        IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_ORDERED), 1)
            IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG1_17_FATHER_AND_SON_REUNITED)
                SET_VALUE(GSWF(GSWF_GOR01_LENS_ARRIVED), 1)
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_ARRIVED), 0)
        IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG1_17_FATHER_AND_SON_REUNITED)
            SET_VALUE(LW(0), GSWF(GSWF_GOR01_LENS_ORDERED))
            ADD(LW(0), GSWF(GSWF_GOR01_LENS_ORDERED_ALT))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(evt_sub_load_progresstime, GSW(GSW_GOR01_LENS_ORDER_TIME), LW(0))
                IF_INT_GREATER_OR_EQUAL(LW(0), 90000)
                    SET_VALUE(GSWF(GSWF_GOR01_LENS_ARRIVED), 1)
                END_IF
            END_IF
        END_IF
    END_IF
    // Create the plaza NPCs; Flavio gets his footstep sounds.
    CALL_CHILD(luigi_npcEnt)
    CALL(evt_npc_setup, PTR(npcEnt))
    CALL(evt_npc_sound_data_set, STRING("マルコ"), STRING("SFX_STG5_MARCO_MOVE1L"), STRING("SFX_STG5_MARCO_MOVE1R"), EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
    IF_INT_EQUAL(LF(0), 1)
        CALL_CHILD(koopa_npc_entry)
    END_IF
    // The Save Block stands in the plaza except during Bowser's visit.
    IF_INT_NOT_EQUAL(LF(0), 1)
        CALL(evt_mobj_save_blk, STRING("mobj_save"), 185, 60, -55, 0, 0)
    END_IF
    // Star Piece panels and the hidden Star Pieces.
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), -455, 0, -260, STRING("S_ground"), 125, GSWF(GSWF_GOR01_STAR_PIECE_PANEL_1))
    CALL(evt_mobj_kururing_floor, STRING("kururin2"), 0, 0, 450, STRING("S_ground"), 125, GSWF(GSWF_GOR01_STAR_PIECE_PANEL_2))
    CALL(evt_item_entry, STRING("item_00"), ITEM_STAR_PIECE, 490, 0, 245, ITEM_ENTRY_FIXED, GSWF(GSWF_GOR01_STAR_PIECE_1), 0)
    CALL(evt_item_entry, STRING("item_01"), ITEM_STAR_PIECE, 550, 0, -150, ITEM_ENTRY_FIXED, GSWF(GSWF_GOR01_STAR_PIECE_2), 0)
    CALL(evt_item_entry, STRING("item_02"), ITEM_STAR_PIECE, -565, 162, -160, ITEM_ENTRY_FIXED, GSWF(GSWF_GOR01_STAR_PIECE_3), 0)
    // Until Flavio's talk the Skull Gem lies on the ground.
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG4_32_CHATTING_WITH_FLAVIO)
        CALL(evt_item_entry, STRING("ドクロジュエル"), ITEM_SKULL_GEM, 315, 20, -125, ITEM_ENTRY_FIXED, -1, 0)
        CALL(evt_item_flag_on, STRING("ドクロジュエル"), ITEM_FLAG_NO_TOUCH)
#if VERSION >= VERSION_JP
        CALL(evt_item_status_on, STRING("ドクロジュエル"), ITEM_STATUS_NO_KOOPS)
#endif
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_jewel"), 0, PTR(marco_jewel), GW(8))
    END_IF
    // Open the building doors, depending on story progress and whether the lens was delivered.
    IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_DELIVERED), 0)
        SET_VALUE(LW(0), PTR(&door_data_01))
    ELSE
        SET_VALUE(LW(0), PTR(&door_data_01_01))
    END_IF
    CALL(evt_door_data_copy, LW(0), GW(6))
    SET_VALUE(LW(0), GW(6))
    CALL_CHILD(evt_door_entry)
    SET_VALUE(LW(0), PTR(&door_data_02_f1))
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG4_32_CHATTING_WITH_FLAVIO)
        IF_INT_EQUAL(GSWF(GSWF_GOR01_LENS_ARRIVED), 1)
            SET_VALUE(LW(0), PTR(&door_data_02_f1_01))
        END_IF
    END_IF
    CALL_CHILD(evt_door_entry)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG0_16_FRANKLYS_HOUSE)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_ie_02_f2_doa01"), 0, PTR(evt_door_02_f2_junbityu), 0)
    ELSE
        SET_VALUE(LW(0), PTR(&door_data_02_f2))
        CALL_CHILD(evt_door_entry)
    END_IF
    SET_VALUE(LW(0), PTR(&door_data_03_f1))
    CALL_CHILD(evt_door_entry)
    SET_VALUE(LW(0), PTR(&door_data_03_f2))
    CALL_CHILD(evt_door_entry)
    SET_VALUE(LW(0), PTR(&door_data_04))
    CALL_CHILD(evt_door_entry)
    // Shops, townsfolk and ambient animations.
    CALL_CHILD(gor_01_shop_setup)
    CALL(evt_kinopio_setup, PTR(&kino_dt))
    CALL(evt_map_playanim, STRING("hae"), 1, 0)
    SPAWN_EVENT(koushukei_dai)
    SPAWN_EVENT(gate_disp)
    SPAWN_EVENT(gor_goki1_urouro)
    SPAWN_EVENT(gor_goki2_urouro)
    // Trouble Center request items and NPCs, except during the darkness scenes.
    IF_INT_EQUAL(LF(1), 0)
        IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 1)
            CALL(evt_item_entry, STRING("item_key00"), ITEM_HOUSE_KEY, -280, 153, -100, ITEM_ENTRY_STAY, GSWF(GSWF_TROUBLE_WORK_BASE), 0)
        END_IF
        CALL_CHILD(borodo2_init)
        SPAWN_EVENT(iri_09_init)
        SPAWN_EVENT(iri_16_init)
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_16_SOLVED), 1)
            CALL(evt_item_entry, STRING("iri_16"), ITEM_ATTACK_FX_B, -150, 153, -120, ITEM_ENTRY_FIXED, GSWF(GSWF_GOR01_TROUBLE16_BADGE_LEFT), 0)
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_18_SOLVED), 1)
            CALL(evt_item_entry, STRING("iri_18"), ITEM_HONEY_SHROOM, -440, 30, -80, ITEM_ENTRY_FIXED, GSWF(GSWF_GOR01_TROUBLE18_ITEM_LEFT), 0)
        END_IF
    END_IF
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_keizi_mae"), 0, PTR(keijiban_omote_joho), 0)
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_keizi_ura"), 0, PTR(keijiban_ura_joho), 0)
    // The Ultra Hammer chest: on the roof until it has fallen, then on the ground.
    CALL(evt_pouch_check_item, ITEM_ULTRA_HAMMER, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        IF_INT_EQUAL(GSWF(GSWF_GOR01_ULTRA_HAMMER_CHEST_FALLEN), 0)
#if VERSION <= VERSION_DEMO_US
            CALL(evt_mobj_itembox, STRING("mobj_box00"), 340, 146, -20, 1, 0, PTR(ultrahammer_get), GSWF(GSWF_GOR01_ULTRA_HAMMER_CHEST_OPENED))
#else
            CALL(evt_mobj_itembox, STRING("mobj_box00"), 340, 110, -20, 1, 0, PTR(ultrahammer_get), GSWF(GSWF_GOR01_ULTRA_HAMMER_CHEST_OPENED))
#endif
            SPAWN_EVENT(ultrahammer_check)
        ELSE
            CALL(evt_mobj_itembox, STRING("mobj_box00"), 275, 0, 75, 1, 0, PTR(ultrahammer_get), GSWF(GSWF_GOR01_ULTRA_HAMMER_CHEST_OPENED))
        END_IF
    END_IF
    // Map object culling for the fence, stage and houses.
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_saku"), MAPOBJ_FLAG_BBOX_CULL)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_dai"), MAPOBJ_FLAG_BBOX_CULL)
#if VERSION >= VERSION_US
    SPAWN_EVENT(dai_disp)
#endif
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_ie_02_f1A"), MAPOBJ_FLAG_BBOX_CULL)
    // Chapter 6: Bowser arrives and the Bowser interlude starts.
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_mario_kill_party, 0)
        SPAWN_EVENT(gor_01_koopa_evt)
    END_IF
    // Chapter 8: start the matching darkness scene.
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_bero_get_entername, LW(0))
        IF_STR_EQUAL(LW(0), STRING("sekai_yami1"))
            SPAWN_EVENT(sekai_yami_evt)
        END_IF
        IF_STR_EQUAL(LW(0), STRING("minnnanokoe"))
            SPAWN_EVENT(minnnanokoe_evt)
        END_IF
    END_IF
    // After the final battle: the epilogue scene starts.
    IF_INT_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG8_END_AFTER_THE_BATTLE)
        CALL(evt_mario_kill_party, 0)
        CALL_CHILD(epilogue_npc_entry)
        SPAWN_EVENT(epilogue_evt)
    END_IF
    // Plaza mail delivery event.
    SPAWN_EVENT(evt_sub_mail_event)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_roten"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("A_roten"), 1, 0)
    RETURN
EVT_END()

#if VERSION >= VERSION_JP
/**
 * Zess T.'s one-ingredient recipes: for each ingredient, the dish made from it by itself before and after the
 * cookbook is solved.
 */
SimpleRecipe R_simple_recipe_table[] = {
    {"ファイアフラワー", "あつあつスープ", "あつあつスープ"},
    {"びりびりキノコ", "キノコいため", "キノコいため"},
    {"キノコ", "キノコいため", "キノコいため"},
    {"スーパーキノコ", "キノコいため", "キノコいため"},
    {"ウルトラキノコ", "キノコステーキ", "キノコステーキ"},
    {"きんきゅうキノコ", "キノコホイルやき", "キノコホイルやき"},
    {"しなびたキノコ", "", "キノコいため"},
    {"ハニーシロップ", "フレッシュジュース", "フレッシュジュース"},
    {"メイプルシロップ", "フレッシュジュース", "フレッシュジュース"},
    {"ローヤルゼリー", "フレッシュジュース", "フレッシュジュース"},
    {"じわじわキノコ", "キノコホイルやき", "キノコホイルやき"},
    {"じわじわシロップ", "フレッシュジュース", "フレッシュジュース"},
    {"ドライフラワー", "", "あつあつスープ"},
    {"ふしぎなタマゴ", "めだまやき", "めだまやき"},
    {"おうごんはっぱ", "ナンシーティー", "ナンシーティー"},
    {"トロピコマンゴー", "フレッシュジュース", "フレッシュジュース"},
    {"生パスタ", "スパゲティ", "スパゲティ"},
    {"おかしのもと", "ムースケーキ", "ムースケーキ"},
    {"レッド・カラリン", "", "スッキリドリンク"},
    {"カメカメはっぱ", "カメカメティー", "カメカメティー"},
    {"つくしんぼ", "", "あつあつスープ"},
    {"ピチピーチ", "フレッシュジュース", "フレッシュジュース"},
    {"ヤシの実", "スッキリドリンク", "スッキリドリンク"},
    {"ゆきうさぎ", "", "あつあつスープ"},
    {"どくキノコ", "", "キノコいため"},
    {"たんこぶ", "", "ナンシースペシャル"},
};

#if VERSION >= VERSION_US
/**
 * Zess T.'s two-ingredient recipes: pairs of ingredients and the dish they make. Version for the earlier
 * releases.
 */
CookRecipe R_cookbook_recipe_table[] = {
    {"キノコ", "かみなりゴロゴロ", "びりびりキノコ"},
    {"キノコ", "かみなりドッカン", "びりびりキノコ"},
    {"キノコ", "ファイアフラワー", "キノコホイルやき"},
    {"キノコ", "びりびりキノコ", "キノコホイルやき"},
    {"キノコ", "ふにゃふにゃくん", "しなびたキノコ"},
    {"スーパーキノコ", "かみなりゴロゴロ", "びりびりキノコ"},
    {"スーパーキノコ", "かみなりドッカン", "びりびりキノコ"},
    {"スーパーキノコ", "ファイアフラワー", "ナンシーディナー"},
    {"スーパーキノコ", "びりびりキノコ", "キノコホイルやき"},
    {"スーパーキノコ", "ふにゃふにゃくん", "しなびたキノコ"},
    {"スーパーキノコ", "キノコ", "キノコホイルやき"},
    {"ウルトラキノコ", "かみなりゴロゴロ", "びりびりキノコ"},
    {"ウルトラキノコ", "かみなりドッカン", "びりびりキノコ"},
    {"ウルトラキノコ", "ファイアフラワー", "ナンシースペシャル"},
    {"ウルトラキノコ", "びりびりキノコ", "キノコステーキ"},
    {"ウルトラキノコ", "ふにゃふにゃくん", "しなびたキノコ"},
    {"ウルトラキノコ", "キノコ", "キノコステーキ"},
    {"ウルトラキノコ", "スーパーキノコ", "キノコステーキ"},
    {"きんきゅうキノコ", "かみなりゴロゴロ", "びりびりキノコ"},
    {"きんきゅうキノコ", "かみなりドッカン", "びりびりキノコ"},
    {"きんきゅうキノコ", "ファイアフラワー", "ナンシーディナー"},
    {"きんきゅうキノコ", "びりびりキノコ", "キノコホイルやき"},
    {"きんきゅうキノコ", "ふにゃふにゃくん", "しなびたキノコ"},
    {"きんきゅうキノコ", "キノコ", "キノコステーキ"},
    {"きんきゅうキノコ", "スーパーキノコ", "キノコステーキ"},
    {"きんきゅうキノコ", "ウルトラキノコ", "キノコステーキ"},
    {"しなびたキノコ", "ファイアフラワー", "キノコいため"},
    {"しなびたキノコ", "びりびりキノコ", "キノコいため"},
    {"しなびたキノコ", "デカデカドリンク", "キノコ"},
    {"しなびたキノコ", "キノコ", "キノコいため"},
    {"しなびたキノコ", "スーパーキノコ", "キノコホイルやき"},
    {"しなびたキノコ", "ウルトラキノコ", "キノコステーキ"},
    {"しなびたキノコ", "きんきゅうキノコ", "キノコステーキ"},
    {"ハニーシロップ", "こおりのいぶき", "アイスキャンディ"},
    {"ハニーシロップ", "びりびりキノコ", "ハニーキノコ"},
    {"ハニーシロップ", "キノコ", "ハニーキノコ"},
    {"ハニーシロップ", "スーパーキノコ", "ハニーキノコＳ"},
    {"ハニーシロップ", "ウルトラキノコ", "ハニーキノコＺ"},
    {"ハニーシロップ", "きんきゅうキノコ", "ハニーキノコＳ"},
    {"メイプルシロップ", "こおりのいぶき", "ナンシーフラッペ"},
    {"メイプルシロップ", "びりびりキノコ", "メイプルキノコ"},
    {"メイプルシロップ", "キノコ", "メイプルキノコ"},
    {"メイプルシロップ", "スーパーキノコ", "メイプルキノコＳ"},
    {"メイプルシロップ", "ウルトラキノコ", "メイプルキノコＺ"},
    {"メイプルシロップ", "きんきゅうキノコ", "メイプルキノコＳ"},
    {"メイプルシロップ", "ハニーシロップ", "フレッシュジュース"},
    {"ローヤルゼリー", "こおりのいぶき", "ナンシーフラッペ"},
    {"ローヤルゼリー", "びりびりキノコ", "ローヤルキノコ"},
    {"ローヤルゼリー", "キノコ", "ローヤルキノコ"},
    {"ローヤルゼリー", "スーパーキノコ", "ローヤルキノコＳ"},
    {"ローヤルゼリー", "ウルトラキノコ", "ローヤルキノコＺ"},
    {"ローヤルゼリー", "きんきゅうキノコ", "ローヤルキノコＳ"},
    {"ローヤルゼリー", "ハニーシロップ", "フレッシュジュース"},
    {"ローヤルゼリー", "メイプルシロップ", "ナンシーティー"},
    {"じわじわキノコ", "かみなりゴロゴロ", "びりびりキノコ"},
    {"じわじわキノコ", "かみなりドッカン", "びりびりキノコ"},
    {"じわじわキノコ", "キラキラおとし", "ナンシーディナー"},
    {"じわじわキノコ", "ファイアフラワー", "ナンシーディナー"},
    {"じわじわキノコ", "びりびりキノコ", "キノコホイルやき"},
    {"じわじわキノコ", "キノコ", "キノコホイルやき"},
    {"じわじわキノコ", "スーパーキノコ", "ナンシーディナー"},
    {"じわじわキノコ", "ウルトラキノコ", "ナンシースペシャル"},
    {"じわじわキノコ", "きんきゅうキノコ", "ナンシーディナー"},
    {"じわじわキノコ", "ハニーシロップ", "ハニーキノコ"},
    {"じわじわキノコ", "メイプルシロップ", "メイプルキノコ"},
    {"じわじわキノコ", "ローヤルゼリー", "ローヤルキノコＳ"},
    {"じわじわシロップ", "キノコ", "キノコホイルやき"},
    {"じわじわシロップ", "スーパーキノコ", "ナンシーディナー"},
    {"じわじわシロップ", "ウルトラキノコ", "ナンシースペシャル"},
    {"じわじわシロップ", "きんきゅうキノコ", "ナンシーディナー"},
    {"じわじわシロップ", "ハニーシロップ", "フレッシュジュース"},
    {"じわじわシロップ", "メイプルシロップ", "フレッシュジュース"},
    {"じわじわシロップ", "ローヤルゼリー", "フレッシュジュース"},
    {"じわじわシロップ", "じわじわキノコ", "じわじわキノコ"},
    {"イレカエール", "かみなりゴロゴロ", "ゆらゆらじしん"},
    {"イレカエール", "かみなりドッカン", "キラキラおとし"},
    {"イレカエール", "キラキラおとし", "かみなりドッカン"},
    {"イレカエール", "こおりのいぶき", "ファイアフラワー"},
    {"イレカエール", "ファイアフラワー", "こおりのいぶき"},
    {"イレカエール", "ゆらゆらじしん", "かみなりゴロゴロ"},
    {"イレカエール", "テレサのふく", "てきヨケール"},
    {"イレカエール", "びりびりキノコ", "スーパーキノコ"},
    {"イレカエール", "てきヨケール", "テレサのふく"},
    {"イレカエール", "まどわせのこな", "しかえしのこな"},
    {"イレカエール", "しかえしのこな", "まどわせのこな"},
    {"イレカエール", "ねむれよいこよ", "スッキリドリンク"},
    {"イレカエール", "デカデカドリンク", "ミニミニくん"},
    {"イレカエール", "カチカチコウラ", "ふにゃふにゃくん"},
    {"イレカエール", "ミニミニくん", "デカデカドリンク"},
    {"イレカエール", "ふにゃふにゃくん", "カチカチコウラ"},
    {"イレカエール", "キノコ", "ハニーシロップ"},
    {"イレカエール", "スーパーキノコ", "メイプルシロップ"},
    {"イレカエール", "ウルトラキノコ", "ローヤルゼリー"},
    {"イレカエール", "きんきゅうキノコ", "スーパーキノコ"},
    {"イレカエール", "しなびたキノコ", "キノコ"},
    {"イレカエール", "スッキリドリンク", "ねむれよいこよ"},
    {"イレカエール", "ハニーシロップ", "キノコ"},
    {"イレカエール", "メイプルシロップ", "スーパーキノコ"},
    {"イレカエール", "ローヤルゼリー", "ウルトラキノコ"},
    {"イレカエール", "じわじわキノコ", "どくキノコ"},
    {"イレカエール", "じわじわシロップ", "ハニーシロップ"},
    {"ドライフラワー", "ファイアフラワー", "あつあつスープ"},
    {"ドライフラワー", "びりびりキノコ", "かみなりドッカン"},
    {"ドライフラワー", "キノコ", "うちゅうしょく"},
    {"ドライフラワー", "スーパーキノコ", "うちゅうしょく"},
    {"ドライフラワー", "ウルトラキノコ", "うちゅうしょく"},
    {"ドライフラワー", "きんきゅうキノコ", "うちゅうしょく"},
    {"ドライフラワー", "しなびたキノコ", "うちゅうしょく"},
    {"ドライフラワー", "じわじわキノコ", "うちゅうしょく"},
    {"ドライフラワー", "ホットドッグ", "うちゅうしょく"},
    {"ふしぎなタマゴ", "ファイアフラワー", "バクハツタマゴ"},
    {"ふしぎなタマゴ", "キノコ", "キセツのオムレツ"},
    {"ふしぎなタマゴ", "スーパーキノコ", "キセツのオムレツ"},
    {"ふしぎなタマゴ", "ウルトラキノコ", "キセツのオムレツ"},
    {"ふしぎなタマゴ", "きんきゅうキノコ", "キセツのオムレツ"},
    {"ふしぎなタマゴ", "ドライフラワー", "うちゅうしょく"},
    {"おうごんはっぱ", "こおりのいぶき", "ゆきうさぎ"},
    {"おうごんはっぱ", "キノコ", "キノコいため"},
    {"おうごんはっぱ", "スーパーキノコ", "キノコホイルやき"},
    {"おうごんはっぱ", "ウルトラキノコ", "キノコステーキ"},
    {"おうごんはっぱ", "きんきゅうキノコ", "キノコステーキ"},
    {"おうごんはっぱ", "じわじわキノコ", "こうちゃキノコ"},
    {"おうごんはっぱ", "ドライフラワー", "うちゅうしょく"},
    {"トロピコマンゴー", "びりびりキノコ", "ナンシーディナー"},
    {"トロピコマンゴー", "キノコ", "ナンシーディナー"},
    {"トロピコマンゴー", "スーパーキノコ", "ナンシーディナー"},
    {"トロピコマンゴー", "ウルトラキノコ", "ナンシーディナー"},
    {"トロピコマンゴー", "ハニーシロップ", "フルーツパフェ"},
    {"トロピコマンゴー", "メイプルシロップ", "フルーツパフェ"},
    {"トロピコマンゴー", "ローヤルゼリー", "フルーツパフェ"},
    {"トロピコマンゴー", "じわじわシロップ", "フルーツパフェ"},
    {"トロピコマンゴー", "ドライフラワー", "うちゅうしょく"},
    {"生パスタ", "びりびりキノコ", "ナンシーディナー"},
    {"生パスタ", "キノコ", "ナンシースペシャル"},
    {"生パスタ", "スーパーキノコ", "ナンシースペシャル"},
    {"生パスタ", "ウルトラキノコ", "ナンシーデラックス"},
    {"生パスタ", "きんきゅうキノコ", "ナンシースペシャル"},
    {"生パスタ", "しなびたキノコ", "ナンシースペシャル"},
    {"生パスタ", "ドライフラワー", "うちゅうしょく"},
    {"生パスタ", "ふしぎなタマゴ", "ナンシーディナー"},
    {"おかしのもと", "ファイアフラワー", "ファイアキャンディ"},
    {"おかしのもと", "びりびりキノコ", "びりびりキャンディ"},
    {"おかしのもと", "まどわせのこな", "メロメロケーキ"},
    {"おかしのもと", "キノコ", "キノコケーキ"},
    {"おかしのもと", "スーパーキノコ", "キノコケーキ"},
    {"おかしのもと", "ウルトラキノコ", "キノコクレープ"},
    {"おかしのもと", "きんきゅうキノコ", "キノコケーキ"},
    {"おかしのもと", "ハニーシロップ", "ハニーあめ"},
    {"おかしのもと", "メイプルシロップ", "ナンシークッキー"},
    {"おかしのもと", "ローヤルゼリー", "ローヤルキャンディ"},
    {"おかしのもと", "じわじわキノコ", "キノコケーキ"},
    {"おかしのもと", "じわじわシロップ", "ナンシークッキー"},
    {"おかしのもと", "ドライフラワー", "うちゅうしょく"},
    {"おかしのもと", "ふしぎなタマゴ", "ナンシークッキー"},
    {"おかしのもと", "トロピコマンゴー", "マンゴープディング"},
    {"レッド・カラリン", "ファイアフラワー", "あつあつスープ"},
    {"レッド・カラリン", "しなびたキノコ", "キノコ"},
    {"レッド・カラリン", "スッキリドリンク", "すみぢる"},
    {"レッド・カラリン", "ハニーシロップ", "スッキリドリンク"},
    {"レッド・カラリン", "メイプルシロップ", "スッキリドリンク"},
    {"レッド・カラリン", "ローヤルゼリー", "スッキリドリンク"},
    {"レッド・カラリン", "生パスタ", "カラリーナパスタ"},
    {"レッド・カラリン", "おかしのもと", "ファイアキャンディ"},
    {"カメカメはっぱ", "キノコ", "キノコいため"},
    {"カメカメはっぱ", "スーパーキノコ", "キノコホイルやき"},
    {"カメカメはっぱ", "ウルトラキノコ", "キノコステーキ"},
    {"カメカメはっぱ", "きんきゅうキノコ", "キノコステーキ"},
    {"カメカメはっぱ", "ハニーシロップ", "フレッシュジュース"},
    {"カメカメはっぱ", "メイプルシロップ", "フレッシュジュース"},
    {"カメカメはっぱ", "ローヤルゼリー", "フレッシュジュース"},
    {"カメカメはっぱ", "じわじわキノコ", "こうちゃキノコ"},
    {"カメカメはっぱ", "じわじわシロップ", "フレッシュジュース"},
    {"カメカメはっぱ", "ドライフラワー", "うちゅうしょく"},
    {"カメカメはっぱ", "おうごんはっぱ", "ヘルスィーサラダ"},
    {"カメカメはっぱ", "トロピコマンゴー", "カメまん"},
    {"カメカメはっぱ", "生パスタ", "カメスパ"},
    {"カメカメはっぱ", "レッド・カラリン", "すみぢる"},
    {"つくしんぼ", "キノコ", "ナンシーディナー"},
    {"つくしんぼ", "スーパーキノコ", "ナンシーディナー"},
    {"つくしんぼ", "ウルトラキノコ", "ナンシースペシャル"},
    {"つくしんぼ", "きんきゅうキノコ", "ナンシーディナー"},
    {"つくしんぼ", "ドライフラワー", "うちゅうしょく"},
    {"つくしんぼ", "ふしぎなタマゴ", "キセツのオムレツ"},
    {"つくしんぼ", "カメカメはっぱ", "ヘルスィーサラダ"},
    {"ピチピーチ", "びりびりキノコ", "ナンシーディナー"},
    {"ピチピーチ", "まどわせのこな", "メロメロケーキ"},
    {"ピチピーチ", "キノコ", "ナンシーディナー"},
    {"ピチピーチ", "スーパーキノコ", "ナンシーディナー"},
    {"ピチピーチ", "ウルトラキノコ", "ナンシースペシャル"},
    {"ピチピーチ", "きんきゅうキノコ", "ナンシーディナー"},
    {"ピチピーチ", "しなびたキノコ", "キノコ"},
    {"ピチピーチ", "ハニーシロップ", "フルーツパフェ"},
    {"ピチピーチ", "メイプルシロップ", "フルーツパフェ"},
    {"ピチピーチ", "ローヤルゼリー", "フルーツパフェ"},
    {"ピチピーチ", "ドライフラワー", "うちゅうしょく"},
    {"ピチピーチ", "トロピコマンゴー", "フルーツパフェ"},
    {"ピチピーチ", "おかしのもと", "ピーチタルト"},
    {"ピチピーチ", "レッド・カラリン", "スッキリドリンク"},
    {"ヤシの実", "ファイアフラワー", "ココナッツボム"},
    {"ヤシの実", "ドライフラワー", "うちゅうしょく"},
    {"ヤシの実", "トロピコマンゴー", "フレッシュジュース"},
    {"ヤシの実", "生パスタ", "ナンシーディナー"},
    {"ヤシの実", "おかしのもと", "ココナツキャンディ"},
    {"ヤシの実", "カメカメはっぱ", "フレッシュジュース"},
    {"ヤシの実", "ピチピーチ", "フレッシュジュース"},
    {"キノコいため", "キラキラおとし", "ほしふるディナー"},
    {"キノコいため", "ドライフラワー", "うちゅうしょく"},
    {"キノコホイルやき", "キラキラおとし", "ほしふるディナー"},
    {"キノコホイルやき", "ドライフラワー", "うちゅうしょく"},
    {"キノコステーキ", "キラキラおとし", "ほしふるディナー"},
    {"キノコステーキ", "ドライフラワー", "うちゅうしょく"},
    {"しっぱいりょうり", "ドライフラワー", "うちゅうしょく"},
    {"ハニーキノコ", "ドライフラワー", "うちゅうしょく"},
    {"メイプルキノコ", "ドライフラワー", "うちゅうしょく"},
    {"ローヤルキノコ", "ドライフラワー", "うちゅうしょく"},
    {"ハニーキノコＳ", "ドライフラワー", "うちゅうしょく"},
    {"メイプルキノコＳ", "ドライフラワー", "うちゅうしょく"},
    {"ローヤルキノコＳ", "ドライフラワー", "うちゅうしょく"},
    {"ハニーキノコＺ", "ドライフラワー", "うちゅうしょく"},
    {"メイプルキノコＺ", "ドライフラワー", "うちゅうしょく"},
    {"ローヤルキノコＺ", "ドライフラワー", "うちゅうしょく"},
    {"ナンシーディナー", "カチカチコウラ", "カチカチりょうり"},
    {"ナンシーディナー", "ドライフラワー", "うちゅうしょく"},
    {"ナンシースペシャル", "カチカチコウラ", "カチカチりょうり"},
    {"ナンシースペシャル", "ドライフラワー", "うちゅうしょく"},
    {"ナンシーデラックス", "カチカチコウラ", "カチカチりょうり"},
    {"ナンシーデラックス", "ドライフラワー", "うちゅうしょく"},
    {"ナンシーダイナマイ", "ドライフラワー", "バクハツタマゴ"},
    {"ナンシーティー", "レッド・カラリン", "すみぢる"},
    {"ゆきうさぎ", "あつあつスープ", "いつまでもふたりで"},
    {"キノコケーキ", "ドライフラワー", "うちゅうしょく"},
    {"キノコクレープ", "ドライフラワー", "うちゅうしょく"},
    {"ムースケーキ", "ドライフラワー", "うちゅうしょく"},
    {"フルーツパフェ", "ドライフラワー", "うちゅうしょく"},
    {"バクハツタマゴ", "ドライフラワー", "うちゅうしょく"},
    {"イカスミパスタ", "ドライフラワー", "うちゅうしょく"},
    {"スパゲティ", "ドライフラワー", "うちゅうしょく"},
    {"スパゲティ", "レッド・カラリン", "カラリーナパスタ"},
    {"スパゲティ", "カメカメはっぱ", "カメスパ"},
    {"こうちゃキノコ", "レッド・カラリン", "すみぢる"},
    {"どくキノコ", "イレカエール", "キノコ"},
    {"どくキノコ", "ドライフラワー", "うちゅうしょく"},
    {"どくキノコ", "おうごんはっぱ", "こうちゃキノコ"},
    {"どくキノコ", "カメカメはっぱ", "こうちゃキノコ"},
    {"ショコラケーキ", "ドライフラワー", "うちゅうしょく"},
    {"マンゴープディング", "ドライフラワー", "うちゅうしょく"},
    {"マンゴープディング", "ふしぎなタマゴ", "はつこいプディング"},
    {"はつこいプディング", "ドライフラワー", "うちゅうしょく"},
    {"ほしふるディナー", "ドライフラワー", "うちゅうしょく"},
    {"ほしふるディナー", "フルーツパフェ", "ナンシーディナー"},
    {"しれんのナベ", "ドライフラワー", "どくキノコ"},
    {"いつまでもふたりで", "ドライフラワー", "うちゅうしょく"},
    {"いつまでもふたりで", "どくキノコ", "しれんのナベ"},
    {"すみぢる", "じわじわキノコ", "どくキノコ"},
    {"すみぢる", "生パスタ", "イカスミパスタ"},
    {"すみぢる", "おかしのもと", "ショコラケーキ"},
    {"すみぢる", "ムースケーキ", "ショコラケーキ"},
    {"すみぢる", "スパゲティ", "イカスミパスタ"},
    {"キセツのオムレツ", "ドライフラワー", "うちゅうしょく"},
    {"カメカメティー", "レッド・カラリン", "すみぢる"},
    {"カメスパ", "ドライフラワー", "うちゅうしょく"},
    {"カメスパ", "レッド・カラリン", "カラリーナパスタ"},
    {"カメスパ", "すみぢる", "イカスミパスタ"},
    {"カラリーナパスタ", "ドライフラワー", "うちゅうしょく"},
    {"カラリーナパスタ", "ヤシの実", "ナンシーディナー"},
    {"カラリーナパスタ", "すみぢる", "イカスミパスタ"},
    {"メロメロケーキ", "ドライフラワー", "うちゅうしょく"},
    {"ピーチタルト", "ドライフラワー", "うちゅうしょく"},
    {"びりびりキャンディ", "ドライフラワー", "うちゅうしょく"},
    {"ファイアキャンディ", "ドライフラワー", "うちゅうしょく"},
    {"ハニーあめ", "ドライフラワー", "うちゅうしょく"},
    {"ココナツキャンディ", "ドライフラワー", "うちゅうしょく"},
    {"ローヤルキャンディ", "ドライフラワー", "うちゅうしょく"},
    {"ナンシークッキー", "ドライフラワー", "うちゅうしょく"},
    {"ヘルスィーサラダ", "ドライフラワー", "うちゅうしょく"},
    {"ヘルスィーサラダ", "生パスタ", "ナンシーディナー"},
    {"ヘルスィーサラダ", "キノコいため", "ナンシーディナー"},
    {"ヘルスィーサラダ", "キノコホイルやき", "ナンシースペシャル"},
    {"ヘルスィーサラダ", "キノコステーキ", "ナンシーデラックス"},
    {"ヘルスィーサラダ", "イカスミパスタ", "ナンシースペシャル"},
    {"ヘルスィーサラダ", "スパゲティ", "ナンシーディナー"},
    {"ヘルスィーサラダ", "カメスパ", "ナンシーディナー"},
    {"ヘルスィーサラダ", "カラリーナパスタ", "ナンシースペシャル"},
    {"カメまん", "ドライフラワー", "うちゅうしょく"},
    {"フレッシュジュース", "レッド・カラリン", "すみぢる"},
    {"たんこぶ", "ドライフラワー", "うちゅうしょく"},
    {"たんこぶ", "おうごんはっぱ", "ナンシーデラックス"},
    {"きんかい", "イレカエール", "キノコ"},
    {"きんかい×３", "イレカエール", "きんかい"},
    {"ココナッツボム", "ドライフラワー", "ヤシの実"},
    {"ココナッツボム", "バクハツタマゴ", "ナンシーダイナマイ"},
    {"カチカチりょうり", "ドライフラワー", "カチカチコウラ"},
};
#else
/**
 * Zess T.'s two-ingredient recipes: pairs of ingredients and the dish they make. Version for the later
 * releases.
 */
CookRecipe R_cookbook_recipe_table[] = {
    {"かみなりドッカン", "かみなりゴロゴロ", "しれんのナベ"},
    {"キノコ", "かみなりゴロゴロ", "びりびりキノコ"},
    {"キノコ", "かみなりドッカン", "びりびりキノコ"},
    {"キノコ", "ファイアフラワー", "キノコホイルやき"},
    {"キノコ", "びりびりキノコ", "キノコホイルやき"},
    {"キノコ", "ふにゃふにゃくん", "しなびたキノコ"},
    {"スーパーキノコ", "かみなりゴロゴロ", "びりびりキノコ"},
    {"スーパーキノコ", "かみなりドッカン", "びりびりキノコ"},
    {"スーパーキノコ", "ファイアフラワー", "ナンシーディナー"},
    {"スーパーキノコ", "びりびりキノコ", "キノコホイルやき"},
    {"スーパーキノコ", "ふにゃふにゃくん", "しなびたキノコ"},
    {"スーパーキノコ", "キノコ", "キノコホイルやき"},
    {"ウルトラキノコ", "かみなりゴロゴロ", "びりびりキノコ"},
    {"ウルトラキノコ", "かみなりドッカン", "びりびりキノコ"},
    {"ウルトラキノコ", "ファイアフラワー", "ナンシースペシャル"},
    {"ウルトラキノコ", "びりびりキノコ", "キノコステーキ"},
    {"ウルトラキノコ", "ふにゃふにゃくん", "しなびたキノコ"},
    {"ウルトラキノコ", "キノコ", "キノコステーキ"},
    {"ウルトラキノコ", "スーパーキノコ", "キノコステーキ"},
    {"きんきゅうキノコ", "かみなりゴロゴロ", "びりびりキノコ"},
    {"きんきゅうキノコ", "かみなりドッカン", "びりびりキノコ"},
    {"きんきゅうキノコ", "ファイアフラワー", "ナンシーディナー"},
    {"きんきゅうキノコ", "びりびりキノコ", "キノコホイルやき"},
    {"きんきゅうキノコ", "ふにゃふにゃくん", "しなびたキノコ"},
    {"きんきゅうキノコ", "キノコ", "キノコステーキ"},
    {"きんきゅうキノコ", "スーパーキノコ", "キノコステーキ"},
    {"きんきゅうキノコ", "ウルトラキノコ", "キノコステーキ"},
    {"しなびたキノコ", "ファイアフラワー", "キノコいため"},
    {"しなびたキノコ", "びりびりキノコ", "キノコいため"},
    {"しなびたキノコ", "デカデカドリンク", "キノコ"},
    {"しなびたキノコ", "キノコ", "キノコいため"},
    {"しなびたキノコ", "スーパーキノコ", "キノコホイルやき"},
    {"しなびたキノコ", "ウルトラキノコ", "キノコステーキ"},
    {"しなびたキノコ", "きんきゅうキノコ", "キノコステーキ"},
    {"ハニーシロップ", "こおりのいぶき", "アイスキャンディ"},
    {"ハニーシロップ", "びりびりキノコ", "ハニーキノコ"},
    {"ハニーシロップ", "キノコ", "ハニーキノコ"},
    {"ハニーシロップ", "スーパーキノコ", "ハニーキノコＳ"},
    {"ハニーシロップ", "ウルトラキノコ", "ハニーキノコＺ"},
    {"ハニーシロップ", "きんきゅうキノコ", "ハニーキノコＳ"},
    {"メイプルシロップ", "こおりのいぶき", "ナンシーフラッペ"},
    {"メイプルシロップ", "びりびりキノコ", "メイプルキノコ"},
    {"メイプルシロップ", "キノコ", "メイプルキノコ"},
    {"メイプルシロップ", "スーパーキノコ", "メイプルキノコＳ"},
    {"メイプルシロップ", "ウルトラキノコ", "メイプルキノコＺ"},
    {"メイプルシロップ", "きんきゅうキノコ", "メイプルキノコＳ"},
    {"メイプルシロップ", "ハニーシロップ", "フレッシュジュース"},
    {"ローヤルゼリー", "こおりのいぶき", "ナンシーフラッペ"},
    {"ローヤルゼリー", "びりびりキノコ", "ローヤルキノコ"},
    {"ローヤルゼリー", "キノコ", "ローヤルキノコ"},
    {"ローヤルゼリー", "スーパーキノコ", "ローヤルキノコＳ"},
    {"ローヤルゼリー", "ウルトラキノコ", "ローヤルキノコＺ"},
    {"ローヤルゼリー", "きんきゅうキノコ", "ローヤルキノコＳ"},
    {"ローヤルゼリー", "ハニーシロップ", "フレッシュジュース"},
    {"ローヤルゼリー", "メイプルシロップ", "ナンシーティー"},
    {"じわじわキノコ", "かみなりゴロゴロ", "びりびりキノコ"},
    {"じわじわキノコ", "かみなりドッカン", "びりびりキノコ"},
    {"じわじわキノコ", "キラキラおとし", "ナンシーディナー"},
    {"じわじわキノコ", "ファイアフラワー", "ナンシーディナー"},
    {"じわじわキノコ", "びりびりキノコ", "キノコホイルやき"},
    {"じわじわキノコ", "キノコ", "キノコホイルやき"},
    {"じわじわキノコ", "スーパーキノコ", "ナンシーディナー"},
    {"じわじわキノコ", "ウルトラキノコ", "ナンシースペシャル"},
    {"じわじわキノコ", "きんきゅうキノコ", "ナンシーディナー"},
    {"じわじわキノコ", "ハニーシロップ", "ハニーキノコ"},
    {"じわじわキノコ", "メイプルシロップ", "メイプルキノコ"},
    {"じわじわキノコ", "ローヤルゼリー", "メイプルキノコＳ"},
    {"じわじわシロップ", "キノコ", "キノコホイルやき"},
    {"じわじわシロップ", "スーパーキノコ", "ナンシーディナー"},
    {"じわじわシロップ", "ウルトラキノコ", "ナンシースペシャル"},
    {"じわじわシロップ", "きんきゅうキノコ", "ナンシーディナー"},
    {"じわじわシロップ", "ハニーシロップ", "フレッシュジュース"},
    {"じわじわシロップ", "メイプルシロップ", "フレッシュジュース"},
    {"じわじわシロップ", "ローヤルゼリー", "フレッシュジュース"},
    {"じわじわシロップ", "じわじわキノコ", "じわじわキノコ"},
    {"イレカエール", "かみなりゴロゴロ", "ゆらゆらじしん"},
    {"イレカエール", "かみなりドッカン", "キラキラおとし"},
    {"イレカエール", "キラキラおとし", "かみなりドッカン"},
    {"イレカエール", "こおりのいぶき", "ファイアフラワー"},
    {"イレカエール", "ファイアフラワー", "こおりのいぶき"},
    {"イレカエール", "ゆらゆらじしん", "かみなりゴロゴロ"},
    {"イレカエール", "テレサのふく", "てきヨケール"},
    {"イレカエール", "びりびりキノコ", "スーパーキノコ"},
    {"イレカエール", "てきヨケール", "テレサのふく"},
    {"イレカエール", "まどわせのこな", "しかえしのこな"},
    {"イレカエール", "しかえしのこな", "まどわせのこな"},
    {"イレカエール", "ねむれよいこよ", "スッキリドリンク"},
    {"イレカエール", "デカデカドリンク", "ミニミニくん"},
    {"イレカエール", "カチカチコウラ", "ふにゃふにゃくん"},
    {"イレカエール", "ミニミニくん", "デカデカドリンク"},
    {"イレカエール", "ふにゃふにゃくん", "カチカチコウラ"},
    {"イレカエール", "キノコ", "ハニーシロップ"},
    {"イレカエール", "スーパーキノコ", "メイプルシロップ"},
    {"イレカエール", "ウルトラキノコ", "ローヤルゼリー"},
    {"イレカエール", "きんきゅうキノコ", "スーパーキノコ"},
    {"イレカエール", "しなびたキノコ", "キノコ"},
    {"イレカエール", "スッキリドリンク", "ねむれよいこよ"},
    {"イレカエール", "ハニーシロップ", "キノコ"},
    {"イレカエール", "メイプルシロップ", "スーパーキノコ"},
    {"イレカエール", "ローヤルゼリー", "ウルトラキノコ"},
    {"イレカエール", "じわじわキノコ", "どくキノコ"},
    {"イレカエール", "じわじわシロップ", "ハニーシロップ"},
    {"ドライフラワー", "ファイアフラワー", "あつあつスープ"},
    {"ドライフラワー", "びりびりキノコ", "かみなりドッカン"},
    {"ドライフラワー", "キノコ", "うちゅうしょく"},
    {"ドライフラワー", "スーパーキノコ", "うちゅうしょく"},
    {"ドライフラワー", "ウルトラキノコ", "うちゅうしょく"},
    {"ドライフラワー", "きんきゅうキノコ", "うちゅうしょく"},
    {"ドライフラワー", "しなびたキノコ", "うちゅうしょく"},
    {"ドライフラワー", "じわじわキノコ", "うちゅうしょく"},
    {"ドライフラワー", "ホットドッグ", "うちゅうしょく"},
    {"ふしぎなタマゴ", "ファイアフラワー", "バクハツタマゴ"},
    {"ふしぎなタマゴ", "キノコ", "キセツのオムレツ"},
    {"ふしぎなタマゴ", "スーパーキノコ", "キセツのオムレツ"},
    {"ふしぎなタマゴ", "ウルトラキノコ", "キセツのオムレツ"},
    {"ふしぎなタマゴ", "きんきゅうキノコ", "キセツのオムレツ"},
    {"ふしぎなタマゴ", "ドライフラワー", "うちゅうしょく"},
    {"おうごんはっぱ", "こおりのいぶき", "ゆきうさぎ"},
    {"おうごんはっぱ", "キノコ", "きんきゅうキノコ"},
    {"おうごんはっぱ", "スーパーキノコ", "きんきゅうキノコ"},
    {"おうごんはっぱ", "ウルトラキノコ", "きんきゅうキノコ"},
    {"おうごんはっぱ", "きんきゅうキノコ", "きんきゅうキノコ"},
    {"おうごんはっぱ", "じわじわキノコ", "こうちゃキノコ"},
    {"おうごんはっぱ", "ドライフラワー", "うちゅうしょく"},
    {"トロピコマンゴー", "びりびりキノコ", "ナンシーディナー"},
    {"トロピコマンゴー", "スーパーキノコ", "ナンシーディナー"},
    {"トロピコマンゴー", "ウルトラキノコ", "ナンシーディナー"},
    {"トロピコマンゴー", "ハニーシロップ", "フルーツパフェ"},
    {"トロピコマンゴー", "メイプルシロップ", "フルーツパフェ"},
    {"トロピコマンゴー", "ローヤルゼリー", "フルーツパフェ"},
    {"トロピコマンゴー", "じわじわシロップ", "フルーツパフェ"},
    {"トロピコマンゴー", "ドライフラワー", "うちゅうしょく"},
    {"生パスタ", "びりびりキノコ", "ナンシーディナー"},
    {"生パスタ", "キノコ", "ナンシーディナー"},
    {"生パスタ", "スーパーキノコ", "ナンシーディナー"},
    {"生パスタ", "ウルトラキノコ", "ナンシースペシャル"},
    {"生パスタ", "きんきゅうキノコ", "ナンシーディナー"},
    {"生パスタ", "しなびたキノコ", "ナンシーディナー"},
    {"生パスタ", "ドライフラワー", "うちゅうしょく"},
    {"生パスタ", "ふしぎなタマゴ", "ナンシーディナー"},
    {"おかしのもと", "ファイアフラワー", "ファイアキャンディ"},
    {"おかしのもと", "びりびりキノコ", "びりびりキャンディ"},
    {"おかしのもと", "まどわせのこな", "メロメロケーキ"},
    {"おかしのもと", "キノコ", "キノコケーキ"},
    {"おかしのもと", "スーパーキノコ", "キノコケーキ"},
    {"おかしのもと", "ウルトラキノコ", "キノコクレープ"},
    {"おかしのもと", "きんきゅうキノコ", "キノコケーキ"},
    {"おかしのもと", "ハニーシロップ", "ハニーあめ"},
    {"おかしのもと", "メイプルシロップ", "ナンシークッキー"},
    {"おかしのもと", "ローヤルゼリー", "ローヤルキャンディ"},
    {"おかしのもと", "じわじわキノコ", "キノコケーキ"},
    {"おかしのもと", "じわじわシロップ", "ナンシークッキー"},
    {"おかしのもと", "ドライフラワー", "うちゅうしょく"},
    {"おかしのもと", "ふしぎなタマゴ", "ナンシークッキー"},
    {"おかしのもと", "トロピコマンゴー", "マンゴープディング"},
    {"レッド・カラリン", "ファイアフラワー", "あつあつスープ"},
    {"レッド・カラリン", "しなびたキノコ", "キノコ"},
    {"レッド・カラリン", "スッキリドリンク", "すみぢる"},
    {"レッド・カラリン", "ハニーシロップ", "スッキリドリンク"},
    {"レッド・カラリン", "メイプルシロップ", "スッキリドリンク"},
    {"レッド・カラリン", "ローヤルゼリー", "スッキリドリンク"},
    {"レッド・カラリン", "生パスタ", "カラリーナパスタ"},
    {"レッド・カラリン", "おかしのもと", "ファイアキャンディ"},
    {"カメカメはっぱ", "キノコ", "きんきゅうキノコ"},
    {"カメカメはっぱ", "スーパーキノコ", "きんきゅうキノコ"},
    {"カメカメはっぱ", "ウルトラキノコ", "きんきゅうキノコ"},
    {"カメカメはっぱ", "きんきゅうキノコ", "きんきゅうキノコ"},
    {"カメカメはっぱ", "ハニーシロップ", "フレッシュジュース"},
    {"カメカメはっぱ", "メイプルシロップ", "フレッシュジュース"},
    {"カメカメはっぱ", "ローヤルゼリー", "フレッシュジュース"},
    {"カメカメはっぱ", "じわじわキノコ", "こうちゃキノコ"},
    {"カメカメはっぱ", "じわじわシロップ", "フレッシュジュース"},
    {"カメカメはっぱ", "ドライフラワー", "うちゅうしょく"},
    {"カメカメはっぱ", "おうごんはっぱ", "ヘルスィーサラダ"},
    {"カメカメはっぱ", "トロピコマンゴー", "カメまん"},
    {"カメカメはっぱ", "生パスタ", "カメスパ"},
    {"カメカメはっぱ", "レッド・カラリン", "すみぢる"},
    {"つくしんぼ", "キノコ", "ナンシーディナー"},
    {"つくしんぼ", "スーパーキノコ", "ナンシーディナー"},
    {"つくしんぼ", "ウルトラキノコ", "ナンシースペシャル"},
    {"つくしんぼ", "きんきゅうキノコ", "ナンシーディナー"},
    {"つくしんぼ", "ドライフラワー", "うちゅうしょく"},
    {"つくしんぼ", "ふしぎなタマゴ", "キセツのオムレツ"},
    {"つくしんぼ", "カメカメはっぱ", "ヘルスィーサラダ"},
    {"ピチピーチ", "びりびりキノコ", "ナンシーディナー"},
    {"ピチピーチ", "まどわせのこな", "メロメロケーキ"},
    {"ピチピーチ", "スーパーキノコ", "ナンシーディナー"},
    {"ピチピーチ", "ウルトラキノコ", "ナンシーディナー"},
    {"ピチピーチ", "しなびたキノコ", "キノコ"},
    {"ピチピーチ", "ハニーシロップ", "フルーツパフェ"},
    {"ピチピーチ", "メイプルシロップ", "フルーツパフェ"},
    {"ピチピーチ", "ローヤルゼリー", "フルーツパフェ"},
    {"ピチピーチ", "ドライフラワー", "うちゅうしょく"},
    {"ピチピーチ", "トロピコマンゴー", "フルーツパフェ"},
    {"ピチピーチ", "おかしのもと", "ピーチタルト"},
    {"ピチピーチ", "レッド・カラリン", "スッキリドリンク"},
    {"ヤシの実", "ファイアフラワー", "ココナッツボム"},
    {"ヤシの実", "ドライフラワー", "うちゅうしょく"},
    {"ヤシの実", "トロピコマンゴー", "フレッシュジュース"},
    {"ヤシの実", "生パスタ", "ナンシーディナー"},
    {"ヤシの実", "おかしのもと", "ココナツキャンディ"},
    {"ヤシの実", "カメカメはっぱ", "フレッシュジュース"},
    {"ヤシの実", "ピチピーチ", "フレッシュジュース"},
    {"キノコいため", "キラキラおとし", "ほしふるディナー"},
    {"キノコいため", "ドライフラワー", "うちゅうしょく"},
    {"キノコホイルやき", "キラキラおとし", "ほしふるディナー"},
    {"キノコホイルやき", "ドライフラワー", "うちゅうしょく"},
    {"キノコステーキ", "キラキラおとし", "ほしふるディナー"},
    {"キノコステーキ", "ドライフラワー", "うちゅうしょく"},
    {"しっぱいりょうり", "ドライフラワー", "うちゅうしょく"},
    {"ハニーキノコ", "ドライフラワー", "うちゅうしょく"},
    {"メイプルキノコ", "ドライフラワー", "うちゅうしょく"},
    {"ローヤルキノコ", "ドライフラワー", "うちゅうしょく"},
    {"ハニーキノコＳ", "ドライフラワー", "うちゅうしょく"},
    {"メイプルキノコＳ", "ドライフラワー", "うちゅうしょく"},
    {"ローヤルキノコＳ", "ドライフラワー", "うちゅうしょく"},
    {"ハニーキノコＺ", "ドライフラワー", "うちゅうしょく"},
    {"メイプルキノコＺ", "ドライフラワー", "うちゅうしょく"},
    {"ローヤルキノコＺ", "ドライフラワー", "うちゅうしょく"},
    {"ナンシーディナー", "カチカチコウラ", "カチカチりょうり"},
    {"ナンシーディナー", "ドライフラワー", "うちゅうしょく"},
    {"ナンシースペシャル", "カチカチコウラ", "カチカチりょうり"},
    {"ナンシースペシャル", "ドライフラワー", "うちゅうしょく"},
    {"ナンシーデラックス", "カチカチコウラ", "カチカチりょうり"},
    {"ナンシーデラックス", "ドライフラワー", "うちゅうしょく"},
    {"ナンシーダイナマイ", "ドライフラワー", "バクハツタマゴ"},
    {"ナンシーティー", "レッド・カラリン", "すみぢる"},
    {"ゆきうさぎ", "あつあつスープ", "いつまでもふたりで"},
    {"キノコケーキ", "ドライフラワー", "うちゅうしょく"},
    {"キノコクレープ", "ドライフラワー", "うちゅうしょく"},
    {"ムースケーキ", "ドライフラワー", "うちゅうしょく"},
    {"フルーツパフェ", "ドライフラワー", "うちゅうしょく"},
    {"バクハツタマゴ", "ドライフラワー", "うちゅうしょく"},
    {"イカスミパスタ", "ドライフラワー", "うちゅうしょく"},
    {"スパゲティ", "ドライフラワー", "うちゅうしょく"},
    {"スパゲティ", "レッド・カラリン", "カラリーナパスタ"},
    {"スパゲティ", "カメカメはっぱ", "カメスパ"},
    {"こうちゃキノコ", "レッド・カラリン", "すみぢる"},
    {"どくキノコ", "イレカエール", "ウルトラキノコ"},
    {"どくキノコ", "ドライフラワー", "うちゅうしょく"},
    {"どくキノコ", "おうごんはっぱ", "こうちゃキノコ"},
    {"ショコラケーキ", "ドライフラワー", "うちゅうしょく"},
    {"マンゴープディング", "ドライフラワー", "うちゅうしょく"},
    {"マンゴープディング", "ふしぎなタマゴ", "はつこいプディング"},
    {"はつこいプディング", "ドライフラワー", "うちゅうしょく"},
    {"ほしふるディナー", "ドライフラワー", "うちゅうしょく"},
    {"ほしふるディナー", "フルーツパフェ", "ナンシーディナー"},
    {"しれんのナベ", "ドライフラワー", "どくキノコ"},
    {"いつまでもふたりで", "ドライフラワー", "うちゅうしょく"},
    {"いつまでもふたりで", "どくキノコ", "しれんのナベ"},
    {"すみぢる", "じわじわキノコ", "どくキノコ"},
    {"すみぢる", "生パスタ", "イカスミパスタ"},
    {"すみぢる", "おかしのもと", "ショコラケーキ"},
    {"すみぢる", "ムースケーキ", "ショコラケーキ"},
    {"すみぢる", "スパゲティ", "イカスミパスタ"},
    {"キセツのオムレツ", "ドライフラワー", "うちゅうしょく"},
    {"カメカメティー", "レッド・カラリン", "すみぢる"},
    {"カメスパ", "ドライフラワー", "うちゅうしょく"},
    {"カメスパ", "レッド・カラリン", "カラリーナパスタ"},
    {"カメスパ", "すみぢる", "イカスミパスタ"},
    {"カラリーナパスタ", "ドライフラワー", "うちゅうしょく"},
    {"カラリーナパスタ", "ヤシの実", "ナンシーディナー"},
    {"カラリーナパスタ", "すみぢる", "イカスミパスタ"},
    {"メロメロケーキ", "ドライフラワー", "うちゅうしょく"},
    {"ピーチタルト", "ドライフラワー", "うちゅうしょく"},
    {"びりびりキャンディ", "ドライフラワー", "うちゅうしょく"},
    {"ファイアキャンディ", "ドライフラワー", "うちゅうしょく"},
    {"ハニーあめ", "ドライフラワー", "うちゅうしょく"},
    {"ココナツキャンディ", "ドライフラワー", "うちゅうしょく"},
    {"ローヤルキャンディ", "ドライフラワー", "うちゅうしょく"},
    {"ナンシークッキー", "ドライフラワー", "うちゅうしょく"},
    {"ヘルスィーサラダ", "ドライフラワー", "うちゅうしょく"},
    {"ヘルスィーサラダ", "生パスタ", "ナンシーディナー"},
    {"ヘルスィーサラダ", "キノコいため", "ナンシーディナー"},
    {"ヘルスィーサラダ", "キノコホイルやき", "ナンシースペシャル"},
    {"ヘルスィーサラダ", "キノコステーキ", "ナンシーデラックス"},
    {"ヘルスィーサラダ", "イカスミパスタ", "ナンシースペシャル"},
    {"ヘルスィーサラダ", "スパゲティ", "ナンシーディナー"},
    {"ヘルスィーサラダ", "カメスパ", "ナンシーディナー"},
    {"ヘルスィーサラダ", "カラリーナパスタ", "ナンシースペシャル"},
    {"カメまん", "ドライフラワー", "うちゅうしょく"},
    {"フレッシュジュース", "レッド・カラリン", "すみぢる"},
    {"たんこぶ", "ドライフラワー", "うちゅうしょく"},
    {"たんこぶ", "おうごんはっぱ", "ナンシーデラックス"},
    {"きんかい", "イレカエール", "キノコ"},
    {"きんかい×３", "イレカエール", "きんかい"},
    {"ココナッツボム", "ドライフラワー", "ヤシの実"},
    {"ココナッツボム", "バクハツタマゴ", "ナンシーダイナマイ"},
    {"カチカチりょうり", "ドライフラワー", "カチカチコウラ"},
};
#endif
#endif

/** The 20 dishes the Mystery item can turn into when cooked. */
s32 naniga_okorukana_list[] = {
    132, 153, 235, 138, 151, 141, 135, 179,
    223, 192, 222, 211, 207, 183, 193, 129,
    209, 176, 232, 197,
};

/** Dishes that get the special radiating light when Zess T. cooks them, ending with -1. */
s32 special_cook_list[] = {
    194, 195, 196, 203, 210, 213, 214, 215,
    216, 217, 218, 219, 220, 221, 224, -1,
};

/**
 * Creates the seven Star Stone effects of the Chapter 8 "everyone's voices" scene in a ring of radius 140 around
 * (args[0], args[1], args[2]), named "starstone0" to "starstone6", hidden at first,
 * and hooks each one into the "mahojin" magic circle effect's draw list.
 */
static USER_FUNC(starstone_entry) {
    char name[16];
    EvtWord* args = event->args;
    f32 x;
    f32 s;
    f32 z;
    f32 angle;
    f32 y;
    f32 c;
    EffectEntry* eff;
    s32 i;

    x = evtGetFloat(event, args[0]);
    y = evtGetFloat(event, args[1]);
    z = evtGetFloat(event, args[2]);
    for (i = 0; i < 7; i++) {
        angle = 6.2831855f * i / 7.0f;
        s = sin(angle);
        c = cos(angle);
        sprintf(name, "starstone%d", i);
        eff = effStarStoneEntry(i, 140.0f * s + x, y, z - 140.0f * c, 1.0f);
        effSetName(eff, name);
        ((EffStarStoneWork*)eff->userdata)->flags &= ~4;
        ((EffStarStoneWork*)eff->userdata)->flags |= STARSTONE_FLAG_NO_DRAW;
        ((EffMahojinWork*)effNameToPtr("mahojin")->userdata)[i + 2].arg = eff;
        ((EffMahojinWork*)effNameToPtr("mahojin")->userdata)[i + 2].func = effStarStoneDraw;
    }
    return EVT_RETURN_DONE;
}

/** Moves the ring of seven Star Stone effects so that its center is at (args[0], args[1], args[2]). */
static USER_FUNC(starstone_set_pos) {
    char name[16];
    EvtWord* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    f32 s;
    f32 angle;
    f32 c;
    EffectEntry* eff;
    s32 i;

    for (i = 0; i < 7; i++) {
        angle = 6.2831855f * i / 7.0f;
        s = sin(angle);
        c = cos(angle);
        sprintf(name, "starstone%d", i);
        eff = effNameToPtr(name);
        ((EffStarStoneWork*)eff->userdata)->position.x = 140.0f * s + x;
        ((EffStarStoneWork*)eff->userdata)->position.y = y;
        ((EffStarStoneWork*)eff->userdata)->position.z = z - 140.0f * c;
    }
    return EVT_RETURN_DONE;
}

/** Sets the Y rotation (args[0], degrees) of all seven Star Stone effects. */
static USER_FUNC(starstone_set_ry) {
    char name[16];
    f32 ry = evtGetFloat(event, event->args[0]);
    s32 i;

    for (i = 0; i < 7; i++) {
        sprintf(name, "starstone%d", i);
        ((EffStarStoneWork*)effNameToPtr(name)->userdata)->rotY = ry;
    }
    return EVT_RETURN_DONE;
}

/** Blocks until the "mahojin" magic circle effect's animation has played through once. */
static USER_FUNC(wait_mahojin) {
    s32 anim = ((s32*)effNameToPtr("mahojin")->userdata)[6];

    if (anim != -1 && 0.0f != animPoseGetLoopTimes(anim)) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

/** Allocates the item list used by Trouble Center job 9; args[0] is the number of Courage Shells Mario carries. */
static USER_FUNC(iri_09_item_tbl_alloc) {
#if VERSION >= VERSION_US
    s32 n = evtGetValue(event, event->args[0]);
    iri_09_item_tbl = _mapAlloc((n + 1) * sizeof(s32));
#else
    iri_09_item_tbl = _mapAlloc((evtGetValue(event, event->args[0]) + 1) * sizeof(s32));
#endif
    return EVT_RETURN_DONE;
}

/**
 * Fills the job 9 item list with args[0] copies of item 143 (Courage Shell) ended by -1
 * and returns its pointer in args[1], so the selection window offers that many shells.
 */
static USER_FUNC(iri_09_item_tbl_make) {
    EvtWord* args = event->args;
    s32 n = evtGetValue(event, args[0]);
    s32 i;

    for (i = 0; i < n; i++) {
        iri_09_item_tbl[i] = 143;
    }
    iri_09_item_tbl[i] = -1;
    evtSetValue(event, args[1], (EvtWord)iri_09_item_tbl);
    return EVT_RETURN_DONE;
}

/** Frees the item list allocated by iri_09_item_tbl_alloc. */
static USER_FUNC(iri_09_item_tbl_free) {
    _mapFree(iri_09_item_tbl);
    iri_09_item_tbl = NULL;
    return EVT_RETURN_DONE;
}

/**
 * Stores the event pointer args[1] as the shop manager's talk hook (second word) in the shopper data at args[0];
 * Trouble Center job 9 uses it to take over his conversation.
 */
static USER_FUNC(set_fook_evt) {
    EvtWord* args = event->args;
    s32* wp = (s32*)evtGetValue(event, args[0]);

    wp[1] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

/**
 * Result of cooking the Mystery item: half the time one of the 20 results in naniga_okorukana_list,
 * otherwise a Mistake (item 182).
 */
static s32 naniga_okorukana_cook(void) {
    s32 r = rand() % 100;

    if (r < 50) {
        return naniga_okorukana_list[(s32)((u32)(r * 20) / 50.0f)];
    }
    return 182;
}

/**
 * Looks up an item by its internal id string in itemDataTable and returns its index, or 0 if none matches.
 * Used to turn the recipe table's names into items.
 */
static s32 itemNameToID(const char* name) {
    s32 i;

    for (i = 0; i < 339; i++) {
        if (strcmp(name, itemDataTable[i].id) == 0) {
            break;
        }
    }
    if (i >= 339) {
        return 0;
    }
    return i;
}

#if VERSION <= VERSION_DEMO_US
/**
 * The demo reads the recipes from cooking.xml on the disc:
 * <cooking_x1> blocks for one ingredient, <cooking_x2> blocks for two.
 * Each call loads the file (blocking until it is in), scans for the matching block and frees it.
 */
static USER_FUNC(cook_chk) {
    EvtWord* args = event->args;
    s32 item = evtGetValue(event, args[0]);
    ItemData* data = &itemDataTable[item];
    FileEntry* file;
    char ingredient[128];
    char result[128];
    char result2[128];

    if (item == 163) {
        item = naniga_okorukana_cook();
        evtSetValue(event, args[1], item);
        evtSetValue(event, args[2], item);
        return EVT_RETURN_DONE;
    }
    file = fileAsyncf(0, NULL, "%s/cooking.xml", getMarioStDvdRoot());
    if (file == NULL) {
        return EVT_RETURN_BLOCK;
    }
    if (fileAsyncMissing(file)) {
        evtSetValue(event, args[1], 0);
        evtSetValue(event, args[2], 0);
        return EVT_RETURN_DONE;
    }
    strcpy(ingredient, "");
    strcpy(result, "");
    strcpy(result2, "");
    file = fileAllocf(0, "%s/cooking.xml", getMarioStDvdRoot());
    parseInit(file->data[0], (u32)file->data[1]);
    while (parsePush("<cooking_x1>")) {
        parseTagGet1("<item>", 0, ingredient);
        parseTagGet1("<cook_lv1>", 0, result);
        parseTagGet1("<cook_lv2>", 0, result2);
        parsePopNext();
        if (strcmp(ingredient, data->id) == 0) {
            break;
        }
        strcpy(ingredient, "");
        strcpy(result, "");
        strcpy(result2, "");
    }
    parsePop();
    fileFree(file);
    // FAKE: volatile casts, see the retail cook_chk.
    evtSetValue(event, (volatile u32)args[1], itemNameToID(result));
    evtSetValue(event, (volatile u32)args[2], itemNameToID(result2));
    return EVT_RETURN_DONE;
}

/**
 * Zess T.'s two-ingredient recipe lookup: given items args[0] and args[1] (in either order),
 * returns the dish in args[2] or 0 if the pair has no recipe.
 * Anything with the Mystery item gives a random result.
 * The demos read cooking.xml from the disc, later releases search R_cookbook_recipe_table.
 */
static USER_FUNC(cook_chk2) {
    EvtWord* args = event->args;
    s32 item1 = evtGetValue(event, args[0]);
    s32 item2 = evtGetValue(event, args[1]);
    ItemData* data1 = &itemDataTable[item1];
    ItemData* data2 = &itemDataTable[item2];
    FileEntry* file;
    char a[128];
    char b[128];
    char out[128];

    if (item1 == 163 || item2 == 163) {
        item2 = naniga_okorukana_cook();
        // FAKE: volatile cast, see the retail cook_chk.
        evtSetValue(event, (volatile u32)args[2], item2);
        return EVT_RETURN_DONE;
    }
    file = fileAsyncf(0, NULL, "%s/cooking.xml", getMarioStDvdRoot());
    if (file == NULL) {
        return EVT_RETURN_BLOCK;
    }
    if (fileAsyncMissing(file)) {
        evtSetValue(event, args[2], 0);
        return EVT_RETURN_DONE;
    }
    strcpy(a, "");
    strcpy(b, "");
    strcpy(out, "");
    file = fileAllocf(0, "%s/cooking.xml", getMarioStDvdRoot());
    parseInit(file->data[0], (u32)file->data[1]);
    while (parsePush("<cooking_x2>")) {
        parseTagGet1("<item1>", 0, a);
        parseTagGet1("<item2>", 0, b);
        parseTagGet1("<cook>", 0, out);
        parsePopNext();
        if ((strcmp(a, data1->id) == 0 && strcmp(b, data2->id) == 0) ||
            (strcmp(a, data2->id) == 0 && strcmp(b, data1->id) == 0)) {
            break;
        }
        strcpy(a, "");
        strcpy(b, "");
        strcpy(out, "");
    }
    parsePop();
    fileFree(file);
    // FAKE: volatile cast, see the retail cook_chk.
    evtSetValue(event, (volatile u32)args[2], itemNameToID(out));
    return EVT_RETURN_DONE;
}
#else
/**
 * Zess T.'s one-ingredient recipe lookup: given the item args[0],
 * returns in args[1] and args[2] the dish made from it by itself (the result before and after the cookbook is
 * solved; 0 if it cannot be cooked). The Mystery item gives a random result.
 * The demos read cooking.xml from the disc, later releases use R_simple_recipe_table.
 */
static USER_FUNC(cook_chk) {
    EvtWord* args = event->args;
    s32 item = evtGetValue(event, args[0]);
    ItemData* data = &itemDataTable[item];
    u32 i;

    if (item == 163) {
        item = naniga_okorukana_cook();
        evtSetValue(event, args[1], item);
        evtSetValue(event, args[2], item);
        return EVT_RETURN_DONE;
    }
    for (i = 0; i < 26; i++) {
        if (strcmp(data->id, R_simple_recipe_table[i].ingredient) == 0) {
            // FAKE: the (volatile u32) casts order the args[n] loads after the inlined itemNameToID as in the target
            // (tried: a result local, a u32 cast of the result, event->args[n]).
            evtSetValue(event, (volatile u32)args[1], itemNameToID(R_simple_recipe_table[i].result));
            evtSetValue(event, (volatile u32)args[2], itemNameToID(R_simple_recipe_table[i].result2));
            return EVT_RETURN_DONE;
        }
    }
    evtSetValue(event, args[1], 0);
    evtSetValue(event, args[2], 0);
    return EVT_RETURN_DONE;
}

/**
 * Zess T.'s two-ingredient recipe lookup: given items args[0] and args[1] (in either order),
 * returns the dish in args[2] or 0 if the pair has no recipe.
 * Anything with the Mystery item gives a random result.
 * The demos read cooking.xml from the disc, later releases search R_cookbook_recipe_table.
 */
static USER_FUNC(cook_chk2) {
    EvtWord* args = event->args;
    s32 item1 = evtGetValue(event, args[0]);
    s32 item2 = evtGetValue(event, args[1]);
    ItemData* data1 = &itemDataTable[item1];
    ItemData* data2 = &itemDataTable[item2];
    u32 i;

    if (item1 == 163 || item2 == 163) {
        item2 = naniga_okorukana_cook();
        // FAKE: volatile cast, see cook_chk.
        evtSetValue(event, (volatile u32)args[2], item2);
        return EVT_RETURN_DONE;
    }
#if VERSION >= VERSION_US
    for (i = 0; i < 292; i++) {
#else
    for (i = 0; i < 289; i++) {
#endif
        if ((strcmp(data1->id, R_cookbook_recipe_table[i].a) == 0 && strcmp(data2->id, R_cookbook_recipe_table[i].b) == 0) ||
            (strcmp(data2->id, R_cookbook_recipe_table[i].a) == 0 && strcmp(data1->id, R_cookbook_recipe_table[i].b) == 0)) {
            // FAKE: volatile cast, see cook_chk.
            evtSetValue(event, (volatile u32)args[2], itemNameToID(R_cookbook_recipe_table[i].out));
            return EVT_RETURN_DONE;
        }
    }
    evtSetValue(event, args[2], 0);
    return EVT_RETURN_DONE;
}
#endif

/** Returns TRUE when item is not 0, i.e. when there is a dish to cook. */
static BOOL chkCookItem(s32 item) {
    return item != 0;
}

/**
 * Builds item_tbl, the list of items Mario carries for the cooking selection (without the item he already
 * picked), ends it with -1 and returns the count in args[1].
 * args[0] is the pouch slot to leave out (the item id in the demos).
 */
static USER_FUNC(make_item_tbl) {
    EvtWord* args = event->args;
    s32 skip = evtGetValue(event, args[0]);
    s32 cnt = pouchGetHaveItemCnt();
    s32 n = 0;
    s32 i;
    s32 item;

    for (i = 0; i < cnt; i++) {
#if VERSION <= VERSION_DEMO_US
        // the demo's argument is an item id: the first matching item is left out
        item = pouchHaveItem(i);
        if (item != 0) {
            if (skip == item) {
                skip = 0;
            } else {
#else
        if (skip != i) {
            item = pouchHaveItem(i);
            if (item != 0) {
#endif
                item_tbl[n] = item;
                n++;
            }
        }
    }
    item_tbl[n] = -1;
    evtSetValue(event, args[1], n);
    return EVT_RETURN_DONE;
}

/**
 * Returns in args[1] the display name of item args[0] (a message string in the US and later,
 * the id string in earlier releases).
 */
static USER_FUNC(get_item_name) {
    EvtWord* args = event->args;
    s32 item = evtGetValue(event, args[0]);

#if VERSION >= VERSION_US
    ItemData* data = &itemDataTable[item];
    evtSetValue(event, args[1], (s32)msgSearch(data->name));
#else
    evtSetValue(event, args[1], (EvtWord)itemDataTable[item].id);
#endif
    return EVT_RETURN_DONE;
}

/**
 * Decides how a finished dish looks when it comes out of the pot:
 * 1 for failures and explosive dishes (smoke and explosion), 0 for the rest (fire).
 */
static s32 chk_cook_eff_type(s32 item) {
    if (item < 148) {
        return 1;
    }
    if (item < 161) {
        return 0;
    }
    if (item < 179) {
        switch (item) {
            case 161:
            case 162:
            case 163:
            case 164:
            case 177:
            case 178:
                return 1;
            default:
                return 0;
        }
    }
    if (item < 236) {
        switch (item) {
            case 196:
            case 202:
            case 203:
            case 209:
                return 1;
            default:
                return 0;
        }
    }
    return 0;
}

/**
 * Plays the cooking effect at Zess T.'s stove (-380, 25..60, -170) for item args[0]:
 * fire and a fire sound for normal dishes, an explosion and smoke for failures.
 */
static USER_FUNC(cook_effect) {
    switch (chk_cook_eff_type(evtGetValue(event, event->args[0]))) {
        case 0:
            psndSFXOn_3D("SFX_EVT_COOK_FIRE1", &(Vec){-380.0f, 25.0f, -170.0f});
            effFireEntry(4, 60, -380.0f, 25.0f, -170.0f, 1.5f);
            break;
        case 1:
        default:
            psndSFXOn_3D("SFX_EVT_COOK_EXPLOSION1", &(Vec){-380.0f, 60.0f, -170.0f});
            effKemuri12N64Entry(0, 60, -380.0f, 60.0f, -170.0f, 2.0f);
            break;
    }
    return EVT_RETURN_DONE;
}

/**
 * Zess T. cooking animation: she walks to the stove, stirs and chops with cooking sounds,
 * the pot reacts (cook_effect for the dishes in LW(14) and LW(15)),
 * a radiating light plays for special dishes (chk_special_cook on LW(13)),
 * and she walks back to the counter facing Mario.
 */
EVT_BEGIN(cooking_evt_sub)
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_EVT_COOKING1"))
    WAIT_MS(500)
    CALL(evt_npc_flag_onoff, 1, STRING("ナンシー"), NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_status_onoff, 1, STRING("ナンシー"), 2)
    CALL(evt_npc_move_position, STRING("ナンシー"), -485, -150, 0, 80, 0)
    CALL(evt_npc_flag_onoff, 0, STRING("ナンシー"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_flag_onoff, 1, STRING("ナンシー"), NPC_FLAG_INSTANT_TURN)
    CALL(evt_npc_set_ry, STRING("ナンシー"), 90)
    CALL(evt_npc_set_anim, STRING("ナンシー"), STRING("S_1R"))
    WAIT_FRAMES(1)
    CALL(evt_npc_flag_onoff, 0, STRING("ナンシー"), NPC_FLAG_INSTANT_TURN)
    BEGIN_INLINE_EVENT
        CALL(evt_msg_toge, 1, 0, 0, 0)
        CALL(evt_msg_print, 0, STRING("gor_01_cook_016"), 0, STRING("ナンシー"))
    END_INLINE_EVENT
    WAIT_MS(500)
    CALL(evt_npc_get_position, STRING("ナンシー"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_COOK_COOKING1"), LW(0), LW(1), LW(2), LW(3))
    CALL(evt_npc_set_anim, STRING("ナンシー"), STRING("C_1"))
    WAIT_MS(2500)
    CALL(evt_snd_sfxoff, LW(3))
    CALL(evt_npc_flag_onoff, 1, STRING("ナンシー"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_move_position, STRING("ナンシー"), -430, -150, 0, 80, 0)
    CALL(evt_npc_flag_onoff, 0, STRING("ナンシー"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_set_anim, STRING("ナンシー"), STRING("C_1"))
    CALL(evt_npc_get_position, STRING("ナンシー"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_COOK_COOKING2"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(1500)
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_COOK_COOKING2"), LW(0), LW(1), LW(2), 0)
    WAIT_MS(1500)
    CALL(evt_npc_flag_onoff, 1, STRING("ナンシー"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_move_position, STRING("ナンシー"), -380, -150, 0, 80, 0)
    CALL(evt_npc_flag_onoff, 0, STRING("ナンシー"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_set_anim, STRING("ナンシー"), STRING("S_1R"))
    WAIT_MS(200)
    CALL(evt_npc_get_position, STRING("ナンシー"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_COOK_COOKING3"), LW(0), LW(1), LW(2), LW(3))
    CALL(evt_npc_set_anim, STRING("ナンシー"), STRING("C_1"))
    WAIT_MS(2800)
    CALL(evt_snd_sfxoff, LW(3))
    WAIT_MS(200)
    CALL(cook_effect, LW(14))
    WAIT_MS(1300)
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(cook_effect, LW(15))
        WAIT_MS(1300)
    END_IF
    CALL(chk_special_cook, LW(13), LW(0))
    IF_INT_EQUAL(LW(0), 1)
        CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_COOK_LIGHT1"), -380, 40, -170, LW(0))
        CALL(evt_eff64, STRING("rad"), STRING("radiation_n64"), 3, -380, 40, -170, FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1300)
        CALL(evt_eff_delete, STRING("rad"))
        CALL(evt_snd_sfxoff, LW(0))
        WAIT_MS(500)
    END_IF
    CALL(evt_npc_flag_onoff, 1, STRING("ナンシー"), NPC_FLAG_MOVE_ANIM)
    CALL(evt_npc_move_position, STRING("ナンシー"), -405, -100, 0, 80, 0)
    CALL(evt_set_dir_to_target, STRING("ナンシー"), STRING("mario"))
    CALL(evt_npc_status_onoff, 0, STRING("ナンシー"), 2)
    CALL(evt_npc_flag_onoff, 0, STRING("ナンシー"), NPC_FLAG_INTANGIBLE)
    CALL(evt_npc_flag_onoff, 1, STRING("ナンシー"), NPC_FLAG_TALK_ANIM)
    WAIT_MS(300)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    WAIT_MS(500)
    RETURN
EVT_END()

/** Items offered in the item menu for Trouble Center job 18: only the Cookbook. */
s32 iri_18_item_tbl[] = {
    ITEM_COOKBOOK, -1,
};

/**
 * Zess T.'s talk after the contact lens: cooking service.
 * Handles the Trouble Center job 18 cookbook request first when it is active,
 * then the introduction on the first visit, and then asks which one or two items Mario wants to cook,
 * shows what she makes, removes the ingredients from the pouch, runs cooking_evt_sub and gives Mario the dish,
 * which also unlocks the recipe log.
 */
EVT_BEGIN(cooking_evt)
    // Controls are locked while Mario and his partners walk up to Zess T.'s stove.
    CALL(evt_mario_key_onoff, 0)
#if VERSION >= VERSION_JP
    SET_VALUE(LW(11), -1)
    SET_VALUE(LW(12), -1)
#endif
    SET_VALUE(LW(14), 0)
    SET_VALUE(LW(15), 0)
    CALL(evt_npc_flag_onoff, 1, STRING("ナンシー"), NPC_FLAG_INTANGIBLE)
    // The partners and Mario line up in front of her and face her.
    SET_VALUE(GF(0), 1)
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 1, -337, -80, 60)
        CALL(evt_party_set_dir_npc, 1, STRING("ナンシー"))
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_move_pos2, 0, -347, -100, 60)
        CALL(evt_party_set_dir_npc, 0, STRING("ナンシー"))
        SET_VALUE(GF(0), 0)
    END_INLINE_EVENT
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_sub_get_dist, LW(0), LW(2), -377, -100, LW(3))
    IF_INT_LESS(LW(3), 10)
        CALL(evt_mario_dispflag_onoff, 1, 4)
    END_IF
    CALL(evt_mario_mov_pos2, -377, -100, 60)
    CALL(evt_mario_dispflag_onoff, 0, 4)
    CALL(evt_mario_set_dir_npc, STRING("ナンシー"))
    WAIT_MS(500)
    WAIT_WHILE(GF(0))
    CALL(evt_set_dir_to_target, STRING("ナンシー"), STRING("mario"))
    WAIT_FRAMES(1)
    CALL(evt_npc_wait_pera, STRING("ナンシー"))
    CALL(evt_npc_flag_onoff, 0, STRING("ナンシー"), NPC_FLAG_INTANGIBLE)
    // Trouble Center job 18: Zess T. has asked Mario to find a Cookbook.
    IF_INT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 18)
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_WORK_BASE), 0)
            // First time: she explains the request and the book she wants.
            CALL(evt_msg_print, 0, STRING("irai_18_001"), 0, STRING("ナンシー"))
            SET_VALUE(GSWF(GSWF_TROUBLE_WORK_BASE), 1)
            CALL(evt_msg_print_add, 0, STRING("irai_18_008_1"))
        ELSE
            // Later: she asks whether he found the book, and Mario can show it in the item menu.
            CALL(evt_msg_print, 0, STRING("irai_18_002"), 0, STRING("ナンシー"))
            SET_VALUE(LF(0), 0)
            CALL(evt_pouch_check_item, ITEM_COOKBOOK, LW(0))
            IF_INT_GREATER_OR_EQUAL(LW(0), 1)
                CALL(evt_msg_continue)
#if VERSION <= VERSION_DEMO_US
                CALL(evt_win_item_select, PTR(iri_18_item_tbl), LW(0))
#else
                CALL(evt_win_item_select, 0, PTR(iri_18_item_tbl), LW(0), 0)
#endif
            ELSE
                SET_VALUE(LW(0), -1)
                SET_VALUE(LF(0), 1)
            END_IF
            IF_INT_NOT_EQUAL(LW(0), -1)
                // Mario hands over the Cookbook; she is thrilled and studies it.
                CALL(evt_pouch_remove_item, ITEM_COOKBOOK, LW(0))
                CALL(evt_msg_print, 0, STRING("irai_18_003"), 0, STRING("ナンシー"))
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_npc_get_position, STRING("ナンシー"), LW(3), LW(4), LW(5))
                IF_INT_LESS(LW(0), LW(3))
                    ADD(LW(0), 20)
                ELSE
                    SUBTRACT(LW(0), 20)
                END_IF
                ADD(LW(1), 20)
                ADD(LW(2), 5)
                CALL(evt_item_entry, STRING("cb"), ITEM_COOKBOOK, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
                CALL(evt_mario_set_pose, STRING("M_C_3"))
                WAIT_MS(800)
                CALL(evt_item_delete, STRING("cb"))
                CALL(evt_mario_set_pose, STRING("M_S_1"))
                WAIT_MS(500)
                CALL(evt_msg_print, 0, STRING("irai_18_004"), 0, STRING("ナンシー"))
                CALL(evt_mario_set_pose, STRING("M_N_1"))
                SET_VALUE(LW(13), 183)
                SET_VALUE(LW(14), 148)
                SET_VALUE(LW(15), 154)
                // She tries out the new recipe in the cooking cutscene and announces the Honey Shroom.
                CALL_CHILD(cooking_evt_sub)
                CALL(evt_msg_print, 0, STRING("irai_18_005"), 0, STRING("ナンシー"))
                SET_VALUE(LF(0), 0)
                CALL(evt_pouch_get_haveitemcnt, LW(0))
                CALL(evt_pouch_check_item, ITEM_STRANGE_SACK, LW(1))
                IF_INT_EQUAL(LW(1), 0)
                    IF_INT_GREATER_OR_EQUAL(LW(0), 10)
                        SET_VALUE(LF(0), 1)
                    END_IF
                ELSE
                    IF_INT_GREATER_OR_EQUAL(LW(0), 20)
                        SET_VALUE(LF(0), 1)
                    END_IF
                END_IF
                IF_INT_EQUAL(LF(0), 0)
                    CALL(evt_msg_continue)
                    // Her reward, a Honey Shroom, goes to Mario if he has room in his pouch.
                    CALL(evt_item_entry, STRING("hk"), ITEM_HONEY_SHROOM, 0, -1000, 0, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
                    CALL(evt_item_get_item, STRING("hk"))
                    CALL(evt_item_get_item_end_wait, STRING("hk"))
                    SET_VALUE(GSWF(GSWF_GOR01_TROUBLE18_ITEM_LEFT), 1)
                ELSE
                    // Pouch full: she leaves the Honey Shroom on the ground for him to pick up.
                    CALL(evt_msg_print_add, 0, STRING("irai_18_006_1"))
                    CALL(evt_npc_set_ry, STRING("ナンシー"), 270)
                    WAIT_FRAMES(1)
                    CALL(evt_npc_wait_pera, STRING("ナンシー"))
                    WAIT_MS(300)
                    CALL(evt_item_entry, STRING("iri_18"), ITEM_HONEY_SHROOM, -440, 30, -80, ITEM_ENTRY_FIXED, GSWF(GSWF_GOR01_TROUBLE18_ITEM_LEFT), 0)
                    WAIT_MS(300)
                    CALL(evt_npc_set_ry, STRING("ナンシー"), 90)
                    WAIT_FRAMES(1)
                    CALL(evt_npc_wait_pera, STRING("ナンシー"))
                END_IF
                // Request complete: she can now cook with two ingredients, and the Trouble Center marks it
                // done.
                CALL(evt_msg_print, 0, STRING("irai_18_007"), 0, STRING("ナンシー"))
                SET_VALUE(GSW(GSW_TROUBLE_ACTIVE), 0)
                SET_VALUE(GSWF(GSWF_TROUBLE_18_SOLVED), 1)
                CALL(evt_msg_print, 0, STRING("sys_request_finish"), 0, 0)
                CALL(evt_mario_key_onoff, 1)
                RETURN
            ELSE
                // Mario came without the book: she tells him where to look and the visit ends.
                IF_INT_EQUAL(LF(0), 0)
                    CALL(evt_msg_print, 0, STRING("irai_18_008"), 0, STRING("ナンシー"))
                ELSE
                    CALL(evt_msg_print_add, 0, STRING("irai_18_008"))
                END_IF
                CALL(evt_msg_print_add, 0, STRING("irai_18_008_1"))
            END_IF
        END_IF
    END_IF
    // First visit after the lens: Zess T. introduces herself and her cooking service.
    IF_INT_EQUAL(GSWF(GSWF_GOR01_ZESS_INTRO_DONE), 0)
        IF_INT_NOT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 18)
            IF_INT_EQUAL(GSWF(GSWF_TROUBLE_18_SOLVED), 0)
                CALL(evt_msg_print, 0, STRING("gor_01_cook_000"), 0, STRING("ナンシー"))
            END_IF
        END_IF
        CALL(evt_msg_print_add, 0, STRING("gor_01_cook_001"))
        SET_VALUE(GSWF(GSWF_GOR01_ZESS_INTRO_DONE), 1)
    ELSE
        // Later visits: she asks if Mario wants her to cook, with a hint about the Cookbook once the story has
        // reached Chapter 4.
        IF_INT_EQUAL(LSWF(1), 0)
            SET_VALUE(LF(0), 0)
            IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT)
                IF_INT_NOT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 18)
                    IF_INT_EQUAL(GSWF(GSWF_TROUBLE_18_SOLVED), 0)
                        SET_VALUE(LF(0), 1)
                    END_IF
                END_IF
            END_IF
            IF_INT_EQUAL(LF(0), 0)
                IF_INT_NOT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 18)
                    CALL(evt_msg_print, 0, STRING("gor_01_cook_002"), 0, STRING("ナンシー"))
                ELSE
                    CALL(evt_msg_print_add, 0, STRING("gor_01_cook_002"))
                END_IF
            ELSE
                CALL(evt_msg_print, 0, STRING("gor_01_cook_003"), 0, STRING("ナンシー"))
            END_IF
        ELSE
            IF_INT_NOT_EQUAL(GSW(GSW_TROUBLE_ACTIVE), 18)
                CALL(evt_msg_print, 0, STRING("gor_01_cook_004"), 0, STRING("ナンシー"))
            ELSE
                CALL(evt_msg_print_add, 0, STRING("gor_01_cook_004"))
            END_IF
        END_IF
    END_IF
    SET_VALUE(LSWF(1), 1)
    // Mario answers whether he wants her to cook something.
    CALL(evt_msg_select, 0, STRING("gor_01_select"))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(0)
    END_IF
#if VERSION <= VERSION_DEMO_US
    CALL(make_item_tbl, LW(14), LW(0))
#else
    CALL(make_item_tbl, LW(11), LW(0))
#endif
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("gor_01_cook_005"))
        GOTO(5)
    END_IF
    // She asks for an ingredient; Mario picks it from his pouch (backing out asks again).
    CALL(evt_msg_print_add, 0, STRING("gor_01_cook_007"))
    LABEL(1)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_win_item_select, PTR(item_tbl), LW(0))
#else
    CALL(evt_win_item_select, 1, PTR(item_tbl), LW(0), LW(1))
#endif
    IF_INT_EQUAL(LW(0), -1)
        CALL(evt_msg_print, 0, STRING("gor_01_cook_008"), 0, STRING("ナンシー"))
        CALL(evt_msg_select, 0, STRING("gor_01_select"))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            GOTO(0)
            CASE_EQUAL(1)
            CALL(evt_msg_continue)
            GOTO(1)
        END_SWITCH
    END_IF
    SET_VALUE(LW(14), LW(0))
#if VERSION >= VERSION_JP
    SET_VALUE(LW(11), LW(1))
#endif
    SET_VALUE(LF(0), 0)
    // With the Cookbook recipes unlocked, Mario may add a second ingredient.
    IF_INT_EQUAL(GSWF(GSWF_TROUBLE_18_SOLVED), 1)
#if VERSION <= VERSION_DEMO_US
        CALL(make_item_tbl, LW(14), LW(0))
#else
        CALL(make_item_tbl, LW(11), LW(0))
#endif
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(evt_msg_print, 0, STRING("gor_01_cook_009"), 0, STRING("ナンシー"))
            CALL(evt_msg_select, 0, STRING("gor_01_select"))
            IF_INT_EQUAL(LW(0), 0)
                CALL(evt_msg_continue)
                LABEL(2)
#if VERSION <= VERSION_DEMO_US
                CALL(evt_win_item_select, PTR(item_tbl), LW(0))
#else
                CALL(evt_win_item_select, 1, PTR(item_tbl), LW(0), LW(1))
#endif
                IF_INT_EQUAL(LW(0), -1)
                    CALL(evt_msg_print, 0, STRING("gor_01_cook_010"), 0, STRING("ナンシー"))
                    CALL(evt_msg_select, 0, STRING("gor_01_cook_select"))
                    SWITCH(LW(0))
                        CASE_EQUAL(0)
                        SET_VALUE(LF(0), 1)
                        GOTO(3)
                        CASE_EQUAL(1)
#if VERSION >= VERSION_JP
                        CALL(evt_msg_continue)
#endif
                        GOTO(2)
                        CASE_EQUAL(2)
                        GOTO(0)
                    END_SWITCH
                END_IF
                IF_INT_EQUAL(LW(14), LW(0))
                    CALL(evt_msg_print, 0, STRING("gor_01_cook_011"), 0, STRING("ナンシー"))
                    GOTO(2)
                END_IF
                SET_VALUE(LW(15), LW(0))
#if VERSION >= VERSION_JP
                SET_VALUE(LW(12), LW(1))
#endif
            ELSE
                SET_VALUE(LF(0), 1)
            END_IF
        END_IF
    END_IF
    // She repeats what she will cook, and Mario confirms or cancels.
    LABEL(3)
    IF_INT_EQUAL(LW(15), 0)
        CALL(get_item_name, LW(14), LW(0))
        IF_INT_EQUAL(LF(0), 0)
#if VERSION == VERSION_EU
            CALL(evt_msg_fmt_str, 0, LW(2), STRING("gor_01_cook_012"), LW(0))
            CALL(evt_msg_print, 1, LW(2), 0, STRING("ナンシー"))
#else
            CALL(evt_msg_print_insert, 0, STRING("gor_01_cook_012"), 0, STRING("ナンシー"), LW(0))
#endif
        ELSE
#if VERSION == VERSION_EU
            CALL(evt_msg_fmt_str, 0, LW(2), STRING("gor_01_cook_012"), LW(0))
            CALL(evt_msg_print_add, 1, LW(2))
#else
            CALL(evt_msg_print_add_insert, 0, STRING("gor_01_cook_012"), LW(0))
#endif
        END_IF
    ELSE
        CALL(get_item_name, LW(14), LW(0))
        CALL(get_item_name, LW(15), LW(1))
#if VERSION == VERSION_EU
        CALL(evt_msg_fmt_str, 0, LW(2), STRING("gor_01_cook_013"), LW(0))
        CALL(evt_msg_fmt_str, 1, LW(2), LW(2), LW(1))
        CALL(evt_msg_print, 1, LW(2), 0, STRING("ナンシー"))
#else
        CALL(evt_msg_print_insert, 0, STRING("gor_01_cook_013"), 0, STRING("ナンシー"), LW(0), LW(1))
#endif
    END_IF
    CALL(evt_msg_select, 0, STRING("gor_01_select"))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(4)
    END_IF
    // The ingredients leave the pouch and the dish is worked out from the recipe.
    IF_INT_EQUAL(LW(15), 0)
        CALL(cook_chk, LW(14), LW(0), LW(1))
#if VERSION <= VERSION_DEMO_US
        CALL(evt_pouch_remove_item, LW(14), LW(3))
#else
        CALL(N_evt_pouch_remove_item_index, LW(14), LW(11), LW(3))
#endif
        IF_INT_EQUAL(GSWF(GSWF_TROUBLE_18_SOLVED), 1)
            SET_VALUE(LW(2), LW(1))
        ELSE
            SET_VALUE(LW(2), LW(0))
        END_IF
    ELSE
        CALL(cook_chk2, LW(14), LW(15), LW(2))
#if VERSION <= VERSION_DEMO_US
        CALL(evt_pouch_remove_item, LW(14), LW(3))
        CALL(evt_pouch_remove_item, LW(15), LW(3))
#else
        CALL(N_evt_pouch_remove_item_index, LW(14), LW(11), LW(3))
        CALL(N_evt_pouch_remove_item_index, LW(15), LW(12), LW(3))
#endif
    END_IF
    IF_INT_EQUAL(LW(2), 0)
        SET_VALUE(LW(2), 182)
    END_IF
    CALL(evt_msg_print_add, 0, STRING("gor_01_cook_015"))
    // The cooking cutscene plays.
    SET_VALUE(LW(13), LW(2))
    CALL_CHILD(cooking_evt_sub)
    SET_VALUE(LW(2), LW(13))
    CALL(chk_cook_msg, LW(2), LW(3))
    // Her reaction depends on how the dish turned out.
    SWITCH(LW(3))
        CASE_EQUAL(0)
        CALL(evt_msg_print, 0, STRING("gor_01_cook_018"), 0, STRING("ナンシー"))
        CASE_EQUAL(1)
        CALL(evt_msg_print, 0, STRING("gor_01_cook_017"), 0, STRING("ナンシー"))
        CASE_EQUAL(2)
        CALL(evt_msg_print, 0, STRING("gor_01_cook_020"), 0, STRING("ナンシー"))
        CASE_EQUAL(3)
        CALL(evt_msg_print, 0, STRING("gor_01_cook_019"), 0, STRING("ナンシー"))
        CASE_EQUAL(4)
        CALL(evt_msg_print, 0, STRING("gor_01_cook_021"), 0, STRING("ナンシー"))
    END_SWITCH
    // She hands over the dish; the recipe log is unlocked and she invites Mario to come back.
    CALL(evt_msg_print_add, 0, STRING("gor_01_cook_022"))
    CALL(evt_item_entry, STRING("cook"), LW(2), 0, -1000, 0, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
    CALL(evt_item_get_item, STRING("cook"))
    SET_VALUE(GSWF(GSWF_RECIPE_LOG_UNLOCKED), 1)
    CALL(cooking_flag, LW(2))
    CALL(evt_msg_print, 0, STRING("gor_01_cook_023"), 0, STRING("ナンシー"))
    GOTO(5)
    // Mario declined to have anything cooked: she is let down.
    LABEL(0)
    CALL(evt_msg_print_add, 0, STRING("gor_01_cook_006"))
    GOTO(5)
    // Mario cancelled at the last moment: she tells him to come back whenever.
    LABEL(4)
    CALL(evt_msg_print_add, 0, STRING("gor_01_cook_014"))
    GOTO(5)
    // The visit ends and Mario's controls return.
    LABEL(5)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/**
 * Picks which reaction Zess T. has to a finished dish, returned in args[1]:
 * 0 and 1 for the best dishes, 2 for a failure (Mistake), 3 or 4 for the rest by cooking effect type.
 */
static USER_FUNC(chk_cook_msg) {
    EvtWord* args = event->args;
    s32 item = evtGetValue(event, args[0]);
    s32 msg;

    if (item == 195 || item == 196) {
        msg = 0;
    } else if ((item >= 193 && item <= 197) || item == 232 || item == 200) {
        msg = 1;
    } else if (item == 182) {
        msg = 2;
    } else {
        msg = chk_cook_eff_type(item) + 3;
    }
    evtSetValue(event, args[1], msg);
    return EVT_RETURN_DONE;
}

/** Marks dish args[0] as cooked in the recipe log (swSet with the item number minus 114). */
static USER_FUNC(cooking_flag) {
    swSet(evtGetValue(event, event->args[0]) - 114);
    return EVT_RETURN_DONE;
}

/**
 * Returns in args[1] whether item args[0] is in special_cook_list,
 * the dishes that get the special radiating light when cooked.
 */
static USER_FUNC(chk_special_cook) {
    EvtWord* args = event->args;
    s32 item = evtGetValue(event, args[0]);
    s32 found = FALSE;
    s32 i;
    s32 v;

    for (i = 0; (v = special_cook_list[i]) != -1; i++) {
        if (item == v) {
            found = TRUE;
            break;
        }
    }
    evtSetValue(event, args[1], found);
    return EVT_RETURN_DONE;
}
