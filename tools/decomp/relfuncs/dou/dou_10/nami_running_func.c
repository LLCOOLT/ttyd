// include: mario/mariost.h
// include: manager/evtmgr_cmd.h
// decl: double sin(double x);
// proto: USER_FUNC(nami_running_func);
USER_FUNC(nami_running_func) {
    f32* lwf = (f32*)event->lwData;
    s32* args = event->args;
    f32 s;

    lwf[6] -= 1.3499999f;
    if (lwf[6] > 840.0f) {
        lwf[7] += 0.35f;
        if (lwf[7] > 0.0f) {
            lwf[7] = 0.0f;
        }
    }
    switch (event->lwData[14]) {
        case 0:
        case 1:
            if (lwf[6] < 200.0f) {
                lwf[7] -= 0.4f;
            }
            break;
        case 2:
        case 3:
            if (lwf[6] < -340.0f) {
                lwf[7] -= 0.4f;
            }
            break;
    }
    event->lwData[15] = 0;
    switch (event->lwData[14]) {
        case 0:
        case 1:
            if (lwf[6] < 0.0f) {
                event->lwData[15] = 1;
            }
            break;
        case 2:
        case 3:
            if (lwf[6] < -540.0f) {
                event->lwData[15] = 1;
            }
            break;
    }
    s = sin(6.2831855f * (2.0f * gp->retraceCount) / 360.0f);
    evtSetFloat(event, args[0], lwf[6]);
    evtSetFloat(event, args[1], lwf[7] + (5.0f * s - 5.0f));
    evtSetFloat(event, args[2], lwf[8]);
    return EVT_RETURN_DONE;
}
