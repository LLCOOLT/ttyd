// include: driver/effdrv.h
// decl: EffectEntry* effFireEntry(s32 type, f32 x, f32 y, f32 z, f32 scale, s32 lifetime);
// decl: void mapObjGetPos(const char* name, Vec* pos);
// decl: void _hikariEntry(const char* name, s32 type, f32 scale);
// proto: void _hikariEntry(const char* name, s32 type, f32 scale);
void _hikariEntry(const char* name, s32 type, f32 scale) {
    Vec pos;
    EffectEntry* eff;

    mapObjGetPos(name, &pos);
    eff = effFireEntry(type, pos.x, pos.y - 7.0f, pos.z, 1.0f, 1000);
    ((f32*)eff->userdata)[30] = scale;
    ((f32*)eff->userdata)[31] = scale;
    effSetName(eff, name);
}
