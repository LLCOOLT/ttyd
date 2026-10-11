// decl: s32 yuugijou_montemedal_keep(EventEntry* event, BOOL isFirstCall);
// proto: void goryuugijo_init_montemedal(EventEntry* event, BOOL isFirstCall);
void goryuugijo_init_montemedal(EventEntry* event, BOOL isFirstCall) {
    if (!evtGetValue(event, GSWF(1229))) {
        yuugijou_montemedal_keep(event, isFirstCall);
    }
}
