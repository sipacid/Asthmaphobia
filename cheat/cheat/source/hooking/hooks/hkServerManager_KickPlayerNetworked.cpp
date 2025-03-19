#include "source/common.h"
#include "source/feature/exploits/antikick/antikick.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkServerManager_KickPlayerNetworked(SDK::ServerManager* serverManager, bool a1, void* photonMessageInfo, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called ServerManager_KickPlayerNetworked");
	if (globalRunning)
		return GetFeatureManagerInstance().GetFeature<Features::Exploits::AntiKick>("Exploits::AntiKick")->OnServerManagerKickPlayerNetworked(
			serverManager, a1, photonMessageInfo, methodInfo);

	return SDK::ServerManager_KickPlayerNetworked_ptr(serverManager, a1, photonMessageInfo, methodInfo);
}
