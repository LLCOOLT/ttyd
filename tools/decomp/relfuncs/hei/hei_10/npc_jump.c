// include: driver/npcdrv.h
// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// include: system.h
// decl: static inline f32 chb_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
// decl: static inline f32 chb_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
// decl: static inline s32 npc_jump_get_time(EventEntry* event, s32* args) { return evtGetValue(event, args[6]); }
// proto: static USER_FUNC(npc_jump);
#pragma opt_propagation off
#pragma opt_lifetimes off
static USER_FUNC(npc_jump) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    f32 speed = evtGetFloat(event, args[4]);
    f32 gravity = evtGetFloat(event, args[5]);
    f32 t = 60.0f * (f32)npc_jump_get_time(event, args) / 1000.0f;
    NpcEntry* npc = npcNameToPtr(name);
    f32 vy;
    f32 dist;
    f32 dy;
    f32 angle;

    if (isFirstCall) {
        dist = PSVECDistance(&(Vec){x, 0.0f, z}, &(Vec){npc->position.x, 0.0f, npc->position.z});
        dy = y - npc->position.y;
        if (t == 0.0f) {
            t = dist / speed;
        } else {
            speed = dist / t;
        }
        vy = dy / t + gravity * t * 0.5f;
        event->userdata[0] = *(s32*)&t;
        event->userdata[1] = *(s32*)&vy;
        event->userdata[2] = *(s32*)&speed;
    }
    t = event->userdataf[0];
    vy = event->userdataf[1];
    speed = event->userdataf[2];
    angle = 6.2831855f * angleABf(npc->position.x, npc->position.z, x, z) / 360.0f;
    npc->position.x = speed * chb_sin(angle) + npc->position.x;
    npc->position.z = npc->position.z - speed * chb_cos(angle);
    npc->position.y += vy;
    vy -= gravity;
    t -= 1.0f;
    if (t < 0.0f) {
        npc->position = (Vec){x, y, z};
        return 1;
    }
    event->userdata[0] = *(s32*)&t;
    event->userdata[1] = *(s32*)&vy;
    return 0;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
