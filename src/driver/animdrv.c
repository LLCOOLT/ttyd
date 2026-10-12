/*
 * Warning, inlining hell
 */
#include "driver/animdrv.h"
#include "driver/dispdrv.h"
#include "driver/mapdrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include <math.h>

#include <stdio.h>

#include <string.h>

#define TESTHEAP_SIZE (u32)(1.5 * 1024 * 1024)
#define PI 3.14159265358979323846264338327950288419716939937510f

extern GlobalWork* gp;
extern int sprintf(char* str, const char* format, ...);
extern double tan(double arg);

//.data
u8 _vivihimoData[0xC00]; // TODO: embed the actual data? gets overwritten by a/vivian.bin in animInit()

//.bss
Mtx g_modeling_mtx_stack[32];
static AnimationWork work;
f32 tanfTbl[0xB2];

//.sdata
s32 vivihimoTailGroupNo[4] = { 0, 2, -1, -1 };
void* vivihimoData[4] = {
    NULL,
    &_vivihimoData,
    &_vivihimoData + 0x400,
    &_vivihimoData + 0x800,
};
static AnimationWork* wp = &work;
s32 _dummy = -1;
static s32 tbl[4] = { 2, 1, 3, 0 };

//.sbss
u32 anim_ext_tex_size;
Mtx mtx; // TODO: make sure it's put in .sbss
s32 g_modeling_mtx_lv;
Mtx* g_modeling_mtx;

// local declarations
void animPoseRefresh(void);
void animPaperPoseDisp(CameraId camId, void* param);
void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
void animPaperPoseDispSub(s32 unused, AnimationPose* pose);
void renderProc(s32 shapeId, s32 unused);
void pushGXModelMtx_JointNode__(AnimPoseNode* node, f32 sx, f32 sy, f32 sz);
void pushGXModelMtx_TransformNode__(AnimPoseNode* node);
void evalProc(s32 parentId, s32 groupId);

inline const char* animGetTexName(const char* name) {
    void** data = wp->mp_ag2tg->data;
    s32 size;
    s32 i;
    char* entry;

    size = (s32)data[1];
    entry = data[0];

    for (i = 0; i < size; entry += 0x20, i += 0x20) {
        if (!strcmp(entry, name)) {
            return entry + 0x20;
        }
    }
    return "";
}

AnimationWork* animGetPtr(void) {
    return wp;
}

OSTime animTimeGetTime(BOOL globalTime) {
    if (globalTime == FALSE) {
        return OSTicksToMilliseconds(gp->renderFieldTime);
    }
    return OSTicksToMilliseconds(gp->renderTime);
}

void initTestHeap(void) {
    if (!wp->testHeap) { // allocate 1.5MiB test heap
        wp->testHeap = __memAlloc(HEAP_DEFAULT, TESTHEAP_SIZE);
    }
    wp->testAlloc = (u32)wp->testHeap;
}

// heavily inlined
void* testAlloc(u32 size) {
    void* alloc = (void*)wp->testAlloc;

    if (size & 31) {
        size += 32 - (size & 31);
    }
    wp->testAlloc += size;
    if ((u32)wp->testAlloc >= (u32)wp->testHeap + TESTHEAP_SIZE) { // need to allocate more
        animPoseRefresh();
        alloc = testAlloc(size);
    }
    return alloc;
}

void animInit(void) {
    int i;
    FileEntry* file;

    wp->totalFiles = 64; // TODO: #define these?
    wp->totalTextures = 64;
    wp->totalPoses = 256;
    wp->mFloatScratchRP = 1024;
    wp->mFloatScratchWP = 0;
    wp->files = __memAlloc(HEAP_DEFAULT, sizeof(AnimationPoseFile) * wp->totalFiles);
    wp->textures = __memAlloc(HEAP_DEFAULT, sizeof(AnimationTextureFile) * wp->totalTextures);
    wp->poses = __memAlloc(HEAP_DEFAULT, sizeof(AnimationPose) * wp->totalPoses);
    wp->mbUseFloatScratch = 0;
    wp->mpFloatScratch = __memAlloc(HEAP_DEFAULT, sizeof(Vec) * wp->mFloatScratchRP);

    wp->mpTexObjs[0] = NULL;
    wp->mpTexObjs[1] = NULL;
    wp->mpCurTexObj = NULL;

    wp->mpTexDatas[0] = NULL;
    wp->mpTexDatas[1] = NULL;
    wp->mpCurTexData = NULL;

    wp->paperMtxPtr[0] = NULL;
    wp->paperMtxPtr[1] = NULL;
    wp->paperMtxPtr[2] = NULL;

    wp->field_0xD8 = 1;
    wp->field_0xDC = 1;

    wp->testHeap = NULL;
    wp->inBattle = FALSE;
    initTestHeap(); // inlined

    for (i = 0; i < 0xB2; i++) {
        tanfTbl[i] = (f32)tan(MTXDegToRad(i - 0x59));
    }
    file = fileAllocf(0, "a/vivian.bin");
    if (file) {
        memcpy_as4(vivihimoData[1], *file->data, sizeof(_vivihimoData));
        memcpy_as4(vivihimoTailGroupNo, (void*)((u32)*file->data + sizeof(_vivihimoData)), sizeof(vivihimoTailGroupNo));
        fileFree(file);
    }
    fileSetCurrentArchiveType(0);
    wp->mp_ag2tg = fileAllocf(0, "a/ag2tg.bin");
}

void animMain(void) {
    dispEntry(CAMERA_OFFSCREEN, 0.0f, 1, animPaperPoseDisp, NULL);
}

inline AnimationPoseData* animPoseGetBaseData(AnimationPose* pose) {
    return *wp->files[pose->fileId].handle->data;
}

#define animPoseGetBaseData(pose) (*(AnimationPoseData**)(wp->files[(pose)->fileId].handle->data))

// heavily inlined, TODO helper function for that AnimPoseData* data, copy of animPoseGetAnimBaseDataPtr with AnimPose*
// arg
void animPose_AllocBuffer(AnimationPose* pose) {
    pose->mpBufferVtxPos = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferPosNum);
    pose->mpVtxArrayPos = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferPosNum);

    pose->mpBufferVtxNrm = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferNrmNum);
    pose->mpVtxArrayNrm = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferNrmNum);

    pose->mpBufferGroupVisibility = testAlloc(sizeof(u8) * animPoseGetBaseData(pose)->mBufferVisibilityNum);
    pose->mpGroupVisibility = pose->mpBufferGroupVisibility;

    pose->mpBufferNode = testAlloc(sizeof(AnimPoseNode*) * animPoseGetBaseData(pose)->mBufferNodeNum);
    pose->mpNodes = testAlloc(sizeof(AnimPoseNode*) * animPoseGetBaseData(pose)->mBufferNodeNum);

    pose->mpBufferTexAnimEntries = testAlloc(sizeof(AnimTexMtx) * animPoseGetBaseData(pose)->mBufferTexAnimNum);
    pose->mpTexAnimEntries = pose->mpBufferTexAnimEntries;

    pose->lastFrameZero = -1;
}

