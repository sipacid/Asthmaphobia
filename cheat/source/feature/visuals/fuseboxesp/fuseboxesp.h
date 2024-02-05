#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class FuseBoxESP final : public Feature
	{
	public:
		explicit FuseBoxESP();
		~FuseBoxESP() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

	private:
		std::shared_ptr<Setting> ShowStatusSetting;
		std::shared_ptr<Setting> ColorSetting;
	};
}
