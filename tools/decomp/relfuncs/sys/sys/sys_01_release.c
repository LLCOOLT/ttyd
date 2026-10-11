// proto: void sys_01_release(void);
void sys_01_release(void) {
    if (g_wp->file != NULL) {
        fileFree(g_wp->file);
    }
    g_wp = NULL;
}
