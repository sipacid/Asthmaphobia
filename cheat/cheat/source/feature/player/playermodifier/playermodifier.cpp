#include "playermodifier.h"

using namespace Asthmaphobia::Features::Player;

PlayerModifier::PlayerModifier() : Feature("Player Modifier", "Modify other player in-game stuff", FeatureCategory::Player)
{
}

void PlayerModifier::OnMenu()
{
	const auto players = Helper::GetPlayers();
	if (!players)
		return ImGui::Text("You must be in-game to view this.");

	static int selectedPlayerIndex = -1;

	// Player list as tabs
	ImGui::BeginTabBar("PlayerTabs");
	for (int playerIndex = 0; playerIndex < players->Fields.Size; playerIndex++)
	{
		const auto player = players->Fields.Items->Vector[playerIndex];
		const auto playerName = Helper::GetPlayerName(player).substr(0, 32);
		const bool isLocalPlayer = player == Helper::GetLocalPlayer();
		const bool isDead = player->Fields.IsDead;

		// Create tab label with status indicators
		std::string tabLabel = playerName;
		if (isLocalPlayer) tabLabel += " [Local]";
		if (isDead) tabLabel += " [Dead]";

		if (ImGui::BeginTabItem(tabLabel.c_str()))
		{
			selectedPlayerIndex = playerIndex;
			const auto localPlayer = Helper::GetLocalPlayer();
			const bool isLocalMasterClient = Helper::IsLocalMasterClient();

			// Player info
			ImGui::Text("Status: %s", player->Fields.IsDead ? "Dead" : "Alive");
			ImGui::Text("Sanity: %d%%", static_cast<int>(100.f - Helper::GetPlayerInsanity(player)));

			if (const auto levelRoom = player->Fields.LevelRoom; levelRoom && levelRoom->Fields.RoomName)
				ImGui::Text("Current Room: %s", Helper::SystemStringToString(*levelRoom->Fields.RoomName).c_str());

			ImGui::Separator();

			// Actions
			if (!isLocalPlayer)
			{
				if (ImGui::Button("Teleport to Player", ImVec2(-1, 0)))
					Helper::TeleportPlayerTo(localPlayer, player);
			}

			if (isLocalMasterClient || isLocalPlayer)
			{
				if (!player->Fields.IsDead)
				{
					if (ImGui::Button("Kill Player", ImVec2(-1, 0)))
					{
						isLocalMasterClient
							? SDK::Player_StartKillingPlayer_ptr(player, nullptr)
							: SDK::Player_KillPlayer_ptr(player, true, nullptr);
					}
				}

				if (!player->Fields.IsDead)
				{
					ImGui::Spacing();
					ImGui::Text("Sanity Control");
					ImGui::SliderInt("Level", &SanityArray[playerIndex], 0, 100);
					if (ImGui::Button("Apply", ImVec2(-1, 0)))
					{
						SDK::PlayerSanity_SetInsanity_ptr(player->Fields.PlayerSanity,
						                                  100 - SanityArray[playerIndex],
						                                  nullptr);
					}
				}
			}

			ImGui::EndTabItem();
		}
	}
	ImGui::EndTabBar();
}
