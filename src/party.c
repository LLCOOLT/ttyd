#include "party.h"
extern const char str_802CCD60[];
extern const char str_802CCD6C[];
extern const char str_802CCD7C[];
extern const char str_802CCD8C[];
extern const char str_802CCD9C[];
extern const char str_802CCDAC[];
extern const char str_802CCDBC[];
extern const char str_802CCEEC[];
extern const char str_802CCF08[];
extern const char str_802CCF10[];
extern const char str_802CCF1C[];
extern const char str_802CCF24[];
extern const char str_802CCF2C[];
extern const char str_802CCF38[];
extern const char str_802CCF40[];
#include "driver/animdrv.h"
#include "mario/mario_pouch.h"
#include "mario/mario_party.h"
#include "mario/mario_cam.h"
#include "memory.h"
#include "system.h"
#include "mario/mariost.h"
#include <string.h>
#ifndef NONMATCHING
#include "mario/mario.h"
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const f32 vec3_802ccd30[3];
__declspec(section ".rodata") extern const f32 vec3_802ccd3c[3];
__declspec(section ".rodata") extern const f32 vec3_802ccd48[3];
__declspec(section ".rodata") extern const f32 vec3_802ccd54[3];
__declspec(section ".rodata") extern const f32 vec3_802ccdcc[3];
__declspec(section ".rodata") extern const f32 vec3_802ccdd8[3];
__declspec(section ".rodata") extern const f32 vec3_802ccde4[3];
__declspec(section ".rodata") extern const f32 vec3_802ccdf0[3];
__declspec(section ".rodata") extern const f32 vec3_802ccdfc[3];
__declspec(section ".rodata") extern const f32 vec3_802cce08[3];
__declspec(section ".rodata") extern const f32 vec3_802cce14[3];
__declspec(section ".rodata") extern const f32 vec3_802cce20[3];
__declspec(section ".rodata") extern const f32 vec3_802cce2c[3];
__declspec(section ".rodata") extern const f32 vec3_802cce38[3];
__declspec(section ".rodata") extern const f32 vec3_802cce44[3];
__declspec(section ".rodata") extern const f32 vec3_802cce50[3];
__declspec(section ".rodata") extern const f32 vec3_802cce5c[3];
__declspec(section ".rodata") extern const f32 vec3_802cce68[3];
__declspec(section ".rodata") extern const f32 vec3_802cce74[3];
__declspec(section ".rodata") extern const f32 vec3_802cce80[3];
__declspec(section ".rodata") extern const f32 vec3_802cce8c[3];
__declspec(section ".rodata") extern const f32 vec3_802cce98[3];
__declspec(section ".rodata") extern const f32 vec3_802ccea4[3];
__declspec(section ".rodata") extern const f32 vec3_802cceb0[3];
__declspec(section ".rodata") extern const f32 vec3_802ccebc[3];
__declspec(section ".rodata") extern const f32 vec3_802ccec8[3];
__declspec(section ".rodata") extern const f32 vec3_802cced4[3];
__declspec(section ".rodata") extern const f32 vec3_802ccee0[3];
__declspec(section ".rodata") extern const f64 double_to_int_mask_802ccef8;
__declspec(section ".rodata") extern const f64 double_to_int_802ccf00;
__declspec(section ".sdata2") extern const f32 float_neg6p8_8041b0d8;
__declspec(section ".sdata2") extern const f32 float_6p8_8041b0dc;
__declspec(section ".sdata2") extern const f32 float_1p2_8041b0e0;
__declspec(section ".sdata2") extern const f32 float_2_8041b0e4;
__declspec(section ".sdata2") extern const f32 float_1_8041b0e8;
__declspec(section ".sdata2") extern const f32 float_neg1_8041b0ec;
__declspec(section ".sdata2") extern const f32 float_90_8041b0f0;
__declspec(section ".sdata2") extern const f32 float_270_8041b0f4;
__declspec(section ".sdata2") extern const f32 float_deg2rad_8041b0f8;
__declspec(section ".sdata2") extern const f32 float_180_8041b0fc;
__declspec(section ".sdata2") extern const f32 float_0_8041b100;
__declspec(section ".sdata2") extern const f32 float_3_8041b104;
__declspec(section ".sdata2") extern const f32 float_3p5_8041b108;
__declspec(section ".sdata2") extern const f32 float_4_8041b10c;
__declspec(section ".sdata2") extern const f32 float_0p75_8041b110;
__declspec(section ".sdata2") extern const f32 float_5000_8041b114;
__declspec(section ".sdata2") extern const f32 float_10000_8041b118;
__declspec(section ".sdata2") extern const f32 float_13p333_8041b11c;
__declspec(section ".sdata2") extern const f32 float_1000_8041b120;
__declspec(section ".sdata2") extern const f32 float_10_8041b124;
__declspec(section ".sdata2") extern const f32 float_290_8041b128;
__declspec(section ".sdata2") extern const f32 float_250_8041b12c;
__declspec(section ".sdata2") extern const f32 float_190_8041b130;
__declspec(section ".sdata2") extern const f32 float_350_8041b134;
__declspec(section ".sdata2") extern const f32 float_170_8041b138;
__declspec(section ".sdata2") extern const f32 float_0p125_8041b13c;
__declspec(section ".sdata2") extern const f32 float_20_8041b140;
__declspec(section ".sdata2") extern const f32 float_neg40_8041b144;
__declspec(section ".sdata2") extern const f32 float_neg30_8041b148;
__declspec(section ".sdata2") extern const f32 float_220_8041b14c;
__declspec(section ".sdata2") extern const f32 float_210_8041b150;
__declspec(section ".sdata2") extern const f32 float_15_8041b154;
__declspec(section ".sdata2") extern const f32 float_neg100_8041b158;
__declspec(section ".sdata2") extern const f32 float_240_8041b15c;
__declspec(section ".sdata2") extern const f32 float_neg6_8041b160;
__declspec(section ".sdata2") extern const f32 float_neg2000_8041b164;
__declspec(section ".sdata2") extern const f32 float_200_8041b168;
__declspec(section ".sdata2") extern const f32 float_1p6_8041b16c;
__declspec(section ".sdata2") extern const f32 float_0p5_8041b170;
__declspec(section ".sdata2") extern const f32 float_0p4_8041b174;
__declspec(section ".sdata2") extern const f32 float_30_8041b178;
__declspec(section ".sdata2") extern const f32 float_16_8041b17c;
__declspec(section ".sdata2") extern const f32 float_neg1p6_8041b180;
__declspec(section ".sdata2") extern const f32 float_0p0625_8041b184;
__declspec(section ".sdata2") extern const f32 float_3p1416_8041b188;
__declspec(section ".sdata2") extern const f32 float_12_8041b18c;
__declspec(section ".sdata2") extern const f32 float_22_8041b190;
__declspec(section ".sdata2") extern const f32 float_40_8041b194;
__declspec(section ".sdata2") extern const f32 float_0p05_8041b198;
__declspec(section ".sdata2") extern const f32 float_neg0p2_8041b19c;
__declspec(section ".sdata2") extern const f32 float_neg4_8041b1a0;
__declspec(section ".sdata2") extern const f32 float_1p5_8041b1a4;
__declspec(section ".sdata2") extern const f32 float_neg3_8041b1a8;
__declspec(section ".sdata2") extern const f32 float_neg1p5_8041b1ac;
__declspec(section ".sdata2") extern const f32 float_26_8041b1b0;
__declspec(section ".sdata2") extern const f32 float_neg26_8041b1b4;
__declspec(section ".sdata2") extern const f32 float_50_8041b1b8;
__declspec(section ".sdata2") extern const f32 float_18p5_8041b1bc;
#endif

//.data
typedef void (*PartyFunc)(PartyEntry* party);

typedef struct PartyData {
    char* name;            // 0x0
    PartyFunc init_func;   // 0x4
    PartyFunc move_func;   // 0x8
    PartyFunc use_func;    // 0xC
    PartyFunc post_func;   // 0x10
    PartyFunc bye_func;    // 0x14
    PartyFunc unk_6_func;  // 0x18
    PartyFunc unk_7_func;  // 0x1C
    PartyFunc unk_8_func;  // 0x20
    PartyFunc exit_func;   // 0x24
} PartyData;

extern PartyData partyDataTbl[];

extern char* yoshigroup[7];

extern char* partyPoseTbl[20][15];
extern char* partyDotPoseTbl[8][15];
extern char* yoshiDotPoseTbl[7][15];

/*
    000b95ec 000020 800bebcc  4 partyGetPtr 	party.o
    000b95c8 000024 800beba8  4 anotherPartyGetPtr 	party.o
    000b94a8 000120 800bea88  4 partyPaperOn 	party.o
    000b942c 00007c 800bea0c  4 partyPaperOff 	party.o
    000b9404 000028 800be9e4  4 partyPaperLightOff 	party.o
    UNUSED   000028 ........ partyPaperLightOn party.o
    UNUSED   000078 ........ setAnimPoseMaterialFlag party.o
    UNUSED   000040 ........ partyPaperRelease party.o
    000b92a0 000164 800be880  4 partyChgPoseId 	party.o
    000b9224 00007c 800be804  4 partyChgPose 	party.o
    000b91b4 000070 800be794  4 partyChgPaper 	party.o
    UNUSED   000078 ........ partyChgPaperTime party.o
    000b917c 000038 800be75c  4 partyCtrlOff 	party.o
    000b9144 000038 800be724  4 partyCtrlOn 	party.o
    000b8f2c 000218 800be50c  4 partyRun 	party.o
    000b8d1c 000210 800be2fc  4 partyStop 	party.o
    000b8af4 000228 800be0d4  4 partySetForceMove 	party.o
    UNUSED   00006c ........ partyGetNum party.o
    UNUSED   00007c ........ getPartyEntryId party.o
    UNUSED   00005c ........ getExtraPartyEntryId party.o
    UNUSED   000008 ........ partyCheck party.o
    UNUSED   000238 ........ partyHello_debug party.o
    000b88bc 000238 800bde9c  4 partyEntryHello 	party.o
    000b8704 0001b8 800bdce4  4 partyEntry 	party.o
    000b84e8 00021c 800bdac8  4 partyEntryPos 	party.o
    000b82b0 000238 800bd890  4 partyGoodbye 	party.o
    000b815c 000154 800bd73c  4 partyKill 	party.o
    000b8060 0000fc 800bd640  4 partyKill2 	party.o
    UNUSED   000080 ........ partyKill_debug party.o
    UNUSED   0000b8 ........ partyPoseEntry party.o
    000b7fc0 0000a0 800bd5a0  4 yoshiSetColor 	party.o
    000b7f90 000030 800bd570  4 partyGetHeight 	party.o
    000b7c0c 000384 800bd1ec  4 partyEntryMain 	party.o
    000b7894 000378 800bce74  4 partyEntry2 	party.o
    000b739c 0004f8 800bc97c  4 partyEntry2Hello 	party.o
    000b6e0c 000590 800bc3ec  4 partyEntry2Pos 	party.o
    000b6de0 00002c 800bc3c0  4 partyInit 	party.o
    000b6214 000bcc 800bb7f4  4 partyReInit 	party.o
    000b61b8 00005c 800bb798  4 partyUsePost 	party.o
    000b5fa0 000218 800bb580  4 partyChgRunMode 	party.o
    UNUSED   000208 ........ partyChgRunMode2 party.o
    000b5f0c 000094 800bb4ec  4 partyPrevRunMode 	party.o
    000b5e28 0000e4 800bb408  4 partyMain 	party.o
    000b5444 0009e4 800baa24  4 driveParty 	party.o
    000b51d0 000274 800ba7b0  4 partyDoWork 	party.o
    UNUSED   0000c4 ........ partyNormalie party.o
    000b503c 000194 800ba61c  4 partyHello 	party.o
    UNUSED   000158 ........ partyHelloInit party.o
    000b4990 0006ac 800b9f70  4 partyHelloMain 	party.o
    UNUSED   000190 ........ party_force_hello party.o
    000b48c4 0000cc 800b9ea4  4 partyGoodbyeInit 	party.o
    000b4014 0008b0 800b95f4  4 partyGoodbyeMain 	party.o
    UNUSED   000054 ........ party_dokan party.o
    000b3a6c 0005a8 800b904c  4 partyDokanInit 	party.o
    000b350c 000560 800b8aec  4 partyDokanMain 	party.o
    000b34a0 00006c 800b8a80  4 partyDokanEnd 	party.o
    UNUSED   000014 ........ partyGetRideScale party.o
    000b3068 000438 800b8648  4 allPartyRidePlane 	party.o
    000b2c30 000438 800b8210  4 allPartyRideShip 	party.o
    000b27f8 000438 800b7dd8  4 allPartyRideJabara 	party.o
    UNUSED   000094 ........ allPartyJabaraEscape party.o
    UNUSED   000358 ........ allPartyRideShip2 party.o
    000b25d8 000220 800b7bb8  4 getRidePos 	party.o
    UNUSED   00018c ........ rideInit party.o
    000b2174 000464 800b7754  4 allPartyForceRideOn 	party.o
    UNUSED   000434 ........ allPartyRideOn party.o
    000b20e0 000094 800b76c0  4 allPartyRideOff 	party.o
    000b204c 000094 800b762c  4 allPartyRideOff2 	party.o
    UNUSED   000018 ........ partyRideOff party.o
    UNUSED   000018 ........ partyRideOff2 party.o
    000b2010 00003c 800b75f0  4 partyRideChk 	party.o
    UNUSED   0000f4 ........ allPartyRideChk party.o
    UNUSED   000048 ........ party_ride party.o
    UNUSED   00000c ........ partyRideInit party.o
    000b111c 000ef4 800b66fc  4 partyRideMain 	party.o
    UNUSED   00003c ........ chkMapAttr party.o
    000b01c8 000f54 800b57a8  4 partyGetAppearPos 	party.o
    000afc44 000584 800b5224  4 partyGetAppearPos2 	party.o
    000af908 00033c 800b4ee8  4 partyGetAppearPos3 	party.o
    000af3e8 000520 800b49c8  4 partyGetAppearPos4 	party.o
    UNUSED   000214 ........ partyGetFrontPos party.o
    000af07c 00036c 800b465c  4 party_force_ride_yoshi 	party.o
    000aeff4 000088 800b45d4  4 party_ride_yoshi_force_move 	party.o
    UNUSED   000048 ........ party_ride_yoshi party.o
    000ae96c 000688 800b3f4c  4 partyRideYoshiMain 	party.o
    UNUSED   000024 ........ chkWater party.o
    000ae390 0005dc 800b3970  4 party_damage_return 	party.o
    000ae360 000030 800b3940  4 partyInitCamId 	party.o
    UNUSED   000008 ........ partyGetCamId party.o
    000ae358 000008 800b3938  4 partySetCamId 	party.o
    UNUSED   0000dc ........ partyGetDispDir party.o
    000ae018 000340 800b35f8  4 partyMakeDispDir 	party.o
    000adcf8 000320 800b32d8  4 partyPreDisp 	party.o
    000ad980 000378 800b2f60  4 partyDisp 	party.o
    000ad97c 000004 800b2f5c  4 partyKeyOn 	party.o
    000ad978 000004 800b2f58  4 partyKeyOff 	party.o
    UNUSED   000008 ........ partySetContNo party.o
    UNUSED   00000c ........ partyGetContNo party.o
    UNUSED   000038 ........ partyClearCont party.o
    000ad870 000108 800b2e50  4 partyUpdateKeyData 	party.o
    UNUSED   000018 ........ partyShadowOn party.o
    000ad858 000018 800b2e38  4 partyShadowOff 	party.o
    UNUSED   00004c ........ partyChkHerohero party.o
    000ad464 0003f4 800b2a44  4 partySetFamicomMode 	party.o
    000ad464 00dd4c 800b2a44  1 .text 	party.o
*/

PartyEntry* partyPtrTbl[2];
PartyData* party_dp;
s32 partyCtrlNo;

void partyChgRunMode(PartyEntry* party, s32 mode);
void partyChgMot(PartyEntry* party, s32 mot);
s32 partyEntryMain(s32 memberId);
void partyGetAppearPos2(PartyEntry* party, Vec* pos);

#ifdef NONMATCHING
PartyEntry* partyGetPtr(s32 index) {
    if (index >= 0) {
        return partyPtrTbl[index];
    }
    return NULL;
}
#endif
#ifndef NONMATCHING
PartyEntry* partyGetPtr(s32 index);
#endif

#ifdef NONMATCHING
PartyEntry* anotherPartyGetPtr(s32 index) {
    if (index < 0) {
        return NULL;
    }
    return *(partyPtrTbl + ((index + 1) & 1));
}
#endif
#ifndef NONMATCHING
PartyEntry* anotherPartyGetPtr(s32 index);
#endif

#ifdef NONMATCHING
BOOL partyPaperOn(PartyEntry* party, const char* animGroup) {
    BOOL flag;
#endif
#ifndef NONMATCHING
void PSMTX44MultVec(const Mtx44 m, const Vec* src, Vec* dst);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
CameraEntry* camGetPtr(CameraId cameraId);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
s32 marioAnimeId(void);
BOOL marioChkInScreen(s32 x, s32 y);
void *memset(void *dest, int ch, size_t count);
s32 psndSFXOn_3D(const char* name, Vec* position);
f32 revise360(f32 angle);
int strcmp(const char *s1, const char *s2);
void L_partyForceSlitOff(PartyEntry* party);
void L_partyVivianTailStart(PartyEntry* party);
void L_partyVivianTailStop(PartyEntry* party);
BOOL N_marioShipGetDir(void);
BOOL N_vivianDisplayTailCheck(PartyEntry* party);
void allPartyForceRideOn(void);
void animPoseVivianMain(s32 poseId, Vec* pos);
void chuchu_reinit(PartyEntry* party);
double cos(double);
void getRidePos(PartyEntry* party, Vec* pos);
s32 hitGetAttr(struct HitEntry* hit);
void marioGetScreenPos(Vec position, f32* x, f32* y, f32* z);
BOOL marioWaitDamageReturnFall(void);
BOOL marioWaitDamageTogeReturnFall(void);
void partyClearFootmark(void);
void partyClearJumpPara(PartyEntry* party);
s32 partyDokanInit(PartyEntry* party);
s32 partyDokanMain(PartyEntry* party);
void partyForceWalk(PartyEntry* party);
void partyGetAppearPos(PartyEntry* party, Vec* pos);
s32 partyHelloMain(PartyEntry* party);
struct HitEntry* partyHitCheck(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
void partyMakeDispDir(PartyEntry* party);
void partyMove(PartyEntry* party);
void partyMoveNoHosei(PartyEntry* party);
void partyPreDisp(PartyEntry* party);
void partyRideMain(PartyEntry* party);
s32 partyRideYoshiMain(PartyEntry* party);
f32 partyToMovedir(PartyEntry* party, f32 dir);
void party_damage_return(PartyEntry* party);
void party_kemuri(PartyEntry* party);
s32 shadowEntryMode(s32 mode, f32 x, f32 y, f32 z, f32 size);
void shadowFlagOn(s32 id, u32 flag);
void shadowSetCamId(s32 id, s32 camId);
double sin(double);
f32 toMovedir(f32 a);
f32 toMovedir2(f32 a, f32 b);
f32 toMovedirSimple(f32 a);
void unk_800c7c98(PartyEntry* party);
void unk_8014c47c(void);
s32 vivianGetStatus(void);
void vivianShadow(PartyEntry* party);
s32 yoshiGetStatus(void);
extern void* jumptable_803127F0[];
extern void* jumptable_80312774[];
extern void* jumptable_80312720[];
BOOL partyPaperOn(PartyEntry* party, const char* animGroup);
#endif

#ifdef NONMATCHING
    if (party->paperPoseId >= 0) {
        animPaperPoseRelease(party->paperPoseId);
        party->paperPoseId = -1;
    }
    party->flags2 = party->flags2 | 0x4000000;
    party->paperPoseId = animPaperPoseEntry(animGroup, 2);
    if ((!strcmp(animGroup, (char*)str_802CCF1C) || !strcmp(animGroup, (char*)str_802CCF24) ||
        !strcmp(animGroup, (char*)str_802CCF2C) || !strcmp(animGroup, (char*)str_802CCF10)) != 0) {
        flag = FALSE;
    } else {
        flag = TRUE;
    }
    if (!strcmp(animGroup, (char*)str_802CCF38)) {
        flag = party->currentMemberId == PARTY_MEMBER_FLURRIE;
    }
    animPoseSetPaperAnimGroup(party->paperAnimGroup, animGroup, flag);
    return TRUE;
}
#endif
#ifndef NONMATCHING
void partyPaperOff(PartyEntry* party);
#endif

#ifdef NONMATCHING
void partyPaperOff(PartyEntry* party) {
    s32 paperPoseId; // r3

    if ((party->flags2 & 0x4000000) && party->field_1C) {
        animPoseSetPaperAnimGroup(party->paperAnimGroup, NULL, FALSE);
        party->field_1C = 0;
        party->flags2 &= ~0x4000000;
        paperPoseId = party->paperPoseId;
        if (paperPoseId >= 0) {
            animPaperPoseRelease(paperPoseId);
            party->paperPoseId = -1;
        }
    }
}

void partyPaperLightOff(PartyEntry* party) {
    animPoseSetMaterialLightFlagOff(party->paperAnimGroup, 1);
}
#endif
#ifndef NONMATCHING
void partyPaperLightOff(PartyEntry* party);
#endif





static inline char* partyChgPoseId_inl(PartyEntry* party, s32 index) {
    BOOL v5;
    s32 poseIdx = index;
    char* v6;
    char* v8;

    if ((party->flags2 & 2) != 0) {
        return party->animName;
    }
    v5 = FALSE;
    if (party->currentMemberId < 8) {
        if (partyGetHp(party->currentMemberId) <= 5) v5 = TRUE;
    }
    if (v5 == TRUE) {
        if (index == 1) {
            poseIdx = 12;
        } else if (index == 2) {
            poseIdx = 13;
        } else if (index == 3) {
            poseIdx = 14;
        }
    }
    if (!(party->flags2 & 0x8000)) {
        v6 = partyPoseTbl[party->currentMemberId][poseIdx];
    } else if (party->currentMemberId != PARTY_MEMBER_YOSHI) {
        v6 = partyDotPoseTbl[party->currentMemberId][poseIdx];
    } else {
        v6 = yoshiDotPoseTbl[pouchGetPartyColor(PARTNER_YOSHI)][poseIdx];
    }
    v8 = party->animName;
    if (v8 && !strcmp(v8, v6)) {
        return v6;
    }
    party->animName = v6;
    party->field_20 = 0;
    party->field_8 |= 0x2000u;
    return v6;
}

#define PCPI2(party, index) \
    do { \
        char* v6; \
        BOOL v5; \
        s32 poseIdx = (index); \
        char* v8; \
        if (((party)->flags2 & 2) == 0) { \
            v5 = FALSE; \
            if ((party)->currentMemberId < 8) { \
                if (partyGetHp((party)->currentMemberId) <= 5) v5 = TRUE; \
            } \
            if (v5 == TRUE) { \
                if ((index) == 1) { \
                    poseIdx = 12; \
                } else if ((index) == 2) { \
                    poseIdx = 13; \
                } else if ((index) == 3) { \
                    poseIdx = 14; \
                } \
            } \
            if (!((party)->flags2 & 0x8000)) { \
                v6 = partyPoseTbl[(party)->currentMemberId][poseIdx]; \
            } else if ((party)->currentMemberId != PARTY_MEMBER_YOSHI) { \
                v6 = partyDotPoseTbl[(party)->currentMemberId][poseIdx]; \
            } else { \
                v6 = yoshiDotPoseTbl[pouchGetPartyColor(PARTNER_YOSHI)][poseIdx]; \
            } \
            v8 = (party)->animName; \
            if (!(v8 && !strcmp(v8, v6))) { \
                (party)->animName = v6; \
                (party)->field_20 = 0; \
                (party)->field_8 |= 0x2000u; \
            } \
        } \
    } while (0)

#ifdef NONMATCHING
char* partyChgPoseId(PartyEntry* party, s32 index) {
    char* v6;
    char* v8;
    BOOL v5;
    s32 poseIdx = index;

    if ((party->flags2 & 2) != 0) {
        return party->animName;
    }
    v5 = 0;
    if ((party->currentMemberId < 8) && (partyGetHp(party->currentMemberId) <= 5)) {
        v5 = TRUE;
    }
    if (v5 == TRUE) {
        if (index == 1) {
            poseIdx = 12;
        } else if (index == 2) {
            poseIdx = 13;
        } else if (index == 3) {
            poseIdx = 14;
        }
    }
    if (!(party->flags2 & 0x8000)) {
        v6 = partyPoseTbl[party->currentMemberId][poseIdx];
    } else if (party->currentMemberId != PARTY_MEMBER_YOSHI) {
        v6 = partyDotPoseTbl[party->currentMemberId][poseIdx];
    } else {
        v6 = yoshiDotPoseTbl[pouchGetPartyColor(PARTNER_YOSHI)][poseIdx];
    }
    v8 = party->animName;
    if (v8 && !strcmp(v8, v6)) {
        return v6;
    }
    party->animName = v6;
    party->field_20 = 0;
    party->field_8 |= 0x2000u;
    return v6;
}
#endif
#ifndef NONMATCHING
char* partyChgPoseId(PartyEntry* party, s32 index);
#endif
#define partyChgPoseId partyChgPoseId_inl


#ifdef NONMATCHING
void partyChgPose(PartyEntry* party, char* pose) {
    if (!(party->flags2 & 2)) {
        if (party->animName == NULL || strcmp(party->animName, pose)) {
            if (!(party->flags2 & 0x8000)) {
                party->animName = pose;
                party->field_20 = 0;
                party->field_8 |= 0x2000;
            }
        }
    }
}
#endif
#ifndef NONMATCHING
void partyChgPose(PartyEntry* party, char* pose);
#endif

#ifdef NONMATCHING
void partyChgPaper(PartyEntry* party, char* paper) {
    if (!(party->flags2 & 2)) {
        if (party->field_1C == 0 || strcmp((char*)party->field_1C, paper)) {
            party->field_1C = (u32)paper;
            party->field_20 = 0;
            party->field_8 |= 0x4000;
        }
    }
}
#endif
#ifndef NONMATCHING
void partyChgPaper(PartyEntry* party, char* paper);
#endif

#ifdef NONMATCHING
void partyCtrlOff(PartyEntry* party) {
    party = partyPtrTbl[0];
    if (party) {
        party->flags |= PARTY_FLAG_CTRL_OFF;
    }
    party = partyPtrTbl[1];
    if (party) {
        party->flags |= PARTY_FLAG_CTRL_OFF;
    }
}
#endif
#ifndef NONMATCHING
void partyCtrlOff(PartyEntry* party);
#endif

#ifdef NONMATCHING
void partyCtrlOn(PartyEntry* party) {
    party = partyPtrTbl[0];
    if (party) {
        party->flags &= ~PARTY_FLAG_CTRL_OFF;
    }
    party = partyPtrTbl[1];
    if (party) {
        party->flags &= ~PARTY_FLAG_CTRL_OFF;
    }
}
#endif
#ifndef NONMATCHING
void partyCtrlOn(PartyEntry* party);
#endif

#ifdef NONMATCHING
void partyRun(PartyEntry* party) {
    if (party->runMode == 0) {
        partyChgRunMode(party, 1);
    }
}
#endif
#ifndef NONMATCHING
void partyRun(PartyEntry* party);
#endif

#ifdef NONMATCHING
void partyStop(PartyEntry* party) {
    partyChgRunMode(party, 0);
}
#endif
#ifndef NONMATCHING
void partyStop(PartyEntry* party);
#endif

#ifdef NONMATCHING
void partySetForceMove(PartyEntry* party, s16 a2, f32 a3, f32 a4) {
    party->targetDir = a3;
    party->field_28 = a2;
    party->moveSpeed = a4;
    partyChgRunMode(party, 9);
    partyChgMot(party, 1);
}
#endif
#ifndef NONMATCHING
void partySetForceMove(PartyEntry* party, s16 a2, f32 a3, f32 a4);
#endif

#ifdef NONMATCHING
s32 partyEntryHello(s32 memberId) {
    s32 id = partyEntryMain(memberId);
    partyChgRunMode(partyGetPtr(id), 4);
    return id;
}
#endif
#ifndef NONMATCHING
s32 partyEntryHello(s32 memberId);
#endif

#ifdef NONMATCHING
s32 partyEntry(s32 memberId) {
    PartyEntry* party;
    s32 id;
    MarioWork* player;
#endif
#ifndef NONMATCHING
s32 partyEntry(s32 memberId);
#endif

#ifdef NONMATCHING
    id = partyEntryMain(memberId);
    party = partyGetPtr(id);
    party->scale = (Vec){1.0f, 1.0f, 1.0f};
    party->field_38 = 10;
    player = party->playerPtr;
    party->displayDirectionTarget = player->displayDirection;
    party->displayDirection = player->displayDirection;
    partyGetAppearPos2(party, &party->position);
    party->field_B8 = party->position;
    partyChgPoseId_inl(party, 1);
    party->runMode = 1;
    return id;
}
#endif
#ifndef NONMATCHING
s32 partyEntryPos(s32 memberId, f32 x, f32 y, f32 z);
#endif

#ifdef NONMATCHING
s32 partyEntryPos(s32 memberId, f32 x, f32 y, f32 z) {
    PartyEntry* party;
    s32 index;
    s32 id;
    BOOL lowHp;
    MarioWork* player;
#endif
#ifndef NONMATCHING
BOOL partyGoodbye(s32 id);
#endif

#ifdef NONMATCHING
    id = partyEntryMain(memberId);
    party = partyGetPtr(id);
    party->scale = (Vec){1.0f, 1.0f, 1.0f};
    party->position = (Vec){x, y, z};
    player = party->playerPtr;
    party->scale = (Vec){1.0f, 1.0f, 1.0f};
    party->displayDirectionTarget = player->displayDirection;
    party->displayDirection = player->displayDirection;
    index = 1;
    if (!(party->flags2 & 2)) {
        lowHp = FALSE;
        if (party->currentMemberId < 8 && partyGetHp(party->currentMemberId) <= 5) {
            lowHp = TRUE;
        }
        if (lowHp == TRUE) {
            index = 12;
        }
        if (!(party->flags2 & 0x8000)) {
            index = (s32)partyPoseTbl[party->currentMemberId][index];
        } else if (party->currentMemberId != PARTY_MEMBER_YOSHI) {
            index = (s32)partyDotPoseTbl[party->currentMemberId][index];
        } else {
            index = (s32)yoshiDotPoseTbl[pouchGetPartyColor(PARTNER_YOSHI)][index];
        }
        if (party->animName == NULL || strcmp(party->animName, (char*)index)) {
            party->animName = (char*)index;
            party->field_20 = 0;
            party->field_8 |= 0x2000;
        }
    }
    party->runMode = 0;
    return id;
}
#endif
#ifndef NONMATCHING
s32 partyKill(s32 id);
#endif

#ifdef NONMATCHING
BOOL partyGoodbye(s32 id) {
    BOOL ret = FALSE;
#endif
#ifndef NONMATCHING
s32 partyKill2(s32 id);
#endif

#ifdef NONMATCHING
    if (id >= 0) {
        partyChgRunMode(partyGetPtr(id), 8);
        ret = TRUE;
    }
    return ret;
}
#endif
#ifndef NONMATCHING
s32 yoshiSetColor(void);
#endif

#ifdef NONMATCHING
s32 partyKill(s32 id) {
    PartyEntry* party;
    MarioWork* player;
    PartyEntry* other;

    party = partyGetPtr(id);
    if (party == NULL) {
        return 0;
    }
    player = party->playerPtr;
    party_dp = &partyDataTbl[partyGetPtr(player->currPartySlotId[id])->currentMemberId];
    if (party_dp->exit_func && party->runMode != 11) {
        party_dp->exit_func(party);
    }
    if (partyGetPtr(player->currPartySlotId[id])) {
        player->prevPartyMemberId[id] = partyGetPtr(player->currPartySlotId[id])->currentMemberId;
    } else {
        player->prevPartyMemberId[id] = 0;
    }
    player->currPartySlotId[id] = -1;
    partyPtrTbl[id] = NULL;
    animPoseRelease(party->paperAnimGroup);
    __memFree(HEAP_DEFAULT, party);
    return 0;
}

s32 partyKill2(s32 id) {
    PartyEntry* party;
    MarioWork* player;

    party = partyGetPtr(id);
    if (party == NULL) {
        return 0;
    }
    player = party->playerPtr;
    party_dp = &partyDataTbl[partyGetPtr(player->currPartySlotId[id])->currentMemberId];
    if (party_dp->exit_func && party->runMode != 11) {
        party_dp->exit_func(party);
    }
    player->prevPartyMemberId[id] = 0;
    player->currPartySlotId[id] = -1;
    partyPtrTbl[id] = NULL;
    animPoseRelease(party->paperAnimGroup);
    __memFree(HEAP_DEFAULT, party);
    return 0;
}

s32 yoshiSetColor(void) {
    s32 color;
    s32 r = irand(1000);

    if (r < 150) {
        color = 0;
    } else if (r < 300) {
        color = 1;
    } else if (r < 450) {
        color = 2;
    } else if (r < 600) {
        color = 3;
    } else if (r < 750) {
        color = 4;
    } else if (r < 900) {
        color = 5;
    } else {
        color = 6;
    }
    pouchSetPartyColor(PARTNER_YOSHI, color);
    return color;
}

f32 partyGetHeight(PartyEntry* party) {
    if (party->currentMemberId == PARTY_MEMBER_YOSHI && (party->flags & 0x100)) {
        return 18.5f + party->height;
    }
    return party->height;
}
#endif
#ifndef NONMATCHING
f32 partyGetHeight(PartyEntry* party);
#endif

static inline s32 partyGetFreeSlot(s32 start) {
    s32 i;

    for (i = start; i < 2; i++) {
        if (partyPtrTbl[i] == NULL) {
            memset(partyPtrTbl[i] = __memAlloc(HEAP_DEFAULT, sizeof(PartyEntry)), 0, sizeof(PartyEntry));
            return i;
        }
    }
    return -1;
}

static inline void partyPoseEntry(PartyEntry* party) {
    char* animName;

    if (party->currentMemberId != PARTY_MEMBER_YOSHI) {
        if (!(party->flags2 & 0x8000)) {
            animName = party_dp->name;
        } else {
            animName = (char*)str_802CCEEC;
        }
    } else {
        animName = yoshigroup[pouchGetPartyColor(PARTNER_YOSHI)];
        if (party->flags2 & 0x8000) {
            animName = (char*)str_802CCEEC;
        }
    }
    if (party->paperAnimGroup >= 0) {
        animPoseRelease(party->paperAnimGroup);
    }
    party->paperAnimGroup = animPoseEntry(animName, 2);
}

static inline void setAnimPoseMaterialFlag(PartyEntry* party) {
    MarioWork* player = party->playerPtr;

    animPoseSetMaterialFlagOn(party->paperAnimGroup, animPoseGetMaterialFlag(player->paperAnimGroupId[marioAnimeId()]));
    animPoseSetMaterialLightFlagOn(party->paperAnimGroup,
                                   animPoseGetMaterialLightFlag(player->paperAnimGroupId[marioAnimeId()]));
}

static inline s32 partyGetFreeSlot2(void) {
    if (partyPtrTbl[1] == NULL) {
        memset(partyPtrTbl[1] = __memAlloc(HEAP_DEFAULT, sizeof(PartyEntry)), 0, sizeof(PartyEntry));
        return 1;
    }
    return -1;
}


#pragma force_active on
__declspec(section ".sdata") char* yoshigroup[7] = {
        (char*)str_802CCD60,
        (char*)str_802CCD6C,
        (char*)str_802CCD7C,
        (char*)str_802CCD8C,
        (char*)str_802CCD9C,
        (char*)str_802CCDAC,
        (char*)str_802CCDBC
};
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_8041061C_sdata[1] = {0};
#pragma force_active reset
#ifdef NONMATCHING
s32 partyEntryMain(s32 memberId) {
    MarioWork* player;
    s32 slot;
    PartyEntry* party;
#endif
#ifndef NONMATCHING
s32 partyEntryMain(s32 memberId);
#endif

#ifdef NONMATCHING
    player = marioGetPtr();
    slot = partyGetFreeSlot(0);
    if (slot < 0) {
        return -1;
    }
    party = partyGetPtr(slot);
    memset(party, 0, sizeof(PartyEntry));
    party->camId = marioGetCamId();
    party->paperAnimGroup = -1;
    party->field_10 = -1;
    party->paperPoseId = -1;
    party->flags = 1;
    party->currentSlotId = slot;
    party->playerPtr = player;
    party->currentMemberId = memberId;
    if (player->prevPartyMemberId[0] == 0) {
        player->prevPartyMemberId[0] = party->currentMemberId;
    }
    if (slot == 1) {
        party->flags |= 4;
    }
    party_dp = &partyDataTbl[memberId];
    if (player->flags & 0x80000000) {
        party->flags2 |= 0x8000;
    }
    if (!party && !party && !party) {
    }
    partyPoseEntry(party);
    animPosePeraOff(party->paperAnimGroup);
    setAnimPoseMaterialFlag(party);
    partyChgPose(party, partyChgPoseId(party, 1));
    party->field_1C = 0;
    party_dp->init_func(party);
    return slot;
}
#endif
#ifndef NONMATCHING
s32 partyEntry2(s32 memberId);
#endif

#ifdef NONMATCHING
s32 partyEntry2(s32 memberId) {
    MarioWork* player;
    s32 slot;
    PartyEntry* party;
#endif
#ifndef NONMATCHING
s32 partyEntry2Hello(s32 memberId);
#endif

#ifdef NONMATCHING
    player = marioGetPtr();
    slot = partyGetFreeSlot2();
    if (slot < 0) {
        return -1;
    }
    party = partyGetPtr(slot);
    memset(party, 0, sizeof(PartyEntry));
    party->camId = marioGetCamId();
    party->paperAnimGroup = -1;
    party->field_10 = -1;
    party->paperPoseId = -1;
    party->flags = 9;
    party->currentSlotId = slot;
    party->playerPtr = player;
    party->currentMemberId = memberId;
    if (slot == 1) {
        party->flags |= 4;
    }
    party_dp = &partyDataTbl[memberId];
    partyPoseEntry(party);
    animPosePeraOff(party->paperAnimGroup);
    setAnimPoseMaterialFlag(party);
    partyChgPose(party, partyChgPoseId(party, 1));
    party->field_1C = 0;
    party_dp->init_func(party);
    party->position = player->position;
    party->field_B8 = party->position;
    party->scale = (Vec){1.0f, 1.0f, 1.0f};
    party->runMode = 0;
    return slot;
}

s32 partyEntry2Hello(s32 memberId) {
    MarioWork* player;
    s32 slot;
    PartyEntry* party;

    player = marioGetPtr();
    slot = partyGetFreeSlot2();
    if (slot < 0) {
        return -1;
    }
    party = partyGetPtr(slot);
    memset(party, 0, sizeof(PartyEntry));
    party->camId = marioGetCamId();
    party->paperAnimGroup = -1;
    party->field_10 = -1;
    party->paperPoseId = -1;
    party->flags = 9;
    party->currentSlotId = slot;
    party->playerPtr = player;
    party->currentMemberId = memberId;
    if (slot == 1) {
        party->flags |= 4;
    }
    party_dp = &partyDataTbl[memberId];
    partyPoseEntry(party);
    animPosePeraOff(party->paperAnimGroup);
    setAnimPoseMaterialFlag(party);
    partyChgPose(party, partyChgPoseId(party, 1));
    party->field_1C = 0;
    party_dp->init_func(party);
    partyChgRunMode(party, 4);
    return slot;
}

s32 partyEntry2Pos(s32 memberId, f32 x, f32 y, f32 z) {
    MarioWork* player;
    s32 slot;
    PartyEntry* party;

    player = marioGetPtr();
    slot = partyGetFreeSlot2();
    if (slot < 0) {
        return -1;
    }
    party = partyGetPtr(slot);
    memset(party, 0, sizeof(PartyEntry));
    party->camId = marioGetCamId();
    party->paperAnimGroup = -1;
    party->field_10 = -1;
    party->paperPoseId = -1;
    party->flags = 9;
    party->currentSlotId = slot;
    party->playerPtr = player;
    party->currentMemberId = memberId;
    if (slot == 1) {
        party->flags |= 4;
    }
    party_dp = &partyDataTbl[memberId];
    partyPoseEntry(party);
    animPosePeraOff(party->paperAnimGroup);
    setAnimPoseMaterialFlag(party);
    { char* id = partyChgPoseId(party, 1); partyChgPose(party, id); }
    party->field_1C = 0;
    party_dp->init_func(party);
    partyChgRunMode(party, 2);
    party->position = (Vec){x, y, z};
    party->field_B8 = party->position;
    party->scale.x = 1.0f;
    party->scale.y = 1.0f;
    party->scale.z = 1.0f;
    return slot;
}
#endif
#ifndef NONMATCHING
s32 partyEntry2Pos(s32 memberId, f32 x, f32 y, f32 z);
#endif

#define PU8(p, o) (*(u8*)((u8*)(p) + (o)))
#define PS8(p, o) (*(s8*)((u8*)(p) + (o)))
void bomhei_use_cancel(void);
void partyShadowOff(PartyEntry* party);
void vivianUnhold(PartyEntry* party);
void marioGetoffYoshi(void);
void L_partyVivianTailStart(PartyEntry* party);
void getRidePos(PartyEntry* party, Vec* pos);
void driveParty(PartyEntry* party);
#include "mario/mario_sbr.h"
s32 partyHelloMain(PartyEntry* party);
double sin(double);
double cos(double);
f32 toMovedir2(f32 a, f32 b);
f32 toMovedirSimple(f32 a);
s32 yoshiGetStatus(void);
BOOL N_marioShipGetDir(void);
void partyClearJumpPara(PartyEntry* party);
void L_partyForceSlitOff(PartyEntry* party);
static inline void partyShadowOn(PartyEntry* party) {
    if (party) {
        party->flags2 &= ~0x100000;
    }
}
#define PU16(p, o) (*(u16*)((u8*)(p) + (o)))
#define PF32(p, o) (*(f32*)((u8*)(p) + (o)))

#ifdef NONMATCHING
void partyInit(void) {
    memset(partyPtrTbl, 0, sizeof(partyPtrTbl));
}
#endif
#ifndef NONMATCHING
void partyInit(void);
#endif



void partyClearFootmark(void);
void chuchu_reinit(PartyEntry* party);
void unk_8014c47c(void);

#ifdef NONMATCHING
static inline void partyReInitClear(PartyEntry* party) {
    s32 poseId;
    poseId = party->paperAnimGroup;
    if (poseId >= 0) {
        animPoseSetMaterialFlagOff(poseId, -1);
        animPoseSetMaterialLightFlagOn(poseId, 2);
    }
}
#endif

#ifdef NONMATCHING
void partyReInit(void) {
    s32 poseId;
    s32 dotted;
    PartyEntry* party;
    char* pose;

    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        party->flags = 0xD;
        party->flags2 = 0;
        poseId = party->paperAnimGroup;
        if (poseId >= 0) {
            animPoseSetMaterialFlagOff(poseId, -1);
            animPoseSetMaterialLightFlagOn(poseId, 2);
        }
        party->field_37 = 0;
        if (party->field_1C) {
            animPoseSetPaperAnimGroup(party->paperAnimGroup, NULL, FALSE);
            party->field_1C = 0;
            party->flags2 &= ~0x4000000;
            if (party->paperPoseId >= 0) {
                animPaperPoseRelease(party->paperPoseId);
                party->paperPoseId = -1;
            }
        }
        *(s32*)((u8*)party + 0x130) = 0;
        *(s32*)((u8*)party + 0x12C) = 0;
        *(s32*)((u8*)party + 0x148) = 0;
        party->field_138 = NULL;
        *(s32*)((u8*)party + 0x13C) = 0;
        *(s32*)((u8*)party + 0x134) = 0;
        *(s32*)((u8*)party + 0x140) = 0;
        party->field_144 = NULL;
        partyChgPose(party, partyChgPoseId(party, 1));
        partyChgRunMode(party, 2);
        partyChgMot(party, 0);
        party->yoshiPsndSFXId = -1;
        party->scale = (Vec){1.0f, 1.0f, 1.0f};
    }
    party = partyGetPtr(marioGetPartyId());
    if (party) {
        dotted = party->flags2 & 0x8000;
        party->flags = 1;
        party->flags2 = 0;
        party->field_37 = 0;
        party->camId = marioGetCamId();
        if (party) {
            poseId = party->paperAnimGroup;
        if (poseId >= 0) {
            animPoseSetMaterialFlagOff(poseId, -1);
            animPoseSetMaterialLightFlagOn(poseId, 2);
        }
            if (party->field_1C) {
            animPoseSetPaperAnimGroup(party->paperAnimGroup, NULL, FALSE);
            party->field_1C = 0;
            party->flags2 &= ~0x4000000;
            if (party->paperPoseId >= 0) {
                animPaperPoseRelease(party->paperPoseId);
                party->paperPoseId = -1;
            }
        }
            *(s32*)((u8*)party + 0x130) = 0;
            *(s32*)((u8*)party + 0x12C) = 0;
            *(s32*)((u8*)party + 0x148) = 0;
            party->field_138 = NULL;
            *(s32*)((u8*)party + 0x13C) = 0;
            *(s32*)((u8*)party + 0x134) = 0;
            *(s32*)((u8*)party + 0x140) = 0;
            party->field_144 = NULL;
            party->scale = (Vec){1.0f, 1.0f, 1.0f};
        }
        partyClearFootmark();
        if (dotted) {
            partyPoseEntry(party);
        }
        if (party->currentMemberId == PARTY_MEMBER_YOSHI && party->runMode == 3) {
            return;
        }
        if (!(marioGetPtr()->flags & 0x400000)) {
            pose = partyChgPoseId(party, 1);
            partyChgPose(party, pose);
            partyChgRunMode(party, 2);
            partyChgMot(party, 0);
        } else {
            pose = partyChgPoseId(party, 1);
            partyChgPose(party, pose);
            partyChgRunMode(party, 2);
            party->field_3A[1] = 6;
            party->field_38 = 0;
            party->flags |= 0x8000;
        }
        if (party->currentMemberId == 7) {
            chuchu_reinit(party);
        }
        unk_8014c47c();
    }
}
void partyUsePost(PartyEntry* party) {
    PartyFunc func;
    if (party && party->runMode == 3) {
        func = partyDataTbl[party->currentMemberId].post_func;
        if (func) {
            func(party);
        }
    }
}
#endif
#ifndef NONMATCHING
void partyReInit(void);
void partyUsePost(PartyEntry* party);
#endif


