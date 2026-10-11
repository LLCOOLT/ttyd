// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// proto: USER_FUNC(peach_set_scale);
USER_FUNC(peach_set_scale) {
    f32 scale = evtGetFloat(event, event->args[0]);
    MarioWork* mario = marioGetPtr();

    mario->scale.x = scale;
    mario->scale.y = scale;
    mario->scale.z = scale;
    mario->wPlayerCollisionBox.x = 20.0f * scale;
    mario->wPlayerCollisionBox.y = 47.0f * scale;
    return EVT_RETURN_DONE;
}
