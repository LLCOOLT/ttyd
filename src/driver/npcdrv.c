#define npcCheckInterrupt npcCheckInterrupt_hdr_void
#include "driver/npcdrv.h"
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
static inline f32 npc_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
static inline f32 npc_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
void FontDrawScale(f32 scale);
void FontDrawStringShake(f32 x, f32 y, const char* message);

extern int __float_nan[];
static inline s32 npc_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
static inline f32 npc_sqrtf(f32 x) { if (x > 0.0f) { f64 guess = __frsqrte(x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); guess = 0.5 * guess * (3.0 - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (npc_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
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
BOOL dbg_battleskip;
u32 npcMainCount;
NpcFieldEntry* release_wp;
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
NpcWork* npcGetWorkPtr(void) {
    return gp->inBattle ? &work.battle : &work.field;
}

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
                    field->wCurrentRenderRotationMinus90Y = pose->field_0x70;
                    field->wRotationY = pose->rotationY;
                    field->wScaleZ_flip = pose->field_0x78;
                    field->wInitToZero4 = pose->field_0x7C;
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
                pose->field_0x70 = field->wCurrentRenderRotationMinus90Y;
                pose->rotationY = field->wRotationY;
                pose->field_0x78 = field->wScaleZ_flip;
                pose->field_0x7C = field->wInitToZero4;

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

void mtx_setup(NpcEntry* entry, Mtx mtx, s32 history) {
    f32 rotationAngle;
    f32 scaleSign;
    CameraEntry* camera;
    f32 targetAngle;
    f32 positionAngle;
    f32 v15;
    Mtx mtxX, mtxY, mtxZ;

    rotationAngle = 0.0f;
    scaleSign = 1.0f;
    if (!(entry->flags & 0x2000000) && !(entry->flags & 0x8000000)) {
        camera = camGetCurPtr();
        targetAngle = angleABf(camera->cameraPos.x, camera->cameraPos.z, camera->cameraAt.x, camera->cameraAt.z);
        positionAngle = angleABf(camera->cameraPos.x, camera->cameraPos.z, entry->position.x, entry->position.z);
        rotationAngle = reviseAngle(targetAngle - positionAngle);
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

double atan2(double y, double x);

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

    if (entry->flags & 0x800000) {
        AnimationPose* animPose;
        AnimTableEntry* anim;
        CameraEntry* camera;
        f32 dx, dz;
        f32 angle;
        u32 i;

        animPoseGetCurrentAnim(entry->poseId);
        animPose = animPoseGetAnimPosePtr(entry->poseId);
        anim = animPoseGetCurrentAnim(entry->poseId);

        camera = camGetPtr(CAMERA_3D);
        dx = camera->cameraAt.x - camera->cameraPos.x;
        dz = camera->cameraAt.z - camera->cameraPos.z;
        angle = reviseAngle(MTXRadToDeg((f32)atan2(-dx, -dz)));
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        angle = reviseAngle((angle - animPose->rotationY));

        
        if ((angle > 90.0f && angle <= 270.0f) || (angle < -90.0f && angle >= -270.0f)) {
            for (i = 0; i < 14; i++) {
                if (!strcmp(luigi_pose[i][0], anim->name)) {
                    break;
                }
            }
            if (i < 14) {
                animPoseSetAnim(entry->poseId, luigi_pose[i][1], FALSE);
            }
        } else {
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
    animPoseMain(entry->poseId);
    animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
}

void npcDisp(CameraId camId, void* param) {
    NpcEntry* entry = param; // cast to proper type
    Mtx mtx;
    GXColor color;
    f32 rotY;
    u32 i;
    AnimTableEntry* anim;

    rotY = reviseAngle(-entry->direction);
    mtx_setup(entry, mtx, -1);

    switch (dispGetCurWork()->renderMode) {
        case 0:
            color = entry->color;
            if (entry->jumpFlags & 0x400000) {
                color.r /= 2;
                color.g /= 2;
                color.b /= 2;
                animPoseSetMaterialEvtColor(entry->poseId, color);
                animPoseSetMaterialFlagOn(entry->poseId, 0x40);
            }

            if (entry->flags & 0x800000) {
                AnimationPose* animPose;
                CameraEntry* camera;
                f32 dx, dz;
                f32 angle;

                animPoseGetCurrentAnim(entry->poseId);
                animPose = animPoseGetAnimPosePtr(entry->poseId);
                anim = animPoseGetCurrentAnim(entry->poseId);

                camera = camGetPtr(CAMERA_3D);
                dx = camera->cameraAt.x - camera->cameraPos.x;
                dz = camera->cameraAt.z - camera->cameraPos.z;
                angle = reviseAngle(MTXRadToDeg((f32)atan2(-dx, -dz)));
                if (angle < 0.0f) {
                    angle += 360.0f;
                }
                angle = reviseAngle((angle - animPose->rotationY));

        
                if ((angle > 90.0f && angle <= 270.0f) || (angle < -90.0f && angle >= -270.0f)) {
                    for (i = 0; i < 14; i++) {
                        if (!strcmp(luigi_pose[i][0], anim->name)) {
                            break;
                        }
                    }
                    if (i < 14) {
                        animPoseSetAnim(entry->poseId, luigi_pose[i][1], FALSE);
                    }
                } else {
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

    color = entry->color;
    if (entry->jumpFlags & 0x400000) {
        color.r /= 2;
        color.g /= 2;
        color.b /= 2;
        animPoseSetMaterialEvtColor(entry->poseId, color);
        animPoseSetMaterialFlagOn(entry->poseId, 0x40);
    }

    if (entry->flags & 0x800000) {
        AnimationPose* animPose;
        AnimTableEntry* anim;
        CameraEntry* camera;
        f32 dx, dz;
        f32 angle;
        u32 i;

        animPoseGetCurrentAnim(entry->poseId);
        animPose = animPoseGetAnimPosePtr(entry->poseId);
        anim = animPoseGetCurrentAnim(entry->poseId);

        camera = camGetPtr(CAMERA_3D);
        dx = camera->cameraAt.x - camera->cameraPos.x;
        dz = camera->cameraAt.z - camera->cameraPos.z;
        angle = reviseAngle(MTXRadToDeg((f32)atan2(-dx, -dz)));
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        angle = reviseAngle((angle - animPose->rotationY));

        
        if ((angle > 90.0f && angle <= 270.0f) || (angle < -90.0f && angle >= -270.0f)) {
            for (i = 0; i < 14; i++) {
                if (!strcmp(luigi_pose[i][0], anim->name)) {
                    break;
                }
            }
            if (i < 14) {
                animPoseSetAnim(entry->poseId, luigi_pose[i][1], FALSE);
            }
        } else {
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
    animPoseMain(entry->poseId);
    animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
    animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    offscreenAddBoundingBox(entry->field_110, left, top, right, bottom);
}

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
            color = entry->color;
            if (entry->jumpFlags & 0x400000) {
                color.r /= 2;
                color.g /= 2;
                color.b /= 2;
                animPoseSetMaterialEvtColor(entry->poseId, color);
                animPoseSetMaterialFlagOn(entry->poseId, 0x40);
            }

            if (entry->flags & 0x800000) {
                u32 i;
                AnimTableEntry* anim;
                AnimationPose* animPose;
                CameraEntry* camera;
                f32 dx, dz;
                f32 angle;

                animPoseGetCurrentAnim(entry->poseId);
                animPose = animPoseGetAnimPosePtr(entry->poseId);
                anim = animPoseGetCurrentAnim(entry->poseId);

                camera = camGetPtr(CAMERA_3D);
                dx = camera->cameraAt.x - camera->cameraPos.x;
                dz = camera->cameraAt.z - camera->cameraPos.z;
                angle = reviseAngle(MTXRadToDeg((f32)atan2(-dx, -dz)));
                if (angle < 0.0f) {
                    angle += 360.0f;
                }
                angle = reviseAngle((angle - animPose->rotationY));

        
                if ((angle > 90.0f && angle <= 270.0f) || (angle < -90.0f && angle >= -270.0f)) {
                    for (i = 0; i < 14; i++) {
                        if (!strcmp(luigi_pose[i][0], anim->name)) {
                            break;
                        }
                    }
                    if (i < 14) {
                        animPoseSetAnim(entry->poseId, luigi_pose[i][1], FALSE);
                    }
                } else {
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
    offscreenAddBoundingBox(entry->field_110, left, top, right, bottom);
}

void npcDisp_blur(CameraId camId, void* param) {
    GXColor col;
    s32 alpha;
    NpcEntry* entry = param;
    s32 i;
    u32 matFlag;
    f32 rotY;
    f32 z;
    f32 x;
    Mtx mtx;

    rotY = reviseAngle(-entry->direction);
    matFlag = animPoseGetMaterialFlag(entry->poseId);
    x = 2.0f * npc_sin((6.2831855f * camGetPtr(camId)->viewYaw) / 360.0f);
    z = 2.0f * -npc_cos((6.2831855f * camGetPtr(camId)->viewYaw) / 360.0f);
    animPoseMain(entry->poseId);
    for (i = 4, alpha = 100; i > 0; i--, alpha -= 25) {
        mtx_setup(entry, mtx, i);
        MTXTransApply(mtx, mtx, x, 0.0f, z);
        animPoseSetMaterialFlagOn(entry->poseId, 0x40);
        {
            GXColor c = {0xFF, 0xFF, 0xFF, 0x00};
            c.a = 0x80 - alpha;
            col = c;
        }
        animPoseSetMaterialEvtColor(entry->poseId, col);
        animPoseDrawMtx(entry->poseId, mtx, 1, rotY, 2.0f);
        animPoseDrawMtx(entry->poseId, mtx, 2, rotY, 2.0f);
        animPoseDrawMtx(entry->poseId, mtx, 3, rotY, 2.0f);
    }
    animPoseSetMaterialFlagOff(entry->poseId, 0x40);
    animPoseSetMaterialFlagOn(entry->poseId, matFlag);
}

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

void npcReset(BOOL inBattle) {
    NpcWork* wp = npcGetWorkPtr2(inBattle);
    memset(wp->entries, 0, sizeof(NpcEntry) * wp->total);
    wp->count = 0;
    if (!inBattle) {
        gp->fbatData->mode = 0;
    }
    npcMainCount = 0;
}

s32 npcGetReactionOfLivingBody(BOOL inBattle) {
    return npcGetWorkPtr2(inBattle)->count;
}

// TODO: fix entry->position delayed set-Vec with r6/r30
// TODO: a1 is desc/ription?
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
    entry->field_154 = 1.0f;
    entry->field_108 = 0;
    entry->field_10C = "M_I_2";
    entry->field_198 = gp->renderTime;
    entry->field_188 = 0;
    entry->jumpGravity = 1.0f;
    entry->field_1D0 = 0.0f;
    entry->jumpYScale = 1.0f;
    entry->field_110 = -1;
    entry->color = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    entry->cameraId = CAMERA_3D;
    entry->field_2F8 = 0;
    entry->balloonType = 1;
    if (animPoseGetVivianType(entry->poseId)) {
        entry->flags |= 0x4000000;
    }
    if (!strcmp(animName, "c_luigi")) {
        entry->flags |= 0x800000u;
    }
    animPoseSetMaterialLightFlagOn(entry->poseId, 2);
    wp->count++;
    return i;
}

NpcTribeInfo* npcGetTribe(const char* tribeName) { // 1:1
    NpcTribeInfo* tribe;

    for (tribe = npcTribe; tribe->nameJp; tribe++) {
        if (!strcmp(tribe->nameJp, tribeName)) {
            return tribe;
        }
    }
    return NULL;
}

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

void _npcDeleteGroup(NpcEntry* entry) { // recursively inlined, warning
    int i;

    if (entry->next) {
        _npcDeleteGroup(entry->next);
    }

    for (i = 0; i < 4; i++) {
        NpcEntry* s = entry->slaves[i];
        if (s) {
            npcDelete(s);
            entry->slaves[i] = NULL;
        }
    }
    npcDelete(entry);
}

void npcDeleteGroup(NpcEntry* entry) {
    if (entry->master) {
        entry = entry->master;
    }
    while (entry->prev) {
        entry = entry->prev;
    }
    _npcDeleteGroup(entry);
}

void _fbatFirstAttackAnnouceDisp(CameraId camId, void* param);
void fbatEncountCheck(void);
void fbatTalkMode(void);
void fbatBattleMode(void);
s32 kpaJumpChk(void);
s32 kpaFireAttackCheck(void);

void npcMain(void) {
    NpcWork* npcwork;
    NpcEntry* entry;
    int i;
    int total;

    npcwork = gp->inBattle ? &work.battle : &work.field;
    // npcwork = npcGetWorkPtr();
    marioGetPtr()->field_0x1D8 = 0;
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

            if ((u16)entry->wFbatHitCheckRelated) {
                entry->wFbatHitCheckRelated--;
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
                /* TODO: block at 0x248-0x2b0 (strcmp/psndSFXOn_3D, 0x1d4 flags) */
                if (!strcmp(gp->currentMapName, (char*)entry + 0x18c)) {
                    psndSFXOn_3D(NULL, (Vec*)((u8*)entry + 0x8c));
                }
                /* TODO: block at 0x2b0-0x8a8 (move/hit side, npcMoveG, anim select, breath, mario/vivian checks) */
                /* TODO: block at 0x8a8-0xc40 (angle tracking, npcCheckInterrupt, cam projection) */
                /* TODO: block at 0xc40-0xfb0 (material color, dispEntry, shadow, hitCheckFilter, vivian) */
                /* TODO: block at 0xfb0-0x1004 (copy position to prev, clear flag) */
            }
        }
    }

    {
        u8* fbat = *(u8**)((u8*)gp + 0x168);
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
        case 1: {
            u8* fb2;
            MarioWork* mario;
            s32 jump, fire;
            fbatEncountCheck();
            fb2 = *(u8**)((u8*)gp + 0x168);
            mario = marioGetPtr();
            jump = 0;
            fire = 0;
            if (*((u8*)mario + 0x3c) == 2) jump = kpaJumpChk();
            if (*((u8*)mario + 0x3c) == 2) fire = kpaFireAttackCheck();
            if (jump) {
                if (*(s32*)(fb2 + 0x57c) > 0 && *(s32*)(fb2 + 0x578) >= 2) {
                    Vec pos = *(Vec*)((u8*)mario + 0x8c);
                    pos.y += 60.0f;
                    kpaAddScorePos(*(s32*)(fb2 + 0x57c), &pos);
                }
                *(s32*)(fb2 + 0x578) = 0;
                *(s32*)(fb2 + 0x57c) = 0;
            } else if (!fire) {
                *(s32*)(fb2 + 0x574) = 0;
            }
            break;
        }
        case 2:
        case 3:
            fbatTalkMode();
            break;
        case 5:
            fbatBattleMode();
            break;
        }
        *(fbat + 0x54d) = 0;
    }
}

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

void npcSetMarioAutoTalkPose(const char* stayPose, const char* talkPose) {
    strcpy(MarioStayPose, stayPose);
    strcpy(MarioTalkPose, talkPose);
}

void npcSetTalkPose(const char* name) {
    PartyEntry* party;
    NpcEntry* npc;

    if (*(s8*)name == 0) return;
    if (!strcmp(name, "(^x^)party")) return;
    if (!strcmp(name, "party")) {
        party = partyGetPtr(marioGetPartyId());
        if (party) {
            partyChgPoseId(party, 7);
        }
    } else if (!strcmp(name, "extparty")) {
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

void npcSetStayPose(const char* name) {
    PartyEntry* party;
    NpcEntry* npc;

    if (*(s8*)name == 0) return;
    if (!strcmp(name, "(^x^)party")) return;
    if (!strcmp(name, "party")) {
        party = partyGetPtr(marioGetPartyId());
        if (party) {
            partyChgPoseId(party, 1);
        }
    } else if (!strcmp(name, "extparty")) {
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

#pragma opt_propagation off
#pragma opt_lifetimes off
BOOL npcCheckHitMarioSide(NpcEntry* npc) {
    MarioWork* mario;
    Vec marioPos;
    f32 dist;
    f32 range;
    f32 angle;
    f32 dx, dz;
    f32 rad;
    f32 len;
    f32 scale;

    mario = marioGetPtr();
    if (npc->position.y > mario->position.y + mario->wPlayerCollisionBox.y) {
        return FALSE;
    }
    if (mario->position.y > npc->position.y + npc->height) {
        return FALSE;
    }
    marioPos.x = mario->position.x;
    marioPos.z = mario->position.z;
    marioPos.y = npc->position.y;
    dist = PSVECDistance(&marioPos, &npc->position);
    range = (5.0f + (mario->wPlayerCollisionBox.x + npc->width)) * 0.5f;
    if (dist > range) {
        return FALSE;
    }
    npc->position.x = npc->prevPosition.x;
    npc->position.z = npc->prevPosition.z;
    dist = PSVECDistance(&marioPos, &npc->position);
    if (dist > range) {
        return FALSE;
    }
    mario->field_0x1D8 = (s32)npc;
    angle = angleABf(mario->position.x, mario->position.z, npc->position.x, npc->position.z);
    if (__fabsf(compAngle(angle, mario->directionView)) < 40.0f) {
        dx = (range - dist) * -npc_sin((6.2832f * mario->directionView) / 360.0f);
        dz = (range - dist) * npc_cos((6.2832f * mario->directionView) / 360.0f);

    } else {
        rad = (6.2832f * angle) / 360.0f;
        dx = (npc->position.x - range * npc_sin(rad)) - mario->position.x;
        dz = (npc->position.z + range * npc_cos(rad)) - mario->position.z;
    }
    len = npc_sqrtf(dx * dx + dz * dz);
    if (len > (mario->wPlayerCollisionBox.z > 4.0f ? 3.0f : 1.5f)) {
        scale = 2.0f / len;
        dx *= scale;
        dz *= scale;
    }
    mario->position.x += dx;
    mario->position.z += dz;
    marioChkWallAround(&mario->position, 0, 0.0f, 160.0f + angle, 20.0f, mario->wPlayerCollisionBox.y);
    return TRUE;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

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
            h = 0.8f * npc->height;
            dist = h + (f32)__fabs(dy);
            if ((npc->field_0x300 = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &dist, &hitNX, &hitNY, &hitNZ,
                                              npc->position.x, npc->position.y + h, npc->position.z, 0.0f,
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

void npcTuningRy(NpcEntry* npc, f32 angle) {
    npc->direction = reviseAngle(angle);
}

f32 npcTransRytoFaceDir(NpcEntry* npc) {
    if (reviseAngle(npc->direction) < 180.0f) {
        return 90.0f;
    }
    return 270.0f;
}

HitEntry* npcHitCheckSide(NpcEntry* npc, f32* outX, f32* outZ, f32* angle, f32 dx, f32 dz) {
    f32 s, c;
    f32 hx, hy, hz, dist, nx, ny, nz;
    f32 lenSq, d, height;
    HitEntry* hit;

    *outX = npc->position.x;
    *outZ = npc->position.z;
    if (dx == 0.0f && dz == 0.0f) {
        return NULL;
    }
    sincosf(&s, &c, angleABf(0.0f, 0.0f, dx, dz));
    lenSq = dx * dx + dz * dz;

    dist = npc_sqrtf(lenSq) + 0.75f * npc->width;
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
        d = dx * nx + dz * nz;
        *outX += 0.5f * (dx - d * nx);
        *outZ += 0.5f * (dz - d * nz);
        if (npc->flags & 0x10000) {
            f32 a = reviseAngle(180.0f + *angle);
            f32 b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * nx, 100.0f * nz));
            *angle = (s32)reviseAngle(b + reviseAngle(b - a));
        }
        return hit;
    }

    dist = npc_sqrtf(lenSq) + 0.75f * npc->width;
    height = 0.4f * npc->height;
    if (npc->flags & 0x2000) {
        hit = hitCheckAttr(4, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    } else {
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    }
    if (hit && angleABf(0.0f, 0.0f, npc_sqrtf(nx * nx + nz * nz), -ny) >= 45.0f) {
        d = dx * nx + dz * nz;
        *outX += 0.5f * (dx - d * nx);
        *outZ += 0.5f * (dz - d * nz);
        if (npc->flags & 0x10000) {
            f32 a = reviseAngle(180.0f + *angle);
            f32 b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * nx, 100.0f * nz));
            *angle = (s32)reviseAngle(b + reviseAngle(b - a));
        }
        return hit;
    }

    dist = npc_sqrtf(lenSq) + 0.75f * npc->width;
    height = 0.75f * npc->height;
    if (npc->flags & 0x2000) {
        hit = hitCheckAttr(4, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    } else {
        hit = hitCheckFilter(NULL, &hx, &hy, &hz, &dist, &nx, &ny, &nz, npc->position.x, npc->position.y + height, npc->position.z, s, 0.0f, c);
    }
    if (hit) {
        d = dx * nx + dz * nz;
        *outX += 0.5f * (dx - d * nx);
        *outZ += 0.5f * (dz - d * nz);
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

FieldBattleData* fbatGetPointer(void) {
    return gp->fbatData;
}

void fbatChangeMode(s16 mode) {
    gp->fbatData->mode = mode;
}

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
            firstStrike->msg_tag = "fb_sensei_shita"; // You struck first!
            firstStrike->type = 2;
            firstStrike->color = (GXColor){ 0xFF, 0x80, 0x80, 0xFF };
            break;
        case 0x10000000:
            firstStrike->msg_tag = "fb_sensei_sareta"; // Your foe struck first!
            firstStrike->type = 1;
            firstStrike->color = (GXColor){ 0x80, 0x80, 0xFF, 0xFF };
            break;
        default:
            firstStrike->type = 0;
            break;
    }
}

void fbatSetAttackAnnounceEnable(void) {
    gp->fbatData->firstStrike.enabled = TRUE;
}

static inline f32 mulf(f32 a, f32 b) { return a * b; }
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
s32 marioStGetSystemLevel(void);
BOOL N_itemPickUpFromFieldCheck(void);
void marioChgMotJump2(void);
f32 marioGetDispDir(void);
void npcKoopaModeEncountCheck(void);

static inline f32 fbat_camAngle(void) {
    CameraEntry* camera = camGetPtr(CAMERA_3D);
    f32 dx = camera->cameraAt.x - camera->cameraPos.x;
    f32 dz = camera->cameraAt.z - camera->cameraPos.z;
    f32 angle = reviseAngle(MTXRadToDeg((f32)atan2(-dx, -dz)));
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}

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

void fbatEncountCheck(void) {
    NpcWork* wp = npcGetWorkPtrInline();
    s32 total = wp->total;
    MarioWork* mario = marioGetPtr();
    FieldBattleData* data;
    NpcEntry* npc;
    u32* kind;
    s32 i;
    NpcEntry* talk;
    f32 best;

    wp->field_0x10 = NULL;
    if ((u32)marioStGetSystemLevel()) {
        return;
    }
    if (!(wp->flags & 1)) {
        if (marioKeyOffChk() || marioCtrlOffChk()) {
            return;
        }
    }
    if (N_itemPickUpFromFieldCheck()) {
        return;
    }
    data = gp->fbatData;
    kind = (u32*)((u8*)data + 0x10);
    npc = fbatHitCheck(0x13f1, kind);
    if (npc && data->mode == 1) {
        AnimationPose* pose;
        f32 rel;
        f32 ang;
        if (!fbat_setHit(npc)) {
            return;
        }
        switch (*kind) {
            case 0x10000:
            case 0x20000:
            default:
                break;
            case 0x40000:
            case 0x80000:
                marioChgMotJump2();
                if (dbg_battleskip != 1) {
                    animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
                }
                break;
            case 0x100000:
            case 0x200000:
            case 0x400000:
                if (dbg_battleskip != 1) {
                    animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
                }
                break;
            case 0x800000:
                if (dbg_battleskip != 1) {
                    animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
                }
                break;
            case 0x1000000:
                if (dbg_battleskip != 1) {
                    animPoseSetAnim(npc->poseId, npc->tribe->damageAnimation, 1);
                }
                break;
        }
        pose = animPoseGetAnimPosePtr(npc->poseId);
        npc->field_148 = npc->direction;
        npc->direction = angleABf(npc->position.x, npc->position.z, mario->position.x, mario->position.z);
        rel = -90.0f + reviseAngle(-npc->direction);
        ang = reviseAngle(fbat_camAngle() - rel);
        if ((ang > 90.0f && ang <= 270.0f) || (ang < -90.0f && ang >= -270.0f)) {
            pose->field_0x7C = reviseAngle(180.0f + fbat_camAngle());
        } else {
            pose->field_0x7C = fbat_camAngle();
        }
        while (pose->field_0x7C - pose->rotationY > 180.0f) {
            pose->rotationY += 360.0f;
        }
        while (pose->field_0x7C - pose->rotationY < -180.0f) {
            pose->rotationY -= 360.0f;
        }
        pose->rotationY += 0.75f * (pose->field_0x7C - pose->rotationY);
        switch (*kind) {
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
        switch (*kind) {
            case 0x20000:
            case 0x40000:
            case 0x80000:
            case 0x100000:
            case 0x200000:
            case 0x400000:
            case 0x800000:
            case 0x1000000:
                if (npc) {
                    psndSFXOn_3D("SFX_BTL_FLD_ENEMY_DAMAGED1", &npc->position);
                }
                break;
            case 0x10000000:
                psndSFXOn_3D("SFX_BTL_FLD_MARIO_DAMAGED1", &mario->position);
                break;
        }
        return;
    }

    best = 1000.0f;
    if (marioChkTalkable() && !mario->keyOffCount) {
        talk = NULL;
        npc = wp->entries;
        for (i = 0; i < total; i++, npc++) {
            BOOL hit;
            if (!(npc->flags & 2) || (npc->flags & 8) || !npc->talkEvt) {
                continue;
            }
            hit = FALSE;
            if (!(npc->position.y > mario->position.y + mario->wPlayerCollisionBox.y) &&
                !(mario->position.y > npc->position.y + npc->height)) {
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
                if (dist <= 0.5f * (mario->wPlayerCollisionBox.x + npc->width) + 10.0f && dist < best) {
                    talk = npc;
                }
                facing = FALSE;
                yaw = camGetPtr(CAMERA_3D)->viewYaw;
                dir = reviseAngle(marioGetDispDir() - yaw);
                for (j = 0; j < 3; j++) {
                    switch (j) {
                        case 0:
                            yaw = camGetPtr(CAMERA_3D)->viewYaw;
                            a = reviseAngle(angleABf(mario->position.x, mario->position.z, npc->position.x, npc->position.z) - yaw);
                            break;
                        case 1:
                            yaw = camGetPtr(CAMERA_3D)->viewYaw;
                            a = reviseAngle(angleABf(mario->position.x, mario->position.z, npc->position.x + 0.5f * npc->width, npc->position.z) - yaw);
                            break;
                        default:
                            yaw = camGetPtr(CAMERA_3D)->viewYaw;
                            a = reviseAngle(angleABf(mario->position.x, mario->position.z, npc->position.x - 0.5f * npc->width, npc->position.z) - yaw);
                            break;
                    }
                    if (a < 180.0f) {
                        if (!(dir > 180.0f)) {
                            facing = TRUE;
                            break;
                        }
                    } else if (!(dir < 180.0f)) {
                        facing = TRUE;
                        break;
                    }
                }
                if (facing) {
                    pos.x = mario->position.x;
                    pos.z = mario->position.z;
                    pos.y = npc->position.y;
                    dist = PSVECDistance(&pos, &npc->position);
                    if (!(dist > 0.5f * (mario->wPlayerCollisionBox.x + npc->width) + 10.0f)) {
                        f32 dx = npc->position.x - mario->position.x;
                        f32 dz = npc->position.z - mario->position.z;
                        f32 s, c, len;
                        f32 hx, hy, hz, nx, ny, nz;
                        sincosf(&s, &c, angleABf(0.0f, 0.0f, dx, dz));
                        len = npc_sqrtf(dx * dx + dz * dz);
                        if (!hitCheckFilter(NULL, &hx, &hy, &hz, &len, &nx, &ny, &nz, mario->position.x,
                                            mario->position.y + 0.75f * mario->wPlayerCollisionBox.y,
                                            mario->position.z, s, 0.0f, c)) {
                            hit = TRUE;
                            if (dist < best) {
                                best = dist;
                                wp->field_0x10 = npc;
                            }
                        }
                    }
                }
            }
            if (hit) {
                if (!(npc->jumpFlags & 0x20000000)) {
                    MarioWork* m = marioGetPtr();
                    npc->jumpFlags |= 0x20000000;
                    npc->field_148 = npc->direction;
                    evtStopID(npc->regularEvtId);
                    if (!(npc->flags & 0x01000000)) {
                        npc->direction = reviseAngle(angleABf(npc->position.x, npc->position.z, m->position.x, m->position.z));
                    }
                }
            } else if (npc->jumpFlags & 0x20000000) {
                npc->jumpFlags &= ~0x20000000;
                if (npc->flags & 0x400000) {
                    npc->direction = npc->field_148;
                    evtStartID(npc->regularEvtId);
                } else {
                    npc->field_140 |= 0x10000000;
                }
            }
        }
        *(NpcEntry**)((u8*)mario + 0x1D4) = talk;
        if (wp->field_0x10 && (keyGetButtonTrg(0) & 0x100)) {
            npc = wp->field_0x10;
            data = gp->fbatData;
            if (data->mode != 1) {
                return;
            }
            data->mode = 2;
            FBAT_SUB(data) = 0;
            FBAT_NPC(data) = npc;
            *(u32*)npc->field_318 = 0;
            return;
        }
    }
    data = gp->fbatData;
    if (data->mode == 1) {
        u32* kind = (u32*)((u8*)data + 0x10);
        npc = fbatHitCheck(0x2361, kind);
        if (npc && data->mode == 1) {
            u32 k = *kind;
            FieldBattleData* d = gp->fbatData;
            if (d->mode == 1) {
                d->mode = 3;
                FBAT_SUB(d) = 0;
                FBAT_NPC(d) = npc;
                *(u32*)npc->field_318 = k;
            }
            switch (*kind) {
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
                    npc->direction = npc->field_148;
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
                npcGetWorkPtrInline()->field_0x10 = NULL;
            }
            break;
    }
}

#define FBAT_U32(d, off) (*(u32*)((u8*)(d) + (off)))
#define NPC_ENEMY_LEVEL(npc) (*(u8*)((u8*)*(void**)(npc)->battleInfo.groupSetup->enemyData + 0xE))

void BattleMajinaiDone(void);
extern s32 _evt_majinai_coin_up_effect[];
void marioChgMoveMotion(void);

void fbatBattleMode(void) {
    FieldBattleData* data = gp->fbatData;
    NpcEntry* npc = data->target;
    PouchData* pouch = pouchGetPtr();
    MarioWork* mario = marioGetPtr();
    FieldBattleInfo* info;
    NpcWork* wp;
    NpcEntry* entry;
    s32 i;
    s32 num;
    s32 result;
    s32 mult;
    s32 stolen;
    BOOL skip;
    BOOL win;
    EventEntry* evt;
    NpcBattleInfo* binfo;

    npc->rotation.y = 0.0f;
    switch (FBAT_SUB(data)) {
        case 0:
            if (dbg_battleskip == 1) {
                data->mode = 1;
                break;
            }
            if (!npc->battleInfo.groupSetup) {
                data->mode = 1;
                break;
            }
            if (gp->systemLevelFlags & 0x10) {
                data->mode = 1;
                break;
            }
            if (!npc->deadEvent) {
                data->mode = 1;
                break;
            }
            data->target->field_140 &= 0xF00;
            evtStopID(data->target->regularEvtId);
            info = &data->info;
            if (!(npc->battleInfo.field_4 & 0x10000000)) {
                if (pouchEquipCheckBadge(0x142) && NPC_ENEMY_LEVEL(npc) < pouch->level) {
                    skip = TRUE;
                    win = TRUE;
                    goto skipped;
                }
                if (pouchEquipCheckBadge(0x141) && (FBAT_U32(data, 0x10) & 0x01FE0000) &&
                    NPC_ENEMY_LEVEL(npc) < pouch->level) {
                    skip = TRUE;
                    win = TRUE;
                    goto skipped;
                }
            }
            if (dbg_battleskip == 2) {
                skip = TRUE;
                win = TRUE;
            } else {
                skip = FALSE;
                win = FALSE;
            }
        skipped:
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
                    for (i = 0, entry = wp->entries; i < num; i++, entry++) {
                        if (entry && (entry->flags & 2) && (entry->flags & 0x10000000)) {
                            entry->jumpFlags |= 0x10000;
                            evtStopID(entry->regularEvtId);
                            animPoseSetLocalTimeRate(entry->poseId, 0.0f);
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
                for (i = 0, entry = wp->entries; i < num; i++, entry++) {
                    if (entry && (entry->flags & 2) && (entry->flags & 0x10000000) &&
                        (entry->jumpFlags & 0x10000)) {
                        entry->jumpFlags &= ~0x10000;
                        evtStartID(entry->regularEvtId);
                        animPoseSetLocalTimeRate(entry->poseId, 1.0f);
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
                if (npc->battleInfo.stolenItems[0]) {
                    stolen = TRUE;
                } else if (npc->battleInfo.stolenItems[1]) {
                    stolen = TRUE;
                } else if (npc->battleInfo.stolenItems[2]) {
                    stolen = TRUE;
                } else if (npc->battleInfo.stolenItems[3]) {
                    stolen = TRUE;
                } else if (npc->battleInfo.stolenItems[4]) {
                    stolen = TRUE;
                } else if (npc->battleInfo.stolenItems[5]) {
                    stolen = TRUE;
                } else if (npc->battleInfo.stolenItems[6]) {
                    stolen = TRUE;
                } else if (npc->battleInfo.stolenItems[7]) {
                    stolen = TRUE;
                }
                data->mode = 1;
                if (result == 1 || result == 2) {
                    mult = 1;
                    if (BattleInformationGetResult(info) == 1) {
                        npc->btlCoinDropCount = info->field_0x14;
                    } else if (result == 1) {
                        npc->btlCoinDropCount = npc->field_316;
                    } else {
                        npc->btlCoinDropCount = 0;
                        mult = 0;
                        goto apply;
                    }
                    if (data->field_54C) {
                        mult = 3;
                    }
                    if (pouchEquipCheckBadge(0x139)) {
                        mult += pouchEquipCheckBadge(0x139);
                    }
                    if (npc->battleInfo.field_4 & 0x100) {
                        mult++;
                    }
                apply:
                    npc->btlCoinDropCount *= mult;
                    if (!stolen) {
                        npcGroupDead(npc, 0);
                        break;
                    }
                    if (npc->flags & 0x400) {
                        npc->field_108 = 0;
                    }
                    npc->wFbatHitCheckRelated = 90;
                    npc->field_140 &= ~0x100;
                    npc->field_140 |= 0x10000000;
                    if (npc->flags & 0x200) {
                        animPoseSetAnim(npc->poseId, npc->currentAnim, 1);
                    }
                    binfo = &npc->battleInfo;
                    for (i = 0; i < 8; i++) {
                        if (binfo->recoveredItems[i]) {
                            itemFlagOn(itemEntry(NULL, binfo->recoveredItems[i], 11, -1, 0,
                                                 npc->position.x, npc->position.y, npc->position.z),
                                       0x100);
                            binfo->recoveredItems[i] = 0;
                        }
                    }
                } else if (result == 4) {
                    if (npc->flags & 0x400) {
                        npc->field_108 = 0;
                    }
                    npc->field_140 |= 0x10000000;
                    marioSetMutekiTime(3000);
                    *(s16*)((u8*)mario + 0x2C0) = sysMsec2Frame(3000);
                    if (npc->flags & 0x200) {
                        animPoseSetAnim(npc->poseId, npc->currentAnim, 1);
                    }
                }
            }
            break;
    }
}

void _npcDead(NpcEntry* npc, s32 reason) {
    npc->field_140 |= 0x10;
    npc->jumpFlags |= 4;
    npc->koopaEncounterType = reason;
    if (npc->flags & 4) {
        fbatGetPointer()->deadInfo[0].mask |= 1 << npc->field_314;
    }
}

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

void npcGroupDead(NpcEntry* entry, BOOL reason) {
    if (entry->master) {
        entry = entry->master;
    }
    while (entry->prev) {
        entry = entry->prev;
    }
    _npcGroupDead(entry, reason);
}

NpcEntry* fbatNpcTalkCheck(void) {
    NpcWork* wp = npcGetWorkPtrInline();
    if (wp->field_0x10 && marioChkTalkable()) {
        return wp->field_0x10;
    }
    return NULL;
}

void fbatHitCheckAll(void) {
    fbatHitCheck(0x13f1, NULL);
}

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

static inline BOOL fbat_canHit(NpcEntry* npc) {
    MarioWork* m = marioGetPtr();
    NpcWork* wp = npcGetWorkPtrInline();
    if (FH(m, 0x0, u32) & 0x82000000) return FALSE;
    if (!(wp->flags & 1) && (FH(m, 0x0, u32) & 0xA)) return FALSE;
    if (FH(gp, 0x164, s32)) return FALSE;
    if (seqGetSeq() != 2) return FALSE;
    if (FH(m, 0x2E, u16) == 0x19) return FALSE;
    if (vivianGetStatus()) return FALSE;
    if (FH(m, 0x2E, u16) == 0x1F || FH(m, 0x2E, u16) == 0x20) return FALSE;
    if (FH(npc, 0x320, u16)) return FALSE;
    return TRUE;
}

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

void* fbatHitCheck(u32 flags, void* a1) {
    NpcEntry* npc = NULL;
    NpcEntry* hit = NULL;
    NpcWork* wp = npcGetWorkPtrInline();
    MarioWork* mario;
    FbatHitResult res;
    f32 dist;
    s32 total;
    s32 i;
    u32 soft;
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
        if (!noJump || FH(mario, 0x4C, s16) <= 0) {
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
                    if (FH(mario, 0x90, f32) >= FH(npc, 0x90, f32) + FH(npc, 0x150, f32)) continue;
                    if (FH(mario, 0x90, f32) + FH(mario, 0x1B8, f32) <= FH(npc, 0x90, f32)) continue;
                    dz = FH(mario, 0x94, f32) - FH(npc, 0x94, f32);
                    dx = FH(mario, 0x8C, f32) - FH(npc, 0x8C, f32);
                    dist = npc_sqrtf(dx * dx + dz * dz);
                    if (dist > 0.5f * (FH(mario, 0x1B4, f32) + FH(npc, 0x14C, f32))) continue;
                    if (dist >= res.dist) continue;
                    if (noJump && !(FH(npc, 0x1D4, u32) & 0x10000) && FH(mario, 0x4C, s16) <= 0) {
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
                    if ((FH(mario, 0x0, u32) & 0x20000) && !(FH(mario, 0x0, u32) & 0x10000) &&
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
            if ((flags & 0x10) && FH(mario, 0x4C, s16) > 0) break;
            if (!fbat_canHit(npc)) break;
            if (flags & 1) {
                MarioWork* m;
                s32 v;
                f32 f;
                f32 s1, c1, s2, c2;
                f32 x, y, z;
                u32 f1000;
                if (FH(mario, 0x2E, u16) != 0x12) break;
                r = 1.5f * FH(mario, 0x1B4, f32);
                angle = reviseAngle(FH(mario, 0x1A8, f32) - 90.0f + FH(camGetPtr(CAMERA_3D), 0x114, f32));
                m = marioGetPtr();
                animPoseGetAnimPosePtr(FH(m, 0x228 + marioAnimeId() * 4, s32));
                v = FH(m, 0x48, s32);
                if (v > 20) v = 10;
                f = v;
                m = marioGetPtr();
                {
                    s32 tbl[11] = {0, 0, 0, 0, 45, 60, 90, 100, 101, 101, 101};
                    if (f < 0.0f) f = 0.0f;
                    if (f >= 11.0f) f = 10.0f;
                    sincosf(&s1, &c1, angle);
                    sincosf(&s2, &c2, tbl[(s32)f]);
                }
                f1000 = flags & 0x1000;
                x = FH(m, 0x8C, f32) + s2 * (s1 * r);
                z = FH(m, 0x94, f32) + s2 * (c1 * r);
                y = FH(m, 0x90, f32) + r * c2;
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
                r = 1.5f * FH(mario, 0x1B4, f32);
                angle = reviseAngle(FH(mario, 0x1A8, f32) - 90.0f + FH(camGetPtr(CAMERA_3D), 0x114, f32));
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
            if ((flags & 0x10) && FH(mario, 0x4C, s16) > 0) break;
            if (!fbat_canHit(npc)) break;
            if (flags & 1) {
                MarioWork* m;
                f32 s, c, x, y, z;
                u32 f1000;
                if (FH(mario, 0x2E, u16) != 0x13) break;
                angle = marioGetAngleKaitenHammer();
                if (angle < 0.0f) break;
                r = 1.5f * FH(mario, 0x1B4, f32);
                m = marioGetPtr();
                sincosf(&s, &c, angle);
                f1000 = flags & 0x1000;
                x = s * r + FH(m, 0x8C, f32);
                z = c * r + FH(m, 0x94, f32);
                y = 15.0f + FH(m, 0x90, f32);
                npc = wp->entries;
                for (i = 0; i < total; i++, npc++) {
                    FH_NPC_FILTER(f1000, 2)
                    if (!_npcHitCheckSphere(npc, &dist, x, y, z, 12.0f)) continue;
                    if (dist >= res.dist) continue;
                    res.dist = dist;
                    hit = npc;
                    if (pouchGetHammerLv() < 3) {
                        *(volatile u32*)&res.kind = 0x200000;
                    } else {
                        *(volatile u32*)&res.kind = 0x400000;
                    }
                    if (!soft) fbatSetAttackAnnounce(res.kind);
                    break;
                }
            } else {
                u32 f1000;
                r = 1.5f * FH(mario, 0x1B4, f32);
                angle = reviseAngle(FH(mario, 0x1A8, f32) - 90.0f + FH(camGetPtr(CAMERA_3D), 0x114, f32));
                npc = wp->entries;
                f1000 = flags & 0x1000;
                for (i = 0; i < total; i++, npc++) {
                    FH_NPC_FILTER(f1000, 2)
                    if (!_npcHitCheckHammerAllMotion(npc, &dist, r, angle)) continue;
                    if (dist >= res.dist) continue;
                    res.dist = dist;
                    hit = npc;
                    if (pouchGetHammerLv() < 3) {
                        *(volatile u32*)&res.kind = 0x200000;
                    } else {
                        *(volatile u32*)&res.kind = 0x400000;
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
            if ((flags & 0x10) && FH(mario, 0x4C, s16) > 0) break;
            if (!fbat_canHit(npc)) break;
            b = flags & 1;
            if (b) {
                s32 st;
                if (party == NULL) break;
                if (FH(party, 0x33, u8) != 2) break;
                if (!(FH(party, 0x0, u32) & 0x100)) break;
                st = nokonokoGetStatus(party);
                if (st < 2 || st > 5) break;
            }
            if (!b) break;
            f1000 = flags & 0x1000;
            r = 0.5f * FH(party, 0xF4, f32);
            y = 0.5f * FH(party, 0xF0, f32) + FH(party, 0x5C, f32);
            x = FH(party, 0x58, f32);
            z = FH(party, 0x60, f32);
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
            if ((flags & 0x10) && FH(mario, 0x4C, s16) > 0) break;
            if (!fbat_canHit(npc)) break;
            if (!(flags & 1)) break;
            if (party == NULL) break;
            if (FH(party, 0x33, u8) != 3) break;
            if (!FH(gp->fbatData, 0x54D, u8)) break;
            npc = wp->entries;
            flags &= 0x1000;
            for (i = 0; i < total; i++, npc++) {
                FH_NPC_FILTER(flags, 8)
                if (!_npcHitCheckSphere(npc, &dist, FH(party, 0x58, f32), 0.5f * FH(party, 0xF0, f32) + FH(party, 0x5C, f32),
                                        FH(party, 0x60, f32), 30.0f)) continue;
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

NpcEntry* _npcHitCheckHammerAllMotion(NpcEntry* npc, f32* dist, f32 r, f32 angle) {
    f32 t;
    f32 d;
    NpcEntry* hit;

    for (t = 0.0f; t <= 11.0f; t += 1.0f) {
        f32 f = t;
        MarioWork* mario = marioGetPtr();
        s32 tbl[11] = {0, 0, 0, 0, 45, 60, 90, 100, 101, 101, 101};
        f32 c2, s2, c1, s1;
        f32 x, y, z;

        if (f < 0.0f) {
            f = 0.0f;
        }
        if (f >= 11.0f) {
            f = 10.0f;
        }
        sincosf(&s1, &c1, angle);
        sincosf(&s2, &c2, tbl[(s32)f]);
        x = mario->position.x + s2 * (s1 * r);
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

BOOL npcCheckInterrupt(NpcEntry* npc) {
    EventEntry* evt;
    u32 flags;

    evtGetPtrID(npc->regularEvtId);
    flags = npc->field_140;
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
            npc->field_140 &= 0xF00;
            npc->jumpFlags &= ~0x1000;
            npc->field_188 = 0;
            npc->moveSpeed = 0.0f;
            return TRUE;
        }
    }
    npc->field_140 &= 0xF00;
    npc->jumpFlags &= ~0x1000;
    return FALSE;
}

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
                for (i = 0; i < 16; i++) {
                    info->field_B0[i] = (u8)setup->field_20[i][0] + irand(setup->field_20[i][1] - setup->field_20[i][0] + 1);
                    ;
                }
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
        npc->field_316 = 0;
        if (info->groupSetup) {
            npc->field_316 = info->groupSetup->enemyData->mUnitKindParams->baseCoin;
        }
        npc->flags |= 0x10000000;
    }
}

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
        setup = areaDataPtr(areaName)->field_8;
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

void npcStopForOneEvent(NpcEntry* npc) {
    if (npc && npc->flags & 2 && npc->flags & 0x10000000) {
        npc->jumpFlags |= 0x10000;
        evtStopID(npc->regularEvtId);
        animPoseSetLocalTimeRate(npc->poseId, 0.0f);
    }
}

void npcStartForEvent(void) {
    NpcWork* wp;
    s32 i;
    s32 total;
    NpcEntry* entry;

    wp = npcGetWorkPtrInline();
    total = wp->total;
    entry = wp->entries;
    for (i = 0; i < total; i++, entry++) {
        npcStartForOneEvent(entry);
    }
}

void npcStartForOneEvent(NpcEntry* npc) {
    if (npc && npc->flags & 2 && npc->flags & 0x10000000 && npc->jumpFlags & 0x10000) {
        npc->jumpFlags &= ~0x10000;
        evtStartID(npc->regularEvtId);
        animPoseSetLocalTimeRate(npc->poseId, 1.0f);
    }
}

void npcSetColor(const char* name, GXColor color) {
    npcNameToPtr(name)->color = color;
}

void npcBlurOn(const char* name) {
    NpcEntry* npc = npcNameToPtr(name);

    npc->flags |= 0x100;
    npc->positionHistory[0] = npc->position;
    npc->positionHistory[1] = npc->position;
    npc->positionHistory[2] = npc->position;
    npc->positionHistory[3] = npc->position;
    npc->positionHistory[4] = npc->position;
}

void npcBlurOff(const char* name) {
    npcNameToPtr(name)->flags &= ~0x100;
}

s32 npcGetBtlSetupWork(NpcEntry* npc, s32 index) {
    return npc->battleInfo.btlSetupWork[index];
}

void npcSetBtlSetupWork(NpcEntry* npc, s32 index, s32 value) {
    npc->battleInfo.btlSetupWork[index] = value;
}

void npcSetSlave(NpcEntry* npc, NpcEntry* slave, s32 id) {
    slave->master = npc;
    npc->slaves[id] = slave;
}

void npcSetLink(NpcEntry* npc, NpcEntry* other) {
    npc->next = other;
    other->prev = npc;
}

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

USER_FUNC(_majinai_effect) {
    MarioWork* mario = marioGetPtr();
    EffectEntry* effect;

    if (isFirstCall) {
        event->userdatap[0] = effMajinaiEntry(0, mario->position.x, mario->position.y + mario->wPlayerCollisionBox.y + 16.0f, mario->position.z);
        effect = event->userdatap[0];
        ((f32*)effect->userdata)[4] = 0.8f;
        effSetName(event->userdatap[0], "mjef_coinup");
    }
    if (event->userdata[0] && effNameToPtr("mjef_coinup")) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

EVT_BEGIN(evt_majinai_effect_se_fld)
    CALL(btlevtcmd_ftomsec, 29, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_FLD_INCANT_CUBE1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 200, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_FLD_INCANT_CUBE2"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 90, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_FLD_INCANT_CUBE3"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 80, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_FLD_INCANT_CUBE4"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 5, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_FLD_INCANT_CUBE5"), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(evt_majinai_effect_se_btl)
    CALL(btlevtcmd_ftomsec, 29, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_BTL_INCANT_CUBE1"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 200, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_BTL_INCANT_CUBE2"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 90, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_BTL_INCANT_CUBE3"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 80, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_BTL_INCANT_CUBE4"), LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_ftomsec, 5, LW(10))
    WAIT_MS(LW(10))
    CALL(evt_snd_sfxon_3d, STRING("SFX_EVT_BTL_INCANT_CUBE5"), LW(0), LW(1), LW(2), 0)
    RETURN
EVT_END()

EVT_BEGIN(_evt_majinai_coin_up_effect)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    SPAWN_EVENT(evt_majinai_effect_se_fld)
    CALL(_majinai_effect)
    CALL(evt_msg_print, 0, PTR("msg_mj_coin_up"), 0, 0)
    CALL(_check, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print, 0, PTR("msg_mj_last"), 0, 0)
    END_IF
    RETURN
EVT_END()

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

void npcClearDeadInfo(void) {
    memset(gp->fbatData->deadInfo, 0, sizeof(gp->fbatData->deadInfo));
}

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
                            !strcmp(hitGetName(entry->field_0x300), "a_magu")) {
                            npcGroupDead(entry, 0x10);
                        }
                        break;
                }
            }
        }
    }
}

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

void fbatSandersBombTriggerOn(void) {
    gp->fbatData->sandersBombTrigger = TRUE;
}

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
    return cloudGetBreathPower(pos, npc->width) > 0.0f;
}

BOOL N_fbatPreventMarioEventChk(void) {
    s32 mode = gp->fbatData->mode;
    if (mode != 0 && mode != 1 && mode != 8) {
        return TRUE;
    }
    return FALSE;
}
