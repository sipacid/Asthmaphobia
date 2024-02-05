#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class PlayerESP final : public Feature
	{
	public:
		PlayerESP();
		~PlayerESP() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

	private:
		std::shared_ptr<Setting> ShowPlayerSanitySetting;
		std::shared_ptr<Setting> ShowDeadStatusSetting;
		std::shared_ptr<Setting> ColorSetting;
	};
}
