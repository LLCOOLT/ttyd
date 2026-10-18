// FAKE: whole unit as asm (asm_inline + hand data naming, jump table via `entry` labels); C kept under #ifdef NONMATCHING. Best pure C: 6/7 (loadDraw 99.81).
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
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".rodata") const f32 vec3_802ed670[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed67c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed688[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed694[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed6a0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed6ac[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed6b8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed6c4[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed6d0[3] = { 0.0f, 100.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed6dc[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed6e8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed6f4[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed700[3] = { -4.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed70c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed718[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed724[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed730[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed73c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed748[3] = { 0.0f, 100.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed754[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed760[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed76c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed778[3] = { -4.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed784[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed790[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed79c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const u32 dat_802ed7a8[16] = { 0x00000000, 0xC2B40000, 0xC3340000, 0xC3070000, 0x42B40000, 0x00000000, 0x43070000, 0x43340000, 0x00000000, 0xC2340000, 0x00000000, 0xC2B40000, 0x42340000, 0x00000000, 0x42B40000, 0x00000000 };
__declspec(section ".rodata") const f32 vec3_802ed7e8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed7f4[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed800[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed80c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed818[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed824[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ed830[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ed83c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") char str_802ED848[20] = "\117\106\106\137\146\137\151\156\137\157\165\164\137\155\141\162\151\157\000";
__declspec(section ".rodata") char str_802ED85C[20] = "\117\106\106\137\146\137\151\156\137\157\165\164\137\153\165\160\160\141\000";
__declspec(section ".rodata") char str_802ED870[20] = "\117\106\106\137\146\137\151\156\137\157\165\164\137\160\145\141\143\150\000";
__declspec(section ".rodata") char str_802ED884[8] = "\141\152\151\137\061\060\000";
__declspec(section ".rodata") char str_802ED88C[8] = "\153\160\141\137\060\060\000";
__declspec(section ".rodata") char str_802ED894[8] = "\156\157\153\137\060\061\000";
__declspec(section ".rodata") char str_802ED89C[12] = "\156\157\153\157\164\141\162\157\165\000\000";
__declspec(section ".rodata") char str_802ED8A8[8] = "\150\145\151\137\060\060\000";
__declspec(section ".rodata") char str_802ED8B0[8] = "\155\162\151\137\060\060\000";
__declspec(section ".rodata") char str_802ED8B8[8] = "\155\162\151\137\060\061\000";
__declspec(section ".rodata") char str_802ED8C0[8] = "\164\157\165\137\060\062\000";
__declspec(section ".rodata") char str_802ED8C8[8] = "\165\163\165\137\060\060\000";
__declspec(section ".rodata") char str_802ED8D0[8] = "\147\157\162\137\060\064\000";
__declspec(section ".rodata") char str_802ED8D8[8] = "\155\165\152\137\061\062\000";
__declspec(section ".rodata") char str_802ED8E0[8] = "\155\165\152\137\060\060\000";
__declspec(section ".rodata") char str_802ED8E8[8] = "\160\151\153\137\060\063\000";
__declspec(section ".rodata") char str_802ED8F0[8] = "\147\157\162\137\060\061\000";
__declspec(section ".rodata") char str_802ED8F8[16] = "\162\145\163\150\141\137\162\145\164\165\162\156\000\000\000";
__declspec(section ".rodata") char str_802ED908[8] = "\160\151\153\137\060\061\000";
__declspec(section ".rodata") char str_802ED910[8] = "\141\152\151\137\061\070\000";
__declspec(section ".rodata") char str_802ED918[8] = "\145\137\142\145\162\157\000";
__declspec(section ".rodata") char str_802ED920[8] = "\147\157\162\137\060\060\000";
__declspec(section ".rodata") char str_802ED928[8] = "\152\151\156\137\060\064\000";
__declspec(section ".rodata") char str_802ED930[8] = "\141\141\141\137\060\060\000";
__declspec(section ".rodata") char str_802ED938[12] = "\160\162\157\154\157\147\165\145\000\000\000";
__declspec(section ".rodata") const u32 gap_04_802ED944_rodata[1] = { 0x00000000 };
__declspec(section ".rodata") const f64 double_480_802ed948 = 480;
__declspec(section ".rodata") const f64 double_32_802ed950 = 32;
__declspec(section ".rodata") const f64 double_544_802ed958 = 544;
__declspec(section ".rodata") char str_802ED960[12] = "\203\146\201\133\203\136\045\163\000\000\000";
__declspec(section ".rodata") char str_802ED96C[16] = "\202\261\202\355\202\352\202\304\202\242\202\334\202\267\000";
__declspec(section ".rodata") char str_802ED97C[16] = "\203\152\203\205\201\133\203\121\201\133\203\200\000\000\000";
__declspec(section ".rodata") char str_802ED98C[12] = "\202\315\202\266\202\337\202\251\202\347\000";
__declspec(section ".rodata") char str_802ED998[12] = "\203\214\203\170\203\213\201\100\045\163\000";
__declspec(section ".rodata") char str_802ED9A4[16] = "\203\166\203\214\203\103\202\266\202\251\202\361\201\100\000";
__declspec(section ".rodata") const u32 gap_04_802ED9B4_rodata[1] = { 0x00000000 };
__declspec(section ".rodata") const f64 double_90_802ed9b8 = 90;
__declspec(section ".rodata") const f64 double_to_int_mask_802ed9c0 = 4503599627370496;
__declspec(section ".rodata") const f64 double_to_int_802ed9c8 = 4503601774854144;
__declspec(section ".rodata") char str_802ED9D0[20] = "\155\163\147\137\163\141\166\145\146\151\154\145\137\163\145\154\145\143\164";
__declspec(section ".rodata") char str_802ED9E4[28] = "\155\163\147\137\163\141\166\145\146\151\154\145\137\144\145\154\145\164\145\137\163\145\154\145\143\164\000";
__declspec(section ".rodata") char str_802EDA00[28] = "\155\163\147\137\163\141\166\145\146\151\154\145\137\143\157\160\171\137\163\145\154\145\143\164\000\000\000";
__declspec(section ".rodata") char str_802EDA1C[24] = "\155\163\147\137\163\141\166\145\146\151\154\145\137\143\157\160\171\137\160\157\151\156\164";
__declspec(section ".rodata") char str_802EDA34[20] = "\045\163\057\167\057\152\160\057\156\141\155\145\056\164\160\154\000\000\000";


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

__declspec(section ".data") static u32 gap_06_803DB834_bss;
static LoadWork work;
static LoadWork* wp = &work;

extern s32 stone_id[];
static s32 evt_shake[12];
extern s32 evt_continue[];

#ifdef NONMATCHING
s32 unk_800f2398(EventEntry* evt, BOOL isFirstCall) {
    fadeReset(4);
    wp->unk48 = evt->printWindowId;
    return 2;
}
#endif

#ifdef NONMATCHING
void seq_loadInit(SequenceWork* seq) {
    memset(wp, 0, sizeof(LoadWork));
}
#endif

#ifdef NONMATCHING
void seq_loadExit(SequenceWork* seq) {
    if (wp->file != NULL) {
        fileFree(wp->file);
    }
    wp->file = NULL;
}
#endif

static inline BOOL loadStart(void) {
    if (fileAsyncf(4, NULL, "%s/w/jp/name.tpl\0\0\0", getMarioStDvdRoot()) != 0U) {
        wp->file = fileAllocf(4, "%s/w/jp/name.tpl\0\0\0", getMarioStDvdRoot());
        return TRUE;
    }
    return FALSE;
}

#ifdef NONMATCHING
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
                    wp->unk44 = gp->rumbleEnabled == 0;
                    wp->unk24 = wp->unk40;
                    wp->unk28 = wp->unk44;
                    wp->slot = gp->lastSlot;
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
#endif

#define SFX(id) psndSFXOn((const char*)(id))
#define SLOTFLAGS(i) (cardGetFilePtr()->saves[(i)].data.flags)

#ifdef NONMATCHING
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
            wp->msg = msgSearch(str_802ED9D0);
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
                    gp->lastSlot = wp->slot;
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
                        seqSetSeq(SEQ_MAP_CHANGE, str_802ED930, str_802ED938);
                    }
                }
            }
            break;
        case 0x23:
            if (!evtCheckID(wp->evt->eventId)) {
                seqSetSeq(SEQ_MAP_CHANGE, str_802ED930, str_802ED938);
            }
            break;
        case 0x28:
            wp->msg = msgSearch(str_802ED9E4);
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
            wp->msg = msgSearch(str_802EDA00);
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
            wp->msg = msgSearch(str_802EDA1C);
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
                gp->rumbleEnabled = wp->unk28 == 0;
                SFX(0x12);
                wp->unk44 = wp->unk28;
                wp->flags &= ~1;
                wp->unk18 = 1;
                if (gp->rumbleEnabled) {
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
#endif

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

#ifdef NONMATCHING
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
    u64 sec;
    WinDt* win;
    WinDt* win1;
    s32 i;
    s32 j;
    s32 k;

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

    win1 = win = win_dt;
    for (i = 0; i < 9; i++) {
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
        switch (win[i].unk10) {
            case 10:
            case 11:
            case 12:
            case 13: {
                col.a = 0xfe;
                winTexInit(*wp->file->data);
                winTexSet(0xe, (Vec){win[i].x, win[i].y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, col);
                winTexInit(*wp->file->data);
                winTexSet(win[i].unk10, (Vec){win[i].x, 60.0f + win[i].y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, col);
                break;
            }
            default: {
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(win[i].unk10, win[i].unk14, (Vec){win[i].x, win[i].y, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, col);
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

    for (i = 0; i < 4; i++, win1++) {
        CardSaveSlot* save = &cardGetFilePtr()->saves[i];
        u16 flags = save->data.flags;
        s16 level = save->data.pouch.level;
        OSTime time = save->data.global.retraceLocalTime;
        u16 stars = *(u16*)&save->data.pouch.mStarPowersObtained;
        s32 gsw0 = save->data.global.mGSW0;
        char* name = (char*)save->data.global.field_0x11BC;
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
        sprintf(buf, str_802ED960, winZenkakuStr(i + 1));
        FontDrawString(win1->x - 100.0f, 84.0f + win1->y, buf);
        FontDrawEdgeOff();
        FontDrawScale(1.0f);
        FontDrawColor((GXColor){32, 32, 32, 255});
        if (i == wp->slot) {
            FontDrawColor((GXColor){0, 0, 0, 255});
        }
        if (flags & 2) {
            str = str_802ED96C;
            FontDrawString(win1->x - FontGetMessageWidth(str) / 2.0f, 12.0f + win1->y, str);
        } else if (flags & 1) {
            str = str_802ED97C;
            FontDrawString(win1->x - FontGetMessageWidth(str) / 2.0f, 12.0f + win1->y, str);
        } else if (gsw0 == 0) {
            str = str_802ED98C;
            FontDrawString(win1->x - FontGetMessageWidth(str) / 2.0f, 12.0f + win1->y, str);
            if (strlen(name) != 0) {
                FontDrawString(win1->x - FontGetMessageWidth(name) / 2, 70.0f + win1->y, name);
            }
        } else {
            FontGetMessageWidth("\x82\x57\x82\x57");
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
            sprintf(buf2, str_802ED998, winZenkakuStr(level));
            FontDrawString(win1->x - FontGetMessageWidth(buf2) / 2.0f, 30.0f + win1->y, buf2);
            strcpy(buf2, str_802ED9A4);
            strcat(buf2, unk_8016af5c(hours, 2));
            strcat(buf2, " ");
            strcat(buf2, unk_8016af5c(mins, 2));
            w = FontGetMessageWidth(buf2);
            FontDrawString(win1->x - w / 2.0f, win1->y, buf2);
            strcpy(buf2, str_802ED9A4);
            strcat(buf2, unk_8016af5c(hours, 2));
            x = FontGetMessageWidth(buf2);
            PSMTXTrans(m, 8.0f + (x + (win1->x - w / 2.0f)), 1.0f + (win1->y - 22.0f), 0.0f);
            PSMTXScale(s, 1.5f, 1.5f, 1.5f);
            PSMTXConcat(m, s, m);
            iconDispGxCol(m, 0, 0x201, (GXColor){0, 0, 0, 255});
            py = &win1->y;
            for (k = 0; k < 7; k++) {
                if (stars & (1 << (k + 1))) {
                    PSMTXTrans(m, (win1->x - 106.0f) + k * 32, *py - 52.0f, 0.0f);
                    iconDispGxCol(m, 0, (u16)stone_id[k], i == wp->slot ? white : gray);
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
        for (i = 0; i < 3; i++) {
            if (i == wp->unk24) {
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

    if (wp->unk18 >= 200 && wp->unk18 < 300) {
        winTexInit(*wp->file->data);
        winTexSet(0xf, (Vec){0.0f, 0.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
        winTexInit_x2(*wp->file->data);
        winTexSet_x2(0x14, 0x1f, (Vec){0.0f, 100.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
        for (i = 0; i < 2; i++) {
            if (i == wp->unk28) {
                winTexInit(*wp->file->data);
                winTexSet(0x33, (Vec){0.0f, 30 - i * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 64});
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(i + 0x18, 0x33, (Vec){-4.0f, 34 - i * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
            } else {
                winTexInit_x2(*wp->file->data);
                winTexSet_x2(i + 0x18, 0x33, (Vec){0.0f, 30 - i * 50, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){255, 255, 255, 255});
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
#endif

__declspec(section ".sdata") s32 stone_id[7] = {0x197, 0x198, 0x19A, 0x19C, 0x19D, 0x199, 0x19B};

__declspec(section ".sdata") static s32 evt_shake[] = {
    0x0003005B, (s32)evt_sub_rumble_onoff, 0, 0,
    0x0001000A, 150,
    0x0003005B, (s32)evt_sub_rumble_onoff, 1, 0,
    0x00000002, 0x00000001,
};

__declspec(section ".sdata") s32 evt_continue[] = {
    0x0002005B, (s32)evt_sub_animgroup_async, (s32)str_802ED848,
    0x0002005B, (s32)evt_sub_animgroup_async, (s32)str_802ED85C,
    0x0002005B, (s32)evt_sub_animgroup_async, (s32)str_802ED870,
    0x00000002, 0x00000001,
};
#ifndef NONMATCHING
extern void strcat(void);
extern void __mod2u(void);
extern void __div2u(void);
extern void __div2i(void);
extern void winZenkakuStr(void);
#endif
#pragma force_active on
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_80410C9C_sdata[1] = {0};

#pragma defer_codegen off
#pragma force_active on
#ifdef NONMATCHING
void continueGame(void) {
    cardCopy2Main(wp->slot);
    gp->saveSlot = wp->slot;
    gp->lastSlot = wp->slot;
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
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED884, 0);
            break;
        case 2:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED88C, 0);
            break;
        case 3:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED894, str_802ED89C);
            break;
        case 4:
            gp->areaFadeInType = 61;
            gp->areaFadeOutType = 56;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED884, 0);
            break;
        case 5:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8A8, 0);
            break;
        case 6:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8B0, 0);
            break;
        case 7:
            gp->areaFadeInType = 61;
            gp->areaFadeOutType = 56;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED884, 0);
            break;
        case 8:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8B8, 0);
            break;
        case 9:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8C0, 0);
            break;
        case 10:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8C8, 0);
            break;
        case 11:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8D0, 0);
            break;
        case 12:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8C8, 0);
            break;
        case 13:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8D8, 0);
            break;
        case 14:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8C8, 0);
            break;
        case 15:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8E0, 0);
            break;
        case 16:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8E8, "next");
            break;
        case 17:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8F0, 0);
            break;
        case 18:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED8D0, str_802ED8F8);
            break;
        case 19:
            gp->areaFadeInType = 62;
            gp->areaFadeOutType = 58;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED908, 0);
            break;
        case 20:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED910, str_802ED918);
            break;
        case 21:
            gp->areaFadeInType = 60;
            gp->areaFadeOutType = 54;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED920, 0);
            break;
        case 22:
            gp->areaFadeInType = 0;
            gp->areaFadeOutType = 28;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED928, 0);
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
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED930, str_802ED938);
            break;
        case 24:
            gp->areaFadeInType = 0x3d;
            gp->areaFadeOutType = 0x38;
            seqSetSeq(SEQ_MAP_CHANGE, str_802ED884, 0);
            break;
    }
}
#endif
#pragma defer_codegen reset


























__declspec(section ".data") void* jumptable_8034A058[25] = { (char*)continueGame + 0xBC, (char*)continueGame + 0xEC, (char*)continueGame + 0x118, (char*)continueGame + 0x144, (char*)continueGame + 0x170, (char*)continueGame + 0x19C, (char*)continueGame + 0x1C8, (char*)continueGame + 0x1F4, (char*)continueGame + 0x220, (char*)continueGame + 0x24C, (char*)continueGame + 0x278, (char*)continueGame + 0x2A4, (char*)continueGame + 0x2D0, (char*)continueGame + 0x2FC, (char*)continueGame + 0x328, (char*)continueGame + 0x354, (char*)continueGame + 0x380, (char*)continueGame + 0x3AC, (char*)continueGame + 0x3D8, (char*)continueGame + 0x404, (char*)continueGame + 0x430, (char*)continueGame + 0x45C, (char*)continueGame + 0x488, (char*)continueGame + 0x4B4, (char*)continueGame + 0x514 };
#pragma force_active on
__declspec(section ".data") u32 gap_05_8034A0BC_data[1] = {0};

#ifndef NONMATCHING
// ASM-STOPGAP: unk_800f2398 (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
__declspec(section ".sdata2") const u32 dat_8041bd68 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd6c = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd70 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd74 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd78 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd7c = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd80 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bd84 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bd88 = 0xA0A0A0FF;
__declspec(section ".sdata2") const u32 dat_8041bd8c = 0x80808080;
__declspec(section ".sdata2") const u32 dat_8041bd90 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bd94 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bd98 = 0xC0C0C0FF;
__declspec(section ".sdata2") const u32 dat_8041bd9c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bda0 = 0x202020FF;
__declspec(section ".sdata2") const u32 dat_8041bda4 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bda8 = 0x000000FF;
__declspec(section ".sdata2") const u32 dat_8041bdac = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdb0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdb4 = 0x00000040;
__declspec(section ".sdata2") const u32 dat_8041bdb8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdbc = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdc0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdc4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdc8 = 0x00000040;
__declspec(section ".sdata2") const u32 dat_8041bdcc = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdd0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_8041bdd4 = 0x00000080;
__declspec(section ".sdata2") const u32 dat_8041bdd8 = 0x00000080;
__declspec(section ".sdata2") const char str_8041BDDC[8] = "next\0\0\0";
__declspec(section ".sdata2") const f32 float_0_8041bde4 = 0.0f;
__declspec(section ".sdata2") const f32 float_1_8041bde8 = 1.0f;
__declspec(section ".sdata2") const f32 float_neg304_8041bdec = -304.0f;
__declspec(section ".sdata2") const f32 float_240_8041bdf0 = 240.0f;
__declspec(section ".sdata2") const f32 float_neg240_8041bdf4 = -240.0f;
__declspec(section ".sdata2") const f32 float_neg272_8041bdf8 = -272.0f;
__declspec(section ".sdata2") const f32 float_272_8041bdfc = 272.0f;
__declspec(section ".sdata2") const f32 float_304_8041be00 = 304.0f;
__declspec(section ".sdata2") const f32 float_60_8041be04 = 60.0f;
__declspec(section ".sdata2") const f32 float_neg250_8041be08 = -250.0f;
__declspec(section ".sdata2") const f32 float_200_8041be0c = 200.0f;
__declspec(section ".sdata2") const f32 float_500_8041be10 = 500.0f;
__declspec(section ".sdata2") const f32 float_40_8041be14 = 40.0f;
__declspec(section ".sdata2") const f32 float_20_8041be18 = 20.0f;
__declspec(section ".sdata2") const f32 float_0p6_8041be1c = 0.6f;
__declspec(section ".sdata2") const f32 float_100_8041be20 = 100.0f;
__declspec(section ".sdata2") const f32 float_84_8041be24 = 84.0f;
__declspec(section ".sdata2") const f32 float_0p5_8041be28 = 0.5f;
__declspec(section ".sdata2") const f32 float_12_8041be2c = 12.0f;
__declspec(section ".sdata2") const f32 float_70_8041be30 = 70.0f;
__declspec(section ".sdata2") const char str_8041BE34[8] = "\x82W\x82W\0\0\0";
__declspec(section ".sdata2") const f32 float_30_8041be3c = 30.0f;
__declspec(section ".sdata2") const char str_8041BE40[4] = " \0\0";
__declspec(section ".sdata2") const f32 float_8_8041be44 = 8.0f;
__declspec(section ".sdata2") const f32 float_22_8041be48 = 22.0f;
__declspec(section ".sdata2") const f32 float_1p5_8041be4c = 1.5f;
__declspec(section ".sdata2") const f32 float_106_8041be50 = 106.0f;
__declspec(section ".sdata2") const f32 float_52_8041be54 = 52.0f;
__declspec(section ".sdata2") const f32 float_0p05_8041be58 = 0.05f;
__declspec(section ".sdata2") const f32 float_120_8041be5c = 120.0f;
__declspec(section ".sdata2") const f32 float_140_8041be60 = 140.0f;
__declspec(section ".sdata2") const f32 float_neg150_8041be64 = -150.0f;
__declspec(section ".sdata2") const f32 float_300_8041be68 = 300.0f;
__declspec(section ".sdata2") const f32 float_50_8041be6c = 50.0f;
__declspec(section ".sdata2") const f32 float_2_8041be70 = 2.0f;
__declspec(section ".sdata2") const f32 float_neg74_8041be74 = -74.0f;
__declspec(section ".sdata2") const f32 float_4_8041be78 = 4.0f;
__declspec(section ".sdata2") const f32 float_0p25_8041be7c = 0.25f;
__declspec(section ".sdata2") const f32 float_0p125_8041be80 = 0.125f;
__declspec(section ".sdata2") const f32 float_1000_8041be84 = 1000.0f;

asm void continueGame(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, vec3_802ed670@ha
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	addi r31, r4, vec3_802ed670@l
	lwz r3, wp(r13)
	lwz r3, 0x20(r3)
	bl cardCopy2Main
	lwz r4, wp(r13)
	lwz r3, gp(r13)
	lwz r0, 0x20(r4)
	stw r0, 0x11d0(r3)
	lwz r4, wp(r13)
	lwz r3, gp(r13)
	lwz r0, 0x20(r4)
	stw r0, 0x11b8(r3)
	bl marioPartyKill
	bl marioGetPtr
	li r0, 0x0
	stb r0, 0x243(r3)
	stb r0, 0x244(r3)
	li r3, 0x4
	bl psndSetFlag
	lwz r3, gp(r13)
	lwz r3, 0x11e0(r3)
	bl marioPartyEntry
	lwz r3, gp(r13)
	lwz r3, 0x11e4(r3)
	bl marioPartyEntry
	li r3, 0x4
	bl psndClearFlag
	bl countDownSaveReStart
	lwz r4, gp(r13)
	li r3, 0x4
	lwz r0, 0x0(r4)
	ori r0, r0, 0x1
	stw r0, 0x0(r4)
	bl swByteGet
	cmplwi r3, 0x18
	bgt @1
	lis r4, jumptable_8034A058@ha
	slwi r0, r3, 2
	addi r3, r4, jumptable_8034A058@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@2:
	lwz r4, gp(r13)
	li r5, 0x0
	li r0, 0x1c
	li r3, 0x3
	stw r5, 0x110(r4)
	li r5, 0x0
	lwz r4, gp(r13)
	stw r0, 0x108(r4)
	lwz r4, gp(r13)
	addi r4, r4, 0x12c
	bl seqSetSeq
	b @1
	@3:
	lwz r3, gp(r13)
	li r5, 0x3d
	li r0, 0x38
	addi r4, r31, 0x214
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@4:
	lwz r3, gp(r13)
	li r5, 0x3e
	li r0, 0x3a
	addi r4, r31, 0x21c
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@5:
	lwz r3, gp(r13)
	li r5, 0x3c
	li r0, 0x36
	addi r4, r31, 0x224
	stw r5, 0x110(r3)
	addi r5, r31, 0x22c
	li r3, 0x3
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@6:
	lwz r3, gp(r13)
	li r5, 0x3d
	li r0, 0x38
	addi r4, r31, 0x214
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@7:
	lwz r3, gp(r13)
	li r5, 0x3e
	li r0, 0x3a
	addi r4, r31, 0x238
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@8:
	lwz r3, gp(r13)
	li r5, 0x3c
	li r0, 0x36
	addi r4, r31, 0x240
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@9:
	lwz r3, gp(r13)
	li r5, 0x3d
	li r0, 0x38
	addi r4, r31, 0x214
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@10:
	lwz r3, gp(r13)
	li r5, 0x3e
	li r0, 0x3a
	addi r4, r31, 0x248
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@11:
	lwz r3, gp(r13)
	li r5, 0x3c
	li r0, 0x36
	addi r4, r31, 0x250
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@12:
	lwz r3, gp(r13)
	li r5, 0x0
	li r0, 0x1c
	addi r4, r31, 0x258
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@13:
	lwz r3, gp(r13)
	li r5, 0x3e
	li r0, 0x3a
	addi r4, r31, 0x260
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@14:
	lwz r3, gp(r13)
	li r5, 0x3c
	li r0, 0x36
	addi r4, r31, 0x258
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@15:
	lwz r3, gp(r13)
	li r5, 0x0
	li r0, 0x1c
	addi r4, r31, 0x268
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@16:
	lwz r3, gp(r13)
	li r5, 0x3e
	li r0, 0x3a
	addi r4, r31, 0x258
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@17:
	lwz r3, gp(r13)
	li r5, 0x3c
	li r0, 0x36
	addi r4, r31, 0x270
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@18:
	lwz r3, gp(r13)
	li r5, 0x0
	li r0, 0x1c
	addi r4, r31, 0x278
	stw r5, 0x110(r3)
	li r3, 0x3
	la r5, str_8041BDDC(r2)
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@19:
	lwz r3, gp(r13)
	li r5, 0x3e
	li r0, 0x3a
	addi r4, r31, 0x280
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@20:
	lwz r3, gp(r13)
	li r5, 0x3c
	li r0, 0x36
	addi r4, r31, 0x260
	stw r5, 0x110(r3)
	addi r5, r31, 0x288
	li r3, 0x3
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@21:
	lwz r3, gp(r13)
	li r5, 0x3e
	li r0, 0x3a
	addi r4, r31, 0x298
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@22:
	lwz r3, gp(r13)
	li r5, 0x3c
	li r0, 0x36
	addi r4, r31, 0x2a0
	stw r5, 0x110(r3)
	addi r5, r31, 0x2a8
	li r3, 0x3
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@23:
	lwz r3, gp(r13)
	li r5, 0x3c
	li r0, 0x36
	addi r4, r31, 0x2b0
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@24:
	lwz r3, gp(r13)
	li r5, 0x0
	li r0, 0x1c
	addi r4, r31, 0x2b8
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	b @1
	@25:
	bl stg0_00_init
	lwz r4, wp(r13)
	lwz r3, gp(r13)
	lwz r0, 0x20(r4)
	stw r0, 0x11d0(r3)
	bl marioPartyKill
	bl marioGetPtr
	li r4, 0x0
	li r0, 0x19
	stb r4, 0x243(r3)
	stb r4, 0x244(r3)
	lwz r3, gp(r13)
	stw r4, 0x110(r3)
	lwz r3, gp(r13)
	stw r0, 0x108(r3)
	bl swInit
	li r3, 0x0
	li r4, 0x0
	bl swByteSet
	addi r4, r31, 0x2c0
	addi r5, r31, 0x2c8
	li r3, 0x3
	bl seqSetSeq
	b @1
	@26:
	lwz r3, gp(r13)
	li r5, 0x3d
	li r0, 0x38
	addi r4, r31, 0x214
	stw r5, 0x110(r3)
	li r3, 0x3
	li r5, 0x0
	lwz r6, gp(r13)
	stw r0, 0x108(r6)
	bl seqSetSeq
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void loadDraw(CameraId camera, void* param) {
	nofralloc
	stwu r1, -0x890(r1)
	mflr r0
	stw r0, 0x894(r1)
	stfd f31, 0x880(r1)
	psq_st f31, -0x778(r1), 0, 0
	stfd f30, 0x870(r1)
	psq_st f30, -0x788(r1), 0, 0
	stfd f29, 0x860(r1)
	psq_st f29, -0x798(r1), 0, 0
	stmw r20, 0x830(r1)
	lis r4, vec3_802ed670@ha
	li r3, 0x8
	addi r30, r4, vec3_802ed670@l
	bl camGetPtr
	lwz r4, dat_8041bd84(r2)
	mr r25, r3
	lwz r0, dat_8041bd88(r2)
	stw r4, 0x78(r1)
	lwz r3, wp(r13)
	stw r0, 0x74(r1)
	lwz r0, dat_8041bd8c(r2)
	lwz r3, 0x18(r3)
	stw r0, 0x70(r1)
	cmpwi r3, 0x20
	blt @1
	cmpwi r3, 0x28
	blt @2
	@1:
	addi r3, r1, 0x34c
	bl GXGetViewportv
	addi r3, r1, 0x330
	bl GXGetProjectionv
	lwz r4, 0x19c(r25)
	addi r3, r25, 0x15c
	bl GXSetProjection
	bl camGetCurPtr
	li r0, 0x4c
	addi r5, r1, 0x594
	subi r4, r3, 0x4
	mtctr r0
	@3:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @3
	bl camGetCurPtr
	li r0, 0x4c
	subi r5, r3, 0x4
	subi r4, r25, 0x4
	mtctr r0
	@4:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @4
	li r3, 0x0
	li r4, 0x1
	li r5, 0x0
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x0
	bl GXSetZCompLoc
	li r3, 0x6
	li r4, 0x80
	li r5, 0x1
	li r6, 0x0
	li r7, 0x0
	bl GXSetAlphaCompare
	li r3, 0x0
	li r4, 0x7
	li r5, 0x0
	bl GXSetZMode
	lfs f1, float_0_8041bde4(r2)
	addi r4, r1, 0x68
	lwz r0, dat_8041bd90(r2)
	li r3, 0x0
	fmr f2, f1
	fmr f3, f1
	stw r0, 0x68(r1)
	fmr f4, f1
	bl GXSetFog
	li r3, 0x0
	bl GXSetNumChans
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	li r7, 0x0
	li r8, 0x0
	li r9, 0x2
	bl GXSetChanCtrl
	li r3, 0x1
	bl GXSetNumTevStages
	li r3, 0x0
	li r4, 0x0
	li r5, 0x0
	li r6, 0xff
	bl GXSetTevOrder
	li r3, 0x0
	li r4, 0x3
	bl GXSetTevOp
	li r3, 0x0
	bl GXSetCullMode
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0xd
	li r4, 0x1
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	addi r3, r25, 0x11c
	li r4, 0x0
	bl GXLoadPosMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lwz r3, wp(r13)
	addi r4, r1, 0x2f0
	li r5, 0x35
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	lfs f1, float_0_8041bde4(r2)
	addi r3, r1, 0x2f0
	li r4, 0x1
	li r5, 0x1
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	addi r3, r1, 0x2f0
	li r4, 0x0
	bl GXLoadTexObj
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lfd f1, 0x2d8(r30)
	addi r3, r1, 0x2f0
	lfd f0, 0x2e0(r30)
	fabs f30, f1
	fabs f31, f0
	bl GXGetTexObjHeight
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x7fc(r1)
	frsp f0, f30
	lfd f2, 0x350(r30)
	addi r3, r1, 0x2f0
	stw r0, 0x7f8(r1)
	lfd f1, 0x7f8(r1)
	fsubs f1, f1, f2
	fdivs f30, f0, f1
	bl GXGetTexObjWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x804(r1)
	frsp f0, f31
	lfd f4, 0x350(r30)
	fmr f2, f30
	stw r0, 0x800(r1)
	addi r3, r1, 0x3c4
	lfs f3, float_1_8041bde8(r2)
	lfd f1, 0x800(r1)
	fsubs f1, f1, f4
	fdivs f1, f0, f1
	bl PSMTXScale
	addi r3, r1, 0x3c4
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	lfs f0, float_neg304_8041bdec(r2)
	lis r3, 0xcc01
	addi r4, r1, 0x2d0
	li r5, 0x34
	stfs f0, -0x8000(r3)
	lfs f0, float_240_8041bdf0(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_neg304_8041bdec(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_neg240_8041bdf4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_neg272_8041bdf8(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_neg240_8041bdf4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_neg272_8041bdf8(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_240_8041bdf0(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lwz r3, wp(r13)
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	lfs f1, float_0_8041bde4(r2)
	addi r3, r1, 0x2d0
	li r4, 0x1
	li r5, 0x1
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	addi r3, r1, 0x2d0
	li r4, 0x0
	bl GXLoadTexObj
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lfd f1, 0x2d8(r30)
	addi r3, r1, 0x2d0
	lfd f0, 0x2e8(r30)
	fabs f30, f1
	fabs f31, f0
	bl GXGetTexObjHeight
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x80c(r1)
	frsp f0, f30
	lfd f2, 0x350(r30)
	addi r3, r1, 0x2d0
	stw r0, 0x808(r1)
	lfd f1, 0x808(r1)
	fsubs f1, f1, f2
	fdivs f30, f0, f1
	bl GXGetTexObjWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x814(r1)
	frsp f0, f31
	lfd f4, 0x350(r30)
	fmr f2, f30
	stw r0, 0x810(r1)
	addi r3, r1, 0x394
	lfs f3, float_1_8041bde8(r2)
	lfd f1, 0x810(r1)
	fsubs f1, f1, f4
	fdivs f1, f0, f1
	bl PSMTXScale
	addi r3, r1, 0x394
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	lfs f0, float_neg272_8041bdf8(r2)
	lis r3, 0xcc01
	addi r4, r1, 0x2b0
	li r5, 0x36
	stfs f0, -0x8000(r3)
	lfs f0, float_240_8041bdf0(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_neg272_8041bdf8(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_neg240_8041bdf4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_272_8041bdfc(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_neg240_8041bdf4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_272_8041bdfc(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_240_8041bdf0(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r3)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r3)
	lwz r3, wp(r13)
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGetGXTexObjFromPalette
	lfs f1, float_0_8041bde4(r2)
	addi r3, r1, 0x2b0
	li r4, 0x1
	li r5, 0x1
	fmr f2, f1
	li r6, 0x0
	fmr f3, f1
	li r7, 0x0
	li r8, 0x0
	bl GXInitTexObjLOD
	addi r3, r1, 0x2b0
	li r4, 0x0
	bl GXLoadTexObj
	li r3, 0x1
	bl GXSetNumTexGens
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lfd f1, 0x2d8(r30)
	addi r3, r1, 0x2b0
	lfd f0, 0x2e0(r30)
	fabs f30, f1
	fabs f31, f0
	bl GXGetTexObjHeight
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x81c(r1)
	frsp f0, f30
	lfd f2, 0x350(r30)
	addi r3, r1, 0x2b0
	stw r0, 0x818(r1)
	lfd f1, 0x818(r1)
	fsubs f1, f1, f2
	fdivs f30, f0, f1
	bl GXGetTexObjWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x824(r1)
	frsp f0, f31
	lfd f4, 0x350(r30)
	fmr f2, f30
	stw r0, 0x820(r1)
	addi r3, r1, 0x364
	lfs f3, float_1_8041bde8(r2)
	lfd f1, 0x820(r1)
	fsubs f1, f1, f4
	fdivs f1, f0, f1
	bl PSMTXScale
	addi r3, r1, 0x364
	li r4, 0x1e
	li r5, 0x1
	bl GXLoadTexMtxImm
	li r3, 0x80
	li r4, 0x0
	li r5, 0x4
	bl GXBegin
	lfs f0, float_272_8041bdfc(r2)
	lis r4, 0xcc01
	lis r3, win_dt@ha
	li r23, 0x0
	stfs f0, -0x8000(r4)
	addi r28, r3, win_dt@l
	lfs f0, float_240_8041bdf0(r2)
	mr r25, r28
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_272_8041bdfc(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_neg240_8041bdf4(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_304_8041be00(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_neg240_8041bdf4(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_304_8041be00(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_240_8041bdf0(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_1_8041bde8(r2)
	stfs f0, -0x8000(r4)
	lfs f0, float_0_8041bde4(r2)
	stfs f0, -0x8000(r4)
	@5:
	lwz r4, wp(r13)
	lwz r3, 0x74(r1)
	lwz r0, 0x20(r4)
	stw r3, 0x6c(r1)
	cmpw r23, r0
	bne @6
	lwz r0, 0x78(r1)
	stw r0, 0x6c(r1)
	@6:
	lwz r0, 0x18(r4)
	cmpwi r0, 0x33
	bne @7
	lwz r0, 0x30(r4)
	cmpw r23, r0
	beq @8
	lwz r0, 0x34(r4)
	cmpw r23, r0
	bne @7
	@8:
	lwz r0, 0x78(r1)
	stw r0, 0x6c(r1)
	@7:
	cmpwi r23, 0x4
	bne @9
	lhz r0, 0x0(r4)
	rlwinm. r0, r0, 0, 27, 27
	beq @9
	lwz r0, 0x70(r1)
	stw r0, 0x6c(r1)
	@9:
	cmpwi r23, 0x5
	bne @10
	lhz r0, 0x0(r4)
	rlwinm. r0, r0, 0, 26, 26
	beq @10
	lwz r0, 0x70(r1)
	stw r0, 0x6c(r1)
	@10:
	lwz r0, 0x10(r25)
	cmpwi r0, 0xe
	bge @11
	cmpwi r0, 0xa
	bge @12
	b @11
	@12:
	lwz r3, wp(r13)
	li r0, 0xfe
	stb r0, 0x6f(r1)
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lwz r3, 0x0(r30)
	addi r4, r1, 0x2a4
	lwz r0, 0x4(r30)
	addi r5, r1, 0x28c
	stw r3, 0x298(r1)
	addi r6, r1, 0x64
	lfs f1, 0x0(r25)
	li r3, 0xe
	stw r0, 0x29c(r1)
	lfs f0, 0x4(r25)
	lwz r8, 0x8(r30)
	stfs f1, 0x298(r1)
	lwz r12, 0x6c(r1)
	stfs f0, 0x29c(r1)
	lwz r11, 0xc(r30)
	lwz r10, 0x10(r30)
	lwz r9, 0x14(r30)
	lwz r7, 0x298(r1)
	lwz r0, 0x29c(r1)
	stw r12, 0x64(r1)
	stw r11, 0x28c(r1)
	stw r10, 0x290(r1)
	stw r9, 0x294(r1)
	stw r8, 0x2a0(r1)
	stw r7, 0x2a4(r1)
	stw r0, 0x2a8(r1)
	stw r8, 0x2ac(r1)
	bl winTexSet
	lwz r3, wp(r13)
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lfs f1, float_60_8041be04(r2)
	addi r4, r1, 0x280
	lfs f0, 0x4(r25)
	addi r5, r1, 0x268
	lwz r3, 0x18(r30)
	addi r6, r1, 0x60
	lwz r0, 0x1c(r30)
	fadds f0, f1, f0
	stw r3, 0x274(r1)
	lfs f1, 0x0(r25)
	stw r0, 0x278(r1)
	lwz r8, 0x20(r30)
	stfs f1, 0x274(r1)
	lwz r3, 0x6c(r1)
	stfs f0, 0x278(r1)
	lwz r11, 0x24(r30)
	lwz r10, 0x28(r30)
	lwz r9, 0x2c(r30)
	lwz r7, 0x274(r1)
	lwz r0, 0x278(r1)
	stw r3, 0x60(r1)
	lwz r3, 0x10(r25)
	stw r11, 0x268(r1)
	stw r10, 0x26c(r1)
	stw r9, 0x270(r1)
	stw r8, 0x27c(r1)
	stw r7, 0x280(r1)
	stw r0, 0x284(r1)
	stw r8, 0x288(r1)
	bl winTexSet
	b @13
	@11:
	lwz r3, 0x4(r4)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit_x2
	lwz r3, 0x30(r30)
	addi r5, r1, 0x25c
	lwz r0, 0x34(r30)
	addi r6, r1, 0x244
	stw r3, 0x250(r1)
	addi r7, r1, 0x5c
	lfs f1, 0x0(r25)
	stw r0, 0x254(r1)
	lfs f0, 0x4(r25)
	lwz r9, 0x38(r30)
	stfs f1, 0x250(r1)
	lwz r3, 0x6c(r1)
	stfs f0, 0x254(r1)
	lwz r4, 0x3c(r30)
	lwz r11, 0x40(r30)
	lwz r10, 0x44(r30)
	lwz r8, 0x250(r1)
	lwz r0, 0x254(r1)
	stw r3, 0x5c(r1)
	lwz r3, 0x10(r25)
	stw r4, 0x244(r1)
	lwz r4, 0x14(r25)
	stw r11, 0x248(r1)
	stw r10, 0x24c(r1)
	stw r9, 0x258(r1)
	stw r8, 0x25c(r1)
	stw r0, 0x260(r1)
	stw r9, 0x264(r1)
	bl winTexSet_x2
	@13:
	addi r23, r23, 0x1
	addi r25, r25, 0x1c
	cmpwi r23, 0x9
	blt @5
	lwz r0, dat_8041bd94(r2)
	addi r4, r1, 0x58
	lfs f1, float_neg250_8041be08(r2)
	li r3, 0x0
	stw r0, 0x58(r1)
	lfs f2, float_200_8041be0c(r2)
	lfs f3, float_500_8041be10(r2)
	lfs f4, float_40_8041be14(r2)
	lfs f5, float_20_8041be18(r2)
	bl windowDispGX_Waku_col
	bl FontDrawStart
	lwz r3, wp(r13)
	lwz r20, 0x38(r3)
	mr r3, r20
	bl FontGetMessageWidth
	clrlwi r0, r3, 16
	mr r5, r20
	neg r3, r0
	li r4, 0xc0
	srwi r0, r3, 31
	add r0, r0, r3
	srawi r3, r0, 1
	bl FontDrawMessage
	li r27, 0x0
	lfs f30, float_100_8041be20(r2)
	lfs f31, float_84_8041be24(r2)
	mr r29, r27
	@14:
	bl cardGetFilePtr
	addi r4, r29, 0x2000
	add r4, r3, r4
	lhz r22, 0x0(r4)
	addi r25, r4, 0x11c4
	lha r23, 0x146a(r4)
	lwz r24, 0x28(r4)
	lwz r21, 0x2c(r4)
	lhz r26, 0x146c(r4)
	lwz r20, 0x17c(r4)
	bl FontDrawStart
	lwz r0, dat_8041bd98(r2)
	addi r3, r1, 0x54
	stw r0, 0x54(r1)
	bl FontDrawColor
	lwz r3, wp(r13)
	lwz r0, 0x20(r3)
	cmpw r27, r0
	bne @15
	lwz r0, dat_8041bd9c(r2)
	addi r3, r1, 0x50
	stw r0, 0x50(r1)
	bl FontDrawColor
	@15:
	lfs f1, float_0p6_8041be1c(r2)
	bl FontDrawScale
	bl FontDrawEdge
	addi r3, r27, 0x1
	bl winZenkakuStr
	mr r5, r3
	addi r3, r1, 0x310
	addi r4, r30, 0x2f0
	crclr 6
	bl sprintf
	lfs f1, 0x0(r28)
	addi r3, r1, 0x310
	lfs f0, 0x4(r28)
	fsubs f1, f1, f30
	fadds f2, f31, f0
	bl FontDrawString
	bl FontDrawEdgeOff
	lfs f1, float_1_8041bde8(r2)
	bl FontDrawScale
	lwz r0, dat_8041bda0(r2)
	addi r3, r1, 0x4c
	stw r0, 0x4c(r1)
	bl FontDrawColor
	lwz r3, wp(r13)
	lwz r0, 0x20(r3)
	cmpw r27, r0
	bne @16
	lwz r0, dat_8041bda4(r2)
	addi r3, r1, 0x48
	stw r0, 0x48(r1)
	bl FontDrawColor
	@16:
	rlwinm. r0, r22, 0, 30, 30
	beq @17
	addi r20, r30, 0x2fc
	mr r3, r20
	bl FontGetMessageWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x824(r1)
	mr r3, r20
	lfd f2, 0x350(r30)
	stw r0, 0x820(r1)
	lfs f3, float_0p5_8041be28(r2)
	lfd f0, 0x820(r1)
	lfs f1, 0x0(r28)
	fsubs f4, f0, f2
	lfs f2, float_12_8041be2c(r2)
	lfs f0, 0x4(r28)
	fnmsubs f1, f4, f3, f1
	fadds f2, f2, f0
	bl FontDrawString
	b @18
	@17:
	clrlwi. r0, r22, 31
	beq @19
	addi r20, r30, 0x30c
	mr r3, r20
	bl FontGetMessageWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x824(r1)
	mr r3, r20
	lfd f2, 0x350(r30)
	stw r0, 0x820(r1)
	lfs f3, float_0p5_8041be28(r2)
	lfd f0, 0x820(r1)
	lfs f1, 0x0(r28)
	fsubs f4, f0, f2
	lfs f2, float_12_8041be2c(r2)
	lfs f0, 0x4(r28)
	fnmsubs f1, f4, f3, f1
	fadds f2, f2, f0
	bl FontDrawString
	b @18
	@19:
	cmpwi r20, 0x0
	bne @20
	addi r20, r30, 0x31c
	mr r3, r20
	bl FontGetMessageWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x824(r1)
	mr r3, r20
	lfd f2, 0x350(r30)
	stw r0, 0x820(r1)
	lfs f3, float_0p5_8041be28(r2)
	lfd f0, 0x820(r1)
	lfs f1, 0x0(r28)
	fsubs f4, f0, f2
	lfs f2, float_12_8041be2c(r2)
	lfs f0, 0x4(r28)
	fnmsubs f1, f4, f3, f1
	fadds f2, f2, f0
	bl FontDrawString
	mr r3, r25
	bl strlen
	cmplwi r3, 0x0
	beq @18
	mr r3, r25
	bl FontGetMessageWidth
	extrwi r3, r3, 15, 16
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	stw r0, 0x820(r1)
	lfd f2, 0x358(r30)
	stw r3, 0x824(r1)
	mr r3, r25
	lfs f3, 0x0(r28)
	lfd f0, 0x820(r1)
	lfs f1, float_70_8041be30(r2)
	fsubs f4, f0, f2
	lfs f0, 0x4(r28)
	fadds f2, f1, f0
	fsubs f1, f3, f4
	bl FontDrawString
	b @18
	@20:
	la r3, str_8041BE34(r2)
	bl FontGetMessageWidth
	lis r4, 0x8000
	mr r3, r24
	lwz r0, 0xf8(r4)
	mr r4, r21
	li r5, 0x0
	srwi r6, r0, 2
	bl __div2i
	lis r5, 0x5
	mr r7, r4
	addi r0, r5, 0x7e3f
	li r6, 0x0
	mr r5, r3
	subfc r0, r7, r0
	subfe r0, r5, r6
	subfe r0, r31, r31
	neg. r0, r0
	beq @21
	li r20, 0x63
	li r21, 0x3b
	b @22
	@21:
	mr r21, r7
	mr r20, r5
	li r5, 0x0
	li r6, 0xe10
	bl __div2u
	mr r3, r20
	mr r20, r4
	mr r4, r21
	li r5, 0x0
	li r6, 0xe10
	bl __mod2u
	li r5, 0x0
	li r6, 0x3c
	bl __div2u
	mr r21, r4
	@22:
	mr r3, r25
	bl strlen
	cmplwi r3, 0x0
	beq @23
	mr r3, r25
	bl FontGetMessageWidth
	extrwi r3, r3, 15, 16
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	stw r0, 0x820(r1)
	lfd f2, 0x358(r30)
	stw r3, 0x824(r1)
	mr r3, r25
	lfs f3, 0x0(r28)
	lfd f0, 0x820(r1)
	lfs f1, float_70_8041be30(r2)
	fsubs f4, f0, f2
	lfs f0, 0x4(r28)
	fadds f2, f1, f0
	fsubs f1, f3, f4
	bl FontDrawString
	@23:
	mr r3, r23
	bl winZenkakuStr
	mr r5, r3
	addi r3, r1, 0x494
	addi r4, r30, 0x328
	crclr 6
	bl sprintf
	addi r3, r1, 0x494
	bl FontGetMessageWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x824(r1)
	addi r3, r1, 0x494
	lfd f2, 0x350(r30)
	stw r0, 0x820(r1)
	lfs f3, float_0p5_8041be28(r2)
	lfd f0, 0x820(r1)
	lfs f1, 0x0(r28)
	fsubs f4, f0, f2
	lfs f2, float_30_8041be3c(r2)
	lfs f0, 0x4(r28)
	fnmsubs f1, f4, f3, f1
	fadds f2, f2, f0
	bl FontDrawString
	addi r3, r1, 0x494
	addi r4, r30, 0x334
	bl strcpy
	mr r3, r20
	li r4, 0x2
	bl unk_8016af5c
	mr r4, r3
	addi r3, r1, 0x494
	bl strcat
	addi r3, r1, 0x494
	la r4, str_8041BE40(r2)
	bl strcat
	mr r3, r21
	li r4, 0x2
	bl unk_8016af5c
	mr r4, r3
	addi r3, r1, 0x494
	bl strcat
	addi r3, r1, 0x494
	bl FontGetMessageWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x81c(r1)
	addi r3, r1, 0x494
	lfd f3, 0x350(r30)
	stw r0, 0x818(r1)
	lfs f0, float_0p5_8041be28(r2)
	lfd f2, 0x818(r1)
	lfs f1, 0x0(r28)
	fsubs f3, f2, f3
	lfs f2, 0x4(r28)
	fmuls f29, f3, f0
	fsubs f1, f1, f29
	bl FontDrawString
	addi r3, r1, 0x494
	addi r4, r30, 0x334
	bl strcpy
	mr r3, r20
	li r4, 0x2
	bl unk_8016af5c
	mr r4, r3
	addi r3, r1, 0x494
	bl strcat
	addi r3, r1, 0x494
	bl FontGetMessageWidth
	clrlwi r3, r3, 16
	lis r0, 0x4330
	stw r3, 0x814(r1)
	addi r3, r1, 0x464
	lfs f0, 0x0(r28)
	stw r0, 0x810(r1)
	lfd f3, 0x350(r30)
	fsubs f2, f0, f29
	lfd f0, 0x810(r1)
	lfs f1, 0x4(r28)
	fsubs f3, f0, f3
	lfs f0, float_22_8041be48(r2)
	lfs f5, float_8_8041be44(r2)
	fsubs f0, f1, f0
	lfs f1, float_1_8041bde8(r2)
	fadds f4, f3, f2
	lfs f3, float_0_8041bde4(r2)
	fadds f2, f1, f0
	fadds f1, f5, f4
	bl PSMTXTrans
	lfs f1, float_1p5_8041be4c(r2)
	addi r3, r1, 0x434
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	addi r3, r1, 0x464
	addi r4, r1, 0x434
	mr r5, r3
	bl PSMTXConcat
	lwz r0, dat_8041bda8(r2)
	addi r3, r1, 0x464
	addi r6, r1, 0x44
	li r4, 0x0
	stw r0, 0x44(r1)
	li r5, 0x201
	bl iconDispGxCol
	addi r23, r28, 0x4
	li r22, 0x0
	li r25, 0x0
	la r24, stone_id(r13)
	@24:
	addi r0, r22, 0x1
	li r3, 0x1
	slw r0, r3, r0
	and. r0, r26, r0
	beq @25
	xoris r3, r25, 0x8000
	lis r0, 0x4330
	stw r3, 0x824(r1)
	addi r3, r1, 0x464
	lfs f3, 0x0(r28)
	stw r0, 0x820(r1)
	lfs f1, float_106_8041be50(r2)
	lfd f2, 0x358(r30)
	lfd f0, 0x820(r1)
	fsubs f5, f3, f1
	lfs f1, 0x0(r23)
	fsubs f4, f0, f2
	lfs f0, float_52_8041be54(r2)
	lfs f3, float_0_8041bde4(r2)
	fsubs f2, f1, f0
	fadds f1, f5, f4
	bl PSMTXTrans
	lwz r3, wp(r13)
	addi r4, r1, 0x74
	lwz r0, 0x20(r3)
	cmpw r27, r0
	bne @26
	addi r4, r1, 0x78
	@26:
	lwz r4, 0x0(r4)
	addi r3, r1, 0x464
	lwz r0, 0x0(r24)
	addi r6, r1, 0x40
	stw r4, 0x40(r1)
	li r4, 0x0
	clrlwi r5, r0, 16
	bl iconDispGxCol
	@25:
	addi r22, r22, 0x1
	addi r24, r24, 0x4
	cmpwi r22, 0x7
	addi r25, r25, 0x20
	blt @24
	@18:
	addi r27, r27, 0x1
	addi r28, r28, 0x1c
	cmpwi r27, 0x4
	addi r29, r29, 0x4000
	blt @14
	lwz r3, wp(r13)
	lhz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq @27
	lfs f1, 0x2c(r3)
	lfs f0, float_0p05_8041be58(r2)
	fadds f0, f1, f0
	stfs f0, 0x2c(r3)
	b @28
	@27:
	lfs f1, 0x2c(r3)
	lfs f0, float_0p05_8041be58(r2)
	fsubs f0, f1, f0
	stfs f0, 0x2c(r3)
	@28:
	lwz r3, wp(r13)
	lfs f0, float_0_8041bde4(r2)
	lfs f1, 0x2c(r3)
	fcmpo cr0, f1, f0
	bge @29
	stfs f0, 0x2c(r3)
	@29:
	lwz r3, wp(r13)
	lfs f0, float_1_8041bde8(r2)
	lfs f1, 0x2c(r3)
	fcmpo cr0, f1, f0
	ble @30
	stfs f0, 0x2c(r3)
	@30:
	lwz r3, wp(r13)
	lfs f1, 0x2c(r3)
	bl nameMaskGX
	lwz r3, wp(r13)
	lwz r0, 0x18(r3)
	cmpwi r0, 0x64
	blt @31
	cmpwi r0, 0xc8
	bge @31
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lwz r12, dat_8041bdac(r2)
	addi r4, r1, 0x238
	lwz r11, 0x54(r30)
	addi r5, r1, 0x22c
	lwz r10, 0x58(r30)
	addi r6, r1, 0x3c
	lwz r9, 0x5c(r30)
	li r3, 0xf
	lwz r8, 0x48(r30)
	lwz r7, 0x4c(r30)
	lwz r0, 0x50(r30)
	stw r12, 0x3c(r1)
	stw r11, 0x22c(r1)
	stw r10, 0x230(r1)
	stw r9, 0x234(r1)
	stw r8, 0x238(r1)
	stw r7, 0x23c(r1)
	stw r0, 0x240(r1)
	bl winTexSet
	lwz r3, wp(r13)
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit_x2
	lwz r20, dat_8041bdb0(r2)
	addi r5, r1, 0x220
	lwz r12, 0x6c(r30)
	addi r6, r1, 0x214
	lwz r11, 0x70(r30)
	addi r7, r1, 0x38
	lwz r10, 0x74(r30)
	li r3, 0x13
	lwz r9, 0x60(r30)
	li r4, 0x1f
	lwz r8, 0x64(r30)
	lwz r0, 0x68(r30)
	stw r20, 0x38(r1)
	stw r12, 0x214(r1)
	stw r11, 0x218(r1)
	stw r10, 0x21c(r1)
	stw r9, 0x220(r1)
	stw r8, 0x224(r1)
	stw r0, 0x228(r1)
	bl winTexSet_x2
	li r24, 0x0
	mr r23, r24
	@32:
	lwz r3, wp(r13)
	lwz r0, 0x24(r3)
	cmpw r24, r0
	bne @33
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	subfic r0, r23, 0x32
	lwz r8, 0x78(r30)
	xoris r3, r0, 0x8000
	lis r0, 0x4330
	stw r3, 0x824(r1)
	addi r4, r1, 0x208
	lwz r7, 0x80(r30)
	addi r5, r1, 0x1f0
	stw r0, 0x820(r1)
	addi r6, r1, 0x34
	lwz r0, 0x7c(r30)
	li r3, 0x33
	lfd f1, 0x358(r30)
	lfd f0, 0x820(r1)
	stw r0, 0x200(r1)
	fsubs f0, f0, f1
	lwz r12, dat_8041bdb4(r2)
	lwz r11, 0x84(r30)
	lwz r10, 0x88(r30)
	stfs f0, 0x200(r1)
	lwz r9, 0x8c(r30)
	lwz r0, 0x200(r1)
	stw r12, 0x34(r1)
	stw r11, 0x1f0(r1)
	stw r10, 0x1f4(r1)
	stw r9, 0x1f8(r1)
	stw r8, 0x1fc(r1)
	stw r7, 0x204(r1)
	stw r8, 0x208(r1)
	stw r0, 0x20c(r1)
	stw r7, 0x210(r1)
	bl winTexSet
	lwz r3, wp(r13)
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit_x2
	subfic r0, r23, 0x36
	lwz r9, 0x90(r30)
	xoris r3, r0, 0x8000
	lis r0, 0x4330
	stw r3, 0x81c(r1)
	addi r3, r24, 0x15
	lwz r8, 0x98(r30)
	addi r5, r1, 0x1e4
	stw r0, 0x818(r1)
	addi r6, r1, 0x1cc
	lwz r0, 0x94(r30)
	addi r7, r1, 0x30
	lfd f1, 0x358(r30)
	li r4, 0x33
	lfd f0, 0x818(r1)
	stw r0, 0x1dc(r1)
	fsubs f0, f0, f1
	lwz r20, dat_8041bdb8(r2)
	lwz r12, 0x9c(r30)
	lwz r11, 0xa0(r30)
	stfs f0, 0x1dc(r1)
	lwz r10, 0xa4(r30)
	lwz r0, 0x1dc(r1)
	stw r20, 0x30(r1)
	stw r12, 0x1cc(r1)
	stw r11, 0x1d0(r1)
	stw r10, 0x1d4(r1)
	stw r9, 0x1d8(r1)
	stw r8, 0x1e0(r1)
	stw r9, 0x1e4(r1)
	stw r0, 0x1e8(r1)
	stw r8, 0x1ec(r1)
	bl winTexSet_x2
	b @34
	@33:
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit_x2
	subfic r0, r23, 0x32
	lwz r9, 0xa8(r30)
	xoris r3, r0, 0x8000
	lis r0, 0x4330
	stw r3, 0x824(r1)
	addi r3, r24, 0x15
	lwz r8, 0xb0(r30)
	addi r5, r1, 0x1c0
	stw r0, 0x820(r1)
	addi r6, r1, 0x1a8
	lwz r0, 0xac(r30)
	addi r7, r1, 0x2c
	lfd f1, 0x358(r30)
	li r4, 0x33
	lfd f0, 0x820(r1)
	stw r0, 0x1b8(r1)
	fsubs f0, f0, f1
	lwz r20, dat_8041bdbc(r2)
	lwz r12, 0xb4(r30)
	lwz r11, 0xb8(r30)
	stfs f0, 0x1b8(r1)
	lwz r10, 0xbc(r30)
	lwz r0, 0x1b8(r1)
	stw r20, 0x2c(r1)
	stw r12, 0x1a8(r1)
	stw r11, 0x1ac(r1)
	stw r10, 0x1b0(r1)
	stw r9, 0x1b4(r1)
	stw r8, 0x1bc(r1)
	stw r9, 0x1c0(r1)
	stw r0, 0x1c4(r1)
	stw r8, 0x1c8(r1)
	bl winTexSet_x2
	@34:
	addi r24, r24, 0x1
	addi r23, r23, 0x32
	cmpwi r24, 0x3
	blt @32
	@31:
	lwz r3, wp(r13)
	lwz r0, 0x18(r3)
	cmpwi r0, 0xc8
	blt @35
	cmpwi r0, 0x12c
	bge @35
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lwz r12, dat_8041bdc0(r2)
	addi r4, r1, 0x19c
	lwz r11, 0xcc(r30)
	addi r5, r1, 0x190
	lwz r10, 0xd0(r30)
	addi r6, r1, 0x28
	lwz r9, 0xd4(r30)
	li r3, 0xf
	lwz r8, 0xc0(r30)
	lwz r7, 0xc4(r30)
	lwz r0, 0xc8(r30)
	stw r12, 0x28(r1)
	stw r11, 0x190(r1)
	stw r10, 0x194(r1)
	stw r9, 0x198(r1)
	stw r8, 0x19c(r1)
	stw r7, 0x1a0(r1)
	stw r0, 0x1a4(r1)
	bl winTexSet
	lwz r3, wp(r13)
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit_x2
	lwz r20, dat_8041bdc4(r2)
	addi r5, r1, 0x184
	lwz r12, 0xe4(r30)
	addi r6, r1, 0x178
	lwz r11, 0xe8(r30)
	addi r7, r1, 0x24
	lwz r10, 0xec(r30)
	li r3, 0x14
	lwz r9, 0xd8(r30)
	li r4, 0x1f
	lwz r8, 0xdc(r30)
	lwz r0, 0xe0(r30)
	stw r20, 0x24(r1)
	stw r12, 0x178(r1)
	stw r11, 0x17c(r1)
	stw r10, 0x180(r1)
	stw r9, 0x184(r1)
	stw r8, 0x188(r1)
	stw r0, 0x18c(r1)
	bl winTexSet_x2
	li r24, 0x0
	mr r23, r24
	@36:
	lwz r3, wp(r13)
	lwz r0, 0x28(r3)
	cmpw r24, r0
	bne @37
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	subfic r0, r23, 0x1e
	lwz r8, 0xf0(r30)
	xoris r3, r0, 0x8000
	lis r0, 0x4330
	stw r3, 0x824(r1)
	addi r4, r1, 0x16c
	lwz r7, 0xf8(r30)
	addi r5, r1, 0x154
	stw r0, 0x820(r1)
	addi r6, r1, 0x20
	lwz r0, 0xf4(r30)
	li r3, 0x33
	lfd f1, 0x358(r30)
	lfd f0, 0x820(r1)
	stw r0, 0x164(r1)
	fsubs f0, f0, f1
	lwz r12, dat_8041bdc8(r2)
	lwz r11, 0xfc(r30)
	lwz r10, 0x100(r30)
	stfs f0, 0x164(r1)
	lwz r9, 0x104(r30)
	lwz r0, 0x164(r1)
	stw r12, 0x20(r1)
	stw r11, 0x154(r1)
	stw r10, 0x158(r1)
	stw r9, 0x15c(r1)
	stw r8, 0x160(r1)
	stw r7, 0x168(r1)
	stw r8, 0x16c(r1)
	stw r0, 0x170(r1)
	stw r7, 0x174(r1)
	bl winTexSet
	lwz r3, wp(r13)
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit_x2
	subfic r0, r23, 0x22
	lwz r9, 0x108(r30)
	xoris r3, r0, 0x8000
	lis r0, 0x4330
	stw r3, 0x81c(r1)
	addi r3, r24, 0x18
	lwz r8, 0x110(r30)
	addi r5, r1, 0x148
	stw r0, 0x818(r1)
	addi r6, r1, 0x130
	lwz r0, 0x10c(r30)
	addi r7, r1, 0x1c
	lfd f1, 0x358(r30)
	li r4, 0x33
	lfd f0, 0x818(r1)
	stw r0, 0x140(r1)
	fsubs f0, f0, f1
	lwz r20, dat_8041bdcc(r2)
	lwz r12, 0x114(r30)
	lwz r11, 0x118(r30)
	stfs f0, 0x140(r1)
	lwz r10, 0x11c(r30)
	lwz r0, 0x140(r1)
	stw r20, 0x1c(r1)
	stw r12, 0x130(r1)
	stw r11, 0x134(r1)
	stw r10, 0x138(r1)
	stw r9, 0x13c(r1)
	stw r8, 0x144(r1)
	stw r9, 0x148(r1)
	stw r0, 0x14c(r1)
	stw r8, 0x150(r1)
	bl winTexSet_x2
	b @38
	@37:
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit_x2
	subfic r0, r23, 0x1e
	lwz r9, 0x120(r30)
	xoris r3, r0, 0x8000
	lis r0, 0x4330
	stw r3, 0x824(r1)
	addi r3, r24, 0x18
	lwz r8, 0x128(r30)
	addi r5, r1, 0x124
	stw r0, 0x820(r1)
	addi r6, r1, 0x10c
	lwz r0, 0x124(r30)
	addi r7, r1, 0x18
	lfd f1, 0x358(r30)
	li r4, 0x33
	lfd f0, 0x820(r1)
	stw r0, 0x11c(r1)
	fsubs f0, f0, f1
	lwz r20, dat_8041bdd0(r2)
	lwz r12, 0x12c(r30)
	lwz r11, 0x130(r30)
	stfs f0, 0x11c(r1)
	lwz r10, 0x134(r30)
	lwz r0, 0x11c(r1)
	stw r20, 0x18(r1)
	stw r12, 0x10c(r1)
	stw r11, 0x110(r1)
	stw r10, 0x114(r1)
	stw r9, 0x118(r1)
	stw r8, 0x120(r1)
	stw r9, 0x124(r1)
	stw r0, 0x128(r1)
	stw r8, 0x12c(r1)
	bl winTexSet_x2
	@38:
	addi r24, r24, 0x1
	addi r23, r23, 0x32
	cmpwi r24, 0x2
	blt @36
	@35:
	lwz r4, wp(r13)
	lwz r0, 0x18(r4)
	cmpwi r0, 0x33
	bne @39
	lwz r0, 0x34(r4)
	cmpwi r0, 0x4
	bge @39
	lwz r27, 0x138(r30)
	slwi r0, r0, 2
	lwz r26, 0x13c(r30)
	addi r3, r1, 0x3f4
	lwz r25, 0x140(r30)
	lwz r24, 0x144(r30)
	lwz r23, 0x148(r30)
	lwz r22, 0x14c(r30)
	lwz r21, 0x150(r30)
	lwz r20, 0x154(r30)
	lwz r12, 0x158(r30)
	lwz r11, 0x15c(r30)
	lwz r10, 0x160(r30)
	lwz r9, 0x164(r30)
	lwz r8, 0x168(r30)
	lwz r7, 0x16c(r30)
	lwz r6, 0x170(r30)
	lwz r5, 0x174(r30)
	lwz r4, 0x30(r4)
	stw r27, 0x3f4(r1)
	slwi r4, r4, 4
	lfd f2, 0x348(r30)
	stw r26, 0x3f8(r1)
	add r0, r4, r0
	stw r25, 0x3fc(r1)
	stw r24, 0x400(r1)
	stw r23, 0x404(r1)
	stw r22, 0x408(r1)
	stw r21, 0x40c(r1)
	stw r20, 0x410(r1)
	stw r12, 0x414(r1)
	stw r11, 0x418(r1)
	stw r10, 0x41c(r1)
	stw r9, 0x420(r1)
	stw r8, 0x424(r1)
	stw r7, 0x428(r1)
	stw r6, 0x42c(r1)
	stw r5, 0x430(r1)
	lfsx f1, r3, r0
	bl fmod
	frsp f0, f1
	lfs f3, float_0_8041bde4(r2)
	fcmpu cr0, f0, f3
	bne @40
	lwz r3, wp(r13)
	lis r5, 0x4330
	stw r5, 0x818(r1)
	lwz r0, 0x30(r3)
	lwz r3, 0x34(r3)
	srwi r7, r0, 31
	clrlwi r6, r0, 31
	add r4, r7, r0
	srwi r0, r3, 31
	srawi r4, r4, 1
	xor r6, r6, r7
	add r0, r0, r3
	stw r5, 0x810(r1)
	srawi r0, r0, 1
	xoris r3, r4, 0x8000
	xoris r0, r0, 0x8000
	stw r3, 0x81c(r1)
	subf r3, r7, r6
	lfd f2, 0x358(r30)
	stw r0, 0x814(r1)
	xoris r0, r3, 0x8000
	lfd f1, 0x818(r1)
	lfd f0, 0x810(r1)
	stw r0, 0x824(r1)
	fsubs f4, f1, f2
	fsubs f0, f0, f2
	stw r5, 0x820(r1)
	lfd f1, 0x820(r1)
	fcmpu cr0, f4, f0
	fsubs f2, f1, f2
	bne @41
	lfs f1, float_140_8041be60(r2)
	fmr f29, f3
	lfs f0, float_120_8041be5c(r2)
	fnmsubs f30, f1, f4, f0
	b @42
	@41:
	lfs f1, float_300_8041be68(r2)
	lfs f0, float_neg150_8041be64(r2)
	lfs f30, float_50_8041be6c(r2)
	fmadds f29, f1, f2, f0
	b @42
	@40:
	fmr f29, f3
	lfs f30, float_50_8041be6c(r2)
	@42:
	lwz r3, wp(r13)
	lfs f0, float_40_8041be14(r2)
	lwz r3, 0x4(r3)
	fsubs f30, f30, f0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lfs f0, float_2_8041be70(r2)
	addi r7, r1, 0x3f4
	lwz r3, 0x178(r30)
	addi r4, r1, 0x100
	lwz r0, 0x17c(r30)
	fadds f1, f0, f29
	stw r3, 0xf4(r1)
	fsubs f0, f30, f0
	lwz r9, 0x180(r30)
	addi r5, r1, 0xe8
	stw r0, 0xf8(r1)
	lwz r20, dat_8041bdd4(r2)
	addi r6, r1, 0x14
	stfs f1, 0xf4(r1)
	li r3, 0x1d
	lwz r12, 0x184(r30)
	stfs f0, 0xf8(r1)
	lwz r11, 0x188(r30)
	lwz r10, 0x18c(r30)
	lwz r8, 0xf4(r1)
	lwz r0, 0xf8(r1)
	stw r20, 0x14(r1)
	lwz r20, wp(r13)
	stw r12, 0xe8(r1)
	stw r11, 0xec(r1)
	stw r10, 0xf0(r1)
	stw r8, 0x100(r1)
	stw r0, 0x104(r1)
	stw r9, 0x108(r1)
	lwz r8, 0x30(r20)
	lwz r0, 0x34(r20)
	slwi r8, r8, 4
	stw r9, 0xfc(r1)
	slwi r0, r0, 2
	add r0, r8, r0
	lfsx f1, r7, r0
	bl winTexSetRot
	lwz r3, 0x190(r30)
	addi r7, r1, 0x3f4
	lwz r0, 0x194(r30)
	addi r4, r1, 0xdc
	stw r3, 0xd0(r1)
	addi r5, r1, 0xc4
	lwz r9, 0x198(r30)
	addi r6, r1, 0x10
	stw r0, 0xd4(r1)
	li r3, 0x1d
	lwz r20, 0x78(r1)
	stfs f29, 0xd0(r1)
	lwz r12, 0x19c(r30)
	stfs f30, 0xd4(r1)
	lwz r11, 0x1a0(r30)
	lwz r10, 0x1a4(r30)
	lwz r8, 0xd0(r1)
	lwz r0, 0xd4(r1)
	stw r20, 0x10(r1)
	lwz r20, wp(r13)
	stw r12, 0xc4(r1)
	stw r11, 0xc8(r1)
	stw r10, 0xcc(r1)
	stw r8, 0xdc(r1)
	stw r0, 0xe0(r1)
	stw r9, 0xe4(r1)
	lwz r8, 0x30(r20)
	lwz r0, 0x34(r20)
	slwi r8, r8, 4
	stw r9, 0xd8(r1)
	slwi r0, r0, 2
	add r0, r8, r0
	lfsx f1, r7, r0
	bl winTexSetRot
	@39:
	lwz r3, wp(r13)
	lhz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 25, 25
	bne @43
	lwz r3, 0x4(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl winTexInit
	lwz r0, dat_8041bdd8(r2)
	addi r4, r1, 0xb8
	lwz r10, 0x1b4(r30)
	addi r5, r1, 0xa0
	lwz r9, 0x1b8(r30)
	addi r6, r1, 0xc
	lwz r8, 0x1bc(r30)
	li r3, 0x0
	stw r0, 0xc(r1)
	lwz r7, 0x1a8(r30)
	lwz r0, 0x1ac(r30)
	stw r10, 0xa0(r1)
	lwz r10, wp(r13)
	stw r9, 0xa4(r1)
	lfs f2, float_2_8041be70(r2)
	stw r8, 0xa8(r1)
	lwz r8, 0x1b0(r30)
	lfs f1, 0x8(r10)
	lfs f0, 0xc(r10)
	fadds f1, f2, f1
	stw r7, 0xac(r1)
	fsubs f0, f0, f2
	stw r0, 0xb0(r1)
	stfs f1, 0xac(r1)
	stfs f0, 0xb0(r1)
	lwz r7, 0xac(r1)
	lwz r0, 0xb0(r1)
	stw r8, 0xb4(r1)
	stw r7, 0xb8(r1)
	stw r0, 0xbc(r1)
	stw r8, 0xc0(r1)
	bl winTexSet
	lwz r8, 0x78(r1)
	addi r4, r1, 0x94
	lwz r11, 0x1cc(r30)
	addi r5, r1, 0x7c
	lwz r10, 0x1d0(r30)
	addi r6, r1, 0x8
	lwz r9, 0x1d4(r30)
	li r3, 0x0
	lwz r7, 0x1c0(r30)
	lwz r0, 0x1c4(r30)
	stw r8, 0x8(r1)
	lwz r12, wp(r13)
	lwz r8, 0x1c8(r30)
	stw r11, 0x7c(r1)
	stw r10, 0x80(r1)
	stw r9, 0x84(r1)
	stw r7, 0x88(r1)
	lfs f1, 0x8(r12)
	lfs f0, 0xc(r12)
	stw r0, 0x8c(r1)
	stfs f1, 0x88(r1)
	stfs f0, 0x8c(r1)
	lwz r7, 0x88(r1)
	lwz r0, 0x8c(r1)
	stw r8, 0x90(r1)
	stw r7, 0x94(r1)
	stw r0, 0x98(r1)
	stw r8, 0x9c(r1)
	bl winTexSet
	@43:
	lfs f1, 0x34c(r1)
	lfs f2, 0x350(r1)
	lfs f3, 0x354(r1)
	lfs f4, 0x358(r1)
	lfs f5, 0x35c(r1)
	lfs f6, 0x360(r1)
	bl GXSetViewport
	addi r3, r1, 0x330
	bl GXSetProjectionv
	bl camGetCurPtr
	li r0, 0x4c
	subi r5, r3, 0x4
	addi r4, r1, 0x594
	mtctr r0
	@44:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz @44
	@2:
	psq_l f31, -0x778(r1), 0, 0
	lfd f31, 0x880(r1)
	psq_l f30, -0x788(r1), 0, 0
	lfd f30, 0x870(r1)
	psq_l f29, -0x798(r1), 0, 0
	lfd f29, 0x860(r1)
	lmw r20, 0x830(r1)
	lwz r0, 0x894(r1)
	mtlr r0
	addi r1, r1, 0x890
	blr
}

asm void loadMain(SequenceWork* seq) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	lis r5, lbl_80349DE8@ha
	lis r4, vec3_802ed670@ha
	stw r0, 0x54(r1)
	stmw r24, 0x30(r1)
	mr r26, r3
	li r3, 0x0
	addi r29, r5, lbl_80349DE8@l
	addi r30, r4, vec3_802ed670@l
	bl keyGetButtonTrg
	mr r0, r3
	li r3, 0x0
	mr r28, r0
	bl keyGetButtonRep
	li r3, 0x0
	bl keyGetDirRep
	mr r27, r3
	bl cardGetCode
	mr r31, r3
	bl cardIsExec
	cmpwi r3, 0x0
	bne @1
	bl fadeIsFinish
	cmpwi r3, 0x0
	bne @2
	@1:
	li r28, 0x0
	li r27, 0x0
	@2:
	lwz r3, wp(r13)
	lwz r0, 0x1c(r3)
	cmpw r0, r31
	beq @3
	li r28, 0x0
	li r27, 0x0
	@3:
	stw r31, 0x1c(r3)
	li r24, 0x0
	li r25, 0x0
	@4:
	bl cardGetFilePtr
	addi r0, r25, 0x2000
	lhzx r3, r3, r0
	clrlwi. r0, r3, 31
	beq @5
	rlwinm. r0, r3, 0, 30, 30
	bne @5
	addi r24, r24, 0x1
	addi r25, r25, 0x4000
	cmpwi r24, 0x4
	blt @4
	@5:
	cmpwi r24, 0x4
	bge @6
	lwz r3, wp(r13)
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 28, 26
	sth r0, 0x0(r3)
	b @7
	@6:
	lwz r3, wp(r13)
	lhz r0, 0x0(r3)
	ori r0, r0, 0x10
	sth r0, 0x0(r3)
	@7:
	lwz r3, wp(r13)
	li r24, 0x0
	mr r25, r24
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 27, 25
	sth r0, 0x0(r3)
	@8:
	bl cardGetFilePtr
	addi r0, r25, 0x2000
	lhzx r3, r3, r0
	clrlwi. r0, r3, 31
	bne @9
	rlwinm. r0, r3, 0, 30, 30
	beq @10
	@9:
	addi r24, r24, 0x1
	addi r25, r25, 0x4000
	cmpwi r24, 0x4
	blt @8
	@10:
	cmpwi r24, 0x4
	blt @11
	lwz r3, wp(r13)
	lhz r0, 0x0(r3)
	ori r0, r0, 0x20
	sth r0, 0x0(r3)
	@11:
	lwz r6, wp(r13)
	lwz r3, 0x18(r6)
	cmpwi r3, 0x21
	beq @12
	bge @13
	cmpwi r3, 0x15
	beq @14
	bge @15
	cmpwi r3, 0xa
	beq @16
	bge @17
	cmpwi r3, 0x1
	beq @18
	bge @19
	cmpwi r3, 0x0
	bge @20
	b @19
	@17:
	cmpwi r3, 0x14
	bge @21
	cmpwi r3, 0xc
	bge @19
	b @22
	@15:
	cmpwi r3, 0x1e
	beq @23
	bge @24
	cmpwi r3, 0x18
	beq @25
	bge @19
	cmpwi r3, 0x17
	bge @26
	b @27
	@24:
	cmpwi r3, 0x20
	bge @28
	b @29
	@13:
	cmpwi r3, 0x33
	beq @30
	bge @31
	cmpwi r3, 0x29
	beq @32
	bge @33
	cmpwi r3, 0x23
	beq @34
	blt @35
	cmpwi r3, 0x28
	bge @36
	b @19
	@33:
	cmpwi r3, 0x32
	bge @37
	cmpwi r3, 0x2b
	bge @19
	b @38
	@31:
	cmpwi r3, 0x64
	beq @39
	bge @40
	cmpwi r3, 0x35
	beq @41
	bge @19
	b @42
	@40:
	cmpwi r3, 0xc8
	beq @43
	b @19
	@20:
	addi r0, r3, 0x1
	stw r0, 0x18(r6)
	@18:
	addi r3, r30, 0x360
	bl msgSearch
	lwz r4, wp(r13)
	rlwinm. r0, r27, 0, 19, 19
	stw r3, 0x38(r4)
	lwz r4, wp(r13)
	lwz r31, 0x20(r4)
	beq @44
	mulli r0, r31, 0x1c
	addi r3, r29, 0x40
	add r3, r3, r0
	lbz r0, 0x18(r3)
	stw r0, 0x20(r4)
	b @45
	@44:
	rlwinm. r0, r27, 0, 18, 18
	beq @46
	mulli r0, r31, 0x1c
	addi r3, r29, 0x40
	add r3, r3, r0
	lbz r0, 0x19(r3)
	stw r0, 0x20(r4)
	b @45
	@46:
	rlwinm. r0, r27, 0, 17, 17
	beq @47
	mulli r0, r31, 0x1c
	addi r3, r29, 0x40
	add r3, r3, r0
	lbz r0, 0x1a(r3)
	stw r0, 0x20(r4)
	b @45
	@47:
	rlwinm. r0, r27, 0, 16, 16
	beq @48
	mulli r0, r31, 0x1c
	addi r3, r29, 0x40
	add r3, r3, r0
	lbz r0, 0x1b(r3)
	stw r0, 0x20(r4)
	b @45
	@48:
	rlwinm. r0, r28, 0, 23, 23
	beq @49
	bl cardGetFilePtr
	lwz r6, wp(r13)
	lwz r5, 0x20(r6)
	slwi r4, r5, 14
	cmpwi r5, 0x6
	addi r0, r4, 0x2000
	lhzx r3, r3, r0
	beq @50
	bge @51
	cmpwi r5, 0x4
	beq @52
	bge @53
	cmpwi r5, 0x0
	bge @54
	b @45
	@51:
	cmpwi r5, 0x8
	beq @55
	bge @45
	b @56
	@54:
	rlwinm. r0, r3, 0, 30, 30
	beq @57
	li r3, 0x13
	bl psndSFXOn
	b @45
	@57:
	clrlwi. r0, r3, 31
	beq @58
	li r0, 0x1e
	li r3, 0x12
	stw r0, 0x18(r6)
	bl psndSFXOn
	b @45
	@58:
	li r0, 0x14
	li r3, 0x12
	stw r0, 0x18(r6)
	bl psndSFXOn
	b @45
	@52:
	lhz r0, 0x0(r6)
	rlwinm. r0, r0, 0, 27, 27
	bne @45
	li r26, 0x0
	mr r25, r26
	@59:
	bl cardGetFilePtr
	addi r0, r25, 0x2000
	lhzx r3, r3, r0
	clrlwi. r0, r3, 31
	beq @60
	rlwinm. r0, r3, 0, 30, 30
	bne @60
	addi r26, r26, 0x1
	addi r25, r25, 0x4000
	cmpwi r26, 0x4
	blt @59
	@60:
	cmpwi r26, 0x4
	bge @61
	li r3, 0x12
	bl psndSFXOn
	lwz r3, wp(r13)
	li r4, 0x0
	li r0, 0x28
	stw r4, 0x20(r3)
	lwz r3, wp(r13)
	stw r0, 0x18(r3)
	b @45
	@61:
	li r3, 0x13
	bl psndSFXOn
	b @45
	@53:
	lhz r0, 0x0(r6)
	rlwinm. r0, r0, 0, 26, 26
	bne @45
	li r26, 0x0
	mr r25, r26
	@62:
	bl cardGetFilePtr
	addi r0, r25, 0x2000
	lhzx r3, r3, r0
	rlwinm. r0, r3, 0, 30, 30
	bne @63
	clrlwi. r0, r3, 31
	beq @64
	@63:
	addi r26, r26, 0x1
	addi r25, r25, 0x4000
	cmpwi r26, 0x4
	blt @62
	@64:
	cmpwi r26, 0x4
	bge @65
	li r3, 0x12
	bl psndSFXOn
	lwz r3, wp(r13)
	li r4, 0x0
	li r0, 0x32
	stw r4, 0x20(r3)
	lwz r3, wp(r13)
	stw r0, 0x18(r3)
	b @45
	@65:
	li r3, 0x13
	bl psndSFXOn
	b @45
	@50:
	li r3, 0x13
	bl psndSFXOn
	lwz r3, wp(r13)
	li r0, 0xa
	stw r0, 0x18(r3)
	b @45
	@56:
	li r3, 0x12
	bl psndSFXOn
	li r3, 0x800
	bl psndBGMOff
	lwz r3, wp(r13)
	li r0, 0x64
	stw r0, 0x18(r3)
	b @45
	@55:
	li r3, 0x12
	bl psndSFXOn
	lwz r3, wp(r13)
	li r0, 0xc8
	stw r0, 0x18(r3)
	b @45
	@49:
	rlwinm. r0, r28, 0, 22, 22
	beq @45
	li r3, 0x13
	bl psndSFXOn
	lwz r3, wp(r13)
	li r0, 0xa
	stw r0, 0x18(r3)
	@45:
	lwz r3, wp(r13)
	lwz r0, 0x20(r3)
	cmpw r31, r0
	beq @66
	cmpwi r0, 0x4
	bge @67
	li r3, 0x9
	bl psndSFXOn
	b @66
	@67:
	li r3, 0x5
	bl psndSFXOn
	@66:
	lwz r5, wp(r13)
	addi r4, r29, 0x40
	lwz r0, 0x20(r5)
	mulli r0, r0, 0x1c
	add r3, r4, r0
	lfsx f1, r4, r0
	lfs f0, 0x8(r3)
	fadds f0, f1, f0
	stfs f0, 0x10(r5)
	lwz r5, wp(r13)
	lwz r0, 0x20(r5)
	mulli r0, r0, 0x1c
	add r3, r4, r0
	lfs f1, 0x4(r3)
	lfs f0, 0xc(r3)
	fadds f0, f1, f0
	stfs f0, 0x14(r5)
	b @19
	@16:
	lwz r0, dat_8041bd6c(r2)
	addi r5, r1, 0x1c
	li r3, 0x1b
	li r4, 0x0
	stw r0, 0x1c(r1)
	bl fadeEntry
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@22:
	bl fadeIsFinish
	cmpwi r3, 0x0
	beq @19
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl seqSetSeq
	b @19
	@21:
	lhz r0, 0x0(r6)
	lis r3, evt_memcard_start@ha
	addi r3, r3, evt_memcard_start@l
	li r4, 0x0
	ori r0, r0, 0x40
	li r5, 0x0
	sth r0, 0x0(r6)
	li r6, 0x0
	bl evtEntryType
	lwz r4, wp(r13)
	stw r3, 0x3c(r4)
	lwz r3, wp(r13)
	lwz r0, 0x20(r3)
	lwz r3, 0x3c(r3)
	stw r0, 0x9c(r3)
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@14:
	lwz r3, 0x3c(r6)
	lwz r3, 0x15c(r3)
	bl evtCheckID
	cmpwi r3, 0x0
	bne @19
	lwz r5, wp(r13)
	lis r3, 0xfd05
	addi r4, r3, 0xf80
	lhz r0, 0x0(r5)
	li r3, 0x0
	rlwinm r0, r0, 0, 26, 24
	sth r0, 0x0(r5)
	bl evtGetValue
	cmpwi r3, 0x1
	bne @68
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@68:
	lwz r3, wp(r13)
	li r0, 0x1
	stw r0, 0x18(r3)
	b @19
	@27:
	lwz r0, dat_8041bd70(r2)
	addi r5, r1, 0x18
	li r3, 0x1b
	li r4, 0x0
	stw r0, 0x18(r1)
	bl fadeEntry
	li r3, 0x200
	li r4, 0x7d0
	li r5, 0x0
	bl psndBGMOff_f_d
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@26:
	bl fadeIsFinish
	cmpwi r3, 0x0
	beq @19
	lwz r7, wp(r13)
	la r3, evt_continue(r13)
	li r4, 0x0
	li r5, 0x0
	lhz r0, 0x0(r7)
	li r6, 0x0
	ori r0, r0, 0x40
	sth r0, 0x0(r7)
	bl evtEntryType
	lwz r4, wp(r13)
	stw r3, 0x3c(r4)
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@25:
	lwz r3, 0x3c(r6)
	lwz r3, 0x15c(r3)
	bl evtCheckID
	cmpwi r3, 0x0
	bne @19
	lwz r3, wp(r13)
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 26, 24
	sth r0, 0x0(r3)
	bl continueGame
	b @19
	@23:
	lwz r0, dat_8041bd74(r2)
	addi r5, r1, 0x14
	li r3, 0x1b
	li r4, 0x0
	stw r0, 0x14(r1)
	bl fadeEntry
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@29:
	bl fadeIsFinish
	cmpwi r3, 0x0
	beq @19
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@28:
	bl nameEntPrepare
	cmpwi r3, 0x0
	beq @19
	li r3, 0x0
	bl nameEntOn
	lwz r0, dat_8041bd78(r2)
	addi r5, r1, 0x10
	li r3, 0x1c
	li r4, 0x0
	stw r0, 0x10(r1)
	bl fadeEntry
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@12:
	bl fadeIsFinish
	cmpwi r3, 0x0
	beq @19
	bl nameEntWait
	cmpwi r3, 0x0
	bne @19
	lwz r0, dat_8041bd7c(r2)
	addi r5, r1, 0xc
	li r3, 0x18
	li r4, 0x0
	stw r0, 0xc(r1)
	bl fadeEntry
	bl nameEntIsCancel
	cmpwi r3, 0x0
	bne @69
	li r3, 0x200
	li r4, 0xbb8
	li r5, 0x0
	bl psndBGMOff_f_d
	@69:
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@35:
	bl fadeIsFinish
	cmpwi r3, 0x0
	beq @19
	bl nameEntOff
	bl nameEntIsCancel
	cmpwi r3, 0x0
	beq @70
	lwz r0, dat_8041bd80(r2)
	addi r5, r1, 0x8
	li r3, 0x1c
	li r4, 0x0
	stw r0, 0x8(r1)
	bl fadeEntry
	lwz r3, wp(r13)
	li r0, 0x1
	stw r0, 0x18(r3)
	b @19
	@70:
	bl nameEntGetName
	lwz r5, gp(r13)
	mr r4, r3
	addi r3, r5, 0x11bc
	bl strcpy
	lwz r4, wp(r13)
	lwz r3, gp(r13)
	lwz r0, 0x20(r4)
	stw r0, 0x11b8(r3)
	bl stg0_00_init
	lwz r4, wp(r13)
	lwz r3, gp(r13)
	lwz r0, 0x20(r4)
	stw r0, 0x11d0(r3)
	bl marioPartyKill
	bl marioGetPtr
	li r4, 0x0
	li r0, 0x19
	stb r4, 0x243(r3)
	stb r4, 0x244(r3)
	lwz r3, gp(r13)
	stw r4, 0x110(r3)
	lwz r3, gp(r13)
	stw r0, 0x108(r3)
	bl swInit
	li r3, 0x0
	li r4, 0x0
	bl swByteSet
	cmpwi r31, 0x0
	bne @71
	lwz r4, wp(r13)
	lis r3, evt_memcard_save@ha
	lwz r6, gp(r13)
	addi r3, r3, evt_memcard_save@l
	lwz r0, 0x20(r4)
	li r4, 0x0
	li r5, 0x0
	stw r0, 0x11d0(r6)
	li r6, 0x0
	bl evtEntryType
	lwz r4, wp(r13)
	li r0, 0x17
	stw r3, 0x3c(r4)
	lwz r3, wp(r13)
	lwz r3, 0x3c(r3)
	stw r0, 0x9c(r3)
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@71:
	addi r4, r30, 0x2c0
	addi r5, r30, 0x2c8
	li r3, 0x3
	bl seqSetSeq
	b @19
	@34:
	lwz r3, 0x3c(r6)
	lwz r3, 0x15c(r3)
	bl evtCheckID
	cmpwi r3, 0x0
	bne @19
	addi r4, r30, 0x2c0
	addi r5, r30, 0x2c8
	li r3, 0x3
	bl seqSetSeq
	b @19
	@36:
	addi r3, r30, 0x374
	bl msgSearch
	lwz r4, wp(r13)
	rlwinm. r0, r27, 0, 19, 19
	stw r3, 0x38(r4)
	lwz r3, wp(r13)
	lwz r31, 0x20(r3)
	beq @72
	mulli r0, r31, 0x1c
	addi r4, r29, 0x13c
	add r4, r4, r0
	lbz r0, 0x18(r4)
	stw r0, 0x20(r3)
	b @73
	@72:
	rlwinm. r0, r27, 0, 18, 18
	beq @74
	mulli r0, r31, 0x1c
	addi r4, r29, 0x13c
	add r4, r4, r0
	lbz r0, 0x19(r4)
	stw r0, 0x20(r3)
	b @73
	@74:
	rlwinm. r0, r27, 0, 17, 17
	beq @75
	mulli r0, r31, 0x1c
	addi r4, r29, 0x13c
	add r4, r4, r0
	lbz r0, 0x1a(r4)
	stw r0, 0x20(r3)
	b @73
	@75:
	rlwinm. r0, r27, 0, 16, 16
	beq @76
	mulli r0, r31, 0x1c
	addi r4, r29, 0x13c
	add r4, r4, r0
	lbz r0, 0x1b(r4)
	stw r0, 0x20(r3)
	b @73
	@76:
	rlwinm. r0, r28, 0, 23, 23
	beq @77
	cmpwi r31, 0x4
	bge @78
	bl cardGetFilePtr
	lwz r4, wp(r13)
	lwz r0, 0x20(r4)
	slwi r4, r0, 14
	addi r0, r4, 0x2000
	lhzx r3, r3, r0
	rlwinm. r0, r3, 0, 30, 30
	bne @79
	clrlwi. r0, r3, 31
	bne @80
	@79:
	li r3, 0x12
	bl psndSFXOn
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @73
	@80:
	li r3, 0x13
	bl psndSFXOn
	b @73
	@78:
	li r4, 0x4
	li r0, 0x1
	stw r4, 0x20(r3)
	li r3, 0x13
	lwz r4, wp(r13)
	stw r0, 0x18(r4)
	bl psndSFXOn
	b @73
	@77:
	rlwinm. r0, r28, 0, 22, 22
	beq @73
	li r4, 0x4
	li r0, 0x1
	stw r4, 0x20(r3)
	li r3, 0x13
	lwz r4, wp(r13)
	stw r0, 0x18(r4)
	bl psndSFXOn
	@73:
	lwz r3, wp(r13)
	lwz r0, 0x20(r3)
	cmpw r31, r0
	beq @81
	cmpwi r0, 0x4
	bge @81
	li r3, 0x9
	bl psndSFXOn
	@81:
	lwz r5, wp(r13)
	addi r4, r29, 0x13c
	lwz r0, 0x20(r5)
	mulli r0, r0, 0x1c
	add r3, r4, r0
	lfsx f1, r4, r0
	lfs f0, 0x8(r3)
	fadds f0, f1, f0
	stfs f0, 0x10(r5)
	lwz r5, wp(r13)
	lwz r0, 0x20(r5)
	mulli r0, r0, 0x1c
	add r3, r4, r0
	lfs f1, 0x4(r3)
	lfs f0, 0xc(r3)
	fadds f0, f1, f0
	stfs f0, 0x14(r5)
	b @19
	@32:
	lhz r0, 0x0(r6)
	lis r3, evt_memcard_delete@ha
	addi r3, r3, evt_memcard_delete@l
	li r4, 0x0
	ori r0, r0, 0x40
	li r5, 0x0
	sth r0, 0x0(r6)
	li r6, 0x0
	bl evtEntryType
	lwz r4, wp(r13)
	stw r3, 0x3c(r4)
	lwz r3, wp(r13)
	lwz r0, 0x20(r3)
	lwz r3, 0x3c(r3)
	stw r0, 0x9c(r3)
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@38:
	lwz r3, 0x3c(r6)
	lwz r3, 0x15c(r3)
	bl evtCheckID
	cmpwi r3, 0x0
	bne @19
	lis r4, 0xfaa3
	li r3, 0x0
	subi r4, r4, 0x4a80
	bl evtGetValue
	cmpwi r3, 0x0
	bne @82
	lwz r5, wp(r13)
	li r4, 0x4
	li r0, 0x1
	lhz r3, 0x0(r5)
	rlwinm r3, r3, 0, 26, 24
	sth r3, 0x0(r5)
	lwz r3, wp(r13)
	stw r4, 0x20(r3)
	lwz r3, wp(r13)
	stw r0, 0x18(r3)
	b @19
	@82:
	lwz r4, wp(r13)
	li r0, 0x1
	lhz r3, 0x0(r4)
	ori r3, r3, 0x80
	sth r3, 0x0(r4)
	stw r0, 0x4(r26)
	b @83
	@37:
	addi r3, r30, 0x390
	bl msgSearch
	lwz r4, wp(r13)
	rlwinm. r0, r27, 0, 19, 19
	stw r3, 0x38(r4)
	lwz r3, wp(r13)
	lwz r31, 0x20(r3)
	beq @84
	mulli r0, r31, 0x1c
	addi r4, r29, 0x13c
	add r4, r4, r0
	lbz r0, 0x18(r4)
	stw r0, 0x20(r3)
	b @85
	@84:
	rlwinm. r0, r27, 0, 18, 18
	beq @86
	mulli r0, r31, 0x1c
	addi r4, r29, 0x13c
	add r4, r4, r0
	lbz r0, 0x19(r4)
	stw r0, 0x20(r3)
	b @85
	@86:
	rlwinm. r0, r27, 0, 17, 17
	beq @87
	mulli r0, r31, 0x1c
	addi r4, r29, 0x13c
	add r4, r4, r0
	lbz r0, 0x1a(r4)
	stw r0, 0x20(r3)
	b @85
	@87:
	rlwinm. r0, r27, 0, 16, 16
	beq @88
	mulli r0, r31, 0x1c
	addi r4, r29, 0x13c
	add r4, r4, r0
	lbz r0, 0x1b(r4)
	stw r0, 0x20(r3)
	b @85
	@88:
	rlwinm. r0, r28, 0, 23, 23
	beq @89
	cmpwi r31, 0x4
	bge @90
	bl cardGetFilePtr
	lwz r5, wp(r13)
	lwz r0, 0x20(r5)
	slwi r4, r0, 14
	addi r0, r4, 0x2000
	lhzx r3, r3, r0
	rlwinm. r0, r3, 0, 30, 30
	bne @85
	clrlwi. r0, r3, 31
	bne @85
	li r0, 0x33
	li r3, 0x12
	stw r0, 0x18(r5)
	lwz r4, wp(r13)
	lwz r0, 0x20(r4)
	stw r0, 0x30(r4)
	lwz r5, wp(r13)
	lwz r4, 0x30(r5)
	addi r4, r4, 0x1
	slwi r0, r4, 30
	srwi r4, r4, 31
	subf r0, r4, r0
	rotlwi r0, r0, 2
	add r0, r0, r4
	stw r0, 0x34(r5)
	lwz r4, wp(r13)
	lwz r0, 0x34(r4)
	stw r0, 0x20(r4)
	bl psndSFXOn
	b @85
	@90:
	li r4, 0x5
	li r0, 0x1
	stw r4, 0x20(r3)
	li r3, 0x13
	lwz r4, wp(r13)
	stw r0, 0x18(r4)
	bl psndSFXOn
	b @85
	@89:
	rlwinm. r0, r28, 0, 22, 22
	beq @85
	li r4, 0x5
	li r0, 0x1
	stw r4, 0x20(r3)
	li r3, 0x13
	lwz r4, wp(r13)
	stw r0, 0x18(r4)
	bl psndSFXOn
	@85:
	lwz r3, wp(r13)
	lwz r0, 0x20(r3)
	cmpw r31, r0
	beq @91
	cmpwi r0, 0x4
	bge @91
	li r3, 0x9
	bl psndSFXOn
	@91:
	lwz r5, wp(r13)
	addi r4, r29, 0x13c
	lwz r0, 0x20(r5)
	mulli r0, r0, 0x1c
	add r3, r4, r0
	lfsx f1, r4, r0
	lfs f0, 0x8(r3)
	fadds f0, f1, f0
	stfs f0, 0x10(r5)
	lwz r5, wp(r13)
	lwz r0, 0x20(r5)
	mulli r0, r0, 0x1c
	add r3, r4, r0
	lfs f1, 0x4(r3)
	lfs f0, 0xc(r3)
	fadds f0, f1, f0
	stfs f0, 0x14(r5)
	b @19
	@30:
	addi r3, r30, 0x3ac
	bl msgSearch
	lwz r4, wp(r13)
	rlwinm. r0, r27, 0, 19, 19
	stw r3, 0x38(r4)
	lwz r5, wp(r13)
	lwz r31, 0x20(r5)
	beq @92
	addi r4, r29, 0x200
	@93:
	lwz r5, wp(r13)
	lwz r0, 0x20(r5)
	mulli r3, r0, 0x1c
	addi r0, r3, 0x18
	lbzx r0, r4, r0
	stw r0, 0x20(r5)
	lwz r5, wp(r13)
	lwz r3, 0x20(r5)
	lwz r0, 0x30(r5)
	cmpw r3, r0
	beq @93
	b @94
	@92:
	rlwinm. r0, r27, 0, 18, 18
	beq @95
	addi r4, r29, 0x200
	@96:
	lwz r5, wp(r13)
	lwz r0, 0x20(r5)
	mulli r3, r0, 0x1c
	addi r0, r3, 0x19
	lbzx r0, r4, r0
	stw r0, 0x20(r5)
	lwz r5, wp(r13)
	lwz r3, 0x20(r5)
	lwz r0, 0x30(r5)
	cmpw r3, r0
	beq @96
	b @94
	@95:
	rlwinm. r0, r27, 0, 17, 17
	beq @97
	addi r4, r29, 0x200
	@98:
	lwz r5, wp(r13)
	lwz r0, 0x20(r5)
	mulli r3, r0, 0x1c
	addi r0, r3, 0x1a
	lbzx r0, r4, r0
	stw r0, 0x20(r5)
	lwz r5, wp(r13)
	lwz r3, 0x20(r5)
	lwz r0, 0x30(r5)
	cmpw r3, r0
	beq @98
	b @94
	@97:
	rlwinm. r0, r27, 0, 16, 16
	beq @99
	addi r4, r29, 0x200
	@100:
	lwz r5, wp(r13)
	lwz r0, 0x20(r5)
	mulli r3, r0, 0x1c
	addi r0, r3, 0x1b
	lbzx r0, r4, r0
	stw r0, 0x20(r5)
	lwz r5, wp(r13)
	lwz r3, 0x20(r5)
	lwz r0, 0x30(r5)
	cmpw r3, r0
	beq @100
	b @94
	@99:
	rlwinm. r0, r28, 0, 23, 23
	beq @101
	li r0, 0x34
	li r3, 0x12
	stw r0, 0x18(r5)
	lwz r4, wp(r13)
	lwz r0, 0x20(r4)
	stw r0, 0x34(r4)
	bl psndSFXOn
	b @94
	@101:
	rlwinm. r0, r28, 0, 22, 22
	beq @94
	lwz r4, 0x30(r5)
	li r0, 0x32
	li r3, 0x13
	stw r4, 0x20(r5)
	lwz r4, wp(r13)
	stw r0, 0x18(r4)
	bl psndSFXOn
	@94:
	lwz r3, wp(r13)
	lwz r0, 0x20(r3)
	cmpw r31, r0
	beq @102
	cmpwi r0, 0x4
	bge @102
	li r3, 0x9
	bl psndSFXOn
	@102:
	lwz r3, wp(r13)
	addi r4, r29, 0x13c
	lwz r0, 0x20(r3)
	stw r0, 0x34(r3)
	lwz r5, wp(r13)
	lwz r0, 0x20(r5)
	mulli r0, r0, 0x1c
	add r3, r4, r0
	lfsx f1, r4, r0
	lfs f0, 0x8(r3)
	fadds f0, f1, f0
	stfs f0, 0x10(r5)
	lwz r5, wp(r13)
	lwz r0, 0x20(r5)
	mulli r0, r0, 0x1c
	add r3, r4, r0
	lfs f1, 0x4(r3)
	lfs f0, 0xc(r3)
	fadds f0, f1, f0
	stfs f0, 0x14(r5)
	b @19
	@42:
	lhz r0, 0x0(r6)
	lis r3, evt_memcard_copy@ha
	addi r3, r3, evt_memcard_copy@l
	li r4, 0x0
	ori r0, r0, 0x40
	li r5, 0x0
	sth r0, 0x0(r6)
	li r6, 0x0
	bl evtEntryType
	lwz r4, wp(r13)
	stw r3, 0x3c(r4)
	lwz r3, wp(r13)
	lwz r0, 0x30(r3)
	lwz r3, 0x3c(r3)
	stw r0, 0x9c(r3)
	lwz r3, wp(r13)
	lwz r0, 0x34(r3)
	lwz r3, 0x3c(r3)
	stw r0, 0xa0(r3)
	lwz r4, wp(r13)
	lwz r3, 0x18(r4)
	addi r0, r3, 0x1
	stw r0, 0x18(r4)
	b @19
	@41:
	lwz r3, 0x3c(r6)
	lwz r3, 0x15c(r3)
	bl evtCheckID
	cmpwi r3, 0x0
	bne @19
	lis r4, 0xfaa3
	li r3, 0x0
	subi r4, r4, 0x4a80
	bl evtGetValue
	cmpwi r3, 0x0
	bne @103
	lwz r5, wp(r13)
	li r4, 0x5
	li r0, 0x1
	lhz r3, 0x0(r5)
	rlwinm r3, r3, 0, 26, 24
	sth r3, 0x0(r5)
	lwz r3, wp(r13)
	stw r4, 0x20(r3)
	lwz r3, wp(r13)
	stw r0, 0x18(r3)
	b @19
	@103:
	lwz r4, wp(r13)
	li r0, 0x1
	lhz r3, 0x0(r4)
	ori r3, r3, 0x80
	sth r3, 0x0(r4)
	stw r0, 0x4(r26)
	b @83
	@39:
	lhz r3, 0x0(r6)
	rlwinm. r0, r27, 0, 19, 19
	ori r0, r3, 0x1
	sth r0, 0x0(r6)
	lwz r4, wp(r13)
	lwz r25, 0x24(r4)
	beq @104
	subi r0, r25, 0x1
	li r3, 0x5
	stw r0, 0x24(r4)
	bl psndSFXOn
	b @105
	@104:
	rlwinm. r0, r27, 0, 18, 18
	beq @106
	addi r0, r25, 0x1
	li r3, 0x5
	stw r0, 0x24(r4)
	bl psndSFXOn
	b @105
	@106:
	rlwinm. r0, r28, 0, 23, 23
	beq @107
	cmpwi r25, 0x1
	beq @108
	bge @109
	cmpwi r25, 0x0
	bge @110
	b @111
	@109:
	cmpwi r25, 0x3
	bge @111
	b @112
	@110:
	li r3, 0x0
	bl OSSetSoundMode
	lwz r3, gp(r13)
	li r0, 0x0
	stw r0, 0x1274(r3)
	b @111
	@108:
	li r3, 0x1
	bl OSSetSoundMode
	lwz r3, gp(r13)
	li r0, 0x0
	stw r0, 0x1274(r3)
	b @111
	@112:
	li r3, 0x1
	bl OSSetSoundMode
	lwz r3, gp(r13)
	li r0, 0x1
	stw r0, 0x1274(r3)
	@111:
	bl OSGetSoundMode
	cmplwi r3, 0x0
	bne @113
	li r3, 0x0
	bl SoundSetOutputMode
	b @114
	@113:
	li r3, 0x1
	bl SoundSetOutputMode
	@114:
	li r3, 0x12
	bl psndSFXOn
	li r3, 0xa0
	li r4, 0x0
	bl psndBGMOn
	li r3, 0x200
	bl psndENVOff
	lwz r4, wp(r13)
	li r0, 0x1
	lwz r3, 0x24(r4)
	stw r3, 0x40(r4)
	lwz r4, wp(r13)
	lhz r3, 0x0(r4)
	rlwinm r3, r3, 0, 16, 30
	sth r3, 0x0(r4)
	lwz r3, wp(r13)
	stw r0, 0x18(r3)
	b @19
	@107:
	rlwinm. r0, r28, 0, 22, 22
	beq @105
	li r3, 0x13
	bl psndSFXOn
	li r3, 0xa0
	li r4, 0x0
	bl psndBGMOn
	li r3, 0x200
	bl psndENVOff
	lwz r3, wp(r13)
	lwz r0, 0x40(r3)
	stw r0, 0x24(r3)
	bl OSGetSoundMode
	cmplwi r3, 0x0
	bne @115
	li r3, 0x0
	bl SoundSetOutputMode
	b @116
	@115:
	li r3, 0x1
	bl SoundSetOutputMode
	@116:
	lwz r4, wp(r13)
	li r0, 0x1
	lhz r3, 0x0(r4)
	rlwinm r3, r3, 0, 16, 30
	sth r3, 0x0(r4)
	lwz r3, wp(r13)
	stw r0, 0x18(r3)
	b @19
	@105:
	lwz r3, wp(r13)
	lwz r0, 0x24(r3)
	cmpwi r0, 0x3
	blt @117
	li r0, 0x0
	stw r0, 0x24(r3)
	@117:
	lwz r3, wp(r13)
	lwz r0, 0x24(r3)
	cmpwi r0, 0x0
	bge @118
	li r0, 0x2
	stw r0, 0x24(r3)
	@118:
	lwz r3, wp(r13)
	lwz r0, 0x24(r3)
	cmpw r0, r25
	beq @119
	cmpwi r0, 0x1
	beq @120
	bge @121
	cmpwi r0, 0x0
	bge @122
	b @123
	@121:
	cmpwi r0, 0x3
	bge @123
	b @124
	@122:
	li r3, 0x0
	bl SoundSetOutputMode
	b @123
	@120:
	li r3, 0x1
	bl SoundSetOutputMode
	b @123
	@124:
	li r3, 0x2
	bl SoundSetOutputMode
	@123:
	li r3, 0x110
	li r4, 0x75
	bl psndENVOn
	@119:
	lfs f0, float_neg74_8041be74(r2)
	lis r0, 0x4330
	lwz r3, wp(r13)
	stw r0, 0x20(r1)
	lfd f1, 0x358(r30)
	stfs f0, 0x10(r3)
	lfs f2, float_50_8041be6c(r2)
	lwz r3, wp(r13)
	lfs f3, float_4_8041be78(r2)
	lwz r0, 0x24(r3)
	xoris r0, r0, 0x8000
	stw r0, 0x24(r1)
	lfd f0, 0x20(r1)
	fsubs f0, f0, f1
	fnmsubs f0, f2, f0, f2
	fadds f0, f3, f0
	stfs f0, 0x14(r3)
	b @19
	@43:
	lhz r3, 0x0(r6)
	rlwinm. r0, r27, 0, 19, 19
	ori r0, r3, 0x1
	sth r0, 0x0(r6)
	beq @125
	lwz r5, wp(r13)
	li r3, 0x5
	lwz r4, 0x28(r5)
	subi r0, r4, 0x1
	stw r0, 0x28(r5)
	bl psndSFXOn
	b @126
	@125:
	rlwinm. r0, r27, 0, 18, 18
	beq @127
	lwz r5, wp(r13)
	li r3, 0x5
	lwz r4, 0x28(r5)
	addi r0, r4, 0x1
	stw r0, 0x28(r5)
	bl psndSFXOn
	b @126
	@127:
	rlwinm. r0, r28, 0, 23, 23
	beq @128
	lwz r5, wp(r13)
	li r3, 0x12
	lwz r4, gp(r13)
	lwz r0, 0x28(r5)
	cntlzw r0, r0
	srwi r0, r0, 5
	stw r0, 0x1294(r4)
	bl psndSFXOn
	lwz r4, wp(r13)
	li r0, 0x1
	lwz r3, 0x28(r4)
	stw r3, 0x44(r4)
	lwz r4, wp(r13)
	lhz r3, 0x0(r4)
	rlwinm r3, r3, 0, 16, 30
	sth r3, 0x0(r4)
	lwz r3, wp(r13)
	stw r0, 0x18(r3)
	lwz r3, gp(r13)
	lwz r0, 0x1294(r3)
	cmpwi r0, 0x0
	beq @126
	la r3, evt_shake(r13)
	li r4, 0x0
	li r5, 0x0
	li r6, 0x0
	bl evtEntryType
	b @126
	@128:
	rlwinm. r0, r28, 0, 22, 22
	beq @126
	li r3, 0x13
	bl psndSFXOn
	lwz r4, wp(r13)
	li r0, 0x1
	lwz r3, 0x44(r4)
	stw r3, 0x28(r4)
	lwz r4, wp(r13)
	lhz r3, 0x0(r4)
	rlwinm r3, r3, 0, 16, 30
	sth r3, 0x0(r4)
	lwz r3, wp(r13)
	stw r0, 0x18(r3)
	@126:
	lwz r3, wp(r13)
	lwz r0, 0x28(r3)
	cmpwi r0, 0x2
	blt @129
	li r0, 0x0
	stw r0, 0x28(r3)
	@129:
	lwz r3, wp(r13)
	lwz r0, 0x28(r3)
	cmpwi r0, 0x0
	bge @130
	li r0, 0x1
	stw r0, 0x28(r3)
	@130:
	lfs f0, float_neg74_8041be74(r2)
	lis r0, 0x4330
	lwz r3, wp(r13)
	stw r0, 0x20(r1)
	lfd f2, 0x358(r30)
	stfs f0, 0x10(r3)
	lfs f3, float_50_8041be6c(r2)
	lwz r3, wp(r13)
	lfs f0, float_30_8041be3c(r2)
	lwz r0, 0x28(r3)
	lfs f4, float_4_8041be78(r2)
	xoris r0, r0, 0x8000
	stw r0, 0x24(r1)
	lfd f1, 0x20(r1)
	fsubs f1, f1, f2
	fnmsubs f0, f3, f1, f0
	fadds f0, f4, f0
	stfs f0, 0x14(r3)
	@19:
	lwz r3, wp(r13)
	lis r0, 0x4330
	lfs f4, float_0p25_8041be7c(r2)
	lfs f0, 0x10(r3)
	lfs f3, 0x8(r3)
	stw r0, 0x20(r1)
	fsubs f1, f0, f3
	lfd f2, 0x350(r30)
	lfs f0, float_0p125_8041be80(r2)
	fmadds f1, f1, f4, f3
	stfs f1, 0x8(r3)
	lwz r3, wp(r13)
	lfs f1, 0x14(r3)
	lfs f3, 0xc(r3)
	fsubs f1, f1, f3
	fmadds f1, f1, f4, f3
	stfs f1, 0xc(r3)
	lwz r3, gp(r13)
	lwz r0, 0x1c(r3)
	stw r0, 0x24(r1)
	lfd f1, 0x20(r1)
	fsubs f1, f1, f2
	fmuls f1, f1, f0
	bl sin
	frsp f2, f1
	lfs f0, float_2_8041be70(r2)
	lis r3, loadDraw@ha
	lwz r7, wp(r13)
	addi r5, r3, loadDraw@l
	lfs f1, float_1000_8041be84(r2)
	fmuls f0, f0, f2
	lfs f2, 0x8(r7)
	li r3, 0x4
	li r4, 0x0
	li r6, 0x0
	fabs f0, f0
	fadds f0, f2, f0
	stfs f0, 0x8(r7)
	bl dispEntry
	@83:
	lmw r24, 0x30(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void seq_loadMain(SequenceWork* seq) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	lwz r0, 0x4(r3)
	cmpwi r0, 0x2
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r0, 0x4
	beq @6
	bge @5
	b @7
	@3:
	bl getMarioStDvdRoot
	lis r4, str_802EDA34@ha
	mr r6, r3
	addi r5, r4, str_802EDA34@l
	li r3, 0x4
	li r4, 0x0
	crclr 6
	bl fileAsyncf
	cmplwi r3, 0x0
	beq @8
	bl getMarioStDvdRoot
	lis r4, str_802EDA34@ha
	mr r5, r3
	addi r4, r4, str_802EDA34@l
	li r3, 0x4
	crclr 6
	bl fileAllocf
	lwz r4, wp(r13)
	li r0, 0x1
	stw r3, 0x4(r4)
	b @9
	@8:
	li r0, 0x0
	@9:
	cmpwi r0, 0x0
	beq @5
	lwz r3, 0x4(r31)
	addi r0, r3, 0x1
	stw r0, 0x4(r31)
	b @5
	@4:
	lis r3, evt_memcard_check@ha
	li r4, 0x0
	addi r3, r3, evt_memcard_check@l
	li r5, 0x0
	li r6, 0x0
	bl evtEntryType
	lwz r4, wp(r13)
	stw r3, 0x3c(r4)
	lwz r4, wp(r13)
	lhz r3, 0x0(r4)
	rlwinm. r0, r3, 0, 24, 24
	beq @10
	rlwinm r3, r3, 0, 25, 23
	li r0, 0x1
	sth r3, 0x0(r4)
	lwz r3, wp(r13)
	lwz r3, 0x3c(r3)
	stw r0, 0xc4(r3)
	lwz r3, wp(r13)
	lwz r0, 0x48(r3)
	lwz r3, 0x3c(r3)
	stw r0, 0x178(r3)
	@10:
	lwz r3, 0x4(r31)
	addi r0, r3, 0x1
	stw r0, 0x4(r31)
	b @5
	@1:
	lwz r3, wp(r13)
	lwz r3, 0x3c(r3)
	lwz r3, 0x15c(r3)
	bl evtCheckID
	cmpwi r3, 0x0
	bne @5
	lis r4, 0xfaa3
	li r3, 0x0
	subi r4, r4, 0x4a80
	bl evtGetValue
	cmpwi r3, 0x1
	beq @11
	li r3, 0x1
	li r4, 0x0
	li r5, 0x0
	bl seqSetSeq
	b @5
	@11:
	lwz r3, wp(r13)
	li r4, 0x0
	stw r4, 0x3c(r3)
	lwz r3, 0x4(r31)
	addi r0, r3, 0x1
	stw r0, 0x4(r31)
	lwz r3, wp(r13)
	stw r4, 0x18(r3)
	bl cardGetCode
	lwz r4, wp(r13)
	stw r3, 0x1c(r4)
	lwz r3, wp(r13)
	lhz r0, 0x0(r3)
	rlwinm r0, r0, 0, 26, 24
	sth r0, 0x0(r3)
	bl OSGetSoundMode
	cmplwi r3, 0x0
	bne @12
	li r3, 0x0
	bl SoundSetOutputMode
	lwz r3, gp(r13)
	li r0, 0x0
	stw r0, 0x1274(r3)
	lwz r3, wp(r13)
	stw r0, 0x40(r3)
	b @13
	@12:
	li r3, 0x1
	bl SoundSetOutputMode
	lwz r3, gp(r13)
	lwz r0, 0x1274(r3)
	cmpwi r0, 0x0
	bne @14
	lwz r3, wp(r13)
	li r0, 0x1
	stw r0, 0x40(r3)
	b @13
	@14:
	lwz r3, wp(r13)
	li r0, 0x2
	stw r0, 0x40(r3)
	@13:
	lwz r5, gp(r13)
	lis r3, win_dt@ha
	lwz r4, wp(r13)
	addi r3, r3, win_dt@l
	lwz r0, 0x1294(r5)
	cntlzw r0, r0
	srwi r0, r0, 5
	stw r0, 0x44(r4)
	lwz r4, wp(r13)
	lwz r0, 0x40(r4)
	stw r0, 0x24(r4)
	lwz r4, wp(r13)
	lwz r0, 0x44(r4)
	stw r0, 0x28(r4)
	lwz r5, gp(r13)
	lwz r4, wp(r13)
	lwz r0, 0x11b8(r5)
	stw r0, 0x20(r4)
	lwz r4, wp(r13)
	lwz r0, 0x20(r4)
	mulli r0, r0, 0x1c
	lfsx f0, r3, r0
	stfs f0, 0x8(r4)
	lwz r4, wp(r13)
	lwz r0, 0x20(r4)
	mulli r0, r0, 0x1c
	add r3, r3, r0
	lfs f0, 0x4(r3)
	stfs f0, 0xc(r4)
	b @5
	@7:
	lwz r0, dat_8041bd68(r2)
	addi r5, r1, 0x8
	li r3, 0x1c
	li r4, 0x0
	stw r0, 0x8(r1)
	bl fadeEntry
	lwz r3, 0x4(r31)
	addi r0, r3, 0x1
	stw r0, 0x4(r31)
	b @5
	@6:
	bl loadMain
	@5:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void seq_loadExit(SequenceWork* seq) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, wp(r13)
	lwz r3, 0x4(r3)
	cmplwi r3, 0x0
	beq @1
	bl fileFree
	@1:
	lwz r3, wp(r13)
	li r0, 0x0
	stw r0, 0x4(r3)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void seq_loadInit(SequenceWork* seq) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x0
	li r5, 0x4c
	stw r0, 0x14(r1)
	lwz r3, wp(r13)
	bl memset
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 unk_800f2398(EventEntry* evt, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	li r3, 0x4
	bl fadeReset
	lwz r0, 0x178(r31)
	li r3, 0x2
	lwz r4, wp(r13)
	stw r0, 0x48(r4)
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}
// clang-format on
#endif