static inline void partyChgRunM(PartyEntry* party);
static inline void partyChgRunMo(PartyEntry* party);
#ifdef NONMATCHING
void N__partyChgRunMode(PartyEntry* party, s32 prev, s32 mode) {
    MarioWork* mario;
    PartyFunc func;
#endif
#ifndef NONMATCHING
void N__partyChgRunMode(PartyEntry* party, s32 prev, s32 mode);
#endif

#ifdef NONMATCHING
    switch (prev) {
    case 11:
        if (mode != 8) {
            mario = party->playerPtr;
            partyChgRunMo(party);
            party->moveDir = mario->moveDirection;
            party->targetDir = mario->directionView;
            party->displayDirectionTarget = mario->displayDirectionTarget;
            party->flags &= ~0x70000;
            partyClearJumpPara(party);
            partyChgPoseId(party, 1);
            party->flags2 &= ~0x10;
            party->flags2 &= ~1;
            partyShadowOn(party);
        }
        break;
    case 4:
        mario = party->playerPtr;
        partyChgRunM(party);
        party->flags2 &= ~0x10;
        party->moveDir = mario->moveDirection;
        party->targetDir = mario->directionView;
        party->displayDirectionTarget = mario->displayDirectionTarget;
        party->displayDirection = mario->displayDirection;
        partyClearJumpPara(party);
        partyChgPoseId(party, 1);
        party->flags2 &= ~0x10;
        party->runMode = 1;
        break;
    case 12:
        partyShadowOn(party);
        break;
    case 3:
        func = partyDataTbl[party->currentMemberId].post_func;
        if (func) {
            func(party);
        }
        break;
    case 1:
    case 2:
        L_partyForceSlitOff(party);
        break;
    }
}
#endif
#ifndef NONMATCHING
void partyChgRunMode(PartyEntry* party, s32 mode);
#endif

#ifdef NONMATCHING
#pragma dont_inline on
void partyChgRunMode(PartyEntry* party, s32 mode) {
    if (party->runMode != 9 && party->runMode != 3) {
        party->prevRunMode = party->runMode;
    }
    N__partyChgRunMode(party, party->runMode, mode);
    party->runMode = mode;
    party->field_8 |= 8;
}
#pragma dont_inline reset

#pragma dont_inline on
void N_partyForceChgRunMode(PartyEntry* party, s32 mode, s32 sub) {
    if (party->runMode != 9 && party->runMode != 3) {
        party->prevRunMode = party->runMode;
    }
    N__partyChgRunMode(party, party->runMode, mode);
    party->runMode = mode;
    party->field_8 &= ~8;
    party->field_38 = sub;
}
#pragma dont_inline reset
#endif
#ifndef NONMATCHING
void N_partyForceChgRunMode(PartyEntry* party, s32 mode, s32 sub);
#endif

/* @@MID1@@ */
#ifdef NONMATCHING
void unk_800ba2dc(PartyEntry* party) {
    if (party->runMode == party->prevRunMode) {
        return;
    }
    if (party->runMode == 4) {
        MarioWork* mario = party->playerPtr;
        partyChgRunM(party);
        party->flags2 &= ~0x10;
        party->moveDir = mario->moveDirection;
        party->targetDir = mario->directionView;
        party->displayDirectionTarget = mario->displayDirectionTarget;
        party->displayDirection = mario->displayDirection;
        partyClearJumpPara(party);
        partyChgPoseId(party, 1);
        party->flags2 &= ~0x10;
        party->runMode = 1;
        partyUsePost(party);
        partyChgMot(party, 0);
    } else if (party->runMode == 11) {
        MarioWork* mario = party->playerPtr;
        partyChgRunMo(party);
        party->moveDir = mario->moveDirection;
        party->targetDir = mario->directionView;
        party->displayDirectionTarget = mario->displayDirectionTarget;
        party->flags &= ~0x70000;
        partyClearJumpPara(party);
        partyChgPoseId(party, 1);
        party->flags2 &= ~0x10;
        party->flags2 &= ~1;
        partyShadowOn(party);
        partyUsePost(party);
        partyChgMot(party, 0);
    } else {
        if (party->runMode == 12) {
            partyShadowOn(party);
        }
        partyUsePost(party);
        party->runMode = party->prevRunMode;
        party->field_8 |= 8;
        partyChgMot(party, 0);
    }
}
#endif
#ifndef NONMATCHING
void unk_800ba2dc(PartyEntry* party);
#endif


static inline s32 partyCountActive(void) {
    s32 count = 0;
    s32 i;
    for (i = 0; i < 2; i++) {
        if (partyPtrTbl[i] && (partyGetPtr(i)->flags & 1)) {
            count++;
        }
    }
    return count;
}
#ifdef NONMATCHING
void partyMain(void) {
    s32 i;
    PartyEntry* party;

    marioGetPtr();
    if (partyCountActive()) {
        unk_8013be14();
        for (i = 0; i < 2; i++) {
            party = partyPtrTbl[i];
            if (party && (party->flags & 1) && marioBgmodeChk() != 1) {
                driveParty(party);
            }
        }
    }
}
#endif
#ifndef NONMATCHING
void partyMain(void);
#endif

/* @@DRIVE@@ */
void party_kemuri(PartyEntry* party);
void vivianShadow(PartyEntry* party);
s32 vivianGetStatus(void);
void unk_800c7c98(PartyEntry* party);
void partyForceWalk(PartyEntry* party);
void L_partyForceSlitOff(PartyEntry* party);
void partyPreDisp(PartyEntry* party);
void partyHello(PartyEntry* party);
void partyRideMain(PartyEntry* party);
s32 partyRideYoshiMain(PartyEntry* party);
void party_damage_return(PartyEntry* party);
s32 partyDokanInit(PartyEntry* party);
s32 partyDokanMain(PartyEntry* party);

static inline void partyHello_inl(PartyEntry* party);

#ifdef NONMATCHING
void driveParty(PartyEntry* party) {
    MarioWork* mario;
    f32 x, y, z;

    mario = party->playerPtr;
    *(f32*)((u8*)party + 0xF8) = *(f32*)((u8*)mario + 0x198);
    if (*(s16*)((u8*)party + 0x2A) > 0) {
        (*(s16*)((u8*)party + 0x2A))--;
    }
    switch (party->runMode) {
    case 4: case 5: case 6: case 7: case 8: case 14:
        break;
    default:
        if (!(party->flags & 0x20000000)) break;
        if (vivianGetStatus() != 2) {
            vivianShadow(party);
        }
        partyPreDisp(party);
        return;
    }
    if (*(u32*)mario & 0x2000000) {
        party->flags |= 0x800000;
    } else {
        party->flags &= ~0x800000;
    }
    party->field_138 = NULL;
    *(s32*)((u8*)party + 0x12C) = 0;
    *(s32*)((u8*)party + 0x140) = 0;
    *(s32*)((u8*)party + 0x134) = 0;
    *(s32*)((u8*)party + 0x130) = 0;
    switch (party->runMode) {
    case 0:
        if ((party->flags & 0x20000000) && !(party->flags & 0x10000000)) break;
        if (party->field_8 & 8) {
            party->field_8 &= ~8;
            partyChgPoseId_inl(party, 1);
            party->moveSpeed = 0.0f;
            party->flags &= ~0x100;
            partyChgMot(party, 0);
        }
        party_dp = &partyDataTbl[party->currentMemberId];
        party_dp->move_func(party);
        break;
    case 1:
        if ((party->flags & 0x20000000) && !(party->flags & 0x10000000)) break;
        unk_800c7c98(party);
        break;
    case 2:
        if ((party->flags & 0x20000000) && !(party->flags & 0x10000000)) break;
        party_dp = &partyDataTbl[party->currentMemberId];
        party_dp->move_func(party);
        break;
    case 9:
        if ((party->flags & 0x20000000) && !(party->flags & 0x10000000)) break;
        partyForceWalk(party);
        break;
    case 3:
        if ((party->flags & 0x20000000) && !(party->flags & 0x10000000)) break;
        {
            void (*fn)(PartyEntry*);
            party_dp = &partyDataTbl[party->currentMemberId];
            fn = party_dp->use_func;
            party->flags |= 0x100;
            fn(party);
        }
        break;
    case 4:
    case 5:
    case 6:
    case 7:
        partyHello_inl(party);
        break;
    case 8:
        party_dp = &partyDataTbl[party->currentMemberId];
        party_dp->bye_func(party);
        break;
    case 10:
        if (party->field_8 & 8) {
            party->field_8 &= ~8;
            partyDokanInit(party);
            party->flags &= ~0x100;
        }
        partyDokanMain(party);
        break;
    case 11:
        if ((party->flags & 0x20000000) && !(party->flags & 0x10000000)) break;
        if (party->field_8 & 8) {
            party->field_8 &= ~8;
            party->field_38 = 0;
            party->flags &= ~0x100;
            L_partyForceSlitOff(party);
        }
        partyRideMain(party);
        break;
    case 12:
        if ((party->flags & 0x20000000) && !(party->flags & 0x10000000)) break;
        if (party->field_8 & 8) {
            party->field_8 &= ~8;
            party->field_38 = 0;
            party->flags &= ~0x100;
        }
        partyRideYoshiMain(party);
        break;
    case 13:
        if ((party->flags & 0x20000000) && !(party->flags & 0x10000000)) break;
        party_damage_return(party);
        break;
    case 14:
        if (party->field_8 & 8) {
            party->field_8 &= ~8;
        }
        mario->prevPartyMemberId[party->currentSlotId] = party->currentMemberId;
        mario->currPartySlotId[party->currentSlotId] = -1;
        partyPtrTbl[party->currentSlotId] = NULL;
        animPoseRelease(party->paperAnimGroup);
        __memFree(0, party);
        return;
    }
    party_kemuri(party);
    marioGetScreenPos(party->position, &x, &y, &z);
    if (marioChkInScreen(x, y)) {
        party->flags2 &= ~0x800000;
    } else {
        party->flags2 |= 0x800000;
    }
    *(Vec*)((u8*)party + 0xAC) = (Vec){0.0f, 0.0f, 0.0f};
    partyPreDisp(party);
}
static inline void partyHello_inl(PartyEntry* party) {
    MarioWork* mario;

    if (party->field_8 & 8) {
        party->field_8 &= ~8;
        mario = party->playerPtr;
        if (mario->currMotionId == 0x16 || mario->currMotionId == 0x18 || mario->currMotionId == 0x19) {
            party->field_38 = 30;
        } else if (party->runMode == 4 || party->runMode == 5) {
            party->flags2 |= 0x10;
            party->scale = (Vec){0.0f, 0.0f, 0.0f};
            party->field_38 = 0;
            party->displayDirectionTarget = mario->displayDirection;
            party->displayDirection = mario->displayDirection;
            party->position = mario->position;
            party->field_B8 = party->position;
        } else if (party->runMode == 7) {
            party->scale = (Vec){1.0f, 1.0f, 1.0f};
            party->field_38 = 20;
            party->displayDirectionTarget = mario->displayDirection;
            party->displayDirection = mario->displayDirection;
        } else {
            party->scale = (Vec){1.0f, 1.0f, 1.0f};
            party->field_38 = 10;
            party->displayDirectionTarget = mario->displayDirection;
            party->displayDirection = mario->displayDirection;
            party->position = mario->position;
            party->field_B8 = party->position;
        }
        party->flags &= ~0x100;
    }
    partyHelloMain(party);
}
#endif
#ifndef NONMATCHING
void driveParty(PartyEntry* party);
#endif



#ifdef NONMATCHING
BOOL partyDoWork(void) {
    PartyEntry* party = partyGetPtr(marioGetPtr()->currPartySlotId[0]);
    if (!party) {
        return FALSE;
    }
    if (party->runMode != 0 && party->runMode != 1 && party->runMode != 2) {
        return FALSE;
    }
    marioGetPtr()->baseSpeed = 0.0f;
    partyChgRunMode(party, 3);
    return TRUE;
}
#endif
#ifndef NONMATCHING
BOOL partyDoWork(void);
#endif


#ifdef NONMATCHING
void partyHello(PartyEntry* party) {
    partyHello_inl(party);
}
#endif
#ifndef NONMATCHING
void partyHello(PartyEntry* party);
#endif

/* @@HELLO@@ */
void partyMoveNoHosei(PartyEntry* party);
f32 partyToMovedir(PartyEntry* party, f32 dir);
void partyGetAppearPos(PartyEntry* party, Vec* pos);
void allPartyForceRideOn(void);

#ifdef NONMATCHING
s32 partyHelloMain(PartyEntry* party) {
    s32 ret = 0;
    u8* mario = (u8*)party->playerPtr;

    switch (party->field_38) {
    case 0: {
        f32 x, y, z, h, dy;
        x = PF32(mario, 0x8C);
        y = PF32(mario, 0x90);
        z = PF32(mario, 0x94);
        party->position.x = x;
        party->position.y = y + 0.5f * PF32(mario, 0x1B8);
        party->position.z = z;
        partyGetAppearPos(party, (Vec*)((u32)party + 0x94));
        *(s32*)((u8*)party + 0x24) = 16;
        PF32(party, 0x128) = distABf(x, z, PF32(party, 0x94), PF32(party, 0x9C));
        PF32(party, 0x100) = angleABf(x, z, PF32(party, 0x94), PF32(party, 0x9C));
        PF32(party, 0x104) = PF32(party, 0x128) / (f32)*(s32*)((u8*)party + 0x24);
        h = 0.5f * (f32)*(s32*)((u8*)party + 0x24);
        dy = PF32(party, 0x98) - party->position.y;
        if (__fabsf(dy) < 1.0f) {
            dy = 10.0f;
        } else if (dy >= 0.0f) {
            dy += 0.5f * PF32(party, 0xF0);
        } else {
            dy = 10.0f;
        }
        dy = (dy + dy) / (h * h - h);
        PF32(party, 0x114) = dy * h;
        PF32(party, 0x118) = -dy;
        party->flags |= 0x10;
        party->field_38 = 1;
        break;
    }
    case 1:
        partyMoveNoHosei(party);
        if (PF32(party, 0x114) <= 0.0f) {
            party->flags &= ~0x10;
            PF32(party, 0x118) = -1.6f;
        }
        if (party->position.y < -2000.0f) {
            *(s32*)((u8*)party + 0x24) = 0;
            party->field_38 = 2;
            break;
        }
        if (*(u32*)((u8*)party + 0x138) == 0) {
            s32 n = 16 - *(s32*)((u8*)party + 0x24);
        f32 v = (f32)n / 16.0f;
            Vec s;
        s = (Vec){0.0f, 0.0f, 0.0f};
            s.x = s.y = s.z = v;
            party->scale = s;
            if (--*(s32*)((u8*)party + 0x24) <= 0) {
                *(s32*)((u8*)party + 0x24) = 0;
            }
            break;
        }
        party->field_38 = 2;
    case 2: {
        f32 v = (f32)(16 - *(s32*)((u8*)party + 0x24)) / 16.0f;
        Vec s;
        s = (Vec){0.0f, 0.0f, 0.0f};
        s.x = s.y = s.z = v;
        party->scale = s;
        if (--*(s32*)((u8*)party + 0x24) > 0) {
            break;
        }
        *(s32*)((u8*)party + 0x24) = 0;
        if (PF32(party, 0x110) >= 90.0f && PF32(party, 0x110) <= 270.0f) {
            PF32(party, 0xFC) = partyToMovedir(party, 180.0f);
            PF32(party, 0x100) = PF32(party, 0xFC);
            PF32(party, 0x110) = PF32(party, 0x10C) = 180.0f;
        } else {
            PF32(party, 0xFC) = partyToMovedir(party, 0.0f);
            PF32(party, 0x100) = PF32(party, 0xFC);
            PF32(party, 0x110) = PF32(party, 0x10C) = 0.0f;
        }
        partyClearJumpPara(party);
        partyChgPoseId_inl(party, 1);
        party->flags2 &= ~0x10;
        ret = 1;
        party->runMode = 1;
        psndSFXOn_3D((const char*)0x20920, (Vec*)(mario + 0x8C));
        break;
    }
    case 10:
        partyGetAppearPos2(party, &party->position);
        party->field_B8 = party->position;
        PCPI2(party, 1);
        party->runMode = 1;
        ret = 1;
        break;
    case 20:
        PCPI2(party, 1);
        party->runMode = 0;
        ret = 1;
        break;
    case 30:
        allPartyForceRideOn();
        ret = 1;
        break;
    }
    return ret;
}
#endif
#ifndef NONMATCHING
s32 partyHelloMain(PartyEntry* party);
#endif


#ifdef NONMATCHING
s32 partyGoodbyeInit(PartyEntry* party) {
    MarioWork* mario;
    party->field_38 = 10;
    party_dp = &partyDataTbl[party->currentMemberId];
    if (party_dp->init_func) {
        party_dp->init_func(party);
    }
    if (party->flags & 0x100) {
        if (party->currentMemberId == PARTY_MEMBER_VIVIAN) {
            vivianUnhold(party);
            party->field_38 = 0;
        }
        if (party->currentMemberId == PARTY_MEMBER_YOSHI) {
            marioGetoffYoshi();
            party->field_38 = 0;
        }
    }
    mario = party->playerPtr;
    if (mario->currMotionId == 0x16 || mario->currMotionId == 0x18 || mario->currMotionId == 0x19) {
        party->field_38 = 20;
    }
    return 0;
}
#endif
#ifndef NONMATCHING
s32 partyGoodbyeInit(PartyEntry* party);
#endif

/* @@DOKAN@@ */
#ifdef NONMATCHING
s32 partyGoodbyeMain(PartyEntry* party) {
    MarioWork* mario = marioGetPtr();
    f32 tx, ty, tz, px, py, pz;

    switch (party->field_38) {
    case 0:
        party_dp = &partyDataTbl[party->currentMemberId];
        party_dp->use_func(party);
        if (party->currentMemberId == PARTY_MEMBER_VIVIAN) {
            if (vivianGetStatus() == 0) {
                party->field_38 = 10;
                party->runMode = 8;
            }
        } else if (party->currentMemberId == PARTY_MEMBER_YOSHI) {
            if (yoshiGetStatus() == 0) {
                party->field_38 = 10;
                party->runMode = 8;
            }
        } else {
            party->field_38 = 10;
            party->runMode = 8;
        }
        break;
    case 10:
        psndSFXOn_3D((const char*)0x2091F, &mario->position);
        tx = party->moveTarget.x = mario->position.x;
        ty = party->moveTarget.y = 0.5f * mario->wPlayerCollisionBox.y + mario->position.y;
        tz = party->moveTarget.z = mario->position.z;
        px = party->position.x;
        pz = party->position.z;
        py = party->position.y;
        party->moveSpeed = 4.0f;
        party->gravity = 1.6f;
        party->moveDistance = distABf(px, pz, tx, tz);
        party->targetDir = angleABf(px, pz, tx, tz);
        ty -= py;
        party->moveFrames = 15;
        party->moveSpeed = party->moveDistance / (f32)party->moveFrames;
        party->velY = (0.5f * ((f32)party->moveFrames * (party->gravity * (f32)party->moveFrames)) + ty) / (f32)party->moveFrames;
        partyChgPoseId_inl(party, 4);
        party->field_38 = 11;
        break;
    case 11: {
        f32 t;
        party->velY -= party->gravity;
        party->position.y += party->velY;
        movePos(&party->position.x, &party->position.z, party->moveSpeed, party->targetDir);
        party->displayDirection = revise360(50.0f + party->displayDirection);
        t = party->moveFrames;
        if (t > 10.0f) {
            t = 10.0f;
        }
        party->scale.x = t / 10.0f;
        party->scale.y = party->scale.x;
        party->scale.z = party->scale.x;
        if (--party->moveFrames < 0) {
            party->field_38 = 12;
        }
        break;
    }
    case 12:
        partyChgPoseId_inl(party, 1);
        party->velY = 0.0f;
        party->position.y = party->moveTarget.y;
        partyChgRunMode(party, 14);
        return 1;
    case 20:
        partyChgRunMode(party, 14);
        return 1;
    }
    return 0;
}
#endif
#ifndef NONMATCHING
s32 partyGoodbyeMain(PartyEntry* party);
s32 partyGoodbyeMain(PartyEntry* party);
#endif

void L_partyVivianTailStop(PartyEntry* party);

#ifdef NONMATCHING
static inline void partyPaperOn_inl(PartyEntry* party, const char* animGroup) {
    BOOL v4;
    BOOL v5;
#endif

#ifdef NONMATCHING
    if (party->paperPoseId >= 0) {
        animPaperPoseRelease(party->paperPoseId);
        party->paperPoseId = -1;
    }
    party->flags2 |= 0x4000000;
    party->paperPoseId = animPaperPoseEntry(animGroup, 2);
    v4 = FALSE;
    if (!strcmp(animGroup, (char*)str_802CCF1C) || !strcmp(animGroup, (char*)str_802CCF24) || !strcmp(animGroup, (char*)str_802CCF2C) ||
        !strcmp(animGroup, (char*)str_802CCF10)) {
        v4 = TRUE;
    }
    v5 = !v4;
    if (!strcmp(animGroup, (char*)str_802CCF38)) {
        v5 = party->currentMemberId == PARTY_MEMBER_FLURRIE;
    }
    animPoseSetPaperAnimGroup(party->paperAnimGroup, animGroup, v5);
}
#endif
#ifndef NONMATCHING
s32 partyDokanInit(PartyEntry* party);
#endif

#ifdef NONMATCHING
static inline void partyChgRunM(PartyEntry* party) {
    party->scale = (Vec){1.0f, 1.0f, 1.0f};
}
s32 partyDokanInit(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;

    party->flags2 |= 0x10;
    switch (PS8(mario, 0x3E)) {
    case 2:
    case 3:
        partyPaperOn_inl(party, (char*)str_802CCF10);
        PF32(party, 0x124) = 30.0f;
        party->field_38 = 0;
        break;
    case 0:
        *(Vec*)((u8*)party + 0x70) = (Vec){0.0f, 0.0f, 0.0f};
    case 1:
        partyPaperOn_inl(party, (char*)str_802CCF10);
        PF32(party, 0x124) = 30.0f;
        party->field_38 = 0;
        break;
    case 5:
        partyPaperOn_inl(party, (char*)str_802CCF2C);
        PF32(party, 0x124) = 26.0f;
        party->field_38 = 10;
        party->field_8C = 10.0f;
        break;
    case 4:
        partyPaperOn_inl(party, (char*)str_802CCF2C);
        PF32(party, 0x124) = -26.0f;
        party->field_38 = 10;
        party->field_8C = 10.0f;
        PF32(party, 0x64) = revise360(180.0f + mario->rot.x);
        break;
    }
    if (!(party->flags2 & 2)) {
        if (party->field_1C == 0 || strcmp((char*)party->field_1C, (char*)str_802CCF40)) {
            party->field_1C = (u32)(char*)str_802CCF40;
            party->field_20 = 0;
            party->field_8 |= 0x4000;
        }
    }
    partyChgPoseId_inl(party, 0);
    party->flags2 |= 8;
    party->flags2 |= 0x10;
    animPoseSetMaterialLightFlagOff(party->paperAnimGroup, 1);
    party->displayDirectionTarget = revise360(180.0f + mario->displayDirection);
    party->displayDirection = mario->displayDirection;
    party->moveDir = mario->moveDirection;
    party->position = mario->position;
    L_partyVivianTailStop(party);
    return 0;
}

s32 partyDokanMain(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    s32 n;

    switch (party->field_38) {
    case 0:
        party->position = *(Vec*)((u8*)mario + 0x8C);
        party->displayDirection = revise360(party->displayDirection + PF32(party, 0x124));
        party->scale.x += 0.05f;
        if (party->scale.x >= 1.0f) {
            party->scale.x = 1.0f;
        }
        party->scale.y = party->scale.x;
        party->scale.z = party->scale.x;
        break;
    case 10:
        PF32(party, 0x64) += PF32(party, 0x124);
        break;
    case 100:
        switch (PS8(party, 0x2E)) {
        case 0:
        case 1:
            partyChgPaper(party, (char*)str_802CCF08);
            party->moveFrames = 18;
            party->field_38 = 101;
            break;
        case 4:
            partyChgPaper(party, (char*)str_802CCF08);
            party->moveFrames = 18;
            party->field_38 = 101;
            break;
        }
        break;
    case 101:
        switch (PS8(party, 0x2E)) {
        case 0:
        case 1:
            party->position.z += -0.2f;
            break;
        }
        if (--party->moveFrames <= 0) {
            party->field_38 = 102;
        }
        break;
    case 102:
        party->scale = (Vec){1.0f, 1.0f, 1.0f};
        *(Vec*)((u8*)party + 0x64) = (Vec){0.0f, 0.0f, 0.0f};
        *(Vec*)((u8*)party + 0x88) = (Vec){0.0f, 0.0f, 0.0f};
        *(Vec*)((u8*)party + 0x7C) = (Vec){0.0f, 0.0f, 0.0f};
        party->displayDirectionTarget = mario->displayDirectionTarget;
        party->displayDirection = party->displayDirectionTarget;
        party->targetDir = mario->directionView;
        party->moveDir = mario->directionView;
        partyPaperOff(party);
        animPoseSetMaterialLightFlagOn(party->paperAnimGroup, 1);
        party->flags2 &= ~8;
        party->flags2 &= ~0x10;
        party->flags &= ~0x4000000;
        party->flags &= ~0x2000000;
        partyShadowOn(party);
        L_partyVivianTailStart(party);
        party->field_B8 = party->position;
        partyChgRunMode(party, 1);
        n = 0;
        if (partyGetPtr(marioGetPartyId())) {
            n = 1;
        }
        if (partyGetPtr(marioGetExtraPartyId())) {
            n++;
        }
        if ((s8)PU8(party, 0x2E) == 4) {
            if (n == 1) {
                party->position.z += -4.0f;
            } else if (!(party->flags & 8)) {
                party->position.z += -4.0f;
                party->position.x += 1.5f;
            } else {
                party->position.z += -3.0f;
                party->position.x += -1.5f;
            }
        }
        if ((s8)PU8(party, 0x2E) == 1) {
            if (n == 1) {
                party->position.z += -4.0f;
            } else if (!(party->flags & 8)) {
                party->position.z += -4.0f;
                party->position.x += 1.5f;
            } else {
                party->position.z += -3.0f;
                party->position.x += -1.5f;
            }
        }
        break;
    }
    return 0;
}
#endif
#ifndef NONMATCHING
s32 partyDokanMain(PartyEntry* party);
#endif


#ifdef NONMATCHING
void partyDokanEnd(s32 id, s32 dir) {
    PartyEntry* party = partyGetPtr(id);
    if (party && party->runMode == 10) {
        party->field_38 = 100;
        PU8(party, 0x2E) = dir;
        party->flags2 &= ~0x8;
        party->flags2 &= ~0x10;
        party->flags2 &= ~0xC0;
        party->flags &= ~0x4000000;
        party->flags &= ~0x2000000;
        partyShadowOn(party);
        party->field_B8 = party->position;
        L_partyVivianTailStart(party);
    }
}
#endif
#ifndef NONMATCHING
void partyDokanEnd(s32 id, s32 dir);
#endif


/* @@MID2@@ */

#ifdef NONMATCHING
void allPartyRidePlane(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        bomhei_use_cancel();
        party->flags |= 0x10000;
        partyChgRunMode(party, 11);
    }
    party = partyPtrTbl[1];
    if (party) {
        party->flags |= 0x10000;
        partyChgRunMode(party, 11);
    }
}
#endif
#ifndef NONMATCHING
void allPartyRidePlane(void);
#endif

#ifdef NONMATCHING
void allPartyRideShip(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        bomhei_use_cancel();
        party->flags |= 0x20000;
        partyChgRunMode(party, 11);
    }
    party = partyPtrTbl[1];
    if (party) {
        party->flags |= 0x20000;
        partyChgRunMode(party, 11);
    }
}
#endif
#ifndef NONMATCHING
void allPartyRideShip(void);
#endif


