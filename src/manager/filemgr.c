#include "manager/filemgr.h"
#include "dolphin/os.h"
#include "driver/arcdrv.h"
#include "memory.h"
#include "sdk/texPalette.h"
#include <stdarg.h>
#include <string.h>

extern int vsprintf(char* string, const char* format, va_list arg);
extern OSThread dvdmgr_thread;

//.bss
char _filename[0x400]; //for fileAllocf/fileAsyncf vsprintf

//.sbss
FileManagerWork fileWork;

//.sdata
FileManagerWork* afp = &fileWork;
#pragma push
#pragma force_active on
static __declspec(section ".sdata") u32 gap_07_804125DC_sdata[1] = {0};
#pragma pop

//local prototypes
void fileGarbageDataAdrClear(FileEntry* entry);
void fileGarbageDataAdrSet(void* data, s32 type);
FileEntry* _fileAlloc(const char* filename, s32 type, void (*callback)(FileEntry*));
void dvdReadDoneCallBack(s32 error, DVDFileInfo* info);
s32 fileAsync(const char* filename, s32 type, FileCallback callback);




void fileInit(void) {
	FileEntry* ptr;
	int i;

	afp->entries = __memAlloc(HEAP_DEFAULT, sizeof(FileEntry) * 0x400);
	afp->archiveType = 0;
	afp->firstused = 0;
	afp->lastused = 0;
	memset(afp->entries, 0, sizeof(FileEntry) * 0x400);

	for (ptr = afp->entries, i = 0; i < 0x400; i++, ptr++) {
		ptr->next = ptr + 1;
	}

	afp->firstavailable = afp->entries;
	afp->lastavailable = &afp->entries[0x3FF];
	afp->lastavailable->next = NULL;
}

#define FLD(b, o) (*(u32*)((u8*)(b) + (o)))
typedef struct Anim40 {
	u8 pad[0x3c];
	u8* p;
} Anim40;

