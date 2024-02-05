#include "source/common.h"
#include "source/feature/miscellaneous/godmode/godmode.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

std::nullptr_t Hooks::hkPlayer_StartKillingPlayerNetworked(SDK::Player* player, bool a1, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called Player_StartKillingPlayerNetworked");
	if (!globalRunning)
		return SDK::Player_StartKillingPlayerNetworked_ptr(player, a1, photonMessageInfo, methodInfo);

	return dynamic_cast<Features::Miscellaneous::GodMode*>(featureManager->GetFeatureByName("Miscellaneous::GodMode"))->OnPlayerStartKillingPlayerNetworked(
		player, a1, photonMessageInfo, methodInfo);
}
