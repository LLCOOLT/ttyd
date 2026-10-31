// Title sequence: the title screen and its "press start" prompt.
#include "version.h"
#include "seq/seq_title.h"
#include "driver/animdrv.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/fadedrv.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "manager/fontmgr.h"
#include "pmario_sound.h"
#include "sound.h"
#include "sdk/texPalette.h"
#include "system.h"
#include "win/win_main.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>
#include "libc_decls.h"
#include <dolphin/pad.h>

TitleWork work2;
TitleWork* wp2 = &work2;

// Resting height of the title logo (TitleWork.topPosY). The timings below use one second,
// VERSION_PICK(60, gp->framerate) frames: US counts at the display frame rate (50 or 60), JP and the demo at 60.
#if VERSION <= VERSION_DEMO_US
#define TITLE_TOP_Y 130.0f
#else
#define TITLE_TOP_Y 120.0f
#endif

void L_titleInit(SequenceWork* work);
static void titleMain(SequenceWork* work);
static void disp1(CameraId cameraId, void* param);
static void disp2(CameraId cameraId, void* param);
#if VERSION <= VERSION_JP // US and PAL export it (seq_e3 has a local copy); JP and the demo keep it local
static
#endif
    void pressStartGX(s32 alpha, f32 x, f32 y);
static void titleLoadDemo(void);

/** Stub of the debug battle selector's message file hook: always NULL, so a debug battle loads gon_11's messages. */
const char* DbgBtlSel_GetMsgDataPtr(void) {
    return NULL;
}

/**
 * Enters the title sequence: loads mariost.tpl, parks the logo halves off screen,
 * starts the title BGM (the digest theme after a game over) held paused until the curtain opens,
 * and clears the map-event-skip, save-blocks and kiosk flags.
 * Later versions do the setup in L_titleInit and also stop leftover field sound.
 */
#if VERSION <= VERSION_DEMO_US
void seq_titleInit(SequenceWork* work) {
    memset(wp2, 0, sizeof(TitleWork));
    wp2->texture = fileAllocf(4, "%s/mariost.tpl", getMarioStDvdRoot());
    wp2->topPosX = 0.0f;
    wp2->topPosY = 1000.0f;
    wp2->bottomPosX = 0.0f;
    wp2->bottomPosY = -1000.0f;
    wp2->fadeAlpha = 0.0f;
    if (seqGetPrevSeq() != SEQ_LOAD && seqGetPrevSeq() != SEQ_MAP_CHANGE && seqGetPrevSeq() == SEQ_GAME_OVER) {
        psndStopAllFadeOut();
    }
    if (seqGetPrevSeq() != SEQ_LOAD) {
        if (seqGetPrevSeq() == SEQ_GAME_OVER) {
            psndBGMOn(PSND_FADE_OUT, "BGM_DIGEST1");
            if ((u32)psbgm[0].streamId != 0xFFFFFFFFU) {
                sound.streams[psbgm[0].streamId].flags |= 0x8000;
            }
        } else {
            psndBGMOn(PSND_FADE_OUT, "BGM_TITLE1");
            if ((u32)psbgm[0].streamId != 0xFFFFFFFFU) {
                sound.streams[psbgm[0].streamId].flags |= 0x8000;
            }
        }
    }
    camGetPtr(CAMERA_2D)->flags &= ~CAM_FLAG_LETTER_BOX;
    camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_SNAP;
    gp->flags &= ~GLOBAL_FLAG_SKIP_MAP_EVENTS;
    gp->flags &= ~0x40;
    gp->flags &= ~GLOBAL_FLAG_SAVE_BLOCKS_OFF;
    gp->flags &= ~GLOBAL_FLAG_KIOSK;
}
#else
/** Later versions: L_titleInit does the setup, then the same flags are cleared. */
void seq_titleInit(SequenceWork* work) {
    L_titleInit(work);
    gp->flags &= ~GLOBAL_FLAG_SKIP_MAP_EVENTS;
    gp->flags &= ~0x40;
    gp->flags &= ~GLOBAL_FLAG_SAVE_BLOCKS_OFF;
    gp->flags &= ~GLOBAL_FLAG_KIOSK;
}
#endif

