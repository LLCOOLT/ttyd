// decl: EffectEntry* effStardustN64Entry(s32 type, f32 x, f32 y, f32 z, f32 size);
// decl: void effStardustN64SetDrawCam(EffectEntry* eff, s32 camera);
// decl: void display_func(CameraId cameraId, void* param);
// proto: USER_FUNC(display);
USER_FUNC(display) {
    SysWork* wp;
    SysChar* chr;
    s32 type = evtGetValue(event, event->args[0]);
    s32 i;

    if (isFirstCall) {
        wp = _mapAlloc(sizeof(SysWork));
        event->userdatap[0] = wp;
        memset(wp, 0, sizeof(SysWork));
        wp->type = type;
        wp->angle = 0.0f;
        wp->count = 0;
        while (lang_tbl[gp->language][type][wp->count] != -1) {
            wp->count++;
        }
        for (i = 0; i < wp->count; i++) {
            wp->chars[i].x = 36.0f * i - (f32)((wp->count - 1) * 36) / 2;
            wp->chars[i].y = 40.0f;
            wp->chars[i].z = 0.0f;
            wp->chars[i].rot = 90.0f;
            wp->chars[i].timer = i * 20 + 1;
            wp->chars[i].state = 0;
            wp->chars[i].texid = lang_tbl[gp->language][type][i];
        }
    }
    wp = event->userdatap[0];
    g_wp = wp;
    switch (wp->state) {
        case 0:
            if ((void*)fileAsyncf(4, NULL, "%s/e/%s/effect_sys.tpl", getMarioStDvdRoot(), lang_prefix[gp->language]) != NULL) {
                wp->file = fileAllocf(4, "%s/e/%s/effect_sys.tpl", getMarioStDvdRoot(), lang_prefix[gp->language]);
                wp->state++;
            }
            break;
        case 2:
            for (i = 0; i < wp->count; i++) {
                chr = &wp->chars[i];
                switch (chr->state) {
                    case 0:
                        chr->timer--;
                        if (chr->timer < 0) {
                            chr->timer = 0;
                            chr->state++;
                            effStardustN64SetDrawCam(effStardustN64Entry(4, chr->x, chr->y, chr->z, 40.0f), 5);
                        }
                        break;
                    case 1:
                        chr->rot = intplGetValue(5, chr->timer, 90, 90.0f, 1800.0f);
                        chr->timer++;
                        if (chr->timer > 90) {
                            chr->state++;
                        }
                        break;
                    case 2:
                        if (i == wp->count - 1) {
                            wp->angle += 0.8f;
                            if (wp->angle > 360.0f) {
                                wp->angle -= 360.0f;
                            }
                            wp->alpha += 0x30;
                            if (wp->alpha > 10000) {
                                wp->alpha = 10000;
                            }
                        }
                        break;
                }
            }
            break;
        case 3:
            break;
    }
    if (wp->state != 0) {
        dispEntry(CAMERA_3D_EFFECTA, 0.0f, 2, display_func, wp);
    }
    return EVT_RETURN_BLOCK;
}
