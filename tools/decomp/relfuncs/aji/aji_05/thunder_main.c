// include: mario/mario.h
// include: pmario_sound.h
// include: eff/n64/eff_akari_charge_n64.h
// proto: USER_FUNC(thunder_main);
USER_FUNC(thunder_main) {
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    if (event->userdata[0] == 0) {
        if (mario->currMotionId == 0x20) {
            EffectEntry* eff;

            event->userdata[0] = 1;
            psndSFXOn_3D("SFX_STG7_ELECTRIC_SHOCK1", &mario->position);
            eff = effAkariChargeN64Entry(0, 100, mario->position.x, 30.0f + mario->position.y, mario->position.z, 1.0f);
            ((s32*)eff->userdata)[6] = 30;
            ((s32*)eff->userdata)[7] = 231;
            ((s32*)eff->userdata)[8] = 219;
            ((s32*)eff->userdata)[10] = 0;
            ((s32*)eff->userdata)[11] = 0;
            ((s32*)eff->userdata)[12] = 0;
        }
    } else if (mario->currMotionId != 0x20) {
        event->userdata[0] = 0;
    }
    return EVT_RETURN_BLOCK;
}
