#include "feature.h"

#include <algorithm>
#include <ranges>

#include "source/notifications/notifications.h"

#include "curseditems/curseditemmodifier/curseditemmodifier.h"
#include "curseditems/forcecard/forcecard.h"
#include "ghost/ghostmodifier/ghostmodifier.h"
#include "ghost/interactor/interactor.h"
#include "miscellaneous/antikick/antikick.h"
#include "miscellaneous/customname/customname.h"
#include "miscellaneous/doormodifier/doormodifier.h"
#include "miscellaneous/freemouselook/freemouselook.h"
#include "miscellaneous/leavepeople/leavepeople.h"
#include "miscellaneous/rewardmodifier/rewardmodifier.h"
#include "movement/infinitestamina/infinitestamina.h"
#include "movement/noclip/noclip.h"
#include "movement/speed/speed.h"
#include "movement/teleport/teleport.h"
#include "players/godmode/godmode.h"
#include "players/playermodifier/playermodifier.h"
#include "visuals/activitymonitor/activitymonitor.h"
#include "visuals/evidenceesp/evidenceesp.h"
#include "visuals/fuseboxesp/fuseboxesp.h"
#include "visuals/ghostesp/ghostesp.h"
#include "visuals/ghostwindow/ghostwindow.h"
#include "visuals/playeresp/playeresp.h"
#include "visuals/watermark/watermark.h"

using namespace Asthmaphobia;

const char* Asthmaphobia::FeatureTypeToString(const FeatureCategory category)
{
	switch (category)
	{
	case Visuals:
		return "Visuals";
	case Players:
		return "Players";
	case Ghost:
		return "Ghost";
	case CursedItems:
		return "Cursed items";
	case Miscellaneous:
		return "Miscellaneous";
	case Movement:
		return "Movement";
	default:
		return "Unknown";
	}
}

FeatureManager& Asthmaphobia::GetFeatureManagerInstance()
{
	static auto instance = std::make_unique<FeatureManager>();
	return *instance;
}

FeatureManager::FeatureManager()
{
	AddFeature("Visuals::Watermark", std::make_unique<Features::Visuals::Watermark>());
	AddFeature("Visuals::GhostWindow", std::make_unique<Features::Visuals::GhostWindow>());
	AddFeature("Visuals::ActivityMonitor", std::make_unique<Features::Visuals::ActivityMonitor>());
	AddFeature("Visuals::GhostESP", std::make_unique<Features::Visuals::GhostESP>());
	AddFeature("Visuals::PlayerESP", std::make_unique<Features::Visuals::PlayerESP>());
	AddFeature("Visuals::EvidenceESP", std::make_unique<Features::Visuals::EvidenceESP>());
	AddFeature("Visuals::FuseBoxESP", std::make_unique<Features::Visuals::FuseBoxESP>());

	AddFeature("Players::GodMode", std::make_unique<Features::Players::GodMode>());
	AddFeature("Players::PlayerModifier", std::make_unique<Features::Players::PlayerModifier>());

	AddFeature("Ghost::GhostModifier", std::make_unique<Features::Ghost::GhostModifier>());
	AddFeature("Ghost::Interactor", std::make_unique<Features::Ghost::Interactor>());

	AddFeature("CursedItems::CursedItemModifier", std::make_unique<Features::CursedItems::CursedItemModifier>());
	AddFeature("CursedItems::ForceCard", std::make_unique<Features::CursedItems::ForceCard>());

	AddFeature("Miscellaneous::LeavePeople", std::make_unique<Features::Miscellaneous::LeavePeople>());
	AddFeature("Miscellaneous::AntiKick", std::make_unique<Features::Miscellaneous::AntiKick>());
	AddFeature("Miscellaneous::DoorModifier", std::make_unique<Features::Miscellaneous::DoorModifier>());
	AddFeature("Miscellaneous::CustomName", std::make_unique<Features::Miscellaneous::CustomName>());
	AddFeature("Miscellaneous::RewardModifier", std::make_unique<Features::Miscellaneous::RewardModifier>());
	AddFeature("Miscellaneous::FreeMouseLook", std::make_unique<Features::Miscellaneous::FreeMouseLook>());

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
		Visuals, Players, Ghost, CursedItems, Movement, Miscellaneous
	};

	for (const auto featureType : CATEGORIES)
	{
		if (ImGui::BeginTabItem(FeatureTypeToString(featureType)))
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