// heavily inlined
void animPoseRefresh(void) {
    int i;

    initTestHeap(); // inline
    for (i = 0; i < wp->totalPoses; i++) {
        AnimationPose* pose = &wp->poses[i]; // inline
        if (pose->flags) {
            // TODO: cleanup in rewrite?
            if ((!wp->inBattle || pose->type != 0) && (wp->inBattle || pose->type != 1)) {
                animPose_AllocBuffer(pose);
                pose->lastFrameZero = -1; // TODO: redundant?
            }
        }
    }
}

void animPoseBattleInit(void) {
    wp->inBattle = TRUE;
    animPoseRefresh();
}

s32 animPoseEntry(const char* animName, s32 type) {
    AnimationPose *pose, *temp;
    AnimationPoseFile *file, *tempfile;
    AnimationTextureFile *texture, *temptex;
    AnimationPoseData* data;
    s32 poseId, fileId, texId;
    s32 check, i;
    char textureName[256];

    switch (type) {
        case 0:
            fileSetCurrentArchiveType(1);
            break;
        case 1:
            fileSetCurrentArchiveType(2);
            break;
        case 2:
            fileSetCurrentArchiveType(0);
            break;
    }

    for (i = 0, poseId = 0; i < wp->totalPoses; i++, poseId++) {
        temp = &wp->poses[i];
        if (!temp->flags) {
            pose = temp;
            goto label_1;
        }
    }
    pose = NULL;
    poseId = -1;
label_1:
    pose->flags |= 1;
    pose->typeFlags = 0;
    pose->references = 0;

    check = wp->totalFiles;
    for (i = 0; i < check; i++) {
        file = &wp->files[i];
        if (!file->active) {
            data = *file->handle->data;
            if (!strcmp(data->fileName, animName)) {
                file->references++;
                goto label_5;
            }
        }
    }

    for (i = 0, fileId = 0; i < wp->totalFiles; i++, fileId++) {
        tempfile = &wp->files[i];
        if (!tempfile->active) {
            file = tempfile;
            goto label_2;
        }
    }
    file = NULL;
    fileId = -1;
label_2:
    file->active = TRUE;
    file->references++;
    file->handle = fileAllocf(5, "%s/%s", "a", animName);

    if (file->handle) {
        fileId = -2;
        file->active = FALSE;
        file->references--;
    } else {
        data = *file->handle->data;
        if (!data) {
            fileFree(file->handle);
            fileId = -2;
            file->active = FALSE;
            file->references--;
        } else {
            sprintf(textureName, "%s/%s-", "a", data->textureName);
            check = wp->totalTextures;
            for (i = 0; i < check; i++) {
                texture = &wp->textures[i];
                if (texture->active) {
                    if (texture->handle) {
                        if (!strcmp(texture->handle->filename, textureName)) {
                            texture->references++;
                            goto label_4;
                        }
                    }
                }
            }

            for (i = 0, texId = 0; i < wp->totalTextures; i++, texId++) {
                temptex = &wp->textures[i];
                if (!temptex->active) {
                    texture = temptex;
                    goto label_3;
                }
            }
            texture = NULL;
            texId = -1;
        label_3:
            texture->active = TRUE;
            texture->references++;
            texture->handle = fileAlloc(textureName, 4);
        label_4:
            file->textureId = texId;
        }
    }
label_5:
    pose->fileId = fileId;
    if (pose->fileId == -2) {
        pose->flags = 0;
        return -2;
    }
    pose->animId = 0;
    pose->localTime = animTimeGetTime(type); // inline
    pose->lastFrameZero = -1;
    pose->lastFrameTime = 0.0f;
    pose->field_0x80 = 0;
    pose->loopTime = 0.0f;
    pose->field_0x70 = 0.0f;
    pose->rotationY = 0.0f;
    pose->field_0x7C = 0.0f;
    pose->type = type;
    pose->paperId = -1;
    animPose_AllocBuffer(pose);
    pose->gxCallback = NULL;
    pose->disableDraw = 0;
    pose->materialFlag = 0;
    pose->materialLightFlag = 0;
    pose->materialColor = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    pose->materialColor2 = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    pose->field_0xFC = 1.0f;
    pose->field_0xF8 = 1.0f;
    pose->field_0x100 = 0.0f;
    pose->localTimeRate = 1.0f;
    MTXIdentity(pose->matrix);
    if (!strcmp(animName, "tst_vivi")) {
        pose->vivianType = 1;
        pose->vivianGroupNo = &vivihimoTailGroupNo[0];
    } else if (!strcmp(animName, "c_vivian")) {
        pose->vivianType = 1;
        pose->vivianGroupNo = &vivihimoTailGroupNo[1];
    } else if (!strcmp(animName, "c_maririn")) {
        pose->vivianType = 2;
        pose->vivianGroupNo = &vivihimoTailGroupNo[2];
    } else if (!strcmp(animName, "c_majyorin")) {
        pose->vivianType = 3;
        pose->vivianGroupNo = &vivihimoTailGroupNo[3];
    } else { // if none match
        pose->vivianType = 0;
        pose->vivianGroupNo = &_dummy;
    }
    pose->dispCallback = NULL;
    pose->dispUserDataCallback = NULL;
    return poseId;
}

s32 animPaperPoseEntry(const char* animName, s32 group) {
    AnimationPose* pose;
    s32 i;

    for (i = 0; i < wp->totalPoses; i++) {
        pose = animPoseGetAnimPosePtr(i);
        if (pose->flags & 1 && pose->typeFlags & 1 && pose->typeFlags & 2 && pose->type == group &&
            !strcmp(animPoseGetBaseData(pose)->fileName, animName)) {
            break;
        }
    }
    if (i == wp->totalPoses) {
        i = -1;
    }
    if (i >= 0) {
        pose = &wp->poses[i];
        pose->references++;
        return i;
    }
    i = animPoseEntry(animName, group);
    if (i == -2) {
        return i;
    }
    pose = &wp->poses[i];
    pose->typeFlags = 3;
    pose->references = 0;
    pose->flags |= 1;
    return i;
}

BOOL animEffectAsync(const char* animName, u32 group) {
    s32 model, anim;

    switch (group) {
        case 0:
            fileSetCurrentArchiveType(1);
            break;
        case 1:
            fileSetCurrentArchiveType(2);
            break;
        case 2:
            fileSetCurrentArchiveType(0);
            break;
    }
    model = fileAsyncf(5, NULL, "%s/%s", "a", animName);
    anim = fileAsyncf(4, NULL, "%s/%s-", "a", animGetTexName(animName));
    if (model == -1) {
        return TRUE;
    }
    if ((u32)model == 0) {
        return FALSE;
    }
    if (anim == -1) {
        return TRUE;
    }
    if ((u32)anim == 0) {
        return FALSE;
    }
    return TRUE;
}

void animPosePeraOn(s32 poseId) {
    wp->poses[poseId].flags |= 8;
}

void animPosePeraOff(s32 poseId) {
    wp->poses[poseId].flags &= ~8;
}

void animPosePaperPeraOn(s32 poseId) {
    AnimationPose* dst = &wp->poses[wp->poses[poseId].paperId];
    AnimationPose* src = &wp->poses[poseId];

    dst->flags |= 8;
    dst->field_0x70 = src->field_0x70;
    dst->rotationY = src->rotationY;
    dst->field_0x7C = src->field_0x7C;
}

void animPosePaperPeraOff(s32 poseId) {
    wp->poses[wp->poses[poseId].paperId].flags &= ~8;
}

