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

	if (!ghostTraits.Name)
		return;

	ImGui::Begin("Ghost information", nullptr, WINDOW_FLAGS);

	ImGui::Text("Ghost name: %s", Helper::SystemStringToString(*ghostTraits.Name).c_str());
	ImGui::Text("Ghost type: %s", Helper::EnumToString(ghostTraits.GhostType_).c_str());

	switch (ghostTraits.GhostType_)
	{
	case SDK::GhostType::Mimic:
		ImGui::Text("Mimic type: %s", Helper::EnumToString(ghostTraits.MimicType).c_str());
		break;
	case SDK::GhostType::Banshee:
		if (const auto& bansheeTarget = GameState::ghostAI->Fields.BansheeTarget)
			ImGui::Text("Banshee target: %s", Helper::GetPlayerName(bansheeTarget).c_str());
		break;
	default:
		break;
	}

	if (const auto& evidence = GetGhostEvidenceString(); !evidence.empty())
		ImGui::Text("Evidence: %s", evidence.c_str());

	if (const auto& levelRoom = ghostInfo->Fields.LevelRoom;
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
}

std::string GhostWindow::GetGhostEvidenceString()
{
	const auto& ghostInfo = GameState::ghostAI->Fields.GhostInfo;
	const auto& ghostEvidenceList = ghostInfo->Fields.GhostTraits.GhostEvidenceList;

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
