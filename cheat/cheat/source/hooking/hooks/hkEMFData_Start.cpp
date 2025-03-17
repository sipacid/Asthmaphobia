#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkEMFData_Start(SDK::EMFData* emfData, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called EMFData_Start");
	SDK::EMFData_Start_ptr(emfData, methodInfo);

	if (globalRunning)
		GameState::emfData = emfData;
}
