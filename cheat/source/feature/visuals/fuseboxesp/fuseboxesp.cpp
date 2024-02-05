#include "fuseboxesp.h"

using namespace Asthmaphobia::Features::Visuals;

FuseBoxESP::FuseBoxESP() : Feature("FuseBox ESP", "Shows where the FuseBox is located", FeatureCategory::Visuals)
{
	ShowStatusSetting = std::make_shared<Setting>("Show status", "Shows the status of the FuseBox", true);
	ColorSetting = std::make_shared<Setting>("Color", "The color of the FuseBox ESP", ImColor(1.0f, 1.0f, 1.0f, 1.0f));
	Settings_->AddSetting(ShowStatusSetting);
	Settings_->AddSetting(ColorSetting);
}

FuseBoxESP::~FuseBoxESP() = default;

void FuseBoxESP::OnEnable()
{
}

void FuseBoxESP::OnDisable()
{
}

void FuseBoxESP::OnDraw()
{
	if (!GameState::fuseBox)
		return;

	const auto fuseBoxPosition = Helper::GetWorldPosition(GameState::fuseBox->Fields.Field8);
	auto text = std::string("Fuse box");

	if (std::get<bool>(ShowStatusSetting->GetValue()))
	{
		text += std::format(": {}", GameState::fuseBox->Fields.IsOn ? "ON" : "OFF");
	}

	SDK::Vector3 screenPosition;
	if (!Helper::WorldToScreen(fuseBoxPosition, screenPosition))
		return;

	const auto draw = ImGui::GetBackgroundDrawList();
	draw->AddText(ImVec2(screenPosition.X, screenPosition.Y), std::get<ImColor>(ColorSetting->GetValue()), text.c_str());
}

void FuseBoxESP::OnMenu()
{
	constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

	ImGui::Checkbox("Enabled##fuseBoxESP", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::SameLine();
	ImGui::ColorEdit4("Color##fuseBoxESP", reinterpret_cast<float*>(&std::get<ImColor>(ColorSetting->GetValue()).Value), colorEditFlags);

	ImGui::Checkbox("Show status##fuseBoxESP", &std::get<bool>(ShowStatusSetting->GetValue()));
}
