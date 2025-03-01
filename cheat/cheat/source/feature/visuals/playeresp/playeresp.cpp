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
	TextBuffer.reserve(BUFFER_RESERVE_SIZE);
}

void PlayerESP::OnDraw()
{
	if (GameState::ghostAI == nullptr)
		return;

	const auto players = Helper::GetPlayers();
	const auto localPlayer = Helper::GetLocalPlayer();

	if (players == nullptr || localPlayer == nullptr)
		return;

	ShowSanity = std::get<bool>(ShowPlayerSanitySetting->GetValue());
	ShowDeadStatus = std::get<bool>(ShowDeadStatusSetting->GetValue());
	Color = std::get<ImColor>(ColorSetting->GetValue());

	const auto draw = ImGui::GetBackgroundDrawList();
	const int playerCount = players->Fields.Size;
	const auto& playerVector = players->Fields.Items->Vector;

	SDK::Vector3 screenPosition;
	for (int playerIndex = 0; playerIndex < playerCount; playerIndex++)
	{
		const auto player = playerVector[playerIndex];
		if (player == nullptr || player == localPlayer)
			continue;

		const auto playerPosition = Helper::GetWorldPosition(player);
		if (!Helper::WorldToScreen(playerPosition, screenPosition))
			continue;

		TextBuffer.clear();
		TextBuffer = Helper::GetPlayerName(player);

		if (ShowDeadStatus && player->Fields.IsDead)
		{
			TextBuffer += " [DEAD]";
		}
		else if (ShowSanity)
		{
			const int sanity = static_cast<int>(100.f - Helper::GetPlayerInsanity(player));
			TextBuffer += " [S: " + std::to_string(sanity) + "%]";
		}

		draw->AddText(ImVec2(screenPosition.X, screenPosition.Y), Color, TextBuffer.c_str());
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