void fileGarbageDataAdrClear(FileEntry* entry) {
	u16 i;
	TEXHeader* img;
	CLUTHeader* pal;
	TEXPalette* tpl;
	s32 j, n;
	Anim40* e;
	u8* q;
	void* data = *entry->data;
	switch (entry->field_0x1) {
		case 1:
			if (FLD(data, 0x14c) >= (u32)data) {
				FLD(data, 0x14c) -= (u32)data;
				FLD(data, 0x150) -= (u32)data;
				FLD(data, 0x154) -= (u32)data;
				FLD(data, 0x158) -= (u32)data;
				FLD(data, 0x15c) -= (u32)data;
				FLD(data, 0x160) -= (u32)data;
				FLD(data, 0x164) -= (u32)data;
				FLD(data, 0x168) -= (u32)data;
				FLD(data, 0x16c) -= (u32)data;
				FLD(data, 0x170) -= (u32)data;
				FLD(data, 0x174) -= (u32)data;
				FLD(data, 0x178) -= (u32)data;
				FLD(data, 0x17c) -= (u32)data;
				FLD(data, 0x180) -= (u32)data;
				FLD(data, 0x184) -= (u32)data;
				FLD(data, 0x188) -= (u32)data;
				FLD(data, 0x18c) -= (u32)data;
				FLD(data, 0x190) -= (u32)data;
				FLD(data, 0x194) -= (u32)data;
				FLD(data, 0x198) -= (u32)data;
				FLD(data, 0x19c) -= (u32)data;
				FLD(data, 0x1a0) -= (u32)data;
				FLD(data, 0x1a4) -= (u32)data;
				FLD(data, 0x1a8) -= (u32)data;
				FLD(data, 0x1ac) -= (u32)data;
			}
			break;
		case 2:
			if (FLD(data, 0x24) >= (u32)data) {
				FLD(data, 0x24) -= (u32)data;
				FLD(data, 0x28) -= (u32)data;
				FLD(data, 0x2c) -= (u32)data;
				FLD(data, 0x30) -= (u32)data;
				FLD(data, 0x34) -= (u32)data;
				FLD(data, 0x38) -= (u32)data;
				FLD(data, 0x3c) -= (u32)data;
				FLD(data, 0x40) -= (u32)data;
			}
			break;
		case 3:
			if (FLD(data, 0x48) >= (u32)data) {
				FLD(data, 0x48) -= (u32)data;
			}
			break;
		case 4:
			tpl = data;
			if (tpl->versionNumber != 0x0020AF30) {
				OSPanic("filemgr.c", 147, "invalid version number for texture palette\0");
			}
			if ((u32)tpl->descriptorArray >= (u32)tpl) {
				for (i = 0; i < tpl->numDescriptors; i++) {
					img = tpl->descriptorArray[i].textureHeader;
					if (img) {
						if (img->unpacked) {
							img->unpacked = FALSE;
							*(u32*)&tpl->descriptorArray[i].textureHeader->data -= (u32)tpl;
						}
						*(u32*)&tpl->descriptorArray[i].textureHeader -= (u32)tpl;
					}
					pal = tpl->descriptorArray[i].CLUTHeader;
					if (pal) {
						if (pal->unpacked) {
							pal->unpacked = FALSE;
							*(u32*)&tpl->descriptorArray[i].CLUTHeader->data -= (u32)tpl;
						}
						*(u32*)&tpl->descriptorArray[i].CLUTHeader -= (u32)tpl;
					}
				}
				*(u32*)&tpl->descriptorArray -= (u32)tpl;
			}
			break;
		case 5:
			if (FLD(data, 0x14c) >= (u32)data) {
				n = *(s32*)((u8*)data + 0x148);
				for (j = 0; j < n; j++) {
					e = &(*(Anim40**)((u8*)data + 0x1ac))[j];
					q = e->p;
					e->p = q - (u32)data;
					if (FLD(q, 0x24) >= (u32)q) {
						FLD(q, 0x24) -= (u32)q;
						FLD(q, 0x28) -= (u32)q;
						FLD(q, 0x2c) -= (u32)q;
						FLD(q, 0x30) -= (u32)q;
						FLD(q, 0x34) -= (u32)q;
						FLD(q, 0x38) -= (u32)q;
						FLD(q, 0x3c) -= (u32)q;
						FLD(q, 0x40) -= (u32)q;
					}
				}
				FLD(data, 0x14c) -= (u32)data;
				FLD(data, 0x150) -= (u32)data;
				FLD(data, 0x154) -= (u32)data;
				FLD(data, 0x158) -= (u32)data;
				FLD(data, 0x15c) -= (u32)data;
				FLD(data, 0x160) -= (u32)data;
				FLD(data, 0x164) -= (u32)data;
				FLD(data, 0x168) -= (u32)data;
				FLD(data, 0x16c) -= (u32)data;
				FLD(data, 0x170) -= (u32)data;
				FLD(data, 0x174) -= (u32)data;
				FLD(data, 0x178) -= (u32)data;
				FLD(data, 0x17c) -= (u32)data;
				FLD(data, 0x180) -= (u32)data;
				FLD(data, 0x184) -= (u32)data;
				FLD(data, 0x188) -= (u32)data;
				FLD(data, 0x18c) -= (u32)data;
				FLD(data, 0x190) -= (u32)data;
				FLD(data, 0x194) -= (u32)data;
				FLD(data, 0x198) -= (u32)data;
				FLD(data, 0x19c) -= (u32)data;
				FLD(data, 0x1a0) -= (u32)data;
				FLD(data, 0x1a4) -= (u32)data;
				FLD(data, 0x1a8) -= (u32)data;
				FLD(data, 0x1ac) -= (u32)data;
			}
			break;
		case 6:
			if (FLD(data, 0x48) >= (u32)data) {
				FLD(data, 0x48) -= (u32)data;
			}
			break;
		case 7:
			if (FLD(data, 0x64) >= (u32)data) {
				FLD(data, 0x64) -= (u32)data;
				FLD(data, 0x68) -= (u32)data;
				FLD(data, 0x6c) -= (u32)data;
			}
			break;
		case 8:
			if (FLD(data, 0xc8) >= (u32)data) {
				FLD(data, 0xc8) -= (u32)data;
				FLD(data, 0xcc) -= (u32)data;
				FLD(data, 0xd0) -= (u32)data;
				FLD(data, 0xd4) -= (u32)data;
				FLD(data, 0xd8) -= (u32)data;
				FLD(data, 0xdc) -= (u32)data;
				FLD(data, 0xe0) -= (u32)data;
				FLD(data, 0xe4) -= (u32)data;
				FLD(data, 0xe8) -= (u32)data;
				FLD(data, 0xec) -= (u32)data;
				FLD(data, 0xf0) -= (u32)data;
				FLD(data, 0xf4) -= (u32)data;
				FLD(data, 0xf8) -= (u32)data;
				FLD(data, 0xfc) -= (u32)data;
				FLD(data, 0x100) -= (u32)data;
				FLD(data, 0x104) -= (u32)data;
				FLD(data, 0x108) -= (u32)data;
				FLD(data, 0x10c) -= (u32)data;
				FLD(data, 0x110) -= (u32)data;
				FLD(data, 0x114) -= (u32)data;
				FLD(data, 0x118) -= (u32)data;
				FLD(data, 0x11c) -= (u32)data;
				FLD(data, 0x120) -= (u32)data;
			}
			break;
		case 9:
			if (FLD(data, 0x58) >= (u32)data) {
				FLD(data, 0x58) -= (u32)data;
				FLD(data, 0x5c) -= (u32)data;
				FLD(data, 0x60) -= (u32)data;
				FLD(data, 0x64) -= (u32)data;
			}
			break;
		case 10:
			if (FLD(data, 0x48) >= (u32)data) {
				FLD(data, 0x48) -= (u32)data;
			}
			break;
		case 0:
		default:
			break;
	}
}

