#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "driver/npcdrv.h"
#include "driver/extdrv.h"
#include "string.h"
#include "dolphin/os.h"
#include "mario/mariost.h"
#include "driver/animdrv.h"
#include "stdlib.h"
#include "driver/camdrv.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "memory.h"
#include "driver/dispdrv.h"

typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
typedef struct YuuNpcPose { char name[16]; char anim[8]; u16 field_0x18; f32 frames; f32 jump; s32 start; s32 count; u16 flags; f32 field_0x30; } YuuNpcPose;
typedef struct YuuNpc { s16 id; u16 flags; s16 state; f32 field_0x8; Vec goal; Vec dest; Vec pos; u8 field_0x30[0xC]; f32 radius; f32 vy; u8 field_0x44[0x10]; s16 poseId; u8 field_0x56[0xA]; NpcEntry* npc; f32 animSpeed; u64 time; } YuuNpc;
typedef struct YuuNpcWork { u16 flags; s32 numNpc; u8 field_0x8[0xC]; YuuNpc* npcs; s32 basePoseNum; s32 numPoses; s32 chusanPose; s16 hit[6 * 72]; s16 hitY[72]; YuuNpcPose pose[32]; } YuuNpcWork;
static YuuNpcWork* yuunpc_wp;
typedef struct YuuNpcData { const char* name; const char* anim; f32 frames; } YuuNpcData;
s32 yuunpc_pose_check(const char* name, const char* anim);
void yuunpc_pose_change(YuuNpc* npc, s16 id, f32 speed, f32 frame);
f32 yuusintbl[450];
s32 chusan_mov_tbl[28];
s32 chusan_act_tbl[8];
f32 yuunpc_pose_sub(ExtPose* ext, YuuNpc* npc);
ExtPose* extGetPosePtr(void);
void ext_yuunpc_minigame4_init_sub(void);
s32 extGetPoseNum(void);
void* yuunpc_yuuminigame4_ptr;
void extLoadRenderMode(void);
void extLoadVertex(void);
void extLoadTexture(void);
void extLoadTev(void);
void extDraw(void);
void extLoadTextureExit(void);
void yuunpc_disp(CameraId camera, void* param);
void yuunpc_pose_minigame1_main(void);
void yuunpc_pose_minigame2_main(void);
void yuunpc_pose_minigame3_main(void);
void yuunpc_pose_minigame4_main(void);

USER_FUNC(evt_ext_entry);
USER_FUNC(evt_npc_delete);
USER_FUNC(evt_npc_entry);
USER_FUNC(evt_npc_flag_onoff);
USER_FUNC(evt_npc_set_position);
USER_FUNC(evt_seq_wait);
void ext_yuunpc_minigame4_main(void);
void ext_yuunpc_minigame3_main(void);
void ext_yuunpc_minigame2_main(void);
void ext_yuunpc_minigame1_main(void);
void ext_yuunpc_dispent(void);
void yuunpc_disp(CameraId camera, void* param);
void yuunpc_pose_minigame4_main(void);
void ext_yuunpc_minigame4_init(void);
void ext_yuunpc_minigame4_init_sub(void);
s32 yuunpc_juni(Vec* pos);
u16 yuunpc_wp_flag_check(u16 flag);
void yuunpc_wp_flag_off(u16 flag);
void yuunpc_wp_flag_on(u16 flag);
void errper_set_rtn(YuuNpc* npc);
s32 goalincheck(YuuNpc* npc);
s32 fallcheck(YuuNpc* npc);
s32 hitcheck(YuuNpc* npc);
void yuunpc_pose_minigame3_main(void);
void ext_yuunpc_minigame3_init(void);
void yuunpc_pose_minigame2_main(void);
void ext_yuunpc_minigame2_init(void);
void yuunpc_pose_minigame1_main(void);
void ext_yuunpc_minigame1_init(void);
f32 yuunpc_pose_sub(ExtPose* ext, YuuNpc* npc);
void yuunpc_set_jump_pose(const char* name, const char* anim, f32 jump);
void yuunpc_pose_change2(YuuNpc* npc, const char* name, const char* anim, f32 speed);
void yuunpc_pose_change(YuuNpc* npc, s16 id, f32 speed, f32 frame);
s32 yuunpc_pose_check(const char* name, const char* anim);
void yuunpc_pose_init(YuuNpcData* data);
void yuunpc_maphit_init(void);

__declspec(section ".data") u64 fd_evt_yuunpc_negone_one_374;
__declspec(section ".data") s32 fd_evt_yuunpc_neg_one_382[1];
__declspec(section ".data") s32 fd_evt_yuunpc___local_PI_383[1];
__declspec(section ".data") s32 fd_evt_yuunpc___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_evt_yuunpc_one_negone_373;
__declspec(section ".data") s32 fd_evt_yuunpc___local_PIO2_384[1];
__declspec(section ".data") s32 fd_evt_yuunpc_one_381[1];
__declspec(section ".data") u64 fd_evt_yuunpc_negone_one_360;
__declspec(section ".data") s32 fd_evt_yuunpc_neg_one_365[1];
__declspec(section ".data") s32 fd_evt_yuunpc___local_PI_366[1];
__declspec(section ".data") s32 fd_evt_yuunpc___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_evt_yuunpc_one_negone_359;
__declspec(section ".data") s32 fd_evt_yuunpc___local_PIO2_367[1];
__declspec(section ".data") s32 fd_evt_yuunpc_one_364[1];
extern signed char hitdata[];
s32 ext_yuunpc_minigame1_data[18];
s32 ext_yuunpc_minigame2_data[18];
s32 ext_yuunpc_minigame3_data[18];
s32 ext_yuunpc_minigame4_data[234];
s32 chusan_mov_tbl[28];
__declspec(section ".data") s32 chusan_act_tbl[8];
s32 evt_yuunpc_minigame1[69];
s32 evt_yuunpc_minigame2[69];
s32 evt_yuunpc_minigame3[69];
s32 evt_yuunpc_minigame4[167];

