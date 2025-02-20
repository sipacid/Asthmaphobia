#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkCursedItemController_Awake(SDK::CursedItemController* cursedItemController, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called CursedItemController_Awake")
	SDK::CursedItemController_Awake_ptr(cursedItemController, methodInfo);

	if (globalRunning)
		GameState::cursedItemController = cursedItemController;
}
