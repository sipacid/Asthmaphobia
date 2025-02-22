#include "helper.h"

#include <KnownFolders.h>
#include <shlobj_core.h>

using namespace Asthmaphobia;

SDK::Network* Helper::GetNetwork()
{
	if (GameState::network)
		return GameState::network;

	SDK::Network* network = SDK::Network_Get_Network_ptr(nullptr);

	if (network == nullptr)
		return nullptr;

	GameState::network = network;

	return network;
}

bool Helper::IsLocalMasterClient()
{
	return SDK::PhotonNetwork_Get_IsMasterClient_ptr(nullptr);
}

SDK::Player* Helper::GetLocalPlayer()
{
	if (!GetNetwork())
		return nullptr;

	return GameState::network->Fields.LocalPlayer;
}

std::string Helper::EnumToString(SDK::GhostType ghostType)
{
	std::string ghostTypeString;

	switch (ghostType)
	{
	case SDK::GhostType::Spirit:
		ghostTypeString = "Spirit";
		break;
	case SDK::GhostType::Wraith:
		ghostTypeString = "Wraith";
		break;
	case SDK::GhostType::Phantom:
		ghostTypeString = "Phantom";
		break;
	case SDK::GhostType::Poltergeist:
		ghostTypeString = "Poltergeist";
		break;
	case SDK::GhostType::Banshee:
		ghostTypeString = "Banshee";
		break;
	case SDK::GhostType::Jinn:
		ghostTypeString = "Jinn";
		break;
	case SDK::GhostType::Mare:
		ghostTypeString = "Mare";
		break;
	case SDK::GhostType::Revenant:
		ghostTypeString = "Revenant";
		break;
	case SDK::GhostType::Shade:
		ghostTypeString = "Shade";
		break;
	case SDK::GhostType::Demon:
		ghostTypeString = "Demon";
		break;
	case SDK::GhostType::Yurei:
		ghostTypeString = "Yurei";
		break;
	case SDK::GhostType::Oni:
		ghostTypeString = "Oni";
		break;
	case SDK::GhostType::Yokai:
		ghostTypeString = "Yokai";
		break;
	case SDK::GhostType::Hantu:
		ghostTypeString = "Hantu";
		break;
	case SDK::GhostType::Goryo:
		ghostTypeString = "Goryo";
		break;
	case SDK::GhostType::Myling:
		ghostTypeString = "Myling";
		break;
	case SDK::GhostType::Onryo:
		ghostTypeString = "Onryo";
		break;
	case SDK::GhostType::TheTwins:
		ghostTypeString = "The Twins";
		break;
	case SDK::GhostType::Raiju:
		ghostTypeString = "Raiju";
		break;
	case SDK::GhostType::Obake:
		ghostTypeString = "Obake";
		break;
	case SDK::GhostType::Mimic:
		ghostTypeString = "Mimic";
		break;
	case SDK::GhostType::Moroi:
		ghostTypeString = "Moroi";
		break;
	case SDK::GhostType::Deogen:
		ghostTypeString = "Deogen";
		break;
	case SDK::GhostType::Thaye:
		ghostTypeString = "Thaye";
		break;
	default:
		ghostTypeString = "Unknown";
		break;
	}

	return ghostTypeString;
}

std::string Helper::EnumToString(const SDK::GhostEvidence* ghostEvidence)
{
	std::string evidenceTypeString;

	switch (*ghostEvidence)
	{
	case SDK::GhostEvidence::None:
		evidenceTypeString = "None";
		break;
	case SDK::GhostEvidence::EMF:
		evidenceTypeString = "EMF Level 5";
		break;
	case SDK::GhostEvidence::SpiritBox:
		evidenceTypeString = "Spirit Box";
		break;
	case SDK::GhostEvidence::Ultraviolet:
		evidenceTypeString = "Ultraviolet";
		break;
	case SDK::GhostEvidence::GhostOrb:
		evidenceTypeString = "Ghost Orb";
		break;
	case SDK::GhostEvidence::GhostWritingBook:
		evidenceTypeString = "Ghost Writing";
		break;
	case SDK::GhostEvidence::Temperature:
		evidenceTypeString = "Freezing Temperature";
		break;
	case SDK::GhostEvidence::DotsProjector:
		evidenceTypeString = "D.O.T.S. Projector";
		break;
	default:
		evidenceTypeString = "Unknown";
		break;
	}

	return evidenceTypeString;
}

bool Helper::WorldToScreen(const SDK::Vector3 vWorldPosition, SDK::Vector3& vScreenPosition)
{
	RECT rect;
	const HWND hGame = FindWindowA(nullptr, "Phasmophobia");
	GetWindowRect(hGame, &rect);

	const auto screenHeight = rect.bottom - rect.top;
	const auto camera = GetLocalPlayer()->Fields.Camera;
	if (camera == nullptr)
		return false;

	const auto cameraTransform = SDK::Component_Get_Transform_ptr(reinterpret_cast<SDK::Component*>(camera), nullptr);
	const auto cameraPos = SDK::Transform_Get_Position_ptr(cameraTransform, nullptr);
	const auto cameraForward = SDK::Transform_Get_Forward_ptr(cameraTransform, nullptr);

	SDK::Vector3 direction;
	direction.X = vWorldPosition.X - cameraPos.X;
	direction.Y = vWorldPosition.Y - cameraPos.Y;
	direction.Z = vWorldPosition.Z - cameraPos.Z;

	const float dot = direction.X * cameraForward.X +
		direction.Y * cameraForward.Y +
		direction.Z * cameraForward.Z;

	if (dot <= 0)
		return false;

	const auto worldToScreen = SDK::Camera_WorldToScreenPoint_ptr(camera, vWorldPosition, nullptr);
	vScreenPosition.X = worldToScreen.X;
	vScreenPosition.Y = static_cast<float>(screenHeight) - worldToScreen.Y;
	vScreenPosition.Z = worldToScreen.Z;

	return true;
}

