#include "fullbright.h"

using namespace Asthmaphobia::Features::Visuals;

FullBright::FullBright() : Feature("FullBright", "Makes the entire map fully lit (LOCAL ONLY)", FeatureCategory::Visuals)
{
}

void FullBright::OnMenu()
{
	ImGui::Checkbox("Enabled##fullBright", &std::get<bool>(EnabledSetting->GetValue()));
	DrawHotkeyUI();
}

void FullBright::OnPCDisableComponentsStart(const SDK::PCDisablePlayerComponents* pcDisablePlayerComponents, SDK::MethodInfo* methodInfo) const
{
	if (!std::get<bool>(EnabledSetting->GetValue()))
		return;

	const auto light = pcDisablePlayerComponents->Fields.ShoulderFlashLight;
	if (light == nullptr)
		return;

	SDK::Light_Set_Intensity_ptr(light, 2.f, nullptr);
	SDK::Light_Set_Type_ptr(light, SDK::LightType::Directional, nullptr);
	SDK::Light_Set_Shadows_ptr(light, SDK::LightShadows::None, nullptr);
}
