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

typedef struct LoadWork {
    u16 flags;          // 0x0
    FileEntry* file;    // 0x4
    f32 x;              // 0x8
    f32 y;              // 0xC
    f32 tx;             // 0x10
    f32 ty;             // 0x14
    s32 unk18;          // 0x18
    s32 unk1C;          // 0x1C
    s32 slot;           // 0x20
    s32 unk24;          // 0x24
    s32 unk28;          // 0x28
    f32 alpha;          // 0x2C
    s32 unk30;          // 0x30
    s32 unk34;          // 0x34
    const char* msg;    // 0x38
    EventEntry* evt;    // 0x3C
    s32 unk40;          // 0x40
    s32 unk44;          // 0x44
    s32 unk48;          // 0x48
} LoadWork;

typedef struct WinDt {
    f32 x;      // 0x0
    f32 y;      // 0x4
    f32 ofsX;   // 0x8
    f32 ofsY;   // 0xC
    s32 unk10;  // 0x10
    s32 unk14;  // 0x14
    u8 next[4]; // 0x18
} WinDt;

extern s32 evt_memcard_check[];
extern s32 evt_memcard_start[];
extern s32 evt_memcard_save[];
extern s32 evt_memcard_delete[];
extern s32 evt_memcard_copy[];
extern s32 evt_sub_rumble_onoff(EventEntry* evt, BOOL isFirstCall);
extern s32 evt_sub_animgroup_async(EventEntry* evt, BOOL isFirstCall);
extern void SoundSetOutputMode(s32 mode);
extern void OSSetSoundMode(u32 mode);
extern BOOL psndENVOn(u32 flags, const char* name);
extern BOOL psndBGMOff(u32 flags);
void nameEntOn(s32 type);
void nameEntOff(void);
const char* nameEntGetName(void);
BOOL nameEntWait(void);
BOOL nameEntPrepare(void);
BOOL nameEntIsCancel(void);
double sin(double);
double fmod(double, double);
static inline float fabsf(float x) { return (float)__fabs(x); }
void winTexInit_x2(TEXPalette* texture);
void winTexSet_x2(u32 id1, u32 id2, Vec translate, Vec scale, GXColor color);
void winTexSetRot(u32 id, Vec translate, Vec scale, GXColor color, f32 rot);
void nameMaskGX(f32 alpha);
const char* unk_8016af5c(s32 num, s32 digits);
void FontDrawScale(f32 scale);
void FontDrawString(f32 x, f32 y, const char* str);
void FontDrawEdge(void);
void FontDrawEdgeOff(void);
void loadMain(SequenceWork* seq);
void loadDraw(CameraId camera, void* param);
void continueGame(void);


__declspec(section ".data") f32 lbl_80349DE8[] = { -1.0f, 1.0f };
__declspec(section ".data") static f32 negone_one_374[] = { -1.0f, 1.0f };
__declspec(section ".data") f32 lbl_80349DF8[] = { 1.0f, -1.0f };
__declspec(section ".data") static f32 one_negone_373[] = { 1.0f, -1.0f };
__declspec(section ".data") f32 lbl_80349E08[] = { -1.0f, 1.0f };
__declspec(section ".data") static f32 negone_one_360[] = { -1.0f, 1.0f };
__declspec(section ".data") f32 lbl_80349E18[] = { 1.0f, -1.0f };
__declspec(section ".data") static f32 one_negone_359[] = { 1.0f, -1.0f };

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

extern s32 stone_id[];
static s32 evt_shake[12];
extern s32 evt_continue[];

s32 unk_800f2398(EventEntry* evt, BOOL isFirstCall) {
    fadeReset(4);
    wp->unk48 = evt->printWindowId;
    return 2;
}

void seq_loadInit(SequenceWork* seq) {
    memset(wp, 0, sizeof(LoadWork));
}

void seq_loadExit(SequenceWork* seq) {
    if (wp->file != NULL) {
        fileFree(wp->file);
    }
    wp->file = NULL;
}

static inline BOOL loadStart(void) {
    if (fileAsyncf(4, NULL, "%s/w/jp/name.tpl\0\0\0", getMarioStDvdRoot()) != 0U) {
        wp->file = fileAllocf(4, "%s/w/jp/name.tpl\0\0\0", getMarioStDvdRoot());
        return TRUE;
    }
    return FALSE;
}