void yuunpc_maphit_init(void) {
    f32 frame = rand() / 32767.0f;
    s16 id = yuunpc_pose_check(name, anim);
    YuuNpcPose* cur = &yuunpc_wp->pose[npc->poseId];
    YuuNpcPose* pose = &yuunpc_wp->pose[id];

    if (speed <= 0.0f) {
        npc->flags |= 4;
        npc->poseId = id;
        npc->animSpeed = 1.0f;
        npc->time = OSMillisecondsToTicks(1000.0f * (frame * (pose->frames * npc->animSpeed)) / 60.0f);
    } else {
        u16 flags = npc->flags;
        npc->flags = flags & ~4;
        if (npc->poseId == id) {
            f32 old = npc->animSpeed;
            if (old != speed) {
                if (flags & 4) {
                    frame = 60.0f * OSTicksToMilliseconds(npc->time) / 1000.0f;
                    frame /= pose->frames * old;
                } else {
                    frame = 60.0f * OSTicksToMilliseconds(gp->renderTime - npc->time) / 1000.0f;
                    frame /= cur->frames * old;
                }
            } else {
                return;
            }
        } else {
            npc->poseId = id;
        }
        npc->animSpeed = speed;
        npc->time = gp->renderTime - OSMillisecondsToTicks(1000.0f * (frame * (pose->frames * npc->animSpeed)) / 60.0f);
    }
    switch (npc->flags & 0x300) {
        case 0:
            break;
        case 0x100:
        case 0x200:
        case 0x300:
            animPoseSetAnim(npc->npc->poseId, pose->anim, TRUE);
            animPoseMain(npc->npc->poseId);
            break;
    }
}

void yuunpc_pose_init(YuuNpcData* data) {
    char name[32];
    char anim[32];
    s32 n = 0;
    s32 start;
    s32 i;

    strcpy(name, "");
    strcpy(anim, "");
    yuunpc_wp->numPoses = -1;
    do {
        if (strcmp(data->name, name) != 0) {
            strcpy(name, data->name);
            strcpy(anim, "");
        }
        if (strcmp(data->anim, anim) != 0) {
            strcpy(anim, data->anim);
            start = n;
            yuunpc_wp->numPoses++;
        }
        strcpy(yuunpc_wp->pose[yuunpc_wp->numPoses].name, name);
        strcpy(yuunpc_wp->pose[yuunpc_wp->numPoses].anim, anim);
        yuunpc_wp->pose[yuunpc_wp->numPoses].start = start;
        yuunpc_wp->pose[yuunpc_wp->numPoses].count = n - start + 1;
        n++;
        yuunpc_wp->pose[yuunpc_wp->numPoses].frames += 1.0f;
        yuunpc_wp->pose[yuunpc_wp->numPoses].field_0x18 = 1;
        yuunpc_wp->pose[yuunpc_wp->numPoses].jump = 0.0f;
        yuunpc_wp->pose[yuunpc_wp->numPoses].field_0x30 = 2.0f;
        data++;
    } while (data->name != NULL);
    data++;
    yuunpc_wp->numPoses++;
    yuunpc_wp->basePoseNum = yuunpc_wp->numPoses;
    while (data->name != NULL) {
        strcpy(yuunpc_wp->pose[yuunpc_wp->numPoses].name, data->name);
        strcpy(yuunpc_wp->pose[yuunpc_wp->numPoses].anim, data->anim);
        yuunpc_wp->pose[yuunpc_wp->numPoses].start = start;
        yuunpc_wp->pose[yuunpc_wp->numPoses].count = 1;
        yuunpc_wp->pose[yuunpc_wp->numPoses].frames = data->frames;
        data++;
        yuunpc_wp->pose[yuunpc_wp->numPoses].field_0x18 = 1;
        yuunpc_wp->pose[yuunpc_wp->numPoses].jump = 0.0f;
        yuunpc_wp->pose[yuunpc_wp->numPoses].field_0x30 = 1.0f;
        yuunpc_wp->pose[yuunpc_wp->numPoses].flags |= 1;
        yuunpc_wp->numPoses++;
    }
    for (i = 0; i < yuunpc_wp->basePoseNum; i++) {
        if (strcmp(yuunpc_wp->pose[i].name, "c_tyusan") == 0 && strcmp(yuunpc_wp->pose[i].anim, "CHU_S_1") == 0) {
            yuunpc_wp->chusanPose = i;
            yuunpc_wp->pose[i].frames = 224.0f;
        }
    }
}

s32 yuunpc_pose_check(const char* name, const char* anim) {
    YuuNpcPose* pose = yuunpc_wp->pose;
    s32 i;

    for (i = 0; i < yuunpc_wp->numPoses; i++, pose++) {
        if (strcmp(pose->name, name) == 0 && strcmp(pose->anim, anim) == 0) {
            break;
        }
    }
    if (i >= yuunpc_wp->numPoses) {
        return -1;
    }
    return i;
}

