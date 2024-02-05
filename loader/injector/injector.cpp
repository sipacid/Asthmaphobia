#include "injector.h"

#include <iostream>
#include <TlHelp32.h>

DWORD Injector::GetProcessIdByName(const char* processName)
{
	DWORD processId = 0;

	if (const HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); hSnapshot && hSnapshot != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 processEntry32{};
		processEntry32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnapshot, &processEntry32))
		{
			do
			{
				if (!_stricmp(processEntry32.szExeFile, processName))
				{
					processId = processEntry32.th32ProcessID;
					break;
				}
			} while (Process32Next(hSnapshot, &processEntry32));
		}
	}

	return processId;
}

void Injector::InjectDLL(DWORD processId, const char* dllPath)
{
	char dllLibFullPath[256];

	if (!GetFullPathName(dllPath, sizeof(dllLibFullPath), dllLibFullPath, nullptr))
	{
		printf("[x] Cannot get full path to %s\n", dllPath);
		return;
	}

	const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);
	if (hProcess && hProcess != INVALID_HANDLE_VALUE)
	{
		if (const LPVOID lpBaseAddress = VirtualAllocEx(hProcess, nullptr, MAX_PATH, MEM_COMMIT | MEM_RESERVE,
			PAGE_READWRITE))
		{
			WriteProcessMemory(hProcess, lpBaseAddress, dllLibFullPath, strlen(dllLibFullPath) + 1, nullptr);

			if (const HANDLE hThread = CreateRemoteThread(hProcess, nullptr, 0,
				reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryA),
				lpBaseAddress, 0, nullptr))
			{
				CloseHandle(hThread);
			}
		}
	}

	if (hProcess)
	{
		CloseHandle(hProcess);
	}
}
