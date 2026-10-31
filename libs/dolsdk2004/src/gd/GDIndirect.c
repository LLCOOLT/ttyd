#include <dolphin/gd.h>
#include <dolphin/os.h>

/**
 * Writes the BP indirect texture setup of one TEV stage:
 * indirect stage, format, bias, matrix, S and T wrap, add- previous and unsigned LOD flags and alpha selection.
 */
void GDSetTevIndirect(GXTevStageID tev_stage, GXIndTexStageID ind_stage,
                      GXIndTexFormat format, GXIndTexBiasSel bias_sel,
                      GXIndTexMtxID matrix_sel, GXIndTexWrap wrap_s,
                      GXIndTexWrap wrap_t, u8 add_prev, u8 utc_lod,
                      GXIndTexAlphaSel alpha_sel) {
    GDWriteBPCmd(BP_TEV_INDIRECT(
        ind_stage & 3,
        format & 3,
        bias_sel & 7,
        alpha_sel & 3,
        matrix_sel & 0xF,
        wrap_s & 7,
        wrap_t & 7,
        utc_lod & 1,
        add_prev & 1,
        0x10 + (tev_stage & 0xF)
    ));
}

/**
 * Writes one of the three indirect texture matrices as three BP registers.
 * Each element is converted to fixed point (scaled by 1024, 11 bits)
 * and the scale exponent plus 17 is split across the three registers.
 */
void GDSetIndTexMtx(GXIndTexMtxID mtx_id, const f32 offset[2][3], s8 scale_exp) {
    u32 id_offset;

    switch (mtx_id) {
    case GX_ITM_0:
        id_offset = 0;
        break;
    case GX_ITM_1:
        id_offset = 3;
        break;
    case GX_ITM_2:
        id_offset = 6;
        break;
    default:
        ASSERTMSGLINE(111, 0, "GDSetIndTexMtx: Invalid matrix id");
        break;
    }

    scale_exp += 17;

    GDWriteBPCmd(BP_IND_MTX(
        (s32)(offset[0][0] * 0x400) & 0x7FF,
        (s32)(offset[1][0] * 0x400) & 0x7FF,
        scale_exp & 3,
        6 + id_offset
    ));

    GDWriteBPCmd(BP_IND_MTX(
        (s32)(offset[0][1] * 0x400) & 0x7FF,
        (s32)(offset[1][1] * 0x400) & 0x7FF,
        (scale_exp >> 2) & 3,
        7 + id_offset
    ));

    GDWriteBPCmd(BP_IND_MTX(
        (s32)(offset[0][2] * 0x400) & 0x7FF,
        (s32)(offset[1][2] * 0x400) & 0x7FF,
        (scale_exp >> 4) & 3,
        8 + id_offset
    ));
}

/**
 * Writes the S and T scales for a pair of indirect stages (starting at an even stage) into BP register 0x25
 * or 0x26.
 */
void GDSetIndTexCoordScale(GXIndTexStageID indStageEven, GXIndTexScale scaleS0,
                           GXIndTexScale scaleT0, GXIndTexScale scaleS1,
                           GXIndTexScale scaleT1) {
    GDWriteBPCmd(BP_IND_TEXCOORD_SCALE(
        scaleS0 & 0xF,
        scaleT0 & 0xF,
        scaleS1 & 0xF,
        scaleT1 & 0xF,
        0x25 + ((indStageEven >> 1) & 1)
    ));
}

/** Writes the texture map and texture coordinate for each of the four indirect stages into BP register 0x27. */
void GDSetIndTexOrder(GXTexCoordID texCoord0, GXTexMapID texMap0,
                      GXTexCoordID texCoord1, GXTexMapID texMap1,
                      GXTexCoordID texCoord2, GXTexMapID texMap2,
                      GXTexCoordID texCoord3, GXTexMapID texMap3) {
    GDWriteBPCmd(BP_IND_TEX_ORDER(
        texMap0 & 7,
        texCoord0 & 7,
        texMap1 & 7,
        texCoord1 & 7,
        texMap2 & 7,
        texCoord2 & 7,
        texMap3 & 7,
        texCoord3 & 7,
        0x27
    ));
}

/** Switches a TEV stage back to direct texturing: no indirect matrix, bias or wrap. */
void GDSetTevDirect(GXTevStageID tev_stage) {
    GDSetTevIndirect(tev_stage, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_OFF, GX_ITW_OFF, 0, 0, GX_ITBA_OFF);
}

/**
 * Sets a TEV stage to warp its texture coordinates by an indirect texture,
 * using a matrix and optionally a signed offset; replace_mode replaces the coordinates instead of adding.
 */
void GDSetTevIndWarp(GXTevStageID tev_stage, GXIndTexStageID ind_stage, u8 signed_offset, u8 replace_mode, GXIndTexMtxID matrix_sel) {
    GXIndTexWrap wrap;
    wrap = replace_mode ? GX_ITW_0 : GX_ITW_OFF;

    GDSetTevIndirect(tev_stage,
                     ind_stage,
                     GX_ITF_8,
                     signed_offset ? GX_ITB_STU : GX_ITB_NONE,
                     matrix_sel,
                     wrap,
                     wrap,
                     0,
                     0,
                     GX_ITBA_OFF);
}

/**
 * Sets a TEV stage for tiled indirect lookups: picks the wrap from the tile size (16 to 256),
 * loads an indirect matrix scaled by the tile spacing and writes the stage's setup.
 */