void fileGarbageDataAdrSet(void* data, s32 type) {
	u8* q;
	s32 j, n;
	TEXPalette* tpl;
	switch (type) {
		case 1:
			if (FLD(data, 0x14c) < (u32)data) {
				FLD(data, 0x14c) += (u32)data;
				FLD(data, 0x150) += (u32)data;
				FLD(data, 0x154) += (u32)data;
				FLD(data, 0x158) += (u32)data;
				FLD(data, 0x15c) += (u32)data;
				FLD(data, 0x160) += (u32)data;
				FLD(data, 0x164) += (u32)data;
				FLD(data, 0x168) += (u32)data;
				FLD(data, 0x16c) += (u32)data;
				FLD(data, 0x170) += (u32)data;
				FLD(data, 0x174) += (u32)data;
				FLD(data, 0x178) += (u32)data;
				FLD(data, 0x17c) += (u32)data;
				FLD(data, 0x180) += (u32)data;
				FLD(data, 0x184) += (u32)data;
				FLD(data, 0x188) += (u32)data;
				FLD(data, 0x18c) += (u32)data;
				FLD(data, 0x190) += (u32)data;
				FLD(data, 0x194) += (u32)data;
				FLD(data, 0x198) += (u32)data;
				FLD(data, 0x19c) += (u32)data;
				FLD(data, 0x1a0) += (u32)data;
				FLD(data, 0x1a4) += (u32)data;
				FLD(data, 0x1a8) += (u32)data;
				FLD(data, 0x1ac) += (u32)data;
			}
			break;
		case 2:
			if (FLD(data, 0x24) < (u32)data) {
				FLD(data, 0x24) += (u32)data;
				FLD(data, 0x28) += (u32)data;
				FLD(data, 0x2c) += (u32)data;
				FLD(data, 0x30) += (u32)data;
				FLD(data, 0x34) += (u32)data;
				FLD(data, 0x38) += (u32)data;
				FLD(data, 0x3c) += (u32)data;
				FLD(data, 0x40) += (u32)data;
			}
			break;
		case 3:
			if (FLD(data, 0x48) < (u32)data) {
				FLD(data, 0x48) += (u32)data;
			}
			break;
		case 4:
			tpl = data;
			if (tpl->versionNumber != 0x0020AF30) {
				OSPanic("filemgr.c", 106, "invalid version number for texture palette\0");
			}
			if ((u32)tpl->descriptorArray < (u32)tpl) {
				u16 i;
				*(u32*)&tpl->descriptorArray += (u32)tpl;
				for (i = 0; i < tpl->numDescriptors; i++) {
					TEXHeader* img;
					CLUTHeader* pal;
					img = tpl->descriptorArray[i].textureHeader;
					if (img) {
						tpl->descriptorArray[i].textureHeader = (TEXHeader*)((u32)tpl + (u32)img);
						if (!tpl->descriptorArray[i].textureHeader->unpacked) {
							tpl->descriptorArray[i].textureHeader->data = (char*)((u32)tpl + (u32)tpl->descriptorArray[i].textureHeader->data);
							tpl->descriptorArray[i].textureHeader->unpacked = TRUE;
						}
					}
					pal = tpl->descriptorArray[i].CLUTHeader;
					if (pal) {
						tpl->descriptorArray[i].CLUTHeader = (CLUTHeader*)((u32)tpl + (u32)pal);
						if (!tpl->descriptorArray[i].CLUTHeader->unpacked) {
							tpl->descriptorArray[i].CLUTHeader->data = (char*)((u32)tpl + (u32)tpl->descriptorArray[i].CLUTHeader->data);
							tpl->descriptorArray[i].CLUTHeader->unpacked = TRUE;
						}
					}
				}
			}
			break;
		case 5:
			if (FLD(data, 0x14c) < (u32)data) {
				FLD(data, 0x14c) += (u32)data;
				FLD(data, 0x150) += (u32)data;
				FLD(data, 0x154) += (u32)data;
				FLD(data, 0x158) += (u32)data;
				FLD(data, 0x15c) += (u32)data;
				FLD(data, 0x160) += (u32)data;
				FLD(data, 0x164) += (u32)data;
				FLD(data, 0x168) += (u32)data;
				FLD(data, 0x16c) += (u32)data;
				FLD(data, 0x170) += (u32)data;
				FLD(data, 0x174) += (u32)data;
				FLD(data, 0x178) += (u32)data;
				FLD(data, 0x17c) += (u32)data;
				FLD(data, 0x180) += (u32)data;
				FLD(data, 0x184) += (u32)data;
				FLD(data, 0x188) += (u32)data;
				FLD(data, 0x18c) += (u32)data;
				FLD(data, 0x190) += (u32)data;
				FLD(data, 0x194) += (u32)data;
				FLD(data, 0x198) += (u32)data;
				FLD(data, 0x19c) += (u32)data;
				FLD(data, 0x1a0) += (u32)data;
				FLD(data, 0x1a4) += (u32)data;
				FLD(data, 0x1a8) += (u32)data;
				FLD(data, 0x1ac) += (u32)data;
				n = *(s32*)((u8*)data + 0x148);
				for (j = 0; j < n; j++) {
					*(u32*)&(*(Anim40**)((u8*)data + 0x1ac))[j].p += (u32)data;
					q = (*(Anim40**)((u8*)data + 0x1ac))[j].p;
					if (FLD(q, 0x24) < (u32)q) {
						FLD(q, 0x24) += (u32)q;
						FLD(q, 0x28) += (u32)q;
						FLD(q, 0x2c) += (u32)q;
						FLD(q, 0x30) += (u32)q;
						FLD(q, 0x34) += (u32)q;
						FLD(q, 0x38) += (u32)q;
						FLD(q, 0x3c) += (u32)q;
						FLD(q, 0x40) += (u32)q;
					}
				}
			}
			break;
		case 6:
			if (FLD(data, 0x48) < (u32)data) {
				FLD(data, 0x48) += (u32)data;
			}
			break;
		case 7:
			if (FLD(data, 0x64) < (u32)data) {
				FLD(data, 0x64) += (u32)data;
				FLD(data, 0x68) += (u32)data;
				FLD(data, 0x6c) += (u32)data;
			}
			break;
		case 8:
			if (FLD(data, 0xc8) < (u32)data) {
				FLD(data, 0xc8) += (u32)data;
				FLD(data, 0xcc) += (u32)data;
				FLD(data, 0xd0) += (u32)data;
				FLD(data, 0xd4) += (u32)data;
				FLD(data, 0xd8) += (u32)data;
				FLD(data, 0xdc) += (u32)data;
				FLD(data, 0xe0) += (u32)data;
				FLD(data, 0xe4) += (u32)data;
				FLD(data, 0xe8) += (u32)data;
				FLD(data, 0xec) += (u32)data;
				FLD(data, 0xf0) += (u32)data;
				FLD(data, 0xf4) += (u32)data;
				FLD(data, 0xf8) += (u32)data;
				FLD(data, 0xfc) += (u32)data;
				FLD(data, 0x100) += (u32)data;
				FLD(data, 0x104) += (u32)data;
				FLD(data, 0x108) += (u32)data;
				FLD(data, 0x10c) += (u32)data;
				FLD(data, 0x110) += (u32)data;
				FLD(data, 0x114) += (u32)data;
				FLD(data, 0x118) += (u32)data;
				FLD(data, 0x11c) += (u32)data;
				FLD(data, 0x120) += (u32)data;
			}
			break;
		case 9:
			if (FLD(data, 0x58) < (u32)data) {
				FLD(data, 0x58) += (u32)data;
				FLD(data, 0x5c) += (u32)data;
				FLD(data, 0x60) += (u32)data;
				FLD(data, 0x64) += (u32)data;
			}
			break;
		case 10:
			if (FLD(data, 0x48) < (u32)data) {
				FLD(data, 0x48) += (u32)data;
			}
			break;
		case 0:
		default:
			break;
	}
}

