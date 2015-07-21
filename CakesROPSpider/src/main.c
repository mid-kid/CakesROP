/*
 * Contributed to Cakes by an anonymous contributor
 * adapted from https://github.com/SciresM/memdump
 */
#include "mkhax.h"

#include "types.h"
#include "compat.h"
#include "svc.h"
#include "nvram.h"
#include "ctru.h"

/* undef to dump NVRAM */
#define PATCH

int main();

__attribute__ ((section (".text.start"), naked))
void entry()
{
	main();
}

size_t strlen(const char *s)
{
	size_t sz = 0;

	for(; *s; s++)
		sz++;

	return sz;
}


int main()
{
	init_compat();
	Result ret;

	compat.app.svcSleepThread(0x400000LL);

	arm11_kernel_exploit_setup();
	patch_srv_access();

	Handle CFGNOR_handle;
	const char* svcName = "cfg:nor";
	if((ret = compat.app.srvGetServiceHandle(&CFGNOR_handle, svcName, strlen(svcName))) != 0)
	{
		svcExitThread();
	}

#ifdef PATCH
	PatchNVRAM(CFGNOR_handle);
#else
	DumpNVRAM(CFGNOR_handle);
#endif
	svcCloseHandle(CFGNOR_handle);
	svcExitThread();

	return 0;
}