#ifdef NONMATCHING
void getRidePos(PartyEntry* party, Vec* pos) {
    MarioWork* mario = party->playerPtr;
    PartyEntry* ride;
    f32 angle;
    f32 s;
    f32 c;

    if (mario->currMotionId == 0x1A) {
        angle = 3.1415927f * toMovedir(mario->displayDirectionTarget) / 180.0f;
        if (yoshiGetStatus() != 2) {
            pos->x = mario->position.x - 10.0f * (f32)sin(angle);
            pos->z = mario->position.z - 10.0f * (f32)cos(angle);
            pos->y = 20.0f + mario->position.y;
        } else {
            pos->x = mario->position.x - 20.0f * (f32)sin(angle);
            pos->z = mario->position.z - 20.0f * (f32)cos(angle);
            pos->y = 16.0f + mario->position.y;
        }
        if (party->currentSlotId) {
            ride = partyGetPtr(marioGetPartyId());
            sincosf(&s, &c, toMovedir2(mario->displayDirectionTarget, 10.0f));
            if (yoshiGetStatus() != 2) {
                pos->x = ride->position.x - 12.0f * s;
                pos->z = ride->position.z - 12.0f * c;
                pos->y = 20.0f + ride->position.y;
            } else {
                pos->x = ride->position.x - 22.0f * s;
                pos->z = ride->position.z - 22.0f * c;
                pos->y = 16.0f + ride->position.y;
            }
        }
    } else if (mario->currMotionId == 0x18) {
        pos->x = mario->position.x;
        pos->z = mario->position.z;
        pos->y = 40.0f + mario->position.y;
    } else if (mario->currMotionId == 0x19) {
        sincosf(&s, &c, toMovedirSimple(N_marioShipGetDir() ? 0.0f : 180.0f));
        pos->x = mario->position.x + 22.0f * s;
        pos->z = mario->position.z + 22.0f * c;
        pos->y = mario->position.y;
    } else {
        pos->x = mario->position.x;
        pos->z = mario->position.z;
        pos->y = 20.0f + mario->position.y;
    }
}
#endif
#ifndef NONMATCHING
void getRidePos(PartyEntry* party, Vec* pos);
#endif


#ifdef NONMATCHING
#pragma dont_inline on
void allPartyForceRideOn(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        N_partyForceChgRunMode(party, 11, 11);
        party->flags2 |= 1;
        partyShadowOff(party);
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        N_partyForceChgRunMode(party, 11, 11);
        party->flags2 |= 1;
        partyShadowOff(party);
    }
}
#pragma dont_inline reset
#endif
#ifndef NONMATCHING
void allPartyForceRideOn(void);
#endif

#ifdef NONMATCHING
void L_allPartyRideOn(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        partyChgRunMode(party, 11);
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        partyChgRunMode(party, 11);
    }
}
#endif
#ifndef NONMATCHING
void L_allPartyRideOn(void);
#endif

#ifdef NONMATCHING
void allPartyRideOff(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party && party->runMode == 11) {
        party->field_38 = 100;
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party && party->runMode == 11) {
        party->field_38 = 100;
    }
}
#endif
#ifndef NONMATCHING
void allPartyRideOff(void);
#endif

#ifdef NONMATCHING
void allPartyRideOff2(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party && party->runMode == 11) {
        party->field_38 = 101;
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party && party->runMode == 11) {
        party->field_38 = 101;
    }
}
#endif
#ifndef NONMATCHING
void allPartyRideOff2(void);
#endif


#ifdef NONMATCHING
s32 partyRideChk(PartyEntry* party) {
    s32 ret = 0;
    if (party == NULL) {
        return 0;
    }
    if (party->runMode == 11) {
        ret = 1;
        if (party->field_38 >= 2) {
            ret = 2;
        }
    }
    return ret;
}
#endif
#ifndef NONMATCHING
s32 partyRideChk(PartyEntry* party);
#endif

/* @@MID3@@ */

f32 toMovedir(f32 a);


#ifdef NONMATCHING
void partyRideMain(PartyEntry *party)
{
  f32 new_var;
  Vec pos; f32 new_var2 ;
  Vec s;
  f32 dy0;
  u8 *mario = (u8 *) party->playerPtr; int new_var3 ;
  switch (party->field_38)
  {
    case 0:
      getRidePos(party, &pos);
      *((Vec *) (((u8 *) party) + 0x94)) = pos;
      *((f32 *) (((u8 *) party) + 0x128)) = distABf(party->position.x, party->position.z, *((f32 *) (((u8 *) party) + 0x94)), *((f32 *) (((u8 *) party) + 0x9C)));
      *((f32 *) (((u8 *) party) + 0x100)) = angleABf(party->position.x, party->position.z, *((f32 *) (((u8 *) party) + 0x94)), *((f32 *) (((u8 *) party) + 0x9C)));
      *((s32 *) (((u8 *) party) + 0x24)) = 30;
      *((f32 *) (((u8 *) party) + 0x104)) = (*((f32 *) (((u8 *) party) + 0x128))) / ((f32) (*((s32 *) (((u8 *) party) + 0x24))));
      dy0 = (*((f32 *) (((u8 *) party) + 0x98))) - party->position.y;
      *((f32 *) (((u8 *) party) + 0x11C)) = 0.4f;
      *((f32 *) (((u8 *) party) + 0x114)) = (dy0 + (0.5f * (((f32) (*((s32 *) (((u8 *) party) + 0x24)))) * ((*((f32 *) (((u8 *) party) + 0x11C))) * ((f32) (*((s32 *) (((u8 *) party) + 0x24)))))))) / ((f32) (*((s32 *) (((u8 *) party) + 0x24))));
      *((f32 *) (((u8 *) party) + 0x124)) = 1.0f;
      party->flags2 |= 0x10;
      do
    {
      char *v6;
      BOOL v5;
      s32 poseIdx = 4;
      char *v8;
      if ((party->flags2 & 2) == 0)
      {
        v5 = 0;
        if (party->currentMemberId < 8)
        {
          if (partyGetHp(party->currentMemberId) <= 5)
          {
            v5 = 1;
          }
        }
        if (v5 == 1)
        {
          if (4 == 1)
          {
            poseIdx = 12;
          }
          else
            if (4 == 2)
          {
            poseIdx = 13;
          }
          else
            if (4 == 3)
          {
            poseIdx = 14;
          }
        }
        if (!(party->flags2 & 0x8000))
        {
          v6 = partyPoseTbl[party->currentMemberId][poseIdx];
        }
        else
          if (party->currentMemberId != PARTY_MEMBER_YOSHI)
        {
          v6 = partyDotPoseTbl[party->currentMemberId][poseIdx];
        }
        else
        {
          v6 = yoshiDotPoseTbl[pouchGetPartyColor(PARTNER_YOSHI)][poseIdx];
        }
        v8 = party->animName;
        if (!(v8 && (!strcmp(v8, v6))))
        {
          party->animName = v6;
          party->field_20 = 0;
          party->field_8 |= 0x2000u;
        }
      }
    }
    while (0);
      party->field_38 = 1;
      break;

    case 1:
    {
      f32 t;
      *((f32 *) (((u8 *) party) + 0x114)) = (*((f32 *) (((u8 *) party) + 0x114))) - (*((f32 *) (((u8 *) party) + 0x11C)));
      party->position.y = party->position.y + (*((f32 *) (((u8 *) party) + 0x114)));
      movePos(&party->position.x, &party->position.z, *((f32 *) (((u8 *) party) + 0x104)), *((f32 *) (((u8 *) party) + 0x100)));
      *((f32 *) (((u8 *) party) + 0x10C)) = revise360((*((f32 *) (((u8 *) party) + 0x10C))) + (*((f32 *) (((u8 *) party) + 0x124))));
      *((f32 *) (((u8 *) party) + 0x124)) += 2.0f;
      if ((*((f32 *) (((u8 *) party) + 0x124))) >= 30.0f)
      {
        *((f32 *) (((u8 *) party) + 0x124)) = 30.0f;
      }
      t = (f32) (*((s32 *) (((u8 *) party) + 0x24)));
      if (t > 10.0f)
      {
        t = 10.0f;
      }
      party->scale.x = t / 10.0f;
      party->scale.y = party->scale.x;
      party->scale.z = party->scale.x;
      if ((--(*((s32 *) (((u8 *) party) + 0x24)))) < 0)
      {
        party->field_38 = 2;
      }
      break;
    }

    case 2:
    {
      do
      {
        char *v6;
        BOOL v5;
        s32 poseIdx = 1;
        char *v8;
        if ((party->flags2 & 2) == 0)
        {
          v5 = 0;
          if (party->currentMemberId < 8)
          {
            if (partyGetHp(party->currentMemberId) <= 5)
            {
              v5 = 1;
            }
          }
          if (v5 == 1)
          {
            if (1 == 1)
            {
              poseIdx = 12;
            }
            else
              if (1 == 2)
            {
              poseIdx = 13;
            }
            else
              if (1 == 3)
            {
              poseIdx = 14;
            }
          }
          if (!(party->flags2 & 0x8000))
          {
            v6 = partyPoseTbl[party->currentMemberId][poseIdx];
          }
          else
            if (party->currentMemberId != PARTY_MEMBER_YOSHI)
          {
            v6 = partyDotPoseTbl[party->currentMemberId][poseIdx];
          }
          else
          {
            v6 = yoshiDotPoseTbl[pouchGetPartyColor(PARTNER_YOSHI)][poseIdx];
          }
          v8 = party->animName;
          if (!(v8 && (!strcmp(v8, v6))))
          {
            party->animName = v6;
            party->field_20 = 0;
            party->field_8 |= 0x2000u;
          }
        }
      }
      while (0);
      *((f32 *) (((u8 *) party) + 0x114)) = 0.0f;
      party->position.y = *((f32 *) (((u8 *) party) + 0x98));
      party->scale = (Vec){0.0f, 0.0f, 0.0f};
      party->flags2 |= 1;
      partyShadowOff(party);
      party->field_38 = 10;
      break;
    }

    case 10:
      party->position = *((Vec *) (mario + 0x8C));
      *((f32 *) (((u8 *) party) + 0x110)) = *((f32 *) (((u8 *) mario) + 0x1AC));
      *((f32 *) (((u8 *) party) + 0xFC)) = toMovedir(*((f32 *) (((u8 *) party) + 0x110)));
      break;

    case 11:
    {
      do
      {
        char *v6;
        BOOL v5;
        s32 poseIdx = 1;
        char *v8;
        if ((party->flags2 & 2) == 0)
        {
          v5 = 0;
          if (party->currentMemberId < 8)
          {
            if (partyGetHp(party->currentMemberId) <= 5)
            {
              v5 = 1;
            }
          }
          if (v5 == 1)
          {
            if (1 == 1)
            {
              poseIdx = 12;
            }
            else
              if (1 == 2)
            {
              poseIdx = 13;
            }
            else
              if (1 == 3)
            {
              poseIdx = 14;
            }
          }
          if (!(party->flags2 & 0x8000))
          {
            v6 = partyPoseTbl[party->currentMemberId][poseIdx];
          }
          else
            if (party->currentMemberId != PARTY_MEMBER_YOSHI)
          {
            v6 = partyDotPoseTbl[party->currentMemberId][poseIdx];
          }
          else
          {
            v6 = yoshiDotPoseTbl[pouchGetPartyColor(PARTNER_YOSHI)][poseIdx];
          }
          v8 = party->animName;
          if (!(v8 && (!strcmp(v8, v6))))
          {
            party->animName = v6;
            party->field_20 = 0;
            party->field_8 |= 0x2000u;
          }
        }
      }
      while (0);
      party->flags2 |= 1;
      partyShadowOff(party);
      getRidePos(party, &pos);
      party->scale = (Vec){0.0f, 0.0f, 0.0f};
      party->position = pos;
      *((f32 *) (((u8 *) party) + 0x114)) = 0.0f;
      *((f32 *) (((u8 *) party) + 0x110)) = *((f32 *) (((u8 *) ((u8 *) party->playerPtr)) + 0x1AC));
      *((f32 *) (((u8 *) party) + 0xFC)) = toMovedir(*((f32 *) (((u8 *) party) + 0x110)));
      break;
    }

    case 20:
      party->field_38 = 21;
      *((s32 *) (((u8 *) party) + 0x24)) = 16;
      *((f32 *) (((u8 *) party) + 0x114)) = 16.0f;
      *((f32 *) (((u8 *) party) + 0x174)) = 0.5f;

    case 21:
      party->position.y = party->position.y + (*((f32 *) (((u8 *) party) + 0x114)));
      *((f32 *) (((u8 *) party) + 0x114)) = (*((f32 *) (((u8 *) party) + 0x114))) + (*((f32 *) (((u8 *) party) + 0x174)));
      if ((--(*((s32 *) (((u8 *) party) + 0x24)))) > 0)
    {
      break;
    }
      party->field_38 = 22;
      party->flags |= 0x2000000;
      break;

    case 22:
      break;

    case 200:
      party->flags &= ~0x70000;
      *((f32 *) (((u8 *) party) + 0x80)) = 0.0f;
      party->scale.x = 1.0f;
      party->scale.y = party->scale.x;
      party->scale.z = party->scale.x;
      partyShadowOn(party);
      partyChgRunMode(party, 1);
      break;

    case 100:

    case 101:
    {
      f32 x;
      f32 z;
      f32 h;
      f32 dy;
      party->flags2 &= ~1;
      x = *((f32 *) (((u8 *) mario) + 0x8C));
      z = *((f32 *) (((u8 *) mario) + 0x94));
      new_var = *((f32 *) (((u8 *) mario) + 0x90));
      party->position.x = x;
      party->position.y = new_var + (0.5f * (*((f32 *) (((u8 *) mario) + 0x1B8))));
      party->position.z = z;
      if (party->field_38 == 100)
      {
        partyGetAppearPos(party, (Vec *) (((u8 *) party) + 0x94));
      }
      else
      {
        partyGetAppearPos2(party, (Vec *) (((u8 *) party) + 0x94));
      }
      *((f32 *) (((u8 *) party) + 0x110)) = *((f32 *) (((u8 *) mario) + 0x1AC));
      *((s32 *) (((u8 *) party) + 0x24)) = 16;
      new_var3 = 0xF0;
      *((f32 *) (((u8 *) party) + 0x128)) = distABf(x, z, *((f32 *) (((u8 *) party) + 0x94)), *((f32 *) (((u8 *) party) + 0x9C)));
      *((f32 *) (((u8 *) party) + 0x100)) = angleABf(x, z, *((f32 *) (((u8 *) party) + 0x94)), *((f32 *) (((u8 *) party) + 0x9C)));
      *((f32 *) (((u8 *) party) + 0x104)) = (*((f32 *) (((u8 *) party) + 0x128))) / ((f32) (*((s32 *) (((u8 *) party) + 0x24))));
      h = 0.5f * ((f32) (*((s32 *) (((u8 *) party) + 0x24))));
      dy = (*((f32 *) (((u8 *) party) + 0x98))) - party->position.y;
      if (__fabsf(dy) < 1.0f)
      {
        dy = 10.0f;
      }
      else
        if (dy >= 0.0f)
      {
        dy = (0.5f * (*((f32 *) (((u8 *) party) + new_var3)))) + dy;
      }
      else
      {
        dy = 10.0f;
      }
      dy = (dy + dy) / ((h * h) - h);
      *((f32 *) (((u8 *) party) + 0x114)) = dy * h;
      *((f32 *) (((u8 *) party) + 0x118)) = -dy;
      party->flags |= 0x10;
      party->flags2 &= ~1;
      partyShadowOn(party);
      party->field_38 = 110;
      break;
    }

    case 110:
      partyMoveNoHosei(party);
      if ((*((f32 *) (((u8 *) party) + 0x114))) <= 0.0f)
    {
      party->flags &= ~0x10;
      *((f32 *) (((u8 *) party) + 0x118)) = -1.6f;
    }
      if (party->position.y < (-2000.0f))
    {
      *((s32 *) (((u8 *) party) + 0x24)) = 0;
      party->field_38 = 111;
      break;
    }
      if ((*((u32 *) (((u8 *) party) + 0x138))) == 0)
    {
      s = (Vec){0.0f, 0.0f, 0.0f};
      s.x = (s.y = (s.z = ((f32) (16 - (*((s32 *) (((u8 *) party) + 0x24))))) * 0.0625f));
      party->scale = s;
      if ((--(*((s32 *) (((u8 *) party) + 0x24)))) <= 0)
      {
        *((s32 *) (((u8 *) party) + 0x24)) = 0;
      }
      break;
    }
      party->field_38 = 111;

    case 111:
    new_var2 = (f32) (16 - (* ((s32 *) (((u8 *) party) + 0x24)))); {
      s = (Vec){0.0f, 0.0f, 0.0f};
      s.x = (s.y = (s.z = new_var2 * 0.0625f));
      party->scale = s;
      if ((--(*((s32 *) (((u8 *) party) + 0x24)))) > 0)
      {
        break;
      }
      *((s32 *) (((u8 *) party) + 0x24)) = 0;
      *((f32 *) (((u8 *) party) + 0x110)) = *((f32 *) (((u8 *) mario) + 0x1AC));
      *((f32 *) (((u8 *) party) + 0x10C)) = *((f32 *) (((u8 *) mario) + 0x1AC));
      *((f32 *) (((u8 *) party) + 0xFC)) = toMovedirSimple(*((f32 *) (((u8 *) party) + 0x10C)));
      *((f32 *) (((u8 *) party) + 0x100)) = *((f32 *) (((u8 *) party) + 0xFC));
      partyClearJumpPara(party);
      partyChgPoseId_inl(party, 1);
      party->flags2 &= ~0x10;
      party->flags &= ~0x70000;
      *((f32 *) (((u8 *) party) + 0x80)) = 0.0f;
      party->scale.x = 1.0f;
      party->scale.y = party->scale.x;
      party->scale.z = party->scale.x;
      party->flags2 &= ~1;
      partyShadowOn(party);
      partyChgRunMode(party, 1);
      break;
    }

  }

  party->field_B8 = party->position;
}
static inline void partyChgRunMo(PartyEntry* party) {
    party->scale = (Vec){1.0f, 1.0f, 1.0f};
    *(Vec*)((u8*)party + 0x7C) = (Vec){0.0f, 0.0f, 0.0f};
}
#endif
#ifndef NONMATCHING
void partyRideMain(PartyEntry *party);
#endif


#ifdef NONMATCHING
void party_force_ride_yoshi(PartyEntry* party) {
    Vec pos;

    N_partyForceChgRunMode(party, 12, 10);
    party->flags &= ~0x100;
    getRidePos(party, &pos);
    party->position = pos;
    partyChgPoseId(party, 1);
    party->velY = 0.0f;
    partyShadowOff(party);
    party->displayDirectionTarget = party->playerPtr->displayDirectionTarget;
    party->moveDir = toMovedir(party->displayDirectionTarget);
}
#endif
#ifndef NONMATCHING
void party_force_ride_yoshi(PartyEntry* party);
#endif


#ifdef NONMATCHING
void party_ride_yoshi_force_move(void) {
    Vec pos;
    PartyEntry* party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        getRidePos(party, &pos);
        party->position = pos;
        party->displayDirectionTarget = party->playerPtr->displayDirectionTarget;
        party->moveDir = toMovedir(party->displayDirectionTarget);
    }
}
#endif
#ifndef NONMATCHING
void party_ride_yoshi_force_move(void);
#endif

void partyGetAppearPos(PartyEntry* party, Vec* pos);

#ifdef NONMATCHING
s32 partyRideYoshiMain(PartyEntry* party) {
    Vec pos;
    Vec pos2;
    MarioWork* mario = party->playerPtr;

    switch (party->field_38) {
    case 0:
        party->gravity = 1.6f;
        getRidePos(party, &pos);
        *(Vec*)((u8*)party + 0x94) = pos;
        party->moveDistance = distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
        party->targetDir = angleABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
        party->moveFrames = 15;
        party->moveSpeed = party->moveDistance / (f32)party->moveFrames;
        party->velY = (0.5f * ((f32)party->moveFrames * (party->gravity * (f32)party->moveFrames)) + (party->moveTarget.y - party->position.y)) / (f32)party->moveFrames;
        partyChgPoseId_inl(party, 4);
        party->field_38 = 1;
        break;
    case 1:
        getRidePos(party, &pos);
        *(Vec*)((u8*)party + 0x94) = pos;
        party->moveDistance = distABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
        party->targetDir = angleABf(party->position.x, party->position.z, party->moveTarget.x, party->moveTarget.z);
        party->moveSpeed = party->moveDistance / (f32)party->moveFrames;
        party->velY -= party->gravity;
        party->position.y += party->velY;
        movePos(&party->position.x, &party->position.z, party->moveSpeed, party->targetDir);
        if (--party->moveFrames <= 0) {
            party->field_38 = 2;
        }
        break;
    case 2:
        partyChgPoseId_inl(party, 1);
        party->velY = 0.0f;
        party->position.y = party->moveTarget.y;
        party->field_38 = 10;
        if (party) {
            party->flags2 |= 0x100000;
        }
        break;
    case 10:
        getRidePos(party, &pos);
        party->position = pos;
        party->displayDirectionTarget = mario->displayDirectionTarget;
        party->moveDir = toMovedir(party->displayDirectionTarget);
        if (*(u16*)((u8*)mario + 0x2E) != 0x1A) {
            partyGetAppearPos(party, &pos2);
            party->position.x = pos2.x;
            party->position.z = pos2.z;
            partyChgRunMode(party, 2);
            if (party) {
                party->flags2 &= ~0x100000;
            }
            *(Vec*)((u8*)party + 0x7C) = (Vec){0.0f, 0.0f, 0.0f};
        }
        break;
    }
    return 0;
}
#endif
#ifndef NONMATCHING
s32 partyRideYoshiMain(PartyEntry* party);
#endif


void marioGetScreenPos(Vec position, f32* x, f32* y, f32* z);
s32 hitGetAttr(struct HitEntry* hit);
s32 sysMsec2Frame(s32 msec);
BOOL marioWaitDamageReturnFall(void);
BOOL marioWaitDamageTogeReturnFall(void);
void vivianShadow(PartyEntry* party);
void partyMove(PartyEntry* party);

#ifdef NONMATCHING
void party_damage_return(PartyEntry* party) {
    MarioWork* mario = party->playerPtr;
    f32 x, y, z;
    f32 mx, my, mz;
    f32 lim;
    Vec pos;

    if (party->field_8 & 8) {
        party->field_8 &= ~8;
        party->flags &= ~0x100;
        if (!(party->field_8 & 0x1000000)) {
            party->field_38 = 10;
        } else {
            party->field_38 = 0;
            party->moveFrames = 100;
        }
    }
    switch (party->field_38) {
    case 0:
        if (--party->moveFrames > 0) {
            break;
        }
        party->field_38 = 10;
    case 10:
        partyChgPoseId_inl(party, 8);
        party->moveFrames = sysMsec2Frame(200);
        party->field_38 = 11;
    case 11:
        if (--party->moveFrames > 0) {
            break;
        }
        party->velY = 15.0f;
        party->accelY = 0.0f;
        party->field_38 = 12;
    case 12:
        party->position.y += party->velY;
        marioGetScreenPos(party->position, &x, &y, &z);
        marioGetScreenPos(mario->position, &mx, &my, &mz);
        lim = (my < -100.0f) ? my : -100.0f;
        if (y <= lim) {
            party->moveFrames = 32;
            party->field_38 = 20;
        }
        break;
    case 20:
        marioGetScreenPos(party->position, &x, &y, &z);
        if (y <= -100.0f) {
            party->position.y += 1.0f;
        }
        if (mario->currMotionId == 0x1F) {
            if (!marioWaitDamageReturnFall()) {
                break;
            }
        } else if (mario->currMotionId == 0x20) {
            if (!marioWaitDamageTogeReturnFall()) {
                break;
            }
        }
        party->field_38 = 21;
    case 21:
        if (--party->moveFrames > 0) {
            break;
        }
        partyGetAppearPos(party, &pos);
        party->position.x = pos.x;
        party->position.z = pos.z;
        party->velY = 0.0f;
        party->accelY = -1.0f;
        party->moveSpeed = 0.0f;
        party->flags |= 0x20;
        party->flags |= 0x2000000;
        party->field_38 = 22;
        break;
    case 22:
        marioGetScreenPos(party->position, &x, &y, &z);
        if (y > 240.0f) {
            party->flags &= ~0x2000000;
        }
        partyMove(party);
        if (party->velY <= -6.0f) {
            party->accelY = 0.0f;
            party->velY = -6.0f;
        }
        if (party->position.y < -2000.0f) {
            party->position = mario->position;
            party->position.y += 200.0f;
            party->flags &= ~0x70;
        }
        if (*(struct HitEntry**)((u8*)party + 0x138) && !((hitGetAttr(*(struct HitEntry**)((u8*)party + 0x138)) >> 9) & 1)) {
            partyChgPoseId_inl(party, 9);
            party->field_38 = 23;
            party->moveFrames = 30;
        }
        break;
    case 23:
        if (--party->moveFrames > 0) {
            break;
        }
        partyChgRunMode(party, 2);
        PU8(party, 0x3B) = 0;
        party->flags2 &= ~0x10;
        break;
    }
    if (vivianGetStatus() != 2) {
        vivianShadow(party);
    }
}
#endif
#ifndef NONMATCHING
__declspec(section ".data") static void* jumptable_803126C0[] = {
    (char*)party_damage_return + 0x8C,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0xA4,
    (char*)party_damage_return + 0x17C,
    (char*)party_damage_return + 0x1A4,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x508,
    (char*)party_damage_return + 0x248,
    (char*)party_damage_return + 0x2D0,
    (char*)party_damage_return + 0x334,
    (char*)party_damage_return + 0x4D8,
};
__declspec(section ".data") void* jumptable_80312720[] = {
    (char*)partyGoodbyeMain + 0x78,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x110,
    (char*)partyGoodbyeMain + 0x2F0,
    (char*)partyGoodbyeMain + 0x3A4,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4CC,
    (char*)partyGoodbyeMain + 0x4B8,
};
__declspec(section ".data") void* jumptable_80312774[] = {
    (char*)partyHelloMain + 0x5C,
    (char*)partyHelloMain + 0x18C,
    (char*)partyHelloMain + 0x284,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x4A8,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x5C8,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6D0,
    (char*)partyHelloMain + 0x6C8,
};
__declspec(section ".data") void* jumptable_803127F0[] = {
    (char*)driveParty + 0xF8,
    (char*)driveParty + 0x260,
    (char*)driveParty + 0x280,
    (char*)driveParty + 0x2E4,
    (char*)driveParty + 0x334,
    (char*)driveParty + 0x334,
    (char*)driveParty + 0x334,
    (char*)driveParty + 0x334,
    (char*)driveParty + 0x4AC,
    (char*)driveParty + 0x2C4,
    (char*)driveParty + 0x4DC,
    (char*)driveParty + 0x510,
    (char*)driveParty + 0x560,
    (char*)driveParty + 0x5A8,
    (char*)driveParty + 0x5C8,
};
void party_damage_return(PartyEntry* party);
#endif


#ifdef NONMATCHING
void partyInitCamId(PartyEntry* party) {
    party->camId = marioGetCamId();
}
#endif
#ifndef NONMATCHING
void partyInitCamId(PartyEntry* party);
#endif

/*
//.data
typedef struct PartyData {
        char* name; //0, TODO: modelname? animname?
        void* init_func; //1
        void* move_func; //2
        void* use_func; //3
        void* post_func; //4
        void* bye_func; //5
        void* unk_6_func; //6
        void* unk_7_func; //7
        void* unk_8_func; //8
        void* exit_func; //9
} PartyData;

PartyData partyDataTbl[] = { //change to [20]
        {"c_pkr", kuribo_init, partyMoveWalk, kuribo_use, kuribo_use_post, kuribo_bye, NULL, NULL, NULL, NULL},
        {"c_pnk", nokonoko_init, nokonoko_move, nokonoko_use, nokonoko_use_post, nokonoko_bye, NULL, NULL, NULL, NULL},
        {"c_bomt_n", bomhei_init, partyMoveWalk, bomhei_use, bomhei_use_post, bomhei_bye, NULL, NULL, NULL,
bomhei_exit},
        {(char*)str_802CCD60, yoshi_init, partyMoveWalk, yoshi_use, NULL, yoshi_bye, NULL, NULL, NULL, yoshi_exit},
        {"c_windy", cloud_init, cloud_move, cloud_use, NULL, kuribo_bye, NULL, NULL, NULL, cloud_exit},
        {"c_vivian", vivian_init, vivian_move, vivian_use, NULL, kuribo_bye, NULL, NULL, NULL, NULL},
        {"c_tyutyu", chuchu_init, chuchu_move, chuchu_use, NULL, kuribo_bye, NULL, NULL, NULL, chuchu_exit},
        {(char*)str_802CCD60, kuribo_init, partyMoveWalk, kuribo_use, NULL, kuribo_bye, NULL, NULL, NULL, NULL},
        {"c_marco", kuribo_init, partyMoveWalk, kuribo_use, NULL, kuribo_bye, NULL, NULL, NULL, NULL},
        {"c_pguide", kuribo_init, partyMoveWalk, kuribo_use, NULL, kuribo_bye, NULL, NULL, NULL, NULL},
        {"c_kuri_h", kuribo_init, partyMoveWalk, kuribo_use, NULL, kuribo_bye, NULL, NULL, NULL, NULL},
        {"c_monban", kuribo_init, partyMoveWalk, kuribo_use, NULL, kuribo_bye, NULL, NULL, NULL, NULL},
        {"c_pkr", kuribo_init, partyMoveWalk, kuribo_use, NULL, kuribo_bye, NULL, NULL, NULL, NULL},
        {"c_pnk", nokonoko_init, nokonoko_move, nokonoko_use, NULL, nokonoko_bye, NULL, NULL, NULL, NULL},
        {"c_bomt_n", bomhei_init, partyMoveWalk, bomhei_use, bomhei_use_post, bomhei_bye, NULL, NULL, NULL, NULL},
        {(char*)str_802CCD60, yoshi_init, partyMoveWalk, yoshi_use, NULL, yoshi_bye, NULL, NULL, NULL, NULL},
        {"c_windy", cloud_init, cloud_move, cloud_use, NULL, kuribo_bye, NULL, NULL, NULL, cloud_exit},
        {"c_vivian", vivian_init, vivian_move, vivian_use, NULL, kuribo_bye, NULL, NULL, NULL, NULL},
        {"c_tyutyu", chuchu_init, partyMoveWalk, chuchu_use, NULL, kuribo_bye, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
};

char* partyPoseTbl[20][15] = {
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {"PKR_Z_1", "PKR_S_1", "PKR_W_1", "PKR_R_1", "PKR_J_1A", "PKR_J_1B", "PKR_N_1", "PKR_T_1", "PKR_D_1", "PKR_D_4",
"PKR_S_1", "PKR_S_1", "PKR_D_2", "PKR_W_2", "PKR_R_2"},
        {"PNK_Z_1", "PNK_S_1", "PNK_W_1", "PNK_R_1", "PNK_J_1A", "PNK_J_1B", "PNK_N_1", "PNK_T_1", "PNK_D_1", "PNK_D_4",
"PNK_S_1", "PNK_S_1", "PNK_D_2", "PNK_W_2", "PNK_R_2"},
        {"Z_1", "S_1", "W_1", "R_1", "J_1A", "J_1B", "N_1", "T_1", "D_1", "F_1", "S_1", "S_1", "D_2", "W_3", "R_3"},
        {"PYS_Z_1", "PYS_S_1", "PYS_W_1", "PYS_R_1", "PYS_J_1A", "PYS_J_1B", "PYS_N_1", "PYS_T_1", "PYS_D_1", "PYS_D_4",
"PYS_S_1", "PYS_S_1", "PYS_D_2", "PYS_W_3", "PYS_R_3"},
        {"PWD_Z_1", "PWD_S_1", "PWD_W_1", "PWD_R_1", "PWD_S_1", "PWD_S_1", "PWD_N_1", "PWD_T_1", "PWD_D_1", "PWD_F_1",
"PWD_S_1", "PWD_S_1", "PWD_D_2", "PWD_W_2", "PWD_R_2"},
        {"PTR_Z_1", "PTR_S_1", "PTR_W_1", "PTR_R_1", "PTR_S_1", "PTR_S_1", "PTR_N_1", "PTR_T_1", "PTR_D_1", "PTR_F_1",
"PTR_Z_1", "PTR_Z_1", "PTR_D_2", "PTR_W_2", "PTR_R_2"},
        {"PCH_Z_1", "PCH_S_1", "PCH_W_1", "PCH_R_1", "PCH_J_1A", "PCH_J_1B", "PCH_N_1", "PCH_T_1", "PCH_D_1", "PCH_F_1",
"PCH_S_1", "PCH_S_1", "PCH_D_2", "PCH_R_2", "PCH_W_2"},
        {"PYS_E_1", "PYS_E_2", "PYS_E_3", "PYS_E_3", "PYS_E_2", "PYS_E_2", "PYS_E_2", "PYS_E_2", "PYS_E_2", "PYS_E_2",
"PYS_E_2", "PYS_E_2", "PYS_E_2", "PYS_E_3", "PYS_E_3"},
        {"Z_1", "S_1", "W_1", "R_1", "J_1A", "J_1B", "S_1", "T_1", "D_1", "D_1", "Z_1", "Z_1", "S_1", "W_1", "R_1"},
        {"Z_1", "S_1", "W_1", "R_1", "J_1A", "J_1B", "S_1", "T_1", "Z_1", "Z_1", "S_1", "Z_1", "Z_1", "W_1", "R_1"},
        {"Z_1", "S_1", "W_1", "R_1", "W_1", "W_1", "S_1", "T_1", "Z_1", "Z_1", "S_1", "Z_1", "Z_1", "W_1", "R_1"},
        {"Z_1", "S_1", "W_1", "R_1", "S_1", "S_1", "S_1", "T_1", "S_1", "S_1", "S_1", "S_1", "S_1", "W_1", "R_1"},
        {"PKR_Z_1", "PKR_S_1", "PKR_W_1", "PKR_R_1", "PKR_J_1A", "PKR_J_1B", "PKR_N_1", "PKR_T_1", "PKR_D_1", "PKR_D_4",
"PKR_S_1", "PKR_S_1", "PKR_D_2", "PKR_W_2", "PKR_R_2"},
        {"PNK_Z_1", "PNK_S_1", "PNK_W_1", "PNK_R_1", "PNK_J_1A", "PNK_J_1B", "PNK_N_1", "PNK_T_1", "PNK_D_1", "PNK_D_4",
"PNK_S_1", "PNK_S_1", "PNK_D_2", "PNK_W_2", "PNK_R_2"},
        {"Z_1", "S_1", "W_1", "R_1", "J_1A", "J_1B", "N_1", "T_1", "D_1", "F_1", "S_1", "S_1", "D_2", "W_3", "R_3"},
        {"PYS_Z_1", "PYS_S_1", "PYS_W_1", "PYS_R_1", "PYS_J_1A", "PYS_J_1B", "PYS_N_1", "PYS_T_1", "PYS_D_1", "PYS_D_4",
"PYS_S_1", "PYS_S_1", "PYS_D_2", "PYS_W_2", "PYS_R_2"},
        {"PWD_Z_1", "PWD_S_1", "PWD_W_1", "PWD_R_1", "PWD_S_1", "PWD_S_1", "PWD_N_1", "PWD_T_1", "PWD_D_1", "PWD_F_1",
"PWD_S_1", "PWD_S_1", "PWD_D_2", "PWD_W_2", "PWD_R_2"},
        {"PTR_Z_1", "PTR_S_1", "PTR_W_1", "PTR_R_1", "PTR_S_1", "PTR_S_1", "PTR_N_1", "PTR_T_1", "PTR_D_1", "PTR_F_1",
"PTR_Z_1", "PTR_Z_1", "PTR_D_2", "PTR_W_2", "PTR_R_2"},
        {"PCH_Z_1", "PCH_S_1", "PCH_W_1", "PCH_R_1", "PCH_J_1A", "PCH_J_1B", "PCH_N_1", "PCH_T_1", "PCH_D_1", "PCH_F_1",
"PCH_S_1", "PCH_S_1", "PCH_D_2", "PCH_R_2", "PCH_W_2"}
};

char* partyDotPoseTbl[8][15] = {
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {"Z_2", "Z_2", "W_2", "R_2", "Z_2", "Z_2", "Z_2", "Z_2", "Z_2", "Z_2", "Z_2", "Z_2", "Z_2", "W_2", "R_2"},
        {"Z_3", "Z_3", "W_3", "R_3", "Z_3", "Z_3", "Z_3", "Z_3", "Z_3", "Z_3", "Z_3", "Z_3", "Z_3", "W_3", "R_3"},
        {"Z_13", "Z_13", "W_13", "R_13", "Z_13", "Z_13", "Z_13", "Z_13", "Z_13", "Z_13", "Z_13", "Z_13", "Z_13", "W_13",
"R_13"},
        {"Z_5", "Z_5", "W_5", "R_5", "Z_5", "Z_5", "Z_5", "Z_5", "Z_5", "Z_5", "Z_5", "Z_5", "Z_5", "W_5", "R_5"},
        {"Z_4", "Z_4", "W_4", "R_4", "Z_4", "Z_4", "Z_4", "Z_4", "Z_4", "Z_4", "Z_4", "Z_4", "Z_4", "W_4", "R_4"},
        {"Z_12", "Z_12", "W_12", "R_12", "Z_12", "Z_12", "Z_12", "Z_12", "Z_12", "Z_12", "Z_12", "Z_12", "Z_12", "W_12",
"R_12"},
        {"Z_14", "Z_14", "W_14", "R_14", "Z_14", "Z_14", "Z_14", "Z_14", "Z_14", "Z_14", "Z_14", "Z_14", "Z_14", "W_14",
"R_14"}
};

char* yoshiDotPoseTbl[7][15] = {
        {"Z_5", "Z_5", "W_5", "R_5", "Z_5", "Z_5", "Z_5", "Z_5", "Z_5", "Z_5", "Z_5", "Z_5", "Z_5", "W_5", "R_5"},
        {"Z_6", "Z_6", "W_6", "R_6", "Z_6", "Z_6", "Z_6", "Z_6", "Z_6", "Z_6", "Z_6", "Z_6", "Z_6", "W_6", "R_6"},
        {"Z_7", "Z_7", "W_7", "R_7", "Z_7", "Z_7", "Z_7", "Z_7", "Z_7", "Z_7", "Z_7", "Z_7", "Z_7", "W_7", "R_7"},
        {"Z_8", "Z_8", "W_8", "R_8", "Z_8", "Z_8", "Z_8", "Z_8", "Z_8", "Z_8", "Z_8", "Z_8", "Z_8", "W_8", "R_8"},
        {"Z_9", "Z_9", "W_9", "R_9", "Z_9", "Z_9", "Z_9", "Z_9", "Z_9", "Z_9", "Z_9", "Z_9", "Z_9", "W_9", "R_9"},
        {"Z_10", "Z_10", "W_10", "R_10", "Z_10", "Z_10", "Z_10", "Z_10", "Z_10", "Z_10", "Z_10", "Z_10", "Z_10", "W_10",
"R_10"},
        {"Z_11", "Z_11", "W_11", "R_11", "Z_11", "Z_11", "Z_11", "Z_11", "Z_11", "Z_11", "Z_11", "Z_11", "Z_11", "W_11",
"R_11"}
};

//.sbss
PartyEntry* partyPtrTbl[2];
PartyData* party_dp;
s32 partyCtrlNo;

void partyChgRunMode(PartyEntry* party, s32 mode);
void partyChgMot(PartyEntry* party, s32 mot);
s32 partyEntryMain(s32 memberId);
void partyGetAppearPos2(PartyEntry* party, Vec* pos);

//.sdata

PartyEntry* partyGetPtr(s32 id) {
        if (id >= 0) {
                return partyPtrTbl[id];
        }
        return NULL;
}

PartyEntry* anotherPartyGetPtr(s32 id) {
        if (id < 0) {
                return NULL;
        }
        else {
                return partyPtrTbl[(id + 1) & 1];
        }
}

BOOL partyPaperOn(PartyEntry* entry, char* anim) {
    BOOL v4 = FALSE;
    BOOL v5;
    if (entry->paperPoseId >= 0) {
        animPaperPoseRelease(entry->paperPoseId);
        entry->paperPoseId = -1;
    }
    entry->flags2 |= 0x4000000;
    entry->paperPoseId = animPaperPoseEntry(anim, 2);
    if (!strcmp(anim, (char*)str_802CCF1C) || !strcmp(anim, (char*)str_802CCF24) || !strcmp(anim, (char*)str_802CCF2C) ||
        !strcmp(anim, (char*)str_802CCF10)) {
        v4 = TRUE;
    }
    v5 = !v4;
    if (!strcmp(anim, (char*)str_802CCF38)) {
        v5 = entry->currentMemberId == PARTY_MEMBER_FLURRIE;
    }
    animPoseSetPaperAnimGroup(entry->paperAnimGroup, anim, v5);
    return TRUE;
}







s32 partyEntry2(s32 memberId) {
        PartyEntry* entry;
        MarioWork* player;
        char* animName;
        s32 slotId;

        player = marioGetPtr();
        if (partyPtrTbl[1]) {
                slotId = -1;
        }
        else {
                partyPtrTbl[1] = (PartyEntry*)__memAlloc(HEAP_DEFAULT, sizeof(PartyEntry));
                memset(partyPtrTbl[1], 0, sizeof(PartyEntry));
                slotId = 1;
        }
        if (slotId < 0) {
                return -1;
        }
        entry = partyPtrTbl[slotId];
        memset(entry, 0, sizeof(PartyEntry));
        entry->camId = marioGetCamId();
        entry->field_0xC = -1;
        entry->talkTarget = -1;
        entry->field_0x14 = -1;
        entry->flags = 9;
        entry->currentSlotId = (s8)slotId; //TODO: re-type?
        entry->currentMemberId = (PartyMember)memberId;
        entry->flags |= 4;
        party_dp = &partyDataTbl[memberId];
        if (entry->currentMemberId == PARTY_MEMBER_YOSHI) {
                animName = yoshigroup[pouchGetPartyColor(PARTNER_YOSHI)];
                if ((entry->flags2 & 0x8000)) {
                        animName = (char*)str_802CCEEC;
                }
        } else if ((entry->flags2 & 0x8000)) {
                animName = (char*)str_802CCEEC;
        }
        else {
                animName = partyDataTbl[memberId].name;
        }
        if (entry->field_0xC >= 0) {
                animPoseRelease(entry->field_0xC);
        }
        entry->field_0xC = animPoseEntry(animName, 2);






        return -1;
}
*/

