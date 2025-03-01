#include "source/common.h"
#include "source/feature/miscellaneous/rewardmodifier/rewardmodifier.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

bool Hooks::hkLevelValues_IsPerfectGame(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called LevelValues_IsPerfectGame");
	if (globalRunning)
		return featureManager->GetFeature<Features::Miscellaneous::RewardModifier>("Miscellaneous::RewardModifier")->OnIsPerfectGame(levelValues, methodInfo);

	return SDK::LevelValues_IsPerfectGame_ptr(levelValues, methodInfo);
}
