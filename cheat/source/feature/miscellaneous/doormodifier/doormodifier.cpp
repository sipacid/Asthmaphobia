#include "doormodifier.h"

using namespace Asthmaphobia::Features::Miscellaneous;

DoorModifier::DoorModifier() : Feature("Door Modifier", "Modify door behaviour", FeatureCategory::Miscellaneous)
{
}

DoorModifier::~DoorModifier() = default;

void DoorModifier::OnEnable()
{
}

void DoorModifier::OnDisable()
{
}

void DoorModifier::OnDraw()
{
}

void DoorModifier::OnMenu()
{
	if (ImGui::Button("Disable door collision"))
		Run(Mode::ToggleDoorCollision, false);
	ImGui::SameLine();
	if (ImGui::Button("Enable door collision"))
		Run(Mode::ToggleDoorCollision, true);

	if (ImGui::Button("Disable door interaction"))
		Run(Mode::ToggleDoorInteraction, false);
	ImGui::SameLine();
	if (ImGui::Button("Enable door interaction"))
		Run(Mode::ToggleDoorInteraction, true);

	if (ImGui::Button("Unlock doors"))
		Run(Mode::ToggleDoorLock, false);
	ImGui::SameLine();
	if (ImGui::Button("Lock doors"))
		Run(Mode::ToggleDoorLock, true);
}

void DoorModifier::DoorLoop(const Mode mode, const bool enabled, SDK::DoorArray* const doorArray)
{
	for (int doorIndex = 0; doorIndex < reinterpret_cast<int32_t>(doorArray->MaxLength); doorIndex++)
	{
		if (const auto door = doorArray->Vector[doorIndex])
			switch (mode)
			{
			case Mode::ToggleDoorCollision:
				SDK::Door_DisableOrEnableCollider_ptr(door, enabled, nullptr);
				break;
			case Mode::ToggleDoorInteraction:
				SDK::Door_DisableOrEnableDoor_ptr(door, enabled, false, nullptr);
				break;
			case Mode::ToggleDoorLock:
				SDK::Door_LockDoorForTime_ptr(door, enabled ? 13370000 : 0, enabled, nullptr);
				break;
			}
	}
}

void DoorModifier::Run(const Mode mode, const bool enabled)
{
	if (!GameState::mapController)
		return AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);

	const auto gameController = GameState::mapController->Fields.GameController;
	const auto levelController = gameController->Fields.LevelController;

	const auto doorArray0 = levelController->Fields.DoorArray0;
	DoorLoop(mode, enabled, doorArray0);

	const auto doorArray1 = levelController->Fields.DoorArray1;
	DoorLoop(mode, enabled, doorArray1);
}