#ifdef NONMATCHING
void partySetCamId(PartyEntry* party, s32 cameraId) {
    party->camId = cameraId;
}
#endif
#ifndef NONMATCHING
void partySetCamId(PartyEntry* party, s32 cameraId);
#endif

/* @@DISP@@ */
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#define PS16(p, o) (*(s16*)((u8*)(p) + (o)))
s32 shadowEntryMode(s32 mode, f32 x, f32 y, f32 z, f32 size);
void shadowSetCamId(s32 id, s32 camId);
void shadowFlagOn(s32 id, u32 flag);
BOOL N_vivianDisplayTailCheck(PartyEntry* party);
void animPoseVivianMain(s32 poseId, Vec* pos);
struct HitEntry* partyHitCheck(PartyEntry* party, Vec* pos, Vec* dir, Vec* outPos, Vec* outNrm, f32* dist);
void partyDisp(CameraId cam, void* param);

#ifdef NONMATCHING
void partyMakeDispDir(PartyEntry* party) {
    f32 diff;
    f32 tgt;
    f32 cur;
    f32 step;
#endif
#ifndef NONMATCHING
void partyMakeDispDir(PartyEntry* party);
#endif

#ifdef NONMATCHING
    if (party->flags2 & 0x100) {
        return;
    }
    if (!(party->flags2 & 0x10)) {
        diff = revise360(party->moveDir - PF32(party, 0xF8));
        tgt = party->displayDirectionTarget;
        if (!(party->flags2 & 0x100)) {
            if (290.0f == tgt || 250.0f == tgt) {
                tgt = 180.0f;
                if (diff >= tgt) {
                    tgt = 0.0f;
                }
            }
        }
        if (party->moveSpeed) {
            if (diff >= 190.0f && diff <= 350.0f) {
                tgt = 0.0f;
            } else if (diff >= 10.0f && diff <= 170.0f) {
                tgt = 180.0f;
            }
        }
        party->displayDirectionTarget = tgt;
        if (party->flags2 & 0x20) {
            party->displayDirection = party->displayDirectionTarget;
        }
        if (party->displayDirection == party->displayDirectionTarget) {
            return;
        }
    }
    if ((cur = party->displayDirection) <= 180.0f) {
        if (0.0f == party->displayDirectionTarget) {
            step = 0.125f * (((party->field_8 & 0x1000) ? 20.0f : -40.0f) - party->displayDirection);
            party->displayDirection += step;
            if (!(party->field_8 & 0x1000)) {
                if (party->displayDirection < -30.0f) {
                    party->field_8 |= 0x1000;
                }
            } else if (party->displayDirection >= 0.0f) {
                party->displayDirection = 0.0f;
                party->field_8 &= ~0x1000;
            }
        } else if (180.0f == party->displayDirectionTarget) {
            step = 0.125f * (((party->field_8 & 0x1000) ? 170.0f : 220.0f) - party->displayDirection);
            party->displayDirection += step;
            if (!(party->field_8 & 0x1000)) {
                if (party->displayDirection > 210.0f) {
                    party->field_8 |= 0x1000;
                }
            } else if (party->displayDirection <= 180.0f) {
                party->displayDirection = 180.0f;
                party->field_8 &= ~0x1000;
            }
        }
    } else if (cur > 180.0f) {
        if (0.0f == party->displayDirectionTarget) {
            step = 0.125f * (((party->field_8 & 0x1000) ? 20.0f : -40.0f) - party->displayDirection);
            party->displayDirection += step;
            if (!(party->field_8 & 0x1000)) {
                if (party->displayDirection < -30.0f) {
                    party->field_8 |= 0x1000;
                }
            } else if (party->displayDirection >= 0.0f) {
                party->displayDirection = 0.0f;
                party->field_8 &= ~0x1000;
            }
        } else if (180.0f == party->displayDirectionTarget) {
            step = 0.125f * (((party->field_8 & 0x1000) ? 170.0f : 220.0f) - party->displayDirection);
            party->displayDirection += step;
            if (!(party->field_8 & 0x1000)) {
                if (party->displayDirection > 210.0f) {
                    party->field_8 |= 0x1000;
                } else if (party->displayDirection <= 180.0f) {
                    party->displayDirection = 180.0f;
                    party->field_8 &= ~0x1000;
                }
            }
        }
    }
}
#endif
#ifndef NONMATCHING
void partyPreDisp(PartyEntry* party);
#endif

#ifdef NONMATCHING
void partyPreDisp(PartyEntry* party) {
    Vec screen;
    f32 z;
    f32 size;
    s32 mode;
    s32 v;

    if (!(party->flags2 & 0x10) && !(party->flags & 0x200)) {
        partyMakeDispDir(party);
    }
    if (party->field_8 & 0x6000) {
        if (party->field_8 & 0x2000) {
            party->field_8 &= ~0x2000;
        }
        if (party->field_8 & 0x4000) {
            party->field_8 &= ~0x4000;
        }
        animPoseSetAnim(party->paperAnimGroup, party->animName, 1);
        if (party->field_1C) {
            animPoseSetPaperAnim(party->paperAnimGroup, (const char*)party->field_1C, 1);
        }
        animPoseSetLocalTime(party->paperAnimGroup, party->field_20);
    }
    animPoseMain(party->paperAnimGroup);
    if (party->flags2 & 1) {
        return;
    }
    screen = party->position;
    PSMTX44MultVec(camGetPtr((CameraId)4)->projection, &screen, &screen);
    z = 5000.0f * screen.z + 5000.0f;
    if (z < 0.0f) {
        z = 0.0f;
    } else if (z > 10000.0f) {
        z = 10000.0f;
    }
    z *= -1.0f;
    v = PS16(party, 0x2A);
    if (v > 0) {
        if (!(v & 2)) {
            dispEntry((CameraId)party->camId, z, 1, partyDisp, party);
        }
    } else {
        dispEntry((CameraId)party->camId, z, 1, partyDisp, party);
    }
    mode = 2;
    size = 13.333333f;
    if ((s8)PU8(party, 0x31) != 6) {
        party->field_B8 = party->position;
    } else {
        if (party->runMode == 4 || (party->runMode == 8 && !(party->flags & 0x100))) {
            party->field_B8 = party->position;
        }
        if (party->flags & 0x100) {
            size = PF32(party, 0x174);
            if (party->flags & 0x80000000) {
                mode = 1;
            }
        }
    }
    if (N_vivianDisplayTailCheck(party)) {
        Vec pos;
        Vec dir;
        Vec hitPos;
        Vec hitNrm;
        f32 dist;

        dist = 1000.0f;
        pos = party->position;
        pos.y += 10.0f;
        dir = (Vec){0.0f, -1.0f, 0.0f};
        party->field_B8.y = partyHitCheck(party, &pos, &dir, &hitPos, &hitNrm, &dist) ? hitPos.y : party->position.y;
        animPoseVivianMain(party->paperAnimGroup, &party->field_B8);
    }
    if (!(party->flags2 & 0x100000)) {
        mode = shadowEntryMode(mode, party->field_B8.x, party->field_B8.y, party->field_B8.z, size);
        if (party->camId != 4) {
            shadowSetCamId(mode, party->camId);
        }
        if (party->flags2 & 0x200000) {
            shadowFlagOn(mode, 4);
        }
    }
}

void partyDisp(CameraId cam, void* param) {
    PartyEntry* party = param;
    Mtx m;
    Mtx t;
    Mtx s;
    f32 scale;
    f32 dir;
    f32 yoff;
    BOOL flip;

    if (!partyCountActive()) {
        return;
    }
    if (party->flags & 0x200) {
        PF32(party, 0x88) = -6.8f;
        party->field_8C = 6.8f;
    }
    scale = (party->flags & 0x800000) ? 1.2f : 2.0f;
    PSMTXScale(m, party->scale.x * scale, party->scale.y * scale, party->scale.z * scale);
    if (!(party->flags2 & 8)) {
        dir = revise360(party->displayDirection);
        flip = FALSE;
        if (dir >= 90.0f && dir <= 270.0f) {
            flip = TRUE;
        }
        PSMTXScale(s, 1.0f, 1.0f, flip ? -1.0f : 1.0f);
        PSMTXConcat(s, m, m);
    }
    PSMTXTrans(t, -PF32(party, 0x88), -party->field_8C, -PF32(party, 0x90));
    PSMTXConcat(t, m, m);
    PSMTXRotRad(t, 'z', 0.017453292f * party->rotation);
    PSMTXConcat(t, m, m);
    PSMTXRotRad(t, 'x', 0.017453292f * PF32(party, 0x64));
    PSMTXConcat(t, m, m);
    PSMTXRotRad(t, 'y', 0.017453292f * revise360(party->displayDirection - PF32(party, 0xF8)));
    PSMTXConcat(t, m, m);
    if (party->flags2 & 0xC0) {
        dir = revise360(party->displayDirection);
        if (dir >= 90.0f && dir <= 270.0f) {
            PSMTXRotRad(t, 'y', 0.017453292f * ((party->flags2 & 0x40) ? 180.0f : 0.0f));
            PSMTXConcat(t, m, m);
        } else {
            PSMTXRotRad(t, 'y', 0.017453292f * ((party->flags2 & 0x40) ? 0.0f : 180.0f));
            PSMTXConcat(t, m, m);
        }
    }
    PSMTXTrans(t, PF32(party, 0x88), party->field_8C, PF32(party, 0x90));
    PSMTXConcat(t, m, m);
    yoff = 0.0f;
    if (party->field_1C) {
        if (party->currentMemberId == 4) {
            yoff = 1.0f;
        } else if (party->currentMemberId == 3) {
            yoff = 2.0f;
        } else if (party->currentMemberId == 7) {
            yoff = 2.0f;
        } else if (party->currentMemberId == 1) {
            yoff = 2.0f;
        } else if (party->currentMemberId == 11) {
            yoff = 3.0f;
        } else if (party->currentMemberId == 8) {
            yoff = 3.5f;
        } else if (party->currentMemberId == 10) {
            yoff = 4.0f;
        } else if (party->currentMemberId == 9) {
            yoff = -1.0f;
        }
    }
    PSMTXTrans(t, party->position.x + PF32(party, 0x7C), yoff + (party->position.y + PF32(party, 0x80)),
               party->position.z + PF32(party, 0x84));
    PSMTXConcat(t, m, m);
    animPoseDrawMtx(party->paperAnimGroup, m, 2, 0.0f, 1.0f);
    animPoseDrawMtx(party->paperAnimGroup, m, 1, 0.0f, 1.0f);
    animPoseSetLocalTimeRate(party->paperAnimGroup, (party->flags & 0x80) ? 0.75f : 1.0f);
}
#endif
#ifndef NONMATCHING
void partyDisp(CameraId cam, void* param);
#endif


#ifdef NONMATCHING
void partyKeyOn(void) {
}
#endif
#ifndef NONMATCHING
void partyKeyOn(void);
#endif

#ifdef NONMATCHING
void partyKeyOff(void) {
}
#endif
#ifndef NONMATCHING
void partyKeyOff(void);
#endif

#ifdef NONMATCHING
void L_partyClearCont(PartyEntry* party) {
    PS8(party, 0x158) = 0;
    PS8(party, 0x159) = 0;
    PS8(party, 0x15A) = 0;
    PS8(party, 0x15B) = 0;
    PS8(party, 0x15C) = 0;
    PS8(party, 0x15D) = 0;
    PS8(party, 0x15E) = 0;
    PS8(party, 0x15F) = 0;
    PU16(party, 0x150) = 0;
    PU16(party, 0x152) = 0;
    PU16(party, 0x154) = 0;
    PU16(party, 0x156) = 0;
}
#endif
#ifndef NONMATCHING
void L_partyClearCont(PartyEntry* party);
#endif

#ifdef NONMATCHING
void partyUpdateKeyData(PartyEntry* party) {
    s32 port = PS8(party, 0x30);
    if (party->flags & 0x60000000) {
        L_partyClearCont(party);
        return;
    }
    PS8(party, 0x158) = gp->stickX[port];
    PS8(party, 0x159) = -gp->stickY[port];
    PS8(party, 0x15A) = gp->substickX[port];
    PS8(party, 0x15B) = -gp->substickY[port];
    PS8(party, 0x15C) = gp->triggerLeft[port];
    PS8(party, 0x15D) = gp->triggerRight[port];
    PS8(party, 0x15E) = 0;
    PS8(party, 0x15F) = 0;
    PU16(party, 0x150) = gp->button[port];
    PU16(party, 0x152) = gp->buttonNew[port];
    PU16(party, 0x154) = gp->buttonRepeat[port];
    PU16(party, 0x156) = gp->buttonUp[port];
}
#endif
#ifndef NONMATCHING
void partyUpdateKeyData(PartyEntry* party);
#endif

#ifdef NONMATCHING
void partyShadowOff(PartyEntry* party) {
    if (party) {
        party->flags2 |= 0x100000;
    }
}
#endif
#ifndef NONMATCHING
void partyShadowOff(PartyEntry* party);
#endif

/* @@FAMI@@ */
#ifdef NONMATCHING
static inline void partyPoseEntryF(PartyEntry* party) {
    char* animName;

    if ((s8)PU8(party, 0x31) != PARTY_MEMBER_YOSHI) {
        if (!(party->flags2 & 0x8000)) {
            animName = party_dp->name;
        } else {
            animName = (char*)str_802CCEEC;
        }
    } else {
        animName = yoshigroup[pouchGetPartyColor(PARTNER_YOSHI)];
        if (party->flags2 & 0x8000) {
            animName = (char*)str_802CCEEC;
        }
    }
    if (party->paperAnimGroup >= 0) {
        animPoseRelease(party->paperAnimGroup);
    }
    party->paperAnimGroup = animPoseEntry(animName, 2);
}
#endif


#ifdef NONMATCHING
void partySetFamicomMode(PartyEntry* party, s32 mode) {
    if (mode == 1) {
        if (party->flags2 & 0x8000) {
            return;
        }
        L_partyForceSlitOff(party);
        party->flags2 |= 0x8000;
        partyPoseEntryF(party);
        partyChgPose(party, partyChgPoseId(party, 1));
    } else {
        if (!(party->flags2 & 0x8000)) {
            return;
        }
        party->flags2 &= ~0x8000;
        partyPoseEntryF(party);
        partyChgPose(party, partyChgPoseId(party, 1));
    }
}
#endif
#ifndef NONMATCHING
void partySetFamicomMode(PartyEntry* party, s32 mode);
#endif


// prototypes for asm stopgap forward references
void partySetFamicomMode(PartyEntry* party, s32 mode);
void partyShadowOff(PartyEntry* party);
void partyUpdateKeyData(PartyEntry* party);
void L_partyClearCont(PartyEntry* party);
void partyKeyOff(void);
void partyKeyOn(void);
void partyDisp(CameraId cam, void* param);
void partyPreDisp(PartyEntry* party);
void partyMakeDispDir(PartyEntry* party);
void partySetCamId(PartyEntry* party, s32 cameraId);
void partyInitCamId(PartyEntry* party);
void party_damage_return(PartyEntry* party);
s32 partyRideYoshiMain(PartyEntry* party);
void party_ride_yoshi_force_move(void);
void party_force_ride_yoshi(PartyEntry* party);
void partyRideMain(PartyEntry *party);
s32 partyRideChk(PartyEntry* party);
void allPartyRideOff2(void);
void allPartyRideOff(void);
void L_allPartyRideOn(void);
void allPartyForceRideOn(void);
void getRidePos(PartyEntry* party, Vec* pos);
void allPartyRideShip(void);
void allPartyRidePlane(void);
void partyDokanEnd(s32 id, s32 dir);
s32 partyDokanMain(PartyEntry* party);
s32 partyDokanInit(PartyEntry* party);
s32 partyGoodbyeMain(PartyEntry* party);
s32 partyGoodbyeInit(PartyEntry* party);
s32 partyHelloMain(PartyEntry* party);
void partyHello(PartyEntry* party);
BOOL partyDoWork(void);
void driveParty(PartyEntry* party);
void partyMain(void);
void unk_800ba2dc(PartyEntry* party);
void N_partyForceChgRunMode(PartyEntry* party, s32 mode, s32 sub);
void partyChgRunMode(PartyEntry* party, s32 mode);
void N__partyChgRunMode(PartyEntry* party, s32 prev, s32 mode);
void partyUsePost(PartyEntry* party);
void partyReInit(void);
void partyInit(void);
s32 partyEntry2Pos(s32 memberId, f32 x, f32 y, f32 z);
s32 partyEntry2Hello(s32 memberId);
s32 partyEntry2(s32 memberId);
s32 partyEntryMain(s32 memberId);
f32 partyGetHeight(PartyEntry* party);
s32 yoshiSetColor(void);
s32 partyKill2(s32 id);
s32 partyKill(s32 id);
BOOL partyGoodbye(s32 id);
s32 partyEntryPos(s32 memberId, f32 x, f32 y, f32 z);
s32 partyEntry(s32 memberId);
s32 partyEntryHello(s32 memberId);
void partySetForceMove(PartyEntry* party, s16 a2, f32 a3, f32 a4);
void partyStop(PartyEntry* party);
void partyRun(PartyEntry* party);
void partyCtrlOn(PartyEntry* party);
void partyCtrlOff(PartyEntry* party);
void partyChgPaper(PartyEntry* party, char* paper);
void partyChgPose(PartyEntry* party, char* pose);
char* partyChgPoseId(PartyEntry* party, s32 index);
void partyPaperLightOff(PartyEntry* party);
void partyPaperOff(PartyEntry* party);
BOOL partyPaperOn(PartyEntry* party, const char* animGroup);
PartyEntry* anotherPartyGetPtr(s32 index);
PartyEntry* partyGetPtr(s32 index);

#ifndef NONMATCHING
static inline PartyEntry* partyGetPtr__af_inl(s32 index) {
    if (index >= 0) {
        return partyPtrTbl[index];
    }
    return NULL;
}
static inline void partyShadowOff__af_inl(PartyEntry* party) {
    if (party) {
        party->flags2 |= 0x100000;
    }
}
static inline void partyChgPose__af_inl(PartyEntry* party, char* pose) {
    if (!(party->flags2 & 2)) {
        if (party->animName == NULL || strcmp(party->animName, pose)) {
            if (!(party->flags2 & 0x8000)) {
                party->animName = pose;
                party->field_20 = 0;
                party->field_8 |= 0x2000;
            }
        }
    }
}

#define partyGetPtr partyGetPtr__af_inl
void partyDokanEnd(s32 id, s32 dir) {
    PartyEntry* party = partyGetPtr(id);
    if (party && party->runMode == 10) {
        party->field_38 = 100;
        PU8(party, 0x2E) = dir;
        party->flags2 &= ~0x8;
        party->flags2 &= ~0x10;
        party->flags2 &= ~0xC0;
        party->flags &= ~0x4000000;
        party->flags &= ~0x2000000;
        partyShadowOn(party);
        party->field_B8 = party->position;
        L_partyVivianTailStart(party);
    }
}

#undef partyGetPtr

#define partyGetPtr partyGetPtr__af_inl
void allPartyRidePlane(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        bomhei_use_cancel();
        party->flags |= 0x10000;
        partyChgRunMode(party, 11);
    }
    party = partyPtrTbl[1];
    if (party) {
        party->flags |= 0x10000;
        partyChgRunMode(party, 11);
    }
}

#undef partyGetPtr

#define partyGetPtr partyGetPtr__af_inl
void allPartyRideShip(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        bomhei_use_cancel();
        party->flags |= 0x20000;
        partyChgRunMode(party, 11);
    }
    party = partyPtrTbl[1];
    if (party) {
        party->flags |= 0x20000;
        partyChgRunMode(party, 11);
    }
}

#undef partyGetPtr

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void getRidePos(PartyEntry* party, Vec* pos) {
	asm volatile {
		opword 0x9421FFD0
		opword 0x7C0802A6
		opword 0x90010034
		opword 0xDBE10020
		opword 0xF3E10028
		opword 0x93E1001C
		opword 0x93C10018
		opword 0x93A10014
		opword 0x7C7F1B78
		opword 0x7C9D2378
		opword 0x83C30160
		opword 0xA01E002E
		opword 0x2800001A
		opword 0x4082017C
		opword 0xC03E01AC
		bl toMovedir
		lfs f2, float_3p1416_8041b188(r2)
		lfs f0, float_180_8041b0fc(r2)
		opword 0xEC220072
		opword 0xEFE10024
		bl yoshiGetStatus
		opword 0x2C030002
		opword 0x41820050
		opword 0xFC20F890
		bl sin
		opword 0xFC600818
		lfs f2, float_10_8041b124(r2)
		opword 0xC01E008C
		opword 0xFC20F890
		opword 0xEC0200FC
		opword 0xD01D0000
		bl cos
		opword 0xFC600818
		lfs f2, float_10_8041b124(r2)
		opword 0xC01E0094
		lfs f1, float_20_8041b140(r2)
		opword 0xEC0200FC
		opword 0xD01D0008
		opword 0xC01E0090
		opword 0xEC01002A
		opword 0xD01D0004
		opword 0x4800004C
		opword 0xFC20F890
		bl sin
		opword 0xFC600818
		lfs f2, float_20_8041b140(r2)
		opword 0xC01E008C
		opword 0xFC20F890
		opword 0xEC0200FC
		opword 0xD01D0000
		bl cos
		opword 0xFC600818
		lfs f2, float_20_8041b140(r2)
		opword 0xC01E0094
		lfs f1, float_16_8041b17c(r2)
		opword 0xEC0200FC
		opword 0xD01D0008
		opword 0xC01E0090
		opword 0xEC01002A
		opword 0xD01D0004
		opword 0x881F002F
		opword 0x7C000775
		opword 0x41820164
		bl marioGetPartyId
		opword 0x2C030000
		opword 0x41800014
		opword 0x5460103A
		la r3, partyPtrTbl(r13)
		opword 0x7FE3002E
		opword 0x48000008
		opword 0x3BE00000
		opword 0xC03E01AC
		lfs f2, float_10_8041b124(r2)
		bl toMovedir2
		opword 0x3861000C
		opword 0x38810008
		bl sincosf
		bl yoshiGetStatus
		opword 0x2C030002
		opword 0x4182003C
		lfs f3, float_12_8041b18c(r2)
		opword 0xC041000C
		opword 0xC01F0058
		lfs f1, float_20_8041b140(r2)
		opword 0xEC0300BC
		opword 0xD01D0000
		opword 0xC0410008
		opword 0xC01F0060
		opword 0xEC0300BC
		opword 0xD01D0008
		opword 0xC01F005C
		opword 0xEC01002A
		opword 0xD01D0004
		opword 0x480000E8
		lfs f3, float_22_8041b190(r2)
		opword 0xC041000C
		opword 0xC01F0058
		lfs f1, float_16_8041b17c(r2)
		opword 0xEC0300BC
		opword 0xD01D0000
		opword 0xC0410008
		opword 0xC01F0060
		opword 0xEC0300BC
		opword 0xD01D0008
		opword 0xC01F005C
		opword 0xEC01002A
		opword 0xD01D0004
		opword 0x480000B0
		opword 0x28000018
		opword 0x40820028
		opword 0xC01E008C
		lfs f1, float_40_8041b194(r2)
		opword 0xD01D0000
		opword 0xC01E0094
		opword 0xD01D0008
		opword 0xC01E0090
		opword 0xEC01002A
		opword 0xD01D0004
		opword 0x48000084
		opword 0x28000019
		opword 0x4082005C
		bl N_marioShipGetDir
		opword 0x2C030000
		opword 0x4182000C
		lfs f1, float_0_8041b100(r2)
		opword 0x48000008
		lfs f1, float_180_8041b0fc(r2)
		bl toMovedirSimple
		opword 0x3861000C
		opword 0x38810008
		bl sincosf
		lfs f2, float_22_8041b190(r2)
		opword 0xC021000C
		opword 0xC01E008C
		opword 0xEC02007A
		opword 0xD01D0000
		opword 0xC0210008
		opword 0xC01E0094
		opword 0xEC02007A
		opword 0xD01D0008
		opword 0xC01E0090
		opword 0xD01D0004
		opword 0x48000024
		opword 0xC01E008C
		lfs f1, float_20_8041b140(r2)
		opword 0xD01D0000
		opword 0xC01E0094
		opword 0xD01D0008
		opword 0xC01E0090
		opword 0xEC01002A
		opword 0xD01D0004
		opword 0xE3E10028
		opword 0x80010034
		opword 0xCBE10020
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x7C0803A6
		opword 0x38210030
	}
}
#pragma pop

#define partyShadowOff partyShadowOff__af_inl
#define partyGetPtr partyGetPtr__af_inl
#pragma dont_inline on
#pragma dont_inline on
#pragma dont_inline on
void allPartyForceRideOn(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        N_partyForceChgRunMode(party, 11, 11);
        party->flags2 |= 1;
        partyShadowOff(party);
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        N_partyForceChgRunMode(party, 11, 11);
        party->flags2 |= 1;
        partyShadowOff(party);
    }
}
#pragma dont_inline reset

#pragma dont_inline reset

#pragma dont_inline reset

#undef partyShadowOff
#undef partyGetPtr

#define partyGetPtr partyGetPtr__af_inl
void L_allPartyRideOn(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party) {
        partyChgRunMode(party, 11);
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        partyChgRunMode(party, 11);
    }
}

#undef partyGetPtr

#define partyGetPtr partyGetPtr__af_inl
void allPartyRideOff(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party && party->runMode == 11) {
        party->field_38 = 100;
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party && party->runMode == 11) {
        party->field_38 = 100;
    }
}

#undef partyGetPtr

#define partyGetPtr partyGetPtr__af_inl
void allPartyRideOff2(void) {
    PartyEntry* party = partyGetPtr(marioGetPartyId());
    if (party && party->runMode == 11) {
        party->field_38 = 101;
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party && party->runMode == 11) {
        party->field_38 = 101;
    }
}

#undef partyGetPtr

