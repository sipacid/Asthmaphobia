#include "infinitestamina.h"

using namespace Asthmaphobia::Features::Movement;

InfiniteStamina::InfiniteStamina() : Feature("Infinite Stamina", "Infinite stamina, be like Marco", FeatureCategory::Movement)
{
	ShouldDrawSection = false;
}

InfiniteStamina::~InfiniteStamina() = default;

void InfiniteStamina::OnEnable()
{
}

void InfiniteStamina::OnDisable()
{
}

void InfiniteStamina::OnDraw()
{
}

void InfiniteStamina::OnMenu()
{
	ImGui::Checkbox("Infinite Stamina", &std::get<bool>(EnabledSetting->GetValue()));
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("%s", Description.c_str());
}

void InfiniteStamina::OnPlayerStamina_Update(SDK::PlayerStamina* playerStamina, SDK::MethodInfo* methodInfo) const
{
	if (std::get<bool>(EnabledSetting->GetValue()) && playerStamina->Fields.Field18 != 3.0f)
		playerStamina->Fields.Field18 = 3.0f;

	SDK::PlayerStamina_Update_ptr(playerStamina, methodInfo);
}
