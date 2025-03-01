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
			}
			while (Process32Next(hSnapshot, &processEntry32));
		}
	}

	return processId;
}

bool Injector::InjectDLL(const DWORD processId, const char* dllPath)
{
	char dllLibFullPath[256];
	bool success = false;

	if (!GetFullPathName(dllPath, sizeof(dllLibFullPath), dllLibFullPath, nullptr))
	{
		printf("[!] Cannot get full path to %s\n", dllPath);
		return false;
	}
	printf("[+] Full DLL path: %s\n", dllLibFullPath);

	const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);
	if (!hProcess || hProcess == INVALID_HANDLE_VALUE)
	{
		printf("[!] Failed to open process handle. Error: %lu\n", GetLastError());
		return false;
	}

	printf("[+] Allocating memory in target process...\n");
	const LPVOID lpBaseAddress = VirtualAllocEx(hProcess, nullptr, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!lpBaseAddress)
	{
		printf("[!] Memory allocation failed. Error: %lu\n", GetLastError());
		CloseHandle(hProcess);
		return false;
	}

	printf("[+] Writing DLL path to target process...\n");
	if (!WriteProcessMemory(hProcess, lpBaseAddress, dllLibFullPath, strlen(dllLibFullPath) + 1, nullptr))
	{
		printf("[!] Failed to write to process memory. Error: %lu\n", GetLastError());
		CloseHandle(hProcess);
		return false;
	}

	printf("[+] Creating remote thread for LoadLibrary...\n");
	const HANDLE hThread = CreateRemoteThread(hProcess, nullptr, 0,
	                                          reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryA),
	                                          lpBaseAddress, 0, nullptr);

	if (hThread)
	{
		printf("[+] Waiting for thread completion...\n");
		WaitForSingleObject(hThread, INFINITE);
		DWORD exitCode = 0;
		GetExitCodeThread(hThread, &exitCode);
		success = (exitCode != 0);
		printf("[+] Thread completed with exit code: 0x%08lX\n", exitCode);
		CloseHandle(hThread);
	}
	else
	{
		printf("[!] Failed to create remote thread. Error: %lu\n", GetLastError());
	}

	CloseHandle(hProcess);
	return success;
}
