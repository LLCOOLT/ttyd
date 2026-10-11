// include: driver/animdrv.h
// decl: s32 EXIGetType(s32 chan, u32 dev, u32* type);
// proto: USER_FUNC(is_dol_viewer);
USER_FUNC(is_dol_viewer) {
    u32 type;

    EXIGetType(0, 2, &type);
    if (type == 0x05070000) {
        animPoseRelease(animPoseEntry("MOBJ_EFF_las_mon", 0));
        animPoseRelease(animPoseEntry("EFF_treasure_map", 0));
        animPoseRelease(animPoseEntry("MOBJ_EFF_mahojin_omote", 0));
        animPoseRelease(animPoseEntry("MOBJ_EFF_mahojin_ura", 0));
        animPoseRelease(animPoseEntry("MOBJ_EFF_laser", 0));
        animPoseRelease(animPoseEntry("OFF_d_tizu_tex", 0));
        animPoseRelease(animPoseEntry("TIZ_stg_1", 0));
        animPoseRelease(animPoseEntry("TIZ_stg_2", 0));
        animPoseRelease(animPoseEntry("TIZ_stg_3", 0));
        animPoseRelease(animPoseEntry("TIZ_stg_4", 0));
        animPoseRelease(animPoseEntry("TIZ_stg_5", 0));
        animPoseRelease(animPoseEntry("TIZ_stg_6", 0));
        animPoseRelease(animPoseEntry("TIZ_stg_7", 0));
    }
    return EVT_RETURN_DONE;
}
