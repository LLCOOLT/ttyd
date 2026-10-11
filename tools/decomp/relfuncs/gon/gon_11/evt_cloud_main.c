// include: mario/mario.h
// include: mario/mariost.h
// include: party.h
// include: party/party_cloud.h
// include: pmario_sound.h
// include: driver/animdrv.h
// include: driver/hitdrv.h
// include: driver/imgdrv.h
// include: driver/offscreendrv.h
// include: string.h
// decl: typedef struct CloudWork { s32 used; s32 state; char animName[0x20]; char imgName[0x20]; char offscreenName[0x20]; char groupNames[8][0x20]; char hitName[0x20]; s32 limit; s32 counter; EventEntry* evt; void* endEvt; s32 timer; s32 x; s32 y; s32 w; s32 h; f32 lastFrame; } CloudWork;
// decl: static CloudWork* cloud;
// decl: static u8 cloud_once_flag;
// decl: static void _mapsetofs_all(CloudWork* wp);
// decl: static void _mapclsofs_all(CloudWork* wp);
// decl: static BOOL _get_boundingbox(const char* name, s32* x, s32* y, s32* w, s32* h);
// decl: static void _img_alloc_capture(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7);
// proto: USER_FUNC(evt_cloud_main);
USER_FUNC(evt_cloud_main) {
    CloudWork* wp = (CloudWork*)event->lwData[0];
    s32 group = gp->inBattle != 0;
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    HitEntry* hit0;
    HitEntry* hit1;
    HitEntry* hit2;
    HitEntry* hit3;
    HitEntry* hit;
    ImageEntry* img;
    OffscreenEntry* os;

    if (isFirstCall) {
        return EVT_RETURN_BLOCK;
    }
    if (party == NULL) {
        return EVT_RETURN_BLOCK;
    }
    hit0 = (HitEntry*)cloudGetHitBreathout(0);
    hit1 = (HitEntry*)cloudGetHitBreathout(1);
    hit2 = (HitEntry*)cloudGetHitBreathout(2);
    hit3 = (HitEntry*)cloudGetHitBreathout(3);
    switch (wp->state) {
        case 0:
            if ((s32)cloud_once_flag == 1) {
                break;
            }
            hit = hitNameToPtr(wp->hitName);
            if (hit0 == hit || hit1 == hit || hit2 == hit || hit3 == hit) {
                wp->state++;
            }
            wp->counter = 0;
            break;
        case 1:
            if (mario->unk1AC > 90.0f && mario->unk1AC <= 270.0f) {
                strcpy(wp->animName, "P_oof_cloud_2");
            } else {
                strcpy(wp->animName, "P_oof_cloud_1");
            }
            if (!animGroupBaseAsync(wp->animName, group, NULL)) {
                break;
            }
            cloud_once_flag = 1;
            animPaperPoseEntry(wp->animName, group);
            offscreenEntry(wp->offscreenName);
            os = offscreenNameToPtr(wp->offscreenName);
            os->unk3C = 4;
            os->unk40 = 4;
            _mapsetofs_all(wp);
            wp->state++;
            break;
        case 2:
            imgEntry(wp->imgName, group);
            img = imgNameToPtr(wp->imgName, group);
            img->poseId = animPaperPoseGetId(wp->animName, group);
            *(OSTime*)&img->field_0x10C[4] = animTimeGetTime(group);
            imgClearVirtualPoint(img);
            imgSetShadow(img, 2);
            img->flags |= 2;
            wp->state = 222;
            break;
        case 222:
            if (!_get_boundingbox(wp->hitName, &wp->x, &wp->y, &wp->w, &wp->h)) {
                break;
            }
            _img_alloc_capture((s32)wp->imgName, 0, (s32)wp->offscreenName, 1, wp->x, wp->y, wp->w, wp->h);
            wp->state = 223;
            break;
        case 223:
            img = imgNameToPtr(wp->imgName, group);
            img->flags &= ~2;
            wp->state = 3;
        case 3:
            img = imgNameToPtr(wp->imgName, group);
            img->field_0x108 = (s32)"A_1";
            *(OSTime*)&img->field_0x10C[4] = animTimeGetTime(group);
            img->flags &= ~2;
            wp->timer = 30;
            wp->lastFrame = 0.0f;
            wp->state++;
            break;
        case 4:
            img = imgNameToPtr(wp->imgName, group);
            if (wp->lastFrame == 0.0f || wp->lastFrame + 1.0f < img->field_0x118) {
                psndSFXOn_3D("SFX_OFF_CLAUD_WIND2", &mario->position);
                wp->lastFrame = img->field_0x118;
            }
            if (mario->currMotionId != 27) {
                wp->state = 10;
                break;
            }
            hit = hitNameToPtr(wp->hitName);
            if (hit0 != hit && hit1 != hit && hit2 != hit && hit3 != hit) {
                if (wp->timer == 0) {
                    wp->state = 10;
                } else {
                    wp->timer--;
                    wp->counter += 2;
                }
            } else {
                wp->timer = 30;
                wp->counter += 2;
                if (wp->counter > wp->limit) {
                    wp->state = 20;
                }
            }
            break;
        case 10:
            wp->state = 99;
            break;
        case 20:
            psndSFXOn_3D("SFX_OFF_CLAUD_WIND3", &mario->position);
            if (wp->endEvt != NULL) {
                evtEntry(wp->endEvt, 0, 0);
            }
            img = imgNameToPtr(wp->imgName, group);
            img->field_0x108 = (s32)"A_2";
            *(OSTime*)&img->field_0x10C[4] = animTimeGetTime(group);
            wp->timer = 60;
            wp->state++;
            break;
        case 21:
            if (wp->timer != 0) {
                wp->timer--;
                break;
            }
            wp->timer = 30;
            wp->counter += 2;
            wp->state = 100;
            break;
        case 99:
        case 100:
            img = imgNameToPtr(wp->imgName, group);
            _mapclsofs_all(wp);
            animPaperPoseRelease(img->poseId);
            imgFreeCapture(img, 0);
            imgSetShadow(img, 0);
            imgRelease(img, group);
            offscreenDelete(wp->offscreenName);
            cloud_once_flag = 0;
            if (wp->state == 99) {
                wp->state = 0;
                break;
            }
            return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
