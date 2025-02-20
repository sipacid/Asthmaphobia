#include "source/common.h"
#include "source/feature/miscellaneous/leavepeople/leavepeople.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

bool Hooks::hkExitlevel_ThereAreAlivePlayersOutsideTheTruck(SDK::ExitLevel* exitLevel, SDK::MethodInfo* methodInfo)
{
	LOG_DEBUG("Called ExitLevel_ThereAreAlivePlayersOutsideTheTruck");
	if (!globalRunning)
		return SDK::ExitLevel_ThereAreAlivePlayersOutsideTheTruck_ptr(exitLevel, methodInfo);

	return dynamic_cast<Features::Miscellaneous::LeavePeople*>(
			featureManager->GetFeatureByName("Miscellaneous::LeavePeople"))
		->OnExitLevelThereAreAlivePlayersOutsideTheTruck(exitLevel, methodInfo);
}
