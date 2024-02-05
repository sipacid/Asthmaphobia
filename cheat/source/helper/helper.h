#pragma once
#include "source/common.h"

namespace Asthmaphobia::Helper
{
	SDK::Network* GetNetwork();
	bool IsLocalMasterClient();
	SDK::Player* GetLocalPlayer();
	std::string EnumToString(SDK::GhostType ghostType);
	std::string EnumToString(const SDK::GhostEvidence* ghostEvidence);
	bool WorldToScreen(SDK::Vector3 vWorldPosition, SDK::Vector3& vScreenPosition);
	SDK::Vector3 GetWorldPosition(const SDK::Player* player);
	SDK::Vector3 GetWorldPosition(const SDK::GhostAI* ghostAI);
	SDK::Vector3 GetWorldPosition(SDK::Component* component);
	SDK::Vector3 GetWorldPosition(SDK::Transform* transform);
	void TeleportPlayerTo(SDK::Player* player, const SDK::Vector3& position);
	void TeleportPlayerTo(SDK::Player* player, const SDK::Player* otherPlayer);
	void TeleportPlayerTo(SDK::Player* player, const SDK::GhostAI* ghostAI);
	void TeleportPlayerTo(SDK::Player* player, SDK::Component* component);
	void TeleportPlayerTo(SDK::Player* player, SDK::Transform* transform);
	SDK::ListPlayer* GetPlayers();
	float GetPlayerInsanity(const SDK::Player* player);
	std::string SystemStringToString(const SDK::String& string);
	SDK::String* StringToSystemString(const std::string& string);
	std::wstring StringToWString(const std::string& string);
	int GetPlayerIndex(const SDK::Player* player);
	SDK::NetworkPlayerSpot* GetNetworkPlayerSpot(const SDK::Player* player);
	std::string GetPlayerName(const SDK::Player* player);
}