/** Leaves the title sequence: frees mariost.tpl and fades out all sound unless going on to the file select. */
void seq_titleExit(SequenceWork* work) {
    fileFree(wp2->texture);
    if (seqGetNextSeq() != SEQ_LOAD) {
        psndStopAllFadeOut();
    }
}

/** Per-frame title sequence; all the work is in titleMain. */
void seq_titleMain(SequenceWork* work) {
    titleMain(work);
}

/**
 * Debug mode state from the title-screen button code: -1 once X, B, R, B, Y, L has been entered.
 * The crash handler only shows its error screen in debug mode; otherwise it stops sound and hangs.
 */
#if VERSION >= VERSION_JP
s32 N_getDebugMode(void) {
    return wp2->debug;
}

/**
 * Later versions' title setup (called by seq_titleInit):
 * loads mariost.tpl, parks the logo off screen,
 * stops leftover field sound (BGM fades over 3 s after a map change), and starts the title BGM,
 * or the digest theme after a game over, held paused until the curtain opens.
 */
void L_titleInit(SequenceWork* work) {
    memset(wp2, 0, sizeof(TitleWork));
    wp2->texture = fileAllocf(4, "%s/mariost.tpl", getMarioStDvdRoot());
    wp2->topPosX = 0.0f;
    wp2->topPosY = 1000.0f;
    wp2->bottomPosX = 0.0f;
    wp2->bottomPosY = -1000.0f;
    wp2->fadeAlpha = 0.0f;
    wp2->debug = 0;
    if (seqGetPrevSeq() == SEQ_LOAD) {
        psndSFXAllOff();
    } else if (seqGetPrevSeq() != SEQ_LOGO) {
        if (seqGetPrevSeq() == SEQ_MAP_CHANGE) {
            psndBGMOff_f_d(PSND_FADE_OUT, 3000, 0);
            psndBGMOff_f_d(PSND_FADE_OUT | PSND_CH(1), 3000, 0);
            psndSFXAllOff();
        } else if (seqGetPrevSeq() == SEQ_GAME_OVER) {
            psndStopAllFadeOut();
        }
    }
    if (seqGetPrevSeq() != SEQ_LOAD) {
        if (seqGetPrevSeq() == SEQ_GAME_OVER) {
            if (OSGetSoundMode() == 0) {
                SoundSetOutputMode(0);
            } else {
                SoundSetOutputMode(1);
            }
            psndBGMOn(PSND_FADE_OUT, "BGM_DIGEST1");
            if ((u32)psbgm[0].streamId != 0xFFFFFFFFU) {
                sound.streams[psbgm[0].streamId].flags |= 0x8000;
            }
        } else {
            psndBGMOn(PSND_FADE_OUT, "BGM_TITLE1");
            if ((u32)psbgm[0].streamId != 0xFFFFFFFFU) {
                sound.streams[psbgm[0].streamId].flags |= 0x8000;
            }
        }
    }
    camGetPtr(CAMERA_2D)->flags &= ~CAM_FLAG_LETTER_BOX;
    camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_SNAP;
}
#endif

/**
 * Title screen state machine: waits for the BGM (and curtain animations), opens the curtain,
 * slides the logo halves in, then waits for A or Start (to the file select via SEQ_LOAD)
 * or about 19 s of idling (to the dmo_00 opening demo).
 * Queues the logo draws each frame; later versions also track the debug-mode button code.
 */
