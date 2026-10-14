#include "parse.h"
#include <string.h>
#include <stdio.h>

int sscanf(const char* s, const char* format, ...);

//.bss
ParseWork parse;

void parseInit(void* ptr, u32 size) {
	parse.ptr = ptr;
	parse.depth = 0;
	parse.pos[0] = 0;
	parse.end[0] = size;
}

BOOL parsePush(const char* tag) {
	static char buf[128];
	s32 i;
	s32 end;
	s8* p;
	s32 state;
	s32 newStart;
	s32 newEnd;
	s32 depth;
	s32 n;
	s32 j;
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
					n = 0;
					for (j = i; j < end; j++) {
						c = p[j];
						if (c != ' ' && c != '\t' && c != '\n' && c != '\r') {
							buf[n] = c;
							n++;
						}
						if (n >= 127 || p[j] == '>') {
							break;
						}
					}
					buf[n] = 0;
					if (strcmp(buf, tag) == 0) {
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

void parsePop(void) {
	parse.depth--;
}

void parsePopNext(void) {
	parse.depth--;
	parse.pos[parse.depth] = parse.end[parse.depth + 1];
}

BOOL parseGet1Next(s32 type, void* data) {
	s32* posp;
	s32 i;
	s32 end;
	s8* p;
	s32 start;
	s32 stop;
	BOOL result = TRUE;
	s32 state;
	s8 c;
	char* dst;
	s32 n;

	switch (type) {
	case 3:
		result *= parseGet1Next(2, data);
		result *= parseGet1Next(2, (void*)((u32)data + 4));
		result *= parseGet1Next(2, (void*)((u32)data + 8));
		return result;
	}

	state = 0;
	p = (s8*)parse.ptr;
	i = parse.pos[parse.depth];
	end = parse.end[parse.depth];
	posp = &parse.pos[parse.depth];
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

BOOL parseTagGet1(const char* tag, s32 type, void* data) {
	BOOL result;

	if (parsePush(tag)) {
		result = parseGet1Next(type, data);
		parsePop();
		return result;
	}
	return FALSE;
}

