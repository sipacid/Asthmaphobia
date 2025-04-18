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
	std::string ghostTypeString = "Unknown";

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
	}

	return ghostTypeString;
}

std::string Helper::EnumToString(const SDK::GhostEvidence ghostEvidence)
{
	std::string evidenceTypeString = "Unknown";

	switch (ghostEvidence)
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
	}

	return evidenceTypeString;
}

bool Helper::WorldToScreen(const SDK::Vector3 vWorldPosition, SDK::Vector3& vScreenPosition)
{
	RECT rect;
	const HWND hGame = FindWindowA(nullptr, "Phasmophobia");
	GetWindowRect(hGame, &rect);

	const auto screenHeight = rect.bottom - rect.top;
	const auto screenWidth = rect.right;
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

	SDK::Matrix4x4 viewMatrix = SDK::Camera_Get_WorldToCameraMatrix_ptr(camera, nullptr);
	SDK::Matrix4x4 projMatrix = SDK::Camera_Get_ProjectionMatrix_ptr(camera, nullptr);

	// First apply the worldToCamera (view) matrix to convert from world to camera space
	// Matrix multiplication with a point: Matrix * (x,y,z,1)
	// Using Unity's Matrix4x4 field naming: mrc where r=row, c=column
	float camX = viewMatrix.m00 * vWorldPosition.X + viewMatrix.m01 * vWorldPosition.Y +
		viewMatrix.m02 * vWorldPosition.Z + viewMatrix.m03;

	float camY = viewMatrix.m10 * vWorldPosition.X + viewMatrix.m11 * vWorldPosition.Y +
		viewMatrix.m12 * vWorldPosition.Z + viewMatrix.m13;

	float camZ = viewMatrix.m20 * vWorldPosition.X + viewMatrix.m21 * vWorldPosition.Y +
		viewMatrix.m22 * vWorldPosition.Z + viewMatrix.m23;

	float camW = viewMatrix.m30 * vWorldPosition.X + viewMatrix.m31 * vWorldPosition.Y +
		viewMatrix.m32 * vWorldPosition.Z + viewMatrix.m33;

	// Then apply the projection matrix to convert from camera to clip space
	float clipX = projMatrix.m00 * camX + projMatrix.m01 * camY +
		projMatrix.m02 * camZ + projMatrix.m03 * camW;

	float clipY = projMatrix.m10 * camX + projMatrix.m11 * camY +
		projMatrix.m12 * camZ + projMatrix.m13 * camW;

	float clipZ = projMatrix.m20 * camX + projMatrix.m21 * camY +
		projMatrix.m22 * camZ + projMatrix.m23 * camW;

	float clipW = projMatrix.m30 * camX + projMatrix.m31 * camY +
		projMatrix.m32 * camZ + projMatrix.m33 * camW;

	// Check if the point is behind the camera after projection
	if (clipW < 0.1f)
		return false;

	// Perspective divide to get normalized device coordinates
	float ndcX = clipX / clipW;
	float ndcY = clipY / clipW;
	float ndcZ = clipZ / clipW;

	// Transform from NDC to screen coordinates
	vScreenPosition.X = (ndcX * 0.5f + 0.5f) * screenWidth;
	vScreenPosition.Y = (1.0f - (ndcY * 0.5f + 0.5f)) * screenHeight; // Flip Y for screen space
	vScreenPosition.Z = ndcZ;

	return true;
}

SDK::Vector3 Helper::GetWorldPosition(const SDK::Player* player)
{
	return GetWorldPosition(player->Fields.MapIcon);
}

SDK::Vector3 Helper::GetWorldPosition(const SDK::GhostAI* ghostAI)
{
	return GetWorldPosition(ghostAI->Fields.HuntingRaycastPoint);
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

	return GameState::network->Fields.PlayersData->Fields.Items->Vector[GetPlayerIndex(player)];
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
