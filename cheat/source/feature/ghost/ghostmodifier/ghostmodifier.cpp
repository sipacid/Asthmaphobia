#include "ghostmodifier.h"

using namespace Asthmaphobia::Features::Ghost;

GhostModifier::GhostModifier() : Feature("GhostModifier", "Modify the ghost's behaviour", FeatureCategory::Ghost)
{
	GhostSpeedSetting = std::make_shared<Setting>("Ghost speed", "The speed of the ghost.", 3.0f);
	Settings_->AddSetting(GhostSpeedSetting);
}

GhostModifier::~GhostModifier() = default;

void GhostModifier::OnEnable()
{
}

void GhostModifier::OnDisable()
{
}

void GhostModifier::OnDraw()
{
}

void GhostModifier::OnMenu()
{
	ImGui::Checkbox("Enable custom ghost speed##ghostModifier", &std::get<bool>(EnabledSetting->GetValue()));
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("This will only work if you are the host.");
	ImGui::SliderFloat("Ghost Speed##ghostModifier", &std::get<float>(GhostSpeedSetting->GetValue()), 0.0f, 15.0f, "%.1f");

	if (ImGui::Button("Force appear##ghostModifier"))
	{
		if (GameState::ghostAI == nullptr)
		{
			AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else if (!Helper::IsLocalMasterClient())
		{
			AddNotification("You must be host to use this feature.", Notifications::NotificationType::Error, 3.0f);
		}
		else
		{
			ForceAppear = true;
		}
	}
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("This will only work if you are the host.");
}

void GhostModifier::OnGhostAIUpdate(SDK::GhostAI* ghost, SDK::MethodInfo* methodInfo)
{
	if (!std::get<bool>(EnabledSetting->GetValue()) || !Helper::IsLocalMasterClient())
		return;

	ghost->Fields.Speed = std::get<float>(GhostSpeedSetting->GetValue());
	ghost->Fields.Field22 = std::get<float>(GhostSpeedSetting->GetValue());
	ghost->Fields.Field23 = std::get<float>(GhostSpeedSetting->GetValue());

	if (ForceAppear)
	{
		SDK::GhostAI_Appear_ptr(ghost, INT_MAX, nullptr);
		ForceAppear = false;
	}
}