void fileGarbageMoveMem(void* data, FileEntry* file) {
	if (file->state == 3) {
		if (!file->entry) {
			fileGarbageDataAdrClear(file);
		}
	}
	else {
		fileGarbageDataAdrClear(file);
	}
	memmove(data, ((smartEntry*)file->data)->address, ((smartEntry*)file->data)->size);
	*file->data = data;
	if (file->state == 3) {
		if (file->entry) {
			file->entry->address = data;
		}
		else {
			fileGarbageDataAdrSet(*file->data, file->field_0x1);
		}
	}
	else {
		fileGarbageDataAdrSet(*file->data, file->field_0x1);
	}
}

void _fileGarbage(BOOL a1) {
	FileEntry* f;
	FileEntry* prev;
	FileEntry* first;
	FileEntry* next;

	if (a1 == 0) {
		for (f = afp->firstused; f; f = f->next) {
			if (f->state == 3) {
				if (f->entry) {
					if (OSGetCurrentThread() == &dvdmgr_thread) {
						f->entry->status = 8;
					}
					else {
						while (f->entry) {
							OSYieldThread();
						}
					}
				}
				f->state = 2;
			}
		}
	}
	else if (a1 == 1) {
		for (f = afp->firstused; f; f = f->next) {
			if (f->state == 3) {
				if (f->entry) {
					if (OSGetCurrentThread() == &dvdmgr_thread) {
						continue;
					}
					while (f->entry) {
						OSYieldThread();
					}
				}
				else {
					f->references--;
					if ((s16)f->references <= -2) {
						f->state = 2;
					}
				}
			}
		}
	}

	prev = NULL;
	first = NULL;
	for (f = afp->firstused; f; f = next) {
		next = f->next;
		if (f->state == 2) {
			f->state = 0;
			if ((void**)&f->field_0x4 != f->data) {
				smartFree((smartEntry*)f->data);
			}
			if (prev) {
				prev->next = f->next;
			}
			if (!afp->firstavailable) {
				afp->firstavailable = f;
			}
			else {
				afp->lastavailable->next = f;
			}
			f->next = NULL;
			afp->lastavailable = f;
		}
		else {
			if (!prev) {
				first = f;
			}
			prev = f;
		}
	}
	afp->firstused = first;
	afp->lastused = prev;
}

