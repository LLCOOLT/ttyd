// include: manager/evtmgr_cmd.h
// include: data/item_data.h
// decl: extern ItemData itemDataTable[];
// decl: typedef struct CookRecipe { const char* a; const char* b; const char* out; } CookRecipe;
// include: string.h
// decl: s32 naniga_okorukana_cook(void);
// decl: s32 itemNameToID(const char* name);
// decl: extern s32 R_simple_recipe_table[];
// proto: USER_FUNC(cook_chk);
USER_FUNC(cook_chk) {
    s32* args = event->args;
    s32 item = evtGetValue(event, args[0]);
    ItemData* data = &itemDataTable[item];
    u32 i;

    if (item == 163) {
        item = naniga_okorukana_cook();
        evtSetValue(event, args[1], item);
        evtSetValue(event, args[2], item);
        return EVT_RETURN_DONE;
    }
    for (i = 0; i < 26; i++) {
        if (strcmp(data->id, (const char*)R_simple_recipe_table[i * 3]) == 0) {
            evtSetValue(event, (volatile u32)args[1], itemNameToID((const char*)R_simple_recipe_table[i * 3 + 1]));
            evtSetValue(event, (volatile u32)args[2], itemNameToID((const char*)R_simple_recipe_table[i * 3 + 2]));
            return EVT_RETURN_DONE;
        }
    }
    evtSetValue(event, args[1], 0);
    evtSetValue(event, args[2], 0);
    return EVT_RETURN_DONE;
}
