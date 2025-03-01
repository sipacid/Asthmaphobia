#include "rewardmodifier.h"

using namespace Asthmaphobia::Features::Miscellaneous;

RewardModifier::RewardModifier() : Feature("Reward modifier", "Modifies the reward you get from a game", FeatureCategory::Miscellaneous)
{
	InvestigationBonusSetting = std::make_shared<Setting>("Investigation bonus", "The bonus you get from investigating", 1000);
	PerfectGameSetting = std::make_shared<Setting>("Perfect Game", "Always have a perfect game", false);
	Settings_->AddSetting(InvestigationBonusSetting);
	Settings_->AddSetting(PerfectGameSetting);
}

void RewardModifier::OnMenu()
{
	ImGui::Checkbox("Always perfect game##rewardModifier", &std::get<bool>(PerfectGameSetting->GetValue()));
	ImGui::Checkbox("Enable custom bonus reward##rewardModifier", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::InputInt("Investigation bonus##rewardModifier", &std::get<int>(InvestigationBonusSetting->GetValue()));
}

int32_t RewardModifier::OnGetInvestigationBonus(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo) const
{
	if (!std::get<bool>(EnabledSetting->GetValue()))
		return SDK::LevelValues_GetInvestigationBonus_ptr(levelValues, methodInfo);

	return std::get<int>(InvestigationBonusSetting->GetValue());
}

bool RewardModifier::OnIsPerfectGame(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo) const
{
	if (!std::get<bool>(PerfectGameSetting->GetValue()))
		return SDK::LevelValues_IsPerfectGame_ptr(levelValues, methodInfo);

	return std::get<bool>(PerfectGameSetting->GetValue());
}
