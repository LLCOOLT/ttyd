// include: manager/evtmgr_cmd.h
// include: data/item_data.h
// decl: extern ItemData itemDataTable[];
// decl: typedef struct CookRecipe { const char* a; const char* b; const char* out; } CookRecipe;
// include: string.h
// decl: s32 naniga_okorukana_cook(void);
// decl: s32 itemNameToID(const char* name);
// decl: extern s32 R_cookbook_recipe_table[];
// proto: USER_FUNC(cook_chk2);
USER_FUNC(cook_chk2) {
    s32* args = event->args;
    s32 item1 = evtGetValue(event, args[0]);
    s32 item2 = evtGetValue(event, args[1]);
    ItemData* data1 = &itemDataTable[item1];
    ItemData* data2 = &itemDataTable[item2];
    u32 i;

    if (item1 == 163 || item2 == 163) {
        item2 = naniga_okorukana_cook();
        evtSetValue(event, (volatile u32)args[2], item2);
        return EVT_RETURN_DONE;
    }
    for (i = 0; i < 289; i++) {
        if ((strcmp(data1->id, (const char*)R_cookbook_recipe_table[i * 3]) == 0 && strcmp(data2->id, (const char*)R_cookbook_recipe_table[i * 3 + 1]) == 0) ||
            (strcmp(data2->id, (const char*)R_cookbook_recipe_table[i * 3]) == 0 && strcmp(data1->id, (const char*)R_cookbook_recipe_table[i * 3 + 1]) == 0)) {
            evtSetValue(event, (volatile u32)args[2], itemNameToID((const char*)R_cookbook_recipe_table[i * 3 + 2]));
            return EVT_RETURN_DONE;
        }
    }
    evtSetValue(event, args[2], 0);
    return EVT_RETURN_DONE;
}
