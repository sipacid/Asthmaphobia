#include "watermark.h"

using namespace Asthmaphobia::Features::Visuals;

Watermark::Watermark() : Feature("Watermark", "Shows a watermark on the screen.", FeatureCategory::Visuals)
{
	ShowAverageSanitySetting = std::make_shared<Setting>("Show average sanity", "Shows the average player sanity", true);
	ShowPingSetting = std::make_shared<Setting>("Show ping", "Shows your ping to the server", true);
	Settings_->AddSetting(ShowAverageSanitySetting);
	Settings_->AddSetting(ShowPingSetting);
}

Watermark::~Watermark() = default;

void Watermark::OnEnable()
{
}

void Watermark::OnDisable()
{
}

void Watermark::OnDraw()
{
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoCollapse;
	windowFlags |= ImGuiWindowFlags_NoTitleBar;
	windowFlags |= ImGuiWindowFlags_AlwaysAutoResize;
	windowFlags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Watermark", nullptr, windowFlags);

	auto text = static_cast<std::string>(cheatName);

	if (std::get<bool>(ShowPingSetting->GetValue()) && SDK::PhotonNetwork_Get_IsConnected_ptr(nullptr))
		text += " | Ping: " + std::to_string(SDK::PhotonNetwork_GetPing_ptr(nullptr)) + " ms";

	if (std::get<bool>(ShowAverageSanitySetting->GetValue()) && GameState::mapController != nullptr && GameState::mapController->Fields.GameController != nullptr)
		text += " | Avg. sanity: " + std::to_string(
			static_cast<int>(100.f - SDK::GameController_GetAveragePlayerInsanity_ptr(GameState::mapController->Fields.GameController, nullptr)));

	ImGui::Text("%s", text.c_str());

	ImGui::End();
}

void Watermark::OnMenu()
{
	ImGui::Checkbox("Enabled##waterMark", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::Checkbox("Show average sanity", &std::get<bool>(ShowAverageSanitySetting->GetValue()));
	ImGui::Checkbox("Show ping", &std::get<bool>(ShowPingSetting->GetValue()));
}
