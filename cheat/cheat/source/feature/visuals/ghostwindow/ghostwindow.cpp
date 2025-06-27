#include "ghostwindow.h"

using namespace Asthmaphobia::Features::Visuals;

GhostWindow::GhostWindow() : Feature("Ghost window", "Shows ghost information.", FeatureCategory::Visuals)
{
}

void GhostWindow::OnDraw()
{
	if (!GameState::ghostAI || !GameState::ghostAI->Fields.GhostInfo)
		return;

	const auto& ghostInfo = GameState::ghostAI->Fields.GhostInfo;
	const auto& ghostTraits = ghostInfo->Fields.GhostTraits;

	// if the ghost name is null, all the other fields won't be valid either.
	if (!ghostTraits.GhostName)
		return;

	ImGui::Begin("Ghost information", nullptr, WINDOW_FLAGS);

	ImGui::Text("Ghost name: %s", Helper::SystemStringToString(*ghostTraits.GhostName).c_str());
	ImGui::Text("Ghost type: %s", Helper::EnumToString(ghostTraits.InitialGhostType).c_str());

	if (ghostTraits.InitialGhostType == SDK::GhostType::Banshee)
	{
		if (const auto& bansheeTarget = GameState::ghostAI->Fields.BansheeTarget)
			ImGui::Text("Banshee target: %s", Helper::GetPlayerName(bansheeTarget).c_str());
	}

	if (const auto& evidence = GetGhostEvidenceString(); !evidence.empty())
		ImGui::Text("Evidence: %s", evidence.c_str());

	if (const auto& levelRoom = ghostInfo->Fields.FavouriteRoom;
		levelRoom && levelRoom->Fields.RoomName)
	{
		ImGui::Text("Room: %s", Helper::SystemStringToString(*levelRoom->Fields.RoomName).c_str());
	}

	ImGui::Text("Is hunting: %s", GameState::isHunting ? "true" : "false");
	ImGui::End();
}

void GhostWindow::OnMenu()
{
	ImGui::Checkbox("Enabled##ghostWindow", &std::get<bool>(EnabledSetting->GetValue()));
	DrawHotkeyUI();
}

std::string GhostWindow::GetGhostEvidenceString()
{
	const auto& ghostInfo = GameState::ghostAI->Fields.GhostInfo;
	const auto& ghostEvidenceList = ghostInfo->Fields.GhostTraits.Evidences;

	if (!ghostEvidenceList || ghostEvidenceList->Fields.Size == 0)
		return {};

	std::string evidence;
	evidence.reserve(ghostEvidenceList->Fields.Size);

	const auto items = ghostEvidenceList->Fields.Items->Vector;
	for (auto i = 0; i < ghostEvidenceList->Fields.Size; ++i)
	{
		if (i > 0)
			evidence += " | ";
		evidence += Helper::EnumToString(items[i]);
	}

	return evidence;
}
