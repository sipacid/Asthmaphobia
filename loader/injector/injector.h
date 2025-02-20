#pragma once
#include <Windows.h>

namespace Injector
{
	DWORD GetProcessIdByName(const char* processName);
	bool InjectDLL(DWORD processId, const char* dllPath);
}
