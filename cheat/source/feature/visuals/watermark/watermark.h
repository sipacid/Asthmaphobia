#pragma once
#include "source/feature/feature.h"

namespace Asthmaphobia::Features::Visuals
{
	class Watermark final : public Feature
	{
	public:
		Watermark();
		~Watermark() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnDraw() override;
		void OnMenu() override;

	private:
		std::shared_ptr<Setting> ShowAverageSanitySetting;
		std::shared_ptr<Setting> ShowPingSetting;
	};
}
