#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkPauseMenuController_Leave(SDK::PauseMenuController* pauseMenuController, SDK::MethodInfo* methodInfo)
{
	LOG_DEBUG("Called PauseMenuController_Leave");
	SDK::PauseMenuController_Leave_ptr(pauseMenuController, methodInfo);

	if (globalRunning)
		GameState::Reset();
}
