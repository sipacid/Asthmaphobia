#include "ghostesp.h"

using namespace Asthmaphobia::Features::Visuals;

GhostESP::GhostESP() : Feature("Ghost ESP", "Draws the ghost's name above the ghost.", FeatureCategory::Visuals)
{
	ColorSetting = std::make_shared<Setting>("ESP color setting", "The color value of the ESP", ImColor(255, 0, 0, 255));
	Settings_->AddSetting(ColorSetting);
}

GhostESP::~GhostESP() = default;

void GhostESP::OnEnable()
{
}

void GhostESP::OnDisable()
{
}

void GhostESP::OnDraw()
{
	if (GameState::ghostAI == nullptr)
		return;

	const auto ghostInfo = GameState::ghostAI->Fields.GhostInfo;
	if (ghostInfo == nullptr)
		return;

	const auto ghostTraits = ghostInfo->Fields.GhostTraits;
	const auto ghostName = ghostTraits.Name;
	if (ghostName == nullptr)
		return;
	if (std::get<bool>(ForceAppearSetting->GetValue()))
		SDK::GhostAI_Appear_ptr(GameState::ghostAI, 0, nullptr); //force ghost appearance, test if others see...
	const auto ghostPosition = Helper::GetWorldPosition(GameState::ghostAI);

	SDK::Vector3 screenPosition;
	if (!Helper::WorldToScreen(ghostPosition, screenPosition))
		return;

	const auto draw = ImGui::GetBackgroundDrawList();
	draw->AddText(ImVec2(screenPosition.X, screenPosition.Y), std::get<ImColor>(ColorSetting->GetValue()), Helper::SystemStringToString(*ghostName).c_str());
}

void GhostESP::OnMenu()
{
	constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

	ImGui::Checkbox("Enabled##ghostESP", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::SameLine();
	ImGui::ColorEdit4("Color##ghostESP", reinterpret_cast<float*>(&std::get<ImColor>(ColorSetting->GetValue()).Value), colorEditFlags);
	if (Helper::IsLocalMasterClient()) //game crashes if used when not materclient. Wonder what other ways we can get it to appear
	{
		ImGui::Checkbox("Force Appear", &std::get<bool>(ForceAppearSetting->GetValue()));
		if (ImGui::Button("Appear"))
			SDK::GhostAI_Appear_ptr(GameState::ghostAI, 0, nullptr);
	}
}
