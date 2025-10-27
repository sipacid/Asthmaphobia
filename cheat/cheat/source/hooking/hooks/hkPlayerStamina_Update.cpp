#include "source/common.h"
#include "source/feature/movement/infinitestamina/infinitestamina.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkPlayerStamina_Update(SDK::PlayerStamina* playerStamina, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called PlayerStamina_Update");
	if (globalRunning)
		GetFeatureManagerInstance().GetFeature<Features::Movement::InfiniteStamina>("Movement::InfiniteStamina")->OnPlayerStaminaUpdate(playerStamina, methodInfo);

	SDK::PlayerStamina_Update_ptr(playerStamina, methodInfo);
}
