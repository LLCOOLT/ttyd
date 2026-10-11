// include: driver/effdrv.h
// include: dolphin/mtx.h
// include: system.h
// decl: int rand(void);
// decl: f32 maer;
// decl: Vec nowv;
// proto: USER_FUNC(evt_eff_firechange00);
USER_FUNC(evt_eff_firechange00) {
    Mtx m;
    Vec target;
    Vec pos;
    Vec dir;
    s32* args = event->args;
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, args[0]));
    s32 mode = evtGetValue(event, args[1]);
    BOOL reset;
    f32 a;
    f32 d;

    target.x = evtGetValue(event, args[2]);
    target.y = evtGetValue(event, args[3]);
    target.z = 0.0f;
    pos.x = ((f32*)eff->userdata)[14];
    pos.y = ((f32*)eff->userdata)[15];
    pos.z = 0.0f;
    if (isFirstCall) {
        event->field_84 = 0;
        if (mode == 0) {
            PSVECSubtract(&target, &pos, &nowv);
            PSVECNormalize(&nowv, &nowv);
            maer = rand() % 60 - 30;
            maer += (maer < 0.0f) ? -30 : 31;
            ((s32*)eff->userdata)[6] = 255;
            ((s32*)eff->userdata)[7] = 255;
            ((s32*)eff->userdata)[8] = 255;
            ((s32*)eff->userdata)[10] = 255;
            ((s32*)eff->userdata)[11] = 65;
            ((s32*)eff->userdata)[12] = 20;
        }
    }
    switch (event->field_84) {
        case 0:
            break;
        case 1:
            target.x = -2700.0f;
            break;
    }
    PSVECSubtract(&target, &pos, &dir);
    reset = FALSE;
    if (PSVECSquareMag(&dir) > 2500.0f) {
        maer += rand() % 41 - 20;
        if (maer > 80.0f || maer < -80.0f || (maer < 20.0f && maer > -20.0f)) {
            maer = rand() % 60 - 30;
            maer += (maer < 0.0f) ? -30 : 31;
            reset = TRUE;
        }
        PSMTXRotRad(m, 'Z', 0.017453292f * maer);
        PSMTXMultVec(m, &dir, &dir);
    } else {
        reset = TRUE;
    }
    PSVECNormalize(&dir, &dir);
    a = angleABf(0.0f, 0.0f, nowv.x, nowv.y);
    d = angleABf(0.0f, 0.0f, dir.x, dir.y);
    d = compAngle(a, d);
    if (!reset) {
        if ((d >= 0.0f ? d : -d) > 15.0f) {
            d = (d > 0.0f) ? 15.0f : -15.0f;
        }
    }
    PSMTXRotRad(m, 'Z', 0.017453292f * d);
    PSMTXMultVec(m, &nowv, &nowv);
    PSVECScale(&nowv, &dir, 15.0f);
    PSVECAdd(&pos, &dir, &pos);
    if (pos.y < 10.0f) {
        if (((f32*)eff->userdata)[15] >= 10.0f) {
            nowv.y = -nowv.y;
        } else if (nowv.y < 0.0f) {
            nowv.y = -nowv.y;
        }
    }
    ((f32*)eff->userdata)[14] = pos.x;
    ((f32*)eff->userdata)[15] = pos.y;
    switch (event->field_84) {
        case 0:
            if (PSVECSquareDistance(&pos, &target) < 225.0f) {
                if (mode) {
                    event->field_84 = 1;
                } else {
                    return 1;
                }
            }
            break;
        case 1:
            if (pos.x <= -270.0f) {
                effSoftDelete(eff);
                return 1;
            }
            break;
    }
    return 0;
}
