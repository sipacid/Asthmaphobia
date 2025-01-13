#include "rewardmodifier.h"

using namespace Asthmaphobia::Features::Miscellaneous;

RewardModifier::RewardModifier() : Feature("Reward modifier", "Modifies the reward you get from a game", FeatureCategory::Miscellaneous)
{
	InvestigationBonusSetting = std::make_shared<Setting>("Investigation bonus", "The bonus you get from investigating", 1000);
	Settings_->AddSetting(InvestigationBonusSetting);
}

RewardModifier::~RewardModifier() = default;

void RewardModifier::OnEnable()
{
}

void RewardModifier::OnDisable()
{
}

void RewardModifier::OnDraw()
{
}

void RewardModifier::OnMenu()
{
	ImGui::Checkbox("Enabled##rewardModifier", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::InputInt("Investigation bonus##rewardModifier", &std::get<int>(InvestigationBonusSetting->GetValue()));
}

int32_t RewardModifier::OnGetInvestigationBonus(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo) const
{
	if (!std::get<bool>(EnabledSetting->GetValue()))
		return SDK::LevelValues_GetInvestigationBonus_ptr(levelValues, methodInfo);

	return std::get<int>(InvestigationBonusSetting->GetValue());
}
