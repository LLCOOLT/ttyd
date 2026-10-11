// include: mario/mario.h
// include: driver/hitdrv.h
// include: system.h
// decl: void partyKeyOn(void);
// decl: void partyKeyOff(void);
// decl: void statusWinForceOpen(void);
// decl: void statusWinForceOff(void);
// proto: USER_FUNC(evt_iwamove_main);
USER_FUNC(evt_iwamove_main) {
    IwaMoveWork* wk = (IwaMoveWork*)event->lwData[0];
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
        return EVT_RETURN_BLOCK;
    }
    switch (wk->state) {
        case 0:
            if (mario->hitobjPush == hitNameToPtr("A_h_iwa")) {
                wk->timer = 80;
                wk->state++;
                marioKeyOff();
                partyKeyOff();
                marioChgPose("M_O_1");
                mario->dispFlags |= 2;
                statusWinForceOpen();
            }
            break;
        case 1:
            if (keyGetStickX(0) > 10) {
                if (wk->timer-- == 0) {
                    wk->state++;
                }
            } else {
                wk->state--;
                mario->dispFlags &= ~2;
                marioChgPose("M_S_1");
                marioKeyOn();
                partyKeyOn();
                statusWinForceOff();
            }
            break;
        case 2:
            if (wk->script != NULL) {
                evtEntry(wk->script, 0, 0);
            }
            statusWinForceOff();
            wk->state++;
            break;
        case 3:
            break;
    }
    return EVT_RETURN_BLOCK;
}
