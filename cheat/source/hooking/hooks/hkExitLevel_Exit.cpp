#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkExitLevel_Exit(SDK::ExitLevel* exitLevel, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called ExitLevel_Exit")
	if (!globalRunning)
		return SDK::ExitLevel_Exit_ptr(exitLevel, photonMessageInfo, methodInfo);

	GameState::Reset();
	SDK::ExitLevel_Exit_ptr(exitLevel, photonMessageInfo, methodInfo);
}