void yuunpc_pose_change(YuuNpc* npc, s16 id, f32 speed, f32 frame) {
    YuuNpcPose* cur = &yuunpc_wp->pose[npc->poseId];
    YuuNpcPose* pose = &yuunpc_wp->pose[id];

    if (speed <= 0.0f) {
        npc->flags |= 4;
        npc->poseId = id;
        npc->animSpeed = 1.0f;
        npc->time = OSMillisecondsToTicks(1000.0f * (frame * (pose->frames * npc->animSpeed)) / 60.0f);
    } else {
        u16 flags = npc->flags;
        npc->flags = flags & ~4;
        if (npc->poseId == id) {
            f32 old = npc->animSpeed;
            if (old != speed) {
                if (flags & 4) {
                    frame = 60.0f * OSTicksToMilliseconds(npc->time) / 1000.0f;
                    frame /= pose->frames * old;
                } else {
                    frame = 60.0f * OSTicksToMilliseconds(gp->renderTime - npc->time) / 1000.0f;
                    frame /= cur->frames * old;
                }
            } else {
                return;
            }
        } else {
            npc->poseId = id;
        }
        npc->animSpeed = speed;
        npc->time = gp->renderTime - OSMillisecondsToTicks(1000.0f * (frame * (pose->frames * npc->animSpeed)) / 60.0f);
    }
    switch (npc->flags & 0x300) {
        case 0:
            break;
        case 0x100:
        case 0x200:
        case 0x300:
            animPoseSetAnim(npc->npc->poseId, pose->anim, TRUE);
            animPoseMain(npc->npc->poseId);
            break;
    }
}

void yuunpc_pose_change2(YuuNpc* npc, const char* name, const char* anim, f32 speed) {
    f32 frame = rand() / 32767.0f;

    yuunpc_pose_change(npc, yuunpc_pose_check(name, anim), speed, frame);
}

void yuunpc_set_jump_pose(const char* name, const char* anim, f32 jump) {
    s32 id = yuunpc_pose_check(name, anim);

    if (id >= 0) {
        yuunpc_wp->pose[id].jump = jump;
    }
}

f32 yuunpc_pose_sub(ExtPose* ext, YuuNpc* npc) {
    YuuNpcPose* pose = &yuunpc_wp->pose[npc->poseId];
    f32 t;
    f32 a;

    if (!(ext->flags & 2)) {
        f32 c, s;
        a = 450.0f - ext->rot;
        if (a >= 360.0f) {
            a -= 360.0f;
        }
        s = yuusintbl[(s32)a];
        c = yuusintbl[(s32)a + 90];
        ext->mtx[0][0] = c;
        ext->mtx[2][2] = c;
        ext->mtx[0][2] = s;
        ext->mtx[2][0] = -s;
    }
    if (npc->flags & 4) {
        t = 60.0f * OSTicksToMilliseconds(npc->time) / 1000.0f;
        t /= pose->frames * npc->animSpeed;
    } else {
        OSTime now = gp->renderTime;
        t = 0.5f + 60.0f * OSTicksToMilliseconds(now - npc->time) / 1000.0f;
        t /= pose->frames * npc->animSpeed;
        if (t >= 1.0f) {
            npc->time = now;
            t = 0.0f;
        }
    }
    switch (npc->flags & 0x300) {
        case 0x100:
        case 0x200:
        case 0x300: {
            f32 rot;
            animPoseSetLocalTime(npc->npc->poseId, (s32)(pose->frames * t));
            rot = 3600.0f + (90.0f - ext->rot);
            npc->npc->rotation.y = rot - (s32)(rot / 360.0f) * 360;
            npc->npc->position = npc->pos;
            break;
        }
        case 0:
            if (npc->poseId != yuunpc_wp->chusanPose) {
                ext->frame = pose->start + (s32)(pose->count * t);
            } else {
                s32 k = 224.0f * t;
                ext->frame = pose->start + (chusan_mov_tbl[k >> 3] ? chusan_act_tbl[k & 7] : 0);
            }
            break;
    }
    return t;
}

__declspec(section ".data") u64 fd_evt_yuunpc_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_evt_yuunpc_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_evt_yuunpc___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_evt_yuunpc___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_evt_yuunpc_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_evt_yuunpc___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_evt_yuunpc_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_evt_yuunpc_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_evt_yuunpc_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_evt_yuunpc___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_evt_yuunpc___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_evt_yuunpc_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_evt_yuunpc___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_evt_yuunpc_one_364[] = {
    1065353216,
};

