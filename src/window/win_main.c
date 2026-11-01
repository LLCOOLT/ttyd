// Pause menu: opening and closing the menu, item use from the menu, and the shared text and texture helpers.
#include "win/win_main.h"
#include "eff/eff_recovery.h"
#include "data/item_data.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/seqdrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/fontmgr.h"
#include "mario/mario.h"
#include "memory.h"
#include "party.h"
#include "system.h"
#include <dolphin/pad.h>
#include <demo/DEMOPad.h>
#include <string.h>
#include <stdarg.h>
#include "evt/evt_yuugijou.h"
#include "libc_decls.h"
#include "evt/evt_eff.h"
#include "evt/evt_env.h"
#include "evt/evt_fade.h"
#include "evt/evt_item.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_party.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "koopa.h"
#include "party/party_motion.h"
#include "win/win_log.h"
#include "version.h"
#include "evt/evt_story.h"
#include "win/win_root.h"
#if VERSION >= VERSION_US
#endif
#include "driver/msgdrv.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "win/win_party.h"
// FAKE: win_main.c calls pouchSetHP through this prototype (the types it was compiled with) instead of the one in mario/mario_pouch.h; same registers, behaviour-identical.
typedef void (*PouchSetHPS32Fn)(s32);
// FAKE: win_main.c calls pouchSetFP through this prototype (the types it was compiled with) instead of the one in mario/mario_pouch.h; same registers, behaviour-identical.
typedef void (*PouchSetFPS32Fn)(s32);
// FAKE: win_main.c calls pouchSetAP through this prototype (the types it was compiled with) instead of the one in mario/mario_pouch.h; same registers, behaviour-identical.
typedef void (*PouchSetAPS32Fn)(s32);

// FAKE: the 0.5f that winTexSet and friends load is a named .sdata2 constant defined after winLectureCheck
// (winConstHalf below); with a plain 0.5f literal the .sdata2 constants come out in a different
// order (winTexSet, winIconSet, winMain and others then differ).
#define HALF_F winConstHalf
static USER_FUNC(cam_r);
// Badge tutorial helper: lets the player's input through again (defined below).
USER_FUNC(lecture_key_mask_off);
static USER_FUNC(wait);
// Item-use helper: turns off the partners' forced slit (defined below).
USER_FUNC(all_party_slit_off);
static USER_FUNC(party_color);
static USER_FUNC(famicom_check);
static USER_FUNC(itemUseFunc2);
EvtWord evt_lecture_msg[];
EvtWord evt_item_use[];
EvtWord evt_diary_read[];

//.data

//.sbss
// itemUseFunc's step counter. The demo map has it as a static local (cnt$730), but as one it would be emitted
// first in .sbss instead of after wp and winTexTpl, so it stays at file scope.
static s32 cnt;
TEXPalette* winTexTpl;
static WindowWork* wp;

// local prototypes
#include "driver/fadedrv.h"
#include "driver/mobjdrv.h"
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "driver/swdrv.h"
#include "driver/effdrv.h"
#include "manager/filemgr.h"
#include "mario/mario_party.h"
#include "pmario_sound.h"
#include "statuswindow.h"
#include "icon_ids.h"
#include "data/party_data.h"
#include "manager/evtmgr_cmd.h"
static void winLectureKeyMask(void);
// FAKE: the prototype this file was compiled with (u16 icon id; icondrv.h has s16/s32), so callers zero-extend the id
void iconGetTexObj(GXTexObj* obj, u16 iconId);
static void winDisp(CameraId camId, void* param);
static void winDispKoopa(CameraId camId, void* param);

/** Returns the pause menu's work area (shared by every menu tab). */
WindowWork* winGetPtr(void) {
    return wp;
}

/** Allocates and clears the pause menu work at game start (from mariost.c). */
void winInit(void) {
    wp = __memAlloc(HEAP_DEFAULT, sizeof(WindowWork));
    memset(wp, 0, sizeof(WindowWork));
}

/** Clears the pause menu work again; run on map change and on game over. */
void winReInit(void) {
    memset(wp, 0, sizeof(WindowWork));
}

/**
 * TRUE while the pause menu is open (menuState 1..199) outside the badge tutorial.
 * The main loop and casedrv use it to hold off field logic while the menu is up.
 */
BOOL winCheck(void) {
    s32 state;

    if (wp == NULL) {
        return FALSE;
    }

    if (wp->flags & WIN_FLAG_LECTURE) {
        return FALSE;
    }

    state = wp->menuState;
    if (state != 0 && state < 200) {
        return TRUE;
    }
    return FALSE;
}

/** Allows the pause menu to be opened again (clears WIN_FLAG_OPEN_DISABLED); called from the evt_window script helpers. */
void winOpenEnable(void) {
    if (wp) {
        wp->flags &= ~WIN_FLAG_OPEN_DISABLED;
    }
}

/** Blocks the pause menu from opening or running (sets WIN_FLAG_OPEN_DISABLED, which winMain checks first). */
void winOpenDisable(void) {
    if (wp) {
        wp->flags |= WIN_FLAG_OPEN_DISABLED;
    }
}

#if VERSION >= VERSION_US
typedef struct {
    const char* s[6];
} WinLangTbl;
#else
typedef struct {
    const char* s[2];
} WinLangTbl;
#endif
static const WinLangTbl winLangTbl;

/**
 * Per-frame pause menu driver.
 * In the field it reads the pad, opens the menu on Start
 * or a D-pad shortcut (Party, Items, Badges, Journal tabs), freezes Mario and partners, loads win.tpl,
 * runs winRootMain, and on close restores control.
 * It also starts the item-use and Ragged Diary scenes, swaps partners, and opens the Pianta Parlor window.
 */
