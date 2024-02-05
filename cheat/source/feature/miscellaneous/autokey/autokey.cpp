#include "autokey.h"

using namespace Asthmaphobia::Features::Miscellaneous;

AutoKey::AutoKey() : Feature("Auto Key", "Automatically grabs the keys when loaded in", FeatureCategory::Miscellaneous)
{
	ShouldDrawSection = false;
}

AutoKey::~AutoKey() = default;

void AutoKey::OnEnable()
{
}

void AutoKey::OnDisable()
{
}

void AutoKey::OnDraw()
{
}

void AutoKey::OnMenu()
{
	ImGui::Checkbox("Auto Key", &std::get<bool>(EnabledSetting->GetValue()));
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("%s", Description.c_str());
}

void AutoKey::OnKey_Start(SDK::Key* key, SDK::MethodInfo* methodInfo) const
{
	SDK::Key_Start_ptr(key, methodInfo);

	if (std::get<bool>(EnabledSetting->GetValue()))
		SDK::Key_GrabbedKey_ptr(key, nullptr);
}
