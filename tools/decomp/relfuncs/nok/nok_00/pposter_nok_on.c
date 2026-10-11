// decl: typedef struct PosterWork { u32 flags; s32 group; s32 shape; } PosterWork;
// decl: PosterWork* poster;
// proto: USER_FUNC(pposter_nok_on);
USER_FUNC(pposter_nok_on) {
    poster->flags |= 1;
    return EVT_RETURN_DONE;
}
