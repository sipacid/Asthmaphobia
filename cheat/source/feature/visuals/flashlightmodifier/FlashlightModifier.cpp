#include "FlashlightModifier.h"

using namespace Asthmaphobia::Features::Visuals;

FlashlightModifier::FlashlightModifier() : Feature("Flashlight modifier", "Modify your flashlight", FeatureCategory::Visuals)
{
	ShoulderLightEnabledSetting = std::make_shared<Setting>("Shoulder light enabled", "Shoulder light enabled", true);
	FlashlightEnabledSetting = std::make_shared<Setting>("Flashlight enabled", "Flashlight enabled", false);
	IntensitySetting = std::make_shared<Setting>("Intensity", "Intensity of the head light", 2.0f);
	BounceIntensitySetting = std::make_shared<Setting>("Bounce intensity", "Bounce intensity of the head light", 2.0f);
	ColorSetting = std::make_shared<Setting>("Color", "Color of the head light", ImColor(1.0f, 1.0f, 1.0f, 1.0f));
	SpotAngleSetting = std::make_shared<Setting>("Spot angle", "Spot angle of the head light", 360.0f);
	RangeSetting = std::make_shared<Setting>("Range", "Range of the head light", 1000.0f);
	ShadowStrengthSetting = std::make_shared<Setting>("Shadow strength", "Shadow strength of the head light", 0.0f);
	Settings_->AddSetting(ShoulderLightEnabledSetting);
	Settings_->AddSetting(FlashlightEnabledSetting);
	Settings_->AddSetting(IntensitySetting);
	Settings_->AddSetting(BounceIntensitySetting);
	Settings_->AddSetting(ColorSetting);
	Settings_->AddSetting(SpotAngleSetting);
	Settings_->AddSetting(RangeSetting);
	Settings_->AddSetting(ShadowStrengthSetting);

	LightSettings = std::map<SDK::Light*, SDK::LightSettings>();
}

FlashlightModifier::~FlashlightModifier() = default;

void FlashlightModifier::OnEnable()
{
}

void FlashlightModifier::OnDisable()
{
}

void FlashlightModifier::OnDraw()
{
}

void FlashlightModifier::OnMenu()
{
	constexpr auto colorEditFlags = ImGuiColorEditFlags_NoInputs;

	ImGui::Checkbox("ShoulderLight##flashLightModifier", &std::get<bool>(ShoulderLightEnabledSetting->GetValue()));
	ImGui::Checkbox("Flashlight##flashLightModifier", &std::get<bool>(FlashlightEnabledSetting->GetValue()));
	ImGui::SameLine();
	ImGui::ColorEdit4("Color##flashLightModifier", reinterpret_cast<float*>(&std::get<ImColor>(ColorSetting->GetValue()).Value), colorEditFlags);

	ImGui::SliderFloat("Intensity##flashLightModifier", &std::get<float>(IntensitySetting->GetValue()), 0.0f, 8.0f);
	ImGui::SliderFloat("Bounce intensity##flashLightModifier", &std::get<float>(BounceIntensitySetting->GetValue()), 0.0f, 8.0f);
	ImGui::SliderFloat("Spot angle##flashLightModifier", &std::get<float>(SpotAngleSetting->GetValue()), 0.0f, 360.0f);
	ImGui::SliderFloat("Range##flashLightModifier", &std::get<float>(RangeSetting->GetValue()), 0.0f, 1000.0f);
	ImGui::SliderFloat("Shadow strength##flashLightModifier", &std::get<float>(ShadowStrengthSetting->GetValue()), 0.0f, 1.0f);
}

