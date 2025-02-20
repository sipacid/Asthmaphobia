#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkEvidenceController_Start(SDK::EvidenceController* evidenceController, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called EvidenceController_Start")
	if (!globalRunning)
		return SDK::EvidenceController_Start_ptr(evidenceController, methodInfo);

	GameState::evidenceController = evidenceController;
	SDK::EvidenceController_Start_ptr(evidenceController, methodInfo);
}
