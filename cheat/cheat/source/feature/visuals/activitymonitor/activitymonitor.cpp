#include "activitymonitor.h"

#include <algorithm>

using namespace Asthmaphobia::Features::Visuals;

ActivityMonitor::ActivityMonitor() : Feature("Activity Monitor", "Displays the ghost activity graph", FeatureCategory::Visuals)
{
}

void ActivityMonitor::OnDraw()
{
	if (!GameState::emfData)
		return;

	ImGui::SetNextWindowSize(ImVec2(450, 275), ImGuiCond_Always);
	ImGui::Begin("Activity Monitor", nullptr, WINDOW_FLAGS);

	ImGui::SetCursorPos(ImVec2(25, 35)); // Move the graph down by increasing Y position

	constexpr auto graphSize = ImVec2(400, 200);
	const ImVec2 graphPos = ImGui::GetCursorScreenPos();

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	constexpr int gridSpacingX = graphSize.x / 6; // 10 seconds interval (0-60 seconds)
	constexpr int gridSpacingY = graphSize.y / 10; // 1 strength unit interval (0-10 scale)
	constexpr ImU32 gridColor = IM_COL32(100, 100, 100, 128);
	constexpr ImU32 axisColor = IM_COL32(200, 200, 200, 255);

	for (int x = 0; x <= graphSize.x; x += gridSpacingX)
	{
		drawList->AddLine(ImVec2(graphPos.x + x, graphPos.y), ImVec2(graphPos.x + x, graphPos.y + graphSize.y), gridColor);
	}
	for (int y = 0; y <= graphSize.y; y += gridSpacingY)
	{
		drawList->AddLine(ImVec2(graphPos.x, graphPos.y + y), ImVec2(graphPos.x + graphSize.x, graphPos.y + y), gridColor);
	}

	drawList->AddLine(ImVec2(graphPos.x, graphPos.y), ImVec2(graphPos.x, graphPos.y + graphSize.y), axisColor, 2.0f); // Y-axis
	drawList->AddLine(ImVec2(graphPos.x, graphPos.y + graphSize.y), ImVec2(graphPos.x + graphSize.x, graphPos.y + graphSize.y), axisColor, 2.0f); // X-axis

	std::vector<ImVec2> graphPoints;
	graphPoints.reserve(60);

	for (int i = 0; i < 60; ++i)
	{
		const SDK::Vector3 position = SDK::LineRenderer_GetPosition_ptr(GameState::emfData->Fields.Rend, i, nullptr);

		// Use proper scaling: 480 = 10, so divide by 48 to get correct scale
		float adjustedY = position.Y / 48.0f;
		float normalizedY = std::clamp(adjustedY, 0.0f, 10.0f);

		float yPos = graphPos.y + graphSize.y - (normalizedY * (graphSize.y / 10.0f));

		yPos = (std::min)(yPos, graphPos.y + graphSize.y);
		yPos = (std::max)(yPos, graphPos.y);

		graphPoints.emplace_back(
			graphPos.x + static_cast<float>(i) * (graphSize.x / 60.0f),
			yPos);
	}

	drawList->AddPolyline(graphPoints.data(), graphPoints.size(), IM_COL32(255, 0, 0, 255), false, 2.0f);

	for (int x = 0; x <= 60; x += 10)
	{
		std::string label = std::to_string(x) + "s";
		drawList->AddText(ImVec2(graphPos.x + x * (graphSize.x / 60.0f) - 5, graphPos.y + graphSize.y + 5), IM_COL32(255, 255, 255, 255), label.c_str());
	}
	for (int y = 0; y <= 10; y += 2) // Label every 2 units for readability
	{
		std::string label = std::to_string(y);
		drawList->AddText(ImVec2(graphPos.x - 20, graphPos.y + graphSize.y - y * (graphSize.y / 10.0f) - 7), IM_COL32(255, 255, 255, 255), label.c_str());
	}

	ImGui::Dummy(ImVec2(graphSize.x, graphSize.y + 10));

	ImGui::End();
}

void ActivityMonitor::OnMenu()
{
	ImGui::Checkbox("Enabled##activityMonitor", &std::get<bool>(EnabledSetting->GetValue()));
}
