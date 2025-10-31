#include "source/common.h"
#include "source/feature/exploits/rewardmodifier/rewardmodifier.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

int32_t Hooks::hkLevelValues_GetInvestigationBonusReward(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called LevelValues_GetInvestigationBonus");
	if (globalRunning)
		return GetFeatureManagerInstance().GetFeature<Features::Exploits::RewardModifier>("Exploits::RewardModifier")->OnGetInvestigationBonusReward(levelValues, methodInfo);

	return SDK::LevelValues_GetInvestigationBonusReward_ptr(levelValues, methodInfo);
}
