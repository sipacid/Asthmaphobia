#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class GhostESP final : public Feature
	{
	public:
		GhostESP();
		~GhostESP() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

	private:
		std::shared_ptr<Setting> ColorSetting;
		std::shared_ptr<Setting> ForceAppearSetting;
	};
}
