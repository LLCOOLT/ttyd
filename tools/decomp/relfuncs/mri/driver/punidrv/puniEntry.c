// include: driver/punidrv.h
// include: driver/dispdrv.h
// include: memory.h
// include: string.h
// proto: void puniEntry(s32 poseNum, PunidrvTexInfo* texInfo, void (*initFunc)(void), void (*mainFunc)(void), void (*mainFunc2)(void));
void puniEntry(s32 poseNum, PunidrvTexInfo* texInfo, void (*initFunc)(void), void (*mainFunc)(void),
               void (*mainFunc2)(void)) {
    static f32 Normals[] = {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f};
    static GXColor Colors[] = {{0xFF, 0xFF, 0xFF, 0xFF}};
    static f32 UVs[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f};
    PunidrvWork* wp = work;
    PunidrvTexInfo* info;
    s32 texNum;
    s32 i;

    texNum = 0;
    for (info = texInfo; info->group != NULL; info++) {
        texNum++;
    }
    wp->poses = __memAlloc(HEAP_EXT, poseNum * sizeof(PunidrvPose));
    wp->poseNum = poseNum;
    wp->mainFunc = mainFunc;
    wp->mainFunc2 = mainFunc2;
    wp->texs = __memAlloc(HEAP_EXT, texNum * sizeof(PunidrvTex));
    wp->texNum = texNum;
    wp->mtxs = __memAlloc(HEAP_EXT, poseNum * sizeof(Mtx));
    wp->vtx = __memAlloc(HEAP_EXT, texNum * 12 * sizeof(f32));
    wp->normals = Normals;
    wp->colors = Colors;
    wp->uvs = UVs;
    wp->sort = __memAlloc(HEAP_EXT, poseNum * sizeof(PunidrvSort));
    wp->dl = __memAlloc(HEAP_EXT, texNum * 0x80);
    DCInvalidateRange(wp->dl, texNum * 0x80);
    wp->dlSize = __memAlloc(HEAP_EXT, texNum * sizeof(u32));
    memset(wp->poses, 0, wp->poseNum * sizeof(PunidrvPose));
    for (i = 0; i < poseNum; i++) {
        wp->sort[i].index = i;
        wp->poses[i].mtx = &wp->mtxs[i];
        wp->poses[i].scale = 1.0f;
    }
    PSMTXIdentity(wp->shadowMtx);
    dispEntry(CAMERA_OFFSCREEN, 0.0f, 1, puniMakeTexture, texInfo);
    if (initFunc != NULL) {
        initFunc();
    }
}
