#include "source/common.h"
#include "source/feature/players/godmode/godmode.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

std::nullptr_t Hooks::hkPlayer_StartKillingPlayerNetworked(SDK::Player* player, bool a1, bool a2, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called Player_StartKillingPlayerNetworked");
	if (globalRunning)
		return featureManager->GetFeature<Features::Players::GodMode>("Players::GodMode")->OnPlayerStartKillingPlayerNetworked(player, a1, a2, photonMessageInfo, methodInfo);

	return SDK::Player_StartKillingPlayerNetworked_ptr(player, a1, a2, photonMessageInfo, methodInfo);
}
