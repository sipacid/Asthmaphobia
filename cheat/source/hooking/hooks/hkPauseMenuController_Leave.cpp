#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkPauseMenuController_Leave(SDK::PauseMenuController* pauseMenuController, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called PauseMenuController_Leave");
	if (!globalRunning)
		return SDK::PauseMenuController_Leave_ptr(pauseMenuController, methodInfo);

	GameState::Reset();
	SDK::PauseMenuController_Leave_ptr(pauseMenuController, methodInfo);
}
