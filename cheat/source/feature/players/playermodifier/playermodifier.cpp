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
	static SDK::Player* selectedPlayer;
	static std::vector<SDK::Player*> frozenPlayers;
	const auto players = Helper::GetPlayers();

	if (!players)
	{
		frozenPlayers.clear();
		selectedPlayer = nullptr;
		return ImGui::Text("You need to be in-game to view this.");
	}
	else if (selectedPlayer == nullptr)
		selectedPlayer = Helper::GetLocalPlayer();

	ImGui::BeginGroup();
	{
		ImGui::BeginListBox("Players", ImVec2(200, 27 * players->Fields.Size));
		{
			for (int i = 0; i < players->Fields.Size; i++)
			{
				const auto player = players->Fields.Items->Vector[i];
				std::string name = Helper::GetPlayerName(player);
				bool isSelectedPlayer = name == Helper::GetPlayerName(selectedPlayer);
				bool isLocalPlayer = player == Helper::GetLocalPlayer();

				//long ass line but does as expected
				isSelectedPlayer ? ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)) : ImGui::PushStyleColor(ImGuiCol_Text, isLocalPlayer ? ImVec4(0.2f, 1.0f, 0.2f, 1.0f) : ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
				if (ImGui::Button(name.c_str()))
					selectedPlayer = player;
				ImGui::PopStyleColor();
			}
		}
		ImGui::EndListBox();
	}
	ImGui::EndGroup();
	ImGui::SameLine();
	ImGui::BeginGroup();
	{
		bool isFrozen = std::find(frozenPlayers.begin(), frozenPlayers.end(), selectedPlayer) != frozenPlayers.end();
		bool isMasterClient = SDK::PhotonNetwork_Get_MasterClient_ptr(nullptr) == selectedPlayer;
		bool isLocalPlayer = selectedPlayer == Helper::GetLocalPlayer();
		std::string name = Helper::GetPlayerName(selectedPlayer);
		static int sanity = 0;

		ImGui::Text(name.c_str());
		ImGui::Text("Sanity: %s", selectedPlayer->Fields.IsDead ? "DEAD" : std::to_string(Helper::GetPlayerSanity(selectedPlayer)).c_str());
		if (const auto levelRoom = selectedPlayer->Fields.LevelRoom; levelRoom && levelRoom->Fields.RoomName)
			ImGui::Text("Current room: %s", Helper::SystemStringToString(*selectedPlayer->Fields.LevelRoom->Fields.RoomName).c_str());

		if (!isLocalPlayer)
		{
			if (ImGui::Button("Teleport"))
				Helper::TeleportPlayerTo(Helper::GetLocalPlayer(), selectedPlayer);
		}
		else //add local only features here
		{
		}

		if (ImGui::Button("Kill"))
			Helper::IsLocalMasterClient() ? SDK::Player_StartKillingPlayer_ptr(selectedPlayer, nullptr) : SDK::Player_KillPlayer_ptr(selectedPlayer, true, nullptr);

		if (Helper::IsLocalMasterClient()) //Master client only options, try to keep these to a minimum
		{
			ImGui::SameLine();
			if (ImGui::Button("Revive"))
				SDK::Player_RevivePlayer_ptr(selectedPlayer, nullptr);
		}

		if (isLocalPlayer || Helper::IsLocalMasterClient())
		{
			if (ImGui::Button(isFrozen ? "UnFreeze" : "Freeze"))
			{
				SDK::Player_ToggleFreezePlayer_ptr(selectedPlayer, !isFrozen, nullptr);
				if (isFrozen)
				{
					auto it = std::find(frozenPlayers.begin(), frozenPlayers.end(), selectedPlayer);
					if (it != frozenPlayers.end())
						frozenPlayers.erase(it);
				}
				else
					frozenPlayers.push_back(selectedPlayer);
			}
			ImGui::PushItemWidth(200);
			ImGui::SliderInt("Santity", &sanity, 0, 100, "%d");
			ImGui::PopItemWidth();
			ImGui::SameLine();
			if (ImGui::Button("Set"))
				SDK::PlayerSanity_SetInsanity_ptr(selectedPlayer->Fields.PlayerSanity, 100 - sanity, nullptr);
		}
	}
	ImGui::EndGroup();
}