#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <random>
#include <filesystem>
#include "injector/injector.h"

using ThreadProc = DWORD(WINAPI *)();

static HMODULE GetRemoteModuleHandle(const DWORD processId, const char* moduleName)
{
	MODULEENTRY32 moduleEntry{};
	moduleEntry.dwSize = sizeof(moduleEntry);
	const HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

	if (snapshot == INVALID_HANDLE_VALUE)
	{
		std::cout << "[!] Failed to create module snapshot. Error: " << GetLastError() << "\n";
		return nullptr;
	}

	bool foundModule = false;
	if (Module32First(snapshot, &moduleEntry))
	{
		do
		{
			if (_stricmp(moduleEntry.szModule, moduleName) == 0)
			{
				foundModule = true;
				break;
			}
		}
		while (Module32Next(snapshot, &moduleEntry));
	}

	CloseHandle(snapshot);
	return foundModule ? moduleEntry.hModule : nullptr;
}

static FARPROC GetRemoteExportAddress(const char* modulePath, const char* exportName, HMODULE remoteBase)
{
	HMODULE localModule = LoadLibraryEx(modulePath, nullptr, DONT_RESOLVE_DLL_REFERENCES);
	if (!localModule)
	{
		std::cout << "[!] Failed to load local copy of DLL. Error: " << GetLastError() << "\n";
		return nullptr;
	}

	FARPROC localExport = GetProcAddress(localModule, exportName);
	if (!localExport)
	{
		FreeLibrary(localModule);
		std::cout << "[!] Export not found in DLL: " << exportName << "\n";
		return nullptr;
	}

	const uintptr_t offset = reinterpret_cast<uintptr_t>(localExport) - reinterpret_cast<uintptr_t>(localModule);

	FreeLibrary(localModule);

	return reinterpret_cast<FARPROC>(reinterpret_cast<uintptr_t>(remoteBase) + offset);
}

static std::string GenerateRandomString(const size_t length)
{
	static constexpr char CHARSET[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dis(0, sizeof(CHARSET) - 2);

	std::string str;
	str.reserve(length);
	for (size_t i = 0; i < length; ++i)
		str += CHARSET[dis(gen)];

	return str;
}

int main()
{
	std::cout << "[+] Waiting for Phasmophobia.exe..." << "\n";
	DWORD processId = 0;

	while (!processId)
	{
		processId = Injector::GetProcessIdByName("Phasmophobia.exe");
		Sleep(30);
	}

	std::cout << "[+] Found process ID: " << processId << "\n";

	const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
	if (!hProcess)
	{
		std::cout << "[!] Failed to open process handle. Error: " << GetLastError() << "\n";
		system("pause");
		return 1;
	}

	const std::string randomName = GenerateRandomString(12) + ".dll";
	const std::string tempPath = std::filesystem::temp_directory_path().string() + randomName;

	if (!CopyFile("cheat.dll", tempPath.c_str(), FALSE))
	{
		std::cout << "[!] Failed to create temporary DLL. Error: " << GetLastError() << "\n";
		CloseHandle(hProcess);
		system("pause");
		return 1;
	}

	std::cout << "[+] Created temporary DLL: " << randomName << "\n";

	const bool injectionResult = Injector::InjectDLL(processId, tempPath.c_str());
	DeleteFile(tempPath.c_str());

	if (!injectionResult)
	{
		std::cout << "[!] DLL injection failed" << "\n";
		CloseHandle(hProcess);
		system("pause");
		return 1;
	}

	std::cout << "[+] DLL injected successfully" << "\n";
	std::cout << "[+] Waiting for module to load..." << "\n";

	Sleep(1000);

	std::cout << "[+] Getting module handle..." << "\n";
	const HMODULE hModule = GetRemoteModuleHandle(processId, randomName.c_str());
	if (!hModule)
	{
		std::cout << "[!] Failed to get module handle in target process\n";
		CloseHandle(hProcess);
		system("pause");
		return 1;
	}

	std::cout << "[+] Module found at: 0x" << std::hex << reinterpret_cast<uintptr_t>(hModule) << std::dec << "\n";

	std::cout << "[+] Creating main thread..." << "\n";

	char dllPath[MAX_PATH];
	GetFullPathName(tempPath.c_str(), MAX_PATH, dllPath, nullptr);

	if (const auto threadProc = GetRemoteExportAddress(dllPath, "AsthmaphobiaThread", hModule))
	{
		const HANDLE hThread = CreateRemoteThread(hProcess, nullptr, 0,
		                                          reinterpret_cast<LPTHREAD_START_ROUTINE>(threadProc), nullptr, 0, nullptr);
		if (hThread)
		{
			std::cout << "[+] Thread created successfully at address: 0x" << std::hex << reinterpret_cast<uintptr_t>(threadProc) << std::dec << "\n";
			CloseHandle(hThread);
		}
		else
		{
			std::cout << "[!] Failed to create thread. Error: " << GetLastError() << "\n";
		}
	}
	else
	{
		std::cout << "[!] Failed to get thread procedure address\n";
	}

	CloseHandle(hProcess);
	std::cout << "\n[+] Process completed." << "\n";
	system("pause");
	return 0;
}
