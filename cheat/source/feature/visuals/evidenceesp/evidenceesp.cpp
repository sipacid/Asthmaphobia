#include "evidenceesp.h"

using namespace Asthmaphobia::Features::Visuals;

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

EvidenceESP::~EvidenceESP() = default;

void EvidenceESP::OnEnable()
{
}

void EvidenceESP::OnDisable()
{
}

void EvidenceESP::OnDraw()
{
	if (GameState::evidenceController == nullptr)
		return;

	const auto evidenceList = GameState::evidenceController->Fields.EvidenceList;
	for (int i = 0; i < evidenceList->Fields.Size; i++)
	{
		const auto evidence = evidenceList->Fields.Items->Vector[i];
		const auto photoValues = evidence->Fields.PhotoValues;
		const auto evidenceType = photoValues->Fields.EvidenceType;

		bool shouldDraw = false;
		ImColor color;
		std::string text;

		switch (evidenceType)
		{
		case SDK::EvidenceType::EMFSpot:
			break;
		case SDK::EvidenceType::OuijaBoard:
			shouldDraw = std::get<bool>(CursedItemEnabledSetting->GetValue());
			color = std::get<ImColor>(CursedItemColorSetting->GetValue());
			text = "Ouija Board";
			break;
		case SDK::EvidenceType::Fingerprint:
			break;
		case SDK::EvidenceType::Footstep:
			break;
		case SDK::EvidenceType::DNA:
			shouldDraw = std::get<bool>(DNAEvidenceEnabledSetting->GetValue());
			color = std::get<ImColor>(DNAEvidenceColorSetting->GetValue());
			text = "DNA Evidence";
			break;
		case SDK::EvidenceType::Ghost:
			break;
		case SDK::EvidenceType::DeadBody:
			break;
		case SDK::EvidenceType::DirtyWater:
			break;
		case SDK::EvidenceType::MusicBox:
			shouldDraw = std::get<bool>(CursedItemEnabledSetting->GetValue());
			color = std::get<ImColor>(CursedItemColorSetting->GetValue());
			text = "Music Box";
			break;
		case SDK::EvidenceType::TarotCards:
			shouldDraw = std::get<bool>(CursedItemEnabledSetting->GetValue());
			color = std::get<ImColor>(CursedItemColorSetting->GetValue());
			text = "Tarot Cards";
			break;
		case SDK::EvidenceType::SummoningCircle:
			shouldDraw = std::get<bool>(CursedItemEnabledSetting->GetValue());
			color = std::get<ImColor>(CursedItemColorSetting->GetValue());
			text = "Summoning Circle";
			break;
		case SDK::EvidenceType::HauntedMirror:
			shouldDraw = std::get<bool>(CursedItemEnabledSetting->GetValue());
			color = std::get<ImColor>(CursedItemColorSetting->GetValue());
			text = "Haunted Mirror";
			break;
		case SDK::EvidenceType::VoodooDoll:
			shouldDraw = std::get<bool>(CursedItemEnabledSetting->GetValue());
			color = std::get<ImColor>(CursedItemColorSetting->GetValue());
			text = "Voodoo Doll";
			break;
		case SDK::EvidenceType::GhostWriting:
			break;
		case SDK::EvidenceType::UsedCrucifix:
			break;
		case SDK::EvidenceType::DotsGhost:
			break;
		case SDK::EvidenceType::MonkeyPaw:
			shouldDraw = std::get<bool>(CursedItemEnabledSetting->GetValue());
			color = std::get<ImColor>(CursedItemColorSetting->GetValue());
			text = "Monkey Paw";
			break;
		case SDK::EvidenceType::None:
			break;
		default:
			color = ImColor(255, 255, 255, 255);
			break;
		}

		if (!shouldDraw)
			continue;

		const auto worldPosition = Helper::GetWorldPosition(reinterpret_cast<SDK::Component*>(evidence));
		if (SDK::Vector3 screenPosition; Helper::WorldToScreen(worldPosition, screenPosition))
		{
			const auto draw = ImGui::GetBackgroundDrawList();
			draw->AddText(ImVec2(screenPosition.X, screenPosition.Y), color, text.c_str());
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
