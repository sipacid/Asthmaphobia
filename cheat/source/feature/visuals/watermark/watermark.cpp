#include "watermark.h"

using namespace Asthmaphobia::Features::Visuals;

Watermark::Watermark() : Feature("Watermark", "Shows a watermark on the screen.", FeatureCategory::Visuals)
{
	ShowAverageSanitySetting = std::make_shared<Setting>("Show average sanity", "Shows the average player sanity", true);
	ShowPingSetting = std::make_shared<Setting>("Show ping", "Shows your ping to the server", true);
	Settings_->AddSetting(ShowAverageSanitySetting);
	Settings_->AddSetting(ShowPingSetting);
	CachedText.reserve(128);
}

void Watermark::OnDraw()
{
	ImGui::Begin("Watermark", nullptr, WINDOW_FLAGS);

	CachedText = cheatName;
	const bool showPing = std::get<bool>(ShowPingSetting->GetValue());
	const bool showSanity = std::get<bool>(ShowAverageSanitySetting->GetValue());

	if (showPing && SDK::PhotonNetwork_Get_IsConnected_ptr(nullptr))
	{
		CachedText.append(PING_PREFIX);
		CachedText.append(std::to_string(SDK::PhotonNetwork_GetPing_ptr(nullptr)));
		CachedText.append(" ms");
	}

	if (showSanity && GameState::mapController && GameState::mapController->Fields.GameController)
	{
		CachedText.append(SANITY_PREFIX);
		const int sanity = static_cast<int>(100.f - SDK::GameController_GetAveragePlayerInsanity_ptr(
			GameState::mapController->Fields.GameController, nullptr));
		CachedText.append(std::to_string(sanity));
	}

	ImGui::Text("%s", CachedText.c_str());

	ImGui::End();
}

void Watermark::OnMenu()
{
	ImGui::Checkbox("Enabled##waterMark", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::Checkbox("Show average sanity", &std::get<bool>(ShowAverageSanitySetting->GetValue()));
	ImGui::Checkbox("Show ping", &std::get<bool>(ShowPingSetting->GetValue()));
}
