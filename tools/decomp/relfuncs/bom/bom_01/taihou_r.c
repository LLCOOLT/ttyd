// include: system.h
// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// include: eff/n64/eff_ripple_n64.h
// decl: double sin(double x);
// decl: double cos(double x);
// decl: void effKemuTestSetRxRz(EffectEntry* effect, f32 rx, f32 rz);
// proto: USER_FUNC(taihou_r);
USER_FUNC(taihou_r) {
    f32 c = cos(0.7853981852531433);
    f32 s = sin(0.7853981852531433);
    f32 x;
    f32 y;
    f32 rx;
    f32 rz;

    x = 100.0f * c;
    y = 100.0f * s;
    rx = -angleABf(0.0f, 0.0f, 0.0f, y);
    rz = -angleABf(0.0f, 0.0f, x, y);

    effKemuTestSetRxRz(effNameToPtr("kemuri"), rx, rz);
    effRippleN64SetRxRz(effNameToPtr("ripple"), rx, rz);
    return EVT_RETURN_DONE;
}
