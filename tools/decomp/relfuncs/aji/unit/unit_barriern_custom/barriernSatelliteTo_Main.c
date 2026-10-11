// include: battle/battle.h
// include: battle/battle_unit.h
// include: memory.h
// decl: f32 intplGetValue(f32 start, f32 end, s32 mode, s32 cur, s32 steps);
// decl: typedef struct BarriernSpline { s32 n; s32* table; f32 a[5]; f32 b[15]; s32 count; } BarriernSpline;
// decl: void spline_maketable(s32 n, s32* table, f32* a, f32* b);
// decl: void spline_getvalue(f32 t, Vec* out, s32 n, s32* table, f32* a, f32* b);
// proto: static u8 barriernSatelliteTo_Main(BattleUnit* unit, s32 n);
static u8 barriernSatelliteTo_Main(BattleUnit* unit, s32 n) {
    BarriernSpline* sp;
    BattleUnit* sat;
    Vec upos;
    Vec pos;

    if (unit->work[4 + n] == -1) {
        return FALSE;
    }
    sp = (BarriernSpline*)unit->work[10 + n];
    if (sp == NULL) {
        return FALSE;
    }
    if (sp->count >= 60) {
        if (sp != NULL) {
            __memFree(HEAP_BATTLE, sp);
            unit->work[10 + n] = 0;
        }
        return FALSE;
    }
    spline_getvalue(intplGetValue(0.0f, 1.0f, 4, sp->count, 60), &pos, sp->n, sp->table, sp->a, sp->b);
    sat = BattleGetUnitPtr(_battleWorkPointer, unit->work[4 + n]);
    if (sat == NULL) {
        return FALSE;
    }
    BtlUnit_GetPos(unit, &upos.x, &upos.y, &upos.z);
    BtlUnit_SetPos(sat, upos.x + pos.x * unit->faceDirection, upos.y + pos.y, upos.z + pos.z);
    BtlUnit_SetHomePos(sat, upos.x + pos.x * unit->faceDirection, upos.y + pos.y, upos.z + pos.z);
    sp->count++;
    return TRUE;
}
