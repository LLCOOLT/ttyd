// The init events of the tst maps, plus a test that draws a polygon with the stick and fills it through the GLU
// tessellator (glu/). The tst_nakayama map runs the test. The Japanese demo has no test (the tess code and the
// tst_nakayama events came after it), but the GLU units are still linked into its tst.rel.
#include "evt/evt_cmd.h"
#include "tst.h"
#include "evt_init.h"

#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "driver/offscreendrv.h"
#include "eff/eff_nokotarou.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include "libc_decls.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include "evt/evt_img.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_offscreen.h"
#include "evt/evt_paper.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_sub.h"
#include "manager/fontmgr.h"
#include "npc_event.h"
#include "evt/evt_snd.h"
#include "driver/mapdrv.h"
#include "version.h"

#if VERSION >= VERSION_JP
// One point of the drawn outline (and of the vertices the tessellator adds where edges cross).
typedef struct TessVertex {
    f64 x;                // 0x00
    f64 y;                // 0x08
    f64 z;                // 0x10, always 0
    u8 reserved_18[0x28]; // 0x18, never accessed
    s32 contour;          // 0x40, index of the contour the point belongs to
    GXColor color;        // 0x44, set on combined vertices
    s32 edge;             // 0x48, 3 for a combined vertex, 4 when it lies on an outline edge
    u8 reserved_4C[0xC];  // 0x4C, never accessed
} TessVertex;

#define TESS_MAX_VERTICES 512
#define TESS_MAX_INDICES 2048

typedef struct TessTestWork {
    s32 x;                                  // 0x00, cursor position, moved with the stick
    s32 y;                                  // 0x04
    s32 lastX;                              // 0x08, cursor position when the last point was added
    s32 lastY;                              // 0x0C
    smartEntry* capture;                    // 0x10, screen copy the filled polygon is textured with
    s32 vertexCount;                        // 0x14
    s32 contourCount;                       // 0x18
    TessVertex vertices[TESS_MAX_VERTICES]; // 0x20
    s32 indexCount;                         // 0xB020
    s32 indices[TESS_MAX_INDICES];          // 0xB024, triangle list from the tessellator
} TessTestWork;

USER_FUNC(tess_test_draw);
USER_FUNC(tess_test_run);
USER_FUNC(tess_test_disp_entry);
USER_FUNC(tess_test_end);

extern EvtWord tst_nakayama_tess_evt[];

void tess_test(void);
#endif

// MWCC emits file-scope variables in reverse order: item_name comes first in .bss.
#if VERSION >= VERSION_JP
TessTestWork* tess_test_work;
#endif
char item_name[32];

EVT_BEGIN(tst_00_init_evt)
    CALL(evt_mario_set_pos, -525, 0, -15)
    RETURN
EVT_END()

EVT_BEGIN(tst_01_font_evt)
    LOOP(0)
        WAIT_FRAMES(60)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_msg_print, 0, STRING("font_test"), 0, 0)
        CALL(evt_mario_key_onoff, 1)
        WAIT_FRAMES(60)
        CALL(evt_mario_key_onoff, 0)
        CALL(evt_msg_print, 0, STRING("font_test1"), 0, 0)
        CALL(evt_mario_key_onoff, 1)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(tst_01_init_evt)
    CALL(evt_mario_set_pos, -525, 0, -15)
    SPAWN_EVENT(tst_01_font_evt)
    RETURN
EVT_END()

EVT_BEGIN(tst_02_init_evt)
    CALL(evt_mario_set_pos, 0, 0, -100)
    RETURN
EVT_END()

EVT_BEGIN(tst_npc_talk_evt)
    CALL(evt_npc_set_anim, STRING("me"), STRING("PAN_D_1"))
    WAIT_MS(500)
    CALL(evt_npc_return_interrupt, STRING("me"))
    RETURN
EVT_END()

// Never ends, so it has no end command.
EvtWord tst_npc_env_evt[] = {
    CALL(evt_snd_envon, 0, STRING("ENV_STG1_HEI2"))
    CALL(evt_snd_envon, PSND_CH(1), STRING("ENV_STG1_HEI1"))
    LABEL(0)
    CALL(evt_npc_get_position, STRING("NPC_01"), LW(0), LW(1), LW(2))
    WAIT_MS(1000)
    GOTO(0)
};

