#include "source/common.h"
#include "source/feature/miscellaneous/rewardmodifier/rewardmodifier.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

int32_t Hooks::hkLevelValues_GetInestigationBonus(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo)
{
	DEBUG_LOG("Called LevelValues_GetInestigationBonus");
	if (!globalRunning)
		return SDK::LevelValues_GetInestigationBonus_ptr(levelValues, methodInfo);

	return dynamic_cast<Features::Miscellaneous::RewardModifier*>(featureManager->GetFeatureByName("Miscellaneous::RewardModifier"))->OnGetInestigationBonus(
		levelValues, methodInfo);
}
