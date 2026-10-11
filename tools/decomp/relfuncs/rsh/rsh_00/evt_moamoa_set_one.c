// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; Vec pos; f32 angle; s16 pose; u64 startTime; } Moamoa;
// decl: typedef struct MoamoaWork { s32 field_0x0; s32 count; Moamoa* moa; s32 numDefs; MoamoaPoseDef defs[32]; } MoamoaWork;
// decl: typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
// decl: static MoamoaWork* wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: USER_FUNC(evt_moamoa_set_one);
USER_FUNC(evt_moamoa_set_one) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    ExtPose* pose;
    Moamoa* moa;
    Mtx m;

    pose = extGetPosePtr();

    (moa = &wp->moa[idx])->state = 3;
    {
        Vec pos = {0.0f, 0.0f, 0.0f};

        pos.x = x;
        pos.y = y;
        pos.z = z;
        moa->pos = pos;
    }
    if (!(moa->flags & 1)) {
        PSMTXRotRad(m, 'y', 1.5707964f);
        PSMTXConcat(pose[idx].mtx, m, pose[idx].mtx);
        moa->flags |= 1;
    }
    return EVT_RETURN_DONE;
}
