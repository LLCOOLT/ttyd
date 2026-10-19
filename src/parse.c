// FAKE: G5 asm stopgap (parseTagGet1..parsePush as asm so .text order holds); C under #ifdef NONMATCHING. Best pure C: 5/6 (parsePush 99.71).
#include "parse.h"
#include <string.h>
#include <stdio.h>
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
__declspec(section ".sdata2") extern const char str_8041A6B0[3];
__declspec(section ".sdata2") extern const char str_8041A6B4[3];
#endif

int sscanf(const char* s, const char* format, ...);

//.bss
#ifdef NONMATCHING
static char parsePushBuf[128]; // FAKE: was parsePush's local static (asm cannot name it)
#endif
extern ParseWork parse;
__declspec(section ".data") u8 g5_buf_s405[128];

void parseInit(void* ptr, u32 size) {
	parse.ptr = ptr;
	parse.depth = 0;
	parse.pos[0] = 0;
	parse.end[0] = size;
}

int strcmp(const char *s1, const char *s2);
#ifdef NONMATCHING
BOOL parsePush(const char* tag) {
	static char buf[128];
	s32 i;
	s32 end;
	s8* p;
	s32 state;
	s32 newStart;
	s32 newEnd;
	s32 depth;
	s32 j;
	s32 n;
	s8 c;
	depth = 0;
	state = 0;
	p = (s8*)parse.ptr;
	i = parse.pos[parse.depth];
	end = parse.end[parse.depth];
	for (; i < end; i++) {
		if (p[i] == '<') {
			if (p[i + 1] == '/') {
				depth--;
				if (state == 1 && depth == 0) {
					for (; i < end; i++) {
						if (p[i] == '>') {
							i++;
							break;
						}
					}
					newEnd = i;
					state = 2;
					break;
				}
			}
			else {
				if (state == 0 && depth == 0) {
					for (j = i, n = 0; j < end; j++) {
						c = p[j];
						if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
							buf[n] = c;
							n += 1;
						}
						if (n >= 127 || p[j] == '>') {
							break;
						}
					}
					*(buf + n) = 0;
					if (strcmp(&buf[0], tag) == 0) {
						for (; i < end; i++) {
							if (p[i] == '>') {
								break;
							}
						}
						state = 1;
						newStart = i + 1;
					}
				}
				depth++;
			}
		}
	}
	if (state != 2) {
		return FALSE;
	}
	i = ++parse.depth;
	parse.pos[i] = newStart;
	parse.end[i] = newEnd;
	return TRUE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // lets the prologue scheduler run
BOOL parsePush(const char* tag) {
	asm {
		lis r4, parse@ha
	}
	asm volatile {
		addi r31, r4, parse@l
		opword 0x3BDF0004
		mr r21, r3
		opword 0x3BBF002C
		opword 0x3AC00000
		opword 0x3B200000
		opword 0x801F0054
		opword 0x835F0000
		opword 0x5400103A
		opword 0x7F9E002E
		opword 0x7F7D002E
		opword 0x48000154
		opword 0x7CBAE214
		opword 0x88050000
		opword 0x2C00003C
		opword 0x40820140
		opword 0x88050001
		opword 0x2C00002F
		opword 0x40820054
		opword 0x2C190001
		opword 0x3AD6FFFF
		opword 0x40820128
		opword 0x2C160000
		opword 0x40820120
		opword 0x7C1CD850
		opword 0x7C0903A6
		opword 0x7C1CD800
		opword 0x40800024
		opword 0x88050000
		opword 0x2C00003E
		opword 0x4082000C
		opword 0x3B9C0001
		opword 0x48000010
		opword 0x3B9C0001
		opword 0x38A50001
		opword 0x4200FFE4
		opword 0x7F97E378
		opword 0x3B200002
		opword 0x480000F0
		opword 0x2C190000
		opword 0x408200D8
		opword 0x2C160000
		opword 0x408200D0
		lis r3, g5_buf_s405@ha
		opword 0x7C1CD850
		addi r6, r3, g5_buf_s405@l
		opword 0x7F84E378
		opword 0x7CA32B78
		opword 0x38A00000
		opword 0x7C0903A6
		opword 0x7C1CD800
		opword 0x40800058
		opword 0x88E30000
		opword 0x7CE00774
		opword 0x2C000020
		opword 0x41820028
		opword 0x2C000009
		opword 0x41820020
		opword 0x2C00000A
		opword 0x41820018
		opword 0x2C00000D
		opword 0x41820010
		opword 0x98E60000
		opword 0x38C60001
		opword 0x38A50001
		opword 0x2C05007F
		opword 0x4080001C
		opword 0x88030000
		opword 0x2C00003E
		opword 0x41820010
		opword 0x38840001
		opword 0x38630001
		opword 0x4200FFB0
		lis r3, g5_buf_s405@ha
		opword 0x38000000
		addi r3, r3, g5_buf_s405@l
		opword 0x7EA4AB78
		opword 0x7C0329AE
		bl strcmp
		opword 0x2C030000
		opword 0x40820038
		opword 0x7C1CD850
		opword 0x7C7AE214
		opword 0x7C0903A6
		opword 0x7C1CD800
		opword 0x4080001C
		opword 0x88030000
		opword 0x2C00003E
		opword 0x41820010
		opword 0x3B9C0001
		opword 0x38630001
		opword 0x4200FFEC
		opword 0x3B200001
		opword 0x3B1C0001
		opword 0x3AD60001
		opword 0x3B9C0001
		opword 0x7C1CD800
		opword 0x4180FEAC
		opword 0x2C190002
		opword 0x4182000C
		opword 0x38600000
		opword 0x48000020
		opword 0x809F0054
		opword 0x38600001
		opword 0x38040001
		opword 0x901F0054
		opword 0x5400103A
		opword 0x7F1E012E
		opword 0x7EFD012E
	}
}
#pragma pop
#endif

