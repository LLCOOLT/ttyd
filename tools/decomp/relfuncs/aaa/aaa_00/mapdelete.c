// include: manager/filemgr.h
// decl: typedef struct AaaWork { FileEntry* tpl; s32 alpha; } AaaWork;
// decl: static AaaWork* wp;
// proto: void mapdelete(void);
void mapdelete(void) {
    if (wp != NULL && wp->tpl != NULL) {
        fileFree(wp->tpl);
    }
}