void FlashlightModifier::OnPCDisablePlayerComponents_Start(SDK::PCDisablePlayerComponents* pcDisablePlayerComponents, SDK::MethodInfo* methodInfo)
{
	if (!LightSettings.contains(pcDisablePlayerComponents->Fields.ShoulderFlashlightLight))
		LightSettings[pcDisablePlayerComponents->Fields.ShoulderFlashlightLight] = GetLightSettings(pcDisablePlayerComponents->Fields.ShoulderFlashlightLight);

	if (!std::get<bool>(ShoulderLightEnabledSetting->GetValue()))
		SetLightSettings(pcDisablePlayerComponents->Fields.ShoulderFlashlightLight, LightSettings[pcDisablePlayerComponents->Fields.ShoulderFlashlightLight]);
	else
		SetLightSettings(pcDisablePlayerComponents->Fields.ShoulderFlashlightLight);

	SDK::PCDisablePlayerComponents_Start_ptr(pcDisablePlayerComponents, methodInfo);
}

void FlashlightModifier::OnPCFlashlight_Update(SDK::PCFlashlight* pcFlashLight, SDK::MethodInfo* methodInfo)
{
	if (!LightSettings.contains(pcFlashLight->Fields.Headlight))
		LightSettings[pcFlashLight->Fields.Headlight] = GetLightSettings(pcFlashLight->Fields.Headlight);

	if (!std::get<bool>(FlashlightEnabledSetting->GetValue()))
		SetLightSettings(pcFlashLight->Fields.Headlight, LightSettings[pcFlashLight->Fields.Headlight]);
	else
		SetLightSettings(pcFlashLight->Fields.Headlight);

	SDK::PCFlashlight_Update_ptr(pcFlashLight, methodInfo);
}

void FlashlightModifier::OnTorch_Update(SDK::Torch* torch, SDK::MethodInfo* methodInfo)
{
	if (!LightSettings.contains(torch->Fields.Field0))
		LightSettings[torch->Fields.Field0] = GetLightSettings(torch->Fields.Field0);

	if (std::get<bool>(FlashlightEnabledSetting->GetValue()))
		SetLightSettings(torch->Fields.Field0);
	else
		SetLightSettings(torch->Fields.Field0, LightSettings[torch->Fields.Field0]);

	SDK::Torch_Update_ptr(torch, methodInfo);
}

void FlashlightModifier::SetLightSettings(SDK::Light* light) const
{
	const auto imColor = std::get<ImColor>(ColorSetting->GetValue());
	const auto color = SDK::Quaternion(imColor.Value.x, imColor.Value.y, imColor.Value.z, 1.0f);

	SetLightSettings(light, SDK::LightSettings{
		                 std::get<float>(IntensitySetting->GetValue()),
		                 std::get<float>(BounceIntensitySetting->GetValue()),
		                 std::get<float>(RangeSetting->GetValue()),
		                 std::get<float>(SpotAngleSetting->GetValue()),
		                 std::get<float>(ShadowStrengthSetting->GetValue()),
		                 color
	                 });
}

void FlashlightModifier::SetLightSettings(SDK::Light* light, const SDK::LightSettings& lightSettings)
{
	SDK::Light_Set_Intensity_ptr(light, lightSettings.Intensity, nullptr);
	SDK::Light_Set_BounceIntensity_ptr(light, lightSettings.BounceIntensity, nullptr);
	SDK::Light_Set_Color_ptr(light, lightSettings.Color, nullptr);
	SDK::Light_Set_SpotAngle_ptr(light, lightSettings.SpotAngle, nullptr);
	SDK::Light_Set_Range_ptr(light, lightSettings.Range, nullptr);
	SDK::Light_Set_ShadowStrength_ptr(light, lightSettings.ShadowStrength, nullptr);
}

SDK::LightSettings FlashlightModifier::GetLightSettings(SDK::Light* light)
{
	return SDK::LightSettings{
		SDK::Light_Get_Intensity_ptr(light, nullptr),
		SDK::Light_Get_BounceIntensity_ptr(light, nullptr),
		SDK::Light_Get_Range_ptr(light, nullptr),
		SDK::Light_Get_SpotAngle_ptr(light, nullptr),
		SDK::Light_Get_ShadowStrength_ptr(light, nullptr),
		SDK::Light_Get_Color_ptr(light, nullptr)
	};
}
