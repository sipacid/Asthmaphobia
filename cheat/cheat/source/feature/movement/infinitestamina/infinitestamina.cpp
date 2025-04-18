#include "infinitestamina.h"

using namespace Asthmaphobia::Features::Movement;

InfiniteStamina::InfiniteStamina() : Feature("Infinite Stamina", "Infinite stamina, be like Marco", FeatureCategory::Movement)
{
}

void InfiniteStamina::OnMenu()
{
	ImGui::Checkbox("Enabled##infiniteStamina", &std::get<bool>(EnabledSetting->GetValue()));
}

void InfiniteStamina::OnPlayerStamina_Update(SDK::PlayerStamina* playerStamina, SDK::MethodInfo* methodInfo) const
{
	if (std::get<bool>(EnabledSetting->GetValue()) && playerStamina->Fields.CurrentStamina != 3.0f)
		playerStamina->Fields.CurrentStamina = 3.0f;
}
