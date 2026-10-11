// include: manager/evtmgr_cmd.h
// decl: EffectEntry* effKemuriEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// proto: USER_FUNC(maffia_kemuri);
USER_FUNC(maffia_kemuri) {
    s32* args = event->args;
    f32 x = evtGetValue(event, args[0]);
    f32 y = evtGetValue(event, args[1]);
    f32 z = evtGetValue(event, args[2]);

    effKemuriEntry(1, x, y, z, 0.0f);
    return EVT_RETURN_DONE;
}