static void titleMain(SequenceWork* work) {
    switch (wp2->state) {
        case 0:
#if VERSION <= VERSION_DEMO_US
            if (psndBGMStartCheck(0) != 0U) {
#else
            // later versions also wait for the curtain animations to load
            if (psndBGMStartCheck(0) != 0U && animGroupBaseAsync("OFF_d_maku_left_right", 2, 0) && animGroupBaseAsync("OFF_d_maku_center", 2, 0)) {
#endif
                if (seqGetPrevSeq() == SEQ_LOAD) {
                    fadeEntry(FADE_CURTAIN_SIDES_A2_TOP, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
                    fadeEntry(FADE_CURTAIN_CENTER_Z2_3D, 0, (GXColor){0x00, 0x00, 0x00, 0xFF});
#if VERSION >= VERSION_JP
                    wp2->topPosY = TITLE_TOP_Y;
                    wp2->bottomPosY = -170.0f;
#endif
                    wp2->timer = 0;
                } else if (seqGetPrevSeq() == SEQ_GAME_OVER) {
                    fadeEntry(FADE_OUT_WHITE_3D, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
                    fadeEntry(FADE_CURTAIN_CENTER_A1_3D, 0, (GXColor){0x00, 0x00, 0x00, 0xFF});
                    wp2->timer = 78;
                } else {
                    fadeEntry(FADE_OUT_WHITE_3D, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
                    fadeEntry(FADE_CURTAIN_ENTER_3D, 0, (GXColor){0x00, 0x00, 0x00, 0xFF});
                    fadeSetNarrowFast();
#if VERSION <= VERSION_DEMO_US
                    wp2->timer = 38;
#else
                    wp2->timer = 23;
#endif
                }
                wp2->state++;
            }
            break;
        case 1:
            wp2->timer--;
            if (wp2->timer == 0) {
                if ((u32)psbgm[0].streamId != 0xFFFFFFFFU) {
                    sound.streams[psbgm[0].streamId].flags &= ~0x8000;
                }
            }
            if (fadeIsFinish()) {
                if (seqGetPrevSeq() != SEQ_LOAD) {
                    fadeEntry(FADE_IN_WHITE_3D, 500, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
                    wp2->state++;
                } else {
                    wp2->topPosY = TITLE_TOP_Y;
                    wp2->bottomPosY = -170.0f;
#if VERSION >= VERSION_US
                    wp2->counter = 0;
#endif
#if VERSION >= VERSION_JP
                    wp2->frame = 0;
#endif
                    wp2->state = 3;
                }
            }
            break;
        case 2:
            wp2->topPosX = 0.0f;
            wp2->topPosY = intplGetValue(10, 300.0f, TITLE_TOP_Y, wp2->counter, VERSION_PICK(60, gp->framerate));
            wp2->timer--;
            if (wp2->timer == 0) {
                if ((u32)psbgm[0].streamId != 0xFFFFFFFFU) {
                    sound.streams[psbgm[0].streamId].flags &= ~0x8000;
                }
                if (seqGetPrevSeq() == SEQ_GAME_OVER) {
                    psndSFXOn((const char*)0xAB8);
                }
            }
            wp2->bottomPosX = 0.0f;
            wp2->bottomPosY = intplGetValue(11, -300.0f, -170.0f, wp2->counter, VERSION_PICK(60, gp->framerate));
            wp2->counter++;
            if (wp2->counter > VERSION_PICK(60, gp->framerate)) {
                titleLoadDemo();
#if VERSION == VERSION_US
                wp2->counter = 0;
#endif
#if VERSION >= VERSION_JP
                wp2->frame = 0;
#endif
                wp2->state++;
            }
            break;
        case 3:
#if VERSION >= VERSION_US
            wp2->counter++;
            if (wp2->counter > VERSION_PICK(60, gp->framerate)) {
#endif
                wp2->fadeAlpha += 0.1f;
                if (wp2->fadeAlpha > 1.0f) {
                    wp2->fadeAlpha = 1.0f;
                }
                if (keyGetButtonTrg(0) & (PAD_BUTTON_A | PAD_BUTTON_START)) {
#if VERSION <= VERSION_DEMO_US
                    psndSFXOn((const char*)0x12);
#else
                psndSFXOn((const char*)8);
#endif
                    wp2->state = 10;
                } else if (++wp2->idle > VERSION_PICK(60, gp->framerate) * 20 - VERSION_PICK(60, gp->framerate)) {
                    wp2->state = 20;
                }
#if VERSION >= VERSION_US
            }
#endif
            break;
        case 10:
            fadeEntry(FADE_CURTAIN_SIDES_A1_TOP, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
            wp2->state++;
        case 11:
            if (fadeIsFinish()) {
                fadeEntry(FADE_CURTAIN_SIDES_Z1_3D, 0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
                wp2->state++;
            }
            break;
        case 12:
            if (fadeIsFinish()) {
                fadeReset(4);
                seqSetSeq(SEQ_LOAD, NULL, NULL);
            }
            break;
        case 20:
            fadeEntry(FADE_CURTAIN_LEAVE_3D, 0, (GXColor){0x00, 0x00, 0x00, 0xFF});
#if VERSION <= VERSION_DEMO_US
            fadeEntry(FADE_OUT_WHITE, 1000, (GXColor){0x00, 0x00, 0x00, 0xFF});
#else
            fadeEntry(FADE_OUT_BLACK, 1000, (GXColor){0x00, 0x00, 0x00, 0xFF});
#endif
            psndBGMOff_f_d(PSND_FADE_OUT, 1000, 0);
            wp2->counter = 0;
            wp2->state++;
            break;
        case 21:
            wp2->topPosY = intplGetValue(11, TITLE_TOP_Y, 400.0f, wp2->counter, VERSION_PICK(60, gp->framerate));
            wp2->bottomPosY = intplGetValue(11, -170.0f, -400.0f, wp2->counter, VERSION_PICK(60, gp->framerate));
            wp2->counter++;
            if (wp2->counter > VERSION_PICK(60, gp->framerate)) {
                wp2->counter = VERSION_PICK(60, gp->framerate);
            }
            wp2->fadeAlpha -= 0.1f;
            if (wp2->fadeAlpha < 0.0f) {
                wp2->fadeAlpha = 0.0f;
            }
            if (fadeIsFinish()) {
                fadeReset(1);
#if VERSION <= VERSION_DEMO_US
                gp->areaFadeInType = FADE_OUT_WHITE;
#else
                if (pouchGetHP() <= 0) {
                    pouchSetHP(1);
                }
                gp->areaFadeInType = FADE_OUT_BLACK;
#endif
                gp->areaFadeInDuration = 0;
                seqSetSeq(SEQ_MAP_CHANGE, "dmo_00", NULL);
            }
            break;
    }
    if (wp2->state != 12 && work->state < 14) {
        dispEntry(CAMERA_3D, 0.0f, 0, disp1, NULL);
        dispEntry(CAMERA_3D_EFFECTB, 0.0f, 0, disp2, NULL);
#if VERSION >= VERSION_JP
        // a button sequence on the title screen turns on debug mode (getDebugMode)
        switch (wp2->debug) {
            case 0:
                if (keyGetButtonTrg(0) & ~PAD_BUTTON_X) {
                    wp2->debug = 0;
                } else if (keyGetButtonTrg(0) & PAD_BUTTON_X) {
                    wp2->debug++;
                }
                break;
            case 1:
                if (keyGetButtonTrg(0) & ~PAD_BUTTON_B) {
                    wp2->debug = 0;
                } else if (keyGetButtonTrg(0) & PAD_BUTTON_B) {
                    wp2->debug++;
                }
                break;
            case 2:
                if (keyGetButtonTrg(0) & ~PAD_TRIGGER_R) {
                    wp2->debug = 0;
                } else if (keyGetButtonTrg(0) & PAD_TRIGGER_R) {
                    wp2->debug++;
                }
                break;
            case 3:
                if (keyGetButtonTrg(0) & ~PAD_BUTTON_B) {
                    wp2->debug = 0;
                } else if (keyGetButtonTrg(0) & PAD_BUTTON_B) {
                    wp2->debug++;
                }
                break;
            case 4:
                if (keyGetButtonTrg(0) & ~PAD_BUTTON_Y) {
                    wp2->debug = 0;
                } else if (keyGetButtonTrg(0) & PAD_BUTTON_Y) {
                    wp2->debug++;
                }
                break;
            case 5:
                if (keyGetButtonTrg(0) & ~PAD_TRIGGER_L) {
                    wp2->debug = 0;
                } else if (keyGetButtonTrg(0) & PAD_TRIGGER_L) {
                    wp2->debug = -1;
                }
                break;
        }
#endif
    }
}

/** 3D-camera draw callback: draws the title background image from mariost.tpl through the 2D camera. */
static void disp1(CameraId cameraId, void* param) {
    CameraEntry* cam = camGetPtr(CAMERA_2D);
    CameraEntry saved;
    f32 proj[7];
    f32 vp[6];

    saved = *camGetPtr(cameraId);
    *camGetPtr(cameraId) = *cam;
    GXGetProjectionv(proj);
    GXGetViewportv(vp);
    GXSetProjection(cam->projection, cam->projType);
    GXSetViewport(cam->viewport[0], cam->viewport[1], cam->viewport[2],
                  cam->viewport[3], cam->viewport[4], cam->viewport[5]);
    winTexInit(*wp2->texture->data);
#if VERSION >= VERSION_US
    winTexSet(5, (Vec){0.0f, 0.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
#else
    winTexSet(7, (Vec){0.0f, 0.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
#endif
    *camGetPtr(cameraId) = saved;
    GXSetProjectionv(proj);
    GXSetViewport(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
}

/**
 * Effect-layer draw callback: draws the two logo halves at their animated positions (per-language images in US
 * and PAL) and the pulsing "press start" prompt.
 * Later versions show the build date and time while Z is held in debug mode.
 */
static void disp2(CameraId cameraId, void* param) {
    CameraEntry* cam = camGetPtr(CAMERA_2D);
    CameraEntry saved;
    f32 proj[7];
    f32 vp[6];
    s32 alpha;
    f32 s;
#if VERSION == VERSION_EU
    s32 tbl[6] = {19, 19, 20, 21, 22, 23};
#elif VERSION >= VERSION_US
    s32 tbl[6] = {21, 21, 22, 23, 24, 25};
#endif

    saved = *camGetPtr(cameraId);
    *camGetPtr(cameraId) = *cam;
    GXGetProjectionv(proj);
    GXGetViewportv(vp);
    GXSetProjection(cam->projection, cam->projType);
    GXSetViewport(cam->viewport[0], cam->viewport[1], cam->viewport[2],
                  cam->viewport[3], cam->viewport[4], cam->viewport[5]);
    winTexInit(*wp2->texture->data);
#if VERSION >= VERSION_US
    winTexSetNearest(tbl[gp->language], (Vec){wp2->topPosX, wp2->topPosY - 20.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
#if VERSION == VERSION_EU
    winTexSet(gp->language + 7, (Vec){wp2->bottomPosX, wp2->bottomPosY, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
#else
    winTexSet(gp->language + 9, (Vec){wp2->bottomPosX, wp2->bottomPosY, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
#endif
#elif VERSION <= VERSION_DEMO_US
    winTexSet(5, (Vec){wp2->topPosX, wp2->topPosY, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    winTexSet(6, (Vec){wp2->bottomPosX, wp2->bottomPosY, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
#else
    winTexSetNearest(5, (Vec){wp2->topPosX, wp2->topPosY, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    winTexSet(6, (Vec){wp2->bottomPosX, wp2->bottomPosY, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
#endif
#if VERSION <= VERSION_DEMO_US
    s = (f32)sin((f32)gp->retraceCount / 30.0f);
#else
    wp2->frame++;
    s = (f32)sin(6.2831855f * (f32)wp2->frame / 120.0f);
#endif
    alpha = (s32)(wp2->fadeAlpha * (459.0f * s));
    if (alpha < 0) {
        alpha = 0;
    }
    if (alpha > 255) {
        alpha = 255;
    }
#if VERSION >= VERSION_US
    pressStartGX(alpha, 0.0f, -122.0f);
#else
    pressStartGX(alpha, 0.0f, -110.0f);
#endif
#if VERSION >= VERSION_JP
    if (wp2->debug < 0 && (keyGetButton(0) & PAD_TRIGGER_Z)) {
        FontDrawStart();
        FontDrawEdge();
        FontDrawColor((GXColor){0xFA, 0xFA, 0xFA, 0xFF});
        FontDrawScale(0.8f);
        FontDrawString(60.0f, 220.0f, build_date_ptr);
        FontDrawString(200.0f, 220.0f, build_time_ptr);
    }
#endif
    *camGetPtr(cameraId) = saved;
    GXSetProjectionv(proj);
    GXSetViewport(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
}

#if VERSION <= VERSION_JP
static
#endif
    void pressStartGX(s32 alpha, f32 x, f32 y) {
    CameraEntry* camera = camGetCurPtr();
    GXTexObj startText, gradient;
    Mtx v17, v16;

#if VERSION >= VERSION_US
#if VERSION == VERSION_EU
    TEXGetGXTexObjFromPalette(*wp2->texture->data, &startText, gp->language + 13);
#else
    TEXGetGXTexObjFromPalette(*wp2->texture->data, &startText, gp->language + 15);
#endif
    GXLoadTexObj(&startText, GX_TEXMAP0);
    TEXGetGXTexObjFromPalette(*wp2->texture->data, &gradient, 6);
#else
    TEXGetGXTexObjFromPalette(*wp2->texture->data, &startText, 8);
    GXLoadTexObj(&startText, GX_TEXMAP0);
    TEXGetGXTexObjFromPalette(*wp2->texture->data, &gradient, 9);
#endif
    GXLoadTexObj(&gradient, GX_TEXMAP1);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
    GXSetTevColor(GX_TEVREG0, (GXColor){0x00, 0x00, 0x00, alpha});
    GXSetNumChans(0);
    GXSetNumTexGens(2);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, 30);
    MTXScale(v16, 1.0f, 1.0f, 1.0f);
    // the frame count scrolls the "press start" gradient
#if VERSION <= VERSION_DEMO_US
    MTXTrans(v17, (f32)gp->retraceCount / -200.0f, 0.0f, 0.0f);
#else
    MTXTrans(v17, (f32)wp2->frame / -200.0f, 0.0f, 0.0f);
#endif
    MTXConcat(v16, v17, v17);
    GXLoadTexMtxImm(v17, 30, GX_MTX2x4);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_DISABLE, GX_LEQUAL, GX_DISABLE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    MTXTrans(v17, x, y, 0.0f);
    MTXScale(v16, (f32)GXGetTexObjWidth(&startText), (f32)GXGetTexObjHeight(&startText), 1.0f);
    MTXConcat(v17, v16, v17);
    MTXConcat(camera->view, v17, v17);
    GXLoadPosMtxImm(v17, 0);
    GXSetCurrentMtx(0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-0.5f, -0.5f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(0.5f, -0.5f, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.5f, 0.5f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(-0.5f, 0.5f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
}

/**
 * Prefetches demo.tpl and the animations used by the dmo_00 opening demo (Peach, the treasure chest,
 * a Goomba and the other characters of the opening) once the logo has landed, so the idle demo starts quickly.
 */
static void titleLoadDemo(void) {
    fileAsyncf(4, 0, "%s/demo.tpl", getMarioStDvdRoot());
    animGroupBaseAsync("c_peach", 0, 0);
    animGroupBaseAsync("c_nazo", 0, 0);
    animGroupBaseAsync("MOBJ_GoldenTreasureBox", 0, 0);
#if VERSION >= VERSION_JP
    animGroupBaseAsync("MOBJ_BigTreasureBox", 0, 0);
#endif
    animGroupBaseAsync("c_roten", 0, 0);
    animGroupBaseAsync("c_kuribo_n", 0, 0);
    animGroupBaseAsync("c_tyusan", 0, 0);
}
