#include "nameent.h"
#include "system.h"
#include "driver/dispdrv.h"
#include "driver/camdrv.h"
#include "driver/fadedrv.h"
#include "sdk/texPalette.h"
#include "driver/msgdrv.h"
#include "driver/windowdrv.h"
#include "manager/fontmgr.h"
#include "win/win_main.h"
#include "mario/mariost.h"
#include "pmario_sound.h"

void winTexInit_x2(TEXPalette* texture);
void winTexSet_x2(u32 id1, u32 id2, Vec translate, Vec scale, GXColor color);
void FontDrawString(f32 x, f32 y, const char* str);
void FontDrawEdge(void);
void FontDrawEdgeOff(void);
void GXGetProjectionv(f32* ptr);
void GXGetViewportv(f32* vp);
void nameBG(void);
void nameKirinukiGX(f32 x, f32 y, f32 w, f32 h);
void nameMaskGX(f32 t);
void nameWinGX(TEXPalette* tpl, s32 type, f32 x, f32 y, f32 w, f32 h);
#include <string.h>

s32 nameMain(void);
double sin(double);
void nameEntDisp(CameraId cameraId, void* param);

//.data
const char* hiragana_tbl[] = {
	"\x82\xA0", "\x82\xA2", "\x82\xA4", "\x82\xA6", "\x82\xA8", "\x82\xED",
	"\x81\x40", "\x82\xF0", "\x81\x40", "\x82\xF1", "\x82\x4F", "\x82\x50",
	"\x82\x51", "\x82\x52", "\x82\xA9", "\x82\xAB", "\x82\xAD", "\x82\xAF",
	"\x82\xB1", "\x82\xAA", "\x82\xAC", "\x82\xAE", "\x82\xB0", "\x82\xB2",
	"\x82\x53", "\x82\x54", "\x82\x55", "\x82\x56", "\x82\xB3", "\x82\xB5",
	"\x82\xB7", "\x82\xB9", "\x82\xBB", "\x82\xB4", "\x82\xB6", "\x82\xB8",
	"\x82\xBA", "\x82\xBC", "\x82\x57", "\x82\x58", "\x81\x49", "\x81\x48",
	"\x82\xBD", "\x82\xBF", "\x82\xC2", "\x82\xC4", "\x82\xC6", "\x82\xBE",
	"\x82\xC0", "\x82\xC3", "\x82\xC5", "\x82\xC7", "\x81\x40", "\x94\xB5",
	"\x81\x99", "\x81\xF4", "\x82\xC8", "\x82\xC9", "\x82\xCA", "\x82\xCB",
	"\x82\xCC", "\x82\xCE", "\x82\xD1", "\x82\xD4", "\x82\xD7", "\x82\xDA",
	NULL,       NULL,       NULL,       NULL,       "\x82\xCD", "\x82\xD0",
	"\x82\xD3", "\x82\xD6", "\x82\xD9", "\x82\xCF", "\x82\xD2", "\x82\xD5",
	"\x82\xD8", "\x82\xDB", NULL,       NULL,       NULL,       NULL,
	"\x82\xDC", "\x82\xDD", "\x82\xDE", "\x82\xDF", "\x82\xE0", "\x82\x9F",
	"\x82\xA1", "\x82\xA3", "\x82\xA5", "\x82\xA7", NULL,       NULL,
	NULL,       NULL,       "\x82\xE2", "\x81\x40", "\x82\xE4", "\x81\x40",
	"\x82\xE6", "\x82\xE1", "\x82\xE3", "\x82\xE5", "\x82\xC1", "\x89\x4C",
	NULL,       NULL,       NULL,       NULL,       "\x82\xE7", "\x82\xE8",
	"\x82\xE9", "\x82\xEA", "\x82\xEB", "\x81\x7C", "\x81\x60", "\x81\x45",
	"\x81\x44", "\x81\x40", NULL,       NULL,       NULL,       NULL
};
const char* katakana_tbl[] = {
	"\x83\x41", "\x83\x43", "\x83\x45", "\x83\x47", "\x83\x49", "\x83\x8F",
	"\x81\x40", "\x83\x92", "\x81\x40", "\x83\x93", "\x82\x4F", "\x82\x50",
	"\x82\x51", "\x82\x52", "\x83\x4A", "\x83\x4C", "\x83\x4E", "\x83\x50",
	"\x83\x52", "\x83\x4B", "\x83\x4D", "\x83\x4F", "\x83\x51", "\x83\x53",
	"\x82\x53", "\x82\x54", "\x82\x55", "\x82\x56", "\x83\x54", "\x83\x56",
	"\x83\x58", "\x83\x5A", "\x83\x5C", "\x83\x55", "\x83\x57", "\x83\x59",
	"\x83\x5B", "\x83\x5D", "\x82\x57", "\x82\x58", "\x81\x49", "\x81\x48",
	"\x83\x5E", "\x83\x60", "\x83\x63", "\x83\x65", "\x83\x67", "\x83\x5F",
	"\x83\x61", "\x83\x64", "\x83\x66", "\x83\x68", "\x81\x40", "\x94\xB5",
	"\x81\x99", "\x81\xF4", "\x83\x69", "\x83\x6A", "\x83\x6B", "\x83\x6C",
	"\x83\x6D", "\x83\x6F", "\x83\x72", "\x83\x75", "\x83\x78", "\x83\x7B",
	NULL,       NULL,       NULL,       NULL,       "\x83\x6E", "\x83\x71",
	"\x83\x74", "\x83\x77", "\x83\x7A", "\x83\x70", "\x83\x73", "\x83\x76",
	"\x83\x79", "\x83\x7C", NULL,       NULL,       NULL,       NULL,
	"\x83\x7D", "\x83\x7E", "\x83\x80", "\x83\x81", "\x83\x82", "\x83\x40",
	"\x83\x42", "\x83\x44", "\x83\x46", "\x83\x48", NULL,       NULL,
	NULL,       NULL,       "\x83\x84", "\x81\x40", "\x83\x86", "\x81\x40",
	"\x83\x88", "\x83\x83", "\x83\x85", "\x83\x87", "\x83\x62", "\x83\x94",
	NULL,       NULL,       NULL,       NULL,       "\x83\x89", "\x83\x8A",
	"\x83\x8B", "\x83\x8C", "\x83\x8D", "\x81\x7C", "\x81\x60", "\x81\x45",
	"\x81\x44", "\x81\x40", NULL,       NULL,       NULL,       NULL
};

