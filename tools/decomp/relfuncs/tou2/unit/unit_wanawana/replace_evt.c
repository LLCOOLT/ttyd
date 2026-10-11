// include: battle/battle.h
// include: battle/battle_unit.h
// include: driver/animdrv.h
// include: driver/dispdrv.h
// include: memory.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: typedef struct WanaWork { s32 ready; s32 poseId; Mtx mtx; GXTexObj obj; BattleUnitPart* part; smartEntry* tex; } WanaWork;
// decl: void replace_callback(BattleUnitPart* part, s32 type);
// decl: void replace_disp(CameraId camera, void* param);
// proto: USER_FUNC(replace_evt);
USER_FUNC(replace_evt) {
    BattleUnitPart* part = BattleGetUnitPartsPtr(BattleTransID(event, -2), 1);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, -2));
    AnimationPoseData* data = animPoseGetAnimBaseDataPtr(part->poseId);
    WanaWork* wp;
    s32 w;
    s32 h;

    {
        Vec min;
        Vec max;

        min = (Vec){data->bboxMin.x, data->bboxMin.y, data->bboxMin.z};
        max = (Vec){data->bboxMax.x, data->bboxMax.y, data->bboxMax.z};

        w = 2.0f * (max.x - min.x);
        h = 2.0f * (max.z - min.z);
    }
    w += w & 1;
    h += h & 1;
    wp = __memAlloc(HEAP_BATTLE, sizeof(WanaWork));
    wp->tex = smartAlloc(GXGetTexBufferSize(w / 2, h / 2, GX_TF_RGB5A3, GX_FALSE, 0), 1);
    wp->poseId = part->poseId;
    wp->part = part;
    GXInitTexObj(&wp->obj, wp->tex->address, w / 2, h / 2, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&wp->obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    PSMTXIdentity(wp->mtx);
    animGetPtr()->poses[part->poseId].flags |= 0x10;
    *(void**)((u8*)part + 0x210) = replace_callback;
    *(WanaWork**)((u8*)unit + 0x310) = wp;
    *(smartEntry**)((u8*)unit + 0x318) = wp->tex;
    wp->ready = 0;
    dispEntry(CAMERA_SHADOW, 0.0f, 0, replace_disp, wp);
    return EVT_RETURN_DONE;
}
