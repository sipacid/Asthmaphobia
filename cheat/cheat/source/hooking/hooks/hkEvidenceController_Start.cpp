#include "source/common.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

void Hooks::hkEvidenceController_Start(SDK::EvidenceController* evidenceController, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called EvidenceController_Start");
	SDK::EvidenceController_Start_ptr(evidenceController, methodInfo);

	if (globalRunning)
		GameState::evidenceController = evidenceController;
}
