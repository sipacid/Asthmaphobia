#include "source/common.h"
#include "source/feature/miscellaneous/rewardmodifier/rewardmodifier.h"
#include "source/hooking/hooking.h"

using namespace Asthmaphobia;

int32_t Hooks::hkLevelValues_GetInvestigationBonus(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo)
{
	LOG_CALL("Called LevelValues_GetInvestigationBonus");
	if (!globalRunning)
		return SDK::LevelValues_GetInvestigationBonus_ptr(levelValues, methodInfo);

	return dynamic_cast<Features::Miscellaneous::RewardModifier*>(featureManager->GetFeatureByName("Miscellaneous::RewardModifier"))->OnGetInvestigationBonus(
		levelValues, methodInfo);
}
