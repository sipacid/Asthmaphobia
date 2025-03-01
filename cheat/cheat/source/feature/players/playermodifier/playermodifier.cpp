#include "playermodifier.h"

using namespace Asthmaphobia::Features::Players;

PlayerModifier::PlayerModifier() : Feature("Player Modifier", "Modify other player in-game stuff", FeatureCategory::Players)
{
}

void PlayerModifier::OnMenu()
{
	const auto players = Helper::GetPlayers();
	if (!players)
		return ImGui::Text("You must be in-game to view this.");

	for (int playerIndex = 0; playerIndex < players->Fields.Size; playerIndex++)
	{
		const auto localPlayer = Helper::GetLocalPlayer();
		const auto player = players->Fields.Items->Vector[playerIndex];
		ImGui::Text("Player: %s", Helper::GetPlayerName(player).c_str());
		ImGui::Text("Sanity: %s", player->Fields.IsDead ? "DEAD" : std::to_string(static_cast<int>(100.f - Helper::GetPlayerInsanity(player))).c_str());
		if (const auto levelRoom = player->Fields.LevelRoom; levelRoom && levelRoom->Fields.RoomName)
			ImGui::Text("Current room: %s", Helper::SystemStringToString(*player->Fields.LevelRoom->Fields.RoomName).c_str());

		// Teleport button
		const auto teleportToLabel = std::format("Teleport to##{}", playerIndex);
		if (ImGui::Button(teleportToLabel.c_str()))
		{
			if (localPlayer == player)
			{
				AddNotification("You can't teleport to yourself.", Notifications::NotificationType::Error, 3.0f);
			}
			else
			{
				Helper::TeleportPlayerTo(localPlayer, player);
			}
		}

		if (const auto isLocalMasterClient = Helper::IsLocalMasterClient(); player == Helper::GetLocalPlayer() || isLocalMasterClient)
		{
			// Kill player button
			const auto killPlayerLabel = std::format("Kill player##{}", playerIndex);
			if (ImGui::Button(killPlayerLabel.c_str()))
			{
				if (player->Fields.IsDead)
				{
					AddNotification("Player is already dead.", Notifications::NotificationType::Error, 3.0f);
				}
				else
				{
					isLocalMasterClient ? SDK::Player_StartKillingPlayer_ptr(player, nullptr) : SDK::Player_KillPlayer_ptr(player, true, nullptr);
				}
			}

			// Freeze/Unfreeze buttons
			const auto freezePlayerLabel = std::format("Freeze player##{}", playerIndex);
			if (ImGui::Button(freezePlayerLabel.c_str()))
				SDK::Player_ToggleFreezePlayer_ptr(player, true, nullptr);
			ImGui::SameLine();
			const auto unfreezePlayerLabel = std::format("Unfreeze player##{}", playerIndex);
			if (ImGui::Button(unfreezePlayerLabel.c_str()))
				SDK::Player_ToggleFreezePlayer_ptr(player, false, nullptr);

			// Sanity controls
			const auto sanityLabel = std::format("Sanity##i{}", playerIndex);
			ImGui::SliderInt(sanityLabel.c_str(), &SanityArray[playerIndex], 0, 100);
			ImGui::SameLine();

			const auto setSanityLabel = std::format("Set sanity##i{}", playerIndex);
			if (ImGui::Button(setSanityLabel.c_str()))
			{
				if (player->Fields.IsDead)
				{
					AddNotification("Player is already dead.", Notifications::NotificationType::Error, 3.0f);
				}
				else
				{
					SDK::PlayerSanity_SetInsanity_ptr(player->Fields.PlayerSanity, 100 - SanityArray[playerIndex], nullptr);
				}
			}
		}

		ImGui::Separator();
	}
}
