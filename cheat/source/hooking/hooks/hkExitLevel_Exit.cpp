#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkExitLevel_Exit(SDK::ExitLevel* exitLevel, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called ExitLevel_Exit");
	SDK::ExitLevel_Exit_ptr(exitLevel, photonMessageInfo, methodInfo);

	if (globalRunning)
		GameState::Reset();
}
