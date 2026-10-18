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

#ifdef NONMATCHING
PartyEntry* anotherPartyGetPtr(s32 index) {
    if (index < 0) {
        return NULL;
    }
    return *(partyPtrTbl + ((index + 1) & 1));
}
#endif

#ifdef NONMATCHING
BOOL partyPaperOn(PartyEntry* party, const char* animGroup) {
    BOOL flag;

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
#endif

#ifdef NONMATCHING
void partyPaperLightOff(PartyEntry* party) {
    animPoseSetMaterialLightFlagOff(party->paperAnimGroup, 1);
}
#endif





#ifdef NONMATCHING
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
#endif

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

#ifdef NONMATCHING
void partyRun(PartyEntry* party) {
    if (party->runMode == 0) {
        partyChgRunMode(party, 1);
    }
}
#endif

#ifdef NONMATCHING
void partyStop(PartyEntry* party) {
    partyChgRunMode(party, 0);
}
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

#ifdef NONMATCHING
s32 partyEntryHello(s32 memberId) {
    s32 id = partyEntryMain(memberId);
    partyChgRunMode(partyGetPtr(id), 4);
    return id;
}
#endif

#ifdef NONMATCHING
s32 partyEntry(s32 memberId) {
    PartyEntry* party;
    s32 id;
    MarioWork* player;

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

#ifdef NONMATCHING
s32 partyEntryPos(s32 memberId, f32 x, f32 y, f32 z) {
    PartyEntry* party;
    s32 index;
    s32 id;
    BOOL lowHp;
    MarioWork* player;

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

#ifdef NONMATCHING
BOOL partyGoodbye(s32 id) {
    BOOL ret = FALSE;

    if (id >= 0) {
        partyChgRunMode(partyGetPtr(id), 8);
        ret = TRUE;
    }
    return ret;
}
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
f32 partyGetHeight(PartyEntry* party) {
    if (party->currentMemberId == PARTY_MEMBER_YOSHI && (party->flags & 0x100)) {
        return 18.5f + party->height;
    }
    return party->height;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
static inline void setAnimPoseMaterialFlag(PartyEntry* party) {
    MarioWork* player = party->playerPtr;

    animPoseSetMaterialFlagOn(party->paperAnimGroup, animPoseGetMaterialFlag(player->paperAnimGroupId[marioAnimeId()]));
    animPoseSetMaterialLightFlagOn(party->paperAnimGroup,
                                   animPoseGetMaterialLightFlag(player->paperAnimGroupId[marioAnimeId()]));
}
#endif

#ifdef NONMATCHING
static inline s32 partyGetFreeSlot2(void) {
    if (partyPtrTbl[1] == NULL) {
        memset(partyPtrTbl[1] = __memAlloc(HEAP_DEFAULT, sizeof(PartyEntry)), 0, sizeof(PartyEntry));
        return 1;
    }
    return -1;
}
#endif


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

#ifdef NONMATCHING
s32 partyEntry2(s32 memberId) {
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
    party->position = player->position;
    party->field_B8 = party->position;
    party->scale = (Vec){1.0f, 1.0f, 1.0f};
    party->runMode = 0;
    return slot;
}
#endif

#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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
#ifdef NONMATCHING
static inline void partyShadowOn(PartyEntry* party) {
    if (party) {
        party->flags2 &= ~0x100000;
    }
}
#endif
#define PU16(p, o) (*(u16*)((u8*)(p) + (o)))
#define PF32(p, o) (*(f32*)((u8*)(p) + (o)))

#ifdef NONMATCHING
void partyInit(void) {
    memset(partyPtrTbl, 0, sizeof(partyPtrTbl));
}
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
#endif
#ifdef NONMATCHING
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


static inline void partyChgRunM(PartyEntry* party);
static inline void partyChgRunMo(PartyEntry* party);
#ifdef NONMATCHING
void N__partyChgRunMode(PartyEntry* party, s32 prev, s32 mode) {
    MarioWork* mario;
    PartyFunc func;

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

#pragma dont_inline on
#ifdef NONMATCHING
void partyChgRunMode(PartyEntry* party, s32 mode) {
    if (party->runMode != 9 && party->runMode != 3) {
        party->prevRunMode = party->runMode;
    }
    N__partyChgRunMode(party, party->runMode, mode);
    party->runMode = mode;
    party->field_8 |= 8;
}
#endif
#pragma dont_inline reset

#pragma dont_inline on
#ifdef NONMATCHING
void N_partyForceChgRunMode(PartyEntry* party, s32 mode, s32 sub) {
    if (party->runMode != 9 && party->runMode != 3) {
        party->prevRunMode = party->runMode;
    }
    N__partyChgRunMode(party, party->runMode, mode);
    party->runMode = mode;
    party->field_8 &= ~8;
    party->field_38 = sub;
}
#endif
#pragma dont_inline reset

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


#ifdef NONMATCHING
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
#endif
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
#endif
#ifdef NONMATCHING
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


#ifdef NONMATCHING
void partyHello(PartyEntry* party) {
    partyHello_inl(party);
}
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

void L_partyVivianTailStop(PartyEntry* party);

#ifdef NONMATCHING
static inline void partyPaperOn_inl(PartyEntry* party, const char* animGroup) {
    BOOL v4;
    BOOL v5;

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

#ifdef NONMATCHING
static inline void partyChgRunM(PartyEntry* party) {
    party->scale = (Vec){1.0f, 1.0f, 1.0f};
}
#endif
#ifdef NONMATCHING
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
#endif

#ifdef NONMATCHING
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


#pragma dont_inline on
#ifdef NONMATCHING
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
#endif
#pragma dont_inline reset

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
#endif
#ifdef NONMATCHING
static inline void partyChgRunMo(PartyEntry* party) {
    party->scale = (Vec){1.0f, 1.0f, 1.0f};
    *(Vec*)((u8*)party + 0x7C) = (Vec){0.0f, 0.0f, 0.0f};
}
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


#ifdef NONMATCHING
void partyInitCamId(PartyEntry* party) {
    party->camId = marioGetCamId();
}
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
#endif

#ifdef NONMATCHING
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


#ifdef NONMATCHING
void partyKeyOn(void) {
}
#endif

#ifdef NONMATCHING
void partyKeyOff(void) {
}
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

#ifdef NONMATCHING
void partyShadowOff(PartyEntry* party) {
    if (party) {
        party->flags2 |= 0x100000;
    }
}
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
// ASM-STOPGAP: partyGetPtr (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802ccd30[3] = { 1.0f, 1.0f, 1.0f };
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802ccd3c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ccd48[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ccd54[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const char str_802CCD60[] = "c_babyyoshi";
__declspec(section ".rodata") const char str_802CCD6C[] = "c_babyyoshi2\000\000\000";
__declspec(section ".rodata") const char str_802CCD7C[] = "c_babyyoshi3\000\000\000";
__declspec(section ".rodata") const char str_802CCD8C[] = "c_babyyoshi4\000\000\000";
__declspec(section ".rodata") const char str_802CCD9C[] = "c_babyyoshi5\000\000\000";
__declspec(section ".rodata") const char str_802CCDAC[] = "c_babyyoshi6\000\000\000";
__declspec(section ".rodata") const char str_802CCDBC[] = "c_babyyoshi7\000\000\000";
__declspec(section ".rodata") const f32 vec3_802ccdcc[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ccdd8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ccde4[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ccdf0[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ccdfc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cce08[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cce14[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802cce20[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802cce2c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cce38[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cce44[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802cce50[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cce5c[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802cce68[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cce74[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cce80[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cce8c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cce98[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ccea4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cceb0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ccebc[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802ccec8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802cced4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802ccee0[3] = { 0.0f, -1.0f, 0.0f };
__declspec(section ".rodata") const char str_802CCEEC[] = "d_mario";
__declspec(section ".rodata") const f64 double_to_int_mask_802ccef8 = 4503599627370496;
__declspec(section ".rodata") const f64 double_to_int_802ccf00 = 4503601774854144;
__declspec(section ".rodata") const char str_802CCF08[] = "PM_D_1B";
__declspec(section ".rodata") const char str_802CCF10[] = "p_dokan_y\000\000";
__declspec(section ".rodata") const char str_802CCF1C[] = "p_roll\000";
__declspec(section ".rodata") const char str_802CCF24[] = "p_plane";
__declspec(section ".rodata") const char str_802CCF2C[] = "p_dokan_x\000\000";
__declspec(section ".rodata") const char str_802CCF38[] = "p_slit\000";
__declspec(section ".rodata") const char str_802CCF40[] = "PM_D_1A";
#pragma force_active reset
#pragma force_active on
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

void party_damage_return(PartyEntry* party);
#pragma force_active on
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
s32 partyGoodbyeMain(PartyEntry* party);
#pragma force_active on
__declspec(section ".data") static void* jumptable_80312720[] = {
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
s32 partyHelloMain(PartyEntry* party);
#pragma force_active on
__declspec(section ".data") static void* jumptable_80312774[] = {
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
void driveParty(PartyEntry* party);
#pragma force_active on
__declspec(section ".data") static void* jumptable_803127F0[] = {
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
void N__partyChgRunMode(PartyEntry* party, s32 prev, s32 mode);
void N_partyForceChgRunMode(PartyEntry* party, s32 mode, s32 sub);
void PSMTX44MultVec(const Mtx44 m, const Vec* src, Vec* dst);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void* __memAlloc(HEAP_TYPE heap, u32 size);
void __memFree(HEAP_TYPE heap, void* ptr);
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
s32 animPaperPoseEntry(const char* animName, s32 type);
void animPaperPoseRelease(s32 poseId);
void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
s32 animPoseEntry(const char* animName, s32 type);
u32 animPoseGetMaterialFlag(s32 poseId);
u32 animPoseGetMaterialLightFlag(s32 poseId);
void animPoseMain(s32 poseId);
void animPosePeraOff(s32 poseId);
void animPoseRelease(s32 poseId);
void animPoseSetAnim(s32 poseId, const char* animName, BOOL reset);
void animPoseSetLocalTime(s32 poseId, f32 localTimeFrames);
void animPoseSetLocalTimeRate(s32 poseId, f32 localTimeRate);
void animPoseSetMaterialFlagOff(s32 poseId, u32 mask);
void animPoseSetMaterialFlagOn(s32 poseId, u32 mask);
void animPoseSetMaterialLightFlagOff(s32 poseId, u32 mask);
void animPoseSetMaterialLightFlagOn(s32 poseId, u32 mask);
void animPoseSetPaperAnim(s32 poseId, const char* animName, BOOL reset);
void animPoseSetPaperAnimGroup(s32 poseId, const char* animName, BOOL someflag);
CameraEntry* camGetPtr(CameraId cameraId);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
f32 distABf(f32 x1, f32 y1, f32 x2, f32 y2);
s32 irand(s32 scalar);
s32 marioAnimeId(void);
BOOL marioBgmodeChk(void);
BOOL marioChkInScreen(s32 x, s32 y);
s32 marioGetCamId(void);
s32 marioGetExtraPartyId(void);
s32 marioGetPartyId(void);
MarioWork* marioGetPtr(void);
void *memset(void *dest, int ch, size_t count);
void movePos(float* ret_sin, float* ret_cos, f32 a3, f32 degree);
s32 partyGetHp(PartyId partnerId);
void partyMakeDispDir(PartyEntry* party);
s32 pouchGetPartyColor(PartyId partnerId);
void pouchSetPartyColor(PartyId partnerId, s32 color);
s32 psndSFXOn_3D(const char* name, Vec* position);
f32 revise360(f32 angle);
void sincosf(f32* ret_sin, f32* ret_cos, f32 degree);
int strcmp(const char *s1, const char *s2);
s32 unk_8013be14(void);
asm void partySetFamicomMode(PartyEntry* party, s32 mode) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	cmpwi r4, 0x1
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	bne @1
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @2
	bl L_partyForceSlitOff
	lwz r0, 0x4(r31)
	ori r0, r0, 0x8000
	stw r0, 0x4(r31)
	lbz r0, 0x31(r31)
	cmpwi r0, 0x4
	beq @3
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @4
	lwz r3, party_dp(r13)
	lwz r30, 0x0(r3)
	b @5
	@4:
	lis r3, str_802CCEEC@ha
	addi r30, r3, str_802CCEEC@l
	b @5
	@3:
	li r3, 0x4
	bl pouchGetPartyColor
	lwz r0, 0x4(r31)
	slwi r4, r3, 2
	la r3, yoshigroup(r13)
	rlwinm. r0, r0, 0, 16, 16
	lwzx r30, r3, r4
	beq @5
	lis r3, str_802CCEEC@ha
	addi r30, r3, str_802CCEEC@l
	@5:
	lwz r3, 0xc(r31)
	cmpwi r3, 0x0
	blt @6
	bl animPoseRelease
	@6:
	mr r3, r30
	li r4, 0x2
	bl animPoseEntry
	stw r3, 0xc(r31)
	li r30, 0x1
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq @7
	lwz r30, 0x18(r31)
	b @8
	@7:
	lbz r0, 0x31(r31)
	li r29, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @9
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @9
	li r29, 0x1
	@9:
	cmpwi r29, 0x1
	bne @10
	li r30, 0xc
	@10:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @11
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @12
	@11:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @13
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @12
	@13:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@12:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @14
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne @14
	b @8
	@14:
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@8:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 30, 30
	bne @2
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @15
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	@15:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @2
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	b @2
	@1:
	lwz r3, 0x4(r31)
	rlwinm. r0, r3, 0, 16, 16
	beq @2
	rlwinm r0, r3, 0, 17, 15
	stw r0, 0x4(r31)
	lbz r0, 0x31(r31)
	cmpwi r0, 0x4
	beq @16
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @17
	lwz r3, party_dp(r13)
	lwz r30, 0x0(r3)
	b @18
	@17:
	lis r3, str_802CCEEC@ha
	addi r30, r3, str_802CCEEC@l
	b @18
	@16:
	li r3, 0x4
	bl pouchGetPartyColor
	lwz r0, 0x4(r31)
	slwi r4, r3, 2
	la r3, yoshigroup(r13)
	rlwinm. r0, r0, 0, 16, 16
	lwzx r30, r3, r4
	beq @18
	lis r3, str_802CCEEC@ha
	addi r30, r3, str_802CCEEC@l
	@18:
	lwz r3, 0xc(r31)
	cmpwi r3, 0x0
	blt @19
	bl animPoseRelease
	@19:
	mr r3, r30
	li r4, 0x2
	bl animPoseEntry
	stw r3, 0xc(r31)
	li r30, 0x1
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq @20
	lwz r30, 0x18(r31)
	b @21
	@20:
	lbz r0, 0x31(r31)
	li r29, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @22
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @22
	li r29, 0x1
	@22:
	cmpwi r29, 0x1
	bne @23
	li r30, 0xc
	@23:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @24
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @25
	@24:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @26
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @25
	@26:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@25:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @27
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne @27
	b @21
	@27:
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@21:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 30, 30
	bne @2
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @28
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	@28:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @2
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void partyShadowOff(PartyEntry* party) {
	nofralloc
	cmplwi r3, 0x0
	beqlr
	lwz r0, 0x4(r3)
	oris r0, r0, 0x10
	stw r0, 0x4(r3)
	blr
}

asm void partyUpdateKeyData(PartyEntry* party) {
	nofralloc
	lwz r0, 0x0(r3)
	lbz r6, 0x30(r3)
	rlwinm. r0, r0, 0, 1, 2
	extsb r6, r6
	beq @1
	li r0, 0x0
	stb r0, 0x158(r3)
	stb r0, 0x159(r3)
	stb r0, 0x15a(r3)
	stb r0, 0x15b(r3)
	stb r0, 0x15c(r3)
	stb r0, 0x15d(r3)
	stb r0, 0x15e(r3)
	stb r0, 0x15f(r3)
	sth r0, 0x150(r3)
	sth r0, 0x152(r3)
	sth r0, 0x154(r3)
	sth r0, 0x156(r3)
	blr
	@1:
	lwz r5, gp(r13)
	li r4, 0x0
	slwi r0, r6, 2
	add r5, r5, r6
	lbz r5, 0x13b8(r5)
	stb r5, 0x158(r3)
	lwz r5, gp(r13)
	add r5, r5, r6
	lbz r5, 0x13bc(r5)
	neg r5, r5
	stb r5, 0x159(r3)
	lwz r5, gp(r13)
	add r5, r5, r6
	lbz r5, 0x13c0(r5)
	stb r5, 0x15a(r3)
	lwz r5, gp(r13)
	add r5, r5, r6
	lbz r5, 0x13c4(r5)
	neg r5, r5
	stb r5, 0x15b(r3)
	lwz r5, gp(r13)
	add r5, r5, r6
	lbz r5, 0x13c8(r5)
	stb r5, 0x15c(r3)
	lwz r5, gp(r13)
	add r5, r5, r6
	lbz r5, 0x13cc(r5)
	stb r5, 0x15d(r3)
	stb r4, 0x15e(r3)
	stb r4, 0x15f(r3)
	lwz r4, gp(r13)
	add r4, r4, r0
	lwz r4, 0x1328(r4)
	sth r4, 0x150(r3)
	lwz r4, gp(r13)
	add r4, r4, r0
	lwz r4, 0x1338(r4)
	sth r4, 0x152(r3)
	lwz r4, gp(r13)
	add r4, r4, r0
	lwz r4, 0x1348(r4)
	sth r4, 0x154(r3)
	lwz r4, gp(r13)
	add r4, r4, r0
	lwz r0, 0x1368(r4)
	sth r0, 0x156(r3)
	blr
}

asm void L_partyClearCont(PartyEntry* party) {
	nofralloc
	li r0, 0x0
	stb r0, 0x158(r3)
	stb r0, 0x159(r3)
	stb r0, 0x15a(r3)
	stb r0, 0x15b(r3)
	stb r0, 0x15c(r3)
	stb r0, 0x15d(r3)
	stb r0, 0x15e(r3)
	stb r0, 0x15f(r3)
	sth r0, 0x150(r3)
	sth r0, 0x152(r3)
	sth r0, 0x154(r3)
	sth r0, 0x156(r3)
	blr
}

asm void partyKeyOff(void) {
	nofralloc
	blr
}

asm void partyKeyOn(void) {
	nofralloc
	blr
}

asm void partyDisp(CameraId cam, void* param) {
	nofralloc
	stwu r1, -0xa0(r1)
	mflr r0
	la r5, partyPtrTbl(r13)
	li r3, 0x0
	stw r0, 0xa4(r1)
	stw r31, 0x9c(r1)
	mr r31, r4
	lwz r4, partyPtrTbl(r13)
	cmplwi r4, 0x0
	beq @1
	cmpwi r3, 0x0
	blt @2
	b @3
	@2:
	mr r4, r3
	@3:
	lwz r0, 0x0(r4)
	clrlwi. r0, r0, 31
	beq @1
	li r3, 0x1
	@1:
	lwz r4, 0x4(r5)
	li r0, 0x1
	cmplwi r4, 0x0
	beq @4
	cmpwi r0, 0x0
	blt @5
	b @6
	@5:
	li r4, 0x0
	@6:
	lwz r0, 0x0(r4)
	clrlwi. r0, r0, 31
	beq @4
	addi r3, r3, 0x1
	@4:
	cmpwi r3, 0x0
	beq @7
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 22, 22
	beq @8
	lfs f1, float_neg6p8_8041b0d8(r2)
	lfs f0, float_6p8_8041b0dc(r2)
	stfs f1, 0x88(r31)
	stfs f0, 0x8c(r31)
	@8:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 8, 8
	beq @9
	lfs f3, float_1p2_8041b0e0(r2)
	b @10
	@9:
	lfs f3, float_2_8041b0e4(r2)
	@10:
	lfs f1, 0x70(r31)
	addi r3, r1, 0x68
	lfs f2, 0x74(r31)
	lfs f0, 0x78(r31)
	fmuls f1, f1, f3
	fmuls f2, f2, f3
	fmuls f3, f0, f3
	bl PSMTXScale
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 28, 28
	bne @11
	lfs f1, 0x10c(r31)
	bl revise360
	fmr f3, f1
	lfs f0, float_90_8041b0f0(r2)
	lfs f1, float_1_8041b0e8(r2)
	addi r3, r1, 0x8
	li r0, 0x0
	fcmpo cr0, f3, f0
	fmr f2, f1
	cror eq, gt, eq
	bne @12
	lfs f0, float_270_8041b0f4(r2)
	fcmpo cr0, f3, f0
	cror eq, lt, eq
	bne @12
	li r0, 0x1
	@12:
	cmpwi r0, 0x0
	beq @13
	lfs f3, float_neg1_8041b0ec(r2)
	b @14
	@13:
	lfs f3, float_1_8041b0e8(r2)
	@14:
	bl PSMTXScale
	addi r4, r1, 0x68
	addi r3, r1, 0x8
	mr r5, r4
	bl PSMTXConcat
	@11:
	lfs f1, 0x88(r31)
	addi r3, r1, 0x38
	lfs f2, 0x8c(r31)
	lfs f0, 0x90(r31)
	fneg f1, f1
	fneg f2, f2
	fneg f3, f0
	bl PSMTXTrans
	addi r4, r1, 0x68
	addi r3, r1, 0x38
	mr r5, r4
	bl PSMTXConcat
	lfs f1, float_deg2rad_8041b0f8(r2)
	addi r3, r1, 0x38
	lfs f0, 0x6c(r31)
	li r4, 0x7a
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r4, r1, 0x68
	addi r3, r1, 0x38
	mr r5, r4
	bl PSMTXConcat
	lfs f1, float_deg2rad_8041b0f8(r2)
	addi r3, r1, 0x38
	lfs f0, 0x64(r31)
	li r4, 0x78
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r4, r1, 0x68
	addi r3, r1, 0x38
	mr r5, r4
	bl PSMTXConcat
	lfs f1, 0x10c(r31)
	lfs f0, 0xf8(r31)
	fsubs f1, f1, f0
	bl revise360
	lfs f0, float_deg2rad_8041b0f8(r2)
	addi r3, r1, 0x38
	li r4, 0x79
	fmuls f1, f0, f1
	bl PSMTXRotRad
	addi r4, r1, 0x68
	addi r3, r1, 0x38
	mr r5, r4
	bl PSMTXConcat
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 24, 25
	beq @15
	lfs f1, 0x10c(r31)
	bl revise360
	lfs f0, float_90_8041b0f0(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @16
	lfs f0, float_270_8041b0f4(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @16
	lwz r0, 0x4(r31)
	addi r3, r1, 0x38
	lfs f1, float_deg2rad_8041b0f8(r2)
	li r4, 0x79
	rlwinm. r0, r0, 0, 25, 25
	beq @17
	lfs f0, float_180_8041b0fc(r2)
	b @18
	@17:
	lfs f0, float_0_8041b100(r2)
	@18:
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r4, r1, 0x68
	addi r3, r1, 0x38
	mr r5, r4
	bl PSMTXConcat
	b @15
	@16:
	lwz r0, 0x4(r31)
	addi r3, r1, 0x38
	lfs f1, float_deg2rad_8041b0f8(r2)
	li r4, 0x79
	rlwinm. r0, r0, 0, 25, 25
	beq @19
	lfs f0, float_0_8041b100(r2)
	b @20
	@19:
	lfs f0, float_180_8041b0fc(r2)
	@20:
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r4, r1, 0x68
	addi r3, r1, 0x38
	mr r5, r4
	bl PSMTXConcat
	@15:
	lfs f1, 0x88(r31)
	addi r3, r1, 0x38
	lfs f2, 0x8c(r31)
	lfs f3, 0x90(r31)
	bl PSMTXTrans
	addi r4, r1, 0x68
	addi r3, r1, 0x38
	mr r5, r4
	bl PSMTXConcat
	lwz r0, 0x1c(r31)
	lfs f5, float_0_8041b100(r2)
	cmplwi r0, 0x0
	beq @21
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	bne @22
	lfs f5, float_1_8041b0e8(r2)
	b @21
	@22:
	cmpwi r0, 0x3
	bne @23
	lfs f5, float_2_8041b0e4(r2)
	b @21
	@23:
	cmpwi r0, 0x7
	bne @24
	lfs f5, float_2_8041b0e4(r2)
	b @21
	@24:
	cmpwi r0, 0x1
	bne @25
	lfs f5, float_2_8041b0e4(r2)
	b @21
	@25:
	cmpwi r0, 0xb
	bne @26
	lfs f5, float_3_8041b104(r2)
	b @21
	@26:
	cmpwi r0, 0x8
	bne @27
	lfs f5, float_3p5_8041b108(r2)
	b @21
	@27:
	cmpwi r0, 0xa
	bne @28
	lfs f5, float_4_8041b10c(r2)
	b @21
	@28:
	cmpwi r0, 0x9
	bne @21
	lfs f5, float_neg1_8041b0ec(r2)
	@21:
	lfs f1, 0x5c(r31)
	addi r3, r1, 0x38
	lfs f0, 0x80(r31)
	lfs f4, 0x58(r31)
	fadds f2, f1, f0
	lfs f1, 0x7c(r31)
	lfs f3, 0x60(r31)
	lfs f0, 0x84(r31)
	fadds f1, f4, f1
	fadds f2, f5, f2
	fadds f3, f3, f0
	bl PSMTXTrans
	addi r4, r1, 0x68
	addi r3, r1, 0x38
	mr r5, r4
	bl PSMTXConcat
	lwz r3, 0xc(r31)
	addi r4, r1, 0x68
	lfs f1, float_0_8041b100(r2)
	li r5, 0x2
	lfs f2, float_1_8041b0e8(r2)
	bl animPoseDrawMtx
	lwz r3, 0xc(r31)
	addi r4, r1, 0x68
	lfs f1, float_0_8041b100(r2)
	li r5, 0x1
	lfs f2, float_1_8041b0e8(r2)
	bl animPoseDrawMtx
	lwz r0, 0x0(r31)
	lwz r3, 0xc(r31)
	rlwinm. r0, r0, 0, 24, 24
	beq @29
	lfs f1, float_0p75_8041b110(r2)
	b @30
	@29:
	lfs f1, float_1_8041b0e8(r2)
	@30:
	bl animPoseSetLocalTimeRate
	@7:
	lwz r0, 0xa4(r1)
	lwz r31, 0x9c(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}

asm void partyPreDisp(PartyEntry* party) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stw r31, 0x5c(r1)
	stw r30, 0x58(r1)
	lwz r0, 0x4(r3)
	mr r30, r3
	rlwinm. r0, r0, 0, 27, 27
	bne @1
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 22, 22
	bne @1
	bl partyMakeDispDir
	@1:
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 17, 18
	beq @2
	rlwinm. r0, r3, 0, 18, 18
	beq @3
	rlwinm r0, r3, 0, 19, 17
	stw r0, 0x8(r30)
	@3:
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 17, 17
	beq @4
	rlwinm r0, r3, 0, 18, 16
	stw r0, 0x8(r30)
	@4:
	lwz r3, 0xc(r30)
	li r5, 0x1
	lwz r4, 0x18(r30)
	bl animPoseSetAnim
	lwz r4, 0x1c(r30)
	cmplwi r4, 0x0
	beq @5
	lwz r3, 0xc(r30)
	li r5, 0x1
	bl animPoseSetPaperAnim
	@5:
	lhz r5, 0x20(r30)
	lis r0, 0x4330
	lis r3, double_to_int_mask_802ccef8@ha
	stw r0, 0x48(r1)
	addi r4, r3, double_to_int_mask_802ccef8@l
	lwz r3, 0xc(r30)
	stw r5, 0x4c(r1)
	lfd f1, 0x0(r4)
	lfd f0, 0x48(r1)
	fsubs f1, f0, f1
	bl animPoseSetLocalTime
	@2:
	lwz r3, 0xc(r30)
	bl animPoseMain
	lwz r0, 0x4(r30)
	clrlwi. r0, r0, 31
	bne @6
	lwz r4, 0x58(r30)
	li r3, 0x4
	lwz r0, 0x5c(r30)
	stw r4, 0x3c(r1)
	stw r0, 0x40(r1)
	lwz r0, 0x60(r30)
	stw r0, 0x44(r1)
	bl camGetPtr
	addi r4, r1, 0x3c
	addi r3, r3, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f2, float_5000_8041b114(r2)
	lfs f1, 0x44(r1)
	lfs f0, float_0_8041b100(r2)
	fmadds f1, f2, f1, f2
	fcmpo cr0, f1, f0
	bge @7
	fmr f1, f0
	b @8
	@7:
	lfs f0, float_10000_8041b118(r2)
	fcmpo cr0, f1, f0
	ble @8
	fmr f1, f0
	@8:
	lfs f0, float_neg1_8041b0ec(r2)
	lha r0, 0x2a(r30)
	fmuls f1, f1, f0
	cmpwi r0, 0x0
	ble @9
	rlwinm. r0, r0, 0, 30, 30
	bne @10
	lis r3, partyDisp@ha
	mr r6, r30
	addi r5, r3, partyDisp@l
	lwz r3, 0x164(r30)
	li r4, 0x1
	bl dispEntry
	b @10
	@9:
	lis r3, partyDisp@ha
	mr r6, r30
	addi r5, r3, partyDisp@l
	lwz r3, 0x164(r30)
	li r4, 0x1
	bl dispEntry
	@10:
	lbz r0, 0x31(r30)
	li r31, 0x2
	lfs f31, float_13p333_8041b11c(r2)
	cmpwi r0, 0x6
	beq @11
	lwz r3, 0x58(r30)
	lwz r0, 0x5c(r30)
	stw r3, 0xb8(r30)
	stw r0, 0xbc(r30)
	lwz r0, 0x60(r30)
	stw r0, 0xc0(r30)
	b @12
	@11:
	lbz r0, 0x34(r30)
	cmplwi r0, 0x4
	beq @13
	cmplwi r0, 0x8
	bne @14
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 23, 23
	bne @14
	@13:
	lwz r3, 0x58(r30)
	lwz r0, 0x5c(r30)
	stw r3, 0xb8(r30)
	stw r0, 0xbc(r30)
	lwz r0, 0x60(r30)
	stw r0, 0xc0(r30)
	@14:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 23, 23
	beq @12
	clrrwi. r0, r3, 31
	lfs f31, 0x174(r30)
	beq @12
	li r31, 0x1
	@12:
	mr r3, r30
	bl N_vivianDisplayTailCheck
	cmpwi r3, 0x0
	beq @15
	lfs f1, float_1000_8041b120(r2)
	lis r3, vec3_802ccee0@ha
	addi r11, r3, vec3_802ccee0@l
	lfs f0, float_10_8041b124(r2)
	stfs f1, 0x8(r1)
	mr r3, r30
	lwz r10, 0x0(r11)
	addi r4, r1, 0x30
	lwz r12, 0x58(r30)
	addi r5, r1, 0x24
	lwz r0, 0x5c(r30)
	addi r6, r1, 0x18
	lwz r9, 0x4(r11)
	addi r7, r1, 0xc
	stw r0, 0x34(r1)
	addi r8, r1, 0x8
	lwz r0, 0x8(r11)
	lfs f1, 0x34(r1)
	stw r12, 0x30(r1)
	fadds f0, f1, f0
	lwz r11, 0x60(r30)
	stw r11, 0x38(r1)
	stfs f0, 0x34(r1)
	stw r10, 0x24(r1)
	stw r9, 0x28(r1)
	stw r0, 0x2c(r1)
	bl partyHitCheck
	cmplwi r3, 0x0
	beq @16
	lfs f0, 0x1c(r1)
	b @17
	@16:
	lfs f0, 0x5c(r30)
	@17:
	stfs f0, 0xbc(r30)
	addi r4, r30, 0xb8
	lwz r3, 0xc(r30)
	bl animPoseVivianMain
	@15:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 11, 11
	bne @6
	fmr f4, f31
	lfs f1, 0xb8(r30)
	lfs f2, 0xbc(r30)
	mr r3, r31
	lfs f3, 0xc0(r30)
	bl shadowEntryMode
	lwz r4, 0x164(r30)
	mr r31, r3
	cmpwi r4, 0x4
	beq @18
	bl shadowSetCamId
	@18:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 10, 10
	beq @6
	mr r3, r31
	li r4, 0x4
	bl shadowFlagOn
	@6:
	psq_l f31, 0x68(r1), 0, 0
	lwz r0, 0x74(r1)
	lfd f31, 0x60(r1)
	lwz r31, 0x5c(r1)
	lwz r30, 0x58(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void partyMakeDispDir(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r3, 0x4(r3)
	rlwinm. r0, r3, 0, 23, 23
	bne @1
	rlwinm. r0, r3, 0, 27, 27
	bne @2
	lfs f1, 0xfc(r31)
	lfs f0, 0xf8(r31)
	fsubs f1, f1, f0
	bl revise360
	lwz r0, 0x4(r31)
	lfs f3, 0x110(r31)
	rlwinm. r0, r0, 0, 23, 23
	bne @3
	lfs f0, float_290_8041b128(r2)
	fcmpu cr0, f0, f3
	beq @4
	lfs f0, float_250_8041b12c(r2)
	fcmpu cr0, f0, f3
	bne @3
	@4:
	lfs f3, float_180_8041b0fc(r2)
	fcmpo cr0, f1, f3
	cror eq, gt, eq
	bne @3
	lfs f3, float_0_8041b100(r2)
	@3:
	lfs f0, 0x104(r31)
	lfs f2, float_0_8041b100(r2)
	fcmpu cr0, f0, f2
	beq @5
	lfs f0, float_190_8041b130(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @6
	lfs f0, float_350_8041b134(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @6
	fmr f3, f2
	b @5
	@6:
	lfs f0, float_10_8041b124(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @5
	lfs f0, float_170_8041b138(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @5
	lfs f3, float_180_8041b0fc(r2)
	@5:
	stfs f3, 0x110(r31)
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 26, 26
	beq @7
	lfs f0, 0x110(r31)
	stfs f0, 0x10c(r31)
	@7:
	lfs f1, 0x10c(r31)
	lfs f0, 0x110(r31)
	fcmpu cr0, f1, f0
	beq @1
	@2:
	lfs f2, 0x10c(r31)
	lfs f1, float_180_8041b0fc(r2)
	fcmpo cr0, f2, f1
	cror eq, lt, eq
	bne @8
	lfs f0, float_0_8041b100(r2)
	lfs f3, 0x110(r31)
	fcmpu cr0, f0, f3
	bne @9
	lwz r0, 0x8(r31)
	lfs f1, float_0p125_8041b13c(r2)
	rlwinm. r0, r0, 0, 19, 19
	beq @10
	lfs f0, float_20_8041b140(r2)
	b @11
	@10:
	lfs f0, float_neg40_8041b144(r2)
	@11:
	fsubs f0, f0, f2
	fmuls f0, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x10c(r31)
	lwz r3, 0x8(r31)
	rlwinm. r0, r3, 0, 19, 19
	bne @12
	lfs f1, 0x10c(r31)
	lfs f0, float_neg30_8041b148(r2)
	fcmpo cr0, f1, f0
	bge @1
	ori r0, r3, 0x1000
	stw r0, 0x8(r31)
	b @1
	@12:
	lfs f1, 0x10c(r31)
	lfs f0, float_0_8041b100(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @1
	stfs f0, 0x10c(r31)
	lwz r0, 0x8(r31)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x8(r31)
	b @1
	@9:
	fcmpu cr0, f1, f3
	bne @1
	lwz r0, 0x8(r31)
	lfs f1, float_0p125_8041b13c(r2)
	rlwinm. r0, r0, 0, 19, 19
	beq @13
	lfs f0, float_170_8041b138(r2)
	b @14
	@13:
	lfs f0, float_220_8041b14c(r2)
	@14:
	fsubs f0, f0, f2
	fmuls f0, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x10c(r31)
	lwz r3, 0x8(r31)
	rlwinm. r0, r3, 0, 19, 19
	bne @15
	lfs f1, 0x10c(r31)
	lfs f0, float_210_8041b150(r2)
	fcmpo cr0, f1, f0
	ble @1
	ori r0, r3, 0x1000
	stw r0, 0x8(r31)
	b @1
	@15:
	lfs f1, 0x10c(r31)
	lfs f0, float_180_8041b0fc(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @1
	stfs f0, 0x10c(r31)
	lwz r0, 0x8(r31)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x8(r31)
	b @1
	@8:
	fcmpo cr0, f2, f1
	ble @1
	lfs f0, float_0_8041b100(r2)
	lfs f3, 0x110(r31)
	fcmpu cr0, f0, f3
	bne @16
	lwz r0, 0x8(r31)
	lfs f1, float_0p125_8041b13c(r2)
	rlwinm. r0, r0, 0, 19, 19
	beq @17
	lfs f0, float_20_8041b140(r2)
	b @18
	@17:
	lfs f0, float_neg40_8041b144(r2)
	@18:
	fsubs f0, f0, f2
	fmuls f0, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x10c(r31)
	lwz r3, 0x8(r31)
	rlwinm. r0, r3, 0, 19, 19
	bne @19
	lfs f1, 0x10c(r31)
	lfs f0, float_neg30_8041b148(r2)
	fcmpo cr0, f1, f0
	bge @1
	ori r0, r3, 0x1000
	stw r0, 0x8(r31)
	b @1
	@19:
	lfs f1, 0x10c(r31)
	lfs f0, float_0_8041b100(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @1
	stfs f0, 0x10c(r31)
	lwz r0, 0x8(r31)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x8(r31)
	b @1
	@16:
	fcmpu cr0, f1, f3
	bne @1
	lwz r0, 0x8(r31)
	lfs f1, float_0p125_8041b13c(r2)
	rlwinm. r0, r0, 0, 19, 19
	beq @20
	lfs f0, float_170_8041b138(r2)
	b @21
	@20:
	lfs f0, float_220_8041b14c(r2)
	@21:
	fsubs f0, f0, f2
	fmuls f0, f1, f0
	fadds f0, f2, f0
	stfs f0, 0x10c(r31)
	lwz r3, 0x8(r31)
	rlwinm. r0, r3, 0, 19, 19
	bne @1
	lfs f1, 0x10c(r31)
	lfs f0, float_210_8041b150(r2)
	fcmpo cr0, f1, f0
	ble @22
	ori r0, r3, 0x1000
	stw r0, 0x8(r31)
	b @1
	@22:
	lfs f0, float_180_8041b0fc(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @1
	stfs f0, 0x10c(r31)
	lwz r0, 0x8(r31)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x8(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void partySetCamId(PartyEntry* party, s32 cameraId) {
	nofralloc
	stw r4, 0x164(r3)
	blr
}

asm void partyInitCamId(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	bl marioGetCamId
	stw r3, 0x164(r31)
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void party_damage_return(PartyEntry* party) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stw r31, 0x6c(r1)
	stw r30, 0x68(r1)
	mr r30, r3
	stw r29, 0x64(r1)
	lwz r3, 0x8(r3)
	lwz r31, 0x160(r30)
	rlwinm. r0, r3, 0, 28, 28
	beq @1
	rlwinm r0, r3, 0, 29, 27
	stw r0, 0x8(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x0(r30)
	lwz r0, 0x8(r30)
	rlwinm. r0, r0, 0, 7, 7
	bne @2
	li r0, 0xa
	stb r0, 0x38(r30)
	b @1
	@2:
	li r3, 0x0
	li r0, 0x64
	stb r3, 0x38(r30)
	stw r0, 0x24(r30)
	@1:
	lbz r0, 0x38(r30)
	cmplwi r0, 0x17
	bgt @3
	lis r3, jumptable_803126C0@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_803126C0@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@4:
	lwz r3, 0x24(r30)
	subic. r0, r3, 0x1
	stw r0, 0x24(r30)
	bgt @3
	li r0, 0xa
	stb r0, 0x38(r30)
	@5:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne @6
	lbz r0, 0x31(r30)
	extsb r3, r0
	cmpwi r3, 0x8
	bge @7
	bl partyGetHp
	@7:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @8
	lbz r4, 0x31(r30)
	lis r3, partyPoseTbl@ha
	addi r0, r3, partyPoseTbl@l
	extsb r3, r4
	mulli r3, r3, 0x3c
	add r3, r0, r3
	lwz r29, 0x20(r3)
	b @9
	@8:
	lbz r0, 0x31(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @10
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	addi r0, r3, partyDotPoseTbl@l
	add r3, r0, r4
	lwz r29, 0x20(r3)
	b @9
	@10:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	addi r0, r3, yoshiDotPoseTbl@l
	add r3, r0, r4
	lwz r29, 0x20(r3)
	@9:
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @11
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @6
	@11:
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@6:
	li r3, 0xc8
	bl sysMsec2Frame
	stw r3, 0x24(r30)
	li r0, 0xb
	stb r0, 0x38(r30)
	@12:
	lwz r3, 0x24(r30)
	subic. r0, r3, 0x1
	stw r0, 0x24(r30)
	bgt @3
	lfs f1, float_15_8041b154(r2)
	li r0, 0xc
	lfs f0, float_0_8041b100(r2)
	stfs f1, 0x114(r30)
	stfs f0, 0x118(r30)
	stb r0, 0x38(r30)
	@13:
	lfs f1, 0x5c(r30)
	addi r3, r1, 0x44
	lfs f0, 0x114(r30)
	addi r4, r1, 0x1c
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	fadds f0, f1, f0
	stfs f0, 0x5c(r30)
	lwz r7, 0x58(r30)
	lwz r0, 0x5c(r30)
	stw r7, 0x44(r1)
	stw r0, 0x48(r1)
	lwz r0, 0x60(r30)
	stw r0, 0x4c(r1)
	bl marioGetScreenPos
	lwz r7, 0x8c(r31)
	addi r3, r1, 0x38
	lwz r0, 0x90(r31)
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	stw r7, 0x38(r1)
	stw r0, 0x3c(r1)
	lwz r0, 0x94(r31)
	stw r0, 0x40(r1)
	bl marioGetScreenPos
	lfs f1, 0xc(r1)
	lfs f0, float_neg100_8041b158(r2)
	fcmpo cr0, f1, f0
	bge @14
	b @15
	@14:
	fmr f1, f0
	@15:
	lfs f0, 0x18(r1)
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	bne @3
	li r3, 0x20
	li r0, 0x14
	stw r3, 0x24(r30)
	stb r0, 0x38(r30)
	b @3
	@16:
	lwz r7, 0x58(r30)
	addi r3, r1, 0x2c
	lwz r0, 0x5c(r30)
	addi r4, r1, 0x1c
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	stw r7, 0x2c(r1)
	stw r0, 0x30(r1)
	lwz r0, 0x60(r30)
	stw r0, 0x34(r1)
	bl marioGetScreenPos
	lfs f1, 0x18(r1)
	lfs f0, float_neg100_8041b158(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @17
	lfs f1, 0x5c(r30)
	lfs f0, float_1_8041b0e8(r2)
	fadds f0, f1, f0
	stfs f0, 0x5c(r30)
	@17:
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x1f
	bne @18
	bl marioWaitDamageReturnFall
	cmpwi r3, 0x0
	beq @3
	b @19
	@18:
	cmplwi r0, 0x20
	bne @19
	bl marioWaitDamageTogeReturnFall
	cmpwi r3, 0x0
	beq @3
	@19:
	li r0, 0x15
	stb r0, 0x38(r30)
	@20:
	lwz r3, 0x24(r30)
	subic. r0, r3, 0x1
	stw r0, 0x24(r30)
	bgt @3
	mr r3, r30
	addi r4, r1, 0x50
	bl partyGetAppearPos
	lfs f0, 0x50(r1)
	li r0, 0x16
	lfs f1, float_0_8041b100(r2)
	stfs f0, 0x58(r30)
	lfs f0, float_neg1_8041b0ec(r2)
	lfs f2, 0x58(r1)
	stfs f2, 0x60(r30)
	stfs f1, 0x114(r30)
	stfs f0, 0x118(r30)
	stfs f1, 0x104(r30)
	lwz r3, 0x0(r30)
	ori r3, r3, 0x20
	stw r3, 0x0(r30)
	lwz r3, 0x0(r30)
	oris r3, r3, 0x200
	stw r3, 0x0(r30)
	stb r0, 0x38(r30)
	b @3
	@21:
	lwz r7, 0x58(r30)
	addi r3, r1, 0x20
	lwz r0, 0x5c(r30)
	addi r4, r1, 0x1c
	addi r5, r1, 0x18
	addi r6, r1, 0x14
	stw r7, 0x20(r1)
	stw r0, 0x24(r1)
	lwz r0, 0x60(r30)
	stw r0, 0x28(r1)
	bl marioGetScreenPos
	lfs f1, 0x18(r1)
	lfs f0, float_240_8041b15c(r2)
	fcmpo cr0, f1, f0
	ble @22
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 7, 5
	stw r0, 0x0(r30)
	@22:
	mr r3, r30
	bl partyMove
	lfs f0, 0x114(r30)
	lfs f1, float_neg6_8041b160(r2)
	fcmpo cr0, f0, f1
	cror eq, lt, eq
	bne @23
	lfs f0, float_0_8041b100(r2)
	stfs f0, 0x118(r30)
	stfs f1, 0x114(r30)
	@23:
	lfs f1, 0x5c(r30)
	lfs f0, float_neg2000_8041b164(r2)
	fcmpo cr0, f1, f0
	bge @24
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	lfs f0, float_200_8041b168(r2)
	stw r3, 0x58(r30)
	stw r0, 0x5c(r30)
	lwz r0, 0x94(r31)
	stw r0, 0x60(r30)
	lfs f1, 0x5c(r30)
	fadds f0, f1, f0
	stfs f0, 0x5c(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 28, 24
	stw r0, 0x0(r30)
	@24:
	lwz r3, 0x138(r30)
	cmplwi r3, 0x0
	beq @3
	bl hitGetAttr
	extrwi. r0, r3, 1, 22
	bne @3
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne @25
	lbz r0, 0x31(r30)
	extsb r3, r0
	cmpwi r3, 0x8
	bge @26
	bl partyGetHp
	@26:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @27
	lbz r4, 0x31(r30)
	lis r3, partyPoseTbl@ha
	addi r0, r3, partyPoseTbl@l
	extsb r3, r4
	mulli r3, r3, 0x3c
	add r3, r0, r3
	lwz r29, 0x24(r3)
	b @28
	@27:
	lbz r0, 0x31(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @29
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	addi r0, r3, partyDotPoseTbl@l
	add r3, r0, r4
	lwz r29, 0x24(r3)
	b @28
	@29:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	addi r0, r3, yoshiDotPoseTbl@l
	add r3, r0, r4
	lwz r29, 0x24(r3)
	@28:
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @30
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @25
	@30:
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@25:
	li r3, 0x17
	li r0, 0x1e
	stb r3, 0x38(r30)
	stw r0, 0x24(r30)
	b @3
	@31:
	lwz r3, 0x24(r30)
	subic. r0, r3, 0x1
	stw r0, 0x24(r30)
	bgt @3
	mr r3, r30
	li r4, 0x2
	bl partyChgRunMode
	li r0, 0x0
	stb r0, 0x3b(r30)
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r30)
	@3:
	bl vivianGetStatus
	cmpwi r3, 0x2
	beq @32
	mr r3, r30
	bl vivianShadow
	@32:
	lwz r0, 0x74(r1)
	lwz r31, 0x6c(r1)
	lwz r30, 0x68(r1)
	lwz r29, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm s32 partyRideYoshiMain(PartyEntry* party) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stw r31, 0x4c(r1)
	mr r31, r3
	stw r30, 0x48(r1)
	stw r29, 0x44(r1)
	lbz r0, 0x38(r3)
	lwz r29, 0x160(r3)
	cmpwi r0, 0x2
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r0, 0xa
	beq @6
	b @5
	@3:
	lfs f0, float_1p6_8041b16c(r2)
	addi r4, r1, 0x14
	stfs f0, 0x11c(r31)
	bl getRidePos
	lwz r3, 0x14(r1)
	lwz r0, 0x18(r1)
	stw r3, 0x94(r31)
	stw r0, 0x98(r31)
	lwz r0, 0x1c(r1)
	stw r0, 0x9c(r31)
	lfs f1, 0x58(r31)
	lfs f2, 0x60(r31)
	lfs f3, 0x94(r31)
	lfs f4, 0x9c(r31)
	bl distABf
	stfs f1, 0x128(r31)
	lfs f1, 0x58(r31)
	lfs f2, 0x60(r31)
	lfs f3, 0x94(r31)
	lfs f4, 0x9c(r31)
	bl angleABf
	stfs f1, 0x100(r31)
	lis r0, 0x4330
	li r4, 0xf
	lis r3, double_to_int_802ccf00@ha
	stw r4, 0x24(r31)
	lfd f6, double_to_int_802ccf00@l(r3)
	lwz r3, 0x24(r31)
	stw r0, 0x20(r1)
	xoris r3, r3, 0x8000
	lfs f1, 0x128(r31)
	stw r3, 0x24(r1)
	lfs f5, float_0p5_8041b170(r2)
	lfd f0, 0x20(r1)
	stw r0, 0x30(r1)
	fsubs f0, f0, f6
	stw r0, 0x28(r1)
	fdivs f0, f1, f0
	stw r0, 0x38(r1)
	stfs f0, 0x104(r31)
	lwz r0, 0x24(r31)
	lfs f1, 0x98(r31)
	xoris r0, r0, 0x8000
	lfs f0, 0x5c(r31)
	stw r0, 0x34(r1)
	fsubs f1, f1, f0
	lfs f3, 0x11c(r31)
	lfd f2, 0x30(r1)
	stw r0, 0x2c(r1)
	fsubs f0, f2, f6
	lfd f2, 0x28(r1)
	stw r0, 0x3c(r1)
	fsubs f4, f2, f6
	fmuls f2, f3, f0
	lfd f0, 0x38(r1)
	fsubs f0, f0, f6
	fmuls f2, f4, f2
	fmadds f1, f5, f2, f1
	fdivs f0, f1, f0
	stfs f0, 0x114(r31)
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 30, 30
	bne @7
	lbz r0, 0x31(r31)
	extsb r3, r0
	cmpwi r3, 0x8
	bge @8
	bl partyGetHp
	@8:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @9
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r0, r3, partyPoseTbl@l
	extsb r3, r4
	mulli r3, r3, 0x3c
	add r3, r0, r3
	lwz r30, 0x10(r3)
	b @10
	@9:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @11
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	addi r0, r3, partyDotPoseTbl@l
	add r3, r0, r4
	lwz r30, 0x10(r3)
	b @10
	@11:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	addi r0, r3, yoshiDotPoseTbl@l
	add r3, r0, r4
	lwz r30, 0x10(r3)
	@10:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @12
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @7
	@12:
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@7:
	li r0, 0x1
	stb r0, 0x38(r31)
	b @5
	@4:
	addi r4, r1, 0x14
	bl getRidePos
	lwz r3, 0x14(r1)
	lwz r0, 0x18(r1)
	stw r3, 0x94(r31)
	stw r0, 0x98(r31)
	lwz r0, 0x1c(r1)
	stw r0, 0x9c(r31)
	lfs f1, 0x58(r31)
	lfs f2, 0x60(r31)
	lfs f3, 0x94(r31)
	lfs f4, 0x9c(r31)
	bl distABf
	stfs f1, 0x128(r31)
	lfs f1, 0x58(r31)
	lfs f2, 0x60(r31)
	lfs f3, 0x94(r31)
	lfs f4, 0x9c(r31)
	bl angleABf
	stfs f1, 0x100(r31)
	lis r0, 0x4330
	lis r4, double_to_int_802ccf00@ha
	addi r3, r31, 0x58
	lwz r6, 0x24(r31)
	addi r5, r4, double_to_int_802ccf00@l
	stw r0, 0x38(r1)
	addi r4, r31, 0x60
	xoris r0, r6, 0x8000
	lfd f1, 0x0(r5)
	stw r0, 0x3c(r1)
	lfs f2, 0x128(r31)
	lfd f0, 0x38(r1)
	fsubs f0, f0, f1
	fdivs f0, f2, f0
	stfs f0, 0x104(r31)
	lfs f1, 0x114(r31)
	lfs f0, 0x11c(r31)
	fsubs f0, f1, f0
	stfs f0, 0x114(r31)
	lfs f1, 0x5c(r31)
	lfs f0, 0x114(r31)
	fadds f0, f1, f0
	stfs f0, 0x5c(r31)
	lfs f1, 0x104(r31)
	lfs f2, 0x100(r31)
	bl movePos
	lwz r3, 0x24(r31)
	subic. r0, r3, 0x1
	stw r0, 0x24(r31)
	bgt @5
	li r0, 0x2
	stb r0, 0x38(r31)
	b @5
	@1:
	lwz r0, 0x4(r31)
	li r30, 0x1
	rlwinm. r0, r0, 0, 30, 30
	bne @13
	lbz r0, 0x31(r31)
	li r29, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @14
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @14
	li r29, 0x1
	@14:
	cmpwi r29, 0x1
	bne @15
	li r30, 0xc
	@15:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @16
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @17
	@16:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @18
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @17
	@18:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@17:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @19
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @13
	@19:
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@13:
	lfs f0, float_0_8041b100(r2)
	cmplwi r31, 0x0
	li r0, 0xa
	stfs f0, 0x114(r31)
	lfs f0, 0x98(r31)
	stfs f0, 0x5c(r31)
	stb r0, 0x38(r31)
	beq @5
	lwz r0, 0x4(r31)
	oris r0, r0, 0x10
	stw r0, 0x4(r31)
	b @5
	@6:
	addi r4, r1, 0x14
	bl getRidePos
	lwz r3, 0x14(r1)
	lwz r0, 0x18(r1)
	stw r3, 0x58(r31)
	stw r0, 0x5c(r31)
	lwz r0, 0x1c(r1)
	stw r0, 0x60(r31)
	lfs f0, 0x1ac(r29)
	stfs f0, 0x110(r31)
	lfs f1, 0x110(r31)
	bl toMovedir
	stfs f1, 0xfc(r31)
	lhz r0, 0x2e(r29)
	cmplwi r0, 0x1a
	beq @5
	mr r3, r31
	addi r4, r1, 0x8
	bl partyGetAppearPos
	lfs f0, 0x8(r1)
	mr r3, r31
	li r4, 0x2
	stfs f0, 0x58(r31)
	lfs f0, 0x10(r1)
	stfs f0, 0x60(r31)
	bl partyChgRunMode
	cmplwi r31, 0x0
	beq @20
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x4(r31)
	@20:
	lis r3, vec3_802cced4@ha
	addi r4, r3, vec3_802cced4@l
	lwz r3, 0x0(r4)
	lwz r0, 0x4(r4)
	stw r3, 0x7c(r31)
	stw r0, 0x80(r31)
	lwz r0, 0x8(r4)
	stw r0, 0x84(r31)
	@5:
	lwz r0, 0x54(r1)
	li r3, 0x0
	lwz r31, 0x4c(r1)
	lwz r30, 0x48(r1)
	lwz r29, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void party_ride_yoshi_force_move(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	bl marioGetExtraPartyId
	cmpwi r3, 0x0
	blt @1
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r31, r3, r0
	b @2
	@1:
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	beq @3
	mr r3, r31
	addi r4, r1, 0x8
	bl getRidePos
	lwz r3, 0x8(r1)
	lwz r0, 0xc(r1)
	stw r3, 0x58(r31)
	stw r0, 0x5c(r31)
	lwz r0, 0x10(r1)
	stw r0, 0x60(r31)
	lwz r3, 0x160(r31)
	lfs f0, 0x1ac(r3)
	stfs f0, 0x110(r31)
	lfs f1, 0x110(r31)
	bl toMovedir
	stfs f1, 0xfc(r31)
	@3:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void party_force_ride_yoshi(PartyEntry* party) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	li r4, 0xc
	li r5, 0xa
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	mr r30, r3
	stw r29, 0x24(r1)
	bl N_partyForceChgRunMode
	lwz r0, 0x0(r30)
	mr r3, r30
	addi r4, r1, 0x8
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x0(r30)
	bl getRidePos
	lwz r3, 0x8(r1)
	li r31, 0x1
	lwz r0, 0xc(r1)
	stw r3, 0x58(r30)
	stw r0, 0x5c(r30)
	lwz r0, 0x10(r1)
	stw r0, 0x60(r30)
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne @1
	lbz r0, 0x31(r30)
	li r29, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @2
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @2
	li r29, 0x1
	@2:
	cmpwi r29, 0x1
	bne @3
	li r31, 0xc
	@3:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @4
	lbz r4, 0x31(r30)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r31, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r31, r3, r0
	b @5
	@4:
	lbz r0, 0x31(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @6
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r31, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r31, r3, r0
	b @5
	@6:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r31, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r31, r3, r0
	@5:
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @7
	mr r4, r31
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	@7:
	stw r31, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@1:
	lfs f0, float_0_8041b100(r2)
	cmplwi r30, 0x0
	stfs f0, 0x114(r30)
	beq @8
	lwz r0, 0x4(r30)
	oris r0, r0, 0x10
	stw r0, 0x4(r30)
	@8:
	lwz r3, 0x160(r30)
	lfs f0, 0x1ac(r3)
	stfs f0, 0x110(r30)
	lfs f1, 0x110(r30)
	bl toMovedir
	stfs f1, 0xfc(r30)
	lwz r0, 0x34(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void partyRideMain(PartyEntry *party) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stfd f30, 0x60(r1)
	psq_st f30, 0x68(r1), 0, 0
	stw r31, 0x5c(r1)
	stw r30, 0x58(r1)
	stw r29, 0x54(r1)
	stw r28, 0x50(r1)
	mr r29, r3
	lis r4, vec3_802ccd30@ha
	lbz r0, 0x38(r3)
	addi r31, r4, vec3_802ccd30@l
	lwz r30, 0x160(r3)
	cmpwi r0, 0x15
	beq @1
	bge @2
	cmpwi r0, 0xa
	beq @3
	bge @4
	cmpwi r0, 0x1
	beq @5
	bge @6
	cmpwi r0, 0x0
	bge @7
	b @8
	@6:
	cmpwi r0, 0x3
	bge @8
	b @9
	@4:
	cmpwi r0, 0x14
	bge @10
	cmpwi r0, 0xc
	bge @8
	b @11
	@2:
	cmpwi r0, 0x6e
	beq @12
	bge @13
	cmpwi r0, 0x64
	bge @14
	b @8
	@14:
	cmpwi r0, 0x66
	bge @8
	b @15
	@13:
	cmpwi r0, 0xc8
	beq @16
	bge @8
	cmpwi r0, 0x70
	bge @8
	b @17
	@7:
	addi r4, r1, 0x20
	bl getRidePos
	lwz r3, 0x20(r1)
	lwz r0, 0x24(r1)
	stw r3, 0x94(r29)
	stw r0, 0x98(r29)
	lwz r0, 0x28(r1)
	stw r0, 0x9c(r29)
	lfs f1, 0x58(r29)
	lfs f2, 0x60(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl distABf
	stfs f1, 0x128(r29)
	lfs f1, 0x58(r29)
	lfs f2, 0x60(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl angleABf
	stfs f1, 0x100(r29)
	lis r0, 0x4330
	li r3, 0x1e
	lfd f5, 0x1d0(r31)
	stw r3, 0x24(r29)
	lfs f1, float_0p4_8041b174(r2)
	lwz r3, 0x24(r29)
	stw r0, 0x30(r1)
	xoris r3, r3, 0x8000
	lfs f3, 0x128(r29)
	stw r3, 0x34(r1)
	lfs f4, float_0p5_8041b170(r2)
	lfd f0, 0x30(r1)
	stw r0, 0x40(r1)
	fsubs f2, f0, f5
	lfs f0, float_1_8041b0e8(r2)
	stw r0, 0x38(r1)
	fdivs f2, f3, f2
	stw r0, 0x48(r1)
	stfs f2, 0x104(r29)
	lfs f3, 0x98(r29)
	lfs f2, 0x5c(r29)
	stfs f1, 0x11c(r29)
	fsubs f6, f3, f2
	lwz r0, 0x24(r29)
	lfs f2, 0x11c(r29)
	xoris r0, r0, 0x8000
	stw r0, 0x44(r1)
	lfd f1, 0x40(r1)
	stw r0, 0x3c(r1)
	fsubs f1, f1, f5
	lfd f3, 0x38(r1)
	stw r0, 0x4c(r1)
	fmuls f2, f2, f1
	fsubs f3, f3, f5
	lfd f1, 0x48(r1)
	fsubs f1, f1, f5
	fmuls f2, f3, f2
	fmadds f2, f4, f2, f6
	fdivs f1, f2, f1
	stfs f1, 0x114(r29)
	stfs f0, 0x124(r29)
	lwz r0, 0x4(r29)
	ori r0, r0, 0x10
	stw r0, 0x4(r29)
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 30, 30
	bne @18
	lbz r0, 0x31(r29)
	extsb r3, r0
	cmpwi r3, 0x8
	bge @19
	bl partyGetHp
	@19:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @20
	lbz r4, 0x31(r29)
	lis r3, partyPoseTbl@ha
	addi r0, r3, partyPoseTbl@l
	extsb r3, r4
	mulli r3, r3, 0x3c
	add r3, r0, r3
	lwz r30, 0x10(r3)
	b @21
	@20:
	lbz r0, 0x31(r29)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @22
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	addi r0, r3, partyDotPoseTbl@l
	add r3, r0, r4
	lwz r30, 0x10(r3)
	b @21
	@22:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	addi r0, r3, yoshiDotPoseTbl@l
	add r3, r0, r4
	lwz r30, 0x10(r3)
	@21:
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @23
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @18
	@23:
	stw r30, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@18:
	li r0, 0x1
	stb r0, 0x38(r29)
	b @8
	@5:
	lfs f1, 0x114(r29)
	addi r3, r29, 0x58
	lfs f0, 0x11c(r29)
	addi r4, r29, 0x60
	fsubs f0, f1, f0
	stfs f0, 0x114(r29)
	lfs f1, 0x5c(r29)
	lfs f0, 0x114(r29)
	fadds f0, f1, f0
	stfs f0, 0x5c(r29)
	lfs f1, 0x104(r29)
	lfs f2, 0x100(r29)
	bl movePos
	lfs f1, 0x10c(r29)
	lfs f0, 0x124(r29)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x10c(r29)
	lfs f1, float_2_8041b0e4(r2)
	lfs f2, 0x124(r29)
	lfs f0, float_30_8041b178(r2)
	fadds f1, f2, f1
	stfs f1, 0x124(r29)
	lfs f1, 0x124(r29)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @24
	stfs f0, 0x124(r29)
	@24:
	lwz r3, 0x24(r29)
	lis r0, 0x4330
	stw r0, 0x48(r1)
	xoris r0, r3, 0x8000
	lfd f2, 0x1d0(r31)
	stw r0, 0x4c(r1)
	lfs f0, float_10_8041b124(r2)
	lfd f1, 0x48(r1)
	fsubs f1, f1, f2
	fcmpo cr0, f1, f0
	ble @25
	fmr f1, f0
	@25:
	lfs f0, float_10_8041b124(r2)
	fdivs f0, f1, f0
	stfs f0, 0x70(r29)
	lfs f0, 0x70(r29)
	stfs f0, 0x74(r29)
	lfs f0, 0x70(r29)
	stfs f0, 0x78(r29)
	lwz r3, 0x24(r29)
	subic. r0, r3, 0x1
	stw r0, 0x24(r29)
	bge @8
	li r0, 0x2
	stb r0, 0x38(r29)
	b @8
	@9:
	lwz r0, 0x4(r29)
	li r30, 0x1
	rlwinm. r0, r0, 0, 30, 30
	bne @26
	lbz r0, 0x31(r29)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @27
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @27
	li r28, 0x1
	@27:
	cmpwi r28, 0x1
	bne @28
	li r30, 0xc
	@28:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @29
	lbz r4, 0x31(r29)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @30
	@29:
	lbz r0, 0x31(r29)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @31
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @30
	@31:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@30:
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @32
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @26
	@32:
	stw r30, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@26:
	lfs f0, float_0_8041b100(r2)
	cmplwi r29, 0x0
	stfs f0, 0x114(r29)
	lfs f0, 0x98(r29)
	stfs f0, 0x5c(r29)
	lwz r3, 0x15c(r31)
	lwz r0, 0x160(r31)
	stw r3, 0x70(r29)
	stw r0, 0x74(r29)
	lwz r0, 0x164(r31)
	stw r0, 0x78(r29)
	lwz r0, 0x4(r29)
	ori r0, r0, 0x1
	stw r0, 0x4(r29)
	beq @33
	lwz r0, 0x4(r29)
	oris r0, r0, 0x10
	stw r0, 0x4(r29)
	@33:
	li r0, 0xa
	stb r0, 0x38(r29)
	b @8
	@3:
	lwz r3, 0x8c(r30)
	lwz r0, 0x90(r30)
	stw r3, 0x58(r29)
	stw r0, 0x5c(r29)
	lwz r0, 0x94(r30)
	stw r0, 0x60(r29)
	lfs f0, 0x1ac(r30)
	stfs f0, 0x110(r29)
	lfs f1, 0x110(r29)
	bl toMovedir
	stfs f1, 0xfc(r29)
	b @8
	@11:
	lwz r0, 0x4(r29)
	li r30, 0x1
	rlwinm. r0, r0, 0, 30, 30
	bne @34
	lbz r0, 0x31(r29)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @35
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @35
	li r28, 0x1
	@35:
	cmpwi r28, 0x1
	bne @36
	li r30, 0xc
	@36:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @37
	lbz r4, 0x31(r29)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @38
	@37:
	lbz r0, 0x31(r29)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @39
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @38
	@39:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@38:
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @40
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @34
	@40:
	stw r30, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@34:
	lwz r0, 0x4(r29)
	cmplwi r29, 0x0
	ori r0, r0, 0x1
	stw r0, 0x4(r29)
	beq @41
	lwz r0, 0x4(r29)
	oris r0, r0, 0x10
	stw r0, 0x4(r29)
	@41:
	mr r3, r29
	addi r4, r1, 0x20
	bl getRidePos
	lwz r3, 0x168(r31)
	lwz r0, 0x16c(r31)
	lfs f0, float_0_8041b100(r2)
	stw r3, 0x70(r29)
	stw r0, 0x74(r29)
	lwz r0, 0x170(r31)
	stw r0, 0x78(r29)
	lwz r3, 0x20(r1)
	lwz r0, 0x24(r1)
	stw r3, 0x58(r29)
	stw r0, 0x5c(r29)
	lwz r0, 0x28(r1)
	stw r0, 0x60(r29)
	stfs f0, 0x114(r29)
	lwz r3, 0x160(r29)
	lfs f0, 0x1ac(r3)
	stfs f0, 0x110(r29)
	lfs f1, 0x110(r29)
	bl toMovedir
	stfs f1, 0xfc(r29)
	b @8
	@10:
	li r3, 0x15
	li r0, 0x10
	stb r3, 0x38(r29)
	lfs f1, float_16_8041b17c(r2)
	stw r0, 0x24(r29)
	lfs f0, float_0p5_8041b170(r2)
	stfs f1, 0x114(r29)
	stfs f0, 0x174(r29)
	@1:
	lfs f1, 0x5c(r29)
	lfs f0, 0x114(r29)
	fadds f0, f1, f0
	stfs f0, 0x5c(r29)
	lfs f1, 0x114(r29)
	lfs f0, 0x174(r29)
	fadds f0, f1, f0
	stfs f0, 0x114(r29)
	lwz r3, 0x24(r29)
	subic. r0, r3, 0x1
	stw r0, 0x24(r29)
	bgt @8
	li r0, 0x16
	stb r0, 0x38(r29)
	lwz r0, 0x0(r29)
	oris r0, r0, 0x200
	stw r0, 0x0(r29)
	b @8
	@16:
	lwz r0, 0x0(r29)
	cmplwi r29, 0x0
	lfs f1, float_0_8041b100(r2)
	rlwinm r0, r0, 0, 16, 12
	lfs f0, float_1_8041b0e8(r2)
	stw r0, 0x0(r29)
	stfs f1, 0x80(r29)
	stfs f0, 0x70(r29)
	lfs f0, 0x70(r29)
	stfs f0, 0x74(r29)
	lfs f0, 0x70(r29)
	stfs f0, 0x78(r29)
	beq @42
	lwz r0, 0x4(r29)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x4(r29)
	@42:
	mr r3, r29
	li r4, 0x1
	bl partyChgRunMode
	b @8
	@15:
	lwz r0, 0x4(r29)
	lfs f1, float_0p5_8041b170(r2)
	clrrwi r0, r0, 1
	stw r0, 0x4(r29)
	lfs f31, 0x8c(r30)
	lfs f2, 0x90(r30)
	lfs f30, 0x94(r30)
	stfs f31, 0x58(r29)
	lfs f0, 0x1b8(r30)
	fmadds f0, f1, f0, f2
	stfs f0, 0x5c(r29)
	stfs f30, 0x60(r29)
	lbz r0, 0x38(r29)
	cmplwi r0, 0x64
	bne @43
	addi r4, r29, 0x94
	bl partyGetAppearPos
	b @44
	@43:
	addi r4, r29, 0x94
	bl partyGetAppearPos2
	@44:
	lfs f0, 0x1ac(r30)
	li r0, 0x10
	fmr f1, f31
	stfs f0, 0x110(r29)
	fmr f2, f30
	stw r0, 0x24(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl distABf
	stfs f1, 0x128(r29)
	fmr f1, f31
	fmr f2, f30
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl angleABf
	stfs f1, 0x100(r29)
	lis r0, 0x4330
	lfd f4, 0x1d0(r31)
	lwz r3, 0x24(r29)
	stw r0, 0x48(r1)
	xoris r3, r3, 0x8000
	lfs f2, 0x128(r29)
	stw r3, 0x4c(r1)
	lfs f3, float_0p5_8041b170(r2)
	lfd f0, 0x48(r1)
	stw r0, 0x40(r1)
	fsubs f1, f0, f4
	lfs f0, float_1_8041b0e8(r2)
	fdivs f1, f2, f1
	stfs f1, 0x104(r29)
	lwz r0, 0x24(r29)
	lfs f2, 0x98(r29)
	xoris r0, r0, 0x8000
	lfs f1, 0x5c(r29)
	stw r0, 0x44(r1)
	fsubs f5, f2, f1
	lfd f1, 0x40(r1)
	fsubs f2, f1, f4
	fabs f1, f5
	fmuls f2, f3, f2
	fcmpo cr0, f1, f0
	bge @45
	lfs f5, float_10_8041b124(r2)
	b @46
	@45:
	lfs f0, float_0_8041b100(r2)
	fcmpo cr0, f5, f0
	cror eq, gt, eq
	bne @47
	lfs f0, 0xf0(r29)
	fmadds f5, f3, f0, f5
	b @46
	@47:
	lfs f5, float_10_8041b124(r2)
	@46:
	fadds f1, f5, f5
	cmplwi r29, 0x0
	fmsubs f0, f2, f2, f2
	fdivs f0, f1, f0
	fmuls f1, f0, f2
	fneg f0, f0
	stfs f1, 0x114(r29)
	stfs f0, 0x118(r29)
	lwz r0, 0x0(r29)
	ori r0, r0, 0x10
	stw r0, 0x0(r29)
	lwz r0, 0x4(r29)
	clrrwi r0, r0, 1
	stw r0, 0x4(r29)
	beq @48
	lwz r0, 0x4(r29)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x4(r29)
	@48:
	li r0, 0x6e
	stb r0, 0x38(r29)
	b @8
	@12:
	bl partyMoveNoHosei
	lfs f1, 0x114(r29)
	lfs f0, float_0_8041b100(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @49
	lwz r0, 0x0(r29)
	lfs f0, float_neg1p6_8041b180(r2)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x0(r29)
	stfs f0, 0x118(r29)
	@49:
	lfs f1, 0x5c(r29)
	lfs f0, float_neg2000_8041b164(r2)
	fcmpo cr0, f1, f0
	bge @50
	li r3, 0x0
	li r0, 0x6f
	stw r3, 0x24(r29)
	stb r0, 0x38(r29)
	b @8
	@50:
	lwz r0, 0x138(r29)
	cmplwi r0, 0x0
	bne @51
	lwz r0, 0x24(r29)
	lis r5, 0x4330
	lwz r4, 0x174(r31)
	subfic r0, r0, 0x10
	lwz r3, 0x178(r31)
	xoris r6, r0, 0x8000
	lwz r0, 0x17c(r31)
	stw r6, 0x4c(r1)
	lfd f2, 0x1d0(r31)
	stw r5, 0x48(r1)
	lfs f0, float_0p0625_8041b184(r2)
	lfd f1, 0x48(r1)
	stw r4, 0x14(r1)
	fsubs f1, f1, f2
	stw r3, 0x18(r1)
	fmuls f0, f1, f0
	stw r0, 0x1c(r1)
	stfs f0, 0x14(r1)
	stfs f0, 0x18(r1)
	lwz r0, 0x14(r1)
	stfs f0, 0x1c(r1)
	lwz r3, 0x18(r1)
	stw r0, 0x70(r29)
	lwz r0, 0x1c(r1)
	stw r3, 0x74(r29)
	stw r0, 0x78(r29)
	lwz r3, 0x24(r29)
	subic. r0, r3, 0x1
	stw r0, 0x24(r29)
	bgt @8
	li r0, 0x0
	stw r0, 0x24(r29)
	b @8
	@51:
	li r0, 0x6f
	stb r0, 0x38(r29)
	@17:
	lwz r0, 0x24(r29)
	lis r5, 0x4330
	lwz r4, 0x180(r31)
	subfic r0, r0, 0x10
	lwz r3, 0x184(r31)
	xoris r6, r0, 0x8000
	lwz r0, 0x188(r31)
	stw r6, 0x4c(r1)
	lfd f2, 0x1d0(r31)
	stw r5, 0x48(r1)
	lfs f0, float_0p0625_8041b184(r2)
	lfd f1, 0x48(r1)
	stw r4, 0x8(r1)
	fsubs f1, f1, f2
	stw r3, 0xc(r1)
	fmuls f0, f1, f0
	stw r0, 0x10(r1)
	stfs f0, 0x8(r1)
	stfs f0, 0xc(r1)
	lwz r0, 0x8(r1)
	stfs f0, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0x70(r29)
	lwz r0, 0x10(r1)
	stw r3, 0x74(r29)
	stw r0, 0x78(r29)
	lwz r3, 0x24(r29)
	subic. r0, r3, 0x1
	stw r0, 0x24(r29)
	bgt @8
	li r0, 0x0
	stw r0, 0x24(r29)
	lfs f0, 0x1ac(r30)
	stfs f0, 0x110(r29)
	lfs f0, 0x1ac(r30)
	stfs f0, 0x10c(r29)
	lfs f1, 0x10c(r29)
	bl toMovedirSimple
	stfs f1, 0xfc(r29)
	mr r3, r29
	lfs f0, 0xfc(r29)
	stfs f0, 0x100(r29)
	bl partyClearJumpPara
	lwz r0, 0x4(r29)
	li r30, 0x1
	rlwinm. r0, r0, 0, 30, 30
	bne @52
	lbz r0, 0x31(r29)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @53
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @53
	li r28, 0x1
	@53:
	cmpwi r28, 0x1
	bne @54
	li r30, 0xc
	@54:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @55
	lbz r4, 0x31(r29)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @56
	@55:
	lbz r0, 0x31(r29)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @57
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @56
	@57:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@56:
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @58
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @52
	@58:
	stw r30, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@52:
	lwz r0, 0x4(r29)
	cmplwi r29, 0x0
	lfs f1, float_0_8041b100(r2)
	rlwinm r0, r0, 0, 28, 26
	lfs f0, float_1_8041b0e8(r2)
	stw r0, 0x4(r29)
	lwz r0, 0x0(r29)
	rlwinm r0, r0, 0, 16, 12
	stw r0, 0x0(r29)
	stfs f1, 0x80(r29)
	stfs f0, 0x70(r29)
	lfs f0, 0x70(r29)
	stfs f0, 0x74(r29)
	lfs f0, 0x70(r29)
	stfs f0, 0x78(r29)
	lwz r0, 0x4(r29)
	clrrwi r0, r0, 1
	stw r0, 0x4(r29)
	beq @59
	lwz r0, 0x4(r29)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x4(r29)
	@59:
	mr r3, r29
	li r4, 0x1
	bl partyChgRunMode
	@8:
	lwz r3, 0x58(r29)
	lwz r0, 0x5c(r29)
	stw r3, 0xb8(r29)
	stw r0, 0xbc(r29)
	lwz r0, 0x60(r29)
	stw r0, 0xc0(r29)
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	lwz r31, 0x5c(r1)
	lwz r30, 0x58(r1)
	lwz r29, 0x54(r1)
	lwz r0, 0x84(r1)
	lwz r28, 0x50(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm s32 partyRideChk(PartyEntry* party) {
	nofralloc
	cmplwi r3, 0x0
	li r4, 0x0
	bne @1
	li r3, 0x0
	blr
	@1:
	lbz r0, 0x34(r3)
	cmplwi r0, 0xb
	bne @2
	lbz r0, 0x38(r3)
	li r4, 0x1
	cmplwi r0, 0x2
	blt @2
	li r4, 0x2
	@2:
	mr r3, r4
	blr
}

asm void allPartyRideOff2(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPartyId
	cmpwi r3, 0x0
	blt @1
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @2
	@1:
	li r3, 0x0
	@2:
	cmplwi r3, 0x0
	beq @3
	lbz r0, 0x34(r3)
	cmplwi r0, 0xb
	bne @3
	li r0, 0x65
	stb r0, 0x38(r3)
	@3:
	bl marioGetExtraPartyId
	cmpwi r3, 0x0
	blt @4
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @5
	@4:
	li r3, 0x0
	@5:
	cmplwi r3, 0x0
	beq @6
	lbz r0, 0x34(r3)
	cmplwi r0, 0xb
	bne @6
	li r0, 0x65
	stb r0, 0x38(r3)
	@6:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void allPartyRideOff(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPartyId
	cmpwi r3, 0x0
	blt @1
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @2
	@1:
	li r3, 0x0
	@2:
	cmplwi r3, 0x0
	beq @3
	lbz r0, 0x34(r3)
	cmplwi r0, 0xb
	bne @3
	li r0, 0x64
	stb r0, 0x38(r3)
	@3:
	bl marioGetExtraPartyId
	cmpwi r3, 0x0
	blt @4
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @5
	@4:
	li r3, 0x0
	@5:
	cmplwi r3, 0x0
	beq @6
	lbz r0, 0x34(r3)
	cmplwi r0, 0xb
	bne @6
	li r0, 0x64
	stb r0, 0x38(r3)
	@6:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void L_allPartyRideOn(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	bl marioGetPartyId
	cmpwi r3, 0x0
	blt @1
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @2
	@1:
	li r3, 0x0
	@2:
	cmplwi r3, 0x0
	beq @3
	li r4, 0xb
	bl partyChgRunMode
	@3:
	bl marioGetExtraPartyId
	cmpwi r3, 0x0
	blt @4
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @5
	@4:
	li r3, 0x0
	@5:
	cmplwi r3, 0x0
	beq @6
	li r4, 0xb
	bl partyChgRunMode
	@6:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void allPartyForceRideOn(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl marioGetPartyId
	cmpwi r3, 0x0
	blt @1
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r31, r3, r0
	b @2
	@1:
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	beq @3
	mr r3, r31
	li r4, 0xb
	li r5, 0xb
	bl N_partyForceChgRunMode
	lwz r0, 0x4(r31)
	cmplwi r31, 0x0
	ori r0, r0, 0x1
	stw r0, 0x4(r31)
	beq @3
	lwz r0, 0x4(r31)
	oris r0, r0, 0x10
	stw r0, 0x4(r31)
	@3:
	bl marioGetExtraPartyId
	cmpwi r3, 0x0
	blt @4
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r31, r3, r0
	b @5
	@4:
	li r31, 0x0
	@5:
	cmplwi r31, 0x0
	beq @6
	mr r3, r31
	li r4, 0xb
	li r5, 0xb
	bl N_partyForceChgRunMode
	lwz r0, 0x4(r31)
	cmplwi r31, 0x0
	ori r0, r0, 0x1
	stw r0, 0x4(r31)
	beq @6
	lwz r0, 0x4(r31)
	oris r0, r0, 0x10
	stw r0, 0x4(r31)
	@6:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void getRidePos(PartyEntry* party, Vec* pos) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stfd f31, 0x20(r1)
	psq_st f31, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r31, r3
	mr r29, r4
	lwz r30, 0x160(r3)
	lhz r0, 0x2e(r30)
	cmplwi r0, 0x1a
	bne @1
	lfs f1, 0x1ac(r30)
	bl toMovedir
	lfs f2, float_3p1416_8041b188(r2)
	lfs f0, float_180_8041b0fc(r2)
	fmuls f1, f2, f1
	fdivs f31, f1, f0
	bl yoshiGetStatus
	cmpwi r3, 0x2
	beq @2
	fmr f1, f31
	bl sin
	frsp f3, f1
	lfs f2, float_10_8041b124(r2)
	lfs f0, 0x8c(r30)
	fmr f1, f31
	fnmsubs f0, f2, f3, f0
	stfs f0, 0x0(r29)
	bl cos
	frsp f3, f1
	lfs f2, float_10_8041b124(r2)
	lfs f0, 0x94(r30)
	lfs f1, float_20_8041b140(r2)
	fnmsubs f0, f2, f3, f0
	stfs f0, 0x8(r29)
	lfs f0, 0x90(r30)
	fadds f0, f1, f0
	stfs f0, 0x4(r29)
	b @3
	@2:
	fmr f1, f31
	bl sin
	frsp f3, f1
	lfs f2, float_20_8041b140(r2)
	lfs f0, 0x8c(r30)
	fmr f1, f31
	fnmsubs f0, f2, f3, f0
	stfs f0, 0x0(r29)
	bl cos
	frsp f3, f1
	lfs f2, float_20_8041b140(r2)
	lfs f0, 0x94(r30)
	lfs f1, float_16_8041b17c(r2)
	fnmsubs f0, f2, f3, f0
	stfs f0, 0x8(r29)
	lfs f0, 0x90(r30)
	fadds f0, f1, f0
	stfs f0, 0x4(r29)
	@3:
	lbz r0, 0x2f(r31)
	extsb. r0, r0
	beq @4
	bl marioGetPartyId
	cmpwi r3, 0x0
	blt @5
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r31, r3, r0
	b @6
	@5:
	li r31, 0x0
	@6:
	lfs f1, 0x1ac(r30)
	lfs f2, float_10_8041b124(r2)
	bl toMovedir2
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl sincosf
	bl yoshiGetStatus
	cmpwi r3, 0x2
	beq @7
	lfs f3, float_12_8041b18c(r2)
	lfs f2, 0xc(r1)
	lfs f0, 0x58(r31)
	lfs f1, float_20_8041b140(r2)
	fnmsubs f0, f3, f2, f0
	stfs f0, 0x0(r29)
	lfs f2, 0x8(r1)
	lfs f0, 0x60(r31)
	fnmsubs f0, f3, f2, f0
	stfs f0, 0x8(r29)
	lfs f0, 0x5c(r31)
	fadds f0, f1, f0
	stfs f0, 0x4(r29)
	b @4
	@7:
	lfs f3, float_22_8041b190(r2)
	lfs f2, 0xc(r1)
	lfs f0, 0x58(r31)
	lfs f1, float_16_8041b17c(r2)
	fnmsubs f0, f3, f2, f0
	stfs f0, 0x0(r29)
	lfs f2, 0x8(r1)
	lfs f0, 0x60(r31)
	fnmsubs f0, f3, f2, f0
	stfs f0, 0x8(r29)
	lfs f0, 0x5c(r31)
	fadds f0, f1, f0
	stfs f0, 0x4(r29)
	b @4
	@1:
	cmplwi r0, 0x18
	bne @8
	lfs f0, 0x8c(r30)
	lfs f1, float_40_8041b194(r2)
	stfs f0, 0x0(r29)
	lfs f0, 0x94(r30)
	stfs f0, 0x8(r29)
	lfs f0, 0x90(r30)
	fadds f0, f1, f0
	stfs f0, 0x4(r29)
	b @4
	@8:
	cmplwi r0, 0x19
	bne @9
	bl N_marioShipGetDir
	cmpwi r3, 0x0
	beq @10
	lfs f1, float_0_8041b100(r2)
	b @11
	@10:
	lfs f1, float_180_8041b0fc(r2)
	@11:
	bl toMovedirSimple
	addi r3, r1, 0xc
	addi r4, r1, 0x8
	bl sincosf
	lfs f2, float_22_8041b190(r2)
	lfs f1, 0xc(r1)
	lfs f0, 0x8c(r30)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r29)
	lfs f1, 0x8(r1)
	lfs f0, 0x94(r30)
	fmadds f0, f2, f1, f0
	stfs f0, 0x8(r29)
	lfs f0, 0x90(r30)
	stfs f0, 0x4(r29)
	b @4
	@9:
	lfs f0, 0x8c(r30)
	lfs f1, float_20_8041b140(r2)
	stfs f0, 0x0(r29)
	lfs f0, 0x94(r30)
	stfs f0, 0x8(r29)
	lfs f0, 0x90(r30)
	fadds f0, f1, f0
	stfs f0, 0x4(r29)
	@4:
	psq_l f31, 0x28(r1), 0, 0
	lwz r0, 0x34(r1)
	lfd f31, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void allPartyRideShip(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl marioGetPartyId
	cmpwi r3, 0x0
	blt @1
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r31, r3, r0
	b @2
	@1:
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	beq @3
	bl bomhei_use_cancel
	lwz r0, 0x0(r31)
	mr r3, r31
	li r4, 0xb
	oris r0, r0, 0x2
	stw r0, 0x0(r31)
	bl partyChgRunMode
	@3:
	la r3, partyPtrTbl(r13)
	lwz r3, 0x4(r3)
	cmplwi r3, 0x0
	beq @4
	lwz r0, 0x0(r3)
	li r4, 0xb
	oris r0, r0, 0x2
	stw r0, 0x0(r3)
	bl partyChgRunMode
	@4:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void allPartyRidePlane(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl marioGetPartyId
	cmpwi r3, 0x0
	blt @1
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r31, r3, r0
	b @2
	@1:
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	beq @3
	bl bomhei_use_cancel
	lwz r0, 0x0(r31)
	mr r3, r31
	li r4, 0xb
	oris r0, r0, 0x1
	stw r0, 0x0(r31)
	bl partyChgRunMode
	@3:
	la r3, partyPtrTbl(r13)
	lwz r3, 0x4(r3)
	cmplwi r3, 0x0
	beq @4
	lwz r0, 0x0(r3)
	li r4, 0xb
	oris r0, r0, 0x1
	stw r0, 0x0(r3)
	bl partyChgRunMode
	@4:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void partyDokanEnd(s32 id, s32 dir) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	cmpwi r3, 0x0
	stw r0, 0x14(r1)
	blt @1
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @2
	@1:
	li r3, 0x0
	@2:
	cmplwi r3, 0x0
	beq @3
	lbz r0, 0x34(r3)
	cmplwi r0, 0xa
	bne @3
	li r0, 0x64
	cmplwi r3, 0x0
	stb r0, 0x38(r3)
	stb r4, 0x2e(r3)
	lwz r0, 0x4(r3)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x4(r3)
	lwz r0, 0x4(r3)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r3)
	lwz r0, 0x4(r3)
	rlwinm r0, r0, 0, 26, 23
	stw r0, 0x4(r3)
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 6, 4
	stw r0, 0x0(r3)
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 7, 5
	stw r0, 0x0(r3)
	beq @4
	lwz r0, 0x4(r3)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x4(r3)
	@4:
	lwz r4, 0x58(r3)
	lwz r0, 0x5c(r3)
	stw r4, 0xb8(r3)
	stw r0, 0xbc(r3)
	lwz r0, 0x60(r3)
	stw r0, 0xc0(r3)
	bl L_partyVivianTailStart
	@3:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

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
	beq @1
	bge @2
	cmpwi r0, 0xa
	beq @3
	bge @4
	cmpwi r0, 0x0
	beq @5
	b @4
	@2:
	cmpwi r0, 0x66
	beq @6
	bge @4
	b @7
	@5:
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
	bne @8
	stfs f0, 0x70(r30)
	@8:
	lfs f0, 0x70(r30)
	stfs f0, 0x74(r30)
	lfs f0, 0x70(r30)
	stfs f0, 0x78(r30)
	b @4
	@3:
	lfs f1, 0x64(r30)
	lfs f0, 0x124(r30)
	fadds f0, f1, f0
	stfs f0, 0x64(r30)
	b @4
	@1:
	lbz r0, 0x2e(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @9
	bge @4
	cmpwi r0, 0x2
	bge @4
	cmpwi r0, 0x0
	bge @10
	b @4
	@10:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne @11
	lwz r3, 0x1c(r30)
	cmplwi r3, 0x0
	beq @12
	addi r4, r31, 0x1d8
	bl strcmp
	cmpwi r3, 0x0
	beq @11
	@12:
	addi r3, r31, 0x1d8
	li r0, 0x0
	stw r3, 0x1c(r30)
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x4000
	stw r0, 0x8(r30)
	@11:
	li r3, 0x12
	li r0, 0x65
	stw r3, 0x24(r30)
	stb r0, 0x38(r30)
	b @4
	@9:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne @13
	lwz r3, 0x1c(r30)
	cmplwi r3, 0x0
	beq @14
	addi r4, r31, 0x1d8
	bl strcmp
	cmpwi r3, 0x0
	beq @13
	@14:
	addi r3, r31, 0x1d8
	li r0, 0x0
	stw r3, 0x1c(r30)
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x4000
	stw r0, 0x8(r30)
	@13:
	li r3, 0x12
	li r0, 0x65
	stw r3, 0x24(r30)
	stb r0, 0x38(r30)
	b @4
	@7:
	lbz r0, 0x2e(r30)
	extsb r0, r0
	cmpwi r0, 0x2
	bge @15
	cmpwi r0, 0x0
	bge @16
	b @15
	@16:
	lfs f1, 0x60(r30)
	lfs f0, float_neg0p2_8041b19c(r2)
	fadds f0, f1, f0
	stfs f0, 0x60(r30)
	@15:
	lwz r3, 0x24(r30)
	subic. r0, r3, 0x1
	stw r0, 0x24(r30)
	bgt @4
	li r0, 0x66
	stb r0, 0x38(r30)
	b @4
	@6:
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
	beq @17
	lwz r0, 0x1c(r30)
	cmplwi r0, 0x0
	beq @17
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
	blt @17
	bl animPaperPoseRelease
	li r0, -0x1
	stw r0, 0x14(r30)
	@17:
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
	beq @18
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x4(r30)
	@18:
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
	blt @19
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r0, r3, r0
	b @20
	@19:
	li r0, 0x0
	@20:
	cmplwi r0, 0x0
	beq @21
	li r31, 0x1
	@21:
	bl marioGetExtraPartyId
	cmpwi r3, 0x0
	blt @22
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r0, r3, r0
	b @23
	@22:
	li r0, 0x0
	@23:
	cmplwi r0, 0x0
	beq @24
	addi r31, r31, 0x1
	@24:
	lbz r0, 0x2e(r30)
	cmpwi r0, 0x4
	bne @25
	cmpwi r31, 0x1
	bne @26
	lfs f1, 0x60(r30)
	lfs f0, float_neg4_8041b1a0(r2)
	fadds f0, f1, f0
	stfs f0, 0x60(r30)
	b @25
	@26:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne @27
	lfs f2, 0x60(r30)
	lfs f1, float_neg4_8041b1a0(r2)
	lfs f0, float_1p5_8041b1a4(r2)
	fadds f1, f2, f1
	stfs f1, 0x60(r30)
	lfs f1, 0x58(r30)
	fadds f0, f1, f0
	stfs f0, 0x58(r30)
	b @25
	@27:
	lfs f2, 0x60(r30)
	lfs f1, float_neg3_8041b1a8(r2)
	lfs f0, float_neg1p5_8041b1ac(r2)
	fadds f1, f2, f1
	stfs f1, 0x60(r30)
	lfs f1, 0x58(r30)
	fadds f0, f1, f0
	stfs f0, 0x58(r30)
	@25:
	lbz r0, 0x2e(r30)
	cmpwi r0, 0x1
	bne @4
	cmpwi r31, 0x1
	bne @28
	lfs f1, 0x60(r30)
	lfs f0, float_neg4_8041b1a0(r2)
	fadds f0, f1, f0
	stfs f0, 0x60(r30)
	b @4
	@28:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 28, 28
	bne @29
	lfs f2, 0x60(r30)
	lfs f1, float_neg4_8041b1a0(r2)
	lfs f0, float_1p5_8041b1a4(r2)
	fadds f1, f2, f1
	stfs f1, 0x60(r30)
	lfs f1, 0x58(r30)
	fadds f0, f1, f0
	stfs f0, 0x58(r30)
	b @4
	@29:
	lfs f2, 0x60(r30)
	lfs f1, float_neg3_8041b1a8(r2)
	lfs f0, float_neg1p5_8041b1ac(r2)
	fadds f1, f2, f1
	stfs f1, 0x60(r30)
	lfs f1, 0x58(r30)
	fadds f0, f1, f0
	stfs f0, 0x58(r30)
	@4:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 partyDokanInit(PartyEntry* party) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r3
	lis r3, vec3_802ccd30@ha
	stw r28, 0x10(r1)
	addi r31, r3, vec3_802ccd30@l
	lwz r0, 0x4(r29)
	lwz r30, 0x160(r29)
	ori r0, r0, 0x10
	stw r0, 0x4(r29)
	lbz r0, 0x3e(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @1
	bge @2
	cmpwi r0, 0x1
	beq @3
	bge @4
	cmpwi r0, 0x0
	bge @5
	b @6
	@2:
	cmpwi r0, 0x6
	bge @6
	b @7
	@4:
	lwz r3, 0x14(r29)
	cmpwi r3, 0x0
	blt @8
	bl animPaperPoseRelease
	li r0, -0x1
	stw r0, 0x14(r29)
	@8:
	lwz r0, 0x4(r29)
	addi r3, r31, 0x1e0
	li r4, 0x2
	oris r0, r0, 0x400
	stw r0, 0x4(r29)
	bl animPaperPoseEntry
	stw r3, 0x14(r29)
	addi r3, r31, 0x1e0
	addi r4, r31, 0x1ec
	li r28, 0x0
	bl strcmp
	cmpwi r3, 0x0
	beq @9
	addi r3, r31, 0x1e0
	addi r4, r31, 0x1f4
	bl strcmp
	cmpwi r3, 0x0
	beq @9
	addi r3, r31, 0x1e0
	addi r4, r31, 0x1fc
	bl strcmp
	cmpwi r3, 0x0
	beq @9
	addi r3, r31, 0x1e0
	mr r4, r3
	bl strcmp
	cmpwi r3, 0x0
	bne @10
	@9:
	li r28, 0x1
	@10:
	cntlzw r0, r28
	addi r3, r31, 0x1e0
	srwi r28, r0, 5
	addi r4, r31, 0x208
	bl strcmp
	cmpwi r3, 0x0
	bne @11
	lbz r0, 0x31(r29)
	extsb r0, r0
	subfic r0, r0, 0x5
	cntlzw r0, r0
	srwi r28, r0, 5
	@11:
	lwz r3, 0xc(r29)
	mr r5, r28
	addi r4, r31, 0x1e0
	bl animPoseSetPaperAnimGroup
	lfs f0, float_30_8041b178(r2)
	li r0, 0x0
	stfs f0, 0x124(r29)
	stb r0, 0x38(r29)
	b @6
	@5:
	lwz r3, 0x120(r31)
	lwz r0, 0x124(r31)
	stw r3, 0x70(r29)
	stw r0, 0x74(r29)
	lwz r0, 0x128(r31)
	stw r0, 0x78(r29)
	@3:
	lwz r3, 0x14(r29)
	cmpwi r3, 0x0
	blt @12
	bl animPaperPoseRelease
	li r0, -0x1
	stw r0, 0x14(r29)
	@12:
	lwz r0, 0x4(r29)
	addi r3, r31, 0x1e0
	li r4, 0x2
	oris r0, r0, 0x400
	stw r0, 0x4(r29)
	bl animPaperPoseEntry
	stw r3, 0x14(r29)
	addi r3, r31, 0x1e0
	addi r4, r31, 0x1ec
	li r28, 0x0
	bl strcmp
	cmpwi r3, 0x0
	beq @13
	addi r3, r31, 0x1e0
	addi r4, r31, 0x1f4
	bl strcmp
	cmpwi r3, 0x0
	beq @13
	addi r3, r31, 0x1e0
	addi r4, r31, 0x1fc
	bl strcmp
	cmpwi r3, 0x0
	beq @13
	addi r3, r31, 0x1e0
	mr r4, r3
	bl strcmp
	cmpwi r3, 0x0
	bne @14
	@13:
	li r28, 0x1
	@14:
	cntlzw r0, r28
	addi r3, r31, 0x1e0
	srwi r28, r0, 5
	addi r4, r31, 0x208
	bl strcmp
	cmpwi r3, 0x0
	bne @15
	lbz r0, 0x31(r29)
	extsb r0, r0
	subfic r0, r0, 0x5
	cntlzw r0, r0
	srwi r28, r0, 5
	@15:
	lwz r3, 0xc(r29)
	mr r5, r28
	addi r4, r31, 0x1e0
	bl animPoseSetPaperAnimGroup
	lfs f0, float_30_8041b178(r2)
	li r0, 0x0
	stfs f0, 0x124(r29)
	stb r0, 0x38(r29)
	b @6
	@7:
	lwz r3, 0x14(r29)
	cmpwi r3, 0x0
	blt @16
	bl animPaperPoseRelease
	li r0, -0x1
	stw r0, 0x14(r29)
	@16:
	lwz r0, 0x4(r29)
	addi r3, r31, 0x1fc
	li r4, 0x2
	oris r0, r0, 0x400
	stw r0, 0x4(r29)
	bl animPaperPoseEntry
	stw r3, 0x14(r29)
	addi r3, r31, 0x1fc
	addi r4, r31, 0x1ec
	li r28, 0x0
	bl strcmp
	cmpwi r3, 0x0
	beq @17
	addi r3, r31, 0x1fc
	addi r4, r31, 0x1f4
	bl strcmp
	cmpwi r3, 0x0
	beq @17
	addi r3, r31, 0x1fc
	mr r4, r3
	bl strcmp
	cmpwi r3, 0x0
	beq @17
	addi r3, r31, 0x1fc
	addi r4, r31, 0x1e0
	bl strcmp
	cmpwi r3, 0x0
	bne @18
	@17:
	li r28, 0x1
	@18:
	cntlzw r0, r28
	addi r3, r31, 0x1fc
	srwi r28, r0, 5
	addi r4, r31, 0x208
	bl strcmp
	cmpwi r3, 0x0
	bne @19
	lbz r0, 0x31(r29)
	extsb r0, r0
	subfic r0, r0, 0x5
	cntlzw r0, r0
	srwi r28, r0, 5
	@19:
	lwz r3, 0xc(r29)
	mr r5, r28
	addi r4, r31, 0x1fc
	bl animPoseSetPaperAnimGroup
	lfs f1, float_26_8041b1b0(r2)
	li r0, 0xa
	lfs f0, float_10_8041b124(r2)
	stfs f1, 0x124(r29)
	stb r0, 0x38(r29)
	stfs f0, 0x8c(r29)
	b @6
	@1:
	lwz r3, 0x14(r29)
	cmpwi r3, 0x0
	blt @20
	bl animPaperPoseRelease
	li r0, -0x1
	stw r0, 0x14(r29)
	@20:
	lwz r0, 0x4(r29)
	addi r3, r31, 0x1fc
	li r4, 0x2
	oris r0, r0, 0x400
	stw r0, 0x4(r29)
	bl animPaperPoseEntry
	stw r3, 0x14(r29)
	addi r3, r31, 0x1fc
	addi r4, r31, 0x1ec
	li r28, 0x0
	bl strcmp
	cmpwi r3, 0x0
	beq @21
	addi r3, r31, 0x1fc
	addi r4, r31, 0x1f4
	bl strcmp
	cmpwi r3, 0x0
	beq @21
	addi r3, r31, 0x1fc
	mr r4, r3
	bl strcmp
	cmpwi r3, 0x0
	beq @21
	addi r3, r31, 0x1fc
	addi r4, r31, 0x1e0
	bl strcmp
	cmpwi r3, 0x0
	bne @22
	@21:
	li r28, 0x1
	@22:
	cntlzw r0, r28
	addi r3, r31, 0x1fc
	srwi r28, r0, 5
	addi r4, r31, 0x208
	bl strcmp
	cmpwi r3, 0x0
	bne @23
	lbz r0, 0x31(r29)
	extsb r0, r0
	subfic r0, r0, 0x5
	cntlzw r0, r0
	srwi r28, r0, 5
	@23:
	lwz r3, 0xc(r29)
	mr r5, r28
	addi r4, r31, 0x1fc
	bl animPoseSetPaperAnimGroup
	lfs f1, float_neg26_8041b1b4(r2)
	li r0, 0xa
	lfs f0, float_10_8041b124(r2)
	stfs f1, 0x124(r29)
	lfs f1, float_180_8041b0fc(r2)
	stb r0, 0x38(r29)
	stfs f0, 0x8c(r29)
	lfs f0, 0xbc(r30)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x64(r29)
	@6:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 30, 30
	bne @24
	lwz r3, 0x1c(r29)
	cmplwi r3, 0x0
	beq @25
	addi r4, r31, 0x210
	bl strcmp
	cmpwi r3, 0x0
	beq @24
	@25:
	addi r3, r31, 0x210
	li r0, 0x0
	stw r3, 0x1c(r29)
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x4000
	stw r0, 0x8(r29)
	@24:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 30, 30
	bne @26
	lbz r0, 0x31(r29)
	extsb r3, r0
	cmpwi r3, 0x8
	bge @27
	bl partyGetHp
	@27:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @28
	lbz r0, 0x31(r29)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	extsb r0, r0
	mulli r0, r0, 0x3c
	lwzx r28, r3, r0
	b @29
	@28:
	lbz r0, 0x31(r29)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @30
	mulli r0, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	addi r3, r3, partyDotPoseTbl@l
	lwzx r28, r3, r0
	b @29
	@30:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r0, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	addi r3, r3, yoshiDotPoseTbl@l
	lwzx r28, r3, r0
	@29:
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @31
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	beq @26
	@31:
	stw r28, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@26:
	lwz r0, 0x4(r29)
	li r4, 0x1
	ori r0, r0, 0x8
	stw r0, 0x4(r29)
	lwz r0, 0x4(r29)
	ori r0, r0, 0x10
	stw r0, 0x4(r29)
	lwz r3, 0xc(r29)
	bl animPoseSetMaterialLightFlagOff
	lfs f1, float_180_8041b0fc(r2)
	lfs f0, 0x1a8(r30)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x110(r29)
	mr r3, r29
	lfs f0, 0x1a8(r30)
	stfs f0, 0x10c(r29)
	lfs f0, 0x19c(r30)
	stfs f0, 0xfc(r29)
	lwz r4, 0x8c(r30)
	lwz r0, 0x90(r30)
	stw r4, 0x58(r29)
	stw r0, 0x5c(r29)
	lwz r0, 0x94(r30)
	stw r0, 0x60(r29)
	bl L_partyVivianTailStop
	lwz r0, 0x24(r1)
	li r3, 0x0
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 partyGoodbyeMain(PartyEntry* party) {
	nofralloc
	stwu r1, -0xa0(r1)
	mflr r0
	stw r0, 0xa4(r1)
	stfd f31, 0x90(r1)
	psq_st f31, 0x98(r1), 0, 0
	stfd f30, 0x80(r1)
	psq_st f30, 0x88(r1), 0, 0
	stfd f29, 0x70(r1)
	psq_st f29, 0x78(r1), 0, 0
	stfd f28, 0x60(r1)
	psq_st f28, 0x68(r1), 0, 0
	stfd f27, 0x50(r1)
	psq_st f27, 0x58(r1), 0, 0
	stfd f26, 0x40(r1)
	psq_st f26, 0x48(r1), 0, 0
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	stw r29, 0x34(r1)
	mr r31, r3
	bl marioGetPtr
	lbz r0, 0x38(r31)
	mr r30, r3
	cmplwi r0, 0x14
	bgt @1
	lis r3, jumptable_80312720@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_80312720@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@2:
	lbz r4, 0x31(r31)
	lis r3, partyDataTbl@ha
	addi r0, r3, partyDataTbl@l
	mr r3, r31
	extsb r4, r4
	mulli r4, r4, 0x28
	add r4, r0, r4
	stw r4, party_dp(r13)
	lwz r12, 0xc(r4)
	mtctr r12
	bctrl
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x6
	bne @3
	bl vivianGetStatus
	cmpwi r3, 0x0
	bne @1
	li r3, 0xa
	li r0, 0x8
	stb r3, 0x38(r31)
	stb r0, 0x34(r31)
	b @1
	@3:
	cmpwi r0, 0x4
	bne @4
	bl yoshiGetStatus
	cmpwi r3, 0x0
	bne @1
	li r3, 0xa
	li r0, 0x8
	stb r3, 0x38(r31)
	stb r0, 0x34(r31)
	b @1
	@4:
	li r3, 0xa
	li r0, 0x8
	stb r3, 0x38(r31)
	stb r0, 0x34(r31)
	b @1
	@5:
	lis r3, 0x2
	addi r4, r30, 0x8c
	addi r3, r3, 0x91f
	bl psndSFXOn_3D
	lfs f3, 0x8c(r30)
	lfs f4, float_0p5_8041b170(r2)
	stfs f3, 0x94(r31)
	fmr f30, f3
	lfs f5, float_4_8041b10c(r2)
	lfs f2, 0x1b8(r30)
	lfs f1, 0x90(r30)
	lfs f0, float_1p6_8041b16c(r2)
	fmadds f31, f4, f2, f1
	stfs f31, 0x98(r31)
	lfs f4, 0x94(r30)
	stfs f4, 0x9c(r31)
	fmr f29, f4
	lfs f28, 0x58(r31)
	lfs f26, 0x60(r31)
	lfs f27, 0x5c(r31)
	fmr f1, f28
	fmr f2, f26
	stfs f5, 0x104(r31)
	stfs f0, 0x11c(r31)
	bl distABf
	stfs f1, 0x128(r31)
	fmr f1, f28
	fmr f2, f26
	fmr f3, f30
	fmr f4, f29
	bl angleABf
	stfs f1, 0x100(r31)
	lis r0, 0x4330
	li r4, 0xf
	lis r3, double_to_int_802ccf00@ha
	stw r4, 0x24(r31)
	fsubs f5, f31, f27
	lfd f4, double_to_int_802ccf00@l(r3)
	lwz r3, 0x24(r31)
	stw r0, 0x8(r1)
	xoris r3, r3, 0x8000
	lfs f1, 0x128(r31)
	stw r3, 0xc(r1)
	lfs f3, float_0p5_8041b170(r2)
	lfd f0, 0x8(r1)
	stw r0, 0x18(r1)
	fsubs f0, f0, f4
	stw r0, 0x10(r1)
	fdivs f0, f1, f0
	stw r0, 0x20(r1)
	stfs f0, 0x104(r31)
	lwz r0, 0x24(r31)
	lfs f1, 0x11c(r31)
	xoris r0, r0, 0x8000
	stw r0, 0x1c(r1)
	lfd f0, 0x18(r1)
	stw r0, 0x14(r1)
	fsubs f0, f0, f4
	lfd f2, 0x10(r1)
	stw r0, 0x24(r1)
	fmuls f1, f1, f0
	fsubs f2, f2, f4
	lfd f0, 0x20(r1)
	fsubs f0, f0, f4
	fmuls f1, f2, f1
	fmadds f1, f3, f1, f5
	fdivs f0, f1, f0
	stfs f0, 0x114(r31)
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 30, 30
	bne @6
	lbz r0, 0x31(r31)
	extsb r3, r0
	cmpwi r3, 0x8
	bge @7
	bl partyGetHp
	@7:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @8
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r0, r3, partyPoseTbl@l
	extsb r3, r4
	mulli r3, r3, 0x3c
	add r3, r0, r3
	lwz r30, 0x10(r3)
	b @9
	@8:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @10
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	addi r0, r3, partyDotPoseTbl@l
	add r3, r0, r4
	lwz r30, 0x10(r3)
	b @9
	@10:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	addi r0, r3, yoshiDotPoseTbl@l
	add r3, r0, r4
	lwz r30, 0x10(r3)
	@9:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @11
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @6
	@11:
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@6:
	li r0, 0xb
	stb r0, 0x38(r31)
	b @1
	@12:
	lfs f1, 0x114(r31)
	addi r3, r31, 0x58
	lfs f0, 0x11c(r31)
	addi r4, r31, 0x60
	fsubs f0, f1, f0
	stfs f0, 0x114(r31)
	lfs f1, 0x5c(r31)
	lfs f0, 0x114(r31)
	fadds f0, f1, f0
	stfs f0, 0x5c(r31)
	lfs f1, 0x104(r31)
	lfs f2, 0x100(r31)
	bl movePos
	lfs f1, float_50_8041b1b8(r2)
	lfs f0, 0x10c(r31)
	fadds f1, f1, f0
	bl revise360
	stfs f1, 0x10c(r31)
	lis r0, 0x4330
	lis r3, double_to_int_802ccf00@ha
	lfs f0, float_10_8041b124(r2)
	lwz r4, 0x24(r31)
	stw r0, 0x20(r1)
	xoris r0, r4, 0x8000
	lfd f2, double_to_int_802ccf00@l(r3)
	stw r0, 0x24(r1)
	lfd f1, 0x20(r1)
	fsubs f1, f1, f2
	fcmpo cr0, f1, f0
	ble @13
	fmr f1, f0
	@13:
	lfs f0, float_10_8041b124(r2)
	fdivs f0, f1, f0
	stfs f0, 0x70(r31)
	lfs f0, 0x70(r31)
	stfs f0, 0x74(r31)
	lfs f0, 0x70(r31)
	stfs f0, 0x78(r31)
	lwz r3, 0x24(r31)
	subic. r0, r3, 0x1
	stw r0, 0x24(r31)
	bge @1
	li r0, 0xc
	stb r0, 0x38(r31)
	b @1
	@14:
	lwz r0, 0x4(r31)
	li r30, 0x1
	rlwinm. r0, r0, 0, 30, 30
	bne @15
	lbz r0, 0x31(r31)
	li r29, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @16
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @16
	li r29, 0x1
	@16:
	cmpwi r29, 0x1
	bne @17
	li r30, 0xc
	@17:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @18
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @19
	@18:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @20
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @19
	@20:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@19:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @21
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @15
	@21:
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@15:
	lfs f0, float_0_8041b100(r2)
	mr r3, r31
	li r4, 0xe
	stfs f0, 0x114(r31)
	lfs f0, 0x98(r31)
	stfs f0, 0x5c(r31)
	bl partyChgRunMode
	li r3, 0x1
	b @22
	@23:
	mr r3, r31
	li r4, 0xe
	bl partyChgRunMode
	li r3, 0x1
	b @22
	@1:
	li r3, 0x0
	@22:
	psq_l f31, 0x98(r1), 0, 0
	lfd f31, 0x90(r1)
	psq_l f30, 0x88(r1), 0, 0
	lfd f30, 0x80(r1)
	psq_l f29, 0x78(r1), 0, 0
	lfd f29, 0x70(r1)
	psq_l f28, 0x68(r1), 0, 0
	lfd f28, 0x60(r1)
	psq_l f27, 0x58(r1), 0, 0
	lfd f27, 0x50(r1)
	psq_l f26, 0x48(r1), 0, 0
	lfd f26, 0x40(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	lwz r0, 0xa4(r1)
	lwz r29, 0x34(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}

asm s32 partyGoodbyeInit(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, partyDataTbl@ha
	stw r0, 0x14(r1)
	li r0, 0xa
	stw r31, 0xc(r1)
	mr r31, r3
	stb r0, 0x38(r3)
	addi r0, r4, partyDataTbl@l
	lbz r4, 0x31(r3)
	extsb r4, r4
	mulli r4, r4, 0x28
	add r4, r0, r4
	stw r4, party_dp(r13)
	lwz r12, 0x4(r4)
	cmplwi r12, 0x0
	beq @1
	mtctr r12
	bctrl
	@1:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq @2
	lbz r0, 0x31(r31)
	cmpwi r0, 0x6
	bne @3
	mr r3, r31
	bl vivianUnhold
	li r0, 0x0
	stb r0, 0x38(r31)
	@3:
	lbz r0, 0x31(r31)
	cmpwi r0, 0x4
	bne @2
	bl marioGetoffYoshi
	li r0, 0x0
	stb r0, 0x38(r31)
	@2:
	lwz r3, 0x160(r31)
	lhz r0, 0x2e(r3)
	cmplwi r0, 0x16
	beq @4
	cmplwi r0, 0x18
	beq @4
	cmplwi r0, 0x19
	bne @5
	@4:
	li r0, 0x14
	stb r0, 0x38(r31)
	@5:
	lwz r0, 0x14(r1)
	li r3, 0x0
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 partyHelloMain(PartyEntry* party) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stfd f30, 0x40(r1)
	psq_st f30, 0x48(r1), 0, 0
	stw r31, 0x3c(r1)
	stw r30, 0x38(r1)
	stw r29, 0x34(r1)
	stw r28, 0x30(r1)
	mr r29, r3
	li r31, 0x0
	lbz r0, 0x38(r3)
	lwz r30, 0x160(r3)
	cmplwi r0, 0x1e
	bgt @1
	lis r4, jumptable_80312774@ha
	slwi r0, r0, 2
	addi r4, r4, jumptable_80312774@l
	lwzx r0, r4, r0
	mtctr r0
	bctr
	@2:
	lfs f31, 0x8c(r30)
	addi r4, r29, 0x94
	lfs f2, 0x90(r30)
	lfs f30, 0x94(r30)
	lfs f1, float_0p5_8041b170(r2)
	stfs f31, 0x58(r29)
	lfs f0, 0x1b8(r30)
	fmadds f0, f1, f0, f2
	stfs f0, 0x5c(r29)
	stfs f30, 0x60(r29)
	bl partyGetAppearPos
	li r0, 0x10
	fmr f1, f31
	stw r0, 0x24(r29)
	fmr f2, f30
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl distABf
	stfs f1, 0x128(r29)
	fmr f1, f31
	fmr f2, f30
	lfs f3, 0x94(r29)
	lfs f4, 0x9c(r29)
	bl angleABf
	stfs f1, 0x100(r29)
	lis r0, 0x4330
	lis r3, double_to_int_802ccf00@ha
	lfs f3, float_0p5_8041b170(r2)
	lwz r5, 0x24(r29)
	addi r4, r3, double_to_int_802ccf00@l
	stw r0, 0x20(r1)
	xoris r3, r5, 0x8000
	lfd f4, 0x0(r4)
	stw r3, 0x24(r1)
	lfs f2, 0x128(r29)
	lfd f0, 0x20(r1)
	stw r0, 0x28(r1)
	fsubs f1, f0, f4
	lfs f0, float_1_8041b0e8(r2)
	fdivs f1, f2, f1
	stfs f1, 0x104(r29)
	lwz r0, 0x24(r29)
	lfs f2, 0x98(r29)
	xoris r0, r0, 0x8000
	lfs f1, 0x5c(r29)
	stw r0, 0x2c(r1)
	fsubs f5, f2, f1
	lfd f1, 0x28(r1)
	fsubs f2, f1, f4
	fabs f1, f5
	fmuls f2, f3, f2
	fcmpo cr0, f1, f0
	bge @3
	lfs f5, float_10_8041b124(r2)
	b @4
	@3:
	lfs f0, float_0_8041b100(r2)
	fcmpo cr0, f5, f0
	cror eq, gt, eq
	bne @5
	lfs f0, 0xf0(r29)
	fmadds f5, f3, f0, f5
	b @4
	@5:
	lfs f5, float_10_8041b124(r2)
	@4:
	fadds f1, f5, f5
	li r0, 0x1
	fmsubs f0, f2, f2, f2
	fdivs f0, f1, f0
	fmuls f1, f0, f2
	fneg f0, f0
	stfs f1, 0x114(r29)
	stfs f0, 0x118(r29)
	lwz r3, 0x0(r29)
	ori r3, r3, 0x10
	stw r3, 0x0(r29)
	stb r0, 0x38(r29)
	b @1
	@6:
	bl partyMoveNoHosei
	lfs f1, 0x114(r29)
	lfs f0, float_0_8041b100(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @7
	lwz r0, 0x0(r29)
	lfs f0, float_neg1p6_8041b180(r2)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x0(r29)
	stfs f0, 0x118(r29)
	@7:
	lfs f1, 0x5c(r29)
	lfs f0, float_neg2000_8041b164(r2)
	fcmpo cr0, f1, f0
	bge @8
	li r3, 0x0
	li r0, 0x2
	stw r3, 0x24(r29)
	stb r0, 0x38(r29)
	b @1
	@8:
	lwz r0, 0x138(r29)
	cmplwi r0, 0x0
	bne @9
	lwz r5, 0x24(r29)
	lis r0, 0x4330
	stw r0, 0x28(r1)
	lis r4, double_to_int_802ccf00@ha
	subfic r5, r5, 0x10
	lis r3, vec3_802cce2c@ha
	xoris r0, r5, 0x8000
	stw r0, 0x2c(r1)
	addi r5, r3, vec3_802cce2c@l
	addi r3, r4, double_to_int_802ccf00@l
	lwz r4, 0x0(r5)
	lfd f1, 0x0(r3)
	lfd f0, 0x28(r1)
	lwz r3, 0x4(r5)
	fsubs f1, f0, f1
	lfs f0, float_0p0625_8041b184(r2)
	lwz r0, 0x8(r5)
	stw r4, 0x14(r1)
	fmuls f0, f1, f0
	stw r3, 0x18(r1)
	stfs f0, 0x14(r1)
	stw r0, 0x1c(r1)
	lwz r0, 0x14(r1)
	stfs f0, 0x18(r1)
	stfs f0, 0x1c(r1)
	lwz r3, 0x18(r1)
	stw r0, 0x70(r29)
	lwz r0, 0x1c(r1)
	stw r3, 0x74(r29)
	stw r0, 0x78(r29)
	lwz r3, 0x24(r29)
	subic. r0, r3, 0x1
	stw r0, 0x24(r29)
	bgt @1
	li r0, 0x0
	stw r0, 0x24(r29)
	b @1
	@9:
	li r0, 0x2
	stb r0, 0x38(r29)
	@10:
	lwz r5, 0x24(r29)
	lis r0, 0x4330
	stw r0, 0x28(r1)
	lis r4, double_to_int_802ccf00@ha
	subfic r5, r5, 0x10
	lis r3, vec3_802cce38@ha
	xoris r0, r5, 0x8000
	stw r0, 0x2c(r1)
	addi r5, r3, vec3_802cce38@l
	addi r3, r4, double_to_int_802ccf00@l
	lwz r4, 0x0(r5)
	lfd f1, 0x0(r3)
	lfd f0, 0x28(r1)
	lwz r3, 0x4(r5)
	fsubs f1, f0, f1
	lfs f0, float_0p0625_8041b184(r2)
	lwz r0, 0x8(r5)
	stw r4, 0x8(r1)
	fmuls f0, f1, f0
	stw r3, 0xc(r1)
	stfs f0, 0x8(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x8(r1)
	stfs f0, 0xc(r1)
	stfs f0, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0x70(r29)
	lwz r0, 0x10(r1)
	stw r3, 0x74(r29)
	stw r0, 0x78(r29)
	lwz r3, 0x24(r29)
	subic. r0, r3, 0x1
	stw r0, 0x24(r29)
	bgt @1
	li r0, 0x0
	lfs f0, float_90_8041b0f0(r2)
	stw r0, 0x24(r29)
	lfs f1, 0x110(r29)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne @11
	lfs f0, float_270_8041b0f4(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne @11
	lfs f1, float_180_8041b0fc(r2)
	mr r3, r29
	bl partyToMovedir
	stfs f1, 0xfc(r29)
	lfs f0, float_180_8041b0fc(r2)
	lfs f1, 0xfc(r29)
	stfs f1, 0x100(r29)
	stfs f0, 0x10c(r29)
	stfs f0, 0x110(r29)
	b @12
	@11:
	lfs f1, float_0_8041b100(r2)
	mr r3, r29
	bl partyToMovedir
	stfs f1, 0xfc(r29)
	lfs f0, float_0_8041b100(r2)
	lfs f1, 0xfc(r29)
	stfs f1, 0x100(r29)
	stfs f0, 0x10c(r29)
	stfs f0, 0x110(r29)
	@12:
	mr r3, r29
	bl partyClearJumpPara
	lwz r0, 0x4(r29)
	li r31, 0x1
	rlwinm. r0, r0, 0, 30, 30
	bne @13
	lbz r0, 0x31(r29)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @14
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @14
	li r28, 0x1
	@14:
	cmpwi r28, 0x1
	bne @15
	li r31, 0xc
	@15:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @16
	lbz r4, 0x31(r29)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r31, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r31, r3, r0
	b @17
	@16:
	lbz r0, 0x31(r29)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @18
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r31, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r31, r3, r0
	b @17
	@18:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r31, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r31, r3, r0
	@17:
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @19
	mr r4, r31
	bl strcmp
	cmpwi r3, 0x0
	beq @13
	@19:
	stw r31, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@13:
	lwz r5, 0x4(r29)
	lis r3, 0x2
	li r0, 0x1
	addi r4, r30, 0x8c
	rlwinm r5, r5, 0, 28, 26
	addi r3, r3, 0x920
	stw r5, 0x4(r29)
	li r31, 0x1
	stb r0, 0x34(r29)
	bl psndSFXOn_3D
	b @1
	@20:
	addi r4, r29, 0x58
	bl partyGetAppearPos2
	lwz r3, 0x58(r29)
	li r30, 0x1
	lwz r0, 0x5c(r29)
	stw r3, 0xb8(r29)
	stw r0, 0xbc(r29)
	lwz r0, 0x60(r29)
	stw r0, 0xc0(r29)
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 30, 30
	bne @21
	lbz r0, 0x31(r29)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @22
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @22
	li r28, 0x1
	@22:
	cmpwi r28, 0x1
	bne @23
	li r30, 0xc
	@23:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @24
	lbz r4, 0x31(r29)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @25
	@24:
	lbz r0, 0x31(r29)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @26
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @25
	@26:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@25:
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @27
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @21
	@27:
	stw r30, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@21:
	li r0, 0x1
	li r31, 0x1
	stb r0, 0x34(r29)
	b @1
	@28:
	lwz r0, 0x4(r29)
	li r30, 0x1
	rlwinm. r0, r0, 0, 30, 30
	bne @29
	lbz r0, 0x31(r29)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @30
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @30
	li r28, 0x1
	@30:
	cmpwi r28, 0x1
	bne @31
	li r30, 0xc
	@31:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @32
	lbz r4, 0x31(r29)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @33
	@32:
	lbz r0, 0x31(r29)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @34
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @33
	@34:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@33:
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @35
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @29
	@35:
	stw r30, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@29:
	li r0, 0x0
	li r31, 0x1
	stb r0, 0x34(r29)
	b @1
	@36:
	bl allPartyForceRideOn
	li r31, 0x1
	@1:
	mr r3, r31
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	lwz r29, 0x34(r1)
	lwz r0, 0x64(r1)
	lwz r28, 0x30(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void partyHello(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r5, vec3_802ccd30@ha
	stw r0, 0x14(r1)
	addi r6, r5, vec3_802ccd30@l
	lwz r4, 0x8(r3)
	rlwinm. r0, r4, 0, 28, 28
	beq @1
	rlwinm r0, r4, 0, 29, 27
	stw r0, 0x8(r3)
	lwz r7, 0x160(r3)
	lhz r0, 0x2e(r7)
	cmplwi r0, 0x16
	beq @2
	cmplwi r0, 0x18
	beq @2
	cmplwi r0, 0x19
	bne @3
	@2:
	li r0, 0x1e
	stb r0, 0x38(r3)
	b @4
	@3:
	lbz r0, 0x34(r3)
	cmplwi r0, 0x4
	beq @5
	cmplwi r0, 0x5
	bne @6
	@5:
	lwz r4, 0x4(r3)
	li r0, 0x0
	ori r4, r4, 0x10
	stw r4, 0x4(r3)
	lwz r5, 0xd8(r6)
	lwz r4, 0xdc(r6)
	stw r5, 0x70(r3)
	stw r4, 0x74(r3)
	lwz r4, 0xe0(r6)
	stw r4, 0x78(r3)
	stb r0, 0x38(r3)
	lfs f0, 0x1a8(r7)
	stfs f0, 0x110(r3)
	lfs f0, 0x1a8(r7)
	stfs f0, 0x10c(r3)
	lwz r4, 0x8c(r7)
	lwz r0, 0x90(r7)
	stw r4, 0x58(r3)
	stw r0, 0x5c(r3)
	lwz r0, 0x94(r7)
	stw r0, 0x60(r3)
	lwz r4, 0x58(r3)
	lwz r0, 0x5c(r3)
	stw r4, 0xb8(r3)
	stw r0, 0xbc(r3)
	lwz r0, 0x60(r3)
	stw r0, 0xc0(r3)
	b @4
	@6:
	cmplwi r0, 0x7
	bne @7
	lwz r5, 0xe4(r6)
	li r0, 0x14
	lwz r4, 0xe8(r6)
	stw r5, 0x70(r3)
	stw r4, 0x74(r3)
	lwz r4, 0xec(r6)
	stw r4, 0x78(r3)
	stb r0, 0x38(r3)
	lfs f0, 0x1a8(r7)
	stfs f0, 0x110(r3)
	lfs f0, 0x1a8(r7)
	stfs f0, 0x10c(r3)
	b @4
	@7:
	lwz r5, 0xf0(r6)
	li r0, 0xa
	lwz r4, 0xf4(r6)
	stw r5, 0x70(r3)
	stw r4, 0x74(r3)
	lwz r4, 0xf8(r6)
	stw r4, 0x78(r3)
	stb r0, 0x38(r3)
	lfs f0, 0x1a8(r7)
	stfs f0, 0x110(r3)
	lfs f0, 0x1a8(r7)
	stfs f0, 0x10c(r3)
	lwz r4, 0x8c(r7)
	lwz r0, 0x90(r7)
	stw r4, 0x58(r3)
	stw r0, 0x5c(r3)
	lwz r0, 0x94(r7)
	stw r0, 0x60(r3)
	lwz r4, 0x58(r3)
	lwz r0, 0x5c(r3)
	stw r4, 0xb8(r3)
	stw r0, 0xbc(r3)
	lwz r0, 0x60(r3)
	stw r0, 0xc0(r3)
	@4:
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x0(r3)
	@1:
	bl partyHelloMain
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL partyDoWork(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stfd f31, 0x10(r1)
	psq_st f31, 0x18(r1), 0, 0
	stw r31, 0xc(r1)
	bl marioGetPtr
	lbz r0, 0x241(r3)
	extsb. r0, r0
	blt @1
	slwi r0, r0, 2
	la r3, partyPtrTbl(r13)
	lwzx r31, r3, r0
	b @2
	@1:
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @3
	li r3, 0x0
	b @4
	@3:
	lbz r0, 0x34(r31)
	cmplwi r0, 0x0
	beq @5
	cmplwi r0, 0x1
	beq @5
	cmplwi r0, 0x2
	beq @5
	li r3, 0x0
	b @4
	@5:
	lfs f31, float_0_8041b100(r2)
	bl marioGetPtr
	stfs f31, 0x180(r3)
	mr r3, r31
	li r4, 0x3
	bl partyChgRunMode
	li r3, 0x1
	@4:
	psq_l f31, 0x18(r1), 0, 0
	lwz r0, 0x24(r1)
	lfd f31, 0x10(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void driveParty(PartyEntry* party) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	lis r4, vec3_802ccd30@ha
	stw r0, 0x44(r1)
	stw r31, 0x3c(r1)
	addi r31, r4, vec3_802ccd30@l
	stw r30, 0x38(r1)
	mr r30, r3
	stw r29, 0x34(r1)
	stw r28, 0x30(r1)
	lwz r3, 0x160(r3)
	lfs f0, 0x198(r3)
	stfs f0, 0xf8(r30)
	lha r4, 0x2a(r30)
	cmpwi r4, 0x0
	ble @1
	subi r0, r4, 0x1
	sth r0, 0x2a(r30)
	@1:
	lbz r0, 0x34(r30)
	cmpwi r0, 0xe
	beq @2
	bge @3
	cmpwi r0, 0x9
	bge @3
	cmpwi r0, 0x4
	bge @2
	@3:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 2, 2
	beq @2
	bl vivianGetStatus
	cmpwi r3, 0x2
	beq @4
	mr r3, r30
	bl vivianShadow
	@4:
	mr r3, r30
	bl partyPreDisp
	b @5
	@2:
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 6, 6
	beq @6
	lwz r0, 0x0(r30)
	oris r0, r0, 0x80
	stw r0, 0x0(r30)
	b @7
	@6:
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 9, 7
	stw r0, 0x0(r30)
	@7:
	li r0, 0x0
	stw r0, 0x138(r30)
	stw r0, 0x12c(r30)
	stw r0, 0x140(r30)
	stw r0, 0x134(r30)
	stw r0, 0x130(r30)
	lbz r0, 0x34(r30)
	cmplwi r0, 0xe
	bgt @8
	lis r4, jumptable_803127F0@ha
	slwi r0, r0, 2
	addi r4, r4, jumptable_803127F0@l
	lwzx r0, r4, r0
	mtctr r0
	bctr
	@9:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 2, 2
	beq @10
	rlwinm. r0, r3, 0, 3, 3
	beq @8
	@10:
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 28, 28
	beq @11
	rlwinm r0, r3, 0, 29, 27
	li r29, 0x1
	stw r0, 0x8(r30)
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne @12
	lbz r0, 0x31(r30)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @13
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @13
	li r28, 0x1
	@13:
	cmpwi r28, 0x1
	bne @14
	li r29, 0xc
	@14:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @15
	lbz r4, 0x31(r30)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r29, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r29, r3, r0
	b @16
	@15:
	lbz r0, 0x31(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @17
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	b @16
	@17:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	@16:
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @18
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @12
	@18:
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@12:
	lfs f0, float_0_8041b100(r2)
	mr r3, r30
	li r4, 0x0
	stfs f0, 0x104(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x0(r30)
	bl partyChgMot
	@11:
	lbz r4, 0x31(r30)
	lis r3, partyDataTbl@ha
	addi r0, r3, partyDataTbl@l
	mr r3, r30
	extsb r4, r4
	mulli r4, r4, 0x28
	add r4, r0, r4
	stw r4, party_dp(r13)
	lwz r12, 0x8(r4)
	mtctr r12
	bctrl
	b @8
	@19:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 2, 2
	beq @20
	rlwinm. r0, r3, 0, 3, 3
	beq @8
	@20:
	mr r3, r30
	bl unk_800c7c98
	b @8
	@21:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 2, 2
	beq @22
	rlwinm. r0, r3, 0, 3, 3
	beq @8
	@22:
	lbz r4, 0x31(r30)
	lis r3, partyDataTbl@ha
	addi r0, r3, partyDataTbl@l
	mr r3, r30
	extsb r4, r4
	mulli r4, r4, 0x28
	add r4, r0, r4
	stw r4, party_dp(r13)
	lwz r12, 0x8(r4)
	mtctr r12
	bctrl
	b @8
	@23:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 2, 2
	beq @24
	rlwinm. r0, r3, 0, 3, 3
	beq @8
	@24:
	mr r3, r30
	bl partyForceWalk
	b @8
	@25:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 2, 2
	beq @26
	rlwinm. r0, r3, 0, 3, 3
	beq @8
	@26:
	lbz r4, 0x31(r30)
	lis r3, partyDataTbl@ha
	addi r0, r3, partyDataTbl@l
	extsb r4, r4
	mr r3, r30
	mulli r4, r4, 0x28
	add r4, r0, r4
	stw r4, party_dp(r13)
	lwz r0, 0x0(r30)
	lwz r12, 0xc(r4)
	ori r0, r0, 0x100
	stw r0, 0x0(r30)
	mtctr r12
	bctrl
	b @8
	@27:
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 28, 28
	beq @28
	rlwinm r0, r3, 0, 29, 27
	stw r0, 0x8(r30)
	lwz r5, 0x160(r30)
	lhz r0, 0x2e(r5)
	cmplwi r0, 0x16
	beq @29
	cmplwi r0, 0x18
	beq @29
	cmplwi r0, 0x19
	bne @30
	@29:
	li r0, 0x1e
	stb r0, 0x38(r30)
	b @31
	@30:
	lbz r0, 0x34(r30)
	cmplwi r0, 0x4
	beq @32
	cmplwi r0, 0x5
	bne @33
	@32:
	lwz r3, 0x4(r30)
	li r0, 0x0
	ori r3, r3, 0x10
	stw r3, 0x4(r30)
	lwz r4, 0xd8(r31)
	lwz r3, 0xdc(r31)
	stw r4, 0x70(r30)
	stw r3, 0x74(r30)
	lwz r3, 0xe0(r31)
	stw r3, 0x78(r30)
	stb r0, 0x38(r30)
	lfs f0, 0x1a8(r5)
	stfs f0, 0x110(r30)
	lfs f0, 0x1a8(r5)
	stfs f0, 0x10c(r30)
	lwz r3, 0x8c(r5)
	lwz r0, 0x90(r5)
	stw r3, 0x58(r30)
	stw r0, 0x5c(r30)
	lwz r0, 0x94(r5)
	stw r0, 0x60(r30)
	lwz r3, 0x58(r30)
	lwz r0, 0x5c(r30)
	stw r3, 0xb8(r30)
	stw r0, 0xbc(r30)
	lwz r0, 0x60(r30)
	stw r0, 0xc0(r30)
	b @31
	@33:
	cmplwi r0, 0x7
	bne @34
	lwz r4, 0xe4(r31)
	li r0, 0x14
	lwz r3, 0xe8(r31)
	stw r4, 0x70(r30)
	stw r3, 0x74(r30)
	lwz r3, 0xec(r31)
	stw r3, 0x78(r30)
	stb r0, 0x38(r30)
	lfs f0, 0x1a8(r5)
	stfs f0, 0x110(r30)
	lfs f0, 0x1a8(r5)
	stfs f0, 0x10c(r30)
	b @31
	@34:
	lwz r4, 0xf0(r31)
	li r0, 0xa
	lwz r3, 0xf4(r31)
	stw r4, 0x70(r30)
	stw r3, 0x74(r30)
	lwz r3, 0xf8(r31)
	stw r3, 0x78(r30)
	stb r0, 0x38(r30)
	lfs f0, 0x1a8(r5)
	stfs f0, 0x110(r30)
	lfs f0, 0x1a8(r5)
	stfs f0, 0x10c(r30)
	lwz r3, 0x8c(r5)
	lwz r0, 0x90(r5)
	stw r3, 0x58(r30)
	stw r0, 0x5c(r30)
	lwz r0, 0x94(r5)
	stw r0, 0x60(r30)
	lwz r3, 0x58(r30)
	lwz r0, 0x5c(r30)
	stw r3, 0xb8(r30)
	stw r0, 0xbc(r30)
	lwz r0, 0x60(r30)
	stw r0, 0xc0(r30)
	@31:
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x0(r30)
	@28:
	mr r3, r30
	bl partyHelloMain
	b @8
	@35:
	lbz r4, 0x31(r30)
	lis r3, partyDataTbl@ha
	addi r0, r3, partyDataTbl@l
	mr r3, r30
	extsb r4, r4
	mulli r4, r4, 0x28
	add r4, r0, r4
	stw r4, party_dp(r13)
	lwz r12, 0x14(r4)
	mtctr r12
	bctrl
	b @8
	@36:
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 28, 28
	beq @37
	rlwinm r0, r3, 0, 29, 27
	mr r3, r30
	stw r0, 0x8(r30)
	bl partyDokanInit
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x0(r30)
	@37:
	mr r3, r30
	bl partyDokanMain
	b @8
	@38:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 2, 2
	beq @39
	rlwinm. r0, r3, 0, 3, 3
	beq @8
	@39:
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 28, 28
	beq @40
	rlwinm r3, r3, 0, 29, 27
	li r0, 0x0
	stw r3, 0x8(r30)
	mr r3, r30
	stb r0, 0x38(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x0(r30)
	bl L_partyForceSlitOff
	@40:
	mr r3, r30
	bl partyRideMain
	b @8
	@41:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 2, 2
	beq @42
	rlwinm. r0, r3, 0, 3, 3
	beq @8
	@42:
	lwz r3, 0x8(r30)
	rlwinm. r0, r3, 0, 28, 28
	beq @43
	rlwinm r3, r3, 0, 29, 27
	li r0, 0x0
	stw r3, 0x8(r30)
	stb r0, 0x38(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x0(r30)
	@43:
	mr r3, r30
	bl partyRideYoshiMain
	b @8
	@44:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 2, 2
	beq @45
	rlwinm. r0, r3, 0, 3, 3
	beq @8
	@45:
	mr r3, r30
	bl party_damage_return
	b @8
	@46:
	lwz r4, 0x8(r30)
	rlwinm. r0, r4, 0, 28, 28
	beq @47
	rlwinm r0, r4, 0, 29, 27
	stw r0, 0x8(r30)
	@47:
	lbz r0, 0x2f(r30)
	li r6, -0x1
	lbz r8, 0x31(r30)
	li r5, 0x0
	extsb r0, r0
	la r4, partyPtrTbl(r13)
	add r7, r3, r0
	stb r8, 0x243(r7)
	lbz r0, 0x2f(r30)
	extsb r0, r0
	add r3, r3, r0
	stb r6, 0x241(r3)
	lbz r0, 0x2f(r30)
	extsb r0, r0
	slwi r0, r0, 2
	stwx r5, r4, r0
	lwz r3, 0xc(r30)
	bl animPoseRelease
	mr r4, r30
	li r3, 0x0
	bl __memFree
	b @5
	@8:
	mr r3, r30
	bl party_kemuri
	lwz r7, 0x58(r30)
	addi r3, r1, 0x14
	lwz r0, 0x5c(r30)
	addi r4, r1, 0x10
	addi r5, r1, 0xc
	addi r6, r1, 0x8
	stw r7, 0x14(r1)
	stw r0, 0x18(r1)
	lwz r0, 0x60(r30)
	stw r0, 0x1c(r1)
	bl marioGetScreenPos
	lfs f1, 0x10(r1)
	lfs f0, 0xc(r1)
	fctiwz f1, f1
	fctiwz f0, f0
	stfd f1, 0x20(r1)
	stfd f0, 0x28(r1)
	lwz r3, 0x24(r1)
	lwz r4, 0x2c(r1)
	bl marioChkInScreen
	cmpwi r3, 0x0
	beq @48
	lwz r0, 0x4(r30)
	rlwinm r0, r0, 0, 9, 7
	stw r0, 0x4(r30)
	b @49
	@48:
	lwz r0, 0x4(r30)
	oris r0, r0, 0x80
	stw r0, 0x4(r30)
	@49:
	lwz r4, 0xcc(r31)
	mr r3, r30
	lwz r0, 0xd0(r31)
	stw r4, 0xac(r30)
	stw r0, 0xb0(r30)
	lwz r0, 0xd4(r31)
	stw r0, 0xb4(r30)
	bl partyPreDisp
	@5:
	lwz r0, 0x44(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	lwz r29, 0x34(r1)
	lwz r28, 0x30(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

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
	beq @1
	cmpwi r3, 0x0
	blt @2
	b @3
	@2:
	mr r4, r3
	@3:
	lwz r0, 0x0(r4)
	clrlwi. r0, r0, 31
	beq @1
	li r3, 0x1
	@1:
	addi r4, r31, 0x4
	li r0, 0x1
	lwz r4, 0x0(r4)
	cmplwi r4, 0x0
	beq @4
	cmpwi r0, 0x0
	blt @5
	b @6
	@5:
	li r4, 0x0
	@6:
	lwz r0, 0x0(r4)
	clrlwi. r0, r0, 31
	beq @4
	addi r3, r3, 0x1
	@4:
	cmpwi r3, 0x0
	beq @7
	bl unk_8013be14
	li r30, 0x0
	@8:
	lwz r29, 0x0(r31)
	cmplwi r29, 0x0
	beq @9
	lwz r0, 0x0(r29)
	clrlwi. r0, r0, 31
	beq @9
	bl marioBgmodeChk
	cmpwi r3, 0x1
	beq @9
	mr r3, r29
	bl driveParty
	@9:
	addi r30, r30, 0x1
	addi r31, r31, 0x4
	cmpwi r30, 0x2
	blt @8
	@7:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void unk_800ba2dc(PartyEntry* party) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r4, vec3_802ccd30@ha
	stw r0, 0x24(r1)
	addi r5, r4, vec3_802ccd30@l
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lbz r6, 0x34(r3)
	lbz r0, 0x35(r3)
	cmplw r6, r0
	beq @1
	cmplwi r6, 0x4
	bne @2
	lwz r6, 0x160(r31)
	lwz r4, 0x114(r5)
	lwz r0, 0x118(r5)
	stw r4, 0x70(r31)
	stw r0, 0x74(r31)
	lwz r0, 0x11c(r5)
	stw r0, 0x78(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r31)
	lfs f0, 0x19c(r6)
	stfs f0, 0xfc(r31)
	lfs f0, 0x1a0(r6)
	stfs f0, 0x100(r31)
	lfs f0, 0x1ac(r6)
	stfs f0, 0x110(r31)
	lfs f0, 0x1a8(r6)
	stfs f0, 0x10c(r31)
	bl partyClearJumpPara
	lwz r0, 0x4(r31)
	li r30, 0x1
	rlwinm. r0, r0, 0, 30, 30
	bne @3
	lbz r0, 0x31(r31)
	li r29, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @4
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @4
	li r29, 0x1
	@4:
	cmpwi r29, 0x1
	bne @5
	li r30, 0xc
	@5:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @6
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @7
	@6:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @8
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @7
	@8:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@7:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @9
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @3
	@9:
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@3:
	lwz r3, 0x4(r31)
	cmplwi r31, 0x0
	li r0, 0x1
	rlwinm r3, r3, 0, 28, 26
	stw r3, 0x4(r31)
	stb r0, 0x34(r31)
	beq @10
	lbz r0, 0x34(r31)
	cmplwi r0, 0x3
	bne @10
	lbz r0, 0x31(r31)
	lis r3, partyDataTbl@ha
	addi r3, r3, partyDataTbl@l
	extsb r0, r0
	mulli r0, r0, 0x28
	add r3, r3, r0
	lwz r12, 0x10(r3)
	cmplwi r12, 0x0
	beq @10
	mr r3, r31
	mtctr r12
	bctrl
	@10:
	mr r3, r31
	li r4, 0x0
	bl partyChgMot
	b @1
	@2:
	cmplwi r6, 0xb
	bne @11
	lwz r6, 0x160(r31)
	lwz r4, 0x18c(r5)
	lwz r0, 0x190(r5)
	stw r4, 0x70(r31)
	stw r0, 0x74(r31)
	lwz r0, 0x194(r5)
	stw r0, 0x78(r31)
	lwz r4, 0x198(r5)
	lwz r0, 0x19c(r5)
	stw r4, 0x7c(r31)
	stw r0, 0x80(r31)
	lwz r0, 0x1a0(r5)
	stw r0, 0x84(r31)
	lfs f0, 0x19c(r6)
	stfs f0, 0xfc(r31)
	lfs f0, 0x1a0(r6)
	stfs f0, 0x100(r31)
	lfs f0, 0x1ac(r6)
	stfs f0, 0x110(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 16, 12
	stw r0, 0x0(r31)
	bl partyClearJumpPara
	lwz r0, 0x4(r31)
	li r30, 0x1
	rlwinm. r0, r0, 0, 30, 30
	bne @12
	lbz r0, 0x31(r31)
	li r29, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @13
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @13
	li r29, 0x1
	@13:
	cmpwi r29, 0x1
	bne @14
	li r30, 0xc
	@14:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @15
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @16
	@15:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @17
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @16
	@17:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@16:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @18
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @12
	@18:
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@12:
	lwz r0, 0x4(r31)
	cmplwi r31, 0x0
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r31)
	lwz r0, 0x4(r31)
	clrrwi r0, r0, 1
	stw r0, 0x4(r31)
	beq @19
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x4(r31)
	@19:
	cmplwi r31, 0x0
	beq @20
	lbz r0, 0x34(r31)
	cmplwi r0, 0x3
	bne @20
	lbz r0, 0x31(r31)
	lis r3, partyDataTbl@ha
	addi r3, r3, partyDataTbl@l
	extsb r0, r0
	mulli r0, r0, 0x28
	add r3, r3, r0
	lwz r12, 0x10(r3)
	cmplwi r12, 0x0
	beq @20
	mr r3, r31
	mtctr r12
	bctrl
	@20:
	mr r3, r31
	li r4, 0x0
	bl partyChgMot
	b @1
	@11:
	cmplwi r6, 0xc
	bne @21
	cmplwi r31, 0x0
	beq @21
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x4(r31)
	@21:
	cmplwi r31, 0x0
	beq @22
	lbz r0, 0x34(r31)
	cmplwi r0, 0x3
	bne @22
	lbz r0, 0x31(r31)
	lis r3, partyDataTbl@ha
	addi r3, r3, partyDataTbl@l
	extsb r0, r0
	mulli r0, r0, 0x28
	add r3, r3, r0
	lwz r12, 0x10(r3)
	cmplwi r12, 0x0
	beq @22
	mr r3, r31
	mtctr r12
	bctrl
	@22:
	lbz r0, 0x35(r31)
	mr r3, r31
	li r4, 0x0
	stb r0, 0x34(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x8
	stw r0, 0x8(r31)
	bl partyChgMot
	@1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void N_partyForceChgRunMode(PartyEntry* party, s32 mode, s32 sub) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r5
	stw r30, 0x18(r1)
	mr r30, r4
	stw r29, 0x14(r1)
	mr r29, r3
	lbz r0, 0x34(r3)
	cmplwi r0, 0x9
	beq @1
	cmplwi r0, 0x3
	beq @1
	stb r0, 0x35(r29)
	@1:
	lbz r4, 0x34(r29)
	mr r3, r29
	mr r5, r30
	bl N__partyChgRunMode
	stb r30, 0x34(r29)
	lwz r0, 0x8(r29)
	rlwinm r0, r0, 0, 29, 27
	stw r0, 0x8(r29)
	stb r31, 0x38(r29)
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void partyChgRunMode(PartyEntry* party, s32 mode) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r4
	stw r30, 0x8(r1)
	mr r30, r3
	lbz r0, 0x34(r3)
	cmplwi r0, 0x9
	beq @1
	cmplwi r0, 0x3
	beq @1
	stb r0, 0x35(r30)
	@1:
	lbz r4, 0x34(r30)
	mr r3, r30
	mr r5, r31
	bl N__partyChgRunMode
	stb r31, 0x34(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x8
	stw r0, 0x8(r30)
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void N__partyChgRunMode(PartyEntry* party, s32 prev, s32 mode) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r6, vec3_802ccd30@ha
	cmpwi r4, 0x4
	stw r0, 0x24(r1)
	addi r6, r6, vec3_802ccd30@l
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	beq @1
	bge @2
	cmpwi r4, 0x3
	bge @3
	cmpwi r4, 0x1
	bge @4
	b @5
	@2:
	cmpwi r4, 0xc
	beq @6
	bge @5
	cmpwi r4, 0xb
	bge @7
	b @5
	@7:
	cmpwi r5, 0x8
	beq @5
	lwz r5, 0x160(r31)
	lwz r4, 0x18c(r6)
	lwz r0, 0x190(r6)
	stw r4, 0x70(r31)
	stw r0, 0x74(r31)
	lwz r0, 0x194(r6)
	stw r0, 0x78(r31)
	lwz r4, 0x198(r6)
	lwz r0, 0x19c(r6)
	stw r4, 0x7c(r31)
	stw r0, 0x80(r31)
	lwz r0, 0x1a0(r6)
	stw r0, 0x84(r31)
	lfs f0, 0x19c(r5)
	stfs f0, 0xfc(r31)
	lfs f0, 0x1a0(r5)
	stfs f0, 0x100(r31)
	lfs f0, 0x1ac(r5)
	stfs f0, 0x110(r31)
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 16, 12
	stw r0, 0x0(r31)
	bl partyClearJumpPara
	lwz r0, 0x4(r31)
	li r30, 0x1
	rlwinm. r0, r0, 0, 30, 30
	bne @8
	lbz r0, 0x31(r31)
	li r29, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @9
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @9
	li r29, 0x1
	@9:
	cmpwi r29, 0x1
	bne @10
	li r30, 0xc
	@10:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @11
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @12
	@11:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @13
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @12
	@13:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@12:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @14
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @8
	@14:
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@8:
	lwz r0, 0x4(r31)
	cmplwi r31, 0x0
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r31)
	lwz r0, 0x4(r31)
	clrrwi r0, r0, 1
	stw r0, 0x4(r31)
	beq @5
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x4(r31)
	b @5
	@1:
	lwz r5, 0x160(r31)
	lwz r4, 0x114(r6)
	lwz r0, 0x118(r6)
	stw r4, 0x70(r31)
	stw r0, 0x74(r31)
	lwz r0, 0x11c(r6)
	stw r0, 0x78(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x4(r31)
	lfs f0, 0x19c(r5)
	stfs f0, 0xfc(r31)
	lfs f0, 0x1a0(r5)
	stfs f0, 0x100(r31)
	lfs f0, 0x1ac(r5)
	stfs f0, 0x110(r31)
	lfs f0, 0x1a8(r5)
	stfs f0, 0x10c(r31)
	bl partyClearJumpPara
	lwz r0, 0x4(r31)
	li r30, 0x1
	rlwinm. r0, r0, 0, 30, 30
	bne @15
	lbz r0, 0x31(r31)
	li r29, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @16
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @16
	li r29, 0x1
	@16:
	cmpwi r29, 0x1
	bne @17
	li r30, 0xc
	@17:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @18
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @19
	@18:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @20
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @19
	@20:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@19:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @21
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @15
	@21:
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@15:
	lwz r3, 0x4(r31)
	li r0, 0x1
	rlwinm r3, r3, 0, 28, 26
	stw r3, 0x4(r31)
	stb r0, 0x34(r31)
	b @5
	@6:
	cmplwi r31, 0x0
	beq @5
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x4(r31)
	b @5
	@3:
	lbz r0, 0x31(r31)
	lis r4, partyDataTbl@ha
	addi r4, r4, partyDataTbl@l
	extsb r0, r0
	mulli r0, r0, 0x28
	add r4, r4, r0
	lwz r12, 0x10(r4)
	cmplwi r12, 0x0
	beq @5
	mtctr r12
	bctrl
	b @5
	@4:
	bl L_partyForceSlitOff
	@5:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void partyUsePost(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	cmplwi r3, 0x0
	stw r0, 0x14(r1)
	beq @1
	lbz r0, 0x34(r3)
	cmplwi r0, 0x3
	bne @1
	lbz r0, 0x31(r3)
	lis r4, partyDataTbl@ha
	addi r4, r4, partyDataTbl@l
	extsb r0, r0
	mulli r0, r0, 0x28
	add r4, r4, r0
	lwz r12, 0x10(r4)
	cmplwi r12, 0x0
	beq @1
	mtctr r12
	bctrl
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void partyReInit(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r3, vec3_802ccd30@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	addi r31, r3, vec3_802ccd30@l
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	bl marioGetExtraPartyId
	cmpwi r3, 0x0
	blt @1
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r30, r3, r0
	b @2
	@1:
	li r30, 0x0
	@2:
	cmplwi r30, 0x0
	beq @3
	li r3, 0xd
	li r0, 0x0
	stw r3, 0x0(r30)
	stw r0, 0x4(r30)
	lwz r28, 0xc(r30)
	cmpwi r28, 0x0
	blt @4
	mr r3, r28
	li r4, -0x1
	bl animPoseSetMaterialFlagOff
	mr r3, r28
	li r4, 0x2
	bl animPoseSetMaterialLightFlagOn
	@4:
	li r0, 0x0
	stb r0, 0x37(r30)
	lwz r0, 0x1c(r30)
	cmplwi r0, 0x0
	beq @5
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
	blt @5
	bl animPaperPoseRelease
	li r0, -0x1
	stw r0, 0x14(r30)
	@5:
	li r28, 0x0
	li r29, 0x1
	stw r28, 0x130(r30)
	stw r28, 0x12c(r30)
	stw r28, 0x148(r30)
	stw r28, 0x138(r30)
	stw r28, 0x13c(r30)
	stw r28, 0x134(r30)
	stw r28, 0x140(r30)
	stw r28, 0x144(r30)
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	beq @6
	lwz r29, 0x18(r30)
	b @7
	@6:
	lbz r0, 0x31(r30)
	extsb r3, r0
	cmpwi r3, 0x8
	bge @8
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @8
	li r28, 0x1
	@8:
	cmpwi r28, 0x1
	bne @9
	li r29, 0xc
	@9:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @10
	lbz r4, 0x31(r30)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r29, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r29, r3, r0
	b @11
	@10:
	lbz r0, 0x31(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @12
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	b @11
	@12:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	@11:
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @13
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	bne @13
	b @7
	@13:
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@7:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne @14
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @15
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @14
	@15:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @14
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@14:
	mr r3, r30
	li r4, 0x2
	bl partyChgRunMode
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	li r0, -0x1
	stw r0, 0x168(r30)
	lwz r3, 0xb4(r31)
	lwz r0, 0xb8(r31)
	stw r3, 0x70(r30)
	stw r0, 0x74(r30)
	lwz r0, 0xbc(r31)
	stw r0, 0x78(r30)
	@3:
	bl marioGetPartyId
	cmpwi r3, 0x0
	blt @16
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r30, r3, r0
	b @17
	@16:
	li r30, 0x0
	@17:
	cmplwi r30, 0x0
	beq @18
	lwz r4, 0x4(r30)
	li r3, 0x1
	li r0, 0x0
	stw r3, 0x0(r30)
	rlwinm r29, r4, 0, 16, 16
	stw r0, 0x4(r30)
	stb r0, 0x37(r30)
	bl marioGetCamId
	cmplwi r30, 0x0
	stw r3, 0x164(r30)
	beq @19
	lwz r28, 0xc(r30)
	cmpwi r28, 0x0
	blt @20
	mr r3, r28
	li r4, -0x1
	bl animPoseSetMaterialFlagOff
	mr r3, r28
	li r4, 0x2
	bl animPoseSetMaterialLightFlagOn
	@20:
	lwz r0, 0x1c(r30)
	cmplwi r0, 0x0
	beq @21
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
	blt @21
	bl animPaperPoseRelease
	li r0, -0x1
	stw r0, 0x14(r30)
	@21:
	li r0, 0x0
	stw r0, 0x130(r30)
	stw r0, 0x12c(r30)
	stw r0, 0x148(r30)
	stw r0, 0x138(r30)
	stw r0, 0x13c(r30)
	stw r0, 0x134(r30)
	stw r0, 0x140(r30)
	stw r0, 0x144(r30)
	lwz r3, 0xc0(r31)
	lwz r0, 0xc4(r31)
	stw r3, 0x70(r30)
	stw r0, 0x74(r30)
	lwz r0, 0xc8(r31)
	stw r0, 0x78(r30)
	@19:
	bl partyClearFootmark
	cmpwi r29, 0x0
	beq @22
	lbz r0, 0x31(r30)
	cmpwi r0, 0x4
	beq @23
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @24
	lwz r3, party_dp(r13)
	lwz r29, 0x0(r3)
	b @25
	@24:
	addi r29, r31, 0x1bc
	b @25
	@23:
	li r3, 0x4
	bl pouchGetPartyColor
	lwz r0, 0x4(r30)
	slwi r4, r3, 2
	la r3, yoshigroup(r13)
	rlwinm. r0, r0, 0, 16, 16
	lwzx r29, r3, r4
	beq @25
	addi r29, r31, 0x1bc
	@25:
	lwz r3, 0xc(r30)
	cmpwi r3, 0x0
	blt @26
	bl animPoseRelease
	@26:
	mr r3, r29
	li r4, 0x2
	bl animPoseEntry
	stw r3, 0xc(r30)
	@22:
	lbz r0, 0x31(r30)
	cmpwi r0, 0x4
	bne @27
	lbz r0, 0x34(r30)
	cmplwi r0, 0x3
	beq @18
	@27:
	bl marioGetPtr
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 9, 9
	bne @28
	lwz r0, 0x4(r30)
	li r29, 0x1
	rlwinm. r0, r0, 0, 30, 30
	beq @29
	lwz r29, 0x18(r30)
	b @30
	@29:
	lbz r0, 0x31(r30)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @31
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @31
	li r28, 0x1
	@31:
	cmpwi r28, 0x1
	bne @32
	li r29, 0xc
	@32:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @33
	lbz r4, 0x31(r30)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r29, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r29, r3, r0
	b @34
	@33:
	lbz r0, 0x31(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @35
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	b @34
	@35:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	@34:
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @36
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	bne @36
	b @30
	@36:
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@30:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne @37
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @38
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @37
	@38:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @37
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@37:
	mr r3, r30
	li r4, 0x2
	bl partyChgRunMode
	mr r3, r30
	li r4, 0x0
	bl partyChgMot
	b @39
	@28:
	lwz r0, 0x4(r30)
	li r29, 0x1
	rlwinm. r0, r0, 0, 30, 30
	beq @40
	lwz r29, 0x18(r30)
	b @41
	@40:
	lbz r0, 0x31(r30)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @42
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @42
	li r28, 0x1
	@42:
	cmpwi r28, 0x1
	bne @43
	li r29, 0xc
	@43:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @44
	lbz r4, 0x31(r30)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r29, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r29, r3, r0
	b @45
	@44:
	lbz r0, 0x31(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @46
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	b @45
	@46:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	@45:
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @47
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	bne @47
	b @41
	@47:
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@41:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne @48
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @49
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @48
	@49:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @48
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@48:
	mr r3, r30
	li r4, 0x2
	bl partyChgRunMode
	li r3, 0x6
	li r0, 0x0
	stb r3, 0x3b(r30)
	stb r0, 0x38(r30)
	lwz r0, 0x0(r30)
	ori r0, r0, 0x8000
	stw r0, 0x0(r30)
	@39:
	lbz r0, 0x31(r30)
	cmpwi r0, 0x7
	bne @50
	mr r3, r30
	bl chuchu_reinit
	@50:
	bl unk_8014c47c
	@18:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void partyInit(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	la r3, partyPtrTbl(r13)
	li r4, 0x0
	stw r0, 0x14(r1)
	li r5, 0x8
	bl memset
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 partyEntry2Pos(s32 memberId, f32 x, f32 y, f32 z) {
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
	stmw r27, 0x1c(r1)
	fmr f29, f1
	mr r27, r3
	fmr f30, f2
	fmr f31, f3
	bl marioGetPtr
	la r28, partyPtrTbl(r13)
	mr r29, r3
	lwz r0, 0x4(r28)
	cmplwi r0, 0x0
	bne @1
	li r3, 0x0
	li r4, 0x188
	bl __memAlloc
	stw r3, 0x4(r28)
	li r4, 0x0
	li r5, 0x188
	bl memset
	li r31, 0x1
	b @2
	@1:
	li r31, -0x1
	@2:
	cmpwi r31, 0x0
	bge @3
	li r3, -0x1
	b @4
	@3:
	blt @5
	slwi r0, r31, 2
	la r3, partyPtrTbl(r13)
	lwzx r30, r3, r0
	b @6
	@5:
	li r30, 0x0
	@6:
	mr r3, r30
	li r4, 0x0
	li r5, 0x188
	bl memset
	bl marioGetCamId
	stw r3, 0x164(r30)
	li r3, -0x1
	li r0, 0x9
	cmpwi r31, 0x1
	stw r3, 0xc(r30)
	stw r3, 0x10(r30)
	stw r3, 0x14(r30)
	stw r0, 0x0(r30)
	stb r31, 0x2f(r30)
	stw r29, 0x160(r30)
	stb r27, 0x31(r30)
	bne @7
	lwz r0, 0x0(r30)
	ori r0, r0, 0x4
	stw r0, 0x0(r30)
	@7:
	mulli r4, r27, 0x28
	lis r3, partyDataTbl@ha
	addi r0, r3, partyDataTbl@l
	add r3, r0, r4
	stw r3, party_dp(r13)
	lbz r0, 0x31(r30)
	cmpwi r0, 0x4
	beq @8
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @9
	lwz r29, 0x0(r3)
	b @10
	@9:
	lis r3, str_802CCEEC@ha
	addi r29, r3, str_802CCEEC@l
	b @10
	@8:
	li r3, 0x4
	bl pouchGetPartyColor
	lwz r0, 0x4(r30)
	slwi r4, r3, 2
	la r3, yoshigroup(r13)
	rlwinm. r0, r0, 0, 16, 16
	lwzx r29, r3, r4
	beq @10
	lis r3, str_802CCEEC@ha
	addi r29, r3, str_802CCEEC@l
	@10:
	lwz r3, 0xc(r30)
	cmpwi r3, 0x0
	blt @11
	bl animPoseRelease
	@11:
	mr r3, r29
	li r4, 0x2
	bl animPoseEntry
	stw r3, 0xc(r30)
	lwz r3, 0xc(r30)
	bl animPosePeraOff
	lwz r29, 0x160(r30)
	bl marioAnimeId
	slwi r0, r3, 2
	add r3, r29, r0
	lwz r3, 0x228(r3)
	bl animPoseGetMaterialFlag
	mr r4, r3
	lwz r3, 0xc(r30)
	bl animPoseSetMaterialFlagOn
	bl marioAnimeId
	slwi r0, r3, 2
	add r3, r29, r0
	lwz r3, 0x228(r3)
	bl animPoseGetMaterialLightFlag
	mr r4, r3
	lwz r3, 0xc(r30)
	bl animPoseSetMaterialLightFlagOn
	lwz r0, 0x4(r30)
	li r29, 0x1
	rlwinm. r0, r0, 0, 30, 30
	beq @12
	lwz r29, 0x18(r30)
	b @13
	@12:
	lbz r0, 0x31(r30)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @14
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @14
	li r28, 0x1
	@14:
	cmpwi r28, 0x1
	bne @15
	li r29, 0xc
	@15:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @16
	lbz r4, 0x31(r30)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r29, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r29, r3, r0
	b @17
	@16:
	lbz r0, 0x31(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @18
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	b @17
	@18:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	@17:
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @19
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	bne @19
	b @13
	@19:
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@13:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne @20
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @21
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @20
	@21:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @20
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@20:
	li r0, 0x0
	mr r3, r30
	stw r0, 0x1c(r30)
	lwz r4, party_dp(r13)
	lwz r12, 0x4(r4)
	mtctr r12
	bctrl
	mr r3, r30
	li r4, 0x2
	bl partyChgRunMode
	lis r3, vec3_802ccdd8@ha
	lfs f0, float_1_8041b0e8(r2)
	addi r5, r3, vec3_802ccdd8@l
	mr r3, r31
	lwz r0, 0x0(r5)
	lwz r4, 0x4(r5)
	stw r0, 0x8(r1)
	lwz r0, 0x8(r5)
	stw r4, 0xc(r1)
	stfs f29, 0x8(r1)
	stw r0, 0x10(r1)
	lwz r0, 0x8(r1)
	stfs f30, 0xc(r1)
	stfs f31, 0x10(r1)
	lwz r4, 0xc(r1)
	stw r0, 0x58(r30)
	lwz r0, 0x10(r1)
	stw r4, 0x5c(r30)
	stw r0, 0x60(r30)
	lwz r4, 0x58(r30)
	lwz r0, 0x5c(r30)
	stw r4, 0xb8(r30)
	stw r0, 0xbc(r30)
	lwz r0, 0x60(r30)
	stw r0, 0xc0(r30)
	stfs f0, 0x70(r30)
	stfs f0, 0x74(r30)
	stfs f0, 0x78(r30)
	@4:
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	lmw r27, 0x1c(r1)
	lwz r0, 0x64(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm s32 partyEntry2Hello(s32 memberId) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	bl marioGetPtr
	la r28, partyPtrTbl(r13)
	mr r29, r3
	lwz r0, 0x4(r28)
	cmplwi r0, 0x0
	bne @1
	li r3, 0x0
	li r4, 0x188
	bl __memAlloc
	stw r3, 0x4(r28)
	li r4, 0x0
	li r5, 0x188
	bl memset
	li r31, 0x1
	b @2
	@1:
	li r31, -0x1
	@2:
	cmpwi r31, 0x0
	bge @3
	li r3, -0x1
	b @4
	@3:
	blt @5
	slwi r0, r31, 2
	la r3, partyPtrTbl(r13)
	lwzx r30, r3, r0
	b @6
	@5:
	li r30, 0x0
	@6:
	mr r3, r30
	li r4, 0x0
	li r5, 0x188
	bl memset
	bl marioGetCamId
	stw r3, 0x164(r30)
	li r3, -0x1
	li r0, 0x9
	cmpwi r31, 0x1
	stw r3, 0xc(r30)
	stw r3, 0x10(r30)
	stw r3, 0x14(r30)
	stw r0, 0x0(r30)
	stb r31, 0x2f(r30)
	stw r29, 0x160(r30)
	stb r27, 0x31(r30)
	bne @7
	lwz r0, 0x0(r30)
	ori r0, r0, 0x4
	stw r0, 0x0(r30)
	@7:
	mulli r4, r27, 0x28
	lis r3, partyDataTbl@ha
	addi r0, r3, partyDataTbl@l
	add r3, r0, r4
	stw r3, party_dp(r13)
	lbz r0, 0x31(r30)
	cmpwi r0, 0x4
	beq @8
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @9
	lwz r29, 0x0(r3)
	b @10
	@9:
	lis r3, str_802CCEEC@ha
	addi r29, r3, str_802CCEEC@l
	b @10
	@8:
	li r3, 0x4
	bl pouchGetPartyColor
	lwz r0, 0x4(r30)
	slwi r4, r3, 2
	la r3, yoshigroup(r13)
	rlwinm. r0, r0, 0, 16, 16
	lwzx r29, r3, r4
	beq @10
	lis r3, str_802CCEEC@ha
	addi r29, r3, str_802CCEEC@l
	@10:
	lwz r3, 0xc(r30)
	cmpwi r3, 0x0
	blt @11
	bl animPoseRelease
	@11:
	mr r3, r29
	li r4, 0x2
	bl animPoseEntry
	stw r3, 0xc(r30)
	lwz r3, 0xc(r30)
	bl animPosePeraOff
	lwz r29, 0x160(r30)
	bl marioAnimeId
	slwi r0, r3, 2
	add r3, r29, r0
	lwz r3, 0x228(r3)
	bl animPoseGetMaterialFlag
	mr r4, r3
	lwz r3, 0xc(r30)
	bl animPoseSetMaterialFlagOn
	bl marioAnimeId
	slwi r0, r3, 2
	add r3, r29, r0
	lwz r3, 0x228(r3)
	bl animPoseGetMaterialLightFlag
	mr r4, r3
	lwz r3, 0xc(r30)
	bl animPoseSetMaterialLightFlagOn
	lwz r0, 0x4(r30)
	li r29, 0x1
	rlwinm. r0, r0, 0, 30, 30
	beq @12
	lwz r29, 0x18(r30)
	b @13
	@12:
	lbz r0, 0x31(r30)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @14
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @14
	li r28, 0x1
	@14:
	cmpwi r28, 0x1
	bne @15
	li r29, 0xc
	@15:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @16
	lbz r4, 0x31(r30)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r29, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r29, r3, r0
	b @17
	@16:
	lbz r0, 0x31(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @18
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	b @17
	@18:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	@17:
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @19
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	bne @19
	b @13
	@19:
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@13:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	bne @20
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @21
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @20
	@21:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @20
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@20:
	li r0, 0x0
	mr r3, r30
	stw r0, 0x1c(r30)
	lwz r4, party_dp(r13)
	lwz r12, 0x4(r4)
	mtctr r12
	bctrl
	mr r3, r30
	li r4, 0x4
	bl partyChgRunMode
	mr r3, r31
	@4:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 partyEntry2(s32 memberId) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r28, r3
	bl marioGetPtr
	la r27, partyPtrTbl(r13)
	mr r31, r3
	lwz r0, 0x4(r27)
	cmplwi r0, 0x0
	bne @1
	li r3, 0x0
	li r4, 0x188
	bl __memAlloc
	stw r3, 0x4(r27)
	li r4, 0x0
	li r5, 0x188
	bl memset
	li r30, 0x1
	b @2
	@1:
	li r30, -0x1
	@2:
	cmpwi r30, 0x0
	bge @3
	li r3, -0x1
	b @4
	@3:
	blt @5
	slwi r0, r30, 2
	la r3, partyPtrTbl(r13)
	lwzx r29, r3, r0
	b @6
	@5:
	li r29, 0x0
	@6:
	mr r3, r29
	li r4, 0x0
	li r5, 0x188
	bl memset
	bl marioGetCamId
	stw r3, 0x164(r29)
	li r3, -0x1
	li r0, 0x9
	cmpwi r30, 0x1
	stw r3, 0xc(r29)
	stw r3, 0x10(r29)
	stw r3, 0x14(r29)
	stw r0, 0x0(r29)
	stb r30, 0x2f(r29)
	stw r31, 0x160(r29)
	stb r28, 0x31(r29)
	bne @7
	lwz r0, 0x0(r29)
	ori r0, r0, 0x4
	stw r0, 0x0(r29)
	@7:
	mulli r4, r28, 0x28
	lis r3, partyDataTbl@ha
	addi r0, r3, partyDataTbl@l
	add r3, r0, r4
	stw r3, party_dp(r13)
	lbz r0, 0x31(r29)
	cmpwi r0, 0x4
	beq @8
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @9
	lwz r28, 0x0(r3)
	b @10
	@9:
	lis r3, str_802CCEEC@ha
	addi r28, r3, str_802CCEEC@l
	b @10
	@8:
	li r3, 0x4
	bl pouchGetPartyColor
	lwz r0, 0x4(r29)
	slwi r4, r3, 2
	la r3, yoshigroup(r13)
	rlwinm. r0, r0, 0, 16, 16
	lwzx r28, r3, r4
	beq @10
	lis r3, str_802CCEEC@ha
	addi r28, r3, str_802CCEEC@l
	@10:
	lwz r3, 0xc(r29)
	cmpwi r3, 0x0
	blt @11
	bl animPoseRelease
	@11:
	mr r3, r28
	li r4, 0x2
	bl animPoseEntry
	stw r3, 0xc(r29)
	lwz r3, 0xc(r29)
	bl animPosePeraOff
	lwz r28, 0x160(r29)
	bl marioAnimeId
	slwi r0, r3, 2
	add r3, r28, r0
	lwz r3, 0x228(r3)
	bl animPoseGetMaterialFlag
	mr r4, r3
	lwz r3, 0xc(r29)
	bl animPoseSetMaterialFlagOn
	bl marioAnimeId
	slwi r0, r3, 2
	add r3, r28, r0
	lwz r3, 0x228(r3)
	bl animPoseGetMaterialLightFlag
	mr r4, r3
	lwz r3, 0xc(r29)
	bl animPoseSetMaterialLightFlagOn
	lwz r0, 0x4(r29)
	li r28, 0x1
	rlwinm. r0, r0, 0, 30, 30
	beq @12
	lwz r28, 0x18(r29)
	b @13
	@12:
	lbz r0, 0x31(r29)
	li r27, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @14
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @14
	li r27, 0x1
	@14:
	cmpwi r27, 0x1
	bne @15
	li r28, 0xc
	@15:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @16
	lbz r4, 0x31(r29)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r28, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r28, r3, r0
	b @17
	@16:
	lbz r0, 0x31(r29)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @18
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r28, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r28, r3, r0
	b @17
	@18:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r28, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r28, r3, r0
	@17:
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @19
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @19
	b @13
	@19:
	stw r28, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@13:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 30, 30
	bne @20
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @21
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	beq @20
	@21:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @20
	stw r28, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@20:
	li r0, 0x0
	mr r3, r29
	stw r0, 0x1c(r29)
	lwz r4, party_dp(r13)
	lwz r12, 0x4(r4)
	mtctr r12
	bctrl
	lwz r5, 0x8c(r31)
	lis r3, vec3_802ccdcc@ha
	lwz r4, 0x90(r31)
	addi r6, r3, vec3_802ccdcc@l
	li r0, 0x0
	mr r3, r30
	stw r5, 0x58(r29)
	stw r4, 0x5c(r29)
	lwz r4, 0x94(r31)
	stw r4, 0x60(r29)
	lwz r5, 0x58(r29)
	lwz r4, 0x5c(r29)
	stw r5, 0xb8(r29)
	stw r4, 0xbc(r29)
	lwz r4, 0x60(r29)
	stw r4, 0xc0(r29)
	lwz r5, 0x0(r6)
	lwz r4, 0x4(r6)
	stw r5, 0x70(r29)
	stw r4, 0x74(r29)
	lwz r4, 0x8(r6)
	stw r4, 0x78(r29)
	stb r0, 0x34(r29)
	@4:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 partyEntryMain(s32 memberId) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	bl marioGetPtr
	li r0, 0x2
	mr r31, r3
	li r30, 0x0
	la r3, partyPtrTbl(r13)
	mtctr r0
	@1:
	lwz r0, 0x0(r3)
	cmplwi r0, 0x0
	bne @2
	li r3, 0x0
	li r4, 0x188
	bl __memAlloc
	slwi r0, r30, 2
	la r4, partyPtrTbl(r13)
	stwx r3, r4, r0
	li r4, 0x0
	li r5, 0x188
	bl memset
	b @3
	@2:
	addi r3, r3, 0x4
	addi r30, r30, 0x1
	bdnz @1
	li r30, -0x1
	@3:
	cmpwi r30, 0x0
	bge @4
	li r3, -0x1
	b @5
	@4:
	blt @6
	slwi r0, r30, 2
	la r3, partyPtrTbl(r13)
	lwzx r29, r3, r0
	b @7
	@6:
	li r29, 0x0
	@7:
	mr r3, r29
	li r4, 0x0
	li r5, 0x188
	bl memset
	bl marioGetCamId
	stw r3, 0x164(r29)
	li r3, -0x1
	li r0, 0x1
	stw r3, 0xc(r29)
	stw r3, 0x10(r29)
	stw r3, 0x14(r29)
	stw r0, 0x0(r29)
	stb r30, 0x2f(r29)
	stw r31, 0x160(r29)
	stb r28, 0x31(r29)
	lbz r0, 0x243(r31)
	extsb. r0, r0
	bne @8
	lbz r0, 0x31(r29)
	stb r0, 0x243(r31)
	@8:
	cmpwi r30, 0x1
	bne @9
	lwz r0, 0x0(r29)
	ori r0, r0, 0x4
	stw r0, 0x0(r29)
	@9:
	mulli r4, r28, 0x28
	lis r3, partyDataTbl@ha
	addi r0, r3, partyDataTbl@l
	add r0, r0, r4
	stw r0, party_dp(r13)
	lwz r0, 0x0(r31)
	clrrwi. r0, r0, 31
	beq @10
	lwz r0, 0x4(r29)
	ori r0, r0, 0x8000
	stw r0, 0x4(r29)
	@10:
	lbz r0, 0x31(r29)
	cmpwi r0, 0x4
	beq @11
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @12
	lwz r3, party_dp(r13)
	lwz r28, 0x0(r3)
	b @13
	@12:
	lis r3, str_802CCEEC@ha
	addi r28, r3, str_802CCEEC@l
	b @13
	@11:
	li r3, 0x4
	bl pouchGetPartyColor
	lwz r0, 0x4(r29)
	slwi r4, r3, 2
	la r3, yoshigroup(r13)
	rlwinm. r0, r0, 0, 16, 16
	lwzx r28, r3, r4
	beq @13
	lis r3, str_802CCEEC@ha
	addi r28, r3, str_802CCEEC@l
	@13:
	lwz r3, 0xc(r29)
	cmpwi r3, 0x0
	blt @14
	bl animPoseRelease
	@14:
	mr r3, r28
	li r4, 0x2
	bl animPoseEntry
	stw r3, 0xc(r29)
	lwz r3, 0xc(r29)
	bl animPosePeraOff
	lwz r28, 0x160(r29)
	bl marioAnimeId
	slwi r0, r3, 2
	add r3, r28, r0
	lwz r3, 0x228(r3)
	bl animPoseGetMaterialFlag
	mr r4, r3
	lwz r3, 0xc(r29)
	bl animPoseSetMaterialFlagOn
	bl marioAnimeId
	slwi r0, r3, 2
	add r3, r28, r0
	lwz r3, 0x228(r3)
	bl animPoseGetMaterialLightFlag
	mr r4, r3
	lwz r3, 0xc(r29)
	bl animPoseSetMaterialLightFlagOn
	lwz r0, 0x4(r29)
	li r28, 0x1
	rlwinm. r0, r0, 0, 30, 30
	beq @15
	lwz r28, 0x18(r29)
	b @16
	@15:
	lbz r0, 0x31(r29)
	li r31, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @17
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @17
	li r31, 0x1
	@17:
	cmpwi r31, 0x1
	bne @18
	li r28, 0xc
	@18:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @19
	lbz r4, 0x31(r29)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r28, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r28, r3, r0
	b @20
	@19:
	lbz r0, 0x31(r29)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @21
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r28, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r28, r3, r0
	b @20
	@21:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r28, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r28, r3, r0
	@20:
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @22
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne @22
	b @16
	@22:
	stw r28, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@16:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 30, 30
	bne @23
	lwz r3, 0x18(r29)
	cmplwi r3, 0x0
	beq @24
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	beq @23
	@24:
	lwz r0, 0x4(r29)
	rlwinm. r0, r0, 0, 16, 16
	bne @23
	stw r28, 0x18(r29)
	li r0, 0x0
	sth r0, 0x20(r29)
	lwz r0, 0x8(r29)
	ori r0, r0, 0x2000
	stw r0, 0x8(r29)
	@23:
	li r0, 0x0
	mr r3, r29
	stw r0, 0x1c(r29)
	lwz r4, party_dp(r13)
	lwz r12, 0x4(r4)
	mtctr r12
	bctrl
	mr r3, r30
	@5:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm f32 partyGetHeight(PartyEntry* party) {
	nofralloc
	lbz r0, 0x31(r3)
	cmpwi r0, 0x4
	bne @1
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 23, 23
	beq @1
	lfs f1, float_18p5_8041b1bc(r2)
	lfs f0, 0xf0(r3)
	fadds f1, f1, f0
	blr
	@1:
	lfs f1, 0xf0(r3)
	blr
}

asm s32 yoshiSetColor(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x3e8
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl irand
	cmpwi r3, 0x96
	bge @1
	li r31, 0x0
	b @2
	@1:
	cmpwi r3, 0x12c
	bge @3
	li r31, 0x1
	b @2
	@3:
	cmpwi r3, 0x1c2
	bge @4
	li r31, 0x2
	b @2
	@4:
	cmpwi r3, 0x258
	bge @5
	li r31, 0x3
	b @2
	@5:
	cmpwi r3, 0x2ee
	bge @6
	li r31, 0x4
	b @2
	@6:
	cmpwi r3, 0x384
	bge @7
	li r31, 0x5
	b @2
	@7:
	li r31, 0x6
	@2:
	mr r4, r31
	li r3, 0x4
	bl pouchSetPartyColor
	lwz r0, 0x14(r1)
	mr r3, r31
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 partyKill2(s32 id) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr. r29, r3
	stw r28, 0x10(r1)
	blt @1
	slwi r0, r29, 2
	la r3, partyPtrTbl(r13)
	lwzx r31, r3, r0
	b @2
	@1:
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @3
	li r3, 0x0
	b @4
	@3:
	lwz r28, 0x160(r31)
	add r30, r28, r29
	lbz r0, 0x241(r30)
	extsb. r0, r0
	blt @5
	slwi r0, r0, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @6
	@5:
	li r3, 0x0
	@6:
	lbz r4, 0x31(r3)
	lis r3, partyDataTbl@ha
	addi r0, r3, partyDataTbl@l
	extsb r3, r4
	mulli r3, r3, 0x28
	add r3, r0, r3
	stw r3, party_dp(r13)
	lwz r12, 0x24(r3)
	cmplwi r12, 0x0
	beq @7
	lbz r0, 0x34(r31)
	cmplwi r0, 0xb
	beq @7
	mr r3, r31
	mtctr r12
	bctrl
	@7:
	add r3, r28, r29
	li r5, 0x0
	stb r5, 0x243(r3)
	li r4, -0x1
	slwi r0, r29, 2
	la r3, partyPtrTbl(r13)
	stb r4, 0x241(r30)
	stwx r5, r3, r0
	lwz r3, 0xc(r31)
	bl animPoseRelease
	mr r4, r31
	li r3, 0x0
	bl __memFree
	li r3, 0x0
	@4:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 partyKill(s32 id) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr. r28, r3
	blt @1
	slwi r0, r28, 2
	la r3, partyPtrTbl(r13)
	lwzx r31, r3, r0
	b @2
	@1:
	li r31, 0x0
	@2:
	cmplwi r31, 0x0
	bne @3
	li r3, 0x0
	b @4
	@3:
	lwz r29, 0x160(r31)
	add r30, r29, r28
	lbz r0, 0x241(r30)
	extsb. r0, r0
	blt @5
	slwi r0, r0, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @6
	@5:
	li r3, 0x0
	@6:
	lbz r4, 0x31(r3)
	lis r3, partyDataTbl@ha
	addi r0, r3, partyDataTbl@l
	extsb r3, r4
	mulli r3, r3, 0x28
	add r3, r0, r3
	stw r3, party_dp(r13)
	lwz r12, 0x24(r3)
	cmplwi r12, 0x0
	beq @7
	lbz r0, 0x34(r31)
	cmplwi r0, 0xb
	beq @7
	mr r3, r31
	mtctr r12
	bctrl
	@7:
	lbz r4, 0x241(r30)
	extsb. r4, r4
	blt @8
	slwi r0, r4, 2
	la r3, partyPtrTbl(r13)
	lwzx r0, r3, r0
	b @9
	@8:
	li r0, 0x0
	@9:
	cmplwi r0, 0x0
	beq @10
	cmpwi r4, 0x0
	blt @11
	slwi r0, r4, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @12
	@11:
	li r3, 0x0
	@12:
	lbz r0, 0x31(r3)
	add r3, r29, r28
	stb r0, 0x243(r3)
	b @13
	@10:
	add r3, r29, r28
	li r0, 0x0
	stb r0, 0x243(r3)
	@13:
	li r3, -0x1
	slwi r0, r28, 2
	stb r3, 0x241(r30)
	li r4, 0x0
	la r3, partyPtrTbl(r13)
	stwx r4, r3, r0
	lwz r3, 0xc(r31)
	bl animPoseRelease
	mr r4, r31
	li r3, 0x0
	bl __memFree
	li r3, 0x0
	@4:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm BOOL partyGoodbye(s32 id) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	cmpwi r3, 0x0
	stw r0, 0x14(r1)
	li r0, 0x0
	blt @1
	blt @2
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @3
	@2:
	li r3, 0x0
	@3:
	li r4, 0x8
	bl partyChgRunMode
	li r0, 0x1
	@1:
	mr r3, r0
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

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
	blt @1
	slwi r0, r28, 2
	la r3, partyPtrTbl(r13)
	lwzx r30, r3, r0
	b @2
	@1:
	li r30, 0x0
	@2:
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
	bne @3
	lbz r0, 0x31(r30)
	li r31, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @4
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @4
	li r31, 0x1
	@4:
	cmpwi r31, 0x1
	bne @5
	li r29, 0xc
	@5:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @6
	lbz r4, 0x31(r30)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r29, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r29, r3, r0
	b @7
	@6:
	lbz r0, 0x31(r30)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @8
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	b @7
	@8:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r29, r3, r0
	@7:
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @9
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq @3
	@9:
	stw r29, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@3:
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

asm s32 partyEntry(s32 memberId) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	bl partyEntryMain
	mr. r29, r3
	blt @1
	slwi r0, r29, 2
	la r3, partyPtrTbl(r13)
	lwzx r31, r3, r0
	b @2
	@1:
	li r31, 0x0
	@2:
	lis r3, vec3_802ccd30@ha
	li r0, 0xa
	addi r7, r3, vec3_802ccd30@l
	mr r3, r31
	lwz r6, 0x0(r7)
	addi r4, r31, 0x58
	lwz r5, 0x4(r7)
	stw r6, 0x70(r31)
	stw r5, 0x74(r31)
	lwz r5, 0x8(r7)
	stw r5, 0x78(r31)
	stb r0, 0x38(r31)
	lwz r5, 0x160(r31)
	lfs f0, 0x1a8(r5)
	stfs f0, 0x110(r31)
	lfs f0, 0x1a8(r5)
	stfs f0, 0x10c(r31)
	bl partyGetAppearPos2
	lwz r3, 0x58(r31)
	li r30, 0x1
	lwz r0, 0x5c(r31)
	stw r3, 0xb8(r31)
	stw r0, 0xbc(r31)
	lwz r0, 0x60(r31)
	stw r0, 0xc0(r31)
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 30, 30
	bne @3
	lbz r0, 0x31(r31)
	li r28, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @4
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @4
	li r28, 0x1
	@4:
	cmpwi r28, 0x1
	bne @5
	li r30, 0xc
	@5:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @6
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r30, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @7
	@6:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @8
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @7
	@8:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r30, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@7:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @9
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	beq @3
	@9:
	stw r30, 0x18(r31)
	li r0, 0x0
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@3:
	li r0, 0x1
	mr r3, r29
	stb r0, 0x34(r31)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 partyEntryHello(s32 memberId) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	bl partyEntryMain
	mr. r31, r3
	blt @1
	slwi r0, r31, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	b @2
	@1:
	li r3, 0x0
	@2:
	li r4, 0x4
	bl partyChgRunMode
	lwz r0, 0x14(r1)
	mr r3, r31
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void partySetForceMove(PartyEntry* party, s16 a2, f32 a3, f32 a4) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	stfs f1, 0x100(r3)
	sth r4, 0x28(r3)
	li r4, 0x9
	stfs f2, 0x104(r3)
	bl partyChgRunMode
	mr r3, r31
	li r4, 0x1
	bl partyChgMot
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void partyStop(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x0
	stw r0, 0x14(r1)
	bl partyChgRunMode
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void partyRun(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lbz r0, 0x34(r3)
	cmplwi r0, 0x0
	bne @1
	li r4, 0x1
	bl partyChgRunMode
	@1:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void partyCtrlOn(PartyEntry* party) {
	nofralloc
	lwz r3, partyPtrTbl(r13)
	cmplwi r3, 0x0
	beq @1
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 3, 1
	stw r0, 0x0(r3)
	@1:
	la r3, partyPtrTbl(r13)
	lwz r3, 0x4(r3)
	cmplwi r3, 0x0
	beqlr
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 3, 1
	stw r0, 0x0(r3)
	blr
}

asm void partyCtrlOff(PartyEntry* party) {
	nofralloc
	lwz r3, partyPtrTbl(r13)
	cmplwi r3, 0x0
	beq @1
	lwz r0, 0x0(r3)
	oris r0, r0, 0x2000
	stw r0, 0x0(r3)
	@1:
	la r3, partyPtrTbl(r13)
	lwz r3, 0x4(r3)
	cmplwi r3, 0x0
	beqlr
	lwz r0, 0x0(r3)
	oris r0, r0, 0x2000
	stw r0, 0x0(r3)
	blr
}

asm void partyChgPaper(PartyEntry* party, char* paper) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r4
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 30, 30
	bne @1
	lwz r3, 0x1c(r30)
	cmplwi r3, 0x0
	beq @2
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	@2:
	stw r31, 0x1c(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x4000
	stw r0, 0x8(r30)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void partyChgPose(PartyEntry* party, char* pose) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r4
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 30, 30
	bne @1
	lwz r3, 0x18(r30)
	cmplwi r3, 0x0
	beq @2
	bl strcmp
	cmpwi r3, 0x0
	beq @1
	@2:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 16, 16
	bne @1
	stw r31, 0x18(r30)
	li r0, 0x0
	sth r0, 0x20(r30)
	lwz r0, 0x8(r30)
	ori r0, r0, 0x2000
	stw r0, 0x8(r30)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

#undef partyChgPoseId
asm char* partyChgPoseId(PartyEntry* party, s32 index) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r4
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 30, 30
	beq @1
	lwz r3, 0x18(r31)
	b @2
	@1:
	lbz r0, 0x31(r31)
	li r30, 0x0
	extsb r3, r0
	cmpwi r3, 0x8
	bge @3
	bl partyGetHp
	cmpwi r3, 0x5
	bgt @3
	li r30, 0x1
	@3:
	cmpwi r30, 0x1
	bne @4
	cmpwi r29, 0x1
	bne @5
	li r29, 0xc
	b @4
	@5:
	cmpwi r29, 0x2
	bne @6
	li r29, 0xd
	b @4
	@6:
	cmpwi r29, 0x3
	bne @4
	li r29, 0xe
	@4:
	lwz r0, 0x4(r31)
	rlwinm. r0, r0, 0, 16, 16
	bne @7
	lbz r4, 0x31(r31)
	lis r3, partyPoseTbl@ha
	addi r3, r3, partyPoseTbl@l
	slwi r0, r29, 2
	extsb r4, r4
	mulli r4, r4, 0x3c
	add r3, r3, r4
	lwzx r30, r3, r0
	b @8
	@7:
	lbz r0, 0x31(r31)
	extsb r0, r0
	cmpwi r0, 0x4
	beq @9
	mulli r4, r0, 0x3c
	lis r3, partyDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, partyDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	b @8
	@9:
	li r3, 0x4
	bl pouchGetPartyColor
	mulli r4, r3, 0x3c
	lis r3, yoshiDotPoseTbl@ha
	slwi r0, r29, 2
	addi r3, r3, yoshiDotPoseTbl@l
	add r3, r3, r4
	lwzx r30, r3, r0
	@8:
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq @10
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne @10
	mr r3, r30
	b @2
	@10:
	stw r30, 0x18(r31)
	li r0, 0x0
	mr r3, r30
	sth r0, 0x20(r31)
	lwz r0, 0x8(r31)
	ori r0, r0, 0x2000
	stw r0, 0x8(r31)
	@2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void partyPaperLightOff(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x1
	stw r0, 0x14(r1)
	lwz r3, 0xc(r3)
	bl animPoseSetMaterialLightFlagOff
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void partyPaperOff(PartyEntry* party) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r0, 0x4(r3)
	rlwinm. r0, r0, 0, 5, 5
	beq @1
	lwz r0, 0x1c(r31)
	cmplwi r0, 0x0
	beq @1
	lwz r3, 0xc(r31)
	li r4, 0x0
	li r5, 0x0
	bl animPoseSetPaperAnimGroup
	li r0, 0x0
	stw r0, 0x1c(r31)
	lwz r0, 0x4(r31)
	rlwinm r0, r0, 0, 6, 4
	stw r0, 0x4(r31)
	lwz r3, 0x14(r31)
	cmpwi r3, 0x0
	blt @1
	bl animPaperPoseRelease
	li r0, -0x1
	stw r0, 0x14(r31)
	@1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL partyPaperOn(PartyEntry* party, const char* animGroup) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lis r5, vec3_802ccd30@ha
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	addi r30, r5, vec3_802ccd30@l
	stw r29, 0x14(r1)
	mr r29, r4
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r3, 0x14(r3)
	cmpwi r3, 0x0
	blt @1
	bl animPaperPoseRelease
	li r0, -0x1
	stw r0, 0x14(r28)
	@1:
	lwz r0, 0x4(r28)
	mr r3, r29
	li r4, 0x2
	oris r0, r0, 0x400
	stw r0, 0x4(r28)
	bl animPaperPoseEntry
	stw r3, 0x14(r28)
	mr r3, r29
	addi r4, r30, 0x1ec
	li r31, 0x0
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	mr r3, r29
	addi r4, r30, 0x1f4
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	mr r3, r29
	addi r4, r30, 0x1fc
	bl strcmp
	cmpwi r3, 0x0
	beq @2
	mr r3, r29
	addi r4, r30, 0x1e0
	bl strcmp
	cmpwi r3, 0x0
	bne @3
	@2:
	li r31, 0x1
	@3:
	cntlzw r0, r31
	mr r3, r29
	srwi r0, r0, 5
	addi r4, r30, 0x208
	mr r30, r0
	bl strcmp
	cmpwi r3, 0x0
	bne @4
	lbz r0, 0x31(r28)
	extsb r0, r0
	subfic r0, r0, 0x5
	cntlzw r0, r0
	srwi r30, r0, 5
	@4:
	lwz r3, 0xc(r28)
	mr r4, r29
	mr r5, r30
	bl animPoseSetPaperAnimGroup
	lwz r0, 0x24(r1)
	li r3, 0x1
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm PartyEntry* anotherPartyGetPtr(s32 index) {
	nofralloc
	cmpwi r3, 0x0
	bge @1
	li r3, 0x0
	blr
	@1:
	addi r0, r3, 0x1
	la r3, partyPtrTbl(r13)
	clrlslwi r0, r0, 31, 2
	lwzx r3, r3, r0
	blr
}

asm PartyEntry* partyGetPtr(s32 index) {
	nofralloc
	cmpwi r3, 0x0
	blt @1
	slwi r0, r3, 2
	la r3, partyPtrTbl(r13)
	lwzx r3, r3, r0
	blr
	@1:
	li r3, 0x0
	blr
}
// clang-format on
#endif
