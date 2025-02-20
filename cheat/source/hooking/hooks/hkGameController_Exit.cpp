#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkGameController_Exit(SDK::GameController* gameController, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	LOG_DEBUG("Called GameController_Exit");
	SDK::GameController_Exit_ptr(gameController, photonMessageInfo, methodInfo);

	if (globalRunning)
		GameState::Reset();
}
