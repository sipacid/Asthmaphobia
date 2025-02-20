#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkDeadZoneController_Awake(SDK::DeadZoneController* deadZoneController, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called DeadZoneController_Awake")
	SDK::DeadZoneController_Awake_ptr(deadZoneController, methodInfo);

	if (globalRunning)
		GameState::deadZoneController = deadZoneController;
}