void animPoseSetLocalTimeRate(s32 poseId, f32 localTimeRate) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->localTimeRate = localTimeRate;
}

void animPoseSetLocalTime(s32 poseId, f32 localTimeFrames) {
    AnimationPose *pose, *pera;

    pose = &wp->poses[poseId];
    pose->localTime = animTimeGetTime(pose->type) - (u64)(16.666666f * localTimeFrames);
    pose->mLocalTimeInit = pose->localTime;
    if (pose->paperId != -1) {
        pera = &wp->poses[pose->paperId];
        if (!(pera->typeFlags & 2)) {
            pera->localTime = pose->localTime;
        }
    }
}

void animPoseSetStartTime(s32 poseId, OSTime startTime) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->localTime = startTime;
}

#define animPosePaperAnimId(pose) (*(s32*)(pose)->field_0x94)
#define animPoseGetBaseDataId(id) (*(AnimationPoseData**)(wp->files[wp->poses[id].fileId].handle->data))

inline s32 animPoseGetAnimIdx(AnimationPoseData* data, const char* name) {
    s32 count = data->mAnimCount;
    s32 i = (s32)name;

    if (i < 0) {
        for (i = 0; i < count; i++) {
            if (!strcmp(data->mpAnims[i].name, name)) {
                return i;
            }
        }
    }
    else if (i < count) {
        return i;
    }
    return 0;
}

void animPoseSetAnim(s32 poseId, const char* animName, BOOL reset) {
    AnimationPose* pose;
    s32 animId;

    pose = &wp->poses[poseId];
    animId = animPoseGetAnimIdx(animPoseGetBaseData(pose), animName);
    if (reset || animId != pose->animId) {
        pose->animId = animId;
        if (pose->paperId != -1 && pose->flags & 2) {
            pose->flags |= 4;
        }
        pose->localTime = animTimeGetTime(pose->type);
        pose->lastFrameZero = -1;
        pose->lastFrameTime = 0.0f;
        pose->field_0x80 = 0;
        pose->loopTime = 0.0f;
    }
}

s32 animPaperPoseGetId(const char* animName, s32 group) {
    AnimationPose* pose;
    s32 i;

    for (i = 0; i < wp->totalPoses; i++) {
        pose = &wp->poses[i];
        if (pose->flags & 1 && pose->typeFlags & 1 && pose->typeFlags & 2 && pose->type == group &&
            !strcmp(animPoseGetBaseData(pose)->fileName, animName)) {
            break;
        }
    }
    if (i == wp->totalPoses) {
        i = -1;
    }
    return i;
}

void animPoseSetPaperAnimGroup(s32 poseId, const char* animName, BOOL someflag) {
    AnimationPose* pose = &wp->poses[poseId];

    if (!animName) {
        pose->paperId = -1;
        animPoseSetMaterialLightFlagOff(poseId, 1);
        return;
    }
    pose->paperId = animPaperPoseGetId(animName, pose->type);
    if (pose->paperId < 0) {
        pose->paperId = animPaperPoseGetId(animName, 2);
    }
    animPosePaperAnimId(pose) = -1;
    pose->mLocalTimeInit = animTimeGetTime(pose->type);
    if (someflag) {
        pose->flags |= 2;
        pose->flags |= 4;
    }
    else {
        pose->flags &= ~2;
        pose->flags &= ~4;
    }
    animPoseSetMaterialLightFlagOn(poseId, 1);
}

void animPoseSetPaperAnim(s32 poseId, const char* animName, BOOL reset) {
    AnimationPose* pose = &wp->poses[poseId];
    s32 id;
    AnimationPoseData* data;

    animPosePaperAnimId(pose) = animPoseGetAnimIdx(data = animPoseGetAnimBaseDataPtr(pose->paperId), animName);
    pose->mLocalTimeInit = animTimeGetTime(pose->type);
    id = pose->paperId;
    if (id != -1 && !(*(u32*)((u8*)wp->poses + id * sizeof(AnimationPose) + 4) & 2)) {
        animPoseMain(pose->paperId);
    }
}

void animPoseSetEffect(s32 poseId, const char* animName, BOOL someflag) {
    AnimationPose* pose = &wp->poses[poseId];
    AnimationPose* paper;
    s32 id;

    if (pose->paperId != -1) {
        if (animName && !strcmp(animPoseGetAnimBaseDataPtr(pose->paperId)->fileName, animName) &&
            (s32)((pose->flags >> 1) & 1) == someflag) {
            return;
        }
        animPaperPoseRelease(pose->paperId);
    }
    if (!animName) {
        pose->paperId = -1;
        animPoseSetMaterialLightFlagOff(poseId, 1);
        return;
    }
    id = animPoseEntry(animName, pose->type);
    if (id != -2) {
        paper = &wp->poses[id];
        paper->typeFlags = 1;
        paper->references = 0;
        paper->flags |= 1;
    }
    pose->paperId = id;
    animPosePaperAnimId(pose) = -1;
    pose->mLocalTimeInit = animTimeGetTime(pose->type);
    if (someflag) {
        pose->flags |= 2;
        pose->flags |= 4;
    }
    else {
        pose->flags &= ~2;
    }
    animPoseSetMaterialLightFlagOn(poseId, 1);
}

void animPoseSetEffectAnim(s32 poseId, const char* animName, BOOL reset) {
    AnimationPose* pose = &wp->poses[poseId];

    if (pose->paperId != -1) {
        animPoseSetAnim(pose->paperId, animName, reset);
    }
}

void animPoseSetGXFunc(s32 poseId, void (*callback)(s32 wXluStage), BOOL disableDraw) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->gxCallback = callback;
    pose->disableDraw = disableDraw;
}

f32 animPoseGetRadius(s32 poseId) {
    return 2.0f * animPoseGetAnimBaseDataPtr(poseId)->radius;
}

f32 animPoseGetHeight(s32 poseId) {
    return 2.0f * animPoseGetAnimBaseDataPtr(poseId)->height;
}

f32 animPoseGetLoopTimes(s32 id) {
    AnimationPose* pose = &wp->poses[id];
    return pose->loopTime;
}

BOOL animPoseGetPeraEnd(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    if (!(pose->flags & 8)) {
        return TRUE;
    }
    if (__fabs(pose->field_0x7C - pose->rotationY) < 10.0) {
        return TRUE;
    }
    return FALSE;
}

void animPoseSetMaterialFlagOn(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialFlag |= mask;
}

void animPoseSetMaterialFlagOff(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialFlag &= ~mask;
}

void animPoseSetMaterialLightFlagOn(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialLightFlag |= mask;
}

void animPoseSetMaterialLightFlagOff(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialLightFlag &= ~mask;
}

void animPoseSetMaterialEvtColor(s32 poseId, GXColor color) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialColor = color;
}

u32 animPoseGetMaterialFlag(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->materialFlag;
}

u32 animPoseGetMaterialLightFlag(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->materialLightFlag;
}

GXColor animPoseGetMaterialEvtColor(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->materialColor;
}

asm void animPoseMain(s32 poseId) {
    nofralloc
    blr
}

