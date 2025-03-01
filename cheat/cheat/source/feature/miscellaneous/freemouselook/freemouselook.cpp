#include "freemouselook.h"

using namespace Asthmaphobia::Features::Miscellaneous;

FreeMouseLook::FreeMouseLook() : Feature("FreeMouseLook", "Disable camera restrictions. (360 view angle)", FeatureCategory::Miscellaneous)
{
	ShouldDrawSection = false;
}

void FreeMouseLook::OnMenu()
{
	ImGui::Checkbox("No camera restrictions", &std::get<bool>(EnabledSetting->GetValue()));
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("%s", Description.c_str());
}

void FreeMouseLook::OnFirstPersonController_Update(const SDK::FirstPersonController* firstPersonController, SDK::MethodInfo* methodInfo) const
{
	if (std::get<bool>(EnabledSetting->GetValue()))
	{
		firstPersonController->Fields.MouseLook->Fields.MinimumX = -360;
		firstPersonController->Fields.MouseLook->Fields.MaximumX = 360;
	}
	else
	{
		firstPersonController->Fields.MouseLook->Fields.MinimumX = -90;
		firstPersonController->Fields.MouseLook->Fields.MaximumX = 90;
	}
}