f32 yuusintbl[] = {
    0.0f, 0.0174519997f, 0.0348990001f, 0.0523359999f, 0.0697560012f, 0.0871559978f, 0.104528002f, 0.121868998f,
    0.139173001f, 0.156434f, 0.173648f, 0.190808997f, 0.207911998f, 0.224950999f, 0.241922006f, 0.258819014f,
    0.275637001f, 0.292371988f, 0.309017003f, 0.325567991f, 0.342020005f, 0.358368009f, 0.374606997f, 0.390731007f,
    0.406737f, 0.422618002f, 0.438371003f, 0.453990012f, 0.469471008f, 0.484809995f, 0.5f, 0.515038013f,
    0.529919028f, 0.544638991f, 0.559193015f, 0.573575974f, 0.587785006f, 0.601814985f, 0.615661025f, 0.629320025f,
    0.642787993f, 0.656059027f, 0.669130981f, 0.681998014f, 0.694657981f, 0.707107008f, 0.719340026f, 0.731353998f,
    0.743144989f, 0.754709005f, 0.766044021f, 0.777145982f, 0.788011014f, 0.798635006f, 0.809017003f, 0.819151998f,
    0.829037011f, 0.838670015f, 0.848047972f, 0.857167006f, 0.866024971f, 0.87462002f, 0.882947028f, 0.891005993f,
    0.898793995f, 0.906307995f, 0.913545012f, 0.920504987f, 0.927183986f, 0.933579981f, 0.939692974f, 0.945518017f,
    0.951056004f, 0.956305027f, 0.961261988f, 0.965925992f, 0.970296025f, 0.974370003f, 0.978147984f, 0.981626987f,
    0.984808028f, 0.987688005f, 0.990267992f, 0.992546022f, 0.994521976f, 0.996195018f, 0.997564018f, 0.998629987f,
    0.999391019f, 0.999848008f, 1.0f, 0.999848008f, 0.999391019f, 0.998629987f, 0.997564018f, 0.996195018f,
    0.994521976f, 0.992546022f, 0.990267992f, 0.987688005f, 0.984808028f, 0.981626987f, 0.978147984f, 0.974370003f,
    0.970296025f, 0.965925992f, 0.961261988f, 0.956305027f, 0.951057017f, 0.94551897f, 0.939692974f, 0.933580995f,
    0.927183986f, 0.920504987f, 0.913546026f, 0.906307995f, 0.898793995f, 0.891007006f, 0.882947981f, 0.87462002f,
    0.866025984f, 0.857168019f, 0.848047972f, 0.838671029f, 0.829038024f, 0.819151998f, 0.809017003f, 0.798636019f,
    0.788011014f, 0.777145982f, 0.766044974f, 0.754710019f, 0.743144989f, 0.731353998f, 0.719340026f, 0.707107008f,
    0.694658995f, 0.681999028f, 0.669130981f, 0.656059027f, 0.642787993f, 0.629320979f, 0.615661979f, 0.601814985f,
    0.587786019f, 0.573576987f, 0.559193015f, 0.544638991f, 0.529919982f, 0.515039027f, 0.5f, 0.484809995f,
    0.469471991f, 0.453990996f, 0.438371986f, 0.422618985f, 0.406737f, 0.39073199f, 0.374606997f, 0.358368993f,
    0.342020988f, 0.325569004f, 0.309017003f, 0.292371988f, 0.275638014f, 0.258819997f, 0.241923004f, 0.224951997f,
    0.207911998f, 0.190808997f, 0.173648998f, 0.156434998f, 0.139173999f, 0.121870004f, 0.104529001f, 0.0871559978f,
    0.0697569996f, 0.0523369983f, 0.0348999985f, 0.0174529999f, 9.99999997e-07f, -0.0174519997f, -0.0348990001f, -0.0523350015f,
    -0.0697560012f, -0.0871549994f, -0.104528002f, -0.121868998f, -0.139173001f, -0.156434f, -0.173648f, -0.190807998f,
    -0.207911f, -0.224950001f, -0.241920993f, -0.258819014f, -0.275637001f, -0.292371005f, -0.309015989f, -0.325567991f,
    -0.342018992f, -0.358366996f, -0.374606013f, -0.390729994f, -0.406735986f, -0.422618002f, -0.438371003f, -0.453990012f,
    -0.469471008f, -0.484809011f, -0.499998987f, -0.515037f, -0.529919028f, -0.544638991f, -0.559192002f, -0.573575974f,
    -0.587785006f, -0.601813972f, -0.615661025f, -0.629320025f, -0.64278698f, -0.656058013f, -0.669130027f, -0.681998014f,
    -0.694657981f, -0.707105994f, -0.719339013f, -0.731352985f, -0.743143976f, -0.754709005f, -0.766044021f, -0.777145028f,
    -0.788010001f, -0.798635006f, -0.809015989f, -0.819151998f, -0.829037011f, -0.838670015f, -0.848047972f, -0.857167006f,
    -0.866024971f, -0.874619007f, -0.882947028f, -0.891005993f, -0.898793995f, -0.906306982f, -0.913545012f, -0.920503974f,
    -0.927182972f, -0.933579981f, -0.93969202f, -0.945518017f, -0.951056004f, -0.956304014f, -0.961260974f, -0.965925992f,
    -0.970295012f, -0.974370003f, -0.97814697f, -0.981626987f, -0.984808028f, -0.987688005f, -0.990267992f, -0.992546022f,
    -0.994521976f, -0.996195018f, -0.997564018f, -0.998628974f, -0.999391019f, -0.999848008f, -1.0f, -0.999848008f,
    -0.999391019f, -0.998629987f, -0.997564018f, -0.996195018f, -0.994521976f, -0.992546022f, -0.990267992f, -0.987688005f,
    -0.984808028f, -0.981626987f, -0.978147984f, -0.974370003f, -0.970296025f, -0.965925992f, -0.961261988f, -0.956305027f,
    -0.951057017f, -0.94551897f, -0.939692974f, -0.933580995f, -0.927183986f, -0.920504987f, -0.913546026f, -0.906307995f,
    -0.898795009f, -0.891007006f, -0.882947981f, -0.87462002f, -0.866025984f, -0.857168019f, -0.848048985f, -0.838671029f,
    -0.829038024f, -0.819153011f, -0.809018016f, -0.798636019f, -0.788011014f, -0.777146995f, -0.766044974f, -0.754710019f,
    -0.743146002f, -0.731353998f, -0.71934098f, -0.707108021f, -0.694658995f, -0.681999028f, -0.669131994f, -0.65605998f,
    -0.642787993f, -0.629320979f, -0.615661979f, -0.601815999f, -0.587786019f, -0.573576987f, -0.559194028f, -0.544640005f,
    -0.529919982f, -0.515039027f, -0.500001013f, -0.484811008f, -0.469473004f, -0.453990996f, -0.438371986f, -0.422618985f,
    -0.406737f, -0.39073199f, -0.37460801f, -0.358368993f, -0.342022002f, -0.325569004f, -0.309017986f, -0.292373002f,
    -0.275638014f, -0.258819997f, -0.241923004f, -0.224951997f, -0.207912996f, -0.190809995f, -0.173648998f, -0.156434998f,
    -0.139174998f, -0.121871002f, -0.104529999f, -0.0871570036f, -0.069757998f, -0.0523369983f, -0.0349010006f, -0.0174540002f,
    -9.99999997e-07f, 0.0174509995f, 0.0348990001f, 0.0523350015f, 0.0697550029f, 0.087154001f, 0.104526997f, 0.121867999f,
    0.139172003f, 0.156433001f, 0.173647001f, 0.190807998f, 0.207910001f, 0.224950001f, 0.241920993f, 0.258818001f,
    0.275635988f, 0.292371005f, 0.309015006f, 0.325567007f, 0.342018992f, 0.358366996f, 0.374605f, 0.390729994f,
    0.406735986f, 0.422616988f, 0.438369989f, 0.453990012f, 0.469471008f, 0.484809011f, 0.499998987f, 0.515037f,
    0.529918015f, 0.544637978f, 0.559190989f, 0.57357502f, 0.587783992f, 0.601813972f, 0.615661025f, 0.629319012f,
    0.64278698f, 0.656058013f, 0.669130027f, 0.681997001f, 0.694657028f, 0.707104981f, 0.719339013f, 0.731352985f,
    0.743143976f, 0.754709005f, 0.766044021f, 0.777145028f, 0.788010001f, 0.798635006f, 0.809015989f, 0.819150984f,
    0.829037011f, 0.838670015f, 0.848047018f, 0.857165992f, 0.866024971f, 0.874619007f, 0.882947028f, 0.891005993f,
    0.898792982f, 0.906306982f, 0.913545012f, 0.920503974f, 0.927182972f, 0.933579981f, 0.93969202f, 0.945518017f,
    0.951056004f, 0.956304014f, 0.961260974f, 0.965924978f, 0.970295012f, 0.974370003f, 0.97814697f, 0.981626987f,
    0.984808028f, 0.987688005f, 0.990267992f, 0.992546022f, 0.994521976f, 0.996195018f, 0.997564018f, 0.998628974f,
    0.999391019f, 0.999848008f,
};