void pushGXModelMtx_TransformNode__(AnimPoseNode* node) {
    Mtx trans, scale, rot, tmp;
    Mtx sc1, sc2, sc3;
    Mtx rc1, rc2, rc3;
    MtxPtr p;
    u32 flags;
    f32 sx, sy, sz;
    f32 rx, ry, rz;
    f32 rcx, rcy, rcz;
    f32 scx, scy, scz;
    f32 rtx, rty, rtz;
    f32 stx, sty, stz;
    f32 tx, ty, tz;

    flags = 0;
    tx = node->mTranslation.x;
    ty = node->mTranslation.y;
    tz = node->mTranslation.z;
    sx = node->mScale.x;
    sy = node->mScale.y;
    sz = node->mScale.z;
    rx = 2.0f * node->mRot1.x;
    ry = 2.0f * node->mRot1.y;
    rz = 2.0f * node->mRot1.z;
    rcx = node->mRotationCenter.x;
    rcy = node->mRotationCenter.y;
    rcz = node->mRotationCenter.z;
    scx = node->mScaleCenter.x;
    scy = node->mScaleCenter.y;
    scz = node->mScaleCenter.z;
    rtx = node->mRotationTranslation.x;
    rty = node->mRotationTranslation.y;
    rtz = node->mRotationTranslation.z;
    stx = node->mScaleTranslation.x;
    sty = node->mScaleTranslation.y;
    stz = node->mScaleTranslation.z;

    if (tx || ty || tz) {
        PSMTXTrans(trans, tx, ty, tz);
        flags |= 1;
    }
    if (sx != 1.0f || sy != 1.0f || sz != 1.0f) {
        PSMTXScale(scale, sx, sy, sz);
        flags |= 2;
    }
    if (scx != 0.0f || scy != 0.0f || scz != 0.0f) {
        if (flags & 2) {
            PSMTXTrans(sc2, -scx, -scy, -scz);
            PSMTXTrans(sc1, scx, scy, scz);
            PSMTXTrans(sc3, stx, sty, stz);
            PSMTXConcat(sc3, sc1, tmp);
            PSMTXConcat(tmp, scale, tmp);
            PSMTXConcat(tmp, sc2, scale);
        }
        else if (stx || sty || stz) {
            PSMTXTrans(scale, stx, sty, stz);
            flags |= 2;
        }
    }
    PSMTXIdentity(rot);
    if (rz) {
        PSMTXRotRad(tmp, 'z', 0.017453292f * rz);
        PSMTXConcat(rot, tmp, rot);
        flags |= 4;
    }
    if (ry) {
        PSMTXRotRad(tmp, 'y', 0.017453292f * ry);
        PSMTXConcat(rot, tmp, rot);
        flags |= 4;
    }
    if (rx) {
        PSMTXRotRad(tmp, 'x', 0.017453292f * rx);
        PSMTXConcat(rot, tmp, rot);
        flags |= 4;
    }
    if (rcx != 0.0f || rcy != 0.0f || rcz != 0.0f) {
        if (flags & 4) {
            PSMTXTrans(rc2, -rcx, -rcy, -rcz);
            PSMTXTrans(rc1, rcx, rcy, rcz);
            PSMTXTrans(rc3, rtx, rty, rtz);
            PSMTXConcat(rc3, rc1, tmp);
            PSMTXConcat(tmp, rot, rot);
            PSMTXConcat(rot, rc2, rot);
        }
        else if (rtx || rty || rtz) {
            PSMTXTrans(rot, rtx, rty, rtz);
            flags |= 4;
        }
    }
    g_modeling_mtx_lv++;
    g_modeling_mtx = &g_modeling_mtx_stack[g_modeling_mtx_lv];
    switch (flags) {
        case 0:
            PSMTXIdentity(tmp);
            p = tmp;
            break;
        case 1:
            p = trans;
            break;
        case 2:
            p = scale;
            break;
        case 3:
            PSMTXConcat(trans, scale, tmp);
            p = tmp;
            break;
        case 4:
            p = rot;
            break;
        case 5:
            PSMTXConcat(trans, rot, tmp);
            p = tmp;
            break;
        case 6:
            PSMTXConcat(rot, scale, tmp);
            p = tmp;
            break;
        case 7:
            PSMTXConcat(trans, rot, tmp);
            PSMTXConcat(tmp, scale, trans);
            p = trans;
            break;
    }
    PSMTXConcat(g_modeling_mtx_stack[g_modeling_mtx_lv - 1], p, g_modeling_mtx_stack[g_modeling_mtx_lv]);
}
// pushGXModelMtx_JointNode__

asm void animSetMaterial_Texture(s32 texCount, s32* texIdRemap, AnimPoseTexEntry* pTexEntries, AnimTexMtx* animEntries,
                             s32 texBindsCapacity, AnimTexBind* texBinds, AnimationTextureFile* texFile) {
    nofralloc
    blr
}

inline BOOL animSetMaterial_ChangeTexture(AnimationPoseData* data, AnimPoseShapeDraw* draw, AnimationPose* pose,
                                          Mtx mtx, void** texData, GXTexObj* texObj, s32 texType) {
    AnimPoseTexEntry* texEntry;
    AnimTexMtx* texAnim;
    AnimTexBind* bind;
    s32 bindCount, texCount;
    s32 dataId, bindId, frameExt;
    GXTexObj* smartObj;
    int i;

    bind = data->texBinds;
    bindCount = data->texBindCount;
    texAnim = pose->mpTexAnimEntries;
    texEntry = data->texData;
    texCount = draw->texCount;

    for (i = 0; i < texCount; i++) {
        dataId = draw->texDataIds[texCount - i - 1];
        frameExt = texAnim[dataId].mTexBindIdx;
        bindId = texEntry[dataId].bindId + frameExt;
        if (bindId < 0 || bindId >= bindCount) {
            bindId = 0;
            //"Error: animSetMaterial_ChangeTexture: テクスチャがありません frameExt=%d\n"
            printf("Error: animSetMaterial_ChangeTexture: "
                   "\x83\x65\x83\x4E\x83\x58\x83\x60\x83\x83\x82\xAA\x82\xA0\x82\xE8\x82\xDC\x82\xB9\x82\xF1 "
                   "frameExt=%d\n",
                   frameExt);
        }
        if (bind[bindId].texType == texType) {
            if (texObj) {
                smartObj = smartTexObj(texObj, texData);
                GXLoadTexObj(smartObj, i);
                if (mtx) {
                    GXLoadTexMtxImm(mtx, GX_TEXMTX0 + (u32)(i * 3), GX_MTX2x4);
                    GXSetTexCoordGen(i, GX_TG_MTX2x4, GX_TG_TEX0 + i, GX_TEXMTX0 + (u32)(i * 3));
                } else {
                    GXSetTexCoordGen(i, GX_TG_MTX2x4, GX_TG_TEX0 + i, GX_IDENTITY);
                }
            }
            return TRUE;
        }
    }
    return FALSE;
}

// materialProc

