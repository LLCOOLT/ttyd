// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/dispdrv.h
// include: driver/camdrv.h
// decl: static void piders_draw_yarn_sub(CameraId camera, void* param);
// proto: USER_FUNC(piders_draw_yarn);
USER_FUNC(piders_draw_yarn) {
    u8 alpha = evtGetValue(event, event->args[0]);
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    PidersYarn* yarn = *(PidersYarn**)&unit->countersetWeapon;

    // from the pider down to its hanging height, and up to the ceiling
    BtlUnit_GetHomePos(unit, &yarn->x1, &yarn->y1, &yarn->z1);
    yarn->y1 = unit->work[2];
    BtlUnit_GetHomePos(unit, &yarn->x0, &yarn->y0, &yarn->z0);
    yarn->y0 = 400.0f;
    yarn->alpha = alpha;
    dispEntry(CAMERA_3D, 0.0f, 2, piders_draw_yarn_sub, yarn);
    return EVT_RETURN_DONE;
}
