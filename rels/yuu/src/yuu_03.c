// yuu_03 (遊技場, Pianta Parlor): minigame 4, Paper Mode (slit, squeezing through slots); entered from gor_03 or mon_10.

#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "manager/evtmgr_cmd.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include "string.h"
#include "mario/mario.h"
#include "driver/dispdrv.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "driver/effdrv.h"
#include "cam_shift.h"
#include "evt/evt_bero.h"
#include "evt/evt_cam.h"
#include "evt/evt_fade.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "evt/evt_yuugijou.h"
#include "evt/evt_yuuranking.h"
#include "mot/mot_slit.h"
#include "party.h"
#include "system.h"
#include "icon_ids.h"
#include "yuu.h"
#include "libc_decls.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"
#include "mot/mot_roll.h"
#if VERSION >= VERSION_US
USER_FUNC(evt_sub_get_language);
#endif

typedef struct RyushiWork {
    s32 flag;
    s32 mode;
    Vec base;
    Vec pos;
    s32 alpha;
    s32 count;
    f32 scale;
    s32 r;
    s32 g;
    s32 b;
    s32 r2;
    s32 g2;
    s32 b2;
} RyushiWork;
static void* yuunpc_wp;
s32 ryuwp;
RyushiWork* xwp;
#if VERSION >= VERSION_JP
Monte* yuu_03_monte_p;
#endif
static USER_FUNC(evt_ryushi_init);
BOOL yuuminigame4_gamerule(EventEntry* event, BOOL isFirstCall, MiniGameWork* wp, SlitWork* data);
#define REVISE360(a) ((3600.0f + (a)) - (s32)((3600.0f + (a)) / 360.0f) * 360)

static USER_FUNC(evt_nomal_cange);

#if VERSION >= VERSION_JP
/** Resets the camera shift offset (camShiftReset) so the camera returns to its normal framing after the minigame. */
USER_FUNC(yuu_03_cam_shift_reset) {
    camShiftReset();
    return EVT_RETURN_DONE;
}

/**
 * Draw callback for the marker icon (ICON_1B6) that floats above Mario during Paper Mode;
 * it bobs up 5 units for part of each 32-frame cycle.
 */
void yuu_03_icon_monte_disp(CameraId camera, void* param) {
    Monte* monte = param;
    s32 i;
    Vec pos;

    if (monte != NULL) {
        for (i = 0; i < monte->num; i++) {
            if (monte[i].hidden == 0) {
                pos = monte[i].icon.position;
                if ((gp->retraceCount & 0x1F) < 9) {
                    pos.y += 5.0f;
                }
                iconDispGx(&pos, 0, ICON_1B6, 1.0f);
            }
        }
    }
}

/**
 * View event that creates the single marker icon on its first call,
 * keeps it 40 units above Mario every frame and draws it through yuu_03_icon_monte_disp. Blocks forever.
 */
USER_FUNC(yuu_03_icon_monte_entry) {
    BOOL exists = FALSE;
    MiniGameWork* wp = (MiniGameWork*)event->lwData[0];
    MarioWork* mario = marioGetPtr();
    s32 total;
    s32 i;
    IconEntry* sub;
    Monte* m;

    if (isFirstCall) {
        if (yuu_03_monte_p != NULL) {
            exists = TRUE;
        }
        total = 0;
        for (i = 0; i < 1; i++) {
            total++;
        }
        yuu_03_monte_p = _mapAlloc(total * sizeof(Monte));
        memset(yuu_03_monte_p, 0, total * sizeof(Monte));
        yuu_03_monte_p->num = total;
        yuu_03_monte_p->wp = wp;
        for (i = 0; i < yuu_03_monte_p->num; i++) {
            sub = &yuu_03_monte_p[i].icon;
            sub->position = mario->position;
            sub->position.y += 40.0f;
            sub->scale = 1.0f;
        }
    }
    for (i = 0; i < yuu_03_monte_p->num; i++) {
        m = &yuu_03_monte_p[i];
        switch (m->state) {
            case 0:
                m->icon.position = mario->position;
                m->icon.position.y += 40.0f;
                break;
            case 1:
                break;
        }
    }
    if (!exists) {
        dispEntry(CAMERA_3D, 0.0f, 1, yuu_03_icon_monte_disp, yuu_03_monte_p);
    }
    return EVT_RETURN_BLOCK;
}

/**
 * Rebuilds the marker icon view event for the next round:
 * stops the old event, frees the icon array and starts a new one.
 */
USER_FUNC(yuu_03_icon_monte_restart) {
    SlitWork* data;

    if (yuu_03_monte_p != NULL) {
        data = yuu_03_monte_p->wp->data;
        if (data->viewEvent != NULL) {
            evtDeleteID(data->viewEvent->eventId);
            data->viewEvent = NULL;
            _mapFree(yuu_03_monte_p);
            data->viewEvent = evtEntryType(yuu_03_icon_monte_entry_evt, 0, 0, 0);
            data->viewEvent->lwData[0] = (EvtWord)yuu_03_monte_p->wp;
        }
    }
    return EVT_RETURN_DONE;
}
#endif

