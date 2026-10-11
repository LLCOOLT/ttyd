// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// include: party.h
// include: driver/npcdrv.h
// decl: NpcEntry* evtNpcNameToPtr(EventEntry* event, const char* name);
// decl: typedef struct OrbitData { f32 angle; f32 dist; } OrbitData;
// decl: OrbitData* _op;
// include: system.h
// proto: USER_FUNC(mario_main_setup_func);
USER_FUNC(mario_main_setup_func) {
    s32* args = event->args;
    f32 cx = evtGetValue(event, args[0]);
    f32 cz = evtGetValue(event, args[1]);
    OrbitData* op = _op;
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    NpcEntry* npc1 = evtNpcNameToPtr(event, "\203}\203\213\203R");
    NpcEntry* npc2 = evtNpcNameToPtr(event, "\203R\203\213\203e\203X");
    NpcEntry* npc3 = evtNpcNameToPtr(event, "\203\202\203j\201[");
    NpcEntry* npc4 = evtNpcNameToPtr(event, "\203K\203\211\202\314\210\253\202\242\220\205\225v");
    NpcEntry* npc5 = evtNpcNameToPtr(event, "\203s\201[\203g\203\223");
    NpcEntry* npc6 = evtNpcNameToPtr(event, "\203I\203h\203I\203h\220\205\225v");

    op[0].dist = distABf(cx, -cz, cx + mario->position.x, -(cz + mario->position.z));
    op[0].angle = angleABf(cx, -cz, cx + mario->position.x, -(cz + mario->position.z));
    op[1].dist = distABf(cx, -cz, cx + party->position.x, -(cz + party->position.z));
    op[1].angle = angleABf(cx, -cz, cx + party->position.x, -(cz + party->position.z));
    op[2].dist = distABf(cx, -cz, cx + npc1->position.x, -(cz + npc1->position.z));
    op[2].angle = angleABf(cx, -cz, cx + npc1->position.x, -(cz + npc1->position.z));
    op[3].dist = distABf(cx, -cz, cx + npc2->position.x, -(cz + npc2->position.z));
    op[3].angle = angleABf(cx, -cz, cx + npc2->position.x, -(cz + npc2->position.z));
    op[4].dist = distABf(cx, -cz, cx + npc3->position.x, -(cz + npc3->position.z));
    op[4].angle = angleABf(cx, -cz, cx + npc3->position.x, -(cz + npc3->position.z));
    op[5].dist = distABf(cx, -cz, cx + npc4->position.x, -(cz + npc4->position.z));
    op[5].angle = angleABf(cx, -cz, cx + npc4->position.x, -(cz + npc4->position.z));
    op[6].dist = distABf(cx, -cz, cx + npc5->position.x, -(cz + npc5->position.z));
    op[6].angle = angleABf(cx, -cz, cx + npc5->position.x, -(cz + npc5->position.z));
    op[7].dist = distABf(cx, -cz, cx + npc6->position.x, -(cz + npc6->position.z));
    op[7].angle = angleABf(cx, -cz, cx + npc6->position.x, -(cz + npc6->position.z));
    return EVT_RETURN_DONE;
}
