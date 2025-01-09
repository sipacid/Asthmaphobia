#include "speed.h"

using namespace Asthmaphobia::Features::Movement;

Speed::Speed() : Feature("Speed", "Custom walk/run speed, become Marco", FeatureCategory::Movement)
{
	WalkSpeedSetting = std::make_shared<Setting>("Walk speed", "Walk speed.", 1.6f);
	RunSpeedSetting = std::make_shared<Setting>("Run speed", "Run speed.", 3.0f);
	MouseLookAdjustmentSetting = std::make_shared<Setting>("Enable MouseLook Adjustments", "Enable adjustments to MouseLook when sprinting.", true);

	Settings_->AddSetting(WalkSpeedSetting);
	Settings_->AddSetting(RunSpeedSetting);
	Settings_->AddSetting(MouseLookAdjustmentSetting); // Add the MouseLook adjustment setting
}

Speed::~Speed() = default;

void Speed::OnEnable()
{
}

void Speed::OnDisable()
{
}

void Speed::OnDraw()
{
}

void Speed::OnMenu()
{


	//ImGui::Checkbox("Break##Neck", &std::get<bool>(Breaknecksetting->GetValue()));
	ImGui::Checkbox("Enabled##speed", &std::get<bool>(EnabledSetting->GetValue()));
	ImGui::SliderFloat("Walk Speed##speed", &std::get<float>(WalkSpeedSetting->GetValue()), 0.0f, 15.0f, "%.1f");
	ImGui::SliderFloat("Run Speed##speed", &std::get<float>(RunSpeedSetting->GetValue()), 0.0f, 15.0f, "%.1f");

	ImGui::Checkbox("Enable MouseLook Adjustments", &std::get<bool>(MouseLookAdjustmentSetting->GetValue()));
}

void Speed::OnFirstPersonController_Update(SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo) const
{
	static bool WasEnabled = false;
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


	if (std::get<bool>(MouseLookAdjustmentSetting->GetValue()) && firstPersonController->Fields.MouseLook) {
		
			firstPersonController->Fields.MouseLook->Fields.MaximumX = 360;
			firstPersonController->Fields.MouseLook->Fields.MinimumX = -360;
		}	
			else {		
				firstPersonController->Fields.MouseLook->Fields.MaximumX = 90;
				firstPersonController->Fields.MouseLook->Fields.MinimumX = -90;
		 }
			
		

	

}
