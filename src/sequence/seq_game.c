// Game sequence: the sequence that runs while Mario is in the field.

#include "seq/seq_game.h"
#include "driver/fadedrv.h"
#include "evt/evt_fade.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "pmario_sound.h"

//.sbss
static OSTime none_key;

//.sdata
EVT_BEGIN(maku_spread)
    WAIT_MS(2000)
    CALL(evt_fade_entry, FADE_CURTAIN_LEAVE, 0, 0, 0, 0)
    RETURN
EVT_END()

void seq_gameInit(SequenceWork* wp) {
    none_key = OSGetTime();
    gp->systemLevelFlags &= ~0x10;
}

void seq_gameMain(SequenceWork* wp) {
    CameraEntry *camera, *camera2;
    Vec position;

    switch (wp->state) {
        case 0:
            if ((gp->flags & GLOBAL_FLAG_CURTAIN_OPEN) != 0) {
                fadeEntry(FADE_IN_WHITE_2D, 900, (GXColor){0, 0, 0, 0xFF});
                evtEntryType(maku_spread, 0, 0, 0);
                gp->flags &= ~GLOBAL_FLAG_CURTAIN_OPEN;
            } else if (!gp->didAreaChange) {
                fadeEntry(gp->mapFadeOutType, gp->mapFadeOutDuration, (GXColor){0, 0, 0, 0xFF});
            } else {
                fadeEntry(gp->areaFadeOutType, gp->areaFadeOutDuration, (GXColor){0, 0, 0, 0xFF});
            }
            gp->mapFadeOutType = FADE_IN_BLACK;
            gp->mapFadeOutDuration = 300;
            gp->areaFadeOutType = FADE_IN_BLACK;
            gp->areaFadeOutDuration = 300;
            wp->state++;
            break;

        case 1:
            if (gp->flags & GLOBAL_FLAG_KIOSK && gp->flags & GLOBAL_FLAG_KIOSK_TIMEOUT && fadeIsFinish() && !seqCheckSeq()) {
                gp->flags &= ~GLOBAL_FLAG_KIOSK_TIMEOUT;
                seqSetSeq(SEQ_GAME_OVER, NULL, NULL);
            }
            marioGetPtr(); // unused
            camera = camGetPtr(CAMERA_3D);
            position = camera->cameraPos;
            camera2 = camGetPtr(CAMERA_3D);
            psndSetPosDirListener(&position, camera2->viewYaw);
            break;
    }
}

void seq_gameExit(SequenceWork* wp) {
    gp->flags &= ~GLOBAL_FLAG_SKIP_MAP_EVENTS;
}
