#include "noclip.h"

using namespace Asthmaphobia::Features::Movement;

NoClip::NoClip() : Feature("NoClip", "Allows you to walk through walls.", FeatureCategory::Movement)
{
	SpeedSetting = std::make_shared<Setting>("Speed", "Speed of the NoClip.", 1.0f);
	Settings_->AddSetting(SpeedSetting);
}

NoClip::~NoClip() = default;

void NoClip::OnEnable()
{
}

void NoClip::OnDisable()
{
}

void NoClip::OnDraw()
{
}

void NoClip::OnMenu()
{
	ImGui::Checkbox("Enabled##noClip", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::SliderFloat("Speed##noClip", &std::get<float>(SpeedSetting->GetValue()), 0.0f, 10.0f, "%.1f");
}

void NoClip::OnFirstPersonController_Update(const SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo) const
{
	const auto rigidBody = firstPersonController->Fields.CharacterController->Fields.Rigidbody;
	if (!std::get<bool>(EnabledSetting->GetValue()))
	{
		SDK::Rigidbody_Set_IsKinematic_ptr(rigidBody, false, nullptr);
		SDK::Behaviour_Set_Enabled_ptr(reinterpret_cast<SDK::Behaviour*>(firstPersonController->Fields.CharacterController), true, nullptr);
		return;
	}

	SDK::Rigidbody_Set_IsKinematic_ptr(rigidBody, true, nullptr);
	SDK::Behaviour_Set_Enabled_ptr(reinterpret_cast<SDK::Behaviour*>(firstPersonController->Fields.CharacterController), false, nullptr);

	const auto transform = SDK::Component_Get_Transform_ptr(reinterpret_cast<SDK::Component*>(firstPersonController->Fields.CharacterController), nullptr);
	SDK::Vector3 position = {.X = 0, .Y = 0, .Z = 0};

	if (GetAsyncKeyState(0x57))
	{
		const auto forward = SDK::Transform_Get_Forward_ptr(transform, nullptr);
		position += forward;
	}

	if (GetAsyncKeyState(0x53))
	{
		const auto forward = SDK::Transform_Get_Forward_ptr(transform, nullptr);
		position -= forward;
	}

	if (GetAsyncKeyState(0x44))
	{
		const auto right = SDK::Transform_Get_Right_ptr(transform, nullptr);
		position += right;
	}

	if (GetAsyncKeyState(0x41))
	{
		const auto right = SDK::Transform_Get_Right_ptr(transform, nullptr);
		position -= right;
	}

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		const auto up = SDK::Transform_Get_Up_ptr(transform, nullptr);
		position += up;
	}

	if (GetAsyncKeyState(VK_LCONTROL))
	{
		const auto up = SDK::Transform_Get_Up_ptr(transform, nullptr);
		position -= up;
	}

	const auto speed = std::get<float>(SpeedSetting->GetValue()) * SDK::Time_Get_DeltaTime_ptr(nullptr);
	position *= speed;

	const auto worldPosition = SDK::Transform_Get_Position_ptr(transform, nullptr);
	position += worldPosition;

	SDK::Transform_Set_Position_ptr(transform, position, nullptr);
}
