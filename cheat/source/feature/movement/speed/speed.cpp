#include "speed.h"

using namespace Asthmaphobia::Features::Movement;

Speed::Speed() : Feature("Speed", "Custom walk/run speed, become Marco", FeatureCategory::Movement)
{
	WalkSpeedSetting = std::make_shared<Setting>("Walk speed", "Walk speed.", 1.6f);
	RunSpeedSetting = std::make_shared<Setting>("Run speed", "Run speed.", 3.0f);
	Settings_->AddSetting(WalkSpeedSetting);
	Settings_->AddSetting(RunSpeedSetting);
}

void Speed::OnMenu()
{
	ImGui::Checkbox("Enabled##speed", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::SliderFloat("Walk Speed##speed", &std::get<float>(WalkSpeedSetting->GetValue()), 0.0f, 15.0f, "%.1f");
	ImGui::SliderFloat("Run Speed##speed", &std::get<float>(RunSpeedSetting->GetValue()), 0.0f, 15.0f, "%.1f");
}

void Speed::OnFirstPersonController_Update(SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo)
{
	if (std::get<bool>(EnabledSetting->GetValue()))
	{
		WasEnabled = true;
		firstPersonController->Fields.CurrentSpeed = !firstPersonController->Fields.IsSprinting
			                                             ? std::get<float>(WalkSpeedSetting->GetValue())
			                                             : std::get<float>(RunSpeedSetting->GetValue());
	}
	else
	{
		if (WasEnabled)
			firstPersonController->Fields.CurrentSpeed = !firstPersonController->Fields.IsSprinting ? DefaultWalkSpeed : DefaultRunSpeed;
		WasEnabled = false;
	}
}
