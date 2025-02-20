#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkGameController_Exit(SDK::GameController* gameController, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called GameController_Exit")
	if (!globalRunning)
		return SDK::GameController_Exit_ptr(gameController, photonMessageInfo, methodInfo);

	GameState::Reset();
	SDK::GameController_Exit_ptr(gameController, photonMessageInfo, methodInfo);
}
