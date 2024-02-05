#include "playermodifier.h"

using namespace Asthmaphobia::Features::Players;

PlayerModifier::PlayerModifier() : Feature("Player Modifier", "Modify other player in-game stuff", FeatureCategory::Players)
{
}

PlayerModifier::~PlayerModifier() = default;

void PlayerModifier::OnEnable()
{
}

void PlayerModifier::OnDisable()
{
}

void PlayerModifier::OnDraw()
{
}

void PlayerModifier::OnMenu()
{
	const auto players = Helper::GetPlayers();
	if (!players)
		return ImGui::Text("You need to be in-game to view this.");

	for (int playerIndex = 0; playerIndex < players->Fields.Size; playerIndex++)
	{
		const auto player = players->Fields.Items->Vector[playerIndex];
		ImGui::Text("Player: %s", Helper::GetPlayerName(player).c_str());
		ImGui::Text("Sanity: %s", player->Fields.IsDead ? "DEAD" : std::to_string(static_cast<int>(100.f - Helper::GetPlayerInsanity(player))).c_str());
		if (const auto levelRoom = player->Fields.LevelRoom; levelRoom && levelRoom->Fields.RoomName)
			ImGui::Text("Current room: %s", Helper::SystemStringToString(*player->Fields.LevelRoom->Fields.RoomName).c_str());

		if (player != Helper::GetLocalPlayer())
		{
			const auto teleportToLabel = std::format("Teleport to##{}", playerIndex);
			if (ImGui::Button(teleportToLabel.c_str()))
				Helper::TeleportPlayerTo(Helper::GetLocalPlayer(), player);
		}

		if (const auto isLocalMasterClient = Helper::IsLocalMasterClient(); player == Helper::GetLocalPlayer() || isLocalMasterClient)
		{
			const auto killPlayerLabel = std::format("Kill player##{}", playerIndex);
			if (ImGui::Button(killPlayerLabel.c_str()))
				isLocalMasterClient ? SDK::Player_StartKillingPlayer_ptr(player, nullptr) : SDK::Player_KillPlayer_ptr(player, true, nullptr);
			if (isLocalMasterClient)
			{
				ImGui::SameLine();
				const auto revivePlayerLabel = std::format("Revive player##{}", playerIndex);
				if (ImGui::Button(revivePlayerLabel.c_str()))
					SDK::Player_RevivePlayer_ptr(player, nullptr);
			}

			const auto freezePlayerLabel = std::format("Freeze player##{}", playerIndex);
			if (ImGui::Button(freezePlayerLabel.c_str()))
				SDK::Player_ToggleFreezePlayer_ptr(player, true, nullptr);
			ImGui::SameLine();
			const auto unfreezePlayerLabel = std::format("Unfreeze player##{}", playerIndex);
			if (ImGui::Button(unfreezePlayerLabel.c_str()))
				SDK::Player_ToggleFreezePlayer_ptr(player, false, nullptr);

			const auto sanityLabel = std::format("Sanity##i{}", playerIndex);
			ImGui::SliderInt(sanityLabel.c_str(), &SanityArray[playerIndex], 0, 100);
			ImGui::SameLine();
			const auto setSanityLabel = std::format("Set sanity##i{}", playerIndex);
			if (ImGui::Button(setSanityLabel.c_str()))
				SDK::PlayerSanity_SetInsanity_ptr(player->Fields.PlayerSanity, 100 - SanityArray[playerIndex], nullptr);
		}

		ImGui::Separator();
	}
}
