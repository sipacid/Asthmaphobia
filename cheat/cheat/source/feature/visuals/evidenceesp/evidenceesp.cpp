#include "evidenceesp.h"

using namespace Asthmaphobia::Features::Visuals;

const std::unordered_map<SDK::EvidenceType, EvidenceESP::EvidenceInfo> EvidenceESP::EVIDENCE_INFO_MAP_ = {
	{SDK::EvidenceType::OuijaBoard, {.Text = "Ouija Board", .IsCursedItem = true}},
	{SDK::EvidenceType::DNA, {.Text = "DNA Evidence", .IsCursedItem = false}},
	{SDK::EvidenceType::MusicBox, {.Text = "Music Box", .IsCursedItem = true}},
	{SDK::EvidenceType::TarotCards, {.Text = "Tarot Cards", .IsCursedItem = true}},
	{SDK::EvidenceType::SummoningCircle, {.Text = "Summoning Circle", .IsCursedItem = true}},
	{SDK::EvidenceType::HauntedMirror, {.Text = "Haunted Mirror", .IsCursedItem = true}},
	{SDK::EvidenceType::VoodooDoll, {.Text = "Voodoo Doll", .IsCursedItem = true}},
	{SDK::EvidenceType::MonkeyPaw, {.Text = "Monkey Paw", .IsCursedItem = true}}
};

EvidenceESP::EvidenceESP() : Feature("Evidence ESP", "Draws the evidence's name on top of the evidence.", FeatureCategory::Visuals)
{
	DNAEvidenceEnabledSetting = std::make_shared<Setting>("DNA Evidence ESP enabled", "If the ESP is enabled", false);
	CursedItemEnabledSetting = std::make_shared<Setting>("Cursed Item ESP enabled", "If the ESP is enabled", false);
	DNAEvidenceColorSetting = std::make_shared<Setting>("DNA Evidence ESP color setting", "The color value of the ESP", ImColor(255, 255, 255, 255));
	CursedItemColorSetting = std::make_shared<Setting>("Cursed Item ESP color setting", "The color value of the ESP", ImColor(255, 255, 255, 255));
	Settings_->AddSetting(DNAEvidenceEnabledSetting);
	Settings_->AddSetting(CursedItemEnabledSetting);
	Settings_->AddSetting(DNAEvidenceColorSetting);
	Settings_->AddSetting(CursedItemColorSetting);
}

void EvidenceESP::OnDraw()
{
	const bool cursedItemEnabled = std::get<bool>(CursedItemEnabledSetting->GetValue());
	const bool dnaEvidenceEnabled = std::get<bool>(DNAEvidenceEnabledSetting->GetValue());

	if (!GameState::evidenceController ||
		(!cursedItemEnabled && !dnaEvidenceEnabled))
		return;

	const auto evidenceList = GameState::evidenceController->Fields.EvidenceList;
	if (!evidenceList || !evidenceList->Fields.Items)
		return;

	const auto& items = evidenceList->Fields.Items->Vector;
	const auto draw = ImGui::GetBackgroundDrawList();
	const auto cursedItemColor = std::get<ImColor>(CursedItemColorSetting->GetValue());
	const auto dnaEvidenceColor = std::get<ImColor>(DNAEvidenceColorSetting->GetValue());

	for (int i = 0; i < evidenceList->Fields.Size; i++)
	{
		const auto evidence = items[i];
		if (!evidence || !evidence->Fields.PhotoValues)
			continue;

		const auto evidenceType = evidence->Fields.PhotoValues->Fields.EvidenceType;
		auto it = EVIDENCE_INFO_MAP_.find(evidenceType);
		if (it == EVIDENCE_INFO_MAP_.end())
			continue;

		const auto& info = it->second;
		const bool shouldDraw = info.IsCursedItem ? cursedItemEnabled : dnaEvidenceEnabled;
		if (!shouldDraw)
			continue;

		const auto worldPosition = Helper::GetWorldPosition(reinterpret_cast<SDK::Component*>(evidence));
		SDK::Vector3 screenPosition;
		if (Helper::WorldToScreen(worldPosition, screenPosition))
		{
			const auto& color = info.IsCursedItem ? cursedItemColor : dnaEvidenceColor;
			draw->AddText(ImVec2(screenPosition.X, screenPosition.Y), color, info.Text.data());
		}
	}
}

void EvidenceESP::OnMenu()
{
	constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

	ImGui::Checkbox("Enabled##evidenceESP", &std::get<bool>(EnabledSetting->GetValue()));

	ImGui::Checkbox("Cursed item##evidenceESP-cursedItem", &std::get<bool>(CursedItemEnabledSetting->GetValue()));
	ImGui::SameLine();
	ImGui::ColorEdit4("Color##evidenceESP-cursedItem", reinterpret_cast<float*>(&std::get<ImColor>(CursedItemColorSetting->GetValue()).Value), colorEditFlags);

	ImGui::Checkbox("DNA evidence##evidenceESP-dnaEvidence", &std::get<bool>(DNAEvidenceEnabledSetting->GetValue()));
	ImGui::SameLine();
	ImGui::ColorEdit4("Color##evidenceESP-dnaEvidence", reinterpret_cast<float*>(&std::get<ImColor>(DNAEvidenceColorSetting->GetValue()).Value), colorEditFlags);
}