s32 partyRideChk(PartyEntry* party) {
    s32 ret = 0;
    if (party == NULL) {
        return 0;
    }
    if (party->runMode == 11) {
        ret = 1;
        if (party->field_38 >= 2) {
            ret = 2;
        }
    }
    return ret;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void partyRideMain(PartyEntry *party) {
	char _af_pad[64];
	asm volatile {
		opword 0x7C7D1B78
		lis r4, vec3_802ccd30@ha
		opword 0x88030038
		addi r31, r4, vec3_802ccd30@l
		opword 0x83C30160
		opword 0x2C000015
		opword 0x41820634
		opword 0x40800048
		opword 0x2C00000A
		opword 0x41820468
		opword 0x40800028
		opword 0x2C000001
		opword 0x41820240
		opword 0x40800010
		opword 0x2C000000
		opword 0x40800064
		opword 0x48000B00
		opword 0x2C000003
		opword 0x40800AF8
		opword 0x480002FC
		opword 0x2C000014
		opword 0x408005D8
		opword 0x2C00000C
		opword 0x40800AE4
		opword 0x4800045C
		opword 0x2C00006E
		opword 0x418207F0
		opword 0x4080001C
		opword 0x2C000064
		opword 0x40800008
		opword 0x48000AC8
		opword 0x2C000066
		opword 0x40800AC0
		opword 0x48000660
		opword 0x2C0000C8
		opword 0x41820608
		opword 0x40800AB0
		opword 0x2C000070
		opword 0x40800AA8
		opword 0x480008A4
		la r4, _af_pad+24
		bl getRidePos
		opword 0x80610020
		opword 0x80010024
		opword 0x907D0094
		opword 0x901D0098
		opword 0x80010028
		opword 0x901D009C
		opword 0xC03D0058
		opword 0xC05D0060
		opword 0xC07D0094
		opword 0xC09D009C
		bl distABf
		opword 0xD03D0128
		opword 0xC03D0058
		opword 0xC05D0060
		opword 0xC07D0094
		opword 0xC09D009C
		bl angleABf
		opword 0xD03D0100
		opword 0x3C004330
		opword 0x3860001E
		opword 0xC8BF01D0
		opword 0x907D0024
		lfs f1, float_0p4_8041b174(r2)
		opword 0x807D0024
		opword 0x90010030
		opword 0x6C638000
		opword 0xC07D0128
		opword 0x90610034
		lfs f4, float_0p5_8041b170(r2)
		opword 0xC8010030
		opword 0x90010040
		opword 0xEC402828
		lfs f0, float_1_8041b0e8(r2)
		opword 0x90010038
		opword 0xEC431024
		opword 0x90010048
		opword 0xD05D0104
		opword 0xC07D0098
		opword 0xC05D005C
		opword 0xD03D011C
		opword 0xECC31028
		opword 0x801D0024
		opword 0xC05D011C
		opword 0x6C008000
		opword 0x90010044
		opword 0xC8210040
		opword 0x9001003C
		opword 0xEC212828
		opword 0xC8610038
		opword 0x9001004C
		opword 0xEC420072
		opword 0xEC632828
		opword 0xC8210048
		opword 0xEC212828
		opword 0xEC4300B2
		opword 0xEC4430BA
		opword 0xEC220824
		opword 0xD03D0114
		opword 0xD01D0124
		opword 0x801D0004
		opword 0x60000010
		opword 0x901D0004
		opword 0x801D0004
		opword 0x540007BD
		opword 0x408200BC
		opword 0x881D0031
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800008
		bl partyGetHp
		opword 0x801D0004
		opword 0x54000421
		opword 0x40820024
		opword 0x889D0031
		lis r3, partyPoseTbl@ha
		addi r0, r3, partyPoseTbl@l
		opword 0x7C830774
		opword 0x1C63003C
		opword 0x7C601A14
		opword 0x83C30010
		opword 0x48000048
		opword 0x881D0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x4182001C
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		addi r0, r3, partyDotPoseTbl@l
		opword 0x7C602214
		opword 0x83C30010
		opword 0x48000020
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		addi r0, r3, yoshiDotPoseTbl@l
		opword 0x7C602214
		opword 0x83C30010
		opword 0x807D0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DD0018
		opword 0x38000000
		opword 0xB01D0020
		opword 0x801D0008
		opword 0x60002000
		opword 0x901D0008
		opword 0x38000001
		opword 0x981D0038
		opword 0x480008D4
		opword 0xC03D0114
		opword 0x387D0058
		opword 0xC01D011C
		opword 0x389D0060
		opword 0xEC010028
		opword 0xD01D0114
		opword 0xC03D005C
		opword 0xC01D0114
		opword 0xEC01002A
		opword 0xD01D005C
		opword 0xC03D0104
		opword 0xC05D0100
		bl movePos
		opword 0xC03D010C
		opword 0xC01D0124
		opword 0xEC21002A
		bl revise360
		opword 0xD03D010C
		lfs f1, float_2_8041b0e4(r2)
		opword 0xC05D0124
		lfs f0, float_30_8041b178(r2)
		opword 0xEC22082A
		opword 0xD03D0124
		opword 0xC03D0124
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820008
		opword 0xD01D0124
		opword 0x807D0024
		opword 0x3C004330
		opword 0x90010048
		opword 0x6C608000
		opword 0xC85F01D0
		opword 0x9001004C
		lfs f0, float_10_8041b124(r2)
		opword 0xC8210048
		opword 0xEC211028
		opword 0xFC010040
		opword 0x40810008
		opword 0xFC200090
		lfs f0, float_10_8041b124(r2)
		opword 0xEC010024
		opword 0xD01D0070
		opword 0xC01D0070
		opword 0xD01D0074
		opword 0xC01D0070
		opword 0xD01D0078
		opword 0x807D0024
		opword 0x3403FFFF
		opword 0x901D0024
		opword 0x40800808
		opword 0x38000002
		opword 0x981D0038
		opword 0x480007FC
		opword 0x801D0004
		opword 0x3BC00001
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881D0031
		li r28, 0x0
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801D0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889D0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881D0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807D0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DD0018
		opword 0x38000000
		opword 0xB01D0020
		opword 0x801D0008
		opword 0x60002000
		opword 0x901D0008
		lfs f0, float_0_8041b100(r2)
		opword 0x281D0000
		opword 0xD01D0114
		opword 0xC01D0098
		opword 0xD01D005C
		opword 0x807F015C
		opword 0x801F0160
		opword 0x907D0070
		opword 0x901D0074
		opword 0x801F0164
		opword 0x901D0078
		opword 0x801D0004
		opword 0x60000001
		opword 0x901D0004
		opword 0x41820010
		opword 0x801D0004
		opword 0x64000010
		opword 0x901D0004
		opword 0x3800000A
		opword 0x981D0038
		opword 0x480006B8
		opword 0x807E008C
		opword 0x801E0090
		opword 0x907D0058
		opword 0x901D005C
		opword 0x801E0094
		opword 0x901D0060
		opword 0xC01E01AC
		opword 0xD01D0110
		opword 0xC03D0110
		bl toMovedir
		opword 0xD03D00FC
		opword 0x48000688
		opword 0x801D0004
		opword 0x3BC00001
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881D0031
		opword 0x3B800000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801D0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889D0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881D0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807D0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DD0018
		opword 0x38000000
		opword 0xB01D0020
		opword 0x801D0008
		opword 0x60002000
		opword 0x901D0008
		opword 0x801D0004
		opword 0x281D0000
		opword 0x60000001
		opword 0x901D0004
		opword 0x41820010
		opword 0x801D0004
		opword 0x64000010
		opword 0x901D0004
		opword 0x7FA3EB78
		opword 0x38810020
		bl getRidePos
		opword 0x807F0168
		opword 0x801F016C
		lfs f0, float_0_8041b100(r2)
		opword 0x907D0070
		opword 0x901D0074
		opword 0x801F0170
		opword 0x901D0078
		opword 0x80610020
		opword 0x80010024
		opword 0x907D0058
		opword 0x901D005C
		opword 0x80010028
		opword 0x901D0060
		opword 0xD01D0114
		opword 0x807D0160
		opword 0xC00301AC
		opword 0xD01D0110
		opword 0xC03D0110
		bl toMovedir
		opword 0xD03D00FC
		opword 0x48000518
		opword 0x38600015
		opword 0x38000010
		opword 0x987D0038
		lfs f1, float_16_8041b17c(r2)
		opword 0x901D0024
		lfs f0, float_0p5_8041b170(r2)
		opword 0xD03D0114
		opword 0xD01D0174
		opword 0xC03D005C
		opword 0xC01D0114
		opword 0xEC01002A
		opword 0xD01D005C
		opword 0xC03D0114
		opword 0xC01D0174
		opword 0xEC01002A
		opword 0xD01D0114
		opword 0x807D0024
		opword 0x3403FFFF
		opword 0x901D0024
		opword 0x418104C8
		opword 0x38000016
		opword 0x981D0038
		opword 0x801D0000
		opword 0x64000200
		opword 0x901D0000
		opword 0x480004B0
		opword 0x801D0000
		opword 0x281D0000
		lfs f1, float_0_8041b100(r2)
		opword 0x54000418
		lfs f0, float_1_8041b0e8(r2)
		opword 0x901D0000
		opword 0xD03D0080
		opword 0xD01D0070
		opword 0xC01D0070
		opword 0xD01D0074
		opword 0xC01D0070
		opword 0xD01D0078
		opword 0x41820010
		opword 0x801D0004
		opword 0x54000314
		opword 0x901D0004
		opword 0x7FA3EB78
		opword 0x38800001
		bl partyChgRunMode
		opword 0x48000460
		opword 0x801D0004
		lfs f1, float_0p5_8041b170(r2)
		opword 0x5400003C
		opword 0x901D0004
		opword 0xC3FE008C
		opword 0xC05E0090
		lfs f30, 0x94(r30)
		opword 0xD3FD0058
		opword 0xC01E01B8
		opword 0xEC01103A
		opword 0xD01D005C
		opword 0xD3DD0060
		opword 0x881D0038
		opword 0x28000064
		opword 0x40820010
		opword 0x389D0094
		bl partyGetAppearPos
		opword 0x4800000C
		opword 0x389D0094
		bl partyGetAppearPos2
		opword 0xC01E01AC
		opword 0x38000010
		opword 0xFC20F890
		opword 0xD01D0110
		opword 0xFC40F090
		opword 0x901D0024
		opword 0xC07D0094
		opword 0xC09D009C
		bl distABf
		opword 0xD03D0128
		opword 0xFC20F890
		opword 0xFC40F090
		opword 0xC07D0094
		opword 0xC09D009C
		bl angleABf
		opword 0xD03D0100
		opword 0x3C004330
		opword 0xC89F01D0
		opword 0x807D0024
		opword 0x90010048
		opword 0x6C638000
		opword 0xC05D0128
		opword 0x9061004C
		lfs f3, float_0p5_8041b170(r2)
		opword 0xC8010048
		opword 0x90010040
		opword 0xEC202028
		lfs f0, float_1_8041b0e8(r2)
		opword 0xEC220824
		opword 0xD03D0104
		opword 0x801D0024
		opword 0xC05D0098
		opword 0x6C008000
		opword 0xC03D005C
		opword 0x90010044
		opword 0xECA20828
		opword 0xC8210040
		opword 0xEC412028
		opword 0xFC202A10
		opword 0xEC4300B2
		opword 0xFC010040
		opword 0x4080000C
		lfs f5, float_10_8041b124(r2)
		opword 0x48000024
		lfs f0, float_0_8041b100(r2)
		opword 0xFC050040
		opword 0x4C411382
		opword 0x40820010
		opword 0xC01D00F0
		opword 0xECA3283A
		opword 0x48000008
		lfs f5, float_10_8041b124(r2)
		opword 0xEC25282A
		opword 0x281D0000
		opword 0xEC0210B8
		opword 0xEC010024
		opword 0xEC2000B2
		opword 0xFC000050
		opword 0xD03D0114
		opword 0xD01D0118
		opword 0x801D0000
		opword 0x60000010
		opword 0x901D0000
		opword 0x801D0004
		opword 0x5400003C
		opword 0x901D0004
		opword 0x41820010
		opword 0x801D0004
		opword 0x54000314
		opword 0x901D0004
		opword 0x3800006E
		opword 0x981D0038
		opword 0x480002EC
		bl partyMoveNoHosei
		opword 0xC03D0114
		lfs f0, float_0_8041b100(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820018
		opword 0x801D0000
		lfs f0, float_neg1p6_8041b180(r2)
		opword 0x54000734
		opword 0x901D0000
		opword 0xD01D0118
		opword 0xC03D005C
		lfs f0, float_neg2000_8041b164(r2)
		opword 0xFC010040
		opword 0x40800018
		opword 0x38600000
		opword 0x3800006F
		opword 0x907D0024
		opword 0x981D0038
		opword 0x4800029C
		opword 0x801D0138
		opword 0x28000000
		opword 0x40820088
		opword 0x801D0024
		opword 0x3CA04330
		opword 0x809F0174
		opword 0x20000010
		opword 0x807F0178
		opword 0x6C068000
		opword 0x801F017C
		opword 0x90C1004C
		opword 0xC85F01D0
		opword 0x90A10048
		lfs f0, float_0p0625_8041b184(r2)
		opword 0xC8210048
		opword 0x90810014
		opword 0xEC211028
		opword 0x90610018
		opword 0xEC010032
		opword 0x9001001C
		opword 0xD0010014
		opword 0xD0010018
		opword 0x80010014
		opword 0xD001001C
		opword 0x80610018
		opword 0x901D0070
		opword 0x8001001C
		opword 0x907D0074
		opword 0x901D0078
		opword 0x807D0024
		opword 0x3403FFFF
		opword 0x901D0024
		opword 0x41810218
		opword 0x38000000
		opword 0x901D0024
		opword 0x4800020C
		opword 0x3800006F
		opword 0x981D0038
		opword 0x801D0024
		opword 0x3CA04330
		opword 0x809F0180
		opword 0x20000010
		opword 0x807F0184
		opword 0x6C068000
		opword 0x801F0188
		opword 0x90C1004C
		opword 0xC85F01D0
		opword 0x90A10048
		lfs f0, float_0p0625_8041b184(r2)
		opword 0xC8210048
		opword 0x90810008
		opword 0xEC211028
		opword 0x9061000C
		opword 0xEC010032
		opword 0x90010010
		opword 0xD0010008
		opword 0xD001000C
		opword 0x80010008
		opword 0xD0010010
		opword 0x8061000C
		opword 0x901D0070
		opword 0x80010010
		opword 0x907D0074
		opword 0x901D0078
		opword 0x807D0024
		opword 0x3403FFFF
		opword 0x901D0024
		opword 0x4181018C
		opword 0x38000000
		opword 0x901D0024
		opword 0xC01E01AC
		opword 0xD01D0110
		opword 0xC01E01AC
		opword 0xD01D010C
		opword 0xC03D010C
		bl toMovedirSimple
		opword 0xD03D00FC
		opword 0x7FA3EB78
		opword 0xC01D00FC
		opword 0xD01D0100
		bl partyClearJumpPara
		opword 0x801D0004
		opword 0x3BC00001
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881D0031
		opword 0x3B800000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801D0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889D0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881D0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807D0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DD0018
		opword 0x38000000
		opword 0xB01D0020
		opword 0x801D0008
		opword 0x60002000
		opword 0x901D0008
		opword 0x801D0004
		opword 0x281D0000
		lfs f1, float_0_8041b100(r2)
		opword 0x54000734
		lfs f0, float_1_8041b0e8(r2)
		opword 0x901D0004
		opword 0x801D0000
		opword 0x54000418
		opword 0x901D0000
		opword 0xD03D0080
		opword 0xD01D0070
		opword 0xC01D0070
		opword 0xD01D0074
		opword 0xC01D0070
		opword 0xD01D0078
		opword 0x801D0004
		opword 0x5400003C
		opword 0x901D0004
		opword 0x41820010
		opword 0x801D0004
		opword 0x54000314
		opword 0x901D0004
		opword 0x7FA3EB78
		opword 0x38800001
		bl partyChgRunMode
		opword 0x807D0058
		opword 0x801D005C
		opword 0x907D00B8
		opword 0x901D00BC
		opword 0x801D0060
		opword 0x901D00C0
	}
}
#pragma pop

#define partyShadowOff partyShadowOff__af_inl
void party_force_ride_yoshi(PartyEntry* party) {
    Vec pos;

    N_partyForceChgRunMode(party, 12, 10);
    party->flags &= ~0x100;
    getRidePos(party, &pos);
    party->position = pos;
    partyChgPoseId(party, 1);
    party->velY = EXT_LIT(float_0_8041b100, 0.0f);
    partyShadowOff(party);
    party->displayDirectionTarget = party->playerPtr->displayDirectionTarget;
    party->moveDir = toMovedir(party->displayDirectionTarget);
}

#undef partyShadowOff

#define partyGetPtr partyGetPtr__af_inl
void party_ride_yoshi_force_move(void) {
    Vec pos;
    PartyEntry* party = partyGetPtr(marioGetExtraPartyId());
    if (party) {
        getRidePos(party, &pos);
        party->position = pos;
        party->displayDirectionTarget = party->playerPtr->displayDirectionTarget;
        party->moveDir = toMovedir(party->displayDirectionTarget);
    }
}

#undef partyGetPtr

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 partyRideYoshiMain(PartyEntry* party) {
	asm volatile {
		opword 0x9421FFB0
		opword 0x7C0802A6
		opword 0x90010054
		opword 0x93E1004C
		opword 0x7C7F1B78
		opword 0x93C10048
		opword 0x93A10044
		opword 0x88030038
		opword 0x83A30160
		opword 0x2C000002
		opword 0x418202B8
		opword 0x40800014
		opword 0x2C000000
		opword 0x41820018
		opword 0x408001D4
		opword 0x48000460
		opword 0x2C00000A
		opword 0x418203BC
		opword 0x48000454
		lfs f0, float_1p6_8041b16c(r2)
		opword 0x38810014
		opword 0xD01F011C
		bl getRidePos
		opword 0x80610014
		opword 0x80010018
		opword 0x907F0094
		opword 0x901F0098
		opword 0x8001001C
		opword 0x901F009C
		opword 0xC03F0058
		opword 0xC05F0060
		opword 0xC07F0094
		opword 0xC09F009C
		bl distABf
		opword 0xD03F0128
		opword 0xC03F0058
		opword 0xC05F0060
		opword 0xC07F0094
		opword 0xC09F009C
		bl angleABf
		opword 0xD03F0100
		opword 0x3C004330
		opword 0x3880000F
		lis r3, double_to_int_802ccf00@ha
		opword 0x909F0024
		lfd f6, double_to_int_802ccf00@l(r3)
		opword 0x807F0024
		opword 0x90010020
		opword 0x6C638000
		opword 0xC03F0128
		opword 0x90610024
		lfs f5, float_0p5_8041b170(r2)
		opword 0xC8010020
		opword 0x90010030
		opword 0xEC003028
		opword 0x90010028
		opword 0xEC010024
		opword 0x90010038
		opword 0xD01F0104
		opword 0x801F0024
		opword 0xC03F0098
		opword 0x6C008000
		opword 0xC01F005C
		opword 0x90010034
		opword 0xEC210028
		opword 0xC07F011C
		opword 0xC8410030
		opword 0x9001002C
		opword 0xEC023028
		opword 0xC8410028
		opword 0x9001003C
		opword 0xEC823028
		opword 0xEC430032
		opword 0xC8010038
		opword 0xEC003028
		opword 0xEC4400B2
		opword 0xEC2508BA
		opword 0xEC010024
		opword 0xD01F0114
		opword 0x801F0004
		opword 0x540007BD
		opword 0x408200BC
		opword 0x881F0031
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800008
		bl partyGetHp
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820024
		opword 0x889F0031
		lis r3, partyPoseTbl@ha
		addi r0, r3, partyPoseTbl@l
		opword 0x7C830774
		opword 0x1C63003C
		opword 0x7C601A14
		opword 0x83C30010
		opword 0x48000048
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x4182001C
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		addi r0, r3, partyDotPoseTbl@l
		opword 0x7C602214
		opword 0x83C30010
		opword 0x48000020
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		addi r0, r3, yoshiDotPoseTbl@l
		opword 0x7C602214
		opword 0x83C30010
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		opword 0x38000001
		opword 0x981F0038
		opword 0x48000294
		opword 0x38810014
		bl getRidePos
		opword 0x80610014
		opword 0x80010018
		opword 0x907F0094
		opword 0x901F0098
		opword 0x8001001C
		opword 0x901F009C
		opword 0xC03F0058
		opword 0xC05F0060
		opword 0xC07F0094
		opword 0xC09F009C
		bl distABf
		opword 0xD03F0128
		opword 0xC03F0058
		opword 0xC05F0060
		opword 0xC07F0094
		opword 0xC09F009C
		bl angleABf
		opword 0xD03F0100
		opword 0x3C004330
		lis r4, double_to_int_802ccf00@ha
		opword 0x387F0058
		opword 0x80DF0024
		addi r5, r4, double_to_int_802ccf00@l
		opword 0x90010038
		opword 0x389F0060
		opword 0x6CC08000
		opword 0xC8250000
		opword 0x9001003C
		opword 0xC05F0128
		opword 0xC8010038
		opword 0xEC000828
		opword 0xEC020024
		opword 0xD01F0104
		opword 0xC03F0114
		opword 0xC01F011C
		opword 0xEC010028
		opword 0xD01F0114
		opword 0xC03F005C
		opword 0xC01F0114
		opword 0xEC01002A
		opword 0xD01F005C
		opword 0xC03F0104
		opword 0xC05F0100
		bl movePos
		opword 0x807F0024
		opword 0x3403FFFF
		opword 0x901F0024
		opword 0x418101CC
		opword 0x38000002
		opword 0x981F0038
		opword 0x480001C0
		opword 0x801F0004
		opword 0x3BC00001
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881F0031
		opword 0x3BA00000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3BA00001
		opword 0x2C1D0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889F0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		lfs f0, float_0_8041b100(r2)
		opword 0x281F0000
		opword 0x3800000A
		opword 0xD01F0114
		opword 0xC01F0098
		opword 0xD01F005C
		opword 0x981F0038
		opword 0x418200B0
		opword 0x801F0004
		opword 0x64000010
		opword 0x901F0004
		opword 0x480000A0
		opword 0x38810014
		bl getRidePos
		opword 0x80610014
		opword 0x80010018
		opword 0x907F0058
		opword 0x901F005C
		opword 0x8001001C
		opword 0x901F0060
		opword 0xC01D01AC
		opword 0xD01F0110
		opword 0xC03F0110
		bl toMovedir
		opword 0xD03F00FC
		opword 0xA01D002E
		opword 0x2800001A
		opword 0x41820060
		opword 0x7FE3FB78
		opword 0x38810008
		bl partyGetAppearPos
		opword 0xC0010008
		opword 0x7FE3FB78
		opword 0x38800002
		opword 0xD01F0058
		opword 0xC0010010
		opword 0xD01F0060
		bl partyChgRunMode
		opword 0x281F0000
		opword 0x41820010
		opword 0x801F0004
		opword 0x54000314
		opword 0x901F0004
		lis r3, vec3_802cced4@ha
		addi r4, r3, vec3_802cced4@l
		opword 0x80640000
		opword 0x80040004
		opword 0x907F007C
		opword 0x901F0080
		opword 0x80040008
		opword 0x901F0084
		opword 0x80010054
		opword 0x38600000
		opword 0x83E1004C
		opword 0x83C10048
		opword 0x83A10044
		opword 0x7C0803A6
		opword 0x38210050
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void party_damage_return(PartyEntry* party) {
	asm volatile {
		opword 0x9421FF90
		opword 0x7C0802A6
		opword 0x90010074
		opword 0x93E1006C
		opword 0x93C10068
		opword 0x7C7E1B78
		opword 0x93A10064
		opword 0x80630008
		opword 0x83FE0160
		opword 0x54600739
		opword 0x41820040
		opword 0x54600776
		opword 0x901E0008
		opword 0x801E0000
		opword 0x5400062C
		opword 0x901E0000
		opword 0x801E0008
		opword 0x540001CF
		opword 0x40820010
		opword 0x3800000A
		opword 0x981E0038
		opword 0x48000014
		opword 0x38600000
		opword 0x38000064
		opword 0x987E0038
		opword 0x901E0024
		opword 0x881E0038
		opword 0x28000017
		opword 0x41810498
		lis r3, jumptable_803126C0@ha
		opword 0x5400103A
		addi r3, r3, jumptable_803126C0@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x807E0024
		opword 0x3403FFFF
		opword 0x901E0024
		opword 0x41810470
		opword 0x3800000A
		opword 0x981E0038
		opword 0x801E0004
		opword 0x540007BD
		opword 0x408200BC
		opword 0x881E0031
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800008
		bl partyGetHp
		opword 0x801E0004
		opword 0x54000421
		opword 0x40820024
		opword 0x889E0031
		lis r3, partyPoseTbl@ha
		addi r0, r3, partyPoseTbl@l
		opword 0x7C830774
		opword 0x1C63003C
		opword 0x7C601A14
		opword 0x83A30020
		opword 0x48000048
		opword 0x881E0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x4182001C
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		addi r0, r3, partyDotPoseTbl@l
		opword 0x7C602214
		opword 0x83A30020
		opword 0x48000020
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		addi r0, r3, yoshiDotPoseTbl@l
		opword 0x7C602214
		opword 0x83A30020
		opword 0x807E0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93BE0018
		opword 0x38000000
		opword 0xB01E0020
		opword 0x801E0008
		opword 0x60002000
		opword 0x901E0008
		opword 0x386000C8
		bl sysMsec2Frame
		opword 0x907E0024
		opword 0x3800000B
		opword 0x981E0038
		opword 0x807E0024
		opword 0x3403FFFF
		opword 0x901E0024
		opword 0x41810380
		lfs f1, float_15_8041b154(r2)
		opword 0x3800000C
		lfs f0, float_0_8041b100(r2)
		opword 0xD03E0114
		opword 0xD01E0118
		opword 0x981E0038
		opword 0xC03E005C
		opword 0x38610044
		opword 0xC01E0114
		opword 0x3881001C
		opword 0x38A10018
		opword 0x38C10014
		opword 0xEC01002A
		opword 0xD01E005C
		opword 0x80FE0058
		opword 0x801E005C
		opword 0x90E10044
		opword 0x90010048
		opword 0x801E0060
		opword 0x9001004C
		bl marioGetScreenPos
		opword 0x80FF008C
		opword 0x38610038
		opword 0x801F0090
		opword 0x38810010
		opword 0x38A1000C
		opword 0x38C10008
		opword 0x90E10038
		opword 0x9001003C
		opword 0x801F0094
		opword 0x90010040
		bl marioGetScreenPos
		opword 0xC021000C
		lfs f0, float_neg100_8041b158(r2)
		opword 0xFC010040
		opword 0x40800008
		opword 0x48000008
		opword 0xFC200090
		opword 0xC0010018
		opword 0xFC000840
		opword 0x4C401382
		opword 0x408202D8
		opword 0x38600020
		opword 0x38000014
		opword 0x907E0024
		opword 0x981E0038
		opword 0x480002C4
		opword 0x80FE0058
		opword 0x3861002C
		opword 0x801E005C
		opword 0x3881001C
		opword 0x38A10018
		opword 0x38C10014
		opword 0x90E1002C
		opword 0x90010030
		opword 0x801E0060
		opword 0x90010034
		bl marioGetScreenPos
		opword 0xC0210018
		lfs f0, float_neg100_8041b158(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820014
		opword 0xC03E005C
		lfs f0, float_1_8041b0e8(r2)
		opword 0xEC01002A
		opword 0xD01E005C
		opword 0xA01F002E
		opword 0x2800001F
		opword 0x40820014
		bl marioWaitDamageReturnFall
		opword 0x2C030000
		opword 0x4182025C
		opword 0x48000018
		opword 0x28000020
		opword 0x40820010
		bl marioWaitDamageTogeReturnFall
		opword 0x2C030000
		opword 0x41820244
		opword 0x38000015
		opword 0x981E0038
		opword 0x807E0024
		opword 0x3403FFFF
		opword 0x901E0024
		opword 0x4181022C
		opword 0x7FC3F378
		opword 0x38810050
		bl partyGetAppearPos
		opword 0xC0010050
		opword 0x38000016
		lfs f1, float_0_8041b100(r2)
		opword 0xD01E0058
		lfs f0, float_neg1_8041b0ec(r2)
		opword 0xC0410058
		opword 0xD05E0060
		opword 0xD03E0114
		opword 0xD01E0118
		opword 0xD03E0104
		opword 0x807E0000
		opword 0x60630020
		opword 0x907E0000
		opword 0x807E0000
		opword 0x64630200
		opword 0x907E0000
		opword 0x981E0038
		opword 0x480001D8
		opword 0x80FE0058
		opword 0x38610020
		opword 0x801E005C
		opword 0x3881001C
		opword 0x38A10018
		opword 0x38C10014
		opword 0x90E10020
		opword 0x90010024
		opword 0x801E0060
		opword 0x90010028
		bl marioGetScreenPos
		opword 0xC0210018
		lfs f0, float_240_8041b15c(r2)
		opword 0xFC010040
		opword 0x40810010
		opword 0x801E0000
		opword 0x540001CA
		opword 0x901E0000
		opword 0x7FC3F378
		bl partyMove
		opword 0xC01E0114
		lfs f1, float_neg6_8041b160(r2)
		opword 0xFC000840
		opword 0x4C401382
		opword 0x40820010
		lfs f0, float_0_8041b100(r2)
		opword 0xD01E0118
		opword 0xD03E0114
		opword 0xC03E005C
		lfs f0, float_neg2000_8041b164(r2)
		opword 0xFC010040
		opword 0x40800038
		opword 0x807F008C
		opword 0x801F0090
		lfs f0, float_200_8041b168(r2)
		opword 0x907E0058
		opword 0x901E005C
		opword 0x801F0094
		opword 0x901E0060
		opword 0xC03E005C
		opword 0xEC01002A
		opword 0xD01E005C
		opword 0x801E0000
		opword 0x54000730
		opword 0x901E0000
		opword 0x807E0138
		opword 0x28030000
		opword 0x41820118
		bl hitGetAttr
		opword 0x5460BFFF
		opword 0x4082010C
		opword 0x801E0004
		opword 0x540007BD
		opword 0x408200BC
		opword 0x881E0031
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800008
		bl partyGetHp
		opword 0x801E0004
		opword 0x54000421
		opword 0x40820024
		opword 0x889E0031
		lis r3, partyPoseTbl@ha
		addi r0, r3, partyPoseTbl@l
		opword 0x7C830774
		opword 0x1C63003C
		opword 0x7C601A14
		opword 0x83A30024
		opword 0x48000048
		opword 0x881E0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x4182001C
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		addi r0, r3, partyDotPoseTbl@l
		opword 0x7C602214
		opword 0x83A30024
		opword 0x48000020
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		addi r0, r3, yoshiDotPoseTbl@l
		opword 0x7C602214
		opword 0x83A30024
		opword 0x807E0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93BE0018
		opword 0x38000000
		opword 0xB01E0020
		opword 0x801E0008
		opword 0x60002000
		opword 0x901E0008
		opword 0x38600017
		opword 0x3800001E
		opword 0x987E0038
		opword 0x901E0024
		opword 0x48000034
		opword 0x807E0024
		opword 0x3403FFFF
		opword 0x901E0024
		opword 0x41810024
		opword 0x7FC3F378
		opword 0x38800002
		bl partyChgRunMode
		opword 0x38000000
		opword 0x981E003B
		opword 0x801E0004
		opword 0x54000734
		opword 0x901E0004
		bl vivianGetStatus
		opword 0x2C030002
		opword 0x4182000C
		opword 0x7FC3F378
		bl vivianShadow
		opword 0x80010074
		opword 0x83E1006C
		opword 0x83C10068
		opword 0x83A10064
		opword 0x7C0803A6
		opword 0x38210070
	}
}
#pragma pop

void partyInitCamId(PartyEntry* party) {
    party->camId = marioGetCamId();
}

void partySetCamId(PartyEntry* party, s32 cameraId) {
    party->camId = cameraId;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void partyMakeDispDir(PartyEntry* party) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0x93E1000C
		opword 0x7C7F1B78
		opword 0x80630004
		opword 0x546005EF
		opword 0x40820310
		opword 0x546006F7
		opword 0x408200D4
		opword 0xC03F00FC
		opword 0xC01F00F8
		opword 0xEC210028
		bl revise360
		opword 0x801F0004
		opword 0xC07F0110
		opword 0x540005EF
		opword 0x40820030
		lfs f0, float_290_8041b128(r2)
		opword 0xFC001800
		opword 0x41820010
		lfs f0, float_250_8041b12c(r2)
		opword 0xFC001800
		opword 0x40820018
		lfs f3, float_180_8041b0fc(r2)
		opword 0xFC011840
		opword 0x4C411382
		opword 0x40820008
		lfs f3, float_0_8041b100(r2)
		opword 0xC01F0104
		lfs f2, float_0_8041b100(r2)
		opword 0xFC001000
		opword 0x41820050
		lfs f0, float_190_8041b130(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082001C
		lfs f0, float_350_8041b134(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082000C
		opword 0xFC601090
		opword 0x48000028
		lfs f0, float_10_8041b124(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820018
		lfs f0, float_170_8041b138(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820008
		lfs f3, float_180_8041b0fc(r2)
		opword 0xD07F0110
		opword 0x801F0004
		opword 0x540006B5
		opword 0x4182000C
		opword 0xC01F0110
		opword 0xD01F010C
		opword 0xC03F010C
		opword 0xC01F0110
		opword 0xFC010000
		opword 0x41820238
		opword 0xC05F010C
		lfs f1, float_180_8041b0fc(r2)
		opword 0xFC020840
		opword 0x4C401382
		opword 0x40820114
		lfs f0, float_0_8041b100(r2)
		opword 0xC07F0110
		opword 0xFC001800
		opword 0x40820080
		opword 0x801F0008
		lfs f1, float_0p125_8041b13c(r2)
		opword 0x540004E7
		opword 0x4182000C
		lfs f0, float_20_8041b140(r2)
		opword 0x48000008
		lfs f0, float_neg40_8041b144(r2)
		opword 0xEC001028
		opword 0xEC010032
		opword 0xEC02002A
		opword 0xD01F010C
		opword 0x807F0008
		opword 0x546004E7
		opword 0x40820020
		opword 0xC03F010C
		lfs f0, float_neg30_8041b148(r2)
		opword 0xFC010040
		opword 0x408001CC
		opword 0x60601000
		opword 0x901F0008
		opword 0x480001C0
		opword 0xC03F010C
		lfs f0, float_0_8041b100(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x408201AC
		opword 0xD01F010C
		opword 0x801F0008
		opword 0x54000524
		opword 0x901F0008
		opword 0x48000198
		opword 0xFC011800
		opword 0x40820190
		opword 0x801F0008
		lfs f1, float_0p125_8041b13c(r2)
		opword 0x540004E7
		opword 0x4182000C
		lfs f0, float_170_8041b138(r2)
		opword 0x48000008
		lfs f0, float_220_8041b14c(r2)
		opword 0xEC001028
		opword 0xEC010032
		opword 0xEC02002A
		opword 0xD01F010C
		opword 0x807F0008
		opword 0x546004E7
		opword 0x40820020
		opword 0xC03F010C
		lfs f0, float_210_8041b150(r2)
		opword 0xFC010040
		opword 0x40810148
		opword 0x60601000
		opword 0x901F0008
		opword 0x4800013C
		opword 0xC03F010C
		lfs f0, float_180_8041b0fc(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820128
		opword 0xD01F010C
		opword 0x801F0008
		opword 0x54000524
		opword 0x901F0008
		opword 0x48000114
		opword 0xFC020840
		opword 0x4081010C
		lfs f0, float_0_8041b100(r2)
		opword 0xC07F0110
		opword 0xFC001800
		opword 0x40820080
		opword 0x801F0008
		lfs f1, float_0p125_8041b13c(r2)
		opword 0x540004E7
		opword 0x4182000C
		lfs f0, float_20_8041b140(r2)
		opword 0x48000008
		lfs f0, float_neg40_8041b144(r2)
		opword 0xEC001028
		opword 0xEC010032
		opword 0xEC02002A
		opword 0xD01F010C
		opword 0x807F0008
		opword 0x546004E7
		opword 0x40820020
		opword 0xC03F010C
		lfs f0, float_neg30_8041b148(r2)
		opword 0xFC010040
		opword 0x408000B4
		opword 0x60601000
		opword 0x901F0008
		opword 0x480000A8
		opword 0xC03F010C
		lfs f0, float_0_8041b100(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820094
		opword 0xD01F010C
		opword 0x801F0008
		opword 0x54000524
		opword 0x901F0008
		opword 0x48000080
		opword 0xFC011800
		opword 0x40820078
		opword 0x801F0008
		lfs f1, float_0p125_8041b13c(r2)
		opword 0x540004E7
		opword 0x4182000C
		lfs f0, float_170_8041b138(r2)
		opword 0x48000008
		lfs f0, float_220_8041b14c(r2)
		opword 0xEC001028
		opword 0xEC010032
		opword 0xEC02002A
		opword 0xD01F010C
		opword 0x807F0008
		opword 0x546004E7
		opword 0x40820040
		opword 0xC03F010C
		lfs f0, float_210_8041b150(r2)
		opword 0xFC010040
		opword 0x40810010
		opword 0x60601000
		opword 0x901F0008
		opword 0x48000024
		lfs f0, float_180_8041b0fc(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820014
		opword 0xD01F010C
		opword 0x801F0008
		opword 0x54000524
		opword 0x901F0008
		opword 0x80010014
		opword 0x83E1000C
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
void partyPreDisp(PartyEntry* party) {
	char _af_pad[72];
	asm volatile {
		opword 0x80030004
		mr r30, r3
		opword 0x540006F7
		opword 0x40820014
		opword 0x801E0000
		opword 0x540005AD
		opword 0x40820008
		bl partyMakeDispDir
		opword 0x807E0008
		opword 0x54600465
		opword 0x4182007C
		opword 0x546004A5
		opword 0x4182000C
		opword 0x546004E2
		opword 0x901E0008
		opword 0x807E0008
		opword 0x54600463
		opword 0x4182000C
		opword 0x546004A0
		opword 0x901E0008
		opword 0x807E000C
		opword 0x38A00001
		opword 0x809E0018
		bl animPoseSetAnim
		opword 0x809E001C
		opword 0x28040000
		opword 0x41820010
		opword 0x807E000C
		opword 0x38A00001
		bl animPoseSetPaperAnim
		opword 0xA0BE0020
		opword 0x3C004330
		lis r3, double_to_int_mask_802ccef8@ha
		stw r0, _af_pad+64(r1)
		addi r4, r3, double_to_int_mask_802ccef8@l
		opword 0x807E000C
		opword 0x90A1004C
		opword 0xC8240000
		opword 0xC8010048
		opword 0xEC200828
		bl animPoseSetLocalTime
		opword 0x807E000C
		bl animPoseMain
		opword 0x801E0004
		opword 0x540007FF
		opword 0x40820228
		opword 0x809E0058
		opword 0x38600004
		opword 0x801E005C
		opword 0x9081003C
		opword 0x90010040
		opword 0x801E0060
		opword 0x90010044
		bl camGetPtr
		opword 0x3881003C
		opword 0x3863015C
		opword 0x7C852378
		bl PSMTX44MultVec
		lfs f2, float_5000_8041b114(r2)
		opword 0xC0210044
		lfs f0, float_0_8041b100(r2)
		opword 0xEC22107A
		opword 0xFC010040
		opword 0x4080000C
		opword 0xFC200090
		opword 0x48000014
		lfs f0, float_10000_8041b118(r2)
		opword 0xFC010040
		opword 0x40810008
		opword 0xFC200090
		lfs f0, float_neg1_8041b0ec(r2)
		opword 0xA81E002A
		opword 0xEC210032
		opword 0x2C000000
		opword 0x40810028
		opword 0x540007BD
		opword 0x40820038
		lis r3, partyDisp@ha
		opword 0x7FC6F378
		addi r5, r3, partyDisp@l
		opword 0x807E0164
		opword 0x38800001
		bl dispEntry
		opword 0x4800001C
		lis r3, partyDisp@ha
		opword 0x7FC6F378
		addi r5, r3, partyDisp@l
		opword 0x807E0164
		opword 0x38800001
		bl dispEntry
		opword 0x881E0031
		opword 0x3BE00002
		lfs f31, float_13p333_8041b11c(r2)
		opword 0x2C000006
		opword 0x41820020
		opword 0x807E0058
		opword 0x801E005C
		opword 0x907E00B8
		opword 0x901E00BC
		opword 0x801E0060
		opword 0x901E00C0
		opword 0x48000058
		opword 0x881E0034
		opword 0x28000004
		opword 0x41820018
		opword 0x28000008
		opword 0x40820028
		opword 0x801E0000
		opword 0x540005EF
		opword 0x4082001C
		opword 0x807E0058
		opword 0x801E005C
		opword 0x907E00B8
		opword 0x901E00BC
		opword 0x801E0060
		opword 0x901E00C0
		opword 0x807E0000
		opword 0x546005EF
		opword 0x41820014
		opword 0x54600001
		opword 0xC3FE0174
		opword 0x41820008
		opword 0x3BE00001
		opword 0x7FC3F378
		bl N_vivianDisplayTailCheck
		opword 0x2C030000
		opword 0x41820094
		lfs f1, float_1000_8041b120(r2)
		lis r3, vec3_802ccee0@ha
		addi r11, r3, vec3_802ccee0@l
		lfs f0, float_10_8041b124(r2)
		opword 0xD0210008
		opword 0x7FC3F378
		opword 0x814B0000
		opword 0x38810030
		opword 0x819E0058
		opword 0x38A10024
		opword 0x801E005C
		opword 0x38C10018
		opword 0x812B0004
		opword 0x38E1000C
		opword 0x90010034
		opword 0x39010008
		opword 0x800B0008
		opword 0xC0210034
		opword 0x91810030
		opword 0xEC01002A
		opword 0x817E0060
		opword 0x91610038
		opword 0xD0010034
		opword 0x91410024
		opword 0x91210028
		opword 0x9001002C
		bl partyHitCheck
		opword 0x28030000
		opword 0x4182000C
		opword 0xC001001C
		opword 0x48000008
		opword 0xC01E005C
		opword 0xD01E00BC
		opword 0x389E00B8
		opword 0x807E000C
		bl animPoseVivianMain
		opword 0x801E0004
		opword 0x540002D7
		opword 0x40820048
		opword 0xFC80F890
		opword 0xC03E00B8
		opword 0xC05E00BC
		opword 0x7FE3FB78
		opword 0xC07E00C0
		bl shadowEntryMode
		opword 0x809E0164
		opword 0x7C7F1B78
		opword 0x2C040004
		opword 0x41820008
		bl shadowSetCamId
		opword 0x801E0004
		opword 0x54000295
		opword 0x41820010
		opword 0x7FE3FB78
		opword 0x38800004
		bl shadowFlagOn
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void partyDisp(CameraId cam, void* param) {
	asm volatile {
		opword 0x9421FF60
		opword 0x7C0802A6
		la r5, partyPtrTbl(r13)
		opword 0x38600000
		opword 0x900100A4
		opword 0x93E1009C
		opword 0x7C9F2378
		lwz r4, partyPtrTbl(r13)
		opword 0x28040000
		opword 0x41820024
		opword 0x2C030000
		opword 0x41800008
		opword 0x48000008
		opword 0x7C641B78
		opword 0x80040000
		opword 0x540007FF
		opword 0x41820008
		opword 0x38600001
		opword 0x80850004
		opword 0x38000001
		opword 0x28040000
		opword 0x41820024
		opword 0x2C000000
		opword 0x41800008
		opword 0x48000008
		opword 0x38800000
		opword 0x80040000
		opword 0x540007FF
		opword 0x41820008
		opword 0x38630001
		opword 0x2C030000
		opword 0x41820378
		opword 0x801F0000
		opword 0x540005AD
		opword 0x41820014
		lfs f1, float_neg6p8_8041b0d8(r2)
		lfs f0, float_6p8_8041b0dc(r2)
		opword 0xD03F0088
		opword 0xD01F008C
		opword 0x801F0000
		opword 0x54000211
		opword 0x4182000C
		lfs f3, float_1p2_8041b0e0(r2)
		opword 0x48000008
		lfs f3, float_2_8041b0e4(r2)
		opword 0xC03F0070
		opword 0x38610068
		opword 0xC05F0074
		opword 0xC01F0078
		opword 0xEC2100F2
		opword 0xEC4200F2
		opword 0xEC6000F2
		bl PSMTXScale
		opword 0x801F0004
		opword 0x54000739
		opword 0x4082006C
		opword 0xC03F010C
		bl revise360
		opword 0xFC600890
		lfs f0, float_90_8041b0f0(r2)
		lfs f1, float_1_8041b0e8(r2)
		opword 0x38610008
		opword 0x38000000
		opword 0xFC030040
		opword 0xFC400890
		opword 0x4C411382
		opword 0x40820018
		lfs f0, float_270_8041b0f4(r2)
		opword 0xFC030040
		opword 0x4C401382
		opword 0x40820008
		opword 0x38000001
		opword 0x2C000000
		opword 0x4182000C
		lfs f3, float_neg1_8041b0ec(r2)
		opword 0x48000008
		lfs f3, float_1_8041b0e8(r2)
		bl PSMTXScale
		opword 0x38810068
		opword 0x38610008
		opword 0x7C852378
		bl PSMTXConcat
		opword 0xC03F0088
		opword 0x38610038
		opword 0xC05F008C
		opword 0xC01F0090
		opword 0xFC200850
		opword 0xFC401050
		opword 0xFC600050
		bl PSMTXTrans
		opword 0x38810068
		opword 0x38610038
		opword 0x7C852378
		bl PSMTXConcat
		lfs f1, float_deg2rad_8041b0f8(r2)
		opword 0x38610038
		opword 0xC01F006C
		opword 0x3880007A
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x38810068
		opword 0x38610038
		opword 0x7C852378
		bl PSMTXConcat
		lfs f1, float_deg2rad_8041b0f8(r2)
		opword 0x38610038
		opword 0xC01F0064
		opword 0x38800078
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x38810068
		opword 0x38610038
		opword 0x7C852378
		bl PSMTXConcat
		opword 0xC03F010C
		opword 0xC01F00F8
		opword 0xEC210028
		bl revise360
		lfs f0, float_deg2rad_8041b0f8(r2)
		opword 0x38610038
		opword 0x38800079
		opword 0xEC200072
		bl PSMTXRotRad
		opword 0x38810068
		opword 0x38610038
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x801F0004
		opword 0x54000633
		opword 0x418200A8
		opword 0xC03F010C
		bl revise360
		lfs f0, float_90_8041b0f0(r2)
		opword 0xFC010040
		opword 0x4C411382
		opword 0x40820054
		lfs f0, float_270_8041b0f4(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820044
		opword 0x801F0004
		opword 0x38610038
		lfs f1, float_deg2rad_8041b0f8(r2)
		opword 0x38800079
		opword 0x54000673
		opword 0x4182000C
		lfs f0, float_180_8041b0fc(r2)
		opword 0x48000008
		lfs f0, float_0_8041b100(r2)
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x38810068
		opword 0x38610038
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x48000040
		opword 0x801F0004
		opword 0x38610038
		lfs f1, float_deg2rad_8041b0f8(r2)
		opword 0x38800079
		opword 0x54000673
		opword 0x4182000C
		lfs f0, float_0_8041b100(r2)
		opword 0x48000008
		lfs f0, float_180_8041b0fc(r2)
		opword 0xEC210032
		bl PSMTXRotRad
		opword 0x38810068
		opword 0x38610038
		opword 0x7C852378
		bl PSMTXConcat
		opword 0xC03F0088
		opword 0x38610038
		opword 0xC05F008C
		opword 0xC07F0090
		bl PSMTXTrans
		opword 0x38810068
		opword 0x38610038
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x801F001C
		lfs f5, float_0_8041b100(r2)
		opword 0x28000000
		opword 0x41820088
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x4082000C
		lfs f5, float_1_8041b0e8(r2)
		opword 0x48000070
		opword 0x2C000003
		opword 0x4082000C
		lfs f5, float_2_8041b0e4(r2)
		opword 0x48000060
		opword 0x2C000007
		opword 0x4082000C
		lfs f5, float_2_8041b0e4(r2)
		opword 0x48000050
		opword 0x2C000001
		opword 0x4082000C
		lfs f5, float_2_8041b0e4(r2)
		opword 0x48000040
		opword 0x2C00000B
		opword 0x4082000C
		lfs f5, float_3_8041b104(r2)
		opword 0x48000030
		opword 0x2C000008
		opword 0x4082000C
		lfs f5, float_3p5_8041b108(r2)
		opword 0x48000020
		opword 0x2C00000A
		opword 0x4082000C
		lfs f5, float_4_8041b10c(r2)
		opword 0x48000010
		opword 0x2C000009
		opword 0x40820008
		lfs f5, float_neg1_8041b0ec(r2)
		opword 0xC03F005C
		opword 0x38610038
		opword 0xC01F0080
		opword 0xC09F0058
		opword 0xEC41002A
		opword 0xC03F007C
		opword 0xC07F0060
		opword 0xC01F0084
		opword 0xEC24082A
		opword 0xEC45102A
		opword 0xEC63002A
		bl PSMTXTrans
		opword 0x38810068
		opword 0x38610038
		opword 0x7C852378
		bl PSMTXConcat
		opword 0x807F000C
		opword 0x38810068
		lfs f1, float_0_8041b100(r2)
		opword 0x38A00002
		lfs f2, float_1_8041b0e8(r2)
		bl animPoseDrawMtx
		opword 0x807F000C
		opword 0x38810068
		lfs f1, float_0_8041b100(r2)
		opword 0x38A00001
		lfs f2, float_1_8041b0e8(r2)
		bl animPoseDrawMtx
		opword 0x801F0000
		opword 0x807F000C
		opword 0x54000631
		opword 0x4182000C
		lfs f1, float_0p75_8041b110(r2)
		opword 0x48000008
		lfs f1, float_1_8041b0e8(r2)
		bl animPoseSetLocalTimeRate
		opword 0x800100A4
		opword 0x83E1009C
		opword 0x7C0803A6
		opword 0x382100A0
	}
}
#pragma pop

void partyKeyOn(void) {
}

void partyKeyOff(void) {
}

void L_partyClearCont(PartyEntry* party) {
    PS8(party, 0x158) = 0;
    PS8(party, 0x159) = 0;
    PS8(party, 0x15A) = 0;
    PS8(party, 0x15B) = 0;
    PS8(party, 0x15C) = 0;
    PS8(party, 0x15D) = 0;
    PS8(party, 0x15E) = 0;
    PS8(party, 0x15F) = 0;
    PU16(party, 0x150) = 0;
    PU16(party, 0x152) = 0;
    PU16(party, 0x154) = 0;
    PU16(party, 0x156) = 0;
}

void partyUpdateKeyData(PartyEntry* party) {
    s32 port = PS8(party, 0x30);
    if (party->flags & 0x60000000) {
        L_partyClearCont(party);
        return;
    }
    PS8(party, 0x158) = gp->stickX[port];
    PS8(party, 0x159) = -gp->stickY[port];
    PS8(party, 0x15A) = gp->substickX[port];
    PS8(party, 0x15B) = -gp->substickY[port];
    PS8(party, 0x15C) = gp->triggerLeft[port];
    PS8(party, 0x15D) = gp->triggerRight[port];
    PS8(party, 0x15E) = 0;
    PS8(party, 0x15F) = 0;
    PU16(party, 0x150) = gp->button[port];
    PU16(party, 0x152) = gp->buttonNew[port];
    PU16(party, 0x154) = gp->buttonRepeat[port];
    PU16(party, 0x156) = gp->buttonUp[port];
}

void partyShadowOff(PartyEntry* party) {
    if (party) {
        party->flags2 |= 0x100000;
    }
}

#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void partySetFamicomMode(PartyEntry* party, s32 mode) {
	asm {
		cmpwi r4, 0x1
		mr r31, r3
	}
	asm volatile {
		opword 0x408201E4
		opword 0x801F0004
		opword 0x54000421
		opword 0x408203AC
		bl L_partyForceSlitOff
		opword 0x801F0004
		opword 0x60008000
		opword 0x901F0004
		opword 0x881F0031
		opword 0x2C000004
		opword 0x41820028
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820010
		lwz r3, party_dp(r13)
		opword 0x83C30000
		opword 0x48000038
		lis r3, str_802CCEEC@ha
		addi r30, r3, str_802CCEEC@l
		opword 0x4800002C
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x801F0004
		opword 0x5464103A
		la r3, yoshigroup(r13)
		opword 0x54000421
		opword 0x7FC3202E
		opword 0x4182000C
		lis r3, str_802CCEEC@ha
		addi r30, r3, str_802CCEEC@l
		opword 0x807F000C
		opword 0x2C030000
		opword 0x41800008
		bl animPoseRelease
		opword 0x7FC3F378
		opword 0x38800002
		bl animPoseEntry
		opword 0x907F000C
		opword 0x3BC00001
		opword 0x801F0004
		opword 0x540007BD
		opword 0x4182000C
		opword 0x83DF0018
		opword 0x480000E8
		opword 0x881F0031
		li r29, 0x0
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3BA00001
		opword 0x2C1D0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889F0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820018
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		opword 0x801F0004
		opword 0x540007BD
		opword 0x4082021C
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x41820200
		opword 0x801F0004
		opword 0x54000421
		opword 0x408201F4
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		opword 0x480001D8
		opword 0x807F0004
		opword 0x54600421
		opword 0x418201CC
		opword 0x5460045E
		opword 0x901F0004
		opword 0x881F0031
		opword 0x2C000004
		opword 0x41820028
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820010
		lwz r3, party_dp(r13)
		opword 0x83C30000
		opword 0x48000038
		lis r3, str_802CCEEC@ha
		addi r30, r3, str_802CCEEC@l
		opword 0x4800002C
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x801F0004
		opword 0x5464103A
		la r3, yoshigroup(r13)
		opword 0x54000421
		opword 0x7FC3202E
		opword 0x4182000C
		lis r3, str_802CCEEC@ha
		addi r30, r3, str_802CCEEC@l
		opword 0x807F000C
		opword 0x2C030000
		opword 0x41800008
		bl animPoseRelease
		opword 0x7FC3F378
		opword 0x38800002
		bl animPoseEntry
		opword 0x907F000C
		opword 0x3BC00001
		opword 0x801F0004
		opword 0x540007BD
		opword 0x4182000C
		opword 0x83DF0018
		opword 0x480000E8
		opword 0x881F0031
		opword 0x3BA00000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3BA00001
		opword 0x2C1D0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889F0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820018
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		opword 0x801F0004
		opword 0x540007BD
		opword 0x40820044
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x41820028
		opword 0x801F0004
		opword 0x54000421
		opword 0x4082001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
	}
}
#pragma pop

#pragma defer_codegen reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm s32 partyDokanMain(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lis r3, vec3_802ccd30@ha
	lbz r0, 0x38(r30)
	addi r31, r3, vec3_802ccd30@l
	lwz r4, 0x160(r30)
	cmpwi r0, 0x64
	beq L_af_1
	bge L_af_2
	cmpwi r0, 0xa
	beq L_af_3
	bge L_af_4
	cmpwi r0, 0x0
	beq L_af_5
	b L_af_4
L_af_2:
	cmpwi r0, 0x66
	beq L_af_6
	bge L_af_4
	b L_af_7
L_af_5:
	lwz r3, 0x8c(r4)
	lwz r0, 0x90(r4)
	stw r3, 0x58(r30)
	stw r0, 0x5c(r30)
	lwz r0, 0x94(r4)
	stw r0, 0x60(r30)
	lfs f1, 0x10c(r30)
	lfs f0, 0x124(r30)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x10c(r30)
	lfs f1, float_0p05_8041b198(r2)
	lfs f2, 0x70(r30)
	lfs f0, float_1_8041b0e8(r2)
	fadds f1, f2, f1
	stfs f1, 0x70(r30)
	lfs f1, 0x70(r30)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne L_af_8
	stfs f0, 0x70(r30)
L_af_8:
	lfs f0, 0x70(r30)
	stfs f0, 0x74(r30)
	lfs f0, 0x70(r30)
	stfs f0, 0x78(r30)
	b L_af_4
L_af_3:
	lfs f1, 0x64(r30)
	lfs f0, 0x124(r30)
	fadds f0, f1, f0
	stfs f0, 0x64(r30)
	b L_af_4
L_af_1:
	lbz r0, 0x2e(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq L_af_9
	bge L_af_4
	cmpwi r0, 0x2
	bge L_af_4
	cmpwi r0, 0x0
	bge L_af_10
	b L_af_4
L_af_10:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne L_af_11
	lwz r3, 0x1c(r30)
	cmplwi r3, 0x0
	beq L_af_12
	addi r4, r31, 0x1d8
	bl strcmp
	cmpwi r3, 0x0
	beq L_af_11
L_af_12:
	addi r3, r31, 0x1d8
	li r0, 0x0
	stw r3, 0x1c(r30)
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x4000
	stw r0, 0x8(r30)
L_af_11:
	li r3, 0x12
	li r0, 0x65
	stw r3, 0x24(r30)
	stb r0, 0x38(r30)
	b L_af_4
L_af_9:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne L_af_13
	lwz r3, 0x1c(r30)
	cmplwi r3, 0x0
	beq L_af_14
	addi r4, r31, 0x1d8
	bl strcmp
	cmpwi r3, 0x0
	beq L_af_13
L_af_14:
	addi r3, r31, 0x1d8
	li r0, 0x0
	stw r3, 0x1c(r30)
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x4000
	stw r0, 0x8(r30)
L_af_13:
	li r3, 0x12
	li r0, 0x65
	stw r3, 0x24(r30)
	stb r0, 0x38(r30)
	b L_af_4
L_af_7:
	lbz r0, 0x2e(r30)
	extsb r0, r0
	cmpwi r0, 0x2
	bge L_af_15
	cmpwi r0, 0x0
	bge L_af_16
	b L_af_15
L_af_16:
	lfs f1, 0x60(r30)
	lfs f0, float_neg0p2_8041b19c(r2)
	fadds f0, f1, f0
	stfs f0, 0x60(r30)
L_af_15:
	lwz r3, 0x24(r30)
	subic. r0, r3, 0x1
	stw r0, 0x24(r30)
	bgt L_af_4
	li r0, 0x66
	stb r0, 0x38(r30)
	b L_af_4
L_af_6:
	lwz r3, 0x12c(r31)
	lwz r0, 0x130(r31)
	stw r3, 0x70(r30)
	stw r0, 0x74(r30)
	lwz r0, 0x134(r31)
	stw r0, 0x78(r30)
	lwz r3, 0x138(r31)
	lwz r0, 0x13c(r31)
	stw r3, 0x64(r30)
	stw r0, 0x68(r30)
	lwz r0, 0x140(r31)
	stw r0, 0x6c(r30)
	lwz r3, 0x144(r31)
	lwz r0, 0x148(r31)
	stw r3, 0x88(r30)
	stw r0, 0x8c(r30)
	lwz r0, 0x14c(r31)
	stw r0, 0x90(r30)
	lwz r3, 0x150(r31)
	lwz r0, 0x154(r31)
	stw r3, 0x7c(r30)
	stw r0, 0x80(r30)
	lwz r0, 0x158(r31)
	stw r0, 0x84(r30)
	lfs f0, 0x1ac(r4)
	stfs f0, 0x110(r30)
	lfs f0, 0x110(r30)
	stfs f0, 0x10c(r30)
	lfs f0, 0x1a0(r4)
	stfs f0, 0x100(r30)
	lfs f0, 0x1a0(r4)
	stfs f0, 0xfc(r30)
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 5, 5
	beq L_af_17
	lwz r0, 0x1c(r30)
	cmplwi r0, 0x0
	beq L_af_17
	lwz r3, 0xc(r30)
	li r4, 0x0
	li r5, 0x0
	bl animPoseSetPaperAnimGroup
	li r0, 0x0
	stw r0, 0x1c(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 6, 4
	stw r0, 0x4(r30)
	lwz r3, 0x14(r30)
	cmpwi r3, 0x0
	blt L_af_17
	bl animPaperPoseRelease
	li r0, -0x1
	stw r0, 0x14(r30)
L_af_17:
	lwz r3, 0xc(r30)
	li r4, 0x1
	bl animPoseSetMaterialLightFlagOn
	lwz r0, 0x4(r30)
	cmplwi r30, 0x0
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x4(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 6, 4
	stw r0, 0x0(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 7, 5
	stw r0, 0x0(r30)
	beq L_af_18
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x4(r30)
L_af_18:
	mr r3, r30
	bl L_partyVivianTailStart
	lwz r5, 0x58(r30)
	mr r3, r30
	lwz r0, 0x5c(r30)
	li r4, 0x1
	stw r5, 0xb8(r30)
	stw r0, 0xbc(r30)
	lwz r0, 0x60(r30)
	stw r0, 0xc0(r30)
	bl partyChgRunMode
	li r31, 0x0
	bl marioGetPartyId
	cmpwi r3, 0x0
	blt L_af_19
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r0, r3, r0
	b L_af_20
L_af_19:
	li r0, 0x0
L_af_20:
	cmplwi r0, 0x0
	beq L_af_21
	li r31, 0x1
L_af_21:
	bl marioGetExtraPartyId
	cmpwi r3, 0x0
	blt L_af_22
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r0, r3, r0
	b L_af_23
L_af_22:
	li r0, 0x0
L_af_23:
	cmplwi r0, 0x0
	beq L_af_24
	addi r31, r31, 0x1
L_af_24:
	lbz r0, 0x2e(r30)
	cmpwi r0, 0x4
	bne L_af_25
	cmpwi r31, 0x1
	bne L_af_26
	lfs f1, 0x60(r30)
	lfs f0, float_neg4_8041b1a0(r2)
	fadds f0, f1, f0
	stfs f0, 0x60(r30)
	b L_af_25
L_af_26:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne L_af_27
	lfs f2, 0x60(r30)
	lfs f1, float_neg4_8041b1a0(r2)
	lfs f0, float_1p5_8041b1a4(r2)
	fadds f1, f2, f1
	stfs f1, 0x60(r30)
	lfs f1, 0x58(r30)
	fadds f0, f1, f0
	stfs f0, 0x58(r30)
	b L_af_25
L_af_27:
	lfs f2, 0x60(r30)
	lfs f1, float_neg3_8041b1a8(r2)
	lfs f0, float_neg1p5_8041b1ac(r2)
	fadds f1, f2, f1
	stfs f1, 0x60(r30)
	lfs f1, 0x58(r30)
	fadds f0, f1, f0
	stfs f0, 0x58(r30)
L_af_25:
	lbz r0, 0x2e(r30)
	cmpwi r0, 0x1
	bne L_af_4
	cmpwi r31, 0x1
	bne L_af_28
	lfs f1, 0x60(r30)
	lfs f0, float_neg4_8041b1a0(r2)
	fadds f0, f1, f0
	stfs f0, 0x60(r30)
	b L_af_4
L_af_28:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne L_af_29
	lfs f2, 0x60(r30)
	lfs f1, float_neg4_8041b1a0(r2)
	lfs f0, float_1p5_8041b1a4(r2)
	fadds f1, f2, f1
	stfs f1, 0x60(r30)
	lfs f1, 0x58(r30)
	fadds f0, f1, f0
	stfs f0, 0x58(r30)
	b L_af_4
L_af_29:
	lfs f2, 0x60(r30)
	lfs f1, float_neg3_8041b1a8(r2)
	lfs f0, float_neg1p5_8041b1ac(r2)
	fadds f1, f2, f1
	stfs f1, 0x60(r30)
	lfs f1, 0x58(r30)
	fadds f0, f1, f0
	stfs f0, 0x58(r30)
L_af_4:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void driveParty(PartyEntry* party) {
	char _af_pad[32];
	asm {
		lis r4, vec3_802ccd30@ha
		addi r31, r4, vec3_802ccd30@l
		mr r30, r3
	}
	asm volatile {
		opword 0x80630160
		opword 0xC0030198
		opword 0xD01E00F8
		opword 0xA89E002A
		opword 0x2C040000
		opword 0x4081000C
		opword 0x3804FFFF
		opword 0xB01E002A
		opword 0x881E0034
		opword 0x2C00000E
		opword 0x41820044
		opword 0x40800014
		opword 0x2C000009
		opword 0x4080000C
		opword 0x2C000004
		opword 0x40800030
		opword 0x801E0000
		opword 0x54000085
		opword 0x41820024
		bl vivianGetStatus
		opword 0x2C030002
		opword 0x4182000C
		opword 0x7FC3F378
		bl vivianShadow
		opword 0x7FC3F378
		bl partyPreDisp
		opword 0x48000640
		opword 0x80030000
		opword 0x5400018D
		opword 0x41820014
		opword 0x801E0000
		opword 0x64000080
		opword 0x901E0000
		opword 0x48000010
		opword 0x801E0000
		opword 0x5400024E
		opword 0x901E0000
		opword 0x38000000
		opword 0x901E0138
		opword 0x901E012C
		opword 0x901E0140
		opword 0x901E0134
		opword 0x901E0130
		opword 0x881E0034
		opword 0x2800000E
		opword 0x41810558
		lis r4, jumptable_803127F0@ha
		opword 0x5400103A
		addi r4, r4, jumptable_803127F0@l
		opword 0x7C04002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x807E0000
		opword 0x54600085
		opword 0x4182000C
		opword 0x546000C7
		opword 0x4182052C
		opword 0x807E0008
		opword 0x54600739
		opword 0x4182011C
		opword 0x54600776
		opword 0x3BA00001
		opword 0x901E0008
		opword 0x801E0004
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881E0031
		li r28, 0x0
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BA0000C
		opword 0x801E0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889E0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57A0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x48000050
		opword 0x881E0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57A0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57A0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x807E0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93BE0018
		opword 0x38000000
		opword 0xB01E0020
		opword 0x801E0008
		opword 0x60002000
		opword 0x901E0008
		lfs f0, float_0_8041b100(r2)
		opword 0x7FC3F378
		opword 0x38800000
		opword 0xD01E0104
		opword 0x801E0000
		opword 0x5400062C
		opword 0x901E0000
		bl partyChgMot
		opword 0x889E0031
		lis r3, partyDataTbl@ha
		addi r0, r3, partyDataTbl@l
		opword 0x7FC3F378
		opword 0x7C840774
		opword 0x1C840028
		opword 0x7C802214
		stw r4, party_dp(r13)
		opword 0x81840008
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x480003D8
		opword 0x807E0000
		opword 0x54600085
		opword 0x4182000C
		opword 0x546000C7
		opword 0x418203C4
		opword 0x7FC3F378
		bl unk_800c7c98
		opword 0x480003B8
		opword 0x807E0000
		opword 0x54600085
		opword 0x4182000C
		opword 0x546000C7
		opword 0x418203A4
		opword 0x889E0031
		lis r3, partyDataTbl@ha
		addi r0, r3, partyDataTbl@l
		opword 0x7FC3F378
		opword 0x7C840774
		opword 0x1C840028
		opword 0x7C802214
		stw r4, party_dp(r13)
		opword 0x81840008
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x48000374
		opword 0x807E0000
		opword 0x54600085
		opword 0x4182000C
		opword 0x546000C7
		opword 0x41820360
		opword 0x7FC3F378
		bl partyForceWalk
		opword 0x48000354
		opword 0x807E0000
		opword 0x54600085
		opword 0x4182000C
		opword 0x546000C7
		opword 0x41820340
		opword 0x889E0031
		lis r3, partyDataTbl@ha
		addi r0, r3, partyDataTbl@l
		opword 0x7C840774
		opword 0x7FC3F378
		opword 0x1C840028
		opword 0x7C802214
		stw r4, party_dp(r13)
		opword 0x801E0000
		opword 0x8184000C
		opword 0x60000100
		opword 0x901E0000
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x48000304
		opword 0x807E0008
		opword 0x54600739
		opword 0x41820164
		opword 0x54600776
		opword 0x901E0008
		opword 0x80BE0160
		opword 0xA005002E
		opword 0x28000016
		opword 0x41820014
		opword 0x28000018
		opword 0x4182000C
		opword 0x28000019
		opword 0x40820010
		opword 0x3800001E
		opword 0x981E0038
		opword 0x48000124
		opword 0x881E0034
		opword 0x28000004
		opword 0x4182000C
		opword 0x28000005
		opword 0x40820074
		opword 0x807E0004
		opword 0x38000000
		opword 0x60630010
		opword 0x907E0004
		opword 0x809F00D8
		opword 0x807F00DC
		opword 0x909E0070
		opword 0x907E0074
		opword 0x807F00E0
		opword 0x907E0078
		opword 0x981E0038
		opword 0xC00501A8
		opword 0xD01E0110
		opword 0xC00501A8
		opword 0xD01E010C
		opword 0x8065008C
		opword 0x80050090
		opword 0x907E0058
		opword 0x901E005C
		opword 0x80050094
		opword 0x901E0060
		opword 0x807E0058
		opword 0x801E005C
		opword 0x907E00B8
		opword 0x901E00BC
		opword 0x801E0060
		opword 0x901E00C0
		opword 0x480000A0
		opword 0x28000007
		opword 0x40820038
		opword 0x809F00E4
		opword 0x38000014
		opword 0x807F00E8
		opword 0x909E0070
		opword 0x907E0074
		opword 0x807F00EC
		opword 0x907E0078
		opword 0x981E0038
		opword 0xC00501A8
		opword 0xD01E0110
		opword 0xC00501A8
		opword 0xD01E010C
		opword 0x48000064
		opword 0x809F00F0
		opword 0x3800000A
		opword 0x807F00F4
		opword 0x909E0070
		opword 0x907E0074
		opword 0x807F00F8
		opword 0x907E0078
		opword 0x981E0038
		opword 0xC00501A8
		opword 0xD01E0110
		opword 0xC00501A8
		opword 0xD01E010C
		opword 0x8065008C
		opword 0x80050090
		opword 0x907E0058
		opword 0x901E005C
		opword 0x80050094
		opword 0x901E0060
		opword 0x807E0058
		opword 0x801E005C
		opword 0x907E00B8
		opword 0x901E00BC
		opword 0x801E0060
		opword 0x901E00C0
		opword 0x801E0000
		opword 0x5400062C
		opword 0x901E0000
		opword 0x7FC3F378
		bl partyHelloMain
		opword 0x4800018C
		opword 0x889E0031
		lis r3, partyDataTbl@ha
		addi r0, r3, partyDataTbl@l
		opword 0x7FC3F378
		opword 0x7C840774
		opword 0x1C840028
		opword 0x7C802214
		stw r4, party_dp(r13)
		opword 0x81840014
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x4800015C
		opword 0x807E0008
		opword 0x54600739
		opword 0x41820020
		opword 0x54600776
		opword 0x7FC3F378
		opword 0x901E0008
		bl partyDokanInit
		opword 0x801E0000
		opword 0x5400062C
		opword 0x901E0000
		opword 0x7FC3F378
		bl partyDokanMain
		opword 0x48000128
		opword 0x807E0000
		opword 0x54600085
		opword 0x4182000C
		opword 0x546000C7
		opword 0x41820114
		opword 0x807E0008
		opword 0x54600739
		opword 0x41820028
		opword 0x54630776
		opword 0x38000000
		opword 0x907E0008
		opword 0x7FC3F378
		opword 0x981E0038
		opword 0x801E0000
		opword 0x5400062C
		opword 0x901E0000
		bl L_partyForceSlitOff
		opword 0x7FC3F378
		bl partyRideMain
		opword 0x480000D8
		opword 0x807E0000
		opword 0x54600085
		opword 0x4182000C
		opword 0x546000C7
		opword 0x418200C4
		opword 0x807E0008
		opword 0x54600739
		opword 0x41820020
		opword 0x54630776
		opword 0x38000000
		opword 0x907E0008
		opword 0x981E0038
		opword 0x801E0000
		opword 0x5400062C
		opword 0x901E0000
		opword 0x7FC3F378
		bl partyRideYoshiMain
		opword 0x48000090
		opword 0x807E0000
		opword 0x54600085
		opword 0x4182000C
		opword 0x546000C7
		opword 0x4182007C
		opword 0x7FC3F378
		bl party_damage_return
		opword 0x48000070
		opword 0x809E0008
		opword 0x54800739
		opword 0x4182000C
		opword 0x54800776
		opword 0x901E0008
		opword 0x881E002F
		opword 0x38C0FFFF
		opword 0x891E0031
		opword 0x38A00000
		opword 0x7C000774
		la r4, partyPtrTbl(r13)
		opword 0x7CE30214
		opword 0x99070243
		opword 0x881E002F
		opword 0x7C000774
		opword 0x7C630214
		opword 0x98C30241
		opword 0x881E002F
		opword 0x7C000774
		opword 0x5400103A
		opword 0x7CA4012E
		opword 0x807E000C
		bl animPoseRelease
		opword 0x7FC4F378
		opword 0x38600000
		bl __memFree
		opword 0x480000A0
		opword 0x7FC3F378
		bl party_kemuri
		opword 0x80FE0058
		la r3, _af_pad+12
		opword 0x801E005C
		opword 0x38810010
		opword 0x38A1000C
		opword 0x38C10008
		opword 0x90E10014
		opword 0x90010018
		opword 0x801E0060
		opword 0x9001001C
		bl marioGetScreenPos
		opword 0xC0210010
		opword 0xC001000C
		opword 0xFC20081E
		opword 0xFC00001E
		opword 0xD8210020
		opword 0xD8010028
		opword 0x80610024
		opword 0x8081002C
		bl marioChkInScreen
		opword 0x2C030000
		opword 0x41820014
		opword 0x801E0004
		opword 0x5400024E
		opword 0x901E0004
		opword 0x48000010
		opword 0x801E0004
		opword 0x64000080
		opword 0x901E0004
		opword 0x809F00CC
		opword 0x7FC3F378
		opword 0x801F00D0
		opword 0x909E00AC
		opword 0x901E00B0
		opword 0x801F00D4
		opword 0x901E00B4
		bl partyPreDisp
	}
}
#pragma pop

#define partyGetPtr partyGetPtr__af_inl
BOOL partyDoWork(void) {
    PartyEntry* party = partyGetPtr(marioGetPtr()->currPartySlotId[0]);
    if (!party) {
        return FALSE;
    }
    if (party->runMode != 0 && party->runMode != 1 && party->runMode != 2) {
        return FALSE;
    }
    marioGetPtr()->baseSpeed = EXT_LIT(float_0_8041b100, 0.0f);
    partyChgRunMode(party, 3);
    return TRUE;
}

#undef partyGetPtr

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void partyHello(PartyEntry* party) {
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		lis r5, vec3_802ccd30@ha
		opword 0x90010014
		addi r6, r5, vec3_802ccd30@l
		opword 0x80830008
		opword 0x54800739
		opword 0x41820164
		opword 0x54800776
		opword 0x90030008
		opword 0x80E30160
		opword 0xA007002E
		opword 0x28000016
		opword 0x41820014
		opword 0x28000018
		opword 0x4182000C
		opword 0x28000019
		opword 0x40820010
		opword 0x3800001E
		opword 0x98030038
		opword 0x48000124
		opword 0x88030034
		opword 0x28000004
		opword 0x4182000C
		opword 0x28000005
		opword 0x40820074
		opword 0x80830004
		opword 0x38000000
		opword 0x60840010
		opword 0x90830004
		opword 0x80A600D8
		opword 0x808600DC
		opword 0x90A30070
		opword 0x90830074
		opword 0x808600E0
		opword 0x90830078
		opword 0x98030038
		opword 0xC00701A8
		opword 0xD0030110
		opword 0xC00701A8
		opword 0xD003010C
		opword 0x8087008C
		opword 0x80070090
		opword 0x90830058
		opword 0x9003005C
		opword 0x80070094
		opword 0x90030060
		opword 0x80830058
		opword 0x8003005C
		opword 0x908300B8
		opword 0x900300BC
		opword 0x80030060
		opword 0x900300C0
		opword 0x480000A0
		opword 0x28000007
		opword 0x40820038
		opword 0x80A600E4
		opword 0x38000014
		opword 0x808600E8
		opword 0x90A30070
		opword 0x90830074
		opword 0x808600EC
		opword 0x90830078
		opword 0x98030038
		opword 0xC00701A8
		opword 0xD0030110
		opword 0xC00701A8
		opword 0xD003010C
		opword 0x48000064
		opword 0x80A600F0
		opword 0x3800000A
		opword 0x808600F4
		opword 0x90A30070
		opword 0x90830074
		opword 0x808600F8
		opword 0x90830078
		opword 0x98030038
		opword 0xC00701A8
		opword 0xD0030110
		opword 0xC00701A8
		opword 0xD003010C
		opword 0x8087008C
		opword 0x80070090
		opword 0x90830058
		opword 0x9003005C
		opword 0x80070094
		opword 0x90030060
		opword 0x80830058
		opword 0x8003005C
		opword 0x908300B8
		opword 0x900300BC
		opword 0x80030060
		opword 0x900300C0
		opword 0x80030000
		opword 0x5400062C
		opword 0x90030000
		bl partyHelloMain
		opword 0x80010014
		opword 0x7C0803A6
		opword 0x38210010
	}
}
#pragma pop

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 partyHelloMain(PartyEntry* party) {
	asm volatile {
		opword 0x9421FFA0
		opword 0x7C0802A6
		opword 0x90010064
		opword 0xDBE10050
		opword 0xF3E10058
		opword 0xDBC10040
		opword 0xF3C10048
		opword 0x93E1003C
		opword 0x93C10038
		opword 0x93A10034
		opword 0x93810030
		opword 0x7C7D1B78
		opword 0x3BE00000
		opword 0x88030038
		opword 0x83C30160
		opword 0x2800001E
		opword 0x41810690
		lis r4, jumptable_80312774@ha
		opword 0x5400103A
		addi r4, r4, jumptable_80312774@l
		opword 0x7C04002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0xC3FE008C
		opword 0x389D0094
		opword 0xC05E0090
		opword 0xC3DE0094
		lfs f1, float_0p5_8041b170(r2)
		opword 0xD3FD0058
		opword 0xC01E01B8
		opword 0xEC01103A
		opword 0xD01D005C
		opword 0xD3DD0060
		bl partyGetAppearPos
		opword 0x38000010
		opword 0xFC20F890
		opword 0x901D0024
		opword 0xFC40F090
		opword 0xC07D0094
		opword 0xC09D009C
		bl distABf
		opword 0xD03D0128
		opword 0xFC20F890
		opword 0xFC40F090
		opword 0xC07D0094
		opword 0xC09D009C
		bl angleABf
		opword 0xD03D0100
		opword 0x3C004330
		lis r3, double_to_int_802ccf00@ha
		lfs f3, float_0p5_8041b170(r2)
		opword 0x80BD0024
		addi r4, r3, double_to_int_802ccf00@l
		opword 0x90010020
		opword 0x6CA38000
		opword 0xC8840000
		opword 0x90610024
		opword 0xC05D0128
		opword 0xC8010020
		opword 0x90010028
		opword 0xEC202028
		lfs f0, float_1_8041b0e8(r2)
		opword 0xEC220824
		opword 0xD03D0104
		opword 0x801D0024
		opword 0xC05D0098
		opword 0x6C008000
		opword 0xC03D005C
		opword 0x9001002C
		opword 0xECA20828
		opword 0xC8210028
		opword 0xEC412028
		opword 0xFC202A10
		opword 0xEC4300B2
		opword 0xFC010040
		opword 0x4080000C
		lfs f5, float_10_8041b124(r2)
		opword 0x48000024
		lfs f0, float_0_8041b100(r2)
		opword 0xFC050040
		opword 0x4C411382
		opword 0x40820010
		opword 0xC01D00F0
		opword 0xECA3283A
		opword 0x48000008
		lfs f5, float_10_8041b124(r2)
		opword 0xEC25282A
		opword 0x38000001
		opword 0xEC0210B8
		opword 0xEC010024
		opword 0xEC2000B2
		opword 0xFC000050
		opword 0xD03D0114
		opword 0xD01D0118
		opword 0x807D0000
		opword 0x60630010
		opword 0x907D0000
		opword 0x981D0038
		opword 0x48000548
		bl partyMoveNoHosei
		opword 0xC03D0114
		lfs f0, float_0_8041b100(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x40820018
		opword 0x801D0000
		lfs f0, float_neg1p6_8041b180(r2)
		opword 0x54000734
		opword 0x901D0000
		opword 0xD01D0118
		opword 0xC03D005C
		lfs f0, float_neg2000_8041b164(r2)
		opword 0xFC010040
		opword 0x40800018
		opword 0x38600000
		opword 0x38000002
		opword 0x907D0024
		opword 0x981D0038
		opword 0x480004F8
		opword 0x801D0138
		opword 0x28000000
		opword 0x40820098
		opword 0x80BD0024
		opword 0x3C004330
		opword 0x90010028
		lis r4, double_to_int_802ccf00@ha
		opword 0x20A50010
		lis r3, vec3_802cce2c@ha
		opword 0x6CA08000
		opword 0x9001002C
		addi r5, r3, vec3_802cce2c@l
		addi r3, r4, double_to_int_802ccf00@l
		opword 0x80850000
		opword 0xC8230000
		opword 0xC8010028
		opword 0x80650004
		opword 0xEC200828
		lfs f0, float_0p0625_8041b184(r2)
		opword 0x80050008
		opword 0x90810014
		opword 0xEC010032
		opword 0x90610018
		opword 0xD0010014
		opword 0x9001001C
		opword 0x80010014
		opword 0xD0010018
		opword 0xD001001C
		opword 0x80610018
		opword 0x901D0070
		opword 0x8001001C
		opword 0x907D0074
		opword 0x901D0078
		opword 0x807D0024
		opword 0x3403FFFF
		opword 0x901D0024
		opword 0x41810464
		opword 0x38000000
		opword 0x901D0024
		opword 0x48000458
		opword 0x38000002
		opword 0x981D0038
		opword 0x80BD0024
		opword 0x3C004330
		opword 0x90010028
		lis r4, double_to_int_802ccf00@ha
		opword 0x20A50010
		lis r3, vec3_802cce38@ha
		opword 0x6CA08000
		opword 0x9001002C
		addi r5, r3, vec3_802cce38@l
		addi r3, r4, double_to_int_802ccf00@l
		opword 0x80850000
		opword 0xC8230000
		opword 0xC8010028
		opword 0x80650004
		opword 0xEC200828
		lfs f0, float_0p0625_8041b184(r2)
		opword 0x80050008
		opword 0x90810008
		opword 0xEC010032
		opword 0x9061000C
		opword 0xD0010008
		opword 0x90010010
		opword 0x80010008
		opword 0xD001000C
		opword 0xD0010010
		opword 0x8061000C
		opword 0x901D0070
		opword 0x80010010
		opword 0x907D0074
		opword 0x901D0078
		opword 0x807D0024
		opword 0x3403FFFF
		opword 0x901D0024
		opword 0x418103C8
		opword 0x38000000
		lfs f0, float_90_8041b0f0(r2)
		opword 0x901D0024
		opword 0xC03D0110
		opword 0xFC010040
		opword 0x4C411382
		opword 0x4082003C
		lfs f0, float_270_8041b0f4(r2)
		opword 0xFC010040
		opword 0x4C401382
		opword 0x4082002C
		lfs f1, float_180_8041b0fc(r2)
		opword 0x7FA3EB78
		bl partyToMovedir
		opword 0xD03D00FC
		lfs f0, float_180_8041b0fc(r2)
		opword 0xC03D00FC
		opword 0xD03D0100
		opword 0xD01D010C
		opword 0xD01D0110
		opword 0x48000028
		lfs f1, float_0_8041b100(r2)
		opword 0x7FA3EB78
		bl partyToMovedir
		opword 0xD03D00FC
		lfs f0, float_0_8041b100(r2)
		opword 0xC03D00FC
		opword 0xD03D0100
		opword 0xD01D010C
		opword 0xD01D0110
		opword 0x7FA3EB78
		bl partyClearJumpPara
		opword 0x801D0004
		opword 0x3BE00001
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881D0031
		opword 0x3B800000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BE0000C
		opword 0x801D0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889D0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57E0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FE3002E
		opword 0x48000050
		opword 0x881D0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57E0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FE3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57E0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FE3002E
		opword 0x807D0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FE4FB78
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93FD0018
		opword 0x38000000
		opword 0xB01D0020
		opword 0x801D0008
		opword 0x60002000
		opword 0x901D0008
		opword 0x80BD0004
		opword 0x3C600002
		opword 0x38000001
		opword 0x389E008C
		opword 0x54A50734
		opword 0x38630920
		opword 0x90BD0004
		opword 0x3BE00001
		opword 0x981D0034
		bl psndSFXOn_3D
		opword 0x4800022C
		opword 0x389D0058
		bl partyGetAppearPos2
		opword 0x807D0058
		opword 0x3BC00001
		opword 0x801D005C
		opword 0x907D00B8
		opword 0x901D00BC
		opword 0x801D0060
		opword 0x901D00C0
		opword 0x801D0004
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881D0031
		opword 0x3B800000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801D0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889D0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881D0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807D0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DD0018
		opword 0x38000000
		opword 0xB01D0020
		opword 0x801D0008
		opword 0x60002000
		opword 0x901D0008
		opword 0x38000001
		opword 0x3BE00001
		opword 0x981D0034
		opword 0x4800010C
		opword 0x801D0004
		opword 0x3BC00001
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881D0031
		opword 0x3B800000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801D0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889D0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881D0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807D0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DD0018
		opword 0x38000000
		opword 0xB01D0020
		opword 0x801D0008
		opword 0x60002000
		opword 0x901D0008
		opword 0x38000000
		opword 0x3BE00001
		opword 0x981D0034
		opword 0x4800000C
		bl allPartyForceRideOn
		opword 0x3BE00001
		opword 0x7FE3FB78
		opword 0xE3E10058
		opword 0xCBE10050
		opword 0xE3C10048
		opword 0xCBC10040
		opword 0x83E1003C
		opword 0x83C10038
		opword 0x83A10034
		opword 0x80010064
		opword 0x83810030
		opword 0x7C0803A6
		opword 0x38210060
	}
}
#pragma pop

s32 partyGoodbyeInit(PartyEntry* party) {
    MarioWork* mario;
    party->field_38 = 10;
    party_dp = &partyDataTbl[party->currentMemberId];
    if (party_dp->init_func) {
        party_dp->init_func(party);
    }
    if (party->flags & 0x100) {
        if (party->currentMemberId == PARTY_MEMBER_VIVIAN) {
            vivianUnhold(party);
            party->field_38 = 0;
        }
        if (party->currentMemberId == PARTY_MEMBER_YOSHI) {
            marioGetoffYoshi();
            party->field_38 = 0;
        }
    }
    mario = party->playerPtr;
    if (mario->currMotionId == 0x16 || mario->currMotionId == 0x18 || mario->currMotionId == 0x19) {
        party->field_38 = 20;
    }
    return 0;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 partyGoodbyeMain(PartyEntry* party) {
	asm volatile {
		opword 0x9421FF60
		opword 0x7C0802A6
		opword 0x900100A4
		opword 0xDBE10090
		opword 0xF3E10098
		opword 0xDBC10080
		opword 0xF3C10088
		opword 0xDBA10070
		opword 0xF3A10078
		opword 0xDB810060
		opword 0xF3810068
		opword 0xDB610050
		opword 0xF3610058
		opword 0xDB410040
		opword 0xF3410048
		opword 0x93E1003C
		opword 0x93C10038
		opword 0x93A10034
		opword 0x7C7F1B78
		bl marioGetPtr
		opword 0x881F0038
		opword 0x7C7E1B78
		opword 0x28000014
		opword 0x41810470
		lis r3, jumptable_80312720@ha
		opword 0x5400103A
		addi r3, r3, jumptable_80312720@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0x889F0031
		lis r3, partyDataTbl@ha
		addi r0, r3, partyDataTbl@l
		opword 0x7FE3FB78
		opword 0x7C840774
		opword 0x1C840028
		opword 0x7C802214
		stw r4, party_dp(r13)
		opword 0x8184000C
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000006
		opword 0x40820024
		bl vivianGetStatus
		opword 0x2C030000
		opword 0x40820410
		opword 0x3860000A
		opword 0x38000008
		opword 0x987F0038
		opword 0x981F0034
		opword 0x480003FC
		opword 0x2C000004
		opword 0x40820024
		bl yoshiGetStatus
		opword 0x2C030000
		opword 0x408203E8
		opword 0x3860000A
		opword 0x38000008
		opword 0x987F0038
		opword 0x981F0034
		opword 0x480003D4
		opword 0x3860000A
		opword 0x38000008
		opword 0x987F0038
		opword 0x981F0034
		opword 0x480003C0
		opword 0x3C600002
		opword 0x389E008C
		opword 0x3863091F
		bl psndSFXOn_3D
		opword 0xC07E008C
		lfs f4, float_0p5_8041b170(r2)
		opword 0xD07F0094
		opword 0xFFC01890
		lfs f5, float_4_8041b10c(r2)
		opword 0xC05E01B8
		opword 0xC03E0090
		lfs f0, float_1p6_8041b16c(r2)
		opword 0xEFE408BA
		opword 0xD3FF0098
		opword 0xC09E0094
		opword 0xD09F009C
		opword 0xFFA02090
		opword 0xC39F0058
		opword 0xC35F0060
		opword 0xC37F005C
		opword 0xFC20E090
		opword 0xFC40D090
		opword 0xD0BF0104
		opword 0xD01F011C
		bl distABf
		opword 0xD03F0128
		opword 0xFC20E090
		opword 0xFC40D090
		opword 0xFC60F090
		opword 0xFC80E890
		bl angleABf
		opword 0xD03F0100
		opword 0x3C004330
		opword 0x3880000F
		lis r3, double_to_int_802ccf00@ha
		opword 0x909F0024
		opword 0xECBFD828
		lfd f4, double_to_int_802ccf00@l(r3)
		opword 0x807F0024
		opword 0x90010008
		opword 0x6C638000
		opword 0xC03F0128
		opword 0x9061000C
		lfs f3, float_0p5_8041b170(r2)
		opword 0xC8010008
		opword 0x90010018
		opword 0xEC002028
		opword 0x90010010
		opword 0xEC010024
		opword 0x90010020
		opword 0xD01F0104
		opword 0x801F0024
		opword 0xC03F011C
		opword 0x6C008000
		opword 0x9001001C
		opword 0xC8010018
		opword 0x90010014
		opword 0xEC002028
		opword 0xC8410010
		opword 0x90010024
		opword 0xEC210032
		opword 0xEC422028
		opword 0xC8010020
		opword 0xEC002028
		opword 0xEC220072
		opword 0xEC23287A
		opword 0xEC010024
		opword 0xD01F0114
		opword 0x801F0004
		opword 0x540007BD
		opword 0x408200BC
		opword 0x881F0031
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800008
		bl partyGetHp
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820024
		opword 0x889F0031
		lis r3, partyPoseTbl@ha
		addi r0, r3, partyPoseTbl@l
		opword 0x7C830774
		opword 0x1C63003C
		opword 0x7C601A14
		opword 0x83C30010
		opword 0x48000048
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x4182001C
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		addi r0, r3, partyDotPoseTbl@l
		opword 0x7C602214
		opword 0x83C30010
		opword 0x48000020
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		addi r0, r3, yoshiDotPoseTbl@l
		opword 0x7C602214
		opword 0x83C30010
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		opword 0x3800000B
		opword 0x981F0038
		opword 0x480001E0
		opword 0xC03F0114
		opword 0x387F0058
		opword 0xC01F011C
		opword 0x389F0060
		opword 0xEC010028
		opword 0xD01F0114
		opword 0xC03F005C
		opword 0xC01F0114
		opword 0xEC01002A
		opword 0xD01F005C
		opword 0xC03F0104
		opword 0xC05F0100
		bl movePos
		lfs f1, float_50_8041b1b8(r2)
		opword 0xC01F010C
		opword 0xEC21002A
		bl revise360
		opword 0xD03F010C
		opword 0x3C004330
		lis r3, double_to_int_802ccf00@ha
		lfs f0, float_10_8041b124(r2)
		opword 0x809F0024
		opword 0x90010020
		opword 0x6C808000
		lfd f2, double_to_int_802ccf00@l(r3)
		opword 0x90010024
		opword 0xC8210020
		opword 0xEC211028
		opword 0xFC010040
		opword 0x40810008
		opword 0xFC200090
		lfs f0, float_10_8041b124(r2)
		opword 0xEC010024
		opword 0xD01F0070
		opword 0xC01F0070
		opword 0xD01F0074
		opword 0xC01F0070
		opword 0xD01F0078
		opword 0x807F0024
		opword 0x3403FFFF
		opword 0x901F0024
		opword 0x40800138
		opword 0x3800000C
		opword 0x981F0038
		opword 0x4800012C
		opword 0x801F0004
		opword 0x3BC00001
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881F0031
		opword 0x3BA00000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3BA00001
		opword 0x2C1D0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889F0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		lfs f0, float_0_8041b100(r2)
		opword 0x7FE3FB78
		opword 0x3880000E
		opword 0xD01F0114
		opword 0xC01F0098
		opword 0xD01F005C
		bl partyChgRunMode
		opword 0x38600001
		opword 0x4800001C
		opword 0x7FE3FB78
		opword 0x3880000E
		bl partyChgRunMode
		opword 0x38600001
		opword 0x48000008
		opword 0x38600000
		opword 0xE3E10098
		opword 0xCBE10090
		opword 0xE3C10088
		opword 0xCBC10080
		opword 0xE3A10078
		opword 0xCBA10070
		opword 0xE3810068
		opword 0xCB810060
		opword 0xE3610058
		opword 0xCB610050
		opword 0xE3410048
		opword 0xCB410040
		opword 0x83E1003C
		opword 0x83C10038
		opword 0x800100A4
		opword 0x83A10034
		opword 0x7C0803A6
		opword 0x382100A0
	}
}
#pragma pop

#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the epilogue scheduler run
s32 partyDokanInit(PartyEntry* party) {
	asm {
		mr r29, r3
		lis r3, vec3_802ccd30@ha
	}
	asm volatile {
		addi r31, r3, vec3_802ccd30@l
		opword 0x801D0004
		opword 0x83DD0160
		opword 0x60000010
		opword 0x901D0004
		opword 0x881E003E
		opword 0x7C000774
		opword 0x2C000004
		opword 0x418202EC
		opword 0x4080001C
		opword 0x2C000001
		opword 0x41820118
		opword 0x4080001C
		opword 0x2C000000
		opword 0x408000F4
		opword 0x480003C8
		opword 0x2C000006
		opword 0x408003C0
		opword 0x480001DC
		opword 0x807D0014
		opword 0x2C030000
		opword 0x41800010
		bl animPaperPoseRelease
		opword 0x3800FFFF
		opword 0x901D0014
		opword 0x801D0004
		opword 0x387F01E0
		opword 0x38800002
		opword 0x64000400
		opword 0x901D0004
		bl animPaperPoseEntry
		opword 0x907D0014
		opword 0x387F01E0
		opword 0x389F01EC
		li r28, 0x0
		bl strcmp
		opword 0x2C030000
		opword 0x41820040
		opword 0x387F01E0
		opword 0x389F01F4
		bl strcmp
		opword 0x2C030000
		opword 0x4182002C
		opword 0x387F01E0
		opword 0x389F01FC
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x387F01E0
		opword 0x7C641B78
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x3B800001
		opword 0x7F800034
		opword 0x387F01E0
		opword 0x541CD97E
		opword 0x389F0208
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x881D0031
		opword 0x7C000774
		opword 0x20000005
		opword 0x7C000034
		opword 0x541CD97E
		opword 0x807D000C
		opword 0x7F85E378
		opword 0x389F01E0
		bl animPoseSetPaperAnimGroup
		lfs f0, float_30_8041b178(r2)
		opword 0x38000000
		opword 0xD01D0124
		opword 0x981D0038
		opword 0x480002DC
		opword 0x807F0120
		opword 0x801F0124
		opword 0x907D0070
		opword 0x901D0074
		opword 0x801F0128
		opword 0x901D0078
		opword 0x807D0014
		opword 0x2C030000
		opword 0x41800010
		bl animPaperPoseRelease
		opword 0x3800FFFF
		opword 0x901D0014
		opword 0x801D0004
		opword 0x387F01E0
		opword 0x38800002
		opword 0x64000400
		opword 0x901D0004
		bl animPaperPoseEntry
		opword 0x907D0014
		opword 0x387F01E0
		opword 0x389F01EC
		opword 0x3B800000
		bl strcmp
		opword 0x2C030000
		opword 0x41820040
		opword 0x387F01E0
		opword 0x389F01F4
		bl strcmp
		opword 0x2C030000
		opword 0x4182002C
		opword 0x387F01E0
		opword 0x389F01FC
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x387F01E0
		opword 0x7C641B78
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x3B800001
		opword 0x7F800034
		opword 0x387F01E0
		opword 0x541CD97E
		opword 0x389F0208
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x881D0031
		opword 0x7C000774
		opword 0x20000005
		opword 0x7C000034
		opword 0x541CD97E
		opword 0x807D000C
		opword 0x7F85E378
		opword 0x389F01E0
		bl animPoseSetPaperAnimGroup
		lfs f0, float_30_8041b178(r2)
		opword 0x38000000
		opword 0xD01D0124
		opword 0x981D0038
		opword 0x480001E4
		opword 0x807D0014
		opword 0x2C030000
		opword 0x41800010
		bl animPaperPoseRelease
		opword 0x3800FFFF
		opword 0x901D0014
		opword 0x801D0004
		opword 0x387F01FC
		opword 0x38800002
		opword 0x64000400
		opword 0x901D0004
		bl animPaperPoseEntry
		opword 0x907D0014
		opword 0x387F01FC
		opword 0x389F01EC
		opword 0x3B800000
		bl strcmp
		opword 0x2C030000
		opword 0x41820040
		opword 0x387F01FC
		opword 0x389F01F4
		bl strcmp
		opword 0x2C030000
		opword 0x4182002C
		opword 0x387F01FC
		opword 0x7C641B78
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x387F01FC
		opword 0x389F01E0
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x3B800001
		opword 0x7F800034
		opword 0x387F01FC
		opword 0x541CD97E
		opword 0x389F0208
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x881D0031
		opword 0x7C000774
		opword 0x20000005
		opword 0x7C000034
		opword 0x541CD97E
		opword 0x807D000C
		opword 0x7F85E378
		opword 0x389F01FC
		bl animPoseSetPaperAnimGroup
		lfs f1, float_26_8041b1b0(r2)
		opword 0x3800000A
		lfs f0, float_10_8041b124(r2)
		opword 0xD03D0124
		opword 0x981D0038
		opword 0xD01D008C
		opword 0x480000FC
		opword 0x807D0014
		opword 0x2C030000
		opword 0x41800010
		bl animPaperPoseRelease
		opword 0x3800FFFF
		opword 0x901D0014
		opword 0x801D0004
		opword 0x387F01FC
		opword 0x38800002
		opword 0x64000400
		opword 0x901D0004
		bl animPaperPoseEntry
		opword 0x907D0014
		opword 0x387F01FC
		opword 0x389F01EC
		opword 0x3B800000
		bl strcmp
		opword 0x2C030000
		opword 0x41820040
		opword 0x387F01FC
		opword 0x389F01F4
		bl strcmp
		opword 0x2C030000
		opword 0x4182002C
		opword 0x387F01FC
		opword 0x7C641B78
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x387F01FC
		opword 0x389F01E0
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x3B800001
		opword 0x7F800034
		opword 0x387F01FC
		opword 0x541CD97E
		opword 0x389F0208
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x881D0031
		opword 0x7C000774
		opword 0x20000005
		opword 0x7C000034
		opword 0x541CD97E
		opword 0x807D000C
		opword 0x7F85E378
		opword 0x389F01FC
		bl animPoseSetPaperAnimGroup
		lfs f1, float_neg26_8041b1b4(r2)
		opword 0x3800000A
		lfs f0, float_10_8041b124(r2)
		opword 0xD03D0124
		lfs f1, float_180_8041b0fc(r2)
		opword 0x981D0038
		opword 0xD01D008C
		opword 0xC01E00BC
		opword 0xEC21002A
		bl revise360
		opword 0xD03D0064
		opword 0x801D0004
		opword 0x540007BD
		opword 0x4082003C
		opword 0x807D001C
		opword 0x28030000
		opword 0x41820014
		opword 0x389F0210
		bl strcmp
		opword 0x2C030000
		opword 0x41820020
		opword 0x387F0210
		opword 0x38000000
		opword 0x907D001C
		opword 0xB01D0020
		opword 0x801D0008
		opword 0x60004000
		opword 0x901D0008
		opword 0x801D0004
		opword 0x540007BD
		opword 0x408200B0
		opword 0x881D0031
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800008
		bl partyGetHp
		opword 0x801D0004
		opword 0x54000421
		opword 0x40820020
		opword 0x881D0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x7C000774
		opword 0x1C00003C
		opword 0x7F83002E
		opword 0x48000040
		opword 0x881D0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820018
		opword 0x1C00003C
		lis r3, partyDotPoseTbl@ha
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7F83002E
		opword 0x4800001C
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C03003C
		lis r3, yoshiDotPoseTbl@ha
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7F83002E
		opword 0x807D0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7F84E378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x939D0018
		opword 0x38000000
		opword 0xB01D0020
		opword 0x801D0008
		opword 0x60002000
		opword 0x901D0008
		opword 0x801D0004
		opword 0x38800001
		opword 0x60000008
		opword 0x901D0004
		opword 0x801D0004
		opword 0x60000010
		opword 0x901D0004
		opword 0x807D000C
		bl animPoseSetMaterialLightFlagOff
		lfs f1, float_180_8041b0fc(r2)
		opword 0xC01E01A8
		opword 0xEC21002A
		bl revise360
		opword 0xD03D0110
		opword 0x7FA3EB78
		opword 0xC01E01A8
		opword 0xD01D010C
		opword 0xC01E019C
		opword 0xD01D00FC
		opword 0x809E008C
		opword 0x801E0090
		opword 0x909D0058
		opword 0x901D005C
		opword 0x801E0094
		opword 0x901D0060
		bl L_partyVivianTailStop
	}
	asm {
		li r3, 0x0
	}
}
#pragma pop

#pragma defer_codegen reset

asm void partyMain(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	bl marioGetPtr
	la r31, partyPtrTbl(r13)
	li r3, 0x0
	lwz r4, partyPtrTbl(r13)
	cmplwi r4, 0x0
	beq L_af_1
	cmpwi r3, 0x0
	blt L_af_2
	b L_af_3
L_af_2:
	mr r4, r3
L_af_3:
	lwz r0, 0x0(r4)
	clrlwi. r0, r0, 31
	beq L_af_1
	li r3, 0x1
L_af_1:
	addi r4, r31, 0x4
	li r0, 0x1
	lwz r4, 0x0(r4)
	cmplwi r4, 0x0
	beq L_af_4
	cmpwi r0, 0x0
	blt L_af_5
	b L_af_6
L_af_5:
	li r4, 0x0
L_af_6:
	lwz r0, 0x0(r4)
	clrlwi. r0, r0, 31
	beq L_af_4
	addi r3, r3, 0x1
L_af_4:
	cmpwi r3, 0x0
	beq L_af_7
	bl unk_8013be14
	li r30, 0x0
L_af_8:
	lwz r29, 0x0(r31)
	cmplwi r29, 0x0
	beq L_af_9
	lwz r0, 0x0(r29)
	clrlwi. r0, r0, 31
	beq L_af_9
	bl marioBgmodeChk
	cmpwi r3, 0x1
	beq L_af_9
	mr r3, r29
	bl driveParty
L_af_9:
	addi r30, r30, 0x1
	addi r31, r31, 0x4
	cmpwi r30, 0x2
	blt L_af_8
L_af_7:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

#define partyGetPtr partyGetPtr__af_inl
BOOL partyGoodbye(s32 id) {
    BOOL ret = FALSE;

    if (id >= 0) {
        partyChgRunMode(partyGetPtr(id), 8);
        ret = TRUE;
    }
    return ret;
}

#undef partyGetPtr

#define partyGetPtr partyGetPtr__af_inl
s32 partyKill(s32 id) {
    PartyEntry* party;
    MarioWork* player;
    PartyEntry* other;

    party = partyGetPtr(id);
    if (party == NULL) {
        return 0;
    }
    player = party->playerPtr;
    party_dp = &partyDataTbl[partyGetPtr(player->currPartySlotId[id])->currentMemberId];
    if (party_dp->exit_func && party->runMode != 11) {
        party_dp->exit_func(party);
    }
    if (partyGetPtr(player->currPartySlotId[id])) {
        player->prevPartyMemberId[id] = partyGetPtr(player->currPartySlotId[id])->currentMemberId;
    } else {
        player->prevPartyMemberId[id] = 0;
    }
    player->currPartySlotId[id] = -1;
    partyPtrTbl[id] = NULL;
    animPoseRelease(party->paperAnimGroup);
    __memFree(HEAP_DEFAULT, party);
    return 0;
}

#undef partyGetPtr

#define partyGetPtr partyGetPtr__af_inl
s32 partyKill2(s32 id) {
    PartyEntry* party;
    MarioWork* player;

    party = partyGetPtr(id);
    if (party == NULL) {
        return 0;
    }
    player = party->playerPtr;
    party_dp = &partyDataTbl[partyGetPtr(player->currPartySlotId[id])->currentMemberId];
    if (party_dp->exit_func && party->runMode != 11) {
        party_dp->exit_func(party);
    }
    player->prevPartyMemberId[id] = 0;
    player->currPartySlotId[id] = -1;
    partyPtrTbl[id] = NULL;
    animPoseRelease(party->paperAnimGroup);
    __memFree(HEAP_DEFAULT, party);
    return 0;
}

#undef partyGetPtr

s32 yoshiSetColor(void) {
    s32 color;
    s32 r = irand(1000);

    if (r < 150) {
        color = 0;
    } else if (r < 300) {
        color = 1;
    } else if (r < 450) {
        color = 2;
    } else if (r < 600) {
        color = 3;
    } else if (r < 750) {
        color = 4;
    } else if (r < 900) {
        color = 5;
    } else {
        color = 6;
    }
    pouchSetPartyColor(PARTNER_YOSHI, color);
    return color;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
f32 partyGetHeight(PartyEntry* party) {
	asm volatile {
		opword 0x88030031
		opword 0x2C000004
		opword 0x40820020
		opword 0x80030000
		opword 0x540005EF
		opword 0x41820014
		lfs f1, float_18p5_8041b1bc(r2)
		opword 0xC00300F0
		opword 0xEC21002A
		opword 0x4E800020
		opword 0xC02300F0
	}
}
#pragma pop

#define partyChgPose partyChgPose__af_inl
#define partyGetPtr partyGetPtr__af_inl
s32 partyEntryMain(s32 memberId) {
    MarioWork* player;
    s32 slot;
    PartyEntry* party;

    player = marioGetPtr();
    slot = partyGetFreeSlot(0);
    if (slot < 0) {
        return -1;
    }
    party = partyGetPtr(slot);
    memset(party, 0, sizeof(PartyEntry));
    party->camId = marioGetCamId();
    party->paperAnimGroup = -1;
    party->field_10 = -1;
    party->paperPoseId = -1;
    party->flags = 1;
    party->currentSlotId = slot;
    party->playerPtr = player;
    party->currentMemberId = memberId;
    if (player->prevPartyMemberId[0] == 0) {
        player->prevPartyMemberId[0] = party->currentMemberId;
    }
    if (slot == 1) {
        party->flags |= 4;
    }
    party_dp = &partyDataTbl[memberId];
    if (player->flags & 0x80000000) {
        party->flags2 |= 0x8000;
    }
    if (!party && !party && !party) {
    }
    partyPoseEntry(party);
    animPosePeraOff(party->paperAnimGroup);
    setAnimPoseMaterialFlag(party);
    partyChgPose(party, partyChgPoseId(party, 1));
    party->field_1C = 0;
    party_dp->init_func(party);
    return slot;
}

#undef partyChgPose
#undef partyGetPtr

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 partyEntry2(s32 memberId) {
	asm volatile {
		opword 0x7C7C1B78
		bl marioGetPtr
		la r27, partyPtrTbl(r13)
		opword 0x7C7F1B78
		opword 0x801B0004
		opword 0x28000000
		opword 0x40820028
		opword 0x38600000
		opword 0x38800188
		bl __memAlloc
		opword 0x907B0004
		opword 0x38800000
		opword 0x38A00188
		bl memset
		opword 0x3BC00001
		opword 0x48000008
		opword 0x3BC0FFFF
		opword 0x2C1E0000
		opword 0x4080000C
		opword 0x3860FFFF
		opword 0x48000300
		opword 0x41800014
		opword 0x57C0103A
		la r3, partyPtrTbl(r13)
		opword 0x7FA3002E
		opword 0x48000008
		opword 0x3BA00000
		opword 0x7FA3EB78
		opword 0x38800000
		opword 0x38A00188
		bl memset
		bl marioGetCamId
		opword 0x907D0164
		opword 0x3860FFFF
		opword 0x38000009
		opword 0x2C1E0001
		opword 0x907D000C
		opword 0x907D0010
		opword 0x907D0014
		opword 0x901D0000
		opword 0x9BDD002F
		opword 0x93FD0160
		opword 0x9B9D0031
		opword 0x40820010
		opword 0x801D0000
		opword 0x60000004
		opword 0x901D0000
		opword 0x1C9C0028
		lis r3, partyDataTbl@ha
		addi r0, r3, partyDataTbl@l
		opword 0x7C602214
		stw r3, party_dp(r13)
		opword 0x881D0031
		opword 0x2C000004
		opword 0x41820024
		opword 0x801D0004
		opword 0x54000421
		opword 0x4082000C
		opword 0x83830000
		opword 0x48000038
		lis r3, str_802CCEEC@ha
		addi r28, r3, str_802CCEEC@l
		opword 0x4800002C
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x801D0004
		opword 0x5464103A
		la r3, yoshigroup(r13)
		opword 0x54000421
		opword 0x7F83202E
		opword 0x4182000C
		lis r3, str_802CCEEC@ha
		addi r28, r3, str_802CCEEC@l
		opword 0x807D000C
		opword 0x2C030000
		opword 0x41800008
		bl animPoseRelease
		opword 0x7F83E378
		opword 0x38800002
		bl animPoseEntry
		opword 0x907D000C
		opword 0x807D000C
		bl animPosePeraOff
		opword 0x839D0160
		bl marioAnimeId
		opword 0x5460103A
		opword 0x7C7C0214
		opword 0x80630228
		bl animPoseGetMaterialFlag
		opword 0x7C641B78
		opword 0x807D000C
		bl animPoseSetMaterialFlagOn
		bl marioAnimeId
		opword 0x5460103A
		opword 0x7C7C0214
		opword 0x80630228
		bl animPoseGetMaterialLightFlag
		opword 0x7C641B78
		opword 0x807D000C
		bl animPoseSetMaterialLightFlagOn
		opword 0x801D0004
		opword 0x3B800001
		opword 0x540007BD
		opword 0x4182000C
		opword 0x839D0018
		opword 0x480000E8
		opword 0x881D0031
		opword 0x3B600000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B600001
		opword 0x2C1B0001
		opword 0x40820008
		opword 0x3B80000C
		opword 0x801D0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889D0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x5780103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7F83002E
		opword 0x48000050
		opword 0x881D0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x5780103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7F83002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x5780103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7F83002E
		opword 0x807D0018
		opword 0x28030000
		opword 0x41820018
		opword 0x7F84E378
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x939D0018
		opword 0x38000000
		opword 0xB01D0020
		opword 0x801D0008
		opword 0x60002000
		opword 0x901D0008
		opword 0x801D0004
		opword 0x540007BD
		opword 0x40820044
		opword 0x807D0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7F84E378
		bl strcmp
		opword 0x2C030000
		opword 0x41820028
		opword 0x801D0004
		opword 0x54000421
		opword 0x4082001C
		opword 0x939D0018
		opword 0x38000000
		opword 0xB01D0020
		opword 0x801D0008
		opword 0x60002000
		opword 0x901D0008
		opword 0x38000000
		opword 0x7FA3EB78
		opword 0x901D001C
		lwz r4, party_dp(r13)
		opword 0x81840004
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x80BF008C
		lis r3, vec3_802ccdcc@ha
		opword 0x809F0090
		addi r6, r3, vec3_802ccdcc@l
		opword 0x38000000
		opword 0x7FC3F378
		opword 0x90BD0058
		opword 0x909D005C
		opword 0x809F0094
		opword 0x909D0060
		opword 0x80BD0058
		opword 0x809D005C
		opword 0x90BD00B8
		opword 0x909D00BC
		opword 0x809D0060
		opword 0x909D00C0
		opword 0x80A60000
		opword 0x80860004
		opword 0x90BD0070
		opword 0x909D0074
		opword 0x80860008
		opword 0x909D0078
		opword 0x981D0034
	}
}
#pragma pop

#define partyChgPose partyChgPose__af_inl
#define partyGetPtr partyGetPtr__af_inl
s32 partyEntry2Hello(s32 memberId) {
    MarioWork* player;
    s32 slot;
    PartyEntry* party;

    player = marioGetPtr();
    slot = partyGetFreeSlot2();
    if (slot < 0) {
        return -1;
    }
    party = partyGetPtr(slot);
    memset(party, 0, sizeof(PartyEntry));
    party->camId = marioGetCamId();
    party->paperAnimGroup = -1;
    party->field_10 = -1;
    party->paperPoseId = -1;
    party->flags = 9;
    party->currentSlotId = slot;
    party->playerPtr = player;
    party->currentMemberId = memberId;
    if (slot == 1) {
        party->flags |= 4;
    }
    party_dp = &partyDataTbl[memberId];
    partyPoseEntry(party);
    animPosePeraOff(party->paperAnimGroup);
    setAnimPoseMaterialFlag(party);
    partyChgPose(party, partyChgPoseId(party, 1));
    party->field_1C = 0;
    party_dp->init_func(party);
    partyChgRunMode(party, 4);
    return slot;
}

#undef partyChgPose
#undef partyGetPtr

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 partyEntry2Pos(s32 memberId, f32 x, f32 y, f32 z) {
	char _af_pad[12];
	asm volatile {
		fmr f29, f1
		mr r27, r3
		opword 0xFFC01090
		opword 0xFFE01890
		bl marioGetPtr
		la r28, partyPtrTbl(r13)
		opword 0x7C7D1B78
		opword 0x801C0004
		opword 0x28000000
		opword 0x40820028
		opword 0x38600000
		opword 0x38800188
		bl __memAlloc
		opword 0x907C0004
		opword 0x38800000
		opword 0x38A00188
		bl memset
		opword 0x3BE00001
		opword 0x48000008
		opword 0x3BE0FFFF
		opword 0x2C1F0000
		opword 0x4080000C
		opword 0x3860FFFF
		opword 0x48000320
		opword 0x41800014
		opword 0x57E0103A
		la r3, partyPtrTbl(r13)
		opword 0x7FC3002E
		opword 0x48000008
		opword 0x3BC00000
		opword 0x7FC3F378
		opword 0x38800000
		opword 0x38A00188
		bl memset
		bl marioGetCamId
		opword 0x907E0164
		opword 0x3860FFFF
		opword 0x38000009
		opword 0x2C1F0001
		opword 0x907E000C
		opword 0x907E0010
		opword 0x907E0014
		opword 0x901E0000
		opword 0x9BFE002F
		opword 0x93BE0160
		opword 0x9B7E0031
		opword 0x40820010
		opword 0x801E0000
		opword 0x60000004
		opword 0x901E0000
		opword 0x1C9B0028
		lis r3, partyDataTbl@ha
		addi r0, r3, partyDataTbl@l
		opword 0x7C602214
		stw r3, party_dp(r13)
		opword 0x881E0031
		opword 0x2C000004
		opword 0x41820024
		opword 0x801E0004
		opword 0x54000421
		opword 0x4082000C
		opword 0x83A30000
		opword 0x48000038
		lis r3, str_802CCEEC@ha
		addi r29, r3, str_802CCEEC@l
		opword 0x4800002C
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x801E0004
		opword 0x5464103A
		la r3, yoshigroup(r13)
		opword 0x54000421
		opword 0x7FA3202E
		opword 0x4182000C
		lis r3, str_802CCEEC@ha
		addi r29, r3, str_802CCEEC@l
		opword 0x807E000C
		opword 0x2C030000
		opword 0x41800008
		bl animPoseRelease
		opword 0x7FA3EB78
		opword 0x38800002
		bl animPoseEntry
		opword 0x907E000C
		opword 0x807E000C
		bl animPosePeraOff
		opword 0x83BE0160
		bl marioAnimeId
		opword 0x5460103A
		opword 0x7C7D0214
		opword 0x80630228
		bl animPoseGetMaterialFlag
		opword 0x7C641B78
		opword 0x807E000C
		bl animPoseSetMaterialFlagOn
		bl marioAnimeId
		opword 0x5460103A
		opword 0x7C7D0214
		opword 0x80630228
		bl animPoseGetMaterialLightFlag
		opword 0x7C641B78
		opword 0x807E000C
		bl animPoseSetMaterialLightFlagOn
		opword 0x801E0004
		opword 0x3BA00001
		opword 0x540007BD
		opword 0x4182000C
		opword 0x83BE0018
		opword 0x480000E8
		opword 0x881E0031
		opword 0x3B800000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BA0000C
		opword 0x801E0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889E0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57A0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x48000050
		opword 0x881E0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57A0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57A0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x807E0018
		opword 0x28030000
		opword 0x41820018
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x93BE0018
		opword 0x38000000
		opword 0xB01E0020
		opword 0x801E0008
		opword 0x60002000
		opword 0x901E0008
		opword 0x801E0004
		opword 0x540007BD
		opword 0x40820044
		opword 0x807E0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820028
		opword 0x801E0004
		opword 0x54000421
		opword 0x4082001C
		opword 0x93BE0018
		opword 0x38000000
		opword 0xB01E0020
		opword 0x801E0008
		opword 0x60002000
		opword 0x901E0008
		opword 0x38000000
		opword 0x7FC3F378
		opword 0x901E001C
		lwz r4, party_dp(r13)
		opword 0x81840004
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x7FC3F378
		opword 0x38800002
		bl partyChgRunMode
		lis r3, vec3_802ccdd8@ha
		lfs f0, float_1_8041b0e8(r2)
		addi r5, r3, vec3_802ccdd8@l
		opword 0x7FE3FB78
		opword 0x80050000
		opword 0x80850004
		stw r0, _af_pad+0(r1)
		opword 0x80050008
		opword 0x9081000C
		opword 0xD3A10008
		opword 0x90010010
		opword 0x80010008
		opword 0xD3C1000C
		opword 0xD3E10010
		opword 0x8081000C
		opword 0x901E0058
		opword 0x80010010
		opword 0x909E005C
		opword 0x901E0060
		opword 0x809E0058
		opword 0x801E005C
		opword 0x909E00B8
		opword 0x901E00BC
		opword 0x801E0060
		opword 0x901E00C0
		opword 0xD01E0070
		opword 0xD01E0074
		opword 0xD01E0078
	}
}
#pragma pop

void partyInit(void) {
    memset(partyPtrTbl, 0, sizeof(partyPtrTbl));
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
void partyReInit(void) {
	asm {
		lis r3, vec3_802ccd30@ha
		addi r31, r3, vec3_802ccd30@l
	}
	asm volatile {
		bl marioGetExtraPartyId
		opword 0x2C030000
		opword 0x41800014
		opword 0x5460103A
		la r3, partyPtrTbl(r13)
		opword 0x7FC3002E
		opword 0x48000008
		opword 0x3BC00000
		opword 0x281E0000
		opword 0x41820228
		opword 0x3860000D
		opword 0x38000000
		opword 0x907E0000
		opword 0x901E0004
		lwz r28, 0xc(r30)
		opword 0x2C1C0000
		opword 0x4180001C
		opword 0x7F83E378
		opword 0x3880FFFF
		bl animPoseSetMaterialFlagOff
		opword 0x7F83E378
		opword 0x38800002
		bl animPoseSetMaterialLightFlagOn
		opword 0x38000000
		opword 0x981E0037
		opword 0x801E001C
		opword 0x28000000
		opword 0x41820040
		opword 0x807E000C
		opword 0x38800000
		opword 0x38A00000
		bl animPoseSetPaperAnimGroup
		opword 0x38000000
		opword 0x901E001C
		opword 0x801E0004
		opword 0x54000188
		opword 0x901E0004
		opword 0x807E0014
		opword 0x2C030000
		opword 0x41800010
		bl animPaperPoseRelease
		opword 0x3800FFFF
		opword 0x901E0014
		opword 0x3B800000
		opword 0x3BA00001
		opword 0x939E0130
		opword 0x939E012C
		opword 0x939E0148
		opword 0x939E0138
		opword 0x939E013C
		opword 0x939E0134
		opword 0x939E0140
		opword 0x939E0144
		opword 0x801E0004
		opword 0x540007BD
		opword 0x4182000C
		opword 0x83BE0018
		opword 0x480000E4
		opword 0x881E0031
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BA0000C
		opword 0x801E0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889E0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57A0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x48000050
		opword 0x881E0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57A0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57A0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x807E0018
		opword 0x28030000
		opword 0x41820018
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x93BE0018
		opword 0x38000000
		opword 0xB01E0020
		opword 0x801E0008
		opword 0x60002000
		opword 0x901E0008
		opword 0x801E0004
		opword 0x540007BD
		opword 0x40820044
		opword 0x807E0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820028
		opword 0x801E0004
		opword 0x54000421
		opword 0x4082001C
		opword 0x93BE0018
		opword 0x38000000
		opword 0xB01E0020
		opword 0x801E0008
		opword 0x60002000
		opword 0x901E0008
		opword 0x7FC3F378
		opword 0x38800002
		bl partyChgRunMode
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0x3800FFFF
		opword 0x901E0168
		opword 0x807F00B4
		opword 0x801F00B8
		opword 0x907E0070
		opword 0x901E0074
		opword 0x801F00BC
		opword 0x901E0078
		bl marioGetPartyId
		opword 0x2C030000
		opword 0x41800014
		opword 0x5460103A
		la r3, partyPtrTbl(r13)
		opword 0x7FC3002E
		opword 0x48000008
		opword 0x3BC00000
		opword 0x281E0000
		opword 0x41820468
		opword 0x809E0004
		opword 0x38600001
		opword 0x38000000
		opword 0x907E0000
		opword 0x549D0420
		opword 0x901E0004
		opword 0x981E0037
		bl marioGetCamId
		opword 0x281E0000
		opword 0x907E0164
		opword 0x418200AC
		opword 0x839E000C
		opword 0x2C1C0000
		opword 0x4180001C
		opword 0x7F83E378
		opword 0x3880FFFF
		bl animPoseSetMaterialFlagOff
		opword 0x7F83E378
		opword 0x38800002
		bl animPoseSetMaterialLightFlagOn
		opword 0x801E001C
		opword 0x28000000
		opword 0x41820040
		opword 0x807E000C
		opword 0x38800000
		opword 0x38A00000
		bl animPoseSetPaperAnimGroup
		opword 0x38000000
		opword 0x901E001C
		opword 0x801E0004
		opword 0x54000188
		opword 0x901E0004
		opword 0x807E0014
		opword 0x2C030000
		opword 0x41800010
		bl animPaperPoseRelease
		opword 0x3800FFFF
		opword 0x901E0014
		opword 0x38000000
		opword 0x901E0130
		opword 0x901E012C
		opword 0x901E0148
		opword 0x901E0138
		opword 0x901E013C
		opword 0x901E0134
		opword 0x901E0140
		opword 0x901E0144
		opword 0x807F00C0
		opword 0x801F00C4
		opword 0x907E0070
		opword 0x901E0074
		opword 0x801F00C8
		opword 0x901E0078
		bl partyClearFootmark
		opword 0x2C1D0000
		opword 0x41820074
		opword 0x881E0031
		opword 0x2C000004
		opword 0x41820024
		opword 0x801E0004
		opword 0x54000421
		opword 0x40820010
		lwz r3, party_dp(r13)
		opword 0x83A30000
		opword 0x48000030
		opword 0x3BBF01BC
		opword 0x48000028
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x801E0004
		opword 0x5464103A
		la r3, yoshigroup(r13)
		opword 0x54000421
		opword 0x7FA3202E
		opword 0x41820008
		opword 0x3BBF01BC
		opword 0x807E000C
		opword 0x2C030000
		opword 0x41800008
		bl animPoseRelease
		opword 0x7FA3EB78
		opword 0x38800002
		bl animPoseEntry
		opword 0x907E000C
		opword 0x881E0031
		opword 0x2C000004
		opword 0x40820010
		opword 0x881E0034
		opword 0x28000003
		opword 0x41820300
		bl marioGetPtr
		opword 0x80030000
		opword 0x54000253
		opword 0x40820168
		opword 0x801E0004
		opword 0x3BA00001
		opword 0x540007BD
		opword 0x4182000C
		opword 0x83BE0018
		opword 0x480000E8
		opword 0x881E0031
		opword 0x3B800000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BA0000C
		opword 0x801E0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889E0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57A0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x48000050
		opword 0x881E0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57A0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57A0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x807E0018
		opword 0x28030000
		opword 0x41820018
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x93BE0018
		opword 0x38000000
		opword 0xB01E0020
		opword 0x801E0008
		opword 0x60002000
		opword 0x901E0008
		opword 0x801E0004
		opword 0x540007BD
		opword 0x40820044
		opword 0x807E0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820028
		opword 0x801E0004
		opword 0x54000421
		opword 0x4082001C
		opword 0x93BE0018
		opword 0x38000000
		opword 0xB01E0020
		opword 0x801E0008
		opword 0x60002000
		opword 0x901E0008
		opword 0x7FC3F378
		opword 0x38800002
		bl partyChgRunMode
		opword 0x7FC3F378
		opword 0x38800000
		bl partyChgMot
		opword 0x48000174
		opword 0x801E0004
		opword 0x3BA00001
		opword 0x540007BD
		opword 0x4182000C
		opword 0x83BE0018
		opword 0x480000E8
		opword 0x881E0031
		opword 0x3B800000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BA0000C
		opword 0x801E0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889E0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57A0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x48000050
		opword 0x881E0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57A0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57A0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FA3002E
		opword 0x807E0018
		opword 0x28030000
		opword 0x41820018
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x4800001C
		opword 0x93BE0018
		opword 0x38000000
		opword 0xB01E0020
		opword 0x801E0008
		opword 0x60002000
		opword 0x901E0008
		opword 0x801E0004
		opword 0x540007BD
		opword 0x40820044
		opword 0x807E0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FA4EB78
		bl strcmp
		opword 0x2C030000
		opword 0x41820028
		opword 0x801E0004
		opword 0x54000421
		opword 0x4082001C
		opword 0x93BE0018
		opword 0x38000000
		opword 0xB01E0020
		opword 0x801E0008
		opword 0x60002000
		opword 0x901E0008
		opword 0x7FC3F378
		opword 0x38800002
		bl partyChgRunMode
		opword 0x38600006
		opword 0x38000000
		opword 0x987E003B
		opword 0x981E0038
		opword 0x801E0000
		opword 0x60008000
		opword 0x901E0000
		opword 0x881E0031
		opword 0x2C000007
		opword 0x4082000C
		opword 0x7FC3F378
		bl chuchu_reinit
		bl unk_8014c47c
	}
}
#pragma pop

void partyUsePost(PartyEntry* party) {
    PartyFunc func;
    if (party && party->runMode == 3) {
        func = partyDataTbl[party->currentMemberId].post_func;
        if (func) {
            func(party);
        }
    }
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void N__partyChgRunMode(PartyEntry* party, s32 prev, s32 mode) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		lis r6, vec3_802ccd30@ha
		opword 0x2C040004
		opword 0x90010024
		addi r6, r6, vec3_802ccd30@l
		opword 0x93E1001C
		opword 0x7C7F1B78
		opword 0x93C10018
		opword 0x93A10014
		opword 0x418201B8
		opword 0x40800018
		opword 0x2C040003
		opword 0x40800318
		opword 0x2C040001
		opword 0x40800340
		opword 0x48000340
		opword 0x2C04000C
		opword 0x418202EC
		opword 0x40800334
		opword 0x2C04000B
		opword 0x40800008
		opword 0x48000328
		opword 0x2C050008
		opword 0x41820320
		opword 0x80BF0160
		opword 0x8086018C
		opword 0x80060190
		opword 0x909F0070
		opword 0x901F0074
		opword 0x80060194
		opword 0x901F0078
		opword 0x80860198
		opword 0x8006019C
		opword 0x909F007C
		opword 0x901F0080
		opword 0x800601A0
		opword 0x901F0084
		opword 0xC005019C
		opword 0xD01F00FC
		opword 0xC00501A0
		opword 0xD01F0100
		opword 0xC00501AC
		opword 0xD01F0110
		opword 0x801F0000
		opword 0x54000418
		opword 0x901F0000
		bl partyClearJumpPara
		opword 0x801F0004
		opword 0x3BC00001
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881F0031
		opword 0x3BA00000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3BA00001
		opword 0x2C1D0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889F0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		opword 0x801F0004
		opword 0x281F0000
		opword 0x54000734
		opword 0x901F0004
		opword 0x801F0004
		opword 0x5400003C
		opword 0x901F0004
		opword 0x418201B4
		opword 0x801F0004
		opword 0x54000314
		opword 0x901F0004
		opword 0x480001A4
		opword 0x80BF0160
		opword 0x80860114
		opword 0x80060118
		opword 0x909F0070
		opword 0x901F0074
		opword 0x8006011C
		opword 0x901F0078
		opword 0x801F0004
		opword 0x54000734
		opword 0x901F0004
		opword 0xC005019C
		opword 0xD01F00FC
		opword 0xC00501A0
		opword 0xD01F0100
		opword 0xC00501AC
		opword 0xD01F0110
		opword 0xC00501A8
		opword 0xD01F010C
		bl partyClearJumpPara
		opword 0x801F0004
		opword 0x3BC00001
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881F0031
		opword 0x3BA00000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3BA00001
		opword 0x2C1D0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889F0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		opword 0x807F0004
		opword 0x38000001
		opword 0x54630734
		opword 0x907F0004
		opword 0x981F0034
		opword 0x48000050
		opword 0x281F0000
		opword 0x41820048
		opword 0x801F0004
		opword 0x54000314
		opword 0x901F0004
		opword 0x48000038
		opword 0x881F0031
		lis r4, partyDataTbl@ha
		addi r4, r4, partyDataTbl@l
		opword 0x7C000774
		opword 0x1C000028
		opword 0x7C840214
		opword 0x81840010
		opword 0x280C0000
		opword 0x41820014
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x48000008
		bl L_partyForceSlitOff
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop

#pragma dont_inline on
#pragma dont_inline on
#pragma dont_inline on
#pragma dont_inline on
void partyChgRunMode(PartyEntry* party, s32 mode) {
    if (party->runMode != 9 && party->runMode != 3) {
        party->prevRunMode = party->runMode;
    }
    N__partyChgRunMode(party, party->runMode, mode);
    party->runMode = mode;
    party->field_8 |= 8;
}
#pragma dont_inline reset

#pragma dont_inline reset

#pragma dont_inline reset
#pragma dont_inline reset

#pragma dont_inline on
#pragma dont_inline on
#pragma dont_inline on
#pragma dont_inline on
void N_partyForceChgRunMode(PartyEntry* party, s32 mode, s32 sub) {
    if (party->runMode != 9 && party->runMode != 3) {
        party->prevRunMode = party->runMode;
    }
    N__partyChgRunMode(party, party->runMode, mode);
    party->runMode = mode;
    party->field_8 &= ~8;
    party->field_38 = sub;
}
#pragma dont_inline reset

#pragma dont_inline reset

#pragma dont_inline reset
#pragma dont_inline reset

#pragma defer_codegen off
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
void unk_800ba2dc(PartyEntry* party) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		lis r4, vec3_802ccd30@ha
		opword 0x90010024
		addi r5, r4, vec3_802ccd30@l
		opword 0x93E1001C
		opword 0x7C7F1B78
		opword 0x93C10018
		opword 0x93A10014
		opword 0x88C30034
		opword 0x88030035
		opword 0x7C060040
		opword 0x41820404
		opword 0x28060004
		opword 0x408201A8
		opword 0x80DF0160
		opword 0x80850114
		opword 0x80050118
		opword 0x909F0070
		opword 0x901F0074
		opword 0x8005011C
		opword 0x901F0078
		opword 0x801F0004
		opword 0x54000734
		opword 0x901F0004
		opword 0xC006019C
		opword 0xD01F00FC
		opword 0xC00601A0
		opword 0xD01F0100
		opword 0xC00601AC
		opword 0xD01F0110
		opword 0xC00601A8
		opword 0xD01F010C
		bl partyClearJumpPara
		opword 0x801F0004
		opword 0x3BC00001
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881F0031
		opword 0x3BA00000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3BA00001
		opword 0x2C1D0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889F0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		opword 0x807F0004
		opword 0x281F0000
		opword 0x38000001
		opword 0x54630734
		opword 0x907F0004
		opword 0x981F0034
		opword 0x41820040
		opword 0x881F0034
		opword 0x28000003
		opword 0x40820034
		opword 0x881F0031
		lis r3, partyDataTbl@ha
		addi r3, r3, partyDataTbl@l
		opword 0x7C000774
		opword 0x1C000028
		opword 0x7C630214
		opword 0x81830010
		opword 0x280C0000
		opword 0x41820010
		opword 0x7FE3FB78
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x7FE3FB78
		opword 0x38800000
		bl partyChgMot
		opword 0x48000258
		opword 0x2806000B
		opword 0x408201D0
		opword 0x80DF0160
		opword 0x8085018C
		opword 0x80050190
		opword 0x909F0070
		opword 0x901F0074
		opword 0x80050194
		opword 0x901F0078
		opword 0x80850198
		opword 0x8005019C
		opword 0x909F007C
		opword 0x901F0080
		opword 0x800501A0
		opword 0x901F0084
		opword 0xC006019C
		opword 0xD01F00FC
		opword 0xC00601A0
		opword 0xD01F0100
		opword 0xC00601AC
		opword 0xD01F0110
		opword 0x801F0000
		opword 0x54000418
		opword 0x901F0000
		bl partyClearJumpPara
		opword 0x801F0004
		opword 0x3BC00001
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881F0031
		opword 0x3BA00000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3BA00001
		opword 0x2C1D0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889F0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		opword 0x801F0004
		opword 0x281F0000
		opword 0x54000734
		opword 0x901F0004
		opword 0x801F0004
		opword 0x5400003C
		opword 0x901F0004
		opword 0x41820010
		opword 0x801F0004
		opword 0x54000314
		opword 0x901F0004
		opword 0x281F0000
		opword 0x41820040
		opword 0x881F0034
		opword 0x28000003
		opword 0x40820034
		opword 0x881F0031
		lis r3, partyDataTbl@ha
		addi r3, r3, partyDataTbl@l
		opword 0x7C000774
		opword 0x1C000028
		opword 0x7C630214
		opword 0x81830010
		opword 0x280C0000
		opword 0x41820010
		opword 0x7FE3FB78
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x7FE3FB78
		opword 0x38800000
		bl partyChgMot
		opword 0x48000084
		opword 0x2806000C
		opword 0x40820018
		opword 0x281F0000
		opword 0x41820010
		opword 0x801F0004
		opword 0x54000314
		opword 0x901F0004
		opword 0x281F0000
		opword 0x41820040
		opword 0x881F0034
		opword 0x28000003
		opword 0x40820034
		opword 0x881F0031
		lis r3, partyDataTbl@ha
		addi r3, r3, partyDataTbl@l
		opword 0x7C000774
		opword 0x1C000028
		opword 0x7C630214
		opword 0x81830010
		opword 0x280C0000
		opword 0x41820010
		opword 0x7FE3FB78
		opword 0x7D8903A6
		opword 0x4E800421
		opword 0x881F0035
		opword 0x7FE3FB78
		opword 0x38800000
		opword 0x981F0034
		opword 0x801F0008
		opword 0x60000008
		opword 0x901F0008
		bl partyChgMot
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop

#pragma defer_codegen reset

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
asm s32 partyEntryPos(s32 memberId, f32 x, f32 y, f32 z) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stfd f29, 0x30(r1)
	psq_st f29, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	stw r29, 0x24(r1)
	stw r28, 0x20(r1)
	fmr f29, f1
	lis r4, vec3_802ccd30@ha
	fmr f30, f2
	addi r31, r4, vec3_802ccd30@l
	fmr f31, f3
	bl partyEntryMain
	mr. r28, r3
	blt L_af_1
	slwi r0, r28, 2
	la r3, partyPtrTbl(r13)
	lwzx r30, r3, r0
	b L_af_2
L_af_1:
	li r30, 0x0
L_af_2:
	lwz r3, 0xc(r31)
	li r29, 0x1
	lwz r0, 0x10(r31)
	stw r3, 0x70(r30)
	stw r0, 0x74(r30)
	lwz r0, 0x14(r31)
	stw r0, 0x78(r30)
	lwz r0, 0x18(r31)
	lwz r3, 0x1c(r31)
	stw r0, 0x8(r1)
	lwz r0, 0x20(r31)
	stw r3, 0xc(r1)
	stw r0, 0x10(r1)
	stfs f29, 0x8(r1)
	lwz r0, 0x8(r1)
	stfs f30, 0xc(r1)
	stfs f31, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0x58(r30)
	lwz r0, 0x10(r1)
	stw r3, 0x5c(r30)
	stw r0, 0x60(r30)
	lwz r4, 0x160(r30)
	lwz r3, 0x24(r31)
	lwz r0, 0x28(r31)
	stw r3, 0x70(r30)
	stw r0, 0x74(r30)
	lwz r0, 0x2c(r31)
	stw r0, 0x78(r30)
	lfs f0, 0x1a8(r4)
	stfs f0, 0x110(r30)
	lfs f0, 0x1a8(r4)
	stfs f0, 0x10c(r30)
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne L_af_3
	lbz r0, 0x31(r30)
	li r31, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge L_af_4
	bl partyGetHp
	cmpwi r3, 0x5
	bgt L_af_4
	li r31, 0x1
L_af_4:
	cmpwi r31, 0x1
	bne L_af_5
	li r29, 0xc
L_af_5:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne L_af_6
	lbz r4, 0x31(r30)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r29, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r29, r3, r0
	b L_af_7
L_af_6:
	lbz r0, 0x31(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq L_af_8
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	b L_af_7
L_af_8:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
L_af_7:
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq L_af_9
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq L_af_3
L_af_9:
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
L_af_3:
	li r0, 0x0
	mr r3, r28
	stb r0, 0x34(r30)
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	lwz r0, 0x64(r1)
	lwz r28, 0x20(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

PartyEntry* partyGetPtr(s32 index) {
    if (index >= 0) {
        return partyPtrTbl[index];
    }
    return NULL;
}

PartyEntry* anotherPartyGetPtr(s32 index) {
    if (index < 0) {
        return NULL;
    }
    return *(partyPtrTbl + ((index + 1) & 1));
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the epilogue scheduler run
BOOL partyPaperOn(PartyEntry* party, const char* animGroup) {
	asm {
		lis r5, vec3_802ccd30@ha
		addi r30, r5, vec3_802ccd30@l
		mr r29, r4
	}
	asm volatile {
		mr r28, r3
		opword 0x80630014
		opword 0x2C030000
		opword 0x41800010
		bl animPaperPoseRelease
		opword 0x3800FFFF
		opword 0x901C0014
		opword 0x801C0004
		opword 0x7FA3EB78
		opword 0x38800002
		opword 0x64000400
		opword 0x901C0004
		bl animPaperPoseEntry
		opword 0x907C0014
		opword 0x7FA3EB78
		opword 0x389E01EC
		opword 0x3BE00000
		bl strcmp
		opword 0x2C030000
		opword 0x41820040
		opword 0x7FA3EB78
		opword 0x389E01F4
		bl strcmp
		opword 0x2C030000
		opword 0x4182002C
		opword 0x7FA3EB78
		opword 0x389E01FC
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x7FA3EB78
		opword 0x389E01E0
		bl strcmp
		opword 0x2C030000
		opword 0x40820008
		opword 0x3BE00001
		opword 0x7FE00034
		opword 0x7FA3EB78
		opword 0x5400D97E
		opword 0x389E0208
		opword 0x7C1E0378
		bl strcmp
		opword 0x2C030000
		opword 0x40820018
		opword 0x881C0031
		opword 0x7C000774
		opword 0x20000005
		opword 0x7C000034
		opword 0x541ED97E
		opword 0x807C000C
		opword 0x7FA4EB78
		opword 0x7FC5F378
		bl animPoseSetPaperAnimGroup
	}
	asm {
		li r3, 0x1
	}
}
#pragma pop

void partyPaperOff(PartyEntry* party) {
    s32 paperPoseId; // r3

    if ((party->flags2 & 0x4000000) && party->field_1C) {
        animPoseSetPaperAnimGroup(party->paperAnimGroup, NULL, FALSE);
        party->field_1C = 0;
        party->flags2 &= ~0x4000000;
        paperPoseId = party->paperPoseId;
        if (paperPoseId >= 0) {
            animPaperPoseRelease(paperPoseId);
            party->paperPoseId = -1;
        }
    }
}

void partyPaperLightOff(PartyEntry* party) {
    animPoseSetMaterialLightFlagOff(party->paperAnimGroup, 1);
}

#undef partyChgPoseId
char* partyChgPoseId(PartyEntry* party, s32 index) {
    char* v6;
    char* v8;
    BOOL v5;
    s32 poseIdx = index;

    if ((party->flags2 & 2) != 0) {
        return party->animName;
    }
    v5 = 0;
    if ((party->currentMemberId < 8) && (partyGetHp(party->currentMemberId) <= 5)) {
        v5 = TRUE;
    }
    if (v5 == TRUE) {
        if (index == 1) {
            poseIdx = 12;
        } else if (index == 2) {
            poseIdx = 13;
        } else if (index == 3) {
            poseIdx = 14;
        }
    }
    if (!(party->flags2 & 0x8000)) {
        v6 = partyPoseTbl[party->currentMemberId][poseIdx];
    } else if (party->currentMemberId != PARTY_MEMBER_YOSHI) {
        v6 = partyDotPoseTbl[party->currentMemberId][poseIdx];
    } else {
        v6 = yoshiDotPoseTbl[pouchGetPartyColor(PARTNER_YOSHI)][poseIdx];
    }
    v8 = party->animName;
    if (v8 && !strcmp(v8, v6)) {
        return v6;
    }
    party->animName = v6;
    party->field_20 = 0;
    party->field_8 |= 0x2000u;
    return v6;
}
#define partyChgPoseId partyChgPoseId_inl

void partyChgPose(PartyEntry* party, char* pose) {
    if (!(party->flags2 & 2)) {
        if (party->animName == NULL || strcmp(party->animName, pose)) {
            if (!(party->flags2 & 0x8000)) {
                party->animName = pose;
                party->field_20 = 0;
                party->field_8 |= 0x2000;
            }
        }
    }
}

void partyChgPaper(PartyEntry* party, char* paper) {
    if (!(party->flags2 & 2)) {
        if (party->field_1C == 0 || strcmp((char*)party->field_1C, paper)) {
            party->field_1C = (u32)paper;
            party->field_20 = 0;
            party->field_8 |= 0x4000;
        }
    }
}

void partyCtrlOff(PartyEntry* party) {
    party = partyPtrTbl[0];
    if (party) {
        party->flags |= PARTY_FLAG_CTRL_OFF;
    }
    party = partyPtrTbl[1];
    if (party) {
        party->flags |= PARTY_FLAG_CTRL_OFF;
    }
}

void partyCtrlOn(PartyEntry* party) {
    party = partyPtrTbl[0];
    if (party) {
        party->flags &= ~PARTY_FLAG_CTRL_OFF;
    }
    party = partyPtrTbl[1];
    if (party) {
        party->flags &= ~PARTY_FLAG_CTRL_OFF;
    }
}

#pragma dont_inline on
void partyRun(PartyEntry* party) {
    if (party->runMode == 0) {
        partyChgRunMode(party, 1);
    }
}
#pragma dont_inline reset

#pragma dont_inline on
void partyStop(PartyEntry* party) {
    partyChgRunMode(party, 0);
}
#pragma dont_inline reset

#pragma dont_inline on
void partySetForceMove(PartyEntry* party, s16 a2, f32 a3, f32 a4) {
    party->targetDir = a3;
    party->field_28 = a2;
    party->moveSpeed = a4;
    partyChgRunMode(party, 9);
    partyChgMot(party, 1);
}
#pragma dont_inline reset

s32 partyEntryHello(s32 memberId) {
    s32 id = partyEntryMain(memberId);
    partyChgRunMode(partyGetPtr(id), 4);
    return id;
}

// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 partyEntry(s32 memberId) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x90010024
		opword 0x93E1001C
		opword 0x93C10018
		opword 0x93A10014
		opword 0x93810010
		bl partyEntryMain
		opword 0x7C7D1B79
		opword 0x41800014
		opword 0x57A0103A
		la r3, partyPtrTbl(r13)
		opword 0x7FE3002E
		opword 0x48000008
		opword 0x3BE00000
		lis r3, vec3_802ccd30@ha
		opword 0x3800000A
		addi r7, r3, vec3_802ccd30@l
		opword 0x7FE3FB78
		opword 0x80C70000
		opword 0x389F0058
		opword 0x80A70004
		opword 0x90DF0070
		opword 0x90BF0074
		opword 0x80A70008
		opword 0x90BF0078
		opword 0x981F0038
		opword 0x80BF0160
		opword 0xC00501A8
		opword 0xD01F0110
		opword 0xC00501A8
		opword 0xD01F010C
		bl partyGetAppearPos2
		opword 0x807F0058
		opword 0x3BC00001
		opword 0x801F005C
		opword 0x907F00B8
		opword 0x901F00BC
		opword 0x801F0060
		opword 0x901F00C0
		opword 0x801F0004
		opword 0x540007BD
		opword 0x408200E4
		opword 0x881F0031
		opword 0x3B800000
		opword 0x7C030774
		opword 0x2C030008
		opword 0x40800014
		bl partyGetHp
		opword 0x2C030005
		opword 0x41810008
		opword 0x3B800001
		opword 0x2C1C0001
		opword 0x40820008
		opword 0x3BC0000C
		opword 0x801F0004
		opword 0x54000421
		opword 0x40820028
		opword 0x889F0031
		lis r3, partyPoseTbl@ha
		addi r3, r3, partyPoseTbl@l
		opword 0x57C0103A
		opword 0x7C840774
		opword 0x1C84003C
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000050
		opword 0x881F0031
		opword 0x7C000774
		opword 0x2C000004
		opword 0x41820020
		opword 0x1C80003C
		lis r3, partyDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, partyDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x48000024
		opword 0x38600004
		bl pouchGetPartyColor
		opword 0x1C83003C
		lis r3, yoshiDotPoseTbl@ha
		opword 0x57C0103A
		addi r3, r3, yoshiDotPoseTbl@l
		opword 0x7C632214
		opword 0x7FC3002E
		opword 0x807F0018
		opword 0x28030000
		opword 0x41820014
		opword 0x7FC4F378
		bl strcmp
		opword 0x2C030000
		opword 0x4182001C
		opword 0x93DF0018
		opword 0x38000000
		opword 0xB01F0020
		opword 0x801F0008
		opword 0x60002000
		opword 0x901F0008
		opword 0x38000001
		opword 0x7FA3EB78
		opword 0x981F0034
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x83810010
		opword 0x80010024
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop


// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802ccd30[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802ccd3c[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802ccd48[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802ccd54[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const char str_802CCD60[12] = "c_babyyoshi";
__declspec(section ".rodata") const char str_802CCD6C[15] = "c_babyyoshi2\0\0\0";
__declspec(section ".rodata") const char str_802CCD7C[15] = "c_babyyoshi3\0\0\0";
__declspec(section ".rodata") const char str_802CCD8C[15] = "c_babyyoshi4\0\0\0";
__declspec(section ".rodata") const char str_802CCD9C[15] = "c_babyyoshi5\0\0\0";
__declspec(section ".rodata") const char str_802CCDAC[15] = "c_babyyoshi6\0\0\0";
__declspec(section ".rodata") const char str_802CCDBC[15] = "c_babyyoshi7\0\0\0";
__declspec(section ".rodata") const f32 vec3_802ccdcc[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802ccdd8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802ccde4[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802ccdf0[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802ccdfc[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cce08[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cce14[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802cce20[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802cce2c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cce38[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cce44[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802cce50[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cce5c[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802cce68[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cce74[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cce80[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cce8c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cce98[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802ccea4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cceb0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802ccebc[3] = {1.0f, 1.0f, 1.0f};
__declspec(section ".rodata") const f32 vec3_802ccec8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802cced4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802ccee0[3] = {0.0f, -1.0f, 0.0f};
__declspec(section ".rodata") const char str_802CCEEC[8] = "d_mario";
__declspec(section ".rodata") const f64 double_to_int_mask_802ccef8 = 4503599627370496.0;
__declspec(section ".rodata") const f64 double_to_int_802ccf00 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802CCF08[8] = "PM_D_1B";
__declspec(section ".rodata") const char str_802CCF10[11] = "p_dokan_y\0\0";
__declspec(section ".rodata") const char str_802CCF1C[7] = "p_roll\0";
__declspec(section ".rodata") const char str_802CCF24[8] = "p_plane";
__declspec(section ".rodata") const char str_802CCF2C[11] = "p_dokan_x\0\0";
__declspec(section ".rodata") const char str_802CCF38[7] = "p_slit\0";
__declspec(section ".rodata") const char str_802CCF40[8] = "PM_D_1A";
__declspec(section ".sdata2") const f32 float_neg6p8_8041b0d8 = -6.8f;
__declspec(section ".sdata2") const f32 float_6p8_8041b0dc = 6.8f;
__declspec(section ".sdata2") const f32 float_1p2_8041b0e0 = 1.2f;
__declspec(section ".sdata2") const f32 float_2_8041b0e4 = 2.0f;
__declspec(section ".sdata2") const f32 float_1_8041b0e8 = 1.0f;
__declspec(section ".sdata2") const f32 float_neg1_8041b0ec = -1.0f;
__declspec(section ".sdata2") const f32 float_90_8041b0f0 = 90.0f;
__declspec(section ".sdata2") const f32 float_270_8041b0f4 = 270.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_8041b0f8 = 0.017453292f;
__declspec(section ".sdata2") const f32 float_180_8041b0fc = 180.0f;
__declspec(section ".sdata2") const f32 float_0_8041b100 = 0.0f;
__declspec(section ".sdata2") const f32 float_3_8041b104 = 3.0f;
__declspec(section ".sdata2") const f32 float_3p5_8041b108 = 3.5f;
__declspec(section ".sdata2") const f32 float_4_8041b10c = 4.0f;
__declspec(section ".sdata2") const f32 float_0p75_8041b110 = 0.75f;
__declspec(section ".sdata2") const f32 float_5000_8041b114 = 5000.0f;
__declspec(section ".sdata2") const f32 float_10000_8041b118 = 10000.0f;
__declspec(section ".sdata2") const f32 float_13p333_8041b11c = 13.333333f;
__declspec(section ".sdata2") const f32 float_1000_8041b120 = 1000.0f;
__declspec(section ".sdata2") const f32 float_10_8041b124 = 10.0f;
__declspec(section ".sdata2") const f32 float_290_8041b128 = 290.0f;
__declspec(section ".sdata2") const f32 float_250_8041b12c = 250.0f;
__declspec(section ".sdata2") const f32 float_190_8041b130 = 190.0f;
__declspec(section ".sdata2") const f32 float_350_8041b134 = 350.0f;
__declspec(section ".sdata2") const f32 float_170_8041b138 = 170.0f;
__declspec(section ".sdata2") const f32 float_0p125_8041b13c = 0.125f;
__declspec(section ".sdata2") const f32 float_20_8041b140 = 20.0f;
__declspec(section ".sdata2") const f32 float_neg40_8041b144 = -40.0f;
__declspec(section ".sdata2") const f32 float_neg30_8041b148 = -30.0f;
__declspec(section ".sdata2") const f32 float_220_8041b14c = 220.0f;
__declspec(section ".sdata2") const f32 float_210_8041b150 = 210.0f;
__declspec(section ".sdata2") const f32 float_15_8041b154 = 15.0f;
__declspec(section ".sdata2") const f32 float_neg100_8041b158 = -100.0f;
__declspec(section ".sdata2") const f32 float_240_8041b15c = 240.0f;
__declspec(section ".sdata2") const f32 float_neg6_8041b160 = -6.0f;
__declspec(section ".sdata2") const f32 float_neg2000_8041b164 = -2000.0f;
__declspec(section ".sdata2") const f32 float_200_8041b168 = 200.0f;
__declspec(section ".sdata2") const f32 float_1p6_8041b16c = 1.6f;
__declspec(section ".sdata2") const f32 float_0p5_8041b170 = 0.5f;
__declspec(section ".sdata2") const f32 float_0p4_8041b174 = 0.4f;
__declspec(section ".sdata2") const f32 float_30_8041b178 = 30.0f;
__declspec(section ".sdata2") const f32 float_16_8041b17c = 16.0f;
__declspec(section ".sdata2") const f32 float_neg1p6_8041b180 = -1.6f;
__declspec(section ".sdata2") const f32 float_0p0625_8041b184 = 0.0625f;
__declspec(section ".sdata2") const f32 float_3p1416_8041b188 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_12_8041b18c = 12.0f;
__declspec(section ".sdata2") const f32 float_22_8041b190 = 22.0f;
__declspec(section ".sdata2") const f32 float_40_8041b194 = 40.0f;
__declspec(section ".sdata2") const f32 float_0p05_8041b198 = 0.05f;
__declspec(section ".sdata2") const f32 float_neg0p2_8041b19c = -0.2f;
__declspec(section ".sdata2") const f32 float_neg4_8041b1a0 = -4.0f;
__declspec(section ".sdata2") const f32 float_1p5_8041b1a4 = 1.5f;
__declspec(section ".sdata2") const f32 float_neg3_8041b1a8 = -3.0f;
__declspec(section ".sdata2") const f32 float_neg1p5_8041b1ac = -1.5f;
__declspec(section ".sdata2") const f32 float_26_8041b1b0 = 26.0f;
__declspec(section ".sdata2") const f32 float_neg26_8041b1b4 = -26.0f;
__declspec(section ".sdata2") const f32 float_50_8041b1b8 = 50.0f;
__declspec(section ".sdata2") const f32 float_18p5_8041b1bc = 18.5f;

#pragma force_active on
__declspec(section ".data") u32 gap_05_8031282C_data[1] = {0};  // unreferenced zero word after the jumptables in target
#pragma force_active reset


#endif