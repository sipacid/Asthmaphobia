#include "feature.h"

#include <algorithm>
#include <ranges>

#include "source/notifications/notifications.h"

#include "curseditems/curseditemmodifier/curseditemmodifier.h"
#include "curseditems/forcecard/forcecard.h"
#include "exploits/antikick/antikick.h"
#include "exploits/freemouselook/freemouselook.h"
#include "exploits/leavepeople/leavepeople.h"
#include "exploits/pickup/pickup.h"
#include "exploits/rewardmodifier/rewardmodifier.h"
#include "ghost/ghostmodifier/ghostmodifier.h"
#include "ghost/interactor/interactor.h"
#include "movement/infinitestamina/infinitestamina.h"
#include "movement/noclip/noclip.h"
#include "movement/speed/speed.h"
#include "movement/teleport/teleport.h"
#include "player/customname/customname.h"
#include "player/godmode/godmode.h"
#include "player/playermodifier/playermodifier.h"
#include "visuals/activitymonitor/activitymonitor.h"
#include "visuals/evidenceesp/evidenceesp.h"
#include "visuals/fuseboxesp/fuseboxesp.h"
#include "visuals/ghostesp/ghostesp.h"
#include "visuals/ghostwindow/ghostwindow.h"
#include "visuals/playeresp/playeresp.h"
#include "visuals/watermark/watermark.h"
#include "world/doormodifier/doormodifier.h"

using namespace Asthmaphobia;

FeatureManager& Asthmaphobia::GetFeatureManagerInstance()
{
	static auto instance = std::make_unique<FeatureManager>();
	return *instance;
}

FeatureManager::FeatureManager()
{
	AddFeature("Players::GodMode", std::make_unique<Features::Player::GodMode>());
	AddFeature("Player::CustomName", std::make_unique<Features::Player::CustomName>());
	AddFeature("Players::PlayerModifier", std::make_unique<Features::Player::PlayerModifier>());

	AddFeature("Ghost::GhostModifier", std::make_unique<Features::Ghost::GhostModifier>());
	AddFeature("Ghost::Interactor", std::make_unique<Features::Ghost::Interactor>());

	AddFeature("World::DoorModifier", std::make_unique<Features::World::DoorModifier>());

	AddFeature("CursedItems::CursedItemModifier", std::make_unique<Features::CursedItems::CursedItemModifier>());
	AddFeature("CursedItems::ForceCard", std::make_unique<Features::CursedItems::ForceCard>());

	AddFeature("Visuals::Watermark", std::make_unique<Features::Visuals::Watermark>());
	AddFeature("Visuals::GhostWindow", std::make_unique<Features::Visuals::GhostWindow>());
	AddFeature("Visuals::ActivityMonitor", std::make_unique<Features::Visuals::ActivityMonitor>());
	AddFeature("Visuals::GhostESP", std::make_unique<Features::Visuals::GhostESP>());
	AddFeature("Visuals::PlayerESP", std::make_unique<Features::Visuals::PlayerESP>());
	AddFeature("Visuals::EvidenceESP", std::make_unique<Features::Visuals::EvidenceESP>());
	AddFeature("Visuals::FuseBoxESP", std::make_unique<Features::Visuals::FuseBoxESP>());

	AddFeature("Exploits::LeavePeople", std::make_unique<Features::Exploits::LeavePeople>());
	AddFeature("Exploits::AntiKick", std::make_unique<Features::Exploits::AntiKick>());
	AddFeature("Exploits::RewardModifier", std::make_unique<Features::Exploits::RewardModifier>());
	AddFeature("Exploits::FreeMouseLook", std::make_unique<Features::Exploits::FreeMouseLook>());
	AddFeature("Exploits::Pickup", std::make_unique<Features::Exploits::Pickup>());

	AddFeature("Movement::InfiniteStamina", std::make_unique<Features::Movement::InfiniteStamina>());
	AddFeature("Movement::NoClip", std::make_unique<Features::Movement::NoClip>());
	AddFeature("Movement::Speed", std::make_unique<Features::Movement::Speed>());
	AddFeature("Movement::Teleport", std::make_unique<Features::Movement::Teleport>());
}

FeatureManager::~FeatureManager()
{
	Features.clear();
}

void FeatureManager::Cleanup()
{
	Features.clear();
}

void FeatureManager::AddFeature(const std::string_view name, std::unique_ptr<Feature> feature)
{
	Features.emplace(std::string(name), std::move(feature));
}

Feature* FeatureManager::GetFeatureByName(const std::string_view name) const
{
	if (const auto it = Features.find(std::string(name)); it != Features.end())
		return it->second.get();
	return nullptr;
}

void FeatureManager::OnDraw() const
{
	for (const auto& feature : Features | std::views::values)
	{
		if (feature->IsEnabled())
		{
			feature->OnDraw();
		}
	}
}

void FeatureManager::OnMenu() const
{
	static constexpr FeatureCategory CATEGORIES[] = {
		Player,
		Ghost,
		World,
		CursedItems,
		Visuals,
		Exploits,
		Movement,
	};

	for (const auto featureType : CATEGORIES)
	{
		// GG if this fails, but this should never fail :)
		if (ImGui::BeginTabItem(CATEGORY_TO_STRING.find(featureType)->second))
		{
			for (const auto& feature : Features | std::views::values)
			{
				if (feature->GetCategory() == featureType)
				{
					if (feature->ShouldDrawSection)
					{
						ImGui::Text("%s", feature->GetName().c_str());
						ImGui::TextColored(ImColor(173, 173, 173, 255), "%s",
						                   feature->GetDescription().c_str());
					}

					feature->OnMenu();
					ImGui::Separator();
				}
			}
			ImGui::EndTabItem();
		}
	}
}
