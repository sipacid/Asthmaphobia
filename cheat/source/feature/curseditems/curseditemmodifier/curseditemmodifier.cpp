#include "curseditemmodifier.h"

using namespace Asthmaphobia::Features::CursedItems;

CursedItemModifier::CursedItemModifier() : Feature("CursedItem Modifier", "Modify cursed item behaviour", FeatureCategory::CursedItems)
{
}

CursedItemModifier::~CursedItemModifier() = default;

void CursedItemModifier::OnEnable()
{
}

void CursedItemModifier::OnDisable()
{
}

void CursedItemModifier::OnDraw()
{
}

void CursedItemModifier::OnMenu()
{
	if (ImGui::Button("Break cursed items##cursedItems"))
	{
		if (GameState::cursedItemController == nullptr)
			return AddNotification("You need to be in-game!", Notifications::NotificationType::Info, 3.0f);

		if (DoesCursedItemExist(SDK::CursedItemType::OuijaBoard))
			SDK::CursedItem_BreakItem_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.OuijaBoard), nullptr);

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
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("This will make all cursed items unusable.");

	if (ImGui::Button("Use cursed items##cursedItems"))
	{
		if (GameState::cursedItemController == nullptr)
			return AddNotification("You need to be in-game!", Notifications::NotificationType::Info, 3.0f);

		if (DoesCursedItemExist(SDK::CursedItemType::OuijaBoard))
			SDK::CursedItem_Use_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.OuijaBoard), nullptr);

		if (DoesCursedItemExist(SDK::CursedItemType::MusicBox))
			SDK::CursedItem_Use_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.MusicBox), nullptr);

		if (DoesCursedItemExist(SDK::CursedItemType::TarotCards))
			SDK::CursedItem_Use_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.TarotCards), nullptr);

		if (DoesCursedItemExist(SDK::CursedItemType::HauntedMirror))
			SDK::CursedItem_Use_ptr(static_cast<SDK::CursedItem*>(GameState::cursedItemController->Fields.HauntedMirror), nullptr);
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("This will use the following cursed items: Music Box, Tarot Cards (1 card) and the Haunted Mirror.");
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
