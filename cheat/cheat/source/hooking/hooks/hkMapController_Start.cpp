#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkMapController_Start(SDK::MapController* mapController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called MapController_Start");
	SDK::MapController_Start_ptr(mapController, methodInfo);

	if (globalRunning)
		GameState::mapController = mapController;
}
