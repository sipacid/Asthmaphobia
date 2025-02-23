#include "source/common.h"
#include "source/feature/miscellaneous/leavepeople/leavepeople.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

bool Hooks::hkExitlevel_ThereAreAlivePlayersOutsideTheTruck(SDK::ExitLevel* exitLevel, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called ExitLevel_ThereAreAlivePlayersOutsideTheTruck");
	if (globalRunning)
		return featureManager->GetFeature<Features::Miscellaneous::LeavePeople>("Miscellaneous::LeavePeople")->
		                       OnExitLevelThereAreAlivePlayersOutsideTheTruck(exitLevel, methodInfo);

	return SDK::ExitLevel_ThereAreAlivePlayersOutsideTheTruck_ptr(exitLevel, methodInfo);
}
