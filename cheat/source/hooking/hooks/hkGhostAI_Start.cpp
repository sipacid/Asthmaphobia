#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkGhostAI_Start(SDK::GhostAI* ghostAI, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called GhostAI_Start")
	if (!globalRunning)
		return SDK::GhostAI_Start_ptr(ghostAI, methodInfo);

	GameState::ghostAI = ghostAI;
	SDK::GhostAI_Start_ptr(ghostAI, methodInfo);
}