signed char hitdata[] = "000000000000000000000000001617181911121314151122231102030405060607080910000000000000000000242526272828282828000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000747474747474744949242400000000000000000000000000000000000000000000000000\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\241\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\241\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\241\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\241\201\240\201\240\201\240\201\240\201\241\201\241\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\241\201\240\201\240\201\241\201\240\201\240\201\240\201\240\201\241\201\241\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\241\201\241\201\241\201\241\201\241\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\241\201\240\201\240\201\241\201\240\201\240\201\240\201\240\201\241\201\241\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\241\201\241\201\241\201\241\201\241\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\241\201\240\201\240\201\240\201\240\201\241\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\241\201\241\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\241\201\240\201\240\201\240\201\240\201\241\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\201\240\000\000\000";

s32 ext_yuunpc_minigame1_data[] = {
    (s32)"c_kinopiko", (s32)"KNF_S_1", 0, (s32)"c_roten", (s32)"S_1", 0, (s32)"c_jugemu", (s32)"JGM_S_1",
    0, (s32)"c_kinopio", (s32)"KNP_S_1", 0, 0, 0, 0, 0,
    0, 0,
};

s32 ext_yuunpc_minigame2_data[] = {
    (s32)"c_kinopiko", (s32)"KNF_S_1", 0, (s32)"c_roten", (s32)"S_1", 0, (s32)"c_jugemu", (s32)"JGM_S_1",
    0, (s32)"c_kinopio", (s32)"KNP_S_1", 0, 0, 0, 0, 0,
    0, 0,
};

s32 ext_yuunpc_minigame3_data[] = {
    (s32)"c_kinopiko", (s32)"KNF_S_1", 0, (s32)"c_roten", (s32)"S_1", 0, (s32)"c_jugemu", (s32)"JGM_S_1",
    0, (s32)"c_kinopio", (s32)"KNP_S_1", 0, 0, 0, 0, 0,
    0, 0,
};

