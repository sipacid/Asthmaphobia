#include "source/common.h"
#include "source/feature/miscellaneous/rewardmodifier/rewardmodifier.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

bool Hooks::hkLevelValues_IsPerfectGame(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called LevelValues_IsPerfectGame");
	if (!globalRunning)
		return SDK::LevelValues_IsPerfectGame_ptr(levelValues, methodInfo);

	return dynamic_cast<Features::Miscellaneous::RewardModifier*>(featureManager->GetFeatureByName("Miscellaneous::RewardModifier"))->OnIsPerfectGame(
		levelValues, methodInfo);
}
