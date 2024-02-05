#include "antikick.h"

using namespace Asthmaphobia::Features::Miscellaneous;

AntiKick::AntiKick() : Feature("AntiKick", "Prevents the server from kicking you", FeatureCategory::Miscellaneous)
{
	ShouldDrawSection = false;
}

AntiKick::~AntiKick() = default;

void AntiKick::OnEnable()
{
}

void AntiKick::OnDisable()
{
}

void AntiKick::OnDraw()
{
}

void AntiKick::OnMenu()
{
	ImGui::Checkbox("Anti Kick", &std::get<bool>(EnabledSetting->GetValue()));
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("%s", Description.c_str());
}

void AntiKick::OnServerManagerKickPlayerNetworked(SDK::ServerManager* serverManager, bool a1, void* photonMessageInfo, SDK::MethodInfo* methodInfo) const
{
	if (!std::get<bool>(EnabledSetting->GetValue()) || Helper::IsLocalMasterClient())
		return SDK::ServerManager_KickPlayerNetworked_ptr(serverManager, a1, photonMessageInfo, methodInfo);

	AddNotification("The host just tried to kick you", Notifications::NotificationType::Warning, 3.0f);
}
