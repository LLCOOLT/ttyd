// File select sequence: the save file menu (new game, copy, delete, sound and rumble settings).
#include "version.h"
#include "icon_ids.h"
#include "evt/evt_memcard.h"
#include "evt/evt_sub.h"
#include "seq/seq_load.h"
#include "sdk_decls.h"
#include "win/win_mario.h"
#include "libc_decls.h"
#include "nameent.h"
#include "evt/evt_cmd.h"
#include "countdown.h"
#include "driver/fadedrv.h"
#include "driver/seqdrv.h"
#include "driver/swdrv.h"
#include "event.h"
#include "manager/cardmgr.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "manager/filemgr.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mariost.h"
#include "pmario_sound.h"
#include "system.h"
#include <dolphin/os.h>
#include "driver/dispdrv.h"
#include "driver/msgdrv.h"
#include <string.h>
#include <stdio.h>
#include "driver/camdrv.h"
#include "manager/fontmgr.h"
#include "driver/windowdrv.h"
#include "driver/icondrv.h"
#include "win/win_main.h"
#include "sdk/texPalette.h"
#include "evt/evt_story.h"
#include <dolphin/pad.h>
#include <demo/DEMOPad.h>
#include "sound.h"

typedef struct LoadWork {
    u16 flags;         // 0x0
    FileEntry* file;   // 0x4
    f32 x;             // 0x8
    f32 y;             // 0xC
    f32 tx;            // 0x10
    f32 ty;            // 0x14
    s32 state;         // 0x18, sequence state
    s32 cardCode;      // 0x1C, cardGetCode() at the last check
    s32 slot;          // 0x20
    s32 soundCursor;   // 0x24, sound menu choice
    s32 rumbleCursor;  // 0x28, rumble menu choice
    f32 alpha;         // 0x2C
    s32 copySrc;       // 0x30, copy: source slot
    s32 copyDst;       // 0x34, copy: destination slot
    const char* msg;   // 0x38
    EventEntry* evt;   // 0x3C
    s32 soundSetting;  // 0x40, sound mode in effect (restored on cancel)
    s32 rumbleSetting; // 0x44, rumble setting in effect (restored on cancel)
#if VERSION >= VERSION_JP
    s32 savedWinId; // 0x48, event printWindowId, restored on exit
#endif
} LoadWork;

typedef struct WinDt {
    f32 x;      // 0x0
    f32 y;      // 0x4
    f32 ofsX;   // 0x8
    f32 ofsY;   // 0xC
    s32 tex;    // 0x10, icon texture
    s32 tex2;   // 0x14, second texture (winTexSet_x2)
    u8 next[4]; // 0x18
} WinDt;

// Texture of the highlight bar behind the selected rumble option (the sound options use 0x33 in every version)
#if VERSION >= VERSION_US
#define RUMBLE_SEL_TEX 0x20
#else
#define RUMBLE_SEL_TEX 0x33
#endif

// SFX(id): plays a sound effect by its numeric id (psndSFXOn takes a name or an id).
#define SFX(id) psndSFXOn((const char*)(id))
// SLOTFLAGS(i): the flags word of save slot i.
#define SLOTFLAGS(i) (cardGetFilePtr()->saves[(i)].data.flags)

#if VERSION <= VERSION_DEMO_US
static BOOL loadMain(SequenceWork* seq);
#else
static void loadMain(SequenceWork* seq);
#endif
static void loadDraw(CameraId camera, void* param);
static void continueGame(void);

#if VERSION <= VERSION_DEMO_US
s32 stone_id[7] = {ICON_197, ICON_198, ICON_19A, ICON_19C, ICON_19D, ICON_199, ICON_19B};

static EVT_BEGIN(evt_shake)
    CALL(evt_sub_rumble_onoff, 0, 0)
    WAIT_MS(150)
    CALL(evt_sub_rumble_onoff, 1, 0)
    RETURN
EVT_END()
#endif

WinDt win_dt[9] = {
    {-140.0f, 75.0f, -120.0f, 60.0f, 13, 0, {7, 2, 1, 1}},
    {140.0f, 75.0f, -120.0f, 60.0f, 12, 0, {8, 3, 0, 0}},
    {-140.0f, -65.0f, -120.0f, 60.0f, 11, 0, {0, 4, 3, 3}},
    {140.0f, -65.0f, -120.0f, 60.0f, 10, 0, {1, 5, 2, 2}},
    {-200.0f, -150.0f, -80.0f, 0.0f, 16, 30, {2, 7, 6, 5}},
    {0.0f, -150.0f, -80.0f, 0.0f, 17, 30, {2, 7, 4, 6}},
    {200.0f, -150.0f, -80.0f, 0.0f, 18, 30, {3, 8, 5, 4}},
    {-130.0f, -190.0f, -100.0f, 0.0f, 19, 31, {4, 0, 8, 8}},
    {130.0f, -190.0f, -100.0f, 0.0f, 20, 31, {5, 1, 7, 7}},
};

WinDt win_dt2[7] = {
    {-140.0f, 75.0f, -120.0f, 60.0f, 13, 0, {6, 2, 1, 1}},
    {140.0f, 75.0f, -120.0f, 60.0f, 12, 0, {6, 3, 0, 0}},
    {-140.0f, -65.0f, -120.0f, 60.0f, 11, 0, {0, 6, 3, 3}},
    {140.0f, -65.0f, -120.0f, 60.0f, 10, 0, {1, 6, 2, 2}},
    {-200.0f, -150.0f, -80.0f, 0.0f, 16, 30, {2, 7, 6, 5}},
    {0.0f, -150.0f, -80.0f, 0.0f, 17, 30, {2, 7, 4, 6}},
    {200.0f, -150.0f, -80.0f, 0.0f, 18, 30, {3, 1, 6, 6}},
};

WinDt win_dt3[4] = {
    {-140.0f, 75.0f, -120.0f, 60.0f, 13, 0, {2, 2, 1, 1}},
    {140.0f, 75.0f, -120.0f, 60.0f, 12, 0, {3, 3, 0, 0}},
    {-140.0f, -65.0f, -120.0f, 60.0f, 11, 0, {0, 0, 3, 3}},
    {140.0f, -65.0f, -120.0f, 60.0f, 10, 0, {1, 1, 2, 2}},
};

static LoadWork work;
static LoadWork* wp = &work;
#if VERSION >= VERSION_US
__declspec(section ".sdata2") const u32 seq_logo_zero_color[2];
#endif

static EvtWord evt_shake[12];

#if VERSION >= VERSION_JP
s32 evt_seq_load_keep_msg_window(EventEntry* evt, BOOL isFirstCall) {
    fadeReset(4);
    wp->savedWinId = evt->printWindowId;
    return 2;
}
#endif

void seq_loadInit(SequenceWork* seq) {
    memset(wp, 0, sizeof(LoadWork));
}

void seq_loadExit(SequenceWork* seq) {
    if (wp->file != NULL) {
        fileFree(wp->file);
    }
    wp->file = NULL;
}