// I'm so sorry, whoever gets tasked with matching this function
// note: I detect at least 8 inlined functions here, good luck finding the separation
void renderProc(s32 shapeId, s32 unused) {
    CameraEntry* camera;
    AnimationPoseData* data;
    AnimPoseShape *shapes, *shape;
    AnimPoseShapeDraw *draws, *draw;
    s32 dispMode, drawId;
    s32 posFirstVtx, nrmFirstVtx, clr0FirstVtx;

    f32* buffer;
    s32 nrmVtxSize;
    s32 texCount;
    AnimationPose* pose;
    Mtx* mtx;
    GXTexObj* texObj;
    BOOL texChange1, check1, texChange2, check2;
    GXTexObj* currTexObj;
    u8* texIds;
    s32* firstId;
    AnimDrawCallEntry* drawCall;
    s32 drawCallCount;
    GXColor* clr0VtxPtr;
    s32 posFirstId, nrmFirstId, clr0FirstId;
    Vec *nrmVtxPtr, *posVtxPtr;

    s32 count;
    u16 *posIndexPtr, *nrmIndexPtr, *clr0IndexPtr, *texIndexPtr;
    s32 firstDrawId;
    s32 index;
    s32 texIndex;

    int i, j, k, l;

    // stack variables
    s32 clr0VtxSize, posVtxSize; // TODO: make sure stack, +0xB0, +0xAC
    s32 drawCount;               // TODO: make sure stack, +0xA8
    Mtx camMtx, invCamMtx;
    f32* texVtxIndices[8];
    Vec lightPos, lightPos2; // TODO: rename? 2 is probably implicit stack copy

    if (shapeId != -1) {
        camera = camGetCurPtr();
        MTXConcat(camera->view, *g_modeling_mtx, camMtx);
        GXLoadPosMtxImm(camMtx, 0);
        MTXInvXpose(camMtx, invCamMtx);
        GXLoadNrmMtxImm(invCamMtx, 0);
        GXSetCurrentMtx(0);

        data = wp->mpCurPoseData;
        shapes = data->shapes;
        draws = data->draws;
        shape = &shapes[shapeId];
        dispMode = shape->dispMode;
        drawId = shape->shapeDrawStart;
        posFirstVtx = shape->vtxPos.first;
        nrmFirstVtx = shape->vtxNrm.first;
        clr0FirstVtx = shape->vtxClr0.first;
        drawCount = shape->shapeDrawCount;
        draw = &draws[drawId];

        if ((dispMode == 0 && wp->currDispMode == 2) || dispMode == wp->currDispMode ||
            wp->mpCurPose->materialColor.a != 0xFF || wp->mpCurPose->materialColor2.a != 0xFF) {
            GXSetCullMode(tbl[shape->cullMode]);
            data = wp->mpCurPoseData;
            posVtxSize = (s32)sizeof(Vec) * posFirstVtx;
            clr0VtxSize = (s32)sizeof(GXColor) * clr0FirstVtx;
            nrmVtxSize = (s32)sizeof(Vec) * nrmFirstVtx;
            buffer = data->texVtxBuffer;
            texVtxIndices[0] = &buffer[2 * shape->vtxTex[0].first];
            texVtxIndices[1] = &buffer[2 * shape->vtxTex[1].first];
            texVtxIndices[2] = &buffer[2 * shape->vtxTex[2].first];
            texVtxIndices[3] = &buffer[2 * shape->vtxTex[3].first];
            texVtxIndices[4] = &buffer[2 * shape->vtxTex[4].first];
            texVtxIndices[5] = &buffer[2 * shape->vtxTex[5].first];
            texVtxIndices[6] = &buffer[2 * shape->vtxTex[6].first];
            texVtxIndices[7] = &buffer[2 * shape->vtxTex[7].first];

            for (i = 0; i < drawCount; i++, draw++) {
                texCount = draw->texCount;
                if (!wp->mpCurPose->disableDraw) {
                    lightPos = (Vec){ 0.0f, 0.0f, 0.0f };
                    MTXMultVec(*g_modeling_mtx, &lightPos, &lightPos);
                    lightPos2 = lightPos;
                    mapSetMaterialLight(wp->mpCurPose->materialLightFlag, lightPos2);
                    animSetMaterial_Texture(draw->texCount, draw->texDataIds, wp->mpCurPoseData->texData,
                                            wp->mpCurPose->mpTexAnimEntries, wp->mpCurPoseData->texBindCount,
                                            wp->mpCurPoseData->texBinds,
                                            &wp->textures[wp->files[wp->mpCurPose->fileId].textureId]);
                    mapSetMaterialLastStageBlend(wp->mpCurPose->materialFlag, wp->mpCurPose->materialColor,
                                                 wp->mpCurPose->materialColor2);
                    camera = camGetPtr(CAMERA_3D);
                    if (camGetCurPtr() == camera) {
                        mapSetMaterialFog();
                    }
                    mapSetMaterialTev(texCount, draw->drawMode, wp->mpCurPose->materialFlag, *g_modeling_mtx);
                }
                pose = wp->mpCurPose;
                if (pose->typeFlags) {
                    texChange1 = animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, *wp->paperMtxPtr[0],
                                                               wp->mpTexDatas[0], wp->mpTexObjs[0], 1);
                    check1 = texChange1;
                    if (!texChange1) {
                        texChange2 = animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, *wp->paperMtxPtr[1],
                                                                   wp->mpTexDatas[1], wp->mpTexObjs[1], 2);
                        check1 = texChange2;
                        check2 = texChange2;
                    } else {
                        check2 = FALSE;
                    }

                    if (check1 && (texChange1 && !wp->field_0xD8 || check2 && !wp->field_0xDC) && !draw->drawMode) {
                        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
                    }
                    if (check1 && !draw->drawMode) {
                        currTexObj = wp->mpCurTexObj;
                        if (currTexObj) {
                            smartTexObj(currTexObj, wp->mpCurTexData);
                            if (wp->currDispMode != 3) {
                                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                                GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                                GXSetZCompLoc(GX_FALSE);
                                GXSetAlphaCompare(GX_GEQUAL, 0x80u, GX_AOP_OR, GX_NEVER, 0);
                            }
                            texObj = wp->mpTexObjs[texChange1 == 0];
                            if (texObj) {
                                GXLoadTexObj(texObj, GX_TEXMAP0);
                                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE,
                                                  GX_PTIDENTITY);
                                GXLoadTexMtxImm(*wp->paperMtxPtr[texChange1 == 0], GX_TEXMTX0, GX_MTX2x4);
                            }
                            GXLoadTexObj(currTexObj, GX_TEXMAP1);
                            GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE,
                                              GX_PTIDENTITY);
                            GXLoadTexMtxImm(*wp->paperMtxPtr[2], GX_TEXMTX1, GX_MTX2x4);
                            mapSetMaterialTev(2, 12, wp->mpCurPose->materialFlag, *g_modeling_mtx);
                        }
                    }
                }

                pose = wp->mpCurPose;
                if (pose->flags & 0x10) {
                    texObj = wp->mpTexObjs[0];
                    if (texObj) {
                        mtx = wp->paperMtxPtr[0];
                        if (mtx) {
                            animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, *mtx, wp->mpTexDatas[0],
                                                          texObj, 1);
                        }
                    }
                }

                texIds = draw->texArrayIds;
                firstId = draw->firstIdTex;
                data = wp->mpCurPoseData; // inlined function here
                drawCall = &data->drawCalls[draw->firstDrawCall];
                texCount = draw->texCount;
                drawCallCount = draw->drawCallCount;
                clr0VtxPtr = (GXColor*)((u8*)data->clr0VtxBuffer + clr0VtxSize);
                posFirstId = draw->firstIdPos;
                nrmFirstId = draw->firstIdNrm;
                clr0FirstId = draw->firstIdClr0;

                if (wp->mbUseFloatScratch) {
                    nrmVtxPtr = (Vec*)((u8*)wp->vtxArrayNrm + nrmVtxSize);
                    posVtxPtr = (Vec*)((u8*)wp->vtxArrayPos + posVtxSize);
                } else {
                    pose = wp->mpCurPose;
                    posVtxPtr = (Vec*)((u8*)pose->mpVtxArrayPos + posVtxSize);
                    nrmVtxPtr = (Vec*)((u8*)pose->mpVtxArrayNrm + nrmVtxSize);
                }
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_POS, posVtxPtr, sizeof(Vec));
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_NRM, nrmVtxPtr, sizeof(Vec));
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
                GXSetArray(GX_VA_CLR0, clr0VtxPtr, sizeof(GXColor));

                if (texCount == 1) { // just use texIndex[0]
                    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
                    GXSetArray(GX_VA_TEX0, texVtxIndices[texIds[0]], sizeof(f32) * 2);
                    for (j = 0; j < drawCallCount; j++, drawCall++) {
                        data = wp->mpCurPoseData; // doubly inlined function here
                        count = drawCall->count;
                        // indices are stored as u32, has to do math to load the lower 2 bytes
                        posIndexPtr = &data->posIndex[((drawCall->first + posFirstId) * 2) + 1];
                        nrmIndexPtr = &data->nrmIndex[((drawCall->first + nrmFirstId) * 2) + 1];
                        clr0IndexPtr = &data->clr0Index[((drawCall->first + clr0FirstId) * 2) + 1];
                        texIndexPtr = &data->texIndex[texIds[0]][((drawCall->first + firstId[texIds[0]]) * 2) + 1];
                        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, (u16)drawCall->count);
                        for (k = 0; k < count; k++) { // unrolled, warning
                            GXPosition1x16(*posIndexPtr);
                            posIndexPtr += 2;
                            GXNormal1x16(*nrmIndexPtr);
                            nrmIndexPtr += 2;
                            GXColor1x16(*clr0IndexPtr);
                            clr0IndexPtr += 2;
                            GXTexCoord1x16(*texIndexPtr);
                            texIndexPtr += 2;
                        }
                    }
                } else { // enumerate texIndex
                    for (j = 0; j < texCount; j++) {
                        GXSetVtxDesc(GX_VA_TEX0 + j, GX_INDEX16);
                        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0 + j, GX_TEX_ST, GX_F32, 0);
                        GXSetArray(GX_VA_TEX0 + j, texVtxIndices[texIds[texCount - j - 1]], sizeof(f32) * 2);
                    }
                    for (j = 0; j < drawCallCount; j++, drawCall++) {
                        firstDrawId = drawCall->first;
                        data = wp->mpCurPoseData; // doubly inlined function here
                        count = drawCall->count;
                        // indices are stored as u32, has to do math to load the lower 2 bytes
                        posIndexPtr = &data->posIndex[((drawCall->first + posFirstId) * 2) + 1];
                        nrmIndexPtr = &data->nrmIndex[((drawCall->first + nrmFirstId) * 2) + 1];
                        clr0IndexPtr = &data->clr0Index[((drawCall->first + clr0FirstId) * 2) + 1];

                        for (k = 0, texIndex = 0; k < count; k++) {
                            GXPosition1x16(*posIndexPtr);
                            GXNormal1x16(*nrmIndexPtr);
                            GXColor1x16(*clr0IndexPtr);
                            for (l = 0; l < texCount; l++) {
                                index = texIds[texCount - l - 1];
                                GXTexCoord1x16(wp->mpCurPoseData
                                                   ->texIndex[index][((drawCall->first + firstId[index]) * 2) + texIndex]);
                            }
                            texIndex += 2;
                            posIndexPtr += 2;
                            nrmIndexPtr += 2;
                            clr0IndexPtr += 2;
                        }
                    }
                }
            }
        }
    }
}

