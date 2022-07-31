#include "pch.h"
#include "Registry.h"
#include "Checker.h"

void debug(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	char buffer[100];
	vsnprintf_s(buffer, sizeof(buffer), format, args);

	OutputDebugStringA(buffer);

	va_end(args);
}

boolean check()
{
	debug("Checking...\n");

	HKEY HKEY_LOCAL_MACHINE = (HKEY)2147483650U;

	BYTE value[1024];
	DWORD valueKind = 0;
	getValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\PhoneProvisioner", "ColdBootDone", (LPBYTE)&value, sizeof(value), &valueKind);
	if (valueKind != REG_DWORD)
	{
		debug("Wrong registry value type!\n");
		return false;
	}
	DWORD valueWord = *value;
	debug("Value %d\n", valueWord);

	return true;
}