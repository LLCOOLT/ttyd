// include: driver/camdrv.h
// include: driver/icondrv.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: typedef struct I3 { s32 v[3]; } I3;
// decl: static const I3 disp_slot_icons = {{0x1F3, 0x1F3, 0x1F3}};
// decl: typedef struct GoryuuWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } GoryuuWork;
// decl: typedef struct SlotWork { u32 flags; s32 phase; f32 reberAngle; f32 angle[2][3]; f32 speed[3]; s8 state[3]; s8 face[2][3]; s8 stopCount[3]; s32 wait[3]; s32 extra[3]; s32 counter; s32 neonCount; s32 monteCount; s32 nowSlot; s32 caseId[2]; EventEntry* monteEvt; s32 sfxId; s16 cursor; } SlotWork;
// decl: typedef struct SlotDrum { const char* drum[3]; const char* reber; const char* anim; const char* window[3][3]; const char* neon[3]; } SlotDrum;
// decl: #define DRUMNAME ((SlotDrum*)drumname)
// decl: void mapObjGetPos(const char* name, Vec* pos);
// proto: void goryuugijo_disp_slot(CameraId camera, void* param);
void goryuugijo_disp_slot(CameraId camera, void* param) {
    SlotWork* data = ((GoryuuWork*)param)->data;
    I3 icons = disp_slot_icons;
    s32 i;
    Vec pos;
    f32 sx;
    f32 sy;
    f32 sz;
    CameraEntry* cam;
    f32 proj[7];
    f32 vp[6];
    Mtx trans;
    Mtx scale;
    Mtx mtx;

    for (i = 0; i < 3; i++) {
        if (data->state[i] == 2 && i == data->cursor) {
            mapObjGetPos(DRUMNAME[data->nowSlot].drum[i], &pos);
            pos.x -= 25.0f;
            pos.y += 10.0f;
            cam = camGetPtr(CAMERA_3D);
            GXSetProjection(cam->projection, cam->projType);
            GXGetProjectionv(proj);
            GXGetViewportv(vp);
            GXProject(pos.x, pos.y, pos.z, cam->view, proj, vp, &sx, &sy, &sz);
            cam = camGetPtr(camera);
            GXSetProjection(cam->projection, cam->projType);
            PSMTXScale(scale, 1.1f, 1.1f, 1.1f);
            PSMTXTrans(trans, -304.0f + sx, 240.0f - sy, 0.0f);
            PSMTXConcat(trans, scale, mtx);
            iconDispGx2(mtx, 0x10, 0x1F2);
            PSMTXTrans(trans, -304.0f + sx, 31.35f + (240.0f - sy), 0.0f);
            PSMTXConcat(trans, scale, mtx);
            ((void (*)(Mtx, s16, u16))iconDispGx2)(mtx, 0x10, icons.v[i]);
        }
    }
}
