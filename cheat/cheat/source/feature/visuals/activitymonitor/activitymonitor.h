#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class ActivityMonitor final : public Feature
	{
	public:
		explicit ActivityMonitor();
		~ActivityMonitor() override = default;

		void OnEnable() override
		{
		}

		void OnDisable() override
		{
		}

		void OnDraw() override;
		void OnMenu() override;

	private:
		static constexpr ImGuiWindowFlags WINDOW_FLAGS =
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize;
	};
}