/** args[0] = minigame work pointer, args[1] = new phase for the Paper Mode state machine. */
static USER_FUNC(yuuminigame4_set_phase) {
    EvtWord* args = event->args;
    SlitWork* data = ((MiniGameWork*)evtGetValue(event, args[0]))->data;

    data->phase = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

/**
 * Script call that forces Mario out of the paper-thin "slit" squeeze motion
 * if he has just started a new motion (marioSlitForceCancel).
 */
static USER_FUNC(evt_slit_cancel) {
    MarioWork* mario = marioGetPtr();

    if (mario->trigFlags & MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION) {
        mario->trigFlags &= ~MARIO_TRIG_FLAG_IS_STARTING_NEW_MOTION;
        marioSlitForceCancel();
    }
    return EVT_RETURN_DONE;
}

/** Script call that re-runs the Paper Mode NPC (Pianta) set-up for the next round (ext_yuunpc_minigame4_init_sub). */
static USER_FUNC(re_init_yuunpc) {
    ext_yuunpc_minigame4_init_sub();
    return EVT_RETURN_DONE;
}

/**
 * Script call that clears bit 1 of the NPC work flags (yuunpc_wp_flag_off),
 * letting the Pianta NPC move once the game starts.
 */
static USER_FUNC(yuunpc_go) {
    yuunpc_wp_flag_off(1);
    return EVT_RETURN_DONE;
}

/**
 * Script call that returns Mario to his normal form:
 * cancels any roll and the paper-mode slit squeeze, then blocks until he is no longer in a slit.
 * "nomal cange" is "normal change".
 */
static USER_FUNC(evt_nomal_cange) {
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
#if VERSION <= VERSION_DEMO_JP
        marioRollCancel();
#else
        marioRollTryCancel();
#endif
        if (mario->flags & MARIO_FLAG_PAPER_MODE) {
            motSlitCancel3();
        }
    }
    if (!marioRollKeyDisable()) {
        return EVT_RETURN_BLOCK;
    }
    return (mario->dispFlags & MARIO_DISP_FLAG_SLIT) ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

/**
 * args[0] = minigame work pointer, args[1] = on/off.
 * Sets or clears the "opening cutscene pending" bit (flags bit 0).
 */
static USER_FUNC(yuuminigame4_opening_on_off) {
    EvtWord* args = event->args;
    SlitWork* data = ((MiniGameWork*)evtGetValue(event, args[0]))->data;

    if (evtGetValue(event, args[1])) {
        data->flags |= 1;
    } else {
        data->flags &= ~1;
    }
    return EVT_RETURN_DONE;
}

/**
 * args[0] = minigame work pointer, args[1] = output.
 * Writes 1 if the opening cutscene is still pending (flags bit 0), else 0.
 */
static USER_FUNC(yuuminigame4_opening_chk) {
    EvtWord* args = event->args;
    MiniGameWork* wp = (MiniGameWork*)evtGetValue(event, args[0]);

    if (((SlitWork*)wp->data)->flags & 1) {
        evtSetValue(event, args[1], 1);
    } else {
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}

/**
 * Emits one textured quad in immediate mode with its top-left corner at (x, y), size w by h,
 * and texture coordinates running to (u, v).
 */
static void polygon(f32 x, f32 y, f32 w, f32 h, f32 u, f32 v) {
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x, y, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(x + w, y, 0.0f);
    GXTexCoord2f32(u, 0.0f);
    GXPosition3f32(x + w, y - h, 0.0f);
    GXTexCoord2f32(u, v);
    GXPosition3f32(x, y - h, 0.0f);
    GXTexCoord2f32(0.0f, v);
}

/**
 * Draw callback for the "ryushi" (particle) wind streaks of Paper Mode:
 * sets up a textured additive GX pipeline and draws each active particle as a camera-facing quad that sways
 * sideways on a sine table, tinted by the work colours.
 */
static void ryushi_disp(CameraId camera, void* param) {
    RyushiWork* hdr = xwp;
    s32 g = hdr->g;
    s32 b = hdr->b;
    RyushiWork* p;
    s32 i;
    s32 n;
    f32 deg;
    f32 scale;
    f32 amp;
    Mtx trans;
    Mtx rot;
    Mtx scl;
    Mtx out;
    Mtx base;
    GXTexObj tex;

    PSMTXScale(base, hdr->scale, hdr->scale, 1.0f);
    PSMTXTransApply(base, base, hdr->pos.x, hdr->pos.y, hdr->pos.z);
    PSMTXRotRad(rot, 'y', 0.017453292f * -camGetPtr(camera)->viewYaw);
    PSMTXConcat(base, rot, base);
    effGetTexObj(0x1E, &tex);
    GXLoadTexObj(&tex, GX_TEXMAP0);
    GXSetTevColor(GX_TEVREG1, (GXColor){hdr->r2, hdr->g2, hdr->b2});
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_C0, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_A0, GX_CA_APREV, GX_CA_ZERO);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    for (i = 1, p = hdr + 1; i < ryuwp; i++, p++) {
        scale = p->scale;
        if (scale) {
            GXSetTevColor(GX_TEVREG0, (GXColor){amp, g, b, p->alpha});
            deg = 180.0f * ((p->pos.z / 8.0f + 3.14f * i / 4.0f) / 3.14f);
            n = deg / 360.0f;
            if (deg < 0.0f) {
                n--;
            }
            deg -= n * 360;
            amp = 3.0f;
            PSMTXTrans(trans, p->pos.x + amp * yuusintbl[(s32)deg], p->pos.y, p->pos.z);
            PSMTXScale(scl, scale, scale, scale);
            PSMTXConcat(trans, scl, trans);
            PSMTXConcat(base, trans, trans);
            PSMTXConcat(camGetPtr(camera)->view, trans, out);
            GXLoadPosMtxImm(out, GX_PNMTX0);
            GXSetCurrentMtx(GX_PNMTX0);
            polygon(-8.0f, -8.0f, 16.0f, 16.0f, 1.0f, 1.0f);
        }
    }
}

/** Returns a random float between min and max using rand() / 32767. */
static f32 randf(f32 min, f32 max) {
    f32 r = rand() / 32767.0f;

    return r * (max - min) + min;
}

/**
 * Allocates the particle array (241 entries: one header plus 240 particles)
 * and sets the header's default colours, scale and counters.
 */
static USER_FUNC(evt_ryushi_init) {
    RyushiWork* p;
    RyushiWork* q;
    s32 i;

    ryuwp = 241;
    xwp = p = _mapAlloc(ryuwp * sizeof(RyushiWork));
    p->mode = 0;
    p->count = 0;
    p->alpha = 0;
    p->pos.x = 0.0f;
    p->pos.y = 0.0f;
    p->pos.z = 0.0f;
    p->scale = 1.0f;
    p->r = 255;
    p->g = 0;
    p->b = 255;
    p->r2 = 255;
    p->g2 = 128;
    p->b2 = 255;
    for (i = 1, q = p + 1; i < 241; i++, q++) {
        q->flag = 0;
    }
    return EVT_RETURN_DONE;
}

/**
 * args[0] = direction mode (0 streaks toward -z, 1 toward +z).
 * Resets the particle header and lays the 240 particles out on a jittered grid (10 by 6 by 4) around the camera.
 */
static USER_FUNC(evt_ryushi_clr) {
    RyushiWork* p = xwp;
    EvtWord* args = event->args;
    s32 i;
    s32 n = ryuwp;
    s32 j;
    s32 x;
    s32 y;
    s32 z;

    p->mode = evtGetValue(event, *args++);
    p->count = 0;
    p->alpha = 0;
    p->pos.x = 0.0f;
    p->pos.y = 0.0f;
    p->pos.z = 0.0f;
    xwp->base.x = 50.0f;
    xwp->base.y = 50.0f;
    xwp->base.z = 100.0f;
    for (i = 1, p++; i < n; i++, p++) {
        j = i - 1;
        p->flag = 0;
        x = j % 10;
        y = (j / 10) % 6;
        z = j / 60;
        p->base.x = x * xwp->base.x - 4.5f * xwp->base.x + xwp->base.x / 2.0f * ((y + z) & 1);
        p->base.y = y * xwp->base.y - 2.5f * xwp->base.y;
        p->base.z = z * xwp->base.z - 1.5f * xwp->base.z;
        p->pos.x = p->base.x + randf(0.3f * -xwp->base.x, 0.3f * xwp->base.x);
        p->pos.y = p->base.y + randf(0.3f * -xwp->base.y, 0.3f * xwp->base.y);
        p->pos.z = p->base.z + randf(0.3f * -xwp->base.z, 0.3f * xwp->base.z);
        p->scale = 0.5f;
    }
    return EVT_RETURN_DONE;
}

/**
 * Per-frame update of the wind particles: moves them at a speed set by the current Paper Mode wind state,
 * wraps them around the view, fades them in and out with the state timer, and queues ryushi_disp.
 */
static USER_FUNC(evt_ryushi) {
    RyushiWork* hdr = xwp;
    Vec pos2;
    Vec pos = {0.0f, 0.0f, 0.0f};
    SlitWork* data;
    RyushiWork* p;
    s32 i;
    s32 n;
    f32 speed;
    f32 alphaScale;
    f32 camX;
    f32 scale;
    f32 w;
    f32 d;

    pos.x = hdr->pos.x;
    pos.y = hdr->pos.y;
    pos.z = hdr->pos.z;
    pos2 = pos;
    speed = 0.0f;
    alphaScale = 0.0f;
    scale = 1.0f;
    data = ((MiniGameWork*)event->lwData[0])->data;
    camX = camGetPtr(CAMERA_3D)->cameraAt.x;
    switch (data->state) {
        case 2:
        case 3:
        case 4:
#if VERSION <= VERSION_DEMO_JP
            speed = 3.3333333f;
#else
            speed = 2.9166667f;
#endif
            alphaScale = 1.0f;
            break;
        case 6:
        case 7:
        case 8:
#if VERSION <= VERSION_DEMO_JP
            speed = 3.3333333f;
#else
            speed = 2.9166667f;
#endif
            alphaScale = 1.0f;
            break;
    }
    switch (data->state) {
        case 1:
        case 5:
            alphaScale = (60 - data->timer) / 60.0f;
            scale = alphaScale;
            break;
        case 2:
        case 6:
            speed = speed * (60 - data->timer) / 60.0f;
            break;
        case 4:
        case 8:
            alphaScale = data->timer / 48.0f;
            break;
    }
    hdr->count++;
    n = hdr->count;
    if (n <= 20) {
        hdr->alpha = n * 12;
    } else {
        hdr->alpha = 255;
    }
    if (n & 1) {
        hdr->alpha /= 2;
    }
    scale = 0.5f * scale;
    for (i = 1, p = hdr + 1; i < ryuwp; i++, p++) {
        switch (xwp->mode) {
            case 0:
                p->pos.z -= speed;
                if (p->pos.z < -200.0f) {
                    p->pos.x = p->base.x + randf(0.3f * -xwp->base.x, 0.3f * xwp->base.x);
                    p->pos.y = p->base.y + randf(0.3f * -xwp->base.y, 0.3f * xwp->base.y);
                    p->pos.z = 200.0f + randf(0.3f * -xwp->base.z, 0.3f * xwp->base.z);
                }
                break;
            case 1:
                p->pos.z += speed;
                if (p->pos.z > 200.0f) {
                    p->pos.x = p->base.x + randf(0.3f * -xwp->base.x, 0.3f * xwp->base.x);
                    p->pos.y = p->base.y + randf(0.3f * -xwp->base.y, 0.3f * xwp->base.y);
                    p->pos.z = -200.0f + randf(0.3f * -xwp->base.z, 0.3f * xwp->base.z);
                }
                break;
        }
        n = (p->pos.x - camX) / (10.0f * xwp->base.x / 2.0f);
        if (n != 0) {
            if (n > 0) {
                n++;
            } else {
                n--;
            }
            p->pos.x += (-n / 2) * (10.0f * xwp->base.x);
        }
        if (p->pos.z < 0.0f) {
            d = -p->pos.z;
        } else {
            d = p->pos.z;
        }
        d -= 100.0f;
        if (d < 0.0f) {
            d = 0.0f;
        } else if (d > 100.0f) {
            d = 100.0f;
        }
        p->alpha = 0.7 * (255.0f * ((100.0f - d) / 100.0f) * alphaScale);
        p->scale = scale;
    }
    dispEntry(CAMERA_3D, dispCalcZ(&pos2), 2, ryushi_disp, NULL);
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_JP
/** Event wrapper that runs yuu_03_icon_monte_entry as a blocking view event. */
EVT_BEGIN(yuu_03_icon_monte_entry_evt)
    CALL(yuu_03_icon_monte_entry)
    RETURN
EVT_END()
#endif

/**
 * Runs the wind particle effect for one gust: clears the particles for the direction in LW(1)
 * and updates them each frame until GW(0) becomes 1 (gust over) or 2 (abort).
 */
EVT_BEGIN(ryushi_event)
    SET_VALUE(GW(0), 0)
    CALL(evt_ryushi_clr, LW(1))
    LOOP(0)
        CALL(evt_ryushi)
        IF_INT_EQUAL(GW(0), 1)
            BREAK_LOOP
        END_IF
        IF_INT_EQUAL(GW(0), 2)
            RETURN
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/** Puts Mario on the Paper Mode starting spot (x -1650) facing right. */
EVT_BEGIN(yuu_03_kaijo_init)
    CALL(evt_mario_set_pos, -1650, 0, 0)
    CALL(evt_mario_set_dir, 90, 0, 0)
    RETURN
EVT_END()

/** Puts Mario back on the start spot after the opening camera or between rounds (x -1520) facing right. */
EVT_BEGIN(yuu_03_kaijo_init2)
    CALL(evt_mario_set_pos, -1520, 0, 0)
    CALL(evt_mario_set_dir, 90, 0, 0)
    RETURN
EVT_END()

/**
 * Set-up for minigame 4 (Paper Mode): freezes Mario's controls, allocates the minigame work area,
 * dismisses the partners, starts the crowd sound and sets phase 1.
 */
EVT_BEGIN(minigame04_main)
    CALL(evt_mario_key_onoff, 0)
    CALL_CHILD(yuu_03_kaijo_init)
    CALL(evt_yuuminigame_alloc, LW(0), 3)
    CALL(yuuminigame_set_dataadr, 0, LW(0))
    CALL(evt_mario_kill_party, 0)
    CALL(evt_mario_kill_party, 1)
    CALL(evt_snd_sfxon, STRING("SFX_EVT_GAME_AUDIENCE1"), GW(10))
    CALL(yuuminigame_get_dataadr, 0, LW(0))
    CALL(yuuminigame4_set_phase, LW(0), 1)
    RETURN
EVT_END()

/**
 * Opening cutscene of Paper Mode: pans the 3D camera along the course,
 * then shows the "menu_title_minigame4" title card.
 */
EVT_BEGIN(minigame04_start_cam)
    CALL(evt_cam3d_evt_set, FLOAT(-1520.0f), FLOAT(335.0f), FLOAT(850.0f), FLOAT(-1520.0f), FLOAT(65.0f), FLOAT(-25.0f), 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_seq_wait, 2)
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_cam3d_evt_set, FLOAT(1285.0f), FLOAT(334.0f), FLOAT(850.0f), FLOAT(1285.0f), FLOAT(65.0f), FLOAT(-25.0f), 5000, 0)
#else
    CALL(evt_cam3d_evt_set, FLOAT(1285.0f), FLOAT(334.0f), FLOAT(850.0f), FLOAT(1285.0f), FLOAT(65.0f), FLOAT(-25.0f), 10000, 0)
#endif
    WAIT_MS(1000)
    CALL(evt_yuutitle_alloc, 0, 0, STRING("menu_title_minigame4"))
#if VERSION <= VERSION_DEMO_JP
    WAIT_MS(2000)
#else
    WAIT_MS(7000)
#endif
    CALL(evt_yuutitle_free)
    WAIT_MS(2000)
    RETURN
EVT_END()

/**
 * Cleans up when the player skips the opening camera:
 * frees the title card, turns off the event camera and puts Mario at the start spot.
 */
EVT_BEGIN(minigame04_start_cam_cancel)
    CALL(evt_seq_wait, 2)
    CALL(evt_yuutitle_free)
    CALL(evt_cam3d_evt_off, 0, 11)
    WAIT_FRAMES(1)
    CALL(evt_mario_wait_move_end)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL_CHILD(yuu_03_kaijo_init2)
    RETURN
EVT_END()

/**
 * Phase 1 of Paper Mode: plays the opening camera (skippable), starts the minigame music,
 * shows the countdown effect, gives Mario control, lets the Pianta NPC go and starts the counter (limit 701).
 */
EVT_BEGIN(minigame04_start)
    CALL(yuuminigame4_opening_chk, LW(0), LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        SPAWN_EVENT_GET_ID(PTR(minigame04_start_cam), LW(8))
        LOOP(0)
            IS_EVENT_RUNNING(LW(8), LW(9))
            IF_INT_EQUAL(LW(9), 0)
                CALL(evt_seq_wait, 2)
                BREAK_LOOP
            ELSE
                CALL(evt_key_get_buttontrg, 0, LW(9))
                IF_BITS_SET(LW(9), 768)
                    DELETE_EVENT(LW(8))
                    CALL(evt_seq_wait, 2)
                    CALL_CHILD(minigame04_start_cam_cancel)
                    BREAK_LOOP
                END_IF
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(yuuminigame4_opening_on_off, LW(0), 0)
        CALL_CHILD(yuu_03_kaijo_init2)
        CALL(evt_cam3d_evt_off, 0, 11)
        WAIT_FRAMES(1)
    END_IF
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_MINIGAME1"))
    CALL(eff_call_minigame, 0, 0, 0, 500)
    WAIT_MS(3000)
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_mario_key_onoff, 1)
#else
    CALL(evt_mario_set_enable_key, 352)
    CALL(evt_cam_letter_box_onoff, 0, 0)
    CALL(evt_cam_letter_box_disable, 1)
#endif
    CALL(yuunpc_go)
    CALL(evt_yuucounter_alloc, 0, 70, 2, 701)
#if VERSION >= VERSION_JP
    CALL(evt_mario_key_onoff, 1)
#endif
    RETURN
EVT_END()

/**
 * Ends a Paper Mode round: lets Mario land and walks him to the goal side,
 * shows the success or failure effect (the counter reaching 701 means failure), the score and monte rewards,
 * and pays out the medals.
 * Then asks whether to play again: quitting (or having fewer than 10 medals) sets GSWF_YUU_MINIGAME_QUIT
 * and returns Mario to gor_03; playing again charges 10 medals and resets the course.
 */
EVT_BEGIN(minigame04_end)
    // The round is over: the controls lock and the crowd reacts.
#if VERSION >= VERSION_JP
    CALL(evt_cam_letter_box_onoff, 1, 0)
    CALL(evt_cam_letter_box_disable, 0)
    CALL(evt_cam3d_evt_set_now)
    CALL(evt_mario_set_enable_key, 0)
#endif
    CALL(evt_snd_sfxon, STRING("SFX_EVT_GAME_AUDIENCE2"), 0)
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_mario_normalize)
#endif
    SET_VALUE(GW(0), 1)
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_mario_cam_y_off)
#endif
    SET_VALUE(GF(0), 1)
    SET_VALUE(LW(3), 1)
    BEGIN_INLINE_EVENT
        // Both early demos watch Mario's height in an extra event (cancel the slit below -100, clamp him at -500); the releases wait for him to land instead
