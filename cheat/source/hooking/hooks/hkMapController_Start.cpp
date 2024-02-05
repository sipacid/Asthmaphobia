#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkMapController_Start(SDK::MapController* mapController, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called MapController_Start");
	if (!globalRunning)
		return SDK::MapController_Start_ptr(mapController, methodInfo);

	GameState::mapController = mapController;

	SDK::MapController_Start_ptr(mapController, methodInfo);
}
