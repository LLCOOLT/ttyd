// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// include: party.h
// include: driver/npcdrv.h
// decl: NpcEntry* evtNpcNameToPtr(EventEntry* event, const char* name);
// decl: typedef struct OrbitData { f32 angle; f32 dist; } OrbitData;
// decl: OrbitData* _op;
// decl: double sin(double x);
// decl: double cos(double x);
// decl: #define ORBIT(i, pos) { f32 rad; f32 r; f32 x; f32 z; op[i].angle += d; rad = 3.141592f * op[i].angle / 180.0f; r = op[i].dist; x = r * (f32)sin(rad) + cx; z = r * (f32)cos(rad) + cz; (pos).x = x; (pos).z = z; }
// proto: USER_FUNC(mario_main_func);
USER_FUNC(mario_main_func) {
    s32* args = event->args;
    f32 a = evtGetValue(event, args[0]);
    f32 b = evtGetValue(event, args[1]);
    f32 cx = evtGetValue(event, args[2]);
    f32 cz = evtGetValue(event, args[3]);
    OrbitData* op = _op;
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    NpcEntry* npc1 = evtNpcNameToPtr(event, "\203}\203\213\203R");
    NpcEntry* npc2 = evtNpcNameToPtr(event, "\203R\203\213\203e\203X");
    NpcEntry* npc3 = evtNpcNameToPtr(event, "\203\202\203j\201[");
    NpcEntry* npc4 = evtNpcNameToPtr(event, "\203K\203\211\202\314\210\253\202\242\220\205\225v");
    NpcEntry* npc5 = evtNpcNameToPtr(event, "\203s\201[\203g\203\223");
    NpcEntry* npc6 = evtNpcNameToPtr(event, "\203I\203h\203I\203h\220\205\225v");
    f32 d = b - a;

    ORBIT(0, mario->position);
    ORBIT(1, party->position);
    ORBIT(2, npc1->position);
    ORBIT(3, npc2->position);
    ORBIT(4, npc3->position);
    ORBIT(5, npc4->position);
    ORBIT(6, npc5->position);
    ORBIT(7, npc6->position);
    npc1->prevPosition = npc1->position;
    npc2->prevPosition = npc2->position;
    npc3->prevPosition = npc3->position;
    npc4->prevPosition = npc4->position;
    npc5->prevPosition = npc5->position;
    npc6->prevPosition = npc6->position;
    return EVT_RETURN_DONE;
}