EVT_BEGIN(tst_npc_init_evt)
    CALL(evt_npc_change_interrupt, STRING("NPC_01"), 1, PTR(testnpc_move_event))
    CALL(evt_npc_change_interrupt, STRING("NPC_01"), 8, PTR(tst_npc_talk_evt))
    CALL(evt_npc_reaction_flag_onoff, 1, STRING("NPC_01"), 2)
    CALL(evt_npc_flag_onoff, 1, STRING("NPC_01"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
    CALL(evt_npc_change_fbat_mode, 1)
    SPAWN_EVENT(tst_npc_env_evt)
    RETURN
EVT_END()

EVT_BEGIN(tst_moj_00_init_evt)
    CALL(tst_mobj_koopa_on)
    CALL(evt_mobj_lv_blk, STRING("l1"), -450, 0, 100, 0, LSWF(0), STRING("MOBJ_Lv1Block"))
    CALL(evt_mobj_lv_blk, STRING("l1b"), -450, 0, 0, 0, LSWF(1), STRING("MOBJ_Lv1BigBlock"))
    CALL(evt_mobj_lv_blk, STRING("l1bb"), -450, 0, -100, 0, LSWF(2), STRING("MOBJ_Lv1BigBigBlock"))
    CALL(evt_mobj_lv_blk, STRING("l2"), -300, 0, 100, 0, LSWF(3), STRING("MOBJ_Lv2Block"))
    CALL(evt_mobj_lv_blk, STRING("l2b"), -300, 0, 0, 0, LSWF(4), STRING("MOBJ_Lv2BigBlock"))
    CALL(evt_mobj_lv_blk, STRING("l2bb"), -300, 0, -100, 0, LSWF(5), STRING("MOBJ_Lv2BigBigBlock"))
    CALL(evt_mobj_lv_blk, STRING("l3"), -150, 0, 100, 0, LSWF(15), STRING("MOBJ_Lv3Block"))
    CALL(evt_mobj_lv_blk, STRING("l3b"), -150, 0, 0, 0, LSWF(16), STRING("MOBJ_Lv3BigBlock"))
    CALL(evt_mobj_lv_blk, STRING("l3bb"), -150, 0, -100, 0, LSWF(17), STRING("MOBJ_Lv3BigBigBlock"))
    CALL(evt_mobj_float_blk, STRING("gb"), 0, 0, 100, 0, 0, 0, LSWF(6))
    CALL(evt_mobj_float_blk, STRING("bgb"), 0, 0, 0, 0, 1, 0, LSWF(7))
    CALL(evt_mobj_float_blk, STRING("bbgb"), 0, 0, -100, 0, 2, 0, LSWF(8))
    CALL(evt_mobj_float_blk, STRING("pb"), 150, 0, 100, 1, 0, 0, LSWF(9))
    CALL(evt_mobj_float_blk, STRING("bpb"), 150, 0, 0, 1, 1, 0, LSWF(10))
    CALL(evt_mobj_float_blk, STRING("bbpb"), 150, 0, -100, 1, 2, 0, LSWF(11))
    CALL(evt_mobj_float_blk, STRING("ob"), 300, 0, 100, 2, 0, 0, LSWF(12))
    CALL(evt_mobj_float_blk, STRING("bob"), 300, 0, 0, 2, 1, 0, LSWF(13))
    CALL(evt_mobj_float_blk, STRING("bbob"), 300, 0, -100, 2, 2, 0, LSWF(14))
    CALL(evt_mobj_float_blk, STRING("bbrb"), 450, 0, -100, 3, 2, 0, LSWF(18))
    RETURN
EVT_END()

EVT_BEGIN(tst_moj_01_init_evt)
    CALL(tst_mobj_koopa_on)
    CALL(evt_mobj_rideswitch_orange, STRING("rso"), 100, 0, -200, 0, LSWF(0))
    CALL(evt_mobj_rideswitch_green, STRING("rsg"), 200, 0, -200, 0, LSWF(1))
    CALL(evt_mobj_rideswitch_lightblue, STRING("rsl"), 300, 0, -200, 0, 0, LSWF(2))
    CALL(evt_mobj_timerswitch, 0, STRING("tsb1"), 150, 0, -100, STRING("tsb2"), 250, 0, -100, 600, 0, LSWF(3))
    CALL(evt_mobj_timerswitch, 1, STRING("tsr1"), 350, 0, -100, STRING("tsr2"), 450, 0, -100, 600, 0, LSWF(4))
    CALL(evt_mobj_switch_blue, 0, STRING("sb"), 100, 0, 0, 0, LSWF(5))
    CALL(evt_mobj_switch_red, 0, STRING("sr"), 200, 0, 0, 0, LSWF(6))
    CALL(evt_mobj_switch_blue, 1, STRING("sk"), 300, 0, 0, 0, LSWF(10))
    CALL(evt_mobj_switch_red, 1, STRING("sw"), 400, 0, 0, 0, LSWF(11))
    CALL(evt_mobj_switch_float_blk, STRING("fgb"), 150, 0, 100, STRING(""), 0, 0, LSWF(7))
    CALL(evt_mobj_switch_float_blk, STRING("fpb"), 250, 0, 100, STRING(""), 1, 0, LSWF(8))
    CALL(evt_mobj_switch_float_blk, STRING("fob"), 350, 0, 100, STRING(""), 2, 0, LSWF(9))
    CALL(evt_mobj_switch_float_blk, STRING("frb"), 450, 0, 100, STRING(""), 3, 0, LSWF(16))
    CALL(evt_mobj_floatswitch_blue, 0, STRING("fsb"), 100, 64, 200, 0, LSWF(12))
    CALL(evt_mobj_floatswitch_red, 0, STRING("fsr"), 200, 64, 200, 0, LSWF(13))
    CALL(evt_mobj_tornadoswitch_blue, 0, STRING("trsb"), 300, 0, 200, 0, LSWF(14))
    CALL(evt_mobj_tornadoswitch_red, 0, STRING("trsr"), 400, 0, 200, 0, LSWF(15))
    RETURN
EVT_END()

EVT_BEGIN(tst_moj_02_init_evt)
    CALL(evt_mobj_recovery_blk, STRING("rb1"), 0, -300, 64, 0, 0, LSWF(0))
    CALL(evt_mobj_recovery_blk, STRING("rb2"), 10, -200, 64, 0, 0, LSWF(1))
    CALL(evt_mobj_save_blk, STRING("sb"), -100, 64, 0, 0, LSWF(2))
    CALL(evt_mobj_blk, STRING("b"), 0, 64, 0, 0, 0, LSWF(3))
    CALL(evt_mobj_blk, STRING("pb"), 100, 64, 0, 1, 0, LSWF(4))
    CALL(evt_mobj_badgeblk, STRING("hb"), 200, 64, 0, ITEM_MUSHROOM, 0, LSWF(5), 0)
    CALL(evt_mobj_badgeblk, STRING("bb"), 300, 64, 0, ITEM_ATTACK_FX_R, 0, LSWF(6), 1)
    CALL(evt_mobj_powerupblk, STRING("pub"), 400, 64, 0, 0, LSWF(7), 0)
    CALL(evt_mobj_brick, STRING("b_n"), 50, 64, 100, 0, 0, 0, LSWF(8))
    CALL(evt_mobj_brick, STRING("b_h"), 150, 64, 100, ITEM_MUSHROOM, 1, 0, LSWF(9))
    CALL(evt_mobj_brick, STRING("b_b"), 250, 64, 100, ITEM_ATTACK_FX_R, 2, 0, LSWF(10))
    CALL(evt_mobj_brick, STRING("b_10"), 350, 64, 100, 0, 3, 0, LSWF(11))
    CALL(evt_mobj_brick, STRING("hb_h"), 200, 64, 200, ITEM_MUSHROOM, 11, 0, LSWF(13))
    CALL(evt_mobj_brick, STRING("hb_b"), 300, 64, 200, ITEM_ATTACK_FX_R, 12, 0, LSWF(14))
    CALL(evt_mobj_brick, STRING("hb_10"), 400, 64, 200, 0, 13, 0, LSWF(15))
    RETURN
EVT_END()

EVT_BEGIN(tst_moj_03_init_evt)
    CALL(evt_mobj_jumpstand_red, 0, STRING("j1r"), 0, 0, -100, 0, LSWF(0))
    CALL(evt_mobj_jumpstand_blue, 0, STRING("j1b"), 200, 200, 0, -100, 0, LSWF(2))
    CALL(evt_mobj_lock, STRING("l"), ITEM_CASTLE_KEY_0x0C, 300, 0, -100, 0, 0, 0, LSWF(3))
    CALL(evt_mobj_itembox, STRING("tb"), 50, 0, 0, 0, 0, 0, LSWF(4))
    CALL(evt_mobj_itembox, STRING("btb"), 150, 0, 0, 1, 0, 0, LSWF(5))
    CALL(evt_mobj_signboard, STRING("sb"), 250, 0, 0, 0, LSWF(6))
    CALL(evt_mobj_arrow, STRING("ar"), 350, 0, 0, 0)
    CALL(evt_mobj_breaking_floor, STRING("bf"), 0, 0, 100, 0, 0, LSWF(7))
    CALL(evt_mobj_kururing_floor, STRING("kf"), 100, 0, 100, STRING("S_yuka01"), 121, LSWF(8))
    CALL(evt_mobj_trap_floor, STRING("tf"), 200, 0, 100, STRING("S_yuka01"), 121, LSWF(9))
    CALL(evt_mobj_breaking_rock, STRING("br"), -100, 0, 0, 0, LSWF(10))
    CALL(evt_mobj_itembox, STRING("tbr"), -50, 0, 0, 2, 0, 0, LSWF(11))
    CALL(evt_mobj_itembox, STRING("tbb"), -150, 0, 0, 3, 0, 0, LSWF(12))
    CALL(evt_mobj_itembox, STRING("tbg"), -250, 0, 0, 4, 0, 0, LSWF(13))
    RETURN
EVT_END()

EVT_BEGIN(tst_off_01_init_evt)
    CALL(evt_paper_entry, STRING("OFF_cloud_1"))
    CALL(evt_paper_entry, STRING("OFF_hei_07"))
    CALL(evt_img_entry, STRING("img"))
    CALL(evt_img_set_paper, STRING("img"), STRING("OFF_cloud_1"))
    CALL(evt_img_alloc_capture, STRING("img"), 0, 0, 0, 152, 120, 304, 240)
    CALL(evt_img_set_virtual_point, STRING("img"), 0, 0, -100)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1L"))
            CALL(evt_img_wait_animend, STRING("img"))
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_img_entry, STRING("img2"))
    CALL(evt_img_set_paper, STRING("img2"), STRING("OFF_hei_07"))
    CALL(evt_img_alloc_capture, STRING("img2"), 0, 0, 0, 152, 120, 304, 240)
    CALL(evt_img_set_virtual_point, STRING("img2"), 0, 0, 0)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_img_set_paper_anim, STRING("img2"), STRING("A_1"))
            CALL(evt_img_wait_animend, STRING("img2"))
        END_LOOP
    END_INLINE_EVENT
    CALL(evt_paper_entry, STRING("nakayama_test3"))
    CALL(evt_img_entry, STRING("img3"))
    CALL(evt_img_set_paper, STRING("img3"), STRING("nakayama_test3"))
    CALL(evt_img_alloc_capture, STRING("img3"), 0, 0, 0, 0, 360, 152, 120)
    CALL(evt_img_clear_virtual_point, STRING("img3"))
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_img_set_paper_anim, STRING("img3"), STRING("A_1"))
            CALL(evt_img_wait_animend, STRING("img3"))
        END_LOOP
    END_INLINE_EVENT
    RETURN
