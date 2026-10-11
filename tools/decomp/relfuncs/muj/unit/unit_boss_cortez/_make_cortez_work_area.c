// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_audience.h
// include: system.h
// decl: typedef struct CortezWork { s16 state; s16 count; s16 audienceId[100]; s16 wait[100]; s16 timer[100]; s16 seq[100]; void* eff[100]; Vec srcPos[100]; Vec dstPos[100]; } CortezWork;
// decl: s32 entry_honeduka[12];
// proto: USER_FUNC(_make_cortez_work_area);
USER_FUNC(_make_cortez_work_area) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, *args++);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    unit->countersetWeapon = BattleAlloc(sizeof(CortezWork));
    return EVT_RETURN_DONE;
}
