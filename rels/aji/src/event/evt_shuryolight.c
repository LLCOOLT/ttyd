#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "manager/evtmgr_cmd.h"
#include "memory.h"

void animPoseDrawShape(s32 poseId, s32 shapeIdx);
void animPoseSetDispCallBack(s32 poseId, void (*callback)(void* param, s32 group), void* param);
typedef struct ShuryoLight { NpcEntry* npc; const char** anims; s32 status; s32 group; s32 shape; } ShuryoLight;
typedef struct ShuryoWork { s32 powerEvt; s32 headEvt; s32 tueEvt; ShuryoLight lights[5]; } ShuryoWork;
static ShuryoWork* slhp;

static USER_FUNC(evt_shuryolight_set_anim);
static USER_FUNC(evt_shuryolight_wait_anim_end);
USER_FUNC(evt_sub_random);
static USER_FUNC(evt_shuryolight_delete);
static USER_FUNC(evt_shuryolight_run_tue_evt);
static USER_FUNC(evt_shuryolight_run_head_evt);
static USER_FUNC(evt_shuryolight_run_power_evt);
USER_FUNC(evt_shuryolight_run_evt_2_text_B538);
static USER_FUNC(evt_shuryolight_get_status);
static USER_FUNC(evt_shuryolight_get_anim_time);
USER_FUNC(evt_shuryolight_init_2_text_B870);
static s32 shuryolightRunEvt(s32* code, s32 id);
static void shuryolightSetAnim(s32 index, s32 anim);
static void shuryolight_callback(void* param, s32 group);

__declspec(section ".data") u64 fd_evt_shuryolight_negone_one_374;
__declspec(section ".data") s32 fd_evt_shuryolight_neg_one_382[1];
__declspec(section ".data") s32 fd_evt_shuryolight___local_PI_383[1];
__declspec(section ".data") s32 fd_evt_shuryolight___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_evt_shuryolight_one_negone_373;
__declspec(section ".data") s32 fd_evt_shuryolight___local_PIO2_384[1];
__declspec(section ".data") s32 fd_evt_shuryolight_one_381[1];
__declspec(section ".data") u64 fd_evt_shuryolight_negone_one_360;
__declspec(section ".data") s32 fd_evt_shuryolight_neg_one_365[1];
__declspec(section ".data") s32 fd_evt_shuryolight___local_PI_366[1];
__declspec(section ".data") s32 fd_evt_shuryolight___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_evt_shuryolight_one_negone_359;
__declspec(section ".data") s32 fd_evt_shuryolight___local_PIO2_367[1];
__declspec(section ".data") s32 fd_evt_shuryolight_one_364[1];
static __declspec(section ".data") s32 green_light_anim[5];
static __declspec(section ".data") s32 yellow_light_anim[5];
static __declspec(section ".data") s32 red_light_anim[5];
static __declspec(section ".data") s32 orange_light_anim[5];
s32 shuryolight_pow_normal_2_data_36ED8[44];
static s32 shuryolight_pow_tenmetu[31];
s32 shuryolight_head_normal_2_data_37004[30];
static s32 shuryolight_head_tenmetu[20];
static s32 shuryolight_head_off[14];
s32 shuryolight_tue_normal_2_data_37104[31];

__declspec(section ".data") u64 fd_evt_shuryolight_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_evt_shuryolight_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_evt_shuryolight___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_evt_shuryolight___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_evt_shuryolight_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_evt_shuryolight___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_evt_shuryolight_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_evt_shuryolight_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_evt_shuryolight_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_evt_shuryolight___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_evt_shuryolight___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_evt_shuryolight_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_evt_shuryolight___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_evt_shuryolight_one_364[] = {
    1065353216,
};

static __declspec(section ".data") s32 green_light_anim[] = {
    (s32)"L_1C", (s32)"L_1B", (s32)"L_1D", (s32)"L_1A", (s32)"L_1E",
};

static __declspec(section ".data") s32 yellow_light_anim[] = {
    (s32)"L_2C", (s32)"L_2B", (s32)"L_2D", (s32)"L_2A", (s32)"L_2E",
};

static __declspec(section ".data") s32 red_light_anim[] = {
    (s32)"L_3C", (s32)"L_3B", (s32)"L_3D", (s32)"L_3A", (s32)"L_3E",
};

static __declspec(section ".data") s32 orange_light_anim[] = {
    (s32)"L_4C", (s32)"L_4B", (s32)"L_4D", (s32)"L_4A", (s32)"L_4E",
};