//.bss
static NameEntryWork work;

//.sdata
static const char* msg_tbl[] = {
	"msg_nameent_1",
	"msg_nameent_2",
	"msg_nameent_3",
	"msg_nameent_3",
	"msg_nameent_4"
};
static NameEntryWork* wp = &work;

void nameEntInit(void) {
	memset(wp, 0, sizeof(NameEntryWork));
}

void nameEntReInit(void) {
	wp->field_0x4 = 3;
}

BOOL nameEntPrepare(void) {
	return fileAsyncf(4, NULL, "%s/w/jp/name.tpl", getMarioStDvdRoot()) != 0;
}

void nameEntOn(s32 type) {
	s32 i;

	wp->field_0x0 = 0;
	wp->field_0xC = type;
	wp->field_0x4 = 1;
	wp->field_0x8 = 0;
	wp->field_0x50 = hiragana_tbl;
	wp->field_0x18 = 0;
	wp->field_0x10 = 0;
	wp->field_0x14 = 0;
	wp->x1 = wp->x2 = (f32)(wp->field_0x10 * 24 + (wp->field_0x10 / 5) * 30 - 190);
	wp->y1 = wp->y2 = (f32)(112 - wp->field_0x14 * 28);
	wp->field_0x2C = wp->field_0x34 = -106.0f;
	wp->field_0x30 = wp->field_0x38 = 135.0f;
	strcpy(wp->field_0x3C, "");
	for (i = 0; i < 8; i++) {
		strcat(wp->field_0x3C, "\x81\x40");
	}
	wp->field_0x54 = 0.0f;
	switch (type) {
		case 2:
			hiragana_tbl[9] = "\x81\x40";
			katakana_tbl[9] = "\x81\x40";
			break;
		default:
			hiragana_tbl[9] = "\x82\xF1";
			katakana_tbl[9] = "\x83\x93";
			break;
	}
}

void nameEntOff(void) {
	wp->field_0x4 = 3;
}

BOOL nameEntWait(void) {
	wp->field_0x0 |= 1;
	return wp->field_0x8 != 0x65;
}

BOOL nameEntIsCancel(void) {
	return (wp->field_0x0 >> 1) & 1;
}

