#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class GhostWindow final : public Feature
	{
	public:
		GhostWindow();
		~GhostWindow() override = default;

		void OnEnable() override
		{
		}

		void OnDisable() override
		{
		}

		void OnDraw() override;
		void OnMenu() override;

	private:
		static std::string GetGhostEvidenceString();
		static constexpr ImGuiWindowFlags WINDOW_FLAGS =
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoResize;
	};
}
