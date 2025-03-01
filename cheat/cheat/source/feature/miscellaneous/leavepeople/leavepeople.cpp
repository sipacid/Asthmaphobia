#include "leavepeople.h"

using namespace Asthmaphobia::Features::Miscellaneous;

LeavePeople::LeavePeople() : Feature("Leave People", "Leave whilst there are still players alive outside of the truck (HOST ONLY)", FeatureCategory::Miscellaneous)
{
	this->ShouldDrawSection = false;
}

void LeavePeople::OnMenu()
{
	ImGui::Checkbox("Leave People", &std::get<bool>(EnabledSetting->GetValue()));
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("%s", Description.c_str());
}

bool LeavePeople::OnExitLevelThereAreAlivePlayersOutsideTheTruck(SDK::ExitLevel* exitLevel, SDK::MethodInfo* methodInfo) const
{
	if (!std::get<bool>(EnabledSetting->GetValue()) || !Helper::IsLocalMasterClient())
		return SDK::ExitLevel_ThereAreAlivePlayersOutsideTheTruck_ptr(exitLevel, methodInfo);

	return false;
}