void seq_loadMain(SequenceWork* seq) {
    switch (seq->state) {
        case 0:
            if (loadStart()) {
                seq->state++;
            }
            break;
        case 1:
            wp->evt = evtEntryType(evt_memcard_check, 0, 0, 0);
            if (wp->flags & 0x80) {
                wp->flags &= ~0x80;
                *(s32*)((u8*)wp->evt + 0xC4) = 1;
                wp->evt->printWindowId = wp->unk48;
            }
            seq->state++;
            break;
        case 2:
            if (evtCheckID(wp->evt->eventId) == 0) {
                if (evtGetValue(NULL, (s32)0xFAA2B580) != 1) {
                    seqSetSeq(SEQ_TITLE, NULL, NULL);
                } else {
                    wp->evt = NULL;
                    seq->state++;
                    wp->unk18 = 0;
                    wp->unk1C = cardGetCode();
                    wp->flags &= ~0x40;
                    if (OSGetSoundMode() == 0) {
                        SoundSetOutputMode(0);
                        gp->unk1274 = 0;
                        wp->unk40 = 0;
                    } else {
                        SoundSetOutputMode(1);
                        if (gp->unk1274 == 0) {
                            wp->unk40 = 1;
                        } else {
                            wp->unk40 = 2;
                        }
                    }
                    wp->unk44 = gp->unk1294 == 0;
                    wp->unk24 = wp->unk40;
                    wp->unk28 = wp->unk44;
                    wp->slot = gp->unk11B8;
                    wp->x = win_dt[wp->slot].x;
                    wp->y = win_dt[wp->slot].y;
                }
            }
            break;
        case 3: {
            GXColor c = {0, 0, 0, 255};
            fadeEntry(0x1c, 0, c);
            seq->state++;
            break;
        }
        case 4:
            loadMain(seq);
            break;
    }
}

#define SFX(id) psndSFXOn((const char*)(id))
#define SLOTFLAGS(i) (cardGetFilePtr()->saves[(i)].data.flags)