const char* nameEntGetName(void) {
	s32 i;

	if (wp->field_0x8 != 0x65) {
		return NULL;
	}
	for (i = 7; i >= 1; i--) {
		if (strncmp(&wp->field_0x3C[i * 2], "\x81\x40", 2)) {
			break;
		}
		wp->field_0x3C[i * 2] = 0;
		wp->field_0x3C[i * 2 + 1] = 0;
	}
	return wp->field_0x3C;
}

static inline BOOL nameEntLoad(void) {
	if (fileAsyncf(4, NULL, "%s/w/jp/name.tpl", getMarioStDvdRoot()) != 0U) {
		wp->field_0x60 = fileAllocf(4, "%s/w/jp/name.tpl", getMarioStDvdRoot());
		return TRUE;
	}
	return FALSE;
}

void nameEntMain(void) {
	switch (wp->field_0x4) {
		case 0:
			break;
		case 1:
			if (nameEntLoad()) {
				wp->field_0x4++;
			}
		case 2:
			nameMain();
			break;
		case 3:
			if (wp->field_0x60) {
				fileFree(wp->field_0x60);
			}
			wp->field_0x60 = NULL;
			wp->field_0x4 = 0;
			break;
	}
	if (wp->field_0x4 > 1) {
		dispEntry(CAMERA_3D, 0.0f, 7, nameEntDisp, NULL);
	}
}

