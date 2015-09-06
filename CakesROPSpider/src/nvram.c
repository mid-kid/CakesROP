/*
 * Contributed to Cakes by an anonymous contributor
 * adapted from https://github.com/SciresM/memdump
 */

#include "nvram.h"
#include "compat.h"
#include "patches.h"
#include "ctru.h"

#define PAYLOAD_FNAME_LEN 0x32

typedef struct index_s
{
	char *desc;
	u32 offset;
} index_s;

typedef struct patch_s
{
	u32 size;
	u32 offset;
	u8 patch[];
} patch_s;

typedef struct patch_set_s
{
	u32 magic;
	u32 count;
	u32 offset[];
} patch_set_s;

// https://nfc-wisp.wikispaces.com/file/view/fcd-15693-3.pdf/271283012/fcd-15693-3.pdf
// http://www.barrgroup.com/Embedded-Systems/How-To/CRC-Calculation-C-Code
#define POLYNOMIAL 0x8005

static inline u16 Rev16(u16 input)
{
	input = ((input >> 1) & 0x5555) | ((input & 0x5555) << 1);
	input = ((input >> 2) & 0x3333) | ((input & 0x3333) << 2);
	input = ((input >> 4) & 0x0F0F) | ((input & 0x0F0F) << 4);
	input = ((input >> 8) & 0x00FF) | ((input & 0x00FF) << 8);

	return input;
}

static inline u8 Rev8(u8 input)
{
	input = ((input >> 1) & 0x55) | ((input & 0x55) << 1);
	input = ((input >> 2) & 0x33) | ((input & 0x33) << 2);
	input = ((input >> 4) & 0x0F) | ((input & 0x0F) << 4);

	return input;
}

// Reflected input/output CRC16 with poly 0x8005
u32 CRC16(const void *data, size_t size)
{
	const u8* ucdata = (const u8 *) data;
	u32 current_crc_value = 0xFFFF; // Preset
	for(u32 i = 0; i < size; i++)
	{
		current_crc_value ^= Rev8(ucdata[i]) << 8;
		for(int j = 0; j < 8; j++)
		{
			if(current_crc_value & 0x8000)
			{
				current_crc_value = (current_crc_value << 1) ^ POLYNOMIAL;
			}
			else
			{
				current_crc_value = (current_crc_value << 1);
			}
		}
	}

	return Rev16(current_crc_value);
}

void UserSettingsCRC(void *buffer)
{
	u16 *slot = buffer;
	u16 crc1 = CRC16(slot, 0x70);
	u16 crc2 = CRC16(&slot[0x3A], 0x8A);
	slot[0x39] = crc1;
	slot[0x7F] = crc2;
}

// Apply zoogie patches
int ApplyPatch(const u8 *patchBuf, u8 *work, u32 sel)
{
	const wchar_t cakes[PAYLOAD_FNAME_LEN / 2] = L"YS:/" DATNAME;
	u32 magic = *(u32 *)(patchBuf);
	if(magic != 0x524f5050)
		return -1;

	u32 index_offset = *(u32 *)(patchBuf + 4);
	index_s *indices = (index_s *)(patchBuf + index_offset);

	patch_set_s *ps = (patch_set_s *)(patchBuf + indices[sel].offset);

	for(u32 i = 0; i < ps->count; ++i)
	{
		patch_s *patch = (patch_s *)(patchBuf + ps->offset[i]);
		_memcpy(work + patch->offset, patch->patch, patch->size);
	}

	u8 *name = work + 0x11C;

	IFILE file;
	_memset(&file, 0, sizeof(file));
	if(compat.app.IFile_Open(&file, L"dmc:/ropCustom.txt", FILE_R) == 0)
	{
		const u32 maxPathLen = PAYLOAD_FNAME_LEN / 2;
		const u32 maxFnameLen = maxPathLen - 4;

		u8 *custName = (u8 *)(0x18410000 + 0x200);
		_memset(custName, 0, maxPathLen);
		_memcpy(custName, "YS:/", 4);

		unsigned int read;
		compat.app.IFile_Read(&file, &read, custName + 4, maxFnameLen);
		for(u32 i = 0; i < maxPathLen; i++)
		{
			name[i * 2 + 1] = 0;
			if(custName[i] == '\n' || custName[i] == '\r' || custName[i] == 0)
			{
				name[i * 2] = 0;
				break;
			}

			name[i * 2] = custName[i];
		}
	}
	else
		compat.app.memcpy(name, cakes, PAYLOAD_FNAME_LEN);

	// Fix CRCs
	UserSettingsCRC(work);
	UserSettingsCRC(work + 0x100);

	return 0;
}

Result DumpNVRAM(Handle CFGNOR_handle)
{
	Result ret = 0;
	// chunk size 0x100 taken from ctrulib
	// no idea why it's so low
	u32 chunksize = 0x100;
	u32 size = 128 * 1024;
	u32 *buf = (u32 *) 0x18410000;

	/* Mystery value 1. 3dbrew says it's "usually" 1. */
	if((ret = CFGNOR_Initialize(CFGNOR_handle, 1)) == 0)
	{
		IFILE file;
		_memset(&file, 0, sizeof(file));
		compat.app.IFile_Open(&file, L"dmc:/nvram.bin", FILE_W);

		for(u32 pos = 0; pos < size; pos += chunksize)
		{
			if(size - pos < chunksize)
				chunksize = size - pos;

			ret = CFGNOR_ReadData(CFGNOR_handle, pos, buf, chunksize);
			if(ret != 0)
				return ret;

			unsigned int written;
			compat.app.IFile_Write(&file, &written, buf, chunksize, 1);
		}
		compat.app.svcSleepThread(0x400000LL);
	}

	return ret;
}

Result PatchNVRAM(Handle CFGNOR_handle)
{
	Result ret = 0;
	u8 *buf = (u8 *) 0x18410000;

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
			if(ApplyPatch(rawData, buf, compat.patch_sel))
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
