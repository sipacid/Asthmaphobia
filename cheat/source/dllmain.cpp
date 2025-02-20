#include "common.h"
#include "feature/feature.h"
#include "hooking/hooking.h"
#include "menu/menu.h"

using namespace Asthmaphobia;

DWORD WINAPI MainThread()
{
#ifdef _DEBUG
	auto loggerInstance = std::make_unique<Logger>();
#endif

	auto configManagerInstance = std::make_unique<ConfigManager>();
	auto rendererInstance = std::make_unique<Renderer>();
	auto hookingInstance = std::make_unique<Hooking>();
	auto featureManagerInstance = std::make_unique<FeatureManager>();

	ConfigManager::LoadConfig();

	hooking->OriginalPresent = renderer->GetPresent();

	hooking->AddHook("D3D11Present", &reinterpret_cast<PVOID&>(hooking->OriginalPresent), Hooks::HkPresent);
	hooking->AddHook("ExitLevel_Exit", &reinterpret_cast<PVOID&>(SDK::ExitLevel_Exit_ptr), Hooks::hkExitLevel_Exit);
	hooking->AddHook("PauseMenuController_Leave", &reinterpret_cast<PVOID&>(SDK::PauseMenuController_Leave_ptr), Hooks::hkPauseMenuController_Leave);
	hooking->AddHook("GameController_Exit", &reinterpret_cast<PVOID&>(SDK::GameController_Exit_ptr), Hooks::hkGameController_Exit);
	hooking->AddHook("GhostAI_Start", &reinterpret_cast<PVOID&>(SDK::GhostAI_Start_ptr), Hooks::hkGhostAI_Start);
	hooking->AddHook("GhostAI_Update", &reinterpret_cast<PVOID&>(SDK::GhostAI_Update_ptr), Hooks::hkGhostAI_Update);
	hooking->AddHook("GhostAI_Hunting", &reinterpret_cast<PVOID&>(SDK::GhostAI_Hunting_ptr), Hooks::hkGhostAI_Hunting);
	hooking->AddHook("EvidenceController_Start", &reinterpret_cast<PVOID&>(SDK::EvidenceController_Start_ptr), Hooks::hkEvidenceController_Start);
	hooking->AddHook("MapController_Start", &reinterpret_cast<PVOID&>(SDK::MapController_Start_ptr), Hooks::hkMapController_Start);
	hooking->AddHook("FuseBox_Start", &reinterpret_cast<PVOID&>(SDK::FuseBox_Start_ptr), Hooks::hkFuseBox_Start);
	hooking->AddHook("ExitLevel_ThereArePlayersOutsideTheTruck", &reinterpret_cast<PVOID&>(SDK::ExitLevel_ThereAreAlivePlayersOutsideTheTruck_ptr),
	                 Hooks::hkExitlevel_ThereAreAlivePlayersOutsideTheTruck);
	hooking->AddHook("ServerManager_KickPlayerNetworked", &reinterpret_cast<PVOID&>(SDK::ServerManager_KickPlayerNetworked_ptr), Hooks::hkServerManager_KickPlayerNetworked);
	hooking->AddHook("Player_StartKillingPlayerNetworked", &reinterpret_cast<PVOID&>(SDK::Player_StartKillingPlayerNetworked_ptr), Hooks::hkPlayer_StartKillingPlayerNetworked);
	hooking->AddHook("PlayerStamina_Update", &reinterpret_cast<PVOID&>(SDK::PlayerStamina_Update_ptr), Hooks::hkPlayerStamina_Update);
	hooking->AddHook("FirstPersonController_Update", &reinterpret_cast<PVOID&>(SDK::FirstPersonController_Update_ptr), Hooks::hkFirstPersonController_Update);
	hooking->AddHook("TarotCard_SetCard", &reinterpret_cast<PVOID&>(SDK::TarotCard_SetCard_ptr), Hooks::hkTarotCard_SetCard);
	hooking->AddHook("LevelValues_InvestigationBonusReward", &reinterpret_cast<PVOID&>(SDK::LevelValues_GetInvestigationBonus_ptr), Hooks::hkLevelValues_GetInvestigationBonus);
	hooking->AddHook("LevelValues_IsPerfectGame", &reinterpret_cast<PVOID&>(SDK::LevelValues_IsPerfectGame_ptr), Hooks::hkLevelValues_IsPerfectGame);
	hooking->AddHook("DeadZoneController_Awake", &reinterpret_cast<PVOID&>(SDK::DeadZoneController_Awake_ptr), Hooks::hkDeadZoneController_Awake);
	hooking->AddHook("CursedItemController_Awake", &reinterpret_cast<PVOID&>(SDK::CursedItemController_Awake_ptr), Hooks::hkCursedItemController_Awake);
	hooking->ApplyHooks();

#ifdef _DEBUG
	logger->Log(Logger::LogType::Info, "Successfully loaded.");
#endif

	do
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	while (globalRunning);

	ConfigManager::SaveConfig();
	ImGui::SaveIniSettingsToDisk((ConfigManager::GetConfigDirectoryPath() + "\\menu.ini").c_str());

	featureManagerInstance.reset();
	hookingInstance.reset();
	rendererInstance.reset();

#ifdef _DEBUG
	logger->Log(Logger::LogType::Info, "Exiting...");
	loggerInstance.reset();
#endif

	configManagerInstance.reset();

	CloseHandle(mainThread);
	FreeLibraryAndExitThread(globalModule, NULL);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved)
{
	switch (ulReasonForCall)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);

		globalModule = hModule;
		mainThread = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), nullptr, NULL, &mainThreadId);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		globalRunning = false;
		break;
	}
	return TRUE;
}