s32 nameMain(void) {
	s32 len;
	s32 i;
	s32 off;
	s32 idx;
	f32 dist;

	dist = distABf(wp->x2, wp->y2, wp->x1, wp->y1);
	switch (wp->field_0x8) {
		case 0:
			if ((wp->field_0x0 & 1) && gp->unk8 == 0) {
				if (keyGetButtonTrg(0) & 0x100) {
					if (wp->field_0x10 >= 10 && wp->field_0x14 >= 4) {
						switch (wp->field_0x14) {
							case 4:
								wp->field_0x50 = hiragana_tbl;
								psndSFXOn((const char*)0x2000C);
								break;
							case 5:
								wp->field_0x50 = katakana_tbl;
								psndSFXOn((const char*)0x2000C);
								break;
							case 6:
								if (wp->field_0x18 > 0) {
									wp->field_0x18--;
									psndSFXOn((const char*)0x2000B);
								}
								break;
							case 7:
								len = strlen(wp->field_0x3C) / 2;
								for (i = 0; i < len; i++) {
									if (strncmp(&wp->field_0x3C[i * 2], "\x81\x40", 2)) {
										break;
									}
								}
								if (i < len || wp->field_0xC != 0) {
									wp->field_0x5C = 1;
									wp->field_0x8 = 100;
									psndSFXOn((const char*)0x20012);
									if (wp->field_0xC == 1 && i >= len) {
										strcpy(wp->field_0x3C, msgSearch("name_party3"));
										wp->field_0x18 = strlen(wp->field_0x3C) / 2;
									}
								} else {
									psndSFXOn((const char*)0x20014);
								}
								break;
						}
					} else if (wp->field_0x18 < 8) {
						((u16*)wp->field_0x3C)[wp->field_0x18] = *(u16*)wp->field_0x50[wp->field_0x14 * 14 + wp->field_0x10];
						wp->field_0x18++;
						if (wp->field_0x18 >= 8) {
							wp->field_0x18 = 7;
							wp->field_0x10 = 10;
							wp->field_0x14 = 7;
						}
						psndSFXOn((const char*)0xA);
					} else if (wp->field_0x18 == 8) {
						wp->field_0x18 = 7;
						((u16*)wp->field_0x3C)[wp->field_0x18] = *(u16*)wp->field_0x50[wp->field_0x14 * 14 + wp->field_0x10];
						wp->field_0x10 = 10;
						wp->field_0x14 = 7;
						psndSFXOn((const char*)0xA);
					}
				} else if (keyGetButtonTrg(0) & 0x1000) {
					len = strlen(wp->field_0x3C) / 2;
					for (i = 0; i < len; i++) {
						if (strncmp(&wp->field_0x3C[i * 2], "\x81\x40", 2)) {
							break;
						}
					}
					if (i < len || wp->field_0xC != 0) {
						wp->field_0x5C = 1;
						wp->field_0x8 = 100;
						psndSFXOn((const char*)0x12);
						if (wp->field_0xC == 1 && i >= len) {
							strcpy(wp->field_0x3C, msgSearch("name_party3"));
							wp->field_0x18 = strlen(wp->field_0x3C) / 2;
						}
					} else {
						psndSFXOn((const char*)0x20014);
					}
				} else if (keyGetButtonTrg(0) & 0x200) {
					if (wp->field_0x18 == 0 && wp->field_0xC == 0 && !strncmp(wp->field_0x3C, "\x81\x40", 2)) {
						psndSFXOn((const char*)0x13);
						wp->field_0x8 = 0x65;
						wp->field_0x0 |= 2;
					} else {
						((u16*)wp->field_0x3C)[wp->field_0x18] = *(u16*)"\x81\x40";
						wp->field_0x18--;
						if (wp->field_0x18 < 0) {
							wp->field_0x18 = 0;
						}
						psndSFXOn((const char*)0xB);
					}
				} else if (keyGetDirRep(0) & 0x4000) {
					if (dist < 10.0f) {
						wp->field_0x10--;
						if (wp->field_0x14 > 3) {
							if (wp->field_0x10 < 0) {
								wp->field_0x10 = 10;
								if (wp->field_0x14 > 7) {
									wp->field_0x14 = 7;
								}
							}
						} else if (wp->field_0x10 < 0) {
							wp->field_0x10 = 13;
						}
						psndSFXOn((const char*)5);
					}
				} else if (keyGetDirRep(0) & 0x8000) {
					if (dist < 10.0f) {
						wp->field_0x10++;
						if (wp->field_0x14 > 3) {
							if (wp->field_0x10 >= 10 && wp->field_0x14 > 7) {
								wp->field_0x14 = 7;
							}
							if (wp->field_0x10 >= 11) {
								wp->field_0x10 = 0;
							}
						} else if (wp->field_0x10 >= 14) {
							wp->field_0x10 = 0;
						}
						psndSFXOn((const char*)5);
					}
				} else if (keyGetDirRep(0) & 0x1000) {
					if (dist < 10.0f) {
						wp->field_0x14--;
						if (wp->field_0x14 < 0) {
							if (wp->field_0x10 > 9) {
								wp->field_0x14 = 7;
								wp->field_0x10 = 10;
							} else {
								wp->field_0x14 = 8;
							}
						}
						psndSFXOn((const char*)5);
					}
				} else if (keyGetDirRep(0) & 0x2000) {
					if (dist < 10.0f) {
						wp->field_0x14++;
						if (wp->field_0x10 > 9) {
							if (wp->field_0x14 >= 4) {
								wp->field_0x10 = 10;
							}
							if (wp->field_0x14 >= 8) {
								wp->field_0x14 = 0;
							}
						} else if (wp->field_0x14 >= 9) {
							wp->field_0x14 = 0;
						}
						psndSFXOn((const char*)5);
					}
				}
			}
			if (wp->field_0x10 > 9 && wp->field_0x14 > 3) {
				wp->x2 = 100.0f;
				wp->y2 = (f32)(-20 - (wp->field_0x14 - 4) * 34);
				wp->x2 -= 6.0f;
				wp->y2 += 6.0f;
			} else {
				wp->x2 = (f32)(wp->field_0x10 * 24 + (wp->field_0x10 / 5) * 30 - 190);
				wp->y2 = (f32)(112 - wp->field_0x14 * 28);
				wp->x2 -= 16.0f;
				wp->y2 -= 12.0f;
			}
			wp->field_0x54 -= 0.05f;
			if (wp->field_0x54 <= 0.0f) {
				wp->field_0x54 = 0.0f;
			}
			break;
		case 100:
			if (keyGetButtonTrg(0) & 0x100) {
				if (wp->field_0x5C == 0) {
					wp->field_0x8++;
					psndSFXOn((const char*)0x12);
				} else {
					wp->field_0x8 = 0;
					psndSFXOn((const char*)0x13);
				}
			} else if (keyGetButtonTrg(0) & 0x200) {
				wp->field_0x8 = 0;
				psndSFXOn((const char*)0x13);
			} else if (keyGetDirRep(0) & 0x3000) {
				wp->field_0x5C = 1 - wp->field_0x5C;
				psndSFXOn((const char*)5);
			}
			wp->x2 = -60.0f;
			wp->y2 = -30.0f - 40.0f * (f32)wp->field_0x5C;
			wp->field_0x54 += 0.05f;
			if (wp->field_0x54 >= 1.0f) {
				wp->field_0x54 = 1.0f;
			}
			break;
	}
	wp->x1 = (wp->x2 - wp->x1) * 0.25f + wp->x1;
	wp->y1 = (wp->y2 - wp->y1) * 0.25f + wp->y1;
	wp->x1 = wp->x1 + __fabs(2.0f * (f32)sin(gp->retraceCount * 0.125f));
	idx = wp->field_0x18;
	if (idx >= 8) {
		idx--;
	}
	wp->field_0x34 = (f32)(idx * 32 - 106);
	wp->field_0x38 = 135.0f;
	wp->field_0x2C = (wp->field_0x34 - wp->field_0x2C) * 0.25f + wp->field_0x2C;
	wp->field_0x30 = (wp->field_0x38 - wp->field_0x30) * 0.25f + wp->field_0x30;
	wp->field_0x30 = wp->field_0x30 + __fabs(2.0f * (f32)sin(gp->retraceCount * 0.125f));
	return 0;
}

