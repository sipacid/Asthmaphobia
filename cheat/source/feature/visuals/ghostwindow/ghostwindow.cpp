#include "ghostwindow.h"

using namespace Asthmaphobia::Features::Visuals;

GhostWindow::GhostWindow() : Feature("Ghost window", "Shows ghost information.", FeatureCategory::Visuals)
{
}

GhostWindow::~GhostWindow() = default;

void GhostWindow::OnEnable()
{
}

void GhostWindow::OnDisable()
{
}

void GhostWindow::OnDraw()
{
	if (GameState::ghostAI == nullptr)
		return;

	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoCollapse;
	windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
	windowFlags |= ImGuiWindowFlags_NoResize;

	const auto ghostInfo = GameState::ghostAI->Fields.GhostInfo;
	if (ghostInfo == nullptr)
		return;

	const auto ghostTraits = ghostInfo->Fields.GhostTraits;
	const auto ghostName = ghostTraits.Name;
	if (!ghostName)
		return;

	ImGui::Begin("Ghost information", nullptr, windowFlags);
	ImGui::Text("Ghost name: %s", Helper::SystemStringToString(*ghostName).c_str());

	const auto ghostType = ghostTraits.GhostType_;
	ImGui::Text("Ghost type: %s", Helper::EnumToString(ghostType).c_str());

	if (ghostType == SDK::GhostType::Mimic)
	{
		const auto mimicType = ghostTraits.MimicType;
		ImGui::Text("Mimic type: %s", Helper::EnumToString(mimicType).c_str());
	}

	else if (ghostType == SDK::GhostType::Banshee && GameState::ghostAI->Fields.BansheeTarget != nullptr)
	{
		const auto bansheeTarget = GameState::ghostAI->Fields.BansheeTarget;
		ImGui::Text("Banshee target: %s", Helper::GetPlayerName(bansheeTarget).c_str());
	}

	const auto ghostEvidence = GetGhostEvidenceString();
	if (!ghostEvidence.empty())
		ImGui::Text("Evidence: %s", ghostEvidence.c_str());

	if (const auto levelRoom = ghostInfo->Fields.LevelRoom; levelRoom && levelRoom->Fields.RoomName)
		ImGui::Text("Room: %s", Helper::SystemStringToString(*levelRoom->Fields.RoomName).c_str());

	ImGui::Text("Is hunting: %s", GameState::isHunting ? "true" : "false");

	ImGui::End();
}

void GhostWindow::OnMenu()
{
	ImGui::Checkbox("Enabled##ghostWindow", &std::get<bool>(EnabledSetting->GetValue()));
}

std::string GhostWindow::GetGhostEvidenceString()
{
	const auto ghostInfo = GameState::ghostAI->Fields.GhostInfo;
	const auto ghostTraits = ghostInfo->Fields.GhostTraits;
	const auto ghostEvidenceList = ghostTraits.GhostEvidenceList;
	if (!ghostEvidenceList)
		return "";

	std::string ghostEvidenceString;

	for (auto i = 0; i < ghostEvidenceList->Fields.Size; i++)
	{
		const auto ghostEvidence = ghostEvidenceList->Fields.Items->Vector + i;
		ghostEvidenceString += Helper::EnumToString(ghostEvidence);
		if (i < ghostEvidenceList->Fields.Size - 1)
			ghostEvidenceString += " | ";
	}

	return ghostEvidenceString;
}
