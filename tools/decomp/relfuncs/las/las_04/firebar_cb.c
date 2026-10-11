// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// decl: typedef struct FirebarBall { s32 pose; Vec pos; } FirebarBall;
// decl: typedef struct FirebarSetup { u8 type; u8 count; u8 field_0x2[2]; Vec pos; f32 spacing; f32 field_0x14; f32 speed; void* callback; f32 field_0x20; f32 radius; } FirebarSetup;
// decl: typedef struct FirebarWork { u8 type; u8 count; u16 flags; Vec pos; f32 prevAngle; f32 angle; f32 speed; f32 spacing; f32 field_0x20; f32 scale; f32 field_0x28; f32 radius; void (*callback)(struct FirebarWork* wp, s32 type); s32 hitCount; s32 sfxId; s32 state; f32 shadowAngle; FirebarBall* balls; FirebarSetup* setup; } FirebarWork;
// decl: extern s32 firebar_coin[];
// decl: void set_damage_root_ypos(f32 y);
// decl: void marioChgMot(s32 motion);
// proto: void firebar_cb(FirebarWork* wp, s32 type);
void firebar_cb(FirebarWork* wp, s32 type) {
    MarioWork* mario = marioGetPtr();
    EventEntry* evt;

    switch (type) {
        case 1:
            if (wp->hitCount >= 10 && wp->type == 0) {
                wp->flags |= 8;
                evt = evtEntry(firebar_coin, 0, 0);
                evt->lwData[0] = wp->pos.x;
                evt->lwData[1] = wp->pos.y;
                evt->lwData[2] = wp->pos.z;
            }
            break;
        case 2:
            set_damage_root_ypos(mario->position.y);
            marioChgMot(0x20);
            break;
    }
}
