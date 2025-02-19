#pragma once
#include "source/common.h"

namespace Asthmaphobia
{
	struct Hooks
	{
		static HRESULT HkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
		static LRESULT HkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static void hkExitLevel_Exit(SDK::ExitLevel* exitLevel, void* photonMessageInfo, SDK::MethodInfo* methodInfo);
		static void hkPauseMenuController_Leave(SDK::PauseMenuController* pauseMenuController, SDK::MethodInfo* methodInfo);
		static void hkGameController_Exit(SDK::GameController* gameController, void* photonMessageInfo, SDK::MethodInfo* methodInfo);
		static void hkGhostAI_Start(SDK::GhostAI* ghostAI, SDK::MethodInfo* methodInfo);
		static void hkGhostAI_Update(SDK::GhostAI* ghostAI, SDK::MethodInfo* methodInfo);
		static void hkGhostAI_Hunting(SDK::GhostAI* ghostAI, bool isHunting, int a1, void* photonMessageInfo, SDK::MethodInfo* methodInfo);
		static void hkEvidenceController_Start(SDK::EvidenceController* evidenceController, SDK::MethodInfo* methodInfo);
		static void hkMapController_Start(SDK::MapController* mapController, SDK::MethodInfo* methodInfo);
		static void hkFuseBox_Start(SDK::FuseBox* fuseBox, SDK::MethodInfo* methodInfo);
		static bool hkExitlevel_ThereAreAlivePlayersOutsideTheTruck(SDK::ExitLevel* exitLevel, SDK::MethodInfo* methodInfo);
		static void hkServerManager_KickPlayerNetworked(SDK::ServerManager* serverManager, bool a1, void* photonMessageInfo, SDK::MethodInfo* methodInfo);
		static std::nullptr_t hkPlayer_StartKillingPlayerNetworked(SDK::Player* player, bool a1, void* photonMessageInfo, SDK::MethodInfo* methodInfo);
		static void hkPlayerStamina_Update(SDK::PlayerStamina* playerStamina, SDK::MethodInfo* methodInfo);
		static void hkFirstPersonController_Update(SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo);
		static void hkTarotCard_SetCard(SDK::TarotCard* tarotCard, SDK::TarotCardType type, SDK::MethodInfo* methodInfo);
		static void hkKey_Start(SDK::Key* key, SDK::MethodInfo* methodInfo);
		static int32_t hkLevelValues_GetInvestigationBonus(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo);
		static bool hkLevelValues_IsPerfectGame(SDK::LevelValues* levelValues, SDK::MethodInfo* methodInfo);
		static void hkDeadZoneController_Awake(SDK::DeadZoneController* deadZoneController, SDK::MethodInfo* methodInfo);
	};
}