static inline BOOL loadStart(void);

void seq_loadMain(SequenceWork* seq) {
    switch (seq->state) {
        case 0:
            if (loadStart()) {
                seq->state++;
            }
            break;
        case 1:
            wp->evt = evtEntryType(evt_memcard_check, 0, 0, 0);
#if VERSION >= VERSION_JP
            if (wp->flags & 0x80) {
                wp->flags &= ~0x80;
                wp->evt->lwData[10] = 1;
                wp->evt->printWindowId = wp->savedWinId;
            }
#endif
            seq->state++;
            break;
        case 2:
            if (evtCheckID(wp->evt->eventId) == 0) {
                if (evtGetValue(NULL, (s32)0xFAA2B580) != 1) {
                    seqSetSeq(SEQ_TITLE, NULL, NULL);
                } else {
                    wp->evt = NULL;
                    seq->state++;
#if VERSION <= VERSION_DEMO_US
                    wp->cardCode = cardGetCode();
                    if (OSGetSoundMode() == 0) {
                        SoundSetOutputMode(0);
                        gp->soundMode = 0;
                        wp->soundSetting = 0;
                    } else if (gp->soundMode == 0) {
                        SoundSetOutputMode(1);
                        wp->soundSetting = 1;
                    } else {
                        SoundSetOutputMode(2);
                        wp->soundSetting = 2;
                    }
#else
                    wp->state = 0;
                    wp->cardCode = cardGetCode();
                    wp->flags &= ~0x40;
                    if (OSGetSoundMode() == 0) {
                        SoundSetOutputMode(0);
                        gp->soundMode = 0;
                        wp->soundSetting = 0;
                    } else {
                        SoundSetOutputMode(1);
                        if (gp->soundMode == 0) {
                            wp->soundSetting = 1;
                        } else {
                            wp->soundSetting = 2;
                        }
                    }
#endif
                    wp->rumbleSetting = gp->rumbleEnabled == 0;
                    wp->soundCursor = wp->soundSetting;
                    wp->rumbleCursor = wp->rumbleSetting;
                    wp->slot = gp->lastSlot;
                    wp->x = win_dt[wp->slot].x;
                    wp->y = win_dt[wp->slot].y;
                }
            }
            break;
        case 3: {
            GXColor c = {0, 0, 0, 255};
            fadeEntry(FADE_CURTAIN_SIDES_A2, 0, c);
            seq->state++;
            break;
        }
        case 4:
            loadMain(seq);
            break;
    }
}

