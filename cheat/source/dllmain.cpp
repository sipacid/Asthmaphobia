#include "common.h"
#include "feature/feature.h"
#include "hooking/hooking.h"
#include "menu/menu.h"

using namespace Asthmaphobia;

extern "C" __declspec(dllexport) DWORD WINAPI AsthmaphobiaThread()
{
	static std::unique_ptr<Logger> loggerInstance;
	static std::unique_ptr<ConfigManager> configManagerInstance;
	static std::unique_ptr<Renderer> rendererInstance;
	static std::unique_ptr<Hooking> hookingInstance;
	static std::unique_ptr<FeatureManager> featureManagerInstance;

	try
	{
		loggerInstance = std::make_unique<Logger>();
		configManagerInstance = std::make_unique<ConfigManager>();
		rendererInstance = std::make_unique<Renderer>();
		hookingInstance = std::make_unique<Hooking>();
		featureManagerInstance = std::make_unique<FeatureManager>();

		ConfigManager::LoadConfig();

		hookingInstance->OriginalPresent = rendererInstance->GetPresent();

		hookingInstance->AddHook("D3D11Present", &reinterpret_cast<PVOID&>(hookingInstance->OriginalPresent), Hooks::HkPresent);
		hookingInstance->AddHook("ExitLevel_Exit", &reinterpret_cast<PVOID&>(SDK::ExitLevel_Exit_ptr), Hooks::hkExitLevel_Exit);
		hookingInstance->AddHook("PauseMenuController_Leave", &reinterpret_cast<PVOID&>(SDK::PauseMenuController_Leave_ptr), Hooks::hkPauseMenuController_Leave);
		hookingInstance->AddHook("GameController_Exit", &reinterpret_cast<PVOID&>(SDK::GameController_Exit_ptr), Hooks::hkGameController_Exit);
		hookingInstance->AddHook("GhostAI_Start", &reinterpret_cast<PVOID&>(SDK::GhostAI_Start_ptr), Hooks::hkGhostAI_Start);
		hookingInstance->AddHook("GhostAI_Update", &reinterpret_cast<PVOID&>(SDK::GhostAI_Update_ptr), Hooks::hkGhostAI_Update);
		hookingInstance->AddHook("GhostAI_Hunting", &reinterpret_cast<PVOID&>(SDK::GhostAI_Hunting_ptr), Hooks::hkGhostAI_Hunting);
		hookingInstance->AddHook("EvidenceController_Start", &reinterpret_cast<PVOID&>(SDK::EvidenceController_Start_ptr), Hooks::hkEvidenceController_Start);
		hookingInstance->AddHook("MapController_Start", &reinterpret_cast<PVOID&>(SDK::MapController_Start_ptr), Hooks::hkMapController_Start);
		hookingInstance->AddHook("FuseBox_Start", &reinterpret_cast<PVOID&>(SDK::FuseBox_Start_ptr), Hooks::hkFuseBox_Start);
		hookingInstance->AddHook("ExitLevel_ThereArePlayersOutsideTheTruck", &reinterpret_cast<PVOID&>(SDK::ExitLevel_ThereAreAlivePlayersOutsideTheTruck_ptr),
		                         Hooks::hkExitlevel_ThereAreAlivePlayersOutsideTheTruck);
		hookingInstance->AddHook("ServerManager_KickPlayerNetworked", &reinterpret_cast<PVOID&>(SDK::ServerManager_KickPlayerNetworked_ptr),
		                         Hooks::hkServerManager_KickPlayerNetworked);
		hookingInstance->AddHook("Player_StartKillingPlayerNetworked", &reinterpret_cast<PVOID&>(SDK::Player_StartKillingPlayerNetworked_ptr),
		                         Hooks::hkPlayer_StartKillingPlayerNetworked);
		hookingInstance->AddHook("PlayerStamina_Update", &reinterpret_cast<PVOID&>(SDK::PlayerStamina_Update_ptr), Hooks::hkPlayerStamina_Update);
		hookingInstance->AddHook("FirstPersonController_Update", &reinterpret_cast<PVOID&>(SDK::FirstPersonController_Update_ptr), Hooks::hkFirstPersonController_Update);
		hookingInstance->AddHook("TarotCard_SetCard", &reinterpret_cast<PVOID&>(SDK::TarotCard_SetCard_ptr), Hooks::hkTarotCard_SetCard);
		hookingInstance->AddHook("LevelValues_InvestigationBonusReward", &reinterpret_cast<PVOID&>(SDK::LevelValues_GetInvestigationBonus_ptr),
		                         Hooks::hkLevelValues_GetInvestigationBonus);
		hookingInstance->AddHook("LevelValues_IsPerfectGame", &reinterpret_cast<PVOID&>(SDK::LevelValues_IsPerfectGame_ptr), Hooks::hkLevelValues_IsPerfectGame);
		hookingInstance->AddHook("DeadZoneController_Awake", &reinterpret_cast<PVOID&>(SDK::DeadZoneController_Awake_ptr), Hooks::hkDeadZoneController_Awake);
		hookingInstance->AddHook("CursedItemController_Awake", &reinterpret_cast<PVOID&>(SDK::CursedItemController_Awake_ptr), Hooks::hkCursedItemController_Awake);
		hookingInstance->ApplyHooks();

		LOG_INFO("Successfully loaded.");

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

		LOG_INFO("Exiting...");
		loggerInstance.reset();
		configManagerInstance.reset();
	}
	catch (const std::exception& e)
	{
		LOG_ERROR(std::string("Exception in main Asthmaphobia thread: ") + e.what());
	}

	FreeLibraryAndExitThread(globalModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved)
{
	switch (ulReasonForCall)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		globalModule = hModule;
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		globalRunning = false;
	}
	return TRUE;
}
