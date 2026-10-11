// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_audience.h
// include: system.h
// decl: typedef struct CortezWork { s16 state; s16 count; s16 audienceId[100]; s16 wait[100]; s16 timer[100]; s16 seq[100]; void* eff[100]; Vec srcPos[100]; Vec dstPos[100]; } CortezWork;
// decl: u8 psndSFX_get_vol(s32 id);
// proto: USER_FUNC(unk_muj_0000652c);
USER_FUNC(unk_muj_0000652c) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 out = args[1];

    evtSetValue(event, out, psndSFX_get_vol(id));
    return EVT_RETURN_DONE;
}
