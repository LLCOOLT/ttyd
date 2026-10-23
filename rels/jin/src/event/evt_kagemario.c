#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario.h"
#include "driver/mapdrv.h"
#include "dolphin/gx.h"
#include "driver/animdrv.h"
#include "party.h"
#include "driver/swdrv.h"

static void callback(MapTevCallbackInfo* info);
static s32 color_change_evt(s32 on);

static USER_FUNC(check);
USER_FUNC(evt_mario_clear_party);
USER_FUNC(evt_mario_kill_party);
USER_FUNC(evt_party_cont_onoff);
USER_FUNC(evt_party_set_pos);
USER_FUNC(evt_party_stop);
static USER_FUNC(test);
USER_FUNC(evt_kagemario_change);
USER_FUNC(evt_kagemario_init);
static s32 color_change_evt(s32 on);
static void callback(MapTevCallbackInfo* info);

__declspec(section ".data") u64 fd_evt_kagemario_negone_one_374;
__declspec(section ".data") s32 fd_evt_kagemario_neg_one_382[1];
__declspec(section ".data") s32 fd_evt_kagemario___local_PI_383[1];
__declspec(section ".data") s32 fd_evt_kagemario___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_evt_kagemario_one_negone_373;
__declspec(section ".data") s32 fd_evt_kagemario___local_PIO2_384[1];
__declspec(section ".data") s32 fd_evt_kagemario_one_381[1];
__declspec(section ".data") u64 fd_evt_kagemario_negone_one_360;
__declspec(section ".data") s32 fd_evt_kagemario_neg_one_365[1];
__declspec(section ".data") s32 fd_evt_kagemario___local_PI_366[1];
__declspec(section ".data") s32 fd_evt_kagemario___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_evt_kagemario_one_negone_359;
__declspec(section ".data") s32 fd_evt_kagemario___local_PIO2_367[1];
__declspec(section ".data") s32 fd_evt_kagemario_one_364[1];
static __declspec(section ".data") s32 evt_check[4];
s32 evt_usu_kagemario_party_kill[42];

static void callback(MapTevCallbackInfo* info) {
    s32 stage = info->tevStage;
    s32 texCoord = info->texCoord;
    s32 texMap = info->texMap;
    s32 field_0x18 = info->indStage;

    if (marioGetPtr()->flags & 0x2000000) {
        GXColor color = {0, 0, 0, 255};
        GXSetTevColor(GX_TEVREG0, color);
    } else {
        GXColor color = {77, 9, 82, 255};
        GXSetTevColor(GX_TEVREG0, color);
    }
    GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevSwapMode(stage, GX_TEV_SWAP0, GX_TEV_SWAP0);
    info->tevStage = stage + 1;
    info->texMap = texMap;
    info->indStage = field_0x18;
    info->texCoord = texCoord;
}

static s32 color_change_evt(s32 on) {
    s32 i;

    if (on == 0) {
        for (i = 0; i < 3; i++) {
            animPoseSetMaterialFlagOff(marioGetPtr()->paperAnimGroupId[i], 0x0A000000);
        }
        marioGetPtr()->flags &= ~0x40000000;
    } else {
        mapSetTevCallback(10, callback);
        for (i = 0; i < 3; i++) {
            animPoseSetMaterialFlagOn(marioGetPtr()->paperAnimGroupId[i], 0x0A000000);
        }
        marioGetPtr()->flags |= 0x40000000;
    }
    return 0;
}

static USER_FUNC(check) {
    if (partyGetPtr(0) != NULL) {
        animPoseSetMaterialFlagOff(partyGetPtr(0)->paperAnimGroup, 0x0A000000);
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(evt_kagemario_init) {
    s32 sequence = swByteGet(0);

    if (sequence >= 201 && sequence < 212) {
        color_change_evt(1);
        evtEntry(evt_check, 0, 0);
    } else {
        color_change_evt(0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(evt_kagemario_change) {
    color_change_evt(event->args[0]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(test) {
    marioGetPtr()->prevPartyMemberId[0] = 0;
    marioGetPtr()->prevPartyMemberId[1] = 0;
    return EVT_RETURN_DONE;
}

__declspec(section ".data") u64 fd_evt_kagemario_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_evt_kagemario_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_evt_kagemario___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_evt_kagemario___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_evt_kagemario_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_evt_kagemario___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_evt_kagemario_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_evt_kagemario_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_evt_kagemario_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_evt_kagemario___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_evt_kagemario___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_evt_kagemario_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_evt_kagemario___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_evt_kagemario_one_364[] = {
    1065353216,
};

static __declspec(section ".data") EVT_BEGIN(evt_check)
    CALL(check)
    RETURN
EVT_END()

EVT_BEGIN(evt_usu_kagemario_party_kill)
    SWITCH(GSW(0))
        CASE_BETWEEN(201, 205)
        CALL(evt_party_stop, 0)
        CALL(evt_party_set_pos, 0, 0, -1000, 0)
        CALL(evt_party_cont_onoff, 0, 0)
        CALL(evt_mario_kill_party, 0)
        CALL(evt_party_stop, 1)
        CALL(evt_party_set_pos, 1, 0, -1000, 0)
        CALL(evt_party_cont_onoff, 1, 0)
        CALL(evt_mario_clear_party, 1)
        CALL(test)
    END_SWITCH
    RETURN
EVT_END()