void nameEntDisp(CameraId cameraId, void* param) {
	GXColor unused = {0xFF, 0xFF, 0xFF, 0xFF};
	GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
	GXColor white2 = {0xFF, 0xFF, 0xFF, 0xFF};
	CameraEntry saved;
	f32 proj[7];
	f32 vp[6];
	char buf[16];
	CameraEntry* cam;
	const char* str;
	const char* ok;
	const char* yes;
	const char* no;
	s32 i, j;
	u16 width;
	f32 w;

	saved = *camGetCurPtr();
	GXGetProjectionv(proj);
	GXGetViewportv(vp);
	cam = camGetPtr(CAMERA_2D);
	*camGetCurPtr() = *cam;
	cam = camGetPtr(CAMERA_2D);
	GXSetProjection(camGetPtr(CAMERA_2D)->projection, cam->projType);
	nameBG();
	winTexInit(*wp->field_0x60->data);
	winTexSet(0x2a, (Vec){-130.0f, 160.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
	for (i = 0; i < 8; i++) {
		winTexSet(0x29, (Vec){(f32)(i * 32 - 106), 160.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white2);
	}
	winTexSet(0x2b, (Vec){142.0f, 160.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
	nameKirinukiGX(-240.0f, 120.0f, 480.0f, 270.0f);
	FontDrawStart();
	for (j = 0; j < 9; j++) {
		for (i = 0; i < 14; i++) {
			str = wp->field_0x50[j * 14 + i];
			if (str) {
				width = FontGetMessageWidth(str);
				FontDrawString((f32)(i * 24 - 190 + ((i / 5) * 30 + (24 - width) / 2)), (f32)(112 - j * 28), str);
			}
		}
	}
	for (i = 0; i < 4; i++) {
		if (wp->field_0x10 >= 10 && wp->field_0x14 - 4 == i) {
			winTexInit(*wp->field_0x60->data);
			winTexSet(0x33, (Vec){160.0f, (f32)(-20 - i * 34), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 0x40});
			winTexInit_x2(*wp->field_0x60->data);
			winTexSet_x2(i + 0x25, 0x33, (Vec){154.0f, (f32)(-14 - i * 34), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white2);
		} else {
			winTexInit_x2(*wp->field_0x60->data);
			winTexSet_x2(i + 0x25, 0x33, (Vec){160.0f, (f32)(-20 - i * 34), 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white2);
		}
	}
	winTexInit(*wp->field_0x60->data);
	winTexSet(0x24, (Vec){2.0f + wp->field_0x2C, wp->field_0x30 - 2.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 0x80});
	winTexSet(0x24, (Vec){wp->field_0x2C, wp->field_0x30, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
	FontDrawStart();
	for (i = 0; i < 8; i++) {
		memset(buf, 0, sizeof(buf));
		strncpy(buf, &wp->field_0x3C[i * 2], 2);
		if (strlen(buf)) {
			width = FontGetMessageWidth(buf);
			FontDrawString((28.0f - width) * 0.5f + (f32)(i * 32 - 120), 171.0f, buf);
		}
	}
	str = msg_tbl[wp->field_0xC];
	w = FontGetMessageWidth(msgSearch(str));
	windowDispGX_Waku_col(0, (GXColor){0xFF, 0xFF, 0xFF, 0xFF}, -250.0f, -160.0f, 500.0f, 40.0f, 20.0f);
	FontDrawStart();
	FontDrawString((240.0f - w) * 0.5f + -120.0f, -168.0f, msgSearch(str));
	nameMaskGX(wp->field_0x54);
	if (wp->field_0x8 == 100) {
		ok = msgSearch("msg_nameent_ok");
		yes = msgSearch("msg_nameent_yes");
		no = msgSearch("msg_nameent_no");
		if (wp->field_0xC == 4) {
			ok = msgSearch("msg_nameent_ok_01");
		}
		nameWinGX(*wp->field_0x60->data, 1, -180.0f, 130.0f, 360.0f, 100.0f);
		nameWinGX(*wp->field_0x60->data, 1, -80.0f, 10.0f, 160.0f, 120.0f);
		FontDrawStart();
		FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
		FontDrawEdge();
		FontDrawString(-(f32)FontGetMessageWidth(ok) * 0.5f, 110.0f, ok);
		FontDrawString(-(f32)FontGetMessageWidth(wp->field_0x3C) * 0.5f, 70.0f, wp->field_0x3C);
		FontDrawString(-(f32)FontGetMessageWidth(no) * 0.5f, -20.0f, yes);
		FontDrawString(-(f32)FontGetMessageWidth(no) * 0.5f, -60.0f, no);
		FontDrawEdgeOff();
	}
	winTexInit(*wp->field_0x60->data);
	winTexSet(0, (Vec){2.0f + wp->x1, wp->y1 - 2.0f, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, (GXColor){0, 0, 0, 0x80});
	winTexSet(0, (Vec){wp->x1, wp->y1, 0.0f}, (Vec){1.0f, 1.0f, 1.0f}, white);
	*camGetCurPtr() = saved;
	GXSetProjectionv(proj);
	GXSetViewport(vp[0], vp[1], vp[2], vp[3], vp[4], vp[5]);
}

void nameBG(void) {
	Mtx m1, m2, m3;
	GXTexObj obj1, obj2, obj3;
	f32 sy;
	double h1, w1, h2, w2, h3, w3;

	GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
	GXSetZCompLoc(GX_FALSE);
	GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
	GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
	GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){0xFF, 0xFF, 0xFF, 0xFF});
	GXSetNumChans(0);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
	GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
	GXSetCullMode(GX_CULL_NONE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GXLoadPosMtxImm(camGetPtr(CAMERA_2D)->view, GX_PNMTX0);
	GXSetCurrentMtx(GX_PNMTX0);

	TEXGetGXTexObjFromPalette(*wp->field_0x60->data, &obj1, 0x22);
	GXInitTexObjLOD(&obj1, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	GXLoadTexObj(&obj1, GX_TEXMAP0);
	GXSetNumTexGens(1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	h1 = __fabs(480.0);
	w1 = __fabs(32.0);
	sy = (f32)h1 / GXGetTexObjHeight(&obj1);
	PSMTXScale(m1, (f32)w1 / GXGetTexObjWidth(&obj1), sy, 1.0f);
	GXLoadTexMtxImm(m1, GX_TEXMTX0, GX_MTX2x4);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition3f32(-304.0f, 240.0f, 0.0f);
	GXTexCoord2f32(0.0f, 0.0f);
	GXPosition3f32(-304.0f, -240.0f, 0.0f);
	GXTexCoord2f32(0.0f, 1.0f);
	GXPosition3f32(-272.0f, -240.0f, 0.0f);
	GXTexCoord2f32(1.0f, 1.0f);
	GXPosition3f32(-272.0f, 240.0f, 0.0f);
	GXTexCoord2f32(1.0f, 0.0f);

	TEXGetGXTexObjFromPalette(*wp->field_0x60->data, &obj2, 0x21);
	GXInitTexObjLOD(&obj2, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	GXLoadTexObj(&obj2, GX_TEXMAP0);
	GXSetNumTexGens(1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	h2 = __fabs(480.0);
	w2 = __fabs(544.0);
	sy = (f32)h2 / GXGetTexObjHeight(&obj2);
	PSMTXScale(m2, (f32)w2 / GXGetTexObjWidth(&obj2), sy, 1.0f);
	GXLoadTexMtxImm(m2, GX_TEXMTX0, GX_MTX2x4);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition3f32(-272.0f, 240.0f, 0.0f);
	GXTexCoord2f32(0.0f, 0.0f);
	GXPosition3f32(-272.0f, -240.0f, 0.0f);
	GXTexCoord2f32(0.0f, 1.0f);
	GXPosition3f32(272.0f, -240.0f, 0.0f);
	GXTexCoord2f32(1.0f, 1.0f);
	GXPosition3f32(272.0f, 240.0f, 0.0f);
	GXTexCoord2f32(1.0f, 0.0f);

	TEXGetGXTexObjFromPalette(*wp->field_0x60->data, &obj3, 0x23);
	GXInitTexObjLOD(&obj3, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	GXLoadTexObj(&obj3, GX_TEXMAP0);
	GXSetNumTexGens(1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	h3 = __fabs(480.0);
	w3 = __fabs(32.0);
	sy = (f32)h3 / GXGetTexObjHeight(&obj3);
	PSMTXScale(m3, (f32)w3 / GXGetTexObjWidth(&obj3), sy, 1.0f);
	GXLoadTexMtxImm(m3, GX_TEXMTX0, GX_MTX2x4);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition3f32(272.0f, 240.0f, 0.0f);
	GXTexCoord2f32(0.0f, 0.0f);
	GXPosition3f32(272.0f, -240.0f, 0.0f);
	GXTexCoord2f32(0.0f, 1.0f);
	GXPosition3f32(304.0f, -240.0f, 0.0f);
	GXTexCoord2f32(1.0f, 1.0f);
	GXPosition3f32(304.0f, 240.0f, 0.0f);
	GXTexCoord2f32(1.0f, 0.0f);
}

#pragma inline_max_total_size(100000)
static inline void nameTexQuad(s32 id, f32 x, f32 y, f32 w, f32 h) {
	GXTexObj obj;
	Mtx m;
	f32 sy;
	double ah;
	double aw;

	TEXGetGXTexObjFromPalette(*wp->field_0x60->data, &obj, id);
	GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	GXLoadTexObj(&obj, GX_TEXMAP0);
	GXSetNumTexGens(1);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	ah = __fabs(h);
	aw = __fabs(w);
	sy = (f32)ah / GXGetTexObjHeight(&obj);
	PSMTXScale(m, (f32)aw / GXGetTexObjWidth(&obj), sy, 1.0f);
	GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition3f32(x, y, 0.0f);
	GXTexCoord2f32(0.0f, 0.0f);
	GXPosition3f32(x, y - h, 0.0f);
	GXTexCoord2f32(0.0f, 1.0f);
	GXPosition3f32(x + w, y - h, 0.0f);
	GXTexCoord2f32(1.0f, 1.0f);
	GXPosition3f32(x + w, y, 0.0f);
	GXTexCoord2f32(1.0f, 0.0f);
}

void nameKirinukiGX(f32 x, f32 y, f32 w, f32 h) {
	GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
	GXSetZCompLoc(GX_FALSE);
	GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
	GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
	GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
	GXSetNumChans(0);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
	GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
	GXSetCullMode(GX_CULL_NONE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GXLoadPosMtxImm(camGetPtr((CameraId)8)->view, 0);
	GXSetCurrentMtx(0);
	nameTexQuad(0x2F, x, y, 8, 8);
	nameTexQuad(0x2D, x + 8, y, w - 8 - 8, 8);
	nameTexQuad(0x31, x + w - 8, y, 8, 8);
	nameTexQuad(0x2E, x, y - 8, 8, h - 8 - 8);
	nameTexQuad(0x2C, x + 8, y - 8, w - 8, h - 8 - 8);
	nameTexQuad(0x30, x, y - (h - 8), 8, 8);
	nameTexQuad(0x2C, x + 8, y - (h - 8), w - 8 - 8, 8);
	nameTexQuad(0x32, x + w - 8, y - (h - 8), 8, 8);
}

void nameMaskGX(f32 t) {
	Mtx a, b, c;
	GXTexObj obj;
	f32 s;

	s = t * (t * (t * (1000.0f * t * t)));
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
	GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
	GXSetNumChans(0);
	GXSetNumTevStages(1);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
	GXSetTevColor(GX_TEVREG0, (GXColor){0, 0, 0, 0x80});
	TEXGetGXTexObjFromPalette(fadeGetTpl(), &obj, 1);
	GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	GXLoadTexObj(&obj, GX_TEXMAP0);
	GXSetNumTexGens(1);
	PSMTXTrans(a, 0.5f, 0.5f, 0.0f);
	PSMTXScale(b, s, s, 0.0f);
	PSMTXTrans(c, -0.5f, -0.5f, 0.0f);
	PSMTXConcat(a, b, a);
	PSMTXConcat(a, c, a);
	GXLoadTexMtxImm(a, GX_TEXMTX0, GX_MTX2x4);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	GXSetCullMode(GX_CULL_NONE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GXLoadPosMtxImm(camGetPtr(CAMERA_2D)->view, GX_PNMTX0);
	GXSetCurrentMtx(GX_PNMTX0);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition3s16(-304, 240, 0);
	GXTexCoord2f32(0.0f, 0.0f);
	GXPosition3s16(304, 240, 0);
	GXTexCoord2f32(1.0f, 0.0f);
	GXPosition3s16(304, -240, 0);
	GXTexCoord2f32(1.0f, 1.0f);
	GXPosition3s16(-304, -240, 0);
	GXTexCoord2f32(0.0f, 1.0f);
}

static inline void nameWinQuad(TEXPalette* tpl, s32 a, s32 b, s32 c, f32 x, f32 y, f32 w, f32 h) {
	GXTexObj obj;
	Mtx m;
	double ah;
	double aw;

	GXSetNumTexGens(2);
	TEXGetGXTexObjFromPalette(tpl, &obj, a);
	GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	GXLoadTexObj(&obj, GX_TEXMAP0);
	GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
	ah = __fabs(h);
	aw = __fabs(w);
	PSMTXScale(m, (f32)aw / GXGetTexObjWidth(&obj), (f32)ah / GXGetTexObjHeight(&obj), 1.0f);
	GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
	TEXGetGXTexObjFromPalette(tpl, &obj, b);
	GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	GXLoadTexObj(&obj, GX_TEXMAP1);
	TEXGetGXTexObjFromPalette(tpl, &obj, c);
	GXInitTexObjLOD(&obj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
	GXLoadTexObj(&obj, GX_TEXMAP2);
	GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
	ah = __fabs(h);
	aw = __fabs(w);
	PSMTXScale(m, (f32)aw / GXGetTexObjWidth(&obj), (f32)ah / GXGetTexObjHeight(&obj), 1.0f);
	GXLoadTexMtxImm(m, GX_TEXMTX1, GX_MTX2x4);
	GXBegin(GX_QUADS, GX_VTXFMT0, 4);
	GXPosition3f32(x, y, 0.0f);
	GXTexCoord2f32(0.0f, 0.0f);
	GXPosition3f32(x, y - h, 0.0f);
	GXTexCoord2f32(0.0f, 1.0f);
	GXPosition3f32(x + w, y - h, 0.0f);
	GXTexCoord2f32(1.0f, 1.0f);
	GXPosition3f32(x + w, y, 0.0f);
	GXTexCoord2f32(1.0f, 0.0f);
}

void nameWinGX(TEXPalette* tpl, s32 type, f32 x, f32 y, f32 w, f32 h) {
	GXSetZCompLoc(GX_TRUE);
	GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
	GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
	GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
	GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
	GXSetNumChans(0);
	GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
	GXSetNumTevStages(3);
	GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
	GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
	GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
	GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
	GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
	GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
	GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
	GXSetTevColor(GX_TEVREG0, (GXColor){ 0, 0, 0, 0x80 });
	GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
	GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP2, GX_COLOR_NULL);
	GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
	GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_CPREV, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
	GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_APREV, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
	GXSetTevKAlphaSel(GX_TEVSTAGE2, 0);
	GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
	GXSetCullMode(GX_CULL_NONE);
	GXClearVtxDesc();
	GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
	GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
	GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
	GXLoadPosMtxImm(camGetPtr((CameraId)8)->view, 0);
	GXSetCurrentMtx(0);
	nameWinQuad(tpl, type + 4, type + 5, type, x, y, w - 16, h - 16);
	nameWinQuad(tpl, type + 4, type + 7, type + 2, x + w - 16, y, 16, h - 16);
	nameWinQuad(tpl, type + 4, type + 6, type + 1, x, y - h + 16, w - 16, 16);
	nameWinQuad(tpl, type + 4, type + 8, type + 3, x + w - 16, y - h + 16, 16, 16);
}