#if VERSION <= VERSION_DEMO_JP
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        LOOP(0)
            IF_INT_NOT_EQUAL(LW(3), 0)
                IF_INT_LESS_OR_EQUAL(LW(1), -100)
                    SET_VALUE(LW(3), 0)
                    CALL(evt_slit_cancel)
                    CALL(evt_mario_cam_y_off)
                END_IF
            END_IF
            IF_INT_LESS_OR_EQUAL(LW(1), -500)
                CALL(evt_mario_set_pos, LW(0), -500, LW(2))
            ELSE
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            END_IF
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    // Once Mario lands on something, he walks on to the goal side (x 1650) if he stopped short of it.
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_mario_get_name_hitobj_ride, LW(0))
            IF_STR_NOT_EQUAL(LW(0), 0)
                BREAK_LOOP
            END_IF
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        IF_INT_NOT_EQUAL(GF(0), 0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            IF_INT_LESS(LW(0), 1650)
                CALL(evt_nomal_cange)
                CALL(evt_mario_mov_pos2, 1650, LW(2), 120)
            END_IF
        END_IF
    END_INLINE_EVENT
    // Running the counter out to 701 plays the failure effect; otherwise the success effect plays.
    IF_INT_GREATER_OR_EQUAL(LW(0), 701)
        CALL(eff_call_minigame, 2, 0, 0, 500)
        WAIT_MS(4000)
    ELSE
        CALL(eff_call_minigame, 1, 0, 0, 500)
        WAIT_MS(4000)
    END_IF
    // The tally screen shows the score and Mario receives his piantas, then the ranking screen records it.
    CALL(evt_yuucounter_free)
    CALL(yuugijou_montemedal_disp_onoff, 1)
    CALL(evt_yuuranking_alloc, 0, 0, 1, 0, LW(0), 0, LW(1), 701)
    WAIT_FRAMES(1)
    CALL(yuuranking_wait_button)
    CALL(yuuranking_get_monte, LW(3))
    CALL(yuugijou_add_montemedal, 0, LW(3))
    CALL(yuugijou_montemedal_wait)
    CALL(evt_yuuranking_free)
    WAIT_MS(200)
    CALL(evt_yuuranking_alloc, 0, 0, 1, 1, LW(0), 0, LW(1), 701)
    WAIT_FRAMES(1)
    CALL(yuuranking_wait_button)
    CALL(evt_yuuranking_free)
    // With fewer than 10 piantas the game ends; otherwise the player picks Continue (10 piantas) or Quit.
    SET_VALUE(LW(1), 10)
    CALL(yuugijou_get_montemedal, LW(0))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(0), 1)
    ELSE
        CALL(evt_msg_select, 0, STRING("sysyuu_03_00"))
    END_IF
    // Quitting sends Mario back through the pipe to gor_03.
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GSWF(GSWF_YUU_MINIGAME_QUIT), 1)
        CALL(evt_mario_set_prev_party_pos, 0, 0, -1000, 0)
        CALL(evt_mario_set_prev_party_pos, 1, 0, -1000, 0)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT)
        CALL(evt_bero_mapchange, STRING("gor_03"), STRING("A_dokan_02"))
        RETURN
    END_IF
    // Continuing pays 10 piantas; the course fades out, Mario goes back to the start and the racers line up.
    MULTIPLY(LW(1), -1)
    CALL(yuugijou_add_montemedal, 0, LW(1))
    CALL(yuugijou_montemedal_wait)
    WAIT_MS(200)
    CALL(yuugijou_montemedal_disp_onoff, 0)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
    CALL(evt_snd_sfxoff, GW(10))
    CALL(evt_fade_out, 1000)
    SET_VALUE(GF(0), 0)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL_CHILD(yuu_03_kaijo_init2)
    CALL(evt_cam_road_reset)
    CALL(evt_slit_cancel)
    CALL(evt_mario_normalize)
    WAIT_MS(500)
    CALL(re_init_yuunpc)
    CALL(evt_snd_sfxon, STRING("SFX_EVT_GAME_AUDIENCE1"), GW(10))
    CALL(evt_fade_in, 1000)
    RETURN
