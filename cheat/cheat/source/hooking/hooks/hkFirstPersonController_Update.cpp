#include "source/common.h"
#include "source/feature/miscellaneous/freemouselook/freemouselook.h"
#include "source/feature/movement/noclip/noclip.h"
#include "source/feature/movement/speed/speed.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkFirstPersonController_Update(SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called FirstPersonController_Update");
	if (globalRunning)
	{
		GetFeatureManagerInstance().GetFeature<Features::Movement::Speed>("Movement::Speed")->OnFirstPersonController_Update(firstPersonController, methodInfo);
		GetFeatureManagerInstance().GetFeature<Features::Movement::NoClip>("Movement::NoClip")->OnFirstPersonController_Update(firstPersonController, methodInfo);
		GetFeatureManagerInstance().GetFeature<Features::Miscellaneous::FreeMouseLook>("Miscellaneous::FreeMouseLook")->OnFirstPersonController_Update(
			firstPersonController, methodInfo);
	}

	SDK::FirstPersonController_Update_ptr(firstPersonController, methodInfo);
}
