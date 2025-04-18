#include "fuseboxesp.h"

using namespace Asthmaphobia::Features::Visuals;

FuseBoxESP::FuseBoxESP()
	: Feature("FuseBox ESP", "Shows where the FuseBox is located", FeatureCategory::Visuals), TextBuffer()
{
	TextBuffer.reserve(INITIAL_BUFFER_SIZE);
	ShowStatusSetting = std::make_shared<Setting>("Show status", "Shows the status of the FuseBox", true);
	ColorSetting = std::make_shared<Setting>("Color", "The color of the FuseBox ESP", ImColor(1.0f, 1.0f, 1.0f, 1.0f));

	Settings_->AddSetting(ShowStatusSetting);
	Settings_->AddSetting(ColorSetting);
}

void FuseBoxESP::OnDraw()
{
	if (!GameState::fuseBox)
		return;

	const auto& fuseBoxPosition = Helper::GetWorldPosition(GameState::fuseBox->Fields.ParentObject);

	SDK::Vector3 screenPosition;
	if (!Helper::WorldToScreen(fuseBoxPosition, screenPosition))
		return;

	TextBuffer.clear();
	TextBuffer = "Fuse box";

	if (std::get<bool>(ShowStatusSetting->GetValue()))
	{
		TextBuffer += GameState::fuseBox->Fields.IsOn ? ": ON" : ": OFF";
	}

	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2(screenPosition.X, screenPosition.Y),
		std::get<ImColor>(ColorSetting->GetValue()),
		TextBuffer.c_str());
}

void FuseBoxESP::OnMenu()
{
	constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

	ImGui::Checkbox("Enabled##fuseBoxESP", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::SameLine();
	ImGui::ColorEdit4("Color##fuseBoxESP", reinterpret_cast<float*>(&std::get<ImColor>(ColorSetting->GetValue()).Value), colorEditFlags);

	ImGui::Checkbox("Show status##fuseBoxESP", &std::get<bool>(ShowStatusSetting->GetValue()));
}
