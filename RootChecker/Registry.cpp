#include "pch.h"
#include "Win32Api.h"
#include "Registry.h"

void getValue(HKEY hKeyRoot, LPCSTR lpSubKey, LPCSTR valueName, LPBYTE value, DWORD valueSize, PDWORD valueKind)
{
	Win32Api win32Api;

	HKEY hKey = {};
	auto lResult = win32Api.RegOpenKeyExA(hKeyRoot, lpSubKey, 0, KEY_READ, &hKey);
	if (lResult != 0) {
		return;
	}

	lResult = win32Api.RegQueryValueExA(hKey, valueName, NULL, valueKind, value, &valueSize);
	if (lResult != 0) {
		return;
	}

	win32Api.RegCloseKey(hKey);
}