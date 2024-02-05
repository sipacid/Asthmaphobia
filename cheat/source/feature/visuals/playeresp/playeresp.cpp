#include "playeresp.h"

using namespace Asthmaphobia::Features::Visuals;

PlayerESP::PlayerESP() : Feature("Player ESP", "Draws players name and/or sanity above players.", FeatureCategory::Visuals)
{
	ShowPlayerSanitySetting = std::make_shared<Setting>("Draw player sanity", "Draws the player sanity next to their name", true);
	ShowDeadStatusSetting = std::make_shared<Setting>("Draw player alive status", "Draws the player's alive status next to their name", true);
	ColorSetting = std::make_shared<Setting>("ESP color setting", "The color value of the ESP", ImColor(255, 255, 255, 255));
	Settings_->AddSetting(ShowPlayerSanitySetting);
	Settings_->AddSetting(ShowDeadStatusSetting);
	Settings_->AddSetting(ColorSetting);
}

PlayerESP::~PlayerESP() = default;

void PlayerESP::OnEnable()
{
}

void PlayerESP::OnDisable()
{
}

void PlayerESP::OnDraw()
{
	if (GameState::ghostAI == nullptr)
		return;

	const auto players = Helper::GetPlayers();
	const auto localPlayer = Helper::GetLocalPlayer();

	if (players == nullptr || localPlayer == nullptr)
		return;

	for (int playerIndex = 0; playerIndex < players->Fields.Size; playerIndex++)
	{
		const auto player = players->Fields.Items->Vector[playerIndex];
		if (player == nullptr || player == localPlayer)
			continue;

		const auto playerPosition = Helper::GetWorldPosition(player);
		SDK::Vector3 screenPosition;
		if (!Helper::WorldToScreen(playerPosition, screenPosition))
			continue;

		auto text = Helper::GetPlayerName(player);
		if (std::get<bool>(ShowDeadStatusSetting->GetValue()) && player->Fields.IsDead)
			text += " [DEAD]";

		else if (std::get<bool>(ShowPlayerSanitySetting->GetValue()))
			text += std::format(" [S: {}%]", std::to_string(static_cast<int>(100.f - Helper::GetPlayerInsanity(player))));

		const auto draw = ImGui::GetBackgroundDrawList();
		draw->AddText(ImVec2(screenPosition.X, screenPosition.Y), std::get<ImColor>(ColorSetting->GetValue()), text.c_str());
	}
}

void PlayerESP::OnMenu()
{
	constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

	ImGui::Checkbox("Enabled##playerESP", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::SameLine();
	ImGui::ColorEdit4("Color##playerESP", reinterpret_cast<float*>(&std::get<ImColor>(ColorSetting->GetValue()).Value), colorEditFlags);

	ImGui::Checkbox("Show player sanity", &std::get<bool>(ShowPlayerSanitySetting->GetValue()));
	ImGui::Checkbox("Show dead status", &std::get<bool>(ShowDeadStatusSetting->GetValue()));
}
