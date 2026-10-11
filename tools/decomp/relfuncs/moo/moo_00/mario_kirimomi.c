// include: mario/mario.h
// include: manager/evtmgr_cmd.h
// decl: double fmod(double x, double y);
// proto: USER_FUNC(mario_kirimomi);
USER_FUNC(mario_kirimomi) {
    f32 angle = evtGetFloat(event, event->args[0]);
    MarioWork* mario = marioGetPtr();

    mario->scale.x = mario->scale.y = mario->scale.z = 1.0f;
    mario->field_0xB4 = mario->wPlayerCollisionBox.y / 2 * mario->scale.y;
    mario->field_0xC4 = angle;
    mario->field_0xC4 = fmod(mario->field_0xC4, 360.0);
    return EVT_RETURN_DONE;
}
