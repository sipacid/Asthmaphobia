#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkGhostAI_Start(SDK::GhostAI* ghostAI, SDK::MethodInfo* methodInfo)
{
	LOG_DEBUG("Called GhostAI_Start");
	SDK::GhostAI_Start_ptr(ghostAI, methodInfo);

	if (globalRunning)
		GameState::ghostAI = ghostAI;
}
