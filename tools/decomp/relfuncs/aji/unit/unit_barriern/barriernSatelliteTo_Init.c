// include: battle/battle.h
// include: battle/battle_unit.h
// include: memory.h
// decl: typedef struct BarriernSpline { s32 n; s32* table; f32 a[5]; f32 b[15]; s32 count; } BarriernSpline;
// decl: void spline_maketable(s32 n, s32* table, f32* a, f32* b);
// decl: void spline_getvalue(f32 t, Vec* out, s32 n, s32* table, f32* a, f32* b);
// proto: static u8 barriernSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table);
static u8 barriernSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table) {
    BarriernSpline* sp;

    if (unit->work[4 + n] == -1) {
        return FALSE;
    }
    sp = __memAlloc(HEAP_BATTLE, sizeof(BarriernSpline));
    unit->work[10 + n] = (s32)sp;
    sp->n = 5;
    sp->table = table;
    sp->count = 0;
    spline_maketable(5, sp->table, sp->a, sp->b);
    BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[4 + n]), 1)->work[2] = (s32)table;
    return TRUE;
}
