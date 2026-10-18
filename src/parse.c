// FAKE: G5 asm stopgap (parseTagGet1..parsePush as asm so .text order holds); C under #ifdef NONMATCHING. Best pure C: 5/6 (parsePush 99.71).
#include "parse.h"
#include <string.h>
#include <stdio.h>

int sscanf(const char* s, const char* format, ...);

//.bss
static char parsePushBuf[128]; // FAKE: was parsePush's local static (asm cannot name it)
extern ParseWork parse;

void parseInit(void* ptr, u32 size) {
	parse.ptr = ptr;
	parse.depth = 0;
	parse.pos[0] = 0;
	parse.end[0] = size;
}

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
#endif

#ifdef NONMATCHING
void parsePop(void) {
	parse.depth--;
}
#endif

#ifdef NONMATCHING
void parsePopNext(void) {
	parse.depth--;
	parse.pos[parse.depth] = parse.end[parse.depth + 1];
}
#endif

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
#endif

#ifdef NONMATCHING
BOOL parseTagGet1(const char* tag, s32 type, void* data) {
	BOOL result;

	if (parsePush(tag)) {
		result = parseGet1Next(type, data);
		parsePop();
		return result;
	}
	return FALSE;
}
#endif

#ifndef NONMATCHING
// ASM-STOPGAP: parsePush (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
__declspec(section ".sdata2") const char str_8041A6B0[4] = "%d\0";
__declspec(section ".sdata2") const char str_8041A6B4[4] = "%f\0";

asm BOOL parseTagGet1(const char* tag, s32 type, void* data) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r5
	stw r30, 0x8(r1)
	mr r30, r4
	bl parsePush
	cmpwi r3, 0x0
	beq @1
	mr r3, r30
	mr r4, r31
	bl parseGet1Next
	lis r4, parse@ha
	addi r5, r4, parse@l
	lwz r4, 0x54(r5)
	subi r0, r4, 0x1
	stw r0, 0x54(r5)
	b @2
	@1:
	li r3, 0x0
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm BOOL parseGet1Next(s32 type, void* data) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	cmpwi r3, 0x3
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	li r31, 0x1
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	mr r29, r4
	beq @1
	b @2
	@1:
	li r3, 0x2
	bl parseGet1Next
	mullw r31, r31, r3
	addi r4, r29, 0x4
	li r3, 0x2
	bl parseGet1Next
	mullw r31, r31, r3
	addi r4, r29, 0x8
	li r3, 0x2
	bl parseGet1Next
	mullw r31, r31, r3
	mr r3, r31
	b @3
	@2:
	lis r4, parse@ha
	li r5, 0x0
	addi r7, r4, parse@l
	lwz r0, 0x54(r7)
	lwz r4, 0x0(r7)
	slwi r0, r0, 2
	add r31, r7, r0
	lwz r10, 0x4(r31)
	lwz r0, 0x2c(r31)
	addi r31, r31, 0x4
	b @4
	@5:
	add r8, r4, r10
	lbz r9, 0x0(r8)
	cmpwi r9, 0x2f
	bne @6
	lbz r7, 0x1(r8)
	cmpwi r7, 0x2f
	bne @6
	subf r7, r10, r0
	mtctr r7
	cmpw r10, r0
	bge @7
	@8:
	lbz r7, 0x0(r8)
	extsb r7, r7
	cmplwi r7, 0x2f6e
	beq @7
	addi r10, r10, 0x1
	addi r8, r8, 0x1
	bdnz @8
	b @7
	@6:
	extsb r7, r9
	cmpwi r7, 0x20
	beq @7
	cmpwi r7, 0x9
	beq @7
	cmpwi r7, 0xa
	beq @7
	cmpwi r7, 0xd
	beq @7
	mr r6, r10
	addi r10, r10, 0x1
	subf r7, r10, r0
	li r5, 0x1
	mtctr r7
	cmpw r10, r0
	bge @9
	@10:
	add r9, r4, r10
	lbz r7, 0x0(r9)
	extsb r8, r7
	cmpwi r8, 0x20
	beq @11
	subi r7, r7, 0x9
	clrlwi r7, r7, 24
	cmplwi r7, 0x1
	ble @11
	cmpwi r8, 0xd
	beq @11
	cmpwi r8, 0x2f
	bne @12
	lbz r7, 0x1(r9)
	cmpwi r7, 0x2f
	bne @12
	@11:
	mr r30, r10
	li r5, 0x2
	b @9
	@12:
	addi r10, r10, 0x1
	bdnz @10
	b @9
	@7:
	addi r10, r10, 0x1
	@4:
	cmpw r10, r0
	blt @5
	@9:
	cmpwi r5, 0x1
	bgt @13
	li r3, 0x0
	b @3
	@13:
	cmpwi r3, 0x1
	beq @14
	bge @15
	cmpwi r3, 0x0
	bge @16
	b @17
	@15:
	cmpwi r3, 0x3
	bge @17
	b @18
	@16:
	mr r10, r6
	mr r8, r29
	add r5, r4, r6
	li r11, 0x0
	b @19
	@20:
	lbz r3, 0x0(r5)
	cmpwi r3, 0x22
	bne @21
	addi r10, r10, 0x1
	mr r7, r8
	subf r3, r10, r0
	add r6, r4, r10
	mtctr r3
	cmpw r10, r0
	addi r5, r5, 0x1
	bge @21
	@22:
	lbz r9, 0x0(r6)
	cmpwi r9, 0x22
	beq @21
	stb r9, 0x0(r7)
	addi r7, r7, 0x1
	addi r8, r8, 0x1
	addi r11, r11, 0x1
	addi r10, r10, 0x1
	addi r5, r5, 0x1
	addi r6, r6, 0x1
	bdnz @22
	@21:
	addi r10, r10, 0x1
	addi r5, r5, 0x1
	@19:
	cmpw r10, r0
	blt @20
	li r0, 0x0
	stbx r0, r11, r29
	stw r10, 0x0(r31)
	b @17
	@14:
	mr r5, r29
	add r3, r4, r6
	la r4, str_8041A6B0(r2)
	crclr 6
	bl sscanf
	stw r30, 0x0(r31)
	b @17
	@18:
	mr r5, r29
	add r3, r4, r6
	la r4, str_8041A6B4(r2)
	crclr 6
	bl sscanf
	stw r30, 0x0(r31)
	@17:
	li r3, 0x1
	@3:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void parsePopNext(void) {
	nofralloc
	lis r3, parse@ha
	addi r4, r3, parse@l
	lwz r3, 0x54(r4)
	subi r0, r3, 0x1
	slwi r3, r0, 2
	stw r0, 0x54(r4)
	add r3, r4, r3
	lwz r0, 0x30(r3)
	stw r0, 0x4(r3)
	blr
}

