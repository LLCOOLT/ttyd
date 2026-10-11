// proto: USER_FUNC(keijiban_joho_check);
USER_FUNC(keijiban_joho_check) {
    evtSetValue(event, event->args[0], KJDT->count);
    return EVT_RETURN_DONE;
}