FileEntry* fileAllocf(s32 type, const char* format, ...) {
	va_list va;

	va_start(va, format);
	vsprintf(_filename, format, va);
	return _fileAlloc(_filename, type, NULL);
}

FileEntry* fileAlloc(const char* filename, s32 type) {
	return _fileAlloc(filename, type, NULL);
}

FileEntry* _fileAlloc(const char* filename, s32 type, void (*callback)(FileEntry*)) {
	void* handle;
	FileEntry *search;
	smartEntry* smart;
	DVDEntry* entry;
	FileEntry *newentry, *temp;
	u32 size, test;

	for (search = afp->firstused; search; search = search->next) {
		if (search->state && !strcmp(search->filename, filename)) {
			while (search->entry) {;} //infinite loop????
			if (search->state == 3) {
				search->state = 1;
				search->references = 0;
			}
			else if (search->state == 2) {
				search->state = 1;
			}
			search->references++;
			return search;
		}
	}
	newentry = afp->firstavailable;
	if (!newentry) {
		_fileGarbage(1);
		newentry = afp->firstavailable;
	}
	if (!newentry) {
		_fileGarbage(0);
		newentry = afp->firstavailable;
	}

	handle = NULL;
	temp = newentry->next;

	switch (afp->archiveType) {
		case 0:
			handle = arcOpen(filename, NULL, NULL);
			break;
		case 1:
			handle = arcOpen(filename, NULL, NULL);
			if (!handle) {
				handle = arcOpen(filename, NULL, NULL);
			}
			if (!handle) {
				handle = arcOpen(filename, NULL, NULL);
			}
			break;
		case 2:
			handle = arcOpen(filename, NULL, NULL);
			if (!handle) {
				handle = arcOpen(filename, NULL, NULL);
			}
			if (!handle) {
				handle = arcOpen(filename, NULL, NULL);
			}
			break;
	}
	if (handle) {
		fileGarbageDataAdrSet(handle, type);
	}
	if (handle) {
		newentry->state = 1;
		newentry->data = &newentry->field_0x4;
		*newentry->data = handle;
		newentry->references = 1;
		newentry->field_0x1 = type;
		newentry->next = NULL;
		strcpy(newentry->filename, filename);
		newentry->entry = NULL;
	}
	else {
		entry = DVDMgrOpen(filename, 2, 0);
		if (!entry) {
			return NULL;
		}
		size = DVDMgrGetLength(entry);
		test = size + ((size & 31) ? 32 - (size & 31) : 0);
		if (!test) {
			DVDMgrClose(entry);
			return NULL;
		}
		if (test & 31) {
			test += 32 - (test & 31);
		}
		smart = smartAlloc(test, 0);
		smart->field_0x8 = newentry;
		DVDMgrRead(entry, smart->address, test, 0);
		DVDMgrClose(entry);
		newentry->data = &smart->address;
		newentry->state = 1;
		newentry->references = 1;
		newentry->field_0x1 = type;
		newentry->next = NULL;
		strcpy(newentry->filename, filename);
		newentry->entry = NULL;
		fileGarbageDataAdrSet(smart->address, type);
	}
	afp->firstavailable = temp;
	if (!afp->firstavailable) {
		afp->lastavailable = NULL;
	}
	if (!afp->firstused) {
		afp->firstused = newentry;
		afp->lastused = newentry;
	}
	else {
		afp->lastused->next = newentry;
		afp->lastused = newentry;
	}
	return newentry;
}