void loadMain(SequenceWork* seq) {
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
    if (wp->unk1C != code) {
        trg = 0;
        dir = 0;
    }
    wp->unk1C = code;
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

    switch (wp->unk18) {
        case 0:
            wp->unk18++;
        case 1:
            wp->msg = msgSearch("msg_savefile_select");
            prev = wp->slot;
            if (dir & 0x1000) {
                wp->slot = win_dt[prev].next[0];
            } else if (dir & 0x2000) {
                wp->slot = win_dt[prev].next[1];
            } else if (dir & 0x4000) {
                wp->slot = win_dt[prev].next[2];
            } else if (dir & 0x8000) {
                wp->slot = win_dt[prev].next[3];
            } else if (trg & 0x100) {
                flags = SLOTFLAGS(wp->slot);
                switch (wp->slot) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        if (flags & 2) {
                            SFX(0x13);
                        } else if (flags & 1) {
                            wp->unk18 = 0x1e;
                            SFX(0x12);
                        } else {
                            wp->unk18 = 0x14;
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
                                wp->unk18 = 0x28;
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
                                wp->unk18 = 0x32;
                            } else {
                                SFX(0x13);
                            }
                        }
                        break;
                    case 6:
                        SFX(0x13);
                        wp->unk18 = 0xa;
                        break;
                    case 7:
                        SFX(0x12);
                        psndBGMOff(0x800);
                        wp->unk18 = 0x64;
                        break;
                    case 8:
                        SFX(0x12);
                        wp->unk18 = 0xc8;
                        break;
                }
            } else if (trg & 0x200) {
                SFX(0x13);
                wp->unk18 = 0xa;
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
            fadeEntry(0x1b, 0, (GXColor){0, 0, 0, 255});
            wp->unk18++;
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
            wp->unk18++;
            break;
        case 0x15:
            if (!evtCheckID(wp->evt->eventId)) {
                wp->flags &= ~0x40;
                if (evtGetValue(NULL, (s32)0xFD050F80) == 1) {
                    wp->unk18++;
                } else {
                    wp->unk18 = 1;
                }
            }
            break;
        case 0x16:
            fadeEntry(0x1b, 0, (GXColor){0, 0, 0, 255});
            psndBGMOff_f_d(0x200, 2000, 0);
            wp->unk18++;
            break;
        case 0x17:
            if (fadeIsFinish()) {
                wp->flags |= 0x40;
                wp->evt = evtEntryType(evt_continue, 0, 0, 0);
                wp->unk18++;
            }
            break;
        case 0x18:
            if (!evtCheckID(wp->evt->eventId)) {
                wp->flags &= ~0x40;
                continueGame();
            }
            break;
        case 0x1e:
            fadeEntry(0x1b, 0, (GXColor){0, 0, 0, 255});
            wp->unk18++;
            break;
        case 0x1f:
            if (fadeIsFinish()) {
                wp->unk18++;
            }
            break;
        case 0x20:
            if (nameEntPrepare()) {
                nameEntOn(0);
                fadeEntry(0x1c, 0, (GXColor){0, 0, 0, 255});
                wp->unk18++;
            }
            break;
        case 0x21:
            if (fadeIsFinish() && !nameEntWait()) {
                fadeEntry(0x18, 0, (GXColor){0, 0, 0, 255});
                if (!nameEntIsCancel()) {
                    psndBGMOff_f_d(0x200, 3000, 0);
                }
                wp->unk18++;
            }
            break;
        case 0x22:
            if (fadeIsFinish()) {
                nameEntOff();
                if (nameEntIsCancel()) {
                    fadeEntry(0x1c, 0, (GXColor){0, 0, 0, 255});
                    wp->unk18 = 1;
                } else {
                    strcpy((char*)gp->field_0x11BC, nameEntGetName());
                    gp->unk11B8 = wp->slot;
                    stg0_00_init();
                    gp->saveSlot = wp->slot;
                    marioPartyKill();
                    {
                        MarioWork* m = marioGetPtr();
                        m->prevPartyMemberId[0] = 0;
                        m->prevPartyMemberId[1] = 0;
                    }
                    gp->areaFadeInType = 0;
                    gp->areaFadeOutType = 25;
                    swInit();
                    swByteSet(0, 0);
                    if (code == 0) {
                        gp->saveSlot = wp->slot;
                        wp->evt = evtEntryType(evt_memcard_save, 0, 0, 0);
                        wp->evt->lwData[0] = 0x17;
                        wp->unk18++;
                    } else {
                        seqSetSeq(SEQ_MAP_CHANGE, "aaa_00", "prologue");
                    }
                }
            }
            break;
        case 0x23:
            if (!evtCheckID(wp->evt->eventId)) {
                seqSetSeq(SEQ_MAP_CHANGE, "aaa_00", "prologue");
            }
            break;
        case 0x28:
            wp->msg = msgSearch("msg_savefile_delete_select");
            prev = wp->slot;
            if (dir & 0x1000) {
                wp->slot = win_dt2[prev].next[0];
            } else if (dir & 0x2000) {
                wp->slot = win_dt2[prev].next[1];
            } else if (dir & 0x4000) {
                wp->slot = win_dt2[prev].next[2];
            } else if (dir & 0x8000) {
                wp->slot = win_dt2[prev].next[3];
            } else if (trg & 0x100) {
                if (prev < 4) {
                    flags = SLOTFLAGS(wp->slot);
                    if ((flags & 2) || !(flags & 1)) {
                        SFX(0x12);
                        wp->unk18++;
                    } else {
                        SFX(0x13);
                    }
                } else {
                    wp->slot = 4;
                    wp->unk18 = 1;
                    SFX(0x13);
                }
            } else if (trg & 0x200) {
                wp->slot = 4;
                wp->unk18 = 1;
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
            wp->unk18++;
            break;
        case 0x2a:
            if (!evtCheckID(wp->evt->eventId)) {
                if (evtGetValue(NULL, (s32)0xFAA2B580) == 0) {
                    wp->flags &= ~0x40;
                    wp->slot = 4;
                    wp->unk18 = 1;
                } else {
                    wp->flags |= 0x80;
                    seq->state = 1;
                    return;
                }
            }
            break;
        case 0x32:
            wp->msg = msgSearch("msg_savefile_copy_select");
            prev = wp->slot;
            if (dir & 0x1000) {
                wp->slot = win_dt2[prev].next[0];
            } else if (dir & 0x2000) {
                wp->slot = win_dt2[prev].next[1];
            } else if (dir & 0x4000) {
                wp->slot = win_dt2[prev].next[2];
            } else if (dir & 0x8000) {
                wp->slot = win_dt2[prev].next[3];
            } else if (trg & 0x100) {
                if (prev < 4) {
                    flags = SLOTFLAGS(wp->slot);
                    if (!(flags & 2) && !(flags & 1)) {
                        wp->unk18 = 0x33;
                        wp->unk30 = wp->slot;
                        wp->unk34 = (wp->unk30 + 1) % 4;
                        wp->slot = wp->unk34;
                        SFX(0x12);
                    }
                } else {
                    wp->slot = 5;
                    wp->unk18 = 1;
                    SFX(0x13);
                }
            } else if (trg & 0x200) {
                wp->slot = 5;
                wp->unk18 = 1;
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
            if (dir & 0x1000) {
                do {
                    wp->slot = win_dt3[wp->slot].next[0];
                } while (wp->slot == wp->unk30);
            } else if (dir & 0x2000) {
                do {
                    wp->slot = win_dt3[wp->slot].next[1];
                } while (wp->slot == wp->unk30);
            } else if (dir & 0x4000) {
                do {
                    wp->slot = win_dt3[wp->slot].next[2];
                } while (wp->slot == wp->unk30);
            } else if (dir & 0x8000) {
                do {
                    wp->slot = win_dt3[wp->slot].next[3];
                } while (wp->slot == wp->unk30);
            } else if (trg & 0x100) {
                wp->unk18 = 0x34;
                wp->unk34 = wp->slot;
                SFX(0x12);
            } else if (trg & 0x200) {
                wp->slot = wp->unk30;
                wp->unk18 = 0x32;
                SFX(0x13);
            }
            if (prev != wp->slot && wp->slot < 4) {
                SFX(9);
            }
            wp->unk34 = wp->slot;
            wp->tx = win_dt2[wp->slot].x + win_dt2[wp->slot].ofsX;
            wp->ty = win_dt2[wp->slot].y + win_dt2[wp->slot].ofsY;
            break;
        case 0x34:
            wp->flags |= 0x40;
            wp->evt = evtEntryType(evt_memcard_copy, 0, 0, 0);
            wp->evt->lwData[0] = wp->unk30;
            wp->evt->lwData[1] = wp->unk34;
            wp->unk18++;
            break;
        case 0x35:
            if (!evtCheckID(wp->evt->eventId)) {
                if (evtGetValue(NULL, (s32)0xFAA2B580) == 0) {
                    wp->flags &= ~0x40;
                    wp->slot = 5;
                    wp->unk18 = 1;
                } else {
                    wp->flags |= 0x80;
                    seq->state = 1;
                    return;
                }
            }
            break;
        case 0x64:
            wp->flags |= 1;
            sound = wp->unk24;
            if (dir & 0x1000) {
                wp->unk24 = wp->unk24 - 1;
                SFX(5);
            } else if (dir & 0x2000) {
                wp->unk24 = wp->unk24 + 1;
                SFX(5);
            } else if (trg & 0x100) {
                switch (sound) {
                    case 0:
                        OSSetSoundMode(0);
                        gp->unk1274 = 0;
                        break;
                    case 1:
                        OSSetSoundMode(1);
                        gp->unk1274 = 0;
                        break;
                    case 2:
                        OSSetSoundMode(1);
                        gp->unk1274 = 1;
                        break;
                }
                if (OSGetSoundMode() == 0) {
                    SoundSetOutputMode(0);
                } else {
                    SoundSetOutputMode(1);
                }
                SFX(0x12);
                psndBGMOn(0xa0, NULL);
                psndENVOff(0x200);
                wp->unk40 = wp->unk24;
                wp->flags &= ~1;
                wp->unk18 = 1;
                break;
            } else if (trg & 0x200) {
                SFX(0x13);
                psndBGMOn(0xa0, NULL);
                psndENVOff(0x200);
                wp->unk24 = wp->unk40;
                if (OSGetSoundMode() == 0) {
                    SoundSetOutputMode(0);
                } else {
                    SoundSetOutputMode(1);
                }
                wp->flags &= ~1;
                wp->unk18 = 1;
                break;
            }
            if (wp->unk24 >= 3) {
                wp->unk24 = 0;
            }
            if (wp->unk24 < 0) {
                wp->unk24 = 2;
            }
            if (wp->unk24 != sound) {
                switch (wp->unk24) {
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
                psndENVOn(0x110, (const char*)0x75);
            }
            wp->tx = -74.0f;
            wp->ty = 4.0f + (50.0f - 50.0f * wp->unk24);
            break;
        case 0xc8:
            wp->flags |= 1;
            if (dir & 0x1000) {
                wp->unk28--;
                SFX(5);
            } else if (dir & 0x2000) {
                wp->unk28++;
                SFX(5);
            } else if (trg & 0x100) {
                gp->unk1294 = wp->unk28 == 0;
                SFX(0x12);
                wp->unk44 = wp->unk28;
                wp->flags &= ~1;
                wp->unk18 = 1;
                if (gp->unk1294) {
                    evtEntryType(evt_shake, 0, 0, 0);
                }
            } else if (trg & 0x200) {
                SFX(0x13);
                wp->unk28 = wp->unk44;
                wp->flags &= ~1;
                wp->unk18 = 1;
            }
            if (wp->unk28 >= 2) {
                wp->unk28 = 0;
            }
            if (wp->unk28 < 0) {
                wp->unk28 = 1;
            }
            wp->tx = -74.0f;
            wp->ty = 4.0f + (30.0f - 50.0f * wp->unk28);
            break;
    }
    wp->x += (wp->tx - wp->x) / 4.0f;
    wp->y += (wp->ty - wp->y) / 4.0f;
    { f32 s = 2.0f * (f32)sin(gp->retraceCount / 8.0f); wp->x += __fabsf(s); }
    dispEntry(CAMERA_3D, 1000.0f, 0, loadDraw, NULL);
}

#define GXFIFO_F32 (*(volatile f32*)0xCC008000)

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
    GXFIFO_F32 = x0;
    GXFIFO_F32 = y0;
    GXFIFO_F32 = 0.0f;
    GXFIFO_F32 = 0.0f;
    GXFIFO_F32 = 0.0f;
    GXFIFO_F32 = x0;
    GXFIFO_F32 = y1;
    GXFIFO_F32 = 0.0f;
    GXFIFO_F32 = 0.0f;
    GXFIFO_F32 = 1.0f;
    GXFIFO_F32 = x1;
    GXFIFO_F32 = y1;
    GXFIFO_F32 = 0.0f;
    GXFIFO_F32 = 1.0f;
    GXFIFO_F32 = 1.0f;
    GXFIFO_F32 = x1;
    GXFIFO_F32 = y0;
    GXFIFO_F32 = 0.0f;
    GXFIFO_F32 = 1.0f;
    GXFIFO_F32 = 0.0f;
}

void loadDraw(CameraId camera, void* param) {
    CameraEntry* cam = camGetPtr(CAMERA_2D);
    GXColor white = {255, 255, 255, 255};
    GXColor gray = {160, 160, 160, 255};
    GXColor dark = {128, 128, 128, 128};
    f32 vp[6];
    f32 proj[7];
    CameraEntry saved;
    char buf[0x20];
    char buf2[0x100];
    Mtx m;
    Mtx s;
    f32 x;
    f32 y;
    f32 w;
    f32* py;
    WinDt* win;
    s32 i;
    s32 j;
    u64 sec;

    if (wp->unk18 >= 0x20 && wp->unk18 < 0x28) {
        return;
    }
    GXGetViewportv(vp);
    GXGetProjectionv(proj);
    GXSetProjection(cam->projection, cam->projType);
    saved = *camGetCurPtr();
    *camGetCurPtr() = *cam;
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
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    loadDrawBg(0x35, -304.0f, 240.0f, -272.0f, -240.0f);
    loadDrawBg(0x34, -272.0f, 240.0f, 272.0f, -240.0f);
    loadDrawBg(0x36, 272.0f, 240.0f, 304.0f, -240.0f);

    win = win_dt;
    for (i = 0; i < 9; i++) {
        WinDt* win1 = &win_dt[i];
        GXColor col = gray;
        if (i == wp->slot) {
            col = white;
        }
        if (wp->unk18 == 0x33 && (i == wp->unk30 || i == wp->unk34)) {
            col = white;
        }
        if (i == 4 && (wp->flags & 0x10)) {
            col = dark;
        }
        if (i == 5 && (wp->flags & 0x20)) {
            col = dark;
        }
        switch (win1->unk10) {
            case 10:
            case 11:
            case 12:
            case 13: {
                col.a = 0xfe;
                winTexInit(*wp->file->data);
                winTexSet(0xe, (Vec){win1->x, win1->y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, col);
                winTexInit(*wp->file->data);
                winTexSet(win1->unk10, (Vec){win1->x, 60.0f + win1->y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, col);
                break;
            }
            default: {
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(win1->unk10, win1->unk14, (Vec){win1->x, win1->y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, col);
                break;
            }
        }
    }

    windowDispGX_Waku_col(0, (GXColor){255, 255, 255, 255}, -250.0f, 200.0f, 500.0f, 40.0f, 20.0f);
    FontDrawStart();
    {
        const char* msg = wp->msg;
        FontDrawMessage(-FontGetMessageWidth(msg) / 2, 192, msg);
    }

    for (i = 0; i < 4; i++, win++) {
        CardSaveSlot* save = &cardGetFilePtr()->saves[i];
        u16 flags = save->data.flags;
        s16 level = save->data.pouch.level;
        OSTime time = save->data.global.retraceLocalTime;
        u16 stars = *(u16*)&save->data.pouch.mStarPowersObtained;
        char* name = (char*)save->data.global.field_0x11BC;
        s32 gsw0 = save->data.global.mGSW0;
        const char* str;
        s32 hours;
        s32 mins;

        FontDrawStart();
        FontDrawColor((GXColor){192, 192, 192, 255});
        if (i == wp->slot) {
            FontDrawColor((GXColor){255, 255, 255, 255});
        }
        FontDrawScale(0.6f);
        FontDrawEdge();
        sprintf(buf, "\x83\x66\x81\x5b\x83\x5e%s", winZenkakuStr(i + 1));
        FontDrawString(win->x - 100.0f, 84.0f + win->y, buf);
        FontDrawEdgeOff();
        FontDrawScale(1.0f);
        FontDrawColor((GXColor){32, 32, 32, 255});
        if (i == wp->slot) {
            FontDrawColor((GXColor){0, 0, 0, 255});
        }
        if (flags & 2) {
            str = "\x82\xb1\x82\xed\x82\xea\x82\xc4\x82\xa2\x82\xdc\x82\xb7";
            FontDrawString(win->x - FontGetMessageWidth(str) / 2.0f, 12.0f + win->y, str);
        } else if (flags & 1) {
            str = "\x83\x6a\x83\x85\x81\x5b\x83\x51\x81\x5b\x83\x80";
            FontDrawString(win->x - FontGetMessageWidth(str) / 2.0f, 12.0f + win->y, str);
        } else if (gsw0 == 0) {
            str = "\x82\xcd\x82\xb6\x82\xdf\x82\xa9\x82\xe7";
            FontDrawString(win->x - FontGetMessageWidth(str) / 2.0f, 12.0f + win->y, str);
            if (strlen(name) != 0) {
                FontDrawString(win->x - FontGetMessageWidth(name) / 2, 70.0f + win->y, name);
            }
        } else {
            FontGetMessageWidth("\x82\x57\x82\x57");
            sec = OSTicksToSeconds(time);
            if (sec > 359999) {
                hours = 99;
                mins = 59;
            } else {
                hours = sec / 3600;
                mins = (sec % 3600) / 60;
            }
            if (strlen(name) != 0) {
                FontDrawString(win->x - FontGetMessageWidth(name) / 2, 70.0f + win->y, name);
            }
            sprintf(buf2, "\x83\x8c\x83\x78\x83\x8b\x81\x40%s", winZenkakuStr(level));
            FontDrawString(win->x - FontGetMessageWidth(buf2) / 2.0f, 30.0f + win->y, buf2);
            strcpy(buf2, "\x83\x76\x83\x8c\x83\x43\x82\xb6\x82\xa9\x82\xf1\x81\x40");
            strcat(buf2, unk_8016af5c(hours, 2));
            strcat(buf2, " ");
            strcat(buf2, unk_8016af5c(mins, 2));
            w = FontGetMessageWidth(buf2) / 2.0f;
            FontDrawString(win->x - w, win->y, buf2);
            strcpy(buf2, "\x83\x76\x83\x8c\x83\x43\x82\xb6\x82\xa9\x82\xf1\x81\x40");
            strcat(buf2, unk_8016af5c(hours, 2));
            x = FontGetMessageWidth(buf2);
            PSMTXTrans(m, 8.0f + (x + (win->x - w)), 1.0f + (win->y - 22.0f), 0.0f);
            PSMTXScale(s, 1.5f, 1.5f, 1.5f);
            PSMTXConcat(m, s, m);
            iconDispGxCol(m, 0, 0x201, (GXColor){0, 0, 0, 255});
            py = &win->y;
            for (j = 0; j < 7; j++) {
                if (stars & (1 << (j + 1))) {
                    PSMTXTrans(m, (win->x - 106.0f) + j * 32, *py - 52.0f, 0.0f);
                    iconDispGxCol(m, 0, (u16)stone_id[j], i == wp->slot ? white : gray);
                }
            }
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

    if (wp->unk18 >= 100 && wp->unk18 < 200) {
        winTexInit(*wp->file->data);
        winTexSet(0xf, (Vec){0.0f, 0.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
        winTexInit_x2(*wp->file->data);
        winTexSet_x2(0x13, 0x1f, (Vec){0.0f, 100.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
        for (j = 0; j < 3; j++) {
            if (j == wp->unk24) {
                winTexInit(*wp->file->data);
                winTexSet(0x33, (Vec){0.0f, 50 - j * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 64});
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(j + 0x15, 0x33, (Vec){-4.0f, 54 - j * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
            } else {
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(j + 0x15, 0x33, (Vec){0.0f, 50 - j * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
            }
        }
    }

    if (wp->unk18 >= 200 && wp->unk18 < 300) {
        winTexInit(*wp->file->data);
        winTexSet(0xf, (Vec){0.0f, 0.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
        winTexInit_x2(*wp->file->data);
        winTexSet_x2(0x14, 0x1f, (Vec){0.0f, 100.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
        for (j = 0; j < 2; j++) {
            if (j == wp->unk28) {
                winTexInit(*wp->file->data);
                winTexSet(0x33, (Vec){0.0f, 30 - j * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 64});
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(j + 0x18, 0x33, (Vec){-4.0f, 34 - j * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
            } else {
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(j + 0x18, 0x33, (Vec){0.0f, 30 - j * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
            }
        }
    }

    if (wp->unk18 == 0x33 && wp->unk34 < 4) {
        f32 angle[4][4] = {
            {0.0f, -90.0f, -180.0f, -135.0f},
            {90.0f, 0.0f, 135.0f, 180.0f},
            {0.0f, -45.0f, 0.0f, -90.0f},
            {45.0f, 0.0f, 90.0f, 0.0f},
        };
        f32 cx;
        f32 cy;
        if (!(f32)fmod(angle[wp->unk30][wp->unk34], 90.0)) {
            f32 c0 = wp->unk30 % 2;
            f32 r0 = wp->unk30 / 2;
            f32 r1 = wp->unk34 / 2;
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
        winTexSetRot(0x1d, (Vec){2.0f + cx, cy - 2.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 128}, angle[wp->unk30][wp->unk34]);
        winTexSetRot(0x1d, (Vec){cx, cy, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white, angle[wp->unk30][wp->unk34]);
    }

    if (!(wp->flags & 0x40)) {
        winTexInit(*wp->file->data);
        winTexSet(0, (Vec){2.0f + wp->x, wp->y - 2.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 128});
        winTexSet(0, (Vec){wp->x, wp->y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
    }

    GXSetViewport(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
    GXSetProjectionv(proj);
    *camGetCurPtr() = saved;
}

__declspec(section ".sdata") s32 stone_id[7] = {0x197, 0x198, 0x19A, 0x19C, 0x19D, 0x199, 0x19B};

__declspec(section ".sdata") static s32 evt_shake[] = {
    0x0003005B, (s32)evt_sub_rumble_onoff, 0, 0,
    0x0001000A, 150,
    0x0003005B, (s32)evt_sub_rumble_onoff, 1, 0,
    0x00000002, 0x00000001,
};

__declspec(section ".sdata") s32 evt_continue[] = {
    0x0002005B, (s32)evt_sub_animgroup_async, (s32)"OFF_f_in_out_mario",
    0x0002005B, (s32)evt_sub_animgroup_async, (s32)"OFF_f_in_out_kuppa",
    0x0002005B, (s32)evt_sub_animgroup_async, (s32)"OFF_f_in_out_peach",
    0x00000002, 0x00000001,
};

void continueGame(void) {
    cardCopy2Main(wp->slot);
    gp->saveSlot = wp->slot;
    gp->unk11B8 = wp->slot;
    marioPartyKill();
    {
        MarioWork* m = marioGetPtr();
        m->prevPartyMemberId[0] = 0;
        m->prevPartyMemberId[1] = 0;
    }
    psndSetFlag(4);
    marioPartyEntry(gp->savePartyId[0]);
    marioPartyEntry(gp->savePartyId[1]);
    psndClearFlag(4);
    countDownSaveReStart();
    gp->flags |= 1;
    switch (swByteGet(4)) {
        case 0:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, gp->currentMapName, 0);
            break;
        case 1:
            gp->areaFadeInType = 61;
            gp->areaFadeOutType = 56;
            seqSetSeq(SEQ_MAP_CHANGE, "aji_10", 0);
            break;
        case 2:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, "kpa_00", 0);
            break;
        case 3:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, "nok_01", "nokotarou");
            break;
        case 4:
            gp->areaFadeInType = 61;
            gp->areaFadeOutType = 56;
            seqSetSeq(SEQ_MAP_CHANGE, "aji_10", 0);
            break;
        case 5:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, "hei_00", 0);
            break;
        case 6:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, "mri_00", 0);
            break;
        case 7:
            gp->areaFadeInType = 61;
            gp->areaFadeOutType = 56;
            seqSetSeq(SEQ_MAP_CHANGE, "aji_10", 0);
            break;
        case 8:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, "mri_01", 0);
            break;
        case 9:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, "tou_02", 0);
            break;
        case 10:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, "usu_00", 0);
            break;
        case 11:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, "gor_04", 0);
            break;
        case 12:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, "usu_00", 0);
            break;
        case 13:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, "muj_12", 0);
            break;
        case 14:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, "usu_00", 0);
            break;
        case 15:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, "muj_00", 0);
            break;
        case 16:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, "pik_03", "next");
            break;
        case 17:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, "gor_01", 0);
            break;
        case 18:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, "gor_04", "resha_return");
            break;
        case 19:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, "pik_01", 0);
            break;
        case 20:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, "aji_18", "e_bero");
            break;
        case 21:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, "gor_00", 0);
            break;
        case 22:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, "jin_04", 0);
            break;
        case 23:
            stg0_00_init();
            gp->saveSlot = wp->slot;
            marioPartyKill();
            {
                MarioWork* m = marioGetPtr();
                m->prevPartyMemberId[0] = 0;
                m->prevPartyMemberId[1] = 0;
            }
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 25;
            swInit();
            swByteSet(0, 0);
            seqSetSeq(SEQ_MAP_CHANGE, "aaa_00", "prologue");
            break;
        case 24:
            gp->areaFadeInType = 0x3d;
            gp->areaFadeOutType = 0x38;
            seqSetSeq(SEQ_MAP_CHANGE, "aji_10", 0);
            break;
    }
}
