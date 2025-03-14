#include "godmode.h"

using namespace Asthmaphobia::Features::Players;

GodMode::GodMode() : Feature("GodMode", "Become invincible, will spawn dead body when attacked by ghost", FeatureCategory::Players)
{
}

void GodMode::OnMenu()
{
	ImGui::Checkbox("Enabled", &std::get<bool>(EnabledSetting->GetValue()));
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("%s", Description.c_str());
}

std::nullptr_t GodMode::OnPlayerStartKillingPlayerNetworked(SDK::Player* player, const bool a1, const bool a2, void* photonMessageInfo, SDK::MethodInfo* methodInfo) const
{
	if (!std::get<bool>(EnabledSetting->GetValue()) || player != Helper::GetLocalPlayer())
		return SDK::Player_StartKillingPlayerNetworked_ptr(player, a1, a2, photonMessageInfo, methodInfo);

	return nullptr;
}
