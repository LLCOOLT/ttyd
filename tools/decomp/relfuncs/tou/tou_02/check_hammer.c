// include: mario/mario.h
// include: party.h
// include: party/party_cloud.h
// include: system.h
// include: driver/camdrv.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Fan { u16 flags; s16 state; s16 animIdx; u8 pad_0x6[2]; u64 time; Vec pos; Vec vel; f32 field_0x28; Vec target; Vec param; s16 timer; } Fan;
// decl: typedef struct FanAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } FanAnim;
// decl: typedef struct FanWork { s32 num; Fan* fans; s32 animNum; FanAnim anim[32]; s32 hammerTimer; s32 count; s32 sfxId; u8 vol; } FanWork;
// decl: typedef struct FanData { const char* name; const char* anim; f32 rate; } FanData;
// decl: FanWork* fan_wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: static inline f32 fan_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
// decl: static inline f32 fan_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
// decl: f32 cloudGetBreathDist(void);
// proto: s32 check_hammer(Fan* fan);
#pragma opt_propagation off
#pragma opt_lifetimes off
s32 check_hammer(Fan* fan) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;
    f32 rot;
    f32 x;
    f32 z;
    f32 angle;
    f32 dist;
    Vec pos;

    if (mario->position.y > 0.0f) {
        return 0;
    }
    if (fan->flags & 1) {
        return 0;
    }
    if (mario->currMotionId == 0x12 && fan_wp->hammerTimer > 10) {
        rot = 6.2831855f * reviseAngle(mario->unk1A8 - 90.0f + camGetPtr(CAMERA_3D)->viewYaw) / 360.0f;

        x = mario->position.x + 35.0f * fan_sin(rot);
        z = mario->position.z - 35.0f * fan_cos(rot);
        if (distABf(fan->pos.x, fan->pos.z, x, z) < 35.0f) {
            return 1;
        }
    }
    if (mario->currMotionId == 0x13 && (s32)mario->currSubMotionId == 0x14 && PSVECDistance(&mario->position, &fan->pos) < 65.0f) {
        return 1;
    }
    party = partyGetPtr(0);
    if (party != NULL && party->currentMemberId == 5 && (party->flags & 0x100)) {
        angle = 6.2831855f * cloudGetBreathDir() / 360.0f;
        dist = cloudGetBreathDist();
        pos.x = party->position.x + dist * fan_sin(angle);
        pos.y = party->position.y;
        pos.z = party->position.z - dist * fan_cos(angle);
        if (angle >= 0.0f && PSVECDistance(&pos, &fan->pos) < 30.0f) {
            return 2;
        }
    }
    return 0;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
