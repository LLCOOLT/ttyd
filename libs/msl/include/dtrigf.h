#ifndef _DTRIGF_H_
#define _DTRIGF_H_

/* Constants of MSL's paired-single sine/cosine helpers (dtrigf.h). In the original, the helpers are inline
 * assembly whose const locals get storage in every unit built with the MSL precompiled header, even though no
 * game code calls them: one set of constants for each of the two helpers, each constant stored twice (its
 * initial value, then the named object). The names are the original's (map files of the Japanese July 2004 demo). The main.dol link keeps
 * the 8-byte constants with their initial values and strips the floats; the REL links keep only the named objects. */

// FAKE: this repository has no assembly, so the helpers are not reproduced. Instead their constants are written
// here as plain static data with the same values, alignment and order (see docs/FAKES.md):
// - main.dol units (msl_main.pch defines DTRIGF_WITH_INITIAL_VALUES): what that link keeps, the two 8-byte
//   constants of each helper with their initial values.
// - REL units: the named constants only, as static locals of empty inline functions (below).

#ifdef DTRIGF_WITH_INITIAL_VALUES

/* main.dol: the float constants are small data, which that link strips as unreferenced; the two 8-byte paired
 * constants stay in .data with their initial values. */
typedef struct DtrigfPairedConstants {
    long long negone_one_init; // 0x00
    long long negone_one;      // 0x08
    long long one_negone_init; // 0x10
    long long one_negone;      // 0x18
} DtrigfPairedConstants;

/* One array for both helpers: at 0x40 bytes it is above the main.dol small-data limit (-sdata 48), so it stays
 * in .data like the original constants. */
static DtrigfPairedConstants sincosf_constants[2] = {
    {(long long)0xBF8000003F800000, (long long)0xBF8000003F800000, 0x3F800000BF800000, 0x3F800000BF800000},
    {(long long)0xBF8000003F800000, (long long)0xBF8000003F800000, 0x3F800000BF800000, 0x3F800000BF800000},
};

#else

/* REL: each helper's constants are static locals of an (uncalled, empty) inline function, so they carry the
 * original's names: the compiler names function-scope statics name$N, the form the original's objects have
 * (negone_one$42 ...), and objdiff pairs them with the original's by that name. The $N numbers are the
 * compiler's counter, not reproducible exactly: statics are numbered in declaration order but emitted in reverse
 * order of declaration, while the original's were numbered in declaration order and emitted in reverse order of
 * first use. So each set is declared last constant first, for the original's storage order. */
static inline void sincosf_f(void) {
    static float one = 1.0f;
    static float __local_PIO2 = 1.57079632679489661923f;
    static long long one_negone = 0x3F800000BF800000;
    static float __local_3PIO2 = 3.0f * 1.57079632679489661923f;
    static float __local_PI = 3.14159265358979323846f;
    static float neg_one = -1.0f;
    static long long negone_one = (long long)0xBF8000003F800000;
}

static inline void sincosf_a(void) {
    static float one = 1.0f;
    static float __local_PIO2 = 1.57079632679489661923f;
    static long long one_negone = 0x3F800000BF800000;
    static float __local_3PIO2 = 3.0f * 1.57079632679489661923f;
    static float __local_PI = 3.14159265358979323846f;
    static float neg_one = -1.0f;
    static long long negone_one = (long long)0xBF8000003F800000;
}

#endif

#endif