// dispProc

void materialProc(s32 shapeId, s32 xluStage);
void vivihimo(Mtx a, Mtx b, f32 speed, f32 scale, f32 offA, f32 offB);

void dispProc(s32 parentId, s32 groupId, s32 xluStage, s32 arg3, f32 arg4) {
    AnimPoseGroup* group;
    AnimPoseGroup* parent;
    AnimPoseNode* node;
    AnimationPose* pose;
    AnimationPoseData* data;
    f32 sx, sy, sz;

    if (groupId == -1) {
        return;
    }
    data = wp->mpCurPoseData;
    group = &data->groups[groupId];
    if (*(s8*)&wp->mpCurPose->mpGroupVisibility[group->visibilityId]) {
        pose = wp->mpCurPose;
        node = (AnimPoseNode*)((u32*)pose->mpNodes + group->nodeId);
        if (group->useSSC) {
            if (parentId == -1) {
                sx = sy = sz = 1.0f;
            }
            else {
                parent = &data->groups[parentId];
                if (!parent->useSSC) {
                    sx = sy = sz = 1.0f;
                }
                else {
                    AnimPoseNode* pnode = (AnimPoseNode*)((u32*)pose->mpNodes + parent->nodeId);
                    sx = pnode->mScale.x;
                    sy = pnode->mScale.y;
                    sz = pnode->mScale.z;
                }
            }
            pushGXModelMtx_JointNode__(node, sx, sy, sz);
        }
        else {
            pushGXModelMtx_TransformNode__(node);
        }
        if (wp->mpCurPose->flags & 0x40) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = (*g_modeling_mtx)[0][3];
            pos.y = (*g_modeling_mtx)[1][3];
            pos.z = (*g_modeling_mtx)[2][3];
            (*wp->mpCurPose->worldPositions)[groupId] = pos;
        }
        if (wp->mpCurPose->flags & 0x80) {
            PSMTXCopy(*g_modeling_mtx, (*wp->mpCurPose->worldMatrices)[groupId]);
        }
        pose = wp->mpCurPose;
        if (pose->flags & 0x20 && groupId == pose->vivianGroupNo[0]) {
            Mtx* m;
            MtxPtr mat;
            f32* speed;
            f32 offA, offB;
            int i, j;
            s32 type;

            offB = offA = 0.0f;
            type = pose->vivianType;
            speed = (f32*)vivihimoData[type] + pose->animId * 2;
            m = g_modeling_mtx;
            mat = pose->matrix;
            switch (type) {
                case 1:
                    offA = -2.0f;
                    offB = 0.5f;
                    break;
                case 2:
                    offA = -3.0f;
                    offB = 0.5f;
                    break;
                case 3:
                    offA = -1.0f;
                    offB = 0.5f;
                    break;
            }
            materialProc(group->shapeId, xluStage);
            vivihimo(*m, mat, speed[0], speed[1], offA, offB);
            wp->mpCurPose->flags &= ~0x20;
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    mat[i][j] += 0.04f * ((*m)[i][j] - mat[i][j]);
                }
            }
        }
        else {
            if (pose->dispCallback) {
                ((void (*)(void*, s32, Mtx*))pose->dispCallback)(pose->dispUserDataCallback, groupId, g_modeling_mtx);
            }
            renderProc(group->shapeId, xluStage);
            dispProc(groupId, group->childGroupId, xluStage, arg3, arg4);
        }
        g_modeling_mtx_lv--;
        g_modeling_mtx = &g_modeling_mtx_stack[g_modeling_mtx_lv];
    }
    dispProc(groupId, group->brotherGroupId, xluStage, arg3, arg4);
}


