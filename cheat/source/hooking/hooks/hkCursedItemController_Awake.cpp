#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkCursedItemController_Awake(SDK::CursedItemController* cursedItemController, SDK::MethodInfo* methodInfo)
{
	LOG_DEBUG("Called CursedItemController_Awake");
	SDK::CursedItemController_Awake_ptr(cursedItemController, methodInfo);

	if (globalRunning)
		GameState::cursedItemController = cursedItemController;
}
