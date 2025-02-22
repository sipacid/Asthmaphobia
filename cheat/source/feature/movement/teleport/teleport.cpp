#include "teleport.h"

using namespace Asthmaphobia::Features::Movement;

Teleport::Teleport() : Feature("Teleport", "Portal <3", FeatureCategory::Movement)
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

	if (ImGui::Button("Teleport all items to me##teleport"))
		TeleportItems();
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip("Some items might be only locally there until you pick them up.");
}

void Teleport::Run(const SDK::Player* player) const
{
	if (!GameState::mapController || !GameState::deadZoneController || !GameState::ghostAI)
		return AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);

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

void Teleport::TeleportItems()
{
	if (!GameState::mapController || !GameState::deadZoneController || !GameState::ghostAI)
		return AddNotification("You must be in-game to use this feature.", Notifications::NotificationType::Error, 3.0f);

	const auto localPlayer = Helper::GetLocalPlayer();
	const auto objects = SDK::GameObject_FindGameObjectsWithTag_ptr(Helper::StringToSystemString("Item"), nullptr);
	if (objects == nullptr)
		return;

	for (int objectIndex = 0; objectIndex < reinterpret_cast<int32_t>(objects->MaxLength); ++objectIndex)
	{
		const auto object = objects->Vector[objectIndex];
		if (object == nullptr)
			continue;

		const auto transform = SDK::GameObject_Get_Transform_ptr(object, nullptr);
		if (transform == nullptr)
			continue;

		const auto worldPosition = Helper::GetWorldPosition(localPlayer);
		SDK::Transform_Set_Position_ptr(transform, worldPosition + SDK::Vector3{
			                                .X = Helper::RandomNumber(-1, 1), .Y = Helper::RandomNumber(0, 0.25), .Z = Helper::RandomNumber(1, 3)
		                                },
		                                nullptr);
	}
}
