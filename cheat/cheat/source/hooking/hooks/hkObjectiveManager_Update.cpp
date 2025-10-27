#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkObjectiveManager_Update(SDK::ObjectiveManager* objectiveManager, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called ObjectiveManager_Update");
	SDK::ObjectiveManager_Update_ptr(objectiveManager, methodInfo);

	if (globalRunning)
		GameState::objectiveManager = objectiveManager;
}
