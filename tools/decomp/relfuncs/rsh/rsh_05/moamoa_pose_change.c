// include: string.h
// include: memory.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: mario/mariost.h
// include: driver/mapdrv.h
// include: manager/evtmgr.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 field_0x28; f32 field_0x2c; u8 field_0x30[0x3c - 0x30]; s16 pose; u8 field_0x3e[2]; OSTime startTime; u8 field_0x48[4]; u8 kind; u8 field_0x4d[3]; } Moamoa;
// decl: typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; MapObject* mobj; f32 mobjY; Vec target[3]; s16 field_0x38; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 field_0x42; EventEntry* escapeEvt; u8 field_0x48[0x4c - 0x48]; s32 numDefs; MoamoaPoseDef defs[32]; f32 angle; f32 dist; s32 field_0x558; f32 breathDir; f32 breathDist; Vec breathPos; u8 field_0x570[0x870 - 0x570]; } MoamoaWork;
// decl: typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
// decl: static MoamoaWork* wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: void extReset(void);
// decl: int rand(void);
// decl: static f32 randf(f32 min, f32 max);
// decl: static void moamoa_pose_init(void);
// decl: static void moamoa_pose_main(void);
// decl: static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
// proto: static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim) {
    static const char* group_tbl[][2] = {
        {"c_n_moa_a", "S_1"},
        {"c_n_moa_b", "S_1"},
        {"c_kinodebu", "G_1"},
        {"c_puku_c", "U_1"},
        {"c_powan", "O_1"},
        {"c_smoko", "T_2"},
        {"c_rose", "G_1"},
        {"c_papab", "G_1"},
        {"c_mamab", "G_1"},
        {"c_konari", "G_1"},
        {"c_n_moa_a", "S_1"},
    };
    MoamoaPoseDef* def = wp->defs;
    s32 i;

    if (moa->flags & 0x800) {
        model = group_tbl[moa->kind][0];
        if (moa->kind >= 2) {
            anim = group_tbl[moa->kind][1];
        }
        if (moa->kind == 10) {
            anim = "S_2";
        }
    }
    for (i = 0; i < wp->numDefs; i++, def++) {
        if (!strcmp(def->model, model) && !strcmp(def->anim, anim)) {
            break;
        }
    }
    if (i < wp->numDefs && moa->pose != i) {
        if (moa->flags & 4) {
            if (strncmp(anim, "D", 1)) {
                return;
            }
        }
        if (moa->flags & 0x10) {
            if (strncmp(anim, "R", 1)) {
                return;
            }
        }
        moa->pose = i;
        moa->startTime = gp->renderTime;
    }
}
