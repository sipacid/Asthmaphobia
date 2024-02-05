#include "source/common.h"
#include "source/feature/visuals/flashlightmodifier/FlashlightModifier.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkPCFlashlight_Update(SDK::PCFlashlight* pcFlashLight, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called PCFlashlight_Update");
	if (!globalRunning)
		return SDK::PCFlashlight_Update_ptr(pcFlashLight, methodInfo);

	dynamic_cast<Features::Visuals::FlashlightModifier*>(
			featureManager->GetFeatureByName("Visuals::FlashlightModifier"))
		->OnPCFlashlight_Update(pcFlashLight, methodInfo);
}
