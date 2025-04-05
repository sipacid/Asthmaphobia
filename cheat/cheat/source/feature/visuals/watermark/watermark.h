#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class Watermark final : public Feature
	{
	public:
		Watermark();
		~Watermark() override = default;

		void OnEnable() override
		{
		}

		void OnDisable() override
		{
		}

		void OnDraw() override;
		void OnMenu() override;
		[[nodiscard]] bool IsEnabled() const noexcept override { return true; }

	private:
		std::shared_ptr<Setting> ShowAverageSanitySetting;
		std::shared_ptr<Setting> ShowPingSetting;

		static constexpr ImGuiWindowFlags WINDOW_FLAGS =
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove;

		std::string CachedText;
		static constexpr std::string_view PING_PREFIX = " | Ping: ";
		static constexpr std::string_view SANITY_PREFIX = " | Avg. sanity: ";
	};
}