#else
        // If Mario finished in time and is above the course, he walks on to the goal side (x 1650) on landing;
        // otherwise the event just waits until he is standing on something.
        IF_INT_LESS(LW(0), 701)
            LOOP(0)
                CALL(evt_mario_get_name_hitobj_ride, LW(0))
                IF_STR_NOT_EQUAL(LW(0), 0)
                    BREAK_LOOP
                END_IF
                IF_INT_EQUAL(GF(0), 0)
                    BREAK_LOOP
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            IF_INT_GREATER(LW(1), -100)
                IF_INT_NOT_EQUAL(GF(0), 0)
                    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                    IF_INT_LESS(LW(0), 1650)
                        CALL(evt_mario_normalize)
                        CALL(evt_mario_mov_pos2, 1650, LW(2), 120)
                    END_IF
                END_IF
            ELSE
                CALL(evt_mario_wait_rideon)
                CALL(evt_mario_normalize)
            END_IF
        ELSE
            CALL(evt_mario_wait_rideon)
            CALL(evt_mario_normalize)
        END_IF
    END_INLINE_EVENT
    // Running the counter out to 701 plays the failure effect; otherwise the success effect plays.
    IF_INT_GREATER_OR_EQUAL(LW(0), 701)
        CALL(eff_call_minigame, 2, 0, 0, 500)
        WAIT_MS(4000)
    ELSE
        CALL(eff_call_minigame, 1, 0, 0, 500)
        WAIT_MS(4000)
    END_IF
    // The tally screen shows the score and Mario receives his piantas, then the ranking screen records it.
    CALL(evt_yuucounter_free)
    CALL(yuugijou_montemedal_disp_onoff, 1)
    CALL(evt_yuuranking_alloc, 0, 0, 1, 0, LW(0), 0, LW(1), 701)
    WAIT_FRAMES(1)
    CALL(yuuranking_wait_button)
    CALL(yuuranking_get_monte, LW(3))
    CALL(yuugijou_add_montemedal, 0, LW(3))
    CALL(yuugijou_montemedal_wait)
    CALL(evt_yuuranking_free)
    WAIT_MS(200)
    CALL(evt_yuuranking_alloc, 0, 0, 1, 1, LW(0), 0, LW(1), 701)
    WAIT_FRAMES(1)
    CALL(yuuranking_wait_button)
    CALL(evt_yuuranking_free)
    // With fewer than 10 piantas the game ends; otherwise the player picks Continue (10 piantas) or Quit.
    SET_VALUE(LW(1), 10)
    CALL(yuugijou_get_montemedal, LW(0))
    IF_INT_LESS(LW(0), LW(1))
        SET_VALUE(LW(0), 1)
    ELSE
        CALL(evt_msg_select, 0, STRING("sysyuu_03_00"))
    END_IF
    // Quitting sends Mario back through the pipe to gor_03.
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(GSWF(GSWF_YUU_MINIGAME_QUIT), 1)
        CALL(evt_mario_set_prev_party_pos, 0, 0, -1000, 0)
        CALL(evt_mario_set_prev_party_pos, 1, 0, -1000, 0)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT)
        CALL(evt_bero_mapchange, STRING("gor_03"), STRING("A_dokan_02"))
        RETURN
    END_IF
    // Continuing pays 10 piantas; the course fades out, Mario goes back to the start and the racers line up.
    MULTIPLY(LW(1), -1)
    CALL(yuugijou_add_montemedal, 0, LW(1))
    CALL(yuugijou_montemedal_wait)
    WAIT_MS(200)
    CALL(yuugijou_montemedal_disp_onoff, 0)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
    CALL(evt_snd_sfxoff, GW(10))
    CALL(evt_fade_out, 1000)
    CALL(evt_cam3d_evt_off, 0, 11)
    SET_VALUE(GF(0), 0)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL_CHILD(yuu_03_kaijo_init2)
    CALL(evt_cam_road_reset)
    CALL(yuu_03_cam_shift_reset)
    WAIT_MS(500)
    CALL(re_init_yuunpc)
    CALL(evt_snd_sfxon, STRING("SFX_EVT_GAME_AUDIENCE1"), GW(10))
    CALL(evt_fade_in, 1000)
    RETURN
