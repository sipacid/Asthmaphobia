#include "source/common.h"
#include "source/feature/visuals/flashlightmodifier/FlashlightModifier.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkPCDisablePlayerComponents_Start(SDK::PCDisablePlayerComponents* pcDisablePlayerComponents, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called PCDisablePlayerComponents_Start");
	if (!globalRunning)
		return SDK::PCDisablePlayerComponents_Start_ptr(pcDisablePlayerComponents, methodInfo);

	dynamic_cast<Features::Visuals::FlashlightModifier*>(
			featureManager->GetFeatureByName("Visuals::FlashlightModifier"))
		->OnPCDisablePlayerComponents_Start(pcDisablePlayerComponents, methodInfo);
}
