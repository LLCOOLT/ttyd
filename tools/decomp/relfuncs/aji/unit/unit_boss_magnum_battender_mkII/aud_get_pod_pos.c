// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// proto: void aud_get_pod_pos(BattleUnit* unit, f32* x, f32* y, f32* z);
void aud_get_pod_pos(BattleUnit* unit, f32* x, f32* y, f32* z) {
    BtlUnit_GetPos(unit, x, y, z);
    *x += 10.0f;
    *y += 78.0f;
}
