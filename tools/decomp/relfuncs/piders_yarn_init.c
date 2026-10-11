// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: memory.h
// decl: typedef struct PidersYarn { f32 x0; f32 y0; f32 z0; f32 x1; f32 y1; f32 z1; u8 alpha; } PidersYarn;
// proto: USER_FUNC(piders_yarn_init);
USER_FUNC(piders_yarn_init) {
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    *(PidersYarn**)&unit->countersetWeapon = __memAlloc(HEAP_BATTLE, sizeof(PidersYarn));
    return EVT_RETURN_DONE;
}
