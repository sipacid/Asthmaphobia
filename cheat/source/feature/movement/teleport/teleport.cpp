#include "teleport.h"

using namespace Asthmaphobia::Features::Movement;

Teleport::Teleport() : Feature("Teleport", "Teleport to a specific location", FeatureCategory::Movement)
{
	TargetSetting = std::make_shared<Setting>("Target", "Target to teleport to", static_cast<int>(Target::Ghost));
	Settings_->AddSetting(TargetSetting);
}

Teleport::~Teleport() = default;

void Teleport::OnEnable()
{
}

void Teleport::OnDisable()
{
}

void Teleport::OnDraw()
{
}

void Teleport::OnMenu()
{
	const char* targetList[] = {"Ghost", "Death room", "Truck"};
	ImGui::Combo("Target##teleport", &std::get<int>(TargetSetting->GetValue()), targetList, IM_ARRAYSIZE(targetList));
	ImGui::SameLine();
	if (ImGui::Button("Teleport##teleport"))
		Run(nullptr);
}

void Teleport::Run(const SDK::Player* player) const
{
	if (!GameState::mapController || !GameState::deadZoneController || !GameState::ghostAI)
		return AddNotification("You must be in-game to use this feature", Notifications::NotificationType::Info, 3.0f);

	const auto localPlayer = Helper::GetLocalPlayer();

	switch (static_cast<Target>(std::get<int>(TargetSetting->GetValue())))
	{
	case Target::Ghost:
		Helper::TeleportPlayerTo(localPlayer, GameState::ghostAI);
		break;
	case Target::DeathRoom:
		Helper::TeleportPlayerTo(localPlayer, GameState::deadZoneController->Fields.PlayerSpawn);
		break;
	case Target::Truck:
		break;
	case Target::Player:
		Helper::TeleportPlayerTo(localPlayer, player);
		break;
	default:
		break;
	}
}