s32 ext_yuunpc_minigame4_data[] = {
    (s32)"c_kinopiko", (s32)"KNF_S_1", 0, (s32)"c_roten", (s32)"S_1", 0, (s32)"c_jugemu", (s32)"JGM_S_1",
    0, (s32)"c_kinopio", (s32)"KNP_S_1", 0, (s32)"c_kinopio", (s32)"KNP_R_1", 0, (s32)"c_kinopio",
    (s32)"KNP_R_1", 1065353216, (s32)"c_kinopio", (s32)"KNP_R_1", 1073741824, (s32)"c_kinopio", (s32)"KNP_R_1", 1077936128,
    (s32)"c_kinopio", (s32)"KNP_R_1", 1082130432, (s32)"c_kinopio", (s32)"KNP_R_1", 1084227584, (s32)"c_kinopio", (s32)"KNP_R_1",
    1086324736, (s32)"c_kinopio", (s32)"KNP_R_1", 1088421888, (s32)"c_kinopio", (s32)"KNP_R_1", 1090519040, (s32)"c_kinopio",
    (s32)"KNP_R_1", 1091567616, (s32)"c_kinopio", (s32)"KNP_R_1", 1092616192, (s32)"c_kinopio", (s32)"KNP_R_1", 1093664768,
    (s32)"c_kinopio", (s32)"KNP_R_1", 1094713344, (s32)"c_kinopio", (s32)"KNP_R_1", 1095761920, (s32)"c_kinopio", (s32)"KNP_R_1",
    1096810496, (s32)"c_kinopio", (s32)"KNP_R_1", 1097859072, (s32)"c_kinopio", (s32)"KNP_R_1", 1098907648, (s32)"c_kinopio",
    (s32)"KNP_R_1", 1099431936, (s32)"c_kinopio", (s32)"KNP_R_1", 1099956224, (s32)"c_kinopio", (s32)"KNP_R_1", 1100480512,
    (s32)"c_kinopio", (s32)"KNP_R_1", 1101004800, (s32)"c_kinopio", (s32)"KNP_R_1", 1101529088, (s32)"c_kinopio", (s32)"KNP_R_1",
    1102053376, (s32)"c_kinopio", (s32)"KNP_R_1", 1102577664, (s32)"c_bom_n", (s32)"S_1", 0, (s32)"c_bom_n",
    (s32)"R_1", 0, (s32)"c_bom_n", (s32)"R_1", 1065353216, (s32)"c_bom_n", (s32)"R_1", 1073741824,
    (s32)"c_bom_n", (s32)"R_1", 1077936128, (s32)"c_bom_n", (s32)"R_1", 1082130432, (s32)"c_bom_n", (s32)"R_1",
    1084227584, (s32)"c_bom_n", (s32)"R_1", 1086324736, (s32)"c_bom_n", (s32)"R_1", 1088421888, (s32)"c_bom_n",
    (s32)"R_1", 1090519040, (s32)"c_bom_n", (s32)"R_1", 1091567616, (s32)"c_bom_n", (s32)"R_1", 1092616192,
    (s32)"c_bom_n", (s32)"R_1", 1093664768, (s32)"c_bom_n", (s32)"R_1", 1094713344, (s32)"c_bom_n", (s32)"R_1",
    1095761920, (s32)"c_bom_n", (s32)"R_1", 1096810496, (s32)"c_bom_n", (s32)"R_1", 1097859072, (s32)"c_bom_n",
    (s32)"R_1", 1098907648, (s32)"c_bom_n", (s32)"R_1", 1099431936, (s32)"c_bom_n", (s32)"R_1", 1099956224,
    (s32)"c_bom_n", (s32)"R_1", 1100480512, (s32)"c_tyusan", (s32)"CHU_S_1", 0, (s32)"c_tyusan", (s32)"CHU_S_1",
    1124270080, (s32)"c_tyusan", (s32)"CHU_S_1", 1124335616, (s32)"c_tyusan", (s32)"CHU_S_1", 1124401152, (s32)"c_tyusan",
    (s32)"CHU_R_1", 0, (s32)"c_tyusan", (s32)"CHU_R_1", 1065353216, (s32)"c_tyusan", (s32)"CHU_R_1", 1073741824,
    (s32)"c_tyusan", (s32)"CHU_R_1", 1077936128, (s32)"c_tyusan", (s32)"CHU_R_1", 1082130432, (s32)"c_tyusan", (s32)"CHU_R_1",
    1084227584, (s32)"c_tyusan", (s32)"CHU_R_1", 1086324736, (s32)"c_tyusan", (s32)"CHU_R_1", 1088421888, (s32)"c_tyusan",
    (s32)"CHU_R_1", 1090519040, (s32)"c_tyusan", (s32)"CHU_R_1", 1091567616, (s32)"c_tyusan", (s32)"CHU_R_1", 1092616192,
    (s32)"c_tyusan", (s32)"CHU_R_1", 1093664768, (s32)"c_tyusan", (s32)"CHU_R_1", 1094713344, (s32)"c_tyusan", (s32)"CHU_R_1",
    1095761920, 0, 0, 0, (s32)"c_luigi", (s32)"S_1", 1109393408, (s32)"c_luigi",
    (s32)"W_1", 1109393408, (s32)"c_luigi", (s32)"R_1", 1101004800, (s32)"c_nokorin", (s32)"S_1", 1109393408,
    (s32)"c_nokorin", (s32)"W_1", 1109393408, (s32)"c_nokorin", (s32)"R_1", 1101004800, (s32)"c_joho_a", (s32)"S_1",
    1114636288, (s32)"c_joho_a", (s32)"W_1", 1111490560, (s32)"c_joho_a", (s32)"R_1", 1103101952, 0,
    0, 0,
};

s32 chusan_mov_tbl[] = {
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 1, 0, 0, 1, 1,
    0, 0, 0, 0,
};

__declspec(section ".data") s32 chusan_act_tbl[] = {
    1, 2, 3, 3, 3, 2, 1, 0,
};

