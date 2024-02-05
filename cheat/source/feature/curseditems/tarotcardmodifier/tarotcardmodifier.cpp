#include "tarotcardmodifier.h"

using namespace Asthmaphobia::Features::CursedItems;

TarotCardModifier::TarotCardModifier() : Feature("TarotCard Modifier", "Modify tarot card behaviour", FeatureCategory::CursedItems)
{
	ForceTypeSetting = std::make_shared<Setting>("Force type", "Force the type of the tarot card", false);
	ForcedTypeSetting = std::make_shared<Setting>("Forced type", "The type of the tarot card to force", static_cast<int>(SDK::TarotCardType::Fool));
	Settings_->AddSetting(ForceTypeSetting);
	Settings_->AddSetting(ForcedTypeSetting);
}

TarotCardModifier::~TarotCardModifier() = default;

void TarotCardModifier::OnEnable()
{
}

void TarotCardModifier::OnDisable()
{
}

void TarotCardModifier::OnDraw()
{
}

void TarotCardModifier::OnMenu()
{
	ImGui::Checkbox("Enabled##tarotCardModifier", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::Checkbox("Force type##tarotCardModifier", &std::get<bool>(ForceTypeSetting->GetValue()));
	const char* tarotCardList[] = {"Fool", "Wheel Of Fortune", "Tower", "Devil", "Death", "Hermit", "Moon", "Sun", "High Priestess", "Hanged Man"};
	ImGui::Combo("Forced type##tarotCardModifier", &std::get<int>(ForcedTypeSetting->GetValue()), tarotCardList, IM_ARRAYSIZE(tarotCardList));
}

void TarotCardModifier::OnTarotCard_SetCard(SDK::TarotCard* tarotCard, SDK::TarotCardType type, SDK::MethodInfo* methodInfo) const
{
	if (!std::get<bool>(EnabledSetting->GetValue()))
		return SDK::TarotCard_SetCard_ptr(tarotCard, type, methodInfo);

	if (std::get<bool>(ForceTypeSetting->GetValue()))
		type = static_cast<SDK::TarotCardType>(std::get<int>(ForcedTypeSetting->GetValue()));

	SDK::TarotCard_SetCard_ptr(tarotCard, type, methodInfo);
}
