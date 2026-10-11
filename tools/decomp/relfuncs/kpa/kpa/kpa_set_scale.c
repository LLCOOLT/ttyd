// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// decl: f32 kpaGetWidth(s32 type);
// proto: USER_FUNC(kpa_set_scale);
USER_FUNC(kpa_set_scale) {
    f32 scale = evtGetFloat(event, event->args[0]);
    MarioWork* mario = marioGetPtr();

    mario->scale = (Vec){scale, scale, scale};
    mario->wPlayerCollisionBox.x = scale * kpaGetWidth(1);
    mario->wPlayerCollisionBox.y = 75.0f * scale;
    return EVT_RETURN_DONE;
}