#endif
EVT_END()

#if VERSION >= VERSION_US
/**
 * Map init for yuu_03 (Paper Mode room): starts the arrow, ball, grade and audience animations,
 * the minigame set- up and the NPC script, and (US and later) hides all
 * but the current game-language sign graphics.
 */
EVT_BEGIN(yuu_03_init_evt)
    CALL(evt_map_playanim, STRING("yajirushi"), 1, 0)
    CALL(evt_map_playanim, STRING("tama"), 1, 0)
    CALL(evt_map_playanim, STRING("gurade"), 1, 0)
    CALL(evt_map_playanim, STRING("kyaku"), 1, 0)
    SPAWN_EVENT(minigame04_main)
    CALL_CHILD(evt_yuunpc_minigame4)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("J_mon"), MAPOBJ_FLAG_DISABLE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("E_mon"), MAPOBJ_FLAG_DISABLE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("D_mon"), MAPOBJ_FLAG_DISABLE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("F_mon"), MAPOBJ_FLAG_DISABLE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("Sp_mon"), MAPOBJ_FLAG_DISABLE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("I_mon"), MAPOBJ_FLAG_DISABLE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("mon_10"), MAPOBJ_FLAG_DISABLE)
    CALL(evt_sub_get_language, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("J_mon"), MAPOBJ_FLAG_DISABLE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("mon_10"), MAPOBJ_FLAG_DISABLE)
        CASE_EQUAL(1)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("E_mon"), MAPOBJ_FLAG_DISABLE)
        CASE_EQUAL(2)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("D_mon"), MAPOBJ_FLAG_DISABLE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("mon_10"), MAPOBJ_FLAG_DISABLE)
        CASE_EQUAL(3)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("F_mon"), MAPOBJ_FLAG_DISABLE)
        CASE_EQUAL(4)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("Sp_mon"), MAPOBJ_FLAG_DISABLE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("mon_10"), MAPOBJ_FLAG_DISABLE)
        CASE_EQUAL(5)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("I_mon"), MAPOBJ_FLAG_DISABLE)
    END_SWITCH
    RETURN