void parsePop(void) {
	parse.depth--;
}

void parsePopNext(void) {
	parse.depth--;
	parse.pos[parse.depth] = parse.end[parse.depth + 1];
}

#ifdef NONMATCHING
BOOL parseGet1Next(s32 type, void* data) {
	s32* posp;
	char* dst;
	s32 i;
	s32 end;
	s8* p;
	s32 start;
	s32 stop;
	BOOL result = TRUE;
	s32* new_var;
	s32 state;
	s32 j;
	s32 n;
	s8 c;

	switch (type) {
	case 3:
		result *= parseGet1Next(2, data);
		result *= parseGet1Next(2, (void*)((u32)data + 4));
		result *= parseGet1Next(2, (void*)((u32)data + 8));
		return result;
	}

	new_var = parse.pos;
	state = 0;
	p = (s8*)parse.ptr;
	i = new_var[parse.depth];
	end = parse.end[parse.depth];
	posp = new_var + parse.depth;
	for (; i < end; i++) {
		if (p[i] == '/' && p[i + 1] == '/') {
			for (; i < end; i++) {
				if (p[i] == '/n') {
					break;
				}
			}
		}
		else if (p[i] != ' ' && p[i] != '\t' && p[i] != '\n' && p[i] != '\r') {
			start = i;
			state = 1;
			for (i++; i < end; i++) {
				c = p[i];
				if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || (c == '/' && p[i + 1] == '/')) {
					stop = i;
					state = 2;
					break;
				}
			}
			break;
		}
	}
	if (state <= 1) {
		return FALSE;
	}
	switch (type) {
	case 0:
		n = 0;
		for (i = start; i < end; i++) {
			if (p[i] == '"') {
				for (i++; i < end; i++) {
					if (p[i] == '"') {
						break;
					}
					((char*)data)[n] = p[i];
					n++;
				}
			}
		}
		((char*)data)[n] = 0;
		*posp = i;
		break;
	case 1:
		sscanf((char*)&p[start], "%d", data);
		*posp = stop;
		break;
	case 2:
		sscanf((char*)&p[start], "%f\0", data);
		*posp = stop;
		break;
	}
	return TRUE;
}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
BOOL parseGet1Next(s32 type, void* data) {
	asm volatile {
		opword 0x9421FFE0
		opword 0x7C0802A6
		opword 0x2C030003
		opword 0x90010024
		opword 0x93E1001C
		opword 0x3BE00001
		opword 0x93C10018
		opword 0x93A10014
		opword 0x7C9D2378
		opword 0x41820008
		opword 0x48000038
		opword 0x38600002
		bl parseGet1Next
		opword 0x7FFF19D6
		opword 0x389D0004
		opword 0x38600002
		bl parseGet1Next
		opword 0x7FFF19D6
		opword 0x389D0008
		opword 0x38600002
		bl parseGet1Next
		opword 0x7FFF19D6
		opword 0x7FE3FB78
		opword 0x48000218
		lis r4, parse@ha
		opword 0x38A00000
		addi r7, r4, parse@l
		opword 0x80070054
		opword 0x80870000
		opword 0x5400103A
		opword 0x7FE70214
		opword 0x815F0004
		opword 0x801F002C
		opword 0x3BFF0004
		opword 0x480000EC
		opword 0x7D045214
		opword 0x89280000
		opword 0x2C09002F
		opword 0x40820040
		opword 0x88E80001
		opword 0x2C07002F
		opword 0x40820034
		opword 0x7CEA0050
		opword 0x7CE903A6
		opword 0x7C0A0000
		opword 0x408000BC
		opword 0x88E80000
		opword 0x7CE70774
		opword 0x28072F6E
		opword 0x418200AC
		opword 0x394A0001
		opword 0x39080001
		opword 0x4200FFE8
		opword 0x4800009C
		opword 0x7D270774
		opword 0x2C070020
		opword 0x41820090
		opword 0x2C070009
		opword 0x41820088
		opword 0x2C07000A
		opword 0x41820080
		opword 0x2C07000D
		opword 0x41820078
		opword 0x7D465378
		opword 0x394A0001
		opword 0x7CEA0050
		opword 0x38A00001
		opword 0x7CE903A6
		opword 0x7C0A0000
		opword 0x40800068
		opword 0x7D245214
		opword 0x88E90000
		opword 0x7CE80774
		opword 0x2C080020
		opword 0x41820030
		opword 0x38E7FFF7
		opword 0x54E7063E
		opword 0x28070001
		opword 0x40810020
		opword 0x2C08000D
		opword 0x41820018
		opword 0x2C08002F
		opword 0x4082001C
		opword 0x88E90001
		opword 0x2C07002F
		opword 0x40820010
		opword 0x7D5E5378
		opword 0x38A00002
		opword 0x4800001C
		opword 0x394A0001
		opword 0x4200FFB0
		opword 0x48000010
		opword 0x394A0001
		opword 0x7C0A0000
		opword 0x4180FF14
		opword 0x2C050001
		opword 0x4181000C
		opword 0x38600000
		opword 0x480000EC
		opword 0x2C030001
		opword 0x418200AC
		opword 0x40800010
		opword 0x2C030000
		opword 0x40800014
		opword 0x480000D0
		opword 0x2C030003
		opword 0x408000C8
		opword 0x480000AC
		opword 0x7CCA3378
		opword 0x7FA8EB78
		opword 0x7CA43214
		opword 0x39600000
		opword 0x48000064
		opword 0x88650000
		opword 0x2C030022
		opword 0x40820050
		opword 0x394A0001
		opword 0x7D074378
		opword 0x7C6A0050
		opword 0x7CC45214
		opword 0x7C6903A6
		opword 0x7C0A0000
		opword 0x38A50001
		opword 0x40800030
		opword 0x89260000
		opword 0x2C090022
		opword 0x41820024
		opword 0x99270000
		opword 0x38E70001
		opword 0x39080001
		opword 0x396B0001
		opword 0x394A0001
		opword 0x38A50001
		opword 0x38C60001
		opword 0x4200FFD8
		opword 0x394A0001
		opword 0x38A50001
		opword 0x7C0A0000
		opword 0x4180FF9C
		opword 0x38000000
		opword 0x7C0BE9AE
		opword 0x915F0000
		opword 0x48000038
		opword 0x7FA5EB78
		opword 0x7C643214
		la r4, str_8041A6B0(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x93DF0000
		opword 0x4800001C
		opword 0x7FA5EB78
		opword 0x7C643214
		la r4, str_8041A6B4(r2)
		opword 0x4CC63182
		bl sscanf
		opword 0x93DF0000
		opword 0x38600001
		opword 0x80010024
		opword 0x83E1001C
		opword 0x83C10018
		opword 0x83A10014
		opword 0x7C0803A6
		opword 0x38210020
	}
}
#pragma pop
#endif

BOOL parseTagGet1(const char* tag, s32 type, void* data) {
	BOOL result;

	if (parsePush(tag)) {
		result = parseGet1Next(type, data);
		parsePop();
		return result;
	}
	return FALSE;
}


ParseWork parse;

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".sdata2") const char str_8041A6B0[3] = "%d\0";
__declspec(section ".sdata2") const char str_8041A6B4[3] = "%f\0";
#endif