static inline BOOL loadStart(void) {
#if VERSION >= VERSION_US
    const char* lang[] = {"jp", "us", "ge", "fr", "sp", "it"};
    if (fileAsyncf(4, NULL, "%s/w/%s/name.tpl", getMarioStDvdRoot(), lang[gp->language]) != NULL) {
        wp->file = fileAllocf(4, "%s/w/%s/name.tpl", getMarioStDvdRoot(), lang[gp->language]);
#elif VERSION <= VERSION_DEMO_US
    if (fileAsyncf(4, NULL, "%s/window/jp/name.tpl", getMarioStDvdRoot()) != NULL) {
        wp->file = fileAllocf(4, "%s/window/jp/name.tpl", getMarioStDvdRoot());
#else
    if (fileAsyncf(4, NULL, "%s/w/jp/name.tpl", getMarioStDvdRoot()) != NULL) {
        wp->file = fileAllocf(4, "%s/w/jp/name.tpl", getMarioStDvdRoot());
#endif
        return TRUE;
    }
    return FALSE;
}

// New game: reset the story state and the party and set the fades into the prologue map
static inline void loadNewGameSetup(void) {
    stg0_00_init();
    gp->saveSlot = wp->slot;
    marioPartyKill();
    {
        MarioWork* m = marioGetPtr();
        m->prevPartyMemberId[0] = 0;
        m->prevPartyMemberId[1] = 0;
    }
    gp->areaFadeInType = FADE_NONE;
    gp->areaFadeOutType = FADE_CURTAIN_SIDES_A2_3D;
    swInit();
    swByteSet(GSW_STORY_PROGRESS, STORY_STG0_00_PROLOGUE);
}

#if VERSION <= VERSION_DEMO_US
static BOOL loadMain(SequenceWork* seq) {
#else
static void loadMain(SequenceWork* seq) {
#endif
    u32 trg;
    u32 dir;
    s32 code;
    s32 prev;
    s32 i;
    s32 sound;
    u16 flags;

    trg = keyGetButtonTrg(0);
    keyGetButtonRep(0);
    dir = keyGetDirRep(0);
    code = cardGetCode();
    if (cardIsExec() || !fadeIsFinish()) {
        trg = 0;
        dir = 0;
    }
    if (wp->cardCode != code) {
        trg = 0;
        dir = 0;
    }
    wp->cardCode = code;
    for (i = 0; i < 4; i++) {
        flags = SLOTFLAGS(i);
        if (!(flags & 1) || (flags & 2)) {
            break;
        }
    }
    if (i < 4) {
        wp->flags &= ~0x10;
    } else {
        wp->flags |= 0x10;
    }
    wp->flags &= ~0x20;
    for (i = 0; i < 4; i++) {
        flags = SLOTFLAGS(i);
        if (!(flags & 1) && !(flags & 2)) {
            break;
        }
    }
    if (i >= 4) {
        wp->flags |= 0x20;
    }

    switch (wp->state) {
        case 0:
            wp->state++;
        case 1:
            wp->msg = msgSearch("msg_savefile_select");
            prev = wp->slot;
            if (dir & DEMO_STICK_UP) {
                wp->slot = win_dt[prev].next[0];
            } else if (dir & DEMO_STICK_DOWN) {
                wp->slot = win_dt[prev].next[1];
            } else if (dir & DEMO_STICK_LEFT) {
                wp->slot = win_dt[prev].next[2];
            } else if (dir & DEMO_STICK_RIGHT) {
                wp->slot = win_dt[prev].next[3];
            } else if (trg & PAD_BUTTON_A) {
                flags = SLOTFLAGS(wp->slot);
                switch (wp->slot) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        if (flags & 2) {
                            SFX(0x13);
                        } else if (flags & 1) {
                            wp->state = 0x1e;
                            SFX(0x12);
                        } else {
                            wp->state = 0x14;
                            SFX(0x12);
                        }
                        break;
                    case 4:
                        if (!(wp->flags & 0x10)) {
                            for (i = 0; i < 4; i++) {
                                flags = SLOTFLAGS(i);
                                if (!(flags & 1) || (flags & 2)) {
                                    break;
                                }
                            }
                            if (i < 4) {
                                SFX(0x12);
                                wp->slot = 0;
                                wp->state = 0x28;
                            } else {
                                SFX(0x13);
                            }
                        }
                        break;
                    case 5:
                        if (!(wp->flags & 0x20)) {
                            for (i = 0; i < 4; i++) {
                                flags = SLOTFLAGS(i);
                                if (!(flags & 2) && !(flags & 1)) {
                                    break;
                                }
                            }
                            if (i < 4) {
                                SFX(0x12);
                                wp->slot = 0;
                                wp->state = 0x32;
                            } else {
                                SFX(0x13);
                            }
                        }
                        break;
                    case 6:
                        SFX(0x13);
                        wp->state = 0xa;
                        break;
                    case 7:
                        SFX(0x12);
#if VERSION >= VERSION_JP
                        psndBGMOff(PSND_FADE_DIP_TO(10));
#endif
                        wp->state = 0x64;
                        break;
                    case 8:
                        SFX(0x12);
                        wp->state = 0xc8;
                        break;
                }
            } else if (trg & PAD_BUTTON_B) {
                SFX(0x13);
                wp->state = 0xa;
            }
            if (prev != wp->slot) {
                if (wp->slot < 4) {
                    SFX(9);
                } else {
                    SFX(5);
                }
            }
            wp->tx = win_dt[wp->slot].x + win_dt[wp->slot].ofsX;
            wp->ty = win_dt[wp->slot].y + win_dt[wp->slot].ofsY;
            break;
        case 0xa:
            fadeEntry(FADE_CURTAIN_SIDES_A1, 0, (GXColor){0, 0, 0, 255});
            wp->state++;
            break;
        case 0xb:
            if (fadeIsFinish()) {
                seqSetSeq(SEQ_TITLE, NULL, NULL);
            }
            break;
        case 0x14:
            wp->flags |= 0x40;
            wp->evt = evtEntryType(evt_memcard_start, 0, 0, 0);
            wp->evt->lwData[0] = wp->slot;
            wp->state++;
            break;
        case 0x15:
            if (!evtCheckID(wp->evt->eventId)) {
                wp->flags &= ~0x40;
                if (evtGetValue(NULL, (s32)0xFD050F80) == 1) {
                    wp->state++;
                } else {
                    wp->state = 1;
                }
            }
            break;
        case 0x16:
            fadeEntry(FADE_CURTAIN_SIDES_A1, 0, (GXColor){0, 0, 0, 255});
#if VERSION <= VERSION_DEMO_US
            psndBGMOff_f_d(PSND_FADE_OUT, 3000, 0);
#else
            psndBGMOff_f_d(PSND_FADE_OUT, 2000, 0);
#endif
            wp->state++;
            break;
        case 0x17:
            if (fadeIsFinish()) {
                wp->flags |= 0x40;
                wp->evt = evtEntryType(evt_continue, 0, 0, 0);
                wp->state++;
            }
            break;
        case 0x18:
            if (!evtCheckID(wp->evt->eventId)) {
                wp->flags &= ~0x40;
                continueGame();
            }
            break;
        case 0x1e:
            fadeEntry(FADE_CURTAIN_SIDES_A1, 0, (GXColor){0, 0, 0, 255});
            wp->state++;
            break;
        case 0x1f:
            if (fadeIsFinish()) {
                wp->state++;
            }
            break;
        case 0x20:
            if (nameEntPrepare()) {
                nameEntOn(0);
                fadeEntry(FADE_CURTAIN_SIDES_A2, 0, (GXColor){0, 0, 0, 255});
                wp->state++;
            }
            break;
        case 0x21:
            if (fadeIsFinish() && !nameEntWait()) {
                fadeEntry(FADE_CURTAIN_SIDES_A1_3D, 0, (GXColor){0, 0, 0, 255});
                if (!nameEntIsCancel()) {
                    psndBGMOff_f_d(PSND_FADE_OUT, 3000, 0);
                }
                wp->state++;
            }
            break;
        case 0x22:
            if (fadeIsFinish()) {
                nameEntOff();
                if (nameEntIsCancel()) {
                    fadeEntry(FADE_CURTAIN_SIDES_A2, 0, (GXColor){0, 0, 0, 255});
                    wp->state = 1;
                } else {
                    strcpy((char*)gp->playerName, nameEntGetName());
                    gp->lastSlot = wp->slot;
#if VERSION <= VERSION_DEMO_US
                    if (code == 0) {
                        gp->saveSlot = wp->slot;
                        wp->evt = evtEntryType(evt_memcard_save, 0, 0, 0);
                        wp->evt->lwData[0] = 0x17;
                        wp->state++;
                    } else {
                        // demo: the new-game setup runs once the name is in, or after the first save
                        loadNewGameSetup();
                        seqSetSeq(SEQ_MAP_CHANGE, "aaa_00", "prologue");
                    }
#else
                    loadNewGameSetup();
                    if (code == 0) {
                        gp->saveSlot = wp->slot;
#if VERSION >= VERSION_US
                        wp->evt = evtEntryType(evt_memcard_save_wrapper, 0, 0, 0);
#else
                        wp->evt = evtEntryType(evt_memcard_save, 0, 0, 0);
#endif
                        wp->evt->lwData[0] = 0x17;
                        wp->state++;
                    } else {
                        seqSetSeq(SEQ_MAP_CHANGE, "aaa_00", "prologue");
                    }
#endif
                }
            }
            break;
        case 0x23:
            if (!evtCheckID(wp->evt->eventId)) {
#if VERSION <= VERSION_DEMO_US
                loadNewGameSetup();
#endif
                seqSetSeq(SEQ_MAP_CHANGE, "aaa_00", "prologue");
            }
            break;
        case 0x28:
            wp->msg = msgSearch("msg_savefile_delete_select");
            prev = wp->slot;
            if (dir & DEMO_STICK_UP) {
                wp->slot = win_dt2[prev].next[0];
            } else if (dir & DEMO_STICK_DOWN) {
                wp->slot = win_dt2[prev].next[1];
            } else if (dir & DEMO_STICK_LEFT) {
                wp->slot = win_dt2[prev].next[2];
            } else if (dir & DEMO_STICK_RIGHT) {
                wp->slot = win_dt2[prev].next[3];
            } else if (trg & PAD_BUTTON_A) {
                if (prev < 4) {
                    flags = SLOTFLAGS(wp->slot);
                    if ((flags & 2) || !(flags & 1)) {
                        SFX(0x12);
                        wp->state++;
                    } else {
                        SFX(0x13);
                    }
                } else {
                    wp->slot = 4;
                    wp->state = 1;
                    SFX(0x13);
                }
            } else if (trg & PAD_BUTTON_B) {
                wp->slot = 4;
                wp->state = 1;
                SFX(0x13);
            }
            if (prev != wp->slot && wp->slot < 4) {
                SFX(9);
            }
            wp->tx = win_dt2[wp->slot].x + win_dt2[wp->slot].ofsX;
            wp->ty = win_dt2[wp->slot].y + win_dt2[wp->slot].ofsY;
            break;
        case 0x29:
            wp->flags |= 0x40;
            wp->evt = evtEntryType(evt_memcard_delete, 0, 0, 0);
            wp->evt->lwData[0] = wp->slot;
            wp->state++;
            break;
        case 0x2a:
            if (!evtCheckID(wp->evt->eventId)) {
#if VERSION <= VERSION_DEMO_US
                wp->flags &= ~0x40;
                wp->slot = 4;
                wp->state = 1;
#else
                if (evtGetValue(NULL, (s32)0xFAA2B580) == 0) {
                    wp->flags &= ~0x40;
                    wp->slot = 4;
                    wp->state = 1;
                } else {
                    wp->flags |= 0x80;
                    seq->state = 1;
                    return;
                }
#endif
            }
            break;
        case 0x32:
            wp->msg = msgSearch("msg_savefile_copy_select");
            prev = wp->slot;
            if (dir & DEMO_STICK_UP) {
                wp->slot = win_dt2[prev].next[0];
            } else if (dir & DEMO_STICK_DOWN) {
                wp->slot = win_dt2[prev].next[1];
            } else if (dir & DEMO_STICK_LEFT) {
                wp->slot = win_dt2[prev].next[2];
            } else if (dir & DEMO_STICK_RIGHT) {
                wp->slot = win_dt2[prev].next[3];
            } else if (trg & PAD_BUTTON_A) {
                if (prev < 4) {
                    flags = SLOTFLAGS(wp->slot);
                    if (!(flags & 2) && !(flags & 1)) {
                        wp->state = 0x33;
                        wp->copySrc = wp->slot;
                        wp->copyDst = (wp->copySrc + 1) % 4;
                        wp->slot = wp->copyDst;
                        SFX(0x12);
                    }
                } else {
                    wp->slot = 5;
                    wp->state = 1;
                    SFX(0x13);
                }
            } else if (trg & PAD_BUTTON_B) {
                wp->slot = 5;
                wp->state = 1;
                SFX(0x13);
            }
            if (prev != wp->slot && wp->slot < 4) {
                SFX(9);
            }
            wp->tx = win_dt2[wp->slot].x + win_dt2[wp->slot].ofsX;
            wp->ty = win_dt2[wp->slot].y + win_dt2[wp->slot].ofsY;
            break;
        case 0x33:
            wp->msg = msgSearch("msg_savefile_copy_point");
            prev = wp->slot;
            if (dir & DEMO_STICK_UP) {
                do {
                    wp->slot = win_dt3[wp->slot].next[0];
                } while (wp->slot == wp->copySrc);
            } else if (dir & DEMO_STICK_DOWN) {
                do {
                    wp->slot = win_dt3[wp->slot].next[1];
                } while (wp->slot == wp->copySrc);
            } else if (dir & DEMO_STICK_LEFT) {
                do {
                    wp->slot = win_dt3[wp->slot].next[2];
                } while (wp->slot == wp->copySrc);
            } else if (dir & DEMO_STICK_RIGHT) {
                do {
                    wp->slot = win_dt3[wp->slot].next[3];
                } while (wp->slot == wp->copySrc);
            } else if (trg & PAD_BUTTON_A) {
                wp->state = 0x34;
                wp->copyDst = wp->slot;
                SFX(0x12);
            } else if (trg & PAD_BUTTON_B) {
                wp->slot = wp->copySrc;
                wp->state = 0x32;
                SFX(0x13);
            }
            if (prev != wp->slot && wp->slot < 4) {
                SFX(9);
            }
            wp->copyDst = wp->slot;
            wp->tx = win_dt2[wp->slot].x + win_dt2[wp->slot].ofsX;
            wp->ty = win_dt2[wp->slot].y + win_dt2[wp->slot].ofsY;
            break;
        case 0x34:
            wp->flags |= 0x40;
            wp->evt = evtEntryType(evt_memcard_copy, 0, 0, 0);
            wp->evt->lwData[0] = wp->copySrc;
            wp->evt->lwData[1] = wp->copyDst;
            wp->state++;
            break;
        case 0x35:
            if (!evtCheckID(wp->evt->eventId)) {
#if VERSION <= VERSION_DEMO_US
                wp->flags &= ~0x40;
                wp->slot = 5;
                wp->state = 1;
#else
                if (evtGetValue(NULL, (s32)0xFAA2B580) == 0) {
                    wp->flags &= ~0x40;
                    wp->slot = 5;
                    wp->state = 1;
                } else {
                    wp->flags |= 0x80;
                    seq->state = 1;
                    return;
                }
#endif
            }
            break;
        case 0x64:
#if VERSION <= VERSION_DEMO_US
            wp->flags |= 1;
            if (dir & DEMO_STICK_UP) {
                wp->soundCursor--;
                SFX(5);
            } else if (dir & DEMO_STICK_DOWN) {
                wp->soundCursor++;
                SFX(5);
            } else if (trg & PAD_BUTTON_A) {
                switch (wp->soundCursor) {
                    case 0:
                        OSSetSoundMode(0);
                        SoundSetOutputMode(0);
                        gp->soundMode = 0;
                        break;
                    case 1:
                        OSSetSoundMode(1);
                        SoundSetOutputMode(1);
                        gp->soundMode = 0;
                        break;
                    case 2:
                        OSSetSoundMode(1);
                        SoundSetOutputMode(2);
                        gp->soundMode = 1;
                        break;
                }
                SFX(0x12);
                wp->soundSetting = wp->soundCursor;
                wp->flags &= ~1;
                wp->state = 1;
            } else if (trg & PAD_BUTTON_B) {
                SFX(0x13);
                wp->soundCursor = wp->soundSetting;
                wp->flags &= ~1;
                wp->state = 1;
            }
            if (wp->soundCursor >= 3) {
                wp->soundCursor = 0;
            }
            if (wp->soundCursor < 0) {
                wp->soundCursor = 2;
            }
            wp->tx = -74.0f;
            wp->ty = 4.0f + (50.0f - 50.0f * wp->soundCursor);
            break;
#else
            wp->flags |= 1;
            sound = wp->soundCursor;
            if (dir & DEMO_STICK_UP) {
                wp->soundCursor = wp->soundCursor - 1;
                SFX(5);
            } else if (dir & DEMO_STICK_DOWN) {
                wp->soundCursor = wp->soundCursor + 1;
                SFX(5);
            } else if (trg & PAD_BUTTON_A) {
                switch (sound) {
                    case 0:
                        OSSetSoundMode(0);
                        gp->soundMode = 0;
                        break;
                    case 1:
                        OSSetSoundMode(1);
                        gp->soundMode = 0;
                        break;
                    case 2:
                        OSSetSoundMode(1);
                        gp->soundMode = 1;
                        break;
                }
                if (OSGetSoundMode() == 0) {
                    SoundSetOutputMode(0);
                } else {
                    SoundSetOutputMode(1);
                }
                SFX(0x12);
                psndBGMOn(PSND_FADE_RESUME | PSND_FADE_UNDIP, NULL);
                psndENVOff(PSND_FADE_OUT);
                wp->soundSetting = wp->soundCursor;
                wp->flags &= ~1;
                wp->state = 1;
                break;
            } else if (trg & PAD_BUTTON_B) {
                SFX(0x13);
                psndBGMOn(PSND_FADE_RESUME | PSND_FADE_UNDIP, NULL);
                psndENVOff(PSND_FADE_OUT);
                wp->soundCursor = wp->soundSetting;
                if (OSGetSoundMode() == 0) {
                    SoundSetOutputMode(0);
                } else {
                    SoundSetOutputMode(1);
                }
                wp->flags &= ~1;
                wp->state = 1;
                break;
            }
            if (wp->soundCursor >= 3) {
                wp->soundCursor = 0;
            }
            if (wp->soundCursor < 0) {
                wp->soundCursor = 2;
            }
            if (wp->soundCursor != sound) {
                switch (wp->soundCursor) {
                    case 0:
                        SoundSetOutputMode(0);
                        break;
                    case 1:
                        SoundSetOutputMode(1);
                        break;
                    case 2:
                        SoundSetOutputMode(2);
                        break;
                }
                psndENVOn(PSND_FADE_RESTART | PSND_FADE_IN, (const char*)0x75);
            }
            wp->tx = -74.0f;
            wp->ty = 4.0f + (50.0f - 50.0f * wp->soundCursor);
            break;
#endif
        case 0xc8:
            wp->flags |= 1;
            if (dir & DEMO_STICK_UP) {
                wp->rumbleCursor--;
                SFX(5);
            } else if (dir & DEMO_STICK_DOWN) {
                wp->rumbleCursor++;
                SFX(5);
            } else if (trg & PAD_BUTTON_A) {
                gp->rumbleEnabled = wp->rumbleCursor == 0;
                SFX(0x12);
                wp->rumbleSetting = wp->rumbleCursor;
                wp->flags &= ~1;
                wp->state = 1;
                if (gp->rumbleEnabled) {
                    evtEntryType(evt_shake, 0, 0, 0);
                }
            } else if (trg & PAD_BUTTON_B) {
                SFX(0x13);
                wp->rumbleCursor = wp->rumbleSetting;
                wp->flags &= ~1;
                wp->state = 1;
            }
            if (wp->rumbleCursor >= 2) {
                wp->rumbleCursor = 0;
            }
            if (wp->rumbleCursor < 0) {
                wp->rumbleCursor = 1;
            }
            wp->tx = -74.0f;
            wp->ty = 4.0f + (30.0f - 50.0f * wp->rumbleCursor);
            break;
    }
    wp->x += (wp->tx - wp->x) / 4.0f;
    wp->y += (wp->ty - wp->y) / 4.0f;
    {
        f32 s = 2.0f * (f32)sin(gp->retraceCount / 8.0f);
        wp->x += __fabsf(s);
    }
#if VERSION <= VERSION_DEMO_US
    dispEntry(CAMERA_2D, 1000.0f, 0, loadDraw, NULL);
    return FALSE;
#else
    dispEntry(CAMERA_3D, 1000.0f, 0, loadDraw, NULL);
#endif
}

static inline void loadDrawBg(u32 id, f32 x0, f32 y0, f32 x1, f32 y1) {
    GXTexObj obj;
    Mtx m;
    f64 w;
    f64 h;

    TEXGetGXTexObjFromPalette(*wp->file->data, &obj, id);
    GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    h = __fabs(y0 - y1);
    w = __fabs(x1 - x0);
    PSMTXScale(m, (f32)w / GXGetTexObjWidth(&obj), (f32)h / GXGetTexObjHeight(&obj), 1.0f);
    GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(x0, y0, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(x0, y1, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(x1, y1, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(x1, y0, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
}

static void loadDraw(CameraId camera, void* param) {
    CameraEntry* cam = camGetPtr(CAMERA_2D);
    GXColor white = {255, 255, 255, 255};
    GXColor gray = {160, 160, 160, 255};
    GXColor dark = {128, 128, 128, 128};
#if VERSION >= VERSION_JP
    f32 vp[6];
    f32 proj[7];
    CameraEntry saved;
#endif
    char buf[0x20];
#if VERSION >= VERSION_JP
    char buf2[0x100];
#endif
    Mtx m;
    Mtx s;
#if VERSION >= VERSION_JP
    f32 x;
#endif
    f32 y;
    f32 w;
    u64 sec;
    WinDt* win1;
    s32 i;
    s32 j;
    s32 k;

    if (wp->state >= 0x20 && wp->state < 0x28) {
        return;
    }
#if VERSION >= VERSION_JP
    GXGetViewportv(vp);
    GXGetProjectionv(proj);
    GXSetProjection(cam->projection, cam->projType);
    saved = *camGetCurPtr();
    *camGetCurPtr() = *cam;
#endif
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){255, 255, 255, 255});
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    // FAKE: win1 reused as a cam alias before its win_dt web, so the win_dt web becomes a lifetime-split temp
    // (addi straight into win1's register, loop 1 iterates a copy) as in the target
    win1 = (WinDt*)cam;
    GXLoadPosMtxImm(((CameraEntry*)win1)->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    loadDrawBg(0x35, -304.0f, 240.0f, -272.0f, -240.0f);
    loadDrawBg(0x34, -272.0f, 240.0f, 272.0f, -240.0f);
    loadDrawBg(0x36, 272.0f, 240.0f, 304.0f, -240.0f);

    win1 = win_dt;
    for (i = 0; i < 9; i++) {
        GXColor col = gray;
        if (i == wp->slot) {
            col = white;
        }
#if VERSION <= VERSION_DEMO_US
        if (wp->state == 0x29 && (i == wp->copySrc || i == wp->copyDst)) {
#else
        if (wp->state == 0x33 && (i == wp->copySrc || i == wp->copyDst)) {
#endif
            col = white;
        }
        if (i == 4 && (wp->flags & 0x10)) {
            col = dark;
        }
        if (i == 5 && (wp->flags & 0x20)) {
            col = dark;
        }
        switch (win1[i].tex) {
            case 10:
            case 11:
            case 12:
            case 13: {
                col.a = 0xfe;
                winTexInit(*wp->file->data);
                winTexSet(0xe, (Vec){win1[i].x, win1[i].y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, col);
                winTexInit(*wp->file->data);
                winTexSet(win1[i].tex, (Vec){win1[i].x, 60.0f + win1[i].y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, col);
                break;
            }
            default: {
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(win1[i].tex, win1[i].tex2, (Vec){win1[i].x, win1[i].y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, col);
                break;
            }
        }
    }

    windowDispGX_Waku_col(0, (GXColor){255, 255, 255, 255}, -250.0f, 200.0f, 500.0f, 40.0f, 20.0f);
    FontDrawStart();
    {
        const char* msg = wp->msg;
#if VERSION <= VERSION_DEMO_US
        FontDrawString(-FontGetMessageWidth(msg) / 2, 192.0f, msg);
#else
        FontDrawMessage(-FontGetMessageWidth(msg) / 2, 192, msg);
#endif
    }

    for (i = 0; i < 4; i++, win1++) {
        CardSaveSlot* save = &cardGetFilePtr()->saves[i];
#if VERSION >= VERSION_US
        // US declares the slot fields in another order and reads them after the declarations (register order)
        u16 flags;
        OSTime time;
        u16 stars;
        s32 gsw0;
        char* name;
        s16 level;
        const char* str;
        s32 hours;
        s32 mins;
        flags = save->data.flags;
        level = save->data.pouch.level;
        time = save->data.global.retraceLocalTime;
        stars = save->data.pouch.starPowersObtained;
        gsw0 = save->data.global.gsw0;
        name = (char*)save->data.global.playerName;
#else
        u16 flags = save->data.flags;
        s16 level = save->data.pouch.level;
        OSTime time = save->data.global.retraceLocalTime;
        u16 stars = save->data.pouch.starPowersObtained;
        s32 gsw0 = save->data.global.gsw0;
#endif
#if VERSION <= VERSION_DEMO_US
        // demo: the clamp compares the 64-bit hour count, and name is declared last (register order)
        const char* str;
        u64 hours;
        s32 mins;
        char* name = (char*)save->data.global.playerName;
#elif VERSION == VERSION_JP
        char* name = (char*)save->data.global.playerName;
        const char* str;
        s32 hours;
        s32 mins;
#endif

        FontDrawStart();
        FontDrawColor((GXColor){192, 192, 192, 255});
        if (i == wp->slot) {
            FontDrawColor((GXColor){255, 255, 255, 255});
        }
        FontDrawScale(0.6f);
        FontDrawEdge();
#if VERSION >= VERSION_US
        if ((u32)gp->language == 0) {
            str = "データ";
        } else {
            str = msgSearch("msg_mcard_file");
        }
        sprintf(buf, "%s%s", str, winZenkakuStr(i + 1));
#elif VERSION <= VERSION_DEMO_US
        sprintf(buf, "データ%d", i + 1);
#else
    sprintf(buf, "データ%s", winZenkakuStr(i + 1));
#endif
        FontDrawString(win1->x - 100.0f, 84.0f + win1->y, buf);
        FontDrawEdgeOff();
        FontDrawScale(1.0f);
        FontDrawColor((GXColor){32, 32, 32, 255});
        if (i == wp->slot) {
            FontDrawColor((GXColor){0, 0, 0, 255});
        }
        if (flags & 2) {
#if VERSION >= VERSION_US
            if ((u32)gp->language == 0) {
                str = "こわれています";
            } else {
                str = msgSearch("msg_mcard_kowareteru");
            }
            w = FontGetMessageWidth(str);
            FontDrawStart();
            FontDrawMessage(win1->x - w / 2.0f, 28.0f + win1->y, str);
            str = msgSearch("msg_mcard_kowaretitle");
            FontDrawString(win1->x - FontGetMessageWidth(str) / 2, 70.0f + win1->y, str);
#else
            str = "こわれています";
            FontDrawString(win1->x - FontGetMessageWidth(str) / 2.0f, 12.0f + win1->y, str);
#endif
        } else if (flags & 1) {
#if VERSION >= VERSION_US
            if ((u32)gp->language == 0) {
                str = "ニューゲーム";
            } else {
                str = msgSearch("msg_mcard_new_game");
            }
#else
            str = "ニューゲーム";
#endif
            FontDrawString(win1->x - FontGetMessageWidth(str) / 2.0f, 12.0f + win1->y, str);
        } else if (gsw0 == 0) {
#if VERSION >= VERSION_US
            if ((u32)gp->language == 0) {
                str = "はじめから";
            } else {
                str = msgSearch("msg_mcard_hajimekara");
            }
#else
            str = "はじめから";
#endif
            FontDrawString(win1->x - FontGetMessageWidth(str) / 2.0f, 12.0f + win1->y, str);
            if (strlen(name) != 0) {
                FontDrawString(win1->x - FontGetMessageWidth(name) / 2, 70.0f + win1->y, name);
            }
        } else {
#if VERSION <= VERSION_DEMO_US
            w = FontGetMessageWidth("\x82\x57\x82\x57");
            sec = OSTicksToSeconds(time);
            hours = (u64)sec / 3600;
            mins = ((u64)sec % 3600) / 60;
            if (hours > 99) {
                hours = 99;
            }
            FontDrawStringPitch(win1->x - 100.0f, 30.0f + win1->y, 18.0f, "レベル");
            FontDrawStringPitch(win1->x - 100.0f, win1->y, 18.0f, "プレイじかん");
            if (strlen(name) != 0) {
                FontDrawString(win1->x - FontGetMessageWidth(name) / 2, 70.0f + win1->y, name);
            }
            sprintf(buf, "%d", level);
            y = FontGetMessageWidth(buf);
            FontDrawString(60.0f + win1->x + (w - y), 30.0f + win1->y, buf);
            sprintf(buf, "%02d", (s32)hours);
            y = FontGetMessageWidth(buf);
            FontDrawString(10.0f + win1->x + (w - y), win1->y, buf);
            sprintf(buf, "%02d", mins);
            y = FontGetMessageWidth(buf);
            FontDrawString(60.0f + win1->x + (w - y), win1->y, buf);
            PSMTXTrans(m, 58.0f + win1->x, win1->y - 20.0f, 0.0f);
            iconDispGxCol(m, 4, ICON_201, (GXColor){0, 0, 0, 255});
            // FAKE: y read through a byte offset so the loop-invariant &win1->y becomes a hoisted @ temp (target pop order)
            for (k = 0; k < 7; k++) {
                if (stars & (1 << (k + 1))) {
                    PSMTXTrans(m, (win1->x - 106.0f) + k * 32, *(f32*)((u8*)win1 + offsetof(WinDt, y)) - 52.0f, 0.0f);
                    PSMTXScale(s, 0.7f, 0.7f, 0.7f);
                    PSMTXConcat(m, s, m);
                    iconDispGxCol(m, 4, (u16)stone_id[k], i == wp->slot ? white : gray);
                }
            }
#else
#if VERSION >= VERSION_US
            FontGetMessageWidth((u32)gp->language != 0 ? "88" : "\x82\x57\x82\x57");
#else
            FontGetMessageWidth("\x82\x57\x82\x57");
#endif
            sec = OSTicksToSeconds(time);
            if (sec > 359999) {
                hours = 99;
                mins = 59;
            } else {
                hours = (u64)sec / 3600;
                mins = ((u64)sec % 3600) / 60;
            }
            if (strlen(name) != 0) {
                FontDrawString(win1->x - FontGetMessageWidth(name) / 2, 70.0f + win1->y, name);
            }
#if VERSION >= VERSION_US
            // US: localised labels; a play time wider than 200 is squeezed to fit
            sprintf(buf2, (u32)gp->language != 0 ? "%s %s" : "%s　%s", msgSearch("msg_menu_mario_level"), winZenkakuStr(level));
            FontDrawString(win1->x - FontGetMessageWidth(buf2) / 2.0f, 30.0f + win1->y, buf2);
            sprintf(buf2, (u32)gp->language != 0 ? "%s " : "%s　", msgSearch("msg_menu_mario_num_playtime"));
            strcat(buf2, winZenkakuStrPad(hours, 2));
            strcat(buf2, " ");
            strcat(buf2, winZenkakuStrPad(mins, 2));
            w = FontGetMessageWidth(buf2);
            if (w > 200.0f) {
                FontDrawScaleVec((Vec){200.0f / w, 1.0f, 1.0f});
                w = 200.0f;
            }
            FontDrawString(win1->x - w / 2.0f, win1->y, buf2);
            FontDrawScaleVec((Vec){1.0f, 1.0f, 1.0f});
            w = FontGetMessageWidth(buf2);
            sprintf(buf2, (u32)gp->language != 0 ? "%s " : "%s　", msgSearch("msg_menu_mario_num_playtime"));
            strcat(buf2, winZenkakuStrPad(hours, 2));
            x = FontGetMessageWidth(buf2);
            if (w > 200.0f) {
                x *= 200.0f / w;
                x += 1600.0f / w;
                w = 200.0f;
            } else {
                x += 8.0f;
            }
            PSMTXTrans(m, x + (win1->x - w / 2.0f), 1.0f + (win1->y - 22.0f), 0.0f);
#else
            sprintf(buf2, "レベル　%s", winZenkakuStr(level));
            FontDrawString(win1->x - FontGetMessageWidth(buf2) / 2.0f, 30.0f + win1->y, buf2);
            strcpy(buf2, "プレイじかん　");
            strcat(buf2, winZenkakuStrPad(hours, 2));
            strcat(buf2, " ");
            strcat(buf2, winZenkakuStrPad(mins, 2));
            w = FontGetMessageWidth(buf2);
            FontDrawString(win1->x - w / 2.0f, win1->y, buf2);
            strcpy(buf2, "プレイじかん　");
            strcat(buf2, winZenkakuStrPad(hours, 2));
            x = FontGetMessageWidth(buf2);
            PSMTXTrans(m, 8.0f + (x + (win1->x - w / 2.0f)), 1.0f + (win1->y - 22.0f), 0.0f);
#endif
            PSMTXScale(s, 1.5f, 1.5f, 1.5f);
            PSMTXConcat(m, s, m);
            iconDispGxCol(m, 0, ICON_201, (GXColor){0, 0, 0, 255});
            // FAKE: y read through a byte offset so the loop-invariant &win1->y becomes a hoisted @ temp (target pop order)
            for (k = 0; k < 7; k++) {
                if (stars & (1 << (k + 1))) {
                    PSMTXTrans(m, (win1->x - 106.0f) + k * 32, *(f32*)((u8*)win1 + offsetof(WinDt, y)) - 52.0f, 0.0f);
                    iconDispGxCol(m, 0, (u16)stone_id[k], i == wp->slot ? white : gray);
                }
            }
#endif
        }
    }

    if (wp->flags & 1) {
        wp->alpha += 0.05f;
    } else {
        wp->alpha -= 0.05f;
    }
    if (wp->alpha < 0.0f) {
        wp->alpha = 0.0f;
    }
    if (wp->alpha > 1.0f) {
        wp->alpha = 1.0f;
    }
    nameMaskGX(wp->alpha);

    if (wp->state >= 100 && wp->state < 200) {
        winTexInit(*wp->file->data);
        winTexSet(0xf, (Vec){0.0f, 0.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
        winTexInit_x2(*wp->file->data);
        winTexSet_x2(0x13, 0x1f, (Vec){0.0f, 100.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
        for (i = 0; i < 3; i++) {
            if (i == wp->soundCursor) {
                winTexInit(*wp->file->data);
                winTexSet(0x33, (Vec){0.0f, 50 - i * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 64});
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(i + 0x15, 0x33, (Vec){-4.0f, 54 - i * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
            } else {
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(i + 0x15, 0x33, (Vec){0.0f, 50 - i * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
            }
        }
    }

    if (wp->state >= 200 && wp->state < 300) {
        winTexInit(*wp->file->data);
        winTexSet(0xf, (Vec){0.0f, 0.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
        winTexInit_x2(*wp->file->data);
        winTexSet_x2(0x14, 0x1f, (Vec){0.0f, 100.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
        for (i = 0; i < 2; i++) {
            if (i == wp->rumbleCursor) {
                winTexInit(*wp->file->data);
                winTexSet(RUMBLE_SEL_TEX, (Vec){0.0f, 30 - i * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 64});
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(i + 0x18, RUMBLE_SEL_TEX, (Vec){-4.0f, 34 - i * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
            } else {
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(i + 0x18, RUMBLE_SEL_TEX, (Vec){0.0f, 30 - i * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
            }
        }
    }

    if (wp->state == 0x33 && wp->copyDst < 4) {
        f32 angle[4][4] = {
            {0.0f, -90.0f, -180.0f, -135.0f},
            {90.0f, 0.0f, 135.0f, 180.0f},
            {0.0f, -45.0f, 0.0f, -90.0f},
            {45.0f, 0.0f, 90.0f, 0.0f},
        };
        f32 cx;
        f32 cy;
        if (!(f32)fmod(angle[wp->copySrc][wp->copyDst], 90.0)) {
            f32 c0 = wp->copySrc % 2;
            f32 r0 = wp->copySrc / 2;
            f32 r1 = wp->copyDst / 2;
            if (r0 == r1) {
                cx = 0.0f;
                cy = 120.0f - 140.0f * r0;
            } else {
                cx = -150.0f + 300.0f * c0;
                cy = 50.0f;
            }
        } else {
            cx = 0.0f;
            cy = 50.0f;
        }
        cy -= 40.0f;
        winTexInit(*wp->file->data);
        winTexSetRot(0x1d, (Vec){2.0f + cx, cy - 2.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 128}, angle[wp->copySrc][wp->copyDst]);
        winTexSetRot(0x1d, (Vec){cx, cy, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white, angle[wp->copySrc][wp->copyDst]);
    }

    if (!(wp->flags & 0x40)) {
        winTexInit(*wp->file->data);
        winTexSet(0, (Vec){2.0f + wp->x, wp->y - 2.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 128});
        winTexSet(0, (Vec){wp->x, wp->y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    }

#if VERSION >= VERSION_JP
    GXSetViewport(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
    GXSetProjectionv(proj);
    *camGetCurPtr() = saved;
#endif
}

#if VERSION >= VERSION_JP
s32 stone_id[7] = {ICON_197, ICON_198, ICON_19A, ICON_19C, ICON_19D, ICON_199, ICON_19B};

static EVT_BEGIN(evt_shake)
    CALL(evt_sub_rumble_onoff, 0, 0)
    WAIT_MS(150)
    CALL(evt_sub_rumble_onoff, 1, 0)
    RETURN
EVT_END()
#endif

EVT_BEGIN(evt_continue)
    CALL(evt_sub_animgroup_async, STRING("OFF_f_in_out_mario"))
    CALL(evt_sub_animgroup_async, STRING("OFF_f_in_out_kuppa"))
    CALL(evt_sub_animgroup_async, STRING("OFF_f_in_out_peach"))
    RETURN
EVT_END()
#pragma defer_codegen off
static void continueGame(void) {
    cardCopy2Main(wp->slot);
    gp->saveSlot = wp->slot;
    gp->lastSlot = wp->slot;
    marioPartyKill();
    {
        MarioWork* m = marioGetPtr();
        m->prevPartyMemberId[0] = 0;
        m->prevPartyMemberId[1] = 0;
    }
    psndSetFlag(PSND_FLAG_SFX_OFF);
    marioPartyEntry(gp->savePartyId[0]);
    marioPartyEntry(gp->savePartyId[1]);
    psndClearFlag(PSND_FLAG_SFX_OFF);
    countDownSaveReStart();
    gp->flags |= GLOBAL_FLAG_LOADED;
    switch (swByteGet(GSW_SAVE_RESUME_KIND)) {
        case 0:
            gp->areaFadeInType = FADE_NONE;
            gp->areaFadeOutType = FADE_CURTAIN_SIDES_A2;
            seqSetSeq(SEQ_MAP_CHANGE, gp->currentMapName, 0);
            break;
        case 1:
            gp->areaFadeInType = FADE_STORY_PEACH_A2;
            gp->areaFadeOutType = FADE_STORY_PEACH_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "aji_10", 0);
            break;
        case 2:
            gp->areaFadeInType = FADE_STORY_BOWSER_A2;
            gp->areaFadeOutType = FADE_STORY_BOWSER_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "kpa_00", 0);
            break;
        case 3:
            gp->areaFadeInType = FADE_STORY_MARIO_A2;
            gp->areaFadeOutType = FADE_STORY_MARIO_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "nok_01", "nokotarou");
            break;
        case 4:
            gp->areaFadeInType = FADE_STORY_PEACH_A2;
            gp->areaFadeOutType = FADE_STORY_PEACH_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "aji_10", 0);
            break;
        case 5:
            gp->areaFadeInType = FADE_STORY_BOWSER_A2;
            gp->areaFadeOutType = FADE_STORY_BOWSER_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "hei_00", 0);
            break;
        case 6:
            gp->areaFadeInType = FADE_STORY_MARIO_A2;
            gp->areaFadeOutType = FADE_STORY_MARIO_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "mri_00", 0);
            break;
        case 7:
            gp->areaFadeInType = FADE_STORY_PEACH_A2;
            gp->areaFadeOutType = FADE_STORY_PEACH_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "aji_10", 0);
            break;
        case 8:
            gp->areaFadeInType = FADE_STORY_BOWSER_A2;
            gp->areaFadeOutType = FADE_STORY_BOWSER_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "mri_01", 0);
            break;
        case 9:
            gp->areaFadeInType = FADE_STORY_MARIO_A2;
            gp->areaFadeOutType = FADE_STORY_MARIO_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "tou_02", 0);
            break;
        case 10:
#if VERSION <= VERSION_DEMO_US
            gp->areaFadeInType = FADE_STORY_PEACH_A2;
            gp->areaFadeOutType = FADE_STORY_PEACH_A3;
#else
            gp->areaFadeInType = FADE_NONE;
            gp->areaFadeOutType = FADE_CURTAIN_SIDES_A2;
#endif
            seqSetSeq(SEQ_MAP_CHANGE, "usu_00", 0);
            break;
        case 11:
            gp->areaFadeInType = FADE_STORY_BOWSER_A2;
            gp->areaFadeOutType = FADE_STORY_BOWSER_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "gor_04", 0);
            break;
        case 12:
            gp->areaFadeInType = FADE_STORY_MARIO_A2;
            gp->areaFadeOutType = FADE_STORY_MARIO_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "usu_00", 0);
            break;
        case 13:
#if VERSION <= VERSION_DEMO_US
            gp->areaFadeInType = FADE_STORY_MARIO_A2;
            gp->areaFadeOutType = FADE_STORY_MARIO_A3;
#else
            gp->areaFadeInType = FADE_NONE;
            gp->areaFadeOutType = FADE_CURTAIN_SIDES_A2;
#endif
            seqSetSeq(SEQ_MAP_CHANGE, "muj_12", 0);
            break;
        case 14:
            gp->areaFadeInType = FADE_STORY_BOWSER_A2;
            gp->areaFadeOutType = FADE_STORY_BOWSER_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "usu_00", 0);
            break;
        case 15:
            gp->areaFadeInType = FADE_STORY_MARIO_A2;
            gp->areaFadeOutType = FADE_STORY_MARIO_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "muj_00", 0);
            break;
        case 16:
#if VERSION <= VERSION_DEMO_US
            gp->areaFadeInType = FADE_STORY_MARIO_A2;
            gp->areaFadeOutType = FADE_STORY_MARIO_A3;
#else
            gp->areaFadeInType = FADE_NONE;
            gp->areaFadeOutType = FADE_CURTAIN_SIDES_A2;
#endif
            seqSetSeq(SEQ_MAP_CHANGE, "pik_03", "next");
            break;
        case 17:
            gp->areaFadeInType = FADE_STORY_BOWSER_A2;
            gp->areaFadeOutType = FADE_STORY_BOWSER_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "gor_01", 0);
            break;
        case 18:
            gp->areaFadeInType = FADE_STORY_MARIO_A2;
            gp->areaFadeOutType = FADE_STORY_MARIO_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "gor_04", "resha_return");
            break;
        case 19:
            gp->areaFadeInType = FADE_STORY_BOWSER_A2;
            gp->areaFadeOutType = FADE_STORY_BOWSER_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "pik_01", 0);
            break;
        case 20:
            gp->areaFadeInType = FADE_STORY_MARIO_A2;
            gp->areaFadeOutType = FADE_STORY_MARIO_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "aji_18", "e_bero");
            break;
        case 21:
            gp->areaFadeInType = FADE_STORY_MARIO_A2;
            gp->areaFadeOutType = FADE_STORY_MARIO_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "gor_00", 0);
            break;
        case 22:
#if VERSION <= VERSION_DEMO_US
            gp->areaFadeInType = FADE_STORY_MARIO_A2;
            gp->areaFadeOutType = FADE_STORY_MARIO_A3;
#else
            gp->areaFadeInType = FADE_NONE;
            gp->areaFadeOutType = FADE_CURTAIN_SIDES_A2;
#endif
            seqSetSeq(SEQ_MAP_CHANGE, "jin_04", 0);
            break;
        case 23:
            loadNewGameSetup();
            seqSetSeq(SEQ_MAP_CHANGE, "aaa_00", "prologue");
            break;
        case 24:
            gp->areaFadeInType = FADE_STORY_PEACH_A2;
            gp->areaFadeOutType = FADE_STORY_PEACH_A3;
            seqSetSeq(SEQ_MAP_CHANGE, "aji_10", 0);
            break;
    }
}
#pragma defer_codegen reset