EVT_END()
#else
/**
 * Map init for yuu_03 (Paper Mode room): starts the arrow, ball, grade and audience animations,
 * the minigame set- up and the NPC script, and (US and later) hides all
 * but the current game-language sign graphics.
 */
EVT_BEGIN(yuu_03_init_evt)
    CALL(evt_map_playanim, STRING("yajirushi"), 1, 0)
    CALL(evt_map_playanim, STRING("tama"), 1, 0)
    CALL(evt_map_playanim, STRING("gurade"), 1, 0)
    CALL(evt_map_playanim, STRING("kyaku"), 1, 0)
    SPAWN_EVENT(minigame04_main)
    CALL_CHILD(evt_yuunpc_minigame4)
    RETURN
EVT_END()
#endif

/**
 * Init callback for minigame 4: (JP and later) starts the marker icon event,
 * marks the opening cutscene as pending and allocates the wind particles.
 */
void yuuminigame_init_4slit(EventEntry* event, BOOL isFirstCall) {
    SlitWork* data = ((MiniGameWork*)event->lwData[0])->data;

#if VERSION >= VERSION_JP
    data->viewEvent = evtEntryType(yuu_03_icon_monte_entry_evt, 0, 0, 0);
    data->viewEvent->lwData[0] = event->lwData[0];
#endif
    data->flags |= 1;
    evt_ryushi_init(event, isFirstCall);
}

