#include "noclip.h"
#include "source/menu/menu.h"

using namespace Asthmaphobia::Features::Movement;

NoClip::NoClip() : Feature("NoClip", "Allows you to walk through walls.", FeatureCategory::Movement)
{
	SpeedSetting = std::make_shared<Setting>("Speed", "Speed of the NoClip.", 1.0f);
	Settings_->AddSetting(SpeedSetting);
}

void NoClip::OnMenu()
{
	ImGui::Checkbox("Enabled##noClip", &std::get<bool>(EnabledSetting->GetValue()));
	DrawHotkeyUI();
	ImGui::SliderFloat("Speed##noClip", &std::get<float>(SpeedSetting->GetValue()), 0.0f, 10.0f, "%.1f");
}

void NoClip::OnFirstPersonControllerUpdate(const SDK::FirstPersonController* firstPersonController, SDK::MethodInfo*) const
{
	const auto& enabled = std::get<bool>(EnabledSetting->GetValue());
	const auto controller = firstPersonController->Fields.CharacterController;
	const auto rigidBody = controller->Fields.Rigidbody;

	if (!enabled)
	{
		SDK::Rigidbody_Set_IsKinematic_ptr(rigidBody, false, nullptr);
		SDK::Behaviour_Set_Enabled_ptr(reinterpret_cast<SDK::Behaviour*>(controller), true, nullptr);
		return;
	}

	// Prevent no-clip from working when the game is not in focus
	const HWND foregroundWindow = GetForegroundWindow();
	DWORD foregroundProcessId = 0;
	GetWindowThreadProcessId(foregroundWindow, &foregroundProcessId);
	if (foregroundProcessId != GetCurrentProcessId() || menu.Open)
		return;

	SDK::Rigidbody_Set_IsKinematic_ptr(rigidBody, true, nullptr);
	SDK::Behaviour_Set_Enabled_ptr(reinterpret_cast<SDK::Behaviour*>(controller), false, nullptr);

	const auto transform = SDK::Component_Get_Transform_ptr(reinterpret_cast<SDK::Component*>(controller), nullptr);

	const auto forward = SDK::Transform_Get_Forward_ptr(transform, nullptr);
	const auto right = SDK::Transform_Get_Right_ptr(transform, nullptr);
	const auto up = SDK::Transform_Get_Up_ptr(transform, nullptr);

	SDK::Vector3 position = {};

	const uint8_t movementMask = (GetAsyncKeyState(0x57) ? 1 : 0) | // W
		(GetAsyncKeyState(0x53) ? 2 : 0) | // S
		(GetAsyncKeyState(0x44) ? 4 : 0) | // D
		(GetAsyncKeyState(0x41) ? 8 : 0) | // A
		(GetAsyncKeyState(VK_LSHIFT) ? 16 : 0) |
		(GetAsyncKeyState(VK_LCONTROL) ? 32 : 0);

	if (movementMask & 1)
		position += forward;
	if (movementMask & 2)
		position -= forward;
	if (movementMask & 4)
		position += right;
	if (movementMask & 8)
		position -= right;
	if (movementMask & 16)
		position += up;
	if (movementMask & 32)
		position -= up;

	const auto speed = std::get<float>(SpeedSetting->GetValue()) * SDK::Time_Get_DeltaTime_ptr(nullptr);
	position *= speed;
	position += SDK::Transform_Get_Position_ptr(transform, nullptr);

	SDK::Transform_Set_Position_ptr(transform, position, nullptr);
}
