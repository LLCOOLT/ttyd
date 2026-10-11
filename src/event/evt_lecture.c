#include "evt/evt_lecture.h"
#include "driver/camdrv.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mariost.h"
#include "party.h"

static Vec stPt;
static Vec stAt;
static Vec stMpos;
static Vec stPpos;
static Vec stXpos;
static f32 stMdir1;
static f32 stMdir2;
static f32 stMdir3;
static f32 stMdir4;
static f32 stPdir1;
static f32 stPdir2;
static f32 stPdir3;
static f32 stPdir4;
static f32 stXdir1;
static f32 stXdir2;
static f32 stXdir3;
static f32 stXdir4;
static void* lect_work;

// s32 level
USER_FUNC(lect_set_systemlevel) {
    marioStSystemLevel(evtGetValue(event, *event->args));
    return EVT_RETURN_DONE;
}

USER_FUNC(lect_test_systemlevel) {
    marioStGetSystemLevel();
    return EVT_RETURN_DONE;
}

// save the camera, Mario, partner and follower positions
USER_FUNC(lect_cam_save) {
    CameraEntry* camera;
    MarioWork* mario;
    PartyEntry* party;
    PartyEntry* extra;

    camera = camGetPtr(CAMERA_3D);
    mario = marioGetPtr();
    party = partyGetPtr(marioGetPartyId());
    extra = partyGetPtr(marioGetExtraPartyId());

    stPt = camera->cameraPos;
    stAt = camera->cameraAt;
    stMpos = mario->position;
    stMdir1 = mario->unk1A8;
    stMdir2 = mario->unk1AC;
    stMdir3 = mario->directionView;
    stMdir4 = mario->unk19C;
    if (party) {
        stPpos = party->position;
        stPdir1 = party->field_10C;
        stPdir2 = party->field_110;
        stPdir3 = party->field_100;
        stPdir4 = party->field_FC;
    }
    if (extra) {
        stXpos = extra->position;
        stXdir1 = extra->field_10C;
        stXdir2 = extra->field_110;
        stXdir3 = extra->field_100;
        stXdir4 = extra->field_FC;
    }
    return EVT_RETURN_DONE;
}

// s32 msec
USER_FUNC(lect_cam_load) {
    s32 msec;
    CameraEntry* camera;
    MarioWork* mario;
    PartyEntry* party;
    PartyEntry* extra;

    msec = evtGetValue(event, *event->args);
    camera = camGetPtr(CAMERA_3D);
    mario = marioGetPtr();
    party = partyGetPtr(marioGetPartyId());
    extra = partyGetPtr(marioGetExtraPartyId());

    camera->presetPos = camera->cameraPos;
    camera->presetAt = camera->cameraAt;
    camera->storedPos = stPt;
    camera->storedAt = stAt;
    camera->startTimeA = gp->renderTime;
    camera->durationA = OSMillisecondsToTicks(msec);
    camera->stateA = 3;
    camera->curveA = 11;

    mario->position = stMpos;
    mario->unk1A8 = stMdir1;
    mario->unk1AC = stMdir2;
    mario->directionView = stMdir3;
    mario->unk19C = stMdir4;
    if (party) {
        party->position = stPpos;
        party->field_10C = stPdir1;
        party->field_110 = stPdir2;
        party->field_100 = stPdir3;
        party->field_FC = stPdir4;
    }
    if (extra) {
        extra->position = stXpos;
        extra->field_10C = stXdir1;
        extra->field_110 = stXdir2;
        extra->field_100 = stXdir3;
        extra->field_FC = stXdir4;
    }
    return EVT_RETURN_DONE;
}

// void* evt
USER_FUNC(lect_juyoitem_rel_set) {
    lect_work = (void*)evtGetValue(event, *event->args);
    return EVT_RETURN_DONE;
}

// void* evt (out)
USER_FUNC(lect_juyoitem_rel_get) {
    evtSetValue(event, *event->args, (s32)lect_work);
    return EVT_RETURN_DONE;
}

// clang-format off
EVT_BEGIN(all_juyoitem_lecture)
    CALL(lect_juyoitem_rel_get, LW(0))
    CALL_CHILD(LW(0))
    RETURN
    END
EVT_END();
// clang-format on