void GDSetTevIndTile(GXTevStageID tev_stage, GXIndTexStageID ind_stage,
                     u16 tilesize_s, u16 tilesize_t, u16 tilespacing_s,
                     u16 tilespacing_t, GXIndTexFormat format,
                     GXIndTexMtxID matrix_sel, GXIndTexBiasSel bias_sel,
                     GXIndTexAlphaSel alpha_sel) {
    GXIndTexWrap wrap_s;
    GXIndTexWrap wrap_t;
    f32 mtx[2][3];

    switch (tilesize_s) {
    case 256:
        wrap_s = GX_ITW_256;
        break;  
    case 128:
        wrap_s = GX_ITW_128;
        break;  
    case 64:
        wrap_s = GX_ITW_64;
        break;  
    case 32:
        wrap_s = GX_ITW_32;
        break;  
    case 16:
        wrap_s = GX_ITW_16;
        break;  
    default:
        ASSERTMSGLINE(268, 0, "GDSetTevIndTile: Invalid tilesize for S coordinate");
        wrap_s = GX_ITW_OFF;
        break;
    }

    switch (tilesize_t) {
    case 256:
        wrap_t = GX_ITW_256;
        break;  
    case 128:
        wrap_t = GX_ITW_128;
        break;  
    case 64:
        wrap_t = GX_ITW_64;
        break;  
    case 32:
        wrap_t = GX_ITW_32;
        break;  
    case 16:
        wrap_t = GX_ITW_16;
        break;  
    default:
        ASSERTMSGLINE(280, 0, "GDSetTevIndTile: Invalid tilesize for T coordinate");
        wrap_t = GX_ITW_OFF;
        break;
    }

    mtx[0][0] = (f32)tilespacing_s / 0x400;
    mtx[0][1] = mtx[0][2] = 0.0f;

    mtx[1][1] = (f32)tilespacing_t / 0x400;
    mtx[1][0] = mtx[1][2] = 0.0f;
    GDSetIndTexMtx(matrix_sel, mtx, 10); 
    
    GDSetTevIndirect(tev_stage,
                     ind_stage,
                     format,
                     bias_sel,
                     matrix_sel,
                     wrap_s,
                     wrap_t,
                     0,
                     1,
                     alpha_sel);
}

/**
 * Sets up bump mapping in S/T space, which takes three TEV stages from tev_stage:
 * one applying the S matrix, one the T matrix (adding the previous stage)
 * and one repeating the result with no matrix.
 */
void GDSetTevIndBumpST(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexMtxID matrix_sel) {
    GXIndTexMtxID sm;
    GXIndTexMtxID tm;

    switch(matrix_sel) {
    case GX_ITM_0:
        sm = GX_ITM_S0;
        tm = GX_ITM_T0;
        break;
    case GX_ITM_1:
        sm = GX_ITM_S1;
        tm = GX_ITM_T1;
        break;
    case GX_ITM_2:
        sm = GX_ITM_S2;
        tm = GX_ITM_T2;
        break;
    default:
        ASSERTMSGLINE(332, 0, "GDSetTevIndBumpST: Invalid matrix selection");
        break;
    }

    GDSetTevIndirect(tev_stage,
                     ind_stage,
                     GX_ITF_8,
                     GX_ITB_ST,
                     sm,
                     GX_ITW_0,
                     GX_ITW_0,
                     0,
                     0,
                     GX_ITBA_OFF);

    GDSetTevIndirect(tev_stage + 1,
                     ind_stage,
                     GX_ITF_8,
                     GX_ITB_ST,
                     tm,
                     GX_ITW_0,
                     GX_ITW_0,
                     1,
                     0,
                     GX_ITBA_OFF);

    GDSetTevIndirect(tev_stage + 2,
                     ind_stage,
                     GX_ITF_8,
                     GX_ITB_NONE,
                     GX_ITM_OFF,
                     GX_ITW_OFF,
                     GX_ITW_OFF,
                     1,
                     0,
                     GX_ITBA_OFF);
}

/** Sets a TEV stage for bump mapping where the indirect texture gives an XYZ offset through the chosen matrix. */
void GDSetTevIndBumpXYZ(GXTevStageID tev_stage, GXIndTexStageID ind_stage, GXIndTexMtxID matrix_sel) {
    GDSetTevIndirect(tev_stage,
                     ind_stage,
                     GX_ITF_8,
                     GX_ITB_STU,
                     matrix_sel,
                     GX_ITW_OFF,
                     GX_ITW_OFF,
                     0,
                     0,
                     GX_ITBA_OFF);
}

/** Sets a TEV stage to use the previous stage's coordinates (wrap 0, add previous) with no indirect lookup. */
void GDSetTevIndRepeat(GXTevStageID tev_stage) {
    GDSetTevIndirect(tev_stage,
                     GX_INDTEXSTAGE0,
                     GX_ITF_8,
                     GX_ITB_NONE,
                     GX_ITM_OFF,
                     GX_ITW_0,
                     GX_ITW_0,
                     1,
                     0,
                     GX_ITBA_OFF);
}

/** Writes the BP mask of enabled indirect stages (low 8 bits). */
void __GDSetIndTexMask(u32 mask) {
    GDWriteBPCmd(BP_IND_MASK(mask & 0xFF, 0xF));
}