EVT_BEGIN(shuryolight_pow_normal_2_data_36ED8)
    LOOP(0)
        CALL(evt_shuryolight_set_anim, 0, 1)
        CALL(evt_sub_random, 3000, LW(0))
        ADD(LW(0), 3000)
        WAIT_MS(LW(0))
        CALL(evt_sub_random, 100, LW(0))
        DIVIDE(LW(0), 30)
        IF_INT_GREATER(LW(0), 0)
            LOOP(LW(0))
                CALL(evt_shuryolight_set_anim, 0, 3)
                WAIT_MS(80)
                CALL(evt_shuryolight_set_anim, 0, 1)
                WAIT_MS(80)
            END_LOOP
        END_IF
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(shuryolight_pow_tenmetu)
    LOOP(0)
        CALL(evt_shuryolight_set_anim, 0, 1)
        CALL(evt_sub_random, 3000, LW(0))
        CALL(evt_sub_random, 1000, LW(1))
        ADD(LW(0), LW(1))
        ADD(LW(0), 700)
        WAIT_MS(LW(0))
        CALL(evt_shuryolight_set_anim, 0, 3)
        WAIT_MS(200)
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(shuryolight_head_normal_2_data_37004)
    SET_VALUE(LW(0), 3)
    LOOP(0)
        CALL(evt_shuryolight_set_anim, LW(0), 1)
        WAIT_MS(400)
        CALL(evt_shuryolight_set_anim, LW(0), 3)
        SUBTRACT(LW(0), 1)
        IF_INT_LESS(LW(0), 1)
            SET_VALUE(LW(0), 3)
            WAIT_MS(400)
        END_IF
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(shuryolight_head_tenmetu)
    LOOP(0)
        CALL(evt_shuryolight_set_anim, 1, 4)
        CALL(evt_shuryolight_set_anim, 2, 4)
        CALL(evt_shuryolight_set_anim, 3, 4)
        CALL(evt_shuryolight_wait_anim_end, 1)
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(shuryolight_head_off)
    CALL(evt_shuryolight_set_anim, 1, 3)
    CALL(evt_shuryolight_set_anim, 2, 3)
    CALL(evt_shuryolight_set_anim, 3, 3)
    RETURN
EVT_END()

EVT_BEGIN(shuryolight_tue_normal_2_data_37104)
    LOOP(0)
        CALL(evt_shuryolight_set_anim, 4, 0)
        CALL(evt_shuryolight_wait_anim_end, 4)
        CALL(evt_shuryolight_set_anim, 4, 1)
        WAIT_MS(1000)
        CALL(evt_shuryolight_set_anim, 4, 2)
        CALL(evt_shuryolight_wait_anim_end, 4)
        CALL(evt_shuryolight_set_anim, 4, 3)
        WAIT_MS(1000)
    END_LOOP
    RETURN
EVT_END()

