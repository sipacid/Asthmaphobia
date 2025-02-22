#include "source/common.h"
#include "source/feature/ghost/ghostmodifier/ghostmodifier.h"
#include "source/feature/ghost/interactor/interactor.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkGhostAI_Update(SDK::GhostAI* ghostAI, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called GhostAI_Update");
	if (globalRunning)
	{
		dynamic_cast<Features::Ghost::GhostModifier*>(featureManager->GetFeatureByName("Ghost::GhostModifier"))->OnGhostAIUpdate(ghostAI, methodInfo);
		dynamic_cast<Features::Ghost::Interactor*>(featureManager->GetFeatureByName("Ghost::Interactor"))->OnGhostAIUpdate(ghostAI, methodInfo);
	}

	SDK::GhostAI_Update_ptr(ghostAI, methodInfo);
}
