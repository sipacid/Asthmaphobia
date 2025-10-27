#include "source/common.h"
#include "source/feature/exploits/freemouselook/freemouselook.h"
#include "source/feature/movement/noclip/noclip.h"
#include "source/feature/movement/speed/speed.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkFirstPersonController_Update(SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called FirstPersonController_Update");
	if (globalRunning)
	{
		GetFeatureManagerInstance().GetFeature<Features::Movement::Speed>("Movement::Speed")->OnFirstPersonControllerUpdate(firstPersonController, methodInfo);
		GetFeatureManagerInstance().GetFeature<Features::Movement::NoClip>("Movement::NoClip")->OnFirstPersonControllerUpdate(firstPersonController, methodInfo);
		GetFeatureManagerInstance().GetFeature<Features::Exploits::FreeMouseLook>("Exploits::FreeMouseLook")->OnFirstPersonControllerUpdate(
			firstPersonController, methodInfo);
	}

	SDK::FirstPersonController_Update_ptr(firstPersonController, methodInfo);
}
