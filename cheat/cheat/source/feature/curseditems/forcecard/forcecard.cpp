#include "forcecard.h"

using namespace Asthmaphobia::Features::CursedItems;

ForceCard::ForceCard() : Feature("ForceCard", "Force a specific tarot card", FeatureCategory::CursedItems)
{
	ForcedTypeSetting = std::make_shared<Setting>("Forced type", "The type of the tarot card to force", static_cast<int>(SDK::TarotCardType::Fool));
	Settings_->AddSetting(ForcedTypeSetting);
}

void ForceCard::OnMenu()
{
	ImGui::Checkbox("Enabled##tarotCardModifier", &std::get<bool>(EnabledSetting->GetValue()));
	DrawHotkeyUI();
	const char* tarotCardList[] = {"Fool", "Wheel Of Fortune", "Tower", "Devil", "Death", "Hermit", "Moon", "Sun", "High Priestess", "Hanged Man"};
	ImGui::Combo("Forced type##tarotCardModifier", &std::get<int>(ForcedTypeSetting->GetValue()), tarotCardList, IM_ARRAYSIZE(tarotCardList));
}

void ForceCard::OnTarotCardSetCard(SDK::TarotCard* tarotCard, SDK::TarotCardType type, SDK::MethodInfo* methodInfo) const
{
	if (!std::get<bool>(EnabledSetting->GetValue()))
		return SDK::TarotCard_SetCard_ptr(tarotCard, type, methodInfo);

	type = static_cast<SDK::TarotCardType>(std::get<int>(ForcedTypeSetting->GetValue()));

	return SDK::TarotCard_SetCard_ptr(tarotCard, type, methodInfo);
}
