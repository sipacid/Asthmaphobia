#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class PlayerESP final : public Feature
	{
	public:
		PlayerESP();
		~PlayerESP() override = default;

		void OnEnable() override
		{
		}

		void OnDisable() override
		{
		}

		void OnDraw() override;
		void OnMenu() override;

	private:
		std::shared_ptr<Setting> ShowPlayerSanitySetting;
		std::shared_ptr<Setting> ShowDeadStatusSetting;
		std::shared_ptr<Setting> ColorSetting;

		bool ShowSanity;
		bool ShowDeadStatus;
		ImColor Color;
		std::string TextBuffer;
		static constexpr size_t BUFFER_RESERVE_SIZE = 64;
	};
}
