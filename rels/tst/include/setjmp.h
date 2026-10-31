#pragma once

/* MSL setjmp/longjmp (Runtime: __setjmp, longjmp), as tst.rel's GLU tessellator uses them. The buffer holds the
 * saved registers, floating-point ones included, so it is double-aligned (0x190 bytes). */

typedef double jmp_buf[50];

int __setjmp(jmp_buf env);
void longjmp(jmp_buf env, int val);

#define setjmp(env) __setjmp(env)
