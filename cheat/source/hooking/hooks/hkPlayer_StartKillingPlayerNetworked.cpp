#include "source/common.h"
#include "source/feature/players/godmode/godmode.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

std::nullptr_t Hooks::hkPlayer_StartKillingPlayerNetworked(SDK::Player* player, bool a1, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	LOG_DEBUG("Called Player_StartKillingPlayerNetworked");
	if (!globalRunning)
		return SDK::Player_StartKillingPlayerNetworked_ptr(player, a1, photonMessageInfo, methodInfo);

	return dynamic_cast<Features::Players::GodMode*>(featureManager->GetFeatureByName("Players::GodMode"))->OnPlayerStartKillingPlayerNetworked(
		player, a1, photonMessageInfo, methodInfo);
}
