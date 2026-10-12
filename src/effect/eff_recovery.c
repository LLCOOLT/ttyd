#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "driver/effdrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>

double sin(double);
double cos(double);
s32 rand(void);
s32 psndSFXOn_3D(const char* name, Vec* position);
EffectEntry* effStardustEntry(s32, f32, f32, f32, f32, f32, s32, s32);
int sprintf(char* str, const char* format, ...);
u32 strlen(const char* s);
void* memset(void* dst, int val, u32 n);
void effNumberGX(Mtx mtx, s32 type, s32 number, u8 alpha, s32 extra);

typedef struct MayaPoly {
    s32 pad0[2];
    s32 count;
    s16** strips;
} MayaPoly;

typedef struct MayaKeyList {
    s32 count;
    MayaPoly* polys;
} MayaKeyList;

typedef struct MayaAnimData {
    u8 pad0[4];
    f32 endTime;
    MayaKeyList* lists;
} MayaAnimData;

typedef struct MayaJoint {
    Mtx mtx;
    f32 alpha;
} MayaJoint;

typedef struct MayaAnim {
    u16 flags;
    f32 time;
    OSTime startTime;
    MayaAnimData* data;
    MayaJoint joints[1];
} MayaAnim;

MayaAnim* effMayaAnimAlloc(MayaAnimData* data);
void effDeleteMayaAnim(MayaAnim* anim);
void effPlayMayaAnim(MayaAnim* anim);
void effCalcMayaAnim(MayaAnim* anim);

typedef struct RecoveryWork {
    s8 type;         // 0x0
    s8 amount;       // 0x1
    s8 state;        // 0x2
    s32 alpha;       // 0x4
    Vec position;    // 0x8
    Vec velocity;    // 0x14
    Vec scale;       // 0x20
    s16 timer;       // 0x2c
    f32 angle;       // 0x30
    u32 tick;        // 0x34
    MayaAnim* anim;  // 0x38
    s32 delay;       // 0x3c
    f32 baseY;       // 0x40
} RecoveryWork;

#define QUAD(l, r, t, b, u) \
    GXBegin(GX_QUADS, GX_VTXFMT0, 4); \
    GXPosition3f32((l), (t), 0.0f); GXTexCoord2f32(0.0f, 0.0f); \
    GXPosition3f32((r), (t), 0.0f); GXTexCoord2f32((u), 0.0f); \
    GXPosition3f32((r), (b), 0.0f); GXTexCoord2f32((u), 1.0f); \
    GXPosition3f32((l), (b), 0.0f); GXTexCoord2f32(0.0f, 1.0f);

