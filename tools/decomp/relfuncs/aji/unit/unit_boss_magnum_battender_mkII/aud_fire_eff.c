// include: eff/eff_kemu_test.h
// decl: void effKemuTestSetRxRz(EffectEntry* eff, f32 rx, f32 rz);
// proto: void aud_fire_eff(f32 x, f32 y, f32 z);
void aud_fire_eff(f32 x, f32 y, f32 z) {
    effKemuTestSetRxRz(effKemuTestEntry(11, x - 50.0f, 20.0f + y, 50.0f + z, 0.75f), 40.0f, 110.0f);
}
