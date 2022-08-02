#pragma once

// See https://github.com/tandasat/SecRuntimeSample/blob/master/SecRuntimeSampleNative/Win32Api.h


typedef ACCESS_MASK REGSAM;

typedef struct _STARTUPINFOA {
	DWORD cb;
	LPSTR lpReserved;
	LPSTR lpDesktop;
	LPSTR lpTitle;
	DWORD dwX;
	DWORD dwY;
	DWORD dwXSize;
	DWORD dwYSize;
	DWORD dwXCountChars;
	DWORD dwYCountChars;
	DWORD dwFillAttribute;
	DWORD dwFlags;
	WORD wShowWindow;
	WORD cbReserved2;
	LPBYTE lpReserved2;
	HANDLE hStdInput;
	HANDLE hStdOutput;
	HANDLE hStdError;
} STARTUPINFOA, *LPSTARTUPINFOA;

typedef struct _PROCESS_INFORMATION {
	HANDLE hProcess;
	HANDLE hThread;
	DWORD dwProcessId;
	DWORD dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;


extern "C" {
	WINBASEAPI HMODULE WINAPI GetModuleHandleW(LPCWSTR lpModuleName);

	LONG WINAPI RegOpenKeyExA(HKEY, LPCSTR, DWORD, REGSAM, PHKEY);
	LONG WINAPI RegQueryValueExA(HKEY, LPCSTR, PDWORD, PDWORD, LPBYTE, PDWORD);
	LONG WINAPI RegCloseKey(HKEY);

	WINBASEAPI HANDLE WINAPI FindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
	WINBASEAPI BOOL WINAPI FindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);
	WINBASEAPI BOOL WINAPI FindClose(HANDLE hFindFile);

	WINBASEAPI BOOL WINAPI CreateProcessA(LPCSTR lpApplicationName, LPSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCSTR lpCurrentDirectory, LPSTARTUPINFOA lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
	WINBASEAPI BOOL WINAPI CloseHandle(HANDLE hObject);

	BOOL WINAPI LogonUserExExW(LPTSTR lpszUsername, LPTSTR lpszDomain, LPTSTR lpszPassword, DWORD dwLogonType, DWORD dwLogonProvider, PTOKEN_GROUPS pTokenGroups, PHANDLE phToken, PSID *ppLogonSid, PVOID *ppProfileBuffer, LPDWORD pdwProfileLength, PQUOTA_LIMITS pQuotaLimits);
}

#define WIN32API_TOSTRING(x) #x

// Link exported function
#define WIN32API_INIT_PROC(Module, Name)  \
  Name(reinterpret_cast<decltype(&::Name)>( \
      ::GetProcAddress((Module), WIN32API_TOSTRING(Name))))

// Convenientmacro to declare function
#define WIN32API_DEFINE_PROC(Name) const decltype(&::Name) Name

class Win32Api {

private:
	// Returns a base address of KernelBase.dll
	static HMODULE GetKernelBase() {
		return GetBaseAddress(&::DisableThreadLibraryCalls);
	}

	// Returns a base address of the given address
	static HMODULE GetBaseAddress(const void *Address) {
		MEMORY_BASIC_INFORMATION mbi = {};
		if (!::VirtualQuery(Address, &mbi, sizeof(mbi))) {
			return nullptr;
		}
		const auto mz = *reinterpret_cast<WORD *>(mbi.AllocationBase);
		if (mz != IMAGE_DOS_SIGNATURE) {
			return nullptr;
		}
		return reinterpret_cast<HMODULE>(mbi.AllocationBase);
	}

public:
	const HMODULE m_Kernelbase;
	WIN32API_DEFINE_PROC(GetModuleHandleW);
	WIN32API_DEFINE_PROC(RegOpenKeyExA);
	WIN32API_DEFINE_PROC(RegQueryValueExA);
	WIN32API_DEFINE_PROC(RegCloseKey);
	WIN32API_DEFINE_PROC(FindFirstFileW);
	WIN32API_DEFINE_PROC(FindNextFileW);
	WIN32API_DEFINE_PROC(FindClose);
	WIN32API_DEFINE_PROC(CreateProcessA);
	WIN32API_DEFINE_PROC(CloseHandle);
	const HMODULE m_Sspicli;
	WIN32API_DEFINE_PROC(LogonUserExExW);

	Win32Api()
		: m_Kernelbase(GetKernelBase()),
		WIN32API_INIT_PROC(m_Kernelbase, GetModuleHandleW),
		WIN32API_INIT_PROC(m_Kernelbase, RegOpenKeyExA),
		WIN32API_INIT_PROC(m_Kernelbase, RegQueryValueExA),
		WIN32API_INIT_PROC(m_Kernelbase, RegCloseKey),
		WIN32API_INIT_PROC(m_Kernelbase, FindFirstFileW),
		WIN32API_INIT_PROC(m_Kernelbase, FindNextFileW),
		WIN32API_INIT_PROC(m_Kernelbase, FindClose),
		WIN32API_INIT_PROC(m_Kernelbase, CreateProcessA),
		WIN32API_INIT_PROC(m_Kernelbase, CloseHandle),
		m_Sspicli(GetModuleHandleW(L"SSPICLI.DLL")),
		WIN32API_INIT_PROC(m_Sspicli, LogonUserExExW)
	{};

};