/**
 * Per-frame state machine for Paper Mode: phase 1 starts minigame04_start, phase 2 picks the first wind delay,
 * phases 2 and 3 run the rules check, phase 4 launches minigame04_end with the final counter
 * and a result code chosen from the coin total (special repeated-digit totals pay out more).
 * It also spins the "puro" and "pera" map objects (the course's turning bars) every frame.
 */
void yuuminigame_main_4slit(EventEntry* event, BOOL isFirstCall) {
    MiniGameWork* wp = (MiniGameWork*)event->lwData[0];
    SlitWork* data = wp->data;

    switch (data->phase) {
        case 0:
            break;
        case 5:
            data->phase = 1;
        case 1:
            wp->subEvent = evtEntry(minigame04_start, 0, 0);
            wp->subEvent->lwData[0] = event->lwData[0];
            data->phase++;
            break;
        case 2:
            data->state = 0;
            data->timer = (irand(3901) + 100) * 60 / 1000;
            data->result = 0;
            data->phase = 3;
        case 3:
            if (yuuminigame4_gamerule(event, isFirstCall, wp, data)) {
                data->phase++;
            }
            break;
        case 4:
            wp->subEvent = evtEntry(minigame04_end, 0, 0);
            wp->subEvent->lwData[0] = data->coins;
            switch (data->coins) {
                // Both early demos give other results for zero to two coins
#if VERSION <= VERSION_DEMO_JP
                case 0:
                    data->result = 0x2;
                    break;
                case 1:
                    data->result = 0x10A;
                    break;
                case 2:
                    data->result = 0x105;
                    break;
#else
                case 0:
                    data->result = 0x105;
                    break;
                case 1:
                    data->result = 0x103;
                    break;
                case 2:
                    data->result = 0x101;
                    break;
#endif
                case 10:
                case 21:
                case 32:
                case 43:
                case 54:
                case 65:
                case 76:
                case 87:
                case 98:
                case 110:
                case 221:
                case 332:
                case 443:
                case 554:
                case 665:
                case 776:
                case 887:
                case 998:
                case 1110:
                case 2221:
                case 3332:
                case 4443:
                case 5554:
                case 6665:
                case 7776:
                case 8887:
                case 9998:
                    data->result = 0x103;
                    break;
            }
            wp->subEvent->lwData[1] = data->result;
            data->phase++;
            break;
    }
    mapObjRotate("puro_1", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_2", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_3", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_4", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_5", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_6", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_7", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_8", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_9", 0.0f, 0.0f, data->rot1);
    mapObjRotate("puro_10", 0.0f, 0.0f, data->rot1);
    mapObjRotate("pera_1", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_2", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_3", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_4", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_5", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_6", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_7", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_8", 0.0f, 0.0f, data->rot2);
    mapObjRotate("pera_9", 0.0f, 0.0f, data->rot2);
}

/** Draw callback for minigame 4: draws the collected-coin counter (monteCountDisp). */
void yuuminigame_disp_4slit(CameraId camera, void* param) {
    monteCountDisp();
}

/**
 * Per-frame rules of Paper Mode: runs the wind state machine (idle, gust building up, full gust, fading,
 * in one of two directions with random delays), turns the puro/pera bars to match,
 * pushes Mario along with the wind unless he is squeezed through a slit in paper form,
 * and returns TRUE once he falls off (counter forced to 701) or reaches x >= 1500.
 */
BOOL yuuminigame4_gamerule(EventEntry* event, BOOL isFirstCall, MiniGameWork* wp, SlitWork* data) {
    MarioWork* mario = marioGetPtr();
    EventEntry* ev;
    f32 speed;

    data->timer--;
    switch (data->state) {
        case 0:
            if (data->timer == 0) {
                if (irand(2)) {
                    data->state = 1;
                    ev = evtEntryType(ryushi_event, 0, 0, 0);
                    ev->lwData[0] = (EvtWord)wp;
                    ev->lwData[1] = 1;
                } else {
                    data->state = 5;
                    ev = evtEntryType(ryushi_event, 0, 0, 0);
                    ev->lwData[0] = (EvtWord)wp;
                    ev->lwData[1] = 0;
                }
                data->timer = 60;
            }
            break;
        case 1:
            if (data->timer == 0) {
                data->state = 2;
                data->timer = 60;
            }
        case 2:
            if (data->timer == 0) {
                data->state = 3;
                data->timer = (irand(2001) + 3000) * 60 / 1000;
            }
            break;
        case 3:
            if (data->timer == 0) {
                data->state = 4;
                data->timer = 48;
            }
            break;
        case 4:
            if (data->timer == 0) {
                data->state = 0;
                data->timer = (irand(3901) + 100) * 60 / 1000;
                evtSetValue(event, GW(0), 1);
            }
            break;
        case 5:
            if (data->timer == 0) {
                data->state = 6;
                data->timer = 60;
            }
            break;
        case 6:
            if (data->timer == 0) {
                data->state = 7;
                data->timer = (irand(2001) + 3000) * 60 / 1000;
            }
            break;
        case 7:
            if (data->timer == 0) {
                data->state = 8;
                data->timer = 48;
            }
            break;
        case 8:
            if (data->timer == 0) {
                data->state = 0;
                data->timer = (irand(3901) + 100) * 60 / 1000;
                evtSetValue(event, GW(0), 1);
            }
            break;
    }
    switch (data->state) {
        case 0:
            break;
        case 1:
        case 2:
            data->rot1 += 36.0f * (120.0f - (data->timer - 1)) / 120.0f;
            data->rot1 = REVISE360(data->rot1);
            break;
        case 3:
            data->rot1 += 36.0f;
            data->rot1 = REVISE360(data->rot1);
            break;
        case 4:
            data->rot1 += 36.0f * (data->timer - 1) / 48.0f;
            data->rot1 = REVISE360(data->rot1);
            break;
        case 5:
        case 6:
            data->rot2 += 36.0f * (120.0f - (data->timer - 1)) / 120.0f;
            data->rot2 = REVISE360(data->rot2);
            break;
        case 7:
            data->rot2 += 36.0f;
            data->rot2 = REVISE360(data->rot2);
            break;
        case 8:
            data->rot2 += 36.0f * (data->timer - 1) / 48.0f;
            data->rot2 = REVISE360(data->rot2);
            break;
    }
    if (mario->position.x < 1500.0f) {
        speed = 0.0f;
        switch (data->state) {
            case 2:
            case 3:
            case 4:
                if (mario->dispFlags & MARIO_DISP_FLAG_SLIT) {
                    if (mario->flags & MARIO_FLAG_PAPER_MODE) {
                        speed = 0.0f;
                    } else {
#if VERSION <= VERSION_DEMO_JP
                        speed = 1.6666666f;
#else
                        speed = 0.0f;
#endif
                    }
                } else {
#if VERSION <= VERSION_DEMO_JP
                    speed = 3.3333333f;
#else
                    speed = 2.9166667f;
#endif
                }
                break;
            case 6:
            case 7:
            case 8:
                if (mario->dispFlags & MARIO_DISP_FLAG_SLIT) {
                    if (mario->flags & MARIO_FLAG_PAPER_MODE) {
                        speed = -0.0f;
                    } else {
#if VERSION <= VERSION_DEMO_JP
                        speed = -1.6666666f;
#else
                        speed = -0.0f;
#endif
                    }
                } else {
#if VERSION <= VERSION_DEMO_JP
                    speed = -3.3333333f;
#else
                    speed = -2.9166667f;
#endif
                }
                break;
        }
        switch (data->state) {
            case 2:
            case 6:
                speed = speed * (60 - data->timer) / 60.0f;
                break;
        }
        mario->floorMove.z += speed;
    }
    if (mario->position.y <= -100.0f || mario->position.x >= 1500.0f) {
        if (mario->position.y <= -100.0f) {
            data->coins = 701;
            yuucounter_flag_on(1);
        } else {
            data->coins = yuucounter_get_data();
        }
        data->state = 0;
        data->timer = (irand(3901) + 100) * 60 / 1000;
        marioKeyOff();
        partyKeyOff();
        yuucounter_flag_on(2);
        return TRUE;
    }
    return FALSE;
}