asm void parsePop(void) {
	nofralloc
	lis r3, parse@ha
	addi r4, r3, parse@l
	lwz r3, 0x54(r4)
	subi r0, r3, 0x1
	stw r0, 0x54(r4)
	blr
}

asm BOOL parsePush(const char* tag) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	lis r4, parse@ha
	stw r0, 0x44(r1)
	stmw r21, 0x14(r1)
	addi r31, r4, parse@l
	addi r30, r31, 0x4
	mr r21, r3
	addi r29, r31, 0x2c
	li r22, 0x0
	li r25, 0x0
	lwz r0, 0x54(r31)
	lwz r26, 0x0(r31)
	slwi r0, r0, 2
	lwzx r28, r30, r0
	lwzx r27, r29, r0
	b @1
	@2:
	add r5, r26, r28
	lbz r0, 0x0(r5)
	cmpwi r0, 0x3c
	bne @3
	lbz r0, 0x1(r5)
	cmpwi r0, 0x2f
	bne @4
	cmpwi r25, 0x1
	subi r22, r22, 0x1
	bne @3
	cmpwi r22, 0x0
	bne @3
	subf r0, r28, r27
	mtctr r0
	cmpw r28, r27
	bge @5
	@6:
	lbz r0, 0x0(r5)
	cmpwi r0, 0x3e
	bne @7
	addi r28, r28, 0x1
	b @5
	@7:
	addi r28, r28, 0x1
	addi r5, r5, 0x1
	bdnz @6
	@5:
	mr r23, r28
	li r25, 0x2
	b @8
	@4:
	cmpwi r25, 0x0
	bne @9
	cmpwi r22, 0x0
	bne @9
	lis r3, parsePushBuf@ha
	subf r0, r28, r27
	addi r6, r3, parsePushBuf@l
	mr r4, r28
	mr r3, r5
	li r5, 0x0
	mtctr r0
	cmpw r28, r27
	bge @10
	@11:
	lbz r7, 0x0(r3)
	extsb r0, r7
	cmpwi r0, 0x20
	beq @12
	cmpwi r0, 0x9
	beq @12
	cmpwi r0, 0xa
	beq @12
	cmpwi r0, 0xd
	beq @12
	stb r7, 0x0(r6)
	addi r6, r6, 0x1
	addi r5, r5, 0x1
	@12:
	cmpwi r5, 0x7f
	bge @10
	lbz r0, 0x0(r3)
	cmpwi r0, 0x3e
	beq @10
	addi r4, r4, 0x1
	addi r3, r3, 0x1
	bdnz @11
	@10:
	lis r3, parsePushBuf@ha
	li r0, 0x0
	addi r3, r3, parsePushBuf@l
	mr r4, r21
	stbx r0, r3, r5
	bl strcmp
	cmpwi r3, 0x0
	bne @9
	subf r0, r28, r27
	add r3, r26, r28
	mtctr r0
	cmpw r28, r27
	bge @13
	@14:
	lbz r0, 0x0(r3)
	cmpwi r0, 0x3e
	beq @13
	addi r28, r28, 0x1
	addi r3, r3, 0x1
	bdnz @14
	@13:
	li r25, 0x1
	addi r24, r28, 0x1
	@9:
	addi r22, r22, 0x1
	@3:
	addi r28, r28, 0x1
	@1:
	cmpw r28, r27
	blt @2
	@8:
	cmpwi r25, 0x2
	beq @15
	li r3, 0x0
	b @16
	@15:
	lwz r4, 0x54(r31)
	li r3, 0x1
	addi r0, r4, 0x1
	stw r0, 0x54(r31)
	slwi r0, r0, 2
	stwx r24, r30, r0
	stwx r23, r29, r0
	@16:
	lmw r21, 0x14(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}
// clang-format on
#endif

ParseWork parse;
