#include <Windows.h>

#include "injector/injector.h"

int main()
{
	DWORD processId = 0;

	while (!processId)
	{
		processId = Injector::GetProcessIdByName("Phasmophobia.exe");
		Sleep(30);
	}

	Injector::InjectDLL(processId, "cheat.dll");

	return 0;
}