EVT_BEGIN(evt_yuunpc_minigame1)
    CALL(evt_npc_entry, STRING("yuunpc0"), STRING("c_kinopiko"))
    CALL(evt_npc_entry, STRING("yuunpc1"), STRING("c_roten"))
    CALL(evt_npc_entry, STRING("yuunpc2"), STRING("c_jugemu"))
    CALL(evt_npc_entry, STRING("yuunpc3"), STRING("c_kinopio"))
    CALL(evt_npc_set_position, STRING("yuunpc0"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc1"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc2"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc3"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc0"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc1"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc2"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc3"), 32)
    CALL(evt_ext_entry, 300, PTR(ext_yuunpc_minigame1_data), PTR(ext_yuunpc_minigame1_init), PTR(ext_yuunpc_minigame1_main), PTR(ext_yuunpc_dispent))
    RETURN
EVT_END()

EVT_BEGIN(evt_yuunpc_minigame2)
    CALL(evt_npc_entry, STRING("yuunpc0"), STRING("c_kinopiko"))
    CALL(evt_npc_entry, STRING("yuunpc1"), STRING("c_roten"))
    CALL(evt_npc_entry, STRING("yuunpc2"), STRING("c_jugemu"))
    CALL(evt_npc_entry, STRING("yuunpc3"), STRING("c_kinopio"))
    CALL(evt_npc_set_position, STRING("yuunpc0"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc1"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc2"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc3"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc0"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc1"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc2"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc3"), 32)
    CALL(evt_ext_entry, 300, PTR(ext_yuunpc_minigame2_data), PTR(ext_yuunpc_minigame2_init), PTR(ext_yuunpc_minigame2_main), PTR(ext_yuunpc_dispent))
    RETURN
EVT_END()

EVT_BEGIN(evt_yuunpc_minigame3)
    CALL(evt_npc_entry, STRING("yuunpc0"), STRING("c_kinopiko"))
    CALL(evt_npc_entry, STRING("yuunpc1"), STRING("c_roten"))
    CALL(evt_npc_entry, STRING("yuunpc2"), STRING("c_jugemu"))
    CALL(evt_npc_entry, STRING("yuunpc3"), STRING("c_kinopio"))
    CALL(evt_npc_set_position, STRING("yuunpc0"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc1"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc2"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc3"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc0"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc1"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc2"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc3"), 32)
    CALL(evt_ext_entry, 360, PTR(ext_yuunpc_minigame3_data), PTR(ext_yuunpc_minigame3_init), PTR(ext_yuunpc_minigame3_main), PTR(ext_yuunpc_dispent))
    RETURN
EVT_END()

EVT_BEGIN(evt_yuunpc_minigame4)
    CALL(evt_npc_entry, STRING("yuunpc0"), STRING("c_kinopiko"))
    CALL(evt_npc_entry, STRING("yuunpc1"), STRING("c_roten"))
    CALL(evt_npc_entry, STRING("yuunpc2"), STRING("c_jugemu"))
    CALL(evt_npc_entry, STRING("yuunpc3"), STRING("c_kinopio"))
    CALL(evt_npc_entry, STRING("yuunpc4"), STRING("c_bom_n"))
    CALL(evt_npc_entry, STRING("yuunpc5"), STRING("c_tyusan"))
    CALL(evt_npc_entry, STRING("yuusp0"), STRING("c_luigi"))
    CALL(evt_npc_entry, STRING("yuusp1"), STRING("c_nokorin"))
    CALL(evt_npc_entry, STRING("yuusp2"), STRING("c_joho_a"))
    CALL(evt_npc_set_position, STRING("yuunpc0"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc1"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc2"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc3"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc4"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuunpc5"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuusp0"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuusp1"), 0, -1000, 0)
    CALL(evt_npc_set_position, STRING("yuusp2"), 0, -1000, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc0"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc1"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc2"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc3"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc4"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuunpc5"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuusp0"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuusp1"), 32)
    CALL(evt_npc_flag_onoff, 1, STRING("yuusp2"), 32)
    CALL(evt_ext_entry, 900, PTR(ext_yuunpc_minigame4_data), PTR(ext_yuunpc_minigame4_init), PTR(ext_yuunpc_minigame4_main), PTR(ext_yuunpc_dispent))
    BEGIN_INLINE_EVENT
        CALL(evt_seq_wait, 2)
        CALL(evt_npc_delete, STRING("yuunpc0"))
        CALL(evt_npc_delete, STRING("yuunpc1"))
        CALL(evt_npc_delete, STRING("yuunpc2"))
        CALL(evt_npc_delete, STRING("yuunpc3"))
        CALL(evt_npc_delete, STRING("yuunpc4"))
        CALL(evt_npc_delete, STRING("yuunpc5"))
    END_INLINE_EVENT
    RETURN
EVT_END()

void ext_yuunpc_minigame1_init(void) {
}

void yuunpc_pose_minigame1_main(void) {
    f32 camX = camGetPtr(4)->cameraAt.x;
    ExtPose* ext = extGetPosePtr();
    f32 right = 500.0f + camX;
    s32 i;
    YuuNpc* npc = yuunpc_wp->npcs;
    f32 x, y, z;

    for (i = 0; i < yuunpc_wp->numNpc; i++, ext++, npc++) {
        if (npc->flags & 1) {
            x = ext->mtx[0][3];
            if (x > camX) {
                while (x > right) {
                    x -= 1000.0f;
                    ext->mtx[0][3] = x;
                }
            } else {
                while (x < camX - 500.0f) {
                    x += 1000.0f;
                    ext->mtx[0][3] = x;
                }
            }
            z = ext->mtx[2][3];
            if (z < -260.0f) {
                y = ext->mtx[1][3];
                if ((x >= -5000.0f && x <= -1500.0f) || (x >= 1700.0f && x <= 5000.0f) || (x >= 6000.0f && x <= 7000.0f)) {
                    if (y > -500.0f) {
                        ext->mtx[1][3] = y + -1000.0f;
                    }
                } else {
                    if (y < -500.0f) {
                        ext->mtx[1][3] = y - -1000.0f;
                    }
                }
            }
            if (irand(150) == 0) {
                if (irand(101) <= 80) {
                    ext->rot = angleABf(camX, 0.0f, x, z);
                } else {
                    ext->rot = angleABf(camX, 0.0f, x - 2.0f * (x - camX), z);
                }
            }
        }
        yuunpc_pose_sub(ext, npc);
    }
}

void ext_yuunpc_minigame2_init(void) {
}

void yuunpc_pose_minigame2_main(void) {
}

void ext_yuunpc_minigame3_init(void) {
}

void yuunpc_pose_minigame3_main(void) {
}

s32 hitcheck(YuuNpc* npc) {
    return 0;
}

s32 fallcheck(YuuNpc* npc) {
    s32 out = 0;
    s32 h;
    f32 y;

    npc->pos.y += npc->vy;
    if (npc->pos.x < -1800.0f || npc->pos.x >= 1800.0f || npc->pos.z < -150.0f || npc->pos.z >= 150.0f) {
        out = 1;
    }
    if (out) {
        h = -500;
    } else {
        h = yuunpc_wp->hit[(s32)((npc->pos.z - -150.0f) / 50.0f) * 72 + (s32)((npc->pos.x - -1800.0f) / 50.0f)];
    }
    y = h;
    if (npc->pos.y <= y) {
        npc->pos.y = y;
        npc->vy = 0.0f;
        return -1;
    }
    npc->vy -= 0.53333336f;
    if (npc->vy < -16.666666f) {
        npc->vy = -16.666666f;
    }
    return 0;
}

s32 goalincheck(YuuNpc* npc) {
    f32 r = npc->radius;
    f32 dz = npc->pos.z - npc->dest.z;
    f32 dx = npc->pos.x - npc->dest.x;

    if (dx * dx + dz * dz <= r * r) {
        if (npc->dest.x == npc->goal.x && npc->dest.z == npc->goal.z) {
            npc->pos.x = npc->dest.x;
            npc->pos.z = npc->dest.z;
            return -1;
        }
        npc->dest = npc->goal;
    }
    return 0;
}

void errper_set_rtn(YuuNpc* npc) {
    switch (npc->state) {
        case 0:
        case 2:
        case 4:
            npc->field_0x8 = -0.25f + 2.0f * (0.25f * (rand() / 32767.0f));
            break;
        case 1:
        case 3:
        case 5:
            npc->field_0x8 = -0.25f + 2.0f * (0.25f * (rand() / 32767.0f));
            break;
        case -1:
        case 6:
            npc->field_0x8 = -0.25f + 2.0f * (0.25f * (rand() / 32767.0f));
            break;
        default:
            npc->field_0x8 = -0.1f + 2.0f * (0.1f * (rand() / 32767.0f));
            break;
    }
}

void yuunpc_wp_flag_on(u16 flag) {
    yuunpc_wp->flags |= flag;
}

void yuunpc_wp_flag_off(u16 flag) {
    yuunpc_wp->flags &= ~flag;
}

u16 yuunpc_wp_flag_check(u16 flag) {
    return yuunpc_wp->flags & flag;
}

s32 yuunpc_juni(Vec* pos) {
    f32 x = pos->x;
    s32 n = 0;
    s32 i;
    YuuNpc* npc = yuunpc_wp->npcs;

    for (i = 0; i < yuunpc_wp->numNpc; i++, npc++) {
        if ((npc->flags & 2) && !(npc->flags & 0x40) && x < npc->pos.x) {
            n++;
        }
    }
    return n;
}

void ext_yuunpc_minigame4_init_sub(void) {
}

void ext_yuunpc_minigame4_init(void) {
    yuunpc_wp = _mapAlloc(sizeof(YuuNpcWork));
    memset(yuunpc_wp, 0, sizeof(YuuNpcWork));
    yuunpc_wp->numNpc = extGetPoseNum();
    yuunpc_wp->npcs = _mapAlloc(yuunpc_wp->numNpc * sizeof(YuuNpc));
    memset(yuunpc_wp->npcs, 0, yuunpc_wp->numNpc * sizeof(YuuNpc));
    ext_yuunpc_minigame4_init_sub();
}

void yuunpc_pose_minigame4_main(void) {
}

void yuunpc_disp(CameraId camera, void* param) {
    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    extDraw();
    extLoadTextureExit();
}

void ext_yuunpc_dispent(void) {
    dispEntry(4, 0.0f, 1, yuunpc_disp, NULL);
}

void ext_yuunpc_minigame1_main(void) {
    yuunpc_pose_minigame1_main();
}

void ext_yuunpc_minigame2_main(void) {
    yuunpc_pose_minigame2_main();
}

void ext_yuunpc_minigame3_main(void) {
    yuunpc_pose_minigame3_main();
}

void ext_yuunpc_minigame4_main(void) {
    yuunpc_pose_minigame4_main();
}

