// include: driver/npcdrv.h
// include: driver/effdrv.h
// include: system.h
// decl: static inline f32 hoshi_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
// decl: static inline f32 hoshi_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
// proto: USER_FUNC(hoshi_jump);
#pragma opt_propagation off
#pragma opt_lifetimes off
USER_FUNC(hoshi_jump) {
    f32* pos = (f32*)((EffectEntry*)event->lwData[10])->userdata + 2;
    NpcEntry* npc = npcNameToPtr("\203}\203W\203\207\203\212\203\223");
    f32 vy;
    f32 speed;
    f32 t;
    f32 x = npc->position.x;
    f32 y = 50.0f + npc->position.y;
    f32 z = npc->position.z;
    f32 angle;
    f32 g;
    f32 dy;

    speed = 0.5f;
    if (isFirstCall) {
        t = distABf(x, z, pos[0], pos[2]) / speed;
        dy = y - pos[1];
        g = 0.1f * t;
        vy = dy / t + g / 2.0f;
        event->userdata[0] = *(s32*)&t;
        event->userdata[1] = *(s32*)&vy;
        event->userdata[2] = *(s32*)&speed;
        event->field_84 = 0;
    }
    t = event->userdataf[0];
    vy = event->userdataf[1];
    speed = event->userdataf[2];
    angle = 6.2831855f * angleABf(pos[0], pos[2], x, z) / 360.0f;
    pos[0] = speed * hoshi_sin(angle) + pos[0];
    pos[2] = pos[2] - speed * hoshi_cos(angle);
    pos[1] += vy;
    vy -= 0.1f;
    t -= 1.0f;
    if (t < 0.0f) {
        pos[0] = x;
        pos[1] = y;
        pos[2] = z;
        return EVT_RETURN_DONE;
    }
    event->userdata[0] = *(s32*)&t;
    event->userdata[1] = *(s32*)&vy;
    return EVT_RETURN_BLOCK;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
