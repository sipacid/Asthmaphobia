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
	static FeatureCategory selectedCategory = Player;
	static constexpr float SIDE_PANEL_WIDTH = 200.0f;

	ImGui::Columns(2, "MenuColumns", false);

	// Side panel
	ImGui::SetColumnWidth(0, SIDE_PANEL_WIDTH);
	ImGui::BeginGroup();
	{
		// Draw all category buttons
		for (const auto& [category, name] : CATEGORY_TO_STRING)
		{
			const bool isSelected = selectedCategory == category;
			if (isSelected)
				ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);

			if (ImGui::Button(name, ImVec2(SIDE_PANEL_WIDTH - 16, 30)))
				selectedCategory = category;

			if (isSelected)
				ImGui::PopStyleColor();
		}
	}
	ImGui::EndGroup();

	// Main content area
	ImGui::NextColumn();
	ImGui::BeginChild("MainContent", ImVec2(0, 0), false);
	{
		ImGui::Text("%s", CATEGORY_TO_STRING.find(selectedCategory)->second);
		ImGui::Separator();

		if (selectedCategory == MenuSettings)
		{
			// Settings content
			if (ImGui::Button("License"))
			{
				ImGui::OpenPopup("License Information");
			}

			if (ImGui::BeginPopupModal("License Information", nullptr, ImGuiWindowFlags_NoResize))
			{
				ImGui::BeginChild("LicenseText", ImVec2(500 * dpiScale, 300 * dpiScale), false, ImGuiWindowFlags_NoCollapse);
				ImGui::TextWrapped(
					"MIT License\n\n"
					"Copyright (c) 2024-2025 sipacid\n\n"
					"Permission is hereby granted, free of charge, to any person obtaining a copy "
					"of this software and associated documentation files (the \"Software\"), to deal "
					"in the Software without restriction, including without limitation the rights "
					"to use, copy, modify, merge, publish, distribute, sublicense, and/or sell "
					"copies of the Software, and to permit persons to whom the Software is "
					"furnished to do so, subject to the following conditions:\n\n"
					"The above copyright notice and this permission notice shall be included in all "
					"copies or substantial portions of the Software.\n\n"
					"THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR "
					"IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, "
					"FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE "
					"AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER "
					"LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, "
					"OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE "
					"SOFTWARE.");
				ImGui::EndChild();

				if (ImGui::Button("Close"))
				{
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}

			if (ImGui::Button("Unload cheat"))
			{
				globalRunning = false;
			}

			ImGui::Text("Built on: %s %s", buildDate, buildTime);
			ImGui::Text("%s", creditsText);
		}
		else
		{
			// Feature content
			ImGui::BeginChild("FeatureList", ImVec2(0, 0), false);
			for (const auto& feature : Features | std::views::values)
			{
				if (feature->GetCategory() == selectedCategory)
				{
					const float contentWidth = ImGui::GetContentRegionAvail().x - 16.0f;
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);
					ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
					ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8, 8));

					ImGui::BeginChild(("FeatureCard_" + feature->GetName()).c_str(),
					                  ImVec2(contentWidth, 0),
					                  ImGuiChildFlags_Border | ImGuiChildFlags_AutoResizeY);

					ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);
					ImGui::Text("%s", feature->GetName().c_str());
					ImGui::PopFont();
					ImGui::TextColored(ImColor(173, 173, 173, 255), "%s", feature->GetDescription().c_str());
					ImGui::Spacing();

					feature->OnMenu();
					ImGui::EndChild();
					ImGui::PopStyleVar(3);
					ImGui::Spacing();
				}
			}
			ImGui::EndChild();
		}
	}
	ImGui::EndChild();

	ImGui::Columns(1);
}
