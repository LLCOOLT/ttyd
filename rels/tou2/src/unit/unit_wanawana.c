// unit_wanawana: wanawana battle unit (a trap; UNIT_UNUSED_WANAWANA in the unit table).

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle_unit.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "memory.h"
#include "system.h"
#include "string.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "battle/battle.h"
#include "driver/dispdrv.h"
#include "battle/battle_event_default.h"
#include "battle/battle_sub.h"
#include "unit/unit_wanawana.h"
#include "battle/battle_event_cmd.h"
#include "evt/evt_map.h"
#include "driver/mapdrv.h"
#include "libc_decls.h"

BattleUnitKind unit_wanawana;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleDataEntry data_table[1];
static BattleUnitKindPart parts[1];
static EvtWord init_event[29];
static EvtWord damage_event[10];
static EvtWord attack_event[19];
static EvtWord wait_event[6];

/** Out-of-line f32 wrapper of tan. */
static f32 tanFloat(f32 x) {
    return tan(x);
}

BattleUnitKind unit_wanawana = {
    199,
    "btl_un_wanawana",
    2,
    0,
    1,
    1,
    1,
    0,
    1,
    0,
    0,
    100,
    9,
    24,
    24,
    24,
    24,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    0.0f,
    12.0f,
    15.6f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    0,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BTL_DAMAGE1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static StatusVulnerability regist = {100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100};

static PoseTableEntry pose_table[] = {
    {28, "S_1"},
    {31, "S_1"},
    {39, "S_1"},
    {BTL_POSE_STAY_DEFAULT, "S_1"},
};

static BattleDataEntry data_table[] = {
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_wanawana", "nakayama_test4", 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 0.0f, 0.0f, 40.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x9, 0, pose_table},
};

/**
 * Guess: draw callback that renders the floor under the trap from above into a texture (a top-down camera over
 * the part's bounding box) so the trap can show the ground it sits on.
 */
static void replace_disp(CameraId camera, void* param) {
    WanaWork* wp = param;
    CameraEntry saved;
    AnimationPoseData* data;
    CameraEntry* cam;
    Vec min;
    Vec max;
    Vec pos;
    s32 w;
    s32 h;

    memcpy(&saved, camGetPtr(camera), sizeof(CameraEntry));
    data = animPoseGetAnimBaseDataPtr(wp->poseId);
    min = (Vec){data->bboxMin.x, data->bboxMin.y, data->bboxMin.z};
    max = (Vec){data->bboxMax.x, data->bboxMax.y, data->bboxMax.z};
    w = 2.0f * (max.x - min.x);
    h = 2.0f * (max.z - min.z);
    cam = camGetPtr(camera);
    w += w & 1;
    h += h & 1;
    BtlUnit_GetPartsWorldPos(wp->part, &pos.x, &pos.y, &pos.z);
    cam->cameraUp = (Vec){0.0f, 0.0f, -1.0f};
    cam->cameraAt = pos;
    cam->cameraPos = pos;
    cam->cameraPos.y += (h / 2.0f) / tanFloat(0.21816616f);
    C_MTXPerspective(cam->projection, 25.0f, (f32)w / (f32)h, 1.0f, 32767.0f);
    cam->projType = GX_PERSPECTIVE;
    C_MTXLookAt(cam->view, &cam->cameraPos, &cam->cameraUp, &cam->cameraAt);
    GXSetProjection(cam->projection, cam->projType);
    GXSetViewport(0.0f, 0.0f, w, h, 0.0f, 1.0f);
    GXSetScissor(0, 0, w, h);
    test_kururing_mapdisp(camera);
    sysWaitDrawSync();
    GXSetTexCopySrc(0, 0, w, h);
    GXSetTexCopyDst(w / 2, h / 2, GX_TF_RGB5A3, GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXCopyTex(wp->tex->address, GX_TRUE);
    GXInvalidateTexAll();
    GXPixModeSync();
    GXTexModeSync();
    memcpy(camGetPtr(camera), &saved, sizeof(CameraEntry));
    wp->ready = 1;
}

/**
 * Guess: part display callback: while the floor texture is ready,
 * binds it as the part's paper texture (type 0) and resets the paper texture afterwards.
 */
static void replace_callback(BattleUnitPart* part, s32 type) {
    WanaWork* wp = (WanaWork*)part->owner->countersetWeapon;

    if (wp->ready) {
        Mtx mtx;

        PSMTXIdentity(mtx);
        if (type == 0) {
            animSetPaperTexMtx(mtx, NULL, NULL);
            animSetPaperTexObj(&wp->obj, NULL, NULL, wp->tex, NULL, NULL, 1, 1);
        } else {
            animSetPaperTexMtx(NULL, NULL, NULL);
            animSetPaperTexObj(NULL, NULL, NULL, NULL, NULL, NULL, 1, 1);
        }
    }
}

/**
 * Guess: script helper that sets up the wanawana trap's floor-copy texture:
 * allocates the texture and work area, enables the texture overlay on the part and queues replace_disp.
 */
static USER_FUNC(replace_evt) {
    BattleUnitPart* part = BattleGetUnitPartsPtr(BattleTransID(event, -2), 1);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, -2));
    AnimationPoseData* data = animPoseGetAnimBaseDataPtr(part->poseId);
    WanaWork* wp;
    s32 w;
    s32 h;

    {
        Vec min;
        Vec max;

        min = (Vec){data->bboxMin.x, data->bboxMin.y, data->bboxMin.z};
        max = (Vec){data->bboxMax.x, data->bboxMax.y, data->bboxMax.z};

        w = 2.0f * (max.x - min.x);
        h = 2.0f * (max.z - min.z);
    }
    w += w & 1;
    h += h & 1;
    wp = BTL_ALLOC(sizeof(WanaWork));
    wp->tex = smartAlloc(GXGetTexBufferSize(w / 2, h / 2, GX_TF_RGB5A3, GX_FALSE, 0), 1);
    wp->poseId = part->poseId;
    wp->part = part;
    GXInitTexObj(&wp->obj, wp->tex->address, w / 2, h / 2, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&wp->obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    PSMTXIdentity(wp->mtx);
    animGetPtr()->poses[part->poseId].flags |= ANIM_POSE_FLAG_TEX_OVERLAY;
    part->dispCallback = replace_callback;
    unit->countersetWeapon = (struct BattleWeapon*)wp; // reused as the WanaWork pointer
    unit->screenTexBuf = wp->tex;
    wp->ready = 0;
    dispEntry(CAMERA_SHADOW, 0.0f, 0, replace_disp, wp);
    return EVT_RETURN_DONE;
}

/**
 * Init script of the unused wanawana trap unit:
 * registers its wait, attack and damage handlers (confusion uses the default handler),
 * turns on the MAPOBJ_FLAG_KURURING_PASS flag of the S_yuka map object group,
 * runs replace_evt and starts the idle event. Guess: the map object flag is about the floor the trap sits on.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_yuka"), MAPOBJ_FLAG_KURURING_PASS)
    CALL(replace_evt)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage reaction: runs the default damage handling (btldefaultevt_Damage) with LW(10) = -2 (the unit itself)
 * and LW(11) = 1.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Phase event: empty, it does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/** Attack event: uses an item if it has one; otherwise it does nothing and goes back to idling. */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Idle event: sets the unit's body part 1 to the pose given by its pose table for its current state. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()
