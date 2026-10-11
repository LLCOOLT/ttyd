// include: battle/battle.h
// include: battle/battle_unit.h
// include: memory.h
// include: system.h
// decl: typedef struct BattenSpline { s32 n; s32* table; f32 a[5]; f32 b[15]; s32 count; } BattenSpline;
// decl: void spline_maketable(s32 n, s32* table, f32* a, f32* b);
// decl: void spline_getvalue(f32 t, Vec* out, s32 n, s32* table, f32* a, f32* b);
// proto: u8 battenSatelliteTo_Main(BattleUnit* unit, s32 n);
u8 battenSatelliteTo_Main(BattleUnit* unit, s32 n) {
    BattenSpline* sp;
    BattleUnit* sat;
    Vec upos;
    Vec pos;

    if (unit->work[9 + n] == -1) {
        return FALSE;
    }
    sp = (BattenSpline*)unit->work[13 + n];
    if (sp == NULL) {
        return FALSE;
    }
    if (sp->count >= 60) {
        if (sp != NULL) {
            __memFree(HEAP_BATTLE, sp);
            unit->work[13 + n] = 0;
        }
        return FALSE;
    }
    spline_getvalue(intplGetValue(4, sp->count, 60, 0.0f, 1.0f), &pos, sp->n, sp->table, sp->a, sp->b);
    sat = BattleGetUnitPtr(_battleWorkPointer, unit->work[9 + n]);
    if (sat == NULL) {
        return FALSE;
    }
    BtlUnit_GetPos(unit, &upos.x, &upos.y, &upos.z);
    BtlUnit_SetPos(sat, upos.x + pos.x * unit->faceDirection, 5.0f + (upos.y + pos.y), upos.z + pos.z);
    BtlUnit_SetHomePos(sat, upos.x + pos.x * unit->faceDirection, 5.0f + (upos.y + pos.y), upos.z + pos.z);
    sp->count++;
    return TRUE;
}
