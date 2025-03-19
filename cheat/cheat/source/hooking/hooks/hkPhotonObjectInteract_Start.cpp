#include "source/common.h"
#include "source/feature/miscellaneous/pickup/pickup.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkPhotonObjectInteract_Start(SDK::PhotonObjectInteract* photonObjectInteract, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called PhotonObjectInteract_Start");
	if (globalRunning)
	{
		GetFeatureManagerInstance().GetFeature<Features::Miscellaneous::Pickup>("Miscellaneous::Pickup")->OnPhotonObjectInteract_Start(photonObjectInteract, methodInfo);
	}

	SDK::PhotonObjectInteract_Start_ptr(photonObjectInteract, methodInfo);
}