SDK::Vector3 Helper::GetWorldPosition(const SDK::Player* player)
{
	return GetWorldPosition(player->Fields.Field10);
}

SDK::Vector3 Helper::GetWorldPosition(const SDK::GhostAI* ghostAI)
{
	return GetWorldPosition(ghostAI->Fields.Transform1);
}

SDK::Vector3 Helper::GetWorldPosition(SDK::Component* component)
{
	return GetWorldPosition(SDK::Component_Get_Transform_ptr(component, nullptr));
}

SDK::Vector3 Helper::GetWorldPosition(SDK::Transform* transform)
{
	return SDK::Transform_Get_Position_ptr(transform, nullptr);
}

void Helper::TeleportPlayerTo(SDK::Player* player, const SDK::Vector3& position)
{
	SDK::Player_Teleport_ptr(player, position, nullptr);
}

void Helper::TeleportPlayerTo(SDK::Player* player, const SDK::Player* otherPlayer)
{
	TeleportPlayerTo(player, GetWorldPosition(otherPlayer));
}

void Helper::TeleportPlayerTo(SDK::Player* player, const SDK::GhostAI* ghostAI)
{
	TeleportPlayerTo(player, GetWorldPosition(ghostAI));
}

void Helper::TeleportPlayerTo(SDK::Player* player, SDK::Component* component)
{
	TeleportPlayerTo(player, GetWorldPosition(component));
}

void Helper::TeleportPlayerTo(SDK::Player* player, SDK::Transform* transform)
{
	TeleportPlayerTo(player, GetWorldPosition(transform));
}

SDK::ListPlayer* Helper::GetPlayers()
{
	if (GameState::mapController == nullptr)
		return nullptr;

	return GameState::mapController->Fields.Players;
}

float Helper::GetPlayerInsanity(const SDK::Player* player)
{
	return player->Fields.PlayerSanity->Fields.Insanity;
}

std::string Helper::SystemStringToString(const SDK::String& string)
{
	const int32_t stringLength = string.Fields.StringLength;
	const auto firstCharPtr = &string.Fields.FirstChar;

	std::wstring wideStr(firstCharPtr, firstCharPtr + stringLength);
	std::string result(wideStr.begin(), wideStr.end());

	return result;
}

SDK::String* Helper::StringToSystemString(const std::string& string)
{
	return SDK::Marshal_PtrToStringAnsi_ptr((void*)string.c_str(), nullptr);
}

std::wstring Helper::StringToWString(const std::string& string)
{
	return std::wstring{string.begin(), string.end()};
}

int Helper::GetPlayerIndex(const SDK::Player* player)
{
	const auto players = GetPlayers();
	if (!players)
		return -1;

	for (int playerIndex = 0; playerIndex < players->Fields.Size; playerIndex++)
	{
		if (players->Fields.Items->Vector[playerIndex] == player)
			return playerIndex;
	}

	return -1;
}

SDK::NetworkPlayerSpot* Helper::GetNetworkPlayerSpot(const SDK::Player* player)
{
	if (!GetNetwork())
		return nullptr;

	return GameState::network->Fields.NetworkPlayerSpots->Fields.Items->Vector[GetPlayerIndex(player)];
}

std::string Helper::GetPlayerName(const SDK::Player* player)
{
	try
	{
		const auto networkPlayerSpot = GetNetworkPlayerSpot(player);
		if (networkPlayerSpot == nullptr)
			return {};
		return SystemStringToString(*networkPlayerSpot->Fields.AccountName);
	}
	catch (const std::exception& e)
	{
		LOG_ERROR("Failed to get player name: {}", e.what());
		return {};
	}
}

float Helper::RandomNumber(const float min, const float max)
{
	return min + static_cast<float>(rand()) / (RAND_MAX / (max - min));
}

std::string Helper::GetAsthmaphobiaDirectory()
{
	PWSTR path;
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path);

	std::wstring widePath(path);
	CoTaskMemFree(path);

	const std::string configDirectoryPathA(widePath.begin(), widePath.end());
	return configDirectoryPathA + "\\Asthmaphobia";
}

void Helper::CreateAsthmaphobiaDirectory()
{
	const std::string configDirectoryPath = GetAsthmaphobiaDirectory();
	if (std::filesystem::exists(configDirectoryPath))
		return;

	LOG_INFO("Asthmaphobia directory not found, creating one.");
	std::filesystem::create_directory(configDirectoryPath);
}
