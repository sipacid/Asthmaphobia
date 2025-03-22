#include "curseditemmodifier.h"

using namespace Asthmaphobia::Features::CursedItems;

CursedItemModifier::CursedItemModifier() : Feature("CursedItem Modifier", "Modify cursed item behaviour", FeatureCategory::CursedItems)
{
	CustomMessageSetting = std::make_unique<Setting>("CustomMessage", "Custom ouija board message", "meow");
	Settings_->AddSetting(CustomMessageSetting);
}

void CursedItemModifier::OnMenu()
{
	ImGui::InputText("##cursedItemModifierMessage", MessageBuffer, IM_ARRAYSIZE(MessageBuffer));
	ImGui::SameLine();
	if (ImGui::Button("Send message##cursedItemModifierMessage"))
	{
		if (GameState::cursedItemController == nullptr)
		{
			AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else if (!Helper::IsLocalMasterClient())
		{
			AddNotification("You must be host to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else
		{
			CustomMessageSetting->SetValue(std::string(MessageBuffer));
			SendOuijaBoardMessage = true;
		}
	}

	if (ImGui::Button("Break cursed items##cursedItems"))
	{
		if (GameState::cursedItemController == nullptr)
		{
			AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else if (!Helper::IsLocalMasterClient())
		{
			AddNotification("You must be the host to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else
		{
			if (DoesCursedItemExist(SDK::CursedItemType::OuijaBoard))
				SDK::CursedItem_BreakItem_ptr(reinterpret_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.OuijaBoard), nullptr);

			if (DoesCursedItemExist(SDK::CursedItemType::MusicBox))
				SDK::CursedItem_BreakItem_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.MusicBox), nullptr);

			if (DoesCursedItemExist(SDK::CursedItemType::TarotCards))
				SDK::CursedItem_BreakItem_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.TarotCards), nullptr);

			if (DoesCursedItemExist(SDK::CursedItemType::SummoningCircle))
				SDK::CursedItem_BreakItem_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.SummoningCircle), nullptr);

			if (DoesCursedItemExist(SDK::CursedItemType::HauntedMirror))
				SDK::CursedItem_BreakItem_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.HauntedMirror), nullptr);

			if (DoesCursedItemExist(SDK::CursedItemType::VoodooDoll))
				SDK::CursedItem_BreakItem_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.VoodooDoll), nullptr);

			if (DoesCursedItemExist(SDK::CursedItemType::MonkeyPaw))
				SDK::CursedItem_BreakItem_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.MonkeyPaw), nullptr);
		}
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("This will make all cursed items unusable.");

	if (ImGui::Button("Use cursed items##cursedItems"))
	{
		if (GameState::cursedItemController == nullptr)
		{
			AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else
		{
			if (DoesCursedItemExist(SDK::CursedItemType::OuijaBoard))
				SDK::CursedItem_Use_ptr(reinterpret_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.OuijaBoard), nullptr);

			if (DoesCursedItemExist(SDK::CursedItemType::MusicBox))
				SDK::CursedItem_Use_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.MusicBox), nullptr);

			if (DoesCursedItemExist(SDK::CursedItemType::TarotCards))
				SDK::CursedItem_Use_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.TarotCards), nullptr);

			if (DoesCursedItemExist(SDK::CursedItemType::HauntedMirror))
				SDK::CursedItem_Use_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.HauntedMirror), nullptr);
		}
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("This will use the following cursed items: Music Box, Tarot Cards (1 card) and the Haunted Mirror.");
}

void CursedItemModifier::OnGhostAIUpdate(SDK::GhostAI* ghost, SDK::MethodInfo* methodInfo)
{
	if (!SendOuijaBoardMessage || GameState::cursedItemController->Fields.OuijaBoard == nullptr) return;

	SDK::OuijaBoard_SendMessage_ptr(GameState::cursedItemController->Fields.OuijaBoard, Helper::StringToSystemString(std::get<std::string>(CustomMessageSetting->GetValue())),
	                                nullptr);
	SendOuijaBoardMessage = false;
}

bool CursedItemModifier::DoesCursedItemExist(const SDK::CursedItemType cursedItemType)
{
	const auto cursedItems = GameState::cursedItemController->Fields.CursedItems;
	for (int i = 0; i < cursedItems->Fields.Size; i++)
	{
		if (cursedItems->Fields.Items->Vector[i] == cursedItemType)
		{
			return true;
		}
	}

	return false;
}
