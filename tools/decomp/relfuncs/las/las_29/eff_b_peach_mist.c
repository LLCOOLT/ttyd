// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// include: driver/camdrv.h
// decl: double sin(double);
// decl: double cos(double);
// decl: void* effMistEntry(s32 type, s32 lifetime, f32 x, f32 y, f32 z, f32 angle);
// proto: USER_FUNC(eff_b_peach_mist);
USER_FUNC(eff_b_peach_mist) {
    NpcEntry* npc = npcNameToPtr("\203s\201[\203`\225P");
    f32 s;
    f32 angle;
    f32 c;
    f32 dx;
    f32 dz;

    s = 180.0f + camGetPtr(CAMERA_3D)->viewYaw;
    angle = 6.2831855f * s / 360.0f;
    s = sin(angle);
    c = cos(angle);
    dx = 20.0f * s;
    dz = 20.0f * -c;

    effMistEntry(6, 300, npc->position.x + dx, 30.0f + npc->position.y, npc->position.z + dz, 0.0f);
    return EVT_RETURN_DONE;
}
