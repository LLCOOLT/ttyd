// FAKE: whole unit as G5 asm stopgap (force_active + fixbase); C under #ifdef NONMATCHING.
#define EOF -1
#define SIGDIGLEN 36
#define MAX_SIG_DIG 20

typedef struct decimal {
    char sign;
    char unused;
    short exp;
    struct {
        unsigned char length;
        unsigned char text[SIGDIGLEN];
        unsigned char unused;
    } sig;
} decimal;

struct lconv_ {
    char* decimal_point;
    char pad[0x30];
};
extern struct lconv_ __lconv;

extern unsigned char __ctype_map[];
extern unsigned char __upper_map[];
extern float __float_huge[];
extern float __float_nan[];
extern double __double_huge[];
extern double __extended_min[];
extern double __extended_max[];
extern double __dec2num(const decimal*);

#define __control_char 0x01
#define __motion_char 0x02
#define __space_char 0x04
#define __punctuation 0x08
#define __digit 0x10
#define __hex_digit 0x20
#define __lower_case 0x40
#define __upper_case 0x80

#define __letter (__lower_case | __upper_case)
#define __whitespace (__motion_char | __space_char)

#define isalpha(c) ((int)(__ctype_map[(unsigned char)(c)] & __letter))
#define isdigit(c) ((int)(__ctype_map[(unsigned char)(c)] & __digit))
#define isspace(c) ((int)(__ctype_map[(unsigned char)(c)] & __whitespace))
#define isxdigit(c) ((int)(__ctype_map[(unsigned char)(c)] & __hex_digit))
#define toupper(c) ((c == EOF) ? EOF : ((int)__upper_map[(unsigned char)(c)]))

enum __ReadProcActions { __GetAChar, __UngetAChar, __TestForError };

enum scan_states {
    start = 0x0001,
    sig_start = 0x0002,
    leading_sig_zeroes = 0x0004,
    int_digit_loop = 0x0008,
    frac_start = 0x0010,
    frac_digit_loop = 0x0020,
    sig_end = 0x0040,
    exp_start = 0x0080,
    exp_sign = 0x0100,
    leading_exp_digit = 0x0200,
    exp_digit_loop = 0x0400,
    finished = 0x0800,
    failure = 0x1000,
    nan_state = 0x2000,
    inf_state = 0x4000,
    hex_state = 0x8000
};

enum hex_scan_states {
    not_hex = 0x00,
    hex_start = 0x01,
    leading_hex_zeroes = 0x02,
    int_hex_digit_loop = 0x04,
    frac_hex_start = 0x08,
    frac_hex_digit_loop = 0x10,
    p_exp_start = 0x20,
    p_exp_sign = 0x40,
    p_exp_digit_loop = 0x100
};

#define final_state(scan_state) (scan_state & (finished | failure))
#define success(scan_state) (scan_state & (leading_sig_zeroes | int_digit_loop | frac_digit_loop | leading_exp_digit | exp_digit_loop | finished))
#define fetch() (count++, (*ReadProc)(ReadProcArg, 0, __GetAChar))
#define unfetch(c) (*ReadProc)(ReadProcArg, c, __UngetAChar)