u32 recovery_effHermit_0[] = {
    0x00000000, 0x00000000, 0x00000140, 0x0000FFDD, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000007, 0x00000000, 0x00000007, 0x00000000, 0x00000007,
    0x00000000, 0x00000000, 0x0000FFA1, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x0000FFA1, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000009, 0x00000000, 0x00000000, 0x0000FFEA,
    0xFFEA0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00400005, 0x00050000, 0x00400002,
    0x00020000, 0x00400004, 0x00040000, 0x00000000, 0x00000000, 0xFFA10000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFA10000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000E0000,
    0x00000000, 0x00000000, 0x00040004, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000053,
    0xFFFFFFFF, 0x00000020, 0x00010001, 0x00000040, 0x00000000, 0x00000000,
    0x00000000, 0x0000FFA1, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x0000FFA1, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000013, 0x00000000, 0x00000000, 0x002C0000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x0033FFFF, 0xFFFF0000, 0x004C0003, 0x00030000,
    0x00400000, 0x00000000, 0x00000000, 0x00000000, 0xFFA10000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFA10000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00180000, 0x00000000,
    0x00000000, 0xFFFDFFFE, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000040, 0x00000000,
    0x00000040, 0x00000000, 0x00000040, 0x00000000, 0x00000000, 0x00000000,
    0x0000FFA1, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x0000FFA1, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000022, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFF50000,
    0x00000000, 0x00400000, 0x00000000, 0x00400000, 0x00000000, 0x00400000,
    0x00000000, 0x00000000, 0x00000000, 0xFFA10000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0xFFA10000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00310000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x0000000B, 0x00000000, 0x00000040, 0x00000000, 0x00000040,
    0x00000000, 0x00000040, 0x00000000, 0x00000000, 0x00000000, 0x0000FFA1,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000FFA1,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000036,
    0x00000000, 0x00000000, 0x0000FFFF, 0xFFFF0000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00400000, 0x00000000, 0x0040FFFF, 0xFFFF0000, 0x00400000, 0x00000000,
    0x00000000, 0x00000000, 0xFFA10000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0xFFA10000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00450000, 0x00000000, 0x0000FFE0, 0x00140014,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x0000004C, 0xFFFEFFFE, 0x00000026, 0x00010001,
    0x00000040, 0xFFFEFFFE, 0x00000000, 0x00000000, 0x0000FFA1, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000FFA1, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000004F, 0x00000000,
    0x00000000, 0x02000036, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000FFF9,
    0x00000000, 0x00600005, 0x00000000, 0x0000FFFA, 0x00000000, 0x00000000,
    0x00000000, 0xFFA10000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0xFFA10000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000,
};
static u8 color_rotation_data[] = {
    0xFE, 0xAC, 0xAC, 0xFE, 0xAC, 0xD5, 0xFE, 0xB4, 0x9A, 0xD5, 0xB4, 0xFE,
    0xB4, 0xB4, 0xFE, 0xB4, 0xDD, 0xFE, 0xB4, 0xFE, 0xFE, 0xB4, 0xFE, 0xD5,
    0xB4, 0xFE, 0xB4, 0xD5, 0xFE, 0xB4, 0xFE, 0xFE, 0xB4, 0xFE, 0xD5, 0xAC,
};
u32 recovery_effFace_pPlane2_q007_0[] = {
    0x0004FD00, 0xFD000000, 0x00000200, 0x0300FD00, 0x00000200, 0x02000300,
    0x03000000, 0x02000000, 0xFD000300, 0x00000000, 0x00000000,
};
u32* recovery_effFaceDt_pPlane2_q007 = recovery_effFace_pPlane2_q007_0;
u32 recovery_effAnimRST[] = {
    0x0000000A, (u32)recovery_effHermit_0, 0x00000001, (u32)&recovery_effFaceDt_pPlane2_q007,
};
u32 recovery_effAnimRSTDt[] = { 0x1, (u32)recovery_effAnimRST };
MayaAnimData recovery_effAnimDt = { { 0 }, 79.0f, (MayaKeyList*)recovery_effAnimRSTDt };

GXColor unk_80423040;
GXColor unk_80423044;

void effRecoveryMain(EffectEntry* effect);
void effRecoveryMain2(EffectEntry* effect);

void effRecoveryDisp(CameraId cameraId, EffectEntry* effect);
void effRecoveryDisp2(CameraId cameraId, EffectEntry* effect);
void effRecoveryDisp3(CameraId cameraId, EffectEntry* effect);
void effRecoveryDisp4(CameraId cameraId, EffectEntry* effect);

