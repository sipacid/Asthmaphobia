#include "source/common.h"
#include "source/feature/ghost/ghostmodifier/ghostmodifier.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkGhostAI_Update(SDK::GhostAI* ghostAI, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called GhostAI_Update");
	if (!globalRunning)
		return SDK::GhostAI_Update_ptr(ghostAI, methodInfo);

	dynamic_cast<Features::Ghost::GhostModifier*>(featureManager->GetFeatureByName("Ghost::GhostModifier"))->OnGhostAIUpdate(ghostAI, methodInfo);

	SDK::GhostAI_Update_ptr(ghostAI, methodInfo);
}