EVT_END()

EVT_BEGIN(btl_tst_00_init_evt)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("saku_00"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("saku_01"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("saku_02"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kusa_b_01"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kusa_b_02"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kusa_b_04"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kusa_b_05"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kusa_b_06"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kusa_b_07"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kusa_b_08"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("ki_1"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("ki_2"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("ki_6"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("yama_a_01"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("yama_a_02"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("yama_a_03"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("yama_a_04"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("yama_a_05"), MAPOBJ_FLAG_HIDE)
    RETURN
EVT_END()

EVT_BEGIN(tst_bt00_init_evt)
    RETURN
EVT_END()

// The Japanese store demo has no tst_nakayama_init_evt, though tst.c still registers it: its tst.rel holds 0 there
// with no relocation. Keep the event out of that version; tst.c explains how the build reproduces the reference.
#if VERSION >= VERSION_JP
EVT_BEGIN(tst_nakayama_init_evt)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_set_pos, 0, 0, 0)
    CALL(evt_party_set_pos, 0, 30, 0, 0)
    SPAWN_EVENT(tst_nakayama_tess_evt)
    RETURN
EVT_END()

// Shows a random paper, draws the outline with the stick, and cuts the paper to the tessellated polygon.
EVT_BEGIN(tst_nakayama_tess_evt)
    CALL(evt_seq_wait, 2)
    LOOP(0)
        CALL(evt_sub_random, 50, LW(0))
        SWITCH(LW(0))
            CASE_LESS(10)
            SET_VALUE(LW(10), STRING("OFF_gon_04_3"))
            SET_VALUE(LW(11), STRING("A_1"))
            CASE_LESS(20)
            SET_VALUE(LW(10), STRING("OFF_d_nabi"))
            SET_VALUE(LW(11), STRING("A_1"))
            CASE_LESS(30)
            SET_VALUE(LW(10), STRING("OFF_d_roll"))
            SET_VALUE(LW(11), STRING("A_2"))
            CASE_LESS(40)
            SET_VALUE(LW(10), STRING("OFF_d_pazu"))
            SET_VALUE(LW(11), STRING("A_1"))
            CASE_LESS(50)
            SET_VALUE(LW(10), STRING("OFF_d_ori"))
            SET_VALUE(LW(11), STRING("A_1"))
        END_SWITCH
        CALL(evt_paper_entry, LW(10))
        CALL(evt_offscreen_entry, STRING("ofs"))
        CALL(evt_img_entry, STRING("img"))
        CALL(evt_img_set_paper, STRING("img"), LW(10))
        CALL(evt_img_onoff, STRING("img"), 0)
        CALL(tess_test_draw)
        WAIT_FRAMES(1)
        CALL(tess_test_run)
        WAIT_FRAMES(1)
        CALL(tess_test_disp_entry)
        CALL(evt_img_alloc_capture, STRING("img"), 0, STRING("ofs"), 1, 0, 0, 0, 0)
        CALL(evt_img_alloc_capture, STRING("img"), 1, STRING("ofs"), 1, 0, 0, 0, 0)
        CALL(evt_img_alloc_capture, STRING("img"), 2, STRING("ofs"), 1, 0, 0, 0, 0)
        WAIT_FRAMES(1)
        CALL(evt_img_onoff, STRING("img"), 1)
        CALL(evt_img_set_shadow, STRING("img"), 2)
        CALL(evt_img_set_paper_anim, STRING("img"), LW(11))
        CALL(evt_img_clear_virtual_point, STRING("img"))
        CALL(evt_img_wait_animend, STRING("img"))
        CALL(evt_img_onoff, STRING("img"), 0)
        CALL(evt_img_set_shadow, STRING("img"), 0)
        CALL(evt_img_release, STRING("img"))
        CALL(evt_offscreen_delete, STRING("ofs"))
        CALL(evt_paper_delete, LW(10))
        CALL(tess_test_end)
    END_LOOP
    RETURN
EVT_END()
#endif

// The unit is built with -inline auto,deferred, which emits the functions in reverse order: the last one here comes
// first in the REL.

#if VERSION >= VERSION_JP
// Draws the outline: one rainbow line per segment, the buffer use, and the cursor.
void tess_test_line_disp(CameraId cameraId, void* param) {
    s32 i;

    GXLoadPosMtxImm(camGetPtr(cameraId)->view, 0);
    GXSetCurrentMtx(0);
    dbgDrawReset(-1);
    {
        // "Trail buffer %d / %d"
        GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
        dbgDrawPrintf(120, -200, &white, 1.0f, "@Py\x8B\x4F\x90\xD5\x83\x6F\x83\x62\x83\x74\x83\x40 %d / %d@Pw",
                      tess_test_work->vertexCount, TESS_MAX_VERTICES);
    }
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_OR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetLineWidth(16, GX_TO_ZERO);
    for (i = 0; i < tess_test_work->vertexCount - 1; i++) {
        GXColor hsv = {0x00, 0xFF, 0xFF, 0xFF};

        hsv.r = (gp->retraceCount + i * 2) % 255;
        GXSetChanMatColor(GX_COLOR0A0, HSV2RGB(hsv));
        GXBegin(GX_LINES, GX_VTXFMT0, 2);
        GXPosition3f32(tess_test_work->vertices[i].x, tess_test_work->vertices[i].y, 0.0f);
        GXPosition3f32(tess_test_work->vertices[i + 1].x, tess_test_work->vertices[i + 1].y, 0.0f);
    }
    dbgDrawReset(-1);
    {
        GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
        dbgDrawCursor(tess_test_work->x, tess_test_work->y, color, -2.0f);
    }
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    {
        GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
        dbgDrawCursor(tess_test_work->x, tess_test_work->y, color, -2.0f);
    }
    dbgDrawReset(-1);
}

// Copies the screen into the texture the filled polygon is drawn with.
void tess_test_capture(CameraId cameraId, void* param) {
    tess_test_work->capture = smartAlloc(GXGetTexBufferSize(608, 480, GX_TF_I8, GX_FALSE, 0), 1);
    GXSetTexCopySrc(0, 0, 608, 480);
    GXSetTexCopyDst(608, 480, GX_TF_I8, GX_FALSE);
    GXCopyTex(tess_test_work->capture->address, GX_FALSE);
    GXPixModeSync();
}

// Whether segment a-b crosses segment c-d.
BOOL tess_test_cross(TessVertex* a, TessVertex* b, TessVertex* c, TessVertex* d) {
    if (((a->x - b->x) * (c->y - a->y) + (a->y - b->y) * (a->x - c->x)) *
            ((a->x - b->x) * (d->y - a->y) + (a->y - b->y) * (a->x - d->x)) <
        0.0) {
        if (((c->x - d->x) * (a->y - c->y) + (c->y - d->y) * (c->x - a->x)) *
                ((c->x - d->x) * (b->y - c->y) + (c->y - d->y) * (c->x - b->x)) <
            0.0) {
            return TRUE;
        }
    }
    return FALSE;
}

// Moves the cursor with the stick and adds a point every 6 frames, until the newest segment crosses an older one.
USER_FUNC(tess_test_draw) {
    s32 j;
    s32 i;

    if (isFirstCall) {
        tess_test_work = _mapAlloc(sizeof(TessTestWork));
        tess_test_work->x = 0;
        tess_test_work->y = 0;
        tess_test_work->lastX = -1;
        tess_test_work->lastY = -1;
        tess_test_work->vertexCount = 0;
        tess_test_work->contourCount = 1;
    }
    tess_test_work->x += keyGetStickX(0) / 10.0f;
    tess_test_work->y += keyGetStickY(0) / 10.0f;
    if (tess_test_work->x < -264) {
        tess_test_work->x = -264;
    }
    if (tess_test_work->x > 264) {
        tess_test_work->x = 264;
    }
    if (tess_test_work->y > 200) {
        tess_test_work->y = 200;
    }
    if (tess_test_work->y < -200) {
        tess_test_work->y = -200;
    }
    if (gp->retraceCount % 6 == 0) {
        if (tess_test_work->lastX != tess_test_work->x || tess_test_work->lastY != tess_test_work->y) {
            tess_test_work->vertices[tess_test_work->vertexCount].x = tess_test_work->x;
            tess_test_work->vertices[tess_test_work->vertexCount].y = tess_test_work->y;
            tess_test_work->vertices[tess_test_work->vertexCount].z = 0.0;
            tess_test_work->lastX = tess_test_work->x;
            tess_test_work->lastY = tess_test_work->y;
            tess_test_work->vertexCount++;
            if (tess_test_work->vertexCount >= TESS_MAX_VERTICES) {
                tess_test_work->vertexCount = 0;
            }
        }
    }
    if (tess_test_work->vertexCount > 3) {
        for (i = 0; i < tess_test_work->vertexCount - 2; i++) {
            if (tess_test_cross(&tess_test_work->vertices[i], &tess_test_work->vertices[i + 1],
                                &tess_test_work->vertices[tess_test_work->vertexCount - 2],
                                &tess_test_work->vertices[tess_test_work->vertexCount - 1])) {
                for (j = 0; j < i; j++) {
                    tess_test_work->vertices[j] = tess_test_work->vertices[tess_test_work->vertexCount - 1];
                }
                dispEntry(CAMERA_2D, 0.0f, 0, tess_test_capture, NULL);
                return EVT_RETURN_DONE;
            }
        }
    }
    dispEntry(CAMERA_2D, 0.0f, 0, tess_test_line_disp, NULL);
    return EVT_RETURN_BLOCK;
}

// Draws the tessellated polygon with the screen copy and records its bounding box for the "ofs" offscreen.
void tess_test_disp(CameraId cameraId, void* param) {
    GXTexObj texObj;
    Mtx mtx;
    u16 left, top, right, bottom;
    s32 i;
    s32* index;

    sysWaitDrawSync();
    GXClearBoundingBox();
    GXInitTexObj(&texObj, tess_test_work->capture->address, 608, 480, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    C_MTXLightOrtho(mtx, -240.0f, 240.0f, -304.0f, 304.0f, 0.5f, 0.5f, 0.5f, 0.5f);
    PSMTXConcat(mtx, camGetPtr(CAMERA_2D)->view, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_1);
    GXLoadPosMtxImm(camGetPtr(CAMERA_2D)->view, GX_PNMTX0);
    index = tess_test_work->indices;
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXBegin(GX_TRIANGLES, GX_VTXFMT0, tess_test_work->indexCount);
    for (i = 0; i < tess_test_work->indexCount; i++) {
        TessVertex* v = &tess_test_work->vertices[*index++];
        GXPosition3f32(v->x, v->y, 0.0f);
    }
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    offscreenAddBoundingBox(offscreenNameToId("ofs"), left, top, right, bottom);
}

// Runs the tessellator over the drawn outline and flushes the vertices for the GPU.
USER_FUNC(tess_test_run) {
    tess_test();
    DCFlushRange(tess_test_work->vertices, tess_test_work->vertexCount * sizeof(TessVertex));
    return EVT_RETURN_DONE;
}

USER_FUNC(tess_test_disp_entry) {
    dispEntry(CAMERA_OFFSCREEN2, 0.0f, 1, tess_test_disp, NULL);
    return EVT_RETURN_DONE;
}

USER_FUNC(tess_test_end) {
    smartFree(tess_test_work->capture);
    _mapFree(tess_test_work);
    return EVT_RETURN_DONE;
}

void tess_test_begin(u32 type, void* polygonData) {
}

void tess_test_edge_flag(u8 flag, void* polygonData) {
}

void tess_test_end_polygon(void* polygonData) {
}

void tess_test_error(u32 error, void* polygonData) {
}

// Collects the triangle list: each vertex is an index into the outline.
void tess_test_vertex(void* vertexData, void* polygonData) {
    if (tess_test_work->indexCount >= TESS_MAX_INDICES) {
        OSPanic("evt_init.c", 1263, "MAX_INDICES over!!\n");
    }
    tess_test_work->indices[tess_test_work->indexCount++] = (s32)vertexData;
}

// Adds a vertex where two edges cross, unless it repeats a corner; it is marked as on the outline when the
// crossing edges are outline edges.
void tess_test_combine(f64 coords[3], u32 index[4], f32 weight[4], u32* outIndex, void* polygonData) {
    TessVertex* v0 = &tess_test_work->vertices[index[0]];
    TessVertex* v1 = &tess_test_work->vertices[index[1]];
    TessVertex* v2 = &tess_test_work->vertices[index[2]];
    TessVertex* v3 = &tess_test_work->vertices[index[3]];
    TessVertex* out = &tess_test_work->vertices[tess_test_work->vertexCount];
    f64 x = coords[0];
    f64 y = coords[1];
    f64 y0;
    f64 x1 = v1->x;

    if (v0->x == x1) {
        y0 = v0->y;
        if (y0 == v1->y && v0->x == v2->x && y0 == v2->y && v0->x == v3->x && y0 == v3->y) {
            return;
        }
    }
    if (v0->x == x1 && v0->y == v1->y && weight[2] == 0.0f && weight[3] == 0.0f) {
        return;
    }
    out->x = x;
    out->y = y;
    out->contour = tess_test_work->contourCount;
    {
        GXColor color = {0x9B, 0xFF, 0x9B, 0xFF};
        out->color = color;
    }
    out->edge = 3;
    if (index[0] == index[1] + 1) {
        if (index[2] == index[3] + 1) {
            if (v0->edge == 0 && v2->edge == 0) {
                out->edge = 4;
            }
        } else if (index[2] == index[3] - 1) {
            if (v0->edge == 0 && v3->edge == 0) {
                out->edge = 4;
            }
        }
    } else if (index[0] == index[1] - 1) {
        if (index[2] == index[3] - 1) {
            if (v1->edge == 0 && v3->edge == 0) {
                out->edge = 4;
            }
        } else if (index[2] == index[3] + 1) {
            if (v1->edge == 0 && v2->edge == 0) {
                out->edge = 4;
            }
        }
    } else if (v0->edge == 4 || v1->edge == 4) {
        if (v2->edge == 4 || v3->edge == 4) {
            out->edge = 4;
        } else if (index[2] == index[3] + 1) {
            if (v2->edge == 0) {
                out->edge = 4;
            }
        } else if (index[2] == index[3] - 1) {
            if (v3->edge == 0) {
                out->edge = 4;
            }
        }
    } else if (v2->edge == 4 || v3->edge == 4) {
        if (index[0] == index[1] + 1) {
            if (v0->edge == 0) {
                out->edge = 4;
            }
        } else if (index[0] == index[1] - 1) {
            if (v1->edge == 0) {
                out->edge = 4;
            }
        }
    }
    *outIndex = tess_test_work->vertexCount;
    tess_test_work->vertexCount++;
}

// Feeds each contour of the outline to the tessellator.
void tess_test(void) {
    GLUtesselator* tess = gluNewTess();
    TessVertex* v = tess_test_work->vertices;
    s32 contourCount = tess_test_work->contourCount;
    s32 i = 0;
    s32 contour;

    tess_test_work->indexCount = 0;
    gluTessCallback(tess, GLU_TESS_BEGIN_DATA, (_GLUfuncptr)tess_test_begin);
    gluTessCallback(tess, GLU_TESS_EDGE_FLAG_DATA, (_GLUfuncptr)tess_test_edge_flag);
    gluTessCallback(tess, GLU_TESS_VERTEX_DATA, (_GLUfuncptr)tess_test_vertex);
    gluTessCallback(tess, GLU_TESS_END_DATA, (_GLUfuncptr)tess_test_end_polygon);
    gluTessCallback(tess, GLU_TESS_COMBINE_DATA, (_GLUfuncptr)tess_test_combine);
    gluTessCallback(tess, GLU_TESS_ERROR_DATA, (_GLUfuncptr)tess_test_error);
    gluTessBeginPolygon(tess, NULL);
    for (contour = 0; contour < contourCount; contour++) {
        gluTessBeginContour(tess);
        while (v->contour == contour) {
            gluTessVertex(tess, &v->x, (void*)i);
            i++;
            v++;
        }
        gluTessEndContour(tess);
    }
    gluTessEndPolygon(tess);
    gluDeleteTess(tess);
}
#endif

USER_FUNC(make_item_name) {
    EvtWord* args = event->args;

    sprintf(item_name, "%03d", evtGetValue(event, args[0]));
    evtSetValue(event, args[1], (EvtWord)item_name);
    return EVT_RETURN_DONE;
}

// Keeps a Koops shell effect on Mario for 600 frames.
USER_FUNC(nokotarou_follow_test) {
    MarioWork* mario = marioGetPtr();
    EffectEntry* effect;

    if (isFirstCall) {
        event->userdatap[0] = effNokotarouEntry(0, 0, mario->position.x, mario->position.y, mario->position.z, 3.0f);
        event->userdata[1] = 0;
    }
    effect = event->userdatap[0];
    ((EffNokotarouWork*)effect->userdata)->position.x = mario->position.x;
    ((EffNokotarouWork*)effect->userdata)->position.y = mario->position.y;
    ((EffNokotarouWork*)effect->userdata)->position.z = mario->position.z;
    if (++event->userdata[1] > 600) {
        effSoftDelete(effect);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

// Puts every item on the floor of tst_item_00, 31 at a time; each run of the event shows the next 31.
EVT_BEGIN(tst_item_00_show_evt)
    SET_VALUE(LW(0), 1)
    LOOP(0)
        CALL(make_item_name, LW(0), LW(1))
        CALL(evt_item_delete, LW(1))
        ADD(LW(0), 1)
        IF_INT_GREATER_OR_EQUAL(LW(0), 339)
            BREAK_LOOP
        END_IF
    END_LOOP
    WAIT_FRAMES(1)
    SET_VALUE(LW(0), GW(0))
    SET_VALUE(LW(2), -400)
    LOOP(31)
        CALL(make_item_name, LW(0), LW(1))
        CALL(evt_item_entry, LW(1), LW(0), LW(2), 0, -100, ITEM_ENTRY_FIXED, -1, 0)
        ADD(LW(2), 25)
        ADD(LW(0), 1)
        IF_INT_GREATER_OR_EQUAL(LW(0), 339)
            BREAK_LOOP
        END_IF
    END_LOOP
    ADD(GW(0), 31)
    IF_INT_GREATER_OR_EQUAL(GW(0), 339)
        SET_VALUE(GW(0), 1)
    END_IF
    DEBUG_PUT_REG(GW(0))
    RETURN
EVT_END()

EVT_BEGIN(tst_item_00_init_evt)
    SET_VALUE(GW(0), 1)
    CALL_CHILD(tst_item_00_show_evt)
    CALL(evt_mobj_switch_red, 0, STRING("sw"), 0, 0, 50, PTR(tst_item_00_show_evt), LSWF(6))
    CALL(evt_mobj_powerupblk, STRING("powblk"), 350, 45, -100, 0, LSWF(6), 0)
    CALL(evt_mobj_save_blk, STRING("saveblk"), 380, 45, -100, 0, LSWF(6))
    CALL(evt_mobj_recovery_blk, STRING("rcvblk"), 0, 410, 45, -100, 0, LSWF(6))
    CALL(evt_mobj_recovery_blk, STRING("rcvblk2"), 10, 440, 45, -100, 0, LSWF(6))
    CALL(evt_mobj_lock, STRING("lock"), ITEM_ELEVATOR_KEY_0x1A, 500, 10, -100, -90, 0, 0, LSWF(6))
    RETURN
EVT_END()