void winMain(void) {
    MarioWork* mario;
    s32 i;
#if VERSION >= VERSION_DEMO_EU
    WindowPartyDt* list[7];
#endif

    mario = marioGetPtr();
    if (!(wp->flags & WIN_FLAG_OPEN_DISABLED) && seqGetSeq() == SEQ_GAME && !seqCheckSeq()) {
        wp->buttonTrg = keyGetButtonTrg(0);
        wp->buttonRep = keyGetButtonRep(0);
        wp->dirTrg = keyGetDirTrg(0);
        wp->dirRep = keyGetDirRep(0);

        if (keyGetButtonTrg(0) & PAD_BUTTON_LEFT) {
            wp->dirTrg |= DEMO_STICK_LEFT;
        }
        if (keyGetButtonTrg(0) & PAD_BUTTON_RIGHT) {
            wp->dirTrg |= DEMO_STICK_RIGHT;
        }
        if (keyGetButtonTrg(0) & PAD_BUTTON_UP) {
            wp->dirTrg |= DEMO_STICK_UP;
        }
        if (keyGetButtonTrg(0) & PAD_BUTTON_DOWN) {
            wp->dirTrg |= DEMO_STICK_DOWN;
        }

        if (keyGetButtonRep(0) & PAD_BUTTON_LEFT) {
            wp->dirRep |= DEMO_STICK_LEFT;
        }
        if (keyGetButtonRep(0) & PAD_BUTTON_RIGHT) {
            wp->dirRep |= DEMO_STICK_RIGHT;
        }
        if (keyGetButtonRep(0) & PAD_BUTTON_UP) {
            wp->dirRep |= DEMO_STICK_UP;
        }
        if (keyGetButtonRep(0) & PAD_BUTTON_DOWN) {
            wp->dirRep |= DEMO_STICK_DOWN;
        }

        winLectureKeyMask();

        switch (wp->menuState) {
            case 0:
                if (!(wp->flags & WIN_FLAG_LECTURE)) {
                    if (marioStGetSystemLevel() != 0U) {
                        break;
                    }
                    if (marioCheckMenuDisable()) {
                        break;
                    }
                    if (mobjCheckExec()) {
                        break;
                    }
                    if (!fadeIsFinish()) {
                        break;
                    }
                    if (mario->characterId == 2) {
                        if (!(wp->buttonTrg & PAD_BUTTON_START)) {
                            break;
                        }
                        wp->menuSel = 0;
                    } else if (wp->buttonTrg & PAD_BUTTON_START) {
                        wp->menuSel = 0;
                    } else {
                        if (keyGetButton(0) & PAD_TRIGGER_Z) {
                            break;
                        }
#if VERSION >= VERSION_JP
                        if (strcmp(gp->currentAreaName, "yuu") == 0) {
                            break;
                        }
#endif
                        if ((wp->buttonTrg & PAD_BUTTON_LEFT) && (swByteGet(GSW_STORY_PROGRESS) >= STORY_STG0_07_GOOMBELLA_JOINS || partyChkJoin(1))) {
                            wp->menuSel = 1;
                        } else if (wp->buttonTrg & PAD_BUTTON_UP) {
                            wp->menuSel = 2;
                        } else if ((wp->buttonTrg & PAD_BUTTON_RIGHT) && (swByteGet(GSW_STORY_PROGRESS) >= STORY_STG0_17_BADGE_TUTORIAL || pouchGetHaveBadgeCnt())) {
                            wp->menuSel = 3;
                        } else if (wp->buttonTrg & PAD_BUTTON_DOWN) {
                            wp->menuSel = 4;
                        } else {
                            break;
                        }
                    }
                    if (keyGetButton(0) & PAD_TRIGGER_L) {
                        break;
                    }
#if VERSION >= VERSION_US
                    if ((gp->flags & GLOBAL_FLAG_KIOSK) && evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG0_07_GOOMBELLA_JOINS) {
                        break;
                    }
#endif
                }
#if VERSION >= VERSION_JP
                else {
                    wp->menuSel = 0;
                }
#endif
                camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
                if (gp->flags & GLOBAL_FLAG_KIOSK) {
                    wp->menuSel = 1;
                }
                if (!(wp->flags & WIN_FLAG_LECTURE)) {
                    marioStSystemLevel(4);
                } else {
                    npcStopForEvent();
                }
                fbatChangeMode(7);
#if VERSION <= VERSION_DEMO_JP
                marioCtrlOff2();
#else
                if (mario->characterId == 2) {
                    if (!kpaGetStageViewType()) {
                        marioCtrlOff();
                    } else {
                        marioCtrlOff2();
                    }
                } else {
                    marioCtrlOff2();
                }
#endif
                partyCtrlOff();
                psndSetFlag(PSND_FLAG_MUTE_SFX);
                if (mario->characterId == 2) {
                    kpaPauseSE2();
                }
                if (mario->flags & MARIO_FLAG_IS_8_BIT) {
                    wp->flags |= WIN_FLAG_8BIT_MARIO;
                } else {
                    wp->flags &= ~WIN_FLAG_8BIT_MARIO;
                }
                for (i = 0; i < 4; i++) {
                    padRumbleHardOff(i);
                }
#if VERSION >= VERSION_US
                fileAsyncf(4, 0, WIN_DIR "%s/mail.tpl", getMarioStDvdRoot(), (u32)gp->language == 0 ? "jp" : "us");
#else
                fileAsyncf(4, 0, WIN_DIR "jp/mail.tpl", getMarioStDvdRoot());
#endif
                {
#if VERSION >= VERSION_US
                    fileAsyncf(4, 0, WIN_DIR "%s/%s", getMarioStDvdRoot(), (u32)gp->language == 0 ? "jp" : "us", winGetMapTplName());
#else
                    const char* name = winGetMapTplName();
                    fileAsyncf(4, 0, WIN_DIR "jp/%s", getMarioStDvdRoot(), name);
#endif
                }
                wp->active = 0;
                if (strncmp(gp->currentMapName, "yuu_", 4) == 0) {
                    wp->menuState = 400;
                } else {
                    wp->menuState++;
                }
                break;

            case 1: {
                WinLangTbl lang = winLangTbl;
                BOOL ok;

                if (fileAsyncf(4, 0, WIN_DIR "%s/win.tpl", getMarioStDvdRoot(), lang.s[gp->language]) == NULL) {
                    ok = FALSE;
                } else {
                    wp->res = fileAllocf(4, WIN_DIR "%s/win.tpl", getMarioStDvdRoot(), lang.s[gp->language]);
                    ok = TRUE;
                }
                if (ok) {
                    wp->menuState++;
                }
                break;
            }

            case 2:
                if (!marioGetPtr()->characterId) {
                    switch (winRootMain(wp)) {
                        case -1:
                            wp->menuState++;
                            break;
                        case -2:
                            wp->menuState = 100;
                            break;
                        case -3:
                            if (wp->item.useItem == ITEM_RAGGED_DIARY) {
                                wp->menuState = 300;
                            } else {
                                wp->menuState = 200;
                            }
                            break;
                    }
                } else if (wp->buttonTrg & PAD_BUTTON_START) {
                    kpaPauseSE2();
                    wp->menuState = 3;
                }
                break;

            case 3:
                camGetPtr(CAMERA_2D)->flags &= ~CAM_FLAG_LETTER_BOX_DISABLE;
#if VERSION <= VERSION_DEMO_JP
                marioCtrlOn2();
#else
                if (mario->characterId == 2) {
                    if (!kpaGetStageViewType()) {
                        marioCtrlOn();
                    } else {
                        marioCtrlOn2();
                    }
                } else {
                    marioCtrlOn2();
                }
#endif
                partyCtrlOn();
                fbatChangeMode(1);
                psndClearFlag(PSND_FLAG_MUTE_SFX);
                statusWinForceUpdate();
                if (!(wp->flags & WIN_FLAG_LECTURE)) {
                    marioStSystemLevel(0);
                } else {
                    npcStartForEvent();
                }
                if (wp->res) {
                    fileFree(wp->res);
                }
                wp->res = NULL;
                wp->flags = 0;
                wp->menuState = 0;
                break;

            case 100:
                if (marioBgmodeChk()) {
                    MarioWork* m = marioGetPtr();
                    m->prevPartyMemberId[0] = wp->party.partyIds[wp->party.cursor];
                    wp->menuState = 3;
                } else if (animGroupBaseAsync(partyDataTbl[wp->party.partyIds[wp->party.cursor]].name, 2, 0)) {
                    wp->menuState++;
                }
                break;

            case 101:
                marioPartyGoodbye();
                wp->menuState++;
                break;

            case 102:
                if (!marioGetParty()) {
                    marioPartyHello(wp->party.partyIds[wp->party.cursor]);
                    wp->menuState = 3;
                }
                break;

            case 200: {
#if VERSION >= VERSION_DEMO_EU
                s32 partyId;
                s32 n;

                partyId = !marioBgmodeChk() ? marioGetParty() : marioGetPtr()->prevPartyMemberId[0];
                n = 0;
                for (i = 0; i < 7; i++) {
                    if (partyId == winPartyDt[i].partyId) {
                        list[n++] = &winPartyDt[i];
                    }
                }
                // PAL lists only the other partners that have joined (flag 1) and are not away (flag 2)
                for (i = 0; i < 7; i++) {
                    if (partyId != winPartyDt[i].partyId && (pouchGetPtr()->partyData[winPartyDt[i].partyId].flags & POUCH_PARTY_FLAG_JOINED) &&
                        !(pouchGetPtr()->partyData[winPartyDt[i].partyId].flags & POUCH_PARTY_FLAG_AWAY)) {
                        list[n++] = &winPartyDt[i];
                    }
                }
#else
#if VERSION >= VERSION_US
                WindowPartyDt* list[11]; /* FAKE */ // US frame is 96 bytes; only 7 entries used
#else
                WindowPartyDt* list[7];
#endif
                WindowPartyDt* p;
                WindowPartyDt* base;
                s32 partyId;
                s32 n;

                partyId = !marioBgmodeChk() ? marioGetParty() : marioGetPtr()->prevPartyMemberId[0];
                base = winPartyDt;
                n = 0;
                for (i = 0, p = base; i < 7; i++, p++) {
                    if (partyId == p->partyId) {
                        list[n++] = p;
                    }
                }
                for (i = 0; i < 7; i++, base++) {
                    if (partyId != base->partyId) {
                        list[n++] = base;
                    }
                }
#endif
                wp->currentEvent = evtEntryType(evt_item_use, 0, 0, 0);
                wp->currentEvent->lwData[10] = wp->item.useItem;
                wp->currentEvent->lwData[11] = wp->item.useTarget == 0 ? 0 : list[wp->item.useTarget - 1]->partyId;
                psndClearFlag(PSND_FLAG_MUTE_SFX);
                wp->menuState++;
                pouchRemoveItemIndex(wp->item.useItem, wp->item.useIdx);
                break;
            }

            case 201:
                if (!evtCheckID(wp->currentEvent->eventId)) {
                    wp->menuState = 3;
                }
                break;

            case 300:
                wp->currentEvent = evtEntryType(evt_diary_read, 0, 0, 0);
                wp->menuState++;
                break;

            case 301:
                if (!evtCheckID(wp->currentEvent->eventId)) {
                    wp->menuState = 3;
                }
                break;

            case 400:
                evtYuuWindow();
                wp->menuState++;
                break;

            case 401:
                if (evtYuuWindowEndChk()) {
                    wp->menuState = 3;
                }
                break;
        }

        if (wp->menuState == 2) {
            switch (marioGetPtr()->characterId) {
                case 0:
                    if (!(wp->flags & WIN_FLAG_LECTURE)) {
                        dispEntry(CAMERA_2D, 250.0f, 0, winDisp, NULL);
                    } else {
                        dispEntry(CAMERA_2D, 500.0f, 0, winDisp, NULL);
                    }
                    break;
                case 2:
                    dispEntry(CAMERA_2D, 250.0f, 0, winDispKoopa, NULL);
                    break;
            }
        }
    }
}

