// include: manager/evtmgr_cmd.h
// include: manager/filemgr.h
// decl: typedef struct TegamiWork { s32 alpha; FileEntry* tpl; } TegamiWork;
// decl: static TegamiWork* wp;
// proto: void tegami_delete(void);
void tegami_delete(void) {
    if (wp != NULL && wp->tpl != NULL) {
        fileFree(wp->tpl);
    }
}
