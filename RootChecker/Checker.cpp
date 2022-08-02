#include "pch.h"
#include "Registry.h"
#include "Checker.h"
#include "Win32Api.h"

void debug(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	char buffer[100];
	vsnprintf_s(buffer, sizeof(buffer), format, args);

	OutputDebugStringA(buffer);

	va_end(args);
}

boolean check01()
{
	debug("Checking registry access...\n");

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

boolean check02()
{
	debug("Checking filesystem access...\n");

	Win32Api win32Api;

	WIN32_FIND_DATAW win32_FIND_DATA = {};
	HANDLE handle = win32Api.FindFirstFileW(L"C:\\Windows\\System32\\config\\*", (LPWIN32_FIND_DATAW)&win32_FIND_DATA);
	if (handle == INVALID_HANDLE_VALUE)
	{
		debug("Failed to query folder. Error: %d\n", GetLastError());
		return false;
	}

	do
	{
		if (win32_FIND_DATA.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			OutputDebugString(L"Directory name:");
		}
		else
		{
			OutputDebugString(L"File name:");
		}
		OutputDebugString(win32_FIND_DATA.cFileName);
		OutputDebugString(L"\n");
	} while (win32Api.FindNextFileW(handle, (LPWIN32_FIND_DATAW)&win32_FIND_DATA));
	if (GetLastError() != ERROR_NO_MORE_FILES)
	{
		debug("Failed to query folder. Error: %d\n", GetLastError());
		return false;
	}
	win32Api.FindClose(handle);

	return true;
}

boolean check03()
{
	debug("Checking process creation...\n");

	Win32Api win32Api;

	PROCESS_INFORMATION process_INFORMATION = {};
	STARTUPINFOA startupinfo = {};
	ZeroMemory(&startupinfo, sizeof(startupinfo));
	if (!win32Api.CreateProcessA("C:\\WINDOWS\\SYSTEM32\\XBFGENERATOR.EXE", NULL, NULL, NULL, false, NORMAL_PRIORITY_CLASS, NULL, NULL, &startupinfo, &process_INFORMATION))
	{
		debug("CreateProcess failed. Error: %d\n", GetLastError());
		return false;
	}
	win32Api.CloseHandle(process_INFORMATION.hProcess);
	win32Api.CloseHandle(process_INFORMATION.hThread);

	return true;
}