void animPoseDraw(s32 poseId, f32 x, f32 y, f32 z, f32 rotY, f32 scale, s32 xluMode) {
    Mtx matrix;

    MTXTrans(matrix, x, y, z);
    animPoseDrawMtx(poseId, matrix, xluMode, rotY, scale);
}

// _animPoseDrawMtx

asm void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale) {
    nofralloc
    blr
}

void animSetPaperTexObj(GXTexObj* obj1, GXTexObj* obj2, GXTexObj* obj3, void* data1, void* data2, void* data3, s32 a7, s32 a8) {
    wp->mpTexObjs[0] = data1 ? obj1 : NULL;
    wp->mpTexObjs[1] = data2 ? obj2 : NULL;
    wp->mpCurTexObj = data3 ? obj3 : NULL;
    wp->mpTexDatas[0] = data1;
    wp->mpTexDatas[1] = data2;
    wp->mpCurTexData = data3;
    wp->field_0xD8 = a7;
    wp->field_0xDC = a7;
}

inline void animPoseFileRelease(s32 fileId) {
    AnimationPoseFile* file = &wp->files[fileId];
    AnimationTextureFile* tex;

    file->references--;
    if (file->references <= 0) {
        file->active = 0;
        tex = &wp->textures[file->textureId];
        tex->references--;
        if (tex->references <= 0) {
            fileFree(tex->handle);
            tex->active = FALSE;
        }
        fileFree(file->handle);
    }
}

void animPoseRelease(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    if ((u32)pose->typeFlags != 0) {
        animPaperPoseRelease(poseId);
    }
    else {
        if (pose->flags & 0x40) {
            smartFree((smartEntry*)pose->worldPositions);
        }
        if (pose->flags & 0x80) {
            smartFree((smartEntry*)pose->worldMatrices);
        }
        animPoseFileRelease(pose->fileId);
        pose->flags = 0;
    }
}

void animPaperPoseRelease(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    pose->references--;
    if (pose->references < 0) {
        animPoseFileRelease(pose->fileId);
        pose->flags = 0;
    }
}

void animPoseAutoRelease(s32 type) {
    int i;
    AnimationPose* pose;

    for (i = 0; i < wp->totalPoses; i++) {
        pose = animPoseGetAnimPosePtr(i);
        if (pose->flags & 1 && pose->type == type) {
            animPoseRelease(i);
        }
    }
    if (type == 1) {
        wp->inBattle = FALSE;
    }
    animPoseRefresh();
}

void animPaperPoseDisp(CameraId camId, void* param) {
    int i;
    AnimationPose* pose;

    for (i = 0, pose = wp->poses; i < wp->totalPoses; i++, pose++) {
        if (pose->flags & 1 && pose->paperId != -1) {
            animPaperPoseDispSub(0, pose);
        }
    }
}

asm void animPaperPoseDispSub(s32 unused, AnimationPose* pose) {
    nofralloc
    blr
}

// animPoseDisp_MakeExtTexture

void animSetPaperTexMtx(Mtx mtx1, Mtx mtx2, Mtx mtx3) {
    if (mtx1 == NULL) {
        wp->paperMtxPtr[0] = NULL;
    }
    else {
        PSMTXCopy(mtx1, wp->paperMtx[0]);
        wp->paperMtxPtr[0] = &wp->paperMtx[0];
    }
    if (mtx2 == NULL) {
        wp->paperMtxPtr[1] = NULL;
    }
    else {
        PSMTXCopy(mtx2, wp->paperMtx[1]);
        wp->paperMtxPtr[1] = &wp->paperMtx[1];
    }
    if (mtx3 == NULL) {
        wp->paperMtxPtr[2] = NULL;
    }
    else {
        PSMTXCopy(mtx3, wp->paperMtx[2]);
        wp->paperMtxPtr[2] = &wp->paperMtx[2];
    }
}

BOOL animGroupBaseAsync(const char* name, s32 group, void* callback) {
    s32 model, anim;

    switch (group) {
        case 0:
            fileSetCurrentArchiveType(1);
            break;
        case 1:
            fileSetCurrentArchiveType(2);
            break;
        case 2:
            fileSetCurrentArchiveType(0);
            break;
    }
    model = fileAsyncf(5, callback, "%s/%s", "a", name);
    anim = fileAsyncf(4, NULL, "%s/%s-", "a", animGetTexName(name));
    if (model == -1) {
        return TRUE;
    }
    if ((u32)model == 0) {
        return FALSE;
    }
    if (anim == -1) {
        return TRUE;
    }
    return anim != 0;
}

AnimationPose* animPoseGetAnimPosePtr(s32 poseId) {
    return &wp->poses[poseId];
}

AnimData* animPoseGetAnimDataPtr(s32 poseId) {
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);
    return animPoseGetAnimBaseDataPtr(poseId)->mpAnims[pose->animId].data;
}

AnimationPoseData* animPoseGetAnimBaseDataPtr(s32 poseId) {
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);
    return *wp->files[pose->fileId].handle->data;
}

AnimTableEntry* animPoseGetCurrentAnim(s32 poseId) {
    AnimationPoseData* data = animPoseGetAnimBaseDataPtr(poseId);
    return &data->mpAnims[animPoseGetAnimPosePtr(poseId)->animId];
}

BOOL animPoseTestXLU(s32 poseId) {
    return (animPoseGetAnimBaseDataPtr(poseId)->flags >> 3) & 1;
}

void evalProc(s32 parentId, s32 groupId) {
    AnimPoseGroup* group;
    AnimPoseGroup* parent;
    AnimPoseNode* node;
    AnimationPose* pose;
    AnimationPoseData* data;
    f32 sx, sy, sz;

    if (groupId == -1) {
        return;
    }
    data = wp->mpCurPoseData;
    group = &data->groups[groupId];
    if (*(s8*)&wp->mpCurPose->mpGroupVisibility[group->visibilityId]) {
        pose = wp->mpCurPose;
        node = (AnimPoseNode*)((u32*)pose->mpNodes + group->nodeId);
        if (group->useSSC) {
            if (parentId == -1) {
                sx = sy = sz = 1.0f;
            }
            else {
                parent = &data->groups[parentId];
                if (!parent->useSSC) {
                    sx = sy = sz = 1.0f;
                }
                else {
                    AnimPoseNode* pnode = (AnimPoseNode*)((u32*)pose->mpNodes + parent->nodeId);
                    sx = pnode->mScale.x;
                    sy = pnode->mScale.y;
                    sz = pnode->mScale.z;
                }
            }
            pushGXModelMtx_JointNode__(node, sx, sy, sz);
        }
        else {
            pushGXModelMtx_TransformNode__(node);
        }
        if (wp->mpCurPose->flags & 0x40) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = (*g_modeling_mtx)[0][3];
            pos.y = (*g_modeling_mtx)[1][3];
            pos.z = (*g_modeling_mtx)[2][3];
            (*wp->mpCurPose->worldPositions)[groupId] = pos;
        }
        if (wp->mpCurPose->flags & 0x80) {
            PSMTXCopy(*g_modeling_mtx, (*wp->mpCurPose->worldMatrices)[groupId]);
        }
        if (!(wp->mpCurPose->flags & 0x20) || groupId != wp->mpCurPose->vivianGroupNo[0]) {
            evalProc(groupId, group->childGroupId);
        }
        g_modeling_mtx_lv--;
        g_modeling_mtx = &g_modeling_mtx_stack[g_modeling_mtx_lv];
    }
    evalProc(groupId, group->brotherGroupId);
}