#pragma opt_propagation off
#pragma opt_lifetimes off
EffectEntry* effRecoveryEntry(s32 type, s32 amount, f32 x, f32 y, f32 z) {
    EffectEntry* effect;
    RecoveryWork* work;
    s32 i;
    RecoveryWork* pp;
    s32 size;
    f32 ang;
    f32 zero;
    s32 delay;

    effect = effEntry();
    switch (type) {
    case 2:
    case 3:
        amount = 0;
        break;
    case 4:
    case 5:
        amount = 20;
        break;
    case 6:
        amount = 11;
        break;
    }
    effect->type = "Recovery\0\0\0";
    effect->count = amount + 1;
    size = effect->count * sizeof(RecoveryWork);
    work = __memAlloc(HEAP_EFFECT, size);
    effect->userdata = work;
    switch (type) {
    case 6:
        effect->callback = effRecoveryMain2;
        break;
    default:
        effect->callback = effRecoveryMain;
        break;
    }
    work->anim = effMayaAnimAlloc(&recovery_effAnimDt);
    effPlayMayaAnim(work->anim);
    work->type = type;
    work->amount = amount;
    work->position.x = x;
    work->position.y = y;
    work->position.z = z;
    work->timer = 0;
    work->tick = gp->retraceCount;
    work->alpha = 255;
    work->baseY = -30.0f;
    {
    Vec sfxPos;
    Vec pos = { 0.0f, 0.0f, 0.0f };
    pos.x = work->position.x;
    pos.y = work->position.y;
    pos.z = work->position.z;
    sfxPos = pos;
    switch (work->type) {
    case 0:
    case 7:
        if (work->amount <= 5) {
            psndSFXOn_3D("SFX_HP_RECOVER_SMALL1", &sfxPos);
        } else if (work->amount <= 10) {
            psndSFXOn_3D("SFX_HP_RECOVER_MID1", &sfxPos);
        } else {
            psndSFXOn_3D("SFX_HP_RECOVER_BIG1", &sfxPos);
        }
        break;
    case 1:
    case 8:
        if (work->amount <= 5) {
            psndSFXOn_3D("SFX_FP_RECOVER_SMALL1", &sfxPos);
        } else if (work->amount <= 10) {
            psndSFXOn_3D("SFX_FP_RECOVER_MID1", &sfxPos);
        } else {
            psndSFXOn_3D("SFX_FP_RECOVER_BIG1", &sfxPos);
        }
        break;
    case 4:
        psndSFXOn_3D("SFX_HP_RECOVER_BIG1", &sfxPos);
        break;
    case 5:
        psndSFXOn_3D("SFX_FP_RECOVER_BIG1", &sfxPos);
        break;
    }
    }
    switch (type) {
    case 6:
        effDeleteMayaAnim(work->anim);
        work->timer = 180;
        break;
    }
    zero = 0.0f;
    delay = 8;
    pp = work + 1;
    for (i = 1; i < effect->count; i++, pp++, delay += 8) {
        work = pp;
        work->position.x = zero;
        switch (type) {
        case 4:
        case 5:
            work->position.y = (i < 10) ? zero : -15.0f;
            break;
        default:
            work->position.y = 0.0f;
            break;
        }
        work->position.z = zero;
        work->scale.x = zero;
        work->scale.y = zero;
        work->scale.z = zero;
        work->velocity.x = zero;
        work->velocity.y = zero;
        work->velocity.z = zero;
        work->timer = 0;
        work->state = 0;
        work->alpha = 255;
        work->angle = zero;
        switch (type) {
        case 6:
            if (i == 1) {
                work->scale.x = work->scale.y = work->scale.z = 1.5f;
                work->alpha = 0;
                work->delay = 0;
            } else {
                work->scale.x = work->scale.y = work->scale.z = 0.3f;
                work->angle = (f32)(((i & 1) ? irand(80) : -irand(80)) + 90);
                work->velocity.x = 1.8f * (f32)cos(6.2831855f * work->angle / 360.0f);
                work->velocity.y = 1.8f * (f32)sin(6.2831855f * work->angle / 360.0f);
                work->alpha = 255;
                work->delay = delay;
            }
            break;
        }
    }
    return effect;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset

void effRecoveryMain(EffectEntry* effect) {
    RecoveryWork* work = effect->userdata;
    RecoveryWork* p;
    s32 type = work->type;
    s32 done = 0;
    s32 go = 0;
    u32 n = 0;
    s32 i;
    s32 amount;
    f32 baseY = work->baseY;
    f32 x, y, z;
    f32 a, d;

    effCalcMayaAnim(work->anim);
    if (gp->retraceCount > work->tick) {
        n = gp->retraceCount - work->tick;
    }
    if (n < 1) {
        n = 1;
    }
    while (n-- != 0) {
        p = work = effect->userdata;
        amount = work->amount;
        x = work->position.x;
        y = work->position.y;
        z = work->position.z;
        if (type == 4 || type == 5) {
            amount = 10;
        }
        work->timer++;
        if (work->timer > 10) {
            go = 1;
        }
        p++;
        for (i = 1; i < effect->count; i++, p++) {
            switch (p->state) {
            case 0:
                if (go) {
                    a = 6.2831855f * (90.0f + 360.0f * (f32)(i - 1) / (f32)amount) / 360.0f;
                    p->velocity.x = 12.0f * (f32)sin(a);
                    p->velocity.y = 0.0f;
                    p->velocity.z = 12.0f * -(f32)cos(a);
                    p->timer = 0;
                    p->state++;
                }
                break;
            case 1:
                if (p->timer < 10) {
                    p->velocity.x *= 0.7f;
                    p->velocity.y *= 0.7f;
                    p->velocity.z *= 0.7f;
                    p->position.x += p->velocity.x;
                    p->position.y += p->velocity.y;
                    p->position.z += p->velocity.z;
                    p->scale.x = p->scale.y = p->scale.z = 1.0f;
                    p->timer++;
                } else {
                    p->timer = 10;
                    p->state++;
                }
                break;
            case 2:
                if (--p->timer <= 0) {
                    p->timer = 0;
                    p->state++;
                }
                break;
            case 3:
                if (p->timer < 40) {
                    a = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(0.0f, 360.0f, 11, ++p->timer, 40);
                    d = distABf(0.0f, 0.0f, p->position.x, p->position.z) * 0.99f;
                    a = 6.2831855f * (90.0f + (a + 360.0f * (f32)(i - 2) / (f32)amount)) / 360.0f;
                    p->position.x = d * (f32)sin(a);
                    p->position.z = d * -(f32)cos(a);
                } else {
                    p->timer = rand() % 20;
                    p->state++;
                }
                break;
            case 4:
                if (--p->timer <= 0) {
                    p->timer = 0;
                    p->state++;
                }
                break;
            case 5:
                if (p->timer < 16) {
                    p->timer++;
                    p->position.x = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(p->position.x, 0.0f, 1, p->timer, 16);
                    p->position.y = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(p->position.y, baseY, 1, p->timer, 16);
                    p->position.z = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(p->position.z, 0.0f, 1, p->timer, 20);
                    p->scale.x = p->scale.y = p->scale.z = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(1.0f, 0.0f, 1, p->timer, 16);
                } else {
                    p->state++;
                }
                break;
            case 6:
                done++;
                break;
            }
        }
        if (type <= 1u || type == 7 || type == 8 || type == 4 || type == 5) {
            if (done >= amount) {
                work = effect->userdata;
                if (type != 7 && type != 8) {
                    Vec sfxPos;
                    effStardustEntry(2, x, y - 20.0f, z, 30.0f, 30.0f, 2, 30);
                    {
                    Vec pos = { 0.0f, 0.0f, 0.0f };
                    pos.x = work->position.x;
                    pos.y = work->position.y;
                    pos.z = work->position.z;
                    sfxPos = pos;
                    switch (work->type) {
                    case 0:
                        if (work->amount <= 5) {
                            psndSFXOn_3D("SFX_HP_RECOVER_SHINE1", &sfxPos);
                        } else if (work->amount <= 10) {
                            psndSFXOn_3D("SFX_HP_RECOVER_SHINE2", &sfxPos);
                        } else {
                            psndSFXOn_3D("SFX_HP_RECOVER_SHINE3", &sfxPos);
                        }
                        break;
                    case 1:
                        if (work->amount <= 5) {
                            psndSFXOn_3D("SFX_FP_RECOVER_SHINE1", &sfxPos);
                        } else if (work->amount <= 10) {
                            psndSFXOn_3D("SFX_FP_RECOVER_SHINE2", &sfxPos);
                        } else {
                            psndSFXOn_3D("SFX_FP_RECOVER_SHINE3", &sfxPos);
                        }
                        break;
                    case 4:
                        psndSFXOn_3D("SFX_HP_RECOVER_SHINE3", &sfxPos);
                        break;
                    case 5:
                        psndSFXOn_3D("SFX_FP_RECOVER_SHINE3", &sfxPos);
                        break;
                    }
                    }
                }
                effDeleteMayaAnim(work->anim);
                effDelete(effect);
                return;
            }
        }
    }
    work = effect->userdata;
    work->tick = gp->retraceCount;
    {
    Vec calc = { 0.0f, 0.0f, 0.0f };
    calc.x = work->position.x;
    calc.y = work->position.y;
    calc.z = work->position.z;
    dispEntry(CAMERA_3D, dispCalcZ(&calc), 1, (DispCallback)effRecoveryDisp, effect);
    }
    if (type <= 1u || type == 7 || type == 8) {
        Vec calc = { 0.0f, 0.0f, 0.0f };
        calc.x = work->position.x;
        calc.y = work->position.y;
        calc.z = work->position.z;
        dispEntry(CAMERA_3D, dispCalcZ(&calc), 2, (DispCallback)effRecoveryDisp2, effect);
    }
    if (type == 4 || type == 5) {
        Vec calc = { 0.0f, 0.0f, 0.0f };
        calc.x = work->position.x;
        calc.y = work->position.y;
        calc.z = work->position.z;
        dispEntry(CAMERA_3D, dispCalcZ(&calc), 2, (DispCallback)effRecoveryDisp3, effect);
    }
}

void effRecoveryMain2(EffectEntry* effect) {
    RecoveryWork* work = effect->userdata;
    Vec calc;
    Vec pos = { 0.0f, 0.0f, 0.0f };
    s32 i;

    pos.x = work->position.x;
    pos.y = work->position.y;
    pos.z = work->position.z;
    calc = pos;
    if (work->timer < 1000) {
        work->timer--;
    }
    if (work->timer < 32) {
        work->alpha = work->timer << 3;
    }
    if (work->timer < 0) {
        effStardustEntry(2, work->position.x, work->position.y, work->position.z, 40.0f, 45.0f, 6, 30);
        effDelete(effect);
        return;
    }
    work++;
    for (i = 1; i < effect->count; i++, work++) {
        if (work->delay != 0) {
            work->delay--;
            continue;
        }
        work->position.x += work->velocity.x;
        work->position.y += work->velocity.y;
        work->position.z += work->velocity.z;
        work->velocity.x *= 0.95f;
        work->velocity.y *= 0.95f;
        work->velocity.z *= 0.95f;
        if (i == 1) {
            work->alpha += 5;
            if (work->alpha > 128) {
                work->alpha = 128;
            }
        } else {
            work->alpha -= 8;
            if (work->alpha < 0) {
                work->position.x = 0.0f;
                work->position.y = 0.0f;
                work->position.z = 0.0f;
                work->velocity.x = 2.0f * (f32)cos(6.2831855f * work->angle / 360.0f);
                work->velocity.y = 2.0f * (f32)sin(6.2831855f * work->angle / 360.0f);
                work->alpha = 255;
            }
        }
    }
    dispEntry(CAMERA_3D, dispCalcZ(&calc), 2, (DispCallback)effRecoveryDisp4, effect);
}

void effRecoveryDisp(CameraId cameraId, EffectEntry* effect) {
    RecoveryWork* work = effect->userdata;
    RecoveryWork* p;
    CameraEntry* cam;
    s32 type;
    s32 i;
    u8* c;
    GXColor color;
    GXTexObj texObj;
    Mtx transMtx;
    Mtx rotMtx;
    Mtx scaleMtx;
    Mtx base;

    cam = camGetPtr(cameraId);
    type = work->type;
    PSMTXTrans(transMtx, work->position.x, work->position.y, work->position.z);
    PSMTXRotRad(rotMtx, 'y', 0.017453292f * -camGetPtr(cameraId)->viewYaw);
    PSMTXConcat(transMtx, rotMtx, base);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(0);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    switch (type) {
    case 0:
    case 2:
    case 4:
    case 7:
        effGetTexObj(18, &texObj);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
        effGetTexObj(20, &texObj);
        GXLoadTexObj(&texObj, GX_TEXMAP1);
        break;
    case 1:
    case 3:
    case 5:
    case 8:
        effGetTexObj(19, &texObj);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
        effGetTexObj(21, &texObj);
        GXLoadTexObj(&texObj, GX_TEXMAP1);
        break;
    }
    p = effect->userdata;
    PSMTXTrans(transMtx, p->position.x, p->position.y, p->position.z);
    PSMTXRotRad(rotMtx, 'y', 0.017453292f * -camGetPtr(cameraId)->viewYaw);
    PSMTXConcat(transMtx, rotMtx, transMtx);
    PSMTXScale(scaleMtx, 10.0f, 10.0f, 10.0f);
    PSMTXConcat(transMtx, scaleMtx, transMtx);
    PSMTXTrans(scaleMtx, 0.0f, 2.0f, 0.0f);
    PSMTXConcat(transMtx, scaleMtx, transMtx);
    if (type <= 1u || (u32)(type - 7) <= 1u || type == 4 || type == 5) {
        PSMTXConcat(transMtx, (void*)((u8*)p->anim + 0x14), transMtx);
    }
    PSMTXConcat(cam->view, transMtx, transMtx);
    PSMTXScale(scaleMtx, 0.1f, 0.1f, 0.1f);
    PSMTXConcat(transMtx, scaleMtx, transMtx);
    GXLoadPosMtxImm(transMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    QUAD(-16.0f, 16.0f, 16.0f, -16.0f, 1.0f)
    if (type != 2 && type != 3) {
        p++;
        GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
        GXSetZCompLoc(GX_FALSE);
        GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        for (i = 1; i < effect->count; i++, p++) {
            color = unk_80423040;
            color.a = p->alpha;
            c = &color_rotation_data[((gp->retraceCount + i) % 12) * 3];
            color.r = c[0];
            color.g = c[1];
            color.b = c[2];
            GXSetTevColor(GX_TEVREG0, color);
            PSMTXTrans(transMtx, p->position.x, p->position.y, p->position.z);
            PSMTXScale(scaleMtx, p->scale.x, p->scale.y, p->scale.z);
            PSMTXConcat(transMtx, scaleMtx, transMtx);
            PSMTXConcat(base, transMtx, transMtx);
            PSMTXConcat(camGetPtr(cameraId)->view, transMtx, transMtx);
            GXLoadPosMtxImm(transMtx, GX_PNMTX0);
            GXSetCurrentMtx(GX_PNMTX0);
            QUAD(-6.0f, 6.0f, 6.0f, -6.0f, 2.0f)
        }
    }
}

void effRecoveryDisp2(CameraId cameraId, EffectEntry* effect) {
    RecoveryWork* work = effect->userdata;
    CameraEntry* cam;
    s32 type;
    s32 amount;
    s32 len;
    char buf[0x20];
    Mtx mtx;
    Mtx rot;
    Mtx tmp;
    f32 off;

    cam = camGetPtr(cameraId);
    amount = work->amount;
    type = work->type;
    sprintf(buf, "%d", amount);
    len = strlen(buf);
    PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
    PSMTXRotRad(rot, 'y', 0.017453292f * -camGetPtr(cameraId)->viewYaw);
    PSMTXConcat(mtx, rot, mtx);
    PSMTXTrans(tmp, 0.0f, 0.0f, 1.0f);
    PSMTXConcat(mtx, tmp, mtx);
    PSMTXScale(tmp, 10.0f, 10.0f, 10.0f);
    PSMTXConcat(mtx, tmp, mtx);
    PSMTXTrans(tmp, 0.0f, 2.0f, 0.0f);
    PSMTXConcat(mtx, tmp, mtx);
    PSMTXConcat(mtx, (void*)((u8*)work->anim + 0x14), mtx);
    PSMTXScale(tmp, 0.035f, 0.035f, 0.035f);
    PSMTXConcat(mtx, tmp, mtx);
    off = 24.0f * (f32)(-(len - 1));
    off *= 0.5f;
    PSMTXTrans(tmp, off, 0.0f, 0.0f);
    PSMTXConcat(mtx, tmp, mtx);
    switch (type) {
    case 0:
    case 2:
    case 7:
        effNumberGX(mtx, 0, amount, 0xFF, 1);
        break;
    case 1:
    case 3:
    case 8:
        effNumberGX(mtx, 1, amount, 0xFF, 1);
        break;
    }
}

void effRecoveryDisp3(CameraId cameraId, EffectEntry* effect) {
    RecoveryWork* work = effect->userdata;
    CameraEntry* cam;
    s32 type;
    s32 i;
    GXTexObj texObj;
    Mtx mtx;
    Mtx rot;
    Mtx tmp;
    Mtx base;
    f32 w;
    f32 left;
    f32 right;
    f32 top;
    f32 bot;

    cam = camGetPtr(cameraId);
    type = work->type;
    PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
    PSMTXRotRad(rot, 'y', 0.017453292f * -camGetPtr(cameraId)->viewYaw);
    PSMTXConcat(mtx, rot, mtx);
    PSMTXTrans(tmp, 0.0f, 0.0f, 1.0f);
    PSMTXConcat(mtx, tmp, mtx);
    PSMTXScale(tmp, 10.0f, 10.0f, 10.0f);
    PSMTXConcat(mtx, tmp, mtx);
    PSMTXTrans(tmp, 0.0f, 2.0f, 0.0f);
    PSMTXConcat(mtx, tmp, mtx);
    PSMTXConcat(mtx, (void*)((u8*)work->anim + 0x14), base);
    PSMTXConcat(cam->view, base, base);
    PSMTXScale(tmp, 0.05f, 0.05f, 0.05f);
    PSMTXConcat(base, tmp, base);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    w = 108.0f;
    left = -w * 0.5f;
    right = left + w;
    top = 20.0f;
    bot = -20.0f;
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            effGetTexObj(0x8B, &texObj);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            GXSetChanMatColor(GX_COLOR0A0, (GXColor){ 0x00, 0x00, 0x00, 0xA0 });
        } else {
            effGetTexObj(0x8A, &texObj);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            if (type == 4) {
                GXSetChanMatColor(GX_COLOR0A0, (GXColor){ 0xF5, 0x98, 0x9D, 0xFF });
            } else {
                GXSetChanMatColor(GX_COLOR0A0, (GXColor){ 0x5D, 0xC1, 0x00, 0xFF });
            }
        }
        PSMTXTrans(mtx, (f32)((1 - i) * 2), (f32)(-(1 - i) * 2), 0.0f);
        PSMTXConcat(base, mtx, mtx);
        GXLoadPosMtxImm(mtx, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        QUAD(left, right, top, bot, 1.0f)
    }
}

void effRecoveryDisp4(CameraId cameraId, EffectEntry* effect) {
    RecoveryWork* work = effect->userdata;
    CameraEntry* cam;
    s32 i;
    s32 alpha;
    GXColor color;
    GXColor color2;
    GXColor color3;
    Mtx mtx;
    Mtx rotMtx;
    Mtx scaleMtx;
    Mtx base;
    GXTexObj texObj;
    u8* c;
    f32 w;
    f32 nw;
    f32 l;
    f32 r;
    f32 v;
    f32 off;
    f32 u;

    cam = camGetPtr(cameraId);
    alpha = work->alpha;
    PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
    PSMTXRotRad(rotMtx, 'y', 0.017453292f * -camGetPtr(cameraId)->viewYaw);
    PSMTXConcat(mtx, rotMtx, base);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    w = 32.0f;
    nw = -w;
    work++;
    for (i = 1; i < effect->count; i++, work++) {
        if (work->delay == 0) {
            if (i == 1) {
                effGetTexObj(18, &texObj);
                GXLoadTexObj(&texObj, GX_TEXMAP0);
                color = (GXColor){ 0xFF, 0xFF, 0xFF, 0x00 };
                color.a = alpha * work->alpha / 255;
                GXSetChanMatColor(GX_COLOR0A0, color);
            } else {
                color2 = unk_80423044;
                c = &color_rotation_data[((gp->retraceCount + i) % 12) * 3];
                color2.r = c[0];
                color2.g = c[1];
                color2.b = c[2];
                color2.a = alpha * work->alpha / 255;
                effGetTexObj(20, &texObj);
                GXLoadTexObj(&texObj, GX_TEXMAP0);
                GXSetChanMatColor(GX_COLOR0A0, color2);
            }
            PSMTXTrans(mtx, work->position.x, work->position.y, work->position.z);
            PSMTXScale(scaleMtx, work->scale.x, work->scale.y, work->scale.z);
            if (i != 1) {
                PSMTXRotRad(rotMtx, 'z', 0.017453292f * (work->angle - 90.0f));
            } else {
                PSMTXRotRad(rotMtx, 'z', 0.0f);
            }
            PSMTXConcat(base, mtx, mtx);
            PSMTXConcat(mtx, scaleMtx, mtx);
            PSMTXConcat(mtx, rotMtx, mtx);
            PSMTXConcat(cam->view, mtx, mtx);
            GXLoadPosMtxImm(mtx, GX_PNMTX0);
            GXSetCurrentMtx(GX_PNMTX0);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            u = 1.0f;
            off = 0.0f;
            if (i == 1) {
                off = 8.0f;
            }
            if (i != 1) {
                u = 2.0f;
            }
            l = nw / 2.0f;
            r = 16.0f;
            v = 1.0f;
            GXPosition3f32(l, r + off, 0.0f); GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(r, r + off, 0.0f); GXTexCoord2f32(u, 0.0f);
            GXPosition3f32(r, l + off, 0.0f); GXTexCoord2f32(u, v);
            GXPosition3f32(l, l + off, 0.0f); GXTexCoord2f32(0.0f, v);
        }
    }
}
