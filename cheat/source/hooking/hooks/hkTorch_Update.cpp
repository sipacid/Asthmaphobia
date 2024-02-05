#include "source/common.h"
#include "source/feature/visuals/flashlightmodifier/FlashlightModifier.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkTorch_Update(SDK::Torch* torch, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called Torch_Update");
	if (!globalRunning)
		return SDK::Torch_Update_ptr(torch, methodInfo);

	dynamic_cast<Features::Visuals::FlashlightModifier*>(
			featureManager->GetFeatureByName("Visuals::FlashlightModifier"))
		->OnTorch_Update(torch, methodInfo);
}
