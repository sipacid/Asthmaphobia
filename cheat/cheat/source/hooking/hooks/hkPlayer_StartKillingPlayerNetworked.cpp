#include "source/common.h"
#include "source/feature/player/godmode/godmode.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

std::nullptr_t Hooks::hkPlayer_StartKillingPlayerNetworked(SDK::Player* player, bool revive, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called Player_StartKillingPlayerNetworked");
	if (globalRunning)
		return GetFeatureManagerInstance().GetFeature<Features::Player::GodMode>("Player::GodMode")->OnPlayerStartKillingPlayerNetworked(
			player, revive, photonMessageInfo, methodInfo);

	return SDK::Player_StartKillingPlayerNetworked_ptr(player, revive, photonMessageInfo, methodInfo);
}