static void shuryolight_callback(void* param, s32 group) {
    ShuryoLight* lights = param;
    s32 i;

    for (i = 0; i < 5; i++) {
        if (group == lights[i].group) {
            break;
        }
    }
    if (i != 5) {
        animPoseMain(lights[i].npc->poseId);
        animPoseDrawShape(lights[i].npc->poseId, lights[i].shape);
    }
}
static void shuryolightSetAnim(s32 index, s32 anim) {
    ShuryoLight* light = &slhp->lights[index];

    light->status = anim;
    animPoseSetAnim(light->npc->poseId, light->anims[anim], TRUE);
}
static s32 shuryolightRunEvt(s32* code, s32 id) {
    if (evtCheckID(id)) {
        evtDeleteID(id);
    }
    return evtEntryType(code, 0, 0, 0)->eventId;
}
USER_FUNC(evt_shuryolight_init_2_text_B870) {
    NpcEntry* base = npcNameToPtr((const char*)evtGetValue(event, event->args[0]));
    ShuryoLight* lights;
    NpcEntry* npc;

    npcEntry("light_power", "c_shuryo");
    npcEntry("light_head_1", "c_shuryo");
    npcEntry("light_head_2", "c_shuryo");
    npcEntry("light_head_3", "c_shuryo");
    npcEntry("light_tue_1", "c_shuryo");
    slhp = _mapAlloc(sizeof(ShuryoWork));
    slhp->powerEvt = 0;
    slhp->headEvt = 0;
    slhp->tueEvt = 0;
    lights = slhp->lights;
    npc = npcNameToPtr("light_power");
    npc->flags |= 0xA0;
    lights[0].npc = npc;
    lights[0].anims = (const char**)green_light_anim;
    lights[0].group = animPoseGetGroupIdx(base->poseId, "locator6");
    lights[0].shape = animPoseGetShapeIdx(npc->poseId, "pPlaneShape34");
    shuryolightSetAnim(0, 1);
    npc = npcNameToPtr("light_head_1");
    npc->flags |= 0xA0;
    lights[1].npc = npc;
    lights[1].anims = (const char**)orange_light_anim;
    lights[1].group = animPoseGetGroupIdx(base->poseId, "locator9");
    lights[1].shape = animPoseGetShapeIdx(npc->poseId, "pPlaneShape37");
    shuryolightSetAnim(1, 3);
    npc = npcNameToPtr("light_head_2");
    npc->flags |= 0xA0;
    lights[2].npc = npc;
    lights[2].anims = (const char**)red_light_anim;
    lights[2].group = animPoseGetGroupIdx(base->poseId, "locator8");
    lights[2].shape = animPoseGetShapeIdx(npc->poseId, "pPlaneShape36");
    shuryolightSetAnim(2, 3);
    npc = npcNameToPtr("light_head_3");
    npc->flags |= 0xA0;
    lights[3].npc = npc;
    lights[3].anims = (const char**)yellow_light_anim;
    lights[3].group = animPoseGetGroupIdx(base->poseId, "locator7");
    lights[3].shape = animPoseGetShapeIdx(npc->poseId, "pPlaneShape35");
    shuryolightSetAnim(3, 3);
    npc = npcNameToPtr("light_tue_1");
    npc->flags |= 0xA0;
    lights[4].npc = npc;
    lights[4].anims = (const char**)red_light_anim;
    lights[4].group = animPoseGetGroupIdx(base->poseId, "locator5\0\0\0");
    lights[4].shape = animPoseGetShapeIdx(npc->poseId, "pPlaneShape36");
    shuryolightSetAnim(4, 1);
    animPoseSetDispCallBack(base->poseId, shuryolight_callback, lights);
    return EVT_RETURN_DONE;
}
static USER_FUNC(evt_shuryolight_set_anim) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);

    shuryolightSetAnim(index, evtGetValue(event, args[1]));
    return EVT_RETURN_DONE;
}
static USER_FUNC(evt_shuryolight_wait_anim_end) {
    s32 index = evtGetValue(event, event->args[0]);
    ShuryoLight* light = &slhp->lights[index];

    if (animPoseGetLoopTimes(light->npc->poseId) < 1.0f) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
static USER_FUNC(evt_shuryolight_get_anim_time) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    ShuryoLight* light = &slhp->lights[index];
    u8* data = (u8*)animPoseGetAnimDataPtr(light->npc->poseId);

    evtSetValue(event, args[1], 1000.0f * ((*(f32**)(data + 0x24))[2] - (*(f32**)(data + 0x24))[1]) / 60.0f);
    return EVT_RETURN_DONE;
}
static USER_FUNC(evt_shuryolight_get_status) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    ShuryoLight* light = &slhp->lights[index];

    evtSetValue(event, args[1], light->status);
    return EVT_RETURN_DONE;
}
USER_FUNC(evt_shuryolight_run_evt_2_text_B538) {
    s32* args = event->args;
    s32* power = (s32*)evtGetValue(event, args[0]);
    s32* head = (s32*)evtGetValue(event, args[1]);
    s32* tue = (s32*)evtGetValue(event, args[2]);

    if (power != NULL) {
        slhp->powerEvt = shuryolightRunEvt(power, slhp->powerEvt);
    }
    if (head != NULL) {
        slhp->headEvt = shuryolightRunEvt(head, slhp->headEvt);
    }
    if (tue != NULL) {
        slhp->tueEvt = shuryolightRunEvt(tue, slhp->tueEvt);
    }
    return EVT_RETURN_DONE;
}
static USER_FUNC(evt_shuryolight_run_power_evt) {
    s32* code = (s32*)evtGetValue(event, event->args[0]);

    slhp->powerEvt = shuryolightRunEvt(code, slhp->powerEvt);
    return EVT_RETURN_DONE;
}
static USER_FUNC(evt_shuryolight_run_head_evt) {
    s32* code = (s32*)evtGetValue(event, event->args[0]);

    slhp->headEvt = shuryolightRunEvt(code, slhp->headEvt);
    return EVT_RETURN_DONE;
}
static USER_FUNC(evt_shuryolight_run_tue_evt) {
    s32* code = (s32*)evtGetValue(event, event->args[0]);

    slhp->tueEvt = shuryolightRunEvt(code, slhp->tueEvt);
    return EVT_RETURN_DONE;
}
static USER_FUNC(evt_shuryolight_delete) {
    s32 i;

    if (slhp->powerEvt != 0) {
        evtDeleteID(slhp->powerEvt);
        slhp->powerEvt = 0;
    }
    if (slhp->headEvt != 0) {
        evtDeleteID(slhp->headEvt);
        slhp->headEvt = 0;
    }
    if (slhp->tueEvt != 0) {
        evtDeleteID(slhp->tueEvt);
        slhp->tueEvt = 0;
    }
    for (i = 0; i < 5; i++) {
        npcDeleteGroup(slhp->lights[i].npc);
    }
    _mapFree(slhp);
    slhp = NULL;
    return EVT_RETURN_DONE;
}