#ifdef NONMATCHING
long double __strtold(int max_width, int (*ReadProc)(void*, int, int), void* ReadProcArg, int* chars_scanned, int* overflow) {
    decimal d = {0, 0, 0, {0, ""}};
    char* ip;
    int scan_state = start;
    short hex_exp = 0;
    int hex_digits = 0;
    int nan_index;
    union {
        long double v;
        unsigned char b[8];
        short s;
        unsigned long long u;
    } r;
    int radix = *(unsigned char*)__lconv.decimal_point;
    int hex_exp_digits = 0;
    unsigned char* buf = r.b;
    int hex_dig_count;
    int c;
    int n_index;
    char* np;
    int sign = 0;
    int exp_negative = 0;
    int hex_scan_state = not_hex;
    int sign_detected = 0;
    int hex_exp_negative = 0;
    int count = 0;
    int spaces = 0;
    int exp_value;
    int dec_exp = 0;
    int inf_index;
    exp_value = 0;
    *overflow = 0;
    c = fetch();

    while (count <= max_width && c != EOF && !final_state(scan_state)) {
        switch (scan_state) {
        case start:
            if (isspace(c)) {
                c = (*ReadProc)(ReadProcArg, 0, __GetAChar);
                spaces++;
                break;
            }
            switch (toupper(c)) {
            case '-':
                sign = 1;
            case '+':
                c = fetch();
                sign_detected = 1;
                break;
            case 'I':
                c = fetch();
                scan_state = inf_state;
                break;
            case 'N':
                c = fetch();
                scan_state = nan_state;
                break;
            default:
                scan_state = sig_start;
                break;
            }
            break;
        case inf_state: {
            char inf_string[] = "INFINITY";
            ip = inf_string + 1;
            inf_index = 1;
            while (inf_index < 8 && *ip == toupper(c)) {
                ip++;
                inf_index++;
                c = fetch();
            }
            if (inf_index == 3 || inf_index == 8) {
                r.v = sign ? -__float_huge[0] : __float_huge[0];
                *chars_scanned = spaces + (inf_index + sign_detected);
                return r.v;
            }
            scan_state = failure;
            break;
        }
        case nan_state: {
            char nan_string[] = "NAN(";
            np = nan_string + 1;
            nan_index = 1;
            n_index = 0;
            while (nan_index < 4 && *np == toupper(c)) {
                np++;
                nan_index++;
                c = fetch();
            }
            if (nan_index == 3 || nan_index == 4) {
                if (nan_index == 4) {
                    while (n_index < 32 && (isdigit(c) || isalpha(c))) {
                        n_index++;
                        c = fetch();
                    }
                    if (c != ')') {
                        scan_state = failure;
                        break;
                    }
                    n_index++;
                }
                r.v = sign ? -__float_nan[0] : __float_nan[0];
                *chars_scanned = spaces + nan_index + n_index + sign_detected;
                return r.v;
            }
            scan_state = failure;
            break;
        }
        case sig_start:
            if (c == radix) {
                scan_state = frac_start;
                c = fetch();
                break;
            }
            if (!isdigit(c)) {
                scan_state = failure;
                break;
            }
            if (c == '0') {
                c = fetch();
                if (toupper(c) == 'X') {
                    hex_scan_state = hex_start;
                    scan_state = hex_state;
                } else {
                    scan_state = leading_sig_zeroes;
                }
            } else {
                scan_state = int_digit_loop;
            }
            break;
        case leading_sig_zeroes:
            if (c == '0') {
                c = fetch();
            } else {
                scan_state = int_digit_loop;
            }
            break;
        case int_digit_loop:
            if (!isdigit(c)) {
                if (c == radix) {
                    scan_state = frac_digit_loop;
                    c = fetch();
                } else {
                    scan_state = sig_end;
                }
                break;
            }
            if (d.sig.length < MAX_SIG_DIG) {
                d.sig.text[d.sig.length++] = c;
            } else {
                dec_exp++;
            }
            c = fetch();
            break;
        case frac_start:
            if (!isdigit(c)) {
                scan_state = failure;
            } else {
                scan_state = frac_digit_loop;
            }
            break;
        case frac_digit_loop:
            if (!isdigit(c)) {
                scan_state = sig_end;
                break;
            }
            if (d.sig.length < MAX_SIG_DIG) {
                if (c != '0' || d.sig.length != 0) {
                    d.sig.text[d.sig.length++] = c;
                }
                dec_exp--;
            }
            c = fetch();
            break;
        case sig_end:
            if (toupper(c) == 'E') {
                scan_state = exp_start;
                c = fetch();
            } else {
                scan_state = finished;
            }
            break;
        case exp_start:
            if (c == '+') {
                c = fetch();
            } else if (c == '-') {
                c = fetch();
                exp_negative = 1;
            }
            scan_state = exp_sign;
            break;
        case exp_sign:
            if (!isdigit(c)) {
                scan_state = failure;
                break;
            }
            if (c == '0') {
                scan_state = leading_exp_digit;
                c = fetch();
            } else {
                scan_state = exp_digit_loop;
            }
            break;
        case leading_exp_digit:
            if (c == '0') {
                c = fetch();
            } else {
                scan_state = exp_digit_loop;
            }
            break;
        case exp_digit_loop:
            if (!isdigit(c)) {
                scan_state = finished;
                break;
            }
            exp_value = exp_value * 10 + (c - '0');
            if (exp_value > 0x7fff) {
                *overflow = 1;
            }
            c = fetch();
            break;
        case hex_state:
            switch (hex_scan_state) {
            case hex_start:
                r.b[0] = 0; r.b[1] = 0; r.b[2] = 0; r.b[3] = 0; r.b[4] = 0; r.b[5] = 0; r.b[6] = 0; r.b[7] = 0;
                hex_digits = 2;
                hex_scan_state = leading_hex_zeroes;
                c = fetch();
                break;
            case leading_hex_zeroes:
                if (c == '0') {
                    c = fetch();
                } else {
                    hex_scan_state = int_hex_digit_loop;
                }
                break;
            case int_hex_digit_loop:
                if (!isxdigit(c)) {
                    if (c == radix) {
                        hex_scan_state = frac_hex_start;
                        c = fetch();
                    } else {
                        hex_scan_state = frac_hex_digit_loop;
                    }
                    break;
                }
                if (hex_digits < 17) {
                    unsigned char t = buf[hex_digits / 2];
                    unsigned char dig;
                    int u;
                    hex_dig_count++;
                    u = toupper(c);
                    if (u >= 'A') u = u - 'A' + 10; else u -= '0';
                    dig = u;
                    if (hex_digits % 2) {
                        t |= dig;
                    } else {
                        t |= dig << 4;
                    }
                    buf[hex_digits++ / 2] = t;
                    c = fetch();
                    break;
                }
                c = fetch();
                break;
            case frac_hex_start:
                if (!isxdigit(c)) {
                    hex_scan_state = frac_hex_digit_loop;
                    break;
                }
                if (hex_digits < 17) {
                    unsigned char t = buf[hex_digits / 2];
                    unsigned char dig;
                    int u;
                    u = toupper(c);
                    if (u >= 'A') u = u - 'A' + 10; else u -= '0';
                    dig = u;
                    if (hex_digits % 2) {
                        t |= dig;
                    } else {
                        t |= dig << 4;
                    }
                    buf[hex_digits++ / 2] = t;
                    c = fetch();
                    break;
                }
                c = fetch();
                break;
            case frac_hex_digit_loop:
                if (toupper(c) == 'P') {
                    hex_scan_state = p_exp_start;
                    hex_exp_digits++;
                    c = fetch();
                } else {
                    scan_state = finished;
                }
                break;
            case p_exp_start:
                hex_exp_digits++;
                if (c == '-') {
                    hex_exp_negative = 1;
                } else if (c != '+') {
                    unfetch(c);
                    hex_exp_digits--;
                }
                hex_scan_state = p_exp_sign;
                c = fetch();
                break;
            case p_exp_sign:
                if (!isdigit(c)) {
                    scan_state = failure;
                    break;
                }
                if (c == '0') {
                    hex_scan_state = 0x80;
                    hex_exp_digits++;
                    c = fetch();
                } else {
                    hex_scan_state = p_exp_digit_loop;
                }
                break;
            case p_exp_digit_loop:
                if (!isdigit(c)) {
                    scan_state = finished;
                    break;
                }
                hex_exp = hex_exp * 10 + (c - '0');
                if (exp_value > 0x7fff) {
                    *overflow = 1;
                }
                hex_exp_digits++;
                c = fetch();
                break;
            }
            break;
        }
    }

    if (!success(scan_state)) {
        *chars_scanned = 0;
    } else {
        *chars_scanned = count - 1 + spaces;
    }
    unfetch(c);

    if (hex_scan_state == not_hex) {
        int n;
        unsigned char* p;
        if (exp_negative) {
            exp_value = -exp_value;
        }
        n = d.sig.length;
        p = &d.sig.text[n];
        while (n-- != 0 && *--p == '0') {
            dec_exp++;
        }
        d.sig.length = n + 1;
        if (d.sig.length == 0) {
            d.sig.text[d.sig.length++] = '0';
        }
        exp_value += dec_exp;
        if (exp_value < -0x8000 || exp_value > 0x7fff) {
            *overflow = 1;
        }
        if (*overflow) {
            if (exp_negative) {
                return 0.0;
            }
            if (sign) {
                return -__double_huge[0];
            }
            return __double_huge[0];
        }
        d.exp = exp_value;
        r.v = __dec2num(&d);
        if (r.v != 0.0 && r.v < __extended_min[0]) {
            *overflow = 1;
        } else if (r.v > __extended_max[0]) {
            *overflow = 1;
            r.v = __double_huge[0];
        }
        if (sign && scan_state) {
            r.v = -r.v;
        }
        return r.v;
    }

    if (r.v) {
        if (hex_exp_negative) {
            hex_exp = -hex_exp;
        }
        while ((*(short*)buf & 0xf0) != 0x10) {
            hex_exp++;
            r.u >>= 1;
        }
        hex_exp += (hex_dig_count - 1) * 4;
        r.s &= 0xf;
        r.s |= (hex_exp + 0x3ff) << 4;
        *chars_scanned = spaces + sign_detected + hex_digits + 1 + hex_exp_digits;
        if (0.0 != r.v && r.v < __extended_min[0]) {
            r.v = 0.0;
            *overflow = 1;
        } else if (r.v > __extended_max[0]) {
            *overflow = 1;
            r.v = __double_huge[0];
        }
        if (sign) {
            r.s |= 0x8000;
        }
    } else {
        r.v = 0.0;
    }
    return r.v;
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: __strtold (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
#pragma force_active on // FAKE: keep asm-only-referenced data from being dead-stripped
__declspec(section ".rodata") const unsigned long zero_803025a0[11] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
__declspec(section ".rodata") const char str_803025CC[] = "INFINITY\000\000\000";
__declspec(section ".sdata2") const char str_80422660[8] = "NAN(\0\0\0";
__declspec(section ".sdata2") const double double_0_80422668 = 0.0;
__declspec(section ".sdata2") const double double_0_80422670 = 0.0;

asm long double __strtold(int max_width, int (*ReadProc)(void*, int, int), void* ReadProcArg, int* chars_scanned, int* overflow) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	lis r8, zero_803025a0@ha
	stw r0, 0xb4(r1)
	li r0, 0x0
	stmw r14, 0x68(r1)
	addi r23, r8, zero_803025a0@l
	mr r16, r4
	lis r4, __lconv@ha
	addi r14, r4, __lconv@l
	mr r17, r5
	mr r18, r7
	stw r6, 0xc(r1)
	mr r12, r16
	addi r26, r1, 0x18
	stw r3, 0x8(r1)
	mr r3, r17
	li r15, 0x1
	li r31, 0x0
	li r29, 0x0
	li r28, 0x0
	li r27, 0x0
	li r24, 0x0
	lwz r22, 0x0(r23)
	lwz r20, 0x4(r23)
	lwz r21, 0x8(r23)
	lwz r4, 0xc(r23)
	lwz r5, 0x10(r23)
	lwz r19, 0x14(r23)
	lwz r11, 0x18(r23)
	lwz r10, 0x1c(r23)
	lwz r9, 0x20(r23)
	lwz r8, 0x24(r23)
	lhz r7, 0x28(r23)
	li r23, 0x0
	stw r22, 0x2c(r1)
	li r22, 0x0
	lwz r6, 0x0(r14)
	li r14, 0x0
	stw r20, 0x30(r1)
	li r20, 0x0
	stw r4, 0x38(r1)
	li r4, 0x0
	stw r5, 0x3c(r1)
	li r5, 0x0
	stw r20, 0x60(r1)
	li r20, 0x0
	stw r20, 0x5c(r1)
	li r20, 0x0
	stw r21, 0x34(r1)
	stw r19, 0x40(r1)
	stw r11, 0x44(r1)
	stw r10, 0x48(r1)
	stw r9, 0x4c(r1)
	stw r8, 0x50(r1)
	sth r7, 0x54(r1)
	lbz r21, 0x0(r6)
	stw r20, 0x58(r1)
	stw r0, 0x0(r18)
	mtctr r12
	li r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@2:
	cmpwi r15, 0x80
	beq @3
	bge @4
	cmpwi r15, 0x8
	beq @5
	bge @6
	cmpwi r15, 0x3
	beq @1
	bge @7
	cmpwi r15, 0x1
	beq @8
	bge @9
	b @1
	@7:
	cmpwi r15, 0x5
	bge @1
	b @10
	@6:
	cmpwi r15, 0x20
	beq @11
	bge @12
	cmpwi r15, 0x10
	beq @13
	b @1
	@12:
	cmpwi r15, 0x40
	beq @14
	b @1
	@4:
	cmpwi r15, 0x2000
	beq @15
	bge @16
	cmpwi r15, 0x200
	beq @17
	bge @18
	cmpwi r15, 0x100
	beq @19
	b @1
	@18:
	cmpwi r15, 0x400
	beq @20
	b @1
	@16:
	lis r3, 0x1
	addi r0, r3, -0x8000
	cmpw r15, r0
	beq @21
	bge @1
	cmpwi r15, 0x4000
	beq @22
	b @1
	@8:
	lis r3, __ctype_map@ha
	clrlwi r5, r4, 24
	addi r3, r3, __ctype_map@l
	lbzx r0, r3, r5
	rlwinm. r0, r0, 0, 29, 30
	beq @23
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	bctrl
	mr r4, r3
	addi r29, r29, 0x1
	b @1
	@23:
	cmpwi r4, -0x1
	bne @24
	li r0, -0x1
	b @25
	@24:
	lis r3, __upper_map@ha
	addi r3, r3, __upper_map@l
	lbzx r0, r3, r5
	@25:
	cmpwi r0, 0x49
	beq @26
	bge @27
	cmpwi r0, 0x2c
	beq @28
	bge @29
	cmpwi r0, 0x2b
	bge @30
	b @28
	@29:
	cmpwi r0, 0x2e
	bge @28
	b @31
	@27:
	cmpwi r0, 0x4e
	beq @32
	b @28
	@31:
	li r14, 0x1
	@30:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	li r0, 0x1
	mr r4, r3
	stw r0, 0x5c(r1)
	b @1
	@26:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	li r15, 0x4000
	mr r4, r3
	b @1
	@32:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	li r15, 0x2000
	mr r4, r3
	b @1
	@28:
	li r15, 0x2
	b @1
	@22:
	lis r3, str_803025CC@ha
	addi r15, r1, 0x21
	addi r6, r3, str_803025CC@l
	li r19, 0x1
	lwz r5, 0x0(r6)
	lwz r3, 0x4(r6)
	lbz r0, 0x8(r6)
	stw r5, 0x20(r1)
	stw r3, 0x24(r1)
	stb r0, 0x28(r1)
	b @33
	@34:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r15, r15, 0x1
	addi r19, r19, 0x1
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	@33:
	cmpwi r19, 0x8
	bge @35
	lbz r0, 0x0(r15)
	cmpwi r4, -0x1
	extsb r5, r0
	bne @36
	li r0, -0x1
	b @37
	@36:
	lis r3, __upper_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __upper_map@l
	lbzx r0, r3, r0
	@37:
	cmpw r5, r0
	beq @34
	@35:
	cmpwi r19, 0x3
	beq @38
	cmpwi r19, 0x8
	bne @39
	@38:
	cmpwi r14, 0x0
	beq @40
	lis r3, __float_huge@ha
	lfs f0, __float_huge@l(r3)
	fneg f1, f0
	b @41
	@40:
	lis r3, __float_huge@ha
	lfs f1, __float_huge@l(r3)
	@41:
	lwz r0, 0x5c(r1)
	lwz r3, 0xc(r1)
	add r0, r19, r0
	stfd f1, 0x18(r1)
	add r0, r29, r0
	stw r0, 0x0(r3)
	b @42
	@39:
	li r15, 0x1000
	b @1
	@15:
	lwz r3, str_80422660(r2)
	addi r15, r1, 0x11
	lbz r0, str_80422660+0x4(r2)
	li r20, 0x1
	stw r3, 0x10(r1)
	li r19, 0x0
	stb r0, 0x14(r1)
	b @43
	@44:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r15, r15, 0x1
	addi r20, r20, 0x1
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	@43:
	cmpwi r20, 0x4
	bge @45
	lbz r0, 0x0(r15)
	cmpwi r4, -0x1
	extsb r5, r0
	bne @46
	li r0, -0x1
	b @47
	@46:
	lis r3, __upper_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __upper_map@l
	lbzx r0, r3, r0
	@47:
	cmpw r5, r0
	beq @44
	@45:
	cmpwi r20, 0x3
	beq @48
	cmpwi r20, 0x4
	bne @49
	@48:
	cmpwi r20, 0x4
	bne @50
	lis r3, __ctype_map@ha
	addi r15, r3, __ctype_map@l
	b @51
	@52:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r19, r19, 0x1
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	@51:
	cmpwi r19, 0x20
	bge @53
	clrlwi r0, r4, 24
	lbzx r3, r15, r0
	rlwinm. r0, r3, 0, 27, 27
	bne @52
	rlwinm. r0, r3, 0, 24, 25
	bne @52
	@53:
	cmpwi r4, 0x29
	beq @54
	li r15, 0x1000
	b @1
	@54:
	addi r19, r19, 0x1
	@50:
	cmpwi r14, 0x0
	beq @55
	lis r3, __float_nan@ha
	lfs f0, __float_nan@l(r3)
	fneg f1, f0
	b @56
	@55:
	lis r3, __float_nan@ha
	lfs f1, __float_nan@l(r3)
	@56:
	lwz r0, 0x5c(r1)
	add r3, r20, r19
	stfd f1, 0x18(r1)
	add r0, r3, r0
	lwz r3, 0xc(r1)
	add r0, r29, r0
	stw r0, 0x0(r3)
	b @42
	@49:
	li r15, 0x1000
	b @1
	@9:
	cmpw r4, r21
	bne @57
	mr r12, r16
	mr r3, r17
	li r15, 0x10
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@57:
	lis r3, __ctype_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __ctype_map@l
	lbzx r0, r3, r0
	rlwinm. r0, r0, 0, 27, 27
	bne @58
	li r15, 0x1000
	b @1
	@58:
	cmpwi r4, 0x30
	bne @59
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	cmpwi r3, -0x1
	mr r4, r3
	bne @60
	li r0, -0x1
	b @61
	@60:
	lis r5, __upper_map@ha
	clrlwi r0, r3, 24
	addi r3, r5, __upper_map@l
	lbzx r0, r3, r0
	@61:
	cmpwi r0, 0x58
	bne @62
	lis r3, 0x1
	li r31, 0x1
	addi r15, r3, -0x8000
	b @1
	@62:
	li r15, 0x4
	b @1
	@59:
	li r15, 0x8
	b @1
	@10:
	cmpwi r4, 0x30
	bne @63
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@63:
	li r15, 0x8
	b @1
	@5:
	lis r3, __ctype_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __ctype_map@l
	lbzx r0, r3, r0
	rlwinm. r0, r0, 0, 27, 27
	bne @64
	cmpw r4, r21
	bne @65
	mr r12, r16
	mr r3, r17
	li r15, 0x20
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@65:
	li r15, 0x40
	b @1
	@64:
	lbz r5, 0x30(r1)
	cmplwi r5, 0x14
	bge @66
	addi r0, r5, 0x1
	addi r3, r1, 0x2c
	stb r0, 0x30(r1)
	addi r0, r5, 0x5
	stbx r4, r3, r0
	b @67
	@66:
	addi r27, r27, 0x1
	@67:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@13:
	lis r3, __ctype_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __ctype_map@l
	lbzx r0, r3, r0
	rlwinm. r0, r0, 0, 27, 27
	bne @68
	li r15, 0x1000
	b @1
	@68:
	li r15, 0x20
	b @1
	@11:
	lis r3, __ctype_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __ctype_map@l
	lbzx r0, r3, r0
	rlwinm. r0, r0, 0, 27, 27
	bne @69
	li r15, 0x40
	b @1
	@69:
	lbz r0, 0x30(r1)
	cmplwi r0, 0x14
	bge @70
	cmpwi r4, 0x30
	bne @71
	cmplwi r0, 0x0
	beq @72
	@71:
	lbz r6, 0x30(r1)
	addi r3, r1, 0x2c
	addi r5, r6, 0x1
	addi r0, r6, 0x5
	stb r5, 0x30(r1)
	stbx r4, r3, r0
	@72:
	subi r27, r27, 0x1
	@70:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@14:
	cmpwi r4, -0x1
	bne @73
	li r0, -0x1
	b @74
	@73:
	lis r3, __upper_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __upper_map@l
	lbzx r0, r3, r0
	@74:
	cmpwi r0, 0x45
	bne @75
	mr r12, r16
	mr r3, r17
	li r15, 0x80
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@75:
	li r15, 0x800
	b @1
	@3:
	cmpwi r4, 0x2b
	bne @76
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @77
	@76:
	cmpwi r4, 0x2d
	bne @77
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	li r0, 0x1
	mr r4, r3
	stw r0, 0x60(r1)
	@77:
	li r15, 0x100
	b @1
	@19:
	lis r3, __ctype_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __ctype_map@l
	lbzx r0, r3, r0
	rlwinm. r0, r0, 0, 27, 27
	bne @78
	li r15, 0x1000
	b @1
	@78:
	cmpwi r4, 0x30
	bne @79
	mr r12, r16
	mr r3, r17
	li r15, 0x200
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@79:
	li r15, 0x400
	b @1
	@17:
	cmpwi r4, 0x30
	bne @80
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@80:
	li r15, 0x400
	b @1
	@20:
	lis r3, __ctype_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __ctype_map@l
	lbzx r0, r3, r0
	rlwinm. r0, r0, 0, 27, 27
	bne @81
	li r15, 0x800
	b @1
	@81:
	mulli r0, r28, 0xa
	add r28, r4, r0
	subi r28, r28, 0x30
	cmpwi r28, 0x7fff
	ble @82
	li r0, 0x1
	stw r0, 0x0(r18)
	@82:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@21:
	cmpwi r31, 0x10
	beq @83
	bge @84
	cmpwi r31, 0x4
	beq @85
	bge @86
	cmpwi r31, 0x2
	beq @87
	bge @1
	cmpwi r31, 0x1
	bge @88
	b @1
	@86:
	cmpwi r31, 0x8
	beq @89
	b @1
	@84:
	cmpwi r31, 0x40
	beq @90
	bge @91
	cmpwi r31, 0x20
	beq @92
	b @1
	@91:
	cmpwi r31, 0x100
	beq @93
	b @1
	@88:
	li r0, 0x0
	mr r12, r16
	mr r3, r17
	stb r0, 0x18(r1)
	li r25, 0x2
	li r31, 0x2
	stb r0, 0x19(r1)
	li r4, 0x0
	li r5, 0x0
	stb r0, 0x1a(r1)
	stb r0, 0x1b(r1)
	stb r0, 0x1c(r1)
	stb r0, 0x1d(r1)
	stb r0, 0x1e(r1)
	stb r0, 0x1f(r1)
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@87:
	cmpwi r4, 0x30
	bne @94
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@94:
	li r31, 0x4
	b @1
	@85:
	lis r3, __ctype_map@ha
	clrlwi r5, r4, 24
	addi r3, r3, __ctype_map@l
	lbzx r0, r3, r5
	rlwinm. r0, r0, 0, 26, 26
	bne @95
	cmpw r4, r21
	bne @96
	mr r12, r16
	mr r3, r17
	li r31, 0x8
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@96:
	li r31, 0x10
	b @1
	@95:
	cmpwi r25, 0x11
	bge @97
	srwi r0, r25, 31
	cmpwi r4, -0x1
	add r0, r0, r25
	addi r23, r23, 0x1
	srawi r0, r0, 1
	lbzx r6, r26, r0
	bne @98
	li r3, -0x1
	b @99
	@98:
	lis r3, __upper_map@ha
	addi r3, r3, __upper_map@l
	lbzx r3, r3, r5
	@99:
	cmpwi r3, 0x41
	blt @100
	subi r5, r3, 0x37
	b @101
	@100:
	subi r5, r3, 0x30
	@101:
	srwi r4, r25, 31
	clrlwi r0, r25, 31
	xor r3, r0, r4
	clrlslwi r0, r5, 24, 4
	subf. r3, r4, r3
	clrlwi r3, r5, 24
	or r0, r6, r0
	clrlwi r5, r0, 24
	beq @102
	or r0, r6, r3
	clrlwi r5, r0, 24
	@102:
	srwi r0, r25, 31
	mr r12, r16
	add r0, r0, r25
	mr r3, r17
	srawi r0, r0, 1
	li r4, 0x0
	stbx r5, r26, r0
	li r5, 0x0
	mtctr r12
	addi r25, r25, 0x1
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@97:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@89:
	lis r3, __ctype_map@ha
	clrlwi r5, r4, 24
	addi r3, r3, __ctype_map@l
	lbzx r0, r3, r5
	rlwinm. r0, r0, 0, 26, 26
	bne @103
	li r31, 0x10
	b @1
	@103:
	cmpwi r25, 0x11
	bge @104
	srwi r0, r25, 31
	cmpwi r4, -0x1
	add r0, r0, r25
	srawi r0, r0, 1
	lbzx r6, r26, r0
	bne @105
	li r3, -0x1
	b @106
	@105:
	lis r3, __upper_map@ha
	addi r3, r3, __upper_map@l
	lbzx r3, r3, r5
	@106:
	cmpwi r3, 0x41
	blt @107
	subi r5, r3, 0x37
	b @108
	@107:
	subi r5, r3, 0x30
	@108:
	srwi r4, r25, 31
	clrlwi r0, r25, 31
	xor r3, r0, r4
	clrlslwi r0, r5, 24, 4
	subf. r3, r4, r3
	clrlwi r3, r5, 24
	or r0, r6, r0
	clrlwi r5, r0, 24
	beq @109
	or r0, r6, r3
	clrlwi r5, r0, 24
	@109:
	srwi r0, r25, 31
	mr r12, r16
	add r0, r0, r25
	mr r3, r17
	srawi r0, r0, 1
	li r4, 0x0
	stbx r5, r26, r0
	li r5, 0x0
	mtctr r12
	addi r25, r25, 0x1
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@104:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@83:
	cmpwi r4, -0x1
	bne @110
	li r0, -0x1
	b @111
	@110:
	lis r3, __upper_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __upper_map@l
	lbzx r0, r3, r0
	@111:
	cmpwi r0, 0x50
	bne @112
	mr r12, r16
	mr r3, r17
	li r31, 0x20
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r24, r24, 0x1
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@112:
	li r15, 0x800
	b @1
	@92:
	cmpwi r4, 0x2d
	addi r24, r24, 0x1
	bne @113
	li r0, 0x1
	stw r0, 0x58(r1)
	b @114
	@113:
	cmpwi r4, 0x2b
	beq @114
	mr r12, r16
	mr r3, r17
	li r5, 0x1
	mtctr r12
	bctrl
	subi r24, r24, 0x1
	@114:
	mr r12, r16
	mr r3, r17
	li r31, 0x40
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@90:
	lis r3, __ctype_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __ctype_map@l
	lbzx r0, r3, r0
	rlwinm. r0, r0, 0, 27, 27
	bne @115
	li r15, 0x1000
	b @1
	@115:
	cmpwi r4, 0x30
	bne @116
	mr r12, r16
	mr r3, r17
	li r31, 0x80
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r24, r24, 0x1
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	b @1
	@116:
	li r31, 0x100
	b @1
	@93:
	lis r3, __ctype_map@ha
	clrlwi r0, r4, 24
	addi r3, r3, __ctype_map@l
	lbzx r0, r3, r0
	rlwinm. r0, r0, 0, 27, 27
	bne @117
	li r15, 0x800
	b @1
	@117:
	mulli r0, r22, 0xa
	cmpwi r28, 0x7fff
	add r3, r4, r0
	subi r0, r3, 0x30
	extsh r22, r0
	ble @118
	li r0, 0x1
	stw r0, 0x0(r18)
	@118:
	mr r12, r16
	mr r3, r17
	li r4, 0x0
	li r5, 0x0
	mtctr r12
	addi r24, r24, 0x1
	addi r30, r30, 0x1
	bctrl
	mr r4, r3
	@1:
	lwz r0, 0x8(r1)
	cmpw r30, r0
	bgt @119
	cmpwi r4, -0x1
	beq @119
	rlwinm. r0, r15, 0, 19, 20
	beq @2
	@119:
	andi. r15, r15, 0xe2c
	bne @120
	lwz r3, 0xc(r1)
	li r0, 0x0
	stw r0, 0x0(r3)
	b @121
	@120:
	add r3, r30, r29
	subi r0, r3, 0x1
	lwz r3, 0xc(r1)
	stw r0, 0x0(r3)
	@121:
	mr r12, r16
	mr r3, r17
	li r5, 0x1
	mtctr r12
	bctrl
	cmpwi r31, 0x0
	bne @122
	lwz r0, 0x60(r1)
	cmpwi r0, 0x0
	beq @123
	neg r28, r28
	@123:
	lbz r3, 0x30(r1)
	addi r0, r1, 0x2c
	addi r4, r3, 0x5
	add r4, r0, r4
	b @124
	@125:
	addi r27, r27, 0x1
	@124:
	cmpwi r3, 0x0
	subi r3, r3, 0x1
	beq @126
	lbzu r0, -0x1(r4)
	cmplwi r0, 0x30
	beq @125
	@126:
	addi r0, r3, 0x1
	clrlwi. r4, r0, 24
	stb r0, 0x30(r1)
	bne @127
	addi r0, r4, 0x1
	addi r3, r1, 0x31
	stb r0, 0x30(r1)
	li r0, 0x30
	stbx r0, r3, r4
	@127:
	add r28, r28, r27
	cmpwi r28, -0x8000
	blt @128
	cmpwi r28, 0x7fff
	ble @129
	@128:
	li r0, 0x1
	stw r0, 0x0(r18)
	@129:
	lwz r0, 0x0(r18)
	cmpwi r0, 0x0
	beq @130
	lwz r0, 0x60(r1)
	cmpwi r0, 0x0
	beq @131
	lfd f1, double_0_80422668(r2)
	b @42
	@131:
	cmpwi r14, 0x0
	beq @132
	lis r3, __double_huge@ha
	lfd f0, __double_huge@l(r3)
	fneg f1, f0
	b @42
	@132:
	lis r3, __double_huge@ha
	lfd f1, __double_huge@l(r3)
	b @42
	@130:
	sth r28, 0x2e(r1)
	addi r3, r1, 0x2c
	bl __dec2num
	lfd f0, double_0_80422668(r2)
	stfd f1, 0x18(r1)
	fcmpu cr0, f0, f1
	beq @133
	lis r3, __extended_min@ha
	lfd f0, __extended_min@l(r3)
	fcmpo cr0, f1, f0
	bge @133
	li r0, 0x1
	stw r0, 0x0(r18)
	b @134
	@133:
	lis r3, __extended_max@ha
	lfd f0, __extended_max@l(r3)
	fcmpo cr0, f1, f0
	ble @134
	li r0, 0x1
	lis r3, __double_huge@ha
	stw r0, 0x0(r18)
	lfd f0, __double_huge@l(r3)
	stfd f0, 0x18(r1)
	@134:
	cmpwi r14, 0x0
	beq @135
	cmpwi r15, 0x0
	beq @135
	lfd f0, 0x18(r1)
	fneg f0, f0
	stfd f0, 0x18(r1)
	@135:
	lfd f1, 0x18(r1)
	b @42
	@122:
	lfd f1, 0x18(r1)
	lfd f0, double_0_80422670(r2)
	fcmpu cr0, f1, f0
	beq @136
	lwz r0, 0x58(r1)
	cmpwi r0, 0x0
	beq @137
	neg r0, r22
	extsh r22, r0
	b @137
	@138:
	lwz r4, 0x18(r1)
	addi r22, r22, 0x1
	lwz r3, 0x1c(r1)
	srwi r0, r4, 1
	rotrwi r3, r3, 1
	stw r0, 0x18(r1)
	rlwimi r3, r4, 31, 0, 0
	stw r3, 0x1c(r1)
	@137:
	lha r3, 0x18(r1)
	rlwinm r0, r3, 0, 24, 27
	cmpwi r0, 0x10
	bne @138
	subi r0, r23, 0x1
	clrlwi r4, r3, 28
	slwi r5, r0, 2
	lwz r0, 0x5c(r1)
	sth r4, 0x18(r1)
	add r3, r0, r25
	add r0, r22, r5
	extsh r22, r0
	lfd f1, double_0_80422668(r2)
	addi r0, r3, 0x1
	addi r3, r22, 0x3ff
	rlwimi r4, r3, 4, 0, 27
	add r0, r0, r24
	sth r4, 0x18(r1)
	add r0, r29, r0
	lwz r3, 0xc(r1)
	lfd f2, 0x18(r1)
	stw r0, 0x0(r3)
	fcmpu cr0, f1, f2
	beq @139
	lis r3, __extended_min@ha
	lfd f0, __extended_min@l(r3)
	fcmpo cr0, f2, f0
	bge @139
	li r0, 0x1
	stfd f1, 0x18(r1)
	stw r0, 0x0(r18)
	b @140
	@139:
	lis r3, __extended_max@ha
	lfd f0, __extended_max@l(r3)
	fcmpo cr0, f2, f0
	ble @140
	li r0, 0x1
	lis r3, __double_huge@ha
	stw r0, 0x0(r18)
	lfd f0, __double_huge@l(r3)
	stfd f0, 0x18(r1)
	@140:
	cmpwi r14, 0x0
	beq @141
	lha r0, 0x18(r1)
	ori r0, r0, 0x8000
	sth r0, 0x18(r1)
	b @141
	@136:
	lfd f0, double_0_80422668(r2)
	stfd f0, 0x18(r1)
	@141:
	lfd f1, 0x18(r1)
	@42:
	lmw r14, 0x68(r1)
	lwz r0, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}
// clang-format on
#endif
