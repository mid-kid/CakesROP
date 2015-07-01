#ifndef _NVRAM_H
#define _NVRAM_H

#include "types.h"

Result DumpNVRAM(Handle CFGNOR_handle);
Result PatchNVRAM(Handle CFGNOR_handle);

#endif
