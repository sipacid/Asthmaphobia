#include "common.h"
#include "feature/feature.h"
#include "hooking/hooking.h"
#include "menu/menu.h"

using namespace Asthmaphobia;

extern "C" __declspec(dllexport) DWORD WINAPI AsthmaphobiaThread()
{
	try
	{
		// Initialise the logger before anything else, in case something goes wrong.
		auto& logger = GetLoggerInstance();

		if (!SDK::InitializeSDK())
		{
			throw std::runtime_error("Failed to initialize SDK");
		}

		auto& hooking = GetHookingInstance();
		auto& renderer = GetRendererInstance();
		auto& featureManager = GetFeatureManagerInstance();

		Config::LoadConfig();

		hooking.OriginalPresent = renderer.GetPresent();

		hooking.AddHook("D3D11Present", &hooking.OriginalPresent, Hooks::HkPresent);
		hooking.AddHook("ExitLevel_Exit", &SDK::ExitLevel_Exit_ptr, Hooks::hkExitLevel_Exit);
		hooking.AddHook("PauseMenuController_Leave", &SDK::PauseMenuController_Leave_ptr, Hooks::hkPauseMenuController_Leave);
		hooking.AddHook("GameController_Exit", &SDK::GameController_Exit_ptr, Hooks::hkGameController_Exit);
		hooking.AddHook("GhostAI_Start", &SDK::GhostAI_Start_ptr, Hooks::hkGhostAI_Start);
		hooking.AddHook("GhostAI_Update", &SDK::GhostAI_Update_ptr, Hooks::hkGhostAI_Update);
		hooking.AddHook("GhostAI_Hunting", &SDK::GhostAI_Hunting_ptr, Hooks::hkGhostAI_Hunting);
		hooking.AddHook("EMFData_Start", &SDK::EMFData_Start_ptr, Hooks::hkEMFData_Start);
		hooking.AddHook("EvidenceController_Start", &SDK::EvidenceController_Start_ptr, Hooks::hkEvidenceController_Start);
		hooking.AddHook("MapController_Start", &SDK::MapController_Start_ptr, Hooks::hkMapController_Start);
		hooking.AddHook("FuseBox_Start", &SDK::FuseBox_Start_ptr, Hooks::hkFuseBox_Start);
		hooking.AddHook("ExitLevel_ThereArePlayersOutsideTheTruck", &SDK::ExitLevel_ThereAreAlivePlayersOutsideTheTruck_ptr,
		                Hooks::hkExitlevel_ThereAreAlivePlayersOutsideTheTruck);
		hooking.AddHook("ServerManager_KickPlayerNetworked", &SDK::ServerManager_KickPlayerNetworked_ptr,
		                Hooks::hkServerManager_KickPlayerNetworked);
		hooking.AddHook("Player_StartKillingPlayerNetworked", &SDK::Player_StartKillingPlayerNetworked_ptr,
		                Hooks::hkPlayer_StartKillingPlayerNetworked);
		hooking.AddHook("PlayerStamina_Update", &SDK::PlayerStamina_Update_ptr, Hooks::hkPlayerStamina_Update);
		hooking.AddHook("FirstPersonController_Update", &SDK::FirstPersonController_Update_ptr, Hooks::hkFirstPersonController_Update);
		hooking.AddHook("TarotCard_SetCard", &SDK::TarotCard_SetCard_ptr, Hooks::hkTarotCard_SetCard);
		hooking.AddHook("LevelValues_InvestigationBonusReward", &SDK::LevelValues_GetInvestigationBonus_ptr,
		                Hooks::hkLevelValues_GetInvestigationBonus);
		hooking.AddHook("LevelValues_IsPerfectGame", &SDK::LevelValues_IsPerfectGame_ptr, Hooks::hkLevelValues_IsPerfectGame);
		hooking.AddHook("DeadZoneController_Awake", &SDK::DeadZoneController_Awake_ptr, Hooks::hkDeadZoneController_Awake);
		hooking.AddHook("CursedItemController_Awake", &SDK::CursedItemController_Awake_ptr, Hooks::hkCursedItemController_Awake);
		hooking.AddHook("ObjectiveManager_Update", &SDK::ObjectiveManager_Update_ptr, Hooks::hkObjectiveManager_Update);
		hooking.AddHook("PhotonObjectInteract_Start", &SDK::PhotonObjectInteract_Start_ptr, Hooks::hkPhotonObjectInteract_Start);

		if (hooking.ApplyHooks() != Hooking::HookResult::Success)
		{
			LOG_WARN("Some hooks may not have been applied successfully");
		}

		LOG_INFO("Successfully loaded.");
		AddNotification("Asthmaphobia loaded. Press INSERT to open the menu.", Notifications::NotificationType::Info, 10.0f);

		do
		{
#ifdef _DEBUG
			// Backup in case we fuck up the menu and can't uninject
			if (GetAsyncKeyState(VK_DELETE) & 1)
			{
				LOG_DEBUG("Pressed DELETE key to uninject.");
				globalRunning = false;
			}
#endif

			// Terrible way of detecting hotkey presses
			featureManager.ProcessHotkeys();

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		while (globalRunning);

		Config::SaveConfig();
		ImGui::SaveIniSettingsToDisk((Helper::GetAsthmaphobiaDirectory() + "\\menu.ini").c_str());

		hooking.Cleanup();
		featureManager.Cleanup();
		renderer.Cleanup();

		LOG_INFO("Exiting...");
		logger.Cleanup();
	}
	catch (const std::exception& e)
	{
		LOG_ERROR(std::string("Exception in main Asthmaphobia thread: ") + e.what());
		MessageBoxA(nullptr, e.what(), "Asthmaphobia Exception", MB_ICONERROR);
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