/** 2D draw callback for Mario's pause menu: draws all the menu windows through winRootDisp. */
static void winDisp(CameraId camId, void* param) {
    winRootDisp(camId, wp);
}

/** 2D draw callback used while playing as Bowser: his pause screen is just one texture (0xB7) from win.tpl. */
static void winDispKoopa(CameraId camId, void* param) {
    winTexInit(*wp->res->data);
    winTexSet(0xB7, (Vec){0.0f, 50.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
}

#if VERSION >= VERSION_US
/**
 * Language folders of the menu graphics (win.tpl), indexed by the game language;
 * the menu loads its textures from them.
 */
static const WinLangTbl winLangTbl = {{"jp", "us", "ge", "fr", "sp", "it"}};
#else
/** Language folders of the menu graphics (win.tpl), indexed by the game language: Japanese and English. */
static const WinLangTbl winLangTbl = {{"jp", "us"}};
#endif

/**
 * Puts the current partner into its item-receiving pose (the *_I_1 animations)
 * when an item is used on them from the menu.
 * The JP and later releases skip it while Koops reports a nonzero nokonokoGetStatus.
 */
EVT_BEGIN(kime_pose)
#if VERSION >= VERSION_JP
    CALL(evt_party_nokotaro_get_status, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
#endif
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_party_set_pose, 0, STRING("PKR_I_1"))
        CASE_EQUAL(2)
        CALL(evt_party_set_pose, 0, STRING("PNK_I_1"))
        CASE_EQUAL(3)
        CALL(evt_party_set_pose, 0, STRING("I_1"))
        CASE_EQUAL(4)
        CALL(evt_party_set_pose, 0, STRING("PYS_I_1"))
        CASE_EQUAL(5)
        CALL(evt_party_set_pose, 0, STRING("PWD_I_1"))
        CASE_EQUAL(6)
        CALL(evt_party_set_pose, 0, STRING("PTR_I_1"))
        CASE_EQUAL(7)
        CALL(evt_party_set_pose, 0, STRING("PCH_I_1"))
    END_SWITCH
    RETURN
EVT_END()

/** Puts the current partner into its happy pose (the *_Y_1 animations) as the used item's recovery takes effect. */
EVT_BEGIN(kime_pose2)
#if VERSION >= VERSION_JP
    CALL(evt_party_nokotaro_get_status, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
#endif
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_party_set_pose, 0, STRING("PKR_Y_1"))
        CASE_EQUAL(2)
        CALL(evt_party_set_pose, 0, STRING("PNK_Y_1"))
        CASE_EQUAL(3)
        CALL(evt_party_set_pose, 0, STRING("Y_1"))
        CASE_EQUAL(4)
        CALL(evt_party_set_pose, 0, STRING("PYS_Y_1"))
        CASE_EQUAL(5)
        CALL(evt_party_set_pose, 0, STRING("PWD_Y_1"))
        CASE_EQUAL(6)
        CALL(evt_party_set_pose, 0, STRING("PTR_Y_1"))
        CASE_EQUAL(7)
        CALL(evt_party_set_pose, 0, STRING("PCH_Y_1"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * Returns the current partner to its normal standing pose
 * after item use (JP on: skipped while Koops reports a nonzero nokonokoGetStatus).
 */
#if VERSION >= VERSION_JP
EVT_BEGIN(win_main_child_evt)
    CALL(evt_party_nokotaro_get_status, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
    CALL(evt_party_set_breed_pose, 0, 1)
    RETURN
EVT_END()
#endif

/**
 * The 8-bit (Famicom-style) version of the partner item poses, used while Mario is in his 8-bit form;
 * Yoshi's pose depends on his color (party_color).
 */
EVT_BEGIN(kime_pose_famicom)
#if VERSION >= VERSION_JP
    CALL(evt_party_nokotaro_get_status, 0, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        RETURN
    END_IF
#endif
    CALL(evt_mario_get_party, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        CASE_EQUAL(1)
        CALL(evt_party_set_pose, 0, STRING("R_2"))
        CASE_EQUAL(2)
        CALL(evt_party_set_pose, 0, STRING("R_3"))
        CASE_EQUAL(3)
        CALL(evt_party_set_pose, 0, STRING("R_13"))
        CASE_EQUAL(4)
        CALL(party_color, LW(0))
        SWITCH(LW(0))
            CASE_EQUAL(0)
            CALL(evt_party_set_pose, 0, STRING("R_5"))
            CASE_EQUAL(1)
            CALL(evt_party_set_pose, 0, STRING("R_6"))
            CASE_EQUAL(2)
            CALL(evt_party_set_pose, 0, STRING("R_7"))
            CASE_EQUAL(3)
            CALL(evt_party_set_pose, 0, STRING("R_8"))
            CASE_EQUAL(4)
            CALL(evt_party_set_pose, 0, STRING("R_9"))
            CASE_EQUAL(5)
            CALL(evt_party_set_pose, 0, STRING("R_10"))
            CASE_EQUAL(6)
            CALL(evt_party_set_pose, 0, STRING("R_11"))
        END_SWITCH
        CASE_EQUAL(5)
        CALL(evt_party_set_pose, 0, STRING("R_4"))
        CASE_EQUAL(6)
        CALL(evt_party_set_pose, 0, STRING("R_12"))
        CASE_EQUAL(7)
        CALL(evt_party_set_pose, 0, STRING("R_15"))
    END_SWITCH
    RETURN
EVT_END()

/**
 * Field scene for using a recovery item from the Items menu:
 * LW(10) is the item, LW(11) the target partner (0 for Mario).
 * The item floats above the user with a sparkle and sound,
 * then itemUseFunc applies HP/FP/SP and shows the recovery numbers. Started by winMain (menuState 200).
 */
EVT_BEGIN(evt_item_use)
    SET_TYPE(0)
    CALL(evt_mario_normalize)
#if VERSION <= VERSION_DEMO_JP
    WAIT_FRAMES(1)
    CALL(evt_mario_adjust_dir)
#else
    CALL(all_party_slit_off)
    WAIT_FRAMES(1)
    CALL(evt_mario_adjust_dir)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL_CHILD(win_main_child_evt)
#endif
    IF_INT_EQUAL(LW(11), 0)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(1), 50)
        CALL(evt_item_entry, STRING("menu_dummy"), LW(10), LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
        ADD(LW(1), 10)
        CALL(evt_eff, 0, STRING("itemget"), 10, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_MARIO_USE1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_mario_set_pose, STRING("M_I_1"))
        WAIT_MS(1000)
        CALL(evt_item_delete, STRING("menu_dummy"))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_RECOVERY_SHINE1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff64, 0, STRING("stardust2_n64"), 4, LW(0), LW(1), LW(2), 40, 40, 30, 120, 0, 0, 0, 0)
        WAIT_MS(1400)
        CALL(evt_mario_set_pose, STRING("M_V_2"))
        CALL(itemUseFunc)
        WAIT_MS(1500)
        CALL(itemUseFunc2)
        CALL(evt_mario_set_normal_pose)
        RETURN
    END_IF
    CALL(evt_mario_get_party, LW(0))
    IF_INT_EQUAL(LW(0), LW(11))
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        ADD(LW(1), 50)
        CALL(evt_item_entry, STRING("menu_dummy"), LW(10), LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
        ADD(LW(1), 10)
        CALL(evt_eff, 0, STRING("itemget"), 10, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_MARIO_USE1"), LW(0), LW(1), LW(2), 0)
        CALL(famicom_check, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL_CHILD(kime_pose)
        ELSE
            CALL_CHILD(kime_pose_famicom)
        END_IF
        WAIT_MS(1000)
        CALL(evt_item_delete, STRING("menu_dummy"))
        CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_ITEM_RECOVERY_SHINE1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff64, 0, STRING("stardust2_n64"), 4, LW(0), LW(1), LW(2), 40, 40, 30, 120, 0, 0, 0, 0)
        WAIT_MS(1400)
        CALL(famicom_check, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            CALL_CHILD(kime_pose2)
        ELSE
            CALL_CHILD(kime_pose_famicom)
        END_IF
        CALL(itemUseFunc)
        WAIT_MS(1500)
        CALL(itemUseFunc2)
#if VERSION <= VERSION_DEMO_JP
        CALL(evt_party_set_breed_pose, 0, 1)
#else
        CALL_CHILD(win_main_child_evt)
        CALL(evt_mario_set_normal_pose)
#endif
        RETURN
    END_IF
    RETURN
EVT_END()

/**
 * Reading the Ragged Diary (chapter 6, Excess Express) from Important Items.
 * After three yes/no prompts a ghost appears, the camera rolls and the game goes to the Game Over screen.
 * Started by winMain (menuState 300).
 */
EVT_BEGIN(evt_diary_read)
    SET_TYPE(0)
    // "Read the diary?" Saying no ends it here.
    CALL(evt_party_cont_onoff, 0, 1)
    WAIT_FRAMES(1)
    CALL(evt_mario_normalize)
    CALL(evt_msg_print, 0, STRING("stg6_rsh_diary_01"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg6_rsh_diary_01_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_continue)
        CALL(evt_party_cont_onoff, 0, 0)
        RETURN
    END_IF
    // "You may be cursed by the ghost!" Saying no ends it here.
    CALL(evt_msg_print_add, 0, STRING("stg6_rsh_diary_02"))
    CALL(evt_msg_select, 0, STRING("stg6_rsh_diary_01_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_continue)
        CALL(evt_party_cont_onoff, 0, 0)
        RETURN
    END_IF
    // "This could be really, REALLY bad." Saying no ends it here.
    CALL(evt_msg_print_add, 0, STRING("stg6_rsh_diary_03"))
    CALL(evt_msg_select, 0, STRING("stg6_rsh_diary_01_yn"))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_continue)
        CALL(evt_party_cont_onoff, 0, 0)
        RETURN
    END_IF
    CALL(evt_msg_continue)
    // The music fades and Mario reads the first lines of the diary.
    CALL(evt_snd_bgmoff_f, PSND_FADE_OUT, 2000)
#if VERSION >= VERSION_JP
    CALL(evt_mario_dispflag_onoff, 1, 2)
#endif
    CALL(evt_mario_adjust_dir)
    CALL(evt_mario_set_pose, STRING("M_L_2"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_diary_04"), 0, 0)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    // The ghost is brought in (once) and starts pulsing between faint and solid.
    CALL(evt_npc_check, STRING("ゆうれい"), LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_npc_entry, STRING("ゆうれい"), STRING("c_ghost_k"))
        CALL(evt_npc_set_position, STRING("ゆうれい"), 0, -1000, 0)
        CALL(evt_npc_set_tribe, STRING("ゆうれい"), STRING("ゆうれい"))
        CALL(evt_npc_set_anim, STRING("ゆうれい"), STRING("O_1"))
        CALL(evt_npc_set_autotalkpose, STRING("ゆうれい"), STRING("O_2"), STRING("T_2"))
    END_IF
    CALL(evt_npc_flag_onoff, 1, STRING("ゆうれい"), NPC_FLAG_NO_SHADOW | NPC_FLAG_INTANGIBLE)
    BEGIN_INLINE_EVENT
        LOOP(0)
            CALL(evt_sub_intpl_msec_init, 11, 180, 64, 1000)
            LABEL(1)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_npc_set_color, STRING("ゆうれい"), 255, 255, 255, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(1)
            END_IF
            CALL(evt_sub_intpl_msec_init, 11, 64, 180, 1000)
            LABEL(2)
            CALL(evt_sub_intpl_msec_get_value)
            CALL(evt_npc_set_color, STRING("ゆうれい"), 255, 255, 255, LW(0))
            WAIT_FRAMES(1)
            IF_INT_EQUAL(LW(1), 1)
                GOTO(2)
            END_IF
        END_LOOP
    END_INLINE_EVENT
    // The ghost music plays and the ghost appears right behind Mario: "YOU LOOKED!"
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_EVT_STG5_GHOST1"))
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    ADD(LW(1), 20)
    ADD(LW(2), 20)
    CALL(evt_npc_set_position, STRING("ゆうれい"), LW(0), LW(1), LW(2))
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_GHOST_APPEAR1"), LW(0), LW(1), LW(2), 0)
#else
    CALL(evt_snd_sfxon_3d, 132773, LW(0), LW(1), LW(2), 0)
#endif
    WAIT_MS(200)
    CALL(evt_mario_set_pose, STRING("M_I_O"))
    CALL(evt_msg_print, 0, STRING("stg6_rsh_diary_05"), 0, STRING("ゆうれい"))
    WAIT_MS(300)
    // Silence, then the screen blurs with a shaking sound and the camera rolls.
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
    BEGIN_INLINE_EVENT
        CALL(evt_env_blur_on, 0, 0)
    END_INLINE_EVENT
#if VERSION <= VERSION_DEMO_JP
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG6_GHOST_SHAKE1"), LW(0), LW(1), LW(2), LW(3))
#else
    CALL(evt_snd_sfxon, 132770, LW(3))
#endif
    BEGIN_INLINE_EVENT
        CALL(cam_r)
    END_INLINE_EVENT
    // Four seconds later: Game Over.
    WAIT_MS(4000)
    CALL(evt_fade_set_mapchange_type, 1, -1, 600, -1, -1)
    CALL(evt_seq_set_seq, SEQ_GAME_OVER, 0, 0)
    RETURN
EVT_END()

/**
 * The badge tutorial's text (lecture_badge_00..07) shown over the pause menu;
 * each wait step blocks until the player has made the input winLectureKeyMask allows for that step.
 * Started by winLectureOn.
 */
EVT_BEGIN(evt_lecture_msg)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("lecture_badge_00"), 0, 0)
    CALL(wait, 1)
    CALL(evt_msg_continue)
    CALL(evt_msg_print, 0, STRING("lecture_badge_01"), 0, 0)
    CALL(wait, 2)
    CALL(evt_msg_continue)
    CALL(evt_msg_print, 0, STRING("lecture_badge_02"), 0, 0)
#if VERSION >= VERSION_US
    WAIT_MS(500)
    CALL(wait, 3)
    WAIT_MS(500)
    CALL(wait, 4)
    WAIT_MS(500)
#endif
    CALL(wait, 5)
#if VERSION >= VERSION_US
    WAIT_MS(500)
#endif
    CALL(evt_msg_continue)
    CALL(evt_msg_print, 0, STRING("lecture_badge_03"), 0, 0)
    CALL(wait, 6)
    CALL(evt_msg_continue)
    CALL(evt_msg_print, 0, STRING("lecture_badge_04"), 0, 0)
    CALL(wait, 7)
    CALL(evt_msg_continue)
    CALL(evt_msg_print, 0, STRING("lecture_badge_05"), 0, 0)
    CALL(wait, 8)
    CALL(evt_msg_continue)
    CALL(evt_msg_print, 0, STRING("lecture_badge_06"), 0, 0)
    CALL(wait, 9)
    CALL(evt_msg_continue)
    CALL(evt_msg_print, 0, STRING("lecture_badge_07"), 0, 0)
    CALL(wait, 10)
    CALL(evt_msg_continue)
#if VERSION >= VERSION_US
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG0_17_BADGE_TUTORIAL)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
#endif
    WAIT_MS(500)
#if VERSION >= VERSION_JP
    CALL(lecture_key_mask_off)
#endif
    RETURN
#if VERSION == VERSION_DEMO_US || VERSION >= VERSION_US
    OPCODE_END_SCRIPT,
    // the June US demo and the US code line (US, PAL, the September demos): a trailing zero word in the object (the
    // JP gap_05 data word)
    0
};
#else
EVT_END()
#endif

/**
 * evt_item_use step: opens the status window, adds the item's HP/FP/SP to Mario (or HP to partner LW(11) plus
 * FP/SP), then counts frames while spawning the HP and FP recovery number effects over the target.
 * Blocks until done.
 */
static USER_FUNC(itemUseFunc) {
    PartyEntry* party;
    MarioWork* mario;
    ItemData* item;
#if VERSION >= VERSION_JP
    EffectEntry* eff;
#endif

    item = &itemDataTable[event->lwData[10]];
    mario = marioGetPtr();
    party = partyGetPtr(0);
    if (isFirstCall) {
        cnt = 0;
    }
    switch (cnt) {
        case 0:
            statusWinForceOpen();
            if (event->lwData[11] == 0) {
                ((PouchSetHPS32Fn)pouchSetHP)(pouchGetHP() + item->hp_restored);
                ((PouchSetFPS32Fn)pouchSetFP)(pouchGetFP() + item->fp_restored);
                ((PouchSetAPS32Fn)pouchSetAP)(pouchGetAP() + item->sp_restored);
            } else {
                pouchSetPartyHP(event->lwData[11], pouchGetPartyHP(event->lwData[11]) + item->hp_restored);
                ((PouchSetFPS32Fn)pouchSetFP)(pouchGetFP() + item->fp_restored);
                ((PouchSetAPS32Fn)pouchSetAP)(pouchGetAP() + item->sp_restored);
            }
            cnt++;
            break;
        case 1:
            if (event->lwData[11]) {
                cnt = 200;
                break;
            }
            if (!item->hp_restored) {
                cnt = 100;
                break;
            }
            effRecoveryEntry(0, item->hp_restored, mario->position.x, mario->position.y + mario->wPlayerCollisionBox.y, mario->position.z);
            cnt++;
            break;
        case 31:
            cnt++;
            break;
        case 60:
            cnt = 100;
            break;
        case 100:
            if (!item->fp_restored) {
                cnt = 999;
                break;
            }
            effRecoveryEntry(1, item->fp_restored, mario->position.x, mario->position.y + mario->wPlayerCollisionBox.y, mario->position.z);
        case 130:
            cnt = 999;
            break;
        case 200:
            if (!item->hp_restored) {
                cnt = 300;
                break;
            }
#if VERSION <= VERSION_DEMO_JP
            effRecoveryEntry(0, item->hp_restored, party->position.x, party->position.y + party->height, party->position.z);
#else
            eff = effRecoveryEntry(0, item->hp_restored, party->position.x, party->position.y + party->height, party->position.z);
            ((RecoveryWork*)eff->userdata)->baseY = -party->height * HALF_F;
#endif
            cnt++;
            break;
        case 230:
            cnt++;
            break;
        case 260:
            cnt = 300;
            break;
        case 300:
            if (!item->fp_restored) {
                cnt = 999;
                break;
            }
            effRecoveryEntry(1, item->fp_restored, party->position.x, party->position.y + party->height, party->position.z);
            cnt++;
            break;
        case 330:
            cnt = 999;
            break;
        case 999:
        case 1000:
            return EVT_RETURN_DONE;
        default:
            cnt++;
            break;
    }
    return EVT_RETURN_BLOCK;
}

/** evt_item_use's last step: hides the status window that itemUseFunc forced open. */
static USER_FUNC(itemUseFunc2) {
    statusWinForceOff();
    return EVT_RETURN_DONE;
}

/** Sets args[0] to 1 if Mario is in his 8-bit form (WIN_FLAG_8BIT_MARIO), else 0; picks the partner pose script. */
static USER_FUNC(famicom_check) {
    EvtWord* args = event->args;

    if (wp->flags & WIN_FLAG_8BIT_MARIO) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}

/** Sets args[0] to Yoshi's color (pouchGetPartyColor(4)) for the 8-bit item pose. */
static USER_FUNC(party_color) {
    EvtWord* args = event->args;

    evtSetValue(event, args[0], pouchGetPartyColor(4));
    return EVT_RETURN_DONE;
}

/** Clears the forced slit state on every partner (allPartyForceSlitOff) before the item-use scene. */
#if VERSION >= VERSION_JP
USER_FUNC(all_party_slit_off) {
    allPartyForceSlitOff();
    return EVT_RETURN_DONE;
}
#endif

/**
 * Ragged Diary scene camera: rolls the 3D camera 3 degrees per frame and sways it toward
 * and away from its target. Never finishes; runs in an inline event until the Game Over sequence takes over.
 */
static USER_FUNC(cam_r) {
    CameraEntry* cam;
    Vec v;
    f32 s;

    cam = camGetPtr(CAMERA_3D);
    cam->rollAngle += 3.0f;
    s = (f32)sin((f32)(u32)gp->retraceCount / 10.0f);
    PSVECSubtract(&cam->cameraAt, &cam->cameraPos, &v);
    PSVECScale(&v, &v, 0.2f * s);
    cam->viewOffset.x = v.x;
    cam->viewOffset.y = v.y;
    cam->viewOffset.z = v.z;
    return EVT_RETURN_BLOCK;
}

/** TRUE while the Ragged Diary scene runs or the game is in Game Over; evt_shop and evt_win use it to hold off. */
BOOL winGhostDiaryChk(void) {
    if (wp->menuState == 301) {
        return TRUE;
    }
    return seqGetSeq() == SEQ_GAME_OVER;
}

// FAKE: stand-in for a function the linker stripped; it only keeps the original's path format string
// in its place in .rodata.
const char* winMainStrippedTpl(void) {
    return WIN_DIR "%s/win.tpl";
}

/** Prepares the font renderer for the winFontSet* calls that follow. */
void winFontInit(void) {
    FontDrawStart();
}

/**
 * Draws printf-formatted menu text at pos with scale and color (message control codes honoured).
 * The US and later releases only format when the string contains '%', with a larger buffer.
 */
#if VERSION >= VERSION_US
void winFontSet(Vec pos, Vec scale, GXColor color, const char* fmt, ...) {
    char buf[0x1000];
    const char* msg = fmt;
    Mtx trans;
    Mtx scl;
    va_list args;

    if (strstr(fmt, "%")) {
        va_start(args, fmt);
        vsprintf(buf, fmt, args);
        msg = buf;
    }
    PSMTXTrans(trans, pos.x, pos.y, pos.z);
    PSMTXScale(scl, scale.x, scale.y, scale.z);
    PSMTXConcat(trans, scl, trans);
    FontDrawColor(color);
    FontDrawMessageMtx(trans, msg);
}

/** Like winFontSet, but squeezes the text horizontally so it fits in width; used for long localized names. */
void winFontSetWidth(Vec pos, Vec scale, GXColor color, f32 width, const char* fmt, ...) {
    char buf[0x1000];
    const char* msg = fmt;
    va_list args;
    f32 w;

    if (strstr(fmt, "%")) {
        va_start(args, fmt);
        vsprintf(buf, fmt, args);
        msg = buf;
    }
    w = scale.x * FontGetMessageWidth(msg);
    if (w > width) {
        scale.x *= width / w;
    }
    winFontSet(pos, scale, color, msg);
}
#else
/** Pre-US winFontSet: always formats into a 1 KB buffer, then draws it. */
void winFontSet(Vec pos, Vec scale, GXColor color, const char* fmt, ...) {
    char buf[0x400];
    Mtx trans;
    Mtx scl;
    va_list args;

    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    PSMTXTrans(trans, pos.x, pos.y, pos.z);
    PSMTXScale(scl, scale.x, scale.y, scale.z);
    PSMTXConcat(trans, scl, trans);
    FontDrawColor(color);
    FontDrawMessageMtx(trans, buf);
}
#endif

/**
 * Draws formatted text right-aligned to the width of a three-digit number ("999", full-width in Japanese),
 * for HP/FP/BP style counters. Draws as a plain string, without message control codes.
 */
#if VERSION >= VERSION_US
void winFontSetR(Vec pos, Vec scale, GXColor color, const char* fmt, ...) {
    char buf[0x1000];
    const char* msg = fmt;
    Mtx trans;
    Mtx scl;
    va_list args;
    s32 ref;

    if (strstr(fmt, "%")) {
        va_start(args, fmt);
        vsprintf(buf, fmt, args);
        msg = buf;
    }
    if ((u32)gp->language != 0) {
        ref = FontGetMessageWidth("999");
    } else {
        ref = FontGetMessageWidth("９９９");
    }
    {
        s32 w = ref - FontGetMessageWidth(msg);
        PSMTXTrans(trans, pos.x + scale.x * w, pos.y, pos.z);
    }
    PSMTXScale(scl, scale.x, scale.y, scale.z);
    PSMTXConcat(trans, scl, trans);
    FontDrawColor(color);
    FontDrawStringMtx(trans, msg);
}
#else
/** Pre-US winFontSetR: always right-aligns to the full-width "９９９". */
void winFontSetR(Vec pos, Vec scale, GXColor color, const char* fmt, ...) {
    char buf[0x400];
    Mtx trans;
    Mtx scl;
    va_list args;

    va_start(args, fmt);
    do {
        vsprintf(buf, fmt, args);
    } while (0);
    {
        s32 w = FontGetMessageWidth("９９９") - FontGetMessageWidth(buf);
        PSMTXTrans(trans, pos.x + scale.x * w, pos.y, pos.z);
    }
    PSMTXScale(scl, scale.x, scale.y, scale.z);
    PSMTXConcat(trans, scl, trans);
    FontDrawColor(color);
    FontDrawStringMtx(trans, buf);
}
#endif

#if VERSION >= VERSION_DEMO_EU
/** PAL: right-aligned like winFontSetR, squeezed horizontally to fit width */
void winFontSetRWidth(Vec pos, Vec scale, GXColor color, f32 width, const char* fmt, ...) {
    char buf[0x1000];
    const char* msg;
    Mtx trans;
    Mtx scl;
    va_list args;
    s32 ref;
    s32 w;

    if (strstr(fmt, "%")) {
        va_start(args, fmt);
        vsprintf(buf, fmt, args);
        msg = buf;
    } else {
        msg = fmt;
    }
    if ((u32)gp->language != 0) {
        ref = scale.x * FontGetMessageWidth("999");
    } else {
        ref = scale.x * FontGetMessageWidth("９９９");
    }
    w = scale.x * FontGetMessageWidth(msg);
    if (w > width) {
        scale.x *= width / w;
        w = width;
    }
    PSMTXTrans(trans, pos.x + (ref - w), pos.y, pos.z);
    PSMTXScale(scl, scale.x, scale.y, scale.z);
    PSMTXConcat(trans, scl, trans);
    FontDrawColor(color);
    FontDrawStringMtx(trans, msg);
}
#endif

/** Draws formatted text as a plain string with the font's outline (edge) turned on. */
#if VERSION >= VERSION_US
void winFontSetEdge(Vec pos, Vec scale, GXColor color, const char* fmt, ...) {
    char buf[0x1000];
    const char* msg = fmt;
    Mtx trans;
    Mtx scl;
    va_list args;

    if (strstr(fmt, "%")) {
        va_start(args, fmt);
        vsprintf(buf, fmt, args);
        msg = buf;
    }
    PSMTXTrans(trans, pos.x, pos.y, pos.z);
    PSMTXScale(scl, scale.x, scale.y, scale.z);
    PSMTXConcat(trans, scl, trans);
    FontDrawColor(color);
    FontDrawEdge();
    FontDrawStringMtx(trans, msg);
    FontDrawEdgeOff();
}

/** Outlined text squeezed horizontally to fit in width (winFontSetEdge plus the winFontSetWidth fit). */
void winFontSetEdgeWidth(Vec pos, Vec scale, GXColor color, f32 width, const char* fmt, ...) {
    char buf[0x1000];
    const char* msg = fmt;
    va_list args;
    f32 w;

    if (strstr(fmt, "%")) {
        va_start(args, fmt);
        vsprintf(buf, fmt, args);
        msg = buf;
    }
    w = scale.x * FontGetMessageWidth(msg);
    if (w > width) {
        scale.x *= width / w;
    }
    winFontSetEdge(pos, scale, color, msg);
}
#else
/** Pre-US winFontSetEdge: always formats into a 1 KB buffer. */
void winFontSetEdge(Vec pos, Vec scale, GXColor color, const char* fmt, ...) {
    char buf[0x400];
    Mtx trans;
    Mtx scl;
    va_list args;

    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    PSMTXTrans(trans, pos.x, pos.y, pos.z);
    PSMTXScale(scl, scale.x, scale.y, scale.z);
    PSMTXConcat(trans, scl, trans);
    FontDrawColor(color);
    FontDrawEdge();
    FontDrawStringMtx(trans, buf);
    FontDrawEdgeOff();
}
#endif

/** Looks up message id msg (msgSearch) and draws it; does nothing for NULL. */
void winFontSetLabel(Vec pos, Vec scale, GXColor color, const char* msg) {
    Mtx trans;
    Mtx scl;

    if (msg) {
        PSMTXTrans(trans, pos.x, pos.y, pos.z);
        PSMTXScale(scl, scale.x, scale.y, scale.z);
        PSMTXConcat(trans, scl, trans);
        FontDrawColor(color);
        FontDrawMessageMtx(trans, msgSearch(msg));
    }
}

/** Draws formatted text with a fixed character pitch (FontDrawStringVecPitch). Only in JP and the demos. */
#if VERSION <= VERSION_JP
void winFontSetPitch(f32 pitch, Vec pos, Vec scale, GXColor color, const char* fmt, ...) {
    char buf[0x400];
    va_list args;

    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    FontDrawColor(color);
    FontDrawScaleVec(scale);
    // FAKE: called through a cast that passes the address of this function's own pos (the same registers as
    // fontmgr.h's by-value Vec): the plain call first copies pos to a temporary, which the target does not.
    ((void (*)(Vec*, const char*, f32))FontDrawStringVecPitch)(&pos, buf, pitch);
}
#endif

/** Selects the texture palette (TPL) that winTexSet draws from and sets up GX for one textured, color-tinted quad. */
void winTexInit(TEXPalette* texture) {
    winTexTpl = texture;
    GXSetCullMode(GX_CULL_NONE);
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetNumTexGens(1u);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
}

/**
 * Draws texture textureId of the current TPL centred at translate, sized texture size times scale,
 * tinted by color in 2D camera space. Alpha below 255 blends; opaque draws use an alpha test instead.
 */
void winTexSet(u32 textureId, Vec translate, Vec scale, GXColor color) {
    Mtx trans;
    Mtx scl;
    Mtx m;
    GXTexObj obj;
    f32 sy;

    if (color.a != 0xFF) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZCompLoc(GX_TRUE);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    } else {
        GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZCompLoc(GX_FALSE);
        GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    }
    TEXGetGXTexObjFromPalette(winTexTpl, &obj, textureId);
    GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXSetTevColor(GX_TEVREG0, color);
    PSMTXTrans(trans, translate.x, translate.y, translate.z);
    sy = scale.y * GXGetTexObjHeight(&obj);
    PSMTXScale(scl, scale.x * GXGetTexObjWidth(&obj), sy, scale.z);
    PSMTXConcat(trans, scl, m);
    PSMTXConcat(camGetPtr(CAMERA_2D)->view, m, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-0.5f, -0.5f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(HALF_F, -0.5f, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(HALF_F, HALF_F, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(-0.5f, HALF_F, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
}

/** winTexSet that always alpha-blends, whatever the color's alpha. Not in the demos. */
#if VERSION >= VERSION_JP
void winTexSetNearest(u32 textureId, Vec translate, Vec scale, GXColor color) {
    Mtx trans;
    Mtx scl;
    Mtx m;
    GXTexObj obj;
    f32 sy;

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    TEXGetGXTexObjFromPalette(winTexTpl, &obj, textureId);
    GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXSetTevColor(GX_TEVREG0, color);
    PSMTXTrans(trans, translate.x, translate.y, translate.z);
    sy = scale.y * GXGetTexObjHeight(&obj);
    PSMTXScale(scl, scale.x * GXGetTexObjWidth(&obj), sy, scale.z);
    PSMTXConcat(trans, scl, m);
    PSMTXConcat(camGetPtr(CAMERA_2D)->view, m, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-0.5f, -0.5f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(HALF_F, -0.5f, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(HALF_F, HALF_F, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(-0.5f, HALF_F, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
}
#endif

/** winTexSet with the quad rotated rot degrees about the screen's z axis. */
void winTexSetRot(u32 textureId, Vec translate, Vec scale, GXColor color, f32 rot) {
    Mtx trans;
    Mtx scl;
    Mtx r;
    Mtx m;
    GXTexObj obj;
    f32 sy;

    if (color.a != 0xFF) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZCompLoc(GX_TRUE);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    } else {
        GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZCompLoc(GX_FALSE);
        GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    }
    TEXGetGXTexObjFromPalette(winTexTpl, &obj, textureId);
    GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXSetTevColor(GX_TEVREG0, color);
    PSMTXTrans(trans, translate.x, translate.y, translate.z);
    PSMTXRotRad(r, 'z', 0.017453292f * rot);
    sy = scale.y * GXGetTexObjHeight(&obj);
    PSMTXScale(scl, scale.x * GXGetTexObjWidth(&obj), sy, scale.z);
    PSMTXConcat(trans, r, m);
    PSMTXConcat(m, scl, m);
    PSMTXConcat(camGetPtr(CAMERA_2D)->view, m, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-0.5f, -0.5f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(HALF_F, -0.5f, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(HALF_F, HALF_F, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(-0.5f, HALF_F, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
}

/**
 * Two-texture variant of winTexInit: stage 0 takes the first texture's color,
 * stage 1 multiplies by the tint and takes the second texture's alpha,
 * so the second texture works as a mask (used for menu tab labels).
 */
void winTexInit_x2(TEXPalette* texture) {
    winTexInit(texture);
    GXSetNumTexGens(2);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C);
    GXSetNumTevStages(2);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C0, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
}

/** Draws textureId1 masked by textureId2 (see winTexInit_x2), blended, sized from the second texture. */
void winTexSet_x2(u32 textureId1, u32 textureId2, Vec translate, Vec scale, GXColor color) {
    Mtx trans;
    Mtx scl;
    Mtx m;
    GXTexObj obj;
    f32 sy;

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    TEXGetGXTexObjFromPalette(winTexTpl, &obj, textureId1);
    GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    TEXGetGXTexObjFromPalette(winTexTpl, &obj, textureId2);
    GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP1);
    GXSetTevColor(GX_TEVREG0, color);
    PSMTXTrans(trans, translate.x, translate.y, translate.z);
    sy = scale.y * GXGetTexObjHeight(&obj);
    PSMTXScale(scl, scale.x * GXGetTexObjWidth(&obj), sy, scale.z);
    PSMTXConcat(trans, scl, m);
    PSMTXConcat(camGetPtr(CAMERA_2D)->view, m, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-0.5f, -0.5f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(HALF_F, -0.5f, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(HALF_F, HALF_F, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(-0.5f, HALF_F, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
}

/** Sets up GX for winIconSet (no TPL; icons come from the icon driver). */
void winIconInit(void) {
    winTexInit(NULL);
}

/**
 * Sets up GX so the following winIconSet draws a grayscale icon (R, G and B summed at 1/3 each);
 * used for badges that cost more BP than Mario has left.
 */
void winIconGrayInit(void) {
    winTexInit(NULL);
    GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
    GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevColor(GX_TEVREG1, (GXColor){0x55, 0x55, 0x55, 0xFF});
    GXSetNumTevStages(4);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C1, GX_CC_TEXC, GX_CC_CPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP2);
    if (!GX_TEVSTAGE2 && !GX_TEVSTAGE2 && !GX_TEVSTAGE2) {
    }
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C1, GX_CC_TEXC, GX_CC_CPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP3);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_ZERO, GX_CC_C0, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_A0, GX_CA_APREV, GX_CA_ZERO);
    GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
}

/**
 * Draws item/menu icon iconId centred at translate, scaled and tinted, with linear filtering.
 * One icon id is remapped to its neighbour (ICON_115 to ICON_114).
 */
void winIconSet(s32 iconId, Vec translate, Vec scale, GXColor color) {
    Mtx trans;
    Mtx scl;
    Mtx m;
    GXTexObj obj;
    f32 sy;

    if (iconId == ICON_115) {
        iconId = ICON_114;
    }
    iconGetTexObj(&obj, iconId);
    GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    if (color.a != 0xFF) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZCompLoc(GX_TRUE);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    } else {
        GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
        GXSetZCompLoc(GX_FALSE);
        GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    }
    GXSetTevColor(GX_TEVREG0, color);
    PSMTXTrans(trans, translate.x, translate.y, translate.z);
    sy = scale.y * GXGetTexObjHeight(&obj);
    PSMTXScale(scl, scale.x * GXGetTexObjWidth(&obj), sy, scale.z);
    PSMTXConcat(trans, scl, m);
    PSMTXConcat(camGetPtr(CAMERA_2D)->view, m, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-0.5f, -0.5f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(HALF_F, -0.5f, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(HALF_F, HALF_F, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(-0.5f, HALF_F, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
}

/**
 * evt_lecture_msg step: blocks until the tutorial has reached step args[0].
 * While waiting it lets input through (clears WIN_FLAG_LECTURE_KEY_MASK), and masks it again once the step is reached.
 */
static USER_FUNC(wait) {
    s32 n = evtGetValue(event, event->args[0]);

#if VERSION <= VERSION_DEMO_JP
    // The demo has no key mask flag.
    if (wp->lectureStep < n) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
#else
    if (isFirstCall) {
        wp->flags &= ~WIN_FLAG_LECTURE_KEY_MASK;
    }
    if (wp->lectureStep < n) {
        return EVT_RETURN_BLOCK;
    }
    wp->flags |= WIN_FLAG_LECTURE_KEY_MASK;
    return EVT_RETURN_DONE;
#endif
}

/** End of the badge tutorial text: clears WIN_FLAG_LECTURE_KEY_MASK so the player has full control of the menu. */
#if VERSION >= VERSION_JP
USER_FUNC(lecture_key_mask_off) {
    wp->flags &= ~WIN_FLAG_LECTURE_KEY_MASK;
    return EVT_RETURN_DONE;
}
#endif

/**
 * Badge tutorial input filter, run by winMain each frame:
 * while the tutorial is on, only the input the current step asks for gets through and doing it advances lectureStep:
 * steps 0-1 take A (read from the pad and swallowed), 2-4 Right, 5-8 A, 9 Start. In JP and later nothing gets
 * through while WIN_FLAG_LECTURE_KEY_MASK is set (outside the script's wait steps).
 */
static void winLectureKeyMask(void) {
    if (wp->flags & WIN_FLAG_LECTURE) {
#if VERSION >= VERSION_JP
        if (wp->flags & WIN_FLAG_LECTURE_KEY_MASK) {
            wp->buttonTrg = 0;
            wp->buttonRep = 0;
            wp->dirTrg = 0;
            wp->dirRep = 0;
            return;
        }
#endif
        switch (wp->lectureStep) {
            case 0:
            case 1:
                wp->buttonTrg = 0;
                wp->buttonRep = 0;
                wp->dirTrg = 0;
                wp->dirRep = 0;
                if (keyGetButtonTrg(0) & PAD_BUTTON_A) {
                    wp->lectureStep++;
                }
                break;
            case 2:
            case 3:
            case 4:
                wp->buttonTrg = 0;
                wp->buttonRep = 0;
                wp->dirTrg &= DEMO_STICK_RIGHT;
                wp->dirRep &= DEMO_STICK_RIGHT;
                if (wp->dirTrg || wp->dirRep) {
                    wp->lectureStep++;
                }
                break;
            case 5:
            case 6:
            case 7:
            case 8:
                wp->buttonTrg &= PAD_BUTTON_A;
                wp->buttonRep &= PAD_BUTTON_A;
                wp->dirTrg = 0;
                wp->dirRep = 0;
                if (wp->buttonTrg || wp->buttonRep) {
                    wp->lectureStep++;
                }
                break;
            case 9:
                wp->buttonTrg &= PAD_BUTTON_START;
                wp->buttonRep &= PAD_BUTTON_START;
                wp->dirTrg = 0;
                wp->dirRep = 0;
                if (wp->buttonTrg || wp->buttonRep) {
                    wp->lectureStep++;
                }
                break;
        }
    }
}

/**
 * Starts the badge tutorial menu (from Rogueport, gor_02):
 * sets the tutorial flag, which opens the menu straight away, and starts evt_lecture_msg.
 */
void winLectureOn(void) {
    wp->flags |= WIN_FLAG_LECTURE;
#if VERSION >= VERSION_JP
    wp->flags |= WIN_FLAG_LECTURE_KEY_MASK;
#endif
    wp->lectureStep = 0;
    wp->lectureEvent = evtEntry(evt_lecture_msg, 0, 0);
}

/** TRUE while the badge tutorial's text script is still running; once it ends, clears the tutorial flag. */
BOOL winLectureCheck(void) {

    if ((wp->flags & WIN_FLAG_LECTURE) && evtCheckID(wp->lectureEvent->eventId)) {
        return TRUE;
    }
    wp->flags &= ~WIN_FLAG_LECTURE;
    return FALSE;
}

// FAKE: see HALF_F at the top; volatile keeps each use a load from this word.
const volatile f32 winConstHalf __attribute__((aligned(8))) = 0.5f;

// FAKE: stand-in for a function the linker stripped; it only keeps the original's int-to-float
// conversion constant in its place in .sdata2.
void winMainStrippedPool(f32* f, s32 i) {
    *f = (f32)i;
}
