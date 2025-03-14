#include "interactor.h"

using namespace Asthmaphobia::Features::Ghost;

Interactor::Interactor() : Feature("Interactor", "Force the ghost to interact", FeatureCategory::Ghost)
{
}

void Interactor::OnMenu()
{
	if (ImGui::Button("Force ability##interactor"))
	{
		if (GameState::ghostAI == nullptr)
		{
			AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else if (!Helper::IsLocalMasterClient())
		{
			AddNotification("You must be host to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else
		{
			ForceAbility = true;
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Force interact with door##interactor"))
	{
		if (GameState::ghostAI == nullptr)
		{
			AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else if (!Helper::IsLocalMasterClient())
		{
			AddNotification("You must be host to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else
		{
			ForceInteractWithRandomDoor = true;
		}
	}

	if (ImGui::Button("Force interact with random prop##interactor"))
	{
		if (GameState::ghostAI == nullptr)
		{
			AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else if (!Helper::IsLocalMasterClient())
		{
			AddNotification("You must be host to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else
		{
			ForceInteractWithRandomProp = true;
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Force normal interaction##interactor"))
	{
		if (GameState::ghostAI == nullptr)
		{
			AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else if (!Helper::IsLocalMasterClient())
		{
			AddNotification("You must be host to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else
		{
			ForceNormalInteraction = true;
		}
	}

	if (ImGui::Button("Force twin interaction##interactor"))
	{
		if (GameState::ghostAI == nullptr)
		{
			AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else if (!Helper::IsLocalMasterClient())
		{
			AddNotification("You must be host to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else
		{
			ForceTwinInteraction = true;
		}
	}
}

void Interactor::OnGhostAIUpdate(const SDK::GhostAI* ghost, SDK::MethodInfo* methodInfo)
{
	if (ForceAbility)
	{
		SDK::GhostActivity_GhostAbility_ptr(ghost->Fields.GhostActivity, methodInfo);
		ForceAbility = false;
	}

	if (ForceInteractWithRandomDoor)
	{
		SDK::GhostActivity_InteractWithARandomDoor_ptr(ghost->Fields.GhostActivity, methodInfo);
		ForceInteractWithRandomDoor = false;
	}

	if (ForceInteractWithRandomProp)
	{
		SDK::GhostActivity_InteractWithARandomProp_ptr(ghost->Fields.GhostActivity, true, methodInfo);
		ForceInteractWithRandomProp = false;
	}

	if (ForceNormalInteraction)
	{
		SDK::GhostActivity_NormalInteraction_ptr(ghost->Fields.GhostActivity, true, methodInfo);
		ForceNormalInteraction = false;
	}

	if (ForceTwinInteraction)
	{
		SDK::GhostActivity_TwinInteraction_ptr(ghost->Fields.GhostActivity, true, methodInfo);
		ForceTwinInteraction = false;
	}
}
