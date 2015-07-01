/*
 * Contributed to Cakes by an anonymous contributor
 * adapted from https://github.com/SciresM/memdump
 */

#include "nvram.h"
#include "compat.h"
#include "patches.h"
#include "ctru.h"

static struct file *const patchf = (void*)0x08F10000;

typedef struct index_s
{
	char *desc;
	uint32_t offset;
} index_s;

typedef struct patch_s
{
	uint32_t size;
	uint32_t offset;
	uint32_t patch;
} patch_s;

typedef struct patch_set_s
{
	uint32_t magic;
	uint32_t count;
	uint32_t offset[];
} patch_set_s;

/* Thanks, desmume */
u32 calc_CRC16(u32 start, const void *dataptr, int count)
{
	const u8 *data = dataptr;
	int i, j;
	u32 crc = start & 0xffff;
	const u16 val[8] =
	{0xC0C1, 0xC181, 0xC301, 0xC601, 0xCC01, 0xD801, 0xF001, 0xA001};
	for(i = 0; i < count; i++)
	{
		crc = crc ^ data[i];

		for(j = 0; j < 8; j++)
		{
			int do_bit = 0;

			if(crc & 0x1)
				do_bit = 1;

			crc = crc >> 1;

			if(do_bit)
			{
				crc = crc ^ (val[j] << (7 - j));
			}
		}
	}
	return crc;
}

void userSettingsCRC(void *buffer)
{
	u16 *slot = buffer;
	u16 CRC1 = calc_CRC16(0xFFFF, slot, 0x70);
	u16 CRC2 = calc_CRC16(0xFFFF, &slot[0x3A], 0x8A);
	slot[0x39] = CRC1;
	slot[0x7F] = CRC2;
}

// Apply zoogie patches
int apply(const uint8_t *patchBuf, uint8_t *work, uint32_t sel)
{
	const wchar_t cakes[] = L"YS:/Cakes.dat";
	uint32_t magic = *(uint32_t *)(patchBuf);
	if(magic != 0x524f5050)
		return -1;

	uint32_t index_offset = *(uint32_t *)(patchBuf + 4);
	index_s *indices = (index_s *)(patchBuf + index_offset);

	patch_set_s *ps = (patch_set_s *)(patchBuf + indices[sel].offset);

	for(uint32_t i = 0; i < ps->count; ++i)
	{
		patch_s *patch = (patch_s *)(patchBuf + ps->offset[i]);
		compat.app.memcpy(work + patch->offset, &(patch->patch), patch->size);
	}

	compat.app.memcpy(work + 0x11C, cakes, 0x20);

	// Fix CRCs
	userSettingsCRC(work);
	userSettingsCRC(work + 0x100);

	return 0;
}

Result DumpNVRAM(Handle CFGNOR_handle)
{
	Result ret = 0;
	u32 pos = 0;
	// chunk size 0x100 taken from ctrulib
	// no idea why it's so low
	u32 chunksize = 0x100;
	u32 size = 128 * 1024;
	u32 *buf = (u32 *) 0x18410000;
	int *fileop_len = (void *) 0x08F01000;

	/* Mystery value 1. 3dbrew says it's "usually" 1. */
	if((ret = CFGNOR_Initialize(CFGNOR_handle, 1)) == 0)
	{
		patchf->pos = 0;
		compat.app.IFile_Open(patchf, L"dmc:/nvram.bin", FILE_W);

		for(pos = 0; pos < size; pos += chunksize)
		{
			if(size - pos < chunksize)
				chunksize = size - pos;

			ret = CFGNOR_ReadData(CFGNOR_handle, pos, buf, chunksize);
			if(ret != 0)
				return ret;
			compat.app.IFile_Write(patchf, fileop_len, buf, chunksize, 1);
		}
		compat.app.svcSleepThread(0x400000LL);
	}

	return ret;
}

Result PatchNVRAM(Handle CFGNOR_handle)
{
	Result ret = 0;
	u8 *buf = (u8 *) 0x18410000;
	u8 *patchBuf = buf + 0x200;

	// Mystery value 1. 3dbrew says it's "usually" 1.
	if((ret = CFGNOR_Initialize(CFGNOR_handle, 1)) == 0)
	{
		// User settings should always be at 0x1FE00
		u32 userSettingsOffset = 0x1FE00;

		// Read current user settings
		ret = CFGNOR_ReadData(CFGNOR_handle, userSettingsOffset, (u32 *)buf, 0x100);
		ret |= CFGNOR_ReadData(CFGNOR_handle, userSettingsOffset + 0x100, (u32 *)(buf + 0x100), 0x100);

		if(ret == 0)
		{
			if(apply(rawData, buf, compat.patch_sel))
				return -1;

			// ctrulib doesn't read/write more than 0x100 at a time. Better
			// err on the side of caution here.
			CFGNOR_WriteData(CFGNOR_handle, userSettingsOffset,         (u32 *)buf, 0x100);
			buf += 0x100;
			CFGNOR_WriteData(CFGNOR_handle, userSettingsOffset + 0x100, (u32 *)buf, 0x100);
		}

		CFGNOR_Shutdown(CFGNOR_handle);
	}

	return ret;
}