void animPoseWorldPositionEvalOn(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    AnimationPoseData* data = animPoseGetBaseData(pose);
    u8 heap;

    if (!(pose->flags & 0x40)) {
        pose->flags |= 0x40;
        switch (pose->type) {
            case 0:
                heap = 1;
                break;
            case 1:
                heap = 2;
                break;
            case 2:
                heap = 0;
                break;
        }
        pose->numWorldPositions = data->groupCount;
        pose->worldPositions = (Vec**)smartAlloc(sizeof(Vec) * data->groupCount, heap);
    }
}

void L_animPoseWorldPositionEvalOff(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    if (pose->flags & 0x40) {
        pose->flags &= ~0x40;
        smartFree((smartEntry*)pose->worldPositions);
        pose->worldPositions = NULL;
    }
}

void animPoseWorldMatrixEvalOn(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    AnimationPoseData* data = animPoseGetBaseData(pose);
    u8 heap;

    if (!(pose->flags & 0x80)) {
        pose->flags |= 0x80;
        switch (pose->type) {
            case 0:
                heap = 1;
                break;
            case 1:
                heap = 2;
                break;
            case 2:
                heap = 0;
                break;
        }
        pose->numWorldMatrices = data->groupCount;
        pose->worldMatrices = (Mtx**)smartAlloc(sizeof(Mtx) * data->groupCount, heap);
    }
}

void animPoseVivianMain(s32 poseId, Vec* pos) {
    AnimationPose* pose = &wp->poses[poseId];

    pose->flags |= 0x20;
    pose->matrix[0][3] = pos->x;
    pose->matrix[1][3] = pos->y;
    pose->matrix[2][3] = pos->z;
}

s32 animPoseGetVivianType(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->vivianType;
}

void animPoseSetDispCallBack(s32 poseId, void* callback, void* userData) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->dispCallback = callback;
    pose->dispUserDataCallback = userData;
}

inline void animPoseMainSub(AnimationPose* pose) {
    s32 id = ((u32)pose - (u32)wp->poses) / sizeof(AnimationPose);
    if (pose->typeFlags & 2) {
        AnimationPoseData* data = animPoseGetBaseData(pose);
        s32 posNum = data->mBufferPosNum;
        s32 nrmNum = data->mBufferNrmNum;
        s32 total = posNum + nrmNum;
        if (total <= wp->mFloatScratchRP) {
            if (wp->mFloatScratchWP + total > wp->mFloatScratchRP) {
                wp->mFloatScratchWP = 0;
            }
            wp->mbUseFloatScratch = 1;
            wp->vtxArrayPos = &wp->mpFloatScratch[wp->mFloatScratchWP];
            wp->mFloatScratchWP += posNum;
            wp->vtxArrayNrm = &wp->mpFloatScratch[wp->mFloatScratchWP];
            wp->mFloatScratchWP += nrmNum;
        }
        animPoseMain(id);
        wp->mbUseFloatScratch = 0;
    }
    else {
        animPoseMain(id);
    }
}

void animPoseDrawShape(s32 poseId, s32 shapeId) {
    AnimationPose* pose;
    GXTexObj* texObj0;
    GXTexObj* texObj1;
    GXTexObj* curTexObj;
    void* texData0;
    void* texData1;
    void* curTexData;
    Mtx* paperMtx0;
    Mtx* paperMtx1;
    Mtx* paperMtx2;
    AnimationPose* curPose;
    AnimData* curAnimData;
    AnimationPoseData* curPoseData;
    u32 d8;
    u32 dc;
    s32 id;

    pose = &wp->poses[poseId];
    curPose = wp->mpCurPose;
    curAnimData = wp->mpCurAnimData;
    curPoseData = wp->mpCurPoseData;
    texObj0 = wp->mpTexObjs[0];
    texObj1 = wp->mpTexObjs[1];
    curTexObj = wp->mpCurTexObj;
    texData0 = wp->mpTexDatas[0];
    texData1 = wp->mpTexDatas[1];
    curTexData = wp->mpCurTexData;
    paperMtx0 = wp->paperMtxPtr[0];
    paperMtx1 = wp->paperMtxPtr[1];
    paperMtx2 = wp->paperMtxPtr[2];
    d8 = wp->field_0xD8;
    dc = wp->field_0xDC;

    wp->mpCurPose = pose;
    wp->mpCurAnimData = animPoseGetBaseData(pose)->mpAnims[pose->animId].data;
    wp->mpCurPoseData = animPoseGetBaseData(pose);
    wp->mpTexObjs[0] = NULL;
    wp->mpTexObjs[1] = NULL;
    wp->mpCurTexObj = NULL;
    wp->mpTexDatas[0] = NULL;
    wp->mpTexDatas[1] = NULL;
    wp->mpCurTexData = NULL;
    wp->paperMtxPtr[0] = NULL;
    wp->paperMtxPtr[1] = NULL;
    wp->paperMtxPtr[2] = NULL;
    wp->field_0xD8 = 0;
    wp->field_0xDC = 0;

    if (pose->lastFrameZero == -1) {
        animPoseMainSub(pose);
    }
    renderProc(shapeId, pose->field_0x28);

    wp->mpCurPose = curPose;
    wp->mpCurAnimData = curAnimData;
    wp->mpCurPoseData = curPoseData;
    wp->mpTexObjs[0] = texObj0;
    wp->mpTexObjs[1] = texObj1;
    wp->mpCurTexObj = curTexObj;
    wp->mpTexDatas[0] = texData0;
    wp->mpTexDatas[1] = texData1;
    wp->mpCurTexData = curTexData;
    wp->paperMtxPtr[0] = paperMtx0;
    wp->paperMtxPtr[1] = paperMtx1;
    wp->paperMtxPtr[2] = paperMtx2;
    wp->field_0xD8 = d8;
    wp->field_0xDC = dc;
}

s32 animPoseGetShapeIdx(s32 poseId, const char* name) {
    AnimationPoseData* data;
    AnimPoseShape* shape;
    s32 i;

    data = animPoseGetAnimBaseDataPtr(poseId);
    shape = data->shapes;
    for (i = 0; i < data->shapeCount; i++, shape++) {
        if (!strcmp(shape->name, name)) {
            return i;
        }
    }
    return -1;
}

s32 animPoseGetGroupIdx(s32 poseId, const char* name) {
    AnimationPoseData* data;
    AnimPoseGroup* group;
    s32 i;

    data = animPoseGetAnimBaseDataPtr(poseId);
    group = data->groups;
    for (i = 0; i < data->groupCount; i++, group++) {
        if (!strcmp(group->name, name)) {
            return i;
        }
    }
    return -1;
}

const char* animPoseGetGroupName(s32 poseId, s32 group) {
    return animPoseGetAnimBaseDataPtr(poseId)->groups[group].name;
}
