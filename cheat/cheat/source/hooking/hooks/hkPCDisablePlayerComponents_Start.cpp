#include "source/common.h"
#include "source/feature/visuals/fullbright/fullbright.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkPCDisablePlayerComponents_Start(SDK::PCDisablePlayerComponents* pcDisablePlayerComponents, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called PCDisablePlayerComponents_Start");
	if (globalRunning)
	{
		GetFeatureManagerInstance().GetFeature<Features::Visuals::FullBright>("Visuals::FullBright")->OnPCDisableComponentsStart(pcDisablePlayerComponents, methodInfo);
	}

	SDK::PCDisablePlayerComponents_Start_ptr(pcDisablePlayerComponents, methodInfo);
}
