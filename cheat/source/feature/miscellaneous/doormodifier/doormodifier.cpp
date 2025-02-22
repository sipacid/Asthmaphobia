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

	if (ImGui::Button("Test"))
		Test();
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

void DoorModifier::Test()
{
	const auto gameController = GameState::mapController->Fields.GameController;
	const auto levelController = gameController->Fields.LevelController;
	const auto localPlayerPosition = Helper::GetWorldPosition(Helper::GetLocalPlayer());

	const auto doorArray0 = levelController->Fields.DoorArray0;
	const auto doorArray1 = levelController->Fields.DoorArray1;

	for (int doorIndex = 0; doorIndex < reinterpret_cast<int32_t>(doorArray0->MaxLength); doorIndex++)
	{
		if (const auto door = doorArray0->Vector[doorIndex])
		{
			const auto transform = SDK::Component_Get_Transform_ptr(reinterpret_cast<SDK::Component*>(door), nullptr);
			const auto currentParent = SDK::Transform_Get_Parent_ptr(transform, nullptr);
			if (currentParent != nullptr)
			{
				const auto worldPosition = SDK::Transform_Get_Position_ptr(transform, nullptr);
				const auto worldRotation = SDK::Transform_Get_Rotation_ptr(transform, nullptr);

				SDK::Transform_Set_Parent_ptr(transform, nullptr, nullptr);

				SDK::Transform_Set_Position_ptr(transform, worldPosition, nullptr);
				SDK::Transform_Set_Rotation_ptr(transform, worldRotation, nullptr);
			}

			const auto rigidBody = door->Fields.Rigidbody;
			if (SDK::Rigidbody_Get_Constraints_ptr(rigidBody, nullptr) != SDK::RigidbodyConstraints::None)
				SDK::Rigidbody_Set_Constraints_ptr(rigidBody, SDK::RigidbodyConstraints::None, nullptr);
			SDK::Rigidbody_Set_IsKinematic_ptr(rigidBody, true, nullptr);

			SDK::Transform_Set_Position_ptr(transform, localPlayerPosition, nullptr);
		}
	}

	for (int doorIndex = 0; doorIndex < reinterpret_cast<int32_t>(doorArray1->MaxLength); doorIndex++)
	{
		if (const auto door = doorArray1->Vector[doorIndex])
		{
			const auto transform = SDK::Component_Get_Transform_ptr(reinterpret_cast<SDK::Component*>(door), nullptr);
			const auto currentParent = SDK::Transform_Get_Parent_ptr(transform, nullptr);
			if (currentParent != nullptr)
			{
				const auto worldPosition = SDK::Transform_Get_Position_ptr(transform, nullptr);
				const auto worldRotation = SDK::Transform_Get_Rotation_ptr(transform, nullptr);

				SDK::Transform_Set_Parent_ptr(transform, nullptr, nullptr);

				SDK::Transform_Set_Position_ptr(transform, worldPosition, nullptr);
				SDK::Transform_Set_Rotation_ptr(transform, worldRotation, nullptr);
			}

			const auto rigidBody = door->Fields.Rigidbody;
			if (SDK::Rigidbody_Get_Constraints_ptr(rigidBody, nullptr) != SDK::RigidbodyConstraints::None)
				SDK::Rigidbody_Set_Constraints_ptr(rigidBody, SDK::RigidbodyConstraints::None, nullptr);
			SDK::Rigidbody_Set_IsKinematic_ptr(rigidBody, true, nullptr);

			SDK::Transform_Set_Position_ptr(transform, localPlayerPosition, nullptr);
		}
	}
}
