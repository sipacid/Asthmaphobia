#include "source/common.h"
#include "source/feature/movement/infinitestamina/infinitestamina.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkPlayerStamina_Update(SDK::PlayerStamina* playerStamina, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called PlayerStamina_Update");
	if (globalRunning)
		featureManager->GetFeature<Features::Movement::InfiniteStamina>("Movement::InfiniteStamina")->OnPlayerStamina_Update(playerStamina, methodInfo);

	SDK::PlayerStamina_Update_ptr(playerStamina, methodInfo);
}
