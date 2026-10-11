// include: battle/battle.h
// include: battle/battle_unit.h
// include: memory.h
// decl: typedef struct BattenSpline { s32 n; s32* table; f32 a[5]; f32 b[15]; s32 count; } BattenSpline;
// decl: void spline_maketable(s32 n, s32* table, f32* a, f32* b);
// decl: void spline_getvalue(f32 t, Vec* out, s32 n, s32* table, f32* a, f32* b);
// proto: u8 battenSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table);
u8 battenSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table) {
    BattenSpline* sp;

    sp = __memAlloc(HEAP_BATTLE, sizeof(BattenSpline));
    if (unit->work[9 + n] == -1) {
        return FALSE;
    }
    unit->work[13 + n] = (s32)sp;
    sp->n = 5;
    sp->table = table;
    sp->count = 0;
    spline_maketable(5, sp->table, sp->a, sp->b);
    BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[9 + n]), 1)->work[1] = (s32)table;
    return TRUE;
}
