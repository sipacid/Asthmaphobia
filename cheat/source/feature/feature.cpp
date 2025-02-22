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

FeatureManager::FeatureManager()
{
	InitializeCriticalSection(&DrawSection);
	Features = std::unordered_map<std::string, Feature*>();

	AddFeature("Visuals::Watermark", new Features::Visuals::Watermark());
	AddFeature("Visuals::GhostWindow", new Features::Visuals::GhostWindow());
	AddFeature("Visuals::GhostESP", new Features::Visuals::GhostESP());
	AddFeature("Visuals::PlayerESP", new Features::Visuals::PlayerESP());
	AddFeature("Visuals::EvidenceESP", new Features::Visuals::EvidenceESP());
	AddFeature("Visuals::FuseBoxESP", new Features::Visuals::FuseBoxESP());

	AddFeature("Players::GodMode", new Features::Players::GodMode());
	AddFeature("Players::PlayerModifier", new Features::Players::PlayerModifier());

	AddFeature("Ghost::GhostModifier", new Features::Ghost::GhostModifier());
	AddFeature("Ghost::Interactor", new Features::Ghost::Interactor());

	AddFeature("CursedItems::CursedItemModifier", new Features::CursedItems::CursedItemModifier());
	AddFeature("CursedItems::ForceCard", new Features::CursedItems::ForceCard());

	AddFeature("Miscellaneous::LeavePeople", new Features::Miscellaneous::LeavePeople());
	AddFeature("Miscellaneous::AntiKick", new Features::Miscellaneous::AntiKick());
	AddFeature("Miscellaneous::DoorModifier", new Features::Miscellaneous::DoorModifier());
	AddFeature("Miscellaneous::CustomName", new Features::Miscellaneous::CustomName());
	AddFeature("Miscellaneous::RewardModifier", new Features::Miscellaneous::RewardModifier());
	AddFeature("Miscellaneous::FreeMouseLook", new Features::Miscellaneous::FreeMouseLook());

	AddFeature("Movement::InfiniteStamina", new Features::Movement::InfiniteStamina());
	AddFeature("Movement::NoClip", new Features::Movement::NoClip());
	AddFeature("Movement::Speed", new Features::Movement::Speed());
	AddFeature("Movement::Teleport", new Features::Movement::Teleport());

	featureManager = this;
}

FeatureManager::~FeatureManager()
{
	DeleteCriticalSection(&DrawSection);
	Features.clear();

	for (const auto& feature : Features | std::views::values)
	{
		delete feature;
	}

	featureManager = nullptr;
}

void FeatureManager::AddFeature(const std::string& name, Feature* feature)
{
	Features[name] = feature;
}

Feature* FeatureManager::GetFeatureByName(const std::string& name) const
{
	return Features.at(name);
}

void FeatureManager::OnDraw() const
{
	EnterCriticalSection(&DrawSection);
	for (const auto& feature : Features | std::views::values)
	{
		if (feature->IsEnabled())
		{
			feature->OnDraw();
		}
	}
	LeaveCriticalSection(&DrawSection);
}

void FeatureManager::OnMenu() const
{
	for (const auto& featureType : {Visuals, Players, Ghost, CursedItems, Movement, Miscellaneous})
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
						ImGui::TextColored(ImColor(173, 173, 173, 255), "%s", feature->GetDescription().c_str());
					}

					EnterCriticalSection(&DrawSection);
					feature->OnMenu();
					LeaveCriticalSection(&DrawSection);

					ImGui::Separator();
				}
			}

			ImGui::EndTabItem();
		}
	}
}
