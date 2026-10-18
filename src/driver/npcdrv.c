#define npcCheckInterrupt npcCheckInterrupt_hdr_void
#include "driver/npcdrv.h"
extern const char str_802C2FC8[];
extern const char str_802C2FE4[];
extern const char str_802C3000[];
extern const char str_802C301C[];
extern const char str_802C3038[];
extern const char str_802C3054[];
extern const char str_802C3070[];
extern const char str_802C308C[];
extern const char str_802C30A8[];
extern const char str_802C30C4[];
extern const char str_802C30E0[];
extern const char str_802C30F0[];
extern const char str_802C30FC[];
extern const char str_802C3104[];
extern const char str_802C310C[];
extern const char str_802C3128[];
extern const char str_802C3158[];
extern const char str_802C3168[];
extern const char str_802C317C[];
extern const char str_802C3198[];
extern const char str_802C31C0[];
extern const char str_802C31CC[];
extern const char str_802C31E0[];
#undef npcCheckInterrupt
BOOL npcCheckInterrupt(NpcEntry* npc);
#include "dolphin/gx/GXStruct.h"
#include "driver/animdrv.h"
#include "driver/msgdrv.h"
#include "driver/windowdrv.h"
#include "manager/fontmgr.h"
#include "mario/mario_party.h"
#include "party.h"
#include "driver/swdrv.h"
#include "data/mapdata.h"
#include "driver/effdrv.h"
#include "driver/hitdrv.h"
#include "driver/itemdrv.h"
#include "eff/eff_majinai.h"
#include "evt/evt_cmd.h"
#include "evt/evt_snd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_pouch.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include "driver/dispdrv.h"
#include "driver/offscreendrv.h"
#include "driver/seqdrv.h"
#include "battle/battle_information.h"
#include <string.h>

extern GlobalWork* gp;
extern NpcTribeInfo npcTribe[];

f32 cloudGetBreathPower(Vec pos, f32 width);
BOOL kpaMutekiCheck(void);
void kpaAddScorePos(s32 score, Vec* pos);
s32 kpaEnemyHitChk(f32 x, f32 y, f32 z, f32 height, f32 width);
void kpaPowDown(void);
void FontDrawEdge(void);
void marioChkWallAround(Vec* pos, s32 a1, f32 a2, f32 angle, f32 radius, f32 height);
#ifdef NONMATCHING
static inline f32 npc_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } return a; }
static inline f32 npc_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; } return a; }
#endif
void FontDrawScale(f32 scale);
void FontDrawStringShake(f32 x, f32 y, const char* message);

#define NPC_RAD2DEG(r) ((r) * 57.29579f)
extern int __float_nan[];
#ifdef NONMATCHING
static inline s32 npc_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 npc_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * (0.5 * guess * (3.0 - guess * guess * x)); } else if (x < 0.0) { return *(f32*)__float_nan; } else if (npc_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
#endif
USER_FUNC(btlevtcmd_ftomsec);
USER_FUNC(evt_mario_get_pos);
USER_FUNC(evt_msg_print);

typedef struct NpcWork2 {
    NpcWork field;  // 0x0
    NpcWork battle; // 0x14
} NpcWork2;

//.data
char* luigi_pose[14][2] = { { "Z_1", "Z_1R" }, { "S_1", "S_1R" },   { "W_1", "W_1R" },   { "R_1", "R_1R" },
                            { "T_1", "T_1R" }, { "J_1A", "J_1RR" }, { "J_1B", "J_1BR" }, { "Z_2", "Z_2R" },
                            { "S_2", "S_2R" }, { "T_2", "T_2R" },   { "L_1", "L_1R" },   { "L_2", "L_2R" },
                            { "L_3", "L_3R" }, { "I_1", "I_1R" } };

//.sdata
char MarioStayPose[32] = "KPA_S_1";
char MarioTalkPose[32] = "KPA_T_1";

//.sbss
BOOL dbg_battleskip = 0;
u32 npcMainCount = 0;
NpcFieldEntry* release_wp = NULL;
#pragma force_active on
u32 gap_08_804186C4_sbss;
#pragma force_active reset
static NpcWork2 work;

// local prototypes
void mtx_setup(NpcEntry* entry, Mtx mtx, s32 history);
void npcDisp_xlu(CameraId cameraId, void* param);
void npcDisp(CameraId camId, void* param);
void npcDisp_offscreen_xlu(CameraId camId, void* param);
void npcDisp_offscreen(CameraId camId, void* param);
void npcDisp_blur(CameraId camId, void* param);
void _npcDeleteGroup(NpcEntry* entry);

#define npcGetWorkPtr2(inBattle) ((inBattle) ? &work.battle : &work.field)
// TODO: inlining?
#define npcGetWorkPtrInline() (gp->inBattle ? &work.battle : &work.field)

// TODO: inlining?
#ifdef NONMATCHING
NpcWork* npcGetWorkPtr(void) {
    return gp->inBattle ? &work.battle : &work.field;
}
#endif

#ifdef NONMATCHING
void npcReleaseFieldNpc(void) {
    NpcWork* wp;
    NpcFieldEntry* field;
    NpcEntry* entry;
    AnimationPose* pose;
    int i;

    wp = &work.field;
    field = release_wp;
    if (wp->flags & 2) {
        entry = wp->entries;
        for (i = 0; i < wp->total; i++, entry++) {
            // entry = &wp->entries[i];
            if (entry->flags & 1 && entry->flags & 2 && animPoseGetAnimPosePtr(entry->poseId)->paperId == -1) {
                if (entry->poseId >= 0) {
                    pose = animPoseGetAnimPosePtr(entry->poseId);
                    field->mFlags = pose->flags;
                    field->wCurrentRenderRotationMinus90Y = pose->peraRotY;
                    field->wRotationY = pose->rotationY;
                    field->wScaleZ_flip = pose->field_0x78;
                    field->wInitToZero4 = pose->peraTargetRotY;
                    strcpy(field->mModelName, animPoseGetAnimBaseDataPtr(entry->poseId)->fileName);
                    strcpy(field->mAnimName, animPoseGetCurrentAnim(entry->poseId)->name);
                    animPoseRelease(entry->poseId);
                    field++; // next release_wp entry
                    entry->poseId = -1;
                }
            }
        }
    }
}
#endif

#ifdef NONMATCHING
void npcRecoveryFieldNpc(void) {
    NpcWork* wp;
    NpcFieldEntry* field;
    NpcEntry* entry;
    AnimationPose* pose;
    int i;

    wp = &work.field;
    field = release_wp;
    if (wp->flags & 2) {
        entry = wp->entries;
        for (i = 0; i < wp->total; i++, entry++) {
            if (entry->flags & 1 && entry->flags & 2 && entry->poseId == -1) {
                entry->poseId = animPoseEntry(field->mModelName, 0);
                animPoseSetAnim(entry->poseId, field->mAnimName, TRUE);
                pose = animPoseGetAnimPosePtr(entry->poseId);
                pose->flags = field->mFlags;
                pose->peraRotY = field->wCurrentRenderRotationMinus90Y;
                pose->rotationY = field->wRotationY;
                pose->field_0x78 = field->wScaleZ_flip;
                pose->peraTargetRotY = field->wInitToZero4;

                if (pose->flags & 0x40) {
                    pose->flags &= ~0x40;
                    animPoseWorldPositionEvalOn(entry->poseId);
                }
                if (pose->flags & 0x80) {
                    pose->flags &= ~0x80;
                    animPoseWorldMatrixEvalOn(entry->poseId);
                }
                animPoseMain(entry->poseId);
                field++; // next release_wp entry
            }
        }
        wp->flags &= ~2;
    }
}
#endif

#ifdef NONMATCHING
void mtx_setup(NpcEntry* entry, Mtx mtx, s32 history) {
    f32 rotationAngle;
    f32 scaleSign;
    CameraEntry* camera;
    f32 tmpi2[2];
    f32 v15;
    Mtx mtxX, mtxY, mtxZ;

    rotationAngle = 0.0f;
    scaleSign = 1.0f;
    if (!(entry->flags & 0x2000000) && !(entry->flags & 0x8000000)) {
        camera = camGetCurPtr();
        tmpi2[1] = angleABf(camera->cameraPos.x, camera->cameraPos.z, camera->cameraAt.x, camera->cameraAt.z);
        tmpi2[0] = angleABf(camera->cameraPos.x, camera->cameraPos.z, entry->position.x, entry->position.z);
        rotationAngle = reviseAngle(tmpi2[1] - tmpi2[0]);
    }
    v15 = reviseAngle(reviseAngle(entry->rotation.y));
    if (v15 >= 90.0f && v15 <= 270.0f) {
        scaleSign *= -1.0f;
    }
    MTXIdentity(mtx);
    if (entry->scale.x != 1.0f || entry->scale.y != 1.0f || entry->scale.z != 1.0f || scaleSign != 1.0f) {
        MTXScaleApply(mtx, mtx, entry->scale.x, entry->scale.y, entry->scale.z * scaleSign);
    }
    if (entry->rotationOffset.x || entry->rotationOffset.y || entry->rotationOffset.z) {
        MTXTransApply(mtx, mtx, -entry->rotationOffset.x, -entry->rotationOffset.y, -entry->rotationOffset.z);
    }
    if (entry->rotation.z) {
        MTXRotRad(mtxZ, 'z', entry->rotation.z * 0.017453292f);
        MTXConcat(mtxZ, mtx, mtx);
    }
    if (entry->rotation.x) {
        MTXRotRad(mtxX, 'x', entry->rotation.x * 0.017453292f);
        MTXConcat(mtxX, mtx, mtx);
    }
    if (entry->rotation.y || rotationAngle) {
        MTXRotRad(mtxY, 'y', (entry->rotation.y + rotationAngle) * 0.017453292f);
        MTXConcat(mtxY, mtx, mtx);
    }
    if (entry->rotationOffset.x || entry->rotationOffset.y || entry->rotationOffset.z) {
        MTXTransApply(mtx, mtx, entry->rotationOffset.x, entry->rotationOffset.y, entry->rotationOffset.z);
    }
    if (history == -1) {
        MTXTransApply(mtx, mtx, entry->position.x, entry->position.y, entry->position.z);
    } else {
        MTXTransApply(mtx, mtx, entry->positionHistory[history].x, entry->positionHistory[history].y,
                      entry->positionHistory[history].z);
    }
}
#endif

double atan2(double y, double x);

#ifdef NONMATCHING
static inline void npcLuigiPoseFlip(NpcEntry* entry) {
    if (entry->flags & 0x800000) {
        AnimationPose* animPose;
        AnimTableEntry* anim;
        CameraEntry* camera;
        f32 dx, dz;
        f32 angle;

        animPoseGetCurrentAnim(entry->poseId);
        animPose = animPoseGetAnimPosePtr(entry->poseId);
        anim = animPoseGetCurrentAnim(entry->poseId);

        camera = camGetPtr(CAMERA_3D);
        dx = camera->cameraAt.x - camera->cameraPos.x;
        dz = camera->cameraAt.z - camera->cameraPos.z;
        angle = reviseAngle(NPC_RAD2DEG((f32)atan2(-dx, -dz)));
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        angle = angle - animPose->rotationY;
        angle = reviseAngle(angle);

        if ((angle > 90.0f && angle <= 270.0f) || (angle < -90.0f && angle >= -270.0f)) {
            u32 i;
            for (i = 0; i < 14; i++) {
                if (!strcmp(luigi_pose[i][0], anim->name)) {
                    break;
                }
            }
            if (i < 14) {
                animPoseSetAnim(entry->poseId, luigi_pose[i][1], FALSE);
            }
        } else {
            u32 i;
            for (i = 0; i < 14; i++) {
                if (!strcmp(luigi_pose[i][1], anim->name)) {
                    break;
                }
            }
            if (i < 14) {
                animPoseSetAnim(entry->poseId, luigi_pose[i][0], FALSE);
            }
        }
    }
}
#endif

#ifdef NONMATCHING
static inline void npcDimColor(NpcEntry* entry) {
    GXColor color = entry->color;
    if (entry->jumpFlags & 0x400000) {
        color.r /= 2;
        color.g /= 2;
        color.b /= 2;
        animPoseSetMaterialEvtColor(entry->poseId, color);
        animPoseSetMaterialFlagOn(entry->poseId, 0x40);
    }
}
#endif

#ifdef NONMATCHING
void npcDisp_xlu(CameraId cameraId, void* param) {
    NpcEntry* entry = param; // cast to proper type
    Mtx mtx;
    GXColor color;
    f32 rotY;

    rotY = reviseAngle(-entry->direction);
    mtx_setup(entry, mtx, -1);

    color = entry->color;
    if (entry->jumpFlags & 0x400000) {
        color.r /= 2;
        color.g /= 2;
        color.b /= 2;
        animPoseSetMaterialEvtColor(entry->poseId, color);
        animPoseSetMaterialFlagOn(entry->poseId, 0x40);
    }

    npcLuigiPoseFlip(entry);
    animPoseMain(entry->poseId);
    animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
}
#endif

#ifdef NONMATCHING
void npcDisp(CameraId camId, void* param) {
    NpcEntry* entry = param; // cast to proper type
    Mtx mtx;
    GXColor color;
    f32 rotY;
    AnimTableEntry* anim;
    const char* nm;

    rotY = reviseAngle(-entry->direction);
    mtx_setup(entry, mtx, -1);

    switch (dispGetCurWork()->renderMode) {
        case 0:
            color = entry->color;
            if (entry->jumpFlags & 0x400000) {
                color.r /= 2;
                color.g /= 2;
                if (rotY && rotY && rotY) {
                }
                color.b /= 2;
                animPoseSetMaterialEvtColor(entry->poseId, color);
                animPoseSetMaterialFlagOn(entry->poseId, 0x40);
            }

            npcLuigiPoseFlip(entry);
            animPoseMain(entry->poseId);
            animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
            break;
        case 1:
            animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
            break;
        case 2:
            animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
            break;
    }
}
#endif

#ifdef NONMATCHING
void npcDisp_offscreen_xlu(CameraId camId, void* param) {
    NpcEntry* entry = param; // cast to proper type
    u16 left, top, right, bottom;
    Mtx mtx;
    GXColor color;
    f32 rotY;

    sysWaitDrawSync();
    GXClearBoundingBox();
    rotY = reviseAngle(-entry->direction);
    mtx_setup(entry, mtx, -1);

    npcDimColor(entry);

    npcLuigiPoseFlip(entry);
    if (!bottom) {
    }
    animPoseMain(entry->poseId);
    animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    offscreenAddBoundingBox(entry->offscreenId, left, top, right, bottom);
}
#endif

#ifdef NONMATCHING
void npcDisp_offscreen(CameraId camId, void* param) {
    NpcEntry* entry = param; // cast to proper type
    u16 left, top, right, bottom;
    Mtx mtx;
    GXColor color;
    f32 rotY;

    sysWaitDrawSync();
    GXClearBoundingBox();
    rotY = reviseAngle(-entry->direction);
    mtx_setup(entry, mtx, -1);

    switch (dispGetCurWork()->renderMode) {
        case 0:
            npcDimColor(entry);

            npcLuigiPoseFlip(entry);
            animPoseMain(entry->poseId);
            animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
            break;
        case 1:
            animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
            break;
        case 2:
            animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
            break;
    }
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    offscreenAddBoundingBox(entry->offscreenId, left, top, right, bottom);
}
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off

#ifdef NONMATCHING
void npcDisp_blur(CameraId camId, void* param) {
    NpcEntry* entry = param;
    s32 i;
    s32 alpha;
    s32 flag;
    f32 rotY;
    f32 x;
    f32 z;
    Mtx mtx;

    rotY = reviseAngle(-entry->direction);
    flag = animPoseGetMaterialFlag(entry->poseId);
    x = 2.0f * npc_sin((6.2831855f * camGetPtr(camId)->viewYaw) / 360.0f);
    z = 2.0f * -npc_cos((6.2831855f * camGetPtr(camId)->viewYaw) / 360.0f);
    animPoseMain(entry->poseId);
    for (i = 4, alpha = 100; i > 0; i--, alpha -= 25) {
        mtx_setup(entry, mtx, i);
        MTXTransApply(mtx, mtx, x, 0.0f, z);
        animPoseSetMaterialFlagOn(entry->poseId, 0x40);
        animPoseSetMaterialEvtColor(entry->poseId, (GXColor){0xFF, 0xFF, 0xFF, (u8)(0x80 - alpha)});
        animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
        animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
        animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
    }
    animPoseSetMaterialFlagOff(entry->poseId, 0x40);
    animPoseSetMaterialFlagOn(entry->poseId, flag);
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#ifdef NONMATCHING
void npcInit(void) { // 1:1
    FieldBattleData* data;
    NpcWork* wp;

    wp = &work.field;
    wp->total = NPC_FIELD_MAX_COUNT;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(NpcEntry) * wp->total);
    memset(wp->entries, 0, sizeof(NpcEntry) * wp->total);

    release_wp = __memAlloc(HEAP_DEFAULT, sizeof(NpcFieldEntry) * wp->total);

    wp = &work.battle;
    wp->total = NPC_BATTLE_MAX_COUNT;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(NpcEntry) * wp->total);
    memset(wp->entries, 0, sizeof(NpcEntry) * wp->total);

    data = __memAlloc(HEAP_DEFAULT, sizeof(FieldBattleData));
    gp->fbatData = data;
    memset(gp->fbatData, 0, sizeof(FieldBattleData));
    data->mode = 0;
    npcMainCount = 0;
}
#endif

#ifdef NONMATCHING
void npcReset(BOOL inBattle) {
    NpcWork* wp = npcGetWorkPtr2(inBattle);
    memset(wp->entries, 0, sizeof(NpcEntry) * wp->total);
    wp->count = 0;
    if (!inBattle) {
        gp->fbatData->mode = 0;
    }
    npcMainCount = 0;
}
#endif

#ifdef NONMATCHING
s32 npcGetReactionOfLivingBody(BOOL inBattle) {
    return npcGetWorkPtr2(inBattle)->count;
}
#endif

// TODO: fix entry->position delayed set-Vec with r6/r30
// TODO: a1 is desc/ription?
#ifdef NONMATCHING
s32 npcEntry(const char* a1, const char* animName) {
    NpcWork* wp;
    s32 i;
    NpcEntry* entry;
    s32 total;


    wp = gp->inBattle ? &work.battle : &work.field;
    total = wp->total;
    for (i = 0, entry = wp->entries; i < total; i++, entry++) {
        if (entry->flags & 1 && !strcmp(entry->description, a1)) {
            break;
        }
    }

    entry = wp->entries;
    for (i = 0; i < total; i++, entry++) {
        if (!(entry->flags & 1)) {
            break;
        }
    }
    memset(entry, 0, sizeof(NpcEntry));
    entry->flags = 3;
    strcpy(entry->description, a1);
    entry->poseId = animPoseEntry(animName, gp->inBattle != 0);
    if (entry->poseId == -2) {
        entry->poseId = animPoseEntry("hoshi", gp->inBattle != 0);
    }
    animPosePeraOn(entry->poseId);
    entry->position = (Vec){0.0f, 0.0f, 0.0f};
    entry->prevPosition = entry->position;
    entry->width = animPoseGetHeight(entry->poseId);
    entry->height = animPoseGetRadius(entry->poseId);
    entry->scale = (Vec){1.0f, 1.0f, 1.0f};
    entry->shadowScale = 1.0f;
    entry->field_108 = 0;
    entry->field_10C = "M_I_2";
    entry->field_198 = gp->renderTime;
    entry->field_188 = 0;
    entry->jumpGravity = 1.0f;
    entry->field_1D0 = 0.0f;
    entry->jumpYScale = 1.0f;
    entry->offscreenId = -1;
    entry->color = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    entry->cameraId = CAMERA_3D;
    entry->field_2F8 = 0;
    entry->balloonType = 1;
    if (animPoseGetVivianType(entry->poseId)) {
        entry->flags |= 0x4000000;
    }
    if (!strcmp(animName, (char*)str_802C31E0)) {
        entry->flags |= 0x800000u;
    }
    animPoseSetMaterialLightFlagOn(entry->poseId, 2);
    wp->count++;
    return i;
}
#endif

#ifdef NONMATCHING
static const Vec sZeroVec3 = {0.0f, 0.0f, 0.0f};
#endif

#ifdef NONMATCHING
NpcTribeInfo* npcGetTribe(const char* tribeName) { // 1:1
    NpcTribeInfo* tribe;

    for (tribe = npcTribe; tribe->nameJp; tribe++) {
        if (!strcmp(tribe->nameJp, tribeName)) {
            return tribe;
        }
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
void npcDelete(NpcEntry* entry) {
    int i;

    for (i = 0; i < 4; i++) {
        if (entry->slaves[i]) {
            entry->slaves[i]->master = NULL;
        }
        entry->slaves[i] = NULL;
    }

    if (entry->prev) {
        if (entry->next) {
            entry->prev->next = entry->next;
            entry->next->prev = entry->prev;
        } else {
            entry->prev->next = NULL;
        }
    } else {
        if (entry->next) {
            entry->next->prev = NULL;
        }
    }
    entry->flags &= ~2;
    if (entry->poseId >= 0) {
        animPoseRelease(entry->poseId);
    }
    entry->poseId = -1;
    entry->flags &= ~1;
    npcGetWorkPtrInline()->count--;
}
#endif

#ifdef NONMATCHING
void _npcDeleteGroup(NpcEntry* entry) { // recursively inlined, warning
    NpcEntry* s;
    int i;

    if (entry->next) {
        _npcDeleteGroup(entry->next);
    }

    for (i = 0; i < 4; i++) {
        s = entry->slaves[i];
        if (s) {
            npcDelete(s);
            entry->slaves[i] = NULL;
        }
    }
    npcDelete(entry);
}
#endif

#ifdef NONMATCHING
void npcDeleteGroup(NpcEntry* entry) {
    if (entry->master) {
        entry = entry->master;
    }
    while (entry->prev) {
        entry = entry->prev;
    }
    _npcDeleteGroup(entry);
}
#endif

void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param);
void fbatEncountCheck(void);
void fbatTalkMode(void);
void fbatBattleMode(void);
s32 kpaJumpChk(void);
s32 kpaFireAttackCheck(void);

void npcMoveG(NpcEntry* npc);
BOOL npcCheckHitMarioSide(NpcEntry* npc);
HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz);
s32 vivianGetStatus(void);
#define NPC_CHKMARIO(ok) do {     m = marioGetPtr();     if (*(u32*)m & 0x82000000) { ok = 0; break; }     if (*(u32*)m & 0xA) { ok = 0; break; }     if (*(s32*)((u8*)gp + 0x164) != 0) { ok = 0; break; }     if (seqGetSeq() != 2) { ok = 0; break; }     if (*(u16*)((u8*)m + 0x2E) == 0x19) { ok = 0; break; }     if (vivianGetStatus() != 0 && vivianGetStatus() != 1) { ok = 0; } else { ok = 1; } } while (0)
void shadowSetCollision(s32 shadow, s32 val);
s32 shadowEntry(f32 x, f32 y, f32 z, f32 size);
void animPoseVivianMain(s32 poseId, Vec* pos);
f32 sinfd(f32 degrees);
void npcKoopaModeMain(void);
BOOL npcCheckBlow(NpcEntry* npc);
#ifdef NONMATCHING
void npcMain(void) {
    const char* kpaSfx;
    NpcWork* npcwork;
    u8* fbat;
    NpcEntry* entry;
    int i;
    int total;
    f32 dir;
    f32 prio;
    f32 dist; Vec dv; Vec dv2;
    s32 fire, jump;

    npcwork = gp->inBattle ? &work.battle : &work.field;
    // npcwork = npcGetWorkPtr();
    marioGetPtr()->targetNpc = 0;
    kpaSfx = (char*)str_802C310C;

    npcMainCount++;

    total = npcwork->total;
    for (i = 0, entry = npcwork->entries; i < total; i++, entry++) {
        if (entry->flags & 1 && entry->flags & 2) {
            if (entry->flags & 0x8000) {
                animPoseGetAnimPosePtr(entry->poseId)->flags |= 0x100;
            } else {
                animPoseGetAnimPosePtr(entry->poseId)->flags &= ~0x100;
            }

            if (!(entry->flags & 0x100000)) {
                entry->jumpFlags |= 0x10;
            }
            if (entry->jumpFlags & 0x10000) {
                entry->jumpFlags &= ~0x10;
            }

            if (*(u16*)&entry->wFbatHitCheckRelated) {
                entry->wFbatHitCheckRelated = *(u16*)&entry->wFbatHitCheckRelated - 1;
            }

            if (entry->jumpFlags & 0x10) {
                entry->field_190 = gp->renderTime - entry->field_198;
                if (OSTicksToMilliseconds(entry->field_190) > 500) {
                    entry->field_190 = OSMillisecondsToTicks(16);
                }
                if (entry->flags & 0x20000) {
                    entry->field_178 += entry->field_190;
                } else {
                    entry->field_178 = 0;
                }
                entry->field_188 += entry->field_190;
                entry->field_198 = gp->renderTime;
                entry->field_1A0 = (f32)(OSTicksToMicroseconds(entry->field_188)) / 1000000.0f;
                entry->field_180 = (f32)(OSTicksToMicroseconds(entry->field_178)) / 1000000.0f;
                entry->moveDt = (f32)(OSTicksToMicroseconds(entry->field_190)) / 1000000.0f;
                entry->field_1A8 = (f32)(OSTicksToMicroseconds(entry->field_198)) / 1000000.0f;

            } else {
                entry->field_198 = gp->renderTime;
            }

            if (entry->flags & 2) {
                if (entry->jumpFlags & 0x100000) {
                    entry->jumpFlags |= 0x200000;
                } else {
                    entry->jumpFlags &= ~0x200000;
                }
                entry->jumpFlags &= ~0x100000;
                {
                    f32 f30v;
                    if (!strcmp(gp->currentMapName, (char*)str_802C3104) && !(entry->position.y > 365.0f)) {
                        entry->jumpFlags |= 0x100000;
                        if (!(entry->jumpFlags & 0x200000) && (entry->jumpFlags & 0x100000)) {
                            psndSFXOn_3D(kpaSfx, &entry->position);
                        }
                    }
                    if (entry->jumpFlags & 0x100000 && !(entry->jumpFlags & 0x10000000)) {
                        entry->field_1D0 = 100.0f;
                        f30v = 0.5f;
                    } else {
                        f30v = 1.0f;
                    }
                    if (entry->jumpFlags & 0x100000) {
                        entry->field_31E |= 1;
                    }
                    if (entry->jumpFlags & 0x10) {
                        if (entry->moveDt > 0.0f) {
                            f32 mx = entry->moveOffset.x;
                            f32 mz = entry->moveOffset.z;
                            if (entry->jumpFlags & 0x100000 && !(entry->jumpFlags & 0x10000000)) {
                                mx *= 0.5f;
                                mz *= 0.5f;
                            }
                            if (entry->flags & 0x8000000) {
                                mz = 0.0f;
                            }
                            if (entry->flags & 0x40000000) {
                                entry->position.x += mx;
                                entry->position.z += mz;
                            } else {
                                entry->wallHit = (u32)npcHitCheckSide(entry, &entry->position.x, &entry->position.z,
                                                                        &entry->moveDir, mx, mz);
                            }
                            entry->moveOffset.x = 0.0f;
                            entry->moveOffset.z = 0.0f;
                            npcMoveG(entry);
                        }
                        if (!(entry->flags & 8) && !(entry->flags & 0x20) && !(entry->flags & 0x4000)) {
                            npcCheckHitMarioSide(entry);
                        }
                        {
                            
                            PSVECSubtract(&entry->position, &entry->prevPosition, &dv);
                            if (entry->flags & 0x400 && entry->moveDt > 0.0f) {
                                f32 spd = npc_sqrtf(dv.x * dv.x + dv.z * dv.z) / entry->moveDt;
                                if (spd < 0.1f) {
                                    if (entry->field_108 != 1) {
                                        animPoseSetAnim(entry->poseId, entry->tribe->stayAnim, TRUE);
                                        entry->field_108 = 1;
                                    }
                                } else if (spd < entry->tribe->runStartSpeed * f30v) {
                                    if (entry->field_108 != 2) {
                                        animPoseSetAnim(entry->poseId, entry->tribe->walkAnimation, TRUE);
                                        entry->field_108 = 2;
                                    }
                                } else {
                                    if (entry->field_108 != 3) {
                                        animPoseSetAnim(entry->poseId, entry->tribe->runAnimation, TRUE);
                                        entry->field_108 = 3;
                                    }
                                }
                            }
                        }
                    }
                }
                if (entry->regularEvtId) {
                    EventEntry* evt = evtGetPtrID(entry->regularEvtId);
                    if (evt && !(evt->flags & 2)) {
                        s32 st = evt->wNpcEventType;
                        if (entry->blowEvent && st != 5 && st != 8) {
                            int trig;
                            trig = npcCheckBlow(entry);
                            if (trig) {
                                entry->interruptFlags |= 8;
                                goto interrupt;
                            }
                        }
                        if (entry->territoryType != 0 && (st == 1 || st == 2)) {
                            int trig;
                            trig = 0;
                            if (entry->territoryType == 1) {
                                f32 tz = entry->territoryBase.z - entry->position.z;
                                f32 tx = entry->territoryBase.x - entry->position.x;
                                f32 d = npc_sqrtf(tx * tx + tz * tz);
                                if (d > (st == 2 ? entry->territoryHoming.x : entry->territoryHoming.x)) {
                                    trig = 1;
                                }
                            } else if (entry->territoryType == 2) {
                                if (st == 2) {
                                    if (entry->position.x < entry->territoryBase.x - entry->territoryHoming.x ||
                                        entry->position.x > entry->territoryBase.x + entry->territoryHoming.x ||
                                        entry->position.z < entry->territoryBase.z - entry->territoryHoming.z ||
                                        entry->position.z > entry->territoryBase.z + entry->territoryHoming.z) {
                                        trig = 1;
                                    }
                                } else {
                                    if (entry->position.x < entry->territoryBase.x - entry->territoryLoiter.x ||
                                        entry->position.x > entry->territoryBase.x + entry->territoryLoiter.x ||
                                        entry->position.z < entry->territoryBase.z - entry->territoryLoiter.z ||
                                        entry->position.z > entry->territoryBase.z + entry->territoryLoiter.z) {
                                        trig = 1;
                                    }
                                }
                            }
                            if (trig) {
                                entry->interruptFlags |= 4;
                                goto interrupt;
                            }
                        }
                        if (st == 2) {
                            MarioWork* m = marioGetPtr();
                            f32 dx = m->position.x - entry->position.x;
                            f32 dy = m->position.y - entry->position.y;
                            f32 dz = m->position.z - entry->position.z;
                            int trig;
                            PSVECSubtract(&entry->prevPosition, &entry->position, &dv2);
                            dir = entry->direction;
                            if (entry->jumpFlags & 2) {
                                if (npc_sqrtf(dv2.x * dv2.x + dv2.z * dv2.z) > 0.05f) {
                                    dir = entry->moveDir;
                                }
                            }
                            trig = 0;
                            { s32 ok_; NPC_CHKMARIO(ok_); if (!ok_) {
                                trig = 1;
                            } else {
                                dist = npc_sqrtf(dx * dx + dz * dz);
                                if (dist > 0.25f * entry->homingRange) {
                                    if (dy > entry->territoryLoiter.y) {
                                        trig = 1;
                                    } else if (-dy > entry->territoryHoming.y) {
                                        trig = 1;
                                    } else if (dist > entry->homingRange) {
                                        trig = 1;
                                    } else if ((dist = angleABf(0.0f, 0.0f, dx, dz), __fabsf(compAngle(dir, dist))) >
                                               0.5f * entry->homingAngle) {
                                        trig = 1;
                                    }
                                }
                            }
                            }
                            if (trig) {
                                entry->interruptFlags |= 2;
                                goto interrupt;
                            }
                        }
                        if (st == 1 || st == 4) {
                            MarioWork* m = marioGetPtr();
                            f32 dx, dy, dz;
                            int trig;
                            Vec dv;
                            dx = m->position.x - entry->position.x;
                            dz = m->position.z - entry->position.z;
                            dy = m->position.y - entry->position.y;
                            dist = dx * dx + dz * dz;
                            npc_sqrtf(dist);
                            PSVECSubtract(&entry->prevPosition, &entry->position, &dv);
                            dir = reviseAngle(entry->direction) < 180.0f ? 90.0f : 270.0f;
                            trig = 1;
                            { s32 ok_; NPC_CHKMARIO(ok_); if (!ok_) {
                                trig = 0;
                            } else {
                                f32 a14;
                                dist = npc_sqrtf(dist);
                                if (dist > 0.25f * entry->searchRange) {
                                    if (dist > entry->searchRange) {
                                        trig = 0;
                                        goto done14;
                                    } else if ((a14 = angleABf(0.0f, 0.0f, dx, dz), __fabsf(compAngle(dir, a14))) >
                                               0.5f * entry->searchAngle) {
                                        trig = 0;
                                        goto done14;
                                    }
                                }
                                {
                                    if (dy > entry->territoryLoiter.y) {
                                        trig = 0;
                                    } else if (-dy > entry->territoryHoming.y) {
                                        trig = 0;
                                    } else if (st == 4) {
                                        if (entry->territoryType == 1) {
                                            f32 tz = entry->territoryBase.z - entry->position.z;
                                            f32 tx = entry->territoryBase.x - entry->position.x;
                                            f32 d = npc_sqrtf(tx * tx + tz * tz);
                                            if (d > 0.75 * entry->territoryHoming.x) {
                                                trig = 0;
                                            }
                                        } else {
                                            if (entry->position.x < entry->territoryBase.x - 0.75f * entry->territoryHoming.x ||
                                                entry->position.x > entry->territoryBase.x + 0.75f * entry->territoryHoming.x ||
                                                entry->position.z < entry->territoryBase.z - 0.75f * entry->territoryHoming.z ||
                                                entry->position.z > entry->territoryBase.z + 0.75f * entry->territoryHoming.z) {
                                                trig = 0;
                                            }
                                        }
                                    }
                                }
                            }
                            }
                            done14:
                            if (trig) {
                                entry->interruptFlags |= 1;
                            }
                        }
                    }
interrupt:
                    npcCheckInterrupt(entry);
                }
                if (!(entry->flags & 0x800)) {
                    CameraEntry* cam;

                    cam = camGetPtr((CameraId)4);
                    PSMTXMultVec((void*)((u8*)cam + 0x11C), &entry->position, &dv);
                    cam = camGetPtr((CameraId)4);
                    PSMTX44MultVec((void*)((u8*)cam + 0x15C), &dv, &dv);
                    if ((dv.z > -1.0f && dv.z < 0.0f && dv.x >= -2.0f && dv.x <= 2.0f && dv.y >= -2.0f && dv.y <= 2.0f) ||
                        (entry->flags & 0x40)) {
                        if (entry->color.r != 0xFF || entry->color.g != 0xFF || entry->color.b != 0xFF ||
                            entry->color.a != 0xFF) {
                            animPoseSetMaterialFlagOn(entry->poseId, 0x40);
                            animPoseSetMaterialEvtColor(entry->poseId, entry->color);
                        } else {
                            animPoseSetMaterialFlagOff(entry->poseId, 0x40);
                        }
                        prio = 5000.0f + 5000.0f * dv.z;
                        if (prio < 0.0f) {
                            prio = 0.0f;
                        } else if (prio > 10000.0f) {
                            prio = 10000.0f;
                        }
                        prio *= -1.0f;
                        if (!(entry->flags & 0x80) &&
                            (!(*(u16*)&entry->wFbatHitCheckRelated & 2) || (entry->jumpFlags & 0x10000))) {
                            if (entry->color.a != 0xFF) {
                                dispEntry((CameraId)entry->cameraId, prio, 2, npcDisp_xlu, entry);
                            } else {
                                dispEntry((CameraId)entry->cameraId, prio, 0, npcDisp, entry);
                                dispEntry((CameraId)entry->cameraId, prio, 1, npcDisp, entry);
                                dispEntry((CameraId)entry->cameraId, prio, 2, npcDisp, entry);
                            }
                            if (!(entry->flags & 0x4000000)) {
                                if (!(entry->flags & 0x40000)) {
                                    Vec sp = entry->position;
                                    if (entry->tribe) {
                                        sp.x += entry->tribe->shadowOffsetX * entry->scale.x * sinfd(reviseAngle(entry->direction) < 180.0f ? 90.0f : 270.0f);
                                        sp.y += entry->tribe->shadowOffsetY * entry->scale.y;
                                        sp.z += entry->tribe->shadowOffsetZ * entry->scale.z;
                                    }
                                    {
                                        s32 sh = shadowEntry(
                                            sp.x, sp.y, sp.z,
                                            1.33f * (entry->shadowScale * (entry->width / 3.0f * entry->scale.x)));
                                        if (entry->flags & 0x80000) {
                                            shadowSetCollision(sh, 0);
                                        }
                                    }
                                }
                            } else {
                                Vec vp = entry->position;
                                f32 o0, o1, o2, o3, o4, o5, o6;
                                o3 = 100.0f;
                                if (hitCheckFilter(NULL, &o0, &o1, &o2, &o3, &o4, &o5, &o6, vp.x, 1.0f + vp.y, vp.z,
                                                   0.0f, -1.0f, 0.0f)) {
                                    vp.y = o1;
                                }
                                animPoseVivianMain(entry->poseId, &vp);
                                {
                                    s32 sh = shadowEntry(entry->position.x, entry->position.y, entry->position.z,
                                                         entry->shadowScale * (entry->width / 3.0f * entry->scale.x));
                                    if (entry->flags & 0x80000) {
                                        shadowSetCollision(sh, 0);
                                    }
                                }
                            }
                            if (entry->flags & 0x100) {
                                dispEntry((CameraId)entry->cameraId, prio, 2, npcDisp_blur, entry);
                            }
                        }
                        if (entry->offscreenId != -1) {
                            if (entry->color.a != 0xFF) {
                                dispEntry((CameraId)1, prio, 2, npcDisp_offscreen_xlu, entry);
                            } else {
                                dispEntry((CameraId)1, prio, 0, npcDisp_offscreen, entry);
                                dispEntry((CameraId)1, prio, 1, npcDisp_offscreen, entry);
                                dispEntry((CameraId)1, prio, 2, npcDisp_offscreen, entry);
                            }
                        }
                    }
                }
                entry->prevPosition = entry->position;
                if (entry->flags & 0x100 && !(npcMainCount & 1)) {
                    entry->positionHistory[4] = entry->positionHistory[3];
                    entry->positionHistory[3] = entry->positionHistory[2];
                    entry->positionHistory[2] = entry->positionHistory[1];
                    entry->positionHistory[1] = entry->positionHistory[0];
                    entry->positionHistory[0] = entry->position;
                }
            }
            entry->jumpFlags &= ~0x10;
        }
    }

    fbat = *(u8**)((u8*)gp + 0x168);
    {
        u8* ann = fbat + 0x550;
        if (*(s32*)ann) {
            switch (*(s32*)(ann + 8)) {
            case 2:
                (*(s32*)(ann + 0xc))++;
                if (*(s32*)(ann + 0xc) < 20) {
                    *(f32*)(ann + 0x10) = intplGetValue(5, *(s32*)(ann + 0xc), 20, -600.0f, 0.0f);
                } else if (*(s32*)(ann + 0xc) < 80) {
                    *(f32*)(ann + 0x10) = 0.0f;
                } else if (*(s32*)(ann + 0xc) < 100) {
                    *(f32*)(ann + 0x10) = intplGetValue(1, *(s32*)(ann + 0xc) - 80, 20, 0.0f, 600.0f);
                } else {
                    *(s32*)(ann + 4) = 0;
                    break;
                }
                *(f32*)(ann + 0x14) = 0.0f;
                dispEntry((CameraId)9, 0.0f, 2, _fbatFirstAttackAnnouceDisp, ann);
                break;
            case 1:
                (*(s32*)(ann + 0xc))++;
                if (*(s32*)(ann + 0xc) > 60) {
                    *(s32*)(ann + 4) = 0;
                    break;
                }
                *(f32*)(ann + 0x10) = 0.0f;
                *(f32*)(ann + 0x14) = 0.0f;
                dispEntry((CameraId)9, 0.0f, 2, _fbatFirstAttackAnnouceDisp, ann);
                break;
            }
        }
        switch (*(s16*)fbat) {
        case 1:
            npcKoopaModeMain();
            break;
        case 2:
        case 3:
            fbatTalkMode();
            break;
        case 5:
            fbatBattleMode();
            break;
        case 6:
            break;
        }
        *(fbat + 0x54d) = 0;
    }
}
#endif

#ifdef NONMATCHING
NpcEntry* npcNameToPtr(const char* name) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;
    for (i = 0; i < total; i++, entry++) {
        if (entry->flags & 1 && !strcmp(entry->description, name)) {
            break;
        }
    }
    return entry;
}
#endif

#ifdef NONMATCHING
NpcEntry* npcNameToPtr_NoAssert(const char* name) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;
    for (i = 0; i < total; i++, entry++) {
        if (entry->flags & 1 && !strcmp(entry->description, name)) {
            break;
        }
    }
    if (i >= total) {
        return NULL;
    }
    return entry;
}
#endif

#ifdef NONMATCHING
void npcSetMarioAutoTalkPose(const char* stayPose, const char* talkPose) {
    strcpy(MarioStayPose, stayPose);
    strcpy(MarioTalkPose, talkPose);
}
#endif

#pragma opt_propagation off
#pragma opt_lifetimes off
#ifdef NONMATCHING
void npcSetTalkPose(const char* name) {
    PartyEntry* party;
    NpcEntry* npc;

    if (*(s8*)name == 0) {
        return;
    }
    if (!strcmp(name, (char*)str_802C31C0)) {
        return;
    }
    if (!strcmp(name, "party")) {
        party = partyGetPtr(marioGetPartyId());
        if (party) {
            partyChgPoseId(party, 7);
        }
    } else if (!strcmp(name, (char*)str_802C31CC)) {
        party = partyGetPtr(marioGetExtraPartyId());
        if (party) {
            partyChgPoseId(party, 7);
        }
    } else if (!strcmp(name, "mario")) {
        marioChgPose(MarioTalkPose);
    } else {
        npc = npcNameToPtr(name);
        if (npc->flags & 0x200) {
            animPoseSetAnim(npc->poseId, npc->talkAnim, TRUE);
        }
    }
}
#endif

#ifdef NONMATCHING
void npcSetStayPose(const char* name) {
    PartyEntry* party;
    NpcEntry* npc;

    if (*(s8*)name == 0) {
        return;
    }
    if (!strcmp(name, (char*)str_802C31C0)) {
        return;
    }
    if (!strcmp(name, "party")) {
        party = partyGetPtr(marioGetPartyId());
        if (party) {
            partyChgPoseId(party, 1);
        }
    } else if (!strcmp(name, (char*)str_802C31CC)) {
        party = partyGetPtr(marioGetExtraPartyId());
        if (party) {
            partyChgPoseId(party, 1);
        }
    } else if (!strcmp(name, "mario")) {
        marioChgPose(MarioStayPose);
    } else {
        npc = npcNameToPtr(name);
        if (npc->flags & 0x200) {
            animPoseSetAnim(npc->poseId, npc->stayAnim, TRUE);
        }
    }
}
#endif

#ifdef NONMATCHING
BOOL npcCheckHitMarioSide(NpcEntry* npc) {
    MarioWork* mario; float new_var ; // FAKE: temp needed for 100% (99.97 without)
    Vec marioPos;
    f32 dist;
    f32 range;
    f32 angle;
    f32 dx; f32 dz;
    f32 rad;
    f32 len;
    f32 scale;

    mario = marioGetPtr();
    if (npc->position.y > ( mario->position.y + mario->wPlayerCollisionBox.y) ) {
        dz = mario->wPlayerCollisionBox.y;
        return FALSE;
    }
    if (mario->position.y > ( npc->position.y + npc->height) ) {
        return FALSE;
    }
    marioPos.x = mario->position.x;
    marioPos.z = mario->position.z;
    marioPos.y = npc->position.y;
    dist = PSVECDistance(&marioPos, &npc->position);
    new_var = 5.0f + (mario->wPlayerCollisionBox.x + npc->width); range = new_var ;
    range *= 0.5f;
    if (dist > range) {
        return FALSE;
    }
    npc->position.x = npc->prevPosition.x;
    npc->position.z = npc->prevPosition.z;
    dist = PSVECDistance(&marioPos, &npc->position);
    if (dist > range) {
        return FALSE;
    }
    mario->targetNpc = (s32)npc;
    angle = angleABf(mario->position.x, mario->position.z, npc->position.x, npc->position.z);
    if (__fabsf(compAngle(angle, mario->directionView)) < 40.0f) {
        dx = (range - dist) * ( -npc_sin((6.2831855f * mario->directionView) / 360.0f) );
        dz = (range - dist) * npc_cos((6.2831855f * mario->directionView) / 360.0f);

    } else {
        rad = (6.2831855f * angle) / 360.0f;
        dx = (npc->position.x - ( range * npc_sin(rad) )) - mario->position.x;
        dz = (npc->position.z + ( range * npc_cos(rad) )) - mario->position.z;
    }
    len = npc_sqrtf(( dx * dx ) + ( dz * dz) );
    if (len > ( (mario->wPlayerCollisionBox.z > 4.0f ) ? ( 3.0f ) : ( 1.5f))) { if (1 ) {
        scale = 2.0f / len;
        dx *= scale;
        dz *= scale;
    }
    }
    mario->position.x += dx;
    mario->position.z += dz;
    dz = mario->wPlayerCollisionBox.y;
    marioChkWallAround(&mario->position, 0, 0.0f, 160.0f + angle, 20.0f, dz);
    return TRUE;
}
#endif
#pragma opt_propagation reset
#pragma opt_lifetimes reset

#ifdef NONMATCHING
void npcMoveG(NpcEntry* npc) {
    f32 dy;
    f32 vel;
    f32 t;
    f32 dt;
    f32 tp;
    f32 limit;
    f32 hitX, hitY, hitZ, dist, hitNX, hitNY, hitNZ;
    f32 h;

    dy = npc->moveOffset.y;
    npc->moveOffset.y = 0.0f;
    if (npc->jumpFlags & 0x100000 && !(npc->jumpFlags & 0x10000000)) {
        dy *= 0.5f;
    }
    vel = 0.0f;
    if (npc->flags & 0x20000) {
        t = npc->field_180;
        dt = npc->moveDt;
        tp = t - dt;
        if (!(npc->jumpFlags & 0x100000) || npc->jumpFlags & 0x10000000) {
            vel = npc->jumpVelY * dt + (-980.0f * npc->jumpGravity) * (t * t - tp * tp);
        } else {
            vel = 0.4f * (npc->jumpVelY * dt) + (0.15f * (-980.0f * npc->jumpGravity)) * (t * t - tp * tp);
        }
        vel *= npc->jumpYScale;
        if (npc->field_1D0 > 0.0f) {
            if (npc->jumpFlags & 0x100000) {
                limit = 0.5f * (-npc->field_1D0 * dt);
            } else {
                limit = -npc->field_1D0 * dt;
            }
            if (vel < limit) {
                vel = limit;
            }
        }
    }
    dy += vel;
    if (!(npc->flags & 0x10)) {
        npc->position.y += dy;
        if (npc->position.y < -1000.0f) {
            npc->position.y = -1000.0f;
        }
    } else if (dy != 0.0f) {
        if (dy > 0.0f) {
            npc->jumpFlags |= 1;
            npc->position.y += dy;
        } else {
            f64 ad = __fabs(dy);
            f32 hh = 0.8f * npc->height;
            dist = hh + (f32)ad;
            if ((npc->field_0x300 = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &dist, &hitNX, &hitNY, &hitNZ,
                                              npc->position.x, npc->position.y + hh, npc->position.z, 0.0f,
                                              -1.0f, 0.0f)) == NULL) {
                npc->jumpFlags |= 1;
                npc->position.y += dy;
            } else {
                npc->jumpFlags &= ~1;
                npc->position.y = hitY;
                npc->field_178 = 0;
            }
        }
    }
}
#endif

#ifdef NONMATCHING
void npcTuningRy(NpcEntry* npc, f32 angle) {
    npc->direction = reviseAngle(angle);
}
#endif

#ifdef NONMATCHING
f32 npcTransRytoFaceDir(NpcEntry* npc) {
    if (reviseAngle(npc->direction) < 180.0f) {
        return 90.0f;
    }
    return 270.0f;
}
#endif

#ifdef NONMATCHING
static inline void npcSideSlide(f32* outX, f32* outZ, f32 dx, f32 dz, f32 nx, f32 nz) {
    f32 d = dx * nx + dz * nz;
    f32 ax = 0.5f * (dx - d * nx);
    f32 az = 0.5f * (dz - d * nz);
    *outX += ax;
    *outZ += az;
}
#endif

#ifdef NONMATCHING
HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz) {
    f32 hx, hy, hz, dist, nx, ny, nz;
    f32 lenSq, d, height;
    HitEntry* hit;
    f32 s, c;

    *outX = npc->position.x;
    *outZ = npc->position.z;
    if (dx == 0.0f && dz == 0.0f) {
        return NULL;
    }
    sincosf(&s, &c, angleABf(0.0f, 0.0f, dx, dz));

    dist = npc_sqrtf(dx * dx + dz * dz) + 0.75f * npc->width;
    height = 0.2f * npc->height;
    if (height > 10.0f) {
        height = 10.0f;
    }
    if (npc->flags & 0x2000) {
        hit = hitCheckAttr(4, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    } else {
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    }
    if (hit) {
        npcSideSlide(outX, outZ, dx, dz, nx, nz);
        if (npc->flags & 0x10000) {
            f32 a = reviseAngle(180.0f + *angle);
            f32 b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * nx, 100.0f * nz));
            *angle = (s32)reviseAngle(b + reviseAngle(b - a));
        }
        return hit;
    }

    dist = npc_sqrtf(dx * dx + dz * dz) + 0.75f * npc->width;
    height = 0.4f * npc->height;
    if (npc->flags & 0x2000) {
        hit = hitCheckAttr(4, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    } else {
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    }
    if (hit && angleABf(0.0f, 0.0f, npc_sqrtf(nx * nx + nz * nz), -ny) >= 45.0f) {
        npcSideSlide(outX, outZ, dx, dz, nx, nz);
        if (npc->flags & 0x10000) {
            f32 a = reviseAngle(180.0f + *angle);
            f32 b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * nx, 100.0f * nz));
            *angle = (s32)reviseAngle(b + reviseAngle(b - a));
        }
        return hit;
    }

    dist = npc_sqrtf(dx * dx + dz * dz) + 0.75f * npc->width;
    height = 0.75f * npc->height;
    if (npc->flags & 0x2000) {
        hit = hitCheckAttr(4, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    } else {
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    }
    if (hit) {
        npcSideSlide(outX, outZ, dx, dz, nx, nz);
        if (npc->flags & 0x10000) {
            f32 a = reviseAngle(180.0f + *angle);
            f32 b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * nx, 100.0f * nz));
            *angle = (s32)reviseAngle(b + reviseAngle(b - a));
        }
        return hit;
    }
    *outX += dx;
    *outZ += dz;
    return NULL;
}
#endif

#ifdef NONMATCHING
NpcEntry* npcNearDistCheck(f32 x, f32 y, f32 z, f32 range) {
    NpcWork* wp;
    NpcEntry* entry;
    NpcEntry* found;
    s32 i;
    f32 dx, dy, dz;
    f32 dist;
    s32 total;

    wp = npcGetWorkPtrInline();
    found = NULL;
    entry = wp->entries;
    total = wp->total;
    for (i = 0; i < total; i++, entry++) {
        if (entry->flags & 1) {
            dx = x - entry->position.x;
            dz = z - entry->position.z;
            dy = y - entry->position.y;
            dist = npc_sqrtf(dx * dx + dz * dz);
            npc_sqrtf(dx * dx + dy * dy + dz * dz);
            if (dist < range) {
                found = entry;
            }
        }
    }
    return found;
}
#endif

#ifdef NONMATCHING
FieldBattleData* fbatGetPointer(void) {
    return gp->fbatData;
}
#endif

#ifdef NONMATCHING
void fbatChangeMode(s16 mode) {
    gp->fbatData->mode = mode;
}
#endif

#ifdef NONMATCHING
void fbatSetAttackAnnounce(s32 a1) {
    FirstStrikeInfo* firstStrike = &gp->fbatData->firstStrike;

    firstStrike->enabled = FALSE;
    firstStrike->field_0x4 = a1;
    firstStrike->field_0xC = 0;
    switch (firstStrike->field_0x4) {
        case 0x20000:
        case 0x40000:
        case 0x80000:
        case 0x100000:
        case 0x200000:
        case 0x400000:
        case 0x800000:
        case 0x1000000:
            firstStrike->msg_tag = (char*)str_802C3158; // You struck first!
            firstStrike->type = 2;
            firstStrike->color = (GXColor){ 0xFF, 0x80, 0x80, 0xFF };
            break;
        case 0x10000000:
            firstStrike->msg_tag = (char*)str_802C3168; // Your foe struck first!
            firstStrike->type = 1;
            firstStrike->color = (GXColor){ 0x80, 0x80, 0xFF, 0xFF };
            break;
        default:
            firstStrike->type = 0;
            break;
    }
}
#endif

#ifdef NONMATCHING
void fbatSetAttackAnnounceEnable(void) {
    gp->fbatData->firstStrike.enabled = TRUE;
}
#endif

#ifdef NONMATCHING
static inline f32 mulf(f32 a, f32 b) { return a * b; }
#endif
#ifdef NONMATCHING
void npcStrippedAnnouncePool(f32* f) {
    f[0] = -600.0f;
    f[1] = 600.0f;
}
#endif

#ifdef NONMATCHING
void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param) {
    FirstStrikeInfo* firstStrike = param;
    const char* message;
    f32 x;
    f32 y;
    f32 width;
    f32 shakeX;
    f32 shakeY;

    message = msgSearch(firstStrike->msg_tag);
    x = firstStrike->field_0x10;
    y = firstStrike->field_0x14;
    width = FontGetMessageWidth(message);
    shakeX = x + (f32)(irand(10000) % 5);
    shakeY = y + (f32)(irand(10000) % 5);
    windowDispGX_Waku_col(0, firstStrike->color, mulf(0.1f, shakeX - 10.0f - width / 2.0f),
                          mulf(shakeY, 0.1f), mulf(20.0f + width, 0.1f), 3.2f, 1.0f);
    FontDrawStart();
    FontDrawEdge();
    FontDrawColor((GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
    FontDrawScale(0.1f);
    FontDrawStringShake(mulf(0.1f, x - width / 2.0f), mulf(y - 3.0f, 0.1f), message);
}
#endif

#define FBAT_SUB(d) (((u8*)(d))[2])
#define FBAT_NPC(d) (*(NpcEntry**)((u8*)(d) + 4))
#define FBAT_EVTID(d) (*(s32*)((u8*)(d) + 0xC))

void partyKeyOn(void);
void partyKeyOff(void);
void marioChgTalkMotion(void);
void marioChgStayMotion(void);
BOOL marioChkTalkable(void);
void* fbatHitCheck(u32 flags, void* a1);

#include "eff/eff_small_star.h"
s32 _majinai_effect(EventEntry* event, BOOL isFirstCall);
s32 _check(EventEntry* event, BOOL isFirstCall);
s32 marioStGetSystemLevel(void);
BOOL N_itemPickUpFromFieldCheck(void);
void marioChgMotJump2(void);
f32 marioGetDispDir(void);
void npcKoopaModeEncountCheck(void);

#ifdef NONMATCHING
static inline f32 fbat_camAngle(void) {
    CameraEntry* camera = camGetPtr(CAMERA_3D);
    f32 dx = camera->cameraAt.x - camera->cameraPos.x;
    f32 dz = camera->cameraAt.z - camera->cameraPos.z;
    f32 angle = reviseAngle(NPC_RAD2DEG((f32)atan2(-dx, -dz)));
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}
#endif

#ifdef NONMATCHING
static inline BOOL fbat_setHit(NpcEntry* npc) {
    FieldBattleData* d = gp->fbatData;
    if (d->mode != 1) {
        return FALSE;
    }
    d->mode = 5;
    FBAT_SUB(d) = 0;
    FBAT_NPC(d) = npc;
    d->target = npc;
    return TRUE;
}
#endif

#ifdef NONMATCHING
void fbatEncountCheck(void)
{
  NpcWork *wp = (gp->inBattle) ? (&work.battle) : (&work.field);
  s32 total = wp->total;
  MarioWork *mario = marioGetPtr();
  FieldBattleData *data;
  NpcEntry *npc;
  u32 *kind;
  s32 i;
  NpcEntry *talk;
  f32 best;
  wp->talkTarget = (void *) 0;
  if (((u32) marioStGetSystemLevel()) != 0)
  {
    return;
  }
  if (!(wp->flags & 1))
  {
    if ((!npc->width) && (!npc->width))
    {
    }
    if (marioKeyOffChk() || marioCtrlOffChk())
    {
      return;
    }
  }
  if (N_itemPickUpFromFieldCheck())
  {
    return;
  }
  data = gp->fbatData;
  kind = (u32 *) (((u8 *) data) + 0x10);
  npc = fbatHitCheck(0x13f1, kind);
  if (npc && (data->mode == 1))
  {
    AnimationPose *pose;
    f32 rel;
    f32 ang;
    if (!fbat_setHit(npc))
    {
      return;
    }
    switch (*kind)
    {
      case 0x10000:

      default:
        break;

      case 0x20000:

      case 0x40000:

      case 0x80000:
        marioChgMotJump2();
        if (dbg_battleskip != 1)
      {
        animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
      }
        break;

      case 0x100000:

      case 0x200000:

      case 0x400000:
        if (dbg_battleskip != 1)
      {
        animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
      }
        break;

      case 0x800000:
        if (dbg_battleskip != 1)
      {
        animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
      }
        break;

      case 0x1000000:
        if (dbg_battleskip != 1)
      {
        animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
      }
        break;

    }

    pose = animPoseGetAnimPosePtr(npc->poseId);
    npc->savedDirection = npc->direction;
    npc->direction = angleABf(npc->position.x, npc->position.z, mario->position.x, mario->position.z);
    rel = reviseAngle(-npc->direction);
    rel += -90.0f;
    ang = reviseAngle(fbat_camAngle() - rel);
    if (((ang > 90.0f) && (ang <= 270.0f)) || ((ang < (-90.0f)) && (ang >= (-270.0f))))
    {
      pose->peraTargetRotY = reviseAngle(180.0f + fbat_camAngle());
    }
    else
    {
      pose->peraTargetRotY = fbat_camAngle();
    }
    while ((pose->peraTargetRotY - pose->rotationY) > 180.0f)
    {
      pose->rotationY += 360.0f;
    }

    while ((pose->peraTargetRotY - pose->rotationY) < (-180.0f))
    {
      pose->rotationY -= 360.0f;
    }

    pose->rotationY += 0.75f * (pose->peraTargetRotY - pose->rotationY);
    switch (*kind)
    {
      case 0x20000:

      case 0x40000:

      case 0x80000:

      case 0x100000:

      case 0x200000:

      case 0x400000:

      case 0x800000:

      case 0x1000000:
        effSmallStarEntry(3, 3, npc->position.x, npc->position.y + npc->height, npc->position.z, 0.0f, -1.0f, 0.0f);
        break;

      case 0x10000000:
        effSmallStarEntry(3, 3, mario->position.x, mario->position.y + mario->wPlayerCollisionBox.y, mario->position.z, 0.0f, -1.0f, 0.0f);
        break;

    }

    switch (*kind)
    {
      case 0x20000:

      case 0x40000:

      case 0x80000:

      case 0x100000:

      case 0x200000:

      case 0x400000:

      case 0x800000:

      case 0x1000000:
        if (npc)
      {
        psndSFXOn_3D((char*)str_802C317C, &npc->position);
      }
        break;

      case 0x10000000:
        psndSFXOn_3D((char*)str_802C3198, &mario->position);
        break;

    }

    return;
  }
  best = 1000.0f;
  if (marioChkTalkable() && (!mario->keyOffCount))
  {
    talk = (void *) 0;
    npc = wp->entries;
    for (i = 0; i < total; i++, npc++)
    {
      BOOL hit;
      if (((!(npc->flags & 2)) || (npc->flags & 8)) || (!npc->talkEvt))
      {
        continue;
      }
      hit = 0;
      if ((!(npc->position.y > (mario->position.y + mario->wPlayerCollisionBox.y))) && (!(mario->position.y > (npc->position.y + npc->height))))
      {
        Vec pos;
        f32 dist;
        BOOL facing;
        s32 j;
        f32 dir;
        f32 a;
        f32 yaw;
        pos.x = mario->position.x;
        pos.z = mario->position.z;
        pos.y = npc->position.y;
        dist = PSVECDistance(&pos, &npc->position);
        if ((dist <= ((0.5f * (mario->wPlayerCollisionBox.x + npc->width)) + 10.0f)) && (dist < best))
        {
          talk = npc;
        }
        facing = 0;
        yaw = camGetPtr(CAMERA_3D)->viewYaw;
        dir = reviseAngle(marioGetDispDir() - yaw);
        for (j = 0; j < 3; j++)
        {
          switch (j)
          {
            case 0:
              yaw = camGetPtr(CAMERA_3D)->viewYaw;
              a = reviseAngle(angleABf(mario->position.x, mario->position.z, npc->position.x, npc->position.z) - yaw);
              break;

            case 1:
              yaw = camGetPtr(CAMERA_3D)->viewYaw;
              a = reviseAngle(angleABf(mario->position.x, mario->position.z, npc->position.x + (0.5f * npc->width), npc->position.z) - yaw);
              break;

            default:
              yaw = camGetPtr(CAMERA_3D)->viewYaw;
              a = reviseAngle(angleABf(mario->position.x, mario->position.z, npc->position.x - (0.5f * npc->width), npc->position.z) - yaw);
              break;

          }

          if (a < 180.0f)
          {
            if (!(dir > 180.0f))
            {
              facing = 1;
              break;
            }
          }
          else
            if (!(dir < 180.0f))
          {
            facing = 1;
            break;
          }
        }

        if (facing)
        {
          pos.x = mario->position.x;
          pos.z = mario->position.z;
          pos.y = npc->position.y;
          dist = PSVECDistance(&pos, &npc->position);
          if (!(dist > ((0.5f * (mario->wPlayerCollisionBox.x + npc->width)) + 10.0f)))
          {
            f32 dx = npc->position.x - mario->position.x;
            f32 dz = npc->position.z - mario->position.z;
            f32 s;
            f32 c;
            f32 len;
            f32 hx;
            f32 hy;
            f32 hz;
            f32 nx;
            f32 ny;
            f32 nz;
            sincosf(&s, &c, angleABf(0.0f, 0.0f, dx, dz));
            len = npc_sqrtf((dx * dx) + (dz * dz));
            if (!hitCheckFilter((void *) 0, &hx, &hy, &hz, &len, &nx, &ny, &nz, mario->position.x, mario->position.y + (0.75f * mario->wPlayerCollisionBox.y), mario->position.z, s, 0.0f, c))
            {
              hit = 1;
              if (dist < best)
              {
                best = dist;
                wp->talkTarget = npc;
              }
            }
          }
        }
      }
      if (hit)
      {
        if (!(npc->jumpFlags & 0x20000000))
        {
          MarioWork *m = marioGetPtr();
          npc->jumpFlags |= 0x20000000;
          npc->savedDirection = npc->direction;
          evtStopID(npc->regularEvtId);
          if (!(npc->flags & 0x01000000))
          {
            npc->direction = reviseAngle(angleABf(npc->position.x, npc->position.z, m->position.x, m->position.z));
          }
        }
      }
      else
        if (npc->jumpFlags & 0x20000000)
      {
        npc->jumpFlags &= ~0x20000000;
        if (npc->flags & 0x400000)
        {
          npc->direction = npc->savedDirection;
          evtStartID(npc->regularEvtId);
        }
        else
        {
          npc->interruptFlags |= 0x10000000;
        }
      }
    }

    *((NpcEntry **) (((u8 *) mario) + 0x1D4)) = talk;
    if (wp->talkTarget && (keyGetButtonTrg(0) & 0x100))
    {
      npc = wp->talkTarget;
      data = gp->fbatData;
      if (data->mode != 1)
      {
        return;
      }
      data->mode = 2;
      ((u8 *) data)[2] = 0;
      *((NpcEntry **) (((u8 *) data) + 4)) = npc;
      *((u32 *) npc->field_318) = 0;
      return;
    }
  }
  data = gp->fbatData;
  if (data->mode == 1)
  {
    u32 *kind = (u32 *) (((u8 *) data) + 0x10);
    npc = fbatHitCheck(0x2361, kind);
    if (npc && (data->mode == 1))
    {
      u32 k = *kind;
      FieldBattleData *d = gp->fbatData;
      if (d->mode == 1)
      {
        d->mode = 3;
        ((u8 *) d)[2] = 0;
        *((NpcEntry **) (((u8 *) d) + 4)) = npc;
        *((u32 *) npc->field_318) = k;
      }
      switch (*kind)
      {
        case 0x20000:

        case 0x40000:

        case 0x80000:
          marioChgMotJump2();
          break;

      }

      effSmallStarEntry(3, 3, npc->position.x, npc->position.y + npc->height, npc->position.z, 0.0f, -1.0f, 0.0f);
      return;
    }
  }
  npcKoopaModeEncountCheck();
}
#endif

#ifdef NONMATCHING
void fbatTalkMode(void) {
    FieldBattleData* data = gp->fbatData;
    NpcEntry* npc = FBAT_NPC(data);
    MarioWork* mario = marioGetPtr();
    EventEntry* evt;

    switch (FBAT_SUB(data)) {
        case 0:
            evtStopID(FBAT_NPC(data)->regularEvtId);
            if (!(npc->flags & 0x01000000)) {
                npc->direction = reviseAngle(angleABf(npc->position.x, npc->position.z,
                                                      mario->position.x, mario->position.z));
            }
            marioKeyOff();
            partyKeyOff();
            switch (data->mode) {
                case 3:
                    evt = evtEntry(npc->deadEvent, 0, 0);
                    evt->wNpcEventType = 6;
                    break;
                default:
                    evt = evtEntry(npc->talkEvt, 0, 0);
                    evt->wNpcEventType = 6;
                    marioChgTalkMotion();
                    break;
            }
            evt->ownerNPC = npc;
            FBAT_EVTID(data) = evt->eventId;
            FBAT_SUB(data)++;
            break;
        case 1:
            if (!evtCheckID(FBAT_EVTID(data))) {
                if (!(npc->jumpFlags & 0x20000000)) {
                    evtStartID(FBAT_NPC(data)->regularEvtId);
                    npc->direction = npc->savedDirection;
                }
                if (npc->flags & 0x400) {
                    npc->field_108 = 0;
                }
                if (npc->flags & 0x200) {
                    animPoseSetAnim(npc->poseId, npc->currentAnim, 1);
                }
                marioKeyOn();
                partyKeyOn();
                marioChgStayMotion();
                data->mode = 1;
                npcGetWorkPtrInline()->talkTarget = NULL;
            }
            break;
    }
}
#endif

#define FBAT_U32(d, off) (*(u32*)((u8*)(d) + (off)))
#define NPC_ENEMY_LEVEL(npc) (*(u8*)((u8*)*(void**)(npc)->battleInfo.groupSetup->enemyData + 0xE))

void BattleMajinaiDone(void);
extern s32 _evt_majinai_coin_up_effect[];
void marioChgMoveMotion(void);

#ifdef NONMATCHING
void fbatBattleMode(void) {
    FieldBattleInfo* info;
    NpcWork* wp;
    s32 num;
    EventEntry* evt;
    s32 result;
    s32 mult;
    NpcEntry* cur;
    s32 stolen;
    BOOL skip;
    BOOL win;
    NpcBattleInfo* binfo;
    FieldBattleData* data;
    PouchData* pouch;
    MarioWork* mario;
    data = gp->fbatData;
    cur = data->target;
    pouch = pouchGetPtr();
    mario = marioGetPtr();
    cur->rotation.y = 0.0f;
    switch (FBAT_SUB(data)) {
        case 0:
            if (dbg_battleskip == 1) {
                data->mode = 1;
                break;
            }
            if (!cur->battleInfo.groupSetup) {
                data->mode = 1;
                break;
            }
            if (gp->systemLevelFlags & 0x10) {
                data->mode = 1;
                break;
            }
            if (!cur->deadEvent) {
                data->mode = 1;
                break;
            }
            data->target->interruptFlags &= 0xF00;
            evtStopID(data->target->regularEvtId);
            info = &data->info;
            if (!(cur->battleInfo.field_4 & 0x10000000)) {
                if (pouchEquipCheckBadge(0x142) && NPC_ENEMY_LEVEL(cur) < pouch->level) {
                    skip = TRUE;
                    win = TRUE;
                    goto decided;
                }
                if (pouchEquipCheckBadge(0x141) && (FBAT_U32(data, 0x10) & 0x01FE0000) &&
                    NPC_ENEMY_LEVEL(cur) < pouch->level) {
                    skip = TRUE;
                    win = TRUE;
                    goto decided;
                }
            }
            if (dbg_battleskip == 2) {
                skip = TRUE;
                win = TRUE;
            } else {
                skip = FALSE;
                win = FALSE;
            }
        decided:
            if (!skip) {
                if (!win) {
                    gp->fbatData->firstStrike.enabled = TRUE;
                }
                marioFBattlePrepare();
                seqSetSeq(4, NULL, NULL);
                if (FBAT_U32(data, 0x10) == 0x10000000) {
                    unk_80058374();
                }
                FBAT_SUB(data) = 1;
            } else {
                if (win) {
                    BattleInformationSetResult(info, 2);
                } else {
                    BattleInformationSetResult(info, 5);
                }
                FBAT_SUB(data) = 4;
            }
            break;
        case 1:
            if (gp->inBattle) {
                FBAT_SUB(data)++;
            }
            break;
        case 2:
            if (!gp->inBattle) {
                data->field_54C = 0;
                result = BattleInformationGetResult(&data->info);
                if (pouch->mMerleeNextCurseType == 4 && result == 1) {
                    FBAT_SUB(data) = 3;
                    data->field_54C = 1;
                    evt = evtEntry(_evt_majinai_coin_up_effect, 0, 0);
                    FBAT_U32(data, 0x48) = evt->eventId;
                    BattleMajinaiDone();
                    marioKeyOff();
                    wp = npcGetWorkPtrInline();
                    num = wp->total;
                    for (result = 0, cur = wp->entries; result < num; result++, cur++) {
                        if (cur && (cur->flags & 2) && (cur->flags & 0x10000000)) {
                            cur->jumpFlags |= 0x10000;
                            evtStopID(cur->regularEvtId);
                            animPoseSetLocalTimeRate(cur->poseId, 0.0f);
                        }
                    }
                } else {
                    marioFBattlePost();
                    FBAT_SUB(data) = 4;
                }
            }
            break;
        case 3:
            if (!evtCheckID(FBAT_U32(data, 0x48))) {
                marioKeyOn();
                marioFBattlePost();
                FBAT_U32(data, 0x48) = 0;
                FBAT_SUB(data) = 4;
                wp = npcGetWorkPtrInline();
                num = wp->total;
                for (result = 0, cur = wp->entries; result < num; result++, cur++) {
                            if (cur && (cur->flags & 2) && (cur->flags & 0x10000000) &&
                        (cur->jumpFlags & 0x10000)) {
                        cur->jumpFlags &= ~0x10000;
                        evtStartID(cur->regularEvtId);
                        animPoseSetLocalTimeRate(cur->poseId, 1.0f);
                    }
                }
            }
            break;
        case 4:
            marioChgMoveMotion();
            if (!gp->inBattle) {
                info = &data->info;
                result = BattleInformationGetResult(info);
                stolen = FALSE;
                if (cur->battleInfo.stolenItems[0]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[1]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[2]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[3]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[4]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[5]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[6]) {
                    stolen = TRUE;
                } else if (cur->battleInfo.stolenItems[7]) {
                    stolen = TRUE;
                }
                data->mode = 1;
                if (result == 1 || result == 2) {
                    mult = 1;
                    if (BattleInformationGetResult(info) == 1) {
                        cur->btlCoinDropCount = info->coins;
                    } else if (result == 1) {
                        cur->btlCoinDropCount = cur->baseCoinCount;
                    } else {
                        cur->btlCoinDropCount = 0;
                        mult = 0;
                        goto apply;
                    }
                    if (data->field_54C) {
                        mult = 3;
                    }
                    if (pouchEquipCheckBadge(0x139)) {
                        mult += pouchEquipCheckBadge(0x139);
                    }
                    if (cur->battleInfo.field_4 & 0x100) {
                        mult++;
                    }
                apply:
                    cur->btlCoinDropCount *= mult;
                    if (!stolen) {
                        npcGroupDead(cur, 0);
                        break;
                    }
                    if (cur->flags & 0x400) {
                        cur->field_108 = 0;
                    }
                    cur->wFbatHitCheckRelated = 90;
                    cur->interruptFlags &= ~0x100;
                    cur->interruptFlags |= 0x10000000;
                    if (cur->flags & 0x200) {
                        animPoseSetAnim(cur->poseId, cur->currentAnim, 1);
                    }
                    binfo = &cur->battleInfo;
                    for (result = 0; result < 8; result++) {
                        if (binfo->recoveredItems[result]) {
                            itemFlagOn(itemEntry(NULL, binfo->recoveredItems[result], 11, -1, 0,
                                                 cur->position.x, cur->position.y, cur->position.z),
                                       0x100);
                            binfo->recoveredItems[result] = 0;
                        }
                    }
                } else if (result == 4) {
                    if (cur->flags & 0x400) {
                        cur->field_108 = 0;
                    }
                    cur->interruptFlags |= 0x10000000;
                    marioSetMutekiTime(3000);
                    *(s16*)((u8*)mario + 0x2C0) = sysMsec2Frame(3000);
                    if (cur->flags & 0x200) {
                        animPoseSetAnim(cur->poseId, cur->currentAnim, 1);
                    }
                }
            }
            break;
    }
}
#endif

#ifdef NONMATCHING
void _npcDead(NpcEntry* npc, s32 reason) {
    npc->interruptFlags |= 0x10;
    npc->jumpFlags |= 4;
    npc->koopaEncounterType = reason;
    if (npc->flags & 4) {
        fbatGetPointer()->deadInfo[0].mask |= 1 << npc->setupIndex;
    }
}
#endif

#ifdef NONMATCHING
void _npcGroupDead(NpcEntry* entry, s32 reason) {
    int i;

    if (entry->next) {
        _npcGroupDead(entry->next, reason);
    }
    for (i = 0; i < 4; i++) {
        if (entry->slaves[i]) {
            _npcDead(entry->slaves[i], reason);
        }
    }
    _npcDead(entry, reason);
}
#endif

#ifdef NONMATCHING
void npcGroupDead(NpcEntry* entry, BOOL reason) {
    if (entry->master) {
        entry = entry->master;
    }
    while (entry->prev) {
        entry = entry->prev;
    }
    _npcGroupDead(entry, reason);
}
#endif

#ifdef NONMATCHING
NpcEntry* fbatNpcTalkCheck(void) {
    NpcWork* wp = npcGetWorkPtrInline();
    if (wp->talkTarget && marioChkTalkable()) {
        return wp->talkTarget;
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
void fbatHitCheckAll(void) {
    fbatHitCheck(0x13f1, NULL);
}
#endif

#define FH(p, off, T) (*(T*)((u8*)(p) + (off)))

typedef struct FbatHitResult {
    u32 kind;   // 0x0
    s32 evtId;  // 0x4
    f32 dist;   // 0x8
    u32 bits; // 0xC
} FbatHitResult;

s32 vivianGetStatus(void);
s32 marioGetJabaraState(void);
s32 nokonokoGetStatus(PartyEntry* party);
f32 marioGetAngleKaitenHammer(void);
NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r);
NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle);

#ifdef NONMATCHING
static inline BOOL fbat_canHit(NpcEntry* npc) {
    MarioWork* m = marioGetPtr();
    NpcWork* wp = npcGetWorkPtrInline();
    if (m->flags & 0x82000000) return FALSE;
    if (!(wp->flags & 1) && (m->flags & 0xA)) return FALSE;
    if (FH(gp, 0x164, s32)) return FALSE;
    if (seqGetSeq() != 2) return FALSE;
    if (FH(m, 0x2E, u16) == 0x19) return FALSE;
    if (vivianGetStatus()) return FALSE;
    if (FH(m, 0x2E, u16) == 0x1F || FH(m, 0x2E, u16) == 0x20) return FALSE;
    if (FH(npc, 0x320, u16)) return FALSE;
    return TRUE;
}
#endif

#define FH_NPC_FILTER(f1000, bit)                                                    \
    if (npc == NULL) continue;                                                       \
    if (!(npc->flags & 2)) continue;                                                 \
    if (f1000) { if (!(npc->flags & 8)) continue; } else { if (npc->flags & 8) continue; } \
    if (soft && !(FH(npc, 0x4, u32) & (bit))) continue;                              \
    if (npc->flags & 0x20000000) continue;                                           \
    if (npc->flags & 0x20) continue;                                                 \
    if (FH(npc, 0x1D4, u32) & 4) continue;                                           \
    if (npc->flags & 0x08000000) continue;

#define FH_NPC_FILTER2(f1000, bit)                                                        if (npc == NULL) continue;                                                           if (!(npc->flags & 2)) continue;                                                     if (f1000) { if (!(npc->flags & 8)) continue; } else { if (npc->flags & 8) continue; }     if (soft && !(FH(npc, 0x4, u32) & (bit))) continue;                                  if (npc->flags & 0x20000000) continue;                                               if (npc->flags & 0x20) continue;                                                     if (npc->flags & 0x08000000) continue;                                               if (FH(npc, 0x1D4, u32) & 4) continue;

typedef struct { s32 v[11]; } SinTbl;
#ifdef NONMATCHING
static const SinTbl sSinTbl = {{0, 0, 0, 0, 45, 60, 90, 100, 101, 101, 101}};
#endif

#ifdef NONMATCHING
void* fbatHitCheck(u32 flags, void* a1) {
    NpcEntry* npc = NULL;
    NpcEntry* hit = NULL;
    NpcWork* wp = npcGetWorkPtrInline();
    MarioWork* mario;
    FbatHitResult res;
    f32 dist;
    s32 i;
    u32 soft;
    s32 total;
    PartyEntry* party;

    mario = marioGetPtr();
    res.kind = 0;
    res.dist = 1000.0f;
    res.bits &= ~1;
    soft = flags & 0x2000;
    if (soft) {
        res.bits |= 1;
    }

    if (flags & 0x30) {
        u32 noJump = flags & 0x10;
        total = wp->total;
        npc = wp->entries;
        if (!noJump || mario->unk4C <= 0) {
            if (fbat_canHit(npc)) {
                u32 f1000 = flags & 0x1000;
                u32 f20 = flags & 0x20;
                for (i = 0; i < total; i++, npc++) {
                    f32 dx, dz;
                    if (npc == NULL) continue;
                    if (!(npc->flags & 2)) continue;
                    if (f1000) {
                        if (!(npc->flags & 8)) continue;
                    } else {
                        if (npc->flags & 8) continue;
                    }
                    if (soft && !(FH(npc, 0x4, u32) & 1)) continue;
                    if (npc->flags & 0x20) continue;
                    if (FH(npc, 0x1D4, u32) & 4) continue;
                    if (npc->flags & 0x08000000) continue;
                    if (mario->position.y >= FH(npc, 0x90, f32) + FH(npc, 0x150, f32)) continue;
                    if (mario->position.y + mario->wPlayerCollisionBox.y <= FH(npc, 0x90, f32)) continue;
                    dz = mario->position.z - FH(npc, 0x94, f32);
                    dx = mario->position.x - FH(npc, 0x8C, f32);
                    dist = npc_sqrtf(dx * dx + dz * dz);
                    if (dist > 0.5f * (mario->wPlayerCollisionBox.x + FH(npc, 0x14C, f32))) continue;
                    if (dist >= res.dist) continue;
                    if (noJump && !(FH(npc, 0x1D4, u32) & 0x10000) && mario->unk4C <= 0) {
                        if (FH(npc, 0x2F8, s32) == 0 ||
                            (evtGetPtrID(FH(npc, 0x11C, s32)) ? evtGetPtrID(FH(npc, 0x11C, s32))->wNpcEventType == 5 : 0)) {
                            if (npc->flags & 0x20000000) continue;
                            res.kind = 0x10000;
                            hit = npc;
                            res.dist = dist;
                            if (!soft) fbatSetAttackAnnounce(0x10000);
                        } else if (pouchEquipCheckBadge(0x140)) {
                            res.kind = 0x10000;
                            hit = npc;
                            res.dist = dist;
                            if (!soft) fbatSetAttackAnnounce(0x10000);
                        } else {
                            res.kind = 0x10000000;
                            hit = npc;
                            res.dist = dist;
                            if (!soft) {
                                fbatSetAttackAnnounce(0x10000000);
                            }
                            res.evtId = FH(npc, 0x2F8, s32);
                        }
                    }
                    if (!f20) continue;
                    if ((mario->flags & 0x20000) && !(mario->flags & 0x10000) &&
                        !(npc->flags & 0x20000000)) {
                        hit = npc;
                        res.dist = dist;
                        if (marioGetJabaraState() == 6) {
                            res.kind = 0x20000;
                            if (!soft) fbatSetAttackAnnounce(0x20000);
                        } else if (FH(mario, 0x2E, u16) == 0x10) {
                            res.kind = 0x40000;
                            if (!soft) fbatSetAttackAnnounce(0x40000);
                        } else {
                            res.kind = 0x20000;
                            if (!soft) fbatSetAttackAnnounce(0x20000);
                        }
                    } else if (marioGetJabaraState() == 6 && !(npc->flags & 0x20000000)) {
                        res.kind = 0x20000;
                        hit = npc;
                        res.dist = dist;
                        if (!soft) fbatSetAttackAnnounce(0x20000);
                    }
                }
            }
        }
    }

    if (flags & 0x40) {
        while (hit == NULL) {
            f32 r, angle;
            if ((flags & 0x10) && mario->unk4C > 0) break;
            if (!fbat_canHit(npc)) break;
            if (flags & 1) {
                MarioWork* m;
                s32 v;
                f32 f;
                f32 s1, c1, s2, c2;
                f32 z, x, y;
                u32 f1000;
                if (FH(mario, 0x2E, u16) != 0x12) break;
                r = 1.5f * mario->wPlayerCollisionBox.x;
                angle = reviseAngle(mario->displayDirection - 90.0f + FH(camGetPtr(CAMERA_3D), 0x114, f32));
                m = marioGetPtr();
                animPoseGetAnimPosePtr(FH(m, 0x228 + marioAnimeId() * 4, s32));
                v = FH(m, 0x48, s32);
                if (v > 20) v = 10;
                f = v;
                m = marioGetPtr();
                {
                    SinTbl tbl = sSinTbl;
                    if (f < 0.0f) f = 0.0f;
                    if (f >= 11.0f) f = 10.0f;
                    sincosf(&s1, &c1, angle);
                    sincosf(&s2, &c2, tbl.v[(s32)f]);
                }
                f1000 = flags & 0x1000;
                x = m->position.x + s2 * (s1 * r);
                z = m->position.z + s2 * (c1 * r);
                y = m->position.y + r * c2;
                npc = wp->entries;
                for (i = 0; i < total; i++, npc++) {
                    FH_NPC_FILTER2(f1000, 2)
                    if (!_npcHitCheckSphere(npc, &dist, x, y, z, 12.0f)) continue;
                    if (dist >= res.dist) continue;
                    res.dist = dist;
                    hit = npc;
                    res.kind = 0x100000;
                    if (!soft) fbatSetAttackAnnounce(0x100000);
                    break;
                }
            } else {
                u32 f1000;
                r = 1.5f * mario->wPlayerCollisionBox.x;
                angle = reviseAngle(mario->displayDirection - 90.0f + FH(camGetPtr(CAMERA_3D), 0x114, f32));
                npc = wp->entries;
                f1000 = flags & 0x1000;
                for (i = 0; i < total; i++, npc++) {
                    FH_NPC_FILTER(f1000, 2)
                    if (!_npcHitCheckHammerAllMotion(npc, &dist, r, angle)) continue;
                    if (dist >= res.dist) continue;
                    res.dist = dist;
                    hit = npc;
                    res.kind = 0x100000;
                    if (!soft) fbatSetAttackAnnounce(0x100000);
                    break;
                }
            }
            break;
        }
    }

    if (flags & 0x80) {
        while (hit == NULL) {
            f32 r, angle;
            if ((flags & 0x10) && mario->unk4C > 0) break;
            if (!fbat_canHit(npc)) break;
            if (flags & 1) {
                MarioWork* m;
                f32 s, c, x, y, z;
                u32 f1000;
                if (FH(mario, 0x2E, u16) != 0x13) break;
                angle = marioGetAngleKaitenHammer();
                if (angle < 0.0f) break;
                r = 1.5f * mario->wPlayerCollisionBox.x;
                m = marioGetPtr();
                sincosf(&s, &c, angle);
                f1000 = flags & 0x1000;
                x = s * r + m->position.x;
                z = c * r + m->position.z;
                y = 15.0f + m->position.y;
                npc = wp->entries;
                for (i = 0; i < total; i++, npc++) {
                    FH_NPC_FILTER(f1000, 2)
                    if (!_npcHitCheckSphere(npc, &dist, x, y, z, 12.0f)) continue;
                    if (dist >= res.dist) continue;
                    res.dist = dist;
                    hit = npc;
                    if (pouchGetHammerLv() < 3) {
                        res.kind = 0x200000;
                    } else {
                        res.kind = 0x400000;
                    }
                    if (!soft) fbatSetAttackAnnounce(res.kind);
                    break;
                }
            } else {
                u32 f1000;
                r = 1.5f * mario->wPlayerCollisionBox.x;
                angle = reviseAngle(mario->displayDirection - 90.0f + FH(camGetPtr(CAMERA_3D), 0x114, f32));
                npc = wp->entries;
                f1000 = flags & 0x1000;
                for (i = 0; i < total; i++, npc++) {
                    FH_NPC_FILTER(f1000, 2)
                    if (!_npcHitCheckHammerAllMotion(npc, &dist, r, angle)) continue;
                    if (dist >= res.dist) continue;
                    res.dist = dist;
                    hit = npc;
                    if (pouchGetHammerLv() < 3) {
                        res.kind = 0x200000;
                    } else {
                        res.kind = 0x400000;
                    }
                    if (!soft) fbatSetAttackAnnounce(res.kind);
                    break;
                }
            }
            break;
        }
    }

    if (flags & 0x100) {
        party = partyGetPtr(marioGetPartyId());
        while (hit == NULL) {
            u32 b;
            f32 x, y, z, r;
            u32 f1000;
            if ((flags & 0x10) && mario->unk4C > 0) break;
            if (!fbat_canHit(npc)) break;
            b = flags & 1;
            if (b) {
                s32 st;
                if (party == NULL) break;
                if (FH(party, 0x33, u8) != 2) break;
                if (!(party->flags & 0x100)) break;
                st = nokonokoGetStatus(party);
                if (st < 2 || st > 5) break;
            }
            if (!b) break;
            f1000 = flags & 0x1000;
            r = 0.5f * party->width;
            y = 0.5f * party->height + party->position.y;
            x = party->position.x;
            z = party->position.z;
            npc = wp->entries;
            for (i = 0; i < total; i++, npc++) {
                FH_NPC_FILTER(f1000, 4)
                if (!_npcHitCheckSphere(npc, &dist, x, y, z, r)) continue;
                if (dist >= res.dist) continue;
                res.dist = dist;
                hit = npc;
                res.kind = 0x800000;
                if (!soft) fbatSetAttackAnnounce(0x800000);
                break;
            }
            break;
        }
    }

    if (flags & 0x200) {
        party = partyGetPtr(marioGetPartyId());
        while (hit == NULL) {
            if ((flags & 0x10) && mario->unk4C > 0) break;
            if (!fbat_canHit(npc)) break;
            if (!(flags & 1)) break;
            if (party == NULL) break;
            if (FH(party, 0x33, u8) != 3) break;
            if (!FH(gp->fbatData, 0x54D, u8)) break;
            npc = wp->entries;
            flags &= 0x1000;
            for (i = 0; i < total; i++, npc++) {
                FH_NPC_FILTER(flags, 8)
                if (!_npcHitCheckSphere(npc, &dist, party->position.x, 0.5f * party->height + party->position.y,
                                        party->position.z, 30.0f)) continue;
                if (dist >= res.dist) continue;
                res.dist = dist;
                hit = npc;
                res.kind = 0x1000000;
                if (!soft) fbatSetAttackAnnounce(0x1000000);
                break;
            }
            break;
        }
    }

    if (a1) {
        *(FbatHitResult*)a1 = res;
    }
    return hit;
}
#endif

#ifdef NONMATCHING
void npcStrippedHitPool(f32* f) {
    f[0] = 15.0f;
}
#endif

#ifdef NONMATCHING
NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r) {
    f32 dx = x - npc->position.x;
    f32 dy = y - npc->position.y;
    f32 dz = z - npc->position.z;

    if (y != npc->position.y) {
        if (y >= npc->position.y && y <= npc->position.y + npc->height) {
            dy = 0.0f;
        } else if (y > npc->position.y + npc->height) {
            dy = y - (npc->position.y + npc->height);
        }
    }
    *dist = npc_sqrtf(dx * dx + dy * dy + dz * dz);
    if (*dist < 0.5f * npc->width + r) {
        return npc;
    }
    return NULL;
}
#endif

#ifdef NONMATCHING
NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle) {
    f32 t;
    f32 d;
    float tmpi2;
    NpcEntry* hit;

    for (t = 0.0f; t <= 11.0f; t += 1.0f) {
        f32 f = t;
        MarioWork* mario = marioGetPtr();
        f32 c2, s2, c1, s1;
        f32 x, y, z;
        SinTbl tbl = *(volatile const SinTbl*)&sSinTbl; // FAKE: volatile copy needed for 100% (87.59 with a plain struct copy)

        if (f < 0.0f) {
            f = 0.0f;
        }
        if (f >= 11.0f) {
            f = 10.0f;
        }
        sincosf(&s1, &c1, angle);
        sincosf(&s2, &c2, tbl.v[(s32)f]);
        tmpi2 = mario->position.x + s2 * (s1 * r);
        x = tmpi2;
        z = mario->position.z + s2 * (c1 * r);
        y = mario->position.y + r * c2;
        hit = _npcHitCheckSphere(npc, &d, x, y, z, 12.0f);
        if (hit) {
            break;
        }
    }
    *dist = d;
    return hit;
}
#endif

#ifdef NONMATCHING
BOOL npcCheckInterrupt(NpcEntry* npc) {
    EventEntry* evt;
    u32 flags;

    evtGetPtrID(npc->regularEvtId);
    flags = npc->interruptFlags;
    if (flags & ~0xF00) {
        evt = NULL;
        if ((flags & 0x10) && npc->deadEvent) {
            evt = evtEntry(npc->deadEvent, 0, 0x20);
            evt->wNpcEventType = 8;
            evt->ownerNPC = npc;
        } else if ((flags & 0x10000000) && npc->moveEvent) {
            evt = evtEntry(npc->moveEvent, 0, 0x20);
            evt->wNpcEventType = 1;
            evt->ownerNPC = npc;
        } else if ((flags & 8) && npc->blowEvent) {
            evt = evtEntry(npc->blowEvent, 0, 0x20);
            evt->wNpcEventType = 5;
            evt->ownerNPC = npc;
        } else if ((flags & 1) && npc->findEvent && !(npc->jumpFlags & 0x1000) &&
                   !(npc->flags & 0x200000) && !(flags & 0x100)) {
            evt = evtEntry(npc->findEvent, 0, 0x20);
            evt->wNpcEventType = 2;
            evt->ownerNPC = npc;
        } else if ((flags & 2) && npc->lostEvent && !(npc->jumpFlags & 0x1000) &&
                   !(npc->flags & 0x200000)) {
            evt = evtEntry(npc->lostEvent, 0, 0x20);
            evt->wNpcEventType = 3;
            evt->ownerNPC = npc;
        } else if ((flags & 4) && npc->returnEvent && !(npc->jumpFlags & 0x1000) &&
                   !(npc->flags & 0x200000)) {
            evt = evtEntry(npc->returnEvent, 0, 0x20);
            evt->wNpcEventType = 4;
            evt->ownerNPC = npc;
        }
        if (evt) {
            evtDeleteID(npc->regularEvtId);
            npc->regularEvtId = evt->eventId;
            npc->interruptFlags &= 0xF00;
            npc->jumpFlags &= ~0x1000;
            npc->field_188 = 0;
            npc->moveSpeed = 0.0f;
            return TRUE;
        }
    }
    npc->interruptFlags &= 0xF00;
    npc->jumpFlags &= ~0x1000;
    return FALSE;
}
#endif

#ifdef NONMATCHING
static inline void npcRandField(NpcBattleInfo* info, NpcSetupBattleInfo* setup) {
    s32 i;
    for (i = 0; i < 16; i++) {
        info->field_B0[i] = (u8)setup->field_20[i][0] + irand(setup->field_20[i][1] - setup->field_20[i][0] + 1);
    }
}
#endif

#ifdef NONMATCHING
void npcSetupBattleInfo(NpcEntry* npc, NpcSetupBattleInfo* setup) {
    s32 i;
    s32 num;
    NpcBattleInfo* info;
    NpcBattleSelect* select;
    BattleUnitSetup* unit;
    ItemDropData* table;
    ItemDropData* drop;
    s32 total;

    info = &npc->battleInfo;
    memset(info, 0, sizeof(NpcBattleInfo));
    memset(info->recoveredItems, 0, sizeof(info->recoveredItems));
    if (setup && setup->name) {
        info->field_AC = setup->field_1C;
        switch (info->field_AC) {
            case 0:
            default:
                npcRandField(info, setup);
                break;
            case 1:
            case 2:
                break;
        }
        info->field_4 = setup->field_18;
        info->fixedItem = setup->fixedItem;
        info->itemDropped = 0;
        info->heartsDropped = 0;
        info->flowersDropped = 0;
        info->field_C0 = setup->field_40;
        if (setup->swFlag >= -EVTDAT_GSWF_BASE && setup->swFlag <= EVTDAT_GSWF_MAX) {
            if (swGet(setup->swFlag + EVTDAT_GSWF_BASE)) {
                select = setup->altSelect;
            } else {
                select = setup->select;
            }
        } else {
            select = setup->select;
        }
        info->groupSetup = NULL;
        if (select) {
            NpcBattleSelect* p;
            s32 w;

            total = 0;
            for (p = select; (w = p->weight) > 0; p++) {
                total += w;
            }
            if (total > 0) {
                total = irand(total);
                while (TRUE) {
                    if ((total -= select->weight) < 0) {
                        break;
                    }
                    select++;
                }
                info->groupSetup = select->groupSetup;
                info->stageData = select->stageData;
            }
        }
        if (info->groupSetup) {
            num = info->groupSetup->numEnemies;
            unit = info->groupSetup->enemyData;
            memset(info->heldItems, 0, sizeof(info->heldItems));
            for (i = 0; i < num; unit++, i++) {
                table = unit->itemDropTable;
                if (table) {
                    total = 0;
                    for (drop = table; drop->holdWeight > 0 || drop->type; drop++) {
                        total += drop->holdWeight;
                    }
                    if (total > 0) {
                        total = irand(total);
                        while (TRUE) {
                            if ((total -= table->holdWeight) < 0) {
                                info->heldItems[i] = table->type;
                                info->itemDropLists[i] = unit->itemDropTable;
                                break;
                            }
                            table++;
                        }
                    }
                }
            }
        }
        npc->baseCoinCount = 0;
        if (info->groupSetup) {
            npc->baseCoinCount = info->groupSetup->enemyData->mUnitKindParams->baseCoin;
        }
        npc->flags |= 0x10000000;
    }
}
#endif

#ifdef NONMATCHING
void npcSetBattleInfo(NpcEntry* npc, s32 battleInfoId) {
    NpcSetupBattleInfo* setup;
    char areaName[4];
    s32 i;

    if (battleInfoId == -1) {
        setup = NULL;
    } else {
        areaName[0] = gp->currentMapName[0];
        areaName[1] = gp->currentMapName[1];
        areaName[2] = gp->currentMapName[2];
        areaName[3] = '\0';
        setup = areaDataPtr(areaName)->btlSetupTbl;
        for (i = battleInfoId; i > 0; i--) {
            setup++;
        }
    }
    npcSetupBattleInfo(npc, setup);
    for (i = 0; i < 4; i++) {
        if (npc->slaves[i]) {
            npc->slaves[i]->battleInfo = npc->battleInfo;
        }
    }
}
#endif

#ifdef NONMATCHING
void npcStopForEvent(void) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;
    for (i = 0; i < total; i++, entry++) {
        npcStopForOneEvent(entry);
    }
}
#endif

#ifdef NONMATCHING
void npcStopForOneEvent(NpcEntry* npc) {
    if (npc && npc->flags & 2 && npc->flags & 0x10000000) {
        npc->jumpFlags |= 0x10000;
        evtStopID(npc->regularEvtId);
        animPoseSetLocalTimeRate(npc->poseId, 0.0f);
    }
}
#endif

#ifdef NONMATCHING
void npcStartForEvent(void) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;
    if (total) {
    }
    for (i = 0; i < total; i++, entry++) {
        npcStartForOneEvent(entry);
    }
}
#endif

#ifdef NONMATCHING
void npcStartForOneEvent(NpcEntry* npc) {
    if (npc && npc->flags & 2 && npc->flags & 0x10000000 && npc->jumpFlags & 0x10000) {
        npc->jumpFlags &= ~0x10000;
        evtStartID(npc->regularEvtId);
        animPoseSetLocalTimeRate(npc->poseId, 1.0f);
    }
}
#endif

#ifdef NONMATCHING
void npcSetColor(const char* name, GXColor color) {
    npcNameToPtr(name)->color = color;
}
#endif

#ifdef NONMATCHING
void npcBlurOn(const char* name) {
    NpcEntry* npc = npcNameToPtr(name);

    npc->flags |= 0x100;
    npc->positionHistory[0] = npc->position;
    npc->positionHistory[1] = npc->position;
    npc->positionHistory[2] = npc->position;
    npc->positionHistory[3] = npc->position;
    npc->positionHistory[4] = npc->position;
}
#endif

#ifdef NONMATCHING
void npcBlurOff(const char* name) {
    npcNameToPtr(name)->flags &= ~0x100;
}
#endif

#ifdef NONMATCHING
s32 npcGetBtlSetupWork(NpcEntry* npc, s32 index) {
    return npc->battleInfo.btlSetupWork[index];
}
#endif

#ifdef NONMATCHING
void npcSetBtlSetupWork(NpcEntry* npc, s32 index, s32 value) {
    npc->battleInfo.btlSetupWork[index] = value;
}
#endif

#ifdef NONMATCHING
void npcSetSlave(NpcEntry* npc, NpcEntry* slave, s32 id) {
    slave->master = npc;
    npc->slaves[id] = slave;
}
#endif

#ifdef NONMATCHING
void npcSetLink(NpcEntry* npc, NpcEntry* other) {
    npc->next = other;
    other->prev = npc;
}
#endif

#ifdef NONMATCHING
NpcTerritoryType dbGetDefData(NpcTerritoryInfo* info, const char* description) {
    NpcTerritoryType type;

    type = NPC_TERRITORY_TYPE_NOTHING;
    while (TRUE) {
        if (!info->description) {
            break;
        }
        if (!strcmp(info->description, description)) {
            type = info->type;
            break;
        }
        info++;
    }
    return type;
}
#endif

#ifdef NONMATCHING
void npcExecAllInitEvt(void) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;
    EventEntry* evt;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;

    for (i = 0; i < total; i++, entry++) {
        if (entry && entry->flags & 1) {
            if (entry->initEvent) {
                if (entry->initEvtId) {
                    evtDeleteID(entry->initEvtId);
                }
                evt = evtEntry(entry->initEvent, 0, 0);
                evt->wNpcEventType = 0;
                evt->ownerNPC = entry;
                entry->initEvtId = evt->eventId;
            } else {
                entry->initEvtId = 0;
            }
        }
    }
}
#endif

#ifdef NONMATCHING
BOOL npcWaitAllInitEvtEnd(void) {
    NpcWork* wp;
    BOOL done;
    s32 i;
    s32 total;
    NpcEntry* entry;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    done = TRUE;
    entry = wp->entries;

    for (i = 0; i < total; i++, entry++) {
        if (entry && entry->flags & 1 && !(entry->flags & 2)) {
            if (entry->initEvtId) {
                done = FALSE;
                if (!evtCheckID(entry->initEvtId)) {
                    entry->initEvtId = 0;
                    entry->flags |= 2;
                }
            } else {
                entry->flags |= 2;
            }
        }
    }
    return done;
}
#endif

#ifdef NONMATCHING
void npcExecAllReglEvt(void) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;
    EventEntry* evt;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;

    for (i = 0; i < total; i++, entry++) {
        if (entry && entry->flags & 1 && entry->moveEvent) {
            if (entry->regularEvtId) {
                evtDeleteID(entry->regularEvtId);
            }
            evt = evtEntry(entry->moveEvent, 0, 0x20);
            evt->wNpcEventType = 1;
            evt->ownerNPC = entry;
            entry->regularEvtId = evt->eventId;
        }
    }
}
#endif

#ifdef NONMATCHING
USER_FUNC(_check) {
    s32* args = event->args;
    s32 index = *args++;

    if (pouchGetPtr()->mMerleeCurseUsesRemaining) {
        evtSetValue(event, index, 0);
    } else {
        evtSetValue(event, index, 1);
    }
    return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(_majinai_effect) {
    MarioWork* mario = marioGetPtr();
    EffectEntry* effect;

    if (isFirstCall) {
        event->userdatap[0] = effMajinaiEntry(0, mario->position.x, mario->position.y + mario->wPlayerCollisionBox.y + 16.0f, mario->position.z);
        effect = event->userdatap[0];
        ((f32*)effect->userdata)[4] = 0.8f;
        effSetName(event->userdatap[0], (char*)str_802C3128);
    }
    if (event->userdata[0] && effNameToPtr((char*)str_802C3128)) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}
#endif

EVT_BEGIN(evt_majinai_effect_se_fld)
    CALL(btlevtcmd_ftomsec, 29, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C2FC8), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 200, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C2FE4), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 90, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3000), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 80, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C301C), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 5, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3038), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_majinai_effect_se_btl)
    CALL(btlevtcmd_ftomsec, 29, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3054), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 200, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C3070), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 90, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C308C), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 80, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C30A8), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 5, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING((char*)str_802C30C4), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(_evt_majinai_coin_up_effect)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    SPAWN_EVENT(evt_majinai_effect_se_fld)
    CALL(_majinai_effect)
    CALL(evt_msg_print, 0, PTR((char*)str_802C30E0), 0, 0)
    CALL(_check, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, PTR((char*)str_802C30F0), 0, 0)
    END_IF
    RETURN
EVT_END()

#ifdef NONMATCHING
void npcGetBackItemEntry(NpcEntry* npc) {
    NpcBattleInfo* info = &npc->battleInfo;
    s32 i;

    for (i = 0; i < 8; i++) {
        if (info->recoveredItems[i]) {
            itemFlagOn(itemEntry(NULL, info->recoveredItems[i], 11, -1, 0, npc->position.x,
                                 npc->position.y, npc->position.z),
                       0x100);
            info->recoveredItems[i] = 0;
        }
    }
}
#endif

#ifdef NONMATCHING
void npcClearDeadInfo(void) {
    memset(gp->fbatData->deadInfo, 0, sizeof(gp->fbatData->deadInfo));
}
#endif

#ifdef NONMATCHING
void npcStrippedKoopaPool(f32* f, const char** p) {
    f[0] = 60.0f;
    f[1] = 365.0f;
    p[0] = (char*)str_802C3104;
    p[1] = (char*)str_802C310C;
}
#endif

#ifdef NONMATCHING
void npcKoopaModeMain(void) {
    s32 jump;
    u8* fb2;
    s32 fire;
    MarioWork* mario;
    fbatEncountCheck();
    fb2 = *(u8**)((u8*)gp + 0x168);
    mario = marioGetPtr();
    jump = 0;
    fire = jump;
    if (*((s8*)mario + 0x3c) == 2) jump = kpaJumpChk();
    if (*((s8*)mario + 0x3c) == 2) fire = kpaFireAttackCheck();
    if (jump) {
        if (*(s32*)(fb2 + 0x57c) > 0 && *(s32*)(fb2 + 0x578) >= 2) {
            Vec pos = *(Vec*)((u8*)mario + 0x8c);
            pos.y += 60.0f;
            kpaAddScorePos(*(s32*)(fb2 + 0x57c), &pos);
        }
        *(s32*)(fb2 + 0x578) = 0;
        *(s32*)(fb2 + 0x57c) = 0;
    }
    if (!fire) {
        *(s32*)(fb2 + 0x574) = 0;
    }
}
#endif

#ifdef NONMATCHING
void npcKoopaModeEncountCheck(void) {
    NpcWork* wp;
    FieldBattleData* data;
    s32 i;
    s32 total;
    NpcEntry* entry;

    data = gp->fbatData;
    wp = npcGetWorkPtrInline();
    total = wp->total;

    if (data->mode == 1) {
        entry = wp->entries;
        for (i = 0; i < total; i++, entry++) {
            if (entry && entry->flags & 1 && entry->flags & 0x8000000 && !(entry->jumpFlags & 4)) {
                switch (kpaEnemyHitChk(entry->position.x, entry->position.y, entry->position.z, entry->height,
                                       entry->width)) {
                    case 1:
                        if (!(entry->field_31E & 1)) {
                            npcGroupDead(entry, 1);
                        }
                        break;
                    case 2:
                        if (!(entry->field_31E & 2)) {
                            npcGroupDead(entry, 2);
                        }
                        break;
                    case 3:
                        if (!(entry->field_31E & 4)) {
                            npcGroupDead(entry, 4);
                        }
                        break;
                    case 4:
                        kpaPowDown();
                        break;
                    default:
                        if (!(entry->field_31E & 0x10) && entry->field_0x300 &&
                            !strcmp(hitGetName(entry->field_0x300), (char*)str_802C30FC)) {
                            npcGroupDead(entry, 0x10);
                        }
                        break;
                }
            }
        }
    }
}
#endif

#ifdef NONMATCHING
s32 npcKoopaModeMobjBoundDeadCheck(HitEntry* hit) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;
    s32 count;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    count = 0;

    if (hit == NULL) {
        return 0;
    }
    entry = wp->entries;
    for (i = 0; i < total; i++, entry++) {
        if (entry && entry->flags & 1 && entry->flags & 0x8000000 && !(entry->jumpFlags & 4) &&
            !(entry->field_31E & 8) && entry->field_0x300 == hit) {
            npcGroupDead(entry, 8);
            count++;
        }
    }
    return count;
}
#endif

#ifdef NONMATCHING
void fbatSandersBombTriggerOn(void) {
    gp->fbatData->sandersBombTrigger = TRUE;
}
#endif

#ifdef NONMATCHING
s32 npcCalcScore(NpcEntry* npc) {
    FieldBattleData* data = gp->fbatData;
    s32 score = 300;
    Vec pos = npc->position;

    pos.y += npc->tribe->height;
    if (npc->koopaEncounterType == 0x10) {
        score = 0;
    } else {
        if (npc->koopaEncounterType == 8) {
            score = 400;
        }
        if (kpaMutekiCheck()) {
            score += 100;
        }
        if (npc->koopaEncounterType == 2) {
            data->field_574++;
            score *= data->field_574;
        }
        if (npc->koopaEncounterType == 1) {
            data->field_578++;
            data->field_57C += score;
        }
        if (score > 9999) {
            score = 10000;
        }
    }
    if (score > 0) {
        kpaAddScorePos(score, &pos);
    }
    return score;
}
#endif

#ifdef NONMATCHING
BOOL npcCheckBlow(NpcEntry* npc) {
    Vec pos;

    if (npc->flags & 0x20000000) {
        return FALSE;
    }
    if (npc->flags & 0x20) {
        return FALSE;
    }
    pos = npc->position;
    if (cloudGetBreathPower(pos, npc->width) > 0.0f) {
        return TRUE;
    }
    pos = npc->position;
    pos.y -= npc->height / 2.0f;
    if (cloudGetBreathPower(pos, npc->width) > 0.0f) {
        return TRUE;
    }
    pos = npc->position;
    pos.y -= npc->height;
    if (cloudGetBreathPower(pos, npc->width) > 0.0f) {
        return TRUE;
    }
    return FALSE;
}
#endif

#ifdef NONMATCHING
BOOL N_fbatPreventMarioEventChk(void) {
    s32 mode = gp->fbatData->mode;
    if (mode != 0 && mode != 1 && mode != 8) {
        return TRUE;
    }
    return FALSE;
}
#endif

#pragma force_active on
__declspec(section ".data") u32 gap_05_8030543C_data[1] = {0};
#pragma force_active reset


// prototypes for asm stopgap forward references
BOOL N_fbatPreventMarioEventChk(void);
BOOL npcCheckBlow(NpcEntry* npc);
s32 npcCalcScore(NpcEntry* npc);
void fbatSandersBombTriggerOn(void);
s32 npcKoopaModeMobjBoundDeadCheck(HitEntry* hit);
void npcKoopaModeEncountCheck(void);
void npcClearDeadInfo(void);
void npcGetBackItemEntry(NpcEntry* npc);
s32 _majinai_effect(EventEntry* event, BOOL isFirstCall);
s32 _check(EventEntry* event, BOOL isFirstCall);
void npcExecAllReglEvt(void);
BOOL npcWaitAllInitEvtEnd(void);
void npcExecAllInitEvt(void);
NpcTerritoryType dbGetDefData(NpcTerritoryInfo* info, const char* description);
void npcSetLink(NpcEntry* npc, NpcEntry* other);
void npcSetSlave(NpcEntry* npc, NpcEntry* slave, s32 id);
void npcSetBtlSetupWork(NpcEntry* npc, s32 index, s32 value);
s32 npcGetBtlSetupWork(NpcEntry* npc, s32 index);
void npcBlurOff(const char* name);
void npcBlurOn(const char* name);
void npcSetColor(const char* name, GXColor color);
void npcStartForOneEvent(NpcEntry* npc);
void npcStartForEvent(void);
void npcStopForOneEvent(NpcEntry* npc);
void npcStopForEvent(void);
void npcSetBattleInfo(NpcEntry* npc, s32 battleInfoId);
void npcSetupBattleInfo(NpcEntry* npc, NpcSetupBattleInfo* setup);
BOOL npcCheckInterrupt(NpcEntry* npc);
NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle);
NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r);
void* fbatHitCheck(u32 flags, void* a1);
void fbatHitCheckAll(void);
NpcEntry* fbatNpcTalkCheck(void);
void npcGroupDead(NpcEntry* entry, BOOL reason);
void _npcGroupDead(NpcEntry* entry, s32 reason);
void _npcDead(NpcEntry* npc, s32 reason);
void fbatBattleMode(void);
void fbatTalkMode(void);
void fbatEncountCheck(void);
void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param);
void fbatSetAttackAnnounceEnable(void);
void fbatSetAttackAnnounce(s32 a1);
void fbatChangeMode(s16 mode);
FieldBattleData* fbatGetPointer(void);
NpcEntry* npcNearDistCheck(f32 x, f32 y, f32 z, f32 range);
HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz);
f32 npcTransRytoFaceDir(NpcEntry* npc);
void npcTuningRy(NpcEntry* npc, f32 angle);
void npcMoveG(NpcEntry* npc);
BOOL npcCheckHitMarioSide(NpcEntry* npc);
void npcSetStayPose(const char* name);
void npcSetTalkPose(const char* name);
void npcSetMarioAutoTalkPose(const char* stayPose, const char* talkPose);
NpcEntry* npcNameToPtr_NoAssert(const char* name);
NpcEntry* npcNameToPtr(const char* name);
void npcMain(void);
void npcDeleteGroup(NpcEntry* entry);
void _npcDeleteGroup(NpcEntry* entry);
void npcDelete(NpcEntry* entry);
NpcTribeInfo* npcGetTribe(const char* tribeName);
s32 npcEntry(const char* a1, const char* animName);
s32 npcGetReactionOfLivingBody(BOOL inBattle);
void npcReset(BOOL inBattle);
void npcInit(void);
void npcDisp_blur(CameraId camId, void* param);
void npcDisp_offscreen(CameraId camId, void* param);
void npcDisp_offscreen_xlu(CameraId camId, void* param);
void npcDisp(CameraId camId, void* param);
void npcDisp_xlu(CameraId cameraId, void* param);
void mtx_setup(NpcEntry* entry, Mtx mtx, s32 history);
void npcRecoveryFieldNpc(void);
void npcReleaseFieldNpc(void);
NpcWork* npcGetWorkPtr(void);
#ifndef NONMATCHING
// ASM-STOPGAP: npcGetWorkPtr (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c2f78[3] = { 0.0f, 0.0f, 0.0f };
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802c2f84[3] = { 1.0f, 1.0f, 1.0f };
__declspec(section ".rodata") const f32 vec3_802c2f90[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const u32 dat_802c2f9c[11] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000002D, 0x0000003C, 0x0000005A, 0x00000064, 0x00000065, 0x00000065, 0x00000065 };
__declspec(section ".rodata") const char str_802C2FC8[] = "SFX_EVT_FLD_INCANT_CUBE1\000\000\000";
__declspec(section ".rodata") const char str_802C2FE4[] = "SFX_EVT_FLD_INCANT_CUBE2\000\000\000";
__declspec(section ".rodata") const char str_802C3000[] = "SFX_EVT_FLD_INCANT_CUBE3\000\000\000";
__declspec(section ".rodata") const char str_802C301C[] = "SFX_EVT_FLD_INCANT_CUBE4\000\000\000";
__declspec(section ".rodata") const char str_802C3038[] = "SFX_EVT_FLD_INCANT_CUBE5\000\000\000";
__declspec(section ".rodata") const char str_802C3054[] = "SFX_EVT_BTL_INCANT_CUBE1\000\000\000";
__declspec(section ".rodata") const char str_802C3070[] = "SFX_EVT_BTL_INCANT_CUBE2\000\000\000";
__declspec(section ".rodata") const char str_802C308C[] = "SFX_EVT_BTL_INCANT_CUBE3\000\000\000";
__declspec(section ".rodata") const char str_802C30A8[] = "SFX_EVT_BTL_INCANT_CUBE4\000\000\000";
__declspec(section ".rodata") const char str_802C30C4[] = "SFX_EVT_BTL_INCANT_CUBE5\000\000\000";
__declspec(section ".rodata") const char str_802C30E0[] = "msg_mj_coin_up\000";
__declspec(section ".rodata") const char str_802C30F0[] = "msg_mj_last";
__declspec(section ".rodata") const char str_802C30FC[] = "a_magu\000";
__declspec(section ".rodata") const char str_802C3104[] = "kpa_03\000";
__declspec(section ".rodata") const char str_802C310C[] = "SFX_KUPPA_3RD_WATER_FALL1\000\000";
__declspec(section ".rodata") const char str_802C3128[] = "mjef_coinup";
__declspec(section ".rodata") const u32 gap_04_802C3134_rodata[1] = { 0x00000000 };
__declspec(section ".rodata") const f64 double_0p5_802c3138 = 0.5;
__declspec(section ".rodata") const f64 double_3_802c3140 = 3;
__declspec(section ".rodata") const f64 double_0_802c3148 = 0;
__declspec(section ".rodata") const f64 double_to_int_802c3150 = 4503601774854144;
__declspec(section ".rodata") const char str_802C3158[] = "fb_sensei_shita";
__declspec(section ".rodata") const char str_802C3168[] = "fb_sensei_sareta\000\000\000";
__declspec(section ".rodata") const char str_802C317C[] = "SFX_BTL_FLD_ENEMY_DAMAGED1\000";
__declspec(section ".rodata") const char str_802C3198[] = "SFX_BTL_FLD_MARIO_DAMAGED1\000";
__declspec(section ".rodata") const f64 double_to_int_mask_802c31b8 = 4503599627370496;
__declspec(section ".rodata") const char str_802C31C0[] = "(^x^)party\000";
__declspec(section ".rodata") const char str_802C31CC[] = "extparty\000\000\000";
__declspec(section ".rodata") const f64 double_0p75_802c31d8 = 0.75;
__declspec(section ".rodata") const char str_802C31E0[] = "c_luigi";
#pragma force_active reset
#pragma force_active on
__declspec(section ".sdata2") const u32 dat_80419b88 = 0xFFFFFF00;
__declspec(section ".sdata2") const u32 dat_80419b8c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419b90 = 0xFF8080FF;
__declspec(section ".sdata2") const u32 dat_80419b94 = 0x8080FFFF;
__declspec(section ".sdata2") const u32 dat_80419b98 = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_0_80419b9c = 0.0f;
__declspec(section ".sdata2") const f32 float_0p5_80419ba0 = 0.5f;
__declspec(section ".sdata2") const f32 float_60_80419ba4 = 60.0f;
__declspec(section ".sdata2") const f32 float_365_80419ba8 = 365.0f;
__declspec(section ".sdata2") const f32 float_16_80419bac = 16.0f;
__declspec(section ".sdata2") const f32 float_0p8_80419bb0 = 0.8f;
__declspec(section ".sdata2") const f32 float_1_80419bb4 = 1.0f;
__declspec(section ".sdata2") const f32 float_10_80419bb8 = 10.0f;
__declspec(section ".sdata2") const f32 float_11_80419bbc = 11.0f;
__declspec(section ".sdata2") const f32 float_12_80419bc0 = 12.0f;
__declspec(section ".sdata2") const f32 float_15_80419bc4 = 15.0f;
__declspec(section ".sdata2") const f32 float_1000_80419bc8 = 1000.0f;
__declspec(section ".sdata2") const f32 float_1p5_80419bcc = 1.5f;
__declspec(section ".sdata2") const f32 float_90_80419bd0 = 90.0f;
__declspec(section ".sdata2") const f32 float_30_80419bd4 = 30.0f;
__declspec(section ".sdata2") const f32 float_neg90_80419bd8 = -90.0f;
__declspec(section ".sdata2") const f32 float_rad2deg_80419bdc = 57.29579f;
__declspec(section ".sdata2") const f32 float_360_80419be0 = 360.0f;
__declspec(section ".sdata2") const f32 float_270_80419be4 = 270.0f;
__declspec(section ".sdata2") const f32 float_neg270_80419be8 = -270.0f;
__declspec(section ".sdata2") const f32 float_180_80419bec = 180.0f;
__declspec(section ".sdata2") const f32 float_neg180_80419bf0 = -180.0f;
__declspec(section ".sdata2") const f32 float_0p75_80419bf4 = 0.75f;
__declspec(section ".sdata2") const f32 float_neg1_80419bf8 = -1.0f;
__declspec(section ".sdata2") const f32 float_0p1_80419bfc = 0.1f;
__declspec(section ".sdata2") const f32 float_20_80419c00 = 20.0f;
__declspec(section ".sdata2") const f32 float_3p2_80419c04 = 3.2f;
__declspec(section ".sdata2") const f32 float_3_80419c08 = 3.0f;
__declspec(section ".sdata2") const f32 float_neg600_80419c0c = -600.0f;
__declspec(section ".sdata2") const f32 float_600_80419c10 = 600.0f;
__declspec(section ".sdata2") const f32 float_0p2_80419c14 = 0.2f;
__declspec(section ".sdata2") const f32 float_100_80419c18 = 100.0f;
__declspec(section ".sdata2") const f32 float_0p4_80419c1c = 0.4f;
__declspec(section ".sdata2") const f32 float_45_80419c20 = 45.0f;
__declspec(section ".sdata2") const f32 float_neg980_80419c24 = -980.0f;
__declspec(section ".sdata2") const f32 float_0p15_80419c28 = 0.15f;
__declspec(section ".sdata2") const f32 float_neg1000_80419c2c = -1000.0f;
__declspec(section ".sdata2") const f32 float_5_80419c30 = 5.0f;
__declspec(section ".sdata2") const f32 float_40_80419c34 = 40.0f;
__declspec(section ".sdata2") const f32 float_6p2832_80419c38 = 6.2831855f;
__declspec(section ".sdata2") const f32 float_0p00761_80419c3c = 0.00761f;
__declspec(section ".sdata2") const f32 float_0p16605_80419c40 = 0.16605f;
__declspec(section ".sdata2") const f32 float_3p1416_80419c44 = 3.1415927f;
__declspec(section ".sdata2") const f32 float_1p5708_80419c48 = 1.5707964f;
__declspec(section ".sdata2") const f32 float_4p7124_80419c4c = 4.712389f;
__declspec(section ".sdata2") const f32 float_0p03705_80419c50 = 0.03705f;
__declspec(section ".sdata2") const f32 float_0p4967_80419c54 = 0.4967f;
__declspec(section ".sdata2") const f32 float_4_80419c58 = 4.0f;
__declspec(section ".sdata2") const f32 float_2_80419c5c = 2.0f;
__declspec(section ".sdata2") const f32 float_160_80419c60 = 160.0f;
__declspec(section ".sdata2") const char str_80419C64[8] = "party\0\0";
__declspec(section ".sdata2") const char str_80419C6C[8] = "mario\0\0";
__declspec(section ".sdata2") const f32 float_1E06_80419c74 = 1000000.0f;
__declspec(section ".sdata2") const f32 float_0p05_80419c78 = 0.05f;
__declspec(section ".sdata2") const f32 float_0p25_80419c7c = 0.25f;
__declspec(section ".sdata2") const f32 float_neg2_80419c80 = -2.0f;
__declspec(section ".sdata2") const f32 float_5000_80419c84 = 5000.0f;
__declspec(section ".sdata2") const f32 float_10000_80419c88 = 10000.0f;
__declspec(section ".sdata2") const f32 float_1p33_80419c8c = 1.33f;
__declspec(section ".sdata2") const char str_80419C90[8] = "hoshi\0\0";
__declspec(section ".sdata2") const char str_80419C98[8] = "M_I_2\0\0";
__declspec(section ".sdata2") const f32 float_deg2rad_80419ca0 = 0.017453292f;

s32 BattleInformationGetResult(FieldBattleInfo* info);
void BattleInformationSetResult(FieldBattleInfo* info, u32 result);
void FontDrawColor(GXColor color);
void FontDrawStart(void);
u16 FontGetMessageWidth(const char* message);
void GXClearBoundingBox(void);
void GXReadBoundingBox(u16* left, u16* top, u16* right, u16* bottom);
void PSMTX44MultVec(const Mtx44 m, const Vec* src, Vec* dst);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXIdentity(Mtx m);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScaleApply(const Mtx src, Mtx dst, f32 xS, f32 yS, f32 zS);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 xT, f32 yT, f32 zT);
f32 PSVECDistance(const Vec* a, const Vec* b);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void __cvt_sll_flt();
void __div2i();
void* __memAlloc(HEAP_TYPE heap, u32 size);
void _npcDead(NpcEntry* npc, s32 reason);
void _npcGroupDead(NpcEntry* entry, s32 reason);
f32 angleABf(f32 x1, f32 y1, f32 x2, f32 y2);
void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
s32 animPoseEntry(const char* animName, s32 type);
AnimationPoseData* animPoseGetAnimBaseDataPtr(s32 poseId);
AnimationPose* animPoseGetAnimPosePtr(s32 poseId);
AnimTableEntry* animPoseGetCurrentAnim(s32 poseId);
f32 animPoseGetHeight(s32 poseId);
u32 animPoseGetMaterialFlag(s32 poseId);
f32 animPoseGetRadius(s32 poseId);
s32 animPoseGetVivianType(s32 poseId);
void animPoseMain(s32 poseId);
void animPosePeraOn(s32 poseId);
void animPoseRelease(s32 poseId);
void animPoseSetAnim(s32 poseId, const char* animName, BOOL reset);
void animPoseSetLocalTimeRate(s32 poseId, f32 localTimeRate);
void animPoseSetMaterialEvtColor(s32 poseId, GXColor color);
void animPoseSetMaterialFlagOff(s32 poseId, u32 mask);
void animPoseSetMaterialFlagOn(s32 poseId, u32 mask);
void animPoseSetMaterialLightFlagOn(s32 poseId, u32 mask);
void animPoseWorldMatrixEvalOn(s32 poseId);
void animPoseWorldPositionEvalOn(s32 poseId);
AreaData* areaDataPtr(const char* areaName);
CameraEntry* camGetCurPtr(void);
CameraEntry* camGetPtr(CameraId cameraId);
f32 compAngle(f32 angle1, f32 angle2);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
DispEntry* dispGetCurWork(void);
EffectEntry* effMajinaiEntry(s32 type, f32 x, f32 y, f32 z);
EffectEntry* effNameToPtr(const char* name);
void effSetName(EffectEntry* effect, const char* name);
EffectEntry* effSmallStarEntry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5, f32 arg6,
                               f32 arg7);
BOOL evtCheckID(s32 eventId);
void evtDeleteID(s32 eventId);
EventEntry* evtEntry(void* evtCode, u8 priority, u8 flags);
EventEntry* evtGetPtrID(s32 eventId);
s32 evtSetValue(EventEntry* entry, s32 index, s32 value);
void evtStartID(s32 eventId);
void evtStopID(s32 eventId);
FieldBattleData* fbatGetPointer(void);
HitEntry* hitCheckAttr(s32 user0, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX, f32* hitNY, f32* hitNZ,
                       f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz);
HitEntry* hitCheckFilter(HitFilterCallback callback, f32* hitX, f32* hitY, f32* hitZ, f32* distance, f32* hitNX,
                         f32* hitNY, f32* hitNZ, f32 x, f32 y, f32 z, f32 nx, f32 ny, f32 nz);
const char* hitGetName(HitEntry* hit);
f32 intplGetValue(s32 mode, s32 currStep, s32 steps, f32 start, f32 end);
s32 irand(s32 scalar);
void itemEntry();
void itemFlagOn();
u32 keyGetButtonTrg(u32 chan);
s32 marioAnimeId(void);
void marioChgPose(const char* name);
s32 marioCtrlOffChk(void);
void marioFBattlePost(void);
void marioFBattlePrepare(void);
s32 marioGetExtraPartyId(void);
s32 marioGetPartyId(void);
MarioWork* marioGetPtr(void);
s32 marioKeyOff(void);
s32 marioKeyOffChk(void);
s32 marioKeyOn(void);
s16 marioSetMutekiTime(s32 msec);
void *memset(void *dest, int ch, size_t count);
const char* msgSearch(const char* tag);
void npcDelete(NpcEntry* entry);
void npcGroupDead(NpcEntry* entry, BOOL reason);
void npcSetupBattleInfo(NpcEntry* npc, NpcSetupBattleInfo* setup);
void offscreenAddBoundingBox(s32 id, u16 left, u16 top, u16 right, u16 bottom);
void partyChgPoseId();
PartyEntry* partyGetPtr(s32 index);
s32 pouchEquipCheckBadge(s32 badgeId);
s32 pouchGetHammerLv(void);
PouchData* pouchGetPtr(void);
s32 psndSFXOn_3D(const char* name, Vec* position);
f32 reviseAngle(f32 angle);
SequenceType seqGetSeq(void);
void seqSetSeq(SequenceType seq, const char* map, const char* bero);
void sincosf(f32* ret_sin, f32* ret_cos, f32 degree);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
BOOL swGet(s32 index);
s32 sysMsec2Frame(s32 msec);
void sysWaitDrawSync(void);
void unk_80058374(void);
void windowDispGX_Waku_col(u16 gxTexMapID, GXColor color, f32 x, f32 y, f32 width, f32 height, f32 curve);
asm BOOL N_fbatPreventMarioEventChk(void) {
	nofralloc
	lwz r3, gp(r13)
	lwz r3, 0x168(r3)
	lha r0, 0x0(r3)
	cmpwi r0, 0x0
	beq lbl_a2_1
	cmpwi r0, 0x1
	beq lbl_a2_1
	cmpwi r0, 0x8
	beq lbl_a2_1
	li r3, 0x1
	blr
	lbl_a2_1:
	li r3, 0x0
	blr
}

asm BOOL npcCheckBlow(NpcEntry* npc) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stw r31, 0x3c(r1)
	mr r31, r3
	lwz r3, 0x0(r3)
	rlwinm. r0, r3, 0, 2, 2
	beq lbl_a2_1
	li r3, 0x0
	b lbl_a2_2
	lbl_a2_1:
	rlwinm. r0, r3, 0, 26, 26
	beq lbl_a2_3
	li r3, 0x0
	b lbl_a2_2
	lbl_a2_3:
	lwz r5, 0x8c(r31)
	addi r3, r1, 0x20
	lwz r4, 0x90(r31)
	lwz r0, 0x94(r31)
	stw r5, 0x2c(r1)
	stw r5, 0x20(r1)
	stw r4, 0x24(r1)
	stw r0, 0x28(r1)
	stw r4, 0x30(r1)
	lfs f1, 0x14c(r31)
	stw r0, 0x34(r1)
	bl cloudGetBreathPower
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_4
	li r3, 0x1
	b lbl_a2_2
	lbl_a2_4:
	lwz r0, 0x90(r31)
	addi r3, r1, 0x14
	lwz r5, 0x8c(r31)
	stw r0, 0x30(r1)
	lwz r4, 0x94(r31)
	lfs f2, 0x150(r31)
	lfs f1, float_0p5_80419ba0(r2)
	lfs f0, 0x30(r1)
	stw r5, 0x14(r1)
	fnmsubs f0, f2, f1, f0
	stw r4, 0x1c(r1)
	stfs f0, 0x30(r1)
	lwz r0, 0x30(r1)
	stw r5, 0x2c(r1)
	stw r0, 0x18(r1)
	stw r4, 0x34(r1)
	lfs f1, 0x14c(r31)
	bl cloudGetBreathPower
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_5
	li r3, 0x1
	b lbl_a2_2
	lbl_a2_5:
	lwz r0, 0x90(r31)
	addi r3, r1, 0x8
	lwz r5, 0x8c(r31)
	stw r0, 0x30(r1)
	lwz r4, 0x94(r31)
	lfs f0, 0x150(r31)
	lfs f1, 0x30(r1)
	stw r5, 0x8(r1)
	fsubs f0, f1, f0
	stw r4, 0x10(r1)
	stfs f0, 0x30(r1)
	lwz r0, 0x30(r1)
	stw r5, 0x2c(r1)
	stw r0, 0xc(r1)
	stw r4, 0x34(r1)
	lfs f1, 0x14c(r31)
	bl cloudGetBreathPower
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	mfcr r0
	extrwi r3, r0, 1, 1
	lbl_a2_2:
	lwz r0, 0x44(r1)
	lwz r31, 0x3c(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 npcCalcScore(NpcEntry* npc) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	li r30, 0x12c
	stw r29, 0x24(r1)
	mr r29, r3
	lwz r4, gp(r13)
	lwz r3, 0x8c(r3)
	lwz r31, 0x168(r4)
	lwz r0, 0x90(r29)
	stw r0, 0xc(r1)
	stw r3, 0x8(r1)
	lfs f1, 0xc(r1)
	lwz r0, 0x94(r29)
	stw r0, 0x10(r1)
	lwz r3, 0x28(r29)
	lfs f0, 0x2c(r3)
	fadds f0, f1, f0
	stfs f0, 0xc(r1)
	lhz r0, 0x31c(r29)
	cmplwi r0, 0x10
	bne lbl_a2_1
	li r30, 0x0
	b lbl_a2_2
	lbl_a2_1:
	cmplwi r0, 0x8
	bne lbl_a2_3
	li r30, 0x190
	lbl_a2_3:
	bl kpaMutekiCheck
	cmpwi r3, 0x0
	beq lbl_a2_4
	addi r30, r30, 0x64
	lbl_a2_4:
	lhz r0, 0x31c(r29)
	cmplwi r0, 0x2
	bne lbl_a2_5
	lwz r3, 0x574(r31)
	addi r0, r3, 0x1
	stw r0, 0x574(r31)
	lwz r0, 0x574(r31)
	mullw r30, r30, r0
	lbl_a2_5:
	lhz r0, 0x31c(r29)
	cmplwi r0, 0x1
	bne lbl_a2_6
	lwz r3, 0x578(r31)
	addi r0, r3, 0x1
	stw r0, 0x578(r31)
	lwz r0, 0x57c(r31)
	add r0, r0, r30
	stw r0, 0x57c(r31)
	lbl_a2_6:
	cmpwi r30, 0x270f
	ble lbl_a2_2
	li r30, 0x2710
	lbl_a2_2:
	cmpwi r30, 0x0
	ble lbl_a2_7
	mr r3, r30
	addi r4, r1, 0x8
	bl kpaAddScorePos
	lbl_a2_7:
	lwz r0, 0x34(r1)
	mr r3, r30
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void fbatSandersBombTriggerOn(void) {
	nofralloc
	lwz r3, gp(r13)
	li r0, 0x1
	lwz r3, 0x168(r3)
	stb r0, 0x54d(r3)
	blr
}

asm s32 npcKoopaModeMobjBoundDeadCheck(HitEntry* hit) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	la r3, work(r13)
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r3, r3, 0x14
	lbl_a2_1:
	cmplwi r27, 0x0
	lwz r30, 0x4(r3)
	li r28, 0x0
	bne lbl_a2_2
	li r3, 0x0
	b lbl_a2_3
	lbl_a2_2:
	lwz r29, 0xc(r3)
	li r31, 0x0
	b lbl_a2_4
	lbl_a2_5:
	cmplwi r29, 0x0
	beq lbl_a2_6
	lwz r3, 0x0(r29)
	clrlwi. r0, r3, 31
	beq lbl_a2_6
	rlwinm. r0, r3, 0, 4, 4
	beq lbl_a2_6
	lwz r0, 0x1d4(r29)
	rlwinm. r0, r0, 0, 29, 29
	bne lbl_a2_6
	lhz r0, 0x31e(r29)
	rlwinm. r0, r0, 0, 28, 28
	bne lbl_a2_6
	lwz r0, 0x300(r29)
	cmplw r0, r27
	bne lbl_a2_6
	mr r3, r29
	li r4, 0x8
	bl npcGroupDead
	addi r28, r28, 0x1
	lbl_a2_6:
	addi r31, r31, 0x1
	addi r29, r29, 0x340
	lbl_a2_4:
	cmpw r31, r30
	blt lbl_a2_5
	mr r3, r28
	lbl_a2_3:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcKoopaModeEncountCheck(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	la r3, work(r13)
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	lwz r4, 0x168(r4)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r3, r3, 0x14
	lbl_a2_1:
	lha r0, 0x0(r4)
	lwz r30, 0x4(r3)
	cmpwi r0, 0x1
	bne lbl_a2_2
	lwz r29, 0xc(r3)
	li r31, 0x0
	b lbl_a2_3
	lbl_a2_4:
	cmplwi r29, 0x0
	beq lbl_a2_5
	lwz r3, 0x0(r29)
	clrlwi. r0, r3, 31
	beq lbl_a2_5
	rlwinm. r0, r3, 0, 4, 4
	beq lbl_a2_5
	lwz r0, 0x1d4(r29)
	rlwinm. r0, r0, 0, 29, 29
	bne lbl_a2_5
	lfs f1, 0x8c(r29)
	lfs f2, 0x90(r29)
	lfs f3, 0x94(r29)
	lfs f4, 0x150(r29)
	lfs f5, 0x14c(r29)
	bl kpaEnemyHitChk
	cmpwi r3, 0x3
	beq lbl_a2_6
	bge lbl_a2_7
	cmpwi r3, 0x1
	beq lbl_a2_8
	bge lbl_a2_9
	b lbl_a2_10
	lbl_a2_7:
	cmpwi r3, 0x5
	bge lbl_a2_10
	b lbl_a2_11
	lbl_a2_8:
	lhz r0, 0x31e(r29)
	clrlwi. r0, r0, 31
	bne lbl_a2_5
	mr r3, r29
	li r4, 0x1
	bl npcGroupDead
	b lbl_a2_5
	lbl_a2_9:
	lhz r0, 0x31e(r29)
	rlwinm. r0, r0, 0, 30, 30
	bne lbl_a2_5
	mr r3, r29
	li r4, 0x2
	bl npcGroupDead
	b lbl_a2_5
	lbl_a2_6:
	lhz r0, 0x31e(r29)
	rlwinm. r0, r0, 0, 29, 29
	bne lbl_a2_5
	mr r3, r29
	li r4, 0x4
	bl npcGroupDead
	b lbl_a2_5
	lbl_a2_11:
	bl kpaPowDown
	b lbl_a2_5
	lbl_a2_10:
	lhz r0, 0x31e(r29)
	rlwinm. r0, r0, 0, 27, 27
	bne lbl_a2_5
	lwz r3, 0x300(r29)
	cmplwi r3, 0x0
	beq lbl_a2_5
	bl hitGetName
	lis r4, str_802C30FC@ha
	addi r4, r4, str_802C30FC@l
	bl strcmp
	cmpwi r3, 0x0
	bne lbl_a2_5
	mr r3, r29
	li r4, 0x10
	bl npcGroupDead
	lbl_a2_5:
	addi r31, r31, 0x1
	addi r29, r29, 0x340
	lbl_a2_3:
	cmpw r31, r30
	blt lbl_a2_4
	lbl_a2_2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcClearDeadInfo(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r4, 0x0
	li r5, 0x500
	stw r0, 0x14(r1)
	lwz r3, gp(r13)
	lwz r3, 0x168(r3)
	addi r3, r3, 0x4c
	bl memset
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void npcGetBackItemEntry(NpcEntry* npc) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	li r31, 0x0
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	li r29, 0x0
	stw r28, 0x10(r1)
	mr r28, r3
	addi r30, r28, 0x230
	lbl_a2_1:
	lwz r4, 0x7c(r30)
	cmpwi r4, 0x0
	beq lbl_a2_2
	lfs f1, 0x8c(r28)
	li r3, 0x0
	lfs f2, 0x90(r28)
	li r5, 0xb
	lfs f3, 0x94(r28)
	li r6, -0x1
	li r7, 0x0
	bl itemEntry
	li r4, 0x100
	bl itemFlagOn
	stw r31, 0x7c(r30)
	lbl_a2_2:
	addi r29, r29, 0x1
	addi r30, r30, 0x4
	cmpwi r29, 0x8
	blt lbl_a2_1
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 _majinai_effect(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r4
	stw r30, 0x8(r1)
	mr r30, r3
	bl marioGetPtr
	cmpwi r31, 0x0
	mr r4, r3
	beq lbl_a2_1
	lfs f1, 0x90(r4)
	li r3, 0x0
	lfs f0, 0x1b8(r4)
	lfs f2, float_16_80419bac(r2)
	fadds f0, f1, f0
	lfs f1, 0x8c(r4)
	lfs f3, 0x94(r4)
	fadds f2, f2, f0
	bl effMajinaiEntry
	stw r3, 0x78(r30)
	lis r3, str_802C3128@ha
	addi r4, r3, str_802C3128@l
	lfs f0, float_0p8_80419bb0(r2)
	lwz r3, 0x78(r30)
	lwz r3, 0xc(r3)
	stfs f0, 0x10(r3)
	lwz r3, 0x78(r30)
	bl effSetName
	lbl_a2_1:
	lwz r0, 0x78(r30)
	cmpwi r0, 0x0
	beq lbl_a2_2
	lis r3, str_802C3128@ha
	addi r3, r3, str_802C3128@l
	bl effNameToPtr
	cmplwi r3, 0x0
	beq lbl_a2_2
	li r3, 0x0
	b lbl_a2_3
	lbl_a2_2:
	li r3, 0x2
	lbl_a2_3:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 _check(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r3, 0x18(r3)
	lwz r31, 0x0(r3)
	bl pouchGetPtr
	lbz r0, 0x5b8(r3)
	cmplwi r0, 0x0
	beq lbl_a2_1
	mr r3, r30
	mr r4, r31
	li r5, 0x0
	bl evtSetValue
	b lbl_a2_2
	lbl_a2_1:
	mr r3, r30
	mr r4, r31
	li r5, 0x1
	bl evtSetValue
	lbl_a2_2:
	lwz r0, 0x14(r1)
	li r3, 0x2
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void npcExecAllReglEvt(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	la r4, work(r13)
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r4, r4, 0x14
	lbl_a2_1:
	lwz r30, 0x4(r4)
	li r31, 0x0
	lwz r29, 0xc(r4)
	b lbl_a2_2
	lbl_a2_3:
	cmplwi r29, 0x0
	beq lbl_a2_4
	lwz r0, 0x0(r29)
	clrlwi. r0, r0, 31
	beq lbl_a2_4
	lwz r0, 0x124(r29)
	cmplwi r0, 0x0
	beq lbl_a2_4
	lwz r3, 0x11c(r29)
	cmpwi r3, 0x0
	beq lbl_a2_5
	bl evtDeleteID
	lbl_a2_5:
	lwz r3, 0x124(r29)
	li r4, 0x0
	li r5, 0x20
	bl evtEntry
	li r0, 0x1
	stb r0, 0x10(r3)
	stw r29, 0x170(r3)
	lwz r0, 0x15c(r3)
	stw r0, 0x11c(r29)
	lbl_a2_4:
	addi r31, r31, 0x1
	addi r29, r29, 0x340
	lbl_a2_2:
	cmpw r31, r30
	blt lbl_a2_3
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm BOOL npcWaitAllInitEvtEnd(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	la r4, work(r13)
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r4, r4, 0x14
	lbl_a2_1:
	lwz r29, 0x4(r4)
	li r31, 0x1
	lwz r28, 0xc(r4)
	li r30, 0x0
	b lbl_a2_2
	lbl_a2_3:
	cmplwi r28, 0x0
	beq lbl_a2_4
	lwz r4, 0x0(r28)
	clrlwi. r0, r4, 31
	beq lbl_a2_4
	rlwinm. r0, r4, 0, 30, 30
	bne lbl_a2_4
	lwz r3, 0x118(r28)
	cmpwi r3, 0x0
	beq lbl_a2_5
	li r31, 0x0
	bl evtCheckID
	cmpwi r3, 0x0
	bne lbl_a2_4
	li r0, 0x0
	stw r0, 0x118(r28)
	lwz r0, 0x0(r28)
	ori r0, r0, 0x2
	stw r0, 0x0(r28)
	b lbl_a2_4
	lbl_a2_5:
	ori r0, r4, 0x2
	stw r0, 0x0(r28)
	lbl_a2_4:
	addi r30, r30, 0x1
	addi r28, r28, 0x340
	lbl_a2_2:
	cmpw r30, r29
	blt lbl_a2_3
	lwz r0, 0x24(r1)
	mr r3, r31
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcExecAllInitEvt(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	la r4, work(r13)
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r4, r4, 0x14
	lbl_a2_1:
	lwz r30, 0x4(r4)
	li r31, 0x0
	lwz r29, 0xc(r4)
	b lbl_a2_2
	lbl_a2_3:
	cmplwi r29, 0x0
	beq lbl_a2_4
	lwz r0, 0x0(r29)
	clrlwi. r0, r0, 31
	beq lbl_a2_4
	lwz r0, 0x120(r29)
	cmplwi r0, 0x0
	beq lbl_a2_5
	lwz r3, 0x118(r29)
	cmpwi r3, 0x0
	beq lbl_a2_6
	bl evtDeleteID
	lbl_a2_6:
	lwz r3, 0x120(r29)
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	li r0, 0x0
	stb r0, 0x10(r3)
	stw r29, 0x170(r3)
	lwz r0, 0x15c(r3)
	stw r0, 0x118(r29)
	b lbl_a2_4
	lbl_a2_5:
	li r0, 0x0
	stw r0, 0x118(r29)
	lbl_a2_4:
	addi r31, r31, 0x1
	addi r29, r29, 0x340
	lbl_a2_2:
	cmpw r31, r30
	blt lbl_a2_3
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm NpcTerritoryType dbGetDefData(NpcTerritoryInfo* info, const char* description) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	li r31, 0x0
	stw r30, 0x18(r1)
	mr r30, r4
	stw r29, 0x14(r1)
	mr r29, r3
	lbl_a2_1:
	lwz r3, 0x0(r29)
	cmplwi r3, 0x0
	beq lbl_a2_2
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne lbl_a2_3
	lwz r31, 0x4(r29)
	b lbl_a2_2
	lbl_a2_3:
	addi r29, r29, 0x8
	b lbl_a2_1
	lbl_a2_2:
	lwz r0, 0x24(r1)
	mr r3, r31
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcSetLink(NpcEntry* npc, NpcEntry* other) {
	nofralloc
	stw r4, 0x328(r3)
	stw r3, 0x324(r4)
	blr
}

asm void npcSetSlave(NpcEntry* npc, NpcEntry* slave, s32 id) {
	nofralloc
	slwi r0, r5, 2
	stw r3, 0x32c(r4)
	add r3, r3, r0
	stw r4, 0x330(r3)
	blr
}

asm void npcSetBtlSetupWork(NpcEntry* npc, s32 index, s32 value) {
	nofralloc
	slwi r0, r4, 2
	add r3, r3, r0
	stw r5, 0x2cc(r3)
	blr
}

asm s32 npcGetBtlSetupWork(NpcEntry* npc, s32 index) {
	nofralloc
	slwi r0, r4, 2
	add r3, r3, r0
	lwz r3, 0x2cc(r3)
	blr
}

asm void npcBlurOff(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	la r3, work(r13)
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r3, r3, 0x14
	lbl_a2_1:
	lwz r30, 0x4(r3)
	li r29, 0x0
	lwz r31, 0xc(r3)
	b lbl_a2_2
	lbl_a2_3:
	lwz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	beq lbl_a2_4
	mr r4, r28
	addi r3, r31, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_5
	lbl_a2_4:
	addi r29, r29, 0x1
	addi r31, r31, 0x340
	lbl_a2_2:
	cmpw r29, r30
	blt lbl_a2_3
	lbl_a2_5:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x0(r31)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcBlurOn(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	la r3, work(r13)
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r3, r3, 0x14
	lbl_a2_1:
	lwz r30, 0x4(r3)
	li r29, 0x0
	lwz r31, 0xc(r3)
	b lbl_a2_2
	lbl_a2_3:
	lwz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	beq lbl_a2_4
	mr r4, r28
	addi r3, r31, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_5
	lbl_a2_4:
	addi r29, r29, 0x1
	addi r31, r31, 0x340
	lbl_a2_2:
	cmpw r29, r30
	blt lbl_a2_3
	lbl_a2_5:
	lwz r0, 0x0(r31)
	ori r0, r0, 0x100
	stw r0, 0x0(r31)
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0xa4(r31)
	stw r0, 0xa8(r31)
	lwz r0, 0x94(r31)
	stw r0, 0xac(r31)
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0xb0(r31)
	stw r0, 0xb4(r31)
	lwz r0, 0x94(r31)
	stw r0, 0xb8(r31)
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0xbc(r31)
	stw r0, 0xc0(r31)
	lwz r0, 0x94(r31)
	stw r0, 0xc4(r31)
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0xc8(r31)
	stw r0, 0xcc(r31)
	lwz r0, 0x94(r31)
	stw r0, 0xd0(r31)
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0xd4(r31)
	stw r0, 0xd8(r31)
	lwz r0, 0x94(r31)
	stw r0, 0xdc(r31)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcSetColor(const char* name, GXColor color) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	mr r28, r4
	la r3, work(r13)
	lwz r5, gp(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r3, r3, 0x14
	lbl_a2_1:
	lwz r30, 0x4(r3)
	li r29, 0x0
	lwz r31, 0xc(r3)
	b lbl_a2_2
	lbl_a2_3:
	lwz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	beq lbl_a2_4
	mr r4, r27
	addi r3, r31, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_5
	lbl_a2_4:
	addi r29, r29, 0x1
	addi r31, r31, 0x340
	lbl_a2_2:
	cmpw r29, r30
	blt lbl_a2_3
	lbl_a2_5:
	lwz r0, 0x0(r28)
	stw r0, 0x114(r31)
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcStartForOneEvent(NpcEntry* npc) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr. r31, r3
	beq lbl_a2_1
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_1
	rlwinm. r0, r3, 0, 3, 3
	beq lbl_a2_1
	lwz r3, 0x1d4(r31)
	rlwinm. r0, r3, 0, 15, 15
	beq lbl_a2_1
	rlwinm r0, r3, 0, 16, 14
	stw r0, 0x1d4(r31)
	lwz r3, 0x11c(r31)
	bl evtStartID
	lwz r3, 0x104(r31)
	lfs f1, float_1_80419bb4(r2)
	bl animPoseSetLocalTimeRate
	lbl_a2_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void npcStartForEvent(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	la r4, work(r13)
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r4, r4, 0x14
	lbl_a2_1:
	lwz r30, 0x4(r4)
	li r31, 0x0
	lwz r29, 0xc(r4)
	b lbl_a2_2
	lbl_a2_3:
	cmplwi r29, 0x0
	beq lbl_a2_4
	lwz r3, 0x0(r29)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_4
	rlwinm. r0, r3, 0, 3, 3
	beq lbl_a2_4
	lwz r3, 0x1d4(r29)
	rlwinm. r0, r3, 0, 15, 15
	beq lbl_a2_4
	rlwinm r0, r3, 0, 16, 14
	stw r0, 0x1d4(r29)
	lwz r3, 0x11c(r29)
	bl evtStartID
	lwz r3, 0x104(r29)
	lfs f1, float_1_80419bb4(r2)
	bl animPoseSetLocalTimeRate
	lbl_a2_4:
	addi r31, r31, 0x1
	addi r29, r29, 0x340
	lbl_a2_2:
	cmpw r31, r30
	blt lbl_a2_3
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcStopForOneEvent(NpcEntry* npc) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr. r31, r3
	beq lbl_a2_1
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_1
	rlwinm. r0, r3, 0, 3, 3
	beq lbl_a2_1
	lwz r0, 0x1d4(r31)
	oris r0, r0, 0x1
	stw r0, 0x1d4(r31)
	lwz r3, 0x11c(r31)
	bl evtStopID
	lwz r3, 0x104(r31)
	lfs f1, float_0_80419b9c(r2)
	bl animPoseSetLocalTimeRate
	lbl_a2_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void npcStopForEvent(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	la r4, work(r13)
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r4, r4, 0x14
	lbl_a2_1:
	lwz r30, 0x4(r4)
	li r31, 0x0
	lwz r29, 0xc(r4)
	b lbl_a2_2
	lbl_a2_3:
	cmplwi r29, 0x0
	beq lbl_a2_4
	lwz r3, 0x0(r29)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_4
	rlwinm. r0, r3, 0, 3, 3
	beq lbl_a2_4
	lwz r0, 0x1d4(r29)
	oris r0, r0, 0x1
	stw r0, 0x1d4(r29)
	lwz r3, 0x11c(r29)
	bl evtStopID
	lwz r3, 0x104(r29)
	lfs f1, float_0_80419b9c(r2)
	bl animPoseSetLocalTimeRate
	lbl_a2_4:
	addi r31, r31, 0x1
	addi r29, r29, 0x340
	lbl_a2_2:
	cmpw r31, r30
	blt lbl_a2_3
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcSetBattleInfo(NpcEntry* npc, s32 battleInfoId) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	mr r31, r3
	stw r30, 0x18(r1)
	mr r30, r4
	cmpwi r30, -0x1
	bne lbl_a2_1
	li r4, 0x0
	b lbl_a2_2
	lbl_a2_1:
	lwz r5, gp(r13)
	li r0, 0x0
	addi r3, r1, 0x8
	lbz r4, 0x12c(r5)
	stb r4, 0x8(r1)
	lbz r4, 0x12d(r5)
	stb r4, 0x9(r1)
	lbz r4, 0x12e(r5)
	stb r4, 0xa(r1)
	stb r0, 0xb(r1)
	bl areaDataPtr
	cmpwi r30, 0x0
	lwz r4, 0x8(r3)
	mr r3, r30
	ble lbl_a2_2
	srwi. r0, r30, 3
	mtctr r0
	beq lbl_a2_3
	lbl_a2_4:
	addi r4, r4, 0x220
	bdnz lbl_a2_4
	andi. r3, r3, 0x7
	beq lbl_a2_2
	lbl_a2_3:
	mtctr r3
	lbl_a2_5:
	addi r4, r4, 0x44
	bdnz lbl_a2_5
	lbl_a2_2:
	mr r3, r31
	bl npcSetupBattleInfo
	mr r7, r31
	li r8, 0x0
	li r4, 0x19
	lbl_a2_6:
	lwz r3, 0x330(r7)
	cmplwi r3, 0x0
	beq lbl_a2_7
	addi r6, r3, 0x22c
	addi r5, r31, 0x22c
	mtctr r4
	lbl_a2_8:
	lwz r3, 0x4(r5)
	lwzu r0, 0x8(r5)
	stw r3, 0x4(r6)
	stwu r0, 0x8(r6)
	bdnz lbl_a2_8
	lbl_a2_7:
	addi r8, r8, 0x1
	addi r7, r7, 0x4
	cmpwi r8, 0x4
	blt lbl_a2_6
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcSetupBattleInfo(NpcEntry* npc, NpcSetupBattleInfo* setup) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	li r5, 0xc8
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r29, r3
	addi r31, r29, 0x230
	mr r30, r4
	li r4, 0x0
	mr r3, r31
	bl memset
	addi r3, r31, 0x7c
	li r4, 0x0
	li r5, 0x20
	bl memset
	cmplwi r30, 0x0
	beq lbl_a2_1
	lwz r0, 0x0(r30)
	cmplwi r0, 0x0
	beq lbl_a2_1
	lwz r0, 0x1c(r30)
	stw r0, 0xac(r31)
	lwz r0, 0xac(r31)
	cmpwi r0, 0x0
	beq lbl_a2_2
	blt lbl_a2_2
	cmpwi r0, 0x3
	bge lbl_a2_2
	b lbl_a2_3
	lbl_a2_2:
	li r28, 0x0
	mr r27, r30
	lbl_a2_4:
	lbz r3, 0x20(r27)
	lbz r0, 0x21(r27)
	extsb r3, r3
	extsb r0, r0
	subf r3, r3, r0
	addi r3, r3, 0x1
	bl irand
	lbz r4, 0x20(r27)
	addi r0, r28, 0xb0
	addi r28, r28, 0x1
	addi r27, r27, 0x2
	add r3, r4, r3
	cmpwi r28, 0x10
	stbx r3, r31, r0
	blt lbl_a2_4
	lbl_a2_3:
	lwz r0, 0x18(r30)
	lis r3, 0xf840
	li r4, 0x0
	stw r0, 0x4(r31)
	addi r0, r3, 0x5b80
	lwz r3, 0x8(r30)
	stw r3, 0x8(r31)
	stw r4, 0xc(r31)
	stw r4, 0x10(r31)
	stw r4, 0x14(r31)
	lwz r3, 0x40(r30)
	stw r3, 0xc0(r31)
	lwz r4, 0xc(r30)
	cmpw r4, r0
	blt lbl_a2_5
	lis r3, 0xf8d9
	subi r0, r3, 0xe00
	cmpw r4, r0
	bgt lbl_a2_5
	addis r3, r4, 0x7c0
	subi r3, r3, 0x5b80
	bl swGet
	cmpwi r3, 0x0
	beq lbl_a2_6
	lwz r27, 0x10(r30)
	b lbl_a2_7
	lbl_a2_6:
	lwz r27, 0x14(r30)
	b lbl_a2_7
	lbl_a2_5:
	lwz r27, 0x14(r30)
	lbl_a2_7:
	li r0, 0x0
	cmplwi r27, 0x0
	stw r0, 0x18(r31)
	beq lbl_a2_8
	mr r4, r27
	li r3, 0x0
	b lbl_a2_9
	lbl_a2_10:
	add r3, r3, r0
	addi r4, r4, 0xc
	lbl_a2_9:
	lwz r0, 0x0(r4)
	cmpwi r0, 0x0
	bgt lbl_a2_10
	cmpwi r3, 0x0
	ble lbl_a2_8
	bl irand
	lbl_a2_11:
	lwz r0, 0x0(r27)
	subf. r3, r0, r3
	blt lbl_a2_12
	addi r27, r27, 0xc
	b lbl_a2_11
	lbl_a2_12:
	lwz r0, 0x4(r27)
	stw r0, 0x18(r31)
	lwz r0, 0x8(r27)
	stw r0, 0x0(r31)
	lbl_a2_8:
	lwz r4, 0x18(r31)
	cmplwi r4, 0x0
	beq lbl_a2_13
	lwz r30, 0x0(r4)
	addi r3, r31, 0x1c
	lwz r26, 0x4(r4)
	li r4, 0x0
	li r5, 0x20
	bl memset
	mr r27, r31
	li r28, 0x0
	b lbl_a2_14
	lbl_a2_15:
	lwz r25, 0x2c(r26)
	cmplwi r25, 0x0
	beq lbl_a2_16
	mr r5, r25
	li r3, 0x0
	b lbl_a2_17
	lbl_a2_18:
	add r3, r3, r4
	addi r5, r5, 0x8
	lbl_a2_17:
	lha r4, 0x4(r5)
	extsh. r0, r4
	bgt lbl_a2_18
	lwz r0, 0x0(r5)
	cmpwi r0, 0x0
	bne lbl_a2_18
	cmpwi r3, 0x0
	ble lbl_a2_16
	bl irand
	lbl_a2_19:
	lha r0, 0x4(r25)
	subf. r3, r0, r3
	bge lbl_a2_20
	lwz r0, 0x0(r25)
	stw r0, 0x1c(r27)
	lwz r0, 0x2c(r26)
	stw r0, 0x3c(r27)
	b lbl_a2_16
	lbl_a2_20:
	addi r25, r25, 0x8
	b lbl_a2_19
	lbl_a2_16:
	addi r26, r26, 0x30
	addi r27, r27, 0x4
	addi r28, r28, 0x1
	lbl_a2_14:
	cmpw r28, r30
	blt lbl_a2_15
	lbl_a2_13:
	li r0, 0x0
	stb r0, 0x316(r29)
	lwz r3, 0x18(r31)
	cmplwi r3, 0x0
	beq lbl_a2_21
	lwz r3, 0x4(r3)
	lwz r3, 0x0(r3)
	lbz r0, 0x12(r3)
	stb r0, 0x316(r29)
	lbl_a2_21:
	lwz r0, 0x0(r29)
	oris r0, r0, 0x1000
	stw r0, 0x0(r29)
	lbl_a2_1:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm BOOL npcCheckInterrupt(NpcEntry* npc) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	stw r30, 0x8(r1)
	mr r30, r3
	lwz r3, 0x11c(r3)
	bl evtGetPtrID
	lwz r4, 0x140(r30)
	rlwinm. r0, r4, 0, 24, 19
	beq lbl_a2_1
	rlwinm. r0, r4, 0, 27, 27
	li r31, 0x0
	beq lbl_a2_2
	lwz r3, 0x12c(r30)
	cmplwi r3, 0x0
	beq lbl_a2_2
	li r4, 0x0
	li r5, 0x20
	bl evtEntry
	li r0, 0x8
	mr r31, r3
	stb r0, 0x10(r3)
	stw r30, 0x170(r3)
	b lbl_a2_3
	lbl_a2_2:
	rlwinm. r0, r4, 0, 3, 3
	beq lbl_a2_4
	lwz r3, 0x124(r30)
	cmplwi r3, 0x0
	beq lbl_a2_4
	li r4, 0x0
	li r5, 0x20
	bl evtEntry
	li r0, 0x1
	mr r31, r3
	stb r0, 0x10(r3)
	stw r30, 0x170(r3)
	b lbl_a2_3
	lbl_a2_4:
	rlwinm. r0, r4, 0, 28, 28
	beq lbl_a2_5
	lwz r3, 0x13c(r30)
	cmplwi r3, 0x0
	beq lbl_a2_5
	li r4, 0x0
	li r5, 0x20
	bl evtEntry
	li r0, 0x5
	mr r31, r3
	stb r0, 0x10(r3)
	stw r30, 0x170(r3)
	b lbl_a2_3
	lbl_a2_5:
	clrlwi. r0, r4, 31
	beq lbl_a2_6
	lwz r3, 0x130(r30)
	cmplwi r3, 0x0
	beq lbl_a2_6
	lwz r0, 0x1d4(r30)
	rlwinm. r0, r0, 0, 19, 19
	bne lbl_a2_6
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 10, 10
	bne lbl_a2_6
	rlwinm. r0, r4, 0, 23, 23
	bne lbl_a2_6
	li r4, 0x0
	li r5, 0x20
	bl evtEntry
	li r0, 0x2
	mr r31, r3
	stb r0, 0x10(r3)
	stw r30, 0x170(r3)
	b lbl_a2_3
	lbl_a2_6:
	rlwinm. r0, r4, 0, 30, 30
	beq lbl_a2_7
	lwz r3, 0x134(r30)
	cmplwi r3, 0x0
	beq lbl_a2_7
	lwz r0, 0x1d4(r30)
	rlwinm. r0, r0, 0, 19, 19
	bne lbl_a2_7
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 10, 10
	bne lbl_a2_7
	li r4, 0x0
	li r5, 0x20
	bl evtEntry
	li r0, 0x3
	mr r31, r3
	stb r0, 0x10(r3)
	stw r30, 0x170(r3)
	b lbl_a2_3
	lbl_a2_7:
	rlwinm. r0, r4, 0, 29, 29
	beq lbl_a2_3
	lwz r3, 0x138(r30)
	cmplwi r3, 0x0
	beq lbl_a2_3
	lwz r0, 0x1d4(r30)
	rlwinm. r0, r0, 0, 19, 19
	bne lbl_a2_3
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 10, 10
	bne lbl_a2_3
	li r4, 0x0
	li r5, 0x20
	bl evtEntry
	li r0, 0x4
	mr r31, r3
	stb r0, 0x10(r3)
	stw r30, 0x170(r3)
	lbl_a2_3:
	cmplwi r31, 0x0
	beq lbl_a2_1
	lwz r3, 0x11c(r30)
	bl evtDeleteID
	lwz r4, 0x15c(r31)
	li r0, 0x0
	lfs f0, float_0_80419b9c(r2)
	li r3, 0x1
	stw r4, 0x11c(r30)
	lwz r4, 0x140(r30)
	rlwinm r4, r4, 0, 20, 23
	stw r4, 0x140(r30)
	lwz r4, 0x1d4(r30)
	rlwinm r4, r4, 0, 20, 18
	stw r4, 0x1d4(r30)
	stw r0, 0x18c(r30)
	stw r0, 0x188(r30)
	stfs f0, 0x1b0(r30)
	b lbl_a2_8
	lbl_a2_1:
	lwz r0, 0x140(r30)
	li r3, 0x0
	rlwinm r0, r0, 0, 20, 23
	stw r0, 0x140(r30)
	lwz r0, 0x1d4(r30)
	rlwinm r0, r0, 0, 20, 18
	stw r0, 0x1d4(r30)
	lbl_a2_8:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle) {
	nofralloc
	stwu r1, -0x120(r1)
	mflr r0
	stw r0, 0x124(r1)
	stfd f31, 0x110(r1)
	psq_st f31, 0x118(r1), 0, 0
	stfd f30, 0x100(r1)
	psq_st f30, 0x108(r1), 0, 0
	stfd f29, 0xf0(r1)
	psq_st f29, 0xf8(r1), 0, 0
	stfd f28, 0xe0(r1)
	psq_st f28, 0xe8(r1), 0, 0
	stfd f27, 0xd0(r1)
	psq_st f27, 0xd8(r1), 0, 0
	stfd f26, 0xc0(r1)
	psq_st f26, 0xc8(r1), 0, 0
	stfd f25, 0xb0(r1)
	psq_st f25, 0xb8(r1), 0, 0
	stfd f24, 0xa0(r1)
	psq_st f24, 0xa8(r1), 0, 0
	stfd f23, 0x90(r1)
	psq_st f23, 0x98(r1), 0, 0
	stfd f22, 0x80(r1)
	psq_st f22, 0x88(r1), 0, 0
	stfd f21, 0x70(r1)
	psq_st f21, 0x78(r1), 0, 0
	stmw r26, 0x58(r1)
	lfs f27, float_0_80419b9c(r2)
	lis r5, vec3_802c2f78@ha
	addi r30, r5, vec3_802c2f78@l
	fmr f25, f1
	fmr f26, f2
	lfs f29, float_11_80419bbc(r2)
	fmr f28, f27
	lfd f30, 0x1d8(r30)
	fmr f31, f27
	lfs f22, float_0p5_80419ba0(r2)
	lfs f23, float_12_80419bc0(r2)
	mr r28, r3
	lfs f24, float_1_80419bb4(r2)
	mr r29, r4
	addi r26, r1, 0x1c
	lis r27, 0x4330
	b lbl_a2_1
	lbl_a2_2:
	fmr f21, f27
	bl marioGetPtr
	lwz r12, 0x24(r30)
	fcmpo cr0, f27, f28
	lwz r11, 0x28(r30)
	mr r31, r3
	lwz r10, 0x2c(r30)
	lwz r9, 0x30(r30)
	lwz r8, 0x34(r30)
	lwz r7, 0x38(r30)
	lwz r6, 0x3c(r30)
	lwz r5, 0x40(r30)
	lwz r4, 0x44(r30)
	lwz r3, 0x48(r30)
	lwz r0, 0x4c(r30)
	stw r12, 0x1c(r1)
	stw r11, 0x20(r1)
	stw r10, 0x24(r1)
	stw r9, 0x28(r1)
	stw r8, 0x2c(r1)
	stw r7, 0x30(r1)
	stw r6, 0x34(r1)
	stw r5, 0x38(r1)
	stw r4, 0x3c(r1)
	stw r3, 0x40(r1)
	stw r0, 0x44(r1)
	bge lbl_a2_3
	fmr f21, f28
	lbl_a2_3:
	fcmpo cr0, f21, f29
	cror eq, gt, eq
	bne lbl_a2_4
	lfs f21, float_10_80419bb8(r2)
	lbl_a2_4:
	fmr f1, f26
	addi r3, r1, 0xc
	addi r4, r1, 0x10
	bl sincosf
	fctiwz f0, f21
	stw r27, 0x50(r1)
	addi r3, r1, 0x14
	addi r4, r1, 0x18
	stfd f0, 0x48(r1)
	lwz r0, 0x4c(r1)
	slwi r0, r0, 2
	lwzx r0, r26, r0
	xoris r0, r0, 0x8000
	stw r0, 0x54(r1)
	lfd f0, 0x50(r1)
	fsubs f1, f0, f30
	bl sincosf
	lfs f1, 0xc(r1)
	lfs f0, 0x10(r1)
	fmuls f5, f1, f25
	lfs f6, 0x14(r1)
	lfs f2, 0x8c(r31)
	fmuls f1, f0, f25
	lfs f0, 0x94(r31)
	lfs f4, 0x18(r1)
	lfs f3, 0x90(r31)
	fmadds f5, f6, f5, f2
	lfs f2, 0x8c(r28)
	fmadds f1, f6, f1, f0
	lfs f0, 0x94(r28)
	fmadds f6, f25, f4, f3
	lfs f4, 0x90(r28)
	fsubs f3, f5, f2
	fcmpu cr0, f6, f4
	fsubs f2, f6, f4
	fsubs f1, f1, f0
	beq lbl_a2_5
	fcmpo cr0, f6, f4
	cror eq, gt, eq
	bne lbl_a2_6
	lfs f0, 0x150(r28)
	fadds f0, f4, f0
	fcmpo cr0, f6, f0
	cror eq, lt, eq
	bne lbl_a2_6
	lfs f2, float_0_80419b9c(r2)
	b lbl_a2_5
	lbl_a2_6:
	lfs f0, 0x150(r28)
	fadds f0, f4, f0
	fcmpo cr0, f6, f0
	ble lbl_a2_5
	fsubs f2, f6, f0
	lbl_a2_5:
	fmuls f0, f2, f2
	fmadds f0, f3, f3, f0
	fmadds f4, f1, f1, f0
	fcmpo cr0, f4, f31
	ble lbl_a2_7
	frsqrte f1, f4
	lfd f3, 0x1c0(r30)
	lfd f2, 0x1c8(r30)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f0, f1, f0
	fmul f4, f4, f0
	frsp f4, f4
	b lbl_a2_8
	lbl_a2_7:
	lfd f0, 0x1d0(r30)
	fcmpo cr0, f4, f0
	bge lbl_a2_9
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	b lbl_a2_8
	lbl_a2_9:
	stfs f4, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_10
	bge lbl_a2_11
	cmpwi r3, 0x0
	beq lbl_a2_12
	b lbl_a2_11
	lbl_a2_10:
	clrlwi. r0, r4, 9
	beq lbl_a2_13
	li r0, 0x1
	b lbl_a2_14
	lbl_a2_13:
	li r0, 0x2
	b lbl_a2_14
	lbl_a2_12:
	clrlwi. r0, r4, 9
	beq lbl_a2_15
	li r0, 0x5
	b lbl_a2_14
	lbl_a2_15:
	li r0, 0x3
	b lbl_a2_14
	lbl_a2_11:
	li r0, 0x4
	lbl_a2_14:
	cmpwi r0, 0x1
	bne lbl_a2_8
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	lbl_a2_8:
	lfs f0, 0x14c(r28)
	fmr f1, f4
	fmadds f0, f22, f0, f23
	fcmpo cr0, f4, f0
	bge lbl_a2_16
	mr r0, r28
	b lbl_a2_17
	lbl_a2_16:
	li r0, 0x0
	lbl_a2_17:
	cmplwi r0, 0x0
	mr r3, r0
	bne lbl_a2_18
	fadds f27, f27, f24
	lbl_a2_1:
	fcmpo cr0, f27, f29
	cror eq, lt, eq
	beq lbl_a2_2
	lbl_a2_18:
	stfs f1, 0x0(r29)
	psq_l f31, 0x118(r1), 0, 0
	lfd f31, 0x110(r1)
	psq_l f30, 0x108(r1), 0, 0
	lfd f30, 0x100(r1)
	psq_l f29, 0xf8(r1), 0, 0
	lfd f29, 0xf0(r1)
	psq_l f28, 0xe8(r1), 0, 0
	lfd f28, 0xe0(r1)
	psq_l f27, 0xd8(r1), 0, 0
	lfd f27, 0xd0(r1)
	psq_l f26, 0xc8(r1), 0, 0
	lfd f26, 0xc0(r1)
	psq_l f25, 0xb8(r1), 0, 0
	lfd f25, 0xb0(r1)
	psq_l f24, 0xa8(r1), 0, 0
	lfd f24, 0xa0(r1)
	psq_l f23, 0x98(r1), 0, 0
	lfd f23, 0x90(r1)
	psq_l f22, 0x88(r1), 0, 0
	lfd f22, 0x80(r1)
	psq_l f21, 0x78(r1), 0, 0
	lfd f21, 0x70(r1)
	lmw r26, 0x58(r1)
	lwz r0, 0x124(r1)
	mtlr r0
	addi r1, r1, 0x120
	blr
}

asm NpcEntry* _npcHitCheckSphere(NpcEntry* npc, f32* dist, f32 x, f32 y, f32 z, f32 r) {
	nofralloc
	stwu r1, -0x10(r1)
	lis r5, vec3_802c2f78@ha
	addi r5, r5, vec3_802c2f78@l
	lfs f6, 0x90(r3)
	lfs f5, 0x8c(r3)
	lfs f0, 0x94(r3)
	fcmpu cr0, f2, f6
	fsubs f5, f1, f5
	fsubs f1, f2, f6
	fsubs f3, f3, f0
	beq lbl_a2_1
	fcmpo cr0, f2, f6
	cror eq, gt, eq
	bne lbl_a2_2
	lfs f0, 0x150(r3)
	fadds f0, f6, f0
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne lbl_a2_2
	lfs f1, float_0_80419b9c(r2)
	b lbl_a2_1
	lbl_a2_2:
	lfs f0, 0x150(r3)
	fadds f0, f6, f0
	fcmpo cr0, f2, f0
	ble lbl_a2_1
	fsubs f1, f2, f0
	lbl_a2_1:
	fmuls f1, f1, f1
	lfs f0, float_0_80419b9c(r2)
	fmadds f1, f5, f5, f1
	fmadds f5, f3, f3, f1
	fcmpo cr0, f5, f0
	ble lbl_a2_3
	frsqrte f1, f5
	lfd f3, 0x1c0(r5)
	lfd f2, 0x1c8(r5)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f5, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f5, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f5, f0, f2
	fmul f0, f1, f0
	fmul f5, f5, f0
	frsp f5, f5
	b lbl_a2_4
	lbl_a2_3:
	lfd f0, 0x1d0(r5)
	fcmpo cr0, f5, f0
	bge lbl_a2_5
	lis r5, __float_nan@ha
	lfs f5, __float_nan@l(r5)
	b lbl_a2_4
	lbl_a2_5:
	stfs f5, 0x8(r1)
	lis r0, 0x7f80
	lwz r6, 0x8(r1)
	rlwinm r5, r6, 0, 1, 8
	cmpw r5, r0
	beq lbl_a2_6
	bge lbl_a2_7
	cmpwi r5, 0x0
	beq lbl_a2_8
	b lbl_a2_7
	lbl_a2_6:
	clrlwi. r0, r6, 9
	beq lbl_a2_9
	li r0, 0x1
	b lbl_a2_10
	lbl_a2_9:
	li r0, 0x2
	b lbl_a2_10
	lbl_a2_8:
	clrlwi. r0, r6, 9
	beq lbl_a2_11
	li r0, 0x5
	b lbl_a2_10
	lbl_a2_11:
	li r0, 0x3
	b lbl_a2_10
	lbl_a2_7:
	li r0, 0x4
	lbl_a2_10:
	cmpwi r0, 0x1
	bne lbl_a2_4
	lis r5, __float_nan@ha
	lfs f5, __float_nan@l(r5)
	lbl_a2_4:
	stfs f5, 0x0(r4)
	lfs f1, float_0p5_80419ba0(r2)
	lfs f0, 0x14c(r3)
	lfs f2, 0x0(r4)
	fmadds f0, f1, f0, f4
	fcmpo cr0, f2, f0
	bge lbl_a2_12
	b lbl_a2_13
	lbl_a2_12:
	li r3, 0x0
	lbl_a2_13:
	addi r1, r1, 0x10
	blr
}

asm void* fbatHitCheck(u32 flags, void* a1) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stfd f31, 0xf0(r1)
	psq_st f31, 0xf8(r1), 0, 0
	stfd f30, 0xe0(r1)
	psq_st f30, 0xe8(r1), 0, 0
	stfd f29, 0xd0(r1)
	psq_st f29, 0xd8(r1), 0, 0
	stfd f28, 0xc0(r1)
	psq_st f28, 0xc8(r1), 0, 0
	stmw r19, 0x8c(r1)
	lwz r5, gp(r13)
	lis r6, vec3_802c2f78@ha
	mr r19, r3
	mr r20, r4
	lwz r0, 0x14(r5)
	addi r29, r6, vec3_802c2f78@l
	li r24, 0x0
	li r23, 0x0
	cmpwi r0, 0x0
	la r30, work(r13)
	beq lbl_a2_1
	addi r30, r30, 0x14
	lbl_a2_1:
	bl marioGetPtr
	lwz r0, 0x34(r1)
	li r4, 0x0
	lfs f0, float_1000_80419bc8(r2)
	rlwinm. r25, r19, 0, 18, 18
	clrrwi r0, r0, 1
	stw r4, 0x28(r1)
	mr r31, r3
	stfs f0, 0x30(r1)
	stw r0, 0x34(r1)
	beq lbl_a2_2
	ori r0, r0, 0x1
	stw r0, 0x34(r1)
	lbl_a2_2:
	rlwinm. r0, r19, 0, 26, 27
	beq lbl_a2_3
	rlwinm. r26, r19, 0, 27, 27
	lwz r21, 0x4(r30)
	lwz r23, 0xc(r30)
	beq lbl_a2_4
	lha r0, 0x4c(r31)
	cmpwi r0, 0x0
	bgt lbl_a2_3
	lbl_a2_4:
	bl marioGetPtr
	lwz r5, gp(r13)
	mr r22, r3
	la r3, work(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq lbl_a2_5
	addi r3, r3, 0x14
	lbl_a2_5:
	lwz r4, 0x0(r22)
	andis. r0, r4, 0x8200
	beq lbl_a2_6
	li r0, 0x0
	b lbl_a2_7
	lbl_a2_6:
	lwz r0, 0x8(r3)
	clrlwi. r0, r0, 31
	bne lbl_a2_8
	andi. r0, r4, 0xa
	beq lbl_a2_8
	li r0, 0x0
	b lbl_a2_7
	lbl_a2_8:
	lwz r0, 0x164(r5)
	cmpwi r0, 0x0
	beq lbl_a2_9
	li r0, 0x0
	b lbl_a2_7
	lbl_a2_9:
	bl seqGetSeq
	cmpwi r3, 0x2
	beq lbl_a2_10
	li r0, 0x0
	b lbl_a2_7
	lbl_a2_10:
	lhz r0, 0x2e(r22)
	cmplwi r0, 0x19
	bne lbl_a2_11
	li r0, 0x0
	b lbl_a2_7
	lbl_a2_11:
	bl vivianGetStatus
	cmpwi r3, 0x0
	beq lbl_a2_12
	li r0, 0x0
	b lbl_a2_7
	lbl_a2_12:
	lhz r0, 0x2e(r22)
	cmplwi r0, 0x1f
	beq lbl_a2_13
	cmplwi r0, 0x20
	bne lbl_a2_14
	lbl_a2_13:
	li r0, 0x0
	b lbl_a2_7
	lbl_a2_14:
	lhz r0, 0x320(r23)
	cmplwi r0, 0x0
	beq lbl_a2_15
	li r0, 0x0
	b lbl_a2_7
	lbl_a2_15:
	li r0, 0x1
	lbl_a2_7:
	cmpwi r0, 0x0
	beq lbl_a2_3
	rlwinm r28, r19, 0, 19, 19
	rlwinm r27, r19, 0, 26, 26
	li r22, 0x0
	b lbl_a2_16
	lbl_a2_17:
	cmplwi r23, 0x0
	beq lbl_a2_18
	lwz r3, 0x0(r23)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_18
	cmplwi r28, 0x0
	beq lbl_a2_19
	rlwinm. r0, r3, 0, 28, 28
	beq lbl_a2_18
	b lbl_a2_20
	lbl_a2_19:
	rlwinm. r0, r3, 0, 28, 28
	bne lbl_a2_18
	lbl_a2_20:
	cmplwi r25, 0x0
	beq lbl_a2_21
	lwz r0, 0x4(r23)
	clrlwi. r0, r0, 31
	beq lbl_a2_18
	lbl_a2_21:
	rlwinm. r0, r3, 0, 26, 26
	bne lbl_a2_18
	lwz r0, 0x1d4(r23)
	rlwinm. r0, r0, 0, 29, 29
	bne lbl_a2_18
	rlwinm. r0, r3, 0, 4, 4
	bne lbl_a2_18
	lfs f2, 0x90(r23)
	lfs f0, 0x150(r23)
	lfs f1, 0x90(r31)
	fadds f0, f2, f0
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq lbl_a2_18
	lfs f0, 0x1b8(r31)
	fadds f0, f1, f0
	fcmpo cr0, f0, f2
	cror eq, lt, eq
	beq lbl_a2_18
	lfs f1, 0x94(r31)
	lfs f0, 0x94(r23)
	lfs f2, 0x8c(r31)
	fsubs f3, f1, f0
	lfs f1, 0x8c(r23)
	lfs f0, float_0_80419b9c(r2)
	fsubs f2, f2, f1
	fmuls f1, f3, f3
	fmadds f4, f2, f2, f1
	fcmpo cr0, f4, f0
	ble lbl_a2_22
	frsqrte f1, f4
	lfd f3, 0x1c0(r29)
	lfd f2, 0x1c8(r29)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f0, f1, f0
	fmul f4, f4, f0
	frsp f4, f4
	b lbl_a2_23
	lbl_a2_22:
	lfd f0, 0x1d0(r29)
	fcmpo cr0, f4, f0
	bge lbl_a2_24
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	b lbl_a2_23
	lbl_a2_24:
	stfs f4, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_25
	bge lbl_a2_26
	cmpwi r3, 0x0
	beq lbl_a2_27
	b lbl_a2_26
	lbl_a2_25:
	clrlwi. r0, r4, 9
	beq lbl_a2_28
	li r0, 0x1
	b lbl_a2_29
	lbl_a2_28:
	li r0, 0x2
	b lbl_a2_29
	lbl_a2_27:
	clrlwi. r0, r4, 9
	beq lbl_a2_30
	li r0, 0x5
	b lbl_a2_29
	lbl_a2_30:
	li r0, 0x3
	b lbl_a2_29
	lbl_a2_26:
	li r0, 0x4
	lbl_a2_29:
	cmpwi r0, 0x1
	bne lbl_a2_23
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	lbl_a2_23:
	stfs f4, 0x24(r1)
	lfs f2, float_0p5_80419ba0(r2)
	lfs f1, 0x1b4(r31)
	lfs f0, 0x14c(r23)
	fadds f0, f1, f0
	fmuls f0, f2, f0
	fcmpo cr0, f4, f0
	bgt lbl_a2_18
	lfs f0, 0x30(r1)
	fcmpo cr0, f4, f0
	cror eq, gt, eq
	beq lbl_a2_18
	cmplwi r26, 0x0
	beq lbl_a2_31
	lwz r0, 0x1d4(r23)
	rlwinm. r0, r0, 0, 15, 15
	bne lbl_a2_31
	lha r0, 0x4c(r31)
	cmpwi r0, 0x0
	bgt lbl_a2_31
	lwz r0, 0x2f8(r23)
	cmpwi r0, 0x0
	beq lbl_a2_32
	lwz r3, 0x11c(r23)
	bl evtGetPtrID
	cmplwi r3, 0x0
	beq lbl_a2_33
	lwz r3, 0x11c(r23)
	bl evtGetPtrID
	lbz r0, 0x10(r3)
	subfic r0, r0, 0x5
	cntlzw r0, r0
	srwi r0, r0, 5
	b lbl_a2_34
	lbl_a2_33:
	li r0, 0x0
	lbl_a2_34:
	cmpwi r0, 0x0
	beq lbl_a2_35
	lbl_a2_32:
	lwz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 2, 2
	bne lbl_a2_18
	lfs f0, 0x24(r1)
	lis r5, 0x1
	cmplwi r25, 0x0
	stw r5, 0x28(r1)
	mr r24, r23
	stfs f0, 0x30(r1)
	bne lbl_a2_31
	lwz r3, gp(r13)
	li r4, 0x0
	lis r0, 0x20
	lwz r3, 0x168(r3)
	stw r4, 0x550(r3)
	stw r5, 0x554(r3)
	stw r4, 0x55c(r3)
	lwz r4, 0x554(r3)
	cmpw r4, r0
	beq lbl_a2_36
	bge lbl_a2_37
	lis r0, 0x8
	cmpw r4, r0
	beq lbl_a2_36
	bge lbl_a2_38
	lis r0, 0x4
	cmpw r4, r0
	beq lbl_a2_36
	bge lbl_a2_39
	lis r0, 0x2
	cmpw r4, r0
	beq lbl_a2_36
	b lbl_a2_39
	lbl_a2_38:
	lis r0, 0x10
	cmpw r4, r0
	beq lbl_a2_36
	b lbl_a2_39
	lbl_a2_37:
	lis r0, 0x100
	cmpw r4, r0
	beq lbl_a2_36
	bge lbl_a2_40
	lis r0, 0x80
	cmpw r4, r0
	beq lbl_a2_36
	bge lbl_a2_39
	lis r0, 0x40
	cmpw r4, r0
	beq lbl_a2_36
	b lbl_a2_39
	lbl_a2_40:
	lis r0, 0x1000
	cmpw r4, r0
	beq lbl_a2_41
	b lbl_a2_39
	lbl_a2_36:
	addi r4, r29, 0x1e0
	li r0, 0x2
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_31
	lbl_a2_41:
	addi r4, r29, 0x1f0
	li r0, 0x1
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_31
	lbl_a2_39:
	li r0, 0x0
	stw r0, 0x558(r3)
	b lbl_a2_31
	lbl_a2_35:
	li r3, 0x140
	bl pouchEquipCheckBadge
	cmpwi r3, 0x0
	beq lbl_a2_42
	lfs f0, 0x24(r1)
	lis r5, 0x1
	cmplwi r25, 0x0
	stw r5, 0x28(r1)
	mr r24, r23
	stfs f0, 0x30(r1)
	bne lbl_a2_31
	lwz r3, gp(r13)
	li r4, 0x0
	lis r0, 0x20
	lwz r3, 0x168(r3)
	stw r4, 0x550(r3)
	stw r5, 0x554(r3)
	stw r4, 0x55c(r3)
	lwz r4, 0x554(r3)
	cmpw r4, r0
	beq lbl_a2_43
	bge lbl_a2_44
	lis r0, 0x8
	cmpw r4, r0
	beq lbl_a2_43
	bge lbl_a2_45
	lis r0, 0x4
	cmpw r4, r0
	beq lbl_a2_43
	bge lbl_a2_46
	lis r0, 0x2
	cmpw r4, r0
	beq lbl_a2_43
	b lbl_a2_46
	lbl_a2_45:
	lis r0, 0x10
	cmpw r4, r0
	beq lbl_a2_43
	b lbl_a2_46
	lbl_a2_44:
	lis r0, 0x100
	cmpw r4, r0
	beq lbl_a2_43
	bge lbl_a2_47
	lis r0, 0x80
	cmpw r4, r0
	beq lbl_a2_43
	bge lbl_a2_46
	lis r0, 0x40
	cmpw r4, r0
	beq lbl_a2_43
	b lbl_a2_46
	lbl_a2_47:
	lis r0, 0x1000
	cmpw r4, r0
	beq lbl_a2_48
	b lbl_a2_46
	lbl_a2_43:
	addi r4, r29, 0x1e0
	li r0, 0x2
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_31
	lbl_a2_48:
	addi r4, r29, 0x1f0
	li r0, 0x1
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_31
	lbl_a2_46:
	li r0, 0x0
	stw r0, 0x558(r3)
	b lbl_a2_31
	lbl_a2_42:
	lfs f0, 0x24(r1)
	lis r5, 0x1000
	cmplwi r25, 0x0
	stw r5, 0x28(r1)
	mr r24, r23
	stfs f0, 0x30(r1)
	bne lbl_a2_49
	lwz r3, gp(r13)
	li r4, 0x0
	lis r0, 0x20
	lwz r3, 0x168(r3)
	stw r4, 0x550(r3)
	stw r5, 0x554(r3)
	stw r4, 0x55c(r3)
	lwz r4, 0x554(r3)
	cmpw r4, r0
	beq lbl_a2_50
	bge lbl_a2_51
	lis r0, 0x8
	cmpw r4, r0
	beq lbl_a2_50
	bge lbl_a2_52
	lis r0, 0x4
	cmpw r4, r0
	beq lbl_a2_50
	bge lbl_a2_53
	lis r0, 0x2
	cmpw r4, r0
	beq lbl_a2_50
	b lbl_a2_53
	lbl_a2_52:
	lis r0, 0x10
	cmpw r4, r0
	beq lbl_a2_50
	b lbl_a2_53
	lbl_a2_51:
	lis r0, 0x100
	cmpw r4, r0
	beq lbl_a2_50
	bge lbl_a2_54
	lis r0, 0x80
	cmpw r4, r0
	beq lbl_a2_50
	bge lbl_a2_53
	lis r0, 0x40
	cmpw r4, r0
	beq lbl_a2_50
	b lbl_a2_53
	lbl_a2_54:
	cmpw r4, r5
	beq lbl_a2_55
	b lbl_a2_53
	lbl_a2_50:
	addi r4, r29, 0x1e0
	li r0, 0x2
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_49
	lbl_a2_55:
	addi r4, r29, 0x1f0
	li r0, 0x1
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_49
	lbl_a2_53:
	li r0, 0x0
	stw r0, 0x558(r3)
	lbl_a2_49:
	lwz r0, 0x2f8(r23)
	stw r0, 0x2c(r1)
	lbl_a2_31:
	cmplwi r27, 0x0
	beq lbl_a2_18
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 14, 14
	beq lbl_a2_56
	rlwinm. r0, r3, 0, 15, 15
	bne lbl_a2_56
	lwz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 2, 2
	bne lbl_a2_56
	lfs f0, 0x24(r1)
	mr r24, r23
	stfs f0, 0x30(r1)
	bl marioGetJabaraState
	cmpwi r3, 0x6
	bne lbl_a2_57
	lis r5, 0x2
	cmplwi r25, 0x0
	stw r5, 0x28(r1)
	bne lbl_a2_18
	lwz r3, gp(r13)
	li r4, 0x0
	lis r0, 0x20
	lwz r3, 0x168(r3)
	stw r4, 0x550(r3)
	stw r5, 0x554(r3)
	stw r4, 0x55c(r3)
	lwz r4, 0x554(r3)
	cmpw r4, r0
	beq lbl_a2_58
	bge lbl_a2_59
	lis r0, 0x8
	cmpw r4, r0
	beq lbl_a2_58
	bge lbl_a2_60
	lis r0, 0x4
	cmpw r4, r0
	beq lbl_a2_58
	bge lbl_a2_61
	cmpw r4, r5
	beq lbl_a2_58
	b lbl_a2_61
	lbl_a2_60:
	lis r0, 0x10
	cmpw r4, r0
	beq lbl_a2_58
	b lbl_a2_61
	lbl_a2_59:
	lis r0, 0x100
	cmpw r4, r0
	beq lbl_a2_58
	bge lbl_a2_62
	lis r0, 0x80
	cmpw r4, r0
	beq lbl_a2_58
	bge lbl_a2_61
	lis r0, 0x40
	cmpw r4, r0
	beq lbl_a2_58
	b lbl_a2_61
	lbl_a2_62:
	lis r0, 0x1000
	cmpw r4, r0
	beq lbl_a2_63
	b lbl_a2_61
	lbl_a2_58:
	addi r4, r29, 0x1e0
	li r0, 0x2
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_18
	lbl_a2_63:
	addi r4, r29, 0x1f0
	li r0, 0x1
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_18
	lbl_a2_61:
	li r0, 0x0
	stw r0, 0x558(r3)
	b lbl_a2_18
	lbl_a2_57:
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x10
	bne lbl_a2_64
	lis r5, 0x4
	cmplwi r25, 0x0
	stw r5, 0x28(r1)
	bne lbl_a2_18
	lwz r3, gp(r13)
	li r4, 0x0
	lis r0, 0x20
	lwz r3, 0x168(r3)
	stw r4, 0x550(r3)
	stw r5, 0x554(r3)
	stw r4, 0x55c(r3)
	lwz r4, 0x554(r3)
	cmpw r4, r0
	beq lbl_a2_65
	bge lbl_a2_66
	lis r0, 0x8
	cmpw r4, r0
	beq lbl_a2_65
	bge lbl_a2_67
	cmpw r4, r5
	beq lbl_a2_65
	bge lbl_a2_68
	lis r0, 0x2
	cmpw r4, r0
	beq lbl_a2_65
	b lbl_a2_68
	lbl_a2_67:
	lis r0, 0x10
	cmpw r4, r0
	beq lbl_a2_65
	b lbl_a2_68
	lbl_a2_66:
	lis r0, 0x100
	cmpw r4, r0
	beq lbl_a2_65
	bge lbl_a2_69
	lis r0, 0x80
	cmpw r4, r0
	beq lbl_a2_65
	bge lbl_a2_68
	lis r0, 0x40
	cmpw r4, r0
	beq lbl_a2_65
	b lbl_a2_68
	lbl_a2_69:
	lis r0, 0x1000
	cmpw r4, r0
	beq lbl_a2_70
	b lbl_a2_68
	lbl_a2_65:
	addi r4, r29, 0x1e0
	li r0, 0x2
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_18
	lbl_a2_70:
	addi r4, r29, 0x1f0
	li r0, 0x1
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_18
	lbl_a2_68:
	li r0, 0x0
	stw r0, 0x558(r3)
	b lbl_a2_18
	lbl_a2_64:
	lis r5, 0x2
	cmplwi r25, 0x0
	stw r5, 0x28(r1)
	bne lbl_a2_18
	lwz r3, gp(r13)
	li r4, 0x0
	lis r0, 0x20
	lwz r3, 0x168(r3)
	stw r4, 0x550(r3)
	stw r5, 0x554(r3)
	stw r4, 0x55c(r3)
	lwz r4, 0x554(r3)
	cmpw r4, r0
	beq lbl_a2_71
	bge lbl_a2_72
	lis r0, 0x8
	cmpw r4, r0
	beq lbl_a2_71
	bge lbl_a2_73
	lis r0, 0x4
	cmpw r4, r0
	beq lbl_a2_71
	bge lbl_a2_74
	cmpw r4, r5
	beq lbl_a2_71
	b lbl_a2_74
	lbl_a2_73:
	lis r0, 0x10
	cmpw r4, r0
	beq lbl_a2_71
	b lbl_a2_74
	lbl_a2_72:
	lis r0, 0x100
	cmpw r4, r0
	beq lbl_a2_71
	bge lbl_a2_75
	lis r0, 0x80
	cmpw r4, r0
	beq lbl_a2_71
	bge lbl_a2_74
	lis r0, 0x40
	cmpw r4, r0
	beq lbl_a2_71
	b lbl_a2_74
	lbl_a2_75:
	lis r0, 0x1000
	cmpw r4, r0
	beq lbl_a2_76
	b lbl_a2_74
	lbl_a2_71:
	addi r4, r29, 0x1e0
	li r0, 0x2
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_18
	lbl_a2_76:
	addi r4, r29, 0x1f0
	li r0, 0x1
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_18
	lbl_a2_74:
	li r0, 0x0
	stw r0, 0x558(r3)
	b lbl_a2_18
	lbl_a2_56:
	bl marioGetJabaraState
	cmpwi r3, 0x6
	bne lbl_a2_18
	lwz r0, 0x0(r23)
	rlwinm. r0, r0, 0, 2, 2
	bne lbl_a2_18
	lfs f0, 0x24(r1)
	lis r5, 0x2
	cmplwi r25, 0x0
	stw r5, 0x28(r1)
	mr r24, r23
	stfs f0, 0x30(r1)
	bne lbl_a2_18
	lwz r3, gp(r13)
	li r4, 0x0
	lis r0, 0x20
	lwz r3, 0x168(r3)
	stw r4, 0x550(r3)
	stw r5, 0x554(r3)
	stw r4, 0x55c(r3)
	lwz r4, 0x554(r3)
	cmpw r4, r0
	beq lbl_a2_77
	bge lbl_a2_78
	lis r0, 0x8
	cmpw r4, r0
	beq lbl_a2_77
	bge lbl_a2_79
	lis r0, 0x4
	cmpw r4, r0
	beq lbl_a2_77
	bge lbl_a2_80
	cmpw r4, r5
	beq lbl_a2_77
	b lbl_a2_80
	lbl_a2_79:
	lis r0, 0x10
	cmpw r4, r0
	beq lbl_a2_77
	b lbl_a2_80
	lbl_a2_78:
	lis r0, 0x100
	cmpw r4, r0
	beq lbl_a2_77
	bge lbl_a2_81
	lis r0, 0x80
	cmpw r4, r0
	beq lbl_a2_77
	bge lbl_a2_80
	lis r0, 0x40
	cmpw r4, r0
	beq lbl_a2_77
	b lbl_a2_80
	lbl_a2_81:
	lis r0, 0x1000
	cmpw r4, r0
	beq lbl_a2_82
	b lbl_a2_80
	lbl_a2_77:
	addi r4, r29, 0x1e0
	li r0, 0x2
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_18
	lbl_a2_82:
	addi r4, r29, 0x1f0
	li r0, 0x1
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_18
	lbl_a2_80:
	li r0, 0x0
	stw r0, 0x558(r3)
	lbl_a2_18:
	addi r22, r22, 0x1
	addi r23, r23, 0x340
	lbl_a2_16:
	cmpw r22, r21
	blt lbl_a2_17
	lbl_a2_3:
	rlwinm. r0, r19, 0, 25, 25
	beq lbl_a2_83
	b lbl_a2_84
	lbl_a2_85:
	rlwinm. r0, r19, 0, 27, 27
	beq lbl_a2_86
	lha r0, 0x4c(r31)
	cmpwi r0, 0x0
	bgt lbl_a2_83
	lbl_a2_86:
	bl marioGetPtr
	lwz r5, gp(r13)
	mr r22, r3
	la r3, work(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq lbl_a2_87
	addi r3, r3, 0x14
	lbl_a2_87:
	lwz r4, 0x0(r22)
	andis. r0, r4, 0x8200
	beq lbl_a2_88
	li r0, 0x0
	b lbl_a2_89
	lbl_a2_88:
	lwz r0, 0x8(r3)
	clrlwi. r0, r0, 31
	bne lbl_a2_90
	andi. r0, r4, 0xa
	beq lbl_a2_90
	li r0, 0x0
	b lbl_a2_89
	lbl_a2_90:
	lwz r0, 0x164(r5)
	cmpwi r0, 0x0
	beq lbl_a2_91
	li r0, 0x0
	b lbl_a2_89
	lbl_a2_91:
	bl seqGetSeq
	cmpwi r3, 0x2
	beq lbl_a2_92
	li r0, 0x0
	b lbl_a2_89
	lbl_a2_92:
	lhz r0, 0x2e(r22)
	cmplwi r0, 0x19
	bne lbl_a2_93
	li r0, 0x0
	b lbl_a2_89
	lbl_a2_93:
	bl vivianGetStatus
	cmpwi r3, 0x0
	beq lbl_a2_94
	li r0, 0x0
	b lbl_a2_89
	lbl_a2_94:
	lhz r0, 0x2e(r22)
	cmplwi r0, 0x1f
	beq lbl_a2_95
	cmplwi r0, 0x20
	bne lbl_a2_96
	lbl_a2_95:
	li r0, 0x0
	b lbl_a2_89
	lbl_a2_96:
	lhz r0, 0x320(r23)
	cmplwi r0, 0x0
	beq lbl_a2_97
	li r0, 0x0
	b lbl_a2_89
	lbl_a2_97:
	li r0, 0x1
	lbl_a2_89:
	cmpwi r0, 0x0
	beq lbl_a2_83
	clrlwi. r0, r19, 31
	beq lbl_a2_98
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x12
	bne lbl_a2_83
	lfs f1, float_1p5_80419bcc(r2)
	li r3, 0x4
	lfs f0, 0x1b4(r31)
	fmuls f31, f1, f0
	bl camGetPtr
	lfs f1, 0x1a8(r31)
	lfs f0, float_90_80419bd0(r2)
	lfs f2, 0x114(r3)
	fsubs f0, f1, f0
	fadds f1, f0, f2
	bl reviseAngle
	fmr f29, f1
	bl marioGetPtr
	mr r22, r3
	bl marioAnimeId
	slwi r0, r3, 2
	add r3, r22, r0
	lwz r3, 0x228(r3)
	bl animPoseGetAnimPosePtr
	lwz r0, 0x48(r22)
	cmpwi r0, 0x14
	ble lbl_a2_99
	li r0, 0xa
	lbl_a2_99:
	xoris r3, r0, 0x8000
	lis r0, 0x4330
	stw r3, 0x6c(r1)
	lfd f1, 0x1d8(r29)
	stw r0, 0x68(r1)
	lfd f0, 0x68(r1)
	fsubs f30, f0, f1
	bl marioGetPtr
	lfs f0, float_0_80419b9c(r2)
	mr r22, r3
	lwz r12, 0x24(r29)
	lwz r11, 0x28(r29)
	fcmpo cr0, f30, f0
	lwz r10, 0x2c(r29)
	lwz r9, 0x30(r29)
	lwz r8, 0x34(r29)
	lwz r7, 0x38(r29)
	lwz r6, 0x3c(r29)
	lwz r5, 0x40(r29)
	lwz r4, 0x44(r29)
	lwz r3, 0x48(r29)
	lwz r0, 0x4c(r29)
	stw r12, 0x38(r1)
	stw r11, 0x3c(r1)
	stw r10, 0x40(r1)
	stw r9, 0x44(r1)
	stw r8, 0x48(r1)
	stw r7, 0x4c(r1)
	stw r6, 0x50(r1)
	stw r5, 0x54(r1)
	stw r4, 0x58(r1)
	stw r3, 0x5c(r1)
	stw r0, 0x60(r1)
	bge lbl_a2_100
	fmr f30, f0
	lbl_a2_100:
	lfs f0, float_11_80419bbc(r2)
	fcmpo cr0, f30, f0
	cror eq, gt, eq
	bne lbl_a2_101
	lfs f30, float_10_80419bb8(r2)
	lbl_a2_101:
	fmr f1, f29
	addi r3, r1, 0x14
	addi r4, r1, 0x18
	bl sincosf
	fctiwz f0, f30
	lis r0, 0x4330
	addi r5, r1, 0x38
	stw r0, 0x78(r1)
	lfd f1, 0x1d8(r29)
	addi r3, r1, 0x1c
	stfd f0, 0x70(r1)
	addi r4, r1, 0x20
	lwz r0, 0x74(r1)
	slwi r0, r0, 2
	lwzx r0, r5, r0
	xoris r0, r0, 0x8000
	stw r0, 0x7c(r1)
	lfd f0, 0x78(r1)
	fsubs f1, f0, f1
	bl sincosf
	lfs f1, 0x14(r1)
	rlwinm r26, r19, 0, 19, 19
	lfs f0, 0x18(r1)
	li r27, 0x0
	fmuls f5, f1, f31
	lfs f6, 0x1c(r1)
	lfs f4, 0x8c(r22)
	fmuls f3, f0, f31
	lfs f2, 0x94(r22)
	lfs f1, 0x20(r1)
	lfs f0, 0x90(r22)
	fmadds f30, f6, f5, f4
	fmadds f29, f6, f3, f2
	lwz r23, 0xc(r30)
	fmadds f31, f31, f1, f0
	b lbl_a2_102
	lbl_a2_103:
	cmplwi r23, 0x0
	beq lbl_a2_104
	lwz r3, 0x0(r23)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_104
	cmplwi r26, 0x0
	beq lbl_a2_105
	rlwinm. r0, r3, 0, 28, 28
	beq lbl_a2_104
	b lbl_a2_106
	lbl_a2_105:
	rlwinm. r0, r3, 0, 28, 28
	bne lbl_a2_104
	lbl_a2_106:
	cmplwi r25, 0x0
	beq lbl_a2_107
	lwz r0, 0x4(r23)
	rlwinm. r0, r0, 0, 30, 30
	beq lbl_a2_104
	lbl_a2_107:
	rlwinm. r0, r3, 0, 2, 2
	bne lbl_a2_104
	rlwinm. r0, r3, 0, 26, 26
	bne lbl_a2_104
	rlwinm. r0, r3, 0, 4, 4
	bne lbl_a2_104
	lwz r0, 0x1d4(r23)
	rlwinm. r0, r0, 0, 29, 29
	bne lbl_a2_104
	fmr f1, f30
	lfs f4, float_12_80419bc0(r2)
	fmr f2, f31
	mr r3, r23
	fmr f3, f29
	addi r4, r1, 0x24
	bl _npcHitCheckSphere
	cmplwi r3, 0x0
	beq lbl_a2_104
	lfs f1, 0x24(r1)
	lfs f0, 0x30(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq lbl_a2_104
	lis r5, 0x10
	cmplwi r25, 0x0
	stfs f1, 0x30(r1)
	mr r24, r23
	stw r5, 0x28(r1)
	bne lbl_a2_83
	lwz r4, gp(r13)
	li r3, 0x0
	lis r0, 0x20
	lwz r4, 0x168(r4)
	stw r3, 0x550(r4)
	stw r5, 0x554(r4)
	stw r3, 0x55c(r4)
	lwz r3, 0x554(r4)
	cmpw r3, r0
	beq lbl_a2_108
	bge lbl_a2_109
	lis r0, 0x8
	cmpw r3, r0
	beq lbl_a2_108
	bge lbl_a2_110
	lis r0, 0x4
	cmpw r3, r0
	beq lbl_a2_108
	bge lbl_a2_111
	lis r0, 0x2
	cmpw r3, r0
	beq lbl_a2_108
	b lbl_a2_111
	lbl_a2_110:
	cmpw r3, r5
	beq lbl_a2_108
	b lbl_a2_111
	lbl_a2_109:
	lis r0, 0x100
	cmpw r3, r0
	beq lbl_a2_108
	bge lbl_a2_112
	lis r0, 0x80
	cmpw r3, r0
	beq lbl_a2_108
	bge lbl_a2_111
	lis r0, 0x40
	cmpw r3, r0
	beq lbl_a2_108
	b lbl_a2_111
	lbl_a2_112:
	lis r0, 0x1000
	cmpw r3, r0
	beq lbl_a2_113
	b lbl_a2_111
	lbl_a2_108:
	addi r3, r29, 0x1e0
	li r0, 0x2
	stw r3, 0x568(r4)
	stw r0, 0x558(r4)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r4)
	b lbl_a2_83
	lbl_a2_113:
	addi r3, r29, 0x1f0
	li r0, 0x1
	stw r3, 0x568(r4)
	stw r0, 0x558(r4)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r4)
	b lbl_a2_83
	lbl_a2_111:
	li r0, 0x0
	stw r0, 0x558(r4)
	b lbl_a2_83
	lbl_a2_104:
	addi r27, r27, 0x1
	addi r23, r23, 0x340
	lbl_a2_102:
	cmpw r27, r21
	blt lbl_a2_103
	b lbl_a2_83
	lbl_a2_98:
	lfs f1, float_1p5_80419bcc(r2)
	li r3, 0x4
	lfs f0, 0x1b4(r31)
	fmuls f30, f1, f0
	bl camGetPtr
	lfs f1, 0x1a8(r31)
	lfs f0, float_90_80419bd0(r2)
	lfs f2, 0x114(r3)
	fsubs f0, f1, f0
	fadds f1, f0, f2
	bl reviseAngle
	fmr f31, f1
	lwz r23, 0xc(r30)
	rlwinm r22, r19, 0, 19, 19
	li r26, 0x0
	b lbl_a2_114
	lbl_a2_115:
	cmplwi r23, 0x0
	beq lbl_a2_116
	lwz r3, 0x0(r23)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_116
	cmplwi r22, 0x0
	beq lbl_a2_117
	rlwinm. r0, r3, 0, 28, 28
	beq lbl_a2_116
	b lbl_a2_118
	lbl_a2_117:
	rlwinm. r0, r3, 0, 28, 28
	bne lbl_a2_116
	lbl_a2_118:
	cmplwi r25, 0x0
	beq lbl_a2_119
	lwz r0, 0x4(r23)
	rlwinm. r0, r0, 0, 30, 30
	beq lbl_a2_116
	lbl_a2_119:
	rlwinm. r0, r3, 0, 2, 2
	bne lbl_a2_116
	rlwinm. r0, r3, 0, 26, 26
	bne lbl_a2_116
	lwz r0, 0x1d4(r23)
	rlwinm. r0, r0, 0, 29, 29
	bne lbl_a2_116
	rlwinm. r0, r3, 0, 4, 4
	bne lbl_a2_116
	fmr f1, f30
	mr r3, r23
	fmr f2, f31
	addi r4, r1, 0x24
	bl _npcHitCheckHammerAllMotion
	cmplwi r3, 0x0
	beq lbl_a2_116
	lfs f1, 0x24(r1)
	lfs f0, 0x30(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq lbl_a2_116
	lis r5, 0x10
	cmplwi r25, 0x0
	stfs f1, 0x30(r1)
	mr r24, r23
	stw r5, 0x28(r1)
	bne lbl_a2_83
	lwz r4, gp(r13)
	li r3, 0x0
	lis r0, 0x20
	lwz r4, 0x168(r4)
	stw r3, 0x550(r4)
	stw r5, 0x554(r4)
	stw r3, 0x55c(r4)
	lwz r3, 0x554(r4)
	cmpw r3, r0
	beq lbl_a2_120
	bge lbl_a2_121
	lis r0, 0x8
	cmpw r3, r0
	beq lbl_a2_120
	bge lbl_a2_122
	lis r0, 0x4
	cmpw r3, r0
	beq lbl_a2_120
	bge lbl_a2_123
	lis r0, 0x2
	cmpw r3, r0
	beq lbl_a2_120
	b lbl_a2_123
	lbl_a2_122:
	cmpw r3, r5
	beq lbl_a2_120
	b lbl_a2_123
	lbl_a2_121:
	lis r0, 0x100
	cmpw r3, r0
	beq lbl_a2_120
	bge lbl_a2_124
	lis r0, 0x80
	cmpw r3, r0
	beq lbl_a2_120
	bge lbl_a2_123
	lis r0, 0x40
	cmpw r3, r0
	beq lbl_a2_120
	b lbl_a2_123
	lbl_a2_124:
	lis r0, 0x1000
	cmpw r3, r0
	beq lbl_a2_125
	b lbl_a2_123
	lbl_a2_120:
	addi r3, r29, 0x1e0
	li r0, 0x2
	stw r3, 0x568(r4)
	stw r0, 0x558(r4)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r4)
	b lbl_a2_83
	lbl_a2_125:
	addi r3, r29, 0x1f0
	li r0, 0x1
	stw r3, 0x568(r4)
	stw r0, 0x558(r4)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r4)
	b lbl_a2_83
	lbl_a2_123:
	li r0, 0x0
	stw r0, 0x558(r4)
	b lbl_a2_83
	lbl_a2_116:
	addi r26, r26, 0x1
	addi r23, r23, 0x340
	lbl_a2_114:
	cmpw r26, r21
	blt lbl_a2_115
	b lbl_a2_83
	lbl_a2_84:
	cmplwi r24, 0x0
	beq lbl_a2_85
	lbl_a2_83:
	rlwinm. r0, r19, 0, 24, 24
	beq lbl_a2_126
	b lbl_a2_127
	lbl_a2_128:
	rlwinm. r0, r19, 0, 27, 27
	beq lbl_a2_129
	lha r0, 0x4c(r31)
	cmpwi r0, 0x0
	bgt lbl_a2_126
	lbl_a2_129:
	bl marioGetPtr
	lwz r5, gp(r13)
	mr r22, r3
	la r3, work(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq lbl_a2_130
	addi r3, r3, 0x14
	lbl_a2_130:
	lwz r4, 0x0(r22)
	andis. r0, r4, 0x8200
	beq lbl_a2_131
	li r0, 0x0
	b lbl_a2_132
	lbl_a2_131:
	lwz r0, 0x8(r3)
	clrlwi. r0, r0, 31
	bne lbl_a2_133
	andi. r0, r4, 0xa
	beq lbl_a2_133
	li r0, 0x0
	b lbl_a2_132
	lbl_a2_133:
	lwz r0, 0x164(r5)
	cmpwi r0, 0x0
	beq lbl_a2_134
	li r0, 0x0
	b lbl_a2_132
	lbl_a2_134:
	bl seqGetSeq
	cmpwi r3, 0x2
	beq lbl_a2_135
	li r0, 0x0
	b lbl_a2_132
	lbl_a2_135:
	lhz r0, 0x2e(r22)
	cmplwi r0, 0x19
	bne lbl_a2_136
	li r0, 0x0
	b lbl_a2_132
	lbl_a2_136:
	bl vivianGetStatus
	cmpwi r3, 0x0
	beq lbl_a2_137
	li r0, 0x0
	b lbl_a2_132
	lbl_a2_137:
	lhz r0, 0x2e(r22)
	cmplwi r0, 0x1f
	beq lbl_a2_138
	cmplwi r0, 0x20
	bne lbl_a2_139
	lbl_a2_138:
	li r0, 0x0
	b lbl_a2_132
	lbl_a2_139:
	lhz r0, 0x320(r23)
	cmplwi r0, 0x0
	beq lbl_a2_140
	li r0, 0x0
	b lbl_a2_132
	lbl_a2_140:
	li r0, 0x1
	lbl_a2_132:
	cmpwi r0, 0x0
	beq lbl_a2_126
	clrlwi. r0, r19, 31
	beq lbl_a2_141
	lhz r0, 0x2e(r31)
	cmplwi r0, 0x13
	bne lbl_a2_126
	bl marioGetAngleKaitenHammer
	fmr f29, f1
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f29, f0
	blt lbl_a2_126
	lfs f1, float_1p5_80419bcc(r2)
	lfs f0, 0x1b4(r31)
	fmuls f30, f1, f0
	bl marioGetPtr
	fmr f1, f29
	mr r23, r3
	addi r3, r1, 0xc
	addi r4, r1, 0x10
	bl sincosf
	lfs f1, 0xc(r1)
	rlwinm r22, r19, 0, 19, 19
	lfs f0, 0x8c(r23)
	li r26, 0x0
	lfs f3, 0x10(r1)
	lfs f2, 0x94(r23)
	fmadds f29, f1, f30, f0
	lfs f1, float_15_80419bc4(r2)
	lfs f0, 0x90(r23)
	fmadds f31, f3, f30, f2
	lwz r23, 0xc(r30)
	fadds f30, f1, f0
	b lbl_a2_142
	lbl_a2_143:
	cmplwi r23, 0x0
	beq lbl_a2_144
	lwz r3, 0x0(r23)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_144
	cmplwi r22, 0x0
	beq lbl_a2_145
	rlwinm. r0, r3, 0, 28, 28
	beq lbl_a2_144
	b lbl_a2_146
	lbl_a2_145:
	rlwinm. r0, r3, 0, 28, 28
	bne lbl_a2_144
	lbl_a2_146:
	cmplwi r25, 0x0
	beq lbl_a2_147
	lwz r0, 0x4(r23)
	rlwinm. r0, r0, 0, 30, 30
	beq lbl_a2_144
	lbl_a2_147:
	rlwinm. r0, r3, 0, 2, 2
	bne lbl_a2_144
	rlwinm. r0, r3, 0, 26, 26
	bne lbl_a2_144
	lwz r0, 0x1d4(r23)
	rlwinm. r0, r0, 0, 29, 29
	bne lbl_a2_144
	rlwinm. r0, r3, 0, 4, 4
	bne lbl_a2_144
	fmr f1, f29
	lfs f4, float_12_80419bc0(r2)
	fmr f2, f30
	mr r3, r23
	fmr f3, f31
	addi r4, r1, 0x24
	bl _npcHitCheckSphere
	cmplwi r3, 0x0
	beq lbl_a2_144
	lfs f1, 0x24(r1)
	lfs f0, 0x30(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq lbl_a2_144
	stfs f1, 0x30(r1)
	mr r24, r23
	bl pouchGetHammerLv
	cmpwi r3, 0x3
	bge lbl_a2_148
	lis r0, 0x20
	stw r0, 0x28(r1)
	b lbl_a2_149
	lbl_a2_148:
	lis r0, 0x40
	stw r0, 0x28(r1)
	lbl_a2_149:
	cmplwi r25, 0x0
	bne lbl_a2_126
	lwz r3, gp(r13)
	li r4, 0x0
	lwz r5, 0x28(r1)
	lis r0, 0x20
	lwz r3, 0x168(r3)
	stw r4, 0x550(r3)
	stw r5, 0x554(r3)
	stw r4, 0x55c(r3)
	lwz r4, 0x554(r3)
	cmpw r4, r0
	beq lbl_a2_150
	bge lbl_a2_151
	lis r0, 0x8
	cmpw r4, r0
	beq lbl_a2_150
	bge lbl_a2_152
	lis r0, 0x4
	cmpw r4, r0
	beq lbl_a2_150
	bge lbl_a2_153
	lis r0, 0x2
	cmpw r4, r0
	beq lbl_a2_150
	b lbl_a2_153
	lbl_a2_152:
	lis r0, 0x10
	cmpw r4, r0
	beq lbl_a2_150
	b lbl_a2_153
	lbl_a2_151:
	lis r0, 0x100
	cmpw r4, r0
	beq lbl_a2_150
	bge lbl_a2_154
	lis r0, 0x80
	cmpw r4, r0
	beq lbl_a2_150
	bge lbl_a2_153
	lis r0, 0x40
	cmpw r4, r0
	beq lbl_a2_150
	b lbl_a2_153
	lbl_a2_154:
	lis r0, 0x1000
	cmpw r4, r0
	beq lbl_a2_155
	b lbl_a2_153
	lbl_a2_150:
	addi r4, r29, 0x1e0
	li r0, 0x2
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_126
	lbl_a2_155:
	addi r4, r29, 0x1f0
	li r0, 0x1
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_126
	lbl_a2_153:
	li r0, 0x0
	stw r0, 0x558(r3)
	b lbl_a2_126
	lbl_a2_144:
	addi r26, r26, 0x1
	addi r23, r23, 0x340
	lbl_a2_142:
	cmpw r26, r21
	blt lbl_a2_143
	b lbl_a2_126
	lbl_a2_141:
	lfs f1, float_1p5_80419bcc(r2)
	li r3, 0x4
	lfs f0, 0x1b4(r31)
	fmuls f31, f1, f0
	bl camGetPtr
	lfs f1, 0x1a8(r31)
	lfs f0, float_90_80419bd0(r2)
	lfs f2, 0x114(r3)
	fsubs f0, f1, f0
	fadds f1, f0, f2
	bl reviseAngle
	fmr f30, f1
	lwz r23, 0xc(r30)
	rlwinm r22, r19, 0, 19, 19
	li r26, 0x0
	b lbl_a2_156
	lbl_a2_157:
	cmplwi r23, 0x0
	beq lbl_a2_158
	lwz r3, 0x0(r23)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_158
	cmplwi r22, 0x0
	beq lbl_a2_159
	rlwinm. r0, r3, 0, 28, 28
	beq lbl_a2_158
	b lbl_a2_160
	lbl_a2_159:
	rlwinm. r0, r3, 0, 28, 28
	bne lbl_a2_158
	lbl_a2_160:
	cmplwi r25, 0x0
	beq lbl_a2_161
	lwz r0, 0x4(r23)
	rlwinm. r0, r0, 0, 30, 30
	beq lbl_a2_158
	lbl_a2_161:
	rlwinm. r0, r3, 0, 2, 2
	bne lbl_a2_158
	rlwinm. r0, r3, 0, 26, 26
	bne lbl_a2_158
	lwz r0, 0x1d4(r23)
	rlwinm. r0, r0, 0, 29, 29
	bne lbl_a2_158
	rlwinm. r0, r3, 0, 4, 4
	bne lbl_a2_158
	fmr f1, f31
	mr r3, r23
	fmr f2, f30
	addi r4, r1, 0x24
	bl _npcHitCheckHammerAllMotion
	cmplwi r3, 0x0
	beq lbl_a2_158
	lfs f1, 0x24(r1)
	lfs f0, 0x30(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq lbl_a2_158
	stfs f1, 0x30(r1)
	mr r24, r23
	bl pouchGetHammerLv
	cmpwi r3, 0x3
	bge lbl_a2_162
	lis r0, 0x20
	stw r0, 0x28(r1)
	b lbl_a2_163
	lbl_a2_162:
	lis r0, 0x40
	stw r0, 0x28(r1)
	lbl_a2_163:
	cmplwi r25, 0x0
	bne lbl_a2_126
	lwz r3, gp(r13)
	li r4, 0x0
	lwz r5, 0x28(r1)
	lis r0, 0x20
	lwz r3, 0x168(r3)
	stw r4, 0x550(r3)
	stw r5, 0x554(r3)
	stw r4, 0x55c(r3)
	lwz r4, 0x554(r3)
	cmpw r4, r0
	beq lbl_a2_164
	bge lbl_a2_165
	lis r0, 0x8
	cmpw r4, r0
	beq lbl_a2_164
	bge lbl_a2_166
	lis r0, 0x4
	cmpw r4, r0
	beq lbl_a2_164
	bge lbl_a2_167
	lis r0, 0x2
	cmpw r4, r0
	beq lbl_a2_164
	b lbl_a2_167
	lbl_a2_166:
	lis r0, 0x10
	cmpw r4, r0
	beq lbl_a2_164
	b lbl_a2_167
	lbl_a2_165:
	lis r0, 0x100
	cmpw r4, r0
	beq lbl_a2_164
	bge lbl_a2_168
	lis r0, 0x80
	cmpw r4, r0
	beq lbl_a2_164
	bge lbl_a2_167
	lis r0, 0x40
	cmpw r4, r0
	beq lbl_a2_164
	b lbl_a2_167
	lbl_a2_168:
	lis r0, 0x1000
	cmpw r4, r0
	beq lbl_a2_169
	b lbl_a2_167
	lbl_a2_164:
	addi r4, r29, 0x1e0
	li r0, 0x2
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_126
	lbl_a2_169:
	addi r4, r29, 0x1f0
	li r0, 0x1
	stw r4, 0x568(r3)
	stw r0, 0x558(r3)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r3)
	b lbl_a2_126
	lbl_a2_167:
	li r0, 0x0
	stw r0, 0x558(r3)
	b lbl_a2_126
	lbl_a2_158:
	addi r26, r26, 0x1
	addi r23, r23, 0x340
	lbl_a2_156:
	cmpw r26, r21
	blt lbl_a2_157
	b lbl_a2_126
	lbl_a2_127:
	cmplwi r24, 0x0
	beq lbl_a2_128
	lbl_a2_126:
	rlwinm. r0, r19, 0, 23, 23
	beq lbl_a2_170
	bl marioGetPartyId
	bl partyGetPtr
	mr r27, r3
	b lbl_a2_171
	lbl_a2_172:
	rlwinm. r0, r19, 0, 27, 27
	beq lbl_a2_173
	lha r0, 0x4c(r31)
	cmpwi r0, 0x0
	bgt lbl_a2_170
	lbl_a2_173:
	bl marioGetPtr
	lwz r5, gp(r13)
	mr r22, r3
	la r3, work(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq lbl_a2_174
	addi r3, r3, 0x14
	lbl_a2_174:
	lwz r4, 0x0(r22)
	andis. r0, r4, 0x8200
	beq lbl_a2_175
	li r0, 0x0
	b lbl_a2_176
	lbl_a2_175:
	lwz r0, 0x8(r3)
	clrlwi. r0, r0, 31
	bne lbl_a2_177
	andi. r0, r4, 0xa
	beq lbl_a2_177
	li r0, 0x0
	b lbl_a2_176
	lbl_a2_177:
	lwz r0, 0x164(r5)
	cmpwi r0, 0x0
	beq lbl_a2_178
	li r0, 0x0
	b lbl_a2_176
	lbl_a2_178:
	bl seqGetSeq
	cmpwi r3, 0x2
	beq lbl_a2_179
	li r0, 0x0
	b lbl_a2_176
	lbl_a2_179:
	lhz r0, 0x2e(r22)
	cmplwi r0, 0x19
	bne lbl_a2_180
	li r0, 0x0
	b lbl_a2_176
	lbl_a2_180:
	bl vivianGetStatus
	cmpwi r3, 0x0
	beq lbl_a2_181
	li r0, 0x0
	b lbl_a2_176
	lbl_a2_181:
	lhz r0, 0x2e(r22)
	cmplwi r0, 0x1f
	beq lbl_a2_182
	cmplwi r0, 0x20
	bne lbl_a2_183
	lbl_a2_182:
	li r0, 0x0
	b lbl_a2_176
	lbl_a2_183:
	lhz r0, 0x320(r23)
	cmplwi r0, 0x0
	beq lbl_a2_184
	li r0, 0x0
	b lbl_a2_176
	lbl_a2_184:
	li r0, 0x1
	lbl_a2_176:
	cmpwi r0, 0x0
	beq lbl_a2_170
	clrlwi. r22, r19, 31
	beq lbl_a2_185
	cmplwi r27, 0x0
	beq lbl_a2_170
	lbz r0, 0x33(r27)
	cmplwi r0, 0x2
	bne lbl_a2_170
	lwz r0, 0x0(r27)
	rlwinm. r0, r0, 0, 23, 23
	beq lbl_a2_170
	mr r3, r27
	bl nokonokoGetStatus
	cmpwi r3, 0x2
	blt lbl_a2_170
	cmpwi r3, 0x5
	bgt lbl_a2_170
	lbl_a2_185:
	cmplwi r22, 0x0
	beq lbl_a2_170
	lfs f3, float_0p5_80419ba0(r2)
	rlwinm r22, r19, 0, 19, 19
	lfs f2, 0xf4(r27)
	li r26, 0x0
	lfs f1, 0xf0(r27)
	lfs f0, 0x5c(r27)
	fmuls f28, f3, f2
	lfs f29, 0x58(r27)
	fmadds f30, f3, f1, f0
	lfs f31, 0x60(r27)
	lwz r23, 0xc(r30)
	b lbl_a2_186
	lbl_a2_187:
	cmplwi r23, 0x0
	beq lbl_a2_188
	lwz r3, 0x0(r23)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_188
	cmplwi r22, 0x0
	beq lbl_a2_189
	rlwinm. r0, r3, 0, 28, 28
	beq lbl_a2_188
	b lbl_a2_190
	lbl_a2_189:
	rlwinm. r0, r3, 0, 28, 28
	bne lbl_a2_188
	lbl_a2_190:
	cmplwi r25, 0x0
	beq lbl_a2_191
	lwz r0, 0x4(r23)
	rlwinm. r0, r0, 0, 29, 29
	beq lbl_a2_188
	lbl_a2_191:
	rlwinm. r0, r3, 0, 2, 2
	bne lbl_a2_188
	rlwinm. r0, r3, 0, 26, 26
	bne lbl_a2_188
	lwz r0, 0x1d4(r23)
	rlwinm. r0, r0, 0, 29, 29
	bne lbl_a2_188
	rlwinm. r0, r3, 0, 4, 4
	bne lbl_a2_188
	fmr f1, f29
	mr r3, r23
	fmr f2, f30
	addi r4, r1, 0x24
	fmr f3, f31
	fmr f4, f28
	bl _npcHitCheckSphere
	cmplwi r3, 0x0
	beq lbl_a2_188
	lfs f1, 0x24(r1)
	lfs f0, 0x30(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq lbl_a2_188
	lis r5, 0x80
	cmplwi r25, 0x0
	stfs f1, 0x30(r1)
	mr r24, r23
	stw r5, 0x28(r1)
	bne lbl_a2_170
	lwz r4, gp(r13)
	li r3, 0x0
	lis r0, 0x20
	lwz r4, 0x168(r4)
	stw r3, 0x550(r4)
	stw r5, 0x554(r4)
	stw r3, 0x55c(r4)
	lwz r3, 0x554(r4)
	cmpw r3, r0
	beq lbl_a2_192
	bge lbl_a2_193
	lis r0, 0x8
	cmpw r3, r0
	beq lbl_a2_192
	bge lbl_a2_194
	lis r0, 0x4
	cmpw r3, r0
	beq lbl_a2_192
	bge lbl_a2_195
	lis r0, 0x2
	cmpw r3, r0
	beq lbl_a2_192
	b lbl_a2_195
	lbl_a2_194:
	lis r0, 0x10
	cmpw r3, r0
	beq lbl_a2_192
	b lbl_a2_195
	lbl_a2_193:
	lis r0, 0x100
	cmpw r3, r0
	beq lbl_a2_192
	bge lbl_a2_196
	cmpw r3, r5
	beq lbl_a2_192
	bge lbl_a2_195
	lis r0, 0x40
	cmpw r3, r0
	beq lbl_a2_192
	b lbl_a2_195
	lbl_a2_196:
	lis r0, 0x1000
	cmpw r3, r0
	beq lbl_a2_197
	b lbl_a2_195
	lbl_a2_192:
	addi r3, r29, 0x1e0
	li r0, 0x2
	stw r3, 0x568(r4)
	stw r0, 0x558(r4)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r4)
	b lbl_a2_170
	lbl_a2_197:
	addi r3, r29, 0x1f0
	li r0, 0x1
	stw r3, 0x568(r4)
	stw r0, 0x558(r4)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r4)
	b lbl_a2_170
	lbl_a2_195:
	li r0, 0x0
	stw r0, 0x558(r4)
	b lbl_a2_170
	lbl_a2_188:
	addi r26, r26, 0x1
	addi r23, r23, 0x340
	lbl_a2_186:
	cmpw r26, r21
	blt lbl_a2_187
	b lbl_a2_170
	lbl_a2_171:
	cmplwi r24, 0x0
	beq lbl_a2_172
	lbl_a2_170:
	rlwinm. r0, r19, 0, 22, 22
	beq lbl_a2_198
	bl marioGetPartyId
	bl partyGetPtr
	mr r26, r3
	b lbl_a2_199
	lbl_a2_200:
	rlwinm. r0, r19, 0, 27, 27
	beq lbl_a2_201
	lha r0, 0x4c(r31)
	cmpwi r0, 0x0
	bgt lbl_a2_198
	lbl_a2_201:
	bl marioGetPtr
	lwz r5, gp(r13)
	mr r22, r3
	la r3, work(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq lbl_a2_202
	addi r3, r3, 0x14
	lbl_a2_202:
	lwz r4, 0x0(r22)
	andis. r0, r4, 0x8200
	beq lbl_a2_203
	li r0, 0x0
	b lbl_a2_204
	lbl_a2_203:
	lwz r0, 0x8(r3)
	clrlwi. r0, r0, 31
	bne lbl_a2_205
	andi. r0, r4, 0xa
	beq lbl_a2_205
	li r0, 0x0
	b lbl_a2_204
	lbl_a2_205:
	lwz r0, 0x164(r5)
	cmpwi r0, 0x0
	beq lbl_a2_206
	li r0, 0x0
	b lbl_a2_204
	lbl_a2_206:
	bl seqGetSeq
	cmpwi r3, 0x2
	beq lbl_a2_207
	li r0, 0x0
	b lbl_a2_204
	lbl_a2_207:
	lhz r0, 0x2e(r22)
	cmplwi r0, 0x19
	bne lbl_a2_208
	li r0, 0x0
	b lbl_a2_204
	lbl_a2_208:
	bl vivianGetStatus
	cmpwi r3, 0x0
	beq lbl_a2_209
	li r0, 0x0
	b lbl_a2_204
	lbl_a2_209:
	lhz r0, 0x2e(r22)
	cmplwi r0, 0x1f
	beq lbl_a2_210
	cmplwi r0, 0x20
	bne lbl_a2_211
	lbl_a2_210:
	li r0, 0x0
	b lbl_a2_204
	lbl_a2_211:
	lhz r0, 0x320(r23)
	cmplwi r0, 0x0
	beq lbl_a2_212
	li r0, 0x0
	b lbl_a2_204
	lbl_a2_212:
	li r0, 0x1
	lbl_a2_204:
	cmpwi r0, 0x0
	beq lbl_a2_198
	clrlwi. r0, r19, 31
	beq lbl_a2_198
	cmplwi r26, 0x0
	beq lbl_a2_198
	lbz r0, 0x33(r26)
	cmplwi r0, 0x3
	bne lbl_a2_198
	lwz r3, gp(r13)
	lwz r3, 0x168(r3)
	lbz r0, 0x54d(r3)
	cmplwi r0, 0x0
	beq lbl_a2_198
	lwz r22, 0xc(r30)
	rlwinm r19, r19, 0, 19, 19
	li r23, 0x0
	b lbl_a2_213
	lbl_a2_214:
	cmplwi r22, 0x0
	beq lbl_a2_215
	lwz r3, 0x0(r22)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_215
	cmplwi r19, 0x0
	beq lbl_a2_216
	rlwinm. r0, r3, 0, 28, 28
	beq lbl_a2_215
	b lbl_a2_217
	lbl_a2_216:
	rlwinm. r0, r3, 0, 28, 28
	bne lbl_a2_215
	lbl_a2_217:
	cmplwi r25, 0x0
	beq lbl_a2_218
	lwz r0, 0x4(r22)
	rlwinm. r0, r0, 0, 28, 28
	beq lbl_a2_215
	lbl_a2_218:
	rlwinm. r0, r3, 0, 2, 2
	bne lbl_a2_215
	rlwinm. r0, r3, 0, 26, 26
	bne lbl_a2_215
	lwz r0, 0x1d4(r22)
	rlwinm. r0, r0, 0, 29, 29
	bne lbl_a2_215
	rlwinm. r0, r3, 0, 4, 4
	bne lbl_a2_215
	lfs f3, float_0p5_80419ba0(r2)
	mr r3, r22
	lfs f2, 0xf0(r26)
	addi r4, r1, 0x24
	lfs f0, 0x5c(r26)
	lfs f1, 0x58(r26)
	fmadds f2, f3, f2, f0
	lfs f3, 0x60(r26)
	lfs f4, float_30_80419bd4(r2)
	bl _npcHitCheckSphere
	cmplwi r3, 0x0
	beq lbl_a2_215
	lfs f1, 0x24(r1)
	lfs f0, 0x30(r1)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	beq lbl_a2_215
	lis r5, 0x100
	cmplwi r25, 0x0
	stfs f1, 0x30(r1)
	mr r24, r22
	stw r5, 0x28(r1)
	bne lbl_a2_198
	lwz r4, gp(r13)
	li r3, 0x0
	lis r0, 0x20
	lwz r4, 0x168(r4)
	stw r3, 0x550(r4)
	stw r5, 0x554(r4)
	stw r3, 0x55c(r4)
	lwz r3, 0x554(r4)
	cmpw r3, r0
	beq lbl_a2_219
	bge lbl_a2_220
	lis r0, 0x8
	cmpw r3, r0
	beq lbl_a2_219
	bge lbl_a2_221
	lis r0, 0x4
	cmpw r3, r0
	beq lbl_a2_219
	bge lbl_a2_222
	lis r0, 0x2
	cmpw r3, r0
	beq lbl_a2_219
	b lbl_a2_222
	lbl_a2_221:
	lis r0, 0x10
	cmpw r3, r0
	beq lbl_a2_219
	b lbl_a2_222
	lbl_a2_220:
	cmpw r3, r5
	beq lbl_a2_219
	bge lbl_a2_223
	lis r0, 0x80
	cmpw r3, r0
	beq lbl_a2_219
	bge lbl_a2_222
	lis r0, 0x40
	cmpw r3, r0
	beq lbl_a2_219
	b lbl_a2_222
	lbl_a2_223:
	lis r0, 0x1000
	cmpw r3, r0
	beq lbl_a2_224
	b lbl_a2_222
	lbl_a2_219:
	addi r3, r29, 0x1e0
	li r0, 0x2
	stw r3, 0x568(r4)
	stw r0, 0x558(r4)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r4)
	b lbl_a2_198
	lbl_a2_224:
	addi r3, r29, 0x1f0
	li r0, 0x1
	stw r3, 0x568(r4)
	stw r0, 0x558(r4)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r4)
	b lbl_a2_198
	lbl_a2_222:
	li r0, 0x0
	stw r0, 0x558(r4)
	b lbl_a2_198
	lbl_a2_215:
	addi r23, r23, 0x1
	addi r22, r22, 0x340
	lbl_a2_213:
	cmpw r23, r21
	blt lbl_a2_214
	b lbl_a2_198
	lbl_a2_199:
	cmplwi r24, 0x0
	beq lbl_a2_200
	lbl_a2_198:
	cmplwi r20, 0x0
	beq lbl_a2_225
	lwz r3, 0x28(r1)
	lwz r0, 0x2c(r1)
	stw r3, 0x0(r20)
	lwz r3, 0x30(r1)
	stw r0, 0x4(r20)
	lwz r0, 0x34(r1)
	stw r3, 0x8(r20)
	stw r0, 0xc(r20)
	lbl_a2_225:
	mr r3, r24
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	psq_l f29, 0xd8(r1), 0, 0
	lfd f29, 0xd0(r1)
	psq_l f28, 0xc8(r1), 0, 0
	lfd f28, 0xc0(r1)
	lmw r19, 0x8c(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm void fbatHitCheckAll(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x13f1
	li r4, 0x0
	stw r0, 0x14(r1)
	bl fbatHitCheck
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm NpcEntry* fbatNpcTalkCheck(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	la r31, work(r13)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r31, r31, 0x14
	lbl_a2_1:
	lwz r0, 0x10(r31)
	cmplwi r0, 0x0
	beq lbl_a2_2
	bl marioChkTalkable
	cmpwi r3, 0x0
	beq lbl_a2_2
	lwz r3, 0x10(r31)
	b lbl_a2_3
	lbl_a2_2:
	li r3, 0x0
	lbl_a2_3:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void npcGroupDead(NpcEntry* entry, BOOL reason) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r0, 0x32c(r3)
	cmplwi r0, 0x0
	beq lbl_a2_1
	mr r3, r0
	b lbl_a2_1
	lbl_a2_2:
	mr r3, r0
	lbl_a2_1:
	lwz r0, 0x324(r3)
	cmplwi r0, 0x0
	bne lbl_a2_2
	bl _npcGroupDead
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _npcGroupDead(NpcEntry* entry, s32 reason) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r24, 0x10(r1)
	mr r28, r3
	mr r29, r4
	lwz r31, 0x328(r3)
	cmplwi r31, 0x0
	beq lbl_a2_1
	lwz r30, 0x328(r31)
	cmplwi r30, 0x0
	beq lbl_a2_2
	lwz r25, 0x328(r30)
	cmplwi r25, 0x0
	beq lbl_a2_3
	lwz r3, 0x328(r25)
	cmplwi r3, 0x0
	beq lbl_a2_4
	bl _npcGroupDead
	lbl_a2_4:
	li r26, 0x0
	mr r27, r25
	lbl_a2_5:
	lwz r3, 0x330(r27)
	cmplwi r3, 0x0
	beq lbl_a2_6
	mr r4, r29
	bl _npcDead
	lbl_a2_6:
	addi r26, r26, 0x1
	addi r27, r27, 0x4
	cmpwi r26, 0x4
	blt lbl_a2_5
	mr r3, r25
	mr r4, r29
	bl _npcDead
	lbl_a2_3:
	mr r25, r30
	li r26, 0x0
	li r27, 0x1
	lbl_a2_7:
	lwz r24, 0x330(r25)
	cmplwi r24, 0x0
	beq lbl_a2_8
	lwz r0, 0x140(r24)
	ori r0, r0, 0x10
	stw r0, 0x140(r24)
	lwz r0, 0x1d4(r24)
	ori r0, r0, 0x4
	stw r0, 0x1d4(r24)
	sth r29, 0x31c(r24)
	lwz r0, 0x0(r24)
	rlwinm. r0, r0, 0, 29, 29
	beq lbl_a2_8
	bl fbatGetPointer
	lbz r0, 0x314(r24)
	lwz r4, 0x5c(r3)
	slw r0, r27, r0
	or r0, r4, r0
	stw r0, 0x5c(r3)
	lbl_a2_8:
	addi r26, r26, 0x1
	addi r25, r25, 0x4
	cmpwi r26, 0x4
	blt lbl_a2_7
	lwz r0, 0x140(r30)
	ori r0, r0, 0x10
	stw r0, 0x140(r30)
	lwz r0, 0x1d4(r30)
	ori r0, r0, 0x4
	stw r0, 0x1d4(r30)
	sth r29, 0x31c(r30)
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 29, 29
	beq lbl_a2_2
	bl fbatGetPointer
	lbz r0, 0x314(r30)
	li r4, 0x1
	lwz r5, 0x5c(r3)
	slw r0, r4, r0
	or r0, r5, r0
	stw r0, 0x5c(r3)
	lbl_a2_2:
	li r0, 0x2
	mr r6, r31
	li r5, 0x0
	mtctr r0
	lbl_a2_9:
	lwz r7, 0x330(r6)
	cmplwi r7, 0x0
	beq lbl_a2_10
	lwz r0, 0x140(r7)
	ori r0, r0, 0x10
	stw r0, 0x140(r7)
	lwz r0, 0x1d4(r7)
	ori r0, r0, 0x4
	stw r0, 0x1d4(r7)
	sth r29, 0x31c(r7)
	lwz r0, 0x0(r7)
	rlwinm. r0, r0, 0, 29, 29
	beq lbl_a2_10
	lwz r4, gp(r13)
	li r3, 0x1
	lbz r0, 0x314(r7)
	lwz r4, 0x168(r4)
	slw r0, r3, r0
	lwz r3, 0x5c(r4)
	or r0, r3, r0
	stw r0, 0x5c(r4)
	lbl_a2_10:
	lwz r7, 0x334(r6)
	cmplwi r7, 0x0
	beq lbl_a2_11
	lwz r0, 0x140(r7)
	ori r0, r0, 0x10
	stw r0, 0x140(r7)
	lwz r0, 0x1d4(r7)
	ori r0, r0, 0x4
	stw r0, 0x1d4(r7)
	sth r29, 0x31c(r7)
	lwz r0, 0x0(r7)
	rlwinm. r0, r0, 0, 29, 29
	beq lbl_a2_11
	lwz r4, gp(r13)
	li r3, 0x1
	lbz r0, 0x314(r7)
	lwz r4, 0x168(r4)
	slw r0, r3, r0
	lwz r3, 0x5c(r4)
	or r0, r3, r0
	stw r0, 0x5c(r4)
	lbl_a2_11:
	addi r6, r6, 0x8
	addi r5, r5, 0x1
	bdnz lbl_a2_9
	lwz r0, 0x140(r31)
	ori r0, r0, 0x10
	stw r0, 0x140(r31)
	lwz r0, 0x1d4(r31)
	ori r0, r0, 0x4
	stw r0, 0x1d4(r31)
	sth r29, 0x31c(r31)
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 29, 29
	beq lbl_a2_1
	lwz r4, gp(r13)
	li r3, 0x1
	lbz r0, 0x314(r31)
	lwz r4, 0x168(r4)
	slw r0, r3, r0
	lwz r3, 0x5c(r4)
	or r0, r3, r0
	stw r0, 0x5c(r4)
	lbl_a2_1:
	li r0, 0x2
	mr r5, r28
	li r7, 0x0
	mtctr r0
	lbl_a2_12:
	lwz r6, 0x330(r5)
	cmplwi r6, 0x0
	beq lbl_a2_13
	lwz r0, 0x140(r6)
	ori r0, r0, 0x10
	stw r0, 0x140(r6)
	lwz r0, 0x1d4(r6)
	ori r0, r0, 0x4
	stw r0, 0x1d4(r6)
	sth r29, 0x31c(r6)
	lwz r0, 0x0(r6)
	rlwinm. r0, r0, 0, 29, 29
	beq lbl_a2_13
	lwz r4, gp(r13)
	li r3, 0x1
	lbz r0, 0x314(r6)
	lwz r4, 0x168(r4)
	slw r0, r3, r0
	lwz r3, 0x5c(r4)
	or r0, r3, r0
	stw r0, 0x5c(r4)
	lbl_a2_13:
	lwz r6, 0x334(r5)
	cmplwi r6, 0x0
	beq lbl_a2_14
	lwz r0, 0x140(r6)
	ori r0, r0, 0x10
	stw r0, 0x140(r6)
	lwz r0, 0x1d4(r6)
	ori r0, r0, 0x4
	stw r0, 0x1d4(r6)
	sth r29, 0x31c(r6)
	lwz r0, 0x0(r6)
	rlwinm. r0, r0, 0, 29, 29
	beq lbl_a2_14
	lwz r4, gp(r13)
	li r3, 0x1
	lbz r0, 0x314(r6)
	lwz r4, 0x168(r4)
	slw r0, r3, r0
	lwz r3, 0x5c(r4)
	or r0, r3, r0
	stw r0, 0x5c(r4)
	lbl_a2_14:
	addi r5, r5, 0x8
	addi r7, r7, 0x1
	bdnz lbl_a2_12
	lwz r0, 0x140(r28)
	ori r0, r0, 0x10
	stw r0, 0x140(r28)
	lwz r0, 0x1d4(r28)
	ori r0, r0, 0x4
	stw r0, 0x1d4(r28)
	sth r29, 0x31c(r28)
	lwz r0, 0x0(r28)
	rlwinm. r0, r0, 0, 29, 29
	beq lbl_a2_15
	lwz r4, gp(r13)
	li r3, 0x1
	lbz r0, 0x314(r28)
	lwz r4, 0x168(r4)
	slw r0, r3, r0
	lwz r3, 0x5c(r4)
	or r0, r3, r0
	stw r0, 0x5c(r4)
	lbl_a2_15:
	lmw r24, 0x10(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void _npcDead(NpcEntry* npc, s32 reason) {
	nofralloc
	lwz r0, 0x140(r3)
	ori r0, r0, 0x10
	stw r0, 0x140(r3)
	lwz r0, 0x1d4(r3)
	ori r0, r0, 0x4
	stw r0, 0x1d4(r3)
	sth r4, 0x31c(r3)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 29, 29
	beqlr
	lwz r5, gp(r13)
	li r4, 0x1
	lbz r0, 0x314(r3)
	lwz r5, 0x168(r5)
	slw r0, r4, r0
	lwz r3, 0x5c(r5)
	or r0, r3, r0
	stw r0, 0x5c(r5)
	blr
}

asm void fbatBattleMode(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	lwz r3, gp(r13)
	lwz r30, 0x168(r3)
	lwz r29, 0x8(r30)
	bl pouchGetPtr
	mr r31, r3
	bl marioGetPtr
	lfs f0, float_0_80419b9c(r2)
	mr r27, r3
	stfs f0, 0xf0(r29)
	lbz r4, 0x2(r30)
	cmpwi r4, 0x2
	beq lbl_a2_1
	bge lbl_a2_2
	cmpwi r4, 0x0
	beq lbl_a2_3
	bge lbl_a2_4
	b lbl_a2_5
	lbl_a2_2:
	cmpwi r4, 0x4
	beq lbl_a2_6
	bge lbl_a2_5
	b lbl_a2_7
	lbl_a2_3:
	lwz r0, dbg_battleskip(r13)
	cmpwi r0, 0x1
	bne lbl_a2_8
	li r0, 0x1
	sth r0, 0x0(r30)
	b lbl_a2_5
	lbl_a2_8:
	lwz r0, 0x248(r29)
	cmplwi r0, 0x0
	bne lbl_a2_9
	li r0, 0x1
	sth r0, 0x0(r30)
	b lbl_a2_5
	lbl_a2_9:
	lwz r3, gp(r13)
	lwz r0, 0x18(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq lbl_a2_10
	li r0, 0x1
	sth r0, 0x0(r30)
	b lbl_a2_5
	lbl_a2_10:
	lwz r0, 0x12c(r29)
	cmplwi r0, 0x0
	bne lbl_a2_11
	li r0, 0x1
	sth r0, 0x0(r30)
	b lbl_a2_5
	lbl_a2_11:
	lwz r3, 0x8(r30)
	lwz r0, 0x140(r3)
	rlwinm r0, r0, 0, 20, 23
	stw r0, 0x140(r3)
	lwz r3, 0x8(r30)
	lwz r3, 0x11c(r3)
	bl evtStopID
	lwz r0, 0x234(r29)
	addi r28, r30, 0x20
	rlwinm. r0, r0, 0, 3, 3
	bne lbl_a2_12
	li r3, 0x142
	bl pouchEquipCheckBadge
	cmpwi r3, 0x0
	beq lbl_a2_13
	lwz r3, 0x248(r29)
	lha r0, 0x8a(r31)
	lwz r3, 0x4(r3)
	lwz r3, 0x0(r3)
	lbz r3, 0xe(r3)
	cmpw r3, r0
	bge lbl_a2_13
	li r0, 0x1
	li r3, 0x1
	b lbl_a2_14
	lbl_a2_13:
	li r3, 0x141
	bl pouchEquipCheckBadge
	cmpwi r3, 0x0
	beq lbl_a2_12
	lwz r0, 0x10(r30)
	rlwinm. r0, r0, 0, 7, 14
	beq lbl_a2_12
	lwz r3, 0x248(r29)
	lha r0, 0x8a(r31)
	lwz r3, 0x4(r3)
	lwz r3, 0x0(r3)
	lbz r3, 0xe(r3)
	cmpw r3, r0
	bge lbl_a2_12
	li r0, 0x1
	li r3, 0x1
	b lbl_a2_14
	lbl_a2_12:
	lwz r0, dbg_battleskip(r13)
	cmpwi r0, 0x2
	bne lbl_a2_15
	li r0, 0x1
	li r3, 0x1
	b lbl_a2_14
	lbl_a2_15:
	li r0, 0x0
	li r3, 0x0
	lbl_a2_14:
	cmpwi r0, 0x0
	bne lbl_a2_16
	cmpwi r3, 0x0
	bne lbl_a2_17
	lwz r3, gp(r13)
	li r0, 0x1
	lwz r3, 0x168(r3)
	stw r0, 0x550(r3)
	lbl_a2_17:
	bl marioFBattlePrepare
	li r3, 0x4
	li r4, 0x0
	li r5, 0x0
	bl seqSetSeq
	lwz r3, 0x10(r30)
	subis r0, r3, 0x1000
	cmplwi r0, 0x0
	bne lbl_a2_18
	bl unk_80058374
	lbl_a2_18:
	li r0, 0x1
	stb r0, 0x2(r30)
	b lbl_a2_5
	lbl_a2_16:
	cmpwi r3, 0x0
	beq lbl_a2_19
	mr r3, r28
	li r4, 0x2
	bl BattleInformationSetResult
	b lbl_a2_20
	lbl_a2_19:
	mr r3, r28
	li r4, 0x5
	bl BattleInformationSetResult
	lbl_a2_20:
	li r0, 0x4
	stb r0, 0x2(r30)
	b lbl_a2_5
	lbl_a2_4:
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_5
	addi r0, r4, 0x1
	stb r0, 0x2(r30)
	b lbl_a2_5
	lbl_a2_1:
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne lbl_a2_5
	li r0, 0x0
	addi r3, r30, 0x20
	stb r0, 0x54c(r30)
	bl BattleInformationGetResult
	lbz r0, 0x5ba(r31)
	cmplwi r0, 0x4
	bne lbl_a2_21
	cmpwi r3, 0x1
	bne lbl_a2_21
	li r0, 0x3
	lis r3, _evt_majinai_coin_up_effect@ha
	stb r0, 0x2(r30)
	li r0, 0x1
	addi r3, r3, _evt_majinai_coin_up_effect@l
	li r4, 0x0
	stb r0, 0x54c(r30)
	li r5, 0x0
	bl evtEntry
	lwz r0, 0x15c(r3)
	stw r0, 0x48(r30)
	bl BattleMajinaiDone
	bl marioKeyOff
	lwz r3, gp(r13)
	la r4, work(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_22
	addi r4, r4, 0x14
	lbl_a2_22:
	lwz r28, 0x4(r4)
	li r29, 0x0
	lwz r27, 0xc(r4)
	b lbl_a2_23
	lbl_a2_24:
	cmplwi r27, 0x0
	beq lbl_a2_25
	lwz r3, 0x0(r27)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_25
	rlwinm. r0, r3, 0, 3, 3
	beq lbl_a2_25
	lwz r0, 0x1d4(r27)
	oris r0, r0, 0x1
	stw r0, 0x1d4(r27)
	lwz r3, 0x11c(r27)
	bl evtStopID
	lwz r3, 0x104(r27)
	lfs f1, float_0_80419b9c(r2)
	bl animPoseSetLocalTimeRate
	lbl_a2_25:
	addi r29, r29, 0x1
	addi r27, r27, 0x340
	lbl_a2_23:
	cmpw r29, r28
	blt lbl_a2_24
	b lbl_a2_5
	lbl_a2_21:
	bl marioFBattlePost
	li r0, 0x4
	stb r0, 0x2(r30)
	b lbl_a2_5
	lbl_a2_7:
	lwz r3, 0x48(r30)
	bl evtCheckID
	cmpwi r3, 0x0
	bne lbl_a2_5
	bl marioKeyOn
	bl marioFBattlePost
	li r3, 0x0
	li r0, 0x4
	stw r3, 0x48(r30)
	la r4, work(r13)
	stb r0, 0x2(r30)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_26
	addi r4, r4, 0x14
	lbl_a2_26:
	lwz r28, 0x4(r4)
	li r29, 0x0
	lwz r27, 0xc(r4)
	b lbl_a2_27
	lbl_a2_28:
	cmplwi r27, 0x0
	beq lbl_a2_29
	lwz r3, 0x0(r27)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_29
	rlwinm. r0, r3, 0, 3, 3
	beq lbl_a2_29
	lwz r3, 0x1d4(r27)
	rlwinm. r0, r3, 0, 15, 15
	beq lbl_a2_29
	rlwinm r0, r3, 0, 16, 14
	stw r0, 0x1d4(r27)
	lwz r3, 0x11c(r27)
	bl evtStartID
	lwz r3, 0x104(r27)
	lfs f1, float_1_80419bb4(r2)
	bl animPoseSetLocalTimeRate
	lbl_a2_29:
	addi r29, r29, 0x1
	addi r27, r27, 0x340
	lbl_a2_27:
	cmpw r29, r28
	blt lbl_a2_28
	b lbl_a2_5
	lbl_a2_6:
	bl marioChgMoveMotion
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	bne lbl_a2_5
	addi r31, r30, 0x20
	mr r3, r31
	bl BattleInformationGetResult
	lwz r0, 0x28c(r29)
	mr r28, r3
	li r26, 0x0
	cmpwi r0, 0x0
	beq lbl_a2_30
	li r26, 0x1
	b lbl_a2_31
	lbl_a2_30:
	lwz r0, 0x290(r29)
	cmpwi r0, 0x0
	beq lbl_a2_32
	li r26, 0x1
	b lbl_a2_31
	lbl_a2_32:
	lwz r0, 0x294(r29)
	cmpwi r0, 0x0
	beq lbl_a2_33
	li r26, 0x1
	b lbl_a2_31
	lbl_a2_33:
	lwz r0, 0x298(r29)
	cmpwi r0, 0x0
	beq lbl_a2_34
	li r26, 0x1
	b lbl_a2_31
	lbl_a2_34:
	lwz r0, 0x29c(r29)
	cmpwi r0, 0x0
	beq lbl_a2_35
	li r26, 0x1
	b lbl_a2_31
	lbl_a2_35:
	lwz r0, 0x2a0(r29)
	cmpwi r0, 0x0
	beq lbl_a2_36
	li r26, 0x1
	b lbl_a2_31
	lbl_a2_36:
	lwz r0, 0x2a4(r29)
	cmpwi r0, 0x0
	beq lbl_a2_37
	li r26, 0x1
	b lbl_a2_31
	lbl_a2_37:
	lwz r0, 0x2a8(r29)
	cmpwi r0, 0x0
	beq lbl_a2_31
	li r26, 0x1
	lbl_a2_31:
	li r0, 0x1
	cmpwi r28, 0x1
	sth r0, 0x0(r30)
	beq lbl_a2_38
	cmpwi r28, 0x2
	bne lbl_a2_39
	lbl_a2_38:
	mr r3, r31
	li r27, 0x1
	bl BattleInformationGetResult
	cmpwi r3, 0x1
	bne lbl_a2_40
	lwz r0, 0x14(r31)
	stb r0, 0x315(r29)
	b lbl_a2_41
	lbl_a2_40:
	cmpwi r28, 0x1
	bne lbl_a2_42
	lbz r0, 0x316(r29)
	stb r0, 0x315(r29)
	b lbl_a2_41
	lbl_a2_42:
	li r0, 0x0
	li r27, 0x0
	stb r0, 0x315(r29)
	b lbl_a2_43
	lbl_a2_41:
	lbz r0, 0x54c(r30)
	cmplwi r0, 0x0
	beq lbl_a2_44
	li r27, 0x3
	lbl_a2_44:
	li r3, 0x139
	bl pouchEquipCheckBadge
	cmpwi r3, 0x0
	beq lbl_a2_45
	li r3, 0x139
	bl pouchEquipCheckBadge
	add r27, r27, r3
	lbl_a2_45:
	lwz r0, 0x234(r29)
	rlwinm. r0, r0, 0, 23, 23
	beq lbl_a2_43
	addi r27, r27, 0x1
	lbl_a2_43:
	lbz r0, 0x315(r29)
	cmpwi r26, 0x0
	mullw r0, r0, r27
	stb r0, 0x315(r29)
	bne lbl_a2_46
	mr r3, r29
	li r4, 0x0
	bl npcGroupDead
	b lbl_a2_5
	lbl_a2_46:
	lwz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 21, 21
	beq lbl_a2_47
	li r0, 0x0
	stw r0, 0x108(r29)
	lbl_a2_47:
	li r0, 0x5a
	sth r0, 0x320(r29)
	lwz r0, 0x140(r29)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x140(r29)
	lwz r0, 0x140(r29)
	oris r0, r0, 0x1000
	stw r0, 0x140(r29)
	lwz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 22, 22
	beq lbl_a2_48
	lwz r3, 0x104(r29)
	addi r4, r29, 0x2c
	li r5, 0x1
	bl animPoseSetAnim
	lbl_a2_48:
	li r27, 0x0
	addi r30, r29, 0x230
	mr r28, r27
	lbl_a2_49:
	lwz r4, 0x7c(r30)
	cmpwi r4, 0x0
	beq lbl_a2_50
	lfs f1, 0x8c(r29)
	li r3, 0x0
	lfs f2, 0x90(r29)
	li r5, 0xb
	lfs f3, 0x94(r29)
	li r6, -0x1
	li r7, 0x0
	bl itemEntry
	li r4, 0x100
	bl itemFlagOn
	stw r28, 0x7c(r30)
	lbl_a2_50:
	addi r27, r27, 0x1
	addi r30, r30, 0x4
	cmpwi r27, 0x8
	blt lbl_a2_49
	b lbl_a2_5
	lbl_a2_39:
	cmpwi r28, 0x4
	bne lbl_a2_5
	lwz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 21, 21
	beq lbl_a2_51
	li r0, 0x0
	stw r0, 0x108(r29)
	lbl_a2_51:
	lwz r0, 0x140(r29)
	li r3, 0xbb8
	oris r0, r0, 0x1000
	stw r0, 0x140(r29)
	bl marioSetMutekiTime
	li r3, 0xbb8
	bl sysMsec2Frame
	sth r3, 0x2c0(r27)
	lwz r0, 0x0(r29)
	rlwinm. r0, r0, 0, 22, 22
	beq lbl_a2_5
	lwz r3, 0x104(r29)
	addi r4, r29, 0x2c
	li r5, 0x1
	bl animPoseSetAnim
	lbl_a2_5:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void fbatTalkMode(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r3, gp(r13)
	lwz r31, 0x168(r3)
	lwz r30, 0x4(r31)
	bl marioGetPtr
	lbz r0, 0x2(r31)
	mr r29, r3
	cmpwi r0, 0x1
	beq lbl_a2_1
	bge lbl_a2_2
	cmpwi r0, 0x0
	bge lbl_a2_3
	b lbl_a2_2
	lbl_a2_3:
	lwz r3, 0x4(r31)
	lwz r3, 0x11c(r3)
	bl evtStopID
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 7, 7
	bne lbl_a2_4
	lfs f1, 0x8c(r30)
	lfs f2, 0x94(r30)
	lfs f3, 0x8c(r29)
	lfs f4, 0x94(r29)
	bl angleABf
	bl reviseAngle
	stfs f1, 0x144(r30)
	lbl_a2_4:
	bl marioKeyOff
	bl partyKeyOff
	lha r0, 0x0(r31)
	cmpwi r0, 0x3
	beq lbl_a2_5
	b lbl_a2_6
	lbl_a2_5:
	lwz r3, 0x12c(r30)
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	li r0, 0x6
	mr r29, r3
	stb r0, 0x10(r3)
	b lbl_a2_7
	lbl_a2_6:
	lwz r3, 0x128(r30)
	li r4, 0x0
	li r5, 0x0
	bl evtEntry
	li r0, 0x6
	mr r29, r3
	stb r0, 0x10(r3)
	bl marioChgTalkMotion
	lbl_a2_7:
	stw r30, 0x170(r29)
	lwz r0, 0x15c(r29)
	stw r0, 0xc(r31)
	lbz r3, 0x2(r31)
	addi r0, r3, 0x1
	stb r0, 0x2(r31)
	b lbl_a2_2
	lbl_a2_1:
	lwz r3, 0xc(r31)
	bl evtCheckID
	cmpwi r3, 0x0
	bne lbl_a2_2
	lwz r0, 0x1d4(r30)
	rlwinm. r0, r0, 0, 2, 2
	bne lbl_a2_8
	lwz r3, 0x4(r31)
	lwz r3, 0x11c(r3)
	bl evtStartID
	lfs f0, 0x148(r30)
	stfs f0, 0x144(r30)
	lbl_a2_8:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 21, 21
	beq lbl_a2_9
	li r0, 0x0
	stw r0, 0x108(r30)
	lbl_a2_9:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 22, 22
	beq lbl_a2_10
	lwz r3, 0x104(r30)
	addi r4, r30, 0x2c
	li r5, 0x1
	bl animPoseSetAnim
	lbl_a2_10:
	bl marioKeyOn
	bl partyKeyOn
	bl marioChgStayMotion
	li r0, 0x1
	li r5, 0x0
	sth r0, 0x0(r31)
	la r4, work(r13)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_11
	addi r4, r4, 0x14
	lbl_a2_11:
	stw r5, 0x10(r4)
	lbl_a2_2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void fbatEncountCheck(void) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	stw r0, 0xb4(r1)
	stfd f31, 0xa0(r1)
	psq_st f31, 0xa8(r1), 0, 0
	stfd f30, 0x90(r1)
	psq_st f30, 0x98(r1), 0, 0
	stfd f29, 0x80(r1)
	psq_st f29, 0x88(r1), 0, 0
	stfd f28, 0x70(r1)
	psq_st f28, 0x78(r1), 0, 0
	stmw r22, 0x48(r1)
	lwz r3, gp(r13)
	lis r4, vec3_802c2f78@ha
	addi r28, r4, vec3_802c2f78@l
	la r29, work(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r29, r29, 0x14
	lbl_a2_1:
	lwz r27, 0x4(r29)
	bl marioGetPtr
	li r0, 0x0
	mr r30, r3
	stw r0, 0x10(r29)
	bl marioStGetSystemLevel
	cmplwi r3, 0x0
	bne lbl_a2_2
	lwz r0, 0x8(r29)
	clrlwi. r0, r0, 31
	bne lbl_a2_3
	bl marioKeyOffChk
	cmpwi r3, 0x0
	bne lbl_a2_2
	bl marioCtrlOffChk
	cmpwi r3, 0x0
	beq lbl_a2_3
	b lbl_a2_2
	lbl_a2_3:
	bl N_itemPickUpFromFieldCheck
	cmpwi r3, 0x0
	bne lbl_a2_2
	lwz r4, gp(r13)
	li r3, 0x13f1
	lwz r24, 0x168(r4)
	addi r26, r24, 0x10
	mr r4, r26
	bl fbatHitCheck
	mr. r31, r3
	beq lbl_a2_4
	lha r0, 0x0(r24)
	cmpwi r0, 0x1
	bne lbl_a2_4
	lwz r3, gp(r13)
	lwz r4, 0x168(r3)
	lha r0, 0x0(r4)
	cmpwi r0, 0x1
	beq lbl_a2_5
	li r3, 0x0
	b lbl_a2_6
	lbl_a2_5:
	li r3, 0x5
	li r0, 0x0
	sth r3, 0x0(r4)
	li r3, 0x1
	stb r0, 0x2(r4)
	stw r31, 0x4(r4)
	stw r31, 0x8(r4)
	lbl_a2_6:
	cmpwi r3, 0x0
	beq lbl_a2_2
	lwz r3, 0x0(r26)
	lis r0, 0x10
	cmpw r3, r0
	beq lbl_a2_7
	bge lbl_a2_8
	lis r0, 0x4
	cmpw r3, r0
	beq lbl_a2_9
	bge lbl_a2_10
	lis r0, 0x2
	cmpw r3, r0
	beq lbl_a2_9
	bge lbl_a2_11
	lis r0, 0x1
	cmpw r3, r0
	beq lbl_a2_11
	b lbl_a2_11
	lbl_a2_10:
	lis r0, 0x8
	cmpw r3, r0
	beq lbl_a2_9
	b lbl_a2_11
	lbl_a2_8:
	lis r0, 0x80
	cmpw r3, r0
	beq lbl_a2_12
	bge lbl_a2_13
	lis r0, 0x40
	cmpw r3, r0
	beq lbl_a2_7
	bge lbl_a2_11
	lis r0, 0x20
	cmpw r3, r0
	beq lbl_a2_7
	b lbl_a2_11
	lbl_a2_13:
	lis r0, 0x100
	cmpw r3, r0
	beq lbl_a2_14
	b lbl_a2_11
	lbl_a2_9:
	bl marioChgMotJump2
	lwz r0, dbg_battleskip(r13)
	cmpwi r0, 0x1
	beq lbl_a2_11
	lwz r4, 0x28(r31)
	li r5, 0x1
	lwz r3, 0x104(r31)
	lwz r4, 0x20(r4)
	bl animPoseSetAnim
	b lbl_a2_11
	lbl_a2_7:
	lwz r0, dbg_battleskip(r13)
	cmpwi r0, 0x1
	beq lbl_a2_11
	lwz r4, 0x28(r31)
	li r5, 0x1
	lwz r3, 0x104(r31)
	lwz r4, 0x20(r4)
	bl animPoseSetAnim
	b lbl_a2_11
	lbl_a2_12:
	lwz r0, dbg_battleskip(r13)
	cmpwi r0, 0x1
	beq lbl_a2_11
	lwz r4, 0x28(r31)
	li r5, 0x1
	lwz r3, 0x104(r31)
	lwz r4, 0x20(r4)
	bl animPoseSetAnim
	b lbl_a2_11
	lbl_a2_14:
	lwz r0, dbg_battleskip(r13)
	cmpwi r0, 0x1
	beq lbl_a2_11
	lwz r4, 0x28(r31)
	li r5, 0x1
	lwz r3, 0x104(r31)
	lwz r4, 0x20(r4)
	bl animPoseSetAnim
	lbl_a2_11:
	lwz r3, 0x104(r31)
	bl animPoseGetAnimPosePtr
	lfs f0, 0x144(r31)
	mr r24, r3
	stfs f0, 0x148(r31)
	lfs f1, 0x8c(r31)
	lfs f2, 0x94(r31)
	lfs f3, 0x8c(r30)
	lfs f4, 0x94(r30)
	bl angleABf
	stfs f1, 0x144(r31)
	lfs f0, 0x144(r31)
	fneg f1, f0
	bl reviseAngle
	lfs f0, float_neg90_80419bd8(r2)
	li r3, 0x4
	fadds f28, f1, f0
	bl camGetPtr
	lfs f3, 0x18(r3)
	lfs f2, 0xc(r3)
	lfs f1, 0x20(r3)
	lfs f0, 0x14(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fneg f1, f2
	fneg f2, f0
	bl atan2
	frsp f1, f1
	lfs f0, float_rad2deg_80419bdc(r2)
	fmuls f1, f0, f1
	bl reviseAngle
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_15
	lfs f0, float_360_80419be0(r2)
	fadds f1, f1, f0
	lbl_a2_15:
	fsubs f1, f1, f28
	bl reviseAngle
	lfs f0, float_90_80419bd0(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_16
	lfs f0, float_270_80419be4(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	beq lbl_a2_17
	lbl_a2_16:
	lfs f0, float_neg90_80419bd8(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_18
	lfs f0, float_neg270_80419be8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne lbl_a2_18
	lbl_a2_17:
	li r3, 0x4
	bl camGetPtr
	lfs f3, 0x18(r3)
	lfs f2, 0xc(r3)
	lfs f1, 0x20(r3)
	lfs f0, 0x14(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fneg f1, f2
	fneg f2, f0
	bl atan2
	frsp f1, f1
	lfs f0, float_rad2deg_80419bdc(r2)
	fmuls f1, f0, f1
	bl reviseAngle
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_19
	lfs f0, float_360_80419be0(r2)
	fadds f1, f1, f0
	lbl_a2_19:
	lfs f0, float_180_80419bec(r2)
	fadds f1, f0, f1
	bl reviseAngle
	stfs f1, 0x7c(r24)
	b lbl_a2_20
	lbl_a2_18:
	li r3, 0x4
	bl camGetPtr
	lfs f3, 0x18(r3)
	lfs f2, 0xc(r3)
	lfs f1, 0x20(r3)
	lfs f0, 0x14(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fneg f1, f2
	fneg f2, f0
	bl atan2
	frsp f1, f1
	lfs f0, float_rad2deg_80419bdc(r2)
	fmuls f1, f0, f1
	bl reviseAngle
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_21
	lfs f0, float_360_80419be0(r2)
	fadds f1, f1, f0
	lbl_a2_21:
	stfs f1, 0x7c(r24)
	lbl_a2_20:
	lfs f3, float_360_80419be0(r2)
	lfs f0, float_180_80419bec(r2)
	b lbl_a2_22
	lbl_a2_23:
	lfs f1, 0x74(r24)
	fadds f1, f1, f3
	stfs f1, 0x74(r24)
	lbl_a2_22:
	lfs f2, 0x7c(r24)
	lfs f1, 0x74(r24)
	fsubs f1, f2, f1
	fcmpo cr0, f1, f0
	bgt lbl_a2_23
	lfs f3, float_360_80419be0(r2)
	lfs f0, float_neg180_80419bf0(r2)
	b lbl_a2_24
	lbl_a2_25:
	lfs f1, 0x74(r24)
	fsubs f1, f1, f3
	stfs f1, 0x74(r24)
	lbl_a2_24:
	lfs f2, 0x7c(r24)
	lfs f1, 0x74(r24)
	fsubs f2, f2, f1
	fcmpo cr0, f2, f0
	blt lbl_a2_25
	lfs f0, float_0p75_80419bf4(r2)
	lis r0, 0x20
	fmadds f0, f0, f2, f1
	stfs f0, 0x74(r24)
	lwz r3, 0x0(r26)
	cmpw r3, r0
	beq lbl_a2_26
	bge lbl_a2_27
	lis r0, 0x8
	cmpw r3, r0
	beq lbl_a2_26
	bge lbl_a2_28
	lis r0, 0x4
	cmpw r3, r0
	beq lbl_a2_26
	bge lbl_a2_29
	lis r0, 0x2
	cmpw r3, r0
	beq lbl_a2_26
	b lbl_a2_29
	lbl_a2_28:
	lis r0, 0x10
	cmpw r3, r0
	beq lbl_a2_26
	b lbl_a2_29
	lbl_a2_27:
	lis r0, 0x100
	cmpw r3, r0
	beq lbl_a2_26
	bge lbl_a2_30
	lis r0, 0x80
	cmpw r3, r0
	beq lbl_a2_26
	bge lbl_a2_29
	lis r0, 0x40
	cmpw r3, r0
	beq lbl_a2_26
	b lbl_a2_29
	lbl_a2_30:
	lis r0, 0x1000
	cmpw r3, r0
	beq lbl_a2_31
	b lbl_a2_29
	lbl_a2_26:
	lfs f4, float_0_80419b9c(r2)
	li r3, 0x3
	lfs f2, 0x90(r31)
	li r4, 0x3
	lfs f0, 0x150(r31)
	fmr f6, f4
	lfs f1, 0x8c(r31)
	fadds f2, f2, f0
	lfs f3, 0x94(r31)
	lfs f5, float_neg1_80419bf8(r2)
	bl effSmallStarEntry
	b lbl_a2_29
	lbl_a2_31:
	lfs f4, float_0_80419b9c(r2)
	li r3, 0x3
	lfs f2, 0x90(r30)
	li r4, 0x3
	lfs f0, 0x1b8(r30)
	fmr f6, f4
	lfs f1, 0x8c(r30)
	fadds f2, f2, f0
	lfs f3, 0x94(r30)
	lfs f5, float_neg1_80419bf8(r2)
	bl effSmallStarEntry
	lbl_a2_29:
	lwz r3, 0x0(r26)
	lis r0, 0x20
	cmpw r3, r0
	beq lbl_a2_32
	bge lbl_a2_33
	lis r0, 0x8
	cmpw r3, r0
	beq lbl_a2_32
	bge lbl_a2_34
	lis r0, 0x4
	cmpw r3, r0
	beq lbl_a2_32
	bge lbl_a2_2
	lis r0, 0x2
	cmpw r3, r0
	beq lbl_a2_32
	b lbl_a2_2
	lbl_a2_34:
	lis r0, 0x10
	cmpw r3, r0
	beq lbl_a2_32
	b lbl_a2_2
	lbl_a2_33:
	lis r0, 0x100
	cmpw r3, r0
	beq lbl_a2_32
	bge lbl_a2_35
	lis r0, 0x80
	cmpw r3, r0
	beq lbl_a2_32
	bge lbl_a2_2
	lis r0, 0x40
	cmpw r3, r0
	beq lbl_a2_32
	b lbl_a2_2
	lbl_a2_35:
	lis r0, 0x1000
	cmpw r3, r0
	beq lbl_a2_36
	b lbl_a2_2
	lbl_a2_32:
	cmplwi r31, 0x0
	beq lbl_a2_2
	addi r3, r28, 0x204
	addi r4, r31, 0x8c
	bl psndSFXOn_3D
	b lbl_a2_2
	lbl_a2_36:
	addi r3, r28, 0x220
	addi r4, r30, 0x8c
	bl psndSFXOn_3D
	b lbl_a2_2
	lbl_a2_4:
	lfs f30, float_1000_80419bc8(r2)
	bl marioChkTalkable
	cmpwi r3, 0x0
	beq lbl_a2_37
	lbz r0, 0x39(r30)
	extsb. r0, r0
	bne lbl_a2_37
	lwz r31, 0xc(r29)
	li r25, 0x0
	li r26, 0x0
	b lbl_a2_38
	lbl_a2_39:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_40
	rlwinm. r0, r3, 0, 28, 28
	bne lbl_a2_40
	lwz r0, 0x128(r31)
	cmplwi r0, 0x0
	beq lbl_a2_40
	lfs f2, 0x90(r30)
	li r24, 0x0
	lfs f0, 0x1b8(r30)
	lfs f1, 0x90(r31)
	fadds f0, f2, f0
	fcmpo cr0, f1, f0
	bgt lbl_a2_41
	lfs f0, 0x150(r31)
	fadds f0, f1, f0
	fcmpo cr0, f2, f0
	bgt lbl_a2_41
	lfs f0, 0x8c(r30)
	addi r3, r1, 0x30
	addi r4, r31, 0x8c
	stfs f0, 0x30(r1)
	lfs f0, 0x94(r30)
	stfs f0, 0x38(r1)
	stfs f1, 0x34(r1)
	bl PSVECDistance
	lfs f2, 0x1b4(r30)
	lfs f0, 0x14c(r31)
	lfs f3, float_0p5_80419ba0(r2)
	fadds f2, f2, f0
	lfs f0, float_10_80419bb8(r2)
	fmadds f0, f3, f2, f0
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne lbl_a2_42
	fcmpo cr0, f1, f30
	bge lbl_a2_42
	mr r25, r31
	lbl_a2_42:
	li r23, 0x0
	li r3, 0x4
	bl camGetPtr
	lfs f28, 0x114(r3)
	bl marioGetDispDir
	fsubs f1, f1, f28
	bl reviseAngle
	fmr f31, f1
	lfs f29, float_180_80419bec(r2)
	li r22, 0x0
	lbl_a2_43:
	cmpwi r22, 0x1
	beq lbl_a2_44
	bge lbl_a2_45
	cmpwi r22, 0x0
	bge lbl_a2_46
	b lbl_a2_45
	lbl_a2_46:
	li r3, 0x4
	bl camGetPtr
	lfs f28, 0x114(r3)
	lfs f1, 0x8c(r30)
	lfs f2, 0x94(r30)
	lfs f3, 0x8c(r31)
	lfs f4, 0x94(r31)
	bl angleABf
	fsubs f1, f1, f28
	bl reviseAngle
	b lbl_a2_47
	lbl_a2_44:
	li r3, 0x4
	bl camGetPtr
	lfs f2, float_0p5_80419ba0(r2)
	lfs f1, 0x14c(r31)
	lfs f0, 0x8c(r31)
	lfs f28, 0x114(r3)
	fmadds f3, f2, f1, f0
	lfs f1, 0x8c(r30)
	lfs f2, 0x94(r30)
	lfs f4, 0x94(r31)
	bl angleABf
	fsubs f1, f1, f28
	bl reviseAngle
	b lbl_a2_47
	lbl_a2_45:
	li r3, 0x4
	bl camGetPtr
	lfs f2, float_0p5_80419ba0(r2)
	lfs f1, 0x14c(r31)
	lfs f0, 0x8c(r31)
	lfs f28, 0x114(r3)
	fnmsubs f3, f2, f1, f0
	lfs f1, 0x8c(r30)
	lfs f2, 0x94(r30)
	lfs f4, 0x94(r31)
	bl angleABf
	fsubs f1, f1, f28
	bl reviseAngle
	lbl_a2_47:
	fcmpo cr0, f1, f29
	bge lbl_a2_48
	fcmpo cr0, f31, f29
	bgt lbl_a2_49
	li r23, 0x1
	b lbl_a2_50
	lbl_a2_48:
	fcmpo cr0, f31, f29
	blt lbl_a2_49
	li r23, 0x1
	b lbl_a2_50
	lbl_a2_49:
	addi r22, r22, 0x1
	cmpwi r22, 0x3
	blt lbl_a2_43
	lbl_a2_50:
	cmpwi r23, 0x0
	beq lbl_a2_41
	lfs f0, 0x8c(r30)
	addi r3, r1, 0x30
	addi r4, r31, 0x8c
	stfs f0, 0x30(r1)
	lfs f0, 0x94(r30)
	stfs f0, 0x38(r1)
	lfs f0, 0x90(r31)
	stfs f0, 0x34(r1)
	bl PSVECDistance
	lfs f2, 0x1b4(r30)
	fmr f31, f1
	lfs f0, 0x14c(r31)
	lfs f3, float_0p5_80419ba0(r2)
	fadds f2, f2, f0
	lfs f0, float_10_80419bb8(r2)
	fmadds f0, f3, f2, f0
	fcmpo cr0, f31, f0
	bgt lbl_a2_41
	lfs f3, 0x8c(r31)
	lfs f1, 0x8c(r30)
	lfs f2, 0x94(r31)
	lfs f0, 0x94(r30)
	fsubs f28, f3, f1
	lfs f1, float_0_80419b9c(r2)
	fsubs f29, f2, f0
	fmr f2, f1
	fmr f3, f28
	fmr f4, f29
	bl angleABf
	addi r3, r1, 0x2c
	addi r4, r1, 0x28
	bl sincosf
	fmuls f1, f29, f29
	lfs f0, float_0_80419b9c(r2)
	fmadds f4, f28, f28, f1
	fcmpo cr0, f4, f0
	ble lbl_a2_51
	frsqrte f1, f4
	lfd f3, 0x1c0(r28)
	lfd f2, 0x1c8(r28)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f0, f1, f0
	fmul f4, f4, f0
	frsp f4, f4
	b lbl_a2_52
	lbl_a2_51:
	lfd f0, 0x1d0(r28)
	fcmpo cr0, f4, f0
	bge lbl_a2_53
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	b lbl_a2_52
	lbl_a2_53:
	stfs f4, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_54
	bge lbl_a2_55
	cmpwi r3, 0x0
	beq lbl_a2_56
	b lbl_a2_55
	lbl_a2_54:
	clrlwi. r0, r4, 9
	beq lbl_a2_57
	li r0, 0x1
	b lbl_a2_58
	lbl_a2_57:
	li r0, 0x2
	b lbl_a2_58
	lbl_a2_56:
	clrlwi. r0, r4, 9
	beq lbl_a2_59
	li r0, 0x5
	b lbl_a2_58
	lbl_a2_59:
	li r0, 0x3
	b lbl_a2_58
	lbl_a2_55:
	li r0, 0x4
	lbl_a2_58:
	cmpwi r0, 0x1
	bne lbl_a2_52
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	lbl_a2_52:
	stfs f4, 0x24(r1)
	addi r4, r1, 0x20
	lfs f3, float_0p75_80419bf4(r2)
	addi r5, r1, 0x1c
	lfs f2, 0x1b8(r30)
	addi r6, r1, 0x18
	lfs f0, 0x90(r30)
	addi r7, r1, 0x24
	lfs f1, 0x8c(r30)
	addi r8, r1, 0x14
	fmadds f2, f3, f2, f0
	lfs f3, 0x94(r30)
	lfs f4, 0x2c(r1)
	addi r9, r1, 0x10
	lfs f5, float_0_80419b9c(r2)
	addi r10, r1, 0xc
	lfs f6, 0x28(r1)
	li r3, 0x0
	bl hitCheckFilter
	cmplwi r3, 0x0
	bne lbl_a2_41
	fcmpo cr0, f31, f30
	li r24, 0x1
	bge lbl_a2_41
	fmr f30, f31
	stw r31, 0x10(r29)
	lbl_a2_41:
	cmpwi r24, 0x0
	beq lbl_a2_60
	lwz r0, 0x1d4(r31)
	rlwinm. r0, r0, 0, 2, 2
	bne lbl_a2_40
	bl marioGetPtr
	lwz r0, 0x1d4(r31)
	mr r24, r3
	oris r0, r0, 0x2000
	stw r0, 0x1d4(r31)
	lfs f0, 0x144(r31)
	stfs f0, 0x148(r31)
	lwz r3, 0x11c(r31)
	bl evtStopID
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 7, 7
	bne lbl_a2_40
	lfs f1, 0x8c(r31)
	lfs f2, 0x94(r31)
	lfs f3, 0x8c(r24)
	lfs f4, 0x94(r24)
	bl angleABf
	bl reviseAngle
	stfs f1, 0x144(r31)
	b lbl_a2_40
	lbl_a2_60:
	lwz r3, 0x1d4(r31)
	rlwinm. r0, r3, 0, 2, 2
	beq lbl_a2_40
	rlwinm r0, r3, 0, 3, 1
	stw r0, 0x1d4(r31)
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 9, 9
	beq lbl_a2_61
	lfs f0, 0x148(r31)
	stfs f0, 0x144(r31)
	lwz r3, 0x11c(r31)
	bl evtStartID
	b lbl_a2_40
	lbl_a2_61:
	lwz r0, 0x140(r31)
	oris r0, r0, 0x1000
	stw r0, 0x140(r31)
	lbl_a2_40:
	addi r26, r26, 0x1
	addi r31, r31, 0x340
	lbl_a2_38:
	cmpw r26, r27
	blt lbl_a2_39
	stw r25, 0x1d4(r30)
	lwz r0, 0x10(r29)
	cmplwi r0, 0x0
	beq lbl_a2_37
	li r3, 0x0
	bl keyGetButtonTrg
	rlwinm. r0, r3, 0, 23, 23
	beq lbl_a2_37
	lwz r3, gp(r13)
	lwz r4, 0x10(r29)
	lwz r5, 0x168(r3)
	lha r0, 0x0(r5)
	cmpwi r0, 0x1
	bne lbl_a2_2
	li r3, 0x2
	li r0, 0x0
	sth r3, 0x0(r5)
	stb r0, 0x2(r5)
	stw r4, 0x4(r5)
	stw r0, 0x318(r4)
	b lbl_a2_2
	lbl_a2_37:
	lwz r3, gp(r13)
	lwz r25, 0x168(r3)
	lha r0, 0x0(r25)
	cmpwi r0, 0x1
	bne lbl_a2_62
	addi r22, r25, 0x10
	li r3, 0x2361
	mr r4, r22
	bl fbatHitCheck
	mr. r24, r3
	beq lbl_a2_62
	lha r0, 0x0(r25)
	cmpwi r0, 0x1
	bne lbl_a2_62
	lwz r3, gp(r13)
	lwz r4, 0x0(r22)
	lwz r5, 0x168(r3)
	lha r0, 0x0(r5)
	cmpwi r0, 0x1
	bne lbl_a2_63
	li r3, 0x3
	li r0, 0x0
	sth r3, 0x0(r5)
	stb r0, 0x2(r5)
	stw r24, 0x4(r5)
	stw r4, 0x318(r24)
	lbl_a2_63:
	lwz r3, 0x0(r22)
	lis r0, 0x4
	cmpw r3, r0
	beq lbl_a2_64
	bge lbl_a2_65
	lis r0, 0x2
	cmpw r3, r0
	beq lbl_a2_64
	b lbl_a2_66
	lbl_a2_65:
	lis r0, 0x8
	cmpw r3, r0
	beq lbl_a2_64
	b lbl_a2_66
	lbl_a2_64:
	bl marioChgMotJump2
	lbl_a2_66:
	lfs f4, float_0_80419b9c(r2)
	li r3, 0x3
	lfs f2, 0x90(r24)
	li r4, 0x3
	lfs f0, 0x150(r24)
	fmr f6, f4
	lfs f1, 0x8c(r24)
	fadds f2, f2, f0
	lfs f3, 0x94(r24)
	lfs f5, float_neg1_80419bf8(r2)
	bl effSmallStarEntry
	b lbl_a2_2
	lbl_a2_62:
	bl npcKoopaModeEncountCheck
	lbl_a2_2:
	psq_l f31, 0xa8(r1), 0, 0
	lfd f31, 0xa0(r1)
	psq_l f30, 0x98(r1), 0, 0
	lfd f30, 0x90(r1)
	psq_l f29, 0x88(r1), 0, 0
	lfd f29, 0x80(r1)
	psq_l f28, 0x78(r1), 0, 0
	lfd f28, 0x70(r1)
	lmw r22, 0x48(r1)
	lwz r0, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stfd f29, 0x40(r1)
	psq_st f29, 0x48(r1), 0, 0
	stfd f28, 0x30(r1)
	psq_st f28, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	stw r30, 0x28(r1)
	mr r30, r4
	lwz r3, 0x18(r4)
	bl msgSearch
	lfs f31, 0x10(r30)
	mr r31, r3
	lfs f30, 0x14(r30)
	bl FontGetMessageWidth
	clrlwi r4, r3, 16
	lis r0, 0x4330
	lis r3, double_to_int_mask_802c31b8@ha
	stw r4, 0x14(r1)
	addi r4, r3, double_to_int_mask_802c31b8@l
	li r3, 0x2710
	stw r0, 0x10(r1)
	lfd f1, 0x0(r4)
	lfd f0, 0x10(r1)
	fsubs f28, f0, f1
	bl irand
	lis r4, 0x6666
	lis r0, 0x4330
	addi r5, r4, 0x6667
	stw r0, 0x18(r1)
	mulhw r5, r5, r3
	lis r4, double_to_int_802c3150@ha
	lfd f1, double_to_int_802c3150@l(r4)
	srawi r0, r5, 1
	srwi r4, r0, 31
	add r0, r0, r4
	mulli r0, r0, 0x5
	subf r0, r0, r3
	li r3, 0x2710
	xoris r0, r0, 0x8000
	stw r0, 0x1c(r1)
	lfd f0, 0x18(r1)
	fsubs f0, f0, f1
	fadds f29, f31, f0
	bl irand
	lis r5, 0x6666
	lis r4, 0x4330
	addi r0, r5, 0x6667
	lfs f2, float_10_80419bb8(r2)
	mulhw r0, r0, r3
	lfs f0, float_20_80419c00(r2)
	lis r5, double_to_int_802c3150@ha
	lfs f1, float_0p5_80419ba0(r2)
	fsubs f2, f29, f2
	stw r4, 0x20(r1)
	srawi r6, r0, 1
	fmuls f29, f28, f1
	srwi r7, r6, 31
	lwz r0, 0x1c(r30)
	add r6, r6, r7
	fadds f0, f0, f28
	mulli r4, r6, 0x5
	fsubs f1, f2, f29
	lfs f2, float_0p1_80419bfc(r2)
	lfd f5, double_to_int_802c3150@l(r5)
	subf r3, r4, r3
	fmuls f3, f0, f2
	xoris r3, r3, 0x8000
	stw r3, 0x24(r1)
	fmuls f1, f2, f1
	lfs f4, float_3p2_80419c04(r2)
	addi r4, r1, 0xc
	lfd f0, 0x20(r1)
	li r3, 0x0
	stw r0, 0xc(r1)
	fsubs f0, f0, f5
	lfs f5, float_1_80419bb4(r2)
	fadds f0, f30, f0
	fmuls f2, f0, f2
	bl windowDispGX_Waku_col
	bl FontDrawStart
	bl FontDrawEdge
	lwz r0, dat_80419b98(r2)
	addi r3, r1, 0x8
	stw r0, 0x8(r1)
	bl FontDrawColor
	lfs f1, float_0p1_80419bfc(r2)
	bl FontDrawScale
	lfs f0, float_3_80419c08(r2)
	fsubs f1, f31, f29
	lfs f2, float_0p1_80419bfc(r2)
	mr r3, r31
	fsubs f0, f30, f0
	fmuls f1, f2, f1
	fmuls f2, f0, f2
	bl FontDrawStringShake
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	psq_l f29, 0x48(r1), 0, 0
	lfd f29, 0x40(r1)
	psq_l f28, 0x38(r1), 0, 0
	lfd f28, 0x30(r1)
	lwz r31, 0x2c(r1)
	lwz r0, 0x74(r1)
	lwz r30, 0x28(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void fbatSetAttackAnnounceEnable(void) {
	nofralloc
	lwz r3, gp(r13)
	li r0, 0x1
	lwz r3, 0x168(r3)
	stw r0, 0x550(r3)
	blr
}

asm void fbatSetAttackAnnounce(s32 a1) {
	nofralloc
	lwz r5, gp(r13)
	li r4, 0x0
	lis r0, 0x20
	lwz r5, 0x168(r5)
	stw r4, 0x550(r5)
	stw r3, 0x554(r5)
	stw r4, 0x55c(r5)
	lwz r3, 0x554(r5)
	cmpw r3, r0
	beq lbl_a2_1
	bge lbl_a2_2
	lis r0, 0x8
	cmpw r3, r0
	beq lbl_a2_1
	bge lbl_a2_3
	lis r0, 0x4
	cmpw r3, r0
	beq lbl_a2_1
	bge lbl_a2_4
	lis r0, 0x2
	cmpw r3, r0
	beq lbl_a2_1
	b lbl_a2_4
	lbl_a2_3:
	lis r0, 0x10
	cmpw r3, r0
	beq lbl_a2_1
	b lbl_a2_4
	lbl_a2_2:
	lis r0, 0x100
	cmpw r3, r0
	beq lbl_a2_1
	bge lbl_a2_5
	lis r0, 0x80
	cmpw r3, r0
	beq lbl_a2_1
	bge lbl_a2_4
	lis r0, 0x40
	cmpw r3, r0
	beq lbl_a2_1
	b lbl_a2_4
	lbl_a2_5:
	lis r0, 0x1000
	cmpw r3, r0
	beq lbl_a2_6
	b lbl_a2_4
	lbl_a2_1:
	lis r3, str_802C3158@ha
	li r0, 0x2
	addi r3, r3, str_802C3158@l
	stw r3, 0x568(r5)
	stw r0, 0x558(r5)
	lwz r0, dat_80419b90(r2)
	stw r0, 0x56c(r5)
	blr
	lbl_a2_6:
	lis r3, str_802C3168@ha
	li r0, 0x1
	addi r3, r3, str_802C3168@l
	stw r3, 0x568(r5)
	stw r0, 0x558(r5)
	lwz r0, dat_80419b94(r2)
	stw r0, 0x56c(r5)
	blr
	lbl_a2_4:
	li r0, 0x0
	stw r0, 0x558(r5)
	blr
}

asm void fbatChangeMode(s16 mode) {
	nofralloc
	lwz r4, gp(r13)
	lwz r4, 0x168(r4)
	sth r3, 0x0(r4)
	blr
}

asm FieldBattleData* fbatGetPointer(void) {
	nofralloc
	lwz r3, gp(r13)
	lwz r3, 0x168(r3)
	blr
}

asm NpcEntry* npcNearDistCheck(f32 x, f32 y, f32 z, f32 range) {
	nofralloc
	stwu r1, -0x10(r1)
	lis r4, vec3_802c2f78@ha
	addi r5, r4, vec3_802c2f78@l
	lwz r3, gp(r13)
	la r4, work(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r4, r4, 0x14
	lbl_a2_1:
	lwz r0, 0x4(r4)
	li r3, 0x0
	lwz r7, 0xc(r4)
	mtctr r0
	cmpwi r0, 0x0
	ble lbl_a2_2
	lbl_a2_3:
	lwz r0, 0x0(r7)
	clrlwi. r0, r0, 31
	beq lbl_a2_4
	lfs f5, 0x8c(r7)
	lfs f0, 0x94(r7)
	fsubs f6, f1, f5
	lfs f5, 0x90(r7)
	fsubs f7, f3, f0
	lfs f0, float_0_80419b9c(r2)
	fsubs f11, f2, f5
	fmuls f9, f6, f6
	fmuls f10, f7, f7
	fadds f8, f9, f10
	fcmpo cr0, f8, f0
	ble lbl_a2_5
	frsqrte f5, f8
	lfd f7, 0x1c0(r5)
	lfd f6, 0x1c8(r5)
	fmul f0, f5, f5
	fmul f5, f7, f5
	fnmsub f0, f8, f0, f6
	fmul f5, f5, f0
	fmul f0, f5, f5
	fmul f5, f7, f5
	fnmsub f0, f8, f0, f6
	fmul f5, f5, f0
	fmul f0, f5, f5
	fmul f5, f7, f5
	fnmsub f0, f8, f0, f6
	fmul f0, f5, f0
	fmul f8, f8, f0
	frsp f8, f8
	b lbl_a2_6
	lbl_a2_5:
	lfd f0, 0x1d0(r5)
	fcmpo cr0, f8, f0
	bge lbl_a2_7
	lis r4, __float_nan@ha
	lfs f8, __float_nan@l(r4)
	b lbl_a2_6
	lbl_a2_7:
	stfs f8, 0x8(r1)
	lis r0, 0x7f80
	lwz r6, 0x8(r1)
	rlwinm r4, r6, 0, 1, 8
	cmpw r4, r0
	beq lbl_a2_8
	bge lbl_a2_9
	cmpwi r4, 0x0
	beq lbl_a2_10
	b lbl_a2_9
	lbl_a2_8:
	clrlwi. r0, r6, 9
	beq lbl_a2_11
	li r0, 0x1
	b lbl_a2_12
	lbl_a2_11:
	li r0, 0x2
	b lbl_a2_12
	lbl_a2_10:
	clrlwi. r0, r6, 9
	beq lbl_a2_13
	li r0, 0x5
	b lbl_a2_12
	lbl_a2_13:
	li r0, 0x3
	b lbl_a2_12
	lbl_a2_9:
	li r0, 0x4
	lbl_a2_12:
	cmpwi r0, 0x1
	bne lbl_a2_6
	lis r4, __float_nan@ha
	lfs f8, __float_nan@l(r4)
	lbl_a2_6:
	fmadds f5, f11, f11, f9
	lfs f0, float_0_80419b9c(r2)
	fadds f5, f10, f5
	fcmpo cr0, f5, f0
	fcmpo cr0, f8, f4
	bge lbl_a2_4
	mr r3, r7
	lbl_a2_4:
	addi r7, r7, 0x340
	bdnz lbl_a2_3
	lbl_a2_2:
	addi r1, r1, 0x10
	blr
}

asm HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz) {
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
	stmw r26, 0x58(r1)
	mr r26, r3
	lis r3, vec3_802c2f78@ha
	lfs f3, 0x8c(r26)
	mr r27, r4
	fmr f29, f1
	lfs f0, float_0_80419b9c(r2)
	stfs f3, 0x0(r4)
	mr r28, r5
	fmr f30, f2
	mr r29, r6
	lfs f1, 0x94(r26)
	fcmpu cr0, f0, f29
	addi r31, r3, vec3_802c2f78@l
	stfs f1, 0x0(r5)
	bne lbl_a2_1
	fcmpu cr0, f0, f30
	bne lbl_a2_1
	li r3, 0x0
	b lbl_a2_2
	lbl_a2_1:
	lfs f1, float_0_80419b9c(r2)
	fmr f3, f29
	fmr f4, f30
	fmr f2, f1
	bl angleABf
	addi r3, r1, 0x1c
	addi r4, r1, 0x18
	bl sincosf
	fmuls f1, f30, f30
	lfs f0, float_0_80419b9c(r2)
	fmadds f31, f29, f29, f1
	fcmpo cr0, f31, f0
	ble lbl_a2_3
	frsqrte f1, f31
	lfd f3, 0x1c0(r31)
	lfd f2, 0x1c8(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f0, f1, f0
	fmul f3, f31, f0
	frsp f3, f3
	b lbl_a2_4
	lbl_a2_3:
	lfd f0, 0x1d0(r31)
	fcmpo cr0, f31, f0
	bge lbl_a2_5
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b lbl_a2_4
	lbl_a2_5:
	stfs f31, 0x14(r1)
	lis r0, 0x7f80
	lwz r4, 0x14(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_6
	bge lbl_a2_7
	cmpwi r3, 0x0
	beq lbl_a2_8
	b lbl_a2_7
	lbl_a2_6:
	clrlwi. r0, r4, 9
	beq lbl_a2_9
	li r0, 0x1
	b lbl_a2_10
	lbl_a2_9:
	li r0, 0x2
	b lbl_a2_10
	lbl_a2_8:
	clrlwi. r0, r4, 9
	beq lbl_a2_11
	li r0, 0x5
	b lbl_a2_10
	lbl_a2_11:
	li r0, 0x3
	b lbl_a2_10
	lbl_a2_7:
	li r0, 0x4
	lbl_a2_10:
	cmpwi r0, 0x1
	bne lbl_a2_12
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b lbl_a2_4
	lbl_a2_12:
	fmr f3, f31
	lbl_a2_4:
	lfs f1, float_0p75_80419bf4(r2)
	lfs f0, 0x14c(r26)
	lfs f2, float_0p2_80419c14(r2)
	fmadds f1, f1, f0, f3
	lfs f0, float_10_80419bb8(r2)
	stfs f1, 0x2c(r1)
	lfs f1, 0x150(r26)
	fmuls f2, f2, f1
	fcmpo cr0, f2, f0
	ble lbl_a2_13
	fmr f2, f0
	lbl_a2_13:
	lwz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 18, 18
	beq lbl_a2_14
	lfs f0, 0x90(r26)
	addi r4, r1, 0x38
	lfs f1, 0x8c(r26)
	addi r5, r1, 0x34
	fadds f2, f0, f2
	lfs f3, 0x94(r26)
	lfs f4, 0x1c(r1)
	addi r6, r1, 0x30
	lfs f5, float_0_80419b9c(r2)
	addi r7, r1, 0x2c
	lfs f6, 0x18(r1)
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x4
	bl hitCheckAttr
	b lbl_a2_15
	lbl_a2_14:
	lfs f0, 0x90(r26)
	addi r4, r1, 0x38
	lfs f1, 0x8c(r26)
	addi r5, r1, 0x34
	fadds f2, f0, f2
	lfs f3, 0x94(r26)
	lfs f4, 0x1c(r1)
	addi r6, r1, 0x30
	lfs f5, float_0_80419b9c(r2)
	addi r7, r1, 0x2c
	lfs f6, 0x18(r1)
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	lbl_a2_15:
	cmplwi r3, 0x0
	mr r30, r3
	beq lbl_a2_16
	lfs f4, 0x20(r1)
	lfs f1, 0x28(r1)
	fmuls f0, f30, f4
	lfs f2, float_0p5_80419ba0(r2)
	lfs f3, 0x0(r27)
	fmadds f0, f29, f1, f0
	fnmsubs f1, f0, f1, f29
	fnmsubs f0, f0, f4, f30
	fmuls f1, f2, f1
	fmuls f0, f2, f0
	fadds f1, f3, f1
	stfs f1, 0x0(r27)
	lfs f1, 0x0(r28)
	fadds f0, f1, f0
	stfs f0, 0x0(r28)
	lwz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 15, 15
	beq lbl_a2_17
	lfs f1, float_180_80419bec(r2)
	lfs f0, 0x0(r29)
	fadds f1, f1, f0
	bl reviseAngle
	fmr f30, f1
	lfs f1, float_0_80419b9c(r2)
	lfs f4, float_100_80419c18(r2)
	lfs f3, 0x28(r1)
	fmr f2, f1
	lfs f0, 0x20(r1)
	fmuls f3, f4, f3
	fmuls f4, f4, f0
	bl angleABf
	bl reviseAngle
	fmr f29, f1
	fsubs f1, f29, f30
	bl reviseAngle
	fadds f1, f29, f1
	bl reviseAngle
	fctiwz f0, f1
	lis r0, 0x4330
	stw r0, 0x48(r1)
	lfd f1, 0x1d8(r31)
	stfd f0, 0x40(r1)
	lwz r0, 0x44(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x4c(r1)
	lfd f0, 0x48(r1)
	fsubs f0, f0, f1
	stfs f0, 0x0(r29)
	lbl_a2_17:
	mr r3, r30
	b lbl_a2_2
	lbl_a2_16:
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f31, f0
	ble lbl_a2_18
	frsqrte f1, f31
	lfd f3, 0x1c0(r31)
	lfd f2, 0x1c8(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f0, f1, f0
	fmul f3, f31, f0
	frsp f3, f3
	b lbl_a2_19
	lbl_a2_18:
	lfd f0, 0x1d0(r31)
	fcmpo cr0, f31, f0
	bge lbl_a2_20
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b lbl_a2_19
	lbl_a2_20:
	stfs f31, 0x10(r1)
	lis r0, 0x7f80
	lwz r4, 0x10(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_21
	bge lbl_a2_22
	cmpwi r3, 0x0
	beq lbl_a2_23
	b lbl_a2_22
	lbl_a2_21:
	clrlwi. r0, r4, 9
	beq lbl_a2_24
	li r0, 0x1
	b lbl_a2_25
	lbl_a2_24:
	li r0, 0x2
	b lbl_a2_25
	lbl_a2_23:
	clrlwi. r0, r4, 9
	beq lbl_a2_26
	li r0, 0x5
	b lbl_a2_25
	lbl_a2_26:
	li r0, 0x3
	b lbl_a2_25
	lbl_a2_22:
	li r0, 0x4
	lbl_a2_25:
	cmpwi r0, 0x1
	bne lbl_a2_27
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b lbl_a2_19
	lbl_a2_27:
	fmr f3, f31
	lbl_a2_19:
	lfs f2, float_0p75_80419bf4(r2)
	lfs f0, 0x14c(r26)
	lfs f1, float_0p4_80419c1c(r2)
	fmadds f0, f2, f0, f3
	stfs f0, 0x2c(r1)
	lwz r0, 0x0(r26)
	lfs f0, 0x150(r26)
	rlwinm. r0, r0, 0, 18, 18
	fmuls f2, f1, f0
	beq lbl_a2_28
	lfs f0, 0x90(r26)
	addi r4, r1, 0x38
	lfs f1, 0x8c(r26)
	addi r5, r1, 0x34
	fadds f2, f0, f2
	lfs f3, 0x94(r26)
	lfs f4, 0x1c(r1)
	addi r6, r1, 0x30
	lfs f5, float_0_80419b9c(r2)
	addi r7, r1, 0x2c
	lfs f6, 0x18(r1)
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x4
	bl hitCheckAttr
	b lbl_a2_29
	lbl_a2_28:
	lfs f0, 0x90(r26)
	addi r4, r1, 0x38
	lfs f1, 0x8c(r26)
	addi r5, r1, 0x34
	fadds f2, f0, f2
	lfs f3, 0x94(r26)
	lfs f4, 0x1c(r1)
	addi r6, r1, 0x30
	lfs f5, float_0_80419b9c(r2)
	addi r7, r1, 0x2c
	lfs f6, 0x18(r1)
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	lbl_a2_29:
	cmplwi r3, 0x0
	mr r30, r3
	beq lbl_a2_30
	lfs f0, 0x28(r1)
	lfs f1, 0x20(r1)
	fmuls f2, f0, f0
	lfs f0, float_0_80419b9c(r2)
	fmuls f1, f1, f1
	fadds f3, f2, f1
	fcmpo cr0, f3, f0
	ble lbl_a2_31
	frsqrte f1, f3
	lfd f4, 0x1c0(r31)
	lfd f2, 0x1c8(r31)
	fmul f0, f1, f1
	fmul f1, f4, f1
	fnmsub f0, f3, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f4, f1
	fnmsub f0, f3, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f4, f1
	fnmsub f0, f3, f0, f2
	fmul f0, f1, f0
	fmul f3, f3, f0
	frsp f3, f3
	b lbl_a2_32
	lbl_a2_31:
	lfd f0, 0x1d0(r31)
	fcmpo cr0, f3, f0
	bge lbl_a2_33
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	b lbl_a2_32
	lbl_a2_33:
	stfs f3, 0xc(r1)
	lis r0, 0x7f80
	lwz r4, 0xc(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_34
	bge lbl_a2_35
	cmpwi r3, 0x0
	beq lbl_a2_36
	b lbl_a2_35
	lbl_a2_34:
	clrlwi. r0, r4, 9
	beq lbl_a2_37
	li r0, 0x1
	b lbl_a2_38
	lbl_a2_37:
	li r0, 0x2
	b lbl_a2_38
	lbl_a2_36:
	clrlwi. r0, r4, 9
	beq lbl_a2_39
	li r0, 0x5
	b lbl_a2_38
	lbl_a2_39:
	li r0, 0x3
	b lbl_a2_38
	lbl_a2_35:
	li r0, 0x4
	lbl_a2_38:
	cmpwi r0, 0x1
	bne lbl_a2_32
	lis r3, __float_nan@ha
	lfs f3, __float_nan@l(r3)
	lbl_a2_32:
	lfs f1, float_0_80419b9c(r2)
	lfs f0, 0x24(r1)
	fmr f2, f1
	fneg f4, f0
	bl angleABf
	lfs f0, float_45_80419c20(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne lbl_a2_30
	lfs f4, 0x20(r1)
	lfs f1, 0x28(r1)
	fmuls f0, f30, f4
	lfs f2, float_0p5_80419ba0(r2)
	lfs f3, 0x0(r27)
	fmadds f0, f29, f1, f0
	fnmsubs f1, f0, f1, f29
	fnmsubs f0, f0, f4, f30
	fmuls f1, f2, f1
	fmuls f0, f2, f0
	fadds f1, f3, f1
	stfs f1, 0x0(r27)
	lfs f1, 0x0(r28)
	fadds f0, f1, f0
	stfs f0, 0x0(r28)
	lwz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 15, 15
	beq lbl_a2_40
	lfs f1, float_180_80419bec(r2)
	lfs f0, 0x0(r29)
	fadds f1, f1, f0
	bl reviseAngle
	fmr f30, f1
	lfs f1, float_0_80419b9c(r2)
	lfs f4, float_100_80419c18(r2)
	lfs f3, 0x28(r1)
	fmr f2, f1
	lfs f0, 0x20(r1)
	fmuls f3, f4, f3
	fmuls f4, f4, f0
	bl angleABf
	bl reviseAngle
	fmr f29, f1
	fsubs f1, f29, f30
	bl reviseAngle
	fadds f1, f29, f1
	bl reviseAngle
	fctiwz f0, f1
	lis r0, 0x4330
	stw r0, 0x40(r1)
	lfd f1, 0x1d8(r31)
	stfd f0, 0x48(r1)
	lwz r0, 0x4c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x44(r1)
	lfd f0, 0x40(r1)
	fsubs f0, f0, f1
	stfs f0, 0x0(r29)
	lbl_a2_40:
	mr r3, r30
	b lbl_a2_2
	lbl_a2_30:
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f31, f0
	ble lbl_a2_41
	frsqrte f1, f31
	lfd f3, 0x1c0(r31)
	lfd f2, 0x1c8(r31)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f31, f0, f2
	fmul f0, f1, f0
	fmul f31, f31, f0
	frsp f31, f31
	b lbl_a2_42
	lbl_a2_41:
	lfd f0, 0x1d0(r31)
	fcmpo cr0, f31, f0
	bge lbl_a2_43
	lis r3, __float_nan@ha
	lfs f31, __float_nan@l(r3)
	b lbl_a2_42
	lbl_a2_43:
	stfs f31, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_44
	bge lbl_a2_45
	cmpwi r3, 0x0
	beq lbl_a2_46
	b lbl_a2_45
	lbl_a2_44:
	clrlwi. r0, r4, 9
	beq lbl_a2_47
	li r0, 0x1
	b lbl_a2_48
	lbl_a2_47:
	li r0, 0x2
	b lbl_a2_48
	lbl_a2_46:
	clrlwi. r0, r4, 9
	beq lbl_a2_49
	li r0, 0x5
	b lbl_a2_48
	lbl_a2_49:
	li r0, 0x3
	b lbl_a2_48
	lbl_a2_45:
	li r0, 0x4
	lbl_a2_48:
	cmpwi r0, 0x1
	bne lbl_a2_42
	lis r3, __float_nan@ha
	lfs f31, __float_nan@l(r3)
	lbl_a2_42:
	lfs f1, float_0p75_80419bf4(r2)
	lfs f0, 0x14c(r26)
	fmadds f0, f1, f0, f31
	stfs f0, 0x2c(r1)
	lwz r0, 0x0(r26)
	lfs f0, 0x150(r26)
	rlwinm. r0, r0, 0, 18, 18
	fmuls f2, f1, f0
	beq lbl_a2_50
	lfs f0, 0x90(r26)
	addi r4, r1, 0x38
	lfs f1, 0x8c(r26)
	addi r5, r1, 0x34
	fadds f2, f0, f2
	lfs f3, 0x94(r26)
	lfs f4, 0x1c(r1)
	addi r6, r1, 0x30
	lfs f5, float_0_80419b9c(r2)
	addi r7, r1, 0x2c
	lfs f6, 0x18(r1)
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x4
	bl hitCheckAttr
	b lbl_a2_51
	lbl_a2_50:
	lfs f0, 0x90(r26)
	addi r4, r1, 0x38
	lfs f1, 0x8c(r26)
	addi r5, r1, 0x34
	fadds f2, f0, f2
	lfs f3, 0x94(r26)
	lfs f4, 0x1c(r1)
	addi r6, r1, 0x30
	lfs f5, float_0_80419b9c(r2)
	addi r7, r1, 0x2c
	lfs f6, 0x18(r1)
	addi r8, r1, 0x28
	addi r9, r1, 0x24
	addi r10, r1, 0x20
	li r3, 0x0
	bl hitCheckFilter
	lbl_a2_51:
	cmplwi r3, 0x0
	mr r30, r3
	beq lbl_a2_52
	lfs f4, 0x20(r1)
	lfs f1, 0x28(r1)
	fmuls f0, f30, f4
	lfs f2, float_0p5_80419ba0(r2)
	lfs f3, 0x0(r27)
	fmadds f0, f29, f1, f0
	fnmsubs f1, f0, f1, f29
	fnmsubs f0, f0, f4, f30
	fmuls f1, f2, f1
	fmuls f0, f2, f0
	fadds f1, f3, f1
	stfs f1, 0x0(r27)
	lfs f1, 0x0(r28)
	fadds f0, f1, f0
	stfs f0, 0x0(r28)
	lwz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 15, 15
	beq lbl_a2_53
	lfs f1, float_180_80419bec(r2)
	lfs f0, 0x0(r29)
	fadds f1, f1, f0
	bl reviseAngle
	fmr f30, f1
	lfs f1, float_0_80419b9c(r2)
	lfs f4, float_100_80419c18(r2)
	lfs f3, 0x28(r1)
	fmr f2, f1
	lfs f0, 0x20(r1)
	fmuls f3, f4, f3
	fmuls f4, f4, f0
	bl angleABf
	bl reviseAngle
	fmr f29, f1
	fsubs f1, f29, f30
	bl reviseAngle
	fadds f1, f29, f1
	bl reviseAngle
	fctiwz f0, f1
	lis r0, 0x4330
	stw r0, 0x40(r1)
	lfd f1, 0x1d8(r31)
	stfd f0, 0x48(r1)
	lwz r0, 0x4c(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x44(r1)
	lfd f0, 0x40(r1)
	fsubs f0, f0, f1
	stfs f0, 0x0(r29)
	lbl_a2_53:
	mr r3, r30
	b lbl_a2_2
	lbl_a2_52:
	lfs f0, 0x0(r27)
	li r3, 0x0
	fadds f0, f0, f29
	stfs f0, 0x0(r27)
	lfs f0, 0x0(r28)
	fadds f0, f0, f30
	stfs f0, 0x0(r28)
	lbl_a2_2:
	psq_l f31, 0x98(r1), 0, 0
	lfd f31, 0x90(r1)
	psq_l f30, 0x88(r1), 0, 0
	lfd f30, 0x80(r1)
	psq_l f29, 0x78(r1), 0, 0
	lfd f29, 0x70(r1)
	lmw r26, 0x58(r1)
	lwz r0, 0xa4(r1)
	mtlr r0
	addi r1, r1, 0xa0
	blr
}

asm f32 npcTransRytoFaceDir(NpcEntry* npc) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lfs f1, 0x144(r3)
	bl reviseAngle
	lfs f0, float_180_80419bec(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_1
	lfs f1, float_90_80419bd0(r2)
	b lbl_a2_2
	lbl_a2_1:
	lfs f1, float_270_80419be4(r2)
	lbl_a2_2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void npcTuningRy(NpcEntry* npc, f32 angle) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r3
	bl reviseAngle
	stfs f1, 0x144(r31)
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void npcMoveG(NpcEntry* npc) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stw r31, 0x2c(r1)
	lfs f0, float_0_80419b9c(r2)
	mr r31, r3
	lfs f31, 0x1b8(r3)
	stfs f0, 0x1b8(r3)
	lwz r3, 0x1d4(r3)
	rlwinm. r4, r3, 0, 11, 11
	beq lbl_a2_1
	rlwinm. r0, r3, 0, 3, 3
	bne lbl_a2_1
	lfs f0, float_0p5_80419ba0(r2)
	fmuls f31, f31, f0
	lbl_a2_1:
	lwz r5, 0x0(r31)
	lfs f3, float_0_80419b9c(r2)
	rlwinm. r0, r5, 0, 14, 14
	beq lbl_a2_2
	lfs f4, 0x180(r31)
	cmplwi r4, 0x0
	lfs f5, 0x1a4(r31)
	fsubs f0, f4, f5
	beq lbl_a2_3
	rlwinm. r0, r3, 0, 3, 3
	beq lbl_a2_4
	lbl_a2_3:
	fmuls f0, f0, f0
	lfs f2, float_neg980_80419c24(r2)
	lfs f1, 0x1cc(r31)
	lfs f3, 0x1c4(r31)
	fmuls f1, f2, f1
	fmsubs f0, f4, f4, f0
	fmuls f0, f1, f0
	fmadds f3, f3, f5, f0
	b lbl_a2_5
	lbl_a2_4:
	lfs f2, float_neg980_80419c24(r2)
	fmuls f0, f0, f0
	lfs f1, 0x1cc(r31)
	lfs f3, 0x1c4(r31)
	fmuls f1, f2, f1
	lfs f2, float_0p15_80419c28(r2)
	fmsubs f0, f4, f4, f0
	lfs f4, float_0p4_80419c1c(r2)
	fmuls f3, f3, f5
	fmuls f1, f2, f1
	fmuls f0, f1, f0
	fmadds f3, f4, f3, f0
	lbl_a2_5:
	lfs f1, 0x1c8(r31)
	lfs f2, 0x1d0(r31)
	lfs f0, float_0_80419b9c(r2)
	fmuls f3, f3, f1
	fcmpo cr0, f2, f0
	ble lbl_a2_2
	cmplwi r4, 0x0
	beq lbl_a2_6
	fneg f0, f2
	lfs f1, float_0p5_80419ba0(r2)
	fmuls f0, f0, f5
	fmuls f0, f1, f0
	b lbl_a2_7
	lbl_a2_6:
	fneg f0, f2
	fmuls f0, f0, f5
	lbl_a2_7:
	fcmpo cr0, f3, f0
	bge lbl_a2_2
	fmr f3, f0
	lbl_a2_2:
	rlwinm. r0, r5, 0, 27, 27
	fadds f31, f31, f3
	bne lbl_a2_8
	lfs f1, 0x90(r31)
	lfs f0, float_neg1000_80419c2c(r2)
	fadds f1, f1, f31
	stfs f1, 0x90(r31)
	lfs f1, 0x90(r31)
	fcmpo cr0, f1, f0
	bge lbl_a2_9
	stfs f0, 0x90(r31)
	b lbl_a2_9
	lbl_a2_8:
	lfs f4, float_0_80419b9c(r2)
	fcmpu cr0, f4, f31
	beq lbl_a2_9
	fcmpo cr0, f31, f4
	ble lbl_a2_10
	lwz r0, 0x1d4(r31)
	ori r0, r0, 0x1
	stw r0, 0x1d4(r31)
	lfs f0, 0x90(r31)
	fadds f0, f0, f31
	stfs f0, 0x90(r31)
	b lbl_a2_9
	lbl_a2_10:
	fabs f2, f31
	lfs f1, float_0p8_80419bb0(r2)
	lfs f0, 0x150(r31)
	fmr f6, f4
	lfs f5, float_neg1_80419bf8(r2)
	addi r4, r1, 0x20
	fmuls f3, f1, f0
	addi r5, r1, 0x1c
	frsp f0, f2
	addi r6, r1, 0x18
	addi r7, r1, 0x14
	addi r8, r1, 0x10
	fadds f0, f3, f0
	addi r9, r1, 0xc
	addi r10, r1, 0x8
	li r3, 0x0
	stfs f0, 0x14(r1)
	lfs f0, 0x90(r31)
	lfs f1, 0x8c(r31)
	fadds f2, f0, f3
	lfs f3, 0x94(r31)
	bl hitCheckFilter
	cmplwi r3, 0x0
	stw r3, 0x300(r31)
	bne lbl_a2_11
	lwz r0, 0x1d4(r31)
	ori r0, r0, 0x1
	stw r0, 0x1d4(r31)
	lfs f0, 0x90(r31)
	fadds f0, f0, f31
	stfs f0, 0x90(r31)
	b lbl_a2_9
	lbl_a2_11:
	lwz r3, 0x1d4(r31)
	li r0, 0x0
	clrrwi r3, r3, 1
	stw r3, 0x1d4(r31)
	lfs f0, 0x1c(r1)
	stfs f0, 0x90(r31)
	stw r0, 0x17c(r31)
	stw r0, 0x178(r31)
	lbl_a2_9:
	psq_l f31, 0x38(r1), 0, 0
	lwz r0, 0x44(r1)
	lfd f31, 0x30(r1)
	lwz r31, 0x2c(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm BOOL npcCheckHitMarioSide(NpcEntry* npc) {
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
	lis r4, vec3_802c2f78@ha
	mr r29, r3
	addi r30, r4, vec3_802c2f78@l
	bl marioGetPtr
	mr r31, r3
	lfs f1, 0x90(r29)
	lfs f2, 0x90(r3)
	lfs f0, 0x1b8(r3)
	fadds f0, f2, f0
	fcmpo cr0, f1, f0
	ble lbl_a2_1
	li r3, 0x0
	b lbl_a2_2
	lbl_a2_1:
	lfs f0, 0x150(r29)
	fadds f0, f1, f0
	fcmpo cr0, f2, f0
	ble lbl_a2_3
	li r3, 0x0
	b lbl_a2_2
	lbl_a2_3:
	lfs f0, 0x8c(r31)
	addi r3, r1, 0xc
	addi r4, r29, 0x8c
	stfs f0, 0xc(r1)
	lfs f0, 0x94(r31)
	stfs f0, 0x14(r1)
	stfs f1, 0x10(r1)
	bl PSVECDistance
	lfs f2, 0x1b4(r31)
	lfs f0, 0x14c(r29)
	lfs f3, float_5_80419c30(r2)
	fadds f2, f2, f0
	lfs f0, float_0p5_80419ba0(r2)
	fadds f2, f3, f2
	fmuls f30, f2, f0
	fcmpo cr0, f1, f30
	ble lbl_a2_4
	li r3, 0x0
	b lbl_a2_2
	lbl_a2_4:
	lfs f0, 0x98(r29)
	addi r3, r1, 0xc
	addi r4, r29, 0x8c
	stfs f0, 0x8c(r29)
	lfs f0, 0xa0(r29)
	stfs f0, 0x94(r29)
	bl PSVECDistance
	fmr f29, f1
	fcmpo cr0, f29, f30
	ble lbl_a2_5
	li r3, 0x0
	b lbl_a2_2
	lbl_a2_5:
	stw r29, 0x1d8(r31)
	lfs f1, 0x8c(r31)
	lfs f2, 0x94(r31)
	lfs f3, 0x8c(r29)
	lfs f4, 0x94(r29)
	bl angleABf
	fmr f31, f1
	lfs f2, 0x1a0(r31)
	bl compAngle
	fabs f1, f1
	lfs f0, float_40_80419c34(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_6
	lfs f2, float_6p2832_80419c38(r2)
	lfs f1, 0x1a0(r31)
	lfs f0, float_360_80419be0(r2)
	fmuls f2, f2, f1
	lfs f1, float_3p1416_80419c44(r2)
	lfs f4, float_0p00761_80419c3c(r2)
	lfs f3, float_0p16605_80419c40(r2)
	fdivs f6, f2, f0
	lfs f2, float_1_80419bb4(r2)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne lbl_a2_7
	lfs f1, float_1p5708_80419c48(r2)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne lbl_a2_8
	fmuls f0, f6, f6
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f6
	b lbl_a2_9
	lbl_a2_8:
	fsubs f0, f6, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b lbl_a2_9
	lbl_a2_7:
	lfs f0, float_4p7124_80419c4c(r2)
	fcmpo cr0, f6, f0
	bge lbl_a2_10
	fsubs f1, f6, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b lbl_a2_9
	lbl_a2_10:
	fsubs f0, f6, f0
	lfs f1, float_1p5708_80419c48(r2)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	lbl_a2_9:
	lfs f2, float_3p1416_80419c44(r2)
	fsubs f7, f30, f29
	fneg f0, f4
	lfs f5, float_0p03705_80419c50(r2)
	fcmpo cr0, f6, f2
	lfs f4, float_0p4967_80419c54(r2)
	lfs f3, float_1_80419bb4(r2)
	fmuls f0, f7, f0
	cror eq, lt, eq
	bne lbl_a2_11
	lfs f2, float_1p5708_80419c48(r2)
	fcmpo cr0, f6, f2
	cror eq, lt, eq
	bne lbl_a2_12
	fmuls f1, f6, f6
	fmsubs f5, f5, f1, f4
	fmadds f5, f5, f1, f3
	b lbl_a2_13
	lbl_a2_12:
	fsubs f1, f6, f2
	fsubs f1, f2, f1
	fmuls f1, f1, f1
	fmsubs f5, f5, f1, f4
	fmadds f5, f5, f1, f3
	fneg f5, f5
	b lbl_a2_13
	lbl_a2_11:
	lfs f1, float_4p7124_80419c4c(r2)
	fcmpo cr0, f6, f1
	bge lbl_a2_14
	fsubs f1, f6, f2
	fmuls f1, f1, f1
	fmsubs f5, f5, f1, f4
	fmadds f5, f5, f1, f3
	fneg f5, f5
	b lbl_a2_13
	lbl_a2_14:
	fsubs f1, f6, f1
	lfs f2, float_1p5708_80419c48(r2)
	fsubs f1, f2, f1
	fmuls f1, f1, f1
	fmsubs f5, f5, f1, f4
	fmadds f5, f5, f1, f3
	lbl_a2_13:
	fmuls f4, f7, f5
	b lbl_a2_15
	lbl_a2_6:
	lfs f1, float_6p2832_80419c38(r2)
	lfs f0, float_360_80419be0(r2)
	fmuls f2, f1, f31
	lfs f1, float_3p1416_80419c44(r2)
	lfs f4, float_0p00761_80419c3c(r2)
	lfs f3, float_0p16605_80419c40(r2)
	fdivs f6, f2, f0
	lfs f2, float_1_80419bb4(r2)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne lbl_a2_16
	lfs f1, float_1p5708_80419c48(r2)
	fcmpo cr0, f6, f1
	cror eq, lt, eq
	bne lbl_a2_17
	fmuls f0, f6, f6
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f6
	b lbl_a2_18
	lbl_a2_17:
	fsubs f0, f6, f1
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	b lbl_a2_18
	lbl_a2_16:
	lfs f0, float_4p7124_80419c4c(r2)
	fcmpo cr0, f6, f0
	bge lbl_a2_19
	fsubs f1, f6, f1
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	b lbl_a2_18
	lbl_a2_19:
	fsubs f0, f6, f0
	lfs f1, float_1p5708_80419c48(r2)
	fsubs f1, f1, f0
	fmuls f0, f1, f1
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f1
	fneg f4, f4
	lbl_a2_18:
	lfs f0, 0x8c(r29)
	lfs f2, float_3p1416_80419c44(r2)
	fnmsubs f1, f30, f4, f0
	lfs f0, 0x8c(r31)
	fcmpo cr0, f6, f2
	lfs f5, float_0p03705_80419c50(r2)
	lfs f4, float_0p4967_80419c54(r2)
	fsubs f0, f1, f0
	lfs f3, float_1_80419bb4(r2)
	cror eq, lt, eq
	bne lbl_a2_20
	lfs f2, float_1p5708_80419c48(r2)
	fcmpo cr0, f6, f2
	cror eq, lt, eq
	bne lbl_a2_21
	fmuls f1, f6, f6
	fmsubs f5, f5, f1, f4
	fmadds f5, f5, f1, f3
	b lbl_a2_22
	lbl_a2_21:
	fsubs f1, f6, f2
	fsubs f1, f2, f1
	fmuls f1, f1, f1
	fmsubs f5, f5, f1, f4
	fmadds f5, f5, f1, f3
	fneg f5, f5
	b lbl_a2_22
	lbl_a2_20:
	lfs f1, float_4p7124_80419c4c(r2)
	fcmpo cr0, f6, f1
	bge lbl_a2_23
	fsubs f1, f6, f2
	fmuls f1, f1, f1
	fmsubs f5, f5, f1, f4
	fmadds f5, f5, f1, f3
	fneg f5, f5
	b lbl_a2_22
	lbl_a2_23:
	fsubs f1, f6, f1
	lfs f2, float_1p5708_80419c48(r2)
	fsubs f1, f2, f1
	fmuls f1, f1, f1
	fmsubs f5, f5, f1, f4
	fmadds f5, f5, f1, f3
	lbl_a2_22:
	lfs f2, 0x94(r29)
	lfs f1, 0x94(r31)
	fmadds f2, f30, f5, f2
	fsubs f4, f2, f1
	lbl_a2_15:
	fmuls f2, f4, f4
	lfs f1, float_0_80419b9c(r2)
	fmadds f6, f0, f0, f2
	fcmpo cr0, f6, f1
	ble lbl_a2_24
	frsqrte f2, f6
	lfd f5, 0x1c0(r30)
	lfd f3, 0x1c8(r30)
	fmul f1, f2, f2
	fmul f2, f5, f2
	fnmsub f1, f6, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f5, f2
	fnmsub f1, f6, f1, f3
	fmul f2, f2, f1
	fmul f1, f2, f2
	fmul f2, f5, f2
	fnmsub f1, f6, f1, f3
	fmul f1, f2, f1
	fmul f6, f6, f1
	frsp f6, f6
	b lbl_a2_25
	lbl_a2_24:
	lfd f1, 0x1d0(r30)
	fcmpo cr0, f6, f1
	bge lbl_a2_26
	lis r3, __float_nan@ha
	lfs f6, __float_nan@l(r3)
	b lbl_a2_25
	lbl_a2_26:
	stfs f6, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_27
	bge lbl_a2_28
	cmpwi r3, 0x0
	beq lbl_a2_29
	b lbl_a2_28
	lbl_a2_27:
	clrlwi. r0, r4, 9
	beq lbl_a2_30
	li r0, 0x1
	b lbl_a2_31
	lbl_a2_30:
	li r0, 0x2
	b lbl_a2_31
	lbl_a2_29:
	clrlwi. r0, r4, 9
	beq lbl_a2_32
	li r0, 0x5
	b lbl_a2_31
	lbl_a2_32:
	li r0, 0x3
	b lbl_a2_31
	lbl_a2_28:
	li r0, 0x4
	lbl_a2_31:
	cmpwi r0, 0x1
	bne lbl_a2_25
	lis r3, __float_nan@ha
	lfs f6, __float_nan@l(r3)
	lbl_a2_25:
	lfs f2, 0x1bc(r31)
	lfs f1, float_4_80419c58(r2)
	fcmpo cr0, f2, f1
	ble lbl_a2_33
	lfs f1, float_3_80419c08(r2)
	b lbl_a2_34
	lbl_a2_33:
	lfs f1, float_1p5_80419bcc(r2)
	lbl_a2_34:
	fcmpo cr0, f6, f1
	ble lbl_a2_35
	lfs f1, float_2_80419c5c(r2)
	fdivs f1, f1, f6
	fmuls f0, f0, f1
	fmuls f4, f4, f1
	lbl_a2_35:
	lfs f1, 0x8c(r31)
	addi r3, r31, 0x8c
	lfs f2, float_160_80419c60(r2)
	li r4, 0x0
	fadds f0, f1, f0
	lfs f1, float_0_80419b9c(r2)
	fadds f2, f2, f31
	lfs f3, float_20_80419c00(r2)
	stfs f0, 0x8c(r31)
	lfs f0, 0x94(r31)
	fadds f0, f0, f4
	stfs f0, 0x94(r31)
	lfs f4, 0x1b8(r31)
	bl marioChkWallAround
	li r3, 0x1
	lbl_a2_2:
	psq_l f31, 0x58(r1), 0, 0
	lfd f31, 0x50(r1)
	psq_l f30, 0x48(r1), 0, 0
	lfd f30, 0x40(r1)
	psq_l f29, 0x38(r1), 0, 0
	lfd f29, 0x30(r1)
	lwz r31, 0x2c(r1)
	lwz r30, 0x28(r1)
	lwz r0, 0x64(r1)
	lwz r29, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void npcSetStayPose(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lbz r0, 0x0(r3)
	extsb. r0, r0
	beq lbl_a2_1
	lis r4, str_802C31C0@ha
	addi r4, r4, str_802C31C0@l
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_1
	mr r3, r28
	la r4, str_80419C64(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne lbl_a2_2
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq lbl_a2_1
	li r4, 0x1
	bl partyChgPoseId
	b lbl_a2_1
	lbl_a2_2:
	lis r4, str_802C31CC@ha
	mr r3, r28
	addi r4, r4, str_802C31CC@l
	bl strcmp
	cmpwi r3, 0x0
	bne lbl_a2_3
	bl marioGetExtraPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq lbl_a2_1
	li r4, 0x1
	bl partyChgPoseId
	b lbl_a2_1
	lbl_a2_3:
	mr r3, r28
	la r4, str_80419C6C(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne lbl_a2_4
	la r3, MarioStayPose(r13)
	bl marioChgPose
	b lbl_a2_1
	lbl_a2_4:
	lwz r3, gp(r13)
	la r4, work(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_5
	addi r4, r4, 0x14
	lbl_a2_5:
	lwz r30, 0x4(r4)
	li r29, 0x0
	lwz r31, 0xc(r4)
	b lbl_a2_6
	lbl_a2_7:
	lwz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	beq lbl_a2_8
	mr r4, r28
	addi r3, r31, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_9
	lbl_a2_8:
	addi r29, r29, 0x1
	addi r31, r31, 0x340
	lbl_a2_6:
	cmpw r29, r30
	blt lbl_a2_7
	lbl_a2_9:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 22, 22
	beq lbl_a2_1
	lwz r3, 0x104(r31)
	addi r4, r31, 0x4c
	li r5, 0x1
	bl animPoseSetAnim
	lbl_a2_1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcSetTalkPose(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lbz r0, 0x0(r3)
	extsb. r0, r0
	beq lbl_a2_1
	lis r4, str_802C31C0@ha
	addi r4, r4, str_802C31C0@l
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_1
	mr r3, r28
	la r4, str_80419C64(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne lbl_a2_2
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq lbl_a2_1
	li r4, 0x7
	bl partyChgPoseId
	b lbl_a2_1
	lbl_a2_2:
	lis r4, str_802C31CC@ha
	mr r3, r28
	addi r4, r4, str_802C31CC@l
	bl strcmp
	cmpwi r3, 0x0
	bne lbl_a2_3
	bl marioGetExtraPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq lbl_a2_1
	li r4, 0x7
	bl partyChgPoseId
	b lbl_a2_1
	lbl_a2_3:
	mr r3, r28
	la r4, str_80419C6C(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne lbl_a2_4
	la r3, MarioTalkPose(r13)
	bl marioChgPose
	b lbl_a2_1
	lbl_a2_4:
	lwz r3, gp(r13)
	la r4, work(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_5
	addi r4, r4, 0x14
	lbl_a2_5:
	lwz r30, 0x4(r4)
	li r29, 0x0
	lwz r31, 0xc(r4)
	b lbl_a2_6
	lbl_a2_7:
	lwz r0, 0x0(r31)
	clrlwi. r0, r0, 31
	beq lbl_a2_8
	mr r4, r28
	addi r3, r31, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_9
	lbl_a2_8:
	addi r29, r29, 0x1
	addi r31, r31, 0x340
	lbl_a2_6:
	cmpw r29, r30
	blt lbl_a2_7
	lbl_a2_9:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 22, 22
	beq lbl_a2_1
	lwz r3, 0x104(r31)
	addi r4, r31, 0x6c
	li r5, 0x1
	bl animPoseSetAnim
	lbl_a2_1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcSetMarioAutoTalkPose(const char* stayPose, const char* talkPose) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r4
	mr r4, r3
	la r3, MarioStayPose(r13)
	bl strcpy
	mr r4, r31
	la r3, MarioTalkPose(r13)
	bl strcpy
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm NpcEntry* npcNameToPtr_NoAssert(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	la r3, work(r13)
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r3, r3, 0x14
	lbl_a2_1:
	lwz r30, 0x4(r3)
	li r31, 0x0
	lwz r29, 0xc(r3)
	b lbl_a2_2
	lbl_a2_3:
	lwz r0, 0x0(r29)
	clrlwi. r0, r0, 31
	beq lbl_a2_4
	mr r4, r28
	addi r3, r29, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_5
	lbl_a2_4:
	addi r31, r31, 0x1
	addi r29, r29, 0x340
	lbl_a2_2:
	cmpw r31, r30
	blt lbl_a2_3
	lbl_a2_5:
	cmpw r31, r30
	blt lbl_a2_6
	li r3, 0x0
	b lbl_a2_7
	lbl_a2_6:
	mr r3, r29
	lbl_a2_7:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm NpcEntry* npcNameToPtr(const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	la r3, work(r13)
	lwz r4, gp(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r3, r3, 0x14
	lbl_a2_1:
	lwz r30, 0x4(r3)
	li r31, 0x0
	lwz r29, 0xc(r3)
	b lbl_a2_2
	lbl_a2_3:
	lwz r0, 0x0(r29)
	clrlwi. r0, r0, 31
	beq lbl_a2_4
	mr r4, r28
	addi r3, r29, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_5
	lbl_a2_4:
	addi r31, r31, 0x1
	addi r29, r29, 0x340
	lbl_a2_2:
	cmpw r31, r30
	blt lbl_a2_3
	lbl_a2_5:
	lwz r0, 0x24(r1)
	mr r3, r29
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcMain(void) {
	nofralloc
	stwu r1, -0x130(r1)
	mflr r0
	stw r0, 0x134(r1)
	stfd f31, 0x120(r1)
	psq_st f31, 0x128(r1), 0, 0
	stfd f30, 0x110(r1)
	psq_st f30, 0x118(r1), 0, 0
	stfd f29, 0x100(r1)
	psq_st f29, 0x108(r1), 0, 0
	stfd f28, 0xf0(r1)
	psq_st f28, 0xf8(r1), 0, 0
	stfd f27, 0xe0(r1)
	psq_st f27, 0xe8(r1), 0, 0
	stmw r24, 0xc0(r1)
	lwz r3, gp(r13)
	lis r4, vec3_802c2f78@ha
	addi r30, r4, vec3_802c2f78@l
	la r25, work(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r25, r25, 0x14
	lbl_a2_1:
	li r24, 0x0
	bl marioGetPtr
	stw r24, 0x1d8(r3)
	addi r27, r30, 0x194
	li r29, 0x0
	lwz r3, npcMainCount(r13)
	lwz r28, 0x4(r25)
	addi r0, r3, 0x1
	lwz r31, 0xc(r25)
	stw r0, npcMainCount(r13)
	b lbl_a2_2
	lbl_a2_3:
	lwz r3, 0x0(r31)
	clrlwi. r0, r3, 31
	beq lbl_a2_4
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_4
	rlwinm. r0, r3, 0, 16, 16
	beq lbl_a2_5
	lwz r3, 0x104(r31)
	bl animPoseGetAnimPosePtr
	lwz r0, 0x0(r3)
	ori r0, r0, 0x100
	stw r0, 0x0(r3)
	b lbl_a2_6
	lbl_a2_5:
	lwz r3, 0x104(r31)
	bl animPoseGetAnimPosePtr
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 24, 22
	stw r0, 0x0(r3)
	lbl_a2_6:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 11, 11
	bne lbl_a2_7
	lwz r0, 0x1d4(r31)
	ori r0, r0, 0x10
	stw r0, 0x1d4(r31)
	lbl_a2_7:
	lwz r3, 0x1d4(r31)
	rlwinm. r0, r3, 0, 15, 15
	beq lbl_a2_8
	rlwinm r0, r3, 0, 28, 26
	stw r0, 0x1d4(r31)
	lbl_a2_8:
	lhz r3, 0x320(r31)
	cmplwi r3, 0x0
	beq lbl_a2_9
	subi r0, r3, 0x1
	sth r0, 0x320(r31)
	lbl_a2_9:
	lwz r0, 0x1d4(r31)
	rlwinm. r0, r0, 0, 27, 27
	beq lbl_a2_10
	lwz r5, gp(r13)
	lis r3, 0x1062
	addi r6, r3, 0x4dd3
	lwz r0, 0x19c(r31)
	lwz r8, 0x3c(r5)
	lis r4, 0x8000
	lwz r7, 0x38(r5)
	li r5, 0x0
	lwz r3, 0x198(r31)
	subfc r0, r0, r8
	stw r0, 0x194(r31)
	subfe r0, r3, r7
	stw r0, 0x190(r31)
	lwz r0, 0xf8(r4)
	lwz r3, 0x190(r31)
	srwi r0, r0, 2
	lwz r4, 0x194(r31)
	mulhwu r0, r6, r0
	srwi r24, r0, 6
	mr r6, r24
	bl __div2i
	li r0, 0x1f4
	li r6, 0x0
	xoris r5, r6, 0x8000
	xoris r3, r3, 0x8000
	subfc r0, r4, r0
	subfe r3, r3, r5
	subfe r3, r5, r5
	neg. r3, r3
	beq lbl_a2_11
	slwi r0, r24, 4
	stw r0, 0x194(r31)
	stw r6, 0x190(r31)
	lbl_a2_11:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 14, 14
	beq lbl_a2_12
	lwz r5, 0x17c(r31)
	lwz r0, 0x194(r31)
	lwz r4, 0x178(r31)
	lwz r3, 0x190(r31)
	addc r0, r5, r0
	stw r0, 0x17c(r31)
	adde r0, r4, r3
	stw r0, 0x178(r31)
	b lbl_a2_13
	lbl_a2_12:
	li r0, 0x0
	stw r0, 0x17c(r31)
	stw r0, 0x178(r31)
	lbl_a2_13:
	lwz r5, 0x18c(r31)
	lis r3, 0x431c
	lwz r0, 0x194(r31)
	lis r4, 0x8000
	lwz r7, 0x188(r31)
	subi r3, r3, 0x217d
	addc r0, r5, r0
	lwz r6, 0x190(r31)
	li r5, 0x0
	stw r0, 0x18c(r31)
	adde r0, r7, r6
	stw r0, 0x188(r31)
	lwz r6, gp(r13)
	lwz r0, 0x38(r6)
	lwz r6, 0x3c(r6)
	stw r6, 0x19c(r31)
	stw r0, 0x198(r31)
	lwz r0, 0xf8(r4)
	lwz r4, 0x188(r31)
	srwi r0, r0, 2
	lwz r6, 0x18c(r31)
	mulhwu r0, r3, r0
	slwi r3, r4, 3
	slwi r4, r6, 3
	rlwimi r3, r6, 3, 29, 31
	srwi r6, r0, 15
	bl __div2i
	bl __cvt_sll_flt
	lfs f0, float_1E06_80419c74(r2)
	lis r3, 0x431c
	lis r4, 0x8000
	li r5, 0x0
	fdivs f0, f1, f0
	subi r3, r3, 0x217d
	stfs f0, 0x1a0(r31)
	lwz r0, 0xf8(r4)
	lwz r4, 0x178(r31)
	srwi r0, r0, 2
	lwz r6, 0x17c(r31)
	mulhwu r0, r3, r0
	slwi r3, r4, 3
	slwi r4, r6, 3
	rlwimi r3, r6, 3, 29, 31
	srwi r6, r0, 15
	bl __div2i
	bl __cvt_sll_flt
	lfs f0, float_1E06_80419c74(r2)
	lis r3, 0x431c
	lis r4, 0x8000
	li r5, 0x0
	fdivs f0, f1, f0
	subi r3, r3, 0x217d
	stfs f0, 0x180(r31)
	lwz r0, 0xf8(r4)
	lwz r4, 0x190(r31)
	srwi r0, r0, 2
	lwz r6, 0x194(r31)
	mulhwu r0, r3, r0
	slwi r3, r4, 3
	slwi r4, r6, 3
	rlwimi r3, r6, 3, 29, 31
	srwi r6, r0, 15
	bl __div2i
	bl __cvt_sll_flt
	lfs f0, float_1E06_80419c74(r2)
	lis r3, 0x431c
	lis r4, 0x8000
	li r5, 0x0
	fdivs f0, f1, f0
	subi r3, r3, 0x217d
	stfs f0, 0x1a4(r31)
	lwz r0, 0xf8(r4)
	lwz r4, 0x198(r31)
	srwi r0, r0, 2
	lwz r6, 0x19c(r31)
	mulhwu r0, r3, r0
	slwi r3, r4, 3
	slwi r4, r6, 3
	rlwimi r3, r6, 3, 29, 31
	srwi r6, r0, 15
	bl __div2i
	bl __cvt_sll_flt
	lfs f0, float_1E06_80419c74(r2)
	fdivs f0, f1, f0
	stfs f0, 0x1a8(r31)
	b lbl_a2_14
	lbl_a2_10:
	lwz r3, gp(r13)
	lwz r0, 0x38(r3)
	lwz r3, 0x3c(r3)
	stw r3, 0x19c(r31)
	stw r0, 0x198(r31)
	lbl_a2_14:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq lbl_a2_15
	lwz r3, 0x1d4(r31)
	rlwinm. r0, r3, 0, 11, 11
	beq lbl_a2_16
	oris r0, r3, 0x20
	stw r0, 0x1d4(r31)
	b lbl_a2_17
	lbl_a2_16:
	rlwinm r0, r3, 0, 11, 9
	stw r0, 0x1d4(r31)
	lbl_a2_17:
	lwz r0, 0x1d4(r31)
	addi r4, r30, 0x18c
	rlwinm r0, r0, 0, 12, 10
	stw r0, 0x1d4(r31)
	lwz r3, gp(r13)
	addi r3, r3, 0x12c
	bl strcmp
	cmpwi r3, 0x0
	bne lbl_a2_18
	lfs f1, 0x90(r31)
	lfs f0, float_365_80419ba8(r2)
	fcmpo cr0, f1, f0
	bgt lbl_a2_18
	lwz r0, 0x1d4(r31)
	oris r0, r0, 0x10
	stw r0, 0x1d4(r31)
	lwz r3, 0x1d4(r31)
	rlwinm. r0, r3, 0, 10, 10
	bne lbl_a2_18
	rlwinm. r0, r3, 0, 11, 11
	beq lbl_a2_18
	mr r3, r27
	addi r4, r31, 0x8c
	bl psndSFXOn_3D
	lbl_a2_18:
	lwz r3, 0x1d4(r31)
	rlwinm. r0, r3, 0, 11, 11
	beq lbl_a2_19
	rlwinm. r0, r3, 0, 3, 3
	bne lbl_a2_19
	lfs f0, float_100_80419c18(r2)
	lfs f30, float_0p5_80419ba0(r2)
	stfs f0, 0x1d0(r31)
	b lbl_a2_20
	lbl_a2_19:
	lfs f30, float_1_80419bb4(r2)
	lbl_a2_20:
	lwz r0, 0x1d4(r31)
	rlwinm. r0, r0, 0, 11, 11
	beq lbl_a2_21
	lhz r0, 0x31e(r31)
	ori r0, r0, 0x1
	sth r0, 0x31e(r31)
	lbl_a2_21:
	lwz r3, 0x1d4(r31)
	rlwinm. r0, r3, 0, 27, 27
	beq lbl_a2_22
	lfs f1, 0x1a4(r31)
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_23
	rlwinm. r0, r3, 0, 11, 11
	lfs f1, 0x1b4(r31)
	lfs f2, 0x1bc(r31)
	beq lbl_a2_24
	rlwinm. r0, r3, 0, 3, 3
	bne lbl_a2_24
	lfs f0, float_0p5_80419ba0(r2)
	fmuls f1, f1, f0
	fmuls f2, f2, f0
	lbl_a2_24:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 4, 4
	beq lbl_a2_25
	lfs f2, float_0_80419b9c(r2)
	lbl_a2_25:
	rlwinm. r0, r3, 0, 1, 1
	beq lbl_a2_26
	lfs f0, 0x8c(r31)
	fadds f0, f0, f1
	stfs f0, 0x8c(r31)
	lfs f0, 0x94(r31)
	fadds f0, f0, f2
	stfs f0, 0x94(r31)
	b lbl_a2_27
	lbl_a2_26:
	mr r3, r31
	addi r4, r31, 0x8c
	addi r5, r31, 0x94
	addi r6, r31, 0x1ac
	bl npcHitCheckSide
	stw r3, 0x2fc(r31)
	lbl_a2_27:
	lfs f0, float_0_80419b9c(r2)
	mr r3, r31
	stfs f0, 0x1b4(r31)
	stfs f0, 0x1bc(r31)
	bl npcMoveG
	lbl_a2_23:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 28, 28
	bne lbl_a2_28
	rlwinm. r0, r3, 0, 26, 26
	bne lbl_a2_28
	rlwinm. r0, r3, 0, 17, 17
	bne lbl_a2_28
	mr r3, r31
	bl npcCheckHitMarioSide
	lbl_a2_28:
	addi r3, r31, 0x8c
	addi r4, r31, 0x98
	addi r5, r1, 0xac
	bl PSVECSubtract
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 21, 21
	beq lbl_a2_22
	lfs f0, 0x1a4(r31)
	lfs f2, float_0_80419b9c(r2)
	fcmpo cr0, f0, f2
	ble lbl_a2_22
	lfs f1, 0xac(r1)
	lfs f0, 0xb4(r1)
	fmuls f1, f1, f1
	fmuls f0, f0, f0
	fadds f4, f1, f0
	fcmpo cr0, f4, f2
	ble lbl_a2_29
	frsqrte f1, f4
	lfd f3, 0x1c0(r30)
	lfd f2, 0x1c8(r30)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f0, f1, f0
	fmul f4, f4, f0
	frsp f4, f4
	b lbl_a2_30
	lbl_a2_29:
	lfd f0, 0x1d0(r30)
	fcmpo cr0, f4, f0
	bge lbl_a2_31
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	b lbl_a2_30
	lbl_a2_31:
	stfs f4, 0x1c(r1)
	lis r0, 0x7f80
	lwz r4, 0x1c(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_32
	bge lbl_a2_33
	cmpwi r3, 0x0
	beq lbl_a2_34
	b lbl_a2_33
	lbl_a2_32:
	clrlwi. r0, r4, 9
	beq lbl_a2_35
	li r0, 0x1
	b lbl_a2_36
	lbl_a2_35:
	li r0, 0x2
	b lbl_a2_36
	lbl_a2_34:
	clrlwi. r0, r4, 9
	beq lbl_a2_37
	li r0, 0x5
	b lbl_a2_36
	lbl_a2_37:
	li r0, 0x3
	b lbl_a2_36
	lbl_a2_33:
	li r0, 0x4
	lbl_a2_36:
	cmpwi r0, 0x1
	bne lbl_a2_30
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	lbl_a2_30:
	lfs f1, 0x1a4(r31)
	lfs f0, float_0p1_80419bfc(r2)
	fdivs f1, f4, f1
	fcmpo cr0, f1, f0
	bge lbl_a2_38
	lwz r0, 0x108(r31)
	cmpwi r0, 0x1
	beq lbl_a2_22
	lwz r4, 0x28(r31)
	li r5, 0x1
	lwz r3, 0x104(r31)
	lwz r4, 0x10(r4)
	bl animPoseSetAnim
	li r0, 0x1
	stw r0, 0x108(r31)
	b lbl_a2_22
	lbl_a2_38:
	lwz r4, 0x28(r31)
	lfs f0, 0x3c(r4)
	fmuls f0, f0, f30
	fcmpo cr0, f1, f0
	bge lbl_a2_39
	lwz r0, 0x108(r31)
	cmpwi r0, 0x2
	beq lbl_a2_22
	lwz r3, 0x104(r31)
	li r5, 0x1
	lwz r4, 0x18(r4)
	bl animPoseSetAnim
	li r0, 0x2
	stw r0, 0x108(r31)
	b lbl_a2_22
	lbl_a2_39:
	lwz r0, 0x108(r31)
	cmpwi r0, 0x3
	beq lbl_a2_22
	lwz r3, 0x104(r31)
	li r5, 0x1
	lwz r4, 0x1c(r4)
	bl animPoseSetAnim
	li r0, 0x3
	stw r0, 0x108(r31)
	lbl_a2_22:
	lwz r3, 0x11c(r31)
	cmpwi r3, 0x0
	beq lbl_a2_40
	bl evtGetPtrID
	cmplwi r3, 0x0
	beq lbl_a2_41
	lbz r0, 0x8(r3)
	rlwinm. r0, r0, 0, 30, 30
	bne lbl_a2_41
	lwz r0, 0x13c(r31)
	lbz r26, 0x10(r3)
	cmplwi r0, 0x0
	beq lbl_a2_42
	cmpwi r26, 0x5
	beq lbl_a2_42
	cmpwi r26, 0x8
	beq lbl_a2_42
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 2, 2
	beq lbl_a2_43
	li r0, 0x0
	b lbl_a2_44
	lbl_a2_43:
	rlwinm. r0, r3, 0, 26, 26
	beq lbl_a2_45
	li r0, 0x0
	b lbl_a2_44
	lbl_a2_45:
	lwz r5, 0x8c(r31)
	addi r3, r1, 0x58
	lwz r4, 0x90(r31)
	lwz r0, 0x94(r31)
	stw r5, 0x4c(r1)
	stw r5, 0x58(r1)
	stw r4, 0x5c(r1)
	stw r0, 0x60(r1)
	stw r4, 0x50(r1)
	lfs f1, 0x14c(r31)
	stw r0, 0x54(r1)
	bl cloudGetBreathPower
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_46
	li r0, 0x1
	b lbl_a2_44
	lbl_a2_46:
	lwz r0, 0x90(r31)
	addi r3, r1, 0x64
	lwz r5, 0x8c(r31)
	stw r0, 0x50(r1)
	lwz r4, 0x94(r31)
	lfs f2, 0x150(r31)
	lfs f1, float_0p5_80419ba0(r2)
	lfs f0, 0x50(r1)
	stw r5, 0x64(r1)
	fnmsubs f0, f2, f1, f0
	stw r4, 0x6c(r1)
	stfs f0, 0x50(r1)
	lwz r0, 0x50(r1)
	stw r5, 0x4c(r1)
	stw r0, 0x68(r1)
	stw r4, 0x54(r1)
	lfs f1, 0x14c(r31)
	bl cloudGetBreathPower
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_47
	li r0, 0x1
	b lbl_a2_44
	lbl_a2_47:
	lwz r0, 0x90(r31)
	addi r3, r1, 0x70
	lwz r5, 0x8c(r31)
	stw r0, 0x50(r1)
	lwz r4, 0x94(r31)
	lfs f0, 0x150(r31)
	lfs f1, 0x50(r1)
	stw r5, 0x70(r1)
	fsubs f0, f1, f0
	stw r4, 0x78(r1)
	stfs f0, 0x50(r1)
	lwz r0, 0x50(r1)
	stw r5, 0x4c(r1)
	stw r0, 0x74(r1)
	stw r4, 0x54(r1)
	lfs f1, 0x14c(r31)
	bl cloudGetBreathPower
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_48
	li r0, 0x1
	b lbl_a2_44
	lbl_a2_48:
	li r0, 0x0
	lbl_a2_44:
	cmpwi r0, 0x0
	beq lbl_a2_42
	lwz r0, 0x140(r31)
	ori r0, r0, 0x8
	stw r0, 0x140(r31)
	b lbl_a2_41
	lbl_a2_42:
	lwz r0, 0x1f8(r31)
	cmpwi r0, 0x0
	beq lbl_a2_49
	cmpwi r26, 0x1
	beq lbl_a2_50
	cmpwi r26, 0x2
	bne lbl_a2_49
	lbl_a2_50:
	cmpwi r0, 0x1
	li r5, 0x0
	bne lbl_a2_51
	lfs f1, 0x204(r31)
	lfs f0, 0x94(r31)
	lfs f2, 0x1fc(r31)
	fsubs f3, f1, f0
	lfs f1, 0x8c(r31)
	lfs f0, float_0_80419b9c(r2)
	fsubs f2, f2, f1
	fmuls f1, f3, f3
	fmadds f4, f2, f2, f1
	fcmpo cr0, f4, f0
	ble lbl_a2_52
	frsqrte f1, f4
	lfd f3, 0x1c0(r30)
	lfd f2, 0x1c8(r30)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f0, f1, f0
	fmul f4, f4, f0
	frsp f4, f4
	b lbl_a2_53
	lbl_a2_52:
	lfd f0, 0x1d0(r30)
	fcmpo cr0, f4, f0
	bge lbl_a2_54
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	b lbl_a2_53
	lbl_a2_54:
	stfs f4, 0x18(r1)
	lis r0, 0x7f80
	lwz r4, 0x18(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_55
	bge lbl_a2_56
	cmpwi r3, 0x0
	beq lbl_a2_57
	b lbl_a2_56
	lbl_a2_55:
	clrlwi. r0, r4, 9
	beq lbl_a2_58
	li r0, 0x1
	b lbl_a2_59
	lbl_a2_58:
	li r0, 0x2
	b lbl_a2_59
	lbl_a2_57:
	clrlwi. r0, r4, 9
	beq lbl_a2_60
	li r0, 0x5
	b lbl_a2_59
	lbl_a2_60:
	li r0, 0x3
	b lbl_a2_59
	lbl_a2_56:
	li r0, 0x4
	lbl_a2_59:
	cmpwi r0, 0x1
	bne lbl_a2_53
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	lbl_a2_53:
	cmpwi r26, 0x2
	bne lbl_a2_61
	lfs f0, 0x214(r31)
	b lbl_a2_62
	lbl_a2_61:
	lfs f0, 0x214(r31)
	lbl_a2_62:
	fcmpo cr0, f4, f0
	ble lbl_a2_63
	li r5, 0x1
	b lbl_a2_63
	lbl_a2_51:
	cmpwi r0, 0x2
	bne lbl_a2_63
	cmpwi r26, 0x2
	bne lbl_a2_64
	lfs f2, 0x1fc(r31)
	lfs f1, 0x214(r31)
	lfs f3, 0x8c(r31)
	fsubs f0, f2, f1
	fcmpo cr0, f3, f0
	blt lbl_a2_65
	fadds f0, f2, f1
	fcmpo cr0, f3, f0
	bgt lbl_a2_65
	lfs f2, 0x204(r31)
	lfs f1, 0x21c(r31)
	lfs f3, 0x94(r31)
	fsubs f0, f2, f1
	fcmpo cr0, f3, f0
	blt lbl_a2_65
	fadds f0, f2, f1
	fcmpo cr0, f3, f0
	ble lbl_a2_63
	lbl_a2_65:
	li r5, 0x1
	b lbl_a2_63
	lbl_a2_64:
	lfs f2, 0x1fc(r31)
	lfs f1, 0x208(r31)
	lfs f3, 0x8c(r31)
	fsubs f0, f2, f1
	fcmpo cr0, f3, f0
	blt lbl_a2_66
	fadds f0, f2, f1
	fcmpo cr0, f3, f0
	bgt lbl_a2_66
	lfs f2, 0x204(r31)
	lfs f1, 0x210(r31)
	lfs f3, 0x94(r31)
	fsubs f0, f2, f1
	fcmpo cr0, f3, f0
	blt lbl_a2_66
	fadds f0, f2, f1
	fcmpo cr0, f3, f0
	ble lbl_a2_63
	lbl_a2_66:
	li r5, 0x1
	lbl_a2_63:
	cmpwi r5, 0x0
	beq lbl_a2_49
	lwz r0, 0x140(r31)
	ori r0, r0, 0x4
	stw r0, 0x140(r31)
	b lbl_a2_41
	lbl_a2_49:
	cmpwi r26, 0x2
	bne lbl_a2_67
	bl marioGetPtr
	lfs f1, 0x8c(r3)
	addi r4, r31, 0x8c
	lfs f0, 0x8c(r31)
	addi r5, r1, 0xa0
	lfs f3, 0x90(r3)
	lfs f2, 0x90(r31)
	fsubs f31, f1, f0
	lfs f1, 0x94(r3)
	addi r3, r31, 0x98
	lfs f0, 0x94(r31)
	fsubs f29, f3, f2
	fsubs f28, f1, f0
	bl PSVECSubtract
	lwz r0, 0x1d4(r31)
	lfs f30, 0x144(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq lbl_a2_68
	lfs f0, 0xa0(r1)
	lfs f1, 0xa8(r1)
	fmuls f2, f0, f0
	lfs f0, float_0_80419b9c(r2)
	fmuls f1, f1, f1
	fadds f4, f2, f1
	fcmpo cr0, f4, f0
	ble lbl_a2_69
	frsqrte f1, f4
	lfd f3, 0x1c0(r30)
	lfd f2, 0x1c8(r30)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f0, f1, f0
	fmul f4, f4, f0
	frsp f4, f4
	b lbl_a2_70
	lbl_a2_69:
	lfd f0, 0x1d0(r30)
	fcmpo cr0, f4, f0
	bge lbl_a2_71
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	b lbl_a2_70
	lbl_a2_71:
	stfs f4, 0x14(r1)
	lis r0, 0x7f80
	lwz r4, 0x14(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_72
	bge lbl_a2_73
	cmpwi r3, 0x0
	beq lbl_a2_74
	b lbl_a2_73
	lbl_a2_72:
	clrlwi. r0, r4, 9
	beq lbl_a2_75
	li r0, 0x1
	b lbl_a2_76
	lbl_a2_75:
	li r0, 0x2
	b lbl_a2_76
	lbl_a2_74:
	clrlwi. r0, r4, 9
	beq lbl_a2_77
	li r0, 0x5
	b lbl_a2_76
	lbl_a2_77:
	li r0, 0x3
	b lbl_a2_76
	lbl_a2_73:
	li r0, 0x4
	lbl_a2_76:
	cmpwi r0, 0x1
	bne lbl_a2_70
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	lbl_a2_70:
	lfs f0, float_0p05_80419c78(r2)
	fcmpo cr0, f4, f0
	ble lbl_a2_68
	lfs f30, 0x1ac(r31)
	lbl_a2_68:
	li r25, 0x0
	bl marioGetPtr
	mr r24, r3
	lwz r3, 0x0(r3)
	andis. r0, r3, 0x8200
	beq lbl_a2_78
	li r0, 0x0
	b lbl_a2_79
	lbl_a2_78:
	andi. r0, r3, 0xa
	beq lbl_a2_80
	li r0, 0x0
	b lbl_a2_79
	lbl_a2_80:
	lwz r3, gp(r13)
	lwz r0, 0x164(r3)
	cmpwi r0, 0x0
	beq lbl_a2_81
	li r0, 0x0
	b lbl_a2_79
	lbl_a2_81:
	bl seqGetSeq
	cmpwi r3, 0x2
	beq lbl_a2_82
	li r0, 0x0
	b lbl_a2_79
	lbl_a2_82:
	lhz r0, 0x2e(r24)
	cmplwi r0, 0x19
	bne lbl_a2_83
	li r0, 0x0
	b lbl_a2_79
	lbl_a2_83:
	bl vivianGetStatus
	cmpwi r3, 0x0
	beq lbl_a2_84
	bl vivianGetStatus
	cmpwi r3, 0x1
	beq lbl_a2_84
	li r0, 0x0
	b lbl_a2_79
	lbl_a2_84:
	li r0, 0x1
	lbl_a2_79:
	cmpwi r0, 0x0
	bne lbl_a2_85
	li r25, 0x1
	b lbl_a2_86
	lbl_a2_85:
	fmuls f1, f28, f28
	lfs f0, float_0_80419b9c(r2)
	fmadds f4, f31, f31, f1
	fcmpo cr0, f4, f0
	ble lbl_a2_87
	frsqrte f1, f4
	lfd f3, 0x1c0(r30)
	lfd f2, 0x1c8(r30)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f0, f1, f0
	fmul f4, f4, f0
	frsp f4, f4
	b lbl_a2_88
	lbl_a2_87:
	lfd f0, 0x1d0(r30)
	fcmpo cr0, f4, f0
	bge lbl_a2_89
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	b lbl_a2_88
	lbl_a2_89:
	stfs f4, 0x10(r1)
	lis r0, 0x7f80
	lwz r4, 0x10(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_90
	bge lbl_a2_91
	cmpwi r3, 0x0
	beq lbl_a2_92
	b lbl_a2_91
	lbl_a2_90:
	clrlwi. r0, r4, 9
	beq lbl_a2_93
	li r0, 0x1
	b lbl_a2_94
	lbl_a2_93:
	li r0, 0x2
	b lbl_a2_94
	lbl_a2_92:
	clrlwi. r0, r4, 9
	beq lbl_a2_95
	li r0, 0x5
	b lbl_a2_94
	lbl_a2_95:
	li r0, 0x3
	b lbl_a2_94
	lbl_a2_91:
	li r0, 0x4
	lbl_a2_94:
	cmpwi r0, 0x1
	bne lbl_a2_88
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	lbl_a2_88:
	lfs f0, float_0p25_80419c7c(r2)
	lfs f2, 0x228(r31)
	fmuls f0, f0, f2
	fcmpo cr0, f4, f0
	ble lbl_a2_86
	lfs f0, 0x20c(r31)
	fcmpo cr0, f29, f0
	ble lbl_a2_96
	li r25, 0x1
	b lbl_a2_86
	lbl_a2_96:
	fneg f1, f29
	lfs f0, 0x218(r31)
	fcmpo cr0, f1, f0
	ble lbl_a2_97
	li r25, 0x1
	b lbl_a2_86
	lbl_a2_97:
	fcmpo cr0, f4, f2
	ble lbl_a2_98
	li r25, 0x1
	b lbl_a2_86
	lbl_a2_98:
	lfs f1, float_0_80419b9c(r2)
	fmr f3, f31
	fmr f4, f28
	fmr f2, f1
	bl angleABf
	fmr f0, f1
	fmr f1, f30
	fmr f2, f0
	bl compAngle
	lfs f2, float_0p5_80419ba0(r2)
	fabs f1, f1
	lfs f0, 0x22c(r31)
	fmuls f0, f2, f0
	fcmpo cr0, f1, f0
	ble lbl_a2_86
	li r25, 0x1
	lbl_a2_86:
	cmpwi r25, 0x0
	beq lbl_a2_67
	lwz r0, 0x140(r31)
	ori r0, r0, 0x2
	stw r0, 0x140(r31)
	b lbl_a2_41
	lbl_a2_67:
	cmpwi r26, 0x1
	beq lbl_a2_99
	cmpwi r26, 0x4
	bne lbl_a2_41
	lbl_a2_99:
	bl marioGetPtr
	lfs f1, 0x94(r3)
	lfs f0, 0x94(r31)
	lfs f2, 0x8c(r3)
	fsubs f27, f1, f0
	lfs f0, 0x8c(r31)
	lfs f3, 0x90(r3)
	fsubs f28, f2, f0
	lfs f2, 0x90(r31)
	fmuls f1, f27, f27
	lfs f0, float_0_80419b9c(r2)
	fsubs f29, f3, f2
	fmadds f30, f28, f28, f1
	fcmpo cr0, f30, f0
	addi r3, r31, 0x98
	addi r4, r31, 0x8c
	addi r5, r1, 0x94
	bl PSVECSubtract
	lfs f1, 0x144(r31)
	bl reviseAngle
	lfs f0, float_180_80419bec(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_100
	lfs f31, float_90_80419bd0(r2)
	b lbl_a2_101
	lbl_a2_100:
	lfs f31, float_270_80419be4(r2)
	lbl_a2_101:
	li r25, 0x1
	bl marioGetPtr
	mr r24, r3
	lwz r3, 0x0(r3)
	andis. r0, r3, 0x8200
	beq lbl_a2_102
	li r0, 0x0
	b lbl_a2_103
	lbl_a2_102:
	andi. r0, r3, 0xa
	beq lbl_a2_104
	li r0, 0x0
	b lbl_a2_103
	lbl_a2_104:
	lwz r3, gp(r13)
	lwz r0, 0x164(r3)
	cmpwi r0, 0x0
	beq lbl_a2_105
	li r0, 0x0
	b lbl_a2_103
	lbl_a2_105:
	bl seqGetSeq
	cmpwi r3, 0x2
	beq lbl_a2_106
	li r0, 0x0
	b lbl_a2_103
	lbl_a2_106:
	lhz r0, 0x2e(r24)
	cmplwi r0, 0x19
	bne lbl_a2_107
	li r0, 0x0
	b lbl_a2_103
	lbl_a2_107:
	bl vivianGetStatus
	cmpwi r3, 0x0
	beq lbl_a2_108
	bl vivianGetStatus
	cmpwi r3, 0x1
	beq lbl_a2_108
	li r0, 0x0
	b lbl_a2_103
	lbl_a2_108:
	li r0, 0x1
	lbl_a2_103:
	cmpwi r0, 0x0
	bne lbl_a2_109
	li r25, 0x0
	b lbl_a2_110
	lbl_a2_109:
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f30, f0
	ble lbl_a2_111
	frsqrte f1, f30
	lfd f3, 0x1c0(r30)
	lfd f2, 0x1c8(r30)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f30, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f30, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f30, f0, f2
	fmul f0, f1, f0
	fmul f30, f30, f0
	frsp f30, f30
	b lbl_a2_112
	lbl_a2_111:
	lfd f0, 0x1d0(r30)
	fcmpo cr0, f30, f0
	bge lbl_a2_113
	lis r3, __float_nan@ha
	lfs f30, __float_nan@l(r3)
	b lbl_a2_112
	lbl_a2_113:
	stfs f30, 0xc(r1)
	lis r0, 0x7f80
	lwz r4, 0xc(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_114
	bge lbl_a2_115
	cmpwi r3, 0x0
	beq lbl_a2_116
	b lbl_a2_115
	lbl_a2_114:
	clrlwi. r0, r4, 9
	beq lbl_a2_117
	li r0, 0x1
	b lbl_a2_118
	lbl_a2_117:
	li r0, 0x2
	b lbl_a2_118
	lbl_a2_116:
	clrlwi. r0, r4, 9
	beq lbl_a2_119
	li r0, 0x5
	b lbl_a2_118
	lbl_a2_119:
	li r0, 0x3
	b lbl_a2_118
	lbl_a2_115:
	li r0, 0x4
	lbl_a2_118:
	cmpwi r0, 0x1
	bne lbl_a2_112
	lis r3, __float_nan@ha
	lfs f30, __float_nan@l(r3)
	lbl_a2_112:
	lfs f0, float_0p25_80419c7c(r2)
	lfs f1, 0x220(r31)
	fmuls f0, f0, f1
	fcmpo cr0, f30, f0
	ble lbl_a2_120
	fcmpo cr0, f30, f1
	ble lbl_a2_121
	li r25, 0x0
	b lbl_a2_110
	lbl_a2_121:
	lfs f1, float_0_80419b9c(r2)
	fmr f3, f28
	fmr f4, f27
	fmr f2, f1
	bl angleABf
	fmr f0, f1
	fmr f1, f31
	fmr f2, f0
	bl compAngle
	lfs f2, float_0p5_80419ba0(r2)
	fabs f1, f1
	lfs f0, 0x224(r31)
	fmuls f0, f2, f0
	fcmpo cr0, f1, f0
	ble lbl_a2_120
	li r25, 0x0
	b lbl_a2_110
	lbl_a2_120:
	lfs f0, 0x20c(r31)
	fcmpo cr0, f29, f0
	ble lbl_a2_122
	li r25, 0x0
	b lbl_a2_110
	lbl_a2_122:
	fneg f1, f29
	lfs f0, 0x218(r31)
	fcmpo cr0, f1, f0
	ble lbl_a2_123
	li r25, 0x0
	b lbl_a2_110
	lbl_a2_123:
	cmpwi r26, 0x4
	bne lbl_a2_110
	lwz r0, 0x1f8(r31)
	cmpwi r0, 0x1
	bne lbl_a2_124
	lfs f1, 0x204(r31)
	lfs f0, 0x94(r31)
	lfs f2, 0x1fc(r31)
	fsubs f3, f1, f0
	lfs f1, 0x8c(r31)
	lfs f0, float_0_80419b9c(r2)
	fsubs f2, f2, f1
	fmuls f1, f3, f3
	fmadds f4, f2, f2, f1
	fcmpo cr0, f4, f0
	ble lbl_a2_125
	frsqrte f1, f4
	lfd f3, 0x1c0(r30)
	lfd f2, 0x1c8(r30)
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f1, f1, f0
	fmul f0, f1, f1
	fmul f1, f3, f1
	fnmsub f0, f4, f0, f2
	fmul f0, f1, f0
	fmul f4, f4, f0
	frsp f4, f4
	b lbl_a2_126
	lbl_a2_125:
	lfd f0, 0x1d0(r30)
	fcmpo cr0, f4, f0
	bge lbl_a2_127
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	b lbl_a2_126
	lbl_a2_127:
	stfs f4, 0x8(r1)
	lis r0, 0x7f80
	lwz r4, 0x8(r1)
	rlwinm r3, r4, 0, 1, 8
	cmpw r3, r0
	beq lbl_a2_128
	bge lbl_a2_129
	cmpwi r3, 0x0
	beq lbl_a2_130
	b lbl_a2_129
	lbl_a2_128:
	clrlwi. r0, r4, 9
	beq lbl_a2_131
	li r0, 0x1
	b lbl_a2_132
	lbl_a2_131:
	li r0, 0x2
	b lbl_a2_132
	lbl_a2_130:
	clrlwi. r0, r4, 9
	beq lbl_a2_133
	li r0, 0x5
	b lbl_a2_132
	lbl_a2_133:
	li r0, 0x3
	b lbl_a2_132
	lbl_a2_129:
	li r0, 0x4
	lbl_a2_132:
	cmpwi r0, 0x1
	bne lbl_a2_126
	lis r3, __float_nan@ha
	lfs f4, __float_nan@l(r3)
	lbl_a2_126:
	lfd f1, 0x260(r30)
	lfs f0, 0x214(r31)
	fmul f0, f1, f0
	fcmpo cr0, f4, f0
	ble lbl_a2_110
	li r25, 0x0
	b lbl_a2_110
	lbl_a2_124:
	lfs f1, float_0p75_80419bf4(r2)
	lfs f0, 0x214(r31)
	lfs f3, 0x1fc(r31)
	fmuls f2, f1, f0
	lfs f4, 0x8c(r31)
	fsubs f0, f3, f2
	fcmpo cr0, f4, f0
	blt lbl_a2_134
	fadds f0, f3, f2
	fcmpo cr0, f4, f0
	bgt lbl_a2_134
	lfs f0, 0x21c(r31)
	lfs f2, 0x204(r31)
	fmuls f1, f1, f0
	lfs f3, 0x94(r31)
	fsubs f0, f2, f1
	fcmpo cr0, f3, f0
	blt lbl_a2_134
	fadds f0, f2, f1
	fcmpo cr0, f3, f0
	ble lbl_a2_110
	lbl_a2_134:
	li r25, 0x0
	lbl_a2_110:
	cmpwi r25, 0x0
	beq lbl_a2_41
	lwz r0, 0x140(r31)
	ori r0, r0, 0x1
	stw r0, 0x140(r31)
	lbl_a2_41:
	mr r3, r31
	bl npcCheckInterrupt
	lbl_a2_40:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 20, 20
	bne lbl_a2_135
	li r3, 0x4
	bl camGetPtr
	addi r3, r3, 0x11c
	addi r4, r31, 0x8c
	addi r5, r1, 0xac
	bl PSMTXMultVec
	li r3, 0x4
	bl camGetPtr
	addi r4, r1, 0xac
	addi r3, r3, 0x15c
	mr r5, r4
	bl PSMTX44MultVec
	lfs f1, 0xb4(r1)
	lfs f0, float_neg1_80419bf8(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_136
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_136
	lfs f2, 0xac(r1)
	lfs f1, float_neg2_80419c80(r2)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne lbl_a2_136
	lfs f0, float_2_80419c5c(r2)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	bne lbl_a2_136
	lfs f2, 0xb0(r1)
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	bne lbl_a2_136
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	beq lbl_a2_137
	lbl_a2_136:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 25, 25
	beq lbl_a2_135
	lbl_a2_137:
	lbz r0, 0x114(r31)
	cmplwi r0, 0xff
	bne lbl_a2_138
	lbz r0, 0x115(r31)
	cmplwi r0, 0xff
	bne lbl_a2_138
	lbz r0, 0x116(r31)
	cmplwi r0, 0xff
	bne lbl_a2_138
	lbz r0, 0x117(r31)
	cmplwi r0, 0xff
	beq lbl_a2_139
	lbl_a2_138:
	lwz r3, 0x104(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lwz r0, 0x114(r31)
	addi r4, r1, 0x20
	stw r0, 0x20(r1)
	lwz r3, 0x104(r31)
	bl animPoseSetMaterialEvtColor
	b lbl_a2_140
	lbl_a2_139:
	lwz r3, 0x104(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOff
	lbl_a2_140:
	lfs f2, float_5000_80419c84(r2)
	lfs f1, 0xb4(r1)
	lfs f0, float_0_80419b9c(r2)
	fmadds f30, f2, f1, f2
	fcmpo cr0, f30, f0
	bge lbl_a2_141
	fmr f30, f0
	b lbl_a2_142
	lbl_a2_141:
	lfs f0, float_10000_80419c88(r2)
	fcmpo cr0, f30, f0
	ble lbl_a2_142
	fmr f30, f0
	lbl_a2_142:
	lwz r0, 0x0(r31)
	lfs f0, float_neg1_80419bf8(r2)
	rlwinm. r0, r0, 0, 24, 24
	fmuls f30, f30, f0
	bne lbl_a2_143
	lhz r0, 0x320(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq lbl_a2_144
	lwz r0, 0x1d4(r31)
	rlwinm. r0, r0, 0, 15, 15
	beq lbl_a2_143
	lbl_a2_144:
	lbz r0, 0x117(r31)
	cmplwi r0, 0xff
	beq lbl_a2_145
	lis r3, npcDisp_xlu@ha
	fmr f1, f30
	addi r5, r3, npcDisp_xlu@l
	lwz r3, 0x1f4(r31)
	mr r6, r31
	li r4, 0x2
	bl dispEntry
	b lbl_a2_146
	lbl_a2_145:
	lis r3, npcDisp@ha
	fmr f1, f30
	addi r5, r3, npcDisp@l
	lwz r3, 0x1f4(r31)
	mr r6, r31
	li r4, 0x0
	bl dispEntry
	lis r3, npcDisp@ha
	fmr f1, f30
	addi r5, r3, npcDisp@l
	lwz r3, 0x1f4(r31)
	mr r6, r31
	li r4, 0x1
	bl dispEntry
	lis r3, npcDisp@ha
	fmr f1, f30
	addi r5, r3, npcDisp@l
	lwz r3, 0x1f4(r31)
	mr r6, r31
	li r4, 0x2
	bl dispEntry
	lbl_a2_146:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 5, 5
	bne lbl_a2_147
	rlwinm. r0, r3, 0, 13, 13
	bne lbl_a2_148
	lwz r0, 0x28(r31)
	lwz r4, 0x8c(r31)
	lwz r3, 0x90(r31)
	cmplwi r0, 0x0
	lwz r0, 0x94(r31)
	stw r4, 0x88(r1)
	stw r3, 0x8c(r1)
	stw r0, 0x90(r1)
	beq lbl_a2_149
	lfs f1, 0x144(r31)
	bl reviseAngle
	lfs f0, float_180_80419bec(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_150
	lfs f1, float_90_80419bd0(r2)
	b lbl_a2_151
	lbl_a2_150:
	lfs f1, float_270_80419be4(r2)
	lbl_a2_151:
	bl sinfd
	lwz r3, 0x28(r31)
	lfs f0, 0xe0(r31)
	lfs f3, 0x30(r3)
	lfs f2, 0x88(r1)
	fmuls f5, f3, f0
	lfs f4, 0x34(r3)
	lfs f3, 0xe4(r31)
	lfs f0, 0x8c(r1)
	fmadds f5, f5, f1, f2
	lfs f2, 0x38(r3)
	fmadds f3, f4, f3, f0
	lfs f1, 0xe8(r31)
	lfs f0, 0x90(r1)
	stfs f5, 0x88(r1)
	fmadds f0, f2, f1, f0
	stfs f3, 0x8c(r1)
	stfs f0, 0x90(r1)
	lbl_a2_149:
	lfs f2, 0x14c(r31)
	lfs f1, float_3_80419c08(r2)
	lfs f0, 0xe0(r31)
	fdivs f4, f2, f1
	lfs f5, 0x154(r31)
	lfs f6, float_1p33_80419c8c(r2)
	lfs f1, 0x88(r1)
	lfs f2, 0x8c(r1)
	lfs f3, 0x90(r1)
	fmuls f0, f4, f0
	fmuls f0, f5, f0
	fmuls f4, f6, f0
	bl shadowEntry
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 12, 12
	beq lbl_a2_148
	li r4, 0x0
	bl shadowSetCollision
	b lbl_a2_148
	lbl_a2_147:
	lwz r3, 0x8c(r31)
	addi r4, r1, 0x3c
	lwz r0, 0x90(r31)
	addi r5, r1, 0x38
	lfs f4, float_0_80419b9c(r2)
	addi r6, r1, 0x34
	stw r3, 0x7c(r1)
	addi r7, r1, 0x30
	lfs f1, float_1_80419bb4(r2)
	fmr f6, f4
	stw r0, 0x80(r1)
	addi r8, r1, 0x2c
	lfs f3, float_100_80419c18(r2)
	addi r9, r1, 0x28
	lwz r0, 0x94(r31)
	lfs f0, 0x80(r1)
	addi r10, r1, 0x24
	stw r0, 0x84(r1)
	li r3, 0x0
	fadds f2, f1, f0
	lfs f1, 0x7c(r1)
	stfs f3, 0x30(r1)
	lfs f3, 0x84(r1)
	lfs f5, float_neg1_80419bf8(r2)
	bl hitCheckFilter
	cmplwi r3, 0x0
	beq lbl_a2_152
	lfs f0, 0x38(r1)
	stfs f0, 0x80(r1)
	lbl_a2_152:
	lwz r3, 0x104(r31)
	addi r4, r1, 0x7c
	bl animPoseVivianMain
	lfs f2, 0x14c(r31)
	lfs f1, float_3_80419c08(r2)
	lfs f0, 0xe0(r31)
	fdivs f4, f2, f1
	lfs f5, 0x154(r31)
	lfs f1, 0x8c(r31)
	lfs f2, 0x90(r31)
	lfs f3, 0x94(r31)
	fmuls f0, f4, f0
	fmuls f4, f5, f0
	bl shadowEntry
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 12, 12
	beq lbl_a2_148
	li r4, 0x0
	bl shadowSetCollision
	lbl_a2_148:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq lbl_a2_143
	lis r3, npcDisp_blur@ha
	fmr f1, f30
	addi r5, r3, npcDisp_blur@l
	lwz r3, 0x1f4(r31)
	mr r6, r31
	li r4, 0x2
	bl dispEntry
	lbl_a2_143:
	lwz r0, 0x110(r31)
	cmpwi r0, -0x1
	beq lbl_a2_135
	lbz r0, 0x117(r31)
	cmplwi r0, 0xff
	beq lbl_a2_153
	fmr f1, f30
	lis r3, npcDisp_offscreen_xlu@ha
	addi r5, r3, npcDisp_offscreen_xlu@l
	mr r6, r31
	li r3, 0x1
	li r4, 0x2
	bl dispEntry
	b lbl_a2_135
	lbl_a2_153:
	fmr f1, f30
	lis r3, npcDisp_offscreen@ha
	addi r5, r3, npcDisp_offscreen@l
	mr r6, r31
	li r3, 0x1
	li r4, 0x0
	bl dispEntry
	fmr f1, f30
	lis r3, npcDisp_offscreen@ha
	addi r5, r3, npcDisp_offscreen@l
	mr r6, r31
	li r3, 0x1
	li r4, 0x1
	bl dispEntry
	fmr f1, f30
	lis r3, npcDisp_offscreen@ha
	addi r5, r3, npcDisp_offscreen@l
	mr r6, r31
	li r3, 0x1
	li r4, 0x2
	bl dispEntry
	lbl_a2_135:
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0x98(r31)
	stw r0, 0x9c(r31)
	lwz r0, 0x94(r31)
	stw r0, 0xa0(r31)
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 23, 23
	beq lbl_a2_15
	lwz r0, npcMainCount(r13)
	clrlwi. r0, r0, 31
	bne lbl_a2_15
	lwz r3, 0xc8(r31)
	lwz r0, 0xcc(r31)
	stw r3, 0xd4(r31)
	stw r0, 0xd8(r31)
	lwz r0, 0xd0(r31)
	stw r0, 0xdc(r31)
	lwz r3, 0xbc(r31)
	lwz r0, 0xc0(r31)
	stw r3, 0xc8(r31)
	stw r0, 0xcc(r31)
	lwz r0, 0xc4(r31)
	stw r0, 0xd0(r31)
	lwz r3, 0xb0(r31)
	lwz r0, 0xb4(r31)
	stw r3, 0xbc(r31)
	stw r0, 0xc0(r31)
	lwz r0, 0xb8(r31)
	stw r0, 0xc4(r31)
	lwz r3, 0xa4(r31)
	lwz r0, 0xa8(r31)
	stw r3, 0xb0(r31)
	stw r0, 0xb4(r31)
	lwz r0, 0xac(r31)
	stw r0, 0xb8(r31)
	lwz r3, 0x8c(r31)
	lwz r0, 0x90(r31)
	stw r3, 0xa4(r31)
	stw r0, 0xa8(r31)
	lwz r0, 0x94(r31)
	stw r0, 0xac(r31)
	lbl_a2_15:
	lwz r0, 0x1d4(r31)
	rlwinm r0, r0, 0, 28, 26
	stw r0, 0x1d4(r31)
	lbl_a2_4:
	addi r29, r29, 0x1
	addi r31, r31, 0x340
	lbl_a2_2:
	cmpw r29, r28
	blt lbl_a2_3
	lwz r3, gp(r13)
	lwz r27, 0x168(r3)
	addi r24, r27, 0x550
	lwz r0, 0x550(r27)
	cmpwi r0, 0x0
	beq lbl_a2_154
	lwz r0, 0x8(r24)
	cmpwi r0, 0x2
	beq lbl_a2_155
	bge lbl_a2_154
	cmpwi r0, 0x1
	bge lbl_a2_156
	b lbl_a2_154
	lbl_a2_155:
	lwz r3, 0xc(r24)
	addi r0, r3, 0x1
	stw r0, 0xc(r24)
	lwz r4, 0xc(r24)
	cmpwi r4, 0x14
	bge lbl_a2_157
	lfs f1, float_neg600_80419c0c(r2)
	li r3, 0x5
	lfs f2, float_0_80419b9c(r2)
	li r5, 0x14
	bl intplGetValue
	stfs f1, 0x10(r24)
	b lbl_a2_158
	lbl_a2_157:
	cmpwi r4, 0x50
	bge lbl_a2_159
	lfs f0, float_0_80419b9c(r2)
	stfs f0, 0x10(r24)
	b lbl_a2_158
	lbl_a2_159:
	cmpwi r4, 0x64
	bge lbl_a2_160
	lfs f1, float_0_80419b9c(r2)
	subi r4, r4, 0x50
	lfs f2, float_600_80419c10(r2)
	li r3, 0x1
	li r5, 0x14
	bl intplGetValue
	stfs f1, 0x10(r24)
	b lbl_a2_158
	lbl_a2_160:
	li r0, 0x0
	stw r0, 0x4(r24)
	b lbl_a2_154
	lbl_a2_158:
	lfs f1, float_0_80419b9c(r2)
	lis r3, _fbatFirstAttackAnnouceDisp@ha
	addi r5, r3, _fbatFirstAttackAnnouceDisp@l
	mr r6, r24
	stfs f1, 0x14(r24)
	li r3, 0x9
	li r4, 0x2
	bl dispEntry
	b lbl_a2_154
	lbl_a2_156:
	lwz r3, 0xc(r24)
	addi r0, r3, 0x1
	stw r0, 0xc(r24)
	lwz r0, 0xc(r24)
	cmpwi r0, 0x3c
	ble lbl_a2_161
	li r0, 0x0
	stw r0, 0x4(r24)
	b lbl_a2_154
	lbl_a2_161:
	lfs f1, float_0_80419b9c(r2)
	lis r3, _fbatFirstAttackAnnouceDisp@ha
	addi r5, r3, _fbatFirstAttackAnnouceDisp@l
	mr r6, r24
	stfs f1, 0x10(r24)
	li r3, 0x9
	li r4, 0x2
	stfs f1, 0x14(r24)
	bl dispEntry
	lbl_a2_154:
	lha r0, 0x0(r27)
	cmpwi r0, 0x4
	beq lbl_a2_162
	bge lbl_a2_163
	cmpwi r0, 0x1
	beq lbl_a2_164
	bge lbl_a2_165
	b lbl_a2_162
	lbl_a2_163:
	cmpwi r0, 0x6
	beq lbl_a2_162
	bge lbl_a2_162
	b lbl_a2_166
	lbl_a2_164:
	bl fbatEncountCheck
	lwz r3, gp(r13)
	lwz r26, 0x168(r3)
	bl marioGetPtr
	lbz r0, 0x3c(r3)
	li r28, 0x0
	mr r25, r3
	cmpwi r0, 0x2
	mr r24, r28
	bne lbl_a2_167
	bl kpaJumpChk
	mr r28, r3
	lbl_a2_167:
	lbz r0, 0x3c(r25)
	cmpwi r0, 0x2
	bne lbl_a2_168
	bl kpaFireAttackCheck
	mr r24, r3
	lbl_a2_168:
	cmpwi r28, 0x0
	beq lbl_a2_169
	lwz r3, 0x57c(r26)
	cmpwi r3, 0x0
	ble lbl_a2_170
	lwz r0, 0x578(r26)
	cmpwi r0, 0x2
	blt lbl_a2_170
	lwz r5, 0x8c(r25)
	addi r4, r1, 0x40
	lwz r0, 0x90(r25)
	lfs f0, float_60_80419ba4(r2)
	stw r0, 0x44(r1)
	lfs f1, 0x44(r1)
	stw r5, 0x40(r1)
	fadds f0, f1, f0
	lwz r0, 0x94(r25)
	stw r0, 0x48(r1)
	stfs f0, 0x44(r1)
	bl kpaAddScorePos
	lbl_a2_170:
	li r0, 0x0
	stw r0, 0x578(r26)
	stw r0, 0x57c(r26)
	lbl_a2_169:
	cmpwi r24, 0x0
	bne lbl_a2_162
	li r0, 0x0
	stw r0, 0x574(r26)
	b lbl_a2_162
	lbl_a2_165:
	bl fbatTalkMode
	b lbl_a2_162
	lbl_a2_166:
	bl fbatBattleMode
	lbl_a2_162:
	li r0, 0x0
	stb r0, 0x54d(r27)
	psq_l f31, 0x128(r1), 0, 0
	lfd f31, 0x120(r1)
	psq_l f30, 0x118(r1), 0, 0
	lfd f30, 0x110(r1)
	psq_l f29, 0x108(r1), 0, 0
	lfd f29, 0x100(r1)
	psq_l f28, 0xf8(r1), 0, 0
	lfd f28, 0xf0(r1)
	psq_l f27, 0xe8(r1), 0, 0
	lfd f27, 0xe0(r1)
	lmw r24, 0xc0(r1)
	lwz r0, 0x134(r1)
	mtlr r0
	addi r1, r1, 0x130
	blr
}

asm void npcDeleteGroup(NpcEntry* entry) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r0, 0x32c(r3)
	cmplwi r0, 0x0
	beq lbl_a2_1
	mr r3, r0
	b lbl_a2_1
	lbl_a2_2:
	mr r3, r0
	lbl_a2_1:
	lwz r0, 0x324(r3)
	cmplwi r0, 0x0
	bne lbl_a2_2
	bl _npcDeleteGroup
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void _npcDeleteGroup(NpcEntry* entry) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	lwz r31, 0x328(r3)
	cmplwi r31, 0x0
	beq lbl_a2_1
	lwz r3, 0x328(r31)
	cmplwi r3, 0x0
	beq lbl_a2_2
	bl _npcDeleteGroup
	lbl_a2_2:
	li r29, 0x0
	mr r30, r31
	mr r28, r29
	lbl_a2_3:
	lwz r3, 0x330(r30)
	cmplwi r3, 0x0
	beq lbl_a2_4
	bl npcDelete
	stw r28, 0x330(r30)
	lbl_a2_4:
	addi r29, r29, 0x1
	addi r30, r30, 0x4
	cmpwi r29, 0x4
	blt lbl_a2_3
	mr r3, r31
	bl npcDelete
	lbl_a2_1:
	la r29, work(r13)
	mr r31, r27
	li r28, 0x0
	addi r29, r29, 0x14
	lbl_a2_5:
	lwz r30, 0x330(r31)
	cmplwi r30, 0x0
	beq lbl_a2_6
	lwz r3, 0x330(r30)
	li r0, 0x0
	cmplwi r3, 0x0
	beq lbl_a2_7
	stw r0, 0x32c(r3)
	lbl_a2_7:
	stw r0, 0x330(r30)
	lwz r3, 0x334(r30)
	cmplwi r3, 0x0
	beq lbl_a2_8
	stw r0, 0x32c(r3)
	lbl_a2_8:
	stw r0, 0x334(r30)
	addi r4, r30, 0x8
	lwz r3, 0x338(r30)
	cmplwi r3, 0x0
	beq lbl_a2_9
	stw r0, 0x32c(r3)
	lbl_a2_9:
	stw r0, 0x330(r4)
	lwz r3, 0x334(r4)
	cmplwi r3, 0x0
	beq lbl_a2_10
	stw r0, 0x32c(r3)
	lbl_a2_10:
	stw r0, 0x334(r4)
	lwz r3, 0x324(r30)
	cmplwi r3, 0x0
	beq lbl_a2_11
	lwz r0, 0x328(r30)
	cmplwi r0, 0x0
	beq lbl_a2_12
	stw r0, 0x328(r3)
	lwz r0, 0x324(r30)
	lwz r3, 0x328(r30)
	stw r0, 0x324(r3)
	b lbl_a2_13
	lbl_a2_12:
	li r0, 0x0
	stw r0, 0x328(r3)
	b lbl_a2_13
	lbl_a2_11:
	lwz r3, 0x328(r30)
	cmplwi r3, 0x0
	beq lbl_a2_13
	li r0, 0x0
	stw r0, 0x324(r3)
	lbl_a2_13:
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r30)
	lwz r3, 0x104(r30)
	cmpwi r3, 0x0
	blt lbl_a2_14
	bl animPoseRelease
	lbl_a2_14:
	li r0, -0x1
	stw r0, 0x104(r30)
	lwz r0, 0x0(r30)
	clrrwi r0, r0, 1
	stw r0, 0x0(r30)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_15
	mr r4, r29
	b lbl_a2_16
	lbl_a2_15:
	la r4, work(r13)
	lbl_a2_16:
	lwz r3, 0x0(r4)
	li r0, 0x0
	subi r3, r3, 0x1
	stw r3, 0x0(r4)
	stw r0, 0x330(r31)
	lbl_a2_6:
	addi r28, r28, 0x1
	addi r31, r31, 0x4
	cmpwi r28, 0x4
	blt lbl_a2_5
	lwz r3, 0x330(r27)
	li r0, 0x0
	cmplwi r3, 0x0
	beq lbl_a2_17
	stw r0, 0x32c(r3)
	lbl_a2_17:
	stw r0, 0x330(r27)
	lwz r3, 0x334(r27)
	cmplwi r3, 0x0
	beq lbl_a2_18
	stw r0, 0x32c(r3)
	lbl_a2_18:
	stw r0, 0x334(r27)
	addi r4, r27, 0x8
	lwz r3, 0x338(r27)
	cmplwi r3, 0x0
	beq lbl_a2_19
	stw r0, 0x32c(r3)
	lbl_a2_19:
	stw r0, 0x330(r4)
	lwz r3, 0x334(r4)
	cmplwi r3, 0x0
	beq lbl_a2_20
	stw r0, 0x32c(r3)
	lbl_a2_20:
	stw r0, 0x334(r4)
	lwz r3, 0x324(r27)
	cmplwi r3, 0x0
	beq lbl_a2_21
	lwz r0, 0x328(r27)
	cmplwi r0, 0x0
	beq lbl_a2_22
	stw r0, 0x328(r3)
	lwz r0, 0x324(r27)
	lwz r3, 0x328(r27)
	stw r0, 0x324(r3)
	b lbl_a2_23
	lbl_a2_22:
	li r0, 0x0
	stw r0, 0x328(r3)
	b lbl_a2_23
	lbl_a2_21:
	lwz r3, 0x328(r27)
	cmplwi r3, 0x0
	beq lbl_a2_23
	li r0, 0x0
	stw r0, 0x324(r3)
	lbl_a2_23:
	lwz r0, 0x0(r27)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r27)
	lwz r3, 0x104(r27)
	cmpwi r3, 0x0
	blt lbl_a2_24
	bl animPoseRelease
	lbl_a2_24:
	li r0, -0x1
	stw r0, 0x104(r27)
	lwz r0, 0x0(r27)
	clrrwi r0, r0, 1
	stw r0, 0x0(r27)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_25
	b lbl_a2_26
	lbl_a2_25:
	la r29, work(r13)
	lbl_a2_26:
	lwz r3, 0x0(r29)
	subi r0, r3, 0x1
	stw r0, 0x0(r29)
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcDelete(NpcEntry* entry) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	li r0, 0x0
	stw r31, 0xc(r1)
	mr r31, r3
	lwz r4, 0x330(r3)
	cmplwi r4, 0x0
	beq lbl_a2_1
	stw r0, 0x32c(r4)
	lbl_a2_1:
	stw r0, 0x330(r31)
	lwz r4, 0x334(r31)
	cmplwi r4, 0x0
	beq lbl_a2_2
	stw r0, 0x32c(r4)
	lbl_a2_2:
	stw r0, 0x334(r31)
	addi r3, r31, 0x8
	lwz r4, 0x338(r31)
	cmplwi r4, 0x0
	beq lbl_a2_3
	stw r0, 0x32c(r4)
	lbl_a2_3:
	stw r0, 0x330(r3)
	lwz r4, 0x334(r3)
	cmplwi r4, 0x0
	beq lbl_a2_4
	stw r0, 0x32c(r4)
	lbl_a2_4:
	stw r0, 0x334(r3)
	lwz r3, 0x324(r31)
	cmplwi r3, 0x0
	beq lbl_a2_5
	lwz r0, 0x328(r31)
	cmplwi r0, 0x0
	beq lbl_a2_6
	stw r0, 0x328(r3)
	lwz r0, 0x324(r31)
	lwz r3, 0x328(r31)
	stw r0, 0x324(r3)
	b lbl_a2_7
	lbl_a2_6:
	li r0, 0x0
	stw r0, 0x328(r3)
	b lbl_a2_7
	lbl_a2_5:
	lwz r3, 0x328(r31)
	cmplwi r3, 0x0
	beq lbl_a2_7
	li r0, 0x0
	stw r0, 0x324(r3)
	lbl_a2_7:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r31)
	lwz r3, 0x104(r31)
	cmpwi r3, 0x0
	blt lbl_a2_8
	bl animPoseRelease
	lbl_a2_8:
	li r0, -0x1
	la r4, work(r13)
	stw r0, 0x104(r31)
	lwz r0, 0x0(r31)
	clrrwi r0, r0, 1
	stw r0, 0x0(r31)
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq lbl_a2_9
	addi r4, r4, 0x14
	lbl_a2_9:
	lwz r3, 0x0(r4)
	subi r0, r3, 0x1
	stw r0, 0x0(r4)
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm NpcTribeInfo* npcGetTribe(const char* tribeName) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r4, npcTribe@ha
	stw r0, 0x14(r1)
	addi r0, r4, npcTribe@l
	stw r31, 0xc(r1)
	mr r31, r0
	stw r30, 0x8(r1)
	mr r30, r3
	b lbl_a2_1
	lbl_a2_2:
	mr r4, r30
	bl strcmp
	cmpwi r3, 0x0
	bne lbl_a2_3
	mr r3, r31
	b lbl_a2_4
	lbl_a2_3:
	addi r31, r31, 0x54
	lbl_a2_1:
	lwz r3, 0x0(r31)
	cmplwi r3, 0x0
	bne lbl_a2_2
	li r3, 0x0
	lbl_a2_4:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 npcEntry(const char* a1, const char* animName) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	lis r6, vec3_802c2f78@ha
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mr r25, r3
	mr r27, r4
	addi r30, r6, vec3_802c2f78@l
	la r31, work(r13)
	lwz r5, gp(r13)
	lwz r0, 0x14(r5)
	cmpwi r0, 0x0
	beq lbl_a2_1
	addi r31, r31, 0x14
	lbl_a2_1:
	lwz r26, 0x4(r31)
	li r28, 0x0
	lwz r29, 0xc(r31)
	b lbl_a2_2
	lbl_a2_3:
	lwz r0, 0x0(r29)
	clrlwi. r0, r0, 31
	beq lbl_a2_4
	mr r4, r25
	addi r3, r29, 0x8
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_5
	lbl_a2_4:
	addi r28, r28, 0x1
	addi r29, r29, 0x340
	lbl_a2_2:
	cmpw r28, r26
	blt lbl_a2_3
	lbl_a2_5:
	lwz r28, 0xc(r31)
	li r29, 0x0
	mtctr r26
	cmpwi r26, 0x0
	ble lbl_a2_6
	lbl_a2_7:
	lwz r0, 0x0(r28)
	clrlwi. r0, r0, 31
	beq lbl_a2_6
	addi r29, r29, 0x1
	addi r28, r28, 0x340
	bdnz lbl_a2_7
	lbl_a2_6:
	mr r3, r28
	li r4, 0x0
	li r5, 0x340
	bl memset
	li r0, 0x3
	mr r4, r25
	stw r0, 0x0(r28)
	addi r3, r28, 0x8
	bl strcpy
	lwz r4, gp(r13)
	mr r3, r27
	lwz r4, 0x14(r4)
	neg r0, r4
	or r0, r0, r4
	srwi r4, r0, 31
	bl animPoseEntry
	stw r3, 0x104(r28)
	lwz r0, 0x104(r28)
	cmpwi r0, -0x2
	bne lbl_a2_8
	lwz r4, gp(r13)
	la r3, str_80419C90(r2)
	lwz r4, 0x14(r4)
	neg r0, r4
	or r0, r0, r4
	srwi r4, r0, 31
	bl animPoseEntry
	stw r3, 0x104(r28)
	lbl_a2_8:
	lwz r3, 0x104(r28)
	bl animPosePeraOn
	lwz r3, 0x0(r30)
	lwz r0, 0x4(r30)
	stw r3, 0x8c(r28)
	stw r0, 0x90(r28)
	lwz r0, 0x8(r30)
	stw r0, 0x94(r28)
	lwz r3, 0x8c(r28)
	lwz r0, 0x90(r28)
	stw r3, 0x98(r28)
	stw r0, 0x9c(r28)
	lwz r0, 0x94(r28)
	stw r0, 0xa0(r28)
	lwz r3, 0x104(r28)
	bl animPoseGetHeight
	stfs f1, 0x14c(r28)
	lwz r3, 0x104(r28)
	bl animPoseGetRadius
	stfs f1, 0x150(r28)
	li r7, 0x0
	lfs f1, float_1_80419bb4(r2)
	la r5, str_80419C98(r2)
	lwz r8, 0xc(r30)
	li r4, -0x1
	lwz r6, 0x10(r30)
	li r3, 0x4
	lfs f0, float_0_80419b9c(r2)
	li r0, 0x1
	stw r8, 0xe0(r28)
	stw r6, 0xe4(r28)
	lwz r6, 0x14(r30)
	stw r6, 0xe8(r28)
	stfs f1, 0x154(r28)
	stw r7, 0x108(r28)
	stw r5, 0x10c(r28)
	lwz r6, gp(r13)
	lwz r5, 0x38(r6)
	lwz r6, 0x3c(r6)
	stw r6, 0x19c(r28)
	stw r5, 0x198(r28)
	stw r7, 0x18c(r28)
	stw r7, 0x188(r28)
	stfs f1, 0x1cc(r28)
	stfs f0, 0x1d0(r28)
	stfs f1, 0x1c8(r28)
	stw r4, 0x110(r28)
	lwz r4, dat_80419b8c(r2)
	stw r4, 0x114(r28)
	stw r3, 0x1f4(r28)
	stw r7, 0x2f8(r28)
	stb r0, 0x317(r28)
	lwz r3, 0x104(r28)
	bl animPoseGetVivianType
	cmpwi r3, 0x0
	beq lbl_a2_9
	lwz r0, 0x0(r28)
	oris r0, r0, 0x400
	stw r0, 0x0(r28)
	lbl_a2_9:
	mr r3, r27
	addi r4, r30, 0x268
	bl strcmp
	cmpwi r3, 0x0
	bne lbl_a2_10
	lwz r0, 0x0(r28)
	oris r0, r0, 0x80
	stw r0, 0x0(r28)
	lbl_a2_10:
	lwz r3, 0x104(r28)
	li r4, 0x2
	bl animPoseSetMaterialLightFlagOn
	lwz r4, 0x0(r31)
	mr r3, r29
	addi r0, r4, 0x1
	stw r0, 0x0(r31)
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 npcGetReactionOfLivingBody(BOOL inBattle) {
	nofralloc
	cmpwi r3, 0x0
	la r3, work(r13)
	beq lbl_a2_1
	addi r3, r3, 0x14
	lbl_a2_1:
	lwz r3, 0x0(r3)
	blr
}

asm void npcReset(BOOL inBattle) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	la r31, work(r13)
	stw r30, 0x8(r1)
	mr. r30, r3
	beq lbl_a2_1
	addi r31, r31, 0x14
	lbl_a2_1:
	lwz r0, 0x4(r31)
	li r4, 0x0
	lwz r3, 0xc(r31)
	mulli r5, r0, 0x340
	bl memset
	li r0, 0x0
	cmpwi r30, 0x0
	stw r0, 0x0(r31)
	bne lbl_a2_2
	lwz r3, gp(r13)
	lwz r3, 0x168(r3)
	sth r0, 0x0(r3)
	lbl_a2_2:
	li r0, 0x0
	stw r0, npcMainCount(r13)
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void npcInit(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	li r3, 0x0
	stw r0, 0x14(r1)
	li r0, 0x24
	mulli r4, r0, 0x340
	stw r31, 0xc(r1)
	la r31, work(r13)
	stw r0, 0x4(r31)
	bl __memAlloc
	lwz r0, 0x4(r31)
	la r4, work(r13)
	stw r3, 0xc(r4)
	li r4, 0x0
	mulli r5, r0, 0x340
	bl memset
	lwz r0, 0x4(r31)
	li r3, 0x0
	mulli r4, r0, 0x94
	bl __memAlloc
	li r0, 0x10
	la r31, work(r13)
	mulli r4, r0, 0x340
	stw r3, release_wp(r13)
	li r3, 0x0
	stw r0, 0x18(r31)
	bl __memAlloc
	lwz r0, 0x18(r31)
	li r4, 0x0
	stw r3, 0x20(r31)
	mulli r5, r0, 0x340
	bl memset
	li r3, 0x0
	li r4, 0x580
	bl __memAlloc
	lwz r6, gp(r13)
	mr r31, r3
	li r4, 0x0
	li r5, 0x580
	stw r31, 0x168(r6)
	lwz r3, gp(r13)
	lwz r3, 0x168(r3)
	bl memset
	li r0, 0x0
	sth r0, 0x0(r31)
	stw r0, npcMainCount(r13)
	lwz r31, 0xc(r1)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void npcDisp_blur(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stfd f30, 0x60(r1)
	psq_st f30, 0x68(r1), 0, 0
	stfd f29, 0x50(r1)
	psq_st f29, 0x58(r1), 0, 0
	stw r31, 0x4c(r1)
	stw r30, 0x48(r1)
	stw r29, 0x44(r1)
	stw r28, 0x40(r1)
	lfs f0, 0x144(r4)
	mr r29, r3
	mr r30, r4
	fneg f1, f0
	bl reviseAngle
	fmr f31, f1
	lwz r3, 0x104(r30)
	bl animPoseGetMaterialFlag
	mr r0, r3
	mr r3, r29
	mr r28, r0
	bl camGetPtr
	lfs f2, 0x114(r3)
	lfs f1, float_6p2832_80419c38(r2)
	lfs f0, float_360_80419be0(r2)
	fmuls f2, f1, f2
	lfs f1, float_3p1416_80419c44(r2)
	lfs f4, float_0p00761_80419c3c(r2)
	lfs f3, float_0p16605_80419c40(r2)
	fdivs f5, f2, f0
	lfs f2, float_1_80419bb4(r2)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne lbl_a2_1
	lfs f1, float_1p5708_80419c48(r2)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne lbl_a2_2
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b lbl_a2_3
	lbl_a2_2:
	fsubs f0, f5, f1
	fsubs f5, f1, f0
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	b lbl_a2_3
	lbl_a2_1:
	lfs f0, float_4p7124_80419c4c(r2)
	fcmpo cr0, f5, f0
	bge lbl_a2_4
	fsubs f5, f5, f1
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	fneg f4, f4
	b lbl_a2_3
	lbl_a2_4:
	fsubs f0, f5, f0
	lfs f1, float_1p5708_80419c48(r2)
	fsubs f5, f1, f0
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fmuls f4, f4, f5
	fneg f4, f4
	lbl_a2_3:
	lfs f0, float_2_80419c5c(r2)
	mr r3, r29
	fmuls f30, f0, f4
	bl camGetPtr
	lfs f2, 0x114(r3)
	lfs f1, float_6p2832_80419c38(r2)
	lfs f0, float_360_80419be0(r2)
	fmuls f2, f1, f2
	lfs f1, float_3p1416_80419c44(r2)
	lfs f4, float_0p03705_80419c50(r2)
	lfs f3, float_0p4967_80419c54(r2)
	fdivs f5, f2, f0
	lfs f2, float_1_80419bb4(r2)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne lbl_a2_5
	lfs f1, float_1p5708_80419c48(r2)
	fcmpo cr0, f5, f1
	cror eq, lt, eq
	bne lbl_a2_6
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	b lbl_a2_7
	lbl_a2_6:
	fsubs f0, f5, f1
	fsubs f5, f1, f0
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b lbl_a2_7
	lbl_a2_5:
	lfs f0, float_4p7124_80419c4c(r2)
	fcmpo cr0, f5, f0
	bge lbl_a2_8
	fsubs f5, f5, f1
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	fneg f4, f4
	b lbl_a2_7
	lbl_a2_8:
	fsubs f0, f5, f0
	lfs f1, float_1p5708_80419c48(r2)
	fsubs f5, f1, f0
	fmuls f0, f5, f5
	fmsubs f4, f4, f0, f3
	fmadds f4, f4, f0, f2
	lbl_a2_7:
	fneg f0, f4
	lfs f1, float_2_80419c5c(r2)
	lwz r3, 0x104(r30)
	fmuls f29, f1, f0
	bl animPoseMain
	li r29, 0x4
	li r31, 0x64
	lbl_a2_9:
	mr r3, r30
	mr r5, r29
	addi r4, r1, 0x10
	bl mtx_setup
	fmr f1, f30
	addi r3, r1, 0x10
	fmr f3, f29
	lfs f2, float_0_80419b9c(r2)
	mr r4, r3
	bl PSMTXTransApply
	lwz r3, 0x104(r30)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lwz r3, dat_80419b88(r2)
	subfic r0, r31, 0x80
	addi r4, r1, 0xc
	stw r3, 0x8(r1)
	stb r0, 0xb(r1)
	lwz r0, 0x8(r1)
	stw r0, 0xc(r1)
	lwz r3, 0x104(r30)
	bl animPoseSetMaterialEvtColor
	fmr f1, f31
	lwz r3, 0x104(r30)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x10
	li r5, 0x1
	bl animPoseDrawMtx
	fmr f1, f31
	lwz r3, 0x104(r30)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x10
	li r5, 0x2
	bl animPoseDrawMtx
	fmr f1, f31
	lwz r3, 0x104(r30)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x10
	li r5, 0x3
	bl animPoseDrawMtx
	subic. r29, r29, 0x1
	subi r31, r31, 0x19
	bgt lbl_a2_9
	lwz r3, 0x104(r30)
	li r4, 0x40
	bl animPoseSetMaterialFlagOff
	lwz r3, 0x104(r30)
	mr r4, r28
	bl animPoseSetMaterialFlagOn
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	lwz r31, 0x4c(r1)
	lwz r30, 0x48(r1)
	lwz r29, 0x44(r1)
	lwz r0, 0x84(r1)
	lwz r28, 0x40(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm void npcDisp_offscreen(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stw r31, 0x5c(r1)
	stw r30, 0x58(r1)
	stw r29, 0x54(r1)
	stw r28, 0x50(r1)
	mr r31, r4
	bl sysWaitDrawSync
	bl GXClearBoundingBox
	lfs f0, 0x144(r31)
	fneg f1, f0
	bl reviseAngle
	fmr f31, f1
	mr r3, r31
	addi r4, r1, 0x18
	li r5, -0x1
	bl mtx_setup
	bl dispGetCurWork
	lbz r0, 0x1(r3)
	cmpwi r0, 0x1
	beq lbl_a2_1
	bge lbl_a2_2
	cmpwi r0, 0x0
	bge lbl_a2_3
	b lbl_a2_4
	lbl_a2_2:
	cmpwi r0, 0x3
	bge lbl_a2_4
	b lbl_a2_5
	lbl_a2_3:
	lwz r0, 0x1d4(r31)
	lwz r3, 0x114(r31)
	rlwinm. r0, r0, 0, 9, 9
	stw r3, 0x10(r1)
	beq lbl_a2_6
	lbz r5, 0x10(r1)
	addi r4, r1, 0x14
	lbz r6, 0x11(r1)
	srwi r0, r5, 31
	lbz r3, 0x12(r1)
	add r0, r0, r5
	srwi r5, r6, 31
	srawi r7, r0, 1
	srwi r0, r3, 31
	add r5, r5, r6
	srawi r5, r5, 1
	stb r7, 0x10(r1)
	add r0, r0, r3
	srawi r0, r0, 1
	stb r5, 0x11(r1)
	stb r0, 0x12(r1)
	lwz r0, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r3, 0x104(r31)
	bl animPoseSetMaterialEvtColor
	lwz r3, 0x104(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lbl_a2_6:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 8, 8
	beq lbl_a2_7
	lwz r3, 0x104(r31)
	bl animPoseGetCurrentAnim
	lwz r3, 0x104(r31)
	bl animPoseGetAnimPosePtr
	mr r30, r3
	lwz r3, 0x104(r31)
	bl animPoseGetCurrentAnim
	mr r29, r3
	li r3, 0x4
	bl camGetPtr
	lfs f3, 0x18(r3)
	lfs f2, 0xc(r3)
	lfs f1, 0x20(r3)
	lfs f0, 0x14(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fneg f1, f2
	fneg f2, f0
	bl atan2
	frsp f1, f1
	lfs f0, float_rad2deg_80419bdc(r2)
	fmuls f1, f0, f1
	bl reviseAngle
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_8
	lfs f0, float_360_80419be0(r2)
	fadds f1, f1, f0
	lbl_a2_8:
	lfs f0, 0x74(r30)
	fsubs f1, f1, f0
	bl reviseAngle
	lfs f0, float_90_80419bd0(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_9
	lfs f0, float_270_80419be4(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	beq lbl_a2_10
	lbl_a2_9:
	lfs f0, float_neg90_80419bd8(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_11
	lfs f0, float_neg270_80419be8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne lbl_a2_11
	lbl_a2_10:
	lis r3, luigi_pose@ha
	li r30, 0x0
	addi r28, r3, luigi_pose@l
	lbl_a2_12:
	lwz r3, 0x0(r28)
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_13
	addi r30, r30, 0x1
	addi r28, r28, 0x8
	cmplwi r30, 0xe
	blt lbl_a2_12
	lbl_a2_13:
	cmplwi r30, 0xe
	bge lbl_a2_7
	lis r3, luigi_pose@ha
	slwi r0, r30, 3
	addi r4, r3, luigi_pose@l
	lwz r3, 0x104(r31)
	add r4, r4, r0
	li r5, 0x0
	lwz r4, 0x4(r4)
	bl animPoseSetAnim
	b lbl_a2_7
	lbl_a2_11:
	lis r3, luigi_pose@ha
	li r30, 0x0
	addi r28, r3, luigi_pose@l
	lbl_a2_14:
	lwz r3, 0x4(r28)
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_15
	addi r30, r30, 0x1
	addi r28, r28, 0x8
	cmplwi r30, 0xe
	blt lbl_a2_14
	lbl_a2_15:
	cmplwi r30, 0xe
	bge lbl_a2_7
	lis r3, luigi_pose@ha
	slwi r0, r30, 3
	addi r4, r3, luigi_pose@l
	lwz r3, 0x104(r31)
	lwzx r4, r4, r0
	li r5, 0x0
	bl animPoseSetAnim
	lbl_a2_7:
	lwz r3, 0x104(r31)
	bl animPoseMain
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x18
	li r5, 0x1
	bl animPoseDrawMtx
	b lbl_a2_4
	lbl_a2_1:
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x18
	li r5, 0x2
	bl animPoseDrawMtx
	b lbl_a2_4
	lbl_a2_5:
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x18
	li r5, 0x3
	bl animPoseDrawMtx
	lbl_a2_4:
	bl sysWaitDrawSync
	addi r3, r1, 0xe
	addi r4, r1, 0xc
	addi r5, r1, 0xa
	addi r6, r1, 0x8
	bl GXReadBoundingBox
	lwz r3, 0x110(r31)
	lhz r4, 0xe(r1)
	lhz r5, 0xc(r1)
	lhz r6, 0xa(r1)
	lhz r7, 0x8(r1)
	bl offscreenAddBoundingBox
	psq_l f31, 0x68(r1), 0, 0
	lwz r0, 0x74(r1)
	lfd f31, 0x60(r1)
	lwz r31, 0x5c(r1)
	lwz r30, 0x58(r1)
	lwz r29, 0x54(r1)
	lwz r28, 0x50(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void npcDisp_offscreen_xlu(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stw r31, 0x5c(r1)
	stw r30, 0x58(r1)
	stw r29, 0x54(r1)
	stw r28, 0x50(r1)
	mr r31, r4
	bl sysWaitDrawSync
	bl GXClearBoundingBox
	lfs f0, 0x144(r31)
	fneg f1, f0
	bl reviseAngle
	fmr f31, f1
	mr r3, r31
	addi r4, r1, 0x18
	li r5, -0x1
	bl mtx_setup
	lwz r0, 0x1d4(r31)
	lwz r3, 0x114(r31)
	rlwinm. r0, r0, 0, 9, 9
	stw r3, 0x10(r1)
	beq lbl_a2_1
	lbz r5, 0x10(r1)
	addi r4, r1, 0x14
	lbz r6, 0x11(r1)
	srwi r0, r5, 31
	lbz r3, 0x12(r1)
	add r0, r0, r5
	srwi r5, r6, 31
	srawi r7, r0, 1
	srwi r0, r3, 31
	add r5, r5, r6
	srawi r5, r5, 1
	stb r7, 0x10(r1)
	add r0, r0, r3
	srawi r0, r0, 1
	stb r5, 0x11(r1)
	stb r0, 0x12(r1)
	lwz r0, 0x10(r1)
	stw r0, 0x14(r1)
	lwz r3, 0x104(r31)
	bl animPoseSetMaterialEvtColor
	lwz r3, 0x104(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lbl_a2_1:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 8, 8
	beq lbl_a2_2
	lwz r3, 0x104(r31)
	bl animPoseGetCurrentAnim
	lwz r3, 0x104(r31)
	bl animPoseGetAnimPosePtr
	mr r30, r3
	lwz r3, 0x104(r31)
	bl animPoseGetCurrentAnim
	mr r29, r3
	li r3, 0x4
	bl camGetPtr
	lfs f3, 0x18(r3)
	lfs f2, 0xc(r3)
	lfs f1, 0x20(r3)
	lfs f0, 0x14(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fneg f1, f2
	fneg f2, f0
	bl atan2
	frsp f1, f1
	lfs f0, float_rad2deg_80419bdc(r2)
	fmuls f1, f0, f1
	bl reviseAngle
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_3
	lfs f0, float_360_80419be0(r2)
	fadds f1, f1, f0
	lbl_a2_3:
	lfs f0, 0x74(r30)
	fsubs f1, f1, f0
	bl reviseAngle
	lfs f0, float_90_80419bd0(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_4
	lfs f0, float_270_80419be4(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	beq lbl_a2_5
	lbl_a2_4:
	lfs f0, float_neg90_80419bd8(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_6
	lfs f0, float_neg270_80419be8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne lbl_a2_6
	lbl_a2_5:
	lis r3, luigi_pose@ha
	li r30, 0x0
	addi r28, r3, luigi_pose@l
	lbl_a2_7:
	lwz r3, 0x0(r28)
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_8
	addi r30, r30, 0x1
	addi r28, r28, 0x8
	cmplwi r30, 0xe
	blt lbl_a2_7
	lbl_a2_8:
	cmplwi r30, 0xe
	bge lbl_a2_2
	lis r3, luigi_pose@ha
	slwi r0, r30, 3
	addi r4, r3, luigi_pose@l
	lwz r3, 0x104(r31)
	add r4, r4, r0
	li r5, 0x0
	lwz r4, 0x4(r4)
	bl animPoseSetAnim
	b lbl_a2_2
	lbl_a2_6:
	lis r3, luigi_pose@ha
	li r30, 0x0
	addi r28, r3, luigi_pose@l
	lbl_a2_9:
	lwz r3, 0x4(r28)
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_10
	addi r30, r30, 0x1
	addi r28, r28, 0x8
	cmplwi r30, 0xe
	blt lbl_a2_9
	lbl_a2_10:
	cmplwi r30, 0xe
	bge lbl_a2_2
	lis r3, luigi_pose@ha
	slwi r0, r30, 3
	addi r4, r3, luigi_pose@l
	lwz r3, 0x104(r31)
	lwzx r4, r4, r0
	li r5, 0x0
	bl animPoseSetAnim
	lbl_a2_2:
	lwz r3, 0x104(r31)
	bl animPoseMain
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x18
	li r5, 0x1
	bl animPoseDrawMtx
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x18
	li r5, 0x2
	bl animPoseDrawMtx
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x18
	li r5, 0x3
	bl animPoseDrawMtx
	bl sysWaitDrawSync
	addi r3, r1, 0xe
	addi r4, r1, 0xc
	addi r5, r1, 0xa
	addi r6, r1, 0x8
	bl GXReadBoundingBox
	lwz r3, 0x110(r31)
	lhz r4, 0xe(r1)
	lhz r5, 0xc(r1)
	lhz r6, 0xa(r1)
	lhz r7, 0x8(r1)
	bl offscreenAddBoundingBox
	psq_l f31, 0x68(r1), 0, 0
	lwz r0, 0x74(r1)
	lfd f31, 0x60(r1)
	lwz r31, 0x5c(r1)
	lwz r30, 0x58(r1)
	lwz r29, 0x54(r1)
	lwz r28, 0x50(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void npcDisp(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stw r31, 0x4c(r1)
	stw r30, 0x48(r1)
	stw r29, 0x44(r1)
	stw r28, 0x40(r1)
	lfs f0, 0x144(r4)
	mr r31, r4
	fneg f1, f0
	bl reviseAngle
	fmr f31, f1
	mr r3, r31
	addi r4, r1, 0x10
	li r5, -0x1
	bl mtx_setup
	bl dispGetCurWork
	lbz r0, 0x1(r3)
	cmpwi r0, 0x1
	beq lbl_a2_1
	bge lbl_a2_2
	cmpwi r0, 0x0
	bge lbl_a2_3
	b lbl_a2_4
	lbl_a2_2:
	cmpwi r0, 0x3
	bge lbl_a2_4
	b lbl_a2_5
	lbl_a2_3:
	lwz r0, 0x1d4(r31)
	lwz r3, 0x114(r31)
	rlwinm. r0, r0, 0, 9, 9
	stw r3, 0xc(r1)
	beq lbl_a2_6
	lbz r5, 0xc(r1)
	addi r4, r1, 0x8
	lbz r6, 0xd(r1)
	srwi r0, r5, 31
	lbz r3, 0xe(r1)
	add r0, r0, r5
	srwi r5, r6, 31
	srawi r7, r0, 1
	srwi r0, r3, 31
	add r5, r5, r6
	srawi r5, r5, 1
	stb r7, 0xc(r1)
	add r0, r0, r3
	srawi r0, r0, 1
	stb r5, 0xd(r1)
	stb r0, 0xe(r1)
	lwz r0, 0xc(r1)
	stw r0, 0x8(r1)
	lwz r3, 0x104(r31)
	bl animPoseSetMaterialEvtColor
	lwz r3, 0x104(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lbl_a2_6:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 8, 8
	beq lbl_a2_7
	lwz r3, 0x104(r31)
	bl animPoseGetCurrentAnim
	lwz r3, 0x104(r31)
	bl animPoseGetAnimPosePtr
	mr r30, r3
	lwz r3, 0x104(r31)
	bl animPoseGetCurrentAnim
	mr r29, r3
	li r3, 0x4
	bl camGetPtr
	lfs f3, 0x18(r3)
	lfs f2, 0xc(r3)
	lfs f1, 0x20(r3)
	lfs f0, 0x14(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fneg f1, f2
	fneg f2, f0
	bl atan2
	frsp f1, f1
	lfs f0, float_rad2deg_80419bdc(r2)
	fmuls f1, f0, f1
	bl reviseAngle
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_8
	lfs f0, float_360_80419be0(r2)
	fadds f1, f1, f0
	lbl_a2_8:
	lfs f0, 0x74(r30)
	fsubs f1, f1, f0
	bl reviseAngle
	lfs f0, float_90_80419bd0(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_9
	lfs f0, float_270_80419be4(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	beq lbl_a2_10
	lbl_a2_9:
	lfs f0, float_neg90_80419bd8(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_11
	lfs f0, float_neg270_80419be8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne lbl_a2_11
	lbl_a2_10:
	lis r3, luigi_pose@ha
	li r30, 0x0
	addi r28, r3, luigi_pose@l
	lbl_a2_12:
	lwz r3, 0x0(r28)
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_13
	addi r30, r30, 0x1
	addi r28, r28, 0x8
	cmplwi r30, 0xe
	blt lbl_a2_12
	lbl_a2_13:
	cmplwi r30, 0xe
	bge lbl_a2_7
	lis r3, luigi_pose@ha
	slwi r0, r30, 3
	addi r4, r3, luigi_pose@l
	lwz r3, 0x104(r31)
	add r4, r4, r0
	li r5, 0x0
	lwz r4, 0x4(r4)
	bl animPoseSetAnim
	b lbl_a2_7
	lbl_a2_11:
	lis r3, luigi_pose@ha
	li r30, 0x0
	addi r28, r3, luigi_pose@l
	lbl_a2_14:
	lwz r3, 0x4(r28)
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_15
	addi r30, r30, 0x1
	addi r28, r28, 0x8
	cmplwi r30, 0xe
	blt lbl_a2_14
	lbl_a2_15:
	cmplwi r30, 0xe
	bge lbl_a2_7
	lis r3, luigi_pose@ha
	slwi r0, r30, 3
	addi r4, r3, luigi_pose@l
	lwz r3, 0x104(r31)
	lwzx r4, r4, r0
	li r5, 0x0
	bl animPoseSetAnim
	lbl_a2_7:
	lwz r3, 0x104(r31)
	bl animPoseMain
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x10
	li r5, 0x1
	bl animPoseDrawMtx
	b lbl_a2_4
	lbl_a2_1:
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x10
	li r5, 0x2
	bl animPoseDrawMtx
	b lbl_a2_4
	lbl_a2_5:
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x10
	li r5, 0x3
	bl animPoseDrawMtx
	lbl_a2_4:
	psq_l f31, 0x58(r1), 0, 0
	lwz r0, 0x64(r1)
	lfd f31, 0x50(r1)
	lwz r31, 0x4c(r1)
	lwz r30, 0x48(r1)
	lwz r29, 0x44(r1)
	lwz r28, 0x40(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void npcDisp_xlu(CameraId cameraId, void* param) {
	nofralloc
	stwu r1, -0x60(r1)
	mflr r0
	stw r0, 0x64(r1)
	stfd f31, 0x50(r1)
	psq_st f31, 0x58(r1), 0, 0
	stw r31, 0x4c(r1)
	stw r30, 0x48(r1)
	stw r29, 0x44(r1)
	stw r28, 0x40(r1)
	lfs f0, 0x144(r4)
	mr r31, r4
	fneg f1, f0
	bl reviseAngle
	fmr f31, f1
	mr r3, r31
	addi r4, r1, 0x10
	li r5, -0x1
	bl mtx_setup
	lwz r0, 0x1d4(r31)
	lwz r3, 0x114(r31)
	rlwinm. r0, r0, 0, 9, 9
	stw r3, 0xc(r1)
	beq lbl_a2_1
	lbz r5, 0xc(r1)
	addi r4, r1, 0x8
	lbz r6, 0xd(r1)
	srwi r0, r5, 31
	lbz r3, 0xe(r1)
	add r0, r0, r5
	srwi r5, r6, 31
	srawi r7, r0, 1
	srwi r0, r3, 31
	add r5, r5, r6
	srawi r5, r5, 1
	stb r7, 0xc(r1)
	add r0, r0, r3
	srawi r0, r0, 1
	stb r5, 0xd(r1)
	stb r0, 0xe(r1)
	lwz r0, 0xc(r1)
	stw r0, 0x8(r1)
	lwz r3, 0x104(r31)
	bl animPoseSetMaterialEvtColor
	lwz r3, 0x104(r31)
	li r4, 0x40
	bl animPoseSetMaterialFlagOn
	lbl_a2_1:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 8, 8
	beq lbl_a2_2
	lwz r3, 0x104(r31)
	bl animPoseGetCurrentAnim
	lwz r3, 0x104(r31)
	bl animPoseGetAnimPosePtr
	mr r30, r3
	lwz r3, 0x104(r31)
	bl animPoseGetCurrentAnim
	mr r29, r3
	li r3, 0x4
	bl camGetPtr
	lfs f3, 0x18(r3)
	lfs f2, 0xc(r3)
	lfs f1, 0x20(r3)
	lfs f0, 0x14(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fneg f1, f2
	fneg f2, f0
	bl atan2
	frsp f1, f1
	lfs f0, float_rad2deg_80419bdc(r2)
	fmuls f1, f0, f1
	bl reviseAngle
	lfs f0, float_0_80419b9c(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_3
	lfs f0, float_360_80419be0(r2)
	fadds f1, f1, f0
	lbl_a2_3:
	lfs f0, 0x74(r30)
	fsubs f1, f1, f0
	bl reviseAngle
	lfs f0, float_90_80419bd0(r2)
	fcmpo cr0, f1, f0
	ble lbl_a2_4
	lfs f0, float_270_80419be4(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	beq lbl_a2_5
	lbl_a2_4:
	lfs f0, float_neg90_80419bd8(r2)
	fcmpo cr0, f1, f0
	bge lbl_a2_6
	lfs f0, float_neg270_80419be8(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne lbl_a2_6
	lbl_a2_5:
	lis r3, luigi_pose@ha
	li r30, 0x0
	addi r28, r3, luigi_pose@l
	lbl_a2_7:
	lwz r3, 0x0(r28)
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_8
	addi r30, r30, 0x1
	addi r28, r28, 0x8
	cmplwi r30, 0xe
	blt lbl_a2_7
	lbl_a2_8:
	cmplwi r30, 0xe
	bge lbl_a2_2
	lis r3, luigi_pose@ha
	slwi r0, r30, 3
	addi r4, r3, luigi_pose@l
	lwz r3, 0x104(r31)
	add r4, r4, r0
	li r5, 0x0
	lwz r4, 0x4(r4)
	bl animPoseSetAnim
	b lbl_a2_2
	lbl_a2_6:
	lis r3, luigi_pose@ha
	li r30, 0x0
	addi r28, r3, luigi_pose@l
	lbl_a2_9:
	lwz r3, 0x4(r28)
	mr r4, r29
	bl strcmp
	cmpwi r3, 0x0
	beq lbl_a2_10
	addi r30, r30, 0x1
	addi r28, r28, 0x8
	cmplwi r30, 0xe
	blt lbl_a2_9
	lbl_a2_10:
	cmplwi r30, 0xe
	bge lbl_a2_2
	lis r3, luigi_pose@ha
	slwi r0, r30, 3
	addi r4, r3, luigi_pose@l
	lwz r3, 0x104(r31)
	lwzx r4, r4, r0
	li r5, 0x0
	bl animPoseSetAnim
	lbl_a2_2:
	lwz r3, 0x104(r31)
	bl animPoseMain
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x10
	li r5, 0x1
	bl animPoseDrawMtx
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x10
	li r5, 0x2
	bl animPoseDrawMtx
	fmr f1, f31
	lwz r3, 0x104(r31)
	lfs f2, float_2_80419c5c(r2)
	addi r4, r1, 0x10
	li r5, 0x3
	bl animPoseDrawMtx
	psq_l f31, 0x58(r1), 0, 0
	lwz r0, 0x64(r1)
	lfd f31, 0x50(r1)
	lwz r31, 0x4c(r1)
	lwz r30, 0x48(r1)
	lwz r29, 0x44(r1)
	lwz r28, 0x40(r1)
	mtlr r0
	addi r1, r1, 0x60
	blr
}

asm void mtx_setup(NpcEntry* entry, Mtx mtx, s32 history) {
	nofralloc
	stwu r1, -0xd0(r1)
	mflr r0
	stw r0, 0xd4(r1)
	stfd f31, 0xc0(r1)
	psq_st f31, 0xc8(r1), 0, 0
	stfd f30, 0xb0(r1)
	psq_st f30, 0xb8(r1), 0, 0
	stw r31, 0xac(r1)
	stw r30, 0xa8(r1)
	stw r29, 0xa4(r1)
	stw r28, 0xa0(r1)
	mr r28, r3
	lwz r3, 0x0(r3)
	lfs f31, float_0_80419b9c(r2)
	mr r29, r4
	rlwinm. r0, r3, 0, 6, 6
	lfs f30, float_1_80419bb4(r2)
	mr r30, r5
	bne lbl_a2_1
	rlwinm. r0, r3, 0, 4, 4
	bne lbl_a2_1
	bl camGetCurPtr
	mr r31, r3
	lfs f1, 0xc(r3)
	lfs f2, 0x14(r3)
	lfs f3, 0x18(r3)
	lfs f4, 0x20(r3)
	bl angleABf
	fmr f31, f1
	lfs f1, 0xc(r31)
	lfs f2, 0x14(r31)
	lfs f3, 0x8c(r28)
	lfs f4, 0x94(r28)
	bl angleABf
	fsubs f1, f31, f1
	bl reviseAngle
	fmr f31, f1
	lbl_a2_1:
	lfs f1, 0xf0(r28)
	bl reviseAngle
	bl reviseAngle
	lfs f0, float_90_80419bd0(r2)
	fcmpo cr0, f1, f0
	cror eq, gt, eq
	bne lbl_a2_2
	lfs f0, float_270_80419be4(r2)
	fcmpo cr0, f1, f0
	cror eq, lt, eq
	bne lbl_a2_2
	lfs f0, float_neg1_80419bf8(r2)
	fmuls f30, f30, f0
	lbl_a2_2:
	mr r3, r29
	bl PSMTXIdentity
	lfs f2, float_1_80419bb4(r2)
	lfs f1, 0xe0(r28)
	fcmpu cr0, f2, f1
	bne lbl_a2_3
	lfs f0, 0xe4(r28)
	fcmpu cr0, f2, f0
	bne lbl_a2_3
	lfs f0, 0xe8(r28)
	fcmpu cr0, f2, f0
	bne lbl_a2_3
	fcmpu cr0, f2, f30
	beq lbl_a2_4
	lbl_a2_3:
	lfs f0, 0xe8(r28)
	mr r3, r29
	lfs f2, 0xe4(r28)
	mr r4, r29
	fmuls f3, f0, f30
	bl PSMTXScaleApply
	lbl_a2_4:
	lfs f3, 0xf8(r28)
	lfs f1, float_0_80419b9c(r2)
	fcmpu cr0, f3, f1
	bne lbl_a2_5
	lfs f0, 0xfc(r28)
	fcmpu cr0, f0, f1
	bne lbl_a2_5
	lfs f0, 0x100(r28)
	fcmpu cr0, f0, f1
	beq lbl_a2_6
	lbl_a2_5:
	lfs f2, 0xfc(r28)
	fneg f1, f3
	lfs f0, 0x100(r28)
	mr r3, r29
	fneg f2, f2
	mr r4, r29
	fneg f3, f0
	bl PSMTXTransApply
	lbl_a2_6:
	lfs f1, 0xf4(r28)
	lfs f0, float_0_80419b9c(r2)
	fcmpu cr0, f1, f0
	beq lbl_a2_7
	lfs f0, float_deg2rad_80419ca0(r2)
	addi r3, r1, 0x8
	li r4, 0x7a
	fmuls f1, f0, f1
	bl PSMTXRotRad
	mr r4, r29
	mr r5, r29
	addi r3, r1, 0x8
	bl PSMTXConcat
	lbl_a2_7:
	lfs f1, 0xec(r28)
	lfs f0, float_0_80419b9c(r2)
	fcmpu cr0, f1, f0
	beq lbl_a2_8
	lfs f0, float_deg2rad_80419ca0(r2)
	addi r3, r1, 0x68
	li r4, 0x78
	fmuls f1, f0, f1
	bl PSMTXRotRad
	mr r4, r29
	mr r5, r29
	addi r3, r1, 0x68
	bl PSMTXConcat
	lbl_a2_8:
	lfs f1, 0xf0(r28)
	lfs f0, float_0_80419b9c(r2)
	fcmpu cr0, f1, f0
	bne lbl_a2_9
	fcmpu cr0, f31, f0
	beq lbl_a2_10
	lbl_a2_9:
	fadds f0, f1, f31
	lfs f1, float_deg2rad_80419ca0(r2)
	addi r3, r1, 0x38
	li r4, 0x79
	fmuls f1, f1, f0
	bl PSMTXRotRad
	mr r4, r29
	mr r5, r29
	addi r3, r1, 0x38
	bl PSMTXConcat
	lbl_a2_10:
	lfs f1, 0xf8(r28)
	lfs f2, float_0_80419b9c(r2)
	fcmpu cr0, f1, f2
	bne lbl_a2_11
	lfs f0, 0xfc(r28)
	fcmpu cr0, f0, f2
	bne lbl_a2_11
	lfs f0, 0x100(r28)
	fcmpu cr0, f0, f2
	beq lbl_a2_12
	lbl_a2_11:
	lfs f2, 0xfc(r28)
	mr r3, r29
	lfs f3, 0x100(r28)
	mr r4, r29
	bl PSMTXTransApply
	lbl_a2_12:
	cmpwi r30, -0x1
	bne lbl_a2_13
	lfs f1, 0x8c(r28)
	mr r3, r29
	lfs f2, 0x90(r28)
	mr r4, r29
	lfs f3, 0x94(r28)
	bl PSMTXTransApply
	b lbl_a2_14
	lbl_a2_13:
	mulli r0, r30, 0xc
	mr r3, r29
	mr r4, r29
	add r5, r28, r0
	lfs f1, 0xa4(r5)
	lfs f2, 0xa8(r5)
	lfs f3, 0xac(r5)
	bl PSMTXTransApply
	lbl_a2_14:
	psq_l f31, 0xc8(r1), 0, 0
	lfd f31, 0xc0(r1)
	psq_l f30, 0xb8(r1), 0, 0
	lfd f30, 0xb0(r1)
	lwz r31, 0xac(r1)
	lwz r30, 0xa8(r1)
	lwz r29, 0xa4(r1)
	lwz r0, 0xd4(r1)
	lwz r28, 0xa0(r1)
	mtlr r0
	addi r1, r1, 0xd0
	blr
}

asm void npcRecoveryFieldNpc(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	la r3, work(r13)
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	la r30, work(r13)
	lwz r0, 0x8(r3)
	lwz r29, release_wp(r13)
	rlwinm. r0, r0, 0, 30, 30
	beq lbl_a2_1
	lwz r28, 0xc(r30)
	li r27, 0x0
	b lbl_a2_2
	lbl_a2_3:
	lwz r3, 0x0(r28)
	clrlwi. r0, r3, 31
	beq lbl_a2_4
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_4
	lwz r0, 0x104(r28)
	cmpwi r0, -0x1
	bne lbl_a2_4
	mr r3, r29
	li r4, 0x0
	bl animPoseEntry
	stw r3, 0x104(r28)
	addi r4, r29, 0x40
	li r5, 0x1
	lwz r3, 0x104(r28)
	bl animPoseSetAnim
	lwz r3, 0x104(r28)
	bl animPoseGetAnimPosePtr
	lwz r0, 0x80(r29)
	mr r31, r3
	stw r0, 0x0(r3)
	lfs f0, 0x84(r29)
	stfs f0, 0x70(r3)
	lfs f0, 0x88(r29)
	stfs f0, 0x74(r3)
	lfs f0, 0x8c(r29)
	stfs f0, 0x78(r3)
	lfs f0, 0x90(r29)
	stfs f0, 0x7c(r3)
	lwz r3, 0x0(r3)
	rlwinm. r0, r3, 0, 25, 25
	beq lbl_a2_5
	rlwinm r0, r3, 0, 26, 24
	stw r0, 0x0(r31)
	lwz r3, 0x104(r28)
	bl animPoseWorldPositionEvalOn
	lbl_a2_5:
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 24, 24
	beq lbl_a2_6
	rlwinm r0, r3, 0, 25, 23
	stw r0, 0x0(r31)
	lwz r3, 0x104(r28)
	bl animPoseWorldMatrixEvalOn
	lbl_a2_6:
	lwz r3, 0x104(r28)
	bl animPoseMain
	addi r29, r29, 0x94
	lbl_a2_4:
	addi r27, r27, 0x1
	addi r28, r28, 0x340
	lbl_a2_2:
	lwz r0, 0x4(r30)
	cmpw r27, r0
	blt lbl_a2_3
	lwz r0, 0x8(r30)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x8(r30)
	lbl_a2_1:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void npcReleaseFieldNpc(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	la r3, work(r13)
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	la r31, work(r13)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	lwz r0, 0x8(r3)
	lwz r30, release_wp(r13)
	rlwinm. r0, r0, 0, 30, 30
	beq lbl_a2_1
	lwz r29, 0xc(r31)
	li r28, 0x0
	b lbl_a2_2
	lbl_a2_3:
	lwz r3, 0x0(r29)
	clrlwi. r0, r3, 31
	beq lbl_a2_4
	rlwinm. r0, r3, 0, 30, 30
	beq lbl_a2_4
	lwz r3, 0x104(r29)
	bl animPoseGetAnimPosePtr
	lwz r0, 0x90(r3)
	cmpwi r0, -0x1
	bne lbl_a2_4
	lwz r3, 0x104(r29)
	cmpwi r3, 0x0
	blt lbl_a2_4
	bl animPoseGetAnimPosePtr
	lwz r0, 0x0(r3)
	stw r0, 0x80(r30)
	lfs f0, 0x70(r3)
	stfs f0, 0x84(r30)
	lfs f0, 0x74(r3)
	stfs f0, 0x88(r30)
	lfs f0, 0x78(r3)
	stfs f0, 0x8c(r30)
	lfs f0, 0x7c(r3)
	stfs f0, 0x90(r30)
	lwz r3, 0x104(r29)
	bl animPoseGetAnimBaseDataPtr
	mr r4, r3
	mr r3, r30
	addi r4, r4, 0x4
	bl strcpy
	lwz r3, 0x104(r29)
	bl animPoseGetCurrentAnim
	mr r4, r3
	addi r3, r30, 0x40
	bl strcpy
	lwz r3, 0x104(r29)
	bl animPoseRelease
	li r0, -0x1
	addi r30, r30, 0x94
	stw r0, 0x104(r29)
	lbl_a2_4:
	addi r28, r28, 0x1
	addi r29, r29, 0x340
	lbl_a2_2:
	lwz r0, 0x4(r31)
	cmpw r28, r0
	blt lbl_a2_3
	lbl_a2_1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm NpcWork* npcGetWorkPtr(void) {
	nofralloc
	lwz r4, gp(r13)
	la r3, work(r13)
	lwz r0, 0x14(r4)
	cmpwi r0, 0x0
	beqlr
	addi r3, r3, 0x14
	blr
}
// clang-format on
#endif
