#include "source/common.h"
#include "source/feature/miscellaneous/freemouselook/freemouselook.h"
#include "source/feature/movement/noclip/noclip.h"
#include "source/feature/movement/speed/speed.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkFirstPersonController_Update(SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called FirstPersonController_Update")
	if (!globalRunning)
		return SDK::FirstPersonController_Update_ptr(firstPersonController, methodInfo);

	dynamic_cast<Features::Movement::Speed*>(featureManager->GetFeatureByName("Movement::Speed"))->OnFirstPersonController_Update(firstPersonController, methodInfo);
	dynamic_cast<Features::Movement::NoClip*>(featureManager->GetFeatureByName("Movement::NoClip"))->OnFirstPersonController_Update(firstPersonController, methodInfo);
	dynamic_cast<Features::Miscellaneous::FreeMouseLook*>(featureManager->GetFeatureByName("Miscellaneous::FreeMouseLook"))->OnFirstPersonController_Update(
		firstPersonController, methodInfo);

	SDK::FirstPersonController_Update_ptr(firstPersonController, methodInfo);
}