void fileFree(FileEntry* handle) {
	if (handle) {
		if (handle->data) {
			if (handle->state == 1) {
				handle->references--;
				if (!handle->references) {
					handle->state = 2;
				}
			}
		}
	}
}

void dvdReadDoneCallBack(s32 error, DVDFileInfo* info) {
	DVDEntry* entry;
	FileEntry* f;

	for (f = afp->firstused; f; f = f->next) {
		if (&f->entry->info == info) {
			break;
		}
	}
	entry = f->entry;
	if (error == -3) {
		f->entry = NULL;
		f->state = 2;
		f->field_0x1 = 11;
		DVDMgrClose(entry);
	}
	else {
		f->entry = NULL;
		fileGarbageDataAdrSet(*f->data, f->field_0x1);
		DVDMgrClose(entry);
		if (f->callback) {
			f->callback(f);
		}
	}
}

s32 fileAsyncf(s32 type, FileCallback callback, const char* format, ...) {
	va_list va;

	va_start(va, format);
	vsprintf(_filename, format, va);
	return fileAsync(_filename, type, callback);
}

s32 fileAsync(const char* filename, s32 type, FileCallback callback) {
	FileEntry *search, *newentry, *temp;
	smartEntry* smart;
	DVDEntry* entry;
	void* handle;
	u32 size, test;

	for (search = afp->firstused; search; search = search->next) {
		if (search->state && !strcmp(search->filename, filename)) {
			if (search->entry) return 0;
			if (search->state == 3) return (s32)search;
			if (search->state == 2) {
				search->state = 3;
			}
			return (s32)search;
		}
	}

	newentry = afp->firstavailable;
	if (!newentry) {
		_fileGarbage(1);
		newentry = afp->firstavailable;
	}
	if (!newentry) {
		_fileGarbage(0);
		newentry = afp->firstavailable;
	}

	handle = NULL;
	temp = newentry->next;

	switch (afp->archiveType) {
		case 0:
			handle = arcOpen(filename, NULL, NULL);
			break;
		case 1:
			handle = arcOpen(filename, NULL, NULL);
			if (!handle) {
				handle = arcOpen(filename, NULL, NULL);
			}
			if (!handle) {
				handle = arcOpen(filename, NULL, NULL);
			}
			break;
		case 2:
			handle = arcOpen(filename, NULL, NULL);
			if (!handle) {
				handle = arcOpen(filename, NULL, NULL);
			}
			if (!handle) {
				handle = arcOpen(filename, NULL, NULL);
			}
			break;
	}

	if (handle) {
		fileGarbageDataAdrSet(handle, type);
	}
	
	if (handle) {
		newentry->state = 3;
		newentry->data = &newentry->field_0x4;
		*newentry->data = handle;
		newentry->references = 0;
		newentry->field_0x1 = type;
		newentry->next = 0;
		strcpy(newentry->filename, filename);
		newentry->entry = NULL;
		afp->firstavailable = afp->firstavailable->next;
		if (!afp->firstavailable) {
			afp->lastavailable = NULL;
		}
		if (!afp->firstused) {
			afp->firstused = newentry;
			afp->lastused = newentry;
		}
		else {
			afp->lastused->next = newentry;
			afp->lastused = newentry;
		}
		return (s32)newentry;
	}
	else {
		entry = DVDMgrOpen(filename, 2, 0);
		if (!entry) {
			return -1;
		}
		size = DVDMgrGetLength(entry);
		test = size + ((size & 31) ? 32 - (size & 31) : 0);
		if (!test) {
			DVDMgrClose(entry);
			return 0;
		}
		DVDMgrClose(entry);
		if (test & 31) {
			test += 32 - (test & 31);
		}
		smart = smartAlloc(test, 0);
		smart->field_0x8 = newentry;
		newentry->data = &smart->address;
		newentry->state = 3;
		newentry->references = 0;
		newentry->field_0x1 = type;
		newentry->next = NULL;
		newentry->callback = callback;
		strcpy(newentry->filename, filename);
		afp->firstavailable = temp;
		if (!afp->firstavailable) {
			afp->lastavailable = NULL;
		}
		if (!afp->firstused) {
			afp->firstused = newentry;
			afp->lastused = newentry;
		}
		else {
			afp->lastused->next = newentry;
			afp->lastused = newentry;
		}
		newentry->entry = DVDMgrOpen(filename, 2u, 0);
		DVDMgrReadAsync(newentry->entry, smart->address, test, 0, dvdReadDoneCallBack);
		return 0;
	}
}

//TODO: enum of all archive types
void fileSetCurrentArchiveType(s32 type) {
	afp->archiveType = type;
}
