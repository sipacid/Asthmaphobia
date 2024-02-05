#pragma once
#include <Windows.h>

namespace Injector
{
	DWORD GetProcessIdByName(const char* processName);
	void InjectDLL(DWORD processId, const char* dllPath);
}