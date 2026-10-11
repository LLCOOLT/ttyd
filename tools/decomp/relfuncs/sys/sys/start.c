// proto: USER_FUNC(start);
USER_FUNC(start) {
    SysWork* wp = g_wp;

    gp->flags |= 0x10;
    if (wp->state < 1) {
        return EVT_RETURN_BLOCK;
    }
    wp->state++;
    return EVT_RETURN_DONE;
}
