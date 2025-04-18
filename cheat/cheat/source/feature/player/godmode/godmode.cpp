#include "godmode.h"

using namespace Asthmaphobia::Features::Player;

GodMode::GodMode() : Feature("GodMode", "Become invincible, will spawn dead body when attacked by ghost", FeatureCategory::Player)
{
}

void GodMode::OnMenu()
{
	ImGui::Checkbox("Enabled##godMode", &std::get<bool>(EnabledSetting->GetValue()));
}

std::nullptr_t GodMode::OnPlayerStartKillingPlayerNetworked(SDK::Player* player, const bool revive, const bool wasDemonAbilityHunt, void* photonMessageInfo,
                                                            SDK::MethodInfo* methodInfo) const
{
	if (!std::get<bool>(EnabledSetting->GetValue()) || player != Helper::GetLocalPlayer())
		return SDK::Player_StartKillingPlayerNetworked_ptr(player, revive, wasDemonAbilityHunt, photonMessageInfo, methodInfo);

	return nullptr;
}
