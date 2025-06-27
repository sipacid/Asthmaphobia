#include "ghostesp.h"

using namespace Asthmaphobia::Features::Visuals;

GhostESP::GhostESP() : Feature("Ghost ESP", "Draws the ghost's name above the ghost.", FeatureCategory::Visuals)
{
	ColorSetting = std::make_shared<Setting>("ESP color setting", "The color value of the ESP", ImColor(255, 0, 0, 255));
	Settings_->AddSetting(ColorSetting);
}

void GhostESP::OnDraw()
{
	if (!GameState::ghostAI || !GameState::ghostAI->Fields.GhostInfo)
		return;

	const auto ghostInfo = GameState::ghostAI->Fields.GhostInfo;
	if (!ghostInfo->Fields.GhostTraits.GhostName)
		return;

	const auto ghostPosition = Helper::GetWorldPosition(GameState::ghostAI);

	SDK::Vector3 screenPosition;
	if (!Helper::WorldToScreen(ghostPosition, screenPosition))
		return;

	ImGui::GetBackgroundDrawList()->AddText(
		ImVec2(screenPosition.X, screenPosition.Y),
		std::get<ImColor>(ColorSetting->GetValue()),
		Helper::SystemStringToString(*ghostInfo->Fields.GhostTraits.GhostName).c_str());
}

void GhostESP::OnMenu()
{
	constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

	ImGui::Checkbox("Enabled##ghostESP", &std::get<bool>(EnabledSetting->GetValue()));
	DrawHotkeyUI();
	ImGui::SameLine();
	ImGui::ColorEdit4("Color##ghostESP",
	                  reinterpret_cast<float*>(&std::get<ImColor>(ColorSetting->GetValue()).Value),
	                  colorEditFlags);
}
